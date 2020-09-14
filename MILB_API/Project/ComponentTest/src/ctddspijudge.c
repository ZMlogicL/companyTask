/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdSpiJudge类
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
#include "../../DeviceDriver/Peripheral/src/ddspi.h"
#include "../../DeviceDriver/Peripheral/src/ddspicolabo.h"
#include "../../DeviceDriver/Peripheral/src/ddspidrive.h"
#include "../../DeviceDriver/Peripheral/src/ddspicalculate.h"
#include "../../DeviceDriver/Peripheral/src/ddhdmac1.h"
#include "../../DeviceDriver/Peripheral/src/ddtmr32.h"
#include "ctddspimain.h"
#include "ctddspitest.h"
#include "ctddspitestone.h"
#include "ctddspitesttwo.h"
#include "ctddspitestthree.h"
#include "ctddspijudge.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdSpiJudge, ct_dd_spi_judge);
#define CT_DD_SPI_JUDGE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdSpiJudgePrivate,CT_TYPE_DD_SPI_JUDGE))

#define CtDdSpiJudge_SPI_DMA_CH_1						(0)
#define CtDdSpiJudge_SPI_DMA_CH_2						(1)
#define CtDdSpiJudge_SPI_TIMER_CH							(7)
#define CtDdSpiJudge_SPI_TIMER_MODE_DMA			(0)
#define CtDdSpiJudge_SPI_TIMER_MODE_STOP		(1)

struct _CtDdSpiJudgePrivate
{
	CtDdSpiTest *test;
};

static CtDdSpiJudgeSpiTransType S_GCT_DD_SPI_TRANS_TYPE = CtDdSpiJudge_SPI_TRNAS_TYPE_SEND;
static kuchar S_GDD_CT_SPI_CH = 0;
static kuchar S_GDD_CT_SPI_TIMER_NUM = 0;
static kint32 S_GDD_CT_SPI_TIMER_MODE = 0;

/*
 *DECLS
 */
static void 			ctDdSpiTimer_cb(void);
static void 			ctDdSpiSetTimer(kuchar spi_ch, kulong msec, kuchar num, kint32 mode);
static void 			ctDdSpiPcTestOpen1(CtDdSpiJudge *self);
static void 			ctDdSpiPcTestOpen2(CtDdSpiJudge *self);
static void 			ctDdSpiPcTestOpen3(CtDdSpiJudge *self);
static void 			ctDdSpiPcTestOpen4(CtDdSpiJudge *self);
static void 			ctDdSpiPcTestClose1(CtDdSpiJudge *self);
static void 			ctDdSpiPcTestClose2(CtDdSpiJudge *self);
static void 			ctDdSpiPcTestCtrl1(CtDdSpiJudge *self);
static void 			ctDdSpiPcTestCtrl2(CtDdSpiJudge *self);
static void 			ctDdSpiPrintCtrlReg(kuchar ch);
static void 			ctDdSpiJudgeSetTest(CtDdSpiJudge *self,CtDdSpiTest *test);

static void ct_dd_spi_judge_constructor(CtDdSpiJudge *self) 
{
	self->priv = CT_DD_SPI_JUDGE_GET_PRIVATE(self);
    self->ret = D_DDIM_OK;
    self->tmout = D_DDIM_USER_SEM_WAIT_POL;
    self->clkDiv = 0;
}

static void ct_dd_spi_judge_destructor(CtDdSpiJudge *self) 
{
	self->endstr = NULL;
}

/*
 *IMPL
 */
static void ctDdSpiTimer_cb(void)
{
	if( S_GDD_CT_SPI_TIMER_MODE == CtDdSpiJudge_SPI_TIMER_MODE_DMA )
		IO_HDMAC1.DMAC[CtDdSpiJudge_SPI_DMA_CH_1].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
		dd_hdmac1_int_handler(dd_hdmac1_get(), CtDdSpiJudge_SPI_DMA_CH_1 );

		if( S_GCT_DD_SPI_TRANS_TYPE == CtDdSpiJudge_SPI_TRNAS_TYPE_FULL ){
			IO_HDMAC1.DMAC[CtDdSpiJudge_SPI_DMA_CH_2 ].DMACB.bit.SS = D_DD_HDMAC1_SS_NORMAL_END;
			dd_hdmac1_int_handler(dd_hdmac1_get(), CtDdSpiJudge_SPI_DMA_CH_2 );
		}
	else if( S_GDD_CT_SPI_TIMER_MODE == CtDdSpiJudge_SPI_TIMER_MODE_STOP ){
		Ddim_Print(("---Stop SPI(%d)---\n", S_GDD_CT_SPI_CH));
		dd_spi_drive_stop(dd_spi_drive_get(), S_GDD_CT_SPI_CH);
	}

	S_GDD_CT_SPI_TIMER_NUM--;
	if( S_GDD_CT_SPI_TIMER_NUM > 0 ){
		ctDdSpiSetTimer( S_GDD_CT_SPI_CH, 100, S_GDD_CT_SPI_TIMER_NUM, S_GDD_CT_SPI_TIMER_MODE );
	}
}

static void ctDdSpiSetTimer(kuchar spi_ch, kulong msec, kuchar num, kint32 mode)
{
	kint32 ret;

	S_GDD_CT_SPI_CH	= spi_ch;
	S_GDD_CT_SPI_TIMER_MODE	= mode;
	S_GDD_CT_SPI_TIMER_NUM = num;

	ret = dd_tmr32_open(dd_tmr32_get(),CtDdSpiJudge_SPI_TIMER_CH, D_DDIM_USER_SEM_WAIT_POL);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("timer open error : ret=%d \n", ret));
		return;
	}

	ret = dd_tmr32_set_timer(dd_tmr32_get(),CtDdSpiJudge_SPI_TIMER_CH, msec * 1000, ctDdSpiTimer_cb);
	if(ret != D_DDIM_OK) {
		dd_tmr32_stop(dd_tmr32_get(),CtDdSpiJudge_SPI_TIMER_CH);
		dd_tmr32_close(dd_tmr32_get(),CtDdSpiJudge_SPI_TIMER_CH);
		Ddim_Print(("timer set error : ret=%d \n", ret));
		return;
	}

	ret = dd_tmr32_start(dd_tmr32_get(),CtDdSpiJudge_SPI_TIMER_CH);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("timer start error : ret=%d \n", ret));
		return;
	}
}

/* open normal (D_DDIM_USER_SEM_WAIT_POL) */
static void ctDdSpiPcTestOpen1(CtDdSpiJudge *self)
{
	CtDdSpiJudgePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi open 0 0");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi close 0");

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* open normal (D_DDIM_USER_SEM_WAIT_FEVR) */
static void ctDdSpiPcTestOpen2(CtDdSpiJudge *self)
{
	CtDdSpiJudgePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 1;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi open 1 -1");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi close 1");

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* open error (D_DDIM_USER_SEM_WAIT_POL->D_DD_SPI_SEM_TIMEOUT) */
static void ctDdSpiPcTestOpen3(CtDdSpiJudge *self)
{
	CtDdSpiJudgePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi open 2 0");
	ct_dd_spi_test_cmd_wrap("ddspi open 2 0");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi close 2");

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* open error (1msec->D_DD_SPI_SEM_TIMEOUT) */
static void ctDdSpiPcTestOpen4(CtDdSpiJudge *self)
{
	CtDdSpiJudgePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi open 0 0");
	ct_dd_spi_test_cmd_wrap("ddspi open 0 1");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi close 0");

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* close normal */
static void ctDdSpiPcTestClose1(CtDdSpiJudge *self)
{
	CtDdSpiJudgePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 1;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi open 1 0");
	ct_dd_spi_test_cmd_wrap("ddspi close 1");
	ret = priv->test->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* close error */
static void ctDdSpiPcTestClose2(CtDdSpiJudge *self)
{
	CtDdSpiJudgePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 2;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	ct_dd_spi_test_cmd_wrap("ddspi close 2");
	ret = priv->test->gctDdSpiResult;

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* ctrl normal1 */
static void ctDdSpiPcTestCtrl1(CtDdSpiJudge *self)
{
	CtDdSpiJudgePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	//                                                                    +---dma_to:0-16777215
	//                                                                    | +---ssout:0-3
	//                                                      +-dly:0-255   | | +---sspol:0-1
	//                                  +-mode:0-3          | +-Inhi:0-1  | | | +---contTrans:0-2
	//                                  | +-sig:0-3         | | +-txwmk   | | | | +---cb
	//                                  | |     +-bit:4-16  | | |  +-rxwmk| | | | | +---cb_ss
	//                                  | |     |           | | |  |      | | | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 sl 0 0 lsb 4 108000000 0 0 64 32 cpu 1 0 0 0 0 0");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi get_ctrl 0");

	ctDdSpiPrintCtrlReg( 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

/* ctrl normal2 */
static void ctDdSpiPcTestCtrl2(CtDdSpiJudge *self)
{
	CtDdSpiJudgePrivate *priv = self->priv;
	kint32 ret;
	kuchar ch = 0;

	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	//                                                                    +---dma_to:0-16777215
	//                                                                    |        +---ssout:0-3
	//                                                      +-dly:0-255   |        | +---sspol:0-1
	//                                  +-mode:0-3          | +-Inhi:0-1  |        | | +---contTrans:0-2
	//                                  | +-sig:0-3         | | +-txwmk   |        | | | +---cb
	//                                  | |     +-bit:4-16  | | |  +-rxwmk|        | | | | +---cb_ss
	//                                  | |     |           | | |  |      |        | | | | |
	ct_dd_spi_test_cmd_wrap("ddspi ctrl 0 ms 3 3 msb 16 421875 255 1 32 16 dma 16777215 3 1 2 1 1");
	ret = priv->test->gctDdSpiResult;
	ct_dd_spi_test_cmd_wrap("ddspi get_ctrl 0");

	ctDdSpiPrintCtrlReg( 0 );

	Ddim_Print(("<%s> End. result = 0x%08X, ch=%d\n", __FUNCTION__, ret, ch));
}

static void ctDdSpiPrintCtrlReg(kuchar ch)
{
	Ddim_Print(("CTRL.bit.MASTER             = %d\n", IO_SPI[ch].CTRL.bit.MASTER));
	Ddim_Print(("CTRL.bit.CPOL               = %d\n", IO_SPI[ch].CTRL.bit.CPOL));
	Ddim_Print(("CTRL.bit.CPHA               = %d\n", IO_SPI[ch].CTRL.bit.CPHA));
	Ddim_Print(("EN.bit.__EXTENSEL           = %d\n", IO_SPI[ch].EN.bit.__EXTENSEL));
	Ddim_Print(("CTRL.bit.MSB1ST             = %d\n", IO_SPI[ch].CTRL.bit.MSB1ST));
	Ddim_Print(("AUX_CTRL.bit.BITSIZE        = %d\n", IO_SPI[ch].AUX_CTRL.bit.BITSIZE));
	Ddim_Print(("CTRL.bit.DIVENABLE          = %d\n", IO_SPI[ch].CTRL.bit.DIVENABLE));
	Ddim_Print(("DIV.bit.DIVISOR             = %d\n", IO_SPI[ch].DIV.bit.DIVISOR));
	Ddim_Print(("CTRL.bit.MWAITEN            = %d\n", IO_SPI[ch].CTRL.bit.MWAITEN));
	Ddim_Print(("MS_DLY.bit.MWAIT            = %d\n", IO_SPI[ch].MS_DLY.bit.MWAIT));
	Ddim_Print(("AUX_CTRL.bit.INHIBITDIN     = %d\n", IO_SPI[ch].AUX_CTRL.bit.INHIBITDIN));
	Ddim_Print(("FIFO_WMK.bit.TXWMARKSET     = %d\n", IO_SPI[ch].FIFO_WMK.bit.TXWMARKSET));
	Ddim_Print(("FIFO_WMK.bit.RXWMARKSET     = %d\n", IO_SPI[ch].FIFO_WMK.bit.RXWMARKSET));
	Ddim_Print(("CTRL.bit.DMA                = %d\n", IO_SPI[ch].CTRL.bit.DMA));
	Ddim_Print(("DMA_TO.bit.TIMEOUT          = %d\n", IO_SPI[ch].DMA_TO.bit.TIMEOUT));
	Ddim_Print(("CTRL.bit.CONTXFER           = %d\n", IO_SPI[ch].CTRL.bit.CONTXFER));
	Ddim_Print(("AUX_CTRL.bit.CONTXFEREXTEND = %d\n", IO_SPI[ch].AUX_CTRL.bit.CONTXFEREXTEND));
	Ddim_Print(("SLV_SEL.bit.SSOUT0          = %d\n", IO_SPI[ch].SLV_SEL.bit.SSOUT0));
	Ddim_Print(("SLV_SEL.bit.SSOUT1          = %d\n", IO_SPI[ch].SLV_SEL.bit.SSOUT1));
	Ddim_Print(("SLV_SEL.bit.SSOUT2          = %d\n", IO_SPI[ch].SLV_SEL.bit.SSOUT2));
	Ddim_Print(("SLV_SEL.bit.SSOUT3          = %d\n", IO_SPI[ch].SLV_SEL.bit.SSOUT3));
	Ddim_Print(("SLV_POL.bit.SSPOL0          = %d\n", IO_SPI[ch].SLV_POL.bit.SSPOL0));
	Ddim_Print(("SLV_POL.bit.SSPOL1          = %d\n", IO_SPI[ch].SLV_POL.bit.SSPOL1));
	Ddim_Print(("SLV_POL.bit.SSPOL2          = %d\n", IO_SPI[ch].SLV_POL.bit.SSPOL2));
	Ddim_Print(("SLV_POL.bit.SSPOL3          = %d\n", IO_SPI[ch].SLV_POL.bit.SSPOL3));
	Ddim_Print(("AUX_CTRL.bit.SPIMODE        = %d\n", IO_SPI[ch].AUX_CTRL.bit.SPIMODE));
	Ddim_Print(("AUX_CTRL.bit.XFERFORMAT     = %d\n", IO_SPI[ch].AUX_CTRL.bit.XFERFORMAT));
	Ddim_Print(("EN.bit.__ENABLEREQ          = %d\n", IO_SPI[ch].EN.bit.__ENABLEREQ));
	Ddim_Print(("INT_CLR.word                = 0x%08lX\n", IO_SPI[ch].INT_CLR.word));
	Ddim_Print(("INT_EN..word                = 0x%08lX\n", IO_SPI[ch].INT_EN.word));
}

static void ctDdSpiJudgeSetTest(CtDdSpiJudge *self,CtDdSpiTest *test)
{
	CtDdSpiJudgePrivate *priv = CT_DD_SPI_JUDGE_GET_PRIVATE(self);

	priv->test = test;
}

/*
 *PUBLIC
 */
CtDdSpiJudgeSpiTransType ct_dd_spi_judge_get_trans_type(void)
{
	return S_GCT_DD_SPI_TRANS_TYPE;
}

void ct_dd_spi_judge_set_trans_type(CtDdSpiJudgeSpiTransType newtype)
{
	S_GCT_DD_SPI_TRANS_TYPE = newtype;
}

void ct_dd_spi_judge_main(CtDdSpiJudge *self, CtDdSpiTest * test,kint argc, kchar** argv)
{  
	CtDdSpiTestone *testone = ct_dd_spi_testone_new();
	CtDdSpiTesttwo *testtwo = ct_dd_spi_testtwo_new();
	CtDdSpiTestthree *testthree = ct_dd_spi_testthree_new();

	ctDdSpiJudgeSetTest(self,test);
	ct_dd_spi_testone_set_test(testone,test);
	ct_dd_spi_testtwo_set_test(testtwo,test);
	ct_dd_spi_testthree_set_test(testthree,test);

    if ( strcmp( argv[1], "set_enable" ) == 0 ){
		self->ch = atoi( argv[2] );
		self->enableSig = atoi( argv[3] );
		self->enable = atoi( argv[4] );

		self->ret = dd_spi_drive_set_spi_enable(dd_spi_drive_get(), self->ch, self->enableSig, self->enable );

		Ddim_Print(("dd_spi_drive_set_spi_enable End. ret=0x%08X, EN.word=0x%02lX\n", self->ret, IO_SPI[self->ch].EN.word));
	}
	else if (strcmp(argv[1], "test") == 0){
		switch (atoi(argv[2])) {
			case 1:
				switch (atoi(argv[3])) {
					case 1:
						ctDdSpiPcTestOpen1(self);
						break;
					case 2:
						ctDdSpiPcTestOpen2(self);
						break;
					case 3:
						ctDdSpiPcTestOpen3(self);
						break;
					case 4:
						ctDdSpiPcTestOpen4(self);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 2:
				switch (atoi(argv[3])) {
					case 1:
						ctDdSpiPcTestClose1(self);
						break;
					case 2:
						ctDdSpiPcTestClose2(self);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 3:
				switch (atoi(argv[3])) {
					case 1:
						ctDdSpiPcTestCtrl1(self);
						break;
					case 2:
						ctDdSpiPcTestCtrl2(self);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 4:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_test_pc_set_send_data_1(test);
						break;
					case 2:
						ct_dd_spi_test_pc_set_send_data_2(test);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 5:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_test_pc_set_recv_data_1(test);
						break;
					case 2:
						ct_dd_spi_test_pc_set_recv_data_2(test);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 6:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_test_pc_start_send_1(test);
						break;
					case 2:
						ct_dd_spi_test_pc_start_send_2(test);
						break;
					case 3:
						ct_dd_spi_test_pc_start_send_3(test);
						break;
					case 4:
						ct_dd_spi_test_pc_start_send_4(test);
						break;
					case 5:
						ct_dd_spi_test_pc_start_send_5(test);
						break;
					case 6:
						ct_dd_spi_test_pc_start_send_6(test);
						break;
					case 7:
						ct_dd_spi_test_pc_start_send_7(test);
						break;
					case 8:
						ct_dd_spi_test_pc_start_send_8(test);
						break;
					case 9:
						ct_dd_spi_test_pc_start_send_9(test);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 7:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_test_pc_start_recv_1(test);
						break;
					case 2:
						ct_dd_spi_test_pc_start_recv_2(test);
						break;
					case 3:
						ct_dd_spi_test_pc_start_recv_3(test);
						break;
					case 4:
						ct_dd_spi_test_pc_start_recv_4(test);
						break;
					case 5:
						ct_dd_spi_test_pc_start_recv_5(test);
						break;
					case 6:
						ct_dd_spi_test_pc_start_recv_6(test);
						break;
					case 7:
						ct_dd_spi_test_pc_start_recv_7(test);
						break;
					case 8:
						ct_dd_spi_test_pc_start_recv_8(test);
						break;
					case 9:
						ct_dd_spi_test_pc_start_recv_9(test);
						break;
					case 10:
						ct_dd_spi_test_pc_start_recv_10(test);
						break;
					case 11:
						ct_dd_spi_test_pc_start_recv_11(test);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 8:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testone_pc_start_full_1(testone);
						break;
					case 2:
						ct_dd_spi_testone_pc_start_full_2(testone);
						break;
					case 3:
						ct_dd_spi_testone_pc_start_full_3(testone);
						break;
					case 4:
						ct_dd_spi_testone_pc_start_full_4(testone);
						break;
					case 5:
						ct_dd_spi_testone_pc_start_full_5(testone);
						break;
					case 6:
						ct_dd_spi_testone_pc_start_full_6(testone);
						break;
					case 7:
						ct_dd_spi_testone_pc_start_full_7(testone);
						break;
					case 8:
						ct_dd_spi_testone_pc_start_full_8(testone);
						break;
					case 9:
						ct_dd_spi_testone_pc_start_full_9(testone);
						break;
					case 10:
						ct_dd_spi_testone_pc_start_full_10(testone);
						break;
					case 11:
						ct_dd_spi_testone_pc_start_full_11(testone);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 9:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testone_pc_stop_1(testone);
						break;
					case 2:
						ct_dd_spi_testone_pc_stop_2(testone);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 10:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testone_pc_setget_ss_1(testone);
						break;
					case 2:
						ct_dd_spi_testone_pc_setget_ss_2(testone);
						break;
					case 3:
						ct_dd_spi_testone_pc_setget_ss_3(testone);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 11:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testone_pc_setget_clkdiv_1(testone);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 12:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testone_pc_handler_1(testone);
						break;
					case 2:
						ct_dd_spi_testone_pc_handler_2(testone);
						break;
					case 3:
						ct_dd_spi_testone_pc_handler_3(testone);
						break;
					case 4:
						ct_dd_spi_testtwo_pc_handler_4(testtwo);
						break;
					case 5:
						ct_dd_spi_testtwo_pc_handler_5(testtwo);
						break;
					case 6:
						ct_dd_spi_testtwo_pc_handler_6(testtwo);
						break;
					case 7:
						ct_dd_spi_testtwo_pc_handler_7(testtwo);
						break;
					case 8:
						ct_dd_spi_testtwo_pc_handler_8(testtwo);
						break;
					case 9:
						ct_dd_spi_testtwo_pc_handler_9(testtwo);
						break;
					case 10:
						ct_dd_spi_testtwo_pc_handler_10(testtwo);
						break;
					case 11:
						ct_dd_spi_testtwo_pc_handler_11(testtwo);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 13:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testtwo_pc_calc_1(testtwo);
						break;
					case 2:
						ct_dd_spi_testtwo_pc_calc_2(testtwo);
						break;
					case 3:
						ct_dd_spi_testtwo_pc_calc_3(testtwo);
						break;
					case 4:
						ct_dd_spi_testtwo_pc_calc_4(testtwo);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 14:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testtwo_pc_start_send_dma_1(testtwo);
						break;
					case 2:
						ct_dd_spi_testtwo_pc_start_send_dma_2(testtwo);
						break;
					case 3:
						ct_dd_spi_testtwo_pc_start_send_dma_3(testtwo);
						break;
					case 4:
						ct_dd_spi_testtwo_pc_start_send_dma_4(testtwo);
						break;
					case 5:
						ct_dd_spi_testtwo_pc_start_send_dma_5(testtwo);
						break;
					case 6:
						ct_dd_spi_testtwo_pc_start_send_dma_6(testtwo);
						break;
					case 7:
						ct_dd_spi_testtwo_pc_start_send_dma_7(testtwo);
						break;
					case 8:
						ct_dd_spi_testtwo_pc_start_send_dma_8(testtwo);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 15:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testthree_pc_start_recv_dma_1(testthree);
						break;
					case 2:
						ct_dd_spi_testthree_pc_start_recv_dma_2(testthree);
						break;
					case 3:
						ct_dd_spi_testthree_pc_start_recv_dma_3(testthree);
						break;
					case 4:
						ct_dd_spi_testthree_pc_start_recv_dma_4(testthree);
						break;
					case 5:
						ct_dd_spi_testthree_pc_start_recv_dma_5(testthree);
						break;
					case 6:
						ct_dd_spi_testthree_pc_start_recv_dma_6(testthree);
						break;
					case 7:
						ct_dd_spi_testthree_pc_start_recv_dma_7(testthree);
						break;
					case 8:
						ct_dd_spi_testthree_pc_start_recv_dma_8(testthree);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 16:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testthree_pc_start_full_dma_1(testthree);
						break;
					case 2:
						ct_dd_spi_testthree_pc_start_full_dma_2(testthree);
						break;
					case 3:
						ct_dd_spi_testthree_pc_start_full_dma_3(testthree);
						break;
					case 4:
						ct_dd_spi_testthree_pc_start_full_dma_4(testthree);
						break;
					case 5:
						ct_dd_spi_testthree_pc_start_full_dma_5(testthree);
						break;
					case 6:
						ct_dd_spi_testthree_pc_start_full_dma_6(testthree);
						break;
					case 7:
						ct_dd_spi_testthree_pc_start_full_dma_7(testthree);
						break;
					case 8:
						ct_dd_spi_testthree_pc_start_full_dma_8(testthree);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			case 17:
				switch (atoi(argv[3])) {
					case 1:
						ct_dd_spi_testthree_pc_set_enable_1(testthree);
						break;
					default :
						Ddim_Print(("ddspi : ERROR test number\n"));
						break;
				}
				break;
			default :
				Ddim_Print(("ddspi : ERROR test number\n"));
				break;
		}
	}
	else if (strcmp(argv[1], "err") == 0){
		kuchar *recvbuf8 = ct_dd_spi_return_recvbuf8();
		kuchar  *sendbuf8 = ct_dd_spi_return_sendbuf8();

		self->ret = dd_spi_drive_open(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX, self->tmout);

		Ddim_Print(("dd_spi_drive_open(): CH number max error. ret=%X\n", self->ret));

		self->ret = dd_spi_drive_open(dd_spi_drive_get(), 0, -2);
		Ddim_Print(("dd_spi_drive_open(): tmout value error. ret=%X\n", self->ret));


		self->ret = dd_spi_drive_close(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX);
		Ddim_Print(("dd_spi_drive_close(): CH number max error. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_ctrl(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX, &(self->spiCtrl));
		Ddim_Print(("dd_spi_drive_ctrl(): CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_drive_ctrl(dd_spi_drive_get(), 0, NULL);
		Ddim_Print(("dd_spi_drive_ctrl(): spiCtrl is NULL. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_get_ctrl(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX, &(self->spiCtrl));
		Ddim_Print(("dd_spi_drive_get_ctrl(): CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_drive_get_ctrl(dd_spi_drive_get(), 0, NULL);
		Ddim_Print(("dd_spi_drive_get_ctrl(): spiCtrl is NULL. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_set_send_data(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX, sendbuf8, 1);
		Ddim_Print(("dd_spi_drive_set_send_data(): CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_drive_set_send_data(dd_spi_drive_get(), 0, NULL, 1);
		Ddim_Print(("dd_spi_drive_set_send_data(): send_addr is NULL. ret=%X\n", self->ret ));

		self->ret = dd_spi_drive_set_send_data(dd_spi_drive_get(), 0, sendbuf8, 0);
		Ddim_Print(("dd_spi_drive_set_send_data(): num is 0. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_start_send(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX);
		Ddim_Print(("dd_spi_drive_start_send(): CH number max error. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_set_recv_data(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX, recvbuf8, 1);
		Ddim_Print(("dd_spi_drive_set_recv_data(): CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_drive_set_recv_data( 0, NULL, 1 );
		Ddim_Print(("dd_spi_drive_set_recv_data(): recv_addr is NULL. ret=%X\n", self->ret ));

		self->ret = dd_spi_drive_set_recv_data(dd_spi_drive_get(), 0, recvbuf8, 0);
		Ddim_Print(("dd_spi_drive_set_recv_data(): num is 0. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_start_recv(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX);
		Ddim_Print(("dd_spi_drive_start_recv(): CH number max error. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_start_full_duplex(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX );
		Ddim_Print(("dd_spi_drive_start_full_duplex(): CH number max error. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_stop(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX);
		Ddim_Print(("dd_spi_drive_stop(): CH number max error. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_set_slave_select(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX, &(self->ssInfo) );
		Ddim_Print(("dd_spi_drive_set_slave_select(): CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_drive_set_slave_select(dd_spi_drive_get(), 0, NULL );
		Ddim_Print(("dd_spi_drive_set_slave_select(): ssInfo is NULL. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_get_slave_select(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX, &(self->ssInfo) );
		Ddim_Print(("dd_spi_drive_get_slave_select(): CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_drive_get_slave_select(dd_spi_drive_get(), 0, NULL );
		Ddim_Print(("dd_spi_drive_get_slave_select(): ssInfo is NULL. ret=%X\n", self->ret ));


		self->ret = dd_spi_calculate_set_clock_divisor(dd_spi_calculate_get(), CtDdSpiJudge_SPI_CH_MAX, self->clkDiv );
		Ddim_Print(("dd_spi_calculate_set_clock_divisor(): CH number max error. ret=%X\n", self->ret ));


		self->ret = dd_spi_calculate_get_clock_divisor(dd_spi_calculate_get(), CtDdSpiJudge_SPI_CH_MAX, &(self->clkDiv) );
		Ddim_Print(("dd_spi_calculate_get_clock_divisor(): CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_calculate_get_clock_divisor(dd_spi_calculate_get(), 0, NULL );
		Ddim_Print(("dd_spi_calculate_get_clock_divisor(): clkDiv is NULL. ret=%X\n", self->ret ));


		self->ret = dd_spi_drive_set_spi_enable(dd_spi_drive_get(), CtDdSpiJudge_SPI_CH_MAX, DdSpiDriveBranch_E_DD_SPI_ENABLE_SIG_CPU, TRUE );
		Ddim_Print(("dd_spi_drive_set_spi_enable(dd_spi_drive_get(),): CH number max error. ret=%X\n", self->ret ));

		dd_spi_int_handler(CtDdSpiJudge_SPI_CH_MAX);
		Ddim_Print(("dd_spi_int_handler(): CH number error.\n"));


		self->ret = dd_spi_calculate_clock_divisor(dd_spi_calculate_get(), 1, NULL);
		Ddim_Print(("dd_spi_calculate_clock_divisor(): clkDiv is NULL. ret=%X\n", self->ret ));


		self->ret = dd_spi_colabo_start_send_dma(dd_spi_colabo_get(), CtDdSpiJudge_SPI_CH_MAX, 5 );
		Ddim_Print(("dd_spi_colabo_start_send_dma(): SPI CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_colabo_start_send_dma(dd_spi_colabo_get(), 0, D_DD_HDMAC1_CH_NUM_MAX );
		Ddim_Print(("dd_spi_colabo_start_send_dma(): DMA CH number max error. ret=%X\n", self->ret ));


		self->ret = dd_spi_colabo_start_recv_dma(dd_spi_colabo_get(), CtDdSpiJudge_SPI_CH_MAX, 5 );
		Ddim_Print(("dd_spi_colabo_start_recv_dma(): SPI CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_colabo_start_recv_dma(dd_spi_colabo_get(), 0, D_DD_HDMAC1_CH_NUM_MAX  );
		Ddim_Print(("dd_spi_colabo_start_recv_dma(): DMA CH number max error. ret=%X\n", self->ret ));


		self->ret = dd_spi_colabo_start_full_duplex_dma(dd_spi_colabo_get(), CtDdSpiJudge_SPI_CH_MAX, 0, 1 );
		Ddim_Print(("Dd_SPI_Start_Full_DMA(): SPI CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_colabo_start_full_duplex_dma(dd_spi_colabo_get(), 0, D_DD_HDMAC1_CH_NUM_MAX, 7 );
		Ddim_Print(("Dd_SPI_Start_Full_DMA(): DMA CH number max error. ret=%X\n", self->ret ));

		self->ret = dd_spi_colabo_start_full_duplex_dma(dd_spi_colabo_get(), 0, 7, D_DD_HDMAC1_CH_NUM_MAX );
		Ddim_Print(("Dd_SPI_Start_Full_DMA(): DMA CH number max error. ret=%X\n", self->ret ));
	}else{
		Ddim_Print(("please check 1st parameter!!\n"));
	}

	test->gctDdSpiResult = self->ret;

	k_object_unref(testone);
	k_object_unref(testtwo);
	k_object_unref(testthree);
}

CtDdSpiJudge* ct_dd_spi_judge_new(void) 
{
    CtDdSpiJudge *self = k_object_new_with_private(CT_TYPE_DD_SPI_JUDGE, sizeof(CtDdSpiJudgePrivate));

    return self;
}
