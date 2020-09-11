/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :SPI(Serial Peripheral Interface) driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include <string.h>
#include "spi.h"
#include "peripheral.h"
#include "dd_hdmac1.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "dd_arm.h"
#include "ddspicolabo.h"

#include "ddspi.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdSpi, dd_spi);
#define DD_SPI_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdSpiPrivate, DD_TYPE_SPI))

struct _DdSpiPrivate
{
    kint a;
};

static void dd_spi_constructor(DdSpi *self)
{
	DdSpiPrivate *priv = DD_SPI_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_spi_destructor(DdSpi *self)
{

}

/*
 * PUBLIC
 */
// Interrupt Handler of SPI.
void dd_spi_int_handler(kuchar ch)
{
	kuint32 remainNum;
	kuint32 fifoLevel;
	kuint32 readSize = 0;
	kuint32 readCount = 0;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return;
	}
#endif

	// ssOut(Master)/ssIn(Slave) interrupt
	if((IO_SPI[ch].INT_EN.bit.XFERDONEPULSE == 1) && (IO_SPI[ch].INT_ST.bit.XFERDONEPULSE == 1)){
		// Clear interrupt(XFERDONEPULSE bit)
		IO_SPI[ch].INT_CLR.word |= DdSpiDriveBranch_INT_XFERDONEPULSE_BIT;
		DdSpiDriveBranch_DD_SPI_DSB();

		if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).pCallbackSs != NULL){
			((void(*)())dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).pCallbackSs)(ch);
		}
	}

	// Receive FIFO Overflow interrupt
	if((IO_SPI[ch].INT_EN.bit.RXFIFOOVERFLOW == 1) && (IO_SPI[ch].INT_ST.bit.RXFIFOOVERFLOW == 1)){
		// Clear interrupt(RXFIFOOVERFLOW bit)
		IO_SPI[ch].INT_CLR.word |= DdSpiDriveBranch_INT_RXFIFOOVERFLOW_BIT;
		DdSpiDriveBranch_DD_SPI_DSB();

		// End SPI communication
		dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), ch);

		if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).pCallback != NULL){
			((void(*)())dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).pCallback)(ch,
					DdSpiDriveBranch_RECV_OVERRUN_ERROR);
		}
		return;
	}

	// Tx FIFO Empty interrupt
	if((IO_SPI[ch].INT_EN.bit.TXEMPTYPULSE == 1) && (IO_SPI[ch].INT_ST.bit.TXEMPTYPULSE == 1)){
		// Clear interrupt(TXEMPTYPULSE bit)
		IO_SPI[ch].INT_CLR.word |= DdSpiDriveBranch_INT_TXEMPTYPULSE_BIT;
		DdSpiDriveBranch_DD_SPI_DSB();

		if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).dmaWait == 2){
			// End SPI communication
			dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), ch);

			if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).pCallback != NULL){
				((void(*)())dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).pCallback)(ch,
						dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
								DdSpiDriveBranch_SEND).result);
			}
			return;
		}
		else {
			if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).spiMode
					== DdSpiDriveBranch_DIR_RECV){
				// Master receiving
				if(IO_SPI[ch].CTRL.bit.MASTER == DdSpiDriveBranch_TYPE_MASTER){
					// Set remain dummy count
					if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).dummyCount
							< dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num){
						// Set remain dummy count
						dd_spi_drive_get_branch_write_dummy_count(dd_spi_drive_get(), ch);

#ifdef CO_DEBUG_ON_PC
						Ddim_Print(("gDD_SPI_Info[%d].num = %u\n", ch,
								dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num));
						Ddim_Print(("gDD_SPI_Info[%d].recvPos = %u\n", ch,
								dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvPos));
						Ddim_Print(("gDD_SPI_Info[%d].dummyCount = %u\n", ch,
								dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).dummyCount));
#endif
					}
				}
			}
			else {
				// Send data
				dd_spi_drive_get_branch_send_data(dd_spi_drive_get(), ch);

#ifdef CO_DEBUG_ON_PC
				Ddim_Print(("gDD_SPI_Info[%d].num = %u\n", ch,
						dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num));
				Ddim_Print(("gDD_SPI_Info[%d].sendPos = %u\n", ch,
						dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).sendPos));
#endif

				// Check remain data
				if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).sendPos
						>= dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num){
					// End SPI communication
					dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), ch);

					if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).pCallback != NULL){
						((void(*)())dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(),
								ch).pCallback)(ch, D_DDIM_OK);
					}
					return;
				}
			}
		}
	}

	// TX FIFO Watermark Level interrupt
	if((IO_SPI[ch].INT_EN.bit.TXWMARKPULSE == 1) && (IO_SPI[ch].INT_ST.bit.TXWMARKPULSE == 1)){
		// Clear interrupt(TXWMARKPULSE bit)
		IO_SPI[ch].INT_CLR.word |= DdSpiDriveBranch_INT_TXWMARKPULSE_BIT;
		DdSpiDriveBranch_DD_SPI_DSB();

		if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).spiMode
				== DdSpiDriveBranch_DIR_RECV){
			// Master receiving
			if(IO_SPI[ch].CTRL.bit.MASTER == DdSpiDriveBranch_TYPE_MASTER){
				// Set remain dummy count
				if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).dummyCount
						< dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num){
					// Set remain dummy count
					dd_spi_drive_get_branch_write_dummy_count(dd_spi_drive_get(), ch);

#ifdef CO_DEBUG_ON_PC
					Ddim_Print(("gDD_SPI_Info[%d].num = %u\n", ch,
							dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num));
					Ddim_Print(("gDD_SPI_Info[%d].recvPos = %u\n", ch,
							dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvPos));
					Ddim_Print(("gDD_SPI_Info[%d].dummyCount = %u\n", ch,
							dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).dummyCount));
#endif
				}
			}
		}
		else {
			// Send data
			dd_spi_drive_get_branch_send_data(dd_spi_drive_get(), ch);

#ifdef CO_DEBUG_ON_PC
			Ddim_Print(("gDD_SPI_Info[%d].num = %u\n", ch,
					dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num));
			Ddim_Print(("gDD_SPI_Info[%d].sendPos = %u\n", ch,
					dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).sendPos));
#endif
		}
	}

	// Rx FIFO Watermark Level interrupt
	if(((IO_SPI[ch].INT_EN.bit.RXWMARKPULSE == 1) && (IO_SPI[ch].INT_ST.bit.RXWMARKPULSE == 1)) ||
		((IO_SPI[ch].INT_EN.bit.RXFULLPULSE == 1) && (IO_SPI[ch].INT_ST.bit.RXFULLPULSE == 1)) ||
		((IO_SPI[ch].INT_EN.bit.RXTIMEOUT == 1) && (IO_SPI[ch].INT_ST.bit.RXTIMEOUT == 1))){

		// Clear interrupt
		if(IO_SPI[ch].INT_ST.bit.RXWMARKPULSE == 1){
			IO_SPI[ch].INT_CLR.word |= DdSpiDriveBranch_INT_RXWMARKPULSE_BIT;
			DdSpiDriveBranch_DD_SPI_DSB();
		}
		if(IO_SPI[ch].INT_ST.bit.RXFULLPULSE == 1){
			IO_SPI[ch].INT_CLR.word |= DdSpiDriveBranch_INT_RXFULLPULSE_BIT;
			DdSpiDriveBranch_DD_SPI_DSB();
		}
		if(IO_SPI[ch].INT_ST.bit.RXTIMEOUT == 1){
			IO_SPI[ch].INT_CLR.word |= DdSpiDriveBranch_INT_RXTIMEOUT_BIT;
			DdSpiDriveBranch_DD_SPI_DSB();
		}

		remainNum = dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num
				- dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvPos;
		fifoLevel = IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL;
		if(remainNum < fifoLevel){
			// guard
			readSize = remainNum;
		}
		else {
			readSize = fifoLevel;
		}

		if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
			while(readCount < readSize){
				// Read data word from the RX Serial Data Register.
				*(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvAddr32
						+ dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvPos
						+ readCount) = IO_SPI[ch].RXDATA;
				readCount++;
			}
		}
		else if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
			while(readCount < readSize){
				// Read data word from the RX Serial Data Register.
				*(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvAddr16
						+ dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvPos
						+ readCount) = IO_SPI[ch].RXDATA;
				readCount++;
			}
		}
		else {
			// IO_SPI[ch].AUX_CTRL.bit.BITSIZE <= E_DD_SPI_BIT_LEN_8
			while(readCount < readSize){
				// Read data word from the RX Serial Data Register.
				*(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvAddr8
						+ dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvPos
						+ readCount) = IO_SPI[ch].RXDATA;
				readCount++;
			}
		}

		dd_spi_drive_set_branch_spi_info_add_recv_pos(dd_spi_drive_get(), ch, readCount);

		// Check remain data
		if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvPos
				>= dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num){
			// End SPI communication
			dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), ch);

			if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).pCallback != NULL){
				((void(*)())dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(),
						ch).pCallback)(ch, D_DDIM_OK);
			}
		}

#ifdef CO_DEBUG_ON_PC
		Ddim_Print(("gDD_SPI_Info[%d].num = %u\n", ch,
				dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).num));
		Ddim_Print(("gDD_SPI_Info[%d].recvPos = %u\n", ch,
				dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), ch).recvPos));
#endif
	}
}

DdSpi* dd_spi_new(void)
{
	DdSpi* self = k_object_new_with_private(DD_TYPE_SPI, sizeof(DdSpiPrivate));
	return self;
}
