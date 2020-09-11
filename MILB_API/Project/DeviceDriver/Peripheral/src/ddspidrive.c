/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-04
* @author    : 肖泽友
* @brief        :SPI(Serial Peripheral Interface) driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、driver section
*
*@version   :1.0.0
*
*/

#include "spi.h"
#include "dd_top.h"
#include "ddspicolabo.h"

#include "ddspidrive.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdSpiDrive, dd_spi_drive);
#define DD_SPI_DRIVE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdSpiDrivePrivate, DD_TYPE_SPI_DRIVE))

struct _DdSpiDrivePrivate
{
	DdSpiDriveBranch  *ddSpiDriveBranch;
};

static void dd_spi_drive_constructor(DdSpiDrive *self)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
    priv->ddSpiDriveBranch = dd_spi_drive_branch_new();
}

static void dd_spi_drive_destructor(DdSpiDrive *self)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	if(priv->ddSpiDriveBranch){
		k_object_unref(priv->ddSpiDriveBranch);
		priv->ddSpiDriveBranch = NULL;
	}
}

/*
 * PUBLIC
 */
/*
 * Open SPI Channel
 */
kint32 dd_spi_drive_open(DdSpiDrive* self, kuchar ch, kint32 timeOut)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(timeOut < D_DDIM_USER_SEM_WAIT_FEVR){
		Ddim_Assertion(("SPI: input param error. timeOut = %x\n", timeOut));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	if(timeOut == D_DDIM_USER_SEM_WAIT_POL) {
		ercd = DDIM_User_Pol_Sem(SID_DD_SPI(ch));
	}
	else{
		ercd = DDIM_User_Twai_Sem(SID_DD_SPI(ch), (DDIM_USER_TMO)timeOut);
	}

	if(ercd != D_DDIM_USER_E_OK) {
		if(D_DDIM_USER_E_TMOUT == ercd) {
			return DdSpiDriveBranch_SEM_TIMEOUT;
		}
		return DdSpiDriveBranch_SEM_NG;
	}

	return D_DDIM_OK;
}

/*
 * Close SPI Channel
 */
kint32 dd_spi_drive_close(DdSpiDrive* self, kuchar ch)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	ercd = DDIM_User_Sig_Sem(SID_DD_SPI(ch));

	if(D_DDIM_USER_E_OK != ercd) {
		return DdSpiDriveBranch_SEM_NG;
	}

	return D_DDIM_OK;
}

/*
 * Set SPI Control
 */
kint32 dd_spi_drive_ctrl(DdSpiDrive* self, kuchar ch, TDdSpiCtrl const* const spiCtrl)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	kint32 wait;
	TDdSpiInfo ddSpiInformation;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(spiCtrl == NULL){
		Ddim_Assertion(("SPI input param error. [spiCtrl] = NULL\n"));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	ddSpiInformation = dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch);

	memset((void*)&ddSpiInformation, 0, sizeof(TDdSpiInfo));

	// 1) Write Enable Register to disable the SPI port and TX/RX FIFOs
	IO_SPI[ch].EN.bit.__ENABLEREQ = 0;
	DdSpiDriveBranch_DD_SPI_DSB();

	// 2) Read the Enable Register - it should be 0 before continuing to the next step.
	for(wait = 0; wait < 1000; wait++){
		if(IO_SPI[ch].EN.bit.__ENABLEREQ == 0){
			break;
		}
	}
	if(IO_SPI[ch].EN.bit.__ENABLEREQ != 0){
		return DdSpiDriveBranch_STATUS_ABNORMAL;
	}

	// 3) Clear any interrupts by writing 'h0000_01FF to Interrupt Clear Register.
	IO_SPI[ch].INT_CLR.word = DdSpiDriveBranch_INT_ALL_BIT_SET;

	// 4) If using interrupts, enable interrupts by writing the Interrupt Enable Register.
	dd_spi_drive_branch_set_spi_info_pcallback(priv->ddSpiDriveBranch, ch, spiCtrl->pCallback);
	dd_spi_drive_branch_set_spi_info_pcallback_ss(priv->ddSpiDriveBranch, ch, spiCtrl->pCallbackSs);
	if(dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).pCallbackSs){
		IO_SPI[ch].INT_EN.word = DdSpiDriveBranch_INT_XFERDONEPULSE_BIT;
	}

	// 5) Set the polarity of the select lines by writing the Slave Select Polarity Register.
	IO_SPI[ch].SLV_POL.bit.SSPOL0 = spiCtrl->ssInfo.sspol[0];
	IO_SPI[ch].SLV_POL.bit.SSPOL1 = spiCtrl->ssInfo.sspol[1];
	IO_SPI[ch].SLV_POL.bit.SSPOL2 = spiCtrl->ssInfo.sspol[2];
	IO_SPI[ch].SLV_POL.bit.SSPOL3 = spiCtrl->ssInfo.sspol[3];

	// 6) If a master, select which slave is to be selected by writing the Slave Select Register.
	IO_SPI[ch].SLV_SEL.bit.SSOUT0 = spiCtrl->ssInfo.ssout[0];
	IO_SPI[ch].SLV_SEL.bit.SSOUT1 = spiCtrl->ssInfo.ssout[1];
	IO_SPI[ch].SLV_SEL.bit.SSOUT2 = spiCtrl->ssInfo.ssout[2];
	IO_SPI[ch].SLV_SEL.bit.SSOUT3 = spiCtrl->ssInfo.ssout[3];

	// 7) If a master, and if a large inter-transfer delay is desired for use with low-performance slaves,
	//    write the Master Inter-Transfer Delay Register.
	if(spiCtrl->delayEn){
		IO_SPI[ch].MS_DLY.bit.MWAIT = spiCtrl->delayVal;
	}
	else {
		IO_SPI[ch].MS_DLY.bit.MWAIT = 0;
	}

	// 8) If a master, and if DMA operation is desired, write to the DMA Timeout Register to set the DMA Timeout Value.
	if(spiCtrl->dmaEn){
		IO_SPI[ch].DMA_TO.bit.TIMEOUT = spiCtrl->dmaRecvTo;
	}
	else {
		// default
		IO_SPI[ch].DMA_TO.bit.TIMEOUT = 0x00800000;
	}

	// 9) Write Control Register
	// a. inter-transfer delay enable (master)
	IO_SPI[ch].CTRL.bit.MWAITEN = spiCtrl->delayEn;

	// b. dmaEnable
	IO_SPI[ch].CTRL.bit.DMA = spiCtrl->dmaEn;

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	if(spiCtrl->type == DdSpiDriveBranch_E_DD_SPI_TYPE_SLAVE){
		switch(ch){
			case 0:
				Dd_Top_Set_PERSEL2_SPIMSEN0(0);
				break;
			case 1:
				Dd_Top_Set_PERSEL2_SPIMSEN1(0);
				break;
			case 2:
				Dd_Top_Set_PERSEL2_SPIMSEN2(0);
				break;
			default:
				return DdSpiDriveBranch_INPUT_PARAM_ERROR;
		}
	}
	else{	// Master
		switch(ch){
			case 0:
				Dd_Top_Set_PERSEL2_SPIMSEN0(1);
				break;
			case 1:
				Dd_Top_Set_PERSEL2_SPIMSEN1(1);
				break;
			case 2:
				Dd_Top_Set_PERSEL2_SPIMSEN2(1);
				break;
			default:
				return DdSpiDriveBranch_INPUT_PARAM_ERROR;
		}
	}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	// c. master or slave mode
	IO_SPI[ch].CTRL.bit.MASTER = spiCtrl->type;

	// d. cpol
	// e. cpha
	switch(spiCtrl->mode){
		case DdSpiDriveBranch_MODE_0_CPOL0_CPHA0:
			IO_SPI[ch].CTRL.bit.CPOL = 0;
			IO_SPI[ch].CTRL.bit.CPHA = 0;
			break;

		case DdSpiDriveBranch_MODE_1_CPOL0_CPHA1:
			IO_SPI[ch].CTRL.bit.CPOL = 0;
			IO_SPI[ch].CTRL.bit.CPHA = 1;
			break;

		case DdSpiDriveBranch_MODE_2_CPOL1_CPHA0:
			IO_SPI[ch].CTRL.bit.CPOL = 1;
			IO_SPI[ch].CTRL.bit.CPHA = 0;
			break;

		case DdSpiDriveBranch_MODE_3_CPOL1_CPHA1:
			IO_SPI[ch].CTRL.bit.CPOL = 1;
			IO_SPI[ch].CTRL.bit.CPHA = 1;
			break;

		default:
			return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}

	// f. msb1st
	IO_SPI[ch].CTRL.bit.MSB1ST = spiCtrl->bitDirection;

	// g. divisorEnable (master)
	if(spiCtrl->clkDiv){
		IO_SPI[ch].CTRL.bit.DIVENABLE = 1;
		IO_SPI[ch].DIV.bit.DIVISOR = spiCtrl->clkDiv;
	}
	else {
		IO_SPI[ch].CTRL.bit.DIVENABLE = 0;
		IO_SPI[ch].DIV.bit.DIVISOR = 0;
	}

	// h. continuous transfer enable (master)

	// 10) Write Auxiliary Control Register
	// a. continuous transfer extend (master)
	if(spiCtrl->ssInfo.contTrans == DdSpiDriveBranch_CONT_TRANS_ACT_FIFO_EMPTY){
		IO_SPI[ch].CTRL.bit.CONTXFER = 1;
		IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND = 1;
	}
	else if(spiCtrl->ssInfo.contTrans == DdSpiDriveBranch_CONT_TRANS_INACT_FIFO_EMPTY){
		IO_SPI[ch].CTRL.bit.CONTXFER = 1;
		IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND = 0;
	}
	else {
		IO_SPI[ch].CTRL.bit.CONTXFER = 0;
		IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND = 0;
	}

	// b. bitsize (from 4 to 16 bits)
	IO_SPI[ch].AUX_CTRL.bit.BITSIZE = spiCtrl->bitLength;

	// c. inhibit writes to RX FIFO
	IO_SPI[ch].AUX_CTRL.bit.INHIBITDIN = spiCtrl->rxInhibitEn;

	// d. Spi mode
	// Normal SPI only
	IO_SPI[ch].AUX_CTRL.bit.SPIMODE = 0;

	// SPI Format
	// Motorola SPI only
	IO_SPI[ch].AUX_CTRL.bit.XFERFORMAT = 0;

	// Write the Enable Signal Select
	IO_SPI[ch].EN.bit.__EXTENSEL = spiCtrl->enableSig;

	// Write TXTX/RX FIFO Watermark
	IO_SPI[ch].FIFO_WMK.bit.TXWMARKSET = spiCtrl->fifoWmarkTx;
	IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET = spiCtrl->fifoWmarkRx;

	DdSpiDriveBranch_DD_SPI_DSB();

	return D_DDIM_OK;
}

/*
 * Get SPI Control
 */
kint32 dd_spi_drive_get_ctrl(DdSpiDrive* self, kuchar ch, TDdSpiCtrl* const spiCtrl)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(spiCtrl == NULL){
		Ddim_Assertion(("SPI input param error. [spiCtrl] = NULL\n"));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	spiCtrl->pCallback = dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).pCallback;
	spiCtrl->pCallbackSs = dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).pCallbackSs;

	spiCtrl->ssInfo.sspol[0] = IO_SPI[ch].SLV_POL.bit.SSPOL0;
	spiCtrl->ssInfo.sspol[1] = IO_SPI[ch].SLV_POL.bit.SSPOL1;
	spiCtrl->ssInfo.sspol[2] = IO_SPI[ch].SLV_POL.bit.SSPOL2;
	spiCtrl->ssInfo.sspol[3] = IO_SPI[ch].SLV_POL.bit.SSPOL3;

	spiCtrl->ssInfo.ssout[0] = IO_SPI[ch].SLV_SEL.bit.SSOUT0;
	spiCtrl->ssInfo.ssout[1] = IO_SPI[ch].SLV_SEL.bit.SSOUT1;
	spiCtrl->ssInfo.ssout[2] = IO_SPI[ch].SLV_SEL.bit.SSOUT2;
	spiCtrl->ssInfo.ssout[3] = IO_SPI[ch].SLV_SEL.bit.SSOUT3;

	spiCtrl->delayVal	= IO_SPI[ch].MS_DLY.bit.MWAIT;
	spiCtrl->dmaRecvTo = IO_SPI[ch].DMA_TO.bit.TIMEOUT;

	spiCtrl->delayEn	= IO_SPI[ch].CTRL.bit.MWAITEN;
	spiCtrl->dmaEn = IO_SPI[ch].CTRL.bit.DMA;
	spiCtrl->type = IO_SPI[ch].CTRL.bit.MASTER;

	if(IO_SPI[ch].CTRL.bit.CPOL == 0){
		if(IO_SPI[ch].CTRL.bit.CPHA == 0){
			spiCtrl->mode = DdSpiDriveBranch_MODE_0_CPOL0_CPHA0;
		}
		else {
			spiCtrl->mode = DdSpiDriveBranch_MODE_1_CPOL0_CPHA1;
		}
	}
	else {
		if(IO_SPI[ch].CTRL.bit.CPHA == 0){
			spiCtrl->mode = DdSpiDriveBranch_MODE_2_CPOL1_CPHA0;
		}
		else {
			spiCtrl->mode = DdSpiDriveBranch_MODE_3_CPOL1_CPHA1;
		}
	}

	spiCtrl->bitDirection = IO_SPI[ch].CTRL.bit.MSB1ST;
	spiCtrl->clkDiv = IO_SPI[ch].CTRL.bit.DIVENABLE;
	spiCtrl->clkDiv = IO_SPI[ch].DIV.bit.DIVISOR;

	if(IO_SPI[ch].CTRL.bit.CONTXFER == 1){
		if(IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND == 1){
			spiCtrl->ssInfo.contTrans = DdSpiDriveBranch_CONT_TRANS_ACT_FIFO_EMPTY;
		}
		else {
			spiCtrl->ssInfo.contTrans = DdSpiDriveBranch_CONT_TRANS_INACT_FIFO_EMPTY;
		}
	}
	else {
		spiCtrl->ssInfo.contTrans = DdSpiDriveBranch_CONT_TRANS_INACT_BETWEEN;
	}

	spiCtrl->bitLength = IO_SPI[ch].AUX_CTRL.bit.BITSIZE;
	spiCtrl->rxInhibitEn = IO_SPI[ch].AUX_CTRL.bit.INHIBITDIN;

	spiCtrl->enableSig = IO_SPI[ch].EN.bit.__EXTENSEL;

	spiCtrl->fifoWmarkTx = IO_SPI[ch].FIFO_WMK.bit.TXWMARKSET;
	spiCtrl->fifoWmarkRx = IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET;

	return D_DDIM_OK;
}

/*
 * Set sending data information
 */
kint32 dd_spi_drive_set_send_data(DdSpiDrive* self, kuchar ch, void const* const sendAddr, kuint32 num)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(sendAddr == NULL){
		Ddim_Assertion(("SPI input param error. [sendAddr] = NULL\n"));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(num == 0){
		Ddim_Assertion(("SPI input param error. [num] = %d\n", num));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
		dd_spi_drive_branch_set_spi_info_send_addr32(priv->ddSpiDriveBranch, ch, (kuint32*)sendAddr);
	}
	else if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
		dd_spi_drive_branch_set_spi_info_send_addr16(priv->ddSpiDriveBranch, ch, (USHORT*)sendAddr);
	}
	else{
		dd_spi_drive_branch_set_spi_info_send_addr8(priv->ddSpiDriveBranch, ch, (kuchar*)sendAddr);
	}

	dd_spi_drive_branch_set_spi_info_num(priv->ddSpiDriveBranch, ch, num);
	dd_spi_drive_branch_set_spi_info_send_pos(priv->ddSpiDriveBranch, ch, 0);

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("gDD_SPI_Info[%d].send_addr8  = 0x%08X\n", ch,
			(kuint32)dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).sendAddr8));
	Ddim_Print(("gDD_SPI_Info[%d].send_addr16 = 0x%08X\n", ch,
			(kuint32)dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).sendAddr16));
	Ddim_Print(("gDD_SPI_Info[%d].num         = %u\n", ch,
			dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).num));
	Ddim_Print(("gDD_SPI_Info[%d].sendPos    = %u\n", ch,
			dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).sendPos));
#endif

	return D_DDIM_OK;
}

/*
 * Set receiving data information
 */
kint32 dd_spi_drive_set_recv_data(DdSpiDrive* self, kuchar ch, void const* const recvAddr, kuint32 num)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(recvAddr == NULL){
		Ddim_Assertion(("SPI input param error. [recvAddr] = NULL\n"));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(num == 0){
		Ddim_Assertion(("SPI input param error. [num] = %d\n", num));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_16){
		dd_spi_drive_branch_set_spi_info_recv_addr32(priv->ddSpiDriveBranch, ch, (kuint32*)recvAddr);
	}
	else if(IO_SPI[ch].AUX_CTRL.bit.BITSIZE > DdSpiDriveBranch_BIT_LEN_8){
		dd_spi_drive_branch_set_spi_info_recv_addr16(priv->ddSpiDriveBranch, ch, (USHORT*)recvAddr);
	}
	else{
		dd_spi_drive_branch_set_spi_info_recv_addr8(priv->ddSpiDriveBranch, ch, (kuchar*)recvAddr);
	}

	dd_spi_drive_branch_set_spi_info_num(priv->ddSpiDriveBranch, ch, num);
	dd_spi_drive_branch_set_spi_info_recv_pos(priv->ddSpiDriveBranch, ch, 0);
	dd_spi_drive_branch_set_spi_info_dummy_count(priv->ddSpiDriveBranch, ch, 0);

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("gDD_SPI_Info[%d].recv_addr8 = 0x%08X\n", ch,
			(kuint32)dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).recvAddr8));
	Ddim_Print(("gDD_SPI_Info[%d].recv_addr16 = 0x%08X\n", ch,
			(kuint32)dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).recvAddr16));
	Ddim_Print(("gDD_SPI_Info[%d].num = %u\n", ch,
			dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).num));
	Ddim_Print(("gDD_SPI_Info[%d].recvPos = %u\n", ch,
			dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).recvPos));
	Ddim_Print(("gDD_SPI_Info[%d].dummyCount = %u\n", ch,
			dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).dummyCount));
#endif

	return D_DDIM_OK;
}

/*
 * Stop sending/receiving data(force stop)
 */
kint32 dd_spi_drive_stop(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	kint32 wait;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	dd_spi_drive_branch_set_spi_info_force_stop_flg(priv->ddSpiDriveBranch, ch, 1);

	if(dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).dmaWait >= 1){
		if((dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).spiMode
				== DdSpiDriveBranch_DIR_SEND)
				|| (dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).spiMode
						== DdSpiDriveBranch_DIR_FULL)){
			Dd_HDMAC1_Stop(dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
					DdSpiDriveBranch_SEND).dmaCh);
			Dd_HDMAC1_Close(dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
					DdSpiDriveBranch_SEND).dmaCh);
		}
		if((dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).spiMode
				== DdSpiDriveBranch_DIR_RECV)
				|| (dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch).spiMode
						== DdSpiDriveBranch_DIR_FULL)){
			Dd_HDMAC1_Stop(dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
					DdSpiDriveBranch_RECV).dmaCh);
			Dd_HDMAC1_Close(dd_spi_colabo_get_dma_info(dd_spi_colabo_get(), ch,
					DdSpiDriveBranch_RECV).dmaCh);
		}
		dd_spi_drive_branch_set_spi_info_dma_wait(priv->ddSpiDriveBranch, ch, 0);
	}

	IO_SPI[ch].INT_EN.word = 0;

	IO_SPI[ch].EN.bit.__ENABLEREQ = 0;
	DdSpiDriveBranch_DD_SPI_DSB();

	for(wait = 0; wait < 1000; wait++){
		if(IO_SPI[ch].EN.bit.__ENABLEREQ == 0){
			break;
		}
	}
	if(IO_SPI[ch].EN.bit.__ENABLEREQ != 0){
		return DdSpiDriveBranch_STATUS_ABNORMAL;
	}

	return D_DDIM_OK;
}

/*
 * Set SPI Slave Select setting
 */
kint32 dd_spi_drive_set_slave_select(DdSpiDrive* self, kuchar ch, DdSpiSsInfo const* const ssInfo)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(ssInfo == NULL){
		Ddim_Assertion(("SPI input param error. [ssInfo] = NULL\n"));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	IO_SPI[ch].SLV_POL.bit.SSPOL0 = ssInfo->sspol[0];
	IO_SPI[ch].SLV_POL.bit.SSPOL1 = ssInfo->sspol[1];
	IO_SPI[ch].SLV_POL.bit.SSPOL2 = ssInfo->sspol[2];
	IO_SPI[ch].SLV_POL.bit.SSPOL3 = ssInfo->sspol[3];

	IO_SPI[ch].SLV_SEL.bit.SSOUT0 = ssInfo->ssout[0];
	IO_SPI[ch].SLV_SEL.bit.SSOUT1 = ssInfo->ssout[1];
	IO_SPI[ch].SLV_SEL.bit.SSOUT2 = ssInfo->ssout[2];
	IO_SPI[ch].SLV_SEL.bit.SSOUT3 = ssInfo->ssout[3];

	if(ssInfo->contTrans == DdSpiDriveBranch_CONT_TRANS_ACT_FIFO_EMPTY){
		IO_SPI[ch].CTRL.bit.CONTXFER = 1;
		IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND = 1;
	}
	else if(ssInfo->contTrans == DdSpiDriveBranch_CONT_TRANS_INACT_FIFO_EMPTY){
		IO_SPI[ch].CTRL.bit.CONTXFER = 1;
		IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND = 0;
	}
	else {
		IO_SPI[ch].CTRL.bit.CONTXFER = 0;
		IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND = 0;
	}

	return D_DDIM_OK;
}

/*
 * Get SPI Slave Select setting
 */
kint32 dd_spi_drive_get_slave_select(DdSpiDrive* self, kuchar ch, DdSpiSsInfo* const ssInfo)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(ssInfo == NULL){
		Ddim_Assertion(("SPI input param error. [ssInfo] = NULL\n"));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	ssInfo->sspol[0] = IO_SPI[ch].SLV_POL.bit.SSPOL0;
	ssInfo->sspol[1] = IO_SPI[ch].SLV_POL.bit.SSPOL1;
	ssInfo->sspol[2] = IO_SPI[ch].SLV_POL.bit.SSPOL2;
	ssInfo->sspol[3] = IO_SPI[ch].SLV_POL.bit.SSPOL3;

	ssInfo->ssout[0] = IO_SPI[ch].SLV_SEL.bit.SSOUT0;
	ssInfo->ssout[1] = IO_SPI[ch].SLV_SEL.bit.SSOUT1;
	ssInfo->ssout[2] = IO_SPI[ch].SLV_SEL.bit.SSOUT2;
	ssInfo->ssout[3] = IO_SPI[ch].SLV_SEL.bit.SSOUT3;

	if(IO_SPI[ch].CTRL.bit.CONTXFER == 1){
		if(IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND == 1){
			ssInfo->contTrans = DdSpiDriveBranch_CONT_TRANS_ACT_FIFO_EMPTY;
		}
		else {
			ssInfo->contTrans = DdSpiDriveBranch_CONT_TRANS_INACT_FIFO_EMPTY;
		}
	}
	else {
		ssInfo->contTrans = DdSpiDriveBranch_CONT_TRANS_INACT_BETWEEN;
	}

	return D_DDIM_OK;
}

/*
 * Set SPI Enable
 */
kint32 dd_spi_drive_set_spi_enable(DdSpiDrive* self, kuchar ch, DdSpiEnableSig enableSig, kboolean enable)
{
	kint32 wait;

#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	if(IO_SPI[ch].EN.bit.__ENABLEREQ){
		// 1) Write Enable Register to disable the SPI port and TX/RX FIFOs
		IO_SPI[ch].EN.bit.__ENABLEREQ = 0;
		DdSpiDriveBranch_DD_SPI_DSB();

		// 2) Read the Enable Register - it should be 0 before continuing to the next step.
		for(wait = 0; wait < 1000; wait++){
			if(IO_SPI[ch].EN.bit.__ENABLEREQ == 0){
				break;
			}
		}
		if(IO_SPI[ch].EN.bit.__ENABLEREQ != 0){
			return DdSpiDriveBranch_STATUS_ABNORMAL;
		}
	}

	IO_SPI[ch].EN.word = enableSig | enable;
	DdSpiDriveBranch_DD_SPI_DSB();

	return D_DDIM_OK;
}

kint32 dd_spi_drive_start_full_duplex(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	return dd_spi_drive_branch_start_full_duplex(priv->ddSpiDriveBranch, ch);
}

kint32 dd_spi_drive_start_recv(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	return dd_spi_drive_branch_start_recv(priv->ddSpiDriveBranch, ch);
}

kint32 dd_spi_drive_start_send(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	return dd_spi_drive_branch_start_send(priv->ddSpiDriveBranch, ch);
}

void dd_spi_drive_get_branch_end_process(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	dd_spi_drive_branch_get_end_process(priv->ddSpiDriveBranch, ch);
}

void dd_spi_drive_get_branch_send_data(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	dd_spi_drive_branch_get_send_data(priv->ddSpiDriveBranch, ch);
}

void dd_spi_drive_get_branch_write_dummy_count(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	dd_spi_drive_branch_get_write_dummy_count(priv->ddSpiDriveBranch, ch);
}

kint32 dd_spi_drive_get_branch_check_stopping_conditions(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	return dd_spi_drive_branch_get_check_stopping_conditions(priv->ddSpiDriveBranch, ch);
}

TDdSpiInfo dd_spi_drive_get_branch_spi_info(DdSpiDrive* self, kuchar ch)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	return dd_spi_drive_branch_get_spi_info(priv->ddSpiDriveBranch, ch);
}

void dd_spi_drive_set_branch_spi_info_add_recv_pos(DdSpiDrive* self, kuchar ch, kuint32 recvPos)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	dd_spi_drive_branch_set_spi_info_add_recv_pos(priv->ddSpiDriveBranch, ch, recvPos);
}

void dd_spi_drive_set_branch_spi_info_dma_wait(DdSpiDrive* self, kuchar ch, kuchar dmaWait)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	dd_spi_drive_branch_set_spi_info_dma_wait(priv->ddSpiDriveBranch, ch, dmaWait);
}

void dd_spi_drive_set_branch_spi_info_force_stop_flg(DdSpiDrive* self, kuchar ch, kuchar forceStopFlg)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	dd_spi_drive_branch_set_spi_info_force_stop_flg(priv->ddSpiDriveBranch, ch, forceStopFlg);
}

void dd_spi_drive_set_branch_spi_info_spi_mode(DdSpiDrive* self, kuchar ch, EDdSpiDir spiMode)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	dd_spi_drive_branch_set_spi_info_spi_mode(priv->ddSpiDriveBranch, ch, spiMode);
}

void dd_spi_drive_set_branch_spi_info_dummy_count(DdSpiDrive* self, kuchar ch, kuint32 dummyCount)
{
	DdSpiDrivePrivate *priv = DD_SPI_DRIVE_GET_PRIVATE(self);
	dd_spi_drive_branch_set_spi_info_dummy_count(priv->ddSpiDriveBranch, ch, dummyCount);
}

DdSpiDrive* dd_spi_drive_get(void)
{
	DdSpiDrive *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_SPI_DRIVE, sizeof(DdSpiDrivePrivate));
	}

	return self;
}
