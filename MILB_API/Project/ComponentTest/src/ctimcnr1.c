/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/
#include "im_cnr.h"
#include "dd_top.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "im_rdma.h"
#include "jdscnr.h"
#include "ctimcnr.h"
#include "ctimcnr1.h"
#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
#include "im_r2y.h"
#endif 

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr1, ct_im_cnr1, G_TYPE_OBJECT); 
#define CT_IM_CNR1_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR1, CtImCnr1Private))

struct _CtImCnr1Private
{
};

static void ctImR2ySetGammaOn(UCHAR ch);

static void ct_im_cnr1_constructor(CtImCnr1 *self) 
{
}

static void ct_im_cnr1_destructor(CtImCnr1 *self) 
{
}

#ifdef D_IM_R2Y_DEBUG_ON_PC
extern volatile UCHAR gIM_R2Y_macro_fake_finish[2];
#endif

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE

#define CtImCnr1_D_INPUT_IMG_RGB_R_ADDR			(0x60000000)
#define CtImCnr1_D_INPUT_IMG_RGB_G_ADDR			(CtImCnr1_D_INPUT_IMG_RGB_R_ADDR + 640 * 480 * 3 / 2)
#define CtImCnr1_D_INPUT_IMG_RGB_B_ADDR			(CtImCnr1_D_INPUT_IMG_RGB_G_ADDR + 640 * 480 * 3 / 2)
#define CtImCnr1_D_OUTPUT_IMG_YC422_Y_ADDR		(0x63000000)
#define CtImCnr1_D_OUTPUT_IMG_YC422_CB_ADDR		(CtImCnr1_D_OUTPUT_IMG_YC422_Y_ADDR + 640 * 480)
#define CtImCnr1_D_OUTPUT_IMG_YC422_CR_ADDR		(0x64000000)
#define CtImCnr1_D_IM_R2Y_SRC_IMG_PIXS_G_WIDTH	(960)	// 640*3/2
#define CtImCnr1_D_IM_R2Y_SRC_IMG_PIXS_WIDTH	(640)
#define CtImCnr1_D_IM_R2Y_SRC_IMG_PIXS_LINES	(480)

#define CtImCnr1_D_IM_R2Y_DST_IMG_PIXS_G_WIDTH	(640)
#define CtImCnr1_D_IM_R2Y_DST_IMG_PIXS_WIDTH	(640)
#define CtImCnr1_D_IM_R2Y_DST_IMG_PIXS_LINES	(480)

// TestBase table
static T_IM_R2Y_CTRL S_GCT_IM_R2Y_CTRL_BASE = {
	// D_IM_R2Y_YYW_CH_0: enable
	.yyw[D_IM_R2Y_YYW_CH_0] = {
		.axi_write_mode = {
			.master_if_select				= D_IM_R2Y_MASTER_IF0_PORT0 
												| D_IM_R2Y_MASTER_IF0_PORT1 
												| D_IM_R2Y_MASTER_IF0_PORT2,
			.burst_length					= D_IM_R2Y_BRST_512,
			.out_enable[D_IM_R2Y_PORT_0]	= D_IM_R2Y_ENABLE_ON,
			.out_enable[D_IM_R2Y_PORT_1]	= D_IM_R2Y_ENABLE_OFF,
			.out_enable[D_IM_R2Y_PORT_2]	= D_IM_R2Y_ENABLE_OFF,
		},
		.write_request_mask[D_IM_R2Y_PORT_0]	= 0,
		.write_request_mask[D_IM_R2Y_PORT_1]	= 0,
		.write_request_mask[D_IM_R2Y_PORT_2]	= 0,
		.resize_mode							= D_IM_R2Y_RSZ_BILINEAR,
		.pixel_avg_reduction_mode				= D_IM_R2Y_RDC_MODE_DIV_2,
		.pixel_avg_reduction_enable				= D_IM_R2Y_ENABLE_OFF,
		.ycc_cc_thin_select						= D_IM_R2Y_THIN_OUT_YCC422_CENTER,
		.trim_out_enable						= D_IM_R2Y_ENABLE_OFF,
		.planar_interleaved_mode				= D_IM_R2Y_PORT_INTERLEAVED,
	},
	// D_IM_R2Y_YYW_CH_1: disable
	.yyw[D_IM_R2Y_YYW_CH_1] = {
		.axi_write_mode = {
			.master_if_select				= D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2,
			.burst_length					= D_IM_R2Y_BRST_512,
			.out_enable[D_IM_R2Y_PORT_0]	= D_IM_R2Y_ENABLE_OFF,
			.out_enable[D_IM_R2Y_PORT_1]	= D_IM_R2Y_ENABLE_OFF,
			.out_enable[D_IM_R2Y_PORT_2]	= D_IM_R2Y_ENABLE_OFF,
		},
		.write_request_mask[D_IM_R2Y_PORT_0]	= 0,
		.write_request_mask[D_IM_R2Y_PORT_1]	= 0,
		.write_request_mask[D_IM_R2Y_PORT_2]	= 0,
		.resize_mode							= D_IM_R2Y_RSZ_BILINEAR,
		.pixel_avg_reduction_mode				= D_IM_R2Y_RDC_MODE_DIV_2,
		.pixel_avg_reduction_enable				= D_IM_R2Y_ENABLE_OFF,
		.ycc_cc_thin_select						= D_IM_R2Y_THIN_OUT_YCC420_CENTER,
		.trim_out_enable						= D_IM_R2Y_ENABLE_OFF,
		.planar_interleaved_mode				= D_IM_R2Y_PORT_INTERLEAVED,
	},
	// D_IM_R2Y_YYW_CH_2: enable
	.yyw[D_IM_R2Y_YYW_CH_2] = {
		.axi_write_mode = {
			.master_if_select				= D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2,
			.burst_length					= D_IM_R2Y_BRST_512,
			.out_enable[D_IM_R2Y_PORT_0]	= D_IM_R2Y_ENABLE_ON,
			.out_enable[D_IM_R2Y_PORT_1]	= D_IM_R2Y_ENABLE_OFF,
			.out_enable[D_IM_R2Y_PORT_2]	= D_IM_R2Y_ENABLE_OFF,
		},
		.write_request_mask[D_IM_R2Y_PORT_0]	= 0,
		.write_request_mask[D_IM_R2Y_PORT_1]	= 0,
		.write_request_mask[D_IM_R2Y_PORT_2]	= 0,
		.resize_mode							= D_IM_R2Y_RSZ_BILINEAR,
		.pixel_avg_reduction_mode				= D_IM_R2Y_RDC_MODE_DIV_2,
		.pixel_avg_reduction_enable				= D_IM_R2Y_ENABLE_OFF,
		.ycc_cc_thin_select						= D_IM_R2Y_THIN_OUT_YCC420_CENTER,
		.trim_out_enable						= D_IM_R2Y_ENABLE_OFF,
		.planar_interleaved_mode				= D_IM_R2Y_PORT_INTERLEAVED,
	},
	// D_IM_R2Y_YYW_CH_0A: disable
	.yyw[D_IM_R2Y_YYW_CH_0A] = {
		.axi_write_mode = {
			.master_if_select				= D_IM_R2Y_MASTER_IF0_PORT0 | D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2,
			.burst_length					= D_IM_R2Y_BRST_512,
			.out_enable[D_IM_R2Y_PORT_0]	= D_IM_R2Y_ENABLE_OFF,
			.out_enable[D_IM_R2Y_PORT_1]	= D_IM_R2Y_ENABLE_OFF,
			.out_enable[D_IM_R2Y_PORT_2]	= D_IM_R2Y_ENABLE_OFF,
		},
		.write_request_mask[D_IM_R2Y_PORT_0]	= 0,
		.write_request_mask[D_IM_R2Y_PORT_1]	= 0,
		.write_request_mask[D_IM_R2Y_PORT_2]	= 0,
		.resize_mode							= D_IM_R2Y_RSZ_BILINEAR,
		.pixel_avg_reduction_mode				= D_IM_R2Y_RDC_MODE_DIV_2,
		.pixel_avg_reduction_enable				= D_IM_R2Y_ENABLE_OFF,
		.ycc_cc_thin_select						= D_IM_R2Y_THIN_OUT_YCC420_CENTER,
		.trim_out_enable						= D_IM_R2Y_ENABLE_OFF,
		.planar_interleaved_mode				= D_IM_R2Y_PORT_INTERLEAVED,
	},

	.line_intr[D_IM_R2Y_LINE_INT_0] = {
		.level = 0,
		.yyw_select = D_IM_R2Y_YYW_CH_0,
	},
	.line_intr[D_IM_R2Y_LINE_INT_1] = {
		.level = 0,
		.yyw_select = D_IM_R2Y_YYW_CH_0,
	},
	.line_intr[D_IM_R2Y_LINE_INT_2] = {
		.level = 0,
		.yyw_select = D_IM_R2Y_YYW_CH_0,
	},

	.yyw_enable[D_IM_R2Y_YYW_CH_0]	= D_IM_R2Y_ENABLE_ON,
	.yyw_enable[D_IM_R2Y_YYW_CH_1]	= D_IM_R2Y_ENABLE_OFF,
	.yyw_enable[D_IM_R2Y_YYW_CH_2]	= D_IM_R2Y_ENABLE_OFF,
	.line_transfer_cycle			= 0,
	.yyw_continue_start_enable		= D_IM_R2Y_ENABLE_OFF,
	.yyw_horizontal_flip			= D_IM_R2Y_ENABLE_OFF,	// Flip OFF
	.video_format_out_select_0		= D_IM_R2Y_VFM_NORMAL,
	.ipu_macro_output_enable		= D_IM_R2Y_ENABLE_OFF,	// IPU output OFF
	.ipu_macro_trimming_enable		= D_IM_R2Y_ENABLE_OFF,
	.cnr_macro_output_enable		= D_IM_R2Y_ENABLE_ON,	// CNR output ON
	.cnr_macro_trimming_enable		= D_IM_R2Y_ENABLE_OFF,
	.output_mode_0a					= D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP,
	.video_format_out_select_0a		= D_IM_R2Y_VFM_NORMAL,
	.output_format_sel1				= D_IM_R2Y_DATA_FORMAT_8,
	.output_type_sel1				= D_IM_R2Y_WRITE_DTYP_PACK8,
	.ycf_bypass						= D_IM_R2Y_ENABLE_OFF,
	.ycf_padding					= D_IM_R2Y_ENABLE_ON,
	.mcc_select						= D_IM_R2Y_MCC_AFTER_CC0,
	.mcc_bit_shift					= D_IM_R2Y_ENABLE_OFF,
	.r2y_user_handler				= NULL,
	.user_param						= 0,
};

// T_IM_R2Y_CTRL_SDRAM_INPUT table for RGB 12bit input
static T_IM_R2Y_CTRL_SDRAM_INPUT S_GCT_IM_R2Y_CTRL_SDRAM_IN_RGB12BIT = {
	.burst_length						= D_IM_R2Y_BRST_512,
	.read_request_mask[D_IM_R2Y_PORT_0]	= 0,
	.read_request_mask[D_IM_R2Y_PORT_1]	= 0,
	.read_request_mask[D_IM_R2Y_PORT_2]	= 0,
	.input_dtype						= D_IM_R2Y_READ_DTYP_PACK12,
	.mono_ebable						= D_IM_R2Y_ENABLE_OFF,
	.rgb_deknee_enable					= D_IM_R2Y_ENABLE_OFF,
	.rgb_left_shift						= D_IM_R2Y_STL_RGB_LEFT_SHIFT_NONE,
	.rgb_saturation_mode				= D_IM_R2Y_ENABLE_OFF,
	.top_offset[D_IM_R2Y_PORT_0]		= 0,
	.top_offset[D_IM_R2Y_PORT_1]		= 0,
	.top_offset[D_IM_R2Y_PORT_2]		= 0,
	.input_global						= CtImCnr1_D_IM_R2Y_SRC_IMG_PIXS_G_WIDTH,
};

// T_IM_R2Y_RESIZE_RECT table for YC422 output
static T_IM_R2Y_RESIZE_RECT S_GCT_IM_R2Y_RESIZE_RECT_PARAM_OUT_YC422 = {
	.input_size.img_left	= 0,
	.input_size.img_top		= 0,
	.input_size.img_width	= CtImCnr1_D_IM_R2Y_SRC_IMG_PIXS_WIDTH,
	.input_size.img_lines	= CtImCnr1_D_IM_R2Y_SRC_IMG_PIXS_LINES,
	.output_size[D_IM_R2Y_YYW_CH_0] = {
		.yyw_width								= CtImCnr1_D_IM_R2Y_DST_IMG_PIXS_WIDTH,
		.yyw_lines								= CtImCnr1_D_IM_R2Y_DST_IMG_PIXS_LINES,
		.output_global_w[D_IM_R2Y_PORT_Y]		= CtImCnr1_D_IM_R2Y_DST_IMG_PIXS_G_WIDTH,
		.output_global_w[D_IM_R2Y_PORT_CBCR]	= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_2]		= 0,	// dummy
	},
	.output_size[D_IM_R2Y_YYW_CH_1] = {
		.yyw_width								= 0,	// dummy
		.yyw_lines								= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_Y]		= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_CBCR]	= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_2]		= 0,	// dummy
	},
	.output_size[D_IM_R2Y_YYW_CH_2] = {
		.yyw_width								= 0,	// dummy
		.yyw_lines								= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_Y]		= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_1]		= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_2]		= 0,	// dummy
	},
	.output_size[D_IM_R2Y_YYW_CH_0A] = {
		.yyw_width								= 0,	// dummy
		.yyw_lines								= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_Y]		= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_CBCR]	= 0,	// dummy
		.output_global_w[D_IM_R2Y_PORT_2]		= 0,	// dummy
	},
};

static T_IM_R2Y_RGB_COLOR S_IM_R2Y_WB_GAIN = {
	(USHORT)(1.0F * 0x100),	// R
	(USHORT)(1.0F * 0x100),	// G
	(USHORT)(1.0F * 0x100),	// B
};

static void ctImR2ySetGammaOn(UCHAR ch)
{
	static const USHORT C_DGAMMA_ABS[D_IM_R2Y_TABLE_MAX_GAMMA] = {
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
	static const ULLONG C_DGAMMA_OFS[D_IM_R2Y_TABLE_MAX_GAMMA] = {
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
	static const T_IM_R2Y_CTRL_GAMMA C_R2Y_CTRL_GAMMA = {
			.gamma_enable = D_IM_R2Y_ENABLE_ON,
			.gamma_mode = D_IM_R2Y_GAMMA_MODE_12,
			.gamma_yb_tbl_simul = D_IM_R2Y_ENABLE_ON,
	};
	INT32 ercd;

	ercd = Im_R2Y_Ctrl_Gamma(ch, &C_R2Y_CTRL_GAMMA);
	if(ercd != D_DDIM_OK) {
		Ddim_Print(("im_r2y_set_gamma Im_R2Y_Ctrl_Gamma ercd=%d\n", ercd));
	}
	ercd = Im_R2Y_Set_Gamma_Table(ch, 0, C_DGAMMA_ABS, C_DGAMMA_OFS);
	if(ercd != D_DDIM_OK) {
		Ddim_Print(("im_r2y_set_gamma Im_R2Y_Set_Gamma_Table ercd=%d\n", ercd));
	}
}

// input : RGB-12bit
// output: YC422
INT32 ct_im_cnr_set_im_r2y_set(CtImCnr1 *self)
{
	UCHAR ch = self->ch1;
	T_IM_R2Y_CTRL				r2yCtrl = S_GCT_IM_R2Y_CTRL_BASE;
	T_IM_R2Y_CTRL_SDRAM_INPUT	r2yCtrlSdramIn = S_GCT_IM_R2Y_CTRL_SDRAM_IN_RGB12BIT;
	T_IM_R2Y_RESIZE_RECT		r2yResizeRectParam = S_GCT_IM_R2Y_RESIZE_RECT_PARAM_OUT_YC422;
	T_IM_R2Y_CTRL_TRIMMING_EXT	r2yCtrlTrimming;
	T_IM_R2Y_INADDR_INFO		r2yInAddr;
	T_IM_R2Y_OUTBANK_INFO		r2yAddr0;
	INT32 ercd;

	Ddim_Print(("R2Y setting\n"));

	// output select
	r2yCtrl.yyw_enable[D_IM_R2Y_YYW_CH_0]	= D_IM_R2Y_ENABLE_ON;
	r2yCtrl.yyw_enable[D_IM_R2Y_YYW_CH_1]	= D_IM_R2Y_ENABLE_OFF;
	r2yCtrl.yyw_enable[D_IM_R2Y_YYW_CH_2]	= D_IM_R2Y_ENABLE_OFF;

	r2yCtrlTrimming.trimming_enable_b			= D_IM_R2Y_ENABLE_OFF;
	r2yCtrlTrimming.trimming_enable_c			= D_IM_R2Y_ENABLE_ON;
	r2yCtrlTrimming.trim_window_c.img_top		= 0;
	r2yCtrlTrimming.trim_window_c.img_left		= 0;
	r2yCtrlTrimming.trim_window_c.img_width		= 640;
	r2yCtrlTrimming.trim_window_c.img_lines		= 480;

	// Set address
	// input : RGB 12bit
	r2yInAddr.rgb.addr_R = (void*)CtImCnr1_D_INPUT_IMG_RGB_R_ADDR;
	r2yInAddr.rgb.addr_G = (void*)CtImCnr1_D_INPUT_IMG_RGB_G_ADDR;
	r2yInAddr.rgb.addr_B = (void*)CtImCnr1_D_INPUT_IMG_RGB_B_ADDR;
	// output : YC420 (set 1 bank)
	r2yAddr0.bank_initial_position	= D_IM_R2Y_YYW_BANK_0;
	r2yAddr0.use_bank_num				= D_IM_R2Y_YYW_BANK_0;
	r2yAddr0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Y	= (void*)CtImCnr_D_IM_CNR_TEST_IMG_DST_Y_ADDR;
	r2yAddr0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cb	= (void*)CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR;
	r2yAddr0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cr	= (void*)CtImCnr_D_IM_CNR_TEST_IMG_DST_CR_ADDR;

	ercd = Im_R2Y_Init(ch);
	Ddim_Print(("Im_R2Y_Init() : 0x%x\n", ercd));

	ercd = Im_R2Y_Ctrl(ch, &r2yCtrl);
	Ddim_Print(("Im_R2Y_Ctrl() : 0x%x\n", ercd));

	ercd = Im_R2Y_Ctrl_ModeSDRAMInput(ch, &r2yCtrlSdramIn);
	Ddim_Print(("Im_R2Y_Ctrl_ModeSDRAMInput() : 0x%x\n", ercd));

	ercd = Im_R2Y_Set_Resize_Rect(ch, &r2yResizeRectParam);
	Ddim_Print(("Im_R2Y_Set_Resize_Rect() : 0x%x\n", ercd));

	ercd = Im_R2Y_Ctrl_Trimming_External(ch, &r2yCtrlTrimming);
	Ddim_Print(("Im_R2Y_Ctrl_Trimming_External() : 0x%x\n", ercd));

	ercd = Im_R2Y_Set_InAddr_Info(ch, &r2yInAddr);
	Ddim_Print(("Im_R2Y_Set_InAddr_Info() : 0x%x\n", ercd));

	ercd = Im_R2Y_Set_OutBankInfo(ch, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Ddim_Print(("Im_R2Y_Set_OutBankInfo() : 0x%x\n", ercd));

	ercd = Im_R2Y_Set_WB_Gain(ch, &S_IM_R2Y_WB_GAIN);
	Ddim_Print(("Im_R2Y_Set_WB_Gain() : 0x%x\n", ercd));

	ctImR2ySetGammaOn(ch);

	return D_DDIM_OK;
}

INT32 ct_im_cnr_set_im_r2y_start(CtImCnr1 *self)
{
	UCHAR ch = self->ch1;
	INT32 ercd;

	Ddim_Print(("R2Y Start\n"));

#ifdef D_IM_R2Y_DEBUG_ON_PC
	if(ch == 0){
		gIM_R2Y_macro_fake_finish[0] = 1;
	}
	else if(ch == 1){
		gIM_R2Y_macro_fake_finish[1] = 1;
	}
	else{
		gIM_R2Y_macro_fake_finish[0] = 1;
		gIM_R2Y_macro_fake_finish[1] = 1;
	}
#endif

	ercd = Im_R2Y_Start(ch);
	Ddim_Print(("Im_R2Y_Start() : 0x%x\n", ercd));

	return D_DDIM_OK;
}

INT32 ct_im_cnr_set_im_r2y_stop(CtImCnr1 *self)
{
	UCHAR ch = self->ch1;
	DDIM_USER_FLGPTN flgptn = 0;
	INT32 ercd;

	if(ch == 0){
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
	}
	else if(ch == 1){
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
	else{
		flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
		flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
	}
	ercd = Im_R2Y_WaitEnd(NULL, flgptn, 3000);
	Ddim_Print(("Im_R2Y_WaitEnd() : 0x%x\n", ercd));

	ercd = Im_R2Y_Stop(ch);
	Ddim_Print(("Im_R2Y_Stop() : 0x%x\n", ercd));

#ifdef D_IM_R2Y_DEBUG_ON_PC
	gIM_R2Y_macro_fake_finish[0] = 0;
	gIM_R2Y_macro_fake_finish[1] = 0;
#endif

	Ddim_Print(("R2Y End\n"));

	return D_DDIM_OK;
}
#endif	// CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_1: "
INT32 ct_im_cnr_ofl_1_1(CtImCnr1 *self)
{
	UCHAR ch = self->ch1;

	INT32 imErcd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_IM_CNR_SEM_TIMEOUT_ERR) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", imErcd));
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_2: "
INT32 ct_im_cnr_ofl_1_2(CtImCnr1 *self)
{
	UCHAR ch = self->ch1;
	INT32 imErcd;
	DDIM_USER_ID sid_back;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	sid_back = SID_IM_CNR_OFL(ch);
	SID_IM_CNR_OFL(ch) = 0xfff;

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_IM_CNR_SEM_NG) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		Im_CNR_OFL_Close(ch);
		return imErcd;
	}

	SID_IM_CNR_OFL(ch) = sid_back;

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_3: "
INT32 ct_im_cnr_ofl_1_3(CtImCnr1 *self)
{
	UCHAR ch = self->ch1;
	INT32 imErcd;
	T_IM_CNR_OFL_CTRL sprCtrl = {
		.mode = E_IM_CNR_OFL_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.r_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_Y_ADDR,

		.r_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CB_ADDR,
		.r_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CR_ADDR,

		.w_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_Y_ADDR,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
		.w_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CR_ADDR,

		.work_addr = CtImCnr_D_IM_CNR_TEST_IMG_TMP_ADDR,

		.divide_top = E_IM_CNR_VPROCESS_NORM,
		.divide_bot = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};
	T_IM_CNR_OFL_CTRL_Y sprCtrlY = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0x1F,
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_Y(ch, &sprCtrlY);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_Y error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Start_Sync(ch, 10);
	if(imErcd != D_IM_CNR_SEM_TIMEOUT_ERR) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Sync error = 0x%x\n", imErcd));
		Im_CNR_OFL_Close(ch);
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_4: "
INT32 ct_im_cnr_ofl_1_4(CtImCnr1 *self)
{
	UCHAR ch = self->ch1;
	INT32 imErcd;
	UINT32 waitFactor;
	T_IM_CNR_OFL_CTRL sprCtrl = {
		.mode = E_IM_CNR_OFL_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.r_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_Y_ADDR,

		.r_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CB_ADDR,
		.r_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CR_ADDR,

		.w_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_Y_ADDR,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
		.w_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CR_ADDR,

		.work_addr = CtImCnr_D_IM_CNR_TEST_IMG_TMP_ADDR,

		.divide_top = E_IM_CNR_VPROCESS_NORM,
		.divide_bot = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};
	T_IM_CNR_OFL_CTRL_Y sprCtrlY = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0x1F,
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}
	Im_CNR_OFL_Init(ch);


	imErcd = Im_CNR_OFL_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_Y(ch, &sprCtrlY);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_Y error = 0x%x\n", imErcd));
		return imErcd;
	}

	Ddim_Print(("[Before Start]ch0 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_0)->OFL_REG_RW.ACESEN.bit.SPRACS));
	Ddim_Print(("[Before Start]ch1 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_1)->OFL_REG_RW.ACESEN.bit.SPRACS));

	imErcd = Im_CNR_OFL_Start_Async(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Async error = 0x%x\n", imErcd));
		return imErcd;
	}

	Ddim_Print(("[After Start]ch0 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_0)->OFL_REG_RW.ACESEN.bit.SPRACS));
	Ddim_Print(("[After Start]ch1 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_1)->OFL_REG_RW.ACESEN.bit.SPRACS));

#ifdef CO_DEBUG_ON_PC
	if(ch == D_IM_CNR_CH_2){
		io_cnr(D_IM_CNR_CH_0)->OFL_REG_RW.SPRICF.bit.__SPDF = 1;
		io_cnr(D_IM_CNR_CH_1)->OFL_REG_RW.SPRICF.bit.__SPDF = 1;
		Im_CNR0_Int_Handler();
		Im_CNR1_Int_Handler();
	}
	else{
		io_cnr(ch)->OFL_REG_RW.SPRICF.bit.__SPDF = 1;
		if(ch == D_IM_CNR_CH_0){
			Im_CNR0_Int_Handler();
		}
		else{
			Im_CNR1_Int_Handler();
		}
	}
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OFL_Wait_End(ch, &waitFactor, 1000);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Wait End error = 0x%x\n", imErcd));
		return imErcd;
	}

	Ddim_Print(("[After Stop]ch0 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_0)->OFL_REG_RW.ACESEN.bit.SPRACS));
	Ddim_Print(("[After Stop]ch1 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_1)->OFL_REG_RW.ACESEN.bit.SPRACS));

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_52: "
INT32 ct_im_cnr_ofl_1_52(CtImCnr1 *self)
{
	UCHAR ch = self->ch1;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL* C_CSPR_SPRS_CC_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRS_CC_Table(ch, &C_CSPR_SPRS_CC_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRS_CC_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_SPRS_CC_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_53: "
INT32 ct_im_cnr_ofl_1_53(CtImCnr1 *self)
{
	INT32 imErcd;
	T_IM_CNR_CTRL_CC_SRC_DST csprSprsCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
			.bd1 = 0x7F,
			.bd2 = 0x7F,
			.bd3 = 0x7F,
			.bd4 = 0x7F,
			.bd5 = 0x7F,
			.of0 = 0x7F,
			.of1 = 0x7F,
			.of2 = 0x7F,
			.of3 = 0x7F,
			.of4 = 0x7F,
			.of5 = 0x7F,
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
			.bd1 = 0x7F,
			.bd2 = 0x7F,
			.bd3 = 0x7F,
			.bd4 = 0x7F,
			.bd5 = 0x7F,
			.of0 = 0x7F,
			.of1 = 0x7F,
			.of2 = 0x7F,
			.of3 = 0x7F,
			.of4 = 0x7F,
			.of5 = 0x7F,
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRS_CC_TBL rdmaCsprSprsCc;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table(&csprSprsCc, &rdmaCsprSprsCc);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprSprsCc.SPRS               = 0x%lx\n", rdmaCsprSprsCc.SPRS.word));

	Ddim_Print(("rdmaCsprSprsCc.SPRSCBOF.SPRSCBOF1 = 0x%lx\n", rdmaCsprSprsCc.SPRSCBOF.SPRSCBOF1.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCBOF.SPRSCBOF2 = 0x%lx\n", rdmaCsprSprsCc.SPRSCBOF.SPRSCBOF2.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCBGA.SPRSCBGA1 = 0x%lx\n", rdmaCsprSprsCc.SPRSCBGA.SPRSCBGA1.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCBGA.SPRSCBGA2 = 0x%lx\n", rdmaCsprSprsCc.SPRSCBGA.SPRSCBGA2.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCBGA.SPRSCBGA3 = 0x%lx\n", rdmaCsprSprsCc.SPRSCBGA.SPRSCBGA3.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCBBD.SPRSCBBD1 = 0x%lx\n", rdmaCsprSprsCc.SPRSCBBD.SPRSCBBD1.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCBBD.SPRSCBBD2 = 0x%lx\n", rdmaCsprSprsCc.SPRSCBBD.SPRSCBBD2.word));

	Ddim_Print(("rdmaCsprSprsCc.SPRSCROF.SPRSCROF1 = 0x%lx\n", rdmaCsprSprsCc.SPRSCROF.SPRSCROF1.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCROF.SPRSCROF2 = 0x%lx\n", rdmaCsprSprsCc.SPRSCROF.SPRSCROF2.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCRGA.SPRSCRGA1 = 0x%lx\n", rdmaCsprSprsCc.SPRSCRGA.SPRSCRGA1.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCRGA.SPRSCRGA2 = 0x%lx\n", rdmaCsprSprsCc.SPRSCRGA.SPRSCRGA2.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCRGA.SPRSCRGA3 = 0x%lx\n", rdmaCsprSprsCc.SPRSCRGA.SPRSCRGA3.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCRBD.SPRSCRBD1 = 0x%lx\n", rdmaCsprSprsCc.SPRSCRBD.SPRSCRBD1.word));
	Ddim_Print(("rdmaCsprSprsCc.SPRSCRBD.SPRSCRBD2 = 0x%lx\n", rdmaCsprSprsCc.SPRSCRBD.SPRSCRBD2.word));

	return imErcd;
}

CtImCnr1* ct_im_cnr1_new(void) 
{
    CtImCnr1 *self = g_object_new(CT_TYPE_IM_CNR1, NULL);
    return self;
}
