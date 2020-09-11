/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2y
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

/**
 * @file		ct_im_r2y.c
 * @brief		R2Y ct code
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "ctimr2y.h"
#include "ctimr2ytool.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y, ct_im_r2y)
#define CT_IM_R2Y_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yPrivate, CT_TYPE_IM_R2Y))


struct _CtImR2yPrivate
{

};

ULONG gctImR2yInAddr = 0x54000000;
ULONG gctImR2yOutAddr[2] = {
	0x55000000,
	0x56000000,
};


// Max/Min table
TImR2yCtrl gctImR2yCtrl[] = {
	[0] = {	// max
		.yyw[D_IM_R2Y_YYW_CH_0] = {
			.axiWriteMode = {
				.masterIfSelect = 0x3F,
				.burstLength = 2,
				.outEnable[D_IM_R2Y_PORT_0] = 1,
				.outEnable[D_IM_R2Y_PORT_1] = 1,
				.outEnable[D_IM_R2Y_PORT_2] = 1,
			},
			.writeRequestMask[D_IM_R2Y_PORT_0] = 0xFFF,
			.writeRequestMask[D_IM_R2Y_PORT_1] = 0xFFF,
			.writeRequestMask[D_IM_R2Y_PORT_2] = 0xFFF,
			.resizeMode = 1,
			.pixelAvgReductionMode = 2,
			.pixelAvgReductionEnable = 1,
			.yccCcThinSelect = 0xF,
			.trimOutEnable = 1,
			.planarInterleavedMode = 1,
		},

		.yyw[D_IM_R2Y_YYW_CH_1] = {
			.axiWriteMode = {
				.masterIfSelect = 0x3F,
				.burstLength = 2,
				.outEnable[D_IM_R2Y_PORT_0] = 1,
				.outEnable[D_IM_R2Y_PORT_1] = 1,
				.outEnable[D_IM_R2Y_PORT_2] = 1,
			},
			.writeRequestMask[D_IM_R2Y_PORT_0] = 0xFFF,
			.writeRequestMask[D_IM_R2Y_PORT_1] = 0xFFF,
			.writeRequestMask[D_IM_R2Y_PORT_2] = 0xFFF,
			.resizeMode = 1,
			.pixelAvgReductionMode = 2,
			.pixelAvgReductionEnable = 1,
			.yccCcThinSelect = 0xF,
			.trimOutEnable = 1,
			.planarInterleavedMode = 1,
		},

		.yyw[D_IM_R2Y_YYW_CH_2] = {
			.axiWriteMode = {
				.masterIfSelect = 3,
				.burstLength = 2,
				.outEnable[D_IM_R2Y_PORT_0] = 1,			// dummy
				.outEnable[D_IM_R2Y_PORT_1] = 1,			// dummy
				.outEnable[D_IM_R2Y_PORT_2] = 1,			// dummy
			},
			.writeRequestMask[D_IM_R2Y_PORT_0] = 0xFFF,
			.writeRequestMask[D_IM_R2Y_PORT_1] = 0xFFF,	// dummy
			.writeRequestMask[D_IM_R2Y_PORT_2] = 0xFFF,	// dummy
			.resizeMode = 1,								// dummy
			.pixelAvgReductionMode = 2,
			.pixelAvgReductionEnable = 1,
			.yccCcThinSelect = 0xF,						// dummy
			.trimOutEnable = 1,
			.planarInterleavedMode = 1,					// dummy
		},

		.yyw[D_IM_R2Y_YYW_CH_0A] = {
			.axiWriteMode = {
				.masterIfSelect = 0xF,
				.burstLength = 2,
				.outEnable[D_IM_R2Y_PORT_0] = 1,
				.outEnable[D_IM_R2Y_PORT_1] = 1,
				.outEnable[D_IM_R2Y_PORT_2] = 1,			// dummy
			},
			.writeRequestMask[D_IM_R2Y_PORT_0] = 0xFFF,
			.writeRequestMask[D_IM_R2Y_PORT_1] = 0xFFF,
			.writeRequestMask[D_IM_R2Y_PORT_2] = 0xFFF,	// dummy
			.resizeMode = 1,								// dummy
			.pixelAvgReductionMode = 2,					// dummy
			.pixelAvgReductionEnable = 1,				// dummy
			.yccCcThinSelect = 0xF,						// dummy
			.trimOutEnable = 1,							// dummy
			.planarInterleavedMode = 1,					// dummy
		},

		.lineIntr[D_IM_R2Y_LINE_INT_0] = {
			.level = 0x3FF8,
			.yywSelect = 1,
		},
		.lineIntr[D_IM_R2Y_LINE_INT_1] = {
			.level = 0x3FF8,
			.yywSelect = 1,
		},
		.lineIntr[D_IM_R2Y_LINE_INT_2] = {
			.level = 0x3FF8,
			.yywSelect = 1,
		},

		.yywEnable[D_IM_R2Y_YYW_CH_0] = 1,
		.yywEnable[D_IM_R2Y_YYW_CH_1] = 1,
		.yywEnable[D_IM_R2Y_YYW_CH_2] = 1,
		.lineTransferCycle = 0x3FFF,
		.yywContinueStartEnable = 1,
		.yywHorizontalFlip = 1,
		.videoFormatOutSelect0 = 1,
		.ipuMacroOutputEnable = 1,
		.ipuMacroTrimmingEnable = 1,
		.cnrMacroOutputEnable = 1,
		.cnrMacroTrimmingEnable = 1,
		.outputMode0a = 3,
		.videoFormatOutSelect0a = 1,
		.outputFormatSel1 = 1,
		.outputTypeSel1 = 3,
		.ycfBypass = 1,
		.ycfPadding = 1,
		.mccSelect = 1,
		.mccBitShift = 1,
	},
	[1] = {	// min
		.yyw[D_IM_R2Y_YYW_CH_0] = {
			.axiWriteMode = {
				.masterIfSelect = 0,
				.burstLength = 0,
				.outEnable[D_IM_R2Y_PORT_0] = 0,
				.outEnable[D_IM_R2Y_PORT_1] = 0,
				.outEnable[D_IM_R2Y_PORT_2] = 0,
			},
			.writeRequestMask[D_IM_R2Y_PORT_0] = 0,
			.writeRequestMask[D_IM_R2Y_PORT_1] = 0,
			.writeRequestMask[D_IM_R2Y_PORT_2] = 0,
			.resizeMode = 0,
			.pixelAvgReductionMode = 0,
			.pixelAvgReductionEnable = 0,
			.yccCcThinSelect = 0,
			.trimOutEnable = 0,
			.planarInterleavedMode = 0,
		},

		.yyw[D_IM_R2Y_YYW_CH_1] = {
			.axiWriteMode = {
				.masterIfSelect = 0,
				.burstLength = 0,
				.outEnable[D_IM_R2Y_PORT_0] = 0,
				.outEnable[D_IM_R2Y_PORT_1] = 0,
				.outEnable[D_IM_R2Y_PORT_2] = 0,
			},
			.writeRequestMask[D_IM_R2Y_PORT_0] = 0,
			.writeRequestMask[D_IM_R2Y_PORT_1] = 0,
			.writeRequestMask[D_IM_R2Y_PORT_2] = 0,
			.resizeMode = 0,
			.pixelAvgReductionMode = 0,
			.pixelAvgReductionEnable = 0,
			.yccCcThinSelect = 0,
			.trimOutEnable = 0,
			.planarInterleavedMode = 0,
		},

		.yyw[D_IM_R2Y_YYW_CH_2] = {
			.axiWriteMode = {
				.masterIfSelect = 0,
				.burstLength = 0,
				.outEnable[D_IM_R2Y_PORT_0] = 0,			// dummy
				.outEnable[D_IM_R2Y_PORT_1] = 0,			// dummy
				.outEnable[D_IM_R2Y_PORT_2] = 0,			// dummy
			},
			.writeRequestMask[D_IM_R2Y_PORT_0] = 0,
			.writeRequestMask[D_IM_R2Y_PORT_1] = 0,		// dummy
			.writeRequestMask[D_IM_R2Y_PORT_2] = 0,		// dummy
			.resizeMode = 0,								// dummy
			.pixelAvgReductionMode = 0,
			.pixelAvgReductionEnable = 0,
			.yccCcThinSelect = 0,						// dummy
			.trimOutEnable = 0,
			.planarInterleavedMode = 0,					// dummy
		},

		.yyw[D_IM_R2Y_YYW_CH_0A] = {
			.axiWriteMode = {
				.masterIfSelect = 0,
				.burstLength = 0,
				.outEnable[D_IM_R2Y_PORT_0] = 0,
				.outEnable[D_IM_R2Y_PORT_1] = 0,
				.outEnable[D_IM_R2Y_PORT_2] = 0,			// dummy
			},
			.writeRequestMask[D_IM_R2Y_PORT_0] = 0,
			.writeRequestMask[D_IM_R2Y_PORT_1] = 0,
			.writeRequestMask[D_IM_R2Y_PORT_2] = 0,		// dummy
			.resizeMode = 0,								// dummy
			.pixelAvgReductionMode = 0,					// dummy
			.pixelAvgReductionEnable = 0,				// dummy
			.yccCcThinSelect = 0,						// dummy
			.trimOutEnable = 0,							// dummy
			.planarInterleavedMode = 0,					// dummy
		},

		.lineIntr[D_IM_R2Y_LINE_INT_0] = {
			.level = 0,
			.yywSelect = 0,
		},
		.lineIntr[D_IM_R2Y_LINE_INT_1] = {
			.level = 0,
			.yywSelect = 0,
		},
		.lineIntr[D_IM_R2Y_LINE_INT_2] = {
			.level = 0,
			.yywSelect = 0,
		},

		.yywEnable[D_IM_R2Y_YYW_CH_0] = 0,
		.yywEnable[D_IM_R2Y_YYW_CH_1] = 0,
		.yywEnable[D_IM_R2Y_YYW_CH_2] = 0,
		.lineTransferCycle = 0,
		.yywContinueStartEnable = 0,
		.yywHorizontalFlip = 0,
		.videoFormatOutSelect0 = 0,
		.ipuMacroOutputEnable = 0,
		.ipuMacroTrimmingEnable = 0,
		.cnrMacroOutputEnable = 0,
		.cnrMacroTrimmingEnable = 0,
		.outputMode0a = 0,
		.videoFormatOutSelect0a = 0,
		.outputFormatSel1 = 0,
		.outputTypeSel1 = 0,
		.ycfBypass = 0,
		.ycfPadding = 0,
		.mccSelect = 0,
		.mccBitShift = 0,
	},
};
// Max/Min table
TImR2yCtrlSdramInput gctImR2yCtrlSdramIn[] = {
	[0] = {	// max
		.burstLength = 2,
		.readRequestMask[D_IM_R2Y_PORT_0] = 0xFFF,
		.readRequestMask[D_IM_R2Y_PORT_1] = 0xFFF,
		.readRequestMask[D_IM_R2Y_PORT_2] = 0xFFF,
		.inputDtype = 3,
		.monoEbable = 1,
		.rgbDekneeEnable = 1,
		.rgbLeftShift = 3,
		.rgbSaturationMode = 1,
		.topOffset[D_IM_R2Y_PORT_0] = 7,
		.topOffset[D_IM_R2Y_PORT_1] = 7,
		.topOffset[D_IM_R2Y_PORT_2] = 7,
		.inputGlobal = 0xFFF0,
	},
	[1] = {	// min
		.burstLength = 0,
		.readRequestMask[D_IM_R2Y_PORT_0] = 0,
		.readRequestMask[D_IM_R2Y_PORT_1] = 0,
		.readRequestMask[D_IM_R2Y_PORT_2] = 0,
		.inputDtype = 0,
		.monoEbable = 0,
		.rgbDekneeEnable = 0,
		.rgbLeftShift = 0,
		.rgbSaturationMode = 0,
		.topOffset[D_IM_R2Y_PORT_0] = 0,
		.topOffset[D_IM_R2Y_PORT_1] = 0,
		.topOffset[D_IM_R2Y_PORT_2] = 0,
		.inputGlobal = 0,
	},
};

// TestBase table
TImR2yCtrl gctImR2yCtrlBase = {
	.yyw[D_IM_R2Y_YYW_CH_0] = {
		.axiWriteMode = {
			.masterIfSelect = D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2,
			.burstLength = D_IM_R2Y_BRST_512,
			.outEnable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_ON,
			.outEnable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_ON,
			.outEnable[D_IM_R2Y_PORT_2] = D_IM_R2Y_ENABLE_ON,
		},
		.writeRequestMask[D_IM_R2Y_PORT_0] = 0,
		.writeRequestMask[D_IM_R2Y_PORT_1] = 0,
		.writeRequestMask[D_IM_R2Y_PORT_2] = 0,
		.resizeMode = D_IM_R2Y_RSZ_BILINEAR,
		.pixelAvgReductionMode = D_IM_R2Y_RDC_MODE_DIV_2,
		.pixelAvgReductionEnable = D_IM_R2Y_ENABLE_OFF,
		.yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC422_CENTER,
		.trimOutEnable = D_IM_R2Y_ENABLE_OFF,
		.planarInterleavedMode = D_IM_R2Y_PORT_INTERLEAVED,
	},

	.yyw[D_IM_R2Y_YYW_CH_1] = {
		.axiWriteMode = {
			.masterIfSelect = D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2,
			.burstLength = D_IM_R2Y_BRST_512,
			.outEnable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_ON,
			.outEnable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_ON,
			.outEnable[D_IM_R2Y_PORT_2] = D_IM_R2Y_ENABLE_ON,
		},
		.writeRequestMask[D_IM_R2Y_PORT_0] = 0,
		.writeRequestMask[D_IM_R2Y_PORT_1] = 0,
		.writeRequestMask[D_IM_R2Y_PORT_2] = 0,
		.resizeMode = D_IM_R2Y_RSZ_BILINEAR,
		.pixelAvgReductionMode = D_IM_R2Y_RDC_MODE_DIV_2,
		.pixelAvgReductionEnable = D_IM_R2Y_ENABLE_OFF,
		.yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC422_CENTER,
		.trimOutEnable = D_IM_R2Y_ENABLE_OFF,
		.planarInterleavedMode = D_IM_R2Y_PORT_INTERLEAVED,
	},

	.yyw[D_IM_R2Y_YYW_CH_2] = {
		.axiWriteMode = {
			.masterIfSelect = D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2,
			.burstLength = D_IM_R2Y_BRST_512,
			.outEnable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_ON,			// dummy
			.outEnable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_ON,			// dummy
			.outEnable[D_IM_R2Y_PORT_2] = D_IM_R2Y_ENABLE_ON,			// dummy
		},
		.writeRequestMask[D_IM_R2Y_PORT_0] = 0,
		.writeRequestMask[D_IM_R2Y_PORT_1] = 0,						// dummy
		.writeRequestMask[D_IM_R2Y_PORT_2] = 0,						// dummy
		.resizeMode = D_IM_R2Y_RSZ_BILINEAR,							// dummy
		.pixelAvgReductionMode = D_IM_R2Y_RDC_MODE_DIV_2,
		.pixelAvgReductionEnable = D_IM_R2Y_ENABLE_OFF,
		.yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC422_CENTER,			// dummy
		.trimOutEnable = D_IM_R2Y_ENABLE_OFF,
		.planarInterleavedMode = D_IM_R2Y_PORT_PLANAR,				// dummy
	},

	.yyw[D_IM_R2Y_YYW_CH_0A] = {
		.axiWriteMode = {
			.masterIfSelect = D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2,
			.burstLength = D_IM_R2Y_BRST_512,
			.outEnable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_ON,
			.outEnable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_ON,
			.outEnable[D_IM_R2Y_PORT_2] = D_IM_R2Y_ENABLE_ON,			// dummy
		},
		.writeRequestMask[D_IM_R2Y_PORT_0] = 0,
		.writeRequestMask[D_IM_R2Y_PORT_1] = 0,
		.writeRequestMask[D_IM_R2Y_PORT_2] = 0,						// dummy
		.resizeMode = D_IM_R2Y_RSZ_BILINEAR,							// dummy
		.pixelAvgReductionMode = D_IM_R2Y_RDC_MODE_DIV_2,			// dummy
		.pixelAvgReductionEnable = D_IM_R2Y_ENABLE_OFF,				// dummy
		.yccCcThinSelect = D_IM_R2Y_THIN_OUT_YCC422_CENTER,			// dummy
		.trimOutEnable = D_IM_R2Y_ENABLE_OFF,							// dummy
		.planarInterleavedMode = D_IM_R2Y_PORT_PLANAR,				// dummy
	},

	.lineIntr[D_IM_R2Y_LINE_INT_0] = {
		.level = 0,
		.yywSelect = D_IM_R2Y_YYW_CH_0,
	},
	.lineIntr[D_IM_R2Y_LINE_INT_1] = {
		.level = 0,
		.yywSelect = D_IM_R2Y_YYW_CH_0,
	},
	.lineIntr[D_IM_R2Y_LINE_INT_2] = {
		.level = 0,
		.yywSelect = D_IM_R2Y_YYW_CH_0,
	},

	.yywEnable[D_IM_R2Y_YYW_CH_0] = D_IM_R2Y_ENABLE_ON,
	.yywEnable[D_IM_R2Y_YYW_CH_1] = D_IM_R2Y_ENABLE_ON,
	.yywEnable[D_IM_R2Y_YYW_CH_2] = D_IM_R2Y_ENABLE_ON,
	.lineTransferCycle = 0,
	.yywContinueStartEnable = D_IM_R2Y_ENABLE_OFF,
	.yywHorizontalFlip = D_IM_R2Y_ENABLE_OFF,
	.videoFormatOutSelect0 = D_IM_R2Y_VFM_NORMAL,
	.ipuMacroOutputEnable = D_IM_R2Y_ENABLE_OFF,
	.ipuMacroTrimmingEnable = D_IM_R2Y_ENABLE_OFF,
	.cnrMacroOutputEnable = D_IM_R2Y_ENABLE_OFF,
	.cnrMacroTrimmingEnable = D_IM_R2Y_ENABLE_OFF,
	.outputMode0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP,
	.videoFormatOutSelect0a = D_IM_R2Y_VFM_NORMAL,
	.outputFormatSel1 = D_IM_R2Y_DATA_FORMAT_8,
	.outputTypeSel1 = D_IM_R2Y_WRITE_DTYP_PACK8,
	.ycfBypass = D_IM_R2Y_ENABLE_OFF,
	.ycfPadding = D_IM_R2Y_ENABLE_ON,
	.mccSelect = D_IM_R2Y_MCC_AFTER_CC0,
	.mccBitShift = D_IM_R2Y_ENABLE_OFF,
	.r2yUserHandler = ct_im_r2y_handler,
	.userParam = 0,
};
// TestBase table
TImR2yCtrlSdramInput gct_im_r2y_ctrl_sdram_in_base = {
	.burstLength = D_IM_R2Y_BRST_512,
	.readRequestMask[D_IM_R2Y_PORT_0] = 0,
	.readRequestMask[D_IM_R2Y_PORT_1] = 0,
	.readRequestMask[D_IM_R2Y_PORT_2] = 0,
	.inputDtype = D_IM_R2Y_READ_DTYP_PACK16,
	.monoEbable = D_IM_R2Y_ENABLE_OFF,
	.rgbDekneeEnable = D_IM_R2Y_ENABLE_OFF,
	.rgbLeftShift = D_IM_R2Y_STL_RGB_LEFT_SHIFT_NONE,
	.rgbSaturationMode = D_IM_R2Y_ENABLE_OFF,
	.topOffset[D_IM_R2Y_PORT_0] = 0,
	.topOffset[D_IM_R2Y_PORT_1] = 0,
	.topOffset[D_IM_R2Y_PORT_2] = 0,
	.inputGlobal = 1920 * 2,
};

// TImR2yCtrlSdramInput table for RGB 8bit input
TImR2yCtrlSdramInput gctImR2yCtrlSdramInRgb8bit = {
	.burstLength = D_IM_R2Y_BRST_512,
	.readRequestMask[D_IM_R2Y_PORT_0] = 0,
	.readRequestMask[D_IM_R2Y_PORT_1] = 0,
	.readRequestMask[D_IM_R2Y_PORT_2] = 0,
	.inputDtype = D_IM_R2Y_READ_DTYP_PACK8,
	.monoEbable = D_IM_R2Y_ENABLE_OFF,
	.rgbDekneeEnable = D_IM_R2Y_ENABLE_ON,
	.rgbLeftShift = D_IM_R2Y_STL_RGB_LEFT_SHIFT_NONE,
	.rgbSaturationMode = D_IM_R2Y_ENABLE_OFF,
	.topOffset[D_IM_R2Y_PORT_0] = 0,
	.topOffset[D_IM_R2Y_PORT_1] = 0,
	.topOffset[D_IM_R2Y_PORT_2] = 0,
	.inputGlobal = D_IM_R2Y_SRC_IMG_GLOBAL_WIDTH_RGB_U8,
};

// TImR2yCtrlSdramInput table for RGB 12bit input
TImR2yCtrlSdramInput gctImR2yCtrlSdramInRgb12bit = {
	.burstLength = D_IM_R2Y_BRST_512,
	.readRequestMask[D_IM_R2Y_PORT_0] = 0,
	.readRequestMask[D_IM_R2Y_PORT_1] = 0,
	.readRequestMask[D_IM_R2Y_PORT_2] = 0,
	.inputDtype = D_IM_R2Y_READ_DTYP_PACK12,
	.monoEbable = D_IM_R2Y_ENABLE_OFF,
	.rgbDekneeEnable = D_IM_R2Y_ENABLE_OFF,
	.rgbLeftShift = D_IM_R2Y_STL_RGB_LEFT_SHIFT_NONE,
	.rgbSaturationMode = D_IM_R2Y_ENABLE_OFF,
	.topOffset[D_IM_R2Y_PORT_0] = 0,
	.topOffset[D_IM_R2Y_PORT_1] = 0,
	.topOffset[D_IM_R2Y_PORT_2] = 0,
	.inputGlobal = D_IM_R2Y_SRC_IMG_GLOBAL_WIDTH_RGB_P12,
};

// TImR2yCtrlSdramInput table for RGB 16bit input
TImR2yCtrlSdramInput gctImR2yCtrlSdramInRgb16bit = {
	.burstLength = D_IM_R2Y_BRST_512,
	.readRequestMask[D_IM_R2Y_PORT_0] = 0,
	.readRequestMask[D_IM_R2Y_PORT_1] = 0,
	.readRequestMask[D_IM_R2Y_PORT_2] = 0,
	.inputDtype = D_IM_R2Y_READ_DTYP_PACK16,
	.monoEbable = D_IM_R2Y_ENABLE_OFF,
	.rgbDekneeEnable = D_IM_R2Y_ENABLE_OFF,
	.rgbLeftShift = D_IM_R2Y_STL_RGB_LEFT_SHIFT_NONE,
	.rgbSaturationMode = D_IM_R2Y_ENABLE_OFF,
	.topOffset[D_IM_R2Y_PORT_0] = 0,
	.topOffset[D_IM_R2Y_PORT_1] = 0,
	.topOffset[D_IM_R2Y_PORT_2] = 0,
	.inputGlobal = D_IM_R2Y_SRC_IMG_GLOBAL_WIDTH_RGB_U16,
};

// TImR2yResizeRect table for YCC444 output
TImR2yResizeRect gctImR2yResizeRectParamOutYcc444 = {
	.inputSize.imgLeft = 0,
	.inputSize.imgTop = 0,
	.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH,
	.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES,
	.outputSize[D_IM_R2Y_YYW_CH_0] = {
		.yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH,
		.yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC444_Y,
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC444_C,
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,		// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_1] = {
		.yywWidth = 320,
		.yywLines = 240,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC444_Y,
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC444_C,
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,		// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_2] = {
		.yywWidth = 160,
		.yywLines = 120,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC444_Y,
		.outputGlobalW[D_IM_R2Y_PORT_1] = 0,		// dummy
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,		// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_0A] = {
		.yywWidth = 0,								// dummy
		.yywLines = 0,								// dummy
		.outputGlobalW[D_IM_R2Y_PORT_Y] = 0,		// dummy
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = 0,	// dummy
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,		// dummy
	},
};

// TImR2yResizeRect table for YCC422 output
TImR2yResizeRect gctImR2yResizeRectParamOutYcc422 = {
	.inputSize.imgLeft = 0,
	.inputSize.imgTop = 0,
	.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH,
	.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES,
	.outputSize[D_IM_R2Y_YYW_CH_0] = {
		.yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH,
		.yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y,
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C,
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,	// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_1] = {
		.yywWidth = 320,
		.yywLines = 240,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y,
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C,
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,	// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_2] = {
		.yywWidth = 160,
		.yywLines = 120,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y,
		.outputGlobalW[D_IM_R2Y_PORT_1] = 0,	// dummy
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,	// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_0A] = {
		.yywWidth = 0,							// dummy
		.yywLines = 0,							// dummy
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y,
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C,
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,	// dummy
	},
};

// TImR2yResizeRect table for YCC420 output
TImR2yResizeRect gctImR2yResizeRectParamOutYcc420 = {
	.inputSize.imgLeft = 0,
	.inputSize.imgTop = 0,
	.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH,
	.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES,
	.outputSize[D_IM_R2Y_YYW_CH_0] = {
		.yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH,
		.yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC420_Y,
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC420_C_SP,
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,	// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_1] = {
		.yywWidth = 320,
		.yywLines = 240,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC420_Y,
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC420_C_SP,
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,	// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_2] = {
		.yywWidth = 160,
		.yywLines = 120,
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC420_Y,
		.outputGlobalW[D_IM_R2Y_PORT_1] = 0,	// dummy
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,	// dummy
	},
	.outputSize[D_IM_R2Y_YYW_CH_0A] = {
		.yywWidth = 0,							// dummy
		.yywLines = 0,							// dummy
		.outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC420_Y,
		.outputGlobalW[D_IM_R2Y_PORT_CBCR] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC420_C_SP,
		.outputGlobalW[D_IM_R2Y_PORT_2] = 0,	// dummy
	},
};

// TImR2yInaddrInfo table for RGB 8bit input
TImR2yInaddrInfo gct_im_r2y_in_addr_rgb8bit = {
	.rgb.addrR = NULL,
	.rgb.addrG = NULL,
	.rgb.addrB = NULL,
};


// TImR2yInaddrInfo table for RGB 12bit input
TImR2yInaddrInfo gctImR2yInAddrRgb12bit = {
	.rgb.addrR = NULL,
	.rgb.addrG = NULL,
	.rgb.addrB = NULL,
};


// TImR2yInaddrInfo table for RGB 16bit input
TImR2yInaddrInfo gctImR2yInAddrRgb16bit = {
	.rgb.addrR = NULL,
	.rgb.addrG = NULL,
	.rgb.addrB = NULL,
};


// TImR2yCtrlDirect table
TImR2yCtrlDirect gctImR2yCtrlDirect = {
	.frameStop = 1,
};


// TImR2yOutbankInfo table for YCC444 output
TImR2yOutbankInfo gctImR2yOutAddrYcc444 = {
	.bankInitialPosition = D_IM_R2Y_YYW_BANK_0,
	.useBankNum = D_IM_R2Y_YYW_BANK_0,
	.outputAddr[D_IM_R2Y_YYW_BANK_0] = {
		.ycc.addrY = NULL,
		.ycc.addrCb = NULL,
		.ycc.addrCr = NULL,
	},
};

// TImR2yOutbankInfo table for YCC422 output
TImR2yOutbankInfo gctImR2yOutAddrYcc422 = {
	.bankInitialPosition = D_IM_R2Y_YYW_BANK_0,
	.useBankNum = D_IM_R2Y_YYW_BANK_0,
	.outputAddr[D_IM_R2Y_YYW_BANK_0] = {
		.ycc.addrY = NULL,
		.ycc.addrCb = NULL,
		.ycc.addrCr = NULL,
	},
};

// TImR2yOutbankInfo table for YCC420 output
TImR2yOutbankInfo gctImR2yOutAddrYcc420 = {
	.bankInitialPosition = D_IM_R2Y_YYW_BANK_0,
	.useBankNum = D_IM_R2Y_YYW_BANK_0,
	.outputAddr[D_IM_R2Y_YYW_BANK_0] = {
		.ycc.addrY = NULL,
		.ycc.addrCb = NULL,
		.ycc.addrCr = NULL,
	},
};

// RGB Deknee table. ( for RGB input )
const USHORT gctImR2yRgbDekneeTbl[D_IM_R2Y_TABLE_MAX_RGB_DEKNEE] = {
	     0,    16,    32,    48,    64,    80,    96,   112,   128,   144,   160,   176,   192,   208,   224,   240,
	   256,   273,   289,   305,   321,   337,   353,   369,   385,   401,   417,   433,   449,   465,   481,   497,
	   513,   529,   546,   562,   578,   594,   610,   626,   642,   658,   674,   690,   706,   722,   738,   754,
	   770,   786,   802,   819,   835,   851,   867,   883,   899,   915,   931,   947,   963,   979,   995,  1011,
	  1027,  1043,  1059,  1075,  1092,  1108,  1124,  1140,  1156,  1172,  1188,  1204,  1220,  1236,  1252,  1268,
	  1284,  1300,  1316,  1332,  1348,  1365,  1381,  1397,  1413,  1429,  1445,  1461,  1477,  1493,  1509,  1525,
	  1541,  1557,  1573,  1589,  1605,  1621,  1638,  1654,  1670,  1686,  1702,  1718,  1734,  1750,  1766,  1782,
	  1798,  1814,  1830,  1846,  1862,  1878,  1894,  1911,  1927,  1943,  1959,  1975,  1991,  2007,  2023,  2039,
	  2055,  2071,  2087,  2103,  2119,  2135,  2151,  2167,  2184,  2200,  2216,  2232,  2248,  2264,  2280,  2296,
	  2312,  2328,  2344,  2360,  2376,  2392,  2408,  2424,  2440,  2457,  2473,  2489,  2505,  2521,  2537,  2553,
	  2569,  2585,  2601,  2617,  2633,  2649,  2665,  2681,  2697,  2713,  2730,  2746,  2762,  2778,  2794,  2810,
	  2826,  2842,  2858,  2874,  2890,  2906,  2922,  2938,  2954,  2970,  2986,  3003,  3019,  3035,  3051,  3067,
	  3083,  3099,  3115,  3131,  3147,  3163,  3179,  3195,  3211,  3227,  3243,  3259,  3276,  3292,  3308,  3324,
	  3340,  3356,  3372,  3388,  3404,  3420,  3436,  3452,  3468,  3484,  3500,  3516,  3532,  3549,  3565,  3581,
	  3597,  3613,  3629,  3645,  3661,  3677,  3693,  3709,  3725,  3741,  3757,  3773,  3789,  3805,  3822,  3838,
	  3854,  3870,  3886,  3902,  3918,  3934,  3950,  3966,  3982,  3998,  4014,  4030,  4046,  4062,  4078,  4095,
};

const USHORT gctImLtmYlogTbl[D_IM_LTM_TABLE_MAX_YLOG] = {
	   0,  905, 1434, 1810, 2101, 2340, 2541, 2715, 2869, 3007, 3131, 3245, 3349, 3446, 3536, 3620,
	3700, 3774, 3845, 3912, 3976, 4036, 4094, 4150, 4203, 4255, 4304, 4351, 4397, 4441, 4484, 4526,
	4566, 4605, 4643, 4680, 4715, 4750, 4784, 4817, 4849, 4881, 4912, 4942, 4971, 5000, 5028, 5055,
	5082, 5109, 5134, 5160, 5185, 5209, 5233, 5257, 5280, 5302, 5325, 5347, 5368, 5389, 5410, 5431,
	5451, 5471, 5491, 5510, 5529, 5548, 5566, 5585, 5603, 5621, 5638, 5655, 5672, 5689, 5706, 5722,
	5739, 5755, 5770, 5786, 5802, 5817, 5832, 5847, 5862, 5876, 5891, 5905, 5919, 5933, 5947, 5960,
	5974, 5987, 6001, 6014, 6027, 6040, 6052, 6065, 6077, 6090, 6102, 6114, 6126, 6138, 6150, 6162,
	6173, 6185, 6196, 6208, 6219, 6230, 6241, 6252, 6263, 6273, 6284, 6295, 6305, 6316, 6326, 6336,
	6346, 6356, 6366, 6376, 6386, 6396, 6406, 6415, 6425, 6434, 6444, 6453, 6462, 6472, 6481, 6490,
	6499, 6508, 6517, 6526, 6535, 6543, 6552, 6561, 6569, 6578, 6586, 6595, 6603, 6611, 6619, 6628,
	6636, 6644, 6652, 6660, 6668, 6676, 6684, 6691, 6699, 6707, 6714, 6722, 6730, 6737, 6745, 6752,
	6759, 6767, 6774, 6781, 6789, 6796, 6803, 6810, 6817, 6824, 6831, 6838, 6845, 6852, 6859, 6866,
	6872, 6879, 6886, 6893, 6899, 6906, 6912, 6919, 6926, 6932, 6938, 6945, 6951, 6958, 6964, 6970,
	6976, 6983, 6989, 6995, 7001, 7007, 7013, 7020, 7026, 7032, 7038, 7043, 7049, 7055, 7061, 7067,
	7073, 7079, 7084, 7090, 7096, 7102, 7107, 7113, 7118, 7124, 7130, 7135, 7141, 7146, 7152, 7157,
	7163, 7168, 7173, 7179, 7184, 7189, 7195, 7200, 7205, 7210, 7216, 7221, 7226, 7231, 7236, 7241,
	7246, 7252, 7257, 7262, 7267, 7272, 7277, 7282, 7287, 7291, 7296, 7301, 7306, 7311, 7316, 7321,
	7325, 7330, 7335, 7340, 7344, 7349, 7354, 7358, 7363, 7368, 7372, 7377, 7382, 7386, 7391, 7395,
	7400, 7404, 7409, 7413, 7418, 7422, 7427, 7431, 7435, 7440, 7444, 7449, 7453, 7457, 7462, 7466,
	7470, 7474, 7479, 7483, 7487, 7491, 7496, 7500, 7504, 7508, 7512, 7516, 7521, 7525, 7529, 7533,
	7537, 7541, 7545, 7549, 7553, 7557, 7561, 7565, 7569, 7573, 7577, 7581, 7585, 7589, 7593, 7597,
	7600, 7604, 7608, 7612, 7616, 7620, 7623, 7627, 7631, 7635, 7639, 7642, 7646, 7650, 7654, 7657,
	7661, 7665, 7668, 7672, 7676, 7679, 7683, 7687, 7690, 7694, 7697, 7701, 7705, 7708, 7712, 7715,
	7719, 7722, 7726, 7729, 7733, 7736, 7740, 7743, 7747, 7750, 7754, 7757, 7761, 7764, 7768, 7771,
	7774, 7778, 7781, 7784, 7788, 7791, 7795, 7798, 7801, 7805, 7808, 7811, 7814, 7818, 7821, 7824,
	7828, 7831, 7834, 7837, 7840, 7844, 7847, 7850, 7853, 7856, 7860, 7863, 7866, 7869, 7872, 7875,
	7879, 7882, 7885, 7888, 7891, 7894, 7897, 7900, 7903, 7906, 7910, 7913, 7916, 7919, 7922, 7925,
	7928, 7931, 7934, 7937, 7940, 7943, 7946, 7949, 7952, 7955, 7958, 7961, 7963, 7966, 7969, 7972,
	7975, 7978, 7981, 7984, 7987, 7990, 7992, 7995, 7998, 8001, 8004, 8007, 8010, 8012, 8015, 8018,
	8021, 8024, 8026, 8029, 8032, 8035, 8038, 8040, 8043, 8046, 8049, 8051, 8054, 8057, 8060, 8062,
	8065, 8068, 8070, 8073, 8076, 8079, 8081, 8084, 8087, 8089, 8092, 8095, 8097, 8100, 8103, 8105,
	8108, 8110, 8113, 8116, 8118, 8121, 8123, 8126, 8129, 8131, 8134, 8136, 8139, 8142, 8144, 8147,
};

static void ct_im_r2y_constructor(CtImR2y *self)
{
	CtImR2yPrivate *priv = CT_IM_R2Y_GET_PRIVATE(self);
}

static void ct_im_r2y_destructor(CtImR2y *self)
{
	CtImR2yPrivate *priv = CT_IM_R2Y_GET_PRIVATE(self);
}

VOID ct_im_r2y_get_loop_val(self->ctImR2y, UCHAR pipeNo, UCHAR* loopSta, UCHAR* loopEnd )
{
	switch( pipeNo ){
		case D_IM_R2Y_PIPE1:
			*loopSta = 0;
			*loopEnd = 0;
			break;
		case D_IM_R2Y_PIPE2:
			*loopSta = 1;
			*loopEnd = 1;
			break;
//		case D_IM_R2Y_PIPE12:
			default:
			*loopSta = 0;
			*loopEnd = 1;
			break;
	}
}

VOID ct_im_r2y_set_gamma_on( UCHAR pipeNo )
{
	static const USHORT dgammaAbs[D_IM_R2Y_TABLE_MAX_GAMMA] = {
		0x0000, 0x0052, 0x0071, 0x0088, 0x009B, 0x00AB, 0x00BA, 0x00C7,
		0x00D4, 0x00DF, 0x00EA, 0x00F5, 0x00FF, 0x0108, 0x0111, 0x011A,
		0x0122, 0x012A, 0x0132, 0x013A, 0x0141, 0x0148, 0x014F, 0x0156,
		0x015D, 0x0163, 0x016A, 0x0170, 0x0176, 0x017C, 0x0182, 0x0188,
		0x018E, 0x0193, 0x0199, 0x019E, 0x01A3, 0x01A9, 0x01AE, 0x01B3,
		0x01B8, 0x01BD, 0x01C2, 0x01C7, 0x01CC, 0x01D0, 0x01D5, 0x01D9,
		0x01DE, 0x01E3, 0x01E7, 0x01EB, 0x01F0, 0x01F4, 0x01F8, 0x01FD,
		0x0201, 0x0205, 0x0209, 0x020D, 0x0211, 0x0215, 0x0219, 0x021D,
		0x0221, 0x0225, 0x0229, 0x022C, 0x0230, 0x0234, 0x0237, 0x023B,
		0x023F, 0x0242, 0x0246, 0x024A, 0x024D, 0x0251, 0x0254, 0x0258,
		0x025B, 0x025E, 0x0262, 0x0265, 0x0269, 0x026C, 0x026F, 0x0272,
		0x0276, 0x0279, 0x027C, 0x027F, 0x0283, 0x0286, 0x0289, 0x028C,
		0x028F, 0x0292, 0x0295, 0x0298, 0x029B, 0x029E, 0x02A1, 0x02A4,
		0x02A7, 0x02AA, 0x02AD, 0x02B0, 0x02B3, 0x02B6, 0x02B9, 0x02BC,
		0x02BF, 0x02C1, 0x02C4, 0x02C7, 0x02CA, 0x02CD, 0x02D0, 0x02D2,
		0x02D5, 0x02D8, 0x02DA, 0x02DD, 0x02E0, 0x02E3, 0x02E5, 0x02E8,
		0x02EB, 0x02ED, 0x02F0, 0x02F3, 0x02F5, 0x02F8, 0x02FA, 0x02FD,
		0x02FF, 0x0302, 0x0305, 0x0307, 0x030A, 0x030C, 0x030F, 0x0311,
		0x0314, 0x0316, 0x0319, 0x031B, 0x031E, 0x0320, 0x0322, 0x0325,
		0x0327, 0x032A, 0x032C, 0x032E, 0x0331, 0x0333, 0x0336, 0x0338,
		0x033A, 0x033D, 0x033F, 0x0341, 0x0344, 0x0346, 0x0348, 0x034B,
		0x034D, 0x034F, 0x0351, 0x0354, 0x0356, 0x0358, 0x035A, 0x035D,
		0x035F, 0x0361, 0x0363, 0x0366, 0x0368, 0x036A, 0x036C, 0x036E,
		0x0371, 0x0373, 0x0375, 0x0377, 0x0379, 0x037B, 0x037D, 0x0380,
		0x0382, 0x0384, 0x0386, 0x0388, 0x038A, 0x038C, 0x038E, 0x0390,
		0x0393, 0x0395, 0x0397, 0x0399, 0x039B, 0x039D, 0x039F, 0x03A1,
		0x03A3, 0x03A5, 0x03A7, 0x03A9, 0x03AB, 0x03AD, 0x03AF, 0x03B1,
		0x03B3, 0x03B5, 0x03B7, 0x03B9, 0x03BB, 0x03BD, 0x03BF, 0x03C1,
		0x03C3, 0x03C5, 0x03C7, 0x03C9, 0x03CB, 0x03CD, 0x03CF, 0x03D0,
		0x03D2, 0x03D4, 0x03D6, 0x03D8, 0x03DA, 0x03DC, 0x03DE, 0x03E0,
		0x03E2, 0x03E3, 0x03E5, 0x03E7, 0x03E9, 0x03EB, 0x03ED, 0x03EF,
		0x03F0, 0x03F2, 0x03F4, 0x03F6, 0x03F8, 0x03FA, 0x03FB, 0x03FD,
	};
	static const ULLONG dgammaOfs[D_IM_R2Y_TABLE_MAX_GAMMA] = {
		0xB83926251B1B1B1Aull, 0x18121212120A1211ull, 0x080A0A0A0A0A1109ull, 0x08090A0911090909ull,
		0x0809090909090909ull, 0x0809090901090909ull, 0x0801090901090901ull, 0x0809080901090109ull,
		0x0009010901090109ull, 0x0801090109080109ull, 0x0801090801090808ull, 0x0009080801090808ull,
		0x0001090808010101ull, 0x0808080801010101ull, 0x0808080808010101ull, 0x0001010101090808ull,
		0x0808080808080808ull, 0x0808080808080808ull, 0x0808000101010101ull, 0x0001010108080808ull,
		0x0800010101010108ull, 0x0808080001010108ull, 0x0808000101010808ull, 0x0800010101080800ull,
		0x0001080808000101ull, 0x0808000101080800ull, 0x0001080800010808ull, 0x0001010808000108ull,
		0x0800010808000108ull, 0x0800010808000108ull, 0x0001010800010808ull, 0x0001080001080800ull,
		0x0008000108000108ull, 0x0800010800010800ull, 0x0008000108000108ull, 0x0001080001080001ull,
		0x0800010800010800ull, 0x0008000108000108ull, 0x0001000108000108ull, 0x0001080001000108ull,
		0x0001080001000108ull, 0x0001080008000108ull, 0x0001000108000100ull, 0x0008000100010800ull,
		0x0000010800080001ull, 0x0800080001000108ull, 0x0008000100010800ull, 0x0800010001080008ull,
		0x0001000108000800ull, 0x0000010800080008ull, 0x0001000100010800ull, 0x0800080001000100ull,
		0x0008000800080001ull, 0x0001000100010800ull, 0x0800080008000100ull, 0x0000010001000100ull,
		0x0008000800080008ull, 0x0008000800080008ull, 0x0008000100010001ull, 0x0001000100010001ull,
		0x0001000100010001ull, 0x0001000100010001ull, 0x0001000800080008ull, 0x0008000800080008ull,
		0x0008000800000100ull, 0x0000010001000100ull, 0x0000080008000800ull, 0x0800000100010001ull,
		0x0001000800080008ull, 0x0000010001000100ull, 0x0800080008000001ull, 0x0001000100080008ull,
		0x0000010001000100ull, 0x0800080000010001ull, 0x0008000800000100ull, 0x0000080008000001ull,
		0x0001000800080000ull, 0x0000080008000001ull, 0x0001000800000100ull, 0x0000080000010001ull,
		0x0008000001000100ull, 0x0800000100010008ull, 0x0000010008000800ull, 0x0001000800000100ull,
		0x0000080000010008ull, 0x0000010008000800ull, 0x0001000800000100ull, 0x0800000100080000ull,
		0x0000080008000001ull, 0x0008000001000800ull, 0x0001000800000100ull, 0x0800000100080000ull,
		0x0000080000010008ull, 0x0000080000010008ull, 0x0000010008000001ull, 0x0008000001000800ull,
		0x0008000001000800ull, 0x0001000800000800ull, 0x0001000800000100ull, 0x0800000800000100ull,
		0x0800000800000100ull, 0x0800000100000100ull, 0x0800000100000100ull, 0x0800000100000100ull,
		0x0800000800000100ull, 0x0800000800000100ull, 0x0001000800000800ull, 0x0001000001000800ull,
		0x0008000001000001ull, 0x0008000008000001ull, 0x0000010008000008ull, 0x0000080000010000ull,
		0x0000080000080000ull, 0x0800000100000100ull, 0x0001000800000800ull, 0x0008000001000001ull,
		0x0000010008000008ull, 0x0000080000080000ull, 0x0000000100000100ull, 0x0001000001000800ull,
		0x0008000008000008ull, 0x0000080000080000ull, 0x0800000100000100ull, 0x0001000001000001ull,
		0x0000010000010000ull, 0x0000000100000100ull, 0x0001000001000001ull, 0x0000010000010000ull,
		0x0000000100000100ull, 0x0001000001000001ull, 0x0000010000010000ull, 0x0000000800000800ull,
		0x0008000008000008ull, 0x0000080000080000ull, 0x0001000001000001ull, 0x0000010000010000ull,
		0x0800000800000800ull, 0x0008000000010000ull, 0x0000000100000800ull, 0x0008000008000000ull,
		0x0000000100000100ull, 0x0008000008000008ull, 0x0000000100000100ull, 0x0008000008000008ull,
		0x0000000100000100ull, 0x0008000008000000ull, 0x0000000100000800ull, 0x0008000000010000ull,
		0x0000000800000800ull, 0x0000010000010000ull, 0x0800000001000001ull, 0x0000080000080000ull,
		0x0001000008000008ull, 0x0000000100000800ull, 0x0008000000010000ull, 0x0800000800000001ull,
		0x0000080000000100ull, 0x0001000008000000ull, 0x0000000800000800ull, 0x0000010000080000ull,
		0x0001000008000008ull, 0x0000000100000800ull, 0x0000010000080000ull, 0x0001000008000000ull,
		0x0000000100000800ull, 0x0000010000080000ull, 0x0001000008000000ull, 0x0000000800000001ull,
		0x0000080000000100ull, 0x0008000000010000ull, 0x0800000001000008ull, 0x0000000100000001ull,
		0x0000080000000100ull, 0x0008000000010000ull, 0x0800000001000008ull, 0x0000000800000001ull,
		0x0000080000000100ull, 0x0008000000010000ull, 0x0001000008000000ull, 0x0000000800000008ull,
		0x0000000100000800ull, 0x0000080000000100ull, 0x0008000000010000ull, 0x0001000008000000ull,
		0x0000000001000008ull, 0x0000000800000001ull, 0x0000080000000800ull, 0x0000010000000100ull,
		0x0008000000080000ull, 0x0001000008000000ull, 0x0800000001000000ull, 0x0000000800000008ull,
		0x0000000100000001ull, 0x0000000100000800ull, 0x0000080000000100ull, 0x0000010000080000ull,
		0x0008000000080000ull, 0x0001000000010000ull, 0x0001000008000000ull, 0x0800000008000000ull,
		0x0000000001000000ull, 0x0000000001000008ull, 0x0000000800000008ull, 0x0000000100000001ull,
		0x0000000100000001ull, 0x0000000100000800ull, 0x0000080000000800ull, 0x0000080000000800ull,
		0x0000080000000800ull, 0x0000010000000100ull, 0x0000010000000100ull, 0x0000010000000100ull,
		0x0000010000000100ull, 0x0000010000000100ull, 0x0000010000000100ull, 0x0000010000000100ull,
		0x0000010000000100ull, 0x0000010000000100ull, 0x0000010000000100ull, 0x0000010000000100ull,
		0x0000010000000800ull, 0x0000080000000800ull, 0x0000080000000800ull, 0x0000080000000001ull,
		0x0000000100000001ull, 0x0000000100000001ull, 0x0000000800000008ull, 0x0000000800000008ull,
		0x0000000001000000ull, 0x0000000001000000ull, 0x0000000008000000ull, 0x0800000008000000ull,
		0x0001000000010000ull, 0x0008000000080000ull, 0x0008000000000100ull, 0x0000010000000800ull,
		0x0000080000000800ull, 0x0000000100000001ull, 0x0000000800000008ull, 0x0000000001000000ull,
		0x0000000008000000ull, 0x0800000000010000ull, 0x0001000000080000ull, 0x0008000000000100ull,
		0x0000080000000800ull, 0x0000000100000001ull, 0x0000000800000000ull, 0x0000000001000000ull,
		0x0800000000010000ull, 0x0001000000080000ull, 0x0000010000000100ull, 0x0000080000000001ull,
		0x0000000100000008ull, 0x0000000001000000ull, 0x0800000000010000ull, 0x0001000000080000ull,
	};
	static const TImR2yCtrlGamma r2yCtrlGamma = {
			.gammaEnable = D_IM_R2Y_ENABLE_ON,
			.gammaMode = D_IM_R2Y_GAMMA_MODE_12,
			.gammaYbTblSimul = D_IM_R2Y_ENABLE_ON,
	};
	INT32 ercd;

	ercd = Im_R2Y_Ctrl_Gamma( pipeNo, &r2yCtrlGamma );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "im_r2y_set_gamma Im_R2Y_Ctrl_Gamma ercd=%d\n", ercd ));
	}
	ercd = Im_R2Y_Set_Gamma_Table( pipeNo, 0, dgammaAbs, dgammaOfs );
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( "im_r2y_set_gamma Im_R2Y_Set_Gamma_Table ercd=%d\n", ercd ));
	}
}

VOID ct_im_r2y_handler( UINT32* result, UINT32 userParam )
{
	if( ((*result) & D_IM_R2Y1_INT_STATE_YYR_END) != 0 ) {
		Ddim_Print(( "R2Y1 YYRch end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_YYWALL_END) != 0 ) {
		Ddim_Print(( "R2Y1 YYWch all end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_YYW0_END) != 0 ) {
		Ddim_Print(( "R2Y1 YYWch 0 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_YYW1_END) != 0 ) {
		Ddim_Print(( "R2Y1 YYWch 1 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_YYW2_END) != 0 ) {
		Ddim_Print(( "R2Y1 YYWch 2 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_YYW0A_END) != 0 ) {
		Ddim_Print(( "R2Y1 YYWch 0A end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_YYW_ERR) != 0 ) {
		Ddim_Print(( "R2Y1 YYWch error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_YYR_ERR) != 0 ) {
		Ddim_Print(( "R2Y1 YYRch error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_AXR_ERR) != 0 ) {
		Ddim_Print(( "R2Y1 AXR error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_AXW_ERR) != 0 ) {
		Ddim_Print(( "R2Y1 AXW error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_LINE0_END) != 0 ) {
		Ddim_Print(( "R2Y1 line0 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_LINE1_END) != 0 ) {
		Ddim_Print(( "R2Y1 line1 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_LINE2_END) != 0 ) {
		Ddim_Print(( "R2Y1 line2 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y1_INT_STATE_YCFERR_ERR) != 0 ) {
		Ddim_Print(( "R2Y1 YCF error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YYR_END) != 0 ) {
		Ddim_Print(( "R2Y2 YYRch end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YYWALL_END) != 0 ) {
		Ddim_Print(( "R2Y2 YYWch all end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YYW0_END) != 0 ) {
		Ddim_Print(( "R2Y2 YYWch 0 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YYW1_END) != 0 ) {
		Ddim_Print(( "R2Y2 YYWch 1 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YYW2_END) != 0 ) {
		Ddim_Print(( "R2Y2 YYWch 2 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YYW0A_END) != 0 ) {
		Ddim_Print(( "R2Y2 YYWch 0A end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YYW_ERR) != 0 ) {
		Ddim_Print(( "R2Y2 YYWch error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YYR_ERR) != 0 ) {
		Ddim_Print(( "R2Y2 YYRch error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_AXR_ERR) != 0 ) {
		Ddim_Print(( "R2Y2 AXR error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_AXW_ERR) != 0 ) {
		Ddim_Print(( "R2Y2 AXW error! %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_LINE0_END) != 0 ) {
		Ddim_Print(( "R2Y2 line0 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_LINE1_END) != 0 ) {
		Ddim_Print(( "R2Y2 line1 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_LINE2_END) != 0 ) {
		Ddim_Print(( "R2Y2 line2 end. %x\n", userParam ));
	}
	if( ((*result) & D_IM_R2Y2_INT_STATE_YCFERR_ERR) != 0 ) {
		Ddim_Print(( "R2Y2 YCF error! %x\n", userParam ));
	}
}

CtImR2y* ct_im_r2y_new(void)
{
	CtImR2y* self = k_object_new_with_private(CT_TYPE_IM_R2Y, sizeof(CtImR2yPrivate));

	return self;
}

CtImR2y* ct_im_r2y_get(void)
{
	static CtImR2y* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y, sizeof(CtImR2yPrivate));
	}

	return self;
}
