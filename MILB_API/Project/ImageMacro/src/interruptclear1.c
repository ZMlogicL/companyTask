/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :王睿
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

#include "interruptclear1.h"
#include "interruptdefine.h"

#include "jdspro.h"
#include "im_pro.h"
#include "im_pro_common.h"
#include "dd_top.h"

K_TYPE_DEFINE_WITH_PRIVATE(InterruptClear1, interrupt_clear1);
#define INTERRUPT_CLEAR1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), InterruptClear1Private, INTERRUPT_TYPE_CLEAR1))

struct _InterruptClear1Private
{
	int a;
};


static void interrupt_clear1_constructor(InterruptClear1 *self)
{
	InterruptClear1Private *priv = INTERRUPT_CLEAR1_GET_PRIVATE(self);
	priv->a=0;
}

static void interrupt_clear1_destructor(InterruptClear1 *self)
{
	InterruptClear1Private *priv = INTERRUPT_CLEAR1_GET_PRIVATE(self);
	priv->a=0;
}

/*----------------------------------------------------------------------*/
/*DECLS   																       */
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* IMPL														                   */
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* PUBLIC                           											   */
/*----------------------------------------------------------------------*/
/**
SENTOP Interrupt setting
@param[in]	intCtrl : SENTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear1_sentop_interrupt_ctrl( InterruptClear1*self,T_IM_PRO_INT_SENTOP_CTRL* intCtrl )
{
	struct io_vhdintenb	vhdintenb;
	struct io_vhdintflg	vhdintflg;

#ifdef CO_PARAM_CHECK
	if (intCtrl == NULL){
		Ddim_Assertion(("I:interrupt_clear1_sentop_interrupt_ctrl error. intCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCtrl->vd_enable.permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear1_sentop_interrupt_ctrl error. 'permission_flg' value over!! (%d)\n", intCtrl->vd_enable.permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	vhdintenb.VHDINTENB1.word	= IO_PRO.SEN.SENTOP.VHDINTENB.VHDINTENB1.word;
	vhdintenb.VHDINTENB2.word	= IO_PRO.SEN.SENTOP.VHDINTENB.VHDINTENB2.word;

	vhdintflg.VHDINTFLG1.word	= 0;
	vhdintflg.VHDINTFLG2.word	= 0;

	// VHDINTENB VD Interrupt
	if (0 != (intCtrl->vd_enable.interrupt_bit & D_IM_PRO_INT_VDE00)){
		vhdintflg.VHDINTFLG1.bit.__VDF00	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB1.bit.VDE00		= intCtrl->vd_enable.permission_flg;
	}
	if (0 != (intCtrl->vd_enable.interrupt_bit & D_IM_PRO_INT_VDE01)){
		vhdintflg.VHDINTFLG1.bit.__VDF01	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB1.bit.VDE01		= intCtrl->vd_enable.permission_flg;
	}
	if (0 != (intCtrl->vd_enable.interrupt_bit & D_IM_PRO_INT_VDE10)){
		vhdintflg.VHDINTFLG1.bit.__VDF10	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB1.bit.VDE10		= intCtrl->vd_enable.permission_flg;
	}
	if (0 != (intCtrl->vd_enable.interrupt_bit & D_IM_PRO_INT_VDE11)){
		vhdintflg.VHDINTFLG1.bit.__VDF11	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB1.bit.VDE10		= intCtrl->vd_enable.permission_flg;
	}
	if (0 != (intCtrl->vd_enable.interrupt_bit & D_IM_PRO_INT_VDE20)){
		vhdintflg.VHDINTFLG1.bit.__VDF20	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB1.bit.VDE20		= intCtrl->vd_enable.permission_flg;
	}
	if (0 != (intCtrl->vd_enable.interrupt_bit & D_IM_PRO_INT_VDE21)){
		vhdintflg.VHDINTFLG1.bit.__VDF21	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB1.bit.VDE21		= intCtrl->vd_enable.permission_flg;
	}
	if (0 != (intCtrl->vd_enable.interrupt_bit & D_IM_PRO_INT_VDE30)){
		vhdintflg.VHDINTFLG1.bit.__VDF30	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB1.bit.VDE30		= intCtrl->vd_enable.permission_flg;
	}
	if (0 != (intCtrl->vd_enable.interrupt_bit & D_IM_PRO_INT_VDE31)){
		vhdintflg.VHDINTFLG1.bit.__VDF31	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB1.bit.VDE31		= intCtrl->vd_enable.permission_flg;
	}

	// VHDINTENB HD Interrupt
	if (0 != (intCtrl->hd_enable.interrupt_bit & D_IM_PRO_INT_HDE00)){
		vhdintflg.VHDINTFLG2.bit.__HDF00	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB2.bit.HDE00		= intCtrl->hd_enable.permission_flg;
	}
	if (0 != (intCtrl->hd_enable.interrupt_bit & D_IM_PRO_INT_HDE01)){
		vhdintflg.VHDINTFLG2.bit.__HDF01	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB2.bit.HDE01		= intCtrl->hd_enable.permission_flg;
	}
	if (0 != (intCtrl->hd_enable.interrupt_bit & D_IM_PRO_INT_HDE10)){
		vhdintflg.VHDINTFLG2.bit.__HDF10	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB2.bit.HDE10		= intCtrl->hd_enable.permission_flg;
	}
	if (0 != (intCtrl->hd_enable.interrupt_bit & D_IM_PRO_INT_HDE11)){
		vhdintflg.VHDINTFLG2.bit.__HDF11	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB2.bit.HDE10		= intCtrl->hd_enable.permission_flg;
	}
	if (0 != (intCtrl->hd_enable.interrupt_bit & D_IM_PRO_INT_HDE20)){
		vhdintflg.VHDINTFLG2.bit.__HDF20	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB2.bit.HDE20		= intCtrl->hd_enable.permission_flg;
	}
	if (0 != (intCtrl->hd_enable.interrupt_bit & D_IM_PRO_INT_HDE21)){
		vhdintflg.VHDINTFLG2.bit.__HDF21	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB2.bit.HDE21		= intCtrl->hd_enable.permission_flg;
	}
	if (0 != (intCtrl->hd_enable.interrupt_bit & D_IM_PRO_INT_HDE30)){
		vhdintflg.VHDINTFLG2.bit.__HDF30	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB2.bit.HDE30		= intCtrl->hd_enable.permission_flg;
	}
	if (0 != (intCtrl->hd_enable.interrupt_bit & D_IM_PRO_INT_HDE31)){
		vhdintflg.VHDINTFLG2.bit.__HDF31	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.VHDINTENB2.bit.HDE31		= intCtrl->hd_enable.permission_flg;
	}

	IO_PRO.SEN.SENTOP.INTCTL.bit.INTMD	= intCtrl->int_mode;
	IO_PRO.SEN.SENTOP.VHDINTFLG.VHDINTFLG1.word	= vhdintflg.VHDINTFLG1.word;
	IO_PRO.SEN.SENTOP.VHDINTENB.VHDINTENB1.word	= vhdintenb.VHDINTENB1.word;

	IO_PRO.SEN.SENTOP.VHDINTFLG.VHDINTFLG2.word	= vhdintflg.VHDINTFLG2.word;
	IO_PRO.SEN.SENTOP.VHDINTENB.VHDINTENB2.word	= vhdintenb.VHDINTENB2.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
SENTOP Interrupt setting
@param[in]	sgIntCtrl : SENTOP SG interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear1_sentop_sg_interrupt_ctrl( InterruptClear1*self,T_IM_PRO_INT_SG_CTRL* sgIntCtrl )
{
	union io_sgvhdintenb	sgvhdintenb;
	union io_sgvhdintflg	sgvhdintflg;

#ifdef CO_PARAM_CHECK
	if (sgIntCtrl == NULL){
		Ddim_Assertion(("I:interrupt_clear1_sentop_sg_interrupt_ctrl error. sgIntCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (sgIntCtrl->sg_vd_enable.permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear1_sentop_sg_interrupt_ctrl error. 'SG VD permission_flg' value over!! (%d)\n", sgIntCtrl->sg_vd_enable.permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (sgIntCtrl->sg_hd_enable.permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear1_sentop_sg_interrupt_ctrl error. 'SG HD permission_flg' value over!! (%d)\n", sgIntCtrl->sg_hd_enable.permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	sgvhdintenb.word	= IO_PRO.SEN.SENTOP.SGVHDINTENB.word;
	sgvhdintflg.word	= 0;

	// SGVHDINTENB VD Interrupt
	if (0 != (sgIntCtrl->sg_vd_enable.interrupt_bit & D_IM_PRO_INT_SGVDE0)){
		sgvhdintflg.bit.__VDF_SG0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sgvhdintenb.bit.VDE_SG0		= sgIntCtrl->sg_vd_enable.permission_flg;
	}
	if (0 != (sgIntCtrl->sg_vd_enable.interrupt_bit & D_IM_PRO_INT_SGVDE1)){
		sgvhdintflg.bit.__VDF_SG1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sgvhdintenb.bit.VDE_SG1		= sgIntCtrl->sg_vd_enable.permission_flg;
	}
	if (0 != (sgIntCtrl->sg_vd_enable.interrupt_bit & D_IM_PRO_INT_SGVDE2)){
		sgvhdintflg.bit.__VDF_SG2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sgvhdintenb.bit.VDE_SG2		= sgIntCtrl->sg_vd_enable.permission_flg;
	}
	if (0 != (sgIntCtrl->sg_vd_enable.interrupt_bit & D_IM_PRO_INT_SGVDE3)){
		sgvhdintflg.bit.__VDF_SG3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sgvhdintenb.bit.VDE_SG3		= sgIntCtrl->sg_vd_enable.permission_flg;
	}

	// SGVHDINTENB HD Interrupt
	if (0 != (sgIntCtrl->sg_hd_enable.interrupt_bit & D_IM_PRO_INT_SGHDE0)){
		sgvhdintflg.bit.__HDF_SG0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sgvhdintenb.bit.HDE_SG0		= sgIntCtrl->sg_hd_enable.permission_flg;
	}
	if (0 != (sgIntCtrl->sg_hd_enable.interrupt_bit & D_IM_PRO_INT_SGHDE1)){
		sgvhdintflg.bit.__HDF_SG1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sgvhdintenb.bit.HDE_SG1		= sgIntCtrl->sg_hd_enable.permission_flg;
	}
	if (0 != (sgIntCtrl->sg_hd_enable.interrupt_bit & D_IM_PRO_INT_SGHDE2)){
		sgvhdintflg.bit.__HDF_SG2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sgvhdintenb.bit.HDE_SG2		= sgIntCtrl->sg_hd_enable.permission_flg;
	}
	if (0 != (sgIntCtrl->sg_hd_enable.interrupt_bit & D_IM_PRO_INT_SGHDE3)){
		sgvhdintflg.bit.__HDF_SG3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sgvhdintenb.bit.HDE_SG3		= sgIntCtrl->sg_hd_enable.permission_flg;
	}

	IO_PRO.SEN.SENTOP.VHDSGCTL.VHDSGCTL1.bit.SGVDEG0	= sgIntCtrl->sg_sync.vdeg[0];
	IO_PRO.SEN.SENTOP.VHDSGCTL.VHDSGCTL1.bit.SGVDEG1	= sgIntCtrl->sg_sync.vdeg[1];
	IO_PRO.SEN.SENTOP.VHDSGCTL.VHDSGCTL2.bit.SGVDEG2	= sgIntCtrl->sg_sync.vdeg[2];
	IO_PRO.SEN.SENTOP.VHDSGCTL.VHDSGCTL2.bit.SGVDEG3	= sgIntCtrl->sg_sync.vdeg[3];
	IO_PRO.SEN.SENTOP.VHDSGCTL.VHDSGCTL1.bit.SGHDEG0	= sgIntCtrl->sg_sync.hdeg[0];
	IO_PRO.SEN.SENTOP.VHDSGCTL.VHDSGCTL1.bit.SGHDEG1	= sgIntCtrl->sg_sync.hdeg[1];
	IO_PRO.SEN.SENTOP.VHDSGCTL.VHDSGCTL2.bit.SGHDEG2	= sgIntCtrl->sg_sync.hdeg[2];
	IO_PRO.SEN.SENTOP.VHDSGCTL.VHDSGCTL2.bit.SGHDEG3	= sgIntCtrl->sg_sync.hdeg[3];

	IO_PRO.SEN.SENTOP.SGVHDINTFLG.word	= sgvhdintflg.word;
	IO_PRO.SEN.SENTOP.SGVHDINTENB.word	= sgvhdintenb.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
GYRO Interrupt setting
@param[in]	gyroIntCtrl : GYRO interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear1_sentop_gyro_interrupt_ctrl( InterruptClear1*self,T_IM_PRO_INT_GYRO_CTRL* gyroIntCtrl )
{
	union io_gintenb	gintenb;
	union io_gintflg	gintflg;

#ifdef CO_PARAM_CHECK
	if (gyroIntCtrl == NULL){
		Ddim_Assertion(("I:interrupt_clear1_sentop_gyro_interrupt_ctrl error. gyroIntCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (gyroIntCtrl->gyro_sof_enable.permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear1_sentop_gyro_interrupt_ctrl error. 'SOF permission_flg' value over!! (%d)\n", gyroIntCtrl->gyro_sof_enable.permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (gyroIntCtrl->gyro_eof_enable.permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear1_sentop_gyro_interrupt_ctrl error. 'EOF permission_flg' value over!! (%d)\n", gyroIntCtrl->gyro_sof_enable.permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	gintenb.word	= IO_PRO.SEN.SENTOP.GINTENB.word;
	gintflg.word	= 0;

	// GINTENB SOF Interrupt
	if (0 != (gyroIntCtrl->gyro_sof_enable.interrupt_bit & D_IM_PRO_INT_GYRO_SOFE0)){
		gintflg.bit.__SOFF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		gintenb.bit.SOFE0	= gyroIntCtrl->gyro_sof_enable.permission_flg;
	}
	if (0 != (gyroIntCtrl->gyro_sof_enable.interrupt_bit & D_IM_PRO_INT_GYRO_SOFE1)){
		gintflg.bit.__SOFF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		gintenb.bit.SOFE1	= gyroIntCtrl->gyro_sof_enable.permission_flg;
	}
	if (0 != (gyroIntCtrl->gyro_sof_enable.interrupt_bit & D_IM_PRO_INT_GYRO_SOFE2)){
		gintflg.bit.__SOFF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		gintenb.bit.SOFE2	= gyroIntCtrl->gyro_sof_enable.permission_flg;
	}
	if (0 != (gyroIntCtrl->gyro_sof_enable.interrupt_bit & D_IM_PRO_INT_GYRO_SOFE3)){
		gintflg.bit.__SOFF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		gintenb.bit.SOFE3	= gyroIntCtrl->gyro_sof_enable.permission_flg;
	}

	// GINTENB EOF Interrupt
	if (0 != (gyroIntCtrl->gyro_eof_enable.interrupt_bit & D_IM_PRO_INT_GYRO_EOFE0)){
		gintflg.bit.__EOFF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		gintenb.bit.EOFE0	= gyroIntCtrl->gyro_eof_enable.permission_flg;
	}
	if (0 != (gyroIntCtrl->gyro_eof_enable.interrupt_bit & D_IM_PRO_INT_GYRO_EOFE1)){
		gintflg.bit.__EOFF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		gintenb.bit.EOFE1	= gyroIntCtrl->gyro_eof_enable.permission_flg;
	}
	if (0 != (gyroIntCtrl->gyro_eof_enable.interrupt_bit & D_IM_PRO_INT_GYRO_EOFE2)){
		gintflg.bit.__EOFF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		gintenb.bit.EOFE2	= gyroIntCtrl->gyro_eof_enable.permission_flg;
	}
	if (0 != (gyroIntCtrl->gyro_eof_enable.interrupt_bit & D_IM_PRO_INT_GYRO_EOFE3)){
		gintflg.bit.__EOFF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		gintenb.bit.EOFE3	= gyroIntCtrl->gyro_eof_enable.permission_flg;
	}

	IO_PRO.SEN.SENTOP.GINTFLG.word	= gintflg.word;
	IO_PRO.SEN.SENTOP.GINTENB.word	= gintenb.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
Set SLVS-EC Common Interrupt flg
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear1_slvs_set_common_interrupt( InterruptClear1*self,T_IM_PRO_INT_CFG* intCfg )
{
	union io_slvsec_peintst	slvsec_peintst;
	union io_slvsec_peinten	slvsec_peinten;
#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear1_slvs_set_common_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear1_slvs_set_common_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	slvsec_peintst.word	= 0;
	slvsec_peinten.word	= IO_PRO.SEN.SLVSEC.COMMON.PEINTEN.word;

	// SLVS-EC IPC errot detect interrupt
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE0_BIT)){
		slvsec_peintst.bit.__IPC0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IPC0		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE1_BIT)){
		slvsec_peintst.bit.__IPC1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IPC1		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE2_BIT)){
		slvsec_peintst.bit.__IPC2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IPC2		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE3_BIT)){
		slvsec_peintst.bit.__IPC3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IPC3		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE4_BIT)){
		slvsec_peintst.bit.__IPC4	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IPC4		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE5_BIT)){
		slvsec_peintst.bit.__IPC5	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IPC5		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE6_BIT)){
		slvsec_peintst.bit.__IPC6	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IPC6		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE7_BIT)){
		slvsec_peintst.bit.__IPC7	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IPC7		= intCfg->permission_flg;
	}

	// SLVS-EC RDE errot detect interrupt
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE0_BIT)){
		slvsec_peintst.bit.__RDE0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.RDE0		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE1_BIT)){
		slvsec_peintst.bit.__RDE1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.RDE1		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE2_BIT)){
		slvsec_peintst.bit.__RDE2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.RDE2		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE3_BIT)){
		slvsec_peintst.bit.__RDE3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.RDE3		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE4_BIT)){
		slvsec_peintst.bit.__RDE4	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.RDE4		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE5_BIT)){
		slvsec_peintst.bit.__RDE5	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.RDE5		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE6_BIT)){
		slvsec_peintst.bit.__RDE6	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.RDE6		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE7_BIT)){
		slvsec_peintst.bit.__RDE7	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.RDE7		= intCfg->permission_flg;
	}

	// SLVS-EC IC errot detect interrupt
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE0_BIT)){
		slvsec_peintst.bit.__IC0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IC0		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE1_BIT)){
		slvsec_peintst.bit.__IC1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IC1		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE2_BIT)){
		slvsec_peintst.bit.__IC2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IC2		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE3_BIT)){
		slvsec_peintst.bit.__IC3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IC3		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE4_BIT)){
		slvsec_peintst.bit.__IC4	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IC4		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE5_BIT)){
		slvsec_peintst.bit.__IC5	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IC5		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE6_BIT)){
		slvsec_peintst.bit.__IC6	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IC6		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE7_BIT)){
		slvsec_peintst.bit.__IC7	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		slvsec_peinten.bit.IC7		= intCfg->permission_flg;
	}

	IO_PRO.SEN.SLVSEC.COMMON.PEINTST.word		= slvsec_peintst.word;
	IO_PRO.SEN.SLVSEC.COMMON.PEINTEN.word		= slvsec_peinten.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
Set SLVS-EC Interrupt flg
@param[in]	streamType : stream type of SLVS
@param[in]	intType : interrupt type of SLVS
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear1_slvs_set_interrupt( InterruptClear1*self,
		E_IM_PRO_SLVS_STREAM_TYPE streamType, E_IM_PRO_SLVS_INT_TYPE intType, T_IM_PRO_INT_CFG* intCfg )
{
	union io_slvsec_intst		slvsecIntst;
	union io_slvsec_inten		slvsecInten;
	union io_slvsec_leintst		slvsecLeintst;
	union io_slvsec_leinten		slvsecLeinten;
	union io_slvsec_meintst0	slvsecMeintst0;
	union io_slvsec_meinten0	slvsecMeinten0;
	union io_slvsec_meintst1	slvsecMeintst1;
	union io_slvsec_meinten1	slvsecMeinten1;

#ifdef CO_PARAM_CHECK
	if (streamType >= E_IM_PRO_SLVS_STREAM_TYPE_BOTH){
		Ddim_Assertion(("I:interrupt_clear1_slvs_set_interrupt. streamType value error!! (%d)\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear1_slvs_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear1_slvs_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	switch( intType ) {
		case E_IM_PRO_SLVS_INT_TYPE_INTN_O:
			slvsecIntst.word	= 0;
			slvsecInten.word	= IO_PRO.SEN.SLVSEC.STREAM[streamType].INTEN.word;

			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_INTST_STBY_BIT)){
				slvsecIntst.bit.STBY	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecInten.bit.STBY	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_INTST_RDY_BIT)){
				slvsecIntst.bit.RDY	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecInten.bit.RDY	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_INTST_FEO_BIT)){
				slvsecIntst.bit.FEO	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecInten.bit.FEO	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_INTST_FEI_BIT)){
				slvsecIntst.bit.FEI	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecInten.bit.FEI	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_INTST_FSO_BIT)){
				slvsecIntst.bit.FSO	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecInten.bit.FSO	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_INTST_FSI_BIT)){
				slvsecIntst.bit.FSI	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecInten.bit.FSI	= intCfg->permission_flg;
			}

			IO_PRO.SEN.SLVSEC.STREAM[streamType].INTST.word	= slvsecIntst.word;
			IO_PRO.SEN.SLVSEC.STREAM[streamType].INTEN.word	= slvsecInten.word;
			Im_Pro_Dsb();
			break;

		case E_IM_PRO_SLVS_INT_TYPE_LINK_ERR:
			slvsecLeintst.word	= 0;
			slvsecLeinten.word	= IO_PRO.SEN.SLVSEC.STREAM[streamType].LEINTEN.word;

			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_LLE_BIT)){
				slvsecLeintst.bit.LLE		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.LLE		= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_PCRCE_BIT)){
				slvsecLeintst.bit.PCRCE	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.PCRCE	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_HCRC1C_BIT)){
				slvsecLeintst.bit.HCRC1C	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.HCRC1C	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_HCRC2C_BIT)){
				slvsecLeintst.bit.HCRC2C	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.HCRC2C	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_HCRCE_BIT)){
				slvsecLeintst.bit.HCRCE	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.HCRCE	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_ECC1C_BIT)){
				slvsecLeintst.bit.ECC1C	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.ECC1C	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_ECC2C_BIT)){
				slvsecLeintst.bit.ECC2C	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.ECC2C	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_ECCE_BIT)){
				slvsecLeintst.bit.ECCE		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.ECCE		= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_LNE_BIT)){
				slvsecLeintst.bit.LNE		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.LNE		= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_LEINTEN_LBOVF_BIT)){
				slvsecLeintst.bit.LBOVF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecLeinten.bit.LBOVF	= intCfg->permission_flg;
			}

			IO_PRO.SEN.SLVSEC.STREAM[streamType].LEINTST.word	= slvsecLeintst.word;
			IO_PRO.SEN.SLVSEC.STREAM[streamType].LEINTEN.word	= slvsecLeinten.word;
			Im_Pro_Dsb();
			break;

		case E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1:
			slvsecMeintst0.word	= 0;
			slvsecMeinten0.word	= IO_PRO.SEN.SLVSEC.STREAM[streamType].MEINTEN0.word;

			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN0_ECL_BIT)){
				slvsecMeintst0.bit.ECL		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten0.bit.ECL		= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN0_SCL_BIT)){
				slvsecMeintst0.bit.SCL		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten0.bit.SCL		= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN0_DCL_BIT)){
				slvsecMeintst0.bit.DCL		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten0.bit.DCL		= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN0_DSD_BIT)){
				slvsecMeintst0.bit.DSD		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten0.bit.DSD		= intCfg->permission_flg;
			}

			IO_PRO.SEN.SLVSEC.STREAM[streamType].MEINTST0.word	= slvsecMeintst0.word;
			IO_PRO.SEN.SLVSEC.STREAM[streamType].MEINTEN0.word	= slvsecMeinten0.word;
			Im_Pro_Dsb();
			break;

		//case E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2:
		default:
			slvsecMeintst1.word	= 0;
			slvsecMeinten1.word	= IO_PRO.SEN.SLVSEC.STREAM[streamType].MEINTEN1.word;

			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE0_BIT)){
				slvsecMeintst1.bit.FOVF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FOVF0	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE1_BIT)){
				slvsecMeintst1.bit.FOVF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FOVF1	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE2_BIT)){
				slvsecMeintst1.bit.FOVF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FOVF2	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE3_BIT)){
				slvsecMeintst1.bit.FOVF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FOVF3	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE4_BIT)){
				slvsecMeintst1.bit.FOVF4	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FOVF4	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE5_BIT)){
				slvsecMeintst1.bit.FOVF5	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FOVF5	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE6_BIT)){
				slvsecMeintst1.bit.FOVF6	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FOVF6	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE7_BIT)){
				slvsecMeintst1.bit.FOVF7	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FOVF7	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE0_BIT)){
				slvsecMeintst1.bit.FUNF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FUNF0	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE1_BIT)){
				slvsecMeintst1.bit.FUNF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FUNF1	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE2_BIT)){
				slvsecMeintst1.bit.FUNF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FUNF2	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE3_BIT)){
				slvsecMeintst1.bit.FUNF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FUNF3	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE4_BIT)){
				slvsecMeintst1.bit.FUNF4	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FUNF4	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE5_BIT)){
				slvsecMeintst1.bit.FUNF5	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FUNF5	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE6_BIT)){
				slvsecMeintst1.bit.FUNF6	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FUNF6	= intCfg->permission_flg;
			}
			if (0 != (intCfg->interrupt_bit & D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE7_BIT)){
				slvsecMeintst1.bit.FUNF7	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
				slvsecMeinten1.bit.FUNF7	= intCfg->permission_flg;
			}

			IO_PRO.SEN.SLVSEC.STREAM[streamType].MEINTST1.word	= slvsecMeintst1.word;
			IO_PRO.SEN.SLVSEC.STREAM[streamType].MEINTEN1.word	= slvsecMeinten1.word;
			Im_Pro_Dsb();
			break;
	}

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
LVDS Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear1_lvds_set_interrupt( InterruptClear1*self,E_IM_PRO_LVDS_CH ch, T_IM_PRO_INT_LVDS_CTRL* intCfg )
{
	union io_lvds_intflg0 lvdsIntflg0;
	union io_lvds_intenb0 lvdsIntenb0;
	union io_lvds_intflg1 lvdsIntflg1;
	union io_lvds_intenb1 lvdsIntenb1;
	union io_lvds_intflg2 lvdsIntflg2;
	union io_lvds_intenb2 lvdsIntenb2;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear1_lvds_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	lvdsIntflg0.word	= 0;
	lvdsIntenb0.word	= IO_PRO.SEN.LVDS[ch].LVDSINTENB0.word;

	if (0 != (intCfg->lvds_int_enable[0].interrupt_bit & D_IM_PRO_LVDSINTENB_SOFE0)){
		lvdsIntflg0.bit.__SOFF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb0.bit.SOFE0		= intCfg->lvds_int_enable[0].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[0].interrupt_bit & D_IM_PRO_LVDSINTENB_EOFE0)){
		lvdsIntflg0.bit.__EOFF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb0.bit.EOFE0		= intCfg->lvds_int_enable[0].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[0].interrupt_bit & D_IM_PRO_LVDSINTENB_SOLE0)){
		lvdsIntflg0.bit.__SOLF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb0.bit.SOLE0		= intCfg->lvds_int_enable[0].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[0].interrupt_bit & D_IM_PRO_LVDSINTENB_EOLE0)){
		lvdsIntflg0.bit.__EOLF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb0.bit.EOLE0		= intCfg->lvds_int_enable[0].permission_flg;
	}

	lvdsIntflg1.word	= 0;
	lvdsIntenb1.word	= IO_PRO.SEN.LVDS[ch].LVDSINTENB1.word;

	if (0 != (intCfg->lvds_int_enable[1].interrupt_bit & D_IM_PRO_LVDSINTENB_SOFE1)){
		lvdsIntflg1.bit.__SOFF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb1.bit.SOFE1		= intCfg->lvds_int_enable[1].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[1].interrupt_bit & D_IM_PRO_LVDSINTENB_EOFE1)){
		lvdsIntflg1.bit.__EOFF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb1.bit.EOFE1		= intCfg->lvds_int_enable[1].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[1].interrupt_bit & D_IM_PRO_LVDSINTENB_SOLE1)){
		lvdsIntflg1.bit.__SOLF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb1.bit.SOLE1		= intCfg->lvds_int_enable[1].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[1].interrupt_bit & D_IM_PRO_LVDSINTENB_EOLE1)){
		lvdsIntflg1.bit.__EOLF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb1.bit.EOLE1		= intCfg->lvds_int_enable[1].permission_flg;
	}

	lvdsIntflg2.word	= 0;
	lvdsIntenb2.word	= IO_PRO.SEN.LVDS[ch].LVDSINTENB2.word;

	if (0 != (intCfg->lvds_int_enable[2].interrupt_bit & D_IM_PRO_LVDSINTENB_SOFE2)){
		lvdsIntflg2.bit.__SOFF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb2.bit.SOFE2		= intCfg->lvds_int_enable[2].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[2].interrupt_bit & D_IM_PRO_LVDSINTENB_EOFE2)){
		lvdsIntflg2.bit.__EOFF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb2.bit.EOFE2		= intCfg->lvds_int_enable[2].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[2].interrupt_bit & D_IM_PRO_LVDSINTENB_SOLE2)){
		lvdsIntflg2.bit.__SOLF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb2.bit.SOLE2		= intCfg->lvds_int_enable[2].permission_flg;
	}
	if (0 != (intCfg->lvds_int_enable[2].interrupt_bit & D_IM_PRO_LVDSINTENB_EOLE2)){
		lvdsIntflg2.bit.__EOLF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lvdsIntenb2.bit.EOLE2		= intCfg->lvds_int_enable[2].permission_flg;
	}

	IO_PRO.SEN.LVDS[ch].LVDSINTFLG0.word	= lvdsIntflg0.word;
	IO_PRO.SEN.LVDS[ch].LVDSINTENB0.word	= lvdsIntenb0.word;
	Im_Pro_Dsb();

	IO_PRO.SEN.LVDS[ch].LVDSINTFLG1.word	= lvdsIntflg1.word;
	IO_PRO.SEN.LVDS[ch].LVDSINTENB1.word	= lvdsIntenb1.word;
	Im_Pro_Dsb();

	IO_PRO.SEN.LVDS[ch].LVDSINTFLG2.word	= lvdsIntflg2.word;
	IO_PRO.SEN.LVDS[ch].LVDSINTENB2.word	= lvdsIntenb2.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
DMIPI Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear1_dmipi_set_interrupt( InterruptClear1*self,E_IM_PRO_DMIPI_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	union io_mpiinte mpiinte;
	union io_mpiintf mpiintf;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear1_dmipi_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear1_dmipi_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	mpiintf.word	= 0;
	mpiinte.word	= IO_PRO.SEN.MIPID[ch].MPIINTE.word;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DEC3)){
		mpiintf.bit.__DECF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DECE3	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DEC2)){
		mpiintf.bit.__DECF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DECE2	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DEC1)){
		mpiintf.bit.__DECF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DECE1	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DEC0)){
		mpiintf.bit.__DECF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DECE0	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DEE3)){
		mpiintf.bit.__DEEF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DEEE3	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DEE2)){
		mpiintf.bit.__DEEF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DEEE2	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DEE1)){
		mpiintf.bit.__DEEF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DEEE1	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DEE0)){
		mpiintf.bit.__DEEF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DEEE0	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DESSH3)){
		mpiintf.bit.__DESSHF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DESSHE3		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DESSH2)){
		mpiintf.bit.__DESSHF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DESSHE2		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DESSH1)){
		mpiintf.bit.__DESSHF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DESSHE1		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DESSH0)){
		mpiintf.bit.__DESSHF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DESSHE0		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DESHE3)){
		mpiintf.bit.__DESHF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DESHE3		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DESHE2)){
		mpiintf.bit.__DESHF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DESHE2		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DESHE1)){
		mpiintf.bit.__DESHF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DESHE1		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_DESHE0)){
		mpiintf.bit.__DESHF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.DESHE0		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_FEO1)){
		mpiintf.bit.__FEO1F	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.FEO1E	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_FEO0)){
		mpiintf.bit.__FEO0F	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.FEO0E	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_FEI1)){
		mpiintf.bit.__FEI1F	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.FEI1E	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_FEI0)){
		mpiintf.bit.__FEI0F	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.FEI0E	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_FSO1)){
		mpiintf.bit.__FSO1F	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.FSO1E	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_FSO0)){
		mpiintf.bit.__FSO0F	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.FSO0E	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_FSI1)){
		mpiintf.bit.__FSI1F	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.FSI1E	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_FSI0)){
		mpiintf.bit.__FSI0F	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.FSI0E	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_LZE3)){
		mpiintf.bit.__LZEF3	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.LZEE3	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_LZE2)){
		mpiintf.bit.__LZEF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.LZEE2	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_LZE1)){
		mpiintf.bit.__LZEF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.LZEE1	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_LZE0)){
		mpiintf.bit.__LZEF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.LZEE0	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_EFS)){
		mpiintf.bit.__EFSF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.EFSE	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_CRCE)){
		mpiintf.bit.__CRCEF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.CRCEE	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_ECCW)){
		mpiintf.bit.__ECCWF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.ECCWE	= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MPIINTE_ECCE)){
		mpiintf.bit.__ECCEF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpiinte.bit.ECCEE	= intCfg->permission_flg;
	}

	IO_PRO.SEN.MIPID[ch].MPIINTF.word	= mpiintf.word;
	IO_PRO.SEN.MIPID[ch].MPIINTE.word	= mpiinte.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

InterruptClear1 *interrupt_clear1_new(void)
{
	InterruptClear1* self = k_object_new_with_private(INTERRUPT_TYPE_CLEAR1,sizeof(InterruptClear1Private));
	return self;
}
