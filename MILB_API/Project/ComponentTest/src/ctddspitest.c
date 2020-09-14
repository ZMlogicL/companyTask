/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :guguangjian
*@brief               :CtDdSpiTest类
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
// #include "dd_hdmac1.h"
// #include "dd_tmr32.h"
#include "../../DeviceDriver/Peripheral/src/ddhdmac1.h"
#include "../../DeviceDriver/Peripheral/src/ddtmr32.h"
#include "ctddspimain.h"
#include "ctddspitest.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdSpiTest, ct_dd_spi_test);
#define CT_DD_SPI_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdSpiTestPrivate,CT_TYPE_DD_SPI_TEST))

struct _CtDdSpiTestPrivate
{
	kint a;
};

/*
 *DECLS
 */
static void 		ctDdSpiPrintSendReg(kuchar ch);
static void 		ctDdSpiPrintRecvTestReg(kuchar ch);

static void ct_dd_spi_test_constructor(CtDdSpiTest *self) 
{
	self->gctDdSpiResult = D_DDIM_OK;
}

static void ct_dd_spi_test_destructor(CtDdSpiTest *self) 
{

}

/*
 *IMPL
 */
static void ctDdSpiPrintSendReg( kuchar ch )
{
	Ddim_Print(("EN.bit.__ENABLEREQ = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_EN.word        = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
	Ddim_Print(("TXDATA             = 0x%04lX\n", IO_SPI[ch].TXDATA));
}

static void ctDdSpiPrintRecvTestReg( kuchar ch )
{
	Ddim_Print(("EN.bit.__ENABLEREQ      = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_EN.word             = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
	Ddim_Print(("FIFO_WMK.bit.RXWMARKSET = %d\n", IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET));
	Ddim_Print(("TX_DWR.word             = 0x%04lX\n", IO_SPI[ch].TX_DWR.word));
}

/*
 *PUBLIC
 */
void ct_dd_spi_test_cmd_wrap(kchar* cmd)
{
	kint32	argc = 0;
	kchar*	argv[32];
	kchar	arg[32][32];
	kint32	pos = 0;
	kint32	len = 0;
	kint32	max = strlen(cmd);
	kint32	i;

	// printf("CMD> %s\n", cmd);

	// Clear arg buffer
	for(i = 0; i < 32; i++){
		argv[i] = arg[i];
		memset(argv[i], 0, 32);
	}

	// Set arg buffer
	for(i = 0; i < max; i++){
		if(cmd[i] == ' '){
			if(len){
				memcpy(argv[argc], &cmd[pos], len);
				argc++;
				len = 0;
			}
			pos = i + 1;
		}
		else if(i == max - 1){
			memcpy(argv[argc], &cmd[pos], len + 1);
			argc++;
			len = 0;
			pos = i + 1;
		}else{
			len++;
		}
	}

	// Execute command
	CtDdSpiMain *spimain = ct_dd_spi_main_new();
	ct_dd_spi_main(spimain,argc, argv);
	k_object_unref(spimain);
}


void ct_dd_spi_test_set_result(CtDdSpiTest *self,kint32 newResult)
{
	self->gctDdSpiResult = newResult;
}

kuchar ct_dd_spi_test_get_async(CtDdSpiTest *self)
{
	return self->gctDdSpiAsync;
}

/* set send normal1 */
void ct_dd_spi_test_pc_set_send_data_1(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 1;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 4;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 1 ms 0 0 lsb 4 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 1 1 data 0xA5");
	ret = self->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* set send normal2 */
void ct_dd_spi_test_pc_set_send_data_2(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 16;

	//                                                                   +---dma_to:0-16777215
	//                                                                   |+---ssout:0-3
	//                                                      +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3          | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3         | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16  | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |           | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 32 data 0xA5A5");
	ret = self->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* set recv normal1 */
void ct_dd_spi_test_pc_set_recv_data_1(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 4;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 0 0 lsb 4 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 0 1 data 0xA5");
	ret = self->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* set recv normal2 */
void ct_dd_spi_test_pc_set_recv_data_2(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 1;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 16;

	//                                                                   +---dma_to:0-16777215
	//                                                                   |+---ssout:0-3
	//                                                      +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3          | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3         | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16  | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |           | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 1 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 1 32 data 0xA5A5");
	ret = self->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send normal (8bit 1byte async) */
void ct_dd_spi_test_pc_start_send_1(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 8;

	//                                                                   +---dma_to:0-16777215
	//                                                                   | +---ssout:0-3
	//                                                     +-dly:0-255   | | +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1  | | | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk   | | | | +---cb
	//                                  | |     +-bit:4-16 | | |  +-rxwmk| | | | | +---cb_ss
	//                                  | |     |          | | |  |      | | | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 0 0 lsb 8 12000000 0 0 64 64 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 0 1 data 0xA5");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 0");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send normal (8bit 1byte sync) */
void ct_dd_spi_test_pc_start_send_2(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 8;

	//                                                                   +---dma_to:0-16777215
	//                                                                   | +---ssout:0-3
	//                                                     +-dly:0-255   | | +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1  | | | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk   | | | | +---cb
	//                                  | |     +-bit:4-16 | | |  +-rxwmk| | | | | +---cb_ss
	//                                  | |     |          | | |  |      | | | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 0 0 lsb 8 12000000 0 0 64 64 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 0 1 data 0xA5");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 0");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send normal (8bit 32byte sync) */
void ct_dd_spi_test_pc_start_send_3(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 32 data 0xA5");

	// gDD_CT_SPI_Send_Buf8[31] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 31);
	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send error (D_DD_SPI_FORCE_STOP) (8bit 32byte sync) (TXFULL=1)*/
void ct_dd_spi_test_pc_start_send_4(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 32 data 0xA5");

	// gDD_CT_SPI_Send_Buf8[31] = 0xB6;
	ct_dd_spi_set_sendbuf8(0xB6, 31);

	IO_SPI[ch].ST.bit.TXFULL = 1;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_send 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send normal (16bit 1byte async) */
void ct_dd_spi_test_pc_start_send_5(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 16;

	//                                                                   +---dma_to:0-16777215
	//                                                                   | +---ssout:0-3
	//                                                     +-dly:0-255   | | +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1  | | | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk   | | | | +---cb
	//                                  | |     +-bit:4-16 | | |  +-rxwmk| | | | | +---cb_ss
	//                                  | |     |          | | |  |      | | | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 0 0 lsb 16 12000000 0 0 64 64 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 0 1 data 0xA5A5");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 0");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send normal (16bit 1byte sync) */
void ct_dd_spi_test_pc_start_send_6(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 16;

	//                                                                   +---dma_to:0-16777215
	//                                                                   | +---ssout:0-3
	//                                                     +-dly:0-255   | | +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1  | | | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk   | | | | +---cb
	//                                  | |     +-bit:4-16 | | |  +-rxwmk| | | | | +---cb_ss
	//                                  | |     |          | | |  |      | | | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 0 0 lsb 16 12000000 0 0 64 64 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 0 1 data 0xA5A5");

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 0");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send normal (16bit 32byte sync) */
void ct_dd_spi_test_pc_start_send_7(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 32 data 0xA5A5");

	// gDD_CT_SPI_Send_Buf16[31] = 0xB6B6;
	ct_dd_spi_set_sendbuf16(0xB6B6, 31);

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;

	ct_dd_spi_test_cmd_wrap("ddspi start_send 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send error (D_DD_SPI_FORCE_STOP) (16bit 32byte sync) (TXFULL=1)*/
void ct_dd_spi_test_pc_start_send_8(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 32 data 0xA5A5");

	// gDD_CT_SPI_Send_Buf16[31] = 0xB6B6;
	ct_dd_spi_set_sendbuf16(0xB6B6, 31);

	IO_SPI[ch].ST.bit.TXFULL = 1;
	IO_SPI[ch].ST.bit.TXEMPTY = 1;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_send 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start send error (D_DD_SPI_FORCE_STOP) (16bit 32byte sync) (TXEMPTY=0) */
void ct_dd_spi_test_pc_start_send_9(CtDdSpiTest *self)
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_send 2 32 data 0xA5A5");

	// gDD_CT_SPI_Send_Buf16[31] = 0xB6B6;
	ct_dd_spi_set_sendbuf16(0xB6B6, 31);

	IO_SPI[ch].ST.bit.TXFULL = 0;
	IO_SPI[ch].ST.bit.TXEMPTY = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_send 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintSendReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv normal (8bit 1byte async) */
void ct_dd_spi_test_pc_start_recv_1(CtDdSpiTest * self)
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 1;
	self->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv normal (8bit 18byte async) */
void ct_dd_spi_test_pc_start_recv_2(CtDdSpiTest * self)
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 18;
	self->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv normal (8bit 1byte sync) */
void ct_dd_spi_test_pc_start_recv_3( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 1;
	self->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv normal (8bit 18byte sync) */
void ct_dd_spi_test_pc_start_recv_4( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 18;
	self->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv error (D_DD_SPI_FORCE_STOP) (RXEMPTY=1) (8bit 18byte sync) */
void ct_dd_spi_test_pc_start_recv_5( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 18;
	self->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 1;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv error (D_DD_SPI_RECV_OVERRUN_ERROR) (8bit 18byte sync) */
void ct_dd_spi_test_pc_start_recv_6( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 18;
	self->gctDdSpiBitLen = 8;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 8 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0x00A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 1;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv normal (16bit 1byte sync) */
void ct_dd_spi_test_pc_start_recv_7( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 1;
	self->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 1 data");

	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv normal (16bit 18byte sync) */
void ct_dd_spi_test_pc_start_recv_8( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 18;
	self->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv error (D_DD_SPI_FORCE_STOP) (RXEMPTY=1) (16bit 18byte sync) */
void ct_dd_spi_test_pc_start_recv_9( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 18;
	self->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 1;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv error (D_DD_SPI_RECV_OVERRUN_ERROR) (16bit 18byte sync) */
void ct_dd_spi_test_pc_start_recv_10( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 18;
	self->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 1;

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* start recv error (D_DD_SPI_FORCE_STOP) (RXEMPTY=0) (16bit 18byte sync)*/
void ct_dd_spi_test_pc_start_recv_11( CtDdSpiTest * self )
{
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	self->gctDdSpiTransNum = 18;
	self->gctDdSpiBitLen = 16;

	//                                                                  +---dma_to:0-16777215
	//                                                                  |+---ssout:0-3
	//                                                     +-dly:0-255  || +---sspol:0-1
	//                                  +-mode:0-3         | +-Inhi:0-1 || | +---contTrans:0-2
	//                                  | +-sig:0-3        | | +-txwmk  || | | +---cb
	//                                  | |     +-bit:4-16 | | | +-rxwmk|| | | | +---cb_ss
	//                                  | |     |          | | | |      || | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 2 ms 0 0 lsb 16 12000000 0 0 8 8 cpu 0 1 1 2 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi set_recv 2 18 data");

	IO_SPI[ch].RXDATA = 0xA5A5;
	IO_SPI[ch].RXFIFO.bit.RX_FIFO_LEVEL = 0;
	IO_SPI[ch].ST.bit.RXEMPTY = 0;
	IO_SPI[ch].ST.bit.RXOVERFLOW = 0;

	ct_dd_spi_test_cmd_wrap("ddspi stop 2");

	ct_dd_spi_test_cmd_wrap("ddspi start_recv 2");

	ret = self->gctDdSpiResult;

	ctDdSpiPrintRecvTestReg( ch );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

CtDdSpiTest* ct_dd_spi_test_new(void) 
{
    CtDdSpiTest *self = k_object_new_with_private(CT_TYPE_DD_SPI_TEST, sizeof(CtDdSpiTestPrivate));
    return self;
}
