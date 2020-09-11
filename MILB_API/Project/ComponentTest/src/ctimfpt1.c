/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 杨文
*@brief : CtImFpt1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimfpt.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImFpt1, ct_im_fpt1)
#define CT_IM_FPT1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImFpt1Private, CT_TYPE_IM_FPT1))


struct _CtImFpt1Private
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

static TImFptMode1 S_GCT_IM_FPT_CTRL_MODE1[] = {
	[0] = {	// max
		.numFeaturePoint = 127,
		.output = D_IM_FPT_OUT_COORD_AND_FEATURE_AMOUNT,
		.globalWidth = 0x3FF8,
		.width = 640,
		.lines = 640,
		.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_1,
		.windowSize = ImFptCommon_D_IM_FPT_WINDOW_7x7,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MAX,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MAX,
		.imgAddr = 0xFFFFFFF8,
		.inputCoordAddr = 0xFFFFFFF8,
		.outputAddr = 0xFFFFFFF8,
	},
	[1] = {	// min
		.numFeaturePoint = 1,
		.output = ImFptCommon_D_IM_FPT_OUT_COORD_ONLY,
		.globalWidth = 13,
		.width = 13,
		.lines = 13,
		.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_OFF,
		.windowSize = ImFptCommon_D_IM_FPT_WINDOW_5x5,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN,
		.imgAddr = 0,
		.inputCoordAddr = 0,
		.outputAddr = 0,
	},
};

static TImFptMode2 S_GCT_IM_FPT_CTRL_MODE2[] = {
	[0] = {	// max
		.baseglobalwidth = 0x3FF8,
		.targetGlobalWidth = 0x3FF8,
		.numFeaturePoint = 127,
		.usageTargetCoord = ImFptCommon_D_IM_FPT_SAME_AS_BASE_COORD,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MAX,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MAX,
		.lutcfg = ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1,
		.searchWindow = {
			.left = 0x800,
			.right = 0x8FF,
			.top = 0x800,
			.bottom = 0x8FF,
		},
		.trackingThreshold = 0x8FF,
		.numIteration = 10,
		.baseImgAddr = 0xFFFFFFF8,
		.targetImgAddr = 0xFFFFFFF8,
		.baseCoordAddr = 0xFFFFFFF8,
		.targetCoordAddr = 0xFFFFFFF8,
		.trackingResultAddr = 0xFFFFFFF8,
	},
	[1] = {	// min
		.baseglobalwidth = 13,
		.targetGlobalWidth = 13,
		.numFeaturePoint = 1,
		.usageTargetCoord = ImFptCommon_D_IM_FPT_READ_FROM_RAM,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN,
		.lutcfg = ImFptCommon_E_IM_FPT_LUTCFG_OFF,
		.searchWindow = {
			.left = 0,
			.right = 0,
			.top = 0,
			.bottom = 0,
		},
		.trackingThreshold = 0,
		.numIteration = 1,
		.baseImgAddr = 0,
		.targetImgAddr = 0,
		.baseCoordAddr = 0,
		.targetCoordAddr = 0,
		.trackingResultAddr = 0,
	},
};

static TImFptMode3 S_GCT_IM_FPT_CTRL_MODE3[] = {
	[0] = {	// max
		.width = 640,
		.lines = 640,
		.windowSize = ImFptCommon_D_IM_FPT_WINDOW_7x7,
		.outputAddr = 0xFFFFFFF8,
		.baseglobalwidth = 0x3FF8,
		.targetGlobalWidth = 0x3FF8,
		.numFeaturePoint = 127,
		.usageTargetCoord = ImFptCommon_D_IM_FPT_SAME_AS_BASE_COORD,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MAX,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MAX,
		.lutcfg = ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1,
		.searchWindow = {
			.left = 0x800,
			.right = 0x8FF,
			.top = 0x800,
			.bottom = 0x8FF,
		},
		.trackingThreshold = 0x8FF,
		.numIteration = 10,
		.baseImgAddr = 0xFFFFFFF8,
		.targetImgAddr = 0xFFFFFFF8,
		.baseCoordAddr = 0xFFFFFFF8,
		.targetCoordAddr = 0xFFFFFFF8,
		.trackingResultAddr = 0xFFFFFFF8,
	},
	[1] = {	// min
		.width = 13,
		.lines = 13,
		.windowSize = ImFptCommon_D_IM_FPT_WINDOW_5x5,
		.outputAddr = 0,
		.baseglobalwidth = 13,
		.targetGlobalWidth = 13,
		.numFeaturePoint = 1,
		.usageTargetCoord = ImFptCommon_D_IM_FPT_READ_FROM_RAM,
		.downSampleX = ImFptCommon_D_IM_FPT_DS_MIN,
		.downSampleY = ImFptCommon_D_IM_FPT_DS_MIN,
		.lutcfg = ImFptCommon_E_IM_FPT_LUTCFG_OFF,
		.searchWindow = {
			.left = 0,
			.right = 0,
			.top = 0,
			.bottom = 0,
		},
		.trackingThreshold = 0,
		.numIteration = 1,
		.baseImgAddr = 0,
		.targetImgAddr = 0,
		.baseCoordAddr = 0,
		.targetCoordAddr = 0,
		.trackingResultAddr = 0,
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


/**
 * IMPL
 */
static void ct_im_fpt1_constructor(CtImFpt1 *self)
{
	CtImFpt1Private *priv = CT_IM_FPT1_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_fpt1_destructor(CtImFpt1 *self)
{
	CtImFpt1Private *priv = CT_IM_FPT1_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_1: "
INT32 ct_im_fpt1_1_1( UCHAR ch )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

	ercd = Im_FPT_Init( ch );
#ifdef CO_MSG_PRINT_ON
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#endif

	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL0    = 0x%lx\n", ch, IO_FPT[ch].FPTCTL0.word ));
	Ddim_Print(( "IO_FPT[%d].FPTAXICTL0 = 0x%lx\n", ch, IO_FPT[ch].FPTAXICTL0.word ));
	ct_im_fpt_off_pclk( ch );

	return ercd;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_2: "
INT32 ct_im_fpt1_1_2( UCHAR ch )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[0] );
#endif
	ct_im_fpt_print_mode0_reg( ch );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[1] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode0( ch, &S_GCT_IM_FPT_CTRL_MODE0[1] );
#endif
	ct_im_fpt_print_mode0_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_3: "
INT32 ct_im_fpt1_1_3( UCHAR ch )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode1( ch, &S_GCT_IM_FPT_CTRL_MODE1[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode1( ch, &S_GCT_IM_FPT_CTRL_MODE1[0] );
#endif
	ct_im_fpt_print_mode1_reg( ch );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode1( ch, &S_GCT_IM_FPT_CTRL_MODE1[1] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode1( ch, &S_GCT_IM_FPT_CTRL_MODE1[1] );
#endif
	ct_im_fpt_print_mode1_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_4: "
INT32 ct_im_fpt1_1_4( UCHAR ch )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode2( ch, &S_GCT_IM_FPT_CTRL_MODE2[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode2( ch, &S_GCT_IM_FPT_CTRL_MODE2[0] );
#endif
	ct_im_fpt_print_mode2_reg( ch );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode2( ch, &S_GCT_IM_FPT_CTRL_MODE2[1] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode2( ch, &S_GCT_IM_FPT_CTRL_MODE2[1] );
#endif
	ct_im_fpt_print_mode2_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_5: "
INT32 ct_im_fpt1_1_5( UCHAR ch )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode3( ch, &S_GCT_IM_FPT_CTRL_MODE3[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode3( ch, &S_GCT_IM_FPT_CTRL_MODE3[0] );
#endif
	ct_im_fpt_print_mode3_reg( ch );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode3( ch, &S_GCT_IM_FPT_CTRL_MODE3[1] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode3( ch, &S_GCT_IM_FPT_CTRL_MODE3[1] );
#endif
	ct_im_fpt_print_mode3_reg( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_6: "
INT32 ct_im_fpt1_1_6( UCHAR ch )
{
	TImFptModeConfig param[2] = {
		{
			// max
			.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER,
			.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_ENABLE,
			.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_DEBUG,
		},
		{
			// min
			.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_SDRAM,
			.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE,
			.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &param[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode_Config( ch, &param[0] );
#endif
	Ddim_Print(( "\n" ));
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL2 = 0x%lx\n", ch, IO_FPT[ch].FPTCTL2.word ));
	ct_im_fpt_off_pclk( ch );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &param[1] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode_Config( ch, &param[1] );
#endif
	Ddim_Print(( "\n" ));
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL2 = 0x%lx\n", ch, IO_FPT[ch].FPTCTL2.word ));
	ct_im_fpt_off_pclk( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_7: "
INT32 ct_im_fpt1_1_7( UCHAR ch )
{
	TImFptBrcConfig param[2] = {
		{
			// max
			.img_offset = 0xFF,
			.img_clip_max = 0xFF,
			.img_clip_min = 0xFF,
		},
		{
			// min
			.img_offset = -0x100,
			.img_clip_max = 0,
			.img_clip_min = 0,
		},
	};
	TImFptMode0 ctrl_param = S_GCT_IM_FPT_CTRL_BASE_MODE0;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

	ctrl_param.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_0;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode0( ch, &ctrl_param );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));

	ercd = Im_FPT_Ctrl_BRC_Config_Base_Img( ch, &param[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode0( ch, &ctrl_param );
	Im_FPT_Ctrl_BRC_Config_Base_Img( ch, &param[0] );
#endif

	Ddim_Print(( "\n" ));
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL4 = 0x%lx\n", ch, IO_FPT[ch].FPTCTL4.word ));
	ct_im_fpt_off_pclk( ch );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_BRC_Config_Base_Img( ch, &param[1] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_BRC_Config_Base_Img( ch, &param[1] );
#endif
	Ddim_Print(( "\n" ));
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL4 = 0x%lx\n", ch, IO_FPT[ch].FPTCTL4.word ));
	ct_im_fpt_off_pclk( ch );

	ctrl_param.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_OFF;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode0( ch, &ctrl_param );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode0( ch, &ctrl_param );
#endif

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_BRC_Config_Base_Img( ch, &param[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_BRC_Config_Base_Img( ch, &param[0] );
#endif
	Ddim_Print(( "\n" ));
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL4 = 0x%lx\n", ch, IO_FPT[ch].FPTCTL4.word ));
	ct_im_fpt_off_pclk( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_8: "
INT32 ct_im_fpt1_1_8( UCHAR ch )
{
	TImFptBrcConfig param[2] = {
		{
			// max
			.img_offset = 0xFF,
			.img_clip_max = 0xFF,
			.img_clip_min = 0xFF,
		},
		{
			// min
			.img_offset = -0x100,
			.img_clip_max = 0,
			.img_clip_min = 0,
		},
	};
	TImFptMode0 ctrl_param = S_GCT_IM_FPT_CTRL_BASE_MODE0;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

	ctrl_param.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_0;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode0( ch, &ctrl_param );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));

	ercd = Im_FPT_Ctrl_BRC_Config_Target_Img( ch, &param[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode0( ch, &ctrl_param );
	Im_FPT_Ctrl_BRC_Config_Target_Img( ch, &param[0] );
#endif
	Ddim_Print(( "\n" ));
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL5 = 0x%lx\n", ch, IO_FPT[ch].FPTCTL5.word ));
	ct_im_fpt_off_pclk( ch );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_BRC_Config_Target_Img( ch, &param[1] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_BRC_Config_Target_Img( ch, &param[1] );
#endif
	Ddim_Print(( "\n" ));
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL5 = 0x%lx\n", ch, IO_FPT[ch].FPTCTL5.word ));
	ct_im_fpt_off_pclk( ch );

	ctrl_param.lutsel = ImFptCommon_E_IM_FPT_LUTSEL_OFF;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode0( ch, &ctrl_param );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));

	ercd = Im_FPT_Ctrl_BRC_Config_Target_Img( ch, &param[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode0( ch, &ctrl_param );
	Im_FPT_Ctrl_BRC_Config_Target_Img( ch, &param[0] );
#endif
	Ddim_Print(( "\n" ));
	ct_im_fpt_on_pclk( ch );
	Ddim_Print(( "IO_FPT[%d].FPTCTL5 = 0x%lx\n", ch, IO_FPT[ch].FPTCTL5.word ));
	ct_im_fpt_off_pclk( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_9: "
INT32 ct_im_fpt1_1_9( UCHAR ch )
{
	UCHAR lut[256];
	USHORT loop;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );

	for( loop = 0; loop < 256; loop++ ) {
		lut[loop] = loop;
	}

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_LUTRAM( ch, 0, &lut[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_LUTRAM( ch, 0, &lut[0] );
#endif

	Ddim_Print(( "\n" ));
	ct_im_fpt_on_hclk( ch );
	for( loop = 0; loop < 256 / 4; loop++ ) {
		Ddim_Print(( "IO_FPT_AHB[%d].FPTLUT0 = 0x%lx\n", ch, IO_FPT_AHB[ch].FPTLUT0.word[loop] ));
	}
	ct_im_fpt_off_hclk( ch );


	for( loop = 0; loop < 256; loop++ ) {
		lut[loop] = 255 - loop;
	}

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_LUTRAM( ch, 1, &lut[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_LUTRAM( ch, 1, &lut[0] );
#endif

	Ddim_Print(( "\n" ));
	ct_im_fpt_on_hclk( ch );
	for( loop = 0; loop < 256 / 4; loop++ ) {
		Ddim_Print(( "IO_FPT_AHB[%d].FPTLUT1 = 0x%lx\n", ch, IO_FPT_AHB[ch].FPTLUT1.word[loop] ));
	}
	ct_im_fpt_off_hclk( ch );

	Im_FPT_Close( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_10: "
INT32 ct_im_fpt1_1_10( UCHAR ch )
{
	USHORT reg[256];
	USHORT loop;
	TImFptModeConfig param;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );

	param.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	param.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	param.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &param );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode_Config( ch, &param );
#endif

	for( loop = 0; loop < 256; loop+=2 ) {
		reg[loop]   = loop;
		reg[loop+1] = loop + 1;
	}

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Set_REGRAM( ch, 0, (UCHAR*)&reg[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Set_REGRAM( ch, 0, (UCHAR*)&reg[0] );
#endif

	Ddim_Print(( "\n" ));
	ct_im_fpt_on_hclk( ch );
	for( loop = 0; loop < 512 / 4; loop++ ) {
		Ddim_Print(( "IO_FPT_AHB[%d].FPTREG0 = 0x%lx\n", ch, IO_FPT_AHB[ch].FPTREG0.word[loop] ));
	}
	ct_im_fpt_off_hclk( ch );


	for( loop = 0; loop < 256; loop+=2 ) {
		reg[loop]   = 65535 - loop;
		reg[loop+1] = 65535 - loop - 1;
	}

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Set_REGRAM( ch, 1, (UCHAR*)&reg[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Set_REGRAM( ch, 1, (UCHAR*)&reg[0] );
#endif

	Ddim_Print(( "\n" ));
	ct_im_fpt_on_hclk( ch );
	for( loop = 0; loop < 512 / 4; loop++ ) {
		Ddim_Print(( "IO_FPT_AHB[%d].FPTREG1 = 0x%lx\n", ch, IO_FPT_AHB[ch].FPTREG1.word[loop] ));
	}
	ct_im_fpt_off_hclk( ch );

	Im_FPT_Close( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_11: "
INT32 ct_im_fpt1_1_11( UCHAR ch )
{
	USHORT reg[256];
	ULONG getReg[128];
	USHORT loop;
	TImFptModeConfig param;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );

	param.imIoMode = ImFptCommon_E_IM_FPT_IO_MODE_REGISTER;
	param.imPipeEn = ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE;
	param.imDebugMode = ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL;
#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Ctrl_Mode_Config( ch, &param );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Ctrl_Mode_Config( ch, &param );
#endif

	for( loop = 0; loop < 256; loop+=2 ) {
		reg[loop]   = loop;
		reg[loop+1] = loop + 1;
	}

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Set_REGRAM( ch, 0, (UCHAR*)&reg[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));

	ercd = Im_FPT_Get_REGRAM( ch, 0, &getReg[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Set_REGRAM( ch, 0, (UCHAR*)&reg[0] );
	Im_FPT_Get_REGRAM( ch, 0, &getReg[0] );
#endif

	Ddim_Print(( "\n" ));
	for( loop = 0; loop < 128; loop++ ) {
		Ddim_Print(( "getReg[%d] = 0x%lx\n", loop, getReg[loop] ));
	}


	for( loop = 0; loop < 256; loop+=2 ) {
		reg[loop]   = 65535 - loop;
		reg[loop+1] = 65535 - loop - 1;
	}

#ifdef CO_MSG_PRINT_ON
	ercd = Im_FPT_Set_REGRAM( ch, 1, (UCHAR*)&reg[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));

	ercd = Im_FPT_Get_REGRAM( ch, 1, &getReg[0] );
	Ddim_Print(( CtImFpt1_ID_IM_FPT_FUNC_NAME "%d\n", ercd ));
#else
	Im_FPT_Set_REGRAM( ch, 1, (UCHAR*)&reg[0] );
	Im_FPT_Get_REGRAM( ch, 1, &getReg[0] );
#endif

	Ddim_Print(( "\n" ));
	for( loop = 0; loop < 128; loop++ ) {
		Ddim_Print(( "getReg[%d] = 0x%lx\n", loop, getReg[loop] ));
	}

	Im_FPT_Close( ch );

	return D_DDIM_OK;
}

#undef CtImFpt1_ID_IM_FPT_FUNC_NAME
#define CtImFpt1_ID_IM_FPT_FUNC_NAME "ct_im_fpt1_1_12: "
INT32 ct_im_fpt1_1_12( UCHAR ch )
{
	Ddim_Print(( "%s\n", CtImFpt1_ID_IM_FPT_FUNC_NAME ));

	Im_FPT_Open( ch, 100 );

	Im_FPT_DebugDump_All_Registers( ch, 0x60000000, 0x68000000 );

	Im_FPT_Close( ch );

	return D_DDIM_OK;
}

INT32 ct_im_fpt1_run_1( UCHAR ch, const UINT32 ctNo2nd )
{
	switch( ctNo2nd ) {
		// Test-1-1-1
		case 1:
			return ct_im_fpt1_1_1( ch );

		// Test-1-1-2
		case 2:
			return ct_im_fpt1_1_2( ch );

		// Test-1-1-3
		case 3:
			return ct_im_fpt1_1_3( ch );

		// Test-1-1-4
		case 4:
			return ct_im_fpt1_1_4( ch );

		// Test-1-1-5
		case 5:
			return ct_im_fpt1_1_5( ch );

		// Test-1-1-6
		case 6:
			return ct_im_fpt1_1_6( ch );

		// Test-1-1-7
		case 7:
			return ct_im_fpt1_1_7( ch );

		// Test-1-1-8
		case 8:
			return ct_im_fpt1_1_8( ch );

		// Test-1-1-9
		case 9:
			return ct_im_fpt1_1_9( ch );

		// Test-1-1-10
		case 10:
			return ct_im_fpt1_1_10( ch );

		// Test-1-1-11
		case 11:
			return ct_im_fpt1_1_11( ch );

		// Test-1-1-12
		case 12:
			return ct_im_fpt1_1_12( ch );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}

CtImFpt1* ct_im_fpt1_new(void)
{
	CtImFpt1* self = k_object_new_with_private(CT_TYPE_IM_FPT1, sizeof(CtImFpt1Private));

	return self;
}

CtImFpt1* ct_im_fpt1_get(void)
{
	static CtImFpt1* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_FPT1, sizeof(CtImFpt1Private));
	}

	return self;
}
