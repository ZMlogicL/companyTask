/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr5类
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
#include "ctimcnr5.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr5, ct_im_cnr5, G_TYPE_OBJECT); 
#define CT_IM_CNR5_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR5, CtImCnr5Private))

struct _CtImCnr5Private
{

};

static VOID ctImCnrOflPrintDebugCtrlHueCc(UCHAR ch);

static void ct_im_cnr5_constructor(CtImCnr5 *self) 
{
//	CtImCnr5Private *priv = CT_IM_CNR5_GET_PRIVATE(self);
}

static void ct_im_cnr5_destructor(CtImCnr5 *self) 
{
//	CtImCnr5Private *priv = CT_IM_CNR5_GET_PRIVATE(self);
}

static VOID ctImCnrOflPrintDebugCtrlHueCc(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	switch(ch){
		case 0:
			loopSta = 0;
			loopEnd = 0;
			break;
		case 1:
			loopSta = 1;
			loopEnd = 1;
			break;
		default:
			loopSta = 0;
			loopEnd = 1;
			break;
	}

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("CDCB      = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CPHPT.bit.CDCB));
		Ddim_Print(("CDCR      = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CPHPT.bit.CDCR));
		Ddim_Print(("KCB       = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CPHPTK.bit.KCB));
		Ddim_Print(("KCR       = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CPHPTK.bit.KCR));

		Ddim_Print(("CDSCLBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_1));
		Ddim_Print(("CDSCLBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLBD.CDSCLBD1.bit.CDSCLBD_2));
		Ddim_Print(("CDSCLBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_3));
		Ddim_Print(("CDSCLBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLBD.CDSCLBD2.bit.CDSCLBD_4));
		Ddim_Print(("CDSCLBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLBD.CDSCLBD3.bit.CDSCLBD_5));

		Ddim_Print(("CDSCLOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_0));
		Ddim_Print(("CDSCLOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLOF.CDSCLOF1.bit.CDSCLOF_1));
		Ddim_Print(("CDSCLOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_2));
		Ddim_Print(("CDSCLOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLOF.CDSCLOF2.bit.CDSCLOF_3));
		Ddim_Print(("CDSCLOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_4));
		Ddim_Print(("CDSCLOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLOF.CDSCLOF3.bit.CDSCLOF_5));

		Ddim_Print(("CDSCLGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLGA.CDSCLGA1.bit.CDSCLGA_0));
		Ddim_Print(("CDSCLGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLGA.CDSCLGA1.bit.CDSCLGA_1));
		Ddim_Print(("CDSCLGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLGA.CDSCLGA2.bit.CDSCLGA_2));
		Ddim_Print(("CDSCLGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLGA.CDSCLGA2.bit.CDSCLGA_3));
		Ddim_Print(("CDSCLGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLGA.CDSCLGA3.bit.CDSCLGA_4));
		Ddim_Print(("CDSCLGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CDSCLGA.CDSCLGA3.bit.CDSCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_27: "
INT32 ct_im_cnr_ofl_1_27(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 imErcd;
	UINT32 loopcnt;
	T_IM_CNR_HUE_SPEC_TABLE sprHueCtrl[3] = {
		[0] = {	//max
			.cd_cb = 0x7F,
			.cd_cr = 0x7F,
			.k_cb = 0x3FF,
			.k_cr = 0x3FF,
			.bd1 = 0x7FF,
			.bd2 = 0x7FF,
			.bd3 = 0x7FF,
			.bd4 = 0x7FF,
			.bd5 = 0x7FF,
			.of0 = 0x100,
			.of1 = 0x100,
			.of2 = 0x100,
			.of3 = 0x100,
			.of4 = 0x100,
			.of5 = 0x100,
			.gain0 = 0x03FF,
			.gain1 = 0x03FF,
			.gain2 = 0x03FF,
			.gain3 = 0x03FF,
			.gain4 = 0x03FF,
			.gain5 = 0x03FF
		},
		[1] = {	//min
			.cd_cb = -0x80,
			.cd_cr = -0x80,
			.k_cb = 0,
			.k_cr = 0,
			.bd1 = 0x00,
			.bd2 = 0x00,
			.bd3 = 0x00,
			.bd4 = 0x00,
			.bd5 = 0x00,
			.of0 = 0x00,
			.of1 = 0x00,
			.of2 = 0x00,
			.of3 = 0x00,
			.of4 = 0x00,
			.of5 = 0x00,
			.gain0 = -0x0400,
			.gain1 = -0x0400,
			.gain2 = -0x0400,
			.gain3 = -0x0400,
			.gain4 = -0x0400,
			.gain5 = -0x0400,
		},
		[2] = {	//countup
			.cd_cb = 1,
			.cd_cr = 2,
			.k_cb = 3,
			.k_cr = 4,
			.bd1 = 0x05,
			.bd2 = 0x06,
			.bd3 = 0x07,
			.bd4 = 0x08,
			.bd5 = 0x09,
			.of0 = 0x0A,
			.of1 = 0x0B,
			.of2 = 0x0C,
			.of3 = 0x0D,
			.of4 = 0x0E,
			.of5 = 0x0F,
			.gain0 = 0x0010,
			.gain1 = 0x0011,
			.gain2 = 0x0012,
			.gain3 = 0x0013,
			.gain4 = 0x0014,
			.gain5 = 0x0015
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	for(loopcnt = 0; loopcnt < (sizeof(sprHueCtrl) / sizeof(sprHueCtrl[0])); loopcnt++) {
		Ddim_Print(("** %u\n", loopcnt));
		imErcd = Im_CNR_OFL_Set_CSPR_Hue_Specified_Table(ch, &sprHueCtrl[loopcnt]);
		if(imErcd != D_DDIM_OK) {
			Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
			return imErcd;
		}
		ctImCnrOflPrintDebugCtrlHueCc(ch);
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_31: "
INT32 ct_im_cnr_ofl_1_31(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.gradation_keep_en = E_IM_CNR_ONOFF_ENABLE,
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
			.y_threshold_cor = 0xFF,
			.y_threshold_gain = 0x01FF,
			.y_threshold_dym_en = E_IM_CNR_ONOFF_ENABLE,
			.y_threshold_scl_en = E_IM_CNR_ONOFF_ENABLE,
			.c_y_threshold_scl_en = E_IM_CNR_ONOFF_ENABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_ENABLE,
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
			.y_threshold_cor = 0xFF,
			.y_threshold_gain = 0x01FF,
			.y_threshold_dym_en = E_IM_CNR_ONOFF_ENABLE,
			.y_threshold_scl_en = E_IM_CNR_ONOFF_ENABLE,
			.c_y_threshold_scl_en = E_IM_CNR_ONOFF_ENABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_ENABLE,
		},
		.whitening_enable = E_IM_CNR_ONOFF_ENABLE,
		.whitening_value = 0xF,
		.whitening_base = E_IM_CNR_WHITEN_BASE_MIDDLE,
		.c_blend_md = E_IM_CNR_C_BLEND_MD_COL_DIFF_EDGE,
		.c_alpha_blend = 0xF,
		.c_range = E_IM_CNR_ONOFF_ENABLE,
		.c_range_mode = E_IM_CNR_C_RANGE_MODE_0_32,
	};
	T_IM_CNR_RDMA_DATA_CTRL_C rdmaCtrlC;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_Ctrl_C(&sprCtrlC, &rdmaCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_Ctrl_C() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCtrlC.CSPREN   = 0x%lx\n", rdmaCtrlC.CSPREN.word));
	Ddim_Print(("rdmaCtrlC.CGDKEN   = 0x%lx\n", rdmaCtrlC.CGDKEN.word));
	Ddim_Print(("rdmaCtrlC.MCEN     = 0x%lx\n", rdmaCtrlC.MCEN.word));
	Ddim_Print(("rdmaCtrlC.MCYTHH   = 0x%lx\n", rdmaCtrlC.MCYTHH.word));
	Ddim_Print(("rdmaCtrlC.MCYTHV   = 0x%lx\n", rdmaCtrlC.MCYTHV.word));
	Ddim_Print(("rdmaCtrlC.MCCTHH   = 0x%lx\n", rdmaCtrlC.MCCTHH.word));
	Ddim_Print(("rdmaCtrlC.MCCTHV   = 0x%lx\n", rdmaCtrlC.MCCTHV.word));
	Ddim_Print(("rdmaCtrlC.MCYDYM   = 0x%lx\n", rdmaCtrlC.MCYDYM.word));
	Ddim_Print(("rdmaCtrlC.MCYDYMDT = 0x%lx\n", rdmaCtrlC.MCYDYMDT.word));
	Ddim_Print(("rdmaCtrlC.MCYSCL   = 0x%lx\n", rdmaCtrlC.MCYSCL.word));
	Ddim_Print(("rdmaCtrlC.MCCSCL   = 0x%lx\n", rdmaCtrlC.MCCSCL.word));
	Ddim_Print(("rdmaCtrlC.MCSSCL   = 0x%lx\n", rdmaCtrlC.MCSSCL.word));
	Ddim_Print(("rdmaCtrlC.LCEN     = 0x%lx\n", rdmaCtrlC.LCEN.word));
	Ddim_Print(("rdmaCtrlC.LCYTHH   = 0x%lx\n", rdmaCtrlC.LCYTHH.word));
	Ddim_Print(("rdmaCtrlC.LCYTHV   = 0x%lx\n", rdmaCtrlC.LCYTHV.word));
	Ddim_Print(("rdmaCtrlC.LCCTHH   = 0x%lx\n", rdmaCtrlC.LCCTHH.word));
	Ddim_Print(("rdmaCtrlC.LCCTHV   = 0x%lx\n", rdmaCtrlC.LCCTHV.word));
	Ddim_Print(("rdmaCtrlC.LCYDYM   = 0x%lx\n", rdmaCtrlC.LCYDYM.word));
	Ddim_Print(("rdmaCtrlC.LCYDYMDT = 0x%lx\n", rdmaCtrlC.LCYDYMDT.word));
	Ddim_Print(("rdmaCtrlC.LCYSC    = 0x%lx\n", rdmaCtrlC.LCYSCL.word));
	Ddim_Print(("rdmaCtrlC.LCCSC    = 0x%lx\n", rdmaCtrlC.LCCSCL.word));
	Ddim_Print(("rdmaCtrlC.LCSSC    = 0x%lx\n", rdmaCtrlC.LCSSCL.word));
	Ddim_Print(("rdmaCtrlC.BLEND    = 0x%lx\n", rdmaCtrlC.BLEND.word));
	Ddim_Print(("rdmaCtrlC.WHTMD    = 0x%lx\n", rdmaCtrlC.WHTMD.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_37: "
INT32 ct_im_cnr_ofl_1_37(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_TABLE csprMidYTable = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL rdmaCsprMidYTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table(&csprMidYTable, &rdmaCsprMidYTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprMidYTable.MCYSCLOF.MCYSCLOF1 = 0x%lx\n", rdmaCsprMidYTable.MCYSCLOF.MCYSCLOF1.word));
	Ddim_Print(("rdmaCsprMidYTable.MCYSCLOF.MCYSCLOF2 = 0x%lx\n", rdmaCsprMidYTable.MCYSCLOF.MCYSCLOF2.word));
	Ddim_Print(("rdmaCsprMidYTable.MCYSCLGA.MCYSCLGA1 = 0x%lx\n", rdmaCsprMidYTable.MCYSCLGA.MCYSCLGA1.word));
	Ddim_Print(("rdmaCsprMidYTable.MCYSCLGA.MCYSCLGA2 = 0x%lx\n", rdmaCsprMidYTable.MCYSCLGA.MCYSCLGA2.word));
	Ddim_Print(("rdmaCsprMidYTable.MCYSCLBD.MCYSCLBD1 = 0x%lx\n", rdmaCsprMidYTable.MCYSCLBD.MCYSCLBD1.word));
	Ddim_Print(("rdmaCsprMidYTable.MCYSCLBD.MCYSCLBD2 = 0x%lx\n", rdmaCsprMidYTable.MCYSCLBD.MCYSCLBD2.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_38: "
INT32 ct_im_cnr_ofl_1_38(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL* C_SPRR_MID_CC_Y_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_Y_Table(ch, &C_SPRR_MID_CC_Y_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_Y_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_SPRR_MID_CC_Y_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_39: "
INT32 ct_im_cnr_ofl_1_39(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_TABLE sprCsprMidCcY = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL rdmaCsprMidCcYTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_Y_Table(&sprCsprMidCcY, &rdmaCsprMidCcYTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_Y_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprMidCcYTable.MCCSCLOF.MCCSCLOF1 = 0x%lx\n", rdmaCsprMidCcYTable.MCCSCLOF.MCCSCLOF1.word));
	Ddim_Print(("rdmaCsprMidCcYTable.MCCSCLOF.MCCSCLOF2 = 0x%lx\n", rdmaCsprMidCcYTable.MCCSCLOF.MCCSCLOF2.word));
	Ddim_Print(("rdmaCsprMidCcYTable.MCCSCLGA.MCCSCLGA1 = 0x%lx\n", rdmaCsprMidCcYTable.MCCSCLGA.MCCSCLGA1.word));
	Ddim_Print(("rdmaCsprMidCcYTable.MCCSCLGA.MCCSCLGA2 = 0x%lx\n", rdmaCsprMidCcYTable.MCCSCLGA.MCCSCLGA2.word));
	Ddim_Print(("rdmaCsprMidCcYTable.MCCSCLBD.MCCSCLBD1 = 0x%lx\n", rdmaCsprMidCcYTable.MCCSCLBD.MCCSCLBD1.word));
	Ddim_Print(("rdmaCsprMidCcYTable.MCCSCLBD.MCCSCLBD2 = 0x%lx\n", rdmaCsprMidCcYTable.MCCSCLBD.MCCSCLBD2.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_40: "
INT32 ct_im_cnr_ofl_1_40(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL* C_CSPR_MID_CC_C_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table(ch, &C_CSPR_MID_CC_C_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_MID_CC_C_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_41: "
INT32 ct_im_cnr_ofl_1_41(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_TABLE sprCsprMidCcC = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL rdmaCsprMidCcCTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table(&sprCsprMidCcC, &rdmaCsprMidCcCTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprMidCcCTable.MCSSCLOF.MCCSCLOF1 = 0x%lx\n", rdmaCsprMidCcCTable.MCSSCLOF.MCSSCLOF1.word));
	Ddim_Print(("rdmaCsprMidCcCTable.MCSSCLOF.MCCSCLOF2 = 0x%lx\n", rdmaCsprMidCcCTable.MCSSCLOF.MCSSCLOF2.word));
	Ddim_Print(("rdmaCsprMidCcCTable.MCSSCLGA.MCCSCLGA1 = 0x%lx\n", rdmaCsprMidCcCTable.MCSSCLGA.MCSSCLGA1.word));
	Ddim_Print(("rdmaCsprMidCcCTable.MCSSCLGA.MCCSCLGA2 = 0x%lx\n", rdmaCsprMidCcCTable.MCSSCLGA.MCSSCLGA2.word));
	Ddim_Print(("rdmaCsprMidCcCTable.MCSSCLBD.MCCSCLBD1 = 0x%lx\n", rdmaCsprMidCcCTable.MCSSCLBD.MCSSCLBD1.word));
	Ddim_Print(("rdmaCsprMidCcCTable.MCSSCLBD.MCCSCLBD2 = 0x%lx\n", rdmaCsprMidCcCTable.MCSSCLBD.MCSSCLBD2.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_42: "
INT32 ct_im_cnr_ofl_1_42(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL* C_CSPR_LOW_Y_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_Y_Table(ch, &C_CSPR_LOW_Y_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_Y_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_LOW_Y_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_43: "
INT32 ct_im_cnr_ofl_1_43(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_TABLE csprLowYTable = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL rdmaCsprLowYTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table(&csprLowYTable, &rdmaCsprLowYTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprLowYTable.LCYSCLOF.LCYSCLOF1 = 0x%lx\n", rdmaCsprLowYTable.LCYSCLOF.LCYSCLOF1.word));
	Ddim_Print(("rdmaCsprLowYTable.LCYSCLOF.LCYSCLOF2 = 0x%lx\n", rdmaCsprLowYTable.LCYSCLOF.LCYSCLOF2.word));
	Ddim_Print(("rdmaCsprLowYTable.LCYSCLGA.LCYSCLGA1 = 0x%lx\n", rdmaCsprLowYTable.LCYSCLGA.LCYSCLGA1.word));
	Ddim_Print(("rdmaCsprLowYTable.LCYSCLGA.LCYSCLGA2 = 0x%lx\n", rdmaCsprLowYTable.LCYSCLGA.LCYSCLGA2.word));
	Ddim_Print(("rdmaCsprLowYTable.LCYSCLBD.LCYSCLBD1 = 0x%lx\n", rdmaCsprLowYTable.LCYSCLBD.LCYSCLBD1.word));
	Ddim_Print(("rdmaCsprLowYTable.LCYSCLBD.LCYSCLBD2 = 0x%lx\n", rdmaCsprLowYTable.LCYSCLBD.LCYSCLBD2.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_44: "
INT32 ct_im_cnr_ofl_1_44(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL* C_CSPR_LOW_CC_Y_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_Y_Table(ch, &C_CSPR_LOW_CC_Y_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_Y_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_LOW_CC_Y_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_45: "
INT32 ct_im_cnr_ofl_1_45(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_TABLE sprCsprLowCcY = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL rdmaCsprLowCcYTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table(&sprCsprLowCcY, &rdmaCsprLowCcYTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprLowCcYTable.LCCSCLOF.LCCSCLOF1 = 0x%lx\n", rdmaCsprLowCcYTable.LCCSCLOF.LCCSCLOF1.word));
	Ddim_Print(("rdmaCsprLowCcYTable.LCCSCLOF.LCCSCLOF2 = 0x%lx\n", rdmaCsprLowCcYTable.LCCSCLOF.LCCSCLOF2.word));
	Ddim_Print(("rdmaCsprLowCcYTable.LCCSCLGA.LCCSCLGA1 = 0x%lx\n", rdmaCsprLowCcYTable.LCCSCLGA.LCCSCLGA1.word));
	Ddim_Print(("rdmaCsprLowCcYTable.LCCSCLGA.LCCSCLGA2 = 0x%lx\n", rdmaCsprLowCcYTable.LCCSCLGA.LCCSCLGA2.word));
	Ddim_Print(("rdmaCsprLowCcYTable.LCCSCLBD.LCCSCLBD1 = 0x%lx\n", rdmaCsprLowCcYTable.LCCSCLBD.LCCSCLBD1.word));
	Ddim_Print(("rdmaCsprLowCcYTable.LCCSCLBD.LCCSCLBD2 = 0x%lx\n", rdmaCsprLowCcYTable.LCCSCLBD.LCCSCLBD2.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_46: "
INT32 ct_im_cnr_ofl_1_46(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL* C_CSPR_LOW_CC_C_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_C_Table(ch, &C_CSPR_LOW_CC_C_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_C_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_LOW_CC_C_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_47: "
INT32 ct_im_cnr_ofl_1_47(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_TABLE sprCsprLowCcC = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL rdmaCsprLowCcCTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table(&sprCsprLowCcC, &rdmaCsprLowCcCTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprLowCcCTable.LCSSCLOF.LCCSCLOF1 = 0x%lx\n", rdmaCsprLowCcCTable.LCSSCLOF.LCSSCLOF1.word));
	Ddim_Print(("rdmaCsprLowCcCTable.LCSSCLOF.LCCSCLOF2 = 0x%lx\n", rdmaCsprLowCcCTable.LCSSCLOF.LCSSCLOF2.word));
	Ddim_Print(("rdmaCsprLowCcCTable.LCSSCLGA.LCCSCLGA1 = 0x%lx\n", rdmaCsprLowCcCTable.LCSSCLGA.LCSSCLGA1.word));
	Ddim_Print(("rdmaCsprLowCcCTable.LCSSCLGA.LCCSCLGA2 = 0x%lx\n", rdmaCsprLowCcCTable.LCSSCLGA.LCSSCLGA2.word));
	Ddim_Print(("rdmaCsprLowCcCTable.LCSSCLBD.LCCSCLBD1 = 0x%lx\n", rdmaCsprLowCcCTable.LCSSCLBD.LCSSCLBD1.word));
	Ddim_Print(("rdmaCsprLowCcCTable.LCSSCLBD.LCCSCLBD2 = 0x%lx\n", rdmaCsprLowCcCTable.LCSSCLBD.LCSSCLBD2.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_48: "
INT32 ct_im_cnr_ofl_1_48(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL* C_CSPR_EDGE_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_Edge_Table(ch, &C_CSPR_EDGE_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_Edge_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_EDGE_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_49: "
INT32 ct_im_cnr_ofl_1_49(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_TABLE sprCsprEdge = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0x3F,
		.of1 = 0x3F,
		.of2 = 0x3F,
		.of3 = 0x3F,
		.of4 = 0x3F,
		.of5 = 0x3F,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL rdmaCsprEdgeTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table(&sprCsprEdge, &rdmaCsprEdgeTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprEdgeTable.CESCLOF.CESCLOF1 = 0x%lx\n", rdmaCsprEdgeTable.CESCLOF.CESCLOF1.word));
	Ddim_Print(("rdmaCsprEdgeTable.CESCLOF.CESCLOF2 = 0x%lx\n", rdmaCsprEdgeTable.CESCLOF.CESCLOF2.word));
	Ddim_Print(("rdmaCsprEdgeTable.CESCLGA.CESCLGA1 = 0x%lx\n", rdmaCsprEdgeTable.CESCLGA.CESCLGA1.word));
	Ddim_Print(("rdmaCsprEdgeTable.CESCLGA.CESCLGA2 = 0x%lx\n", rdmaCsprEdgeTable.CESCLGA.CESCLGA2.word));
	Ddim_Print(("rdmaCsprEdgeTable.CESCLBD.CESCLBD1 = 0x%lx\n", rdmaCsprEdgeTable.CESCLBD.CESCLBD1.word));
	Ddim_Print(("rdmaCsprEdgeTable.CESCLBD.CESCLBD2 = 0x%lx\n", rdmaCsprEdgeTable.CESCLBD.CESCLBD2.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_50: "
INT32 ct_im_cnr_ofl_1_50(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL* C_CSPR_HUE_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OFL_CSPR_Hue_Spec_Table(ch, &C_CSPR_HUE_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OFL_CSPR_Hue_Spec_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_HUE_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_1_51: "
INT32 ct_im_cnr_ofl_1_51(CtImCnr5* self)
{
	INT32 imErcd;
	T_IM_CNR_HUE_SPEC_TABLE sprCsprHue = {
		.cd_cb = 0xFF,
		.cd_cr = 0xFF,
		.k_cb = 0x3FF,
		.k_cr = 0x3FF,
		.bd1 = 0x7FF,
		.bd2 = 0x7FF,
		.bd3 = 0x7FF,
		.bd4 = 0x7FF,
		.bd5 = 0x7FF,
		.of0 = 0x100,
		.of1 = 0x100,
		.of2 = 0x100,
		.of3 = 0x100,
		.of4 = 0x100,
		.of5 = 0x100,
		.gain0 = 0x03FF,
		.gain1 = 0x03FF,
		.gain2 = 0x03FF,
		.gain3 = 0x03FF,
		.gain4 = 0x03FF,
		.gain5 = 0x03FF
	};
	T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL rdmaCsprHueTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table(&sprCsprHue, &rdmaCsprHueTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprHueTable.CPHPT            = 0x%lx\n", rdmaCsprHueTable.CPHPT.word));
	Ddim_Print(("rdmaCsprHueTable.CPHPTK           = 0x%lx\n", rdmaCsprHueTable.CPHPTK.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLOF.CDSCLOF1 = 0x%lx\n", rdmaCsprHueTable.CDSCLOF.CDSCLOF1.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLOF.CDSCLOF2 = 0x%lx\n", rdmaCsprHueTable.CDSCLOF.CDSCLOF2.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLOF.CDSCLOF3 = 0x%lx\n", rdmaCsprHueTable.CDSCLOF.CDSCLOF3.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLGA.CDSCLGA1 = 0x%lx\n", rdmaCsprHueTable.CDSCLGA.CDSCLGA1.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLGA.CDSCLGA2 = 0x%lx\n", rdmaCsprHueTable.CDSCLGA.CDSCLGA2.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLGA.CDSCLGA3 = 0x%lx\n", rdmaCsprHueTable.CDSCLGA.CDSCLGA3.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLBD.CDSCLBD1 = 0x%lx\n", rdmaCsprHueTable.CDSCLBD.CDSCLBD1.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLBD.CDSCLBD2 = 0x%lx\n", rdmaCsprHueTable.CDSCLBD.CDSCLBD2.word));
	Ddim_Print(("rdmaCsprHueTable.CDSCLBD.CDSCLBD3 = 0x%lx\n", rdmaCsprHueTable.CDSCLBD.CDSCLBD3.word));

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_11: "
INT32 ct_im_cnr_6_11(CtImCnr5* self)
{
	UCHAR ch = self->ch5;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_HUE_SPEC_TABLE	sprCsprHue = {
		.cd_cb = 0xFF,
		.cd_cr = 0xFF,
		.k_cb = 0x3FF,
		.k_cr = 0x3FF,
		.bd1 = 0x7FF,
		.bd2 = 0x7FF,
		.bd3 = 0x7FF,
		.bd4 = 0x7FF,
		.bd5 = 0x7FF,
		.of0 = 0x100,
		.of1 = 0x100,
		.of2 = 0x100,
		.of3 = 0x100,
		.of4 = 0x100,
		.of5 = 0x100,
		.gain0 = 0x07FF,
		.gain1 = 0x07FF,
		.gain2 = 0x07FF,
		.gain3 = 0x07FF,
		.gain4 = 0x07FF,
		.gain5 = 0x07FF
	};
	T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL	rdmaHueTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL*	C_HUE_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Hue_Spec_Table(ch, &C_HUE_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Hue_Spec_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table(&sprCsprHue, &rdmaHueTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_HUE_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaHueTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCtrlHueCc(0);
		ctImCnrOflPrintDebugCtrlHueCc(1);
	}
	else{
		ctImCnrOflPrintDebugCtrlHueCc(ch);
	}

	return D_DDIM_OK;
}

CtImCnr5* ct_im_cnr5_new(void) 
{
    CtImCnr5 *self = g_object_new(CT_TYPE_IM_CNR5, NULL);
    return self;
}
