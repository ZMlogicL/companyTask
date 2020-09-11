/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :PWM driver(colabo  section)
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#ifndef __DD_PWM_COLABO_H__
#define __DD_PWM_COLABO_H__

#include <klib.h>
#include "ddpwm.h"

#define DD_TYPE_PWM_COLABO                       (dd_pwm_colabo_get_type())
#define DD_PWM_COLABO(obj)                         K_TYPE_CHECK_INSTANCE_CAST(obj, DdPwmColabo)
#define DD_IS_PWM_COLABO(obj)                    K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_PWM_COLABO)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifdef CO_DDIM_UTILITY_USE
//---------------------- colabo  section -------------------------------
// Force value for force_val of TDdPwmStep
/*< Force disable for force_val of TDdPwmStep */
#define	DdPwmColabo_STEP_FORCE_DISABLE	 	(-1)
/*< Force to 0 for force_val of TDdPwmStep */
#define	DdPwmColabo_STEP_FORCE_0			        (0)
/*< Force to 1 for force_val of TDdPwmStep */
#define	DdPwmColabo_STEP_FORCE_1			        (1)
#endif	/* CO_DDIM_UTILITY_USE */

#ifdef CO_DDIM_UTILITY_USE
typedef struct _TDdPwmStep                   TDdPwmStep;
#endif	/* CO_DDIM_UTILITY_USE */

typedef struct _DdPwmColabo                 DdPwmColabo;
typedef struct _DdPwmColaboPrivate    DdPwmColaboPrivate;

#ifdef CO_DDIM_UTILITY_USE
/* PWM stepping motor control info */
struct _TDdPwmStep{
	/*< clock select						PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_CKS_DIV_0
	*<li>@ref D_DD_PWM_PCNHL_CKS_DIV_4
	*<li>@ref D_DD_PWM_PCNHL_CKS_DIV_16
	*<li>@ref D_DD_PWM_PCNHL_CKS_DIV_64</ul>*/
	kuchar clkSel;
	/*< output polarity					PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_OSEL_NORMAL
	*<li>@ref D_DD_PWM_PCNHL_OSEL_REVERSE</ul>	*/
	kuchar polarity;
	/*< restart enable					PCNH
	*<ul><li>@ref D_DD_PWM_PCNHL_RTRG_OFF
	*<li>@ref D_DD_PWM_PCNHL_RTRG_ON</ul>	*/
	kuchar restartTrig;
	/*< channel assignment		GCN2
	*<ul><li>@ref D_DD_PWM_GCN_CHAS_ABCD
	*<li>@ref D_DD_PWM_GCN_CHAS_CBAD</ul>	*/
	kuchar chAssign;
	/*< hold setting at stop	(0:disable	1:enable)	PCHSETH */
	kuchar hold[DdPwmBranch_CH_NUM_IN_BLOCK];
	/*< force value at stop	(-1:force disable, 0:Force to 0, 1:Force to 1)	PCHSETH */
	kint8 force[DdPwmBranch_CH_NUM_IN_BLOCK];
	/*< No. of stepping motor data(1 to 255)*/
	kuchar stepDataNum;
	/*< No. of under run stepping motor data(0 to 4)	*/
	kuchar undrRunDataNum;
	/*< stepping motor data(cycle,duty,pulse,link)	*/
	PwmTimerEstepsData* stepData;
	/*< under run data(cycle,duty,pulse,link)*/
	PwmTimerEstepsData* underRunData;
	/*< callback function pointer*/
	VpCallbackPwm	pCallback;
};
#endif	/* CO_DDIM_UTILITY_USE */

struct _DdPwmColabo
{
	KObject parent;
};

KConstType                      dd_pwm_colabo_get_type(void);
DdPwmColabo*              dd_pwm_colabo_get(void);

#ifdef CO_DDIM_UTILITY_USE
/*
*The PWM Timer E and DMA is set for stepping motor.
*@param [in]	pwmCh			PWM Channel number (0 or 4 or 8 or 12).<br>
*@param [in]	dmaCh			HDMAC0 Channel number (0 to 7).<br>
*@param [in]	*pwmStep	PWM Start table pointer. See @ref TDdPwmStep.<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                dd_pwm_colabo_write_step(DdPwmColabo* self, kuint32 pwmCh,
		                                          kuint32 dmaCh, TDdPwmStep const* const pwmStep);

/*
*The PWM Timer E and DMA is set for stepping motor.
*@param [in]	pwmCh			PWM Channel number (0 or 4 or 8 or 12).<br>
*@param [in]	dmaCh			HDMAC0 Channel number (0 to 7).<br>
*@param [in]	*pwmStep	PWM Start table pointer. See @ref TDdPwmStep.<br>
*@param [in]	dataNum		the number of entry data<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_PWM_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                                dd_pwm_colabo_write_step_only_buf_data_window(DdPwmColabo* self,
		                                          kuint32 pwmCh, kuint32 dmaCh,
		                                          PwmTimerEstepsData const* const pwmStep,
		                                          kuchar dataNum);

#endif	/* CO_DDIM_UTILITY_USE */

#endif /* __DD_PWM_COLABO_H__ */
