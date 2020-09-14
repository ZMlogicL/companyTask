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

#ifndef __DD_WDOG_H__
#define __DD_WDOG_H__

#include "driver_common.h"
#include <klib.h>

#define DD_TYPE_WDOG		(dd_wdog_get_type())
#define DD_WDOG(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, DdWdog))
#define DD_IS_WDOG(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_WDOG))

/* Return value of watchdog timer processing result */
//Input Parameter Error
#define DdWdog_D_DD_WDOG_INPUT_PARAM_ERR	(D_DD_WDOG | D_DDIM_INPUT_PARAM_ERROR)
//Semaphore acquisition Time Out
#define DdWdog_D_DD_WDOG_SEM_TIMEOUT		(D_DD_WDOG | D_DDIM_SEM_TIMEOUT)
//Semaphore acquisition NG
#define DdWdog_D_DD_WDOG_SEM_NG				(D_DD_WDOG | D_DDIM_SEM_NG)
//Load value is overflow
#define DdWdog_D_DD_WDOG_OVERFLOW			(D_DD_WDOG | D_DDIM_OVERFLOW_ERR)

//General-purpose definition of register value (Effectiveness selection)
//OFF
#define DdWdog_D_DD_WDOG_ENABLE_OFF			(0)
//ON
#define DdWdog_D_DD_WDOG_ENABLE_ON			(1)

typedef struct 	_DdWdogCtrl	 				DdWdogCtrl;
typedef struct 	_DdWdogPeriIdentification	DdWdogPeriIdentification;
typedef struct 	_DdWdog 					DdWdog;
typedef struct 	_DdWdogPrivate 				DdWdogPrivate;

/* Control value */
struct _DdWdogCtrl{
	/** WDOGLOAD register.
	 *Value range : 0x00000000~0xFFFFFFFF
	 */
	kulong 		wdogLoad;
	/** WDOGCONTROL.RESEN : Enable Watchdog reset output.
	 *@ref D_DD_WDOG_ENABLE_OFF
	 *@ref D_DD_WDOG_ENABLE_ON
	 */
	kuchar 		resetEnable;
	/** WDOGCONTROL.INTEN : Enable the interrupt event.
	 *@ref D_DD_WDOG_ENABLE_OFF
	 *@ref D_DD_WDOG_ENABLE_ON
	 */
	kuchar 		intEnable;
	/* Callback function called when interrupt is generated */
	VpCallbackFunc pCallback;
};

/* Peripheral Identification */
struct _DdWdogPeriIdentification{
	//This identifies the peripheral. Value:0x805
	kushort		partNumber;
	//Designer. Value:0x41 (ARM Limited is 0x41, ASCII A.)
	kuchar		designer;
	//Revision number of the peripheral. Value:0~15 (starts from 0.)
	kuchar		revisionNumber;
	//This is the configuration option of the peripheral. Value:0
	kuchar		configuration;
};

struct _DdWdog {
	KObject parent;
};

KConstType	dd_wdog_get_type(void);
DdWdog*		dd_wdog_new(void);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize Watchdog Register.<br>
 * Default status : WDOGCONTROL = 0, WDOGLOAD = 0xFFFFFFFF.<br>
 */
void		dd_wdog_init(DdWdog *self);

/**
 * The Watchdog fuction is exclusively controlled.<br>
 * If Watchdog is unused, exclusive control OK is sent back as (Lock) while using it.<br>
 * Exclusive control NG is sent back when using it (Lock inside of present) or Input Parameter Error.
 * @param[in]	tmout					: Semaphore Timeout Value.<br>
 * 										  <ul><li>Positive Value
 * 											  <li>@ref D_DDIM_USER_SEM_WAIT_POL
 * 											  <li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_SEM_NG			: Lock Error (System has already been used.)
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 * @retval	D_DD_WDOG_SEM_TIMEOUT		: Semaphore Timeout Error
 * @remarks	This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
			This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
 */
kint32		dd_wdog_open(DdWdog *self, kint32 tmout);

/**
 * Setting of common control variable for Watchdog Counter.
 * @param[in]	wdogCtrl				: Watchdog Control value. See @ref DdWdogCtrl
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_ctrl(DdWdog *self, DdWdogCtrl *wdogCtrl);

/**
 * Reload Watchdog Counter.
 */
void		dd_wdog_reload(DdWdog *self);

/**
 * The exclusive control of Watchdog is released.
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_SEM_NG			: Semaphore acquisition NG
 * @remarks	This API uses DDIM_User_Sig_Sem().
 */
kint32		dd_wdog_close(DdWdog *self);

/**
 * Get value of WDOGLOAD register.
 * @param[out]	wdogLoad				: Watchdog Load
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_get_load(DdWdog *self, kulong *wdogLoad);

/**
 * Get value of WDOGVALUE register.
 * @param[out]	wdogCounter			: Watchdog Counter
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_get_counter(DdWdog *self, kulong *wdogCounter);

/**
 * Get value of WDOGCONTROL register.
 * @param[out]	wdogCtrl				: Watchdog Control value. See @ref DdWdogCtrl
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_get_control(DdWdog *self, DdWdogCtrl *wdogCtrl);

/**
 * Get value of WDOGRIS/WDOGMIS register.
 * @param[out]	rawWdogInt			: Raw Watchdog Interrupt
 * @param[out]	maskWdogInt			: Watchdog Interrupt
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_get_status(DdWdog *self, kuchar *rawWdogInt, kuchar *maskWdogInt);

/**
 * @brief	Get value of WDOGLOCK register.
 * @param[out]	wdogLock				: Lock status<br>
 * 										  <ul><li>D_DD_WDOG_ENABLE_OFF : Unlock
 * 											  <li>D_DD_WDOG_ENABLE_ON : Lock</ul>
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_get_lock(DdWdog *self, kuchar *wdogLock);

/**
 * Get value of WDOGITCR register.
 * @param[out]	testMode				: Integration Test Mode Enable
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_get_test_mode(DdWdog *self, kuchar *testMode);
kint32 		dd_wdog_get_peri_identification(DdWdog *self, DdWdogPeriIdentification *identification);

/**
 * Get value of WDOGPERIPHID0~3 register.
 * @param[out]	identification			: Peripheral Identification. See @ref DdWdogPeriIdentification
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_get_peri_identification(DdWdog *self, DdWdogPeriIdentification *identification);

/**
 * Get value of WDOGPCELLID0~3 register.
 * @param[out]	pcell					: PrimeCell Identification. Value:0xB105F00D
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_get_pcell_identification(DdWdog *self, kulong *pcell);

/**
 * Set value of WDOGLOAD register.
 * @param[in]	wdogLoad				: Watchdog Load. Value range:0x00000000~0xFFFFFFFF
 * @retval	D_DDIM_OK					: Normal end
 */
kint32		dd_wdog_set_load(DdWdog *self, kulong wdogLoad);

/**
 * Set value of WDOGCONTROL register.
 * @param[in]	wdogCtrl				: Watchdog Control value. See @ref DdWdogCtrl
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_set_control(DdWdog *self, DdWdogCtrl *wdogCtrl);

/**
 * Clear Interrupt flag (Set WDOGINTCLR register).
 * @return	D_DDIM_OK					: Normal end
 */
kint32		dd_wdog_clear_interrupt(DdWdog *self);

/**
 * Set value of WDOGLOCK register. 
 * @param[in]	wdogLock				: Watchdog Lock setting<br>
 * 										  <ul><li>D_DD_WDOG_ENABLE_OFF : Unlock
 * 											  <li>D_DD_WDOG_ENABLE_ON : Lock</ul>
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_set_lock(DdWdog *self, kuchar wdogLock);

/**
 * Set value of WDOGITCR/WDOGITOP register.
 * @param[in]	testMode				: Integration Test Mode Enable<br>
 * 										  <ul><li>D_DD_WDOG_ENABLE_OFF
 * 											  <li>D_DD_WDOG_ENABLE_ON</ul>
 * @param[in]	testRes				: Integration Test WDOGINT value<br>
 * 										  <ul><li>D_DD_WDOG_ENABLE_OFF
 * 											  <li>D_DD_WDOG_ENABLE_ON</ul>
 * @param[in]	testInt				: Integration Test WDOGRES value<br>
 * 										  <ul><li>D_DD_WDOG_ENABLE_OFF
 * 											  <li>D_DD_WDOG_ENABLE_ON</ul>
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 */
kint32		dd_wdog_set_test_mode(DdWdog *self, kuchar testMode, kuchar testRes, kuchar testInt);

/**
 * It is Interrupt Handler of Watchdog.<br>
 * The CallBack function is called.
 */
void		dd_wdog_int_handler(DdWdog *self);

#ifdef CO_DDIM_UTILITY_USE
/** @name Utility Functions
@{*/
/**
 * To input the value at the passed time to WDOG_LOAD, it converts it into the number of clocks.
 * @param[in]		wdogWdmode			: Watchdog Mode
 * 										  <ul><li>0:INTEN(Interrupt event)
 * 											  <li>1:RESEN(Watchdog reset)</ul>
 * @param[in]		msec				: Designated time(milli seconds)
 * @param[out]		convertCounter		: Value of converted msec
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 * @retval	D_DD_WDOG_OVERFLOW			: Load value is overflow
 * @remarks
 * In the RESEN mode, If PCLK is 50[MHz], range is 1 to 85899[msec].<br>
 * In the INTEN mode, If msec exceeded the maximum value of WDOGLOAD(4294967295=0xFFFFFFFF) as a result of calculation, dd_wdog_calculate uses soft counter.<br>
 * The soft counter enables the count that exceeds the maximum value.<br>
 * The counter maintains the value in which msec is divided by maximum value of WDOGLOAD(4294967295).<br>
 * If soft counter maintains the value when timer is expired, WDOGLOAD is reloaded by 0xFFFFFFFF and soft counter is decrement.<br>
 * If soft counter is zero and timer is expired, WDOGLOAD is reloaded by remained number for msec divided by 4294967295.
 */
kint32 		dd_wdog_calculate(DdWdog *self, kulong wdogWdmode, kulong msec, kulong *convertCounter);

/**
 * The passed time to WDOG_LOAD to set the Watchdog timer, msec converts into the number of clocks. 
 * @param[in]		wdogWdmode			: Watchdog Mode
 * 										  <ul><li>0:INTEN(Interrupt event)
 * 											  <li>1:RESEN(Watchdog reset)</ul>
 * @param[in]		msec				: Designated time(milli seconds)
 * @retval	D_DDIM_OK					: Normal end
 * @retval	D_DD_WDOG_INPUT_PARAM_ERR	: Input Parameter Error
 * @retval	D_DD_WDOG_OVERFLOW			: Load value is overflow
 * @remarks
 * In the RESEN mode, If PCLK is 50[MHz], range is 1 to 85899[msec].<br>
 * In the INTEN mode, If msec exceeded the maximum value of WDOGLOAD(4294967295=0xFFFFFFFF) as a result of calculation, dd_wdog_calculate uses soft counter.<br>
 * The soft counter enables the count that exceeds the maximum value.<br>
 * The counter maintains the value in which msec is divided by maximum value of WDOGLOAD(4294967295).<br>
 * If soft counter maintains the value when timer is expired, WDOGLOAD is reloaded by 0xFFFFFFFF and soft counter is decrement.<br>
 * If soft counter is zero and timer is expired, WDOGLOAD is reloaded by remained number for msec divided by 4294967295.
 */
kint32 		dd_wdog_set_timer(DdWdog *self, kulong wdogWdmode, kulong msec);
/*@}*/
#endif

#ifdef __cplusplus
}
#endif

// __DD_WDOG_H__
#endif
