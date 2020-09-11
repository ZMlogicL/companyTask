/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :陈柱
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
*/
#include "defs.h"
#include "b2rtest.h"


G_DEFINE_TYPE(B2rTest, b2r_test, G_TYPE_OBJECT);

#define B2R_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),B2R_TYPE_TEST, B2rTestPrivate));


#if 0	// for PC debug
#define B2rTest_IO_B2R_P1		(*ioB2r2P1)
#define B2rTest_IO_B2R_P2		(*ioB2r2P2)
#define B2rTest_IO_B2R_TBL_P1	(*ioB2r2TblP1)
#define B2rTest_IO_B2R_TBL_P2	(*ioB2r2TblP2)
#endif


struct _B2rTestPrivate
{
	 gpointer preserved;
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
static void b2r_test_class_init(B2rTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(B2rTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void b2r_test_init(B2rTest *self)
{
	B2rTestPrivate *priv = B2R_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(b2r_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	B2rTest *self = B2R_TEST(object);
	B2rTestPrivate *priv = B2R_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(b2r_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{
}
/**
 * PUBLIC
 */
void b2r_test(void)
{
#if 0
	volatile struct io_b2r*ioB2r2P1		= (void*)0x28412000;
	volatile struct io_b2r*ioB2r2P2		= (void*)0x28512000;
	volatile struct io_b2r_sram*ioB2r2TblP1	= (void*)0x29482000;
	volatile struct io_b2r_sram*ioB2r2TblP2	= (void*)0x29582000;
#endif
	RS_printf("B2R\n");
#if 0
/* f_b2r */
	RS_printf("IO_B2R_P1.F_B2R.CNTL.CNTL        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CNTL.CNTL );
	RS_printf("IO_B2R_P1.F_B2R.CNTL.B2RINTE     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CNTL.B2RINTE );
	RS_printf("IO_B2R_P1.F_B2R.CNTL.B2RINTF     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CNTL.B2RINTF );
	RS_printf("IO_B2R_P1.F_B2R.CNTL.FLTAEN      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CNTL.FLTAEN );

	RS_printf("IO_B2R_P1.F_B2R.OFG.OFSTRB       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.OFSTRB );
	RS_printf("IO_B2R_P1.F_B2R.OFG.OFSTG        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.OFSTG );
	RS_printf("IO_B2R_P1.F_B2R.OFG.BLSFT        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.BLSFT );
	RS_printf("IO_B2R_P1.F_B2R.OFG.WBGARB       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.WBGARB );
	RS_printf("IO_B2R_P1.F_B2R.OFG.WBGAGR       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.WBGAGR );
	RS_printf("IO_B2R_P1.F_B2R.OFG.WBHCTL       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.WBHCTL );
	RS_printf("IO_B2R_P1.F_B2R.OFG.WBSLP        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.WBSLP );
	RS_printf("IO_B2R_P1.F_B2R.OFG.WBLVRB       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.WBLVRB );
	RS_printf("IO_B2R_P1.F_B2R.OFG.WBLVGR       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.OFG.WBLVGR );

	RS_printf("IO_B2R_P1.F_B2R.CIA.SHARP        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CIA.SHARP );
	RS_printf("IO_B2R_P1.F_B2R.CIA.AIRESY       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CIA.AIRESY );
	RS_printf("IO_B2R_P1.F_B2R.CIA.LF           = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CIA.LF );
	RS_printf("IO_B2R_P1.F_B2R.CIA.CMC          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CIA.CMC );
	RS_printf("IO_B2R_P1.F_B2R.CIA.DIRRLITH     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.CIA.DIRRLITH );

	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACTL       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACTL );

	RS_printf("IO_B2R_P1.F_B2R.HFA.HFK[0]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFK.word[0] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFK[1]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFK.word[1] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFK[2]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFK.word[2] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFK[3]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFK.word[3] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFEFCLP      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFEFCLP );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAFST       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAFST );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAFGU       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAFGU );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAFCLP      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAFCLP );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYC[0]     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYC.word[0] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYC[1]     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYC.word[1] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYC[2]     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYC.word[2] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYC[3]     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYC.word[3] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYOF[0]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYOF.word[0] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYOF[1]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYOF.word[1] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYGA       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYGA );

	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYBD[0]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYBD.word[0] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYBD[1]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYBD.word[1] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYDIV      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYDIV );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYCLP      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYCLP );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACOR       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACOR );

	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACLP[0]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACLP.word[0] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACLP[1]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACLP.word[1] );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVCTL    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVCTL );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACVAFX     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACVAFX );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVASCLOF = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVASCLOF );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVASCLGA = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVASCLGA );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVASCLBD = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVASCLBD );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVASCLCP = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVASCLCP );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYASCLGA   = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYASCLGA );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYASCLBD   = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYASCLBD );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYASCLCLP  = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYASCLCLP );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACVBFX     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACVBFX );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVBSCLOF = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVBSCLOF );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVBSCLGA = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVBSCLGA );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVBSCLBD = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVBSCLBD );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFACRVBSCLCP = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFACRVBSCLCP );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYBSCLGA   = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYBSCLGA );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYBSCLBD   = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYBSCLBD );
	RS_printf("IO_B2R_P1.F_B2R.HFA.HFAYBSCLCLP  = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.F_B2R.HFA.HFAYBSCLCLP );

/* jdsb2r */
	RS_printf("IO_B2R_P1.YBCH.YBRAXCTL          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBRAXCTL );
	RS_printf("IO_B2R_P1.YBCH.YBWAXCTL          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBWAXCTL );
	RS_printf("IO_B2R_P1.YBCH.YBRAXSTS          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBRAXSTS );
	RS_printf("IO_B2R_P1.YBCH.YBWAXSTS          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBWAXSTS );
	RS_printf("IO_B2R_P1.YBCH.YBRAXMD           = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBRAXMD );
	RS_printf("IO_B2R_P1.YBCH.YBWAXMD           = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBWAXMD );
	RS_printf("IO_B2R_P1.YBCH.YBRREQMSK         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBRREQMSK );

	RS_printf("IO_B2R_P1.YBCH.YBWREQMSK[0]      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBWREQMSK.word[0] );
	RS_printf("IO_B2R_P1.YBCH.YBWREQMSK[1]      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBCH.YBWREQMSK.word[1] );

	RS_printf("IO_B2R_P1.B2R_CMN.YBINTE         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.B2R_CMN.YBINTE );
	RS_printf("IO_B2R_P1.B2R_CMN.YBINTF         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.B2R_CMN.YBINTF );
	RS_printf("IO_B2R_P1.B2R_CMN.DINSEL         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.B2R_CMN.DINSEL );
	RS_printf("IO_B2R_P1.B2R_CMN.B2RMODE        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.B2R_CMN.B2RMODE );
	RS_printf("IO_B2R_P1.B2R_CMN.ELNLV          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.B2R_CMN.ELNLV );
	RS_printf("IO_B2R_P1.B2R_CMN.RAMAEN         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.B2R_CMN.RAMAEN );
	RS_printf("IO_B2R_P1.B2R_CMN.EXALMSL        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.B2R_CMN.EXALMSL );

	RS_printf("IO_B2R_P1.YBR.YBRTRG             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.YBRTRG );
	RS_printf("IO_B2R_P1.YBR.YBRCTL             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.YBRCTL );
	RS_printf("IO_B2R_P1.YBR.YBRA               = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.YBRA );
	RS_printf("IO_B2R_P1.YBR.YBROFS             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.YBROFS );
	RS_printf("IO_B2R_P1.YBR.YBRDEF             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.YBRDEF );
	RS_printf("IO_B2R_P1.YBR.YBRHSIZ            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.YBRHSIZ );
	RS_printf("IO_B2R_P1.YBR.YBRVSIZ            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.YBRVSIZ );
	RS_printf("IO_B2R_P1.YBR.YBRHBLNK           = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.YBRHBLNK );
	RS_printf("IO_B2R_P1.YBR.DINCTL             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.DINCTL );
	RS_printf("IO_B2R_P1.YBR.DINHSTA            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.DINHSTA );
	RS_printf("IO_B2R_P1.YBR.DINVSTA            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.DINVSTA );
	RS_printf("IO_B2R_P1.YBR.DINHSIZ            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.DINHSIZ );
	RS_printf("IO_B2R_P1.YBR.DINVSIZ            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.DINVSIZ );
	RS_printf("IO_B2R_P1.YBR.DINELS             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.DINELS );
	RS_printf("IO_B2R_P1.YBR.DINERR             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBR.DINERR );

	RS_printf("IO_B2R_P1.YBW.YBWTRG             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWTRG );
	RS_printf("IO_B2R_P1.YBW.YBWCTL             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWCTL );
	RS_printf("IO_B2R_P1.YBW.YBWMD              = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWMD );
	RS_printf("IO_B2R_P1.YBW.YBWBANK            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWBANK );

	RS_printf("IO_B2R_P1.YBW.YBWA[0][0]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWA.word[0][0] );
	RS_printf("IO_B2R_P1.YBW.YBWA[0][1]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWA.word[0][1] );
	RS_printf("IO_B2R_P1.YBW.YBWA[2][2]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWA.word[2][2] );
	RS_printf("IO_B2R_P1.YBW.YBWA[2][3]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWA.word[2][3] );

	RS_printf("IO_B2R_P1.YBW.YBWDEF             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWDEF );
	RS_printf("IO_B2R_P1.YBW.YBWTRMH            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWTRMH );
	RS_printf("IO_B2R_P1.YBW.YBWTRMV            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P1.YBW.YBWTRMV );

/* jdsb2r tbl */
	RS_printf("IO_B2R_TBL_P1.DKNTBL[0]          = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.DKNTBL.hword[0] );
	RS_printf("IO_B2R_TBL_P1.DKNTBL[1]          = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.DKNTBL.hword[1] );
	RS_printf("IO_B2R_TBL_P1.DKNTBL[254]        = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.DKNTBL.hword[254] );
	RS_printf("IO_B2R_TBL_P1.DKNTBL[255]        = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.DKNTBL.hword[255] );

	RS_printf("IO_B2R_TBL_P1.KNETBLR[0]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLR.byte[0] );
	RS_printf("IO_B2R_TBL_P1.KNETBLR[1]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLR.byte[1] );
	RS_printf("IO_B2R_TBL_P1.KNETBLR[255]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLR.byte[255] );
	RS_printf("IO_B2R_TBL_P1.KNETBLR[256]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLR.byte[256] );

	RS_printf("IO_B2R_TBL_P1.KNETBLG[0]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLG.byte[0] );
	RS_printf("IO_B2R_TBL_P1.KNETBLG[1]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLG.byte[1] );
	RS_printf("IO_B2R_TBL_P1.KNETBLG[255]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLG.byte[255] );
	RS_printf("IO_B2R_TBL_P1.KNETBLG[256]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLG.byte[256] );

	RS_printf("IO_B2R_TBL_P1.KNETBLB[0]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLB.byte[0] );
	RS_printf("IO_B2R_TBL_P1.KNETBLB[1]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLB.byte[1] );
	RS_printf("IO_B2R_TBL_P1.KNETBLB[255]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLB.byte[255] );
	RS_printf("IO_B2R_TBL_P1.KNETBLB[256]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P1.KNETBLB.byte[256] );

	RS_printf(" \n");

/* f_b2r */
	RS_printf("IO_B2R_P2.F_B2R.CNTL.CNTL        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CNTL.CNTL );
	RS_printf("IO_B2R_P2.F_B2R.CNTL.B2RINTE     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CNTL.B2RINTE );
	RS_printf("IO_B2R_P2.F_B2R.CNTL.B2RINTF     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CNTL.B2RINTF );
	RS_printf("IO_B2R_P2.F_B2R.CNTL.FLTAEN      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CNTL.FLTAEN );

	RS_printf("IO_B2R_P2.F_B2R.OFG.OFSTRB       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.OFSTRB );
	RS_printf("IO_B2R_P2.F_B2R.OFG.OFSTG        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.OFSTG );
	RS_printf("IO_B2R_P2.F_B2R.OFG.BLSFT        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.BLSFT );
	RS_printf("IO_B2R_P2.F_B2R.OFG.WBGARB       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.WBGARB );
	RS_printf("IO_B2R_P2.F_B2R.OFG.WBGAGR       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.WBGAGR );
	RS_printf("IO_B2R_P2.F_B2R.OFG.WBHCTL       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.WBHCTL );
	RS_printf("IO_B2R_P2.F_B2R.OFG.WBSLP        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.WBSLP );
	RS_printf("IO_B2R_P2.F_B2R.OFG.WBLVRB       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.WBLVRB );
	RS_printf("IO_B2R_P2.F_B2R.OFG.WBLVGR       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.OFG.WBLVGR );

	RS_printf("IO_B2R_P2.F_B2R.CIA.SHARP        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CIA.SHARP );
	RS_printf("IO_B2R_P2.F_B2R.CIA.AIRESY       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CIA.AIRESY );
	RS_printf("IO_B2R_P2.F_B2R.CIA.LF           = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CIA.LF );
	RS_printf("IO_B2R_P2.F_B2R.CIA.CMC          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CIA.CMC );
	RS_printf("IO_B2R_P2.F_B2R.CIA.DIRRLITH     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.CIA.DIRRLITH );

	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACTL       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACTL );

	RS_printf("IO_B2R_P2.F_B2R.HFA.HFK[0]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFK.word[0] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFK[1]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFK.word[1] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFK[2]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFK.word[2] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFK[3]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFK.word[3] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFEFCLP      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFEFCLP );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAFST       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAFST );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAFGU       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAFGU );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAFCLP      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAFCLP );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYC[0]     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYC.word[0] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYC[1]     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYC.word[1] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYC[2]     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYC.word[2] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYC[3]     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYC.word[3] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYOF[0]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYOF.word[0] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYOF[1]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYOF.word[1] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYGA       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYGA );

	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYBD[0]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYBD.word[0] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYBD[1]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYBD.word[1] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYDIV      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYDIV );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYCLP      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYCLP );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACOR       = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACOR );

	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACLP[0]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACLP.word[0] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACLP[1]    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACLP.word[1] );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVCTL    = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVCTL );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACVAFX     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACVAFX );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVASCLOF = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVASCLOF );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVASCLGA = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVASCLGA );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVASCLBD = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVASCLBD );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVASCLCP = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVASCLCP );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYASCLGA   = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYASCLGA );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYASCLBD   = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYASCLBD );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYASCLCLP  = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYASCLCLP );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACVBFX     = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACVBFX );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVBSCLOF = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVBSCLOF );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVBSCLGA = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVBSCLGA );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVBSCLBD = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVBSCLBD );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFACRVBSCLCP = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFACRVBSCLCP );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYBSCLGA   = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYBSCLGA );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYBSCLBD   = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYBSCLBD );
	RS_printf("IO_B2R_P2.F_B2R.HFA.HFAYBSCLCLP  = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.F_B2R.HFA.HFAYBSCLCLP );

/* jdsb2r */
	RS_printf("IO_B2R_P2.YBCH.YBRAXCTL          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBRAXCTL );
	RS_printf("IO_B2R_P2.YBCH.YBWAXCTL          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBWAXCTL );
	RS_printf("IO_B2R_P2.YBCH.YBRAXSTS          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBRAXSTS );
	RS_printf("IO_B2R_P2.YBCH.YBWAXSTS          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBWAXSTS );
	RS_printf("IO_B2R_P2.YBCH.YBRAXMD           = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBRAXMD );
	RS_printf("IO_B2R_P2.YBCH.YBWAXMD           = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBWAXMD );
	RS_printf("IO_B2R_P2.YBCH.YBRREQMSK         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBRREQMSK );

	RS_printf("IO_B2R_P2.YBCH.YBWREQMSK[0]      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBWREQMSK.word[0] );
	RS_printf("IO_B2R_P2.YBCH.YBWREQMSK[1]      = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBCH.YBWREQMSK.word[1] );

	RS_printf("IO_B2R_P2.B2R_CMN.YBINTE         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.B2R_CMN.YBINTE );
	RS_printf("IO_B2R_P2.B2R_CMN.YBINTF         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.B2R_CMN.YBINTF );
	RS_printf("IO_B2R_P2.B2R_CMN.DINSEL         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.B2R_CMN.DINSEL );
	RS_printf("IO_B2R_P2.B2R_CMN.B2RMODE        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.B2R_CMN.B2RMODE );
	RS_printf("IO_B2R_P2.B2R_CMN.ELNLV          = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.B2R_CMN.ELNLV );
	RS_printf("IO_B2R_P2.B2R_CMN.RAMAEN         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.B2R_CMN.RAMAEN );
	RS_printf("IO_B2R_P2.B2R_CMN.EXALMSL        = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.B2R_CMN.EXALMSL );

	RS_printf("IO_B2R_P2.YBR.YBRTRG             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.YBRTRG );
	RS_printf("IO_B2R_P2.YBR.YBRCTL             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.YBRCTL );
	RS_printf("IO_B2R_P2.YBR.YBRA               = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.YBRA );
	RS_printf("IO_B2R_P2.YBR.YBROFS             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.YBROFS );
	RS_printf("IO_B2R_P2.YBR.YBRDEF             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.YBRDEF );
	RS_printf("IO_B2R_P2.YBR.YBRHSIZ            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.YBRHSIZ );
	RS_printf("IO_B2R_P2.YBR.YBRVSIZ            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.YBRVSIZ );
	RS_printf("IO_B2R_P2.YBR.YBRHBLNK           = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.YBRHBLNK );
	RS_printf("IO_B2R_P2.YBR.DINCTL             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.DINCTL );
	RS_printf("IO_B2R_P2.YBR.DINHSTA            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.DINHSTA );
	RS_printf("IO_B2R_P2.YBR.DINVSTA            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.DINVSTA );
	RS_printf("IO_B2R_P2.YBR.DINHSIZ            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.DINHSIZ );
	RS_printf("IO_B2R_P2.YBR.DINVSIZ            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.DINVSIZ );
	RS_printf("IO_B2R_P2.YBR.DINELS             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.DINELS );
	RS_printf("IO_B2R_P2.YBR.DINERR             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBR.DINERR );

	RS_printf("IO_B2R_P2.YBW.YBWTRG             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWTRG );
	RS_printf("IO_B2R_P2.YBW.YBWCTL             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWCTL );
	RS_printf("IO_B2R_P2.YBW.YBWMD              = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWMD );
	RS_printf("IO_B2R_P2.YBW.YBWBANK            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWBANK );

	RS_printf("IO_B2R_P2.YBW.YBWA[0][0]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWA.word[0][0] );
	RS_printf("IO_B2R_P2.YBW.YBWA[0][1]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWA.word[0][1] );
	RS_printf("IO_B2R_P2.YBW.YBWA[2][2]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWA.word[2][2] );
	RS_printf("IO_B2R_P2.YBW.YBWA[2][3]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWA.word[2][3] );

	RS_printf("IO_B2R_P2.YBW.YBWDEF             = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWDEF );
	RS_printf("IO_B2R_P2.YBW.YBWTRMH            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWTRMH );
	RS_printf("IO_B2R_P2.YBW.YBWTRMV            = %lX\n", (unsigned long)&B2rTest_IO_B2R_P2.YBW.YBWTRMV );

/* jdsb2r tbl */
	RS_printf("IO_B2R_TBL_P2.DKNTBL[0]          = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.DKNTBL.hword[0] );
	RS_printf("IO_B2R_TBL_P2.DKNTBL[1]          = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.DKNTBL.hword[1] );
	RS_printf("IO_B2R_TBL_P2.DKNTBL[254]        = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.DKNTBL.hword[254] );
	RS_printf("IO_B2R_TBL_P2.DKNTBL[255]        = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.DKNTBL.hword[255] );

	RS_printf("IO_B2R_TBL_P2.KNETBLR[0]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLR.byte[0] );
	RS_printf("IO_B2R_TBL_P2.KNETBLR[1]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLR.byte[1] );
	RS_printf("IO_B2R_TBL_P2.KNETBLR[255]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLR.byte[255] );
	RS_printf("IO_B2R_TBL_P2.KNETBLR[256]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLR.byte[256] );

	RS_printf("IO_B2R_TBL_P2.KNETBLG[0]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLG.byte[0] );
	RS_printf("IO_B2R_TBL_P2.KNETBLG[1]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLG.byte[1] );
	RS_printf("IO_B2R_TBL_P2.KNETBLG[255]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLG.byte[255] );
	RS_printf("IO_B2R_TBL_P2.KNETBLG[256]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLG.byte[256] );

	RS_printf("IO_B2R_TBL_P2.KNETBLB[0]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLB.byte[0] );
	RS_printf("IO_B2R_TBL_P2.KNETBLB[1]         = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLB.byte[1] );
	RS_printf("IO_B2R_TBL_P2.KNETBLB[255]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLB.byte[255] );
	RS_printf("IO_B2R_TBL_P2.KNETBLB[256]       = %lX\n", (unsigned long)&B2rTest_IO_B2R_TBL_P2.KNETBLB.byte[256] );

	RS_printf(" \n");
#endif
}

B2rTest *b2r_test_new()
{
	B2rTest *self = g_object_new(B2R_TYPE_TEST, NULL);
	return self;
}
