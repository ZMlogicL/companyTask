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

#define im_r2y_yyw_is_activated(a)				(gIM_Io_R2y_Reg_Ptr[a]->YYW.YYWTRG.bit.YYWTRG != D_IM_R2Y_YYWTRG_IDLE)

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
	Im_r2y_init( D_IM_R2Y_PIPE12 );
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

	VOID User_Photo_Handler( UINT32* status, UINT32 user_param );

	VOID User_Capture_R2Y_Process( VOID ) {
		T_IM_R2Y_CTRL r2y_ctrl;
		T_IM_R2Y_CTRL_SDRAM_INPUT r2y_ctrl_sdram_in;
		T_IM_R2Y_RESIZE_RECT r2y_resize_rect_param;
		T_IM_R2Y_INADDR_INFO r2y_in_addr;
		T_IM_R2Y_OUTBANK_INFO r2y_addr_0;
		T_IM_R2Y_ERR_FLAG t_r2y_err_flg;

		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_Y] = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_CB] = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_CR] = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_Y] = 0;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_CB] = 0;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_CR] = 0;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].trim_out_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].planar_interleaved_mode = D_IM_R2Y_PORT_PLANAR;

		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.out_enable[D_IM_R2Y_PORT_Y] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.out_enable[D_IM_R2Y_PORT_CB] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.out_enable[D_IM_R2Y_PORT_CR] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].write_request_mask[D_IM_R2Y_PORT_Y] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].write_request_mask[D_IM_R2Y_PORT_CB] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].write_request_mask[D_IM_R2Y_PORT_CR] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;				// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].trim_out_enable = D_IM_R2Y_ENABLE_OFF;								// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].planar_interleaved_mode = D_IM_R2Y_PORT_PLANAR;						// dummy

		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0;		// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.out_enable[D_IM_R2Y_PORT_Y] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.out_enable[D_IM_R2Y_PORT_CB] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.out_enable[D_IM_R2Y_PORT_CR] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].write_request_mask[D_IM_R2Y_PORT_Y] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].write_request_mask[D_IM_R2Y_PORT_CB] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].write_request_mask[D_IM_R2Y_PORT_CR] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;				// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].trim_out_enable = D_IM_R2Y_ENABLE_OFF;								// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].planar_interleaved_mode = D_IM_R2Y_PORT_PLANAR;						// dummy

		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0;		// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.out_enable[D_IM_R2Y_PORT_Y] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.out_enable[D_IM_R2Y_PORT_CB] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.out_enable[D_IM_R2Y_PORT_CR] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].write_request_mask[D_IM_R2Y_PORT_Y] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].write_request_mask[D_IM_R2Y_PORT_CB] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].write_request_mask[D_IM_R2Y_PORT_CR] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;				// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;				// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].trim_out_enable = D_IM_R2Y_ENABLE_OFF;								// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].planar_interleaved_mode = D_IM_R2Y_PORT_PLANAR;					// dummy

		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_0].level = 0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_1].level = 0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_2].level = 0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_0].yyw_select = D_IM_R2Y_YYW_CH_0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_1].yyw_select = D_IM_R2Y_YYW_CH_0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_2].yyw_select = D_IM_R2Y_YYW_CH_0;

		r2y_ctrl.yyw_enable[D_IM_R2Y_YYW_CH_0] = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw_enable[D_IM_R2Y_YYW_CH_1] = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.yyw_enable[D_IM_R2Y_YYW_CH_2] = D_IM_R2Y_ENABLE_OFF;

		r2y_ctrl.line_transfer_cycle = 0;
		r2y_ctrl.yyw_continue_start_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.yyw_horizontal_flip = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.video_format_out_select_0 = D_IM_R2Y_VFM_NORMAL;
		r2y_ctrl.ipu_macro_output_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.ipu_macro_trimming_enable = D_IM_R2Y_ENABLE_OFF;	// dummy
		r2y_ctrl.cnr_macro_output_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.cnr_macro_trimming_enable = D_IM_R2Y_ENABLE_OFF;	// dummy
		r2y_ctrl.output_mode_0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP;
		r2y_ctrl.video_format_out_select_0a = D_IM_R2Y_VFM_NORMAL;	// dummy
		r2y_ctrl.output_format_sel1 = D_IM_R2Y_DATA_FORMAT_8;		// dummy
		r2y_ctrl.output_type_sel1 = D_IM_R2Y_WRITE_DTYP_PACK8;		// dummy
		r2y_ctrl.ycf_bypass = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.ycf_padding = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.mcc_select = D_IM_R2Y_MCC_AFTER_CC0;
		r2y_ctrl.mcc_bit_shift = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.r2y_user_handler = User_Photo_Handler;
		r2y_ctrl.user_param = 0;

		r2y_ctrl_sdram_in.burst_length = D_IM_R2Y_BRST_512;
		r2y_ctrl_sdram_in.read_request_mask[D_IM_R2Y_PORT_0] = 0;
		r2y_ctrl_sdram_in.read_request_mask[D_IM_R2Y_PORT_1] = 0;
		r2y_ctrl_sdram_in.read_request_mask[D_IM_R2Y_PORT_2] = 0;
		r2y_ctrl_sdram_in.input_dtype = D_IM_R2Y_READ_DTYP_PACK12;
		r2y_ctrl_sdram_in.mono_ebable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl_sdram_in.rgb_deknee_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl_sdram_in.rgb_left_shift = D_IM_R2Y_STL_RGB_LEFT_SHIFT_NONE;
		r2y_ctrl_sdram_in.rgb_saturation_mode = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.top_offset[D_IM_R2Y_PORT_Y] = 0;
		r2y_ctrl.top_offset[D_IM_R2Y_PORT_CB] = 0;
		r2y_ctrl.top_offset[D_IM_R2Y_PORT_CR] = 0;
		r2y_ctrl_sdram_in.input_global = D_USER_RGB_LINEFEED_BYTES;

		r2y_resize_rect_param.input_size.img_top = D_USER_YCC_TOP_X_PIXS;
		r2y_resize_rect_param.input_size.img_left = D_USER_YCC_TOP_Y_PIXS;
		r2y_resize_rect_param.input_size.img_width = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.input_size.img_lines = D_USER_YCC_LINES_PIXS;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0].yyw_width = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0].yyw_lines = D_USER_YCC_LINES_PIXS;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_Y] = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_1].yyw_width = D_USER_YCC_WIDTH_PIXS;									// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_1].yyw_lines = D_USER_YCC_LINES_PIXS;									// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_1].output_global_w[D_IM_R2Y_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_1].output_global_w[D_IM_R2Y_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;		// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_2].yyw_width = D_USER_YCC_WIDTH_PIXS;									// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_2].yyw_lines = D_USER_YCC_LINES_PIXS;									// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_2].output_global_w[D_IM_R2Y_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_2].output_global_w[D_IM_R2Y_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;		// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0A].yyw_width = D_USER_YCC_WIDTH_PIXS;								// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0A].yyw_lines = D_USER_YCC_LINES_PIXS;								// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0A].output_global_w[D_IM_R2Y_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0A].output_global_w[D_IM_R2Y_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;	// dummy

		r2y_in_addr.rgb.addr_R = (VOID*)D_USER_RAW_IN_ADDR_R;
		r2y_in_addr.rgb.addr_G = (VOID*)D_USER_RAW_IN_ADDR_G;
		r2y_in_addr.rgb.addr_B = (VOID*)D_USER_RAW_IN_ADDR_B;

		memset( &r2y_addr_0, '\x00', sizeof(r2y_addr_0) );
		r2y_addr_0.bank_initial_position = D_IM_R2Y_YYW_BANK_0;
		r2y_addr_0.use_bank_num = 3;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Y = (VOID*)D_USER_YCC_OUT_ADDR_Y;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cb = (VOID*)D_USER_YCC_OUT_ADDR_CB;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cr = (VOID*)D_USER_YCC_OUT_ADDR_CR;

		im_r2y_ctrl(im_r2y_new(), D_IM_R2Y_PIPE1, &r2y_ctrl );
		im_r2y_ctrl_mode_sdram_input(im_r2y_new(), D_IM_R2Y_PIPE1, &r2y_ctrl_sdram_in );
		im_r2y2_set_resize_rect(im_r2y2_new(),  D_IM_R2Y_PIPE1, &r2y_resize_rect_param );
		im_r2y_set_inaddr_info(im_r2y_new(), D_IM_R2Y_PIPE1, &r2y_in_addr );
		im_r2y_set_out_bank_info(im_r2y_new(), D_IM_R2Y_PIPE1, D_IM_R2Y_YYW_0, &r2y_addr_0 );

		// Start R2Y
		im_r2y_proc_start(im_r2y_proc_new(), D_IM_R2Y_PIPE1);

		// Wait R2Y YYW0 is normal end.
		im_r2y_proc_waitend(im_r2y_proc_new(),  NULL, D_IM_R2Y1_INT_FLG_YYW0_END, 60 );

		// Stop R2Y
		im_r2y_proc_stop(im_r2y_proc_new(), D_IM_R2Y_PIPE1);
	}

	T_IM_R2Y_HISTOGRAM_STAT photo_hist_overflow_status;
	T_IM_R2Y_HISTOGRAM_ADDR photo_hist_dst_buf;
	VOID User_Photo_Handler( UINT32* status, UINT32 user_param )
	{
		switch( *status ) {
			case D_IM_R2Y1_INT_FLG_YYW0_END:
				// Finished create YCC image.
				im_r2y3_get_histogram(im_r2y3_new(),  D_IM_R2Y_PIPE1, &photo_hist_overflow_status, &photo_hist_dst_buf );
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

	VOID User_View_Handler( UINT32* status, UINT32 user_param );

	VOID User_View_R2Y_Start( VOID ) {
		T_IM_R2Y_CTRL r2y_ctrl;
		T_IM_R2Y_CTRL_DIRECT r2y_ctrl_direct;
		T_IM_R2Y_RESIZE_RECT r2y_resize_rect_param;
		T_IM_R2Y_OUTBANK_INFO r2y_addr_0;
		T_IM_R2Y_CTRL_HISTOGRAM r2y_hist_ctrl;

		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_Y] = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_CB] = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_CR] = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_Y] = 0;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_CB] = 0;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_CR] = 0;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].trim_out_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0].planar_interleaved_mode = D_IM_R2Y_PORT_PLANAR;

		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.out_enable[D_IM_R2Y_PORT_Y] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.out_enable[D_IM_R2Y_PORT_CB] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].axi_write_mode.out_enable[D_IM_R2Y_PORT_CR] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].write_request_mask[D_IM_R2Y_PORT_Y] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].write_request_mask[D_IM_R2Y_PORT_CB] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].write_request_mask[D_IM_R2Y_PORT_CR] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;				// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].trim_out_enable = D_IM_R2Y_ENABLE_OFF;								// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_1].planar_interleaved_mode = D_IM_R2Y_PORT_PLANAR;						// dummy

		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0;		// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.out_enable[D_IM_R2Y_PORT_Y] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.out_enable[D_IM_R2Y_PORT_CB] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].axi_write_mode.out_enable[D_IM_R2Y_PORT_CR] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].write_request_mask[D_IM_R2Y_PORT_Y] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].write_request_mask[D_IM_R2Y_PORT_CB] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].write_request_mask[D_IM_R2Y_PORT_CR] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;				// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].trim_out_enable = D_IM_R2Y_ENABLE_OFF;								// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_2].planar_interleaved_mode = D_IM_R2Y_PORT_PLANAR;						// dummy

		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0;		// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.out_enable[D_IM_R2Y_PORT_Y] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.out_enable[D_IM_R2Y_PORT_CB] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].axi_write_mode.out_enable[D_IM_R2Y_PORT_CR] = D_IM_R2Y_ENABLE_ON;	// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].write_request_mask[D_IM_R2Y_PORT_Y] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].write_request_mask[D_IM_R2Y_PORT_CB] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].write_request_mask[D_IM_R2Y_PORT_CR] = 0;							// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;				// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;					// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;				// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].trim_out_enable = D_IM_R2Y_ENABLE_OFF;								// dummy
		r2y_ctrl.yyw[D_IM_R2Y_YYW_CH_0A].planar_interleaved_mode = D_IM_R2Y_PORT_PLANAR;					// dummy

		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_0].level = 0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_1].level = 0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_2].level = 0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_0].yyw_select = D_IM_R2Y_YYW_CH_0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_1].yyw_select = D_IM_R2Y_YYW_CH_0;
		r2y_ctrl.line_intr[D_IM_R2Y_LINE_INT_2].yyw_select = D_IM_R2Y_YYW_CH_0;

		r2y_ctrl.yyw_enable[D_IM_R2Y_YYW_CH_0] = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw_enable[D_IM_R2Y_YYW_CH_1] = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.yyw_enable[D_IM_R2Y_YYW_CH_2] = D_IM_R2Y_ENABLE_OFF;

		r2y_ctrl.line_transfer_cycle = 0;
		r2y_ctrl.yyw_continue_start_enable = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.yyw_horizontal_flip = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.video_format_out_select_0 = D_IM_R2Y_VFM_NORMAL;
		r2y_ctrl.ipu_macro_output_enable = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.ipu_macro_trimming_enable = D_IM_R2Y_ENABLE_OFF;	// dummy
		r2y_ctrl.cnr_macro_output_enable = D_IM_R2Y_ENABLE_ON;
		r2y_ctrl.cnr_macro_trimming_enable = D_IM_R2Y_ENABLE_OFF;	// dummy
		r2y_ctrl.output_mode_0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP;
		r2y_ctrl.video_format_out_select_0a = D_IM_R2Y_VFM_NORMAL;	// dummy
		r2y_ctrl.output_format_sel1 = D_IM_R2Y_DATA_FORMAT_8;		// dummy
		r2y_ctrl.output_type_sel1 = D_IM_R2Y_WRITE_DTYP_PACK8;		// dummy
		r2y_ctrl.ycf_bypass = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.ycf_padding = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.mcc_select = D_IM_R2Y_MCC_AFTER_CC0;
		r2y_ctrl.mcc_bit_shift = D_IM_R2Y_ENABLE_OFF;
		r2y_ctrl.r2y_user_handler = User_View_Handler;
		r2y_ctrl.user_param = 0;

		r2y_resize_rect_param.input_size.img_top = D_USER_YCC_TOP_X_PIXS;
		r2y_resize_rect_param.input_size.img_left = D_USER_YCC_TOP_Y_PIXS;
		r2y_resize_rect_param.input_size.img_width = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.input_size.img_lines = D_USER_YCC_LINES_PIXS;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0].yyw_width = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0].yyw_lines = D_USER_YCC_LINES_PIXS;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_Y] = D_USER_YCC_WIDTH_PIXS;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_1].yyw_width = D_USER_YCC_WIDTH_PIXS;									// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_1].yyw_lines = D_USER_YCC_LINES_PIXS;									// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_1].output_global_w[D_IM_R2Y_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_1].output_global_w[D_IM_R2Y_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;		// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_2].yyw_width = D_USER_YCC_WIDTH_PIXS;									// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_2].yyw_lines = D_USER_YCC_LINES_PIXS;									// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_2].output_global_w[D_IM_R2Y_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_2].output_global_w[D_IM_R2Y_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;		// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0A].yyw_width = D_USER_YCC_WIDTH_PIXS;								// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0A].yyw_lines = D_USER_YCC_LINES_PIXS;								// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0A].output_global_w[D_IM_R2Y_PORT_Y] = D_USER_YCC_WIDTH_PIXS;			// dummy
		r2y_resize_rect_param.output_size[D_IM_R2Y_YYW_CH_0A].output_global_w[D_IM_R2Y_PORT_CB] = D_USER_YCC_WIDTH_PIXS / 2;	// dummy

		memset( &r2y_addr_0, '\x00', sizeof(r2y_addr_0) );
		r2y_addr_0.bank_initial_position = D_IM_R2Y_YYW_BANK_0;
		r2y_addr_0.use_bank_num = 3;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Y  = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_0_Y;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cb = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_0_CB;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cr = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_0_CR;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Y  = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_1_Y;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Cb = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_1_CB;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_1].ycc.addr_Cr = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_1_CR;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Y  = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_2_Y;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Cb = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_2_CB;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_2].ycc.addr_Cr = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_2_CR;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Y  = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_3_Y;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Cb = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_3_CB;
		r2y_addr_0.output_addr[D_IM_R2Y_YYW_BANK_3].ycc.addr_Cr = (VOID*)D_USER_VIEW_YCC_OUT_ADDR_3_CR;

		r2y_hist_ctrl.enable = D_IM_R2Y_ENABLE_ON;
		r2y_hist_ctrl.yyw_no = D_IM_R2Y_YYW_CH_0;
		r2y_hist_ctrl.sampling_pitch = D_IM_R2Y_HIST_PIT_16X16;
		r2y_hist_ctrl.histogram_area.img_top = 0;
		r2y_hist_ctrl.histogram_area.img_left = 0;
		r2y_hist_ctrl.histogram_area.img_width = D_USER_YCC_WIDTH_PIXS;
		r2y_hist_ctrl.histogram_area.img_lines = D_USER_YCC_LINES_PIXS;

		im_r2y_ctrl(im_r2y_new(), D_IM_R2Y_PIPE1, &r2y_ctrl );

		r2y_ctrl_direct.frame_stop = 0;

		im_r2y3_ctrl_mode_direct(im_r2y3_new(),  D_IM_R2Y_PIPE1, &r2y_ctrl_direct );
		im_r2y2_set_resize_rect(im_r2y2_new(),  D_IM_R2Y_PIPE1, &r2y_resize_rect_param );
		im_r2y_set_out_bank_info(im_r2y_new(), D_IM_R2Y_PIPE1, D_IM_R2Y_YYW_0, &r2y_addr_0 );

		im_r2y3_ctrl_histogram(im_r2y3_new(),  D_IM_R2Y_PIPE1, r2y_hist_ctrl );

		// Start R2Y
		im_r2y_proc_start(im_r2y_proc_new(), D_IM_R2Y_PIPE1);
	}

	T_IM_R2Y_HISTOGRAM_STAT view_hist_overflow_status;
	T_IM_R2Y_HISTOGRAM_ADDR view_hist_dst_buf;
	VOID User_View_Handler( UINT32* status, UINT32 user_param )
	{
		switch( *status ) {
			case D_IM_R2Y1_INT_FLG_YYW0_END:
				// Finished create YCC image.
				im_r2y3_get_histogram(im_r2y3_new(),  D_IM_R2Y_PIPE1, &view_hist_overflow_status, &view_hist_dst_buf );
				break;
			default:
				// Nothing to do.
				break;
		}
	}
	@endcode
	<br><br>

@}*/	// weakgroup im_r2y

INT32 im_r2y_set_access_enable(ImR2y2 *self, UCHAR pipe_no, volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE* const acc_en_mng, const UCHAR acc_enable, const UCHAR wait_enable, const CHAR errmsg[] );

void im_r2y2_loop_set(ImR2y2 *self, UCHAR loop_cnt);

void im_r2y2_sta_manage_init(ImR2y2 *self, UCHAR pipe_no, UCHAR size_coef);

/**
Set YYW parameter hold
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		hold_enable				: Parameter hold enable/disable
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y2_set_yyw_param_hold(ImR2y2 *self, UCHAR pipe_no, UCHAR hold_enable );

/**
R2Y pixel average reduction rectangle Control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_resize_rect_param	: Resize Rectangle Control information.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@remarks		Selecting normal format	: Set output_global_w in units of 8 bytes.<br>
				Selecting video format	: Set output_global_w in units of 128 bytes.
										  Setting this parameter to a negative value is prohibited.
*/
INT32 im_r2y2_set_resize_rect(ImR2y2 *self, UCHAR pipe_no, const T_IM_R2Y_RESIZE_RECT* const r2y_resize_rect_param );

/**
R2Y resize pitch Control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_resize_pitch		: Resize Pitch Control information.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@remarks		Selecting normal format	: Set output_global_w in units of 8 bytes.<br>
				Selecting video format	: Set output_global_w in units of 128 bytes.
										  Setting this parameter to a negative value is prohibited.
*/
INT32 im_r2y2_set_resize_pitch(ImR2y2 *self, UCHAR pipe_no, const T_IM_R2Y_RESIZE_PITCH* const r2y_resize_pitch );

/**
R2Y get resize rectangle Control information.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2).
@param[out]		r2y_resize_param		: Resize Rectangle Control information.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y2_get_resize_param(ImR2y2 *self, UCHAR pipe_no, T_IM_R2Y_RESIZE_PARAM* const r2y_resize_param );

#endif /* __IM_R2Y2_H__ */
