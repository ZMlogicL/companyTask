/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-08
* @author    : 肖泽友
* @brief        :peripheral 32 bit reload timer driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、The interruption flag is cleared, and the CallBack function for 32bit Reload Timer is called.
*
*@version   :1.0.0
*
*/

#ifndef __DD_TMR32_INTERRUPTION_H__
#define __DD_TMR32_INTERRUPTION_H__

#include <klib.h>
#include "ddtmr32.h"

#define DD_TYPE_TMR32_INTERRUPTION         (dd_tmr32_interruption_get_type())
#define DD_TMR32_INTERRUPTION(obj)           K_TYPE_CHECK_INSTANCE_CAST(obj, DdTmr32Interruption)
#define DD_IS_TMR32_INTERRUPTION(obj)      K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_TMR32_INTERRUPTION)

typedef struct _DdTmr32Interruption                 DdTmr32Interruption;
typedef struct _DdTmr32InterruptionPrivate    DdTmr32InterruptionPrivate;

struct _DdTmr32Interruption
{
	KObject parent;
};

KConstType                        dd_tmr32_interruption_get_type(void);
DdTmr32Interruption*     dd_tmr32_interruption_new(void);

/*
*The interruption flag is cleared, and the CallBack function for 32bit Reload Timer is called.<br>
*(Only an interruption clear flag of CallBack when it is unregistered.)<br>
*The counter value is calculated according to specified timing.
*
*@param [in] 	ch		Channel number (0 to 13)
*/
void	                                 dd_tmr32_interruption_int_handler(kuint32 ch);   //TODO  中断汇编调用

#endif /* __DD_TMR32_INTERRUPTION_H__ */
