/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、Watchdog Timer driver
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "dd_arm.h"
#include "dd_top.h"
#include "arm.h"
#include "ddwdog.h"
#include "lytest.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdWdog, dd_wdog);
#define DD_WDOG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdWdogPrivate, DD_TYPE_WDOG))

/* Initialize of Watchdog Load (32bit) */
#define D_DD_WDOG_LOAD_INIT					(0xFFFFFFFF)
/* Max value of Watchdog Counter (32bit) */
#define D_DD_WDOG_COUNTER_MAX_VALUE			(0xFFFFFFFF)
/* Watchdog Lock Register - enables write access to all other registers */
#define D_DD_WDOG_REGISTER_ACCESS_ENABLE	(0x1ACCE551)

struct _DdWdogPrivate
{
	int a;
};

//How many Watchdog Counter is reloaded
static volatile kulong 		S_SOFT_COUNTER = 0;
//Rest of Watchdog Counter divided by 0xFFFFFFFF multiple
static volatile kulong 		S_REMAIN_NUMBER = 0;
//Pointer of Interrupt Callback Function
static volatile VP_CALLBACK	S_CALLBACK = NULL;

static void dd_wdog_constructor(DdWdog *self)
{
//	DdWdogPrivate *priv = DD_WDOG_GET_PRIVATE(self);
}

static void dd_wdog_destructor(DdWdog *self)
{
//	DdWdogPrivate *priv = DD_WDOG_GET_PRIVATE(self);
}

/**
 * @brief  	Initialize Watchdog Register.
 */
VOID dd_wdog_init(DdWdog *self)
{
	S_SOFT_COUNTER	= 0;
	S_REMAIN_NUMBER	= 0;
	
	// register write access enable.
	dd_wdog_set_lock(DdWdog_D_DD_WDOG_ENABLE_ON);
	// register write test disable.
	dd_wdog_set_test_mode(DdWdog_D_DD_WDOG_ENABLE_OFF, DdWdog_D_DD_WDOG_ENABLE_OFF, DdWdog_D_DD_WDOG_ENABLE_OFF);

	// WDOGCONTROL
	// disable the reset.
	IO_WDOG.WDOGCONTROL.bit.RESEN = DdWdog_D_DD_WDOG_ENABLE_OFF;
	// disable the interrupt.
	IO_WDOG.WDOGCONTROL.bit.INTEN = DdWdog_D_DD_WDOG_ENABLE_OFF;
	// WDOGLOAD
	// Initialize Watchdog Load
//	IO_WDOG.WDOGLOAD = D_DD_WDOG_LOAD_INIT;
}

/**
 * @brief	The Watchdog fuction is exclusively controlled.
 */
kint32 dd_wdog_open(DdWdog *self, kint32 tmout)
{
	DDIM_USER_ER ercd;
	DDIM_USER_ID sid;
	
// CO_PARAM_CHECK
#ifdef CO_PARAM_CHECK
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ){
		Ddim_Assertion(("Dd_WDOG_Open: input param error. tmout = %d\n",tmout));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	sid = SID_DD_WDOG;
	
	if( D_DDIM_USER_SEM_WAIT_POL == tmout ){
		// pol_sem()
		ercd = DDIM_User_Pol_Sem(sid);
	}
	else{
		// twai_sem()
		ercd = DDIM_User_Twai_Sem(sid, (DDIM_USER_TMO)tmout);
	}
	
	if( D_DDIM_USER_E_OK != ercd ){
		if( D_DDIM_USER_E_TMOUT == ercd ){
			return DdWdog_D_DD_WDOG_SEM_TIMEOUT;
		}
		return DdWdog_D_DD_WDOG_SEM_NG;
	}
	return D_DDIM_OK;
}

/**
 * @brief	Setting of common control variable for Watchdog Counter.
 */
kint32 dd_wdog_ctrl(DdWdog *self, DdWdogCtrl *const wdogCtrl)
{
#ifdef CO_PARAM_CHECK
	if( wdogCtrl == NULL ){
		Ddim_Assertion(("Dd_WDOG_Ctrl: input param error. [*wdogCtrl] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Set Callback function.
	S_CALLBACK = wdogCtrl->pCallback;
	// Set value of WDOGLOAD register
	dd_wdog_set_load(wdogCtrl->wdogLoad);
	// Set value of WDOGCONTROL register
	dd_wdog_set_control(wdogCtrl);
	
	return D_DDIM_OK;
}

/**
 * @brief	Reload Watchdog Counter.
 */
VOID dd_wdog_reload(DdWdog *self)
{
	// Set value of WDOGLOAD register
	dd_wdog_set_load(IO_WDOG.WDOGLOAD);
	Dd_ARM_Dsb_Pou();
}

/**
 * @brief	The exclusive control of Watchdog is released.
 */
kint32 dd_wdog_close(DdWdog *self)
{
	DDIM_USER_ER	ercd;
	DDIM_USER_ID	sid;
	
	sid = SID_DD_WDOG;
	// sig_sem()
	ercd = DDIM_User_Sig_Sem(sid);
	
	if( D_DDIM_USER_E_OK != ercd ){
		return DdWdog_D_DD_WDOG_SEM_NG;
	}
	return D_DDIM_OK;
}

/**
 * @brief	Get value of WDOGLOAD register.
 */
kint32 dd_wdog_get_load(DdWdog *self, kulong *wdogLoad)
{
#ifdef CO_PARAM_CHECK
	if( wdogLoad == NULL ){
		Ddim_Assertion(("Dd_WDOG_Get_Load: input param error. [*wdogLoad] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Get value of WDOGLOAD register
	*wdogLoad = IO_WDOG.WDOGLOAD;
	
	return D_DDIM_OK;
}

/**
 * @brief	Get value of WDOGVALUE register.
 */
kint32 dd_wdog_get_counter(DdWdog *self, kulong *wdogCounter)
{
#ifdef CO_PARAM_CHECK
	if( wdogCounter == NULL ){
		Ddim_Assertion(("dd_wdog_get_counter: input param error. [*wdogCounter] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Get value of WDOGVALUE register
	*wdogCounter	= IO_WDOG.WDOGVALUE;
	
	return D_DDIM_OK;
}

/**
 * @brief	Get value of WDOGCONTROL register.
 */
kint32 dd_wdog_get_control(DdWdog *self, DdWdogCtrl *wdogCtrl)
{
#ifdef CO_PARAM_CHECK
	if( wdogCtrl == NULL ){
		Ddim_Assertion(("dd_wdog_get_control: input param error. [*wdogCtrl] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Get value of reset enable.
	wdogCtrl->resetEnable	= IO_WDOG.WDOGCONTROL.bit.RESEN;
	// Get value of interrupt enable.
	wdogCtrl->intEnable	= IO_WDOG.WDOGCONTROL.bit.INTEN;
	
	return D_DDIM_OK;
}

/**
 * @brief	Get value of WDOGRIS/WDOGMIS register.
 */
kint32 dd_wdog_get_status(DdWdog *self, kuchar *rawWdogInt, kuchar *maskWdogInt)
{
#ifdef CO_PARAM_CHECK
	if((rawWdogInt == NULL) || (maskWdogInt == NULL)){
		Ddim_Assertion(("dd_wdog_get_status: input param error. [*wdog_interrupt] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Get value of WDOGRIS register
	*rawWdogInt	= IO_WDOG.WDOGRIS.bit.STATUS;
	// Get value of WDOGMIS register
	*maskWdogInt = IO_WDOG.WDOGMIS.bit.STATUS;
	
	return D_DDIM_OK;
}

/**
 * @brief	Get value of WDOGLOCK register.
 */
kint32 dd_wdog_get_lock(DdWdog *self, kuchar *wdogLock)
{
#ifdef CO_PARAM_CHECK
	if( wdogLock == NULL ){
		Ddim_Assertion(("dd_wdog_get_lock: input param error. [wdogLock] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Get WDOGLOCK
	*wdogLock = IO_WDOG.WDOGLOCK.bit.EN_STATUS;
	
	return D_DDIM_OK;
}

/**
 * @brief	Get value of WDOGITCR register.
 */
kint32 dd_wdog_get_test_mode(DdWdog *self, kuchar *testMode)
{
#ifdef CO_PARAM_CHECK
	if( testMode == NULL ){
		Ddim_Assertion(("dd_wdog_get_test_mode: input param error. [testMode] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Get WDOGITCR.
	*testMode = IO_WDOG.WDOGITCR.bit.ITEN;
	
	return D_DDIM_OK;
}

/**
 * @brief	Get value of WDOGPERIPHID0~3 register.
 */
kint32 Dd_WDOG_Get_Peri_Identification(DdWdog *self, DdWdogPeriIdentification *identification)
{
#ifdef CO_PARAM_CHECK
	if( identification == NULL ){
		Ddim_Assertion(("Dd_WDOG_Get_Peri_Identification: input param error. [identification] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Get WDOGPERIPHID0~3
	identification->partNumber		= IO_WDOG.WDOGPERIPHID0.bit.PARTNUMBER0 | (IO_WDOG.WDOGPERIPHID1.bit.PARTNUMBER1 << 8);
	identification->designer		= IO_WDOG.WDOGPERIPHID1.bit.DESIGNER0 | (IO_WDOG.WDOGPERIPHID2.bit.DESIGNER1 << 4);
	identification->revisionNumber	= IO_WDOG.WDOGPERIPHID2.bit.REVISION;
	identification->configuration	= IO_WDOG.WDOGPERIPHID3.bit.CONFIGURATION;
	
	return D_DDIM_OK;
}

/**
 * @brief	Get value of WDOGPCELLID0~3 register.
 */
kint32 dd_wdog_get_pcell_identification(DdWdog *self, kulong *pcell)
{
#ifdef CO_PARAM_CHECK
	if( pcell == NULL ) {
		Ddim_Assertion(("dd_wdog_get_pcell_identification: input param error. [pcell] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Get WDOGPCELLID0~3
	*pcell	= IO_WDOG.WDOGPCELLID[0].bit.WDOGPCELLID | (IO_WDOG.WDOGPCELLID[1].bit.WDOGPCELLID << 8) |
				(IO_WDOG.WDOGPCELLID[2].bit.WDOGPCELLID << 16) | (IO_WDOG.WDOGPCELLID[3].bit.WDOGPCELLID << 24);

	return D_DDIM_OK;
}

/**
 * @brief	Set value of WDOGLOAD register.
 */
kint32 dd_wdog_set_load(DdWdog *self, kulong wdogLoad)
{
#ifdef CO_PARAM_CHECK
	if( wdogLoad == 0 ){
		Ddim_Assertion(("dd_wdog_set_load: input param error. wdogLoad = 0\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Set value of WDOGLOAD register
	IO_WDOG.WDOGLOAD = wdogLoad;
	
	return D_DDIM_OK;
}

/**
 * @brief	Set value of WDOGCONTROL register.
 */
kint32 dd_wdog_set_control(DdWdog *self, DdWdogCtrl *wdogCtrl)
{
#ifdef CO_PARAM_CHECK
	if( wdogCtrl == NULL ){
		Ddim_Assertion(("dd_wdog_set_control: input param error. [*wdogCtrl] NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
	if((wdogCtrl->resetEnable != DdWdog_D_DD_WDOG_ENABLE_ON) && (wdogCtrl->resetEnable != DdWdog_D_DD_WDOG_ENABLE_OFF)){
		Ddim_Assertion(("dd_wdog_set_control: input param error. resetEnable=%d\n", wdogCtrl->resetEnable));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
	if((wdogCtrl->intEnable != DdWdog_D_DD_WDOG_ENABLE_ON) && (wdogCtrl->intEnable != DdWdog_D_DD_WDOG_ENABLE_OFF)){
		Ddim_Assertion(("dd_wdog_set_control: input param error. intEnable=%d\n", wdogCtrl->intEnable));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Set WdogControl
	if( wdogCtrl->resetEnable == DdWdog_D_DD_WDOG_ENABLE_ON ) {
		IO_WDOG.WDOGCONTROL.bit.RESEN	= DdWdog_D_DD_WDOG_ENABLE_ON;
		IO_WDOG.WDOGCONTROL.bit.INTEN	= 1;
	}
	if( wdogCtrl->intEnable == DdWdog_D_DD_WDOG_ENABLE_ON ) {
		IO_WDOG.WDOGCONTROL.bit.INTEN	= DdWdog_D_DD_WDOG_ENABLE_ON;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief	Clear Interrupt flag (Set WDOGINTCLR register).
 */
kint32 dd_wdog_clear_interrupt(DdWdog *self)
{
	// Set value of WdogIntClr register
	IO_WDOG.WDOGINTCLR = 1;
	
	return D_DDIM_OK;
}

/**
 * @brief	Set value of WDOGLOCK register.
 */
kint32 dd_wdog_set_lock(DdWdog *self, kuchar wdogLock)
{
#ifdef CO_PARAM_CHECK
	if((wdogLock != DdWdog_D_DD_WDOG_ENABLE_ON) && (wdogLock != DdWdog_D_DD_WDOG_ENABLE_OFF)){
		Ddim_Assertion(("dd_wdog_set_lock: input param error. wdogLock=%d\n", wdogLock));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	if( wdogLock == DdWdog_D_DD_WDOG_ENABLE_ON ){
		// Unlock(write access to all other registers is enabled).
		IO_WDOG.WDOGLOCK.word = D_DD_WDOG_REGISTER_ACCESS_ENABLE;
	}
	else{
		// Lock(write access to all other registers is disable).
		IO_WDOG.WDOGLOCK.word = 0;
	}
	return D_DDIM_OK;
}

/**
 * @brief	Set value of WDOGITCR/WDOGITOP register.
 */
kint32 dd_wdog_set_test_mode(DdWdog *self, kuchar testMode, kuchar testRes, kuchar testInt)
{
#ifdef CO_PARAM_CHECK
	if((testMode != DdWdog_D_DD_WDOG_ENABLE_ON) && (testMode != DdWdog_D_DD_WDOG_ENABLE_OFF)){
		Ddim_Assertion(("dd_wdog_set_test_mode: input param error. testMode=%d\n", testMode));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
	if((testRes != DdWdog_D_DD_WDOG_ENABLE_ON) && (testRes != DdWdog_D_DD_WDOG_ENABLE_OFF)){
		Ddim_Assertion(("dd_wdog_set_test_mode: input param error. testRes=%d\n", testRes));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
	if((testInt != DdWdog_D_DD_WDOG_ENABLE_ON) && (testInt != DdWdog_D_DD_WDOG_ENABLE_OFF)){
		Ddim_Assertion(("dd_wdog_set_test_mode: input param error. testInt=%d\n", testInt));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Set WDOGITCR.
	IO_WDOG.WDOGITCR.bit.ITEN = testMode;
	// Set WDOGITOP.
	IO_WDOG.WDOGITOP.bit.WDOGRES = testRes;
	IO_WDOG.WDOGITOP.bit.WDOGINT = testInt;
	
	return D_DDIM_OK;
}

/**
 * @brief	It is Interrupt Handler of Watchdog.<br>
 *			The CallBack function is called.
*/
VOID dd_wdog_int_handler(DdWdog *self)
{
	// Soft Counter check
	if( S_SOFT_COUNTER > 1 ){
		S_SOFT_COUNTER--;
		
		// Reload
		dd_wdog_set_load(D_DD_WDOG_COUNTER_MAX_VALUE);
		// Clear Interrupt
		dd_wdog_clear_interrupt();
		Dd_ARM_Dsb_Pou();
	}
	else if( S_SOFT_COUNTER == 1 ){
		S_SOFT_COUNTER--;
		
		// Reload
		dd_wdog_set_load(S_REMAIN_NUMBER);
		// Clear Interrupt
		dd_wdog_clear_interrupt();
		Dd_ARM_Dsb_Pou();
	}
	else{
		if( S_CALLBACK != NULL ){
			// Callback.
			(*S_CALLBACK)();
		}
		
		// Clear Interrupt
		dd_wdog_clear_interrupt();
		Dd_ARM_Dsb_Pou();
	}
}

// CO_DDIM_UTILITY_USE
#ifdef CO_DDIM_UTILITY_USE
/**
 * @brief  To input the value at the passed time to WdogLoad, it converts it into the number of clocks. 
 */
kint32 dd_wdog_calculate(DdWdog *self, kulong wdogWdmode, kulong msec, kulong *convertCounter)
{
	ULLONG periClk;
	ULLONG msecCount;
	
#ifdef CO_PARAM_CHECK
	if( wdogWdmode > 1 ){
		Ddim_Assertion(("dd_wdog_calculate: input param error. wdogWdmode > 1\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
	if( msec == 0 ){
		Ddim_Assertion(("dd_wdog_calculate: input param error. [msec] = 0\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
	if( convertCounter == NULL ){
		Ddim_Assertion(("dd_wdog_calculate: input param error. [convertCounter] = NULL\n"));
		return DdWdog_D_DD_WDOG_INPUT_PARAM_ERR;
	}
#endif
	// Call ChipTop API
	periClk = Dd_Top_Get_PCLK();
	// Convert to counter value
	msecCount = periClk * msec / 1000;
	if( wdogWdmode == 1 ){
		// Watchdog mode
		if( msecCount > D_DD_WDOG_COUNTER_MAX_VALUE ){
			return DdWdog_D_DD_WDOG_OVERFLOW;
		}
	}
	// Calculate to input value divided by the maximum value of 32bit
	S_SOFT_COUNTER = msecCount / ((ULLONG)D_DD_WDOG_COUNTER_MAX_VALUE + 1);
	// Calculate to the remainder into which the input value is divided by the maximum value of 32bit is acquired
	S_REMAIN_NUMBER = msecCount & D_DD_WDOG_COUNTER_MAX_VALUE;
	if( S_SOFT_COUNTER > 0 ){
		// Max value of watchdog counter
		msecCount = D_DD_WDOG_COUNTER_MAX_VALUE;
	}
	
	*convertCounter = msecCount;
	
	return D_DDIM_OK;
}

/**
 * @brief  The passed time to WdogLoad to set the watchdog timer, msec converts into the number of clocks. 
 */
kint32 dd_wdog_set_timer(DdWdog *self, kulong wdogWdmode, kulong msec)
{
	kulong convertCounter;
	kint32 ercd;
	
	ercd = dd_wdog_calculate(wdogWdmode, msec, &convertCounter);
	if( ercd != D_DDIM_OK ){
		return ercd;
	}
	// Set value of WdogLoad register
	dd_wdog_set_load(convertCounter);
	
	return D_DDIM_OK;
}
#endif

DdWdog *dd_wdog_new(void)
{
	DdWdog* self = k_object_new_with_private(DD_TYPE_WDOG,sizeof(DdWdogPrivate));
	return self;
}
