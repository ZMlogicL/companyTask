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
 IMPL
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
 PUBLIC
*/
/*************************************************************************/
void peri_chiptop_test_peri_test(PeriChiptopTest *self)
{
// for PC debug
#if 0
#define IO_PERI     (*IO_PERI2)
    volatile IoPeri* IO_PERI2 = (kpointer)0x1E000000;
#define IO_PWMDMA   (IO_PWMDMA2)
    volatile IoPwmdma* IO_PWMDMA2 = (kpointer)0x1E120000;
#define IO_USIO     (*IO_USIO2)
    volatile union IoUsio* IO_USIO2 = (kpointer)0x1E700000;
#define IO_HDMAC    (*IO_HDMAC2)
    volatile IoHdmac* IO_HDMAC2 = (kpointer)0x1B040000;
#define IO_HDMAC0   (*IO_HDMAC02)
    volatile IoHdmac* IO_HDMAC02 = (kpointer)0x1E100000;
#define IO_HDMAC1   (*IO_HDMAC12)
    volatile IoHdmac* IO_HDMAC12 = (kpointer)0x1E110000;
#define IO_SLIMBUS0 (*IO_SLIMBUS02)
    volatile IoSlimbus* IO_SLIMBUS02 = (kpointer)0x1E300000;
#define IO_SLIMBUS1 (*IO_SLIMBUS12)
    volatile IoSlimbus* IO_SLIMBUS12 = (kpointer)0x1E400000;
#define IO_SLIMBUS2 (*IO_SLIMBUS22)
    volatile IoSlimbus* IO_SLIMBUS22 = (kpointer)0x1E900000;
#define IO_SLIMBUS3 (*IO_SLIMBUS32)
    volatile IoSlimbus* IO_SLIMBUS32 = (kpointer)0x1EA00000;
#endif
    PERI_CHIPTOP_TEST_RS_PRINTF("Peri\n");
#if 0
    int i;

    /* 32bit Reload Timer */
    for ( i = 0; i < 14; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR[%d].TMCSR     = %lX\n", i, (kulong)&IO_PERI.TMR[i].TMCSR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR[%d].TMR       = %lX\n", i, (kulong)&IO_PERI.TMR[i].TMR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR[%d].TMRLR0    = %lX\n", i, (kulong)&IO_PERI.TMR[i].TMRLR0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR[%d].TMRLR1    = %lX\n", i, (kulong)&IO_PERI.TMR[i].TMRLR1);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* 64bit Free Run Timer */
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.TMCSR64_1    = %lX\n", (kulong)&IO_PERI.TMR64.TMCSR64_1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.TMCSR64_2    = %lX\n", (kulong)&IO_PERI.TMR64.TMCSR64_2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.GTIMSTMP     = %lX\n", (kulong)&IO_PERI.TMR64.GTIMSTMP);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.FSTMSTMP[0]  = %lX\n", (kulong)&IO_PERI.TMR64.FSTMSTMP[0]);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.FSTMSTMP[1]  = %lX\n", (kulong)&IO_PERI.TMR64.FSTMSTMP[1]);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.FSTMSTMP[2]  = %lX\n", (kulong)&IO_PERI.TMR64.FSTMSTMP[2]);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.FSTMSTMP[3]  = %lX\n", (kulong)&IO_PERI.TMR64.FSTMSTMP[3]);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.FETMSTMP[0]  = %lX\n", (kulong)&IO_PERI.TMR64.FETMSTMP[0]);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.FETMSTMP[1]  = %lX\n", (kulong)&IO_PERI.TMR64.FETMSTMP[1]);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.FETMSTMP[2]  = %lX\n", (kulong)&IO_PERI.TMR64.FETMSTMP[2]);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.FETMSTMP[3]  = %lX\n", (kulong)&IO_PERI.TMR64.FETMSTMP[3]);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.TMR64_L      = %lX\n", (kulong)&IO_PERI.TMR64.TMR64_L);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.TMR64.TMR64_H      = %lX\n", (kulong)&IO_PERI.TMR64.TMR64_H);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* PWM Timer */
    for ( i = 0; i < 4; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].GCN1       = %lX\n", i, (kulong)&IO_PERI.PWM[i].GCN1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].GCN2       = %lX\n", i, (kulong)&IO_PERI.PWM[i].GCN2);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PTMRA      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PTMRA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRA      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTA      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCNA       = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCNA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PTMRB      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PTMRB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRB      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTB      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCNB       = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCNB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PTMRC      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PTMRC);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRC      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRC);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTC      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTC);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCNC       = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCNC);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PTMRD      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PTMRD);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRD      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRD);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTD      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTD);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCND       = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCND);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PTMRE      = %lX\n", i, (kulong)&IO_PERI.PWM[i].PTMRE);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCNE       = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCNE);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].TSEL       = %lX\n", i, (kulong)&IO_PERI.PWM[i].TSEL);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PREV       = %lX\n", i, (kulong)&IO_PERI.PWM[i].PREV);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRQA     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRQA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTQA     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTQA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRQB     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRQB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTQB     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTQB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRQC     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRQC);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTQC     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTQC);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRQD     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRQD);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTQD     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTQD);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRRA     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRRA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTRA     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTRA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRRB     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRRB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTRB     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTRB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRRC     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRRC);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTRC     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTRC);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRRD     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRRD);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTRD     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTRD);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCHSET0    = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCHSET0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCHSET1    = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCHSET1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PINTCT0    = %lX\n", i, (kulong)&IO_PERI.PWM[i].PINTCT0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PINTCT1    = %lX\n", i, (kulong)&IO_PERI.PWM[i].PINTCT1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].STMRH      = %lX\n", i, (kulong)&IO_PERI.PWM[i].STMRH);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].STMRL      = %lX\n", i, (kulong)&IO_PERI.PWM[i].STMRL);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRE0     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRE0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTE0     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTE0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALE0     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALE0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRE1     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRE1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTE1     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTE1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALE1     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALE1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRE2     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRE2);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTE2     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTE2);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALE2     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALE2);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRE3     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRE3);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTE3     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTE3);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALE3     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALE3);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRE4     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRE4);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTE4     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTE4);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALE4     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALE4);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRE5     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRE5);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTE5     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTE5);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALE5     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALE5);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRE6     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRE6);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTE6     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTE6);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALE6     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALE6);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRE7     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRE7);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTE7     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTE7);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALE7     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALE7);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRU0     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRU0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTU0     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTU0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALU0     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALU0);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRU1     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRU1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTU1     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTU1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALU1     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALU1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRU2     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRU2);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTU2     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTU2);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALU2     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALU2);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PCSRU3     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PCSRU3);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PDUTU3     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PDUTU3);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.PWM[%d].PPALU3     = %lX\n", i, (kulong)&IO_PERI.PWM[i].PPALU3);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PWMDMA[%d].BFDTPT       = %lX\n", i, (kulong)&IO_PWMDMA[i].BFDTPT);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* UpDownCounter */
    for ( i = 0; i < 6; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.UDC[%d].UDCR      = %lX\n", i, (kulong)&IO_PERI.UDC[i].UDCR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.UDC[%d].RCR       = %lX\n", i, (kulong)&IO_PERI.UDC[i].RCR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.UDC[%d].CSR       = %lX\n", i, (kulong)&IO_PERI.UDC[i].CSR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.UDC[%d].CCR       = %lX\n", i, (kulong)&IO_PERI.UDC[i].CCR);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* I2C */
    for ( i = 0; i < 3; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.I2C[%d].SDAT      = %lX\n", i, (kulong)&IO_PERI.I2C[i].SDAT);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.I2C[%d].ST        = %lX\n", i, (kulong)&IO_PERI.I2C[i].ST  );
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.I2C[%d].CST       = %lX\n", i, (kulong)&IO_PERI.I2C[i].CST );
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.I2C[%d].CTL1      = %lX\n", i, (kulong)&IO_PERI.I2C[i].CTL1);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.I2C[%d].ADDR      = %lX\n", i, (kulong)&IO_PERI.I2C[i].ADDR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.I2C[%d].CTL2      = %lX\n", i, (kulong)&IO_PERI.I2C[i].CTL2);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.I2C[%d].TOPR      = %lX\n", i, (kulong)&IO_PERI.I2C[i].TOPR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_PERI.I2C[%d].CTL3      = %lX\n", i, (kulong)&IO_PERI.I2C[i].CTL3);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* UART/CSIO */
    for ( i = 0; i < 6; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.UART[%d].SMR      = %lX\n", i, (kulong)&IO_USIO.UART[i].SMR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.UART[%d].SCR      = %lX\n", i, (kulong)&IO_USIO.UART[i].SCR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.UART[%d].ESCR     = %lX\n", i, (kulong)&IO_USIO.UART[i].ESCR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.UART[%d].SSR      = %lX\n", i, (kulong)&IO_USIO.UART[i].SSR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.UART[%d].DR       = %lX\n", i, (kulong)&IO_USIO.UART[i].DR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.UART[%d].BGR      = %lX\n", i, (kulong)&IO_USIO.UART[i].BGR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.UART[%d].FCR      = %lX\n", i, (kulong)&IO_USIO.UART[i].FCR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.UART[%d].FBYTE    = %lX\n", i, (kulong)&IO_USIO.UART[i].FBYTE);

        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.CSIO[%d].SMR      = %lX\n", i, (kulong)&IO_USIO.CSIO[i].SMR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.CSIO[%d].SCR      = %lX\n", i, (kulong)&IO_USIO.CSIO[i].SCR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.CSIO[%d].ESCR     = %lX\n", i, (kulong)&IO_USIO.CSIO[i].ESCR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.CSIO[%d].SSR      = %lX\n", i, (kulong)&IO_USIO.CSIO[i].SSR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.CSIO[%d].DR       = %lX\n", i, (kulong)&IO_USIO.CSIO[i].DR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.CSIO[%d].BGR      = %lX\n", i, (kulong)&IO_USIO.CSIO[i].BGR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.CSIO[%d].FCR      = %lX\n", i, (kulong)&IO_USIO.CSIO[i].FCR);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_USIO.CSIO[%d].FBYTE    = %lX\n", i, (kulong)&IO_USIO.CSIO[i].FBYTE);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* HDMAC */
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC.DMACR      = %lX\n", (kulong)&IO_HDMAC.DMACR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC0.DMACR     = %lX\n", (kulong)&IO_HDMAC0.DMACR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC1.DMACR     = %lX\n", (kulong)&IO_HDMAC1.DMACR);
    for ( i = 0; i < 8; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC[%d].DMACA     = %lX\n", i, (kulong)&IO_HDMAC.DMAC[i].DMACA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC[%d].DMACB     = %lX\n", i, (kulong)&IO_HDMAC.DMAC[i].DMACB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC[%d].DMACSA    = %lX\n", i, (kulong)&IO_HDMAC.DMAC[i].DMACSA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC[%d].DMACDA    = %lX\n", i, (kulong)&IO_HDMAC.DMAC[i].DMACDA);
    }
    for ( i = 0; i < 8; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC0[%d].DMACA     = %lX\n", i, (kulong)&IO_HDMAC0.DMAC[i].DMACA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC0[%d].DMACB     = %lX\n", i, (kulong)&IO_HDMAC0.DMAC[i].DMACB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC0[%d].DMACSA    = %lX\n", i, (kulong)&IO_HDMAC0.DMAC[i].DMACSA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC0[%d].DMACDA    = %lX\n", i, (kulong)&IO_HDMAC0.DMAC[i].DMACDA);
    }
    for ( i = 0; i < 8; i++ ) {
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC1[%d].DMACA     = %lX\n", i, (kulong)&IO_HDMAC1.DMAC[i].DMACA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC1[%d].DMACB     = %lX\n", i, (kulong)&IO_HDMAC1.DMAC[i].DMACB);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC1[%d].DMACSA    = %lX\n", i, (kulong)&IO_HDMAC1.DMAC[i].DMACSA);
        PERI_CHIPTOP_TEST_RS_PRINTF("IO_HDMAC1[%d].DMACDA    = %lX\n", i, (kulong)&IO_HDMAC1.DMAC[i].DMACDA);
    }
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* SLIMbus */
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.CONFIG_MODE  = %lX\n", (kulong)&IO_SLIMBUS0.CONFIG_MODE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.CONFIG_EA    = %lX\n", (kulong)&IO_SLIMBUS0.CONFIG_EA);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.CONFIG_PR_TP = %lX\n", (kulong)&IO_SLIMBUS0.CONFIG_PR_TP);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.CONFIG_FR    = %lX\n", (kulong)&IO_SLIMBUS0.CONFIG_FR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.CONFIG_DPORT = %lX\n", (kulong)&IO_SLIMBUS0.CONFIG_DPORT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.CONFIG_EA2   = %lX\n", (kulong)&IO_SLIMBUS0.CONFIG_EA2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.CONFIG_THR   = %lX\n", (kulong)&IO_SLIMBUS0.CONFIG_THR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.COMMAND      = %lX\n", (kulong)&IO_SLIMBUS0.COMMAND);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.STATE        = %lX\n", (kulong)&IO_SLIMBUS0.STATE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.IE_STATE     = %lX\n", (kulong)&IO_SLIMBUS0.IE_STATE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.MCH_USAGE    = %lX\n", (kulong)&IO_SLIMBUS0.MCH_USAGE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.INT_EN       = %lX\n", (kulong)&IO_SLIMBUS0.INT_EN);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.INT          = %lX\n", (kulong)&IO_SLIMBUS0.INT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.MC_FIFO      = %lX\n", (kulong)&IO_SLIMBUS0.MC_FIFO);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.P0_INT_EN    = %lX\n", (kulong)&IO_SLIMBUS0.P0_INT_EN);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.P0_INT       = %lX\n", (kulong)&IO_SLIMBUS0.P0_INT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.P0_STATE_0   = %lX\n", (kulong)&IO_SLIMBUS0.P0_STATE_0);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.P0_STATE_1   = %lX\n", (kulong)&IO_SLIMBUS0.P0_STATE_1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS0.P0_FIFO      = %lX\n", (kulong)&IO_SLIMBUS0.P0_FIFO);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.CONFIG_MODE  = %lX\n", (kulong)&IO_SLIMBUS1.CONFIG_MODE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.CONFIG_EA    = %lX\n", (kulong)&IO_SLIMBUS1.CONFIG_EA);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.CONFIG_PR_TP = %lX\n", (kulong)&IO_SLIMBUS1.CONFIG_PR_TP);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.CONFIG_FR    = %lX\n", (kulong)&IO_SLIMBUS1.CONFIG_FR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.CONFIG_DPORT = %lX\n", (kulong)&IO_SLIMBUS1.CONFIG_DPORT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.CONFIG_EA2   = %lX\n", (kulong)&IO_SLIMBUS1.CONFIG_EA2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.CONFIG_THR   = %lX\n", (kulong)&IO_SLIMBUS1.CONFIG_THR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.COMMAND      = %lX\n", (kulong)&IO_SLIMBUS1.COMMAND);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.STATE        = %lX\n", (kulong)&IO_SLIMBUS1.STATE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.IE_STATE     = %lX\n", (kulong)&IO_SLIMBUS1.IE_STATE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.MCH_USAGE    = %lX\n", (kulong)&IO_SLIMBUS1.MCH_USAGE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.INT_EN       = %lX\n", (kulong)&IO_SLIMBUS1.INT_EN);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.INT          = %lX\n", (kulong)&IO_SLIMBUS1.INT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.MC_FIFO      = %lX\n", (kulong)&IO_SLIMBUS1.MC_FIFO);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.P0_INT_EN    = %lX\n", (kulong)&IO_SLIMBUS1.P0_INT_EN);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.P0_INT       = %lX\n", (kulong)&IO_SLIMBUS1.P0_INT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.P0_STATE_0   = %lX\n", (kulong)&IO_SLIMBUS1.P0_STATE_0);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.P0_STATE_1   = %lX\n", (kulong)&IO_SLIMBUS1.P0_STATE_1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS1.P0_FIFO      = %lX\n", (kulong)&IO_SLIMBUS1.P0_FIFO);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.CONFIG_MODE  = %lX\n", (kulong)&IO_SLIMBUS2.CONFIG_MODE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.CONFIG_EA    = %lX\n", (kulong)&IO_SLIMBUS2.CONFIG_EA);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.CONFIG_PR_TP = %lX\n", (kulong)&IO_SLIMBUS2.CONFIG_PR_TP);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.CONFIG_FR    = %lX\n", (kulong)&IO_SLIMBUS2.CONFIG_FR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.CONFIG_DPORT = %lX\n", (kulong)&IO_SLIMBUS2.CONFIG_DPORT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.CONFIG_EA2   = %lX\n", (kulong)&IO_SLIMBUS2.CONFIG_EA2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.CONFIG_THR   = %lX\n", (kulong)&IO_SLIMBUS2.CONFIG_THR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.COMMAND      = %lX\n", (kulong)&IO_SLIMBUS2.COMMAND);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.STATE        = %lX\n", (kulong)&IO_SLIMBUS2.STATE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.IE_STATE     = %lX\n", (kulong)&IO_SLIMBUS2.IE_STATE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.MCH_USAGE    = %lX\n", (kulong)&IO_SLIMBUS2.MCH_USAGE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.INT_EN       = %lX\n", (kulong)&IO_SLIMBUS2.INT_EN);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.INT          = %lX\n", (kulong)&IO_SLIMBUS2.INT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.MC_FIFO      = %lX\n", (kulong)&IO_SLIMBUS2.MC_FIFO);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.P0_INT_EN    = %lX\n", (kulong)&IO_SLIMBUS2.P0_INT_EN);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.P0_INT       = %lX\n", (kulong)&IO_SLIMBUS2.P0_INT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.P0_STATE_0   = %lX\n", (kulong)&IO_SLIMBUS2.P0_STATE_0);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.P0_STATE_1   = %lX\n", (kulong)&IO_SLIMBUS2.P0_STATE_1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS2.P0_FIFO      = %lX\n", (kulong)&IO_SLIMBUS2.P0_FIFO);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.CONFIG_MODE  = %lX\n", (kulong)&IO_SLIMBUS3.CONFIG_MODE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.CONFIG_EA    = %lX\n", (kulong)&IO_SLIMBUS3.CONFIG_EA);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.CONFIG_PR_TP = %lX\n", (kulong)&IO_SLIMBUS3.CONFIG_PR_TP);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.CONFIG_FR    = %lX\n", (kulong)&IO_SLIMBUS3.CONFIG_FR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.CONFIG_DPORT = %lX\n", (kulong)&IO_SLIMBUS3.CONFIG_DPORT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.CONFIG_EA2   = %lX\n", (kulong)&IO_SLIMBUS3.CONFIG_EA2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.CONFIG_THR   = %lX\n", (kulong)&IO_SLIMBUS3.CONFIG_THR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.COMMAND      = %lX\n", (kulong)&IO_SLIMBUS3.COMMAND);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.STATE        = %lX\n", (kulong)&IO_SLIMBUS3.STATE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.IE_STATE     = %lX\n", (kulong)&IO_SLIMBUS3.IE_STATE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.MCH_USAGE    = %lX\n", (kulong)&IO_SLIMBUS3.MCH_USAGE);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.INT_EN       = %lX\n", (kulong)&IO_SLIMBUS3.INT_EN);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.INT          = %lX\n", (kulong)&IO_SLIMBUS3.INT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.MC_FIFO      = %lX\n", (kulong)&IO_SLIMBUS3.MC_FIFO);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.P0_INT_EN    = %lX\n", (kulong)&IO_SLIMBUS3.P0_INT_EN);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.P0_INT       = %lX\n", (kulong)&IO_SLIMBUS3.P0_INT);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.P0_STATE_0   = %lX\n", (kulong)&IO_SLIMBUS3.P0_STATE_0);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.P0_STATE_1   = %lX\n", (kulong)&IO_SLIMBUS3.P0_STATE_1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_SLIMBUS3.P0_FIFO      = %lX\n", (kulong)&IO_SLIMBUS3.P0_FIFO);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
#endif
}

void peri_chiptop_test_chiptop_test(PeriChiptopTest *self)
{
    PERI_CHIPTOP_TEST_RS_PRINTF("CHIPTOP\n");
#if 1
    /* Clock */
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PERSEL1     = %lX\n", (kulong)&IO_CHIPTOP.PERSEL1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PERSEL2     = %lX\n", (kulong)&IO_CHIPTOP.PERSEL2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PERSEL3     = %lX\n", (kulong)&IO_CHIPTOP.PERSEL3);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PERSEL4     = %lX\n", (kulong)&IO_CHIPTOP.PERSEL4);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.MSELC       = %lX\n", (kulong)&IO_CHIPTOP.MSELC);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.DBCNT1      = %lX\n", (kulong)&IO_CHIPTOP.DBCNT1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.DBCNT2      = %lX\n", (kulong)&IO_CHIPTOP.DBCNT2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.DBCNT3      = %lX\n", (kulong)&IO_CHIPTOP.DBCNT3);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.DBCNT4      = %lX\n", (kulong)&IO_CHIPTOP.DBCNT4);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.DBCNT5      = %lX\n", (kulong)&IO_CHIPTOP.DBCNT5);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PUDCNT      = %lX\n", (kulong)&IO_CHIPTOP.PUDCNT);
    PERI_CHIPTOP_TEST_RS_PRINTF("\n");
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL1     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL2     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL3     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL3);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL4     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL4);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL5     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL5);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL6     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL6);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL7     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL7);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL8     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL8);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL9     = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL9);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL10    = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL10);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL11    = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL11);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSEL12    = %lX\n", (kulong)&IO_CHIPTOP.CLKSEL12);
    PERI_CHIPTOP_TEST_RS_PRINTF("\n");
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLCNT1     = %lX\n", (kulong)&IO_CHIPTOP.PLLCNT1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLCNT2     = %lX\n", (kulong)&IO_CHIPTOP.PLLCNT2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLCNT3     = %lX\n", (kulong)&IO_CHIPTOP.PLLCNT3);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLCNT4     = %lX\n", (kulong)&IO_CHIPTOP.PLLCNT4);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLCNT5     = %lX\n", (kulong)&IO_CHIPTOP.PLLCNT5);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLCNT7     = %lX\n", (kulong)&IO_CHIPTOP.PLLCNT7);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLCNT8     = %lX\n", (kulong)&IO_CHIPTOP.PLLCNT8);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLCNT9     = %lX\n", (kulong)&IO_CHIPTOP.PLLCNT9);
    PERI_CHIPTOP_TEST_RS_PRINTF("\n");
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP1    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP2    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP2);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP3    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP3);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP4    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP4);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP5    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP5);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP6    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP6);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP7    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP7);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP8    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP8);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP9    = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP9);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP10   = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP10);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP11   = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP11);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP12   = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP12);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP13   = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP13);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CLKSTOP14   = %lX\n", (kulong)&IO_CHIPTOP.CLKSTOP14);
    PERI_CHIPTOP_TEST_RS_PRINTF("\n");
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CRSWR       = %lX\n", (kulong)&IO_CHIPTOP.CRSWR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CRRRS       = %lX\n", (kulong)&IO_CHIPTOP.CRRRS);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CRRSM       = %lX\n", (kulong)&IO_CHIPTOP.CRRSM);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");

    /* PORT */
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PDR         = %lX\n", (kulong)&IO_CHIPTOP.PDR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.DDR         = %lX\n", (kulong)&IO_CHIPTOP.DDR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.EPCR        = %lX\n", (kulong)&IO_CHIPTOP.EPCR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PUDER       = %lX\n", (kulong)&IO_CHIPTOP.PUDER);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PUDCR       = %lX\n", (kulong)&IO_CHIPTOP.PUDCR);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.PLLFREQ1    = %lX\n", (kulong)&IO_CHIPTOP.PLLFREQ1);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.ODIVCH0     = %lX\n", (kulong)&IO_CHIPTOP.ODIVCH0);
    PERI_CHIPTOP_TEST_RS_PRINTF("IO_CHIPTOP.CMDEN       = %lX\n", (kulong)&IO_CHIPTOP.CMDEN);
    PERI_CHIPTOP_TEST_RS_PRINTF(" \n");
#endif
}

PeriChiptopTest* peri_chiptop_test_new(void)
{
    PeriChiptopTest* self = k_object_new_with_private(PERI_TYPE_CHIPTOP_TEST, sizeof(PeriChiptopTestPrivate));
    return self;
}
