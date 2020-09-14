/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :郑蛘钊
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/


#include "defs.h"
#include "mxictest.h"


G_DEFINE_TYPE(Mxic, mxic_test, G_TYPE_OBJECT);

#define MXIC_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),MXIC_TYPE_TEST, MxicPrivate));


struct _MxicPrivate
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
static void mxic_test_class_init(MxicClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(MxicPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void mxic_test_init(Mxic *self)
{
	MxicPrivate *priv = MXIC_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(mxic_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	Mxic *self = MXIC_TEST(object);
	MxicPrivate *priv = MXIC_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(mxic_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void mxic_test(Mxic* self)
{
	RS_printf("MXIC\n");
#if 0
	RS_printf("ioMxic0.tmirst         = %x\n", (kuint)&ioMxic0.tmirst );
	RS_printf("ioMxic0.tcken          = %x\n", (kuint)&ioMxic0.tcken );
	RS_printf("ioMxic0.tckenp         = %x\n", (kuint)&ioMxic0.tckenp );
	RS_printf("ioMxic0.tmie           = %x\n", (kuint)&ioMxic0.tmie );
	RS_printf("ioMxic0.tmif           = %x\n", (kuint)&ioMxic0.tmif );
	RS_printf("ioMxic0.tdestw         = %x\n", (kuint)&ioMxic0.tdestw );
	RS_printf("ioMxic0.tdestr         = %x\n", (kuint)&ioMxic0.tdestr );
	RS_printf("ioMxic0.tcftrg         = %x\n", (kuint)&ioMxic0.tcftrg );
	RS_printf("ioMxic0.tcfmd          = %x\n", (kuint)&ioMxic0.tcfmd );
	RS_printf("ioMxic0.tdeclr         = %x\n", (kuint)&ioMxic0.tdeclr );
	RS_printf("ioMxic0.trvsw          = %x\n", (kuint)&ioMxic0.trvsw );

	RS_printf("ioMxic0.taen           = %x\n", (kuint)&ioMxic0.taen );
	RS_printf("ioMxic0.tacptcw        = %x\n", (kuint)&ioMxic0.tacptcw );
	RS_printf("ioMxic0.tacptcr        = %x\n", (kuint)&ioMxic0.tacptcr );

	RS_printf("ioMxic0.tsmtrg         = %x\n", (kuint)&ioMxic0.tsmtrg );

	RS_printf("ioMxic0.tregion[0]     = %x\n", (kuint)&ioMxic0.tregion[0] );
	RS_printf("ioMxic0.tregion[1]     = %x\n", (kuint)&ioMxic0.tregion[1] );
	RS_printf("ioMxic0.tregion[2]     = %x\n", (kuint)&ioMxic0.tregion[2] );
	RS_printf("ioMxic0.tregion[3]     = %x\n", (kuint)&ioMxic0.tregion[3] );

	RS_printf("ioMxic0.tsasetw[0]     = %x\n", (kuint)&ioMxic0.tsasetw[0] );
	RS_printf("ioMxic0.tsasetw[1]     = %x\n", (kuint)&ioMxic0.tsasetw[1] );
	RS_printf("ioMxic0.tsasetw[2]     = %x\n", (kuint)&ioMxic0.tsasetw[2] );
	RS_printf("ioMxic0.tsasetw[3]     = %x\n", (kuint)&ioMxic0.tsasetw[3] );

	RS_printf("ioMxic0.tmtrg          = %x\n", (kuint)&ioMxic0.tmtrg );
	RS_printf("ioMxic0.tmmd           = %x\n", (kuint)&ioMxic0.tmmd );
	RS_printf("ioMxic0.tmontrg        = %x\n", (kuint)&ioMxic0.tmontrg );
	RS_printf("ioMxic0.tmuptrg        = %x\n", (kuint)&ioMxic0.tmuptrg );
	RS_printf("ioMxic0.tmlimsel       = %x\n", (kuint)&ioMxic0.tmlimsel );
	RS_printf("ioMxic0.tmlimit        = %x\n", (kuint)&ioMxic0.tmlimit );
	RS_printf("ioMxic0.tmsel          = %x\n", (kuint)&ioMxic0.tmsel );
	RS_printf("ioMxic0.tmcnt[0]       = %x\n", (kuint)&ioMxic0.tmcnt[0] );
	RS_printf("ioMxic0.tmcnt[1]       = %x\n", (kuint)&ioMxic0.tmcnt[1] );
	RS_printf("ioMxic0.tmcnt[2]       = %x\n", (kuint)&ioMxic0.tmcnt[2] );
	RS_printf("ioMxic0.tmcnt[3]       = %x\n", (kuint)&ioMxic0.tmcnt[3] );

	RS_printf("ioMxic0.thstw[0][0]    = %x\n", (kuint)&ioMxic0.thstw[0][0] );
	RS_printf("ioMxic0.thstw[1][0]    = %x\n", (kuint)&ioMxic0.thstw[1][0] );
	RS_printf("ioMxic0.thstw[2][0]    = %x\n", (kuint)&ioMxic0.thstw[2][0] );
	RS_printf("ioMxic0.thstw[3][0]    = %x\n", (kuint)&ioMxic0.thstw[3][0] );

	RS_printf("ioMxic0.thstr[0][0]    = %x\n", (kuint)&ioMxic0.thstr[0][0] );
	RS_printf("ioMxic0.thstr[1][0]    = %x\n", (kuint)&ioMxic0.thstr[1][0] );
	RS_printf("ioMxic0.thstr[2][0]    = %x\n", (kuint)&ioMxic0.thstr[2][0] );
	RS_printf("ioMxic0.thstr[3][0]    = %x\n", (kuint)&ioMxic0.thstr[3][0] );

	RS_printf("ioMxic0.tmarlpW1[0]  = %x\n", (kuint)&ioMxic0.tmarlpW1[0] );
	RS_printf("ioMxic0.tmarlpW2[0]  = %x\n", (kuint)&ioMxic0.tmarlpW2[0] );
	RS_printf("ioMxic0.tmarlpW3[0]  = %x\n", (kuint)&ioMxic0.tmarlpW3[0] );
	RS_printf("ioMxic0.tmarlpW4[0]  = %x\n", (kuint)&ioMxic0.tmarlpW4[0] );

	RS_printf("ioMxic0.tmarlpR1[0]  = %x\n", (kuint)&ioMxic0.tmarlpR1[0] );
	RS_printf("ioMxic0.tmarlpR2[0]  = %x\n", (kuint)&ioMxic0.tmarlpR2[0] );
	RS_printf("ioMxic0.tmarlpR3[0]  = %x\n", (kuint)&ioMxic0.tmarlpR3[0] );
	RS_printf("ioMxic0.tmarlpR4[0]  = %x\n", (kuint)&ioMxic0.tmarlpR4[0] );

	RS_printf("ioMxic0.trmcw[0]       = %x\n", (kuint)&ioMxic0.trmcw[0] );
	RS_printf("ioMxic0.trmcr[0]       = %x\n", (kuint)&ioMxic0.trmcr[0] );

	RS_printf("ioMxic0.tlvlw1[0]      = %x\n", (kuint)&ioMxic0.tlvlw1[0] );
	RS_printf("ioMxic0.tlvlw1[1]      = %x\n", (kuint)&ioMxic0.tlvlw1[1] );
	RS_printf("ioMxic0.tlvlw1[2]      = %x\n", (kuint)&ioMxic0.tlvlw1[2] );
	RS_printf("ioMxic0.tlvlw1[3]      = %x\n", (kuint)&ioMxic0.tlvlw1[3] );

	RS_printf("ioMxic0.tlvlw2[0]      = %x\n", (kuint)&ioMxic0.tlvlw2[0] );
	RS_printf("ioMxic0.tlvlw2[1]      = %x\n", (kuint)&ioMxic0.tlvlw2[1] );
	RS_printf("ioMxic0.tlvlw2[2]      = %x\n", (kuint)&ioMxic0.tlvlw2[2] );
	RS_printf("ioMxic0.tlvlw2[3]      = %x\n", (kuint)&ioMxic0.tlvlw2[3] );

	RS_printf("ioMxic0.tlvlw3[0]      = %x\n", (kuint)&ioMxic0.tlvlw3[0] );
	RS_printf("ioMxic0.tlvlw3[1]      = %x\n", (kuint)&ioMxic0.tlvlw3[1] );
	RS_printf("ioMxic0.tlvlw3[2]      = %x\n", (kuint)&ioMxic0.tlvlw3[2] );
	RS_printf("ioMxic0.tlvlw3[3]      = %x\n", (kuint)&ioMxic0.tlvlw3[3] );

	RS_printf("ioMxic0.tlvlw4[0]      = %x\n", (kuint)&ioMxic0.tlvlw4[0] );
	RS_printf("ioMxic0.tlvlw4[1]      = %x\n", (kuint)&ioMxic0.tlvlw4[1] );
	RS_printf("ioMxic0.tlvlw4[2]      = %x\n", (kuint)&ioMxic0.tlvlw4[2] );
	RS_printf("ioMxic0.tlvlw4[3]      = %x\n", (kuint)&ioMxic0.tlvlw4[3] );

	RS_printf("ioMxic0.tlvlr1[0]      = %x\n", (kuint)&ioMxic0.tlvlr1[0] );
	RS_printf("ioMxic0.tlvlr1[1]      = %x\n", (kuint)&ioMxic0.tlvlr1[1] );
	RS_printf("ioMxic0.tlvlr1[2]      = %x\n", (kuint)&ioMxic0.tlvlr1[2] );
	RS_printf("ioMxic0.tlvlr1[3]      = %x\n", (kuint)&ioMxic0.tlvlr1[3] );

	RS_printf("ioMxic0.tlvlr2[0]      = %x\n", (kuint)&ioMxic0.tlvlr2[0] );
	RS_printf("ioMxic0.tlvlr2[1]      = %x\n", (kuint)&ioMxic0.tlvlr2[1] );
	RS_printf("ioMxic0.tlvlr2[2]      = %x\n", (kuint)&ioMxic0.tlvlr2[2] );
	RS_printf("ioMxic0.tlvlr2[3]      = %x\n", (kuint)&ioMxic0.tlvlr2[3] );

	RS_printf("ioMxic0.tlvlr3[0]      = %x\n", (kuint)&ioMxic0.tlvlr3[0] );
	RS_printf("ioMxic0.tlvlr3[1]      = %x\n", (kuint)&ioMxic0.tlvlr3[1] );
	RS_printf("ioMxic0.tlvlr3[2]      = %x\n", (kuint)&ioMxic0.tlvlr3[2] );
	RS_printf("ioMxic0.tlvlr3[3]      = %x\n", (kuint)&ioMxic0.tlvlr3[3] );

	RS_printf("ioMxic0.tlvlr4[0]      = %x\n", (kuint)&ioMxic0.tlvlr4[0] );
	RS_printf("ioMxic0.tlvlr4[1]      = %x\n", (kuint)&ioMxic0.tlvlr4[1] );
	RS_printf("ioMxic0.tlvlr4[2]      = %x\n", (kuint)&ioMxic0.tlvlr4[2] );
	RS_printf("ioMxic0.tlvlr4[3]      = %x\n", (kuint)&ioMxic0.tlvlr4[3] );

	RS_printf("ioMxic0.tmstw[0]       = %x\n", (kuint)&ioMxic0.tmstw[0] );
	RS_printf("ioMxic0.tmstr[0]       = %x\n", (kuint)&ioMxic0.tmstr[0] );

	RS_printf("ioMxic0.tslsw1[0][0]  = %x\n", (kuint)&ioMxic0.tslsw1[0][0] );
	RS_printf("ioMxic0.tslsw1[1][0]  = %x\n", (kuint)&ioMxic0.tslsw1[1][0] );
	RS_printf("ioMxic0.tslsw1[2][0]  = %x\n", (kuint)&ioMxic0.tslsw1[2][0] );
	RS_printf("ioMxic0.tslsw1[3][0]  = %x\n", (kuint)&ioMxic0.tslsw1[3][0] );
	RS_printf("ioMxic0.tslsw2[0][0]  = %x\n", (kuint)&ioMxic0.tslsw2[0][0] );
	RS_printf("ioMxic0.tslsw2[1][0]  = %x\n", (kuint)&ioMxic0.tslsw2[1][0] );
	RS_printf("ioMxic0.tslsw2[2][0]  = %x\n", (kuint)&ioMxic0.tslsw2[2][0] );
	RS_printf("ioMxic0.tslsw2[3][0]  = %x\n", (kuint)&ioMxic0.tslsw2[3][0] );
	RS_printf("ioMxic0.tslsw3[0][0]  = %x\n", (kuint)&ioMxic0.tslsw3[0][0] );
	RS_printf("ioMxic0.tslsw3[1][0]  = %x\n", (kuint)&ioMxic0.tslsw3[1][0] );
	RS_printf("ioMxic0.tslsw3[2][0]  = %x\n", (kuint)&ioMxic0.tslsw3[2][0] );
	RS_printf("ioMxic0.tslsw3[3][0]  = %x\n", (kuint)&ioMxic0.tslsw3[3][0] );
	RS_printf("ioMxic0.tslsw4[0][0]  = %x\n", (kuint)&ioMxic0.tslsw4[0][0] );
	RS_printf("ioMxic0.tslsw4[1][0]  = %x\n", (kuint)&ioMxic0.tslsw4[1][0] );
	RS_printf("ioMxic0.tslsw4[2][0]  = %x\n", (kuint)&ioMxic0.tslsw4[2][0] );
	RS_printf("ioMxic0.tslsw4[3][0]  = %x\n", (kuint)&ioMxic0.tslsw4[3][0] );

	RS_printf("ioMxic0.tslsr1[0][0]  = %x\n", (kuint)&ioMxic0.tslsr1[0][0] );
	RS_printf("ioMxic0.tslsr1[1][0]  = %x\n", (kuint)&ioMxic0.tslsr1[1][0] );
	RS_printf("ioMxic0.tslsr1[2][0]  = %x\n", (kuint)&ioMxic0.tslsr1[2][0] );
	RS_printf("ioMxic0.tslsr1[3][0]  = %x\n", (kuint)&ioMxic0.tslsr1[3][0] );
	RS_printf("ioMxic0.tslsr2[0][0]  = %x\n", (kuint)&ioMxic0.tslsr2[0][0] );
	RS_printf("ioMxic0.tslsr2[1][0]  = %x\n", (kuint)&ioMxic0.tslsr2[1][0] );
	RS_printf("ioMxic0.tslsr2[2][0]  = %x\n", (kuint)&ioMxic0.tslsr2[2][0] );
	RS_printf("ioMxic0.tslsr2[3][0]  = %x\n", (kuint)&ioMxic0.tslsr2[3][0] );
	RS_printf("ioMxic0.tslsr3[0][0]  = %x\n", (kuint)&ioMxic0.tslsr3[0][0] );
	RS_printf("ioMxic0.tslsr3[1][0]  = %x\n", (kuint)&ioMxic0.tslsr3[1][0] );
	RS_printf("ioMxic0.tslsr3[2][0]  = %x\n", (kuint)&ioMxic0.tslsr3[2][0] );
	RS_printf("ioMxic0.tslsr3[3][0]  = %x\n", (kuint)&ioMxic0.tslsr3[3][0] );
	RS_printf("ioMxic0.tslsr4[0][0]  = %x\n", (kuint)&ioMxic0.tslsr4[0][0] );
	RS_printf("ioMxic0.tslsr4[1][0]  = %x\n", (kuint)&ioMxic0.tslsr4[1][0] );
	RS_printf("ioMxic0.tslsr4[2][0]  = %x\n", (kuint)&ioMxic0.tslsr4[2][0] );
	RS_printf("ioMxic0.tslsr4[3][0]  = %x\n", (kuint)&ioMxic0.tslsr4[3][0] );

	RS_printf("ioMxic0.tgcken         = %x\n", (kuint)&ioMxic0.tgcken );
	RS_printf("ioMxic0.tgcfmd         = %x\n", (kuint)&ioMxic0.tgcfmd );

	RS_printf("ioMxic0.tgacptcw       = %x\n", (kuint)&ioMxic0.tgacptcw );
	RS_printf("ioMxic0.tgacptcr       = %x\n", (kuint)&ioMxic0.tgacptcr );
	RS_printf("ioMxic0.tportmw        = %x\n", (kuint)&ioMxic0.tportmw );
	RS_printf("ioMxic0.tportmr        = %x\n", (kuint)&ioMxic0.tportmr );

	RS_printf("ioMxic0.trmcwGr[0]    = %x\n", (kuint)&ioMxic0.trmcwGr[0] );
	RS_printf("ioMxic0.trmcrGr[0]    = %x\n", (kuint)&ioMxic0.trmcrGr[0] );
	RS_printf("ioMxic0.tmstwGr[0]    = %x\n", (kuint)&ioMxic0.tmstwGr[0] );
	RS_printf("ioMxic0.tmstrGr[0]    = %x\n", (kuint)&ioMxic0.tmstrGr[0] );

	RS_printf("ioMxic0.tgslsw[0]      = %x\n", (kuint)&ioMxic0.tgslsw[0] );
	RS_printf("ioMxic0.tgslsw[1]      = %x\n", (kuint)&ioMxic0.tgslsw[1] );
	RS_printf("ioMxic0.tgslsw[2]      = %x\n", (kuint)&ioMxic0.tgslsw[2] );
	RS_printf("ioMxic0.tgslsw[3]      = %x\n", (kuint)&ioMxic0.tgslsw[3] );
	RS_printf("ioMxic0.tgslsw[4]      = %x\n", (kuint)&ioMxic0.tgslsw[4] );
	RS_printf("ioMxic0.tgslsw[5]      = %x\n", (kuint)&ioMxic0.tgslsw[5] );
	RS_printf("ioMxic0.tgslsw[6]      = %x\n", (kuint)&ioMxic0.tgslsw[6] );
	RS_printf("ioMxic0.tgslsw[7]      = %x\n", (kuint)&ioMxic0.tgslsw[7] );
	RS_printf("ioMxic0.tgslsr[0]      = %x\n", (kuint)&ioMxic0.tgslsr[0] );
	RS_printf("ioMxic0.tgslsr[1]      = %x\n", (kuint)&ioMxic0.tgslsr[1] );
	RS_printf("ioMxic0.tgslsr[2]      = %x\n", (kuint)&ioMxic0.tgslsr[2] );
	RS_printf("ioMxic0.tgslsr[3]      = %x\n", (kuint)&ioMxic0.tgslsr[3] );
	RS_printf("ioMxic0.tgslsr[4]      = %x\n", (kuint)&ioMxic0.tgslsr[4] );
	RS_printf("ioMxic0.tgslsr[5]      = %x\n", (kuint)&ioMxic0.tgslsr[5] );
	RS_printf("ioMxic0.tgslsr[6]      = %x\n", (kuint)&ioMxic0.tgslsr[6] );
	RS_printf("ioMxic0.tgslsr[7]      = %x\n", (kuint)&ioMxic0.tgslsr[7] );

	RS_printf("IO_MXIC1.tmirst         = %x\n", (kuint)&IO_MXIC1.tmirst );
	RS_printf("IO_MXIC2.tmirst         = %x\n", (kuint)&IO_MXIC2.tmirst );
	RS_printf("IO_MXIC3.tmirst         = %x\n", (kuint)&IO_MXIC3.tmirst );
	RS_printf("IO_MXIC4.tmirst         = %x\n", (kuint)&IO_MXIC4.tmirst );
	RS_printf("IO_MXIC5.tmirst         = %x\n", (kuint)&IO_MXIC5.tmirst );
	RS_printf("IO_MXIC6.tmirst         = %x\n", (kuint)&IO_MXIC6.tmirst );

	RS_printf(" \n");

/* io_jdsmxic */
	RS_printf("ioMxic1Tbl.tslw1[0]  = %x\n", (kuint)&ioMxic1Tbl.tslw1[0] );
	RS_printf("ioMxic1Tbl.tslw1[1]  = %x\n", (kuint)&ioMxic1Tbl.tslw1[1] );
	RS_printf("ioMxic1Tbl.tslw1[2]  = %x\n", (kuint)&ioMxic1Tbl.tslw1[2] );
	RS_printf("ioMxic1Tbl.tslw1[3]  = %x\n", (kuint)&ioMxic1Tbl.tslw1[3] );
	RS_printf("ioMxic1Tbl.tslw2[0]  = %x\n", (kuint)&ioMxic1Tbl.tslw2[0] );
	RS_printf("ioMxic1Tbl.tslw2[1]  = %x\n", (kuint)&ioMxic1Tbl.tslw2[1] );
	RS_printf("ioMxic1Tbl.tslw2[2]  = %x\n", (kuint)&ioMxic1Tbl.tslw2[2] );
	RS_printf("ioMxic1Tbl.tslw2[3]  = %x\n", (kuint)&ioMxic1Tbl.tslw2[3] );
	RS_printf("ioMxic1Tbl.tslw3[0]  = %x\n", (kuint)&ioMxic1Tbl.tslw3[0] );
	RS_printf("ioMxic1Tbl.tslw3[1]  = %x\n", (kuint)&ioMxic1Tbl.tslw3[1] );
	RS_printf("ioMxic1Tbl.tslw3[2]  = %x\n", (kuint)&ioMxic1Tbl.tslw3[2] );
	RS_printf("ioMxic1Tbl.tslw3[3]  = %x\n", (kuint)&ioMxic1Tbl.tslw3[3] );
	RS_printf("ioMxic1Tbl.tslw4[0]  = %x\n", (kuint)&ioMxic1Tbl.tslw4[0] );
	RS_printf("ioMxic1Tbl.tslw4[1]  = %x\n", (kuint)&ioMxic1Tbl.tslw4[1] );
	RS_printf("ioMxic1Tbl.tslw4[2]  = %x\n", (kuint)&ioMxic1Tbl.tslw4[2] );
	RS_printf("ioMxic1Tbl.tslw4[3]  = %x\n", (kuint)&ioMxic1Tbl.tslw4[3] );

	RS_printf("ioMxic1Tbl.tslr1[0]  = %x\n", (kuint)&ioMxic1Tbl.tslr1[0] );
	RS_printf("ioMxic1Tbl.tslr1[1]  = %x\n", (kuint)&ioMxic1Tbl.tslr1[1] );
	RS_printf("ioMxic1Tbl.tslr1[2]  = %x\n", (kuint)&ioMxic1Tbl.tslr1[2] );
	RS_printf("ioMxic1Tbl.tslr1[3]  = %x\n", (kuint)&ioMxic1Tbl.tslr1[3] );
	RS_printf("ioMxic1Tbl.tslr2[0]  = %x\n", (kuint)&ioMxic1Tbl.tslr2[0] );
	RS_printf("ioMxic1Tbl.tslr2[1]  = %x\n", (kuint)&ioMxic1Tbl.tslr2[1] );
	RS_printf("ioMxic1Tbl.tslr2[2]  = %x\n", (kuint)&ioMxic1Tbl.tslr2[2] );
	RS_printf("ioMxic1Tbl.tslr2[3]  = %x\n", (kuint)&ioMxic1Tbl.tslr2[3] );
	RS_printf("ioMxic1Tbl.tslr3[0]  = %x\n", (kuint)&ioMxic1Tbl.tslr3[0] );
	RS_printf("ioMxic1Tbl.tslr3[1]  = %x\n", (kuint)&ioMxic1Tbl.tslr3[1] );
	RS_printf("ioMxic1Tbl.tslr3[2]  = %x\n", (kuint)&ioMxic1Tbl.tslr3[2] );
	RS_printf("ioMxic1Tbl.tslr3[3]  = %x\n", (kuint)&ioMxic1Tbl.tslr3[3] );
	RS_printf("ioMxic1Tbl.tslr4[0]  = %x\n", (kuint)&ioMxic1Tbl.tslr4[0] );
	RS_printf("ioMxic1Tbl.tslr4[1]  = %x\n", (kuint)&ioMxic1Tbl.tslr4[1] );
	RS_printf("ioMxic1Tbl.tslr4[2]  = %x\n", (kuint)&ioMxic1Tbl.tslr4[2] );
	RS_printf("ioMxic1Tbl.tslr4[3]  = %x\n", (kuint)&ioMxic1Tbl.tslr4[3] );

	RS_printf("ioMxic2Tbl.tslw1[0]  = %x\n", (kuint)&ioMxic2Tbl.tslw1[0] );

	RS_printf("ioMxic3Tbl.tslw1[0]  = %x\n", (kuint)&ioMxic3Tbl.tslw1[0] );

	RS_printf(" \n");
#endif
}

Mxic *mxic_test_new(void)
{
	Mxic *self = g_object_new(MXIC_TYPE_TEST, NULL);
	return self;
}
