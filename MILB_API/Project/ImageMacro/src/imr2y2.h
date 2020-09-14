/*
 * imr2y2.h
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :gonghaotian
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __IM_R2Y2_H__
#define __IM_R2Y2_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y2		(im_r2y2_get_type())
#define IM_R2Y2(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2y2))
#define IM_IS_R2Y2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y2))

#define D_IM_R2Y_YYWTRG_IDLE			(2)

#define im_r2y_yyw_is_activated(a)				(gImIoR2yRegPtr[a]->YYW.YYWTRG.bit.YYWTRG != D_IM_R2Y_YYWTRG_IDLE)

typedef struct 				_ImR2y2 ImR2y2;
typedef struct 				_ImR2y2Private ImR2y2Private;


struct _ImR2y2 {
	KObject parent;
};

KConstType 		    im_r2y2_get_type(void);
ImR2y2*		        im_r2y2_new(void);

/**
@weakgroup im_r2y
@{

<hr>

@section im_r2y_sample Sample code

@section im_r2y_sample_section1	Sample code of R2Y Initialization.
	@code
	Im_r2y_init( ImR2yCtrl_PIPE12 );
	@endcode
	<br><br>

@section im_r2y_sample_section2	Sample code of data setting for Photo.
	@code
	#define D_USER_YCC_TOP_X_PIXS 16
	#define D_USER_YCC_TOP_Y_PIXS 12
	#define D_USER_YCC_WIDTH_PIXS 640
	#define D_USER_YCC_LINES_PIXS 480

	#define D_USER_RGB_LINEFEED_BYTES (D_USER_YCC_WIDTH_PIXS *3)	// 1pixel = 24bit
	#define D_USER_RGB_IN_ADDR_R   0x00000000
	#define D_USER_RGB_IN_ADDR_G   0x00000000
	#define D_USER_RGB_IN_ADDR_B   0x00000000
	#define D_USER_YCC_OUT_ADDR_Y  0x00000000
	#define D_USER_YCC_OUT_ADDR_CB 0x00000000
	#define D_USER_YCC_OUT_ADDR_CR 0x00000000

	void User_Photo_Handler( UINT32* status, UINT32 userParam );

	void User_Capture_R2Y_Process( void ) {
		TImR2yCtrl r2yCtrl;
		CtrlSdramInput r2y_ctrl_sdram_in;
		R2yResizeRect r2y_resize_rect_param;
		R2yInaddrInfo r2y_in_addr;
		R2yOutbankInfo r2y_addr_0;
		T_IM_R2Y_ERR_FLAG t_r2y_err_flg;

		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.masterIfSelect = ImR2yCtrl_MASTER_IF0_PORT0 | ImR2yCtrl_MASTER_IF0_PORT1 | ImR2yCtrl_MASTER_IF0_PORT2;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.burstLength = ImR2yCtrl_BRST_512;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.outEnable[ImR2yCtrl_PORT_Y] = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.outEnable[ImR2yCtrl_PORT_CB] = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.outEnable[ImR2yCtrl_PORT_CR] = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].writeRequestMask[ImR2yCtrl_PORT_Y] = 0;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].writeRequestMask[ImR2yCtrl_PORT_CB] = 0;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].writeRequestMask[ImR2yCtrl_PORT_CR] = 0;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].pixelAvgReductionMode = ImR2yCtrl_RDC_MODE_DIV_2;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].pixelAvgReductionEnable = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].yccCcThinSelect = ImR2yCtrl_THIN_OUT_YCC422_CENTER;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].trimOutEnable = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].planarInterleavedMode = ImR2yCtrl_PORT_PLANAR;

		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.masterIfSelect = ImR2yCtrl_MASTER_IF0_PORT0 | ImR2yCtrl_MASTER_IF0_PORT1 | ImR2yCtrl_MASTER_IF0_PORT2;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.burstLength = ImR2yCtrl_BRST_512;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.outEnable[ImR2yCtrl_PORT_Y] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.outEnable[ImR2yCtrl_PORT_CB] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.outEnable[ImR2yCtrl_PORT_CR] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].writeRequestMask[ImR2yCtrl_PORT_Y] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].writeRequestMask[ImR2yCtrl_PORT_CB] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].writeRequestMask[ImR2yCtrl_PORT_CR] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].pixelAvgReductionMode = ImR2yCtrl_RDC_MODE_DIV_2;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].pixelAvgReductionEnable = ImR2yCtrl_ENABLE_OFF;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].yccCcThinSelect = ImR2yCtrl_THIN_OUT_YCC422_CENTER;				// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].trimOutEnable = ImR2yCtrl_ENABLE_OFF;								// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].planarInterleavedMode = ImR2yCtrl_PORT_PLANAR;						// dummy

		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.masterIfSelect = ImR2yCtrl_MASTER_IF0_PORT0;		// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.burstLength = ImR2yCtrl_BRST_512;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.outEnable[ImR2yCtrl_PORT_Y] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.outEnable[ImR2yCtrl_PORT_CB] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.outEnable[ImR2yCtrl_PORT_CR] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].writeRequestMask[ImR2yCtrl_PORT_Y] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].writeRequestMask[ImR2yCtrl_PORT_CB] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].writeRequestMask[ImR2yCtrl_PORT_CR] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].pixelAvgReductionMode = ImR2yCtrl_RDC_MODE_DIV_2;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].pixelAvgReductionEnable = ImR2yCtrl_ENABLE_OFF;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].yccCcThinSelect = ImR2yCtrl_THIN_OUT_YCC422_CENTER;				// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].trimOutEnable = ImR2yCtrl_ENABLE_OFF;								// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].planarInterleavedMode = ImR2yCtrl_PORT_PLANAR;						// dummy

		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.masterIfSelect = ImR2yCtrl_MASTER_IF0_PORT0;		// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.burstLength = ImR2yCtrl_BRST_512;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.outEnable[ImR2yCtrl_PORT_Y] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.outEnable[ImR2yCtrl_PORT_CB] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.outEnable[ImR2yCtrl_PORT_CR] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].writeRequestMask[ImR2yCtrl_PORT_Y] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].writeRequestMask[ImR2yCtrl_PORT_CB] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].writeRequestMask[ImR2yCtrl_PORT_CR] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].pixelAvgReductionMode = ImR2yCtrl_RDC_MODE_DIV_2;				// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].pixelAvgReductionEnable = ImR2yCtrl_ENABLE_OFF;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].yccCcThinSelect = ImR2yCtrl_THIN_OUT_YCC422_CENTER;				// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].trimOutEnable = ImR2yCtrl_ENABLE_OFF;								// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].planarInterleavedMode = ImR2yCtrl_PORT_PLANAR;					// dummy

		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_0].level = 0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_1].level = 0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_2].level = 0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_0].yywSelect = ImR2yCtrl_YYW_CH_0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_1].yywSelect = ImR2yCtrl_YYW_CH_0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_2].yywSelect = ImR2yCtrl_YYW_CH_0;

		r2yCtrl.yywEnable[ImR2yCtrl_YYW_CH_0] = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yywEnable[ImR2yCtrl_YYW_CH_1] = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.yywEnable[ImR2yCtrl_YYW_CH_2] = ImR2yCtrl_ENABLE_OFF;

		r2yCtrl.lineTransferCycle = 0;
		r2yCtrl.yywContinueStartEnable = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.yywHorizontalFlip = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.videoFormatOutSelect0 = ImR2yCtrl_VFM_NORMAL;
		r2yCtrl.ipuMacroOutputEnable = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.ipuMacroTrimmingEnable = ImR2yCtrl_ENABLE_OFF;	// dummy
		r2yCtrl.cnrMacroOutputEnable = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.cnrMacroTrimmingEnable = ImR2yCtrl_ENABLE_OFF;	// dummy
		r2yCtrl.outputMode0a = ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP;
		r2yCtrl.videoFormatOutSelect0a = ImR2yCtrl_VFM_NORMAL;	// dummy
		r2yCtrl.outputFormatSel1 = ImR2yCtrl_DATA_FORMAT_8;		// dummy
		r2yCtrl.outputTypeSel1 = ImR2yCtrl_WRITE_DTYP_PACK8;		// dummy
		r2yCtrl.ycfBypass = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.ycfPadding = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.mccSelect = ImR2yCtrl_MCC_AFTER_CC0;
		r2yCtrl.mccBitShift = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.r2yUserHandler = User_Photo_Handler;
		r2yCtrl.userParam = 0;

		r2y_ctrl_sdram_in.burstLength = ImR2yCtrl_BRST_512;
		r2y_ctrl_sdram_in.readRequestMask[ImR2yCtrl_PORT_0] = 0;
		r2y_ctrl_sdram_in.readRequestMask[ImR2yCtrl_PORT_1] = 0;
		r2y_ctrl_sdram_in.readRequestMask[ImR2yCtrl_PORT_2] = 0;
		r2y_ctrl_sdram_in.inputDtype = ImR2yCtrl_READ_DTYP_PACK12;
		r2y_ctrl_sdram_in.monoEbable = ImR2yCtrl_ENABLE_OFF;
		r2y_ctrl_sdram_in.rgbDekneeEnable = ImR2yCtrl_ENABLE_OFF;
		r2y_ctrl_sdram_in.rgbLeftShift = ImR2yCtrl_STL_RGB_LEFT_SHIFT_NONE;
		r2y_ctrl_sdram_in.rgbSaturationMode = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.topOffset[ImR2yCtrl_PORT_Y] = 0;
		r2yCtrl.topOffset[ImR2yCtrl_PORT_CB] = 0;
		r2yCtrl.topOffset[ImR2yCtrl_PORT_CR] = 0;
		r2y_ctrl_sdram_in.inputGlobal = D_USER_RGB_LINEFEED_BYTES;

		r2y_resize_rect_param.inputSize.imgTop = D_USER_YCC_TOP_X_PIXS;
		r2y_resize_rect_param.inputSize.imgLeft = D_USER_YCC_TOP_Y_PIXS;
		r2y_resize_rect_param.inputSize.imgWidth = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.inputSize.imgLines = D_USER_YCC_LINES_PIXS;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0].yywWidth = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0].yywLines = D_USER_YCC_LINES_PIXS;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0].outputGlobalW[ImR2yCtrl_PORT_Y] = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0].outputGlobalW[ImR2yCtrl_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_1].yywWidth = D_USER_YCC_WIDTH_PIXS;									// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_1].yywLines = D_USER_YCC_LINES_PIXS;									// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_1].outputGlobalW[ImR2yCtrl_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_1].outputGlobalW[ImR2yCtrl_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;		// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_2].yywWidth = D_USER_YCC_WIDTH_PIXS;									// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_2].yywLines = D_USER_YCC_LINES_PIXS;									// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_2].outputGlobalW[ImR2yCtrl_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_2].outputGlobalW[ImR2yCtrl_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;		// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0A].yywWidth = D_USER_YCC_WIDTH_PIXS;								// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0A].yywLines = D_USER_YCC_LINES_PIXS;								// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0A].outputGlobalW[ImR2yCtrl_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0A].outputGlobalW[ImR2yCtrl_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;	// dummy

		r2y_in_addr.rgb.addrR = (void*)D_USER_RAW_IN_ADDR_R;
		r2y_in_addr.rgb.addrG = (void*)D_USER_RAW_IN_ADDR_G;
		r2y_in_addr.rgb.addrB = (void*)D_USER_RAW_IN_ADDR_B;

		memset( &r2y_addr_0, '\x00', sizeof(r2y_addr_0) );
		r2y_addr_0.bankInitialPosition = ImR2yCtrl_YYW_BANK_0;
		r2y_addr_0.useBankNum = 3;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrY = (void*)D_USER_YCC_OUT_ADDR_Y;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCb = (void*)D_USER_YCC_OUT_ADDR_CB;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCr = (void*)D_USER_YCC_OUT_ADDR_CR;

		im_r2y_ctrl(im_r2y_new(), ImR2yCtrl_PIPE1, &r2yCtrl );
		im_r2y_ctrl_mode_sdram_input(im_r2y_new(), ImR2yCtrl_PIPE1, &r2y_ctrl_sdram_in );
		im_r2y2_set_resize_rect(im_r2y2_new(),  ImR2yCtrl_PIPE1, &r2y_resize_rect_param );
		im_r2y_set_inaddr_info(im_r2y_new(), ImR2yCtrl_PIPE1, &r2y_in_addr );
		im_r2y_set_out_bank_info(im_r2y_new(), ImR2yCtrl_PIPE1, D_IM_R2Y_YYW_0, &r2y_addr_0 );

		// Start R2Y
		im_r2y_proc_start(im_r2y_proc_new(), ImR2yCtrl_PIPE1);

		// Wait R2Y YYW0 is normal end.
		im_r2y_proc_waitend(im_r2y_proc_new(),  NULL, ImR2yCtrl_INT_FLG_YYW0_END1, 60 );

		// Stop R2Y
		im_r2y_proc_stop(im_r2y_proc_new(), ImR2yCtrl_PIPE1);
	}

	R2yHistogramStat photo_hist_overflow_status;
	R2yHistogramAddr photo_hist_dst_buf;
	void User_Photo_Handler( UINT32* status, UINT32 userParam )
	{
		switch( *status ) {
			case ImR2yCtrl_INT_FLG_YYW0_END1:
				// Finished create YCC image.
				im_r2y3_get_histogram(im_r2y3_new(),  ImR2yCtrl_PIPE1, &photo_hist_overflow_status, &photo_hist_dst_buf );
				break;
			default:
				// Nothing to do.
				break;
		}
	}
	@endcode
	<br><br>


@section im_r2y_sample_section3	Sample code of data setting for Video.
	@code
	#define D_USER_YCC_TOP_X_PIXS 16
	#define D_USER_YCC_TOP_Y_PIXS 12
	#define D_USER_YCC_WIDTH_PIXS 640
	#define D_USER_YCC_LINES_PIXS 480

	#define D_USER_VIEW_HORIZONTAL_BLANKING 200
	#define D_USER_VIEW_YCC_OUT_ADDR_0_Y  0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_0_CB 0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_0_CR 0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_1_Y  0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_1_CB 0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_1_CR 0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_2_Y  0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_2_CB 0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_2_CR 0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_3_Y  0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_3_CB 0x00000000
	#define D_USER_VIEW_YCC_OUT_ADDR_3_CR 0x00000000

	void User_View_Handler( UINT32* status, UINT32 userParam );

	void User_View_R2Y_Start( void ) {
		TImR2yCtrl r2yCtrl;
		R2CtrlDirect r2y_ctrl_direct;
		R2yResizeRect r2y_resize_rect_param;
		R2yOutbankInfo r2y_addr_0;
		R2yCtrlHistogram r2y_hist_ctrl;

		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.masterIfSelect = ImR2yCtrl_MASTER_IF0_PORT0 | ImR2yCtrl_MASTER_IF0_PORT1 | ImR2yCtrl_MASTER_IF0_PORT2;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.burstLength = ImR2yCtrl_BRST_512;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.outEnable[ImR2yCtrl_PORT_Y] = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.outEnable[ImR2yCtrl_PORT_CB] = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].axiWriteMode.outEnable[ImR2yCtrl_PORT_CR] = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].writeRequestMask[ImR2yCtrl_PORT_Y] = 0;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].writeRequestMask[ImR2yCtrl_PORT_CB] = 0;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].writeRequestMask[ImR2yCtrl_PORT_CR] = 0;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].pixelAvgReductionMode = ImR2yCtrl_RDC_MODE_DIV_2;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].pixelAvgReductionEnable = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].yccCcThinSelect = ImR2yCtrl_THIN_OUT_YCC422_CENTER;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].trimOutEnable = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0].planarInterleavedMode = ImR2yCtrl_PORT_PLANAR;

		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.masterIfSelect = ImR2yCtrl_MASTER_IF0_PORT0 | ImR2yCtrl_MASTER_IF0_PORT1 | ImR2yCtrl_MASTER_IF0_PORT2;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.burstLength = ImR2yCtrl_BRST_512;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.outEnable[ImR2yCtrl_PORT_Y] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.outEnable[ImR2yCtrl_PORT_CB] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].axiWriteMode.outEnable[ImR2yCtrl_PORT_CR] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].writeRequestMask[ImR2yCtrl_PORT_Y] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].writeRequestMask[ImR2yCtrl_PORT_CB] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].writeRequestMask[ImR2yCtrl_PORT_CR] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].pixelAvgReductionMode = ImR2yCtrl_RDC_MODE_DIV_2;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].pixelAvgReductionEnable = ImR2yCtrl_ENABLE_OFF;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].yccCcThinSelect = ImR2yCtrl_THIN_OUT_YCC422_CENTER;				// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].trimOutEnable = ImR2yCtrl_ENABLE_OFF;								// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_1].planarInterleavedMode = ImR2yCtrl_PORT_PLANAR;						// dummy

		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.masterIfSelect = ImR2yCtrl_MASTER_IF0_PORT0;		// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.burstLength = ImR2yCtrl_BRST_512;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.outEnable[ImR2yCtrl_PORT_Y] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.outEnable[ImR2yCtrl_PORT_CB] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].axiWriteMode.outEnable[ImR2yCtrl_PORT_CR] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].writeRequestMask[ImR2yCtrl_PORT_Y] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].writeRequestMask[ImR2yCtrl_PORT_CB] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].writeRequestMask[ImR2yCtrl_PORT_CR] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].pixelAvgReductionMode = ImR2yCtrl_RDC_MODE_DIV_2;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].pixelAvgReductionEnable = ImR2yCtrl_ENABLE_OFF;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].yccCcThinSelect = ImR2yCtrl_THIN_OUT_YCC422_CENTER;				// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].trimOutEnable = ImR2yCtrl_ENABLE_OFF;								// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_2].planarInterleavedMode = ImR2yCtrl_PORT_PLANAR;						// dummy

		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.masterIfSelect = ImR2yCtrl_MASTER_IF0_PORT0;		// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.burstLength = ImR2yCtrl_BRST_512;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.outEnable[ImR2yCtrl_PORT_Y] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.outEnable[ImR2yCtrl_PORT_CB] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].axiWriteMode.outEnable[ImR2yCtrl_PORT_CR] = ImR2yCtrl_ENABLE_ON;	// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].writeRequestMask[ImR2yCtrl_PORT_Y] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].writeRequestMask[ImR2yCtrl_PORT_CB] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].writeRequestMask[ImR2yCtrl_PORT_CR] = 0;							// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].pixelAvgReductionMode = ImR2yCtrl_RDC_MODE_DIV_2;				// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].pixelAvgReductionEnable = ImR2yCtrl_ENABLE_OFF;					// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].yccCcThinSelect = ImR2yCtrl_THIN_OUT_YCC422_CENTER;				// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].trimOutEnable = ImR2yCtrl_ENABLE_OFF;								// dummy
		r2yCtrl.yyw[ImR2yCtrl_YYW_CH_0A].planarInterleavedMode = ImR2yCtrl_PORT_PLANAR;					// dummy

		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_0].level = 0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_1].level = 0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_2].level = 0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_0].yywSelect = ImR2yCtrl_YYW_CH_0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_1].yywSelect = ImR2yCtrl_YYW_CH_0;
		r2yCtrl.lineIntr[ImR2yCtrl_LINE_INT_2].yywSelect = ImR2yCtrl_YYW_CH_0;

		r2yCtrl.yywEnable[ImR2yCtrl_YYW_CH_0] = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yywEnable[ImR2yCtrl_YYW_CH_1] = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.yywEnable[ImR2yCtrl_YYW_CH_2] = ImR2yCtrl_ENABLE_OFF;

		r2yCtrl.lineTransferCycle = 0;
		r2yCtrl.yywContinueStartEnable = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.yywHorizontalFlip = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.videoFormatOutSelect0 = ImR2yCtrl_VFM_NORMAL;
		r2yCtrl.ipuMacroOutputEnable = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.ipuMacroTrimmingEnable = ImR2yCtrl_ENABLE_OFF;	// dummy
		r2yCtrl.cnrMacroOutputEnable = ImR2yCtrl_ENABLE_ON;
		r2yCtrl.cnrMacroTrimmingEnable = ImR2yCtrl_ENABLE_OFF;	// dummy
		r2yCtrl.outputMode0a = ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP;
		r2yCtrl.videoFormatOutSelect0a = ImR2yCtrl_VFM_NORMAL;	// dummy
		r2yCtrl.outputFormatSel1 = ImR2yCtrl_DATA_FORMAT_8;		// dummy
		r2yCtrl.outputTypeSel1 = ImR2yCtrl_WRITE_DTYP_PACK8;		// dummy
		r2yCtrl.ycfBypass = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.ycfPadding = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.mccSelect = ImR2yCtrl_MCC_AFTER_CC0;
		r2yCtrl.mccBitShift = ImR2yCtrl_ENABLE_OFF;
		r2yCtrl.r2yUserHandler = User_View_Handler;
		r2yCtrl.userParam = 0;

		r2y_resize_rect_param.inputSize.imgTop = D_USER_YCC_TOP_X_PIXS;
		r2y_resize_rect_param.inputSize.imgLeft = D_USER_YCC_TOP_Y_PIXS;
		r2y_resize_rect_param.inputSize.imgWidth = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.inputSize.imgLines = D_USER_YCC_LINES_PIXS;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0].yywWidth = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0].yywLines = D_USER_YCC_LINES_PIXS;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0].outputGlobalW[ImR2yCtrl_PORT_Y] = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0].outputGlobalW[ImR2yCtrl_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_1].yywWidth = D_USER_YCC_WIDTH_PIXS;									// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_1].yywLines = D_USER_YCC_LINES_PIXS;									// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_1].outputGlobalW[ImR2yCtrl_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_1].outputGlobalW[ImR2yCtrl_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;		// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_2].yywWidth = D_USER_YCC_WIDTH_PIXS;									// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_2].yywLines = D_USER_YCC_LINES_PIXS;									// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_2].outputGlobalW[ImR2yCtrl_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_2].outputGlobalW[ImR2yCtrl_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;		// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0A].yywWidth = D_USER_YCC_WIDTH_PIXS;								// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0A].yywLines = D_USER_YCC_LINES_PIXS;								// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0A].outputGlobalW[ImR2yCtrl_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.outputSize[ImR2yCtrl_YYW_CH_0A].outputGlobalW[ImR2yCtrl_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;	// dummy

		memset( &r2y_addr_0, '\x00', sizeof(r2y_addr_0) );
		r2y_addr_0.bankInitialPosition = ImR2yCtrl_YYW_BANK_0;
		r2y_addr_0.useBankNum = 3;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrY  = (void*)D_USER_VIEW_YCC_OUT_ADDR_0_Y;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCb = (void*)D_USER_VIEW_YCC_OUT_ADDR_0_CB;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_0].ycc.addrCr = (void*)D_USER_VIEW_YCC_OUT_ADDR_0_CR;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrY  = (void*)D_USER_VIEW_YCC_OUT_ADDR_1_Y;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrCb = (void*)D_USER_VIEW_YCC_OUT_ADDR_1_CB;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_1].ycc.addrCr = (void*)D_USER_VIEW_YCC_OUT_ADDR_1_CR;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrY  = (void*)D_USER_VIEW_YCC_OUT_ADDR_2_Y;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrCb = (void*)D_USER_VIEW_YCC_OUT_ADDR_2_CB;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_2].ycc.addrCr = (void*)D_USER_VIEW_YCC_OUT_ADDR_2_CR;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrY  = (void*)D_USER_VIEW_YCC_OUT_ADDR_3_Y;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrCb = (void*)D_USER_VIEW_YCC_OUT_ADDR_3_CB;
		r2y_addr_0.outputAddr[ImR2yCtrl_YYW_BANK_3].ycc.addrCr = (void*)D_USER_VIEW_YCC_OUT_ADDR_3_CR;

		r2y_hist_ctrl.enable = ImR2yCtrl_ENABLE_ON;
		r2y_hist_ctrl.yywNo = ImR2yCtrl_YYW_CH_0;
		r2y_hist_ctrl.samplingPitch = ImR2yCtrl_HIST_PIT_16X16;
		r2y_hist_ctrl.histogramArea.imgTop = 0;
		r2y_hist_ctrl.histogramArea.imgLeft = 0;
		r2y_hist_ctrl.histogramArea.imgWidth = D_USER_YCC_WIDTH_PIXS;
		r2y_hist_ctrl.histogramArea.imgLines = D_USER_YCC_LINES_PIXS;

		im_r2y_ctrl(im_r2y_new(), ImR2yCtrl_PIPE1, &r2yCtrl );

		r2y_ctrl_direct.frameStop = 0;

		im_r2y3_ctrl_mode_direct(im_r2y3_new(),  ImR2yCtrl_PIPE1, &r2y_ctrl_direct );
		im_r2y2_set_resize_rect(im_r2y2_new(),  ImR2yCtrl_PIPE1, &r2y_resize_rect_param );
		im_r2y_set_out_bank_info(im_r2y_new(), ImR2yCtrl_PIPE1, D_IM_R2Y_YYW_0, &r2y_addr_0 );

		im_r2y3_ctrl_histogram(im_r2y3_new(),  ImR2yCtrl_PIPE1, r2y_hist_ctrl );

		// Start R2Y
		im_r2y_proc_start(im_r2y_proc_new(), ImR2yCtrl_PIPE1);
	}

	R2yHistogramStat view_hist_overflow_status;
	R2yHistogramAddr view_hist_dst_buf;
	void User_View_Handler( UINT32* status, UINT32 userParam )
	{
		switch( *status ) {
			case ImR2yCtrl_INT_FLG_YYW0_END1:
				// Finished create YCC image.
				im_r2y3_get_histogram(im_r2y3_new(),  ImR2yCtrl_PIPE1, &view_hist_overflow_status, &view_hist_dst_buf );
				break;
			default:
				// Nothing to do.
				break;
		}
	}
	@endcode
	<br><br>

@}*/	// weakgroup im_r2y

INT32 im_r2y_set_access_enable(ImR2y2 *self, kuint16 pipeNo, volatile R2yAccessEnableManage* const acc_en_mng, const kuint16 acc_enable, const kuint16 wait_enable, const CHAR errmsg[] );

void im_r2y2_loop_set(ImR2y2 *self, kuint16 loop_cnt);

void im_r2y2_sta_manage_init(ImR2y2 *self, kuint16 pipeNo, kuint16 size_coef);

/**
Set YYW parameter hold
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		hold_enable				: Parameter hold enable/disable
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y2_set_yyw_param_hold(ImR2y2 *self, kuint16 pipeNo, kuint16 hold_enable );

/**
R2Y pixel average reduction rectangle Control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_resize_rect_param	: Resize Rectangle Control information.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		Selecting normal format	: Set outputGlobalW in units of 8 bytes.<br>
				Selecting video format	: Set outputGlobalW in units of 128 bytes.
										  Setting this parameter to a negative value is prohibited.
*/
INT32 im_r2y2_set_resize_rect(ImR2y2 *self, kuint16 pipeNo, const R2yResizeRect* const r2y_resize_rect_param );

/**
R2Y resize pitch Control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2yResizePitch		: Resize Pitch Control information.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		Selecting normal format	: Set outputGlobalW in units of 8 bytes.<br>
				Selecting video format	: Set outputGlobalW in units of 128 bytes.
										  Setting this parameter to a negative value is prohibited.
*/
INT32 im_r2y2_set_resize_pitch(ImR2y2 *self, kuint16 pipeNo, const R2yResizePitch* const r2yResizePitch );

/**
R2Y get resize rectangle Control information.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2).
@param[out]		r2y_resize_param		: Resize Rectangle Control information.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y2_get_resize_param(ImR2y2 *self, kuint16 pipeNo, R2yResizeParam* const r2y_resize_param );

#endif /* __IM_R2Y2_H__ */
