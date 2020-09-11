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
#include "ipcutest.h"


G_DEFINE_TYPE(IpcuTest, ipcu_test, G_TYPE_OBJECT);

#define IPCU_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),IPCU_TYPE_TEST, IpcuTestPrivate));


struct _IpcuTestPrivate
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
static void ipcu_test_class_init(IpcuTestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(IpcuTestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void ipcu_test_init(IpcuTest *self)
{
	IpcuTestPrivate *priv = IPCU_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ipcu_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	IpcuTest *self = IPCU_TEST(object);
	IpcuTestPrivate *priv = IPCU_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(ipcu_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void ipcu_test()
{
	RS_printf("IO_IPCU\n");
#if 0
	/* Unit0 */
	RS_printf("IO_IPCU0                   		= %p\n", &IO_IPCU0 );
	RS_printf("IO_IPCU0.ISR[0]              	= %p\n", &IO_IPCU0.ISR[0] );
	for(int i=1; i<16; i++) {
		RS_printf("IO_IPCU0.ISR[%d]         	= %p\n", i, &IO_IPCU0.ISR[i] );
	}
	RS_printf("Reserved                     	= %p\n", &IO_IPCU0.dmy_0040_007F );
	RS_printf(" \n");

	RS_printf("IO_IPCU0.MBADR[0]             	= %p\n", &IO_IPCU0.MBADR[0] );
	for(int i=1; i<16; i++) {
		RS_printf("IO_IPCU0.MBADR[%d]        	= %p\n", i, &IO_IPCU0.MBADR[i] );
	}
	RS_printf("Reserved                     	= %p\n", &IO_IPCU0.dmy_00C0_00FF );
	RS_printf(" \n");

	RS_printf("IO_IPCU0.MAILBOX[0]           	= %p\n", &IO_IPCU0.MAILBOX[0] );
	RS_printf("IO_IPCU0.MAILBOX[0].SRC       	= %p\n", &IO_IPCU0.MAILBOX[0].SRC );
	RS_printf("IO_IPCU0.MAILBOX[0].MODE      	= %p\n", &IO_IPCU0.MAILBOX[0].MODE );
	RS_printf("IO_IPCU0.MAILBOX[0].SEND      	= %p\n", &IO_IPCU0.MAILBOX[0].SEND );
	RS_printf("Reserved                     	= %p\n", &IO_IPCU0.MAILBOX[0].dmy_010C_010F );
	RS_printf("IO_IPCU0.MAILBOX[0].DSTSET    	= %p\n", &IO_IPCU0.MAILBOX[0].DSTSET );
	RS_printf("IO_IPCU0.MAILBOX[0].DSTCLR    	= %p\n", &IO_IPCU0.MAILBOX[0].DSTCLR );
	RS_printf("IO_IPCU0.MAILBOX[0].DSTSTAT   	= %p\n", &IO_IPCU0.MAILBOX[0].DSTSTAT );
	RS_printf("Reserved                     	= %p\n", &IO_IPCU0.MAILBOX[0].dmy_011C_011F );
	RS_printf("IO_IPCU0.MAILBOX[0].MASKSET   	= %p\n", &IO_IPCU0.MAILBOX[0].MASKSET );
	RS_printf("IO_IPCU0.MAILBOX[0].MASKCLR   	= %p\n", &IO_IPCU0.MAILBOX[0].MASKCLR );
	RS_printf("IO_IPCU0.MAILBOX[0].MASKSTAT  	= %p\n", &IO_IPCU0.MAILBOX[0].MASKSTAT );
	RS_printf("Reserved                     	= %p\n", &IO_IPCU0.MAILBOX[0].dmy_012C_0130 );
	RS_printf("IO_IPCU0.MAILBOX[0].ACKSET    	= %p\n", &IO_IPCU0.MAILBOX[0].ACKSET );
	RS_printf("IO_IPCU0.MAILBOX[0].ACKCLR    	= %p\n", &IO_IPCU0.MAILBOX[0].ACKCLR );
	RS_printf("IO_IPCU0.MAILBOX[0].ACKSTAT   	= %p\n", &IO_IPCU0.MAILBOX[0].ACKSTAT );
	RS_printf("IO_IPCU0.MAILBOX[0].ACKSRC    	= %p\n", &IO_IPCU0.MAILBOX[0].ACKSRC );
	RS_printf("IO_IPCU0.MAILBOX[0].DATA[0]   	= %p\n", &IO_IPCU0.MAILBOX[0].DATA[0] );
	for(int i=1; i<9; i++) {
		RS_printf("IO_IPCU0.MAILBOX[0].DATA[%d] = %p\n", i, &IO_IPCU0.MAILBOX[0].DATA[i] );
	}
	RS_printf("Reserved                     	= %p\n", &IO_IPCU0.MAILBOX[0].dmy_0164_017F );
	for(int i=1; i<8; i++) {
	RS_printf("IO_IPCU0.MAILBOX[%d]           	= %p\n", i, &IO_IPCU0.MAILBOX[i] );
	}
	RS_printf("Reserved                     	= %p\n", &IO_IPCU0.dmy_0500_08FF );
	RS_printf(" \n");

	RS_printf("IO_IPCU0.MBSTAT               	= %p\n", &IO_IPCU0.MBSTAT );
	RS_printf(" \n");
	RS_printf(" \n");

	/* Unit1 */
	RS_printf("IO_IPCU1                   		= %p\n", &IO_IPCU1 );
	RS_printf("IO_IPCU1.ISR[0]              	= %p\n", &IO_IPCU1.ISR[0] );
	for(int i=1; i<16; i++) {
		RS_printf("IO_IPCU1.ISR[%d]         	= %p\n", i, &IO_IPCU1.ISR[i] );
	}
	RS_printf("Reserved                     	= %p\n", &IO_IPCU1.dmy_0040_007F );
	RS_printf(" \n");

	RS_printf("IO_IPCU1.MBADR[0]             	= %p\n", &IO_IPCU1.MBADR[0] );
	for(int i=1; i<16; i++) {
		RS_printf("IO_IPCU1.MBADR[%d]        	= %p\n", i, &IO_IPCU1.MBADR[i] );
	}
	RS_printf("Reserved                     	= %p\n", &IO_IPCU1.dmy_00C0_00FF );
	RS_printf(" \n");

	RS_printf("IO_IPCU1.MAILBOX[0]           	= %p\n", &IO_IPCU1.MAILBOX[0] );
	RS_printf("IO_IPCU1.MAILBOX[0].SRC       	= %p\n", &IO_IPCU1.MAILBOX[0].SRC );
	RS_printf("IO_IPCU1.MAILBOX[0].MODE      	= %p\n", &IO_IPCU1.MAILBOX[0].MODE );
	RS_printf("IO_IPCU1.MAILBOX[0].SEND      	= %p\n", &IO_IPCU1.MAILBOX[0].SEND );
	RS_printf("Reserved                     	= %p\n", &IO_IPCU1.MAILBOX[0].dmy_010C_010F );
	RS_printf("IO_IPCU1.MAILBOX[0].DSTSET    	= %p\n", &IO_IPCU1.MAILBOX[0].DSTSET );
	RS_printf("IO_IPCU1.MAILBOX[0].DSTCLR    	= %p\n", &IO_IPCU1.MAILBOX[0].DSTCLR );
	RS_printf("IO_IPCU1.MAILBOX[0].DSTSTAT   	= %p\n", &IO_IPCU1.MAILBOX[0].DSTSTAT );
	RS_printf("Reserved                     	= %p\n", &IO_IPCU1.MAILBOX[0].dmy_011C_011F );
	RS_printf("IO_IPCU1.MAILBOX[0].MASKSET   	= %p\n", &IO_IPCU1.MAILBOX[0].MASKSET );
	RS_printf("IO_IPCU1.MAILBOX[0].MASKCLR   	= %p\n", &IO_IPCU1.MAILBOX[0].MASKCLR );
	RS_printf("IO_IPCU1.MAILBOX[0].MASKSTAT  	= %p\n", &IO_IPCU1.MAILBOX[0].MASKSTAT );
	RS_printf("Reserved                     	= %p\n", &IO_IPCU1.MAILBOX[0].dmy_012C_0130 );
	RS_printf("IO_IPCU1.MAILBOX[0].ACKSET    	= %p\n", &IO_IPCU1.MAILBOX[0].ACKSET );
	RS_printf("IO_IPCU1.MAILBOX[0].ACKCLR    	= %p\n", &IO_IPCU1.MAILBOX[0].ACKCLR );
	RS_printf("IO_IPCU1.MAILBOX[0].ACKSTAT   	= %p\n", &IO_IPCU1.MAILBOX[0].ACKSTAT );
	RS_printf("IO_IPCU1.MAILBOX[0].ACKSRC    	= %p\n", &IO_IPCU1.MAILBOX[0].ACKSRC );
	RS_printf("IO_IPCU1.MAILBOX[0].DATA[0]   	= %p\n", &IO_IPCU1.MAILBOX[0].DATA[0] );
	for(int i=1; i<9; i++) {
		RS_printf("IO_IPCU1.MAILBOX[0].DATA[%d] = %p\n", i, &IO_IPCU1.MAILBOX[0].DATA[i] );
	}
	RS_printf("Reserved                     	= %p\n", &IO_IPCU1.MAILBOX[0].dmy_0164_017F );
	for(int i=1; i<8; i++) {
	RS_printf("IO_IPCU1.MAILBOX[%d]           	= %p\n", i, &IO_IPCU1.MAILBOX[i] );
	}
	RS_printf("Reserved                     	= %p\n", &IO_IPCU1.dmy_0500_08FF );
	RS_printf(" \n");

	RS_printf("IO_IPCU1.MBSTAT               	= %p\n", &IO_IPCU1.MBSTAT );
	RS_printf(" \n");

#endif
}

IpcuTest *ipcu_test_new()
{
	IpcuTest *self = g_object_new(IPCU_TYPE_TEST, NULL);
	return self;
}
