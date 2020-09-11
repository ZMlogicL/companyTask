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
#include "itmtest.h"


G_DEFINE_TYPE(ItmTest, itm_test, G_TYPE_OBJECT);

#define ITM_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),ITM_TYPE_TEST, ItmTestPrivate));


struct _ItmTestPrivate
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
static void itm_test_class_init(ItmTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ItmTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void itm_test_init(ItmTest *self)
{
	ItmTestPrivate *priv = ITM_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(itm_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	ItmTest *self = ITM_TEST(object);
	ItmTestPrivate *priv = ITM_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(itm_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void ltm_test( void )
{
#if 0	// for PC debug
#define IO_LTM_P1		(*IO_LTM2_P1)
#define IO_LTM_P2		(*IO_LTM2_P2)
#define IO_LTM_P3		(*IO_LTM2_P3)
#define IO_LTM_TBL_P1	(*IO_LTM2_TBL_P1)
#define IO_LTM_TBL_P2	(*IO_LTM2_TBL_P2)
#define IO_LTM_TBL_P3	(*IO_LTM2_TBL_P3)
	volatile struct io_ltm_top*		IO_LTM2_P1		= (void*)0x28413000;
	volatile struct io_ltm_top*		IO_LTM2_P2		= (void*)0x28513000;
	volatile struct io_ltm_top*		IO_LTM2_P3		= (void*)0x28613000;
	volatile struct io_ltm_sram*	IO_LTM2_TBL_P1	= (void*)0x29490000;
	volatile struct io_ltm_sram*	IO_LTM2_TBL_P2	= (void*)0x29590000;
	volatile struct io_ltm_sram*	IO_LTM2_TBL_P3	= (void*)0x29690000;
#endif
	RS_printf("LTM\n");
#if 0
/* rbk */
	RS_printf("IO_LTM_P1.RBK.RBKSR       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RBKSR );
	RS_printf("IO_LTM_P1.RBK.RSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSRAMEN );
	RS_printf("IO_LTM_P1.RBK.RTRG        = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RTRG );
	RS_printf("IO_LTM_P1.RBK.RFRSTP      = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RFRSTP );
	RS_printf("IO_LTM_P1.RBK.RPARMSK     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RPARMSK );
	RS_printf("IO_LTM_P1.RBK.RINT0       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RINT0 );
	RS_printf("IO_LTM_P1.RBK.RINT1       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RINT1 );
	RS_printf("IO_LTM_P1.RBK.RLINTLV     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RLINTLV );
	RS_printf("IO_LTM_P1.RBK.RAXICTLR1   = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RAXICTLR1 );
	RS_printf("IO_LTM_P1.RBK.RAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RAXIRERR );
	RS_printf("IO_LTM_P1.RBK.RAXICTLW1   = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RAXICTLW1 );
	RS_printf("IO_LTM_P1.RBK.RAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RAXIWERR );
	RS_printf("IO_LTM_P1.RBK.RAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RAXIBSIZ );
	RS_printf("IO_LTM_P1.RBK.RSDRHSZ     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSDRHSZ );
	RS_printf("IO_LTM_P1.RBK.RSDRDEF     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSDRDEF );
	RS_printf("IO_LTM_P1.RBK.RSDRVSZ     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSDRVSZ );
	RS_printf("IO_LTM_P1.RBK.RSDRADR     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSDRADR );
	RS_printf("IO_LTM_P1.RBK.RSDRADG     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSDRADG );
	RS_printf("IO_LTM_P1.RBK.RSDRADB     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSDRADB );
	RS_printf("IO_LTM_P1.RBK.RSDWAD      = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSDWAD );
	RS_printf("IO_LTM_P1.RBK.RSDWDEF     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSDWDEF );
	RS_printf("IO_LTM_P1.RBK.RIOCTL      = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RIOCTL );
	RS_printf("IO_LTM_P1.RBK.BTHSTA0     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.BTHSTA0 );
	RS_printf("IO_LTM_P1.RBK.BTVSTA0     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.BTVSTA0 );
	RS_printf("IO_LTM_P1.RBK.BTHSIZ0     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.BTHSIZ0 );
	RS_printf("IO_LTM_P1.RBK.BTVSIZ0     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.BTVSIZ0 );
	RS_printf("IO_LTM_P1.RBK.BTHSTA1     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.BTHSTA1 );
	RS_printf("IO_LTM_P1.RBK.BTVSTA1     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.BTVSTA1 );
	RS_printf("IO_LTM_P1.RBK.BTHSIZ1     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.BTHSIZ1 );
	RS_printf("IO_LTM_P1.RBK.BTVSIZ1     = %lX\n", (unsigned long)&IO_LTM_P1.RBK.BTVSIZ1 );
	RS_printf("IO_LTM_P1.RBK.RSFEN       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RSFEN );
	RS_printf("IO_LTM_P1.RBK.HVEN        = %lX\n", (unsigned long)&IO_LTM_P1.RBK.HVEN );
	RS_printf("IO_LTM_P1.RBK.RHSTA       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RHSTA );
	RS_printf("IO_LTM_P1.RBK.RHPIT       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RHPIT );
	RS_printf("IO_LTM_P1.RBK.RVSTA       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RVSTA );
	RS_printf("IO_LTM_P1.RBK.RVPIT       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RVPIT );
	RS_printf("IO_LTM_P1.RBK.RDCMD       = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RDCMD );
	RS_printf("IO_LTM_P1.RBK.RTEN        = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RTEN );
	RS_printf("IO_LTM_P1.RBK.RTHSTA      = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RTHSTA );
	RS_printf("IO_LTM_P1.RBK.RTVSTA      = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RTVSTA );
	RS_printf("IO_LTM_P1.RBK.RTHSIZ      = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RTHSIZ );
	RS_printf("IO_LTM_P1.RBK.RTVSIZ      = %lX\n", (unsigned long)&IO_LTM_P1.RBK.RTVSIZ );

/* map */
	RS_printf("IO_LTM_P1.MAP.MAPSR       = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MAPSR );
	RS_printf("IO_LTM_P1.MAP.MSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSRAMEN );
	RS_printf("IO_LTM_P1.MAP.MTRG        = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MTRG );
	RS_printf("IO_LTM_P1.MAP.MFRSTP      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MFRSTP );
	RS_printf("IO_LTM_P1.MAP.MPARMSK     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MPARMSK );
	RS_printf("IO_LTM_P1.MAP.MINT0       = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MINT0 );
	RS_printf("IO_LTM_P1.MAP.MINT1       = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MINT1 );
	RS_printf("IO_LTM_P1.MAP.MLINTLV     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MLINTLV );
	RS_printf("IO_LTM_P1.MAP.AXICHSEL    = %lX\n", (unsigned long)&IO_LTM_P1.MAP.AXICHSEL );
	RS_printf("IO_LTM_P1.MAP.MAXICTLR    = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MAXICTLR );
	RS_printf("IO_LTM_P1.MAP.MAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MAXIRERR );
	RS_printf("IO_LTM_P1.MAP.MAXICTLW    = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MAXICTLW );
	RS_printf("IO_LTM_P1.MAP.MAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MAXIWERR );
	RS_printf("IO_LTM_P1.MAP.MAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MAXIBSIZ );
	RS_printf("IO_LTM_P1.MAP.MSDRHSZ     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDRHSZ );
	RS_printf("IO_LTM_P1.MAP.MSDRDEF     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDRDEF );
	RS_printf("IO_LTM_P1.MAP.MSDRVSZ     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDRVSZ );
	RS_printf("IO_LTM_P1.MAP.MSDRAD      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDRAD );
	RS_printf("IO_LTM_P1.MAP.MSDROFS     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDROFS );
	RS_printf("IO_LTM_P1.MAP.MSDWADW0    = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDWADW0 );
	RS_printf("IO_LTM_P1.MAP.MSDWDEFW0   = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDWDEFW0 );
	RS_printf("IO_LTM_P1.MAP.MSDWADW1    = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDWADW1 );
	RS_printf("IO_LTM_P1.MAP.MSDWDEFW1   = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MSDWDEFW1 );
	RS_printf("IO_LTM_P1.MAP.MIOCTL      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MIOCTL );
	RS_printf("IO_LTM_P1.MAP.GAINR       = %lX\n", (unsigned long)&IO_LTM_P1.MAP.GAINR );
	RS_printf("IO_LTM_P1.MAP.GAING       = %lX\n", (unsigned long)&IO_LTM_P1.MAP.GAING );
	RS_printf("IO_LTM_P1.MAP.GAINB       = %lX\n", (unsigned long)&IO_LTM_P1.MAP.GAINB );
	RS_printf("IO_LTM_P1.MAP.GAINCPR     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.GAINCPR );
	RS_printf("IO_LTM_P1.MAP.GAINCPG     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.GAINCPG );
	RS_printf("IO_LTM_P1.MAP.GAINCPB     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.GAINCPB );
	RS_printf("IO_LTM_P1.MAP.PEPS0M      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.PEPS0M );
	RS_printf("IO_LTM_P1.MAP.PEPS0OF     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.PEPS0OF );
	RS_printf("IO_LTM_P1.MAP.PEPS1M      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.PEPS1M );
	RS_printf("IO_LTM_P1.MAP.PEPS1OF     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.PEPS1OF );
	RS_printf("IO_LTM_P1.MAP.PEPS2M      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.PEPS2M );
	RS_printf("IO_LTM_P1.MAP.PEPS2OF     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.PEPS2OF );
	RS_printf("IO_LTM_P1.MAP.NEPS0M      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.NEPS0M );
	RS_printf("IO_LTM_P1.MAP.NEPS0OF     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.NEPS0OF );
	RS_printf("IO_LTM_P1.MAP.NEPS1M      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.NEPS1M );
	RS_printf("IO_LTM_P1.MAP.NEPS1OF     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.NEPS1OF );
	RS_printf("IO_LTM_P1.MAP.NEPS2M      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.NEPS2M );
	RS_printf("IO_LTM_P1.MAP.NEPS2OF     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.NEPS2OF );
	RS_printf("IO_LTM_P1.MAP.YSHADOW     = %lX\n", (unsigned long)&IO_LTM_P1.MAP.YSHADOW );
	RS_printf("IO_LTM_P1.MAP.YHIGHLIGHT  = %lX\n", (unsigned long)&IO_LTM_P1.MAP.YHIGHLIGHT );
	RS_printf("IO_LTM_P1.MAP.MYLCTL      = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MYLCTL );
	RS_printf("IO_LTM_P1.MAP.MYLOG0EP0   = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MYLOG0EP0 );
	RS_printf("IO_LTM_P1.MAP.MYLOG0EP1   = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MYLOG0EP1 );
	RS_printf("IO_LTM_P1.MAP.MYLOG1EP0   = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MYLOG1EP0 );
	RS_printf("IO_LTM_P1.MAP.MYLOG1EP1   = %lX\n", (unsigned long)&IO_LTM_P1.MAP.MYLOG1EP1 );

/* ltm */
	RS_printf("IO_LTM_P1.LTM.LTMSR       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LTMSR );
	RS_printf("IO_LTM_P1.LTM.LSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSRAMEN );
	RS_printf("IO_LTM_P1.LTM.LTRG        = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LTRG );
	RS_printf("IO_LTM_P1.LTM.LFRSTP      = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LFRSTP );
	RS_printf("IO_LTM_P1.LTM.LPARMSK     = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LPARMSK );
	RS_printf("IO_LTM_P1.LTM.LINT0       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LINT0 );
	RS_printf("IO_LTM_P1.LTM.LINT1       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LINT1 );
	RS_printf("IO_LTM_P1.LTM.LLINTLV     = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LLINTLV );
	RS_printf("IO_LTM_P1.LTM.LAXICTLR1   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LAXICTLR1 );
	RS_printf("IO_LTM_P1.LTM.LAXICTLR2   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LAXICTLR2 );
	RS_printf("IO_LTM_P1.LTM.LAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LAXIRERR );
	RS_printf("IO_LTM_P1.LTM.LAXICTLW    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LAXICTLW );
	RS_printf("IO_LTM_P1.LTM.LAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LAXIWERR );
	RS_printf("IO_LTM_P1.LTM.LAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LAXIBSIZ );
	RS_printf("IO_LTM_P1.LTM.AXIRSEL     = %lX\n", (unsigned long)&IO_LTM_P1.LTM.AXIRSEL );
	RS_printf("IO_LTM_P1.LTM.LSDRHSZR2   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRHSZR2 );
	RS_printf("IO_LTM_P1.LTM.LSDRDEFR2   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRDEFR2 );
	RS_printf("IO_LTM_P1.LTM.LSDRVSZR2   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRVSZR2 );
	RS_printf("IO_LTM_P1.LTM.LSDRADR2R   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRADR2R );
	RS_printf("IO_LTM_P1.LTM.LSDRADR2G   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRADR2G );
	RS_printf("IO_LTM_P1.LTM.LSDRADR2B   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRADR2B );
	RS_printf("IO_LTM_P1.LTM.LSDRHSZR3   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRHSZR3 );
	RS_printf("IO_LTM_P1.LTM.LSDRDEFR3   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRDEFR3 );
	RS_printf("IO_LTM_P1.LTM.LSDRVSZR3   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRVSZR3 );
	RS_printf("IO_LTM_P1.LTM.LSDRADR3    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRADR3 );
	RS_printf("IO_LTM_P1.LTM.LSDRDEFR4   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRDEFR4 );
	RS_printf("IO_LTM_P1.LTM.LSDRADR4    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDRADR4 );
	RS_printf("IO_LTM_P1.LTM.LSDROFS     = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDROFS );
	RS_printf("IO_LTM_P1.LTM.LSDWADR     = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDWADR );
	RS_printf("IO_LTM_P1.LTM.LSDWDEFR    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDWDEFR );
	RS_printf("IO_LTM_P1.LTM.LSDWADG     = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDWADG );
	RS_printf("IO_LTM_P1.LTM.LSDWDEFG    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDWDEFG );
	RS_printf("IO_LTM_P1.LTM.LSDWADB     = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDWADB );
	RS_printf("IO_LTM_P1.LTM.LSDWDEFB    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LSDWDEFB );
	RS_printf("IO_LTM_P1.LTM.LIOCTL      = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LIOCTL );
	RS_printf("IO_LTM_P1.LTM.LHSTA       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LHSTA );
	RS_printf("IO_LTM_P1.LTM.LHPIT       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LHPIT );
	RS_printf("IO_LTM_P1.LTM.LVSTA       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LVSTA );
	RS_printf("IO_LTM_P1.LTM.LVPIT       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LVPIT );
	RS_printf("IO_LTM_P1.LTM.NLVTHOF7    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.NLVTHOF7 );
	RS_printf("IO_LTM_P1.LTM.PLVTHOF7    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.PLVTHOF7 );
	RS_printf("IO_LTM_P1.LTM.LYSHADOW    = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LYSHADOW );
	RS_printf("IO_LTM_P1.LTM.LYHIGHLIGHT = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LYHIGHLIGHT );
	RS_printf("IO_LTM_P1.LTM.BLDYRT      = %lX\n", (unsigned long)&IO_LTM_P1.LTM.BLDYRT );
	RS_printf("IO_LTM_P1.LTM.BLDOF       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.BLDOF );
	RS_printf("IO_LTM_P1.LTM.BLDGA       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.BLDGA );
	RS_printf("IO_LTM_P1.LTM.BLDBD       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.BLDBD );
	RS_printf("IO_LTM_P1.LTM.LTMMD       = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LTMMD );
	RS_printf("IO_LTM_P1.LTM.CGOF        = %lX\n", (unsigned long)&IO_LTM_P1.LTM.CGOF );
	RS_printf("IO_LTM_P1.LTM.CGGA        = %lX\n", (unsigned long)&IO_LTM_P1.LTM.CGGA );
	RS_printf("IO_LTM_P1.LTM.CGBD        = %lX\n", (unsigned long)&IO_LTM_P1.LTM.CGBD );
	RS_printf("IO_LTM_P1.LTM.LYLCTL      = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LYLCTL );
	RS_printf("IO_LTM_P1.LTM.LYLOG0EP0   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LYLOG0EP0 );
	RS_printf("IO_LTM_P1.LTM.LYLOG0EP1   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LYLOG0EP1 );
	RS_printf("IO_LTM_P1.LTM.LYLOG1EP0   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LYLOG1EP0 );
	RS_printf("IO_LTM_P1.LTM.LYLOG1EP1   = %lX\n", (unsigned long)&IO_LTM_P1.LTM.LYLOG1EP1 );

/* map tbl */
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG0TBL1.hword[511] );

	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.MAP_SRAM.MYLOG1TBL1.hword[511] );

/* ltm tbl */
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG0TBL1.hword[511] );

	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P1.LTM_SRAM.LYLOG1TBL1.hword[511] );

	RS_printf(" \n");

	RS_printf("IO_LTM_P2.RBK.RBKSR       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RBKSR );
	RS_printf("IO_LTM_P2.RBK.RSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSRAMEN );
	RS_printf("IO_LTM_P2.RBK.RTRG        = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RTRG );
	RS_printf("IO_LTM_P2.RBK.RFRSTP      = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RFRSTP );
	RS_printf("IO_LTM_P2.RBK.RPARMSK     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RPARMSK );
	RS_printf("IO_LTM_P2.RBK.RINT0       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RINT0 );
	RS_printf("IO_LTM_P2.RBK.RINT1       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RINT1 );
	RS_printf("IO_LTM_P2.RBK.RLINTLV     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RLINTLV );
	RS_printf("IO_LTM_P2.RBK.RAXICTLR1   = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RAXICTLR1 );
	RS_printf("IO_LTM_P2.RBK.RAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RAXIRERR );
	RS_printf("IO_LTM_P2.RBK.RAXICTLW1   = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RAXICTLW1 );
	RS_printf("IO_LTM_P2.RBK.RAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RAXIWERR );
	RS_printf("IO_LTM_P2.RBK.RAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RAXIBSIZ );
	RS_printf("IO_LTM_P2.RBK.RSDRHSZ     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSDRHSZ );
	RS_printf("IO_LTM_P2.RBK.RSDRDEF     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSDRDEF );
	RS_printf("IO_LTM_P2.RBK.RSDRVSZ     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSDRVSZ );
	RS_printf("IO_LTM_P2.RBK.RSDRADR     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSDRADR );
	RS_printf("IO_LTM_P2.RBK.RSDRADG     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSDRADG );
	RS_printf("IO_LTM_P2.RBK.RSDRADB     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSDRADB );
	RS_printf("IO_LTM_P2.RBK.RSDWAD      = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSDWAD );
	RS_printf("IO_LTM_P2.RBK.RSDWDEF     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSDWDEF );
	RS_printf("IO_LTM_P2.RBK.RIOCTL      = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RIOCTL );
	RS_printf("IO_LTM_P2.RBK.BTHSTA0     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.BTHSTA0 );
	RS_printf("IO_LTM_P2.RBK.BTVSTA0     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.BTVSTA0 );
	RS_printf("IO_LTM_P2.RBK.BTHSIZ0     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.BTHSIZ0 );
	RS_printf("IO_LTM_P2.RBK.BTVSIZ0     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.BTVSIZ0 );
	RS_printf("IO_LTM_P2.RBK.BTHSTA1     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.BTHSTA1 );
	RS_printf("IO_LTM_P2.RBK.BTVSTA1     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.BTVSTA1 );
	RS_printf("IO_LTM_P2.RBK.BTHSIZ1     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.BTHSIZ1 );
	RS_printf("IO_LTM_P2.RBK.BTVSIZ1     = %lX\n", (unsigned long)&IO_LTM_P2.RBK.BTVSIZ1 );
	RS_printf("IO_LTM_P2.RBK.RSFEN       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RSFEN );
	RS_printf("IO_LTM_P2.RBK.HVEN        = %lX\n", (unsigned long)&IO_LTM_P2.RBK.HVEN );
	RS_printf("IO_LTM_P2.RBK.RHSTA       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RHSTA );
	RS_printf("IO_LTM_P2.RBK.RHPIT       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RHPIT );
	RS_printf("IO_LTM_P2.RBK.RVSTA       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RVSTA );
	RS_printf("IO_LTM_P2.RBK.RVPIT       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RVPIT );
	RS_printf("IO_LTM_P2.RBK.RDCMD       = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RDCMD );
	RS_printf("IO_LTM_P2.RBK.RTEN        = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RTEN );
	RS_printf("IO_LTM_P2.RBK.RTHSTA      = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RTHSTA );
	RS_printf("IO_LTM_P2.RBK.RTVSTA      = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RTVSTA );
	RS_printf("IO_LTM_P2.RBK.RTHSIZ      = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RTHSIZ );
	RS_printf("IO_LTM_P2.RBK.RTVSIZ      = %lX\n", (unsigned long)&IO_LTM_P2.RBK.RTVSIZ );

/* map */
	RS_printf("IO_LTM_P2.MAP.MAPSR       = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MAPSR );
	RS_printf("IO_LTM_P2.MAP.MSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSRAMEN );
	RS_printf("IO_LTM_P2.MAP.MTRG        = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MTRG );
	RS_printf("IO_LTM_P2.MAP.MFRSTP      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MFRSTP );
	RS_printf("IO_LTM_P2.MAP.MPARMSK     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MPARMSK );
	RS_printf("IO_LTM_P2.MAP.MINT0       = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MINT0 );
	RS_printf("IO_LTM_P2.MAP.MINT1       = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MINT1 );
	RS_printf("IO_LTM_P2.MAP.MLINTLV     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MLINTLV );
	RS_printf("IO_LTM_P2.MAP.AXICHSEL    = %lX\n", (unsigned long)&IO_LTM_P2.MAP.AXICHSEL);
	RS_printf("IO_LTM_P2.MAP.MAXICTLR    = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MAXICTLR );
	RS_printf("IO_LTM_P2.MAP.MAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MAXIRERR );
	RS_printf("IO_LTM_P2.MAP.MAXICTLW    = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MAXICTLW );
	RS_printf("IO_LTM_P2.MAP.MAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MAXIWERR );
	RS_printf("IO_LTM_P2.MAP.MAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MAXIBSIZ );
	RS_printf("IO_LTM_P2.MAP.MSDRHSZ     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDRHSZ );
	RS_printf("IO_LTM_P2.MAP.MSDRDEF     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDRDEF );
	RS_printf("IO_LTM_P2.MAP.MSDRVSZ     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDRVSZ );
	RS_printf("IO_LTM_P2.MAP.MSDRAD      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDRAD );
	RS_printf("IO_LTM_P2.MAP.MSDROFS     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDROFS );
	RS_printf("IO_LTM_P2.MAP.MSDWADW0    = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDWADW0 );
	RS_printf("IO_LTM_P2.MAP.MSDWDEFW0   = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDWDEFW0 );
	RS_printf("IO_LTM_P2.MAP.MSDWADW1    = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDWADW1 );
	RS_printf("IO_LTM_P2.MAP.MSDWDEFW1   = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MSDWDEFW1 );
	RS_printf("IO_LTM_P2.MAP.MIOCTL      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MIOCTL );
	RS_printf("IO_LTM_P2.MAP.GAINR       = %lX\n", (unsigned long)&IO_LTM_P2.MAP.GAINR );
	RS_printf("IO_LTM_P2.MAP.GAING       = %lX\n", (unsigned long)&IO_LTM_P2.MAP.GAING );
	RS_printf("IO_LTM_P2.MAP.GAINB       = %lX\n", (unsigned long)&IO_LTM_P2.MAP.GAINB );
	RS_printf("IO_LTM_P2.MAP.GAINCPR     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.GAINCPR );
	RS_printf("IO_LTM_P2.MAP.GAINCPG     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.GAINCPG );
	RS_printf("IO_LTM_P2.MAP.GAINCPB     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.GAINCPB );
	RS_printf("IO_LTM_P2.MAP.PEPS0M      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.PEPS0M );
	RS_printf("IO_LTM_P2.MAP.PEPS0OF     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.PEPS0OF );
	RS_printf("IO_LTM_P2.MAP.PEPS1M      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.PEPS1M );
	RS_printf("IO_LTM_P2.MAP.PEPS1OF     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.PEPS1OF );
	RS_printf("IO_LTM_P2.MAP.PEPS2M      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.PEPS2M );
	RS_printf("IO_LTM_P2.MAP.PEPS2OF     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.PEPS2OF );
	RS_printf("IO_LTM_P2.MAP.NEPS0M      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.NEPS0M );
	RS_printf("IO_LTM_P2.MAP.NEPS0OF     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.NEPS0OF );
	RS_printf("IO_LTM_P2.MAP.NEPS1M      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.NEPS1M );
	RS_printf("IO_LTM_P2.MAP.NEPS1OF     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.NEPS1OF );
	RS_printf("IO_LTM_P2.MAP.NEPS2M      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.NEPS2M );
	RS_printf("IO_LTM_P2.MAP.NEPS2OF     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.NEPS2OF );
	RS_printf("IO_LTM_P2.MAP.YSHADOW     = %lX\n", (unsigned long)&IO_LTM_P2.MAP.YSHADOW );
	RS_printf("IO_LTM_P2.MAP.YHIGHLIGHT  = %lX\n", (unsigned long)&IO_LTM_P2.MAP.YHIGHLIGHT );
	RS_printf("IO_LTM_P2.MAP.MYLCTL      = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MYLCTL );
	RS_printf("IO_LTM_P2.MAP.MYLOG0EP0   = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MYLOG0EP0 );
	RS_printf("IO_LTM_P2.MAP.MYLOG0EP1   = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MYLOG0EP1 );
	RS_printf("IO_LTM_P2.MAP.MYLOG1EP0   = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MYLOG1EP0 );
	RS_printf("IO_LTM_P2.MAP.MYLOG1EP1   = %lX\n", (unsigned long)&IO_LTM_P2.MAP.MYLOG1EP1 );

/* ltm */
	RS_printf("IO_LTM_P2.LTM.LTMSR       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LTMSR );
	RS_printf("IO_LTM_P2.LTM.LSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSRAMEN );
	RS_printf("IO_LTM_P2.LTM.LTRG        = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LTRG );
	RS_printf("IO_LTM_P2.LTM.LFRSTP      = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LFRSTP );
	RS_printf("IO_LTM_P2.LTM.LPARMSK     = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LPARMSK );
	RS_printf("IO_LTM_P2.LTM.LINT0       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LINT0 );
	RS_printf("IO_LTM_P2.LTM.LINT1       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LINT1 );
	RS_printf("IO_LTM_P2.LTM.LLINTLV     = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LLINTLV );
	RS_printf("IO_LTM_P2.LTM.LAXICTLR1   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LAXICTLR1 );
	RS_printf("IO_LTM_P2.LTM.LAXICTLR2   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LAXICTLR2 );
	RS_printf("IO_LTM_P2.LTM.LAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LAXIRERR );
	RS_printf("IO_LTM_P2.LTM.LAXICTLW    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LAXICTLW );
	RS_printf("IO_LTM_P2.LTM.LAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LAXIWERR );
	RS_printf("IO_LTM_P2.LTM.LAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LAXIBSIZ );
	RS_printf("IO_LTM_P2.LTM.AXIRSEL     = %lX\n", (unsigned long)&IO_LTM_P2.LTM.AXIRSEL );
	RS_printf("IO_LTM_P2.LTM.LSDRHSZR2   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRHSZR2 );
	RS_printf("IO_LTM_P2.LTM.LSDRDEFR2   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRDEFR2 );
	RS_printf("IO_LTM_P2.LTM.LSDRVSZR2   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRVSZR2 );
	RS_printf("IO_LTM_P2.LTM.LSDRADR2R   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRADR2R );
	RS_printf("IO_LTM_P2.LTM.LSDRADR2G   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRADR2G );
	RS_printf("IO_LTM_P2.LTM.LSDRADR2B   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRADR2B );
	RS_printf("IO_LTM_P2.LTM.LSDRHSZR3   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRHSZR3 );
	RS_printf("IO_LTM_P2.LTM.LSDRDEFR3   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRDEFR3 );
	RS_printf("IO_LTM_P2.LTM.LSDRVSZR3   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRVSZR3 );
	RS_printf("IO_LTM_P2.LTM.LSDRADR3    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRADR3 );
	RS_printf("IO_LTM_P2.LTM.LSDRDEFR4   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRDEFR4 );
	RS_printf("IO_LTM_P2.LTM.LSDRADR4    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDRADR4 );
	RS_printf("IO_LTM_P2.LTM.LSDROFS     = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDROFS );
	RS_printf("IO_LTM_P2.LTM.LSDWADR     = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDWADR );
	RS_printf("IO_LTM_P2.LTM.LSDWDEFR    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDWDEFR );
	RS_printf("IO_LTM_P2.LTM.LSDWADG     = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDWADG );
	RS_printf("IO_LTM_P2.LTM.LSDWDEFG    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDWDEFG );
	RS_printf("IO_LTM_P2.LTM.LSDWADB     = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDWADB );
	RS_printf("IO_LTM_P2.LTM.LSDWDEFB    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LSDWDEFB );
	RS_printf("IO_LTM_P2.LTM.LIOCTL      = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LIOCTL );
	RS_printf("IO_LTM_P2.LTM.LHSTA       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LHSTA );
	RS_printf("IO_LTM_P2.LTM.LHPIT       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LHPIT );
	RS_printf("IO_LTM_P2.LTM.LVSTA       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LVSTA );
	RS_printf("IO_LTM_P2.LTM.LVPIT       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LVPIT );
	RS_printf("IO_LTM_P2.LTM.NLVTHOF7    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.NLVTHOF7 );
	RS_printf("IO_LTM_P2.LTM.PLVTHOF7    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.PLVTHOF7 );
	RS_printf("IO_LTM_P2.LTM.LYSHADOW    = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LYSHADOW );
	RS_printf("IO_LTM_P2.LTM.LYHIGHLIGHT = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LYHIGHLIGHT );
	RS_printf("IO_LTM_P2.LTM.BLDYRT      = %lX\n", (unsigned long)&IO_LTM_P2.LTM.BLDYRT );
	RS_printf("IO_LTM_P2.LTM.BLDOF       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.BLDOF );
	RS_printf("IO_LTM_P2.LTM.BLDGA       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.BLDGA );
	RS_printf("IO_LTM_P2.LTM.BLDBD       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.BLDBD );
	RS_printf("IO_LTM_P2.LTM.LTMMD       = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LTMMD );
	RS_printf("IO_LTM_P2.LTM.CGOF        = %lX\n", (unsigned long)&IO_LTM_P2.LTM.CGOF );
	RS_printf("IO_LTM_P2.LTM.CGGA        = %lX\n", (unsigned long)&IO_LTM_P2.LTM.CGGA );
	RS_printf("IO_LTM_P2.LTM.CGBD        = %lX\n", (unsigned long)&IO_LTM_P2.LTM.CGBD );
	RS_printf("IO_LTM_P2.LTM.LYLCTL      = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LYLCTL );
	RS_printf("IO_LTM_P2.LTM.LYLOG0EP0   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LYLOG0EP0 );
	RS_printf("IO_LTM_P2.LTM.LYLOG0EP1   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LYLOG0EP1 );
	RS_printf("IO_LTM_P2.LTM.LYLOG1EP0   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LYLOG1EP0 );
	RS_printf("IO_LTM_P2.LTM.LYLOG1EP1   = %lX\n", (unsigned long)&IO_LTM_P2.LTM.LYLOG1EP1 );

/* map tbl */
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG0TBL1.hword[511] );

	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.MAP_SRAM.MYLOG1TBL1.hword[511] );

/* ltm tbl */
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG0TBL1.hword[511] );

	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P2.LTM_SRAM.LYLOG1TBL1.hword[511] );

	RS_printf(" \n");

	RS_printf("IO_LTM_P3.RBK.RBKSR       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RBKSR );
	RS_printf("IO_LTM_P3.RBK.RSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSRAMEN );
	RS_printf("IO_LTM_P3.RBK.RTRG        = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RTRG );
	RS_printf("IO_LTM_P3.RBK.RFRSTP      = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RFRSTP );
	RS_printf("IO_LTM_P3.RBK.RPARMSK     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RPARMSK );
	RS_printf("IO_LTM_P3.RBK.RINT0       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RINT0 );
	RS_printf("IO_LTM_P3.RBK.RINT1       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RINT1 );
	RS_printf("IO_LTM_P3.RBK.RLINTLV     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RLINTLV );
	RS_printf("IO_LTM_P3.RBK.RAXICTLR1   = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RAXICTLR1 );
	RS_printf("IO_LTM_P3.RBK.RAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RAXIRERR );
	RS_printf("IO_LTM_P3.RBK.RAXICTLW1   = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RAXICTLW1 );
	RS_printf("IO_LTM_P3.RBK.RAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RAXIWERR );
	RS_printf("IO_LTM_P3.RBK.RAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RAXIBSIZ );
	RS_printf("IO_LTM_P3.RBK.RSDRHSZ     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSDRHSZ );
	RS_printf("IO_LTM_P3.RBK.RSDRDEF     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSDRDEF );
	RS_printf("IO_LTM_P3.RBK.RSDRVSZ     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSDRVSZ );
	RS_printf("IO_LTM_P3.RBK.RSDRADR     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSDRADR );
	RS_printf("IO_LTM_P3.RBK.RSDRADG     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSDRADG );
	RS_printf("IO_LTM_P3.RBK.RSDRADB     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSDRADB );
	RS_printf("IO_LTM_P3.RBK.RSDWAD      = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSDWAD );
	RS_printf("IO_LTM_P3.RBK.RSDWDEF     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSDWDEF );
	RS_printf("IO_LTM_P3.RBK.RIOCTL      = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RIOCTL );
	RS_printf("IO_LTM_P3.RBK.BTHSTA0     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.BTHSTA0 );
	RS_printf("IO_LTM_P3.RBK.BTVSTA0     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.BTVSTA0 );
	RS_printf("IO_LTM_P3.RBK.BTHSIZ0     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.BTHSIZ0 );
	RS_printf("IO_LTM_P3.RBK.BTVSIZ0     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.BTVSIZ0 );
	RS_printf("IO_LTM_P3.RBK.BTHSTA1     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.BTHSTA1 );
	RS_printf("IO_LTM_P3.RBK.BTVSTA1     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.BTVSTA1 );
	RS_printf("IO_LTM_P3.RBK.BTHSIZ1     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.BTHSIZ1 );
	RS_printf("IO_LTM_P3.RBK.BTVSIZ1     = %lX\n", (unsigned long)&IO_LTM_P3.RBK.BTVSIZ1 );
	RS_printf("IO_LTM_P3.RBK.RSFEN       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RSFEN );
	RS_printf("IO_LTM_P3.RBK.HVEN        = %lX\n", (unsigned long)&IO_LTM_P3.RBK.HVEN );
	RS_printf("IO_LTM_P3.RBK.RHSTA       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RHSTA );
	RS_printf("IO_LTM_P3.RBK.RHPIT       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RHPIT );
	RS_printf("IO_LTM_P3.RBK.RVSTA       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RVSTA );
	RS_printf("IO_LTM_P3.RBK.RVPIT       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RVPIT );
	RS_printf("IO_LTM_P3.RBK.RDCMD       = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RDCMD );
	RS_printf("IO_LTM_P3.RBK.RTEN        = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RTEN );
	RS_printf("IO_LTM_P3.RBK.RTHSTA      = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RTHSTA );
	RS_printf("IO_LTM_P3.RBK.RTVSTA      = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RTVSTA );
	RS_printf("IO_LTM_P3.RBK.RTHSIZ      = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RTHSIZ );
	RS_printf("IO_LTM_P3.RBK.RTVSIZ      = %lX\n", (unsigned long)&IO_LTM_P3.RBK.RTVSIZ );

/* map */
	RS_printf("IO_LTM_P3.MAP.MAPSR       = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MAPSR );
	RS_printf("IO_LTM_P3.MAP.MSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSRAMEN );
	RS_printf("IO_LTM_P3.MAP.MTRG        = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MTRG );
	RS_printf("IO_LTM_P3.MAP.MFRSTP      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MFRSTP );
	RS_printf("IO_LTM_P3.MAP.MPARMSK     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MPARMSK );
	RS_printf("IO_LTM_P3.MAP.MINT0       = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MINT0 );
	RS_printf("IO_LTM_P3.MAP.MINT1       = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MINT1 );
	RS_printf("IO_LTM_P3.MAP.MLINTLV     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MLINTLV );
	RS_printf("IO_LTM_P3.MAP.AXICHSEL    = %lX\n", (unsigned long)&IO_LTM_P3.MAP.AXICHSEL );
	RS_printf("IO_LTM_P3.MAP.MAXICTLR    = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MAXICTLR );
	RS_printf("IO_LTM_P3.MAP.MAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MAXIRERR );
	RS_printf("IO_LTM_P3.MAP.MAXICTLW    = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MAXICTLW );
	RS_printf("IO_LTM_P3.MAP.MAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MAXIWERR );
	RS_printf("IO_LTM_P3.MAP.MAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MAXIBSIZ );
	RS_printf("IO_LTM_P3.MAP.MSDRHSZ     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDRHSZ );
	RS_printf("IO_LTM_P3.MAP.MSDRDEF     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDRDEF );
	RS_printf("IO_LTM_P3.MAP.MSDRVSZ     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDRVSZ );
	RS_printf("IO_LTM_P3.MAP.MSDRAD      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDRAD );
	RS_printf("IO_LTM_P3.MAP.MSDROFS     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDROFS );
	RS_printf("IO_LTM_P3.MAP.MSDWADW0    = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDWADW0 );
	RS_printf("IO_LTM_P3.MAP.MSDWDEFW0   = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDWDEFW0 );
	RS_printf("IO_LTM_P3.MAP.MSDWADW1    = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDWADW1 );
	RS_printf("IO_LTM_P3.MAP.MSDWDEFW1   = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MSDWDEFW1 );
	RS_printf("IO_LTM_P3.MAP.MIOCTL      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MIOCTL );
	RS_printf("IO_LTM_P3.MAP.GAINR       = %lX\n", (unsigned long)&IO_LTM_P3.MAP.GAINR );
	RS_printf("IO_LTM_P3.MAP.GAING       = %lX\n", (unsigned long)&IO_LTM_P3.MAP.GAING );
	RS_printf("IO_LTM_P3.MAP.GAINB       = %lX\n", (unsigned long)&IO_LTM_P3.MAP.GAINB );
	RS_printf("IO_LTM_P3.MAP.GAINCPR     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.GAINCPR );
	RS_printf("IO_LTM_P3.MAP.GAINCPG     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.GAINCPG );
	RS_printf("IO_LTM_P3.MAP.GAINCPB     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.GAINCPB );
	RS_printf("IO_LTM_P3.MAP.PEPS0M      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.PEPS0M );
	RS_printf("IO_LTM_P3.MAP.PEPS0OF     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.PEPS0OF );
	RS_printf("IO_LTM_P3.MAP.PEPS1M      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.PEPS1M );
	RS_printf("IO_LTM_P3.MAP.PEPS1OF     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.PEPS1OF );
	RS_printf("IO_LTM_P3.MAP.PEPS2M      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.PEPS2M );
	RS_printf("IO_LTM_P3.MAP.PEPS2OF     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.PEPS2OF );
	RS_printf("IO_LTM_P3.MAP.NEPS0M      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.NEPS0M );
	RS_printf("IO_LTM_P3.MAP.NEPS0OF     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.NEPS0OF );
	RS_printf("IO_LTM_P3.MAP.NEPS1M      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.NEPS1M );
	RS_printf("IO_LTM_P3.MAP.NEPS1OF     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.NEPS1OF );
	RS_printf("IO_LTM_P3.MAP.NEPS2M      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.NEPS2M );
	RS_printf("IO_LTM_P3.MAP.NEPS2OF     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.NEPS2OF );
	RS_printf("IO_LTM_P3.MAP.YSHADOW     = %lX\n", (unsigned long)&IO_LTM_P3.MAP.YSHADOW );
	RS_printf("IO_LTM_P3.MAP.YHIGHLIGHT  = %lX\n", (unsigned long)&IO_LTM_P3.MAP.YHIGHLIGHT );
	RS_printf("IO_LTM_P3.MAP.MYLCTL      = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MYLCTL );
	RS_printf("IO_LTM_P3.MAP.MYLOG0EP0   = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MYLOG0EP0 );
	RS_printf("IO_LTM_P3.MAP.MYLOG0EP1   = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MYLOG0EP1 );
	RS_printf("IO_LTM_P3.MAP.MYLOG1EP0   = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MYLOG1EP0 );
	RS_printf("IO_LTM_P3.MAP.MYLOG1EP1   = %lX\n", (unsigned long)&IO_LTM_P3.MAP.MYLOG1EP1 );

/* ltm */
	RS_printf("IO_LTM_P3.LTM.LTMSR       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LTMSR );
	RS_printf("IO_LTM_P3.LTM.LSRAMEN     = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSRAMEN );
	RS_printf("IO_LTM_P3.LTM.LTRG        = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LTRG );
	RS_printf("IO_LTM_P3.LTM.LFRSTP      = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LFRSTP );
	RS_printf("IO_LTM_P3.LTM.LPARMSK     = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LPARMSK );
	RS_printf("IO_LTM_P3.LTM.LINT0       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LINT0 );
	RS_printf("IO_LTM_P3.LTM.LINT1       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LINT1 );
	RS_printf("IO_LTM_P3.LTM.LLINTLV     = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LLINTLV );
	RS_printf("IO_LTM_P3.LTM.LAXICTLR1   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LAXICTLR1 );
	RS_printf("IO_LTM_P3.LTM.LAXICTLR2   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LAXICTLR2 );
	RS_printf("IO_LTM_P3.LTM.LAXIRERR    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LAXIRERR );
	RS_printf("IO_LTM_P3.LTM.LAXICTLW    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LAXICTLW );
	RS_printf("IO_LTM_P3.LTM.LAXIWERR    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LAXIWERR );
	RS_printf("IO_LTM_P3.LTM.LAXIBSIZ    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LAXIBSIZ );
	RS_printf("IO_LTM_P3.LTM.AXIRSEL     = %lX\n", (unsigned long)&IO_LTM_P3.LTM.AXIRSEL );
	RS_printf("IO_LTM_P3.LTM.LSDRHSZR2   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRHSZR2 );
	RS_printf("IO_LTM_P3.LTM.LSDRDEFR2   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRDEFR2 );
	RS_printf("IO_LTM_P3.LTM.LSDRVSZR2   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRVSZR2 );
	RS_printf("IO_LTM_P3.LTM.LSDRADR2R   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRADR2R );
	RS_printf("IO_LTM_P3.LTM.LSDRADR2G   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRADR2G );
	RS_printf("IO_LTM_P3.LTM.LSDRADR2B   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRADR2B );
	RS_printf("IO_LTM_P3.LTM.LSDRHSZR3   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRHSZR3 );
	RS_printf("IO_LTM_P3.LTM.LSDRDEFR3   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRDEFR3 );
	RS_printf("IO_LTM_P3.LTM.LSDRVSZR3   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRVSZR3 );
	RS_printf("IO_LTM_P3.LTM.LSDRADR3    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRADR3 );
	RS_printf("IO_LTM_P3.LTM.LSDRDEFR4   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRDEFR4 );
	RS_printf("IO_LTM_P3.LTM.LSDRADR4    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDRADR4 );
	RS_printf("IO_LTM_P3.LTM.LSDROFS     = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDROFS );
	RS_printf("IO_LTM_P3.LTM.LSDWADR     = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDWADR );
	RS_printf("IO_LTM_P3.LTM.LSDWDEFR    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDWDEFR );
	RS_printf("IO_LTM_P3.LTM.LSDWADG     = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDWADG );
	RS_printf("IO_LTM_P3.LTM.LSDWDEFG    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDWDEFG );
	RS_printf("IO_LTM_P3.LTM.LSDWADB     = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDWADB );
	RS_printf("IO_LTM_P3.LTM.LSDWDEFB    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LSDWDEFB );
	RS_printf("IO_LTM_P3.LTM.LIOCTL      = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LIOCTL );
	RS_printf("IO_LTM_P3.LTM.LHSTA       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LHSTA );
	RS_printf("IO_LTM_P3.LTM.LHPIT       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LHPIT );
	RS_printf("IO_LTM_P3.LTM.LVSTA       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LVSTA );
	RS_printf("IO_LTM_P3.LTM.LVPIT       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LVPIT );
	RS_printf("IO_LTM_P3.LTM.NLVTHOF7    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.NLVTHOF7 );
	RS_printf("IO_LTM_P3.LTM.PLVTHOF7    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.PLVTHOF7 );
	RS_printf("IO_LTM_P3.LTM.LYSHADOW    = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LYSHADOW );
	RS_printf("IO_LTM_P3.LTM.LYHIGHLIGHT = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LYHIGHLIGHT );
	RS_printf("IO_LTM_P3.LTM.BLDYRT      = %lX\n", (unsigned long)&IO_LTM_P3.LTM.BLDYRT );
	RS_printf("IO_LTM_P3.LTM.BLDOF       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.BLDOF );
	RS_printf("IO_LTM_P3.LTM.BLDGA       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.BLDGA );
	RS_printf("IO_LTM_P3.LTM.BLDBD       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.BLDBD );
	RS_printf("IO_LTM_P3.LTM.LTMMD       = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LTMMD );
	RS_printf("IO_LTM_P3.LTM.CGOF        = %lX\n", (unsigned long)&IO_LTM_P3.LTM.CGOF );
	RS_printf("IO_LTM_P3.LTM.CGGA        = %lX\n", (unsigned long)&IO_LTM_P3.LTM.CGGA );
	RS_printf("IO_LTM_P3.LTM.CGBD        = %lX\n", (unsigned long)&IO_LTM_P3.LTM.CGBD );
	RS_printf("IO_LTM_P3.LTM.LYLCTL      = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LYLCTL );
	RS_printf("IO_LTM_P3.LTM.LYLOG0EP0   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LYLOG0EP0 );
	RS_printf("IO_LTM_P3.LTM.LYLOG0EP1   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LYLOG0EP1 );
	RS_printf("IO_LTM_P3.LTM.LYLOG1EP0   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LYLOG1EP0 );
	RS_printf("IO_LTM_P3.LTM.LYLOG1EP1   = %lX\n", (unsigned long)&IO_LTM_P3.LTM.LYLOG1EP1 );

/* map tbl */
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG0TBL1.hword[511] );

	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.MAP_SRAM.MYLOG1TBL1.hword[511] );

/* ltm tbl */
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL0[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL0.hword[0] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL0[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL0.hword[1] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL0[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL0.hword[510] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL0[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL0.hword[511] );

	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG0TBL1.hword[511] );

	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL1[0]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL1.hword[0] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL1[1]   = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL1.hword[1] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL1[510] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL1.hword[510] );
	RS_printf("IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL1[511] = %lX\n", (unsigned long)&IO_LTM_TBL_P3.LTM_SRAM.LYLOG1TBL1.hword[511] );

	RS_printf(" \n");

#endif
}

ItmTest *itm_test_new()
{
	ItmTest *self = g_object_new(ITM_TYPE_TEST, NULL);
	return self;
}
