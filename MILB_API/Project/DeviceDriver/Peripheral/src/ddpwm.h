/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :PWM driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

/*
@addtogroup dd_pwm
@{
	- @ref PWM_initialization <br>
	- @ref PWM_start_ABCD <br>
	- @ref PWM_start_E <br>
	- @ref PWM_start_timer <br>
	- @ref PWM_end_ABCD <br>
	- @ref PWM_end_E <br>
	- @ref PWM_Sample_TimerABCD <br>
	- @ref PWM_Sample_TimerE <br>
	- @ref PWM_Sample_Oneshot <br>
	- @ref PWM_Sample_Step <br>

	<hr>
	@section PWM_initialization	Sequence of PWM Initialization
	@image html dd_pwm_init.png

	@section PWM_start_ABCD	Sequence of PWM Operation Start by Software Trigger(for Timer ABCD)
	@image html dd_pwm_start_abcd.png

	@section PWM_start_E	Sequence of PWM Operation Start by Software Trigger(for Timer E)
	@image html dd_pwm_start_e.png

	@section PWM_start_timer	Sequence of PWM Operation Start by Timer Trigger(for Timer ABCD)
	@image html dd_pwm_start_timer.png

	@section PWM_end_ABCD	Sequence of PWM Operation End(for Timer ABCD)
	@image html dd_pwm_end_abcd.png

	@section PWM_end_E	Sequence of PWM Operation End(for Timer E)
	@image html dd_pwm_end_e.png

*/

#ifndef __DD_PWM_H__
#define __DD_PWM_H__

#include <klib.h>
#include "ddpwmbranch.h"

#define DD_TYPE_PWM                        (dd_pwm_get_type())
#define DD_PWM(obj)                          K_TYPE_CHECK_INSTANCE_CAST(obj, DdPwm)
#define DD_IS_PWM(obj)                     K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_PWM)

typedef struct _DdPwm                       DdPwm;
typedef struct _DdPwmPrivate           DdPwmPrivate;

struct _DdPwm
{
	KObject parent;
};

KConstType                                     dd_pwm_get_type(void);
DdPwm*                                          dd_pwm_get(void);

#ifdef __cplusplus
extern "C" {
#endif
/*
The PWM control register (all channels) is initialized.
*/
void                                                  dd_pwm_init(DdPwm* self);

/*
*Execute exclusive control for designated PWM channel.<br>
*When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return "D_DDIM_OK",<br>
*if the channel state is in-use (lock), return "D_DD_PWM_SEM_NG".<br>
*When timeout occurs, return "D_DD_PWM_SEM_TIMEOUT".
*@param [in] ch		Channel number (0 to 15)<br>
*@param [in] tmout	Time of timeout<br>
*					<ul><li>Positive Value(Time of timeout)
*						<li>@ref D_DDIM_USER_SEM_WAIT_POL
*						<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@retval D_DD_PWM_SEM_TIMEOUT		Semaphore acquisition Time Out
*@retval D_DD_PWM_SEM_NG				Semaphore acquisition NG
*@remarks Please call Dd_PWM_Open_Timer_E when timer E is used.
*@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
*		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32                                                dd_pwm_open(DdPwm* self, kuint32 ch, kint32 tmout);

/*
*Cancel exclusive control for designated PWM channel.<br>

*@param [in] ch	Channel number (0 to 15)<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@retval	D_DD_UART_SEM_NG			Semaphore release NG
*@remarks
*		- Please note that stop & exclusive control is compulsorily released when PWM is starting.
*		- Please call Dd_PWM_Close_Timer_E when timer E is used.
*@remarks	This API uses DDIM_User_Sig_Sem().
*/
kint32                                                dd_pwm_close(DdPwm* self, kuint32 ch);

/*
*Execute exclusive control for designated PWM Tier-E channel.<br>
*When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return "D_DDIM_OK",<br>
*if the channel state is in-use (lock), return "D_DD_PWM_SEM_NG".<br>
*When timeout occurs, return "D_DD_PWM_SEM_TIMEOUT".
*@param [in] ch	Channel number (0, 4, 8, 12)
*@param [in] tmout	Time of timeout<br>
*					<ul><li>Positive Value(Time of timeout)
*						<li>@ref D_DDIM_USER_SEM_WAIT_POL
*						<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@retval D_DD_PWM_SEM_TIMEOUT		Semaphore acquisition Time Out
*@retval D_DD_PWM_SEM_NG				Semaphore acquisition NG
*@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
*		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32                                                dd_pwm_open_timer_e(DdPwm* self, kuint32 ch, kint32 tmout);

/*
*Cancel exclusive control for designated PWM channel for Timer E.
*@param [in] ch	Channel number (0, 4, 8, 12)
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@retval	D_DD_UART_SEM_NG			Semaphore release NG
*@remarks Please note that stop & exclusive control is compulsorily released when PWM is starting.
*@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32                                                dd_pwm_close_timer_e(DdPwm* self, kuint32 ch);

/*
*The PWM operational condition of a control channel is set.<br>
*Set the callback function when interruption is generate to pCallBack.
*@param [in]		ch				Channel number (0 to 15).<br>
*	When timer E is set, (0 to 3) means hardware block number is 0,<br>
*	(4 to 7) means hardware block number is 1, <br>
*	(8 to 11) means hardware block number is 2,<br>
*	(12 to 15) means hardware block number is 3.
*@param [in]    *pwmCtrlCmn	PWM Start table pointer. See @ref DdPwmCtrlCmn.<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                                dd_pwm_ctrl_common(DdPwm* self, kuint32 ch,
		                                                          DdPwmCtrlCmn const* const pwmCtrlCmn);

/*
*The PWM operational condition of a control channel is set.<br>
*Set the callback function when interruption is generate to pCallBack.
*@param [in]		ch				Channel number (0 to 15).<br>
*	When timer E is set, (0 to 3) means hardware block number is 0,<br>
*	(4 to 7) means hardware block number is 1, <br>
*	(8 to 11) means hardware block number is 2,<br>
*	(12 to 15) means hardware block number is 3.
*@param [in]    *pwmCtrlCmn	PWM Start table pointer. See @ref DdPwmCtrlCmn.<br>
*@param [in]    prevEn	reverse resister enable(1)/disable(0).<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                                dd_pwm_ctrl_common2(DdPwm* self, kuint32 ch,
		                                                          DdPwmCtrlCmn const* const pwmCtrlCmn,
		                                                          kuchar prevEn);

/*
*The PWM operational condition of a control channel is get.<br>
*@param [in]		ch				Channel number (0 to 15).<br>
*@param [in]    *pwmCtrlCmn	PWM Start table pointer. See @ref DdPwmCtrlCmn.<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                                dd_pwm_get_ctrl_common(DdPwm* self, kuint32 ch,
		                                                          DdPwmCtrlCmn* const pwmCtrlCmn);

/*
*The PWM Timer A,B,C,D is set.<br>
*@param [in]		ch				Channel number (0 to 15).<br>
*@param [in]    *pwmCtrlTimerAbcd	PWM Start table pointer. See @ref DdpwmCtrlTimerAbcd.<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                                dd_pwm_ctrl_timer_abcd(DdPwm* self, kuint32 ch,
		                                                          DdpwmCtrlTimerAbcd const* const pwmCtrlTimerAbcd);

/*
*The PWM Timer A,B,C,D is set.<br>
*@param [in]		ch				Channel number (0 to 15).<br>
*@param [in]    *pwmCtrlTimerAbcd	PWM Start table pointer. See @ref DdpwmCtrlTimerAbcd.<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                                dd_pwm_ctrl_timer_abcd_2ch(DdPwm* self, kuint32 ch,
		                                                     DdpwmCtrlTimerAbcd2ch const* const pwmCtrlTimerAbcd2ch);

/*
*The PWM Timer E is set.<br>
*@param [in]		ch		Channel number (0 to 15).<br>
*						(0 to 3) means hardware block number is 0,<br>
*						(4 to 7) means hardware block number is 1,<br>
*						(8 to 11) means hardware block number is 2,<br>
*						(12 to 15) means hardware block number is 3.
*@param [in]    *pwmCtrlTimerE	PWM Start table pointer. See @ref PwmCtrlTimerE.<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                                dd_pwm_ctrl_timer_e(DdPwm* self, kuint32 ch,
		                                                          PwmCtrlTimerE const* const pwmCtrlTimerE);

/*
 * 子类公有方法封装
 */
kint32                                                dd_pwm_start(DdPwm* self, kuint32 ch);
kint32                                                dd_pwm_2ch_start(DdPwm* self,
		                                                        kuint32 chA, kuint32 chB);
kint32                                                dd_pwm_stop(DdPwm* self, kuint32 ch);
kint32                                                dd_pwm_get_timer(DdPwm* self, kuint32 ch,
		                                                        kushort* timerVal, kushort* timerEVal);
kint32                                                dd_pwm_get_pulse_num(DdPwm* self,
		                                                        kuint32 ch, kulong* pulseNum);
kint32                                                dd_pwm_get_interrupt_flag(DdPwm* self,
		                                                        kuint32 ch, kushort* intFlgCtrl0, kushort* intFlgCtrl1);
kint32                                                dd_pwm_set_interrupt_flag(DdPwm* self, kuint32 ch,
		                                                        kushort intFlgCtrl0, kushort intFlgCtrl1);
kint32                                                dd_pwm_get_channel_assign(DdPwm* self,
		                                                        kuint32 ch, kuchar* chAssign);
kint32                                                dd_pwm_set_channel_assign(DdPwm* self,
		                                                        kuint32 ch, kuchar chAssign);
kboolean                                          dd_pwm_get_int_stat(DdPwm* self, kuint32 ch);
void                                                  dd_pwm_int_handler(DdPwm* self, kuint32 ch);
void                                                  dd_pwm_int_handler_stp(DdPwm* self, kuint32 ch);
kint32                                                dd_pwm_set_stopped_output_mask(DdPwm* self,
		                                                        kuint32 ch, kuchar mask);
kint32                                                dd_pwm_get_stopped_output_mask(DdPwm* self,
		                                                        kuint32 ch, kuchar* mask);
kint32                                                dd_pwm_get_clock_sel_timer_e(DdPwm* self,
		                                                        kuint32 ch, kuchar* clock);
kint32                                                dd_pwm_get_stopped_output_status(DdPwm* self,
		                                                        kuint32 ch, kuchar* chStatus);

/*
 * 获取、设置其子类方法及属性
 */
volatile union io_pwm_pcn*      dd_pwm_get_branch_func_pcn_addr(DdPwm* self, kuint32 ch);   //TODO

DdPwmCtrlMemo                           dd_pwm_get_branch_ctrl_memo(DdPwm* self, kuint32 ch);

void                                                 dd_pwm_set_branch_dma_enable(DdPwm* self, kuint32 ch,
		                                                         kuchar dmaEnable);
void                                                 dd_pwm_set_branch_dma_ch(DdPwm* self,
		                                                         kuint32 ch, kuchar dmaCh);
void                                                 dd_pwm_set_branch_cyc_num(DdPwm* self,
		                                                         kuint32 ch, kushort cycNum);
void                                                 dd_pwm_set_branch_duty_num(DdPwm* self, kuint32 ch,
		                                                         kushort dutyNum);
void                                                 dd_pwm_set_branch_clk_sel(DdPwm* self,
		                                                         kuint32 ch, kuchar clkSel);

#ifdef __cplusplus
}
#endif

/*
@weakgroup dd_pwm
@{

	<br>
	<br>
	The example of PWM is as follows.
	<hr>
	@section PWM_Sample_TimerABCD		Sample of PWM with Timer A,B,C,D

@code
	void PWM_Sample_TimerABCD()
	{
		kint32						ret;
		DdPwmCtrlCmn			ctrl_cmn;
		DdpwmCtrlTimerAbcd	ctrl_abcd;
		kushort						cyc_time	= 60000;	// wave cycle(usec)
		kuchar						duty		= 50;		// 50%

		Dd_PWM_Init();			// After power on and the reset, this is executed only once.

		ret = Dd_PWM_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Open !!\n"));
			return;
		}

		ctrl_cmn.drv_mode		= D_DD_PWM_PCNHL_MDSE_PWM;		// PWM or One-Shot operation
		ctrl_cmn.restart_trig	= D_DD_PWM_PCNHL_RTRG_OFF;		// restart enable
		ctrl_cmn.out_mask		= D_DD_PWM_PCNHL_PGMS_L;		// output level mask
		ctrl_cmn.edge			= D_DD_PWM_PCNHL_EGS_RISE;		// edge enable select
		ctrl_cmn.int_enable		= D_DD_PWM_PCNHL_IREN_OFF;		// interrupt enable
		ctrl_cmn.trigger		= D_DD_PWM_PCNHL_IRS_TRG;		// interrupt factor
		ctrl_cmn.polarity		= D_DD_PWM_PCNHL_OSEL_NORMAL;	// output polarity
		ctrl_cmn.in_trigger		= D_DD_PWM_GCN_TSEL_EM0;		// trigger input factor
		ctrl_cmn.tim_e_enable	= D_DD_PWM_GCN_TMEEN_OFF;		// Timer E disable
		ctrl_cmn.ch_assign		= D_DD_PWM_GCN_CHAS_ABCD;		// channel assignment
		ctrl_cmn.pCallBack		= (VP_CALLBACK_PWM)sample_func;	// callback function pointer

		ctrl_abcd.cyc_time		= cyc_time;						// wave cycle(usec)

		ret = Dd_PWM_Calculate(ctrl_abcd.cyc_time, &ctrl_cmn.clk_sel, &ctrl_abcd.cycNum);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM cycle calculate !!\n"));
			return;
		}

		ret = Dd_PWM_Ctrl_Common(ch, &ctrl_cmn);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Ctrl !!\n"));
		}

		ret = Dd_PWM_Ctrl_Timer_ABCD(ch, &ctrl_abcd);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Timer A,B,C,D Ctrl !!\n"));
		}

		ret = Dd_PWM_Write_Cycle_Duty(ch, ctrl_abcd.cycNum, duty, ctrl_cmn.clk_sel);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Change cycle and duty !!\n"));
		}

		ret = Dd_PWM_Start(ch);
		Ddim_Print(("PWM Start !!\n"));
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Start !!\n"));
		}

	//--------------------------------------------------------
	// It is a termination as follows.
	// Please execute it after completing processing.

		ret = Dd_PWM_Stop(ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Stop !!\n"));
		}

		ret = Dd_PWM_Close(ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Close !!\n"));
		}
	}
@endcode

	<br>
	<br>
	@section PWM_Sample_TimerE			Sample of PWM with Timer E

@code
	void PWM_Sample_TimerE()
	{
		kint32						ret;
		DdPwmCtrlCmn			ctrl_cmn;
		PwmCtrlTimerE		ctrl_e;
		kuint32						ch			= 4;		// used channel number. 0, 4, 8, 12 are valid.
		kushort						cyc_time	= 60000;	// wave cycle(usec)
		kushort						cycNum;
		kuchar						ch_in_blk;

		ch_in_blk = (D_DD_PWM_CH_NUM_IN_BLOCK - 1) & ch;

		Dd_PWM_Init();			// After power on and the reset, this is executed only once.

		ret = Dd_PWM_Open_Timer_E(ch, D_DDIM_USER_SEM_WAIT_POL);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Open !!\n"));
			return;
		}

		ctrl_cmn.drv_mode				= D_DD_PWM_PCNHL_MDSE_PWM;		// PWM or One-Shot operation
		ctrl_cmn.restart_trig			= D_DD_PWM_PCNHL_RTRG_OFF;		// restart disable
		ctrl_cmn.out_mask				= D_DD_PWM_PCNHL_PGMS_L;		// output level mask
		ctrl_cmn.edge					= D_DD_PWM_PCNHL_EGS_RISE;		// edge enable select
		ctrl_cmn.int_enable				= D_DD_PWM_PCNHL_IREN_OFF;		// interrupt disable
		ctrl_cmn.trigger				= D_DD_PWM_PCNHL_IRS_TRG;		// interrupt factor
		ctrl_cmn.polarity				= D_DD_PWM_PCNHL_OSEL_NORMAL;	// output polarity
		ctrl_cmn.in_trigger				= D_DD_PWM_GCN_TSEL_EM0;		// trigger input factor
		ctrl_cmn.tim_e_enable			= D_DD_PWM_GCN_TMEEN_ON;		// Timer E disable
		ctrl_cmn.ch_assign				= D_DD_PWM_GCN_CHAS_ABCD;		// channel assignment
		ctrl_cmn.pCallBack				= (VP_CALLBACK_PWM)sample_func;	// callback function pointer

		ctrl_e.hold[0]					= 1;
		ctrl_e.hold[1]					= 1;
		ctrl_e.hold[2]					= 1;
		ctrl_e.hold[3]					= 1;
		ctrl_e.force_val[0]				= 0;
		ctrl_e.force_val[1]				= 1;
		ctrl_e.force_val[2]				= 1;
		ctrl_e.force_val[3]				= 0;
		ctrl_e.force[0]					= 1;
		ctrl_e.force[1]					= 1;
		ctrl_e.force[2]					= 1;
		ctrl_e.force[3]					= 1;
		ctrl_e.empty_dma_req			= D_DD_PWM_PCHSET_RQTIM_4;		// Inerrupt request timing for DMA
		ctrl_e.undr_run_enable			= D_DD_PWM_PCHSET_UDEN_OFF;		// speed down setting under run error
		ctrl_e.undr_run_int_err_enable	= D_DD_PWM_PINTCT_UIE_OFF;		// interrupt enable under run error
		ctrl_e.force_stop_int_enable	= D_DD_PWM_PINTCT_FIE_OFF;		// interrupt enable for force stop
		ctrl_e.auto_stop_int_enable		= D_DD_PWM_PINTCT_AIE_OFF;		// interrupt enable for auto stop
		ctrl_e.dma_int_enable			= D_DD_PWM_PINTCT_DRQE_OFF;		// interrupt enable for dma

		ret = Dd_PWM_Calculate(cyc_time, &ctrl_cmn.clk_sel, &cycNum);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM cycle calculate !!\n"));
			return;
		}

		cycNum[0]		= cycNum;				// cycle : 60msec
		duty_num[0]		= cycNum >> 1;			// duty  : 50%	(30msec)
		pulse_num[0]	= 30;					// 30 times
		link[0]			= 1;					// continue

		cycNum[1]		= cycNum / 6;			// cycle : 10msec
		duty_num[1]		= (cycNum / 6) >> 1;	// duty  : 50%	(5msec)
		pulse_num[1]	= 15;					// 15 times
		link[1]			= 0;					// last

		ret = Dd_PWM_Ctrl_Common(ch, &ctrl_cmn);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Ctrl !!\n"));
		}

		ret = Dd_PWM_Ctrl_Timer_E(ch, &ctrl_e);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Timer E Ctrl !!\n"));
		}

		ret = Dd_PWM_Start(ch);
		Ddim_Print(("PWM Start !!\n"));
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Start !!\n"));
		}

	//--------------------------------------------------------
	// It is a termination as follows.
	// Please execute it after completing processing.

		ret = Dd_PWM_Stop(ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Stop !!\n"));
		}

		ret = Dd_PWM_Close_Timer_E(ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Close !!\n"));
		}
	}
@endcode

	<br>
	<br>
	@section PWM_Sample_Oneshot			Sample of Oneshot utility

@code
	void PWM_Sample_Oneshot()
	{
		kint32						ret;
		DdPwmCtrlCmn			ctrl_cmn;
		DdpwmCtrlTimerAbcd	ctrl_abcd;
		kuint32						ch			= 2;		// used channel number
		kushort						cyc_time	= 60000;	// wave cycle(usec)
		kushort						duty_time	= 30000;	// duty time(usec)

		Dd_PWM_Init();			// After power on and the reset, this is executed only once.

		ret = Dd_PWM_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Open !!\n"));
			return;
		}

		ctrl_cmn.restart_trig	= D_DD_PWM_PCNHL_RTRG_OFF;		// restart enable
		ctrl_cmn.out_mask		= D_DD_PWM_PCNHL_PGMS_L;		// output level mask
		ctrl_cmn.edge			= D_DD_PWM_PCNHL_EGS_RISE;		// edge enable select
		ctrl_cmn.int_enable		= D_DD_PWM_PCNHL_IREN_OFF;		// interrupt enable
		ctrl_cmn.trigger		= D_DD_PWM_PCNHL_IRS_TRG;		// interrupt factor
		ctrl_cmn.polarity		= D_DD_PWM_PCNHL_OSEL_NORMAL;	// output polarity
		ctrl_cmn.in_trigger		= ch;							// trigger input factor
		ctrl_cmn.tim_e_enable	= D_DD_PWM_GCN_TMEEN_OFF;		// Timer E disable
		ctrl_cmn.ch_assign		= D_DD_PWM_GCN_CHAS_ABCD;		// channel assignment
		ctrl_cmn.pCallBack		= (VP_CALLBACK_PWM)sample_func;	// callback function pointer

		ctrl_abcd.cyc_time		= cyc_time;						// wave cycle(usec)

		ret = Dd_PWM_Write_Oneshot(ch, duty_time, &ctrl_cmn, &ctrl_abcd);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Set onshot !!\n"));
			return;
		}

		ret = Dd_PWM_Start(ch);
		Ddim_Print(("PWM Start !!\n"));
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Start !!\n"));
		}
	}
@endcode

	<br>
	<br>
	@section PWM_Sample_Step			Sample of Stepping motor utility

@code
	// PWM stepping data
	static T_DD_PWM_TIMER_E_STEPS_DATA gSample_DD_PWM_Step_Data[16] = {
	//	cycNum,	duty_num,				pulse_num(link)
		50625,		(50625 / 8 * 6),		512 + (1 << 15),
		50625,		(50625 / 8 * 6),		512 + (1 << 15),
		50625,		(50625 / 8 * 6),		512 + (1 << 15),
		50625,		(50625 / 8 * 6),		512 + (1 << 15),
		50625,		(50625 / 8 * 4),		512 + (1 << 15),
		50625,		(50625 / 8 * 4),		512 + (1 << 15),
		50625,		(50625 / 8 * 4),		512 + (1 << 15),
		50625,		(50625 / 8 * 4),		512 + (1 << 15),
		50625,		(50625 / 8 * 3),		512 + (1 << 15),
		50625,		(50625 / 8 * 3),		512 + (1 << 15),
		50625,		(50625 / 8 * 3),		512 + (1 << 15),
		50625,		(50625 / 8 * 3),		512 + (1 << 15),
		50625,		(50625 / 8 * 2),		512 + (1 << 15),
		50625,		(50625 / 8 * 2),		512 + (1 << 15),
		50625,		(50625 / 8 * 2),		512 + (1 << 15),
		50625,		(50625 / 8 * 2),		512 + (0 << 15)
	};
	static T_DD_PWM_TIMER_E_STEPS_DATA* gSample_DD_PWM_Step_Data_p = gSample_DD_PWM_Step_Data;

	// PWM Under run data
	static T_DD_PWM_TIMER_E_STEPS_DATA gSample_PWM_Under_Run_Data[4] = {
	//	cycNum,	duty_num,				pulse_num(link)
		52000,		(52000 / 8 * 2),		512 + (1 << 15),
		54000,		(54000 / 8 * 3),		512 + (1 << 15),
		56000,		(56000 / 8 * 4),		512 + (1 << 15),
		58000,		(58000 / 8 * 6),		512 + (0 << 15)
	};
	static T_DD_PWM_TIMER_E_STEPS_DATA* gSample_PWM_Under_Run_Data_p = gSample_PWM_Under_Run_Data;


	void PWM_Sample_Step()
	{
		kint32			ret;
		T_DD_PWM_STEP	pwm_stp;
		kuint32			ch	= 4;		// used channel number

		Dd_PWM_Init();					// After power on and the reset, this is executed only once.

		ret = Dd_PWM_Open_Timer_E(ch, D_DDIM_USER_SEM_WAIT_POL);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Open E !!\n"));
			return;
		}

		pwm_stp.clk_sel				= D_DD_PWM_PCNHL_CKS_DIV_16;
		pwm_stp.polarity			= D_DD_PWM_PCNHL_OSEL_NORMAL;
		pwm_stp.ch_assign			= D_DD_PWM_GCN_CHAS_ABCD;
		pwm_stp.hold[0]				= 1;
		pwm_stp.hold[1]				= 1;
		pwm_stp.hold[2]				= 1;
		pwm_stp.hold[3]				= 1;
		pwm_stp.force[0]			= 0;
		pwm_stp.force[1]			= 1;
		pwm_stp.force[2]			= 1;
		pwm_stp.force[3]			= 0;
		pwm_stp.step_data_num		= 16;
		pwm_stp.step_data			= gSample_DD_PWM_Step_Data_p;
		pwm_stp.undr_run_data_num	= 4;
		pwm_stp.under_run_data		= gSample_PWM_Under_Run_Data_p;
		pwm_stp.pCallBack			= (VP_CALLBACK_PWM)sample_func;

		ret = Dd_PWM_Write_Step(ch, 0, &pwm_stp);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Set step !!\n"));
			return;
		}

		ret = Dd_PWM_Start(ch);
		Ddim_Print(("PWM Start !!\n"));
		if (ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Start !!\n"));
		}
	}
@endcode
@}*/

#endif /* __DD_PWM_H__ */
