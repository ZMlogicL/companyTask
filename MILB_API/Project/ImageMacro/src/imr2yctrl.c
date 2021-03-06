/*
 * imr2yctrl.c
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
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

#include "imr2yctrl.h"
#include "imr2yutils.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yCtrl, im_r2y_ctrl);
#define IM_R2Y_CTRL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yCtrlPrivate, IM_TYPE_R2Y_CTRL))

struct _ImR2yCtrlPrivate
{
	int a;
};

/*
 * DECLS
 */
static void imR2ySetToneControlTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_tone_control_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetToneControlTblAccessEnable,
};
#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValEe1Ctrl( kuint16 pipeNo, const R2yPostResize1Param* const r2y_ctrl_post_resize );
static void imR2ySetRdmaValEe0Ctrl( kuint16 pipeNo, const R2yPostResize0Param* const r2y_ctrl_post_resize );
static void imR2ySetRdmaValToneCtrl( kuint16 pipeNo, const ImR2yCtrlTone* const r2y_ctrl_tone );
static void imR2ySetRdmaValOffsetCtrl( kuint16 pipeNo, const ImR2yCtrlOfs* const ofs );

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


static void im_r2y_ctrl_constructor(ImR2yCtrl *self)
{
	ImR2yCtrlPrivate *priv = IM_R2Y_CTRL_GET_PRIVATE(self);
}

static void im_r2y_ctrl_destructor(ImR2yCtrl *self)
{
	ImR2yCtrlPrivate *priv = IM_R2Y_CTRL_GET_PRIVATE(self);
}

static void imR2ySetToneControlTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCAEN = enable;
}


#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValEe1Ctrl( kuint16 pipeNo, const R2yPostResize1Param* const r2y_ctrl_post_resize )
{
	CtrlRdmaEe1Val ee1_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EE1_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	ee1_ctrl.EE1CTL.bit.EE1EN = r2y_ctrl_post_resize->edgeEnable;
	ee1_ctrl.EE1CTL.bit.EE1TC = r2y_ctrl_post_resize->gradation_enable;

	ee1_ctrl.EE1HPFK.bit.EE1HPFK0 = r2y_ctrl_post_resize->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK1, r2y_ctrl_post_resize->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK2, r2y_ctrl_post_resize->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK3, r2y_ctrl_post_resize->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK4, r2y_ctrl_post_resize->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK5, r2y_ctrl_post_resize->hpfK[5] );
	ee1_ctrl.EE1NRLV.bit.EE1NRLV = r2y_ctrl_post_resize->strength;

	ee1_ctrl.EE1CORPOF.bit.EE1CORPOF_0 = r2y_ctrl_post_resize->coring_p_offset[0];
	ee1_ctrl.EE1CORPOF.bit.EE1CORPOF_1 = r2y_ctrl_post_resize->coring_p_offset[1];
	ee1_ctrl.EE1CORPOF.bit.EE1CORPOF_2 = r2y_ctrl_post_resize->coring_p_offset[2];
	ee1_ctrl.EE1CORPOF.bit.EE1CORPOF_3 = r2y_ctrl_post_resize->coring_p_offset[3];
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CORPGA, union io_r2y_ee1corpga, EE1CORPGA_0, r2y_ctrl_post_resize->coring_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CORPGA, union io_r2y_ee1corpga, EE1CORPGA_1, r2y_ctrl_post_resize->coring_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CORPGA, union io_r2y_ee1corpga, EE1CORPGA_2, r2y_ctrl_post_resize->coring_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CORPGA, union io_r2y_ee1corpga, EE1CORPGA_3, r2y_ctrl_post_resize->coring_p_gain[3] );
	ee1_ctrl.EE1CORPBD.bit.EE1CORPBD_1 = r2y_ctrl_post_resize->coring_p_border[0];
	ee1_ctrl.EE1CORPBD.bit.EE1CORPBD_2 = r2y_ctrl_post_resize->coring_p_border[1];
	ee1_ctrl.EE1CORPBD.bit.EE1CORPBD_3 = r2y_ctrl_post_resize->coring_p_border[2];

	ee1_ctrl.EE1CORMOF.bit.EE1CORMOF_0 = r2y_ctrl_post_resize->coring_m_offset[0];
	ee1_ctrl.EE1CORMOF.bit.EE1CORMOF_1 = r2y_ctrl_post_resize->coring_m_offset[1];
	ee1_ctrl.EE1CORMOF.bit.EE1CORMOF_2 = r2y_ctrl_post_resize->coring_m_offset[2];
	ee1_ctrl.EE1CORMOF.bit.EE1CORMOF_3 = r2y_ctrl_post_resize->coring_m_offset[3];
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CORMGA, union io_r2y_ee1cormga, EE1CORMGA_0, r2y_ctrl_post_resize->coring_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CORMGA, union io_r2y_ee1cormga, EE1CORMGA_1, r2y_ctrl_post_resize->coring_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CORMGA, union io_r2y_ee1cormga, EE1CORMGA_2, r2y_ctrl_post_resize->coring_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CORMGA, union io_r2y_ee1cormga, EE1CORMGA_3, r2y_ctrl_post_resize->coring_m_gain[3] );
	ee1_ctrl.EE1CORMBD.bit.EE1CORMBD_1 = r2y_ctrl_post_resize->coring_m_border[0];
	ee1_ctrl.EE1CORMBD.bit.EE1CORMBD_2 = r2y_ctrl_post_resize->coring_m_border[1];
	ee1_ctrl.EE1CORMBD.bit.EE1CORMBD_3 = r2y_ctrl_post_resize->coring_m_border[2];

	ee1_ctrl.EE1SCLSUP.bit.EE1SCLSUP = r2y_ctrl_post_resize->scale_reduct_coef;

	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_0 = r2y_ctrl_post_resize->scale_p_offset[0];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_1 = r2y_ctrl_post_resize->scale_p_offset[1];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_2 = r2y_ctrl_post_resize->scale_p_offset[2];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_3 = r2y_ctrl_post_resize->scale_p_offset[3];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_4 = r2y_ctrl_post_resize->scale_p_offset[4];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_5 = r2y_ctrl_post_resize->scale_p_offset[5];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_6 = r2y_ctrl_post_resize->scale_p_offset[6];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_7 = r2y_ctrl_post_resize->scale_p_offset[7];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_8 = r2y_ctrl_post_resize->scale_p_offset[8];
	ee1_ctrl.EE1SCLPOF.bit.EE1SCLPOF_9 = r2y_ctrl_post_resize->scale_p_offset[9];
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_0, r2y_ctrl_post_resize->scale_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_1, r2y_ctrl_post_resize->scale_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_2, r2y_ctrl_post_resize->scale_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_3, r2y_ctrl_post_resize->scale_p_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_4, r2y_ctrl_post_resize->scale_p_gain[4] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_5, r2y_ctrl_post_resize->scale_p_gain[5] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_6, r2y_ctrl_post_resize->scale_p_gain[6] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_7, r2y_ctrl_post_resize->scale_p_gain[7] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_8, r2y_ctrl_post_resize->scale_p_gain[8] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_9, r2y_ctrl_post_resize->scale_p_gain[9] );
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_1 = r2y_ctrl_post_resize->scale_p_border[0];
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_2 = r2y_ctrl_post_resize->scale_p_border[1];
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_3 = r2y_ctrl_post_resize->scale_p_border[2];
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_4 = r2y_ctrl_post_resize->scale_p_border[3];
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_5 = r2y_ctrl_post_resize->scale_p_border[4];
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_6 = r2y_ctrl_post_resize->scale_p_border[5];
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_7 = r2y_ctrl_post_resize->scale_p_border[6];
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_8 = r2y_ctrl_post_resize->scale_p_border[7];
	ee1_ctrl.EE1SCLPBD.bit.EE1SCLPBD_9 = r2y_ctrl_post_resize->scale_p_border[8];

	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_0 = r2y_ctrl_post_resize->scale_m_offset[0];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_1 = r2y_ctrl_post_resize->scale_m_offset[1];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_2 = r2y_ctrl_post_resize->scale_m_offset[2];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_3 = r2y_ctrl_post_resize->scale_m_offset[3];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_4 = r2y_ctrl_post_resize->scale_m_offset[4];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_5 = r2y_ctrl_post_resize->scale_m_offset[5];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_6 = r2y_ctrl_post_resize->scale_m_offset[6];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_7 = r2y_ctrl_post_resize->scale_m_offset[7];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_8 = r2y_ctrl_post_resize->scale_m_offset[8];
	ee1_ctrl.EE1SCLMOF.bit.EE1SCLMOF_9 = r2y_ctrl_post_resize->scale_m_offset[9];
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_0, r2y_ctrl_post_resize->scale_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_1, r2y_ctrl_post_resize->scale_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_2, r2y_ctrl_post_resize->scale_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_3, r2y_ctrl_post_resize->scale_m_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_4, r2y_ctrl_post_resize->scale_m_gain[4] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_5, r2y_ctrl_post_resize->scale_m_gain[5] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_6, r2y_ctrl_post_resize->scale_m_gain[6] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_7, r2y_ctrl_post_resize->scale_m_gain[7] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_8, r2y_ctrl_post_resize->scale_m_gain[8] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_9, r2y_ctrl_post_resize->scale_m_gain[9] );
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_1 = r2y_ctrl_post_resize->scale_m_border[0];
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_2 = r2y_ctrl_post_resize->scale_m_border[1];
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_3 = r2y_ctrl_post_resize->scale_m_border[2];
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_4 = r2y_ctrl_post_resize->scale_m_border[3];
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_5 = r2y_ctrl_post_resize->scale_m_border[4];
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_6 = r2y_ctrl_post_resize->scale_m_border[5];
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_7 = r2y_ctrl_post_resize->scale_m_border[6];
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_8 = r2y_ctrl_post_resize->scale_m_border[7];
	ee1_ctrl.EE1SCLMBD.bit.EE1SCLMBD_9 = r2y_ctrl_post_resize->scale_m_border[8];

	ee1_ctrl.EE1TONPOF.bit.EE1TONPOF_0 = r2y_ctrl_post_resize->gradation_p_offset[0];
	ee1_ctrl.EE1TONPOF.bit.EE1TONPOF_1 = r2y_ctrl_post_resize->gradation_p_offset[1];
	ee1_ctrl.EE1TONPOF.bit.EE1TONPOF_2 = r2y_ctrl_post_resize->gradation_p_offset[2];
	ee1_ctrl.EE1TONPOF.bit.EE1TONPOF_3 = r2y_ctrl_post_resize->gradation_p_offset[3];
	ee1_ctrl.EE1TONPOF.bit.EE1TONPOF_4 = r2y_ctrl_post_resize->gradation_p_offset[4];
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_0, r2y_ctrl_post_resize->gradation_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_1, r2y_ctrl_post_resize->gradation_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_2, r2y_ctrl_post_resize->gradation_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_3, r2y_ctrl_post_resize->gradation_p_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_4, r2y_ctrl_post_resize->gradation_p_gain[4] );
	ee1_ctrl.EE1TONPBD.bit.EE1TONPBD_1 = r2y_ctrl_post_resize->gradation_p_border[0];
	ee1_ctrl.EE1TONPBD.bit.EE1TONPBD_2 = r2y_ctrl_post_resize->gradation_p_border[1];
	ee1_ctrl.EE1TONPBD.bit.EE1TONPBD_3 = r2y_ctrl_post_resize->gradation_p_border[2];
	ee1_ctrl.EE1TONPBD.bit.EE1TONPBD_4 = r2y_ctrl_post_resize->gradation_p_border[3];

	ee1_ctrl.EE1TONMOF.bit.EE1TONMOF_0 = r2y_ctrl_post_resize->gradation_m_offset[0];
	ee1_ctrl.EE1TONMOF.bit.EE1TONMOF_1 = r2y_ctrl_post_resize->gradation_m_offset[1];
	ee1_ctrl.EE1TONMOF.bit.EE1TONMOF_2 = r2y_ctrl_post_resize->gradation_m_offset[2];
	ee1_ctrl.EE1TONMOF.bit.EE1TONMOF_3 = r2y_ctrl_post_resize->gradation_m_offset[3];
	ee1_ctrl.EE1TONMOF.bit.EE1TONMOF_4 = r2y_ctrl_post_resize->gradation_m_offset[4];
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_0, r2y_ctrl_post_resize->gradation_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_1, r2y_ctrl_post_resize->gradation_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_2, r2y_ctrl_post_resize->gradation_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_3, r2y_ctrl_post_resize->gradation_m_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee1_ctrl.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_4, r2y_ctrl_post_resize->gradation_m_gain[4] );
	ee1_ctrl.EE1TONMBD.bit.EE1TONMBD_1 = r2y_ctrl_post_resize->gradation_m_border[0];
	ee1_ctrl.EE1TONMBD.bit.EE1TONMBD_2 = r2y_ctrl_post_resize->gradation_m_border[1];
	ee1_ctrl.EE1TONMBD.bit.EE1TONMBD_3 = r2y_ctrl_post_resize->gradation_m_border[2];
	ee1_ctrl.EE1TONMBD.bit.EE1TONMBD_4 = r2y_ctrl_post_resize->gradation_m_border[3];

	ee1_ctrl.EE1CLPPOF.bit.EE1CLPPOF_0 = r2y_ctrl_post_resize->levelClipPOffset[0];
	ee1_ctrl.EE1CLPPOF.bit.EE1CLPPOF_1 = r2y_ctrl_post_resize->levelClipPOffset[1];
	ee1_ctrl.EE1CLPPOF.bit.EE1CLPPOF_2 = r2y_ctrl_post_resize->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CLPPGA, union io_r2y_ee1clppga, EE1CLPPGA_0, r2y_ctrl_post_resize->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CLPPGA, union io_r2y_ee1clppga, EE1CLPPGA_1, r2y_ctrl_post_resize->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CLPPGA, union io_r2y_ee1clppga, EE1CLPPGA_2, r2y_ctrl_post_resize->levelClipPGain[2] );
	ee1_ctrl.EE1CLPPBD.bit.EE1CLPPBD_1 = r2y_ctrl_post_resize->levelClipPBorder[0];
	ee1_ctrl.EE1CLPPBD.bit.EE1CLPPBD_2 = r2y_ctrl_post_resize->levelClipPBorder[1];

	ee1_ctrl.EE1CLPMOF.bit.EE1CLPMOF_0 = r2y_ctrl_post_resize->levelClipMOffset[0];
	ee1_ctrl.EE1CLPMOF.bit.EE1CLPMOF_1 = r2y_ctrl_post_resize->levelClipMOffset[1];
	ee1_ctrl.EE1CLPMOF.bit.EE1CLPMOF_2 = r2y_ctrl_post_resize->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CLPMGA, union io_r2y_ee1clpmga, EE1CLPMGA_0, r2y_ctrl_post_resize->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CLPMGA, union io_r2y_ee1clpmga, EE1CLPMGA_1, r2y_ctrl_post_resize->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( ee1_ctrl.EE1CLPMGA, union io_r2y_ee1clpmga, EE1CLPMGA_2, r2y_ctrl_post_resize->levelClipMGain[2] );
	ee1_ctrl.EE1CLPMBD.bit.EE1CLPMBD_1 = r2y_ctrl_post_resize->levelClipMBorder[0];
	ee1_ctrl.EE1CLPMBD.bit.EE1CLPMBD_2 = r2y_ctrl_post_resize->levelClipMBorder[1];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEe1Val );
	rdma_ctrl.reg_data_top_addr = (kulong)&ee1_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValEe0Ctrl( kuint16 pipeNo, const R2yPostResize0Param* const r2y_ctrl_post_resize )
{
	CtrlRdmaEe0Val ee0_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EE0_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	ee0_ctrl.EE0CTL.bit.EE0EN = r2y_ctrl_post_resize->edgeEnable;
	ee0_ctrl.EE0CTL.bit.EE0TC = r2y_ctrl_post_resize->gradation_enable;

	ee0_ctrl.EE0HPFK.bit.EE0HPFK0 = r2y_ctrl_post_resize->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK1, r2y_ctrl_post_resize->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK2, r2y_ctrl_post_resize->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK3, r2y_ctrl_post_resize->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK4, r2y_ctrl_post_resize->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK5, r2y_ctrl_post_resize->hpfK[5] );
	ee0_ctrl.EE0NRLV.bit.EE0NRLV = r2y_ctrl_post_resize->strength;

	ee0_ctrl.EE0CORPOF.bit.EE0CORPOF_0 = r2y_ctrl_post_resize->coring_p_offset[0];
	ee0_ctrl.EE0CORPOF.bit.EE0CORPOF_1 = r2y_ctrl_post_resize->coring_p_offset[1];
	ee0_ctrl.EE0CORPOF.bit.EE0CORPOF_2 = r2y_ctrl_post_resize->coring_p_offset[2];
	ee0_ctrl.EE0CORPOF.bit.EE0CORPOF_3 = r2y_ctrl_post_resize->coring_p_offset[3];
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CORPGA, union io_r2y_ee0corpga, EE0CORPGA_0, r2y_ctrl_post_resize->coring_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CORPGA, union io_r2y_ee0corpga, EE0CORPGA_1, r2y_ctrl_post_resize->coring_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CORPGA, union io_r2y_ee0corpga, EE0CORPGA_2, r2y_ctrl_post_resize->coring_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CORPGA, union io_r2y_ee0corpga, EE0CORPGA_3, r2y_ctrl_post_resize->coring_p_gain[3] );
	ee0_ctrl.EE0CORPBD.bit.EE0CORPBD_1 = r2y_ctrl_post_resize->coring_p_border[0];
	ee0_ctrl.EE0CORPBD.bit.EE0CORPBD_2 = r2y_ctrl_post_resize->coring_p_border[1];
	ee0_ctrl.EE0CORPBD.bit.EE0CORPBD_3 = r2y_ctrl_post_resize->coring_p_border[2];

	ee0_ctrl.EE0CORMOF.bit.EE0CORMOF_0 = r2y_ctrl_post_resize->coring_m_offset[0];
	ee0_ctrl.EE0CORMOF.bit.EE0CORMOF_1 = r2y_ctrl_post_resize->coring_m_offset[1];
	ee0_ctrl.EE0CORMOF.bit.EE0CORMOF_2 = r2y_ctrl_post_resize->coring_m_offset[2];
	ee0_ctrl.EE0CORMOF.bit.EE0CORMOF_3 = r2y_ctrl_post_resize->coring_m_offset[3];
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CORMGA, union io_r2y_ee0cormga, EE0CORMGA_0, r2y_ctrl_post_resize->coring_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CORMGA, union io_r2y_ee0cormga, EE0CORMGA_1, r2y_ctrl_post_resize->coring_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CORMGA, union io_r2y_ee0cormga, EE0CORMGA_2, r2y_ctrl_post_resize->coring_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CORMGA, union io_r2y_ee0cormga, EE0CORMGA_3, r2y_ctrl_post_resize->coring_m_gain[3] );
	ee0_ctrl.EE0CORMBD.bit.EE0CORMBD_1 = r2y_ctrl_post_resize->coring_m_border[0];
	ee0_ctrl.EE0CORMBD.bit.EE0CORMBD_2 = r2y_ctrl_post_resize->coring_m_border[1];
	ee0_ctrl.EE0CORMBD.bit.EE0CORMBD_3 = r2y_ctrl_post_resize->coring_m_border[2];

	ee0_ctrl.EE0SCLSUP.bit.EE0SCLSUP = r2y_ctrl_post_resize->scale_reduct_coef;

	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_0 = r2y_ctrl_post_resize->scale_p_offset[0];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_1 = r2y_ctrl_post_resize->scale_p_offset[1];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_2 = r2y_ctrl_post_resize->scale_p_offset[2];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_3 = r2y_ctrl_post_resize->scale_p_offset[3];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_4 = r2y_ctrl_post_resize->scale_p_offset[4];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_5 = r2y_ctrl_post_resize->scale_p_offset[5];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_6 = r2y_ctrl_post_resize->scale_p_offset[6];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_7 = r2y_ctrl_post_resize->scale_p_offset[7];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_8 = r2y_ctrl_post_resize->scale_p_offset[8];
	ee0_ctrl.EE0SCLPOF.bit.EE0SCLPOF_9 = r2y_ctrl_post_resize->scale_p_offset[9];
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_0, r2y_ctrl_post_resize->scale_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_1, r2y_ctrl_post_resize->scale_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_2, r2y_ctrl_post_resize->scale_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_3, r2y_ctrl_post_resize->scale_p_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_4, r2y_ctrl_post_resize->scale_p_gain[4] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_5, r2y_ctrl_post_resize->scale_p_gain[5] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_6, r2y_ctrl_post_resize->scale_p_gain[6] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_7, r2y_ctrl_post_resize->scale_p_gain[7] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_8, r2y_ctrl_post_resize->scale_p_gain[8] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_9, r2y_ctrl_post_resize->scale_p_gain[9] );
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_1 = r2y_ctrl_post_resize->scale_p_border[0];
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_2 = r2y_ctrl_post_resize->scale_p_border[1];
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_3 = r2y_ctrl_post_resize->scale_p_border[2];
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_4 = r2y_ctrl_post_resize->scale_p_border[3];
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_5 = r2y_ctrl_post_resize->scale_p_border[4];
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_6 = r2y_ctrl_post_resize->scale_p_border[5];
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_7 = r2y_ctrl_post_resize->scale_p_border[6];
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_8 = r2y_ctrl_post_resize->scale_p_border[7];
	ee0_ctrl.EE0SCLPBD.bit.EE0SCLPBD_9 = r2y_ctrl_post_resize->scale_p_border[8];

	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_0 = r2y_ctrl_post_resize->scale_m_offset[0];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_1 = r2y_ctrl_post_resize->scale_m_offset[1];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_2 = r2y_ctrl_post_resize->scale_m_offset[2];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_3 = r2y_ctrl_post_resize->scale_m_offset[3];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_4 = r2y_ctrl_post_resize->scale_m_offset[4];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_5 = r2y_ctrl_post_resize->scale_m_offset[5];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_6 = r2y_ctrl_post_resize->scale_m_offset[6];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_7 = r2y_ctrl_post_resize->scale_m_offset[7];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_8 = r2y_ctrl_post_resize->scale_m_offset[8];
	ee0_ctrl.EE0SCLMOF.bit.EE0SCLMOF_9 = r2y_ctrl_post_resize->scale_m_offset[9];
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_0, r2y_ctrl_post_resize->scale_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_1, r2y_ctrl_post_resize->scale_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_2, r2y_ctrl_post_resize->scale_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_3, r2y_ctrl_post_resize->scale_m_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_4, r2y_ctrl_post_resize->scale_m_gain[4] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_5, r2y_ctrl_post_resize->scale_m_gain[5] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_6, r2y_ctrl_post_resize->scale_m_gain[6] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_7, r2y_ctrl_post_resize->scale_m_gain[7] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_8, r2y_ctrl_post_resize->scale_m_gain[8] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_9, r2y_ctrl_post_resize->scale_m_gain[9] );
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_1 = r2y_ctrl_post_resize->scale_m_border[0];
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_2 = r2y_ctrl_post_resize->scale_m_border[1];
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_3 = r2y_ctrl_post_resize->scale_m_border[2];
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_4 = r2y_ctrl_post_resize->scale_m_border[3];
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_5 = r2y_ctrl_post_resize->scale_m_border[4];
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_6 = r2y_ctrl_post_resize->scale_m_border[5];
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_7 = r2y_ctrl_post_resize->scale_m_border[6];
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_8 = r2y_ctrl_post_resize->scale_m_border[7];
	ee0_ctrl.EE0SCLMBD.bit.EE0SCLMBD_9 = r2y_ctrl_post_resize->scale_m_border[8];

	ee0_ctrl.EE0TONPOF.bit.EE0TONPOF_0 = r2y_ctrl_post_resize->gradation_p_offset[0];
	ee0_ctrl.EE0TONPOF.bit.EE0TONPOF_1 = r2y_ctrl_post_resize->gradation_p_offset[1];
	ee0_ctrl.EE0TONPOF.bit.EE0TONPOF_2 = r2y_ctrl_post_resize->gradation_p_offset[2];
	ee0_ctrl.EE0TONPOF.bit.EE0TONPOF_3 = r2y_ctrl_post_resize->gradation_p_offset[3];
	ee0_ctrl.EE0TONPOF.bit.EE0TONPOF_4 = r2y_ctrl_post_resize->gradation_p_offset[4];
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_0, r2y_ctrl_post_resize->gradation_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_1, r2y_ctrl_post_resize->gradation_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_2, r2y_ctrl_post_resize->gradation_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_3, r2y_ctrl_post_resize->gradation_p_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_4, r2y_ctrl_post_resize->gradation_p_gain[4] );
	ee0_ctrl.EE0TONPBD.bit.EE0TONPBD_1 = r2y_ctrl_post_resize->gradation_p_border[0];
	ee0_ctrl.EE0TONPBD.bit.EE0TONPBD_2 = r2y_ctrl_post_resize->gradation_p_border[1];
	ee0_ctrl.EE0TONPBD.bit.EE0TONPBD_3 = r2y_ctrl_post_resize->gradation_p_border[2];
	ee0_ctrl.EE0TONPBD.bit.EE0TONPBD_4 = r2y_ctrl_post_resize->gradation_p_border[3];

	ee0_ctrl.EE0TONMOF.bit.EE0TONMOF_0 = r2y_ctrl_post_resize->gradation_m_offset[0];
	ee0_ctrl.EE0TONMOF.bit.EE0TONMOF_1 = r2y_ctrl_post_resize->gradation_m_offset[1];
	ee0_ctrl.EE0TONMOF.bit.EE0TONMOF_2 = r2y_ctrl_post_resize->gradation_m_offset[2];
	ee0_ctrl.EE0TONMOF.bit.EE0TONMOF_3 = r2y_ctrl_post_resize->gradation_m_offset[3];
	ee0_ctrl.EE0TONMOF.bit.EE0TONMOF_4 = r2y_ctrl_post_resize->gradation_m_offset[4];
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_0, r2y_ctrl_post_resize->gradation_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_1, r2y_ctrl_post_resize->gradation_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_2, r2y_ctrl_post_resize->gradation_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_3, r2y_ctrl_post_resize->gradation_m_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( ee0_ctrl.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_4, r2y_ctrl_post_resize->gradation_m_gain[4] );
	ee0_ctrl.EE0TONMBD.bit.EE0TONMBD_1 = r2y_ctrl_post_resize->gradation_m_border[0];
	ee0_ctrl.EE0TONMBD.bit.EE0TONMBD_2 = r2y_ctrl_post_resize->gradation_m_border[1];
	ee0_ctrl.EE0TONMBD.bit.EE0TONMBD_3 = r2y_ctrl_post_resize->gradation_m_border[2];
	ee0_ctrl.EE0TONMBD.bit.EE0TONMBD_4 = r2y_ctrl_post_resize->gradation_m_border[3];

	ee0_ctrl.EE0CLPPOF.bit.EE0CLPPOF_0 = r2y_ctrl_post_resize->levelClipPOffset[0];
	ee0_ctrl.EE0CLPPOF.bit.EE0CLPPOF_1 = r2y_ctrl_post_resize->levelClipPOffset[1];
	ee0_ctrl.EE0CLPPOF.bit.EE0CLPPOF_2 = r2y_ctrl_post_resize->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CLPPGA, union io_r2y_ee0clppga, EE0CLPPGA_0, r2y_ctrl_post_resize->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CLPPGA, union io_r2y_ee0clppga, EE0CLPPGA_1, r2y_ctrl_post_resize->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CLPPGA, union io_r2y_ee0clppga, EE0CLPPGA_2, r2y_ctrl_post_resize->levelClipPGain[2] );
	ee0_ctrl.EE0CLPPBD.bit.EE0CLPPBD_1 = r2y_ctrl_post_resize->levelClipPBorder[0];
	ee0_ctrl.EE0CLPPBD.bit.EE0CLPPBD_2 = r2y_ctrl_post_resize->levelClipPBorder[1];

	ee0_ctrl.EE0CLPMOF.bit.EE0CLPMOF_0 = r2y_ctrl_post_resize->levelClipMOffset[0];
	ee0_ctrl.EE0CLPMOF.bit.EE0CLPMOF_1 = r2y_ctrl_post_resize->levelClipMOffset[1];
	ee0_ctrl.EE0CLPMOF.bit.EE0CLPMOF_2 = r2y_ctrl_post_resize->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CLPMGA, union io_r2y_ee0clpmga, EE0CLPMGA_0, r2y_ctrl_post_resize->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CLPMGA, union io_r2y_ee0clpmga, EE0CLPMGA_1, r2y_ctrl_post_resize->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( ee0_ctrl.EE0CLPMGA, union io_r2y_ee0clpmga, EE0CLPMGA_2, r2y_ctrl_post_resize->levelClipMGain[2] );
	ee0_ctrl.EE0CLPMBD.bit.EE0CLPMBD_1 = r2y_ctrl_post_resize->levelClipMBorder[0];
	ee0_ctrl.EE0CLPMBD.bit.EE0CLPMBD_2 = r2y_ctrl_post_resize->levelClipMBorder[1];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaEe0Val );
	rdma_ctrl.reg_data_top_addr = (kulong)&ee0_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValToneCtrl( kuint16 pipeNo, const ImR2yCtrlTone* const r2y_ctrl_tone )
{
	CtrlRdmaToneVal tone_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_TONE_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	tone_ctrl.TCCTL.bit.TCEN     = r2y_ctrl_tone->tone_enable;
	tone_ctrl.TCCTL.bit.TCYBEN   = r2y_ctrl_tone->tone_yb_enable;
	tone_ctrl.TCCTL.bit.TCBLEN   = r2y_ctrl_tone->table_blend_enable;
	tone_ctrl.TCCTL.bit.TCRES    = r2y_ctrl_tone->table_resol;
	tone_ctrl.TCCTL.bit.TCTBL    = r2y_ctrl_tone->table_select;
	tone_ctrl.TCCTL.bit.TCYOUT   = r2y_ctrl_tone->ytc_out;
	tone_ctrl.TCCTL.bit.TCINTBIT = r2y_ctrl_tone->int_bit;
	tone_ctrl.TCCTL.bit.TCBLND   = r2y_ctrl_tone->table_blend_ratio;

	tone_ctrl.TCYC.bit.TCYC_0_0 = r2y_ctrl_tone->yc_matrix[0];
	tone_ctrl.TCYC.bit.TCYC_0_1 = r2y_ctrl_tone->yc_matrix[1];
	tone_ctrl.TCYC.bit.TCYC_0_2 = r2y_ctrl_tone->yc_matrix[2];

	tone_ctrl.TCEP.bit.TCEP_0 = r2y_ctrl_tone->table_endp[0];
	tone_ctrl.TCEP.bit.TCEP_1 = r2y_ctrl_tone->table_endp[1];
	tone_ctrl.TCEP.bit.TCEP_2 = r2y_ctrl_tone->table_endp[2];
	tone_ctrl.TCEP.bit.TCEP_3 = r2y_ctrl_tone->table_endp[3];

	tone_ctrl.TCCLPR.bit.TCCLPRP = r2y_ctrl_tone->clipPR;
	tone_ctrl.TCCLPR.bit.TCCLPRM = r2y_ctrl_tone->clipMR;
	tone_ctrl.TCCLPG.bit.TCCLPGP = r2y_ctrl_tone->clipPG;
	tone_ctrl.TCCLPG.bit.TCCLPGM = r2y_ctrl_tone->clipMG;
	tone_ctrl.TCCLPB.bit.TCCLPBP = r2y_ctrl_tone->clipPB;
	tone_ctrl.TCCLPB.bit.TCCLPBM = r2y_ctrl_tone->clipMB;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaToneVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&tone_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValOffsetCtrl( kuint16 pipeNo, const ImR2yCtrlOfs* const ofs )
{
	CtrlRdmaOfstVal ofst_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_OFST_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	imR2yUtils_SET_REG_SIGNED_A( ofst_ctrl.OFST, union io_r2y_ofst, OFSTR, ofs->R );
	imR2yUtils_SET_REG_SIGNED_A( ofst_ctrl.OFST, union io_r2y_ofst, OFSTG, ofs->G );
	imR2yUtils_SET_REG_SIGNED_A( ofst_ctrl.OFST, union io_r2y_ofst, OFSTB, ofs->B );

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaOfstVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&ofst_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
 * PUBLIC
 */
/* Post-resize edge enhancement0 control
 */
INT32 im_r2y_ctrl_post_resize_edge0(ImR2yCtrl *self, kuint16 pipeNo, const R2yPostResize0Param* const r2y_ctrl_post_resize )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_post_resize == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl_post_resize_edge0 error. r2y_ctrl_post_resize = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl_post_resize_edge0 error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEe0Ctrl( pipeNo, r2y_ctrl_post_resize );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CTL.bit.EE0EN = r2y_ctrl_post_resize->edgeEnable;
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CTL.bit.EE0TC = r2y_ctrl_post_resize->gradation_enable;

	gImIoR2yRegPtr[pipeNo]->YYW.EE0HPFK.bit.EE0HPFK0 = r2y_ctrl_post_resize->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK1, r2y_ctrl_post_resize->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK2, r2y_ctrl_post_resize->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK3, r2y_ctrl_post_resize->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK4, r2y_ctrl_post_resize->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0HPFK, union io_r2y_ee0hpfk, EE0HPFK5, r2y_ctrl_post_resize->hpfK[5] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0NRLV.bit.EE0NRLV = r2y_ctrl_post_resize->strength;

	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPOF.bit.EE0CORPOF_0 = r2y_ctrl_post_resize->coring_p_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPOF.bit.EE0CORPOF_1 = r2y_ctrl_post_resize->coring_p_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPOF.bit.EE0CORPOF_2 = r2y_ctrl_post_resize->coring_p_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPOF.bit.EE0CORPOF_3 = r2y_ctrl_post_resize->coring_p_offset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPGA, union io_r2y_ee0corpga, EE0CORPGA_0, r2y_ctrl_post_resize->coring_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPGA, union io_r2y_ee0corpga, EE0CORPGA_1, r2y_ctrl_post_resize->coring_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPGA, union io_r2y_ee0corpga, EE0CORPGA_2, r2y_ctrl_post_resize->coring_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPGA, union io_r2y_ee0corpga, EE0CORPGA_3, r2y_ctrl_post_resize->coring_p_gain[3] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPBD.bit.EE0CORPBD_1 = r2y_ctrl_post_resize->coring_p_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPBD.bit.EE0CORPBD_2 = r2y_ctrl_post_resize->coring_p_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORPBD.bit.EE0CORPBD_3 = r2y_ctrl_post_resize->coring_p_border[2];

	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMOF.bit.EE0CORMOF_0 = r2y_ctrl_post_resize->coring_m_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMOF.bit.EE0CORMOF_1 = r2y_ctrl_post_resize->coring_m_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMOF.bit.EE0CORMOF_2 = r2y_ctrl_post_resize->coring_m_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMOF.bit.EE0CORMOF_3 = r2y_ctrl_post_resize->coring_m_offset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMGA, union io_r2y_ee0cormga, EE0CORMGA_0, r2y_ctrl_post_resize->coring_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMGA, union io_r2y_ee0cormga, EE0CORMGA_1, r2y_ctrl_post_resize->coring_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMGA, union io_r2y_ee0cormga, EE0CORMGA_2, r2y_ctrl_post_resize->coring_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMGA, union io_r2y_ee0cormga, EE0CORMGA_3, r2y_ctrl_post_resize->coring_m_gain[3] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMBD.bit.EE0CORMBD_1 = r2y_ctrl_post_resize->coring_m_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMBD.bit.EE0CORMBD_2 = r2y_ctrl_post_resize->coring_m_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CORMBD.bit.EE0CORMBD_3 = r2y_ctrl_post_resize->coring_m_border[2];

	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLSUP.bit.EE0SCLSUP = r2y_ctrl_post_resize->scale_reduct_coef;

	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_0 = r2y_ctrl_post_resize->scale_p_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_1 = r2y_ctrl_post_resize->scale_p_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_2 = r2y_ctrl_post_resize->scale_p_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_3 = r2y_ctrl_post_resize->scale_p_offset[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_4 = r2y_ctrl_post_resize->scale_p_offset[4];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_5 = r2y_ctrl_post_resize->scale_p_offset[5];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_6 = r2y_ctrl_post_resize->scale_p_offset[6];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_7 = r2y_ctrl_post_resize->scale_p_offset[7];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_8 = r2y_ctrl_post_resize->scale_p_offset[8];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPOF.bit.EE0SCLPOF_9 = r2y_ctrl_post_resize->scale_p_offset[9];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_0, r2y_ctrl_post_resize->scale_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_1, r2y_ctrl_post_resize->scale_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_2, r2y_ctrl_post_resize->scale_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_3, r2y_ctrl_post_resize->scale_p_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_4, r2y_ctrl_post_resize->scale_p_gain[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_5, r2y_ctrl_post_resize->scale_p_gain[5] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_6, r2y_ctrl_post_resize->scale_p_gain[6] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_7, r2y_ctrl_post_resize->scale_p_gain[7] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_8, r2y_ctrl_post_resize->scale_p_gain[8] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPGA, union io_r2y_ee0sclpga, EE0SCLPGA_9, r2y_ctrl_post_resize->scale_p_gain[9] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_1 = r2y_ctrl_post_resize->scale_p_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_2 = r2y_ctrl_post_resize->scale_p_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_3 = r2y_ctrl_post_resize->scale_p_border[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_4 = r2y_ctrl_post_resize->scale_p_border[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_5 = r2y_ctrl_post_resize->scale_p_border[4];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_6 = r2y_ctrl_post_resize->scale_p_border[5];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_7 = r2y_ctrl_post_resize->scale_p_border[6];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_8 = r2y_ctrl_post_resize->scale_p_border[7];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLPBD.bit.EE0SCLPBD_9 = r2y_ctrl_post_resize->scale_p_border[8];

	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_0 = r2y_ctrl_post_resize->scale_m_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_1 = r2y_ctrl_post_resize->scale_m_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_2 = r2y_ctrl_post_resize->scale_m_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_3 = r2y_ctrl_post_resize->scale_m_offset[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_4 = r2y_ctrl_post_resize->scale_m_offset[4];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_5 = r2y_ctrl_post_resize->scale_m_offset[5];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_6 = r2y_ctrl_post_resize->scale_m_offset[6];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_7 = r2y_ctrl_post_resize->scale_m_offset[7];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_8 = r2y_ctrl_post_resize->scale_m_offset[8];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMOF.bit.EE0SCLMOF_9 = r2y_ctrl_post_resize->scale_m_offset[9];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_0, r2y_ctrl_post_resize->scale_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_1, r2y_ctrl_post_resize->scale_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_2, r2y_ctrl_post_resize->scale_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_3, r2y_ctrl_post_resize->scale_m_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_4, r2y_ctrl_post_resize->scale_m_gain[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_5, r2y_ctrl_post_resize->scale_m_gain[5] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_6, r2y_ctrl_post_resize->scale_m_gain[6] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_7, r2y_ctrl_post_resize->scale_m_gain[7] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_8, r2y_ctrl_post_resize->scale_m_gain[8] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMGA, union io_r2y_ee0sclmga, EE0SCLMGA_9, r2y_ctrl_post_resize->scale_m_gain[9] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_1 = r2y_ctrl_post_resize->scale_m_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_2 = r2y_ctrl_post_resize->scale_m_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_3 = r2y_ctrl_post_resize->scale_m_border[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_4 = r2y_ctrl_post_resize->scale_m_border[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_5 = r2y_ctrl_post_resize->scale_m_border[4];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_6 = r2y_ctrl_post_resize->scale_m_border[5];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_7 = r2y_ctrl_post_resize->scale_m_border[6];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_8 = r2y_ctrl_post_resize->scale_m_border[7];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0SCLMBD.bit.EE0SCLMBD_9 = r2y_ctrl_post_resize->scale_m_border[8];

	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPOF.bit.EE0TONPOF_0 = r2y_ctrl_post_resize->gradation_p_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPOF.bit.EE0TONPOF_1 = r2y_ctrl_post_resize->gradation_p_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPOF.bit.EE0TONPOF_2 = r2y_ctrl_post_resize->gradation_p_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPOF.bit.EE0TONPOF_3 = r2y_ctrl_post_resize->gradation_p_offset[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPOF.bit.EE0TONPOF_4 = r2y_ctrl_post_resize->gradation_p_offset[4];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_0, r2y_ctrl_post_resize->gradation_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_1, r2y_ctrl_post_resize->gradation_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_2, r2y_ctrl_post_resize->gradation_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_3, r2y_ctrl_post_resize->gradation_p_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPGA, union io_r2y_ee0tonpga, EE0TONPGA_4, r2y_ctrl_post_resize->gradation_p_gain[4] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPBD.bit.EE0TONPBD_1 = r2y_ctrl_post_resize->gradation_p_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPBD.bit.EE0TONPBD_2 = r2y_ctrl_post_resize->gradation_p_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPBD.bit.EE0TONPBD_3 = r2y_ctrl_post_resize->gradation_p_border[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONPBD.bit.EE0TONPBD_4 = r2y_ctrl_post_resize->gradation_p_border[3];

	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMOF.bit.EE0TONMOF_0 = r2y_ctrl_post_resize->gradation_m_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMOF.bit.EE0TONMOF_1 = r2y_ctrl_post_resize->gradation_m_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMOF.bit.EE0TONMOF_2 = r2y_ctrl_post_resize->gradation_m_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMOF.bit.EE0TONMOF_3 = r2y_ctrl_post_resize->gradation_m_offset[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMOF.bit.EE0TONMOF_4 = r2y_ctrl_post_resize->gradation_m_offset[4];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_0, r2y_ctrl_post_resize->gradation_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_1, r2y_ctrl_post_resize->gradation_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_2, r2y_ctrl_post_resize->gradation_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_3, r2y_ctrl_post_resize->gradation_m_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMGA, union io_r2y_ee0tonmga, EE0TONMGA_4, r2y_ctrl_post_resize->gradation_m_gain[4] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMBD.bit.EE0TONMBD_1 = r2y_ctrl_post_resize->gradation_m_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMBD.bit.EE0TONMBD_2 = r2y_ctrl_post_resize->gradation_m_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMBD.bit.EE0TONMBD_3 = r2y_ctrl_post_resize->gradation_m_border[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0TONMBD.bit.EE0TONMBD_4 = r2y_ctrl_post_resize->gradation_m_border[3];

	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPPOF.bit.EE0CLPPOF_0 = r2y_ctrl_post_resize->levelClipPOffset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPPOF.bit.EE0CLPPOF_1 = r2y_ctrl_post_resize->levelClipPOffset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPPOF.bit.EE0CLPPOF_2 = r2y_ctrl_post_resize->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPPGA, union io_r2y_ee0clppga, EE0CLPPGA_0, r2y_ctrl_post_resize->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPPGA, union io_r2y_ee0clppga, EE0CLPPGA_1, r2y_ctrl_post_resize->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPPGA, union io_r2y_ee0clppga, EE0CLPPGA_2, r2y_ctrl_post_resize->levelClipPGain[2] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPPBD.bit.EE0CLPPBD_1 = r2y_ctrl_post_resize->levelClipPBorder[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPPBD.bit.EE0CLPPBD_2 = r2y_ctrl_post_resize->levelClipPBorder[1];

	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPMOF.bit.EE0CLPMOF_0 = r2y_ctrl_post_resize->levelClipMOffset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPMOF.bit.EE0CLPMOF_1 = r2y_ctrl_post_resize->levelClipMOffset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPMOF.bit.EE0CLPMOF_2 = r2y_ctrl_post_resize->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPMGA, union io_r2y_ee0clpmga, EE0CLPMGA_0, r2y_ctrl_post_resize->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPMGA, union io_r2y_ee0clpmga, EE0CLPMGA_1, r2y_ctrl_post_resize->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPMGA, union io_r2y_ee0clpmga, EE0CLPMGA_2, r2y_ctrl_post_resize->levelClipMGain[2] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPMBD.bit.EE0CLPMBD_1 = r2y_ctrl_post_resize->levelClipMBorder[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE0CLPMBD.bit.EE0CLPMBD_2 = r2y_ctrl_post_resize->levelClipMBorder[1];

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Post-resize edge enhancement1 control
 */
INT32 im_r2y_ctrl_post_resize_edge1(ImR2yCtrl *self, kuint16 pipeNo, const R2yPostResize1Param* const r2y_ctrl_post_resize )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_post_resize == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl_post_resize_edge1 error. r2y_ctrl_post_resize = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl_post_resize_edge1 error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValEe1Ctrl( pipeNo, r2y_ctrl_post_resize );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CTL.bit.EE1EN = r2y_ctrl_post_resize->edgeEnable;
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CTL.bit.EE1TC = r2y_ctrl_post_resize->gradation_enable;

	gImIoR2yRegPtr[pipeNo]->YYW.EE1HPFK.bit.EE1HPFK0 = r2y_ctrl_post_resize->hpfK[0];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK1, r2y_ctrl_post_resize->hpfK[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK2, r2y_ctrl_post_resize->hpfK[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK3, r2y_ctrl_post_resize->hpfK[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK4, r2y_ctrl_post_resize->hpfK[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1HPFK, union io_r2y_ee1hpfk, EE1HPFK5, r2y_ctrl_post_resize->hpfK[5] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1NRLV.bit.EE1NRLV = r2y_ctrl_post_resize->strength;

	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPOF.bit.EE1CORPOF_0 = r2y_ctrl_post_resize->coring_p_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPOF.bit.EE1CORPOF_1 = r2y_ctrl_post_resize->coring_p_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPOF.bit.EE1CORPOF_2 = r2y_ctrl_post_resize->coring_p_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPOF.bit.EE1CORPOF_3 = r2y_ctrl_post_resize->coring_p_offset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPGA, union io_r2y_ee1corpga, EE1CORPGA_0, r2y_ctrl_post_resize->coring_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPGA, union io_r2y_ee1corpga, EE1CORPGA_1, r2y_ctrl_post_resize->coring_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPGA, union io_r2y_ee1corpga, EE1CORPGA_2, r2y_ctrl_post_resize->coring_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPGA, union io_r2y_ee1corpga, EE1CORPGA_3, r2y_ctrl_post_resize->coring_p_gain[3] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPBD.bit.EE1CORPBD_1 = r2y_ctrl_post_resize->coring_p_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPBD.bit.EE1CORPBD_2 = r2y_ctrl_post_resize->coring_p_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORPBD.bit.EE1CORPBD_3 = r2y_ctrl_post_resize->coring_p_border[2];

	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMOF.bit.EE1CORMOF_0 = r2y_ctrl_post_resize->coring_m_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMOF.bit.EE1CORMOF_1 = r2y_ctrl_post_resize->coring_m_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMOF.bit.EE1CORMOF_2 = r2y_ctrl_post_resize->coring_m_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMOF.bit.EE1CORMOF_3 = r2y_ctrl_post_resize->coring_m_offset[3];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMGA, union io_r2y_ee1cormga, EE1CORMGA_0, r2y_ctrl_post_resize->coring_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMGA, union io_r2y_ee1cormga, EE1CORMGA_1, r2y_ctrl_post_resize->coring_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMGA, union io_r2y_ee1cormga, EE1CORMGA_2, r2y_ctrl_post_resize->coring_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMGA, union io_r2y_ee1cormga, EE1CORMGA_3, r2y_ctrl_post_resize->coring_m_gain[3] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMBD.bit.EE1CORMBD_1 = r2y_ctrl_post_resize->coring_m_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMBD.bit.EE1CORMBD_2 = r2y_ctrl_post_resize->coring_m_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CORMBD.bit.EE1CORMBD_3 = r2y_ctrl_post_resize->coring_m_border[2];

	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLSUP.bit.EE1SCLSUP = r2y_ctrl_post_resize->scale_reduct_coef;

	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_0 = r2y_ctrl_post_resize->scale_p_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_1 = r2y_ctrl_post_resize->scale_p_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_2 = r2y_ctrl_post_resize->scale_p_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_3 = r2y_ctrl_post_resize->scale_p_offset[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_4 = r2y_ctrl_post_resize->scale_p_offset[4];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_5 = r2y_ctrl_post_resize->scale_p_offset[5];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_6 = r2y_ctrl_post_resize->scale_p_offset[6];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_7 = r2y_ctrl_post_resize->scale_p_offset[7];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_8 = r2y_ctrl_post_resize->scale_p_offset[8];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPOF.bit.EE1SCLPOF_9 = r2y_ctrl_post_resize->scale_p_offset[9];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_0, r2y_ctrl_post_resize->scale_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_1, r2y_ctrl_post_resize->scale_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_2, r2y_ctrl_post_resize->scale_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_3, r2y_ctrl_post_resize->scale_p_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_4, r2y_ctrl_post_resize->scale_p_gain[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_5, r2y_ctrl_post_resize->scale_p_gain[5] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_6, r2y_ctrl_post_resize->scale_p_gain[6] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_7, r2y_ctrl_post_resize->scale_p_gain[7] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_8, r2y_ctrl_post_resize->scale_p_gain[8] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPGA, union io_r2y_ee1sclpga, EE1SCLPGA_9, r2y_ctrl_post_resize->scale_p_gain[9] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_1 = r2y_ctrl_post_resize->scale_p_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_2 = r2y_ctrl_post_resize->scale_p_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_3 = r2y_ctrl_post_resize->scale_p_border[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_4 = r2y_ctrl_post_resize->scale_p_border[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_5 = r2y_ctrl_post_resize->scale_p_border[4];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_6 = r2y_ctrl_post_resize->scale_p_border[5];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_7 = r2y_ctrl_post_resize->scale_p_border[6];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_8 = r2y_ctrl_post_resize->scale_p_border[7];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLPBD.bit.EE1SCLPBD_9 = r2y_ctrl_post_resize->scale_p_border[8];

	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_0 = r2y_ctrl_post_resize->scale_m_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_1 = r2y_ctrl_post_resize->scale_m_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_2 = r2y_ctrl_post_resize->scale_m_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_3 = r2y_ctrl_post_resize->scale_m_offset[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_4 = r2y_ctrl_post_resize->scale_m_offset[4];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_5 = r2y_ctrl_post_resize->scale_m_offset[5];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_6 = r2y_ctrl_post_resize->scale_m_offset[6];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_7 = r2y_ctrl_post_resize->scale_m_offset[7];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_8 = r2y_ctrl_post_resize->scale_m_offset[8];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMOF.bit.EE1SCLMOF_9 = r2y_ctrl_post_resize->scale_m_offset[9];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_0, r2y_ctrl_post_resize->scale_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_1, r2y_ctrl_post_resize->scale_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_2, r2y_ctrl_post_resize->scale_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_3, r2y_ctrl_post_resize->scale_m_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_4, r2y_ctrl_post_resize->scale_m_gain[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_5, r2y_ctrl_post_resize->scale_m_gain[5] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_6, r2y_ctrl_post_resize->scale_m_gain[6] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_7, r2y_ctrl_post_resize->scale_m_gain[7] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_8, r2y_ctrl_post_resize->scale_m_gain[8] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMGA, union io_r2y_ee1sclmga, EE1SCLMGA_9, r2y_ctrl_post_resize->scale_m_gain[9] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_1 = r2y_ctrl_post_resize->scale_m_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_2 = r2y_ctrl_post_resize->scale_m_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_3 = r2y_ctrl_post_resize->scale_m_border[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_4 = r2y_ctrl_post_resize->scale_m_border[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_5 = r2y_ctrl_post_resize->scale_m_border[4];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_6 = r2y_ctrl_post_resize->scale_m_border[5];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_7 = r2y_ctrl_post_resize->scale_m_border[6];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_8 = r2y_ctrl_post_resize->scale_m_border[7];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1SCLMBD.bit.EE1SCLMBD_9 = r2y_ctrl_post_resize->scale_m_border[8];

	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPOF.bit.EE1TONPOF_0 = r2y_ctrl_post_resize->gradation_p_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPOF.bit.EE1TONPOF_1 = r2y_ctrl_post_resize->gradation_p_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPOF.bit.EE1TONPOF_2 = r2y_ctrl_post_resize->gradation_p_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPOF.bit.EE1TONPOF_3 = r2y_ctrl_post_resize->gradation_p_offset[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPOF.bit.EE1TONPOF_4 = r2y_ctrl_post_resize->gradation_p_offset[4];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_0, r2y_ctrl_post_resize->gradation_p_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_1, r2y_ctrl_post_resize->gradation_p_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_2, r2y_ctrl_post_resize->gradation_p_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_3, r2y_ctrl_post_resize->gradation_p_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPGA, union io_r2y_ee1tonpga, EE1TONPGA_4, r2y_ctrl_post_resize->gradation_p_gain[4] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPBD.bit.EE1TONPBD_1 = r2y_ctrl_post_resize->gradation_p_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPBD.bit.EE1TONPBD_2 = r2y_ctrl_post_resize->gradation_p_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPBD.bit.EE1TONPBD_3 = r2y_ctrl_post_resize->gradation_p_border[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONPBD.bit.EE1TONPBD_4 = r2y_ctrl_post_resize->gradation_p_border[3];

	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMOF.bit.EE1TONMOF_0 = r2y_ctrl_post_resize->gradation_m_offset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMOF.bit.EE1TONMOF_1 = r2y_ctrl_post_resize->gradation_m_offset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMOF.bit.EE1TONMOF_2 = r2y_ctrl_post_resize->gradation_m_offset[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMOF.bit.EE1TONMOF_3 = r2y_ctrl_post_resize->gradation_m_offset[3];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMOF.bit.EE1TONMOF_4 = r2y_ctrl_post_resize->gradation_m_offset[4];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_0, r2y_ctrl_post_resize->gradation_m_gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_1, r2y_ctrl_post_resize->gradation_m_gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_2, r2y_ctrl_post_resize->gradation_m_gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_3, r2y_ctrl_post_resize->gradation_m_gain[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMGA, union io_r2y_ee1tonmga, EE1TONMGA_4, r2y_ctrl_post_resize->gradation_m_gain[4] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMBD.bit.EE1TONMBD_1 = r2y_ctrl_post_resize->gradation_m_border[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMBD.bit.EE1TONMBD_2 = r2y_ctrl_post_resize->gradation_m_border[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMBD.bit.EE1TONMBD_3 = r2y_ctrl_post_resize->gradation_m_border[2];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1TONMBD.bit.EE1TONMBD_4 = r2y_ctrl_post_resize->gradation_m_border[3];

	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPPOF.bit.EE1CLPPOF_0 = r2y_ctrl_post_resize->levelClipPOffset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPPOF.bit.EE1CLPPOF_1 = r2y_ctrl_post_resize->levelClipPOffset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPPOF.bit.EE1CLPPOF_2 = r2y_ctrl_post_resize->levelClipPOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPPGA, union io_r2y_ee1clppga, EE1CLPPGA_0, r2y_ctrl_post_resize->levelClipPGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPPGA, union io_r2y_ee1clppga, EE1CLPPGA_1, r2y_ctrl_post_resize->levelClipPGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPPGA, union io_r2y_ee1clppga, EE1CLPPGA_2, r2y_ctrl_post_resize->levelClipPGain[2] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPPBD.bit.EE1CLPPBD_1 = r2y_ctrl_post_resize->levelClipPBorder[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPPBD.bit.EE1CLPPBD_2 = r2y_ctrl_post_resize->levelClipPBorder[1];

	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPMOF.bit.EE1CLPMOF_0 = r2y_ctrl_post_resize->levelClipMOffset[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPMOF.bit.EE1CLPMOF_1 = r2y_ctrl_post_resize->levelClipMOffset[1];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPMOF.bit.EE1CLPMOF_2 = r2y_ctrl_post_resize->levelClipMOffset[2];
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPMGA, union io_r2y_ee1clpmga, EE1CLPMGA_0, r2y_ctrl_post_resize->levelClipMGain[0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPMGA, union io_r2y_ee1clpmga, EE1CLPMGA_1, r2y_ctrl_post_resize->levelClipMGain[1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPMGA, union io_r2y_ee1clpmga, EE1CLPMGA_2, r2y_ctrl_post_resize->levelClipMGain[2] );
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPMBD.bit.EE1CLPMBD_1 = r2y_ctrl_post_resize->levelClipMBorder[0];
	gImIoR2yRegPtr[pipeNo]->YYW.EE1CLPMBD.bit.EE1CLPMBD_2 = r2y_ctrl_post_resize->levelClipMBorder[1];

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Offset Control
 */
INT32 im_r2y_set_offset(ImR2yCtrl *self, kuint16 pipeNo, const ImR2yCtrlOfs* const ofs )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( ofs == NULL ) {
		Ddim_Assertion(("im_r2y_set_offset error. ofs = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_offset error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValOffsetCtrl( pipeNo, ofs );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.OFST, union io_r2y_ofst, OFSTR, ofs->R );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.OFST, union io_r2y_ofst, OFSTG, ofs->G );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.OFST, union io_r2y_ofst, OFSTB, ofs->B );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Tone Control
 */
INT32 im_r2y_ctrl_tone(ImR2yCtrl *self, kuint16 pipeNo, const ImR2yCtrlTone* const r2y_ctrl_tone )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_tone == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl_tone error. r2y_ctrl_tone = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl_tone error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValToneCtrl( pipeNo, r2y_ctrl_tone );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCEN     = r2y_ctrl_tone->tone_enable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCYBEN   = r2y_ctrl_tone->tone_yb_enable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCBLEN   = r2y_ctrl_tone->table_blend_enable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCRES    = r2y_ctrl_tone->table_resol;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCTBL    = r2y_ctrl_tone->table_select;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCYOUT   = r2y_ctrl_tone->ytc_out;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCINTBIT = r2y_ctrl_tone->int_bit;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCTL.bit.TCBLND   = r2y_ctrl_tone->table_blend_ratio;

	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCYC.bit.TCYC_0_0 = r2y_ctrl_tone->yc_matrix[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCYC.bit.TCYC_0_1 = r2y_ctrl_tone->yc_matrix[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCYC.bit.TCYC_0_2 = r2y_ctrl_tone->yc_matrix[2];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCEP.bit.TCEP_0 = r2y_ctrl_tone->table_endp[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCEP.bit.TCEP_1 = r2y_ctrl_tone->table_endp[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCEP.bit.TCEP_2 = r2y_ctrl_tone->table_endp[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCEP.bit.TCEP_3 = r2y_ctrl_tone->table_endp[3];

	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCLPR.bit.TCCLPRP = r2y_ctrl_tone->clipPR;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCLPR.bit.TCCLPRM = r2y_ctrl_tone->clipMR;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCLPG.bit.TCCLPGP = r2y_ctrl_tone->clipPG;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCLPG.bit.TCCLPGM = r2y_ctrl_tone->clipMG;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCLPB.bit.TCCLPBP = r2y_ctrl_tone->clipPB;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.TC.TCCLPB.bit.TCCLPBM = r2y_ctrl_tone->clipMB;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Tone control table access enable
 */
INT32 im_r2y_set_tone_control_tbl_access_enable(ImR2yCtrl *self, kuint16 pipeNo, kuint16 tc_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_tone_control_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_tone_control_tbl_accen_ctrl,
									 tc_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_set_tone_control_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Is Tone Control active
 */
INT32 im_r2y_is_act_tone(ImR2yCtrl *self, kuint16 pipeNo, kuint16* const active_status )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_is_act_tone error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	*active_status = (gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YFLAG.bit.TCACT != 0)?(ImR2yCtrl_ENABLE_ON):(ImR2yCtrl_ENABLE_OFF);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

ImR2yCtrl *im_r2y_ctrl_new(void)
{
	ImR2yCtrl* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL,sizeof(ImR2yCtrlPrivate));
	return self;
}
