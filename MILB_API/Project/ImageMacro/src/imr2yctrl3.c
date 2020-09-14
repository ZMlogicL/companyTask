/*
 * imr2yctrl3.c
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :gonghaotian
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "imr2yctrl3.h"
#include "imr2yctrl2.h"
#include "imr2yctrl.h"
#include "imr2y.h"
#include "imr2y2.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yCtrl3, im_r2y_ctrl3);
#define IM_R2Y_CTRL3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yCtrl3Private, IM_TYPE_R2Y_CTRL3))

#define im_r2y_rounddown_2(a)					(((a) >> 1) << 1)					// for 2 byte alignment


struct _ImR2yCtrl3Private
{
	int a;
};


/*
 * DECLS
 */
static void imR2ySetMapSclTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_map_scl_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetMapSclTblAccessEnable,
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValCrvCtrl( kuint16 pipeNo, const CtrlCrefEdgeTexture* const r2y_ctrl_c_ref_edge_texture_adj_common );
static void imR2ySetRdmaValEgcrvCtrl( kuint16 pipeNo, const CtrlCrefEdgeAdj* const r2y_ctrl_c_ref_edge_adj );
static void imR2ySetRdmaValYbcrvCtrl( kuint16 pipeNo, const CtrlCrefYbBlend* const r2y_ctrl_c_ref_yb_blend );
static void imR2ySetRdmaValColorNrCtrl( kuint16 pipeNo, const R2yCtrlClpf* const r2y_ctrl_clpf );
static void imR2ySetRdmaValChromaSuppressCtrl( kuint16 pipeNo, const R2yCtrlCs* const r2y_ctrl_cs );
static void imR2ySetRdmaValToneCtrlTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num );
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*IMPL
*/
static void im_r2y_ctrl3_constructor(ImR2yCtrl3 *self)
{
	ImR2yCtrl3Private *priv = IM_R2Y_CTRL3_GET_PRIVATE(self);
}

static void im_r2y_ctrl3_destructor(ImR2yCtrl3 *self)
{
	ImR2yCtrl3Private *priv = IM_R2Y_CTRL3_GET_PRIVATE(self);
}

static void imR2ySetMapSclTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPCTL.bit.EMPAEN = enable;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValCrvCtrl( kuint16 pipeNo, const CtrlCrefEdgeTexture* const r2y_ctrl_c_ref_edge_texture_adj_common )
{
	CtrlRdmaCrvVal crv_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_CRV_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	imR2yUtils_SET_REG_SIGNED( crv_ctrl.CRVAF, union io_r2y_crvaf, CRVAFX1, r2y_ctrl_c_ref_edge_texture_adj_common->cbAFocus1Pos );
	imR2yUtils_SET_REG_SIGNED( crv_ctrl.CRVAF, union io_r2y_crvaf, CRVAFY1, r2y_ctrl_c_ref_edge_texture_adj_common->crAFocus1Pos );
	imR2yUtils_SET_REG_SIGNED( crv_ctrl.CRVAF, union io_r2y_crvaf, CRVAFX2, r2y_ctrl_c_ref_edge_texture_adj_common->cbAFocus2Pos );
	imR2yUtils_SET_REG_SIGNED( crv_ctrl.CRVAF, union io_r2y_crvaf, CRVAFY2, r2y_ctrl_c_ref_edge_texture_adj_common->crAFocus2Pos );
	imR2yUtils_SET_REG_SIGNED( crv_ctrl.CRVBF, union io_r2y_crvbf, CRVBFX1, r2y_ctrl_c_ref_edge_texture_adj_common->cbBFocus1Pos );
	imR2yUtils_SET_REG_SIGNED( crv_ctrl.CRVBF, union io_r2y_crvbf, CRVBFY1, r2y_ctrl_c_ref_edge_texture_adj_common->crBFocus1Pos );
	imR2yUtils_SET_REG_SIGNED( crv_ctrl.CRVBF, union io_r2y_crvbf, CRVBFX2, r2y_ctrl_c_ref_edge_texture_adj_common->cbBFocus2Pos );
	imR2yUtils_SET_REG_SIGNED( crv_ctrl.CRVBF, union io_r2y_crvbf, CRVBFY2, r2y_ctrl_c_ref_edge_texture_adj_common->crBFocus2Pos );

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaCrvVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&crv_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValEgcrvCtrl( kuint16 pipeNo, const CtrlCrefEdgeAdj* const r2y_ctrl_c_ref_edge_adj )
{
	CtrlRdmaEgcrvVal egcrv_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGCRV_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	egcrv_ctrl.EGCRVCTL.bit.EGCRAE   = r2y_ctrl_c_ref_edge_adj->areaAEnable;
	egcrv_ctrl.EGCRVCTL.bit.EGCRBE   = r2y_ctrl_c_ref_edge_adj->areaBEnable;
	egcrv_ctrl.EGCRVCTL.bit.EGCRVMRG = r2y_ctrl_c_ref_edge_adj->mergeMethod;

	egcrv_ctrl.EGCRVASCLOF.bit.EGCRVASCLOF1 = r2y_ctrl_c_ref_edge_adj->areaAScaleOffset;
	imR2yUtils_SET_REG_SIGNED( egcrv_ctrl.EGCRVASCLGA, union io_r2y_egcrvasclga, EGCRVASCLGA_0, r2y_ctrl_c_ref_edge_adj->areaAScaleGain[0] );
	imR2yUtils_SET_REG_SIGNED( egcrv_ctrl.EGCRVASCLGA, union io_r2y_egcrvasclga, EGCRVASCLGA_1, r2y_ctrl_c_ref_edge_adj->areaAScaleGain[1] );
	egcrv_ctrl.EGCRVASCLBD.bit.EGCRVASCLBD1 = r2y_ctrl_c_ref_edge_adj->areaAScaleBorder;
	egcrv_ctrl.EGCRVASCLCP.bit.EGCRVASCLCPL = r2y_ctrl_c_ref_edge_adj->areaAScaleClipLo;
	egcrv_ctrl.EGCRVASCLCP.bit.EGCRVASCLCPH = r2y_ctrl_c_ref_edge_adj->areaAScaleClipHi;
	egcrv_ctrl.EGYASCLGA.bit.EGYASCLGA0     = r2y_ctrl_c_ref_edge_adj->areaAYScaleGainP;
	egcrv_ctrl.EGYASCLGA.bit.EGYASCLGA1     = r2y_ctrl_c_ref_edge_adj->areaAYScaleGainM;
	egcrv_ctrl.EGYASCLBD.bit.EGYASCLBD_0    = r2y_ctrl_c_ref_edge_adj->areaAYScaleBorder[0];
	egcrv_ctrl.EGYASCLBD.bit.EGYASCLBD_1    = r2y_ctrl_c_ref_edge_adj->areaAYScaleBorder[1];
	egcrv_ctrl.EGYASCLCLP.bit.EGYASCLCLPL   = r2y_ctrl_c_ref_edge_adj->areaAYScaleClipLo;
	egcrv_ctrl.EGYASCLCLP.bit.EGYASCLCLPH   = r2y_ctrl_c_ref_edge_adj->areaAYScaleClipHi;

	egcrv_ctrl.EGCRVBSCLOF.bit.EGCRVBSCLOF1 = r2y_ctrl_c_ref_edge_adj->areaBScaleOffset;
	imR2yUtils_SET_REG_SIGNED( egcrv_ctrl.EGCRVBSCLGA, union io_r2y_egcrvbsclga, EGCRVBSCLGA_0, r2y_ctrl_c_ref_edge_adj->areaBScaleGain[0] );
	imR2yUtils_SET_REG_SIGNED( egcrv_ctrl.EGCRVBSCLGA, union io_r2y_egcrvbsclga, EGCRVBSCLGA_1, r2y_ctrl_c_ref_edge_adj->areaBScaleGain[1] );
	egcrv_ctrl.EGCRVBSCLBD.bit.EGCRVBSCLBD1 = r2y_ctrl_c_ref_edge_adj->areaBScaleBoarder;
	egcrv_ctrl.EGCRVBSCLCP.bit.EGCRVBSCLCPL = r2y_ctrl_c_ref_edge_adj->areaBScaleClipLo;
	egcrv_ctrl.EGCRVBSCLCP.bit.EGCRVBSCLCPH = r2y_ctrl_c_ref_edge_adj->areaBScaleClipHi;
	egcrv_ctrl.EGYBSCLGA.bit.EGYBSCLGA0     = r2y_ctrl_c_ref_edge_adj->areaBYScaleGainP;
	egcrv_ctrl.EGYBSCLGA.bit.EGYBSCLGA1     = r2y_ctrl_c_ref_edge_adj->areaBYScaleGainM;
	egcrv_ctrl.EGYBSCLBD.bit.EGYBSCLBD_0    = r2y_ctrl_c_ref_edge_adj->areaBYScaleBorder[0];
	egcrv_ctrl.EGYBSCLBD.bit.EGYBSCLBD_1    = r2y_ctrl_c_ref_edge_adj->areaBYScaleBorder[1];
	egcrv_ctrl.EGYBSCLCLP.bit.EGYBSCLCLPL   = r2y_ctrl_c_ref_edge_adj->areaBYScaleClipLo;
	egcrv_ctrl.EGYBSCLCLP.bit.EGYBSCLCLPH   = r2y_ctrl_c_ref_edge_adj->areaBYScaleClipHi;

	egcrv_ctrl.EGCRVCLP.bit.EGCRVCLPP = r2y_ctrl_c_ref_edge_adj->levelClipP;
	egcrv_ctrl.EGCRVCLP.bit.EGCRVCLPM = r2y_ctrl_c_ref_edge_adj->levelClipM;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEgcrvVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&egcrv_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValYbcrvCtrl( kuint16 pipeNo, const CtrlCrefYbBlend* const r2y_ctrl_c_ref_yb_blend )
{
	CtrlRdmaYbcrvVal ybcrv_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_YBCRV_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	ybcrv_ctrl.YBCRVCTL.bit.YBCRAE = r2y_ctrl_c_ref_yb_blend->areaAEnable;
	ybcrv_ctrl.YBCRVCTL.bit.YBCRBE = r2y_ctrl_c_ref_yb_blend->areaBEnable;

	ybcrv_ctrl.YBCRVAALPOF.bit.YBCRVAALPOF1 = r2y_ctrl_c_ref_yb_blend->areaAOffset;
	imR2yUtils_SET_REG_SIGNED( ybcrv_ctrl.YBCRVAALPGA, union io_r2y_ybcrvaalpga, YBCRVAALPGA_0, r2y_ctrl_c_ref_yb_blend->areaAGain[0] );
	imR2yUtils_SET_REG_SIGNED( ybcrv_ctrl.YBCRVAALPGA, union io_r2y_ybcrvaalpga, YBCRVAALPGA_1, r2y_ctrl_c_ref_yb_blend->areaAGain[1] );
	ybcrv_ctrl.YBCRVAALPBD.bit.YBCRVAALPBD1 = r2y_ctrl_c_ref_yb_blend->areaABoarder;
	ybcrv_ctrl.YBCRVAALPCP.bit.YBCRVAALPCPL = r2y_ctrl_c_ref_yb_blend->areaAScaleClipLo;
	ybcrv_ctrl.YBCRVAALPCP.bit.YBCRVAALPCPH = r2y_ctrl_c_ref_yb_blend->areaAScaleClipHi;
	ybcrv_ctrl.YBYAALPGA.bit.YBYAALPGA0     = r2y_ctrl_c_ref_yb_blend->areaACorrectGainP;
	ybcrv_ctrl.YBYAALPGA.bit.YBYAALPGA1     = r2y_ctrl_c_ref_yb_blend->areaACorrectGainM;
	ybcrv_ctrl.YBYAALPBD.bit.YBYAALPBD_0    = r2y_ctrl_c_ref_yb_blend->areaACorrectBorder[0];
	ybcrv_ctrl.YBYAALPBD.bit.YBYAALPBD_1    = r2y_ctrl_c_ref_yb_blend->areaACorrectBorder[1];
	ybcrv_ctrl.YBYAALPCLP.bit.YBYAALPCLPL   = r2y_ctrl_c_ref_yb_blend->areaACorrectClipLo;
	ybcrv_ctrl.YBYAALPCLP.bit.YBYAALPCLPH   = r2y_ctrl_c_ref_yb_blend->areaACorrectClipHi;

	ybcrv_ctrl.YBCRVBALPOF.bit.YBCRVBALPOF1 = r2y_ctrl_c_ref_yb_blend->areaBOffset;
	imR2yUtils_SET_REG_SIGNED( ybcrv_ctrl.YBCRVBALPGA, union io_r2y_ybcrvbalpga, YBCRVBALPGA_0, r2y_ctrl_c_ref_yb_blend->areaBGain[0] );
	imR2yUtils_SET_REG_SIGNED( ybcrv_ctrl.YBCRVBALPGA, union io_r2y_ybcrvbalpga, YBCRVBALPGA_1, r2y_ctrl_c_ref_yb_blend->areaBGain[1] );
	ybcrv_ctrl.YBCRVBALPBD.bit.YBCRVBALPBD1 = r2y_ctrl_c_ref_yb_blend->areaBBoarder;
	ybcrv_ctrl.YBCRVBALPCP.bit.YBCRVBALPCPL = r2y_ctrl_c_ref_yb_blend->areaBScaleClipLo;
	ybcrv_ctrl.YBCRVBALPCP.bit.YBCRVBALPCPH = r2y_ctrl_c_ref_yb_blend->areaBScaleClipHi;
	ybcrv_ctrl.YBYBALPGA.bit.YBYBALPGA0     = r2y_ctrl_c_ref_yb_blend->areaBCorrectGainP;
	ybcrv_ctrl.YBYBALPGA.bit.YBYBALPGA1     = r2y_ctrl_c_ref_yb_blend->areaBCorrectGainM;
	ybcrv_ctrl.YBYBALPBD.bit.YBYBALPBD_0    = r2y_ctrl_c_ref_yb_blend->areaBCorrectBoarder[0];
	ybcrv_ctrl.YBYBALPBD.bit.YBYBALPBD_1    = r2y_ctrl_c_ref_yb_blend->areaBCorrectBoarder[1];
	ybcrv_ctrl.YBYBALPCLP.bit.YBYBALPCLPL   = r2y_ctrl_c_ref_yb_blend->areaBCorrectClipLo;
	ybcrv_ctrl.YBYBALPCLP.bit.YBYBALPCLPH   = r2y_ctrl_c_ref_yb_blend->areaBCorrectClipHi;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaYbcrvVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&ybcrv_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValColorNrCtrl( kuint16 pipeNo, const R2yCtrlClpf* const r2y_ctrl_clpf )
{
	CtrlRdmaClpfVal clpf_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_CLPF_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	clpf_ctrl.CLPFCTL.bit.CLPFEN = r2y_ctrl_clpf->clpfEnable;
	clpf_ctrl.CLPFCTL.bit.CLPFYA = r2y_ctrl_clpf->interlockBlendEnable;
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_0, r2y_ctrl_clpf->lpfK[0] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_1, r2y_ctrl_clpf->lpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_2, r2y_ctrl_clpf->lpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_3, r2y_ctrl_clpf->lpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_4, r2y_ctrl_clpf->lpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_5, r2y_ctrl_clpf->lpfK[5] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_6, r2y_ctrl_clpf->lpfK[6] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_7, r2y_ctrl_clpf->lpfK[7] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_8, r2y_ctrl_clpf->lpfK[8] );
	clpf_ctrl.CLPFOF.bit.CLPFOF_0 = r2y_ctrl_clpf->lpfIbOffset[0];
	clpf_ctrl.CLPFOF.bit.CLPFOF_1 = r2y_ctrl_clpf->lpfIbOffset[1];
	clpf_ctrl.CLPFOF.bit.CLPFOF_2 = r2y_ctrl_clpf->lpfIbOffset[2];
	clpf_ctrl.CLPFOF.bit.CLPFOF_3 = r2y_ctrl_clpf->lpfIbOffset[3];
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFGA, union io_r2y_clpfga, CLPFGA_0, r2y_ctrl_clpf->lpfIbGain[0] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFGA, union io_r2y_clpfga, CLPFGA_1, r2y_ctrl_clpf->lpfIbGain[1] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFGA, union io_r2y_clpfga, CLPFGA_2, r2y_ctrl_clpf->lpfIbGain[2] );
	imR2yUtils_SET_REG_SIGNED_A( clpf_ctrl.CLPFGA, union io_r2y_clpfga, CLPFGA_3, r2y_ctrl_clpf->lpfIbGain[3] );
	clpf_ctrl.CLPFBD.bit.CLPFBD_1 = r2y_ctrl_clpf->lpfIbBorder[0];
	clpf_ctrl.CLPFBD.bit.CLPFBD_2 = r2y_ctrl_clpf->lpfIbBorder[1];
	clpf_ctrl.CLPFBD.bit.CLPFBD_3 = r2y_ctrl_clpf->lpfIbBorder[2];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaClpfVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&clpf_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValChromaSuppressCtrl( kuint16 pipeNo, const R2yCtrlCs* const r2y_ctrl_cs )
{
	CtrlRdmaCspVal csp_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_CSP_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	csp_ctrl.CSYCTL.bit.CSYEN  = r2y_ctrl_cs->csyEnable;
	csp_ctrl.CSYCTL.bit.CSYKY  = r2y_ctrl_cs->csy_mix_ratio;
	csp_ctrl.CSYCTL.bit.CSYTBL = r2y_ctrl_cs->csy_select_table;
	csp_ctrl.CSYOF.bit.CSYOF_0 = r2y_ctrl_cs->csy_offset[0];
	csp_ctrl.CSYOF.bit.CSYOF_1 = r2y_ctrl_cs->csy_offset[1];
	csp_ctrl.CSYOF.bit.CSYOF_2 = r2y_ctrl_cs->csy_offset[2];
	csp_ctrl.CSYOF.bit.CSYOF_3 = r2y_ctrl_cs->csy_offset[3];
	imR2yUtils_SET_REG_SIGNED_A( csp_ctrl.CSYGA, union io_r2y_csyga, CSYGA_0, r2y_ctrl_cs->csy_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( csp_ctrl.CSYGA, union io_r2y_csyga, CSYGA_1, r2y_ctrl_cs->csy_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( csp_ctrl.CSYGA, union io_r2y_csyga, CSYGA_2, r2y_ctrl_cs->csy_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( csp_ctrl.CSYGA, union io_r2y_csyga, CSYGA_3, r2y_ctrl_cs->csy_gain[3] );
	csp_ctrl.CSYBD.bit.CSYBD_1 = r2y_ctrl_cs->csy_border[0];
	csp_ctrl.CSYBD.bit.CSYBD_2 = r2y_ctrl_cs->csy_border[1];
	csp_ctrl.CSYBD.bit.CSYBD_3 = r2y_ctrl_cs->csy_border[2];
	csp_ctrl.YCRVFX.bit.YRV    = r2y_ctrl_cs->y_rev_enable;
	csp_ctrl.YCRVFX.bit.CRV    = r2y_ctrl_cs->c_rev_enable;
	csp_ctrl.YCRVFX.bit.CFIXEN = r2y_ctrl_cs->c_fixed_enable;
	imR2yUtils_SET_REG_SIGNED( csp_ctrl.CFIX, union io_r2y_cfix, CFIXB, r2y_ctrl_cs->cb_fixed );
	imR2yUtils_SET_REG_SIGNED( csp_ctrl.CFIX, union io_r2y_cfix, CFIXR, r2y_ctrl_cs->cr_fixed );
	imR2yUtils_SET_REG_SIGNED_A( csp_ctrl.YCOF, union io_r2y_ycof, YOF, r2y_ctrl_cs->y_offset );
	imR2yUtils_SET_REG_SIGNED_A( csp_ctrl.YCOF, union io_r2y_ycof, COFB, r2y_ctrl_cs->cb_offset );
	imR2yUtils_SET_REG_SIGNED_A( csp_ctrl.YCOF, union io_r2y_ycof, COFR, r2y_ctrl_cs->cr_offset );

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaCspVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&csp_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValToneCtrlTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_TONE_Tbl_Addr[pipeNo].TC[write_ofs_num / 2]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 2;
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*PUBLIC
*/
/* Copy kuint16 registar value to SDRAM.
 * Registar access is kulong.
 */
INT32 im_r2y_ctrl3_copy_reg_to_sdram_ushort(ImR2yCtrl3 *self, kuint16* const sdram_addr, const volatile kuint16* const reg_addr, const UINT32 array_num )
{
	UINT32 loopcnt;
	union {
		kulong word;
		kuint16 hword[2];
	} conv_wok;
	volatile kulong* reg_addr_ulong;

	reg_addr_ulong = (kulong*)reg_addr;
	for( loopcnt = 0; loopcnt < (array_num / 2); loopcnt++ ) {
		conv_wok.word = reg_addr_ulong[loopcnt];
		sdram_addr[loopcnt * 2] = conv_wok.hword[0];
		sdram_addr[loopcnt * 2 + 1] = conv_wok.hword[1];
	}

	if( (array_num % 2) != 0 ) {
		conv_wok.word = reg_addr_ulong[loopcnt];
		sdram_addr[loopcnt * 2] = conv_wok.hword[0];
	}

	return D_DDIM_OK;
}

/* Map scale control
 */
INT32 im_r2y_ctrl3_map_scl(ImR2yCtrl3 *self, kuint16 pipeNo, const R2yCtrlMapScl* const r2y_ctrl_mapscl )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_mapscl == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_map_scl error. r2y_ctrl_mapscl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_map_scl error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSIZ.bit.EGMPSIZH        = r2y_ctrl_mapscl->blockSizeH;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSIZ.bit.EGMPSIZV        = r2y_ctrl_mapscl->blockSizeV;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSIZHINV.bit.EGMPINVH    = r2y_ctrl_mapscl->recipMultipliH;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSIZHINV.bit.EGMPINVSFTH = r2y_ctrl_mapscl->recipMultipliShiftH;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSIZVINV.bit.EGMPINVV    = r2y_ctrl_mapscl->recipMultipliV;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSIZVINV.bit.EGMPINVSFTV = r2y_ctrl_mapscl->recipMultipliShiftV;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSTAPH.bit.EGMPSTABH     = r2y_ctrl_mapscl->blockStartH;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSTAPH.bit.EGMPSTACH     = r2y_ctrl_mapscl->blockStartCoordH;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSTAPV.bit.EGMPSTABV     = r2y_ctrl_mapscl->blockStartV;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.MAPSCL.EGMPSTAPV.bit.EGMPSTACV     = r2y_ctrl_mapscl->blockStartCoordV;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* Set Map scale table access enable
 */
INT32 im_r2y_ctrl3_set_map_scl_tbl_access_enable(ImR2yCtrl3 *self, kuint16 pipeNo, kuint16 acc_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_set_map_scl_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_map_scl_tbl_accen_ctrl,
									 acc_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_ctrl3_set_map_scl_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Chroma referenced edge and texture adjustment control
 */
INT32 im_r2y_ctrl3_cref_edge_texture_adj_common(ImR2yCtrl3 *self, kuint16 pipeNo, const CtrlCrefEdgeTexture* const r2y_ctrl_c_ref_edge_texture_adj_common )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_c_ref_edge_texture_adj_common == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_cref_edge_texture_adj_common error. r2y_ctrl_c_ref_edge_texture_adj_common = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_cref_edge_texture_adj_common error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCrvCtrl( pipeNo, r2y_ctrl_c_ref_edge_texture_adj_common );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CRV.CRVAF, union io_r2y_crvaf, CRVAFX1, r2y_ctrl_c_ref_edge_texture_adj_common->cbAFocus1Pos );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CRV.CRVAF, union io_r2y_crvaf, CRVAFY1, r2y_ctrl_c_ref_edge_texture_adj_common->crAFocus1Pos );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CRV.CRVAF, union io_r2y_crvaf, CRVAFX2, r2y_ctrl_c_ref_edge_texture_adj_common->cbAFocus2Pos );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CRV.CRVAF, union io_r2y_crvaf, CRVAFY2, r2y_ctrl_c_ref_edge_texture_adj_common->crAFocus2Pos );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CRV.CRVBF, union io_r2y_crvbf, CRVBFX1, r2y_ctrl_c_ref_edge_texture_adj_common->cbBFocus1Pos );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CRV.CRVBF, union io_r2y_crvbf, CRVBFY1, r2y_ctrl_c_ref_edge_texture_adj_common->crBFocus1Pos );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CRV.CRVBF, union io_r2y_crvbf, CRVBFX2, r2y_ctrl_c_ref_edge_texture_adj_common->cbBFocus2Pos );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CRV.CRVBF, union io_r2y_crvbf, CRVBFY2, r2y_ctrl_c_ref_edge_texture_adj_common->crBFocus2Pos );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Chroma referenced edge adjustment control
 */
INT32 im_r2y_ctrl3_cref_edge_adj(ImR2yCtrl3 *self, kuint16 pipeNo, const CtrlCrefEdgeAdj* const r2y_ctrl_c_ref_edge_adj )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_c_ref_edge_adj == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_cref_edge_adj error. r2y_ctrl_c_ref_edge_adj = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_cref_edge_adj error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEgcrvCtrl( pipeNo, r2y_ctrl_c_ref_edge_adj );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVCTL.bit.EGCRAE   = r2y_ctrl_c_ref_edge_adj->areaAEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVCTL.bit.EGCRBE   = r2y_ctrl_c_ref_edge_adj->areaBEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVCTL.bit.EGCRVMRG = r2y_ctrl_c_ref_edge_adj->mergeMethod;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVASCLOF.bit.EGCRVASCLOF1 = r2y_ctrl_c_ref_edge_adj->areaAScaleOffset;
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVASCLGA, union io_r2y_egcrvasclga, EGCRVASCLGA_0, r2y_ctrl_c_ref_edge_adj->areaAScaleGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVASCLGA, union io_r2y_egcrvasclga, EGCRVASCLGA_1, r2y_ctrl_c_ref_edge_adj->areaAScaleGain[1] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVASCLBD.bit.EGCRVASCLBD1 = r2y_ctrl_c_ref_edge_adj->areaAScaleBorder;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVASCLCP.bit.EGCRVASCLCPL = r2y_ctrl_c_ref_edge_adj->areaAScaleClipLo;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVASCLCP.bit.EGCRVASCLCPH = r2y_ctrl_c_ref_edge_adj->areaAScaleClipHi;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYASCLGA.bit.EGYASCLGA0     = r2y_ctrl_c_ref_edge_adj->areaAYScaleGainP;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYASCLGA.bit.EGYASCLGA1     = r2y_ctrl_c_ref_edge_adj->areaAYScaleGainM;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYASCLBD.bit.EGYASCLBD_0    = r2y_ctrl_c_ref_edge_adj->areaAYScaleBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYASCLBD.bit.EGYASCLBD_1    = r2y_ctrl_c_ref_edge_adj->areaAYScaleBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYASCLCLP.bit.EGYASCLCLPL   = r2y_ctrl_c_ref_edge_adj->areaAYScaleClipLo;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYASCLCLP.bit.EGYASCLCLPH   = r2y_ctrl_c_ref_edge_adj->areaAYScaleClipHi;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVBSCLOF.bit.EGCRVBSCLOF1 = r2y_ctrl_c_ref_edge_adj->areaBScaleOffset;
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVBSCLGA, union io_r2y_egcrvbsclga, EGCRVBSCLGA_0, r2y_ctrl_c_ref_edge_adj->areaBScaleGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVBSCLGA, union io_r2y_egcrvbsclga, EGCRVBSCLGA_1, r2y_ctrl_c_ref_edge_adj->areaBScaleGain[1] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVBSCLBD.bit.EGCRVBSCLBD1 = r2y_ctrl_c_ref_edge_adj->areaBScaleBoarder;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVBSCLCP.bit.EGCRVBSCLCPL = r2y_ctrl_c_ref_edge_adj->areaBScaleClipLo;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVBSCLCP.bit.EGCRVBSCLCPH = r2y_ctrl_c_ref_edge_adj->areaBScaleClipHi;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYBSCLGA.bit.EGYBSCLGA0     = r2y_ctrl_c_ref_edge_adj->areaBYScaleGainP;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYBSCLGA.bit.EGYBSCLGA1     = r2y_ctrl_c_ref_edge_adj->areaBYScaleGainM;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYBSCLBD.bit.EGYBSCLBD_0    = r2y_ctrl_c_ref_edge_adj->areaBYScaleBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYBSCLBD.bit.EGYBSCLBD_1    = r2y_ctrl_c_ref_edge_adj->areaBYScaleBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYBSCLCLP.bit.EGYBSCLCLPL   = r2y_ctrl_c_ref_edge_adj->areaBYScaleClipLo;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGYBSCLCLP.bit.EGYBSCLCLPH   = r2y_ctrl_c_ref_edge_adj->areaBYScaleClipHi;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVCLP.bit.EGCRVCLPP = r2y_ctrl_c_ref_edge_adj->levelClipP;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCRV.EGCRVCLP.bit.EGCRVCLPM = r2y_ctrl_c_ref_edge_adj->levelClipM;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Chroma referenced luminance blend control
 */
INT32 im_r2y_ctrl3_cref_yb_blend(ImR2yCtrl3 *self, kuint16 pipeNo, const CtrlCrefYbBlend* const r2y_ctrl_c_ref_yb_blend )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_c_ref_yb_blend == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_cref_yb_blend error. r2y_ctrl_c_ref_yb_blend = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_cref_yb_blend error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValYbcrvCtrl( pipeNo, r2y_ctrl_c_ref_yb_blend );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVCTL.bit.YBCRAE = r2y_ctrl_c_ref_yb_blend->areaAEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVCTL.bit.YBCRBE = r2y_ctrl_c_ref_yb_blend->areaBEnable;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVAALPOF.bit.YBCRVAALPOF1 = r2y_ctrl_c_ref_yb_blend->areaAOffset;
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVAALPGA, union io_r2y_ybcrvaalpga, YBCRVAALPGA_0, r2y_ctrl_c_ref_yb_blend->areaAGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVAALPGA, union io_r2y_ybcrvaalpga, YBCRVAALPGA_1, r2y_ctrl_c_ref_yb_blend->areaAGain[1] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVAALPBD.bit.YBCRVAALPBD1 = r2y_ctrl_c_ref_yb_blend->areaABoarder;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVAALPCP.bit.YBCRVAALPCPL = r2y_ctrl_c_ref_yb_blend->areaAScaleClipLo;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVAALPCP.bit.YBCRVAALPCPH = r2y_ctrl_c_ref_yb_blend->areaAScaleClipHi;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYAALPGA.bit.YBYAALPGA0     = r2y_ctrl_c_ref_yb_blend->areaACorrectGainP;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYAALPGA.bit.YBYAALPGA1     = r2y_ctrl_c_ref_yb_blend->areaACorrectGainM;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYAALPBD.bit.YBYAALPBD_0    = r2y_ctrl_c_ref_yb_blend->areaACorrectBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYAALPBD.bit.YBYAALPBD_1    = r2y_ctrl_c_ref_yb_blend->areaACorrectBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYAALPCLP.bit.YBYAALPCLPL   = r2y_ctrl_c_ref_yb_blend->areaACorrectClipLo;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYAALPCLP.bit.YBYAALPCLPH   = r2y_ctrl_c_ref_yb_blend->areaACorrectClipHi;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVBALPOF.bit.YBCRVBALPOF1 = r2y_ctrl_c_ref_yb_blend->areaBOffset;
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVBALPGA, union io_r2y_ybcrvbalpga, YBCRVBALPGA_0, r2y_ctrl_c_ref_yb_blend->areaBGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVBALPGA, union io_r2y_ybcrvbalpga, YBCRVBALPGA_1, r2y_ctrl_c_ref_yb_blend->areaBGain[1] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVBALPBD.bit.YBCRVBALPBD1 = r2y_ctrl_c_ref_yb_blend->areaBBoarder;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVBALPCP.bit.YBCRVBALPCPL = r2y_ctrl_c_ref_yb_blend->areaBScaleClipLo;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBCRVBALPCP.bit.YBCRVBALPCPH = r2y_ctrl_c_ref_yb_blend->areaBScaleClipHi;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYBALPGA.bit.YBYBALPGA0     = r2y_ctrl_c_ref_yb_blend->areaBCorrectGainP;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYBALPGA.bit.YBYBALPGA1     = r2y_ctrl_c_ref_yb_blend->areaBCorrectGainM;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYBALPBD.bit.YBYBALPBD_0    = r2y_ctrl_c_ref_yb_blend->areaBCorrectBoarder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYBALPBD.bit.YBYBALPBD_1    = r2y_ctrl_c_ref_yb_blend->areaBCorrectBoarder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYBALPCLP.bit.YBYBALPCLPL   = r2y_ctrl_c_ref_yb_blend->areaBCorrectClipLo;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YBCRV.YBYBALPCLP.bit.YBYBALPCLPH   = r2y_ctrl_c_ref_yb_blend->areaBCorrectClipHi;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Color Noise Reduction(LPF) control
 */
INT32 im_r2y_ctrl3_color_nr(ImR2yCtrl3 *self, kuint16 pipeNo, const R2yCtrlClpf* const r2y_ctrl_clpf )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_clpf == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl3_color_nr error. r2y_ctrl_clpf = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_color_nr error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValColorNrCtrl( pipeNo, r2y_ctrl_clpf );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFCTL.bit.CLPFEN = r2y_ctrl_clpf->clpfEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFCTL.bit.CLPFYA = r2y_ctrl_clpf->interlockBlendEnable;
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_0, r2y_ctrl_clpf->lpfK[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_1, r2y_ctrl_clpf->lpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_2, r2y_ctrl_clpf->lpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_3, r2y_ctrl_clpf->lpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_4, r2y_ctrl_clpf->lpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_5, r2y_ctrl_clpf->lpfK[5] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_6, r2y_ctrl_clpf->lpfK[6] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_7, r2y_ctrl_clpf->lpfK[7] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_8, r2y_ctrl_clpf->lpfK[8] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFOF.bit.CLPFOF_0 = r2y_ctrl_clpf->lpfIbOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFOF.bit.CLPFOF_1 = r2y_ctrl_clpf->lpfIbOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFOF.bit.CLPFOF_2 = r2y_ctrl_clpf->lpfIbOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFOF.bit.CLPFOF_3 = r2y_ctrl_clpf->lpfIbOffset[3];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFGA, union io_r2y_clpfga, CLPFGA_0, r2y_ctrl_clpf->lpfIbGain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFGA, union io_r2y_clpfga, CLPFGA_1, r2y_ctrl_clpf->lpfIbGain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFGA, union io_r2y_clpfga, CLPFGA_2, r2y_ctrl_clpf->lpfIbGain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFGA, union io_r2y_clpfga, CLPFGA_3, r2y_ctrl_clpf->lpfIbGain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFBD.bit.CLPFBD_1 = r2y_ctrl_clpf->lpfIbBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFBD.bit.CLPFBD_2 = r2y_ctrl_clpf->lpfIbBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CLPF.CLPFBD.bit.CLPFBD_3 = r2y_ctrl_clpf->lpfIbBorder[2];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Chroma suppress control
 */
INT32 im_r2y_ctrl3_chroma_suppress(ImR2yCtrl3 *self, kuint16 pipeNo, const R2yCtrlCs* const r2y_ctrl_cs )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_cs == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_chroma_suppress error. r2y_ctrl_cs = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_chroma_suppress error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValChromaSuppressCtrl( pipeNo, r2y_ctrl_cs );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYCTL.bit.CSYEN  = r2y_ctrl_cs->csyEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYCTL.bit.CSYKY  = r2y_ctrl_cs->csy_mix_ratio;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYCTL.bit.CSYTBL = r2y_ctrl_cs->csy_select_table;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYOF.bit.CSYOF_0 = r2y_ctrl_cs->csy_offset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYOF.bit.CSYOF_1 = r2y_ctrl_cs->csy_offset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYOF.bit.CSYOF_2 = r2y_ctrl_cs->csy_offset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYOF.bit.CSYOF_3 = r2y_ctrl_cs->csy_offset[3];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYGA, union io_r2y_csyga, CSYGA_0, r2y_ctrl_cs->csy_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYGA, union io_r2y_csyga, CSYGA_1, r2y_ctrl_cs->csy_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYGA, union io_r2y_csyga, CSYGA_2, r2y_ctrl_cs->csy_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYGA, union io_r2y_csyga, CSYGA_3, r2y_ctrl_cs->csy_gain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYBD.bit.CSYBD_1 = r2y_ctrl_cs->csy_border[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYBD.bit.CSYBD_2 = r2y_ctrl_cs->csy_border[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CSYBD.bit.CSYBD_3 = r2y_ctrl_cs->csy_border[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.YCRVFX.bit.YRV    = r2y_ctrl_cs->y_rev_enable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.YCRVFX.bit.CRV    = r2y_ctrl_cs->c_rev_enable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.YCRVFX.bit.CFIXEN = r2y_ctrl_cs->c_fixed_enable;
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CFIX, union io_r2y_cfix, CFIXB, r2y_ctrl_cs->cb_fixed );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.CFIX, union io_r2y_cfix, CFIXR, r2y_ctrl_cs->cr_fixed );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.YCOF, union io_r2y_ycof, YOF, r2y_ctrl_cs->y_offset );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.YCOF, union io_r2y_ycof, COFB, r2y_ctrl_cs->cb_offset );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CSP.YCOF, union io_r2y_ycof, COFR, r2y_ctrl_cs->cr_offset );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Tone control table
 */
INT32 im_r2y_ctrl3_set_tone_control_table(ImR2yCtrl3 *self, kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifndef CO_R2Y_RDMA_ON
	UINT32 loop_cnt;
#endif	// CO_R2Y_RDMA_ON
	INT32  ercd;

#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_set_tone_control_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( write_ofs_num >= ImR2yCtrl_TABLE_MAX_TONE ) {
		Ddim_Assertion(("im_r2y_ctrl3_set_tone_control_table error. write_ofs_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_TONE ) {
		Ddim_Assertion(("im_r2y_ctrl3_set_tone_control_table error. write_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_set_tone_control_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	while( 1 ) {
		ercd = im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValToneCtrlTable( pipeNo, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			gImIoR2yTblPtr[pipeNo]->TC.hword[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Get Tone control Table
 */
INT32 im_r2y_ctrl3_get_tone_control_table(ImR2yCtrl3 *self, kuint16 pipeNo, kuint16* const dst_tbl, kuint16 read_ofs_num, kuint16 array_num )
{
	INT32  ercd;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(dst_tbl == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_get_tone_control_table error. dst_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( read_ofs_num >= ImR2yCtrl_TABLE_MAX_TONE ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_tone_control_table error. read_ofs_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (read_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_TONE ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_tone_control_table error. read_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_get_tone_control_table error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

	while( 1 ) {
		ercd = im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_tbl,	// Read access only support Word-width. (Hardware specification.)
										 &gImIoR2yTblPtr[pipeNo]->TC.hword[im_r2y_rounddown_2(read_ofs_num)],
										 array_num );

		ercd = im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );

	return ercd;
}

/* Get Luminance evaluation
 */
INT32 im_r2y_ctrl3_get_luminance_evaluation_before_tone(ImR2yCtrl3 *self, kuint16 pipeNo, UINT32* const dst_addr, kuint16 array_num )
{
	UINT32 loop_cnt;
	INT32 ercd;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(dst_addr == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_get_luminance_evaluation_before_tone error. dst_addr = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_get_luminance_evaluation_before_tone error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	if( gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YFLAG.bit.TCTACT != 0 ){
		return ImR2yUtils_MACRO_BUSY;
	}

	im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

	while( 1 ) {
		ercd = im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(im_r2y_ctrl2_new(), pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			dst_addr[loop_cnt] = gImIoR2yTblPtr[pipeNo]->TCTDATA.word[loop_cnt];
		}

		ercd = im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(im_r2y_ctrl2_new(), pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return ercd;
}

/* Get BTC Histogram value
 */
INT32 im_r2y_ctrl3_get_histogram_before_tone(ImR2yCtrl3 *self, kuint16 pipeNo, R2yBtcHistRgbtbl data_type, R2yTchsFlg* const overflow_flg, kuint16* const dst_addr )
{
	INT32 ercd;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( dst_addr == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_histogram_before_tone error. dst_addr = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( overflow_flg == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_histogram_before_tone error. overflow_flg = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( data_type >= ImR2y_BTC_HIST_RGBTBL_MAX ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_histogram_before_tone error. data_type >= MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_get_histogram_before_tone error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	if( gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YFLAG.bit.TCHACT != 0 ){
		return ImR2yUtils_MACRO_BUSY;
	}

	im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

	while( 1 ) {
		overflow_flg->Y = gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHOV.bit.TCHYOV;
		overflow_flg->R = gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHOV.bit.TCHROV;
		overflow_flg->G = gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHOV.bit.TCHGOV;
		overflow_flg->B = gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHOV.bit.TCHBOV;

		ercd = im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(im_r2y_ctrl2_new(), pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		switch( data_type ){
			case ImR2y_BTC_HIST_RGBTBL_R:
				im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr,	// Read access only support Word-width. (Hardware specification.)
												 gImIoR2yTblPtr[pipeNo]->TCHSRDATA.hword,
												 ImR2yCtrl_TABLE_MAX_BTC_HISTOGRAM_RGB );
				break;
			case ImR2y_BTC_HIST_RGBTBL_G:
				im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr,	// Read access only support Word-width. (Hardware specification.)
												 gImIoR2yTblPtr[pipeNo]->TCHSGDATA.hword,
												 ImR2yCtrl_TABLE_MAX_BTC_HISTOGRAM_RGB );
				break;
			case ImR2y_BTC_HIST_RGBTBL_B:
				im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr,	// Read access only support Word-width. (Hardware specification.)
												 gImIoR2yTblPtr[pipeNo]->TCHSBDATA.hword,
												 ImR2yCtrl_TABLE_MAX_BTC_HISTOGRAM_RGB );
				break;
//			case ImR2y_BTC_HIST_RGBTBL_Y:
			default:
				im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr,	// Read access only support Word-width. (Hardware specification.)
												 gImIoR2yTblPtr[pipeNo]->TCHSYDATA.hword,
												 ImR2yCtrl_TABLE_MAX_BTC_HISTOGRAM_Y );
				break;
		}

		ercd = im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(im_r2y_ctrl2_new(), pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return ercd;
}

ImR2yCtrl3 *im_r2y_ctrl3_new(void)
{
	ImR2yCtrl3* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL3,sizeof(ImR2yCtrl3Private));
	return self;
}
