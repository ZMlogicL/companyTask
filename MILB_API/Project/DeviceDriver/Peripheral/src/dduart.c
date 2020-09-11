/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :uart driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include <string.h>
#include "uart_csio.h"
#include "dd_csio.h"
#include "dd_hdmac1.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "dd_gic.h"

#ifdef CO_DDIM_IM_TUNING_ON
    #include "../../../../../../ip/fj_ip/ImageTuning/include/im_tuning_buffer.h"
    #include "../../../../../../ip/fj_ip/ImageTuning/include/im_tuning_custom.h"
#endif

#include "dduart.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdUart, dd_uart);
#define DD_UART_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdUartPrivate, DD_TYPE_UART))

struct _DdUartPrivate
{
	// USIO [UART/CSIO common] channel status
	volatile kuchar gDdUsioState[DdUart_CH_NUM_MAX];
	// UART Management table
	volatile DdUartMng gDdUartMng[DdUart_CH_NUM_MAX];
	// UART Ring Buffer table
	volatile DdUartBufferInfo gDdUartBuffInfo[DdUart_CH_NUM_MAX];
	/* Flag to make it not access address that no one sets.
	 * When the handler starts before reception/transmission buffer is set, it accesses 0.
	 */
	volatile kuchar gDdUartFlag[DdUart_CH_NUM_MAX];
	// Uart control information
	volatile DdUartInfo gDdUartInfo[DdUart_CH_NUM_MAX];
};

// For IQTOOL
#ifdef CO_DDIM_IM_TUNING_ON
static volatile kuchar S_GDD_IQTOOL_STATUS = 0;
#endif

// Spin Lock
static DdUartSpinLock S_GDD_UART_SPIN_LOCK[DdUart_CH_NUM_MAX]
                                           __attribute__((section(".LOCK_SECTION"), aligned(64)));

/*
 * DECLS
 */
static kint32     ddUartCheckStoppingConditions(DdUart *self, kuchar ch);

#ifdef CO_DDIM_UTILITY_USE
static kint32     ddUartDmaCopy(kuchar uartCh, kuchar dmaCh, kulong srcAddr,
		                         kulong dstAddr, kulong trnsSize);
#endif

static void dd_uart_constructor(DdUart *self)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);

	kint i;
	for(i = 0; i < DdUart_CH_NUM_MAX; i++){
		priv->gDdUsioState[i] = DdUart_EXC_OFF;
		priv->gDdUartFlag[i] = 0;
		priv->gDdUartInfo[i].recvAddr8 = NULL;
		priv->gDdUartInfo[i].sendAddr8 = NULL;
		priv->gDdUartMng[i].fifoCtrl = NULL;
		priv->gDdUartMng[i].preceiveCallback = NULL;
		priv->gDdUartMng[i].psendCallback = NULL;
		priv->gDdUartMng[i].receiveBuffAddr = NULL;
		priv->gDdUartMng[i].recvDmaCallback = NULL;
		priv->gDdUartMng[i].sendBuffAddr = NULL;
		priv->gDdUartMng[i].sendDmaCallback = NULL;
	}
}

static void dd_uart_destructor(DdUart *self)
{

}

/*
 * IMPL
 */
static kint32 ddUartCheckStoppingConditions(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	if(priv->gDdUartInfo[ch].forceStopFlg == 1){
		priv->gDdUartInfo[ch].forceStopFlg = 0;
		return DdUart_FORCE_STOP;
	}

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
static kint32 ddUartDmaCopy(kuchar uartCh, kuchar dmaCh, kulong srcAddr,
		kulong dstAddr, kulong trnsSize)
{
	kint32					ret;
	T_DD_HDMAC1_CTRL_TRNS	dmaCtrlTrns;

	dmaCtrlTrns.mode.input_sel = DdUart_DMACA_IS_BASE + (uartCh << 1) + 1;
	dmaCtrlTrns.mode.mode_sel = D_DD_HDMAC1_MS_DEMAND;
	dmaCtrlTrns.mode.src_fix = D_DD_HDMAC1_FS_INCR;
	dmaCtrlTrns.mode.dst_fix = D_DD_HDMAC1_FD_FIX;
	dmaCtrlTrns.mode.beat_type = D_DD_HDMAC1_BT_NORMAL;

	dmaCtrlTrns.size.trns_width = D_DD_HDMAC1_TW_BYTE;
	dmaCtrlTrns.size.trns_size = trnsSize;
	dmaCtrlTrns.size.src_addr = srcAddr;
	dmaCtrlTrns.size.dst_addr = dstAddr;

	dmaCtrlTrns.int_handler = NULL;

	ret = Dd_HDMAC1_Ctrl_Trns(dmaCh, &dmaCtrlTrns);
	if(ret == D_DDIM_OK){
		ret = Dd_HDMAC1_Start_Async(dmaCh);
		if(ret != D_DDIM_OK){
			Dd_HDMAC1_Close(dmaCh);
			Ddim_Print(("Dd_HDMAC1_Start_Async() error. ret=0x%x\n", ret));
			return ret;
		}
	}
	else{
		Dd_HDMAC1_Close(dmaCh);
		Ddim_Print(("Dd_HDMAC1_Ctrl_Trns() error. ret=0x%x\n", ret));
		return ret;
	}

	return ret;
}
#endif

/*
 * PUBLIC
 */
/*
 * @brief  The exclusive control of UART is released.
 * @param  kuchar  ch
 * @return kint32  D_DDIM_OK/DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_close(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	// Global variable is clear
//	gDdUartMng.baudRate = 0;
	priv->gDdUartMng[ch].psendCallback = NULL;
	priv->gDdUartMng[ch].preceiveCallback = NULL;
	priv->gDdUartMng[ch].receiveBuffAddr = NULL;
	priv->gDdUartMng[ch].receiveBuffSize = 0;
	priv->gDdUartMng[ch].sendBuffAddr = NULL;
	priv->gDdUartMng[ch].sendBuffSize = 0;
	priv->gDdUartMng[ch].autoEcho = DdUart_AUTO_ECHO_ON;
	priv->gDdUartMng[ch].saveBuff = DdUart_SAVE2BUFFER_EN;
	priv->gDdUartMng[ch].sendDmaCallback = NULL;
	priv->gDdUartMng[ch].recvDmaCallback = NULL;

	priv->gDdUartBuffInfo[ch].rReadPos = 0;
	priv->gDdUartBuffInfo[ch].rWritePos	= 0;
	priv->gDdUartBuffInfo[ch].rSize = 0;
	priv->gDdUartBuffInfo[ch].rFlag = 0;
	priv->gDdUartBuffInfo[ch].sReadPos	= 0;
	priv->gDdUartBuffInfo[ch].sWritePos	= 0;
	priv->gDdUartBuffInfo[ch].sSize = 0;
	priv->gDdUartBuffInfo[ch].sFlag = 0;

	priv->gDdUartInfo[ch].forceStopFlg = 0;
	priv->gDdUartInfo[ch].multiActiveFlg = DdUart_MODE_MULTI_DIS;
	priv->gDdUartInfo[ch].multiSlaveAddr	= 0;
	priv->gDdUartInfo[ch].dmaWait = 0;

	priv->gDdUsioState[ch] = DdUart_EXC_OFF;

	// start flag clear
	priv->gDdUartFlag[ch] = 0;

	// Exclusive release
	ercd = DDIM_User_Sig_Sem(SID_DD_USIO(ch));

	if(D_DDIM_USER_E_OK != ercd) {
		return DdUart_SEM_NG;
	}

	return D_DDIM_OK;
}

/*
 * @brief  The value specified by the argument is set to the register of UART.
 * @param  DdUartMng* uartMng
 * @return kint32  D_DDIM_OK/DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_ctrl(DdUart *self, kuchar ch, DdUartMng const* const uartMng)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	kuint32 num;
	kint32 count;
	kint32 baudRate;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(uartMng == NULL){
		Ddim_Assertion(("UART input param error. [uartMng] = NULL\n"));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(uartMng->mode == DdUart_MODE_MULTI
	&& !(uartMng->dataLength == DdUart_DATA_LENGTH_8
			|| uartMng->dataLength == DdUart_DATA_LENGTH_7)
	){
		Ddim_Assertion(("UART input param error. [mode] = %d, [dataLength] = %d\n",
				uartMng->mode, uartMng->dataLength));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	baudRate = (kint32)uartMng->baudRate;

	// The value gotten by the argument is set to a global table.
	// Baud rate
	priv->gDdUartMng[ch].baudRate = uartMng->baudRate;
	// Send callback function pointer
	priv->gDdUartMng[ch].psendCallback = uartMng->psendCallback;
	// Receive callback function pointer
	priv->gDdUartMng[ch].preceiveCallback = uartMng->preceiveCallback;
	// Receive buffer address
	priv->gDdUartMng[ch].receiveBuffAddr = uartMng->receiveBuffAddr;
	// Receive buffer size
	priv->gDdUartMng[ch].receiveBuffSize = uartMng->receiveBuffSize;
	// Receive buffer address
	priv->gDdUartMng[ch].sendBuffAddr = uartMng->sendBuffAddr;
	// Receive buffer size
	priv->gDdUartMng[ch].sendBuffSize = uartMng->sendBuffSize;
	// Auto echo
	priv->gDdUartMng[ch].autoEcho = uartMng->autoEcho;
	// Save to the buffer
	priv->gDdUartMng[ch].saveBuff = uartMng->saveBuff;
	// Send DMA callback function pointer
	priv->gDdUartMng[ch].sendDmaCallback = uartMng->sendDmaCallback;
	// Receive DMA callback function pointer
	priv->gDdUartMng[ch].recvDmaCallback = uartMng->recvDmaCallback;

	// start flag initialize
	priv->gDdUartFlag[ch] = 1;

	/*-------------------------------*/
	/* Initialization of ring buffer */
	/*-------------------------------*/
	// Reception buffer initialization
	for(num = 0; num < priv->gDdUartMng[ch].receiveBuffSize; num++){
		*(priv->gDdUartMng[ch].receiveBuffAddr + num) = 0;
	}
	priv->gDdUartBuffInfo[ch].rReadPos = 0;
	priv->gDdUartBuffInfo[ch].rWritePos = 0;
	priv->gDdUartBuffInfo[ch].rSize = 0;
	priv->gDdUartBuffInfo[ch].rFlag = 0;

	// Transmission buffer initialization
	for(num = 0; num < priv->gDdUartMng[ch].sendBuffSize; num++){
		*(priv->gDdUartMng[ch].sendBuffAddr + num) = 0;
	}
	priv->gDdUartBuffInfo[ch].sReadPos = 0;
	priv->gDdUartBuffInfo[ch].sWritePos = 0;
	priv->gDdUartBuffInfo[ch].sSize = 0;
	priv->gDdUartBuffInfo[ch].sFlag = 0;

	// Uart control information initialization
	priv->gDdUartInfo[ch].forceStopFlg = 0;
	priv->gDdUartInfo[ch].multiActiveFlg = DdUart_MODE_MULTI_DIS;
	priv->gDdUartInfo[ch].multiSlaveAddr	= 0;
	priv->gDdUartInfo[ch].dmaWait = 0;

	/*----------------------*/
	/* Setting of UART Mode */
	/*----------------------*/
	count = (Dd_Top_Get_HCLK() /  baudRate) -1;

	// RIE, TIE,TBIE Mask
	IO_USIO.UART[ch].SCR.byte = 0x00;
	// UART Macro initialize
	IO_USIO.UART[ch].SCR.byte = 0x80;
	IO_USIO.UART[ch].SMR.byte = 0x01;
	IO_USIO.UART[ch].ESCR.byte = 0x00;
	IO_USIO.UART[ch].SSR.byte = 0x80;
	IO_USIO.UART[ch].FCR.hword = 0x0000;

	if(uartMng->mode == DdUart_MODE_MULTI){
		IO_USIO.UART[ch].SMR.bit.MD = 1;
		IO_USIO.UART[ch].ESCR.bit.PEN	= 0;
	}
	else{
		// Normal mode
		IO_USIO.UART[ch].SMR.bit.MD = 0;

		if(uartMng->parityBit == DdUart_PARITY_BIT_EVEN){
			IO_USIO.UART[ch].ESCR.bit.PEN	= 1;
			IO_USIO.UART[ch].ESCR.bit.P = 0;
		}
		else if(uartMng->parityBit == DdUart_PARITY_BIT_ODD){
			IO_USIO.UART[ch].ESCR.bit.PEN	= 1;
			IO_USIO.UART[ch].ESCR.bit.P = 1;
		}
		else{
			// E_DD_UART_PARITY_BIT_NONE
			IO_USIO.UART[ch].ESCR.bit.PEN	= 0;
		}
	}

	IO_USIO.UART[ch].ESCR.bit.INV	= uartMng->invNrz;
	IO_USIO.UART[ch].ESCR.bit.FLWEN = uartMng->flowEnable;

	IO_USIO.UART[ch].BGR.hword = (kshort)count;
	IO_USIO.UART[ch].BGR.bit.EXT = uartMng->extClk;

	IO_USIO.UART[ch].SMR.bit.BDS	= (kuchar)uartMng->bitDirection;
	IO_USIO.UART[ch].SMR.bit.SBL = (kuchar)uartMng->stopBitLength;

	IO_USIO.UART[ch].ESCR.bit.L = uartMng->dataLength;

	if(priv->gDdUartMng[ch].preceiveCallback != NULL) {
		IO_USIO.UART[ch].SCR.bit.RIE = 1;
	}

	if(uartMng->fifoCtrl == NULL){
		// FIFO not used and FIFO reset
		IO_USIO.UART[ch].FCR.hword = 0x000C;
		return D_DDIM_OK;
	}

	// Initialize
	IO_USIO.UART[ch].FCR.hword = 0x000C;
	// data-lost check permmision bit
	IO_USIO.UART[ch].FCR.bit.FLSTE = uartMng->fifoCtrl->flste;
	// fifo selection bit
	IO_USIO.UART[ch].FCR.bit.FSEL = uartMng->fifoCtrl->fsel;

	// fifo transfer reload pointer storing bit
	IO_USIO.UART[ch].FCR.bit.FSET = uartMng->fifoCtrl->fset;

	IO_USIO.UART[ch].FCR.bit.FE2 = uartMng->fifoCtrl->fe2;
	IO_USIO.UART[ch].FCR.bit.FE1 = uartMng->fifoCtrl->fe1;

	if (((uartMng->fifoCtrl->fsel == 0) && (uartMng->fifoCtrl->fe2 == 1))
	||	 ((uartMng->fifoCtrl->fsel == 1) && (uartMng->fifoCtrl->fe1 == 1))) {
		// Receive FIFO idle detection enable bit
		IO_USIO.UART[ch].FCR.bit.FRIIE = 1;
	}

	// FBYE initial value
	IO_USIO.UART[ch].FBYTE.hword = 0x0000;

	if(uartMng->fifoCtrl->fsel == 0){
		IO_USIO.UART[ch].FBYTE.byte[1] = uartMng->fifoCtrl->fbyteRecv;
	}
	else{
		IO_USIO.UART[ch].FBYTE.byte[0] = uartMng->fifoCtrl->fbyteRecv;
	}

	return D_DDIM_OK;
}

/*
 * @brief  The transmission data specified by the argument is set to the register for the UART transmission.
 * @param  kuchar	ch
 * @param  kchar		putChar
 * @return kint32	D_DDIM_OK / DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_put_char(DdUart *self, kuchar ch, kchar putChar)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	kint32 ret;

#ifdef CO_DDIM_IM_TUNING_ON
    kuchar uputChar = (kuchar)putChar;
	if (S_GDD_IQTOOL_STATUS == DdUart_IQTOOL_START)
    {
		// if block SYSTEM printout
        if ((Get_Print_MsgMask() & D_SYSTEM_MSG))
        {
            uart_TxBuf_write(&uputChar,1);
        }
        return D_DDIM_OK;
    }
#endif

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	if(IO_USIO.UART[ch].SCR.bit.TXE == 0){
		return DdUart_STOPPED;
	}

	if(((IO_USIO.UART[ch].FCR.bit.FSEL == 0) && (IO_USIO.UART[ch].FCR.bit.FE1 == 1)) ||
	   ((IO_USIO.UART[ch].FCR.bit.FSEL == 1) && (IO_USIO.UART[ch].FCR.bit.FE2 == 1))){
		// FIFO use
		while(IO_USIO.UART[ch].FCR.bit.FDRQ == 0){
			ret = ddUartCheckStoppingConditions(self, ch);
			if(ret != D_DDIM_OK){
				return ret;
			}
		}

		IO_USIO.UART[ch].DR.hword = putChar;

		if(priv->gDdUartMng[ch].psendCallback != NULL){
			// Interruput is enable
			IO_USIO.UART[ch].FCR.bit.FDRQ = 0;
			IO_USIO.UART[ch].FCR.bit.FTIE = 1;
		}
	}
	else{
		// FIFO not use
		while(IO_USIO.UART[ch].SSR.bit.__TDRE == 0){
			ret = ddUartCheckStoppingConditions(self, ch);
			if(ret != D_DDIM_OK){
				return ret;
			}
		}
		if(priv->gDdUartInfo[ch].forceStopFlg == 1){
			priv->gDdUartInfo[ch].forceStopFlg = 0;
			return DdUart_FORCE_STOP;
		}

		IO_USIO.UART[ch].DR.hword = putChar;

		if(priv->gDdUartMng[ch].psendCallback != NULL){
			while(IO_USIO.UART[ch].SSR.bit.__TDRE == 1){
				ret = ddUartCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}
			// Interruput is enable
			IO_USIO.UART[ch].SCR.bit.TIE = 1;
		}
	}

	DdUart_DSB();

	return D_DDIM_OK;
}

kint32 dd_uart_send_target_slave_addr(DdUart *self, kuchar ch, kuchar slaveAddr)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif
	// Normal mode
	if(IO_USIO.UART[ch].SMR.bit.MD == 0){
		return DdUart_MODE_UNMATCH;
	}

	if(IO_USIO.UART[ch].SCR.bit.TXE == 0){
		return DdUart_STOPPED;
	}

	if(((IO_USIO.UART[ch].FCR.bit.FSEL == 0) && (IO_USIO.UART[ch].FCR.bit.FE1 == 1)) ||
	   ((IO_USIO.UART[ch].FCR.bit.FSEL == 1) && (IO_USIO.UART[ch].FCR.bit.FE2 == 1))){
		// FIFO use
		while(IO_USIO.UART[ch].FCR.bit.FDRQ == 0){
			ret = ddUartCheckStoppingConditions(self, ch);
			if(ret != D_DDIM_OK){
				return ret;
			}
		}

		IO_USIO.UART[ch].DR.hword = (0x0100 | slaveAddr);

		if(priv->gDdUartMng[ch].psendCallback != NULL){
			// Interruput is enable
			IO_USIO.UART[ch].FCR.bit.FDRQ = 0;
			IO_USIO.UART[ch].FCR.bit.FTIE = 1;
		}
	}
	else{
		// FIFO not use
		while(IO_USIO.UART[ch].SSR.bit.__TDRE == 0){
			ret = ddUartCheckStoppingConditions(self, ch);
			if(ret != D_DDIM_OK){
				return ret;
			}
		}
		if(priv->gDdUartInfo[ch].forceStopFlg == 1){
			priv->gDdUartInfo[ch].forceStopFlg = 0;
			return DdUart_FORCE_STOP;
		}

		IO_USIO.UART[ch].DR.hword = (0x0100 | slaveAddr);

		if(priv->gDdUartMng[ch].psendCallback != NULL){
			while(IO_USIO.UART[ch].SSR.bit.__TDRE == 1){
				ret = ddUartCheckStoppingConditions(self, ch);
				if(ret != D_DDIM_OK){
					return ret;
				}
			}
			// Interruput is enable
			IO_USIO.UART[ch].SCR.bit.TIE = 1;
		}
	}

	priv->gDdUartInfo[ch].multiActiveFlg = DdUart_MODE_MULTI_MASTER;

	DdUart_DSB();

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
/*
 * @brief  All the data that exists in the transmission buffer is transmitted via DMA and UART FIFO.
 * 		   The error is sent back when there is no data in the transmission buffer.
 * @param  kuchar  uartCh
 * @param  kuchar  dmaCh
 * @return kint32  D_DDIM_OK/DdUart_NO_SEND_DATA
 */
kint32 dd_uart_put_str_dma(DdUart *self, kuchar uartCh, kuchar dmaCh)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	kuint32	sendSize;
	kint32	ret = D_DDIM_OK;
	kint32	ret2;
	kushort	status;
	kulong	 srcAddr, dstAddr;

#ifdef CO_PARAM_CHECK
	if(uartCh >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [uartCh] = %d\n", uartCh));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(dmaCh >= D_DD_HDMAC1_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [dmaCh] = %d\n", dmaCh));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	if(priv->gDdUartBuffInfo[uartCh].sSize == 0){
		ret = DdUart_NO_SEND_DATA;
	}
	else{
		// Sets transmission FIFO, when not set with Dd_UART_Ctrl().
		if(((IO_USIO.UART[uartCh].FCR.bit.FSEL == 0) && (IO_USIO.UART[uartCh].FCR.bit.FE1 == 0)) ||
		   ((IO_USIO.UART[uartCh].FCR.bit.FSEL == 1) && (IO_USIO.UART[uartCh].FCR.bit.FE2 == 0))){
			 IO_USIO.UART[uartCh].FCR.bit.FSEL = 0;
			 IO_USIO.UART[uartCh].FCR.bit.FE1 = 1;
			 DdUart_DSB();
		}

		// All the data that exists in the transmission buffer is transmitted.
		while(priv->gDdUartBuffInfo[uartCh].sSize){

			// Open DMA.
			ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_USER_SEM_WAIT_POL);
			if(ret != D_DDIM_OK){
				Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
				return ret;
			}

			// SpinLock.
			Dd_ARM_Critical_Section_Start(S_GDD_UART_SPIN_LOCK[uartCh].lock);

			// Set DMA data.
			srcAddr = (kulong)(priv->gDdUartMng[uartCh].sendBuffAddr
					+ priv->gDdUartBuffInfo[uartCh].sReadPos);
			dstAddr = (kulong)(&(IO_USIO.UART[uartCh].DR));
			if((priv->gDdUartBuffInfo[uartCh].sWritePos <= priv->gDdUartBuffInfo[uartCh].sReadPos)
					&& (priv->gDdUartBuffInfo[uartCh].sFlag == 1)) {
				sendSize = priv->gDdUartMng[uartCh].sendBuffSize - priv->gDdUartBuffInfo[uartCh].sReadPos;
			}
			else {
				sendSize = priv->gDdUartBuffInfo[uartCh].sSize;
			}

			DDIM_User_L1l2cache_Clean_Flush_Addr(srcAddr, sendSize);

			// SpinUnLock.
			Dd_ARM_Critical_Section_End(S_GDD_UART_SPIN_LOCK[uartCh].lock);

			// Start DMA
			ret = ddUartDmaCopy(uartCh, dmaCh, srcAddr, dstAddr, sendSize);

			if(ret == D_DDIM_OK){
				// Start DMA by UART FIFO interrupt.
				IO_USIO.UART[uartCh].FCR.bit.FTIE = 1;
				DdUart_DSB();

				// Wait end of DMA transfer.
				ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);

				if(ret == D_DDIM_OK){
					// SpinLock.
					Dd_ARM_Critical_Section_Start(S_GDD_UART_SPIN_LOCK[uartCh].lock);

					// Increment read position.
					priv->gDdUartBuffInfo[uartCh].sReadPos += sendSize;
					priv->gDdUartBuffInfo[uartCh].sSize -= sendSize;

					if(priv->gDdUartBuffInfo[uartCh].sReadPos >= priv->gDdUartMng[uartCh].sendBuffSize){
						priv->gDdUartBuffInfo[uartCh].sReadPos -= priv->gDdUartMng[uartCh].sendBuffSize;
						// The flag is dropped
						priv->gDdUartBuffInfo[uartCh].sFlag--;
					}

					// SpinUnLock.
					Dd_ARM_Critical_Section_End(S_GDD_UART_SPIN_LOCK[uartCh].lock);
				}
				else{
					Ddim_Print(("Dd_HDMAC1_Wait_End() error. ret=0x%x\n", ret));
				}
			}
			else{
				Ddim_Print(("ddUartDmaCopy() error. ret=0x%x\n", ret));
			}

			// End DMA transfer process.
			IO_USIO.UART[uartCh].FCR.bit.FTIE = 0;
			DdUart_DSB();
			Dd_HDMAC1_Close(dmaCh);
		}

		while(IO_USIO.UART[uartCh].SSR.bit.__TBI == 0){
			// wait until TDR empty
			DDIM_User_Dly_Tsk(1);
			ret2 = ddUartCheckStoppingConditions(self, uartCh);
			if(ret2 != D_DDIM_OK){
				return ret2;
			}
		}
		if(priv->gDdUartInfo[uartCh].forceStopFlg == 1){
			priv->gDdUartInfo[uartCh].forceStopFlg = 0;
			return DdUart_FORCE_STOP;
		}
	}
	return ret;
}
#endif

#ifdef CO_DDIM_IM_TUNING_ON
void dd_uart_iqtool_enable(DdUart *self)
{
    S_GDD_IQTOOL_STATUS = DdUart_IQTOOL_START;
}

void dd_uart_iqtool_disable(DdUart *self)
{
    S_GDD_IQTOOL_STATUS = DdUart_IQTOOL_IDLE;
}

kchar dd_uart_iqtool_status(DdUart *self)
{
    return S_GDD_IQTOOL_STATUS;
}
#endif

kint32 dd_uart_get_check_stopping_conditions(DdUart *self, kuchar ch)
{
	return ddUartCheckStoppingConditions(self, ch);
}

kuchar dd_uart_get_usio_state(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	return priv->gDdUsioState[ch];
}

DdUartMng dd_uart_get_uart_mng(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	return priv->gDdUartMng[ch];
}

DdUartBufferInfo dd_uart_get_uart_buff_info(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	return priv->gDdUartBuffInfo[ch];
}

kuchar dd_uart_get_uart_flag(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	return priv->gDdUartFlag[ch];
}

DdUartInfo dd_uart_get_uart_info(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	return priv->gDdUartInfo[ch];
}

#ifdef CO_DDIM_IM_TUNING_ON
kuchar dd_uart_get_iqtool_status(DdUart *self)
{
	return S_GDD_IQTOOL_STATUS;
}
#endif

void dd_uart_set_usio_state(DdUart *self, kuchar ch, kuchar stateValue)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUsioState[ch] = stateValue;
}

void dd_uart_set_info_force_stop_flg(DdUart *self, kuchar ch, kuchar stopFlg)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartInfo[ch].forceStopFlg = stopFlg;
}

void dd_uart_set_mng_send_buff_addr(DdUart *self, kuchar ch, kchar str)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartMng[ch].sendBuffAddr[priv->gDdUartBuffInfo[ch].sWritePos] = str;
}

void dd_uart_set_buff_info_write_pos(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	++priv->gDdUartBuffInfo[ch].sWritePos;
}

void dd_uart_set_buff_info_size_add(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	++priv->gDdUartBuffInfo[ch].sSize;
}

void dd_uart_set_buff_info_s_write_pos(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].sWritePos -= priv->gDdUartMng[ch].sendBuffSize;
}

void dd_uart_set_buff_info_flag(DdUart *self, kuchar ch, kuchar flag)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].sFlag = flag;
}

void dd_uart_set_buff_info_overlap(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].sOverlapCnt++;
}

void dd_uart_set_buff_info_read_pos(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	++priv->gDdUartBuffInfo[ch].sReadPos;
}

void dd_uart_set_buff_info_size_subtract(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	--priv->gDdUartBuffInfo[ch].sSize;
}

void dd_uart_set_buff_info_s_read_pos(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].sReadPos -= priv->gDdUartMng[ch].sendBuffSize;
}

void dd_uart_set_buff_info_r_read_pos_add(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	++priv->gDdUartBuffInfo[ch].rReadPos;
}

void dd_uart_set_buff_info_r_size_subtract(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	--priv->gDdUartBuffInfo[ch].rSize;
}

void dd_uart_set_buff_info_r_read_pos(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].rReadPos -= priv->gDdUartMng[ch].receiveBuffSize;
}

void dd_uart_set_buff_info_flag_subtract(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].rFlag--;
}

void dd_uart_set_buff_info_size(DdUart *self, kuchar ch, kuchar flag)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].sSize = flag;
}

void dd_uart_set_info_slave_addr(DdUart *self, kuchar ch, kuchar slaveAddr)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartInfo[ch].multiSlaveAddr = slaveAddr;
}

void dd_uart_set_info_multi_active_flg(DdUart *self, kuchar ch, UartModeMultiAct multiActiveFlg)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartInfo[ch].multiActiveFlg = multiActiveFlg;
}

void dd_uart_set_mng_receive_buff_addr(DdUart *self, kuchar ch, kchar	rData)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartMng[ch].receiveBuffAddr[priv->gDdUartBuffInfo[ch].rWritePos] = rData;
}

void dd_uart_set_buff_info_r_write_pos_add(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	++priv->gDdUartBuffInfo[ch].rWritePos;
}

void dd_uart_set_buff_info_r_size_add(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	++priv->gDdUartBuffInfo[ch].rSize;
}

void dd_uart_set_buff_info_r_write_pos(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].rWritePos -= priv->gDdUartMng[ch].receiveBuffSize;
}

void dd_uart_set_buff_info_flag_add(DdUart *self, kuchar ch)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartBuffInfo[ch].rFlag++;
}

void dd_uart_set_info_send_addr(DdUart *self, kuchar ch, void const* const sendAddr)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartInfo[ch].sendAddr8 = (kuchar*)sendAddr;
}

void dd_uart_set_info_num(DdUart *self, kuchar ch, kuint32 num)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartInfo[ch].num = num;
}

void dd_uart_set_info_dma_wait(DdUart *self, kuchar ch, kuchar dmaWait)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartInfo[ch].dmaWait = dmaWait;
}

void dd_uart_set_info_recv_addr(DdUart *self, kuchar ch, void const* const recvAddr)
{
	DdUartPrivate *priv = DD_UART_GET_PRIVATE(self);
	priv->gDdUartInfo[ch].recvAddr8 = (kuchar*)recvAddr;
}

DdUart* dd_uart_get(void)
{
	DdUart *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_UART, sizeof(DdUartPrivate));
	}

	return self;
}
