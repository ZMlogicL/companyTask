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


static void imR2ySetHighEdgeSclTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_high_edge_scl_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetHighEdgeSclTblAccessEnable,
};

static void imR2ySetHighEdgeStepTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_high_edge_step_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetHighEdgeStepTblAccessEnable,
};

static void imR2ySetMediumEdgeSclTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_medium_edge_scl_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetMediumEdgeSclTblAccessEnable,
};

static void imR2ySetMediumEdgeStepTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_medium_edge_step_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetMediumEdgeStepTblAccessEnable,
};

static void imR2ySetlowEdgeSclTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_low_edge_scl_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetlowEdgeSclTblAccessEnable,
};

static void imR2ySetlowEdgeStepTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_low_edge_step_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetlowEdgeStepTblAccessEnable,
};


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValEenrCtrl( kuint16 pipeNo, const CtrlEdgeCmn* const r2y_ctrl_edge_cmn );
static void imR2ySetRdmaValHighEdgeCtrl( kuint16 pipeNo, const R2yCtrlHedge* const r2y_ctrl_hedge );
static void imR2ySetRdmaValMediumEdgeCtrl( kuint16 pipeNo, const R2yCtrlMedge* const r2y_ctrl_medge );
static void imR2ySetRdmaValLowEdgeCtrl( kuint16 pipeNo, const R2yCtrlLedge* const r2y_ctrl_ledge );
static void imR2ySetRdmaValEdgeDotNoiseCtrl( kuint16 pipeNo, const CtrlEdgeDotNoise* const r2y_ctrl_edge_dot );
static void imR2ySetRdmaValEdgeBlendCtrl( kuint16 pipeNo, const CtrlEdgeBlend* const r2y_ctrl_edge_blend );

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

static void imR2ySetHighEdgeSclTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EHSAEN = enable;
}

static void imR2ySetHighEdgeStepTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EHTAEN = enable;
}

static void imR2ySetMediumEdgeSclTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EMSAEN = enable;
}

static void imR2ySetMediumEdgeStepTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EMTAEN = enable;
}

static void imR2ySetlowEdgeSclTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.ELSAEN = enable;
}

static void imR2ySetlowEdgeStepTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.ELTAEN = enable;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValEenrCtrl( kuint16 pipeNo, const CtrlEdgeCmn* const r2y_ctrl_edge_cmn )
{
	CtrlRdmaEenrVal eenr_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EENR_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	eenr_ctrl.EGSMCTL.bit.EGSMT    = r2y_ctrl_edge_cmn->reductionMode;
	eenr_ctrl.EGSMTT.bit.EGSMTTH   = r2y_ctrl_edge_cmn->threshold;
	eenr_ctrl.EGSMTT.bit.EGSMTTXGA = r2y_ctrl_edge_cmn->textureGain;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEenrVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&eenr_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValHighEdgeCtrl( kuint16 pipeNo, const R2yCtrlHedge* const r2y_ctrl_hedge )
{
	CtrlRdmaEghwVal eghw_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGHW_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	eghw_ctrl.EGHWCTL.bit.EGHWEN     = r2y_ctrl_hedge->edgeEnable;
	eghw_ctrl.EGHWCTL.bit.EGHWMP     = r2y_ctrl_hedge->scaleEnable;
	eghw_ctrl.EGHWCTL.bit.EGHWTC     = r2y_ctrl_hedge->tableClipSelect;
	eghw_ctrl.EGHWCTL.bit.EGHWSCLRES = r2y_ctrl_hedge->scaleTableResol;
	eghw_ctrl.EGHWCTL.bit.EGHWSCLTBL = r2y_ctrl_hedge->scaleTableSelect;
	eghw_ctrl.EGHWCTL.bit.EGHWTCRES  = r2y_ctrl_hedge->gradationTableResol;
	eghw_ctrl.EGHWCTL.bit.EGHWTCTBL  = r2y_ctrl_hedge->gradationTableSelect;
	eghw_ctrl.EGHWCTL.bit.EGHWNRLV   = r2y_ctrl_hedge->nrLevel;

	eghw_ctrl.EGHWHPFK.bit.EGHWHPFK0 = r2y_ctrl_hedge->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK1, r2y_ctrl_hedge->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK2, r2y_ctrl_hedge->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK3, r2y_ctrl_hedge->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK4, r2y_ctrl_hedge->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( eghw_ctrl.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK5, r2y_ctrl_hedge->hpfK[5] );

	eghw_ctrl.EGHWCORPOF.bit.EGHWCORPOF_0 = r2y_ctrl_hedge->corpOffset[0];
	eghw_ctrl.EGHWCORPOF.bit.EGHWCORPOF_1 = r2y_ctrl_hedge->corpOffset[1];
	eghw_ctrl.EGHWCORPOF.bit.EGHWCORPOF_2 = r2y_ctrl_hedge->corpOffset[2];
	eghw_ctrl.EGHWCORPOF.bit.EGHWCORPOF_3 = r2y_ctrl_hedge->corpOffset[3];
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_0, r2y_ctrl_hedge->corpGain[0] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_1, r2y_ctrl_hedge->corpGain[1] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_2, r2y_ctrl_hedge->corpGain[2] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_3, r2y_ctrl_hedge->corpGain[3] );
	eghw_ctrl.EGHWCORPBD.bit.EGHWCORPBD_1 = r2y_ctrl_hedge->corpBorder[0];
	eghw_ctrl.EGHWCORPBD.bit.EGHWCORPBD_2 = r2y_ctrl_hedge->corpBorder[1];
	eghw_ctrl.EGHWCORPBD.bit.EGHWCORPBD_3 = r2y_ctrl_hedge->corpBorder[2];

	eghw_ctrl.EGHWCORMOF.bit.EGHWCORMOF_0 = r2y_ctrl_hedge->cormOffset[0];
	eghw_ctrl.EGHWCORMOF.bit.EGHWCORMOF_1 = r2y_ctrl_hedge->cormOffset[1];
	eghw_ctrl.EGHWCORMOF.bit.EGHWCORMOF_2 = r2y_ctrl_hedge->cormOffset[2];
	eghw_ctrl.EGHWCORMOF.bit.EGHWCORMOF_3 = r2y_ctrl_hedge->cormOffset[3];
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_0, r2y_ctrl_hedge->cormGain[0] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_1, r2y_ctrl_hedge->cormGain[1] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_2, r2y_ctrl_hedge->cormGain[2] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_3, r2y_ctrl_hedge->cormGain[3] );
	eghw_ctrl.EGHWCORMBD.bit.EGHWCORMBD_1 = r2y_ctrl_hedge->cormBorder[0];
	eghw_ctrl.EGHWCORMBD.bit.EGHWCORMBD_2 = r2y_ctrl_hedge->cormBorder[1];
	eghw_ctrl.EGHWCORMBD.bit.EGHWCORMBD_3 = r2y_ctrl_hedge->cormBorder[2];

	eghw_ctrl.EGHWSCLSUP.bit.EGHWSCLSUP = r2y_ctrl_hedge->supScl;

	eghw_ctrl.EGHWCLPPOF.bit.EGHWCLPPOF_0 = r2y_ctrl_hedge->levelClipPOffset[0];
	eghw_ctrl.EGHWCLPPOF.bit.EGHWCLPPOF_1 = r2y_ctrl_hedge->levelClipPOffset[1];
	eghw_ctrl.EGHWCLPPOF.bit.EGHWCLPPOF_2 = r2y_ctrl_hedge->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_0, r2y_ctrl_hedge->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_1, r2y_ctrl_hedge->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_2, r2y_ctrl_hedge->levelClipPGain[2] );
	eghw_ctrl.EGHWCLPPBD.bit.EGHWCLPPBD_1 = r2y_ctrl_hedge->levelClipPBorder[0];
	eghw_ctrl.EGHWCLPPBD.bit.EGHWCLPPBD_2 = r2y_ctrl_hedge->levelClipPBorder[1];

	eghw_ctrl.EGHWCLPMOF.bit.EGHWCLPMOF_0 = r2y_ctrl_hedge->levelClipMOffset[0];
	eghw_ctrl.EGHWCLPMOF.bit.EGHWCLPMOF_1 = r2y_ctrl_hedge->levelClipMOffset[1];
	eghw_ctrl.EGHWCLPMOF.bit.EGHWCLPMOF_2 = r2y_ctrl_hedge->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_0, r2y_ctrl_hedge->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_1, r2y_ctrl_hedge->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( eghw_ctrl.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_2, r2y_ctrl_hedge->levelClipMGain[2] );
	eghw_ctrl.EGHWCLPMBD.bit.EGHWCLPMBD_1 = r2y_ctrl_hedge->levelClipMBorder[0];
	eghw_ctrl.EGHWCLPMBD.bit.EGHWCLPMBD_2 = r2y_ctrl_hedge->levelClipMBorder[1];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEghwVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&eghw_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValMediumEdgeCtrl( kuint16 pipeNo, const R2yCtrlMedge* const r2y_ctrl_medge )
{
	CtrlRdmaEgmwVal egmw_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGMW_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	egmw_ctrl.EGMWCTL.bit.EGMWEN     = r2y_ctrl_medge->edgeEnable;
	egmw_ctrl.EGMWCTL.bit.EGMWMP     = r2y_ctrl_medge->scaleEnable;
	egmw_ctrl.EGMWCTL.bit.EGMWTC     = r2y_ctrl_medge->tableClipSelect;
	egmw_ctrl.EGMWCTL.bit.EGMWSCLRES = r2y_ctrl_medge->scaleTableResol;
	egmw_ctrl.EGMWCTL.bit.EGMWSCLTBL = r2y_ctrl_medge->scaleTableSelect;
	egmw_ctrl.EGMWCTL.bit.EGMWTCRES  = r2y_ctrl_medge->gradationTableResol;
	egmw_ctrl.EGMWCTL.bit.EGMWTCTBL  = r2y_ctrl_medge->gradationTableSelect;
	egmw_ctrl.EGMWCTL.bit.EGMWNRLV   = r2y_ctrl_medge->nrLevel;

	egmw_ctrl.EGMWHPFK.bit.EGMWHPFK0 = r2y_ctrl_medge->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK1, r2y_ctrl_medge->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK2, r2y_ctrl_medge->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK3, r2y_ctrl_medge->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK4, r2y_ctrl_medge->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( egmw_ctrl.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK5, r2y_ctrl_medge->hpfK[5] );

	egmw_ctrl.EGMWCORPOF.bit.EGMWCORPOF_0 = r2y_ctrl_medge->corpOffset[0];
	egmw_ctrl.EGMWCORPOF.bit.EGMWCORPOF_1 = r2y_ctrl_medge->corpOffset[1];
	egmw_ctrl.EGMWCORPOF.bit.EGMWCORPOF_2 = r2y_ctrl_medge->corpOffset[2];
	egmw_ctrl.EGMWCORPOF.bit.EGMWCORPOF_3 = r2y_ctrl_medge->corpOffset[3];
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_0, r2y_ctrl_medge->corpGain[0] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_1, r2y_ctrl_medge->corpGain[1] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_2, r2y_ctrl_medge->corpGain[2] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_3, r2y_ctrl_medge->corpGain[3] );
	egmw_ctrl.EGMWCORPBD.bit.EGMWCORPBD_1 = r2y_ctrl_medge->corpBorder[0];
	egmw_ctrl.EGMWCORPBD.bit.EGMWCORPBD_2 = r2y_ctrl_medge->corpBorder[1];
	egmw_ctrl.EGMWCORPBD.bit.EGMWCORPBD_3 = r2y_ctrl_medge->corpBorder[2];

	egmw_ctrl.EGMWCORMOF.bit.EGMWCORMOF_0 = r2y_ctrl_medge->cormOffset[0];
	egmw_ctrl.EGMWCORMOF.bit.EGMWCORMOF_1 = r2y_ctrl_medge->cormOffset[1];
	egmw_ctrl.EGMWCORMOF.bit.EGMWCORMOF_2 = r2y_ctrl_medge->cormOffset[2];
	egmw_ctrl.EGMWCORMOF.bit.EGMWCORMOF_3 = r2y_ctrl_medge->cormOffset[3];
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_0, r2y_ctrl_medge->cormGain[0] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_1, r2y_ctrl_medge->cormGain[1] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_2, r2y_ctrl_medge->cormGain[2] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_3, r2y_ctrl_medge->cormGain[3] );
	egmw_ctrl.EGMWCORMBD.bit.EGMWCORMBD_1 = r2y_ctrl_medge->cormBorder[0];
	egmw_ctrl.EGMWCORMBD.bit.EGMWCORMBD_2 = r2y_ctrl_medge->cormBorder[1];
	egmw_ctrl.EGMWCORMBD.bit.EGMWCORMBD_3 = r2y_ctrl_medge->cormBorder[2];

	egmw_ctrl.EGMWSCLSUP.bit.EGMWSCLSUP = r2y_ctrl_medge->supScl;

	egmw_ctrl.EGMWCLPPOF.bit.EGMWCLPPOF_0 = r2y_ctrl_medge->levelClipPOffset[0];
	egmw_ctrl.EGMWCLPPOF.bit.EGMWCLPPOF_1 = r2y_ctrl_medge->levelClipPOffset[1];
	egmw_ctrl.EGMWCLPPOF.bit.EGMWCLPPOF_2 = r2y_ctrl_medge->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_0, r2y_ctrl_medge->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_1, r2y_ctrl_medge->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_2, r2y_ctrl_medge->levelClipPGain[2] );
	egmw_ctrl.EGMWCLPPBD.bit.EGMWCLPPBD_1 = r2y_ctrl_medge->levelClipPBorder[0];
	egmw_ctrl.EGMWCLPPBD.bit.EGMWCLPPBD_2 = r2y_ctrl_medge->levelClipPBorder[1];

	egmw_ctrl.EGMWCLPMOF.bit.EGMWCLPMOF_0 = r2y_ctrl_medge->levelClipMOffset[0];
	egmw_ctrl.EGMWCLPMOF.bit.EGMWCLPMOF_1 = r2y_ctrl_medge->levelClipMOffset[1];
	egmw_ctrl.EGMWCLPMOF.bit.EGMWCLPMOF_2 = r2y_ctrl_medge->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_0, r2y_ctrl_medge->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_1, r2y_ctrl_medge->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( egmw_ctrl.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_2, r2y_ctrl_medge->levelClipMGain[2] );
	egmw_ctrl.EGMWCLPMBD.bit.EGMWCLPMBD_1 = r2y_ctrl_medge->levelClipMBorder[0];
	egmw_ctrl.EGMWCLPMBD.bit.EGMWCLPMBD_2 = r2y_ctrl_medge->levelClipMBorder[1];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEgmwVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&egmw_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValLowEdgeCtrl( kuint16 pipeNo, const R2yCtrlLedge* const r2y_ctrl_ledge )
{
	CtrlRdmaEglwVal eglw_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGLW_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	eglw_ctrl.EGLWCTL.bit.EGLWEN     = r2y_ctrl_ledge->edgeEnable;
	eglw_ctrl.EGLWCTL.bit.EGLWMP     = r2y_ctrl_ledge->scaleEnable;
	eglw_ctrl.EGLWCTL.bit.EGLWTC     = r2y_ctrl_ledge->tableClipSelect;
	eglw_ctrl.EGLWCTL.bit.EGLWSCLRES = r2y_ctrl_ledge->scaleTableResol;
	eglw_ctrl.EGLWCTL.bit.EGLWSCLTBL = r2y_ctrl_ledge->scaleTableSelect;
	eglw_ctrl.EGLWCTL.bit.EGLWTCRES  = r2y_ctrl_ledge->gradationTableResol;
	eglw_ctrl.EGLWCTL.bit.EGLWTCTBL  = r2y_ctrl_ledge->gradationTableSelect;

	eglw_ctrl.EGLWHPFK.bit.EGLWHPFK0 = r2y_ctrl_ledge->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK1, r2y_ctrl_ledge->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK2, r2y_ctrl_ledge->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK3, r2y_ctrl_ledge->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK4, r2y_ctrl_ledge->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK5, r2y_ctrl_ledge->hpfK[5] );
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK6, r2y_ctrl_ledge->hpfK[6] );
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK7, r2y_ctrl_ledge->hpfK[7] );
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK8, r2y_ctrl_ledge->hpfK[8] );
	imR2yUtils_SET_REG_SIGNED_A( eglw_ctrl.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK9, r2y_ctrl_ledge->hpfK[9] );

	eglw_ctrl.EGLWCORPOF.bit.EGLWCORPOF_0 = r2y_ctrl_ledge->corpOffset[0];
	eglw_ctrl.EGLWCORPOF.bit.EGLWCORPOF_1 = r2y_ctrl_ledge->corpOffset[1];
	eglw_ctrl.EGLWCORPOF.bit.EGLWCORPOF_2 = r2y_ctrl_ledge->corpOffset[2];
	eglw_ctrl.EGLWCORPOF.bit.EGLWCORPOF_3 = r2y_ctrl_ledge->corpOffset[3];
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_0, r2y_ctrl_ledge->corpGain[0] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_1, r2y_ctrl_ledge->corpGain[1] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_2, r2y_ctrl_ledge->corpGain[2] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_3, r2y_ctrl_ledge->corpGain[3] );
	eglw_ctrl.EGLWCORPBD.bit.EGLWCORPBD_1 = r2y_ctrl_ledge->corpBorder[0];
	eglw_ctrl.EGLWCORPBD.bit.EGLWCORPBD_2 = r2y_ctrl_ledge->corpBorder[1];
	eglw_ctrl.EGLWCORPBD.bit.EGLWCORPBD_3 = r2y_ctrl_ledge->corpBorder[2];

	eglw_ctrl.EGLWCORMOF.bit.EGLWCORMOF_0 = r2y_ctrl_ledge->cormOffset[0];
	eglw_ctrl.EGLWCORMOF.bit.EGLWCORMOF_1 = r2y_ctrl_ledge->cormOffset[1];
	eglw_ctrl.EGLWCORMOF.bit.EGLWCORMOF_2 = r2y_ctrl_ledge->cormOffset[2];
	eglw_ctrl.EGLWCORMOF.bit.EGLWCORMOF_3 = r2y_ctrl_ledge->cormOffset[3];
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_0, r2y_ctrl_ledge->cormGain[0] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_1, r2y_ctrl_ledge->cormGain[1] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_2, r2y_ctrl_ledge->cormGain[2] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_3, r2y_ctrl_ledge->cormGain[3] );
	eglw_ctrl.EGLWCORMBD.bit.EGLWCORMBD_1 = r2y_ctrl_ledge->cormBorder[0];
	eglw_ctrl.EGLWCORMBD.bit.EGLWCORMBD_2 = r2y_ctrl_ledge->cormBorder[1];
	eglw_ctrl.EGLWCORMBD.bit.EGLWCORMBD_3 = r2y_ctrl_ledge->cormBorder[2];

	eglw_ctrl.EGLWSCLSUP.bit.EGLWSCLSUP = r2y_ctrl_ledge->supScl;

	eglw_ctrl.EGLWCLPPOF.bit.EGLWCLPPOF_0 = r2y_ctrl_ledge->levelClipPOffset[0];
	eglw_ctrl.EGLWCLPPOF.bit.EGLWCLPPOF_1 = r2y_ctrl_ledge->levelClipPOffset[1];
	eglw_ctrl.EGLWCLPPOF.bit.EGLWCLPPOF_2 = r2y_ctrl_ledge->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_0, r2y_ctrl_ledge->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_1, r2y_ctrl_ledge->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_2, r2y_ctrl_ledge->levelClipPGain[2] );
	eglw_ctrl.EGLWCLPPBD.bit.EGLWCLPPBD_1 = r2y_ctrl_ledge->levelClipPBorder[0];
	eglw_ctrl.EGLWCLPPBD.bit.EGLWCLPPBD_2 = r2y_ctrl_ledge->levelClipPBorder[1];

	eglw_ctrl.EGLWCLPMOF.bit.EGLWCLPMOF_0 = r2y_ctrl_ledge->levelClipMOffset[0];
	eglw_ctrl.EGLWCLPMOF.bit.EGLWCLPMOF_1 = r2y_ctrl_ledge->levelClipMOffset[1];
	eglw_ctrl.EGLWCLPMOF.bit.EGLWCLPMOF_2 = r2y_ctrl_ledge->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_0, r2y_ctrl_ledge->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_1, r2y_ctrl_ledge->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( eglw_ctrl.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_2, r2y_ctrl_ledge->levelClipMGain[2] );
	eglw_ctrl.EGLWCLPMBD.bit.EGLWCLPMBD_1 = r2y_ctrl_ledge->levelClipMBorder[0];
	eglw_ctrl.EGLWCLPMBD.bit.EGLWCLPMBD_2 = r2y_ctrl_ledge->levelClipMBorder[1];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEglwVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&eglw_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValEdgeDotNoiseCtrl( kuint16 pipeNo, const CtrlEdgeDotNoise* const r2y_ctrl_edge_dot )
{
	CtrlRdmaEgdtVal egdt_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGDT_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	egdt_ctrl.EGDTCTL.bit.EGDTHW     = r2y_ctrl_edge_dot->hfEnable;
	egdt_ctrl.EGDTCTL.bit.EGDTMW     = r2y_ctrl_edge_dot->mfEnable;
	egdt_ctrl.EGDTHWTH.bit.EGDTHWTHP = r2y_ctrl_edge_dot->hfPThreshold;
	egdt_ctrl.EGDTHWTH.bit.EGDTHWTHM = r2y_ctrl_edge_dot->hfMThreshold;
	egdt_ctrl.EGDTHWK.bit.EGDTHWKP   = r2y_ctrl_edge_dot->hfPCoef;
	egdt_ctrl.EGDTHWK.bit.EGDTHWKM   = r2y_ctrl_edge_dot->hfMCoef;
	egdt_ctrl.EGDTMWTH.bit.EGDTMWTHP = r2y_ctrl_edge_dot->mfPThreshold;
	egdt_ctrl.EGDTMWTH.bit.EGDTMWTHM = r2y_ctrl_edge_dot->mfMThreshold;
	egdt_ctrl.EGDTMWK.bit.EGDTMWKP   = r2y_ctrl_edge_dot->mfPCoef;
	egdt_ctrl.EGDTMWK.bit.EGDTMWKM   = r2y_ctrl_edge_dot->mfMCoef;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEgdtVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&egdt_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValEdgeBlendCtrl( kuint16 pipeNo, const CtrlEdgeBlend* const r2y_ctrl_edge_blend )
{
	CtrlRdmaEgcmpVal egcmp_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGCMP_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	egcmp_ctrl.EGCMPCTL.bit.EGCMPS = r2y_ctrl_edge_blend->blendType;

	egcmp_ctrl.EGCMPBD.bit.EGCMPBD_1 = r2y_ctrl_edge_blend->border[0];
	egcmp_ctrl.EGCMPBD.bit.EGCMPBD_2 = r2y_ctrl_edge_blend->border[1];
	egcmp_ctrl.EGCMPBD.bit.EGCMPBD_3 = r2y_ctrl_edge_blend->border[2];

	egcmp_ctrl.EGCMPALPOF.bit.EGCMPALPOF_0 = r2y_ctrl_edge_blend->alphaOffset[0];
	egcmp_ctrl.EGCMPALPOF.bit.EGCMPALPOF_1 = r2y_ctrl_edge_blend->alphaOffset[1];
	egcmp_ctrl.EGCMPALPOF.bit.EGCMPALPOF_2 = r2y_ctrl_edge_blend->alphaOffset[2];
	egcmp_ctrl.EGCMPALPOF.bit.EGCMPALPOF_3 = r2y_ctrl_edge_blend->alphaOffset[3];
	imR2yUtils_SET_REG_SIGNED_A( egcmp_ctrl.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_0, r2y_ctrl_edge_blend->alphaGain[0] );
	imR2yUtils_SET_REG_SIGNED_A( egcmp_ctrl.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_1, r2y_ctrl_edge_blend->alphaGain[1] );
	imR2yUtils_SET_REG_SIGNED_A( egcmp_ctrl.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_2, r2y_ctrl_edge_blend->alphaGain[2] );
	imR2yUtils_SET_REG_SIGNED_A( egcmp_ctrl.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_3, r2y_ctrl_edge_blend->alphaGain[3] );

	egcmp_ctrl.EGCMPBTAOF.bit.EGCMPBTAOF_0 = r2y_ctrl_edge_blend->betaOffset[0];
	egcmp_ctrl.EGCMPBTAOF.bit.EGCMPBTAOF_1 = r2y_ctrl_edge_blend->betaOffset[1];
	egcmp_ctrl.EGCMPBTAOF.bit.EGCMPBTAOF_2 = r2y_ctrl_edge_blend->betaOffset[2];
	egcmp_ctrl.EGCMPBTAOF.bit.EGCMPBTAOF_3 = r2y_ctrl_edge_blend->betaOffset[3];
	imR2yUtils_SET_REG_SIGNED_A( egcmp_ctrl.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_0, r2y_ctrl_edge_blend->betaGain[0] );
	imR2yUtils_SET_REG_SIGNED_A( egcmp_ctrl.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_1, r2y_ctrl_edge_blend->betaGain[1] );
	imR2yUtils_SET_REG_SIGNED_A( egcmp_ctrl.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_2, r2y_ctrl_edge_blend->betaGain[2] );
	imR2yUtils_SET_REG_SIGNED_A( egcmp_ctrl.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_3, r2y_ctrl_edge_blend->betaGain[3] );

	egcmp_ctrl.EGCMPCLP.bit.EGCMPCLPP = r2y_ctrl_edge_blend->levelClipP;
	egcmp_ctrl.EGCMPCLP.bit.EGCMPCLPM = r2y_ctrl_edge_blend->levelClipM;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEgcmpVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&egcmp_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*PUBLIC
*/
/* High/Medium frequency edge enhancement common control
 */
INT32 im_r2y_edge_noise_reduction(ImR2yEdge *self, kuint16 pipeNo, const CtrlEdgeCmn* const r2y_ctrl_edge_cmn )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_edge_cmn == NULL) {
		Ddim_Assertion(("im_r2y_edge_noise_reduction error. r2y_ctrl_edge_cmn = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_noise_reduction error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEenrCtrl( pipeNo, r2y_ctrl_edge_cmn );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGSM.EGSMCTL.bit.EGSMT    = r2y_ctrl_edge_cmn->reductionMode;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGSM.EGSMTT.bit.EGSMTTH   = r2y_ctrl_edge_cmn->threshold;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGSM.EGSMTT.bit.EGSMTTXGA = r2y_ctrl_edge_cmn->textureGain;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* High frequency Edge emphasis control
 */
INT32 im_r2y_edge_high_edge(ImR2yEdge *self, kuint16 pipeNo, const R2yCtrlHedge* const r2y_ctrl_hedge )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_hedge == NULL) {
		Ddim_Assertion(("im_r2y_edge_high_edge error. r2y_ctrl_hedge = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_high_edge error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValHighEdgeCtrl( pipeNo, r2y_ctrl_hedge );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EGHWEN     = r2y_ctrl_hedge->edgeEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EGHWMP     = r2y_ctrl_hedge->scaleEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EGHWTC     = r2y_ctrl_hedge->tableClipSelect;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EGHWSCLRES = r2y_ctrl_hedge->scaleTableResol;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EGHWSCLTBL = r2y_ctrl_hedge->scaleTableSelect;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EGHWTCRES  = r2y_ctrl_hedge->gradationTableResol;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EGHWTCTBL  = r2y_ctrl_hedge->gradationTableSelect;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCTL.bit.EGHWNRLV   = r2y_ctrl_hedge->nrLevel;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK0 = r2y_ctrl_hedge->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK1, r2y_ctrl_hedge->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK2, r2y_ctrl_hedge->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK3, r2y_ctrl_hedge->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK4, r2y_ctrl_hedge->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWHPFK, union io_r2y_eghwhpfk, EGHWHPFK5, r2y_ctrl_hedge->hpfK[5] );

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_0 = r2y_ctrl_hedge->corpOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_1 = r2y_ctrl_hedge->corpOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_2 = r2y_ctrl_hedge->corpOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_3 = r2y_ctrl_hedge->corpOffset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_0, r2y_ctrl_hedge->corpGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_1, r2y_ctrl_hedge->corpGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_2, r2y_ctrl_hedge->corpGain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPGA, union io_r2y_eghwcorpga, EGHWCORPGA_3, r2y_ctrl_hedge->corpGain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_1 = r2y_ctrl_hedge->corpBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_2 = r2y_ctrl_hedge->corpBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_3 = r2y_ctrl_hedge->corpBorder[2];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_0 = r2y_ctrl_hedge->cormOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_1 = r2y_ctrl_hedge->cormOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_2 = r2y_ctrl_hedge->cormOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_3 = r2y_ctrl_hedge->cormOffset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_0, r2y_ctrl_hedge->cormGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_1, r2y_ctrl_hedge->cormGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_2, r2y_ctrl_hedge->cormGain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMGA, union io_r2y_eghwcormga, EGHWCORMGA_3, r2y_ctrl_hedge->cormGain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_1 = r2y_ctrl_hedge->cormBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_2 = r2y_ctrl_hedge->cormBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_3 = r2y_ctrl_hedge->cormBorder[2];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWSCLSUP.bit.EGHWSCLSUP = r2y_ctrl_hedge->supScl;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_0 = r2y_ctrl_hedge->levelClipPOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_1 = r2y_ctrl_hedge->levelClipPOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_2 = r2y_ctrl_hedge->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_0, r2y_ctrl_hedge->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_1, r2y_ctrl_hedge->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPPGA, union io_r2y_eghwclppga, EGHWCLPPGA_2, r2y_ctrl_hedge->levelClipPGain[2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPPBD.bit.EGHWCLPPBD_1 = r2y_ctrl_hedge->levelClipPBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPPBD.bit.EGHWCLPPBD_2 = r2y_ctrl_hedge->levelClipPBorder[1];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_0 = r2y_ctrl_hedge->levelClipMOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_1 = r2y_ctrl_hedge->levelClipMOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_2 = r2y_ctrl_hedge->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_0, r2y_ctrl_hedge->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_1, r2y_ctrl_hedge->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPMGA, union io_r2y_eghwclpmga, EGHWCLPMGA_2, r2y_ctrl_hedge->levelClipMGain[2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPMBD.bit.EGHWCLPMBD_1 = r2y_ctrl_hedge->levelClipMBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGHW.EGHWCLPMBD.bit.EGHWCLPMBD_2 = r2y_ctrl_hedge->levelClipMBorder[1];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set High Edge scale table access enable
 */
INT32 im_r2y_edge_set_high_edge_scl_tbl_access_enable( ImR2yEdge *self,kuint16 pipeNo, kuint16 scl_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_high_edge_scl_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_high_edge_scl_tbl_accen_ctrl,
									 scl_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_edge_set_high_edge_scl_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set High Edge step table access enable
 */
INT32 im_r2y_edge_set_high_edge_step_tbl_access_enable(ImR2yEdge *self, kuint16 pipeNo, kuint16 step_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_high_edge_step_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_high_edge_step_tbl_accen_ctrl,
									 step_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_edge_set_high_edge_step_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Medium frequency Edge emphasis control
 */
INT32 im_r2y_edge_medium_edge(ImR2yEdge *self, kuint16 pipeNo, const R2yCtrlMedge* const r2y_ctrl_medge )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_medge == NULL) {
		Ddim_Assertion(("im_r2y_edge_medium_edge error. r2y_ctrl_medge = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_medium_edge error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValMediumEdgeCtrl( pipeNo, r2y_ctrl_medge );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EGMWEN     = r2y_ctrl_medge->edgeEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EGMWMP     = r2y_ctrl_medge->scaleEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EGMWTC     = r2y_ctrl_medge->tableClipSelect;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EGMWSCLRES = r2y_ctrl_medge->scaleTableResol;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EGMWSCLTBL = r2y_ctrl_medge->scaleTableSelect;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EGMWTCRES  = r2y_ctrl_medge->gradationTableResol;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EGMWTCTBL  = r2y_ctrl_medge->gradationTableSelect;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCTL.bit.EGMWNRLV   = r2y_ctrl_medge->nrLevel;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK0 = r2y_ctrl_medge->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK1, r2y_ctrl_medge->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK2, r2y_ctrl_medge->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK3, r2y_ctrl_medge->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK4, r2y_ctrl_medge->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWHPFK, union io_r2y_egmwhpfk, EGMWHPFK5, r2y_ctrl_medge->hpfK[5] );

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_0 = r2y_ctrl_medge->corpOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_1 = r2y_ctrl_medge->corpOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_2 = r2y_ctrl_medge->corpOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_3 = r2y_ctrl_medge->corpOffset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_0, r2y_ctrl_medge->corpGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_1, r2y_ctrl_medge->corpGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_2, r2y_ctrl_medge->corpGain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPGA, union io_r2y_egmwcorpga, EGMWCORPGA_3, r2y_ctrl_medge->corpGain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_1 = r2y_ctrl_medge->corpBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_2 = r2y_ctrl_medge->corpBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_3 = r2y_ctrl_medge->corpBorder[2];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_0 = r2y_ctrl_medge->cormOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_1 = r2y_ctrl_medge->cormOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_2 = r2y_ctrl_medge->cormOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_3 = r2y_ctrl_medge->cormOffset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_0, r2y_ctrl_medge->cormGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_1, r2y_ctrl_medge->cormGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_2, r2y_ctrl_medge->cormGain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMGA, union io_r2y_egmwcormga, EGMWCORMGA_3, r2y_ctrl_medge->cormGain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_1 = r2y_ctrl_medge->cormBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_2 = r2y_ctrl_medge->cormBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_3 = r2y_ctrl_medge->cormBorder[2];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWSCLSUP.bit.EGMWSCLSUP = r2y_ctrl_medge->supScl;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_0 = r2y_ctrl_medge->levelClipPOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_1 = r2y_ctrl_medge->levelClipPOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_2 = r2y_ctrl_medge->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_0, r2y_ctrl_medge->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_1, r2y_ctrl_medge->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPPGA, union io_r2y_egmwclppga, EGMWCLPPGA_2, r2y_ctrl_medge->levelClipPGain[2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPPBD.bit.EGMWCLPPBD_1 = r2y_ctrl_medge->levelClipPBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPPBD.bit.EGMWCLPPBD_2 = r2y_ctrl_medge->levelClipPBorder[1];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_0 = r2y_ctrl_medge->levelClipMOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_1 = r2y_ctrl_medge->levelClipMOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_2 = r2y_ctrl_medge->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_0, r2y_ctrl_medge->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_1, r2y_ctrl_medge->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPMGA, union io_r2y_egmwclpmga, EGMWCLPMGA_2, r2y_ctrl_medge->levelClipMGain[2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPMBD.bit.EGMWCLPMBD_1 = r2y_ctrl_medge->levelClipMBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGMW.EGMWCLPMBD.bit.EGMWCLPMBD_2 = r2y_ctrl_medge->levelClipMBorder[1];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Medium Edge scale table access enable
 */
INT32 im_r2y_edge_set_medium_edge_scl_tbl_access_enable(ImR2yEdge *self, kuint16 pipeNo, kuint16 scl_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_medium_edge_scl_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_medium_edge_scl_tbl_accen_ctrl,
									 scl_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_edge_set_medium_edge_scl_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set Medium Edge step table access enable
 */
INT32 im_r2y_edge_set_medium_edge_step_tbl_access_enable(ImR2yEdge *self, kuint16 pipeNo, kuint16 step_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_medium_edge_step_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_medium_edge_step_tbl_accen_ctrl,
									 step_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_edge_set_medium_edge_step_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Low frequency Edge emphasis control
 */
INT32 im_r2y_edge_ctrl_low_edge(ImR2yEdge *self, kuint16 pipeNo, const R2yCtrlLedge* const r2y_ctrl_ledge )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_ledge == NULL) {
		Ddim_Assertion(("im_r2y_edge_ctrl_low_edge error. r2y_ctrl_ledge = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_ctrl_low_edge error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValLowEdgeCtrl( pipeNo, r2y_ctrl_ledge );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.EGLWEN     = r2y_ctrl_ledge->edgeEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.EGLWMP     = r2y_ctrl_ledge->scaleEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.EGLWTC     = r2y_ctrl_ledge->tableClipSelect;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.EGLWSCLRES = r2y_ctrl_ledge->scaleTableResol;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.EGLWSCLTBL = r2y_ctrl_ledge->scaleTableSelect;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.EGLWTCRES  = r2y_ctrl_ledge->gradationTableResol;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCTL.bit.EGLWTCTBL  = r2y_ctrl_ledge->gradationTableSelect;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK.bit.EGLWHPFK0 = r2y_ctrl_ledge->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK1, r2y_ctrl_ledge->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK2, r2y_ctrl_ledge->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK3, r2y_ctrl_ledge->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK4, r2y_ctrl_ledge->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK5, r2y_ctrl_ledge->hpfK[5] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK6, r2y_ctrl_ledge->hpfK[6] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK7, r2y_ctrl_ledge->hpfK[7] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK8, r2y_ctrl_ledge->hpfK[8] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWHPFK, union io_r2y_eglwhpfk, EGLWHPFK9, r2y_ctrl_ledge->hpfK[9] );

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPOF.bit.EGLWCORPOF_0 = r2y_ctrl_ledge->corpOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPOF.bit.EGLWCORPOF_1 = r2y_ctrl_ledge->corpOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPOF.bit.EGLWCORPOF_2 = r2y_ctrl_ledge->corpOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPOF.bit.EGLWCORPOF_3 = r2y_ctrl_ledge->corpOffset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_0, r2y_ctrl_ledge->corpGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_1, r2y_ctrl_ledge->corpGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_2, r2y_ctrl_ledge->corpGain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPGA, union io_r2y_eglwcorpga, EGLWCORPGA_3, r2y_ctrl_ledge->corpGain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPBD.bit.EGLWCORPBD_1 = r2y_ctrl_ledge->corpBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPBD.bit.EGLWCORPBD_2 = r2y_ctrl_ledge->corpBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORPBD.bit.EGLWCORPBD_3 = r2y_ctrl_ledge->corpBorder[2];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMOF.bit.EGLWCORMOF_0 = r2y_ctrl_ledge->cormOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMOF.bit.EGLWCORMOF_1 = r2y_ctrl_ledge->cormOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMOF.bit.EGLWCORMOF_2 = r2y_ctrl_ledge->cormOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMOF.bit.EGLWCORMOF_3 = r2y_ctrl_ledge->cormOffset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_0, r2y_ctrl_ledge->cormGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_1, r2y_ctrl_ledge->cormGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_2, r2y_ctrl_ledge->cormGain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMGA, union io_r2y_eglwcormga, EGLWCORMGA_3, r2y_ctrl_ledge->cormGain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMBD.bit.EGLWCORMBD_1 = r2y_ctrl_ledge->cormBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMBD.bit.EGLWCORMBD_2 = r2y_ctrl_ledge->cormBorder[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCORMBD.bit.EGLWCORMBD_3 = r2y_ctrl_ledge->cormBorder[2];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWSCLSUP.bit.EGLWSCLSUP = r2y_ctrl_ledge->supScl;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPPOF.bit.EGLWCLPPOF_0 = r2y_ctrl_ledge->levelClipPOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPPOF.bit.EGLWCLPPOF_1 = r2y_ctrl_ledge->levelClipPOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPPOF.bit.EGLWCLPPOF_2 = r2y_ctrl_ledge->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_0, r2y_ctrl_ledge->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_1, r2y_ctrl_ledge->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPPGA, union io_r2y_eglwclppga, EGLWCLPPGA_2, r2y_ctrl_ledge->levelClipPGain[2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPPBD.bit.EGLWCLPPBD_1 = r2y_ctrl_ledge->levelClipPBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPPBD.bit.EGLWCLPPBD_2 = r2y_ctrl_ledge->levelClipPBorder[1];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPMOF.bit.EGLWCLPMOF_0 = r2y_ctrl_ledge->levelClipMOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPMOF.bit.EGLWCLPMOF_1 = r2y_ctrl_ledge->levelClipMOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPMOF.bit.EGLWCLPMOF_2 = r2y_ctrl_ledge->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_0, r2y_ctrl_ledge->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_1, r2y_ctrl_ledge->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPMGA, union io_r2y_eglwclpmga, EGLWCLPMGA_2, r2y_ctrl_ledge->levelClipMGain[2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPMBD.bit.EGLWCLPMBD_1 = r2y_ctrl_ledge->levelClipMBorder[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGLW.EGLWCLPMBD.bit.EGLWCLPMBD_2 = r2y_ctrl_ledge->levelClipMBorder[1];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Low Edge scale table access enable
 */
INT32 im_r2y_edge_set_low_edge_scl_tbl_access_enable(ImR2yEdge *self, kuint16 pipeNo, kuint16 scl_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_low_edge_scl_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_low_edge_scl_tbl_accen_ctrl,
									 scl_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_edge_set_low_edge_scl_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set Low Edge step table access enable
 */
INT32 im_r2y_edge_set_low_edge_step_tbl_access_enable(ImR2yEdge *self, kuint16 pipeNo, kuint16 step_enable, kuint16 wait_enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_set_low_edge_step_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_low_edge_step_tbl_accen_ctrl,
									 step_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_edge_set_low_edge_step_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Is Post filter active
 */
INT32 im_r2y_edge_is_act_post_filter(ImR2yEdge *self, kuint16 pipeNo, kuint16* const active_status )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_is_act_post_filter error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	*active_status = (gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YFLAG.bit.YCFACT != 0)?(ImR2yCtrl_ENABLE_ON):(ImR2yCtrl_ENABLE_OFF);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* Edge dot noise correction control
 */
INT32 im_r2y_edge_ctrl_dot_noise(ImR2yEdge *self, kuint16 pipeNo, const CtrlEdgeDotNoise* const r2y_ctrl_edge_dot )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_edge_dot == NULL) {
		Ddim_Assertion(("im_r2y_edge_ctrl_dot_noise error. r2y_ctrl_edge_dot = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_ctrl_dot_noise error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEdgeDotNoiseCtrl( pipeNo, r2y_ctrl_edge_dot );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTCTL.bit.EGDTHW     = r2y_ctrl_edge_dot->hfEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTCTL.bit.EGDTMW     = r2y_ctrl_edge_dot->mfEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTHWTH.bit.EGDTHWTHP = r2y_ctrl_edge_dot->hfPThreshold;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTHWTH.bit.EGDTHWTHM = r2y_ctrl_edge_dot->hfMThreshold;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTHWK.bit.EGDTHWKP   = r2y_ctrl_edge_dot->hfPCoef;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTHWK.bit.EGDTHWKM   = r2y_ctrl_edge_dot->hfMCoef;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTMWTH.bit.EGDTMWTHP = r2y_ctrl_edge_dot->mfPThreshold;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTMWTH.bit.EGDTMWTHM = r2y_ctrl_edge_dot->mfMThreshold;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTMWK.bit.EGDTMWKP   = r2y_ctrl_edge_dot->mfPCoef;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGDT.EGDTMWK.bit.EGDTMWKM   = r2y_ctrl_edge_dot->mfMCoef;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Edge emphasis blend control
 */
INT32 im_r2y_edge_ctrl_blend(ImR2yEdge *self, kuint16 pipeNo, const CtrlEdgeBlend* const r2y_ctrl_edge_blend )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_edge_blend == NULL) {
		Ddim_Assertion(("im_r2y_edge_ctrl_blend error. r2y_ctrl_edge_blend = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_edge_ctrl_blend error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEdgeBlendCtrl( pipeNo, r2y_ctrl_edge_blend );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPCTL.bit.EGCMPS = r2y_ctrl_edge_blend->blendType;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBD.bit.EGCMPBD_1 = r2y_ctrl_edge_blend->border[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBD.bit.EGCMPBD_2 = r2y_ctrl_edge_blend->border[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBD.bit.EGCMPBD_3 = r2y_ctrl_edge_blend->border[2];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPALPOF.bit.EGCMPALPOF_0 = r2y_ctrl_edge_blend->alphaOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPALPOF.bit.EGCMPALPOF_1 = r2y_ctrl_edge_blend->alphaOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPALPOF.bit.EGCMPALPOF_2 = r2y_ctrl_edge_blend->alphaOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPALPOF.bit.EGCMPALPOF_3 = r2y_ctrl_edge_blend->alphaOffset[3];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_0, r2y_ctrl_edge_blend->alphaGain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_1, r2y_ctrl_edge_blend->alphaGain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_2, r2y_ctrl_edge_blend->alphaGain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPALPGA, union io_r2y_egcmpalpga, EGCMPALPGA_3, r2y_ctrl_edge_blend->alphaGain[3] );

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBTAOF.bit.EGCMPBTAOF_0 = r2y_ctrl_edge_blend->betaOffset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBTAOF.bit.EGCMPBTAOF_1 = r2y_ctrl_edge_blend->betaOffset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBTAOF.bit.EGCMPBTAOF_2 = r2y_ctrl_edge_blend->betaOffset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBTAOF.bit.EGCMPBTAOF_3 = r2y_ctrl_edge_blend->betaOffset[3];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_0, r2y_ctrl_edge_blend->betaGain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_1, r2y_ctrl_edge_blend->betaGain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_2, r2y_ctrl_edge_blend->betaGain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPBTAGA, union io_r2y_egcmpbtaga, EGCMPBTAGA_3, r2y_ctrl_edge_blend->betaGain[3] );

	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPCLP.bit.EGCMPCLPP = r2y_ctrl_edge_blend->levelClipP;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.EGCMP.EGCMPCLP.bit.EGCMPCLPM = r2y_ctrl_edge_blend->levelClipM;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

ImR2yEdge *im_r2y_edge_new(void)
{
	ImR2yEdge* self = k_object_new_with_private(IM_TYPE_R2Y_EDGE,sizeof(ImR2yEdgePrivate));
	return self;
}
