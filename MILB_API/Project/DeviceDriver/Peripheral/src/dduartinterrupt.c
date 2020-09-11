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

#include "dd_csio.h"
#include "dduartbranch.h"
#include "dduartcolabo.h"

#ifdef CO_DDIM_IM_TUNING_ON
    #include "../../../../../../ip/fj_ip/ImageTuning/include/im_tuning_buffer.h"
    #include "../../../../../../ip/fj_ip/ImageTuning/include/im_tuning_custom.h"
#endif

#include "dduartinterrupt.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdUartInterrupt, dd_uart_interrupt);
#define DD_UART_INTERRUPT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		DdUartInterruptPrivate, DD_TYPE_UART_INTERRUPT))

struct _DdUartInterruptPrivate
{
    kint a;
};

static void dd_uart_interrupt_constructor(DdUartInterrupt *self)
{
	DdUartInterruptPrivate *priv = DD_UART_INTERRUPT_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_uart_interrupt_destructor(DdUartInterrupt *self)
{

}

/*
 * PUBLIC
 */
/*
 * @brief  It is a function started when the UART/CSIO transmission is completed.
 * @param  kuchar  ch
 * @return void
 */
void dd_uart_interrupt_int_handler_tx(kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return;
	}
#endif

	if(dd_uart_get_usio_state(dd_uart_get(), ch) == DdUart_EXC_UART){
	#ifdef CO_DDIM_IM_TUNING_ON
		if	((ch == DdUart_IQTOOL_UART_CH) && (dd_uart_get_iqtool_status(dd_uart_get()) == DdUart_IQTOOL_START))
		{
			// IQTOOL only use Ch2
			Dd_UART_IQ_Int_Handler_Tx(DdUart_IQTOOL_UART_CH);
		}
		else
			dd_uart_colabo_int_handler_tx(dd_uart_colabo_get(), ch);
	#else
		dd_uart_colabo_int_handler_tx(dd_uart_colabo_get(), ch);
	#endif
	}
	else if(dd_uart_get_usio_state(dd_uart_get(), ch) == DdUart_EXC_CSIO){
		Dd_CSIO_Int_Handler_Tx(ch);
	}
	else{
		// D_DD_USIO_EXC_OFF
	}
}

/*
 * @brief  It is a function started when the UART/CSIO reception is completed.
 * @param  kuchar  ch
 * @return void
 */
void dd_uart_interrupt_int_handler_rx(kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return;
	}
#endif

	if(dd_uart_get_usio_state(dd_uart_get(), ch) == DdUart_EXC_UART){
	#ifdef CO_DDIM_IM_TUNING_ON
		if ((ch == DdUart_IQTOOL_UART_CH) && (dd_uart_get_iqtool_status(dd_uart_get()) == DdUart_IQTOOL_START))
		{
			// IQTOOL only use Ch2
			Dd_UART_IQ_Int_Handler_Rx(DdUart_IQTOOL_UART_CH);
		}
		else
			dd_uart_branch_int_handler_rx(dd_uart_branch_get(), ch);
	#else
		dd_uart_branch_int_handler_rx(dd_uart_branch_get(), ch);
	#endif
	}
	else if(dd_uart_get_usio_state(dd_uart_get(), ch) == DdUart_EXC_CSIO){
		Dd_CSIO_Int_Handler_Rx(ch);
	}
	else{
		// D_DD_USIO_EXC_OFF
	}
}

DdUartInterrupt* dd_uart_interrupt_new(void)
{
	DdUartInterrupt *self = k_object_new_with_private(DD_TYPE_UART_INTERRUPT,
			sizeof(DdUartInterruptPrivate));
	return self;
}
