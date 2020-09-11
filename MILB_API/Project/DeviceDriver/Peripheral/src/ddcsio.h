/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-07
 *@author : 王顺
 *@brief : DdCsio
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */
/**
 * @file		ddcsio.h
 * @brief		Clock synchronous serial interface driver
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
/**
 @addtogroup dd_csio
 @{
 - @ref CSIO_Sample
 - @ref CSIO_Full_Duplex_Master_Sample
 - @ref CSIO_Full_Duplex_Slave_Sample
 - @ref CSIO_Util_Sample
 - @ref CSIO_Util_Sample_DMA_Send
 - @ref CSIO_Util_Sample_DMA_Recv
 */


#ifndef __DD_CSIO_H__
#define __DD_CSIO_H__

#include <klib.h>
#include "driver_common.h"
#include "ddcsiodma.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_CSIO                  (dd_csio_get_type())
#define DD_CSIO(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdCsio))
#define DD_IS_CSIO(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_CSIO))

/**< CSIO normal complete. */
#define C_CSIO_NORMAL_COMPLETE			(D_DDIM_OK)
/**< Input parameter error. */
#define C_CSIO_INPUT_PARAM_ERROR		(D_DD_CSIO | D_DDIM_INPUT_PARAM_ERROR)
/**< Semaphore acquisition Time Out */
#define	C_CSIO_SEM_TIMEOUT					(D_DD_CSIO | D_DDIM_SEM_TIMEOUT)
/**< Semaphore acquisition NG */
#define	C_CSIO_SEM_NG								(D_DD_CSIO | D_DDIM_SEM_NG)
/**< CSIO receive overrun error. */
#define C_CSIO_RECV_OVERRUN_ERROR	(D_DD_CSIO | D_DDIM_OVERRUN_DATA)
/**< CSIO exist data in send fifo when save the send FIFO read pointer. */
#define C_CSIO_DATA_EXIST_ERROR			(D_DD_CSIO | D_DDIM_DATA_EXIST_ERROR)
/**< CSIO saved data was already overwritten. */
#define C_CSIO_OVERWRITE_ERROR			(D_DD_CSIO | D_DDIM_OVERWRITE_ERROR)
/**< CSIO DMA stop status error. */
#define C_CSIO_DMA_SS_ERROR					(D_DD_CSIO | D_DDIM_STATUS_ABNORMAL)
/**< CSIO Time Out(Only when the master) */
#define C_CSIO_TIMEOUT							(D_DD_CSIO | D_DDIM_TIMEOUT)
/**< CSIO Forced stop by dd_csio_stop(NULL, ) */
#define C_CSIO_FORCE_STOP						(D_DD_CSIO | 0x0100)

// Rest FIFO SELECT
#define C_CSIO_SELECT_FIFO_1					(1) /**< Reset FIFO1. */
#define C_CSIO_SELECT_FIFO_2					(2) /**< Reset FIFO2. */
#define C_CSIO_SELECT_FIFO_BOTH			(3) /**< Reset FIFO1 and FIFO2. */

#ifdef CO_DDIM_UTILITY_USE
/** DMA mode selection of send. */
#define C_CSIO_SEND_DMA_MODE_DEMAND	(0) /**< Demand Transfer mode */
/** DMA mode selection of receive. */
#define C_CSIO_RECV_DMA_MODE_DEMAND	(0) /**< Demand Transfer mode */
#endif


typedef enum _DdCsioMode DdCsioMode;
typedef enum _DdCsioType DdCsioType;
typedef enum _DdCsioDataLength DdCsioDataLength;
typedef enum _DdCsioBitDir DdCsioBitDir;
typedef struct _DdCsioFifoCtrl DdCsioFifoCtrl;
#ifdef CO_DDIM_UTILITY_USE
typedef struct _DdCsioSendCtrl DdCsioSendCtrl;
#endif

/** Transmit mode selection. */
enum _DdCsioMode
{
	DdCsio_DD_CSIO_MODE_NORMAL_SC_H = 0, /**< Normal communication & Serial clock is "H" format */
	DdCsio_DD_CSIO_MODE_NORMAL_SC_L, /**< Normal communication & Serial clock is "L" format */
	DdCsio_DD_CSIO_MODE_SPI_SC_H, /**< SPI communication & Serial clock is "H" format */
	DdCsio_DD_CSIO_MODE_SPI_SC_L /**< SPI communication & Serial clock is "L" format */
};

/** Master/Slave selection. */
enum _DdCsioType
{
	DdCsio_DD_CSIO_TYPE_MASTER = 0, /**< Type of Master */
	DdCsio_DD_CSIO_TYPE_SLAVE /**< Type of Slave */
};

/** Data length selection. */
enum _DdCsioDataLength
{
	DdCsio_DD_CSIO_DATA_LENGTH_8 = 0, /**< 8 bit length */
	DdCsio_DD_CSIO_DATA_LENGTH_5, /**< 5 bit length */
	DdCsio_DD_CSIO_DATA_LENGTH_6, /**< 6 bit length */
	DdCsio_DD_CSIO_DATA_LENGTH_7, /**< 7 bit length */
	DdCsio_DD_CSIO_DATA_LENGTH_9 /**< 9 bit length */
};

/** Bit direction selection. */
enum _DdCsioBitDir
{
	DdCsio_DD_CSIO_BIT_DIR_LSB_FIRST = 0, /**< LSB first */
	DdCsio_DD_CSIO_BIT_DIR_MSB_FIRST	 /**< MSB first */
} ;

/** FIFO control table structure. */
struct _DdCsioFifoCtrl
{
	kuchar fsel; /**< FIFO selection bit	(0:send-1,receive-2	1:send-2,receive-1) */
	kuchar fe1; /**< FIFO 1 enable bit	(0:disable	1:enable) */
	kuchar fe2; /**< FIFO 2 enable bit	(0:disable	1:enable) */
	kuint16 fbyteRecv; /**< Receive data size (byte) */
	kuchar fset; /**< FIFO transfer reload pointer storing bit	(0:no storing	1:storing) */
	kuchar flste; /**< Data-lost check permmision bit	(0:no check	1:check) */
};

#ifdef CO_DDIM_UTILITY_USE
/** CSIO utility control data.
 * @remarks This is for utility
 */
struct _DdCsioSendCtrl
{
	DdCsioMode mode; /**< Transmit mode */
	kulong baudrate; /**< Baud rate reload counter value (>=3) */
	DdCsioBitDir bitDirection; /**< Bit direction, LSB first or MSB first */
	DdCsioDataLength dataLength; /**< Data length */
	kuchar fifoDmaEnable; /**< Send FIFO and DMA enable bit (0:disable	1:enable) */
	kuchar dmaCh; /**< DMA Channel number for send FIFO */
};
#endif


typedef struct _DdCsio DdCsio;
typedef struct _DdCsioPrivate DdCsioPrivate;

//T_DD_CSIO_CTRL改为DdCsioCtrl，将此结构体的成员全部放入类结构体中。
struct _DdCsio
{
	KObject parent;
	DdCsioType type; /**< Master/Slave selection bit */
	DdCsioMode mode; /**< Transmit mode */
	kulong baudrate; /**< Baud rate reload counter value (>=3) */
	DdCsioBitDir bitDirection; /**< Bit direction, LSB first or MSB first */
	DdCsioDataLength dataLength; /**< Data length */
	kuchar sop; /**< Serial output port setting (0:uninfluential, 1:High ) */
	DdCsioFifoCtrl* fifoCtrl; /**< FIFO control table */
	VpCallback pcallback;
/**< Callback function pointer<br>
 If pcallback was specified, dd_csio_start_send and dd_csio_start_recv is asynchronization.<br>
 If pcallback was not specified, dd_csio_start_send and dd_csio_start_recv is synchronization.
 */
};


KConstType		dd_csio_get_type(void);
DdCsio*			dd_csio_new(void);
/**
Execute exclusive control for designated CSIO channel.<br>
When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return
 "D_DDIM_OK",<br>
if the channel state is in-use (lock), return "C_CSIO_SEM_NG".<br>
When timeout occurs, return "C_CSIO_SEM_TIMEOUT".
@param [in]	ch		Channel number(0 to 7)
@param [in] tmout	Time of timeout<br>
					<ul><li>Positive Value(Time of timeout)
						<li>@ref D_DDIM_USER_SEM_WAIT_POL
						<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_CSIO_SEM_TIMEOUT		: Semaphore acquisition Time Out
@retval		C_CSIO_SEM_NG			: Semaphore acquisition NG
@remarks	This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
			This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32			dd_csio_open (DdCsio *self,kuchar ch, kint32 tmout);

/**
Cancel exclusive control for designated CSIO channel.<br>
@param [in]	ch	Channel number(0 to 7)
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_CSIO_SEM_NG			: Semaphore release NG
@remarks	This API uses DDIM_User_Sig_Sem().
*/
kint32			dd_csio_close(DdCsio *self, kuchar ch);

/**
Set CSIO operation condition and callback function for the specified channel.
@param [in]	ch			Channel number(0 to 7)
@param [in]	csioCtrl	CSIO Control data. See @ref DdCsio.
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32			dd_csio_ctrl(kuchar ch, DdCsio const* const self);

/**
Get CSIO operation condition and callback function for the specified channel.
@param [in]		ch	Channel number(0 to 7)
@param [out]	csioCtrl	CSIO Control data. See @ref DdCsio.
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32			dd_csio_get_ctrl(kuchar ch, DdCsio* const self);

/**
Set CSIO baudrate.
@param [in]		ch	Channel number(0 to 7)
@param [in]		baudRate	Baud rate reload counter value(>=3)
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32			dd_csio_set_baudrate(DdCsio *self, kuchar ch, kuint16 baudRate );

/**
Get CSIO baudrate.
@param [in]		ch	Channel number(0 to 7)
@param [out]	baudRate	Baud rate reload counter value
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32			dd_csio_get_baudrate(DdCsio *self, kuchar ch, kuint16* baudRate );

/**
Save the send FIFO read pointer.<br>
Read pointer is used in order to resend, when a communication fault occur.
@param [in]		ch			Channel number(0 to 7)
@param [in]		lostDetect	Reload data lost detect enable (0:detect disable, 1:detect enable)
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_CSIO_DATA_EXIST_ERROR	: Exist data in send fifo. Wait to complete transmission.
@remarks	Please don't call this API during transmission.
*/
kint32			dd_csio_save_send_fifo_pointer(DdCsio *self, kuchar ch, kuchar lostDetect );

/**
Reload the data saved by the @ref dd_csio_save_send_fifo_pointer to a read pointer.
@param [in]		ch			Channel number(0 to 7)
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_CSIO_OVERWRITE_ERROR	: Saved data was already overwritten.<br>
										  Please reset FIFO and retry transmitting processing.
@retval		C_CSIO_FORCE_STOP		: Forced stop by dd_csio_stop(NULL, )
@retval		C_CSIO_TIMEOUT			: CSIO Time Out
@remarks
			- Please don't call this API during transmission.
			- Please don't transmit after reloading in this API until reloading finishes.
			- This API cannot be used in a full-duplex communication.
*/
kint32			dd_csio_reload_send_fifo_pointer(DdCsio *self, kuchar ch );

/**
Get reload status.
@param [in]		ch			Channel number(0 to 7)
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@retval		0							: Not reload.
@retval		1							: Reloading.
@remarks	Please don't transmit after reloading in this API until reloading finishes.
*/
kint32			dd_csio_get_reload_status(DdCsio *self, kuchar ch );

/**
Reset FIFO.
@param [in]		ch			Channel number(0 to 7)
@param [in]		fifoNum	FIFO select (@ref C_CSIO_SELECT_FIFO_1 or @ref C_CSIO_SELECT_FIFO_2 or
C_CSIO_SELECT_FIFO_BOTH)
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@remarks	Please don't call this API during transmission.
*/
kint32			dd_csio_reset_fifo(DdCsio *self, kuchar ch, kuchar fifoNum );

/**
Set data information to send by CSIO.<br>
Please input transmitted data Buffer pointer and size information.
@param [in]	ch			Channel number(0 to 7)
@param [in]	sendAddr	Send data address
@param [in]	num			Number of data
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@remarks	The value must be guaranteed about the transmission data until the transmission processing
is completed.<br>
			Set "kuint16" pointer to sendAddr when Data Length is "DdCsio_DD_CSIO_DATA_LENGTH_9". <br>
			Set "kuchar" pointer to sendAddr when Data Length is "DdCsio_DD_CSIO_DATA_LENGTH_8" or less.<br>
*/
kint32			dd_csio_set_send_data(DdCsio *self, kuchar ch, void const* const sendAddr, kuint32 num);

/**
Start sending data.
@param [in]	ch	Channel number(0 to 7)
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_CSIO_FORCE_STOP		: Forced stop by dd_csio_stop(NULL, )
@retval		C_CSIO_TIMEOUT			: CSIO Time Out
@remarks	If pcallback was specified, this API is asynchronization.<br>
			If pcallback was not specified, this API is synchronization.
*/
kint32			dd_csio_start_send(DdCsio *self, kuchar ch);

/**
Set data information for receiving data. Set the pointer to the buffer and size of it.
@param [in]	ch	Channel number(0 to 7)
@param [in]	recvAddr	Receive data address
@param [in]	num			Number of data
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@remarks	Set "kuint16" pointer to recvAddr when Data Length is "DdCsio_DD_CSIO_DATA_LENGTH_9". <br>
			Set "kuchar" pointer to recvAddr when Data Length is "DdCsio_DD_CSIO_DATA_LENGTH_8" or less.<br>
*/
kint32			dd_csio_set_recv_data(DdCsio *self, kuchar ch, void const* const recvAddr, kuint32 num);

/**
Start receiving data.
@param [in]	ch	Channel number(0 to 7)
@retval		D_DDIM_OK						: OK
@retval		C_CSIO_INPUT_PARAM_ERROR		: Input parameter error
@retval		C_CSIO_RECV_OVERRUN_ERROR	: Overrun error
@retval		C_CSIO_FORCE_STOP			: Forced stop by dd_csio_stop(NULL, )
@remarks	If pcallback was specified, this API is asynchronization.<br>
			If pcallback was not specified, this API is synchronization.
*/
kint32			dd_csio_start_recv(DdCsio *self, kuchar ch);

/**
Start full-duplex communication.
@param [in]	ch	Channel number(0 to 7)
@retval		D_DDIM_OK						: OK
@retval		C_CSIO_INPUT_PARAM_ERROR		: Input parameter error
@remarks
			- This API is asynchronization.
			- fifoCtrl and pcallback in DdCsio must always specify.
*/
kint32			dd_csio_start_full_duplex(DdCsio *self, kuchar ch);

/**
Stop sending/receiving data(force stop).
@param [in]	ch	Channel number(0 to 7)
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@remarks
			- If want to run again after running this API, please reconfigure dd_csio_ctrl().
			- Please call this API using the timer if want to stop the transfer.(in synchronous transfer)
 */
kint32			dd_csio_stop(DdCsio *self, kuchar ch);

/*@}*/

/**
@weakgroup dd_csio
@{
	<hr>
	@section CSIO_Sample Sample of Normally communication
	@code

	kint32       ret = D_DDIM_OK;
	kuchar       ch = 4;
	kuchar       send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x00,0x11};
	kuchar       receive_buf[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	kuint32      send_size = 10;
	kuint32      receive_size = 10;
	DdCsioDma  cal_tbl;
	DdCsio csioCtrl;
	DdCsioFifoCtrl fifoCtrl;

	csioCtrl.fifoCtrl = &fifoCtrl;

	cal_tbl.inFreq  = 100000;		// 100 Kbps
	cal_tbl.calFreq = 0;
	ret = dd_csio_dma_calculate(&cal_tbl);
	if( ret != D_DDIM_OK ) {
		// error correction code here.
		return ;
	}

	csioCtrl.mode					= DdCsio_DD_CSIO_MODE_NORMAL_SC_H;	// Normal communication
	 & Serial clock is "H" format
	csioCtrl.baudrate				= cal_tbl.calFreq;				// Baudrate generator
	csioCtrl.bitDirection 		= DdCsio_DD_CSIO_BIT_DIR_MSB_FIRST;	// MSB first
	csioCtrl.dataLength			= DdCsio_DD_CSIO_DATA_LENGTH_8;		// 8 bit
	csioCtrl.sop					= 0;							// uninfluential
	csioCtrl.type					= DdCsio_DD_CSIO_TYPE_MASTER;		// Master
	csioCtrl.fifoCtrl->fsel		= 0;							// FIFO1 is transfer, FIFO02 is receive
	csioCtrl.fifoCtrl->flste		= 0;							// Data-lost check permmision is disable
	csioCtrl.fifoCtrl->fset		= 0;							// FIFO transfer reload pointer storing is disable
	csioCtrl.fifoCtrl->fe1		= 0;							// FIFO01 is disable
	csioCtrl.fifoCtrl->fe2		= 0;							// FIFO02 is disable
	csioCtrl.fifoCtrl->fbyteRecv = 0;							// 0byte

	csioCtrl.pcallback = 0;

	ret = dd_csio_open(NULL, ch, D_DDIM_WAIT_END_TIME);
	if( ret != D_DDIM_OK ) {
		// error correction code here.
		return ;
	}
	ret = dd_csio_ctrl(ch, &csioCtrl);

	// Transfer process
	ret = dd_csio_set_send_data(NULL, ch, send_buf, send_size);
	ret = dd_csio_start_send(NULL, ch);

	// Receive process
	ret = dd_csio_set_recv_data(NULL, ch, receive_buf, receive_size);
	ret = dd_csio_start_recv(NULL, ch);

	ret = dd_csio_close(NULL, ch);

	@endcode


	<hr>
	@section CSIO_Full_Duplex_Master_Sample Sample of Full-duplex communication (Master)
	@code

	kint32       ret = D_DDIM_OK;
	kuchar       ch = 4;
	kuchar       send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x00,0x11};
	kuchar       receive_buf[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	kuint32      send_size = 10;
	kuint32      receive_size = 10;
	DdCsioDma  cal_tbl;
	DdCsio csioCtrl;
	DdCsioFifoCtrl fifoCtrl;

	csioCtrl.fifoCtrl = &fifoCtrl;

	cal_tbl.inFreq  = 100000;		// 100 Kbps
	cal_tbl.calFreq = 0;
	ret = dd_csio_dma_calculate(&cal_tbl);
	if( ret != D_DDIM_OK ) {
		// error correction code here.
		return ;
	}

	csioCtrl.mode					= DdCsio_DD_CSIO_MODE_NORMAL_SC_H;	// Normal communication
	 & Serial clock is "H" format
	csioCtrl.baudrate				= cal_tbl.calFreq;				// Baudrate generator
	csioCtrl.bitDirection 		= DdCsio_DD_CSIO_BIT_DIR_MSB_FIRST;	// MSB first
	csioCtrl.dataLength			= DdCsio_DD_CSIO_DATA_LENGTH_8;		// 8 bit
	csioCtrl.sop					= 0;							// uninfluential
	csioCtrl.type					= DdCsio_DD_CSIO_TYPE_MASTER;		// Master
	csioCtrl.fifoCtrl->fsel		= 0;							// FIFO1 is transfer, FIFO02 is receive
	csioCtrl.fifoCtrl->flste		= 0;							// Data-lost check permmision is disable
	csioCtrl.fifoCtrl->fset		= 0;							// FIFO transfer reload pointer storing is disable
	csioCtrl.fifoCtrl->fe1		= 0;							// FIFO01 is disable
	csioCtrl.fifoCtrl->fe2		= 0;							// FIFO02 is disable
	csioCtrl.fifoCtrl->fbyteRecv = 0;							// 0byte

	csioCtrl.pcallback = sample_callback_function;

	ret = dd_csio_open(NULL, ch, D_DDIM_WAIT_END_TIME);
	if( ret != D_DDIM_OK ) {
		// error correction code here.
		return ;
	}
	ret = dd_csio_ctrl(ch, &csioCtrl);

	// Transfer set
	ret = dd_csio_set_send_data(NULL, ch, send_buf, send_size);

	// Receive set
	ret = dd_csio_set_recv_data(NULL, ch, receive_buf, receive_size);

	//
	// Demand the preparation to the slave side device according to the handshaking signal.
	// And the waited for preparation completion.
	//

	// Start communication
	ret = dd_csio_start_full_duplex(NULL, ch);

	@endcode


	<hr>
	@section CSIO_Full_Duplex_Slave_Sample Sample of Full-duplex communication (Slave)
	@code

	kint32       ret = D_DDIM_OK;
	kuchar       ch = 4;
	kuchar       send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x00,0x11};
	kuchar       receive_buf[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	kuint32      send_size = 10;
	kuint32      receive_size = 10;
	DdCsioDma  cal_tbl;
	DdCsio csioCtrl;
	DdCsioFifoCtrl fifoCtrl;

	csioCtrl.fifoCtrl = &fifoCtrl;

	cal_tbl.inFreq  = 100000;		// 100 Kbps
	cal_tbl.calFreq = 0;
	ret = dd_csio_dma_calculate(&cal_tbl);
	if( ret != D_DDIM_OK ) {
		// error correction code here.
		return ;
	}

	csioCtrl.mode					= DdCsio_DD_CSIO_MODE_NORMAL_SC_H;	// Normal communication
	& Serial clock is "H" format
	csioCtrl.baudrate				= cal_tbl.calFreq;				// Baudrate generator
	csioCtrl.bitDirection 		= DdCsio_DD_CSIO_BIT_DIR_MSB_FIRST;	// MSB first
	csioCtrl.dataLength			= DdCsio_DD_CSIO_DATA_LENGTH_8;		// 8 bit
	csioCtrl.sop					= 0;							// uninfluential
	csioCtrl.type					= DdCsio_DD_CSIO_TYPE_SLAVE;			// Slave
	csioCtrl.fifoCtrl->fsel		= 0;							// FIFO1 is transfer, FIFO02 is receive
	csioCtrl.fifoCtrl->flste		= 0;							// Data-lost check permmision is disable
	csioCtrl.fifoCtrl->fset		= 0;							// FIFO transfer reload pointer storing is disable
	csioCtrl.fifoCtrl->fe1		= 0;							// FIFO01 is disable
	csioCtrl.fifoCtrl->fe2		= 0;							// FIFO02 is disable
	csioCtrl.fifoCtrl->fbyteRecv = 0;							// 0byte

	csioCtrl.pcallback = sample_callback_function;

	ret = dd_csio_open(NULL, ch, D_DDIM_WAIT_END_TIME);
	if( ret != D_DDIM_OK ) {
		// error correction code here.
		return ;
	}
	ret = dd_csio_ctrl(ch, &csioCtrl);

	// Transfer set
	ret = dd_csio_set_send_data(NULL, ch, send_buf, send_size);

	// Receive set
	ret = dd_csio_set_recv_data(NULL, ch, receive_buf, receive_size);

	// Start communication
	ret = dd_csio_start_full_duplex(NULL, ch);

	//
	// Notify the preparation completion to master side device.
	//

	@endcode


	<hr>
	@section CSIO_Util_Sample Sample of Transfer utility
	@code

	kint32		ret = D_DDIM_OK;
	kuchar		ch = 4;
	kuchar       send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x00,0x11};
	kuint32		send_size = 10;
	DdCsioSendCtrl csio_send_ctrl;

	csio_send_ctrl.mode 			= DdCsio_DD_CSIO_MODE_NORMAL_SC_H;	// Normal communication
	& Serial clock is "H" format
	csio_send_ctrl.baudrate 		= 100000;						// Baudrate generator (100 Kbps)
	csio_send_ctrl.bitDirection	= DdCsio_DD_CSIO_BIT_DIR_MSB_FIRST;	// MSB first
	csio_send_ctrl.dataLength		= DdCsio_DD_CSIO_DATA_LENGTH_8;		// 8 bit
	csio_send_ctrl.fifoDmaEnable	= 0;
	csio_send_ctrl.dmaCh			= 0;

	ret = dd_csio_dma_send(NULL, ch, &csio_send_ctrl, send_buf, send_size);
	if( ret != D_DDIM_OK ) {
		// error correction code here.
		return ;
	}

	@endcode


	<hr>
	@section CSIO_Util_Sample_DMA_Send Sample of Transfer via DMA utility
	@code

	kint32				ret;
	kuchar				ch = 2;
	kuchar				send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA};
	kuint32				send_size = 10;
	kulong				intid;
	kulong				intpri;
	DdCsioDma		cal_tbl;
	DdCsio		csioCtrl;
	DdCsioFifoCtrl	fifoCtrl;

	csioCtrl.fifoCtrl = &fifoCtrl;

	ret = dd_csio_open(NULL, ch, D_DDIM_WAIT_END_TIME);
	if (ret !=D_DDIM_OK) {
		Ddim_Print(("CSIO Open ERR. ret=0x%x\n", ret));
		return;
	}

	cal_tbl.inFreq  = 5500000;		//bps
	cal_tbl.calFreq = 0;
	ret = dd_csio_dma_calculate(&cal_tbl);
	if( ret != D_DDIM_OK ) {
		dd_csio_close(NULL, ch);
		// error correction code here.
		return;
	}

	csioCtrl.mode					= DdCsio_DD_CSIO_MODE_NORMAL_SC_H;	// Normal communication
	 & Serial clock is "H" format
	csioCtrl.baudrate				= cal_tbl.calFreq;				// Baudrate generator
	csioCtrl.bitDirection 		= DdCsio_DD_CSIO_BIT_DIR_MSB_FIRST;	// MSB first
	csioCtrl.dataLength			= DdCsio_DD_CSIO_DATA_LENGTH_8;		// 8 bit
	csioCtrl.sop					= 0;							// uninfluential
	csioCtrl.type					= DdCsio_DD_CSIO_TYPE_MASTER;		// Master
	csioCtrl.fifoCtrl->fsel		= 0;							// FIFO1 is transfer, FIFO02 is receive
	csioCtrl.fifoCtrl->flste		= 0;							// Data-lost check permmision is disable
	csioCtrl.fifoCtrl->fset		= 0;							// FIFO transfer reload pointer storing is disable
	csioCtrl.fifoCtrl->fe1		= 1;							// FIFO01 is enable
	csioCtrl.fifoCtrl->fe2		= 0;							// FIFO02 is disable
	csioCtrl.fifoCtrl->fbyteRecv = 0;							// 0byte

	csioCtrl.pcallback = NULL;

	ret = dd_csio_ctrl(ch, &csioCtrl);
	if (ret !=D_DDIM_OK) {
		dd_csio_close(NULL, ch);
		// error correction code here.
		return;
	}

	ret = dd_csio_set_send_data(NULL, ch, send_buf, send_size);
	if (ret !=D_DDIM_OK) {
		dd_csio_close(NULL, ch);
		// error correction code here.
		return;
	}

	// Disable CSIO interrupt
	dd_gic_ctrl(NULL, (DdGicIntid)(DdGic_INTID_UART_CH0_TRANSMISSION_INT + ch), 0, -1, -1);

	ret = dd_csio_dma_start_send_dma(NULL, ch, 5, E_DD_CSIO_SEND_DMA_MODE_DEMAND);
		// Start sending data via DMA
	if( ret != D_DDIM_OK ) {				// Second parameter is DMA channel
		// error correction code here.
	}

	// Enable CSIO interrupt
	dd_gic_ctrl(NULL, (DdGicIntid)(DdGic_INTID_UART_CH0_TRANSMISSION_INT + ch), 1, -1, -1);

	dd_csio_close(NULL, ch);

	@endcode


	<hr>
	@section CSIO_Util_Sample_DMA_Recv Sample of Receive via DMA utility
	@code

	kint32				ret;
	kuchar				ch = 2;
	kuchar				recv_buf[10];
	kuint32				recv_size = 10;
	kulong				intid;
	kulong				intpri;
	DdCsioDma		cal_tbl;
	DdCsio		csioCtrl;
	DdCsioFifoCtrl	fifoCtrl;

	csioCtrl.fifoCtrl = &fifoCtrl;

	ret = dd_csio_open(NULL, ch, D_DDIM_WAIT_END_TIME);
	if (ret !=D_DDIM_OK) {
		Ddim_Print(("CSIO Open ERR. ret=0x%x\n", ret));
		return;
	}

	cal_tbl.inFreq  = 5500000;		//bps
	cal_tbl.calFreq = 0;
	ret = dd_csio_dma_calculate(&cal_tbl);
	if( ret != D_DDIM_OK ) {
		dd_csio_close(NULL, ch);
		// error correction code here.
		return;
	}

	csioCtrl.mode					= DdCsio_DD_CSIO_MODE_NORMAL_SC_H;	// Normal communication
	 & Serial clock is "H" format
	csioCtrl.baudrate				= cal_tbl.calFreq;				// Baudrate generator
	csioCtrl.bitDirection 		= DdCsio_DD_CSIO_BIT_DIR_MSB_FIRST;	// MSB first
	csioCtrl.dataLength			= DdCsio_DD_CSIO_DATA_LENGTH_8;		// 8 bit
	csioCtrl.sop					= 0;							// uninfluential
	csioCtrl.type					= DdCsio_DD_CSIO_TYPE_MASTER;		// Master
	csioCtrl.fifoCtrl->fsel		= 0;							// FIFO1 is transfer, FIFO02 is receive
	csioCtrl.fifoCtrl->flste		= 0;							// Data-lost check permmision is disable
	csioCtrl.fifoCtrl->fset		= 0;							// FIFO transfer reload pointer storing is disable
	csioCtrl.fifoCtrl->fe1		= 1;							// FIFO01 is enable
	csioCtrl.fifoCtrl->fe2		= 1;							// FIFO02 is enable
	csioCtrl.fifoCtrl->fbyteRecv = 10;							// 10byte

	csioCtrl.pcallback = NULL;

	ret = dd_csio_ctrl(ch, &csioCtrl);
	if (ret !=D_DDIM_OK) {
		dd_csio_close(NULL, ch);
		// error correction code here.
		return;
	}

	ret = dd_csio_set_recv_data(NULL, ch, recv_buf, recv_size);
	if (ret !=D_DDIM_OK) {
		dd_csio_close(NULL, ch);
		// error correction code here.
		return;
	}

	// Disable CSIO interrupt
	dd_gic_ctrl(NULL, (DdGicIntid)(DdGic_INTID_UART_CH0_RECEPTION_INT + ch), 0, -1, -1);

	ret = dd_csio_dma_start_recv_dma(NULL, ch, 5, E_DD_CSIO_RECV_DMA_MODE_DEMAND);
	// Start recving data via DMA
	if( ret != D_DDIM_OK ) {				// Second parameter is DMA channel
		// error correction code here.
	}

	// Enable CSIO interrupt
	dd_gic_ctrl(NULL, (DdGicIntid)(DdGic_INTID_UART_CH0_RECEPTION_INT + ch), 1, -1, -1);

	dd_csio_close(NULL, ch);

	@endcode


*/
/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* __DD_CSIO_H__ */
