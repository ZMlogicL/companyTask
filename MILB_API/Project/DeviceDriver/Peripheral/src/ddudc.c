/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :UpDown Counter driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include "ddim_user_custom.h"
#include "peripheral.h"
#include "dd_top.h"
#include "dd_arm.h"

#include "ddudc.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdUdc, dd_udc);
#define DD_UDC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdUdcPrivate, DD_TYPE_UDC))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// UDC task mode
// State of unlock
//#define D_DD_UDC_EXC_OFF		(0)
// State of lock
//#define D_DD_UDC_EXC_ON			(1)

// CCRH/L: 16bit mode permission setting
//  8bit operational mode
#define DdUdc_M16E_8BIT		    (0x00)
// 16bit operational mode
#define DdUdc_M16E_16BIT		(0x01)

// Peripheral block function select UDCTRG
// UDCTRG bit OFF
#define DdUdc_UDCTRG_OFF		(0x00)
// UDCTRG bit ON
#define DdUdc_UDCTRG_ON		(0x01)

// Set to the lock status.
//#define dd_udc_lock(ch)		{ gDD_UDC_State[(ch)] = D_DD_UDC_EXC_ON;  }
// Set to the unlock status.
//#define dd_udc_unlock(ch)	{ gDD_UDC_State[(ch)] = D_DD_UDC_EXC_OFF; }

typedef struct _DdUdcMngSave DdUdcMngSave;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Set data maintenance table
/*
*	rcr      : RCR register value (0 ~ 65535)
*	pCallback: Callback function pointer
*/
struct _DdUdcMngSave
{
	kushort			rcr;
	DdUdcCallback	 pCallback;
};

struct _DdUdcPrivate
{
	// Save parameter
	volatile DdUdcMngSave gDdUdcMng[DdUdc_CH_COUNT];
};

/*
*	UDC status
*		D_DD_UDC_EXC_OFF	: UDC is not locked.
*		D_DD_UDC_EXC_ON		: UDC is being locked.
*/
//static kuchar gDD_UDC_State[DdUdc_CH_COUNT] = {D_DD_UDC_EXC_OFF,
//D_DD_UDC_EXC_OFF, D_DD_UDC_EXC_OFF, D_DD_UDC_EXC_OFF};
//static kuchar gDD_UDC_State[DdUdc_CH_COUNT] = {D_DD_UDC_EXC_OFF,
//D_DD_UDC_EXC_OFF, D_DD_UDC_EXC_OFF, D_DD_UDC_EXC_OFF, D_DD_UDC_EXC_OFF, D_DD_UDC_EXC_OFF};

/*
 * DECLS
 */
static union io_udc_ccr       ddUdcGetSafeWriteCcr(DdUdc* self, kuchar ch);
static union io_udc_csr       ddUdcGetSafeWriteCsr(DdUdc* self, kuchar ch);
static void                             ddUdcSetRcr(DdUdc* self, kuchar ch, kushort rcr);
static kushort                        ddUdcGetRcr(DdUdc* self, kuchar ch);

#ifdef CO_PARAM_CHECK
static kint32                          ddUdcChkChNumber(DdUdc* self, kuchar ch);
static kint32                          ddUdcChkCountMode(DdUdc* self, kuchar countMode);
#endif	// CO_PARAM_CHECK

static void dd_udc_constructor(DdUdc *self)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);

	kint i;
	for(i = 0; i < DdUdc_CH_COUNT; i++){
		priv->gDdUdcMng[i].pCallback = NULL;
	}
}

static void dd_udc_destructor(DdUdc *self)
{

}

/*
 * IMPL
 */
/*
*The CCR register value that can be safely "read modify write" is returned.
*/
static union io_udc_ccr ddUdcGetSafeWriteCcr(DdUdc* self, kuchar ch)
{
	union io_udc_ccr ccr;

	ccr.word = IO_PERI.UDC[ch].CCR.word;
	// Not change CDCF
	ccr.bit.__CDCF = 1;

	return ccr;
}

/*
*The CSR register value that can be safely "read modify write" is returned.
*/
static union io_udc_csr ddUdcGetSafeWriteCsr(DdUdc* self, kuchar ch)
{
	union io_udc_csr csr;

	csr.word = IO_PERI.UDC[ch].CSR.word;
	// Not change CMPF
	csr.bit.__CMPF = 1;
	// Not change OVFF
	csr.bit.__OVFF = 1;
	// Not change UDFF
	csr.bit.__UDFF = 1;

	return csr;
}

/*
*RCR is written in the register,
*and the reproduction is maintained. (for RCR improper reading)
*@param [in] ch	Channel number.<br>
*@param [in] rcr	RCR value.<br>
*/
static void ddUdcSetRcr(DdUdc* self, kuchar ch, kushort rcr)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);
	IO_PERI.UDC[ch].RCR.bit.D = (kulong)rcr;
	priv->gDdUdcMng[ch].rcr = rcr;
}

/*
*Get RCR value.
*@param [in] ch	Channel number.<br>
*@retval			RCR value
*/
static kushort ddUdcGetRcr(DdUdc* self, kuchar ch)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);
	return priv->gDdUdcMng[ch].rcr;
}

#ifdef CO_PARAM_CHECK
/*
*Check channel number.
*@param [in] ch	Channel number.<br>
*/
static kint32 ddUdcChkChNumber(DdUdc* self, kuchar ch)
{
	// channel number range check
	if(ch >= DdUdc_CH_COUNT){
		// Error of channel number
		return DdUdc_INPUT_PARAM_ERROR;
	}
	return D_DDIM_OK;
}

/*
*Check count mode.
*@param [in] countMode	Count mode.<br>
*/
static kint32 ddUdcChkCountMode(DdUdc* self, kuchar countMode)
{
	kint32 result;

	switch (countMode) {
		case DdUdc_CMS_TIMER:
		case DdUdc_CMS_UP_DOWN:
		case DdUdc_CMS_PHASE_LAG_2:
		case DdUdc_CMS_PHASE_LAG_4:
			result = D_DDIM_OK;
			break;

		default:
			result = DdUdc_INPUT_PARAM_ERROR;
			break;
	}
	return result;
}
#endif	// CO_PARAM_CHECK

/*
 * PUBLIC
 */
/*
 * @brief  The UDC control register (all channels) is initialized.
 * @param  void
 * @return void
 */
void dd_udc_init(DdUdc* self)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);
	kuchar ch;

	for(ch = 0; ch < DdUdc_CH_COUNT; ch++){
		// clear of up/down counter register
		IO_PERI.UDC[ch].CCR.word = 0x00008008;
												// [b15]	M16E=1	:16bit mode(Fixed value)
												// [b14]	CDCF=0	:clear(initilal value)
												// [b13]	CFIE=0	:disable(initilal value)
												// [b12]	CLKS=0	:built-in prescaler(initilal value)
												// [b11-10]	CMS =0	:timer mode(initilal value)
												// [b 9- 8]	CES =0	:detect disable(initilal value)
												// [b 7] 			:reserve
												// [b 6]	CTUT=0	:disable(invalid)
												// [b 5]	UCRE=0	:disable(initial value)
												// [b 4]	RLDE=0	:disable(initial value)
												// [b 3]	UDCC=1	:clear of UDCR register
												// [b 2]	CGSC=0	:gate(initial value)
												// [b1-0]	CGE =0	:disable(initial value)

		// clear of counter status register
		IO_PERI.UDC[ch].CSR.word = 0x00000000;
												// [b7]		CSTR=0	:disable(initilal value)
												// [b6]		CITE=0	:disable(initilal value)
												// [b5]		UDIE=0	:disable(initilal value)
												// [b4]		CMPF=0	:clear(initilal value)
												// [b3]		OVFF=0	:clear(initilal value)
												// [b2]		UDFF=0	:clear(initilal value)
												// [b1-0]	UDF		:read only

		// clear of reload/compare data
		ddUdcSetRcr(self, ch, 0x0000);

		// Initialize for chX management info
		// callback function pointer
		priv->gDdUdcMng[ch].pCallback = NULL;
	}
	return;
}

/*
 * @brief  The UDC channel is exclusively controlled.
 * @param  kuchar	ch
 * @param  kint32	timeOut
 * @return kint32	D_DDIM_OK/DdUdc_INPUT_PARAM_ERROR/D_DD_UDC_EXT_LOCK_NG/D_DD_UDC_SEM_TIMEOUT
 */
kint32 dd_udc_open(DdUdc* self, kuchar ch, kint32 timeOut)
{
//	kint32	status_reg;
	kint32	ercd;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Open parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}

	if (timeOut < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("E:Dd_UDC_Open parameter error. timeOut = %x\n",timeOut));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

//	status_reg = Dd_ARM_DI();
	// Lock check

	if (D_DDIM_USER_SEM_WAIT_POL == timeOut){
		// pol_sem()
		ercd = DDIM_User_Pol_Sem(SID_DD_UDC(ch));
	}
	else {
		// twai_sem()
		ercd = DDIM_User_Twai_Sem(SID_DD_UDC(ch), (DDIM_USER_TMO)timeOut);
	}

	if (D_DDIM_USER_E_OK != ercd){
		if (D_DDIM_USER_E_TMOUT == ercd){
//			Dd_ARM_EI(status_reg);
			return DdUdc_SEM_TIMEOUT;
		}
//		Dd_ARM_EI(status_reg);
		return DdUdc_EXT_LOCK_NG;
	}

//	Dd_ARM_EI(status_reg);
	return D_DDIM_OK;
}

/*
 * @brief  The exclusive control of control Channel it is released.
 * @param  kuchar cntl_ch
 * @return kint32	D_DDIM_OK/DdUdc_INPUT_PARAM_ERROR/D_DD_UDC_SEM_NG
 */
kint32 dd_udc_close(DdUdc* self, kuchar ch)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);
	kint32	ercd;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Close parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// Initialize for chX management info
	// callback function pointer
	priv->gDdUdcMng[ch].pCallback = NULL;

	// sig_sem()
	ercd = DDIM_User_Sig_Sem(SID_DD_UDC(ch));
	if (D_DDIM_USER_E_OK != ercd) {
		return DdUdc_SEM_NG;
	}

	return D_DDIM_OK;
}

/*
 * @brief  Set common setting to each mode of UDC.
 * @param  kuchar ch, DdUdcCtrlCmn *udcCrl
 * @return kint32	D_DDIM_OK/DdUdc_INPUT_PARAM_ERROR/D_DD_UDC_ERROR_BUSY
 */
kint32 dd_udc_ctrl_common(DdUdc* self, kuchar ch, DdUdcCtrlCmn const* const udcCrl)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);
	kint32 result;
	union io_udc_ccr ccr;
	union io_udc_csr csr;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:dd_udc_ctrl_common parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
	// Parameter check
	if (udcCrl == NULL) {
		// A set value makes an error for NULL.
		Ddim_Assertion(("E:dd_udc_ctrl_common parameter error. udcCrl is NULL.\n"));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if((DdUdc_CMS_PHASE_LAG_2 == udcCrl->countMode)
			|| (DdUdc_CMS_PHASE_LAG_4 == udcCrl->countMode)) {
		// M7M update
		//if((ch == 4) || (5 == ch)) {
		// Not Support Mode
		//	return D_DD_UDC_EXT_LOCK_NG;
		//}
		if(Dd_Top_Get_PERSEL2_UDCTRG() == DdUdc_UDCTRG_ON){
			if(ch >= 2) {
				// Not Support Mode
				return DdUdc_EXT_LOCK_NG;
			}
		}
	}

	// callback function pointer
	priv->gDdUdcMng[ch].pCallback = udcCrl->pCallback;

	ccr = ddUdcGetSafeWriteCcr(self, ch);

	ccr.bit.__CGE  = udcCrl->zinEdge;
	ccr.bit.__CGSC = udcCrl->zinMode;
	ccr.bit.__RLDE = udcCrl->reload;
	ccr.bit.__UCRE = udcCrl->compClear;
	ccr.bit.__CMS  = udcCrl->countMode;
	ccr.bit.__CFIE = udcCrl->cntDirInt;
	//Reserve bit. However, it is necessary to be "1".
	ccr.bit.__M16E = DdUdc_M16E_16BIT;
	IO_PERI.UDC[ch].CCR.word = ccr.word;

	csr = ddUdcGetSafeWriteCsr(self, ch);

	csr.bit.__CITE = udcCrl->cmpInt;
	csr.bit.__UDIE = udcCrl->underOver;
	IO_PERI.UDC[ch].CSR.word = csr.word;

	result = dd_udc_set_rcr_counter(self, ch, udcCrl->rcr);
	if (result != D_DDIM_OK) {
		// RCR setting error.
		Ddim_Print(("E:dd_udc_ctrl_common RCR setting error. ch=%d, result=%d\n", ch, result));
		return result;
	}
	result = dd_udc_set_udcr_counter(self, ch, udcCrl->udcr);
	if (result != D_DDIM_OK) {
		// UDCR setting error.
		Ddim_Print(("E:dd_udc_ctrl_common UDCR setting error. ch=%d, result=%d\n", ch, result));
		return result;
	}
	return D_DDIM_OK;
}

/*
*Get common setting to each mode of UDC.<br>
*@param[in]	ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*@param[out]	udcCrl	UDC Start table pointer. See @ref DdUdcCtrlCmn
*/
kint32 dd_udc_get_ctrl_common(DdUdc* self, kuchar ch, DdUdcCtrlCmn* const udcCrl)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Get_Ctrl_Common parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
	if (udcCrl == NULL) {
		// Output parameter is NULL.
		Ddim_Assertion(("E:Dd_UDC_Get_Ctrl_Common parameter error. udcCrl is NULL.\n"));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	udcCrl->udcr = dd_udc_get_udcr_counter(self, ch);
	udcCrl->rcr = ddUdcGetRcr(self, ch);

	udcCrl->countMode = IO_PERI.UDC[ch].CCR.bit.__CMS;
	udcCrl->compClear = IO_PERI.UDC[ch].CCR.bit.__UCRE;
	udcCrl->reload = IO_PERI.UDC[ch].CCR.bit.__RLDE;
	udcCrl->zinMode = IO_PERI.UDC[ch].CCR.bit.__CGSC;
	udcCrl->zinEdge = IO_PERI.UDC[ch].CCR.bit.__CGE;
	udcCrl->cmpInt  = IO_PERI.UDC[ch].CSR.bit.__CITE;
	udcCrl->underOver = IO_PERI.UDC[ch].CSR.bit.__UDIE;
	udcCrl->cntDirInt = IO_PERI.UDC[ch].CCR.bit.__CFIE;
	udcCrl->pCallback  = priv->gDdUdcMng[ch].pCallback;

	return D_DDIM_OK;
}

/*
*Set parameter only for the timer mode.
*@param [in] ch			Channel number.<br>
*@param [in]	prescaler	Built-in prescaler selection.<br>
*/
kint32 dd_udc_ctrl_timer(DdUdc* self, kuchar ch, kuchar prescaler)
{
	union io_udc_ccr ccr;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:dd_udc_ctrl_timer parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
	if ((prescaler != DdUdc_CLKS_2_CLOCK) && (prescaler
			!= DdUdc_CLKS_8_CLOCK)) {
		// Error of prescaler selection
		Ddim_Assertion(("E:dd_udc_ctrl_timer parameter error. prescaler=%d\n", prescaler));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ccr = ddUdcGetSafeWriteCcr(self, ch);
	ccr.bit.__CLKS = prescaler;
	IO_PERI.UDC[ch].CCR.word = ccr.word;

	return D_DDIM_OK;
}

/*
*Get parameter only for the timer mode.
*@param[in]	ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*@param[out]	prescaler	Built-in prescaler selection.<br>
*						- @ref D_DD_UDC_CLKS_2_CLOCK
*						- @ref D_DD_UDC_CLKS_8_CLOCK
*/
kint32 dd_udc_get_ctrl_timer(DdUdc* self, kuchar ch, kuchar* const prescaler)
{
#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Get_Ctrl_Timer parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
	if (prescaler == NULL) {
		// Output parameter is NULL.
		Ddim_Assertion(("E:Dd_UDC_Get_Ctrl_Timer parameter error. prescaler is NULL.\n"));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*prescaler = IO_PERI.UDC[ch].CCR.bit.__CLKS;

	return D_DDIM_OK;
}

/*
*Set parameter only for the up/down count mode.
*@param [in] ch		Channel number.<br>
*@param [in]	edge	Count clock edge.<br>
*/
kint32 dd_udc_ctrl_up_down(DdUdc* self, kuchar ch, kuchar edge)
{
	union io_udc_ccr ccr;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Ctrl_Up_Down parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
	switch (edge) {
		case DdUdc_CES_NOT:
		case DdUdc_CES_RISE:
		case DdUdc_CES_FALL:
		case DdUdc_CES_BOTH:
			// DO NOTHING
			break;
		default:
			// Error of edge selection
			Ddim_Assertion(("E:Dd_UDC_Ctrl_Up_Down parameter error. edge=%d\n", edge));
			return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ccr = ddUdcGetSafeWriteCcr(self, ch);
	ccr.bit.__CES = edge;
	IO_PERI.UDC[ch].CCR.word = ccr.word;

	return D_DDIM_OK;
}

/*
*Get parameter only for the up/down count mode.
*@param[in]	ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*@param[out]	edge	Count clock edge.<br>
*					Please specify either the following.<br>
*					- @ref D_DD_UDC_CES_NOT
*					- @ref D_DD_UDC_CES_RISE
*					- @ref D_DD_UDC_CES_FALL
*					- @ref D_DD_UDC_CES_BOTH
*/
kint32 dd_udc_get_ctrl_up_down(DdUdc* self, kuchar ch, kuchar* const edge)
{
#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Get_Ctrl_Up_Down parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
	if (edge == NULL) {
		// Output parameter is NULL.
		Ddim_Assertion(("E:dd_udc_ctrl_common parameter error. edge is NULL.\n"));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*edge = IO_PERI.UDC[ch].CCR.bit.__CES;

	return D_DDIM_OK;
}

/*
*The UDC of a control channel is started.<br>
*@param [in] ch	Channel number.<br>
*/
kint32 dd_udc_start(DdUdc* self, kuchar ch)
{
	union io_udc_ccr ccr;
	union io_udc_csr csr;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:dd_udc_start parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ccr = ddUdcGetSafeWriteCcr(self, ch);
	// Clear CDCF
	ccr.bit.__CDCF = 0;
	IO_PERI.UDC[ch].CCR.word = ccr.word;

	csr = ddUdcGetSafeWriteCsr(self, ch);
	// Clear CMPF
	csr.bit.__CMPF = 0;
	// Clear OVFF
	csr.bit.__OVFF = 0;
	// Clear UDFF
	csr.bit.__UDFF = 0;
	IO_PERI.UDC[ch].CSR.word = csr.word;

	csr = ddUdcGetSafeWriteCsr(self, ch);
	// Start
	csr.bit.__CSTR = 1;
	IO_PERI.UDC[ch].CSR.word = csr.word;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/*
*The UDC of a control channel is stopped.<br>
*@param [in] ch	Channel number.<br>
*/
kint32 dd_udc_stop(DdUdc* self, kuchar ch)
{
	union io_udc_csr csr;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Stop parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// UDC stop
	csr = ddUdcGetSafeWriteCsr(self, ch);
	csr.bit.__CSTR = 0;
	IO_PERI.UDC[ch].CSR.word = csr.word;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/*
*Set count mode.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*@param [in]	countMode	Count mode.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CMS_TIMER
*				- @ref D_DD_UDC_CMS_UP_DOWN
*				- @ref D_DD_UDC_CMS_PHASE_LAG_2
*				- @ref D_DD_UDC_CMS_PHASE_LAG_4
*/
kint32 dd_udc_set_count_mode(DdUdc* self, kuchar ch, kuchar countMode)
{
	union io_udc_ccr ccr;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Set_Count_Mode parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
	// Check count mode.
	if(ddUdcChkCountMode(self, countMode) != D_DDIM_OK){
		// Error of count mode
		Ddim_Assertion(("E:Dd_UDC_Set_Count_Mode parameter error. countMode=%d\n", countMode));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ccr = ddUdcGetSafeWriteCcr(self, ch);
	ccr.bit.__CMS  = countMode;
	IO_PERI.UDC[ch].CCR.word = ccr.word;

	return D_DDIM_OK;
}

/*
*Set the callback function when interruption is generate to pCallback.
*@param [in] ch	Channel number.<br>
*@param [in]		pCallback	Call Back function pointer
*/
void dd_udc_set_callback(DdUdc* self, kuchar ch, DdUdcCallback pCallback)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Set_CallBack parameter error. ch=%d\n", ch));
		return;
	}
#endif	// CO_PARAM_CHECK

	priv->gDdUdcMng[ch].pCallback = pCallback;
	return;
}

/*
*The input counter is set to the RCR register.
*@param [in] ch		Channel number.<br>
*@param [in] rcr		Set reload / compare counter
*/
kint32 dd_udc_set_rcr_counter(DdUdc* self, kuchar ch, kushort rcr)
{
#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:dd_udc_set_rcr_counter parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ddUdcSetRcr(self, ch, rcr);

	return D_DDIM_OK;
}

/*
*The Up/Down counter value is returned.
*@param [in] ch	Channel number.<br>
*@retval UDCR counter value.<br>
*/
kushort dd_udc_get_udcr_counter(DdUdc* self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:dd_udc_get_udcr_counter parameter error. ch=%d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (kushort)(IO_PERI.UDC[ch].UDCR.bit.D);
}

/*
*The input counter is set to UDCR register.
*@param [in] ch		Channel number.<br>
*@param [in] udcr	Set counter value.
*/
kint32 dd_udc_set_udcr_counter(DdUdc* self, kuchar ch, kushort udcr)
{
	union io_udc_csr	csr;
	union io_udc_ccr 	ccr;
	kuint32 toCnt = 0;
	kint32 result;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:dd_udc_set_udcr_counter parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	result = D_DDIM_OK;
	csr.word = IO_PERI.UDC[ch].CSR.word;

	// Wait for CSTR state clear. (about 100msec)
	while(csr.bit.__CSTR == 1){	/* pgr0872 */
		ercd = DDIM_User_Dly_Tsk(1);
		if(ercd != D_DDIM_USER_E_OK){
			// DDIM_User_Dly_Tsk error
			Ddim_Print(("E:dd_udc_set_udcr_counter(CSTR): DDIM_User_Dly_Tsk error. ercd=%d\n", ercd));
		}
		toCnt++;
		if(toCnt > 100){
			// Error when not stopping even if 100ms is waited
			Ddim_Print(("E:dd_udc_set_udcr_counter: Macro busy error.\n"));
			return DdUdc_ERROR_BUSY;
		}
		csr.word = IO_PERI.UDC[ch].CSR.word;
	}

	// UDCR is written by way of RCR.
	// Temporarily write
	IO_PERI.UDC[ch].RCR.bit.D = (kulong)udcr;

	ccr = ddUdcGetSafeWriteCcr(self, ch);
	// Set RCR --> UDCR
	ccr.bit.__CTUT = 1;
	IO_PERI.UDC[ch].CCR.word = ccr.word;

	// Wait for RCR is forwarded to UDCR. (about 10msec)
	toCnt = 0;
	while (IO_PERI.UDC[ch].UDCR.bit.D != (kulong)udcr) {
		ercd = DDIM_User_Dly_Tsk(1);
		if(ercd != D_DDIM_USER_E_OK){
			// DDIM_User_Dly_Tsk error
			Ddim_Print(("E:dd_udc_set_udcr_counter(UDCR):DDIM_User_Dly_Tsk error. ercd=%d\n", ercd));
		}
		toCnt++;
		if(toCnt > 10){
			// Error when UDCR doesn't become equivalent with write value.
			result = DdUdc_ERROR_BUSY;
			Ddim_Print(("E:dd_udc_set_udcr_counter: UDCR write error.\n"));
			break;
		}
	}

	// Roll back RCR
	IO_PERI.UDC[ch].RCR.bit.D = (kulong)ddUdcGetRcr(self, ch);

	return result;
}

/*
*The RDCC bit of the CCR register of the specified channel is cleared.
*@param [in] ch	Channel number.<br>
*/
kint32 dd_udc_force_clear_udcr(DdUdc* self, kuchar ch)
{
	union io_udc_ccr ccr;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Force_Clear_UDCR parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ccr = ddUdcGetSafeWriteCcr(self, ch);
	// clear UDCR
	ccr.bit.__UDCC = 0;
	IO_PERI.UDC[ch].CCR.word = ccr.word;

	return D_DDIM_OK;
}

/*
*Get kind of the count immediately before.
*@param [in] ch	Channel number.<br>
*/
kuchar dd_udc_get_up_down_flg(DdUdc* self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	// channel number range check
	if(ddUdcChkChNumber(self, ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Get_Up_Down_Flg parameter error. ch=%d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return IO_PERI.UDC[ch].CSR.bit.__UDF;
}

DdUdcCallback dd_udc_get_p_callback(DdUdc* self, kuchar ch)
{
	DdUdcPrivate *priv = DD_UDC_GET_PRIVATE(self);
	return priv->gDdUdcMng[ch].pCallback;
}

kint32 dd_udc_get_chk_ch_number(DdUdc* self, kuchar ch)
{
	return ddUdcChkChNumber(self, ch);
}

DdUdc* dd_udc_get(void)
{
	DdUdc *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_UDC, sizeof(DdUdcPrivate));
	}

	return self;
}
