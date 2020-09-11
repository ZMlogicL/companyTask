/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmMap3类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/
#include <stdlib.h>
#include <string.h>
#include "ct_im_ltm.h"
#include "im_ltm.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif
#include "jdsltm.h"

#include "ctimltmmap1.h"
#include "ctimltmmap2.h"
#include "ctimltmmap3.h"

G_DEFINE_TYPE(CtImLtmMap3, ct_im_ltm_map3, G_TYPE_OBJECT);

#define CT_IM_LTM_MAP_3_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_MAP_3, CtImLtmMap3Private))

struct _CtImLtmMap3Private
{
};

static T_IM_LTM_MAP_CTRL_SDRAM_INPUT S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE = {
	.burst_length = D_IM_LTM_BRST_512,
	.input_global = D_IM_LTM_MAP_SRC_IMG_GLOBAL_WIDTH_UP,
	.input_rect = {
		.img_top = 0,
		.img_left = 0,
		.img_width = D_IM_LTM_MAP_SRC_IMG_PIXS_WIDTH,
		.img_lines = D_IM_LTM_MAP_SRC_IMG_PIXS_LINES,
	},
	.data_type = D_IM_LTM_DTYP_UNPACK12,
};

static T_IM_LTM_MAP_INDATA_INFO S_GCT_IM_LTM_MAP_INDATA_BASE = {
	.addr = (gpointer)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP,
	.top_bit_offset = 0,
};
// TestBase table
static T_IM_LTM_MAP_CTRL_COMMON S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE = {
	.line_intr = 0,
	.wch_burst_length_yp = D_IM_LTM_BRST_512,
	.wch_burst_length_yn = D_IM_LTM_BRST_512,
	.mask_write_yp = D_IM_LTM_MASK_WRITE_ENABLE,
	.mask_write_yn = D_IM_LTM_MASK_WRITE_ENABLE,
	.write_select_yp = D_IM_LTM_PORT_DEFAULT,
	.write_select_yn = D_IM_LTM_PORT_DEFAULT,
	.data_type_yp = D_IM_LTM_DTYP_UNPACK12,
	.data_type_yn = D_IM_LTM_DTYP_UNPACK12,
	.map_user_handler = ct_im_ltm_map1_handler,
	.user_param = 0,
};

static T_IM_LTM_MAP_OUTDATA_INFO S_GCT_IM_LTM_MAP_OUTDATA_BASE = {
	.addr_yp = (gpointer)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP,
	.global_width_yp = D_IM_LTM_MAP_DST_IMG_GLOBAL_WIDTH_UP,
	.addr_yn = (gpointer)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP,
	.global_width_yn = D_IM_LTM_MAP_DST_IMG_GLOBAL_WIDTH_UP,
};

static T_IM_LTM_CTRL_YLOG S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL = {
	.use_tbl = 0,
	.end_point0_tbl0 = 0x3FFF,
	.end_point0_tbl1 = 0x3FFF,
	.end_point1_tbl0 = 0x3FFF,
	.end_point1_tbl1 = 0x3FFF,
};

const guint16 CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[D_IM_LTM_TABLE_MAX_YLOG] = {
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
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	ctImLtmMapRbkIntHandler_cb( guint32* result, guint32 userParam );
static void 	ctImLtmMapStartRbk( CtImLtmMap3 *self );
static void 	ctImLtmMapSetRbk( CtImLtmMap3 *self );

static void ct_im_ltm_map3_class_init(CtImLtmMap3Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmMap3Private));
}

static void ct_im_ltm_map3_init(CtImLtmMap3 *self)
{
//	CtImLtmMap3Private *priv = CT_IM_LTM_MAP_3_GET_PRIVATE(self);
}
//回调
static void ctImLtmMapRbkIntHandler_cb( guint32* result, guint32 userParam )
{
	Ddim_Print(( "RBK Int %x, %x\n", *result, userParam ));
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImLtmMap3 *self = (CtImLtmMap3*)object;
//	CtImLtmMap3Private *priv = CT_IM_LTM_MAP_3_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_map3_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImLtmMap3 *self = (CtImLtmMap3*)object;
//	CtImLtmMap3Private *priv = CT_IM_LTM_MAP_3_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_map3_parent_class)->finalize(object);
}

static void ctImLtmMapStartRbk( CtImLtmMap3 *self )
{
	Im_LTM_RBK_Start( self->pipeNo );
}

static void ctImLtmMapSetRbk( CtImLtmMap3 *self )
{
	T_IM_LTM_RBK_CTRL_COMMON rbkCtrlCommon;
	T_IM_LTM_RBK_CTRL_SDRAM_INPUT rbkCtrlSdramIn;
	T_IM_LTM_INADDR_INFO rbkInAddr;

	memset( &rbkCtrlCommon,   '\0', sizeof(T_IM_LTM_RBK_CTRL_COMMON)      );
	memset( &rbkCtrlSdramIn, '\0', sizeof(T_IM_LTM_RBK_CTRL_SDRAM_INPUT) );
	memset( &rbkInAddr,       '\0', sizeof(T_IM_LTM_INADDR_INFO)          );

	rbkCtrlCommon.out_select = D_IM_LTM_RBK_OUT_MAP_DIRECT;
	rbkCtrlCommon.rbk_user_handler = ctImLtmMapRbkIntHandler_cb;
	rbkCtrlCommon.user_param = 0;

	rbkCtrlSdramIn.input_global = D_IM_LTM_RBK_SRC_IMG_RGB_GLOBAL_WIDTH;
	rbkCtrlSdramIn.input_rect.img_width = D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH;
	rbkCtrlSdramIn.input_rect.img_lines = D_IM_LTM_RBK_SRC_IMG_PIXS_LINES;
	rbkCtrlSdramIn.shift_enable = D_IM_LTM_ENABLE_ON;

	rbkInAddr.addr_r = (gpointer)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP;
	rbkInAddr.addr_g = (gpointer)D_IM_LTM_RBK_IMG_MEM_IN_G_ADDR_TOP;
	rbkInAddr.addr_b = (gpointer)D_IM_LTM_RBK_IMG_MEM_IN_B_ADDR_TOP;

	Im_LTM_RBK_Ctrl_Common( self->pipeNo, &rbkCtrlCommon );
	Im_LTM_RBK_Ctrl_ModeSDRAMInput( self->pipeNo, &rbkCtrlSdramIn );
	Im_LTM_RBK_Set_InAddr_Info( self->pipeNo, &rbkInAddr );
}
/*
 * PUBLIC
 * */
#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_1_9: "
gint32 ct_im_ltm_map3_1_9( CtImLtmMap3 *self )
{
	guint32 loopCnt;
	T_IM_LTM_MAP_CTRL_SDRAM_INPUT mapCtrlSdramIn = S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE;
	T_IM_LTM_MAP_INDATA_INFO mapIndata[] = {
		[0] = { // max
			.addr = (gpointer)0xFFFFFFFF,
			.top_bit_offset = 1,
		},
		[1] = { // min
			.addr = (gpointer)0,
			.top_bit_offset = 0,
		},
		[2] = { // indvisual
			.addr = (gpointer)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP,
			.top_bit_offset = 1,
		},
	};
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &mapCtrlSdramIn );

	for( loopCnt = 0; loopCnt < (sizeof(mapIndata) / sizeof(mapIndata[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));
		Im_LTM_MAP_Set_InData_Info( self->pipeNo, &mapIndata[loopCnt] );
		ct_im_ltm_map1_print_ctrl_sdram_input_reg();
		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.MSDRAD.bit.SDRAD   = 0x%lx\n", IO_LTM_P1.MAP.MSDRAD.bit.SDRAD   ));
		Ddim_Print(( "IO_LTM_P1.MAP.MSDROFS.bit.SDROFS = 0x%x\n",  IO_LTM_P1.MAP.MSDROFS.bit.SDROFS ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.MSDRAD.bit.SDRAD   = 0x%lx\n", IO_LTM_P2.MAP.MSDRAD.bit.SDRAD   ));
		Ddim_Print(( "IO_LTM_P2.MAP.MSDROFS.bit.SDROFS = 0x%x\n",  IO_LTM_P2.MAP.MSDROFS.bit.SDROFS ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	mapCtrlSdramIn.input_rect.img_top = 100;
	mapCtrlSdramIn.input_rect.img_left = 200;

	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &mapCtrlSdramIn );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &mapIndata[2] );
	ct_im_ltm_map1_print_ctrl_sdram_input_reg();

	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "IO_LTM_P1.MAP.MSDRAD.bit.SDRAD   = 0x%lx\n", IO_LTM_P1.MAP.MSDRAD.bit.SDRAD   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDROFS.bit.SDROFS = 0x%x\n",  IO_LTM_P1.MAP.MSDROFS.bit.SDROFS ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDRAD.bit.SDRAD   = 0x%lx\n", IO_LTM_P2.MAP.MSDRAD.bit.SDRAD   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDROFS.bit.SDROFS = 0x%x\n",  IO_LTM_P2.MAP.MSDROFS.bit.SDROFS ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_2: "
gint32 ct_im_ltm_map3_3_2( CtImLtmMap3 *self )
{
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_4: "
gint32 ct_im_ltm_map3_3_4( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_GAIN	mapWbParam = {
		.gain_r = 0x100,
		.gain_g = 0x100,
		.gain_b = 0x100,
		.clip_r = 0xFFF,
		.clip_g = 0xFFF,
		.clip_b = 0xFFF,
	};
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_WB_Gain( self->pipeNo, &mapWbParam );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_WB_Gain( self->pipeNo, &mapWbParam );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_3: "
gint32 ct_im_ltm_map3_3_3( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_CTRL_SDRAM_INPUT mapCtrlSdramIn = S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	mapCtrlSdramIn.data_type = D_IM_LTM_DTYP_PACK12;
	mapCtrlSdramIn.input_global = D_IM_LTM_MAP_SRC_IMG_GLOBAL_WIDTH_P;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &mapCtrlSdramIn );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &mapCtrlSdramIn );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_5: "
gint32 ct_im_ltm_map3_3_5( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_GAIN	mapWbParam = {
		.gain_r = (guint16)(1.67592592592593F * 0x100),
		.gain_g = 0x100,
		.gain_b = (guint16)(1.94623655913978F * 0x100),
		.clip_r = 0xFFF,
		.clip_g = 0xFFF,
		.clip_b = 0xFFF,
	};
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_WB_Gain( self->pipeNo, &mapWbParam );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_WB_Gain( self->pipeNo, &mapWbParam );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_6: "
gint32 ct_im_ltm_map3_3_6( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_GAIN	mapWbParam = {
		.gain_r = 0x100,
		.gain_g = 0x100,
		.gain_b = 0x100,
		.clip_r = 0x400,
		.clip_g = 0x400,
		.clip_b = 0x400,
	};
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_WB_Gain( self->pipeNo, &mapWbParam );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_WB_Gain( self->pipeNo, &mapWbParam );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_7: "
gint32 ct_im_ltm_map3_3_7( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_CTRL_GENERATION_MODE	mapModeCtrl = {
		.mode0 = 0,
		.coef0 = 0x100,
		.mode1 = 0,
		.coef1 = 0x100,
		.mode2 = 0,
		.coef2 = 0x100,
	};
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Generation_Mode( self->pipeNo, &mapModeCtrl );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Ctrl_Generation_Mode( self->pipeNo, &mapModeCtrl );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_8: "
gint32 ct_im_ltm_map3_3_8( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_CTRL_GENERATION_MODE	mapModeCtrl = {
		.mode0 = 1,
		.coef0 = 0x100,
		.mode1 = 1,
		.coef1 = 0x100,
		.mode2 = 1,
		.coef2 = 0x100,
	};
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Generation_Mode( self->pipeNo, &mapModeCtrl );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Ctrl_Generation_Mode( self->pipeNo, &mapModeCtrl );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_9: "
gint32 ct_im_ltm_map3_3_9( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_CTRL_GENERATION_MODE	mapModeCtrl = {
		.mode0 = 0,
		.coef0 = 0xFFF,
		.mode1 = 0,
		.coef1 = 0xFFF,
		.mode2 = 0,
		.coef2 = 0xFFF,
	};
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Generation_Mode( self->pipeNo, &mapModeCtrl );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Ctrl_Generation_Mode( self->pipeNo, &mapModeCtrl );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_10: "
gint32 ct_im_ltm_map3_3_10( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_CTRL_GENERATION_MODE	mapModeCtrl = {
		.mode0 = 0,
		.coef0 = 0,
		.mode1 = 0,
		.coef1 = 0,
		.mode2 = 0,
		.coef2 = 0,
	};
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Generation_Mode( self->pipeNo, &mapModeCtrl );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Ctrl_Generation_Mode( self->pipeNo, &mapModeCtrl );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_12: "
gint32 ct_im_ltm_map3_3_12( CtImLtmMap3 *self )
{
	T_IM_LTM_MAP_CTRL_COMMON mapCtrlCommon = S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE;
	T_IM_LTM_MAP_OUTDATA_INFO mapOutdataParam = S_GCT_IM_LTM_MAP_OUTDATA_BASE;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	mapCtrlCommon.data_type_yp = D_IM_LTM_DTYP_PACK12;
	mapCtrlCommon.data_type_yn = D_IM_LTM_DTYP_PACK12;
	mapOutdataParam.global_width_yp = D_IM_LTM_MAP_DST_IMG_GLOBAL_WIDTH_P;
	mapOutdataParam.global_width_yn = D_IM_LTM_MAP_DST_IMG_GLOBAL_WIDTH_P;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &mapCtrlCommon );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &mapOutdataParam );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &mapCtrlCommon );
	Im_LTM_MAP_Ctrl_ModeSDRAMInput( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN_BASE );
	Im_LTM_MAP_Set_InData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_INDATA_BASE );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &mapOutdataParam );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map3_3_11: "
gint32 ct_im_ltm_map3_3_11( CtImLtmMap3 *self )
{
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ctImLtmMapSetRbk( self );

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_ModeRBKDirect( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Set_FrameStop( self->pipeNo, D_IM_LTM_ENABLE_ON );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Start( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_Ctrl_Common( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON_BASE );
	Im_LTM_MAP_Ctrl_ModeRBKDirect( self->pipeNo );
	Im_LTM_MAP_Set_OutData_Info( self->pipeNo, &S_GCT_IM_LTM_MAP_OUTDATA_BASE );
	Im_LTM_MAP_Ctrl_Ylog_Tbl( self->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_YLOG_TBL );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_YLOG_Table( self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap3_GCT_IM_LTM_MAP_YLOG_TBL[0] );
	Im_LTM_MAP_Set_FrameStop( self->pipeNo, D_IM_LTM_ENABLE_ON );
	Im_LTM_MAP_Start( self->pipeNo );
#endif

	ctImLtmMapStartRbk( self );

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP1_INT_FLG_MAP_END;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( self->pipeNo ) ){
		flgPtn |= D_IM_LTM_MAP2_INT_FLG_MAP_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
	ercd = Im_LTM_MAP_Stop( self->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_WaitEnd( NULL, flgPtn, 60 );
	Im_LTM_MAP_Stop( self->pipeNo );
#endif
	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}
/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmMap3类的一个实例
 */
CtImLtmMap3* ct_im_ltm_map3_new()
{
	CtImLtmMap3 *self = g_object_new(CT_TYPE_IM_LTM_MAP_3,NULL);
	return self;
}
