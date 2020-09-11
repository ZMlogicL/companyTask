/*
 * imr2yedge.c
 *
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

#include "imr2yedge.h"
#include "imr2y.h"
#include "imr2y2.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yEdge, im_r2y_edge);
#define IM_R2Y_EDGE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yEdgePrivate, IM_TYPE_R2Y_EDGE))

struct _ImR2yEdgePrivate
{
	int a;
};


static VOID imR2ySetHighEdgeSclTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_high_edge_scl_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetHighEdgeSclTblAccessEnable,
};

static VOID imR2ySetHighEdgeStepTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_high_edge_step_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetHighEdgeStepTblAccessEnable,
};

static VOID imR2ySetMediumEdgeSclTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_medium_edge_scl_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetMediumEdgeSclTblAccessEnable,
};

static VOID imR2ySetMediumEdgeStepTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_medium_edge_step_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetMediumEdgeStepTblAccessEnable,
};

static VOID imR2ySetlowEdgeSclTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_low_edge_scl_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetlowEdgeSclTblAccessEnable,
};

static VOID imR2ySetlowEdgeStepTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_low_edge_step_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetlowEdgeStepTblAccessEnable,
};


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static VOID imR2ySetRdmaValEenrCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_CMN* const r2y_ctrl_edge_cmn );
static VOID imR2ySetRdmaValHighEdgeCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_HEDGE* const r2y_ctrl_hedge );
static VOID imR2ySetRdmaValMediumEdgeCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_MEDGE* const r2y_ctrl_medge );
static VOID imR2ySetRdmaValLowEdgeCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_LEDGE* const r2y_ctrl_ledge );
static VOID imR2ySetRdmaValEdgeDotNoiseCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_DOT_NOISE* const r2y_ctrl_edge_dot );
static VOID imR2ySetRdmaValEdgeBlendCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_BLEND* const r2y_ctrl_edge_blend );

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*IMPL
*/
static void im_r2y_edge_constructor(ImR2yEdge *self)
{
	ImR2yEdgePrivate *priv = IM_R2Y_EDGE_GET_PRIVATE(self);
}

static void im_r2y_edge_destructor(ImR2yEdge *self)
{
	ImR2yEdgePrivate *priv = IM_R2Y_EDGE_GET_PRIVATE(self);
}

static VOID imR2ySetHighEdgeSclTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EHSAEN = enable;
}

static VOID imR2ySetHighEdgeStepTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EHTAEN = enable;
}

static VOID imR2ySetMediumEdgeSclTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EMSAEN = enable;
}

static VOID imR2ySetMediumEdgeStepTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EMTAEN = enable;
}

static VOID imR2ySetlowEdgeSclTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.ELSAEN = enable;
}

static VOID imR2ySetlowEdgeStepTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.ELTAEN = enable;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static VOID imR2ySetRdmaValEenrCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_CMN* const r2y_ctrl_edge_cmn )
{
	T_IM_R2Y_CTRL_RDMA_EENR_VAL eenr_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_EENR_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	eenr_ctrl.EGSMCTL.bit.EGSMT    = r2y_ctrl_edge_cmn->reduction_mode;
	eenr_ctrl.EGSMTT.bit.EGSMTTH   = r2y_ctrl_edge_cmn->threshold;
	eenr_ctrl.EGSMTT.bit.EGSMTTXGA = r2y_ctrl_edge_cmn->texture_gain;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_EENR_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&eenr_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValHighEdgeCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_HEDGE* const r2y_ctrl_hedge )
{
	T_IM_R2Y_CTRL_RDMA_EGHW_VAL eghw_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_EGHW_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	eghw_ctrl.EGHWCTL.bit.EGHWEN     = r2y_ctrl_hedge->edge_enable;
	eghw_ctrl.EGHWCTL.bit.EGHWMP     = r2y_ctrl_hedge->scale_enable;
	eghw_ctrl.EGHWCTL.bit.EGHWTC     = r2y_ctrl_hedge->table_clip_select;
	eghw_ctrl.EGHWCTL.bit.EGHWSCLRES = r2y_ctrl_hedge->scale_table_resol;
	eghw_ctrl.EGHWCTL.bit.EGHWSCLTBL = r2y_ctrl_hedge->scale_table_select;
	eghw_ctrl.EGHWCTL.bit.EGHWTCRES  = r2y_ctrl_hedge->gradation_table_resol;
	eghw_ctrl.EGHWCTL.bit.EGHWTCTBL  = r2y_ctrl_hedge->gradation_table_select;
	eghw_ctrl.EGHWCTL.bit.EGHWNRLV   = r2y_ctrl_hedge->nr_level;

	eghw_ctrl.EGHWHPFK.bit.EGHWHPFK0 = r2y_ctrl_hedge->hpf_k[0];
	im_r2y_set_reg_signed_a( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK1, r2y_ctrl_hedge->hpf_k[1] );
	im_r2y_set_reg_signed_a( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK2, r2y_ctrl_hedge->hpf_k[2] );
	im_r2y_set_reg_signed_a( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK3, r2y_ctrl_hedge->hpf_k[3] );
	im_r2y_set_reg_signed_a( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK4, r2y_ctrl_hedge->hpf_k[4] );
	im_r2y_set_reg_signed_a( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK5, r2y_ctrl_hedge->hpf_k[5] );

	eghw_ctrl.EGHWCORPOF.bit.EGHWCORPOF_0 = r2y_ctrl_hedge->corp_offset[0];
	eghw_ctrl.EGHWCORPOF.bit.EGHWCORPOF_1 = r2y_ctrl_hedge->corp_offset[1];
	eghw_ctrl.EGHWCORPOF.bit.EGHWCORPOF_2 = r2y_ctrl_hedge->corp_offset[2];
	eghw_ctrl.EGHWCORPOF.bit.EGHWCORPOF_3 = r2y_ctrl_hedge->corp_offset[3];
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_0, r2y_ctrl_hedge->corp_gain[0] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_1, r2y_ctrl_hedge->corp_gain[1] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_2, r2y_ctrl_hedge->corp_gain[2] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_3, r2y_ctrl_hedge->corp_gain[3] );
	eghw_ctrl.EGHWCORPBD.bit.EGHWCORPBD_1 = r2y_ctrl_hedge->corp_border[0];
	eghw_ctrl.EGHWCORPBD.bit.EGHWCORPBD_2 = r2y_ctrl_hedge->corp_border[1];
	eghw_ctrl.EGHWCORPBD.bit.EGHWCORPBD_3 = r2y_ctrl_hedge->corp_border[2];

	eghw_ctrl.EGHWCORMOF.bit.EGHWCORMOF_0 = r2y_ctrl_hedge->corm_offset[0];
	eghw_ctrl.EGHWCORMOF.bit.EGHWCORMOF_1 = r2y_ctrl_hedge->corm_offset[1];
	eghw_ctrl.EGHWCORMOF.bit.EGHWCORMOF_2 = r2y_ctrl_hedge->corm_offset[2];
	eghw_ctrl.EGHWCORMOF.bit.EGHWCORMOF_3 = r2y_ctrl_hedge->corm_offset[3];
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_0, r2y_ctrl_hedge->corm_gain[0] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_1, r2y_ctrl_hedge->corm_gain[1] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_2, r2y_ctrl_hedge->corm_gain[2] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_3, r2y_ctrl_hedge->corm_gain[3] );
	eghw_ctrl.EGHWCORMBD.bit.EGHWCORMBD_1 = r2y_ctrl_hedge->corm_border[0];
	eghw_ctrl.EGHWCORMBD.bit.EGHWCORMBD_2 = r2y_ctrl_hedge->corm_border[1];
	eghw_ctrl.EGHWCORMBD.bit.EGHWCORMBD_3 = r2y_ctrl_hedge->corm_border[2];

	eghw_ctrl.EGHWSCLSUP.bit.EGHWSCLSUP = r2y_ctrl_hedge->sup_scl;

	eghw_ctrl.EGHWCLPPOF.bit.EGHWCLPPOF_0 = r2y_ctrl_hedge->level_clip_p_offset[0];
	eghw_ctrl.EGHWCLPPOF.bit.EGHWCLPPOF_1 = r2y_ctrl_hedge->level_clip_p_offset[1];
	eghw_ctrl.EGHWCLPPOF.bit.EGHWCLPPOF_2 = r2y_ctrl_hedge->level_clip_p_offset[2];
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_0, r2y_ctrl_hedge->level_clip_p_gain[0] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_1, r2y_ctrl_hedge->level_clip_p_gain[1] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_2, r2y_ctrl_hedge->level_clip_p_gain[2] );
	eghw_ctrl.EGHWCLPPBD.bit.EGHWCLPPBD_1 = r2y_ctrl_hedge->level_clip_p_border[0];
	eghw_ctrl.EGHWCLPPBD.bit.EGHWCLPPBD_2 = r2y_ctrl_hedge->level_clip_p_border[1];

	eghw_ctrl.EGHWCLPMOF.bit.EGHWCLPMOF_0 = r2y_ctrl_hedge->level_clip_m_offset[0];
	eghw_ctrl.EGHWCLPMOF.bit.EGHWCLPMOF_1 = r2y_ctrl_hedge->level_clip_m_offset[1];
	eghw_ctrl.EGHWCLPMOF.bit.EGHWCLPMOF_2 = r2y_ctrl_hedge->level_clip_m_offset[2];
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_0, r2y_ctrl_hedge->level_clip_m_gain[0] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_1, r2y_ctrl_hedge->level_clip_m_gain[1] );
	im_r2y_set_reg_signed( eghw_ctrl.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_2, r2y_ctrl_hedge->level_clip_m_gain[2] );
	eghw_ctrl.EGHWCLPMBD.bit.EGHWCLPMBD_1 = r2y_ctrl_hedge->level_clip_m_border[0];
	eghw_ctrl.EGHWCLPMBD.bit.EGHWCLPMBD_2 = r2y_ctrl_hedge->level_clip_m_border[1];

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_EGHW_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&eghw_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValMediumEdgeCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_MEDGE* const r2y_ctrl_medge )
{
	T_IM_R2Y_CTRL_RDMA_EGMW_VAL egmw_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_EGMW_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	egmw_ctrl.EGMWCTL.bit.EGMWEN     = r2y_ctrl_medge->edge_enable;
	egmw_ctrl.EGMWCTL.bit.EGMWMP     = r2y_ctrl_medge->scale_enable;
	egmw_ctrl.EGMWCTL.bit.EGMWTC     = r2y_ctrl_medge->table_clip_select;
	egmw_ctrl.EGMWCTL.bit.EGMWSCLRES = r2y_ctrl_medge->scale_table_resol;
	egmw_ctrl.EGMWCTL.bit.EGMWSCLTBL = r2y_ctrl_medge->scale_table_select;
	egmw_ctrl.EGMWCTL.bit.EGMWTCRES  = r2y_ctrl_medge->gradation_table_resol;
	egmw_ctrl.EGMWCTL.bit.EGMWTCTBL  = r2y_ctrl_medge->gradation_table_select;
	egmw_ctrl.EGMWCTL.bit.EGMWNRLV   = r2y_ctrl_medge->nr_level;

	egmw_ctrl.EGMWHPFK.bit.EGMWHPFK0 = r2y_ctrl_medge->hpf_k[0];
	im_r2y_set_reg_signed_a( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK1, r2y_ctrl_medge->hpf_k[1] );
	im_r2y_set_reg_signed_a( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK2, r2y_ctrl_medge->hpf_k[2] );
	im_r2y_set_reg_signed_a( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK3, r2y_ctrl_medge->hpf_k[3] );
	im_r2y_set_reg_signed_a( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK4, r2y_ctrl_medge->hpf_k[4] );
	im_r2y_set_reg_signed_a( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK5, r2y_ctrl_medge->hpf_k[5] );

	egmw_ctrl.EGMWCORPOF.bit.EGMWCORPOF_0 = r2y_ctrl_medge->corp_offset[0];
	egmw_ctrl.EGMWCORPOF.bit.EGMWCORPOF_1 = r2y_ctrl_medge->corp_offset[1];
	egmw_ctrl.EGMWCORPOF.bit.EGMWCORPOF_2 = r2y_ctrl_medge->corp_offset[2];
	egmw_ctrl.EGMWCORPOF.bit.EGMWCORPOF_3 = r2y_ctrl_medge->corp_offset[3];
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_0, r2y_ctrl_medge->corp_gain[0] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_1, r2y_ctrl_medge->corp_gain[1] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_2, r2y_ctrl_medge->corp_gain[2] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_3, r2y_ctrl_medge->corp_gain[3] );
	egmw_ctrl.EGMWCORPBD.bit.EGMWCORPBD_1 = r2y_ctrl_medge->corp_border[0];
	egmw_ctrl.EGMWCORPBD.bit.EGMWCORPBD_2 = r2y_ctrl_medge->corp_border[1];
	egmw_ctrl.EGMWCORPBD.bit.EGMWCORPBD_3 = r2y_ctrl_medge->corp_border[2];

	egmw_ctrl.EGMWCORMOF.bit.EGMWCORMOF_0 = r2y_ctrl_medge->corm_offset[0];
	egmw_ctrl.EGMWCORMOF.bit.EGMWCORMOF_1 = r2y_ctrl_medge->corm_offset[1];
	egmw_ctrl.EGMWCORMOF.bit.EGMWCORMOF_2 = r2y_ctrl_medge->corm_offset[2];
	egmw_ctrl.EGMWCORMOF.bit.EGMWCORMOF_3 = r2y_ctrl_medge->corm_offset[3];
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_0, r2y_ctrl_medge->corm_gain[0] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_1, r2y_ctrl_medge->corm_gain[1] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_2, r2y_ctrl_medge->corm_gain[2] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_3, r2y_ctrl_medge->corm_gain[3] );
	egmw_ctrl.EGMWCORMBD.bit.EGMWCORMBD_1 = r2y_ctrl_medge->corm_border[0];
	egmw_ctrl.EGMWCORMBD.bit.EGMWCORMBD_2 = r2y_ctrl_medge->corm_border[1];
	egmw_ctrl.EGMWCORMBD.bit.EGMWCORMBD_3 = r2y_ctrl_medge->corm_border[2];

	egmw_ctrl.EGMWSCLSUP.bit.EGMWSCLSUP = r2y_ctrl_medge->sup_scl;

	egmw_ctrl.EGMWCLPPOF.bit.EGMWCLPPOF_0 = r2y_ctrl_medge->level_clip_p_offset[0];
	egmw_ctrl.EGMWCLPPOF.bit.EGMWCLPPOF_1 = r2y_ctrl_medge->level_clip_p_offset[1];
	egmw_ctrl.EGMWCLPPOF.bit.EGMWCLPPOF_2 = r2y_ctrl_medge->level_clip_p_offset[2];
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_0, r2y_ctrl_medge->level_clip_p_gain[0] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_1, r2y_ctrl_medge->level_clip_p_gain[1] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_2, r2y_ctrl_medge->level_clip_p_gain[2] );
	egmw_ctrl.EGMWCLPPBD.bit.EGMWCLPPBD_1 = r2y_ctrl_medge->level_clip_p_border[0];
	egmw_ctrl.EGMWCLPPBD.bit.EGMWCLPPBD_2 = r2y_ctrl_medge->level_clip_p_border[1];

	egmw_ctrl.EGMWCLPMOF.bit.EGMWCLPMOF_0 = r2y_ctrl_medge->level_clip_m_offset[0];
	egmw_ctrl.EGMWCLPMOF.bit.EGMWCLPMOF_1 = r2y_ctrl_medge->level_clip_m_offset[1];
	egmw_ctrl.EGMWCLPMOF.bit.EGMWCLPMOF_2 = r2y_ctrl_medge->level_clip_m_offset[2];
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_0, r2y_ctrl_medge->level_clip_m_gain[0] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_1, r2y_ctrl_medge->level_clip_m_gain[1] );
	im_r2y_set_reg_signed( egmw_ctrl.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_2, r2y_ctrl_medge->level_clip_m_gain[2] );
	egmw_ctrl.EGMWCLPMBD.bit.EGMWCLPMBD_1 = r2y_ctrl_medge->level_clip_m_border[0];
	egmw_ctrl.EGMWCLPMBD.bit.EGMWCLPMBD_2 = r2y_ctrl_medge->level_clip_m_border[1];

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_EGMW_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&egmw_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValLowEdgeCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_LEDGE* const r2y_ctrl_ledge )
{
	T_IM_R2Y_CTRL_RDMA_EGLW_VAL eglw_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_EGLW_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	eglw_ctrl.EGLWCTL.bit.EGLWEN     = r2y_ctrl_ledge->edge_enable;
	eglw_ctrl.EGLWCTL.bit.EGLWMP     = r2y_ctrl_ledge->scale_enable;
	eglw_ctrl.EGLWCTL.bit.EGLWTC     = r2y_ctrl_ledge->table_clip_select;
	eglw_ctrl.EGLWCTL.bit.EGLWSCLRES = r2y_ctrl_ledge->scale_table_resol;
	eglw_ctrl.EGLWCTL.bit.EGLWSCLTBL = r2y_ctrl_ledge->scale_table_select;
	eglw_ctrl.EGLWCTL.bit.EGLWTCRES  = r2y_ctrl_ledge->gradation_table_resol;
	eglw_ctrl.EGLWCTL.bit.EGLWTCTBL  = r2y_ctrl_ledge->gradation_table_select;

	eglw_ctrl.EGLWHPFK.bit.EGLWHPFK0 = r2y_ctrl_ledge->hpf_k[0];
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK1, r2y_ctrl_ledge->hpf_k[1] );
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK2, r2y_ctrl_ledge->hpf_k[2] );
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK3, r2y_ctrl_ledge->hpf_k[3] );
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK4, r2y_ctrl_ledge->hpf_k[4] );
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK5, r2y_ctrl_ledge->hpf_k[5] );
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK6, r2y_ctrl_ledge->hpf_k[6] );
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK7, r2y_ctrl_ledge->hpf_k[7] );
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK8, r2y_ctrl_ledge->hpf_k[8] );
	im_r2y_set_reg_signed_a( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK9, r2y_ctrl_ledge->hpf_k[9] );

	eglw_ctrl.EGLWCORPOF.bit.EGLWCORPOF_0 = r2y_ctrl_ledge->corp_offset[0];
	eglw_ctrl.EGLWCORPOF.bit.EGLWCORPOF_1 = r2y_ctrl_ledge->corp_offset[1];
	eglw_ctrl.EGLWCORPOF.bit.EGLWCORPOF_2 = r2y_ctrl_ledge->corp_offset[2];
	eglw_ctrl.EGLWCORPOF.bit.EGLWCORPOF_3 = r2y_ctrl_ledge->corp_offset[3];
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_0, r2y_ctrl_ledge->corp_gain[0] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_1, r2y_ctrl_ledge->corp_gain[1] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_2, r2y_ctrl_ledge->corp_gain[2] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_3, r2y_ctrl_ledge->corp_gain[3] );
	eglw_ctrl.EGLWCORPBD.bit.EGLWCORPBD_1 = r2y_ctrl_ledge->corp_border[0];
	eglw_ctrl.EGLWCORPBD.bit.EGLWCORPBD_2 = r2y_ctrl_ledge->corp_border[1];
	eglw_ctrl.EGLWCORPBD.bit.EGLWCORPBD_3 = r2y_ctrl_ledge->corp_border[2];

	eglw_ctrl.EGLWCORMOF.bit.EGLWCORMOF_0 = r2y_ctrl_ledge->corm_offset[0];
	eglw_ctrl.EGLWCORMOF.bit.EGLWCORMOF_1 = r2y_ctrl_ledge->corm_offset[1];
	eglw_ctrl.EGLWCORMOF.bit.EGLWCORMOF_2 = r2y_ctrl_ledge->corm_offset[2];
	eglw_ctrl.EGLWCORMOF.bit.EGLWCORMOF_3 = r2y_ctrl_ledge->corm_offset[3];
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_0, r2y_ctrl_ledge->corm_gain[0] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_1, r2y_ctrl_ledge->corm_gain[1] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_2, r2y_ctrl_ledge->corm_gain[2] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_3, r2y_ctrl_ledge->corm_gain[3] );
	eglw_ctrl.EGLWCORMBD.bit.EGLWCORMBD_1 = r2y_ctrl_ledge->corm_border[0];
	eglw_ctrl.EGLWCORMBD.bit.EGLWCORMBD_2 = r2y_ctrl_ledge->corm_border[1];
	eglw_ctrl.EGLWCORMBD.bit.EGLWCORMBD_3 = r2y_ctrl_ledge->corm_border[2];

	eglw_ctrl.EGLWSCLSUP.bit.EGLWSCLSUP = r2y_ctrl_ledge->sup_scl;

	eglw_ctrl.EGLWCLPPOF.bit.EGLWCLPPOF_0 = r2y_ctrl_ledge->level_clip_p_offset[0];
	eglw_ctrl.EGLWCLPPOF.bit.EGLWCLPPOF_1 = r2y_ctrl_ledge->level_clip_p_offset[1];
	eglw_ctrl.EGLWCLPPOF.bit.EGLWCLPPOF_2 = r2y_ctrl_ledge->level_clip_p_offset[2];
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_0, r2y_ctrl_ledge->level_clip_p_gain[0] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_1, r2y_ctrl_ledge->level_clip_p_gain[1] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_2, r2y_ctrl_ledge->level_clip_p_gain[2] );
	eglw_ctrl.EGLWCLPPBD.bit.EGLWCLPPBD_1 = r2y_ctrl_ledge->level_clip_p_border[0];
	eglw_ctrl.EGLWCLPPBD.bit.EGLWCLPPBD_2 = r2y_ctrl_ledge->level_clip_p_border[1];

	eglw_ctrl.EGLWCLPMOF.bit.EGLWCLPMOF_0 = r2y_ctrl_ledge->level_clip_m_offset[0];
	eglw_ctrl.EGLWCLPMOF.bit.EGLWCLPMOF_1 = r2y_ctrl_ledge->level_clip_m_offset[1];
	eglw_ctrl.EGLWCLPMOF.bit.EGLWCLPMOF_2 = r2y_ctrl_ledge->level_clip_m_offset[2];
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_0, r2y_ctrl_ledge->level_clip_m_gain[0] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_1, r2y_ctrl_ledge->level_clip_m_gain[1] );
	im_r2y_set_reg_signed( eglw_ctrl.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_2, r2y_ctrl_ledge->level_clip_m_gain[2] );
	eglw_ctrl.EGLWCLPMBD.bit.EGLWCLPMBD_1 = r2y_ctrl_ledge->level_clip_m_border[0];
	eglw_ctrl.EGLWCLPMBD.bit.EGLWCLPMBD_2 = r2y_ctrl_ledge->level_clip_m_border[1];

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_EGLW_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&eglw_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValEdgeDotNoiseCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_DOT_NOISE* const r2y_ctrl_edge_dot )
{
	T_IM_R2Y_CTRL_RDMA_EGDT_VAL egdt_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_EGDT_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	egdt_ctrl.EGDTCTL.bit.EGDTHW     = r2y_ctrl_edge_dot->hf_enable;
	egdt_ctrl.EGDTCTL.bit.EGDTMW     = r2y_ctrl_edge_dot->mf_enable;
	egdt_ctrl.EGDTHWTH.bit.EGDTHWTHP = r2y_ctrl_edge_dot->hf_p_threshold;
	egdt_ctrl.EGDTHWTH.bit.EGDTHWTHM = r2y_ctrl_edge_dot->hf_m_threshold;
	egdt_ctrl.EGDTHWK.bit.EGDTHWKP   = r2y_ctrl_edge_dot->hf_p_coef;
	egdt_ctrl.EGDTHWK.bit.EGDTHWKM   = r2y_ctrl_edge_dot->hf_m_coef;
	egdt_ctrl.EGDTMWTH.bit.EGDTMWTHP = r2y_ctrl_edge_dot->mf_p_threshold;
	egdt_ctrl.EGDTMWTH.bit.EGDTMWTHM = r2y_ctrl_edge_dot->mf_m_threshold;
	egdt_ctrl.EGDTMWK.bit.EGDTMWKP   = r2y_ctrl_edge_dot->mf_p_coef;
	egdt_ctrl.EGDTMWK.bit.EGDTMWKM   = r2y_ctrl_edge_dot->mf_m_coef;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_EGDT_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&egdt_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValEdgeBlendCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_BLEND* const r2y_ctrl_edge_blend )
{
	T_IM_R2Y_CTRL_RDMA_EGCMP_VAL egcmp_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_EGCMP_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	egcmp_ctrl.EGCMPCTL.bit.EGCMPS = r2y_ctrl_edge_blend->blend_type;

	egcmp_ctrl.EGCMPBD.bit.EGCMPBD_1 = r2y_ctrl_edge_blend->border[0];
	egcmp_ctrl.EGCMPBD.bit.EGCMPBD_2 = r2y_ctrl_edge_blend->border[1];
	egcmp_ctrl.EGCMPBD.bit.EGCMPBD_3 = r2y_ctrl_edge_blend->border[2];

	egcmp_ctrl.EGCMPALPOF.bit.EGCMPALPOF_0 = r2y_ctrl_edge_blend->alpha_offset[0];
	egcmp_ctrl.EGCMPALPOF.bit.EGCMPALPOF_1 = r2y_ctrl_edge_blend->alpha_offset[1];
	egcmp_ctrl.EGCMPALPOF.bit.EGCMPALPOF_2 = r2y_ctrl_edge_blend->alpha_offset[2];
	egcmp_ctrl.EGCMPALPOF.bit.EGCMPALPOF_3 = r2y_ctrl_edge_blend->alpha_offset[3];
	im_r2y_set_reg_signed_a( egcmp_ctrl.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_0, r2y_ctrl_edge_blend->alpha_gain[0] );
	im_r2y_set_reg_signed_a( egcmp_ctrl.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_1, r2y_ctrl_edge_blend->alpha_gain[1] );
	im_r2y_set_reg_signed_a( egcmp_ctrl.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_2, r2y_ctrl_edge_blend->alpha_gain[2] );
	im_r2y_set_reg_signed_a( egcmp_ctrl.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_3, r2y_ctrl_edge_blend->alpha_gain[3] );

	egcmp_ctrl.EGCMPBTAOF.bit.EGCMPBTAOF_0 = r2y_ctrl_edge_blend->beta_offset[0];
	egcmp_ctrl.EGCMPBTAOF.bit.EGCMPBTAOF_1 = r2y_ctrl_edge_blend->beta_offset[1];
	egcmp_ctrl.EGCMPBTAOF.bit.EGCMPBTAOF_2 = r2y_ctrl_edge_blend->beta_offset[2];
	egcmp_ctrl.EGCMPBTAOF.bit.EGCMPBTAOF_3 = r2y_ctrl_edge_blend->beta_offset[3];
	im_r2y_set_reg_signed_a( egcmp_ctrl.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_0, r2y_ctrl_edge_blend->beta_gain[0] );
	im_r2y_set_reg_signed_a( egcmp_ctrl.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_1, r2y_ctrl_edge_blend->beta_gain[1] );
	im_r2y_set_reg_signed_a( egcmp_ctrl.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_2, r2y_ctrl_edge_blend->beta_gain[2] );
	im_r2y_set_reg_signed_a( egcmp_ctrl.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_3, r2y_ctrl_edge_blend->beta_gain[3] );

	egcmp_ctrl.EGCMPCLP.bit.EGCMPCLPP = r2y_ctrl_edge_blend->level_clip_p;
	egcmp_ctrl.EGCMPCLP.bit.EGCMPCLPM = r2y_ctrl_edge_blend->level_clip_m;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_EGCMP_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&egcmp_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*PUBLIC
*/
/* High/Medium frequency edge enhancement common control
 */
INT32 im_r2y_edge_noise_reduction(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_CMN* const r2y_ctrl_edge_cmn )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_edge_cmn == NULL) {
		Ddim_Assertion(("im_r2y_edge_noise_reduction error. r2y_ctrl_edge_cmn = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_noise_reduction error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEenrCtrl( pipe_no, r2y_ctrl_edge_cmn );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGSM.EGSMCTL.bit.EGSMT    = r2y_ctrl_edge_cmn->reduction_mode;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGSM.EGSMTT.bit.EGSMTTH   = r2y_ctrl_edge_cmn->threshold;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGSM.EGSMTT.bit.EGSMTTXGA = r2y_ctrl_edge_cmn->texture_gain;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* High frequency Edge emphasis control
 */
INT32 im_r2y_edge_high_edge(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_HEDGE* const r2y_ctrl_hedge )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_hedge == NULL) {
		Ddim_Assertion(("im_r2y_edge_high_edge error. r2y_ctrl_hedge = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_high_edge error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValHighEdgeCtrl( pipe_no, r2y_ctrl_hedge );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EGHWEN     = r2y_ctrl_hedge->edge_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EGHWMP     = r2y_ctrl_hedge->scale_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EGHWTC     = r2y_ctrl_hedge->table_clip_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EGHWSCLRES = r2y_ctrl_hedge->scale_table_resol;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EGHWSCLTBL = r2y_ctrl_hedge->scale_table_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EGHWTCRES  = r2y_ctrl_hedge->gradation_table_resol;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EGHWTCTBL  = r2y_ctrl_hedge->gradation_table_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCTL.bit.EGHWNRLV   = r2y_ctrl_hedge->nr_level;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK0 = r2y_ctrl_hedge->hpf_k[0];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK1, r2y_ctrl_hedge->hpf_k[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK2, r2y_ctrl_hedge->hpf_k[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK3, r2y_ctrl_hedge->hpf_k[3] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK4, r2y_ctrl_hedge->hpf_k[4] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK5, r2y_ctrl_hedge->hpf_k[5] );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_0 = r2y_ctrl_hedge->corp_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_1 = r2y_ctrl_hedge->corp_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_2 = r2y_ctrl_hedge->corp_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_3 = r2y_ctrl_hedge->corp_offset[3];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_0, r2y_ctrl_hedge->corp_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_1, r2y_ctrl_hedge->corp_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_2, r2y_ctrl_hedge->corp_gain[2] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_3, r2y_ctrl_hedge->corp_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_1 = r2y_ctrl_hedge->corp_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_2 = r2y_ctrl_hedge->corp_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_3 = r2y_ctrl_hedge->corp_border[2];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_0 = r2y_ctrl_hedge->corm_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_1 = r2y_ctrl_hedge->corm_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_2 = r2y_ctrl_hedge->corm_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_3 = r2y_ctrl_hedge->corm_offset[3];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_0, r2y_ctrl_hedge->corm_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_1, r2y_ctrl_hedge->corm_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_2, r2y_ctrl_hedge->corm_gain[2] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_3, r2y_ctrl_hedge->corm_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_1 = r2y_ctrl_hedge->corm_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_2 = r2y_ctrl_hedge->corm_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_3 = r2y_ctrl_hedge->corm_border[2];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWSCLSUP.bit.EGHWSCLSUP = r2y_ctrl_hedge->sup_scl;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_0 = r2y_ctrl_hedge->level_clip_p_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_1 = r2y_ctrl_hedge->level_clip_p_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_2 = r2y_ctrl_hedge->level_clip_p_offset[2];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_0, r2y_ctrl_hedge->level_clip_p_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_1, r2y_ctrl_hedge->level_clip_p_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_2, r2y_ctrl_hedge->level_clip_p_gain[2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPPBD.bit.EGHWCLPPBD_1 = r2y_ctrl_hedge->level_clip_p_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPPBD.bit.EGHWCLPPBD_2 = r2y_ctrl_hedge->level_clip_p_border[1];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_0 = r2y_ctrl_hedge->level_clip_m_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_1 = r2y_ctrl_hedge->level_clip_m_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_2 = r2y_ctrl_hedge->level_clip_m_offset[2];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_0, r2y_ctrl_hedge->level_clip_m_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_1, r2y_ctrl_hedge->level_clip_m_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_2, r2y_ctrl_hedge->level_clip_m_gain[2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPMBD.bit.EGHWCLPMBD_1 = r2y_ctrl_hedge->level_clip_m_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGHW.EGHWCLPMBD.bit.EGHWCLPMBD_2 = r2y_ctrl_hedge->level_clip_m_border[1];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set High Edge scale table access enable
 */
INT32 im_r2y_edge_set_high_edge_scl_tbl_access_enable( ImR2yEdge *self,UCHAR pipe_no, UCHAR scl_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_high_edge_scl_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_high_edge_scl_tbl_accen_ctrl,
									 scl_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_edge_set_high_edge_scl_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set High Edge step table access enable
 */
INT32 im_r2y_edge_set_high_edge_step_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR step_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_high_edge_step_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_high_edge_step_tbl_accen_ctrl,
									 step_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_edge_set_high_edge_step_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Medium frequency Edge emphasis control
 */
INT32 im_r2y_edge_medium_edge(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_MEDGE* const r2y_ctrl_medge )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_medge == NULL) {
		Ddim_Assertion(("im_r2y_edge_medium_edge error. r2y_ctrl_medge = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_medium_edge error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValMediumEdgeCtrl( pipe_no, r2y_ctrl_medge );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EGMWEN     = r2y_ctrl_medge->edge_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EGMWMP     = r2y_ctrl_medge->scale_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EGMWTC     = r2y_ctrl_medge->table_clip_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EGMWSCLRES = r2y_ctrl_medge->scale_table_resol;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EGMWSCLTBL = r2y_ctrl_medge->scale_table_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EGMWTCRES  = r2y_ctrl_medge->gradation_table_resol;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EGMWTCTBL  = r2y_ctrl_medge->gradation_table_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCTL.bit.EGMWNRLV   = r2y_ctrl_medge->nr_level;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK0 = r2y_ctrl_medge->hpf_k[0];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK1, r2y_ctrl_medge->hpf_k[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK2, r2y_ctrl_medge->hpf_k[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK3, r2y_ctrl_medge->hpf_k[3] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK4, r2y_ctrl_medge->hpf_k[4] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK5, r2y_ctrl_medge->hpf_k[5] );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_0 = r2y_ctrl_medge->corp_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_1 = r2y_ctrl_medge->corp_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_2 = r2y_ctrl_medge->corp_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_3 = r2y_ctrl_medge->corp_offset[3];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_0, r2y_ctrl_medge->corp_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_1, r2y_ctrl_medge->corp_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_2, r2y_ctrl_medge->corp_gain[2] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_3, r2y_ctrl_medge->corp_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_1 = r2y_ctrl_medge->corp_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_2 = r2y_ctrl_medge->corp_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_3 = r2y_ctrl_medge->corp_border[2];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_0 = r2y_ctrl_medge->corm_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_1 = r2y_ctrl_medge->corm_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_2 = r2y_ctrl_medge->corm_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_3 = r2y_ctrl_medge->corm_offset[3];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_0, r2y_ctrl_medge->corm_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_1, r2y_ctrl_medge->corm_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_2, r2y_ctrl_medge->corm_gain[2] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_3, r2y_ctrl_medge->corm_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_1 = r2y_ctrl_medge->corm_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_2 = r2y_ctrl_medge->corm_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_3 = r2y_ctrl_medge->corm_border[2];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWSCLSUP.bit.EGMWSCLSUP = r2y_ctrl_medge->sup_scl;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_0 = r2y_ctrl_medge->level_clip_p_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_1 = r2y_ctrl_medge->level_clip_p_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_2 = r2y_ctrl_medge->level_clip_p_offset[2];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_0, r2y_ctrl_medge->level_clip_p_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_1, r2y_ctrl_medge->level_clip_p_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_2, r2y_ctrl_medge->level_clip_p_gain[2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPPBD.bit.EGMWCLPPBD_1 = r2y_ctrl_medge->level_clip_p_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPPBD.bit.EGMWCLPPBD_2 = r2y_ctrl_medge->level_clip_p_border[1];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_0 = r2y_ctrl_medge->level_clip_m_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_1 = r2y_ctrl_medge->level_clip_m_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_2 = r2y_ctrl_medge->level_clip_m_offset[2];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_0, r2y_ctrl_medge->level_clip_m_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_1, r2y_ctrl_medge->level_clip_m_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_2, r2y_ctrl_medge->level_clip_m_gain[2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPMBD.bit.EGMWCLPMBD_1 = r2y_ctrl_medge->level_clip_m_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGMW.EGMWCLPMBD.bit.EGMWCLPMBD_2 = r2y_ctrl_medge->level_clip_m_border[1];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Medium Edge scale table access enable
 */
INT32 im_r2y_edge_set_medium_edge_scl_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR scl_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_medium_edge_scl_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_medium_edge_scl_tbl_accen_ctrl,
									 scl_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_edge_set_medium_edge_scl_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set Medium Edge step table access enable
 */
INT32 im_r2y_edge_set_medium_edge_step_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR step_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_medium_edge_step_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_medium_edge_step_tbl_accen_ctrl,
									 step_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_edge_set_medium_edge_step_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Low frequency Edge emphasis control
 */
INT32 im_r2y_edge_ctrl_low_edge(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_LEDGE* const r2y_ctrl_ledge )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_ledge == NULL) {
		Ddim_Assertion(("im_r2y_edge_ctrl_low_edge error. r2y_ctrl_ledge = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_ctrl_low_edge error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValLowEdgeCtrl( pipe_no, r2y_ctrl_ledge );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.EGLWEN     = r2y_ctrl_ledge->edge_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.EGLWMP     = r2y_ctrl_ledge->scale_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.EGLWTC     = r2y_ctrl_ledge->table_clip_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.EGLWSCLRES = r2y_ctrl_ledge->scale_table_resol;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.EGLWSCLTBL = r2y_ctrl_ledge->scale_table_select;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.EGLWTCRES  = r2y_ctrl_ledge->gradation_table_resol;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCTL.bit.EGLWTCTBL  = r2y_ctrl_ledge->gradation_table_select;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK.bit.EGLWHPFK0 = r2y_ctrl_ledge->hpf_k[0];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK1, r2y_ctrl_ledge->hpf_k[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK2, r2y_ctrl_ledge->hpf_k[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK3, r2y_ctrl_ledge->hpf_k[3] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK4, r2y_ctrl_ledge->hpf_k[4] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK5, r2y_ctrl_ledge->hpf_k[5] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK6, r2y_ctrl_ledge->hpf_k[6] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK7, r2y_ctrl_ledge->hpf_k[7] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK8, r2y_ctrl_ledge->hpf_k[8] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK9, r2y_ctrl_ledge->hpf_k[9] );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPOF.bit.EGLWCORPOF_0 = r2y_ctrl_ledge->corp_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPOF.bit.EGLWCORPOF_1 = r2y_ctrl_ledge->corp_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPOF.bit.EGLWCORPOF_2 = r2y_ctrl_ledge->corp_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPOF.bit.EGLWCORPOF_3 = r2y_ctrl_ledge->corp_offset[3];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_0, r2y_ctrl_ledge->corp_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_1, r2y_ctrl_ledge->corp_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_2, r2y_ctrl_ledge->corp_gain[2] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_3, r2y_ctrl_ledge->corp_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPBD.bit.EGLWCORPBD_1 = r2y_ctrl_ledge->corp_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPBD.bit.EGLWCORPBD_2 = r2y_ctrl_ledge->corp_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORPBD.bit.EGLWCORPBD_3 = r2y_ctrl_ledge->corp_border[2];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMOF.bit.EGLWCORMOF_0 = r2y_ctrl_ledge->corm_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMOF.bit.EGLWCORMOF_1 = r2y_ctrl_ledge->corm_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMOF.bit.EGLWCORMOF_2 = r2y_ctrl_ledge->corm_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMOF.bit.EGLWCORMOF_3 = r2y_ctrl_ledge->corm_offset[3];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_0, r2y_ctrl_ledge->corm_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_1, r2y_ctrl_ledge->corm_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_2, r2y_ctrl_ledge->corm_gain[2] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_3, r2y_ctrl_ledge->corm_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMBD.bit.EGLWCORMBD_1 = r2y_ctrl_ledge->corm_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMBD.bit.EGLWCORMBD_2 = r2y_ctrl_ledge->corm_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCORMBD.bit.EGLWCORMBD_3 = r2y_ctrl_ledge->corm_border[2];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWSCLSUP.bit.EGLWSCLSUP = r2y_ctrl_ledge->sup_scl;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPPOF.bit.EGLWCLPPOF_0 = r2y_ctrl_ledge->level_clip_p_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPPOF.bit.EGLWCLPPOF_1 = r2y_ctrl_ledge->level_clip_p_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPPOF.bit.EGLWCLPPOF_2 = r2y_ctrl_ledge->level_clip_p_offset[2];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_0, r2y_ctrl_ledge->level_clip_p_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_1, r2y_ctrl_ledge->level_clip_p_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_2, r2y_ctrl_ledge->level_clip_p_gain[2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPPBD.bit.EGLWCLPPBD_1 = r2y_ctrl_ledge->level_clip_p_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPPBD.bit.EGLWCLPPBD_2 = r2y_ctrl_ledge->level_clip_p_border[1];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPMOF.bit.EGLWCLPMOF_0 = r2y_ctrl_ledge->level_clip_m_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPMOF.bit.EGLWCLPMOF_1 = r2y_ctrl_ledge->level_clip_m_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPMOF.bit.EGLWCLPMOF_2 = r2y_ctrl_ledge->level_clip_m_offset[2];
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_0, r2y_ctrl_ledge->level_clip_m_gain[0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_1, r2y_ctrl_ledge->level_clip_m_gain[1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_2, r2y_ctrl_ledge->level_clip_m_gain[2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPMBD.bit.EGLWCLPMBD_1 = r2y_ctrl_ledge->level_clip_m_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGLW.EGLWCLPMBD.bit.EGLWCLPMBD_2 = r2y_ctrl_ledge->level_clip_m_border[1];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Low Edge scale table access enable
 */
INT32 im_r2y_edge_set_low_edge_scl_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR scl_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_low_edge_scl_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_low_edge_scl_tbl_accen_ctrl,
									 scl_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_edge_set_low_edge_scl_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set Low Edge step table access enable
 */
INT32 im_r2y_edge_set_low_edge_step_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR step_enable, UCHAR wait_enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_low_edge_step_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_low_edge_step_tbl_accen_ctrl,
									 step_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_edge_set_low_edge_step_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Is Post filter active
 */
INT32 im_r2y_edge_is_act_post_filter(ImR2yEdge *self, UCHAR pipe_no, UCHAR* const active_status )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_is_act_post_filter error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	*active_status = (gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YFLAG.bit.YCFACT != 0)?(D_IM_R2Y_ENABLE_ON):(D_IM_R2Y_ENABLE_OFF);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* Edge dot noise correction control
 */
INT32 im_r2y_edge_ctrl_dot_noise(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_DOT_NOISE* const r2y_ctrl_edge_dot )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_edge_dot == NULL) {
		Ddim_Assertion(("im_r2y_edge_ctrl_dot_noise error. r2y_ctrl_edge_dot = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_ctrl_dot_noise error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEdgeDotNoiseCtrl( pipe_no, r2y_ctrl_edge_dot );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTCTL.bit.EGDTHW     = r2y_ctrl_edge_dot->hf_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTCTL.bit.EGDTMW     = r2y_ctrl_edge_dot->mf_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTHWTH.bit.EGDTHWTHP = r2y_ctrl_edge_dot->hf_p_threshold;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTHWTH.bit.EGDTHWTHM = r2y_ctrl_edge_dot->hf_m_threshold;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTHWK.bit.EGDTHWKP   = r2y_ctrl_edge_dot->hf_p_coef;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTHWK.bit.EGDTHWKM   = r2y_ctrl_edge_dot->hf_m_coef;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTMWTH.bit.EGDTMWTHP = r2y_ctrl_edge_dot->mf_p_threshold;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTMWTH.bit.EGDTMWTHM = r2y_ctrl_edge_dot->mf_m_threshold;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTMWK.bit.EGDTMWKP   = r2y_ctrl_edge_dot->mf_p_coef;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGDT.EGDTMWK.bit.EGDTMWKM   = r2y_ctrl_edge_dot->mf_m_coef;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Edge emphasis blend control
 */
INT32 im_r2y_edge_ctrl_blend(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_BLEND* const r2y_ctrl_edge_blend )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_edge_blend == NULL) {
		Ddim_Assertion(("im_r2y_edge_ctrl_blend error. r2y_ctrl_edge_blend = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_ctrl_blend error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEdgeBlendCtrl( pipe_no, r2y_ctrl_edge_blend );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPCTL.bit.EGCMPS = r2y_ctrl_edge_blend->blend_type;

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBD.bit.EGCMPBD_1 = r2y_ctrl_edge_blend->border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBD.bit.EGCMPBD_2 = r2y_ctrl_edge_blend->border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBD.bit.EGCMPBD_3 = r2y_ctrl_edge_blend->border[2];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPALPOF.bit.EGCMPALPOF_0 = r2y_ctrl_edge_blend->alpha_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPALPOF.bit.EGCMPALPOF_1 = r2y_ctrl_edge_blend->alpha_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPALPOF.bit.EGCMPALPOF_2 = r2y_ctrl_edge_blend->alpha_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPALPOF.bit.EGCMPALPOF_3 = r2y_ctrl_edge_blend->alpha_offset[3];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_0, r2y_ctrl_edge_blend->alpha_gain[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_1, r2y_ctrl_edge_blend->alpha_gain[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_2, r2y_ctrl_edge_blend->alpha_gain[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_3, r2y_ctrl_edge_blend->alpha_gain[3] );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBTAOF.bit.EGCMPBTAOF_0 = r2y_ctrl_edge_blend->beta_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBTAOF.bit.EGCMPBTAOF_1 = r2y_ctrl_edge_blend->beta_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBTAOF.bit.EGCMPBTAOF_2 = r2y_ctrl_edge_blend->beta_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBTAOF.bit.EGCMPBTAOF_3 = r2y_ctrl_edge_blend->beta_offset[3];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_0, r2y_ctrl_edge_blend->beta_gain[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_1, r2y_ctrl_edge_blend->beta_gain[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_2, r2y_ctrl_edge_blend->beta_gain[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_3, r2y_ctrl_edge_blend->beta_gain[3] );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPCLP.bit.EGCMPCLPP = r2y_ctrl_edge_blend->level_clip_p;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.EGCMP.EGCMPCLP.bit.EGCMPCLPM = r2y_ctrl_edge_blend->level_clip_m;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

ImR2yEdge *im_r2y_edge_new(void)
{
	ImR2yEdge* self = k_object_new_with_private(IM_TYPE_R2Y_EDGE,sizeof(ImR2yEdgePrivate));
	return self;
}
