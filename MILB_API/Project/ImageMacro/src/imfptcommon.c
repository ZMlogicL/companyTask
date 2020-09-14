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
#include "ddimusercustomtest.h"
#include "imfptcommon.h"


G_DEFINE_TYPE(ImFptCommon, im_fpt_common, G_TYPE_OBJECT);
#define IM_FPT_COMMON_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_FPT_COMMON, ImFptCommonPrivate));


// NULL
#ifndef NULL
#define NULL	((void*)0x0)
#endif


struct _ImFptCommonPrivate
{
	gint a;
};


static void(*S_GFPT_CALLBACK[2])(guint32 intFactor, guchar ch) = {NULL, NULL };
volatile guchar GFptRresp[2] = { 0, 0 };
volatile guchar GFptWresp[2] = { 0, 0 };
/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
/**
 *IMPL
 */
static void 		im_fpt_common_class_init(ImFptCommonClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImFptCommonPrivate));
}

static void 		im_fpt_common_init(ImFptCommon *self)
{
	ImFptCommonPrivate *priv = IM_FPT_COMMON_GET_PRIVATE(self);
	self->fpt = im_fpt_new();
	self->ddimUserCustomTest = ddim_user_custom_new();
}

static void 		dispose_od(GObject *object)
{
	ImFptCommonPrivate *priv = IM_FPT_COMMON_GET_PRIVATE(object);
	ImFptCommon *self = im_fpt_common_new();
	if(self->fpt){
		g_object_unref(self->fpt);
		self->fpt = NULL;
	}
	if(self->ddimUserCustomTest){
		g_object_unref(self->ddimUserCustomTest);
		self->ddimUserCustomTest = NULL;
	}
	G_OBJECT_CLASS(im_fpt_common_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImFptCommonPrivate *priv = IM_FPT_COMMON_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_fpt_common_parent_class) -> dispose(object);
}
/**
 * PUBLIC
 */
/**
 * Configure mode.
 */
gint32 im_fpt_common_ctrl_mode_config(ImFptCommon*self, guchar ch, const TfptModeConfig* const param)
{
	IoFptFptctl2 fptctl2;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	im_fpt_on_pclk(self->fpt, ch);

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

	im_fpt_off_pclk(self->fpt, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *   Configure BRC(BRightness Correction) of the base image.
 */
gint32 im_fpt_common_ctrl_brc_config_base_img(ImFptCommon*self, guchar ch, const TfptBrcConfig* const param)
{
	IoFptFptctl4 fptctl4;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	fptctl4.word = 0;

	im_fpt_on_pclk(self->fpt, ch);

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

	im_fpt_off_pclk(self->fpt, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 * Configure BRC(BRightness Correction) of the target image.
 */
gint32 im_fpt_common_ctrl_brc_config_target_img(ImFptCommon*self, guchar ch, const TfptBrcConfig* const param)
{
	IoFptFptctl5 fptctl5;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	fptctl5.word = 0;

	im_fpt_on_pclk(self->fpt, ch);

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

	im_fpt_off_pclk(self->fpt, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *   Configure Interrupt.
 */
gint32 im_fpt_common_ctrl_interrupt(ImFptCommon*self, guchar ch, const TfptInterrupt* const param)
{
	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	im_fpt_on_pclk(self->fpt, ch);

	ioFpt[ch].fptinte0.word = param->flag;

	im_fpt_off_pclk(self->fpt, ch);

	S_GFPT_CALLBACK[ch] = param->callback;

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *  Configure LUTRAM.
 */
gint32 im_fpt_common_ctrl_lutram(ImFptCommon*self, guchar ch, gint32 lutSel, const guchar* lut)
{
	gint32 i;
	gulong regVal;
	gulong *pRegAddr;

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_RUNNING) {
		return ImFptCommon_D_IM_FPT_RETVAL_BUSY_ERR;
	}

	if(((lutSel != 0) &&(lutSel != 1)) ||(lut == NULL)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	pRegAddr =(lutSel == 0) ?(gulong*) &ioFptAhb[ch].fptlut0.word[0] :(gulong*) &ioFptAhb[ch].fptlut1.word[0];

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustomTest);
	im_fpt_on_hclk(self->fpt, ch);
	 // 64*4 = 256
	for(i = 0; i < 64; i++) {
		regVal =(gulong)((*lut++) << 0);
		regVal |=(gulong)((*lut++) << 8);
		regVal |=(gulong)((*lut++) << 16);
		regVal |=(gulong)((*lut++) << 24);
		*pRegAddr++ = regVal;
	}

	im_fpt_off_hclk(self->fpt, ch);
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustomTest);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *   Set REGRAM.
 */
gint32 im_fpt_common_set_regram(ImFptCommon*self, guchar ch, gint32 regSel, const guchar* reg)
{
	gint32 i;
	gulong regVal;
	gulong *pRegAddr;
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

	pRegAddr =(regSel == 0) ?(gulong*) &ioFptAhb[ch].fptreg0.word[0] :(gulong*) &ioFptAhb[ch].fptreg1.word[0];

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustomTest);
	im_fpt_on_hclk(self->fpt, ch);
	// 128*4 = 512
	for(i = 0; i < 128; i++) {
		regVal =(gulong)((*reg++) << 0);
		regVal |=(gulong)((*reg++) << 8);
		regVal |=(gulong)((*reg++) << 16);
		regVal |=(gulong)((*reg++) << 24);
		*pRegAddr++ = regVal;
	}

	im_fpt_off_hclk(self->fpt, ch);
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustomTest);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 *  Get REGRAM.
 */
gint32 im_fpt_common_get_regram(ImFptCommon*self, guchar ch, gint32 regSel, gulong* bufAddr)
{
	gint32 i;
	gulong *pRegAddr;
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

	pRegAddr =(regSel == 0) ?(gulong*) &ioFptAhb[ch].fptreg0.word[0] :(gulong*) &ioFptAhb[ch].fptreg1.word[0];

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustomTest);
	im_fpt_on_hclk(self->fpt, ch);
	// 128*4 = 512
	for(i = 0; i < 128; i++) {
		*bufAddr++ =(*pRegAddr++);
	}

	im_fpt_off_hclk(self->fpt, ch);
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustomTest);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 * Start FPT.
 */
gint32 im_fpt_common_start(ImFptCommon*self, guchar ch)
{
	gint32 retval;

	im_fpt_on_pclk(self->fpt, ch);
	im_fpt_on_hclk(self->fpt, ch);
	im_fpt_on_iclk(self->fpt, ch);

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {

		DdimUserCustom_ER ercd;

		ercd = ddim_user_custom_clr_flg(self->ddimUserCustomTest, FID_IM_FPT(ch), ~ImFptCommon_D_IM_FPT_USED_FLG_ALL);

		if( DdimUserCustom_E_OK != ercd) {
			im_fpt_off_iclk(self->fpt, ch);
			im_fpt_off_hclk(self->fpt, ch);
			im_fpt_off_pclk(self->fpt, ch);
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
gint32 im_fpt_common_stop(ImFptCommon*self, guchar ch)
{
	gint32 retval = ImFptCommon_D_IM_FPT_RETVAL_OK;

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {
		retval = ImFptCommon_D_IM_FPT_RETVAL_ERR;
	}
	else {
		DdimUserCustom_ER ercd;

		ioFpt[ch].fptctl1.word = ImFptCommon_D_IM_FPT_TRG_ABORT;
#ifdef CO_DEBUG_ON_PC
		ioFpt[ch].fptctl1.word = ImFptCommon_D_IM_FPT_TRG_STOPPED;
#endif
		ImFptCommon_IM_FPT_DUMMY_READ( ch );

		ercd = ddim_user_custom_set_flg(self->ddimUserCustomTest, FID_IM_FPT(ch), ImFptCommon_D_IM_FPT_ABORT_STOP);

		if(ercd == DdimUserCustom_E_OK) {
			retval = ImFptCommon_D_IM_FPT_RETVAL_OK;
		}
		else {
			retval = ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR;
		}
	}

	im_fpt_off_iclk(self->fpt, ch);
	im_fpt_off_hclk(self->fpt, ch);
	im_fpt_off_pclk(self->fpt, ch);

	return retval;
}

/**
 *  Wait end.
 */
gint32 im_fpt_common_waitend(ImFptCommon*self, guchar ch, guint32* status, gint32 waitTime)
{
	gint32 retval;

	if((status == NULL) ||(waitTime < -1)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	*status = 0;

	im_fpt_on_pclk(self->fpt, ch);

	if(ioFpt[ch].fptinte0.word & ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE) {
		// interrupt wait(open spec.)

		DdimUserCustom_ER ercd;
		DdimUserCustom_FLGPTN flgptn;

		ercd = ddim_user_custom_twai_flg(self->ddimUserCustomTest, FID_IM_FPT(ch), ImFptCommon_D_IM_FPT_USED_FLG_ALL, DdimUserCustom_TWF_ORW, &flgptn, waitTime);
		if( DdimUserCustom_E_OK == ercd) {
			*status = flgptn;
			retval = ImFptCommon_D_IM_FPT_RETVAL_OK;
		}
		else {
			retval = ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR;
		}
		ercd = ddim_user_custom_clr_flg(self->ddimUserCustomTest, FID_IM_FPT(ch), ~flgptn);
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

	im_fpt_off_pclk(self->fpt, ch);

	return retval;
}

/**
 * Interrupt Handler.
 */
gint32 im_fpt_common_int_handler(ImFptCommon*self, guchar ch)
{
	guint32 inte, intf;
	guint32 intFactor;
	DdimUserCustom_ER ercd;
	IoFptFptaxierr0 fptaxierr0;

	im_fpt_on_pclk(self->fpt, ch);

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

	im_fpt_off_pclk(self->fpt, ch);

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
		ercd = ddim_user_custom_set_flg(self->ddimUserCustomTest, FID_IM_FPT(ch),(intFactor));
		if( DdimUserCustom_E_OK != ercd) {
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
gint32 im_fpt_common_get_axi_response(ImFptCommon*self, guchar ch, guchar* readResponse, guchar* writeResponse)
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
void im_fpt_common_debugdump_all_registers(ImFptCommon*self, guchar ch, guint32 buf0Addr, guint32 buf1Addr)
{
	gint32 i;
	guint32 *regPtr;
	guint32 *dstPtr;

	if((buf0Addr & 0x3) ||(buf1Addr & 0x3) ||(buf0Addr == 0x0) ||(buf1Addr == 0x0)) {
		return;
	}

	// APB
	regPtr =(guint32*) &ioFpt[ch].fptctl0.word;
	dstPtr =(guint32*) buf0Addr;

	im_fpt_on_pclk(self->fpt, ch);

	for(i = 0; i < 64; i++) {
		*dstPtr++ = *regPtr++;
	}

	im_fpt_off_pclk(self->fpt, ch);

	// AHB
	regPtr =(guint32*) &ioFptAhb[ch].fptlut0.word[0];
	dstPtr =(guint32*) buf1Addr;

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustomTest);
	im_fpt_on_hclk(self->fpt, ch);

	for(i = 0; i < 128; i++) {
		*dstPtr++ = *regPtr++;
	}

	im_fpt_off_hclk(self->fpt, ch);
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustomTest);
}

/**
 *  Get version info.
 */
void im_fpt_common_get_version(ImFptCommon*self, gchar** str)
{
	*str = ImFptCommon_D_IM_FPT_VERSION;
}

ImFptCommon* 		im_fpt_common_new(void)
{
	ImFptCommon *self = g_object_new(IM_TYPE_FPT_COMMON, NULL);
	return self;
}
