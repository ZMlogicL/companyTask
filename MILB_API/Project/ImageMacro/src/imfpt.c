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
#include "ddarm.h"
#include "ddtop.h"
#include "ddimusercustomtest.h"
#include "imfpt.h"


G_DEFINE_TYPE(ImFpt, im_fpt, G_TYPE_OBJECT);
#define IM_FPT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_FPT, ImFptPrivate));


// NULL
#ifndef NULL
#define NULL	((void*)0x0)
#endif

/*----------------------------------------------------------------------	*/
/* Structure																		*/
/*----------------------------------------------------------------------	*/
//---------------------------- driver section -------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section -------------------------
// Nothing Special
#endif
struct _ImFptPrivate
{
	gulong lock;
	gulong dummy[(64 / 4) - 1];
	ImFpt *fpt;
};


#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------	*/
/* Local Method Definition											*/
/*----------------------------------------------------------------------	*/
//---------------------------- driver section ----------------------------
/* Nothing Special */

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------	*/
/* Global variables															*/
/*----------------------------------------------------------------------	*/
#ifdef ImFptCommon_CO_ACT_FPT_CLOCK
volatile guchar GFptImFptclkCounter[2] = {0, 0};
#endif	// ImFptCommon_CO_ACT_FPT_CLOCK
#ifdef ImFptCommon_CO_ACT_FPT_PCLOCK
volatile guchar GFptPclkCounter[2] = {0, 0};
#endif	// ImFptCommon_CO_ACT_FPT_PCLOCK
#ifdef ImFptCommon_CO_ACT_FPT_HCLOCK
volatile guchar GFptHclkCounter[2] = {0, 0};
#endif	// ImFptCommon_CO_ACT_FPT_HCLOCK
#ifdef ImFptCommon_CO_ACT_FPT_ICLOCK
volatile guchar GFptIclkCounter[2] = {0, 0};
#endif	// ImFptCommon_CO_ACT_FPT_ICLOCK
volatile guint32 GFptRamslpCounter[2] = { 0, 0 };


/*----------------------------------------------------------------------	*/
/* Global Data																*/
/*----------------------------------------------------------------------	*/
//---------------------------- driver section ----------------------------
static ImFptPrivate S_GIMFPT_SPIN_LOCK_TBL[2] __attribute__((section(".LOCK_SECTION"), aligned(64)));

/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
static void 		imFptManagerInit( guchar ch);
static void 		imFptOnFptclk( guchar ch);
static void 		imFptOffFptclk( guchar ch);
static void 		imFptStartRam( guchar ch);
static void 		imFptStopRam( guchar ch);
/**
 *IMPL
 */
static void 		im_fpt_class_init(ImFptClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImFptPrivate));
}

static void 		im_fpt_init(ImFpt *self)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(self);
	priv->fpt = im_fpt_new();
	self->fptaxictl0 = im_fpt_new();
	self->ddimUserCustomTest = ddim_user_custom_new();
	self->fptctl2 =  im_fpt_new();
}

static void 		dispose_od(GObject *object)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(object);
	ImFpt *self = im_fpt_new();
	if(priv->fpt){
		g_object_unref(priv->fpt);
		priv->fpt = NULL;
		}
		if(self->fptaxictl0){
		g_object_unref(self->fptaxictl0);
		self->fptaxictl0 = NULL;
		}
		if(self->ddimUserCustomTest){
			g_object_unref(self->ddimUserCustomTest);
			self->ddimUserCustomTest = NULL;
		}
		if(self->fptctl2){
			g_object_unref(self->fptctl2);
			self->fptctl2 = NULL;
		}
	G_OBJECT_CLASS(im_fpt_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_fpt_parent_class) -> dispose(object);
}

/*----------------------------------------------------------------------	*/
/* Local Function															*/
/*----------------------------------------------------------------------	*/
/**
 Initalize of Managemnet information
 */
static void imFptManagerInit( guchar ch)
{
	// Initialize of PCLK/HCLK/CLK control information
#ifdef ImFptCommon_CO_ACT_FPT_CLOCK
	GFptImFptclkCounter[ch] = 0;
#endif	// ImFptCommon_CO_ACT_FPT_CLOCK
#ifdef ImFptCommon_CO_ACT_FPT_PCLOCK
	GFptPclkCounter[ch] = 0;
#endif	// ImFptCommon_CO_ACT_FPT_PCLOCK
#ifdef ImFptCommon_CO_ACT_FPT_HCLOCK
	GFptHclkCounter[ch] = 0;
#endif	// ImFptCommon_CO_ACT_FPT_HCLOCK
#ifdef ImFptCommon_CO_ACT_FPT_ICLOCK
	GFptIclkCounter[ch] = 0;
#endif	// ImFptCommon_CO_ACT_FPT_ICLOCK
}



/**
 Start FPTCLK.
 */
static void imFptOnFptclk( guchar ch)
{
#ifdef ImFptCommon_CO_ACT_FPT_CLOCK
	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if( ch == 0 ) {
		Dd_Top_Start_Clock((guchar*)&GFptImFptclkCounter[0], ImFptCommon_D_IM_FPT0_CLK_REG_ADDR, ~ImFptCommon_D_IM_FPT0_CLK_REG_BIT );
	}
	else {
		Dd_Top_Start_Clock((guchar*)&GFptImFptclkCounter[1], ImFptCommon_D_IM_FPT1_CLK_REG_ADDR, ~ImFptCommon_D_IM_FPT1_CLK_REG_BIT );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);
#endif	// ImFptCommon_CO_ACT_FPT_CLOCK
}

/**
 Stop FPTCLK.
 */
static void imFptOffFptclk( guchar ch)
{
#ifdef ImFptCommon_CO_ACT_FPT_CLOCK
	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if( ch == 0 ) {
		Dd_Top_Stop_Clock((guchar*)&GFptImFptclkCounter[0], ImFptCommon_D_IM_FPT0_CLK_REG_ADDR, ImFptCommon_D_IM_FPT0_CLK_REG_BIT );
	}
	else {
		Dd_Top_Stop_Clock((guchar*)&GFptImFptclkCounter[1], ImFptCommon_D_IM_FPT1_CLK_REG_ADDR, ImFptCommon_D_IM_FPT1_CLK_REG_BIT );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);
#endif	// ImFptCommon_CO_ACT_FPT_CLOCK
}

//---------------------------- driver section ----------------------------
/**
 Start RAM.
 */
static void imFptStartRam( guchar ch)
{
	IoFptFptctl2 fptctl2;

	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	GFptRamslpCounter[ch]++;
	if(GFptRamslpCounter[ch] == 1) {
		im_fpt_on_pclk(NULL, ch);
		fptctl2.word = ioFpt[ch].fptctl2.word;
		// active
		fptctl2.bit.ramslp = 1;
		ioFpt[ch].fptctl2.word = fptctl2.word;
		ImFptCommon_IM_FPT_DUMMY_READ( ch );

		// wait 1usec
		im_fptasm_wait_cpucyc((660 >> 1));
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	im_fpt_off_pclk(NULL, ch);
}

/**
 Stop RAM.
 */
static void imFptStopRam( guchar ch)
{
	IoFptFptctl2 fptctl2;

	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if(GFptRamslpCounter[ch] > 0) {
		GFptRamslpCounter[ch]--;
	}
	if(GFptRamslpCounter[ch] == 0) {
		im_fpt_on_pclk(NULL, ch);
		fptctl2.word = ioFpt[ch].fptctl2.word;
		// sleep
		fptctl2.bit.ramslp = 0;
		ioFpt[ch].fptctl2.word = fptctl2.word;
		ImFptCommon_IM_FPT_DUMMY_READ( ch );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	im_fpt_off_pclk(NULL, ch);
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/**
 * PUBLIC
 */
/**
 Start HCLK.
 */
void im_fpt_on_hclk(ImFpt*self, guchar ch)
{
#ifdef ImFptCommon_CO_ACT_FPT_HCLOCK
	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if( ch == 0 ) {
		Dd_Top_Start_Clock((guchar*)&GFptHclkCounter[0], ImFptCommon_D_IM_FPT0_HCLK_REG_ADDR, ~ImFptCommon_D_IM_FPT0_HCLK_REG_BIT );
	}
	else {
		Dd_Top_Start_Clock((guchar*)&GFptHclkCounter[1], ImFptCommon_D_IM_FPT1_HCLK_REG_ADDR, ~ImFptCommon_D_IM_FPT1_HCLK_REG_BIT );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);
#endif	// ImFptCommon_CO_ACT_FPT_HCLOCK
}

/**
 Stop HCLK.
 */
void im_fpt_off_hclk(ImFpt*self, guchar ch)
{
#ifdef ImFptCommon_CO_ACT_FPT_HCLOCK
	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if( ch == 0 ) {
		Dd_Top_Stop_Clock((guchar*)&GFptHclkCounter[0], ImFptCommon_D_IM_FPT0_HCLK_REG_ADDR, ImFptCommon_D_IM_FPT0_HCLK_REG_BIT );
	}
	else {
		Dd_Top_Stop_Clock((guchar*)&GFptHclkCounter[1], ImFptCommon_D_IM_FPT1_HCLK_REG_ADDR, ImFptCommon_D_IM_FPT1_HCLK_REG_BIT );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);
#endif	// ImFptCommon_CO_ACT_FPT_HCLOCK
}

/**
 Start ICLK.
 */
void im_fpt_on_iclk(ImFpt*self, guchar ch)
{
#ifdef ImFptCommon_CO_ACT_FPT_ICLOCK
	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if( ch == 0 ) {
		Dd_Top_Start_Clock((guchar*)&GFptIclkCounter[0], ImFptCommon_D_IM_FPT0_ICLK_REG_ADDR, ~ImFptCommon_D_IM_FPT0_ICLK_REG_BIT );
	}
	else {
		Dd_Top_Start_Clock((guchar*)&GFptIclkCounter[1], ImFptCommon_D_IM_FPT1_ICLK_REG_ADDR, ~ImFptCommon_D_IM_FPT1_ICLK_REG_BIT );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);
#endif	// ImFptCommon_CO_ACT_FPT_ICLOCK
}

/**
 Stop ICLK.
 */
void im_fpt_off_iclk(ImFpt*self, guchar ch)
{
#ifdef ImFptCommon_CO_ACT_FPT_ICLOCK
	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if( ch == 0 ) {
		Dd_Top_Stop_Clock((guchar*)&GFptIclkCounter[0], ImFptCommon_D_IM_FPT0_ICLK_REG_ADDR, ImFptCommon_D_IM_FPT0_ICLK_REG_BIT );
	}
	else {
		Dd_Top_Stop_Clock((guchar*)&GFptIclkCounter[1], ImFptCommon_D_IM_FPT1_ICLK_REG_ADDR, ImFptCommon_D_IM_FPT1_ICLK_REG_BIT );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);
#endif	// ImFptCommon_CO_ACT_FPT_ICLOCK
}

/**
 Start PCLK.
 */
void im_fpt_on_pclk(ImFpt*self, guchar ch)
{
#ifdef ImFptCommon_CO_ACT_FPT_PCLOCK
	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if( ch == 0 ) {
		Dd_Top_Start_Clock((guchar*)&GFptPclkCounter[0], ImFptCommon_D_IM_FPT0_PCLK_REG_ADDR, ~ImFptCommon_D_IM_FPT0_PCLK_REG_BIT );
	}
	else {
		Dd_Top_Start_Clock((guchar*)&GFptPclkCounter[1], ImFptCommon_D_IM_FPT1_PCLK_REG_ADDR, ~ImFptCommon_D_IM_FPT1_PCLK_REG_BIT );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);
#endif	// ImFptCommon_CO_ACT_FPT_PCLOCK
}

/**
 Stop PCLK.
 */
void im_fpt_off_pclk(ImFpt*self, guchar ch)
{
#ifdef ImFptCommon_CO_ACT_FPT_PCLOCK
	DD_ARM_CRITICAL_SECTION_START(S_GIMFPT_SPIN_LOCK_TBL[ch]);

	if( ch == 0 ) {
		Dd_Top_Stop_Clock((guchar*)&GFptPclkCounter[0], ImFptCommon_D_IM_FPT0_PCLK_REG_ADDR, ImFptCommon_D_IM_FPT0_PCLK_REG_BIT );
	}
	else {
		Dd_Top_Stop_Clock((guchar*)&GFptPclkCounter[1], ImFptCommon_D_IM_FPT1_PCLK_REG_ADDR, ImFptCommon_D_IM_FPT1_PCLK_REG_BIT );
	}

	DD_ARM_CRITICAL_SECTION_END(S_GIMFPT_SPIN_LOCK_TBL[ch]);
#endif	// ImFptCommon_CO_ACT_FPT_PCLOCK
}
/*----------------------------------------------------------------------	*/
/* Global Function															*/
/*----------------------------------------------------------------------	*/
//---------------------------- driver section ----------------------------
/**
 Initialize driver.
 */
gint32 im_fpt_im_fpt_init(ImFpt*self, guchar ch)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(self);
	//	IoFptFptaxictl0 fptaxictl0;
	gint32 retval;

	// Initalize of Managemnet information
	imFptManagerInit(ch);

	im_fpt_on_pclk(priv->fpt, ch);

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {
		// Software-reset.
		ioFpt[ch].fptctl0.word = 0x1;

		DD_ARM_DSB_POU();

		ImFptCommon_IM_FPT_DUMMY_READ( ch );

		// wait 2usec
		im_fptasm_wait_cpucyc(660);

		// Relase reset.
		ioFpt[ch].fptctl0.word = 0x0;

		DD_ARM_DSB_POU();

		self->fptaxictl0.word = ioFpt[ch].fptaxictl0.word;
		self->fptaxictl0.bit.arcache = 0x0;
		self->fptaxictl0.bit.awcache = 0x0;
		ioFpt[ch].fptaxictl0.word = self->fptaxictl0.word;

		retval = ImFptCommon_D_IM_FPT_RETVAL_OK;
	}
	else {
		retval = ImFptCommon_D_IM_FPT_RETVAL_ERR;
	}

	im_fpt_off_pclk(priv->fpt, ch);

	return retval;
}

/**
 Opend driver.
 */
gint32 im_fpt_open(ImFpt*self, guchar ch, gint32 waitTime)
{
	DdimUserCustom_ER ercd;

	if(waitTime < -1) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}
	else if(0 == waitTime) {
		ercd = ddim_user_custom_pol_sem(self->ddimUserCustomTest, SID_IM_FPT(ch));
	}
	else {
		ercd = ddim_user_custom_twai_sem(self->ddimUserCustomTest, SID_IM_FPT(ch), waitTime);
	}

	if( DdimUserCustom_E_OK != ercd) {
		return ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR;
	}

	// Start FPTCLK and Release RAMSLEEP.
	imFptOnFptclk(ch);
	imFptStartRam(ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 Close driver.
 */
gint32 im_fpt_close(ImFpt*self, guchar ch)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(self);
	DdimUserCustom_ER ercd;

	im_fpt_on_pclk(priv->fpt, ch);

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_RUNNING) {
		im_fpt_off_pclk(NULL, ch);
		return ImFptCommon_D_IM_FPT_RETVAL_ERR;
	}

	im_fpt_off_pclk(priv->fpt, ch);

	// Stop FPTCLK and RAMSLEEP.
	imFptStopRam(ch);
	imFptOffFptclk(ch);

	ercd = ddim_user_custom_sig_sem(self->ddimUserCustomTest, SID_IM_FPT(ch));

	if( DdimUserCustom_E_OK == ercd) {
		return ImFptCommon_D_IM_FPT_RETVAL_OK;
	}
	else {
		return ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR;
	}
}

/**
 Configure the mode, "Calculate Feature Amount".
 */
gint32 im_fpt_ctrl_mode0(ImFpt*self, guchar ch, const TfptMode0* const param)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(self);
	IoFptFptfqctl1 fptfqctl1;
	IoFptFptfqctl2 fptfqctl2;
	IoFptFptfqctl9 fptfqctl9;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	if((param->downSampleX < ImFptCommon_D_IM_FPT_DS_MIN) ||( ImFptCommon_D_IM_FPT_DS_MAX < param->downSampleX)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}
	if((param->downSampleY < ImFptCommon_D_IM_FPT_DS_MIN) ||( ImFptCommon_D_IM_FPT_DS_MAX < param->downSampleY)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	im_fpt_on_pclk(priv->fpt, ch);

	switch(param->lutsel) {
		case ImFptCommon_E_IM_FPT_LUTSEL_OFF:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_OFF);
			break;
		case ImFptCommon_E_IM_FPT_LUTSEL_0:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT0);
			break;
		case ImFptCommon_E_IM_FPT_LUTSEL_1:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT1);
			break;
		default:
			return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	self->fptctl2.word = ioFpt[ch].fptctl2.word;
	self->fptctl2.bit.mode = 0;
	ioFpt[ch].fptctl2.word = self->fptctl2.word;

	ioFpt[ch].fptfqctl0.word = param->globalWidth;

	fptfqctl1.word = 0;
	fptfqctl1.bit.hsize = param->width;
	fptfqctl1.bit.vsize = param->lines;
	ioFpt[ch].fptfqctl1.word = fptfqctl1.word;

	fptfqctl2.word = ioFpt[ch].fptfqctl2.word;
	fptfqctl2.bit.sumw = param->windowSize;

	ioFpt[ch].fptfqctl2.word = fptfqctl2.word;
	ioFpt[ch].fptfqctl3.word = param->imgAddr;
	ioFpt[ch].fptfqctl4.word = param->featureAmountAddr;
	ioFpt[ch].fptfqctl5.word = param->histgramAddr;
	ioFpt[ch].fptfqctl8.word = param->featureAmountLineByte;

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {
		fptfqctl9.word = 0;
		fptfqctl9.bit.skipxFq = param->downSampleX;
		fptfqctl9.bit.skipyFq = param->downSampleY;
		ioFpt[ch].fptfqctl9.word = fptfqctl9.word;
	}

	im_fpt_off_pclk(priv->fpt, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 Configure the mode, "Re-calculate Feature Amount".
 */
gint32 im_fpt_ctrl_mode1(ImFpt*self, guchar ch, const TfptMode1* const param)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(self);
	IoFptFptfqctl1 fptfqctl1;
	IoFptFptfqctl2 fptfqctl2;
	IoFptFptfqctl9 fptfqctl9;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	if((param->downSampleX < ImFptCommon_D_IM_FPT_DS_MIN) ||( ImFptCommon_D_IM_FPT_DS_MAX < param->downSampleX)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}
	if((param->downSampleY < ImFptCommon_D_IM_FPT_DS_MIN) ||( ImFptCommon_D_IM_FPT_DS_MAX < param->downSampleY)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	im_fpt_on_pclk(priv->fpt, ch);

	switch(param->lutsel) {
		case ImFptCommon_E_IM_FPT_LUTSEL_OFF:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_OFF);
			break;
		case ImFptCommon_E_IM_FPT_LUTSEL_0:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT0);
			break;
		case ImFptCommon_E_IM_FPT_LUTSEL_1:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT1);
			break;
		default:
			return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	self->fptctl2.word = ioFpt[ch].fptctl2.word;
	self->fptctl2.bit.mode = 1;
	ioFpt[ch].fptctl2.word = self->fptctl2.word;
	ioFpt[ch].fptfqctl0.word = param->globalWidth;

	fptfqctl1.word = 0;
	fptfqctl1.bit.hsize = param->width;
	fptfqctl1.bit.vsize = param->lines;
	ioFpt[ch].fptfqctl1.word = fptfqctl1.word;

	fptfqctl2.word = 0;
	fptfqctl2.bit.sumw = param->windowSize;
	fptfqctl2.bit.fpmax = param->numFeaturePoint;
	fptfqctl2.bit.outen = param->output;

	ioFpt[ch].fptfqctl2.word = fptfqctl2.word;
	ioFpt[ch].fptfqctl3.word = param->imgAddr;

	if(self->fptctl2.bit.ioMode != 1) { /* pgr0872 */
		ioFpt[ch].fptfqctl6.word = param->inputCoordAddr;
		ioFpt[ch].fptfqctl7.word = param->outputAddr;
	}

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {
		fptfqctl9.word = 0;
		fptfqctl9.bit.skipxFq = param->downSampleX;
		fptfqctl9.bit.skipyFq = param->downSampleY;
		ioFpt[ch].fptfqctl9.word = fptfqctl9.word;
	}

	im_fpt_off_pclk(priv->fpt, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 Configure the mode, "Feature Point Tracking".
 */
gint32 im_fpt_ctrl_mode2(ImFpt*self, guchar ch, const TfptMode2* const param)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(self);
	IoFptFptftctl0 fptftctl0;
	IoFptFptftctl1 fptftctl1;
	IoFptFptftctl2 fptftctl2;
	IoFptFptftctl3 fptftctl3;
	IoFptFptftctl4 fptftctl4;
	IoFptFptftctl10 fptftctl10;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	im_fpt_on_pclk(priv->fpt, ch);

	switch(param->lutcfg) {
		case ImFptCommon_E_IM_FPT_LUTCFG_OFF:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_OFF);
			break;
		case ImFptCommon_E_IM_FPT_LUTCFG_BASE_0:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT0 | ImFptCommon_D_IM_FPT_LUT_BASE);
			break;
		case ImFptCommon_E_IM_FPT_LUTCFG_TARGET_1:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT1 | ImFptCommon_D_IM_FPT_LUT_TARGET);
			break;
		case ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_BASE_X__TARGET_Y);
			break;
		case ImFptCommon_E_IM_FPT_LUTCFG_BASE_1__TARGET_0:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT1 | ImFptCommon_D_IM_FPT_LUT_BASE_X__TARGET_Y);
			break;
		default:
			return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	self->fptctl2.word = ioFpt[ch].fptctl2.word;
	self->fptctl2.bit.mode = 2;
	ioFpt[ch].fptctl2.word = self->fptctl2.word;

	fptftctl0.word = 0;
	fptftctl0.bit.ghbsize = param->baseGlobalWidth;
	fptftctl0.bit.ghtsize = param->targetGlobalWidth;
	ioFpt[ch].fptftctl0.word = fptftctl0.word;

	fptftctl1.word = 0;
	fptftctl1.bit.ftmax = param->numFeaturePoint;
	fptftctl1.bit.init0 = param->usageTargetCoord;
	ioFpt[ch].fptftctl1.word = fptftctl1.word;

	fptftctl2.word = 0;
	fptftctl2.bit.leftlimit = param->searchWindow.left;
	fptftctl2.bit.rightlimit = param->searchWindow.right;
	ioFpt[ch].fptftctl2.word = fptftctl2.word;

	fptftctl3.word = 0;
	fptftctl3.bit.toplimit = param->searchWindow.top;
	fptftctl3.bit.bottomlimit = param->searchWindow.bottom;
	ioFpt[ch].fptftctl3.word = fptftctl3.word;

	fptftctl4.word = 0;
	fptftctl4.bit.maxerr = param->trackingThreshold;
	fptftctl4.bit.maxitr = param->numIteration;

	ioFpt[ch].fptftctl4.word = fptftctl4.word;
	ioFpt[ch].fptftctl5.word = param->baseImgAddr;
	ioFpt[ch].fptftctl6.word = param->targetImgAddr;

	if(self->fptctl2.bit.ioMode != 1) { /* pgr0872 */
		ioFpt[ch].fptftctl7.word = param->baseCoordAddr;
		ioFpt[ch].fptftctl8.word = param->targetCoordAddr;
		ioFpt[ch].fptftctl9.word = param->trackingResultAddr;
	}

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {
		fptftctl10.word = 0;
		fptftctl10.bit.skipxFt = param->downSampleX;
		fptftctl10.bit.skipyFt = param->downSampleY;
		ioFpt[ch].fptftctl10.word = fptftctl10.word;
	}

	im_fpt_off_pclk(priv->fpt, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

/**
 Configure the mode, "Re-calculate Feature Amount and Feature Point Tracking".
 */
gint32 im_fpt_ctrl_mode3(ImFpt*self, guchar ch, const TfptMode3* const param)
{
	ImFptPrivate *priv = IM_FPT_GET_PRIVATE(self);
	IoFptFptfqctl1 fptfqctl1;
	IoFptFptfqctl2 fptfqctl2;
	IoFptFptfqctl9 fptfqctl9;
	IoFptFptftctl0 fptftctl0;
	IoFptFptftctl1 fptftctl1;
	IoFptFptftctl2 fptftctl2;
	IoFptFptftctl3 fptftctl3;
	IoFptFptftctl4 fptftctl4;
	IoFptFptftctl10 fptftctl10;

	if(param == NULL) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	if((param->downSampleX < ImFptCommon_D_IM_FPT_DS_MIN) ||( ImFptCommon_D_IM_FPT_DS_MAX < param->downSampleX)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}
	if((param->downSampleY < ImFptCommon_D_IM_FPT_DS_MIN) ||( ImFptCommon_D_IM_FPT_DS_MAX < param->downSampleY)) {
		return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	im_fpt_on_pclk(priv->fpt, ch);

	switch(param->lutcfg) {
		case ImFptCommon_E_IM_FPT_LUTCFG_OFF:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_OFF);
			break;
		case ImFptCommon_E_IM_FPT_LUTCFG_BASE_0:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT0 | ImFptCommon_D_IM_FPT_LUT_BASE);
			break;
		case ImFptCommon_E_IM_FPT_LUTCFG_TARGET_1:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT1 | ImFptCommon_D_IM_FPT_LUT_TARGET);
			break;
		case ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_BASE_X__TARGET_Y);
			break;
		case ImFptCommon_E_IM_FPT_LUTCFG_BASE_1__TARGET_0:
			ioFpt[ch].fptctl3.word =( ImFptCommon_D_IM_FPT_LUT_ON | ImFptCommon_D_IM_FPT_LUT_LUT1 | ImFptCommon_D_IM_FPT_LUT_BASE_X__TARGET_Y);
			break;
		default:
			return ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR;
	}

	self->fptctl2.word = ioFpt[ch].fptctl2.word;
	self->fptctl2.bit.mode = 3;
	ioFpt[ch].fptctl2.word = self->fptctl2.word;

	fptfqctl1.word = 0;
	fptfqctl1.bit.hsize = param->width;
	fptfqctl1.bit.vsize = param->lines;
	ioFpt[ch].fptfqctl1.word = fptfqctl1.word;

	fptfqctl2.word = 0;
	fptfqctl2.bit.sumw = param->windowSize;
	fptfqctl2.bit.fpmax = param->numFeaturePoint;
	ioFpt[ch].fptfqctl2.word = fptfqctl2.word;

	if(!(self->fptctl2.bit.mode == 0 || self->fptctl2.bit.ioMode == 1)) { /* pgr0872 */
		ioFpt[ch].fptfqctl7.word = param->outputAddr;
	}

	fptfqctl9.word = 0;
	fptfqctl9.bit.skipxFq = param->downSampleX;
	fptfqctl9.bit.skipyFq = param->downSampleY;
	ioFpt[ch].fptfqctl9.word = fptfqctl9.word;

	fptftctl0.word = 0;
	fptftctl0.bit.ghbsize = param->baseGlobalWidth;
	fptftctl0.bit.ghtsize = param->targetGlobalWidth;
	ioFpt[ch].fptftctl0.word = fptftctl0.word;

	fptftctl1.word = 0;
	fptftctl1.bit.ftmax = param->numFeaturePoint;
	fptftctl1.bit.init0 = param->usageTargetCoord;
	ioFpt[ch].fptftctl1.word = fptftctl1.word;

	fptftctl2.word = 0;
	fptftctl2.bit.leftlimit = param->searchWindow.left;
	fptftctl2.bit.rightlimit = param->searchWindow.right;
	ioFpt[ch].fptftctl2.word = fptftctl2.word;

	fptftctl3.word = 0;
	fptftctl3.bit.toplimit = param->searchWindow.top;
	fptftctl3.bit.bottomlimit = param->searchWindow.bottom;
	ioFpt[ch].fptftctl3.word = fptftctl3.word;

	fptftctl4.word = 0;
	fptftctl4.bit.maxerr = param->trackingThreshold;
	fptftctl4.bit.maxitr = param->numIteration;
	ioFpt[ch].fptftctl4.word = fptftctl4.word;

	ioFpt[ch].fptftctl5.word = param->baseImgAddr;
	ioFpt[ch].fptftctl6.word = param->targetImgAddr;

	if(self->fptctl2.bit.ioMode != 1) { /* pgr0872 */
		ioFpt[ch].fptftctl7.word = param->baseCoordAddr;
		ioFpt[ch].fptftctl8.word = param->targetCoordAddr;
		ioFpt[ch].fptftctl9.word = param->trackingResultAddr;
	}

	if(ioFpt[ch].fptctl1.word == ImFptCommon_D_IM_FPT_TRG_STOPPED) {
		fptftctl10.word = 0;
		fptftctl10.bit.skipxFt = param->downSampleX;
		fptftctl10.bit.skipyFt = param->downSampleY;
		ioFpt[ch].fptftctl10.word = fptftctl10.word;
	}

	im_fpt_off_pclk(priv->fpt, ch);

	return ImFptCommon_D_IM_FPT_RETVAL_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif


ImFpt* im_fpt_new(void)
{
	ImFpt *self = k_object_new_with_private(IM_TYPE_FPT, sizeof(ImFptPrivate));
	return self;
}
