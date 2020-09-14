/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 王顺
*@brief : DdCsioCommon
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __DD_CSIO_COMMON_H__
#define __DD_CSIO_COMMON_H__


#include <klib.h>
#include <string.h>
#include "uart_csio.h"
#include "dduart.h"
#include "ddhdmac1.h"
#include "ddtop.h"
#include "ddgic.h"
#include "ddimusercustom.h"
#include "ddarm.h"
#include "peripheral.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_CSIO_COMMON                  (dd_csio_common_get_type())
#define DD_CSIO_COMMON(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdCsioCommon))
#define DD_IS_CSIO_COMMON(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_CSIO_COMMON))

#define C_CSIO_SEND									(0)
#define C_CSIO_RECV									(1)
// Bit Location
#define C_CSIO_SSR_REC_BIT						(1 << 7)		/**< Bit Location of REC on SSR */
#define DdCsioCommon_DD_CSIO_DSB() DD_ARM_DSB_POU()


typedef struct _DdCsioInfo DdCsioInfo;
#ifdef CO_DDIM_UTILITY_USE
typedef struct _DdCsioDmaCountInfo DdCsioDmaCountInfo;
typedef struct _DdCsioDmaInfo DdCsioDmaInfo;
#endif

/* CSIO send/receive data information. */
struct _DdCsioInfo
{
	kuchar * sendAddr8; /* Send data address (8bit length) */
	kuint16 * sendAddr16; /* Send data address (9bit length) */
	kuchar * recvAddr8; /* Receive data address (8bit length) */
	kuint16 * recvAddr16; /* Receive data address (9bit length) */
	kuint32 num; /* Number of data */
	kuint32 sendPos; /* Send data position */
	kuint32 recvPos; /* Receive data position */
	VpCallbackFunc pcallback; /* Callback function pointer */
	kuint32 recvWait; /* Wait count of recive data */
	kuchar fullDuplex; /* full duplex enable bit */
	kuchar dmaWait; /* DMA Waiting Flag */
	kuchar forceStopFlg; /* Force stop Flag */
};

#ifdef CO_DDIM_UTILITY_USE
/* CSIO DMA transfer count information */
struct _DdCsioDmaCountInfo
{
	kulong transCount;
	kulong dmaCount;
	kuint16 beatType;
	kuint16 rFbyte;
	kuint16 sFbyte;
};

/* CSIO DMA transfer information */
struct _DdCsioDmaInfo
{
	DdCsioDmaCountInfo countInfo[3];
	Hdmac1Ctrl hdmac1Ctrl;
	kuint32 count;
	kuint32 index;
	kuint32 index2;
	kint32 result;
	kuchar dmaCh;
};
#endif


typedef struct _DdCsioCommon DdCsioCommon;
typedef struct _DdCsioCommonPrivate DdCsioCommonPrivate;

struct _DdCsioCommon
{
	KObject parent;
};


extern volatile DdCsioInfo gddCsioInfo[DdUart_D_DD_USIO_CH_NUM_MAX];
#ifdef CO_DDIM_UTILITY_USE
/* CSIO DMA transfer information */
extern volatile DdCsioDmaInfo gddCsioDmaInfo[DdUart_D_DD_USIO_CH_NUM_MAX][2];
/* CSIO HDMAC channel information. */
//extern volatile kuchar gddCsioDmaChInfo[DdHdmac1_CH_NUM_MAX];
#endif


KConstType				dd_csio_common_get_type(void);
DdCsioCommon*	dd_csio_common_get(void);
void						dd_csio_common_end (DdCsioCommon *self, kuchar ch);
void						dd_csio_common_int_handler_full_duplex(DdCsioCommon *self, kuchar ch );
kint32						dd_csio_common_check_stopping_conditions(DdCsioCommon *self, kuchar ch, kuint32 waitCnt);
#ifdef CO_DDIM_UTILITY_USE
kint32						dd_csio_common_start_dma(DdCsioCommon *self, kuchar dmaCh, Hdmac1Ctrl* hdmac1Ctrl);
void						dd_csio_common_send_dma_callback( kuchar dmaCh, kuint16* const status );
void						dd_csio_common_recv_dma_callback( kuchar dmaCh, kuint16* const status );
#endif
#ifdef CO_DDIM_UTILITY_USE
kuchar 					dd_csio_common_get_gdd_csio_dma_ch_info(DdCsioCommon *self, kint32 num);
void						dd_csio_common_set_gdd_csio_dma_ch_info(DdCsioCommon *self, kuchar gddCsioDmaChInfo,
									kint32 num);
#endif

#ifdef __cplusplus
}
#endif

#endif /* DD_CSIO2_H_ */
