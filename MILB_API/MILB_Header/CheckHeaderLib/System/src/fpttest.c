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
#include "fpttest.h"


G_DEFINE_TYPE(FptTest, fpt_test, G_TYPE_OBJECT);

#define FPT_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),FPT_TYPE_TEST, FptTestPrivate));


struct _FptTestPrivate
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
static void fpt_test_class_init(FptTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(FptTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void fpt_test_init(FptTest *self)
{
	FptTestPrivate *priv = FPT_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(fpt_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	FptTest *self = FPT_TEST(object);
	FptTestPrivate *priv = FPT_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(fpt_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
void fpt_test()
{
#if 0	// for PC debug
	volatile struct io_jdsfpt*		IO_FPT;
	volatile struct io_jdsfpt_ahb*	IO_FPT_AHB;
	IO_FPT = (void*)0x288D0000;
	IO_FPT_AHB = (void*)0x298C1000;
	int loop;
#endif

	RS_printf("FPT\n");
#if 0
	for( loop = 0; loop < 2; loop++ ){
		RS_printf("IO_FPT[%d].FPTCTL0         = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTCTL0 );
		RS_printf("IO_FPT[%d].FPTCTL1         = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTCTL1 );
		RS_printf("IO_FPT[%d].FPTCTL2         = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTCTL2 );
		RS_printf("IO_FPT[%d].FPTFQCTL0       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL0 );
		RS_printf("IO_FPT[%d].FPTFQCTL1       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL1 );
		RS_printf("IO_FPT[%d].FPTFQCTL2       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL2 );
		RS_printf("IO_FPT[%d].FPTFQCTL3       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL3 );
		RS_printf("IO_FPT[%d].FPTFQCTL4       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL4 );
		RS_printf("IO_FPT[%d].FPTFQCTL5       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL5 );
		RS_printf("IO_FPT[%d].FPTFQCTL6       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL6 );
		RS_printf("IO_FPT[%d].FPTFQCTL7       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL7 );
		RS_printf("IO_FPT[%d].FPTFQCTL8       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL8 );
		RS_printf("IO_FPT[%d].FPTFQCTL9       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFQCTL9 );
		RS_printf("IO_FPT[%d].FPTFTCTL0       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL0 );
		RS_printf("IO_FPT[%d].FPTFTCTL1       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL1 );
		RS_printf("IO_FPT[%d].FPTFTCTL2       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL2 );
		RS_printf("IO_FPT[%d].FPTFTCTL3       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL3 );
		RS_printf("IO_FPT[%d].FPTFTCTL4       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL4 );
		RS_printf("IO_FPT[%d].FPTFTCTL5       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL5 );
		RS_printf("IO_FPT[%d].FPTFTCTL6       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL6 );
		RS_printf("IO_FPT[%d].FPTFTCTL7       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL7 );
		RS_printf("IO_FPT[%d].FPTFTCTL8       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL8 );
		RS_printf("IO_FPT[%d].FPTFTCTL9       = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL9 );
		RS_printf("IO_FPT[%d].FPTFTCTL10      = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTFTCTL10 );
		RS_printf("IO_FPT[%d].FPTINTE0        = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTINTE0 );
		RS_printf("IO_FPT[%d].FPTINTF0        = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTINTF0 );
		RS_printf("IO_FPT[%d].FPTAXICTL0      = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTAXICTL0 );
		RS_printf("IO_FPT[%d].FPTAXIERR0      = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTAXIERR0 );
		RS_printf("IO_FPT[%d].FPTCTL3         = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTCTL3 );
		RS_printf("IO_FPT[%d].FPTCTL4         = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTCTL4 );
		RS_printf("IO_FPT[%d].FPTCTL5         = 0x%lX\n", loop, (unsigned long)&IO_FPT[loop].FPTCTL5 );
		RS_printf(" \n");
		RS_printf("IO_FPT_AHB[%d].FPTLUT0_0   = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTLUT0.word[0] );
		RS_printf("IO_FPT_AHB[%d].FPTLUT0_1   = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTLUT0.word[1] );
		RS_printf("IO_FPT_AHB[%d].FPTLUT0_62  = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTLUT0.word[62] );
		RS_printf("IO_FPT_AHB[%d].FPTLUT0_63  = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTLUT0.word[63] );
		RS_printf("IO_FPT_AHB[%d].FPTLUT1_0   = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTLUT1.word[0] );
		RS_printf("IO_FPT_AHB[%d].FPTLUT1_1   = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTLUT1.word[1] );
		RS_printf("IO_FPT_AHB[%d].FPTLUT1_62  = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTLUT1.word[62] );
		RS_printf("IO_FPT_AHB[%d].FPTLUT1_63  = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTLUT1.word[63] );
		RS_printf("IO_FPT_AHB[%d].FPTREG0_0   = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTREG0.word[0] );
		RS_printf("IO_FPT_AHB[%d].FPTREG0_1   = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTREG0.word[1] );
		RS_printf("IO_FPT_AHB[%d].FPTREG0_126 = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTREG0.word[126] );
		RS_printf("IO_FPT_AHB[%d].FPTREG0_127 = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTREG0.word[127] );
		RS_printf("IO_FPT_AHB[%d].FPTREG1_0   = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTREG1.word[0] );
		RS_printf("IO_FPT_AHB[%d].FPTREG1_1   = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTREG1.word[1] );
		RS_printf("IO_FPT_AHB[%d].FPTREG1_126 = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTREG1.word[126] );
		RS_printf("IO_FPT_AHB[%d].FPTREG1_127 = 0x%lX\n", loop, (unsigned long)&IO_FPT_AHB[loop].FPTREG1.word[127] );
		RS_printf(" \n");
	}
#endif
}

FptTest *fpt_test_new()
{
	FptTest *self = g_object_new(FPT_TYPE_TEST, NULL);
	return self;
}
