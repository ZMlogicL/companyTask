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

#include "spi.h"
#include "ddspicolabo.h"

#include "ddspidrivebranch.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdSpiDriveBranch, dd_spi_drive_branch);
#define DD_SPI_DRIVE_BRANCH_GET_PRIVATE(o) \
	(K_OBJECT_GET_PRIVATE((o), DdSpiDriveBranchPrivate, DD_TYPE_SPI_DRIVE_BRANCH))

struct _DdSpiDriveBranchPrivate
{
	/* SPI send/receive data information. */
	volatile TDdSpiInfo	gDdSpiInfo[DdSpiDriveBranch_CH_MAX];
};

/*
 * DECLS
 */
static void          ddSpiEndProcess(DdSpiDriveBranch* self, kuchar ch);
static void          ddSpiSendData(DdSpiDriveBranch* self, kuchar ch);
static void          ddSpiWriteDummyCount(DdSpiDriveBranch* self, kuchar ch);
static kuint32     ddSpiCheckStoppingConditions(DdSpiDriveBranch* self, kuchar ch);

static void dd_spi_drive_branch_constructor(DdSpiDriveBranch *self)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);

	kint i;
	for(i = 0; i <DdSpiDriveBranch_CH_MAX; i++)
	{
		priv->gDdSpiInfo[i].recvAddr8 = NULL;
		priv->gDdSpiInfo[i].recvAddr16 = NULL;
		priv->gDdSpiInfo[i].recvAddr32 = NULL;
		priv->gDdSpiInfo[i].sendAddr8 = NULL;
		priv->gDdSpiInfo[i].sendAddr16 = NULL;
		priv->gDdSpiInfo[i].sendAddr32 = NULL;
	}
}

static void dd_spi_drive_branch_destructor(DdSpiDriveBranch *self)
{

}

/*
 * IMPL
 */
/*
 * End Communication Process
 */
static void ddSpiEndProcess(DdSpiDriveBranch* self, kuchar ch)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	kuint32 wait;

	priv->gDdSpiInfo[ch].forceStopFlg = 0;

	if((IO_SPI[ch].CTRL.bit.CONTXFER == 1) && (IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND == 1)){
		return;
	}

	// Disable interrupt
	IO_SPI[ch].INT_EN.word = 0;

	// Disable SPI enable
	IO_SPI[ch].EN.bit.__ENABLEREQ = 0;
	DdSpiDriveBranch_DD_SPI_DSB();

	// 2) Read the Enable Register - it should be 0 before continuing to the next step.
	for(wait = 0; wait < 1000; wait++){
		if(IO_SPI[ch].EN.bit.__ENABLEREQ == 0){
			break;
		}
	}
	if(IO_SPI[ch].EN.bit.__ENABLEREQ != 0){
		Ddim_Print(("SPI[%d] FIFO Reset Error :TX_FIFO_LEVEL=%d, RX_FIFO_LEVEL=%d\n", ch,
				IO_SPI[ch].TXFIFO.bit.TX_FIFO_LEVEL, IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL));
	}

	// Disable DMA wait
	if(priv->gDdSpiInfo[ch].dmaWait >= 1){
		if((priv->gDdSpiInfo[ch].spiMode == DdSpiDriveBranch_DIR_SEND)
				|| (priv->gDdSpiInfo[ch].spiMode == DdSpiDriveBranch_DIR_FULL)){
			Dd_HDMAC1_Stop(dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
					DdSpiDriveBranch_SEND).dmaCh);
			Dd_HDMAC1_Close(dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
					DdSpiDriveBranch_SEND).dmaCh);
		}
		if((priv->gDdSpiInfo[ch].spiMode == DdSpiDriveBranch_DIR_RECV)
				|| (priv->gDdSpiInfo[ch].spiMode == DdSpiDriveBranch_DIR_FULL)){
			Dd_HDMAC1_Stop(dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
					DdSpiDriveBranch_RECV).dmaCh);
			Dd_HDMAC1_Close(dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
					DdSpiDriveBranch_RECV).dmaCh);
		}
		priv->gDdSpiInfo[ch].dmaWait = 0;
	}
}

static void ddSpiSendData(DdSpiDriveBranch* self, kuchar ch)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
		while(priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num){
			if(IO_SPI[ch].ST.bit.TXFULL){
				//FIFO is full. Wait next interrupt.
				break;
			}

			// Write to TX Serial Data Register
			IO_SPI[ch].TXDATA = *(priv->gDdSpiInfo[ch].sendAddr32 + priv->gDdSpiInfo[ch].sendPos);
			DdSpiDriveBranch_DD_SPI_DSB();

			priv->gDdSpiInfo[ch].sendPos++;
		}
	}
	else if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
		while(priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num){
			if(IO_SPI[ch].ST.bit.TXFULL){
				//FIFO is full. Wait next interrupt.
				break;
			}

			// Write to TX Serial Data Register
			IO_SPI[ch].TXDATA = *(priv->gDdSpiInfo[ch].sendAddr16 + priv->gDdSpiInfo[ch].sendPos);
			DdSpiDriveBranch_DD_SPI_DSB();

			priv->gDdSpiInfo[ch].sendPos++;
		}
	}
	else {
		// IO_SPI[ch].AUX_CTRL.bit.BITSIZE <= E_DD_SPI_BIT_LEN_8
		while(priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num){
			if(IO_SPI[ch].ST.bit.TXFULL){
				//FIFO is full. Wait next interrupt.
				break;
			}

			// Write to TX Serial Data Register
			IO_SPI[ch].TXDATA = *(priv->gDdSpiInfo[ch].sendAddr8 + priv->gDdSpiInfo[ch].sendPos);
			DdSpiDriveBranch_DD_SPI_DSB();

			priv->gDdSpiInfo[ch].sendPos++;
		}
	}
}

static void ddSpiWriteDummyCount(DdSpiDriveBranch* self, kuchar ch)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	kuint32 remainDummy;
	kuint32 writeDummy;
	kuint32 fifoEmpty;

	remainDummy = priv->gDdSpiInfo[ch].num - priv->gDdSpiInfo[ch].dummyCount;
	fifoEmpty = IO_SPI[ch].FIFO_DPTH.bit.FIFODEPTH - IO_SPI[ch].TXFIFO.bit.TX_FIFO_LEVEL;

	if(remainDummy > fifoEmpty){
		writeDummy = fifoEmpty;
	}
	else {
		writeDummy = remainDummy;
	}

	// Dummy data for master receiving
	IO_SPI[ch].TX_DWR.word = writeDummy;
	DdSpiDriveBranch_DD_SPI_DSB();

	priv->gDdSpiInfo[ch].dummyCount += writeDummy;
}

/*
 * Check Stop condition
 */
static kuint32 ddSpiCheckStoppingConditions(DdSpiDriveBranch* self, kuchar ch)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	if(priv->gDdSpiInfo[ch].forceStopFlg == 1){
		ddSpiEndProcess(self, ch);
		return DdSpiDriveBranch_FORCE_STOP;
	}

	return D_DDIM_OK;
}

/*
 * PUBLIC
 */
/*
 * Start full duplex communication
 */
kuint32 dd_spi_drive_branch_start_full_duplex(DdSpiDriveBranch* self, kuchar ch)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	kuint32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	priv->gDdSpiInfo[ch].forceStopFlg = 0;

	// Set SPI Mode
	priv->gDdSpiInfo[ch].spiMode = DdSpiDriveBranch_DIR_FULL;

	// Enable RxFIFO
	IO_SPI[ch].AUX_CTRL.bit.INHIBITDIN = 0;

	if(priv->gDdSpiInfo[ch].pCallback){
		// For interrupt operation
#if 0 // Delete for the remaining data is to be acquired by the DMA timeout interrupt.
		if(priv->gDdSpiInfo[ch].num <= IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET){
			// Update Rx Watermark Level
			IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET = priv->gDdSpiInfo[ch].num - 1;
			DdSpiDriveBranch_DD_SPI_DSB();
		}
#endif

		// 11) Write the Enable Register to enable the SPI port
		IO_SPI[ch].EN.bit.__ENABLEREQ = 1;

		// Send data
		ddSpiSendData(self, ch);

		// Set interrupt(TXEMPTYPULSE, TXWMARKPULSE, RXWMARKPULSE, RXFULLPULSE_BIT, RXFIFOOVERFLOW, RXTIMEOUT_BIT bit)
		IO_SPI[ch].INT_EN.word |= DdSpiDriveBranch_INT_FULL_CPU_BIT_SET;
		DdSpiDriveBranch_DD_SPI_DSB();

#ifdef CO_DEBUG_ON_PC
		Ddim_Print(("gDdSpiInfo[%d].num = %u\n", ch, priv->gDdSpiInfo[ch].num));
		Ddim_Print(("gDdSpiInfo[%d].sendPos = %u\n", ch, priv->gDdSpiInfo[ch].sendPos));
		Ddim_Print(("gDdSpiInfo[%d].recvPos = %u\n", ch, priv->gDdSpiInfo[ch].recvPos));
#endif

		return ret;
	}

	// For polled operation
	// 11) Write the Enable Register to enable the SPI port
	IO_SPI[ch].EN.bit.__ENABLEREQ = 1;
	DdSpiDriveBranch_DD_SPI_DSB();

	if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
		while((priv->gDdSpiInfo[ch].recvPos < priv->gDdSpiInfo[ch].num)
				||(priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num)){
			if(IO_SPI[ch].TXFIFO.bit.TX_FIFO_LEVEL <= IO_SPI[ch].FIFO_WMK.bit.TXWMARKSET){
				// Send data
				ddSpiSendData(self, ch);
			}

			// Wait FIFO not Empty
			while(IO_SPI[ch].ST.bit.RXEMPTY){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Check for buffer overflow error
			if(IO_SPI[ch].ST.bit.RXOVERFLOW == 1){
				// End SPI communication
				ddSpiEndProcess(self, ch);
				return DdSpiDriveBranch_RECV_OVERRUN_ERROR;
			}

			// Read data word from the RX Serial Data Register.
			*(priv->gDdSpiInfo[ch].recvAddr32 + priv->gDdSpiInfo[ch].recvPos) = IO_SPI[ch].RXDATA;

			priv->gDdSpiInfo[ch].recvPos++;
		}
	}
	else if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
		while((priv->gDdSpiInfo[ch].recvPos < priv->gDdSpiInfo[ch].num) ||
			   (priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num)){
			if(IO_SPI[ch].TXFIFO.bit.TX_FIFO_LEVEL <= IO_SPI[ch].FIFO_WMK.bit.TXWMARKSET){
				// Send data
				ddSpiSendData(self, ch);
			}

			// Wait FIFO not Empty
			while(IO_SPI[ch].ST.bit.RXEMPTY){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Check for buffer overflow error
			if(IO_SPI[ch].ST.bit.RXOVERFLOW == 1){
				// End SPI communication
				ddSpiEndProcess(self, ch);
				return DdSpiDriveBranch_RECV_OVERRUN_ERROR;
			}

			// Read data word from the RX Serial Data Register.
			*(priv->gDdSpiInfo[ch].recvAddr16 + priv->gDdSpiInfo[ch].recvPos) = IO_SPI[ch].RXDATA;

			priv->gDdSpiInfo[ch].recvPos++;
		}
	}
	else {
		// IO_SPI[ch].AUX_CTRL.bit.BITSIZE <= E_DD_SPI_BIT_LEN_8
		while((priv->gDdSpiInfo[ch].recvPos < priv->gDdSpiInfo[ch].num) ||
			   (priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num)){
			if(IO_SPI[ch].TXFIFO.bit.TX_FIFO_LEVEL <= IO_SPI[ch].FIFO_WMK.bit.TXWMARKSET){
				// Send data
				ddSpiSendData(self, ch);
			}

			// Wait FIFO not Empty
			while(IO_SPI[ch].ST.bit.RXEMPTY){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Check for buffer overflow error
			if(IO_SPI[ch].ST.bit.RXOVERFLOW == 1){
				// End SPI communication
				ddSpiEndProcess(self, ch);
				return DdSpiDriveBranch_RECV_OVERRUN_ERROR;
			}

			// Read data word from the RX Serial Data Register.
			*(priv->gDdSpiInfo[ch].recvAddr8 + priv->gDdSpiInfo[ch].recvPos) = IO_SPI[ch].RXDATA;

			priv->gDdSpiInfo[ch].recvPos++;
		}
	}

	// Check force stop and buffer overflow error
	if(priv->gDdSpiInfo[ch].forceStopFlg == 1){
		ret = DdSpiDriveBranch_FORCE_STOP;
	}
	else if(IO_SPI[ch].ST.bit.RXOVERFLOW == 1){
		ret = DdSpiDriveBranch_RECV_OVERRUN_ERROR;
	}

	// End SPI communication
	ddSpiEndProcess(self, ch);

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("gDdSpiInfo[%d].num = %u\n", ch, priv->gDdSpiInfo[ch].num));
	Ddim_Print(("gDdSpiInfo[%d].sendPos = %u\n", ch, priv->gDdSpiInfo[ch].sendPos));
	Ddim_Print(("gDdSpiInfo[%d].recvPos = %u\n", ch, priv->gDdSpiInfo[ch].recvPos));
#endif

	return ret;
}

/*
 * Start receiving data
 */
kuint32 dd_spi_drive_branch_start_recv(DdSpiDriveBranch* self, kuchar ch)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	kuint32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	priv->gDdSpiInfo[ch].forceStopFlg = 0;

	// Set SPI Mode
	priv->gDdSpiInfo[ch].spiMode = DdSpiDriveBranch_DIR_RECV;

	// Enable RxFIFO
	IO_SPI[ch].AUX_CTRL.bit.INHIBITDIN = 0;

	// Master receiving
	if(IO_SPI[ch].CTRL.bit.MASTER == DdSpiDriveBranch_TYPE_MASTER){
		// Set interrupt(TXEMPTYPULSE, TXWMARKPULSE bit)
		IO_SPI[ch].INT_EN.word |= DdSpiDriveBranch_INT_TX_CPU_BIT_SET;

		// Set 1st dummy data
		ddSpiWriteDummyCount(self, ch);
	}

	if(priv->gDdSpiInfo[ch].pCallback){
		// For interrupt operation
#if 0
		// Delete for the remaining data is to be acquired by the DMA timeout interrupt.
		if(priv->gDdSpiInfo[ch].num <= IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET){
			// Update Rx Watermark Level
			IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET = priv->gDdSpiInfo[ch].num - 1;
			DdSpiDriveBranch_DD_SPI_DSB();
		}
#endif

		// Set interrupt(RXWMARKPULSE, RXFULLPULSE_BIT, RXFIFOOVERFLOW, RXTIMEOUT_BIT bit)
		IO_SPI[ch].INT_EN.word |= DdSpiDriveBranch_INT_RX_CPU_BIT_SET;

		// 11) Write the Enable Register to enable the SPI port
		IO_SPI[ch].EN.bit.__ENABLEREQ = 1;
		DdSpiDriveBranch_DD_SPI_DSB();

#ifdef CO_DEBUG_ON_PC
		Ddim_Print(("gDdSpiInfo[%d].num = %u\n", ch, priv->gDdSpiInfo[ch].num));
		Ddim_Print(("gDdSpiInfo[%d].recvPos = %u\n", ch, priv->gDdSpiInfo[ch].recvPos));
		Ddim_Print(("gDdSpiInfo[%d].dummyCount = %u\n", ch, priv->gDdSpiInfo[ch].dummyCount));
#endif

		return ret;
	}

	// For polled operation
	// 11) Write the Enable Register to enable the SPI port
	IO_SPI[ch].EN.bit.__ENABLEREQ = 1;
	DdSpiDriveBranch_DD_SPI_DSB();

	// Get receive data
	if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
		while(priv->gDdSpiInfo[ch].recvPos < priv->gDdSpiInfo[ch].num){
			// Wait FIFO not Empty
			while(IO_SPI[ch].ST.bit.RXEMPTY){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Check for buffer overflow error
			if(IO_SPI[ch].ST.bit.RXOVERFLOW == 1){
				// End SPI communication
				ddSpiEndProcess(self, ch);
				return DdSpiDriveBranch_RECV_OVERRUN_ERROR;
			}

			// Read data word from the RX Serial Data Register.
			*(priv->gDdSpiInfo[ch].recvAddr32 + priv->gDdSpiInfo[ch].recvPos) = IO_SPI[ch].RXDATA;

			priv->gDdSpiInfo[ch].recvPos++;
		}
	}
	else if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
		while(priv->gDdSpiInfo[ch].recvPos < priv->gDdSpiInfo[ch].num){
			// Wait FIFO not Empty
			while(IO_SPI[ch].ST.bit.RXEMPTY){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Check for buffer overflow error
			if(IO_SPI[ch].ST.bit.RXOVERFLOW == 1){
				// End SPI communication
				ddSpiEndProcess(self, ch);
				return DdSpiDriveBranch_RECV_OVERRUN_ERROR;
			}

			// Read data word from the RX Serial Data Register.
			*(priv->gDdSpiInfo[ch].recvAddr16 + priv->gDdSpiInfo[ch].recvPos) = IO_SPI[ch].RXDATA;

			priv->gDdSpiInfo[ch].recvPos++;
		}
	}
	else {
		// IO_SPI[ch].AUX_CTRL.bit.BITSIZE <= E_DD_SPI_BIT_LEN_8
		while(priv->gDdSpiInfo[ch].recvPos < priv->gDdSpiInfo[ch].num){
			// Wait FIFO not Empty
			while(IO_SPI[ch].ST.bit.RXEMPTY){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Check for buffer overflow error
			if(IO_SPI[ch].ST.bit.RXOVERFLOW == 1){
				// End SPI communication
				ddSpiEndProcess(self, ch);
				return DdSpiDriveBranch_RECV_OVERRUN_ERROR;
			}

			// Read data word from the RX Serial Data Register.
			*(priv->gDdSpiInfo[ch].recvAddr8 + priv->gDdSpiInfo[ch].recvPos) = IO_SPI[ch].RXDATA;

			priv->gDdSpiInfo[ch].recvPos++;
		}
	}

	// Check force stop and buffer overflow error
	if(priv->gDdSpiInfo[ch].forceStopFlg == 1){
		ret = DdSpiDriveBranch_FORCE_STOP;
	}
	else if(IO_SPI[ch].ST.bit.RXOVERFLOW == 1){
		ret = DdSpiDriveBranch_RECV_OVERRUN_ERROR;
	}

	// End SPI communication
	ddSpiEndProcess(self, ch);

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("gDdSpiInfo[%d].num = %u\n", ch, priv->gDdSpiInfo[ch].num));
	Ddim_Print(("gDdSpiInfo[%d].recvPos = %u\n", ch, priv->gDdSpiInfo[ch].recvPos));
	Ddim_Print(("gDdSpiInfo[%d].dummyCount = %u\n", ch, priv->gDdSpiInfo[ch].dummyCount));
#endif

	return ret;
}

/*
 * Start sending data
 */
kuint32 dd_spi_drive_branch_start_send(DdSpiDriveBranch* self, kuchar ch)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	kuint32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	priv->gDdSpiInfo[ch].forceStopFlg = 0;

	// Set SPI Mode
	priv->gDdSpiInfo[ch].spiMode = DdSpiDriveBranch_DIR_SEND;

	// Disable RxFIFO
	IO_SPI[ch].AUX_CTRL.bit.INHIBITDIN = 1;

	if(priv->gDdSpiInfo[ch].pCallback){
		// For interrupt operation
		// 11) Write the Enable Register to enable the SPI port
		IO_SPI[ch].EN.bit.__ENABLEREQ = 1;

		// Send data
		ddSpiSendData(self, ch);

		// Set interrupt(TXEMPTYPULSE, TXWMARKPULSE bit)
		IO_SPI[ch].INT_EN.word |= DdSpiDriveBranch_INT_TX_CPU_BIT_SET;
		DdSpiDriveBranch_DD_SPI_DSB();

#ifdef CO_DEBUG_ON_PC
		Ddim_Print(("gDdSpiInfo[%d].num = %u\n", ch, priv->gDdSpiInfo[ch].num));
		Ddim_Print(("gDdSpiInfo[%d].sendPos = %u\n", ch, priv->gDdSpiInfo[ch].sendPos));
#endif

		return ret;
	}

	// For polled operation
	// 11) Write the Enable Register to enable the SPI port
	IO_SPI[ch].EN.bit.__ENABLEREQ = 1;
	DdSpiDriveBranch_DD_SPI_DSB();

	// Send data
	if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
		while(priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num){
			// Wait FIFO not full
			while(IO_SPI[ch].ST.bit.TXFULL){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Write to TX Serial Data Register
			IO_SPI[ch].TXDATA = *(priv->gDdSpiInfo[ch].sendAddr32 + priv->gDdSpiInfo[ch].sendPos);
			DdSpiDriveBranch_DD_SPI_DSB();

			priv->gDdSpiInfo[ch].sendPos++;
		}
	}
	else if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
		while(priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num){
			// Wait FIFO not full
			while(IO_SPI[ch].ST.bit.TXFULL){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Write to TX Serial Data Register
			IO_SPI[ch].TXDATA = *(priv->gDdSpiInfo[ch].sendAddr16 + priv->gDdSpiInfo[ch].sendPos);
			DdSpiDriveBranch_DD_SPI_DSB();

			priv->gDdSpiInfo[ch].sendPos++;
		}
	}
	else {
		// IO_SPI[ch].AUX_CTRL.bit.BITSIZE <= E_DD_SPI_BIT_LEN_8
		while(priv->gDdSpiInfo[ch].sendPos < priv->gDdSpiInfo[ch].num){
			// Wait FIFO not full
			while(IO_SPI[ch].ST.bit.TXFULL){
				ret = ddSpiCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}

			// Write to TX Serial Data Register
			IO_SPI[ch].TXDATA = *(priv->gDdSpiInfo[ch].sendAddr8 + priv->gDdSpiInfo[ch].sendPos);
			DdSpiDriveBranch_DD_SPI_DSB();

			priv->gDdSpiInfo[ch].sendPos++;
		}
	}

	// All data was written
	while(IO_SPI[ch].ST.bit.TXEMPTY == 0){
		// Wait FIFO Empty
		ret = ddSpiCheckStoppingConditions(self, ch);
		if(ret != D_DDIM_OK){
			return ret;
		}
	}

	// Check return code
	if(priv->gDdSpiInfo[ch].forceStopFlg == 1){
		ret = DdSpiDriveBranch_FORCE_STOP;
	}

	// End SPI communication
	ddSpiEndProcess(self, ch);

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("gDdSpiInfo[%d].num = %u\n", ch, priv->gDdSpiInfo[ch].num));
	Ddim_Print(("gDdSpiInfo[%d].sendPos = %u\n", ch, priv->gDdSpiInfo[ch].sendPos));
#endif

	return ret;
}

void dd_spi_drive_branch_get_end_process(DdSpiDriveBranch* self, kuchar ch)
{
	ddSpiEndProcess(self, ch);
}

void dd_spi_drive_branch_get_send_data(DdSpiDriveBranch* self, kuchar ch)
{
	ddSpiSendData(self, ch);
}

void dd_spi_drive_branch_get_write_dummy_count(DdSpiDriveBranch* self, kuchar ch)
{
	ddSpiWriteDummyCount(self, ch);
}

kuint32 dd_spi_drive_branch_get_check_stopping_conditions(DdSpiDriveBranch* self, kuchar ch)
{
	return ddSpiCheckStoppingConditions(self, ch);
}

TDdSpiInfo dd_spi_drive_branch_get_spi_info(DdSpiDriveBranch* self, kuchar ch)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	return priv->gDdSpiInfo[ch];
}

void dd_spi_drive_branch_set_spi_info_pcallback(DdSpiDriveBranch* self, kuchar ch, VpSpiCallback pCallback)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].pCallback = pCallback;
}

void dd_spi_drive_branch_set_spi_info_pcallback_ss(DdSpiDriveBranch* self, kuchar ch, VpSpiSsCallback pCallbackSs)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].pCallbackSs = pCallbackSs;
}

void dd_spi_drive_branch_set_spi_info_send_addr32(DdSpiDriveBranch* self, kuchar ch, kuint32* sendAddr32)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].sendAddr32 = sendAddr32;
}

void dd_spi_drive_branch_set_spi_info_send_addr16(DdSpiDriveBranch* self, kuchar ch, kushort* sendAddr16)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].sendAddr16 = sendAddr16;
}

void dd_spi_drive_branch_set_spi_info_send_addr8(DdSpiDriveBranch* self, kuchar ch, kuchar* sendAddr8)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].sendAddr8 = sendAddr8;
}

void dd_spi_drive_branch_set_spi_info_send_pos(DdSpiDriveBranch* self, kuchar ch, kuint32 sendPos)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].sendPos = sendPos;
}

void dd_spi_drive_branch_set_spi_info_recv_addr32(DdSpiDriveBranch* self, kuchar ch, kuint32* recvAddr32)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].recvAddr32 = recvAddr32;
}

void dd_spi_drive_branch_set_spi_info_recv_addr16(DdSpiDriveBranch* self, kuchar ch, kushort* recvAddr16)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].recvAddr16 = recvAddr16;
}

void dd_spi_drive_branch_set_spi_info_recv_addr8(DdSpiDriveBranch* self, kuchar ch, kuchar* recvAddr8)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].recvAddr8 = recvAddr8;
}

void dd_spi_drive_branch_set_spi_info_recv_pos(DdSpiDriveBranch* self, kuchar ch, kuint32 recvPos)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].recvPos = recvPos;
}

void dd_spi_drive_branch_set_spi_info_add_recv_pos(DdSpiDriveBranch* self, kuchar ch, kuint32 recvPos)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].recvPos += recvPos;
}

void dd_spi_drive_branch_set_spi_info_num(DdSpiDriveBranch* self, kuchar ch, kuint32 num)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].num = num;
}

void dd_spi_drive_branch_set_spi_info_dummy_count(DdSpiDriveBranch* self, kuchar ch, kuint32 dummyCount)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].dummyCount = dummyCount;
}

void dd_spi_drive_branch_set_spi_info_force_stop_flg(DdSpiDriveBranch* self, kuchar ch, kuchar forceStopFlg)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].forceStopFlg = forceStopFlg;
}

void dd_spi_drive_branch_set_spi_info_dma_wait(DdSpiDriveBranch* self, kuchar ch, kuchar dmaWait)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].dmaWait = dmaWait;
}

void dd_spi_drive_branch_set_spi_info_spi_mode(DdSpiDriveBranch* self, kuchar ch, EDdSpiDir spiMode)
{
	DdSpiDriveBranchPrivate *priv = DD_SPI_DRIVE_BRANCH_GET_PRIVATE(self);
	priv->gDdSpiInfo[ch].spiMode = spiMode;
}

DdSpiDriveBranch* dd_spi_drive_branch_new(void)
{
	DdSpiDriveBranch* self = k_object_new_with_private(DD_TYPE_SPI_DRIVE_BRANCH, sizeof(DdSpiDriveBranchPrivate));
	return self;
}
