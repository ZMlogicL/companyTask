/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-05
* @author    : 肖泽友
* @brief        :SPI(Serial Peripheral Interface) driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、colabo section
*
*@version   :1.0.0
*
*/

#include "spi.h"

#include "ddspicolabo.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdSpiColabo, dd_spi_colabo);
#define DD_SPI_COLABO_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdSpiColaboPrivate, DD_TYPE_SPI_COLABO))

#ifdef CO_DDIM_UTILITY_USE
#define D_DD_SPI_DMACA_IS_BASE		(D_DD_HDMAC1_IS_IDREQ_16)
#endif

struct _DdSpiColaboPrivate
{
    kint a;
};

#ifdef CO_DDIM_UTILITY_USE
/* SPI DMA transfer information */
static volatile DdSpiDmaInfo	S_GDD_SPI_DMA_INFO[DdSpiDriveBranch_CH_MAX][2];

/* SPI HDMAC channel information. */
static volatile kuchar	 S_GDD_SPI_DMA_CH_INFO[D_DD_HDMAC1_CH_NUM_MAX];
#endif

/*
 * DECLS
 */
#ifdef CO_DDIM_UTILITY_USE
static kint32       ddSpiStartDma(kuchar dmaCh, T_DD_HDMAC1_CTRL* const hdmac1Ctrl);
static void         ddSpiSendDma_cb(kuchar dmaCh, kushort* const status);
static void         ddSpiRecvDma_cb(kuchar dmaCh, kushort* const status);
static void         ddSpiSetSendDma(DdSpiColabo* self, kuchar spiCh, kuchar dmaCh);
static void         ddSpiSetRecvDma(DdSpiColabo* self, kuchar spiCh, kuchar dmaCh);
#endif

static void dd_spi_colabo_constructor(DdSpiColabo *self)
{
	DdSpiColaboPrivate *priv = DD_SPI_COLABO_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_spi_colabo_destructor(DdSpiColabo *self)
{

}

/*
 * IMPL
 */
#ifdef CO_DDIM_UTILITY_USE
/*
 * Start DMA
 */
static kint32 ddSpiStartDma(kuchar dmaCh, T_DD_HDMAC1_CTRL* const hdmac1Ctrl)
{
	kint32	ret;

	ret = Dd_HDMAC1_Ctrl_Common(dmaCh, hdmac1Ctrl);
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
		Ddim_Print(("Dd_HDMAC1_Ctrl_Common() error. ret=0x%x\n", ret));
		return ret;
	}

	return ret;
}

/*
 * Callback function of DMA Send
 */
static void ddSpiSendDma_cb(kuchar dmaCh, kushort* const status)
{
	kint32	ret;
	kuint32	index;
	kuchar	spiCh;

	spiCh = S_GDD_SPI_DMA_CH_INFO[dmaCh];

	if(*status == D_DD_HDMAC1_SS_NORMAL_END){
		index = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index2++;

		if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index2
				< S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[index].dmaCount){
			// Resume DMA
			ret = Dd_HDMAC1_Resume(dmaCh);

#ifdef CO_DEBUG_ON_PC
			Ddim_Print(("DMA index  = %u\n", S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index));
			Ddim_Print(("DMA index2 = %u\n", S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index2));
#endif
			return;
		}

		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index++;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index2 = 0;

		if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index
				< S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].count){
			index = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index;

			// Update source address
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.src_addr
			          = Dd_HDMAC1_Get_Src_Addr(dmaCh);

			// Update TC
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_a.bit.tc
			     = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[index].transCount - 1;

			if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[index].dmaCount > 1){
				// Enable reload counter
				S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.rc
				          = D_DD_HDMAC1_RC_ENABLE;
			}
			else {
				// Disable reload counter
				S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.rc
				          = D_DD_HDMAC1_RC_DISABLE;
			}

			// Start DMA
			ret = ddSpiStartDma(dmaCh,
					(T_DD_HDMAC1_CTRL*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl);

#ifdef CO_DEBUG_ON_PC
			Ddim_Print(("DMA index  = %u\n", S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index));
			Ddim_Print(("DMA index2 = %u\n", S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index2));
#endif
			if(ret == D_DDIM_OK){
				return;
			}
			else {
				// Set result
				S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].result = ret;
			}
		}
		else {
			// DMA normal complete
			// Set result
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].result = D_DDIM_OK;
		}
	}
	else {	// DMA status error
		Ddim_Print(("Dd_HDMAC1 stop status error. status=%d\n", *status));

		// Set result
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].result
		          = DdSpiDriveBranch_DMA_SS_ERROR;
	}

	// fullduplex end processing in the receive DMA callback
	if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).spiMode
			!= DdSpiDriveBranch_DIR_FULL){
		if(IO_SPI[spiCh].ST.bit.TXEMPTY == 0){
			// Wait interrupt(TXEMPTYPULSE bit)
			dd_spi_drive_set_branch_spi_info_dma_wait(dd_spi_drive_get(), spiCh, 2);
			IO_SPI[spiCh].INT_EN.word |= DdSpiDriveBranch_INT_TXEMPTYPULSE_BIT;
			DdSpiDriveBranch_DD_SPI_DSB();
		}
		else {
			// Check force stop
			if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).forceStopFlg == 1){
				S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].result
				          = DdSpiDriveBranch_FORCE_STOP;
			}

			// End SPI communication
			dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), spiCh);

			if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).pCallback != NULL){
				((void(*)())dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).pCallback)(spiCh,
						S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].result);
			}
		}
	}

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("DMA index = %u\n", S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index));
	Ddim_Print(("DMA index2 = %u\n", S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].index2));
	Ddim_Print(("dmaWait = %u\n", dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).dmaWait));
#endif
}

/*
 * Callback function of DMA Receive
 */
static void ddSpiRecvDma_cb(kuchar dmaCh, kushort* const status)
{
	kint32	ret;
	kuint32	index;
	kuchar	spiCh;

	spiCh = S_GDD_SPI_DMA_CH_INFO[dmaCh];

	if(*status == D_DD_HDMAC1_SS_NORMAL_END){
		index	= S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index2++;

		if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index2
				< S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[index].dmaCount){
			// Resume DMA
			ret = Dd_HDMAC1_Resume(dmaCh);
			return;
		}

		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index++;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index2 = 0;

		if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index
				< S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].count){
			index = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index;

			// Update destination address
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.dst_addr
			          = Dd_HDMAC1_Get_Dst_Addr(dmaCh);

			// Update TC
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_a.bit.tc
			       = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[index].transCount - 1;

			if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[index].dmaCount > 1){
				// Enable reload counter
				S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.rc
				          = D_DD_HDMAC1_RC_ENABLE;
			}
			else {
				// Disable reload counter
				S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.rc
				         = D_DD_HDMAC1_RC_DISABLE;
			}

			// Start DMA
			ret = ddSpiStartDma(dmaCh,
					(T_DD_HDMAC1_CTRL*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl);
			if(ret == D_DDIM_OK){
				return;
			}
			else {
				// Set result
				S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].result = ret;
			}
		}
		else {
			// DMA normal complete
			// Set result
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].result = D_DDIM_OK;
		}
	}
	else {
		// DMA status error
		Ddim_Print(("Dd_HDMAC1 stop status error. status=%d\n", *status));

		// Set result
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].result
		          = DdSpiDriveBranch_DMA_SS_ERROR;
	}

	// End DMA transfer process.
	// Check force stop and buffer overflow error
	if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).forceStopFlg == 1){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].result
		          = DdSpiDriveBranch_FORCE_STOP;
	}
	else if(IO_SPI[spiCh].ST.bit.RXOVERFLOW == 1){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].result
		          = DdSpiDriveBranch_RECV_OVERRUN_ERROR;
	}

	// End SPI communication
	dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), spiCh);

	if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).pCallback != NULL){
		((void(*)())dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(),
				spiCh).pCallback)(spiCh, S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].result);
	}

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("DMA index = %u\n", S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index));
	Ddim_Print(("DMA index2 = %u\n", S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].index2));
#endif
}

/*
 * Set DMA Send
 */
static void ddSpiSetSendDma(DdSpiColabo* self, kuchar spiCh, kuchar dmaCh)
{
	kuint32	remainNum;
	kuint32	count = 0;

	S_GDD_SPI_DMA_CH_INFO[dmaCh] = spiCh;
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].dmaCh	= dmaCh;

	// Set DMA info.
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_a.bit.is
	          = D_DD_SPI_DMACA_IS_BASE + ((spiCh) << 1) + 1;
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.ms
	          = D_DD_HDMAC1_MS_DEMAND;
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.fd
	          = D_DD_HDMAC1_FD_FIX;
	/*omit BT=D_DD_HDMAC1_BT_NORMAL, BC=0, FS=D_DD_HDMAC1_FS_INCR,
	*RS=D_DD_HDMAC1_RS_DISABLE, RD=D_DD_HDMAC1_RD_DISABLE, DP=0*/

	// Interrupt enable?
	if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).pCallback){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.int_handler
		        = (VP_CALLBACK)ddSpiSendDma_cb;
	}
	else {
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.int_handler = NULL;
	}

	if(IO_SPI[spiCh].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.tw
		          = D_DD_HDMAC1_TW_WORD;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.src_addr
		        = (ULONG)dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).sendAddr32;
	}
	else if(IO_SPI[spiCh].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.tw
		          = D_DD_HDMAC1_TW_HWORD;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.src_addr
		        = (ULONG)dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).sendAddr16;
	}
	else{
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.tw
		          = D_DD_HDMAC1_TW_BYTE;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.src_addr
		          = (ULONG)dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).sendAddr8;
	}
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.dst_addr
	              = (ULONG)(&(IO_SPI[spiCh].TXDATA));

	remainNum = dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).num;

	// Set DMA trans count
	if(remainNum > DdSpiDriveBranch_DMA_TC_MAX){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[count].transCount
		          = DdSpiDriveBranch_DMA_TC_MAX;
		// DdSpiDriveBranch_DMA_TC_MAX(65536)
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[count].dmaCount
		          = remainNum >> 16;
		remainNum = remainNum % DdSpiDriveBranch_DMA_TC_MAX;
		count++;
	}
	if(remainNum != 0){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[count].transCount = remainNum;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[count].dmaCount = 1;
		remainNum = 0;
		count++;
	}

	if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[0].dmaCount > 1){
		// Enable reload counter
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.rc
		          = D_DD_HDMAC1_RC_ENABLE;
	}

	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].count = count;

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("DMA countInfo[0].transCount = %lu\n",
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[0].transCount));
	Ddim_Print(("DMA countInfo[0].dmaCount = %lu\n",
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[0].dmaCount));
	Ddim_Print(("DMA countInfo[1].transCount = %lu\n",
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[1].transCount));
	Ddim_Print(("DMA countInfo[1].dmaCount = %lu\n",
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[1].dmaCount));
#endif
}

/*
 * Set DMA Receive
 */
static void ddSpiSetRecvDma(DdSpiColabo* self, kuchar spiCh, kuchar dmaCh)
{
	kuint32	remainNum;
	kuint32	count = 0;

	S_GDD_SPI_DMA_CH_INFO[dmaCh] = spiCh;
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].dmaCh	= dmaCh;

	// Set DMA info.
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_a.bit.is
	          = D_DD_SPI_DMACA_IS_BASE + ((spiCh) << 1);
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.ms
	          = D_DD_HDMAC1_MS_DEMAND;
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.fs = D_DD_HDMAC1_FS_FIX;
	// HPROT of destination protection (8:cacheable)	// ToDo:ユーザ設定させるか
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.dp = 8;
	/*omit BT=D_DD_HDMAC1_BT_NORMAL, BC=0, FD=D_DD_HDMAC1_FD_INCR,
	*RS=D_DD_HDMAC1_RS_DISABLE, RD=D_DD_HDMAC1_RD_DISABLE*/

	// Interrupt enable?
	if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).pCallback){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.int_handler
		        = (VP_CALLBACK)ddSpiRecvDma_cb;
	}
	else {
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.int_handler = NULL;
	}

	if(IO_SPI[spiCh].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.tw
		        = D_DD_HDMAC1_TW_WORD;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.dst_addr
		        = (ULONG)dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).recvAddr32;
	}
	else if(IO_SPI[spiCh].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.tw
		        = D_DD_HDMAC1_TW_HWORD;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.dst_addr
		        = (ULONG)dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).recvAddr16;
	}
	else{
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.tw
		         = D_DD_HDMAC1_TW_BYTE;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.dst_addr
		         = (ULONG)dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).recvAddr8;
	}
	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.src_addr
	             = (ULONG)(&(IO_SPI[spiCh].RXDATA));

	remainNum = dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).num;

	if(remainNum > DdSpiDriveBranch_DMA_TC_MAX){
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[count].transCount
		          = DdSpiDriveBranch_DMA_TC_MAX;
		// DdSpiDriveBranch_DMA_TC_MAX(65536)
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[count].dmaCount
		          = remainNum >> 16;
		remainNum = remainNum % DdSpiDriveBranch_DMA_TC_MAX;
		count++;
	}

	if(remainNum != 0) {
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[count].transCount = remainNum;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[count].dmaCount = 1;
		remainNum = 0;
		count++;
	}

	if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[0].dmaCount > 1){
		// Enable reload counter
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.rc
		          = D_DD_HDMAC1_RC_ENABLE;
	}

	S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].count = count;

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("DMA countInfo[0].transCount = %lu\n",
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[0].transCount));
	Ddim_Print(("DMA countInfo[0].dmaCount = %lu\n",
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[0].dmaCount));
	Ddim_Print(("DMA countInfo[1].transCount = %lu\n",
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[1].transCount));
	Ddim_Print(("DMA countInfo[1].dmaCount = %lu\n",
			S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[1].dmaCount));
#endif
}

#endif

/*
 * PUBLIC
 */
#ifdef CO_DDIM_UTILITY_USE
/*
 * Start sending data via DMA and SPI FIFO.
 */
kint32 dd_spi_colabo_start_send_dma(DdSpiColabo* self, kuchar spiCh, kuchar dmaCh)
{
	kint32	ret;
	kint32	ret2;
	kuint32	index;
	kuint32	index2;
	kushort	status;

#ifdef CO_PARAM_CHECK
	if(spiCh >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [spiCh] = %d\n", spiCh));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(dmaCh >= D_DD_HDMAC1_CH_NUM_MAX){
		Ddim_Assertion(("SPI input param error. [dmaCh] = %d\n", dmaCh));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	// Open DMA.
	ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return DdSpiDriveBranch_STATUS_ABNORMAL;
	}

	/* pgr0584 */
	memset((void*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND], 0,
			sizeof(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND]));

	dd_spi_drive_set_branch_spi_info_force_stop_flg(dd_spi_drive_get(), spiCh, 0);

	// Set SPI Mode
	dd_spi_drive_set_branch_spi_info_spi_mode(dd_spi_drive_get(), spiCh, DdSpiDriveBranch_DIR_SEND);

	// Set DMA wait status
	dd_spi_drive_set_branch_spi_info_dma_wait(dd_spi_drive_get(), spiCh, 1);

	// Set send DMA info
	ddSpiSetSendDma(self, spiCh, dmaCh);

	// Enable DMA
	IO_SPI[spiCh].CTRL.bit.DMA = 1;

	// Disable RxFIFO
	IO_SPI[spiCh].AUX_CTRL.bit.INHIBITDIN = 1;

	// Write the Enable Register to enable the SPI port
	IO_SPI[spiCh].EN.bit.__ENABLEREQ = 1;
	DdSpiDriveBranch_DD_SPI_DSB();

	// Send loop
	for(index = 0; index < S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].count; index++){
		// Update TC
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_a.bit.tc
		         = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[index].transCount - 1;

		// Start DMA
		ret = ddSpiStartDma(dmaCh,
				(T_DD_HDMAC1_CTRL*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl);
		if(ret != D_DDIM_OK){
			// DMA start error
			break;
		}

		// Interrupt enable?
		if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).pCallback){
			return D_DDIM_OK;
		}

		// Wait end of DMA transfer.
		ret = Dd_HDMAC1_Set_Wait_Time(dmaCh, D_DDIM_WAIT_END_FOREVER);
		ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
		if(status != D_DD_HDMAC1_SS_NORMAL_END){
			Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
			ret = DdSpiDriveBranch_DMA_SS_ERROR;
			break;
		}

		if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[index].dmaCount > 1){
			// Loop by FIFO size or HDMAC max size unit, and restart the DMA
			for(index2 = 1;
					index2 < S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[index].dmaCount;
					index2++){
				// Restart DMA
				ret = Dd_HDMAC1_Resume(dmaCh);

				// Wait end of DMA transfer.
				ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
				if(status != D_DD_HDMAC1_SS_NORMAL_END){
					Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
					ret = DdSpiDriveBranch_DMA_SS_ERROR;
					break;
				}
			}
			if(ret != D_DDIM_OK){
				break;
			}
		}

		// Disable reload counter
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.rc
		          = D_DD_HDMAC1_RC_DISABLE;

		// Update source address
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.src_addr
		          = Dd_HDMAC1_Get_Src_Addr(dmaCh);
	}

	// End DMA transfer process.
	while(IO_SPI[spiCh].ST.bit.TXEMPTY == 0){
		// Wait FIFO Empty
		ret2 = dd_spi_drive_get_branch_check_stopping_conditions(dd_spi_drive_get(), spiCh);
		if(ret2 != D_DDIM_OK){
			Dd_HDMAC1_Close(dmaCh);
			return ret2;
		}
	}

	// Check force stop
	if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).forceStopFlg == 1){
		ret = DdSpiDriveBranch_FORCE_STOP;
	}

	// End SPI communication
	dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), spiCh);

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("DMA index = %u\n", index));
	Ddim_Print(("DMA index2 = %u\n", index2));
#endif

	return ret;
}

/*
 * Start Receive data via DMA and SPI FIFO.
 */
kint32 dd_spi_colabo_start_recv_dma(DdSpiColabo* self, kuchar spiCh, kuchar dmaCh)
{
	kint32	ret;
	kuint32	index;
	kuint32	index2;
	kushort	status;

#ifdef CO_PARAM_CHECK
	if(spiCh >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [spiCh] = %d\n", spiCh));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(dmaCh >= D_DD_HDMAC1_CH_NUM_MAX){
		Ddim_Assertion(("SPI input param error. [dmaCh] = %d\n", dmaCh));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	// Open DMA.
	ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return DdSpiDriveBranch_STATUS_ABNORMAL;
	}

	/* pgr0584 */
	memset((void*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV], 0,
			sizeof(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV]));

	dd_spi_drive_set_branch_spi_info_force_stop_flg(dd_spi_drive_get(), spiCh, 0);

	// Set SPI Mode
	dd_spi_drive_set_branch_spi_info_spi_mode(dd_spi_drive_get(), spiCh, DdSpiDriveBranch_DIR_RECV);

	// Set DMA wait status
	dd_spi_drive_set_branch_spi_info_dma_wait(dd_spi_drive_get(), spiCh, 1);

	// Set receive DMA info
	ddSpiSetRecvDma(self, spiCh, dmaCh);

	// Init dummy count
	dd_spi_drive_set_branch_spi_info_dummy_count(dd_spi_drive_get(), spiCh, 0);

	// Master receiving
	if(IO_SPI[spiCh].CTRL.bit.MASTER == DdSpiDriveBranch_TYPE_MASTER){
		// Set interrupt(TXEMPTYPULSE, TXWMARKPULSE bit)
		IO_SPI[spiCh].INT_EN.word |= DdSpiDriveBranch_INT_TX_CPU_BIT_SET;

		// Set 1st dummy data
		dd_spi_drive_get_branch_write_dummy_count(dd_spi_drive_get(), spiCh);
	}

	// Enable RxFIFO
	IO_SPI[spiCh].AUX_CTRL.bit.INHIBITDIN = 0;

	// Enable DMA
	IO_SPI[spiCh].CTRL.bit.DMA = 1;

	// Write the Enable Register to enable the SPI port
	IO_SPI[spiCh].EN.bit.__ENABLEREQ = 1;
	DdSpiDriveBranch_DD_SPI_DSB();

	// Receive loop
	for(index = 0; index < S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].count; index++){
		// Update TC
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_a.bit.tc
		         = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[index].transCount - 1;

		// Start DMA
		ret = ddSpiStartDma(dmaCh,
				(T_DD_HDMAC1_CTRL*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl);
		if(ret != D_DDIM_OK){
			// DMA start error
			break;
		}

		// Interrupt enable?
		if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).pCallback){
			return D_DDIM_OK;
		}

		// Wait end of DMA transfer.
		ret = Dd_HDMAC1_Set_Wait_Time(dmaCh, D_DDIM_WAIT_END_FOREVER);
		ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
		if(status != D_DD_HDMAC1_SS_NORMAL_END){
			Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
			ret = DdSpiDriveBranch_DMA_SS_ERROR;
			break;
		}

		if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[index].dmaCount > 1){
			// Loop by TC size unit, and restart the DMA
			for(index2 = 1;
					index2 < S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[index].dmaCount;
					index2++){
				// Restart DMA
				ret = Dd_HDMAC1_Resume(dmaCh);

				// Wait end of DMA transfer.
				ret = Dd_HDMAC1_Wait_End(dmaCh, &status, D_DD_HDMAC1_WAITMODE_EVENT);
				if(status != D_DD_HDMAC1_SS_NORMAL_END){
					Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error. status=%d\n", status));
					ret = DdSpiDriveBranch_DMA_SS_ERROR;
					break;
				}
			}

			if(ret != D_DDIM_OK){
				break;
			}
		}

		// Disable reload counter
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.rc
		          = D_DD_HDMAC1_RC_DISABLE;

		// Update destination address
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.dst_addr
		          = Dd_HDMAC1_Get_Dst_Addr(dmaCh);
	}

	// End DMA transfer process.
	// Check force stop and buffer overflow error
	if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).forceStopFlg == 1){
		ret = DdSpiDriveBranch_FORCE_STOP;
	}
	else if(IO_SPI[spiCh].ST.bit.RXOVERFLOW == 1){
		ret = DdSpiDriveBranch_RECV_OVERRUN_ERROR;
	}

	// End SPI communication
	dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), spiCh);

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("DMA index  = %u\n", index));
	Ddim_Print(("DMA index2 = %u\n", index2));
#endif

	return ret;
}

/*
 * Start full duplex communication via DMA and SPI FIFO.
 */
kint32 dd_spi_colabo_start_full_duplex_dma(DdSpiColabo* self,
		kuchar spiCh, kuchar dmaChSend, kuchar dmaChRecv)
{
	kint32	ret;
	kuint32	index;
	kuint32	index2;
	kushort	status;

#ifdef CO_PARAM_CHECK
	if(spiCh >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [spiCh] = %d\n", spiCh));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(dmaChSend >= D_DD_HDMAC1_CH_NUM_MAX){
		Ddim_Assertion(("SPI input param error. [dmaChSend] = %d\n", dmaChSend));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(dmaChRecv >= D_DD_HDMAC1_CH_NUM_MAX){
		Ddim_Assertion(("SPI input param error. [dmaChRecv] = %d\n", dmaChRecv));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	// Open send DMA.
	ret = Dd_HDMAC1_Open(dmaChSend, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return DdSpiDriveBranch_STATUS_ABNORMAL;
	}

	// Open receive DMA.
	ret = Dd_HDMAC1_Open(dmaChRecv, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		Dd_HDMAC1_Close(dmaChSend);
		return DdSpiDriveBranch_STATUS_ABNORMAL;
	}

	/* pgr0584 */
	memset((void*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND], 0,
			sizeof(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND]));
	memset((void*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV], 0,
			sizeof(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV]));

	dd_spi_drive_set_branch_spi_info_force_stop_flg(dd_spi_drive_get(), spiCh, 0);

	// Set SPI Mode
	dd_spi_drive_set_branch_spi_info_spi_mode(dd_spi_drive_get(), spiCh, DdSpiDriveBranch_DIR_FULL);

	// Set DMA wait status
	dd_spi_drive_set_branch_spi_info_dma_wait(dd_spi_drive_get(), spiCh, 1);

	// Set send DMA info
	ddSpiSetSendDma(self, spiCh, dmaChSend);

	// Set receive DMA info
	ddSpiSetRecvDma(self, spiCh, dmaChRecv);

	// Enable RxFIFO
	IO_SPI[spiCh].AUX_CTRL.bit.INHIBITDIN = 0;

	// Enable DMA
	IO_SPI[spiCh].CTRL.bit.DMA = 1;

	// Write the Enable Register to enable the SPI port
	IO_SPI[spiCh].EN.bit.__ENABLEREQ = 1;
	DdSpiDriveBranch_DD_SPI_DSB();

	// Send loop
	for(index = 0; index < S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].count; index++){
		// Update TC
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_a.bit.tc
		        = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[0].transCount - 1;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_a.bit.tc
		        = S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].countInfo[0].transCount - 1;

		// Start send DMA
		ret = ddSpiStartDma(dmaChSend,
				(T_DD_HDMAC1_CTRL*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl);
		if(ret != D_DDIM_OK){
			// DMA start error
			break;
		}

		// Start receive DMA
		ret = ddSpiStartDma(dmaChRecv,
				(T_DD_HDMAC1_CTRL*)&S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl);
		if(ret != D_DDIM_OK){
			// DMA start error
			break;
		}

		// Interrupt enable?
		if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).pCallback){
			return D_DDIM_OK;
		}

		ret = Dd_HDMAC1_Set_Wait_Time(dmaChSend, D_DDIM_WAIT_END_FOREVER);
		ret = Dd_HDMAC1_Set_Wait_Time(dmaChRecv, D_DDIM_WAIT_END_FOREVER);

		// Wait end of Send DMA transfer.
		ret = Dd_HDMAC1_Wait_End(dmaChSend, &status, D_DD_HDMAC1_WAITMODE_EVENT);
		if(status != D_DD_HDMAC1_SS_NORMAL_END){
			Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error(send). status=%d\n", status));
			ret = DdSpiDriveBranch_DMA_SS_ERROR;
			break;
		}

		// Wait end of Receive DMA transfer.
		ret = Dd_HDMAC1_Wait_End(dmaChRecv, &status, D_DD_HDMAC1_WAITMODE_EVENT);
		if(status != D_DD_HDMAC1_SS_NORMAL_END){
			Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error(recv). status=%d\n", status));
			ret = DdSpiDriveBranch_DMA_SS_ERROR;
			break;
		}

		if(S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[index].dmaCount > 1){
			// Loop by FIFO size or HDMAC max size unit, and restart the DMA
			for(index2 = 1;
					index2 < S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].countInfo[index].dmaCount;
					index2++){
				// Restart DMA
				ret = Dd_HDMAC1_Resume(dmaChSend);
				// Restart DMA
				ret = Dd_HDMAC1_Resume(dmaChRecv);

				// Wait end of Send DMA transfer.
				ret = Dd_HDMAC1_Wait_End(dmaChSend, &status, D_DD_HDMAC1_WAITMODE_EVENT);
				if(status != D_DD_HDMAC1_SS_NORMAL_END){
					Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error(send). status=%d\n", status));
					ret = DdSpiDriveBranch_DMA_SS_ERROR;
					break;
				}

				// Wait end of Receive DMA transfer.
				ret = Dd_HDMAC1_Wait_End(dmaChRecv, &status, D_DD_HDMAC1_WAITMODE_EVENT);
				if(status != D_DD_HDMAC1_SS_NORMAL_END){
					Ddim_Print(("Dd_HDMAC1_Wait_End() stop status error(recv). status=%d\n", status));
					ret = DdSpiDriveBranch_DMA_SS_ERROR;
					break;
				}
			}
			if(ret != D_DDIM_OK){
				break;
			}
		}

		// Disable reload counter
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.config_b.bit.rc
		          = D_DD_HDMAC1_RC_DISABLE;
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.config_b.bit.rc
		          = D_DD_HDMAC1_RC_DISABLE;

		// Update source address
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_SEND].hdmac1Ctrl.src_addr
		          = Dd_HDMAC1_Get_Src_Addr(dmaChSend);
		S_GDD_SPI_DMA_INFO[spiCh][DdSpiDriveBranch_RECV].hdmac1Ctrl.dst_addr
		          = Dd_HDMAC1_Get_Dst_Addr(dmaChRecv);
	}

	// End DMA transfer process.
	// Check force stop and buffer overflow error
	if(dd_spi_drive_get_branch_spi_info(dd_spi_drive_get(), spiCh).forceStopFlg == 1){
		ret = DdSpiDriveBranch_FORCE_STOP;
	}
	else if(IO_SPI[spiCh].ST.bit.RXOVERFLOW == 1){
		ret = DdSpiDriveBranch_RECV_OVERRUN_ERROR;
	}

	// End SPI communication
	dd_spi_drive_get_branch_end_process(dd_spi_drive_get(), spiCh);

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("DMA index  = %u\n", index));
	Ddim_Print(("DMA index2 = %u\n", index2));
#endif

	return ret;
}

#endif

DdSpiDmaInfo dd_spi_colabo_get_dma_info(DdSpiColabo* self, kuchar chA, kuchar chB)
{
	return S_GDD_SPI_DMA_INFO[chA][chB];
}

DdSpiColabo* dd_spi_colabo_get(void)
{
	DdSpiColabo *self = NULL;
	if(!self)
	{
		self = k_object_new_with_private(DD_TYPE_SPI_COLABO, sizeof(DdSpiColaboPrivate));
	}

	return self;
}
