/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :uart driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

/*
@addtogroup dd_uart
@{
	- @ref UART_Sample
*/

#ifndef __DD_UART_H__
#define __DD_UART_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_arm.h"

#define DD_TYPE_UART                       (dd_uart_get_type())
#define DD_UART(obj)                         K_TYPE_CHECK_INSTANCE_CAST(obj, DdUart)
#define DD_IS_UART(obj)                    K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_UART)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Return value of UART processing result */
/*< UART normal complete. */
#define DdUart_NORMAL_COMPLETE  	   (D_DDIM_OK)
/*< Semaphore acquisition Time Out*/
#define	DdUart_SEM_TIMEOUT		           (D_DD_UART | D_DDIM_SEM_TIMEOUT)
/*< Semaphore acquisition NG*/
#define	DdUart_SEM_NG			                   (D_DD_UART | D_DDIM_SEM_NG)
/*< Input parameter error.	*/
#define DdUart_INPUT_PARAM_ERROR	   (D_DD_UART | D_DDIM_INPUT_PARAM_ERROR)
/*< Receive data none.*/
#define DdUart_NO_RECEIVE		               (D_DD_UART | D_DDIM_NO_RECEIVE)
/*< Overflow error.	*/
#define DdUart_OVERFLOW_ERROR            (D_DD_UART | D_DDIM_OVERFLOW_ERR)
/*< Send data none.	*/
#define DdUart_NO_SEND_DATA		            (D_DD_UART | D_DDIM_NO_SEND_DATA)
/*< Parity error.*/
#define DdUart_PARITY_ERROR		            (D_DD_UART | D_DDIM_PARITY_DATA)
/*< Over-run error.	*/
#define DdUart_OVERRUN_ERROR		        (D_DD_UART | D_DDIM_OVERRUN_DATA)
/*< Framing error.*/
#define DdUart_FRAMING_ERROR		        (D_DD_UART | D_DDIM_FRAMING_DATA)
/*< UART exist data in send fifo when save the send FIFO read pointer.*/
#define DdUart_DATA_EXIST_ERROR	        (D_DD_UART | D_DDIM_DATA_EXIST_ERROR)
/*< UART saved data was already overwritten.	*/
#define DdUart_OVERWRITE_ERROR	        (D_DD_UART | D_DDIM_OVERWRITE_ERROR)
/*< UART DMA stop status error. */
#define DdUart_DMA_SS_ERROR		            (D_DD_UART | D_DDIM_STATUS_ABNORMAL)
/*< UART recieved enter code(0x0D or 0x0A).*/
#define DdUart_RECV_ENTER		                (D_DD_UART | 0x100)
/*< UART recieved character.	*/
#define DdUart_RECV_CHAR			                (D_DD_UART | 0x200)
/*< UART recieved slave address.	*/
#define DdUart_RECV_SLAVE_ADDR         	(D_DD_UART | 0x400)
/*< UART Forced stop by Dd_UART_Stop()*/
#define DdUart_FORCE_STOP		                (D_DD_UART | 0x1000)
/*< mode unmacth	*/
#define DdUart_MODE_UNMATCH		        (D_DD_UART | 0x2000)
/*< Writing in the UART is stopped*/
#define DdUart_STOPPED			                    (D_DD_UART | 0x4000)

/* [UART/CSIO common] Max number of channel */
/*< Max number of channeles. (UART/CSIO common)	*/
#define DdUart_CH_NUM_MAX		                (8)

/* [UART/CSIO common] exclusion mode */
/*< Not execution. (UART/CSIO common)	*/
#define DdUart_EXC_OFF			                        (0)
/*< UART execution. (UART/CSIO common)	*/
#define DdUart_EXC_UART			                    (1)
/*< CSIO execution. (UART/CSIO common)	*/
#define DdUart_EXC_CSIO			                    (2)

/* [UART/CSIO common] exclusion mode */
/*< Not execution. */
#define DdUart_IQTOOL_IDLE			                        (0)
/*< Switch to IQTOOL, other command will discard	*/
#define DdUart_IQTOOL_START			                    (1)
/*< Switch to normal UART command mode	*/
#define DdUart_IQTOOL_STOP			                    (2)
/*< IQTool Just use CH2    */
#define DdUart_IQTOOL_UART_CH                         (2)

// Rest FIFO SELECT
/*< Reset FIFO1.*/
#define DdUart_SELECT_FIFO_1	            	(1)
/*< Reset FIFO2.*/
#define DdUart_SELECT_FIFO_2		            (2)
/*< Reset FIFO1 and FIFO2.*/
#define DdUart_SELECT_FIFO_BOTH	        (3)

// UART callback status
/*< recieved character*/
#define DdUart_INT_STATUS_RECV_CHAR			       (D_DD_UART | 0x0000)
/*< recieved enter*/
#define DdUart_INT_STATUS_RECV_ENTER			       (D_DD_UART | 0x0001)
/*< recieved slave address	*/
#define DdUart_INT_STATUS_RECV_SLAVE_ADDR	   (D_DD_UART | 0x0002)
/*< overrun error	*/
#define DdUart_INT_STATUS_OVERRUN_ERROR		(D_DD_UART | 0x0003)
/*< framing error*/
#define DdUart_INT_STATUS_FRAMING_ERROR		(D_DD_UART | 0x0004)
/*< parity error	*/
#define DdUart_INT_STATUS_PARITY_ERROR		        (D_DD_UART | 0x0005)

#define DdUart_DSB()                                                    Dd_ARM_Dsb_Pou()

// Bit Location
/*< Bit Location of REC on SSR */
#define DdUart_SSR_REC_BIT		        (1 << 7)
/*< Bit Location of D8 on DR */
#define DdUart_DR_D8_BIT			        (1 << 8)

#define DdUart_SEND				            (0)
#define DdUart_RECV				            (1)
#define DdUart_DMA_TC_MAX	        (65536)

#ifdef CO_DDIM_UTILITY_USE
#define DdUart_DMACA_IS_BASE		(D_DD_HDMAC1_IS_IDREQ_0)
#endif

typedef struct _DdUartFifoCtrl                                DdUartFifoCtrl;
typedef struct _DdUartMng                                     DdUartMng;
typedef struct _DdUartBufferInfo                           DdUartBufferInfo;
typedef struct _DdUartInfo                                      DdUartInfo;
typedef struct _DdUartMngSimple                          DdUartMngSimple;
typedef struct _DdUartSpinLock                              DdUartSpinLock;

typedef struct _DdUart                                              DdUart;
typedef struct _DdUartPrivate                                 DdUartPrivate;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/*Baud rate selection. */
typedef enum{
	/*< Baud rate:1200 */
	DdUart_BAUD_RATE_1200 = 1200,
	/*< Baud rate:2400 */
	DdUart_BAUD_RATE_2400 = 2400,
	/*< Baud rate:4800 */
	DdUart_BAUD_RATE_4800 = 4800,
	/*< Baud rate:9600 */
	DdUart_BAUD_RATE_9600 = 9600,
	/*< Baud rate:14400 */
	DdUart_BAUD_RATE_14400 = 14400,
	/*< Baud rate:19200 */
	DdUart_BAUD_RATE_19200 = 19200,
	/*< Baud rate:38400 */
	DdUart_BAUD_RATE_38400 = 38400,
	/*< Baud rate:57600 */
	DdUart_BAUD_RATE_57600 = 57600,
	/*< Baud rate:115200 */
	DdUart_BAUD_RATE_115200 = 115200,
	/*< Baud rate:230400 */
	DdUart_BAUD_RATE_230400 = 230400,
	/*< Baud rate:460800 */
	DdUart_BAUD_RATE_460800 = 460800,
	/*< Baud rate:921600 */
	DdUart_BAUD_RATE_921600 = 921600,
	/*< Baud rate:1000000 */
	DdUart_BAUD_RATE_1000000 = 1000000,
	/*< Baud rate:2000000 (For DMA) */
	DdUart_BAUD_RATE_2000000 = 2000000,
	/*< Baud rate:4000000 (For DMA) */
	DdUart_BAUD_RATE_4000000 = 4000000
}DdUartBaudRate;

/* UART mode selection. */
typedef enum{
	/*< Asynchronization normal mode */
	DdUart_MODE_NORMAL = 0,
	/*< Asynchronization multiprocessor mode */
	DdUart_MODE_MULTI
}EDdUartMode;

/* Transferring direction selection. */
typedef enum {
	/*< LSB first */
	DdUart_BIT_DIR_LSB_FIRST = 0,
	/*< MSB first */
	DdUart_BIT_DIR_MSB_FIRST
}DdUartBitDir;

/* Data length selection. */
typedef enum{
	/*< 8 bit length */
	DdUart_DATA_LENGTH_8 = 0,
	/*< 5 bit length */
	DdUart_DATA_LENGTH_5,
	/*< 6 bit length */
	DdUart_DATA_LENGTH_6,
	/*< 7 bit length */
	DdUart_DATA_LENGTH_7,
}DdUartDataLength;

/* Parity bit type selection. */
typedef enum {
	/*< Presence of parity addition: Parity none */
	DdUart_PARITY_BIT_NONE = 0,
	/*< Presence of parity addition: Parity even number */
	DdUart_PARITY_BIT_EVEN,
	/*< Presence of parity addition: Parity odd number */
	DdUart_PARITY_BIT_ODD
}DdUartParityBit;

/* Stop bit length selection. */
typedef enum {
	/*< 1 bit */
	DdUart_STOP_BIT_1 = 0,
	/*< 2 bit */
	DdUart_STOP_BIT_2
} DdUartStopBit;

/* Auto Echo selection. */
typedef enum {
	/*< Auto echo ON */
	DdUart_AUTO_ECHO_ON = 0,
	/*< Auto echo OFF */
	DdUart_AUTO_ECHO_OFF
}DdUartAutoEcho;

/* Settings for saving received data */
typedef enum {
	/*< Save to the buffer */
	DdUart_SAVE2BUFFER_EN = 0,
	/*< Do not save to the buffer */
	DdUart_SAVE2BUFFER_DIS
}DdUartSaveBuffer;

/* Multi processor mode activation. */
typedef enum{
	/*< Asynchronization multiprocessor mode not active */
	DdUart_MODE_MULTI_DIS = 0,
	/*< Asynchronization multiprocessor mode active(Master) */
	DdUart_MODE_MULTI_MASTER,
	/*< Asynchronization multiprocessor mode active(Slave) */
	DdUart_MODE_MULTI_SLAVE,
}UartModeMultiAct;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* FIFO control table structure */
struct _DdUartFifoCtrl
{
	/*< FIFO selection bit	(0:send-1,receive-2	1:send-2,receive1) */
	kuchar					fsel;
	/*< FIFO 1 enable bit	(0:disable	1:enable) */
	kuchar					fe1;
	/*< FIFO 2 enable bit	(0:disable	1:enable) */
	kuchar					fe2;
	/*< Receive data size (byte) */
	kushort					fbyteRecv;
	/*< FIFO transfer reload pointer storing bit	(0:no storing	1:storing) */
	kuchar					fset;
	/*< Data-lost check permmision bit	(0:no check	1:check) */
	kuchar					flste;
};

/*UART management table structure */
struct _DdUartMng
{
	/*< Baud rate */
	DdUartBaudRate		    baudRate;
	/*< Send callback function pointer */
	VP_CALLBACK				psendCallback;
	/*< Receive callback function pointer */
	VP_CALLBACK				preceiveCallback;
	/*< Receive buffer address */
	kuchar*					        receiveBuffAddr;
	/*< Receive buffer size */
	kuint32					        receiveBuffSize;
	/*< Send buffer address */
	kuchar*					        sendBuffAddr;
	/*< Send buffer size */
	kuint32					        sendBuffSize;
	/*< Auto echo */
	DdUartAutoEcho		    autoEcho;
	/*< Save to the buffer */
	DdUartSaveBuffer	    saveBuff;

	/*< UART Mode, Normal or Multi */
	EDdUartMode			    mode;
	/*< Transferring Direction, LSB first or MSB first */
	DdUartBitDir		            bitDirection;
	/*< Stop bit length */
	DdUartStopBit		        stopBitLength;
	/*< Parity bit type */
	DdUartParityBit 	        parityBit;
	/*< Data Length */
	DdUartDataLength	    dataLength;
	/*< External clock select (0:internal, 1:external) */
	kuchar					        extClk;
	/*< Inversion serial data format (0:NRZ, 1:NRZ-Inversion) */
	kuchar					        invNrz;
	/*< Hardware flow control enable (0:disable, 1:enable) */
	kuchar					        flowEnable;

	/*< FIFO control table */
	DdUartFifoCtrl* 	        fifoCtrl;

	/*< Send DMA callback function pointer */
	VP_CALLBACK				sendDmaCallback;
	/*< Receive DMA callback function pointer */
	VP_CALLBACK				recvDmaCallback;
};

/* Uart ring buffer structure */
struct _DdUartBufferInfo
{
	// [receive] read position
	kuint32		rReadPos;
	// [receive] write position
	kuint32		rWritePos;
	// [receive] write size
	kuint32		rSize;
	// [receive] use flag
	kchar		    rFlag;
	// [store] read position
	kuint32		sReadPos;
	// [store] write position
	kuint32		sWritePos;
	// [store] overlap count
	kulong		    sOverlapCnt;
	// [store] write size
	kuint32		sSize;
	// [store] use flag
	kchar		    sFlag;
};

/* Uart control information */
struct _DdUartInfo
{
	/*< Force stop Flag */
	kuchar						forceStopFlg;
	/*< Malti Processor mode active Flag */
	UartModeMultiAct	multiActiveFlg;
	/*< Malti Processor mode Slave address */
	kuchar						multiSlaveAddr;
	/* Send data address (8bit length) */
	kuchar*						sendAddr8;
	/* Receive data address (8bit length) */
	kuchar*						recvAddr8;
	/* Number of data */
	kuint32						num;
	/* DMA Waiting Flag */
	kuchar						dmaWait;
};

#ifdef CO_DDIM_UTILITY_USE
/* UART control table structure
 * @remarks This is for utility
 */
struct _DdUartMngSimple
{
	/*< Baud rate */
	DdUartBaudRate		    baudRate;
	/*< Receive callback function pointer */
	VP_CALLBACK				preceiveCallback;
	/*< Receive buffer address */
	kuchar*					        receiveBuffAddr;
	/*< Receive buffer size */
	kuint32					        receiveBuffSize;
	/*< Send buffer address */
	kuchar*					        sendBuffAddr;
	/*< Send buffer size */
	kuint32					        sendBuffSize;
	/*< Auto echo */
	DdUartAutoEcho		    autoEcho;
	/*< Save to the buffer */
	DdUartSaveBuffer	    saveBuff;
	/*< Stop bit length */
	DdUartStopBit		        stopBitLength;
	/*< Data Length */
	DdUartDataLength	    dataLength;
	/*< Parity bit type */
	DdUartParityBit	            parityBit;
};
#endif

/* Spin Lock */
struct _DdUartSpinLock
{
	kulong 	lock;
	kulong	    dummy[(64 / 4) - 1];
};

struct _DdUart
{
	KObject parent;
};

KConstType               dd_uart_get_type(void);
DdUart*                     dd_uart_get(void);

#ifdef __cplusplus
extern "C" {
#endif

/*
*Cancel exclusive control for designated PWM channel.<br>
*Transmission/reception interrupt is prohibited.
*@param [in]	ch	Channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_UART_SEM_NG			: Semaphore release NG
*@remarks	This function compulsorily releases exclusive control even if it is processing it.
*@remarks	This API uses DDIM_User_Sig_Sem().
*/
kint32                         dd_uart_close(DdUart *self, kuchar ch);

/*
*The value specified by the argument is set to the register of UART.<br>
*User entry function for transmission/reception specified by the argument is maintained.<br>
*Reception buffer address/size of the reception buffer specified by the argument is assumed to be UART receive data storage area.<br>
*@param [in]	ch			Channel number(0 to 7)
*@param [in]	uartMng	UART management table. See @ref DdUartMng.
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@remarks	When the transmission/reception callback function is NULL, the transmission/reception interrupt is prohibited.
*/
kint32                         dd_uart_ctrl(DdUart *self, kuchar ch, DdUartMng const* const uartMng);

/*
*The transmission data specified by the argument is set to the register for the UART transmission.
*@param [in]	ch			Channel number(0 to 7)
*@param [in]	putChar	Send data
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                         dd_uart_put_char(DdUart *self, kuchar ch, kchar putChar);

/*
*Send the slave address(target)
*@param [in]	ch			Channel number(0 to 7)
*@param [in]	slaveAddr	Slave address(target)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_UART_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_UART_MODE_UNMATCH		: Mode unmacth
*@remarks
*			- This API can be called in the following order:<br>
*				Dd_UART_Ctrl() -> Dd_UART_Start()
*				-> Dd_UART_Send_Target_Slave_Addr() -> Dd_UART_Set_Str() -> Dd_UART_Put_Str()<br>
*			- If want to specify a slave of another communication and after a slave<br>
*				communication end -> Dd_UART_Send_Target_Slave_Addr() -> Dd_UART_Set_Str() -> Dd_UART_Put_Str()<br>
*
*/
kint32                         dd_uart_send_target_slave_addr(DdUart *self, kuchar ch, kuchar slaveAddr);

#ifdef CO_DDIM_UTILITY_USE
/*
*All the data that exists in the transmission buffer is transmitted via DMA and UART FIFO.<br>
*The error is sent back when there is no data in the transmission buffer.
*@param [in]	uartCh	UART channel number(0 to 7)
*@param [in]	dmaCh	DMA channel number(0 to 7)
*@retval		D_DDIM_OK				: OK
*@retval		D_DD_UART_NO_SEND_DATA	: It is the data none in transmission buffer
*@remarks	This API uses DDIM_User_Dly_Tsk().
*/
kint32                         dd_uart_put_str_dma(DdUart *self, kuchar uartCh, kuchar dmaCh);
/*@}*/
#endif

#ifdef CO_DDIM_IM_TUNING_ON
/*
*It is a function to SET IQTOOL Enable.
*/
void                           dd_uart_iqtool_enable(DdUart *self);

/*
*It is a function to SET IQTOOL Disable.
*/
void                           dd_uart_iqtool_disable(DdUart *self);

/*
*It is a function to GET IQTOOL Status(Enb/Disable).
*/
kchar                          dd_uart_iqtool_status(DdUart *self);
#endif

/*
 * 获取、设置私有变量、方法
 */
kint32                         dd_uart_get_check_stopping_conditions(DdUart *self, kuchar ch);

kuchar                        dd_uart_get_usio_state(DdUart *self, kuchar ch);
DdUartMng               dd_uart_get_uart_mng(DdUart *self, kuchar ch);
DdUartBufferInfo     dd_uart_get_uart_buff_info(DdUart *self, kuchar ch);
kuchar                        dd_uart_get_uart_flag(DdUart *self, kuchar ch);
DdUartInfo                dd_uart_get_uart_info(DdUart *self, kuchar ch);

#ifdef CO_DDIM_IM_TUNING_ON
kuchar                        dd_uart_get_iqtool_status(DdUart *self);
#endif

void                           dd_uart_set_usio_state(DdUart *self, kuchar ch, kuchar stateValue);
void                           dd_uart_set_info_force_stop_flg(DdUart *self, kuchar ch, kuchar stopFlg);
void                           dd_uart_set_mng_send_buff_addr(DdUart *self, kuchar ch, kchar str);
void                           dd_uart_set_buff_info_write_pos(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_size_add(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_s_write_pos(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_flag(DdUart *self, kuchar ch, kuchar flag);
void                           dd_uart_set_buff_info_overlap(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_read_pos(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_size_subtract(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_s_read_pos(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_r_read_pos_add(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_r_size_subtract(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_r_read_pos(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_flag_subtract(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_size(DdUart *self, kuchar ch, kuchar flag);
void                           dd_uart_set_info_slave_addr(DdUart *self, kuchar ch, kuchar slaveAddr);
void                           dd_uart_set_info_multi_active_flg(DdUart *self, kuchar ch,
		                                UartModeMultiAct multiActiveFlg);
void                           dd_uart_set_mng_receive_buff_addr(DdUart *self, kuchar ch, kchar	rData);
void                           dd_uart_set_buff_info_r_write_pos_add(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_r_size_add(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_r_write_pos(DdUart *self, kuchar ch);
void                           dd_uart_set_buff_info_flag_add(DdUart *self, kuchar ch);
void                           dd_uart_set_info_send_addr(DdUart *self, kuchar ch, void const* const sendAddr);
void                           dd_uart_set_info_num(DdUart *self, kuchar ch, kuint32 num);
void                           dd_uart_set_info_dma_wait(DdUart *self, kuchar ch, kuchar dmaWait);
void                           dd_uart_set_info_recv_addr(DdUart *self, kuchar ch, void const* const recvAddr);

#ifdef __cplusplus
}
#endif

/*@}*/

/*
@weakgroup dd_uart
@{
	<hr>
	@section UART_Sample Sample of UART
	@code

static DdUartAutoEcho UART_auto_echo = E_DD_UART_AUTO_ECHO_ON;
static unsigned char line_buff[256];
static short in_pos = 0;
static short out_pos = 0;

void sample_uart()
{
	kint32	result;
	DdUartMng uartMng;
	kchar sample1[] = "sample1\n";
	kchar sample2[] = "sample2\n";
	kuint32 length;

	uartMng.baudRate = E_DD_UART_BAUD_RATE_57600;			// Baud rate
	uartMng.psendCallback = NULL;							// Send callback function pointer
	if(UART_auto_echo == E_DD_UART_AUTO_ECHO_ON){
		uartMng.preceiveCallback = sample_receive_cb;		// Receive callback function pointer for auto echo on
	}
	else {
		uartMng.preceiveCallback = sample_receive_cb_echo;// Receive callback function pointer for auto echo off
	}
	uartMng.receiveBuffAddr = &gUart_r_buff[0];			// Receive buffer address
	uartMng.receiveBuffSize = sizeof(gUart_r_buff);		// Receive buffer size
	uartMng.sendBuffAddr = &gUart_s_buff[0];				// Send buffer address
	uartMng.sendBuffSize = sizeof(gUart_s_buff);			// Send buffer size
	uartMng.autoEcho = UART_auto_echo;					// Auto Echo
	uartMng.saveBuff = E_DD_UART_SAVE2BUFFER_EN;			// Save to the buffer
	uartMng.mode = E_DD_UART_MODE_NORMAL;					// UART Normal Mode
	uartMng.bitDirection = E_DD_UART_BIT_DIR_LSB_FIRST;	// Transferring Direction, LSB first or MSB first
	uartMng.stopBitLength = E_DD_UART_STOP_BIT_1;		// Stop bit length
	uartMng.dataLength = E_DD_UART_DATA_LENGTH_8;			// Data Length
	uartMng.parityBit = E_DD_UART_PARITY_BIT_NONE;		// Parity bit type
	uartMng.extClk = 0;									// Internal clock
	uartMng.invNrz = 0;									// NRZ
	uartMng.flowEnable = 0;								// Hardware flow Control disable
	uartMng.fifoCtrl = NULL;								// FIFO Setting

	result = Dd_UART_Open(0, D_DDIM_USER_SEM_WAIT_POL);
	if(result != D_DDIM_OK) {
		// error correction code here.
		return ;
	}

	Dd_UART_Ctrl(0, &uartMng);
	Dd_UART_Start(0);

	// Transfer process (sample1)
	length = strlen(sample1);
	for(count = 0; count < length; count++) {
		Dd_UART_Put_Char(ch, sample1[count]);
	}

	// Transfer process (sample2)
	length = strlen(sample2);
	for(count = 0; count < length; count++) {
		Dd_UART_Set_Str(ch, sample2[count]);
	}
	Dd_UART_Put_Str(ch);
}


void sample_receive_cb(void const *const r_result)
{
	kint32 result;
	kchar  receive_data;

	result = (*(kint32*)r_result);
	if(result == D_DDIM_OK){
		Dd_UART_Get_Char(ch, &receive_data);
		line_buff[in_pos++] = receive_data;
	}
}

void sample_receive_cb_echo(void const *const r_result)
{
	kchar  receive_data;

	receive_data = *((kchar*)r_result);
	line_buff[in_pos++] = receive_data;
	Dd_UART_Put_Char(ch, receive_data);	// echo
}

	@endcode
*/

/*@}*/

#endif /* __DD_UART_H__ */
