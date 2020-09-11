/*
 *
*@Copyright(C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-07
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#include <MILB_Header/Project/Image/src/kjdsfpt.h>
#include "imfpt.h"
#include "ddarm.h"
#include "ddimusercustom.h"
#include "imfptcommon.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImFptCommon, im_fpt_common);
#define IM_FPT_COMMON_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImFptCommonPrivate, IM_TYPE_FPT_COMMON))


// NULL
#ifndef NULL
#define NULL	((void*)0x0)
#endif


struct _ImFptCommonPrivate
{
	kint a;
};


static void(*S_GFPT_CALLBACK[2])(kuint32 intFactor, kuchar ch) = {NULL, NULL };
volatile kuchar GFptRresp[2] = { 0, 0 };
volatile kuchar GFptWresp[2] = { 0, 0 };
/**
 *IMPL
 */
static void im_fpt_common_constructor(ImFptCommon *self)
{
//	ImFptCommonPrivate *priv = IM_FPT_COMMON_GET_PRIVATE(self);
}

static void im_fpt_common_destructor(ImFptCommon *self)
{
//	ImFptCommonPrivate *priv = IM_FPT_COMMON_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
/**
 * Configure mode.
 */
kint32 im_fpt_ctrl_mode_config(ImFptCommon*self, kuchar ch, const TfptModeConfig* const param)
{
	IoFptFptctl2 fptctl2;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	im_fpt_on_pclk(NULL, ch);

	fptctl2.word = ioFpt[ch].fptctl2.word;

	switch(param->imIoMode) {
		case ImFptCommon_E_IM_FPT_IO_MODE_SDRAM:
			fptctl2.bit.ioMode = ImFptCommon_D_IM_FPT_IO_MODE_SDRAM;
			break;
		case ImFptCommon_E_IM_FPT_IO_MODE_REGISTER:
			fptctl2.bit.ioMode = ImFptCommon_D_IM_FPT_IO_MODE_REGISTER;
			break;
		default:
			return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	switch(param->imPipeEn) {
		case ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE:
			fptctl2.bit.pipeEn = ImFptCommon_D_IM_FPT_PIPE_DISABLE;
			break;
		case ImFptCommon_E_IM_FPT_PIPE_EN_ENABLE:
			fptctl2.bit.pipeEn = ImFptCommon_D_IM_FPT_PIPE_ENABLE;
			break;
		default:
			return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	switch(param->imDebugMode) {
		case ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL:
			fptctl2.bit.debugMode = ImFptCommon_D_IM_FPT_NORMAL_MODE;
			break;
		case ImFptCommon_E_IM_FPT_DEBUG_MODE_DEBUG:
			fptctl2.bit.debugMode = ImFptCommon_D_IM_FPT_DEBUG_MODE;
			break;
		default:
			return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	ioFpt[ch].fptctl2.word = fptctl2.word;

	im_fpt_off_pclk(NULL, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *   Configure BRC(BRightness Correction) of the base image.
 */
kint32 im_fpt_ctrl_brc_config_base_img(ImFptCommon*self, kuchar ch, const TfptBrcConfig* const param)
{
	IoFptFptctl4 fptctl4;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	fptctl4.word = 0;

	im_fpt_on_pclk(NULL, ch);

	if(ioFpt[ch].fptctl3.word &= ImFptCommon_D_IM_FPT_LUT_ON) {
		fptctl4.bit.offsetB = param->imgOffset;
		fptctl4.bit.clpmaxB = param->imClipMax;
		fptctl4.bit.clpminB = param->imgClipMin;
		ioFpt[ch].fptctl4.word = fptctl4.word;
	}
	else {
		fptctl4.bit.offsetB = ImFptCommon_D_IM_FPT_OFFSET_OFF;
		fptctl4.bit.clpmaxB = ImFptCommon_D_IM_FPT_CLIP_MAX_OFF;
		fptctl4.bit.clpminB = ImFptCommon_D_IM_FPT_CLIP_MIN_OFF;
		ioFpt[ch].fptctl4.word = fptctl4.word;
	}

	im_fpt_off_pclk(NULL, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 * Configure BRC(BRightness Correction) of the target image.
 */
kint32 im_fpt_ctrl_brc_config_target_img(ImFptCommon*self, kuchar ch, const TfptBrcConfig* const param)
{
	IoFptFptctl5 fptctl5;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	fptctl5.word = 0;

	im_fpt_on_pclk(NULL, ch);

	if(ioFpt[ch].fptctl3.word &= ImFptCommon_D_IM_FPT_LUT_ON) {
		fptctl5.bit.offsetT = param->imgOffset;
		fptctl5.bit.clpmaxT = param->imClipMax;
		fptctl5.bit.clpminT = param->imgClipMin;
		ioFpt[ch].fptctl5.word = fptctl5.word;
	}
	else {
		fptctl5.bit.offsetT = ImFptCommon_D_IM_FPT_OFFSET_OFF;
		fptctl5.bit.clpmaxT = ImFptCommon_D_IM_FPT_CLIP_MAX_OFF;
		fptctl5.bit.clpminT = ImFptCommon_D_IM_FPT_CLIP_MIN_OFF;
		ioFpt[ch].fptctl5.word = fptctl5.word;
	}

	im_fpt_off_pclk(NULL, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *   Configure Interrupt.
 */
kint32 im_fpt_ctrl_interrupt(ImFptCommon*self, kuchar ch, const TfptInterrupt* const param)
{
	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	im_fpt_on_pclk(NULL, ch);

	ioFpt[ch].fptinte0.word = param->flag;

	im_fpt_off_pclk(NULL, ch);

	S_GFPT_CALLBACK[ch] = param->callback;

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *  Configure LUTRAM.
 */
kint32 im_fpt_ctrl_lutram(ImFptCommon*self, kuchar ch, kint32 lutSel, const kuchar* lut)
{
	kint32 i;
	kulong regVal;
	kulong *pRegAddr;

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_RUNNING) {
		return ImFptCommon_D_IM_FPT_RETVAL_BUSY_ERR;
	}

	if(((lutSel != 0) &&(lutSel != 1)) ||(lut == NULL)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	pRegAddr =(lutSel == 0) ?(kulong*) &ioFptAhb[ch].fptlut0.word[0] :(kulong*) &ioFptAhb[ch].fptlut1.word[0];

	DDIM_User_AhbReg_SpinLock();
	im_fpt_on_hclk(NULL, ch);
	 // 64*4 = 256
	for(i = 0; i < 64; i++) {
		regVal =(kulong)((*lut++) << 0);
		regVal |=(kulong)((*lut++) << 8);
		regVal |=(kulong)((*lut++) << 16);
		regVal |=(kulong)((*lut++) << 24);
		*pRegAddr++ = regVal;
	}

	im_fpt_off_hclk(NULL, ch);
	DDIM_User_AhbReg_SpinUnLock();

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *   Set REGRAM.
 */
kint32 im_fpt_set_regram(ImFptCommon*self, kuchar ch, kint32 regSel, const kuchar* reg)
{
	kint32 i;
	kulong regVal;
	kulong *pRegAddr;
	IoFptFptctl2 fptctl2;

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_RUNNING) {
		return ImFptCommon_D_IM_FPT_RETVAL_BUSY_ERR;
	}

	fptctl2.word = ioFpt[ch].fptctl2.word;

	/* pgr0872 */
	if(fptctl2.bit.ioMode != 1) {
		return ImFptCommon_D_IM_FPT_RETVAL_ERR;
	}

	if(((regSel != 0) &&(regSel != 1)) ||(reg == NULL)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	pRegAddr =(regSel == 0) ?(kulong*) &ioFptAhb[ch].fptreg0.word[0] :(kulong*) &ioFptAhb[ch].fptreg1.word[0];

	DDIM_User_AhbReg_SpinLock();
	im_fpt_on_hclk(NULL, ch);
	// 128*4 = 512
	for(i = 0; i < 128; i++) {
		regVal =(kulong)((*reg++) << 0);
		regVal |=(kulong)((*reg++) << 8);
		regVal |=(kulong)((*reg++) << 16);
		regVal |=(kulong)((*reg++) << 24);
		*pRegAddr++ = regVal;
	}

	im_fpt_off_hclk(NULL, ch);
	DDIM_User_AhbReg_SpinUnLock();

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *  Get REGRAM.
 */
kint32 im_fpt_get_regram(ImFptCommon*self, kuchar ch, kint32 regSel, kulong* bufAddr)
{
	kint32 i;
	kulong *pRegAddr;
	IoFptFptctl2 fptctl2;

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_RUNNING) {
		return ImFptCommon_D_IM_FPT_RETVAL_BUSY_ERR;
	}

	fptctl2.word = ioFpt[ch].fptctl2.word;

	/* pgr0872 */
	if(fptctl2.bit.ioMode != 1) {
		return ImFptCommon_D_IM_FPT_RETVAL_ERR;
	}

	if(((regSel != 0) &&(regSel != 1)) ||(bufAddr == NULL)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	pRegAddr =(regSel == 0) ?(kulong*) &ioFptAhb[ch].fptreg0.word[0] :(kulong*) &ioFptAhb[ch].fptreg1.word[0];

	DDIM_User_AhbReg_SpinLock();
	im_fpt_on_hclk(NULL, ch);
	// 128*4 = 512
	for(i = 0; i < 128; i++) {
		*bufAddr++ =(*pRegAddr++);
	}

	im_fpt_off_hclk(NULL, ch);
	DDIM_User_AhbReg_SpinUnLock();

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 * Start FPT.
 */
kint32 im_fpt_start(ImFptCommon*self, kuchar ch)
{
	kint32 retval;

	im_fpt_on_pclk(NULL, ch);
	im_fpt_on_hclk(NULL, ch);
	im_fpt_on_iclk(NULL, ch);

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {

		DDIM_USER_ER ercd;

		ercd = DDIM_User_Clr_Flg(FID_IM_FPT(ch), ~ImFptCommon_D_IM_FPT_USED_FLG_ALL);

		if( D_DDIM_USER_E_OK != ercd) {
			im_fpt_off_iclk(NULL, ch);
			im_fpt_off_hclk(NULL, ch);
			im_fpt_off_pclk(NULL, ch);
			return ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR;
		}

		ioFpt[ch].fptctl1.word = ImFptCommon_D_IM_FPT_TRG_START;
#ifdef CO_DEBUG_ON_PC
		ioFpt[ch].fptctl1.word = ImFptCommon_D_IM_FPT_TRG_RUNNING;
#endif

		retval = ImFptCommon_D_IM_FPT_RETVAL_OK;
	}
	else {
		retval = ImFptCommon_D_IM_FPT_RETVAL_ERR;
	}

	return retval;
}

/**
 * Force stop FPT.
 */
kint32 im_fpt_stop(ImFptCommon*self, kuchar ch)
{
	kint32 retval = ImFptCommon_D_IM_FPT_RETVAL_OK;

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {
		retval = ImFptCommon_D_IM_FPT_RETVAL_ERR;
	}
	else {
		DDIM_USER_ER ercd;

		ioFpt[ch].fptctl1.word = ImFptCommon_D_IM_FPT_TRG_ABORT;
#ifdef CO_DEBUG_ON_PC
		ioFpt[ch].fptctl1.word = ImFptCommon_D_IM_FPT_TRG_STOPPED;
#endif
		ImFptCommon_IM_FPT_DUMMY_READ( ch );

		ercd = DDIM_User_Set_Flg(FID_IM_FPT(ch), ImFptCommon_D_IM_FPT_ABORT_STOP);

		if(ercd == D_DDIM_USER_E_OK) {
			retval = ImFptCommon_D_IM_FPT_RETVAL_OK;
		}
		else {
			retval = ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR;
		}
	}

	im_fpt_off_iclk(NULL, ch);
	im_fpt_off_hclk(NULL, ch);
	im_fpt_off_pclk(NULL, ch);

	return retval;
}

/**
 *  Wait end.
 */
kint32 im_fpt_waitend(ImFptCommon*self, kuchar ch, kuint32* status, kint32 waitTime)
{
	kint32 retval;

	if((status == NULL) ||(waitTime < -1)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	*status = 0;

	im_fpt_on_pclk(NULL, ch);

	if(ioFpt[ch].fptinte0.word & ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE) {
		// interrupt wait(open spec.)

		DDIM_USER_ER ercd;
		DDIM_USER_FLGPTN flgptn;

		ercd = DDIM_User_Twai_Flg(FID_IM_FPT(ch), ImFptCommon_D_IM_FPT_USED_FLG_ALL, D_DDIM_USER_TWF_ORW, &flgptn, waitTime);
		if( D_DDIM_USER_E_OK == ercd) {
			*status = flgptn;
			retval = ImFptCommon_D_IM_FPT_RETVAL_OK;
		}
		else {
			retval = ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR;
		}
		ercd = DDIM_User_Clr_Flg(FID_IM_FPT(ch), ~flgptn);
	}
	else {
		// polling wait(closed spec.)
		do {
			if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {
				break;
			}
		}
		while(1);

		retval = ImFptCommon_D_IM_FPT_RETVAL_OK;
	}

	im_fpt_off_pclk(NULL, ch);

	return retval;
}

/**
 * Interrupt Handler.
 */
kint32 im_fpt_int_handler(ImFptCommon*self, kuchar ch)
{
	kuint32 inte, intf;
	kuint32 intFactor;
	DDIM_USER_ER ercd;
	IoFptFptaxierr0 fptaxierr0;

	im_fpt_on_pclk(NULL, ch);

	inte = ioFpt[ch].fptinte0.word;
	intf = ioFpt[ch].fptintf0.word;
	if(intf & ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR) {
		fptaxierr0.word = ioFpt[ch].fptaxierr0.word;
		/* pgr0872 */
		GFptRresp[ch] = fptaxierr0.bit.rresp;
		/* pgr0872 */
		GFptWresp[ch] = fptaxierr0.bit.wresp;
	}
	else {
		GFptRresp[ch] = 0;
		GFptWresp[ch] = 0;
	}
	ioFpt[ch].fptintf0.word = intf;
	ImFptCommon_IM_FPT_DUMMY_READ( ch );

	im_fpt_off_pclk(NULL, ch);

	intFactor = 0;

	if((inte & ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE) &&(intf & ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE)) {
		intFactor |= ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE;
	}

	if(intf & ImFptCommon_D_IM_FPT_INTERRUPT_ERR) {
		if((inte & ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR) &&(intf & ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR)) {
			intFactor |= ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR;
		}

		if((inte & ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR) &&(intf & ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR)) {
			intFactor |= ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR;
		}
	}

	if(intFactor) {
		ercd = DDIM_User_Set_Flg(FID_IM_FPT(ch),(intFactor));
		if( D_DDIM_USER_E_OK != ercd) {
			return ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR;
		}
	}

	if(S_GFPT_CALLBACK[ch] != NULL) {
		S_GFPT_CALLBACK[ch](intFactor, ch);
	}

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *  Get AXI response.
 */
kint32 im_fpt_get_axi_response(ImFptCommon*self, kuchar ch, kuchar* readResponse, kuchar* writeResponse)
{
	if((readResponse == NULL) ||(writeResponse == NULL)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	*readResponse = GFptRresp[ch];
	*writeResponse = GFptWresp[ch];

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *  Dump the value of all FPT's register.
 */
void im_fpt_debugdump_all_registers(ImFptCommon*self, kuchar ch, kuint32 buf0_addr, kuint32 buf1_addr)
{
	kint32 i;
	kuint32 *regPtr;
	kuint32 *dstPtr;

	if((buf0_addr & 0x3) ||(buf1_addr & 0x3) ||(buf0_addr == 0x0) ||(buf1_addr == 0x0)) {
		return;
	}

	// APB
	regPtr =(kuint32*) &ioFpt[ch].fptctl0.word;
	dstPtr =(kuint32*) buf0_addr;

	im_fpt_on_pclk(NULL, ch);

	for(i = 0; i < 64; i++) {
		*dstPtr++ = *regPtr++;
	}

	im_fpt_off_pclk(NULL, ch);

	// AHB
	regPtr =(kuint32*) &ioFptAhb[ch].fptlut0.word[0];
	dstPtr =(kuint32*) buf1_addr;

	DDIM_User_AhbReg_SpinLock();
	im_fpt_on_hclk(ch);

	for(i = 0; i < 128; i++) {
		*dstPtr++ = *regPtr++;
	}

	im_fpt_off_hclk(NULL, ch);
	DDIM_User_AhbReg_SpinUnLock();
}

/**
 *  Get version info.
 */
void im_fpt_get_version(ImFptCommon*self, kchar** str)
{
	*str = ImFptCommon_D_IM_FPT_VERSION;
}

ImFptCommon* im_fpt_common_new(void)
{
	ImFptCommon *self = k_object_new_with_private(IM_TYPE_FPT_COMMON, sizeof(ImFptCommonPrivate));
	return self;
}
