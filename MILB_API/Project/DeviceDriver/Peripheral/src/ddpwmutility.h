/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :PWM driver(utility  section)
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#ifndef __DD_PWM_UTILITY_H__
#define __DD_PWM_UTILITY_H__

#include <klib.h>
#include "ddpwm.h"

#define DD_TYPE_PWM_UTILITY                     (dd_pwm_utility_get_type())
#define DD_PWM_UTILITY(obj)                       K_TYPE_CHECK_INSTANCE_CAST(obj, DdPwmUtility)
#define DD_IS_PWM_UTILITY(obj)                  K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_PWM_UTILITY)

typedef struct _DdPwmUtility                         DdPwmUtility;
typedef struct _DdPwmUtilityPrivate            DdPwmUtilityPrivate;

struct _DdPwmUtility
{
	KObject parent;
};

KConstType                         dd_pwm_utility_get_type(void);
DdPwmUtility*                   dd_pwm_utility_get(void);

#ifdef CO_DDIM_UTILITY_USE
/* @name Utility Functions
@{*/

/*
*Cycle parameters are calculated according to the designated time (u sec).<br>
*If it doesn't calculate, Input Parameter Error is returned.<br>
*One dividing frequency that can be divided is raised when the count value <br>
*overflows since it calculates and it calculates again.<br>
*In that case, "D_DD_PWM_OVERFLOW_OK" is returned.<br>
*"D_DD_PWM_OVERFLOW_ERROR" is returned when it cannot be divded even if it calculates again.
*
*@param [in]		usec	The designated time of PWM
*@param [out]   *clk		Number of clocks calculated at specified time
*@param [out]   *cycle	Cycle calculated at specified time number
*@retval D_DDIM_OK				OK
*@retval D_DD_PWM_OVERFLOW_OK	Overflow OK
*@retval D_DD_PWM_OVERFLOW_ERROR	Overflow NG
*/
kint32                                   dd_pwm_utility_calculate(DdPwmUtility* self, kulong usec,
		                                             kuchar* const clk, kushort* const cycle);

/*
*Cycle parameters are calculated according to the designated time (u sec)<br>
*and selected index of clock divider.<br>
*If it doesn't calculate, Input Parameter Error is returned.<br>
*In that case, "D_DD_PWM_OVERFLOW_OK" is returned.<br>
*"D_DD_PWM_OVERFLOW_ERROR" is returned when it cannot be divded even if it calculates again.

*@param [in]		usec	The designated time of PWM
*@param [in]     clk		index of clock divider.
*@param [out]   *cycle	Cycle calculated at specified time number
*@retval D_DDIM_OK				OK
*@retval D_DD_PWM_OVERFLOW_ERROR	Overflow NG
*/
kint32                                   dd_pwm_utility_calculate_cycle(DdPwmUtility* self, kulong usec,
		                                             kuchar const clk, kushort* const cycle);

/*
*PWM output control channel wave form is set (change).<br>
*The setting is reflected at the counter borrow opportunity.
*@param [in] ch		Channel number (0 to 15)
*@param [in] cycle	Cycle for PWM
*@param [in] duty	Duty ratio for PWM(0-100%)
*@param [in] clkSel	Selection of PWM clock(PHCLK, PHCLK/4, PHCLK/16, PHCLK/64)
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@remarks set to become cycle>=duty the relation between set cycle and duty.
*/
kint32                                   dd_pwm_utility_write_cycle_duty(DdPwmUtility* self, kuint32 ch,
		                                             kushort cycle, kuchar duty, kuchar clkSel);

/*
*PWM output control channel wave form is set for reverse(change).<br>
*The setting is reflected at the counter borrow opportunity.
*@param [in] ch		Channel number (0 to 15)
*@param [in] cycle	Cycle of reverse for PWM
*@param [in] duty	Duty ratio of reverse for PWM(0-100%)
*@param [in] clkSel	Selection of PWM clock(PHCLK, PHCLK/4, PHCLK/16, PHCLK/64)
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@remarks Please set to become cycle>=duty the relation between set cycle and duty.
*/
kint32                                   dd_pwm_utility_write_cycle_duty_reverse(DdPwmUtility* self,
		                                             kuint32 ch, kushort cycle, kuchar duty, kuchar clkSel);

/*
*PWM output control channel wave form is set for queue(change).<br>
*The setting is reflected at the counter borrow opportunity.
*@param [in] ch		Channel number (0 to 15)
*@param [in] cycle	Cycle of queue for PWM
*@param [in] duty	Duty ratio of queue for PWM(0-100%)
*@param [in] clkSel	Selection of PWM clock(PHCLK, PHCLK/4, PHCLK/16, PHCLK/64)
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@remarks Please set to become cycle>=duty the relation between set cycle and duty.
*/
kint32                                   dd_pwm_utility_write_cycle_duty_queue(DdPwmUtility* self,
		                                             kuint32 ch, kushort cycle, kuchar duty, kuchar clkSel);

/*
*Set an input trigger for PWM specified channel.<br>
*The setting is reflected at the counter borrow opportunity.
*@param [in] ch		Channel number (0 to 15)
*@param [in] gcnTsel	Input trigger
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@remarks Please set to become cycle>=duty the relation between set cycle and duty.
*/
kint32                                   dd_pwm_utility_write_input_trg(DdPwmUtility* self, kuint32 ch, kuchar gcnTsel);

/*
*Switch a writing trigger for PWM specified channel.
*@param [in] ch		Channel number (0 to 15)
*@param [in] tsel	Writing trigger select
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                   dd_pwm_utility_write_cycle_duty_switch(DdPwmUtility* self,
		                                             kuint32 ch, kuchar tsel);

/*
*Set a setting for PWM specified channel.
*@param [in] ch		Channel number (0 to 15)
*@param [in] pcn		Control status
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                   dd_pwm_utility_write_pcn(DdPwmUtility* self, kuint32 ch, kushort pcn);

/*
*The PWM Timer Onshot is set.
*@param [in]	ch						Channel number (0 to 15)
*@param [in]	dutyTime				Duty time(usec)
*@param [in]	*pwmCtrlCmn			PWM Start table pointer. See @ref DdPwmCtrlCmn
*@param [in]	*pwmCtrlTimerAbcd	PWM Start table pointer. See @ref DdpwmCtrlTimerAbcd
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                   dd_pwm_utility_write_onshot(DdPwmUtility* self, kuint32 ch, kushort dutyTime,
								                     DdPwmCtrlCmn* const pwmCtrlCmn,
								                     DdpwmCtrlTimerAbcd* const pwmCtrlTimerAbcd);

/*@}*/
/*@}*/

/*@weakgroup dd_pwm
@{
	<hr>
	Utility Functions <br>
	- @ref PWM_start_reverse_queue <br>
	- @ref PWM_oneshot <br>
	- @ref PWM_step <br>

	@section PWM_start_reverse_queue	Sequence of PWM set and change for cycle and duty
	@image html dd_pwm_start_reverse_queue.png

	@section PWM_oneshot	Sequence of PWM oneshot
	@image html dd_pwm_oneshot.png

	@section PWM_step	Sequence of PWM stepping motor
	@image html dd_pwm_step.png
*/
/*@}*/
#endif	/* CO_DDIM_UTILITY_USE */

#endif /* __DD_PWM_UTILITY_H__ */
