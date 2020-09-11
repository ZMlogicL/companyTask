/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-02
 *@author            :陈倩
 *@brief             :r2ytest1
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *3、
 *4、
 *5、
 *@version
 *
 */


#include <stdlib.h>
#include "CheckHeaderMain.h"
#include "milb.h"
#include "chiptop.h"
#if 0
#include "arm.h"
#include "chiptop.h"
#include "exstop.h"
#include "jdsb2r.h"
#include "jdscnr.h"
#include "jdsdisp.h"
#include "jdsela.h"
#include "jdsfpt.h"
#include "jdsiip.h"
#include "jdsimg.h"
#include "jdsjpgdec.h"
#include "jdsjpgenc.h"
#include "jdsltm.h"
#include "jdsmxic.h"
#include "jdspro.h"
#include "jdsr2y.h"
#include "jdsraw.h"
#include "jdsshdr.h"
#include "jdsxch.h"
#include "jmilaum.h"
#include "jmilhdmi.h"
#include "jmlbmh.h"
#include "jsrlot.h"
#include "peripheral.h"
#include "slimbus.h"
#include "sdramc.h"
#include "uart_csio.h"
#include "jdsme.h"
#endif
#include "r2ytest1.h"


struct _R2yTest1Private {

};

K_TYPE_DEFINE_WITH_PRIVATE(R2yTest1, r2y_test1);
#define R2Y_TEST1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), R2yTest1Private, R2Y_TYPE_TEST1))

#define R2yTest1_RS_PRINTF printf
/**
 IMPL
 */
static void r2y_test1_constructor(R2yTest1 *self)
{
//	R2yTest1Private *priv = R2Y_TEST1_GET_PRIVATE(self);
}

static void r2y_test1_destructor(R2yTest1 *self)
{
//	R2yTest1Private *priv = R2Y_TEST1_GET_PRIVATE(self);
}
/**
 PUBLIC
 */
void r2y_test1_r2y_test(R2yTest1 *self)
{
// for PC debug
#if 0
#define IO_R2Y_P1		(*ioR2y2P1)
#define IO_R2Y_P2		(*ioR2y2P2)
#define IO_R2Y_TBL_P1	(*ioR2y2TblP1)
#define IO_R2Y_TBL_P2	(*ioR2y2TblP2)
	volatile struct IoR2y* ioR2y2P1 = (void*)0x28418000;
	volatile struct IoR2y* ioR2y2P2 = (void*)0x28518000;
	volatile struct IoR2ySram* ioR2y2TblP1 = (void*)0x294A0000;
	volatile struct IoR2ySram* ioR2y2TblP2 = (void*)0x295A0000;
#endif
	R2yTest1_RS_PRINTF("R2Y\n");
#if 0
	/* f_r2y */
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cntl.cntl = %lX\n", (kulong)&ioR2yP1.fR2y.cntl.cntl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cntl.r2yflag = %lX\n", (kulong)&ioR2yP1.fR2y.cntl.r2yflag);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cntl.r2yinte = %lX\n", (kulong)&ioR2yP1.fR2y.cntl.r2yinte);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cntl.r2yintf = %lX\n", (kulong)&ioR2yP1.fR2y.cntl.r2yintf);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cntl.fltaen = %lX\n", (kulong)&ioR2yP1.fR2y.cntl.fltaen);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ofg.ofst[0] = %lX\n", (kulong)&ioR2yP1.fR2y.ofg.ofst.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ofg.ofst[1] = %lX\n", (kulong)&ioR2yP1.fR2y.ofg.ofst.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ofg.wbgar[0] = %lX\n", (kulong)&ioR2yP1.fR2y.ofg.wbgar.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ofg.wbgar[1] = %lX\n", (kulong)&ioR2yP1.fR2y.ofg.wbgar.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ofg.WBLV[0] = %lX\n", (kulong)&ioR2yP1.fR2y.ofg.WBLV.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ofg.WBLV[1] = %lX\n", (kulong)&ioR2yP1.fR2y.ofg.WBLV.word[1]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0ctl = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0ctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0k[0] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0k.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0k[1] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0k.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0k[2] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0k.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0k[3] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0k.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0k[4] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0k.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0ybof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0ybof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0ybof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0ybof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0ybga[0] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0ybga.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0ybga[1] = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0ybga.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.cc0ybbd = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.cc0ybbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca0.ccyc = %lX\n", (kulong)&ioR2yP1.fR2y.cca0.ccyc);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcyc[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcyc.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcyc[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcyc.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcyc[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcyc.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcyc[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcyc.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcyc[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcyc.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcb1ab = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcb1ab);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcb1cd = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcb1cd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcb2ab = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcb2ab);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcb2cd = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcb2cd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcb3ab = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcb3ab);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcb3cd = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcb3cd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcb4ab = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcb4ab);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcb4cd = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcb4cd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcid1 = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcid1);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcid2 = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcid2);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcid3 = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcid3);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcid4 = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcid4);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_4[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKA_4[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcka.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKB_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckb.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKC_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckc.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKD_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckd.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKE_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcke.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKF_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckf.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKG_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckg.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKH_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckh.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKI_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcki.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKJ_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckj.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKK_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckk.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck0.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_0[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck0.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_0[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck0.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck1.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_1[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck1.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_1[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck1.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck2.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_2[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck2.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_2[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck2.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck3.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck3.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck3.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck4.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[3] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck4.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCKL_3[4] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mckl.mck4.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLA_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcla.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLB_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclb.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLC_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclc.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLD_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcld.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLE_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcle.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLF_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclf.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLG_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclg.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLH_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclh.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLI_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcli.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLJ_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclj.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLK_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mclk.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_0[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl0.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_0[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl0.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_0[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl0.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_1[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl1.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_1[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl1.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_1[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl1.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_2[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl2.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_2[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl2.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_2[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl2.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_3[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl3.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_3[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl3.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_3[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl3.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_4[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl4.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_4[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl4.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.MCLL_4[2] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcll.mcl4.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcycbalp = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcycbalp);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcycbga[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcycbga.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcycbga[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcycbga.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcycbbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcycbbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcycbbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcycbbd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcbabalp = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcbabalp);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcbabof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcbabof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcbabof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcbabof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcbabga[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcbabga.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcbabga[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcbabga.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcbabbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcbabbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mcc.mcbabbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.mcc.mcbabbd.word[1]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tcof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tcof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tcof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tcof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tctctl = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tctctl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tctsta = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tctsta);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tctb = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tctb);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tchsctl = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tchsctl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tchssta = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tchssta);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tchssiz = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tchssiz);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.btc.tchov = %lX\n", (kulong)&ioR2yP1.fR2y.btc.tchov);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.tc.tcctl = %lX\n", (kulong)&ioR2yP1.fR2y.tc.tcctl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.tc.tcyc = %lX\n", (kulong)&ioR2yP1.fR2y.tc.tcyc);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.tc.tcep[0] = %lX\n", (kulong)&ioR2yP1.fR2y.tc.tcep.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.tc.tcep[1] = %lX\n", (kulong)&ioR2yP1.fR2y.tc.tcep.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.tc.tcclpr = %lX\n", (kulong)&ioR2yP1.fR2y.tc.tcclpr);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.tc.tcclpg = %lX\n", (kulong)&ioR2yP1.fR2y.tc.tcclpg);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.tc.tcclpb = %lX\n", (kulong)&ioR2yP1.fR2y.tc.tcclpb);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.gam.gmctl = %lX\n", (kulong)&ioR2yP1.fR2y.gam.gmctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1ctl = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1ctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1k[0] = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1k.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1k[1] = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1k.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1k[2] = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1k.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1k[3] = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1k.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1k[4] = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1k.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1clpr = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1clpr);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1clpg = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1clpg);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.cca1.cc1clpb = %lX\n", (kulong)&ioR2yP1.fR2y.cca1.cc1clpb);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.yc.yc[0] = %lX\n", (kulong)&ioR2yP1.fR2y.yc.yc.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.yc.yc[1] = %lX\n", (kulong)&ioR2yP1.fR2y.yc.yc.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.yc.yc[2] = %lX\n", (kulong)&ioR2yP1.fR2y.yc.yc.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.yc.yc[3] = %lX\n", (kulong)&ioR2yP1.fR2y.yc.yc.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.yc.yc[4] = %lX\n", (kulong)&ioR2yP1.fR2y.yc.yc.word[4]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.yc.YBLEND = %lX\n", (kulong)&ioR2yP1.fR2y.yc.YBLEND);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ynr.nrctl = %lX\n", (kulong)&ioR2yP1.fR2y.ynr.nrctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ynr.nrof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.ynr.nrof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ynr.nrof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.ynr.nrof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ynr.nrga[0] = %lX\n", (kulong)&ioR2yP1.fR2y.ynr.nrga.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ynr.nrga[1] = %lX\n", (kulong)&ioR2yP1.fR2y.ynr.nrga.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ynr.nrbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.ynr.nrbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ynr.nrbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.ynr.nrbd.word[1]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egsm.egsmctl = %lX\n", (kulong)&ioR2yP1.fR2y.egsm.egsmctl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egsm.egsmtt = %lX\n", (kulong)&ioR2yP1.fR2y.egsm.egsmtt);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwctl = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwhpfk[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwhpfk.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwhpfk[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwhpfk.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcorpof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcorpof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcorpof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcorpof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcorpga = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcorpga);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcorpbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcorpbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcorpbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcorpbd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcormof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcormof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcormof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcormof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcormga = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcormga);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcormbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcormbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwcormbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwcormbd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwsclsup = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwsclsup);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwclppof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwclppof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwclppof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwclppof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwclppga = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwclppga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwclppbd = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwclppbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwclpmof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwclpmof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwclpmof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwclpmof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwclpmga = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwclpmga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eghw.eghwclpmbd = %lX\n", (kulong)&ioR2yP1.fR2y.eghw.eghwclpmbd);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwctl = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwhpfk[0] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwhpfk.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwhpfk[1] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwhpfk.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcorpof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcorpof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcorpof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcorpof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcorpga = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcorpga);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcorpbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcorpbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcorpbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcorpbd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcormof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcormof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcormof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcormof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcormga = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcormga);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcormbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcormbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwcormbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwcormbd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwsclsup = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwsclsup);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwclppof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwclppof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwclppof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwclppof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwclppga = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwclppga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwclppbd = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwclppbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwclpmof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwclpmof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwclpmof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwclpmof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwclpmga = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwclpmga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egmw.egmwclpmbd = %lX\n", (kulong)&ioR2yP1.fR2y.egmw.egmwclpmbd);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.EGLWCTL = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.EGLWCTL);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwhpfk[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwhpfk.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwhpfk[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwhpfk.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwhpfk[2] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwhpfk.word[2]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcorpof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcorpof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcorpof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcorpof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcorpga = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcorpga );

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcorpbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcorpbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcorpbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcorpbd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcormof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcormof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcormof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcormof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcormga = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcormga);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcormbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcormbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwcormbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwcormbd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwsclsup = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwsclsup);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwclppof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwclppof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwclppof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwclppof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwclppga = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwclppga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwclppbd = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwclppbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwclpmof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwclpmof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwclpmof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwclpmof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwclpmga = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwclpmga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.eglw.eglwclpmbd = %lX\n", (kulong)&ioR2yP1.fR2y.eglw.eglwclpmbd);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egdt.egdtctl = %lX\n", (kulong)&ioR2yP1.fR2y.egdt.egdtctl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egdt.egdthwth = %lX\n", (kulong)&ioR2yP1.fR2y.egdt.egdthwth);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egdt.egdthwk = %lX\n", (kulong)&ioR2yP1.fR2y.egdt.egdthwk);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egdt.egdtmwth = %lX\n", (kulong)&ioR2yP1.fR2y.egdt.egdtmwth);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egdt.egdtmwk = %lX\n", (kulong)&ioR2yP1.fR2y.egdt.egdtmwk);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mapscl.egmpctl = %lX\n", (kulong)&ioR2yP1.fR2y.mapscl.egmpctl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mapscl.egmpsiz = %lX\n", (kulong)&ioR2yP1.fR2y.mapscl.egmpsiz);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mapscl.egmpsizhinv = %lX\n", (kulong)&ioR2yP1.fR2y.mapscl.egmpsizhinv);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mapscl.egmpsizvinv = %lX\n", (kulong)&ioR2yP1.fR2y.mapscl.egmpsizvinv);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mapscl.egmpstaph = %lX\n", (kulong)&ioR2yP1.fR2y.mapscl.egmpstaph);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.mapscl.egmpstapv = %lX\n", (kulong)&ioR2yP1.fR2y.mapscl.egmpstapv);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpctl = %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpbd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpalpof = %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpalpof);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpalpga[0]= %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpalpga.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpalpga[1]= %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpalpga.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpbtaof = %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpbtaof);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpbtaga[0]= %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpbtaga.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpbtaga[1]= %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpbtaga.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcmp.egcmpclp = %lX\n", (kulong)&ioR2yP1.fR2y.egcmp.egcmpclp);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.crv.crvaf = %lX\n", (kulong)&ioR2yP1.fR2y.crv.crvaf);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.crv.crvbf = %lX\n", (kulong)&ioR2yP1.fR2y.crv.crvbf);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvctl = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvctl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvasclof = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvasclof);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvasclga = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvasclga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvasclbd = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvasclbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvasclcp = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvasclcp);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egyasclga = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egyasclga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egyasclbd = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egyasclbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egyasclclp = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egyasclclp);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvbsclof = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvbsclof);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvbsclga = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvbsclga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvbsclbd = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvbsclbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvbsclcp = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvbsclcp);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egybsclga = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egybsclga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egybsclbd = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egybsclbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egybsclclp = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egybsclclp);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.egcrv.egcrvclp = %lX\n", (kulong)&ioR2yP1.fR2y.egcrv.egcrvclp);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvctl = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvctl);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvaalpof = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvaalpof);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvaalpga = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvaalpga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvaalpbd = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvaalpbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvaalpcp = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvaalpcp);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybyaalpga = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybyaalpga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybyaalpbd = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybyaalpbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybyaalpclp = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybyaalpclp);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvbalpof = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvbalpof);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvbalpga = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvbalpga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvbalpbd = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvbalpbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybcrvbalpcp = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybcrvbalpcp);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybybalpga = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybybalpga);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybybalpbd = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybybalpbd);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.ybcrv.ybybalpclp = %lX\n", (kulong)&ioR2yP1.fR2y.ybcrv.ybybalpclp);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfctl = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfk[0] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfk.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfk[1] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfk.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfk[2] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfk.word[2]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfk[3] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfk.word[3]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfk[4] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfk.word[4]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfof = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfof);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfga[0] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfga.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfga[1] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfga.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfbd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfbd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.clpf.clpfbd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.clpf.clpfbd.word[1]);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.csyctl = %lX\n", (kulong)&ioR2yP1.fR2y.csp.csyctl);

	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.csyof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.csp.csyof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.csyof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.csp.csyof.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.csyga[0] = %lX\n", (kulong)&ioR2yP1.fR2y.csp.csyga.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.csyga[1] = %lX\n", (kulong)&ioR2yP1.fR2y.csp.csyga.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.csybd[0] = %lX\n", (kulong)&ioR2yP1.fR2y.csp.csybd.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.csybd[1] = %lX\n", (kulong)&ioR2yP1.fR2y.csp.csybd.word[1]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.ycrvfx = %lX\n", (kulong)&ioR2yP1.fR2y.csp.ycrvfx);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.cfix = %lX\n", (kulong)&ioR2yP1.fR2y.csp.cfix);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.ycof[0] = %lX\n", (kulong)&ioR2yP1.fR2y.csp.ycof.word[0]);
	R2yTest1_RS_PRINTF("ioR2yP1.fR2y.csp.ycof[1] = %lX\n", (kulong)&ioR2yP1.fR2y.csp.ycof.word[1]);
#endif
}

R2yTest1 *r2y_test1_new(void)
{
		R2yTest1* self = k_object_new_with_private(R2Y_TYPE_TEST1, sizeof(R2yTest1Private));
		return self;
}
