/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm5类
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

#include "ctimltmltm.h"
#include "ctimltmltm2.h"
#include "ctimltmltm3.h"
#include "ctimltmltm5.h"

G_DEFINE_TYPE(CtImLtmLtm5, ct_im_ltm_ltm5, G_TYPE_OBJECT);

#define CT_IM_LTM_LTM5_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_LTM_5, CtImLtmLtm5Private))

struct _CtImLtmLtm5Private
{
	CtImLtmLtm4 *ltm45;
};

static const guint16 CtImLtmLtm5_GCT_IM_LTM_LTM_YLOG_TBL[D_IM_LTM_TABLE_MAX_YLOG] =
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
static void 	ctImLtmLtmPrintTable(CtImLtmLtm5 *self, guchar tblNo);

static void ct_im_ltm_ltm5_class_init(CtImLtmLtm5Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmLtm5Private));
}

static void ct_im_ltm_ltm5_init(CtImLtmLtm5 *self)
{
//	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImLtmLtm5 *self = (CtImLtmLtm5*)object;
//	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm5_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImLtmLtm5 *self = (CtImLtmLtm5*)object;
//	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm5_parent_class)->finalize(object);
}

static void ctImLtmLtmPrintTable(CtImLtmLtm5 *self, guchar tblNo)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	guint16 loopCnt;

	Im_LTM_On_Hclk(D_IM_LTM_PIPE12);
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm45->pipeNo)){
		switch(tblNo){
			case 0:
			default:
				Ddim_Print(("\n"));
				for(loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++){
					Ddim_Print(("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0[%d] = 0x%x\n", \
							loopCnt, IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0.hword[loopCnt]));
				}
				break;

			case 1:
				Ddim_Print(("\n"));
				for(loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++){
					Ddim_Print(("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1[%d] = 0x%x\n", \
							loopCnt, IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1.hword[loopCnt]));
				}
				break;

			case 2:
				Ddim_Print(("\n"));
				for(loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++){
					Ddim_Print(("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0[%d] = 0x%x\n", loopCnt, \
							IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0.hword[loopCnt]));
				}
				break;

			case 3:
				Ddim_Print(("\n"));
				for(loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++){
					Ddim_Print(("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1[%d] = 0x%x\n", loopCnt, \
							IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1.hword[loopCnt]));
				}
				break;
		}
	}

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm45->pipeNo)){
		switch(tblNo){
			case 0:
			default:
				Ddim_Print(("\n"));
				for(loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++){
					Ddim_Print(("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0[%d] = 0x%x\n", loopCnt, \
							IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0.hword[loopCnt]));
				}
				break;

			case 1:
				Ddim_Print(("\n"));
				for(loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++){
					Ddim_Print(("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1[%d] = 0x%x\n", loopCnt, \
							IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1.hword[loopCnt]));
				}
				break;

			case 2:
				Ddim_Print(("\n"));
				for(loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++){
					Ddim_Print(("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0[%d] = 0x%x\n", loopCnt, \
							IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0.hword[loopCnt]));
				}
				break;

			case 3:
				Ddim_Print(("\n"));
				for(loopCnt = 0; loopCnt < D_IM_LTM_TABLE_MAX_YLOG; loopCnt++){
					Ddim_Print(("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1[%d] = 0x%x\n", loopCnt, \
							IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1.hword[loopCnt]));
				}
				break;
		}
	}
	Im_LTM_Off_Hclk(D_IM_LTM_PIPE12);
}
/*
 *PUBLIC
 * */
#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_1_23: "
gint32 ct_im_ltm_ltm5_1_23(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	guint32	loopCnt;
	T_IM_LTM_CTRL_YLOG	ltmCtrlYlog[] =
	{
		[0] =
		{	// max
			.use_tbl = 1,
			.end_point0_tbl0 = 0x3FFF,
			.end_point0_tbl1 = 0x3FFF,
			.end_point1_tbl0 = 0x3FFF,
			.end_point1_tbl1 = 0x3FFF,
		},
		[1] =
		{	// min
			.use_tbl = 0,
			.end_point0_tbl0 = 0,
			.end_point0_tbl1 = 0,
			.end_point1_tbl0 = 0,
			.end_point1_tbl1 = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(ltmCtrlYlog) / sizeof(ltmCtrlYlog[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm45->pipeNo, &ltmCtrlYlog[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LYLCTL.bit.YLOGSL      = 0x%x\n", IO_LTM_P1.LTM.LYLCTL.bit.YLOGSL));
		Ddim_Print(("IO_LTM_P1.LTM.LYLOG0EP0.bit.YLOG0EP0 = 0x%x\n", IO_LTM_P1.LTM.LYLOG0EP0.bit.YLOG0EP0));
		Ddim_Print(("IO_LTM_P1.LTM.LYLOG0EP1.bit.YLOG0EP1 = 0x%x\n", IO_LTM_P1.LTM.LYLOG0EP1.bit.YLOG0EP1));
		Ddim_Print(("IO_LTM_P1.LTM.LYLOG1EP0.bit.YLOG1EP0 = 0x%x\n", IO_LTM_P1.LTM.LYLOG1EP0.bit.YLOG1EP0));
		Ddim_Print(("IO_LTM_P1.LTM.LYLOG1EP1.bit.YLOG1EP1 = 0x%x\n", IO_LTM_P1.LTM.LYLOG1EP1.bit.YLOG1EP1));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LYLCTL.bit.YLOGSL      = 0x%x\n", IO_LTM_P2.LTM.LYLCTL.bit.YLOGSL));
		Ddim_Print(("IO_LTM_P2.LTM.LYLOG0EP0.bit.YLOG0EP0 = 0x%x\n", IO_LTM_P2.LTM.LYLOG0EP0.bit.YLOG0EP0));
		Ddim_Print(("IO_LTM_P2.LTM.LYLOG0EP1.bit.YLOG0EP1 = 0x%x\n", IO_LTM_P2.LTM.LYLOG0EP1.bit.YLOG0EP1));
		Ddim_Print(("IO_LTM_P2.LTM.LYLOG1EP0.bit.YLOG1EP0 = 0x%x\n", IO_LTM_P2.LTM.LYLOG1EP0.bit.YLOG1EP0));
		Ddim_Print(("IO_LTM_P2.LTM.LYLOG1EP1.bit.YLOG1EP1 = 0x%x\n", IO_LTM_P2.LTM.LYLOG1EP1.bit.YLOG1EP1));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_1_24: "
gint32 ct_im_ltm_ltm5_1_24(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	guchar actTblNo;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

#ifdef CO_DEBUG_ON_PC
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm45->pipeNo)){
		IO_LTM_P1.LTM.LYLCTL.bit.YLOGSTA = 1;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm45->pipeNo)){
		IO_LTM_P2.LTM.LYLCTL.bit.YLOGSTA = 1;
	}
#endif // CO_DEBUG_ON_PC
	Im_LTM_LTM_Get_Active_Ylog_Tbl_No(priv->ltm45->pipeNo, &actTblNo);
	Ddim_Print(("actTblNo = %u\n", actTblNo));

#ifdef CO_DEBUG_ON_PC
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm45->pipeNo)){
		IO_LTM_P1.LTM.LYLCTL.bit.YLOGSTA = 0;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm45->pipeNo)){
		IO_LTM_P2.LTM.LYLCTL.bit.YLOGSTA = 0;
	}
#endif // CO_DEBUG_ON_PC
	Im_LTM_LTM_Get_Active_Ylog_Tbl_No(priv->ltm45->pipeNo, &actTblNo);
	Ddim_Print(("actTblNo = %u\n", actTblNo));

	return D_DDIM_OK;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_1_25: "
gint32 ct_im_ltm_ltm5_1_25(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	Im_LTM_LTM_Set_YLOG_Table(priv->ltm45->pipeNo, D_LTM_YLOG_TBL_00, &CtImLtmLtm5_GCT_IM_LTM_LTM_YLOG_TBL[0]);

	ctImLtmLtmPrintTable(self, 0);

	Im_LTM_LTM_Set_YLOG_Table(priv->ltm45->pipeNo, D_LTM_YLOG_TBL_01, &CtImLtmLtm5_GCT_IM_LTM_LTM_YLOG_TBL[0]);

	ctImLtmLtmPrintTable(self, 1);

	Im_LTM_LTM_Set_YLOG_Table(priv->ltm45->pipeNo, D_LTM_YLOG_TBL_10, &CtImLtmLtm5_GCT_IM_LTM_LTM_YLOG_TBL[0]);

	ctImLtmLtmPrintTable(self, 2);

	Im_LTM_LTM_Set_YLOG_Table(priv->ltm45->pipeNo, D_LTM_YLOG_TBL_11, &CtImLtmLtm5_GCT_IM_LTM_LTM_YLOG_TBL[0]);

	ctImLtmLtmPrintTable(self, 3);

	return D_DDIM_OK;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_1: "
gint32 ct_im_ltm_ltm5_2_1(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Ctrl_Axi(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM ctrl axi error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_2: "
gint32 ct_im_ltm_ltm5_2_2(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Get_AxiReadStat(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM get axi read stat error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_3: "
gint32 ct_im_ltm_ltm5_2_3(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Get_AxiWriteStat(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM get axi write stat error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_4: "
gint32 ct_im_ltm_ltm5_2_4(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Get_AxiCtrlParam(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM get axi ctrl param error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_5: "
gint32 ct_im_ltm_ltm5_2_5(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Set_AxiCtrlParam(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set axi ctrl param error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_6: "
gint32 ct_im_ltm_ltm5_2_6(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Ctrl_Common(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set ctrl common error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_7: "
gint32 ct_im_ltm_ltm5_2_7(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Ctrl_ModeSDRAMInput(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set ctrl sdram input error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_8: "
gint32 ct_im_ltm_ltm5_2_8(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Set_InAddr_Info_Rgb(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "TLM set inaddr rgb error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_9: "
gint32 ct_im_ltm_ltm5_2_9(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Set_InData_Info(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set indata error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_10: "
gint32 ct_im_ltm_ltm5_2_10(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Set_OutData_Info(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set outdata error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_11: "
gint32 ct_im_ltm_ltm5_2_11(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Ctrl_ModeB2RDirect(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM ctrl b2r direct error = 0x%x\n", ercd));
	}

	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_12: "
gint32 ct_im_ltm_ltm5_2_12(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Set_MapImage_Resize_Pitch(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set resize pitch error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_13: "
gint32 ct_im_ltm_ltm5_2_13(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Get_LtmBusy(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM get ltm busy error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_14: "
gint32 ct_im_ltm_ltm5_2_14(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Set_High_Frequency_Strength(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set hf strength error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_15: "
gint32 ct_im_ltm_ltm5_2_15(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Set_Internal_Param(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set internal param error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_16: "
gint32 ct_im_ltm_ltm5_2_16(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Ctrl_Blend(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM ctrl blend error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_17: "
gint32 ct_im_ltm_ltm5_2_17(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Ctrl_Chroma_Correction_Strength(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM ctrl chroma correction strength error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_18: "
gint32 ct_im_ltm_ltm5_2_18(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Ctrl_Ylog_Tbl(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM ctrl ylog tbl error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_19: "
gint32 ct_im_ltm_ltm5_2_19(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Get_Active_Ylog_Tbl_No(priv->ltm45->pipeNo, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM get active ylog tbl no error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_20: "
gint32 ct_im_ltm_ltm5_2_20(CtImLtmLtm5 *self)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	gint32 ercd = D_DDIM_OK;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Set_YLOG_Table(priv->ltm45->pipeNo, 0, NULL);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM set ylog tbl error = 0x%x\n", ercd));
	}
	return ercd;
}

#undef CtImLtmLtm5_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm5_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm5_2_21: "
gint32 ct_im_ltm_ltm5_2_21(CtImLtmLtm5 *self)
{
	gint32 ercd = D_DDIM_OK;
	DDIM_USER_FLGPTN flgPtn;
	DDIM_USER_FLGPTN waiptn;

	Ddim_Print(("%s\n", CtImLtmLtm5_D_IM_LTM_FUNC_NAME));

	waiptn = 0x11110000;
	ercd = Im_LTM_LTM_WaitEnd(&flgPtn, waiptn, 100);
	if(ercd != D_DDIM_OK){
		Ddim_Print((CtImLtmLtm5_D_IM_LTM_FUNC_NAME "LTM wait end error = 0x%x\n", ercd));
	}
	return ercd;
}

void ct_im_ltm_ltm5_set_ltm4(CtImLtmLtm5 *self,CtImLtmLtm4 *ltm4)
{
	CtImLtmLtm5Private *priv = CT_IM_LTM_LTM5_GET_PRIVATE(self);
	priv->ltm45=ltm4;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmLtm5类的一个实例
 */
CtImLtmLtm5* ct_im_ltm_ltm5_new()
{
	CtImLtmLtm5 *self = g_object_new(CT_TYPE_IM_LTM_LTM_5,NULL);
	return self;
}
