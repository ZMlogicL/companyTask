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
#include "internals.h"
#include "protest1.h"
#include "protest2.h"
#include "protest3.h"
#include "protest4.h"
#include "protest5.h"
#include "protest6.h"
#include "protest7.h"
#include "protest8.h"
#include "nictest.h"
#include "pdmtest.h"
#include "ptimertest.h"
#include "relctest.h"
#include "scutest.h"
#include "sdramctest.h"
#include "kiotest.h"


/*************************************************************************/
//#define		D_ENABLE_IO_PRO_SEN
//#define		D_ENABLE_IO_PRO_SRO_PIPE_1
//#define		D_ENABLE_IO_PRO_SRO_PIPE_2
//#define		D_ENABLE_IO_PRO_SRO_PIPE_3
//#define		D_ENABLE_IO_PRO_B2B_PIPE_1
//#define		D_ENABLE_IO_PRO_B2B_PIPE_2
//#define		D_ENABLE_IO_PRO_B2B_PIPE_3
//#define		D_ENABLE_IO_PRO_STAT
//#define		D_ENABLE_IO_PRO_PAS
//#define		D_ENABLE_IO_PRO_TABLE

void pro_test( EProBlockType type )
{
#if 0	// for PC debug
#define IO_PRO		(*IO_PRO2)
	volatile struct io_pro*			IO_PRO2		= (void*)0x28008000;
#endif	// for PC debug

#ifdef D_ENABLE_IO_PRO_TABLE	// for PC debug
#define IO_PRO_TBL	(*IO_PRO2_TBL)
	volatile struct io_pro_tbl*		IO_PRO2_TBL	= (void*)0x29000000;
#endif	// for PC debug

	RS_printf("Pro\n");
	pro_test1(NULL, type, IO_PRO);
	pro_test2(NULL, type, IO_PRO);
	pro_test3(NULL, type, IO_PRO);
	pro_test4(NULL, type, IO_PRO);
	pro_test5(NULL, type, IO_PRO);
	pro_test6(NULL, type, IO_PRO);
	pro_test7(NULL, type, IO_PRO);
	pro_test8(NULL, type, IO_PRO);

#if 0

	k_io_test_pas_table_test(NULL, type, IO_PRO, IO_PRO_TBL)
	RS_printf(" \n");

#endif
}

