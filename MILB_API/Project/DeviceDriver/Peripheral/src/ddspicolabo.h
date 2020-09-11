/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-05
* @author    : 肖泽友
* @brief        :SPI(Serial Peripheral Interface) driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、colabo section
*
*@version   :1.0.0
*
*/

#ifndef __DD_SPI_COLABO_H__
#define __DD_SPI_COLABO_H__

#include <klib.h>
#include "ddspidrive.h"

#define DD_TYPE_SPI_COLABO              (dd_spi_colabo_get_type())
#define DD_SPI_COLABO(obj)                K_TYPE_CHECK_INSTANCE_CAST(obj, DdSpiColabo)
#define DD_IS_SPI_COLABO(obj)           K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_SPI_COLABO)

typedef struct _DdSpiColabo                  DdSpiColabo;
typedef struct _DdSpiColaboPrivate     DdSpiColaboPrivate;

struct _DdSpiColabo
{
	KObject parent;
};

KConstType                    dd_spi_colabo_get_type(void);
DdSpiColabo*                dd_spi_colabo_get(void);

#ifdef CO_DDIM_UTILITY_USE
/*
*Start sending data via DMA and SPI FIFO.
*@param [in]	spiCh		SPI channel number(0 to 2)
*@param [in]	dmaCh		DMA channel number(0 to 7)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_SPI_DMA_SS_ERROR		: DMA stop status error
*@retval		D_DD_SPI_FORCE_STOP			: Forced stop by Dd_SPI_Stop()
*/
kint32                              dd_spi_colabo_start_send_dma(DdSpiColabo* self, kuchar spiCh, kuchar dmaCh);

/*
*Start receiving data via DMA and SPI FIFO.
*@param [in]	spiCh		SPI channel number(0 to 2)
*@param [in]	dmaCh		DMA channel number(0 to 7)
*@retval		D_DDIM_OK						: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR		: Input parameter error
*@retval		D_DD_SPI_RECV_OVERRUN_ERROR		: Overrun error
*@retval		D_DD_SPI_DMA_SS_ERROR			: DMA stop status error
*/
kint32                              dd_spi_colabo_start_recv_dma(DdSpiColabo* self, kuchar spiCh, kuchar dmaCh);

/*
*Start full duplex communication via DMA and SPI FIFO.
*@param [in]	spiCh			SPI channel number(0 to 2)
*@param [in]	dmaChSend		DMA channel number(for send)(0 to 7)
*@param [in]	dmaChRecv		DMA channel number(for recive)(0 to 7)
*@retval		D_DDIM_OK						: OK
@retval		D_DD_SPI_INPUT_PARAM_ERROR		: Input parameter error
 */
kint32                              dd_spi_colabo_start_full_duplex_dma(DdSpiColabo* self, kuchar spiCh,
		                                      kuchar dmaChSend, kuchar dmaChRecv);

/*@}*/
#endif

/*
 * 获取私有变量
 */
DdSpiDmaInfo                dd_spi_colabo_get_dma_info(DdSpiColabo* self, kuchar chA, kuchar chB);

#endif /* __DD_SPI_COLABO_H__ */
