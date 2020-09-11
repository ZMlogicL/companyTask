/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm4类
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
#include "ctimltmltm2.h"
#include "ctimltmltm3.h"
#include "ctimltmltm4.h"

G_DEFINE_TYPE(CtImLtmLtm4, ct_im_ltm_ltm4, G_TYPE_OBJECT);

#define CT_IM_LTM_LTM4_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_LTM_4, CtImLtmLtm4Private))

struct _CtImLtmLtm4Private
{
	T_IM_LTM_LTM_CTRL_COMMON 			*gctImLtmLtmCtrlCommonBase;
	T_IM_LTM_LTM_CTRL_SDRAM_INPUT 	*gctImLtmLtmCtrlSdramInBase;
	T_IM_LTM_INADDR_INFO 						*gctImLtmLtmRgbInAddrBase;
	T_IM_LTM_LTM_INDATA_INFO 				*gctImLtmLtmIndataBase;
	T_IM_LTM_LTM_OUTDATA_INFO 			*gctImLtmLtmOutdataBase;
	T_IM_LTM_CTRL_YLOG 							*gctImLtmLtmCtrlYlogTbl;
};

static void 	ctImLtmLtmHandler_cb(guint32* result, guint32 userParam);

//变公有
// TestBase table
T_IM_LTM_LTM_CTRL_COMMON gctImLtmLtmCtrlCommonBase =
{
	.line_intr = 0,
	.rch_burst_length_yp = D_IM_LTM_BRST_512,
	.rch_burst_length_yn = D_IM_LTM_BRST_512,
	.wch_burst_length_r = D_IM_LTM_BRST_512,
	.wch_burst_length_g = D_IM_LTM_BRST_512,
	.wch_burst_length_b = D_IM_LTM_BRST_512,
	.mask_write_r = D_IM_LTM_MASK_WRITE_ENABLE,
	.mask_write_g = D_IM_LTM_MASK_WRITE_ENABLE,
	.mask_write_b = D_IM_LTM_MASK_WRITE_ENABLE,
	.read_select_yp = D_IM_LTM_PORT_DEFAULT,
	.read_select_yn = D_IM_LTM_PORT_DEFAULT,
	.in_data_type_yp = D_IM_LTM_DTYP_UNPACK12,
	.in_data_type_yn = D_IM_LTM_DTYP_UNPACK12,
	.out_select =  D_IM_LTM_LTM_OUT_SDRAM,
	.out_data_type = D_IM_LTM_DTYP_UNPACK12,
	.input_rect =
	{
		.img_top = 0,
		.img_left = 0,
		.img_width = D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH,
		.img_lines = D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_LINES,
	},
	.global_width_yp = D_IM_LTM_LTM_SRC_IMG_MAP_GLOBAL_WIDTH_UP,
	.global_width_yn = D_IM_LTM_LTM_SRC_IMG_MAP_GLOBAL_WIDTH_UP,
	.ltm_user_handler = ctImLtmLtmHandler_cb,
	.user_param = 0,
};
//变公有
T_IM_LTM_LTM_CTRL_SDRAM_INPUT gctImLtmLtmCtrlSdramInBase =
{
	.rch_burst_length_r = D_IM_LTM_BRST_512,
	.rch_burst_length_g = D_IM_LTM_BRST_512,
	.rch_burst_length_b = D_IM_LTM_BRST_512,
	.input_global_rgb = D_IM_LTM_LTM_SRC_IMG_RGB_GLOBAL_WIDTH,
	.input_rect =
	{
		.img_top = 0,
		.img_left = 0,
		.img_width = D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_WIDTH,
		.img_lines = D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_LINES,
	},
};
//变公有
T_IM_LTM_INADDR_INFO gctImLtmLtmRgbInAddrBase =
{
	.addr_r = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,
	.addr_g = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_G_ADDR_TOP,
	.addr_b = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_B_ADDR_TOP,
};
//变公有
T_IM_LTM_LTM_INDATA_INFO gctImLtmLtmIndataBase =
{
	.addr_yp = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP,
	.addr_yn = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP,
	.top_bit_offset_yp = 0,
	.top_bit_offset_yn = 0,
};
//变公有
T_IM_LTM_LTM_OUTDATA_INFO gctImLtmLtmOutdataBase =
{
	.addr[0] = (gpointer)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP,
	.addr[1] = (gpointer)D_IM_LTM_LTM_IMG_MEM_OUT_G_ADDR_TOP,
	.addr[2] = (gpointer)D_IM_LTM_LTM_IMG_MEM_OUT_B_ADDR_TOP,
	.global_width[0] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_UP,
	.global_width[1] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_UP,
	.global_width[2] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_UP,
};
//变公有
T_IM_LTM_CTRL_YLOG gctImLtmLtmCtrlYlogTbl =
{
	.use_tbl = 0,
	.end_point0_tbl0 = 0x3FFF,
	.end_point0_tbl1 = 0x3FFF,
	.end_point1_tbl0 = 0x3FFF,
	.end_point1_tbl1 = 0x3FFF,
};

static const guint16 CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[D_IM_LTM_TABLE_MAX_YLOG] =
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

static void ct_im_ltm_ltm4_class_init(CtImLtmLtm4Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmLtm4Private));
}

static void ct_im_ltm_ltm4_init(CtImLtmLtm4 *self)
{
	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	priv->gctImLtmLtmCtrlCommonBase=&gctImLtmLtmCtrlCommonBase;
	priv->gctImLtmLtmCtrlSdramInBase=&gctImLtmLtmCtrlSdramInBase;
	priv->gctImLtmLtmCtrlYlogTbl=&gctImLtmLtmCtrlYlogTbl;
	priv->gctImLtmLtmIndataBase=&gctImLtmLtmIndataBase;
	priv->gctImLtmLtmOutdataBase=&gctImLtmLtmOutdataBase;
	priv->gctImLtmLtmRgbInAddrBase=&gctImLtmLtmRgbInAddrBase;
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImLtmLtm4 *self = (CtImLtmLtm4*)object;
//	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm4_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImLtmLtm4 *self = (CtImLtmLtm4*)object;
//	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm4_parent_class)->finalize(object);
}

static void ctImLtmLtmHandler_cb(guint32* result, guint32 userParam)
{
	if(((*result) & D_IM_LTM_LTM1_INT_STATE_LTM_END) != 0) {
		Ddim_Print(("LTM LTM1 end. 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM1_INT_STATE_EXIP_END) != 0) {
		Ddim_Print(("LTM LTM1 Received transmission starting pulse. 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM1_INT_STATE_LINE_END) != 0) {
		Ddim_Print(("LTM LTM1 line end. 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM1_INT_STATE_AXR_ERR) != 0) {
		Ddim_Print(("LTM LTM1 AXR error! 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM1_INT_STATE_AXW_ERR) != 0) {
		Ddim_Print(("LTM LTM1 AXW error! 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM1_INT_STATE_YLOG_ERR) != 0) {
		Ddim_Print(("LTM LTM1 YLOG access error! 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM2_INT_STATE_LTM_END) != 0) {
		Ddim_Print(("LTM LTM2 end. 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM2_INT_STATE_EXIP_END) != 0) {
		Ddim_Print(("LTM LTM2 Received transmission starting pulse. 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM2_INT_STATE_LINE_END) != 0) {
		Ddim_Print(("LTM LTM2 line end. 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM2_INT_STATE_AXR_ERR) != 0) {
		Ddim_Print(("LTM LTM2 AXR error! 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM2_INT_STATE_AXW_ERR) != 0) {
		Ddim_Print(("LTM LTM2 AXW error! 0x%x\n", userParam));
	}
	if(((*result) & D_IM_LTM_LTM2_INT_STATE_YLOG_ERR) != 0) {
		Ddim_Print(("LTM LTM2 YLOG access error! 0x%x\n", userParam));
	}
}
/*
 *PUBLIC
 * */
#undef CtImLtmLtm4_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm4_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm4_3_1: "
gint32 ct_im_ltm_ltm4_3_1(CtImLtmLtm4 *self)
{
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm4_D_IM_LTM_FUNC_NAME));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_SW_Reset(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_SW_Reset(self->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm4_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm4_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm4_3_2: "
gint32 ct_im_ltm_ltm4_3_2(CtImLtmLtm4 *self)
{
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm4_D_IM_LTM_FUNC_NAME));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(self->pipeNo, &gctImLtmLtmCtrlCommonBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &gctImLtmLtmCtrlSdramInBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &gctImLtmLtmOutdataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Start(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(self->pipeNo, &gctImLtmLtmCtrlCommonBase);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &gctImLtmLtmCtrlSdramInBase);
	Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &gctImLtmLtmOutdataBase);
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(self->pipeNo);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Start(self->pipeNo);
#endif

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(self->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm4_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm4_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm4_3_3: "
gint32 ct_im_ltm_ltm4_3_3(CtImLtmLtm4 *self)
{
	T_IM_LTM_LTM_CTRL_COMMON ltmCtrlCommon = gctImLtmLtmCtrlCommonBase;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm4_D_IM_LTM_FUNC_NAME));

	ltmCtrlCommon.in_data_type_yp = D_IM_LTM_DTYP_PACK12;
	ltmCtrlCommon.in_data_type_yn = D_IM_LTM_DTYP_PACK12;
	ltmCtrlCommon.global_width_yp = D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH * 3 / 2;
	ltmCtrlCommon.global_width_yn = D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH * 3 / 2;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(self->pipeNo, &ltmCtrlCommon);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &gctImLtmLtmCtrlSdramInBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &gctImLtmLtmOutdataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Start(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(self->pipeNo, &ltmCtrlCommon);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &gctImLtmLtmCtrlSdramInBase);
	Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &gctImLtmLtmOutdataBase);
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(self->pipeNo);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Start(self->pipeNo);
#endif

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(self->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm4_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm4_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm4_3_4: "
gint32 ct_im_ltm_ltm4_3_4(CtImLtmLtm4 *self)
{
	T_IM_LTM_LTM_CTRL_COMMON ltmCtrlCommon = gctImLtmLtmCtrlCommonBase;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm4_D_IM_LTM_FUNC_NAME));

	ltmCtrlCommon.global_width_yp = (D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH / 2) * 2;
	ltmCtrlCommon.global_width_yn = (D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH / 2) * 2;
	ltmCtrlCommon.input_rect.img_top = 0;
	ltmCtrlCommon.input_rect.img_left = 0;
	ltmCtrlCommon.input_rect.img_width = (D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH / 2);
	ltmCtrlCommon.input_rect.img_lines = (D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_LINES / 2);

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(self->pipeNo, &ltmCtrlCommon);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &gctImLtmLtmCtrlSdramInBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &gctImLtmLtmOutdataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Start(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(self->pipeNo, &ltmCtrlCommon);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &gctImLtmLtmCtrlSdramInBase);
	Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &gctImLtmLtmOutdataBase);
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(self->pipeNo);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Start(self->pipeNo);
#endif

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(self->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm4_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm4_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm4_3_5: "
gint32 ct_im_ltm_ltm4_3_5(CtImLtmLtm4 *self)
{
	T_IM_LTM_LTM_MAP_RESIZE_PITCH resizePitch;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm4_D_IM_LTM_FUNC_NAME));

	resizePitch.hsta = -0x2000;
	resizePitch.hpit = 64;
	resizePitch.vsta = -0x2000;
	resizePitch.vpit = 64;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(self->pipeNo, &gctImLtmLtmCtrlCommonBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &gctImLtmLtmCtrlSdramInBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &gctImLtmLtmOutdataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch(self->pipeNo, &resizePitch);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Start(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(self->pipeNo, &gctImLtmLtmCtrlCommonBase);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &gctImLtmLtmCtrlSdramInBase);
	Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &gctImLtmLtmOutdataBase);
	Im_LTM_LTM_Set_MapImage_Resize_Pitch(self->pipeNo, &resizePitch);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Start(self->pipeNo);
#endif

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(self->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm4_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm4_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm4_3_6: "
gint32 ct_im_ltm_ltm4_3_6(CtImLtmLtm4 *self)
{
	T_IM_LTM_LTM_CTRL_COMMON ltmCtrlCommon = gctImLtmLtmCtrlCommonBase;
	T_IM_LTM_LTM_CTRL_SDRAM_INPUT ltmCtrlSdramIn = gctImLtmLtmCtrlSdramInBase;
	T_IM_LTM_LTM_OUTDATA_INFO ltmOutdataInfo = gctImLtmLtmOutdataBase;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm4_D_IM_LTM_FUNC_NAME));

	ltmCtrlCommon.input_rect.img_top = (D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_LINES - \
			(D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_LINES / 2)) / 2;
	ltmCtrlCommon.input_rect.img_left = (D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH - \
			(D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH / 2)) / 2;
	ltmCtrlCommon.input_rect.img_width = D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH - \
			(D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_WIDTH / 2);
	ltmCtrlCommon.input_rect.img_lines = D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_LINES - \
			(D_IM_LTM_LTM_SRC_IMG_MAP_PIXS_LINES / 2);
	ltmCtrlSdramIn.input_rect.img_top = (D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_LINES - \
			(D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_LINES / 2)) / 2;
	ltmCtrlSdramIn.input_rect.img_left = (D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_WIDTH - \
			(D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_WIDTH / 2)) / 2;
	ltmCtrlSdramIn.input_rect.img_width = D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_WIDTH - \
			(D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_WIDTH / 2);
	ltmCtrlSdramIn.input_rect.img_lines = D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_LINES - \
			(D_IM_LTM_LTM_SRC_IMG_RGB_PIXS_LINES / 2);
	ltmOutdataInfo.addr[1] = ltmOutdataInfo.addr[0] + D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_UP * \
			D_IM_LTM_LTM_DST_IMG_PIXS_LINES / 4;
	ltmOutdataInfo.addr[2] = ltmOutdataInfo.addr[1] + D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_UP * \
			D_IM_LTM_LTM_DST_IMG_PIXS_LINES / 4;
	ltmOutdataInfo.global_width[0] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_UP / 2;
	ltmOutdataInfo.global_width[1] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_UP / 2;
	ltmOutdataInfo.global_width[2] = D_IM_LTM_LTM_DST_IMG_GLOBAL_WIDTH_UP / 2;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(self->pipeNo, &ltmCtrlCommon);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &ltmCtrlSdramIn);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &ltmOutdataInfo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, \
			&CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Start(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(self->pipeNo, &ltmCtrlCommon);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(self->pipeNo, &ltmCtrlSdramIn);
	Im_LTM_LTM_Set_InAddr_Info_Rgb(self->pipeNo, &gctImLtmLtmRgbInAddrBase);
	Im_LTM_LTM_Set_InData_Info(self->pipeNo, &gctImLtmLtmIndataBase);
	Im_LTM_LTM_Set_OutData_Info(self->pipeNo, &ltmOutdataInfo);
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(self->pipeNo);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(self->pipeNo, &gctImLtmLtmCtrlYlogTbl);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(self->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm4_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Start(self->pipeNo);
#endif

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM1_INT_FLG_LTM_END;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(self->pipeNo)){
		flgPtn |= D_IM_LTM_LTM2_INT_FLG_LTM_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(self->pipeNo);
	Ddim_Print((CtImLtmLtm4_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(self->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

T_IM_LTM_LTM_CTRL_COMMON *ct_im_ltm_ltm4_get1(CtImLtmLtm4 *self)
{
	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	return priv->gctImLtmLtmCtrlCommonBase;
}

T_IM_LTM_LTM_CTRL_SDRAM_INPUT *ct_im_ltm_ltm4_get2(CtImLtmLtm4 *self)
{
	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	return priv->gctImLtmLtmCtrlSdramInBase;
}

T_IM_LTM_INADDR_INFO *ct_im_ltm_ltm4_get3(CtImLtmLtm4 *self)
{
	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	return priv->gctImLtmLtmRgbInAddrBase;
}

T_IM_LTM_LTM_INDATA_INFO *ct_im_ltm_ltm4_get4(CtImLtmLtm4 *self)
{
	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	return priv->gctImLtmLtmIndataBase;
}

T_IM_LTM_LTM_OUTDATA_INFO *ct_im_ltm_ltm4_get5(CtImLtmLtm4 *self)
{
	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	return priv->gctImLtmLtmOutdataBase;
}

T_IM_LTM_CTRL_YLOG *ct_im_ltm_ltm4_get6(CtImLtmLtm4 *self)
{
	CtImLtmLtm4Private *priv = CT_IM_LTM_LTM4_GET_PRIVATE(self);
	return priv->gctImLtmLtmCtrlYlogTbl;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmLtm4类的一个实例
 */
CtImLtmLtm4* ct_im_ltm_ltm4_new()
{
	CtImLtmLtm4 *self = g_object_new(CT_TYPE_IM_LTM_LTM_4,NULL);
	return self;
}
