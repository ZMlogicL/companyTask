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
#include "nictest.h"


K_TYPE_DEFINE_WITH_PRIVATE(NicTest, nic_test)
#define NIC_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), NicTestPrivate, NIC_TYPE_TEST))


struct _NicTestPrivate
{

};

/*DECLS*/


/*IMPL*/
static void nic_test_constructor(NicTest *self)
{
	NicTestPrivate *priv = NIC_TEST_GET_PRIVATE(self);
}

static void nic_test_destructor(NicTest *self)
{
	NicTestPrivate *priv = NIC_TEST_GET_PRIVATE(self);
}


/*PUBLIC*/
void nic_test(NicTest *self)
{
	RS_printf("NIC\n");
#if 0
	RS_printf("IO_NIC_ADDRCTRL\n");
	RS_printf("IO_NIC_ADDRCTRL              = %p\n", &ioNicAddrctrl);
	RS_printf("Reserved                     = %p\n", &ioNicAddrctrl.dmy0000000b);
	RS_printf("IO_NIC_ADDRCTRL.SECURITY1    = %p\n", &ioNicAddrctrl.security1);
	RS_printf("Reserved                     = %p\n", &ioNicAddrctrl.dmy00100fff);
	RS_printf(" \n");

	RS_printf("IO_NIC_ASIB\n");
	RS_printf("IO_NIC_ASIB[0]               = %p\n", &ioNicAsib[0]);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[0].dmy2000203f);
	RS_printf("IO_NIC_ASIB[0].WR_TIDEMARK   = %p\n", &ioNicAsib[0].wrTidemark);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[0].dmy204420ff);
	RS_printf("IO_NIC_ASIB[0].READ_QOS      = %p\n", &ioNicAsib[0].readQos);
	RS_printf("IO_NIC_ASIB[0].WRITE_QOS     = %p\n", &ioNicAsib[0].writeQos);
	RS_printf("IO_NIC_ASIB[0].FN_MOD        = %p\n", &ioNicAsib[0].fnMod);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[0].dmy210c2fff);

	RS_printf("IO_NIC_ASIB[1]               = %p\n", &ioNicAsib[1]);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[1].dmy2000203f);
	RS_printf("IO_NIC_ASIB[1].WR_TIDEMARK   = %p\n", &ioNicAsib[1].wrTidemark);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[1].dmy204420ff);
	RS_printf("IO_NIC_ASIB[1].READ_QOS      = %p\n", &ioNicAsib[1].readQos);
	RS_printf("IO_NIC_ASIB[1].WRITE_QOS     = %p\n", &ioNicAsib[1].writeQos);
	RS_printf("IO_NIC_ASIB[1].FN_MOD        = %p\n", &ioNicAsib[1].fnMod);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[1].dmy210c2fff);

	RS_printf("IO_NIC_ASIB[2]               = %p\n", &ioNicAsib[2]);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[2].dmy2000203f);
	RS_printf("IO_NIC_ASIB[2].WR_TIDEMARK   = %p\n", &ioNicAsib[2].wrTidemark);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[2].dmy204420ff);
	RS_printf("IO_NIC_ASIB[2].READ_QOS      = %p\n", &ioNicAsib[2].readQos);
	RS_printf("IO_NIC_ASIB[2].WRITE_QOS     = %p\n", &ioNicAsib[2].writeQos);
	RS_printf("IO_NIC_ASIB[2].FN_MOD        = %p\n", &ioNicAsib[2].fnMod);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[2].dmy210c2fff);

	RS_printf("IO_NIC_ASIB[3]               = %p\n", &ioNicAsib[3]);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[3].dmy2000203f);
	RS_printf("IO_NIC_ASIB[3].WR_TIDEMARK   = %p\n", &ioNicAsib[3].wrTidemark);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[3].dmy204420ff);
	RS_printf("IO_NIC_ASIB[3].READ_QOS      = %p\n", &ioNicAsib[3].readQos);
	RS_printf("IO_NIC_ASIB[3].WRITE_QOS     = %p\n", &ioNicAsib[3].writeQos);
	RS_printf("IO_NIC_ASIB[3].FN_MOD        = %p\n", &ioNicAsib[3].fnMod);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[3].dmy210c2fff);

	RS_printf("IO_NIC_ASIB[4]               = %p\n", &ioNicAsib[4]);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[4].dmy2000203f);
	RS_printf("IO_NIC_ASIB[4].WR_TIDEMARK   = %p\n", &ioNicAsib[4].wrTidemark);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[4].dmy204420ff);
	RS_printf("IO_NIC_ASIB[4].READ_QOS      = %p\n", &ioNicAsib[4].readQos);
	RS_printf("IO_NIC_ASIB[4].WRITE_QOS     = %p\n", &ioNicAsib[4].writeQos);
	RS_printf("IO_NIC_ASIB[4].FN_MOD        = %p\n", &ioNicAsib[4].fnMod);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[4].dmy210c2fff);

	RS_printf("IO_NIC_ASIB[5]               = %p\n", &ioNicAsib[5]);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[5].dmy2000203f);
	RS_printf("IO_NIC_ASIB[5].WR_TIDEMARK   = %p\n", &ioNicAsib[5].wrTidemark);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[5].dmy204420ff);
	RS_printf("IO_NIC_ASIB[5].READ_QOS      = %p\n", &ioNicAsib[5].readQos);
	RS_printf("IO_NIC_ASIB[5].WRITE_QOS     = %p\n", &ioNicAsib[5].writeQos);
	RS_printf("IO_NIC_ASIB[5].FN_MOD        = %p\n", &ioNicAsib[5].fnMod);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[5].dmy210c2fff);

	RS_printf("IO_NIC_ASIB[6]               = %p\n", &ioNicAsib[6]);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[6].dmy2000203f);
	RS_printf("IO_NIC_ASIB[6].WR_TIDEMARK   = %p\n", &ioNicAsib[6].wrTidemark);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[6].dmy204420ff);
	RS_printf("IO_NIC_ASIB[6].READ_QOS      = %p\n", &ioNicAsib[6].readQos);
	RS_printf("IO_NIC_ASIB[6].WRITE_QOS     = %p\n", &ioNicAsib[6].writeQos);
	RS_printf("IO_NIC_ASIB[6].FN_MOD        = %p\n", &ioNicAsib[6].fnMod);
	RS_printf("Reserved                     = %p\n", &ioNicAsib[6].dmy210c2fff);
	RS_printf(" \n");
#endif
}

NicTest* nic_test_new(void)
{
	NicTest* self = k_object_new_with_private(NIC_TYPE_TEST, sizeof(NicTestPrivate));

	return self;
}
