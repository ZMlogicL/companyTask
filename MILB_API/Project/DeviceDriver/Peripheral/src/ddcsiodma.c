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
#define C_CSIO_DMACA_IS_BASE		(D_DD_HDMAC1_IS_IDREQ_0)
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

	bgr = (Dd_Top_Get_HCLK() / calTbl->inFreq) - 1;
	calTbl->calFreq = bgr;
	Ddim_Print(("dd_csio_dma_calculate() HCLK:%ld freq:%ld bgr:%ld\n", Dd_Top_Get_HCLK(), calTbl->inFreq, bgr));
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
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
			if (IO_USIO.CSIO[ch].SSR.bit.__TBI == 1) {
				IO_USIO.CSIO[ch].SCR.bit.TBIE = 0;
				gddCsioInfo[ch].dmaWait = 0;
				dd_csio_common_end(dd_csio_common_get(), ch);
				Dd_HDMAC1_Close(gddCsioDmaInfo[ch][C_CSIO_SEND].dmaCh);

				if (gddCsioInfo[ch].pcallback != NULL) {
					if (gddCsioInfo[ch].fullDuplex != 1) {
						((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_NORMAL_COMPLETE);
					}
				}
				return;
			}
		} else {	// guard
			IO_USIO.CSIO[ch].FCR.bit.FTIE = 0;
			DdCsioCommon_DD_CSIO_DSB();
			return;
		}
	}

	if ((IO_USIO.CSIO[ch].FCR.bit.FTIE == 1) && (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 1)) {
		// FIFO use
		if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
				while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
					IO_USIO.CSIO[ch].DR.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
					DdCsioCommon_DD_CSIO_DSB();
					gddCsioInfo[ch].sendPos++;

					if (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 0) {// FIFO is not full? (0:full, 1:empty)
						break;
					}
				}
			} else {
				while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
					IO_USIO.CSIO[ch].DR.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
					DdCsioCommon_DD_CSIO_DSB();
					gddCsioInfo[ch].sendPos++;

					if (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 0) {// FIFO is not full? (0:full, 1:empty)
						break;
					}
				}
			}
			// All data was written
			IO_USIO.CSIO[ch].FCR.bit.FDRQ = 0;
			DdCsioCommon_DD_CSIO_DSB();
		} else {	// All data send completed
			if (IO_USIO.CSIO[ch].SSR.bit.__TBI == 1) {
				// End csio communication
				dd_csio_common_end(dd_csio_common_get(), ch);

				if (gddCsioInfo[ch].pcallback != NULL) {
					((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_NORMAL_COMPLETE);
				}
			} else {
				IO_USIO.CSIO[ch].FCR.bit.FTIE = 0;
				IO_USIO.CSIO[ch].SCR.bit.TBIE = 1;
			}
		}
	} else if ((IO_USIO.CSIO[ch].SCR.bit.TIE == 1) && (IO_USIO.CSIO[ch].SSR.bit.__TDRE == 1)) {
		// FIFO not use
		if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
				IO_USIO.CSIO[ch].DR.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
			} else {
				IO_USIO.CSIO[ch].DR.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
			}
			gddCsioInfo[ch].sendPos++;
		} else {	// All data send completed
			if(IO_USIO.CSIO[ch].SSR.bit.__TBI == 1){
				// End csio communication
				dd_csio_common_end(dd_csio_common_get(), ch);

				if (gddCsioInfo[ch].pcallback != NULL) {
					((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_NORMAL_COMPLETE);
				}
			} else {
				IO_USIO.CSIO[ch].SCR.bit.TIE = 0;
				IO_USIO.CSIO[ch].SCR.bit.TBIE = 1;
			}
		}
	} else if ((IO_USIO.CSIO[ch].SCR.bit.TBIE == 1) && (IO_USIO.CSIO[ch].SSR.bit.__TBI == 1)) {
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return;
	}
#endif

	if (gddCsioInfo[ch].dmaWait == 1) {
		IO_USIO.CSIO[ch].FCR.bit.FRIIE = 0;
		IO_USIO.CSIO[ch].SCR.bit.RIE = 0;
		DdCsioCommon_DD_CSIO_DSB();
		return;
	}

	// Check for buffer overrun error
	if (IO_USIO.CSIO[ch].SSR.bit.__ORE == 1) {
		// Clear buffer overrun error
		IO_USIO.CSIO[ch].SSR.byte |= C_CSIO_SSR_REC_BIT;

		// End csio communication
		dd_csio_common_end(dd_csio_common_get(), ch);

		if (gddCsioInfo[ch].pcallback != NULL) {
			((void (*)()) gddCsioInfo[ch].pcallback)(C_CSIO_RECV_OVERRUN_ERROR);
		}
		return;
	}

	if ((IO_USIO.CSIO[ch].SCR.bit.RIE == 1) && (IO_USIO.CSIO[ch].SSR.bit.__RDRF == 1)) {
		if (((IO_USIO.CSIO[ch].FCR.bit.FSEL == 0) && (IO_USIO.CSIO[ch].FCR.bit.FE2 == 1)) ||
				((IO_USIO.CSIO[ch].FCR.bit.FSEL == 1) && (IO_USIO.CSIO[ch].FCR.bit.FE1 == 1))) {
			// FIFO use
			if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
				while (IO_USIO.CSIO[ch].SSR.bit.__RDRF == 1) {
					*(gddCsioInfo[ch].recvAddr16 + gddCsioInfo[ch].recvPos) = IO_USIO.CSIO[ch].DR.hword;
					gddCsioInfo[ch].recvPos++;
				}
			} else {
				while (IO_USIO.CSIO[ch].SSR.bit.__RDRF == 1) {
					*(gddCsioInfo[ch].recvAddr8 + gddCsioInfo[ch].recvPos) = IO_USIO.CSIO[ch].DR.byte[0];
					gddCsioInfo[ch].recvPos++;
				}
			}
		} else {
			// FIFO not use
			if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
				*(gddCsioInfo[ch].recvAddr16 + gddCsioInfo[ch].recvPos) = IO_USIO.CSIO[ch].DR.hword;
			} else {
				*(gddCsioInfo[ch].recvAddr8 + gddCsioInfo[ch].recvPos) = IO_USIO.CSIO[ch].DR.byte[0];
			}
			gddCsioInfo[ch].recvPos++;
		}

		if (gddCsioInfo[ch].recvPos < gddCsioInfo[ch].num) {
			// Dummy data for master receiving
			if (IO_USIO.CSIO[ch].SCR.bit.MS == 0) {
				IO_USIO.CSIO[ch].DR.hword = 0;
				DdCsioCommon_DD_CSIO_DSB();
			}
		} else {	// All data receive completed
			IO_USIO.CSIO[ch].FCR.bit.FRIIE = 0;
			IO_USIO.CSIO[ch].SCR.bit.RIE = 0;

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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
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
	if (csioCh >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [csioCh] = %d\n", csioCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaCh >= D_DD_HDMAC1_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [dmaCh] = %d\n", dmaCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaMode > C_CSIO_RECV_DMA_MODE_DEMAND) {
		Ddim_Assertion(("CSIO input param error. [dmaMode] = %d\n", dmaMode));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	// Open DMA.
	ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return ret;
	}
	/* pgr0584 */
	memset((void*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND], 0, sizeof(gddCsioDmaInfo[csioCh][C_CSIO_SEND]));

//	gddCsioDmaChInfo[dmaCh] = csioCh;
	dd_csio_common_set_gdd_csio_dma_ch_info(dd_csio_common_get(), csioCh,dmaCh);

	gddCsioDmaInfo[csioCh][C_CSIO_SEND].dmaCh = dmaCh;

	IO_USIO.CSIO[csioCh].SMR.bit.SOE = 1;// Enable Serial data output permission bit
	IO_USIO.CSIO[csioCh].SCR.bit.TXE = 1;	// Enable transfer permission bit
	// omit RXE=0, TIE=0, TBIE=0,RIE=0

	// Sets transmission FIFO, when not set with dd_csio_ctrl().
	if (((IO_USIO.CSIO[csioCh].FCR.bit.FSEL == 0) && (IO_USIO.CSIO[csioCh].FCR.bit.FE1 == 0))
			|| ((IO_USIO.CSIO[csioCh].FCR.bit.FSEL == 1) && (IO_USIO.CSIO[csioCh].FCR.bit.FE2 == 0))) {
		IO_USIO.CSIO[csioCh].FCR.bit.FSEL = 0;
		IO_USIO.CSIO[csioCh].FCR.bit.FE1 = 1;
	}

	// Set DMA info.
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_a.bit.is = C_CSIO_DMACA_IS_BASE + (csioCh << 1) + 1;
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.fd = D_DD_HDMAC1_FD_FIX;
	if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.int_handler = (VpCallback) dd_csio_common_send_dma_callback;
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.int_handler = NULL;
	}
	// omit BC=0, FS=D_DD_HDMAC1_FS_INCR, rs=D_DD_HDMAC1_RS_DISABLE, RD=D_DD_HDMAC1_RD_DISABLE

	if (IO_USIO.CSIO[csioCh].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.tw	= D_DD_HDMAC1_TW_HWORD;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.src_addr = (kulong)gddCsioInfo[csioCh].sendAddr16;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.dst_addr = (kulong)(&(IO_USIO.CSIO[csioCh].DR));
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.tw	= D_DD_HDMAC1_TW_BYTE;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.src_addr = (kulong)gddCsioInfo[csioCh].sendAddr8;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.dst_addr = (kulong)(&(IO_USIO.CSIO[csioCh].DR));
	}

	remainNum = gddCsioInfo[csioCh].num;

	// Set Demand Transfer mode
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_DEMAND;

	// Set DMA trans count
	if (remainNum > C_CSIO_DMA_TC_MAX) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].transCount = C_CSIO_DMA_TC_MAX;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].dmaCount = remainNum >> 16;
		// C_CSIO_DMA_TC_MAX(65536)
		remainNum = remainNum % C_CSIO_DMA_TC_MAX;
		count++;
	}
	if (remainNum != 0) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].transCount = remainNum;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].dmaCount = 1;
		remainNum = 0;
		count++;
	}

	gddCsioInfo[csioCh].dmaWait = 1;

	for (index = 0; index < count; index++) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_a.bit.tc =
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].transCount - 1;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_a.bit.bt =
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].beatType;
		if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].dmaCount > 1) {
			// Enable reload counter
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.rc	= D_DD_HDMAC1_RC_ENABLE;
		}

		IO_USIO.CSIO[csioCh].FCR.bit.FTIE = 0;
		IO_USIO.CSIO[csioCh].FCR.bit.FDRQ = 0;
		DdCsioCommon_DD_CSIO_DSB();

		// Start DMA
		ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
						(T_DD_HDMAC1_CTRL*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl);

		if(ret == D_DDIM_OK){
			if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].count = count;
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].index = 0;
				gddCsioDmaInfo[csioCh][C_CSIO_SEND].index2 = 0;

				// Start DMA by CSIO FIFO interrupt.
				IO_USIO.CSIO[csioCh].FCR.bit.FTIE = 1;
				DdCsioCommon_DD_CSIO_DSB();

				return D_DDIM_OK;
			}

			// Start DMA by CSIO FIFO interrupt.
			IO_USIO.CSIO[csioCh].FCR.bit.FTIE = 1;
			DdCsioCommon_DD_CSIO_DSB();

			// Wait end of DMA transfer.
			ret = Dd_HDMAC1_Set_Wait_Time(dmaCh, D_DDIM_WAIT_END_FOREVER);
			ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
			if (status != D_DD_HDMAC1_SS_NORMAL_END) {
				Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
				ret = C_CSIO_DMA_SS_ERROR;
				break;
			}

			if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].dmaCount > 1) {
				// Loop by FIFO size or HDMAC max size unit, and restart the DMA
				for(index2=1; index2 < gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[index].dmaCount; index2++){
					IO_USIO.CSIO[csioCh].FCR.bit.FTIE = 0;
					IO_USIO.CSIO[csioCh].FCR.bit.FDRQ = 0;
					DdCsioCommon_DD_CSIO_DSB();

					// Restart DMA
					ret = Dd_HDMAC1_Resume(dmaCh);

					// Restart DMA by CSIO FIFO interrupt.
					IO_USIO.CSIO[csioCh].FCR.bit.FTIE = 1;
					DdCsioCommon_DD_CSIO_DSB();

					// Wait end of DMA transfer.
					ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
					if (status != D_DD_HDMAC1_SS_NORMAL_END) {
						Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
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
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;

		// Update source address
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.src_addr = Dd_HDMAC1_Get_Src_Addr(dmaCh);
	}

	// End DMA transfer process.
	IO_USIO.CSIO[csioCh].FCR.bit.FTIE = 0;
	DdCsioCommon_DD_CSIO_DSB();

	while (IO_USIO.CSIO[csioCh].SSR.bit.__TBI == 0) {
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
	Dd_HDMAC1_Close(dmaCh);
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
	if (csioCh >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [csioCh] = %d\n", csioCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaCh >= D_DD_HDMAC1_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [dmaCh] = %d\n", dmaCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaMode > C_CSIO_RECV_DMA_MODE_DEMAND) {
		Ddim_Assertion(("CSIO input param error. [dmaMode] = %d\n", dmaMode));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	// Open DMA.
	ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return ret;
	}

	// Set send fifo
	if (IO_USIO.CSIO[csioCh].FCR.bit.FSEL == 1) {
		sendFifoNum = 1;
		recvFifoNum = 0;
	}

	memset((void*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV], 0, sizeof(gddCsioDmaInfo[csioCh][C_CSIO_RECV]));

//	gddCsioDmaChInfo[dmaCh] = csioCh;
	dd_csio_common_set_gdd_csio_dma_ch_info(dd_csio_common_get(), csioCh,dmaCh);
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].dmaCh = dmaCh;
	IO_USIO.CSIO[csioCh].SMR.bit.SOE = 0;// Disable Serial data output permission
	IO_USIO.CSIO[csioCh].SCR.bit.TIE = 0;	// Disable transmit interrupt
	IO_USIO.CSIO[csioCh].SCR.bit.TBIE = 0; // Disable transmit  bus interrupt
	IO_USIO.CSIO[csioCh].SMR.bit.SOE = 0;// Disable Serial data output permission bit
	// omit TXE=0, RXE=0, TIE=0, TBIE=0,RIE=0

	// Set DMA info.
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_a.bit.is = C_CSIO_DMACA_IS_BASE + (csioCh << 1);
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.fs = D_DD_HDMAC1_FS_FIX;
	// HPROT of destination protection (8:cacheable)
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.dp = 8;
	if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.int_handler =
				(VpCallback) dd_csio_common_recv_dma_callback;
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.int_handler = NULL;
	}
	// omit BC=0, FD=D_DD_HDMAC1_FD_INCR, rs=D_DD_HDMAC1_RS_DISABLE, RD=D_DD_HDMAC1_RD_DISABLE

	if (IO_USIO.CSIO[csioCh].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_HWORD;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.src_addr = (kulong) (&(IO_USIO.CSIO[csioCh].DR));
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dst_addr = (kulong) gddCsioInfo[csioCh].recvAddr16;
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_BYTE;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.src_addr = (kulong) (&(IO_USIO.CSIO[csioCh].DR));
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dst_addr = (kulong) gddCsioInfo[csioCh].recvAddr8;
	}

	remainNum = gddCsioInfo[csioCh].num;
	gddCsioInfo[csioCh].dmaWait = 1;

	if (IO_USIO.CSIO[csioCh].SCR.bit.MS == 0) {	// Master receiving
		// Set Demand Transfer mode
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_DEMAND;

		if (remainNum > C_CSIO_FIFO_SIZE) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = remainNum >> 7;	// C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = C_CSIO_FIFO_SIZE;
			remainNum = remainNum % C_CSIO_FIFO_SIZE;
			count++;
		}
		if (remainNum != 0) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = remainNum;
			remainNum = 0;
			count++;
		}

		IO_USIO.CSIO[csioCh].FCR.bit.FRIIE = 1;// Enable receive fifo idle detect permission

		for (index = 0; index < count; index++) {
			IO_USIO.CSIO[csioCh].SCR.bit.RIE = 0;	// Disable receive interrupt
			IO_USIO.CSIO[csioCh].FCR.bit.FE1 = 0;		// Disable FIFO1
			IO_USIO.CSIO[csioCh].FCR.bit.FE2 = 0;		// Disable FIFO2
			IO_USIO.CSIO[csioCh].SCR.bit.RXE = 0;// Disable receive permission
			IO_USIO.CSIO[csioCh].SCR.bit.TXE = 0;// Disable transmit permission
			DdCsioCommon_DD_CSIO_DSB();

			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_a.bit.tc =
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].transCount - 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_a.bit.bt =
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].beatType;
			if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
				// Enable reload counter
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_ENABLE;
			}

			// Start DMA
			ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
							(T_DD_HDMAC1_CTRL*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl);

			if (ret == D_DDIM_OK) {
				// Update FBYTE
				IO_USIO.CSIO[csioCh].FBYTE.byte[recvFifoNum] =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].rFbyte;
				IO_USIO.CSIO[csioCh].FBYTE.byte[sendFifoNum] =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].sFbyte;
				IO_USIO.CSIO[csioCh].FCR.bit.FE1 = 1;	// Enable FIFO1
				IO_USIO.CSIO[csioCh].FCR.bit.FE2 = 1;	// Enable FIFO2

				if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].count = count;
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].index = 0;
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2 = 0;
					// Start DMA by CSIO FIFO interrupt.
					IO_USIO.CSIO[csioCh].FCR.bit.FDRQ = 0;
					IO_USIO.CSIO[csioCh].SCR.bit.RIE = 1;// Enable receive interrupt
					IO_USIO.CSIO[csioCh].SCR.bit.RXE = 1;// Enable receive permission
					IO_USIO.CSIO[csioCh].SCR.bit.TXE = 1;// Enable transmit permission(Start SCK output)
					DdCsioCommon_DD_CSIO_DSB();
					return D_DDIM_OK;
				}

				// Start DMA by CSIO FIFO interrupt.
				IO_USIO.CSIO[csioCh].FCR.bit.FDRQ = 0;
				IO_USIO.CSIO[csioCh].SCR.bit.RIE = 1;// Enable receive interrupt
				IO_USIO.CSIO[csioCh].SCR.bit.RXE = 1;// Enable receive permission
				IO_USIO.CSIO[csioCh].SCR.bit.TXE = 1;// Enable transmit permission(Start SCK output)
				DdCsioCommon_DD_CSIO_DSB();
				// Wait end of DMA transfer.
				ret = Dd_HDMAC1_Set_Wait_Time(dmaCh, D_DDIM_WAIT_END_FOREVER);
				ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
				if(status != D_DD_HDMAC1_SS_NORMAL_END){
					Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
					ret = C_CSIO_DMA_SS_ERROR;
					break;
				}

				if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
					// Loop by FIFO size unit, and restart the DMA
					for(index2=1; index2 < gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount; index2++){
						IO_USIO.CSIO[csioCh].SCR.bit.RIE = 0;
						DdCsioCommon_DD_CSIO_DSB();

						// Restart DMA
						ret = Dd_HDMAC1_Resume(dmaCh);

						// Update FBYTE
						IO_USIO.CSIO[csioCh].FBYTE.byte[sendFifoNum] =
								gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].sFbyte;

						// Restart DMA by CSIO FIFO interrupt.
						IO_USIO.CSIO[csioCh].FCR.bit.FDRQ = 0;
						IO_USIO.CSIO[csioCh].SCR.bit.RIE = 1;// Enable receive interrupt
						DdCsioCommon_DD_CSIO_DSB();

						// Wait end of DMA transfer.
						ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
						if (status != D_DD_HDMAC1_SS_NORMAL_END) {
							Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
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
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;

			// Update destination address
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dst_addr = Dd_HDMAC1_Get_Dst_Addr(dmaCh);
		}
	} else {	// Slave receiving
		// Set Demand Transfer mode
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_DEMAND;

		if (remainNum > C_CSIO_DMA_TC_MAX) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = C_CSIO_DMA_TC_MAX;
			// C_CSIO_DMA_TC_MAX(65536)
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = remainNum >> 16;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE >> 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = remainNum % C_CSIO_DMA_TC_MAX;
			count++;
		}
		if (remainNum != 0) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE >> 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = 0;
			count++;
		}

		IO_USIO.CSIO[csioCh].FCR.bit.FRIIE = 1;// Enable receive fifo idle detect permission
		IO_USIO.CSIO[csioCh].FCR.bit.FE1 = 1;	// Enable FIFO1
		IO_USIO.CSIO[csioCh].FCR.bit.FE2 = 1;	// Enable FIFO2
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].count = count;

		for (index = 0; index < count; index++) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_a.bit.tc =
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].transCount - 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_a.bit.bt =
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].beatType;
			if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
				// Enable reload counter
				gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_ENABLE;
			}

			IO_USIO.CSIO[csioCh].SCR.bit.RIE = 0;	// Disable receive interrupt
			if (index == 0) {
				IO_USIO.CSIO[csioCh].FBYTE.byte[recvFifoNum] =
						gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].rFbyte;
			}
			DdCsioCommon_DD_CSIO_DSB();

			// Start DMA
			ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaCh,
							(T_DD_HDMAC1_CTRL*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl);

			if (ret == D_DDIM_OK) {
				if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].count = count;
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].index = 0;
					gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2 = 0;

					// Start DMA by CSIO FIFO interrupt.
					IO_USIO.CSIO[csioCh].SCR.bit.RIE = 1;// Enable receive interrupt
					IO_USIO.CSIO[csioCh].SCR.bit.RXE = 1;// Enable receive permission
					DdCsioCommon_DD_CSIO_DSB();
					return D_DDIM_OK;
				}

				// Start DMA by CSIO FIFO interrupt.
				IO_USIO.CSIO[csioCh].SCR.bit.RIE = 1;// Enable receive interrupt
				if (index == 0) {
					IO_USIO.CSIO[csioCh].SCR.bit.RXE = 1;// Enable receive permission
				}
				DdCsioCommon_DD_CSIO_DSB();

				// Wait end of DMA transfer.
				ret = Dd_HDMAC1_Set_Wait_Time(dmaCh, D_DDIM_WAIT_END_FOREVER);
				ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
				if (status != D_DD_HDMAC1_SS_NORMAL_END) {
					Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
					ret = C_CSIO_DMA_SS_ERROR;
					break;
				}

				if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount > 1) {
					// Loop by HDMAC max size unit, and restart the DMA
					for (index2 = 1; index2 < gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[index].dmaCount;
							index2++) {
						IO_USIO.CSIO[csioCh].SCR.bit.RIE = 0;
						DdCsioCommon_DD_CSIO_DSB();

						// Restart DMA
						ret = Dd_HDMAC1_Resume(dmaCh);

						// Restart DMA by CSIO FIFO interrupt.
						IO_USIO.CSIO[csioCh].SCR.bit.RIE = 1;// Enable receive interrupt
						DdCsioCommon_DD_CSIO_DSB();

						// Wait end of DMA transfer.
						ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
						if (status != D_DD_HDMAC1_SS_NORMAL_END) {
							Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
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
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;

			// Update destination address
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dst_addr = Dd_HDMAC1_Get_Dst_Addr(dmaCh);
		}
	}

	// Check for buffer overrun error
	if (IO_USIO.CSIO[csioCh].SSR.bit.__ORE == 1) {
		// Clear buffer overrun error
		IO_USIO.CSIO[csioCh].SSR.byte |= C_CSIO_SSR_REC_BIT;
		ret = C_CSIO_RECV_OVERRUN_ERROR;
	}

	// End DMA transfer process.
	IO_USIO.CSIO[csioCh].FCR.bit.FE1 = 0;
	IO_USIO.CSIO[csioCh].FCR.bit.FE2 = 0;
	DdCsioCommon_DD_CSIO_DSB();
	dd_csio_common_end(dd_csio_common_get(), csioCh);
	Dd_HDMAC1_Close(dmaCh);
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
	if (csioCh >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [csioCh] = %d\n", csioCh));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaChSend >= D_DD_HDMAC1_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [dmaChSend] = %d\n", dmaChSend));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (dmaChRecv >= D_DD_HDMAC1_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [dmaChRecv] = %d\n", dmaChRecv));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	gddCsioInfo[csioCh].fullDuplex = 1;

	// Open DMA(send).
	ret = Dd_HDMAC1_Open(dmaChSend, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return ret;
	}

	// Open DMA(receive).
	ret = Dd_HDMAC1_Open(dmaChRecv, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return ret;
	}

	// send setting
	memset((void*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND], 0,
			sizeof(gddCsioDmaInfo[csioCh][C_CSIO_SEND])); /* pgr0584 */
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].dmaCh	= dmaChSend;

	// Set DMA info.
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_a.bit.is = C_CSIO_DMACA_IS_BASE + (csioCh << 1) + 1;
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.fd = D_DD_HDMAC1_FD_FIX;
	if (gddCsioInfo[csioCh].pcallback) {	// Interrupt enable?
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.int_handler = (VpCallback) dd_csio_common_send_dma_callback;
	} else {
		Ddim_Print(("dd_csio_dma_start_full_duplex_dma() error. pcallback=NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	// omit BC=0, FS=D_DD_HDMAC1_FS_INCR, rs=D_DD_HDMAC1_RS_DISABLE, RD=D_DD_HDMAC1_RD_DISABLE

	if (IO_USIO.CSIO[csioCh].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_HWORD;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.src_addr = (kulong) gddCsioInfo[csioCh].sendAddr16;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.dst_addr = (kulong) (&(IO_USIO.CSIO[csioCh].DR));
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_BYTE;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.src_addr = (kulong) gddCsioInfo[csioCh].sendAddr8;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.dst_addr = (kulong) (&(IO_USIO.CSIO[csioCh].DR));
	}

	remainNum = gddCsioInfo[csioCh].num;

	// Set Demand Transfer mode
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_DEMAND;

	// Set DMA trans count
	if (remainNum > C_CSIO_DMA_TC_MAX) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].transCount = C_CSIO_DMA_TC_MAX;
		// C_CSIO_DMA_TC_MAX(65536)
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].dmaCount = remainNum >> 16;
		remainNum = remainNum % C_CSIO_DMA_TC_MAX;
		count++;
	}
	if (remainNum != 0) {
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].transCount = remainNum;
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[count].dmaCount = 1;
		remainNum = 0;
		count++;
	}

	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_a.bit.tc =
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[0].transCount - 1;
	gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_a.bit.bt =
			gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[0].beatType;
	if (gddCsioDmaInfo[csioCh][C_CSIO_SEND].countInfo[0].dmaCount > 1) {
		// Enable reload counter
		gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_ENABLE;
	}

	// Start DMA
	ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaChSend,
					(T_DD_HDMAC1_CTRL*) &gddCsioDmaInfo[csioCh][C_CSIO_SEND].hdmac1Ctrl);

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
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_a.bit.is = C_CSIO_DMACA_IS_BASE + (csioCh << 1);
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.fs = D_DD_HDMAC1_FS_FIX;
	// HPROT of destination protection (8:cacheable)
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.dp = 8;
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.int_handler = (VpCallback) dd_csio_common_recv_dma_callback;
	// omit BC=0, FS=D_DD_HDMAC1_FS_INCR, rs=D_DD_HDMAC1_RS_DISABLE, RD=D_DD_HDMAC1_RD_DISABLE

	if (IO_USIO.CSIO[csioCh].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_HWORD;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.src_addr = (kulong) (&(IO_USIO.CSIO[csioCh].DR));
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dst_addr = (kulong) gddCsioInfo[csioCh].recvAddr16;
	} else {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_BYTE;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.src_addr = (kulong) (&(IO_USIO.CSIO[csioCh].DR));
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.dst_addr = (kulong) gddCsioInfo[csioCh].recvAddr8;
	}

	remainNum = gddCsioInfo[csioCh].num;

	// Set Demand Transfer mode
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_DEMAND;

	if (IO_USIO.CSIO[csioCh].SCR.bit.MS == 0) {	// Master receiving
		if (remainNum > C_CSIO_FIFO_SIZE) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = C_CSIO_FIFO_SIZE;
			// C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = remainNum >> 7;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = remainNum % C_CSIO_FIFO_SIZE;
			count++;
		}
		if( remainNum != 0) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = 0;
			count++;
		}
	} else {	// Slave receiving
		if (remainNum > C_CSIO_DMA_TC_MAX) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = C_CSIO_DMA_TC_MAX;
			// C_CSIO_DMA_TC_MAX(65536)
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount	 = remainNum >> 16;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = remainNum % C_CSIO_DMA_TC_MAX;
			count++;
		}
		if (remainNum != 0) {
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].transCount = remainNum;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].dmaCount = 1;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].rFbyte = C_CSIO_FIFO_SIZE;
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[count].sFbyte = 0;
			remainNum = 0;
			count++;
		}
	}

	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_a.bit.tc =
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].transCount - 1;
	gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_a.bit.bt =
			gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].beatType;
	if (gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].dmaCount > 1) {
		// Enable reload counter
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_ENABLE;
	}

	// Start DMA
	ret = dd_csio_common_start_dma(dd_csio_common_get(), dmaChRecv,
					(T_DD_HDMAC1_CTRL*) &gddCsioDmaInfo[csioCh][C_CSIO_RECV].hdmac1Ctrl);

	if (ret == D_DDIM_OK) {
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].count = count;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].index = 0;
		gddCsioDmaInfo[csioCh][C_CSIO_RECV].index2 = 0;
	} else {
		// Check for buffer overrun error
		if (IO_USIO.CSIO[csioCh].SSR.bit.__ORE == 1) {
			// Clear buffer overrun error
			IO_USIO.CSIO[csioCh].SSR.byte |= C_CSIO_SSR_REC_BIT;
			ret = C_CSIO_RECV_OVERRUN_ERROR;
		}

		// End DMA transfer process.
		IO_USIO.CSIO[csioCh].FCR.bit.FE1 = 0;
		IO_USIO.CSIO[csioCh].FCR.bit.FE2 = 0;
		DdCsioCommon_DD_CSIO_DSB();
		dd_csio_common_end(dd_csio_common_get(), csioCh);
		Dd_HDMAC1_Close(dmaChRecv);
		return ret;
	}

	// send setting
//	gddCsioDmaChInfo[dmaChSend] = csioCh;
	dd_csio_common_set_gdd_csio_dma_ch_info(dd_csio_common_get(), csioCh,dmaChSend);
	IO_USIO.CSIO[csioCh].SMR.bit.SOE = 1;// Enable Serial data output permission bit
	IO_USIO.CSIO[csioCh].SCR.bit.TXE = 1;	// Enable transfer permission bit
	// omit RXE=0, TIE=0, TBIE=0,RIE=0

	IO_USIO.CSIO[csioCh].FCR.bit.FSEL = 0;
	IO_USIO.CSIO[csioCh].FCR.bit.FE1 = 1;
	IO_USIO.CSIO[csioCh].FCR.bit.FE2 = 1;
	IO_USIO.CSIO[csioCh].FCR.bit.FTIE = 0;

	// receive setting
//	gddCsioDmaChInfo[dmaChRecv] = csioCh;
	dd_csio_common_set_gdd_csio_dma_ch_info(dd_csio_common_get(), csioCh,dmaChRecv);
	IO_USIO.CSIO[csioCh].SCR.bit.RIE = 0;		// Disable receive interrupt
	IO_USIO.CSIO[csioCh].SCR.bit.RXE = 0;		// Disable receive permission
	IO_USIO.CSIO[csioCh].FCR.bit.FRIIE = 1;// Enable receive fifo idle detect permission
	IO_USIO.CSIO[csioCh].FBYTE.byte[0] = gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].sFbyte;
	IO_USIO.CSIO[csioCh].FBYTE.byte[1] = gddCsioDmaInfo[csioCh][C_CSIO_RECV].countInfo[0].rFbyte;

	// Start DMA by CSIO FIFO interrupt.
	IO_USIO.CSIO[csioCh].FCR.bit.FDRQ = 0;
	IO_USIO.CSIO[csioCh].SCR.bit.RIE = 1;		// Enable receive interrupt
	IO_USIO.CSIO[csioCh].SCR.bit.RXE = 1;		// Enable receive permission
	IO_USIO.CSIO[csioCh].FCR.bit.FTIE = 1;
	gddCsioInfo[csioCh].dmaWait = 1;
	while (IO_USIO.CSIO[csioCh].SSR.bit.__RDRF == 0) {
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
