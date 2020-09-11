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

#include "interruptclear2.h"
#include "interruptdefine.h"

#include "jdspro.h"
#include "im_pro.h"
#include "im_pro_common.h"
#include "dd_top.h"

K_TYPE_DEFINE_WITH_PRIVATE(InterruptClear2, interrupt_clear2);
#define INTERRUPT_CLEAR2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), InterruptClear2Private, INTERRUPT_TYPE_CLEAR2))

struct _InterruptClear2Private
{
	int a;
};


static void interrupt_clear2_constructor(InterruptClear2 *self)
{
	InterruptClear2Private *priv = INTERRUPT_CLEAR2_GET_PRIVATE(self);
	priv->a=0;
}

static void interrupt_clear2_destructor(InterruptClear2 *self)
{
	InterruptClear2Private *priv = INTERRUPT_CLEAR2_GET_PRIVATE(self);
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
CMIPI Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_cmipi_set_interrupt( InterruptClear2*self,E_IM_PRO_CMIPI_CH ch, T_IM_PRO_INT_CMIPI_CTRL* cmipiIntCtrl )
{
	union io_mpicinte1 mpicinte1;
	union io_mpicintf1 mpicintf1;
	union io_mpicinte2 mpicinte2;
	union io_mpicintf2 mpicintf2;

#ifdef CO_PARAM_CHECK
	if (cmipiIntCtrl == NULL){
		Ddim_Assertion(("I:interrupt_clear2_cmipi_set_interrupt error. cmipiIntCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (cmipiIntCtrl->cmipi_int1_enable.permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_cmipi_set_interrupt error. cmipi_int1_enable 'permission_flg' value over!! (%d)\n", cmipiIntCtrl->cmipi_int1_enable.permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (cmipiIntCtrl->cmipi_int2_enable.permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_cmipi_set_interrupt error. cmipi_int2_enable 'permission_flg' value over!! (%d)\n", cmipiIntCtrl->cmipi_int2_enable.permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	// MPICINTE1 interrupt enabled setting
	mpicintf1.word	= 0;
	mpicinte1.word	= IO_PRO.SEN.MIPIC[ch].MPICINTE1.word;

	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CEC2)){
		mpicintf1.bit.__CECF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CECE2		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CEC1)){
		mpicintf1.bit.__CECF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CECE1		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CEC0)){
		mpicintf1.bit.__CECF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CECE0		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CEE2)){
		mpicintf1.bit.__CEEF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CEEE2		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CEE1)){
		mpicintf1.bit.__CEEF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CEEE1		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CEE0)){
		mpicintf1.bit.__CEEF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CEEE0		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CESSH2)){
		mpicintf1.bit.__CESSHF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CESSHE2	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CESSH1)){
		mpicintf1.bit.__CESSHF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CESSHE1	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CESSH0)){
		mpicintf1.bit.__CESSHF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CESSHE0	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CESH2)){
		mpicintf1.bit.__CESHF2	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CESHE2	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CESH1)){
		mpicintf1.bit.__CESHF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CESHE1	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CESH0)){
		mpicintf1.bit.__CESHF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CESHE0	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_FEO1)){
		mpicintf1.bit.__FEO1F		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.FEO1E		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_FEO0)){
		mpicintf1.bit.__FEO0F		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.FEO0E		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_FEI1)){
		mpicintf1.bit.__FEI1F		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.FEI1E		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_FEI0)){
		mpicintf1.bit.__FEI0F		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.FEI0E		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_FSO1)){
		mpicintf1.bit.__FSO1F		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.FSO1E		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_FSO0)){
		mpicintf1.bit.__FSO0F		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.FSO0E		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_FSI1)){
		mpicintf1.bit.__FSI1F		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.FSI1E		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_FSI0)){
		mpicintf1.bit.__FSI0F		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.FSI0E		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_LZE2)){
		mpicintf1.bit.__LZEF2		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.LZEE2		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_LZE1)){
		mpicintf1.bit.__LZEF1		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.LZEE1		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_LZE0)){
		mpicintf1.bit.__LZEF0		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.LZEE0		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_EFS)){
		mpicintf1.bit.__EFSF		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.EFSE		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_CRCDTE)){
		mpicintf1.bit.__CRCDTEF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.CRCDTEE	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_PHCRC2E)){
		mpicintf1.bit.__PHCRC2EF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.PHCRC2EE	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int1_enable.interrupt_bit & D_IM_PRO_MPICINTE1_PHCRC1E)){
		mpicintf1.bit.__PHCRC1EF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte1.bit.PHCRC1EE	= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}

	// MPICINTE2 interrupt enabled setting
	mpicintf2.word	= 0;
	mpicinte2.word	= IO_PRO.SEN.MIPIC[ch].MPICINTE2.word;

	if (0 != (cmipiIntCtrl->cmipi_int2_enable.interrupt_bit & D_IM_PRO_MPICINTE2_CICHSE2)){
		mpicintf2.bit.__CICHSF2		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte2.bit.CICHSE2		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int2_enable.interrupt_bit & D_IM_PRO_MPICINTE2_CICHSE1)){
		mpicintf2.bit.__CICHSF1		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte2.bit.CICHSE1		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int2_enable.interrupt_bit & D_IM_PRO_MPICINTE2_CICHSE0)){
		mpicintf2.bit.__CICHSF0		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte2.bit.CICHSE0		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}
	if (0 != (cmipiIntCtrl->cmipi_int2_enable.interrupt_bit & D_IM_PRO_MPICINTE2_PHCRCAEE)){
		mpicintf2.bit.__PHCRCAEF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		mpicinte2.bit.PHCRCAEE		= cmipiIntCtrl->cmipi_int1_enable.permission_flg;
	}

	IO_PRO.SEN.MIPIC[ch].MPICINTF1.word	= mpicintf1.word;
	IO_PRO.SEN.MIPIC[ch].MPICINTE1.word	= mpicinte1.word;
	Im_Pro_Dsb();

	IO_PRO.SEN.MIPIC[ch].MPICINTF2.word	= mpicintf2.word;
	IO_PRO.SEN.MIPIC[ch].MPICINTE2.word	= mpicinte2.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
MONI Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_moni_set_interrupt( InterruptClear2*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_MONI_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	const T_IM_PRO_COMMON_MONI_INFO* moniInfo = 0;
	union io_moniintflg moniintflg;
	union io_moniintenb moniintenb;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_moni_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_moni_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_comm_get_moni_reg_info( unitNo, blockType, ch, &moniInfo );
#ifdef CO_PARAM_CHECK
	if (moniInfo->reg_ptr == NULL){
		Ddim_Assertion(("I:interrupt_clear2_moni_set_interrupt error. moniInfo->reg_ptr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unitNo, im_pro_convert_clk_type( blockType ) );
	moniintflg.word	= 0;
	moniintenb.word	= moniInfo->reg_ptr->MONIINTENB.word;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MONIINTENB_MONIHDE)){
		moniintflg.bit.__MONIHDF		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		moniintenb.bit.MONIHDE			= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MONIINTENB_MONIHDE)){
		moniintflg.bit.__MONIEPFF		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		moniintenb.bit.MONIEPFE			= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MONIINTENB_MONIHDE)){
		moniintflg.bit.__MONIEPLF		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		moniintenb.bit.MONIEPLE			= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MONIINTENB_MONIHDE)){
		moniintflg.bit.__MONIBLLMINF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		moniintenb.bit.MONIBLLMINE		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_MONIINTENB_MONIHDE)){
		moniintflg.bit.__MONIBLLMAXF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		moniintenb.bit.MONIBLLMAXE		= intCfg->permission_flg;
	}

	moniInfo->reg_ptr->MONIINTFLG.word	= moniintflg.word;
	moniInfo->reg_ptr->MONIINTENB.word	= moniintenb.word;
	Im_Pro_Dsb();
	im_pro_off_pclk( unitNo, im_pro_convert_clk_type( blockType ) );

	return D_DDIM_OK;
}

/**
LDIV Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_ldiv_set_interrupt( InterruptClear2*self,E_IM_PRO_LDIV_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	union  io_ldivintenb ldivintenb;
	union  io_ldivintflg ldivintflg;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_ldiv_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_ldiv_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ldivintflg.word	= 0;
	ldivintenb.word	= IO_PRO.SEN.LDIV[ch].LDIVINTENB.word;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_LDIVINTENB_LDIVEE)){
		ldivintflg.bit.__LDIVEF		= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		ldivintenb.bit.LDIVEE		= intCfg->permission_flg;
	}
	IO_PRO.SEN.LDIV[ch].LDIVINTFLG.word	= ldivintflg.word;
	IO_PRO.SEN.LDIV[ch].LDIVINTENB.word	= ldivintenb.word;
	Im_Pro_Dsb();
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
OBT Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_obt_set_interrupt( InterruptClear2*self,E_IM_PRO_OBT_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;
	union io_obtintenb obtintenb;
	union io_obtintflg obtintflg;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_obt_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_obt_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	im_pro_comm_get_obt_block_ch( ch, &blockNum, &chNum );

	obtintflg.word	= 0;
	obtintenb.word	= IO_PRO.SEN.OBT[blockNum][ch].OBTINTENB.word;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_OBTINTENB_OBTE)){
		obtintflg.bit.__OBTF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		obtintenb.bit.OBTE		= intCfg->permission_flg;
	}

	IO_PRO.SEN.OBT[blockNum][ch].OBTINTFLG.word	= obtintflg.word;
	IO_PRO.SEN.OBT[blockNum][ch].OBTINTENB.word	= obtintenb.word;
	Im_Pro_Dsb();
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
OBD Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_obd_set_interrupt( InterruptClear2*self,E_IM_PRO_OBD_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;
	union io_obdintenb obdintenb;
	union io_obdintflg obdintflg;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_obd_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_obd_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	im_pro_comm_get_obd_block_ch( ch, &blockNum, &chNum );

	obdintflg.word	= 0;
	obdintenb.word	= IO_PRO.SEN.OBD[blockNum][ch].OBDINTENB.word;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_OBDINTENB_OBDE)){
		obdintflg.bit.__OBDF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		obdintenb.bit.OBDE		= intCfg->permission_flg;
	}

	IO_PRO.SEN.OBD[blockNum][ch].OBDINTFLG.word	= obdintflg.word;
	IO_PRO.SEN.OBD[blockNum][ch].OBDINTENB.word	= obdintenb.word;
	Im_Pro_Dsb();
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
SROTOP Interrupt setting
@param[in]	unitNo : Unit number.
@param[in]	intCtrl : SROTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear2_srotop_interrupt_ctrl( InterruptClear2*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_SROTOP_CTRL* intCtrl )
{
	union io_srovhdintenb	vhdintenb;
	union io_srovhdintflg	vhdintflg;

#ifdef CO_PARAM_CHECK
	if (intCtrl == NULL){
		Ddim_Assertion(("I:interrupt_clear2_srotop_interrupt_ctrl error. intCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (( intCtrl->vd_enable[0].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->vd_enable[1].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->hd_enable[0].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->hd_enable[1].permission_flg > D_IM_PRO_FUNC_EN )
		) {
		Ddim_Assertion(("I:interrupt_clear2_srotop_interrupt_ctrl error. 'permission_flg' value over!! (VD0:%d VD1:%d HD0:%d HD1:%d)\n"	, intCtrl->vd_enable[0].permission_flg
																																, intCtrl->vd_enable[1].permission_flg
																																, intCtrl->hd_enable[0].permission_flg
																																, intCtrl->hd_enable[1].permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	vhdintenb.word	= IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTENB.word;
	vhdintflg.word	= 0;

	// VHDINTENB VD Interrupt
	if (0 != (intCtrl->vd_enable[0].interrupt_bit & D_IM_PRO_SROTOP_INT_VDE0)){
		vhdintflg.bit.__VDF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.VDE0		= intCtrl->vd_enable[0].permission_flg;
	}
	if (0 != (intCtrl->vd_enable[1].interrupt_bit & D_IM_PRO_SROTOP_INT_VDE1)){
		vhdintflg.bit.__VDF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.VDE1		= intCtrl->vd_enable[1].permission_flg;
	}
	// VHDINTENB HD Interrupt
	if (0 != (intCtrl->hd_enable[0].interrupt_bit & D_IM_PRO_SROTOP_INT_HDE0)){
		vhdintflg.bit.__HDF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.HDE0		= intCtrl->hd_enable[0].permission_flg;
	}
	if (0 != (intCtrl->hd_enable[1].interrupt_bit & D_IM_PRO_SROTOP_INT_HDE1)){
		vhdintflg.bit.__HDF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.HDE1		= intCtrl->hd_enable[1].permission_flg;
	}

	IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.INTCTL.bit.INTMD	= intCtrl->int_mode;
	IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTFLG.word		= vhdintflg.word;
	IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTENB.word		= vhdintenb.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Set SDC Interrupt flg
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel<br>
	 			 value range:[0 - 1]<br>
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK				:setting ok
@retval		D_IM_PRO_PARAM_ERROR	:setting ng
*/
INT32 interrupt_clear2_sdc_set_interrupt( InterruptClear2*self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	union io_sdcintenb sdcintenb;
	union io_sdcintflg sdcintflg;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_sdc_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_sdc_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	sdcintflg.word	= 0;
	sdcintenb.word	= IO_PRO.IMG_PIPE[unitNo].SRO.SDC[ch].SDCINTENB.word;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_SDCINTENB_SDCE)){
		sdcintflg.bit.__SDCF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		sdcintenb.bit.SDCE		= intCfg->permission_flg;
	}

	IO_PRO.IMG_PIPE[unitNo].SRO.SDC[ch].SDCINTFLG.word	= sdcintflg.word;
	IO_PRO.IMG_PIPE[unitNo].SRO.SDC[ch].SDCINTENB.word	= sdcintenb.word;
	Im_Pro_Dsb();
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
B2BTOP Interrupt setting
@param[in]	unitNo : Unit number.
@param[in]	intCtrl : B2BTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear2_b2btop_interrupt_ctrl( InterruptClear2*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_B2BTOP_CTRL* intCtrl )
{
	union io_b2b_vhdintenb	vhdintenb;
	union io_b2b_vhdintflg	vhdintflg;

#ifdef CO_PARAM_CHECK
	if (intCtrl == NULL){
		Ddim_Assertion(("I:interrupt_clear2_b2btop_interrupt_ctrl error. intCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (( intCtrl->vd_enable[0].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->vd_enable[1].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->hd_enable[0].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->hd_enable[1].permission_flg > D_IM_PRO_FUNC_EN )
		) {
		Ddim_Assertion(("I:interrupt_clear2_b2btop_interrupt_ctrl error. 'permission_flg' value over!! (VD0:%d VD1:%d HD0:%d HD1:%d)\n"	, intCtrl->vd_enable[0].permission_flg
																																, intCtrl->vd_enable[1].permission_flg
																																, intCtrl->hd_enable[0].permission_flg
																																, intCtrl->hd_enable[1].permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );
	vhdintenb.word	= IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTENB.word;
	vhdintflg.word	= 0;

	// VHDINTENB VD Interrupt
	if (0 != (intCtrl->vd_enable[0].interrupt_bit & D_IM_PRO_B2BTOP_INT_VDE0)){
		vhdintflg.bit.__VDF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.VDE0		= intCtrl->vd_enable[0].permission_flg;
	}
	if (0 != (intCtrl->vd_enable[1].interrupt_bit & D_IM_PRO_B2BTOP_INT_VDE1)){
		vhdintflg.bit.__VDF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.VDE1		= intCtrl->vd_enable[1].permission_flg;
	}
	// VHDINTENB HD Interrupt
	if (0 != (intCtrl->hd_enable[0].interrupt_bit & D_IM_PRO_B2BTOP_INT_HDE0)){
		vhdintflg.bit.__HDF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.HDE0		= intCtrl->hd_enable[0].permission_flg;
	}
	if (0 != (intCtrl->hd_enable[1].interrupt_bit & D_IM_PRO_B2BTOP_INT_HDE1)){
		vhdintflg.bit.__HDF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.HDE1		= intCtrl->hd_enable[1].permission_flg;
	}

	IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.INTCTL.bit.INTMD	= intCtrl->int_mode;
	IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTFLG.word		= vhdintflg.word;
	IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTENB.word		= vhdintenb.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );

	return D_DDIM_OK;
}

/**
AEAWB Macro interrupt permission set
@param[in]	ch : channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_aeawb_set_interrupt( InterruptClear2*self,E_IM_PRO_AEAWB_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	union io_lineintenb lineintenb;
	union io_lineintflg lineintflg;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_obd_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_obd_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
	lineintflg.word	= 0;
	lineintenb.word	= IO_PRO.STAT.AEAWB[ch].LINEINTENB.word;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_LINEINTENB_LINEE)){
		lineintflg.bit.__LINEF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		lineintenb.bit.LINEE	= intCfg->permission_flg;
	}

	IO_PRO.STAT.AEAWB[ch].LINEINTFLG.word	= lineintflg.word;
	IO_PRO.STAT.AEAWB[ch].LINEINTENB.word	= lineintenb.word;
	Im_Pro_Dsb();
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	return D_DDIM_OK;
}

/**
AF Macro interrupt permission set
@param[in]	ch : channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_af_set_interrupt( InterruptClear2*self,E_IM_PRO_AF_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	union io_afintenb afintenb;
	union io_afintflg afintflg;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_af_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_af_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
	afintenb.word	= IO_PRO.STAT.AF[ch].AFGBAL.AFINTENB.word;
	afintflg.word	= 0;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_AFINTENB_AFE)){
		afintflg.bit.__AFF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		afintenb.bit.AFE	= intCfg->permission_flg;
	}

	IO_PRO.STAT.AF[ch].AFGBAL.AFINTFLG.word	= afintflg.word;
	IO_PRO.STAT.AF[ch].AFGBAL.AFINTENB.word	= afintenb.word;
	Im_Pro_Dsb();
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	return D_DDIM_OK;
}

/**
HIST Macro interrupt permission set
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_hist_set_interrupt( InterruptClear2*self,E_IM_PRO_HIST_CH ch, T_IM_PRO_INT_CFG* intCfg )
{
	union io_histintenb histintenb;
	union io_histintflg histintflg;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_hist_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_hist_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
	histintenb.word	= IO_PRO.STAT.HIST[ch].HISTINTENB.word;
	histintflg.word	= 0;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_HISTINTENB_HISTE)){
		histintflg.bit.__HISTF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		histintenb.bit.HISTE	= intCfg->permission_flg;
	}

	IO_PRO.STAT.HIST[ch].HISTINTFLG.word	= histintflg.word;
	IO_PRO.STAT.HIST[ch].HISTINTENB.word	= histintenb.word;
	Im_Pro_Dsb();
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	return D_DDIM_OK;
}

/**
PASTOP Interrupt setting
@param[in]	intCtrl : PASTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear2_pastop_interrupt_ctrl( InterruptClear2*self,T_IM_PRO_INT_PASTOP_CTRL* intCtrl )
{
	union io_pas_vhdintenb	vhdintenb;
	union io_pas_vhdintflg	vhdintflg;

#ifdef CO_PARAM_CHECK
	if (intCtrl == NULL){
		Ddim_Assertion(("I:interrupt_clear2_pastop_interrupt_ctrl error. intCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (( intCtrl->vd_enable[0].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->vd_enable[1].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->hd_enable[0].permission_flg > D_IM_PRO_FUNC_EN ) ||
		( intCtrl->hd_enable[1].permission_flg > D_IM_PRO_FUNC_EN )
		) {
		Ddim_Assertion(("I:interrupt_clear2_pastop_interrupt_ctrl error. 'permission_flg' value over!! (VD0:%d VD1:%d HD0:%d HD1:%d)\n"	, intCtrl->vd_enable[0].permission_flg
																																, intCtrl->vd_enable[1].permission_flg
																																, intCtrl->hd_enable[0].permission_flg
																																, intCtrl->hd_enable[1].permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	vhdintenb.word	= IO_PRO.PAS.PASTOP.VHDINTENB.word;
	vhdintflg.word	= 0;

	// VHDINTENB VD Interrupt
	if (0 != (intCtrl->vd_enable[0].interrupt_bit & D_IM_PRO_PASTOP_INT_VDE0)){
		vhdintflg.bit.__VDF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.VDE0		= intCtrl->vd_enable[0].permission_flg;
	}
	if (0 != (intCtrl->vd_enable[1].interrupt_bit & D_IM_PRO_PASTOP_INT_VDE1)){
		vhdintflg.bit.__VDF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.VDE1		= intCtrl->vd_enable[1].permission_flg;
	}
	// VHDINTENB HD Interrupt
	if (0 != (intCtrl->hd_enable[0].interrupt_bit & D_IM_PRO_PASTOP_INT_HDE0)){
		vhdintflg.bit.__HDF0	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.HDE0		= intCtrl->hd_enable[0].permission_flg;
	}
	if (0 != (intCtrl->hd_enable[1].interrupt_bit & D_IM_PRO_PASTOP_INT_HDE1)){
		vhdintflg.bit.__HDF1	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		vhdintenb.bit.HDE1		= intCtrl->hd_enable[1].permission_flg;
	}

	IO_PRO.PAS.PASTOP.INTCTL.bit.INTMD	= intCtrl->int_mode;
	IO_PRO.PAS.PASTOP.VHDINTFLG.word	= vhdintflg.word;
	IO_PRO.PAS.PASTOP.VHDINTENB.word	= vhdintenb.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	return D_DDIM_OK;
}

/**
PWch Macro interrupt permission set
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch	 : PWch channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_pwch_set_interrupt( InterruptClear2*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PWCH ch, T_IM_PRO_INT_CFG* intCfg )
{
	union io_pwchintenb pwchintenb;
	union io_pwchintflg pwchintflg;
	const T_IM_PRO_COMMON_PWCH_INFO* pwch_reg_info = 0;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_pwch_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_pwch_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwch_reg_info );
#ifdef CO_PARAM_CHECK
	if (pwch_reg_info->reg_ptr == NULL){
		Ddim_Assertion(("I:interrupt_clear2_pwch_set_interrupt error. pwch_reg_info->reg_ptr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unitNo, im_pro_convert_clk_type( blockType ) );

	pwchintenb.word	= pwch_reg_info->reg_ptr->PWCHINTENB.word;
	pwchintflg.word	= 0;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_PWCHINTENB_PWE)){
		pwchintflg.bit.__PWF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		pwchintenb.bit.PWE		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_PWCHINTENB_PWEE)){
		pwchintflg.bit.__PWEF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		pwchintenb.bit.PWEE		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_PWCHINTENB_PWXE)){
		pwchintflg.bit.__PWXF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		pwchintenb.bit.PWXE		= intCfg->permission_flg;
	}

	pwch_reg_info->reg_ptr->PWCHINTFLG.word	= pwchintflg.word;
	pwch_reg_info->reg_ptr->PWCHINTENB.word	= pwchintenb.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( unitNo, im_pro_convert_clk_type( blockType ) );

	return D_DDIM_OK;
}

/**
The permission setting of the PRch interrupt control is done.
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch : PRch channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_prch_set_interrupt( InterruptClear2*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PRCH ch, T_IM_PRO_INT_CFG* intCfg )
{
	union io_prchintenb prchintenb;
	union io_prchintflg prchintflg;
	const T_IM_PRO_COMMON_PRCH_INFO* prch_reg_info = 0;

#ifdef CO_PARAM_CHECK
	if (intCfg == NULL){
		Ddim_Assertion(("I:interrupt_clear2_pwch_set_interrupt error. intCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (intCfg->permission_flg > D_IM_PRO_FUNC_EN){
		Ddim_Assertion(("I:interrupt_clear2_pwch_set_interrupt error. 'permission_flg' value over!! (%d)\n", intCfg->permission_flg));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prch_reg_info );
#ifdef CO_PARAM_CHECK
	if (prch_reg_info->reg_ptr == NULL){
		Ddim_Assertion(("I:interrupt_clear2_prch_set_interrupt error. prch_reg_info->reg_ptr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unitNo, im_pro_convert_clk_type( blockType ) );

	prchintenb.word	= prch_reg_info->reg_ptr->PRCHINTENB.word;
	prchintflg.word	= 0;

	if (0 != (intCfg->interrupt_bit & D_IM_PRO_PRCHINTENB_PRE)){
		prchintflg.bit.__PRF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		prchintenb.bit.PRE		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_PRCHINTENB_PREE)){
		prchintflg.bit.__PREF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		prchintenb.bit.PREE		= intCfg->permission_flg;
	}
	if (0 != (intCfg->interrupt_bit & D_IM_PRO_PRCHINTENB_PRXE)){
		prchintflg.bit.__PRXF	= InterruptDefine_D_IM_PRO_INTFLG_CLEAR;
		prchintenb.bit.PRXE		= intCfg->permission_flg;
	}

	prch_reg_info->reg_ptr->PRCHINTFLG.word	= prchintflg.word;
	prch_reg_info->reg_ptr->PRCHINTENB.word	= prchintenb.word;
	Im_Pro_Dsb();

	im_pro_off_pclk( unitNo, im_pro_convert_clk_type( blockType ) );

	return D_DDIM_OK;
}

InterruptClear2 *interrupt_clear2_new(void)
{
	InterruptClear2* self = k_object_new_with_private(INTERRUPT_TYPE_CLEAR2,sizeof(InterruptClear2Private));
	return self;
}
