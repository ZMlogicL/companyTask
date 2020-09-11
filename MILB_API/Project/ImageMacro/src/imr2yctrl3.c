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
static VOID imR2ySetMapSclTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_map_scl_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetMapSclTblAccessEnable,
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static VOID imR2ySetRdmaValCrvCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_EDGE_TEXTURE_ADJ_COMMON* const r2y_ctrl_c_ref_edge_texture_adj_common );
static VOID imR2ySetRdmaValEgcrvCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_EDGE_ADJ* const r2y_ctrl_c_ref_edge_adj );
static VOID imR2ySetRdmaValYbcrvCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_YB_BLEND* const r2y_ctrl_c_ref_yb_blend );
static VOID imR2ySetRdmaValColorNrCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_CLPF* const r2y_ctrl_clpf );
static VOID imR2ySetRdmaValChromaSuppressCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_CS* const r2y_ctrl_cs );
static VOID imR2ySetRdmaValToneCtrlTable( UCHAR pipe_no, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num );
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

static VOID imR2ySetMapSclTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPCTL.bit.EMPAEN = enable;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static VOID imR2ySetRdmaValCrvCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_EDGE_TEXTURE_ADJ_COMMON* const r2y_ctrl_c_ref_edge_texture_adj_common )
{
	T_IM_R2Y_CTRL_RDMA_CRV_VAL crv_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_CRV_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	im_r2y_set_reg_signed( crv_ctrl.CRVAF, union io_r2y_crvaf, CRVAFX1, r2y_ctrl_c_ref_edge_texture_adj_common->cb_a_focus1_pos );
	im_r2y_set_reg_signed( crv_ctrl.CRVAF, union io_r2y_crvaf, CRVAFY1, r2y_ctrl_c_ref_edge_texture_adj_common->cr_a_focus1_pos );
	im_r2y_set_reg_signed( crv_ctrl.CRVAF, union io_r2y_crvaf, CRVAFX2, r2y_ctrl_c_ref_edge_texture_adj_common->cb_a_focus2_pos );
	im_r2y_set_reg_signed( crv_ctrl.CRVAF, union io_r2y_crvaf, CRVAFY2, r2y_ctrl_c_ref_edge_texture_adj_common->cr_a_focus2_pos );
	im_r2y_set_reg_signed( crv_ctrl.CRVBF, union io_r2y_crvbf, CRVBFX1, r2y_ctrl_c_ref_edge_texture_adj_common->cb_b_focus1_pos );
	im_r2y_set_reg_signed( crv_ctrl.CRVBF, union io_r2y_crvbf, CRVBFY1, r2y_ctrl_c_ref_edge_texture_adj_common->cr_b_focus1_pos );
	im_r2y_set_reg_signed( crv_ctrl.CRVBF, union io_r2y_crvbf, CRVBFX2, r2y_ctrl_c_ref_edge_texture_adj_common->cb_b_focus2_pos );
	im_r2y_set_reg_signed( crv_ctrl.CRVBF, union io_r2y_crvbf, CRVBFY2, r2y_ctrl_c_ref_edge_texture_adj_common->cr_b_focus2_pos );

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_CRV_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&crv_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValEgcrvCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_EDGE_ADJ* const r2y_ctrl_c_ref_edge_adj )
{
	T_IM_R2Y_CTRL_RDMA_EGCRV_VAL egcrv_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_EGCRV_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	egcrv_ctrl.EGCRVCTL.bit.EGCRAE   = r2y_ctrl_c_ref_edge_adj->area_a_enable;
	egcrv_ctrl.EGCRVCTL.bit.EGCRBE   = r2y_ctrl_c_ref_edge_adj->area_b_enable;
	egcrv_ctrl.EGCRVCTL.bit.EGCRVMRG = r2y_ctrl_c_ref_edge_adj->merge_method;

	egcrv_ctrl.EGCRVASCLOF.bit.EGCRVASCLOF1 = r2y_ctrl_c_ref_edge_adj->area_a_scale_offset;
	im_r2y_set_reg_signed( egcrv_ctrl.EGCRVASCLGA, union io_r2y_egcrvasclga, EGCRVASCLGA_0, r2y_ctrl_c_ref_edge_adj->area_a_scale_gain[0] );
	im_r2y_set_reg_signed( egcrv_ctrl.EGCRVASCLGA, union io_r2y_egcrvasclga, EGCRVASCLGA_1, r2y_ctrl_c_ref_edge_adj->area_a_scale_gain[1] );
	egcrv_ctrl.EGCRVASCLBD.bit.EGCRVASCLBD1 = r2y_ctrl_c_ref_edge_adj->area_a_scale_border;
	egcrv_ctrl.EGCRVASCLCP.bit.EGCRVASCLCPL = r2y_ctrl_c_ref_edge_adj->area_a_scale_clip_lo;
	egcrv_ctrl.EGCRVASCLCP.bit.EGCRVASCLCPH = r2y_ctrl_c_ref_edge_adj->area_a_scale_clip_hi;
	egcrv_ctrl.EGYASCLGA.bit.EGYASCLGA0     = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_gain_p;
	egcrv_ctrl.EGYASCLGA.bit.EGYASCLGA1     = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_gain_m;
	egcrv_ctrl.EGYASCLBD.bit.EGYASCLBD_0    = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_border[0];
	egcrv_ctrl.EGYASCLBD.bit.EGYASCLBD_1    = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_border[1];
	egcrv_ctrl.EGYASCLCLP.bit.EGYASCLCLPL   = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_clip_lo;
	egcrv_ctrl.EGYASCLCLP.bit.EGYASCLCLPH   = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_clip_hi;

	egcrv_ctrl.EGCRVBSCLOF.bit.EGCRVBSCLOF1 = r2y_ctrl_c_ref_edge_adj->area_b_scale_offset;
	im_r2y_set_reg_signed( egcrv_ctrl.EGCRVBSCLGA, union io_r2y_egcrvbsclga, EGCRVBSCLGA_0, r2y_ctrl_c_ref_edge_adj->area_b_scale_gain[0] );
	im_r2y_set_reg_signed( egcrv_ctrl.EGCRVBSCLGA, union io_r2y_egcrvbsclga, EGCRVBSCLGA_1, r2y_ctrl_c_ref_edge_adj->area_b_scale_gain[1] );
	egcrv_ctrl.EGCRVBSCLBD.bit.EGCRVBSCLBD1 = r2y_ctrl_c_ref_edge_adj->area_b_scale_border;
	egcrv_ctrl.EGCRVBSCLCP.bit.EGCRVBSCLCPL = r2y_ctrl_c_ref_edge_adj->area_b_scale_clip_lo;
	egcrv_ctrl.EGCRVBSCLCP.bit.EGCRVBSCLCPH = r2y_ctrl_c_ref_edge_adj->area_b_scale_clip_hi;
	egcrv_ctrl.EGYBSCLGA.bit.EGYBSCLGA0     = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_gain_p;
	egcrv_ctrl.EGYBSCLGA.bit.EGYBSCLGA1     = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_gain_m;
	egcrv_ctrl.EGYBSCLBD.bit.EGYBSCLBD_0    = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_border[0];
	egcrv_ctrl.EGYBSCLBD.bit.EGYBSCLBD_1    = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_border[1];
	egcrv_ctrl.EGYBSCLCLP.bit.EGYBSCLCLPL   = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_clip_lo;
	egcrv_ctrl.EGYBSCLCLP.bit.EGYBSCLCLPH   = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_clip_hi;

	egcrv_ctrl.EGCRVCLP.bit.EGCRVCLPP = r2y_ctrl_c_ref_edge_adj->level_clip_p;
	egcrv_ctrl.EGCRVCLP.bit.EGCRVCLPM = r2y_ctrl_c_ref_edge_adj->level_clip_m;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_EGCRV_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&egcrv_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValYbcrvCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_YB_BLEND* const r2y_ctrl_c_ref_yb_blend )
{
	T_IM_R2Y_CTRL_RDMA_YBCRV_VAL ybcrv_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_YBCRV_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	ybcrv_ctrl.YBCRVCTL.bit.YBCRAE = r2y_ctrl_c_ref_yb_blend->area_a_enable;
	ybcrv_ctrl.YBCRVCTL.bit.YBCRBE = r2y_ctrl_c_ref_yb_blend->area_b_enable;

	ybcrv_ctrl.YBCRVAALPOF.bit.YBCRVAALPOF1 = r2y_ctrl_c_ref_yb_blend->area_a_offset;
	im_r2y_set_reg_signed( ybcrv_ctrl.YBCRVAALPGA, union io_r2y_ybcrvaalpga, YBCRVAALPGA_0, r2y_ctrl_c_ref_yb_blend->area_a_gain[0] );
	im_r2y_set_reg_signed( ybcrv_ctrl.YBCRVAALPGA, union io_r2y_ybcrvaalpga, YBCRVAALPGA_1, r2y_ctrl_c_ref_yb_blend->area_a_gain[1] );
	ybcrv_ctrl.YBCRVAALPBD.bit.YBCRVAALPBD1 = r2y_ctrl_c_ref_yb_blend->area_a_border;
	ybcrv_ctrl.YBCRVAALPCP.bit.YBCRVAALPCPL = r2y_ctrl_c_ref_yb_blend->area_a_scale_clip_lo;
	ybcrv_ctrl.YBCRVAALPCP.bit.YBCRVAALPCPH = r2y_ctrl_c_ref_yb_blend->area_a_scale_clip_hi;
	ybcrv_ctrl.YBYAALPGA.bit.YBYAALPGA0     = r2y_ctrl_c_ref_yb_blend->area_a_correct_gain_p;
	ybcrv_ctrl.YBYAALPGA.bit.YBYAALPGA1     = r2y_ctrl_c_ref_yb_blend->area_a_correct_gain_m;
	ybcrv_ctrl.YBYAALPBD.bit.YBYAALPBD_0    = r2y_ctrl_c_ref_yb_blend->area_a_correct_border[0];
	ybcrv_ctrl.YBYAALPBD.bit.YBYAALPBD_1    = r2y_ctrl_c_ref_yb_blend->area_a_correct_border[1];
	ybcrv_ctrl.YBYAALPCLP.bit.YBYAALPCLPL   = r2y_ctrl_c_ref_yb_blend->area_a_correct_clip_lo;
	ybcrv_ctrl.YBYAALPCLP.bit.YBYAALPCLPH   = r2y_ctrl_c_ref_yb_blend->area_a_correct_clip_hi;

	ybcrv_ctrl.YBCRVBALPOF.bit.YBCRVBALPOF1 = r2y_ctrl_c_ref_yb_blend->area_b_offset;
	im_r2y_set_reg_signed( ybcrv_ctrl.YBCRVBALPGA, union io_r2y_ybcrvbalpga, YBCRVBALPGA_0, r2y_ctrl_c_ref_yb_blend->area_b_gain[0] );
	im_r2y_set_reg_signed( ybcrv_ctrl.YBCRVBALPGA, union io_r2y_ybcrvbalpga, YBCRVBALPGA_1, r2y_ctrl_c_ref_yb_blend->area_b_gain[1] );
	ybcrv_ctrl.YBCRVBALPBD.bit.YBCRVBALPBD1 = r2y_ctrl_c_ref_yb_blend->area_b_border;
	ybcrv_ctrl.YBCRVBALPCP.bit.YBCRVBALPCPL = r2y_ctrl_c_ref_yb_blend->area_b_scale_clip_lo;
	ybcrv_ctrl.YBCRVBALPCP.bit.YBCRVBALPCPH = r2y_ctrl_c_ref_yb_blend->area_b_scale_clip_hi;
	ybcrv_ctrl.YBYBALPGA.bit.YBYBALPGA0     = r2y_ctrl_c_ref_yb_blend->area_b_correct_gain_p;
	ybcrv_ctrl.YBYBALPGA.bit.YBYBALPGA1     = r2y_ctrl_c_ref_yb_blend->area_b_correct_gain_m;
	ybcrv_ctrl.YBYBALPBD.bit.YBYBALPBD_0    = r2y_ctrl_c_ref_yb_blend->area_b_correct_border[0];
	ybcrv_ctrl.YBYBALPBD.bit.YBYBALPBD_1    = r2y_ctrl_c_ref_yb_blend->area_b_correct_border[1];
	ybcrv_ctrl.YBYBALPCLP.bit.YBYBALPCLPL   = r2y_ctrl_c_ref_yb_blend->area_b_correct_clip_lo;
	ybcrv_ctrl.YBYBALPCLP.bit.YBYBALPCLPH   = r2y_ctrl_c_ref_yb_blend->area_b_correct_clip_hi;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_YBCRV_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&ybcrv_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValColorNrCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_CLPF* const r2y_ctrl_clpf )
{
	T_IM_R2Y_CTRL_RDMA_CLPF_VAL clpf_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_CLPF_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	clpf_ctrl.CLPFCTL.bit.CLPFEN = r2y_ctrl_clpf->clpf_enable;
	clpf_ctrl.CLPFCTL.bit.CLPFYA = r2y_ctrl_clpf->interlock_blend_enable;
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_0, r2y_ctrl_clpf->lpf_k[0] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_1, r2y_ctrl_clpf->lpf_k[1] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_2, r2y_ctrl_clpf->lpf_k[2] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_3, r2y_ctrl_clpf->lpf_k[3] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_4, r2y_ctrl_clpf->lpf_k[4] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_5, r2y_ctrl_clpf->lpf_k[5] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_6, r2y_ctrl_clpf->lpf_k[6] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_7, r2y_ctrl_clpf->lpf_k[7] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFK, union io_r2y_clpfk, CLPFK_8, r2y_ctrl_clpf->lpf_k[8] );
	clpf_ctrl.CLPFOF.bit.CLPFOF_0 = r2y_ctrl_clpf->lpf_ib_offset[0];
	clpf_ctrl.CLPFOF.bit.CLPFOF_1 = r2y_ctrl_clpf->lpf_ib_offset[1];
	clpf_ctrl.CLPFOF.bit.CLPFOF_2 = r2y_ctrl_clpf->lpf_ib_offset[2];
	clpf_ctrl.CLPFOF.bit.CLPFOF_3 = r2y_ctrl_clpf->lpf_ib_offset[3];
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFGA, union io_r2y_clpfga, CLPFGA_0, r2y_ctrl_clpf->lpf_ib_gain[0] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFGA, union io_r2y_clpfga, CLPFGA_1, r2y_ctrl_clpf->lpf_ib_gain[1] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFGA, union io_r2y_clpfga, CLPFGA_2, r2y_ctrl_clpf->lpf_ib_gain[2] );
	im_r2y_set_reg_signed_a( clpf_ctrl.CLPFGA, union io_r2y_clpfga, CLPFGA_3, r2y_ctrl_clpf->lpf_ib_gain[3] );
	clpf_ctrl.CLPFBD.bit.CLPFBD_1 = r2y_ctrl_clpf->lpf_ib_border[0];
	clpf_ctrl.CLPFBD.bit.CLPFBD_2 = r2y_ctrl_clpf->lpf_ib_border[1];
	clpf_ctrl.CLPFBD.bit.CLPFBD_3 = r2y_ctrl_clpf->lpf_ib_border[2];

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_CLPF_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&clpf_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValChromaSuppressCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_CS* const r2y_ctrl_cs )
{
	T_IM_R2Y_CTRL_RDMA_CSP_VAL csp_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_CSP_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	csp_ctrl.CSYCTL.bit.CSYEN  = r2y_ctrl_cs->csy_enable;
	csp_ctrl.CSYCTL.bit.CSYKY  = r2y_ctrl_cs->csy_mix_ratio;
	csp_ctrl.CSYCTL.bit.CSYTBL = r2y_ctrl_cs->csy_select_table;
	csp_ctrl.CSYOF.bit.CSYOF_0 = r2y_ctrl_cs->csy_offset[0];
	csp_ctrl.CSYOF.bit.CSYOF_1 = r2y_ctrl_cs->csy_offset[1];
	csp_ctrl.CSYOF.bit.CSYOF_2 = r2y_ctrl_cs->csy_offset[2];
	csp_ctrl.CSYOF.bit.CSYOF_3 = r2y_ctrl_cs->csy_offset[3];
	im_r2y_set_reg_signed_a( csp_ctrl.CSYGA, union io_r2y_csyga, CSYGA_0, r2y_ctrl_cs->csy_gain[0] );
	im_r2y_set_reg_signed_a( csp_ctrl.CSYGA, union io_r2y_csyga, CSYGA_1, r2y_ctrl_cs->csy_gain[1] );
	im_r2y_set_reg_signed_a( csp_ctrl.CSYGA, union io_r2y_csyga, CSYGA_2, r2y_ctrl_cs->csy_gain[2] );
	im_r2y_set_reg_signed_a( csp_ctrl.CSYGA, union io_r2y_csyga, CSYGA_3, r2y_ctrl_cs->csy_gain[3] );
	csp_ctrl.CSYBD.bit.CSYBD_1 = r2y_ctrl_cs->csy_border[0];
	csp_ctrl.CSYBD.bit.CSYBD_2 = r2y_ctrl_cs->csy_border[1];
	csp_ctrl.CSYBD.bit.CSYBD_3 = r2y_ctrl_cs->csy_border[2];
	csp_ctrl.YCRVFX.bit.YRV    = r2y_ctrl_cs->y_rev_enable;
	csp_ctrl.YCRVFX.bit.CRV    = r2y_ctrl_cs->c_rev_enable;
	csp_ctrl.YCRVFX.bit.CFIXEN = r2y_ctrl_cs->c_fixed_enable;
	im_r2y_set_reg_signed( csp_ctrl.CFIX, union io_r2y_cfix, CFIXB, r2y_ctrl_cs->cb_fixed );
	im_r2y_set_reg_signed( csp_ctrl.CFIX, union io_r2y_cfix, CFIXR, r2y_ctrl_cs->cr_fixed );
	im_r2y_set_reg_signed_a( csp_ctrl.YCOF, union io_r2y_ycof, YOF, r2y_ctrl_cs->y_offset );
	im_r2y_set_reg_signed_a( csp_ctrl.YCOF, union io_r2y_ycof, COFB, r2y_ctrl_cs->cb_offset );
	im_r2y_set_reg_signed_a( csp_ctrl.YCOF, union io_r2y_ycof, COFR, r2y_ctrl_cs->cr_offset );

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_CSP_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&csp_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValToneCtrlTable( UCHAR pipe_no, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_TONE_Tbl_Addr[pipe_no].TC[write_ofs_num / 2]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 2;
	rdma_ctrl.reg_data_top_addr = (ULONG)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*PUBLIC
*/
/* Copy USHORT registar value to SDRAM.
 * Registar access is ULONG.
 */
INT32 im_r2y_ctrl3_copy_reg_to_sdram_ushort(ImR2yCtrl3 *self, USHORT* const sdram_addr, const volatile USHORT* const reg_addr, const UINT32 array_num )
{
	UINT32 loopcnt;
	union {
		ULONG word;
		USHORT hword[2];
	} conv_wok;
	volatile ULONG* reg_addr_ulong;

	reg_addr_ulong = (ULONG*)reg_addr;
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
INT32 im_r2y_ctrl3_map_scl(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_MAPSCL* const r2y_ctrl_mapscl )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_mapscl == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_map_scl error. r2y_ctrl_mapscl = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_map_scl error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSIZ.bit.EGMPSIZH        = r2y_ctrl_mapscl->block_size_h;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSIZ.bit.EGMPSIZV        = r2y_ctrl_mapscl->block_size_v;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSIZHINV.bit.EGMPINVH    = r2y_ctrl_mapscl->recip_multipli_h;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSIZHINV.bit.EGMPINVSFTH = r2y_ctrl_mapscl->recip_multipli_shift_h;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSIZVINV.bit.EGMPINVV    = r2y_ctrl_mapscl->recip_multipli_v;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSIZVINV.bit.EGMPINVSFTV = r2y_ctrl_mapscl->recip_multipli_shift_v;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSTAPH.bit.EGMPSTABH     = r2y_ctrl_mapscl->block_start_h;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSTAPH.bit.EGMPSTACH     = r2y_ctrl_mapscl->block_start_coord_h;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSTAPV.bit.EGMPSTABV     = r2y_ctrl_mapscl->block_start_v;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MAPSCL.EGMPSTAPV.bit.EGMPSTACV     = r2y_ctrl_mapscl->block_start_coord_v;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* Set Map scale table access enable
 */
INT32 im_r2y_ctrl3_set_map_scl_tbl_access_enable(ImR2yCtrl3 *self, UCHAR pipe_no, UCHAR acc_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_set_map_scl_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_map_scl_tbl_accen_ctrl,
									 acc_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_ctrl3_set_map_scl_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Chroma referenced edge and texture adjustment control
 */
INT32 im_r2y_ctrl3_cref_edge_texture_adj_common(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_EDGE_TEXTURE_ADJ_COMMON* const r2y_ctrl_c_ref_edge_texture_adj_common )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_c_ref_edge_texture_adj_common == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_cref_edge_texture_adj_common error. r2y_ctrl_c_ref_edge_texture_adj_common = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_cref_edge_texture_adj_common error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCrvCtrl( pipe_no, r2y_ctrl_c_ref_edge_texture_adj_common );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CRV.CRVAF, union io_r2y_crvaf, CRVAFX1, r2y_ctrl_c_ref_edge_texture_adj_common->cb_a_focus1_pos );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CRV.CRVAF, union io_r2y_crvaf, CRVAFY1, r2y_ctrl_c_ref_edge_texture_adj_common->cr_a_focus1_pos );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CRV.CRVAF, union io_r2y_crvaf, CRVAFX2, r2y_ctrl_c_ref_edge_texture_adj_common->cb_a_focus2_pos );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CRV.CRVAF, union io_r2y_crvaf, CRVAFY2, r2y_ctrl_c_ref_edge_texture_adj_common->cr_a_focus2_pos );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CRV.CRVBF, union io_r2y_crvbf, CRVBFX1, r2y_ctrl_c_ref_edge_texture_adj_common->cb_b_focus1_pos );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CRV.CRVBF, union io_r2y_crvbf, CRVBFY1, r2y_ctrl_c_ref_edge_texture_adj_common->cr_b_focus1_pos );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CRV.CRVBF, union io_r2y_crvbf, CRVBFX2, r2y_ctrl_c_ref_edge_texture_adj_common->cb_b_focus2_pos );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CRV.CRVBF, union io_r2y_crvbf, CRVBFY2, r2y_ctrl_c_ref_edge_texture_adj_common->cr_b_focus2_pos );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Chroma referenced edge adjustment control
 */
INT32 im_r2y_ctrl3_cref_edge_adj(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_EDGE_ADJ* const r2y_ctrl_c_ref_edge_adj )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_c_ref_edge_adj == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_cref_edge_adj error. r2y_ctrl_c_ref_edge_adj = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_cref_edge_adj error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEgcrvCtrl( pipe_no, r2y_ctrl_c_ref_edge_adj );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVCTL.bit.EGCRAE   = r2y_ctrl_c_ref_edge_adj->area_a_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVCTL.bit.EGCRBE   = r2y_ctrl_c_ref_edge_adj->area_b_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVCTL.bit.EGCRVMRG = r2y_ctrl_c_ref_edge_adj->merge_method;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVASCLOF.bit.EGCRVASCLOF1 = r2y_ctrl_c_ref_edge_adj->area_a_scale_offset;
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVASCLGA, union io_r2y_egcrvasclga, EGCRVASCLGA_0, r2y_ctrl_c_ref_edge_adj->area_a_scale_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVASCLGA, union io_r2y_egcrvasclga, EGCRVASCLGA_1, r2y_ctrl_c_ref_edge_adj->area_a_scale_gain[1] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVASCLBD.bit.EGCRVASCLBD1 = r2y_ctrl_c_ref_edge_adj->area_a_scale_border;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVASCLCP.bit.EGCRVASCLCPL = r2y_ctrl_c_ref_edge_adj->area_a_scale_clip_lo;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVASCLCP.bit.EGCRVASCLCPH = r2y_ctrl_c_ref_edge_adj->area_a_scale_clip_hi;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYASCLGA.bit.EGYASCLGA0     = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_gain_p;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYASCLGA.bit.EGYASCLGA1     = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_gain_m;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYASCLBD.bit.EGYASCLBD_0    = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYASCLBD.bit.EGYASCLBD_1    = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYASCLCLP.bit.EGYASCLCLPL   = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_clip_lo;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYASCLCLP.bit.EGYASCLCLPH   = r2y_ctrl_c_ref_edge_adj->area_a_y_scale_clip_hi;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVBSCLOF.bit.EGCRVBSCLOF1 = r2y_ctrl_c_ref_edge_adj->area_b_scale_offset;
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVBSCLGA, union io_r2y_egcrvbsclga, EGCRVBSCLGA_0, r2y_ctrl_c_ref_edge_adj->area_b_scale_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVBSCLGA, union io_r2y_egcrvbsclga, EGCRVBSCLGA_1, r2y_ctrl_c_ref_edge_adj->area_b_scale_gain[1] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVBSCLBD.bit.EGCRVBSCLBD1 = r2y_ctrl_c_ref_edge_adj->area_b_scale_border;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVBSCLCP.bit.EGCRVBSCLCPL = r2y_ctrl_c_ref_edge_adj->area_b_scale_clip_lo;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVBSCLCP.bit.EGCRVBSCLCPH = r2y_ctrl_c_ref_edge_adj->area_b_scale_clip_hi;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYBSCLGA.bit.EGYBSCLGA0     = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_gain_p;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYBSCLGA.bit.EGYBSCLGA1     = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_gain_m;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYBSCLBD.bit.EGYBSCLBD_0    = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYBSCLBD.bit.EGYBSCLBD_1    = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYBSCLCLP.bit.EGYBSCLCLPL   = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_clip_lo;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGYBSCLCLP.bit.EGYBSCLCLPH   = r2y_ctrl_c_ref_edge_adj->area_b_y_scale_clip_hi;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVCLP.bit.EGCRVCLPP = r2y_ctrl_c_ref_edge_adj->level_clip_p;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCRV.EGCRVCLP.bit.EGCRVCLPM = r2y_ctrl_c_ref_edge_adj->level_clip_m;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Chroma referenced luminance blend control
 */
INT32 im_r2y_ctrl3_cref_yb_blend(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_YB_BLEND* const r2y_ctrl_c_ref_yb_blend )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_c_ref_yb_blend == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_cref_yb_blend error. r2y_ctrl_c_ref_yb_blend = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_cref_yb_blend error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValYbcrvCtrl( pipe_no, r2y_ctrl_c_ref_yb_blend );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVCTL.bit.YBCRAE = r2y_ctrl_c_ref_yb_blend->area_a_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVCTL.bit.YBCRBE = r2y_ctrl_c_ref_yb_blend->area_b_enable;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVAALPOF.bit.YBCRVAALPOF1 = r2y_ctrl_c_ref_yb_blend->area_a_offset;
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVAALPGA, union io_r2y_ybcrvaalpga, YBCRVAALPGA_0, r2y_ctrl_c_ref_yb_blend->area_a_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVAALPGA, union io_r2y_ybcrvaalpga, YBCRVAALPGA_1, r2y_ctrl_c_ref_yb_blend->area_a_gain[1] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVAALPBD.bit.YBCRVAALPBD1 = r2y_ctrl_c_ref_yb_blend->area_a_border;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVAALPCP.bit.YBCRVAALPCPL = r2y_ctrl_c_ref_yb_blend->area_a_scale_clip_lo;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVAALPCP.bit.YBCRVAALPCPH = r2y_ctrl_c_ref_yb_blend->area_a_scale_clip_hi;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYAALPGA.bit.YBYAALPGA0     = r2y_ctrl_c_ref_yb_blend->area_a_correct_gain_p;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYAALPGA.bit.YBYAALPGA1     = r2y_ctrl_c_ref_yb_blend->area_a_correct_gain_m;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYAALPBD.bit.YBYAALPBD_0    = r2y_ctrl_c_ref_yb_blend->area_a_correct_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYAALPBD.bit.YBYAALPBD_1    = r2y_ctrl_c_ref_yb_blend->area_a_correct_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYAALPCLP.bit.YBYAALPCLPL   = r2y_ctrl_c_ref_yb_blend->area_a_correct_clip_lo;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYAALPCLP.bit.YBYAALPCLPH   = r2y_ctrl_c_ref_yb_blend->area_a_correct_clip_hi;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVBALPOF.bit.YBCRVBALPOF1 = r2y_ctrl_c_ref_yb_blend->area_b_offset;
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVBALPGA, union io_r2y_ybcrvbalpga, YBCRVBALPGA_0, r2y_ctrl_c_ref_yb_blend->area_b_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVBALPGA, union io_r2y_ybcrvbalpga, YBCRVBALPGA_1, r2y_ctrl_c_ref_yb_blend->area_b_gain[1] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVBALPBD.bit.YBCRVBALPBD1 = r2y_ctrl_c_ref_yb_blend->area_b_border;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVBALPCP.bit.YBCRVBALPCPL = r2y_ctrl_c_ref_yb_blend->area_b_scale_clip_lo;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBCRVBALPCP.bit.YBCRVBALPCPH = r2y_ctrl_c_ref_yb_blend->area_b_scale_clip_hi;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYBALPGA.bit.YBYBALPGA0     = r2y_ctrl_c_ref_yb_blend->area_b_correct_gain_p;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYBALPGA.bit.YBYBALPGA1     = r2y_ctrl_c_ref_yb_blend->area_b_correct_gain_m;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYBALPBD.bit.YBYBALPBD_0    = r2y_ctrl_c_ref_yb_blend->area_b_correct_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYBALPBD.bit.YBYBALPBD_1    = r2y_ctrl_c_ref_yb_blend->area_b_correct_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYBALPCLP.bit.YBYBALPCLPL   = r2y_ctrl_c_ref_yb_blend->area_b_correct_clip_lo;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YBCRV.YBYBALPCLP.bit.YBYBALPCLPH   = r2y_ctrl_c_ref_yb_blend->area_b_correct_clip_hi;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Color Noise Reduction(LPF) control
 */
INT32 im_r2y_ctrl3_color_nr(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_CLPF* const r2y_ctrl_clpf )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_clpf == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl3_color_nr error. r2y_ctrl_clpf = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_color_nr error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValColorNrCtrl( pipe_no, r2y_ctrl_clpf );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFCTL.bit.CLPFEN = r2y_ctrl_clpf->clpf_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFCTL.bit.CLPFYA = r2y_ctrl_clpf->interlock_blend_enable;
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_0, r2y_ctrl_clpf->lpf_k[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_1, r2y_ctrl_clpf->lpf_k[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_2, r2y_ctrl_clpf->lpf_k[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_3, r2y_ctrl_clpf->lpf_k[3] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_4, r2y_ctrl_clpf->lpf_k[4] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_5, r2y_ctrl_clpf->lpf_k[5] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_6, r2y_ctrl_clpf->lpf_k[6] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_7, r2y_ctrl_clpf->lpf_k[7] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFK, union io_r2y_clpfk, CLPFK_8, r2y_ctrl_clpf->lpf_k[8] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFOF.bit.CLPFOF_0 = r2y_ctrl_clpf->lpf_ib_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFOF.bit.CLPFOF_1 = r2y_ctrl_clpf->lpf_ib_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFOF.bit.CLPFOF_2 = r2y_ctrl_clpf->lpf_ib_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFOF.bit.CLPFOF_3 = r2y_ctrl_clpf->lpf_ib_offset[3];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFGA, union io_r2y_clpfga, CLPFGA_0, r2y_ctrl_clpf->lpf_ib_gain[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFGA, union io_r2y_clpfga, CLPFGA_1, r2y_ctrl_clpf->lpf_ib_gain[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFGA, union io_r2y_clpfga, CLPFGA_2, r2y_ctrl_clpf->lpf_ib_gain[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFGA, union io_r2y_clpfga, CLPFGA_3, r2y_ctrl_clpf->lpf_ib_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFBD.bit.CLPFBD_1 = r2y_ctrl_clpf->lpf_ib_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFBD.bit.CLPFBD_2 = r2y_ctrl_clpf->lpf_ib_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CLPF.CLPFBD.bit.CLPFBD_3 = r2y_ctrl_clpf->lpf_ib_border[2];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Chroma suppress control
 */
INT32 im_r2y_ctrl3_chroma_suppress(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_CS* const r2y_ctrl_cs )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_cs == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_chroma_suppress error. r2y_ctrl_cs = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_chroma_suppress error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValChromaSuppressCtrl( pipe_no, r2y_ctrl_cs );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYCTL.bit.CSYEN  = r2y_ctrl_cs->csy_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYCTL.bit.CSYKY  = r2y_ctrl_cs->csy_mix_ratio;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYCTL.bit.CSYTBL = r2y_ctrl_cs->csy_select_table;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYOF.bit.CSYOF_0 = r2y_ctrl_cs->csy_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYOF.bit.CSYOF_1 = r2y_ctrl_cs->csy_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYOF.bit.CSYOF_2 = r2y_ctrl_cs->csy_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYOF.bit.CSYOF_3 = r2y_ctrl_cs->csy_offset[3];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYGA, union io_r2y_csyga, CSYGA_0, r2y_ctrl_cs->csy_gain[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYGA, union io_r2y_csyga, CSYGA_1, r2y_ctrl_cs->csy_gain[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYGA, union io_r2y_csyga, CSYGA_2, r2y_ctrl_cs->csy_gain[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYGA, union io_r2y_csyga, CSYGA_3, r2y_ctrl_cs->csy_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYBD.bit.CSYBD_1 = r2y_ctrl_cs->csy_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYBD.bit.CSYBD_2 = r2y_ctrl_cs->csy_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CSYBD.bit.CSYBD_3 = r2y_ctrl_cs->csy_border[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.YCRVFX.bit.YRV    = r2y_ctrl_cs->y_rev_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.YCRVFX.bit.CRV    = r2y_ctrl_cs->c_rev_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.YCRVFX.bit.CFIXEN = r2y_ctrl_cs->c_fixed_enable;
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CFIX, union io_r2y_cfix, CFIXB, r2y_ctrl_cs->cb_fixed );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.CFIX, union io_r2y_cfix, CFIXR, r2y_ctrl_cs->cr_fixed );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.YCOF, union io_r2y_ycof, YOF, r2y_ctrl_cs->y_offset );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.YCOF, union io_r2y_ycof, COFB, r2y_ctrl_cs->cb_offset );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CSP.YCOF, union io_r2y_ycof, COFR, r2y_ctrl_cs->cr_offset );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Tone control table
 */
INT32 im_r2y_ctrl3_set_tone_control_table(ImR2yCtrl3 *self, UCHAR pipe_no, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gIM_Io_R2y_Tbl_Ptr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifndef CO_R2Y_RDMA_ON
	UINT32 loop_cnt;
#endif	// CO_R2Y_RDMA_ON
	INT32  ercd;

#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_set_tone_control_table error. src_tbl = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( write_ofs_num >= D_IM_R2Y_TABLE_MAX_TONE ) {
		Ddim_Assertion(("im_r2y_ctrl3_set_tone_control_table error. write_ofs_num > MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > D_IM_R2Y_TABLE_MAX_TONE ) {
		Ddim_Assertion(("im_r2y_ctrl3_set_tone_control_table error. write_ofs_num + array_num > MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_set_tone_control_table error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

	while( 1 ) {
		ercd = im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipe_no, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValToneCtrlTable( pipe_no, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipe_no );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			gIM_Io_R2y_Tbl_Ptr[pipe_no]->TC.hword[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
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
INT32 im_r2y_ctrl3_get_tone_control_table(ImR2yCtrl3 *self, UCHAR pipe_no, USHORT* const dst_tbl, USHORT read_ofs_num, USHORT array_num )
{
	INT32  ercd;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gIM_Io_R2y_Tbl_Ptr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(dst_tbl == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_get_tone_control_table error. dst_tbl = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( read_ofs_num >= D_IM_R2Y_TABLE_MAX_TONE ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_tone_control_table error. read_ofs_num > MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( (read_ofs_num + array_num) > D_IM_R2Y_TABLE_MAX_TONE ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_tone_control_table error. read_ofs_num + array_num > MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_get_tone_control_table error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

	im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipe_no );

	while( 1 ) {
		ercd = im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipe_no, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_tbl,	// Read access only support Word-width. (Hardware specification.)
										 &gIM_Io_R2y_Tbl_Ptr[pipe_no]->TC.hword[im_r2y_rounddown_2(read_ofs_num)],
										 array_num );

		ercd = im_r2y_set_tone_control_tbl_access_enable(im_r2y_ctrl_new(), pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipe_no );

	return ercd;
}

/* Get Luminance evaluation
 */
INT32 im_r2y_ctrl3_get_luminance_evaluation_before_tone(ImR2yCtrl3 *self, UCHAR pipe_no, UINT32* const dst_addr, USHORT array_num )
{
	UINT32 loop_cnt;
	INT32 ercd;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile struct io_r2y_sram** gIM_Io_R2y_Tbl_Ptr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(dst_addr == NULL) {
		Ddim_Assertion(("im_r2y_ctrl3_get_luminance_evaluation_before_tone error. dst_addr = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_get_luminance_evaluation_before_tone error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	if( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YFLAG.bit.TCTACT != 0 ){
		return D_IM_R2Y_MACRO_BUSY;
	}

	im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipe_no );

	while( 1 ) {
		ercd = im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(im_r2y_ctrl2_new(), pipe_no, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			dst_addr[loop_cnt] = gIM_Io_R2y_Tbl_Ptr[pipe_no]->TCTDATA.word[loop_cnt];
		}

		ercd = im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(im_r2y_ctrl2_new(), pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return ercd;
}

/* Get BTC Histogram value
 */
INT32 im_r2y_ctrl3_get_histogram_before_tone(ImR2yCtrl3 *self, UCHAR pipe_no, E_R2Y_BTC_HIST_RGBTBL data_type, T_IM_R2Y_TCHS_FLG* const overflow_flg, USHORT* const dst_addr )
{
	INT32 ercd;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile struct io_r2y_sram** gIM_Io_R2y_Tbl_Ptr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( dst_addr == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_histogram_before_tone error. dst_addr = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( overflow_flg == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_histogram_before_tone error. overflow_flg = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( data_type >= E_R2Y_BTC_HIST_RGBTBL_MAX ) {
		Ddim_Assertion(("im_r2y_ctrl3_get_histogram_before_tone error. data_type >= MAX\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl3_get_histogram_before_tone error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	if( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YFLAG.bit.TCHACT != 0 ){
		return D_IM_R2Y_MACRO_BUSY;
	}

	im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipe_no );

	while( 1 ) {
		overflow_flg->Y = gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHOV.bit.TCHYOV;
		overflow_flg->R = gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHOV.bit.TCHROV;
		overflow_flg->G = gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHOV.bit.TCHGOV;
		overflow_flg->B = gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHOV.bit.TCHBOV;

		ercd = im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(im_r2y_ctrl2_new(), pipe_no, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		switch( data_type ){
			case E_R2Y_BTC_HIST_RGBTBL_R:
				im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr,	// Read access only support Word-width. (Hardware specification.)
												 gIM_Io_R2y_Tbl_Ptr[pipe_no]->TCHSRDATA.hword,
												 D_IM_R2Y_TABLE_MAX_BTC_HISTOGRAM_RGB );
				break;
			case E_R2Y_BTC_HIST_RGBTBL_G:
				im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr,	// Read access only support Word-width. (Hardware specification.)
												 gIM_Io_R2y_Tbl_Ptr[pipe_no]->TCHSGDATA.hword,
												 D_IM_R2Y_TABLE_MAX_BTC_HISTOGRAM_RGB );
				break;
			case E_R2Y_BTC_HIST_RGBTBL_B:
				im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr,	// Read access only support Word-width. (Hardware specification.)
												 gIM_Io_R2y_Tbl_Ptr[pipe_no]->TCHSBDATA.hword,
												 D_IM_R2Y_TABLE_MAX_BTC_HISTOGRAM_RGB );
				break;
//			case E_R2Y_BTC_HIST_RGBTBL_Y:
			default:
				im_r2y_ctrl3_copy_reg_to_sdram_ushort(im_r2y_ctrl3_new(),  dst_addr,	// Read access only support Word-width. (Hardware specification.)
												 gIM_Io_R2y_Tbl_Ptr[pipe_no]->TCHSYDATA.hword,
												 D_IM_R2Y_TABLE_MAX_BTC_HISTOGRAM_Y );
				break;
		}

		ercd = im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(im_r2y_ctrl2_new(), pipe_no, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return ercd;
}

ImR2yCtrl3 *im_r2y_ctrl3_new(void)
{
	ImR2yCtrl3* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL3,sizeof(ImR2yCtrl3Private));
	return self;
}
