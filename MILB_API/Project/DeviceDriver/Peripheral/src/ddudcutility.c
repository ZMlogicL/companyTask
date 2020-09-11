/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-08
* @author    : 肖泽友
* @brief        :UpDown Counter driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、utility section
*
*@version   :1.0.0
*
*/

#include "dd_top.h"

#include "ddudcutility.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdUdcUtility, dd_udc_utility);
#define DD_UDC_UTILITY_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdUdcUtilityPrivate, DD_TYPE_UDC_UTILITY))

#ifdef CO_DDIM_UTILITY_USE
// UDC clock selection
// Ratio of dividing peripheral clock 2
#define DdUdcUtility_CLK_SEL_2		(2)
// Ratio of dividing peripheral clock 8
#define DdUdcUtility_CLK_SEL_8		(8)
// Maximum value of Ratio of dividing peripheral clock
#define DdUdcUtility_CLK_SEL_MAX	(2)

// MAX value of RCR/UDCR
#define DdUdcUtility_COUNTR_MAX		(0xFFFF)
#endif

#ifdef CO_DDIM_UTILITY_USE
typedef struct _DdUdcTimerMng DdUdcTimerMng;
#endif

#ifdef CO_DDIM_UTILITY_USE
// Set timer configuration data table
/*
*	reloadCount   : Number of reloading for maximum timer counter
*	remainCount   : Remaining Timer Counter
*	pTimer_Callback: Callback function pointer for timer function
*/
struct _DdUdcTimerMng{
	kulong					reloadCount;
	kushort					remainCount;
	DdUdcTimerCallback	pTimerCallback;
};
#endif

struct _DdUdcUtilityPrivate
{
#ifdef CO_DDIM_UTILITY_USE
	// Save Ratio of dividing peripheral clock
	volatile kuchar gDdUdcClkSel[DdUdcUtility_CLK_SEL_MAX];
#endif
};

#ifdef CO_DDIM_UTILITY_USE
// Save Timer configuration data
static volatile DdUdcTimerMng	gDdUdcTimerMng[DdUdc_CH_COUNT];
#endif

/*
 * DECLS
 */
#ifdef CO_DDIM_UTILITY_USE
static void    ddUdcTimerCalculate(DdUdcUtility* self, kuchar ch, kulong usec,
		                      kuchar* const clockSel, kulonglong* const timerCount);
static void    ddUdcTimer_cb(kuchar ch, kint32 result);   //TODO
#endif

static void dd_udc_utility_constructor(DdUdcUtility *self)
{
	DdUdcUtilityPrivate *priv = DD_UDC_UTILITY_GET_PRIVATE(self);
    priv->gDdUdcClkSel[0] = DdUdcUtility_CLK_SEL_2;
    priv->gDdUdcClkSel[1] = DdUdcUtility_CLK_SEL_8;
}

static void dd_udc_utility_destructor(DdUdcUtility *self)
{

}

/*
 * IMPL
 */
#ifdef CO_DDIM_UTILITY_USE
/*
*calculate parameter for timer function.
*@param [in] ch		Channel number.<br>
*@param [in] usec	setting time.<br>
*/
static void ddUdcTimerCalculate(DdUdcUtility* self, kuchar ch, kulong usec,
		kuchar* const clockSel, kulonglong* const timerCount)
{
	DdUdcUtilityPrivate *priv = DD_UDC_UTILITY_GET_PRIVATE(self);
	kulonglong totalCount;
	kulong periClk;

	//Get peripheral clock
	periClk = Dd_Top_Get_RCLK();

	//Get total counter (Before clock dividing)
	// usec order
	totalCount = (((kulonglong)periClk * (kulonglong)usec) / 1000000);

	// Caluculate counter value and dividing rate
	// Divide by 8
	if((totalCount % priv->gDdUdcClkSel[1]) == 0){
		// Get total counter with dividing
		*timerCount = totalCount / priv->gDdUdcClkSel[1];
		*clockSel = DdUdc_CLKS_8_CLOCK;
	}
	else if((totalCount % priv->gDdUdcClkSel[0]) == 0){
		// Divide by 2
		// Get total counter with dividing
		*timerCount = totalCount / priv->gDdUdcClkSel[0];
		*clockSel = DdUdc_CLKS_2_CLOCK;
	}
	else{
		/* Case of Can not be divided evenly : Dividing rate 2 that the error margin is
		 fewer is adopted and the fraction is rounded down */
		*timerCount = totalCount / priv->gDdUdcClkSel[0];
		*clockSel = DdUdc_CLKS_2_CLOCK;
	}

	return;
}

/*
*Number of reloading was Decremented and callback at end of timer count.
*@param [in] ch		Channel number.<br>
*@param [in] result	Interrupt factor.<br>
*/
static void ddUdcTimer_cb(kuchar ch, kint32 result)
{
	if(result == DdUdc_UNDER_FLOW){
		// Case of timer count is completed
		if(gDdUdcTimerMng[ch].reloadCount == 0){
			dd_udc_stop(dd_udc_get(), ch);
			(*gDdUdcTimerMng[ch].pTimerCallback)(ch);
		}
		else{
			if(gDdUdcTimerMng[ch].reloadCount >= 1){
				gDdUdcTimerMng[ch].reloadCount--;
			}

			if(gDdUdcTimerMng[ch].reloadCount == 0){
				dd_udc_stop(dd_udc_get(), ch);
				dd_udc_set_udcr_counter(dd_udc_get(), ch, gDdUdcTimerMng[ch].remainCount);
				dd_udc_start(dd_udc_get(), ch);
			}
			else{
				// The reload function as before reboot 0xFFFF
			}
		}
	}

	return;
}
#endif

/*
 * PUBLIC
 */
#ifdef CO_DDIM_UTILITY_USE
/*
*Configuration for timer utility function.
*@param [in] ch					Channel number.<br>
*@param [in] usec				Setting time.(usec order)<br>
*@param [in] timerCallback		Callback function for timer function.<br>
*/
kint32 dd_udc_utility_write_timer_mode(DdUdcUtility* self, kuchar ch,
		kulong usec, DdUdcTimerCallback timerCallback)
{
	kint32 result;
	kulonglong timerCount;
	kuchar clockSel;
	DdUdcCtrlCmn udcCrl;

#ifdef CO_PARAM_CHECK
	// Channel number range check
	if(dd_udc_get_chk_ch_number(dd_udc_get(), ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Write_Timer_Mode parameter error. ch=%d\n", ch));
		return DdUdc_INPUT_PARAM_ERROR;
	}

	// Callback function check
	if(timerCallback == NULL){
		// Error of callback function
		Ddim_Assertion(("E:Dd_UDC_Write_Timer_Mode parameter error. timerCallback is NULL"));
		return DdUdc_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// Calculate timer counter
	ddUdcTimerCalculate(self, ch, usec, &clockSel, &timerCount);

	// Save soft_counter to loop timer operation
	gDdUdcTimerMng[ch].reloadCount = (timerCount / DdUdcUtility_COUNTR_MAX);
	gDdUdcTimerMng[ch].remainCount = (timerCount % DdUdcUtility_COUNTR_MAX);

	// Set reload counter
	if(gDdUdcTimerMng[ch].reloadCount >= 1){
		// Set reload counter as MAX value
		udcCrl.rcr = DdUdcUtility_COUNTR_MAX;
		udcCrl.udcr = DdUdcUtility_COUNTR_MAX;
	}
	else{
		// Set reload counter
		udcCrl.rcr = gDdUdcTimerMng[ch].remainCount;
		udcCrl.udcr = gDdUdcTimerMng[ch].remainCount;
	}

	//Set timer mode
	udcCrl.countMode = DdUdc_CMS_TIMER;
	//Compare clear disable
	udcCrl.compClear = DdUdc_UCRE_OFF;
	//Reload enable
	udcCrl.reload = DdUdc_RLDE_ON;
	//Set counter clear function for ZIN terminal function
	udcCrl.zinMode = DdUdc_CGSC_CLEAR;
	//Disable edge detection for ZIN terminal function
	udcCrl.zinEdge = DdUdc_CGE_NOT;
	//Compare interrupt disable
	udcCrl.cmpInt = DdUdc_CITE_OFF;
	//Under/Over flow interrupt enable
	udcCrl.underOver = DdUdc_UDIE_ON;
	//Count direction interrupt disable
	udcCrl.cntDirInt = DdUdc_CFIE_OFF;
	//Set callback function for check timer reload
	udcCrl.pCallback = ddUdcTimer_cb;

	result = dd_udc_ctrl_common(dd_udc_get(), ch, &udcCrl);
	if(result != D_DDIM_OK){
		// Parameter setting error.
		Ddim_Print(("E:Dd_UDC_Write_Timer_Mode ctrl_common parameter setting error. ch=%d, result=%d\n",
				ch, result));
		return result;
	}

	result = dd_udc_ctrl_timer(dd_udc_get(), ch, clockSel);
	if(result != D_DDIM_OK){
		// CLKS setting error.
		Ddim_Print(("E:Dd_UDC_Write_Timer_Mode prescaler setting error. ch=%d, result=%d\n", ch, result));
		return result;
	}

	// Set callback function for inform the completion of the timer count
	gDdUdcTimerMng[ch].pTimerCallback = timerCallback;

	return D_DDIM_OK;
}
#endif

DdUdcUtility* dd_udc_utility_get(void)
{
	DdUdcUtility *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_UDC_UTILITY, sizeof(DdUdcUtilityPrivate));
	}

	return self;
}
