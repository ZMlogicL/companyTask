/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :PWM driver(branch)
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#ifndef __DD_PWM_BRANCH_H__
#define __DD_PWM_BRANCH_H__

#include <klib.h>
#include "driver_common.h"
#include "peripheral.h"
#include "ddim_typedef.h"

#define DD_TYPE_PWM_BRANCH                                    (dd_pwm_branch_get_type())
#define DD_PWM_BRANCH(obj)                                      K_TYPE_CHECK_INSTANCE_CAST(obj, DdPwmBranch)
#define DD_IS_PWM_BRANCH(obj)                                 K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_PWM_BRANCH)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
// Return value of PWM timer processing result
/*< Input Parameter Error */
#define	DdPwmBranch_INPUT_PARAM_ERROR	      (D_DD_PWM | D_DDIM_INPUT_PARAM_ERROR)
/*< Semaphore acquisition Time Out */
#define	DdPwmBranch_SEM_TIMEOUT		              (D_DD_PWM | D_DDIM_SEM_TIMEOUT)
/*< Semaphore acquisition NG */
#define	DdPwmBranch_SEM_NG				                  (D_DD_PWM | D_DDIM_SEM_NG)
/*< Counter overflow and clock change NG */
#define	DdPwmBranch_OVERFLOW_ERROR		      (D_DD_PWM | D_DDIM_OVERFLOW_ERR)
/*< Counter overflow and clock change OK */
#define	DdPwmBranch_OVERFLOW_OK		              (D_DD_PWM | D_DDIM_OVERFLOW_OK)

// Callback status
/*< Callback status when Trigger input */
#define	DdPwmBranch_INT_STATUS_TRG_INPUT		            (0)
/*< Callback status when Agreement cycle */
#define	DdPwmBranch_INT_STATUS_CYCLE_MATCH		    (1)
/*< Callback status when Agreement duty */
#define	DdPwmBranch_INT_STATUS_DUTY_MATCH		        (2)
/*< Callback status when Agreement duty */
#define	DdPwmBranch_INT_STATUS_CYC_DUTY_MATCH	    (3)
/*< Callback status when Under run error (for Timer E) */
#define	DdPwmBranch_INT_STATUS_UNDER_RUN		        (4)
/*< Callback status when Force stop (for Timer E) */
#define	DdPwmBranch_INT_STATUS_FORCE_STOP		        (5)
/*< Callback status when Auto stop (for Timer E) */
#define	DdPwmBranch_INT_STATUS_AUTO_STOP		            (6)

// Num of channel
/*< The maximum values of number of channels */
#define DdPwmBranch_CH_NUM_MAX					            (16)
/*< The maximum values of number of HW blocks */
#define DdPwmBranch_BLOCK_NUM					                (4)
/*< The maximum values of number of channels in HW block */
#define DdPwmBranch_CH_NUM_IN_BLOCK			        (4)
/*< The maximum values of number of steps in timer E */
#define DdPwmBranch_TIMER_E_STEPS				                (8)
/*< The maximum values of number of steps in timer E under run*/
#define DdPwmBranch_TIMER_E_STEPS_UNDER_RUN   	(4)

// timer operation enable
/*< timer disable */
#define	DdPwmBranch_PCNHL_CNTE_OFF			    (0x0)
/*< timer enable */
#define	DdPwmBranch_PCNHL_CNTE_ON			        (0x1)

// operation mode
/*< PWM */
#define	DdPwmBranch_PCNHL_MDSE_PWM			    (0x0)
/*< One-shot */
#define	DdPwmBranch_PCNHL_MDSE_ONE			    (0x1)

// restart enable
/*< disable */
#define	DdPwmBranch_PCNHL_RTRG_OFF			    (0x0)
/*< enbale */
#define	DdPwmBranch_PCNHL_RTRG_ON			        (0x1)

// counter clock
/*< not dividing frequency	*/
#define	DdPwmBranch_PCNHL_CKS_DIV_0		        (0x0)
/*< 4 dividing frequency */
#define	DdPwmBranch_PCNHL_CKS_DIV_4		        (0x1)
/*< 16 dividing frequency */
#define	DdPwmBranch_PCNHL_CKS_DIV_16		        (0x2)
/*< 64 dividing frequency */
#define	DdPwmBranch_PCNHL_CKS_DIV_64		        (0x3)

// output mask
/*< output is "Low" */
#define	DdPwmBranch_PCNHL_PGMS_L			        (0x0)
/*< output is "High" */
#define	DdPwmBranch_PCNHL_PGMS_H			        (0x1)

// trigger edge
/*< invalid */
#define	DdPwmBranch_PCNHL_EGS_NOT			        (0x0)
/*< rise edge */
#define	DdPwmBranch_PCNHL_EGS_RISE			        (0x1)
/*< fall edge */
#define	DdPwmBranch_PCNHL_EGS_FALL			        (0x2)
/*< both edge */
#define	DdPwmBranch_PCNHL_EGS_BOTH			    (0x3)

// interrupt enable
/*< interrupt disable */
#define	DdPwmBranch_PCNHL_IREN_OFF			    (0x0)
/*< interrupt enbale */
#define	DdPwmBranch_PCNHL_IREN_ON			    (0x1)

// interrupt factor
/*< trigger input */
#define	DdPwmBranch_PCNHL_IRS_TRG			        (0x0)
/*< Agreement cycle */
#define	DdPwmBranch_PCNHL_IRS_CYCLE		        (0x1)
/*< Agreement duty */
#define	DdPwmBranch_PCNHL_IRS_DUTY		         	(0x2)
/*< Agreement cycle or duty */
#define	DdPwmBranch_PCNHL_IRS_CYC_DTY		    (0x3)

// output polarity
/*< output disable */
#define	DdPwmBranch_PCNHL_OSEL_NORMAL		(0x0)
/*< output enbale */
#define	DdPwmBranch_PCNHL_OSEL_REVERSE		    (0x1)

// trigger input factor
/*< EN0 bit */
#define	DdPwmBranch_GCN_TSEL_EM0			    (0x00)
/*< EN1 bit */
#define	DdPwmBranch_GCN_TSEL_EM1			    (0x01)
/*< EN2 bit */
#define	DdPwmBranch_GCN_TSEL_EM2			    (0x02)
/*< EN3 bit */
#define	DdPwmBranch_GCN_TSEL_EM3			    (0x03)
/*< Timer ch0 */
#define	DdPwmBranch_GCN_TSEL_TIM0			(0x04)
/*< Timer ch1 */
#define	DdPwmBranch_GCN_TSEL_TIM1			(0x05)
/*< External trigger0 */
#define	DdPwmBranch_GCN_TSEL_EXT0			(0x08)
/*< External trigger1 */
#define	DdPwmBranch_GCN_TSEL_EXT1			(0x09)
/*< External trigger2 */
#define	DdPwmBranch_GCN_TSEL_EXT2			(0x0A)
/*< External trigger3 */
#define	DdPwmBranch_GCN_TSEL_EXT3			(0x0B)

// timer E enable
/*< timer E disable */
#define	DdPwmBranch_GCN_TMEEN_OFF			(0x0)
/*< timer E enbale */
#define	DdPwmBranch_GCN_TMEEN_ON			(0x1)

// channel assignment factor
/*< channel order : A B C D */
#define	DdPwmBranch_GCN_CHAS_ABCD			(0x0)
/*< channel order : C B A D */
#define	DdPwmBranch_GCN_CHAS_CBAD			(0x1)

// trigger input factor
/*< CPU access	*/
#define	DdPwmBranch_TSEL_CPU				    (0x00)
/*< interrupt of ch0 */
#define	DdPwmBranch_TSEL_INT_CH0			(0x01)
/*< interrupt of ch1 */
#define	DdPwmBranch_TSEL_INT_CH1			(0x02)
/*< interrupt of ch2 */
#define	DdPwmBranch_TSEL_INT_CH2			(0x03)

// DMA interrupt factor
/*< empty 2 entries */
#define	DdPwmBranch_PCHSET_RQTIM_2			(0x00)
/*< empty 4 entries */
#define	DdPwmBranch_PCHSET_RQTIM_4			(0x01)
/*< empty 6 entries */
#define	DdPwmBranch_PCHSET_RQTIM_6			(0x02)

// under run error control enable
/*< disable */
#define	DdPwmBranch_PCHSET_UDEN_OFF		(0x0)
/*< enable */
#define	DdPwmBranch_PCHSET_UDEN_ON		(0x1)

// under run error interrupt enable
/*< disable */
#define	DdPwmBranch_PINTCT_UIE_OFF			(0x0)
/*< enable */
#define	DdPwmBranch_PINTCT_UIE_ON			(0x1)

// force stop interrupt enable
/*< disable */
#define	DdPwmBranch_PINTCT_FIE_OFF			(0x0)
/*< enable */
#define	DdPwmBranch_PINTCT_FIE_ON			    (0x1)

// auto stop interrupt enable
/*< disable */
#define	DdPwmBranch_PINTCT_AIE_OFF		    (0x0)
/*< enable */
#define	DdPwmBranch_PINTCT_AIE_ON			(0x1)

// DMA interrupt enable
/*< disable */
#define	DdPwmBranch_PINTCT_DRQE_OFF		    (0x0)
/*< enable */
#define	DdPwmBranch_PINTCT_DRQE_ON			(0x1)

// PREV enable
/*< disable */
#define	DdPwmBranch_PREV_OFF				    (0x0)
/*< enable */
#define	DdPwmBranch_PREV_ON				    (0x1)

/*< The maximum values of number of steps in timer E */
#define DdPwmBranch_TIMERE_DATA_MAX	(30)

typedef struct _DdPwmCtrlCmn                      DdPwmCtrlCmn;
typedef struct _DdpwmCtrlTimerAbcd           DdpwmCtrlTimerAbcd;
typedef struct _DdpwmCtrlTimerAbcd2ch     DdpwmCtrlTimerAbcd2ch;
typedef struct _PwmTimerEstepsData            PwmTimerEstepsData;
typedef struct _PwmCtrlTimerE                       PwmCtrlTimerE;
typedef struct _DdPwmCtrlMemo                   DdPwmCtrlMemo;

typedef struct _DdPwmBranch                        DdPwmBranch;
typedef struct _DdPwmBranchPrivate           DdPwmBranchPrivate;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/*< Type is defined to Callback function pointer for PWM */
typedef void (*VpCallbackPwm)(kuint32 ch, kuint32 status);

/* PWM control info */
struct _DdPwmCtrlCmn
{
	/*< PWM or One-Shot operation	PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_MDSE_PWM
	*<li>@ref D_DD_PWM_PCNHL_MDSE_ONE</ul>*/
	kuchar drvMode;
	/*< restart enable				PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_RTRG_OFF
	*<li>@ref D_DD_PWM_PCNHL_RTRG_ON</ul>*/
	kuchar restartTrig;
	/*< clock select				PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_CKS_DIV_0
	*li>@ref D_DD_PWM_PCNHL_CKS_DIV_4
	*<li>@ref D_DD_PWM_PCNHL_CKS_DIV_16
	*<li>@ref D_DD_PWM_PCNHL_CKS_DIV_64</ul>*/
	kuchar clkSel;
	/*< output level mask			PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_PGMS_L
	*<li>@ref D_DD_PWM_PCNHL_PGMS_H</ul>*/
	kuchar outMask;
	/*< edge enable select			PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_EGS_NOT
	*<li>@ref D_DD_PWM_PCNHL_EGS_RISE
	*<li>@ref D_DD_PWM_PCNHL_EGS_FALL
	*<li>@ref D_DD_PWM_PCNHL_EGS_BOTH</ul>*/
	kuchar edge;
	/*< interrupt enable			PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_IREN_OFF
	*<li>@ref D_DD_PWM_PCNHL_IREN_ON</ul>*/
	kuchar intEnable;
	/*< interrupt factor			PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_IRS_TRG
	*<li>@ref D_DD_PWM_PCNHL_IRS_CYCLE
	*<li>@ref D_DD_PWM_PCNHL_IRS_DUTY
	*<li>@ref D_DD_PWM_PCNHL_IRS_CYC_DTY</ul>*/
	kuchar trigger;
	/*< output polarity			PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_OSEL_NORMAL
	*<li>@ref D_DD_PWM_PCNHL_OSEL_REVERSE</ul>	*/
	kuchar polarity;
	/*< trigger input factor		GCN1
	*<ul><li>@ref D_DD_PWM_GCN_TSEL_EM0
	*<li>@ref D_DD_PWM_GCN_TSEL_EM1
	*<li>@ref D_DD_PWM_GCN_TSEL_EM2
	*<li>@ref D_DD_PWM_GCN_TSEL_EM3
	*<li>@ref D_DD_PWM_GCN_TSEL_TIM0
	*<li>@ref D_DD_PWM_GCN_TSEL_TIM1
	*<li>@ref D_DD_PWM_GCN_TSEL_EXT0
	*<li>@ref D_DD_PWM_GCN_TSEL_EXT1
	*<li>@ref D_DD_PWM_GCN_TSEL_EXT2
	*<li>@ref D_DD_PWM_GCN_TSEL_EXT3</ul>*/
	kuchar inTrigger;
	/*< timer E enable				GCN2
	*<ul><li>@ref D_DD_PWM_GCN_TMEEN_OFF
	*<li>@ref D_DD_PWM_GCN_TMEEN_ON</ul>*/
	kuchar timEEnable;
	/*< channel assignment			GCN2
	*<ul><li>@ref D_DD_PWM_GCN_CHAS_ABCD
	*<li>@ref D_DD_PWM_GCN_CHAS_CBAD</ul>*/
	kuchar chAssign;
	/*< callback function pointer*/
	VpCallbackPwm	pCallback;
};

/* PWM timer A,B,C,D control info */
struct _DdpwmCtrlTimerAbcd
{
	/*< wave cycle(usec)	*/
	kushort cycTime;
	/*< number of cycle*/
	kushort cycNum;
	/*< number of duty*/
	kushort dutyNum;
};

/* PWM timer A,B,C,D control info */
struct _DdpwmCtrlTimerAbcd2ch
{
	/*< wave cycle(usec)*/
	kushort cycTime[2];
	/*< number of cycle*/
	kushort cycNum[2];
	/*< number of duty*/
	kushort dutyNum[2];
};

/* PWM timer E pulse and link data */
typedef union {
	/*< for kushort access*/
	kushort  hword;
	struct {
		/*< number of pulse*/
		kushort	pulseNum	:10;
		/*< Reserved*/
		kushort				:5;
		/*< link enable*/
		kushort	link		:1;
		/*< for bit access*/
	} bit;
}CtrlTimerEpulseLink;

/* PWM timer E steps data */
struct _PwmTimerEstepsData
{
	/*< number of cycle*/
	kushort cycNum;
	/*< number of duty*/
	kushort dutyNum;
	/*< number of pulse and link*/
	CtrlTimerEpulseLink pulseLink;
};

/* PWM timer E control info */
struct _PwmCtrlTimerE
{
	/*< hold setting at stop bit	(0:disable	1:enable)	PCHSETH */
	kuchar hold[DdPwmBranch_CH_NUM_IN_BLOCK];
	/*< force value at stop bit	(0 or 1)				PCHSETH */
	kuchar forceVal[DdPwmBranch_CH_NUM_IN_BLOCK];
	/*< force setting at stop bit	(0:disable	1:enable)	PCHSETH */
	kuchar force[DdPwmBranch_CH_NUM_IN_BLOCK];
	/*< Inerrupt request timing for DMA	PCHSETL
	*<ul><li>@ref D_DD_PWM_PCHSET_RQTIM_2
	*<li>@ref D_DD_PWM_PCHSET_RQTIM_4
	*<li>@ref D_DD_PWM_PCHSET_RQTIM_6</ul>*/
	kuchar emptyDmaReq;
	/*< speed down setting under run error	PCHSETL
	*<ul><li>@ref D_DD_PWM_PCHSET_UDEN_OFF
	*<li>@ref D_DD_PWM_PCHSET_UDEN_ON</ul>*/
	kuchar undrRunEnable;
	/*< interrupt enable under run error	PINTCTH
	*<ul><li>@ref D_DD_PWM_PINTCT_UIE_OFF
	*<li>@ref D_DD_PWM_PINTCT_UIE_ON</ul>*/
	kuchar undrRunIntErrEnable;
	/*< interrupt enable for force stop	PINTCTH
	*<ul><li>@ref D_DD_PWM_PINTCT_FIE_OFF
	*<li>@ref D_DD_PWM_PINTCT_FIE_ON</ul>	*/
	kuchar forceStopIntEnable;
	/*< interrupt enable for auto stop		PINTCTH
	*<ul><li>@ref D_DD_PWM_PINTCT_AIE_OFF
	*<li>@ref D_DD_PWM_PINTCT_AIE_ON</ul>*/
	kuchar autoStopIntEnable;
	/*< interrupt enable for dma			PINTCTL
	*<ul><li>@ref D_DD_PWM_PINTCT_DRQE_OFF
	*<li>@ref D_DD_PWM_PINTCT_DRQE_ON</ul>*/
	kuchar dmaIntEnable;
	/*< steps data(cycle,duty,pulse,link)*/
	PwmTimerEstepsData stepsData[DdPwmBranch_TIMER_E_STEPS];
	/*< under run data(cycle,duty,pulse,link)*/
	PwmTimerEstepsData underRunData[DdPwmBranch_TIMER_E_STEPS_UNDER_RUN];
};

// PWM control info
struct _DdPwmCtrlMemo
{
	/*< clock select PCNH */
	kuchar clkSel;
	/*< interrupt enable PCNH */
	kuchar intEnable;
	/*< DMA enable	*/
	kuchar dmaEnable;
	/*< DMA enable	*/
	kuchar dmaCh;
	/*< number of cycle*/
	kushort cycNum;
	/*< number of duty*/
	kushort dutyNum;
	/*< callback function pointer*/
	VP_CALLBACK	pCallback;             //TODO
};

struct _DdPwmBranch
{
	KObject parent;
};

KConstType                                    dd_pwm_branch_get_type(void);
DdPwmBranch*                            dd_pwm_branch_new(void);

/*
*The PWM of a control channel is started.
*
*@param [in]		ch			Channel number (0 to 15)
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@remarks The following status is notified by the callback.<br>
*	@code
*	DdPwmBranch_D_DD_PWM_INT_STATUS_TRG_INPUT		: PWM Status is Trigger input
*	DdPwmBranch_D_DD_PWM_INT_STATUS_CYCLE_MATCH		: PWM Status is Agreement cycle
*	D_DD_PWM_INT_STATUS_DUTY_MATCH		: PWM Status is Agreement duty
*	D_DD_PWM_INT_STATUS_CYC_DUTY_MATCH	: PWM Status is Agreement duty
*	D_DD_PWM_INT_STATUS_UNDER_RUN		: PWM Status is Under run error for stepping motor
*	D_DD_PWM_INT_STATUS_FORCE_STOP		: PWM Status is Force stop for stepping motor
*	D_DD_PWM_INT_STATUS_AUTO_STOP		: PWM Status is Auto stop for stepping motor
*	@endcode
*/
kint32                                              dd_pwm_branch_start(DdPwmBranch* self, kuint32 ch);

/*
*The PWM of 2 control channel is started.
*
*@param [in]		ch			Channel number (0 to 15)
*@param [in]		ch			Channel number (0 to 15)
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*@remarks The following status is notified by the callback.<br>
*	@code
*	DdPwmBranch_D_DD_PWM_INT_STATUS_TRG_INPUT		: PWM Status is Trigger input
*	DdPwmBranch_D_DD_PWM_INT_STATUS_CYCLE_MATCH		: PWM Status is Agreement cycle
*	D_DD_PWM_INT_STATUS_DUTY_MATCH		: PWM Status is Agreement duty
*	D_DD_PWM_INT_STATUS_CYC_DUTY_MATCH	: PWM Status is Agreement duty
*	D_DD_PWM_INT_STATUS_UNDER_RUN		: PWM Status is Under run error for stepping motor
*	D_DD_PWM_INT_STATUS_FORCE_STOP		: PWM Status is Force stop for stepping motor
*	D_DD_PWM_INT_STATUS_AUTO_STOP		: PWM Status is Auto stop for stepping motor
*	@endcode
*/
kint32                                              dd_pwm_branch_2ch_start(DdPwmBranch* self,
		                                                        kuint32 chA, kuint32 chB);

/*
*The PWM of a control channel is stopped.
*
*@param [in]		ch			Channel number (0 to 15)
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_stop(DdPwmBranch* self, kuint32 ch);

/*
*Get value of timer register.
*
*@param [in]		ch				Channel number (0 to 15).<br>
*@param [out]	*timerVal		timer register value<br>
*	If timerVal = 0, it does not get value.
*@param [out]	*timerEVal	timer E register value<br>
*	channel 0 to 3	means hardware block number is 0,<br>
*	channel 4 to 7	means hardware block number is 1,<br>
*	channel 8 to 11 means hardware block number is 2,<br>
*	channel 12 to 15 means hardware block number is 3.<br>
*	If timerEVal = 0, it does not get value.
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_get_timer(DdPwmBranch* self, kuint32 ch,
		                                                        kushort* timerVal, kushort* timerEVal);

/*
*Get number of output pulse.
*
*@param [in]		ch				Channel number (0 to 15).<br>
*	channel 0 to 3	means hardware block number is 0,<br>
*	channel 4 to 7	means hardware block number is 1,<br>
*	channel 8 to 11 means hardware block number is 2,<br>
*	channel 12 to 15 means hardware block number is 3.
*@param [out]	*pulseNum		output pulse number
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_get_pulse_num(DdPwmBranch* self,
		                                                        kuint32 ch, kulong* pulseNum);

/*
*Get interrupt flag and enable for timer E.
*
*@param [in]		ch				Channel number (0 to 15).<br>
*	channel 0 to 3	means hardware block number is 0,<br>
*	channel 4 to 7	means hardware block number is 1,<br>
*	channel 8 to 11 means hardware block number is 2,<br>
*	channel 12 to 15 means hardware block number is 3.
*@param [out]	*intFlgCtrl0		flag and enable<br>
*	bit12 UIS (under run error interrupt status flag)<br>
*	bit9  FIS (force stop interrupt status flag)<br>
*	bit8  AIS (auto stop interrupt status flag)<br>
*	bit4  UIE (under run error interrupt enable control)<br>
*	bit1  FIE (force stop interrupt enable control)<br>
*	bit0  AIE (auto stop interrupt enable control)
*@param [out]	*intFlgCtrl1		flag and enable<br>
*	bit15 DRQS (DMA interrupt status flag)<br>
*	bit7  DRQE (DMA interrupt enable control)
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_get_interrupt_flag(DdPwmBranch* self,
		                                                        kuint32 ch, kushort* intFlgCtrl0, kushort* intFlgCtrl1);

/*
*Set interrupt flag and enable for timer E.
*
*@param [in]		ch				Channel number (0 to 15).<br>
*	channel 0 to 3	means hardware block number is 0,<br>
*	channel 4 to 7	means hardware block number is 1,<br>
*	channel 8 to 11 means hardware block number is 2,<br>
*	channel 12 to 15 means hardware block number is 3.
*@param [in]	intFlgCtrl0		flag and enable<br>
*	bit12 UIS (under run error interrupt status flag)<br>
*	bit9  FIS (force stop interrupt status flag)<br>
*	bit8  AIS (auto stop interrupt status flag)<br>
*	bit4  UIE (under run error interrupt enable control)<br>
*	bit1  FIE (force stop interrupt enable control)<br>
*	bit0  AIE (auto stop interrupt enable control)
*@param [in]	intFlgCtrl1		flag and enable<br>
*	bit15 DRQS (DMA interrupt status flag)<br>
*	bit7  DRQE (DMA interrupt enable control)
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_set_interrupt_flag(DdPwmBranch* self, kuint32 ch,
		                                                        kushort intFlgCtrl0, kushort intFlgCtrl1);

/*
*Get channel assignment.
*
*@param [in]		ch				Channel number (0 to 15).<br>
*	channel 0 to 3	means hardware block number is 0,<br>
*	channel 4 to 7	means hardware block number is 1,<br>
*	channel 8 to 11 means hardware block number is 2,<br>
*	channel 12 to 15 means hardware block number is 3.
*@param [out]	*chAssign		channel assignment.<br>
*	@code
*	D_DD_PWM_GCN_CHAS_ABCD	: Channel order : A B C D
*	D_DD_PWM_GCN_CHAS_CBAD	: Channel order : C B A D
*	@endcode
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_get_channel_assign(DdPwmBranch* self,
		                                                        kuint32 ch, kuchar* chAssign);

/*
*Set channel assignment.
*
*@param [in]		ch				Channel number (0 to 15).<br>
*	channel 0 to 3	means hardware block number is 0,<br>
*	channel 4 to 7	means hardware block number is 1,<br>
*	channel 8 to 11 means hardware block number is 2,<br>
*	channel 12 to 15 means hardware block number is 3.
*@param [out]	*chAssign		channel assignment.<br>
*	@code
*	D_DD_PWM_GCN_CHAS_ABCD	: Channel order : A B C D
*	D_DD_PWM_GCN_CHAS_CBAD	: Channel order : C B A D
*	@endcode
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_set_channel_assign(DdPwmBranch* self,
		                                                        kuint32 ch, kuchar chAssign);

/*
*Get Interrupt Status of PWM. (Not PWM_STP)
*
*@param [in]		ch				Channel number (0 to 15)
*@retval TRUE	Interrupt request occur
*@retval FALSE	No interrupt request
*/
kboolean                                        dd_pwm_branch_get_int_stat(DdPwmBranch* self, kuint32 ch);

/*
*It is Interrupt Handler of PWM.<br>
*The interruption flag is cleared, and the CallBack function is called.<br>
*(Only an interruption clear flag of CallBack when it is unregistered.)
*@param [in]		ch	Channel number (0, 4, 8, 12)
*/
void                                                dd_pwm_branch_int_handler(DdPwmBranch* self, kuint32 ch);

/*
*It is Interrupt Handler of PWM STP.<br>
*The interruption flag is cleared, and the CallBack function is called.<br>
*(Only an interruption clear flag of CallBack when it is unregistered.)
*@param [in]		ch	Channel number (0, 4, 8, 12)
*/
void                                                dd_pwm_branch_int_handler_stp(DdPwmBranch* self, kuint32 ch);

/*
*The Mask status is set. Only when the corresponding timer ABCD.
*@param [in]	ch						Channel number (0 to 15)
*@param [in]	mask					Mask Set(0 or 1)
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_set_stopped_output_mask(DdPwmBranch* self,
		                                                        kuint32 ch, kuchar mask);

/*
*Get setting value of the mask. Only when the corresponding timer ABCD.
*@param [in]		ch					Channel number (0 to 15)
*@param [out]	*mask				Mask Status
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
 */
kint32                                              dd_pwm_branch_get_stopped_output_mask(DdPwmBranch* self,
		                                                        kuint32 ch, kuchar* mask);

/*
*Get setting value of the conter clock of TimerE
*@param [in]		ch					Channel number (0 to 15)
*@param [out]	*clock				clock_sel
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
 */
kint32                                              dd_pwm_branch_get_clock_sel_timer_e(DdPwmBranch* self,
		                                                        kuint32 ch, kuchar* clock);

/*
*Get the PWM output state. Only stopped.
*@param [in]		ch					Channel number (0 to 15)
*@param [out]	*chStatus			Output Status
*@retval D_DDIM_OK					OK
*@retval DdPwmBranch_D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                              dd_pwm_branch_get_stopped_output_status(DdPwmBranch* self,
		                                                        kuint32 ch, kuchar* chStatus);

/*
 * 新增静态方法公有化
 */
volatile union io_pwm_pcn*    dd_pwm_branch_get_func_pcn_addr(DdPwmBranch* self, kuint32 ch);     //TODO

/*
 * 获取、设置私有变量方法
 */
DdPwmCtrlMemo                         dd_pwm_branch_get_ctrl_memo(DdPwmBranch* self, kuint32 ch);

void                                                dd_pwm_branch_set_clk_sel(DdPwmBranch* self, kuint32 ch,
		                                                       kuchar clkSel);
void                                                dd_pwm_branch_set_int_enable(DdPwmBranch* self, kuint32 ch,
		                                                       kuchar intEnable);
void                                                dd_pwm_branch_set_p_callback(DdPwmBranch* self, kuint32 ch,
		                                                        VpCallbackPwm pCallback);
void                                                dd_pwm_branch_set_cyc_num(DdPwmBranch* self, kuint32 ch,
		                                                       kushort cycNum);
void                                                dd_pwm_branch_set_duty_num(DdPwmBranch* self, kuint32 ch,
		                                                       kushort dutyNum);
void                                                dd_pwm_branch_set_dma_enable(DdPwmBranch* self, kuint32 ch,
		                                                       kuchar dmaEnable);
void                                                dd_pwm_branch_set_dma_ch(DdPwmBranch* self, kuint32 ch,
		                                                       kuchar dmaCh);

#endif /* __DD_PWM_BRANCH_H__ */
