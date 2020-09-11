/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr11类
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
#include "ctimcnr6.h"
#include "ctimcnr7.h"
#include "ctimcnr8.h"
#include "ctimcnr9.h"
#include "ctimcnr10.h"
#include "ctimcnr11.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr11, ct_im_cnr11, G_TYPE_OBJECT); 
#define CT_IM_CNR11_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR11, CtImCnr11Private))

struct _CtImCnr11Private
{

};

static void ct_im_cnr11_constructor(CtImCnr11 *self) 
{
//	CtImCnr11Private *priv = CT_IM_CNR11_GET_PRIVATE(self);
}

static void ct_im_cnr11_destructor(CtImCnr11 *self) 
{
//	CtImCnr11Private *priv = CT_IM_CNR11_GET_PRIVATE(self);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_45: "
INT32 ct_im_cnr_otf_3_45(CtImCnr11 *self)
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

	imErcd = Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table(&sprCsprEdge, &rdmaCsprEdgeTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table() error = 0x%x\n", imErcd));
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
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_46: "
INT32 ct_im_cnr_otf_3_46(CtImCnr11 *self)
{
	UCHAR ch = self->ch11;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL* C_CSPR_HUE_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OTF_CSPR_Hue_Spec_Table(ch, &C_CSPR_HUE_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OTF_CSPR_Hue_Spec_Table() error = 0x%x\n", imErcd));
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
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_47: "
INT32 ct_im_cnr_otf_3_47(CtImCnr11 *self)
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
		.gain0 = 0x07FF,
		.gain1 = 0x07FF,
		.gain2 = 0x07FF,
		.gain3 = 0x07FF,
		.gain4 = 0x07FF,
		.gain5 = 0x07FF
	};
	T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL rdmaCsprHueTable;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OTF_CSPR_Hue_Spec_Table(&sprCsprHue, &rdmaCsprHueTable);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OTF_CSPR_Hue_Spec_Table() error = 0x%x\n", imErcd));
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
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_48: "
INT32 ct_im_cnr_otf_3_48(CtImCnr11 *self)
{
	UCHAR ch = self->ch11;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL* C_CSPR_SPRS_CC_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRS_CC_Table(ch, &C_CSPR_SPRS_CC_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRS_CC_Table() error = 0x%x\n", imErcd));
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
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_49: "
INT32 ct_im_cnr_otf_3_49(CtImCnr11 *self)
{
	INT32 imErcd;
	T_IM_CNR_CTRL_CC_SRC_DST csprSprsCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
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

	imErcd = Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table(&csprSprsCc, &rdmaCsprSprsCc);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table() error = 0x%x\n", imErcd));
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

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_50: "
INT32 ct_im_cnr_otf_3_50(CtImCnr11 *self)
{
	UCHAR ch = self->ch11;
	INT32 imErcd;
	const T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL* C_CSPR_SPRD_CC_TBL;
	ULONG size;
	ULONG* ptAddr;
	UINT32 loopcnt;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRD_CC_Table(ch, &C_CSPR_SPRD_CC_TBL, &size);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRD_CC_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("size = 0x%lx\n", size));
	ptAddr = (ULONG*)C_CSPR_SPRD_CC_TBL;
	for(loopcnt = 0; loopcnt < size; loopcnt+=4) {
		Ddim_Print(("address = 0x%lx\n", *ptAddr));
		ptAddr++;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_51: "
INT32 ct_im_cnr_otf_3_51(CtImCnr11 *self)
{
	INT32 imErcd;
	T_IM_CNR_CTRL_CC_SRC_DST csprSprdCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRD_CC_TBL rdmaCsprSprdCc;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table(&csprSprdCc, &rdmaCsprSprdCc);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table() error = 0x%x\n", imErcd));
		return imErcd;
	}

	// Check parameter
	Ddim_Print(("rdmaCsprSprdCc.SPRD               = 0x%lx\n", rdmaCsprSprdCc.SPRD.word));

	Ddim_Print(("rdmaCsprSprdCc.SPRDCBOF.SPRDCBOF1 = 0x%lx\n", rdmaCsprSprdCc.SPRDCBOF.SPRDCBOF1.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCBOF.SPRDCBOF2 = 0x%lx\n", rdmaCsprSprdCc.SPRDCBOF.SPRDCBOF2.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCBGA.SPRDCBGA1 = 0x%lx\n", rdmaCsprSprdCc.SPRDCBGA.SPRDCBGA1.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCBGA.SPRDCBGA2 = 0x%lx\n", rdmaCsprSprdCc.SPRDCBGA.SPRDCBGA2.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCBGA.SPRDCBGA3 = 0x%lx\n", rdmaCsprSprdCc.SPRDCBGA.SPRDCBGA3.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCBBD.SPRDCBBD1 = 0x%lx\n", rdmaCsprSprdCc.SPRDCBBD.SPRDCBBD1.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCBBD.SPRDCBBD2 = 0x%lx\n", rdmaCsprSprdCc.SPRDCBBD.SPRDCBBD2.word));

	Ddim_Print(("rdmaCsprSprdCc.SPRDCROF.SPRDCROF1 = 0x%lx\n", rdmaCsprSprdCc.SPRDCROF.SPRDCROF1.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCROF.SPRDCROF2 = 0x%lx\n", rdmaCsprSprdCc.SPRDCROF.SPRDCROF2.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCRGA.SPRDCRGA1 = 0x%lx\n", rdmaCsprSprdCc.SPRDCRGA.SPRDCRGA1.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCRGA.SPRDCRGA2 = 0x%lx\n", rdmaCsprSprdCc.SPRDCRGA.SPRDCRGA2.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCRGA.SPRDCRGA3 = 0x%lx\n", rdmaCsprSprdCc.SPRDCRGA.SPRDCRGA3.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCRBD.SPRDCRBD1 = 0x%lx\n", rdmaCsprSprdCc.SPRDCRBD.SPRDCRBD1.word));
	Ddim_Print(("rdmaCsprSprdCc.SPRDCRBD.SPRDCRBD2 = 0x%lx\n", rdmaCsprSprdCc.SPRDCRBD.SPRDCRBD2.word));

	return imErcd;
}

INT32 ct_im_cnr_run_3(CtImCnr11 *self, const UINT32 ctNo2nd, CtImCnr6 *ctim6)
{
	CtImCnr7 *ctim7 = ct_im_cnr7_new();
	ctim7->ch7 = self->ch11;
	CtImCnr8 *ctim8 = ct_im_cnr8_new();
	ctim8->ch8 = self->ch11;
	CtImCnr9 *ctim9 = ct_im_cnr9_new();
	ctim9->ch9 = self->ch11;	
	CtImCnr10 *ctim10 = ct_im_cnr10_new();
	ctim10->ch10 = self->ch11; 

	Ddim_Print(("ct_im_cnr_run_3 ctNo2nd = 0x%x ctNo3rd = 0x%x\n", ctNo2nd, self->ch11));
	switch(ctNo2nd) {
		// Test-3-1
		case 1:
			return ct_im_cnr_otf_3_1(ctim6);

		// Test-3-2
		case 2:
			return ct_im_cnr_otf_3_2(ctim6);

		// Test-3-3
		case 3:
			return ct_im_cnr_otf_3_3(ctim6);

		// Test-3-4
		case 4:
			return ct_im_cnr_otf_3_4(ctim6);

		// Test-3-5
		case 5:
			return ct_im_cnr_otf_3_5(ctim6);

		// Test-3-6
		case 6:
			return ct_im_cnr_otf_3_6(ctim6);

		// Test-3-7
		case 7:
			return ct_im_cnr_otf_3_7(ctim6);

		// Test-3-8
		case 8:
			return ct_im_cnr_otf_3_8(ctim6);

		// Test-3-9
		case 9:
			return ct_im_cnr_otf_3_9(ctim7);

		// Test-3-10
		case 10:
			return ct_im_cnr_otf_3_10(ctim7);

		// Test-3-11
		case 11:
			return ct_im_cnr_otf_3_11(ctim7);

		// Test-3-12
		case 12:
			return ct_im_cnr_otf_3_12(ctim7);

		// Test-3-13
		case 13:
			return ct_im_cnr_otf_3_13(ctim7);

		// Test-3-14
		case 14:
			return ct_im_cnr_otf_3_14(ctim8);

		// Test-3-15
		case 15:
			return ct_im_cnr_otf_3_15(ctim8);

		// Test-3-16
		case 16:
			return ct_im_cnr_otf_3_16(ctim8);

		// Test-3-17
		case 17:
			return ct_im_cnr_otf_3_17(ctim8);

		// Test-3-18
		case 18:
			return ct_im_cnr_otf_3_18(ctim9);

		// Test-3-19
		case 19:
			return ct_im_cnr_otf_3_19(ctim9);

		// Test-3-20
		case 20:
			return ct_im_cnr_otf_3_20(ctim7);

		// Test-3-21
		case 21:
			return ct_im_cnr_otf_3_21(ctim8);

		// Test-3-22
		case 22:
			return ct_im_cnr_otf_3_22(ctim8);

		// Test-3-23
		case 23:
			return ct_im_cnr_otf_3_23(ctim9);

		// Test-3-24
		case 24:
			return ct_im_cnr_otf_3_24(ctim9);

		// Test-3-25
		case 25:
			return ct_im_cnr_otf_3_25(ctim10);

		// Test-3-26
		case 26:
			return ct_im_cnr_otf_3_26(ctim7);
// test RDMA
		// Test-3-30
		case 30:
			return ct_im_cnr_otf_3_30(ctim10);
		// Test-3-31
		case 31:
			return ct_im_cnr_otf_3_31(ctim10);
		// Test-3-32
		case 32:
			return ct_im_cnr_otf_3_32(ctim10);
		// Test-3-33
		case 33:
			return ct_im_cnr_otf_3_33(ctim10);
		// Test-3-34
		case 34:
			return ct_im_cnr_otf_3_34(ctim10);
		// Test-3-35
		case 35:
			return ct_im_cnr_otf_3_35(ctim10);
		// Test-3-36
		case 36:
			return ct_im_cnr_otf_3_36(ctim10);
		// Test-3-37
		case 37:
			return ct_im_cnr_otf_3_37(ctim10);
		// Test-3-38
		case 38:
			return ct_im_cnr_otf_3_38(ctim10);
		// Test-3-39
		case 39:
			return ct_im_cnr_otf_3_39(ctim10);
		// Test-3-40
		case 40:
			return ct_im_cnr_otf_3_40(ctim10);
		// Test-3-41
		case 41:
			return ct_im_cnr_otf_3_41(ctim10);
		// Test-3-42
		case 42:
			return ct_im_cnr_otf_3_42(ctim10);
		// Test-3-43
		case 43:
			return ct_im_cnr_otf_3_43(ctim10);
		// Test-3-44
		case 44:
			return ct_im_cnr_otf_3_44(ctim10);
		// Test-3-45
		case 45:
			return ct_im_cnr_otf_3_45(self);
		// Test-3-46
		case 46:
			return ct_im_cnr_otf_3_46(self);
		// Test-3-47
		case 47:
			return ct_im_cnr_otf_3_47(self);
		// Test-3-48
		case 48:
			return ct_im_cnr_otf_3_48(self);
		// Test-3-49
		case 49:
			return ct_im_cnr_otf_3_49(self);
		// Test-3-50
		case 50:
			return ct_im_cnr_otf_3_50(self);
		// Test-3-51
		case 51:
			return ct_im_cnr_otf_3_51(self);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	k_object_unref(ctim7);
	k_object_unref(ctim8);
	k_object_unref(ctim9);
	k_object_unref(ctim10);

	return D_DDIM_INPUT_PARAM_ERROR;
}

CtImCnr11* ct_im_cnr11_new(void) 
{
    CtImCnr11 *self = g_object_new(CT_TYPE_IM_CNR11, NULL);
    return self;
}
