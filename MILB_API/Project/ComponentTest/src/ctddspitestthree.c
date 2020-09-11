/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :guguangjian
*@brief               :CtDdSpiTestthree类
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
#include "ctddspitestthree.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdSpiTestthree, ct_dd_spi_testthree);
#define CT_DD_SPI_TESTTHREE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdSpiTestthreePrivate,CT_TYPE_DD_SPI_TESTTHREE))

struct _CtDdSpiTestthreePrivate
{
	CtDdSpiTest *test;
};

/*
 *DECLS
 */
static void 		ctDdSpiPrintTestthreeDmaReg(kuchar ch, kuchar dmaCh);
static void 		ctDdSpiPrintDmaFullReg(kuchar ch, kuchar send_dma_ch, kuchar recv_dma_ch);

static void ct_dd_spi_testthree_constructor(CtDdSpiTestthree *self) 
{
	self->priv = CT_DD_SPI_TESTTHREE_GET_PRIVATE(self);
}

static void ct_dd_spi_testthree_destructor(CtDdSpiTestthree *self) 
{
	CtDdSpiTestthreePrivate *priv = CT_DD_SPI_TESTTHREE_GET_PRIVATE(self);
	
	priv->test = NULL;
}

/*
 *IMPL
 */
static void ctDdSpiPrintTestthreeDmaReg( kuchar ch, kuchar dmaCh )
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

static void ctDdSpiPrintDmaFullReg( kuchar ch, kuchar send_dma_ch, kuchar recv_dma_ch )
{
	Ddim_Print(("EN.bit.__ENABLEREQ      = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_EN.word             = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
	Ddim_Print(("DMACA.bit.EB(send)      = %d\n", IO_HDMAC1.DMAC[send_dma_ch].DMACA.bit.EB));
	Ddim_Print(("DMACA.bit.IS(send)      = 0x%02X\n", IO_HDMAC1.DMAC[send_dma_ch].DMACA.bit.IS));
	Ddim_Print(("DMACA.bit.TC(send)      = %d\n", IO_HDMAC1.DMAC[send_dma_ch].DMACA.bit.TC));
	Ddim_Print(("DMACB.bit.RC(send)      = %d\n", IO_HDMAC1.DMAC[send_dma_ch].DMACB.bit.RC));
	Ddim_Print(("DMACA.bit.EB(recv)      = %d\n", IO_HDMAC1.DMAC[recv_dma_ch].DMACA.bit.EB));
	Ddim_Print(("DMACA.bit.IS(recv)      = 0x%02X\n", IO_HDMAC1.DMAC[recv_dma_ch].DMACA.bit.IS));
	Ddim_Print(("DMACA.bit.TC(recv)      = %d\n", IO_HDMAC1.DMAC[recv_dma_ch].DMACA.bit.TC));
	Ddim_Print(("DMACB.bit.RC(recv)      = %d\n", IO_HDMAC1.DMAC[recv_dma_ch].DMACB.bit.RC));
}

/*
 *PUBLIC
 */
void ct_dd_spi_testthree_set_test(CtDdSpiTestthree *self,CtDdSpiTest *test)
{
	CtDdSpiTestthreePrivate *priv = CT_DD_SPI_TESTTHREE_GET_PRIVATE(self);

	priv->test = test;
}

/* start recv DMA (sync, 8bit, 1byte) */
void ct_dd_spi_testthree_pc_start_recv_dma_1( CtDdSpiTestthree *self )
{	
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv_dma 2 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTestthreeDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv DMA (sync, 8bit, 262143byte) */
void ct_dd_spi_testthree_pc_start_recv_dma_2( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 262143 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv_dma 2 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTestthreeDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv DMA (async, 16bit, 1byte) */
void ct_dd_spi_testthree_pc_start_recv_dma_3( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data 0xA5A5");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv_dma 2 0");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTestthreeDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv DMA (async, 16bit, 262143byte) */
void ct_dd_spi_testthree_pc_start_recv_dma_4( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 262143 data 0xA5A5");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv_dma 2 0");

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

	ctDdSpiPrintTestthreeDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv DMA (sync, 8bit, 1byte, RXOVERFLOW=1) */
void ct_dd_spi_testthree_pc_start_recv_dma_5( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv_dma 2 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTestthreeDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv DMA (sync, 8bit, 1byte, force_stop_flg=1) */
void ct_dd_spi_testthree_pc_start_recv_dma_6( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW =0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");
	ct_dd_spi_test_cmd_wrap("ddspi start_recv_dma 2 0");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTestthreeDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv DMA (async, 8bit, 1byte, RXOVERFLOW=1) */
void ct_dd_spi_testthree_pc_start_recv_dma_7( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv_dma 2 0");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTestthreeDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv DMA (async, 16bit, 1byte, force_stop_flg=1) */
void ct_dd_spi_testthree_pc_start_recv_dma_8( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data 0xA5A5");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_recv_dma 2 0");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintTestthreeDmaReg( ch, 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full DMA (sync, 8bit, 1byte) */
void ct_dd_spi_testthree_pc_start_full_dma_1( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full_dma 2 0 1");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaFullReg( ch, 0, 1 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full DMA (sync, 8bit, 262143byte) */
void ct_dd_spi_testthree_pc_start_full_dma_2( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 262143 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full_dma 2 0 1");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaFullReg( ch, 0, 1 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full DMA (async, 16bit, 1byte) */
void ct_dd_spi_testthree_pc_start_full_dma_3( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full_dma 2 0 1");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[1].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 1 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaFullReg( ch, 0, 1 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full DMA (async, 16bit, 262143byte) */
void ct_dd_spi_testthree_pc_start_full_dma_4( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 262143 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full_dma 2 0 1");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[1].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 1 );

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[1].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 1 );

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[1].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 1 );

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[1].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 1 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaFullReg( ch, 0, 1 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full DMA (sync, 8bit, 1byte, RXOVERFLOW=1) */
void ct_dd_spi_testthree_pc_start_full_dma_5( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 1;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full_dma 2 0 1");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaFullReg( ch, 0, 1 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full DMA (sync, 8bit, 1byte, force_stop_flg=1) */
void ct_dd_spi_testthree_pc_start_full_dma_6( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");
	ct_dd_spi_test_cmd_wrap("ddspi start_full_dma 2 0 1");

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaFullReg( ch, 0, 1 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full DMA (async, 8bit, 1byte, RXOVERFLOW=1) */
void ct_dd_spi_testthree_pc_start_full_dma_7( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 1;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_full_dma 2 0 1");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[1].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 1 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaFullReg( ch, 0, 1 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start full DMA (async, 16bit, 1byte, force_stop_flg=1) */
void ct_dd_spi_testthree_pc_start_full_dma_8( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
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
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;
	IO_SPI[ch].INT_CLR.word = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_full_dma 2 0 1");

	priv->test->gctDdSpiAsync = 0;	// not need data print

	IO_HDMAC1.DMAC[0].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 0 );

	IO_HDMAC1.DMAC[1].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
	Dd_HDMAC1_Int_Handler( 1 );

	ret = priv->test->gctDdSpiResult;

	ctDdSpiPrintDmaFullReg( ch, 0, 1 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

void ct_dd_spi_testthree_pc_set_enable_1( CtDdSpiTestthree *self )
{
	CtDdSpiTestthreePrivate *priv =self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	IO_SPI[ch].EN.bit.__ENABLEREQ = 1;

	ct_dd_spi_test_cmd_wrap("ddspi set_enable 0 8 1");

	ct_dd_spi_test_cmd_wrap("ddspi set_enable 0 8 0");

	ret = priv->test->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

CtDdSpiTestthree* ct_dd_spi_testthree_new(void) 
{
    CtDdSpiTestthree *self = k_object_new_with_private(CT_TYPE_DD_SPI_TESTTHREE, sizeof(CtDdSpiTestthreePrivate));

    return self;
}
