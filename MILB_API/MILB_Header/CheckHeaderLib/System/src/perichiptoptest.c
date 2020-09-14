/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :郑蛘钊
*@brief             :perichiptoptest
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
#include "perichiptoptest.h"


K_TYPE_DEFINE_WITH_PRIVATE(PeriChiptopTest, peri_chiptop_test);

#define PERI_CHIPTOP_TEST_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), PeriChiptopTestPrivate, PERI_TYPE_CHIPTOP_TEST))

#define PERI_CHIPTOP_TEST_RS_PRINTF printf


struct  _PeriChiptopTestPrivate
{

};
/**
*IMPL
*/
static void peri_chiptop_test_constructor(PeriChiptopTest *self)
{
	PeriChiptopTestPrivate *priv = PERI_CHIPTOP_TEST_GET_PRIVATE(self);
}

static void peri_chiptop_test_destructor(PeriChiptopTest *self)
{
	PeriChiptopTestPrivate *priv = PERI_CHIPTOP_TEST_GET_PRIVATE(self);
}
/**
*PUBLIC
*/
/*************************************************************************/
void peri_chiptop_test_peri_test(PeriChiptopTest *self)
{
// for PC debug
#if 0
#define ioPeri     (*ioPeri2)
    volatile IoPeri* ioPeri2 = (kpointer)0x1E000000;
#define ioPwmdma   (ioPwmdma2)
    volatile IoPwmdma* ioPwmdma2 = (kpointer)0x1E120000;
#define ioUsio     (*ioUsio2)
    volatile union IoUsio* ioUsio2 = (kpointer)0x1E700000;
#define ioHdmac    (*ioHdmac2)
    volatile IoHdmac* ioHdmac2 = (kpointer)0x1B040000;
#define ioHdmac0   (*ioHdmac02)
    volatile IoHdmac* ioHdmac02 = (kpointer)0x1E100000;
#define ioHdmac1   (*ioHdmac12)
    volatile IoHdmac* ioHdmac12 = (kpointer)0x1E110000;
#define ioSlimbus0 (*ioSlimbus02)
    volatile IoSlimbus* ioSlimbus02 = (kpointer)0x1E300000;
#define ioSlimbus1 (*ioSlimbus12)
    volatile IoSlimbus* ioSlimbus12 = (kpointer)0x1E400000;
#define ioSlimbus2 (*ioSlimbus22)
    volatile IoSlimbus* ioSlimbus22 = (kpointer)0x1E900000;
#define ioSlimbus3 (*ioSlimbus32)
    volatile IoSlimbus* ioSlimbus32 = (kpointer)0x1EA00000;
#endif
    PERI_CHIPTOP_TEST_RS_PRINTF("Peri\n");
#if 0
    kint i;

    /* 32bit Reload Timer */
    for ( i = 0; i < 14; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr[%d].tmcsr     = %lX\n", i, (kulong)&ioPeri.tmr[i].tmcsr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr[%d].tmr       = %lX\n", i, (kulong)&ioPeri.tmr[i].tmr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr[%d].tmrlr0    = %lX\n", i, (kulong)&ioPeri.tmr[i].tmrlr0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr[%d].tmrlr1    = %lX\n", i, (kulong)&ioPeri.tmr[i].tmrlr1);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* 64bit Free Run Timer */
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.tmcsr641    = %lX\n", (kulong)&ioPeri.tmr64.tmcsr641);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.tmcsr642    = %lX\n", (kulong)&ioPeri.tmr64.tmcsr642);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.gtimstmp     = %lX\n", (kulong)&ioPeri.tmr64.gtimstmp);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.fstmstmp[0]  = %lX\n", (kulong)&ioPeri.tmr64.fstmstmp[0]);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.fstmstmp[1]  = %lX\n", (kulong)&ioPeri.tmr64.fstmstmp[1]);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.fstmstmp[2]  = %lX\n", (kulong)&ioPeri.tmr64.fstmstmp[2]);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.fstmstmp[3]  = %lX\n", (kulong)&ioPeri.tmr64.fstmstmp[3]);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.fetmstmp[0]  = %lX\n", (kulong)&ioPeri.tmr64.fetmstmp[0]);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.fetmstmp[1]  = %lX\n", (kulong)&ioPeri.tmr64.fetmstmp[1]);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.fetmstmp[2]  = %lX\n", (kulong)&ioPeri.tmr64.fetmstmp[2]);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.fetmstmp[3]  = %lX\n", (kulong)&ioPeri.tmr64.fetmstmp[3]);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.tmr64L      = %lX\n", (kulong)&ioPeri.tmr64.tmr64L);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.tmr64.tmr64H      = %lX\n", (kulong)&ioPeri.tmr64.tmr64H);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* pwm Timer */
    for ( i = 0; i < 4; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].gcn1       = %lX\n", i, (kulong)&ioPeri.pwm[i].gcn1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].gcn2       = %lX\n", i, (kulong)&ioPeri.pwm[i].gcn2);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ptmra      = %lX\n", i, (kulong)&ioPeri.pwm[i].ptmra);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsra      = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsra);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pduta      = %lX\n", i, (kulong)&ioPeri.pwm[i].pduta);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcna       = %lX\n", i, (kulong)&ioPeri.pwm[i].pcna);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ptmrb      = %lX\n", i, (kulong)&ioPeri.pwm[i].ptmrb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrb      = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutb      = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcnb       = %lX\n", i, (kulong)&ioPeri.pwm[i].pcnb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ptmrc      = %lX\n", i, (kulong)&ioPeri.pwm[i].ptmrc);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrc      = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrc);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutc      = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutc);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcnc       = %lX\n", i, (kulong)&ioPeri.pwm[i].pcnc);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ptmrd      = %lX\n", i, (kulong)&ioPeri.pwm[i].ptmrd);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrd      = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrd);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutd      = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutd);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcnd       = %lX\n", i, (kulong)&ioPeri.pwm[i].pcnd);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ptmre      = %lX\n", i, (kulong)&ioPeri.pwm[i].ptmre);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcne       = %lX\n", i, (kulong)&ioPeri.pwm[i].pcne);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].tsel       = %lX\n", i, (kulong)&ioPeri.pwm[i].tsel);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].prev       = %lX\n", i, (kulong)&ioPeri.pwm[i].prev);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrqa     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrqa);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutqa     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutqa);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrqb     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrqb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutqb     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutqb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrqc     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrqc);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutqc     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutqc);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrqd     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrqd);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutqd     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutqd);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrra     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrra);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutra     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutra);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrrb     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrrb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutrb     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutrb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrrc     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrrc);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutrc     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutrc);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsrrd     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsrrd);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutrd     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutrd);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pchset0    = %lX\n", i, (kulong)&ioPeri.pwm[i].pchset0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pchset1    = %lX\n", i, (kulong)&ioPeri.pwm[i].pchset1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pintct0    = %lX\n", i, (kulong)&ioPeri.pwm[i].pintct0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pintct1    = %lX\n", i, (kulong)&ioPeri.pwm[i].pintct1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].stmrh      = %lX\n", i, (kulong)&ioPeri.pwm[i].stmrh);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].stmrl      = %lX\n", i, (kulong)&ioPeri.pwm[i].stmrl);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsre0     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsre0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdute0     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdute0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppale0     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppale0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsre1     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsre1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdute1     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdute1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppale1     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppale1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsre2     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsre2);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdute2     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdute2);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppale2     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppale2);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsre3     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsre3);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdute3     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdute3);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppale3     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppale3);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsre4     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsre4);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdute4     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdute4);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppale4     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppale4);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsre5     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsre5);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdute5     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdute5);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppale5     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppale5);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsre6     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsre6);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdute6     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdute6);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppale6     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppale6);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsre7     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsre7);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdute7     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdute7);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppale7     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppale7);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsru0     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsru0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutu0     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutu0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppalu0     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppalu0);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsru1     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsru1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutu1     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutu1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppalu1     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppalu1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsru2     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsru2);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutu2     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutu2);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppalu2     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppalu2);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pcsru3     = %lX\n", i, (kulong)&ioPeri.pwm[i].pcsru3);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].pdutu3     = %lX\n", i, (kulong)&ioPeri.pwm[i].pdutu3);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.pwm[%d].ppalu3     = %lX\n", i, (kulong)&ioPeri.pwm[i].ppalu3);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPwmdma[%d].bfdtpt       = %lX\n", i, (kulong)&ioPwmdma[i].bfdtpt);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* UpDownCounter */
    for ( i = 0; i < 6; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.udc[%d].udcr      = %lX\n", i, (kulong)&ioPeri.udc[i].udcr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.udc[%d].rcr       = %lX\n", i, (kulong)&ioPeri.udc[i].rcr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.udc[%d].csr       = %lX\n", i, (kulong)&ioPeri.udc[i].csr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.udc[%d].ccr       = %lX\n", i, (kulong)&ioPeri.udc[i].ccr);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* i2c */
    for ( i = 0; i < 3; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.i2c[%d].sdat      = %lX\n", i, (kulong)&ioPeri.i2c[i].sdat);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.i2c[%d].st        = %lX\n", i, (kulong)&ioPeri.i2c[i].st  );
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.i2c[%d].cst       = %lX\n", i, (kulong)&ioPeri.i2c[i].cst );
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.i2c[%d].ctl1      = %lX\n", i, (kulong)&ioPeri.i2c[i].ctl1);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.i2c[%d].addr      = %lX\n", i, (kulong)&ioPeri.i2c[i].addr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.i2c[%d].ctl2      = %lX\n", i, (kulong)&ioPeri.i2c[i].ctl2);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.i2c[%d].topr      = %lX\n", i, (kulong)&ioPeri.i2c[i].topr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioPeri.i2c[%d].ctl3      = %lX\n", i, (kulong)&ioPeri.i2c[i].ctl3);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* uart/csio */
    for ( i = 0; i < 6; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.uart[%d].smr      = %lX\n", i, (kulong)&ioUsio.uart[i].smr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.uart[%d].scr      = %lX\n", i, (kulong)&ioUsio.uart[i].scr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.uart[%d].escr     = %lX\n", i, (kulong)&ioUsio.uart[i].escr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.uart[%d].ssr      = %lX\n", i, (kulong)&ioUsio.uart[i].ssr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.uart[%d].dr       = %lX\n", i, (kulong)&ioUsio.uart[i].dr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.uart[%d].bgr      = %lX\n", i, (kulong)&ioUsio.uart[i].bgr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.uart[%d].fcr      = %lX\n", i, (kulong)&ioUsio.uart[i].fcr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.uart[%d].fbyte    = %lX\n", i, (kulong)&ioUsio.uart[i].fbyte);

        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.csio[%d].smr      = %lX\n", i, (kulong)&ioUsio.csio[i].smr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.csio[%d].scr      = %lX\n", i, (kulong)&ioUsio.csio[i].scr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.csio[%d].escr     = %lX\n", i, (kulong)&ioUsio.csio[i].escr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.csio[%d].ssr      = %lX\n", i, (kulong)&ioUsio.csio[i].ssr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.csio[%d].dr       = %lX\n", i, (kulong)&ioUsio.csio[i].dr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.csio[%d].bgr      = %lX\n", i, (kulong)&ioUsio.csio[i].bgr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.csio[%d].fcr      = %lX\n", i, (kulong)&ioUsio.csio[i].fcr);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioUsio.csio[%d].fbyte    = %lX\n", i, (kulong)&ioUsio.csio[i].fbyte);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* HDMAC */
    PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac.dmacr      = %lX\n", (kulong)&ioHdmac.dmacr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac0.dmacr     = %lX\n", (kulong)&ioHdmac0.dmacr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac1.dmacr     = %lX\n", (kulong)&ioHdmac1.dmacr);
    for ( i = 0; i < 8; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac[%d].dmaca     = %lX\n", i, (kulong)&ioHdmac.dmac[i].dmaca);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac[%d].dmacb     = %lX\n", i, (kulong)&ioHdmac.dmac[i].dmacb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac[%d].dmacsa    = %lX\n", i, (kulong)&ioHdmac.dmac[i].dmacsa);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac[%d].dmacda    = %lX\n", i, (kulong)&ioHdmac.dmac[i].dmacda);
    }
    for ( i = 0; i < 8; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac0[%d].dmaca     = %lX\n", i, (kulong)&ioHdmac0.dmac[i].dmaca);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac0[%d].dmacb     = %lX\n", i, (kulong)&ioHdmac0.dmac[i].dmacb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac0[%d].dmacsa    = %lX\n", i, (kulong)&ioHdmac0.dmac[i].dmacsa);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac0[%d].dmacda    = %lX\n", i, (kulong)&ioHdmac0.dmac[i].dmacda);
    }
    for ( i = 0; i < 8; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac1[%d].dmaca     = %lX\n", i, (kulong)&ioHdmac1.dmac[i].dmaca);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac1[%d].dmacb     = %lX\n", i, (kulong)&ioHdmac1.dmac[i].dmacb);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac1[%d].dmacsa    = %lX\n", i, (kulong)&ioHdmac1.dmac[i].dmacsa);
        PERI_CHIPTOP_TEST_RS_PRINTF("ioHdmac1[%d].dmacda    = %lX\n", i, (kulong)&ioHdmac1.dmac[i].dmacda);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* SLIMbus */
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.configMode  = %lX\n", (kulong)&ioSlimbus0.configMode);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.configEa    = %lX\n", (kulong)&ioSlimbus0.configEa);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.configPrTp = %lX\n", (kulong)&ioSlimbus0.configPrTp);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.configFr    = %lX\n", (kulong)&ioSlimbus0.configFr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.configDport = %lX\n", (kulong)&ioSlimbus0.configDport);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.configEa2   = %lX\n", (kulong)&ioSlimbus0.configEa2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.configThr   = %lX\n", (kulong)&ioSlimbus0.configThr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.command      = %lX\n", (kulong)&ioSlimbus0.command);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.state        = %lX\n", (kulong)&ioSlimbus0.state);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.ieState     = %lX\n", (kulong)&ioSlimbus0.ieState);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.mchUsage    = %lX\n", (kulong)&ioSlimbus0.mchUsage);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.intEn       = %lX\n", (kulong)&ioSlimbus0.intEn);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.ksint       = %lX\n", (kulong)&ioSlimbus0.ksint);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.mcFifo      = %lX\n", (kulong)&ioSlimbus0.mcFifo);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.p0IntEn    = %lX\n", (kulong)&ioSlimbus0.p0IntEn);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.p0Int       = %lX\n", (kulong)&ioSlimbus0.p0Int);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.p0State0   = %lX\n", (kulong)&ioSlimbus0.p0State0);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.p0State1   = %lX\n", (kulong)&ioSlimbus0.p0State1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus0.p0Fifo      = %lX\n", (kulong)&ioSlimbus0.p0Fifo);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.configMode  = %lX\n", (kulong)&ioSlimbus1.configMode);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.configEa    = %lX\n", (kulong)&ioSlimbus1.configEa);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.configPrTp = %lX\n", (kulong)&ioSlimbus1.configPrTp);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.configFr    = %lX\n", (kulong)&ioSlimbus1.configFr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.configDport = %lX\n", (kulong)&ioSlimbus1.configDport);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.configEa2   = %lX\n", (kulong)&ioSlimbus1.configEa2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.configThr   = %lX\n", (kulong)&ioSlimbus1.configThr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.command      = %lX\n", (kulong)&ioSlimbus1.command);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.state        = %lX\n", (kulong)&ioSlimbus1.state);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.ieState     = %lX\n", (kulong)&ioSlimbus1.ieState);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.mchUsage    = %lX\n", (kulong)&ioSlimbus1.mchUsage);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.intEn       = %lX\n", (kulong)&ioSlimbus1.intEn);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.ksint          = %lX\n", (kulong)&ioSlimbus1.ksint);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.mcFifo      = %lX\n", (kulong)&ioSlimbus1.mcFifo);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.p0IntEn    = %lX\n", (kulong)&ioSlimbus1.p0IntEn);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.p0Int       = %lX\n", (kulong)&ioSlimbus1.p0Int);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.p0State0   = %lX\n", (kulong)&ioSlimbus1.p0State0);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.p0State1   = %lX\n", (kulong)&ioSlimbus1.p0State1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus1.p0Fifo      = %lX\n", (kulong)&ioSlimbus1.p0Fifo);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.configMode  = %lX\n", (kulong)&ioSlimbus2.configMode);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.configEa    = %lX\n", (kulong)&ioSlimbus2.configEa);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.configPrTp = %lX\n", (kulong)&ioSlimbus2.configPrTp);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.configFr    = %lX\n", (kulong)&ioSlimbus2.configFr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.configDport = %lX\n", (kulong)&ioSlimbus2.configDport);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.configEa2   = %lX\n", (kulong)&ioSlimbus2.configEa2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.configThr   = %lX\n", (kulong)&ioSlimbus2.configThr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.command      = %lX\n", (kulong)&ioSlimbus2.command);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.state        = %lX\n", (kulong)&ioSlimbus2.state);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.ieState     = %lX\n", (kulong)&ioSlimbus2.ieState);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.mchUsage    = %lX\n", (kulong)&ioSlimbus2.mchUsage);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.intEn       = %lX\n", (kulong)&ioSlimbus2.intEn);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.ksint        = %lX\n", (kulong)&ioSlimbus2.ksint);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.mcFifo      = %lX\n", (kulong)&ioSlimbus2.mcFifo);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.p0IntEn    = %lX\n", (kulong)&ioSlimbus2.p0IntEn);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.p0Int       = %lX\n", (kulong)&ioSlimbus2.p0Int);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.p0State0   = %lX\n", (kulong)&ioSlimbus2.p0State0);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.p0State1   = %lX\n", (kulong)&ioSlimbus2.p0State1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus2.p0Fifo      = %lX\n", (kulong)&ioSlimbus2.p0Fifo);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.configMode  = %lX\n", (kulong)&ioSlimbus3.configMode);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.configEa    = %lX\n", (kulong)&ioSlimbus3.configEa);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.configPrTp = %lX\n", (kulong)&ioSlimbus3.configPrTp);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.configFr    = %lX\n", (kulong)&ioSlimbus3.configFr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.configDport = %lX\n", (kulong)&ioSlimbus3.configDport);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.configEa2   = %lX\n", (kulong)&ioSlimbus3.configEa2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.configThr   = %lX\n", (kulong)&ioSlimbus3.configThr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.command      = %lX\n", (kulong)&ioSlimbus3.command);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.state        = %lX\n", (kulong)&ioSlimbus3.state);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.ieState     = %lX\n", (kulong)&ioSlimbus3.ieState);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.mchUsage    = %lX\n", (kulong)&ioSlimbus3.mchUsage);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.intEn       = %lX\n", (kulong)&ioSlimbus3.intEn);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.ksint          = %lX\n", (kulong)&ioSlimbus3.ksint);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.mcFifo      = %lX\n", (kulong)&ioSlimbus3.mcFifo);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.p0IntEn    = %lX\n", (kulong)&ioSlimbus3.p0IntEn);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.p0Int       = %lX\n", (kulong)&ioSlimbus3.p0Int);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.p0State0   = %lX\n", (kulong)&ioSlimbus3.p0State0);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.p0State1   = %lX\n", (kulong)&ioSlimbus3.p0State1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioSlimbus3.p0Fifo      = %lX\n", (kulong)&ioSlimbus3.p0Fifo);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
#endif
}

void peri_chiptop_test_chiptop_test(PeriChiptopTest *self)
{
    PERI_CHIPTOP_TEST_RS_PRINTF("CHIPTOP\n");
#if 1
    /* Clock */
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.persel1     = %lX\n", (kulong)&ioChiptop.persel1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.persel2     = %lX\n", (kulong)&ioChiptop.persel2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.persel3     = %lX\n", (kulong)&ioChiptop.persel3);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.persel4     = %lX\n", (kulong)&ioChiptop.persel4);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.mselc       = %lX\n", (kulong)&ioChiptop.mselc);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.dbcnt1      = %lX\n", (kulong)&ioChiptop.dbcnt1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.dbcnt2      = %lX\n", (kulong)&ioChiptop.dbcnt2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.dbcnt3      = %lX\n", (kulong)&ioChiptop.dbcnt3);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.dbcnt4      = %lX\n", (kulong)&ioChiptop.dbcnt4);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.dbcnt5      = %lX\n", (kulong)&ioChiptop.dbcnt5);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pudcnt      = %lX\n", (kulong)&ioChiptop.pudcnt);
    PERI_CHIPTOP_TEST_RS_PRINTF("\n");
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel1     = %lX\n", (kulong)&ioChiptop.clksel1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel2     = %lX\n", (kulong)&ioChiptop.clksel2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel3     = %lX\n", (kulong)&ioChiptop.clksel3);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel4     = %lX\n", (kulong)&ioChiptop.clksel4);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel5     = %lX\n", (kulong)&ioChiptop.clksel5);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel6     = %lX\n", (kulong)&ioChiptop.clksel6);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel7     = %lX\n", (kulong)&ioChiptop.clksel7);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel8     = %lX\n", (kulong)&ioChiptop.clksel8);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel9     = %lX\n", (kulong)&ioChiptop.clksel9);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel10    = %lX\n", (kulong)&ioChiptop.clksel10);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel11    = %lX\n", (kulong)&ioChiptop.clksel11);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clksel12    = %lX\n", (kulong)&ioChiptop.clksel12);
    PERI_CHIPTOP_TEST_RS_PRINTF("\n");
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllcnt1     = %lX\n", (kulong)&ioChiptop.pllcnt1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllcnt2     = %lX\n", (kulong)&ioChiptop.pllcnt2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllcnt3     = %lX\n", (kulong)&ioChiptop.pllcnt3);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllcnt4     = %lX\n", (kulong)&ioChiptop.pllcnt4);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllcnt5     = %lX\n", (kulong)&ioChiptop.pllcnt5);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllcnt7     = %lX\n", (kulong)&ioChiptop.pllcnt7);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllcnt8     = %lX\n", (kulong)&ioChiptop.pllcnt8);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllcnt9     = %lX\n", (kulong)&ioChiptop.pllcnt9);
    PERI_CHIPTOP_TEST_RS_PRINTF("\n");
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop1    = %lX\n", (kulong)&ioChiptop.clkstop1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop2    = %lX\n", (kulong)&ioChiptop.clkstop2);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop3    = %lX\n", (kulong)&ioChiptop.clkstop3);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop4    = %lX\n", (kulong)&ioChiptop.clkstop4);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop5    = %lX\n", (kulong)&ioChiptop.clkstop5);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop6    = %lX\n", (kulong)&ioChiptop.clkstop6);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop7    = %lX\n", (kulong)&ioChiptop.clkstop7);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop8    = %lX\n", (kulong)&ioChiptop.clkstop8);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop9    = %lX\n", (kulong)&ioChiptop.clkstop9);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop10   = %lX\n", (kulong)&ioChiptop.clkstop10);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop11   = %lX\n", (kulong)&ioChiptop.clkstop11);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop12   = %lX\n", (kulong)&ioChiptop.clkstop12);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop13   = %lX\n", (kulong)&ioChiptop.clkstop13);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.clkstop14   = %lX\n", (kulong)&ioChiptop.clkstop14);
    PERI_CHIPTOP_TEST_RS_PRINTF("\n");
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.crswr       = %lX\n", (kulong)&ioChiptop.crswr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.crrrs       = %lX\n", (kulong)&ioChiptop.crrrs);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.crrsm       = %lX\n", (kulong)&ioChiptop.crrsm);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* PORT */
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pdr         = %lX\n", (kulong)&ioChiptop.pdr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.ddr         = %lX\n", (kulong)&ioChiptop.ddr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.epcr        = %lX\n", (kulong)&ioChiptop.epcr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.puder       = %lX\n", (kulong)&ioChiptop.puder);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pudcr       = %lX\n", (kulong)&ioChiptop.pudcr);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.pllfreq1    = %lX\n", (kulong)&ioChiptop.pllfreq1);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.odivch0     = %lX\n", (kulong)&ioChiptop.odivch0);
    PERI_CHIPTOP_TEST_RS_PRINTF("ioChiptop.cmden       = %lX\n", (kulong)&ioChiptop.cmden);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
#endif
}

PeriChiptopTest* peri_chiptop_test_new(void)
{
    PeriChiptopTest* self = k_object_new_with_private(PERI_TYPE_CHIPTOP_TEST, sizeof(PeriChiptopTestPrivate));
    return self;
}
