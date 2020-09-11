/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmMap1类
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

#include "ctimltmmap.h"
#include "ctimltmmap2.h"
#include "ctimltmmap1.h"

G_DEFINE_TYPE(CtImLtmMap1, ct_im_ltm_map1, G_TYPE_OBJECT);

#define CT_IM_LTM_MAP_1_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_MAP_1, CtImLtmMap1Private))

struct _CtImLtmMap1Private
{
	CtImLtmMap3 *map3;
};

// Max/Min table
static T_IM_LTM_MAP_CTRL_COMMON S_GCT_IM_LTM_MAP_CTRL_COMMON[] = {
	[0] = {	// max
		.line_intr = 0x3FF,
		.wch_burst_length_yp = D_IM_LTM_BRST_256,
		.wch_burst_length_yn = D_IM_LTM_BRST_256,
		.mask_write_yp = D_IM_LTM_MASK_WRITE_DISABLE,
		.mask_write_yn = D_IM_LTM_MASK_WRITE_DISABLE,
		.write_select_yp = D_IM_LTM_PORT_SWITCH,
		.write_select_yn = D_IM_LTM_PORT_SWITCH,
		.data_type_yp = D_IM_LTM_DTYP_UNPACK12,
		.data_type_yn = D_IM_LTM_DTYP_UNPACK12,
	},
	[1] = {	// min
		.line_intr = 0,
		.wch_burst_length_yp = D_IM_LTM_BRST_512,
		.wch_burst_length_yn = D_IM_LTM_BRST_512,
		.mask_write_yp = D_IM_LTM_MASK_WRITE_ENABLE,
		.mask_write_yn = D_IM_LTM_MASK_WRITE_ENABLE,
		.write_select_yp = D_IM_LTM_PORT_DEFAULT,
		.write_select_yn = D_IM_LTM_PORT_DEFAULT,
		.data_type_yp = D_IM_LTM_DTYP_PACK12,
		.data_type_yn = D_IM_LTM_DTYP_PACK12,
	},
};

static T_IM_LTM_MAP_CTRL_SDRAM_INPUT S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN[] = {
	[0] = {	// max
		.burst_length = D_IM_LTM_BRST_256,
		.input_global = 0xFFF0,
		.input_rect = {
			.img_top = 846,
			.img_left = 1015,
			.img_width = 854,
			.img_lines = 1023,
		},
		.data_type = D_IM_LTM_DTYP_UNPACK12,
	},
	[1] = {	// min
		.burst_length = D_IM_LTM_BRST_512,
		.input_global = 0,
		.input_rect = {
			.img_top = 0,
			.img_left = 0,
			.img_width = 8,
			.img_lines = 8,
		},
		.data_type = D_IM_LTM_DTYP_PACK12,
	},
};

const guint16 CtImLtmMap1_GCT_IM_LTM_MAP_YLOG_TBL[D_IM_LTM_TABLE_MAX_YLOG] = {
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
static void 	ctImLtmMapPrintTable( CtImLtmMap1 *self, guchar tblNo );
static void 	ctImLtmMapPrintCtrlCommonReg( void );

static void ct_im_ltm_map1_class_init(CtImLtmMap1Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmMap1Private));
}

static void ct_im_ltm_map1_init(CtImLtmMap1 *self)
{
//	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImLtmMap1 *self = (CtImLtmMap1*)object;
//	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_map1_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImLtmMap1 *self = (CtImLtmMap1*)object;
//	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_map1_parent_class)->finalize(object);
}

static void ctImLtmMapPrintTable( CtImLtmMap1 *self, guchar tblNo )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	guint16 loopCnt;

	Im_LTM_On_Hclk( D_IM_LTM_PIPE12 );
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		switch( tblNo ){
			case 0:
			default:
				Ddim_Print(( "\n" ));
				for( loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++ ){
					Ddim_Print(( "IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0[%d] = 0x%x\n", loopCnt,
							IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0.hword[loopCnt] ));
				}
				break;

			case 1:
				Ddim_Print(( "\n" ));
				for( loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++ ){
					Ddim_Print(( "IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1[%d] = 0x%x\n", loopCnt,
							IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1.hword[loopCnt] ));
				}
				break;

			case 2:
				Ddim_Print(( "\n" ));
				for( loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++ ){
					Ddim_Print(( "IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0[%d] = 0x%x\n", loopCnt,
							IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0.hword[loopCnt] ));
				}
				break;

			case 3:
				Ddim_Print(( "\n" ));
				for( loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++ ){
					Ddim_Print(( "IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1[%d] = 0x%x\n", loopCnt,
							IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1.hword[loopCnt] ));
				}
				break;
		}
	}

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		switch( tblNo ){
			case 0:
			default:
				Ddim_Print(( "\n" ));
				for( loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++ ){
					Ddim_Print(( "IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0[%d] = 0x%x\n", loopCnt,
							IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0.hword[loopCnt] ));
				}
				break;

			case 1:
				Ddim_Print(( "\n" ));
				for( loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++ ){
					Ddim_Print(( "IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1[%d] = 0x%x\n", loopCnt,
							IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1.hword[loopCnt] ));
				}
				break;

			case 2:
				Ddim_Print(( "\n" ));
				for( loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++ ){
					Ddim_Print(( "IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0[%d] = 0x%x\n", loopCnt,
							IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0.hword[loopCnt] ));
				}
				break;

			case 3:
				Ddim_Print(( "\n" ));
				for( loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++ ){
					Ddim_Print(( "IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1[%d] = 0x%x\n",
							loopCnt, IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1.hword[loopCnt] ));
				}
				break;
		}
	}
	Im_LTM_Off_Hclk( D_IM_LTM_PIPE12 );
}

static void ctImLtmMapPrintCtrlCommonReg( void )
{
	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.MAP.MLINTLV.bit.LINTLV     = 0x%x\n", IO_LTM_P1.MAP.MLINTLV.bit.LINTLV     ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYP  = 0x%x\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYP  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYN  = 0x%x\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYN  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYP = 0x%x\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYP ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYN = 0x%x\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYN ));
	Ddim_Print(( "IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL1  = 0x%x\n", IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL1  ));
	Ddim_Print(( "IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL2  = 0x%x\n", IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL2  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MIOCTL.bit.W0DTYP      = 0x%x\n", IO_LTM_P1.MAP.MIOCTL.bit.W0DTYP      ));
	Ddim_Print(( "IO_LTM_P1.MAP.MIOCTL.bit.W1DTYP      = 0x%x\n", IO_LTM_P1.MAP.MIOCTL.bit.W1DTYP      ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.MAP.MLINTLV.bit.LINTLV     = 0x%x\n", IO_LTM_P2.MAP.MLINTLV.bit.LINTLV     ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYP  = 0x%x\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYP  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYN  = 0x%x\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYN  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYP = 0x%x\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYP ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYN = 0x%x\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYN ));
	Ddim_Print(( "IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL1  = 0x%x\n", IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL1  ));
	Ddim_Print(( "IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL2  = 0x%x\n", IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL2  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MIOCTL.bit.W0DTYP      = 0x%x\n", IO_LTM_P2.MAP.MIOCTL.bit.W0DTYP      ));
	Ddim_Print(( "IO_LTM_P2.MAP.MIOCTL.bit.W1DTYP      = 0x%x\n", IO_LTM_P2.MAP.MIOCTL.bit.W1DTYP      ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}
/*
 *PUBLIC
 * */
#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_1_21: "
gint32 ct_im_ltm_map1_1_21( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	Im_LTM_MAP_Set_YLOG_Table( priv->map3->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmMap1_GCT_IM_LTM_MAP_YLOG_TBL[0] );

	ctImLtmMapPrintTable( self, 0 );

	Im_LTM_MAP_Set_YLOG_Table( priv->map3->pipeNo, D_LTM_YLOG_TBL_01, &CtImLtmMap1_GCT_IM_LTM_MAP_YLOG_TBL[0] );

	ctImLtmMapPrintTable( self, 1 );

	Im_LTM_MAP_Set_YLOG_Table( priv->map3->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmMap1_GCT_IM_LTM_MAP_YLOG_TBL[0] );

	ctImLtmMapPrintTable( self, 2 );

	Im_LTM_MAP_Set_YLOG_Table( priv->map3->pipeNo, D_LTM_YLOG_TBL_11, &CtImLtmMap1_GCT_IM_LTM_MAP_YLOG_TBL[0] );

	ctImLtmMapPrintTable( self, 3 );

	return D_DDIM_OK;
}
//变公有
void ct_im_ltm_map1_handler( guint32* result, guint32 userParam )
{
	if( ((*result) & D_IM_LTM_MAP1_INT_STATE_MAP_END) != 0 ) {
		Ddim_Print(( "LTM MAP1 end. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP1_INT_STATE_LINE_END) != 0 ) {
		Ddim_Print(( "LTM MAP1 line end. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP1_INT_STATE_AXR_ERR) != 0 ) {
		Ddim_Print(( "LTM MAP1 AXR error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP1_INT_STATE_AXW_ERR) != 0 ) {
		Ddim_Print(( "LTM MAP1 AXW error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP1_INT_STATE_YLOG_ERR) != 0 ) {
		Ddim_Print(( "LTM MAP1 YLOG access error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP2_INT_STATE_MAP_END) != 0 ) {
		Ddim_Print(( "LTM MAP2 end. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP2_INT_STATE_LINE_END) != 0 ) {
		Ddim_Print(( "LTM MAP2 line end. 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP2_INT_STATE_AXR_ERR) != 0 ) {
		Ddim_Print(( "LTM MAP2 AXR error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP2_INT_STATE_AXW_ERR) != 0 ) {
		Ddim_Print(( "LTM MAP2 AXW error! 0x%x\n", userParam ));
	}
	if( ((*result) & D_IM_LTM_MAP2_INT_STATE_YLOG_ERR) != 0 ) {
		Ddim_Print(( "LTM MAP2 YLOG access error! 0x%x\n", userParam ));
	}
}
//变公有
void ct_im_ltm_map1_print_ctrl_sdram_input_reg( void )
{
	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTR = 0x%x\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTR ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDRDEF.bit.SDRDEF  = 0x%x\n", IO_LTM_P1.MAP.MSDRDEF.bit.SDRDEF  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDRHSZ.bit.SDRHSZ  = 0x%x\n", IO_LTM_P1.MAP.MSDRHSZ.bit.SDRHSZ  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDRVSZ.bit.SDRVSZ  = 0x%x\n", IO_LTM_P1.MAP.MSDRVSZ.bit.SDRVSZ  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MIOCTL.bit.INSEL    = 0x%x\n", IO_LTM_P1.MAP.MIOCTL.bit.INSEL    ));
	Ddim_Print(( "IO_LTM_P1.MAP.MIOCTL.bit.R1DTYP   = 0x%x\n", IO_LTM_P1.MAP.MIOCTL.bit.R1DTYP   ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTR = 0x%x\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTR ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDRDEF.bit.SDRDEF  = 0x%x\n", IO_LTM_P2.MAP.MSDRDEF.bit.SDRDEF  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDRHSZ.bit.SDRHSZ  = 0x%x\n", IO_LTM_P2.MAP.MSDRHSZ.bit.SDRHSZ  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDRVSZ.bit.SDRVSZ  = 0x%x\n", IO_LTM_P2.MAP.MSDRVSZ.bit.SDRVSZ  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MIOCTL.bit.INSEL    = 0x%x\n", IO_LTM_P2.MAP.MIOCTL.bit.INSEL    ));
	Ddim_Print(( "IO_LTM_P2.MAP.MIOCTL.bit.R1DTYP   = 0x%x\n", IO_LTM_P2.MAP.MIOCTL.bit.R1DTYP   ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}
//变公有
void ct_im_ltm_map1_print_all_reg( void )
{
	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAPSR      = 0x%lx\n", IO_LTM_P1.MAP.MAPSR.word      ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSRAMEN    = 0x%lx\n", IO_LTM_P1.MAP.MSRAMEN.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.MTRG       = 0x%lx\n", IO_LTM_P1.MAP.MTRG.word       ));
	Ddim_Print(( "IO_LTM_P1.MAP.MFRSTP     = 0x%lx\n", IO_LTM_P1.MAP.MFRSTP.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.MPARMSK    = 0x%lx\n", IO_LTM_P1.MAP.MPARMSK.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.MINT0      = 0x%lx\n", IO_LTM_P1.MAP.MINT0.word      ));
	Ddim_Print(( "IO_LTM_P1.MAP.MINT1      = 0x%lx\n", IO_LTM_P1.MAP.MINT1.word      ));
	Ddim_Print(( "IO_LTM_P1.MAP.MLINTLV    = 0x%lx\n", IO_LTM_P1.MAP.MLINTLV.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.AXICHSEL   = 0x%lx\n", IO_LTM_P1.MAP.AXICHSEL.word   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXICTLR   = 0x%lx\n", IO_LTM_P1.MAP.MAXICTLR.word   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXIRERR   = 0x%lx\n", IO_LTM_P1.MAP.MAXIRERR.word   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXICTLW   = 0x%lx\n", IO_LTM_P1.MAP.MAXICTLW.word   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXIWERR   = 0x%lx\n", IO_LTM_P1.MAP.MAXIWERR.word   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ   = 0x%lx\n", IO_LTM_P1.MAP.MAXIBSIZ.word   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDRHSZ    = 0x%lx\n", IO_LTM_P1.MAP.MSDRHSZ.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDRDEF    = 0x%lx\n", IO_LTM_P1.MAP.MSDRDEF.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDRVSZ    = 0x%lx\n", IO_LTM_P1.MAP.MSDRVSZ.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDRAD     = 0x%lx\n", IO_LTM_P1.MAP.MSDRAD.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDROFS    = 0x%lx\n", IO_LTM_P1.MAP.MSDROFS.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDWADW0   = 0x%lx\n", IO_LTM_P1.MAP.MSDWADW0.word   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDWDEFW0  = 0x%lx\n", IO_LTM_P1.MAP.MSDWDEFW0.word  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDWADW1   = 0x%lx\n", IO_LTM_P1.MAP.MSDWADW1.word   ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSDWDEFW1  = 0x%lx\n", IO_LTM_P1.MAP.MSDWDEFW1.word  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MIOCTL     = 0x%lx\n", IO_LTM_P1.MAP.MIOCTL.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.GAINR      = 0x%lx\n", IO_LTM_P1.MAP.GAINR.word      ));
	Ddim_Print(( "IO_LTM_P1.MAP.GAING      = 0x%lx\n", IO_LTM_P1.MAP.GAING.word      ));
	Ddim_Print(( "IO_LTM_P1.MAP.GAINB      = 0x%lx\n", IO_LTM_P1.MAP.GAINB.word      ));
	Ddim_Print(( "IO_LTM_P1.MAP.GAINCPR    = 0x%lx\n", IO_LTM_P1.MAP.GAINCPR.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.GAINCPG    = 0x%lx\n", IO_LTM_P1.MAP.GAINCPG.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.GAINCPB    = 0x%lx\n", IO_LTM_P1.MAP.GAINCPB.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.PEPS0M     = 0x%lx\n", IO_LTM_P1.MAP.PEPS0M.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.PEPS0OF    = 0x%lx\n", IO_LTM_P1.MAP.PEPS0OF.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.PEPS1M     = 0x%lx\n", IO_LTM_P1.MAP.PEPS1M.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.PEPS1OF    = 0x%lx\n", IO_LTM_P1.MAP.PEPS1OF.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.PEPS2M     = 0x%lx\n", IO_LTM_P1.MAP.PEPS2M.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.PEPS2OF    = 0x%lx\n", IO_LTM_P1.MAP.PEPS2OF.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.NEPS0M     = 0x%lx\n", IO_LTM_P1.MAP.NEPS0M.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.NEPS0OF    = 0x%lx\n", IO_LTM_P1.MAP.NEPS0OF.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.NEPS1M     = 0x%lx\n", IO_LTM_P1.MAP.NEPS1M.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.NEPS1OF    = 0x%lx\n", IO_LTM_P1.MAP.NEPS1OF.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.NEPS2M     = 0x%lx\n", IO_LTM_P1.MAP.NEPS2M.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.NEPS2OF    = 0x%lx\n", IO_LTM_P1.MAP.NEPS2OF.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.YSHADOW    = 0x%lx\n", IO_LTM_P1.MAP.YSHADOW.word    ));
	Ddim_Print(( "IO_LTM_P1.MAP.YHIGHLIGHT = 0x%lx\n", IO_LTM_P1.MAP.YHIGHLIGHT.word ));
	Ddim_Print(( "IO_LTM_P1.MAP.MYLCTL     = 0x%lx\n", IO_LTM_P1.MAP.MYLCTL.word     ));
	Ddim_Print(( "IO_LTM_P1.MAP.MYLOG0EP0  = 0x%lx\n", IO_LTM_P1.MAP.MYLOG0EP0.word  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MYLOG0EP1  = 0x%lx\n", IO_LTM_P1.MAP.MYLOG0EP1.word  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MYLOG1EP0  = 0x%lx\n", IO_LTM_P1.MAP.MYLOG1EP0.word  ));
	Ddim_Print(( "IO_LTM_P1.MAP.MYLOG1EP1  = 0x%lx\n", IO_LTM_P1.MAP.MYLOG1EP1.word  ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAPSR      = 0x%lx\n", IO_LTM_P2.MAP.MAPSR.word      ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSRAMEN    = 0x%lx\n", IO_LTM_P2.MAP.MSRAMEN.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.MTRG       = 0x%lx\n", IO_LTM_P2.MAP.MTRG.word       ));
	Ddim_Print(( "IO_LTM_P2.MAP.MFRSTP     = 0x%lx\n", IO_LTM_P2.MAP.MFRSTP.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.MPARMSK    = 0x%lx\n", IO_LTM_P2.MAP.MPARMSK.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.MINT0      = 0x%lx\n", IO_LTM_P2.MAP.MINT0.word      ));
	Ddim_Print(( "IO_LTM_P2.MAP.MINT1      = 0x%lx\n", IO_LTM_P2.MAP.MINT1.word      ));
	Ddim_Print(( "IO_LTM_P2.MAP.MLINTLV    = 0x%lx\n", IO_LTM_P2.MAP.MLINTLV.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.AXICHSEL   = 0x%lx\n", IO_LTM_P2.MAP.AXICHSEL.word   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXICTLR   = 0x%lx\n", IO_LTM_P2.MAP.MAXICTLR.word   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXIRERR   = 0x%lx\n", IO_LTM_P2.MAP.MAXIRERR.word   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXICTLW   = 0x%lx\n", IO_LTM_P2.MAP.MAXICTLW.word   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXIWERR   = 0x%lx\n", IO_LTM_P2.MAP.MAXIWERR.word   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ   = 0x%lx\n", IO_LTM_P2.MAP.MAXIBSIZ.word   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDRHSZ    = 0x%lx\n", IO_LTM_P2.MAP.MSDRHSZ.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDRDEF    = 0x%lx\n", IO_LTM_P2.MAP.MSDRDEF.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDRVSZ    = 0x%lx\n", IO_LTM_P2.MAP.MSDRVSZ.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDRAD     = 0x%lx\n", IO_LTM_P2.MAP.MSDRAD.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDROFS    = 0x%lx\n", IO_LTM_P2.MAP.MSDROFS.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDWADW0   = 0x%lx\n", IO_LTM_P2.MAP.MSDWADW0.word   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDWDEFW0  = 0x%lx\n", IO_LTM_P2.MAP.MSDWDEFW0.word  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDWADW1   = 0x%lx\n", IO_LTM_P2.MAP.MSDWADW1.word   ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSDWDEFW1  = 0x%lx\n", IO_LTM_P2.MAP.MSDWDEFW1.word  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MIOCTL     = 0x%lx\n", IO_LTM_P2.MAP.MIOCTL.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.GAINR      = 0x%lx\n", IO_LTM_P2.MAP.GAINR.word      ));
	Ddim_Print(( "IO_LTM_P2.MAP.GAING      = 0x%lx\n", IO_LTM_P2.MAP.GAING.word      ));
	Ddim_Print(( "IO_LTM_P2.MAP.GAINB      = 0x%lx\n", IO_LTM_P2.MAP.GAINB.word      ));
	Ddim_Print(( "IO_LTM_P2.MAP.GAINCPR    = 0x%lx\n", IO_LTM_P2.MAP.GAINCPR.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.GAINCPG    = 0x%lx\n", IO_LTM_P2.MAP.GAINCPG.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.GAINCPB    = 0x%lx\n", IO_LTM_P2.MAP.GAINCPB.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.PEPS0M     = 0x%lx\n", IO_LTM_P2.MAP.PEPS0M.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.PEPS0OF    = 0x%lx\n", IO_LTM_P2.MAP.PEPS0OF.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.PEPS1M     = 0x%lx\n", IO_LTM_P2.MAP.PEPS1M.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.PEPS1OF    = 0x%lx\n", IO_LTM_P2.MAP.PEPS1OF.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.PEPS2M     = 0x%lx\n", IO_LTM_P2.MAP.PEPS2M.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.PEPS2OF    = 0x%lx\n", IO_LTM_P2.MAP.PEPS2OF.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.NEPS0M     = 0x%lx\n", IO_LTM_P2.MAP.NEPS0M.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.NEPS0OF    = 0x%lx\n", IO_LTM_P2.MAP.NEPS0OF.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.NEPS1M     = 0x%lx\n", IO_LTM_P2.MAP.NEPS1M.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.NEPS1OF    = 0x%lx\n", IO_LTM_P2.MAP.NEPS1OF.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.NEPS2M     = 0x%lx\n", IO_LTM_P2.MAP.NEPS2M.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.NEPS2OF    = 0x%lx\n", IO_LTM_P2.MAP.NEPS2OF.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.YSHADOW    = 0x%lx\n", IO_LTM_P2.MAP.YSHADOW.word    ));
	Ddim_Print(( "IO_LTM_P2.MAP.YHIGHLIGHT = 0x%lx\n", IO_LTM_P2.MAP.YHIGHLIGHT.word ));
	Ddim_Print(( "IO_LTM_P2.MAP.MYLCTL     = 0x%lx\n", IO_LTM_P2.MAP.MYLCTL.word     ));
	Ddim_Print(( "IO_LTM_P2.MAP.MYLOG0EP0  = 0x%lx\n", IO_LTM_P2.MAP.MYLOG0EP0.word  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MYLOG0EP1  = 0x%lx\n", IO_LTM_P2.MAP.MYLOG0EP1.word  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MYLOG1EP0  = 0x%lx\n", IO_LTM_P2.MAP.MYLOG1EP0.word  ));
	Ddim_Print(( "IO_LTM_P2.MAP.MYLOG1EP1  = 0x%lx\n", IO_LTM_P2.MAP.MYLOG1EP1.word  ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_3_1: "
gint32 ct_im_ltm_map1_3_1( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);

#ifdef CO_MSG_PRINT_ON
	gint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_LTM_MAP_SW_Reset( priv->map3->pipeNo );
	Ddim_Print(( D_IM_LTM_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_LTM_MAP_SW_Reset( priv->map3->pipeNo );
#endif

	ct_im_ltm_map1_print_all_reg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_1_7: "
gint32 ct_im_ltm_map1_1_7( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < (sizeof(S_GCT_IM_LTM_MAP_CTRL_COMMON) \
			/ sizeof(S_GCT_IM_LTM_MAP_CTRL_COMMON[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));

		Im_LTM_MAP_Ctrl_Common( priv->map3->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_COMMON[loopCnt] );

		ctImLtmMapPrintCtrlCommonReg();
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_1_8: "
gint32 ct_im_ltm_map1_1_8( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < (sizeof(S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN) \
			/ sizeof(S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));

		Im_LTM_MAP_Ctrl_ModeSDRAMInput( priv->map3->pipeNo, &S_GCT_IM_LTM_MAP_CTRL_SDRAM_IN[loopCnt] );

		ct_im_ltm_map1_print_ctrl_sdram_input_reg();
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_1: "
gint32 ct_im_ltm_map1_2_1( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Ctrl_Axi( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP ctrl axi error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_2: "
gint32 ct_im_ltm_map1_2_2( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Get_AxiReadStat( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP get axi read stat error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_3: "
gint32 ct_im_ltm_map1_2_3( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Get_AxiWriteStat( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP get axi write stat error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_4: "
gint32 ct_im_ltm_map1_2_4( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Get_AxiCtrlParam( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP get axi ctrl param error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_5: "
gint32 ct_im_ltm_map1_2_5( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Set_AxiCtrlParam( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP set axi ctrl param error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_6: "
gint32 ct_im_ltm_map1_2_6( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Ctrl_Common( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP set ctrl common error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_7: "
gint32 ct_im_ltm_map1_2_7( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Ctrl_ModeSDRAMInput( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP set ctrl sdram input error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_8: "
gint32 ct_im_ltm_map1_2_8( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Set_InData_Info( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP set indata error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_9: "
gint32 ct_im_ltm_map1_2_9( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Set_OutData_Info( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP set outdata error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_10: "
gint32 ct_im_ltm_map1_2_10( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Get_MapBusy( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP get map busy error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_11: "
gint32 ct_im_ltm_map1_2_11( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Set_WB_Gain( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP set wbgain error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_12: "
gint32 ct_im_ltm_map1_2_12( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Ctrl_Generation_Mode( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP ctrl generation mode error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_13: "
gint32 ct_im_ltm_map1_2_13( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Get_Internal_Param( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP get internal param error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_14: "
gint32 ct_im_ltm_map1_2_14( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Ctrl_Ylog_Tbl( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP ctrl ylog tbl error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_15: "
gint32 ct_im_ltm_map1_2_15( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Get_Active_Ylog_Tbl_No( priv->map3->pipeNo, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP get active ylog tbl no error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_16: "
gint32 ct_im_ltm_map1_2_16( CtImLtmMap1 *self )
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Set_YLOG_Table( priv->map3->pipeNo, 0, NULL );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP set ylog tbl error = 0x%x\n", ercd ));
	}

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map1_2_17: "
gint32 ct_im_ltm_map1_2_17( CtImLtmMap1 *self )
{
	gint32 ercd = D_DDIM_OK;
	DDIM_USER_FLGPTN flgptn;
	DDIM_USER_FLGPTN waiptn;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	waiptn = 0x11110000;
	ercd = Im_LTM_MAP_WaitEnd( &flgptn, waiptn, 100 );
	if( ercd != D_DDIM_OK ){
		Ddim_Print(( D_IM_LTM_FUNC_NAME "MAP wait end error = 0x%x\n", ercd ));
	}

	return ercd;
}

void ct_im_ltm_map1_set_map3(CtImLtmMap1* self, CtImLtmMap3* map3)
{
	CtImLtmMap1Private *priv = CT_IM_LTM_MAP_1_GET_PRIVATE(self);
	priv->map3 = map3;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmMap1类的一个实例
 */
CtImLtmMap1* ct_im_ltm_map1_new()
{
	CtImLtmMap1 *self = g_object_new(CT_TYPE_IM_LTM_MAP_1,NULL);
	return self;
}
