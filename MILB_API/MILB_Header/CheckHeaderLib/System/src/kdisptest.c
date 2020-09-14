/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :郑蛘钊
*@brief             :kdisptest
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
#include "kdisptest.h"


K_TYPE_DEFINE_WITH_PRIVATE(KDispTest, k_disp_test);

#define K_DISP_TEST_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KDispTestPrivate, K_TYPE_DISP_TEST))

#define K_DISP_TEST_RS_PRINTF printf


struct  _KDispTestPrivate
{

};
/**
 *IMPL
 */
static void k_disp_test_constructor(KDispTest *self)
{
//	KDispTestPrivate *priv = K_DISP_TEST_GET_PRIVATE(self);
}

static void k_disp_test_destructor(KDispTest *self)
{
//	KDispTestPrivate *priv = K_DISP_TEST_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
void k_disp_test_disp_test(KDispTest *self)
{
// for PC debug
#if 0
#define ioDisp     (*ioDisp2)
#define ioDispTbl (*ioDisp2Tbl)
    volatile IoJdsdisp* ioDisp2 = (kpointer)0x200F0000;
    volatile IoJdsdispTbl* ioDisp2Tbl = (kpointer)0x24080000;
#endif
    K_DISP_TEST_RS_PRINTF("DISP\n");
#if 0
    /* io_jdslch */
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lrst           = %lx\n", (kulong)&ioDisp.main.lch.lrst);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ltrg           = %lx\n", (kulong)&ioDisp.main.lch.ltrg);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lrpgctl        = %lx\n", (kulong)&ioDisp.main.lch.lrpgctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lidt           = %lx\n", (kulong)&ioDisp.main.lch.lidt);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lisize         = %lx\n", (kulong)&ioDisp.main.lch.lisize);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lysa[0]        = %lx\n", (kulong)&ioDisp.main.lch.lysa[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lysa[3]        = %lx\n", (kulong)&ioDisp.main.lch.lysa[3]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lcsa0[0]       = %lx\n", (kulong)&ioDisp.main.lch.lcsa0[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lcsa0[3]       = %lx\n", (kulong)&ioDisp.main.lch.lcsa0[3]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lyhga          = %lx\n", (kulong)&ioDisp.main.lch.lyhga);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lchga          = %lx\n", (kulong)&ioDisp.main.lch.lchga);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.libctl         = %lx\n", (kulong)&ioDisp.main.lch.libctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lercv          = %lx\n", (kulong)&ioDisp.main.lch.lercv);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lhrsz0         = %lx\n", (kulong)&ioDisp.main.lch.lhrsz0);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lhrsz1         = %lx\n", (kulong)&ioDisp.main.lch.lhrsz1);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lvrsz          = %lx\n", (kulong)&ioDisp.main.lch.lvrsz);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lywth          = %lx\n", (kulong)&ioDisp.main.lch.lywth);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lywhs0         = %lx\n", (kulong)&ioDisp.main.lch.lywhs0);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lywhs1         = %lx\n", (kulong)&ioDisp.main.lch.lywhs1);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lywls0         = %lx\n", (kulong)&ioDisp.main.lch.lywls0);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lywls1         = %lx\n", (kulong)&ioDisp.main.lch.lywls1);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lbltmr         = %lx\n", (kulong)&ioDisp.main.lch.lbltmr);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ldrectl        = %lx\n", (kulong)&ioDisp.main.lch.ldrectl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ldreycal       = %lx\n", (kulong)&ioDisp.main.lch.ldreycal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ldrecbcal      = %lx\n", (kulong)&ioDisp.main.lch.ldrecbcaL);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ldrecrcal      = %lx\n", (kulong)&ioDisp.main.lch.ldrecrcaL);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ly2r[0]        = %lx\n", (kulong)&ioDisp.main.lch.ly2r[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ly2r[2]        = %lx\n", (kulong)&ioDisp.main.lch.ly2r[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ltblaset       = %lx\n", (kulong)&ioDisp.main.lch.ltblaset);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lcc[0]         = %lx\n", (kulong)&ioDisp.main.lch.lcc[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lcc[2]         = %lx\n", (kulong)&ioDisp.main.lch.lcc[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ltcycal        = %lx\n", (kulong)&ioDisp.main.lch.ltcycal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ltcctl         = %lx\n", (kulong)&ioDisp.main.lch.ltcctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ldispen        = %lx\n", (kulong)&ioDisp.main.lch.ldispen);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.ldsta          = %lx\n", (kulong)&ioDisp.main.lch.ldsta);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.lch.lrevdisp       = %lx\n", (kulong)&ioDisp.main.lch.lrevdisp);

    /* io_jdsdcore */
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.reset        = %lx\n", (kulong)&ioDisp.main.dcore.reset);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ifs          = %lx\n", (kulong)&ioDisp.main.dcore.ifs);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.trg          = %lx\n", (kulong)&ioDisp.main.dcore.trg);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.toctl        = %lx\n", (kulong)&ioDisp.main.dcore.toctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.intc         = %lx\n", (kulong)&ioDisp.main.dcore.intc);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.inte         = %lx\n", (kulong)&ioDisp.main.dcore.inte);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.intf         = %lx\n", (kulong)&ioDisp.main.dcore.intf);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.axists       = %lx\n", (kulong)&ioDisp.main.dcore.axists);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.rpgctl       = %lx\n", (kulong)&ioDisp.main.dcore.rpgctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.rpgen        = %lx\n", (kulong)&ioDisp.main.dcore.rpgen);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.polsel       = %lx\n", (kulong)&ioDisp.main.dcore.polsel);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.tsl          = %lx\n", (kulong)&ioDisp.main.dcore.tsl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.vcyc         = %lx\n", (kulong)&ioDisp.main.dcore.vcyc);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.hcyc         = %lx\n", (kulong)&ioDisp.main.dcore.hcyc);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ovpw         = %lx\n", (kulong)&ioDisp.main.dcore.ovpw);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.hpw          = %lx\n", (kulong)&ioDisp.main.dcore.hpw);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.vblk         = %lx\n", (kulong)&ioDisp.main.dcore.vblk);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.hblk         = %lx\n", (kulong)&ioDisp.main.dcore.hblk);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.vdly         = %lx\n", (kulong)&ioDisp.main.dcore.vdly);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.hdly         = %lx\n", (kulong)&ioDisp.main.dcore.hdly);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ovsize       = %lx\n", (kulong)&ioDisp.main.dcore.ovsize);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ohsize       = %lx\n", (kulong)&ioDisp.main.dcore.ohsize);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.vrfctl       = %lx\n", (kulong)&ioDisp.main.dcore.vrfctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.hrfctl       = %lx\n", (kulong)&ioDisp.main.dcore.hrfctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.domd         = %lx\n", (kulong)&ioDisp.main.dcore.domd);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.fdoen        = %lx\n", (kulong)&ioDisp.main.dcore.fdoen);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.fodata       = %lx\n", (kulong)&ioDisp.main.dcore.fodata);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.blankdt      = %lx\n", (kulong)&ioDisp.main.dcore.blankdt);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.clbhsize     = %lx\n", (kulong)&ioDisp.main.dcore.clbhsize);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.clbdt[0]     = %lx\n", (kulong)&ioDisp.main.dcore.clbdt[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.clbdt[15]    = %lx\n", (kulong)&ioDisp.main.dcore.clbdt[15]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.bldctl       = %lx\n", (kulong)&ioDisp.main.dcore.bldctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.r2rctl       = %lx\n", (kulong)&ioDisp.main.dcore.r2rctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.r2y[0]       = %lx\n", (kulong)&ioDisp.main.dcore.r2y[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.r2y[2]       = %lx\n", (kulong)&ioDisp.main.dcore.r2y[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.yctl         = %lx\n", (kulong)&ioDisp.main.dcore.yctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ycal         = %lx\n", (kulong)&ioDisp.main.dcore.ycal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.yclip        = %lx\n", (kulong)&ioDisp.main.dcore.yclip);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.cbcal        = %lx\n", (kulong)&ioDisp.main.dcore.cbcal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.cbclip       = %lx\n", (kulong)&ioDisp.main.dcore.cbclip);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.crcal        = %lx\n", (kulong)&ioDisp.main.dcore.crcal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.crclip       = %lx\n", (kulong)&ioDisp.main.dcore.crclip);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.doctl0       = %lx\n", (kulong)&ioDisp.main.dcore.doctl0);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.doctl1       = %lx\n", (kulong)&ioDisp.main.dcore.doctl1);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.doctl2       = %lx\n", (kulong)&ioDisp.main.dcore.doctl2);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.trscode[0]   = %lx\n", (kulong)&ioDisp.main.dcore.trscode[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.trscode[1]   = %lx\n", (kulong)&ioDisp.main.dcore.trscode[1]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ghdsta       = %lx\n", (kulong)&ioDisp.main.dcore.ghdsta);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.gvdsta       = %lx\n", (kulong)&ioDisp.main.dcore.gvdsta);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.glength      = %lx\n", (kulong)&ioDisp.main.dcore.glength);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.gwidth       = %lx\n", (kulong)&ioDisp.main.dcore.gwidth);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.gitvl        = %lx\n", (kulong)&ioDisp.main.dcore.gitvl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.gnum         = %lx\n", (kulong)&ioDisp.main.dcore.gnum);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.gdctl        = %lx\n", (kulong)&ioDisp.main.dcore.gdctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.gdispen      = %lx\n", (kulong)&ioDisp.main.dcore.gdispen);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffdsta[0]    = %lx\n", (kulong)&ioDisp.main.dcore.ffdsta[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffdsta[15]   = %lx\n", (kulong)&ioDisp.main.dcore.ffdsta[15]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffsize[0]    = %lx\n", (kulong)&ioDisp.main.dcore.ffsize[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffsize[15]   = %lx\n", (kulong)&ioDisp.main.dcore.ffsize[15]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffwidth[0]   = %lx\n", (kulong)&ioDisp.main.dcore.ffwidth[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffwidth[15]  = %lx\n", (kulong)&ioDisp.main.dcore.ffwidth[15]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffclr[0]     = %lx\n", (kulong)&ioDisp.main.dcore.ffclr[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffclr[15]    = %lx\n", (kulong)&ioDisp.main.dcore.ffclr[15]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.dcore.ffdispen     = %lx\n", (kulong)&ioDisp.main.dcore.ffdispen);

    /* io_jdsgrch */
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grrst      = %lx\n", (kulong)&ioDisp.main.grch[0].grrst);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grtrg      = %lx\n", (kulong)&ioDisp.main.grch[0].grtrg);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grrpgctl   = %lx\n", (kulong)&ioDisp.main.grch[0].grrpgctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].gridt      = %lx\n", (kulong)&ioDisp.main.grch[0].gridt);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grtisize   = %lx\n", (kulong)&ioDisp.main.grch[0].grtisize);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grtdsta    = %lx\n", (kulong)&ioDisp.main.grch[0].grtdsta);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].gripo      = %lx\n", (kulong)&ioDisp.main.grch[0].gripo);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grscctl    = %lx\n", (kulong)&ioDisp.main.grch[0].grscctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grercv     = %lx\n", (kulong)&ioDisp.main.grch[0].grercv);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grisize[0] = %lx\n", (kulong)&ioDisp.main.grch[0].grisize[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grisize[9] = %lx\n", (kulong)&ioDisp.main.grch[0].grisize[9]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grsa0[0]   = %lx\n", (kulong)&ioDisp.main.grch[0].grsa0[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grsa0[3]   = %lx\n", (kulong)&ioDisp.main.grch[0].grsa0[3]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grsa[0]    = %lx\n", (kulong)&ioDisp.main.grch[0].grsa[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grsa[8]    = %lx\n", (kulong)&ioDisp.main.grch[0].grsa[8]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grhga[0]   = %lx\n", (kulong)&ioDisp.main.grch[0].grhga[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grhga[9]   = %lx\n", (kulong)&ioDisp.main.grch[0].grhga[9]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grdsta[0]  = %lx\n", (kulong)&ioDisp.main.grch[0].grdsta[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grdsta[9]  = %lx\n", (kulong)&ioDisp.main.grch[0].grdsta[9]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].graren     = %lx\n", (kulong)&ioDisp.main.grch[0].graren);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grbsl      = %lx\n", (kulong)&ioDisp.main.grch[0].grbsl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grblink    = %lx\n", (kulong)&ioDisp.main.grch[0].grblink);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grhrsz0    = %lx\n", (kulong)&ioDisp.main.grch[0].grhrsz0);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grhrsz1    = %lx\n", (kulong)&ioDisp.main.grch[0].grhrsz1);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grvrsz     = %lx\n", (kulong)&ioDisp.main.grch[0].grvrsz);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grr2y[0]   = %lx\n", (kulong)&ioDisp.main.grch[0].grr2y[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grr2y[2]   = %lx\n", (kulong)&ioDisp.main.grch[0].grr2y[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grdrectl   = %lx\n", (kulong)&ioDisp.main.grch[0].grdrectl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grdreycal  = %lx\n", (kulong)&ioDisp.main.grch[0].grdreycal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grdrecbcal = %lx\n", (kulong)&ioDisp.main.grch[0].grdrecbcal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grdrecrcal = %lx\n", (kulong)&ioDisp.main.grch[0].grdrecrcal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].gry2r[0]   = %lx\n", (kulong)&ioDisp.main.grch[0].gry2r[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].gry2r[2]   = %lx\n", (kulong)&ioDisp.main.grch[0].gry2r[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grtblaset  = %lx\n", (kulong)&ioDisp.main.grch[0].grtblaset);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grcc[0]    = %lx\n", (kulong)&ioDisp.main.grch[0].grcc[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grcc[2]    = %lx\n", (kulong)&ioDisp.main.grch[0].grcc[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grtcycal   = %lx\n", (kulong)&ioDisp.main.grch[0].grtcycal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].grtcctl    = %lx\n", (kulong)&ioDisp.main.grch[0].grtcctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[0].gralp      = %lx\n", (kulong)&ioDisp.main.grch[0].gralp);

    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grrst      = %lx\n", (kulong)&ioDisp.main.grch[1].grrst);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grtrg      = %lx\n", (kulong)&ioDisp.main.grch[1].grtrg);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grrpgctl   = %lx\n", (kulong)&ioDisp.main.grch[1].grrpgctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].gridt      = %lx\n", (kulong)&ioDisp.main.grch[1].gridt);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grtisize   = %lx\n", (kulong)&ioDisp.main.grch[1].grtisize);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grtdsta    = %lx\n", (kulong)&ioDisp.main.grch[1].grtdsta);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].gripo      = %lx\n", (kulong)&ioDisp.main.grch[1].gripo);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grscctl    = %lx\n", (kulong)&ioDisp.main.grch[1].grscctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grercv     = %lx\n", (kulong)&ioDisp.main.grch[1].grercv);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grisize[0] = %lx\n", (kulong)&ioDisp.main.grch[1].grisize[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grisize[9] = %lx\n", (kulong)&ioDisp.main.grch[1].grisize[9]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grsa0[0]   = %lx\n", (kulong)&ioDisp.main.grch[1].grsa0[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grsa0[3]   = %lx\n", (kulong)&ioDisp.main.grch[1].grsa0[3]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grsa[0]    = %lx\n", (kulong)&ioDisp.main.grch[1].grsa[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grsa[8]    = %lx\n", (kulong)&ioDisp.main.grch[1].grsa[8]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grhga[0]   = %lx\n", (kulong)&ioDisp.main.grch[1].grhga[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grhga[9]   = %lx\n", (kulong)&ioDisp.main.grch[1].grhga[9]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grdsta[0]  = %lx\n", (kulong)&ioDisp.main.grch[1].grdsta[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grdsta[9]  = %lx\n", (kulong)&ioDisp.main.grch[1].grdsta[9]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].graren     = %lx\n", (kulong)&ioDisp.main.grch[1].graren);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grbsl      = %lx\n", (kulong)&ioDisp.main.grch[1].grbsl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grblink    = %lx\n", (kulong)&ioDisp.main.grch[1].grblink);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grhrsz0    = %lx\n", (kulong)&ioDisp.main.grch[1].grhrsz0);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grhrsz1    = %lx\n", (kulong)&ioDisp.main.grch[1].grhrsz1);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grvrsz     = %lx\n", (kulong)&ioDisp.main.grch[1].grvrsz);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grr2y[0]   = %lx\n", (kulong)&ioDisp.main.grch[1].grr2y[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grr2y[2]   = %lx\n", (kulong)&ioDisp.main.grch[1].grr2y[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grdrectl   = %lx\n", (kulong)&ioDisp.main.grch[1].grdrectl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grdreycal  = %lx\n", (kulong)&ioDisp.main.grch[1].grdreycal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grdrecbcal = %lx\n", (kulong)&ioDisp.main.grch[1].grdrecbcal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grdrecrcal = %lx\n", (kulong)&ioDisp.main.grch[1].grdrecrcal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].gry2r[0]   = %lx\n", (kulong)&ioDisp.main.grch[1].gry2r[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].gry2r[2]   = %lx\n", (kulong)&ioDisp.main.grch[1].gry2r[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grtblaset  = %lx\n", (kulong)&ioDisp.main.grch[1].grtblaset);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grcc[0]    = %lx\n", (kulong)&ioDisp.main.grch[1].grcc[0]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grcc[2]    = %lx\n", (kulong)&ioDisp.main.grch[1].grcc[2]);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grtcycal   = %lx\n", (kulong)&ioDisp.main.grch[1].grtcycal);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].grtcctl    = %lx\n", (kulong)&ioDisp.main.grch[1].grtcctl);
    K_DISP_TEST_RS_PRINTF("ioDisp.main.grch[1].gralp      = %lx\n", (kulong)&ioDisp.main.grch[1].gralp);

    /* io_jdsdisp_tbl */
    K_DISP_TEST_RS_PRINTF("ioDispTbl\n");
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.igtblr         = %lx\n", (kulong)&ioDispTbl.lch0.igtblr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.igtblg         = %lx\n", (kulong)&ioDispTbl.lch0.igtblg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.igtblb         = %lx\n", (kulong)&ioDispTbl.lch0.igtblb);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.tctbl          = %lx\n", (kulong)&ioDispTbl.lch0.tctbl);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.tcep           = %lx\n", (kulong)&ioDispTbl.lch0.tcep);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.dgtblfr        = %lx\n", (kulong)&ioDispTbl.lch0.dgtblfr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.dgtblfg        = %lx\n", (kulong)&ioDispTbl.lch0.dgtblfg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.dgtblfb        = %lx\n", (kulong)&ioDispTbl.lch0.dgtblfb);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.dgtbldr        = %lx\n", (kulong)&ioDispTbl.lch0.dgtbldr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.dgtbldg        = %lx\n", (kulong)&ioDispTbl.lch0.dgtbldg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.lch0.dgtbldb        = %lx\n", (kulong)&ioDispTbl.lch0.dgtbldb);

    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].igtblr     = %lx\n", (kulong)&ioDispTbl.grch0[0].igtblr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].igtblg     = %lx\n", (kulong)&ioDispTbl.grch0[0].igtblg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].igtblb     = %lx\n", (kulong)&ioDispTbl.grch0[0].igtblb);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].tctbl      = %lx\n", (kulong)&ioDispTbl.grch0[0].tctbl);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].tcep       = %lx\n", (kulong)&ioDispTbl.grch0[0].tcep);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].dgtblfr    = %lx\n", (kulong)&ioDispTbl.grch0[0].dgtblfr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].dgtblfg    = %lx\n", (kulong)&ioDispTbl.grch0[0].dgtblfg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].dgtblfb    = %lx\n", (kulong)&ioDispTbl.grch0[0].dgtblfb);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].dgtbldr    = %lx\n", (kulong)&ioDispTbl.grch0[0].dgtbldr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].dgtbldg    = %lx\n", (kulong)&ioDispTbl.grch0[0].dgtbldg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[0].dgtbldb    = %lx\n", (kulong)&ioDispTbl.grch0[0].dgtbldb);

    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].igtblr     = %lx\n", (kulong)&ioDispTbl.grch0[1].igtblr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].igtblg     = %lx\n", (kulong)&ioDispTbl.grch0[1].igtblg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].igtblb     = %lx\n", (kulong)&ioDispTbl.grch0[1].igtblb);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].tctbl      = %lx\n", (kulong)&ioDispTbl.grch0[1].tctbl);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].tcep       = %lx\n", (kulong)&ioDispTbl.grch0[1].tcep);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].dgtblfr    = %lx\n", (kulong)&ioDispTbl.grch0[1].dgtblfr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].dgtblfg    = %lx\n", (kulong)&ioDispTbl.grch0[1].dgtblfg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].dgtblfb    = %lx\n", (kulong)&ioDispTbl.grch0[1].dgtblfb);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].dgtbldr    = %lx\n", (kulong)&ioDispTbl.grch0[1].dgtbldr);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].dgtbldg    = %lx\n", (kulong)&ioDispTbl.grch0[1].dgtbldg);
    K_DISP_TEST_RS_PRINTF("ioDispTbl.grch0[1].dgtbldb    = %lx\n", (kulong)&ioDispTbl.grch0[1].dgtbldb);

    K_DISP_TEST_RS_PRINTF(" \n");
#endif
}

void k_disp_test_xch_test(KDispTest *self)
{
// for PC debug
#if 0
#define ioXch      (*ioXch2)
    volatile IoJdsxch* ioXch2 = (kpointer)0x288C0000;
#endif
    K_DISP_TEST_RS_PRINTF("Xch\n");
#if 0
    K_DISP_TEST_RS_PRINTF("ioXch.sr              = 0x%lX\n", (kulong)&ioXch.sr);
    K_DISP_TEST_RS_PRINTF("ioXch.xchice          = 0x%lX\n", (kulong)&ioXch.xchice);
    K_DISP_TEST_RS_PRINTF("ioXch.xchicf          = 0x%lX\n", (kulong)&ioXch.xchicf);
    // xchctl0
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xtrg    = 0x%lX\n", (kulong)&ioXch.xchctl0.xtrg);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xdtype  = 0x%lX\n", (kulong)&ioXch.xchctl0.xdtype);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xmd     = 0x%lX\n", (kulong)&ioXch.xchctl0.xmd);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xfdt    = 0x%lX\n", (kulong)&ioXch.xchctl0.xfdt);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xcyc    = 0x%lX\n", (kulong)&ioXch.xchctl0.xcyc);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xven    = 0x%lX\n", (kulong)&ioXch.xchctl0.xven);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xhen    = 0x%lX\n", (kulong)&ioXch.xchctl0.xhen);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xshw    = 0x%lX\n", (kulong)&ioXch.xchctl0.xshw);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xghw    = 0x%lX\n", (kulong)&ioXch.xchctl0.xghw);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xdvw    = 0x%lX\n", (kulong)&ioXch.xchctl0.xdvw);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xdhw    = 0x%lX\n", (kulong)&ioXch.xchctl0.xdhw);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xsa     = 0x%lX\n", (kulong)&ioXch.xchctl0.xsa);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl0.xda     = 0x%lX\n", (kulong)&ioXch.xchctl0.xda);

    K_DISP_TEST_RS_PRINTF("ioXch.xhistg0         = 0x%lX\n", (kulong)&ioXch.xhistg0);
    // xchctl1
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xtrg    = 0x%lX\n", (kulong)&ioXch.xchctl1.xtrg);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xdtype  = 0x%lX\n", (kulong)&ioXch.xchctl1.xdtype);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xmd     = 0x%lX\n", (kulong)&ioXch.xchctl1.xmd);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xfdt    = 0x%lX\n", (kulong)&ioXch.xchctl1.xfdt);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xcyc    = 0x%lX\n", (kulong)&ioXch.xchctl1.xcyc);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xven    = 0x%lX\n", (kulong)&ioXch.xchctl1.xven);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xhen    = 0x%lX\n", (kulong)&ioXch.xchctl1.xhen);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xshw    = 0x%lX\n", (kulong)&ioXch.xchctl1.xshw);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xghw    = 0x%lX\n", (kulong)&ioXch.xchctl1.xghw);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xdvw    = 0x%lX\n", (kulong)&ioXch.xchctl1.xdvw);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xdhw    = 0x%lX\n", (kulong)&ioXch.xchctl1.xdhw);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xsa     = 0x%lX\n", (kulong)&ioXch.xchctl1.xsa);
    K_DISP_TEST_RS_PRINTF("ioXch.xchctl1.xda     = 0x%lX\n", (kulong)&ioXch.xchctl1.xda);
    // Hist Buffer
    kint i;
    for ( i = 0; i <= 255; i++ ) {
        K_DISP_TEST_RS_PRINTF("ioXch.xhbf[%d]    = 0x%lX\n", i, (kulong)&ioXch.xhbf[i]);
    }
    K_DISP_TEST_RS_PRINTF(" \n");
#endif
}

void k_disp_test_ela_test(KDispTest *self)
{
    K_DISP_TEST_RS_PRINTF("ELA\n");
#if 0
    {
        K_DISP_TEST_RS_PRINTF("ioEla.earcache              = %lx\n", (kulong)&ioEla.earcache);
        K_DISP_TEST_RS_PRINTF("ioEla.eawcache              = %lx\n", (kulong)&ioEla.eawcache);
        K_DISP_TEST_RS_PRINTF("ioEla.earprot               = %lx\n", (kulong)&ioEla.earprot);
        K_DISP_TEST_RS_PRINTF("ioEla.eawprot               = %lx\n", (kulong)&ioEla.eawprot);
        K_DISP_TEST_RS_PRINTF("ioEla.earaxsts              = %lx\n", (kulong)&ioEla.earaxsts);
        K_DISP_TEST_RS_PRINTF("ioEla.eawaxsts              = %lx\n", (kulong)&ioEla.eawaxsts);

        K_DISP_TEST_RS_PRINTF("ioEla.earreqmsk.earreqmsk1  = %lx\n", (kulong)&ioEla.earreqmsk.earreqmsk1);
        K_DISP_TEST_RS_PRINTF("ioEla.earreqmsk.earreqmsk2  = %lx\n", (kulong)&ioEla.earreqmsk.earreqmsk2);
        K_DISP_TEST_RS_PRINTF("ioEla.EAWREQMSK.eawreqmsk1  = %lx\n", (kulong)&ioEla.EAWREQMSK.eawreqmsk1);
        K_DISP_TEST_RS_PRINTF("ioEla.EAWREQMSK.eawreqmsk2  = %lx\n", (kulong)&ioEla.EAWREQMSK.eawreqmsk2);

        K_DISP_TEST_RS_PRINTF("ioEla.elainte               = %lx\n", (kulong)&ioEla.elainte);
        K_DISP_TEST_RS_PRINTF("ioEla.elaintf               = %lx\n", (kulong)&ioEla.elaintf);
        K_DISP_TEST_RS_PRINTF("ioEla.sramact               = %lx\n", (kulong)&ioEla.sramact);

        K_DISP_TEST_RS_PRINTF("ioEla.elatrg                = %lx\n", (kulong)&ioEla.elatrg);
        K_DISP_TEST_RS_PRINTF("ioEla.elactl                = %lx\n", (kulong)&ioEla.elactl);
        K_DISP_TEST_RS_PRINTF("ioEla.elabyr                = %lx\n", (kulong)&ioEla.elabyr);
        K_DISP_TEST_RS_PRINTF("ioEla.nslmd                 = %lx\n", (kulong)&ioEla.nslmd);
        K_DISP_TEST_RS_PRINTF("ioEla.obof.obof1            = %lx\n", (kulong)&ioEla.obof.obof1);
        K_DISP_TEST_RS_PRINTF("ioEla.obof.obof2            = %lx\n", (kulong)&ioEla.obof.obof2);
        K_DISP_TEST_RS_PRINTF("ioEla.ezsfta1               = %lx\n", (kulong)&ioEla.ezsfta1);
        K_DISP_TEST_RS_PRINTF("ioEla.nslnglmt              = %lx\n", (kulong)&ioEla.nslnglmt);
        K_DISP_TEST_RS_PRINTF("ioEla.eira                  = %lx\n", (kulong)&ioEla.eira);
        K_DISP_TEST_RS_PRINTF("ioEla.eirofs                = %lx\n", (kulong)&ioEla.eirofs);
        K_DISP_TEST_RS_PRINTF("ioEla.eirdef                = %lx\n", (kulong)&ioEla.eirdef);
        K_DISP_TEST_RS_PRINTF("ioEla.eirhsiz               = %lx\n", (kulong)&ioEla.eirhsiz);
        K_DISP_TEST_RS_PRINTF("ioEla.eirvsiz               = %lx\n", (kulong)&ioEla.eirvsiz);
        K_DISP_TEST_RS_PRINTF("ioEla.eiwa                  = %lx\n", (kulong)&ioEla.eiwa);
        K_DISP_TEST_RS_PRINTF("ioEla.eiwdef                = %lx\n", (kulong)&ioEla.eiwdef);
        K_DISP_TEST_RS_PRINTF("ioEla.enwa                  = %lx\n", (kulong)&ioEla.enwa);
        K_DISP_TEST_RS_PRINTF("ioEla.enwdef                = %lx\n", (kulong)&ioEla.enwdef);
        K_DISP_TEST_RS_PRINTF("ioEla.enra                  = %lx\n", (kulong)&ioEla.enra);
        K_DISP_TEST_RS_PRINTF("ioEla.enrhsiz               = %lx\n", (kulong)&ioEla.enrhsiz);
        K_DISP_TEST_RS_PRINTF("ioEla.enrvsiz               = %lx\n", (kulong)&ioEla.enrvsiz);
        K_DISP_TEST_RS_PRINTF("ioEla.ensa                  = %lx\n", (kulong)&ioEla.ensa);
        K_DISP_TEST_RS_PRINTF("ioEla.ensdef                = %lx\n", (kulong)&ioEla.ensdef);
        K_DISP_TEST_RS_PRINTF("ioEla.enshsiz               = %lx\n", (kulong)&ioEla.enshsiz);
        K_DISP_TEST_RS_PRINTF("ioEla.ensvsiz               = %lx\n", (kulong)&ioEla.ensvsiz);
        K_DISP_TEST_RS_PRINTF("ioEla.byrtyp                = %lx\n", (kulong)&ioEla.byrtyp);
        K_DISP_TEST_RS_PRINTF("ioEla.elfzp                 = %lx\n", (kulong)&ioEla.elfzp);
        K_DISP_TEST_RS_PRINTF("ioEla.elfl.elfl1            = %lx\n", (kulong)&ioEla.elfl.elfl1);
        K_DISP_TEST_RS_PRINTF("ioEla.elfl.elfl2            = %lx\n", (kulong)&ioEla.elfl.elfl2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbor.anbor1          = %lx\n", (kulong)&ioEla.anbor.anbor1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbor.anbor2          = %lx\n", (kulong)&ioEla.anbor.anbor2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbkr.anbkr1          = %lx\n", (kulong)&ioEla.anbkr.anbkr1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbkr.anbkr2          = %lx\n", (kulong)&ioEla.anbkr.anbkr2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbdr.anbdr1          = %lx\n", (kulong)&ioEla.anbdr.anbdr1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbdr.anbdr2          = %lx\n", (kulong)&ioEla.anbdr.anbdr2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbog.anbog1          = %lx\n", (kulong)&ioEla.anbog.anbog1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbog.anbog2          = %lx\n", (kulong)&ioEla.anbog.anbog2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbkg.anbkg1          = %lx\n", (kulong)&ioEla.anbkg.anbkg1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbkg.anbkg2          = %lx\n", (kulong)&ioEla.anbkg.anbkg2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbdg.anbdg1          = %lx\n", (kulong)&ioEla.anbdg.anbdg1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbdg.anbdg2          = %lx\n", (kulong)&ioEla.anbdg.anbdg2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbob.anbob1          = %lx\n", (kulong)&ioEla.anbob.anbob1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbob.anbob2          = %lx\n", (kulong)&ioEla.anbob.anbob2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbkb.anbkb1          = %lx\n", (kulong)&ioEla.anbkb.anbkb1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbkb.anbkb2          = %lx\n", (kulong)&ioEla.anbkb.anbkb2);
        K_DISP_TEST_RS_PRINTF("ioEla.anbdb.anbdb1          = %lx\n", (kulong)&ioEla.anbdb.anbdb1);
        K_DISP_TEST_RS_PRINTF("ioEla.anbdb.anbdb2          = %lx\n", (kulong)&ioEla.anbdb.anbdb2);
        K_DISP_TEST_RS_PRINTF("ioEla.lgtw.lgtw1            = %lx\n", (kulong)&ioEla.lgtw.lgtw1);
        K_DISP_TEST_RS_PRINTF("ioEla.lgtw.lgtw2            = %lx\n", (kulong)&ioEla.lgtw.lgtw2);
        K_DISP_TEST_RS_PRINTF("ioEla.lgt                   = %lx\n", (kulong)&ioEla.lgt);
        K_DISP_TEST_RS_PRINTF("ioEla.lgte                  = %lx\n", (kulong)&ioEla.lgte);
        K_DISP_TEST_RS_PRINTF("ioEla.edg2anba              = %lx\n", (kulong)&ioEla.edg2anba);
        K_DISP_TEST_RS_PRINTF("ioEla.edgscla               = %lx\n", (kulong)&ioEla.edgscla);
        K_DISP_TEST_RS_PRINTF("ioEla.edg2anbb              = %lx\n", (kulong)&ioEla.edg2anbb);
        K_DISP_TEST_RS_PRINTF("ioEla.edgsclb               = %lx\n", (kulong)&ioEla.edgsclb);
        K_DISP_TEST_RS_PRINTF("ioEla.alnge.alnge1          = %lx\n", (kulong)&ioEla.alnge.alnge1);
        K_DISP_TEST_RS_PRINTF("ioEla.alnge.alnge2          = %lx\n", (kulong)&ioEla.alnge.alnge2);
        K_DISP_TEST_RS_PRINTF("ioEla.alng.alng1            = %lx\n", (kulong)&ioEla.alng.alng1);
        K_DISP_TEST_RS_PRINTF("ioEla.alng.alng2            = %lx\n", (kulong)&ioEla.alng.alng2);
        K_DISP_TEST_RS_PRINTF("ioEla.alng.alng3            = %lx\n", (kulong)&ioEla.alng.alng3);
        K_DISP_TEST_RS_PRINTF("ioEla.alng.alng4            = %lx\n", (kulong)&ioEla.alng.alng4);
        K_DISP_TEST_RS_PRINTF("ioEla.alng.alng5            = %lx\n", (kulong)&ioEla.alng.alng5);
        K_DISP_TEST_RS_PRINTF("ioEla.alng.alng6            = %lx\n", (kulong)&ioEla.alng.alng6);
        K_DISP_TEST_RS_PRINTF("ioEla.lfth                  = %lx\n", (kulong)&ioEla.lfth);
        K_DISP_TEST_RS_PRINTF("ioEla.lcome                 = %lx\n", (kulong)&ioEla.lcome);
        K_DISP_TEST_RS_PRINTF("ioEla.lcomen                = %lx\n", (kulong)&ioEla.lcomen);
        K_DISP_TEST_RS_PRINTF("ioEla.dkntbl                = %lx\n", (kulong)&ioEla.dkntbl);

        K_DISP_TEST_RS_PRINTF(" \n");
    }
#endif
}

void k_disp_test_jpeg_enc_test(KDispTest *self)
{
// for PC debug
#if 0
#define ioJpegEnc     (*ioJpegEnc2)
    volatile IoJdsjpg1aenc* ioJpegEnc2 = (kpointer)0x24131000;
#endif
    K_DISP_TEST_RS_PRINTF("JPEG ENC\n");
#if 0
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.start                = 0x%lX\n", (kulong)&ioJpegEnc.start);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.strmode              = 0x%lX\n", (kulong)&ioJpegEnc.strmode);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.estatus              = 0x%lX\n", (kulong)&ioJpegEnc.estatus);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.eintmsk              = 0x%lX\n", (kulong)&ioJpegEnc.eintmsk);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.setmode              = 0x%lX\n", (kulong)&ioJpegEnc.setmode);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.setsize              = 0x%lX\n", (kulong)&ioJpegEnc.setsize);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.setrstm              = 0x%lX\n", (kulong)&ioJpegEnc.setrstm);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.settbl               = 0x%lX\n", (kulong)&ioJpegEnc.settbl);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.tblmode              = 0x%lX\n", (kulong)&ioJpegEnc.tblmode);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.qtblwrt              = 0x%lX\n", (kulong)&ioJpegEnc.qtblwrt);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.htblwrt              = 0x%lX\n", (kulong)&ioJpegEnc.htblwrt);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.encsize              = 0x%lX\n", (kulong)&ioJpegEnc.encsize);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.penc                 = 0x%lX\n", (kulong)&ioJpegEnc.penc);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.encsizeP            = 0x%lX\n", (kulong)&ioJpegEnc.encsizeP);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.putbsy               = 0x%lX\n", (kulong)&ioJpegEnc.putbsy);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.putbyt               = 0x%lX\n", (kulong)&ioJpegEnc.putbyt);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.putdat               = 0x%lX\n", (kulong)&ioJpegEnc.putdat);
//  K_DISP_TEST_RS_PRINTF("ioJpegEnc.swstron              = 0x%lX\n", (kulong)&ioJpegEnc.swstron);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.jckgoff              = 0x%lX\n", (kulong)&ioJpegEnc.jckgoff);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.slpmode              = 0x%lX\n", (kulong)&ioJpegEnc.slpmode);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.coreRevs            = 0x%lX\n", (kulong)&ioJpegEnc.coreRevs);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgBarP1           = 0x%lX\n", (kulong)&ioJpegEnc.imgBarP1);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgSizeP1          = 0x%lX\n", (kulong)&ioJpegEnc.imgSizeP1);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgRpP1            = 0x%lX\n", (kulong)&ioJpegEnc.imgRpP1);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgBarP2           = 0x%lX\n", (kulong)&ioJpegEnc.imgBarP2);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgSizeP2          = 0x%lX\n", (kulong)&ioJpegEnc.imgSizeP2);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgRpP2            = 0x%lX\n", (kulong)&ioJpegEnc.imgRpP2);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgBarP3           = 0x%lX\n", (kulong)&ioJpegEnc.imgBarP3);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgSizeP3          = 0x%lX\n", (kulong)&ioJpegEnc.imgSizeP3);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.imgRpP3            = 0x%lX\n", (kulong)&ioJpegEnc.imgRpP3);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.bsBar               = 0x%lX\n", (kulong)&ioJpegEnc.bsBar);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.bsMaxSize          = 0x%lX\n", (kulong)&ioJpegEnc.bsMaxSize);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.bsWp                = 0x%lX\n", (kulong)&ioJpegEnc.bsWp);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.lineOfsP1          = 0x%lX\n", (kulong)&ioJpegEnc.lineOfsP1);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.lineOfsP2          = 0x%lX\n", (kulong)&ioJpegEnc.lineOfsP2);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.lineOfsP3          = 0x%lX\n", (kulong)&ioJpegEnc.lineOfsP3);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.axiCmd              = 0x%lX\n", (kulong)&ioJpegEnc.axiCmd);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.axiCfg              = 0x%lX\n", (kulong)&ioJpegEnc.axiCfg);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.lenMax              = 0x%lX\n", (kulong)&ioJpegEnc.lenMax);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.transMax            = 0x%lX\n", (kulong)&ioJpegEnc.transMax);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.ackgoff              = 0x%lX\n", (kulong)&ioJpegEnc.ackgoff);
    K_DISP_TEST_RS_PRINTF("ioJpegEnc.aximst               = 0x%lX\n", (kulong)&ioJpegEnc.aximst);
//  K_DISP_TEST_RS_PRINTF("ioJpegEnc.rsmode               = 0x%lX\n", (kulong)&ioJpegEnc.rsmode);
//  K_DISP_TEST_RS_PRINTF("ioJpegEnc.trmode               = 0x%lX\n", (kulong)&ioJpegEnc.trmode);

    K_DISP_TEST_RS_PRINTF(" \n");
#endif
}

void k_disp_test_jpeg_dec_test(KDispTest *self)
{
// for PC debug
#if 0
#define ioJpegDec     (*ioJpegDec2)
    volatile IoJdsjpg1adec* ioJpegDec2 = (kpointer)0x24131200;
#endif
    K_DISP_TEST_RS_PRINTF("JPEG DEC\n");
#if 0
    K_DISP_TEST_RS_PRINTF("ioJpegDec.start                   = 0x%lX\n", (kulong)&ioJpegDec.start);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.dstatus                 = 0x%lX\n", (kulong)&ioJpegDec.dstatus);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.dintmsk                 = 0x%lX\n", (kulong)&ioJpegDec.dintmsk);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.strmode                 = 0x%lX\n", (kulong)&ioJpegDec.strmode);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.statusd0                = 0x%lX\n", (kulong)&ioJpegDec.statusd0);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.statusd1                = 0x%lX\n", (kulong)&ioJpegDec.statusd1);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgsized                = 0x%lX\n", (kulong)&ioJpegDec.imgsized);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.paramd                  = 0x%lX\n", (kulong)&ioJpegDec.paramd);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.getrdy                  = 0x%lX\n", (kulong)&ioJpegDec.getrdy);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.getbyt                  = 0x%lX\n", (kulong)&ioJpegDec.getbyt);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.getdat                  = 0x%lX\n", (kulong)&ioJpegDec.getdat);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.crpHorz                = 0x%lX\n", (kulong)&ioJpegDec.crpHorz);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.crpVert                = 0x%lX\n", (kulong)&ioJpegDec.crpVert);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.jckgoff                 = 0x%lX\n", (kulong)&ioJpegDec.jckgoff);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.slpmode                 = 0x%lX\n", (kulong)&ioJpegDec.slpmode);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.corerevs               = 0x%lX\n", (kulong)&ioJpegDec.corerevs);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgbarp1              = 0x%lX\n", (kulong)&ioJpegDec.imgbarp1);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgMaxSizeP1         = 0x%lX\n", (kulong)&ioJpegDec.imgMaxSizeP1);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgWpP1               = 0x%lX\n", (kulong)&ioJpegDec.imgWpP1);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgBarP2              = 0x%lX\n", (kulong)&ioJpegDec.imgBarP2);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgMaxSizeP2         = 0x%lX\n", (kulong)&ioJpegDec.imgMaxSizeP2);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgWpP2               = 0x%lX\n", (kulong)&ioJpegDec.imgWpP2);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgBarP3              = 0x%lX\n", (kulong)&ioJpegDec.imgBarP3);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgMaxSizeP3         = 0x%lX\n", (kulong)&ioJpegDec.imgMaxSizeP3);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.imgWpP3               = 0x%lX\n", (kulong)&ioJpegDec.imgWpP3);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.bsBar                  = 0x%lX\n", (kulong)&ioJpegDec.bsBar);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.bsSize                 = 0x%lX\n", (kulong)&ioJpegDec.bsSize);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.bsRp                   = 0x%lX\n", (kulong)&ioJpegDec.bsRp);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.lineOfsP1             = 0x%lX\n", (kulong)&ioJpegDec.lineOfsP1);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.lineOfsP2             = 0x%lX\n", (kulong)&ioJpegDec.lineOfsP2);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.lineOfsP3             = 0x%lX\n", (kulong)&ioJpegDec.lineOfsP3);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.axiCmd                 = 0x%lX\n", (kulong)&ioJpegDec.axiCmd);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.axiCfg                 = 0x%lX\n", (kulong)&ioJpegDec.axiCfg);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.wrstate                 = 0x%lX\n", (kulong)&ioJpegDec.wrstate);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.lenMax                 = 0x%lX\n", (kulong)&ioJpegDec.lenMax);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.paddata                 = 0x%lX\n", (kulong)&ioJpegDec.paddata);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.transMax               = 0x%lX\n", (kulong)&ioJpegDec.transMax);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.ackgoff                 = 0x%lX\n", (kulong)&ioJpegDec.ackgoff);
//  K_DISP_TEST_RS_PRINTF("ioJpegDec.trmode                  = 0x%lX\n", (kulong)&ioJpegDec.trmode);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.ccmtrx0                 = 0x%lX\n", (kulong)&ioJpegDec.ccmtrx0);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.ccmtrx1                 = 0x%lX\n", (kulong)&ioJpegDec.ccmtrx1);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.ccmtrx2                 = 0x%lX\n", (kulong)&ioJpegDec.ccmtrx2);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.ccmtrx3                 = 0x%lX\n", (kulong)&ioJpegDec.ccmtrx3);
    K_DISP_TEST_RS_PRINTF("ioJpegDec.ccmtrx4                 = 0x%lX\n", (kulong)&ioJpegDec.ccmtrx4);

    K_DISP_TEST_RS_PRINTF(" \n");
#endif
}

KDispTest* k_disp_test_new(void)
{
    KDispTest* self = k_object_new_with_private(K_TYPE_DISP_TEST, sizeof(KDispTestPrivate));
    return self;
}
