/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :陈倩
*@brief             :r2ytest3
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
#include "r2ytest3.h"


struct  _R2yTest3Private
{

};


K_TYPE_DEFINE_WITH_PRIVATE(R2yTest3, r2y_test3);
#define R2Y_TEST3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), R2yTest3Private, R2Y_TYPE_TEST3))

#define R2yTest3_RS_PRINTF printf
/**
 IMPL
*/
static void r2y_test3_constructor(R2yTest3 *self)
{
//	R2yTest3Private *priv = R2Y_TEST3_GET_PRIVATE(self);
}

static void r2y_test3_destructor(R2yTest3 *self)
{
//	R2yTest3Private *priv = R2Y_TEST3_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
void r2y_test3_r2y_test( R2yTest3 *self )
{
// for PC debug
#if 0
#define IO_R2Y_P2		(*ioR2y2P2)
#define ioR2yTblP1	(*ioR2y2TblP1)
#define IO_R2Y_TBL_P2	(*ioR2y2TblP2)
	volatile struct IoR2y* ioR2y2P1 = (void*)0x28418000;
	volatile struct IoR2y* ioR2y2P2 = (void*)0x28518000;
	volatile struct IoR2ySram* ioR2y2TblP1 = (void*)0x294A0000;
	volatile struct IoR2ySram* ioR2y2TblP2 = (void*)0x295A0000;
#endif
	R2yTest3_RS_PRINTF("R2Y\n");
#if 0
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl0.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl0.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl0.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl1.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl1.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl1.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl2.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl2.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl2.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl3.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl3.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl3.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLE_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcle.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl0.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl0.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl0.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl1.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl1.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl1.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl2.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl2.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl2.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl3.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl3.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl3.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLF_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclf.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl0.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl0.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl0.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl1.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl1.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl1.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl2.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl2.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl2.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl3.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl3.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl3.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLG_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclg.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl0.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl0.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl0.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl1.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl1.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl1.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl2.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl2.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl2.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl3.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl3.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl3.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLH_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclh.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl0.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl0.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl0.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl1.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl1.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl1.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl2.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl2.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl2.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl3.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl3.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl3.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLI_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcli.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl0.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl0.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl0.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl1.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl1.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl1.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl2.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl2.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl2.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl3.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl3.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl3.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLJ_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclj.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl0.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl0.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl0.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl1.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl1.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl1.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl2.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl2.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl2.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl3.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl3.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl3.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLK_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclk.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl0.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl0.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl0.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl1.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl1.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl1.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl2.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl2.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl2.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl3.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl3.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl3.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl4.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl4.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLL_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcll.mcl4.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcycbalp = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcycbalp);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcycbga[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcycbga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcycbga[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcycbga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcycbbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcycbbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcycbbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcycbbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcbabalp = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcbabalp);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcbabof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcbabof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcbabof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcbabof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcbabga[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcbabga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcbabga[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcbabga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcbabbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcbabbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mcc.mcbabbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcbabbd.word[1]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tcof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tcof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tcof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tcof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tctctl = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tctctl);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tctsta = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tctsta);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tctb = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tctb);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tchsctl = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tchsctl);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tchssta = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tchssta);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tchssiz = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tchssiz);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.btc.tchov = %lX\n", (kulong)&ioR2yP2.fR2y.btc.tchov);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.tc.tcctl = %lX\n", (kulong)&ioR2yP2.fR2y.tc.tcctl);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.tc.tcyc = %lX\n", (kulong)&ioR2yP2.fR2y.tc.tcyc);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.tc.tcep[0] = %lX\n", (kulong)&ioR2yP2.fR2y.tc.tcep.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.tc.tcep[1] = %lX\n", (kulong)&ioR2yP2.fR2y.tc.tcep.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.tc.tcclpr = %lX\n", (kulong)&ioR2yP2.fR2y.tc.tcclpr);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.tc.tcclpg = %lX\n", (kulong)&ioR2yP2.fR2y.tc.tcclpg);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.tc.tcclpb = %lX\n", (kulong)&ioR2yP2.fR2y.tc.tcclpb);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.gam.gmctl = %lX\n", (kulong)&ioR2yP2.fR2y.gam.gmctl);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1ctl = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1ctl);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1k[0] = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1k.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1k[1] = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1k.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1k[2] = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1k.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1k[3] = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1k.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1k[4] = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1k.word[4]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1clpr = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1clpr);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1clpg = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1clpg);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.cca1.cc1clpb = %lX\n", (kulong)&ioR2yP2.fR2y.cca1.cc1clpb);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.yc.yc[0] = %lX\n", (kulong)&ioR2yP2.fR2y.yc.yc.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.yc.yc[1] = %lX\n", (kulong)&ioR2yP2.fR2y.yc.yc.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.yc.yc[2] = %lX\n", (kulong)&ioR2yP2.fR2y.yc.yc.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.yc.yc[3] = %lX\n", (kulong)&ioR2yP2.fR2y.yc.yc.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.yc.yc[4] = %lX\n", (kulong)&ioR2yP2.fR2y.yc.yc.word[4]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.yc.YBLEND = %lX\n", (kulong)&ioR2yP2.fR2y.yc.YBLEND );

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ynr.nrctl = %lX\n", (kulong)&ioR2yP2.fR2y.ynr.nrctl);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ynr.nrof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.ynr.nrof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ynr.nrof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.ynr.nrof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ynr.nrga[0] = %lX\n", (kulong)&ioR2yP2.fR2y.ynr.nrga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ynr.nrga[1] = %lX\n", (kulong)&ioR2yP2.fR2y.ynr.nrga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ynr.nrbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.ynr.nrbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ynr.nrbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.ynr.nrbd.word[1]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egsm.egsmctl = %lX\n", (kulong)&ioR2yP2.fR2y.egsm.egsmctl);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egsm.egsmtt = %lX\n", (kulong)&ioR2yP2.fR2y.egsm.egsmtt);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwctl = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwctl);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwhpfk[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwhpfk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwhpfk[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwhpfk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcorpof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcorpof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcorpof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcorpof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcorpga = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcorpga);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcorpbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcorpbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcorpbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcorpbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcormof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcormof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcormof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcormof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcormga = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcormga);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcormbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcormbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwcormbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwcormbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwsclsup = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwsclsup);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwclppof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwclppof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwclppof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwclppof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwclppga = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwclppga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwclppbd = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwclppbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwclpmof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwclpmof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwclpmof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwclpmof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwclpmga = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwclpmga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eghw.eghwclpmbd = %lX\n", (kulong)&ioR2yP2.fR2y.eghw.eghwclpmbd);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwctl = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwctl);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwhpfk[0] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwhpfk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwhpfk[1] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwhpfk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcorpof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcorpof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcorpof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcorpof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcorpga = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcorpga);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcorpbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcorpbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcorpbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcorpbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcormof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcormof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcormof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcormof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcormga = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcormga);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcormbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcormbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwcormbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwcormbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwsclsup = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwsclsup);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwclppof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwclppof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwclppof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwclppof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwclppga = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwclppga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwclppbd = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwclppbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwclpmof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwclpmof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwclpmof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwclpmof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwclpmga = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwclpmga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egmw.egmwclpmbd = %lX\n", (kulong)&ioR2yP2.fR2y.egmw.egmwclpmbd);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.EGLWCTL = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.EGLWCTL);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwhpfk[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwhpfk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwhpfk[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwhpfk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwhpfk[2] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwhpfk.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcorpof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcorpof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcorpof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcorpof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcorpga = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcorpga);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcorpbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcorpbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcorpbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcorpbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcormof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcormof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcormof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcormof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcormga = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcormga);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcormbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcormbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwcormbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwcormbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwsclsup = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwsclsup);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwclppof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwclppof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwclppof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwclppof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwclppga = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwclppga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwclppbd = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwclppbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwclpmof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwclpmof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwclpmof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwclpmof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwclpmga = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwclpmga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.eglw.eglwclpmbd = %lX\n", (kulong)&ioR2yP2.fR2y.eglw.eglwclpmbd);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egdt.egdtctl = %lX\n", (kulong)&ioR2yP2.fR2y.egdt.egdtctl);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egdt.egdthwth = %lX\n", (kulong)&ioR2yP2.fR2y.egdt.egdthwth);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egdt.egdthwk = %lX\n", (kulong)&ioR2yP2.fR2y.egdt.egdthwk);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egdt.egdtmwth = %lX\n", (kulong)&ioR2yP2.fR2y.egdt.egdtmwth);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egdt.egdtmwk = %lX\n", (kulong)&ioR2yP2.fR2y.egdt.egdtmwk);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mapscl.egmpctl = %lX\n", (kulong)&ioR2yP2.fR2y.mapscl.egmpctl);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mapscl.egmpsiz = %lX\n", (kulong)&ioR2yP2.fR2y.mapscl.egmpsiz);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mapscl.egmpsizhinv = %lX\n", (kulong)&ioR2yP2.fR2y.mapscl.egmpsizhinv);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mapscl.egmpsizvinv = %lX\n", (kulong)&ioR2yP2.fR2y.mapscl.egmpsizvinv);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mapscl.egmpstaph = %lX\n", (kulong)&ioR2yP2.fR2y.mapscl.egmpstaph);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.mapscl.egmpstapv = %lX\n", (kulong)&ioR2yP2.fR2y.mapscl.egmpstapv);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpctl = %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpctl);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpalpof = %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpalpof);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpalpga[0]= %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpalpga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpalpga[1]= %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpalpga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpbtaof = %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpbtaof);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpbtaga[0]= %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpbtaga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpbtaga[1]= %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpbtaga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcmp.egcmpclp = %lX\n", (kulong)&ioR2yP2.fR2y.egcmp.egcmpclp);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.crv.crvaf = %lX\n", (kulong)&ioR2yP2.fR2y.crv.crvaf);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.crv.crvbf = %lX\n", (kulong)&ioR2yP2.fR2y.crv.crvbf);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvctl = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvctl);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvasclof = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvasclof);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvasclga = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvasclga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvasclbd = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvasclbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvasclcp = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvasclcp);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egyasclga = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egyasclga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egyasclbd = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egyasclbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egyasclclp = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egyasclclp);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvbsclof = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvbsclof);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvbsclga = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvbsclga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvbsclbd = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvbsclbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvbsclcp = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvbsclcp);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egybsclga = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egybsclga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egybsclbd = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egybsclbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egybsclclp = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egybsclclp);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.egcrv.egcrvclp = %lX\n", (kulong)&ioR2yP2.fR2y.egcrv.egcrvclp);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvctl = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvctl);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvaalpof = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvaalpof);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvaalpga = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvaalpga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvaalpbd = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvaalpbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvaalpcp = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvaalpcp);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybyaalpga = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybyaalpga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybyaalpbd = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybyaalpbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybyaalpclp = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybyaalpclp);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvbalpof = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvbalpof);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvbalpga = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvbalpga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvbalpbd = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvbalpbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybcrvbalpcp = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybcrvbalpcp);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybybalpga = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybybalpga);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybybalpbd = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybybalpbd);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.ybcrv.ybybalpclp = %lX\n", (kulong)&ioR2yP2.fR2y.ybcrv.ybybalpclp);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfctl = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfctl);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfk[0] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfk[1] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfk[2] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfk.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfk[3] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfk.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfk[4] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfk.word[4]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfof = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfof);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfga[0] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfga[1] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfbd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.clpf.clpfbd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.clpf.clpfbd.word[1]);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.csyctl = %lX\n", (kulong)&ioR2yP2.fR2y.csp.csyctl);

	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.csyof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.csp.csyof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.csyof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.csp.csyof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.csyga[0] = %lX\n", (kulong)&ioR2yP2.fR2y.csp.csyga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.csyga[1] = %lX\n", (kulong)&ioR2yP2.fR2y.csp.csyga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.csybd[0] = %lX\n", (kulong)&ioR2yP2.fR2y.csp.csybd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.csybd[1] = %lX\n", (kulong)&ioR2yP2.fR2y.csp.csybd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.ycrvfx = %lX\n", (kulong)&ioR2yP2.fR2y.csp.ycrvfx);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.cfix = %lX\n", (kulong)&ioR2yP2.fR2y.csp.cfix);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.ycof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.csp.ycof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.fR2y.csp.ycof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.csp.ycof.word[1]);

	/* jdsr2y */
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyraxctl = %lX\n", (kulong)&ioR2yP2.yych.yyraxctl);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw0axctl = %lX\n", (kulong)&ioR2yP2.yych.yyw0axctl);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yywaaxctl = %lX\n", (kulong)&ioR2yP2.yych.yywaaxctl);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw1axctl = %lX\n", (kulong)&ioR2yP2.yych.yyw1axctl);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw2axctl = %lX\n", (kulong)&ioR2yP2.yych.yyw2axctl);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyraxsts = %lX\n", (kulong)&ioR2yP2.yych.yyraxsts);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw0axsts = %lX\n", (kulong)&ioR2yP2.yych.yyw0axsts);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yywaaxsts = %lX\n", (kulong)&ioR2yP2.yych.yywaaxsts);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw1axsts = %lX\n", (kulong)&ioR2yP2.yych.yyw1axsts);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw2axsts = %lX\n", (kulong)&ioR2yP2.yych.yyw2axsts);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyraxmd = %lX\n", (kulong)&ioR2yP2.yych.yyraxmd);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw0axmd = %lX\n", (kulong)&ioR2yP2.yych.yyw0axmd);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yywaaxmd = %lX\n", (kulong)&ioR2yP2.yych.yywaaxmd);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw1axmd = %lX\n", (kulong)&ioR2yP2.yych.yyw1axmd);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw2axmd = %lX\n", (kulong)&ioR2yP2.yych.yyw2axmd);

	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyrreqmsk[0] = %lX\n", (kulong)&ioR2yP2.yych.yyrreqmsk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyrreqmsk[1] = %lX\n", (kulong)&ioR2yP2.yych.yyrreqmsk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw0reqmsk[0] = %lX\n", (kulong)&ioR2yP2.yych.yyw0reqmsk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw0reqmsk[1] = %lX\n", (kulong)&ioR2yP2.yych.yyw0reqmsk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yywareqmsk = %lX\n", (kulong)&ioR2yP2.yych.yywareqmsk);

	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw1reqmsk[0] = %lX\n", (kulong)&ioR2yP2.yych.yyw1reqmsk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw1reqmsk[1] = %lX\n", (kulong)&ioR2yP2.yych.yyw1reqmsk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yych.yyw2reqmsk = %lX\n", (kulong)&ioR2yP2.yych.yyw2reqmsk);

	R2yTest3_RS_PRINTF("ioR2yP2.r2yCmn.yyinte = %lX\n", (kulong)&ioR2yP2.r2yCmn.yyinte);
	R2yTest3_RS_PRINTF("ioR2yP2.r2yCmn.yyintf = %lX\n", (kulong)&ioR2yP2.r2yCmn.yyintf);
	R2yTest3_RS_PRINTF("ioR2yP2.r2yCmn.lintlv[0] = %lX\n", (kulong)&ioR2yP2.r2yCmn.lintlv.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.r2yCmn.lintlv[1] = %lX\n", (kulong)&ioR2yP2.r2yCmn.lintlv.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.r2yCmn.lintsel = %lX\n", (kulong)&ioR2yP2.r2yCmn.lintsel);
	R2yTest3_RS_PRINTF("ioR2yP2.r2yCmn.r2ymode = %lX\n", (kulong)&ioR2yP2.r2yCmn.r2ymode);
	R2yTest3_RS_PRINTF("ioR2yP2.r2yCmn.ramaen = %lX\n", (kulong)&ioR2yP2.r2yCmn.ramaen);

	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyrtrg = %lX\n", (kulong)&ioR2yP2.yyr.yyrtrg);
	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyrctl = %lX\n", (kulong)&ioR2yP2.yyr.yyrctl);
	R2yTest3_RS_PRINTF("ioR2yP2.yyr.dinctl = %lX\n", (kulong)&ioR2yP2.yyr.dinctl);

	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyra[0] = %lX\n", (kulong)&ioR2yP2.yyr.yyra.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyra[1] = %lX\n", (kulong)&ioR2yP2.yyr.yyra.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyra[2] = %lX\n", (kulong)&ioR2yP2.yyr.yyra.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyrofs = %lX\n", (kulong)&ioR2yP2.yyr.yyrofs);
	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyrdef = %lX\n", (kulong)&ioR2yP2.yyr.yyrdef);
	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyrhsiz = %lX\n", (kulong)&ioR2yP2.yyr.yyrhsiz);
	R2yTest3_RS_PRINTF("ioR2yP2.yyr.yyrvsiz = %lX\n", (kulong)&ioR2yP2.yyr.yyrvsiz);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywtrg = %lX\n", (kulong)&ioR2yP2.yyw.yywtrg);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywctl = %lX\n", (kulong)&ioR2yP2.yyw.yywctl);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywbank = %lX\n", (kulong)&ioR2yP2.yyw.yywbank);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywkpp = %lX\n", (kulong)&ioR2yP2.yyw.yywkpp);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw0md = %lX\n", (kulong)&ioR2yP2.yyw.yyw0md);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw1md = %lX\n", (kulong)&ioR2yP2.yyw.yyw1md);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw2md = %lX\n", (kulong)&ioR2yP2.yyw.yyw2md);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.hstmd = %lX\n", (kulong)&ioR2yP2.yyw.hstmd);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.hsth = %lX\n", (kulong)&ioR2yP2.yyw.hsth);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.hstv = %lX\n", (kulong)&ioR2yP2.yyw.hstv);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw0a[0][0] = %lX\n", (kulong)&ioR2yP2.yyw.yyw0a.word[0][0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw0a[0][1] = %lX\n", (kulong)&ioR2yP2.yyw.yyw0a.word[0][1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw0a[2][2] = %lX\n", (kulong)&ioR2yP2.yyw.yyw0a.word[2][2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw0a[2][3] = %lX\n", (kulong)&ioR2yP2.yyw.yyw0a.word[2][3]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.V[0] = %lX\n", (kulong)&ioR2yP2.yyw.V.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.V[1] = %lX\n", (kulong)&ioR2yP2.yyw.V.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw0ofsx[0] = %lX\n", (kulong)&ioR2yP2.yyw.yyw0ofsx.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw0ofsx[1] = %lX\n", (kulong)&ioR2yP2.yyw.yyw0ofsx.word[1]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz0hsta = %lX\n", (kulong)&ioR2yP2.yyw.rsz0hsta);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz0hpit = %lX\n", (kulong)&ioR2yP2.yyw.rsz0hpit);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz0vsta = %lX\n", (kulong)&ioR2yP2.yyw.rsz0vsta);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz0vpit = %lX\n", (kulong)&ioR2yP2.yyw.rsz0vpit);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.pcemd = %lX\n", (kulong)&ioR2yP2.yyw.pcemd);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.pcexy = %lX\n", (kulong)&ioR2yP2.yyw.pcexy);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.pcec = %lX\n", (kulong)&ioR2yP2.yyw.pcec);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.pceh = %lX\n", (kulong)&ioR2yP2.yyw.pceh);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trm0h = %lX\n", (kulong)&ioR2yP2.yyw.trm0h);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trm0v = %lX\n", (kulong)&ioR2yP2.yyw.trm0v);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trmbh = %lX\n", (kulong)&ioR2yP2.yyw.trmbh);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trmbv = %lX\n", (kulong)&ioR2yP2.yyw.trmbv);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trmch = %lX\n", (kulong)&ioR2yP2.yyw.trmch);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trmcv = %lX\n", (kulong)&ioR2yP2.yyw.trmcv);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw0ltt = %lX\n", (kulong)&ioR2yP2.yyw.yyw0ltt);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywaa[0][0] = %lX\n", (kulong)&ioR2yP2.yyw.yywaa.word[0][0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywaa[0][1] = %lX\n", (kulong)&ioR2yP2.yyw.yywaa.word[0][1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywaa[1][2] = %lX\n", (kulong)&ioR2yP2.yyw.yywaa.word[1][2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywaa[1][3] = %lX\n", (kulong)&ioR2yP2.yyw.yywaa.word[1][3]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywadef = %lX\n", (kulong)&ioR2yP2.yyw.yywadef);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywaofsx[0] = %lX\n", (kulong)&ioR2yP2.yyw.yywaofsx.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yywaofsx[1] = %lX\n", (kulong)&ioR2yP2.yyw.yywaofsx.word[1]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw1a[0][0] = %lX\n", (kulong)&ioR2yP2.yyw.yyw1a.word[0][0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw1a[0][1] = %lX\n", (kulong)&ioR2yP2.yyw.yyw1a.word[0][1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw1a[2][2] = %lX\n", (kulong)&ioR2yP2.yyw.yyw1a.word[2][2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw1a[2][3] = %lX\n", (kulong)&ioR2yP2.yyw.yyw1a.word[2][3]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw1def[0] = %lX\n", (kulong)&ioR2yP2.yyw.yyw1def.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw1def[1] = %lX\n", (kulong)&ioR2yP2.yyw.yyw1def.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz1hsta = %lX\n", (kulong)&ioR2yP2.yyw.rsz1hsta);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz1hpit = %lX\n", (kulong)&ioR2yP2.yyw.rsz1hpit);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz1vsta = %lX\n", (kulong)&ioR2yP2.yyw.rsz1vsta);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz1vpit = %lX\n", (kulong)&ioR2yP2.yyw.rsz1vpit);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trm1h = %lX\n", (kulong)&ioR2yP2.yyw.trm1h);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trm1v = %lX\n", (kulong)&ioR2yP2.yyw.trm1v);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw2a[0] = %lX\n", (kulong)&ioR2yP2.yyw.yyw2a.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw2a[3] = %lX\n", (kulong)&ioR2yP2.yyw.yyw2a.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.yyw2def = %lX\n", (kulong)&ioR2yP2.yyw.yyw2def);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz2hsta = %lX\n", (kulong)&ioR2yP2.yyw.rsz2hsta);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz2hpit = %lX\n", (kulong)&ioR2yP2.yyw.rsz2hpit);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz2vsta = %lX\n", (kulong)&ioR2yP2.yyw.rsz2vsta);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.rsz2vpit = %lX\n", (kulong)&ioR2yP2.yyw.rsz2vpit);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trm2h = %lX\n", (kulong)&ioR2yP2.yyw.trm2h);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.trm2v = %lX\n", (kulong)&ioR2yP2.yyw.trm2v);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0ctl = %lX\n", (kulong)&ioR2yP2.yyw.ee0ctl);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0hpfk[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0hpfk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0hpfk[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0hpfk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0nrlv = %lX\n", (kulong)&ioR2yP2.yyw.ee0nrlv);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0corpof = %lX\n", (kulong)&ioR2yP2.yyw.ee0corpof);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0corpga = %lX\n", (kulong)&ioR2yP2.yyw.ee0corpga);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0corpbd = %lX\n", (kulong)&ioR2yP2.yyw.ee0corpbd);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0cormof = %lX\n", (kulong)&ioR2yP2.yyw.ee0cormof);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0cormga = %lX\n", (kulong)&ioR2yP2.yyw.ee0cormga);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0cormbd = %lX\n", (kulong)&ioR2yP2.yyw.ee0cormbd);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclsup = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclsup);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpof[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpof.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpga[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpga[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpga[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpga.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpga[3] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpga.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpga[4] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpga.word[4]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpbd[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpbd[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclpbd[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclpbd.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmof[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmof.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmga[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmga[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmga[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmga.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmga[3] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmga.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmga[4] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmga.word[4]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmbd[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmbd[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0sclmbd[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee0sclmbd.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonpof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonpof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonpof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonpof.word[1]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonpga[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonpga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonpga[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonpga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonpga[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonpga.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonpbd = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonpbd);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonmof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonmof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonmof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonmof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonmga[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonmga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonmga[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonmga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonmga[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonmga.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0tonmbd = %lX\n", (kulong)&ioR2yP2.yyw.ee0tonmbd);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0clppof = %lX\n", (kulong)&ioR2yP2.yyw.ee0clppof);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0clppga = %lX\n", (kulong)&ioR2yP2.yyw.ee0clppga);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0clppbd = %lX\n", (kulong)&ioR2yP2.yyw.ee0clppbd);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0clpmof = %lX\n", (kulong)&ioR2yP2.yyw.ee0clpmof);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0clpmga = %lX\n", (kulong)&ioR2yP2.yyw.ee0clpmga);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee0clpmbd = %lX\n", (kulong)&ioR2yP2.yyw.ee0clpmbd);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1ctl = %lX\n", (kulong)&ioR2yP2.yyw.ee1ctl);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1hpfk[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1hpfk.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1hpfk[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1hpfk.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1nrlv = %lX\n", (kulong)&ioR2yP2.yyw.ee1nrlv );

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1corpof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1corpof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1corpof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1corpof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1corpga = %lX\n", (kulong)&ioR2yP2.yyw.ee1corpga);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1corpbd[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1corpbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1corpbd[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1corpbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1cormof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1cormof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1cormof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1cormof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1cormga = %lX\n", (kulong)&ioR2yP2.yyw.ee1cormga);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1cormbd[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1cormbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1cormbd[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1cormbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclsup = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclsup);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpof[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpof.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpga[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpga[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpga[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpga.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpga[3] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpga.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpga[4] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpga.word[4]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpbd[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpbd[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpbd[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpbd.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpbd[3] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpbd.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclpbd[4] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclpbd.word[4]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmof[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmof.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmga[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmga[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmga[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmga.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmga[3] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmga.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmga[4] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmga.word[4]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmbd[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmbd[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmbd[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmbd.word[2]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmbd[3] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmbd.word[3]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1sclmbd[4] = %lX\n", (kulong)&ioR2yP2.yyw.ee1sclmbd.word[4]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonpof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonpof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonpof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonpof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonpof[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonpof.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonpga[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonpga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonpga[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonpga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonpga[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonpga.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonpbd[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonpbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonpbd[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonpbd.word[1]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonmof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonmof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonmof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonmof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonmof[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonmof.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonmga[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonmga.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonmga[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonmga.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonmga[2] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonmga.word[2]);

	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonmbd[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonmbd.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1tonmbd[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1tonmbd.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1clppof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1clppof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1clppof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1clppof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1clppga = %lX\n", (kulong)&ioR2yP2.yyw.ee1clppga);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1clppbd = %lX\n", (kulong)&ioR2yP2.yyw.ee1clppbd);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1clpmof[0] = %lX\n", (kulong)&ioR2yP2.yyw.ee1clpmof.word[0]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1clpmof[1] = %lX\n", (kulong)&ioR2yP2.yyw.ee1clpmof.word[1]);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1clpmga = %lX\n", (kulong)&ioR2yP2.yyw.ee1clpmga);
	R2yTest3_RS_PRINTF("ioR2yP2.yyw.ee1clpmbd = %lX\n", (kulong)&ioR2yP2.yyw.ee1clpmbd);

	/* f_r2y tbl */
	R2yTest3_RS_PRINTF("ioR2yTblP2.tc[0] = %lX\n", (kulong)&ioR2yTblP2.tc.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tc[1] = %lX\n", (kulong)&ioR2yTblP2.tc.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tc[1022] = %lX\n", (kulong)&ioR2yTblP2.tc.hword[1022]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tc[1023] = %lX\n", (kulong)&ioR2yTblP2.tc.hword[1023]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.tctdata[0] = %lX\n", (kulong)&ioR2yTblP2.tctdata.word[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tctdata[1] = %lX\n", (kulong)&ioR2yTblP2.tctdata.word[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tctdata[1198] = %lX\n", (kulong)&ioR2yTblP2.tctdata.word[1198]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tctdata[1199] = %lX\n", (kulong)&ioR2yTblP2.tctdata.word[1199]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsydata[0] = %lX\n", (kulong)&ioR2yTblP2.tchsydata.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsydata[1] = %lX\n", (kulong)&ioR2yTblP2.tchsydata.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsydata[4094] = %lX\n", (kulong)&ioR2yTblP2.tchsydata.hword[4094] );
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsydata[4095] = %lX\n", (kulong)&ioR2yTblP2.tchsydata.hword[4095] );

	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsrdata[0] = %lX\n", (kulong)&ioR2yTblP2.tchsrdata.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsrdata[1] = %lX\n", (kulong)&ioR2yTblP2.tchsrdata.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsrdata[254] = %lX\n", (kulong)&ioR2yTblP2.tchsrdata.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsrdata[255] = %lX\n", (kulong)&ioR2yTblP2.tchsrdata.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsgdata[0] = %lX\n", (kulong)&ioR2yTblP2.tchsgdata.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsgdata[1] = %lX\n", (kulong)&ioR2yTblP2.tchsgdata.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsgdata[254] = %lX\n", (kulong)&ioR2yTblP2.tchsgdata.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsgdata[255] = %lX\n", (kulong)&ioR2yTblP2.tchsgdata.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsbdata[0] = %lX\n", (kulong)&ioR2yTblP2.tchsbdata.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsbdata[1] = %lX\n", (kulong)&ioR2yTblP2.tchsbdata.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsbdata[254] = %lX\n", (kulong)&ioR2yTblP2.tchsbdata.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.tchsbdata[255] = %lX\n", (kulong)&ioR2yTblP2.tchsbdata.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrgbdf[0] = %lX\n", (kulong)&ioR2yTblP2.gmrgbdf.dword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrgbdf[1] = %lX\n", (kulong)&ioR2yTblP2.gmrgbdf.dword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrgbdf[254] = %lX\n", (kulong)&ioR2yTblP2.gmrgbdf.dword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrgbdf[255] = %lX\n", (kulong)&ioR2yTblP2.gmrgbdf.dword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrdf[0] = %lX\n", (kulong)&ioR2yTblP2.gmrdf.dword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrdf[1] = %lX\n", (kulong)&ioR2yTblP2.gmrdf.dword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrdf[254] = %lX\n", (kulong)&ioR2yTblP2.gmrdf.dword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrdf[255] = %lX\n", (kulong)&ioR2yTblP2.gmrdf.dword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmgdf[0] = %lX\n", (kulong)&ioR2yTblP2.gmgdf.dword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmgdf[1] = %lX\n", (kulong)&ioR2yTblP2.gmgdf.dword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmgdf[254] = %lX\n", (kulong)&ioR2yTblP2.gmgdf.dword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmgdf[255] = %lX\n", (kulong)&ioR2yTblP2.gmgdf.dword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmbdf[0] = %lX\n", (kulong)&ioR2yTblP2.gmbdf.dword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmbdf[1] = %lX\n", (kulong)&ioR2yTblP2.gmbdf.dword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmbdf[254] = %lX\n", (kulong)&ioR2yTblP2.gmbdf.dword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmbdf[255] = %lX\n", (kulong)&ioR2yTblP2.gmbdf.dword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmybdf[0] = %lX\n", (kulong)&ioR2yTblP2.gmybdf.dword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmybdf[1] = %lX\n", (kulong)&ioR2yTblP2.gmybdf.dword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmybdf[254] = %lX\n", (kulong)&ioR2yTblP2.gmybdf.dword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmybdf[255] = %lX\n", (kulong)&ioR2yTblP2.gmybdf.dword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrgbfl[0] = %lX\n", (kulong)&ioR2yTblP2.gmrgbfl.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrgbfl[1] = %lX\n", (kulong)&ioR2yTblP2.gmrgbfl.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrgbfl[254] = %lX\n", (kulong)&ioR2yTblP2.gmrgbfl.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrgbfl[255] = %lX\n", (kulong)&ioR2yTblP2.gmrgbfl.hword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrfl[0] = %lX\n", (kulong)&ioR2yTblP2.gmrfl.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrfl[1] = %lX\n", (kulong)&ioR2yTblP2.gmrfl.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrfl[254] = %lX\n", (kulong)&ioR2yTblP2.gmrfl.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmrfl[255] = %lX\n", (kulong)&ioR2yTblP2.gmrfl.hword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmgfl[0] = %lX\n", (kulong)&ioR2yTblP2.gmgfl.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmgfl[1] = %lX\n", (kulong)&ioR2yTblP2.gmgfl.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmgfl[254] = %lX\n", (kulong)&ioR2yTblP2.gmgfl.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmgfl[255] = %lX\n", (kulong)&ioR2yTblP2.gmgfl.hword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmbfl[0] = %lX\n", (kulong)&ioR2yTblP2.gmbfl.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmbfl[1] = %lX\n", (kulong)&ioR2yTblP2.gmbfl.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmbfl[254] = %lX\n", (kulong)&ioR2yTblP2.gmbfl.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmbfl[255] = %lX\n", (kulong)&ioR2yTblP2.gmbfl.hword[255]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmybfl[0] = %lX\n", (kulong)&ioR2yTblP2.gmybfl.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmybfl[1] = %lX\n", (kulong)&ioR2yTblP2.gmybfl.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmybfl[254] = %lX\n", (kulong)&ioR2yTblP2.gmybfl.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.gmybfl[255] = %lX\n", (kulong)&ioR2yTblP2.gmybfl.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.eghwscl[0] = %lX\n", (kulong)&ioR2yTblP2.eghwscl.byte[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eghwscl[1] = %lX\n", (kulong)&ioR2yTblP2.eghwscl.byte[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eghwscl[510] = %lX\n", (kulong)&ioR2yTblP2.eghwscl.byte[510]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eghwscl[511] = %lX\n", (kulong)&ioR2yTblP2.eghwscl.byte[511]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eghwton[0] = %lX\n", (kulong)&ioR2yTblP2.eghwton.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eghwton[1] = %lX\n", (kulong)&ioR2yTblP2.eghwton.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eghwton[254] = %lX\n", (kulong)&ioR2yTblP2.eghwton.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eghwton[255] = %lX\n", (kulong)&ioR2yTblP2.eghwton.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.egmwscl[0] = %lX\n", (kulong)&ioR2yTblP2.egmwscl.byte[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmwscl[1] = %lX\n", (kulong)&ioR2yTblP2.egmwscl.byte[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmwscl[510] = %lX\n", (kulong)&ioR2yTblP2.egmwscl.byte[510]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmwscl[511] = %lX\n", (kulong)&ioR2yTblP2.egmwscl.byte[511]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmwton[0] = %lX\n", (kulong)&ioR2yTblP2.egmwton.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmwton[1] = %lX\n", (kulong)&ioR2yTblP2.egmwton.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmwton[254] = %lX\n", (kulong)&ioR2yTblP2.egmwton.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmwton[255] = %lX\n", (kulong)&ioR2yTblP2.egmwton.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.eglwscl[0] = %lX\n", (kulong)&ioR2yTblP2.eglwscl.byte[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eglwscl[1] = %lX\n", (kulong)&ioR2yTblP2.eglwscl.byte[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eglwscl[510] = %lX\n", (kulong)&ioR2yTblP2.eglwscl.byte[510]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eglwscl[511] = %lX\n", (kulong)&ioR2yTblP2.eglwscl.byte[511]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eglwton[0] = %lX\n", (kulong)&ioR2yTblP2.eglwton.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eglwton[1] = %lX\n", (kulong)&ioR2yTblP2.eglwton.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eglwton[254] = %lX\n", (kulong)&ioR2yTblP2.eglwton.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.eglwton[255] = %lX\n", (kulong)&ioR2yTblP2.eglwton.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.egmpscl[0][0] = %lX\n", (kulong)&ioR2yTblP2.egmpscl.hword[0][0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmpscl[0][1] = %lX\n", (kulong)&ioR2yTblP2.egmpscl.hword[0][1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmpscl[12][15] = %lX\n", (kulong)&ioR2yTblP2.egmpscl.hword[12][15]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.egmpscl[12][16] = %lX\n", (kulong)&ioR2yTblP2.egmpscl.hword[12][16]);

	/* jdsr2y tbl */
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblr[0] = %lX\n", (kulong)&ioR2yTblP2.dkntblr.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblr[1] = %lX\n", (kulong)&ioR2yTblP2.dkntblr.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblr[254] = %lX\n", (kulong)&ioR2yTblP2.dkntblr.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblr[255] = %lX\n", (kulong)&ioR2yTblP2.dkntblr.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblg[0] = %lX\n", (kulong)&ioR2yTblP2.dkntblg.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblg[1] = %lX\n", (kulong)&ioR2yTblP2.dkntblg.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblg[254] = %lX\n", (kulong)&ioR2yTblP2.dkntblg.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblg[255] = %lX\n", (kulong)&ioR2yTblP2.dkntblg.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblb[0] = %lX\n", (kulong)&ioR2yTblP2.dkntblb.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblb[1] = %lX\n", (kulong)&ioR2yTblP2.dkntblb.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblb[254] = %lX\n", (kulong)&ioR2yTblP2.dkntblb.hword[254]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.dkntblb[255] = %lX\n", (kulong)&ioR2yTblP2.dkntblb.hword[255]);

	R2yTest3_RS_PRINTF("ioR2yTblP2.hsty[0] = %lX\n", (kulong)&ioR2yTblP2.hsty.hword[0]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.hsty[1] = %lX\n", (kulong)&ioR2yTblP2.hsty.hword[1]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.hsty[126] = %lX\n", (kulong)&ioR2yTblP2.hsty.hword[126]);
	R2yTest3_RS_PRINTF("ioR2yTblP2.hsty[127] = %lX\n", (kulong)&ioR2yTblP2.hsty.hword[127]);

	R2yTest3_RS_PRINTF(" \n");
#endif
}

R2yTest3 *r2y_test3_new(void)
{
	R2yTest3* self = k_object_new_with_private(R2Y_TYPE_TEST3, sizeof(R2yTest3Private));
	return self;
}
