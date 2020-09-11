/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 王顺
*@brief : DdCsioDma
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __DD_CSIO_DMA_H__
#define __DD_CSIO_DMA_H__


#include <klib.h>
#include"ddcsio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_CSIO_DMA                  (dd_csio_dma_get_type())
#define DD_CSIO_DMA(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdCsioDma))
#define DD_IS_CSIO_DMA(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_CSIO_DMA))

#ifdef CO_DDIM_UTILITY_USE
typedef struct _DdCsioSendCtrl DdCsioSendCtrl;
#endif


typedef struct _DdCsioDma DdCsioDma;
typedef struct _DdCsioDmaPrivate DdCsioDmaPrivate;

//T_DD_CSIO_CAL改为DdCsioCal，将此结构体的成员全部放入类结构体中。
struct _DdCsioDma
{
	KObject parent;
	kulong inFreq; /**< Input  frequency */
	kulong calFreq; /**< Output frequency (result of calculate) */
};


KConstType		dd_csio_dma_get_type(void);
DdCsioDma*	dd_csio_dma_new(void);
/**
 Dividing frequency is requested from the clock frequency specified by the argument.
 @param [in]	calTbl	SIO calculate information. See @ref DdCsioDma.
 @retval		D_DDIM_OK					: OK
 @retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
 */
kint32				dd_csio_dma_calculate(DdCsioDma* const calTbl);

/**
It is a function started when the CSIO transmission is completed.<br>
The callback function for the transmission registered by @ref dd_csio_ctrl is started.
@param [in]	ch	Channel number(0 to 7)
*/
void				dd_csio_dma_int_handler_tx(DdCsioDma *self,  kuchar ch );

/**
It is a function started when the CSIO reception is completed.<br>
It is notified to start the callback function for the reception, and to have received it.
@param [in]	ch	Channel number(0 to 7)
*/
void				dd_csio_dma_int_handler_rx(DdCsioDma *self,  kuchar ch );

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
/** @name Utility Functions
 @{*/

/**
 Send data by CSIO.
 @param [in]	ch				Channel number(0 to 7)
 @param [in]	csioSendCtrl	CSIO Control data. See @ref DdCsioSendCtrl.
 @param [in]	sendAddr		Send data address
 @param [in]	num				Number of data
 @retval		D_DDIM_OK					: OK
 @retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
 @retval		D_DD_CSIO_EXT_LOCK_NG		: Lock error (System using designated channel number)
 */
kint32				dd_csio_dma_send(DdCsioDma *self, kuchar ch, DdCsioSendCtrl const* const csioSendCtrl,
							void* sendAddr, kuint32 num);
//---------------------------- colabo section ----------------------------
/**
Start sending data via DMA and CSIO FIFO.
@param [in]	csioCh		CSIO channel number(0 to 7)
@param [in]	dmaCh		DMA channel number(0 to 7)
@param [in]	dmaMode	DMA mode
						<ul><li>@ref C_CSIO_SEND_DMA_MODE_DEMAND</ul>
@retval		D_DDIM_OK					: OK
@retval		C_CSIO_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_CSIO_DMA_SS_ERROR		: DMA stop status error
@retval		C_CSIO_FORCE_STOP		: Forced stop by dd_csio_stop(NULL, )
@retval		C_CSIO_TIMEOUT			: CSIO Time Out
*/
kint32				dd_csio_dma_start_send_dma(DdCsioDma *self, kuchar csioCh, kuchar dmaCh, kuchar dmaMode);

/**
Start receiving data via DMA and CSIO FIFO.
@param [in]	csioCh		CSIO channel number(0 to 7)
@param [in]	dmaCh		DMA channel number(0 to 7)
@param [in]	dmaMode	DMA mode
						<ul><li>@ref C_CSIO_RECV_DMA_MODE_DEMAND</ul>
@retval		D_DDIM_OK						: OK
@retval		C_CSIO_INPUT_PARAM_ERROR		: Input parameter error
@retval		C_CSIO_RECV_OVERRUN_ERROR	: Overrun error
@retval		C_CSIO_DMA_SS_ERROR			: DMA stop status error
*/
kint32				dd_csio_dma_start_recv_dma(DdCsioDma *self, kuchar csioCh, kuchar dmaCh, kuchar dmaMode );

/**
Start full duplex communication via DMA and CSIO FIFO.
@param [in]	csioCh			CSIO channel number(0 to 7)
@param [in]	dmaChSend		DMA channel number(for send)(0 to 7)
							<ul><li>@ref C_CSIO_SEND_DMA_MODE_DEMAND</ul>
@param [in]	dmaChRecv		DMA channel number(for recive)(0 to 7)
							<ul><li>@ref C_CSIO_RECV_DMA_MODE_DEMAND</ul>
@retval		D_DDIM_OK						: OK
@retval		C_CSIO_INPUT_PARAM_ERROR		: Input parameter error
@remarks
			- This API is asynchronization.
			- fifoCtrl and pcallback in DdCsio must always specify.
 */
kint32				dd_csio_dma_start_full_duplex_dma(DdCsioDma *self, kuchar csioCh, kuchar dmaChSend,
							kuchar dmaChRecv);
/*@}*/
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DD_CSIO_DMA_H__ */
