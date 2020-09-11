/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :申雨
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
*/


#include <stdio.h>
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
#include "shdrtest.h"


G_DEFINE_TYPE(ShdrTest, shdr_test, G_TYPE_OBJECT);

#define SHDR_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), SHDR_TYPE_TEST, ShdrTestPrivate));


struct _ShdrTestPrivate
{
	 gint preserved;
};
/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	run_od(AbsHeaderTest *self);
/**
 * IMPL
 */
static void shdr_test_class_init(ShdrTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ShdrTestPrivate));
	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);

	absClass->run = run_od;
}

static void shdr_test_init(ShdrTest *self)
{
	ShdrTestPrivate *priv = SHDR_TEST_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(shdr_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	ShdrTest *self = SHDR_TEST(object);
	ShdrTestPrivate *priv = SHDR_TEST_GET_PRIVATE(self);

	G_OBJECT_CLASS(shdr_test_parent_class)->finalize(object);
}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void shdr_test()
{
#if 0
#define ShdrTest_IO_SHDR	(*ioShdr1)
	volatile IoJdsshdr* ioShdr1	= (gpointer)0x2886A000;
#endif

	IntErnals_RS_printf("SHDR\n");
#if 0
	IntErnals_RS_printf("ShdrTest_IO_SHDR.shdractl0     = %x\n", (guint)&ShdrTest_IO_SHDR.shdractl0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.shdractl1     = %x\n", (guint)&ShdrTest_IO_SHDR.shdractl1 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.shdractl2     = %x\n", (guint)&ShdrTest_IO_SHDR.shdractl2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.shdrint0      = %x\n", (guint)&ShdrTest_IO_SHDR.shdrint0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.shdrint1      = %x\n", (guint)&ShdrTest_IO_SHDR.shdrint1 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axmd          = %x\n", (guint)&ShdrTest_IO_SHDR.axmd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlara     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlara );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlarb     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlarb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlarc     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlarc );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlard     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlard );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlawa     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlawa );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlawb     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlawb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlawc     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlawc );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlra      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlra  );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlrb      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlrb  );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlrc      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlrc  );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlrd      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlrd  );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlwa      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlwa  );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlwb      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlwb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axictlwc      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlwc );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.coremon0      = %x\n", (guint)&ShdrTest_IO_SHDR.coremon0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.coremon1      = %x\n", (guint)&ShdrTest_IO_SHDR.coremon1 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.dgtRsel      = %x\n", (guint)&ShdrTest_IO_SHDR.dgtRsel );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrAddrA   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrA );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrAddrB   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrB );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrAddrC   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrC );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrAddrD   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrD );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrAddrE   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrE );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrAddrF   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrF );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrGhsizeA = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeA );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrGhsizeB = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeB );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrGhsizeC = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeC );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrGhsizeD = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeD );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrGhsizeE = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeE );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrGhsizeF = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeF );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrVfm      = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVfm );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwAddrB   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrB );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwAddrE   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrE );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwAddrF   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrF );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwAddrG   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrG );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwAddrH   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrH );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwAddrI   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrI );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwGhsizeB = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeB );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwGhsizeE = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeE );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwGhsizeF = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeF );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwGhsizeG = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeG );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwGhsizeH = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeH );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwGhsizeI = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeI );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwVfm      = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwVfm );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwBaA     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwBaA );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwBaC     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwBaC );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwBaD     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwBaD );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwFwA     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwFwA );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwFwC     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwFwC );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrwFwD     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwFwD );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.shdrifrm      = %x\n", (guint)&ShdrTest_IO_SHDR.shdrifrm );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.shdrofrm      = %x\n", (guint)&ShdrTest_IO_SHDR.shdrofrm );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrHsizeA  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeA );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrHsizeB  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeB );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrHsizeC  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeC );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrHsizeD  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeD );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrHsizeE  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeE );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrVsizeA  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeA );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrVsizeB  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeB );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrVsizeC  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeC );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrVsizeD  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeD );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sdrrVsizeE  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeE );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.exmag         = %x\n", (guint)&ShdrTest_IO_SHDR.exmag );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.remval        = %x\n", (guint)&ShdrTest_IO_SHDR.remval );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.shift         = %x\n", (guint)&ShdrTest_IO_SHDR.shift );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mrgn          = %x\n", (guint)&ShdrTest_IO_SHDR.mrgn );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.flwcnt        = %x\n", (guint)&ShdrTest_IO_SHDR.flwcnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.tmode         = %x\n", (guint)&ShdrTest_IO_SHDR.tmode );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.modesel       = %x\n", (guint)&ShdrTest_IO_SHDR.modesel );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mcModesel    = %x\n", (guint)&ShdrTest_IO_SHDR.mcModesel );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.compIncfmsel = %x\n", (guint)&ShdrTest_IO_SHDR.compIncfmsel );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.bypasson      = %x\n", (guint)&ShdrTest_IO_SHDR.bypasson );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.axisize       = %x\n", (guint)&ShdrTest_IO_SHDR.axisize );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.lint          = %x\n", (guint)&ShdrTest_IO_SHDR.lint );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wrstartaddr   = %x\n", (guint)&ShdrTest_IO_SHDR.wrstartaddr );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rdstartaddr   = %x\n", (guint)&ShdrTest_IO_SHDR.rdstartaddr );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.premd         = %x\n", (guint)&ShdrTest_IO_SHDR.premd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.y2rcoef       = %x\n", (guint)&ShdrTest_IO_SHDR.y2rcoef );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.prey2rclpul0  = %x\n", (guint)&ShdrTest_IO_SHDR.prey2rclpul0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.prey2rclpll0  = %x\n", (guint)&ShdrTest_IO_SHDR.prey2rclpll0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.prey2rclpus   = %x\n", (guint)&ShdrTest_IO_SHDR.prey2rclpus  );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.prey2rclpls   = %x\n", (guint)&ShdrTest_IO_SHDR.prey2rclpls  );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.r2ycoef       = %x\n", (guint)&ShdrTest_IO_SHDR.r2ycoef );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.prer2yclpul   = %x\n", (guint)&ShdrTest_IO_SHDR.prer2yclpul );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.prer2yclpll   = %x\n", (guint)&ShdrTest_IO_SHDR.prer2yclpll );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.prer2yclpus   = %x\n", (guint)&ShdrTest_IO_SHDR.prer2yclpus );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.prer2yclpls   = %x\n", (guint)&ShdrTest_IO_SHDR.prer2yclpls );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sknofs        = %x\n", (guint)&ShdrTest_IO_SHDR.sknofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sknsl         = %x\n", (guint)&ShdrTest_IO_SHDR.sknsl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sknb1         = %x\n", (guint)&ShdrTest_IO_SHDR.sknb1 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.sknb2         = %x\n", (guint)&ShdrTest_IO_SHDR.sknb2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.lknofs        = %x\n", (guint)&ShdrTest_IO_SHDR.lknofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.lknsl         = %x\n", (guint)&ShdrTest_IO_SHDR.lknsl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.lknb1         = %x\n", (guint)&ShdrTest_IO_SHDR.lknb1 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.lknb2         = %x\n", (guint)&ShdrTest_IO_SHDR.lknb2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.epbd          = %x\n", (guint)&ShdrTest_IO_SHDR.epbd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.epof          = %x\n", (guint)&ShdrTest_IO_SHDR.epof );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.epbld         = %x\n", (guint)&ShdrTest_IO_SHDR.epbld );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.fdweight      = %x\n", (guint)&ShdrTest_IO_SHDR.fdweight );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mvcnt         = %x\n", (guint)&ShdrTest_IO_SHDR.mvcnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.bldrofs       = %x\n", (guint)&ShdrTest_IO_SHDR.bldrofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.bldrsl        = %x\n", (guint)&ShdrTest_IO_SHDR.bldrsl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.bldrb         = %x\n", (guint)&ShdrTest_IO_SHDR.bldrb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtr2ycoef   = %x\n", (guint)&ShdrTest_IO_SHDR.wghtr2ycoef );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtr2yclp    = %x\n", (guint)&ShdrTest_IO_SHDR.wghtr2yclp );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtbase      = %x\n", (guint)&ShdrTest_IO_SHDR.wghtbase );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtrofs      = %x\n", (guint)&ShdrTest_IO_SHDR.wghtrofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtgofs      = %x\n", (guint)&ShdrTest_IO_SHDR.wghtgofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtbofs      = %x\n", (guint)&ShdrTest_IO_SHDR.wghtbofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtrsl       = %x\n", (guint)&ShdrTest_IO_SHDR.wghtrsl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtgsl       = %x\n", (guint)&ShdrTest_IO_SHDR.wghtgsl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtbsl       = %x\n", (guint)&ShdrTest_IO_SHDR.wghtbsl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtrb        = %x\n", (guint)&ShdrTest_IO_SHDR.wghtrb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtgb        = %x\n", (guint)&ShdrTest_IO_SHDR.wghtgb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.wghtbb        = %x\n", (guint)&ShdrTest_IO_SHDR.wghtbb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.isoth         = %x\n", (guint)&ShdrTest_IO_SHDR.isoth );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.isocoef       = %x\n", (guint)&ShdrTest_IO_SHDR.isocoef );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.exp77md       = %x\n", (guint)&ShdrTest_IO_SHDR.exp77md );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.fmdsel        = %x\n", (guint)&ShdrTest_IO_SHDR.fmdsel );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.tlut          = %x\n", (guint)&ShdrTest_IO_SHDR.tlut );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.pmskmd        = %x\n", (guint)&ShdrTest_IO_SHDR.pmskmd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.spnren        = %x\n", (guint)&ShdrTest_IO_SHDR.spnren );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.spebd         = %x\n", (guint)&ShdrTest_IO_SHDR.spebd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.speof         = %x\n", (guint)&ShdrTest_IO_SHDR.speof );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.spebld        = %x\n", (guint)&ShdrTest_IO_SHDR.spebld );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.msky2rclpul   = %x\n", (guint)&ShdrTest_IO_SHDR.msky2rclpul );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.msky2rclpll   = %x\n", (guint)&ShdrTest_IO_SHDR.msky2rclpll );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.msky2rclpus   = %x\n", (guint)&ShdrTest_IO_SHDR.msky2rclpus );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.msky2rclpls   = %x\n", (guint)&ShdrTest_IO_SHDR.msky2rclpls );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.alpha         = %x\n", (guint)&ShdrTest_IO_SHDR.alpha );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.lpfc          = %x\n", (guint)&ShdrTest_IO_SHDR.lpfc );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.bldofs        = %x\n", (guint)&ShdrTest_IO_SHDR.bldofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.bldsl         = %x\n", (guint)&ShdrTest_IO_SHDR.bldsl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.bldb          = %x\n", (guint)&ShdrTest_IO_SHDR.bldb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.normgain      = %x\n", (guint)&ShdrTest_IO_SHDR.normgain );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.normofs       = %x\n", (guint)&ShdrTest_IO_SHDR.normofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mskmd         = %x\n", (guint)&ShdrTest_IO_SHDR.mskmd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.bldsel        = %x\n", (guint)&ShdrTest_IO_SHDR.bldsel );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.alphasel      = %x\n", (guint)&ShdrTest_IO_SHDR.alphasel );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.alphaval      = %x\n", (guint)&ShdrTest_IO_SHDR.alphaval );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.postsft1rnd   = %x\n", (guint)&ShdrTest_IO_SHDR.postsft1rnd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.posty2rcoef   = %x\n", (guint)&ShdrTest_IO_SHDR.posty2rcoef );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.posty2rclpthu = %x\n", (guint)&ShdrTest_IO_SHDR.posty2rclpthu );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.posty2rclpthl = %x\n", (guint)&ShdrTest_IO_SHDR.posty2rclpthl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.postsel1      = %x\n", (guint)&ShdrTest_IO_SHDR.postsel1 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.postmulqpos   = %x\n", (guint)&ShdrTest_IO_SHDR.postmulqpos );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.evknb         = %x\n", (guint)&ShdrTest_IO_SHDR.evknb );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.evknofs       = %x\n", (guint)&ShdrTest_IO_SHDR.evknofs );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.evknsl        = %x\n", (guint)&ShdrTest_IO_SHDR.evknsl );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.postsel0      = %x\n", (guint)&ShdrTest_IO_SHDR.postsel0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.hdrcssmd      = %x\n", (guint)&ShdrTest_IO_SHDR.hdrcssmd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.ch0mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch0mode );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.ch1mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch1mode );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.ch2mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch2mode );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.ch3mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch3mode );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.ch4mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch4mode );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.ch5mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch5mode );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.woutsz        = %x\n", (guint)&ShdrTest_IO_SHDR.woutsz );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rszhcnt2     = %x\n", (guint)&ShdrTest_IO_SHDR.rszhcnt2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rszhcnt3     = %x\n", (guint)&ShdrTest_IO_SHDR.rszhcnt3 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rszhcnt4     = %x\n", (guint)&ShdrTest_IO_SHDR.rszhcnt4 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rszhcnt5     = %x\n", (guint)&ShdrTest_IO_SHDR.rszhcnt5 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rszvcnt2     = %x\n", (guint)&ShdrTest_IO_SHDR.rszvcnt2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rszvcnt3     = %x\n", (guint)&ShdrTest_IO_SHDR.rszvcnt3 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rszvcnt4     = %x\n", (guint)&ShdrTest_IO_SHDR.rszvcnt4 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.rszvcnt5     = %x\n", (guint)&ShdrTest_IO_SHDR.rszvcnt5 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.trmsta2      = %x\n", (guint)&ShdrTest_IO_SHDR.trmsta2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.trmsta3      = %x\n", (guint)&ShdrTest_IO_SHDR.trmsta3 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.trmsta4      = %x\n", (guint)&ShdrTest_IO_SHDR.trmsta4 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.trmsta5      = %x\n", (guint)&ShdrTest_IO_SHDR.trmsta5 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcofst0     = %x\n", (guint)&ShdrTest_IO_SHDR.drcofst0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcofst2     = %x\n", (guint)&ShdrTest_IO_SHDR.drcofst2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcofst3     = %x\n", (guint)&ShdrTest_IO_SHDR.drcofst3 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcgain0     = %x\n", (guint)&ShdrTest_IO_SHDR.drcgain0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcgain2     = %x\n", (guint)&ShdrTest_IO_SHDR.drcgain2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcgain3     = %x\n", (guint)&ShdrTest_IO_SHDR.drcgain3 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcclph0     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclph0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcclph2     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclph2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcclph3     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclph3 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcclpl0     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclpl0 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcclpl2     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclpl2 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.drcclpl3     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclpl3 );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mcarmd        = %x\n", (guint)&ShdrTest_IO_SHDR.mcarmd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mcmpmd        = %x\n", (guint)&ShdrTest_IO_SHDR.mcmpmd );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mmvval        = %x\n", (guint)&ShdrTest_IO_SHDR.mmvval );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mmvrcnt       = %x\n", (guint)&ShdrTest_IO_SHDR.mmvrcnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mdbcnt        = %x\n", (guint)&ShdrTest_IO_SHDR.mdbcnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mdbrocnt      = %x\n", (guint)&ShdrTest_IO_SHDR.mdbrocnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.molrcnt       = %x\n", (guint)&ShdrTest_IO_SHDR.molrcnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mcpcnt        = %x\n", (guint)&ShdrTest_IO_SHDR.mcpcnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mmcrcnt       = %x\n", (guint)&ShdrTest_IO_SHDR.mmcrcnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.molecnt       = %x\n", (guint)&ShdrTest_IO_SHDR.molecnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mmvecnt       = %x\n", (guint)&ShdrTest_IO_SHDR.mmvecnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mcpxecnt      = %x\n", (guint)&ShdrTest_IO_SHDR.mcpxecnt );
	IntErnals_RS_printf("ShdrTest_IO_SHDR.mvlcnt        = %x\n", (guint)&ShdrTest_IO_SHDR.mvlcnt );

	IntErnals_RS_printf(" \n");

	IntErnals_RS_printf("ioShdrTbl.dgtr      = %x\n", (guint)&ioShdrTbl.dgtr );
	IntErnals_RS_printf("ioShdrTbl.dgtg      = %x\n", (guint)&ioShdrTbl.dgtg );
	IntErnals_RS_printf("ioShdrTbl.dgtb      = %x\n", (guint)&ioShdrTbl.dgtb );

	IntErnals_RS_printf(" \n");
#endif
}

ShdrTest *shdr_test_new()
{
	ShdrTest *self = g_object_new(SHDR_TYPE_TEST, NULL);

	return self;
}
