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


#include "ddcsiocommon.h"
#include "ddcsio.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdCsioCommon, dd_csio_common);

#define DD_CSIO_COMMON_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdCsioCommonPrivate, DD_TYPE_CSIO_COMMON))

#define C_CSIO_WAIT_COUNT		(0x000FFFFF)	// Wait time > 566ms
													//   (AHBCLK(min)   / (BGR(max) +1)=baudrate(min)
													//   (66.7*1000000) / (32767    +1)=2036
													//   (1/2036)*9(bit length(max))*128(word(FIFO max))=566ms


struct _DdCsioCommonPrivate
{
#ifdef CO_DDIM_UTILITY_USE
/* CSIO HDMAC channel information. */
volatile kuchar gddCsioDmaChInfo[DdHdmac1_CH_NUM_MAX];
#endif
};


/* CSIO send/receive data information. */
volatile DdCsioInfo gddCsioInfo[DdUart_D_DD_USIO_CH_NUM_MAX];
#ifdef CO_DDIM_UTILITY_USE
/* CSIO DMA transfer information */
volatile DdCsioDmaInfo gddCsioDmaInfo[DdUart_D_DD_USIO_CH_NUM_MAX][2];
/* CSIO HDMAC channel information. */
//volatile kuchar gddCsioDmaChInfo[DdHdmac1_CH_NUM_MAX];
#endif

/**
DECLS
*/

/**
IMPL
*/
static void dd_csio_common_constructor(DdCsioCommon *self)
{
//	DdCsioCommonPrivate *priv = DD_CSIO_COMMON_GET_PRIVATE(self);
}

static void dd_csio_common_destructor(DdCsioCommon *self)
{
//	DdCsioCommonPrivate *priv = DD_CSIO_COMMON_GET_PRIVATE(self);
}
/**
PUBLIC
*/
void dd_csio_common_end (DdCsioCommon *self, kuchar ch)
{
	// Disable send and receive permission
//	ioUsio.csio[ch].smr.bit.soe = 0;
	ioUsio.csio[ch].scr.bit.rxe = 0;
	ioUsio.csio[ch].scr.bit.txe = 0;

	// Disable interrupt
	ioUsio.csio[ch].scr.bit.tie = 0;
	ioUsio.csio[ch].scr.bit.tbie = 0;
	ioUsio.csio[ch].fcr.bit.ftie = 0;
	ioUsio.csio[ch].scr.bit.rie = 0;
	ioUsio.csio[ch].fcr.bit.friie = 0;

	// Clear buffer overrun error
	ioUsio.csio[ch].ssr.byte |= C_CSIO_SSR_REC_BIT;

	// FIFO reset
//	ioUsio.csio[ch].fcr.hword |= 0x000C;

	// Disable full duplex
	gddCsioInfo[ch].fullDuplex = 0;

	// Disable DMA wait
	if (gddCsioInfo[ch].dmaWait == 1) {
		dd_hdmac1_stop(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_SEND].dmaCh);
		dd_hdmac1_close(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_SEND].dmaCh);
		dd_hdmac1_stop(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_RECV].dmaCh);
		dd_hdmac1_close(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_RECV].dmaCh);
	}
	gddCsioInfo[ch].dmaWait = 0;
	gddCsioInfo[ch].forceStopFlg = 0;
	DdCsioCommon_DD_CSIO_DSB();
}

/**
 * @brief	Interrupt Handler of CSIO full duplex.
 * @param	void
 * @return	void
 */
void dd_csio_common_int_handler_full_duplex(DdCsioCommon *self, kuchar ch )
{
	kint32 ret;
	kint32 sendCnt = 0;
	kint32 recvFifoNum = 0;

	// Check for receive buffer overrun error
	if (ioUsio.csio[ch].ssr.bit.__ore == 1) {
		// Clear buffer overrun error
		ioUsio.csio[ch].ssr.byte |= C_CSIO_SSR_REC_BIT;

		// End csio communication
		dd_csio_common_end(dd_csio_common_get(), ch);

		if (gddCsioInfo[ch].pcallback != NULL) {
			((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_RECV_OVERRUN_ERROR);
		}
		return;
	}

	// Select receive fifo
	if (ioUsio.csio[ch].fcr.bit.fsel == 0) {
		recvFifoNum = 1;
	}

	// Receive data
	if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		while (ioUsio.csio[ch].fbyte.byte[recvFifoNum] > 0) {
			*(gddCsioInfo[ch].recvAddr16 + gddCsioInfo[ch].recvPos) = ioUsio.csio[ch].dr.hword;
			gddCsioInfo[ch].recvPos++;
		}
	} else {
		while (ioUsio.csio[ch].fbyte.byte[recvFifoNum] > 0) {
			*(gddCsioInfo[ch].recvAddr8 + gddCsioInfo[ch].recvPos) = ioUsio.csio[ch].dr.byte[0];
			gddCsioInfo[ch].recvPos++;
		}
	}

	// Receive data count check
	if (gddCsioInfo[ch].recvPos < gddCsioInfo[ch].sendPos) {
		gddCsioInfo[ch].recvWait++;
		if (gddCsioInfo[ch].recvWait < 100) {
			return;
		}
	}

	// Send data
	if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			ioUsio.csio[ch].dr.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
			DdCsioCommon_DD_CSIO_DSB();
			gddCsioInfo[ch].sendPos++;
			sendCnt++;

			if (ioUsio.csio[ch].fcr.bit.fdrq == 0) {
				//FIFO is full (0:full, 1:empty)
				break;
			} else {
				// FIFO is not full
				continue;
			}
		}
	} else {
		while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			ioUsio.csio[ch].dr.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
			DdCsioCommon_DD_CSIO_DSB();
			gddCsioInfo[ch].sendPos++;
			sendCnt++;

			if (ioUsio.csio[ch].fcr.bit.fdrq == 0) {
				//FIFO is full (0:full, 1:empty)
				break;
			} else {
				// FIFO is not full
				continue;
			}
		}
	}

	if (sendCnt > 0) {		// Send data was written?
		ioUsio.csio[ch].fcr.bit.fdrq = 0;
		DdCsioCommon_DD_CSIO_DSB();
	} else {
		ioUsio.csio[ch].fcr.bit.ftie = 0;
		ioUsio.csio[ch].scr.bit.tbie = 1;
	}

	if (ioUsio.csio[ch].ssr.bit.__tbi == 0) {
		// bus not idle
		return;
	}

	// End csio communication
	dd_csio_common_end(dd_csio_common_get(), ch);

	// Check reveice complate
	if (gddCsioInfo[ch].recvPos < gddCsioInfo[ch].num) {
		// remain data exist
		ret = C_CSIO_RECV_OVERRUN_ERROR;
	} else {
		ret = C_CSIO_NORMAL_COMPLETE;
	}

	// All data send and receive complate
	if (gddCsioInfo[ch].pcallback != NULL) {
		((void (*)()) gddCsioInfo[ch].pcallback)(ret);
	}
}

kint32 dd_csio_common_check_stopping_conditions(DdCsioCommon *self, kuchar ch, kuint32 waitCnt)
{
	if (ioUsio.csio[ch].scr.bit.ms == DdCsio_DD_CSIO_TYPE_MASTER) {
		if (waitCnt >= C_CSIO_WAIT_COUNT) {
			dd_csio_common_end(dd_csio_common_get(), ch);
			Ddim_Print(("CSIO Time Out err.\n"));
			return C_CSIO_TIMEOUT;
		}
	}
	if (gddCsioInfo[ch].forceStopFlg == 1) {
		dd_csio_common_end(dd_csio_common_get(), ch);
		return C_CSIO_FORCE_STOP;
	}

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
kint32 dd_csio_common_start_dma(DdCsioCommon *self, kuchar dmaCh, Hdmac1Ctrl* hdmac1Ctrl)
{
	kint32 ret;

	ret = dd_hdmac1_ctrl_common(dd_hdmac1_get(), dmaCh, hdmac1Ctrl);
	if (ret == D_DDIM_OK) {
		ret = dd_hdmac1_start_async(dd_hdmac1_get(), dmaCh);
		if (ret != D_DDIM_OK) {
			dd_hdmac1_close(dd_hdmac1_get(), dmaCh);
			Ddim_Print(("Dd_HDMAC1_Start_Async () error. ret=0x%x\n", ret));
			return ret;
		}
	} else {
		dd_hdmac1_close(dd_hdmac1_get(), dmaCh);
		Ddim_Print(("Dd_HDMAC1_Ctrl_Common () error. ret=0x%x\n", ret));
		return ret;
	}

	return ret;
}

void dd_csio_common_send_dma_callback( kuchar dmaCh, kuint16* const status )
{
	kint32 ret;
	kuint32 index;
	kuchar csioCh;
	DdCsioCommonPrivate *priv = DD_CSIO_COMMON_GET_PRIVATE(dd_csio_common_get());

	csioCh = priv->gddCsioDmaChInfo[dmaCh];
	index = gddCsioDmaInfo[csioCh][C_CSIO_SEND].index;

	if (*status == DdHdmac1_SS_NORMAL_END) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].index2++;

		if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].index2
				< gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].dmaCount) {
			ioUsio.csio[csioCh].fcr.bit.ftie = 0;
			ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
			DdCsioCommon_DD_CSIO_DSB();

			// Resume DMA
			ret = dd_hdmac1_resume(dd_hdmac1_get(), dmaCh);

			// Resume DMA by CSIO FIFO interrupt.
			ioUsio.csio[csioCh].fcr.bit.ftie = 1;
			DdCsioCommon_DD_CSIO_DSB();
			return;
		}

		gddCsioDmaInfo[csioCh][C_CSIO_SEND].index++;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].index2 = 0;

		if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].index < gddCsioDmaInfo[csioCh][C_CSIO_SEND].count) {
			index = gddCsioDmaInfo[csioCh][C_CSIO_SEND].index;

			// Update source address
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.srcAddr =
					dd_hdmac1_get_src_addr(dd_hdmac1_get(), dmaCh);
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configA.bit.tc =
					gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].transCount - 1;
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configA.bit.bt =
					gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].beatType;

			if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].dmaCount > 1) {
				// Enable reload counter
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_ENABLE;
			} else {
				// Disable reload counter
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_DISABLE;
			}

			ioUsio.csio[csioCh].fcr.bit.ftie = 0;
			ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
			DdCsioCommon_DD_CSIO_DSB();

			// Start DMA
			ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
							(Hdmac1Ctrl*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl);

			if (ret == D_DDIM_OK) {
				// Start DMA by CSIO FIFO interrupt.
				ioUsio.csio[csioCh].fcr.bit.ftie = 1;
				DdCsioCommon_DD_CSIO_DSB();
				return;
			} else {
				// Set result
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].result = ret;
			}
		} else {	// DMA normal complete
			// Set result
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].result = C_CSIO_NORMAL_COMPLETE;
		}
	} else {	// DMA status error
		Ddim_Print(("Dd_HDMAC1_Wait_End () stop status error. status=%d\n", *status));

		// Set result
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].result = C_CSIO_DMA_SS_ERROR;
	}

	// End DMA transfer process.
	ioUsio.csio[csioCh].fcr.bit.ftie = 0;
	DdCsioCommon_DD_CSIO_DSB();

	if (!gddCsioInfo[csioCh].fullDuplex) {
		if (ioUsio.csio[csioCh].ssr.bit.__tbi == 0) {
			// Wait bus idle interrupt
			gddCsioInfo[csioCh].dmaWait = 2;
			// Enable CSIO interrupt
#ifdef CO_PT_ENABLE
			dd_gic_ctrl(NULL, (DdGicIntid)(DdGic_INTID_UART_CH0_TRANSMISSION_INT + csioCh), 1, -1, -1);
#else
			ddim_user_custom_enableInt(NULL, (DdimUserCustom_INTID)(DdGic_INTID_UART_CH0_TRANSMISSION_INT + csioCh),
					(DdimUserCustom_INTLV)C_PRI14);
#endif
			ioUsio.csio[csioCh].scr.bit.tbie = 1;
			DdCsioCommon_DD_CSIO_DSB();
		} else {
			dd_csio_common_end(dd_csio_common_get(), csioCh);
			dd_hdmac1_close(dd_hdmac1_get(), dmaCh);

			if (gddCsioInfo[csioCh].pcallback != NULL) {
				((void (*)()) gddCsioInfo[csioCh].pcallback)(gddCsioDmaInfo[csioCh][C_CSIO_SEND].result);
			}
		}
	}
}


void dd_csio_common_recv_dma_callback( kuchar dmaCh, kuint16* const status )
{
	kint32 ret;
	kuint32 index;
	kuchar csioCh;
	kuchar sendFifoNum = 0;
	kuchar recvFifoNum = 1;
	DdCsioCommonPrivate *priv = DD_CSIO_COMMON_GET_PRIVATE(dd_csio_common_get());

	csioCh = priv->gddCsioDmaChInfo[dmaCh];
	index = gddCsioDmaInfo[csioCh][C_CSIO_RECV].index;

	// Set send/recv fifo
	if (ioUsio.csio[csioCh].fcr.bit.fsel == 1) {
		sendFifoNum = 1;
		recvFifoNum = 0;
	}

	if (*status == DdHdmac1_SS_NORMAL_END) {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2++;

		if (ioUsio.csio[csioCh].scr.bit.ms == 0) {	// Master receiving
			if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2
					< gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount) {
				ioUsio.csio[csioCh].scr.bit.rie = 0;
				DdCsioCommon_DD_CSIO_DSB();

				// Resume DMA
				ret = dd_hdmac1_resume(dd_hdmac1_get(), dmaCh);

				// Update fbyte
				ioUsio.csio[csioCh].fbyte.byte[sendFifoNum] =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].sFbyte;

				// Resume DMA by CSIO FIFO interrupt.
				if (!gddCsioInfo[csioCh].fullDuplex) {
					ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
				}
				ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
				DdCsioCommon_DD_CSIO_DSB();
				return;
			}

			gddCsioDmaInfo[csioCh][C_CSIO_RECV].index++;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2 = 0;

			if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].index < gddCsioDmaInfo[csioCh][C_CSIO_RECV].count) {
				index = gddCsioDmaInfo[csioCh][C_CSIO_RECV].index;

				ioUsio.csio[csioCh].scr.bit.rie = 0;// Disable receive interrupt
				if (!gddCsioInfo[csioCh].fullDuplex) {
					ioUsio.csio[csioCh].scr.bit.rxe = 0;// Disable receive permission
					ioUsio.csio[csioCh].fcr.bit.fe1 = 0;		// Disable FIFO1
					ioUsio.csio[csioCh].fcr.bit.fe2 = 0;		// Disable FIFO2
					ioUsio.csio[csioCh].scr.bit.txe = 0;// Disable transmit permission
				}
				DdCsioCommon_DD_CSIO_DSB();

				// Update destination address
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dstAddr =
						dd_hdmac1_get_dst_addr(dd_hdmac1_get(), dmaCh);
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.tc =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].transCount - 1;
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.bt =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].beatType;

				if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
					// Enable reload counter
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_ENABLE;
				} else {
					// Disable reload counter
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_DISABLE;
				}

				// Start DMA
				ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
								(Hdmac1Ctrl*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl);

				if (ret == D_DDIM_OK) {
					// Start DMA by CSIO FIFO interrupt.
					if (!gddCsioInfo[csioCh].fullDuplex) {
						ioUsio.csio[csioCh].fbyte.byte[recvFifoNum] =
								gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].rFbyte;
						ioUsio.csio[csioCh].fbyte.byte[sendFifoNum] =
								gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].sFbyte;

						ioUsio.csio[csioCh].fcr.bit.fe1 = 1;	// Enable FIFO1
						ioUsio.csio[csioCh].fcr.bit.fe2 = 1;	// Enable FIFO2

						// Start DMA by CSIO FIFO interrupt.
						ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
					}
					ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt

					if (!gddCsioInfo[csioCh].fullDuplex) {
						ioUsio.csio[csioCh].scr.bit.rxe = 1;// Enable receive permission
						ioUsio.csio[csioCh].scr.bit.txe = 1;// Enable transmit permission(Start SCK output)
					}
					DdCsioCommon_DD_CSIO_DSB();
					return;
				} else {
					// Set result
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].result = ret;
				}
			} else {	// DMA normal complete
				// Set result
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].result = C_CSIO_NORMAL_COMPLETE;
			}
		} else {	// Slave receiving
			if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2
					< gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount) {
				ioUsio.csio[csioCh].scr.bit.rie = 0;
				DdCsioCommon_DD_CSIO_DSB();

				// Resume DMA
				ret = dd_hdmac1_resume(dd_hdmac1_get(), dmaCh);

				// Resume DMA by CSIO FIFO interrupt.
				ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
				DdCsioCommon_DD_CSIO_DSB();
				return;
			}

			gddCsioDmaInfo[csioCh][C_CSIO_RECV].index++;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2 = 0;

			if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].index < gddCsioDmaInfo[csioCh][C_CSIO_RECV].count) {
				index = gddCsioDmaInfo[csioCh][C_CSIO_RECV].index;

				// Update destination address
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dstAddr =
						dd_hdmac1_get_dst_addr(dd_hdmac1_get(), dmaCh);

				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.tc =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].transCount - 1;
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.bt =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].beatType;

				if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
					// Enable reload counter
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_ENABLE;
				} else {
					// Disable reload counter
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_DISABLE;
				}

				ioUsio.csio[csioCh].scr.bit.rie = 0;		// Disable receive interrupt

				// Start DMA
				ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
								(Hdmac1Ctrl*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl);

				if (ret == D_DDIM_OK) {
					// Start DMA by CSIO FIFO interrupt.
					ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
					DdCsioCommon_DD_CSIO_DSB();
					return;
				} else {
					// Set result
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].result = ret;
				}
			} else {	// DMA normal complete
				// Set result
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].result = C_CSIO_NORMAL_COMPLETE;
			}
		}
	} else {	// DMA status error
		Ddim_Print(("Dd_HDMAC1_Wait_End () stop status error. status=%d\n", *status));

		// Set result
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].result = C_CSIO_DMA_SS_ERROR;
	}

	// Check for buffer overrun error
	if (ioUsio.csio[csioCh].ssr.bit.__ore == 1) {
		// Clear buffer overrun error
		ioUsio.csio[csioCh].ssr.byte |= C_CSIO_SSR_REC_BIT;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].result = C_CSIO_RECV_OVERRUN_ERROR;
	}

	// End DMA transfer process.
	ioUsio.csio[csioCh].fcr.bit.fe1 = 0;
	ioUsio.csio[csioCh].fcr.bit.fe2 = 0;
	DdCsioCommon_DD_CSIO_DSB();

	dd_csio_common_end(dd_csio_common_get(), csioCh);
	dd_hdmac1_close(dd_hdmac1_get(), dmaCh);

	if (gddCsioInfo[csioCh].pcallback != NULL) {
		((void (*)()) gddCsioInfo[csioCh].pcallback)(gddCsioDmaInfo[csioCh][C_CSIO_RECV].result);
	}
}
#endif

#ifdef CO_DDIM_UTILITY_USE
kuchar dd_csio_common_get_gdd_csio_dma_ch_info(DdCsioCommon *self, kint32 num)
{
	DdCsioCommonPrivate *priv = DD_CSIO_COMMON_GET_PRIVATE(self);
    return priv->gddCsioDmaChInfo[num];
}

void	dd_csio_common_set_gdd_csio_dma_ch_info(DdCsioCommon *self, kuchar gddCsioDmaChInfo,kint32 num)
{
	DdCsioCommonPrivate *priv = DD_CSIO_COMMON_GET_PRIVATE(self);
	priv->gddCsioDmaChInfo[num] = gddCsioDmaChInfo;
}
#endif

DdCsioCommon* dd_csio_common_get(void)
{
	static DdCsioCommon* self = NULL;

	if (!self) {
		self = k_object_new_with_private(DD_TYPE_CSIO_COMMON, sizeof(DdCsioCommonPrivate));
	}

	return self;
}
