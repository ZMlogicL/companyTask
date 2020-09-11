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
#include "sdramctest.h"


K_TYPE_DEFINE_WITH_PRIVATE(SdramcTest, sdramc_test)
#define SDRAMC_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), SdramcTestPrivate, SDRAMC_TYPE_TEST))


struct _SdramcTestPrivate
{
	int a;
};


/*DECLS*/


/*IMPL*/
static void sdramc_test_constructor(SdramcTest *self)
{
	SdramcTestPrivate *priv = SDRAMC_TEST_GET_PRIVATE(self);
}

static void sdramc_test_destructor(SdramcTest *self)
{
	SdramcTestPrivate *priv = SDRAMC_TEST_GET_PRIVATE(self);
}


/*PUBLIC*/
void sdramc_test(SdramcTest *self)
{
	RS_printf("SDRAMC\n");

#if 0

	int i;

	for( i = 0; i < 2; i++ ) {
		RS_printf("IO_SDRAMC[%d].EMBNUM         = %x\n", i, (unsigned int)&ioSdramc[i].embnum);
		RS_printf("IO_SDRAMC[%d].REMAPADDR      = %x\n", i, (unsigned int)&ioSdramc[i].remapaddr);
		RS_printf("IO_SDRAMC[%d].CHSEL          = %x\n", i, (unsigned int)&ioSdramc[i].chsel);
		RS_printf("IO_SDRAMC[%d].RATECONT       = %x\n", i, (unsigned int)&ioSdramc[i].ratecont);
		RS_printf("IO_SDRAMC[%d].MASTEROPTION   = %x\n", i, (unsigned int)&ioSdramc[i].masteroption);
		RS_printf("IO_SDRAMC[%d].PRIORIT_CAT    = %x\n", i, (unsigned int)&ioSdramc[i].prioritCat);
		RS_printf("IO_SDRAMC[%d].RATE_CHANGE    = %x\n", i, (unsigned int)&ioSdramc[i].rateChange);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLA     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctla);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLB     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctlb);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLC     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctlc);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLD     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctld);
		RS_printf("IO_SDRAMC[%d].UMCINITCTLA    = %x\n", i, (unsigned int)&ioSdramc[i].umcinitctla);
		RS_printf("IO_SDRAMC[%d].UMCINITCTLB    = %x\n", i, (unsigned int)&ioSdramc[i].umcinitctlb);
		RS_printf("IO_SDRAMC[%d].UMCINITCTLC    = %x\n", i, (unsigned int)&ioSdramc[i].umcinitctlc);
		RS_printf("IO_SDRAMC[%d].UMCDRMMRA      = %x\n", i, (unsigned int)&ioSdramc[i].umcdrmmra);
		RS_printf("IO_SDRAMC[%d].UMCINITSET     = %x\n", i, (unsigned int)&ioSdramc[i].umcinitset);
		RS_printf("IO_SDRAMC[%d].UMCINITSTAT    = %x\n", i, (unsigned int)&ioSdramc[i].umcinitstat);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLE     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctle);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLF     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctlf);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLG     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctlg);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLH     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctlh);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLI     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctli);
		RS_printf("IO_SDRAMC[%d].UMCCMDCTLJ     = %x\n", i, (unsigned int)&ioSdramc[i].umccmdctlj);
		RS_printf("IO_SDRAMC[%d].UMCSPCSETA     = %x\n", i, (unsigned int)&ioSdramc[i].umcspcseta);
		RS_printf("IO_SDRAMC[%d].UMCSPCSETB     = %x\n", i, (unsigned int)&ioSdramc[i].umcspcsetb);
		RS_printf("IO_SDRAMC[%d].UMCSPCSTAT     = %x\n", i, (unsigned int)&ioSdramc[i].umcspcstat);
		RS_printf("IO_SDRAMC[%d].UMCMEMCONF0A   = %x\n", i, (unsigned int)&ioSdramc[i].umcmemconf0a);
		RS_printf("IO_SDRAMC[%d].UMCMEMCONF0B   = %x\n", i, (unsigned int)&ioSdramc[i].umcmemconf0b);
		RS_printf("IO_SDRAMC[%d].UMCMEMCONF1A   = %x\n", i, (unsigned int)&ioSdramc[i].umcmemconf1a);
		RS_printf("IO_SDRAMC[%d].UMCMEMCONF1B   = %x\n", i, (unsigned int)&ioSdramc[i].umcmemconf1b);
		RS_printf("IO_SDRAMC[%d].UMCMEMCONFCH   = %x\n", i, (unsigned int)&ioSdramc[i].umcmemconfch);
		RS_printf("IO_SDRAMC[%d].UMCMEMMAPSET   = %x\n", i, (unsigned int)&ioSdramc[i].umcmemmapset);
		RS_printf("IO_SDRAMC[%d].UMCACCCHKA     = %x\n", i, (unsigned int)&ioSdramc[i].umcaccchka);
		RS_printf("IO_SDRAMC[%d].UMCACCARSAA    = %x\n", i, (unsigned int)&ioSdramc[i].umcaccarsaa);
		RS_printf("IO_SDRAMC[%d].UMCACCAREAA    = %x\n", i, (unsigned int)&ioSdramc[i].umcaccareaa);
		RS_printf("IO_SDRAMC[%d].UMCWACCMSTA    = %x\n", i, (unsigned int)&ioSdramc[i].umcwaccmsta);
		RS_printf("IO_SDRAMC[%d].UMCRACCMSTA    = %x\n", i, (unsigned int)&ioSdramc[i].umcraccmsta);
		RS_printf("IO_SDRAMC[%d].UMCACCCHKB     = %x\n", i, (unsigned int)&ioSdramc[i].umcaccchkb);
		RS_printf("IO_SDRAMC[%d].UMCACCARSAB    = %x\n", i, (unsigned int)&ioSdramc[i].umcaccarsab);
		RS_printf("IO_SDRAMC[%d].UMCACCAREAB    = %x\n", i, (unsigned int)&ioSdramc[i].umcaccareab);
		RS_printf("IO_SDRAMC[%d].UMCWACCMSTB    = %x\n", i, (unsigned int)&ioSdramc[i].umcwaccmstb);
		RS_printf("IO_SDRAMC[%d].UMCRACCMSTB    = %x\n", i, (unsigned int)&ioSdramc[i].umcraccmstb);
		RS_printf("IO_SDRAMC[%d].UMCOODCHK      = %x\n", i, (unsigned int)&ioSdramc[i].umcoodchk);
		RS_printf("IO_SDRAMC[%d].UMCMRACS       = %x\n", i, (unsigned int)&ioSdramc[i].umcmracs);
		RS_printf("IO_SDRAMC[%d].UMCMRACSST     = %x\n", i, (unsigned int)&ioSdramc[i].umcmracsst);
		RS_printf("IO_SDRAMC[%d].UMCMRWDT       = %x\n", i, (unsigned int)&ioSdramc[i].umcmrwdt);
		RS_printf("IO_SDRAMC[%d].UMCMRRDT       = %x\n", i, (unsigned int)&ioSdramc[i].umcmrrdt);
		RS_printf("IO_SDRAMC[%d].UMCRDATACTL_D0 = %x\n", i, (unsigned int)&ioSdramc[i].umcrdatactlD0);
		RS_printf("IO_SDRAMC[%d].UMCWDATACTL_D0 = %x\n", i, (unsigned int)&ioSdramc[i].umcwdatactlD0);
		RS_printf("IO_SDRAMC[%d].UMCRDATACTL_D1 = %x\n", i, (unsigned int)&ioSdramc[i].umcrdatactlD1);
		RS_printf("IO_SDRAMC[%d].UMCWDATACTL_D1 = %x\n", i, (unsigned int)&ioSdramc[i].umcwdatactlD1);
		RS_printf("IO_SDRAMC[%d].UMCDATASET     = %x\n", i, (unsigned int)&ioSdramc[i].umcdataset);
		RS_printf("IO_SDRAMC[%d].UMCWDATASWP    = %x\n", i, (unsigned int)&ioSdramc[i].umcwdataswp);
		RS_printf("IO_SDRAMC[%d].UMCINTCAUSEM0  = %x\n", i, (unsigned int)&ioSdramc[i].umcintcausem0);
		RS_printf("IO_SDRAMC[%d].UMCINTMASKM0   = %x\n", i, (unsigned int)&ioSdramc[i].umcintmaskm0);
		RS_printf("IO_SDRAMC[%d].ACCCHKFLG      = %x\n", i, (unsigned int)&ioSdramc[i].accchkflg);
		RS_printf("IO_SDRAMC[%d].ACCCHKFLGCLR   = %x\n", i, (unsigned int)&ioSdramc[i].accchkflgclr);
		RS_printf("IO_SDRAMC[%d].ACCCHKLOGA     = %x\n", i, (unsigned int)&ioSdramc[i].accchkloga);
		RS_printf("IO_SDRAMC[%d].ACCCHKLOGB     = %x\n", i, (unsigned int)&ioSdramc[i].accchklogb);
		RS_printf("IO_SDRAMC[%d].UMCPHYCTLA     = %x\n", i, (unsigned int)&ioSdramc[i].umcphyctla);
		RS_printf("IO_SDRAMC[%d].UMCPHYCTLB     = %x\n", i, (unsigned int)&ioSdramc[i].umcphyctlb);
		RS_printf("IO_SDRAMC[%d].UMCPHYCTLC     = %x\n", i, (unsigned int)&ioSdramc[i].umcphyctlc);
		RS_printf("IO_SDRAMC[%d].UMCDFICTLA     = %x\n", i, (unsigned int)&ioSdramc[i].umcdfictla);
		RS_printf("IO_SDRAMC[%d].UMCPFMCTL      = %x\n", i, (unsigned int)&ioSdramc[i].umcpfmctl);
		RS_printf("IO_SDRAMC[%d].UMCPFMST       = %x\n", i, (unsigned int)&ioSdramc[i].umcpfmst);
		RS_printf("IO_SDRAMC[%d].UMCMIDPFMCTL   = %x\n", i, (unsigned int)&ioSdramc[i].umcmidpfmctl);
		RS_printf("IO_SDRAMC[%d].UMCMIDPFMST    = %x\n", i, (unsigned int)&ioSdramc[i].umcmidpfmst);
		RS_printf("IO_SDRAMC[%d].CLKENBIFA      = %x\n", i, (unsigned int)&ioSdramc[i].clkenbifa);
		RS_printf("IO_SDRAMC[%d].CLKENBIFB      = %x\n", i, (unsigned int)&ioSdramc[i].clkenbifb);
		RS_printf("IO_SDRAMC[%d].CLKENBIFC      = %x\n", i, (unsigned int)&ioSdramc[i].clkenbifc);
		RS_printf("IO_SDRAMC[%d].CLKENDA        = %x\n", i, (unsigned int)&ioSdramc[i].clkenda);
		RS_printf("IO_SDRAMC[%d].CLKENMON       = %x\n", i, (unsigned int)&ioSdramc[i].clkenmon);
		RS_printf("IO_SDRAMC[%d].IRQEN          = %x\n", i, (unsigned int)&ioSdramc[i].irqen);
		RS_printf("IO_SDRAMC[%d].IRQCLR         = %x\n", i, (unsigned int)&ioSdramc[i].irqclr);

		RS_printf(" \n");

	}

#endif

}

SdramcTest* sdramc_test_new(void)
{
	SdramcTest* self = k_object_new_with_private(SDRAMC_TYPE_TEST, sizeof(SdramcTestPrivate));

	return self;
}
