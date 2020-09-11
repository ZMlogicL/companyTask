/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
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
#if 0
#include "_relc.h"
#endif
#include "relctest.h"


K_TYPE_DEFINE_WITH_PRIVATE(RelcTest, relc_test)
#define RELC_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), RelcTestPrivate, RELC_TYPE_TEST))


struct _RelcTestPrivate
{
	int a;
};


/*DECLS*/


/*IMPL*/
static void relc_test_constructor(RelcTest *self)
{
	RelcTestPrivate *priv = RELC_TEST_GET_PRIVATE(self);
}

static void relc_test_destructor(RelcTest *self)
{
	RelcTestPrivate *priv = RELC_TEST_GET_PRIVATE(self);
}


/*PUBLIC*/
void relc_test(RelcTest *self)
{
	RS_printf("RELC\n");

#if 0
	RS_printf("IO_RELC.RELC_RESET     = %x\n", (unsigned int)&ioRelc.relcReset);
	RS_printf("IO_RELC.RELC_MODE1     = %x\n", (unsigned int)&ioRelc.relcMode1);
	RS_printf("IO_RELC.RELC_MODE2     = %x\n", (unsigned int)&ioRelc.relcMode2);
	RS_printf("IO_RELC.RELC_INT_EN    = %x\n", (unsigned int)&ioRelc.relcIntEn);
	RS_printf("IO_RELC.RELC_INT_ST    = %x\n", (unsigned int)&ioRelc.relcIntSt);
	RS_printf("IO_RELC.RELC_STATUS    = %x\n", (unsigned int)&ioRelc.relcStatus);
	RS_printf("IO_RELC.RELC_IN_START_ADDR   = %x\n", (unsigned int)&ioRelc.relcInStartAddr);
	RS_printf("IO_RELC.RELC_IN_END_ADDR     = %x\n", (unsigned int)&ioRelc.relcInEndAddr);
	RS_printf("IO_RELC.RELC_OUT_START_ADDR  = %x\n", (unsigned int)&ioRelc.relcOutStartAddr);
	RS_printf("IO_RELC.RELC_OUT_END_ADDR    = %x\n", (unsigned int)&ioRelc.relcOutEndAddr);
	RS_printf("IO_RELC.RELC_DESCRIPTOR_ADDR = %x\n", (unsigned int)&ioRelc.relcDescriptorAddr);
	RS_printf("IO_RELC.RELC_SEQ_NUM     = %x\n", (unsigned int)&ioRelc.relcSeqNum);
	RS_printf("IO_RELC.RELC_SEQ_CNT     = %x\n", (unsigned int)&ioRelc.relcSeqCnt);
	RS_printf("IO_RELC.RELC_BUF_SIZE    = %x\n", (unsigned int)&ioRelc.relcBufSize);
	RS_printf("IO_RELC.RELC_ERROR_NUM   = %x\n", (unsigned int)&ioRelc.relcErrorNum);
	RS_printf("IO_RELC.RELC_READ_BYTE   = %x\n", (unsigned int)&ioRelc.relcReadByte);
	RS_printf("IO_RELC.RELC_WRITE_BYTE  = %x\n", (unsigned int)&ioRelc.relcWriteByte);
	RS_printf("IO_RELC.RELC_BLOCK       = %x\n", (unsigned int)&ioRelc.relcBlock);
	RS_printf("IO_RELC.RELC_INPUT_BYTE  = %x\n", (unsigned int)&ioRelc.relcInputByte);
	RS_printf("IO_RELC.RELC_OUTPUT_BYTE = %x\n", (unsigned int)&ioRelc.relcOutputByte);
	RS_printf("IO_RELC.RELC_INPUT_BUF_DATA_MIRROR = %x\n", (unsigned int)&ioRelc.relcInputBufDataMirror);
	RS_printf("IO_RELC.RELC_INPUT_BUF_DATA  = %x\n", (unsigned int)&ioRelc.relcInputBufData);
	RS_printf("IO_RELC.RELC_REF_BUF_DATA    = %x\n", (unsigned int)&ioRelc.relcRefBufData);
	RS_printf(" \n");
#endif

}

RelcTest* relc_test_new(void)
{
	RelcTest* self = k_object_new_with_private(RELC_TYPE_TEST, sizeof(RelcTestPrivate));

	return self;
}

