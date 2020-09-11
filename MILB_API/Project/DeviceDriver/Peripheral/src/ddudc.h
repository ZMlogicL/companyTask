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

/*
@addtogroup dd_udc
@{

	- @ref UDC_start_up_down_mode
	- @ref UDC_start_phase_lag_mode_2
	- @ref UDC_start_phase_lag_mode_4
	- @ref UDC_start_timer_mode
	- @ref UDC_start_timer_utility
	- @ref dd_udc_sample_section1
	- @ref dd_udc_sample_section2
	- @ref dd_udc_sample_section3
	- @ref dd_udc_sample_section4
	- @ref dd_udc_sample_section5

	<hr>
	@section UDC_start_up_down_mode	Sequence of UDC up/down count mode
	@image html dd_udc_up_down_mode.png

	@section UDC_start_phase_lag_mode_2	Sequence of UDC phase lag count mode (2 multiply)
	@image html dd_udc_phase_lag2_mod.png

	@section UDC_start_phase_lag_mode_4	Sequence of UDC phase lag count mode (4 multiply)
	@image html dd_udc_phase_lag4_mod.png

	@section UDC_start_timer_mode	Sequence of UDC timer mode
	@image html dd_udc_timer_mode.png

	@section UDC_start_timer_utility	Sequence of timer utility
	@image html dd_udc_timer_utility.png
*/

#ifndef __DD_UDC_H__
#define __DD_UDC_H__

#include <klib.h>
#include "driver_common.h"

#define DD_TYPE_UDC                                   (dd_udc_get_type())
#define DD_UDC(obj)                                     K_TYPE_CHECK_INSTANCE_CAST(obj, DdUdc)
#define DD_IS_UDC(obj)                                K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_UDC)

/*---------------------------------------------------------------*/
/* Definition													 */
/*---------------------------------------------------------------*/
// Return value of UDC timer processing result
/*< Input Parameter Error*/
#define	DdUdc_INPUT_PARAM_ERROR	 (D_DD_UDC | D_DDIM_INPUT_PARAM_ERROR)
/*< Exclusive control NG	*/
#define	DdUdc_EXT_LOCK_NG		         (D_DD_UDC | D_DDIM_EXT_LOCK_NG)
/*< Macro busy	*/
#define DdUdc_ERROR_BUSY			         (D_DD_UDC | D_DDIM_MACRO_BUSY_NG)

/*< Semaphore acquisition Time Out */
#define DdUdc_SEM_TIMEOUT		         (D_DD_UDC | D_DDIM_SEM_TIMEOUT)
/*< Semaphore acquisition NG */
#define DdUdc_SEM_NG				             (D_DD_UDC | D_DDIM_SEM_NG)

// UDC Handler result value
/*< Compare OK*/
#define DdUdc_CMPF_OK			             (D_DD_UDC | 0x00000101)
/*< Overflow generation*/
#define DdUdc_OVER_FLOW			         (D_DD_UDC | 0x00000102)
/*< Underflow generation*/
#define DdUdc_UNDER_FLOW			     (D_DD_UDC | 0x00000103)
/*< Count direction change*/
#define DdUdc_COUNT_DIRECTION	     (D_DD_UDC | 0x00000104)
/*< Flag undetection*/
#define	DdUdc_UNDETECTION		         (D_DD_UDC | 0x00000105)

// CCRH/L: Count mode
/*< Count mode: Timer mode*/
#define DdUdc_CMS_TIMER			         (0x00)
/*< Count mode: Up/Down count mode	*/
#define DdUdc_CMS_UP_DOWN		     (0x01)
/*< Count mode: Phase lag count mode (2 multiply)	*/
#define DdUdc_CMS_PHASE_LAG_2	     (0x02)
/*< Count mode: Phase lag count mode (4 multiply)	*/
#define DdUdc_CMS_PHASE_LAG_4	     (0x03)

// CCRH/L: Compare clear enable
/*< Compare clear enable: disable	*/
#define	DdUdc_UCRE_OFF			(0x00)
/*< Compare clear enable: enable*/
#define	DdUdc_UCRE_ON			(0x01)

// CCRH/L: Reload enable
/*< Reload enable: disable*/
#define	DdUdc_RLDE_OFF			(0x00)
/*< Reload enable: enable*/
#define	DdUdc_RLDE_ON			    (0x01)

// CCRH/L: Function of terminal ZIN
/*< Function of terminal ZIN: Counter clear*/
#define	DdUdc_CGSC_CLEAR			(0x00)
/*< Function of terminal ZIN: Gate*/
#define	DdUdc_CGSC_GATE			    (0x01)

// CCRH/L: Detect edge of terminal ZIN
/*< Detect edge of terminal ZIN: Detect disable	*/
#define	DdUdc_CGE_NOT			    (0x00)
/*< Detect edge of terminal ZIN: Fall edge / L*/
#define	DdUdc_CGE_FALL_L			(0x01)
/*< Detect edge of terminal ZIN: Rise edge / H	*/
#define	DdUdc_CGE_RISE_H			(0x02)

// CCRH/L: Prescaler select
/*< Prescaler select: 2 clock	*/
#define DdUdc_CLKS_2_CLOCK		(0x00)
/*< Prescaler select: 8 clock	*/
#define DdUdc_CLKS_8_CLOCK		(0x01)

// CCRH/L: Count clock edge select
/*< Count clock edge select: Detect disable	*/
#define	DdUdc_CES_NOT			        (0x00)
/*< Count clock edge select: Rise edge*/
#define	DdUdc_CES_RISE			        (0x01)
/*< Count clock edge select: Fall edge*/
#define	DdUdc_CES_FALL			        (0x02)
/*< Count clock edge select: Both edge*/
#define	DdUdc_CES_BOTH		    	(0x03)

// CSR: Up/Down flag
/*< Up/Down flag: No input*/
#define DdUdc_UDF_NON			    (0x00)
/*< Up/Down flag: Down count*/
#define DdUdc_UDF_DOWN			(0x01)
/*< Up/Down flag: Up count	*/
#define DdUdc_UDF_UP			    	(0x02)
/*< Up/Down flag: Up and down count	*/
#define DdUdc_UDF_BOTH			    (0x03)

// CSR: Compare interrupt enable
/*< Compare interrupt enable: disable	*/
#define	DdUdc_CITE_OFF			        (0x00)
/*< Compare interrupt enable: enable*/
#define	DdUdc_CITE_ON			        (0x01)

// CSR: Under/Over-flow interrupt enable
/*< Under/Over-flow interrupt enable: disable*/
#define	DdUdc_UDIE_OFF		    	(0x00)
/*< Under/Over-flow interrupt enable: enable*/
#define	DdUdc_UDIE_ON			        (0x01)

// CCRH/L: Count direction interrupt enable
/*< Count direction interrupt enable: disable*/
#define	DdUdc_CFIE_OFF			        (0x00)
/*< Count direction interrupt enable: enable*/
#define	DdUdc_CFIE_ON			        (0x01)

// Channel number
/*< UDC ch0	*/
#define DdUdc_CH0				(0x00)
/*< UDC ch1	*/
#define DdUdc_CH1				(0x01)
/*< UDC ch2	*/
#define DdUdc_CH2				(0x02)
/*< UDC ch3	*/
#define DdUdc_CH3				(0x03)
/*< UDC ch4	*/
#define DdUdc_CH4				(0x04)
/*< UDC ch5	*/
#define DdUdc_CH5				(0x05)

// UDC channel count
#define DdUdc_CH_COUNT		(6)

// Interrupt flag bit
// CSR.CMPF
#define DdUdc_CSR_BIT_CMPF	(0x00000010)
// CSR.OVFF
#define DdUdc_CSR_BIT_OVFF 	(0x00000008)
// CSR.UDFF
#define DdUdc_CSR_BIT_UDFF  	(0x00000004)
// CCR.CDCF
#define DdUdc_CCR_BIT_CDCF	(0x00004000)

typedef struct _DdUdcCtrlCmn    DdUdcCtrlCmn;

typedef struct _DdUdc                   DdUdc;
typedef struct _DdUdcPrivate       DdUdcPrivate;

/*< Type is defined to Callback function pointer.<br>
*The meaning of the argument is as follows.<br>
*- kuchar ch    : Channel number.<br>
*<ul><li>@ref D_DD_UDC_CH0
*<li>@ref D_DD_UDC_CH1
*<li>@ref D_DD_UDC_CH2
*<li>@ref D_DD_UDC_CH3
*<li>@ref D_DD_UDC_CH4
*<li>@ref D_DD_UDC_CH5</ul>
*- kuchar factor: Factor of callback.
*<ul><li>@ref D_DD_UDC_CMPF_OK
*<li>@ref D_DD_UDC_OVER_FLOW
*<li>@ref D_DD_UDC_UNDER_FLOW
*<li>@ref D_DD_UDC_COUNT_DIRECTION</ul>
*/
typedef void (*DdUdcCallback)(kuchar ch, kint32 factor);

/*---------------------------------------------------------------*/
/* Structure													 */
/*---------------------------------------------------------------*/
/* Control info */
struct _DdUdcCtrlCmn
{
	/*< UDCR: Up/Down counter value.(0x0000 to 0xFFFF)		*/
	kushort		udcr;
	/*< RCR : Reload/Compare value.(0x0000 to 0xFFFF)		*/
	kushort		rcr;

	/*< CCR.CMS: Count mode.<br>
    *<ul><li>@ref D_DD_UDC_CMS_TIMER
	*<li>@ref D_DD_UDC_CMS_UP_DOWN
	*<li>@ref D_DD_UDC_CMS_PHASE_LAG_2
	*<li>@ref D_DD_UDC_CMS_PHASE_LAG_4</ul>
	*/
	kuchar		countMode;
	/*< CCR.UCRE: Compare clear enable.<br>
	* <ul><li>@ref D_DD_UDC_UCRE_OFF
	*<li>@ref D_DD_UDC_UCRE_ON</ul>
	*/
	kuchar		compClear;
	/*< CCR.RLDE: Reload enable.<br>
	*<ul><li>@ref D_DD_UDC_RLDE_OFF
	*<li>@ref D_DD_UDC_RLDE_ON</ul>
	*/
	kuchar		reload;

	/*< CCR.CGSC: Function of terminal ZIN.<br>
	*<ul><li>@ref D_DD_UDC_CGSC_CLEAR
	*<li>@ref D_DD_UDC_CGSC_GATE</ul>
	*/
	kuchar		zinMode;
	/*< CCR.CGE : Detect edge of terminal ZIN.<br>
	*<ul><li>@ref D_DD_UDC_CGE_NOT
	*<li>@ref D_DD_UDC_CGE_FALL_L
	*<li>@ref D_DD_UDC_CGE_RISE_H</ul>
	*/
	kuchar		zinEdge;

	/*< CSR.CITE: Compare interrupt enable.<br>
	*<ul><li>@ref D_DD_UDC_CITE_OFF
	*<li>@ref D_DD_UDC_CITE_ON</ul>
	*/
	kuchar		cmpInt;
	/*< CSR.UDIE: Under/Over-flow interrupt enable.<br>
	*<ul><li>@ref D_DD_UDC_UDIE_OFF
	*<li>@ref D_DD_UDC_UDIE_ON</ul>
	*/
	kuchar		underOver;
	/*< CCR.CFIE: Count direction interrupt enable.<br>
	*<ul><li>@ref D_DD_UDC_CFIE_OFF
	*<li>@ref D_DD_UDC_CFIE_ON</ul>
	*After system reset, the state of count direction
	*is down count.<br>
	*Therefore, the count direction interruption is
	*generated in the up count after system reset.<br>
	*Please confirm the state of count direction by
	*the @ref Dd_UDC_Get_Up_Down_Flg function when
	*you use channel since the second times.<br>
	*/
	kuchar		cntDirInt;

	/*< callback function pointer*/
	DdUdcCallback	 pCallback;
};

struct _DdUdc
{
	KObject parent;
};

KConstType          dd_udc_get_type(void);
DdUdc*                 dd_udc_get(void);

#ifdef __cplusplus
extern "C" {
#endif

/*
*The UDC control register (all channels) is initialized.
*/
void                        dd_udc_init(DdUdc* self);

/*
*The UDC channel is exclusively controlled.<br>
*If UDC is unused, exclusive control OK is sent back as (Lock) while using it. <br>
*Exclusive control NG is sent back when using it (Lock inside of present).
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in]	timeOut	semaphore timeout value(milli seconds)/D_DDIM_USER_SEM_WAIT_POL(polling semaphore).<br>
*@retval D_DDIM_OK						OK
*@retval D_DD_UDC_EXT_LOCK_NG			Lock Error (System Using designated channel number)
*@retval D_DD_UDC_INPUT_PARAM_ERROR		Input Parameter Error
*@retval D_DD_UDC_SEM_TIMEOUT			Semaphore Timeout Error
*@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
*		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32	                    dd_udc_open(DdUdc* self, kuchar ch, kint32 timeOut);

/*
*The exclusive control of control Channel it is released.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*@retval D_DD_UDC_SEM_NG	Semaphore acquisition NG
*@remarks Please note that stop & exclusive control is compulsorily released when UDC is starting.
*@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32	                    dd_udc_close(DdUdc* self, kuchar ch);

/*
*Set common setting to each mode of UDC.<br>
*Set the callback function when interruption is generate to pCallback.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in]	udcCrl	UDC Start table pointer. See @ref DdUdcCtrlCmn
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*@retval D_DD_UDC_ERROR_BUSY		Macro Busy Error
*@remarks	The mode and the function that can be used with each channel
*@remarks	change by setting PERSEL2.UDCTRG register.<br>
*			Please refer to the following tables for details.<br><br>
*			<b>When PERSEL2.UDCTRG=0</b>
*			<table><tr><th rowspan=3>Channel</th>
*			           <th colspan=5>Count mode</th>
*			           <th rowspan=3>ZIN function <br> (*1)</th></tr>
*			       <tr><th rowspan=2>Timer</th>
*			           <th colspan=2>Up/Down count</th>
*			           <th rowspan=2>Phase lag count <br> (2 multiply)</th>
*			           <th rowspan=2>Phase lag count <br> (4 multiply)</th></tr>
*			       <tr><th>Up count <br> (AIN)</th>
*			           <th>Down count <br> (BIN)</th></tr>
*			       <tr align=center><td>0</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td></tr>
*			       <tr align=center><td>1</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td></tr>
*			       <tr align=center><td>2</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td></tr>
*   			       <tr align=center><td>3</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td></tr>
*			       <tr align=center><td>4</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td></tr>
*			       <tr align=center><td>5</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td></tr></table>
*			<br>
*			<b>When PERSEL2.UDCTRG=1</b>
*			<table><tr><th rowspan=3>Channel</th>
*			           <th colspan=5>Count mode</th>
*			           <th rowspan=3>ZIN function <br> (*1)</th></tr>
*			       <tr><th rowspan=2>Timer</th>
*			           <th colspan=2>Up/Down count</th>
*			           <th rowspan=2>Phase lag count <br> (2 multiply)</th>
*			           <th rowspan=2>Phase lag count <br> (4 multiply)</th></tr>
*			       <tr><th>Up count <br> (AIN)</th>
*			           <th>Down count <br> (BIN)</th></tr>
*			       <tr align=center><td>0</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td></tr>
*			       <tr align=center><td>1</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td> <td>o</td></tr>
*			       <tr align=center><td>2</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td> <td>x</td> <td>x</td></tr>
*			       <tr align=center><td>3</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td> <td>x</td> <td>x</td></tr>
*			       <tr align=center><td>4</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td> <td>x</td> <td>x</td></tr>
*			       <tr align=center><td>5</td> <td>o</td> <td>o</td> <td>o</td> <td>x</td> <td>x</td> <td>x</td></tr></table>
*			<br>
*			(*1) Please specify the following parameter when you do not use the ZIN function.<br>
*			@code
*			udcCrl.zinMode = D_DD_UDC_CGSC_CLEAR;
*			udcCrl.zinEdge = D_DD_UDC_CGE_NOT;
*			@endcode
*/
kint32                     dd_udc_ctrl_common(DdUdc* self, kuchar ch, DdUdcCtrlCmn const* const udcCrl);

/*
*Get common setting to each mode of UDC.<br>
*@param[in]	ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param[out]	udcCrl	UDC Start table pointer. See @ref DdUdcCtrlCmn
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                     dd_udc_get_ctrl_common(DdUdc* self, kuchar ch, DdUdcCtrlCmn* const udcCrl);

/*
*Set parameter only for the timer mode.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in]	prescaler	Built-in prescaler selection.(CCR.CLKS)<br>
*						Please specify either the following.<br>
*						- @ref D_DD_UDC_CLKS_2_CLOCK
*						- @ref D_DD_UDC_CLKS_8_CLOCK
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                     dd_udc_ctrl_timer(DdUdc* self, kuchar ch, kuchar prescaler);

/*
*Get parameter only for the timer mode.
*@param[in]	ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param[out]	prescaler	Built-in prescaler selection.(CCR.CLKS)<br>
*						- @ref D_DD_UDC_CLKS_2_CLOCK
*						- @ref D_DD_UDC_CLKS_8_CLOCK
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                     dd_udc_get_ctrl_timer(DdUdc* self, kuchar ch, kuchar* const prescaler);

/*
*Set parameter only for the up/down count mode.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in]	edge	Count clock edge.(CCR.CES)<br>
*					Please specify either the following.<br>
*					- @ref D_DD_UDC_CES_NOT
*					- @ref D_DD_UDC_CES_RISE
*					- @ref D_DD_UDC_CES_FALL
*					- @ref D_DD_UDC_CES_BOTH
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                     dd_udc_ctrl_up_down(DdUdc* self, kuchar ch, kuchar edge);

/*
*Get parameter only for the up/down count mode.
*@param[in]	ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param[out]	edge	Count clock edge.(CCR.CES)<br>
*					Please specify either the following.<br>
*					- @ref D_DD_UDC_CES_NOT
*					- @ref D_DD_UDC_CES_RISE
*					- @ref D_DD_UDC_CES_FALL
*					- @ref D_DD_UDC_CES_BOTH
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                     dd_udc_get_ctrl_up_down(DdUdc* self, kuchar ch, kuchar* const edge);

/*
*The UDC of a control channel is started.<br>
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32	                    dd_udc_start(DdUdc* self, kuchar ch);

/*
*The UDC of a control channel is stopped.<br>
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32	                    dd_udc_stop(DdUdc* self, kuchar ch);

/*
*Set count mode.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in]	countMode	Count mode.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CMS_TIMER
*				- @ref D_DD_UDC_CMS_UP_DOWN
*				- @ref D_DD_UDC_CMS_PHASE_LAG_2
*				- @ref D_DD_UDC_CMS_PHASE_LAG_4
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32	                    dd_udc_set_count_mode(DdUdc* self, kuchar ch, kuchar countMode);

/*
*Set the callback function when interruption is generate to pCallback.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in]	pCallback	Call Back function pointer
*/
void                       dd_udc_set_callback(DdUdc* self, kuchar ch, DdUdcCallback pCallback);

/*
*Set reload / compare counter.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in] rcr		Set reload / compare counter
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32	                   dd_udc_set_rcr_counter(DdUdc* self, kuchar ch, kushort rcr);

/*
*The Up/Down counter value is returned.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@retval UDCR counter value.<br>
*/
kushort	               dd_udc_get_udcr_counter(DdUdc* self, kuchar ch);

/*
*The input counter is set to UDCR register.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in] udcr	Set up/down counter value.
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_ERROR_BUSY		Macro Busy Error
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*@remarks	When the channel is working, it becomes an error.
*@remarks	This API uses DDIM_User_Dly_Tsk().
*/
kint32	                   dd_udc_set_udcr_counter(DdUdc* self, kuchar ch, kushort udcr);

/*
*The RDCC bit of the CCR register of the specified channel is cleared.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@retval D_DDIM_OK				OK
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32	                   dd_udc_force_clear_udcr(DdUdc* self, kuchar ch);

/*
*Get kind of the count immediately before.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@retval	D_DD_UDC_UDF_NON	no input
*@retval	D_DD_UDC_UDF_DOWN	down count
*@retval	D_DD_UDC_UDF_UP		up count
*@retval	D_DD_UDC_UDF_BOTH	up and down count
*/
kuchar                   dd_udc_get_up_down_flg(DdUdc* self, kuchar ch);

/*
 * 获取私有变量及私有方法
 */
DdUdcCallback    dd_udc_get_p_callback(DdUdc* self, kuchar ch);
kint32                    dd_udc_get_chk_ch_number(DdUdc* self, kuchar ch);

/*
@weakgroup dd_udc
@{
<hr>

@section dd_udc_sample_section1	Sample of Up/Down count mode.
	The precondition of the this sample is as follows.<br>
	<ul>
	  <li>Channel 1 is used.</li>
	  <li>Down count is done by the rising edge of BIN.</li>
	  <li>It processes by the first 20 counts, and it stops by the following 80 counts.</li>
	</ul>
    @code
	kuchar gCounter = 0;

	void udc_sample_execute_down_count(void)
	{
		DdUdcCtrlCmn udcCrl;
		kuchar ch;
		kint32 ercd;

		ch       = D_DD_UDC_CH1;
		gCounter = 0;

		udcCrl.countMode  = D_DD_UDC_CMS_UP_DOWN;
		udcCrl.udcr        = 20;
		udcCrl.rcr         = 80;
		udcCrl.compClear  = D_DD_UDC_UCRE_OFF;
		udcCrl.reload      = D_DD_UDC_RLDE_ON;
		udcCrl.zinMode    = D_DD_UDC_CGSC_CLEAR;
		udcCrl.zinEdge    = D_DD_UDC_CGE_NOT;
		udcCrl.cmpInt     = D_DD_UDC_CITE_OFF;
		udcCrl.underOver  = D_DD_UDC_UDIE_ON;
		udcCrl.cntDirInt = D_DD_UDC_CFIE_OFF;
		udcCrl.pCallback   = udc_sample_callback;

		// UDC open.
		ercd = Dd_UDC_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// Set common execution parameter.
		ercd = Dd_UDC_Ctrl_Common(ch, &udcCrl);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}
		// Set execution parameter only for up/doun count mode.
		ercd = Dd_UDC_Ctrl_Up_Down(ch, D_DD_UDC_CES_RISE);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// AIN pull-down enable (Because AIN doesn't use in down count)
		Dd_Top_Set_GPIO5_Control(PUDCR, 3, 0);
		Dd_Top_Set_GPIO5_Control(PUDER, 3, 1);

		// UDC start
		ercd = Dd_UDC_Start(ch);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}
	}

	void udc_sample_callback(kuchar ch, kint32 factor)
	{
		kint32 ercd;

		if ((ch == D_DD_UDC_CH1) && (factor == D_DD_UDC_UNDER_FLOW)) {

			gCounter++;

			if (gCounter == 1) {
				// The processing of first 20 counts is executed here.
			}
			else if (gCounter >= 2) {
				// UDC stop.
				ercd = Dd_UDC_Stop(ch);
				if (result != D_DDIM_OK) {
					// Error processing
					return;
				}

				// AIN pull-down disable
				Dd_Top_Set_GPIO5_Control(PUDER, 3, 0);

				// UDC close.
				ercd = Dd_UDC_Close(ch);
				if (result != D_DDIM_OK) {
					// Error processing
					return;
				}

				// The processing of sencond 80 counts is executed here.
			}
		}
	}
	@endcode

@section dd_udc_sample_section2	Sample of phase lag count mode (2 multiply).
	The precondition of the this sample is as follows.<br>
	<ul>
	  <li>Channel 0 is used.</li>
	  <li>When the direction of the count changes, arbitrary processing is done.</li>
	  <li>It doesn't count between ZIN input level is high.</li>
	</ul>
    @code
	void udc_sample_execute_down_count(void)
	{
		DdUdcCtrlCmn udcCrl;
		kuchar ch;
		kint32 ercd;

		ch = D_DD_UDC_CH0;

		udcCrl.countMode  = D_DD_UDC_CMS_PHASE_LAG_2;
		udcCrl.udcr        = 0;
		udcCrl.rcr         = 0;
		udcCrl.compClear  = D_DD_UDC_UCRE_OFF;
		udcCrl.reload      = D_DD_UDC_UCRE_OFF;
		udcCrl.zinMode    = D_DD_UDC_CGSC_GATE;
		udcCrl.zinEdge    = D_DD_UDC_CGE_RISE_H;
		udcCrl.cmpInt     = D_DD_UDC_CITE_OFF;
		udcCrl.underOver  = D_DD_UDC_UCRE_OFF;
		udcCrl.cntDirInt = D_DD_UDC_CFIE_ON;
		udcCrl.pCallback   = udc_sample_callback;

		// UDC open.
		ercd = Dd_UDC_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// Set execution parameter.
		ercd = Dd_UDC_Ctrl_Common(ch, &udcCrl);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// It changes to the setting for which ZIN control can be used by channel 0, 1.
		Dd_Top_Set_PERSEL2_UDCTRG(1);

		// UDC start
		ercd = Dd_UDC_Start(ch);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}
	}

	void udc_sample_callback(kuchar ch, kint32 factor)
	{
		if ((ch == D_DD_UDC_CH0) && (factor == D_DD_UDC_COUNT_DIRECTION)) {
			// The processing is executed here.
		}
	}
	@endcode

@section dd_udc_sample_section3	Sample of phase lag count mode (4 multiply).
	The precondition of the this sample is as follows.<br>
	<ul>
	  <li>Channel 2 is used.</li>
	  <li>When the direction of the count changes into the down count, arbitrary processing is done.</li>
	</ul>
    @code
	void udc_sample_execute_down_count(void)
	{
		DdUdcCtrlCmn udcCrl;
		kuchar ch;
		kint32 ercd;

		ch = D_DD_UDC_CH2;

		udcCrl.countMode  = D_DD_UDC_CMS_PHASE_LAG_4;
		udcCrl.udcr        = 0;
		udcCrl.rcr         = 0;
		udcCrl.compClear  = D_DD_UDC_UCRE_OFF;
		udcCrl.reload      = D_DD_UDC_UCRE_OFF;
		udcCrl.zinMode    = D_DD_UDC_CGSC_CLEAR;
		udcCrl.zinEdge    = D_DD_UDC_CGE_NOT;
		udcCrl.cmpInt     = D_DD_UDC_CITE_OFF;
		udcCrl.underOver  = D_DD_UDC_UCRE_OFF;
		udcCrl.cntDirInt = D_DD_UDC_CFIE_ON;
		udcCrl.pCallback   = udc_sample_callback;

		// UDC open.
		ercd = Dd_UDC_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// Set execution parameter.
		ercd = Dd_UDC_Ctrl_Common(ch, &udcCrl);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// It changes to the setting for which phase lag count mode can be used by channel 2, 3.
		Dd_Top_Set_PERSEL2_UDCTRG(0);

		// UDC start
		ercd = Dd_UDC_Start(ch);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}
	}

	void udc_sample_callback(kuchar ch, kint32 factor)
	{
		kuchar up_down_flag;

		if ((ch == D_DD_UDC_CH2) && (factor == D_DD_UDC_COUNT_DIRECTION)) {
			// Get up/down flag
			up_down_flag = Dd_UDC_Get_Up_Down_Flg(ch);

			if ((up_down_flag == D_DD_UDC_UDF_DOWN) || (up_down_flag == D_DD_UDC_UDF_BOTH)) {
				// The processing is executed here.
			}
		}
	}
	@endcode

@section dd_udc_sample_section4	Sample of Timer mode.
	The precondition of the this sample is as follows.<br>
	<ul>
	  <li>Channel 0 is used.</li>
	  <li>It processes every 100 counts, and it stops by 1000 counts.</li>
	</ul>
    @code
	kuchar gCounter = 0;

	void udc_sample_execute_timer(void)
	{
		DdUdcCtrlCmn udcCrl;
		kuchar ch;
		kint32 ercd;

		ch       = D_DD_UDC_CH0;
		gCounter = 0;

		udcCrl.countMode  = D_DD_UDC_CMS_TIMER;
		udcCrl.udcr        = 100;
		udcCrl.rcr         = 100;
		udcCrl.compClear  = D_DD_UDC_UCRE_OFF;
		udcCrl.reload      = D_DD_UDC_RLDE_ON;
		udcCrl.zinMode    = D_DD_UDC_CGSC_CLEAR;
		udcCrl.zinEdge    = D_DD_UDC_CGE_NOT;
		udcCrl.cmpInt     = D_DD_UDC_CITE_OFF;
		udcCrl.underOver  = D_DD_UDC_UDIE_ON;
		udcCrl.cntDirInt = D_DD_UDC_CFIE_OFF;
		udcCrl.pCallback   = udc_sample_callback;

		// UDC open.
		ercd = Dd_UDC_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// Set common execution parameter.
		ercd = Dd_UDC_Ctrl_Common(ch, &udcCrl);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}
		// Set execution parameter only for timer mode.
		ercd = Dd_UDC_Ctrl_Timer(ch, D_DD_UDC_CLKS_2_CLOCK);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// UDC start
		ercd = Dd_UDC_Start(ch);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}
	}

	void udc_sample_callback(kuchar ch, kint32 factor)
	{
		kint32 ercd;

		if ((ch == D_DD_UDC_CH0) && (factor == D_DD_UDC_UNDER_FLOW)) {

			gCounter++;

			if (gCounter >= 10) {
				// UDC stop.
				ercd = Dd_UDC_Stop(ch);
				if (result != D_DDIM_OK) {
					// Error processing
					return;
				}

				// UDC close.
				ercd = Dd_UDC_Close(ch);
				if (result != D_DDIM_OK) {
					// Error processing
					return;
				}
			}

			// The processing of every 100 counts is executed here.
		}
	}
	@endcode

@section dd_udc_sample_section5	Sample of timer utility function.
	The precondition of the this sample is as follows.
	<ul>
	  <li>Channel 0 is used.</li>
	  <li>100ms is counted. </li>
	</ul>
	@code
	void udc_sample_timer_utility_function(void)
	{
		kuchar ch;
		kint32 ercd;

		ch = D_DD_UDC_CH0;

		// UDC open.
		ercd = Dd_UDC_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		//Set execution parameter.
		ercd = Dd_UDC_Write_Timer_Mode(ch, 100000, udc_sample_callback);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}

		// UDC start
		ercd = Dd_UDC_Start(ch);
		if (result != D_DDIM_OK) {
			// Error processing
			return;
		}
	}

	void udc_sample_callback(kuchar ch)
	{
		kint32 ercd;

		if ((ch == D_DD_UDC_CH0) && (factor == D_DD_UDC_UNDER_FLOW)) {

			gTimer_Flag == 1;

			if (gTimer_Flag != 0) {
				// UDC close.
				ercd = Dd_UDC_Close(ch);
				if (ercd != D_DDIM_OK) {
					// Error processing
					return;
				}
			}
		}
	}

	@endcode
*/
#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* __DD_UDC_H__ */
