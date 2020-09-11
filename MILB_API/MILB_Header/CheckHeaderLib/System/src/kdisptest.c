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
 IMPL
*/
static void k_disp_test_constructor(KDispTest *self)
{
	KDispTestPrivate *priv = K_DISP_TEST_GET_PRIVATE(self);
}

static void k_disp_test_destructor(KDispTest *self)
{
	KDispTestPrivate *priv = K_DISP_TEST_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
void k_disp_test_disp_test(KDispTest *self)
{
// for PC debug
#if 0
#define IO_DISP     (*IO_DISP2)
#define IO_DISP_TBL (*IO_DISP2_TBL)
    volatile IoJdsdisp* IO_DISP2 = (kpointer)0x200F0000;
    volatile IoJdsdispTbl* IO_DISP2_TBL = (kpointer)0x24080000;
#endif
    K_DISP_TEST_RS_PRINTF("DISP\n");
#if 0
    /* io_jdslch */
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LRST           = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LRST);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LTRG           = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LTRG);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LRPGCTL        = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LRPGCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LIDT           = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LIDT);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LISIZE         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LISIZE);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LYSA[0]        = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LYSA[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LYSA[3]        = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LYSA[3]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LCSA0[0]       = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LCSA0[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LCSA0[3]       = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LCSA0[3]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LYHGA          = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LYHGA);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LCHGA          = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LCHGA);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LIBCTL         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LIBCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LERCV          = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LERCV);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LHRSZ0         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LHRSZ0);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LHRSZ1         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LHRSZ1);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LVRSZ          = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LVRSZ);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LYWTH          = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LYWTH);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LYWHS0         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LYWHS0);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LYWHS1         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LYWHS1);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LYWLS0         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LYWLS0);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LYWLS1         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LYWLS1);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LBLTMR         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LBLTMR);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LDRECTL        = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LDRECTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LDREYCAL       = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LDREYCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LDRECBCAL      = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LDRECBCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LDRECRCAL      = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LDRECRCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LY2R[0]        = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LY2R[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LY2R[2]        = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LY2R[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LTBLASET       = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LTBLASET);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LCC[0]         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LCC[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LCC[2]         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LCC[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LTCYCAL        = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LTCYCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LTCCTL         = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LTCCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LDISPEN        = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LDISPEN);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LDSTA          = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LDSTA);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.LCH.LREVDISP       = %lx\n", (kulong)&IO_DISP.MAIN.LCH.LREVDISP);

    /* io_jdsdcore */
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.RESET        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.RESET);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.IFS          = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.IFS);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.TRG          = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.TRG);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.TOCTL        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.TOCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.INTC         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.INTC);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.INTE         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.INTE);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.INTF         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.INTF);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.AXISTS       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.AXISTS);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.RPGCTL       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.RPGCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.RPGEN        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.RPGEN);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.POLSEL       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.POLSEL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.TSL          = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.TSL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.VCYC         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.VCYC);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.HCYC         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.HCYC);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.OVPW         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.OVPW);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.HPW          = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.HPW);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.VBLK         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.VBLK);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.HBLK         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.HBLK);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.VDLY         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.VDLY);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.HDLY         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.HDLY);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.OVSIZE       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.OVSIZE);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.OHSIZE       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.OHSIZE);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.VRFCTL       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.VRFCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.HRFCTL       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.HRFCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.DOMD         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.DOMD);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FDOEN        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FDOEN);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FODATA       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FODATA);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.BLANKDT      = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.BLANKDT);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.CLBHSIZE     = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.CLBHSIZE);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.CLBDT[0]     = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.CLBDT[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.CLBDT[15]    = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.CLBDT[15]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.BLDCTL       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.BLDCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.R2RCTL       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.R2RCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.R2Y[0]       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.R2Y[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.R2Y[2]       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.R2Y[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.YCTL         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.YCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.YCAL         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.YCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.YCLIP        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.YCLIP);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.CBCAL        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.CBCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.CBCLIP       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.CBCLIP);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.CRCAL        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.CRCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.CRCLIP       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.CRCLIP);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.DOCTL0       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.DOCTL0);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.DOCTL1       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.DOCTL1);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.DOCTL2       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.DOCTL2);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.TRSCODE[0]   = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.TRSCODE[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.TRSCODE[1]   = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.TRSCODE[1]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.GHDSTA       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.GHDSTA);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.GVDSTA       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.GVDSTA);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.GLENGTH      = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.GLENGTH);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.GWIDTH       = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.GWIDTH);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.GITVL        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.GITVL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.GNUM         = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.GNUM);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.GDCTL        = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.GDCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.GDISPEN      = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.GDISPEN);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFDSTA[0]    = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFDSTA[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFDSTA[15]   = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFDSTA[15]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFSIZE[0]    = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFSIZE[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFSIZE[15]   = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFSIZE[15]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFWIDTH[0]   = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFWIDTH[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFWIDTH[15]  = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFWIDTH[15]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFCLR[0]     = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFCLR[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFCLR[15]    = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFCLR[15]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.DCORE.FFDISPEN     = %lx\n", (kulong)&IO_DISP.MAIN.DCORE.FFDISPEN);

    /* io_jdsgrch */
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRRST      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRRST);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRTRG      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRTRG);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRRPGCTL   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRRPGCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRIDT      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRIDT);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRTISIZE   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRTISIZE);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRTDSTA    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRTDSTA);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRIPO      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRIPO);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRSCCTL    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRSCCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRERCV     = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRERCV);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRISIZE[0] = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRISIZE[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRISIZE[9] = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRISIZE[9]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRSA0[0]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRSA0[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRSA0[3]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRSA0[3]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRSA[0]    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRSA[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRSA[8]    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRSA[8]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRHGA[0]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRHGA[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRHGA[9]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRHGA[9]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRDSTA[0]  = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRDSTA[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRDSTA[9]  = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRDSTA[9]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRAREN     = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRAREN);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRBSL      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRBSL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRBLINK    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRBLINK);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRHRSZ0    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRHRSZ0);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRHRSZ1    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRHRSZ1);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRVRSZ     = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRVRSZ);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRR2Y[0]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRR2Y[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRR2Y[2]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRR2Y[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRDRECTL   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRDRECTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRDREYCAL  = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRDREYCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRDRECBCAL = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRDRECBCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRDRECRCAL = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRDRECRCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRY2R[0]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRY2R[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRY2R[2]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRY2R[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRTBLASET  = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRTBLASET);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRCC[0]    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRCC[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRCC[2]    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRCC[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRTCYCAL   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRTCYCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRTCCTL    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRTCCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[0].GRALP      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[0].GRALP);

    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRRST      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRRST);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRTRG      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRTRG);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRRPGCTL   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRRPGCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRIDT      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRIDT);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRTISIZE   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRTISIZE);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRTDSTA    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRTDSTA);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRIPO      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRIPO);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRSCCTL    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRSCCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRERCV     = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRERCV);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRISIZE[0] = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRISIZE[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRISIZE[9] = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRISIZE[9]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRSA0[0]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRSA0[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRSA0[3]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRSA0[3]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRSA[0]    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRSA[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRSA[8]    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRSA[8]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRHGA[0]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRHGA[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRHGA[9]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRHGA[9]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRDSTA[0]  = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRDSTA[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRDSTA[9]  = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRDSTA[9]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRAREN     = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRAREN);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRBSL      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRBSL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRBLINK    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRBLINK);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRHRSZ0    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRHRSZ0);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRHRSZ1    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRHRSZ1);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRVRSZ     = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRVRSZ);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRR2Y[0]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRR2Y[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRR2Y[2]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRR2Y[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRDRECTL   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRDRECTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRDREYCAL  = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRDREYCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRDRECBCAL = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRDRECBCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRDRECRCAL = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRDRECRCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRY2R[0]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRY2R[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRY2R[2]   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRY2R[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRTBLASET  = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRTBLASET);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRCC[0]    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRCC[0]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRCC[2]    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRCC[2]);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRTCYCAL   = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRTCYCAL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRTCCTL    = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRTCCTL);
    K_DISP_TEST_RS_PRINTF("IO_DISP.MAIN.GRCH[1].GRALP      = %lx\n", (kulong)&IO_DISP.MAIN.GRCH[1].GRALP);

    /* io_jdsdisp_tbl */
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL\n");
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.IGTBLR         = %lx\n", (kulong)&IO_DISP_TBL.LCH0.IGTBLR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.IGTBLG         = %lx\n", (kulong)&IO_DISP_TBL.LCH0.IGTBLG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.IGTBLB         = %lx\n", (kulong)&IO_DISP_TBL.LCH0.IGTBLB);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.TCTBL          = %lx\n", (kulong)&IO_DISP_TBL.LCH0.TCTBL);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.TCEP           = %lx\n", (kulong)&IO_DISP_TBL.LCH0.TCEP);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.DGTBLFR        = %lx\n", (kulong)&IO_DISP_TBL.LCH0.DGTBLFR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.DGTBLFG        = %lx\n", (kulong)&IO_DISP_TBL.LCH0.DGTBLFG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.DGTBLFB        = %lx\n", (kulong)&IO_DISP_TBL.LCH0.DGTBLFB);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.DGTBLDR        = %lx\n", (kulong)&IO_DISP_TBL.LCH0.DGTBLDR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.DGTBLDG        = %lx\n", (kulong)&IO_DISP_TBL.LCH0.DGTBLDG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.LCH0.DGTBLDB        = %lx\n", (kulong)&IO_DISP_TBL.LCH0.DGTBLDB);

    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].IGTBLR     = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].IGTBLR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].IGTBLG     = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].IGTBLG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].IGTBLB     = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].IGTBLB);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].TCTBL      = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].TCTBL);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].TCEP       = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].TCEP);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].DGTBLFR    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].DGTBLFR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].DGTBLFG    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].DGTBLFG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].DGTBLFB    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].DGTBLFB);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].DGTBLDR    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].DGTBLDR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].DGTBLDG    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].DGTBLDG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[0].DGTBLDB    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[0].DGTBLDB);

    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].IGTBLR     = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].IGTBLR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].IGTBLG     = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].IGTBLG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].IGTBLB     = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].IGTBLB);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].TCTBL      = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].TCTBL);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].TCEP       = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].TCEP);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].DGTBLFR    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].DGTBLFR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].DGTBLFG    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].DGTBLFG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].DGTBLFB    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].DGTBLFB);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].DGTBLDR    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].DGTBLDR);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].DGTBLDG    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].DGTBLDG);
    K_DISP_TEST_RS_PRINTF("IO_DISP_TBL.GRCH0[1].DGTBLDB    = %lx\n", (kulong)&IO_DISP_TBL.GRCH0[1].DGTBLDB);

    K_DISP_TEST_RS_PRINTF(" \n");
#endif
}

/*************************************************************************/

void k_disp_test_xch_test(KDispTest *self)
{
// for PC debug
#if 0
#define IO_XCH      (*IO_XCH2)
    volatile IoJdsxch* IO_XCH2 = (kpointer)0x288C0000;
#endif
    K_DISP_TEST_RS_PRINTF("Xch\n");
#if 0
    K_DISP_TEST_RS_PRINTF("IO_XCH.sr              = 0x%lX\n", (kulong)&IO_XCH.sr);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHICE          = 0x%lX\n", (kulong)&IO_XCH.XCHICE);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHICF          = 0x%lX\n", (kulong)&IO_XCH.XCHICF);
    // XCHCTL0
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XTRG    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XTRG);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XDTYPE  = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XDTYPE);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XMD     = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XMD);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XFDT    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XFDT);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XCYC    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XCYC);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XVEN    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XVEN);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XHEN    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XHEN);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XSHW    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XSHW);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XGHW    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XGHW);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XDVW    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XDVW);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XDHW    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XDHW);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XSA     = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XSA);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL0.XDA     = 0x%lX\n", (kulong)&IO_XCH.XCHCTL0.XDA);

    K_DISP_TEST_RS_PRINTF("IO_XCH.XHISTG0         = 0x%lX\n", (kulong)&IO_XCH.XHISTG0);
    // XCHCTL1
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XTRG    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XTRG);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XDTYPE  = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XDTYPE);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XMD     = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XMD);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XFDT    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XFDT);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XCYC    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XCYC);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XVEN    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XVEN);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XHEN    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XHEN);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XSHW    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XSHW);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XGHW    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XGHW);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XDVW    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XDVW);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XDHW    = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XDHW);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XSA     = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XSA);
    K_DISP_TEST_RS_PRINTF("IO_XCH.XCHCTL1.XDA     = 0x%lX\n", (kulong)&IO_XCH.XCHCTL1.XDA);
    // Hist Buffer
    int i;
    for ( i = 0; i <= 255; i++ ) {
        K_DISP_TEST_RS_PRINTF("IO_XCH.XHBF[%d]    = 0x%lX\n", i, (kulong)&IO_XCH.XHBF[i]);
    }
    K_DISP_TEST_RS_PRINTF(" \n");
#endif
}

void k_disp_test_ela_test(KDispTest *self)
{
    K_DISP_TEST_RS_PRINTF("ELA\n");
#if 0
    {
        K_DISP_TEST_RS_PRINTF("IO_ELA.EARCACHE              = %lx\n", (kulong)&IO_ELA.EARCACHE);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EAWCACHE              = %lx\n", (kulong)&IO_ELA.EAWCACHE);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EARPROT               = %lx\n", (kulong)&IO_ELA.EARPROT);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EAWPROT               = %lx\n", (kulong)&IO_ELA.EAWPROT);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EARAXSTS              = %lx\n", (kulong)&IO_ELA.EARAXSTS);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EAWAXSTS              = %lx\n", (kulong)&IO_ELA.EAWAXSTS);

        K_DISP_TEST_RS_PRINTF("IO_ELA.EARREQMSK.EARREQMSK1  = %lx\n", (kulong)&IO_ELA.EARREQMSK.EARREQMSK1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EARREQMSK.EARREQMSK2  = %lx\n", (kulong)&IO_ELA.EARREQMSK.EARREQMSK2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EAWREQMSK.EAWREQMSK1  = %lx\n", (kulong)&IO_ELA.EAWREQMSK.EAWREQMSK1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EAWREQMSK.EAWREQMSK2  = %lx\n", (kulong)&IO_ELA.EAWREQMSK.EAWREQMSK2);

        K_DISP_TEST_RS_PRINTF("IO_ELA.ELAINTE               = %lx\n", (kulong)&IO_ELA.ELAINTE);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ELAINTF               = %lx\n", (kulong)&IO_ELA.ELAINTF);
        K_DISP_TEST_RS_PRINTF("IO_ELA.SRAMACT               = %lx\n", (kulong)&IO_ELA.SRAMACT);

        K_DISP_TEST_RS_PRINTF("IO_ELA.ELATRG                = %lx\n", (kulong)&IO_ELA.ELATRG);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ELACTL                = %lx\n", (kulong)&IO_ELA.ELACTL);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ELABYR                = %lx\n", (kulong)&IO_ELA.ELABYR);
        K_DISP_TEST_RS_PRINTF("IO_ELA.NSLMD                 = %lx\n", (kulong)&IO_ELA.NSLMD);
        K_DISP_TEST_RS_PRINTF("IO_ELA.OBOF.OBOF1            = %lx\n", (kulong)&IO_ELA.OBOF.OBOF1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.OBOF.OBOF2            = %lx\n", (kulong)&IO_ELA.OBOF.OBOF2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EZSFTA1               = %lx\n", (kulong)&IO_ELA.EZSFTA1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.NSLNGLMT              = %lx\n", (kulong)&IO_ELA.NSLNGLMT);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EIRA                  = %lx\n", (kulong)&IO_ELA.EIRA);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EIROFS                = %lx\n", (kulong)&IO_ELA.EIROFS);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EIRDEF                = %lx\n", (kulong)&IO_ELA.EIRDEF);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EIRHSIZ               = %lx\n", (kulong)&IO_ELA.EIRHSIZ);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EIRVSIZ               = %lx\n", (kulong)&IO_ELA.EIRVSIZ);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EIWA                  = %lx\n", (kulong)&IO_ELA.EIWA);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EIWDEF                = %lx\n", (kulong)&IO_ELA.EIWDEF);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENWA                  = %lx\n", (kulong)&IO_ELA.ENWA);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENWDEF                = %lx\n", (kulong)&IO_ELA.ENWDEF);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENRA                  = %lx\n", (kulong)&IO_ELA.ENRA);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENRHSIZ               = %lx\n", (kulong)&IO_ELA.ENRHSIZ);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENRVSIZ               = %lx\n", (kulong)&IO_ELA.ENRVSIZ);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENSA                  = %lx\n", (kulong)&IO_ELA.ENSA);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENSDEF                = %lx\n", (kulong)&IO_ELA.ENSDEF);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENSHSIZ               = %lx\n", (kulong)&IO_ELA.ENSHSIZ);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ENSVSIZ               = %lx\n", (kulong)&IO_ELA.ENSVSIZ);
        K_DISP_TEST_RS_PRINTF("IO_ELA.BYRTYP                = %lx\n", (kulong)&IO_ELA.BYRTYP);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ELFZP                 = %lx\n", (kulong)&IO_ELA.ELFZP);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ELFL.ELFL1            = %lx\n", (kulong)&IO_ELA.ELFL.ELFL1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ELFL.ELFL2            = %lx\n", (kulong)&IO_ELA.ELFL.ELFL2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBOR.ANBOR1          = %lx\n", (kulong)&IO_ELA.ANBOR.ANBOR1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBOR.ANBOR2          = %lx\n", (kulong)&IO_ELA.ANBOR.ANBOR2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBKR.ANBKR1          = %lx\n", (kulong)&IO_ELA.ANBKR.ANBKR1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBKR.ANBKR2          = %lx\n", (kulong)&IO_ELA.ANBKR.ANBKR2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBDR.ANBDR1          = %lx\n", (kulong)&IO_ELA.ANBDR.ANBDR1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBDR.ANBDR2          = %lx\n", (kulong)&IO_ELA.ANBDR.ANBDR2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBOG.ANBOG1          = %lx\n", (kulong)&IO_ELA.ANBOG.ANBOG1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBOG.ANBOG2          = %lx\n", (kulong)&IO_ELA.ANBOG.ANBOG2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBKG.ANBKG1          = %lx\n", (kulong)&IO_ELA.ANBKG.ANBKG1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBKG.ANBKG2          = %lx\n", (kulong)&IO_ELA.ANBKG.ANBKG2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBDG.ANBDG1          = %lx\n", (kulong)&IO_ELA.ANBDG.ANBDG1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBDG.ANBDG2          = %lx\n", (kulong)&IO_ELA.ANBDG.ANBDG2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBOB.ANBOB1          = %lx\n", (kulong)&IO_ELA.ANBOB.ANBOB1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBOB.ANBOB2          = %lx\n", (kulong)&IO_ELA.ANBOB.ANBOB2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBKB.ANBKB1          = %lx\n", (kulong)&IO_ELA.ANBKB.ANBKB1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBKB.ANBKB2          = %lx\n", (kulong)&IO_ELA.ANBKB.ANBKB2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBDB.ANBDB1          = %lx\n", (kulong)&IO_ELA.ANBDB.ANBDB1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ANBDB.ANBDB2          = %lx\n", (kulong)&IO_ELA.ANBDB.ANBDB2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.LGTW.LGTW1            = %lx\n", (kulong)&IO_ELA.LGTW.LGTW1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.LGTW.LGTW2            = %lx\n", (kulong)&IO_ELA.LGTW.LGTW2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.LGT                   = %lx\n", (kulong)&IO_ELA.LGT);
        K_DISP_TEST_RS_PRINTF("IO_ELA.LGTE                  = %lx\n", (kulong)&IO_ELA.LGTE);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EDG2ANBA              = %lx\n", (kulong)&IO_ELA.EDG2ANBA);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EDGSCLA               = %lx\n", (kulong)&IO_ELA.EDGSCLA);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EDG2ANBB              = %lx\n", (kulong)&IO_ELA.EDG2ANBB);
        K_DISP_TEST_RS_PRINTF("IO_ELA.EDGSCLB               = %lx\n", (kulong)&IO_ELA.EDGSCLB);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ALNGE.ALNGE1          = %lx\n", (kulong)&IO_ELA.ALNGE.ALNGE1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ALNGE.ALNGE2          = %lx\n", (kulong)&IO_ELA.ALNGE.ALNGE2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ALNG.ALNG1            = %lx\n", (kulong)&IO_ELA.ALNG.ALNG1);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ALNG.ALNG2            = %lx\n", (kulong)&IO_ELA.ALNG.ALNG2);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ALNG.ALNG3            = %lx\n", (kulong)&IO_ELA.ALNG.ALNG3);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ALNG.ALNG4            = %lx\n", (kulong)&IO_ELA.ALNG.ALNG4);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ALNG.ALNG5            = %lx\n", (kulong)&IO_ELA.ALNG.ALNG5);
        K_DISP_TEST_RS_PRINTF("IO_ELA.ALNG.ALNG6            = %lx\n", (kulong)&IO_ELA.ALNG.ALNG6);
        K_DISP_TEST_RS_PRINTF("IO_ELA.LFTH                  = %lx\n", (kulong)&IO_ELA.LFTH);
        K_DISP_TEST_RS_PRINTF("IO_ELA.LCOME                 = %lx\n", (kulong)&IO_ELA.LCOME);
        K_DISP_TEST_RS_PRINTF("IO_ELA.LCOMEN                = %lx\n", (kulong)&IO_ELA.LCOMEN);
        K_DISP_TEST_RS_PRINTF("IO_ELA.DKNTBL                = %lx\n", (kulong)&IO_ELA.DKNTBL);

        K_DISP_TEST_RS_PRINTF(" \n");
    }
#endif
}

void k_disp_test_jpeg_enc_test(KDispTest *self)
{
// for PC debug
#if 0
#define IO_JPEG_ENC     (*IO_JPEG_ENC2)
    volatile IoJdsjpg1aenc* IO_JPEG_ENC2 = (kpointer)0x24131000;
#endif
    K_DISP_TEST_RS_PRINTF("JPEG ENC\n");
#if 0
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.START                = 0x%lX\n", (kulong)&IO_JPEG_ENC.START);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.STRMODE              = 0x%lX\n", (kulong)&IO_JPEG_ENC.STRMODE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.ESTATUS              = 0x%lX\n", (kulong)&IO_JPEG_ENC.ESTATUS);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.EINTMSK              = 0x%lX\n", (kulong)&IO_JPEG_ENC.EINTMSK);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.SETMODE              = 0x%lX\n", (kulong)&IO_JPEG_ENC.SETMODE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.SETSIZE              = 0x%lX\n", (kulong)&IO_JPEG_ENC.SETSIZE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.SETRSTM              = 0x%lX\n", (kulong)&IO_JPEG_ENC.SETRSTM);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.SETTBL               = 0x%lX\n", (kulong)&IO_JPEG_ENC.SETTBL);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.TBLMODE              = 0x%lX\n", (kulong)&IO_JPEG_ENC.TBLMODE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.QTBLWRT              = 0x%lX\n", (kulong)&IO_JPEG_ENC.QTBLWRT);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.HTBLWRT              = 0x%lX\n", (kulong)&IO_JPEG_ENC.HTBLWRT);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.ENCSIZE              = 0x%lX\n", (kulong)&IO_JPEG_ENC.ENCSIZE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.PENC                 = 0x%lX\n", (kulong)&IO_JPEG_ENC.PENC);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.ENCSIZE_P            = 0x%lX\n", (kulong)&IO_JPEG_ENC.ENCSIZE_P);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.PUTBSY               = 0x%lX\n", (kulong)&IO_JPEG_ENC.PUTBSY);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.PUTBYT               = 0x%lX\n", (kulong)&IO_JPEG_ENC.PUTBYT);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.PUTDAT               = 0x%lX\n", (kulong)&IO_JPEG_ENC.PUTDAT);
//  K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.SWSTRON              = 0x%lX\n", (kulong)&IO_JPEG_ENC.SWSTRON);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.JCKGOFF              = 0x%lX\n", (kulong)&IO_JPEG_ENC.JCKGOFF);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.SLPMODE              = 0x%lX\n", (kulong)&IO_JPEG_ENC.SLPMODE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.CORE_REVS            = 0x%lX\n", (kulong)&IO_JPEG_ENC.CORE_REVS);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_BAR_P1           = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_BAR_P1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_SIZE_P1          = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_SIZE_P1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_RP_P1            = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_RP_P1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_BAR_P2           = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_BAR_P2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_SIZE_P2          = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_SIZE_P2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_RP_P2            = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_RP_P2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_BAR_P3           = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_BAR_P3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_SIZE_P3          = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_SIZE_P3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.IMG_RP_P3            = 0x%lX\n", (kulong)&IO_JPEG_ENC.IMG_RP_P3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.BS_BAR               = 0x%lX\n", (kulong)&IO_JPEG_ENC.BS_BAR);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.BS_MAX_SIZE          = 0x%lX\n", (kulong)&IO_JPEG_ENC.BS_MAX_SIZE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.BS_WP                = 0x%lX\n", (kulong)&IO_JPEG_ENC.BS_WP);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.LINE_OFS_P1          = 0x%lX\n", (kulong)&IO_JPEG_ENC.LINE_OFS_P1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.LINE_OFS_P2          = 0x%lX\n", (kulong)&IO_JPEG_ENC.LINE_OFS_P2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.LINE_OFS_P3          = 0x%lX\n", (kulong)&IO_JPEG_ENC.LINE_OFS_P3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.AXI_CMD              = 0x%lX\n", (kulong)&IO_JPEG_ENC.AXI_CMD);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.AXI_CFG              = 0x%lX\n", (kulong)&IO_JPEG_ENC.AXI_CFG);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.LEN_MAX              = 0x%lX\n", (kulong)&IO_JPEG_ENC.LEN_MAX);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.TRANS_MAX            = 0x%lX\n", (kulong)&IO_JPEG_ENC.TRANS_MAX);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.ACKGOFF              = 0x%lX\n", (kulong)&IO_JPEG_ENC.ACKGOFF);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.AXIMST               = 0x%lX\n", (kulong)&IO_JPEG_ENC.AXIMST);
//  K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.RSMODE               = 0x%lX\n", (kulong)&IO_JPEG_ENC.RSMODE);
//  K_DISP_TEST_RS_PRINTF("IO_JPEG_ENC.TRMODE               = 0x%lX\n", (kulong)&IO_JPEG_ENC.TRMODE);

    K_DISP_TEST_RS_PRINTF(" \n");
#endif
}

void k_disp_test_jpeg_dec_test(KDispTest *self)
{
// for PC debug
#if 0
#define IO_JPEG_DEC     (*IO_JPEG_DEC2)
    volatile IoJdsjpg1adec* IO_JPEG_DEC2 = (kpointer)0x24131200;
#endif
    K_DISP_TEST_RS_PRINTF("JPEG DEC\n");
#if 0
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.START                   = 0x%lX\n", (kulong)&IO_JPEG_DEC.START);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.DSTATUS                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.DSTATUS);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.DINTMSK                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.DINTMSK);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.STRMODE                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.STRMODE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.STATUSD0                = 0x%lX\n", (kulong)&IO_JPEG_DEC.STATUSD0);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.STATUSD1                = 0x%lX\n", (kulong)&IO_JPEG_DEC.STATUSD1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMGSIZED                = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMGSIZED);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.PARAMD                  = 0x%lX\n", (kulong)&IO_JPEG_DEC.PARAMD);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.GETRDY                  = 0x%lX\n", (kulong)&IO_JPEG_DEC.GETRDY);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.GETBYT                  = 0x%lX\n", (kulong)&IO_JPEG_DEC.GETBYT);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.GETDAT                  = 0x%lX\n", (kulong)&IO_JPEG_DEC.GETDAT);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.CRP_HORZ                = 0x%lX\n", (kulong)&IO_JPEG_DEC.CRP_HORZ);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.CRP_VERT                = 0x%lX\n", (kulong)&IO_JPEG_DEC.CRP_VERT);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.JCKGOFF                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.JCKGOFF);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.SLPMODE                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.SLPMODE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.CORE_REVS               = 0x%lX\n", (kulong)&IO_JPEG_DEC.CORE_REVS);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_BAR_P1              = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_BAR_P1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_MAX_SIZE_P1         = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_MAX_SIZE_P1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_WP_P1               = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_WP_P1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_BAR_P2              = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_BAR_P2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_MAX_SIZE_P2         = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_MAX_SIZE_P2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_WP_P2               = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_WP_P2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_BAR_P3              = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_BAR_P3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_MAX_SIZE_P3         = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_MAX_SIZE_P3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.IMG_WP_P3               = 0x%lX\n", (kulong)&IO_JPEG_DEC.IMG_WP_P3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.BS_BAR                  = 0x%lX\n", (kulong)&IO_JPEG_DEC.BS_BAR);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.BS_SIZE                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.BS_SIZE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.BS_RP                   = 0x%lX\n", (kulong)&IO_JPEG_DEC.BS_RP);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.LINE_OFS_P1             = 0x%lX\n", (kulong)&IO_JPEG_DEC.LINE_OFS_P1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.LINE_OFS_P2             = 0x%lX\n", (kulong)&IO_JPEG_DEC.LINE_OFS_P2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.LINE_OFS_P3             = 0x%lX\n", (kulong)&IO_JPEG_DEC.LINE_OFS_P3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.AXI_CMD                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.AXI_CMD);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.AXI_CFG                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.AXI_CFG);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.WRSTATE                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.WRSTATE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.LEN_MAX                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.LEN_MAX);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.PADDATA                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.PADDATA);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.TRANS_MAX               = 0x%lX\n", (kulong)&IO_JPEG_DEC.TRANS_MAX);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.ACKGOFF                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.ACKGOFF);
//  K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.TRMODE                  = 0x%lX\n", (kulong)&IO_JPEG_DEC.TRMODE);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.CCMTRX0                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.CCMTRX0);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.CCMTRX1                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.CCMTRX1);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.CCMTRX2                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.CCMTRX2);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.CCMTRX3                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.CCMTRX3);
    K_DISP_TEST_RS_PRINTF("IO_JPEG_DEC.CCMTRX4                 = 0x%lX\n", (kulong)&IO_JPEG_DEC.CCMTRX4);

    K_DISP_TEST_RS_PRINTF(" \n");
#endif
}

KDispTest* k_disp_test_new(void)
{
    KDispTest* self = k_object_new_with_private(K_TYPE_DISP_TEST, sizeof(KDispTestPrivate));
    return self;
}
