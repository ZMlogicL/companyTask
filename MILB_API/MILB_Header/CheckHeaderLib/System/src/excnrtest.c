/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :郑蛘钊
*@brief             :excnrtest
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#include <stdio.h>
#include <stdlib.h>
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
#include "excnrtest.h"


K_TYPE_DEFINE_WITH_PRIVATE(ExCnrTest, ex_cnr_test);

#define EX_CNR_TEST_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ExCnrTestPrivate, EX_TYPE_CNR_TEST))

#define EX_CNR_TEST_RS_PRINTF printf


struct  _ExCnrTestPrivate
{

};
/**
 *IMPL
 */
static void ex_cnr_test_constructor(ExCnrTest *self)
{
	ExCnrTestPrivate *priv = EX_CNR_TEST_GET_PRIVATE(self);
}

static void ex_cnr_test_destructor(ExCnrTest *self)
{
	ExCnrTestPrivate *priv = EX_CNR_TEST_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
void ex_cnr_test_exstop_test(ExCnrTest* self)
{
// for PC debug
#if 0
    #define ioExstop   (*ioExstop2)
    volatile IoExstop* ioExstop2 = (kpointer)0x2B110000;
#endif
    EX_CNR_TEST_RS_PRINTF("EXS TOP\n");
#if 0
    EX_CNR_TEST_RS_PRINTF("ioExstop.xdmaclpctrl           = 0x%lX\n", (kulong)&ioExstop.xdmaclpctrl);
    EX_CNR_TEST_RS_PRINTF("ioExstop.nflpctrl              = 0x%lX\n", (kulong)&ioExstop.nflpctrl);
    EX_CNR_TEST_RS_PRINTF("ioExstop.nfbssigctrl           = 0x%lX\n", (kulong)&ioExstop.nfbssigctrl);
    EX_CNR_TEST_RS_PRINTF("ioExstop.softreset             = 0x%lX\n", (kulong)&ioExstop.softreset);
    EX_CNR_TEST_RS_PRINTF("ioExstop.intstat               = 0x%lX\n", (kulong)&ioExstop.intstat);
    EX_CNR_TEST_RS_PRINTF("ioExstop.intmsk                = 0x%lX\n", (kulong)&ioExstop.intmsk);
    EX_CNR_TEST_RS_PRINTF("ioExstop.sigmon                = 0x%lX\n", (kulong)&ioExstop.sigmon);
    EX_CNR_TEST_RS_PRINTF("ioExstop.deben                 = 0x%lX\n", (kulong)&ioExstop.deben);
    EX_CNR_TEST_RS_PRINTF("ioExstop.cdinsmodctrl          = 0x%lX\n", (kulong)&ioExstop.cdinsmodctrl);
    EX_CNR_TEST_RS_PRINTF("ioExstop.relchptctrl           = 0x%lX\n", (kulong)&ioExstop.relchptctrl);
    EX_CNR_TEST_RS_PRINTF("ioExstop.rampdctrl             = 0x%lX\n", (kulong)&ioExstop.rampdctrl);
    EX_CNR_TEST_RS_PRINTF("ioExstop.pciebifctrl           = 0x%lX\n", (kulong)&ioExstop.pciebifctrl);
    EX_CNR_TEST_RS_PRINTF("ioExstop.netsecptpclkstopctrl  = 0x%lX\n", (kulong)&ioExstop.netsecptpclkstopctrl);

    EX_CNR_TEST_RS_PRINTF(" \n");
#endif
}

void ex_cnr_test_exsgpv_test(ExCnrTest* self)
{
    EX_CNR_TEST_RS_PRINTF("EXS GPV \n");
#if 0
    EX_CNR_TEST_RS_PRINTF("ioGpv.remap           = 0x%p\n", &ioGpv.remap);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.dmy00041fff);

    EX_CNR_TEST_RS_PRINTF("ioGpv.amib[0]         = 0x%p\n", &ioGpv.amib[0]);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.amib[0].dmy00000007);
    EX_CNR_TEST_RS_PRINTF("ioGpv.amib[0].fmbi    = 0x%p\n", &ioGpv.amib[0].fmbi);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.amib[0].dmy000c001f);
    EX_CNR_TEST_RS_PRINTF("ioGpv.amib[0].sm      = 0x%p\n", &ioGpv.amib[0].sm);
    EX_CNR_TEST_RS_PRINTF("ioGpv.amib[0].fm2     = 0x%p\n", &ioGpv.amib[0].fm2);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.amib[0].dmy0028003f);
    EX_CNR_TEST_RS_PRINTF("ioGpv.amib[0].wt      = 0x%p\n", &ioGpv.amib[0].wt);
    EX_CNR_TEST_RS_PRINTF("ioGpv.amib[0].ac      = 0x%p\n", &ioGpv.amib[0].ac);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.amib[0].dmy00480107);
    EX_CNR_TEST_RS_PRINTF("ioGpv.amib[0].fm      = 0x%p\n", &ioGpv.amib[0].fm);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.amib[0].dmy010c0fff);
    for(kint i = 1; i < 14; i++) {
        EX_CNR_TEST_RS_PRINTF("ioGpv.amib[%d]    = 0x%p\n", i, &ioGpv.amib[i]);
    }
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.dmy1000041fff);
    EX_CNR_TEST_RS_PRINTF(" \n");

    EX_CNR_TEST_RS_PRINTF("ioGpv.asib[0]         = 0x%p\n", &ioGpv.asib[0]);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.asib[0].dmy0000001f);
    EX_CNR_TEST_RS_PRINTF("ioGpv.asib[0].sm      = 0x%p\n", &ioGpv.asib[0].sm);
    EX_CNR_TEST_RS_PRINTF("ioGpv.asib[0].fm2     = 0x%p\n", &ioGpv.asib[0].fm2);
    EX_CNR_TEST_RS_PRINTF("ioGpv.asib[0].fma     = 0x%p\n", &ioGpv.asib[0].fma);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.asib[0].dmy002c003f);
    EX_CNR_TEST_RS_PRINTF("ioGpv.asib[0].wt      = 0x%p\n", &ioGpv.asib[0].wt);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.asib[0].dmy004400ff);
    EX_CNR_TEST_RS_PRINTF("ioGpv.asib[0].rq      = 0x%p\n", &ioGpv.asib[0].rq);
    EX_CNR_TEST_RS_PRINTF("ioGpv.asib[0].wq      = 0x%p\n", &ioGpv.asib[0].wq);
    EX_CNR_TEST_RS_PRINTF("ioGpv.asib[0].fm      = 0x%p\n", &ioGpv.asib[0].fm);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.asib[0].dmy010c0fff);
    for(kint i = 1; i < 12; i++) {
        EX_CNR_TEST_RS_PRINTF("ioGpv.asib[%d]    = 0x%p\n", i, &ioGpv.asib[i]);
    }
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.dmy4e000C1fff);
    EX_CNR_TEST_RS_PRINTF(" \n");

    EX_CNR_TEST_RS_PRINTF("ioGpv.ib[0]           = 0x%p\n", &ioGpv.ib[0]);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.ib[0].dmy00000007);
    EX_CNR_TEST_RS_PRINTF("ioGpv.ib[0].fmbi      = 0x%p\n", &ioGpv.ib[0].fmbi);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.ib[0].dmy000c001f);
    EX_CNR_TEST_RS_PRINTF("ioGpv.ib[0].sm        = 0x%p\n", &ioGpv.ib[0].sm);
    EX_CNR_TEST_RS_PRINTF("ioGpv.ib[0].fm2       = 0x%p\n", &ioGpv.ib[0].fm2);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.ib[0].dmy0028003f);
    EX_CNR_TEST_RS_PRINTF("ioGpv.ib[0].wt        = 0x%p\n", &ioGpv.ib[0].wt);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.ib[0].dmy00440107);
    EX_CNR_TEST_RS_PRINTF("ioGpv.ib[0].fm        = 0x%p\n", &ioGpv.ib[0].fm);
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.ib[0].dmy010c0fff);
    for(kint i = 1; i < 4; i++) {
        EX_CNR_TEST_RS_PRINTF("ioGpv.ib[%d]      = 0x%p\n", i, &ioGpv.ib[i]);
    }
    EX_CNR_TEST_RS_PRINTF("Reserved               = 0x%p\n", &ioGpv.dmy_C6000_FFFFF);
    EX_CNR_TEST_RS_PRINTF(" \n");
#endif
}

void ex_cnr_test_cnr_test(ExCnrTest* self)
{
// for PC debug
#if 0
#define ioCnrP1       (*ioCnr2P1)
#define ioCnrP2       (*ioCnr2P2)
#define ioCnrP3       (*ioCnr2P3)
    volatile IoCnrReg* ioCnr2P1 = (kpointer)0x28420000;
    volatile IoCnrReg* ioCnr2P2 = (kpointer)0x28520000;
    volatile IoCnrReg* ioCnr2P3 = (kpointer)0x28620000;
#endif
    EX_CNR_TEST_RS_PRINTF("CNR\n");
#if 0
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.sprsr          = %lX\n", (kulong)&ioCnrP1.otfRegRw.sprsr);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.acesen         = %lX\n", (kulong)&ioCnrP1.otfRegRw.acesen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.sprtrg         = %lX\n", (kulong)&ioCnrP1.otfRegRw.sprtrg);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.sprice         = %lX\n", (kulong)&ioCnrP1.otfRegRw.sprice);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.spricf         = %lX\n", (kulong)&ioCnrP1.otfRegRw.spricf);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.hdiv           = %lX\n", (kulong)&ioCnrP1.otfRegRw.hdiv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.spraxiset      = %lX\n", (kulong)&ioCnrP1.otfRegRw.spraxiset);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.sprmod         = %lX\n", (kulong)&ioCnrP1.otfRegRw.sprmod);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.hsize          = %lX\n", (kulong)&ioCnrP1.otfRegRw.hsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.vsize          = %lX\n", (kulong)&ioCnrP1.otfRegRw.vsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.wcta           = %lX\n", (kulong)&ioCnrP1.otfRegRw.wcta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.wcdef          = %lX\n", (kulong)&ioCnrP1.otfRegRw.wcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfRegRw.cnrwofsx       = %lX\n", (kulong)&ioCnrP1.otfRegRw.cnrwofsx);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cspren       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cgdken       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cgdken);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcen         = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcythh       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcythv       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mccthh       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mccthv       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcydym       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcydymdt     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcyscl       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcysclof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcysclga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcysclbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mccscl       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mccsclof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mccsclga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mccsclbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcsscl       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcssclof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcssclga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.mcssclbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.mcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcen         = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcythh       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcythv       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lccthh       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lccthv       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcydym       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcydymdt     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcyscl       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcysclof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcysclga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcysclbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lccscl       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lccsclof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lccsclga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lccsclbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcsscl       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcssclof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcssclga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.lcssclbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.lcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.blend        = %lX\n", (kulong)&ioCnrP1.otfCsprReg.blend);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cesclof      = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cesclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cesclga      = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cesclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cesclbd      = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cesclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cphpt        = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cphpt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cphptk       = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cphptk);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cdsclof      = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cdsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cdsclga      = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cdsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.cdsclbd      = %lX\n", (kulong)&ioCnrP1.otfCsprReg.cdsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.whtmd        = %lX\n", (kulong)&ioCnrP1.otfCsprReg.whtmd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprs         = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprs);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprscbof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprscbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprscbga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprscbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprscbbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprscbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprscrof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprscrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprscrga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprscrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprscrbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprscrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprd         = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprdcbof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprdcbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprdcbga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprdcbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprdcbbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprdcbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprdcrof     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprdcrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprdcrga     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprdcrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.otfCsprReg.sprdcrbd     = %lX\n", (kulong)&ioCnrP1.otfCsprReg.sprdcrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.sprsr          = %lX\n", (kulong)&ioCnrP1.oflRegRw.sprsr);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.acesen         = %lX\n", (kulong)&ioCnrP1.oflRegRw.acesen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.sprtrg         = %lX\n", (kulong)&ioCnrP1.oflRegRw.sprtrg);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.sprice         = %lX\n", (kulong)&ioCnrP1.oflRegRw.sprice);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.spricf         = %lX\n", (kulong)&ioCnrP1.oflRegRw.spricf);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.vdiv           = %lX\n", (kulong)&ioCnrP1.oflRegRw.vdiv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.spraxiset      = %lX\n", (kulong)&ioCnrP1.oflRegRw.spraxiset);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.sprmod         = %lX\n", (kulong)&ioCnrP1.oflRegRw.sprmod);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.hsize          = %lX\n", (kulong)&ioCnrP1.oflRegRw.hsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.vsize          = %lX\n", (kulong)&ioCnrP1.oflRegRw.vsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.ryta           = %lX\n", (kulong)&ioCnrP1.oflRegRw.ryta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.rydef          = %lX\n", (kulong)&ioCnrP1.oflRegRw.rydef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.rcbta          = %lX\n", (kulong)&ioCnrP1.oflRegRw.rcbta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.rcrta          = %lX\n", (kulong)&ioCnrP1.oflRegRw.rcrta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.rcdef          = %lX\n", (kulong)&ioCnrP1.oflRegRw.rcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.wyta           = %lX\n", (kulong)&ioCnrP1.oflRegRw.wyta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.wydef          = %lX\n", (kulong)&ioCnrP1.oflRegRw.wydef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.wcbta          = %lX\n", (kulong)&ioCnrP1.oflRegRw.wcbta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.wcrta          = %lX\n", (kulong)&ioCnrP1.oflRegRw.wcrta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.wcdef          = %lX\n", (kulong)&ioCnrP1.oflRegRw.wcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegRw.tmpta          = %lX\n", (kulong)&ioCnrP1.oflRegRw.tmpta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cspren       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cgdken       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cgdken);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcen         = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcythh       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcythv       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mccthh       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mccthv       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcydym       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcydymdt     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcyscl       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcysclof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcysclga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcysclbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mccscl       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mccsclof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mccsclga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mccsclbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcsscl       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcssclof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcssclga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.mcssclbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.mcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcen         = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcythh       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcythv       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lccthh       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lccthv       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcydym       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcydymdt     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcyscl       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcysclof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcysclga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcysclbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lccscl       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lccsclof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lccsclga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lccsclbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcsscl       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcssclof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcssclga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.lcssclbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.lcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.blend        = %lX\n", (kulong)&ioCnrP1.oflCsprReg.blend);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cesclof      = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cesclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cesclga      = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cesclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cesclbd      = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cesclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cphpt        = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cphpt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cphptk       = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cphptk);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cdsclof      = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cdsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cdsclga      = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cdsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.cdsclbd      = %lX\n", (kulong)&ioCnrP1.oflCsprReg.cdsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.whtmd        = %lX\n", (kulong)&ioCnrP1.oflCsprReg.whtmd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprs         = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprs);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprscbof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprscbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprscbga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprscbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprscbbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprscbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprscrof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprscrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprscrga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprscrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprscrbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprscrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprd         = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprdcbof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprdcbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprdcbga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprdcbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprdcbbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprdcbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprdcrof     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprdcrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprdcrga     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprdcrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflCsprReg.sprdcrbd     = %lX\n", (kulong)&ioCnrP1.oflCsprReg.sprdcrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegYspr.yspren       = %lX\n", (kulong)&ioCnrP1.oflRegYspr.yspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegYspr.ysprmode     = %lX\n", (kulong)&ioCnrP1.oflRegYspr.ysprmode);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegYspr.ysprfxey     = %lX\n", (kulong)&ioCnrP1.oflRegYspr.ysprfxey);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegYspr.ysprfxec     = %lX\n", (kulong)&ioCnrP1.oflRegYspr.ysprfxec);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegYspr.yspralpbd    = %lX\n", (kulong)&ioCnrP1.oflRegYspr.yspralpbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegYspr.ysprdyeyof   = %lX\n", (kulong)&ioCnrP1.oflRegYspr.ysprdyeyof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegYspr.ysprdyeyga   = %lX\n", (kulong)&ioCnrP1.oflRegYspr.ysprdyeyga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP1.oflRegYspr.ysprdyeybd   = %lX\n", (kulong)&ioCnrP1.oflRegYspr.ysprdyeybd);

    EX_CNR_TEST_RS_PRINTF(" \n");

    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.sprsr          = %lX\n", (kulong)&ioCnrP2.otfRegRw.sprsr);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.acesen         = %lX\n", (kulong)&ioCnrP2.otfRegRw.acesen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.sprtrg         = %lX\n", (kulong)&ioCnrP2.otfRegRw.sprtrg);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.sprice         = %lX\n", (kulong)&ioCnrP2.otfRegRw.sprice);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.spricf         = %lX\n", (kulong)&ioCnrP2.otfRegRw.spricf);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.hdiv           = %lX\n", (kulong)&ioCnrP2.otfRegRw.hdiv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.spraxiset      = %lX\n", (kulong)&ioCnrP2.otfRegRw.spraxiset);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.sprmod         = %lX\n", (kulong)&ioCnrP2.otfRegRw.sprmod);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.hsize          = %lX\n", (kulong)&ioCnrP2.otfRegRw.hsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.vsize          = %lX\n", (kulong)&ioCnrP2.otfRegRw.vsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.wcta           = %lX\n", (kulong)&ioCnrP2.otfRegRw.wcta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.wcdef          = %lX\n", (kulong)&ioCnrP2.otfRegRw.wcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfRegRw.cnrwofsx       = %lX\n", (kulong)&ioCnrP2.otfRegRw.cnrwofsx);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cspren       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cgdken       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cgdken);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcen         = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcythh       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcythv       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mccthh       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mccthv       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcydym       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcydymdt     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcyscl       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcysclof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcysclga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcysclbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mccscl       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mccsclof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mccsclga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mccsclbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcsscl       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcssclof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcssclga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.mcssclbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.mcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcen         = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcythh       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcythv       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lccthh       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lccthv       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcydym       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcydymdt     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcyscl       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcysclof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcysclga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcysclbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lccscl       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lccsclof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lccsclga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lccsclbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcsscl       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcssclof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcssclga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.lcssclbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.lcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.blend        = %lX\n", (kulong)&ioCnrP2.otfCsprReg.blend);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cesclof      = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cesclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cesclga      = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cesclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cesclbd      = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cesclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cphpt        = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cphpt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cphptk       = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cphptk);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cdsclof      = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cdsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cdsclga      = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cdsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.cdsclbd      = %lX\n", (kulong)&ioCnrP2.otfCsprReg.cdsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.whtmd        = %lX\n", (kulong)&ioCnrP2.otfCsprReg.whtmd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprs         = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprs);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprscbof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprscbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprscbga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprscbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprscbbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprscbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprscrof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprscrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprscrga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprscrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprscrbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprscrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprd         = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprdcbof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprdcbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprdcbga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprdcbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprdcbbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprdcbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprdcrof     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprdcrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprdcrga     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprdcrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.otfCsprReg.sprdcrbd     = %lX\n", (kulong)&ioCnrP2.otfCsprReg.sprdcrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.sprsr          = %lX\n", (kulong)&ioCnrP2.oflRegRw.sprsr);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.acesen         = %lX\n", (kulong)&ioCnrP2.oflRegRw.acesen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.sprtrg         = %lX\n", (kulong)&ioCnrP2.oflRegRw.sprtrg);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.sprice         = %lX\n", (kulong)&ioCnrP2.oflRegRw.sprice);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.spricf         = %lX\n", (kulong)&ioCnrP2.oflRegRw.spricf);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.vdiv           = %lX\n", (kulong)&ioCnrP2.oflRegRw.vdiv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.spraxiset      = %lX\n", (kulong)&ioCnrP2.oflRegRw.spraxiset);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.sprmod         = %lX\n", (kulong)&ioCnrP2.oflRegRw.sprmod);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.hsize          = %lX\n", (kulong)&ioCnrP2.oflRegRw.hsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.vsize          = %lX\n", (kulong)&ioCnrP2.oflRegRw.vsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.ryta           = %lX\n", (kulong)&ioCnrP2.oflRegRw.ryta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.rydef          = %lX\n", (kulong)&ioCnrP2.oflRegRw.rydef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.rcbta          = %lX\n", (kulong)&ioCnrP2.oflRegRw.rcbta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.rcrta          = %lX\n", (kulong)&ioCnrP2.oflRegRw.rcrta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.rcdef          = %lX\n", (kulong)&ioCnrP2.oflRegRw.rcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.wyta           = %lX\n", (kulong)&ioCnrP2.oflRegRw.wyta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.wydef          = %lX\n", (kulong)&ioCnrP2.oflRegRw.wydef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.wcbta          = %lX\n", (kulong)&ioCnrP2.oflRegRw.wcbta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.wcrta          = %lX\n", (kulong)&ioCnrP2.oflRegRw.wcrta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.wcdef          = %lX\n", (kulong)&ioCnrP2.oflRegRw.wcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegRw.tmpta          = %lX\n", (kulong)&ioCnrP2.oflRegRw.tmpta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cspren       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cgdken       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cgdken);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcen         = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcythh       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcythv       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mccthh       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mccthv       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcydym       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcydymdt     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcyscl       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcysclof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcysclga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcysclbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mccscl       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mccsclof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mccsclga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mccsclbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcsscl       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcssclof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcssclga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.mcssclbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.mcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcen         = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcythh       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcythv       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lccthh       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lccthv       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcydym       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcydymdt     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcyscl       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcysclof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcysclga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcysclbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lccscl       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lccsclof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lccsclga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lccsclbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcsscl       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcssclof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcssclga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.lcssclbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.lcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.blend        = %lX\n", (kulong)&ioCnrP2.oflCsprReg.blend);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cesclof      = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cesclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cesclga      = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cesclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cesclbd      = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cesclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cphpt        = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cphpt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cphptk       = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cphptk);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cdsclof      = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cdsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cdsclga      = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cdsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.cdsclbd      = %lX\n", (kulong)&ioCnrP2.oflCsprReg.cdsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.whtmd        = %lX\n", (kulong)&ioCnrP2.oflCsprReg.whtmd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprs         = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprs);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprscbof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprscbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprscbga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprscbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprscbbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprscbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprscrof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprscrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprscrga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprscrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprscrbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprscrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprd         = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprdcbof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprdcbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprdcbga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprdcbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprdcbbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprdcbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprdcrof     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprdcrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprdcrga     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprdcrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflCsprReg.sprdcrbd     = %lX\n", (kulong)&ioCnrP2.oflCsprReg.sprdcrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegYspr.yspren       = %lX\n", (kulong)&ioCnrP2.oflRegYspr.yspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegYspr.ysprmode     = %lX\n", (kulong)&ioCnrP2.oflRegYspr.ysprmode);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegYspr.ysprfxey     = %lX\n", (kulong)&ioCnrP2.oflRegYspr.ysprfxey);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegYspr.ysprfxec     = %lX\n", (kulong)&ioCnrP2.oflRegYspr.ysprfxec);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegYspr.yspralpbd    = %lX\n", (kulong)&ioCnrP2.oflRegYspr.yspralpbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegYspr.ysprdyeyof   = %lX\n", (kulong)&ioCnrP2.oflRegYspr.ysprdyeyof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegYspr.ysprdyeyga   = %lX\n", (kulong)&ioCnrP2.oflRegYspr.ysprdyeyga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP2.oflRegYspr.ysprdyeybd   = %lX\n", (kulong)&ioCnrP2.oflRegYspr.ysprdyeybd);

    EX_CNR_TEST_RS_PRINTF(" \n");

    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.sprsr          = %lX\n", (kulong)&ioCnrP3.otfRegRw.sprsr);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.acesen         = %lX\n", (kulong)&ioCnrP3.otfRegRw.acesen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.sprtrg         = %lX\n", (kulong)&ioCnrP3.otfRegRw.sprtrg);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.sprice         = %lX\n", (kulong)&ioCnrP3.otfRegRw.sprice);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.spricf         = %lX\n", (kulong)&ioCnrP3.otfRegRw.spricf);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.hdiv           = %lX\n", (kulong)&ioCnrP3.otfRegRw.hdiv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.spraxiset      = %lX\n", (kulong)&ioCnrP3.otfRegRw.spraxiset);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.sprmod         = %lX\n", (kulong)&ioCnrP3.otfRegRw.sprmod);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.hsize          = %lX\n", (kulong)&ioCnrP3.otfRegRw.hsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.vsize          = %lX\n", (kulong)&ioCnrP3.otfRegRw.vsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.wcta           = %lX\n", (kulong)&ioCnrP3.otfRegRw.wcta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.wcdef          = %lX\n", (kulong)&ioCnrP3.otfRegRw.wcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfRegRw.cnrwofsx       = %lX\n", (kulong)&ioCnrP3.otfRegRw.cnrwofsx);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cspren       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cgdken       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cgdken);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcen         = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcythh       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcythv       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mccthh       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mccthv       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcydym       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcydymdt     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcyscl       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcysclof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcysclga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcysclbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mccscl       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mccsclof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mccsclga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mccsclbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcsscl       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcssclof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcssclga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.mcssclbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.mcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcen         = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcythh       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcythv       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lccthh       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lccthv       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcydym       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcydymdt     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcyscl       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcysclof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcysclga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcysclbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lccscl       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lccsclof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lccsclga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lccsclbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcsscl       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcssclof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcssclga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.lcssclbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.lcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.blend        = %lX\n", (kulong)&ioCnrP3.otfCsprReg.blend);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cesclof      = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cesclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cesclga      = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cesclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cesclbd      = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cesclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cphpt        = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cphpt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cphptk       = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cphptk);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cdsclof      = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cdsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cdsclga      = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cdsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.cdsclbd      = %lX\n", (kulong)&ioCnrP3.otfCsprReg.cdsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.whtmd        = %lX\n", (kulong)&ioCnrP3.otfCsprReg.whtmd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprs         = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprs);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprscbof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprscbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprscbga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprscbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprscbbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprscbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprscrof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprscrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprscrga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprscrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprscrbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprscrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprd         = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprdcbof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprdcbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprdcbga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprdcbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprdcbbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprdcbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprdcrof     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprdcrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprdcrga     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprdcrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.otfCsprReg.sprdcrbd     = %lX\n", (kulong)&ioCnrP3.otfCsprReg.sprdcrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.sprsr          = %lX\n", (kulong)&ioCnrP3.oflRegRw.sprsr);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.acesen         = %lX\n", (kulong)&ioCnrP3.oflRegRw.acesen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.sprtrg         = %lX\n", (kulong)&ioCnrP3.oflRegRw.sprtrg);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.sprice         = %lX\n", (kulong)&ioCnrP3.oflRegRw.sprice);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.spricf         = %lX\n", (kulong)&ioCnrP3.oflRegRw.spricf);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.vdiv           = %lX\n", (kulong)&ioCnrP3.oflRegRw.vdiv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.spraxiset      = %lX\n", (kulong)&ioCnrP3.oflRegRw.spraxiset);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.sprmod         = %lX\n", (kulong)&ioCnrP3.oflRegRw.sprmod);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.hsize          = %lX\n", (kulong)&ioCnrP3.oflRegRw.hsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.vsize          = %lX\n", (kulong)&ioCnrP3.oflRegRw.vsize);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.ryta           = %lX\n", (kulong)&ioCnrP3.oflRegRw.ryta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.rydef          = %lX\n", (kulong)&ioCnrP3.oflRegRw.rydef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.rcbta          = %lX\n", (kulong)&ioCnrP3.oflRegRw.rcbta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.rcrta          = %lX\n", (kulong)&ioCnrP3.oflRegRw.rcrta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.rcdef          = %lX\n", (kulong)&ioCnrP3.oflRegRw.rcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.wyta           = %lX\n", (kulong)&ioCnrP3.oflRegRw.wyta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.wydef          = %lX\n", (kulong)&ioCnrP3.oflRegRw.wydef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.wcbta          = %lX\n", (kulong)&ioCnrP3.oflRegRw.wcbta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.wcrta          = %lX\n", (kulong)&ioCnrP3.oflRegRw.wcrta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.wcdef          = %lX\n", (kulong)&ioCnrP3.oflRegRw.wcdef);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegRw.tmpta          = %lX\n", (kulong)&ioCnrP3.oflRegRw.tmpta);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cspren       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cgdken       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cgdken);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcen         = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcythh       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcythv       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mccthh       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mccthv       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcydym       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcydymdt     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcyscl       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcysclof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcysclga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcysclbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mccscl       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mccsclof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mccsclga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mccsclbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcsscl       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcssclof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcssclga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.mcssclbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.mcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcen         = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcen);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcythh       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcythh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcythv       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcythv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lccthh       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lccthh);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lccthv       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lccthv);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcydym       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcydym);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcydymdt     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcydymdt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcyscl       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcyscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcysclof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcysclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcysclga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcysclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcysclbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcysclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lccscl       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lccscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lccsclof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lccsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lccsclga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lccsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lccsclbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lccsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcsscl       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcsscl);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcssclof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcssclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcssclga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcssclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.lcssclbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.lcssclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.blend        = %lX\n", (kulong)&ioCnrP3.oflCsprReg.blend);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cesclof      = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cesclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cesclga      = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cesclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cesclbd      = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cesclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cphpt        = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cphpt);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cphptk       = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cphptk);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cdsclof      = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cdsclof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cdsclga      = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cdsclga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.cdsclbd      = %lX\n", (kulong)&ioCnrP3.oflCsprReg.cdsclbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.whtmd        = %lX\n", (kulong)&ioCnrP3.oflCsprReg.whtmd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprs         = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprs);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprscbof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprscbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprscbga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprscbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprscbbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprscbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprscrof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprscrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprscrga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprscrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprscrbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprscrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprd         = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprdcbof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprdcbof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprdcbga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprdcbga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprdcbbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprdcbbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprdcrof     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprdcrof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprdcrga     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprdcrga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflCsprReg.sprdcrbd     = %lX\n", (kulong)&ioCnrP3.oflCsprReg.sprdcrbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegYspr.yspren       = %lX\n", (kulong)&ioCnrP3.oflRegYspr.yspren);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegYspr.ysprmode     = %lX\n", (kulong)&ioCnrP3.oflRegYspr.ysprmode);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegYspr.ysprfxey     = %lX\n", (kulong)&ioCnrP3.oflRegYspr.ysprfxey);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegYspr.ysprfxec     = %lX\n", (kulong)&ioCnrP3.oflRegYspr.ysprfxec);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegYspr.yspralpbd    = %lX\n", (kulong)&ioCnrP3.oflRegYspr.yspralpbd);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegYspr.ysprdyeyof   = %lX\n", (kulong)&ioCnrP3.oflRegYspr.ysprdyeyof);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegYspr.ysprdyeyga   = %lX\n", (kulong)&ioCnrP3.oflRegYspr.ysprdyeyga);
    EX_CNR_TEST_RS_PRINTF("ioCnrP3.oflRegYspr.ysprdyeybd   = %lX\n", (kulong)&ioCnrP3.oflRegYspr.ysprdyeybd);
#endif
    EX_CNR_TEST_RS_PRINTF(" \n");
}

ExCnrTest* ex_cnr_test_new(void)
{
    ExCnrTest* self = k_object_new_with_private(EX_TYPE_CNR_TEST, sizeof(ExCnrTestPrivate));
    return self;
}
