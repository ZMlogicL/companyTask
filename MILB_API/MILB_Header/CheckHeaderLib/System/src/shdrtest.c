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

	CheckHeaderMain_RS_PRINTF("SHDR\n");
#if 0
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.shdractl0     = %x\n", (guint)&ShdrTest_IO_SHDR.shdractl0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.shdractl1     = %x\n", (guint)&ShdrTest_IO_SHDR.shdractl1 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.shdractl2     = %x\n", (guint)&ShdrTest_IO_SHDR.shdractl2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.shdrint0      = %x\n", (guint)&ShdrTest_IO_SHDR.shdrint0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.shdrint1      = %x\n", (guint)&ShdrTest_IO_SHDR.shdrint1 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axmd          = %x\n", (guint)&ShdrTest_IO_SHDR.axmd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlara     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlara );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlarb     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlarb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlarc     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlarc );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlard     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlard );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlawa     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlawa );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlawb     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlawb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlawc     = %x\n", (guint)&ShdrTest_IO_SHDR.axictlawc );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlra      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlra  );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlrb      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlrb  );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlrc      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlrc  );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlrd      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlrd  );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlwa      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlwa  );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlwb      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlwb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axictlwc      = %x\n", (guint)&ShdrTest_IO_SHDR.axictlwc );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.coremon0      = %x\n", (guint)&ShdrTest_IO_SHDR.coremon0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.coremon1      = %x\n", (guint)&ShdrTest_IO_SHDR.coremon1 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.dgtRsel      = %x\n", (guint)&ShdrTest_IO_SHDR.dgtRsel );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrAddrA   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrA );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrAddrB   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrB );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrAddrC   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrC );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrAddrD   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrD );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrAddrE   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrE );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrAddrF   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrAddrF );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrGhsizeA = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeA );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrGhsizeB = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeB );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrGhsizeC = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeC );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrGhsizeD = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeD );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrGhsizeE = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeE );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrGhsizeF = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrGhsizeF );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrVfm      = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVfm );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwAddrB   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrB );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwAddrE   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrE );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwAddrF   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrF );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwAddrG   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrG );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwAddrH   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrH );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwAddrI   = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwAddrI );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwGhsizeB = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeB );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwGhsizeE = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeE );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwGhsizeF = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeF );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwGhsizeG = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeG );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwGhsizeH = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeH );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwGhsizeI = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwGhsizeI );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwVfm      = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwVfm );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwBaA     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwBaA );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwBaC     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwBaC );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwBaD     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwBaD );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwFwA     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwFwA );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwFwC     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwFwC );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrwFwD     = %x\n", (guint)&ShdrTest_IO_SHDR.sdrwFwD );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.shdrifrm      = %x\n", (guint)&ShdrTest_IO_SHDR.shdrifrm );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.shdrofrm      = %x\n", (guint)&ShdrTest_IO_SHDR.shdrofrm );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrHsizeA  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeA );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrHsizeB  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeB );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrHsizeC  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeC );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrHsizeD  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeD );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrHsizeE  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrHsizeE );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrVsizeA  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeA );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrVsizeB  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeB );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrVsizeC  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeC );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrVsizeD  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeD );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sdrrVsizeE  = %x\n", (guint)&ShdrTest_IO_SHDR.sdrrVsizeE );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.exmag         = %x\n", (guint)&ShdrTest_IO_SHDR.exmag );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.remval        = %x\n", (guint)&ShdrTest_IO_SHDR.remval );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.shift         = %x\n", (guint)&ShdrTest_IO_SHDR.shift );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mrgn          = %x\n", (guint)&ShdrTest_IO_SHDR.mrgn );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.flwcnt        = %x\n", (guint)&ShdrTest_IO_SHDR.flwcnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.tmode         = %x\n", (guint)&ShdrTest_IO_SHDR.tmode );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.modesel       = %x\n", (guint)&ShdrTest_IO_SHDR.modesel );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mcModesel    = %x\n", (guint)&ShdrTest_IO_SHDR.mcModesel );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.compIncfmsel = %x\n", (guint)&ShdrTest_IO_SHDR.compIncfmsel );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.bypasson      = %x\n", (guint)&ShdrTest_IO_SHDR.bypasson );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.axisize       = %x\n", (guint)&ShdrTest_IO_SHDR.axisize );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.lint          = %x\n", (guint)&ShdrTest_IO_SHDR.lint );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wrstartaddr   = %x\n", (guint)&ShdrTest_IO_SHDR.wrstartaddr );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rdstartaddr   = %x\n", (guint)&ShdrTest_IO_SHDR.rdstartaddr );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.premd         = %x\n", (guint)&ShdrTest_IO_SHDR.premd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.y2rcoef       = %x\n", (guint)&ShdrTest_IO_SHDR.y2rcoef );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.prey2rclpul0  = %x\n", (guint)&ShdrTest_IO_SHDR.prey2rclpul0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.prey2rclpll0  = %x\n", (guint)&ShdrTest_IO_SHDR.prey2rclpll0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.prey2rclpus   = %x\n", (guint)&ShdrTest_IO_SHDR.prey2rclpus  );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.prey2rclpls   = %x\n", (guint)&ShdrTest_IO_SHDR.prey2rclpls  );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.r2ycoef       = %x\n", (guint)&ShdrTest_IO_SHDR.r2ycoef );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.prer2yclpul   = %x\n", (guint)&ShdrTest_IO_SHDR.prer2yclpul );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.prer2yclpll   = %x\n", (guint)&ShdrTest_IO_SHDR.prer2yclpll );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.prer2yclpus   = %x\n", (guint)&ShdrTest_IO_SHDR.prer2yclpus );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.prer2yclpls   = %x\n", (guint)&ShdrTest_IO_SHDR.prer2yclpls );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sknofs        = %x\n", (guint)&ShdrTest_IO_SHDR.sknofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sknsl         = %x\n", (guint)&ShdrTest_IO_SHDR.sknsl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sknb1         = %x\n", (guint)&ShdrTest_IO_SHDR.sknb1 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.sknb2         = %x\n", (guint)&ShdrTest_IO_SHDR.sknb2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.lknofs        = %x\n", (guint)&ShdrTest_IO_SHDR.lknofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.lknsl         = %x\n", (guint)&ShdrTest_IO_SHDR.lknsl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.lknb1         = %x\n", (guint)&ShdrTest_IO_SHDR.lknb1 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.lknb2         = %x\n", (guint)&ShdrTest_IO_SHDR.lknb2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.epbd          = %x\n", (guint)&ShdrTest_IO_SHDR.epbd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.epof          = %x\n", (guint)&ShdrTest_IO_SHDR.epof );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.epbld         = %x\n", (guint)&ShdrTest_IO_SHDR.epbld );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.fdweight      = %x\n", (guint)&ShdrTest_IO_SHDR.fdweight );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mvcnt         = %x\n", (guint)&ShdrTest_IO_SHDR.mvcnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.bldrofs       = %x\n", (guint)&ShdrTest_IO_SHDR.bldrofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.bldrsl        = %x\n", (guint)&ShdrTest_IO_SHDR.bldrsl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.bldrb         = %x\n", (guint)&ShdrTest_IO_SHDR.bldrb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtr2ycoef   = %x\n", (guint)&ShdrTest_IO_SHDR.wghtr2ycoef );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtr2yclp    = %x\n", (guint)&ShdrTest_IO_SHDR.wghtr2yclp );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtbase      = %x\n", (guint)&ShdrTest_IO_SHDR.wghtbase );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtrofs      = %x\n", (guint)&ShdrTest_IO_SHDR.wghtrofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtgofs      = %x\n", (guint)&ShdrTest_IO_SHDR.wghtgofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtbofs      = %x\n", (guint)&ShdrTest_IO_SHDR.wghtbofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtrsl       = %x\n", (guint)&ShdrTest_IO_SHDR.wghtrsl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtgsl       = %x\n", (guint)&ShdrTest_IO_SHDR.wghtgsl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtbsl       = %x\n", (guint)&ShdrTest_IO_SHDR.wghtbsl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtrb        = %x\n", (guint)&ShdrTest_IO_SHDR.wghtrb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtgb        = %x\n", (guint)&ShdrTest_IO_SHDR.wghtgb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.wghtbb        = %x\n", (guint)&ShdrTest_IO_SHDR.wghtbb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.isoth         = %x\n", (guint)&ShdrTest_IO_SHDR.isoth );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.isocoef       = %x\n", (guint)&ShdrTest_IO_SHDR.isocoef );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.exp77md       = %x\n", (guint)&ShdrTest_IO_SHDR.exp77md );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.fmdsel        = %x\n", (guint)&ShdrTest_IO_SHDR.fmdsel );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.tlut          = %x\n", (guint)&ShdrTest_IO_SHDR.tlut );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.pmskmd        = %x\n", (guint)&ShdrTest_IO_SHDR.pmskmd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.spnren        = %x\n", (guint)&ShdrTest_IO_SHDR.spnren );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.spebd         = %x\n", (guint)&ShdrTest_IO_SHDR.spebd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.speof         = %x\n", (guint)&ShdrTest_IO_SHDR.speof );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.spebld        = %x\n", (guint)&ShdrTest_IO_SHDR.spebld );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.msky2rclpul   = %x\n", (guint)&ShdrTest_IO_SHDR.msky2rclpul );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.msky2rclpll   = %x\n", (guint)&ShdrTest_IO_SHDR.msky2rclpll );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.msky2rclpus   = %x\n", (guint)&ShdrTest_IO_SHDR.msky2rclpus );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.msky2rclpls   = %x\n", (guint)&ShdrTest_IO_SHDR.msky2rclpls );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.alpha         = %x\n", (guint)&ShdrTest_IO_SHDR.alpha );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.lpfc          = %x\n", (guint)&ShdrTest_IO_SHDR.lpfc );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.bldofs        = %x\n", (guint)&ShdrTest_IO_SHDR.bldofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.bldsl         = %x\n", (guint)&ShdrTest_IO_SHDR.bldsl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.bldb          = %x\n", (guint)&ShdrTest_IO_SHDR.bldb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.normgain      = %x\n", (guint)&ShdrTest_IO_SHDR.normgain );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.normofs       = %x\n", (guint)&ShdrTest_IO_SHDR.normofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mskmd         = %x\n", (guint)&ShdrTest_IO_SHDR.mskmd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.bldsel        = %x\n", (guint)&ShdrTest_IO_SHDR.bldsel );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.alphasel      = %x\n", (guint)&ShdrTest_IO_SHDR.alphasel );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.alphaval      = %x\n", (guint)&ShdrTest_IO_SHDR.alphaval );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.postsft1rnd   = %x\n", (guint)&ShdrTest_IO_SHDR.postsft1rnd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.posty2rcoef   = %x\n", (guint)&ShdrTest_IO_SHDR.posty2rcoef );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.posty2rclpthu = %x\n", (guint)&ShdrTest_IO_SHDR.posty2rclpthu );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.posty2rclpthl = %x\n", (guint)&ShdrTest_IO_SHDR.posty2rclpthl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.postsel1      = %x\n", (guint)&ShdrTest_IO_SHDR.postsel1 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.postmulqpos   = %x\n", (guint)&ShdrTest_IO_SHDR.postmulqpos );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.evknb         = %x\n", (guint)&ShdrTest_IO_SHDR.evknb );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.evknofs       = %x\n", (guint)&ShdrTest_IO_SHDR.evknofs );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.evknsl        = %x\n", (guint)&ShdrTest_IO_SHDR.evknsl );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.postsel0      = %x\n", (guint)&ShdrTest_IO_SHDR.postsel0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.hdrcssmd      = %x\n", (guint)&ShdrTest_IO_SHDR.hdrcssmd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.ch0mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch0mode );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.ch1mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch1mode );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.ch2mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch2mode );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.ch3mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch3mode );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.ch4mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch4mode );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.ch5mode       = %x\n", (guint)&ShdrTest_IO_SHDR.ch5mode );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.woutsz        = %x\n", (guint)&ShdrTest_IO_SHDR.woutsz );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rszhcnt2     = %x\n", (guint)&ShdrTest_IO_SHDR.rszhcnt2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rszhcnt3     = %x\n", (guint)&ShdrTest_IO_SHDR.rszhcnt3 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rszhcnt4     = %x\n", (guint)&ShdrTest_IO_SHDR.rszhcnt4 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rszhcnt5     = %x\n", (guint)&ShdrTest_IO_SHDR.rszhcnt5 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rszvcnt2     = %x\n", (guint)&ShdrTest_IO_SHDR.rszvcnt2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rszvcnt3     = %x\n", (guint)&ShdrTest_IO_SHDR.rszvcnt3 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rszvcnt4     = %x\n", (guint)&ShdrTest_IO_SHDR.rszvcnt4 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.rszvcnt5     = %x\n", (guint)&ShdrTest_IO_SHDR.rszvcnt5 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.trmsta2      = %x\n", (guint)&ShdrTest_IO_SHDR.trmsta2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.trmsta3      = %x\n", (guint)&ShdrTest_IO_SHDR.trmsta3 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.trmsta4      = %x\n", (guint)&ShdrTest_IO_SHDR.trmsta4 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.trmsta5      = %x\n", (guint)&ShdrTest_IO_SHDR.trmsta5 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcofst0     = %x\n", (guint)&ShdrTest_IO_SHDR.drcofst0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcofst2     = %x\n", (guint)&ShdrTest_IO_SHDR.drcofst2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcofst3     = %x\n", (guint)&ShdrTest_IO_SHDR.drcofst3 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcgain0     = %x\n", (guint)&ShdrTest_IO_SHDR.drcgain0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcgain2     = %x\n", (guint)&ShdrTest_IO_SHDR.drcgain2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcgain3     = %x\n", (guint)&ShdrTest_IO_SHDR.drcgain3 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcclph0     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclph0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcclph2     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclph2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcclph3     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclph3 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcclpl0     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclpl0 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcclpl2     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclpl2 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.drcclpl3     = %x\n", (guint)&ShdrTest_IO_SHDR.drcclpl3 );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mcarmd        = %x\n", (guint)&ShdrTest_IO_SHDR.mcarmd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mcmpmd        = %x\n", (guint)&ShdrTest_IO_SHDR.mcmpmd );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mmvval        = %x\n", (guint)&ShdrTest_IO_SHDR.mmvval );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mmvrcnt       = %x\n", (guint)&ShdrTest_IO_SHDR.mmvrcnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mdbcnt        = %x\n", (guint)&ShdrTest_IO_SHDR.mdbcnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mdbrocnt      = %x\n", (guint)&ShdrTest_IO_SHDR.mdbrocnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.molrcnt       = %x\n", (guint)&ShdrTest_IO_SHDR.molrcnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mcpcnt        = %x\n", (guint)&ShdrTest_IO_SHDR.mcpcnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mmcrcnt       = %x\n", (guint)&ShdrTest_IO_SHDR.mmcrcnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.molecnt       = %x\n", (guint)&ShdrTest_IO_SHDR.molecnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mmvecnt       = %x\n", (guint)&ShdrTest_IO_SHDR.mmvecnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mcpxecnt      = %x\n", (guint)&ShdrTest_IO_SHDR.mcpxecnt );
	CheckHeaderMain_RS_PRINTF("ShdrTest_IO_SHDR.mvlcnt        = %x\n", (guint)&ShdrTest_IO_SHDR.mvlcnt );

	CheckHeaderMain_RS_PRINTF(" \n");

	CheckHeaderMain_RS_PRINTF("ioShdrTbl.dgtr      = %x\n", (guint)&ioShdrTbl.dgtr );
	CheckHeaderMain_RS_PRINTF("ioShdrTbl.dgtg      = %x\n", (guint)&ioShdrTbl.dgtg );
	CheckHeaderMain_RS_PRINTF("ioShdrTbl.dgtb      = %x\n", (guint)&ioShdrTbl.dgtb );

	CheckHeaderMain_RS_PRINTF(" \n");
#endif
}

ShdrTest *shdr_test_new()
{
	ShdrTest *self = g_object_new(SHDR_TYPE_TEST, NULL);

	return self;
}
