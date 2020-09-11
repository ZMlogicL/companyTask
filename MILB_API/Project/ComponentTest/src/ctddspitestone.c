/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :guguangjian
*@brief               :CtDdSpiTestone类
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
#include "ctddspitestone.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdSpiTestone, ct_dd_spi_testone);
#define CT_DD_SPI_TESTONE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdSpiTestonePrivate,CT_TYPE_DD_SPI_TESTONE))

struct _CtDdSpiTestonePrivate
{
	CtDdSpiTest *test;
};

/*
 *DECLS
 */
static void 		ctDdSpiPrintSendTestReg(kuchar ch);
static void 		ctDdSpiPrintFullReg(kuchar ch);
static void 		ctDdSpiPrintSs(kuchar ch);
static void 		ctDdSpiPrintDmaReg(kuchar ch, kuchar dmaCh);


static void ct_dd_spi_testone_constructor(CtDdSpiTestone *self) 
{
	self->priv = CT_DD_SPI_TESTONE_GET_PRIVATE(self);
}

static void ct_dd_spi_testone_destructor(CtDdSpiTestone *self) 
{

}

/*
 *IMPL
 */
static void ctDdSpiPrintSendTestReg(kuchar ch)
{
	Ddim_Print(("EN.bit.__ENABLEREQ = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_EN.word        = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
	Ddim_Print(("TXDATA             = 0x%04lX\n", IO_SPI[ch].TXDATA));
}

static void ctDdSpiPrintFullReg(kuchar ch)
{
	Ddim_Print(("EN.bit.__ENABLEREQ      = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_EN.word             = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
	Ddim_Print(("TXDATA                  = 0x%04lX\n", IO_SPI[ch].TXDATA));
	Ddim_Print(("FIFO_WMK.bit.RXWMARKSET = %d\n", IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET));
}

static void ctDdSpiPrintSs(kuchar ch)
{
	Ddim_Print(("CTRL.bit.CONTXFER           = %d\n", IO_SPI[ch].CTRL.bit.CONTXFER));
	Ddim_Print(("AUX_CTRL.bit.CONTXFEREXTEND = %d\n", IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND));
}

static void ctDdSpiPrintDmaReg(kuchar ch, kuchar dmaCh)
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
void ct_dd_spi_testone_set_test(CtDdSpiTestone *self,CtDdSpiTest *test)
{
	CtDdSpiTestonePrivate *priv = CT_DD_SPI_TESTONE_GET_PRIVATE(self);

	priv->test = test;
}

/* start full normal (8bit 1byte async) */
void ct_dd_spi_testone_pc_start_full_1(CtDdSpiTestone *self)
{
	CtDdSpiTestonePrivate *priv = self->priv;  
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full normal (8bit 18byte async) */
void ct_dd_spi_testone_pc_start_full_2( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;  
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
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	// gDD_CT_SPI_Send_Buf8[17] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 17);

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full normal (8bit 1byte sync) */
void ct_dd_spi_testone_pc_start_full_3( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;  
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full normal (8bit 18byte sync) */
void ct_dd_spi_testone_pc_start_full_4( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;  
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	// gDD_CT_SPI_Send_Buf8[17] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 17);

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full error (D_DD_SPI_FORCE_STOP) (RXEMPTY=1) (8bit 18byte sync) */
void ct_dd_spi_testone_pc_start_full_5( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 1;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	// gDD_CT_SPI_Send_Buf8[17] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 17);

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full error (D_DD_SPI_RECV_OVERRUN_ERROR) (8bit 18byte sync) */
void ct_dd_spi_testone_pc_start_full_6( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 1;

	// gDD_CT_SPI_Send_Buf8[17] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 17);

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full normal (16bit 1byte sync) */
void ct_dd_spi_testone_pc_start_full_7( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 1 data 0xA5A5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full normal (16bit 18byte sync) */
void ct_dd_spi_testone_pc_start_full_8( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5A5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	// gDD_CT_SPI_Send_Buf16[17] = 0xB6B6;
	ct_dd_spi_set_sendbuf16(0xB6B6, 17);

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full error (D_DD_SPI_FORCE_STOP) (RXEMPTY=1) (16bit 18byte sync) */
void ct_dd_spi_testone_pc_start_full_9( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5A5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 1;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	// gDD_CT_SPI_Send_Buf16[17] = 0xB6B6;
	ct_dd_spi_set_sendbuf16(0xB6B6, 17);

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full error (D_DD_SPI_RECV_OVERRUN_ERROR) (16bit 18byte sync) */
void ct_dd_spi_testone_pc_start_full_10( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5A5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 1;

	// gDD_CT_SPI_Send_Buf16[17] = 0xB6B6;
	ct_dd_spi_set_sendbuf16(0xB6B6, 17);

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full error (D_DD_SPI_FORCE_STOP) (RXEMPTY=0) (16bit 18byte sync) */
void ct_dd_spi_testone_pc_start_full_11( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5A5");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	// gDD_CT_SPI_Send_Buf16[17] = 0xB6B6;
	ct_dd_spi_set_sendbuf16(0xB6B6, 17);

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_full 2");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintFullReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* stop normal with CPU */
void ct_dd_spi_testone_pc_stop_1( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 0 1 data 0xA5");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 0");
	ct_dd_spi_test_cmd_wrap("ddspi stop 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintSendTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* stop normal with DMA */
void ct_dd_spi_testone_pc_stop_2( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	priv->test->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 0 0 lsb 8 12000000 0 0 8 8 dma 1 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 0 1 data 0xA5");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi stop 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* set SS info normal1 */
void ct_dd_spi_testone_pc_setget_ss_1( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	// ddspi set_ss [ch] [cont_trans] [ssout0] [ssout1] [ssout2] [ssout3] [sspol0] [sspol1] [sspol2] [sspol3]
	ct_dd_spi_test_cmd_wrap("ddspi set_ss 0 0 1 0 0 1 0 1 1 0");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi get_ss 0");

	ctDdSpiPrintSs( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* set SS info normal2 */
void ct_dd_spi_testone_pc_setget_ss_2( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 1;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	// ddspi set_ss [ch] [cont_trans] [ssout0] [ssout1] [ssout2] [ssout3] [sspol0] [sspol1] [sspol2] [sspol3]
	ct_dd_spi_test_cmd_wrap("ddspi set_ss 1 1 0 1 1 0 1 0 0 1");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi get_ss 1");

	ctDdSpiPrintSs( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* set SS info normal3 */
void ct_dd_spi_testone_pc_setget_ss_3( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	// ddspi set_ss [ch] [cont_trans] [ssout0] [ssout1] [ssout2] [ssout3] [sspol0] [sspol1] [sspol2] [sspol3]
	ct_dd_spi_test_cmd_wrap("ddspi set_ss 2 2 1 1 1 1 1 1 1 1");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi get_ss 2");

	ctDdSpiPrintSs( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* set get clkdiv normal */
void ct_dd_spi_testone_pc_setget_clkdiv_1( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi set_div 0 255");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi get_div 0");

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (XFERDONEPULSE interrupt) */
void ct_dd_spi_testone_pc_handler_1( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---cont_trans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 1");

	IO_SPI[ch].INT_CLR.word = 0;
	IO_SPI[ch].INT_ST.bit.XFERDONEPULSE = 1;

	Dd_SPI_Int_Handler( ch );

	ret = priv->test->gctDdSpiResult;

	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (TXEMPTYPULSE interrupt, dma_wait = 2) */
void ct_dd_spi_testone_pc_handler_2( CtDdSpiTestone *self  )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 dma 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 18 data 0xA5");

	// gDD_CT_SPI_Send_Buf8[17] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 17);

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].INT_ST.bit.TXEMPTYPULSE = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_send_dma 2 0");

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	Dd_SPI_Int_Handler( ch );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintSendTestReg( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* handler (TXEMPTYPULSE interrupt, dma_wait = 0, spi_mode = SEND, send_pos < num) */
void ct_dd_spi_testone_pc_handler_3( CtDdSpiTestone *self )
{
	CtDdSpiTestonePrivate *priv = self->priv;
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

	Dd_SPI_Int_Handler( ch );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintSendTestReg( ch );
	Ddim_Print(("INT_CLR.word = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

CtDdSpiTestone* ct_dd_spi_testone_new(void) 
{
    CtDdSpiTestone *self = k_object_new_with_private(CT_TYPE_DD_SPI_TESTONE, sizeof(CtDdSpiTestonePrivate));

    return self;
}
