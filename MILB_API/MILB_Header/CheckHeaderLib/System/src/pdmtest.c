/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
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
#include "pdmtest.h"


K_TYPE_DEFINE_WITH_PRIVATE(PdmTest, pdm_test)
#define PDM_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), PdmTestPrivate, PDM_TYPE_TEST))


struct _PdmTestPrivate
{

};


/*DECLS*/


/*IMPL*/
static void pdm_test_constructor(PdmTest *self)
{
	PdmTestPrivate *priv = PDM_TEST_GET_PRIVATE(self);
}

static void pdm_test_destructor(PdmTest *self)
{
	PdmTestPrivate *priv = PDM_TEST_GET_PRIVATE(self);
}


/*PUBLIC*/
void pdm_test(PdmTest *self)
{
#if 0
	volatile IoPdm*		ioPdm;
	ioPdm = (void*)0x1E004000;
#endif

	RS_printf("PDM\n");

#if 0
	int loop;

	for (loop = 0; loop < 2; loop++){
		RS_printf("IO_PDM[%d].CORE_CFG       = %lx\n", loop, (unsigned long)&ioPdm[loop].coreCfg);
		RS_printf("IO_PDM[%d].DMA_CFG        = %lx\n", loop, (unsigned long)&ioPdm[loop].dmaCfg);
		RS_printf("IO_PDM[%d].DMA_LEN        = %lx\n", loop, (unsigned long)&ioPdm[loop].dmaLen);
		RS_printf("IO_PDM[%d].DMA0_DST_ADDR  = %lx\n", loop, (unsigned long)&ioPdm[loop].dma0DstAddr);
		RS_printf("IO_PDM[%d].DMA1_DST_ADDR  = %lx\n", loop, (unsigned long)&ioPdm[loop].dma1DstAddr);
		RS_printf("IO_PDM[%d].STATUS         = %lx\n", loop, (unsigned long)&ioPdm[loop].status);
		RS_printf(" \n");
	}
#endif
}

PdmTest* pdm_test_new(void)
{
	PdmTest* self = k_object_new_with_private(PDM_TYPE_TEST, sizeof(PdmTestPrivate));

	return self;
}
