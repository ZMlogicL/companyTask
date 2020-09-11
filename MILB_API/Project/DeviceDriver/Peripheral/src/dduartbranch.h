/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-10
* @author    : 肖泽友
* @brief        :uart driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、branch
*
*@version   :1.0.0
*
*/

#ifndef __DD_UART_BRANCH_H__
#define __DD_UART_BRANCH_H__

#include <klib.h>
#include "dduart.h"

#define DD_TYPE_UART_BRANCH                    (dd_uart_branch_get_type())
#define DD_UART_BRANCH(obj)                      K_TYPE_CHECK_INSTANCE_CAST(obj, DdUartBranch)
#define DD_IS_UART_BRANCH(obj)                 K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_UART_BRANCH)

typedef struct _DdUartBranch                         DdUartBranch;
typedef struct _DdUartBranchPrivate             DdUartBranchPrivate;

struct _DdUartBranch
{
	KObject parent;
};

KConstType                dd_uart_branch_get_type(void);
DdUartBranch*         dd_uart_branch_get(void);

/*
*Execute exclusive control for designated UART channel.<br>
*When the designated channel is idle (un-lock) state, change the channel state to use(lock)
*When and return "D_DDIM_OK",<br>
*if the channel state is in-use (lock), return "D_DD_UART_SEM_NG".<br>
*When timeout occurs, return "D_DD_UART_SEM_TIMEOUT".
*@param [in]	ch		Channel number(0 to 7)
*@param [in] timeOut	Time of timeout<br>
*					<ul><li>Positive Value(Time of timeout)
*						<li>@ref D_DDIM_USER_SEM_WAIT_POL
*						<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_UART_SEM_TIMEOUT		: Semaphore acquisition Time Out
*@retval		D_DD_UART_SEM_NG			: Semaphore acquisition NG
*@remarks	This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
*			This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32                          dd_uart_branch_open(DdUartBranch *self, kuchar ch, kint32 timeOut);

/*
*Set UART baudrate.
*@param [in]	ch			Channel number(0 to 7)
*@param [in]	baudRate	Baud rate reload counter value(>=4)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                          dd_uart_branch_set_baudrate(DdUartBranch *self, kuchar ch, kushort baudRate);

/*
*Get UART baudrate.
*@param [in]		ch			Channel number(0 to 7)
*@param [out]	baudRate	Baud rate reload counter value
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                          dd_uart_branch_get_baudrate(DdUartBranch *self, kuchar ch, kushort* baudRate);

/*
*Save the send FIFO read pointer.<br>
*Read pointer is used in order to resend, when a communication fault occur.
*@param [in]		ch			Channel number(0 to 7)
*@param [in]		lostDetect	Reload data lost detect enable (0:detect disable, 1:detect enable)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_UART_DATA_EXIST_ERROR	: Exist data in send fifo. Wait to complete transmission.
*@remarks	Please don't call this API during transmission.
*/
kint32                          dd_uart_branch_save_send_fifo_pointer(DdUartBranch *self,
		                                  kuchar ch, kuchar lostDetect);

/*
*Get reload status.
*@param [in]		ch			Channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		0							: Not reload.
*@retval		1							: Reloading.
*@remarks	Please don't transmit after reloading in this API until reloading finishes.
*/
kint32                          dd_uart_branch_get_reload_status(DdUartBranch *self, kuchar ch);

/*
*Reset FIFO.
*@param [in]		ch			Channel number(0 to 7)
*@param [in]		fifoNum	FIFO select (@ref D_DD_UART_SELECT_FIFO_1 or
*@ref D_DD_UART_SELECT_FIFO_2 or @ref D_DD_UART_SELECT_FIFO_BOTH)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@remarks	Please don't call this API during transmission.
*/
kint32                          dd_uart_branch_reset_fifo(DdUartBranch *self, kuchar ch, kuchar fifoNum);

/*
*The UART baudrate is reset.
*@param [in]	ch	Channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                          dd_uart_branch_reset_baudrate(DdUartBranch *self, kuchar ch);

/*
*Reload the data saved by the @ref Dd_UART_Save_Send_FIFO_Pointer to a read pointer.
*@param [in]		ch			Channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_UART_OVERWRITE_ERROR	: Saved data was already overwritten.<br>
*										  Please reset FIFO and retry transmitting processing.
*@remarks
*			- Please don't call this API during transmission.
*			- Please don't transmit after reloading in this API until reloading finishes.
*			- This API cannot be used in a full-duplex communication.
*/
kint32                          dd_uart_branch_reload_send_fifo_pointer(DdUartBranch *self, kuchar ch);

/*
*The UART sending and receiving processing begins.
*@param [in]	ch	Channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@remarks
*			- Please call this API before setting the transmission data.
*/
kint32                          dd_uart_branch_start(DdUartBranch *self, kuchar ch);

/*
*The data that wants to transmit to the transmission buffer is stored.<br>
*When the transmission buffer overflows, the overflow error is sent back.
*@param [in]	ch		Channel number(0 to 7)
*@param [in]	str		Send data
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_OVERFLOW_ERROR	: Overflow error
*/
kint32                          dd_uart_branch_set_str(DdUartBranch *self, kuchar ch, kchar str);

/*
*All the data that exists in the transmission buffer is transmitted.<br>
*The error is sent back when there is no data in the transmission buffer.
*@param [in]	ch	Channel number(0 to 7)
*@retval		D_DDIM_OK				: OK
*@retval		D_DD_UART_NO_SEND_DATA	: It is the data none in transmission buffer
*/
kint32                          dd_uart_branch_put_str(DdUartBranch *self, kuchar ch);

/*
*The receive data specified by the argument is get from the register for the UART reception.
* - When there is no receive data, "Receive data none" is sent back.
 *- When the receive data storage area overflows, "Overflow Error" is sent back.
*.
*@param [in]	ch				Channel number(0 to 7)
*@param [in]	getChar		Receive data
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_UART_NO_RECEIVE		: Not received
*@retval		D_DD_UART_OVERFLOW_ERROR	: Overflow error
*/
kint32                          dd_uart_branch_get_char(DdUartBranch *self, kuchar ch, kchar* const getChar);

/*
*Clear the uart buffer information for overwrite.
*@param [in]	ch	Channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                          dd_uart_branch_clear_overwrite(DdUartBranch *self, kuchar ch);

/*
*Get the write pointer address of send buffer.
*@param [in]	ch	Channel number(0 to 7)
*@return		write pointer address
*/
kulong                         dd_uart_branch_get_send_write_pointer_addr(DdUartBranch *self, kuchar ch);

/*
*Get the overlap count of send buffer.
*@param [in]	ch	Channel number(0 to 7)
*@return		overlap count
*/
kulong                         dd_uart_branch_get_send_overlap_count(DdUartBranch *self, kuchar ch);

/*
*Set the slave address(source)
*@param [in]	ch			Channel number(0 to 7)
*@param [in]	slaveAddr	Slave address(source)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                          dd_uart_branch_set_slave_addr(DdUartBranch *self, kuchar ch,
		                                  kuchar slaveAddr);

/*
*It is a function started when the UART reception is completed.<br>
*It is notified to start the callback function for the reception, and to have received it.
*@param [in]	ch	Channel number(0 to 7)
*@remarks	The argument of the callback function is different according to Auto echo mode as follows.<br>
*			- E_DD_UART_AUTO_ECHO_ON<br>
*				&nbsp;&nbsp;&nbsp;&nbsp;Argument is reception result.<br>
*				&nbsp;&nbsp;&nbsp;&nbsp;Please refer to Cast in the type of kint32.<br>
*			- E_DD_UART_AUTO_ECHO_OFF<br>
*				&nbsp;&nbsp;&nbsp;&nbsp;Argument is reception buffer.<br>
*				&nbsp;&nbsp;&nbsp;&nbsp;After Cast in the type of kint32, please refer to Cast in the type of char.<br>
*/
void	                         dd_uart_branch_int_handler_rx(DdUartBranch *self, kuchar ch);

/*
*The value specified by the argument is get from the register of UART.
*@param [in]	ch			Channel number(0 to 7)
*@param [in]	uartMng	UART management table. See @ref DdUartMng.
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                          dd_uart_branch_get_ctrl(DdUartBranch *self, kuchar ch,
		                                  DdUartMng* const uartMng);

#ifdef CO_DDIM_UTILITY_USE
/* @name Utility Functions
@{*/
/*
*The value specified by the simple argument is set to the register of UART.<br>
*User entry function for transmission/reception specified by the argument is maintained.<br>
*Reception buffer address/size of the reception buffer specified by the argument is assumed to be UART receive data storage area.<br>
*The argument set with a fixed value is as follows.
* - Operation mode				: Asynchronous, normal mode
* - Operation clock				: Internal clock
* - Transferring Direction		: LSB first
* - Inversion serial data format	: NRZ
* - FIFO Setting					: Not use
* - Send callback function		: NULL
*.
*@param [in]	ch				Channel number(0 to 7)
*@param [in]	uartMngSimple	UART simple control table. See @ref DdUartMngSimple.
*@retval		D_DD_OK						: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32	                         dd_uart_branch_initialize_simple(DdUartBranch *self, kuchar ch,
		                                  DdUartMngSimple const *const uartMngSimple);

/*
*Set data information to send by UART (DMA).<br>
*Please input transmitted data Buffer pointer and size information.
*@param [in]	ch			Channel number(0 to 7)
*@param [in]	sendAddr	Send data address
*@param [in]	num			Number of data
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@remarks	The value must be guaranteed about the transmission data until the transmission processing is completed.<br>
*			The sendAddr to set "kuchar" pointer.<br>
*/
kint32                          dd_uart_branch_set_send_data_dma(DdUartBranch *self, kuchar ch,
		                                  void const* const sendAddr, kuint32 num);

#endif

#endif /* __DD_UART_BRANCH_H__ */
