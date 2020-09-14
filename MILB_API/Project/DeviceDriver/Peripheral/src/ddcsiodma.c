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


#include "ddcsiocommon.h"
#include "ddcsiodma.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdCsioDma, dd_csio_dma);

#define DD_CSIO_DMA_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdCsioDmaPrivate, DD_TYPE_CSIO_DMA))

#define C_CSIO_FIFO_SIZE					(128)
#define C_CSIO_DMA_TC_MAX				(65536)
#ifdef CO_DDIM_UTILITY_USE
#define C_CSIO_DMACA_IS_BASE		(DdHdmac1_IS_IDREQ_0)
#endif


struct _DdCsioDmaPrivate
{

};

/**
DECLS
*/

/**
IMPL
*/
static void dd_csio_dma_constructor(DdCsioDma *self)
{
//	DdCsioDmaPrivate *priv = DD_CSIO_DMA_GET_PRIVATE(self);
}

static void dd_csio_dma_destructor(DdCsioDma *self)
{
//	DdCsioDmaPrivate *priv = DD_CSIO_DMA_GET_PRIVATE(self);
}
/**
PUBLIC
*/
/**
 * @brief	Dividing frequency is requested from the clock frequency specified by the argument.
 * @param	DdCsioDma*	calTbl		SIO calculate info
 * @return	kint32		D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_dma_calculate(DdCsioDma* const calTbl)
{
	kulong bgr;

#ifdef CO_PARAM_CHECK
	if (calTbl == NULL) {
		Ddim_Assertion(("CSIO input param error. [calTbl] = NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	bgr = (dd_toptwo_get_hclk() / calTbl->inFreq) - 1;
	calTbl->calFreq = bgr;
	Ddim_Print(("dd_csio_dma_calculate() HCLK:%ld freq:%ld bgr:%ld\n", dd_toptwo_get_hclk(), calTbl->inFreq, bgr));
	return D_DDIM_OK;
}


/**
 * @brief	Interrupt Handler of CSIO Send.
 * @param	void
 * @return	void
 */
void dd_csio_dma_int_handler_tx(DdCsioDma *self,  kuchar ch )
{

#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return;
	}
#endif

	if (gddCsioInfo[ch].fullDuplex == 1 && gddCsioInfo[ch].dmaWait == 0) {
		dd_csio_common_int_handler_full_duplex(dd_csio_common_get(), ch);
		return;
	}

	if (gddCsioInfo[ch].dmaWait) {
		if (gddCsioInfo[ch].dmaWait == 2) {
			if (ioUsio.csio[ch].ssr.bit.__tbi == 1) {
				ioUsio.csio[ch].scr.bit.tbie = 0;
				gddCsioInfo[ch].dmaWait = 0;
				dd_csio_common_end(dd_csio_common_get(), ch);
				dd_hdmac1_close(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_SEND].dmaCh);

				if (gddCsioInfo[ch].pcallback != NULL) {
					if (gddCsioInfo[ch].fullDuplex != 1) {
						((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_NORMAL_COMPLETE);
					}
				}
				return;
			}
		} else {	// guard
			ioUsio.csio[ch].fcr.bit.ftie = 0;
			DdCsioCommon_DD_CSIO_DSB();
			return;
		}
	}

	if ((ioUsio.csio[ch].fcr.bit.ftie == 1) && (ioUsio.csio[ch].fcr.bit.fdrq == 1)) {
		// FIFO use
		if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
				while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
					ioUsio.csio[ch].dr.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
					DdCsioCommon_DD_CSIO_DSB();
					gddCsioInfo[ch].sendPos++;

					if (ioUsio.csio[ch].fcr.bit.fdrq == 0) {// FIFO is not full? (0:full, 1:empty)
						break;
					}
				}
			} else {
				while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
					ioUsio.csio[ch].dr.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
					DdCsioCommon_DD_CSIO_DSB();
					gddCsioInfo[ch].sendPos++;

					if (ioUsio.csio[ch].fcr.bit.fdrq == 0) {// FIFO is not full? (0:full, 1:empty)
						break;
					}
				}
			}
			// All data was written
			ioUsio.csio[ch].fcr.bit.fdrq = 0;
			DdCsioCommon_DD_CSIO_DSB();
		} else {	// All data send completed
			if (ioUsio.csio[ch].ssr.bit.__tbi == 1) {
				// End csio communication
				dd_csio_common_end(dd_csio_common_get(), ch);

				if (gddCsioInfo[ch].pcallback != NULL) {
					((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_NORMAL_COMPLETE);
				}
			} else {
				ioUsio.csio[ch].fcr.bit.ftie = 0;
				ioUsio.csio[ch].scr.bit.tbie = 1;
			}
		}
	} else if ((ioUsio.csio[ch].scr.bit.tie == 1) && (ioUsio.csio[ch].ssr.bit.__tdre == 1)) {
		// FIFO not use
		if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
				ioUsio.csio[ch].dr.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
			} else {
				ioUsio.csio[ch].dr.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
			}
			gddCsioInfo[ch].sendPos++;
		} else {	// All data send completed
			if(ioUsio.csio[ch].ssr.bit.__tbi == 1){
				// End csio communication
				dd_csio_common_end(dd_csio_common_get(), ch);

				if (gddCsioInfo[ch].pcallback != NULL) {
					((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_NORMAL_COMPLETE);
				}
			} else {
				ioUsio.csio[ch].scr.bit.tie = 0;
				ioUsio.csio[ch].scr.bit.tbie = 1;
			}
		}
	} else if ((ioUsio.csio[ch].scr.bit.tbie == 1) && (ioUsio.csio[ch].ssr.bit.__tbi == 1)) {
		// End csio communication
		dd_csio_common_end(dd_csio_common_get(), ch);

		if (gddCsioInfo[ch].pcallback != NULL) {
			((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_NORMAL_COMPLETE);
		}
	}
}


/**
 * @brief	Interrupt Handler of CSIO Receive.
 * @param  kuchar  ch
 * @return void
 */
void dd_csio_dma_int_handler_rx(DdCsioDma *self,  kuchar ch )
{

#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return;
	}
#endif

	if (gddCsioInfo[ch].dmaWait == 1) {
		ioUsio.csio[ch].fcr.bit.friie = 0;
		ioUsio.csio[ch].scr.bit.rie = 0;
		DdCsioCommon_DD_CSIO_DSB();
		return;
	}

	// Check for buffer overrun error
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

	if ((ioUsio.csio[ch].scr.bit.rie == 1) && (ioUsio.csio[ch].ssr.bit.__rdrf == 1)) {
		if (((ioUsio.csio[ch].fcr.bit.fsel == 0) && (ioUsio.csio[ch].fcr.bit.fe2 == 1)) ||
				((ioUsio.csio[ch].fcr.bit.fsel == 1) && (ioUsio.csio[ch].fcr.bit.fe1 == 1))) {
			// FIFO use
			if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
				while (ioUsio.csio[ch].ssr.bit.__rdrf == 1) {
					*(gddCsioInfo[ch].recvAddr16 + gddCsioInfo[ch].recvPos) = ioUsio.csio[ch].dr.hword;
					gddCsioInfo[ch].recvPos++;
				}
			} else {
				while (ioUsio.csio[ch].ssr.bit.__rdrf == 1) {
					*(gddCsioInfo[ch].recvAddr8 + gddCsioInfo[ch].recvPos) = ioUsio.csio[ch].dr.byte[0];
					gddCsioInfo[ch].recvPos++;
				}
			}
		} else {
			// FIFO not use
			if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
				*(gddCsioInfo[ch].recvAddr16 + gddCsioInfo[ch].recvPos) = ioUsio.csio[ch].dr.hword;
			} else {
				*(gddCsioInfo[ch].recvAddr8 + gddCsioInfo[ch].recvPos) = ioUsio.csio[ch].dr.byte[0];
			}
			gddCsioInfo[ch].recvPos++;
		}

		if (gddCsioInfo[ch].recvPos < gddCsioInfo[ch].num) {
			// Dummy data for master receiving
			if (ioUsio.csio[ch].scr.bit.ms == 0) {
				ioUsio.csio[ch].dr.hword = 0;
				DdCsioCommon_DD_CSIO_DSB();
			}
		} else {	// All data receive completed
			ioUsio.csio[ch].fcr.bit.friie = 0;
			ioUsio.csio[ch].scr.bit.rie = 0;

			// End csio communication
			dd_csio_common_end(dd_csio_common_get(), ch);

			if (gddCsioInfo[ch].pcallback != NULL) {
				((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_NORMAL_COMPLETE);
			}
		}
	}
}

#ifdef CO_DDIM_UTILITY_USE
/**
 * Send data by CSIO.
 */
kint32	dd_csio_dma_send(DdCsioDma *self, kuchar ch, DdCsioSendCtrl const* const csioSendCtrl, void* sendAddr,
				kuint32 num)
{
	kint32 ret;
	DdCsioDma * calTbl = dd_csio_dma_new() ;
	DdCsio * csioCtrl = dd_csio_new() ;
	DdCsioFifoCtrl fifoCtrl;

#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
	    k_object_unref(csioCtrl);
	    k_object_unref(calTbl);
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (csioSendCtrl == NULL) {
		Ddim_Assertion(("CSIO input param error. [csioSendCtrl] = NULL\n"));
	    k_object_unref(csioCtrl);
	    k_object_unref(calTbl);
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (sendAddr == NULL) {
		Ddim_Assertion(("CSIO input param error. [sendAddr] = NULL\n"));
	    k_object_unref(csioCtrl);
	    k_object_unref(calTbl);
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (num == 0) {
		Ddim_Assertion(("CSIO input param error. [num] = %d\n", num));
	    k_object_unref(csioCtrl);
	    k_object_unref(calTbl);
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	csioCtrl->fifoCtrl = &fifoCtrl;
	calTbl->inFreq = csioSendCtrl->baudrate;
	calTbl->calFreq = 0;
	ret = dd_csio_dma_calculate(calTbl);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("CSIO Cal ERR. ret=0x%x\n", ret));
	}

	csioCtrl->mode = csioSendCtrl->mode;							// Transmit mode
	csioCtrl->baudrate = calTbl->calFreq;									// Baudrate generator
	csioCtrl->bitDirection = csioSendCtrl->bitDirection;	// Bit direction
	csioCtrl->dataLength = csioSendCtrl->dataLength;		// Data length
	csioCtrl->sop = 0;				// Serial output
	csioCtrl->type = DdCsio_DD_CSIO_TYPE_MASTER;						// Master/Slave selection
	csioCtrl->pcallback = 0;	// Callback function pointer

	csioCtrl->fifoCtrl->fsel = 0;				// FIFO selection
	csioCtrl->fifoCtrl->flste = 0;			// Data-lost check permmision
	csioCtrl->fifoCtrl->fset = 0;				// FIFO transfer reload pointer storing
	csioCtrl->fifoCtrl->fe2 = 0;				// FIFO 2 enable bit
	csioCtrl->fifoCtrl->fe1 = 0;				// FIFO 1 enable bit
	csioCtrl->fifoCtrl->fbyteRecv = 0;	// Receive data size (byte)

	ret = dd_csio_open(NULL, ch, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("CSIO Open ERR. ret=0x%x\n", ret));
	    k_object_unref(csioCtrl);
	    k_object_unref(calTbl);
		return ret;
	}

	ret = dd_csio_ctrl(ch, csioCtrl);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("CSIO Ctrl ERR. ret=0x%x\n", ret));
	    k_object_unref(csioCtrl);
	    k_object_unref(calTbl);
		return ret;
	}

	ret = dd_csio_set_send_data(NULL, ch, sendAddr, num);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("CSIO Send Data ERR. ret=0x%x\n", ret));
	    k_object_unref(csioCtrl);
	    k_object_unref(calTbl);
		return ret;
	}

	if (csioSendCtrl->fifoDmaEnable) {
		ret = dd_csio_dma_start_send_dma(NULL, ch, csioSendCtrl->dmaCh, C_CSIO_SEND_DMA_MODE_DEMAND);
		if (ret != D_DDIM_OK) {
			Ddim_Print(("CSIO Send Start ERR. ret=0x%x\n", ret));
		    k_object_unref(csioCtrl);
		    k_object_unref(calTbl);
			return ret;
		}
	} else {
		ret = dd_csio_start_send(NULL, ch);
		if (ret != D_DDIM_OK) {
			Ddim_Print(("CSIO Send Start ERR. ret=0x%x\n", ret));
		    k_object_unref(csioCtrl);
		    k_object_unref(calTbl);
			return ret;
		}
	}

	ret = dd_csio_close(NULL, ch);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("CSIO Close ERR. ret=0x%x\n", ret));
	    k_object_unref(csioCtrl);
	    k_object_unref(calTbl);
		return ret;
	}

    k_object_unref(csioCtrl);
    k_object_unref(calTbl);
	return ret;
}

//---------------------------- colabo section ----------------------------
/**
 * @brief	Start sending data via DMA and CSIO FIFO.
 * @param	kuchar	csioCh
 * @param	kuchar	dmaCh
 * @param	kuchar	dmaMode
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR / C_CSIO_FORCE_STOP
 */
kint32 dd_csio_dma_start_send_dma(DdCsioDma *self, kuchar csioCh, kuchar dmaCh, kuchar dmaMode)
{
	kint32 ret;
	kint32 ret2;
	kuint32 remainNum;
	kuint32 index;
	kuint32 index2;
	kuint32 count = 0;
	kuint16 status;

#ifdef CO_PARAM_CHECK
	if (csioCh >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [csioCh] = %d\n", csioCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaCh >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [dmaCh] = %d\n", dmaCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaMode > C_CSIO_RECV_DMA_MODE_DEMAND) {
		Ddim_Assertion(("CSIO input param error. [dmaMode] = %d\n", dmaMode));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	// Open DMA.
	ret = dd_hdmac1_open(dd_hdmac1_get(), dmaCh, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC1_Open () error. ret=0x%x\n", ret));
		return ret;
	}
	/* pgr0584 */
	memset((void*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND], 0, sizeof(gddCsioDmaInfo[csioCh][C_CSIO_SEND]));

//	gddCsioDmaChInfo[dmaCh] = csioCh;
	dd_csio_common_set_gdd_csio_dma_ch_info(dd_csio_common_get(), csioCh,dmaCh);

	gddCsioDmaInfo[csioCh][C_CSIO_SEND].dmaCh = dmaCh;

	ioUsio.csio[csioCh].smr.bit.soe = 1;// Enable Serial data output permission bit
	ioUsio.csio[csioCh].scr.bit.txe = 1;	// Enable transfer permission bit
	// omit RXE=0, tie=0, tbie=0,RIE=0

	// Sets transmission FIFO, when not set with dd_csio_ctrl().
	if (((ioUsio.csio[csioCh].fcr.bit.fsel == 0) && (ioUsio.csio[csioCh].fcr.bit.fe1 == 0))
			|| ((ioUsio.csio[csioCh].fcr.bit.fsel == 1) && (ioUsio.csio[csioCh].fcr.bit.fe2 == 0))) {
		ioUsio.csio[csioCh].fcr.bit.fsel = 0;
		ioUsio.csio[csioCh].fcr.bit.fe1 = 1;
	}

	// Set DMA info.
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configA.bit.is = C_CSIO_DMACA_IS_BASE + (csioCh << 1) + 1;
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.fd = DdHdmac1_FD_FIX;
	if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.intHandler = (VpCallbackFunc) dd_csio_common_send_dma_callback;
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.intHandler = NULL;
	}
	// omit BC=0, FS=DdHdmac1_FS_INCR, rs=DdHdmac1_RS_DISABLE, RD=DdHdmac1_RD_DISABLE

	if (ioUsio.csio[csioCh].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.tw	= DdHdmac1_TW_HWORD;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.srcAddr = (kulong)gddCsioInfo[csioCh].sendAddr16;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.dstAddr = (kulong)(&(ioUsio.csio[csioCh].dr));
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.tw	= DdHdmac1_TW_BYTE;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.srcAddr = (kulong)gddCsioInfo[csioCh].sendAddr8;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.dstAddr = (kulong)(&(ioUsio.csio[csioCh].dr));
	}

	remainNum = gddCsioInfo[csioCh].num;

	// Set Demand Transfer mode
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.ms = DdHdmac1_MS_DEMAND;

	// Set DMA trans count
	if (remainNum > C_CSIO_DMA_TC_MAX) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].transCount = C_CSIO_DMA_TC_MAX;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].dmaCount = remainNum >> 16;
		// C_CSIO_DMA_TC_MAX(65536)
		remainNum = remainNum % C_CSIO_DMA_TC_MAX;
		count++;
	}
	if (remainNum != 0) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].transCount = remainNum;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].dmaCount = 1;
		remainNum = 0;
		count++;
	}

	gddCsioInfo[csioCh].dmaWait = 1;

	for (index = 0; index < count; index++) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configA.bit.tc =
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].transCount - 1;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configA.bit.bt =
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].beatType;
		if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].dmaCount > 1) {
			// Enable reload counter
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.rc	= DdHdmac1_RC_ENABLE;
		}

		ioUsio.csio[csioCh].fcr.bit.ftie = 0;
		ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
		DdCsioCommon_DD_CSIO_DSB();

		// Start DMA
		ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
						(Hdmac1Ctrl*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl);

		if(ret == D_DDIM_OK){
			if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].count = count;
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].index = 0;
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].index2 = 0;

				// Start DMA by CSIO FIFO interrupt.
				ioUsio.csio[csioCh].fcr.bit.ftie = 1;
				DdCsioCommon_DD_CSIO_DSB();

				return D_DDIM_OK;
			}

			// Start DMA by CSIO FIFO interrupt.
			ioUsio.csio[csioCh].fcr.bit.ftie = 1;
			DdCsioCommon_DD_CSIO_DSB();

			// Wait end of DMA transfer.
			ret = dd_hdmac1_set_wait_time(dd_hdmac1_get(), dmaCh, D_DDIM_WAIT_END_FOREVER);
			ret = dd_hdmac1_wait_end(dd_hdmac1_get(), dmaCh, &status, DdHdmac1_WAITMODE_EVENT);
			if (status != DdHdmac1_SS_NORMAL_END) {
				Ddim_Print(("Dd_HDMAC1_Wait_End () stop status error. status=%d\n", status));
				ret = C_CSIO_DMA_SS_ERROR;
				break;
			}

			if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].dmaCount > 1) {
				// Loop by FIFO size or HDMAC max size unit, and restart the DMA
				for (index2 = 1; index2 < gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].dmaCount; index2++) {
					ioUsio.csio[csioCh].fcr.bit.ftie = 0;
					ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
					DdCsioCommon_DD_CSIO_DSB();

					// Restart DMA
					ret = dd_hdmac1_resume(dd_hdmac1_get(), dmaCh);

					// Restart DMA by CSIO FIFO interrupt.
					ioUsio.csio[csioCh].fcr.bit.ftie = 1;
					DdCsioCommon_DD_CSIO_DSB();

					// Wait end of DMA transfer.
					ret = dd_hdmac1_wait_end(dd_hdmac1_get(), dmaCh, &status, DdHdmac1_WAITMODE_EVENT);
					if (status != DdHdmac1_SS_NORMAL_END) {
						Ddim_Print(("Dd_HDMAC1_Wait_End () stop status error. status=%d\n", status));
						ret = C_CSIO_DMA_SS_ERROR;
						break;
					}
				}
				if (ret != D_DDIM_OK) {
					break;
				}
			}
		} else {
			// DMA start error
			break;
		}

		// Disable reload counter
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_DISABLE;

		// Update source address
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.srcAddr = dd_hdmac1_get_src_addr(dd_hdmac1_get(), dmaCh);
	}

	// End DMA transfer process.
	ioUsio.csio[csioCh].fcr.bit.ftie = 0;
	DdCsioCommon_DD_CSIO_DSB();

	while (ioUsio.csio[csioCh].ssr.bit.__tbi == 0) {
		// wait Bus Idle
		ret2 = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), csioCh, 0);
		if (ret2 != D_DDIM_OK) {
			return ret2;
		}
	}
	if (gddCsioInfo[csioCh].forceStopFlg == 1) {
		dd_csio_common_end(dd_csio_common_get(), csioCh);
		return C_CSIO_FORCE_STOP;
	}

	dd_csio_common_end(dd_csio_common_get(), csioCh);
	dd_hdmac1_close(dd_hdmac1_get(), dmaCh);
	return ret;
}


/**
 * @brief	Start Receive data via DMA and CSIO FIFO.
 * @param	kuchar	csioCh
 * @param	kuchar	dmaCh
 * @param	kuchar	dmaMode
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_dma_start_recv_dma(DdCsioDma *self, kuchar csioCh, kuchar dmaCh, kuchar dmaMode)
{
	kint32 ret;
	kuint32 remainNum = 0;
	kuint32 index;
	kuint32 index2;
	kuint32 count = 0;
	kuint16 status;
	kuchar sendFifoNum = 0;
	kuchar recvFifoNum = 1;

#ifdef CO_PARAM_CHECK
	if (csioCh >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [csioCh] = %d\n", csioCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaCh >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [dmaCh] = %d\n", dmaCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaMode > C_CSIO_RECV_DMA_MODE_DEMAND) {
		Ddim_Assertion(("CSIO input param error. [dmaMode] = %d\n", dmaMode));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	// Open DMA.
	ret = dd_hdmac1_open(dd_hdmac1_get(), dmaCh, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC1_Open () error. ret=0x%x\n", ret));
		return ret;
	}

	// Set send fifo
	if (ioUsio.csio[csioCh].fcr.bit.fsel == 1) {
		sendFifoNum = 1;
		recvFifoNum = 0;
	}

	memset((void*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV], 0, sizeof(gddCsioDmaInfo[csioCh][C_CSIO_RECV]));

//	gddCsioDmaChInfo[dmaCh] = csioCh;
	dd_csio_common_set_gdd_csio_dma_ch_info(dd_csio_common_get(), csioCh,dmaCh);
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].dmaCh = dmaCh;
	ioUsio.csio[csioCh].smr.bit.soe = 0;// Disable Serial data output permission
	ioUsio.csio[csioCh].scr.bit.tie = 0;	// Disable transmit interrupt
	ioUsio.csio[csioCh].scr.bit.tbie = 0; // Disable transmit  bus interrupt
	ioUsio.csio[csioCh].smr.bit.soe = 0;// Disable Serial data output permission bit
	// omit txe=0, RXE=0, tie=0, tbie=0,RIE=0

	// Set DMA info.
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.is = C_CSIO_DMACA_IS_BASE + (csioCh << 1);
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.fs = DdHdmac1_FS_FIX;
	// HPROT of destination protection (8:cacheable)
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.dp = 8;
	if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.intHandler =
				(VpCallbackFunc) dd_csio_common_recv_dma_callback;
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.intHandler = NULL;
	}
	// omit BC=0, FD=DdHdmac1_FD_INCR, rs=DdHdmac1_RS_DISABLE, RD=DdHdmac1_RD_DISABLE

	if (ioUsio.csio[csioCh].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.tw = DdHdmac1_TW_HWORD;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.srcAddr = (kulong) (&(ioUsio.csio[csioCh].dr));
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dstAddr = (kulong) gddCsioInfo[csioCh].recvAddr16;
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.tw = DdHdmac1_TW_BYTE;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.srcAddr = (kulong) (&(ioUsio.csio[csioCh].dr));
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dstAddr = (kulong) gddCsioInfo[csioCh].recvAddr8;
	}

	remainNum = gddCsioInfo[csioCh].num;
	gddCsioInfo[csioCh].dmaWait = 1;

	if (ioUsio.csio[csioCh].scr.bit.ms == 0) {	// Master receiving
		// Set Demand Transfer mode
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.ms = DdHdmac1_MS_DEMAND;

		if (remainNum > C_CSIO_FIFO_SIZE) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = remainNum >> 7;	// C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = C_CSIO_FIFO_SIZE;
			remainNum = remainNum % C_CSIO_FIFO_SIZE;
			count++;
		}
		if (remainNum != 0) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = remainNum;
			remainNum = 0;
			count++;
		}

		ioUsio.csio[csioCh].fcr.bit.friie = 1;// Enable receive fifo idle detect permission

		for (index = 0; index < count; index++) {
			ioUsio.csio[csioCh].scr.bit.rie = 0;	// Disable receive interrupt
			ioUsio.csio[csioCh].fcr.bit.fe1 = 0;		// Disable FIFO1
			ioUsio.csio[csioCh].fcr.bit.fe2 = 0;		// Disable FIFO2
			ioUsio.csio[csioCh].scr.bit.rxe = 0;// Disable receive permission
			ioUsio.csio[csioCh].scr.bit.txe = 0;// Disable transmit permission
			DdCsioCommon_DD_CSIO_DSB();

			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.tc =
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].transCount - 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.bt =
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].beatType;
			if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
				// Enable reload counter
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_ENABLE;
			}

			// Start DMA
			ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
							(Hdmac1Ctrl*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl);

			if (ret == D_DDIM_OK) {
				// Update fbyte
				ioUsio.csio[csioCh].fbyte.byte[recvFifoNum] =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].rFbyte;
				ioUsio.csio[csioCh].fbyte.byte[sendFifoNum] =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].sFbyte;
				ioUsio.csio[csioCh].fcr.bit.fe1 = 1;	// Enable FIFO1
				ioUsio.csio[csioCh].fcr.bit.fe2 = 1;	// Enable FIFO2

				if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].count = count;
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].index = 0;
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2 = 0;
					// Start DMA by CSIO FIFO interrupt.
					ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
					ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
					ioUsio.csio[csioCh].scr.bit.rxe = 1;// Enable receive permission
					ioUsio.csio[csioCh].scr.bit.txe = 1;// Enable transmit permission(Start SCK output)
					DdCsioCommon_DD_CSIO_DSB();
					return D_DDIM_OK;
				}

				// Start DMA by CSIO FIFO interrupt.
				ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
				ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
				ioUsio.csio[csioCh].scr.bit.rxe = 1;// Enable receive permission
				ioUsio.csio[csioCh].scr.bit.txe = 1;// Enable transmit permission(Start SCK output)
				DdCsioCommon_DD_CSIO_DSB();
				// Wait end of DMA transfer.
				ret = dd_hdmac1_set_wait_time(dd_hdmac1_get(), dmaCh, D_DDIM_WAIT_END_FOREVER);
				ret = dd_hdmac1_wait_end(dd_hdmac1_get(), dmaCh, &status, DdHdmac1_WAITMODE_EVENT);
				if(status != DdHdmac1_SS_NORMAL_END){
					Ddim_Print(("Dd_HDMAC1_Wait_End () stop status error. status=%d\n", status));
					ret = C_CSIO_DMA_SS_ERROR;
					break;
				}

				if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
					// Loop by FIFO size unit, and restart the DMA
					for(index2=1; index2 < gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount; index2++){
						ioUsio.csio[csioCh].scr.bit.rie = 0;
						DdCsioCommon_DD_CSIO_DSB();

						// Restart DMA
						ret = dd_hdmac1_resume(dd_hdmac1_get(), dmaCh);

						// Update fbyte
						ioUsio.csio[csioCh].fbyte.byte[sendFifoNum] =
								gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].sFbyte;

						// Restart DMA by CSIO FIFO interrupt.
						ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
						ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
						DdCsioCommon_DD_CSIO_DSB();

						// Wait end of DMA transfer.
						ret = dd_hdmac1_wait_end(dd_hdmac1_get(), dmaCh, &status, DdHdmac1_WAITMODE_EVENT);
						if (status != DdHdmac1_SS_NORMAL_END) {
							Ddim_Print(("Dd_HDMAC1_Wait_End () stop status error. status=%d\n", status));
							ret = C_CSIO_DMA_SS_ERROR;
							break;
						}
					}
					if (ret != D_DDIM_OK) {
						break;
					}
				}
			} else {
				// DMA start error
				break;
			}

			// Disable reload counter
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_DISABLE;

			// Update destination address
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dstAddr = dd_hdmac1_get_dst_addr(dd_hdmac1_get(), dmaCh);
		}
	} else {	// Slave receiving
		// Set Demand Transfer mode
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.ms = DdHdmac1_MS_DEMAND;

		if (remainNum > C_CSIO_DMA_TC_MAX) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = C_CSIO_DMA_TC_MAX;
			// C_CSIO_DMA_TC_MAX(65536)
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = remainNum >> 16;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE >> 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = remainNum % C_CSIO_DMA_TC_MAX;
			count++;
		}
		if (remainNum != 0) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE >> 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = 0;
			count++;
		}

		ioUsio.csio[csioCh].fcr.bit.friie = 1;// Enable receive fifo idle detect permission
		ioUsio.csio[csioCh].fcr.bit.fe1 = 1;	// Enable FIFO1
		ioUsio.csio[csioCh].fcr.bit.fe2 = 1;	// Enable FIFO2
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].count = count;

		for (index = 0; index < count; index++) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.tc =
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].transCount - 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.bt =
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].beatType;
			if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
				// Enable reload counter
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_ENABLE;
			}

			ioUsio.csio[csioCh].scr.bit.rie = 0;	// Disable receive interrupt
			if (index == 0) {
				ioUsio.csio[csioCh].fbyte.byte[recvFifoNum] =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].rFbyte;
			}
			DdCsioCommon_DD_CSIO_DSB();

			// Start DMA
			ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
							(Hdmac1Ctrl*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl);

			if (ret == D_DDIM_OK) {
				if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].count = count;
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].index = 0;
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2 = 0;

					// Start DMA by CSIO FIFO interrupt.
					ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
					ioUsio.csio[csioCh].scr.bit.rxe = 1;// Enable receive permission
					DdCsioCommon_DD_CSIO_DSB();
					return D_DDIM_OK;
				}

				// Start DMA by CSIO FIFO interrupt.
				ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
				if (index == 0) {
					ioUsio.csio[csioCh].scr.bit.rxe = 1;// Enable receive permission
				}
				DdCsioCommon_DD_CSIO_DSB();

				// Wait end of DMA transfer.
				ret = dd_hdmac1_set_wait_time(dd_hdmac1_get(), dmaCh, D_DDIM_WAIT_END_FOREVER);
				ret = dd_hdmac1_wait_end(dd_hdmac1_get(), dmaCh, &status, DdHdmac1_WAITMODE_EVENT);
				if (status != DdHdmac1_SS_NORMAL_END) {
					Ddim_Print(("Dd_HDMAC1_Wait_End () stop status error. status=%d\n", status));
					ret = C_CSIO_DMA_SS_ERROR;
					break;
				}

				if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
					// Loop by HDMAC max size unit, and restart the DMA
					for (index2 = 1; index2 < gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount;
							index2++) {
						ioUsio.csio[csioCh].scr.bit.rie = 0;
						DdCsioCommon_DD_CSIO_DSB();

						// Restart DMA
						ret = dd_hdmac1_resume(dd_hdmac1_get(), dmaCh);

						// Restart DMA by CSIO FIFO interrupt.
						ioUsio.csio[csioCh].scr.bit.rie = 1;// Enable receive interrupt
						DdCsioCommon_DD_CSIO_DSB();

						// Wait end of DMA transfer.
						ret = dd_hdmac1_wait_end(dd_hdmac1_get(), dmaCh, &status, DdHdmac1_WAITMODE_EVENT);
						if (status != DdHdmac1_SS_NORMAL_END) {
							Ddim_Print(("Dd_HDMAC1_Wait_End () stop status error. status=%d\n", status));
							ret = C_CSIO_DMA_SS_ERROR;
							break;
						}
					}
					if (ret != D_DDIM_OK) {
						break;
					}
				}
			} else {
				// DMA start error
				break;
			}

			// Disable reload counter
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_DISABLE;

			// Update destination address
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dstAddr = dd_hdmac1_get_dst_addr(dd_hdmac1_get(), dmaCh);
		}
	}

	// Check for buffer overrun error
	if (ioUsio.csio[csioCh].ssr.bit.__ore == 1) {
		// Clear buffer overrun error
		ioUsio.csio[csioCh].ssr.byte |= C_CSIO_SSR_REC_BIT;
		ret = C_CSIO_RECV_OVERRUN_ERROR;
	}

	// End DMA transfer process.
	ioUsio.csio[csioCh].fcr.bit.fe1 = 0;
	ioUsio.csio[csioCh].fcr.bit.fe2 = 0;
	DdCsioCommon_DD_CSIO_DSB();
	dd_csio_common_end(dd_csio_common_get(), csioCh);
	dd_hdmac1_close(dd_hdmac1_get(), dmaCh);
	return ret;
}

/**
 * @brief	Start full duplex communication via DMA and CSIO FIFO.
 * @param	kuchar	csioCh
 * @param	kuchar	dmaChSend
 * @param	kuchar	dmaChRecv
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_dma_start_full_duplex_dma(DdCsioDma *self, kuchar csioCh, kuchar dmaChSend, kuchar dmaChRecv)
{
	kint32 ret;
	kuint32 remainNum;
	kuint32 count = 0;

#ifdef CO_PARAM_CHECK
	if (csioCh >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [csioCh] = %d\n", csioCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaChSend >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [dmaChSend] = %d\n", dmaChSend));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaChRecv >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [dmaChRecv] = %d\n", dmaChRecv));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	gddCsioInfo[csioCh].fullDuplex = 1;

	// Open DMA(send).
	ret = dd_hdmac1_open(dd_hdmac1_get(), dmaChSend, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC1_Open () error. ret=0x%x\n", ret));
		return ret;
	}

	// Open DMA(receive).
	ret = dd_hdmac1_open(dd_hdmac1_get(), dmaChRecv, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC1_Open () error. ret=0x%x\n", ret));
		return ret;
	}

	// send setting
	memset((void*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND], 0,
			sizeof(gddCsioDmaInfo[csioCh][C_CSIO_SEND])); /* pgr0584 */
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].dmaCh = dmaChSend;

	// Set DMA info.
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configA.bit.is = C_CSIO_DMACA_IS_BASE + (csioCh << 1) + 1;
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.fd = DdHdmac1_FD_FIX;
	if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.intHandler = (VpCallbackFunc) dd_csio_common_send_dma_callback;
	} else {
		Ddim_Print(("dd_csio_dma_start_full_duplex_dma() error. pcallback=NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	// omit BC=0, FS=DdHdmac1_FS_INCR, rs=DdHdmac1_RS_DISABLE, RD=DdHdmac1_RD_DISABLE

	if (ioUsio.csio[csioCh].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.tw = DdHdmac1_TW_HWORD;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.srcAddr = (kulong) gddCsioInfo[csioCh].sendAddr16;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.dstAddr = (kulong) (&(ioUsio.csio[csioCh].dr));
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.tw = DdHdmac1_TW_BYTE;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.srcAddr = (kulong) gddCsioInfo[csioCh].sendAddr8;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.dstAddr = (kulong) (&(ioUsio.csio[csioCh].dr));
	}

	remainNum = gddCsioInfo[csioCh].num;

	// Set Demand Transfer mode
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.ms = DdHdmac1_MS_DEMAND;

	// Set DMA trans count
	if (remainNum > C_CSIO_DMA_TC_MAX) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].transCount = C_CSIO_DMA_TC_MAX;
		// C_CSIO_DMA_TC_MAX(65536)
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].dmaCount = remainNum >> 16;
		remainNum = remainNum % C_CSIO_DMA_TC_MAX;
		count++;
	}
	if (remainNum != 0) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].transCount = remainNum;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].dmaCount = 1;
		remainNum = 0;
		count++;
	}

	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configA.bit.tc =
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[0].transCount - 1;
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configA.bit.bt =
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[0].beatType;
	if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[0].dmaCount > 1) {
		// Enable reload counter
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_ENABLE;
	}

	// Start DMA
	ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaChSend,
					(Hdmac1Ctrl*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl);

	if (ret == D_DDIM_OK) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].count = count;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].index = 0;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].index2 = 0;
	} else {
		dd_csio_common_end(dd_csio_common_get(), csioCh);
		return ret;
	}

	count = 0;

	// receive setting
	memset((void*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV], 0, sizeof(gddCsioDmaInfo[csioCh][C_CSIO_RECV]));
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].dmaCh = dmaChRecv;

	// Set DMA info.
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.is = C_CSIO_DMACA_IS_BASE + (csioCh << 1);
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.fs = DdHdmac1_FS_FIX;
	// HPROT of destination protection (8:cacheable)
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.dp = 8;
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.intHandler = (VpCallbackFunc) dd_csio_common_recv_dma_callback;
	// omit BC=0, FS=DdHdmac1_FS_INCR, rs=DdHdmac1_RS_DISABLE, RD=DdHdmac1_RD_DISABLE

	if (ioUsio.csio[csioCh].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.tw = DdHdmac1_TW_HWORD;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.srcAddr = (kulong) (&(ioUsio.csio[csioCh].dr));
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dstAddr = (kulong) gddCsioInfo[csioCh].recvAddr16;
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.tw = DdHdmac1_TW_BYTE;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.srcAddr = (kulong) (&(ioUsio.csio[csioCh].dr));
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dstAddr = (kulong) gddCsioInfo[csioCh].recvAddr8;
	}

	remainNum = gddCsioInfo[csioCh].num;

	// Set Demand Transfer mode
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.ms = DdHdmac1_MS_DEMAND;

	if (ioUsio.csio[csioCh].scr.bit.ms == 0) {	// Master receiving
		if (remainNum > C_CSIO_FIFO_SIZE) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = C_CSIO_FIFO_SIZE;
			// C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = remainNum >> 7;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = remainNum % C_CSIO_FIFO_SIZE;
			count++;
		}
		if( remainNum != 0) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = 0;
			count++;
		}
	} else {	// Slave receiving
		if (remainNum > C_CSIO_DMA_TC_MAX) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = C_CSIO_DMA_TC_MAX;
			// C_CSIO_DMA_TC_MAX(65536)
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount	 = remainNum >> 16;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = remainNum % C_CSIO_DMA_TC_MAX;
			count++;
		}
		if (remainNum != 0) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = DdHdmac1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = 0;
			count++;
		}
	}

	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.tc =
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].transCount - 1;
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configA.bit.bt =
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].beatType;
	if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].dmaCount > 1) {
		// Enable reload counter
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.configB.bit.rc = DdHdmac1_RC_ENABLE;
	}

	// Start DMA
	ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaChRecv,
					(Hdmac1Ctrl*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl);

	if (ret == D_DDIM_OK) {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].count = count;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].index = 0;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2 = 0;
	} else {
		// Check for buffer overrun error
		if (ioUsio.csio[csioCh].ssr.bit.__ore == 1) {
			// Clear buffer overrun error
			ioUsio.csio[csioCh].ssr.byte |= C_CSIO_SSR_REC_BIT;
			ret = C_CSIO_RECV_OVERRUN_ERROR;
		}

		// End DMA transfer process.
		ioUsio.csio[csioCh].fcr.bit.fe1 = 0;
		ioUsio.csio[csioCh].fcr.bit.fe2 = 0;
		DdCsioCommon_DD_CSIO_DSB();
		dd_csio_common_end(dd_csio_common_get(), csioCh);
		dd_hdmac1_close(dd_hdmac1_get(), dmaChRecv);
		return ret;
	}

	// send setting
//	gddCsioDmaChInfo[dmaChSend] = csioCh;
	dd_csio_common_set_gdd_csio_dma_ch_info(dd_csio_common_get(), csioCh,dmaChSend);
	ioUsio.csio[csioCh].smr.bit.soe = 1;// Enable Serial data output permission bit
	ioUsio.csio[csioCh].scr.bit.txe = 1;	// Enable transfer permission bit
	// omit RXE=0, tie=0, tbie=0,RIE=0

	ioUsio.csio[csioCh].fcr.bit.fsel = 0;
	ioUsio.csio[csioCh].fcr.bit.fe1 = 1;
	ioUsio.csio[csioCh].fcr.bit.fe2 = 1;
	ioUsio.csio[csioCh].fcr.bit.ftie = 0;

	// receive setting
//	gddCsioDmaChInfo[dmaChRecv] = csioCh;
	dd_csio_common_set_gdd_csio_dma_ch_info(dd_csio_common_get(), csioCh,dmaChRecv);
	ioUsio.csio[csioCh].scr.bit.rie = 0;		// Disable receive interrupt
	ioUsio.csio[csioCh].scr.bit.rxe = 0;		// Disable receive permission
	ioUsio.csio[csioCh].fcr.bit.friie = 1;// Enable receive fifo idle detect permission
	ioUsio.csio[csioCh].fbyte.byte[0] = gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].sFbyte;
	ioUsio.csio[csioCh].fbyte.byte[1] = gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].rFbyte;

	// Start DMA by CSIO FIFO interrupt.
	ioUsio.csio[csioCh].fcr.bit.fdrq = 0;
	ioUsio.csio[csioCh].scr.bit.rie = 1;		// Enable receive interrupt
	ioUsio.csio[csioCh].scr.bit.rxe = 1;		// Enable receive permission
	ioUsio.csio[csioCh].fcr.bit.ftie = 1;
	gddCsioInfo[csioCh].dmaWait = 1;
	while (ioUsio.csio[csioCh].ssr.bit.__rdrf == 0) {
		// Wait until RDR filled up with data
	}

	DdCsioCommon_DD_CSIO_DSB();
	return D_DDIM_OK;
}
#endif

DdCsioDma* dd_csio_dma_new(void)
{
	DdCsioDma* self = k_object_new_with_private(DD_TYPE_CSIO_DMA, sizeof(DdCsioDmaPrivate));

	return self;
}
