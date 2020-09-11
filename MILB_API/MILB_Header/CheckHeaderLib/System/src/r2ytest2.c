/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-02
 *@author            :陈倩
 *@brief             :r2ytest2
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
#include "r2ytest2.h"


struct _R2yTest2Private {

};


K_TYPE_DEFINE_WITH_PRIVATE(R2yTest2, r2y_test2);
#define R2Y_TEST2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), R2yTest2Private, R2Y_TYPE_TEST2))

#define R2yTest2_RS_PRINTF printf
/**
 IMPL
 */
static void r2y_test2_constructor(R2yTest2 *self)
{
//	R2yTest2Private *priv = R2Y_TEST2_GET_PRIVATE(self);
}

static void r2y_test2_destructor(R2yTest2 *self)
{
//	R2yTest2Private *priv = R2Y_TEST2_GET_PRIVATE(self);
}
/**
 PUBLIC
 */
void r2y_test2_r2y_test(R2yTest2 *self)
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
	R2yTest2_RS_PRINTF("R2Y\n");
#if 0
	/* jdsr2y */
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyraxctl = %lX\n", (kulong)&ioR2yP1.yych.yyraxctl);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw0axctl = %lX\n", (kulong)&ioR2yP1.yych.yyw0axctl);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yywaaxctl = %lX\n", (kulong)&ioR2yP1.yych.yywaaxctl);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw1axctl = %lX\n", (kulong)&ioR2yP1.yych.yyw1axctl);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw2axctl = %lX\n", (kulong)&ioR2yP1.yych.yyw2axctl);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyraxsts = %lX\n", (kulong)&ioR2yP1.yych.yyraxsts);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw0axsts = %lX\n", (kulong)&ioR2yP1.yych.yyw0axsts);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yywaaxsts = %lX\n", (kulong)&ioR2yP1.yych.yywaaxsts);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw1axsts = %lX\n", (kulong)&ioR2yP1.yych.yyw1axsts);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw2axsts = %lX\n", (kulong)&ioR2yP1.yych.yyw2axsts);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyraxmd = %lX\n", (kulong)&ioR2yP1.yych.yyraxmd);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw0axmd = %lX\n", (kulong)&ioR2yP1.yych.yyw0axmd);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yywaaxmd = %lX\n", (kulong)&ioR2yP1.yych.yywaaxmd);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw1axmd = %lX\n", (kulong)&ioR2yP1.yych.yyw1axmd);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw2axmd = %lX\n", (kulong)&ioR2yP1.yych.yyw2axmd);

	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyrreqmsk[0] = %lX\n", (kulong)&ioR2yP1.yych.yyrreqmsk.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyrreqmsk[1] = %lX\n", (kulong)&ioR2yP1.yych.yyrreqmsk.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw0reqmsk[0] = %lX\n", (kulong)&ioR2yP1.yych.yyw0reqmsk.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw0reqmsk[1] = %lX\n", (kulong)&ioR2yP1.yych.yyw0reqmsk.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yywareqmsk = %lX\n", (kulong)&ioR2yP1.yych.yywareqmsk);

	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw1reqmsk[0] = %lX\n", (kulong)&ioR2yP1.yych.yyw1reqmsk.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw1reqmsk[1] = %lX\n", (kulong)&ioR2yP1.yych.yyw1reqmsk.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yych.yyw2reqmsk = %lX\n", (kulong)&ioR2yP1.yych.yyw2reqmsk) ;

	R2yTest2_RS_PRINTF("ioR2yP1.r2yCmn.yyinte = %lX\n", (kulong)&ioR2yP1.r2yCmn.yyinte);
	R2yTest2_RS_PRINTF("ioR2yP1.r2yCmn.yyintf = %lX\n", (kulong)&ioR2yP1.r2yCmn.yyintf);
	R2yTest2_RS_PRINTF("ioR2yP1.r2yCmn.lintlv[0] = %lX\n", (kulong)&ioR2yP1.r2yCmn.lintlv.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.r2yCmn.lintlv[1] = %lX\n", (kulong)&ioR2yP1.r2yCmn.lintlv.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.r2yCmn.lintsel = %lX\n", (kulong)&ioR2yP1.r2yCmn.lintsel);
	R2yTest2_RS_PRINTF("ioR2yP1.r2yCmn.r2ymode = %lX\n", (kulong)&ioR2yP1.r2yCmn.r2ymode);
	R2yTest2_RS_PRINTF("ioR2yP1.r2yCmn.ramaen = %lX\n", (kulong)&ioR2yP1.r2yCmn.ramaen);

	R2yTest2_RS_PRINTF("ioR2yP1.yyr.yyrtrg = %lX\n", (kulong)&ioR2yP1.yyr.yyrtrg);
	R2yTest2_RS_PRINTF("ioR2yP1.yyr.yyrctl = %lX\n", (kulong)&ioR2yP1.yyr.yyrctl);
	R2yTest2_RS_PRINTF("ioR2yP1.yyr.dinctl = %lX\n", (kulong)&ioR2yP1.yyr.dinctl);

	R2yTest2_RS_PRINTF("ioR2yP1.yyr.yyra[0] = %lX\n", (kulong)&ioR2yP1.yyr.yyra.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyr.yyra[1] = %lX\n", (kulong)&ioR2yP1.yyr.yyra.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyr.yyra[2] = %lX\n", (kulong)&ioR2yP1.yyr.yyra.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyr.yyrofs = %lX\n", (kulong)&ioR2yP1.yyr.yyrofs);
	R2yTest2_RS_PRINTF("ioR2yP1.yyr.yyrdef = %lX\n", (kulong)&ioR2yP1.yyr.yyrdef);
	R2yTest2_RS_PRINTF("ioR2yP1.yyr.YYRHSIZ = %lX\n", (kulong)&ioR2yP1.yyr.yyrhsiz);
	R2yTest2_RS_PRINTF("ioR2yP1.yyr.yyrvsiz = %lX\n", (kulong)&ioR2yP1.yyr.yyrvsiz);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywtrg = %lX\n", (kulong)&ioR2yP1.yyw.yywtrg);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywctl = %lX\n", (kulong)&ioR2yP1.yyw.yywctl);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywbank = %lX\n", (kulong)&ioR2yP1.yyw.yywbank);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywkpp = %lX\n", (kulong)&ioR2yP1.yyw.yywkpp);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw0md = %lX\n", (kulong)&ioR2yP1.yyw.yyw0md);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw1md = %lX\n", (kulong)&ioR2yP1.yyw.yyw1md);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw2md = %lX\n", (kulong)&ioR2yP1.yyw.yyw2md);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.hstmd = %lX\n", (kulong)&ioR2yP1.yyw.hstmd);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.hsth  = %lX\n", (kulong)&ioR2yP1.yyw.hsth);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.hstv  = %lX\n", (kulong)&ioR2yP1.yyw.hstv);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw0a[0][0] = %lX\n", (kulong)&ioR2yP1.yyw.yyw0a.word[0][0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw0a[0][1] = %lX\n", (kulong)&ioR2yP1.yyw.yyw0a.word[0][1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw0a[2][2] = %lX\n", (kulong)&ioR2yP1.yyw.yyw0a.word[2][2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw0a[2][3] = %lX\n", (kulong)&ioR2yP1.yyw.yyw0a.word[2][3]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.V[0] = %lX\n", (kulong)&ioR2yP1.yyw.yyw0def.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.V[1] = %lX\n", (kulong)&ioR2yP1.yyw.V.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw0ofsx[0] = %lX\n", (kulong)&ioR2yP1.yyw.yyw0ofsx.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw0ofsx[1] = %lX\n", (kulong)&ioR2yP1.yyw.yyw0ofsx.word[1]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz0hsta = %lX\n", (kulong)&ioR2yP1.yyw.rsz0hsta);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz0hpit = %lX\n", (kulong)&ioR2yP1.yyw.rsz0hpit);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.RSZ0VSTA = %lX\n", (kulong)&ioR2yP1.yyw.rsz0vsta);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz0vpit = %lX\n", (kulong)&ioR2yP1.yyw.rsz0vpit);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.pcemd = %lX\n", (kulong)&ioR2yP1.yyw.pcemd);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.pcexy = %lX\n", (kulong)&ioR2yP1.yyw.pcexy);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.pcec  = %lX\n", (kulong)&ioR2yP1.yyw.pcec);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.pceh  = %lX\n", (kulong)&ioR2yP1.yyw.pceh);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trm0h = %lX\n", (kulong)&ioR2yP1.yyw.trm0h);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trm0v = %lX\n", (kulong)&ioR2yP1.yyw.trm0v);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trmbh = %lX\n", (kulong)&ioR2yP1.yyw.trmbh);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trmbv = %lX\n", (kulong)&ioR2yP1.yyw.trmbv);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trmch = %lX\n", (kulong)&ioR2yP1.yyw.trmch);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trmcv = %lX\n", (kulong)&ioR2yP1.yyw.trmcv);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw0ltt = %lX\n", (kulong)&ioR2yP1.yyw.yyw0ltt);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywaa[0][0] = %lX\n", (kulong)&ioR2yP1.yyw.yywaa.word[0][0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywaa[0][1] = %lX\n", (kulong)&ioR2yP1.yyw.yywaa.word[0][1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywaa[1][2] = %lX\n", (kulong)&ioR2yP1.yyw.yywaa.word[1][2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywaa[1][3] = %lX\n", (kulong)&ioR2yP1.yyw.yywaa.word[1][3]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywadef = %lX\n", (kulong)&ioR2yP1.yyw.yywadef);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywaofsx[0] = %lX\n", (kulong)&ioR2yP1.yyw.yywaofsx.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yywaofsx[1] = %lX\n", (kulong)&ioR2yP1.yyw.yywaofsx.word[1]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw1a[0][0] = %lX\n", (kulong)&ioR2yP1.yyw.yyw1a.word[0][0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw1a[0][1] = %lX\n", (kulong)&ioR2yP1.yyw.yyw1a.word[0][1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw1a[2][2] = %lX\n", (kulong)&ioR2yP1.yyw.yyw1a.word[2][2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw1a[2][3] = %lX\n", (kulong)&ioR2yP1.yyw.yyw1a.word[2][3]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw1def[0] = %lX\n", (kulong)&ioR2yP1.yyw.yyw1def.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw1def[1] = %lX\n", (kulong)&ioR2yP1.yyw.yyw1def.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz1hsta = %lX\n", (kulong)&ioR2yP1.yyw.rsz1hsta);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz1hpit = %lX\n", (kulong)&ioR2yP1.yyw.rsz1hpit);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz1vsta = %lX\n", (kulong)&ioR2yP1.yyw.rsz1vsta);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz1vpit = %lX\n", (kulong)&ioR2yP1.yyw.rsz1vpit);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trm1h = %lX\n", (kulong)&ioR2yP1.yyw.trm1h);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trm1v = %lX\n", (kulong)&ioR2yP1.yyw.trm1v);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw2a[0] = %lX\n", (kulong)&ioR2yP1.yyw.yyw2a.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw2a[3] = %lX\n", (kulong)&ioR2yP1.yyw.yyw2a.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.yyw2def = %lX\n", (kulong)&ioR2yP1.yyw.yyw2def);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz2hsta = %lX\n", (kulong)&ioR2yP1.yyw.rsz2hsta);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz2hpit = %lX\n", (kulong)&ioR2yP1.yyw.rsz2hpit);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz2vsta = %lX\n", (kulong)&ioR2yP1.yyw.rsz2vsta);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.rsz2vpit = %lX\n", (kulong)&ioR2yP1.yyw.rsz2vpit);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trm2h = %lX\n", (kulong)&ioR2yP1.yyw.trm2h);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.trm2v = %lX\n", (kulong)&ioR2yP1.yyw.trm2v);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0ctl = %lX\n", (kulong)&ioR2yP1.yyw.ee0ctl);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0hpfk[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0hpfk.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0hpfk[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0hpfk.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0nrlv = %lX\n", (kulong)&ioR2yP1.yyw.ee0nrlv);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0corpof = %lX\n", (kulong)&ioR2yP1.yyw.ee0corpof);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0corpga = %lX\n", (kulong)&ioR2yP1.yyw.ee0corpga);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0corpbd = %lX\n", (kulong)&ioR2yP1.yyw.ee0corpbd);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0cormof = %lX\n", (kulong)&ioR2yP1.yyw.ee0cormof);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0cormga = %lX\n", (kulong)&ioR2yP1.yyw.ee0cormga);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0cormbd = %lX\n", (kulong)&ioR2yP1.yyw.ee0cormbd);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclsup = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclsup);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpof[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpof.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpga[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpga[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpga[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpga.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpga[3] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpga.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpga[4] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpga.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpbd[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpbd.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpbd[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpbd.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclpbd[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclpbd.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmof[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmof.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmga[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmga[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmga[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmga.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmga[3] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmga.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmga[4] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmga.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmbd[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmbd.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmbd[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmbd.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0sclmbd[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee0sclmbd.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonpof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonpof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonpof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonpof.word[1]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonpga[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonpga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonpga[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonpga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonpga[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonpga.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonpbd = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonpbd);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonmof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonmof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonmof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonmof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonmga[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonmga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonmga[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonmga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonmga[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonmga.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0tonmbd = %lX\n", (kulong)&ioR2yP1.yyw.ee0tonmbd);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0clppof = %lX\n", (kulong)&ioR2yP1.yyw.ee0clppof);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0clppga = %lX\n", (kulong)&ioR2yP1.yyw.ee0clppga);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0clppbd = %lX\n", (kulong)&ioR2yP1.yyw.ee0clppbd);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0clpmof = %lX\n", (kulong)&ioR2yP1.yyw.ee0clpmof);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0clpmga = %lX\n", (kulong)&ioR2yP1.yyw.ee0clpmga);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee0clpmbd = %lX\n", (kulong)&ioR2yP1.yyw.ee0clpmbd);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1ctl = %lX\n", (kulong)&ioR2yP1.yyw.ee1ctl);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1hpfk[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1hpfk.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1hpfk[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1hpfk.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1nrlv = %lX\n", (kulong)&ioR2yP1.yyw.ee1nrlv);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1corpof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1corpof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1corpof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1corpof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1corpga = %lX\n", (kulong)&ioR2yP1.yyw.ee1corpga);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1corpbd[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1corpbd.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1corpbd[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1corpbd.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1cormof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1cormof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1cormof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1cormof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1cormga = %lX\n", (kulong)&ioR2yP1.yyw.ee1cormga);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1cormbd[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1cormbd.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1cormbd[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1cormbd.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclsup = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclsup);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpof[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpof.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpga[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpga[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpga[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpga.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpga[3] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpga.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpga[4] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpga.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpbd[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpbd.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpbd[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpbd.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpbd[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpbd.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpbd[3] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpbd.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclpbd[4] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclpbd.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmof[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmof.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmga[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmga[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmga[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmga.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmga[3] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmga.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmga[4] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmga.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmbd[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmbd.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmbd[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmbd.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmbd[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmbd.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmbd[3] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmbd.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1sclmbd[4] = %lX\n", (kulong)&ioR2yP1.yyw.ee1sclmbd.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonpof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonpof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonpof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonpof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonpof[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonpof.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonpga[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonpga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonpga[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonpga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonpga[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonpga.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonpbd[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonpbd.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonpbd[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonpbd.word[1]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonmof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonmof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonmof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonmof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonmof[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonmof.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonmga[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonmga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonmga[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonmga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonmga[2] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonmga.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonmbd[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonmbd.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1tonmbd[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1tonmbd.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1clppof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1clppof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1clppof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1clppof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1clppga = %lX\n", (kulong)&ioR2yP1.yyw.ee1clppga);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1clppbd = %lX\n", (kulong)&ioR2yP1.yyw.ee1clppbd);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1clpmof[0] = %lX\n", (kulong)&ioR2yP1.yyw.ee1clpmof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1clpmof[1] = %lX\n", (kulong)&ioR2yP1.yyw.ee1clpmof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1clpmga = %lX\n", (kulong)&ioR2yP1.yyw.ee1clpmga);
	R2yTest2_RS_PRINTF("ioR2yP1.yyw.ee1clpmbd = %lX\n", (kulong)&ioR2yP1.yyw.ee1clpmbd);

	/* f_r2y tbl */
	R2yTest2_RS_PRINTF("ioR2yTblP1.tc[0] = %lX\n", (kulong)&ioR2yTblP1.tc.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tc[1] = %lX\n", (kulong)&ioR2yTblP1.tc.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tc[1022] = %lX\n", (kulong)&ioR2yTblP1.tc.hword[1022]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tc[1023] = %lX\n", (kulong)&ioR2yTblP1.tc.hword[1023]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.tctdata[0] = %lX\n", (kulong)&ioR2yTblP1.tctdata.word[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tctdata[1] = %lX\n", (kulong)&ioR2yTblP1.tctdata.word[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tctdata[1198] = %lX\n", (kulong)&ioR2yTblP1.tctdata.word[1198]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tctdata[1199] = %lX\n", (kulong)&ioR2yTblP1.tctdata.word[1199]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsydata[0] = %lX\n", (kulong)&ioR2yTblP1.tchsydata.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsydata[1] = %lX\n", (kulong)&ioR2yTblP1.tchsydata.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsydata[4094] = %lX\n", (kulong)&ioR2yTblP1.tchsydata.hword[4094]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsydata[4095] = %lX\n", (kulong)&ioR2yTblP1.tchsydata.hword[4095]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsrdata[0] = %lX\n", (kulong)&ioR2yTblP1.tchsrdata.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsrdata[1] = %lX\n", (kulong)&ioR2yTblP1.tchsrdata.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsrdata[254] = %lX\n", (kulong)&ioR2yTblP1.tchsrdata.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsrdata[255] = %lX\n", (kulong)&ioR2yTblP1.tchsrdata.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsgdata[0] = %lX\n", (kulong)&ioR2yTblP1.tchsgdata.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsgdata[1] = %lX\n", (kulong)&ioR2yTblP1.tchsgdata.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsgdata[254] = %lX\n", (kulong)&ioR2yTblP1.tchsgdata.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsgdata[255] = %lX\n", (kulong)&ioR2yTblP1.tchsgdata.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsbdata[0] = %lX\n", (kulong)&ioR2yTblP1.tchsbdata.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsbdata[1] = %lX\n", (kulong)&ioR2yTblP1.tchsbdata.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsbdata[254] = %lX\n", (kulong)&ioR2yTblP1.tchsbdata.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.tchsbdata[255] = %lX\n", (kulong)&ioR2yTblP1.tchsbdata.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrgbdf[0] = %lX\n", (kulong)&ioR2yTblP1.gmrgbdf.dword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrgbdf[1] = %lX\n", (kulong)&ioR2yTblP1.gmrgbdf.dword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrgbdf[254] = %lX\n", (kulong)&ioR2yTblP1.gmrgbdf.dword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrgbdf[255] = %lX\n", (kulong)&ioR2yTblP1.gmrgbdf.dword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrdf[0] = %lX\n", (kulong)&ioR2yTblP1.gmrdf.dword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrdf[1] = %lX\n", (kulong)&ioR2yTblP1.gmrdf.dword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrdf[254] = %lX\n", (kulong)&ioR2yTblP1.gmrdf.dword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrdf[255] = %lX\n", (kulong)&ioR2yTblP1.gmrdf.dword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmgdf[0] = %lX\n", (kulong)&ioR2yTblP1.gmgdf.dword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmgdf[1] = %lX\n", (kulong)&ioR2yTblP1.gmgdf.dword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmgdf[254] = %lX\n", (kulong)&ioR2yTblP1.gmgdf.dword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmgdf[255] = %lX\n", (kulong)&ioR2yTblP1.gmgdf.dword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmbdf[0] = %lX\n", (kulong)&ioR2yTblP1.gmbdf.dword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmbdf[1] = %lX\n", (kulong)&ioR2yTblP1.gmbdf.dword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmbdf[254] = %lX\n", (kulong)&ioR2yTblP1.gmbdf.dword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmbdf[255] = %lX\n", (kulong)&ioR2yTblP1.gmbdf.dword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmybdf[0] = %lX\n", (kulong)&ioR2yTblP1.gmybdf.dword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmybdf[1] = %lX\n", (kulong)&ioR2yTblP1.gmybdf.dword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmybdf[254] = %lX\n", (kulong)&ioR2yTblP1.gmybdf.dword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmybdf[255] = %lX\n", (kulong)&ioR2yTblP1.gmybdf.dword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrgbfl[0] = %lX\n", (kulong)&ioR2yTblP1.gmrgbfl.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrgbfl[1] = %lX\n", (kulong)&ioR2yTblP1.gmrgbfl.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrgbfl[254] = %lX\n", (kulong)&ioR2yTblP1.gmrgbfl.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrgbfl[255] = %lX\n", (kulong)&ioR2yTblP1.gmrgbfl.hword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrfl[0] = %lX\n", (kulong)&ioR2yTblP1.gmrfl.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrfl[1] = %lX\n", (kulong)&ioR2yTblP1.gmrfl.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrfl[254] = %lX\n", (kulong)&ioR2yTblP1.gmrfl.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmrfl[255] = %lX\n", (kulong)&ioR2yTblP1.gmrfl.hword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmgfl[0] = %lX\n", (kulong)&ioR2yTblP1.gmgfl.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmgfl[1] = %lX\n", (kulong)&ioR2yTblP1.gmgfl.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmgfl[254] = %lX\n", (kulong)&ioR2yTblP1.gmgfl.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmgfl[255] = %lX\n", (kulong)&ioR2yTblP1.gmgfl.hword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmbfl[0] = %lX\n", (kulong)&ioR2yTblP1.gmbfl.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmbfl[1] = %lX\n", (kulong)&ioR2yTblP1.gmbfl.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmbfl[254] = %lX\n", (kulong)&ioR2yTblP1.gmbfl.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmbfl[255] = %lX\n", (kulong)&ioR2yTblP1.gmbfl.hword[255]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmybfl[0] = %lX\n", (kulong)&ioR2yTblP1.gmybfl.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmybfl[1] = %lX\n", (kulong)&ioR2yTblP1.gmybfl.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmybfl[254] = %lX\n", (kulong)&ioR2yTblP1.gmybfl.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.gmybfl[255] = %lX\n", (kulong)&ioR2yTblP1.gmybfl.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.eghwscl[0] = %lX\n", (kulong)&ioR2yTblP1.eghwscl.byte[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eghwscl[1] = %lX\n", (kulong)&ioR2yTblP1.eghwscl.byte[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eghwscl[510] = %lX\n", (kulong)&ioR2yTblP1.eghwscl.byte[510]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eghwscl[511] = %lX\n", (kulong)&ioR2yTblP1.eghwscl.byte[511]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eghwton[0] = %lX\n", (kulong)&ioR2yTblP1.eghwton.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eghwton[1] = %lX\n", (kulong)&ioR2yTblP1.eghwton.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eghwton[254] = %lX\n", (kulong)&ioR2yTblP1.eghwton.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eghwton[255] = %lX\n", (kulong)&ioR2yTblP1.eghwton.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.egmwscl[0] = %lX\n", (kulong)&ioR2yTblP1.egmwscl.byte[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmwscl[1] = %lX\n", (kulong)&ioR2yTblP1.egmwscl.byte[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmwscl[510] = %lX\n", (kulong)&ioR2yTblP1.egmwscl.byte[510]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmwscl[511] = %lX\n", (kulong)&ioR2yTblP1.egmwscl.byte[511]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmwton[0] = %lX\n", (kulong)&ioR2yTblP1.egmwton.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmwton[1] = %lX\n", (kulong)&ioR2yTblP1.egmwton.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmwton[254] = %lX\n", (kulong)&ioR2yTblP1.egmwton.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmwton[255] = %lX\n", (kulong)&ioR2yTblP1.egmwton.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.eglwscl[0] = %lX\n", (kulong)&ioR2yTblP1.eglwscl.byte[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eglwscl[1] = %lX\n", (kulong)&ioR2yTblP1.eglwscl.byte[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eglwscl[510] = %lX\n", (kulong)&ioR2yTblP1.eglwscl.byte[510]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eglwscl[511] = %lX\n", (kulong)&ioR2yTblP1.eglwscl.byte[511]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eglwton[0] = %lX\n", (kulong)&ioR2yTblP1.eglwton.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eglwton[1] = %lX\n", (kulong)&ioR2yTblP1.eglwton.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eglwton[254] = %lX\n", (kulong)&ioR2yTblP1.eglwton.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.eglwton[255] = %lX\n", (kulong)&ioR2yTblP1.eglwton.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.egmpscl[0][0] = %lX\n", (kulong)&ioR2yTblP1.egmpscl.hword[0][0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmpscl[0][1] = %lX\n", (kulong)&ioR2yTblP1.egmpscl.hword[0][1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmpscl[12][15] = %lX\n", (kulong)&ioR2yTblP1.egmpscl.hword[12][15]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.egmpscl[12][16] = %lX\n", (kulong)&ioR2yTblP1.egmpscl.hword[12][16]);

	/* jdsr2y tbl */
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblr[0] = %lX\n", (kulong)&ioR2yTblP1.dkntblr.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblr[1] = %lX\n", (kulong)&ioR2yTblP1.dkntblr.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblr[254] = %lX\n", (kulong)&ioR2yTblP1.dkntblr.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblr[255] = %lX\n", (kulong)&ioR2yTblP1.dkntblr.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblg[0] = %lX\n", (kulong)&ioR2yTblP1.dkntblg.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblg[1] = %lX\n", (kulong)&ioR2yTblP1.dkntblg.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblg[254] = %lX\n", (kulong)&ioR2yTblP1.dkntblg.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblg[255] = %lX\n", (kulong)&ioR2yTblP1.dkntblg.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblb[0] = %lX\n", (kulong)&ioR2yTblP1.dkntblb.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblb[1] = %lX\n", (kulong)&ioR2yTblP1.dkntblb.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblb[254] = %lX\n", (kulong)&ioR2yTblP1.dkntblb.hword[254]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.dkntblb[255] = %lX\n", (kulong)&ioR2yTblP1.dkntblb.hword[255]);

	R2yTest2_RS_PRINTF("ioR2yTblP1.hsty[0] = %lX\n", (kulong)&ioR2yTblP1.hsty.hword[0]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.hsty[1] = %lX\n", (kulong)&ioR2yTblP1.hsty.hword[1]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.hsty[126] = %lX\n", (kulong)&ioR2yTblP1.hsty.hword[126]);
	R2yTest2_RS_PRINTF("ioR2yTblP1.hsty[127] = %lX\n", (kulong)&ioR2yTblP1.hsty.hword[127]);

	R2yTest2_RS_PRINTF(" \n");

	/* f_r2y */
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cntl.cntl = %lX\n", (kulong)&ioR2yP2.fR2y.cntl.cntl);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cntl.r2yflag = %lX\n", (kulong)&ioR2yP2.fR2y.cntl.r2yflag);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cntl.r2yinte = %lX\n", (kulong)&ioR2yP2.fR2y.cntl.r2yinte);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cntl.r2yintf = %lX\n", (kulong)&ioR2yP2.fR2y.cntl.r2yintf);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cntl.fltaen = %lX\n", (kulong)&ioR2yP2.fR2y.cntl.fltaen);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.ofg.ofst[0] = %lX\n", (kulong)&ioR2yP2.fR2y.ofg.ofst.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.ofg.ofst[1] = %lX\n", (kulong)&ioR2yP2.fR2y.ofg.ofst.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.ofg.wbgar[0] = %lX\n", (kulong)&ioR2yP2.fR2y.ofg.wbgar.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.ofg.wbgar[1] = %lX\n", (kulong)&ioR2yP2.fR2y.ofg.wbgar.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.ofg.WBLV[0] = %lX\n", (kulong)&ioR2yP2.fR2y.ofg.WBLV.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.ofg.WBLV[1] = %lX\n", (kulong)&ioR2yP2.fR2y.ofg.WBLV.word[1]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0ctl = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0ctl);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0k[0] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0k.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0k[1] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0k.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0k[2] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0k.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0k[3] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0k.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0k[4] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0k.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0ybof[0] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0ybof.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0ybof[1] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0ybof.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0ybga[0] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0ybga.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0ybga[1] = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0ybga.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.cc0ybbd = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.cc0ybbd);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.cca0.ccyc = %lX\n", (kulong)&ioR2yP2.fR2y.cca0.ccyc);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcyc[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcyc.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcyc[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcyc.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcyc[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcyc.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcyc[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcyc.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcyc[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcyc.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcb1ab = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcb1ab);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcb1cd = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcb1cd);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcb2ab = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcb2ab);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcb2cd = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcb2cd);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcb3ab = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcb3ab);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcb3cd = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcb3cd);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcb4ab = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcb4ab);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcb4cd = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcb4cd);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcid1 = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcid1);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcid2 = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcid2);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcid3 = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcid3);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.mcid4 = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcid4);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKA_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcka.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKB_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckb.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKC_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckc.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKD_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckd.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKE_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcke.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKF_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckf.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKG_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckg.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKH_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckh.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKI_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcki.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKJ_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckj.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKK_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckk.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck0.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_0[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck0.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_0[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck0.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck1.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_1[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck1.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_1[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck1.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck2.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_2[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck2.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_2[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck2.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck3.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_3[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck3.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_3[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck3.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck4.word[2]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_4[3] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck4.word[3]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCKL_4[4] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mckl.mck4.word[4]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl0.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl1.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl2.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl3.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLA_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcla.mcl4.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl0.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl1.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl2.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl3.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLB_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclb.mcl4.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl0.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl1.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl2.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl3.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_4[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl4.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_4[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl4.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLC_4[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mclc.mcl4.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_0[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl0.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_0[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl0.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_0[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl0.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_1[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl1.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_1[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl1.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_1[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl1.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_2[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl2.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_2[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl2.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_2[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl2.word[2]);

	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_3[0] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl3.word[0]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_3[1] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl3.word[1]);
	R2yTest2_RS_PRINTF("ioR2yP2.fR2y.mcc.MCLD_3[2] = %lX\n", (kulong)&ioR2yP2.fR2y.mcc.mcld.mcl3.word[2]);
#endif
}

R2yTest2 *r2y_test2_new(void)
{
		R2yTest2* self = k_object_new_with_private(R2Y_TYPE_TEST2, sizeof(R2yTest2Private));
		return self;
}
