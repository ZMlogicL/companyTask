/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :郑蛘钊
*@brief             :kiotest
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
#include "kiotest.h"


K_TYPE_DEFINE_WITH_PRIVATE(KIoTest, k_io_test);

#define K_IO_TEST_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KIoTestPrivate, K_TYPE_IO_TEST))

#define K_IO_TEST_RS_PRINTF printf


struct  _KIoTestPrivate
{

};
/**
*IMPL
*/
static void k_io_test_constructor(KIoTest *self)
{
	KIoTestPrivate *priv = K_IO_TEST_GET_PRIVATE(self);
}

static void k_io_test_destructor(KIoTest *self)
{
	KIoTestPrivate *priv = K_IO_TEST_GET_PRIVATE(self);
}
/**
*PUBLIC
*/
void k_io_test_pas_table_test(KDispTest *self, E_PRO_BLOCK_TYPE type, IoPro ioPro, IoProTbl ioProTbl)
{
#ifdef D_ENABLE_IO_PRO_PAS   /** pas Unit **/
    if(type == E_PRO_BLOCK_TYPE_PAS) {
        // pastop
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.sr                = %x\n", (kuint)&ioPro.pas.pastop.sr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.clkstp            = %x\n", (kuint)&ioPro.pas.pastop.clkstp);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.intmon1           = %x\n", (kuint)&ioPro.pas.pastop.intmon1);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.intmon2           = %x\n", (kuint)&ioPro.pas.pastop.intmon2);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.intctl            = %x\n", (kuint)&ioPro.pas.pastop.intctl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.vhdintenb         = %x\n", (kuint)&ioPro.pas.pastop.vhdintenb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.vhdintflg         = %x\n", (kuint)&ioPro.pas.pastop.vhdintflg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.vhset             = %x\n", (kuint)&ioPro.pas.pastop.vhset);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.vmivadr           = %x\n", (kuint)&ioPro.pas.pastop.vmivadr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.vmihadr           = %x\n", (kuint)&ioPro.pas.pastop.vmihadr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pastop.hmihadr           = %x\n", (kuint)&ioPro.pas.pastop.hmihadr);
        // pg
        K_IO_TEST_RS_PRINTF("ioPro.pas.pg.pgtrg                 = %x\n", (kuint)&ioPro.pas.pg.pgtrg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pg.pgctl                 = %x\n", (kuint)&ioPro.pas.pg.pgctl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pg.pgvw                  = %x\n", (kuint)&ioPro.pas.pg.pgvw);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pg.pghw                  = %x\n", (kuint)&ioPro.pas.pg.pghw);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pg.pgvblnk               = %x\n", (kuint)&ioPro.pas.pg.pgvblnk);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pg.pghblnk               = %x\n", (kuint)&ioPro.pas.pg.pghblnk);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pg.pgvdhdblnk            = %x\n", (kuint)&ioPro.pas.pg.pgvdhdblnk);
        // lnr
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrtrg               = %x\n", (kuint)&ioPro.pas.lnr.lnrtrg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrbr                = %x\n", (kuint)&ioPro.pas.lnr.lnrbr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrincr              = %x\n", (kuint)&ioPro.pas.lnr.lnrincr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrofsr              = %x\n", (kuint)&ioPro.pas.lnr.lnrofsr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrbgr               = %x\n", (kuint)&ioPro.pas.lnr.lnrbgr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrincgr             = %x\n", (kuint)&ioPro.pas.lnr.lnrincgr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrofsgr             = %x\n", (kuint)&ioPro.pas.lnr.lnrofsgr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrbgb               = %x\n", (kuint)&ioPro.pas.lnr.lnrbgb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrincgb             = %x\n", (kuint)&ioPro.pas.lnr.lnrincgb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrofsgb             = %x\n", (kuint)&ioPro.pas.lnr.lnrofsgb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrbb                = %x\n", (kuint)&ioPro.pas.lnr.lnrbb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrincb              = %x\n", (kuint)&ioPro.pas.lnr.lnrincb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.lnr.lnrofsb              = %x\n", (kuint)&ioPro.pas.lnr.lnrofsb);
        // PGAIN
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pgaintrg           = %x\n", (kuint)&ioPro.pas.pgain.pgaintrg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pgainr             = %x\n", (kuint)&ioPro.pas.pgain.pgainr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pgaingr            = %x\n", (kuint)&ioPro.pas.pgain.pgaingr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pgaingb            = %x\n", (kuint)&ioPro.pas.pgain.pgaingb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pgainb             = %x\n", (kuint)&ioPro.pas.pgain.pgainb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pofsr              = %x\n", (kuint)&ioPro.pas.pgain.pofsr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pofsgr             = %x\n", (kuint)&ioPro.pas.pgain.pofsgr);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pofsgb             = %x\n", (kuint)&ioPro.pas.pgain.pofsgb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pgain.pofsb              = %x\n", (kuint)&ioPro.pas.pgain.pofsb);
        // SPT
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.spttrg               = %x\n", (kuint)&ioPro.pas.spt.spttrg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.sptpaen              = %x\n", (kuint)&ioPro.pas.spt.sptpaen);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.spttbl               = %x\n", (kuint)&ioPro.pas.spt.spttbl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.sptbs                = %x\n", (kuint)&ioPro.pas.spt.sptbs);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.sptbd                = %x\n", (kuint)&ioPro.pas.spt.sptbd);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.sptv                 = %x\n", (kuint)&ioPro.pas.spt.sptv);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.spth                 = %x\n", (kuint)&ioPro.pas.spt.spth);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.sptvbc               = %x\n", (kuint)&ioPro.pas.spt.sptvbc);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.spthbc               = %x\n", (kuint)&ioPro.pas.spt.spthbc);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.sptclp               = %x\n", (kuint)&ioPro.pas.spt.sptclp);
        K_IO_TEST_RS_PRINTF("ioPro.pas.spt.sptnopv              = %x\n", (kuint)&ioPro.pas.spt.sptnopv);
        // P2M
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.p2mtrg              = %x\n", (kuint)&ioPro.pas.p2m0.p2mtrg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.p2mpaen             = %x\n", (kuint)&ioPro.pas.p2m0.p2mpaen);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.p2mctl              = %x\n", (kuint)&ioPro.pas.p2m0.p2mctl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.p2mofs              = %x\n", (kuint)&ioPro.pas.p2m0.p2mofs);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.pbsft               = %x\n", (kuint)&ioPro.pas.p2m0.pbsft);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.pclph               = %x\n", (kuint)&ioPro.pas.p2m0.pclph);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.ptrmv               = %x\n", (kuint)&ioPro.pas.p2m0.ptrmv);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.ptrmh               = %x\n", (kuint)&ioPro.pas.p2m0.ptrmh);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.ptrmvw              = %x\n", (kuint)&ioPro.pas.p2m0.ptrmvw);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.ptrmhw              = %x\n", (kuint)&ioPro.pas.p2m0.ptrmhw);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.ptrmxvcyc           = %x\n", (kuint)&ioPro.pas.p2m0.ptrmxvcyc);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.ptrmxhcyc           = %x\n", (kuint)&ioPro.pas.p2m0.ptrmxhcyc);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.ptrmxven            = %x\n", (kuint)&ioPro.pas.p2m0.ptrmxven);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.ptrmxhen            = %x\n", (kuint)&ioPro.pas.p2m0.ptrmxhen);
        K_IO_TEST_RS_PRINTF("ioPro.pas.p2m0.p2mmir              = %x\n", (kuint)&ioPro.pas.p2m0.p2mmir);
        // PWCH
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pwchtrg           = %x\n", (kuint)&ioPro.pas.pwch0.pwchtrg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pws               = %x\n", (kuint)&ioPro.pas.pwch0.pws);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pwaxctl           = %x\n", (kuint)&ioPro.pas.pwch0.pwaxctl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pwchctl           = %x\n", (kuint)&ioPro.pas.pwch0.pwchctl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pwchintenb        = %x\n", (kuint)&ioPro.pas.pwch0.pwchintenb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pwchintflg        = %x\n", (kuint)&ioPro.pas.pwch0.pwchintflg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pwchbresp         = %x\n", (kuint)&ioPro.pas.pwch0.pwchbresp);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pwsa              = %x\n", (kuint)&ioPro.pas.pwch0.pwsa);
        K_IO_TEST_RS_PRINTF("ioPro.pas.pwch0.pwlsize           = %x\n", (kuint)&ioPro.pas.pwch0.pwlsize);
        // M2P
        K_IO_TEST_RS_PRINTF("ioPro.pas.m2p0.m2ptrg             = %x\n", (kuint)&ioPro.pas.m2p0.m2ptrg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.m2p0.m2ppaen            = %x\n", (kuint)&ioPro.pas.m2p0.m2ppaen);
        K_IO_TEST_RS_PRINTF("ioPro.pas.m2p0.m2pctl             = %x\n", (kuint)&ioPro.pas.m2p0.m2pctl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.m2p0.m2pbsft            = %x\n", (kuint)&ioPro.pas.m2p0.m2pbsft);
        K_IO_TEST_RS_PRINTF("ioPro.pas.m2p0.m2pofs             = %x\n", (kuint)&ioPro.pas.m2p0.m2pofs);
        K_IO_TEST_RS_PRINTF("ioPro.pas.m2p0.m2pclip            = %x\n", (kuint)&ioPro.pas.m2p0.m2pclip);
        // PRCH
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prchtrg           = %x\n", (kuint)&ioPro.pas.prch0.prchtrg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prchctl           = %x\n", (kuint)&ioPro.pas.prch0.prchctl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prchrs            = %x\n", (kuint)&ioPro.pas.prch0.prchrs);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.praxctl           = %x\n", (kuint)&ioPro.pas.prch0.praxctl);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prchintenb        = %x\n", (kuint)&ioPro.pas.prch0.prchintenb);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prchintflg        = %x\n", (kuint)&ioPro.pas.prch0.prchintflg);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prchbresp         = %x\n", (kuint)&ioPro.pas.prch0.prchbresp);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prsa              = %x\n", (kuint)&ioPro.pas.prch0.prsa);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prlsize           = %x\n", (kuint)&ioPro.pas.prch0.prlsize);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prvsize           = %x\n", (kuint)&ioPro.pas.prch0.prvsize);
        K_IO_TEST_RS_PRINTF("ioPro.pas.prch0.prhsize           = %x\n", (kuint)&ioPro.pas.prch0.prhsize);
    }
#endif  /** pas Unit **/

#ifdef D_ENABLE_IO_PRO_TABLE    /** PRO-TABLE **/
    if(type == E_PRO_BLOCK_TYPE_TABLE) {
        // SEN Unit
        K_IO_TEST_RS_PRINTF("ioProTbl.senTbl.p2m0kntbl       = 0x%p\n", &ioProTbl.senTbl.p2m0kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.senTbl.p2m1kntbl       = 0x%p\n", &ioProTbl.senTbl.p2m1kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.senTbl.p2m2kntbl       = 0x%p\n", &ioProTbl.senTbl.p2m2kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.senTbl.p2m3kntbl       = 0x%p\n", &ioProTbl.senTbl.p2m3kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.senTbl.p2m4kntbl       = 0x%p\n", &ioProTbl.senTbl.p2m4kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.senTbl.p2m5kntbl       = 0x%p\n", &ioProTbl.senTbl.p2m5kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.senTbl.p2m6kntbl       = 0x%p\n", &ioProTbl.senTbl.p2m6kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.senTbl.p2m7kntbl       = 0x%p\n", &ioProTbl.senTbl.p2m7kntbl);
        // SRO Unit(pipe[1])
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.sdc0gd0      = 0x%p\n", &ioProTbl.sro1Tbl.sdc0gd0);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.sdc0gd1      = 0x%p\n", &ioProTbl.sro1Tbl.sdc0gd1);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.sdc1gd0      = 0x%p\n", &ioProTbl.sro1Tbl.sdc1gd0);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.sdc1gd1      = 0x%p\n", &ioProTbl.sro1Tbl.sdc1gd1);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.p2m0kntbl    = 0x%p\n", &ioProTbl.sro1Tbl.p2m0kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.p2m1kntbl    = 0x%p\n", &ioProTbl.sro1Tbl.p2m1kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.p2m2kntbl    = 0x%p\n", &ioProTbl.sro1Tbl.p2m2kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.p2m3kntbl    = 0x%p\n", &ioProTbl.sro1Tbl.p2m3kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.p2m4kntbl    = 0x%p\n", &ioProTbl.sro1Tbl.p2m4kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.p2m5kntbl    = 0x%p\n", &ioProTbl.sro1Tbl.p2m5kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.m2p0dkntbl   = 0x%p\n", &ioProTbl.sro1Tbl.m2p0dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.m2p1dkntbl   = 0x%p\n", &ioProTbl.sro1Tbl.m2p1dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.m2p6dkntbl   = 0x%p\n", &ioProTbl.sro1Tbl.m2p6dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[1]_TBL.m2p7dkntbl   = 0x%p\n", &ioProTbl.sro1Tbl.m2p7dkntbl);
        // SRO Unit(pipe[2])
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.sdc0gd0      = 0x%p\n", &ioProTbl.sro2Tbl.sdc0gd0);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.sdc0gd1      = 0x%p\n", &ioProTbl.sro2Tbl.sdc0gd1);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.sdc1gd0      = 0x%p\n", &ioProTbl.sro2Tbl.sdc1gd0);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.sdc1gd1      = 0x%p\n", &ioProTbl.sro2Tbl.sdc1gd1);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.p2m0kntbl    = 0x%p\n", &ioProTbl.sro2Tbl.p2m0kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.p2m1kntbl    = 0x%p\n", &ioProTbl.sro2Tbl.p2m1kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.p2m2kntbl    = 0x%p\n", &ioProTbl.sro2Tbl.p2m2kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.p2m3kntbl    = 0x%p\n", &ioProTbl.sro2Tbl.p2m3kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.p2m4kntbl    = 0x%p\n", &ioProTbl.sro2Tbl.p2m4kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.p2m5kntbl    = 0x%p\n", &ioProTbl.sro2Tbl.p2m5kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.m2p0dkntbl   = 0x%p\n", &ioProTbl.sro2Tbl.m2p0dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.m2p1dkntbl   = 0x%p\n", &ioProTbl.sro2Tbl.m2p1dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.m2p6dkntbl   = 0x%p\n", &ioProTbl.sro2Tbl.m2p6dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[2]_TBL.m2p7dkntbl   = 0x%p\n", &ioProTbl.sro2Tbl.m2p7dkntbl);
        // SRO Unit(pipe[3])
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.sdc0gd0      = 0x%p\n", &ioProTbl.sro3Tbl.sdc0gd0);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.sdc0gd1      = 0x%p\n", &ioProTbl.sro3Tbl.sdc0gd1);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.sdc1gd0      = 0x%p\n", &ioProTbl.sro3Tbl.sdc1gd0);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.sdc1gd1      = 0x%p\n", &ioProTbl.sro3Tbl.sdc1gd1);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.p2m0kntbl    = 0x%p\n", &ioProTbl.sro3Tbl.p2m0kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.p2m1kntbl    = 0x%p\n", &ioProTbl.sro3Tbl.p2m1kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.p2m2kntbl    = 0x%p\n", &ioProTbl.sro3Tbl.p2m2kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.p2m3kntbl    = 0x%p\n", &ioProTbl.sro3Tbl.p2m3kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.p2m4kntbl    = 0x%p\n", &ioProTbl.sro3Tbl.p2m4kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.p2m5kntbl    = 0x%p\n", &ioProTbl.sro3Tbl.p2m5kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.m2p0dkntbl   = 0x%p\n", &ioProTbl.sro3Tbl.m2p0dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.m2p1dkntbl   = 0x%p\n", &ioProTbl.sro3Tbl.m2p1dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.m2p6dkntbl   = 0x%p\n", &ioProTbl.sro3Tbl.m2p6dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.SRO[3]_TBL.m2p7dkntbl   = 0x%p\n", &ioProTbl.sro3Tbl.m2p7dkntbl);
        // B2B Unit(pipe[1])
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[1]_TBL.fshdctbl0    = 0x%p\n", &ioProTbl.b2b1Tbl.fshdctbl0);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[1]_TBL.fshdctbl1    = 0x%p\n", &ioProTbl.b2b1Tbl.fshdctbl1);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[1]_TBL.p2m0knetbl   = 0x%p\n", &ioProTbl.b2b1Tbl.p2m0knetbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[1]_TBL.p2m1knetbl   = 0x%p\n", &ioProTbl.b2b1Tbl.p2m1knetbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[1]_TBL.m2p0dkntbl   = 0x%p\n", &ioProTbl.b2b1Tbl.m2p0dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[1]_TBL.m2p1dkntbl   = 0x%p\n", &ioProTbl.b2b1Tbl.m2p1dkntbl);
        // B2B Unit(pipe[2])
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[2]_TBL.fshdctbl0    = 0x%p\n", &ioProTbl.b2b2Tbl.fshdctbl0);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[2]_TBL.fshdctbl1    = 0x%p\n", &ioProTbl.b2b2Tbl.fshdctbl1);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[2]_TBL.p2m0knetbl   = 0x%p\n", &ioProTbl.b2b2Tbl.p2m0knetbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[2]_TBL.p2m1knetbl   = 0x%p\n", &ioProTbl.b2b2Tbl.p2m1knetbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[2]_TBL.m2p0dkntbl   = 0x%p\n", &ioProTbl.b2b2Tbl.m2p0dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[2]_TBL.m2p1dkntbl   = 0x%p\n", &ioProTbl.b2b2Tbl.m2p1dkntbl);
        // B2B Unit(pipe[3])
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[3]_TBL.fshdctbl0    = 0x%p\n", &ioProTbl.b2b3Tbl.fshdctbl0);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[3]_TBL.fshdctbl1    = 0x%p\n", &ioProTbl.b2b3Tbl.fshdctbl1);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[3]_TBL.p2m0knetbl   = 0x%p\n", &ioProTbl.b2b3Tbl.p2m0knetbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[3]_TBL.p2m1knetbl   = 0x%p\n", &ioProTbl.b2b3Tbl.p2m1knetbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[3]_TBL.m2p0dkntbl   = 0x%p\n", &ioProTbl.b2b3Tbl.m2p0dkntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.B2B[3]_TBL.m2p1dkntbl   = 0x%p\n", &ioProTbl.b2b3Tbl.m2p1dkntbl);
        // STAT Unit
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist0rdata     = 0x%p\n", &ioProTbl.statTbl.hist0rdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist0gdata     = 0x%p\n", &ioProTbl.statTbl.hist0gdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist0bdata     = 0x%p\n", &ioProTbl.statTbl.hist0bdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist0ydata     = 0x%p\n", &ioProTbl.statTbl.hist0ydata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist1rdata     = 0x%p\n", &ioProTbl.statTbl.hist1rdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist1gdata     = 0x%p\n", &ioProTbl.statTbl.hist1gdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist1bdata     = 0x%p\n", &ioProTbl.statTbl.hist1bdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist1ydata     = 0x%p\n", &ioProTbl.statTbl.hist1ydata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist2rdata     = 0x%p\n", &ioProTbl.statTbl.hist2rdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist2gdata     = 0x%p\n", &ioProTbl.statTbl.hist2gdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist2bdata     = 0x%p\n", &ioProTbl.statTbl.hist2bdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist2ydata     = 0x%p\n", &ioProTbl.statTbl.hist2ydata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist3rdata     = 0x%p\n", &ioProTbl.statTbl.hist3rdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist3gdata     = 0x%p\n", &ioProTbl.statTbl.hist3gdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist3bdata     = 0x%p\n", &ioProTbl.statTbl.hist3bdata);
        K_IO_TEST_RS_PRINTF("ioProTbl.statTbl.hist3ydata     = 0x%p\n", &ioProTbl.statTbl.hist3ydata);
        // pas Unit
        K_IO_TEST_RS_PRINTF("ioProTbl.pasTbl.spttbl0         = 0x%p\n", &ioProTbl.pasTbl.spttbl0);
        K_IO_TEST_RS_PRINTF("ioProTbl.pasTbl.spttbl1         = 0x%p\n", &ioProTbl.pasTbl.spttbl1);
        K_IO_TEST_RS_PRINTF("ioProTbl.pasTbl.p2m0kntbl       = 0x%p\n", &ioProTbl.pasTbl.p2m0kntbl);
        K_IO_TEST_RS_PRINTF("ioProTbl.pasTbl.m2p0dkntbl      = 0x%p\n", &ioProTbl.pasTbl.m2p0dkntbl);
    }
#endif  /** PRO-TABLE **/
}

void k_io_test_iip_test(KIoTest *self)
{
// for PC debug
#if 0
#define ioIip      (*IO_IIP2)
#define ioIipTbl  (*IO_IIP2_TBL)
    volatile IoIip* IO_IIP2 = (kpointer)0x200C0000;
    volatile IoIipRam* IO_IIP2_TBL = (kpointer)0x24100000;
#endif
    K_IO_TEST_RS_PRINTF("IIP\n");
#if 0
    K_IO_TEST_RS_PRINTF("ioIip.izactl0                    = %lX\n", (kulong)&ioIip.izactl0);
    K_IO_TEST_RS_PRINTF("ioIip.izactl1                    = %lX\n", (kulong)&ioIip.izactl1);
    K_IO_TEST_RS_PRINTF("ioIip.izactl2                    = %lX\n", (kulong)&ioIip.izactl2);
    K_IO_TEST_RS_PRINTF("ioIip.inten0                     = %lX\n", (kulong)&ioIip.inten0);
    K_IO_TEST_RS_PRINTF("ioIip.inten1                     = %lX\n", (kulong)&ioIip.inten1);
    K_IO_TEST_RS_PRINTF("ioIip.inten2                     = %lX\n", (kulong)&ioIip.inten2);
    K_IO_TEST_RS_PRINTF("ioIip.intiz0                     = %lX\n", (kulong)&ioIip.intiz0);
    K_IO_TEST_RS_PRINTF("ioIip.intiz1                     = %lX\n", (kulong)&ioIip.intiz1);
    K_IO_TEST_RS_PRINTF("ioIip.intiz2                     = %lX\n", (kulong)&ioIip.intiz2);
    K_IO_TEST_RS_PRINTF("ioIip.pftrewtflg                 = %lX\n", (kulong)&ioIip.pftrewtflg);
    K_IO_TEST_RS_PRINTF("ioIip.pftrewt                    = %lX\n", (kulong)&ioIip.pftrewt);
    K_IO_TEST_RS_PRINTF("ioIip.pdcctl                     = %lX\n", (kulong)&ioIip.pdcctl);
    K_IO_TEST_RS_PRINTF("ioIip.pdcrac                     = %lX\n", (kulong)&ioIip.pdcrac);
    K_IO_TEST_RS_PRINTF("ioIip.pdcrmc                     = %lX\n", (kulong)&ioIip.pdcrmc);
    K_IO_TEST_RS_PRINTF("ioIip.genline.genline1           = %lX\n", (kulong)&ioIip.genline.genline1);
    K_IO_TEST_RS_PRINTF("ioIip.genline.genline2           = %lX\n", (kulong)&ioIip.genline.genline2);
    K_IO_TEST_RS_PRINTF("ioIip.genline.genline3           = %lX\n", (kulong)&ioIip.genline.genline3);
    K_IO_TEST_RS_PRINTF("ioIip.genline.genline4           = %lX\n", (kulong)&ioIip.genline.genline4);
    K_IO_TEST_RS_PRINTF("ioIip.lkslCtl                   = %lX\n", (kulong)&ioIip.lkslCtl);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl0           = %lX\n", (kulong)&ioIip.lineValIntSl0);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl1           = %lX\n", (kulong)&ioIip.lineValIntSl1);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl2           = %lX\n", (kulong)&ioIip.lineValIntSl2);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl3           = %lX\n", (kulong)&ioIip.lineValIntSl3);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl4           = %lX\n", (kulong)&ioIip.lineValIntSl4);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl5           = %lX\n", (kulong)&ioIip.lineValIntSl5);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl6           = %lX\n", (kulong)&ioIip.lineValIntSl6);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl7           = %lX\n", (kulong)&ioIip.lineValIntSl7);
    K_IO_TEST_RS_PRINTF("ioIip.lineValIntSl8           = %lX\n", (kulong)&ioIip.lineValIntSl8);
    K_IO_TEST_RS_PRINTF("ioIip.dpaxictl                   = %lX\n", (kulong)&ioIip.dpaxictl);
    K_IO_TEST_RS_PRINTF("ioIip.afnaxictl                  = %lX\n", (kulong)&ioIip.afnaxictl);
    K_IO_TEST_RS_PRINTF("ioIip.fraxictl                   = %lX\n", (kulong)&ioIip.fraxictl);
    K_IO_TEST_RS_PRINTF("ioIip.gpcaxictl                  = %lX\n", (kulong)&ioIip.gpcaxictl);
    K_IO_TEST_RS_PRINTF("ioIip.slaxictl.slaxictl1         = %lX\n", (kulong)&ioIip.slaxictl.slaxictl1);
    K_IO_TEST_RS_PRINTF("ioIip.slaxictl.slaxictl2         = %lX\n", (kulong)&ioIip.slaxictl.slaxictl2);
    K_IO_TEST_RS_PRINTF("ioIip.slaxictl.slaxictl3         = %lX\n", (kulong)&ioIip.slaxictl.slaxictl3);
    K_IO_TEST_RS_PRINTF("ioIip.slaxictl.slaxictl4         = %lX\n", (kulong)&ioIip.slaxictl.slaxictl4);
    K_IO_TEST_RS_PRINTF("ioIip.slaxictl.slaxictl5         = %lX\n", (kulong)&ioIip.slaxictl.slaxictl5);
    K_IO_TEST_RS_PRINTF("ioIip.axrsts                     = %lX\n", (kulong)&ioIip.axrsts);
    K_IO_TEST_RS_PRINTF("ioIip.axwsts                     = %lX\n", (kulong)&ioIip.axwsts);
    K_IO_TEST_RS_PRINTF("ioIip.ahbsts                     = %lX\n", (kulong)&ioIip.ahbsts);
    K_IO_TEST_RS_PRINTF("ioIip.acesen0                    = %lX\n", (kulong)&ioIip.acesen0);
    K_IO_TEST_RS_PRINTF("ioIip.dtoutMon                  = %lX\n", (kulong)&ioIip.dtoutMon);
    K_IO_TEST_RS_PRINTF("ioIip.waitMon                   = %lX\n", (kulong)&ioIip.waitMon);
    K_IO_TEST_RS_PRINTF("ioIip.pdcDtoutMon              = %lX\n", (kulong)&ioIip.pdcDtoutMon);
    K_IO_TEST_RS_PRINTF("ioIip.pdcRdyMon                = %lX\n", (kulong)&ioIip.pdcRdyMon);

    K_IO_TEST_RS_PRINTF("ioIip.histmax                    = %lX\n", (kulong)&ioIip.histmax);
    K_IO_TEST_RS_PRINTF("ioIip.maxmon                     = %lX\n", (kulong)&ioIip.maxmon);
    K_IO_TEST_RS_PRINTF("ioIip.minmon                     = %lX\n", (kulong)&ioIip.minmon);
    K_IO_TEST_RS_PRINTF("ioIip.addmon                     = %lX\n", (kulong)&ioIip.addmon);
    K_IO_TEST_RS_PRINTF("ioIip.moninit                    = %lX\n", (kulong)&ioIip.moninit);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[0]               = %lX\n", (kulong)&ioIip.pixfmttbl[0]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[1]               = %lX\n", (kulong)&ioIip.pixfmttbl[1]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[2]               = %lX\n", (kulong)&ioIip.pixfmttbl[2]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[3]               = %lX\n", (kulong)&ioIip.pixfmttbl[3]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[4]               = %lX\n", (kulong)&ioIip.pixfmttbl[4]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[5]               = %lX\n", (kulong)&ioIip.pixfmttbl[5]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[6]               = %lX\n", (kulong)&ioIip.pixfmttbl[6]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[7]               = %lX\n", (kulong)&ioIip.pixfmttbl[7]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[8]               = %lX\n", (kulong)&ioIip.pixfmttbl[8]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[9]               = %lX\n", (kulong)&ioIip.pixfmttbl[9]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[10]              = %lX\n", (kulong)&ioIip.pixfmttbl[10]);
    K_IO_TEST_RS_PRINTF("ioIip.pixfmttbl[11]              = %lX\n", (kulong)&ioIip.pixfmttbl[11]);

    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd0.unitinftbl0 = %lX\n", (kulong)&ioIip.unitinftblLd0.unitinftbl0);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd0.unitinftbl1 = %lX\n", (kulong)&ioIip.unitinftblLd0.unitinftbl1);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd0.unitinftbl2 = %lX\n", (kulong)&ioIip.unitinftblLd0.unitinftbl2);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd0.unitsr      = %lX\n", (kulong)&ioIip.unitinftblLd0.unitsr);

    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd1             = %lX\n", (kulong)&ioIip.unitinftblLd1);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd2             = %lX\n", (kulong)&ioIip.unitinftblLd2);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd3             = %lX\n", (kulong)&ioIip.unitinftblLd3);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblFlt             = %lX\n", (kulong)&ioIip.unitinftblFlt);

    K_IO_TEST_RS_PRINTF("ioIip.unitinftblAfn0            = %lX\n", (kulong)&ioIip.unitinftblAfn0);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblAfn1            = %lX\n", (kulong)&ioIip.unitinftblAfn1);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblAfn2            = %lX\n", (kulong)&ioIip.unitinftblAfn2);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblFrc0            = %lX\n", (kulong)&ioIip.unitinftblFrc0);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblMon             = %lX\n", (kulong)&ioIip.unitinftblMon);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl0             = %lX\n", (kulong)&ioIip.unitinftblSl0);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl1             = %lX\n", (kulong)&ioIip.unitinftblSl1);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl2             = %lX\n", (kulong)&ioIip.unitinftblSl2);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl3             = %lX\n", (kulong)&ioIip.unitinftblSl3);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl4             = %lX\n", (kulong)&ioIip.unitinftblSl4);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl5             = %lX\n", (kulong)&ioIip.unitinftblSl5);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblCsc0            = %lX\n", (kulong)&ioIip.unitinftblCsc0);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblCsc1            = %lX\n", (kulong)&ioIip.unitinftblCsc1);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLut             = %lX\n", (kulong)&ioIip.unitinftblLut);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblGpc             = %lX\n", (kulong)&ioIip.unitinftblGpc);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblBld0            = %lX\n", (kulong)&ioIip.unitinftblBld0);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblBld1            = %lX\n", (kulong)&ioIip.unitinftblBld1);

    K_IO_TEST_RS_PRINTF("ioIip.unitinftblFrc1            = %lX\n", (kulong)&ioIip.unitinftblFrc1);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblCfl0            = %lX\n", (kulong)&ioIip.unitinftblCfl0);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblCsc2            = %lX\n", (kulong)&ioIip.unitinftblCsc2);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblCsc3            = %lX\n", (kulong)&ioIip.unitinftblCsc3);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl6             = %lX\n", (kulong)&ioIip.unitinftblSl6);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl7             = %lX\n", (kulong)&ioIip.unitinftblSl7);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblSl8             = %lX\n", (kulong)&ioIip.unitinftblSl8);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd4             = %lX\n", (kulong)&ioIip.unitinftblLd4);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd5             = %lX\n", (kulong)&ioIip.unitinftblLd5);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd6             = %lX\n", (kulong)&ioIip.unitinftblLd6);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblLd7             = %lX\n", (kulong)&ioIip.unitinftblLd7);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblAfn3            = %lX\n", (kulong)&ioIip.unitinftblAfn3);
    K_IO_TEST_RS_PRINTF("ioIip.unitinftblMft             = %lX\n", (kulong)&ioIip.unitinftblMft);

    K_IO_TEST_RS_PRINTF("ioIipTbl.lutram[0]              = %lX\n", (kulong)&ioIipTbl.lutram.lutram.bit[0][0]);    // LUTA
    K_IO_TEST_RS_PRINTF("ioIipTbl.lutram[1]              = %lX\n", (kulong)&ioIipTbl.lutram.lutram.bit[1][0]);    // LUTD
    K_IO_TEST_RS_PRINTF("ioIipTbl.lutram[2]              = %lX\n", (kulong)&ioIipTbl.lutram.lutram.bit[2][0]);    // LUTB
    K_IO_TEST_RS_PRINTF("ioIipTbl.lutram[3]              = %lX\n", (kulong)&ioIipTbl.lutram.lutram.bit[3][0]);    // LUTE
    K_IO_TEST_RS_PRINTF("ioIipTbl.lutram[4]              = %lX\n", (kulong)&ioIipTbl.lutram.lutram.bit[4][0]);    // LUTC
    K_IO_TEST_RS_PRINTF("ioIipTbl.lutram[5]              = %lX\n", (kulong)&ioIipTbl.lutram.lutram.bit[5][0]);    // LUTF
    K_IO_TEST_RS_PRINTF("ioIipTbl.histgram[0]            = %lX\n", (kulong)&ioIipTbl.histgram.histgram.bit[0][0]);
    K_IO_TEST_RS_PRINTF("ioIipTbl.histgram[1]            = %lX\n", (kulong)&ioIipTbl.histgram.histgram.bit[1][0]);
    K_IO_TEST_RS_PRINTF("ioIipTbl.histgram[2]            = %lX\n", (kulong)&ioIipTbl.histgram.histgram.bit[2][0]);
    K_IO_TEST_RS_PRINTF("ioIipTbl.histgram[3]            = %lX\n", (kulong)&ioIipTbl.histgram.histgram.bit[3][0]);
#endif
}

void k_io_test_audio_test(KIoTest *self)
{
#if 0
#define ioAudio           (*ioAudio2)
    volatile IoAudio* ioAudio2 = (kpointer)0x1E200000;
//  volatile io_audio* ioAudio2;
//  ioAudio2 = (kpointer)0x1E200000;
#endif
    K_IO_TEST_RS_PRINTF("Audio I/F\n");
#if 0
    kint loop;

    K_IO_TEST_RS_PRINTF("ioAudio.audioifCtrl.aures     = %lx\n", (kulong)&ioAudio.audioifCtrl.aures);
    K_IO_TEST_RS_PRINTF("ioAudio.audioifCtrl.auioe     = %lx\n", (kulong)&ioAudio.audioifCtrl.auioe);
    K_IO_TEST_RS_PRINTF("ioAudio.audioifCtrl.aulbe     = %lx\n", (kulong)&ioAudio.audioifCtrl.aulbe);
    K_IO_TEST_RS_PRINTF(" \n");
    for (loop = 0; loop < 6; loop++){
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auidlr      = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auidlr);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auodlr      = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auodlr);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].aucr        = %lx\n", loop, (kulong)&ioAudio.audioif[loop].aucr);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].aumd        = %lx\n", loop, (kulong)&ioAudio.audioif[loop].aumd);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].aust        = %lx\n", loop, (kulong)&ioAudio.audioif[loop].aust);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].aucc        = %lx\n", loop, (kulong)&ioAudio.audioif[loop].aucc);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].audp        = %lx\n", loop, (kulong)&ioAudio.audioif[loop].audp);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auifst      = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auifst);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auofst      = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auofst);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auidl       = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auidl);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auidr       = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auidr);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auodl       = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auodl);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auodr       = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auodr);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auiddmapt   = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auiddmapt);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].auoddmapt   = %lx\n", loop, (kulong)&ioAudio.audioif[loop].auoddmapt);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].audma2ctl   = %lx\n", loop, (kulong)&ioAudio.audioif[loop].audma2ctl);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].audmisample = %lx\n", loop, (kulong)&ioAudio.audioif[loop].audmisample);
        K_IO_TEST_RS_PRINTF("ioAudio.audioif[%d].audmosample = %lx\n", loop, (kulong)&ioAudio.audioif[loop].audmosample);
        K_IO_TEST_RS_PRINTF(" \n");
    }
#endif
}

void k_io_test_hdmi_test(KIoTest *self)
{
// for PC debug
#if 0
#define ioHdmi          (*IO_HDMI2)
    volatile union IoHdmi* IO_HDMI2 = (kpointer)0x2C018000;
#endif
    K_IO_TEST_RS_PRINTF("HDMI\n");
#if 0
    /* io_hdmi_page0 */
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vndId                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.vndId);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.devId                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.devId);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.devRev                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.devRev);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.srst                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.srst);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.sysCtrl1                = %lx\n", (kulong)&ioHdmi.hdmiPage0.sysCtrl1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.sysStat                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.sysStat);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.sysCtrl3                = %lx\n", (kulong)&ioHdmi.hdmiPage0.sysCtrl3);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.dctl                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.dctl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.hdcpCtrl                = %lx\n", (kulong)&ioHdmi.hdmiPage0.hdcpCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.bksv                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.bksv);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.anM0                    = %lx\n", (kulong)&ioHdmi.hdmiPage0.anM0);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.aksv                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.aksv);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ri                       = %lx\n", (kulong)&ioHdmi.hdmiPage0.ri);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ri128Comp              = %lx\n", (kulong)&ioHdmi.hdmiPage0.ri128Comp);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.iCnt                    = %lx\n", (kulong)&ioHdmi.hdmiPage0.iCnt);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.riStat                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.riStat);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.riCmd                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.riCmd);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.riStart                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.riStart);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.riRx                    = %lx\n", (kulong)&ioHdmi.hdmiPage0.riRx);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.deCtrl                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.deCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.deTop                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.deTop);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.deCnt                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.deCnt);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.deLin                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.deLin);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.hres                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.hres);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vres                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.vres);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.iadjust                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.iadjust);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.polDetect               = %lx\n", (kulong)&ioHdmi.hdmiPage0.polDetect);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.hbit2hsync              = %lx\n", (kulong)&ioHdmi.hdmiPage0.hbit2hsync);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.fld2HsOfst             = %lx\n", (kulong)&ioHdmi.hdmiPage0.fld2HsOfst);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.hwidth                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.hwidth);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vbitToVsync            = %lx\n", (kulong)&ioHdmi.hdmiPage0.vbitToVsync);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vwidth                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.vwidth);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vidCtrl                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.vidCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vidAcen                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.vidAcen);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vidMode                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.vidMode);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vidBlank                = %lx\n", (kulong)&ioHdmi.hdmiPage0.vidBlank);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.dcHeader                = %lx\n", (kulong)&ioHdmi.hdmiPage0.dcHeader);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.vidDither               = %lx\n", (kulong)&ioHdmi.hdmiPage0.vidDither);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.rgb2xvccCt              = %lx\n", (kulong)&ioHdmi.hdmiPage0.rgb2xvccCt);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.r2yCoeff                = %lx\n", (kulong)&ioHdmi.hdmiPage0.r2yCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.g2yCoeff                = %lx\n", (kulong)&ioHdmi.hdmiPage0.g2yCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.b2yCoeff                = %lx\n", (kulong)&ioHdmi.hdmiPage0.b2yCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.r2cbCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.r2cbCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.g2cbCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.g2cbCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.b2cbCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.b2cbCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.r2crCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.r2crCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.g2crCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.g2crCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.b2crCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.b2crCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.rgbOffset               = %lx\n", (kulong)&ioHdmi.hdmiPage0.rgbOffset);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.yOffset                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.yOffset);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cbcrOffset              = %lx\n", (kulong)&ioHdmi.hdmiPage0.cbcrOffset);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.intrState               = %lx\n", (kulong)&ioHdmi.hdmiPage0.intrState);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.intr.intr1               = %lx\n", (kulong)&ioHdmi.hdmiPage0.intr.intr1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.intr.intr2               = %lx\n", (kulong)&ioHdmi.hdmiPage0.intr.intr2);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.intr.intr3               = %lx\n", (kulong)&ioHdmi.hdmiPage0.intr.intr3);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.intr.intr4               = %lx\n", (kulong)&ioHdmi.hdmiPage0.intr.intr4);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.unmask.intUnmask1       = %lx\n", (kulong)&ioHdmi.hdmiPage0.unmask.intUnmask1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.unmask.intUnmask2       = %lx\n", (kulong)&ioHdmi.hdmiPage0.unmask.intUnmask2);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.unmask.intUnmask3       = %lx\n", (kulong)&ioHdmi.hdmiPage0.unmask.intUnmask3);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.unmask.intUnmask4       = %lx\n", (kulong)&ioHdmi.hdmiPage0.unmask.intUnmask4);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.intCtrl                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.intCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.tmdsCtrl                = %lx\n", (kulong)&ioHdmi.hdmiPage0.tmdsCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.xvycc2rgbCtrl           = %lx\n", (kulong)&ioHdmi.hdmiPage0.xvycc2rgbCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.y2rCoeff                = %lx\n", (kulong)&ioHdmi.hdmiPage0.y2rCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cr2rCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.cr2rCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cb2bCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.cb2bCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cr2gCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.cr2gCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cb2gCoeff               = %lx\n", (kulong)&ioHdmi.hdmiPage0.cb2gCoeff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.yoffset                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.yoffset);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.offset1                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.offset1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.offset2                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.offset2);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.dclevel                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.dclevel);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.m0Read                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.m0Read);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.txksvFifo               = %lx\n", (kulong)&ioHdmi.hdmiPage0.txksvFifo);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.txdsBstatus1            = %lx\n", (kulong)&ioHdmi.hdmiPage0.txdsBstatus1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.txdsBstatus2            = %lx\n", (kulong)&ioHdmi.hdmiPage0.txdsBstatus2);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.txvh                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.txvh);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcMan                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcMan);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcAddr                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcAddr);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcSegm                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcSegm);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcOffset               = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcOffset);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcCount                = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcCount);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcStatus               = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcStatus);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcCmd                  = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcCmd);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcData                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcData);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ddcFifoCnt             = %lx\n", (kulong)&ioHdmi.hdmiPage0.ddcFifoCnt);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.epst                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.epst);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.epcm                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.epcm);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.regBank                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.regBank);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.acrCtrl                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.acrCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.freqSval                = %lx\n", (kulong)&ioHdmi.hdmiPage0.freqSval);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.nSval                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.nSval);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ctsSval                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.ctsSval);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.ctsHval                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.ctsHval);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.audMode                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.audMode);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.spdifCtrl               = %lx\n", (kulong)&ioHdmi.hdmiPage0.spdifCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.hwSpdifFs              = %lx\n", (kulong)&ioHdmi.hdmiPage0.hwSpdifFs);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.swapI2s                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.swapI2s);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.spdifErth               = %lx\n", (kulong)&ioHdmi.hdmiPage0.spdifErth);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.i2sInMap               = %lx\n", (kulong)&ioHdmi.hdmiPage0.i2sInMap);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.i2sInCtrl              = %lx\n", (kulong)&ioHdmi.hdmiPage0.i2sInCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.i2sChst                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.i2sChst);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.asrc                     = %lx\n", (kulong)&ioHdmi.hdmiPage0.asrc);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.i2sInLen               = %lx\n", (kulong)&ioHdmi.hdmiPage0.i2sInLen);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.hdmiCtrl                = %lx\n", (kulong)&ioHdmi.hdmiPage0.hdmiCtrl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.audoTxstat              = %lx\n", (kulong)&ioHdmi.hdmiPage0.audoTxstat);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.dpd                      = %lx\n", (kulong)&ioHdmi.hdmiPage0.dpd);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.pbCtrl1                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.pbCtrl1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.pbCtrl2                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.pbCtrl2);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.packet.aviType          = %lx\n", (kulong)&ioHdmi.hdmiPage0.packet.aviType);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.packet.aviVers          = %lx\n", (kulong)&ioHdmi.hdmiPage0.packet.aviVers);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.packet.aviLen           = %lx\n", (kulong)&ioHdmi.hdmiPage0.packet.aviLen);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.packet.aviChsum         = %lx\n", (kulong)&ioHdmi.hdmiPage0.packet.aviChsum);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.packet.aviDbyte[0]      = %lx\n", (kulong)&ioHdmi.hdmiPage0.packet.aviDbyte[0]);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.packet.aviDbyte[14]     = %lx\n", (kulong)&ioHdmi.hdmiPage0.packet.aviDbyte[14]);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.spdInf.spdType         = %lx\n", (kulong)&ioHdmi.hdmiPage0.spdInf.spdType);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.spdInf.spdVers         = %lx\n", (kulong)&ioHdmi.hdmiPage0.spdInf.spdVers);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.spdInf.spdLen          = %lx\n", (kulong)&ioHdmi.hdmiPage0.spdInf.spdLen);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.spdInf.spdChsum        = %lx\n", (kulong)&ioHdmi.hdmiPage0.spdInf.spdChsum);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.spdInf.spdDbyte[0]     = %lx\n", (kulong)&ioHdmi.hdmiPage0.spdInf.spdDbyte[0]);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.spdInf.spdDbyte[26]    = %lx\n", (kulong)&ioHdmi.hdmiPage0.spdInf.spdDbyte[26]);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.audioInf.audioType     = %lx\n", (kulong)&ioHdmi.hdmiPage0.audioInf.audioType);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.audioInf.audioVers     = %lx\n", (kulong)&ioHdmi.hdmiPage0.audioInf.audioVers);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.audioInf.audioLen      = %lx\n", (kulong)&ioHdmi.hdmiPage0.audioInf.audioLen);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.audioInf.audioChsum    = %lx\n", (kulong)&ioHdmi.hdmiPage0.audioInf.audioChsum);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.audioInf.audioDbyte[0] = %lx\n", (kulong)&ioHdmi.hdmiPage0.audioInf.audioDbyte[0]);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.audioInf.audioDbyte[9] = %lx\n", (kulong)&ioHdmi.hdmiPage0.audioInf.audioDbyte[9]);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.mpegInf.mpegType       = %lx\n", (kulong)&ioHdmi.hdmiPage0.mpegInf.mpegType);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.mpegInf.mpegVers       = %lx\n", (kulong)&ioHdmi.hdmiPage0.mpegInf.mpegVers);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.mpegInf.mpegLen        = %lx\n", (kulong)&ioHdmi.hdmiPage0.mpegInf.mpegLen);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.mpegInf.mpegChsum      = %lx\n", (kulong)&ioHdmi.hdmiPage0.mpegInf.mpegChsum);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.mpegInf.mpegDbyte[0]   = %lx\n", (kulong)&ioHdmi.hdmiPage0.mpegInf.mpegDbyte[0]);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.mpegInf.mpegDbyte[26]  = %lx\n", (kulong)&ioHdmi.hdmiPage0.mpegInf.mpegDbyte[26]);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.genDbyte                = %lx\n", (kulong)&ioHdmi.hdmiPage0.genDbyte);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cpByte1                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.cpByte1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.gen2Dbyte               = %lx\n", (kulong)&ioHdmi.hdmiPage0.gen2Dbyte);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecDevId               = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecDevId);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecSpec                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecSpec);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecSuff                 = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecSuff);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecFw                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecFw);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecTxFl                = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecTxFl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecTxInit              = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecTxInit);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecTxDest              = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecTxDest);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecTxCommand           = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecTxCommand);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecTxOperand           = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecTxOperand);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecTransmitData        = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecTransmitData);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecTxRetryLimit       = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecTxRetryLimit);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecCa                   = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecCa);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecIntEnable0         = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecIntEnable0);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecIntEnable1         = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecIntEnable1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecIntStatus0         = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecIntStatus0);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecIntStatus1         = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecIntStatus1);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecRxControl           = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecRxControl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecRxCount             = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecRxCount);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecRxCmdHeader        = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecRxCmdHeader);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecRxCommand           = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecRxCommand);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecRxOperand           = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecRxOperand);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecOpAbort             = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecOpAbort);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecAutoPoingControl   = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecAutoPoingControl);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage0.cecAutoPingMap        = %lx\n", (kulong)&ioHdmi.hdmiPage0.cecAutoPingMap);

    /* io_hdmi_page2 */
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage2.gamut.gamutHeader       = %lx\n", (kulong)&ioHdmi.hdmiPage2.gamut.gamutHeader);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage2.gamut.gamutDbyte        = %lx\n", (kulong)&ioHdmi.hdmiPage2.gamut.gamutDbyte);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage2.regBank                 = %lx\n", (kulong)&ioHdmi.hdmiPage2.regBank);
    K_IO_TEST_RS_PRINTF("ioHdmi.hdmiPage2.pbCtrl2                 = %lx\n", (kulong)&ioHdmi.hdmiPage2.pbCtrl2);

    K_IO_TEST_RS_PRINTF(" \n");
#endif
}

KIoTest* k_io_test_new(void)
{
    KIoTest* self = k_object_new_with_private(K_TYPE_IO_TEST, sizeof(KIoTestPrivate));
    return self;
}
