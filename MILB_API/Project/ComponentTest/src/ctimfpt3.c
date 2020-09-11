/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 杨文
*@brief : CtImFpt3
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimfpt.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImFpt3, ct_im_fpt3)
#define CT_IM_FPT3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImFpt3Private, CT_TYPE_IM_FPT3))


struct _CtImFpt3Private
{
	int a;
};


static UCHAR S_GCT_IM_FPT_LUT_TBL[2][256] = {
	{
		  1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,
		 17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,
		 33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
		 49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,
		 65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,
		 81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,
		 97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
		113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
		129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
		145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
		161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
		177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192,
		193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
		209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
		225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240,
		241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,   0,
	},
	{
		255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240,
		239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224,
		223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208,
		207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192,
		191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176,
		175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160,
		159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144,
		143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128,
		127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112,
		111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,  96,
		 95,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,  80,
		 79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,  64,
		 63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,  48,
		 47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,  32,
		 31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,
		 15,  14,  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,   2,   1,   0,
	},
};

// TestBase table
static TImFptMode0 S_GCT_IM_FPT_CTRL_BASE_MODE0 = {
	.globalWidth = 200,
	.width = 200,
	.lines = 150,
	.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_0,
	.windowSize = ImFptCommon_D_IM_FPT_WINDOW_5x5,
	.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN,
	.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN,
	.imgAddr = 0x60000000,
	.featureAmountAddr = 0x68000000,
	.featureAmountLineByte = 200 * 2,
	.histgramAddr = 0x70000000,
};

static TImFptMode1 S_GCT_IM_FPT_CTRL_BASE_MODE1 = {
	.numFeaturePoint = 100,
	.output = ImFptCommon_D_IM_FPT_OUT_COORD_ONLY,
	.globalWidth = 200,
	.width = 13,
	.lines = 13,
	.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_OFF,
	.windowSize = ImFptCommon_D_IM_FPT_WINDOW_5x5,
	.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN,
	.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN,
	.imgAddr = 0x60000000,
	.inputCoordAddr = 0x68000000,
	.outputAddr = 0x70000000,
};

static TImFptMode2 S_GCT_IM_FPT_CTRL_BASE_MODE2 = {
	.baseglobalwidth = 200,
	.targetGlobalWidth = 200,
	.numFeaturePoint = 100,
	.usageTargetCoord = ImFptCommon_D_IM_FPT_SAME_AS_BASE_COORD,
	.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN,
	.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN,
	.lutcfg = ImFptCommon_E_IM_FPT_LUTCFG_BASE_1__TARGET_0,
	.searchWindow = {
		.left = 0x600,
		.right = 0x600,
		.top = 0x600,
		.bottom = 0x600,
	},
	.trackingThreshold = 0x19,
	.numIteration = 10,
	.baseImgAddr = 0x60000000,
	.targetImgAddr = 0x64000000,
	.baseCoordAddr = 0x68000000,
	.targetCoordAddr = 0x6C000000,
	.trackingResultAddr = 0x70000000,
};

static TImFptMode3 S_GCT_IM_FPT_CTRL_BASE_MODE3 = {
		.width = 13,
		.lines = 13,
		.windowSize = ImFptCommon_D_IM_FPT_WINDOW_5x5,
		.outputAddr = 0x74000000,
		.baseglobalwidth = 200,
		.targetGlobalWidth = 200,
		.numFeaturePoint = 100,
		.usageTargetCoord = ImFptCommon_D_IM_FPT_SAME_AS_BASE_COORD,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN,
		.lutcfg = ImFptCommon_E_IM_FPT_LUTCFG_BASE_1__TARGET_0,
		.searchWindow = {
			.left = 0x600,
			.right = 0x600,
			.top = 0x600,
			.bottom = 0x600,
		},
		.trackingThreshold = 0x19,
		.numIteration = 10,
		.baseImgAddr = 0x60000000,
		.targetImgAddr = 0x64000000,
		.baseCoordAddr = 0x68000000,
		.targetCoordAddr = 0x6C000000,
		.trackingResultAddr = 0x70000000,
};


/**
 * IMPL
 */
static void ct_im_fpt3_constructor(CtImFpt3 *self)
{
	CtImFpt3Private *priv = CT_IM_FPT3_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_fpt3_destructor(CtImFpt3 *self)
{
	CtImFpt3Private *priv = CT_IM_FPT3_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_1: "
INT32 ct_im_fpt3_4_1( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Init( ch );

	ct_im_fpt_print_all_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_2: "
INT32 ct_im_fpt3_4_2( UCHAR ch )
{
	INT32 ercd;
	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	Im_FPT_Close( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_3: "
INT32 ct_im_fpt3_4_3( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );

	return Im_FPT_Close( ch );
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_4: "
INT32 ct_im_fpt3_4_4( UCHAR ch )
{
	INT32 ercd;
	UINT32 status;
	TImFptInterrupt param;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE0 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = 	( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &S_GCT_IM_FPT_LUT_TBL[0][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode0_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_5: "
INT32 ct_im_fpt3_4_5( UCHAR ch )
{
	INT32 ercd;
	USHORT loop;
	UINT32 status;
	ULONG getReg[128];
	TImFptInterrupt param;
	TImFptModeConfig config;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &config );

	ercd = Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE0 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &S_GCT_IM_FPT_LUT_TBL[0][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Get_REGRAM( ch, 1, &getReg[0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "get regram error = %d\n", ercd ));
	}
	Ddim_Print(( "\n" ));
	for( loop = 0; loop < 128; loop++ ) {
		Ddim_Print(( "getReg[%d] = 0x%lx\n", loop, getReg[loop] ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode0_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_6: "
INT32 ct_im_fpt3_4_6( UCHAR ch )
{
	INT32 ercd;
	UINT32 status;
	TImFptInterrupt param;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_Mode1( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE1 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode1_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_7: "
INT32 ct_im_fpt3_4_7( UCHAR ch )
{
	INT32 ercd;
	USHORT loop;
	UINT32 status;
	UCHAR* reg = (UCHAR*)0x68000000;
	ULONG getReg[128];
	TImFptInterrupt param;
	TImFptModeConfig config;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &config );

	ercd = Im_FPT_Ctrl_Mode1( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE1 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Set_REGRAM( ch, 0, (UCHAR*)&reg[0] );

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Get_REGRAM( ch, 1, &getReg[0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "get regram error = %d\n", ercd ));
	}
	Ddim_Print(( "\n" ));
	for( loop = 0; loop < 128; loop++ ) {
		Ddim_Print(( "getReg[%d] = 0x%lx\n", loop, getReg[loop] ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode1_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_8: "
INT32 ct_im_fpt3_4_8( UCHAR ch )
{
	INT32 ercd;
	UINT32 status;
	TImFptInterrupt param;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_Mode2( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE2 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &S_GCT_IM_FPT_LUT_TBL[1][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut0 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 1, &S_GCT_IM_FPT_LUT_TBL[0][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut1 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode2_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_9: "
INT32 ct_im_fpt3_4_9( UCHAR ch )
{
	INT32 ercd;
	USHORT loop;
	UINT32 status;
	UCHAR* reg = (UCHAR*)0x68000000;
	ULONG getReg[128];
	TImFptInterrupt param;
	TImFptModeConfig config;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &config );

	ercd = Im_FPT_Ctrl_Mode2( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE2 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Set_REGRAM( ch, 0, (UCHAR*)&reg[0] );

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &S_GCT_IM_FPT_LUT_TBL[1][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut0 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 1, &S_GCT_IM_FPT_LUT_TBL[0][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut1 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Get_REGRAM( ch, 1, &getReg[0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "get regram error = %d\n", ercd ));
	}
	Ddim_Print(( "\n" ));
	for( loop = 0; loop < 128; loop++ ) {
		Ddim_Print(( "getReg[%d] = 0x%lx\n", loop, getReg[loop] ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode2_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_10: "
INT32 ct_im_fpt3_4_10( UCHAR ch )
{
	INT32 ercd;
	UINT32 status;
	TImFptInterrupt param;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_Mode3( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE3 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &S_GCT_IM_FPT_LUT_TBL[1][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut0 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 1, &S_GCT_IM_FPT_LUT_TBL[0][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut1 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode3_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_11: "
INT32 ct_im_fpt3_4_11( UCHAR ch )
{
	INT32 ercd;
	USHORT loop;
	UINT32 status;
	UCHAR* reg = (UCHAR*)0x68000000;
	ULONG getReg[128];
	TImFptInterrupt param;
	TImFptModeConfig config;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &config );

	ercd = Im_FPT_Ctrl_Mode3( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE3 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Set_REGRAM( ch, 0, (UCHAR*)&reg[0] );

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &S_GCT_IM_FPT_LUT_TBL[1][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut0 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 1, &S_GCT_IM_FPT_LUT_TBL[0][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut1 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Get_REGRAM( ch, 1, &getReg[0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "get regram error = %d\n", ercd ));
	}
	Ddim_Print(( "\n" ));
	for( loop = 0; loop < 128; loop++ ) {
		Ddim_Print(( "getReg[%d] = 0x%lx\n", loop, getReg[loop] ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode3_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_12: "
INT32 ct_im_fpt3_4_12( UCHAR ch )
{
	INT32 ercd;
	UINT32 status;
	TImFptInterrupt param;
	TImFptModeConfig config;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_SDRAM;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_ENABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &config );

	ercd = Im_FPT_Ctrl_Mode2( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE2 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &S_GCT_IM_FPT_LUT_TBL[1][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut0 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 1, &S_GCT_IM_FPT_LUT_TBL[0][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut1 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode2_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_13: "
INT32 ct_im_fpt3_4_13( UCHAR ch )
{
	INT32 ercd;
	UINT32 status;
	TImFptInterrupt param;
	TImFptModeConfig config;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_SDRAM;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_DEBUG;
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &config );

	ercd = Im_FPT_Ctrl_Mode3( ch, &S_GCT_IM_FPT_CTRL_BASE_MODE3 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &S_GCT_IM_FPT_LUT_TBL[1][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut0 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Ctrl_LUTRAM( ch, 1, &S_GCT_IM_FPT_LUT_TBL[0][0] );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl lut1 error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode3_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt3_ID_IM_FPT_FUNC_NAME
#define CtImFpt3_ID_IM_FPT_FUNC_NAME "ct_im_fpt3_4_14: "
INT32 ct_im_fpt3_4_14( UCHAR ch )
{
	INT32 ercd;
	UINT32 status;
	TImFptInterrupt param;
	TImFptMode2 mode2_ctrl = S_GCT_IM_FPT_CTRL_BASE_MODE2;

	Ddim_Print(( "%s\n", CtImFpt3_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "open error = %d\n", ercd ));
	}

	mode2_ctrl.lutcfg = ImFptCommon_E_IM_FPT_LUTCFG_OFF;
	ercd = Im_FPT_Ctrl_Mode2( ch, &mode2_ctrl );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl mode error = %d\n", ercd ));
	}

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = ct_im_fpt_handler;
	ercd = Im_FPT_Ctrl_Interrupt( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "ctrl interrupt error = %d\n", ercd ));
	}

	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "start error = %d\n", ercd ));
	}

#ifdef CO_DEBUG_ON_PC
	IO_FPT[ch].FPTINTF0.bit.__FPTFLG = 1;
	im_fpt_int_handler( ch );
#endif

	ercd = Im_FPT_WaitEnd( ch, &status, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "wait end error = %d\n", ercd ));
	}

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt3_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "close error = %d\n", ercd ));
	}

	ct_im_fpt_print_mode2_reg( ch );

	return D_DDIM_OK;
}

INT32 ct_im_fpt3_run_4( UCHAR ch, const UINT32 ctNo2nd )
{
	switch( ctNo2nd ) {
		// Test-1-4-1
		case 1:
			return ct_im_fpt3_4_1( ch );

		// Test-1-4-2
		case 2:
			return ct_im_fpt3_4_2( ch );

		// Test-1-4-3
		case 3:
			return ct_im_fpt3_4_3( ch );

		// Test-1-4-4
		case 4:
			return ct_im_fpt3_4_4( ch );

		// Test-1-4-5
		case 5:
			return ct_im_fpt3_4_5( ch );

		// Test-1-4-6
		case 6:
			return ct_im_fpt3_4_6( ch );

		// Test-1-4-7
		case 7:
			return ct_im_fpt3_4_7( ch );

		// Test-1-4-8
		case 8:
			return ct_im_fpt3_4_8( ch );

		// Test-1-4-9
		case 9:
			return ct_im_fpt3_4_9( ch );

		// Test-1-4-10
		case 10:
			return ct_im_fpt3_4_10( ch );

		// Test-1-4-11
		case 11:
			return ct_im_fpt3_4_11( ch );

		// Test-1-4-12
		case 12:
			return ct_im_fpt3_4_12( ch );

		// Test-1-4-13
		case 13:
			return ct_im_fpt3_4_13( ch );

		// Test-1-4-14
		case 14:
			return ct_im_fpt3_4_14( ch );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}

CtImFpt3* ct_im_fpt3_new(void)
{
	CtImFpt3* self = k_object_new_with_private(CT_TYPE_IM_FPT3, sizeof(CtImFpt3Private));

	return self;
}