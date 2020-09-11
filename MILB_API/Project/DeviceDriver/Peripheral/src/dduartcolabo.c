/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-10
* @author    : 肖泽友
* @brief        :uart driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、colabo section
*
*@version   :1.0.0
*
*/

#include "dd_gic.h"
#include "dd_hdmac1.h"
#include "uart_csio.h"

#include "dduartcolabo.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdUartColabo, dd_uart_colabo);
#define DD_UART_COLABO_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		DdUartColaboPrivate, DD_TYPE_UART_COLABO))

typedef struct _UartDmaCountInfo    UartDmaCountInfo;
typedef struct _DdUartDmaInfo          DdUartDmaInfo;

#ifdef CO_DDIM_UTILITY_USE
/* UART DMA transfer count information */
struct _UartDmaCountInfo
{
	kulong 	transCount;
	kulong 	dmaCount;
	kushort	beatType;
};

/* UART DMA transfer information */
struct _DdUartDmaInfo
{
	UartDmaCountInfo	            countInfo[3];
	T_DD_HDMAC1_CTRL			hdmac1Ctrl;
	kuint32						            count;
	kuint32						            index;
	kuint32						            index2;
	kint32						                result;
	kuchar						            dmaCh;
};
#endif

struct _DdUartColaboPrivate
{
    kint a;
};

#ifdef CO_DDIM_UTILITY_USE
/* UART DMA transfer information */
static volatile DdUartDmaInfo S_GDD_UART_DMA_INFO[DdUart_CH_NUM_MAX][2];

/* UART HDMAC channel information. */
static volatile kuchar S_GDD_UART_DMA_CH_INFO[D_DD_HDMAC1_CH_NUM_MAX];
#endif

/*
 * DECLS
 */
#ifdef CO_DDIM_UTILITY_USE
static void      ddUartEnd(kuchar ch);
static kint32    ddUartStartDma(kuchar dmaCh, T_DD_HDMAC1_CTRL* hdmac1Ctrl);
static void      ddUartSendDma_cb(kuchar dmaCh, kushort* const status);
static void      ddUartRecvDma_cb(kuchar dmaCh, kushort* const status);
#endif

static void dd_uart_colabo_constructor(DdUartColabo *self)
{
	DdUartColaboPrivate *priv = DD_UART_COLABO_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_uart_colabo_destructor(DdUartColabo *self)
{

}

/*
 * IMPL
 */
#ifdef CO_DDIM_UTILITY_USE
static void ddUartEnd(kuchar ch)
{
	// Disable send and receive permission
	IO_USIO.UART[ch].SCR.bit.RXE = 0;
	IO_USIO.UART[ch].SCR.bit.TXE = 0;

	// Disable interrupt
	IO_USIO.UART[ch].SCR.bit.TIE = 0;
	IO_USIO.UART[ch].SCR.bit.TBIE = 0;
	IO_USIO.UART[ch].FCR.bit.FTIE = 0;
	IO_USIO.UART[ch].SCR.bit.RIE  = 0;
	IO_USIO.UART[ch].FCR.bit.FRIIE = 0;

	// Clear buffer overrun error
	IO_USIO.UART[ch].SSR.byte |= DdUart_SSR_REC_BIT;

	// Disable DMA wait
	if(dd_uart_get_uart_info(dd_uart_get(), ch).dmaWait == 1){
		Dd_HDMAC1_Stop(S_GDD_UART_DMA_INFO[ch][DdUart_SEND].dmaCh);
		Dd_HDMAC1_Close(S_GDD_UART_DMA_INFO[ch][DdUart_SEND].dmaCh);
		Dd_HDMAC1_Stop(S_GDD_UART_DMA_INFO[ch][DdUart_RECV].dmaCh);
		Dd_HDMAC1_Close(S_GDD_UART_DMA_INFO[ch][DdUart_RECV].dmaCh);
	}
	dd_uart_set_info_dma_wait(dd_uart_get(), ch, 0);

	dd_uart_set_info_force_stop_flg(dd_uart_get(), ch, 0);

	DdUart_DSB();
}

static kint32 ddUartStartDma(kuchar dmaCh, T_DD_HDMAC1_CTRL* hdmac1Ctrl)
{
	kint32	ret;

	ret = Dd_HDMAC1_Ctrl_Common(dmaCh, hdmac1Ctrl);
	if(ret == D_DDIM_OK){
		ret = Dd_HDMAC1_Start_Async(dmaCh);
		if(ret != D_DDIM_OK){
			Dd_HDMAC1_Close(dmaCh);
			Ddim_Print(("ddUartStartDma: Dd_HDMAC1_Start_Async() error. ret=0x%x\n", ret));
			return ret;
		}
	}
	else{
		Dd_HDMAC1_Close(dmaCh);
		Ddim_Print(("ddUartStartDma: Dd_HDMAC1_Ctrl_Common() error. ret=0x%x\n", ret));
		return ret;
	}

	return ret;
}

static void ddUartSendDma_cb(kuchar dmaCh, kushort* const status)
{
	kint32	ret;
	kuint32	index;
	kuchar	uartCh;

	uartCh = S_GDD_UART_DMA_CH_INFO[dmaCh];
	index = S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index;

	if(*status == D_DD_HDMAC1_SS_NORMAL_END){
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index2++;

		if(S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index2
				< S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].dmaCount){
			IO_USIO.UART[uartCh].FCR.bit.FTIE = 0;
			IO_USIO.UART[uartCh].FCR.bit.FDRQ = 0;
			DdUart_DSB();

			// Resume DMA
			ret = Dd_HDMAC1_Resume(dmaCh);

			// Resume DMA by UART FIFO interrupt.
			IO_USIO.UART[uartCh].FCR.bit.FTIE = 1;
			DdUart_DSB();
			return;
		}

		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index++;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index2 = 0;

		if(S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index
				< S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].count){
			index = S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index;

			// Update source address
			S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.src_addr
			          = Dd_HDMAC1_Get_Src_Addr(dmaCh);

			S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_a.bit.tc
			          = S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].transCount - 1;
			S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_a.bit.bt
			          = S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].beatType;

			if(S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].dmaCount > 1){
				// Enable reload counter
				S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_b.bit.rc
				          = D_DD_HDMAC1_RC_ENABLE;
			}
			else {
				// Disable reload counter
				S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_b.bit.rc
				          = D_DD_HDMAC1_RC_DISABLE;
			}

			IO_USIO.UART[uartCh].FCR.bit.FTIE = 0;
			IO_USIO.UART[uartCh].FCR.bit.FDRQ = 0;
			DdUart_DSB();

			// Start DMA
			ret = ddUartStartDma(dmaCh, (T_DD_HDMAC1_CTRL*)
					&S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl);

			if(ret == D_DDIM_OK){
				// Start DMA by UART FIFO interrupt.
				IO_USIO.UART[uartCh].FCR.bit.FTIE = 1;
				DdUart_DSB();
				return;
			}
			else {
				// Set result
				S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].result = ret;
			}
		}
		else {
			// DMA normal complete
			// Set result
			S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].result = DdUart_NORMAL_COMPLETE;
		}
	}
	else {
		// DMA status error
		Ddim_Print(("ddUartSendDma_cb: Dd_HDMAC1_Wait_End() stop status error. status=%d\n", *status));

		// Set result
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].result = DdUart_DMA_SS_ERROR;
	}

	// End DMA transfer process.
	IO_USIO.UART[uartCh].FCR.bit.FTIE = 0;
	DdUart_DSB();

	if(IO_USIO.UART[uartCh].SSR.bit.__TBI == 0){
		// Wait bus idle interrupt
		dd_uart_set_info_dma_wait(dd_uart_get(), uartCh, 2);
		// Enable UART interrupt
#ifdef CO_PT_ENABLE
		Dd_GIC_Ctrl((E_DD_GIC_INTID)(E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + uartCh), 1, -1, -1);
#else
		DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + uartCh),
				(DDIM_USER_INTLV)D_DD_GIC_PRI14);
#endif
		IO_USIO.UART[uartCh].SCR.bit.TBIE = 1;
		DdUart_DSB();
		return;
	}
	else {
		ddUartEnd(uartCh);
		Dd_HDMAC1_Close(dmaCh);

		if(dd_uart_get_uart_mng(dd_uart_get(), uartCh).sendDmaCallback != NULL){
			((void(*)())dd_uart_get_uart_mng(dd_uart_get(), uartCh).sendDmaCallback)
					(S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].result);
		}
	}
}

static void ddUartRecvDma_cb(kuchar dmaCh, kushort* const status)
{
	kint32	ret;
	kuint32	index;
	kuchar	uartCh;

	uartCh = S_GDD_UART_DMA_CH_INFO[dmaCh];
	index = S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index;

	if(*status == D_DD_HDMAC1_SS_NORMAL_END){
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index2++;

		if(S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index2
				< S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].dmaCount){
			IO_USIO.UART[uartCh].SCR.bit.RIE = 0;
			DdUart_DSB();

			// Resume DMA
			ret = Dd_HDMAC1_Resume(dmaCh);

			// Resume DMA by UART FIFO interrupt.
			// Enable receive interrupt
			IO_USIO.UART[uartCh].SCR.bit.RIE = 1;
			DdUart_DSB();
			return;
		}

		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index++;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index2 = 0;

		if(S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index
				< S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].count){
			index = S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index;

			// Update destination address
			S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.dst_addr
			          = Dd_HDMAC1_Get_Dst_Addr(dmaCh);

			S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_a.bit.tc
			          = S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].transCount - 1;
			S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_a.bit.bt
			          = S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].beatType;

			if(S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].dmaCount > 1){
				// Enable reload counter
				S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_b.bit.rc
				          = D_DD_HDMAC1_RC_ENABLE;
			}
			else {
				// Disable reload counter
				S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_b.bit.rc
				          = D_DD_HDMAC1_RC_DISABLE;
			}

			// Disable receive interrupt
			IO_USIO.UART[uartCh].SCR.bit.RIE = 0;

			// Start DMA
			ret = ddUartStartDma(dmaCh, (T_DD_HDMAC1_CTRL*)
					&S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl);

			if(ret == D_DDIM_OK){
				// Start DMA by UART FIFO interrupt.
				// Enable receive interrupt
				IO_USIO.UART[uartCh].SCR.bit.RIE = 1;
				DdUart_DSB();
				return;
			}
			else {
				// Set result
				S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].result = ret;
			}
		}
		else {
			// DMA normal complete
			// Set result
			S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].result = DdUart_NORMAL_COMPLETE;
		}
	}
	else {	// DMA status error
		Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", *status));

		// Set result
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].result = DdUart_DMA_SS_ERROR;
	}

	// Check for buffer overrun error
	if(IO_USIO.UART[uartCh].SSR.bit.__ORE == 1){
		// Clear buffer overrun error
		IO_USIO.UART[uartCh].SSR.byte |= DdUart_SSR_REC_BIT;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].result = DdUart_OVERRUN_ERROR;
	}

	// End DMA transfer process.
	IO_USIO.UART[uartCh].FCR.bit.FE1 = 0;
	IO_USIO.UART[uartCh].FCR.bit.FE2 = 0;
	DdUart_DSB();

	ddUartEnd(uartCh);
	Dd_HDMAC1_Close(dmaCh);

	if(dd_uart_get_uart_mng(dd_uart_get(), uartCh).recvDmaCallback != NULL){
		((void(*)())dd_uart_get_uart_mng(dd_uart_get(), uartCh).recvDmaCallback)
				(S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].result);
	}
}
#endif

/*
 * PUBLIC
 */
/*
 * @brief	Stop sending/receiving data(force stop)
 * @param	kuchar ch
 * @return	kint32		D_DDIM_OK / DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_colabo_stop(DdUartColabo *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	if(dd_uart_get_uart_info(dd_uart_get(), ch).dmaWait == 1){
		Dd_HDMAC1_Stop(S_GDD_UART_DMA_INFO[ch][DdUart_SEND].dmaCh);
		Dd_HDMAC1_Close(S_GDD_UART_DMA_INFO[ch][DdUart_SEND].dmaCh);
		Dd_HDMAC1_Stop(S_GDD_UART_DMA_INFO[ch][DdUart_RECV].dmaCh);
		Dd_HDMAC1_Close(S_GDD_UART_DMA_INFO[ch][DdUart_RECV].dmaCh);
		dd_uart_set_info_dma_wait(dd_uart_get(), ch, 0);
	}

	// Disable interrupt
	IO_USIO.UART[ch].SCR.bit.RIE	= 0;
	IO_USIO.UART[ch].SCR.bit.TIE	= 0;
	IO_USIO.UART[ch].SCR.bit.TBIE = 0;
	IO_USIO.UART[ch].FCR.bit.FTIE = 0;
	IO_USIO.UART[ch].FCR.bit.FRIIE	= 0;

	// Disable FIFO
	IO_USIO.UART[ch].FCR.bit.FE1 = 0;
	IO_USIO.UART[ch].FCR.bit.FE2 = 0;

	// Soft-Reset
	IO_USIO.UART[ch].SCR.bit.UPCL	 = 1;

	// Disable send/receive
	IO_USIO.UART[ch].SCR.bit.TXE = 0;
	IO_USIO.UART[ch].SCR.bit.RXE = 0;

	dd_uart_set_info_force_stop_flg(dd_uart_get(), ch, 1);

	DdUart_DSB();

	return D_DDIM_OK;
}

/*
 * @brief  It is a function started when the UART transmission is completed.
 * @param  kuchar  ch
 * @return void
 */
void dd_uart_colabo_int_handler_tx(DdUartColabo *self, kuchar ch)
{
	if(dd_uart_get_uart_info(dd_uart_get(), ch).dmaWait){
		if(dd_uart_get_uart_info(dd_uart_get(), ch).dmaWait == 2){
			if(IO_USIO.UART[ch].SSR.bit.__TBI == 1){
				IO_USIO.UART[ch].SCR.bit.TBIE = 0;
				dd_uart_set_info_dma_wait(dd_uart_get(), ch, 0);
				ddUartEnd(ch);
				Dd_HDMAC1_Close(S_GDD_UART_DMA_INFO[ch][DdUart_SEND].dmaCh);

				if(dd_uart_get_uart_mng(dd_uart_get(), ch).sendDmaCallback != NULL){
					((void(*)())dd_uart_get_uart_mng(dd_uart_get(), ch).sendDmaCallback)
							(DdUart_NORMAL_COMPLETE);
				}
				return;
			}
		}
		else {
			// guard
			IO_USIO.UART[ch].FCR.bit.FTIE = 0;
			DdUart_DSB();
			return;
		}
	}

	if(IO_USIO.UART[ch].SSR.bit.__TBI == 1){
		IO_USIO.UART[ch].SCR.bit.TIE = 0;
		IO_USIO.UART[ch].FCR.bit.FTIE = 0;

		DdUart_DSB();

		if((dd_uart_get_uart_mng(dd_uart_get(), ch).psendCallback != NULL)
				&& (dd_uart_get_uart_flag(dd_uart_get(), ch) == 1)){
			(*dd_uart_get_uart_mng(dd_uart_get(), ch).psendCallback)();
		}
	}
}

#ifdef CO_DDIM_UTILITY_USE
/*
 * @brief	Start sending data via DMA and UART FIFO.
 * @param	kuchar	uartCh
 * @param	kuchar	dmaCh
 * @param	kuchar	dma_mode
 * @return	kint32	D_DDIM_OK / DdUart_INPUT_PARAM_ERROR
 * / DdUart_D_DD_UART_FORCE_STOP / DdUart_D_DD_UART_DMA_SS_ERROR
 */
kint32 dd_uart_colabo_start_send_dma(DdUartColabo *self, kuchar uartCh, kuchar dmaCh)
{
	kint32	ret;
	kint32	ret2;
	kuint32	remainNum;
	kuint32	index;
	kuint32	index2;
	kuint32	count = 0;
	kushort	status;

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

	// Open DMA.
	ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return ret;
	}

	/* pgr0584 */
	memset((void*)&S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND], 0,
			sizeof(S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND]));

	S_GDD_UART_DMA_CH_INFO[dmaCh] = uartCh;
	S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].dmaCh = dmaCh;

	// Enable Serial data output permission bit
	IO_USIO.UART[uartCh].SMR.bit.SOE	= 1;
	// Enable transfer permission bit
	IO_USIO.UART[uartCh].SCR.bit.TXE = 1;

	// Sets transmission FIFO, when not set with Dd_UART_Ctrl().
	if(((IO_USIO.UART[uartCh].FCR.bit.FSEL == 0) && (IO_USIO.UART[uartCh].FCR.bit.FE1 == 0)) ||
	   ((IO_USIO.UART[uartCh].FCR.bit.FSEL == 1) && (IO_USIO.UART[uartCh].FCR.bit.FE2 == 0))){
		IO_USIO.UART[uartCh].FCR.bit.FSEL = 0;
		IO_USIO.UART[uartCh].FCR.bit.FE1 = 1;
	}

	// Set DMA info.
	S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_a.bit.is
	          = DdUart_DMACA_IS_BASE + (uartCh << 1) + 1;
	S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_b.bit.fd
	          = D_DD_HDMAC1_FD_FIX;
	if(dd_uart_get_uart_mng(dd_uart_get(), uartCh).sendDmaCallback){
		// Interrupt enable?
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.int_handler
		          = (VP_CALLBACK)ddUartSendDma_cb;
	}
	else {
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.int_handler = NULL;
	}
	// omit BC=0, FS=D_DD_HDMAC1_FS_INCR, RS=D_DD_HDMAC1_RS_DISABLE, RD=D_DD_HDMAC1_RD_DISABLE

	S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_b.bit.tw
	          = D_DD_HDMAC1_TW_BYTE;
	S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.src_addr
	          = (kulong)dd_uart_get_uart_info(dd_uart_get(), uartCh).sendAddr8;
	S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.dst_addr
	          = (kulong)(&(IO_USIO.UART[uartCh].DR));

	remainNum	= dd_uart_get_uart_info(dd_uart_get(), uartCh).num;

	// Set Demand Transfer mode
	S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_b.bit.ms
	          = D_DD_HDMAC1_MS_DEMAND;

	// Set DMA trans count
	if(remainNum > DdUart_DMA_TC_MAX){
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[count].beatType
		          = D_DD_HDMAC1_BT_NORMAL;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[count].transCount
		          = DdUart_DMA_TC_MAX;
		// DdUart_D_DD_UART_DMA_TC_MAX(65536)
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[count].dmaCount
		          = remainNum >> 16;
		remainNum = remainNum % DdUart_DMA_TC_MAX;
		count++;
	}
	if(remainNum != 0) {
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[count].beatType
		          = D_DD_HDMAC1_BT_NORMAL;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[count].transCount = remainNum;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[count].dmaCount = 1;
		remainNum													= 0;
		count++;
	}

	dd_uart_set_info_dma_wait(dd_uart_get(), uartCh, 1);

	for(index=0; index < count; index++){
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_a.bit.tc
		           = S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].transCount - 1;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_a.bit.bt
		           = S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].beatType;
		if(S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].dmaCount > 1){
			// Enable reload counter
			S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_b.bit.rc
			          = D_DD_HDMAC1_RC_ENABLE;
		}

		IO_USIO.UART[uartCh].FCR.bit.FTIE = 0;
		IO_USIO.UART[uartCh].FCR.bit.FDRQ = 0;
		DdUart_DSB();

		// Start DMA
		ret = ddUartStartDma(dmaCh, (T_DD_HDMAC1_CTRL*)
				&S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl);

		if(ret == D_DDIM_OK){
			if(dd_uart_get_uart_mng(dd_uart_get(), uartCh).sendDmaCallback){
				// Interrupt enable?
				S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].count	= count;
				S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index	= 0;
				S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].index2 = 0;

				// Start DMA by UART FIFO interrupt.
				IO_USIO.UART[uartCh].FCR.bit.FTIE = 1;
				DdUart_DSB();

				return D_DDIM_OK;
			}

			// Start DMA by UART FIFO interrupt.
			IO_USIO.UART[uartCh].FCR.bit.FTIE = 1;
			DdUart_DSB();

			// Wait end of DMA transfer.
			ret = Dd_HDMAC1_Set_Wait_Time(dmaCh, D_DDIM_WAIT_END_FOREVER);
			ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
			if(status != D_DD_HDMAC1_SS_NORMAL_END){
				Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
				ret = DdUart_DMA_SS_ERROR;
				break;
			}

			if(S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].dmaCount > 1){
				// Loop by FIFO size or HDMAC max size unit, and restart the DMA
				for(index2=1; index2 < S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].countInfo[index].dmaCount;
						index2++){
					IO_USIO.UART[uartCh].FCR.bit.FTIE = 0;
					IO_USIO.UART[uartCh].FCR.bit.FDRQ = 0;
					DdUart_DSB();

					// Restart DMA
					ret = Dd_HDMAC1_Resume(dmaCh);

					// Restart DMA by UART FIFO interrupt.
					IO_USIO.UART[uartCh].FCR.bit.FTIE = 1;
					DdUart_DSB();

					// Wait end of DMA transfer.
					ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
					if(status != D_DD_HDMAC1_SS_NORMAL_END){
						Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
						ret = DdUart_DMA_SS_ERROR;
						break;
					}
				}
				if(ret != D_DDIM_OK){
					break;
				}
			}
		}
		else {
			// DMA start error
			break;
		}

		// Disable reload counter
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;

		// Update source address
		S_GDD_UART_DMA_INFO[uartCh][DdUart_SEND].hdmac1Ctrl.src_addr = Dd_HDMAC1_Get_Src_Addr(dmaCh);
	}

	// End DMA transfer process.
	IO_USIO.UART[uartCh].FCR.bit.FTIE = 0;
	DdUart_DSB();

	while(IO_USIO.UART[uartCh].SSR.bit.__TBI == 0){
		// wait Bus Idle
		ret2 = dd_uart_get_check_stopping_conditions(dd_uart_get(), uartCh);
		if(ret2 != D_DDIM_OK){
			return ret2;
		}
	}

	if(dd_uart_get_uart_info(dd_uart_get(), uartCh).forceStopFlg == 1){
		ddUartEnd(uartCh);
		return DdUart_FORCE_STOP;
	}

	ddUartEnd(uartCh);
	Dd_HDMAC1_Close(dmaCh);

	return ret;
}

/*
 * @brief	Set data information to receive by UART (DMA).
 * @param	kuchar	ch
 *			void*	recvAddr
 *			kuint32	num
 * @return	kint32	D_DDIM_OK / DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_colabo_set_recv_data_dma(DdUartColabo *self, kuchar ch, void const* const recvAddr, kuint32 num)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(recvAddr == NULL){
		Ddim_Assertion(("UART input param error. [recvAddr] = NULL\n"));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(num == 0){
		Ddim_Assertion(("UART input param error. [num] = %d\n", num));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	dd_uart_set_info_recv_addr(dd_uart_get(), ch, recvAddr);
	dd_uart_set_info_num(dd_uart_get(), ch, num);
	dd_uart_set_info_dma_wait(dd_uart_get(), ch, 0);

	return D_DDIM_OK;
}

/*
 * @brief	Start receive data via DMA and UART FIFO.
 * @param	kuchar	uartCh
 * @param	kuchar	dmaCh
 * @param	kuchar	dma_mode
 * @return	kint32	D_DDIM_OK / DdUart_INPUT_PARAM_ERROR / DdUart_D_DD_UART_DMA_SS_ERROR
 */
kint32 dd_uart_colabo_start_recv_dma(DdUartColabo *self, kuchar uartCh, kuchar dmaCh)
{
	kint32	ret;
	kuint32	remainNum = 0;
	kuint32	index;
	kuint32	index2;
	kuint32	count = 0;
	kushort	status;

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

	// Open DMA.
	ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return ret;
	}

	memset((void*)&S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV], 0,
			sizeof(S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV]));

	S_GDD_UART_DMA_CH_INFO[dmaCh] = uartCh;
	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].dmaCh = dmaCh;

	// Disable Serial data output permission
	IO_USIO.UART[uartCh].SMR.bit.SOE	= 0;
	// Disable transmit interrupt
	IO_USIO.UART[uartCh].SCR.bit.TIE = 0;
	// Disable transmit  bus interrupt
	IO_USIO.UART[uartCh].SCR.bit.TBIE = 0;

	// Set DMA info.
	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_a.bit.is
	           = DdUart_DMACA_IS_BASE + (uartCh << 1);
	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_b.bit.fs	= D_DD_HDMAC1_FS_FIX;
	// HPROT of destination protection (8:cacheable)
	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_b.bit.dp = 8;
	if(dd_uart_get_uart_mng(dd_uart_get(), uartCh).recvDmaCallback){
		// Interrupt enable?
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.int_handler
		           = (VP_CALLBACK)ddUartRecvDma_cb;
	}
	else {
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.int_handler = NULL;
	}
	// omit BC=0, FD=D_DD_HDMAC1_FD_INCR, RS=D_DD_HDMAC1_RS_DISABLE, RD=D_DD_HDMAC1_RD_DISABLE

	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_b.bit.tw
	           = D_DD_HDMAC1_TW_BYTE;
	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.src_addr
	           = (kulong)(&(IO_USIO.UART[uartCh].DR));
	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.dst_addr
	           = (kulong)dd_uart_get_uart_info(dd_uart_get(), uartCh).recvAddr8;

	remainNum	= dd_uart_get_uart_info(dd_uart_get(), uartCh).num;

	dd_uart_set_info_dma_wait(dd_uart_get(), uartCh, 1);

	// Set Demand Transfer mode
	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_b.bit.ms
	           = D_DD_HDMAC1_MS_DEMAND;

	if(remainNum > DdUart_DMA_TC_MAX){
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[count].beatType
		           = D_DD_HDMAC1_BT_NORMAL;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[count].transCount
		           = DdUart_DMA_TC_MAX;
		// DdUart_D_DD_UART_DMA_TC_MAX(65536)
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[count].dmaCount = remainNum >> 16;
		remainNum = remainNum % DdUart_DMA_TC_MAX;
		count++;
	}
	if(remainNum != 0) {
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[count].beatType = D_DD_HDMAC1_BT_NORMAL;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[count].transCount = remainNum;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[count].dmaCount = 1;
		remainNum = 0;
		count++;
	}

	// Enable receive fifo idle detect permission
	IO_USIO.UART[uartCh].FCR.bit.FRIIE = 1;

	// Enable FIFO1
	IO_USIO.UART[uartCh].FCR.bit.FE1 = 1;
	// Enable FIFO2
	IO_USIO.UART[uartCh].FCR.bit.FE2 = 1;

	S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].count = count;

	for(index=0; index < count; index++){
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_a.bit.tc
		           = S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].transCount - 1;
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_a.bit.bt
		           = S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].beatType;
		if(S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].dmaCount > 1){
			// Enable reload counter
			S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_b.bit.rc
			          = D_DD_HDMAC1_RC_ENABLE;
		}

		// Disable receive interrupt
		IO_USIO.UART[uartCh].SCR.bit.RIE = 0;
		DdUart_DSB();

		// Start DMA
		ret = ddUartStartDma(dmaCh, (T_DD_HDMAC1_CTRL*)
				&S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl);

		if(ret == D_DDIM_OK){
			// Interrupt enable?
			if(dd_uart_get_uart_mng(dd_uart_get(), uartCh).recvDmaCallback){
				S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].count = count;
				S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index = 0;
				S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].index2 = 0;

				// Start DMA by UART FIFO interrupt.
				// Enable receive interrupt
				IO_USIO.UART[uartCh].SCR.bit.RIE = 1;
				// Enable receive permission
				IO_USIO.UART[uartCh].SCR.bit.RXE = 1;
				DdUart_DSB();

				return D_DDIM_OK;
			}

			// Start DMA by UART FIFO interrupt.
			// Enable receive interrupt
			IO_USIO.UART[uartCh].SCR.bit.RIE = 1;
			if(index == 0){
				// Enable receive permission
				IO_USIO.UART[uartCh].SCR.bit.RXE = 1;
			}
			DdUart_DSB();

			// Wait end of DMA transfer.
			ret = Dd_HDMAC1_Set_Wait_Time(dmaCh, D_DDIM_WAIT_END_FOREVER);
			ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
			if(status != D_DD_HDMAC1_SS_NORMAL_END){
				Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
				ret = DdUart_DMA_SS_ERROR;
				break;
			}

			if(S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].dmaCount > 1){
				// Loop by HDMAC max size unit, and restart the DMA
				for(index2=1; index2 < S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].countInfo[index].dmaCount;
						index2++){
					IO_USIO.UART[uartCh].SCR.bit.RIE = 0;
					DdUart_DSB();

					// Restart DMA
					ret = Dd_HDMAC1_Resume(dmaCh);

					// Restart DMA by UART FIFO interrupt.
					// Enable receive interrupt
					IO_USIO.UART[uartCh].SCR.bit.RIE = 1;
					DdUart_DSB();

					// Wait end of DMA transfer.
					ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
					if(status != D_DD_HDMAC1_SS_NORMAL_END){
						Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
						ret = DdUart_DMA_SS_ERROR;
						break;
					}
				}
				if(ret != D_DDIM_OK){
					break;
				}
			}
		}
		else {
			// DMA start error
			break;
		}

		// Disable reload counter
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;

		// Update destination address
		S_GDD_UART_DMA_INFO[uartCh][DdUart_RECV].hdmac1Ctrl.dst_addr = Dd_HDMAC1_Get_Dst_Addr(dmaCh);
	}

	// Check for buffer overrun error
	if(IO_USIO.UART[uartCh].SSR.bit.__ORE == 1){
		// Clear buffer overrun error
		IO_USIO.UART[uartCh].SSR.byte |= DdUart_SSR_REC_BIT;
		ret = DdUart_OVERRUN_ERROR;
	}

	// End DMA transfer process.
	IO_USIO.UART[uartCh].FCR.bit.FE1 = 0;
	IO_USIO.UART[uartCh].FCR.bit.FE2 = 0;
	DdUart_DSB();

	ddUartEnd(uartCh);
	Dd_HDMAC1_Close(dmaCh);

	return ret;
}

/*
 * @brief  To disable the transmission and reception.
 * @param  kuchar  ch
 * @return kint32  D_DDIM_OK/DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_colabo_send_recv_disable(DdUartColabo *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	IO_USIO.UART[ch].SCR.bit.TXE = 0;
	IO_USIO.UART[ch].SCR.bit.RXE = 0;

	return D_DDIM_OK;
}
#endif

DdUartColabo* dd_uart_colabo_get(void)
{
	DdUartColabo *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_UART_COLABO, sizeof(DdUartColaboPrivate));
	}

	return self;
}
