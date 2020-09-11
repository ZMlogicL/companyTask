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
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("CSIO: input param error. tmout = %x\n", tmout));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	if (tmout == D_DDIM_USER_SEM_WAIT_POL) {
		ercd = DDIM_User_Pol_Sem(SID_DD_USIO(ch));
	} else {
		ercd = DDIM_User_Twai_Sem(SID_DD_USIO(ch), (DDIM_USER_TMO) tmout);
	}

	if (ercd != D_DDIM_USER_E_OK) {
		if ( D_DDIM_USER_E_TMOUT == ercd) {
			return C_CSIO_SEM_TIMEOUT;
		}
		return C_CSIO_SEM_NG;
	}

	gDD_USIO_State[ch] = D_DD_USIO_EXC_CSIO;
	return D_DDIM_OK;
}


/**
 * @brief	Close the specified channel.
 * @param	kuchar	ch
 * @return	kint32	D_DDIM_OK / C_CSIO_INPUT_PARAM_ERROR
 */
kint32 dd_csio_close(DdCsio *self, kuchar ch)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	gDD_USIO_State[ch] = D_DD_USIO_EXC_OFF;
	ercd = DDIM_User_Sig_Sem(SID_DD_USIO(ch));

	if ( D_DDIM_USER_E_OK != ercd) {
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
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
	IO_USIO.CSIO[ch].SCR.byte = 0x00;
	/*	IO_USIO.CSIO[ch].SMR.byte = 0x00;*/
	IO_USIO.CSIO[ch].ESCR.byte = 0x00;
	IO_USIO.CSIO[ch].DR.hword = 0x0000;
	IO_USIO.CSIO[ch].BGR.hword = 0x0000;
	IO_USIO.CSIO[ch].SCR.bit.UPCL = 1; // Soft-Reset
	IO_USIO.CSIO[ch].SMR.bit.MD = 2; // fixed, CSIO Transferring

	// SCR register setting
	IO_USIO.CSIO[ch].SCR.bit.MS = self->type; //Master/Slave selection bit

	// SMR register setting
	IO_USIO.CSIO[ch].SMR.bit.BDS = (kuchar) self->bitDirection; // Bit Direction, LSB first or MSB first

	// Set SMR.SCKE=1 if using CSIO as master, else SCKE=0
	if (self->type == DdCsio_DD_CSIO_TYPE_MASTER) {
		IO_USIO.CSIO[ch].SMR.bit.SCKE = 1;
	} else {
		IO_USIO.CSIO[ch].SMR.bit.SCKE = 0;
	}

	// ESCR register setting
	IO_USIO.CSIO[ch].ESCR.bit.L = self->dataLength;
	IO_USIO.CSIO[ch].ESCR.bit.SOP = self->sop;

	// BGR register setting
	IO_USIO.CSIO[ch].BGR.hword = self->baudrate;

	// Transmit mode setting. Set register related to transmit mode
	if (self->mode == DdCsio_DD_CSIO_MODE_NORMAL_SC_H) {
		IO_USIO.CSIO[ch].SMR.bit.SCINV = 0;
	} else if (self->mode == DdCsio_DD_CSIO_MODE_NORMAL_SC_L) {
		IO_USIO.CSIO[ch].SMR.bit.SCINV = 1;
	} else if (self->mode == DdCsio_DD_CSIO_MODE_SPI_SC_H) {
		IO_USIO.CSIO[ch].SCR.bit.SPI = 1;
		IO_USIO.CSIO[ch].SMR.bit.SCINV = 0;
	} else {	// DdCsio_DD_CSIO_MODE_SPI_SC_L
		IO_USIO.CSIO[ch].SCR.bit.SPI = 1;
		IO_USIO.CSIO[ch].SMR.bit.SCINV = 1;
	}

	// Callback function
	gddCsioInfo[ch].pcallback = self->pcallback; //Callback function pointer

	// FIFO setting
	if (self->fifoCtrl == NULL) {
		IO_USIO.CSIO[ch].FCR.hword = 0x000C; //FIFO not used and FIFO reset
		return D_DDIM_OK;
	}
	IO_USIO.CSIO[ch].FCR.hword = 0x000C; // Initialize
	IO_USIO.CSIO[ch].FCR.bit.FSEL = self->fifoCtrl->fsel; //fifo selection bit
	IO_USIO.CSIO[ch].FCR.bit.FSET = self->fifoCtrl->fset; //fifo transfer reload pointer storing bit
	IO_USIO.CSIO[ch].FCR.bit.FLSTE = self->fifoCtrl->flste; //data-lost check permmision bit
	IO_USIO.CSIO[ch].FCR.bit.FE1 = self->fifoCtrl->fe1; //FIFO1 enable
	IO_USIO.CSIO[ch].FCR.bit.FE2 = self->fifoCtrl->fe2; //FIFO2 enable
	IO_USIO.CSIO[ch].FBYTE.hword = 0x0000; //FBYE initial value

	if (self->fifoCtrl->fsel == 0) {
		IO_USIO.CSIO[ch].FBYTE.byte[1] = self->fifoCtrl->fbyteRecv; //FIFO2
	} else {
		IO_USIO.CSIO[ch].FBYTE.byte[0] = self->fifoCtrl->fbyteRecv; //FIFO1
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (self == NULL) {
		Ddim_Assertion(("CSIO input param error. [self] = NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	self->type = (DdCsioType) IO_USIO.CSIO[ch].SCR.bit.MS;
	self->bitDirection = (DdCsioBitDir) IO_USIO.CSIO[ch].SMR.bit.BDS;
	self->dataLength = (DdCsioDataLength) IO_USIO.CSIO[ch].ESCR.bit.L;
	self->sop = IO_USIO.CSIO[ch].ESCR.bit.SOP;
	self->baudrate = IO_USIO.CSIO[ch].BGR.hword;

	if (IO_USIO.CSIO[ch].SCR.bit.SPI == 1) {
		if (IO_USIO.CSIO[ch].SMR.bit.SCINV == 1) {
			self->mode = DdCsio_DD_CSIO_MODE_SPI_SC_L;
		} else {
			self->mode = DdCsio_DD_CSIO_MODE_SPI_SC_H;
		}
	} else {
		if (IO_USIO.CSIO[ch].SMR.bit.SCINV == 1) {
			self->mode = DdCsio_DD_CSIO_MODE_NORMAL_SC_L;
		} else {
			self->mode = DdCsio_DD_CSIO_MODE_NORMAL_SC_H;
		}
	}

	self->pcallback = gddCsioInfo[ch].pcallback;

	if (self->fifoCtrl == NULL) {
		return D_DDIM_OK;
	}

	self->fifoCtrl->flste = IO_USIO.CSIO[ch].FCR.bit.FLSTE;
	self->fifoCtrl->fsel = IO_USIO.CSIO[ch].FCR.bit.FSEL;
	self->fifoCtrl->fset = IO_USIO.CSIO[ch].FCR.bit.FSET;
	self->fifoCtrl->fe2 = IO_USIO.CSIO[ch].FCR.bit.FE2;
	self->fifoCtrl->fe1 = IO_USIO.CSIO[ch].FCR.bit.FE1;

	if (self->fifoCtrl->fsel == 0) {
		self->fifoCtrl->fbyteRecv = IO_USIO.CSIO[ch].FBYTE.bit.__FIFO2;
	} else {
		self->fifoCtrl->fbyteRecv = IO_USIO.CSIO[ch].FBYTE.bit.__FIFO1;
	}

	return D_DDIM_OK;
}


kint32 dd_csio_set_baudrate(DdCsio *self, kuchar ch, kuint16 baudRate )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif
	IO_USIO.CSIO[ch].BGR.hword = baudRate;
	return D_DDIM_OK;
}


kint32 dd_csio_get_baudrate(DdCsio *self,kuchar ch, kuint16* baudRate )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if (baudRate == NULL) {
		Ddim_Assertion(("CSIO input param error. [baudRate] = NULL\n"));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif
	*baudRate = IO_USIO.CSIO[ch].BGR.hword;
	return D_DDIM_OK;
}

kint32 dd_csio_save_send_fifo_pointer(DdCsio *self, kuchar ch, kuchar lostDetect )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if ((lostDetect != 0) && (lostDetect != 1)) {
		Ddim_Assertion(("CSIO input param error. [lostDetect] = %d\n", lostDetect));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	// Check exist data in send fifo
	if (IO_USIO.CSIO[ch].FBYTE.byte[IO_USIO.CSIO[ch].FCR.bit.FSEL] != 0) {
		return C_CSIO_DATA_EXIST_ERROR;
	}

	// Save Read Pointer
	IO_USIO.CSIO[ch].FCR.bit.FSET = 1;

	// Enable/Disable data lost detection (FLST)
	IO_USIO.CSIO[ch].FCR.bit.FLSTE = lostDetect;
	return D_DDIM_OK;
}


kint32 dd_csio_reload_send_fifo_pointer(DdCsio *self, kuchar ch )
{
	kuchar fe1;
	kuchar fe2;
	kuint32 waitCnt = 0;
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	if (IO_USIO.CSIO[ch].FCR.bit.FLST == 1) {
		// Reload data lost
		return C_CSIO_OVERWRITE_ERROR;
	}

	// Keep to temporary
	fe1 = IO_USIO.CSIO[ch].FCR.bit.FE1;
	fe2 = IO_USIO.CSIO[ch].FCR.bit.FE2;

	// Disable send/receive
	IO_USIO.CSIO[ch].FCR.bit.FE1 = 0;
	IO_USIO.CSIO[ch].FCR.bit.FE2 = 0;
	IO_USIO.CSIO[ch].SCR.bit.TIE = 0;
	IO_USIO.CSIO[ch].SCR.bit.TBIE = 0;
	IO_USIO.CSIO[ch].FCR.bit.FTIE = 0;

	// Reload Send FIFO
	IO_USIO.CSIO[ch].FCR.bit.FLD = 1;

	// Enable send permission
	IO_USIO.CSIO[ch].SMR.bit.SOE = 1;
	IO_USIO.CSIO[ch].SCR.bit.TXE = 1;

	// Set keep value
	IO_USIO.CSIO[ch].FCR.bit.FE1 = fe1;
	IO_USIO.CSIO[ch].FCR.bit.FE2 = fe2;

	// Subtract the number of resend   ???
//	if( IO_USIO.CSIO[ch].FBYTE.byte[IO_USIO.CSIO[ch].FCR.bit.FSEL] >= gddCsioInfo[ch].sendPos ){
//		gddCsioInfo[ch].sendPos -= IO_USIO.CSIO[ch].FBYTE.byte[IO_USIO.CSIO[ch].FCR.bit.FSEL];
//	}

	if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
		IO_USIO.CSIO[ch].FCR.bit.FDRQ = 0;
		IO_USIO.CSIO[ch].FCR.bit.FTIE = 1;
		DdCsioCommon_DD_CSIO_DSB();
	} else {	// Interrupt is disable
		while (IO_USIO.CSIO[ch].SSR.bit.__TBI == 0) {
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	return IO_USIO.CSIO[ch].FCR.bit.FLD;
}


kint32 dd_csio_reset_fifo(DdCsio *self, kuchar ch, kuchar fifoNum )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
	if ((fifoNum < C_CSIO_SELECT_FIFO_1) || (fifoNum > C_CSIO_SELECT_FIFO_BOTH)) {
		Ddim_Assertion(("CSIO input param error. [fifoNum] = %d\n", fifoNum));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	IO_USIO.CSIO[ch].SCR.bit.TXE = 0;
	IO_USIO.CSIO[ch].SCR.bit.RXE = 0;
	IO_USIO.CSIO[ch].FCR.bit.FTIE = 0;

	// Reset FIFO
	IO_USIO.CSIO[ch].FCR.hword |= fifoNum << 2;
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
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

	if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	IO_USIO.CSIO[ch].SMR.bit.SOE = 1; //Serial data output permission bit
	IO_USIO.CSIO[ch].SCR.bit.RXE = 0; //Disable receive permission bit
	IO_USIO.CSIO[ch].SCR.bit.TXE = 1; //Enable transfer permission bit

	if (((IO_USIO.CSIO[ch].FCR.bit.FSEL == 0) && (IO_USIO.CSIO[ch].FCR.bit.FE1 == 1))
			|| ((IO_USIO.CSIO[ch].FCR.bit.FSEL == 1) && (IO_USIO.CSIO[ch].FCR.bit.FE2 == 1))) {
		// FIFO use
		while (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 0) {
			// wait until FIFO empty
			ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
			if (ret != D_DDIM_OK) {
				return ret;
			}
			waitCnt++;
		}
		waitCnt = 0;

		if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
			while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				IO_USIO.CSIO[ch].DR.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
				gddCsioInfo[ch].sendPos++;

				if (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 1) {// FIFO is not full? (0:full, 1:empty)
					continue;
				} else {	//FIFO is full
					if(gddCsioInfo[ch].pcallback){	// Interrupt enable?
						IO_USIO.CSIO[ch].FCR.bit.FDRQ = 0;
						IO_USIO.CSIO[ch].FCR.bit.FTIE = 1;
						DdCsioCommon_DD_CSIO_DSB();
						return D_DDIM_OK;
					} else {	// Interrupt is disable
						while (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 0) {
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
				IO_USIO.CSIO[ch].DR.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
				gddCsioInfo[ch].sendPos++;

				if (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 1) {// FIFO is not full? (0:full, 1:empty)
					continue;
				} else {	//FIFO is full
					if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
						IO_USIO.CSIO[ch].FCR.bit.FDRQ = 0;
						IO_USIO.CSIO[ch].FCR.bit.FTIE = 1;
						DdCsioCommon_DD_CSIO_DSB();
						return D_DDIM_OK;
					} else {	// Interrupt is disable
						while (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 0) {
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
				IO_USIO.CSIO[ch].FCR.bit.FDRQ = 0;
				IO_USIO.CSIO[ch].FCR.bit.FTIE = 1;
			} else {
				IO_USIO.CSIO[ch].SCR.bit.TBIE = 1;
			}
			DdCsioCommon_DD_CSIO_DSB();
		} else {	// Interrupt is disable
			while (IO_USIO.CSIO[ch].SSR.bit.__TBI == 0) {
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
		if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
			while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				while (IO_USIO.CSIO[ch].SSR.bit.__TDRE == 0) {
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

				IO_USIO.CSIO[ch].DR.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
				gddCsioInfo[ch].sendPos++;

				if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
					IO_USIO.CSIO[ch].SCR.bit.TIE = 1;
					DdCsioCommon_DD_CSIO_DSB();
					return D_DDIM_OK;
				}
			}
		} else {
			while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				while (IO_USIO.CSIO[ch].SSR.bit.__TDRE == 0) {
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

				IO_USIO.CSIO[ch].DR.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
				DdCsioCommon_DD_CSIO_DSB();
				gddCsioInfo[ch].sendPos++;

				if (gddCsioInfo[ch].pcallback) {	 //Interrupt enable?
					IO_USIO.CSIO[ch].SCR.bit.TIE = 1;
					DdCsioCommon_DD_CSIO_DSB();
					return D_DDIM_OK;
				}
			}
		}

		// All data was written
		if (gddCsioInfo[ch].pcallback) {	// Interrupt enable?
			if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
				IO_USIO.CSIO[ch].SCR.bit.TIE = 1;
			} else {
				IO_USIO.CSIO[ch].SCR.bit.TBIE = 1;
			}
			DdCsioCommon_DD_CSIO_DSB();
		} else { //Interrupt is disable
			while (IO_USIO.CSIO[ch].SSR.bit.__TBI == 0) {
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
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

	if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	IO_USIO.CSIO[ch].SMR.bit.SOE = 0; //Serial data output permission bit
	IO_USIO.CSIO[ch].SCR.bit.RXE = 1; //Enable receive permission bit
	IO_USIO.CSIO[ch].SCR.bit.TXE = 1; //Disable transfer permission bit

	if (gddCsioInfo[ch].pcallback) { //Interrupt enable?
		//Dummy data for master receiving
		if (IO_USIO.CSIO[ch].SCR.bit.MS == 0) {
			IO_USIO.CSIO[ch].DR.hword = 0;
		}
		IO_USIO.CSIO[ch].FCR.bit.FRIIE = 1;
		IO_USIO.CSIO[ch].SCR.bit.RIE = 1;
		DdCsioCommon_DD_CSIO_DSB();
	} else { //Interrupt is disble
		if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
			while (gddCsioInfo[ch].recvPos < gddCsioInfo[ch].num) {
				// Dummy data for master receiving
				if (IO_USIO.CSIO[ch].SCR.bit.MS == 0) {
					IO_USIO.CSIO[ch].DR.hword = 0;
					DdCsioCommon_DD_CSIO_DSB();
				}

				// Wait until RDR filled up with data
				while (IO_USIO.CSIO[ch].SSR.bit.__RDRF == 0) {
					// wait until TDR empty
					ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
					if (ret != D_DDIM_OK) {
						return ret;
					}
					waitCnt++;
				}

				// Check for buffer overrun error
				if (IO_USIO.CSIO[ch].SSR.bit.__ORE == 1) {
					// Clear buffer overrun error
					IO_USIO.CSIO[ch].SSR.byte |= C_CSIO_SSR_REC_BIT;
					DdCsioCommon_DD_CSIO_DSB();
					return C_CSIO_RECV_OVERRUN_ERROR;
				}

				*(gddCsioInfo[ch].recvAddr16 + gddCsioInfo[ch].recvPos) = IO_USIO.CSIO[ch].DR.hword;
				gddCsioInfo[ch].recvPos++;
			}
		} else {
			while (gddCsioInfo[ch].recvPos < gddCsioInfo[ch].num) {
				// Dummy data for master receiving
				if (IO_USIO.CSIO[ch].SCR.bit.MS == 0) {
					IO_USIO.CSIO[ch].DR.hword = 0;
					DdCsioCommon_DD_CSIO_DSB();
				}

				// Wait until RDR filled up with data
				while (IO_USIO.CSIO[ch].SSR.bit.__RDRF == 0) {
					// wait until TDR empty
					ret = dd_csio_common_check_stopping_conditions(dd_csio_common_get(), ch, waitCnt);
					if (ret != D_DDIM_OK) {
						return ret;
					}
					waitCnt++;
				}

				// Check for buffer overrun error
				if (IO_USIO.CSIO[ch].SSR.bit.__ORE == 1) {
					// Clear buffer overrun error
					IO_USIO.CSIO[ch].SSR.byte |= C_CSIO_SSR_REC_BIT;
					DdCsioCommon_DD_CSIO_DSB();
					return C_CSIO_RECV_OVERRUN_ERROR;
				}

				*(gddCsioInfo[ch].recvAddr8 + gddCsioInfo[ch].recvPos) = IO_USIO.CSIO[ch].DR.byte[0];
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
	if(ch >= D_DD_USIO_CH_NUM_MAX){
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	gddCsioInfo[ch].fullDuplex = 1;
	IO_USIO.CSIO[ch].SMR.bit.SOE = 1; //Serial data output permission bit
	IO_USIO.CSIO[ch].SCR.bit.RXE = 1; //Disable receive permission bit
	IO_USIO.CSIO[ch].SCR.bit.TXE = 1; //Enable transfer permission bit

	// FIFO setting (When the user doesn't set by CTRL)
	if ((IO_USIO.CSIO[ch].FCR.bit.FE1 == 0) || (IO_USIO.CSIO[ch].FCR.bit.FE2 == 0)) {
		IO_USIO.CSIO[ch].FCR.bit.FSEL = 0; //send:FIFO1, receive:FIFO2
		IO_USIO.CSIO[ch].FCR.bit.FE1 = 1; //FIFO1 enable
		IO_USIO.CSIO[ch].FCR.bit.FE2 = 1; //FIFO2 enable
	}

	// Send data
	if (IO_USIO.CSIO[ch].ESCR.bit.L == DdCsio_DD_CSIO_DATA_LENGTH_9) {
		while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			IO_USIO.CSIO[ch].DR.hword = *(gddCsioInfo[ch].sendAddr16 + gddCsioInfo[ch].sendPos);
			DdCsioCommon_DD_CSIO_DSB();
			gddCsioInfo[ch].sendPos++;

			if (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 0) {
				//FIFO is full (0:full, 1:empty)
				break;
			} else {
				// FIFO is not full
				continue;
			}
		}
	} else {
		while (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
			IO_USIO.CSIO[ch].DR.byte[0] = *(gddCsioInfo[ch].sendAddr8 + gddCsioInfo[ch].sendPos);
			DdCsioCommon_DD_CSIO_DSB();
			gddCsioInfo[ch].sendPos++;

			if (IO_USIO.CSIO[ch].FCR.bit.FDRQ == 0) {
				//FIFO is full (0:full, 1:empty)
				break;
			} else {
				// FIFO is not full
				continue;
			}
		}
	}

	if (gddCsioInfo[ch].sendPos < gddCsioInfo[ch].num) {
		IO_USIO.CSIO[ch].FCR.bit.FDRQ = 0;
		IO_USIO.CSIO[ch].FCR.bit.FTIE = 1;
	} else {
		IO_USIO.CSIO[ch].SCR.bit.TBIE = 1;
	}

	while ((IO_USIO.CSIO[ch].SSR.byte & 0x03) != 0x03) {
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
	if (ch >= D_DD_USIO_CH_NUM_MAX) {
		Ddim_Assertion(("CSIO input param error. [ch] = %d\n", ch));
		return C_CSIO_INPUT_PARAM_ERROR;
	}
#endif

	if (gddCsioInfo[ch].dmaWait == 1) {
		Dd_HDMAC1_Stop(gddCsioDmaInfo[ch][C_CSIO_SEND].dmaCh);
		Dd_HDMAC1_Close(gddCsioDmaInfo[ch][C_CSIO_SEND].dmaCh);
		Dd_HDMAC1_Stop(gddCsioDmaInfo[ch][C_CSIO_RECV].dmaCh);
		Dd_HDMAC1_Close(gddCsioDmaInfo[ch][C_CSIO_RECV].dmaCh);
		gddCsioInfo[ch].dmaWait = 0;
	}

	// Disable interrupt
	IO_USIO.CSIO[ch].SCR.bit.RIE = 0;
	IO_USIO.CSIO[ch].SCR.bit.TIE = 0;
	IO_USIO.CSIO[ch].SCR.bit.TBIE = 0;
	IO_USIO.CSIO[ch].FCR.bit.FTIE = 0;
	IO_USIO.CSIO[ch].FCR.bit.FRIIE = 0;

	// Disable FIFO
	IO_USIO.CSIO[ch].FCR.bit.FE1 = 0;
	IO_USIO.CSIO[ch].FCR.bit.FE2 = 0;
	IO_USIO.CSIO[ch].SCR.bit.UPCL = 1; //Soft-Reset

	// Disable send/receive
	IO_USIO.CSIO[ch].SCR.bit.TXE = 0;
	IO_USIO.CSIO[ch].SCR.bit.RXE = 0;
	gddCsioInfo[ch].forceStopFlg = 1;
	DdCsioCommon_DD_CSIO_DSB();
	return D_DDIM_OK;
}

DdCsio* dd_csio_new(void)
{
	DdCsio* self = k_object_new_with_private(DD_TYPE_CSIO, sizeof(DdCsioPrivate));

	return self;
}
