/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :guguangjian
*@brief               :CtDdSpiTesttwo类
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
#include "ctddspimain.h"
#include "ctddspitest.h"
#include "ctddspitesttwo.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdSpiTesttwo, ct_dd_spi_testtwo);
#define CT_DD_SPI_TESTTWO_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdSpiTesttwoPrivate,CT_TYPE_DD_SPI_TESTTWO))

struct _CtDdSpiTesttwoPrivate
{
	CtDdSpiTest *test;
};

/*
 *DECLS
 */
static void 			ctDdSpiPrintRecvTesttwoReg(kuchar ch);
static void 			ctDdSpiPrintSendTesttwoReg(kuchar ch);
static void 			ctDdSpiPrintTesttwoDmaReg(kuchar ch, kuchar dmaCh);

static void ct_dd_spi_testtwo_constructor(CtDdSpiTesttwo *self) 
{
	self->priv = CT_DD_SPI_TESTTWO_GET_PRIVATE(self);
}

static void ct_dd_spi_testtwo_destructor(CtDdSpiTesttwo *self) 
{
	CtDdSpiTesttwoPrivate *priv = CT_DD_SPI_TESTTWO_GET_PRIVATE(self);

	priv->test =NULL;
}

/*
 *IMPL
 */
static void ctDdSpiPrintRecvTesttwoReg(kuchar ch)
{
	Ddim_Print(("EN.bit.__ENABLEREQ      = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_EN.word             = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
	Ddim_Print(("FIFO_WMK.bit.RXWMARKSET = %d\n", IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET));
	Ddim_Print(("TX_DWR.word             = 0x%04lX\n", IO_SPI[ch].TX_DWR.word));
}

static void ctDdSpiPrintSendTesttwoReg(kuchar ch)
{
	Ddim_Print(("EN.bit.__ENABLEREQ = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_EN.word        = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
	Ddim_Print(("TXDATA             = 0x%04lX\n", IO_SPI[ch].TXDATA));
}

static void ctDdSpiPrintTesttwoDmaReg(kuchar ch, kuchar dmaCh)
{
	Ddim_Print(("EN.bit.__ENABLEREQ      = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_EN.word             = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
	Ddim_Print(("DMACA.bit.EB            = %d\n", IO_HDMAC1.DMAC[dmaCh].DMACA.bit.EB));
	Ddim_Print(("DMACA.bit.IS            = 0x%02X\n", IO_HDMAC1.DMAC[dmaCh].DMACA.bit.IS));
	Ddim_Print(("DMACB.bit.TW            = %d\n", IO_HDMAC1.DMAC[dmaCh].DMACB.bit.TW));
	Ddim_Print(("DMACA.bit.TC            = %d\n", IO_HDMAC1.DMAC[dmaCh].DMACA.bit.TC));
	Ddim_Print(("DMACB.bit.FD            = %d\n", IO_HDMAC1.DMAC[dmaCh].DMACB.bit.FD));
	Ddim_Print(("DMACB.bit.FS            = %d\n", IO_HDMAC1.DMAC[dmaCh].DMACB.bit.FS));
	Ddim_Print(("DMACB.bit.RC            = %d\n", IO_HDMAC1.DMAC[dmaCh].DMACB.bit.RC));
}

/*
 *PUBLIC
 */
void ct_dd_spi_testtwo_set_test(CtDdSpiTesttwo *self,CtDdSpiTest *test)
{
	CtDdSpiTesttwoPrivate *priv = CT_DD_SPI_TESTTWO_GET_PRIVATE(self);

	priv->test = test;
}

/* handler (RXFIFOOVERFLOW interrupt) */
void ct_dd_spi_testtwo_pc_handler_8( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv;;
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 18;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].INT_ST.bit.RXFIFOOVERFLOW = 1;
	IO_SPI[ch].INT_ST.bit.TXEMPTYPULSE = 0;
	IO_SPI[ch].TXFIFO.bit.TX_FIFO_LEVEL = 8;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	Dd_SPI_Int_Handler( ch );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintRecvTesttwoReg( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (RXWMARKPULSE interrupt, RX_FIFO_LEVEL = 8) */
void ct_dd_spi_testtwo_pc_handler_9( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 18;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_ST.bit.RXWMARKPULSE = 1;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 8;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	Dd_SPI_Int_Handler( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Dd_SPI_Int_Handler( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Dd_SPI_Int_Handler( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintRecvTesttwoReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (RXFULLPULSE interrupt, RX_FIFO_LEVEL = 16) */
void ct_dd_spi_testtwo_pc_handler_10( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 18;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_ST.bit.RXFULLPULSE = 1;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 16;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	Dd_SPI_Int_Handler( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Dd_SPI_Int_Handler( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintRecvTesttwoReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (RXTIMEOUT interrupt, RX_FIFO_LEVEL = 8, 16bit) */
void ct_dd_spi_testtwo_pc_handler_11( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 18;
	priv->test->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_ST.bit.RXTIMEOUT = 1;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 8;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	Dd_SPI_Int_Handler( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Dd_SPI_Int_Handler( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Dd_SPI_Int_Handler( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintRecvTesttwoReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

void ct_dd_spi_testtwo_pc_calc_1( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 0;

	IO_CHIPTOP.CLKSEL8.bit.SPICLK = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi cal 108000000");

	ret = priv->test->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

void ct_dd_spi_testtwo_pc_calc_2( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 0;

	IO_CHIPTOP.CLKSEL8.bit.SPICLK = 1;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi cal 300000");

	ret = priv->test->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

void ct_dd_spi_testtwo_pc_calc_3( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 0;

	IO_CHIPTOP.CLKSEL8.bit.SPICLK = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi cal 20000000");

	ret = priv->test->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

void ct_dd_spi_testtwo_pc_calc_4( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 0;

	IO_CHIPTOP.CLKSEL8.bit.SPICLK = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi cal 108000001");

	ret = priv->test->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send DMA (sync, 8bit, 1byte) */
void ct_dd_spi_testtwo_pc_start_send_dma_1( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 1;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 dma 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5");

	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTesttwoDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send DMA (sync, 8bit, 262143byte) */
void ct_dd_spi_testtwo_pc_start_send_dma_2( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 262143;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 dma 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 262143 data 0xA5");

	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTesttwoDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send DMA (async, 16bit, 1byte) */
void ct_dd_spi_testtwo_pc_start_send_dma_3( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 1;
	priv->test->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 dma 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5A5");

	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTesttwoDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send DMA (async, 16bit, 262143byte) */
void ct_dd_spi_testtwo_pc_start_send_dma_4( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 262143;
	priv->test->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 dma 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 262143 data 0xA5A5");

	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTesttwoDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send DMA (sync, 8bit, 1byte, TXEMPTY=0) */
void ct_dd_spi_testtwo_pc_start_send_dma_5( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 1;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 dma 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5");

	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");
	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTesttwoDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send DMA (sync, 8bit, 1byte, force_stop_flg=1) */
void ct_dd_spi_testtwo_pc_start_send_dma_6( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 1;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 dma 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5");

	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");
	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTesttwoDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send DMA (async, 8bit, 1byte, TXEMPTY=0) */
void ct_dd_spi_testtwo_pc_start_send_dma_7( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 1;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 dma 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5");

	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTesttwoDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send DMA (async, 16bit, 1byte, force_stop_flg=1) */
void ct_dd_spi_testtwo_pc_start_send_dma_8( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 1;
	priv->test->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 dma 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5A5");

	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTesttwoDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (TXWMARKPULSE interrupt, spi_mode = RECV, TX_FIFO_LEVEL = 8) */
void ct_dd_spi_testtwo_pc_handler_7( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 18;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_ST.bit.TXWMARKPULSE = 1;
	IO_SPI[ch].TXFIFO.bit.TX_FIFO_LEVEL = 8;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	Dd_SPI_Int_Handler( ch );

	Dd_SPI_Int_Handler( ch );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintRecvTesttwoReg( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (TXEMPTYPULSE interrupt, spi_mode = RECV, TX_FIFO_LEVEL = 8) */
void ct_dd_spi_testtwo_pc_handler_6( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiTransNum = 18;
	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_ST.bit.TXEMPTYPULSE = 1;
	IO_SPI[ch].TXFIFO.bit.TX_FIFO_LEVEL = 8;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	Dd_SPI_Int_Handler( ch );

	Dd_SPI_Int_Handler( ch );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintRecvTesttwoReg( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (TXWMARKPULSE interrupt, dma_wait = 0, spi_mode = SEND) */
void ct_dd_spi_testtwo_pc_handler_5( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5");

	// gDD_CT_SPI_Send_Buf8[17] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 17);

	IO_SPI[ch].ST.bit.TXFULL = 1;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].INT_ST.bit.TXEMPTYPULSE = 0;
	IO_SPI[ch].INT_ST.bit.TXWMARKPULSE = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 2");

	IO_SPI[ch].ST.bit.TXFULL = 0;

	Dd_SPI_Int_Handler( ch );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintSendTesttwoReg( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (TXEMPTYPULSE interrupt, dma_wait = 0, spi_mode = SEND, send_pos == num) */
void ct_dd_spi_testtwo_pc_handler_4( CtDdSpiTesttwo *self )
{
	CtDdSpiTesttwoPrivate *priv = self->priv; 
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5");

	// gDD_CT_SPI_Send_Buf8[17] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 17);

	IO_SPI[ch].ST.bit.TXFULL = 1;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].INT_ST.bit.TXEMPTYPULSE = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 2");

	IO_SPI[ch].ST.bit.TXFULL = 0;

	Dd_SPI_Int_Handler( ch );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintSendTesttwoReg( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

CtDdSpiTesttwo* ct_dd_spi_testtwo_new(void) 
{
    CtDdSpiTesttwo *self = k_object_new_with_private(CT_TYPE_DD_SPI_TESTTWO, sizeof(CtDdSpiTesttwoPrivate));

    return self;
}