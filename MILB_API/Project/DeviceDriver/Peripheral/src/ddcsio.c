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
 * @file		dd_csio.c
 * @brief		Clock Synchronous Serial Interface driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "ddcsio.h"
#include "ddcsiocommon.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdCsio, dd_csio);

#define DD_CSIO_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdCsioPrivate, DD_TYPE_CSIO))

#ifdef CO_DDIM_UTILITY_USE
#define DdCsio_DD_CSIO_DMA_RESET_FOR_M7M
#ifdef DdCsio_DD_CSIO_DMA_RESET_FOR_M7M
#define C_CSIO_DMACA_RESET_WAIT_TIME	(10)
#endif // DdCsio_DD_CSIO_DMA_RESET_FOR_M7M
#endif


#ifdef CO_DDIM_UTILITY_USE
typedef struct _DdCsioDmaBtInfo DdCsioDmaBtInfo;
#endif

#ifdef CO_DDIM_UTILITY_USE
/* CSIO DMA beat type information */
struct _DdCsioDmaBtInfo
{
	kulong beatNum;
	kulong shiftNum;
	kulong dmaRegi;
};
#endif

struct _DdCsioPrivate
{

};


#ifdef CO_DDIM_UTILITY_USE
#ifdef DdCsio_DD_CSIO_DMA_RESET_FOR_M7M
static volatile kuchar S_GDD_CSIO_DMA_RESET_BUFF[16];
#endif // DdCsio_DD_CSIO_DMA_RESET_FOR_M7M
#endif

/**
DECLS
*/

/**
IMPL
*/
static void dd_csio_constructor(DdCsio *self)
{
//	DdCsioPrivate *priv = DD_CSIO_GET_PRIVATE(self);
}

static void dd_csio_destructor(DdCsio *self)
{
//	DdCsioPrivate *priv = DD_CSIO_GET_PRIVATE(self);
	if(self->fifoCtrl){
		k_free(self->fifoCtrl);
		self->fifoCtrl=NULL;
	}
	if(self->pcallback){
		k_free(self->pcallback);
		self->pcallback=NULL;
	}
}
/**
PUBLIC
*/
/**
 * @brief	Open channel for using. Each CSIO channel is exclusively controlled
 Return NG when the specified channel is occupied by some other task
 * @param	kuchar	ch
 * @param	kint32	tmout
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR / C_CSIO_SEM_TIMEOUT / C_CSIO_SEM_NG
 */
kint32 dd_csio_open (DdCsio *self, kuchar ch, kint32 tmout)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("CSIO: input param error. tmout = %x\n", tmout));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	if (tmout == DdimUserCustom_SEM_WAIT_POL) {
		ercd = ddim_user_custom_pol_sem(NULL, SID_DD_USIO(ch));
	} else {
		ercd = ddim_user_custom_twai_sem(NULL, SID_DD_USIO(ch), (DdimUserCustom_TMO) tmout);
	}

	if (ercd != DdimUserCustom_E_OK) {
		if ( DdimUserCustom_E_TMOUT == ercd) {
			return C_CSIO_SEM_TIMEOUT;
		}
		return C_CSIO_SEM_NG;
	}

//	gDD_USIO_State[ch] = DdUart_D_DD_USIO_EXC_CSIO;
	dd_uart_set_usio_state(dd_uart_get(), ch, DdUart_D_DD_USIO_EXC_CSIO);
	return D_DDIM_OK;
}

/**
 * @brief	Close the specified channel.
 * @param	kuchar	ch
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_close(DdCsio *self, kuchar ch)
{
	DdimUserCustom_ER	ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

//	gDD_USIO_State[ch] = DdUart_D_DD_USIO_EXC_OFF;
	dd_uart_set_usio_state(dd_uart_get(), ch, DdUart_D_DD_USIO_EXC_OFF);
	ercd = ddim_user_custom_sig_sem(NULL, SID_DD_USIO(ch));

	if ( DdimUserCustom_E_OK != ercd) {
		return C_CSIO_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Set CSIO operation condition and callback function for the specified channel
 * @param	kuchar			ch
			DdCsio*	self
 * @return	kint32			D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_ctrl(kuchar ch, DdCsio const* const self)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (self == NULL) {
		Ddim_Assertion(("CSIO input param error. [self] = NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	memset((void*) &gddCsioInfo[ch], 0, sizeof(DdCsioInfo));

	// Setting register for each CSIO channel.
	//Initialize
	ioUsio.csio[ch].scr.byte = 0x00;
	/*	ioUsio.csio[ch].smr.byte = 0x00;*/
	ioUsio.csio[ch].escr.byte = 0x00;
	ioUsio.csio[ch].dr.hword = 0x0000;
	ioUsio.csio[ch].bgr.hword = 0x0000;
	ioUsio.csio[ch].scr.bit.upcl = 1; // Soft-Reset
	ioUsio.csio[ch].smr.bit.md = 2; // fixed, CSIO Transferring

	// SCR register setting
	ioUsio.csio[ch].scr.bit.ms = self->type; //Master/Slave selection bit

	// SMR register setting
	ioUsio.csio[ch].smr.bit.bds = (kuchar) self->bitDirection; // Bit Direction, LSB first or MSB first

	// Set SMR.scke=1 if using CSIO as master, else scke=0
	if (self->type == DdCsio_DD_CSIO_TYPE_MASTER) {
		ioUsio.csio[ch].smr.bit.scke = 1;
	} else {
		ioUsio.csio[ch].smr.bit.scke = 0;
	}

	// ESCR register setting
	ioUsio.csio[ch].escr.bit.l = self->dataLength;
	ioUsio.csio[ch].escr.bit.sop = self->sop;

	// BGR register setting
	ioUsio.csio[ch].bgr.hword = self->baudrate;

	// Transmit mode setting. Set register related to transmit mode
	if (self->mode == DdCsio_DD_CSIO_MODE_NORMAL_SC_H) {
		ioUsio.csio[ch].smr.bit.scinv = 0;
	} else if (self->mode == DdCsio_DD_CSIO_MODE_NORMAL_SC_L) {
		ioUsio.csio[ch].smr.bit.scinv = 1;
	} else if (self->mode == DdCsio_DD_CSIO_MODE_SPI_SC_H) {
		ioUsio.csio[ch].scr.bit.spi = 1;
		ioUsio.csio[ch].smr.bit.scinv = 0;
	} else {	// DdCsio_DD_CSIO_MODE_SPI_SC_L
		ioUsio.csio[ch].scr.bit.spi = 1;
		ioUsio.csio[ch].smr.bit.scinv = 1;
	}

	// Callback function
	gddCsioInfo[ch].pcallback = self->pcallback; //Callback function pointer

	// FIFO setting
	if (self->fifoCtrl == NULL) {
		ioUsio.csio[ch].fcr.hword = 0x000C; //FIFO not used and FIFO reset
		return D_DDIM_OK;
	}
	ioUsio.csio[ch].fcr.hword = 0x000C; // Initialize
	ioUsio.csio[ch].fcr.bit.fsel = self->fifoCtrl->fsel; //fifo selection bit
	ioUsio.csio[ch].fcr.bit.fset = self->fifoCtrl->fset; //fifo transfer reload pointer storing bit
	ioUsio.csio[ch].fcr.bit.flste = self->fifoCtrl->flste; //data-lost check permmision bit
	ioUsio.csio[ch].fcr.bit.fe1 = self->fifoCtrl->fe1; //FIFO1 enable
	ioUsio.csio[ch].fcr.bit.fe2 = self->fifoCtrl->fe2; //FIFO2 enable
	ioUsio.csio[ch].fbyte.hword = 0x0000; //FBYE initial value

	if (self->fifoCtrl->fsel == 0) {
		ioUsio.csio[ch].fbyte.byte[1] = self->fifoCtrl->fbyteRecv; //FIFO2
	} else {
		ioUsio.csio[ch].fbyte.byte[0] = self->fifoCtrl->fbyteRecv; //FIFO1
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get CSIO operation condition and callback function for the specified channel
 * @param	kuchar			ch
 DdCsio*	self
 * @return	kint32			D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_get_ctrl(kuchar ch, DdCsio* const self)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (self == NULL) {
		Ddim_Assertion(("CSIO input param error. [self] = NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	self->type = (DdCsioType) ioUsio.csio[ch].scr.bit.ms;
	self->bitDirection = (DdCsioBitDir) ioUsio.csio[ch].smr.bit.bds;
	self->dataLength = (DdCsioDataLength) ioUsio.csio[ch].escr.bit.l;
	self->sop = ioUsio.csio[ch].escr.bit.sop;
	self->baudrate = ioUsio.csio[ch].bgr.hword;

	if (ioUsio.csio[ch].scr.bit.spi == 1) {
		if (ioUsio.csio[ch].smr.bit.scinv == 1) {
			self->mode = DdCsio_DD_CSIO_MODE_SPI_SC_L;
		} else {
			self->mode = DdCsio_DD_CSIO_MODE_SPI_SC_H;
		}
	} else {
		if (ioUsio.csio[ch].smr.bit.scinv == 1) {
			self->mode = DdCsio_DD_CSIO_MODE_NORMAL_SC_L;
		} else {
			self->mode = DdCsio_DD_CSIO_MODE_NORMAL_SC_H;
		}
	}

	self->pcallback = gddCsioInfo[ch].pcallback;

	if (self->fifoCtrl == NULL) {
		return D_DDIM_OK;
	}

	self->fifoCtrl->flste = ioUsio.csio[ch].fcr.bit.flste;
	self->fifoCtrl->fsel = ioUsio.csio[ch].fcr.bit.fsel;
	self->fifoCtrl->fset = ioUsio.csio[ch].fcr.bit.fset;
	self->fifoCtrl->fe2 = ioUsio.csio[ch].fcr.bit.fe2;
	self->fifoCtrl->fe1 = ioUsio.csio[ch].fcr.bit.fe1;

	if (self->fifoCtrl->fsel == 0) {
		self->fifoCtrl->fbyteRecv = ioUsio.csio[ch].fbyte.bit.__fifo2;
	} else {
		self->fifoCtrl->fbyteRecv = ioUsio.csio[ch].fbyte.bit.__fifo1;
	}

	return D_DDIM_OK;
}


kint32 dd_csio_set_baudrate(DdCsio *self, kuchar ch, kuint16 baudRate )
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif
	ioUsio.csio[ch].bgr.hword = baudRate;
	return D_DDIM_OK;
}


kint32 dd_csio_get_baudrate(DdCsio *self,kuchar ch, kuint16* baudRate )
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (baudRate == NULL) {
		Ddim_Assertion(("CSIO input param error. [baudRate] = NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif
	*baudRate = ioUsio.csio[ch].bgr.hword;
	return D_DDIM_OK;
}

kint32 dd_csio_save_send_fifo_pointer(DdCsio *self, kuchar ch, kuchar lostDetect )
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if ((lostDetect != 0) && (lostDetect != 1)) {
		Ddim_Assertion(("CSIO input param error. [lostDetect] = %d\n", lostDetect));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	// Check exist data in send fifo
	if (ioUsio.csio[ch].fbyte.byte[ioUsio.csio[ch].fcr.bit.fsel] != 0) {
		return C_CSIO_DATA_EXIST_ERROR;
	}

	// Save Read Pointer
	ioUsio.csio[ch].fcr.bit.fset = 1;

	// Enable/Disable data lost detection (flst)
	ioUsio.csio[ch].fcr.bit.flste = lostDetect;
	return D_DDIM_OK;
}


kint32 dd_csio_reload_send_fifo_pointer(DdCsio *self, kuchar ch )
{
	kuchar fe1;
	kuchar fe2;
	kuint32 waitCnt = 0;
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	if (ioUsio.csio[ch].fcr.bit.flst == 1) {
		// Reload data lost
		return C_CSIO_OVERWRITE_ERROR;
	}

	// Keep to temporary
	fe1 = ioUsio.csio[ch].fcr.bit.fe1;
	fe2 = ioUsio.csio[ch].fcr.bit.fe2;

	// Disable send/receive
	ioUsio.csio[ch].fcr.bit.fe1 = 0;
	ioUsio.csio[ch].fcr.bit.fe2 = 0;
	ioUsio.csio[ch].scr.bit.tie = 0;
	ioUsio.csio[ch].scr.bit.tbie = 0;
	ioUsio.csio[ch].fcr.bit.ftie = 0;

	// Reload Send FIFO
	ioUsio.csio[ch].fcr.bit.fld = 1;

	// Enable send permission
	ioUsio.csio[ch].smr.bit.soe = 1;
	ioUsio.csio[ch].scr.bit.txe = 1;

	// Set keep value
	ioUsio.csio[ch].fcr.bit.fe1 = fe1;
	ioUsio.csio[ch].fcr.bit.fe2 = fe2;

	// Subtract the number of resend   ???
//	if( ioUsio.csio[ch].fbyte.byte[ioUsio.csio[ch].fcr.bit.fsel] >= gddCsioInfo[ch].sendPos ){
//		gddCsioInfo[ch].sendPos -= ioUsio.csio[ch].fbyte.byte[ioUsio.csio[ch].fcr.bit.fsel];
//	}

	if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
		ioUsio.csio[ch].fcr.bit.fdrq = 0;
		ioUsio.csio[ch].fcr.bit.ftie = 1;
		DdCsioCommon_DD_CSIO_DSB();
	} else {	// Interrupt is disable
		while (ioUsio.csio[ch].ssr.bit.__tbi == 0) {
			// wait until TDR empty
			ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
			if (ret != D_DDIM_OK) {
				return ret;
			}
			waitCnt++;
		}
		if (gddCsioInfo[ch].forceStopFlg == 1) {
			dd_csio_common_end(dd_csio_common_get(), ch);
			return C_CSIO_FORCE_STOP;
		}
		// End csio communication
		dd_csio_common_end(dd_csio_common_get(), ch);
	}

	return D_DDIM_OK;
}


kint32 dd_csio_get_reload_status(DdCsio *self, kuchar ch )
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	return ioUsio.csio[ch].fcr.bit.fld;
}


kint32 dd_csio_reset_fifo(DdCsio *self, kuchar ch, kuchar fifoNum )
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if ((fifoNum < C_CSIO_SELECT_FIFO_1) || (fifoNum > C_CSIO_SELECT_FIFO_BOTH)) {
		Ddim_Assertion(("CSIO input param error. [fifoNum] = %d\n", fifoNum));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	ioUsio.csio[ch].scr.bit.txe = 0;
	ioUsio.csio[ch].scr.bit.rxe = 0;
	ioUsio.csio[ch].fcr.bit.ftie = 0;

	// Reset FIFO
	ioUsio.csio[ch].fcr.hword |= fifoNum << 2;
	// C_CSIO_SELECT_FIFO_1		(1)// C_CSIO_SELECT_FIFO_2		(2)// C_CSIO_SELECT_FIFO_BOTH	(3)
	DdCsioCommon_DD_CSIO_DSB();
	return D_DDIM_OK;
}

/**
 * @brief	Set data information to send by CSIO
 * @param	kuchar	ch
			void*	sendAddr
			kuint32	num
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_set_send_data(DdCsio *self, kuchar ch, void const* const sendAddr, kuint32 num)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (sendAddr == NULL) {
		Ddim_Assertion(("CSIO input param error. [sendAddr] = NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (num == 0) {
		Ddim_Assertion(("CSIO input param error. [num] = %d\n", num));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioInfo[ch].sendAddr16 = (kuint16*) sendAddr;
	} else {
		gddCsioInfo[ch].sendAddr8 = (kuchar*) sendAddr;
	}

	gddCsioInfo[ch].num = num;
	gddCsioInfo[ch].sendPos = 0;
	gddCsioInfo[ch].dmaWait = 0;
	return D_DDIM_OK;
}

/**
 * @brief	Start sending data
 * @param	kuchar	ch
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR / C_CSIO_FORCE_STOP / C_CSIO_TIMEOUT
 */
kint32 dd_csio_start_send(DdCsio *self, kuchar ch)
{
	kuint32 waitCnt = 0;
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	ioUsio.csio[ch].smr.bit.soe = 1; //Serial data output permission bit
	ioUsio.csio[ch].scr.bit.rxe = 0; //Disable receive permission bit
	ioUsio.csio[ch].scr.bit.txe = 1; //Enable transfer permission bit

	if (((ioUsio.csio[ch].fcr.bit.fsel == 0) && (ioUsio.csio[ch].fcr.bit.fe1 == 1))
			|| ((ioUsio.csio[ch].fcr.bit.fsel == 1) && (ioUsio.csio[ch].fcr.bit.fe2 == 1))) {
		// FIFO use
		while (ioUsio.csio[ch].fcr.bit.fdrq == 0) {
			// wait until FIFO empty
			ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
			if (ret != D_DDIM_OK) {
				return ret;
			}
			waitCnt++;
		}
		waitCnt = 0;

		if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
			while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				ioUsio.csio[ch].dr.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
				gddCsioInfo[ch].sendPos++;

				if (ioUsio.csio[ch].fcr.bit.fdrq == 1) {// FIFO is not full? (0:full, 1:empty)
					continue;
				} else {	//FIFO is full
					if(gddCsioInfo[ch].pcallback){	// Interrupt enable?
						ioUsio.csio[ch].fcr.bit.fdrq = 0;
						ioUsio.csio[ch].fcr.bit.ftie = 1;
						DdCsioCommon_DD_CSIO_DSB();
						return D_DDIM_OK;
					} else {	// Interrupt is disable
						while (ioUsio.csio[ch].fcr.bit.fdrq == 0) {
							// wait until FIFO empty
							ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
							if (ret != D_DDIM_OK) {
								return ret;
							}
							waitCnt++;
						}
						waitCnt = 0;
					}
				}
			}
		} else {
			while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				ioUsio.csio[ch].dr.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
				gddCsioInfo[ch].sendPos++;

				if (ioUsio.csio[ch].fcr.bit.fdrq == 1) {// FIFO is not full? (0:full, 1:empty)
					continue;
				} else {	//FIFO is full
					if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
						ioUsio.csio[ch].fcr.bit.fdrq = 0;
						ioUsio.csio[ch].fcr.bit.ftie = 1;
						DdCsioCommon_DD_CSIO_DSB();
						return D_DDIM_OK;
					} else {	// Interrupt is disable
						while (ioUsio.csio[ch].fcr.bit.fdrq == 0) {
							// wait until FIFO empty
							ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
							if (ret != D_DDIM_OK) {
								return ret;
							}
							waitCnt++;
						}
						waitCnt = 0;
					}
				}
			}
		}

		// All data was written
		if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
			if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				ioUsio.csio[ch].fcr.bit.fdrq = 0;
				ioUsio.csio[ch].fcr.bit.ftie = 1;
			} else {
				ioUsio.csio[ch].scr.bit.tbie = 1;
			}
			DdCsioCommon_DD_CSIO_DSB();
		} else {	// Interrupt is disable
			while (ioUsio.csio[ch].ssr.bit.__tbi == 0) {
				// wait until TDR empty
				ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
				if (ret != D_DDIM_OK) {
					return ret;
				}
				waitCnt++;
			}
			waitCnt = 0;
			if (gddCsioInfo[ch].forceStopFlg == 1) {
				dd_csio_common_end(dd_csio_common_get(), ch);
				return C_CSIO_FORCE_STOP;
			}
			// End csio communication
			dd_csio_common_end(dd_csio_common_get(), ch);
		}
	} else {
		// FIFO not use
		if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
			while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				while (ioUsio.csio[ch].ssr.bit.__tdre == 0) {
					// wait until TDR empty
					ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
					if (ret != D_DDIM_OK) {
						return ret;
					}
					waitCnt++;
				}
				waitCnt = 0;
				if (gddCsioInfo[ch].forceStopFlg == 1) {
					dd_csio_common_end(dd_csio_common_get(), ch);
					return C_CSIO_FORCE_STOP;
				}

				ioUsio.csio[ch].dr.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
				gddCsioInfo[ch].sendPos++;

				if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
					ioUsio.csio[ch].scr.bit.tie = 1;
					DdCsioCommon_DD_CSIO_DSB();
					return D_DDIM_OK;
				}
			}
		} else {
			while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				while (ioUsio.csio[ch].ssr.bit.__tdre == 0) {
					// wait until TDR empty
					ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
					if (ret != D_DDIM_OK) {
						return ret;
					}
					waitCnt++;
				}
				waitCnt = 0;
				if (gddCsioInfo[ch].forceStopFlg == 1) {
					dd_csio_common_end(dd_csio_common_get(), ch);
					return C_CSIO_FORCE_STOP;
				}

				ioUsio.csio[ch].dr.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
				gddCsioInfo[ch].sendPos++;

				if (gddCsioInfo[ch].pcallback) {	 //Interrupt enable?
					ioUsio.csio[ch].scr.bit.tie = 1;
					DdCsioCommon_DD_CSIO_DSB();
					return D_DDIM_OK;
				}
			}
		}

		// All data was written
		if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
			if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				ioUsio.csio[ch].scr.bit.tie = 1;
			} else {
				ioUsio.csio[ch].scr.bit.tbie = 1;
			}
			DdCsioCommon_DD_CSIO_DSB();
		} else { //Interrupt is disable
			while (ioUsio.csio[ch].ssr.bit.__tbi == 0) {
				// wait until TDR empty
				ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
				if (ret != D_DDIM_OK) {
					return ret;
				}
				waitCnt++;
			}
			waitCnt = 0;
			if (gddCsioInfo[ch].forceStopFlg == 1) {
				dd_csio_common_end(dd_csio_common_get(), ch);
				return C_CSIO_FORCE_STOP;
			}
			// End csio communication
			dd_csio_common_end(dd_csio_common_get(), ch);
		}
	}

	return D_DDIM_OK;
}


/**
 * @brief	Set data information to receive by CSIO
 * @param	kuchar	ch
 void*	recvAddr
 kuint32	num
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_set_recv_data(DdCsio *self, kuchar ch, void const* const recvAddr, kuint32 num)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (recvAddr == NULL) {
		Ddim_Assertion(("CSIO input param error. [recvAddr] = NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (num == 0) {
		Ddim_Assertion(("CSIO input param error. [num] = %d\n", num));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		gddCsioInfo[ch].recvAddr16 = (kuint16*) recvAddr;
	} else {
		gddCsioInfo[ch].recvAddr8 = (kuchar*) recvAddr;
	}

	gddCsioInfo[ch].num = num;
	gddCsioInfo[ch].recvPos = 0;
	gddCsioInfo[ch].recvWait = 0;
	gddCsioInfo[ch].dmaWait = 0;
	return D_DDIM_OK;
}

/**
 * @brief	Start receiving data
 * @param	kuchar	ch
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR / C_CSIO_FORCE_STOP
 */
kint32 dd_csio_start_recv(DdCsio *self, kuchar ch)
{
	kuint32 waitCnt = 0;
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	ioUsio.csio[ch].smr.bit.soe = 0; //Serial data output permission bit
	ioUsio.csio[ch].scr.bit.rxe = 1; //Enable receive permission bit
	ioUsio.csio[ch].scr.bit.txe = 1; //Disable transfer permission bit

	if (gddCsioInfo[ch].pcallback) { //Interrupt enable?
		//Dummy data for master receiving
		if (ioUsio.csio[ch].scr.bit.ms == 0) {
			ioUsio.csio[ch].dr.hword = 0;
		}
		ioUsio.csio[ch].fcr.bit.friie = 1;
		ioUsio.csio[ch].scr.bit.rie = 1;
		DdCsioCommon_DD_CSIO_DSB();
	} else { //Interrupt is disble
		if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
			while (gddCsioInfo[ch].recvPos < gddCsioInfo[ch].num) {
				// Dummy data for master receiving
				if (ioUsio.csio[ch].scr.bit.ms == 0) {
					ioUsio.csio[ch].dr.hword = 0;
					DdCsioCommon_DD_CSIO_DSB();
				}

				// Wait until RDR filled up with data
				while (ioUsio.csio[ch].ssr.bit.__rdrf == 0) {
					// wait until TDR empty
					ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
					if (ret != D_DDIM_OK) {
						return ret;
					}
					waitCnt++;
				}

				// Check for buffer overrun error
				if (ioUsio.csio[ch].ssr.bit.__ore == 1) {
					// Clear buffer overrun error
					ioUsio.csio[ch].ssr.byte |= C_CSIO_SSR_REC_BIT;
					DdCsioCommon_DD_CSIO_DSB();
					return C_CSIO_RECV_OVERRUN_ERROR;
				}

				*(gddCsioInfo[ch].recvAddr16 + gddCsioInfo[ch].recvPos) = ioUsio.csio[ch].dr.hword;
				gddCsioInfo[ch].recvPos++;
			}
		} else {
			while (gddCsioInfo[ch].recvPos < gddCsioInfo[ch].num) {
				// Dummy data for master receiving
				if (ioUsio.csio[ch].scr.bit.ms == 0) {
					ioUsio.csio[ch].dr.hword = 0;
					DdCsioCommon_DD_CSIO_DSB();
				}

				// Wait until RDR filled up with data
				while (ioUsio.csio[ch].ssr.bit.__rdrf == 0) {
					// wait until TDR empty
					ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
					if (ret != D_DDIM_OK) {
						return ret;
					}
					waitCnt++;
				}

				// Check for buffer overrun error
				if (ioUsio.csio[ch].ssr.bit.__ore == 1) {
					// Clear buffer overrun error
					ioUsio.csio[ch].ssr.byte |= C_CSIO_SSR_REC_BIT;
					DdCsioCommon_DD_CSIO_DSB();
					return C_CSIO_RECV_OVERRUN_ERROR;
				}

				*(gddCsioInfo[ch].recvAddr8 + gddCsioInfo[ch].recvPos) = ioUsio.csio[ch].dr.byte[0];
				gddCsioInfo[ch].recvPos++;
			}
		}
		// End csio communication
		dd_csio_common_end(dd_csio_common_get(), ch);
	}
	return D_DDIM_OK;
}

/**
 * @brief	Start full duplex communication
 * @param	kuchar	ch
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_start_full_duplex(DdCsio *self, kuchar ch)
{

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_D_DD_USIO_CH_NUM_MAX){
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	gddCsioInfo[ch].fullDuplex = 1;
	ioUsio.csio[ch].smr.bit.soe = 1; //Serial data output permission bit
	ioUsio.csio[ch].scr.bit.rxe = 1; //Disable receive permission bit
	ioUsio.csio[ch].scr.bit.txe = 1; //Enable transfer permission bit

	// FIFO setting (When the user doesn't set by CTRL)
	if ((ioUsio.csio[ch].fcr.bit.fe1 == 0) || (ioUsio.csio[ch].fcr.bit.fe2 == 0)) {
		ioUsio.csio[ch].fcr.bit.fsel = 0; //send:FIFO1, receive:FIFO2
		ioUsio.csio[ch].fcr.bit.fe1 = 1; //FIFO1 enable
		ioUsio.csio[ch].fcr.bit.fe2 = 1; //FIFO2 enable
	}

	// Send data
	if (ioUsio.csio[ch].escr.bit.l == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			ioUsio.csio[ch].dr.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
			DdCsioCommon_DD_CSIO_DSB();
			gddCsioInfo[ch].sendPos++;

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

			if (ioUsio.csio[ch].fcr.bit.fdrq == 0) {
				//FIFO is full (0:full, 1:empty)
				break;
			} else {
				// FIFO is not full
				continue;
			}
		}
	}

	if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
		ioUsio.csio[ch].fcr.bit.fdrq = 0;
		ioUsio.csio[ch].fcr.bit.ftie = 1;
	} else {
		ioUsio.csio[ch].scr.bit.tbie = 1;
	}

	while ((ioUsio.csio[ch].ssr.byte & 0x03) != 0x03) {
		// wait until TDR empty
	}

	DdCsioCommon_DD_CSIO_DSB();
	return D_DDIM_OK;
}

/**
 * @brief	Stop sending/receiving data(force stop)
 * @param	kuchar ch
 * @return	kint32		D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_stop(DdCsio *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdUart_D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	if (gddCsioInfo[ch].dmaWait == 1) {
		dd_hdmac1_stop(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_SEND].dmaCh);
		dd_hdmac1_close(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_SEND].dmaCh);
		dd_hdmac1_stop(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_RECV].dmaCh);
		dd_hdmac1_close(dd_hdmac1_get(), gddCsioDmaInfo[ch][C_CSIO_RECV].dmaCh);
		gddCsioInfo[ch].dmaWait = 0;
	}

	// Disable interrupt
	ioUsio.csio[ch].scr.bit.rie = 0;
	ioUsio.csio[ch].scr.bit.tie = 0;
	ioUsio.csio[ch].scr.bit.tbie = 0;
	ioUsio.csio[ch].fcr.bit.ftie = 0;
	ioUsio.csio[ch].fcr.bit.friie = 0;

	// Disable FIFO
	ioUsio.csio[ch].fcr.bit.fe1 = 0;
	ioUsio.csio[ch].fcr.bit.fe2 = 0;
	ioUsio.csio[ch].scr.bit.upcl = 1; //Soft-Reset

	// Disable send/receive
	ioUsio.csio[ch].scr.bit.txe = 0;
	ioUsio.csio[ch].scr.bit.rxe = 0;
	gddCsioInfo[ch].forceStopFlg = 1;
	DdCsioCommon_DD_CSIO_DSB();
	return D_DDIM_OK;
}

DdCsio* dd_csio_new(void)
{
	DdCsio* self = k_object_new_with_private(DD_TYPE_CSIO, sizeof(DdCsioPrivate));

	return self;
}
