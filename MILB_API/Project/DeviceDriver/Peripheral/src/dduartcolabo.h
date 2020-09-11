/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-10
* @author    : 肖泽友
* @brief        :uart driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、colabo section
*
*@version   :1.0.0
*
*/

#ifndef __DD_UART_COLABO_H__
#define __DD_UART_COLABO_H__

#include <klib.h>
#include "dduart.h"

#define DD_TYPE_UART_COLABO           (dd_uart_colabo_get_type())
#define DD_UART_COLABO(obj)             K_TYPE_CHECK_INSTANCE_CAST(obj, DdUartColabo)
#define DD_IS_UART_COLABO(obj)        K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_UART_COLABO)

typedef struct _DdUartColabo                 DdUartColabo;
typedef struct _DdUartColaboPrivate     DdUartColaboPrivate;

struct _DdUartColabo
{
	KObject parent;
};

KConstType            dd_uart_colabo_get_type(void);
DdUartColabo*     dd_uart_colabo_get(void);

/*
*Stop sending/receiving data(force stop)
*@param [in]	ch	Channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@remarks
*			- If want to run again after running this API, please reconfigure Dd_UART_Ctrl().
*			- Please call this API using the timer if want to stop the transfer.(in synchronous transfer)
 */
kint32                      dd_uart_colabo_stop(DdUartColabo *self, kuchar ch);

/*
*It is a function started when the UART transmission is completed.<br>
*The callback function for the transmission registered by @ref Dd_UART_Ctrl is started.
*@param [in]	ch	Channel number(0 to 7)
*/
void	                     dd_uart_colabo_int_handler_tx(DdUartColabo *self, kuchar ch);

#ifdef CO_DDIM_UTILITY_USE
/*
*Start sending data via DMA and UART FIFO.
*@param [in]	uartCh	UART channel number(0 to 7)
*@param [in]	dmaCh	DMA channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_UART_DMA_SS_ERROR		: DMA stop status error
*@retval		D_DD_UART_FORCE_STOP		: Forced stop by Dd_UART_Stop()
*@remarks	If send_dma_callback was specified, this API is asynchronization.<br>
*			If send_dma_callback was not specified, this API is synchronization.<br>
*			In the case of multi-mode, before Dd_UART_Start_Send_DMA run, you run the Dd_UART_Send_Recv_Disable.<br>
*			In the case of multi-mode, when returning to the CPU transfer, start over from Dd_UART_Ctrl.<br>
*/
kint32                      dd_uart_colabo_start_send_dma(DdUartColabo *self, kuchar uartCh, kuchar dmaCh);

/*
*Set data information for receiving data (DMA). Set the pointer to the buffer and size of it.
*@param [in]	ch	Channel number(0 to 7)
*@param [in]	recvAddr	Receive data address
*@param [in]	num			Number of data
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@remarks	The recvAddr to set "kuchar" pointer.<br>
*/
kint32                      dd_uart_colabo_set_recv_data_dma(DdUartColabo *self, kuchar ch,
		                              void const* const recvAddr, kuint32 num);

/*
*Start receive data via DMA and UART FIFO.
*@param [in]	uartCh	UART channel number(0 to 7)
*@param [in]	dmaCh	DMA channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_UART_DMA_SS_ERROR		: DMA stop status error
*@remarks	If recv_dma_callback was specified, this API is asynchronization.<br>
*			If recv_dma_callback was not specified, this API is synchronization.<br>
*			In the case of multi-mode, before Dd_UART_Start_Send_DMA run, you run the Dd_UART_Send_Recv_Disable.<br>
*			In the case of multi-mode, when returning to the CPU transfer, start over from Dd_UART_Ctrl.<br>
*/
kint32                      dd_uart_colabo_start_recv_dma(DdUartColabo *self, kuchar uartCh, kuchar dmaCh);

/*
*To disable the transmission and reception.
*@param [in]	ch	Channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                      dd_uart_colabo_send_recv_disable(DdUartColabo *self, kuchar ch);
/*@}*/
#endif

#endif /* __DD_UART_COLABO_H__ */
