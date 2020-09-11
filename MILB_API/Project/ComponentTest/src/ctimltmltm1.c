/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm1类
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
#include "ctimltmltm1.h"

G_DEFINE_TYPE(CtImLtmLtm1, ct_im_ltm_ltm1, G_TYPE_OBJECT);

#define CT_IM_LTM_LTM1_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_LTM_1, CtImLtmLtm1Private))

struct _CtImLtmLtm1Private
{
	CtImLtmLtm2 *ctrlBlend;
	CtImLtmLtm4 *ltm4;
};

// Max/Min table
static T_IM_LTM_LTM_CTRL_COMMON S_GCT_IM_LTM_LTM_CTRL_COMMON[] =
{
	[0] =
	{	// max
		.line_intr = 0x3FFF,
		.rch_burst_length_yp = D_IM_LTM_BRST_256,
		.rch_burst_length_yn = D_IM_LTM_BRST_256,
		.wch_burst_length_r = D_IM_LTM_BRST_256,
		.wch_burst_length_g = D_IM_LTM_BRST_256,
		.wch_burst_length_b = D_IM_LTM_BRST_256,
		.mask_write_r = D_IM_LTM_MASK_WRITE_DISABLE,
		.mask_write_g = D_IM_LTM_MASK_WRITE_DISABLE,
		.mask_write_b = D_IM_LTM_MASK_WRITE_DISABLE,
		.read_select_yp = D_IM_LTM_PORT_SWITCH,
		.read_select_yn = D_IM_LTM_PORT_SWITCH,
		.in_data_type_yp = D_IM_LTM_DTYP_UNPACK12,
		.in_data_type_yn = D_IM_LTM_DTYP_UNPACK12,
		.out_select =  D_IM_LTM_LTM_OUT_R2Y_DIRECT,
		.out_data_type = D_IM_LTM_DTYP_UNPACK12,
		.input_rect = {
			.img_top = 1015,
			.img_left = 846,
			.img_width = 854,
			.img_lines = 1023,
		},
		.global_width_yp = 0xFFF0,
		.global_width_yn = 0xFFF0,
	},
	[1] =
	{	// min
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
		.in_data_type_yp = D_IM_LTM_DTYP_PACK12,
		.in_data_type_yn = D_IM_LTM_DTYP_PACK12,
		.out_select =  D_IM_LTM_LTM_OUT_SDRAM,
		.out_data_type = D_IM_LTM_DTYP_PACK12,
		.input_rect =
		{
			.img_top = 0,
			.img_left = 0,
			.img_width = 8,
			.img_lines = 8,
		},
		.global_width_yp = 0,
		.global_width_yn = 0,
	},
};

static T_IM_LTM_LTM_CTRL_SDRAM_INPUT S_GCT_IM_LTM_LTM_CTRL_SDRAM_IN[] =
{
	[0] =
	{	// max
		.rch_burst_length_r = D_IM_LTM_BRST_256,
		.rch_burst_length_g = D_IM_LTM_BRST_256,
		.rch_burst_length_b = D_IM_LTM_BRST_256,
		.input_global_rgb = 0xFFF0,
		.input_rect =
		{
			.img_top = 2264,
			.img_left = 8888,
			.img_width = 2360,
			.img_lines = 8960,
		},
	},
	[1] = {	// min
		.rch_burst_length_r = D_IM_LTM_BRST_512,
		.rch_burst_length_g = D_IM_LTM_BRST_512,
		.rch_burst_length_b = D_IM_LTM_BRST_512,
		.input_global_rgb = 0,
		.input_rect =
		{
			.img_top = 0,
			.img_left = 0,
			.img_width = 96,
			.img_lines = 72,
		},
	},
};

static T_IM_LTM_LTM_CTRL_B2R_DIRECT S_GCT_IM_LTM_LTM_CTRL_B2R_DIRECT[] =
{
	[0] =
	{	// max
		.input_rect =
		{
			.img_top = 2264,
			.img_left = 8888,
			.img_width = 2360,
			.img_lines = 8960,
		},
		.bypass = D_IM_LTM_ENABLE_ON,
	},
	[1] =
	{	// min
		.input_rect =
		{
			.img_top = 0,
			.img_left = 0,
			.img_width = 96,
			.img_lines = 72,
		},
		.bypass = D_IM_LTM_ENABLE_OFF,
	},
};

static const guint16 CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[D_IM_LTM_TABLE_MAX_YLOG] =
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
static void 	ctImLtmLtmPrintCtrlCommonReg(void);
static void 	ctImLtmLtmPrintB2rDirectReg(void);

static void ct_im_ltm_ltm1_class_init(CtImLtmLtm1Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmLtm1Private));
}

static void ct_im_ltm_ltm1_init(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	priv->ctrlBlend=NULL;
	priv->ltm4=NULL;
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImLtmLtm1 *self = (CtImLtmLtm1*)object;
//	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm1_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImLtmLtm1 *self = (CtImLtmLtm1*)object;
//	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm1_parent_class)->finalize(object);
}

static void ctImLtmLtmPrintCtrlCommonReg(void)
{
	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P1.LTM.LLINTLV.bit.LINTLV     = 0x%x\n", IO_LTM_P1.LTM.LLINTLV.bit.LINTLV));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYP  = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYP));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYN  = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYN));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWR   = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWR));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWG   = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWG));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWB   = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWB));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKR  = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKR));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKG  = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKG));
	Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKB  = 0x%x\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKB));
	Ddim_Print(("IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL1   = 0x%x\n", IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL1));
	Ddim_Print(("IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL2   = 0x%x\n", IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL2));
	Ddim_Print(("IO_LTM_P1.LTM.LIOCTL.bit.R3DTYP      = 0x%x\n", IO_LTM_P1.LTM.LIOCTL.bit.R3DTYP));
	Ddim_Print(("IO_LTM_P1.LTM.LIOCTL.bit.R4DTYP      = 0x%x\n", IO_LTM_P1.LTM.LIOCTL.bit.R4DTYP));
	Ddim_Print(("IO_LTM_P1.LTM.LIOCTL.bit.OUTSEL      = 0x%x\n", IO_LTM_P1.LTM.LIOCTL.bit.OUTSEL));
	Ddim_Print(("IO_LTM_P1.LTM.LIOCTL.bit.W1DTYP      = 0x%x\n", IO_LTM_P1.LTM.LIOCTL.bit.W1DTYP));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRHSZR3.bit.SDRHSZR3 = 0x%x\n", IO_LTM_P1.LTM.LSDRHSZR3.bit.SDRHSZR3));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRDEFR3.bit.SDRDEFR3 = 0x%x\n", IO_LTM_P1.LTM.LSDRDEFR3.bit.SDRDEFR3));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRVSZR3.bit.SDRVSZR3 = 0x%x\n", IO_LTM_P1.LTM.LSDRVSZR3.bit.SDRVSZR3));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRDEFR4.bit.SDRDEFR4 = 0x%x\n", IO_LTM_P1.LTM.LSDRDEFR4.bit.SDRDEFR4));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LLINTLV.bit.LINTLV     = 0x%x\n", IO_LTM_P2.LTM.LLINTLV.bit.LINTLV));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYP  = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYP));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYN  = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYN));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWR   = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWR));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWG   = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWG));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWB   = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWB));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKR  = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKR));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKG  = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKG));
	Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKB  = 0x%x\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKB));
	Ddim_Print(("IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL1   = 0x%x\n", IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL1));
	Ddim_Print(("IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL2   = 0x%x\n", IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL2));
	Ddim_Print(("IO_LTM_P2.LTM.LIOCTL.bit.R3DTYP      = 0x%x\n", IO_LTM_P2.LTM.LIOCTL.bit.R3DTYP));
	Ddim_Print(("IO_LTM_P2.LTM.LIOCTL.bit.R4DTYP      = 0x%x\n", IO_LTM_P2.LTM.LIOCTL.bit.R4DTYP));
	Ddim_Print(("IO_LTM_P2.LTM.LIOCTL.bit.OUTSEL      = 0x%x\n", IO_LTM_P2.LTM.LIOCTL.bit.OUTSEL));
	Ddim_Print(("IO_LTM_P2.LTM.LIOCTL.bit.W1DTYP      = 0x%x\n", IO_LTM_P2.LTM.LIOCTL.bit.W1DTYP));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRHSZR3.bit.SDRHSZR3 = 0x%x\n", IO_LTM_P2.LTM.LSDRHSZR3.bit.SDRHSZR3));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRDEFR3.bit.SDRDEFR3 = 0x%x\n", IO_LTM_P2.LTM.LSDRDEFR3.bit.SDRDEFR3));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRVSZR3.bit.SDRVSZR3 = 0x%x\n", IO_LTM_P2.LTM.LSDRVSZR3.bit.SDRVSZR3));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRDEFR4.bit.SDRDEFR4 = 0x%x\n", IO_LTM_P2.LTM.LSDRDEFR4.bit.SDRDEFR4));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
}

static void ctImLtmLtmPrintB2rDirectReg(void)
{
	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P1.LTM.LIOCTL.bit.INSEL       = 0x%x\n", IO_LTM_P1.LTM.LIOCTL.bit.INSEL));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRHSZR2.bit.SDRHSZR2 = 0x%x\n", IO_LTM_P1.LTM.LSDRHSZR2.bit.SDRHSZR2));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRVSZR2.bit.SDRVSZR2 = 0x%x\n", IO_LTM_P1.LTM.LSDRVSZR2.bit.SDRVSZR2));
	Ddim_Print(("IO_LTM_P1.LTM.LIOCTL.bit.BYPASS      = 0x%x\n", IO_LTM_P1.LTM.LIOCTL.bit.BYPASS));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LIOCTL.bit.INSEL       = 0x%x\n", IO_LTM_P2.LTM.LIOCTL.bit.INSEL));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRHSZR2.bit.SDRHSZR2 = 0x%x\n", IO_LTM_P2.LTM.LSDRHSZR2.bit.SDRHSZR2));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRVSZR2.bit.SDRVSZR2 = 0x%x\n", IO_LTM_P2.LTM.LSDRVSZR2.bit.SDRVSZR2));
	Ddim_Print(("IO_LTM_P2.LTM.LIOCTL.bit.BYPASS      = 0x%x\n", IO_LTM_P2.LTM.LIOCTL.bit.BYPASS));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
}
/*
 *PUBLIC
 * */
#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_1_7: "
gint32 ct_im_ltm_ltm1_1_7(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(S_GCT_IM_LTM_LTM_CTRL_COMMON) \
			/ sizeof(S_GCT_IM_LTM_LTM_CTRL_COMMON[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, &S_GCT_IM_LTM_LTM_CTRL_COMMON[loopCnt]);
		ctImLtmLtmPrintCtrlCommonReg();
	}
	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_1_8: "
gint32 ct_im_ltm_ltm1_1_8(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(S_GCT_IM_LTM_LTM_CTRL_SDRAM_IN)\
			/ sizeof(S_GCT_IM_LTM_LTM_CTRL_SDRAM_IN[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, &S_GCT_IM_LTM_LTM_CTRL_SDRAM_IN[loopCnt]);
		ct_im_ltm_ltm2_print_ctrl_sdram_input_reg();
	}
	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_1_12: "
gint32 ct_im_ltm_ltm1_1_12(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(S_GCT_IM_LTM_LTM_CTRL_B2R_DIRECT) \
			/ sizeof(S_GCT_IM_LTM_LTM_CTRL_B2R_DIRECT[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Ctrl_ModeB2RDirect(priv->ltm4->pipeNo, &S_GCT_IM_LTM_LTM_CTRL_B2R_DIRECT[loopCnt]);
		ctImLtmLtmPrintB2rDirectReg();
	}
	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_3_7: "
gint32 ct_im_ltm_ltm1_3_7(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_HF_STRENGTH hfCtrl;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	hfCtrl.strength = 4096;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_High_Frequency_Strength(priv->ltm4->pipeNo, &hfCtrl);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00,
					&CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10,
					&CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Set_High_Frequency_Strength(priv->ltm4->pipeNo, &hfCtrl);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo,ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
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
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_3_8: "
gint32 ct_im_ltm_ltm1_3_8(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_HF_STRENGTH hfCtrl;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	hfCtrl.strength = 0;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_High_Frequency_Strength(priv->ltm4->pipeNo, &hfCtrl);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Set_High_Frequency_Strength(priv->ltm4->pipeNo, &hfCtrl);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
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
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_3_9: "
gint32 ct_im_ltm_ltm1_3_9(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_BLEND blendCtrl = priv->ctrlBlend->gctImLtmLtmCtrlBlend;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	blendCtrl.ratio = 0;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_Blend(priv->ltm4->pipeNo, &blendCtrl);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Ctrl_Blend(priv->ltm4->pipeNo, &blendCtrl);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
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
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_3_10: "
gint32 ct_im_ltm_ltm1_3_10(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_BLEND blendCtrl = priv->ctrlBlend->gctImLtmLtmCtrlBlend;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	blendCtrl.ratio = 8;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_Blend(priv->ltm4->pipeNo, &blendCtrl);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Ctrl_Blend(priv->ltm4->pipeNo, &blendCtrl);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
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
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_3_11: "
gint32 ct_im_ltm_ltm1_3_11(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_BLEND blendCtrl = priv->ctrlBlend->gctImLtmLtmCtrlBlend;
	DDIM_USER_FLGPTN flgPtn = 0;
#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	blendCtrl.mode = 0;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_Blend(priv->ltm4->pipeNo, &blendCtrl);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
	ercd = Im_LTM_LTM_Start(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get3(priv->ltm4));
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get4(priv->ltm4));
	Im_LTM_LTM_Set_OutData_Info(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get5(priv->ltm4));
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);
	Im_LTM_LTM_Ctrl_Blend(priv->ltm4->pipeNo, &blendCtrl);
	Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get6(priv->ltm4));
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
	Im_LTM_LTM_Set_YLOG_Table(priv->ltm4->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm1_GCT_IM_LTM_LTM_YLOG_TBL[0]);
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
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));

	ercd = Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
	Ddim_Print((CtImLtmLtm1_D_IM_LTM_FUNC_NAME "0x%x\n", ercd));
#else
	Im_LTM_LTM_WaitEnd(NULL, flgPtn, 30);
	Im_LTM_LTM_Stop(priv->ltm4->pipeNo);
#endif

	ct_im_ltm_ltm2_print_all_reg();

	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_1_9: "
gint32 ct_im_ltm_ltm1_1_9(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	guint32 loopCnt;
	T_IM_LTM_LTM_CTRL_SDRAM_INPUT *ltmCtrlSdramIn = ct_im_ltm_ltm4_get2(priv->ltm4);
	T_IM_LTM_INADDR_INFO ltmInAddr[] = {
		[0] = { // max
			.addr_r = (gpointer)0xFFFFFFFE,
			.addr_g = (gpointer)0xFFFFFFFE,
			.addr_b = (gpointer)0xFFFFFFFE,
		},
		[1] = { // min
			.addr_r = (gpointer)0,
			.addr_g = (gpointer)0,
			.addr_b = (gpointer)0,
		},
		[2] = { // indvisual
			.addr_r = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,
			.addr_g = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_G_ADDR_TOP,
			.addr_b = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_B_ADDR_TOP,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get1(priv->ltm4));
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ltmCtrlSdramIn);

	for(loopCnt = 0; loopCnt < (sizeof(ltmInAddr) / sizeof(ltmInAddr[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, &ltmInAddr[loopCnt]);

		ct_im_ltm_ltm2_print_ctrl_sdram_input_reg();

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2R.bit.SDRADR2R = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2R.bit.SDRADR2R));
		Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2G.bit.SDRADR2G = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2G.bit.SDRADR2G));
		Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2B.bit.SDRADR2B = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2B.bit.SDRADR2B));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2R.bit.SDRADR2R = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2R.bit.SDRADR2R));
		Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2G.bit.SDRADR2G = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2G.bit.SDRADR2G));
		Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2B.bit.SDRADR2B = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2B.bit.SDRADR2B));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	ltmCtrlSdramIn->input_rect.img_top = 100;
	ltmCtrlSdramIn->input_rect.img_left = 200;

	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ltmCtrlSdramIn);

	Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm4->pipeNo, &ltmInAddr[2]);

	ct_im_ltm_ltm2_print_ctrl_sdram_input_reg();

	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2R.bit.SDRADR2R = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2R.bit.SDRADR2R));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2G.bit.SDRADR2G = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2G.bit.SDRADR2G));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR2B.bit.SDRADR2B = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR2B.bit.SDRADR2B));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2R.bit.SDRADR2R = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2R.bit.SDRADR2R));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2G.bit.SDRADR2G = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2G.bit.SDRADR2G));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR2B.bit.SDRADR2B = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR2B.bit.SDRADR2B));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);

	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_1_10: "
gint32 ct_im_ltm_ltm1_1_10(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	guint32 loopCnt;
	T_IM_LTM_LTM_CTRL_COMMON *ltmCtrlCommon = ct_im_ltm_ltm4_get1(priv->ltm4);
	T_IM_LTM_LTM_INDATA_INFO ltmInData[] = {
		[0] = { // max
			.addr_yp = (gpointer)0xFFFFFFFE,
			.addr_yn = (gpointer)0xFFFFFFFE,
			.top_bit_offset_yp = 1,
			.top_bit_offset_yn = 1,
		},
		[1] = { // min
			.addr_yp = (gpointer)0,
			.addr_yn = (gpointer)0,
			.top_bit_offset_yp = 0,
			.top_bit_offset_yn = 0,
		},
		[2] = { // indvisual
			.addr_yp = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP,
			.addr_yn = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP,
			.top_bit_offset_yp = 0,
			.top_bit_offset_yn = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ltmCtrlCommon);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));

	for(loopCnt = 0; loopCnt < (sizeof(ltmInData) / sizeof(ltmInData[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, &ltmInData[loopCnt]);

		ct_im_ltm_ltm2_print_ctrl_sdram_input_reg();

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LSDRADR3.bit.SDRADR3 = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR3.bit.SDRADR3));
		Ddim_Print(("IO_LTM_P1.LTM.LSDROFS.bit.SDROFSR3 = 0x%x\n",  IO_LTM_P1.LTM.LSDROFS.bit.SDROFSR3));
		Ddim_Print(("IO_LTM_P1.LTM.LSDRADR4.bit.SDRADR4 = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR4.bit.SDRADR4));
		Ddim_Print(("IO_LTM_P1.LTM.LSDROFS.bit.SDROFSR4 = 0x%x\n",  IO_LTM_P1.LTM.LSDROFS.bit.SDROFSR4));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LSDRADR3.bit.SDRADR3 = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR3.bit.SDRADR3));
		Ddim_Print(("IO_LTM_P2.LTM.LSDROFS.bit.SDROFSR3 = 0x%x\n",  IO_LTM_P2.LTM.LSDROFS.bit.SDROFSR3));
		Ddim_Print(("IO_LTM_P2.LTM.LSDRADR4.bit.SDRADR4 = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR4.bit.SDRADR4));
		Ddim_Print(("IO_LTM_P2.LTM.LSDROFS.bit.SDROFSR4 = 0x%x\n",  IO_LTM_P2.LTM.LSDROFS.bit.SDROFSR4));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	ltmCtrlCommon->input_rect.img_top = 100;
	ltmCtrlCommon->input_rect.img_left = 200;

	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ltmCtrlCommon);

	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, &ltmInData[2]);

	ct_im_ltm_ltm2_print_ctrl_sdram_input_reg();

	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR3.bit.SDRADR3 = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR3.bit.SDRADR3));
	Ddim_Print(("IO_LTM_P1.LTM.LSDROFS.bit.SDROFSR3 = 0x%x\n",  IO_LTM_P1.LTM.LSDROFS.bit.SDROFSR3));
	Ddim_Print(("IO_LTM_P1.LTM.LSDRADR4.bit.SDRADR4 = 0x%lx\n", IO_LTM_P1.LTM.LSDRADR4.bit.SDRADR4));
	Ddim_Print(("IO_LTM_P1.LTM.LSDROFS.bit.SDROFSR4 = 0x%x\n",  IO_LTM_P1.LTM.LSDROFS.bit.SDROFSR4));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR3.bit.SDRADR3 = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR3.bit.SDRADR3));
	Ddim_Print(("IO_LTM_P2.LTM.LSDROFS.bit.SDROFSR3 = 0x%x\n",  IO_LTM_P2.LTM.LSDROFS.bit.SDROFSR3));
	Ddim_Print(("IO_LTM_P2.LTM.LSDRADR4.bit.SDRADR4 = 0x%lx\n", IO_LTM_P2.LTM.LSDRADR4.bit.SDRADR4));
	Ddim_Print(("IO_LTM_P2.LTM.LSDROFS.bit.SDROFSR4 = 0x%x\n",  IO_LTM_P2.LTM.LSDROFS.bit.SDROFSR4));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);

	return D_DDIM_OK;
}

#undef CtImLtmLtm1_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm1_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm1_1_13: "
gint32 ct_im_ltm_ltm1_1_13(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	T_IM_LTM_LTM_CTRL_COMMON *ltmCtrlCommon = ct_im_ltm_ltm4_get1(priv->ltm4);
	T_IM_LTM_LTM_INDATA_INFO ltmInData = {
		.addr_yp = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP,
		.addr_yn = (gpointer)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP,
		.top_bit_offset_yp = 0,
		.top_bit_offset_yn = 0,
	};
	Ddim_Print(("%s\n", CtImLtmLtm1_D_IM_LTM_FUNC_NAME));

	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ltmCtrlCommon);
	Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm4->pipeNo, ct_im_ltm_ltm4_get2(priv->ltm4));
	Im_LTM_LTM_Set_InData_Info(priv->ltm4->pipeNo, &ltmInData);
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);

	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("IO_LTM_P1.LTM.LHSTA.bit.HSTA = 0x%x\n", IO_LTM_P1.LTM.LHSTA.bit.HSTA));
	Ddim_Print(("IO_LTM_P1.LTM.LHPIT.bit.HPIT = 0x%x\n", IO_LTM_P1.LTM.LHPIT.bit.HPIT));
	Ddim_Print(("IO_LTM_P1.LTM.LVSTA.bit.VSTA = 0x%x\n", IO_LTM_P1.LTM.LVSTA.bit.VSTA));
	Ddim_Print(("IO_LTM_P1.LTM.LVPIT.bit.VPIT = 0x%x\n", IO_LTM_P1.LTM.LVPIT.bit.VPIT));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LHSTA.bit.HSTA = 0x%x\n", IO_LTM_P2.LTM.LHSTA.bit.HSTA));
	Ddim_Print(("IO_LTM_P2.LTM.LHPIT.bit.HPIT = 0x%x\n", IO_LTM_P2.LTM.LHPIT.bit.HPIT));
	Ddim_Print(("IO_LTM_P2.LTM.LVSTA.bit.VSTA = 0x%x\n", IO_LTM_P2.LTM.LVSTA.bit.VSTA));
	Ddim_Print(("IO_LTM_P2.LTM.LVPIT.bit.VPIT = 0x%x\n", IO_LTM_P2.LTM.LVPIT.bit.VPIT));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);

	ltmCtrlCommon->input_rect.img_width /= 2;
	ltmCtrlCommon->input_rect.img_lines /= 2;

	Im_LTM_LTM_Ctrl_Common(priv->ltm4->pipeNo, ltmCtrlCommon);
	Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto(priv->ltm4->pipeNo);

	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P1.LTM.LHSTA.bit.HSTA = 0x%x\n", IO_LTM_P1.LTM.LHSTA.bit.HSTA));
	Ddim_Print(("IO_LTM_P1.LTM.LHPIT.bit.HPIT = 0x%x\n", IO_LTM_P1.LTM.LHPIT.bit.HPIT));
	Ddim_Print(("IO_LTM_P1.LTM.LVSTA.bit.VSTA = 0x%x\n", IO_LTM_P1.LTM.LVSTA.bit.VSTA));
	Ddim_Print(("IO_LTM_P1.LTM.LVPIT.bit.VPIT = 0x%x\n", IO_LTM_P1.LTM.LVPIT.bit.VPIT));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LHSTA.bit.HSTA = 0x%x\n", IO_LTM_P2.LTM.LHSTA.bit.HSTA));
	Ddim_Print(("IO_LTM_P2.LTM.LHPIT.bit.HPIT = 0x%x\n", IO_LTM_P2.LTM.LHPIT.bit.HPIT));
	Ddim_Print(("IO_LTM_P2.LTM.LVSTA.bit.VSTA = 0x%x\n", IO_LTM_P2.LTM.LVSTA.bit.VSTA));
	Ddim_Print(("IO_LTM_P2.LTM.LVPIT.bit.VPIT = 0x%x\n", IO_LTM_P2.LTM.LVPIT.bit.VPIT));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);

	return D_DDIM_OK;
}

void ct_im_ltm_ltm1_set_ltm4(CtImLtmLtm1 *self,CtImLtmLtm4 *ltm4)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	priv->ltm4=ltm4;
}

guchar ct_im_ltm_ltm1_get_self1(CtImLtmLtm1 *self)
{
	CtImLtmLtm1Private *priv = CT_IM_LTM_LTM1_GET_PRIVATE(self);
	return priv->ltm4->pipeNo;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmLtm1类的一个实例
 */
CtImLtmLtm1* ct_im_ltm_ltm1_new()
{
	CtImLtmLtm1 *self = g_object_new(CT_TYPE_IM_LTM_LTM_1,NULL);
	return self;
}
