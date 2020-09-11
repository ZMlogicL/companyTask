/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-09
* @author    : 肖泽友
* @brief        :uart driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、It is a function started when the UART/CSIO transmission/reception is completed.
*
*@version   :1.0.0
*
*/

#ifndef __DD_UART_INTERRUPT_H__
#define __DD_UART_INTERRUPT_H__

#include <klib.h>
#include "dduart.h"

#define DD_TYPE_UART_INTERRUPT                 (dd_uart_interrupt_get_type())
#define DD_UART_INTERRUPT(obj)                   K_TYPE_CHECK_INSTANCE_CAST(obj, DdUartInterrupt)
#define DD_IS_UART_INTERRUPT(obj)              K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_UART_INTERRUPT)

typedef struct _DdUartInterrupt                       DdUartInterrupt;
typedef struct _DdUartInterruptPrivate          DdUartInterruptPrivate;

struct _DdUartInterrupt
{
	KObject parent;
};

KConstType               dd_uart_interrupt_get_type(void);
DdUartInterrupt*     dd_uart_interrupt_new(void);

/*
*It is a function started when the UART/CSIO transmission is completed.<br>
*@param [in]	ch	Channel number(0 to 7)
*/
void	                        dd_uart_interrupt_int_handler_tx(kuchar ch);   //TODO 中断汇编调用

/*
*It is a function started when the UART/CSIO reception is completed.<br>
*@param [in]	ch	Channel number(0 to 7)
*/
void	                        dd_uart_interrupt_int_handler_rx(kuchar ch);  //TODO 中断汇编调用

#endif /* __DD_UART_INTERRUPT_H__ */
