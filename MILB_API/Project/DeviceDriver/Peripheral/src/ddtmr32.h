/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :peripheral 32 bit reload timer driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

/*
@addtogroup dd_tmr32
@{
	- @ref Timer32_start_base

	<hr>
	@section Timer32_start_base		Basic sequence of 32 bit Timer
	@image html dd_tmr32_base.png

	@code
	kint32 Timer32_Sample_Code(VOID)
	{
		kuint32		ch = 1;
		kint32		timeOut;
		TDdTmr32Ctrl 	tmr32Ctrl;

		tmr32Ctrl.csr.bit.rels       = 0;
		tmr32Ctrl.csr.bit.csl        = 2;		// 32div
		tmr32Ctrl.csr.bit.mod        = 0;
		tmr32Ctrl.csr.bit.outl       = 0;
		tmr32Ctrl.csr.bit.reld       = 1;		// Reload
		tmr32Ctrl.csr.bit.inte       = 1;		// Interrupt enable
		tmr32Ctrl.csr.bit.ufFixed1  = 0;
		tmr32Ctrl.csr.bit.cnte       = 1;		// Timer counter enable
		tmr32Ctrl.csr.bit.trgFixed0 = 0;

		tmr32Ctrl.rlr1         = (1687500 - 1);		// Timer Count (1sec)
		tmr32Ctrl.rlr2         = 0;
		tmr32Ctrl.softCounter = 1;					// Soft counter
		tmr32Ctrl.pCallback    = Sample_Code_CB;		// User's Callback Function

		ret = Dd_TMR32_Open(ch, timeOut);
		if (ret != D_DDIM_OK) {
			// ERROR
			return ;
		}
		ret = Dd_TMR32_Ctrl(ch, &tmr32Ctrl);
		if (ret != D_DDIM_OK) {
			// ERROR
			Dd_TMR32_Close(ch, timeOut);
			return ;
		}
		ret = Dd_TMR32_Start(ch);
		if (ret != D_DDIM_OK) {
			// ERROR
			Dd_TMR32_Close(ch, timeOut);
			return ;
		}
	}
	@endcode

*/

#ifndef __DD_TMR32_H__
#define __DD_TMR32_H__

#include <klib.h>
#include "driver_common.h"

#define DD_TYPE_TMR32                       (dd_tmr32_get_type())
#define DD_TMR32(obj)                         K_TYPE_CHECK_INSTANCE_CAST(obj, DdTmr32)
#define DD_IS_TMR32(obj)                    K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_TMR32)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Return value of 32 bit reload timer processing result */
/*< Input Parameter Error */
#define DdTmr32_INPUT_PARAM_ERR		          (D_DD_TMR32 | D_DDIM_INPUT_PARAM_ERROR)
/*< Semaphore acquisition Time Out */
#define DdTmr32_SEM_TIMEOUT			              (D_DD_TMR32 | D_DDIM_SEM_TIMEOUT)
/*< Semaphore acquisition NG */
#define DdTmr32_SEM_NG				                      (D_DD_TMR32 | D_DDIM_SEM_NG)

/* Channel Number max */
/*< Channel max number */
#define DdTmr32_CH_NUM_MAX			               (14)

/* External Trriger Max Channel Number */
/*< Channel max number that can use external trigger */
#define DdTmr32_EXT_TRG_CH_NUM_MAX	       (6)

typedef struct _TDdTmr32Ctrl         TDdTmr32Ctrl;

typedef struct _DdTmr32                 DdTmr32;
typedef struct _DdTmr32Private     DdTmr32Private;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* CSR of reload timer */
typedef union
{
	/*< for kulong access */
	kulong		word;
	 /*< for bit access*/
	struct {
		/*< TRG is "0" fiexed (1)*/
		kulong	 trgFixed0	:1;
		/*< Timer counter Enable (0 or 1)	*/
		kulong	 cnte		:1;
		/*< UF is "1" fiexed (1)*/
		kulong	 ufFixed1	:1;
		/*< Interrupt Enable (0 or 1)*/
		kulong inte		:1;
		/*< Reload Enable (0 or 1)*/
		kulong	 reld		:1;
		/*< Out Level (0 or 1)*/
		kulong	 outl		:1;
		/*< Reserved	*/
		kulong				:1;
		/*< Mode select (0 to 7)*/
		kulong	 mod			:3;
		/*< Count clock select (0 to 3)*/
		kulong	 csl			:2;
		/*< Reload register select (0 or 1)	*/
		kulong rels		:1;
		/*< Reserved*/
		kulong				:3;
		/*< Reserved	*/
		kulong				:16;
    } bit;
}UDdTmr32Csr;

/* Control information */
struct _TDdTmr32Ctrl
{
	/*< Control status    TMCSR*/
	UDdTmr32Csr	csr;
	/*< Reload register1  TMRLR1 (0x00000000 tor 0xFFFFFFFF)	*/
	kulong				rlr1;
	/*< Reload register2  TMRLR2 (0x00000000 tor 0xFFFFFFFF)	*/
	kulong				rlr2;
	/*< soft counter (0x00000001 tor 0xFFFFFFFF)*/
	kulong				           softCounter;
	/*< Call Back function pointer	*/
	VP_CALLBACK			pCallback;
};

struct _DdTmr32
{
	KObject parent;
};

KConstType           dd_tmr32_get_type(void);
DdTmr32*             dd_tmr32_get(void);

#ifdef __cplusplus
extern "C" {
#endif

/*
*The 32bit Reload Timer channel is exclusively controlled.<br>
*If a pertinent channel of 32bit Reload Timer is unused, exclusive control OK is sent back as (Lock) while using it.<br>
*Exclusive control NG is sent back when using it (Lock inside of present).
*When timeout occurs, return "D_DD_TMR32_SEM_TIMEOUT".
*
*@param [in] 	ch	Channel number (0 to 13)
*@param [in]		timeOut		Time of timeout<br>
*							<ul><li>Positive Value(Time of timeout)
*								<li>@ref D_DDIM_USER_SEM_WAIT_POL
*								<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*@retval D_DD_TMR32_SEM_NG				Lock Error (System Using designated channel number)
*@retval D_DD_TMR32_SEM_TIMEOUT		Semaphore acquisition Time Out
*@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
*		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32	                    dd_tmr32_open(DdTmr32* self, kuint32 ch, kint32 timeOut);

/*
*32bit Reload Timer(Channel) is released.
*
*@param [in] 	ch	Channel number (0 to 13)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32	                    dd_tmr32_close(DdTmr32* self, kuint32 ch);

/*
*The operation condition of 32bit Reload Timer (Channel) is set.<br>
*Please set the callback function when the interruption is generated to "pCallback".<br>
*"softCounter" is the one that how many times "load_value" is repeated is specified.<br>
*When the number of "softCounter" is repeated, the function registered in "pCallback" is called.
*
*@param [in] 	ch			Channel number (0 to 13)
*@param [in]    *tmr32Ctrl	Timer32 Control Information
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_ctrl(DdTmr32* self, kuint32 ch, TDdTmr32Ctrl const* const tmr32Ctrl);

/*
*The value of TDdTmr32Ctrl that corresponds at the time specified by "usec" is calculated.<br>
*The unit of "usec" is a micro second.<br>
*If it doesn't calculate, Input Parameter Error is returned.<br>
*
*@param [in] 	usec			The designated time(micro second)
*@param [out]   *tmr32Ctrl		Timer32 Control Information
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_calculate(DdTmr32* self, kulong usec, TDdTmr32Ctrl* const tmr32Ctrl);

/*
*The value of TDdTmr32Ctrl that corresponds.<br>
*
*@param [in] 	pwmCh			pwmCh
*@param [in] 	mode			0:for 60fps, 1:for 240fps
*@param [out]   *tmr32Ctrl		Timer32 Control Information
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_calculate_pwm_sync(DdTmr32* self, kuint32 pwmCh,
		                             kuchar mode, TDdTmr32Ctrl* const tmr32Ctrl);

/*
*32bit Reload Timer(Channel) is started.
*
*@param [in] 	ch	Channel number (0 to 13)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_start(DdTmr32* self, kuint32 ch);

/*
*32bit Reload Timer(Channel) 32bit Reload Timer(Channel) wait for external trigger.
*
*@param [in] 	ch	Channel number. value range (0 to 5)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_external_start(DdTmr32* self, kuint32 ch);

/*
*32bit Reload Timer(Channel) is stopped.
*
*@param [in] 	ch	Channel number (0 to 13)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_stop(DdTmr32* self, kuint32 ch);

/*
*32bit Reload Timer(Channel) is paused.
*
*@param [in] 	ch	Channel number (0 to 13)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_pause(DdTmr32* self, kuint32 ch);

/*
*Dual Input Timer counter value is gotten.
*
*@param [in] 	ch		Channel number (0 to 13)
*@param [out]   *hCount	Pointer of TimerValue
*@param [out]   *sCount	Pointer of Soft Counter
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_get_counter(DdTmr32* self, kuint32 ch,
		                             kulong* const hCount, kulong* const sCount);

/*
*Value of TDdTmr32Ctrl is gotten.
*
*@param [in] 	ch			Channel number (0 to 13)
*@param [out]   *tmr32Ctrl	Timer32 Control Information
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*@remarks	Because TMRLR1 and TMRLR2 are the register of Write Only, the value cannot be acquired.
*/
kint32	                    dd_tmr32_get_ctrl(DdTmr32* self, kuint32 ch, TDdTmr32Ctrl* const tmr32Ctrl);

/*
*The value of softCounter is set.
*
*@param [in] 	ch				Channel number (0 to 13)
*@param [in]		softCounter	Soft counter (0x00000001 to 0xFFFFFFFF)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_set_soft_counter_value(DdTmr32* self, kuint32 ch, kulong softCounter);

/*
*The soft count value is gotten.
*
*@param [in] 	ch		Channel number (0 to 13)
*@retval softCounter	Soft counter
*/
kulong	                    dd_tmr32_get_soft_counter_vlaue(DdTmr32* self, kuint32 ch);

/*
*The value of reload_flg is set.<br>
*If the reload_flg is "0", timer processing is not retried(=one shot).<br>
*And if the reload_flg is "1", timer processing is retried(counter is reloaded when timer processing is completed).
*
*@param [in]		ch		Channel number (0 to 13)
*@param [in]		flg		reload flag (0 to 1)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_set_reload_flg_value(DdTmr32* self, kuint32 ch, kuchar flg);

/*
*The reload flag is gotten.
*
*@param [in]		ch		Channel number (0 to 13)
*@retval gTimer32_Set_Reload_flg[ch]	The reload flag of designated ch
*/
kint32	                    dd_tmr32_get_reload_flg_value(DdTmr32* self, kuint32 ch);

#ifdef CO_DDIM_UTILITY_USE
/* @name Utility Functions
@{*/
/*
*The operation condition of Reload Timer (Channel) is set according to designate time parameter.<br>
*Please set the callback function when the interruption is generated to pCallback.<br>
*If the reload_flg is "0", timer processing is not retried(= one shot).<br>
*And if the reload_flg is "1", timer processing is retried (counter is reloaded when timer processing is completed).
*
*@param [in] 	ch				Channel number (0 to 13)
*@param [in]		usec			Designated time(micro second)
*@param [in]	  	pCallback		Call Back function pointer
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_set_timer(DdTmr32* self, kuint32 ch, kulong usec, VP_CALLBACK pCallback);

/*
*The operation condition of Reload Timer (Channel) is set according to designate time parameter.<br>
*Please set the callback function when the interruption is generated to pCallback.<br>
*If the reload_flg is "0", timer processing is not retried(= one shot).<br>
*And if the reload_flg is "1", timer processing is retried (counter is reloaded when timer processing is completed).
*
*@param [in] 	reloadCh		Channel number (0 to 13)
*@param [in] 	pwmCh			Channel number (4 or 8)
*@param [in]	  	mode			0:for 60fps, 1:for 240fps
*@param [in]	  	pCallback		Call Back function pointer
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_set_timer_pwm(DdTmr32* self, kuint32 reloadCh,
		                             kuint32 pwmCh, kuchar mode, VP_CALLBACK pCallback);

/*
*Designated Channel of 32bit Reload Timer is started for reload.
*@param [in]		ch			Channel number (0 to 13)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_start_reload(DdTmr32* self, kuint32 ch);

/*
*Designated Channel of 32bit Reload Timer is started for oneshot.
*
*@param [in]		ch			Channel number (0 to 13)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_start_one_shot(DdTmr32* self, kuint32 ch);

/*
*The outLevel(OUTL) is set.
*@param [in]		outLevel		Out level (0 to 1)
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR32_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                    dd_tmr32_set_out_level(DdTmr32* self, kuint32 outLevel);

/*@}*/
/*@}*/

/************************************************************************/
/* Utility																*/
/************************************************************************/
/* @weakgroup dd_tmr32
@{
	<hr>
	Utility Functions <br>
	- @ref Timer32_start_utility_OneShot <br>
	- @ref Timer32_start_utility_Reload  <br>

	<hr>
	@section Timer32_start_utility_OneShot	Sequence of the One-Shot of 32 bit Timer. (Utility)
	@image html dd_tmr32_utility_OneShot.png

	@section Timer32_start_utility_Reload	Sequence of the Reload of 32 bit Timer. (Utility)
	@image html dd_tmr32_utility_Reload.png

	@code
	kint32 Timer32_Utility_Reload_Sample_Code(VOID)
	{
		kuint32		ch;
		kint32		timeOut;
		kulong		time;
		VP_CALLBACK	call_back;

		// Parameter Setting
		ch        = 1;
		time      = 1000000;			// 1 sec
		call_back = Sample_Code_CB;		// User's Callback Function

		ret = Dd_TMR32_Open(ch, timeOut);
		if (ret != D_DDIM_OK) {
			// ERROR
			return ;
		}
		ret = Dd_TMR32_SetTimer(ch, time, call_back);
		if (ret != D_DDIM_OK) {
			// ERROR
			Dd_TMR32_Close(ch);
			return ;
		}
		ret = Dd_TMR32_StartReload(ch);
		if (ret != D_DDIM_OK) {
			// ERROR
			Dd_TMR32_Close(ch);
			return ;
		}
	}

	kint32 Timer32_Utility_OneShot_Sample_Code(VOID)
	{
		kuint32		ch;
		kint32		timeOut;
		kulong		time;
		VP_CALLBACK	call_back;

		// Parameter Setting
		ch        = 1;
		time      = 1000000;	// 1 sec
		call_back = 0;			// User's Callback Function None

		ret = Dd_TMR32_Open(ch, timeOut);
		if (ret != D_DDIM_OK) {
			// ERROR
			return ;
		}
		ret = Dd_TMR32_SetTimer(ch, time, call_back);
		if (ret != D_DDIM_OK) {
			// ERROR
			Dd_TMR32_Close(ch);
			return ;
		}
		ret = Dd_TMR32_StartOneshot(ch);
		if (ret != D_DDIM_OK) {
			// ERROR
			Dd_TMR32_Close(ch);
			return ;
		}
	}
	@endcode
*/
/*@}*/
#endif

/*
 * 获取、设置私有变量
 */
kulong                    dd_tmr32_get_soft_counter(DdTmr32* self, kuint32 ch);
kulong                    dd_tmr32_get_soft_counter_ini(DdTmr32* self, kuint32 ch);
kuchar                    dd_tmr32_get_reload_flg(DdTmr32* self, kuint32 ch);
VP_CALLBACK       dd_tmr32_get_callback(DdTmr32* self, kuint32 ch);

void                        dd_tmr32_set_soft_counter_reduce(DdTmr32* self, kuint32 ch);
void                        dd_tmr32_set_soft_counter(DdTmr32* self, kuint32 ch);

#ifdef __cplusplus
}
#endif

#endif /* __DD_TMR32_H__ */
