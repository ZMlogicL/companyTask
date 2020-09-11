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
#include "dd_spi.h"
#include "dd_top.h"
#include "peripheral.h"
#include "dd_hdmac1.h"
#include "dd_tmr32.h"
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
static void 		ctDdSpiPrintCtrl(kuchar ch, T_DD_SPI_CTRL const* const spiCtrl);
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

static void ctDdSpiPrintCtrl(kuchar ch, T_DD_SPI_CTRL const* const spiCtrl)
{
	Ddim_Print(("SPI type               = %d\n", spiCtrl->type));
	Ddim_Print(("SPI mode               = %d\n", spiCtrl->mode));
	Ddim_Print(("SPI enableSig         = %d\n", spiCtrl->enable_sig));
	Ddim_Print(("SPI bit_direction      = %d\n", spiCtrl->bit_direction));
	Ddim_Print(("SPI bit_length         = %d\n", spiCtrl->bit_length));
	Ddim_Print(("SPI clkDiv            = %d\n", spiCtrl->clk_div));
	Ddim_Print(("SPI delay_en           = %d\n", spiCtrl->delay_en));
	Ddim_Print(("SPI delay_val          = %d\n", spiCtrl->delay_val));
	Ddim_Print(("SPI rx_inhibit_en      = %d\n", spiCtrl->rx_inhibit_en));
	Ddim_Print(("SPI fifo_wmark_tx      = %d\n", spiCtrl->fifo_wmark_tx));
	Ddim_Print(("SPI fifo_wmark_rx      = %d\n", spiCtrl->fifo_wmark_rx));
	Ddim_Print(("SPI dma_en             = %d\n", spiCtrl->dma_en));
	Ddim_Print(("SPI dma_recv_to        = %d\n", spiCtrl->dma_recv_to));
	Ddim_Print(("SPI ssInfo.cont_trans = %d\n", spiCtrl->ss_info.cont_trans));
	Ddim_Print(("SPI ssInfo.ssout[0]   = %d\n", spiCtrl->ss_info.ssout[0]));
	Ddim_Print(("SPI ssInfo.ssout[1]   = %d\n", spiCtrl->ss_info.ssout[1]));
	Ddim_Print(("SPI ssInfo.ssout[2]   = %d\n", spiCtrl->ss_info.ssout[2]));
	Ddim_Print(("SPI ssInfo.ssout[3]   = %d\n", spiCtrl->ss_info.ssout[3]));
	Ddim_Print(("SPI ssInfo.sspol[0]   = %d\n", spiCtrl->ss_info.sspol[0]));
	Ddim_Print(("SPI ssInfo.sspol[1]   = %d\n", spiCtrl->ss_info.sspol[1]));
	Ddim_Print(("SPI ssInfo.sspol[2]   = %d\n", spiCtrl->ss_info.sspol[2]));
	Ddim_Print(("SPI ssInfo.sspol[3]   = %d\n", spiCtrl->ss_info.sspol[3]));
	Ddim_Print(("SPI pcallback          = 0x%08X\n", (kuint32)spiCtrl->pcallback));
	Ddim_Print(("SPI pcallback_ss       = 0x%08X\n", (kuint32)spiCtrl->pcallback_ss));
}

static void ctDdSpiPrintSendData(CtDdSpiTest * test)
{
	kint32 index;

	if( !S_GDD_CT_SPI_SEND_DATA_ADDR ){
		Ddim_Print(("---Sned data---\n"));
		if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
			for( index = 0; index < test->gctDdSpiTransNum; index++ ){
				Ddim_Print(("S_GDD_CT_SPI_SEND_BUF32[%d] = 0x%08X\n", index, S_GDD_CT_SPI_SEND_BUF32[index]));
			}
		}
		else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
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
		if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
			for( index = 0; index < test->gctDdSpiTransNum; index++ ){
				Ddim_Print(("S_GDD_CT_SPI_RECV_BUF32[%d] = 0x%08X\n", index, S_GDD_CT_SPI_RECV_BUF32[index]));
			}
		}
		else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
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

		priv->judge->ret = Dd_SPI_Open(priv->judge->ch, priv->judge->tmout);

		Ddim_Print(("Dd_SPI_Open() End. ret=0x%08X\n", priv->judge->ret));
	}
	// Close
	else if( strcmp(argv[1], "close") == 0 ){		
		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = Dd_SPI_Close( priv->judge->ch );
		Ddim_Print(("Dd_SPI_Close() End. ret=0x%08X\n", priv->judge->ret));
	}
	// Calc
	else if( strcmp(argv[1], "cal") == 0 ){			
		priv->judge->baudrate = atoi( argv[2] );

		priv->judge->ret = Dd_SPI_Calculate( priv->judge->baudrate, &(priv->judge->clkDiv) );

		Ddim_Print(("Dd_SPI_Calculate() End. ret=0x%08X, clkDiv=%d\n", priv->judge->ret, priv->judge->clkDiv));
	}
	// Set Control
	else if( strcmp(argv[1], "ctrl") == 0 ){
		/*
		*ddspi ctrl [priv->judge->ch] [type] [mode] [sig] [msb] [bit] [bps] [dly] [inhrx] [txwmk] [rxwmk] [dma/cpu]
		*[timeout] [ssout] [sspol] [cont_trans] [cb] [cbss]
		*/	
		priv->judge->ch = atoi( argv[2] );

		// Type
		if(strcmp(argv[3], "ms") == 0){
			priv->judge->spiCtrl.type = E_DD_SPI_TYPE_MASTER;
		}
		else if(strcmp(argv[3], "sl") == 0){
			priv->judge->spiCtrl.type = E_DD_SPI_TYPE_SLAVE;
		}else{
			Ddim_Print(("please check type parameter!!\n") );
			return;
		}

		// Mode
		priv->judge->spiCtrl.mode = atoi(argv[4]);
		if(priv->judge->spiCtrl.mode > E_DD_SPI_MODE_3_CPOL1_CPHA1){
			Ddim_Print(("please check mode parameter!!\n" ));
			return;
		}

		// Enable signal
		priv->judge->spiCtrl.enable_sig = atoi(argv[5]);
		if(priv->judge->spiCtrl.enable_sig > E_DD_SPI_ENABLE_SIG_EXT_2){
			Ddim_Print( ("please check enableSig parameter!!\n" ) );
			return;
		}

		// LSB first or MSB first
		if( strcmp(argv[6], "lsb") == 0 ){
			priv->judge->spiCtrl.bit_direction = E_DD_SPI_BIT_DIR_LSB_FIRST;
		}
		else if( strcmp(argv[6], "msb") == 0 ){
			priv->judge->spiCtrl.bit_direction = E_DD_SPI_BIT_DIR_MSB_FIRST;
		}else{
			Ddim_Print( ("please check bit_direction parameter!!\n" ) );
			return;
		}

		// Bit length
		priv->judge->spiCtrl.bit_length = atoi( argv[7] ) - 1;
		if( ( priv->judge->spiCtrl.bit_length < E_DD_SPI_BIT_LEN_4 ) ||
			( priv->judge->spiCtrl.bit_length > E_DD_SPI_BIT_LEN_32 ) ){
			Ddim_Print( ("please check bit_length parameter!!\n" ) );
			return;
		}
		test->gctDdSpiBitLen = priv->judge->spiCtrl.bit_length;

		// Baudrate (bps)
		priv->judge->baudrate = atol(argv[8]);
		priv->judge->ret = Dd_SPI_Calculate( priv->judge->baudrate, &(priv->judge->spiCtrl.clk_div) );
		if( priv->judge->ret !=D_DDIM_OK ){
			Ddim_Print(("SPI Calc ERR. ret=0x%08X\n", priv->judge->ret));
			return;
		}

		// Inter-Transfer Delay
		priv->judge->val = atoi( argv[9] );
		if( priv->judge->val == 0 ){
			priv->judge->spiCtrl.delay_val = 0;
			priv->judge->spiCtrl.delay_en = 0;
		}
		else if( priv->judge->val < 256 ){
			priv->judge->spiCtrl.delay_val = priv->judge->val;
			priv->judge->spiCtrl.delay_en = 1;
		}else {
			Ddim_Print( ("please check delay parameter!!\n" ) );
			return;
		}

		// Inhibit the RX_FIFO
		priv->judge->val = atoi( argv[10] );
		if( priv->judge->val == 0 ){
			priv->judge->spiCtrl.rx_inhibit_en = 0;
		}
		else if( priv->judge->val == 1 ){
			priv->judge->spiCtrl.rx_inhibit_en = 1;
		}else {
			Ddim_Print( ("please check rx_inhibit_en parameter!!\n" ) );
			return;
		}

		// TX FIFO Watermark
		priv->judge->spiCtrl.fifo_wmark_tx = atoi( argv[11] );
		if( priv->judge->spiCtrl.fifo_wmark_tx > S_GDD_CT_SPI_FIFO_DEPTH[priv->judge->ch] ){
			Ddim_Print( ("please check fifo_wmark_tx parameter!!\n" ) );
			return;
		}

		// RX FIFO Watermark
		priv->judge->spiCtrl.fifo_wmark_rx = atoi( argv[12] );
		if( priv->judge->spiCtrl.fifo_wmark_rx > S_GDD_CT_SPI_FIFO_DEPTH[priv->judge->ch] ){
			Ddim_Print( ("please check fifo_wmark_rx parameter!!\n" ) );
			return;
		}

		// DMA enable
		if( strcmp(argv[13], "dma") == 0 ){
			priv->judge->spiCtrl.dma_en = 1;

			priv->judge->val = atoi( argv[14] );
			if( priv->judge->val <= 0xFFFFFF ){
				priv->judge->spiCtrl.dma_recv_to = priv->judge->val;
			}else {
				Ddim_Print( ("please check dma_recv_to parameter!!\n" ) );
				return;
			}
		}
		else if( strcmp(argv[13], "cpu") == 0 ){
			priv->judge->spiCtrl.dma_en = 0;
			priv->judge->spiCtrl.dma_recv_to = 0;
		}else{
			Ddim_Print( ("please check dma_en parameter!!\n" ) );
			return;
		}

		// Slave Select Output
		priv->judge->val = atoi( argv[15] );
		if( priv->judge->val >= D_DD_SPI_SS_MAX ){
			Ddim_Print( ("please check ssout parameter!!\n" ) );
			return;
		}else {
			for( priv->judge->index = 0; priv->judge->index < D_DD_SPI_SS_MAX; priv->judge->index++ ){
				if( priv->judge->val == priv->judge->index ){
					priv->judge->spiCtrl.ss_info.ssout[priv->judge->index] = 1;
				}else {
					priv->judge->spiCtrl.ss_info.ssout[priv->judge->index] = 0;
				}
			}
		}

		// Slave Select Polarity
		priv->judge->val = atoi( argv[16] );
		if( priv->judge->val > 1 ){
			Ddim_Print( ("please check sspol parameter!!\n" ) );
			return;
		}else {
			for( priv->judge->index = 0; priv->judge->index < D_DD_SPI_SS_MAX; priv->judge->index++ ){
				priv->judge->spiCtrl.ss_info.sspol[priv->judge->index] = priv->judge->val;
			}
		}

		// ssOUT Continuous Transfer
		priv->judge->spiCtrl.ss_info.cont_trans = atoi( argv[17] );
		if( priv->judge->spiCtrl.ss_info.cont_trans > E_DD_SPI_CONT_TRANS_ACT_FIFO_EMPTY ){
			Ddim_Print( ("please check cont_trans parameter!!\n" ) );
			return;
		}

		// Callback function
		priv->judge->val = atoi( argv[18] );
		if( priv->judge->val == 0 ){
			priv->judge->spiCtrl.pcallback = NULL;
		}else{
			asyncTmp = ct_dd_spi_test_get_async(test);
			tmp = test;
			priv->judge->spiCtrl.pcallback = ctDdSpi_cb;
			ct_dd_spi_test_set_result(test,resultTmp);
			test->gctDdSpiAsync = 1;
		}

		// Callback function for ssIN/OUT
		priv->judge->val = atoi( argv[19] );
		if( priv->judge->val == 0 ){
			priv->judge->spiCtrl.pcallback_ss = NULL;
		}else{
			priv->judge->spiCtrl.pcallback_ss = ctDdSpiSs_cb;
			test->gctDdSpiAsync = 1;
		}

		// Set Control
		priv->judge->ret = Dd_SPI_Ctrl( priv->judge->ch, &(priv->judge->spiCtrl) );

		Ddim_Print(("Dd_SPI_Ctrl() End. ret=0x%08X\n", priv->judge->ret));
		ctDdSpiPrintCtrl( priv->judge->ch, &(priv->judge->spiCtrl) );
	}
	else if( strcmp(argv[1], "get_ctrl") == 0 ){
		T_DD_SPI_CTRL spiCtrl;

		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = Dd_SPI_Get_Ctrl( priv->judge->ch, &spiCtrl );

		Ddim_Print(("Dd_SPI_Get_Ctrl() End. ret=0x%08X\n", priv->judge->ret));
		ctDdSpiPrintCtrl( priv->judge->ch, &spiCtrl );
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

			if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
				/* pgr0539 */
				memset( S_GDD_CT_SPI_SEND_BUF32, data, sizeof(S_GDD_CT_SPI_SEND_BUF32));	

				// Set send data
				priv->judge->ret = Dd_SPI_Set_Send_Data( priv->judge->ch,S_GDD_CT_SPI_SEND_BUF32, 
														test->gctDdSpiTransNum );
			}
			
			else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
				/* pgr0539 */
				memset( S_GDD_CT_SPI_SEND_BUF16, data, sizeof(S_GDD_CT_SPI_SEND_BUF16) );	

				// Set send data
				priv->judge->ret = Dd_SPI_Set_Send_Data( priv->judge->ch, S_GDD_CT_SPI_SEND_BUF16,
																test->gctDdSpiTransNum );
			}else {
				/* pgr0539 */
				memset( S_GDD_CT_SPI_SEND_BUF8, data, sizeof(S_GDD_CT_SPI_SEND_BUF8) );		

				// Set send data
				priv->judge->ret = Dd_SPI_Set_Send_Data( priv->judge->ch, S_GDD_CT_SPI_SEND_BUF8,
														test->gctDdSpiTransNum );
			}

			Ddim_Print(("Dd_SPI_Set_Send_Data() End. ret=0x%08X\n", priv->judge->ret));
		}
		else if( strcmp(argv[4], "addr") == 0 ){
			S_GDD_CT_SPI_SEND_DATA_ADDR = strtoul( argv[5], &(priv->judge->endstr), 16 );

			data = strtoul( argv[6], &(priv->judge->endstr), 16 );

			if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_SEND_DATA_ADDR, data, (test->gctDdSpiTransNum * 4) );	
			}
			else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_SEND_DATA_ADDR, data, (test->gctDdSpiTransNum * 2) );	
			}else {
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_SEND_DATA_ADDR, data, test->gctDdSpiTransNum );		
			}

			// Set send data
			priv->judge->ret = Dd_SPI_Set_Send_Data( priv->judge->ch, (kpointer)S_GDD_CT_SPI_SEND_DATA_ADDR, 
													test->gctDdSpiTransNum );

			Ddim_Print(("Dd_SPI_Set_Send_Data() End. ret=0x%08X\n", priv->judge->ret));
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

			if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
				memset( S_GDD_CT_SPI_RECV_BUF32, 0, sizeof(S_GDD_CT_SPI_RECV_BUF32) );

				// Set receive data
				priv->judge->ret = Dd_SPI_Set_Recv_Data( priv->judge->ch, S_GDD_CT_SPI_RECV_BUF16,
														test->gctDdSpiTransNum );
			}
			else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
				memset( S_GDD_CT_SPI_RECV_BUF16, 0, sizeof(S_GDD_CT_SPI_RECV_BUF16) );

				// Set receive data
				priv->judge->ret = Dd_SPI_Set_Recv_Data( priv->judge->ch, S_GDD_CT_SPI_RECV_BUF16,
														test->gctDdSpiTransNum );
			}else {
				memset( S_GDD_CT_SPI_RECV_BUF8, 0, sizeof(S_GDD_CT_SPI_RECV_BUF8) );

				// Set receive data
				priv->judge->ret = Dd_SPI_Set_Recv_Data( priv->judge->ch, S_GDD_CT_SPI_RECV_BUF8,
														test->gctDdSpiTransNum );
			}
		}
		else if( strcmp(argv[4], "addr") == 0 ){
			S_GDD_CT_SPI_RECV_DATA_ADDR = strtoul( argv[5], &(priv->judge->endstr), 16 );

			if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_RECV_DATA_ADDR, 0, (test->gctDdSpiTransNum * 4) );	
			}
			else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_RECV_DATA_ADDR, 0, (test->gctDdSpiTransNum * 2) );	
			}else {
				/* pgr0539 */
				memset( (kpointer)S_GDD_CT_SPI_RECV_DATA_ADDR, 0, test->gctDdSpiTransNum );			
			}

			// Set send data
			priv->judge->ret = Dd_SPI_Set_Recv_Data( priv->judge->ch, (kpointer)S_GDD_CT_SPI_RECV_DATA_ADDR,
													test->gctDdSpiTransNum );
		}else {
			Ddim_Print( ("please check data/addr parameter!!\n" ) );
		}

		Ddim_Print(("Dd_SPI_Set_Recv_Data() End. ret=0x%08X\n", priv->judge->ret));
	}
	// Start send
	else if ( strcmp( argv[1], "start_send" ) == 0 ){		
		priv->judge->ch = atoi( argv[2] );
		// gCT_DD_SPI_Trans_Type = CtDdSpiJudge_SPI_TRNAS_TYPE_SEND;
		ct_dd_spi_judge_set_trans_type(CtDdSpiJudge_SPI_TRNAS_TYPE_SEND);

		priv->judge->ret = Dd_SPI_Start_Send( priv->judge->ch );

		Ddim_Print(("Dd_SPI_Start_Send() End. ret=0x%08X\n", priv->judge->ret));

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

		priv->judge->ret = Dd_SPI_Start_Recv( priv->judge->ch );

		Ddim_Print(("Dd_SPI_Start_Recv() End. ret=0x%08X\n", priv->judge->ret));

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

		priv->judge->ret = Dd_SPI_Start_Full_Duplex( priv->judge->ch );

		Ddim_Print(("Dd_SPI_Start_Full_Duplex() End. ret=0x%08X\n", priv->judge->ret));

		if( priv->judge->ret == D_DDIM_OK ){
			if( !test->gctDdSpiAsync ){
				ctDdSpiPrintData(test);
			}
		}
	}
	else if ( strcmp( argv[1], "start_send_dma" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );
		priv->judge->dmaCh[0] = atoi( argv[3] );

		if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
			if( S_GDD_CT_SPI_SEND_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_DATA_ADDR, 
														test->gctDdSpiTransNum * 4 );
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr( (kulong)S_GDD_CT_SPI_SEND_BUF32,
														sizeof(S_GDD_CT_SPI_SEND_BUF32) );
			}
		}
		else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
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

		priv->judge->ret = Dd_SPI_Start_Send_DMA( priv->judge->ch, priv->judge->dmaCh[0]);

		Ddim_Print(("Dd_SPI_Start_Send_DMA() End. ret=0x%08X\n", priv->judge->ret));

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

		if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
			if( S_GDD_CT_SPI_RECV_DATA_ADDR ){
				DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)S_GDD_CT_SPI_RECV_DATA_ADDR, 
														test->gctDdSpiTransNum * 4);
			}else {
				DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)S_GDD_CT_SPI_RECV_BUF32, 
														sizeof(S_GDD_CT_SPI_RECV_BUF32));
			}
		}
		else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
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

		priv->judge->ret = Dd_SPI_Start_Recv_DMA( priv->judge->ch, priv->judge->dmaCh[0] );

		Ddim_Print(("Dd_SPI_Start_Recv_DMA() End. ret=0x%08X\n", priv->judge->ret));

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

		if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_16 ){
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
		else if( test->gctDdSpiBitLen > E_DD_SPI_BIT_LEN_8 ){
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

		priv->judge->ret = Dd_SPI_Start_Full_Duplex_DMA( priv->judge->ch, priv->judge->dmaCh[0],
															priv->judge->dmaCh[1] );

		Ddim_Print(("Dd_SPI_Start_Full_Duplex_DMA() End. ret=0x%08X\n", priv->judge->ret));

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

		priv->judge->ret = Dd_SPI_Stop( priv->judge->ch );

		Ddim_Print(("Dd_SPI_Stop() End. ret=0x%08X\n", priv->judge->ret));
	}
	else if ( strcmp( argv[1], "set_ss" ) == 0 ){
		/* ddspi set_ss [priv->judge->ch] [cont_trans] [ssout0] [ssout1] 
		*[ssout2] [ssout3] [sspol0] [sspol1] [sspol2] [sspol3]
		*/
		if( argc < 12 ){
			Ddim_Print( ("please check 12 parameter!!\n" ) );
			return;
		}

		priv->judge->ch = atoi( argv[2] );
		priv->judge->ssInfo.cont_trans = atoi( argv[3] );

		for( priv->judge->index = 0; priv->judge->index < D_DD_SPI_SS_MAX; priv->judge->index++ ){
			priv->judge->ssInfo.ssout[priv->judge->index] = atoi( argv[4 + priv->judge->index] );
		}
		for( priv->judge->index = 0; priv->judge->index < D_DD_SPI_SS_MAX; priv->judge->index++ ){
			priv->judge->ssInfo.sspol[priv->judge->index] = atoi( argv[4 + D_DD_SPI_SS_MAX + priv->judge->index]);
		}

		priv->judge->ret = Dd_SPI_Set_Slave_Select( priv->judge->ch, &(priv->judge->ssInfo) );

		Ddim_Print(("Dd_SPI_Set_Slave_Select End. ret=0x%08X\n", priv->judge->ret));
	}
	else if ( strcmp( argv[1], "get_ss" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = Dd_SPI_Get_Slave_Select( priv->judge->ch, &(priv->judge->ssInfo) );

		Ddim_Print(("Dd_SPI_Get_Slave_Select End. ret=0x%08X\n", priv->judge->ret));

		Ddim_Print(("---Get SS_INFO---\n"));
		Ddim_Print(("cont_trans = %d\n", priv->judge->ssInfo.cont_trans));
		for( priv->judge->index = 0; priv->judge->index < D_DD_SPI_SS_MAX; priv->judge->index++ ){
			Ddim_Print(("ssout[%d] = %d\n", priv->judge->index, priv->judge->ssInfo.ssout[priv->judge->index]));
		}
		for( priv->judge->index = 0; priv->judge->index < D_DD_SPI_SS_MAX; priv->judge->index++ ){
			Ddim_Print(("sspol[%d] = %d\n", priv->judge->index, priv->judge->ssInfo.sspol[priv->judge->index]));
		}
	}
	else if ( strcmp( argv[1], "set_div" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );
		priv->judge->clkDiv = atoi( argv[3] );

		priv->judge->ret = Dd_SPI_Set_Clock_Divisor( priv->judge->ch, priv->judge->clkDiv );

		Ddim_Print(("Dd_SPI_Set_Clock_Divisor End. ret=0x%08X\n", priv->judge->ret));
	}
	else if ( strcmp( argv[1], "get_div" ) == 0 ){
		priv->judge->ch = atoi( argv[2] );

		priv->judge->ret = Dd_SPI_Get_Clock_Divisor( priv->judge->ch, &(priv->judge->clkDiv) );

		Ddim_Print(("Dd_SPI_Get_Clock_Divisor End. ret=0x%08X, clkDiv=%d\n", priv->judge->ret, priv->judge->clkDiv));
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
