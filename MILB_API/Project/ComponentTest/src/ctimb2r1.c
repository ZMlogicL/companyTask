/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ct_im_b2r.h"

#include "im_b2r.h"
#include "im_pro.h"
#include "im_pro_common.h"

#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

#include "jdsb2r.h"

#include <stdlib.h>
#include <string.h>

#include "ctimb2r.h"

#include "ctimb2r1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r1, ct_im_b2r1);
#define CT_IM_B2R1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r1Private,CT_TYPE_IM_B2R1))

struct _CtImB2r1Private
{

};

void ct_im_b2r1_handler_cb( kuint32* result, kuint32 user_param );


// TestBase table
 T_IM_B2R_CTRL gctImB2rCtrlBase = {
	.bayer_top_pixel = D_IM_B2R_TOP_PIXEL_R,

	.ybw = {
		.axi_write_mode = {
			.out_sel = D_IM_B2R_YBW_OUTPUT_RGB,
			.burst_length = D_IM_B2R_BRST_512,
		},
		.output_dtype = D_IM_B2R_STL_DTYP_PACK12,
		.write_request_mask[D_IM_B2R_PORT_R] = 0,
		.write_request_mask[D_IM_B2R_PORT_G] = 0,
		.write_request_mask[D_IM_B2R_PORT_B] = 0,
		.trim_out_enable = D_IM_B2R_ENABLE_OFF,
		.knee_enable = 1,
	},

	.line_intr = {
		.count = 0,
	},
	.ybw_continue_start_enable = D_IM_B2R_ENABLE_OFF,
	.deknee_enable = D_IM_B2R_ENABLE_OFF,
	.cia_bypass = D_IM_B2R_ENABLE_OFF,
	.cia_padding = D_IM_B2R_ENABLE_ON,
	.ext_out_en = D_IM_B2R_ENABLE_OFF,
	.ext_out_alarm = D_IM_B2R_EXT_OUT_ALARM_1LINE,
	.b2r_user_handler = ct_im_b2r1_handler_cb,
	.user_param = 0,
};
// TestBase table
 T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInBase = {
	.burst_length = D_IM_B2R_BRST_512,
	.read_request_mask = 0,
	.input_dtype = D_IM_B2R_STL_DTYP_PACK16,
	.top_offset = 0,
	.input_global = 2360 *2,
	.line_space = 0,
};

// T_IM_B2R_CTRL table for RAW input
 T_IM_B2R_CTRL gctImB2rCtrlRaw = {
	.bayer_top_pixel = D_IM_B2R_TOP_PIXEL_R,

	.ybw = {
		.axi_write_mode = {
			.out_sel = D_IM_B2R_YBW_OUTPUT_RGB,
			.burst_length = D_IM_B2R_BRST_512,
		},
		.output_dtype = D_IM_B2R_STL_DTYP_PACK8,
		.write_request_mask[D_IM_B2R_PORT_R] = 0,
		.write_request_mask[D_IM_B2R_PORT_G] = 0,
		.write_request_mask[D_IM_B2R_PORT_B] = 0,
		.trim_out_enable = D_IM_B2R_ENABLE_OFF,
		.knee_enable = 1,
	},

	.line_intr = {
		.count = 0,
	},
	.ybw_continue_start_enable = D_IM_B2R_ENABLE_OFF,
	.deknee_enable = D_IM_B2R_ENABLE_OFF,
	.cia_bypass = D_IM_B2R_ENABLE_OFF,
	.cia_padding = D_IM_B2R_ENABLE_ON,
	.ext_out_en = D_IM_B2R_ENABLE_OFF,
	.ext_out_alarm = D_IM_B2R_EXT_OUT_ALARM_1LINE,
	.b2r_user_handler = ct_im_b2r1_handler_cb,
	.user_param = 0,
};

// T_IM_B2R_CTRL_SDRAM_INPUT table for RAW 16bit input
 T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInRaw16bit = {
	.burst_length = D_IM_B2R_BRST_512,
	.read_request_mask = 0,
	.input_dtype = D_IM_B2R_STL_DTYP_PACK16,
	.top_offset = 0,
	.input_global = D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK,
	.line_space = 0,
};

// T_IM_B2R_CTRL_SDRAM_INPUT table for RAW 12bit input
 T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInRaw12bit = {
	.burst_length = D_IM_B2R_BRST_512,
	.read_request_mask = 0,
	.input_dtype = D_IM_B2R_STL_DTYP_PACK12,
	.top_offset = 0,
	.input_global = D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_12BIT_PACK,
	.line_space = 0,
};

// T_IM_B2R_CTRL_SDRAM_INPUT table for RAW 10bit input
 T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInRaw10bit = {
	.burst_length = D_IM_B2R_BRST_512,
	.read_request_mask = 0,
	.input_dtype = D_IM_B2R_STL_DTYP_PACK10,
	.top_offset = 0,
	.input_global = D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_10BIT_PACK,
	.line_space = 0,
};

// T_IM_B2R_CTRL_SDRAM_INPUT table for RAW 8bit input
 T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInRaw8bit = {
	.burst_length = D_IM_B2R_BRST_512,
	.read_request_mask = 0,
	.input_dtype = D_IM_B2R_STL_DTYP_PACK8,
	.top_offset = 0,
	.input_global = D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_8BIT_NONPACK,
	.line_space = 0,
};

// T_IM_B2R_RECT table for RGB P12
 T_IM_B2R_RECT gctImB2rRectParamOutRgbP12 = {
	.input_size.img_left = 0,
	.input_size.img_top = 0,
	.input_size.img_width = D_IM_B2R_SRC_IMG_PIXS_WIDTH,
	.input_size.img_lines = D_IM_B2R_SRC_IMG_PIXS_LINES,
	.output_size = {
		.output_global_w = D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_P12,
	},
};

// T_IM_B2R_RECT table for RGB U8
 T_IM_B2R_RECT gctImB2rRectParamOutRgbU8 = {
	.input_size.img_left = 0,
	.input_size.img_top = 0,
	.input_size.img_width = D_IM_B2R_SRC_IMG_PIXS_WIDTH,
	.input_size.img_lines = D_IM_B2R_SRC_IMG_PIXS_LINES,
	.output_size = {
		.output_global_w = D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U8,
	},
};

// T_IM_B2R_INADDR_INFO table for RAW input
 T_IM_B2R_INADDR_INFO gctImB2rInAddrRaw = {
	.raw.addr = NULL,
};

// T_IM_B2R_OUTBANK_INFO table for RGB output
 T_IM_B2R_OUTBANK_INFO gctImB2rOutAddrRgb = {
	.bank_initial_position = D_IM_B2R_YBW_BANK_0,
	.use_bank_num = D_IM_B2R_YBW_BANK_0,
	.output_addr[D_IM_B2R_YBW_BANK_0] = {
		.rgb.addr_R = NULL,
		.rgb.addr_G = NULL,
		.rgb.addr_B = NULL,
	},
};

// T_IM_B2R_CTRL_B2B_DIRECT table
T_IM_B2R_CTRL_B2B_DIRECT gctImB2rCtrlB2bDirect = {
	.even_line_start_timming = 1000,
	.frame_stop = 1,
};


// Deknee table.
 const UCHAR gctImB2rKneeTbl[D_IM_B2R_TABLE_MAX_RGB_KNEE] = {
	  0,   1,   1,   2,   2,   3,   3,   4,   4,   5,   5,   6,   6,   7,   8,  12,
	 16,  20,  24,  28,  32,  36,  40,  44,  48,  52,  56,  58,  60,  62,  64,  66,
	 68,  70,  72,  74,  76,  78,  80,  82,  84,  86,  88,  90,  92,  94,  96,  98,
	100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 119, 120, 121, 122, 123, 124,
	125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
	141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,
	157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
	173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188,
	189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204,
	205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220,
	221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 230, 231, 231, 232, 232, 233,
	233, 234, 234, 235, 235, 236, 236, 237, 237, 238, 238, 239, 239, 240, 240, 241,
	241, 242, 242, 243, 243, 243, 243, 244, 244, 244, 244, 245, 245, 245, 245, 246,
	246, 246, 246, 247, 247, 247, 247, 248, 248, 248, 248, 249, 249, 249, 249, 250,
	250, 250, 250, 251, 251, 251, 251, 251, 251, 252, 252, 252, 252, 252, 252, 253,
	253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255
};

static volatile BOOL S_GCT_IM_B2R_B2B_VD_FLG = FALSE;

/*
DECLS
*/
static void ctImB2rB2bPrchIntHandler_cb( T_CALLBACK_ID* cb_id, ULONG result, ULONG user_param );
static void ctImB2rB2bVdIntHandler_cb( T_CALLBACK_ID* cb_id, ULONG result, ULONG user_param );
static void ctImB2rWaitVdB2b( void );

static void ct_im_b2r1_constructor(CtImB2r1 *self) 
{
//	CtImB2r1Private *priv = CT_IM_B2R1_GET_PRIVATE(self);
}

static void ct_im_b2r1_destructor(CtImB2r1 *self) 
{
//	CtImB2r1Private *priv = CT_IM_B2R1_GET_PRIVATE(self);
}

/*
IMPL//todo
*/

static void ctImB2rB2bPrchIntHandler_cb( T_CALLBACK_ID* cb_id, ULONG result, ULONG user_param )
{
	Ddim_Print(( "PRch Int %u, %u, %u %lx, %lx\n", cb_id->unit_no, cb_id->block_type, cb_id->channel, result, user_param ));
}

static void ctImB2rB2bVdIntHandler_cb( T_CALLBACK_ID* cb_id, ULONG result, ULONG user_param )
{
	Ddim_Print(( "VD Int %u, %u, %u %lx, %lx\n", cb_id->unit_no, cb_id->block_type, cb_id->channel, result, user_param ));
	S_GCT_IM_B2R_B2B_VD_FLG = TRUE;
}

static void ctImB2rWaitVdB2b( void )
{
	kuint32 loopcnt;
#ifdef CO_DEBUG_ON_PC
	T_CALLBACK_ID cb_id = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};
#endif

	for( loopcnt = 0; S_GCT_IM_B2R_B2B_VD_FLG == FALSE; loopcnt++ ) {
		if( loopcnt >= 10 ) {
			Ddim_Print(( "B2B wait end timeout.\n" ));
			break;
		}

		DDIM_User_Dly_Tsk( 1 );
#ifdef CO_DEBUG_ON_PC
		ctImB2rB2bVdIntHandler_cb( &cb_id, 0, 0 );
#endif
	}

	S_GCT_IM_B2R_B2B_VD_FLG = FALSE;
}

/*
PUBLIC//todo
*/


 void ct_im_b2r1_handler_cb( kuint32* result, kuint32 user_param )
{
	if( ((*result) & D_IM_B2R1_INT_STATE_YBR_END) != 0 ) {
		Ddim_Print(( "B2R1 YBRch end. %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R1_INT_STATE_YBW_END) != 0 ) {
		Ddim_Print(( "B2R1 YBWch end. %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R1_INT_STATE_FB2R_END) != 0 ) {
		Ddim_Print(( "B2R1 F_B2R end. %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R1_INT_STATE_LINE_END) != 0 ) {
		Ddim_Print(( "B2R1 line end. %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R1_INT_STATE_YBR_ERR) != 0 ) {
		Ddim_Print(( "B2R1 YBRch error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R1_INT_STATE_YBW_ERR) != 0 ) {
		Ddim_Print(( "B2R1 YBWch error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R1_INT_STATE_AXR_ERR) != 0 ) {
		Ddim_Print(( "B2R1 AXR error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R1_INT_STATE_AXW_ERR) != 0 ) {
		Ddim_Print(( "B2R1 AXW error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R1_INT_STATE_CPERR_ERR) != 0 ) {
		Ddim_Print(( "B2R1 CP error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_YBR_END) != 0 ) {
		Ddim_Print(( "B2R2 YBRch end. %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_YBW_END) != 0 ) {
		Ddim_Print(( "B2R2 YBWch end. %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_FB2R_END) != 0 ) {
		Ddim_Print(( "B2R2 F_B2R end. %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_LINE_END) != 0 ) {
		Ddim_Print(( "B2R2 line end. %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_YBR_ERR) != 0 ) {
		Ddim_Print(( "B2R2 YBRch error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_YBW_ERR) != 0 ) {
		Ddim_Print(( "B2R2 YBWch error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_AXR_ERR) != 0 ) {
		Ddim_Print(( "B2R2 AXR error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_AXW_ERR) != 0 ) {
		Ddim_Print(( "B2R2 AXW error! %x\n", user_param ));
	}
	if( ((*result) & D_IM_B2R2_INT_STATE_CPERR_ERR) != 0 ) {
		Ddim_Print(( "B2R2 CP error! %x\n", user_param ));
	}
}


 void ct_im_b2r1_set_b2b( E_IM_PRO_UNIT_NUM unit_no )
{
	T_IM_PRO_B2BTOP_CTRL		b2b_ctrl;
	T_IM_PRO_PG_CTRL			pg_ctrl;
	T_IM_PRO_M2P_CTRL			m2p_ctrl;
	T_IM_PRO_PRCH_CTRL			pr_ctrl;
	T_IM_PRO_PRCH_AREA			pr_area = {
		.width = 640 * 1.5,				// bytes
		.height = 480 / 2,
		.global_width = 640 * 2 * 1.5,	// 12bit pack, Interlace
	};
	T_IM_PRO_INT_B2BTOP_CTRL	int_ctrl;
	T_IM_PRO_CALLBACK_CFG		callback_cfg;

	Im_PRO_B2BTOP_Init( unit_no );

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Dd_Top_Set_CLKSTOP10_B2B1CK( 1 );
	Dd_Top_Set_CLKSTOP12_B2B2CK( 1 );
	Dd_Top_Set_CLKSEL5_B2B1CLK( 0 );		// 300MHz
	Dd_Top_Set_CLKSEL7_B2B2CLK( 0 );		// 300MHz
	Dd_Top_Set_CLKSTOP10_B2B1CK( 0 );
	Dd_Top_Set_CLKSTOP12_B2B2CK( 0 );

	Ddim_Print(( "B2B1 CLK %u\n", Dd_Top_Get_CLKSEL5_B2B1CLK() ));
	Ddim_Print(( "B2B2 CLK %u\n", Dd_Top_Get_CLKSEL7_B2B2CLK() ));
#endif

	Im_PRO_B2BTOP_Control_Clock( unit_no, E_IM_PRO_B2BTOP_CLK_TYPE_B2BCLK, D_IM_PRO_CLOCK_ON, 1 );

	// B2BTOP(and PAT) settings
	b2b_ctrl.input_mode		= E_IM_PRO_B2BTOP_INPUT_MODE_REINPUT;
	b2b_ctrl.cag_target_sel	= E_IM_PRO_B2BTOP_CAG_TARGET_BLOCK_SRO;
	b2b_ctrl.first_pixel[0]	= E_IM_PRO_ORG_R;
	b2b_ctrl.first_pixel[1]	= E_IM_PRO_ORG_GB;
	Im_PRO_B2BTOP_Ctrl( unit_no, &b2b_ctrl );

	// PG settings
	pg_ctrl.mode				= E_IM_PRO_PG_MODE_2LINE;
	pg_ctrl.input_img_width		= D_IM_B2R_SRC_IMG_PIXS_WIDTH;
	pg_ctrl.input_img_lines		= D_IM_B2R_SRC_IMG_PIXS_LINES / 2;
	pg_ctrl.vertical_blanking	= 200;		// branking line after image
	pg_ctrl.horizontal_blanking	= 1000;		// branking line after image
	pg_ctrl.start_blanking		= 100;		// branking line before image
	Im_PRO_PG_Ctrl( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, &pg_ctrl );

	// M2P settings
	m2p_ctrl.data_type				= E_IM_PRO_M2P_DATA_TYPE_12BIT;
	m2p_ctrl.deknee_enable			= E_IM_PRO_M2P_DEKNEE_DIS;
	m2p_ctrl.shift_bit				= E_IM_PRO_M2P_SHIFT_0BIT;
	m2p_ctrl.shift_sat				= E_IM_PRO_M2P_SAT_NOCOMP;
	m2p_ctrl.bit_shift				= E_IM_PRO_M2P_BIT_SHIFT_L;
	m2p_ctrl.valid_bit_count		= 8;	// dummy
	m2p_ctrl.shift_value			= 0;
	m2p_ctrl.upper_limit_clip_value	= 0xFFFF;
	m2p_ctrl.lower_limit_clip_value	= 0;
	Im_PRO_M2P_Ctrl( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_M2P_0, &m2p_ctrl );
	Im_PRO_M2P_Ctrl( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_M2P_1, &m2p_ctrl );

	// PRch settings
	pr_ctrl.trans_mode		= E_IM_PRO_PRCH_BURST_512BYTE;
	pr_ctrl.req_threshold	= E_IM_PRO_PRCH_CNT_NOLIMIT;
	pr_ctrl.trans_to		= E_IM_PRO_PRCH_TRANS_IO_0;
	Im_PRO_PRch_Ctrl( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_0, &pr_ctrl );
	Im_PRO_PRch_Ctrl( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_1, &pr_ctrl );

	Im_PRO_PRch_Set_Addr( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_0, D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP );
	Im_PRO_PRch_Set_Addr( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_1, D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP + pr_area.global_width / 2 );

	Im_PRO_PRch_Set_Area( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_0, &pr_area );
	Im_PRO_PRch_Set_Area( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_1, &pr_area );

	int_ctrl.int_mode						= E_IM_PRO_INT_INTMD_OR;
	int_ctrl.vd_enable[0].interrupt_bit		= D_IM_PRO_B2BTOP_INT_VDE0;
	int_ctrl.vd_enable[0].permission_flg	= 1;
	int_ctrl.hd_enable[0].interrupt_bit		= 0;
	int_ctrl.hd_enable[0].permission_flg	= 0;
	int_ctrl.vd_enable[1].interrupt_bit		= D_IM_PRO_B2BTOP_INT_VDE1;
	int_ctrl.vd_enable[1].permission_flg	= 1;
	int_ctrl.hd_enable[1].interrupt_bit		= 0;
	int_ctrl.hd_enable[1].permission_flg	= 0;
	Im_PRO_B2BTOP_Interrupt_Ctrl( unit_no, &int_ctrl );

	callback_cfg.inthandler	= ctImB2rB2bVdIntHandler_cb;
	callback_cfg.user_param	= 0;
	Im_PRO_B2BTOP_Pipe_Set_VD_Int_Handler( unit_no, &callback_cfg );

	callback_cfg.inthandler	= ctImB2rB2bPrchIntHandler_cb;
	callback_cfg.user_param	= 0;
	Im_PRO_PRch_Set_Int_Handler( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_0, &callback_cfg );
	Im_PRO_PRch_Set_Int_Handler( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_1, &callback_cfg );

}

 void ct_im_b2r1_start_b2b( E_IM_PRO_UNIT_NUM unit_no )
{
	S_GCT_IM_B2R_B2B_VD_FLG = FALSE;

	Im_PRO_PRch_Start( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_0 );
	Im_PRO_PRch_Start( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_1 );
	Im_PRO_M2P_Set_PAEN( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_M2P_0, E_IM_PRO_M2P_PAEN_EN );
	Im_PRO_M2P_Set_PAEN( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_M2P_1, E_IM_PRO_M2P_PAEN_EN );
	Im_PRO_M2P_Start( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_M2P_0 );
	Im_PRO_M2P_Start( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_M2P_1 );

	Im_PRO_PG_Start( unit_no, E_IM_PRO_BLOCK_TYPE_B2B );
}

 void ct_im_b2r1_waitend_stop_b2b( E_IM_PRO_UNIT_NUM unit_no )
{
	ctImB2rWaitVdB2b();

	Im_PRO_PWch_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PWCH_0, 0 );
	Im_PRO_P2M_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_P2M_CH0, 0 );
	Im_PRO_PWch_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PWCH_1, 0 );
	Im_PRO_P2M_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_P2M_CH1, 0 );

	Im_PRO_PRch_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_0, 0 );
	Im_PRO_M2P_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_M2P_0, 0 );
	Im_PRO_PRch_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_PRCH_1, 0 );
	Im_PRO_M2P_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B, E_IM_PRO_M2P_1, 0 );

	ctImB2rWaitVdB2b();

	Im_PRO_PG_Stop( unit_no, E_IM_PRO_BLOCK_TYPE_B2B );
}

 void ct_im_b2r1_set_wb_gain( CtImB2r1* self )
{
	static T_IM_B2R_BAYER_COLOR im_b2r_wb_gain = {
		(USHORT)(1.67592592592593F * 0x100),	// R
		(USHORT)(1.94623655913978F * 0x100),	// B
		(USHORT)(1.0F * 0x100),	// Gr
		(USHORT)(1.0F * 0x100),	// Gb
	};
	kint32	im_ercd;
	im_ercd = Im_B2R_Set_WB_Gain( self->pipeNo, &im_b2r_wb_gain );
	if( im_ercd != D_DDIM_OK ) {
		Ddim_Print(( "Im_B2R_Set_WB_Gain() error=%d\n", im_ercd ));
	}
}

 void ct_im_b2r1_print_b2r_common_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.YBINTE = 0x%lx\n", IO_B2R_P1.B2R_CMN.YBINTE.word ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.YBINTF = 0x%lx\n", IO_B2R_P1.B2R_CMN.YBINTF.word ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.YBINTE = 0x%lx\n", IO_B2R_P2.B2R_CMN.YBINTE.word ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.YBINTF = 0x%lx\n", IO_B2R_P2.B2R_CMN.YBINTF.word ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_b2r_ybr_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 0x%x\n", IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG ));
	Ddim_Print(( "IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 0x%x\n", IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_b2r_ybw_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWTRG.bit.YBWTRG = 0x%x\n", IO_B2R_P1.YBW.YBWTRG.bit.YBWTRG ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWTRG.bit.YBWTRG = 0x%x\n", IO_B2R_P2.YBW.YBWTRG.bit.YBWTRG ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_b2r_ctrl_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXMD.bit.YBWDOS        = %u\n",   IO_B2R_P1.YBCH.YBWAXMD.bit.YBWDOS ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXMD.bit.YBWBL         = %u\n",   IO_B2R_P1.YBCH.YBWAXMD.bit.YBWBL ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWREQMSK.bit.YBWREQMSK_0 = 0x%x\n", IO_B2R_P1.YBCH.YBWREQMSK.bit.YBWREQMSK_0 ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWREQMSK.bit.YBWREQMSK_1 = 0x%x\n", IO_B2R_P1.YBCH.YBWREQMSK.bit.YBWREQMSK_1 ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWREQMSK.bit.YBWREQMSK_2 = 0x%x\n", IO_B2R_P1.YBCH.YBWREQMSK.bit.YBWREQMSK_2 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.ELNLV.bit.ELNLV        = 0x%x\n", IO_B2R_P1.B2R_CMN.ELNLV.bit.ELNLV ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.B2RMODE.bit.CIABYP     = 0x%x\n", IO_B2R_P1.B2R_CMN.B2RMODE.bit.CIABYP ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.B2RMODE.bit.CIAPDD     = 0x%x\n", IO_B2R_P1.B2R_CMN.B2RMODE.bit.CIAPDD ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.EXALMSL.bit.EXALMSL    = 0x%x\n", IO_B2R_P1.B2R_CMN.EXALMSL.bit.EXALMSL ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.YBR.YBRCTL.bit.PIXEL           = %u\n",   IO_B2R_P1.YBR.YBRCTL.bit.PIXEL ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWCTL.bit.YBWDTYP         = %u\n",   IO_B2R_P1.YBW.YBWCTL.bit.YBWDTYP ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWCTL.bit.YBWCSE          = %u\n",   IO_B2R_P1.YBW.YBWCTL.bit.YBWCSE ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWMD.bit.TRMEN            = %u\n",   IO_B2R_P1.YBW.YBWMD.bit.TRMEN ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWMD.bit.KNEEN            = %u\n",   IO_B2R_P1.YBW.YBWMD.bit.KNEEN ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXMD.bit.YBWDOS        = %u\n",   IO_B2R_P2.YBCH.YBWAXMD.bit.YBWDOS ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXMD.bit.YBWBL         = %u\n",   IO_B2R_P2.YBCH.YBWAXMD.bit.YBWBL ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWREQMSK.bit.YBWREQMSK_0 = 0x%x\n", IO_B2R_P2.YBCH.YBWREQMSK.bit.YBWREQMSK_0 ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWREQMSK.bit.YBWREQMSK_1 = 0x%x\n", IO_B2R_P2.YBCH.YBWREQMSK.bit.YBWREQMSK_1 ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWREQMSK.bit.YBWREQMSK_2 = 0x%x\n", IO_B2R_P2.YBCH.YBWREQMSK.bit.YBWREQMSK_2 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.ELNLV.bit.ELNLV        = 0x%x\n", IO_B2R_P2.B2R_CMN.ELNLV.bit.ELNLV ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.B2RMODE.bit.CIABYP     = 0x%x\n", IO_B2R_P2.B2R_CMN.B2RMODE.bit.CIABYP ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.B2RMODE.bit.CIAPDD     = 0x%x\n", IO_B2R_P2.B2R_CMN.B2RMODE.bit.CIAPDD ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.EXALMSL.bit.EXALMSL    = 0x%x\n", IO_B2R_P2.B2R_CMN.EXALMSL.bit.EXALMSL ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.YBR.YBRCTL.bit.PIXEL           = %u\n",   IO_B2R_P2.YBR.YBRCTL.bit.PIXEL ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWCTL.bit.YBWDTYP         = %u\n",   IO_B2R_P2.YBW.YBWCTL.bit.YBWDTYP ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWCTL.bit.YBWCSE          = %u\n",   IO_B2R_P2.YBW.YBWCTL.bit.YBWCSE ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWMD.bit.TRMEN            = %u\n",   IO_B2R_P2.YBW.YBWMD.bit.TRMEN ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWMD.bit.KNEEN            = %u\n",   IO_B2R_P2.YBW.YBWMD.bit.KNEEN ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.DINSEL.bit.B2BDIN    = %u\n",   IO_B2R_P1.B2R_CMN.DINSEL.bit.B2BDIN ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBRAXMD.bit.YBRBL       = %u\n",   IO_B2R_P1.YBCH.YBRAXMD.bit.YBRBL ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBRREQMSK.bit.YBRREQMSK = 0x%x\n", IO_B2R_P1.YBCH.YBRREQMSK.bit.YBRREQMSK ));
	Ddim_Print(( "IO_B2R_P1.YBR.YBRCTL.bit.YBRDTYP       = %u\n",   IO_B2R_P1.YBR.YBRCTL.bit.YBRDTYP ));
	Ddim_Print(( "IO_B2R_P1.YBR.YBRCTL.bit.DKNEN         = 0x%x\n", IO_B2R_P1.YBR.YBRCTL.bit.DKNEN ));
	Ddim_Print(( "IO_B2R_P1.YBR.YBROFS.bit.YBROFS        = %u\n",   IO_B2R_P1.YBR.YBROFS.bit.YBROFS ));
	Ddim_Print(( "IO_B2R_P1.YBR.YBRDEF.bit.YBRDEF        = 0x%x\n", IO_B2R_P1.YBR.YBRDEF.bit.YBRDEF ));
	Ddim_Print(( "IO_B2R_P1.YBR.YBRHBLNK.bit.YBRHBLNK    = 0x%x\n", IO_B2R_P1.YBR.YBRHBLNK.bit.YBRHBLNK ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.DINSEL.bit.B2BDIN    = %u\n",   IO_B2R_P2.B2R_CMN.DINSEL.bit.B2BDIN ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBRAXMD.bit.YBRBL       = %u\n",   IO_B2R_P2.YBCH.YBRAXMD.bit.YBRBL ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBRREQMSK.bit.YBRREQMSK = 0x%x\n", IO_B2R_P2.YBCH.YBRREQMSK.bit.YBRREQMSK ));
	Ddim_Print(( "IO_B2R_P2.YBR.YBRCTL.bit.YBRDTYP       = %u\n",   IO_B2R_P2.YBR.YBRCTL.bit.YBRDTYP ));
	Ddim_Print(( "IO_B2R_P2.YBR.YBRCTL.bit.DKNEN         = 0x%x\n", IO_B2R_P2.YBR.YBRCTL.bit.DKNEN ));
	Ddim_Print(( "IO_B2R_P2.YBR.YBROFS.bit.YBROFS        = %u\n",   IO_B2R_P2.YBR.YBROFS.bit.YBROFS ));
	Ddim_Print(( "IO_B2R_P2.YBR.YBRDEF.bit.YBRDEF        = 0x%x\n", IO_B2R_P2.YBR.YBRDEF.bit.YBRDEF ));
	Ddim_Print(( "IO_B2R_P2.YBR.YBRHBLNK.bit.YBRHBLNK    = 0x%x\n", IO_B2R_P2.YBR.YBRHBLNK.bit.YBRHBLNK ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_b2r_ctrl_modeb2bdirect_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.DINSEL.bit.B2BDIN = %u\n",   IO_B2R_P1.B2R_CMN.DINSEL.bit.B2BDIN ));
	Ddim_Print(( "IO_B2R_P1.YBR.DINELS.bit.DINELS     = 0x%x\n", IO_B2R_P1.YBR.DINELS.bit.DINELS ));
	Ddim_Print(( "IO_B2R_P1.YBR.DINCTL.bit.FRMSTP     = %u\n",   IO_B2R_P1.YBR.DINCTL.bit.FRMSTP ));
	Ddim_Print(( "IO_B2R_P1.YBR.DINHSTA               = %lu\n",  IO_B2R_P1.YBR.DINHSTA.word ));
	Ddim_Print(( "IO_B2R_P1.YBR.DINVSTA               = %lu\n",  IO_B2R_P1.YBR.DINVSTA.word ));
	Ddim_Print(( "IO_B2R_P1.YBR.DINHSIZ               = %lu\n",  IO_B2R_P1.YBR.DINHSIZ.word ));
	Ddim_Print(( "IO_B2R_P1.YBR.DINVSIZ               = %lu\n",  IO_B2R_P1.YBR.DINVSIZ.word ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.DINSEL.bit.B2BDIN = %u\n",   IO_B2R_P2.B2R_CMN.DINSEL.bit.B2BDIN ));
	Ddim_Print(( "IO_B2R_P2.YBR.DINELS.bit.DINELS     = 0x%x\n", IO_B2R_P2.YBR.DINELS.bit.DINELS ));
	Ddim_Print(( "IO_B2R_P2.YBR.DINCTL.bit.FRMSTP     = %u\n",   IO_B2R_P2.YBR.DINCTL.bit.FRMSTP ));
	Ddim_Print(( "IO_B2R_P2.YBR.DINHSTA               = %lu\n",  IO_B2R_P2.YBR.DINHSTA.word ));
	Ddim_Print(( "IO_B2R_P2.YBR.DINVSTA               = %lu\n",  IO_B2R_P2.YBR.DINVSTA.word ));
	Ddim_Print(( "IO_B2R_P2.YBR.DINHSIZ               = %lu\n",  IO_B2R_P2.YBR.DINHSIZ.word ));
	Ddim_Print(( "IO_B2R_P2.YBR.DINVSIZ               = %lu\n",  IO_B2R_P2.YBR.DINVSIZ.word ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_rect_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	// im_b2r_calc_ybr_address_sdram_input(), im_b2r_set_ybr_address_sdram_input(), Im_B2R_Set_InAddr_Info()
	Ddim_Print(( "IO_B2R_P1.YBR.YBRA.bit.YBRA     = %lx\n",    IO_B2R_P1.YBR.YBRA.bit.YBRA ));
	// im_b2r_calc_in_rect_sdram_input()
	Ddim_Print(( "IO_B2R_P1.YBR.YBRHSIZ           = %lu\n",    IO_B2R_P1.YBR.YBRHSIZ.word ));
	Ddim_Print(( "IO_B2R_P1.YBR.YBRVSIZ           = %lu\n",    IO_B2R_P1.YBR.YBRVSIZ.word ));
	// Im_B2R_Set_Rect()
	Ddim_Print(( "IO_B2R_P1.YBW.YBWDEF.bit.YBWDEF = %x(%d)\n", IO_B2R_P1.YBW.YBWDEF.bit.YBWDEF, IO_B2R_P1.YBW.YBWDEF.bit.YBWDEF ));

	Ddim_Print(( "\n" ));
	// im_b2r_calc_ybr_address_sdram_input(), im_b2r_set_ybr_address_sdram_input(), Im_B2R_Set_InAddr_Info()
	Ddim_Print(( "IO_B2R_P2.YBR.YBRA.bit.YBRA     = %lx\n",    IO_B2R_P2.YBR.YBRA.bit.YBRA ));
	// im_b2r_calc_in_rect_sdram_input()
	Ddim_Print(( "IO_B2R_P2.YBR.YBRHSIZ           = %lu\n",    IO_B2R_P2.YBR.YBRHSIZ.word ));
	Ddim_Print(( "IO_B2R_P2.YBR.YBRVSIZ           = %lu\n",    IO_B2R_P2.YBR.YBRVSIZ.word ));
	// Im_B2R_Set_Rect()
	Ddim_Print(( "IO_B2R_P2.YBW.YBWDEF.bit.YBWDEF = %x(%d)\n", IO_B2R_P2.YBW.YBWDEF.bit.YBWDEF, IO_B2R_P2.YBW.YBWDEF.bit.YBWDEF ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_trimming_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWTRMH.bit.TRMHSTA = %u\n", IO_B2R_P1.YBW.YBWTRMH.bit.TRMHSTA ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWTRMH.bit.TRMHSIZ = %u\n", IO_B2R_P1.YBW.YBWTRMH.bit.TRMHSIZ ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWTRMV.bit.TRMVSTA = %u\n", IO_B2R_P1.YBW.YBWTRMV.bit.TRMVSTA ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWTRMV.bit.TRMVSIZ = %u\n", IO_B2R_P1.YBW.YBWTRMV.bit.TRMVSIZ ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWTRMH.bit.TRMHSTA = %u\n", IO_B2R_P2.YBW.YBWTRMH.bit.TRMHSTA ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWTRMH.bit.TRMHSIZ = %u\n", IO_B2R_P2.YBW.YBWTRMH.bit.TRMHSIZ ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWTRMV.bit.TRMVSTA = %u\n", IO_B2R_P2.YBW.YBWTRMV.bit.TRMVSTA ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWTRMV.bit.TRMVSIZ = %u\n", IO_B2R_P2.YBW.YBWTRMV.bit.TRMVSIZ ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_other_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	// Other
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWCTL.bit.USEBANK  = %u\n",   IO_B2R_P1.YBW.YBWCTL.bit.USEBANK ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_0_0   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_0_0 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_1_0   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_1_0 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_2_0   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_2_0 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_0_1   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_0_1 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_1_1   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_1_1 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_2_1   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_2_1 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_0_2   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_0_2 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_1_2   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_1_2 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_2_2   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_2_2 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_0_3   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_0_3 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_1_3   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_1_3 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_2_3   = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_2_3 ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWBANK.bit.BANKPS  = %u\n",   IO_B2R_P1.YBW.YBWBANK.bit.BANKPS ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWBANK.bit.BANKSTS = %u\n",   IO_B2R_P1.YBW.YBWBANK.bit.BANKSTS ));
	Ddim_Print(( "IO_B2R_P1.YBW.YBWBANK.bit.BANKST  = %u\n",   IO_B2R_P1.YBW.YBWBANK.bit.BANKST ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWCTL.bit.USEBANK  = %u\n",   IO_B2R_P2.YBW.YBWCTL.bit.USEBANK ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_0_0   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_0_0 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_1_0   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_1_0 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_2_0   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_2_0 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_0_1   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_0_1 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_1_1   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_1_1 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_2_1   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_2_1 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_0_2   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_0_2 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_1_2   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_1_2 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_2_2   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_2_2 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_0_3   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_0_3 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_1_3   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_1_3 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_2_3   = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_2_3 ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWBANK.bit.BANKPS  = %u\n",   IO_B2R_P2.YBW.YBWBANK.bit.BANKPS ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWBANK.bit.BANKSTS = %u\n",   IO_B2R_P2.YBW.YBWBANK.bit.BANKSTS ));
	Ddim_Print(( "IO_B2R_P2.YBW.YBWBANK.bit.BANKST  = %u\n",   IO_B2R_P2.YBW.YBWBANK.bit.BANKST ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}

 void ct_im_b2r1_print_fb2r_ctrl_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "(F_B2R)\n" ));
	Ddim_Print(( "IO_B2R_P1.F_B2R.CNTL.CNTL.bit.TRG = %u\n",    IO_B2R_P1.F_B2R.CNTL.CNTL.bit.TRG ));
	Ddim_Print(( "IO_B2R_P1.F_B2R.CNTL.B2RINTE      = 0x%lx\n", IO_B2R_P1.F_B2R.CNTL.B2RINTE.word ));
	Ddim_Print(( "IO_B2R_P1.F_B2R.CNTL.B2RINTF      = 0x%lx\n", IO_B2R_P1.F_B2R.CNTL.B2RINTF.word ));
	Ddim_Print(( "IO_B2R_P1.F_B2R.CNTL.FLTAEN.CIAEN = 0x%x\n",  IO_B2R_P1.F_B2R.CNTL.FLTAEN.bit.CIAEN ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.F_B2R.CNTL.CNTL.bit.TRG = %u\n",    IO_B2R_P2.F_B2R.CNTL.CNTL.bit.TRG ));
	Ddim_Print(( "IO_B2R_P2.F_B2R.CNTL.B2RINTE      = 0x%lx\n", IO_B2R_P2.F_B2R.CNTL.B2RINTE.word ));
	Ddim_Print(( "IO_B2R_P2.F_B2R.CNTL.B2RINTF      = 0x%lx\n", IO_B2R_P2.F_B2R.CNTL.B2RINTF.word ));
	Ddim_Print(( "IO_B2R_P2.F_B2R.CNTL.FLTAEN.CIAEN = 0x%x\n",  IO_B2R_P2.F_B2R.CNTL.FLTAEN.bit.CIAEN ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}


 void ct_im_b2r1_print_axi_reg( void )
{
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBRAXCTL.bit.YBRCACHE   = %u\n", IO_B2R_P1.YBCH.YBRAXCTL.bit.YBRCACHE ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBRAXCTL.bit.YBRPROT    = %u\n", IO_B2R_P1.YBCH.YBRAXCTL.bit.YBRPROT ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_0 = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_0 ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_0  = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_0 ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_1 = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_1 ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_1  = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_1 ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_2 = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWCACHE_2 ));
	Ddim_Print(( "IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_2  = %u\n", IO_B2R_P1.YBCH.YBWAXCTL.bit.YBWPROT_2 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBRAXCTL.bit.YBRCACHE   = %u\n", IO_B2R_P2.YBCH.YBRAXCTL.bit.YBRCACHE ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBRAXCTL.bit.YBRPROT    = %u\n", IO_B2R_P2.YBCH.YBRAXCTL.bit.YBRPROT ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_0 = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_0 ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_0  = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_0 ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_1 = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_1 ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_1  = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_1 ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_2 = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWCACHE_2 ));
	Ddim_Print(( "IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_2  = %u\n", IO_B2R_P2.YBCH.YBWAXCTL.bit.YBWPROT_2 ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}


void ct_im_b2r1_printreg( void )
{
	ct_im_b2r1_print_b2r_common_reg();
	ct_im_b2r1_print_b2r_ybr_reg();
	ct_im_b2r1_print_b2r_ybw_reg();
	ct_im_b2r1_print_b2r_ctrl_reg();
	ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();
	ct_im_b2r1_print_b2r_ctrl_modeb2bdirect_reg();
	ct_im_b2r1_print_rect_reg();
	ct_im_b2r1_print_trimming_reg();
	ct_im_b2r1_print_other_reg();
	ct_im_b2r1_print_fb2r_ctrl_reg();
	ct_im_b2r1_print_axi_reg();


#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif
}

CtImB2r1* ct_im_b2r1_new(void) 
{
    CtImB2r1 *self = k_object_new_with_private(CT_TYPE_IM_B2R1, sizeof(CtImB2r1Private));
    return self;
}
