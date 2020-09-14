/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-02
 *@author : THH
 *@brief : CtImR2yClassa
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

#include "ctimr2yclassa.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClassa, ct_im_r2y_classa)
#define CT_IM_R2Y_CLASSA_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClassaPrivate, CT_TYPE_IM_R2Y_CLASSA))

struct _CtImR2yClassaPrivate
{

};

static void ct_im_r2y_classa_constructor(CtImR2yClassa *self)
{
	CtImR2yClassaPrivate *priv = CT_IM_R2Y_CLASSA_GET_PRIVATE(self);
	self->ctImR2yClassa=ct_im_r2y_classa_new();
	self->imR2yCtrl2=im_r2y_ctrl2_new();
	self->imR2yClk=im_r2y_clk_new();
}

static void ct_im_r2y_classa_destructor(CtImR2yClassa *self)
{
	CtImR2yClassaPrivate *priv = CT_IM_R2Y_CLASSA_GET_PRIVATE(self);

	if(self->ctImR2yClassa){
		k_object_unref(self->ctImR2yClassa);
		self->ctImR2yClassa=NULL;
	}

	if(self->imR2yCtrl2){
		k_object_unref(self->imR2yCtrl2);
		self->imR2yCtrl2=NULL;
	}

	if(self->imR2yClk){
			k_object_unref(self->imR2yClk);
			self->imR2yClk=NULL;
		}
}

static volatile BOOL gct_im_r2y_b2r_end_flg = FALSE;
VOID ct_im_r2y_classa_b2r_int_handler(CtImR2yClassa*self,UINT32* result, UINT32 userParam)
{
	Ddim_Print(("B2R Int %x, %x\n", *result, userParam));
	gct_im_r2y_b2r_end_flg = TRUE;
}

VOID ct_im_r2y_classa_set_b2r(CtImR2yClassa*self,UCHAR pipeNo)
{
	TImB2rCtrl b2rCtrl;
	TImB2rCtrlSdramInput b2rCtrlSdramIn;
	TImB2rRect b2rRectParam;
	TImB2rInaddrInfo b2rInAddr;
	static TImB2rBayerColor imB2rWbGain = {
	        (USHORT) (1.67592592592593F * 0x100),	// R
	        (USHORT) (1.94623655913978F * 0x100),	// B
	        (USHORT) (1.0F * 0x100),	// Gr
	        (USHORT) (1.0F * 0x100),	// Gb
	        };

	IO_IMG.IMGPIPEPSW.bit.R2YSEL = 0;

	b2rCtrl.bayerTopPixel = D_IM_B2R_TOP_PIXEL_R;
	b2rCtrl.ybw.axiWriteMode.outSel = D_IM_B2R_YBW_OUTPUT_RGB;
	b2rCtrl.ybw.axiWriteMode.burstLength = D_IM_B2R_BRST_512;
	b2rCtrl.ybw.writeRequestMask [D_IM_B2R_PORT_R] = 0;
	b2rCtrl.ybw.writeRequestMask [D_IM_B2R_PORT_G] = 0;
	b2rCtrl.ybw.writeRequestMask [D_IM_B2R_PORT_B] = 0;
	b2rCtrl.ybw.trimOutEnable = D_IM_B2R_ENABLE_OFF;
	b2rCtrl.ybw.kneeEnable = 0;
	b2rCtrl.lineIntr.count = 0;
	b2rCtrl.ybwContinueStartEnable = D_IM_B2R_ENABLE_OFF;
	b2rCtrl.dekneeEnable = D_IM_B2R_ENABLE_OFF;
	b2rCtrl.ciaBypass = D_IM_B2R_ENABLE_OFF;
	b2rCtrl.ciaPadding = D_IM_B2R_ENABLE_ON;
	b2rCtrl.extOutEn = D_IM_B2R_ENABLE_ON;
	b2rCtrl.extOutAlarm = D_IM_B2R_EXT_OUT_ALARM_1LINE;
	b2rCtrl.b2rUserHandler = ct_im_r2y_classa_b2r_int_handler;
	b2rCtrl.userParam = 0;

	b2rCtrlSdramIn.burstLength = D_IM_B2R_BRST_512;
	b2rCtrlSdramIn.readRequestMask = 0;
	b2rCtrlSdramIn.inputDtype = D_IM_B2R_STL_DTYP_PACK16;
	b2rCtrlSdramIn.topOffset = 0;
	b2rCtrlSdramIn.inputGlobal = D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK;
	b2rCtrlSdramIn.lineSpace = 0;

	b2rRectParam.inputSize.imgLeft = 0;
	b2rRectParam.inputSize.imgTop = 0;
	b2rRectParam.inputSize.imgWidth = D_IM_B2R_SRC_IMG_PIXS_WIDTH;
	b2rRectParam.inputSize.imgLines = D_IM_B2R_SRC_IMG_PIXS_LINES;
	b2rRectParam.outputSize.outputGlobalW = D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES;	// dummy

	b2rInAddr.raw.addr = (VOID*) D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP;

	Im_B2R_Ctrl(pipeNo, &b2rCtrl);
	Im_B2R_Ctrl_ModeSDRAMInput(pipeNo, &b2rCtrlSdramIn);
	Im_B2R_Ctrl_Left_Shift(pipeNo, 0, 0);
	Im_B2R_Set_Rect(pipeNo, &b2rRectParam);
	Im_B2R_Set_InAddr_Info(pipeNo, &b2rInAddr);
	Im_B2R_Set_WB_Gain(pipeNo, &imB2rWbGain);
}

VOID ct_im_r2y_classa_start_b2r(CtImR2yClassa*self,UCHAR pipeNo)
{
	gct_im_r2y_b2r_end_flg = FALSE;
	Im_B2R_Start(pipeNo, D_IM_B2R_START_EXTERNAL_IF_ONLY);
}

VOID ct_im_r2y_classa_wait_b2r(CtImR2yClassa*self,UCHAR pipeNo)
{
	UINT32 loopcnt;

	for (loopcnt = 0; gct_im_r2y_b2r_end_flg == FALSE ; loopcnt++) {
		if(loopcnt >= 10) {
			Ddim_Print(("B2R wait end timeout.\n"));
			break;
		}

		DDIM_User_Dly_Tsk(1);
#ifdef CO_DEBUG_ON_PC
		ct_im_r2y_classa_b2r_int_handler( 0, 0 );
#endif
	}

	gct_im_r2y_b2r_end_flg = FALSE;
}

VOID ct_im_r2y_classa_waitend_stop_b2r(CtImR2yClassa*self,UCHAR pipeNo)
{
	ct_im_r2y_classa_wait_b2r(pipeNo);

	Im_B2R_Stop(pipeNo);
}

static volatile BOOL gct_im_r2y_ltm_end_flg = FALSE;

VOID ct_im_r2y_calssa_ltm_int_handler(UINT32* result, UINT32 userParam)
{
	Ddim_Print(("LTM Int %x, %x\n", *result, userParam));
	gct_im_r2y_ltm_end_flg = TRUE;
}

VOID ct_im_r2y_classa_set_ltm(CtImR2yClassa*self,UCHAR pipeNo)
{
	TImLtmLtmCtrlCommon ltmCtrlCommon;
	TImLtmLtmCtrlSdramInput ltmCtrlSdramIn;
	TImLtmInaddrInfo ltmInAddr;
	TImLtmLtmIndataInfo inDataInfo;
	TImLtmCtrlYlog ltmYlogCtrl;

	memset(&ltmCtrlCommon, '\0', sizeof(TImLtmLtmCtrlCommon));
	memset(&ltmCtrlSdramIn, '\0', sizeof(TImLtmLtmCtrlSdramInput));

	IO_IMG.IMGPIPEPSW.bit.R2YSEL = 1;

	ltmCtrlCommon.outSelect = D_IM_LTM_LTM_OUT_R2Y_DIRECT;
	ltmCtrlCommon.inputRect.imgWidth = D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH;
	ltmCtrlCommon.inputRect.imgLines = D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_LINES;
	ltmCtrlCommon.globalWidthYp = D_IM_LTM_LTM_SRC_IMG_MAP_GLOBAL_WIDTH_UP;
	ltmCtrlCommon.globalWidthYn = D_IM_LTM_LTM_SRC_IMG_MAP_GLOBAL_WIDTH_UP;
	ltmCtrlCommon.ltmUserHandler = ct_im_r2y_calssa_ltm_int_handler;

	ltmCtrlSdramIn.inputGlobalRgb = D_IM_LTM_LTM_SRC_IMG_RGB_GLOBAL_WIDTH;
	ltmCtrlSdramIn.inputRect.imgWidth = D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_WIDTH;
	ltmCtrlSdramIn.inputRect.imgLines = D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_LINES;

	ltmInAddr.addrR = (VOID*) D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP;
	ltmInAddr.addrG = (VOID*) D_IM_LTM_LTM_IMG_MEM_IN_G_ADDR_TOP;
	ltmInAddr.addrB = (VOID*) D_IM_LTM_LTM_IMG_MEM_IN_B_ADDR_TOP;

	inDataInfo.addrYp = (VOID*) D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP;
	inDataInfo.addrYn = (VOID*) D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP;
	inDataInfo.topBitOffsetYp = 0;
	inDataInfo.topBitOffsetYn = 0;

	ltmYlogCtrl.useTbl = 0;
	ltmYlogCtrl.endPoint0Tbl0 = 0x3FFF;
	ltmYlogCtrl.endPoint0Tbl1 = 0x3FFF;
	ltmYlogCtrl.endPoint1Tbl0 = 0x3FFF;
	ltmYlogCtrl.endPoint1Tbl1 = 0x3FFF;

	Im_LTM_LTM_Init(pipeNo);
	Im_LTM_LTM_Ctrl_Common(pipeNo, &ltmCtrlCommon);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(pipeNo, &ltmCtrlSdramIn);
	Im_LTM_LTM_Set_InAddr_Info_Rgb(pipeNo, &ltmInAddr);
	Im_LTM_LTM_Set_InData_Info(pipeNo, &inDataInfo);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(pipeNo, &ltmYlogCtrl);
	Im_LTM_LTM_Set_YLOG_Table(pipeNo, D_LTM_YLOG_TBL_00, &gctImLtmYlogTbl [0]);
}

VOID ct_im_r2y_classa_start_ltm(CtImR2yClassa*self,UCHAR pipeNo)
{
	gct_im_r2y_ltm_end_flg = FALSE;
	Im_LTM_LTM_Start(pipeNo);
}

VOID ct_im_r2y_classa_wait_ltm(CtImR2yClassa*self,UCHAR pipeNo)
{
	UINT32 loopcnt;
#ifdef CO_DEBUG_ON_PC
	UINT32 result = 1;
#endif

	for (loopcnt = 0; gct_im_r2y_ltm_end_flg == FALSE ; loopcnt++) {
		if(loopcnt >= 10) {
			Ddim_Print(("B2R wait end timeout.\n"));
			break;
		}

		DDIM_User_Dly_Tsk(1);
#ifdef CO_DEBUG_ON_PC
		ct_im_r2y_calssa_ltm_int_handler( &result, pipeNo );
#endif
	}

	gct_im_r2y_ltm_end_flg = FALSE;
}

VOID ct_im_r2y_classa_waitend_stop_ltm(CtImR2yClassa*self,UCHAR pipeNo)
{
	ct_im_r2y_classa_wait_ltm(self->ctImR2yClassa,pipeNo);

	Im_LTM_LTM_Stop(pipeNo);
}

VOID ct_im_r2y_classa_set_wb_gain_rgb(CtImR2yClassa*self,UCHAR pipeNo)
{
	static TImR2yRgbColor imR2yWbGain = {
	        (USHORT) (1.0F * 0x100),	// R
	        (USHORT) (1.0F * 0x100),	// G
	        (USHORT) (1.0F * 0x100),	// B
	        };
	INT32 imErcd;
	imErcd = im_r2y_ctrl2_set_wb_gain(self->imR2yCtrl2,pipeNo, &imR2yWbGain);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print(("im_r2y_ctrl2_set_wb_gain(self->imR2yCtrl2,) error=%d\n", imErcd));
	}
}

VOID ct_im_r2y_classa_print_r2y_common_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("R2yCmn.YYINTE = 0x%lx\n", ioR2yP1.R2yCmn.YYINTE.word));
	Ddim_Print(("R2yCmn.YYINTF = 0x%lx\n", ioR2yP1.R2yCmn.YYINTF.word));
	Ddim_Print(("R2yCmn.ramaen = 0x%lx\n", ioR2yP1.R2yCmn.ramaen.word));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("R2yCmn.YYINTE = 0x%lx\n", ioR2yP2.R2yCmn.YYINTE.word));
	Ddim_Print(("R2yCmn.YYINTF = 0x%lx\n", ioR2yP2.R2yCmn.YYINTF.word));
	Ddim_Print(("R2yCmn.ramaen = 0x%lx\n", ioR2yP2.R2yCmn.ramaen.word));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_r2y_yyr_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);//11111111111111111111111111111111111111111111111111
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyr.yyrtrg.bit.yyrtrg = 0x%x\n", ioR2yP1.yyr.yyrtrg.bit.yyrtrg));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyr.yyrtrg.bit.yyrtrg = 0x%x\n", ioR2yP2.yyr.yyrtrg.bit.yyrtrg));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_r2y_yyw_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);//111111111111111111111111111111111111111111111111111111111
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyw.YYWTRG.bit.YYWTRG = 0x%x\n", ioR2yP1.yyw.YYWTRG.bit.YYWTRG));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyw.YYWTRG.bit.YYWTRG = 0x%x\n", ioR2yP2.yyw.YYWTRG.bit.YYWTRG));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_r2y_ctrl_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("R2yCmn.LINTLV.bit.LINTLV_0      = %u\n", ioR2yP1.R2yCmn.LINTLV.bit.LINTLV_0));
	Ddim_Print(("R2yCmn.LINTLV.bit.LINTLV_1      = %u\n", ioR2yP1.R2yCmn.LINTLV.bit.LINTLV_1));
	Ddim_Print(("R2yCmn.LINTLV.bit.LINTLV_2      = %u\n", ioR2yP1.R2yCmn.LINTLV.bit.LINTLV_2));
	Ddim_Print(("R2yCmn.LINTSEL.bit.LINTS_0      = %u\n", ioR2yP1.R2yCmn.LINTSEL.bit.LINTS_0));
	Ddim_Print(("R2yCmn.LINTSEL.bit.LINTS_1      = %u\n", ioR2yP1.R2yCmn.LINTSEL.bit.LINTS_1));
	Ddim_Print(("R2yCmn.LINTSEL.bit.LINTS_2      = %u\n", ioR2yP1.R2yCmn.LINTSEL.bit.LINTS_2));
	Ddim_Print(("R2yCmn.R2YMODE.bit.YCFBYP       = %u\n", ioR2yP1.R2yCmn.R2YMODE.bit.YCFBYP));
	Ddim_Print(("R2yCmn.R2YMODE.bit.YCFPDD       = %u\n", ioR2yP1.R2yCmn.R2YMODE.bit.YCFPDD));
	Ddim_Print(("R2yCmn.R2YMODE.bit.MCCSL        = %u\n", ioR2yP1.R2yCmn.R2YMODE.bit.MCCSL));
	Ddim_Print(("R2yCmn.R2YMODE.bit.MCC1BM       = %u\n", ioR2yP1.R2yCmn.R2YMODE.bit.MCC1BM));
	Ddim_Print(("yyw.YYW0LTT.bit.YYW0LTT          = %u\n", ioR2yP1.yyw.YYW0LTT.bit.YYW0LTT));
	Ddim_Print(("yyw.yywctl.bit.YYWCSE            = %u\n", ioR2yP1.yyw.yywctl.bit.YYWCSE));
	Ddim_Print(("yyw.yywctl.bit.YYWHRV            = %u\n", ioR2yP1.yyw.yywctl.bit.YYWHRV));
	Ddim_Print(("yyw.yywctl.bit.YYWMODE           = %u\n", ioR2yP1.yyw.yywctl.bit.YYWMODE));
	Ddim_Print(("yyw.yywkpp.bit.yywkpp            = %u\n", ioR2yP1.yyw.yywkpp.bit.yywkpp));
	Ddim_Print(("\n"));
	Ddim_Print(("yych.yyw0axmd.bit.yyw0msl        = %u\n", ioR2yP1.yych.yyw0axmd.bit.yyw0msl));
	Ddim_Print(("yych.yyw0axmd.bit.yyw0doe        = %u\n", ioR2yP1.yych.yyw0axmd.bit.yyw0doe));
	Ddim_Print(("yych.yyw0axmd.bit.yyw0bl         = %u\n", ioR2yP1.yych.yyw0axmd.bit.yyw0bl));
	Ddim_Print(("yych.YYW0REQMSK.bit.YYW0REQMSK_0 = %u\n", ioR2yP1.yych.YYW0REQMSK.bit.YYW0REQMSK_0));
	Ddim_Print(("yych.YYW0REQMSK.bit.YYW0REQMSK_1 = %u\n", ioR2yP1.yych.YYW0REQMSK.bit.YYW0REQMSK_1));
	Ddim_Print(("yych.YYW0REQMSK.bit.YYW0REQMSK_2 = %u\n", ioR2yP1.yych.YYW0REQMSK.bit.YYW0REQMSK_2));
	Ddim_Print(("yyw.yyw0md.bit.RSZ0MD            = %u\n", ioR2yP1.yyw.yyw0md.bit.RSZ0MD));
	Ddim_Print(("yyw.yyw0md.bit.RDC0MD            = %u\n", ioR2yP1.yyw.yyw0md.bit.RDC0MD));
	Ddim_Print(("yyw.yyw0md.bit.RDC0EN            = %u\n", ioR2yP1.yyw.yyw0md.bit.RDC0EN));
	Ddim_Print(("yyw.yyw0md.bit.CSS0SL            = %u\n", ioR2yP1.yyw.yyw0md.bit.CSS0SL));
	Ddim_Print(("yyw.yyw0md.bit.TRM0EN            = %u\n", ioR2yP1.yyw.yyw0md.bit.TRM0EN));
	Ddim_Print(("yyw.yyw0md.bit.SPL0EN            = %u\n", ioR2yP1.yyw.yyw0md.bit.SPL0EN));
	Ddim_Print(("yyw.yyw0md.bit.CH0VFM            = %u\n", ioR2yP1.yyw.yyw0md.bit.CH0VFM));
	Ddim_Print(("yyw.yyw0md.bit.extben            = %u\n", ioR2yP1.yyw.yyw0md.bit.extben));
	Ddim_Print(("yyw.yyw0md.bit.TRMBEN            = %u\n", ioR2yP1.yyw.yyw0md.bit.TRMBEN));
	Ddim_Print(("yyw.yyw0md.bit.extcen            = %u\n", ioR2yP1.yyw.yyw0md.bit.extcen));
	Ddim_Print(("yyw.yyw0md.bit.TRMCEN            = %u\n", ioR2yP1.yyw.yyw0md.bit.TRMCEN));
	Ddim_Print(("yyw.yyw0md.bit.CH0AMD            = %u\n", ioR2yP1.yyw.yyw0md.bit.CH0AMD));
	Ddim_Print(("yyw.yyw0md.bit.CHAVFM            = %u\n", ioR2yP1.yyw.yyw0md.bit.CHAVFM));
	Ddim_Print(("\n"));
	Ddim_Print(("yych.yywaaxmd.bit.yywamsl        = %u\n", ioR2yP1.yych.yywaaxmd.bit.yywamsl));
	Ddim_Print(("yych.yywaaxmd.bit.yywadoe        = %u\n", ioR2yP1.yych.yywaaxmd.bit.yywadoe));
	Ddim_Print(("yych.yywaaxmd.bit.yywabl         = %u\n", ioR2yP1.yych.yywaaxmd.bit.yywabl));
	Ddim_Print(("yych.YYWAREQMSK.bit.YYWAREQMSK_0 = %u\n", ioR2yP1.yych.YYWAREQMSK.bit.YYWAREQMSK_0));
	Ddim_Print(("yych.YYWAREQMSK.bit.YYWAREQMSK_1 = %u\n", ioR2yP1.yych.YYWAREQMSK.bit.YYWAREQMSK_1));
	Ddim_Print(("\n"));
	Ddim_Print(("yych.yyw1axmd.bit.yyw1msl        = %u\n", ioR2yP1.yych.yyw1axmd.bit.yyw1msl));
	Ddim_Print(("yych.yyw1axmd.bit.yyw1doe        = %u\n", ioR2yP1.yych.yyw1axmd.bit.yyw1doe));
	Ddim_Print(("yych.yyw1axmd.bit.yyw1bl         = %u\n", ioR2yP1.yych.yyw1axmd.bit.yyw1bl));
	Ddim_Print(("yych.YYW1REQMSK.bit.YYW1REQMSK_0 = %u\n", ioR2yP1.yych.YYW1REQMSK.bit.YYW1REQMSK_0));
	Ddim_Print(("yych.YYW1REQMSK.bit.YYW1REQMSK_1 = %u\n", ioR2yP1.yych.YYW1REQMSK.bit.YYW1REQMSK_1));
	Ddim_Print(("yych.YYW1REQMSK.bit.YYW1REQMSK_2 = %u\n", ioR2yP1.yych.YYW1REQMSK.bit.YYW1REQMSK_2));
	Ddim_Print(("yyw.YYW1MD.bit.RSZ1MD            = %u\n", ioR2yP1.yyw.YYW1MD.bit.RSZ1MD));
	Ddim_Print(("yyw.YYW1MD.bit.RDC1MD            = %u\n", ioR2yP1.yyw.YYW1MD.bit.RDC1MD));
	Ddim_Print(("yyw.YYW1MD.bit.RDC1EN            = %u\n", ioR2yP1.yyw.YYW1MD.bit.RDC1EN));
	Ddim_Print(("yyw.YYW1MD.bit.CSS1SL            = %u\n", ioR2yP1.yyw.YYW1MD.bit.CSS1SL));
	Ddim_Print(("yyw.YYW1MD.bit.TRM1EN            = %u\n", ioR2yP1.yyw.YYW1MD.bit.TRM1EN));
	Ddim_Print(("yyw.YYW1MD.bit.SPL1EN            = %u\n", ioR2yP1.yyw.YYW1MD.bit.SPL1EN));
	Ddim_Print(("yyw.YYW1MD.bit.DFM1SL            = %u\n", ioR2yP1.yyw.YYW1MD.bit.DFM1SL));
	Ddim_Print(("yyw.YYW1MD.bit.DTY1SL            = %u\n", ioR2yP1.yyw.YYW1MD.bit.DTY1SL));
	Ddim_Print(("\n"));
	Ddim_Print(("yych.yyw2axmd.bit.yyw2msl        = %u\n", ioR2yP1.yych.yyw2axmd.bit.yyw2msl));
	Ddim_Print(("yych.yyw2axmd.bit.yyw2bl         = %u\n", ioR2yP1.yych.yyw2axmd.bit.yyw2bl));
	Ddim_Print(("yych.YYW2REQMSK.bit.YYW2REQMSK   = %u\n", ioR2yP1.yych.YYW2REQMSK.bit.YYW2REQMSK));
	Ddim_Print(("yyw.YYW2MD.bit.RDC2MD            = %u\n", ioR2yP1.yyw.YYW2MD.bit.RDC2MD));
	Ddim_Print(("yyw.YYW2MD.bit.RDC2EN            = %u\n", ioR2yP1.yyw.YYW2MD.bit.RDC2EN));
	Ddim_Print(("yyw.YYW2MD.bit.TRM2EN            = %u\n", ioR2yP1.yyw.YYW2MD.bit.TRM2EN));
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("R2yCmn.LINTLV.bit.LINTLV_0      = %u\n", ioR2yP2.R2yCmn.LINTLV.bit.LINTLV_0));
	Ddim_Print(("R2yCmn.LINTLV.bit.LINTLV_1      = %u\n", ioR2yP2.R2yCmn.LINTLV.bit.LINTLV_1));
	Ddim_Print(("R2yCmn.LINTLV.bit.LINTLV_2      = %u\n", ioR2yP2.R2yCmn.LINTLV.bit.LINTLV_2));
	Ddim_Print(("R2yCmn.LINTSEL.bit.LINTS_0      = %u\n", ioR2yP2.R2yCmn.LINTSEL.bit.LINTS_0));
	Ddim_Print(("R2yCmn.LINTSEL.bit.LINTS_1      = %u\n", ioR2yP2.R2yCmn.LINTSEL.bit.LINTS_1));
	Ddim_Print(("R2yCmn.LINTSEL.bit.LINTS_2      = %u\n", ioR2yP2.R2yCmn.LINTSEL.bit.LINTS_2));
	Ddim_Print(("R2yCmn.R2YMODE.bit.YCFBYP       = %u\n", ioR2yP2.R2yCmn.R2YMODE.bit.YCFBYP));
	Ddim_Print(("R2yCmn.R2YMODE.bit.YCFPDD       = %u\n", ioR2yP2.R2yCmn.R2YMODE.bit.YCFPDD));
	Ddim_Print(("R2yCmn.R2YMODE.bit.MCCSL        = %u\n", ioR2yP2.R2yCmn.R2YMODE.bit.MCCSL));
	Ddim_Print(("R2yCmn.R2YMODE.bit.MCC1BM       = %u\n", ioR2yP2.R2yCmn.R2YMODE.bit.MCC1BM));
	Ddim_Print(("yyw.YYW0LTT.bit.YYW0LTT          = %u\n", ioR2yP2.yyw.YYW0LTT.bit.YYW0LTT));
	Ddim_Print(("yyw.yywctl.bit.YYWCSE            = %u\n", ioR2yP2.yyw.yywctl.bit.YYWCSE));
	Ddim_Print(("yyw.yywctl.bit.YYWHRV            = %u\n", ioR2yP2.yyw.yywctl.bit.YYWHRV));
	Ddim_Print(("yyw.yywctl.bit.YYWMODE           = %u\n", ioR2yP2.yyw.yywctl.bit.YYWMODE));
	Ddim_Print(("yyw.yywkpp.bit.yywkpp            = %u\n", ioR2yP2.yyw.yywkpp.bit.yywkpp));
	Ddim_Print(("\n"));
	Ddim_Print(("yych.yyw0axmd.bit.yyw0msl        = %u\n", ioR2yP2.yych.yyw0axmd.bit.yyw0msl));
	Ddim_Print(("yych.yyw0axmd.bit.yyw0doe        = %u\n", ioR2yP2.yych.yyw0axmd.bit.yyw0doe));
	Ddim_Print(("yych.yyw0axmd.bit.yyw0bl         = %u\n", ioR2yP2.yych.yyw0axmd.bit.yyw0bl));
	Ddim_Print(("yych.YYW0REQMSK.bit.YYW0REQMSK_0 = %u\n", ioR2yP2.yych.YYW0REQMSK.bit.YYW0REQMSK_0));
	Ddim_Print(("yych.YYW0REQMSK.bit.YYW0REQMSK_1 = %u\n", ioR2yP2.yych.YYW0REQMSK.bit.YYW0REQMSK_1));
	Ddim_Print(("yych.YYW0REQMSK.bit.YYW0REQMSK_2 = %u\n", ioR2yP2.yych.YYW0REQMSK.bit.YYW0REQMSK_2));
	Ddim_Print(("yyw.yyw0md.bit.RSZ0MD            = %u\n", ioR2yP2.yyw.yyw0md.bit.RSZ0MD));
	Ddim_Print(("yyw.yyw0md.bit.RDC0MD            = %u\n", ioR2yP2.yyw.yyw0md.bit.RDC0MD));
	Ddim_Print(("yyw.yyw0md.bit.RDC0EN            = %u\n", ioR2yP2.yyw.yyw0md.bit.RDC0EN));
	Ddim_Print(("yyw.yyw0md.bit.CSS0SL            = %u\n", ioR2yP2.yyw.yyw0md.bit.CSS0SL));
	Ddim_Print(("yyw.yyw0md.bit.TRM0EN            = %u\n", ioR2yP2.yyw.yyw0md.bit.TRM0EN));
	Ddim_Print(("yyw.yyw0md.bit.SPL0EN            = %u\n", ioR2yP2.yyw.yyw0md.bit.SPL0EN));
	Ddim_Print(("yyw.yyw0md.bit.CH0VFM            = %u\n", ioR2yP2.yyw.yyw0md.bit.CH0VFM));
	Ddim_Print(("yyw.yyw0md.bit.extben            = %u\n", ioR2yP2.yyw.yyw0md.bit.extben));
	Ddim_Print(("yyw.yyw0md.bit.TRMBEN            = %u\n", ioR2yP2.yyw.yyw0md.bit.TRMBEN));
	Ddim_Print(("yyw.yyw0md.bit.extcen            = %u\n", ioR2yP2.yyw.yyw0md.bit.extcen));
	Ddim_Print(("yyw.yyw0md.bit.TRMCEN            = %u\n", ioR2yP2.yyw.yyw0md.bit.TRMCEN));
	Ddim_Print(("yyw.yyw0md.bit.CH0AMD            = %u\n", ioR2yP2.yyw.yyw0md.bit.CH0AMD));
	Ddim_Print(("yyw.yyw0md.bit.CHAVFM            = %u\n", ioR2yP2.yyw.yyw0md.bit.CHAVFM));
	Ddim_Print(("\n"));
	Ddim_Print(("yych.yywaaxmd.bit.yywamsl        = %u\n", ioR2yP2.yych.yywaaxmd.bit.yywamsl));
	Ddim_Print(("yych.yywaaxmd.bit.yywadoe        = %u\n", ioR2yP2.yych.yywaaxmd.bit.yywadoe));
	Ddim_Print(("yych.yywaaxmd.bit.yywabl         = %u\n", ioR2yP2.yych.yywaaxmd.bit.yywabl));
	Ddim_Print(("yych.YYWAREQMSK.bit.YYWAREQMSK_0 = %u\n", ioR2yP2.yych.YYWAREQMSK.bit.YYWAREQMSK_0));
	Ddim_Print(("yych.YYWAREQMSK.bit.YYWAREQMSK_1 = %u\n", ioR2yP2.yych.YYWAREQMSK.bit.YYWAREQMSK_1));
	Ddim_Print(("\n"));
	Ddim_Print(("yych.yyw1axmd.bit.yyw1msl        = %u\n", ioR2yP2.yych.yyw1axmd.bit.yyw1msl));
	Ddim_Print(("yych.yyw1axmd.bit.yyw1doe        = %u\n", ioR2yP2.yych.yyw1axmd.bit.yyw1doe));
	Ddim_Print(("yych.yyw1axmd.bit.yyw1bl         = %u\n", ioR2yP2.yych.yyw1axmd.bit.yyw1bl));
	Ddim_Print(("yych.YYW1REQMSK.bit.YYW1REQMSK_0 = %u\n", ioR2yP2.yych.YYW1REQMSK.bit.YYW1REQMSK_0));
	Ddim_Print(("yych.YYW1REQMSK.bit.YYW1REQMSK_1 = %u\n", ioR2yP2.yych.YYW1REQMSK.bit.YYW1REQMSK_1));
	Ddim_Print(("yych.YYW1REQMSK.bit.YYW1REQMSK_2 = %u\n", ioR2yP2.yych.YYW1REQMSK.bit.YYW1REQMSK_2));
	Ddim_Print(("yyw.YYW1MD.bit.RSZ1MD            = %u\n", ioR2yP2.yyw.YYW1MD.bit.RSZ1MD));
	Ddim_Print(("yyw.YYW1MD.bit.RDC1MD            = %u\n", ioR2yP2.yyw.YYW1MD.bit.RDC1MD));
	Ddim_Print(("yyw.YYW1MD.bit.RDC1EN            = %u\n", ioR2yP2.yyw.YYW1MD.bit.RDC1EN));
	Ddim_Print(("yyw.YYW1MD.bit.CSS1SL            = %u\n", ioR2yP2.yyw.YYW1MD.bit.CSS1SL));
	Ddim_Print(("yyw.YYW1MD.bit.TRM1EN            = %u\n", ioR2yP2.yyw.YYW1MD.bit.TRM1EN));
	Ddim_Print(("yyw.YYW1MD.bit.SPL1EN            = %u\n", ioR2yP2.yyw.YYW1MD.bit.SPL1EN));
	Ddim_Print(("yyw.YYW1MD.bit.DFM1SL            = %u\n", ioR2yP2.yyw.YYW1MD.bit.DFM1SL));
	Ddim_Print(("yyw.YYW1MD.bit.DTY1SL            = %u\n", ioR2yP2.yyw.YYW1MD.bit.DTY1SL));
	Ddim_Print(("\n"));
	Ddim_Print(("yych.yyw2axmd.bit.yyw2msl        = %u\n", ioR2yP2.yych.yyw2axmd.bit.yyw2msl));
	Ddim_Print(("yych.yyw2axmd.bit.yyw2bl         = %u\n", ioR2yP2.yych.yyw2axmd.bit.yyw2bl));
	Ddim_Print(("yych.YYW2REQMSK.bit.YYW2REQMSK   = %u\n", ioR2yP2.yych.YYW2REQMSK.bit.YYW2REQMSK));
	Ddim_Print(("yyw.YYW2MD.bit.RDC2MD            = %u\n", ioR2yP2.yyw.YYW2MD.bit.RDC2MD));
	Ddim_Print(("yyw.YYW2MD.bit.RDC2EN            = %u\n", ioR2yP2.yyw.YYW2MD.bit.RDC2EN));
	Ddim_Print(("yyw.YYW2MD.bit.TRM2EN            = %u\n", ioR2yP2.yyw.YYW2MD.bit.TRM2EN));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yych.YYRAXMD.bit.YYRBL         = %u\n", ioR2yP1.yych.YYRAXMD.bit.YYRBL));
	Ddim_Print(("yych.YYRREQMSK.bit.YYRREQMSK_0 = %u\n", ioR2yP1.yych.YYRREQMSK.bit.YYRREQMSK_0));
	Ddim_Print(("yych.YYRREQMSK.bit.YYRREQMSK_1 = %u\n", ioR2yP1.yych.YYRREQMSK.bit.YYRREQMSK_1));
	Ddim_Print(("yych.YYRREQMSK.bit.YYRREQMSK_2 = %u\n", ioR2yP1.yych.YYRREQMSK.bit.YYRREQMSK_2));

	Ddim_Print(("yyr.dinctl.bit.B2RDIN          = %u\n", ioR2yP1.yyr.dinctl.bit.B2RDIN));
	Ddim_Print(("yyr.YYRCTL.bit.YYRDTYP         = %u\n", ioR2yP1.yyr.YYRCTL.bit.YYRDTYP));
	Ddim_Print(("yyr.YYRCTL.bit.MONOEN          = %u\n", ioR2yP1.yyr.YYRCTL.bit.MONOEN));
	Ddim_Print(("yyr.YYRCTL.bit.DKNEN           = %u\n", ioR2yP1.yyr.YYRCTL.bit.DKNEN));
	Ddim_Print(("yyr.YYRCTL.bit.RGBLSFT         = %u\n", ioR2yP1.yyr.YYRCTL.bit.RGBLSFT));
	Ddim_Print(("yyr.YYRCTL.bit.RGBLSM          = %u\n", ioR2yP1.yyr.YYRCTL.bit.RGBLSM));
	Ddim_Print(("yyr.YYRDEF.bit.YYRDEF          = %u\n", ioR2yP1.yyr.YYRDEF.bit.YYRDEF));
	Ddim_Print(("yyr.YYROFS.bit.YYROFS_0        = %u\n", ioR2yP1.yyr.YYROFS.bit.YYROFS_0));
	Ddim_Print(("yyr.YYROFS.bit.YYROFS_1        = %u\n", ioR2yP1.yyr.YYROFS.bit.YYROFS_1));
	Ddim_Print(("yyr.YYROFS.bit.YYROFS_2        = %u\n", ioR2yP1.yyr.YYROFS.bit.YYROFS_2));
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yych.YYRAXMD.bit.YYRBL         = %u\n", ioR2yP2.yych.YYRAXMD.bit.YYRBL));
	Ddim_Print(("yych.YYRREQMSK.bit.YYRREQMSK_0 = %u\n", ioR2yP2.yych.YYRREQMSK.bit.YYRREQMSK_0));
	Ddim_Print(("yych.YYRREQMSK.bit.YYRREQMSK_1 = %u\n", ioR2yP2.yych.YYRREQMSK.bit.YYRREQMSK_1));
	Ddim_Print(("yych.YYRREQMSK.bit.YYRREQMSK_2 = %u\n", ioR2yP2.yych.YYRREQMSK.bit.YYRREQMSK_2));

	Ddim_Print(("yyr.dinctl.bit.B2RDIN          = %u\n", ioR2yP2.yyr.dinctl.bit.B2RDIN));
	Ddim_Print(("yyr.YYRCTL.bit.YYRDTYP         = %u\n", ioR2yP2.yyr.YYRCTL.bit.YYRDTYP));
	Ddim_Print(("yyr.YYRCTL.bit.MONOEN          = %u\n", ioR2yP2.yyr.YYRCTL.bit.MONOEN));
	Ddim_Print(("yyr.YYRCTL.bit.DKNEN           = %u\n", ioR2yP2.yyr.YYRCTL.bit.DKNEN));
	Ddim_Print(("yyr.YYRCTL.bit.RGBLSFT         = %u\n", ioR2yP2.yyr.YYRCTL.bit.RGBLSFT));
	Ddim_Print(("yyr.YYRCTL.bit.RGBLSM          = %u\n", ioR2yP2.yyr.YYRCTL.bit.RGBLSM));
	Ddim_Print(("yyr.YYRDEF.bit.YYRDEF          = %u\n", ioR2yP2.yyr.YYRDEF.bit.YYRDEF));
	Ddim_Print(("yyr.YYROFS.bit.YYROFS_0        = %u\n", ioR2yP2.yyr.YYROFS.bit.YYROFS_0));
	Ddim_Print(("yyr.YYROFS.bit.YYROFS_1        = %u\n", ioR2yP2.yyr.YYROFS.bit.YYROFS_1));
	Ddim_Print(("yyr.YYROFS.bit.YYROFS_2        = %u\n", ioR2yP2.yyr.YYROFS.bit.YYROFS_2));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyr.dinctl.bit.B2RDIN = %u\n", ioR2yP1.yyr.dinctl.bit.B2RDIN));
	Ddim_Print(("yyr.dinctl.bit.frmstp = %u\n", ioR2yP1.yyr.dinctl.bit.frmstp));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyr.dinctl.bit.B2RDIN = %u\n", ioR2yP2.yyr.dinctl.bit.B2RDIN));
	Ddim_Print(("yyr.dinctl.bit.frmstp = %u\n", ioR2yP2.yyr.dinctl.bit.frmstp));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_resize_rect_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE1\n"));
	// im_r2y_calc_yyr_address_sdram_input(), im_r2y_set_yyr_address_sdram_input(), im_r2y_set_in_addr_info(self->imR2y,)
	Ddim_Print(("yyr.YYRA.bit.YYRA_0         = %lx\n", ioR2yP1.yyr.YYRA.bit.YYRA_0));
	Ddim_Print(("yyr.YYRA.bit.YYRA_1         = %lx\n", ioR2yP1.yyr.YYRA.bit.YYRA_1));
	Ddim_Print(("yyr.YYRA.bit.YYRA_2         = %lx\n", ioR2yP1.yyr.YYRA.bit.YYRA_2));
	// im_r2y_calc_in_rect_sdram_input()
	Ddim_Print(("yyr.YYRHSIZ                 = %lu\n", ioR2yP1.yyr.YYRHSIZ.word));
	Ddim_Print(("yyr.YYRVSIZ                 = %lu\n", ioR2yP1.yyr.YYRVSIZ.word));
	// im_r2y_calc_out_pitch(), im_r2y_set_out_pitch()
	Ddim_Print(
	        ("RSZ0HSTA                    = %x(%f)\n", ioR2yP1.yyw.RSZ0HSTA.bit.RSZ0HSTA, (float) ioR2yP1.yyw
	                .RSZ0HSTA.bit.RSZ0HSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ0HPIT                    = %x(%f)\n", ioR2yP1.yyw.RSZ0HPIT.bit.RSZ0HPIT, (float) ioR2yP1.yyw
	                .RSZ0HPIT.bit.RSZ0HPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ0VSTA                    = %x(%f)\n", ioR2yP1.yyw.RSZ0VSTA.bit.RSZ0VSTA, (float) ioR2yP1.yyw
	                .RSZ0VSTA.bit.RSZ0VSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ0VPIT                    = %x(%f)\n", ioR2yP1.yyw.RSZ0VPIT.bit.RSZ0VPIT, (float) ioR2yP1.yyw
	                .RSZ0VPIT.bit.RSZ0VPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ1HSTA                    = %x(%f)\n", ioR2yP1.yyw.RSZ1HSTA.bit.RSZ1HSTA, (float) ioR2yP1.yyw
	                .RSZ1HSTA.bit.RSZ1HSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ1HPIT                    = %x(%f)\n", ioR2yP1.yyw.RSZ1HPIT.bit.RSZ1HPIT, (float) ioR2yP1.yyw
	                .RSZ1HPIT.bit.RSZ1HPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ1VSTA                    = %x(%f)\n", ioR2yP1.yyw.RSZ1VSTA.bit.RSZ1VSTA, (float) ioR2yP1.yyw
	                .RSZ1VSTA.bit.RSZ1VSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ1VPIT                    = %x(%f)\n", ioR2yP1.yyw.RSZ1VPIT.bit.RSZ1VPIT, (float) ioR2yP1.yyw
	                .RSZ1VPIT.bit.RSZ1VPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ2HSTA                    = %x(%f)\n", ioR2yP1.yyw.RSZ2HSTA.bit.RSZ2HSTA, (float) ioR2yP1.yyw
	                .RSZ2HSTA.bit.RSZ2HSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ2HPIT                    = %x(%f)\n", ioR2yP1.yyw.RSZ2HPIT.bit.RSZ2HPIT, (float) ioR2yP1.yyw
	                .RSZ2HPIT.bit.RSZ2HPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ2VSTA                    = %x(%f)\n", ioR2yP1.yyw.RSZ2VSTA.bit.RSZ2VSTA, (float) ioR2yP1.yyw
	                .RSZ2VSTA.bit.RSZ2VSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ2VPIT                    = %x(%f)\n", ioR2yP1.yyw.RSZ2VPIT.bit.RSZ2VPIT, (float) ioR2yP1.yyw
	                .RSZ2VPIT.bit.RSZ2VPIT / D_IM_R2Y_STA_PIT_1_0));
	// im_r2y2_set_resize_rect(self->imR2y2,), Im_r2y_set_resize_pitch(self->imR2y,)
	Ddim_Print(
	        ("yyw.YYW0DEF.bit.YYW0DEF_0   = %x(%d)\n", ioR2yP1.yyw.YYW0DEF.bit.YYW0DEF_0, ioR2yP1.yyw.YYW0DEF.bit
	                .YYW0DEF_0));
	Ddim_Print(
	        ("yyw.YYW0DEF.bit.YYW0DEF_1   = %x(%d)\n", ioR2yP1.yyw.YYW0DEF.bit.YYW0DEF_1, ioR2yP1.yyw.YYW0DEF.bit
	                .YYW0DEF_1));
	Ddim_Print(
	        ("yyw.YYW1DEF.bit.YYW1DEF_0   = %x(%d)\n", ioR2yP1.yyw.YYW1DEF.bit.YYW1DEF_0, ioR2yP1.yyw.YYW1DEF.bit
	                .YYW1DEF_0));
	Ddim_Print(
	        ("yyw.YYW1DEF.bit.YYW1DEF_1   = %x(%d)\n", ioR2yP1.yyw.YYW1DEF.bit.YYW1DEF_1, ioR2yP1.yyw.YYW1DEF.bit
	                .YYW1DEF_1));
	Ddim_Print(
	        ("yyw.YYW2DEF.bit.YYW2DEF     = %x(%d)\n", ioR2yP1.yyw.YYW2DEF.bit.YYW2DEF, ioR2yP1.yyw.YYW2DEF.bit
	                .YYW2DEF));
	Ddim_Print(
	        ("yyw.YYWADEF.bit.YYWADEF     = %x(%d)\n", ioR2yP1.yyw.YYWADEF.bit.YYWADEF, ioR2yP1.yyw.YYWADEF.bit
	                .YYWADEF));
	//
	Ddim_Print(
	        ("yyw.YYW0OFSX.bit.YYW0OFSX_0 = %x(%d)\n", ioR2yP1.yyw.YYW0OFSX.bit.YYW0OFSX_0, ioR2yP1.yyw.YYW0OFSX.bit
	                .YYW0OFSX_0));
	Ddim_Print(
	        ("yyw.YYW0OFSX.bit.YYW0OFSX_1 = %x(%d)\n", ioR2yP1.yyw.YYW0OFSX.bit.YYW0OFSX_1, ioR2yP1.yyw.YYW0OFSX.bit
	                .YYW0OFSX_1));
	Ddim_Print(
	        ("yyw.YYW0OFSX.bit.YYW0OFSX_2 = %x(%d)\n", ioR2yP1.yyw.YYW0OFSX.bit.YYW0OFSX_2, ioR2yP1.yyw.YYW0OFSX.bit
	                .YYW0OFSX_2));
	Ddim_Print(
	        ("yyw.YYW0OFSX.bit.YYW0OFSX_3 = %x(%d)\n", ioR2yP1.yyw.YYW0OFSX.bit.YYW0OFSX_3, ioR2yP1.yyw.YYW0OFSX.bit
	                .YYW0OFSX_3));
	Ddim_Print(
	        ("yyw.YYWAOFSX.bit.YYWAOFSX_0 = %x(%d)\n", ioR2yP1.yyw.YYWAOFSX.bit.YYWAOFSX_0, ioR2yP1.yyw.YYWAOFSX.bit
	                .YYWAOFSX_0));
	Ddim_Print(
	        ("yyw.YYWAOFSX.bit.YYWAOFSX_1 = %x(%d)\n", ioR2yP1.yyw.YYWAOFSX.bit.YYWAOFSX_1, ioR2yP1.yyw.YYWAOFSX.bit
	                .YYWAOFSX_1));
	Ddim_Print(
	        ("yyw.YYWAOFSX.bit.YYWAOFSX_2 = %x(%d)\n", ioR2yP1.yyw.YYWAOFSX.bit.YYWAOFSX_2, ioR2yP1.yyw.YYWAOFSX.bit
	                .YYWAOFSX_2));
	Ddim_Print(
	        ("yyw.YYWAOFSX.bit.YYWAOFSX_3 = %x(%d)\n", ioR2yP1.yyw.YYWAOFSX.bit.YYWAOFSX_3, ioR2yP1.yyw.YYWAOFSX.bit
	                .YYWAOFSX_3));
	Ddim_Print(("PIPE2\n"));
	// im_r2y_calc_yyr_address_sdram_input(), im_r2y_set_yyr_address_sdram_input(), im_r2y_set_in_addr_info(self->imR2y,)
	Ddim_Print(("yyr.YYRA.bit.YYRA_0         = %lx\n", ioR2yP2.yyr.YYRA.bit.YYRA_0));
	Ddim_Print(("yyr.YYRA.bit.YYRA_1         = %lx\n", ioR2yP2.yyr.YYRA.bit.YYRA_1));
	Ddim_Print(("yyr.YYRA.bit.YYRA_2         = %lx\n", ioR2yP2.yyr.YYRA.bit.YYRA_2));
	// im_r2y_calc_in_rect_sdram_input()
	Ddim_Print(("yyr.YYRHSIZ                 = %lu\n", ioR2yP2.yyr.YYRHSIZ.word));
	Ddim_Print(("yyr.YYRVSIZ                 = %lu\n", ioR2yP2.yyr.YYRVSIZ.word));
	// im_r2y_calc_out_pitch(), im_r2y_set_out_pitch()
	Ddim_Print(
	        ("RSZ0HSTA                    = %x(%f)\n", ioR2yP2.yyw.RSZ0HSTA.bit.RSZ0HSTA, (float) ioR2yP2.yyw
	                .RSZ0HSTA.bit.RSZ0HSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ0HPIT                    = %x(%f)\n", ioR2yP2.yyw.RSZ0HPIT.bit.RSZ0HPIT, (float) ioR2yP2.yyw
	                .RSZ0HPIT.bit.RSZ0HPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ0VSTA                    = %x(%f)\n", ioR2yP2.yyw.RSZ0VSTA.bit.RSZ0VSTA, (float) ioR2yP2.yyw
	                .RSZ0VSTA.bit.RSZ0VSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ0VPIT                    = %x(%f)\n", ioR2yP2.yyw.RSZ0VPIT.bit.RSZ0VPIT, (float) ioR2yP2.yyw
	                .RSZ0VPIT.bit.RSZ0VPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ1HSTA                    = %x(%f)\n", ioR2yP2.yyw.RSZ1HSTA.bit.RSZ1HSTA, (float) ioR2yP2.yyw
	                .RSZ1HSTA.bit.RSZ1HSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ1HPIT                    = %x(%f)\n", ioR2yP2.yyw.RSZ1HPIT.bit.RSZ1HPIT, (float) ioR2yP2.yyw
	                .RSZ1HPIT.bit.RSZ1HPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ1VSTA                    = %x(%f)\n", ioR2yP2.yyw.RSZ1VSTA.bit.RSZ1VSTA, (float) ioR2yP2.yyw
	                .RSZ1VSTA.bit.RSZ1VSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ1VPIT                    = %x(%f)\n", ioR2yP2.yyw.RSZ1VPIT.bit.RSZ1VPIT, (float) ioR2yP2.yyw
	                .RSZ1VPIT.bit.RSZ1VPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ2HSTA                    = %x(%f)\n", ioR2yP2.yyw.RSZ2HSTA.bit.RSZ2HSTA, (float) ioR2yP2.yyw
	                .RSZ2HSTA.bit.RSZ2HSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ2HPIT                    = %x(%f)\n", ioR2yP2.yyw.RSZ2HPIT.bit.RSZ2HPIT, (float) ioR2yP2.yyw
	                .RSZ2HPIT.bit.RSZ2HPIT / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ2VSTA                    = %x(%f)\n", ioR2yP2.yyw.RSZ2VSTA.bit.RSZ2VSTA, (float) ioR2yP2.yyw
	                .RSZ2VSTA.bit.RSZ2VSTA / D_IM_R2Y_STA_PIT_1_0));
	Ddim_Print(
	        ("RSZ2VPIT                    = %x(%f)\n", ioR2yP2.yyw.RSZ2VPIT.bit.RSZ2VPIT, (float) ioR2yP2.yyw
	                .RSZ2VPIT.bit.RSZ2VPIT / D_IM_R2Y_STA_PIT_1_0));
	// im_r2y2_set_resize_rect(self->imR2y2,), Im_r2y_set_resize_pitch(self->imR2y,)
	Ddim_Print(
	        ("yyw.YYW0DEF.bit.YYW0DEF_0   = %x(%d)\n", ioR2yP2.yyw.YYW0DEF.bit.YYW0DEF_0, ioR2yP2.yyw.YYW0DEF.bit
	                .YYW0DEF_0));
	Ddim_Print(
	        ("yyw.YYW0DEF.bit.YYW0DEF_1   = %x(%d)\n", ioR2yP2.yyw.YYW0DEF.bit.YYW0DEF_1, ioR2yP2.yyw.YYW0DEF.bit
	                .YYW0DEF_1));
	Ddim_Print(
	        ("yyw.YYW1DEF.bit.YYW1DEF_0   = %x(%d)\n", ioR2yP2.yyw.YYW1DEF.bit.YYW1DEF_0, ioR2yP2.yyw.YYW1DEF.bit
	                .YYW1DEF_0));
	Ddim_Print(
	        ("yyw.YYW1DEF.bit.YYW1DEF_1   = %x(%d)\n", ioR2yP2.yyw.YYW1DEF.bit.YYW1DEF_1, ioR2yP2.yyw.YYW1DEF.bit
	                .YYW1DEF_1));
	Ddim_Print(
	        ("yyw.YYW2DEF.bit.YYW2DEF     = %x(%d)\n", ioR2yP2.yyw.YYW2DEF.bit.YYW2DEF, ioR2yP2.yyw.YYW2DEF.bit
	                .YYW2DEF));
	Ddim_Print(
	        ("yyw.YYWADEF.bit.YYWADEF     = %x(%d)\n", ioR2yP2.yyw.YYWADEF.bit.YYWADEF, ioR2yP2.yyw.YYWADEF.bit
	                .YYWADEF));
	//
	Ddim_Print(
	        ("yyw.YYW0OFSX.bit.YYW0OFSX_0 = %x(%d)\n", ioR2yP2.yyw.YYW0OFSX.bit.YYW0OFSX_0, ioR2yP2.yyw.YYW0OFSX.bit
	                .YYW0OFSX_0));
	Ddim_Print(
	        ("yyw.YYW0OFSX.bit.YYW0OFSX_1 = %x(%d)\n", ioR2yP2.yyw.YYW0OFSX.bit.YYW0OFSX_1, ioR2yP2.yyw.YYW0OFSX.bit
	                .YYW0OFSX_1));
	Ddim_Print(
	        ("yyw.YYW0OFSX.bit.YYW0OFSX_2 = %x(%d)\n", ioR2yP2.yyw.YYW0OFSX.bit.YYW0OFSX_2, ioR2yP2.yyw.YYW0OFSX.bit
	                .YYW0OFSX_2));
	Ddim_Print(
	        ("yyw.YYW0OFSX.bit.YYW0OFSX_3 = %x(%d)\n", ioR2yP2.yyw.YYW0OFSX.bit.YYW0OFSX_3, ioR2yP2.yyw.YYW0OFSX.bit
	                .YYW0OFSX_3));

	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_trimming_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyw.TRM0H.bit.TRM0HSTA = %u\n", ioR2yP1.yyw.TRM0H.bit.TRM0HSTA));
	Ddim_Print(("yyw.TRM0H.bit.TRM0HSIZ = %u\n", ioR2yP1.yyw.TRM0H.bit.TRM0HSIZ));
	Ddim_Print(("yyw.TRM0V.bit.TRM0VSTA = %u\n", ioR2yP1.yyw.TRM0V.bit.TRM0VSTA));
	Ddim_Print(("yyw.TRM0V.bit.TRM0VSIZ = %u\n", ioR2yP1.yyw.TRM0V.bit.TRM0VSIZ));
	Ddim_Print(("yyw.TRM1H.bit.TRM1HSTA = %u\n", ioR2yP1.yyw.TRM1H.bit.TRM1HSTA));
	Ddim_Print(("yyw.TRM1H.bit.TRM1HSIZ = %u\n", ioR2yP1.yyw.TRM1H.bit.TRM1HSIZ));
	Ddim_Print(("yyw.TRM1V.bit.TRM1VSTA = %u\n", ioR2yP1.yyw.TRM1V.bit.TRM1VSTA));
	Ddim_Print(("yyw.TRM1V.bit.TRM1VSIZ = %u\n", ioR2yP1.yyw.TRM1V.bit.TRM1VSIZ));
	Ddim_Print(("yyw.TRM2H.bit.TRM2HSTA = %u\n", ioR2yP1.yyw.TRM2H.bit.TRM2HSTA));
	Ddim_Print(("yyw.TRM2H.bit.TRM2HSIZ = %u\n", ioR2yP1.yyw.TRM2H.bit.TRM2HSIZ));
	Ddim_Print(("yyw.TRM2V.bit.TRM2VSTA = %u\n", ioR2yP1.yyw.TRM2V.bit.TRM2VSTA));
	Ddim_Print(("yyw.TRM2V.bit.TRM2VSIZ = %u\n", ioR2yP1.yyw.TRM2V.bit.TRM2VSIZ));
	Ddim_Print(("yyw.TRMBH.bit.TRMBHSTA = %u\n", ioR2yP1.yyw.TRMBH.bit.TRMBHSTA));
	Ddim_Print(("yyw.TRMBH.bit.TRMBHSIZ = %u\n", ioR2yP1.yyw.TRMBH.bit.TRMBHSIZ));
	Ddim_Print(("yyw.TRMBV.bit.TRMBVSTA = %u\n", ioR2yP1.yyw.TRMBV.bit.TRMBVSTA));
	Ddim_Print(("yyw.TRMBV.bit.TRMBVSIZ = %u\n", ioR2yP1.yyw.TRMBV.bit.TRMBVSIZ));
	Ddim_Print(("yyw.TRMCH.bit.TRMCHSTA = %u\n", ioR2yP1.yyw.TRMCH.bit.TRMCHSTA));
	Ddim_Print(("yyw.TRMCH.bit.TRMCHSIZ = %u\n", ioR2yP1.yyw.TRMCH.bit.TRMCHSIZ));
	Ddim_Print(("yyw.TRMCV.bit.TRMCVSTA = %u\n", ioR2yP1.yyw.TRMCV.bit.TRMCVSTA));
	Ddim_Print(("yyw.TRMCV.bit.TRMCVSIZ = %u\n", ioR2yP1.yyw.TRMCV.bit.TRMCVSIZ));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyw.TRM0H.bit.TRM0HSTA = %u\n", ioR2yP2.yyw.TRM0H.bit.TRM0HSTA));
	Ddim_Print(("yyw.TRM0H.bit.TRM0HSIZ = %u\n", ioR2yP2.yyw.TRM0H.bit.TRM0HSIZ));
	Ddim_Print(("yyw.TRM0V.bit.TRM0VSTA = %u\n", ioR2yP2.yyw.TRM0V.bit.TRM0VSTA));
	Ddim_Print(("yyw.TRM0V.bit.TRM0VSIZ = %u\n", ioR2yP2.yyw.TRM0V.bit.TRM0VSIZ));
	Ddim_Print(("yyw.TRM1H.bit.TRM1HSTA = %u\n", ioR2yP2.yyw.TRM1H.bit.TRM1HSTA));
	Ddim_Print(("yyw.TRM1H.bit.TRM1HSIZ = %u\n", ioR2yP2.yyw.TRM1H.bit.TRM1HSIZ));
	Ddim_Print(("yyw.TRM1V.bit.TRM1VSTA = %u\n", ioR2yP2.yyw.TRM1V.bit.TRM1VSTA));
	Ddim_Print(("yyw.TRM1V.bit.TRM1VSIZ = %u\n", ioR2yP2.yyw.TRM1V.bit.TRM1VSIZ));
	Ddim_Print(("yyw.TRM2H.bit.TRM2HSTA = %u\n", ioR2yP2.yyw.TRM2H.bit.TRM2HSTA));
	Ddim_Print(("yyw.TRM2H.bit.TRM2HSIZ = %u\n", ioR2yP2.yyw.TRM2H.bit.TRM2HSIZ));
	Ddim_Print(("yyw.TRM2V.bit.TRM2VSTA = %u\n", ioR2yP2.yyw.TRM2V.bit.TRM2VSTA));
	Ddim_Print(("yyw.TRM2V.bit.TRM2VSIZ = %u\n", ioR2yP2.yyw.TRM2V.bit.TRM2VSIZ));
	Ddim_Print(("yyw.TRMBH.bit.TRMBHSTA = %u\n", ioR2yP2.yyw.TRMBH.bit.TRMBHSTA));
	Ddim_Print(("yyw.TRMBH.bit.TRMBHSIZ = %u\n", ioR2yP2.yyw.TRMBH.bit.TRMBHSIZ));
	Ddim_Print(("yyw.TRMBV.bit.TRMBVSTA = %u\n", ioR2yP2.yyw.TRMBV.bit.TRMBVSTA));
	Ddim_Print(("yyw.TRMBV.bit.TRMBVSIZ = %u\n", ioR2yP2.yyw.TRMBV.bit.TRMBVSIZ));
	Ddim_Print(("yyw.TRMCH.bit.TRMCHSTA = %u\n", ioR2yP2.yyw.TRMCH.bit.TRMCHSTA));
	Ddim_Print(("yyw.TRMCH.bit.TRMCHSIZ = %u\n", ioR2yP2.yyw.TRMCH.bit.TRMCHSIZ));
	Ddim_Print(("yyw.TRMCV.bit.TRMCVSTA = %u\n", ioR2yP2.yyw.TRMCV.bit.TRMCVSTA));
	Ddim_Print(("yyw.TRMCV.bit.TRMCVSIZ = %u\n", ioR2yP2.yyw.TRMCV.bit.TRMCVSIZ));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_color_extract_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyw.PCEMD.bit.PCEEN = %u\n", ioR2yP1.yyw.PCEMD.bit.PCEEN));
	Ddim_Print(("yyw.PCEXY.bit.PCEX  = 0x%x\n", ioR2yP1.yyw.PCEXY.bit.PCEX));
	Ddim_Print(("yyw.PCEXY.bit.PCEY  = 0x%x\n", ioR2yP1.yyw.PCEXY.bit.PCEY));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyw.PCEMD.bit.PCEEN = %u\n", ioR2yP2.yyw.PCEMD.bit.PCEEN));
	Ddim_Print(("yyw.PCEXY.bit.PCEX  = 0x%x\n", ioR2yP2.yyw.PCEXY.bit.PCEX));
	Ddim_Print(("yyw.PCEXY.bit.PCEY  = 0x%x\n", ioR2yP2.yyw.PCEXY.bit.PCEY));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_chroma_scale_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyw.PCEC.bit.PCECOF = 0x%x\n", ioR2yP1.yyw.PCEC.bit.PCECOF));
	Ddim_Print(("yyw.PCEC.bit.PCECGA = 0x%x\n", ioR2yP1.yyw.PCEC.bit.PCECGA));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyw.PCEC.bit.PCECOF = 0x%x\n", ioR2yP2.yyw.PCEC.bit.PCECOF));
	Ddim_Print(("yyw.PCEC.bit.PCECGA = 0x%x\n", ioR2yP2.yyw.PCEC.bit.PCECGA));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_hue_scale_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyw.PCEH.bit.PCEHOF = 0x%x\n", ioR2yP1.yyw.PCEH.bit.PCEHOF));
	Ddim_Print(("yyw.PCEH.bit.PCEHGA = 0x%x\n", ioR2yP1.yyw.PCEH.bit.PCEHGA));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyw.PCEH.bit.PCEHOF = 0x%x\n", ioR2yP2.yyw.PCEH.bit.PCEHOF));
	Ddim_Print(("yyw.PCEH.bit.PCEHGA = 0x%x\n", ioR2yP2.yyw.PCEH.bit.PCEHGA));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_hist_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyw.hstmd.bit.HSTEN  = %u\n", ioR2yP1.yyw.hstmd.bit.HSTEN));
	Ddim_Print(("yyw.hstmd.bit.HSTSEL = %u\n", ioR2yP1.yyw.hstmd.bit.HSTSEL));
	Ddim_Print(("yyw.hstmd.bit.PIT_M  = %u\n", ioR2yP1.yyw.hstmd.bit.PIT_M));
	Ddim_Print(("yyw.hstmd.bit.yhsovf = %u\n", ioR2yP1.yyw.hstmd.bit.yhsovf));
	Ddim_Print(("yyw.hstmd.bit.hststs = %u\n", ioR2yP1.yyw.hstmd.bit.hststs));
	Ddim_Print(("yyw.HSTH.bit.HSTHSTA = 0x%x\n", ioR2yP1.yyw.HSTH.bit.HSTHSTA));
	Ddim_Print(("yyw.HSTH.bit.HSTHSIZ = 0x%x\n", ioR2yP1.yyw.HSTH.bit.HSTHSIZ));
	Ddim_Print(("yyw.HSTV.bit.HSTVSTA = 0x%x\n", ioR2yP1.yyw.HSTV.bit.HSTVSTA));
	Ddim_Print(("yyw.HSTV.bit.HSTVSIZ = 0x%x\n", ioR2yP1.yyw.HSTV.bit.HSTVSIZ));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyw.hstmd.bit.HSTEN  = %u\n", ioR2yP2.yyw.hstmd.bit.HSTEN));
	Ddim_Print(("yyw.hstmd.bit.HSTSEL = %u\n", ioR2yP2.yyw.hstmd.bit.HSTSEL));
	Ddim_Print(("yyw.hstmd.bit.PIT_M  = %u\n", ioR2yP2.yyw.hstmd.bit.PIT_M));
	Ddim_Print(("yyw.hstmd.bit.yhsovf = %u\n", ioR2yP2.yyw.hstmd.bit.yhsovf));
	Ddim_Print(("yyw.hstmd.bit.hststs = %u\n", ioR2yP2.yyw.hstmd.bit.hststs));
	Ddim_Print(("yyw.HSTH.bit.HSTHSTA = 0x%x\n", ioR2yP2.yyw.HSTH.bit.HSTHSTA));
	Ddim_Print(("yyw.HSTH.bit.HSTHSIZ = 0x%x\n", ioR2yP2.yyw.HSTH.bit.HSTHSIZ));
	Ddim_Print(("yyw.HSTV.bit.HSTVSTA = 0x%x\n", ioR2yP2.yyw.HSTV.bit.HSTVSTA));
	Ddim_Print(("yyw.HSTV.bit.HSTVSIZ = 0x%x\n", ioR2yP2.yyw.HSTV.bit.HSTVSIZ));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

VOID ct_im_r2y_classa_print_post_resize_edge0_reg( CtImR2yClassa*self)
{
	im_r2y_clk_on_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("PIPE1\n"));
	Ddim_Print(("yyw.ee0ctl.bit.ee0en          = 0x%x\n", ioR2yP1.yyw.ee0ctl.bit.ee0en));
	Ddim_Print(("yyw.ee0ctl.bit.ee0tc          = 0x%x\n", ioR2yP1.yyw.ee0ctl.bit.ee0tc));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk0      = 0x%x\n", ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk0));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk1      = 0x%x\n", ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk1));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk2      = 0x%x\n", ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk2));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk3      = 0x%x\n", ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk3));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk4      = 0x%x\n", ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk4));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk5      = 0x%x\n", ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk5));
	Ddim_Print(("yyw.ee0nrlv.bit.ee0nrlv       = 0x%x\n", ioR2yP1.yyw.ee0nrlv.bit.ee0nrlv));
	Ddim_Print(("yyw.ee0corpof.bit.ee0corpof0 = 0x%x\n", ioR2yP1.yyw.ee0corpof.bit.ee0corpof0));
	Ddim_Print(("yyw.ee0corpof.bit.ee0corpof1 = 0x%x\n", ioR2yP1.yyw.ee0corpof.bit.ee0corpof1));
	Ddim_Print(("yyw.ee0corpof.bit.ee0corpof2 = 0x%x\n", ioR2yP1.yyw.ee0corpof.bit.ee0corpof2));
	Ddim_Print(("yyw.ee0corpof.bit.ee0corpof3 = 0x%x\n", ioR2yP1.yyw.ee0corpof.bit.ee0corpof3));
	Ddim_Print(("yyw.ee0corpga.bit.ee0corpga0 = 0x%x\n", ioR2yP1.yyw.ee0corpga.bit.ee0corpga0));
	Ddim_Print(("yyw.ee0corpga.bit.ee0corpga1 = 0x%x\n", ioR2yP1.yyw.ee0corpga.bit.ee0corpga1));
	Ddim_Print(("yyw.ee0corpga.bit.ee0corpga2 = 0x%x\n", ioR2yP1.yyw.ee0corpga.bit.ee0corpga2));
	Ddim_Print(("yyw.ee0corpga.bit.ee0corpga3 = 0x%x\n", ioR2yP1.yyw.ee0corpga.bit.ee0corpga3));
	Ddim_Print(("yyw.ee0corpbd.bit.ee0corpbd1 = 0x%x\n", ioR2yP1.yyw.ee0corpbd.bit.ee0corpbd1));
	Ddim_Print(("yyw.ee0corpbd.bit.ee0corpbd2 = 0x%x\n", ioR2yP1.yyw.ee0corpbd.bit.ee0corpbd2));
	Ddim_Print(("yyw.ee0corpbd.bit.ee0corpbd3 = 0x%x\n", ioR2yP1.yyw.ee0corpbd.bit.ee0corpbd3));
	Ddim_Print(("yyw.ee0cormof.bit.ee0cormof0 = 0x%x\n", ioR2yP1.yyw.ee0cormof.bit.ee0cormof0));
	Ddim_Print(("yyw.ee0cormof.bit.ee0cormof1 = 0x%x\n", ioR2yP1.yyw.ee0cormof.bit.ee0cormof1));
	Ddim_Print(("yyw.ee0cormof.bit.ee0cormof2 = 0x%x\n", ioR2yP1.yyw.ee0cormof.bit.ee0cormof2));
	Ddim_Print(("yyw.ee0cormof.bit.ee0cormof3 = 0x%x\n", ioR2yP1.yyw.ee0cormof.bit.ee0cormof3));
	Ddim_Print(("yyw.ee0cormga.bit.ee0cormga0 = 0x%x\n", ioR2yP1.yyw.ee0cormga.bit.ee0cormga0));
	Ddim_Print(("yyw.ee0cormga.bit.ee0cormga1 = 0x%x\n", ioR2yP1.yyw.ee0cormga.bit.ee0cormga1));
	Ddim_Print(("yyw.ee0cormga.bit.ee0cormga2 = 0x%x\n", ioR2yP1.yyw.ee0cormga.bit.ee0cormga2));
	Ddim_Print(("yyw.ee0cormga.bit.ee0cormga3 = 0x%x\n", ioR2yP1.yyw.ee0cormga.bit.ee0cormga3));
	Ddim_Print(("yyw.ee0cormbd.bit.ee0cormbd1 = 0x%x\n", ioR2yP1.yyw.ee0cormbd.bit.ee0cormbd1));
	Ddim_Print(("yyw.ee0cormbd.bit.ee0cormbd2 = 0x%x\n", ioR2yP1.yyw.ee0cormbd.bit.ee0cormbd2));
	Ddim_Print(("yyw.ee0cormbd.bit.ee0cormbd3 = 0x%x\n", ioR2yP1.yyw.ee0cormbd.bit.ee0cormbd3));
	Ddim_Print(("yyw.ee0sclsup.bit.ee0sclsup   = 0x%x\n", ioR2yP1.yyw.ee0sclsup.bit.ee0sclsup));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof0 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof0));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof1 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof1));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof2 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof2));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof3 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof3));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof4 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof4));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof5 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof5));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof6 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof6));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof7 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof7));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof8 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof8));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof9 = 0x%x\n", ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof9));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga0 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga0));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga1 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga1));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga2 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga2));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga3 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga3));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga4 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga4));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga5 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga5));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga6 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga6));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga7 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga7));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga8 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga8));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga9 = 0x%x\n", ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga9));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd1 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd1));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd2 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd2));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd3 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd3));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd4 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd4));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd5 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd5));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd6 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd6));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd7 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd7));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd8 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd8));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd9 = 0x%x\n", ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd9));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof0 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof0));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof1 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof1));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof2 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof2));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof3 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof3));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof4 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof4));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof5 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof5));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof6 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof6));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof7 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof7));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof8 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof8));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof9 = 0x%x\n", ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof9));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga0 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga0));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga1 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga1));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga2 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga2));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga3 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga3));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga4 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga4));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga5 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga5));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga6 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga6));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga7 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga7));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga8 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga8));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga9 = 0x%x\n", ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga9));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd1 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd1));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd2 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd2));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd3 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd3));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd4 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd4));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd5 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd5));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd6 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd6));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd7 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd7));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd8 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd8));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd9 = 0x%x\n", ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd9));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof0 = 0x%x\n", ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof0));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof1 = 0x%x\n", ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof1));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof2 = 0x%x\n", ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof2));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof3 = 0x%x\n", ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof3));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof4 = 0x%x\n", ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof4));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga0 = 0x%x\n", ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga0));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga1 = 0x%x\n", ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga1));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga2 = 0x%x\n", ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga2));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga3 = 0x%x\n", ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga3));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga4 = 0x%x\n", ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga4));
	Ddim_Print(("yyw.ee0tonpbd.bit.ee0tonpbd1 = 0x%x\n", ioR2yP1.yyw.ee0tonpbd.bit.ee0tonpbd1));
	Ddim_Print(("yyw.ee0tonpbd.bit.ee0tonpbd2 = 0x%x\n", ioR2yP1.yyw.ee0tonpbd.bit.ee0tonpbd2));
	Ddim_Print(("yyw.ee0tonpbd.bit.ee0tonpbd3 = 0x%x\n", ioR2yP1.yyw.ee0tonpbd.bit.ee0tonpbd3));
	Ddim_Print(("yyw.ee0tonpbd.bit.ee0tonpbd4 = 0x%x\n", ioR2yP1.yyw.ee0tonpbd.bit.ee0tonpbd4));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof0 = 0x%x\n", ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof0));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof1 = 0x%x\n", ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof1));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof2 = 0x%x\n", ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof2));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof3 = 0x%x\n", ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof3));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof4 = 0x%x\n", ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof4));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga0 = 0x%x\n", ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga0));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga1 = 0x%x\n", ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga1));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga2 = 0x%x\n", ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga2));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga3 = 0x%x\n", ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga3));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga4 = 0x%x\n", ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga4));
	Ddim_Print(("yyw.ee0tonmbd.bit.ee0tonmbd1 = 0x%x\n", ioR2yP1.yyw.ee0tonmbd.bit.ee0tonmbd1));
	Ddim_Print(("yyw.ee0tonmbd.bit.ee0tonmbd2 = 0x%x\n", ioR2yP1.yyw.ee0tonmbd.bit.ee0tonmbd2));
	Ddim_Print(("yyw.ee0tonmbd.bit.ee0tonmbd3 = 0x%x\n", ioR2yP1.yyw.ee0tonmbd.bit.ee0tonmbd3));
	Ddim_Print(("yyw.ee0tonmbd.bit.ee0tonmbd4 = 0x%x\n", ioR2yP1.yyw.ee0tonmbd.bit.ee0tonmbd4));
	Ddim_Print(("yyw.ee0clppof.bit.ee0clppof0 = 0x%x\n", ioR2yP1.yyw.ee0clppof.bit.ee0clppof0));
	Ddim_Print(("yyw.ee0clppof.bit.ee0clppof1 = 0x%x\n", ioR2yP1.yyw.ee0clppof.bit.ee0clppof1));
	Ddim_Print(("yyw.ee0clppof.bit.ee0clppof2 = 0x%x\n", ioR2yP1.yyw.ee0clppof.bit.ee0clppof2));
	Ddim_Print(("yyw.ee0clppga.bit.ee0clppga0 = 0x%x\n", ioR2yP1.yyw.ee0clppga.bit.ee0clppga0));
	Ddim_Print(("yyw.ee0clppga.bit.ee0clppga1 = 0x%x\n", ioR2yP1.yyw.ee0clppga.bit.ee0clppga1));
	Ddim_Print(("yyw.ee0clppga.bit.ee0clppga2 = 0x%x\n", ioR2yP1.yyw.ee0clppga.bit.ee0clppga2));
	Ddim_Print(("yyw.ee0clppbd.bit.ee0clppbd1 = 0x%x\n", ioR2yP1.yyw.ee0clppbd.bit.ee0clppbd1));
	Ddim_Print(("yyw.ee0clppbd.bit.ee0clppbd2 = 0x%x\n", ioR2yP1.yyw.ee0clppbd.bit.ee0clppbd2));
	Ddim_Print(("yyw.ee0clpmof.bit.ee0clpmof0 = 0x%x\n", ioR2yP1.yyw.ee0clpmof.bit.ee0clpmof0));
	Ddim_Print(("yyw.ee0clpmof.bit.ee0clpmof1 = 0x%x\n", ioR2yP1.yyw.ee0clpmof.bit.ee0clpmof1));
	Ddim_Print(("yyw.ee0clpmof.bit.ee0clpmof2 = 0x%x\n", ioR2yP1.yyw.ee0clpmof.bit.ee0clpmof2));
	Ddim_Print(("yyw.ee0clpmga.bit.ee0clpmga0 = 0x%x\n", ioR2yP1.yyw.ee0clpmga.bit.ee0clpmga0));
	Ddim_Print(("yyw.ee0clpmga.bit.ee0clpmga1 = 0x%x\n", ioR2yP1.yyw.ee0clpmga.bit.ee0clpmga1));
	Ddim_Print(("yyw.ee0clpmga.bit.ee0clpmga2 = 0x%x\n", ioR2yP1.yyw.ee0clpmga.bit.ee0clpmga2));
	Ddim_Print(("yyw.ee0clpmbd.bit.ee0clpmbd1 = 0x%x\n", ioR2yP1.yyw.ee0clpmbd.bit.ee0clpmbd1));
	Ddim_Print(("yyw.ee0clpmbd.bit.ee0clpmbd2 = 0x%x\n", ioR2yP1.yyw.ee0clpmbd.bit.ee0clpmbd2));
	Ddim_Print(("PIPE2\n"));
	Ddim_Print(("yyw.ee0ctl.bit.ee0en          = 0x%x\n", ioR2yP2.yyw.ee0ctl.bit.ee0en));
	Ddim_Print(("yyw.ee0ctl.bit.ee0tc          = 0x%x\n", ioR2yP2.yyw.ee0ctl.bit.ee0tc));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk0      = 0x%x\n", ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk0));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk1      = 0x%x\n", ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk1));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk2      = 0x%x\n", ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk2));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk3      = 0x%x\n", ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk3));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk4      = 0x%x\n", ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk4));
	Ddim_Print(("yyw.ee0hpfk.bit.ee0hpfk5      = 0x%x\n", ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk5));
	Ddim_Print(("yyw.ee0nrlv.bit.ee0nrlv       = 0x%x\n", ioR2yP2.yyw.ee0nrlv.bit.ee0nrlv));
	Ddim_Print(("yyw.ee0corpof.bit.ee0corpof0 = 0x%x\n", ioR2yP2.yyw.ee0corpof.bit.ee0corpof0));
	Ddim_Print(("yyw.ee0corpof.bit.ee0corpof1 = 0x%x\n", ioR2yP2.yyw.ee0corpof.bit.ee0corpof1));
	Ddim_Print(("yyw.ee0corpof.bit.ee0corpof2 = 0x%x\n", ioR2yP2.yyw.ee0corpof.bit.ee0corpof2));
	Ddim_Print(("yyw.ee0corpof.bit.ee0corpof3 = 0x%x\n", ioR2yP2.yyw.ee0corpof.bit.ee0corpof3));
	Ddim_Print(("yyw.ee0corpga.bit.ee0corpga0 = 0x%x\n", ioR2yP2.yyw.ee0corpga.bit.ee0corpga0));
	Ddim_Print(("yyw.ee0corpga.bit.ee0corpga1 = 0x%x\n", ioR2yP2.yyw.ee0corpga.bit.ee0corpga1));
	Ddim_Print(("yyw.ee0corpga.bit.ee0corpga2 = 0x%x\n", ioR2yP2.yyw.ee0corpga.bit.ee0corpga2));
	Ddim_Print(("yyw.ee0corpga.bit.ee0corpga3 = 0x%x\n", ioR2yP2.yyw.ee0corpga.bit.ee0corpga3));
	Ddim_Print(("yyw.ee0corpbd.bit.ee0corpbd1 = 0x%x\n", ioR2yP2.yyw.ee0corpbd.bit.ee0corpbd1));
	Ddim_Print(("yyw.ee0corpbd.bit.ee0corpbd2 = 0x%x\n", ioR2yP2.yyw.ee0corpbd.bit.ee0corpbd2));
	Ddim_Print(("yyw.ee0corpbd.bit.ee0corpbd3 = 0x%x\n", ioR2yP2.yyw.ee0corpbd.bit.ee0corpbd3));
	Ddim_Print(("yyw.ee0cormof.bit.ee0cormof0 = 0x%x\n", ioR2yP2.yyw.ee0cormof.bit.ee0cormof0));
	Ddim_Print(("yyw.ee0cormof.bit.ee0cormof1 = 0x%x\n", ioR2yP2.yyw.ee0cormof.bit.ee0cormof1));
	Ddim_Print(("yyw.ee0cormof.bit.ee0cormof2 = 0x%x\n", ioR2yP2.yyw.ee0cormof.bit.ee0cormof2));
	Ddim_Print(("yyw.ee0cormof.bit.ee0cormof3 = 0x%x\n", ioR2yP2.yyw.ee0cormof.bit.ee0cormof3));
	Ddim_Print(("yyw.ee0cormga.bit.ee0cormga0 = 0x%x\n", ioR2yP2.yyw.ee0cormga.bit.ee0cormga0));
	Ddim_Print(("yyw.ee0cormga.bit.ee0cormga1 = 0x%x\n", ioR2yP2.yyw.ee0cormga.bit.ee0cormga1));
	Ddim_Print(("yyw.ee0cormga.bit.ee0cormga2 = 0x%x\n", ioR2yP2.yyw.ee0cormga.bit.ee0cormga2));
	Ddim_Print(("yyw.ee0cormga.bit.ee0cormga3 = 0x%x\n", ioR2yP2.yyw.ee0cormga.bit.ee0cormga3));
	Ddim_Print(("yyw.ee0cormbd.bit.ee0cormbd1 = 0x%x\n", ioR2yP2.yyw.ee0cormbd.bit.ee0cormbd1));
	Ddim_Print(("yyw.ee0cormbd.bit.ee0cormbd2 = 0x%x\n", ioR2yP2.yyw.ee0cormbd.bit.ee0cormbd2));
	Ddim_Print(("yyw.ee0cormbd.bit.ee0cormbd3 = 0x%x\n", ioR2yP2.yyw.ee0cormbd.bit.ee0cormbd3));
	Ddim_Print(("yyw.ee0sclsup.bit.ee0sclsup   = 0x%x\n", ioR2yP2.yyw.ee0sclsup.bit.ee0sclsup));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof0 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof0));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof1 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof1));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof2 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof2));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof3 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof3));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof4 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof4));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof5 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof5));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof6 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof6));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof7 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof7));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof8 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof8));
	Ddim_Print(("yyw.ee0sclpof.bit.ee0sclpof9 = 0x%x\n", ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof9));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga0 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga0));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga1 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga1));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga2 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga2));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga3 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga3));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga4 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga4));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga5 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga5));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga6 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga6));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga7 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga7));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga8 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga8));
	Ddim_Print(("yyw.ee0sclpga.bit.ee0sclpga9 = 0x%x\n", ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga9));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd1 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd1));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd2 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd2));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd3 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd3));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd4 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd4));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd5 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd5));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd6 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd6));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd7 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd7));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd8 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd8));
	Ddim_Print(("yyw.ee0sclpbd.bit.ee0sclpbd9 = 0x%x\n", ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd9));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof0 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof0));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof1 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof1));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof2 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof2));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof3 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof3));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof4 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof4));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof5 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof5));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof6 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof6));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof7 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof7));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof8 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof8));
	Ddim_Print(("yyw.ee0sclmof.bit.ee0sclmof9 = 0x%x\n", ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof9));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga0 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga0));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga1 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga1));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga2 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga2));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga3 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga3));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga4 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga4));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga5 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga5));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga6 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga6));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga7 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga7));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga8 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga8));
	Ddim_Print(("yyw.ee0sclmga.bit.ee0sclmga9 = 0x%x\n", ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga9));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd1 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd1));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd2 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd2));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd3 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd3));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd4 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd4));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd5 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd5));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd6 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd6));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd7 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd7));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd8 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd8));
	Ddim_Print(("yyw.ee0sclmbd.bit.ee0sclmbd9 = 0x%x\n", ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd9));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof0 = 0x%x\n", ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof0));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof1 = 0x%x\n", ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof1));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof2 = 0x%x\n", ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof2));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof3 = 0x%x\n", ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof3));
	Ddim_Print(("yyw.ee0tonpof.bit.ee0tonpof4 = 0x%x\n", ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof4));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga0 = 0x%x\n", ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga0));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga1 = 0x%x\n", ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga1));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga2 = 0x%x\n", ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga2));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga3 = 0x%x\n", ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga3));
	Ddim_Print(("yyw.ee0tonpga.bit.ee0tonpga4 = 0x%x\n", ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga4));
	Ddim_Print(("yyw.ee0tonpbd.bit.ee0tonpbd1 = 0x%x\n", ioR2yP2.yyw.ee0tonpbd.bit.ee0tonpbd1));
	Ddim_Print(("yyw.ee0tonpbd.bit.ee0tonpbd2 = 0x%x\n", ioR2yP2.yyw.ee0tonpbd.bit.ee0tonpbd2));
	Ddim_Print(("yyw.ee0tonpbd.bit.ee0tonpbd3 = 0x%x\n", ioR2yP2.yyw.ee0tonpbd.bit.ee0tonpbd3));
	Ddim_Print(("yyw.ee0tonpbd.bit.ee0tonpbd4 = 0x%x\n", ioR2yP2.yyw.ee0tonpbd.bit.ee0tonpbd4));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof0 = 0x%x\n", ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof0));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof1 = 0x%x\n", ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof1));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof2 = 0x%x\n", ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof2));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof3 = 0x%x\n", ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof3));
	Ddim_Print(("yyw.ee0tonmof.bit.ee0tonmof4 = 0x%x\n", ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof4));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga0 = 0x%x\n", ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga0));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga1 = 0x%x\n", ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga1));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga2 = 0x%x\n", ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga2));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga3 = 0x%x\n", ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga3));
	Ddim_Print(("yyw.ee0tonmga.bit.ee0tonmga4 = 0x%x\n", ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga4));
	Ddim_Print(("yyw.ee0tonmbd.bit.ee0tonmbd1 = 0x%x\n", ioR2yP2.yyw.ee0tonmbd.bit.ee0tonmbd1));
	Ddim_Print(("yyw.ee0tonmbd.bit.ee0tonmbd2 = 0x%x\n", ioR2yP2.yyw.ee0tonmbd.bit.ee0tonmbd2));
	Ddim_Print(("yyw.ee0tonmbd.bit.ee0tonmbd3 = 0x%x\n", ioR2yP2.yyw.ee0tonmbd.bit.ee0tonmbd3));
	Ddim_Print(("yyw.ee0tonmbd.bit.ee0tonmbd4 = 0x%x\n", ioR2yP2.yyw.ee0tonmbd.bit.ee0tonmbd4));
	Ddim_Print(("yyw.ee0clppof.bit.ee0clppof0 = 0x%x\n", ioR2yP2.yyw.ee0clppof.bit.ee0clppof0));
	Ddim_Print(("yyw.ee0clppof.bit.ee0clppof1 = 0x%x\n", ioR2yP2.yyw.ee0clppof.bit.ee0clppof1));
	Ddim_Print(("yyw.ee0clppof.bit.ee0clppof2 = 0x%x\n", ioR2yP2.yyw.ee0clppof.bit.ee0clppof2));
	Ddim_Print(("yyw.ee0clppga.bit.ee0clppga0 = 0x%x\n", ioR2yP2.yyw.ee0clppga.bit.ee0clppga0));
	Ddim_Print(("yyw.ee0clppga.bit.ee0clppga1 = 0x%x\n", ioR2yP2.yyw.ee0clppga.bit.ee0clppga1));
	Ddim_Print(("yyw.ee0clppga.bit.ee0clppga2 = 0x%x\n", ioR2yP2.yyw.ee0clppga.bit.ee0clppga2));
	Ddim_Print(("yyw.ee0clppbd.bit.ee0clppbd1 = 0x%x\n", ioR2yP2.yyw.ee0clppbd.bit.ee0clppbd1));
	Ddim_Print(("yyw.ee0clppbd.bit.ee0clppbd2 = 0x%x\n", ioR2yP2.yyw.ee0clppbd.bit.ee0clppbd2));
	Ddim_Print(("yyw.ee0clpmof.bit.ee0clpmof0 = 0x%x\n", ioR2yP2.yyw.ee0clpmof.bit.ee0clpmof0));
	Ddim_Print(("yyw.ee0clpmof.bit.ee0clpmof1 = 0x%x\n", ioR2yP2.yyw.ee0clpmof.bit.ee0clpmof1));
	Ddim_Print(("yyw.ee0clpmof.bit.ee0clpmof2 = 0x%x\n", ioR2yP2.yyw.ee0clpmof.bit.ee0clpmof2));
	Ddim_Print(("yyw.ee0clpmga.bit.ee0clpmga0 = 0x%x\n", ioR2yP2.yyw.ee0clpmga.bit.ee0clpmga0));
	Ddim_Print(("yyw.ee0clpmga.bit.ee0clpmga1 = 0x%x\n", ioR2yP2.yyw.ee0clpmga.bit.ee0clpmga1));
	Ddim_Print(("yyw.ee0clpmga.bit.ee0clpmga2 = 0x%x\n", ioR2yP2.yyw.ee0clpmga.bit.ee0clpmga2));
	Ddim_Print(("yyw.ee0clpmbd.bit.ee0clpmbd1 = 0x%x\n", ioR2yP2.yyw.ee0clpmbd.bit.ee0clpmbd1));
	Ddim_Print(("yyw.ee0clpmbd.bit.ee0clpmbd2 = 0x%x\n", ioR2yP2.yyw.ee0clpmbd.bit.ee0clpmbd2));
	im_r2y_clk_off_pclk(self->imR2yClk,D_IM_R2Y_PIPE12);
}

CtImR2yClassa* ct_im_r2y_classa_new(void)
{
	CtImR2yClassa* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSA, sizeof(CtImR2yClassaPrivate));

	return self;
}

CtImR2yClassa* ct_im_r2y_classa_get(void)
{
	static CtImR2yClassa* self = NULL;

	if(!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSA, sizeof(CtImR2yClassaPrivate));
	}

	return self;
}
