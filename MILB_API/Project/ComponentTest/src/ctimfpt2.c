/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 杨文
*@brief : CtImFpt2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimfpt.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImFpt2, ct_im_fpt2)
#define CT_IM_FPT2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImFpt2Private, CT_TYPE_IM_FPT2))


struct _CtImFpt2Private
{
	int a;
};


// Max/Min table
static TImFptMode0 S_GCT_IM_FPT_CTRL_MODE0[] = {
	[0] = {	// max
		.globalWidth = 0x3FF8,
		.width = 4480,
		.lines = 3000,
		.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_1,
		.windowSize = ImFptCommon_D_IM_FPT_WINDOW_7x7,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MAX,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MAX,
		.imgAddr = 0xFFFFFFF8,
		.featureAmountAddr = 0xFFFFFFF8,
		.featureAmountLineByte = 0x3FF8,
		.histgramAddr = 0xFFFFFFF8,
	},
	[1] = {	// min
		.globalWidth = 13,
		.width = 13,
		.lines = 13,
		.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_OFF,
		.windowSize = ImFptCommon_D_IM_FPT_WINDOW_5x5,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN,
		.imgAddr = 0,
		.featureAmountAddr = 0,
		.featureAmountLineByte = 0,
		.histgramAddr = 0,
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
static void ct_im_fpt2_constructor(CtImFpt2 *self)
{
	CtImFpt2Private *priv = CT_IM_FPT2_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_fpt2_destructor(CtImFpt2 *self)
{
	CtImFpt2Private *priv = CT_IM_FPT2_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_1: "
INT32 ct_im_fpt2_2_1( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );
	Im_FPT_Init( ch );
	Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[0] );
	Im_FPT_Start( ch );
	ercd = Im_FPT_Init( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Init error = 0x%x\n", ercd ));
	}
	Im_FPT_Stop( ch );
	Im_FPT_Close( ch );

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_2: "
INT32 ct_im_fpt2_2_2( UCHAR ch )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Open0 error = 0x%x\n", ercd ));
		return ercd;
	}

	ercd = Im_FPT_Open( ch, 100 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Open1 error = 0x%x\n", ercd ));
		Im_FPT_Close( ch );
		return ercd;
	}

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Close error = 0x%x\n", ercd ));
		return ercd;
	}

	return D_DDIM_OK;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_3: "
INT32 ct_im_fpt2_2_3( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );
	Im_FPT_Init( ch );
	Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[0] );
	Im_FPT_Start( ch );
	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Close error = 0x%x\n", ercd ));
	}
	Im_FPT_Stop( ch );
	Im_FPT_Close( ch );

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_4: "
INT32 ct_im_fpt2_2_4( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;
	DDIM_USER_ID sidBack;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	sidBack = SID_IM_FPT( ch );
	SID_IM_FPT( ch ) = 0xfff;

	ercd = Im_FPT_Close( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Close error = 0x%x\n", ercd ));
	}

	SID_IM_FPT( ch ) = sidBack;

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_5: "
INT32 ct_im_fpt2_2_5( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;
	UCHAR lut[256];

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );
	Im_FPT_Init( ch );
	Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[0] );
	Im_FPT_Start( ch );
	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, lut );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Ctrl_LUTRAM error = 0x%x\n", ercd ));
	}
	Im_FPT_Stop( ch );
	Im_FPT_Close( ch );

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_6: "
INT32 ct_im_fpt2_2_6( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;
	UCHAR reg[512];

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );
	Im_FPT_Init( ch );
	Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[0] );
	Im_FPT_Start( ch );
	ercd = Im_FPT_Set_REGRAM( ch, 0, reg );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Set_REGRAM error = 0x%x\n", ercd ));
	}
	Im_FPT_Stop( ch );
	Im_FPT_Close( ch );

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_7: "
INT32 ct_im_fpt2_2_7( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;
	UCHAR reg[512];
	TImFptModeConfig param;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_SDRAM;
	param.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	param.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;

	Im_FPT_Open( ch, 100 );
	Im_FPT_Init( ch );
	Im_FPT_Ctrl_Mode_Config( ch, &param );
	ercd = Im_FPT_Set_REGRAM( ch, 0, reg );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Set_REGRAM error = 0x%x\n", ercd ));
	}
	Im_FPT_Stop( ch );
	Im_FPT_Close( ch );

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_8: "
INT32 ct_im_fpt2_2_8( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;
	ULONG reg[128];

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );
	Im_FPT_Init( ch );
	Im_FPT_Start( ch );
	ercd = Im_FPT_Get_REGRAM( ch, 0, reg );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Get_REGRAM error = 0x%x\n", ercd ));
	}
	Im_FPT_Stop( ch );
	Im_FPT_Close( ch );

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_9: "
INT32 ct_im_fpt2_2_9( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;
	ULONG reg[128];
	TImFptModeConfig param;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_SDRAM;
	param.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	param.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;

	Im_FPT_Open( ch, 100 );
	Im_FPT_Init( ch );
	Im_FPT_Ctrl_Mode_Config( ch, &param );
	ercd = Im_FPT_Get_REGRAM( ch, 0, reg );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Get_REGRAM error = 0x%x\n", ercd ));
	}
	Im_FPT_Stop( ch );
	Im_FPT_Close( ch );

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_10: "
INT32 ct_im_fpt2_2_10( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );
	Im_FPT_Init( ch );
	Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[0] );
	Im_FPT_Start( ch );
	ercd = Im_FPT_Start( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Start error = 0x%x\n", ercd ));
	}
	Im_FPT_Stop( ch );
	Im_FPT_Close( ch );

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_11: "
INT32 ct_im_fpt2_2_11( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Stop( ch );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Stop error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_2_12: "
INT32 ct_im_fpt2_2_12( UCHAR ch )
{
	INT32 ercd = D_DDIM_OK;
	UINT32 status;
	TImFptInterrupt param;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.flag = (ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | 
				  ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR);
	param.callback = NULL;
	Im_FPT_Ctrl_Interrupt( ch, &param );

	ercd = Im_FPT_WaitEnd( ch, &status, 10 );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( CtImFpt2_ID_IM_FPT_FUNC_NAME "Wait end error = 0x%x\n", ercd ));
	}

	return ercd;
}

INT32 ct_im_fpt2_run_2( UCHAR ch, const UINT32 ctNo2nd )
{
	switch( ctNo2nd ) {
		// Test-1-2-1
		case 1:
			return ct_im_fpt2_2_1( ch );

		// Test-1-2-2
		case 2:
			return ct_im_fpt2_2_2( ch );

		// Test-1-2-3
		case 3:
			return ct_im_fpt2_2_3( ch );

		// Test-1-2-4
		case 4:
			return ct_im_fpt2_2_4( ch );

		// Test-1-2-5
		case 5:
			return ct_im_fpt2_2_5( ch );

		// Test-1-2-6
		case 6:
			return ct_im_fpt2_2_6( ch );

		// Test-1-2-7
		case 7:
			return ct_im_fpt2_2_7( ch );

		// Test-1-2-8
		case 8:
			return ct_im_fpt2_2_8( ch );

		// Test-1-2-9
		case 9:
			return ct_im_fpt2_2_9( ch );

		// Test-1-2-10
		case 10:
			return ct_im_fpt2_2_10( ch );

		// Test-1-2-11
		case 11:
			return ct_im_fpt2_2_11( ch );

		// Test-1-2-12
		case 12:
			return ct_im_fpt2_2_12( ch );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_1: "
INT32 ct_im_fpt2_3_1( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Open( ch, -2 );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_2: "
INT32 ct_im_fpt2_3_2( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_Mode0( ch, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_3: "
INT32 ct_im_fpt2_3_3( UCHAR ch )
{
	INT32 ercd;
	TImFptMode0 param = S_GCT_IM_FPT_CTRL_BASE_MODE0;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN - 1;
	ercd = Im_FPT_Ctrl_Mode0( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	param.downSampleX = ImFptCommon_D_IM_FPT_DS_MAX + 1;
	ercd = Im_FPT_Ctrl_Mode0( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	return D_DDIM_OK;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_4: "
INT32 ct_im_fpt2_3_4( UCHAR ch )
{
	INT32 ercd;
	TImFptMode0 param = S_GCT_IM_FPT_CTRL_BASE_MODE0;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN - 1;
	ercd = Im_FPT_Ctrl_Mode0( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	param.downSampleY = ImFptCommon_D_IM_FPT_DS_MAX + 1;
	ercd = Im_FPT_Ctrl_Mode0( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	return D_DDIM_OK;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_5: "
INT32 ct_im_fpt2_3_5( UCHAR ch )
{
	TImFptMode0 param = S_GCT_IM_FPT_CTRL_BASE_MODE0;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.lutsel = 3;
	return Im_FPT_Ctrl_Mode0( ch, &param );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_6: "
INT32 ct_im_fpt2_3_6( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_Mode1( ch, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_7: "
INT32 ct_im_fpt2_3_7( UCHAR ch )
{
	INT32 ercd;
	TImFptMode1 param = S_GCT_IM_FPT_CTRL_BASE_MODE1;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN - 1;
	ercd = Im_FPT_Ctrl_Mode1( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	param.downSampleX = ImFptCommon_D_IM_FPT_DS_MAX + 1;
	ercd = Im_FPT_Ctrl_Mode1( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	return D_DDIM_OK;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_8: "
INT32 ct_im_fpt2_3_8( UCHAR ch )
{
	INT32 ercd;
	TImFptMode1 param = S_GCT_IM_FPT_CTRL_BASE_MODE1;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN - 1;
	ercd = Im_FPT_Ctrl_Mode1( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	param.downSampleY = ImFptCommon_D_IM_FPT_DS_MAX + 1;
	ercd = Im_FPT_Ctrl_Mode1( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	return D_DDIM_OK;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_9: "
INT32 ct_im_fpt2_3_9( UCHAR ch )
{
	TImFptMode1 param = S_GCT_IM_FPT_CTRL_BASE_MODE1;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.lutsel = 3;
	return Im_FPT_Ctrl_Mode1( ch, &param );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_10: "
INT32 ct_im_fpt2_3_10( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_Mode2( ch, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_11: "
INT32 ct_im_fpt2_3_11( UCHAR ch )
{
	TImFptMode2 param = S_GCT_IM_FPT_CTRL_BASE_MODE2;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.lutcfg = 5;
	return Im_FPT_Ctrl_Mode2( ch, &param );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_12: "
INT32 ct_im_fpt2_3_12( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_Mode3( ch, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_13: "
INT32 ct_im_fpt2_3_13( UCHAR ch )
{
	INT32 ercd;
	TImFptMode3 param = S_GCT_IM_FPT_CTRL_BASE_MODE3;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN - 1;
	ercd = Im_FPT_Ctrl_Mode3( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	param.downSampleX = ImFptCommon_D_IM_FPT_DS_MAX + 1;
	ercd = Im_FPT_Ctrl_Mode3( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	return D_DDIM_OK;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_14: "
INT32 ct_im_fpt2_3_14( UCHAR ch )
{
	INT32 ercd;
	TImFptMode3 param = S_GCT_IM_FPT_CTRL_BASE_MODE3;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN - 1;
	ercd = Im_FPT_Ctrl_Mode3( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	param.downSampleY = ImFptCommon_D_IM_FPT_DS_MAX + 1;
	ercd = Im_FPT_Ctrl_Mode3( ch, &param );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	return D_DDIM_OK;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_15: "
INT32 ct_im_fpt2_3_15( UCHAR ch )
{
	TImFptMode3 param = S_GCT_IM_FPT_CTRL_BASE_MODE3;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.lutcfg = 5;
	return Im_FPT_Ctrl_Mode3( ch, &param );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_16: "
INT32 ct_im_fpt2_3_16( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_Mode_Config( ch, NULL );;
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_17: "
INT32 ct_im_fpt2_3_17( UCHAR ch )
{
	TImFptModeConfig param;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.imIoMode = 2;
	param.imPipeEn = 0;
	param.imDebugMode = 0;

	return Im_FPT_Ctrl_Mode_Config( ch, &param );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_18: "
INT32 ct_im_fpt2_3_18( UCHAR ch )
{
	TImFptModeConfig param;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.imIoMode = 0;
	param.imPipeEn = 2;
	param.imDebugMode = 0;

	return Im_FPT_Ctrl_Mode_Config( ch, &param );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_19: "
INT32 ct_im_fpt2_3_19( UCHAR ch )
{
	TImFptModeConfig param;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	param.imIoMode = 0;
	param.imPipeEn = 0;
	param.imDebugMode = 2;

	return Im_FPT_Ctrl_Mode_Config( ch, &param );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_20: "
INT32 ct_im_fpt2_3_20( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_BRC_Config_Base_Img( ch, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_21: "
INT32 ct_im_fpt2_3_21( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_BRC_Config_Target_Img( ch, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_22: "
INT32 ct_im_fpt2_3_22( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_Interrupt( ch, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_23: "
INT32 ct_im_fpt2_3_23( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_LUTRAM( ch, 0, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_24: "
INT32 ct_im_fpt2_3_24( UCHAR ch )
{
	UCHAR lut[256];

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_Ctrl_LUTRAM( ch, 2, lut );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_25: "
INT32 ct_im_fpt2_3_25( UCHAR ch )
{
	TImFptModeConfig config;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	Im_FPT_Ctrl_Mode_Config( ch, &config );

	return Im_FPT_Set_REGRAM( ch, 0, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_26: "
INT32 ct_im_fpt2_3_26( UCHAR ch )
{
	TImFptModeConfig config;
	UCHAR reg[512];

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	Im_FPT_Ctrl_Mode_Config( ch, &config );

	return Im_FPT_Set_REGRAM( ch, 2, reg );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_27: "
INT32 ct_im_fpt2_3_27( UCHAR ch )
{
	TImFptModeConfig config;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	Im_FPT_Ctrl_Mode_Config( ch, &config );

	return Im_FPT_Get_REGRAM( ch, 0, NULL );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_28: "
INT32 ct_im_fpt2_3_28( UCHAR ch )
{
	TImFptModeConfig config;
	ULONG reg[128];

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	config.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	config.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	config.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
	Im_FPT_Ctrl_Mode_Config( ch, &config );

	return Im_FPT_Get_REGRAM( ch, 2, reg );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_29: "
INT32 ct_im_fpt2_3_29( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_WaitEnd( ch, NULL, 100 );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_30: "
INT32 ct_im_fpt2_3_30( UCHAR ch )
{
	UINT32 status;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	return Im_FPT_WaitEnd( ch, &status, -2 );
}

#undef CtImFpt2_ID_IM_FPT_FUNC_NAME
#define CtImFpt2_ID_IM_FPT_FUNC_NAME "ct_im_fpt2_3_31: "
INT32 ct_im_fpt2_3_31( UCHAR ch )
{
	INT32 ercd;
	UCHAR buf;

	Ddim_Print(( "%s\n", CtImFpt2_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Get_Axi_Response( ch, &buf, NULL );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	ercd = Im_FPT_Get_Axi_Response( ch, NULL, &buf );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "result = %d\n", ercd ));
	}

	return D_DDIM_OK;
}

INT32 ct_im_fpt2_run_3( UCHAR ch, const UINT32 ctNo2nd )
{
	switch( ctNo2nd ) {
		// Test-1-3-1
		case 1:
			return ct_im_fpt2_3_1( ch );

		// Test-1-3-2
		case 2:
			return ct_im_fpt2_3_2( ch );

		// Test-1-3-3
		case 3:
			return ct_im_fpt2_3_3( ch );

		// Test-1-3-4
		case 4:
			return ct_im_fpt2_3_4( ch );

		// Test-1-3-5
		case 5:
			return ct_im_fpt2_3_5( ch );

		// Test-1-3-6
		case 6:
			return ct_im_fpt2_3_6( ch );

		// Test-1-3-7
		case 7:
			return ct_im_fpt2_3_7( ch );

		// Test-1-3-8
		case 8:
			return ct_im_fpt2_3_8( ch );

		// Test-1-3-9
		case 9:
			return ct_im_fpt2_3_9( ch );

		// Test-1-3-10
		case 10:
			return ct_im_fpt2_3_10( ch );

		// Test-1-3-11
		case 11:
			return ct_im_fpt2_3_11( ch );

		// Test-1-3-12
		case 12:
			return ct_im_fpt2_3_12( ch );

		// Test-1-3-13
		case 13:
			return ct_im_fpt2_3_13( ch );

		// Test-1-3-14
		case 14:
			return ct_im_fpt2_3_14( ch );

		// Test-1-3-15
		case 15:
			return ct_im_fpt2_3_15( ch );

		// Test-1-3-16
		case 16:
			return ct_im_fpt2_3_16( ch );

		// Test-1-3-17
		case 17:
			return ct_im_fpt2_3_17( ch );

		// Test-1-3-18
		case 18:
			return ct_im_fpt2_3_18( ch );

		// Test-1-3-19
		case 19:
			return ct_im_fpt2_3_19( ch );

		// Test-1-3-20
		case 20:
			return ct_im_fpt2_3_20( ch );

		// Test-1-3-21
		case 21:
			return ct_im_fpt2_3_21( ch );

		// Test-1-3-22
		case 22:
			return ct_im_fpt2_3_22( ch );

		// Test-1-3-23
		case 23:
			return ct_im_fpt2_3_23( ch );

		// Test-1-3-24
		case 24:
			return ct_im_fpt2_3_24( ch );

		// Test-1-3-25
		case 25:
			return ct_im_fpt2_3_25( ch );

		// Test-1-3-26
		case 26:
			return ct_im_fpt2_3_26( ch );

		// Test-1-3-27
		case 27:
			return ct_im_fpt2_3_27( ch );

		// Test-1-3-28
		case 28:
			return ct_im_fpt2_3_28( ch );

		// Test-1-3-29
		case 29:
			return ct_im_fpt2_3_29( ch );

		// Test-1-3-30
		case 30:
			return ct_im_fpt2_3_30( ch );

		// Test-1-3-31
		case 31:
			return ct_im_fpt2_3_31( ch );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

CtImFpt2* ct_im_fpt2_new(void)
{
	CtImFpt2* self = k_object_new_with_private(CT_TYPE_IM_FPT2, sizeof(CtImFpt2Private));

	return self;
}