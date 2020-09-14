/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdSpiMain类
*@rely                :klib
*@function
*1.0.0 2020年09月开始开发
*设计的主要功能:
*1、
*@version
*
*/

#include "stdlib.h"
#include "string.h"
#include "ct_dd_spi.h"
#include "spi.h"
// #include "dd_spi.h"
#include "dd_top.h"
#include "peripheral.h"
// #include "dd_hdmac1.h"
// #include "dd_tmr32.h"
#include "../../DeviceDriver/Peripheral/src/ddspidrivebranch.h"
#include "../../DeviceDriver/Peripheral/src/ddspicolabo.h"
#include "../../DeviceDriver/Peripheral/src/ddspicalculate.h"
#include "../../DeviceDriver/Peripheral/src/ddspidrive.h"
#include "../../DeviceDriver/Peripheral/src/ddhdmac1.h"
#include "../../DeviceDriver/Peripheral/src/ddtmr32.h"
#include "ctddspitest.h"
#include "ctddspijudge.h"
#include "ctddspimain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdSpiMain, ct_dd_spi_main);
#define CT_DD_SPI_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdSpiMainPrivate,CT_TYPE_DD_SPI_MAIN))

struct _CtDdSpiMainPrivate
{
	CtDdSpiJudge *judge;
};

#ifdef CO_DEBUG_ON_PC
static kuchar  S_GDD_CT_SPI_SEND_BUF8[262144];
static kushort S_GDD_CT_SPI_SEND_BUF16[262144];
static kuint32 S_GDD_CT_SPI_SEND_BUF32[262144];
static kuchar  S_GDD_CT_SPI_RECV_BUF8[262144];
static kushort S_GDD_CT_SPI_RECV_BUF16[262144];
static kuint32 S_GDD_CT_SPI_RECV_BUF32[262144];
#else
static kuchar  S_GDD_CT_SPI_SEND_BUF8[32];
static kushort S_GDD_CT_SPI_SEND_BUF16[32];
static kuint32 S_GDD_CT_SPI_SEND_BUF32[32];
static kuchar  S_GDD_CT_SPI_RECV_BUF8[32];
static kushort S_GDD_CT_SPI_RECV_BUF16[32];
static kuint32 S_GDD_CT_SPI_RECV_BUF32[32];
#endif 

static kulong S_GDD_CT_SPI_SEND_DATA_ADDR;
static kulong S_GDD_CT_SPI_RECV_DATA_ADDR;
static kint32 resultTmp;
static kuchar asyncTmp;
static void *tmp = NULL;
static kuchar S_GDD_CT_SPI_FIFO_DEPTH[CtDdSpiJudge_SPI_CH_MAX] = {128, 64, 16};

/*
 *DECLS
 */
static void 		ctDdSpiSs_cb(kuchar ch);
static void 		ctDdSpi_cb(kuchar ch, kint32 result);
static void 		ctDdSpiPrintCtrl(kuchar ch, TDdSpiCtrl const* const spiCtrl);
static void 		ctDdSpiPrintSendData(CtDdSpiTest * test);
static void 		ctDdSpiPrintRecvData(CtDdSpiTest * test);
static void 		ctDdSpiPrintData(CtDdSpiTest * test);

static void ct_dd_spi_main_constructor(CtDdSpiMain *self) 
{
	CtDdSpiMainPrivate *priv = CT_DD_SPI_MAIN_GET_PRIVATE(self);
	
    priv->judge = ct_dd_spi_judge_new();
}

static void ct_dd_spi_main_destructor(CtDdSpiMain *self) 
{
	CtDdSpiMainPrivate *priv = CT_DD_SPI_MAIN_GET_PRIVATE(self);

    k_object_unref(priv->judge);
    priv->judge = NULL;
}

/*
 *IMPL
 */
static void ctDdSpiSs_cb(kuchar ch)
{
	Ddim_Print(("SPI[%d] Callback of SSOUT/IN\n", ch));
}

static void ctDdSpi_cb(kuchar ch, kint32 result)
{
	Ddim_Print(("SPI[%d] Callback. result=0x%08X\n", ch, result));

	if( result == D_DDIM_OK ){
		//原来是gCT_DD_SPI_Async,因为是回调不能加参,使用全局静态变量来获取该值@ggj20200904
		if( asyncTmp ){
			ctDdSpiPrintData(tmp);
		}
	}

	resultTmp = result;
}

static void ctDdSpiPrintCtrl(kuchar ch, TDdSpiCtrl const* const spiCtrl)
{
	Ddim_Print(("SPI type               = %d\n", spiCtrl->type));
	Ddim_Print(("SPI mode               = %d\n", spiCtrl->mode));
	Ddim_Print(("SPI enableSig         = %d\n", spiCtrl->enableSig));
	Ddim_Print(("SPI bitDirection      = %d\n", spiCtrl->bitDirection));
	Ddim_Print(("SPI bitLength         = %d\n", spiCtrl->bitLength));
	Ddim_Print(("SPI clkDiv            = %d\n", spiCtrl->clkDiv));
	Ddim_Print(("SPI delayEn           = %d\n", spiCtrl->delayEn));
	Ddim_Print(("SPI delayVal          = %d\n", spiCtrl->delayVal));
	Ddim_Print(("SPI rxInhibitEn      = %d\n", spiCtrl->rxInhibitEn));
	Ddim_Print(("SPI fifoWmarkTx      = %d\n", spiCtrl->fifoWmarkTx));
	Ddim_Print(("SPI fifoWmarkRx      = %d\n", spiCtrl->fifoWmarkRx));
	Ddim_Print(("SPI              = %d\n", spiCtrl->));
	Ddim_Print(("SPI dmaRecvTo        = %d\n", spiCtrl->dmaRecvTo));
	Ddim_Print(("SPI ssInfo.contTrans = %d\n", spiCtrl->ssInfo.contTrans));
	Ddim_Print(("SPI ssInfo.ssout[0]   = %d\n", spiCtrl->ssInfo.ssout[0]));
	Ddim_Print(("SPI ssInfo.ssout[1]   = %d\n", spiCtrl->ssInfo.ssout[1]));
	Ddim_Print(("SPI ssInfo.ssout[2]   = %d\n", spiCtrl->ssInfo.ssout[2]));
	Ddim_Print(("SPI ssInfo.ssout[3]   = %d\n", spiCtrl->ssInfo.ssout[3]));
	Ddim_Print(("SPI ssInfo.sspol[0]   = %d\n", spiCtrl->ssInfo.sspol[0]));
	Ddim_Print(("SPI ssInfo.sspol[1]   = %d\n", spiCtrl->ssInfo.sspol[1]));
	Ddim_Print(("SPI ssInfo.sspol[2]   = %d\n", spiCtrl->ssInfo.sspol[2]));
	Ddim_Print(("SPI ssInfo.sspol[3]   = %d\n", spiCtrl->ssInfo.sspol[3]));
	Ddim_Print(("SPI pCallback          = 0x%08X\n", (kuint32)spiCtrl->pCallback));
	Ddim_Print(("SPI pCallbackSs       = 0x%08X\n", (kuint32)spiCtrl->pCallbackSs));
}

static void ctDdSpiPrintSendData(CtDdSpiTest * test)
{
	kint32 index;

	if( !S_GDD_CT_SPI_SEND_DATA_ADDR ){
		Ddim_Print(("---Sned data---\n"));
		if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
			for( index = 0; index < test->gctDdSpiTransNum; index++ ){
				Ddim_Print(("S_GDD_CT_SPI_SEND_BUF32[%d] = 0x%08X\n", index, S_GDD_CT_SPI_SEND_BUF32[index]));
			}
		}
		else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
			for( index = 0; index < test->gctDdSpiTransNum; index++ ){
				Ddim_Print(("S_GDD_CT_SPI_SEND_BUF16[%d] = 0x%04X\n", index, S_GDD_CT_SPI_SEND_BUF16[index]));
			}
		}else {
			for( index = 0; index < test->gctDdSpiTransNum; index++ ){
				Ddim_Print(("S_GDD_CT_SPI_SEND_BUF8[%d] = 0x%02X\n", index, S_GDD_CT_SPI_SEND_BUF8[index]));
			}
		}
	}
}

static void ctDdSpiPrintRecvData(CtDdSpiTest * test)
{
	kint32 index;

	if( !S_GDD_CT_SPI_RECV_DATA_ADDR ){
		Ddim_Print(("---Receive data---\n"));
		if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
			for( index = 0; index < test->gctDdSpiTransNum; index++ ){
				Ddim_Print(("S_GDD_CT_SPI_RECV_BUF32[%d] = 0x%08X\n", index, S_GDD_CT_SPI_RECV_BUF32[index]));
			}
		}
		else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
			for( index = 0; index < test->gctDdSpiTransNum; index++ ){
				Ddim_Print(("S_GDD_CT_SPI_RECV_BUF16[%d] = 0x%04X\n", index, S_GDD_CT_SPI_RECV_BUF16[index]));
			}
		}else {
			for( index = 0; index < test->gctDdSpiTransNum; index++ ){
				Ddim_Print(("S_GDD_CT_SPI_RECV_BUF8[%d] = 0x%02X\n", index, S_GDD_CT_SPI_RECV_BUF8[index]));
			}
		}
	}
}

static void ctDdSpiPrintData(CtDdSpiTest * test)
{
	if( ct_dd_spi_judge_get_trans_type() == CtDdSpiJudge_SPI_TRNAS_TYPE_SEND ){
		ctDdSpiPrintSendData(test);
	}
	else if( ct_dd_spi_judge_get_trans_type() == CtDdSpiJudge_SPI_TRNAS_TYPE_RECV ){
		ctDdSpiPrintRecvData(test);
	}else {	
		// CtDdSpiJudge_SPI_TRNAS_TYPE_FULL
		ctDdSpiPrintSendData(test);
		ctDdSpiPrintRecvData(test);
	}
}

/*
 *PUBLIC
 */
kuchar  *ct_dd_spi_return_sendbuf8(void)
{
	return S_GDD_CT_SPI_SEND_BUF8;
}

void ct_dd_spi_set_sendbuf8(kuchar ch, kint index)
{
	S_GDD_CT_SPI_SEND_BUF8[index] = ch;
}

kushort *ct_dd_spi_return_sendbuf16(void)
{
	return S_GDD_CT_SPI_SEND_BUF16;
}

void ct_dd_spi_set_sendbuf16(kushort ch, kint index)
{
	S_GDD_CT_SPI_SEND_BUF16[index] = ch;
}

kuint32 *ct_dd_spi_return_sendbuf32(void)
{
	return S_GDD_CT_SPI_SEND_BUF32;
}

kuchar *ct_dd_spi_return_recvbuf8(void)
{
	return S_GDD_CT_SPI_RECV_BUF8;
}

kushort *ct_dd_spi_return_recvbuf16(void)
{
	return S_GDD_CT_SPI_RECV_BUF16;
}

kuint32 *ct_dd_spi_return_recvbuf32(void)
{
	return S_GDD_CT_SPI_RECV_BUF32;
}

/*
 * @brief  Command main function for SPI test.
 * @param  kint32 argc	:The number of parameters
 *	CGAR** argv	:The value of parameters
 * @return void
 */
void ct_dd_spi_main(CtDdSpiMain *self,kint argc, kchar** argv)
{
    CtDdSpiMainPrivate *priv = CT_DD_SPI_MAIN_GET_PRIVATE(self);
    priv->judge->ret = D_DDIM_OK;
    priv->judge->clkDiv = 0;
    priv->judge->tmout = D_DDIM_USER_SEM_WAIT_POL;

	CtDdSpiTest * test = ct_dd_spi_test_new();
	// Open
	if( strcmp(argv[1], "open") == 0 ){				
		priv->judge->ch = atoi( argv[2] );
		priv->judge->tmout = atoi(argv[3]);

		priv->judge->ret = dd_spi_drive_open(dd_spi_drive_get(), priv->judge->ch, priv->judge->tmout);

		Ddim_Print(("dd_spi_drive_open() End. ret=0x%08X\n", priv->judge->ret));
	}
	// Close
	else if( strcmp(argv[1], "close") == 0 ){		
		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = dd_spi_drive_close(dd_spi_drive_get(), priv->judge->ch);
		Ddim_Print(("dd_spi_drive_close() End. ret=0x%08X\n", priv->judge->ret));
	}
	// Calc
	else if( strcmp(argv[1], "cal") == 0 ){			
		priv->judge->baudrate = atoi( argv[2] );

		priv->judge->ret = dd_spi_calculate_clock_divisor(dd_spi_calculate_get(), priv->judge->baudrate,
					&(priv->judge->clkDiv));

		Ddim_Print(("dd_spi_calculate_clock_divisor() End. ret=0x%08X, clkDiv=%d\n", priv->judge->ret,
					priv->judge->clkDiv));
	}
	// Set Control
	else if( strcmp(argv[1], "ctrl") == 0 ){
		/*
		*ddspi ctrl [priv->judge->ch] [type] [mode] [sig] [msb] [bit] [bps] [dly] [inhrx] [txwmk] [rxwmk] [dma/cpu]
		*[timeout] [ssout] [sspol] [contTrans] [cb] [cbss]
		*/	
		priv->judge->ch = atoi( argv[2] );

		// Type
		if(strcmp(argv[3], "ms") == 0){
			priv->judge->spiCtrl.type = DdSpiDriveBranch_E_DD_SPI_TYPE_MASTER;
		}
		else if(strcmp(argv[3], "sl") == 0){
			priv->judge->spiCtrl.type = DdSpiDriveBranch_E_DD_SPI_TYPE_SLAVE;
		}else{
			Ddim_Print(("please check type parameter!!\n") );
			return;
		}

		// Mode
		priv->judge->spiCtrl.mode = atoi(argv[4]);
		if(priv->judge->spiCtrl.mode > DdSpiDriveBranch_E_DD_SPI_MODE_3_CPOL1_CPHA1){
			Ddim_Print(("please check mode parameter!!\n" ));
			return;
		}

		// Enable signal
		priv->judge->spiCtrl.enableSig = atoi(argv[5]);
		if(priv->judge->spiCtrl.enableSig > DdSpiDriveBranch_E_DD_SPI_ENABLE_SIG_EXT_2){
			Ddim_Print( ("please check enableSig parameter!!\n" ) );
			return;
		}

		// LSB first or MSB first
		if( strcmp(argv[6], "lsb") == 0 ){
			priv->judge->spiCtrl.bitDirection = DdSpiDriveBranch_E_DD_SPI_BIT_DIR_LSB_FIRST;
		}
		else if( strcmp(argv[6], "msb") == 0 ){
			priv->judge->spiCtrl.bitDirection = DdSpiDriveBranch_E_DD_SPI_BIT_DIR_MSB_FIRST;
		}else{
			Ddim_Print( ("please check bitDirection parameter!!\n" ) );
			return;
		}

		// Bit length
		priv->judge->spiCtrl.bitLength = atoi( argv[7] ) - 1;
		if( ( priv->judge->spiCtrl.bitLength < DdSpiDriveBranch_E_DD_SPI_BIT_LEN_4) ||
			( priv->judge->spiCtrl.bitLength > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_32)){
			Ddim_Print( ("please check bitLength parameter!!\n" ) );
			return;
		}
		test->gctDdSpiBitLen = priv->judge->spiCtrl.bitLength;

		// Baudrate (bps)
		priv->judge->baudrate = atol(argv[8]);
		priv->judge->ret = dd_spi_calculate_clock_divisor(dd_spi_calculate_get(), priv->judge->baudrate, 
					&(priv->judge->spiCtrl.clkDiv) );
		if( priv->judge->ret !=D_DDIM_OK ){
			Ddim_Print(("SPI Calc ERR. ret=0x%08X\n", priv->judge->ret));
			return;
		}

		// Inter-Transfer Delay
		priv->judge->val = atoi( argv[9] );
		if( priv->judge->val == 0 ){
			priv->judge->spiCtrl.delayVal = 0;
			priv->judge->spiCtrl.delayEn = 0;
		}
		else if( priv->judge->val < 256 ){
			priv->judge->spiCtrl.delayVal = priv->judge->val;
			priv->judge->spiCtrl.delayEn = 1;
		}else {
			Ddim_Print( ("please check delay parameter!!\n" ) );
			return;
		}

		// Inhibit the RX_FIFO
		priv->judge->val = atoi( argv[10] );
		if( priv->judge->val == 0 ){
			priv->judge->spiCtrl.rxInhibitEn = 0;
		}
		else if( priv->judge->val == 1 ){
			priv->judge->spiCtrl.rxInhibitEn = 1;
		}else {
			Ddim_Print( ("please check rxInhibitEn parameter!!\n" ) );
			return;
		}

		// TX FIFO Watermark
		priv->judge->spiCtrl.fifoWmarkTx = atoi( argv[11] );
		if( priv->judge->spiCtrl.fifoWmarkTx > S_GDD_CT_SPI_FIFO_DEPTH[priv->judge->ch] ){
			Ddim_Print( ("please check fifoWmarkTx parameter!!\n" ) );
			return;
		}

		// RX FIFO Watermark
		priv->judge->spiCtrl.fifoWmarkRx = atoi( argv[12] );
		if( priv->judge->spiCtrl.fifoWmarkRx > S_GDD_CT_SPI_FIFO_DEPTH[priv->judge->ch] ){
			Ddim_Print( ("please check fifoWmarkRx parameter!!\n" ) );
			return;
		}

		// DMA enable
		if( strcmp(argv[13], "dma") == 0 ){
			priv->judge->spiCtrl. = 1;

			priv->judge->val = atoi( argv[14] );
			if( priv->judge->val <= 0xFFFFFF ){
				priv->judge->spiCtrl.dmaRecvTo = priv->judge->val;
			}else {
				Ddim_Print( ("please check dmaRecvTo parameter!!\n" ) );
				return;
			}
		}
		else if( strcmp(argv[13], "cpu") == 0 ){
			priv->judge->spiCtrl. = 0;
			priv->judge->spiCtrl.dmaRecvTo = 0;
		}else{
			Ddim_Print( ("please check  parameter!!\n" ) );
			return;
		}

		// Slave Select Output
		priv->judge->val = atoi( argv[15] );
		if( priv->judge->val >= DdSpiDriveBranch_D_DD_SPI_SS_MAX){
			Ddim_Print( ("please check ssout parameter!!\n" ) );
			return;
		}else {
			for( priv->judge->index = 0; priv->judge->index < DdSpiDriveBranch_D_DD_SPI_SS_MAX; priv->judge->index++){
				if( priv->judge->val == priv->judge->index ){
					priv->judge->spiCtrl.ssInfo.ssout[priv->judge->index] = 1;
				}else {
					priv->judge->spiCtrl.ssInfo.ssout[priv->judge->index] = 0;
				}
			}
		}

		// Slave Select Polarity
		priv->judge->val = atoi( argv[16] );
		if( priv->judge->val > 1 ){
			Ddim_Print( ("please check sspol parameter!!\n" ) );
			return;
		}else {
			for( priv->judge->index = 0; priv->judge->index < DdSpiDriveBranch_D_DD_SPI_SS_MAX; priv->judge->index++){
				priv->judge->spiCtrl.ssInfo.sspol[priv->judge->index] = priv->judge->val;
			}
		}

		// ssOUT Continuous Transfer
		priv->judge->spiCtrl.ssInfo.contTrans = atoi( argv[17] );
		if( priv->judge->spiCtrl.ssInfo.contTrans > DdSpiDriveBranch_E_DD_SPI_CONT_TRANS_ACT_FIFO_EMPTY){
			Ddim_Print( ("please check contTrans parameter!!\n" ) );
			return;
		}

		// Callback function
		priv->judge->val = atoi( argv[18] );
		if( priv->judge->val == 0 ){
			priv->judge->spiCtrl.pCallback = NULL;
		}else{
			asyncTmp = ct_dd_spi_test_get_async(test);
			tmp = test;
			priv->judge->spiCtrl.pCallback = ctDdSpi_cb;
			ct_dd_spi_test_set_result(test,resultTmp);
			test->gctDdSpiAsync = 1;
		}

		// Callback function for ssIN/OUT
		priv->judge->val = atoi( argv[19] );
		if( priv->judge->val == 0 ){
			priv->judge->spiCtrl.pCallbackSs = NULL;
		}else{
			priv->judge->spiCtrl.pCallbackSs = ctDdSpiSs_cb;
			test->gctDdSpiAsync = 1;
		}

		// Set Control
		priv->judge->ret = dd_spi_drive_ctrl(dd_spi_drive_get(), priv->judge->ch, &(priv->judge->spiCtrl));

		Ddim_Print(("dd_spi_drive_ctrl() End. ret=0x%08X\n", priv->judge->ret));
		ctDdSpiPrintCtrl(priv->judge->ch, &(priv->judge->spiCtrl));
	}
	else if( strcmp(argv[1], "get_ctrl") == 0 ){
		TDdSpiCtrl spiCtrl;

		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = dd_spi_drive_get_ctrl(dd_spi_drive_get(), priv->judge->ch, &spiCtrl);

		Ddim_Print(("dd_spi_drive_get_ctrl() End. ret=0x%08X\n", priv->judge->ret));
		ctDdSpiPrintCtrl(priv->judge->ch, &spiCtrl );
	}
	// Set send data
	else if( strcmp(argv[1], "set_send") == 0 ){			
		// ddspi set_send [priv->judge->ch] [num] data [data value]
		// ddspi set_send [priv->judge->ch] [num] addr [addr value] [data value]
		kuchar	data;

		priv->judge->ch = atoi( argv[2] );

		// Data size
		test->gctDdSpiTransNum = atoi(argv[3]);
		if( strcmp(argv[4], "data") == 0 ){
			S_GDD_CT_SPI_SEND_DATA_ADDR = 0;

			data = strtoul( argv[5], &(priv->judge->endstr), 16 );

			if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
				/* pgr0539 */
				memset( S_GDD_CT_SPI_SEND_BUF32, data, sizeof(S_GDD_CT_SPI_SEND_BUF32));	

				// Set send data
				priv->judge->ret = dd_spi_drive_set_send_data(dd_spi_drive_get(), priv->judge->ch,
						S_GDD_CT_SPI_SEND_BUF32, test->gctDdSpiTransNum);
			}
			
			else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
				/* pgr0539 */
				memset( S_GDD_CT_SPI_SEND_BUF16, data, sizeof(S_GDD_CT_SPI_SEND_BUF16) );	

				// Set send data
				priv->judge->ret = dd_spi_drive_set_send_data(dd_spi_drive_get(), priv->judge->ch,
						S_GDD_CT_SPI_SEND_BUF16, test->gctDdSpiTransNum);
			}else {
				/* pgr0539 */
				memset( S_GDD_CT_SPI_SEND_BUF8, data, sizeof(S_GDD_CT_SPI_SEND_BUF8) );		

				// Set send data
				priv->judge->ret = dd_spi_drive_set_send_data(dd_spi_drive_get(), priv->judge->ch,
						S_GDD_CT_SPI_SEND_BUF8, test->gctDdSpiTransNum );
			}

			Ddim_Print(("dd_spi_drive_set_send_data() End. ret=0x%08X\n", priv->judge->ret));
		}
		else if( strcmp(argv[4], "addr") == 0 ){
			S_GDD_CT_SPI_SEND_DATA_ADDR = strtoul( argv[5], &(priv->judge->endstr), 16 );

			data = strtoul( argv[6], &(priv->judge->endstr), 16 );

			if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_SEND_DATA_ADDR, data, (test->gctDdSpiTransNum * 4) );	
			}
			else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_SEND_DATA_ADDR, data, (test->gctDdSpiTransNum * 2) );	
			}else {
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_SEND_DATA_ADDR, data, test->gctDdSpiTransNum );		
			}

			// Set send data
			priv->judge->ret = dd_spi_drive_set_send_data(dd_spi_drive_get(), priv->judge->ch,
					(kpointer)S_GDD_CT_SPI_SEND_DATA_ADDR, test->gctDdSpiTransNum);

			Ddim_Print(("dd_spi_drive_set_send_data() End. ret=0x%08X\n", priv->judge->ret));
		}else {
			Ddim_Print( ("please check data/addr parameter!!\n" ) );
		}
	}
	// Set revceive data
	else if( strcmp(argv[1], "set_recv") == 0 ){			
		// ddspi set_recv [priv->judge->ch] [num] data
		// ddspi set_recv [priv->judge->ch] [num] addr [addr value]
		priv->judge->ch = atoi( argv[2] );

		// Data size
		test->gctDdSpiTransNum = atoi(argv[3]);

		if( strcmp(argv[4], "data") == 0 ){
			S_GDD_CT_SPI_RECV_DATA_ADDR = 0;

			if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
				memset( S_GDD_CT_SPI_RECV_BUF32, 0, sizeof(S_GDD_CT_SPI_RECV_BUF32) );

				// Set receive data
				priv->judge->ret = dd_spi_drive_set_recv_data(dd_spi_drive_get(), priv->judge->ch, 
								S_GDD_CT_SPI_RECV_BUF16, test->gctDdSpiTransNum);
			}
			else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
				memset( S_GDD_CT_SPI_RECV_BUF16, 0, sizeof(S_GDD_CT_SPI_RECV_BUF16) );

				// Set receive data
				priv->judge->ret = dd_spi_drive_set_recv_data(dd_spi_drive_get(), priv->judge->ch,
								S_GDD_CT_SPI_RECV_BUF16, test->gctDdSpiTransNum);
			}else {
				memset( S_GDD_CT_SPI_RECV_BUF8, 0, sizeof(S_GDD_CT_SPI_RECV_BUF8) );

				// Set receive data
				priv->judge->ret = dd_spi_drive_set_recv_data(dd_spi_drive_get(), priv->judge->ch,
								S_GDD_CT_SPI_RECV_BUF8, test->gctDdSpiTransNum);
			}
		}
		else if( strcmp(argv[4], "addr") == 0 ){
			S_GDD_CT_SPI_RECV_DATA_ADDR = strtoul( argv[5], &(priv->judge->endstr), 16 );

			if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_RECV_DATA_ADDR, 0, (test->gctDdSpiTransNum * 4) );	
			}
			else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_RECV_DATA_ADDR, 0, (test->gctDdSpiTransNum * 2) );	
			}else {
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_RECV_DATA_ADDR, 0, test->gctDdSpiTransNum );			
			}

			// Set send data
			priv->judge->ret = dd_spi_drive_set_recv_data(dd_spi_drive_get(), priv->judge->ch,
					(kpointer)S_GDD_CT_SPI_RECV_DATA_ADDR,test->gctDdSpiTransNum );
		}else {
			Ddim_Print( ("please check data/addr parameter!!\n" ) );
		}

		Ddim_Print(("dd_spi_drive_set_recv_data() End. ret=0x%08X\n", priv->judge->ret));
	}
	// Start send
	else if ( strcmp( argv[1], "start_send" ) == 0 ){		
		priv->judge->ch = atoi( argv[2] );
		// gCT_DD_SPI_Trans_Type = CtDdSpiJudge_SPI_TRNAS_TYPE_SEND;
		ct_dd_spi_judge_set_trans_type(CtDdSpiJudge_SPI_TRNAS_TYPE_SEND);

		priv->judge->ret = dd_spi_drive_start_send(dd_spi_drive_get(), priv->judge->ch);

		Ddim_Print(("dd_spi_drive_start_send() End. ret=0x%08X\n", priv->judge->ret));

		if( priv->judge->ret == D_DDIM_OK ){
			if( !test->gctDdSpiAsync ){
				ctDdSpiPrintData(test);
			}
		}
	}
	// Start receive
	else if ( strcmp( argv[1], "start_recv" ) == 0 ){		
		priv->judge->ch = atoi( argv[2] );
		// gCT_DD_SPI_Trans_Type = CtDdSpiJudge_SPI_TRNAS_TYPE_RECV;
		ct_dd_spi_judge_set_trans_type(CtDdSpiJudge_SPI_TRNAS_TYPE_RECV);

		priv->judge->ret = dd_spi_drive_start_recv(dd_spi_drive_get(), priv->judge->ch);

		Ddim_Print(("dd_spi_drive_start_recv() End. ret=0x%08X\n", priv->judge->ret));

		if( priv->judge->ret == D_DDIM_OK ){
			if( !test->gctDdSpiAsync ){
				ctDdSpiPrintData(test);
			}
		}
	}
	else if ( strcmp( argv[1], "start_full" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );
		// gCT_DD_SPI_Trans_Type = CtDdSpiJudge_SPI_TRNAS_TYPE_FULL;
		ct_dd_spi_judge_set_trans_type(CtDdSpiJudge_SPI_TRNAS_TYPE_FULL);

		priv->judge->ret = dd_spi_drive_start_full_duplex(dd_spi_drive_get(), priv->judge->ch );

		Ddim_Print(("dd_spi_drive_start_full_duplex() End. ret=0x%08X\n", priv->judge->ret));

		if( priv->judge->ret == D_DDIM_OK ){
			if( !test->gctDdSpiAsync ){
				ctDdSpiPrintData(test);
			}
		}
	}
	else if ( strcmp( argv[1], "start_send_dma" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );
		priv->judge->dmaCh[0] = atoi( argv[3] );

		if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
			if( S_GDD_CT_SPI_SEND_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_DATA_ADDR, 
														test->gctDdSpiTransNum * 4 );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_BUF32,
														sizeof(S_GDD_CT_SPI_SEND_BUF32) );
			}
		}
		else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
			if( S_GDD_CT_SPI_SEND_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_DATA_ADDR,
													test->gctDdSpiTransNum * 2 );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_BUF16, 
														sizeof(S_GDD_CT_SPI_SEND_BUF16) );
			}
		}else {
			if( S_GDD_CT_SPI_SEND_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_DATA_ADDR, test->gctDdSpiTransNum);
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_BUF8, sizeof(S_GDD_CT_SPI_SEND_BUF8));
			}
		}

		priv->judge->ret = dd_spi_colabo_start_send_dma(dd_spi_colabo_get(), priv->judge->ch, priv->judge->dmaCh[0]);

		Ddim_Print(("dd_spi_colabo_start_send_dma() End. ret=0x%08X\n", priv->judge->ret));

		if( priv->judge->ret == D_DDIM_OK ){
			if( !test->gctDdSpiAsync ){
#ifndef CO_DEBUG_ON_PC
				ctDdSpiPrintData(test);
#endif
			}
		}
	}
	else if ( strcmp( argv[1], "start_recv_dma" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );
		priv->judge->dmaCh[0] = atoi( argv[3] );

		if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
			if( S_GDD_CT_SPI_RECV_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)S_GDD_CT_SPI_RECV_DATA_ADDR, 
														test->gctDdSpiTransNum * 4);
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)S_GDD_CT_SPI_RECV_BUF32, 
														sizeof(S_GDD_CT_SPI_RECV_BUF32));
			}
		}
		else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
			if( S_GDD_CT_SPI_RECV_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)S_GDD_CT_SPI_RECV_DATA_ADDR, 
														test->gctDdSpiTransNum * 2);
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)S_GDD_CT_SPI_RECV_BUF16, 
													sizeof(S_GDD_CT_SPI_RECV_BUF16));
			}
		}else {
			if( S_GDD_CT_SPI_RECV_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_RECV_DATA_ADDR,
													test->gctDdSpiTransNum );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_RECV_BUF8,
														sizeof(S_GDD_CT_SPI_RECV_BUF8) );
			}
		}

		priv->judge->ret = dd_spi_colabo_start_recv_dma(dd_spi_colabo_get(), priv->judge->ch, priv->judge->dmaCh[0] );

		Ddim_Print(("dd_spi_colabo_start_recv_dma(dd_spi_colabo_get(),) End. ret=0x%08X\n", priv->judge->ret));

		if( priv->judge->ret == D_DDIM_OK ){
			if( !test->gctDdSpiAsync ){
#ifndef CO_DEBUG_ON_PC
				ctDdSpiPrintData(test);
#endif
			}
		}
	}
	else if ( strcmp( argv[1], "start_full_dma" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );
		priv->judge->dmaCh[0] = atoi( argv[3] );
		priv->judge->dmaCh[1] = atoi( argv[4] );

		if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_16){
			if( S_GDD_CT_SPI_SEND_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_DATA_ADDR, 
														test->gctDdSpiTransNum * 4 );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_BUF32, 
														sizeof(S_GDD_CT_SPI_SEND_BUF32) );
			}

			if( S_GDD_CT_SPI_RECV_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_RECV_DATA_ADDR, 
														test->gctDdSpiTransNum * 4 );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_RECV_BUF32,
														sizeof(S_GDD_CT_SPI_RECV_BUF32) );
			}
		}
		else if( test->gctDdSpiBitLen > DdSpiDriveBranch_E_DD_SPI_BIT_LEN_8){
			if( S_GDD_CT_SPI_SEND_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_DATA_ADDR,
														test->gctDdSpiTransNum * 2 );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_BUF16, 
														sizeof(S_GDD_CT_SPI_SEND_BUF16) );
			}

			if( S_GDD_CT_SPI_RECV_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_RECV_DATA_ADDR, 
													test->gctDdSpiTransNum * 2 );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_RECV_BUF16,
														sizeof(S_GDD_CT_SPI_RECV_BUF16) );
			}
		}else {
			if( S_GDD_CT_SPI_SEND_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_DATA_ADDR, 
														test->gctDdSpiTransNum );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_BUF8,
														sizeof(S_GDD_CT_SPI_SEND_BUF8) );
			}

			if( S_GDD_CT_SPI_RECV_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_RECV_DATA_ADDR,
														test->gctDdSpiTransNum );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_RECV_BUF8,
														sizeof(S_GDD_CT_SPI_RECV_BUF8) );
			}
		}

		priv->judge->ret = dd_spi_colabo_start_full_duplex_dma(dd_spi_colabo_get(), priv->judge->ch, priv->judge->dmaCh[0],
															priv->judge->dmaCh[1] );

		Ddim_Print(("dd_spi_colabo_start_full_duplex_dma(dd_spi_colabo_get(),) End. ret=0x%08X\n", priv->judge->ret));

		if( priv->judge->ret == D_DDIM_OK ){
			if( !test->gctDdSpiAsync ){
#ifndef CO_DEBUG_ON_PC
				ctDdSpiPrintData(test);
#endif
			}
		}
	}
	else if ( strcmp( argv[1], "stop" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = dd_spi_drive_stop(dd_spi_drive_get(), priv->judge->ch);

		Ddim_Print(("dd_spi_drive_stop() End. ret=0x%08X\n", priv->judge->ret));
	}
	else if ( strcmp( argv[1], "set_ss" ) == 0 ){
		/* ddspi set_ss [priv->judge->ch] [contTrans] [ssout0] [ssout1] 
		*[ssout2] [ssout3] [sspol0] [sspol1] [sspol2] [sspol3]
		*/
		if( argc < 12 ){
			Ddim_Print( ("please check 12 parameter!!\n" ) );
			return;
		}

		priv->judge->ch = atoi( argv[2] );
		priv->judge->ssInfo.contTrans = atoi( argv[3] );

		for( priv->judge->index = 0; priv->judge->index < DdSpiDriveBranch_D_DD_SPI_SS_MAX; priv->judge->index++){
			priv->judge->ssInfo.ssout[priv->judge->index] = atoi( argv[4 + priv->judge->index] );
		}
		for( priv->judge->index = 0; priv->judge->index < DdSpiDriveBranch_D_DD_SPI_SS_MAX; priv->judge->index++){
			priv->judge->ssInfo.sspol[priv->judge->index] = atoi( argv[4 + 
					DdSpiDriveBranch_D_DD_SPI_SS_MAX + priv->judge->index]);
		}

		priv->judge->ret = dd_spi_drive_set_slave_select(dd_spi_drive_get(), priv->judge->ch, &(priv->judge->ssInfo) );

		Ddim_Print(("dd_spi_drive_set_slave_select End. ret=0x%08X\n", priv->judge->ret));
	}
	else if ( strcmp( argv[1], "get_ss" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = dd_spi_drive_get_slave_select(dd_spi_drive_get(), priv->judge->ch, &(priv->judge->ssInfo) );

		Ddim_Print(("dd_spi_drive_get_slave_select End. ret=0x%08X\n", priv->judge->ret));

		Ddim_Print(("---Get SS_INFO---\n"));
		Ddim_Print(("contTrans = %d\n", priv->judge->ssInfo.contTrans));
		for( priv->judge->index = 0; priv->judge->index < DdSpiDriveBranch_D_DD_SPI_SS_MAX; priv->judge->index++){
			Ddim_Print(("ssout[%d] = %d\n", priv->judge->index, priv->judge->ssInfo.ssout[priv->judge->index]));
		}
		for( priv->judge->index = 0; priv->judge->index < DdSpiDriveBranch_D_DD_SPI_SS_MAX; priv->judge->index++){
			Ddim_Print(("sspol[%d] = %d\n", priv->judge->index, priv->judge->ssInfo.sspol[priv->judge->index]));
		}
	}
	else if ( strcmp( argv[1], "set_div" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );
		priv->judge->clkDiv = atoi( argv[3] );

		priv->judge->ret = dd_spi_calculate_set_clock_divisor(dd_spi_calculate_get(), priv->judge->ch, priv->judge->clkDiv );

		Ddim_Print(("dd_spi_calculate_set_clock_divisor End. ret=0x%08X\n", priv->judge->ret));
	}
	else if ( strcmp( argv[1], "get_div" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = dd_spi_calculate_get_clock_divisor(dd_spi_calculate_get(), priv->judge->ch, &(priv->judge->clkDiv) );

		Ddim_Print(("dd_spi_calculate_get_clock_divisor End. ret=0x%08X, clkDiv=%d\n", priv->judge->ret, priv->judge->clkDiv));
	}
    
    ct_dd_spi_judge_main( priv->judge, test,argc, argv );
	k_object_unref(test);
	return ;
}

CtDdSpiMain* ct_dd_spi_main_new(void) 
{
    CtDdSpiMain *self = k_object_new_with_private(CT_TYPE_DD_SPI_MAIN, sizeof(CtDdSpiMainPrivate));

    return self;
}
