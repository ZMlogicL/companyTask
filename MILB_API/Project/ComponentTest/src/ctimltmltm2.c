/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm2类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#include <stdlib.h>
#include <string.h>
#include "ct_im_b2r.h"
#include "ct_im_ltm.h"
#include "im_b2r.h"
#include "im_ltm.h"
#include "im_r2y.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif
#include "jdsimg.h"
#include "jdsltm.h"

#include "ctimltmltm.h"
#include "ctimltmltm3.h"
#include "ctimltmltm4.h"
#include "ctimltmltm2.h"

G_DEFINE_TYPE(CtImLtmLtm2, ct_im_ltm_ltm2, G_TYPE_OBJECT);

#define CT_IM_LTM_LTM2_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_LTM_2, CtImLtmLtm2Private))

struct _CtImLtmLtm2Private
{
	CtImLtmLtm4 *ltm4;
};

static T_IM_LTM_LTM_CTRL_B2R_DIRECT S_GCT_IM_LTM_LTM2_CTRL_B2R_DIRECT_BASE =
{
		.input_rect =
		{
		.img_top = 0,
		.img_left = 0,
		.img_width = D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_WIDTH,
		.img_lines = D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_LINES,
	},
		.bypass = D_IM_LTM_ENABLE_OFF,
};
//变公有
T_IM_LTM_LTM_CTRL_BLEND gctImLtmLtmCtrlBlend =
{
	.ratio		= 8,
	.offset[0]	= 0,
	.offset[1]	= 0,
	.offset[2]	= 0,
	.offset[3]	= 0,
	.offset[4]	= 0,
	.offset[5]	= 0,
	.offset[6]	= 0,
	.offset[7]	= 4096,
	.gain[0]	= 0,
	.gain[1]	= 0,
	.gain[2]	= 0,
	.gain[3]	= 0,
	.gain[4]	= 0,
	.gain[5]	= 0,
	.gain[6]	= 0,
	.gain[7]	= 0,
	.border[0]	= 0,
	.border[1]	= 0,
	.border[2]	= 0,
	.border[3]	= 0,
	.border[4]	= 0,
	.border[5]	= 0,
	.border[6]	= 0,
	.border[7]	= 0,
	.mode		= 1,
};

static const guint16 CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[D_IM_LTM_TABLE_MAX_YLOG] =
{
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
static void 	ctImLtmLtmR2yIntHandler_cb(guint32* result, guint32 userParam);
static void 	ctImLtmLtmB2rIntHandler_cb(guint32* result, guint32 userParam);
static void 	ctImLtmLtmStartB2r(CtImLtmLtm2 *self);
static void 	ctImLtmLtmSetB2r(CtImLtmLtm2 *self);
static void 	ctImLtmLtmSetR2y(CtImLtmLtm2 *self);
static void 	ctImLtmLtmStartR2y(CtImLtmLtm2 *self);

static void ct_im_ltm_ltm2_class_init(CtImLtmLtm2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmLtm2Private));
}

static void ct_im_ltm_ltm2_init(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	priv->ltm4=NULL;
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImLtmLtm2 *self = (CtImLtmLtm2*)object;
//	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm2_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImLtmLtm2 *self = (CtImLtmLtm2*)object;
//	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm2_parent_class)->finalize(object);
}

static void ctImLtmLtmR2yIntHandler_cb(guint32* result, guint32 userParam)
{
	Ddim_Print(("R2Y Int %x, %x\n", *result, userParam));
}

static void ctImLtmLtmB2rIntHandler_cb(guint32* result, guint32 userParam)
{
	Ddim_Print(("B2R Int %x, %x\n", *result, userParam));
}

static void ctImLtmLtmStartB2r(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);

	Im_B2R_Start(priv->ltm4->pipeNo, D_IM_B2R_START_EXTERNAL_IF_ONLY);
}

static void ctImLtmLtmSetB2r(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	T_IM_B2R_CTRL b2rCtrl;
	T_IM_B2R_CTRL_SDRAM_INPUT b2rCtrlSdramIn;
	T_IM_B2R_RECT b2rRectParam;
	T_IM_B2R_INADDR_INFO b2rInAddr;
	static T_IM_B2R_BAYER_COLOR S_IM_B2R_WB_GAIN = {
		(guint16)(1.67592592592593F * 0x100),	// R
		(guint16)(1.94623655913978F * 0x100),	// B
		(guint16)(1.0F * 0x100),	// Gr
		(guint16)(1.0F * 0x100),	// Gb
	};

	IO_IMG.IMGPIPEPSW.bit.B2RCNC = 1;

	b2rCtrl.bayer_top_pixel                         			= D_IM_B2R_TOP_PIXEL_R;
	b2rCtrl.ybw.axi_write_mode.out_sel         	= D_IM_B2R_YBW_OUTPUT_RGB;
	b2rCtrl.ybw.axi_write_mode.burst_length	= D_IM_B2R_BRST_512;
	b2rCtrl.ybw.write_request_mask[D_IM_B2R_PORT_R] = 0;
	b2rCtrl.ybw.write_request_mask[D_IM_B2R_PORT_G] = 0;
	b2rCtrl.ybw.write_request_mask[D_IM_B2R_PORT_B] = 0;
	b2rCtrl.ybw.trim_out_enable             = D_IM_B2R_ENABLE_OFF;
	b2rCtrl.ybw.knee_enable                  	= 0;
	b2rCtrl.line_intr.count                       	= 0;
	b2rCtrl.ybw_continue_start_enable	= D_IM_B2R_ENABLE_OFF;
	b2rCtrl.deknee_enable                      	= D_IM_B2R_ENABLE_OFF;
	b2rCtrl.cia_bypass                              = D_IM_B2R_ENABLE_OFF;
	b2rCtrl.cia_padding                          	= D_IM_B2R_ENABLE_ON;
	b2rCtrl.ext_out_en                              = D_IM_B2R_ENABLE_ON;
	b2rCtrl.ext_out_alarm                        = D_IM_B2R_EXT_OUT_ALARM_1LINE;
	b2rCtrl.b2r_user_handler                  	= ctImLtmLtmB2rIntHandler_cb;
	b2rCtrl.user_param                          	= 0;

	b2rCtrlSdramIn.burst_length            = D_IM_B2R_BRST_512;
	b2rCtrlSdramIn.read_request_mask	= 0;
	b2rCtrlSdramIn.input_dtype             	= D_IM_B2R_STL_DTYP_PACK16;
	b2rCtrlSdramIn.top_offset              	= 0;
	b2rCtrlSdramIn.input_global         	= D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK;
	b2rCtrlSdramIn.line_space          	    = 0;

	b2rRectParam.input_size.img_left               		= 0;
	b2rRectParam.input_size.img_top               	 	= 0;
	b2rRectParam.input_size.img_width              	= D_IM_B2R_SRC_IMG_PIXS_WIDTH;
	b2rRectParam.input_size.img_lines              	= D_IM_B2R_SRC_IMG_PIXS_LINES;
	b2rRectParam.output_size.output_global_w 	= D_IM_B2R_IMG_MEM_OUT_RGB_U8_BYTES;	// dummy

	b2rInAddr.raw.addr                             				= (gpointer)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP;

	Im_B2R_Ctrl(priv->ltm4->pipeNo, &b2rCtrl);
	Im_B2R_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, &b2rCtrlSdramIn);
	Im_B2R_Ctrl_Left_Shift(priv->ltm4->pipeNo, 0, 0);
	Im_B2R_Set_Rect(priv->ltm4->pipeNo, &b2rRectParam);
	Im_B2R_Set_InAddr_Info(priv->ltm4->pipeNo, &b2rInAddr);
	Im_B2R_Set_WB_Gain(priv->ltm4->pipeNo, &S_IM_B2R_WB_GAIN);
}

static void ctImLtmLtmSetR2y(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	T_IM_R2Y_CTRL r2yCtrl;
	T_IM_R2Y_CTRL_DIRECT r2yCtrlDirect;
	T_IM_R2Y_RESIZE_RECT r2yResizeRectParam;
	T_IM_R2Y_OUTBANK_INFO r2yAddr0;
	static const guint16 CtImLtmLtm2_DGAMMA_ABS[D_IM_R2Y_TABLE_MAX_GAMMA] =
	{
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
	static const ULLONG CtImLtmLtm2_DGAMMA_OFS[D_IM_R2Y_TABLE_MAX_GAMMA] =
	{
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
	static const T_IM_R2Y_CTRL_GAMMA CtImLtmLtm2_R2Y_CTRL_GAMMA =
	{
			.gamma_enable = D_IM_R2Y_ENABLE_ON,
			.gamma_mode = D_IM_R2Y_GAMMA_MODE_12,
			.gamma_yb_tbl_simul = D_IM_R2Y_ENABLE_ON,
	};

	IO_IMG.IMGPIPEPSW.bit.R2YSEL = 1;

	memset(&r2yCtrl, '\0', sizeof(T_IM_R2Y_CTRL));
	memset(&r2yCtrlDirect, '\0', sizeof(T_IM_R2Y_CTRL_DIRECT));
	memset(&r2yResizeRectParam, '\0', sizeof(T_IM_R2Y_RESIZE_RECT));
	memset(&r2yAddr0, '\0', sizeof(T_IM_R2Y_OUTBANK_INFO));

	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.master_if_select = D_IM_R2Y_MASTER_IF0_PORT0 \
			| D_IM_R2Y_MASTER_IF0_PORT1 | D_IM_R2Y_MASTER_IF0_PORT2;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.burst_length = D_IM_R2Y_BRST_512;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_0] = D_IM_R2Y_ENABLE_ON;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_1] = D_IM_R2Y_ENABLE_ON;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].axi_write_mode.out_enable[D_IM_R2Y_PORT_2] = D_IM_R2Y_ENABLE_ON;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_0] = 0;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_1] = 0;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].write_request_mask[D_IM_R2Y_PORT_2] = 0;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].resize_mode = D_IM_R2Y_RSZ_BILINEAR;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].pixel_avg_reduction_mode = D_IM_R2Y_RDC_MODE_DIV_2;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].pixel_avg_reduction_enable = D_IM_R2Y_ENABLE_OFF;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].ycc_cc_thin_select = D_IM_R2Y_THIN_OUT_YCC422_CENTER;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].trim_out_enable = D_IM_R2Y_ENABLE_OFF;
	r2yCtrl.yyw[D_IM_R2Y_YYW_CH_0].planar_interleaved_mode = D_IM_R2Y_PORT_INTERLEAVED;
	r2yCtrl.yyw_enable[D_IM_R2Y_YYW_CH_0] = D_IM_R2Y_ENABLE_ON;
	r2yCtrl.yyw_continue_start_enable = D_IM_R2Y_ENABLE_ON;
	r2yCtrl.r2y_user_handler = ctImLtmLtmR2yIntHandler_cb;
	r2yCtrl.user_param = 0;

	r2yResizeRectParam.input_size.img_left = 0;
	r2yResizeRectParam.input_size.img_top = 0;
	r2yResizeRectParam.input_size.img_width = 640;
	r2yResizeRectParam.input_size.img_lines = 480;
	r2yResizeRectParam.output_size[D_IM_R2Y_YYW_CH_0].yyw_width = 640;
	r2yResizeRectParam.output_size[D_IM_R2Y_YYW_CH_0].yyw_lines = 480;
	r2yResizeRectParam.output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_Y] = 640;
	r2yResizeRectParam.output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_CBCR] = 640;
	r2yResizeRectParam.output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_2] = 0;	// dummy

	r2yAddr0.bank_initial_position = D_IM_R2Y_YYW_BANK_0;
	r2yAddr0.use_bank_num = D_IM_R2Y_YYW_BANK_0;
	r2yAddr0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Y  = (gpointer)D_IM_LTM_LTM_IMG_MEM_OUT_Y_ADDR_TOP;
	r2yAddr0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cb = (gpointer)D_IM_LTM_LTM_IMG_MEM_OUT_C_ADDR_TOP;
	r2yAddr0.output_addr[D_IM_R2Y_YYW_BANK_0].ycc.addr_Cr = 0;

	Im_R2Y_Ctrl(priv->ltm4->pipeNo, &r2yCtrl);
	Im_R2Y_Ctrl_ModeDirect(priv->ltm4->pipeNo, &r2yCtrlDirect);
	Im_R2Y_Set_Resize_Rect(priv->ltm4->pipeNo, &r2yResizeRectParam);
	Im_R2Y_Set_OutBankInfo(priv->ltm4->pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0);
	Im_R2Y_Ctrl_Gamma(priv->ltm4->pipeNo, &CtImLtmLtm2_R2Y_CTRL_GAMMA);
	Im_R2Y_Set_Gamma_Table(priv->ltm4->pipeNo, 0, CtImLtmLtm2_DGAMMA_ABS, CtImLtmLtm2_DGAMMA_OFS);
}

static void ctImLtmLtmStartR2y(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	Im_R2Y_Start(priv->ltm4->pipeNo);
	Im_R2Y_Set_FrameStop(priv->ltm4->pipeNo, 1);
}
/*
 *PUBLIC
 * */
void ct_im_ltm_ltm2_print_ctrl_sdram_input_reg(void)
{
	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRR   = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRR  ));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRG   = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRG  ));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRB   = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRB  ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRDEFR2.bit.SDRDEFR2 = 0x%x\n", IO_LTM_P1.LTM.LSDRDEFR2.bit.SDRDEFR2));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRHSZR2.bit.SDRHSZR2 = 0x%x\n", IO_LTM_P1.LTM.LSDRHSZR2.bit.SDRHSZR2));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRVSZR2.bit.SDRVSZR2 = 0x%x\n", IO_LTM_P1.LTM.LSDRVSZR2.bit.SDRVSZR2));
	Ddim_Print(("IO_LTM_P1.LTM.LIOCTL.bit.INSEL       = 0x%x\n", IO_LTM_P1.LTM.LIOCTL.bit.INSEL      ));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRR   = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRR  ));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRG   = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRG  ));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRB   = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRB  ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRDEFR2.bit.SDRDEFR2 = 0x%x\n", IO_LTM_P2.LTM.LSDRDEFR2.bit.SDRDEFR2));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRHSZR2.bit.SDRHSZR2 = 0x%x\n", IO_LTM_P2.LTM.LSDRHSZR2.bit.SDRHSZR2));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRVSZR2.bit.SDRVSZR2 = 0x%x\n", IO_LTM_P2.LTM.LSDRVSZR2.bit.SDRVSZR2));
	Ddim_Print(("IO_LTM_P2.LTM.LIOCTL.bit.INSEL       = 0x%x\n", IO_LTM_P2.LTM.LIOCTL.bit.INSEL      ));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
}
//变公有
void ct_im_ltm_ltm2_print_all_reg(void)
{
	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P1.LTM.LTMSR        = 0x%lx\n", IO_LTM_P1.LTM.LTMSR.word       ));
	Ddim_Print(("IO_LTM_P1.LTM.LSRAMEN      = 0x%lx\n", IO_LTM_P1.LTM.LSRAMEN.word     ));
	Ddim_Print(("IO_LTM_P1.LTM.LTRG         = 0x%lx\n", IO_LTM_P1.LTM.LTRG.word        ));
	Ddim_Print(("IO_LTM_P1.LTM.LFRSTP       = 0x%lx\n", IO_LTM_P1.LTM.LFRSTP.word      ));
	Ddim_Print(("IO_LTM_P1.LTM.LPARMSK      = 0x%lx\n", IO_LTM_P1.LTM.LPARMSK.word     ));
	Ddim_Print(("IO_LTM_P1.LTM.LINT0        = 0x%lx\n", IO_LTM_P1.LTM.LINT0.word       ));
	Ddim_Print(("IO_LTM_P1.LTM.LINT1        = 0x%lx\n", IO_LTM_P1.LTM.LINT1.word       ));
	Ddim_Print(("IO_LTM_P1.LTM.LLINTLV      = 0x%lx\n", IO_LTM_P1.LTM.LLINTLV.word     ));
	Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR1    = 0x%lx\n", IO_LTM_P1.LTM.LAXICTLR1.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR2    = 0x%lx\n", IO_LTM_P1.LTM.LAXICTLR2.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIRERR     = 0x%lx\n", IO_LTM_P1.LTM.LAXIRERR.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LAXICTLW     = 0x%lx\n", IO_LTM_P1.LTM.LAXICTLW.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIWERR     = 0x%lx\n", IO_LTM_P1.LTM.LAXIWERR.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ     = 0x%lx\n", IO_LTM_P1.LTM.LAXIBSIZ.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.AXIRSEL      = 0x%lx\n", IO_LTM_P1.LTM.AXIRSEL.word     ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRHSZR2    = 0x%lx\n", IO_LTM_P1.LTM.LSDRHSZR2.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRDEFR2    = 0x%lx\n", IO_LTM_P1.LTM.LSDRDEFR2.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRVSZR2    = 0x%lx\n", IO_LTM_P1.LTM.LSDRVSZR2.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2R    = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2R.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2G    = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2G.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2B    = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2B.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRHSZR3    = 0x%lx\n", IO_LTM_P1.LTM.LSDRHSZR3.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRDEFR3    = 0x%lx\n", IO_LTM_P1.LTM.LSDRDEFR3.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRVSZR3    = 0x%lx\n", IO_LTM_P1.LTM.LSDRVSZR3.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR3     = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR3.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRDEFR4    = 0x%lx\n", IO_LTM_P1.LTM.LSDRDEFR4.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR4     = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR4.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDROFS      = 0x%lx\n", IO_LTM_P1.LTM.LSDROFS.word     ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDWADR      = 0x%lx\n", IO_LTM_P1.LTM.LSDWADR.word     ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDWDEFR     = 0x%lx\n", IO_LTM_P1.LTM.LSDWDEFR.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDWADG      = 0x%lx\n", IO_LTM_P1.LTM.LSDWADG.word     ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDWDEFG     = 0x%lx\n", IO_LTM_P1.LTM.LSDWDEFG.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDWADB      = 0x%lx\n", IO_LTM_P1.LTM.LSDWADB.word     ));
	Ddim_Print(("IO_LTM_P1.LTM.LSDWDEFB     = 0x%lx\n", IO_LTM_P1.LTM.LSDWDEFB.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LIOCTL       = 0x%lx\n", IO_LTM_P1.LTM.LIOCTL.word      ));
	Ddim_Print(("IO_LTM_P1.LTM.LHSTA        = 0x%lx\n", IO_LTM_P1.LTM.LHSTA.word       ));
	Ddim_Print(("IO_LTM_P1.LTM.LHPIT        = 0x%lx\n", IO_LTM_P1.LTM.LHPIT.word       ));
	Ddim_Print(("IO_LTM_P1.LTM.LVSTA        = 0x%lx\n", IO_LTM_P1.LTM.LVSTA.word       ));
	Ddim_Print(("IO_LTM_P1.LTM.LVPIT        = 0x%lx\n", IO_LTM_P1.LTM.LVPIT.word       ));
	Ddim_Print(("IO_LTM_P1.LTM.NLVTHOF7     = 0x%lx\n", IO_LTM_P1.LTM.NLVTHOF7.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.PLVTHOF7     = 0x%lx\n", IO_LTM_P1.LTM.PLVTHOF7.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LYSHADOW     = 0x%lx\n", IO_LTM_P1.LTM.LYSHADOW.word    ));
	Ddim_Print(("IO_LTM_P1.LTM.LYHIGHLIGHT  = 0x%lx\n", IO_LTM_P1.LTM.LYHIGHLIGHT.word ));
	Ddim_Print(("IO_LTM_P1.LTM.BLDYRT       = 0x%lx\n", IO_LTM_P1.LTM.BLDYRT.word      ));
	Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF1 = 0x%lx\n", IO_LTM_P1.LTM.BLDOF.BLDOF1.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF2 = 0x%lx\n", IO_LTM_P1.LTM.BLDOF.BLDOF2.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF3 = 0x%lx\n", IO_LTM_P1.LTM.BLDOF.BLDOF3.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF4 = 0x%lx\n", IO_LTM_P1.LTM.BLDOF.BLDOF4.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA1 = 0x%lx\n", IO_LTM_P1.LTM.BLDGA.BLDGA1.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA2 = 0x%lx\n", IO_LTM_P1.LTM.BLDGA.BLDGA2.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA3 = 0x%lx\n", IO_LTM_P1.LTM.BLDGA.BLDGA3.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA4 = 0x%lx\n", IO_LTM_P1.LTM.BLDGA.BLDGA4.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD1 = 0x%lx\n", IO_LTM_P1.LTM.BLDBD.BLDBD1.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD2 = 0x%lx\n", IO_LTM_P1.LTM.BLDBD.BLDBD2.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD3 = 0x%lx\n", IO_LTM_P1.LTM.BLDBD.BLDBD3.word));
	Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD4 = 0x%lx\n", IO_LTM_P1.LTM.BLDBD.BLDBD4.word));
	Ddim_Print(("IO_LTM_P1.LTM.LTMMD        = 0x%lx\n", IO_LTM_P1.LTM.LTMMD.word       ));
	Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF1   = 0x%lx\n", IO_LTM_P1.LTM.CGOF.CGOF1.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF2   = 0x%lx\n", IO_LTM_P1.LTM.CGOF.CGOF2.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF3   = 0x%lx\n", IO_LTM_P1.LTM.CGOF.CGOF3.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF4   = 0x%lx\n", IO_LTM_P1.LTM.CGOF.CGOF4.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA1   = 0x%lx\n", IO_LTM_P1.LTM.CGGA.CGGA1.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA2   = 0x%lx\n", IO_LTM_P1.LTM.CGGA.CGGA2.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA3   = 0x%lx\n", IO_LTM_P1.LTM.CGGA.CGGA3.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA4   = 0x%lx\n", IO_LTM_P1.LTM.CGGA.CGGA4.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD1   = 0x%lx\n", IO_LTM_P1.LTM.CGBD.CGBD1.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD2   = 0x%lx\n", IO_LTM_P1.LTM.CGBD.CGBD2.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD3   = 0x%lx\n", IO_LTM_P1.LTM.CGBD.CGBD3.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD4   = 0x%lx\n", IO_LTM_P1.LTM.CGBD.CGBD4.word  ));
	Ddim_Print(("IO_LTM_P1.LTM.LYLCTL       = 0x%lx\n", IO_LTM_P1.LTM.LYLCTL.word      ));
	Ddim_Print(("IO_LTM_P1.LTM.LYLOG0EP0    = 0x%lx\n", IO_LTM_P1.LTM.LYLOG0EP0.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LYLOG0EP1    = 0x%lx\n", IO_LTM_P1.LTM.LYLOG0EP1.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LYLOG1EP0    = 0x%lx\n", IO_LTM_P1.LTM.LYLOG1EP0.word   ));
	Ddim_Print(("IO_LTM_P1.LTM.LYLOG1EP1    = 0x%lx\n", IO_LTM_P1.LTM.LYLOG1EP1.word   ));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LTMSR        = 0x%lx\n", IO_LTM_P2.LTM.LTMSR.word       ));
	Ddim_Print(("IO_LTM_P2.LTM.LSRAMEN      = 0x%lx\n", IO_LTM_P2.LTM.LSRAMEN.word     ));
	Ddim_Print(("IO_LTM_P2.LTM.LTRG         = 0x%lx\n", IO_LTM_P2.LTM.LTRG.word        ));
	Ddim_Print(("IO_LTM_P2.LTM.LFRSTP       = 0x%lx\n", IO_LTM_P2.LTM.LFRSTP.word      ));
	Ddim_Print(("IO_LTM_P2.LTM.LPARMSK      = 0x%lx\n", IO_LTM_P2.LTM.LPARMSK.word     ));
	Ddim_Print(("IO_LTM_P2.LTM.LINT0        = 0x%lx\n", IO_LTM_P2.LTM.LINT0.word       ));
	Ddim_Print(("IO_LTM_P2.LTM.LINT1        = 0x%lx\n", IO_LTM_P2.LTM.LINT1.word       ));
	Ddim_Print(("IO_LTM_P2.LTM.LLINTLV      = 0x%lx\n", IO_LTM_P2.LTM.LLINTLV.word     ));
	Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR1    = 0x%lx\n", IO_LTM_P2.LTM.LAXICTLR1.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR2    = 0x%lx\n", IO_LTM_P2.LTM.LAXICTLR2.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIRERR     = 0x%lx\n", IO_LTM_P2.LTM.LAXIRERR.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LAXICTLW     = 0x%lx\n", IO_LTM_P2.LTM.LAXICTLW.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIWERR     = 0x%lx\n", IO_LTM_P2.LTM.LAXIWERR.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ     = 0x%lx\n", IO_LTM_P2.LTM.LAXIBSIZ.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.AXIRSEL      = 0x%lx\n", IO_LTM_P2.LTM.AXIRSEL.word     ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRHSZR2    = 0x%lx\n", IO_LTM_P2.LTM.LSDRHSZR2.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRDEFR2    = 0x%lx\n", IO_LTM_P2.LTM.LSDRDEFR2.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRVSZR2    = 0x%lx\n", IO_LTM_P2.LTM.LSDRVSZR2.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2R    = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2R.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2G    = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2G.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2B    = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2B.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRHSZR3    = 0x%lx\n", IO_LTM_P2.LTM.LSDRHSZR3.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRDEFR3    = 0x%lx\n", IO_LTM_P2.LTM.LSDRDEFR3.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRVSZR3    = 0x%lx\n", IO_LTM_P2.LTM.LSDRVSZR3.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR3     = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR3.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRDEFR4    = 0x%lx\n", IO_LTM_P2.LTM.LSDRDEFR4.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR4     = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR4.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDROFS      = 0x%lx\n", IO_LTM_P2.LTM.LSDROFS.word     ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDWADR      = 0x%lx\n", IO_LTM_P2.LTM.LSDWADR.word     ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDWDEFR     = 0x%lx\n", IO_LTM_P2.LTM.LSDWDEFR.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDWADG      = 0x%lx\n", IO_LTM_P2.LTM.LSDWADG.word     ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDWDEFG     = 0x%lx\n", IO_LTM_P2.LTM.LSDWDEFG.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDWADB      = 0x%lx\n", IO_LTM_P2.LTM.LSDWADB.word     ));
	Ddim_Print(("IO_LTM_P2.LTM.LSDWDEFB     = 0x%lx\n", IO_LTM_P2.LTM.LSDWDEFB.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LIOCTL       = 0x%lx\n", IO_LTM_P2.LTM.LIOCTL.word      ));
	Ddim_Print(("IO_LTM_P2.LTM.LHSTA        = 0x%lx\n", IO_LTM_P2.LTM.LHSTA.word       ));
	Ddim_Print(("IO_LTM_P2.LTM.LHPIT        = 0x%lx\n", IO_LTM_P2.LTM.LHPIT.word       ));
	Ddim_Print(("IO_LTM_P2.LTM.LVSTA        = 0x%lx\n", IO_LTM_P2.LTM.LVSTA.word       ));
	Ddim_Print(("IO_LTM_P2.LTM.LVPIT        = 0x%lx\n", IO_LTM_P2.LTM.LVPIT.word       ));
	Ddim_Print(("IO_LTM_P2.LTM.NLVTHOF7     = 0x%lx\n", IO_LTM_P2.LTM.NLVTHOF7.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.PLVTHOF7     = 0x%lx\n", IO_LTM_P2.LTM.PLVTHOF7.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LYSHADOW     = 0x%lx\n", IO_LTM_P2.LTM.LYSHADOW.word    ));
	Ddim_Print(("IO_LTM_P2.LTM.LYHIGHLIGHT  = 0x%lx\n", IO_LTM_P2.LTM.LYHIGHLIGHT.word ));
	Ddim_Print(("IO_LTM_P2.LTM.BLDYRT       = 0x%lx\n", IO_LTM_P2.LTM.BLDYRT.word      ));
	Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF1 = 0x%lx\n", IO_LTM_P2.LTM.BLDOF.BLDOF1.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF2 = 0x%lx\n", IO_LTM_P2.LTM.BLDOF.BLDOF2.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF3 = 0x%lx\n", IO_LTM_P2.LTM.BLDOF.BLDOF3.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF4 = 0x%lx\n", IO_LTM_P2.LTM.BLDOF.BLDOF4.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA1 = 0x%lx\n", IO_LTM_P2.LTM.BLDGA.BLDGA1.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA2 = 0x%lx\n", IO_LTM_P2.LTM.BLDGA.BLDGA2.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA3 = 0x%lx\n", IO_LTM_P2.LTM.BLDGA.BLDGA3.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA4 = 0x%lx\n", IO_LTM_P2.LTM.BLDGA.BLDGA4.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD1 = 0x%lx\n", IO_LTM_P2.LTM.BLDBD.BLDBD1.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD2 = 0x%lx\n", IO_LTM_P2.LTM.BLDBD.BLDBD2.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD3 = 0x%lx\n", IO_LTM_P2.LTM.BLDBD.BLDBD3.word));
	Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD4 = 0x%lx\n", IO_LTM_P2.LTM.BLDBD.BLDBD4.word));
	Ddim_Print(("IO_LTM_P2.LTM.LTMMD        = 0x%lx\n", IO_LTM_P2.LTM.LTMMD.word       ));
	Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF1   = 0x%lx\n", IO_LTM_P2.LTM.CGOF.CGOF1.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF2   = 0x%lx\n", IO_LTM_P2.LTM.CGOF.CGOF2.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF3   = 0x%lx\n", IO_LTM_P2.LTM.CGOF.CGOF3.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF4   = 0x%lx\n", IO_LTM_P2.LTM.CGOF.CGOF4.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA1   = 0x%lx\n", IO_LTM_P2.LTM.CGGA.CGGA1.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA2   = 0x%lx\n", IO_LTM_P2.LTM.CGGA.CGGA2.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA3   = 0x%lx\n", IO_LTM_P2.LTM.CGGA.CGGA3.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA4   = 0x%lx\n", IO_LTM_P2.LTM.CGGA.CGGA4.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD1   = 0x%lx\n", IO_LTM_P2.LTM.CGBD.CGBD1.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD2   = 0x%lx\n", IO_LTM_P2.LTM.CGBD.CGBD2.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD3   = 0x%lx\n", IO_LTM_P2.LTM.CGBD.CGBD3.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD4   = 0x%lx\n", IO_LTM_P2.LTM.CGBD.CGBD4.word  ));
	Ddim_Print(("IO_LTM_P2.LTM.LYLCTL       = 0x%lx\n", IO_LTM_P2.LTM.LYLCTL.word      ));
	Ddim_Print(("IO_LTM_P2.LTM.LYLOG0EP0    = 0x%lx\n", IO_LTM_P2.LTM.LYLOG0EP0.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LYLOG0EP1    = 0x%lx\n", IO_LTM_P2.LTM.LYLOG0EP1.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LYLOG1EP0    = 0x%lx\n", IO_LTM_P2.LTM.LYLOG1EP0.word   ));
	Ddim_Print(("IO_LTM_P2.LTM.LYLOG1EP1    = 0x%lx\n", IO_LTM_P2.LTM.LYLOG1EP1.word   ));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
}

#undef CtImLtmLtm2_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm2_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm2_3_12: "
gint32 ct_im_ltm_ltm2_3_12(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_BLEND blendCtrl = self->gctImLtmLtmCtrlBlend;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm2_D_IM_LTM_FUNC_NAME));

	blendCtrl.mode = 1;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Blend(priv->ltm4->pipeNo, &blendCtrl);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00,
			&CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10,
			&CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Ctrl_Blend(priv->ltm4->pipeNo, &blendCtrl);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Start(priv->ltm4->pipeNo);
#endif

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm4->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm4->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm2_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm2_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm2_3_13: "
gint32 ct_im_ltm_ltm2_3_13(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_COMMON *ltmCtrlCommon = ct_im_ltm_ltm4_get1(priv->ltm4);
	T_IM_LTM_LTM_OUTDATA_INFO *ltmOutdataInfo = ct_im_ltm_ltm4_get5(priv->ltm4);
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm2_D_IM_LTM_FUNC_NAME));

	ltmCtrlCommon->out_data_type = D_IM_LTM_DTYP_PACK12;
	ltmOutdataInfo->global_width[0] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_P;
	ltmOutdataInfo->global_width[1] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_P;
	ltmOutdataInfo->global_width[2] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_P;
	ltmOutdataInfo->addr[1] = (gpointer)(D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP + \
			D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_P * D_IM_LTM_LTM_DST_IMG_PIXS_LINES);
	ltmOutdataInfo->addr[2] = (gpointer)(D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP + \
			D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_P * D_IM_LTM_LTM_DST_IMG_PIXS_LINES * 2);

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ltmCtrlCommon);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ltmOutdataInfo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00,
			&CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10,
			&CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ltmCtrlCommon);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ltmOutdataInfo);
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Start(priv->ltm4->pipeNo);
#endif

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm4->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm4->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm2_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm2_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm2_3_14: "
gint32 ct_im_ltm_ltm2_3_14(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm2_D_IM_LTM_FUNC_NAME));

	ctImLtmLtmSetB2r(self);

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeB2RDirect(priv->ltm4->pipeNo, &S_GCT_IM_LTM_LTM2_CTRL_B2R_DIRECT_BASE);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00,
			&CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10,
			&CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_FrameStop(priv->ltm4->pipeNo, D_IM_LTM_ENABLE_ON);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeB2RDirect(priv->ltm4->pipeNo, &S_GCT_IM_LTM_LTM2_CTRL_B2R_DIRECT_BASE);
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_FrameStop(priv->ltm4->pipeNo, D_IM_LTM_ENABLE_ON);
	Im_LTM_LTM_Start(priv->ltm4->pipeNo);
#endif

	ctImLtmLtmStartB2r(self);

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm4->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm4->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm2_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm2_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm2_3_15: "
gint32 ct_im_ltm_ltm2_3_15(CtImLtmLtm2 *self)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_B2R_DIRECT ltmCtrlDirect = S_GCT_IM_LTM_LTM2_CTRL_B2R_DIRECT_BASE;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm2_D_IM_LTM_FUNC_NAME));

	ltmCtrlDirect.bypass = 1;

	ctImLtmLtmSetB2r(self);

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeB2RDirect(priv->ltm4->pipeNo, &ltmCtrlDirect);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00,
			&CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10,
			&CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeB2RDirect(priv->ltm4->pipeNo, &ltmCtrlDirect);
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm2_GCT_IM_LTM_LTM_YLOG_TBL[0]);
#endif

	ctImLtmLtmSetR2y(self);
	ctImLtmLtmStartR2y(self);

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

#else
	Im_LTM_LTM_Start(priv->ltm4->pipeNo);
#endif

	ctImLtmLtmStartB2r(self);

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm4->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm4->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm2_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

void ct_im_ltm_ltm2_set_ltm4(CtImLtmLtm2 *self,CtImLtmLtm4 *ltm4)
{
	CtImLtmLtm2Private *priv = CT_IM_LTM_LTM2_GET_PRIVATE(self);
	priv->ltm4=ltm4;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmLtm2类的一个实例
 */
CtImLtmLtm2* ct_im_ltm_ltm2_new()
{
	CtImLtmLtm2 *self = g_object_new(CT_TYPE_IM_LTM_LTM_2,NULL);
	return self;
}
