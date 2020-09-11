/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-05
* @author    : 肖泽友
* @brief        :SPI(Serial Peripheral Interface) driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、driver section（branch）
*
*@version   :1.0.0
*
*/

#ifndef __DD_SPI_DRIVE_BRANCH_H__
#define __DD_SPI_DRIVE_BRANCH_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_hdmac1.h"
#include "dd_arm.h"

#define DD_TYPE_SPI_DRIVE_BRANCH                        (dd_spi_drive_branch_get_type())
#define DD_SPI_DRIVE_BRANCH(obj)                          K_TYPE_CHECK_INSTANCE_CAST(obj, DdSpiDriveBranch)
#define DD_IS_SPI_DRIVE_BRANCH(obj)                     K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_SPI_DRIVE_BRANCH)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Return values
/*< Input parameter error. */
#define DdSpiDriveBranch_INPUT_PARAM_ERROR		(D_DD_SPI | D_DDIM_INPUT_PARAM_ERROR)
/*< Semaphore acquisition Time Out */
#define	DdSpiDriveBranch_SEM_TIMEOUT			            (D_DD_SPI | D_DDIM_SEM_TIMEOUT)
/*< Semaphore acquisition NG */
#define	DdSpiDriveBranch_SEM_NG					            (D_DD_SPI | D_DDIM_SEM_NG)
/*< Abnormal Status */
#define DdSpiDriveBranch_STATUS_ABNORMAL		    (D_DD_SPI | D_DDIM_STATUS_ABNORMAL)
/*< SPI receive overrun error. */
#define DdSpiDriveBranch_RECV_OVERRUN_ERROR	(D_DD_SPI | D_DDIM_OVERRUN_DATA)
/*< SPI DMA stop status error. */
#define DdSpiDriveBranch_DMA_SS_ERROR			        (D_DD_SPI | D_DDIM_BUS_ERROR)
/*< SPI Forced stop by Dd_SPI_Stop() */
#define DdSpiDriveBranch_FORCE_STOP				        (D_DD_SPI | D_DDIM_FORCE_STOP)

#define DdSpiDriveBranch_CH_MAX			    (3)
/*< Maximum connectable slave select */
#define DdSpiDriveBranch_SS_MAX				(4)

#define DdSpiDriveBranch_SEND			        (0)
#define DdSpiDriveBranch_RECV			            (1)

#define DdSpiDriveBranch_DMA_TC_MAX		(65536)

// Interrupt Bit Location
#define DdSpiDriveBranch_INT_TXEMPTYPULSE_BIT	    (1)
#define DdSpiDriveBranch_INT_TXWMARKPULSE_BIT	    (1 << 1)
#define DdSpiDriveBranch_INT_RXWMARKPULSE_BIT	    (1 << 2)
#define DdSpiDriveBranch_INT_RXFULLPULSE_BIT	        (1 << 3)
#define DdSpiDriveBranch_INT_XFERDONEPULSE_BIT    (1 << 4)
#define DdSpiDriveBranch_INT_RXFIFOOVERFLOW_BIT  (1 << 7)
#define DdSpiDriveBranch_INT_RXTIMEOUT_BIT		         (1 << 8)
#define DdSpiDriveBranch_INT_ALL_BIT_SET		             (0x01FF)
#define DdSpiDriveBranch_INT_TX_CPU_BIT_SET	\
	(DdSpiDriveBranch_INT_TXEMPTYPULSE_BIT | DdSpiDriveBranch_INT_TXWMARKPULSE_BIT)
#define DdSpiDriveBranch_INT_TX_DMA_BIT_SET		        (DdSpiDriveBranch_INT_TX_CPU_BIT_SET)
#define DdSpiDriveBranch_INT_RX_CPU_BIT_SET	\
	(DdSpiDriveBranch_INT_RXWMARKPULSE_BIT | DdSpiDriveBranch_INT_RXFULLPULSE_BIT \
			| DdSpiDriveBranch_INT_RXFIFOOVERFLOW_BIT | DdSpiDriveBranch_INT_RXTIMEOUT_BIT)
#define DdSpiDriveBranch_INT_RX_DMA_BIT_SET		        (DdSpiDriveBranch_INT_RX_CPU_BIT_SET \
		| DdSpiDriveBranch_INT_RXTIMEOUT_BIT)
#define DdSpiDriveBranch_INT_FULL_CPU_BIT_SET	            (DdSpiDriveBranch_INT_TX_CPU_BIT_SET \
		| DdSpiDriveBranch_INT_RX_CPU_BIT_SET)
#define DdSpiDriveBranch_INT_FULL_DMA_BIT_SET	        (DdSpiDriveBranch_INT_FULL_CPU_BIT_SET \
		| DdSpiDriveBranch_INT_RXTIMEOUT_BIT)

#define DdSpiDriveBranch_DSB()                                            Dd_ARM_Dsb_Pou()

typedef struct _DdSpiSsInfo                          DdSpiSsInfo;
typedef struct _TDdSpiCtrl                             TDdSpiCtrl;
typedef struct _TDdSpiInfo                            TDdSpiInfo;

#ifdef CO_DDIM_UTILITY_USE
typedef struct _SpiDmaCountInfo                 SpiDmaCountInfo;
typedef struct _DdSpiDmaInfo                      DdSpiDmaInfo;
#endif

typedef struct _DdSpiDriveBranch                DdSpiDriveBranch;
typedef struct _DdSpiDriveBranchPrivate    DdSpiDriveBranchPrivate;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Master/Slave selection. */
typedef enum{
	/*< Type of Slave */
	DdSpiDriveBranch_TYPE_SLAVE = 0,
	/*< Type of Master */
	DdSpiDriveBranch_TYPE_MASTER
} EDdSpiType;

/* Transmit mode selection. */
typedef enum{
	/*< Mode0:Clock Polarity=0, Clock Phase=0<br>
	*Data are captured on the clock's rising edge and data is output on a falling edge. */
	DdSpiDriveBranch_MODE_0_CPOL0_CPHA0 = 0,
	/*< Mode1:Clock Polarity=0, Clock Phase=1
	*Data are captured on the clock's falling edge and data is output on a rising edge. */
	DdSpiDriveBranch_MODE_1_CPOL0_CPHA1,
	/*< Mode2:Clock Polarity=1, Clock Phase=0
	*Data are captured on clock's falling edge and data is output on a rising edge. */
	DdSpiDriveBranch_MODE_2_CPOL1_CPHA0,
	/*< Mode3:Clock Polarity=1, Clock Phase=1
	*Data are captured on clock's rising edge and data is output on a falling edge. */
	DdSpiDriveBranch_MODE_3_CPOL1_CPHA1,
} EDdSpiMode;

/* Enable signal selection. */
typedef enum{
	/*< Use CPU. (software) */
	DdSpiDriveBranch_ENABLE_SIG_CPU = 0x00,
	/*< use external enable 0. */
	DdSpiDriveBranch_ENABLE_SIG_EXT_0 = 0x02,
	/*< use external enable 1. */
	DdSpiDriveBranch_ENABLE_SIG_EXT_1 = 0x04,
	/*< use external enable 2. */
	DdSpiDriveBranch_ENABLE_SIG_EXT_2 = 0x08
} DdSpiEnableSig;

/* Bit direction selection. */
typedef enum {
	/*< LSB first */
	DdSpiDriveBranch_BIT_DIR_LSB_FIRST = 0,
	/*< MSB first */
	DdSpiDriveBranch_BIT_DIR_MSB_FIRST
} DdSpiBitDir;

/* Data length selection. */
typedef enum{
	/*< 4 bit length */
	DdSpiDriveBranch_BIT_LEN_4 = 3,
	/*< 5 bit length */
	DdSpiDriveBranch_BIT_LEN_5,
	/*< 6 bit length */
	DdSpiDriveBranch_BIT_LEN_6,
	/*< 7 bit length */
	DdSpiDriveBranch_BIT_LEN_7,
	/*< 8 bit length */
	DdSpiDriveBranch_BIT_LEN_8,
	/*< 9 bit length */
	DdSpiDriveBranch_BIT_LEN_9,
	/*< 10 bit length */
	DdSpiDriveBranch_BIT_LEN_10,
	/*< 11 bit length */
	DdSpiDriveBranch_BIT_LEN_11,
	/*< 12 bit length */
	DdSpiDriveBranch_BIT_LEN_12,
	/*< 13 bit length */
	DdSpiDriveBranch_BIT_LEN_13,
	/*< 14 bit length */
	DdSpiDriveBranch_BIT_LEN_14,
	/*< 15 bit length */
	DdSpiDriveBranch_BIT_LEN_15,
	/*< 16 bit length */
	DdSpiDriveBranch_BIT_LEN_16,
	/*< 17 bit length */
	DdSpiDriveBranch_BIT_LEN_17,
	/*< 18 bit length */
	DdSpiDriveBranch_BIT_LEN_18,
	/*< 19 bit length */
	DdSpiDriveBranch_BIT_LEN_19,
	/*< 20 bit length */
	DdSpiDriveBranch_BIT_LEN_20,
	/*< 21 bit length */
	DdSpiDriveBranch_BIT_LEN_21,
	/*< 22 bit length */
	DdSpiDriveBranch_BIT_LEN_22,
	/*< 23 bit length */
	DdSpiDriveBranch_BIT_LEN_23,
	/*< 24 bit length */
	DdSpiDriveBranch_BIT_LEN_24,
	/*< 25 bit length */
	DdSpiDriveBranch_BIT_LEN_25,
	/*< 26 bit length */
	DdSpiDriveBranch_BIT_LEN_26,
	/*< 27 bit length */
	DdSpiDriveBranch_BIT_LEN_27,
	/*< 28 bit length */
	DdSpiDriveBranch_BIT_LEN_28,
	/*< 29 bit length */
	DdSpiDriveBranch_BIT_LEN_29,
	/*< 30 bit length */
	DdSpiDriveBranch_BIT_LEN_30,
	/*< 31 bit length */
	DdSpiDriveBranch_BIT_LEN_31,
	/*< 32 bit length */
	DdSpiDriveBranch_BIT_LEN_32,
} DdSpiBitLen;

/* ssOut continuous selection. */
typedef enum {
	/*< ssOut goes inactive between successive transfers. */
	DdSpiDriveBranch_CONT_TRANS_INACT_BETWEEN = 0,
	/*< ssOut become inactive when the TX FIFO is empty. */
	DdSpiDriveBranch_CONT_TRANS_INACT_FIFO_EMPTY,
	/*< ssOut remain active even when the TX FIFO is empty. */
	DdSpiDriveBranch_CONT_TRANS_ACT_FIFO_EMPTY
} DdSpiContTrans;

typedef enum {
	DdSpiDriveBranch_DIR_SEND = 0,
	DdSpiDriveBranch_DIR_RECV,
	DdSpiDriveBranch_DIR_FULL
} EDdSpiDir;

/*
*Type is defined to Callback function pointer when complete communication.<br>
*@param [in]	ch			Channel number(0 to 2)
*@param [in] status		Complete status. (Same API return values)
*/
typedef void (*VpSpiCallback)(kuchar ch, kuint32 status);

/*
*Type is defined to Callback function pointer when ssOut/ssIn is active.<br>
*@param [in]	ch			Channel number(0 to 2)
*/
typedef void (*VpSpiSsCallback)(kuchar ch);

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Slave Select setting information. */
struct _DdSpiSsInfo{
	/*< Continuous Transfer enable. See @ref DdSpiContTrans. */
	DdSpiContTrans	contTrans;
	/*< Slave Select Output selection.<br>
	*0: Do not select slave for TX/RX<br>
	*1: Select Slave for TX/RX<br>
	*<br>
	*The maximum SSOUT is as follows.<br>
	*ch0: 4<br>
	*ch1: 4<br>
	*ch2: 1 */
	kuchar				ssout[DdSpiDriveBranch_SS_MAX];
	/*< Slave Select Polarity selection.<br>
	*sspol[0] = 0  : SSOUT/SSIN[0] is an active Low<br>
	*sspol[0] = 1  : SSOUT/SSIN[0] is an active High<br>
	*sspol[1~3] = 0: SSOUT[1~3] is an active Low<br>
	*sspol[1~3] = 1: SSOUT[1~3] is an active High */
	kuchar				sspol[DdSpiDriveBranch_SS_MAX];
};

/*SPI control data. */
struct _TDdSpiCtrl{
	/*< Master/Slave selection. */
	EDdSpiType			type;
	/*< Transmit mode. See @ref EDdSpiMode. */
	EDdSpiMode			mode;
	/*< Enable signal selection. See @ref DdSpiEnableSig. */
	DdSpiEnableSig		enableSig;
	/*< Bit direction, LSB first or MSB first. */
	DdSpiBitDir		    bitDirection;
	/*< Data length. See @ref DdSpiBitLen. */
	DdSpiBitLen		    bitLength;
	/*< Serial Clock Divisor.<br>
	*SCLK(bps) = extSclkM(SPICLK) / (2 * (clkDiv + 1)<br>
	*<br>
	*The maximum SCLK baudrate is as follows.<br>
	*ch0: 108Mbps<br>
	*ch1: 50Mbps<br>
	*ch2: 50Mbps */
	kuchar					clkDiv;
	/*< Inter-Transfer Delay enable. (Master operation only)<br>
	*0: Disable delay (full speed)<br>
	*1: Enable delay. See @ref delayVal. */
	kuchar					delayEn;
	/*< SCLK cycles for Inter-transfer delay. (Master operation only)<br>
	*The delay is (delayVal+1) SCLK cycles. */
	kuchar					delayVal;
	/*< Inhibit the RX_FIFO.<br>
	*0: Not inhibit<br>
	*1: Inhibit the SPI bus from writing to the RX FIFO */
	kuchar					rxInhibitEn;
	/*< TX FIFO Watermark value.<br>
	*FIFO size is as follows.<br>
	*ch0: 128 words<br>
	*ch1: 64 words<br>
	*ch2: 16 words */
	kuchar					fifoWmarkTx;
	/*< RX FIFO Watermark value.<br>
	*In the case of master reception, please also set fifoWmarkTx.<br>
	*FIFO size is as follows.<br>
	*ch0: 128 words<br>
	*ch1: 64 words<br>
	*ch2: 16 words */
	kuchar					fifoWmarkRx;
	/*< DMA enable.<br>
	*If set to 1, please use the Dd_SPI_Start_Xxxx_DMA() as the starting API.<br>
	*In addition, please also set to 1, if using the Dd_SPI_Start_Recv()
	*or Dd_SPI_Start_Full_Duplex() by asynchronization, when DMA is not use. */
	kuchar					dmaEn;
	/*< DMA Receive Timeout. (0 to 16,777,215)<br>
	*If the receive FIFO remains less than the RX watermark level for dmaRecvTo(+1) HCLK cycles,
	*the DMA logic will issue a dma interrupt request to the CPU.<br>
	*Please also set if using the Dd_SPI_Start_Recv() or
	*Dd_SPI_Start_Full_Duplex() by asynchronization, when DMA is not use. */
	kuint32					dmaRecvTo;
	/*< Slave Select setting information. See @ref DdSpiSsInfo */
	DdSpiSsInfo		    ssInfo;
	/*< Callback function pointer<br>
	*If pCallback was specified, Dd_SPI_Start_Xxxx() function is asynchronization.<br>
	*If pCallback was not specified, Dd_SPI_Start_Xxxx() function is synchronization. */
	VpSpiCallback			pCallback;
	/*< Enable callback when the ssOut/ssIn is active. */
	VpSpiSsCallback		pCallbackSs;
};

/* SPI send/receive data information. */
struct _TDdSpiInfo{
	/* Send data address (8bit length) */
	kuchar*				sendAddr8;
	/* Send data address (9~16bit length) */
	kushort*				sendAddr16;
	/* Send data address (17~32bit length) */
	kuint32*				sendAddr32;
	/* Receive data address (8bit length) */
	kuchar*				recvAddr8;
	/* Receive data address (9~16bit length) */
	kushort*				recvAddr16;
	/* Receive data address (17~32bit length) */
	kuint32*				recvAddr32;
	/* Number of data */
	kuint32				num;
	/* Send data position */
	kuint32				sendPos;
	/* Receive data position */
	kuint32				recvPos;
	/* Number of dummy data */
	kuint32				dummyCount;
	/* Callback function pointer when complete communication */
	VpSpiCallback		pCallback;
	/* Callback function pointer when ssOut/ssIn is active */
	VpSpiSsCallback	pCallbackSs;
	/* SPI mode (Send/Receive/Fullduplex) */
	EDdSpiDir		    spiMode;
	/* DMA Waiting Flag */
	kuchar				dmaWait;
	/* Force stop Flag */
	kuchar				forceStopFlg;
};

#ifdef CO_DDIM_UTILITY_USE
/* SPI DMA transfer count information */
struct _SpiDmaCountInfo{
	kulong	 transCount;
	kulong	 dmaCount;
};

/* SPI DMA transfer information */
struct _DdSpiDmaInfo{
	SpiDmaCountInfo		            countInfo[2];
	T_DD_HDMAC1_CTRL			hdmac1Ctrl;
	kuint32						count;
	kuint32						index;
	kuint32						index2;
	kuint32						result;
	kuchar						dmaCh;
};
#endif

struct _DdSpiDriveBranch
{
	KObject parent;
};

KConstType                  dd_spi_drive_branch_get_type(void);
DdSpiDriveBranch*    dd_spi_drive_branch_new(void);

/*
*Start full-duplex communication.
*@param [in]	ch	Channel number(0 to 2)
*@retval		D_DDIM_OK						: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR		: Input parameter error
*@remarks	If pCallback was specified, this API is asynchronization.<br>
*			If pCallback was not specified, this API is synchronization.
*			If asynchronization receiving, please set the TDdSpiCtrl.dmaEn and TDdSpiCtrl.dmaRecvTo.
*/
kuint32                         dd_spi_drive_branch_start_full_duplex(DdSpiDriveBranch* self, kuchar ch);

/*
*Start receiving data.
*@param [in]	ch	Channel number(0 to 2)
*@retval		D_DDIM_OK						: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR		: Input parameter error
*@retval		D_DD_SPI_RECV_OVERRUN_ERROR		: Overrun error
*@retval		D_DD_SPI_FORCE_STOP				: Forced stop by Dd_SPI_Stop()
*@remarks	If pCallback was specified, this API is asynchronization.<br>
*			If pCallback was not specified, this API is synchronization.<br>
*			If asynchronization receiving, please set the TDdSpiCtrl.dmaEn and TDdSpiCtrl.dmaRecvTo.
*/
kuint32                         dd_spi_drive_branch_start_recv(DdSpiDriveBranch* self, kuchar ch);

/*
*Start sending data.
*@param [in]	ch	Channel number(0 to 2)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_SPI_FORCE_STOP			: Forced stop by Dd_SPI_Stop()
*@remarks	If pCallback was specified, this API is asynchronization.<br>
*			If pCallback was not specified, this API is synchronization.
*/
kuint32                         dd_spi_drive_branch_start_send(DdSpiDriveBranch* self, kuchar ch);

/*
 * 获取、设置私有方法、属性
 */
void                              dd_spi_drive_branch_get_end_process(DdSpiDriveBranch* self, kuchar ch);
void                              dd_spi_drive_branch_get_send_data(DdSpiDriveBranch* self, kuchar ch);
void                              dd_spi_drive_branch_get_write_dummy_count(DdSpiDriveBranch* self, kuchar ch);
kuint32                         dd_spi_drive_branch_get_check_stopping_conditions(DdSpiDriveBranch* self, kuchar ch);

TDdSpiInfo                   dd_spi_drive_branch_get_spi_info(DdSpiDriveBranch* self, kuchar ch);

void                              dd_spi_drive_branch_set_spi_info_pcallback(DdSpiDriveBranch* self,
		                                   kuchar ch, VpSpiCallback pCallback);
void                              dd_spi_drive_branch_set_spi_info_pcallback_ss(DdSpiDriveBranch* self,
		                                   kuchar ch, VpSpiSsCallback pCallbackSs);
void                              dd_spi_drive_branch_set_spi_info_send_addr32(DdSpiDriveBranch* self,
		                                   kuchar ch, kuint32* sendAddr32);
void                              dd_spi_drive_branch_set_spi_info_send_addr16(DdSpiDriveBranch* self,
		                                   kuchar ch, kushort* sendAddr16);
void                              dd_spi_drive_branch_set_spi_info_send_addr8(DdSpiDriveBranch* self,
		                                   kuchar ch, kuchar* sendAddr8);
void                              dd_spi_drive_branch_set_spi_info_send_pos(DdSpiDriveBranch* self,
		                                   kuchar ch, kuint32 sendPos);
void                              dd_spi_drive_branch_set_spi_info_recv_addr32(DdSpiDriveBranch* self,
		                                   kuchar ch, kuint32* recvAddr32);
void                              dd_spi_drive_branch_set_spi_info_recv_addr16(DdSpiDriveBranch* self,
		                                   kuchar ch, kushort* recvAddr16);
void                              dd_spi_drive_branch_set_spi_info_recv_addr8(DdSpiDriveBranch* self,
		                                   kuchar ch, kuchar* recvAddr8);
void                              dd_spi_drive_branch_set_spi_info_recv_pos(DdSpiDriveBranch* self,
		                                   kuchar ch, kuint32 recvPos);
void                              dd_spi_drive_branch_set_spi_info_add_recv_pos(DdSpiDriveBranch* self,
		                                   kuchar ch, kuint32 recvPos);
void                              dd_spi_drive_branch_set_spi_info_num(DdSpiDriveBranch* self, kuchar ch,
		                                   kuint32 num);
void                              dd_spi_drive_branch_set_spi_info_dummy_count(DdSpiDriveBranch* self,
		                                   kuchar ch, kuint32 dummyCount);
void                              dd_spi_drive_branch_set_spi_info_force_stop_flg(DdSpiDriveBranch* self,
		                                   kuchar ch, kuchar forceStopFlg);
void                              dd_spi_drive_branch_set_spi_info_dma_wait(DdSpiDriveBranch* self,
		                                   kuchar ch, kuchar dmaWait);
void                              dd_spi_drive_branch_set_spi_info_spi_mode(DdSpiDriveBranch* self,
		                                   kuchar ch, EDdSpiDir spiMode);

#endif /* __DD_SPI_DRIVE_BRANCH_H__ */
