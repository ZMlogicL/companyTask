/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdRelcJugde类
*@rely                :klib
*@function
*1.0.0 2020年09月开始开发
*设计的主要功能:
*1、
*@version
*
*/

#include <stdlib.h>
#include <string.h>
#include "_relc.h"
#include "dd_relc.h"
#include "exstop.h"
#include "chiptop.h"
#include "dd_exs.h"
#include "ctddrelc.h"
#include "ctddrelcmain.h"
#include "ctddrelcjugde.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdRelcJugde, ct_dd_relc_jugde);
#define CT_DD_RELC_JUGDE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdRelcJugdePrivate,CT_TYPE_DD_RELC_JUGDE))

struct _CtDdRelcJugdePrivate
{
	CtDdRelcMain *cdrm;
};

static kulong S_GRELC_DESC_TABLE1[] =
{
	0x00000000, 0x58100000, 0x00000000, 0x58200000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,

	0x00000000, 0x58300000, 0x00000000, 0x58400000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,

	0x00000000, 0x58500000, 0x00000000, 0x58600000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,

	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000
};

/* Working buffer */
#ifdef PC_DEBUG
static volatile kulong S_BUF[ 2048 ];
#endif

/*
 *DECLS
 */
#ifdef PC_DEBUG
static void putDump(kulong *buffer, kulong ofs, kulong adr, kushort cnt);
#endif 

static void ct_dd_relc_jugde_constructor(CtDdRelcJugde *self) 
{
    self->ret = D_DD_RELC_OK;
    self->setSize = 0;
    self->refBufSize = 0;
}

static void ct_dd_relc_jugde_destructor(CtDdRelcJugde *self) 
{
	self->endstr = NULL;
    self->hprot = NULL;
}

/*
 *IMPL
 */
#ifdef PC_DEBUG
static void putDump(kulong *buffer, kulong ofs, kulong adr, kushort cnt)
{
	unsigned kshort n;

	Ddim_Print(("\r\n%08lX  %08lX ", ofs, adr));

	for ( n = 0 ; n < cnt ; n++ ) {
		Ddim_Print((" %08lX", S_BUF[n]));
	}
}
#endif

/*
 *PUBLIC
 */
void ct_dd_relc_buffer_dump(void)
{
#ifdef PC_DEBUG
	ks64 *ptr;
	kulong addr;
	kulong ofs;
	kulong adr;

	// RELC Input data Buffer Mirror [2k byte] Base Address + 1000h
	addr = 0x3A001000;
	memcpy( (kulong*)S_BUF, (kpointer)IO_RELC.RELC_INPUT_BUF_DATA_MIRROR, 8192 );

	Ddim_Print(("\n RELC Input data Buffer Mirror [2k byte] Base Address + 1000h"));
	Ddim_Print(("\n OFFSET    ADDRESS   0 1 2 3   4 5 6 7   8 9 A B   C D E F  "));
	Ddim_Print(("\n ---------+---------+---------+---------+---------+---------+"));

	for ( ptr = (ks64*)S_BUF, ofs = 0, adr = addr ; adr < addr + 0x800 ; ptr+=16, ofs+=16, adr+=16 ) {
		putDump( (kulong*)ptr, ofs, adr, 4 );
	}

	/*
	 * RELC Input data Buffer
	 * [2k byte] Base Address + 1800h
	 */
	addr = 0x3A001800;
	memcpy( (kulong*)S_BUF, (kpointer)IO_RELC.RELC_INPUT_BUF_DATA, 8192 );

	Ddim_Print(("\n RELC Input data Buffer        [2k byte] Base Address + 1800h"));
	Ddim_Print(("\n OFFSET    ADDRESS   0 1 2 3   4 5 6 7   8 9 A B   C D E F  "));
	Ddim_Print(("\n ---------+---------+---------+---------+---------+---------+"));

	for ( ptr = (ks64*)S_BUF, ofs = 0, adr = addr ; adr < addr + 0x800 ; ptr+=16, ofs+=16, adr+=16 ) {
		putDump((kulong*)ptr, ofs, adr, 4);
	}

	/*
	 * RELC Reference Data Buffer
	 * [8k byte] Base Address + 2000h
	 */
	addr = 0x3A002000;
	memcpy( (kulong*)S_BUF, (kpointer)IO_RELC.RELC_REF_BUF_DATA, 8192 );

	Ddim_Print(("\n RELC Reference Data Buffer    [8k byte] Base Address + 2000h"));
	Ddim_Print(("\n OFFSET    ADDRESS   0 1 2 3   4 5 6 7   8 9 A B   C D E F  "));
	Ddim_Print(("\n ---------+---------+---------+---------+---------+---------+"));

	for ( ptr = (ks64*)S_BUF, ofs = 0, adr = addr ; adr < addr + 0x2000 ; ptr+=16, ofs+=16, adr+=16 ) {
		putDump( (kulong*)ptr, ofs, adr, 4 );
	}
#endif
}

void ct_dd_relc_help(void)
{
	Ddim_Print(("--- RELC --- (This command help for real machine test)\n"));
	Ddim_Print(("USAGE>relc init writeHprot readHprot\n"));
	Ddim_Print(("                    # Initialize RELC macro.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc open\n"));
	Ddim_Print(("                    # Open RELC macro.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc close\n"));
	Ddim_Print(("                    # Close RELC macro.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc start [sync/async]\n"));
	Ddim_Print(("                    # Start RELC macro.\n"));
	Ddim_Print(("                    #   [sync/async] sync : Synchronization of RELC macro start\n"));
	Ddim_Print(("                    #                async: Asynchronous of RELC macro start\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc stop\n"));
	Ddim_Print(("                    # Stop RELC macro.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc ctrlcomm [reg/desc] [nmod/cmod] [seq_num]\n"));
	Ddim_Print(("                    # Set control common data.\n"));
	Ddim_Print(("                    #   [reg/des]          reg  : register \n"));
	Ddim_Print(("                    #                      desc : Output disable\n"));
	Ddim_Print(("                    #   [nmod/cmod]        nmod : Normal mode\n"));
	Ddim_Print(("                    #                      smod : Continuous mode\n"));
	Ddim_Print(("                    #   [seq_num]          Sequential run number of times\n"));
	Ddim_Print(("                    #                      When 0 or 1 is specified, a value is 1.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc ctrlreg [imaxd/imaxe] [omaxd/omaxe] [in_sta_addr] [in_end_addr] [out_sta_addr] [out_end_addr]\n"));
	Ddim_Print(("                    # Set control register data.\n"));
	Ddim_Print(("                    #   [imaxd/imaxe]      imaxd : Input end address disable\n"));
	Ddim_Print(("                    #                      imaxe : Input end address enable\n"));
	Ddim_Print(("                    #   [omaxd/omaxe]      omaxd : Output end address disable\n"));
	Ddim_Print(("                    #                      omaxe : Output end address enable\n"));
	Ddim_Print(("                    #   [in_sta_addr]      Input start address\n"));
	Ddim_Print(("                    #   [out_sta_addr]     Output start address\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc ctrldesc [desc_addr]\n"));
	Ddim_Print(("                    # Set control descriptor data.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc set in_sta_addr [in_sta_addr]\n"));
	Ddim_Print(("                    # Set control input start address.\n"));
	Ddim_Print(("                    #   [in_sta_addr]       Input start address\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc set in_end_addr [in_end_addr]\n"));
	Ddim_Print(("                    # Set control input end address.\n"));
	Ddim_Print(("                    #   [in_end_addr]       Input end address\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc set out_sta_addr [out_sta_addr]\n"));
	Ddim_Print(("                    # Set control output start address.\n"));
	Ddim_Print(("                    #   [out_sta_addr]      Output start address\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc set out_end_addr [out_end_addr]\n"));
	Ddim_Print(("                    # Set control output end address.\n"));
	Ddim_Print(("                    #   [out_end_addr]      Output end address\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get ctrlcomm\n"));
	Ddim_Print(("                    # Get control common data.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get ctrlreg\n"));
	Ddim_Print(("                    # Get control register data.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get ctrldesc\n"));
	Ddim_Print(("                    # Get control descriptor data.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get msta\n"));
	Ddim_Print(("                    # Get RELC macro statusa.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get sleep\n"));
	Ddim_Print(("                    # Get RELC sleep status.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get errsta\n"));
	Ddim_Print(("                    # Get RELC error status.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get err\n"));
	Ddim_Print(("                    # Get RELC error number.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get psta\n"));
	Ddim_Print(("                    # Get RELC process status.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get bufsiz\n"));
	Ddim_Print(("                    # Get RELC buffer size.\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc set [inbuf/inbufm/refbuf] [in_addr] [in_size] [out_addr\n"));
	Ddim_Print(("                    # Set data to RELC buffer .\n"));
	Ddim_Print(("                    #   [inbuf/inbufm/refbuf]  inbuf  : input data buffer\n"));
	Ddim_Print(("                    #                          inbufm : input data buffer(mirror erea)\n"));
	Ddim_Print(("                    #                          refbuf : reference data buffer\n"));
	Ddim_Print(("                    #   [in_addr]              input data address on RAM\n"));
	Ddim_Print(("                    #   [in_size]              input data size on RAM\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc get [inbuf/inbufm/refbuf] [out_addr] [out_size]\n"));
	Ddim_Print(("                    # Get data from RELC buffer .\n"));
	Ddim_Print(("                    #   [inbuf/inbufm/refbuf]  inbuf  : input data buffer\n"));
	Ddim_Print(("                    #                          inbufm : input data buffer(mirror erea)\n"));
	Ddim_Print(("                    #                          refbuf : reference data buffer\n"));
	Ddim_Print(("                    #   [out_addr]             outputdata address from input data buffer to SDRAM\n"));
	Ddim_Print(("                    #   [out_size]             output data size\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc norm async [testNum]\n"));
	Ddim_Print(("                    # Set and Start RELC normal mode.(Async type)\n"));
	Ddim_Print(("                    #   [testNum]             test pattern number\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc desc async [testNum]\n"));
	Ddim_Print(("                    # Set and Start RELC descriptor mode.(Async type)\n"));
	Ddim_Print(("                    #   [testNum]            test pattern number\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc norm sync [testNum]\n"));
	Ddim_Print(("                    # Set and Start RELC normal mode.(Sync type)\n"));
	Ddim_Print(("                    #   [testNum]             test pattern number\n"));
	Ddim_Print(("\n"));
	Ddim_Print(("USAGE>relc desc sync [testNum]\n"));
	Ddim_Print(("                    # Set and Start RELC descriptor mode.(Sync type)\n"));
	Ddim_Print(("                    #   [testNum]            test pattern number\n"));
	Ddim_Print(("\n"));
}

/**
 * @brief  Command main function for RELC test.
 * @param  kint32 argc	:The number of parameters
 *		   CGAR** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| P1            | P2               | P3            | P4            | P5            | P6            | P7            | Meaning                                     |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| init          | writeHprot      | readHprot    |               |               |               |               | Initialize RELC macro.                      |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Init                              |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| open          |                  |               |               |               |               |               | Open RELC macro.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Open                              |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| close         |                  |               |               |               |               |               | Close RELC macro.                           |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Close                             |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| start         | sync             |               |               |               |               |               | Start RELC macro.                           |
 *	|               | async            |               |               |               |               |               |  sync : Synchronization of RELC macro start |
 *	|               |                  |               |               |               |               |               |  async: Asynchronous of RELC macro start    |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Start_Sync                        |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Start_Async                       |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| stop          |                  |               |               |               |               |               | Stop RELC macro.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Stop                              |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| ctrlcomm      | reg              | nmod          | seq_num       |               |               |               | Set control common data.                    |
 *	|               | desc             | cmod          |               |               |               |               |  reg  : register                            |
 *	|               |                  |               |               |               |               |               |  desc : Output disable                      |
 *	|               |                  |               |               |               |               |               |  nmod : Normal mode                         |
 *	|               |                  |               |               |               |               |               |  smod : Continuous mode                     |
 *	|               |                  |               |               |               |               |               |  seq_num : Sequential run number of times   |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Common                       |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| ctrlreg       | imaxd            | omaxd         | in_sta_addr   | in_end_addr   | out_sta_addr  | out_end_addr  | Set control register data.                  |
 *	|               | imaxe            | omaxe         |               |               |               |               |  imaxd : Input end address disable          |
 *	|               |                  |               |               |               |               |               |  imaxe : Input end address enable           |
 *	|               |                  |               |               |               |               |               |  omaxd : Output end address disable         |
 *	|               |                  |               |               |               |               |               |  omaxe : Output end address enable          |
 *	|               |                  |               |               |               |               |               |  Input start address                        |
 *	|               |                  |               |               |               |               |               |  Input end address                          |
 *	|               |                  |               |               |               |               |               |  Output start address                       |
 *	|               |                  |               |               |               |               |               |  Output end address                         |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Register                     |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| ctrldesc      | desc_addr        |               |               |               |               |               | Set control descriptor data.                |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Descriptor                   |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| set           | in_sta_addr      | in_sta_addr   |               |               |               |               | Set control input start address.            |
 *	|               |                  |               |               |               |               |               |  in_sta_addr : Input start address          |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_In_Start_Addr                 |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| set           | in_end_addr      | in_end_addr   |               |               |               |               | Set control input end address.              |
 *	|               |                  |               |               |               |               |               |  in_end_addr : Input end address            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_In_End_Addr                   |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| set           | out_sta_addr     | out_sta_addr  |               |               |               |               | Set control output start address.           |
 *	|               |                  |               |               |               |               |               |  out_sta_addr : Output start address        |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_Out_Start_Addr                |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| set           | out_end_addr     | out_end_addr  |               |               |               |               | Set control output end address.             |
 *	|               |                  |               |               |               |               |               |  out_end_addr : Output end address          |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_Out_End_Addr                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | ctrlcomm         |               |               |               |               |               | Get control common data.                    |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Common                   |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | ctrlreg          |               |               |               |               |               | Get control register data.                  |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Register                 |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | ctrldesc         |               |               |               |               |               | Get control descriptor data.                |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Descriptor               |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | msta             |               |               |               |               |               | Get RELC macro status.                      |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Status                        |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | sleep            |               |               |               |               |               | Get RELC sleep status.                      |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Sleep_Reason                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | errsta           |               |               |               |               |               | Get RELC error status.                      |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Error_Status                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | err              |               |               |               |               |               | Get RELC error number.                      |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Error                         |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | psta             |               |               |               |               |               | Get RELC process status.                    |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Process_Status                |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | bufsiz           |               |               |               |               |               | Get RELC buffer size.                       |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Buf_Size                      |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| set           | inbuf            | in_addr       | in_size       |               |               |               | Set data to RELC buffer.                    |
 *	|               | inbufm           |               |               |               |               |               |  inbuf  : input data buffer                 |
 *	|               | refbuf           |               |               |               |               |               |  inbufm : input data buffer(mirror erea)    |
 *	|               |                  |               |               |               |               |               |  refbuf : reference data buffer             |
 *	|               |                  |               |               |               |               |               |  in_addr : input data address on RAM        |
 *	|               |                  |               |               |               |               |               |  in_size : input data size on RAM           |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_In_Buf_Data                   |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_In_Buf_Data_Mirror            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_Ref_Buf_Data                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| get           | inbuf            | out_addr      | out_size      |               |               |               | Get data from RELC buffer.                  |
 *	|               | inbufm           |               |               |               |               |               |  inbuf  : input data buffer                 |
 *	|               | refbuf           |               |               |               |               |               |  inbufm : input data buffer(mirror erea)    |
 *	|               |                  |               |               |               |               |               |  refbuf : reference data buffer             |
 *	|               |                  |               |               |               |               |               |  out_addr : outputdata address from         |
 *	|               |                  |               |               |               |               |               |             input data buffer to SDRAM      |
 *	|               |                  |               |               |               |               |               |  out_size : output data size                |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_In_Buf_Data                   |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_In_Buf_Data_Mirror            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ref_Buf_Data                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| norm          | async            | testNum      |               |               |               |               | Set and Start RELC normal mode.             |
 *	|               |                  |               |               |               |               |               |  testNum : test pattern number             |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Utility_Register                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| desc          | async            | testNum      |               |               |               |               | Set and Start RELC descriptor mode.         |
 *	|               |                  |               |               |               |               |               |  testNum : test pattern number             |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Utility_Descriptor                |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| norm          | sync             | testNum      |               |               |               |               | Set and Start RELC normal mode.             |
 *	|               |                  |               |               |               |               |               |  testNum : test pattern number             |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Init                              |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Open                              |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Common                       |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Common                   |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Register                     |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Register                 |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Start_Sync                        |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Status                        |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Process_Status                |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Error_Status                  |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Error                         |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Wait_End                          |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Close                             |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| desc          | sync             | testNum      |               |               |               |               | Set and Start RELC descriptor mode.         |
 *	|               |                  |               |               |               |               |               |  testNum : test pattern number             |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Init                              |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Open                              |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Common                       |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Common                   |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Descriptor                   |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Descriptor               |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Status                        |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Process_Status                |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Error_Status                  |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Error                         |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Start_Sync                        |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Wait_End                          |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Close"                            |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| inthdr        | testNum         |               |               |               |               |               | Interrupt Handler.                          |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Int_Handler                       |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | open             |               |               |               |               |               | Open error.                                 |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Open                              |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | ctrlcomm         |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Common                       |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | ctrlreg          |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Register                     |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | ctrldesc         |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Ctrl_Descriptor                   |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | set_in_sta_addr  |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_In_Start_Addr                 |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | set_in_end_addr  |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_In_End_Addr                   |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | set_out_sta_addr |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_Out_Start_Addr                |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | set_out_end_addr |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_Out_End_Addr                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | set_inbuf        |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_In_Buf_Data                   |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | set_inbufm       |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_In_Buf_Data_Mirror            |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | set_refbuf       |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Set_Ref_Buf_Data                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_ctrlcomm     |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Common                   |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_ctrlreg      |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Register                 |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_ctrldesc     |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ctrl_Descriptor               |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_psta         |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Process_Status                |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_bufsize1     |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Buf_Size                      |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_bufsize2     |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Buf_Size                      |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_inbuf        |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_In_Buf_Data                   |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_inbufm       |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_In_Buf_Data_Mirror            |
 *	+---------------+------------------+---------------+---------------+---------------+---------------+---------------+---------------------------------------------+
 *	| err           | get_refbuf       |               |               |               |               |               | Parameter error.                            |
 *	|               |                  |               |               |               |               |               | >>Dd_RELC_Get_Ref_Buf_Data                  |
 *	+---------------+------------------+---------------+---------------+---------------+---------------;---------------+---------------------------------------------+
*/
void ct_dd_relc_judge(CtDdRelcJugde *self,kint argc, kchar** argv)
{
    if ( strcmp( argv[ 1 ], "desc" ) == 0 ) {
		if ( strcmp( argv[ 2 ], "async" ) == 0 ) {

			self->testNum = (kuchar)atoi( (const kchar *)argv[ 3 ] );
			memset( &(self->setModDesc), 0, sizeof(T_DD_RELC_SET_MOD_DESC) );

			if ( self->testNum == 1 ) {
				/* Normal mode */
				self->setModDesc.write_hprot = 11;
				self->setModDesc.read_hprot = 11;
				self->setModDesc.relc_descriptor_addr	= 0x58000000;
				self->setModDesc.seq_num = 1;
				self->setModDesc.callback	= (RELK_CALLBACK)ct_dd_relc_cmd_cb;

				memcpy( (kuchar *)0x58000000, S_GRELC_DESC_TABLE1, sizeof(S_GRELC_DESC_TABLE1) );

				self->ret = Dd_RELC_Utility_Descriptor( &(self->setModDesc) );

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Set and Start RELC descriptor mode error. ret=%d\n", self->ret));
					return;
				}

				ct_dd_relc_register_dump();
				ct_dd_relc_buffer_dump();
			}
			/* Continuous run mode */
			else if ( self->testNum == 2 ) {		
				self->setModDesc.write_hprot = 11;
				self->setModDesc.read_hprot = 11;
				self->setModDesc.relc_descriptor_addr	= 0x58000000;
				self->setModDesc.seq_num = 3;
				self->setModDesc.callback	= (RELK_CALLBACK)ct_dd_relc_cmd_cb;

				memcpy( (kuchar *)0x58000000, S_GRELC_DESC_TABLE1, sizeof(S_GRELC_DESC_TABLE1) );

				self->ret = Dd_RELC_Utility_Descriptor( &(self->setModDesc) );
				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Set and Start RELC descriptor mode error. ret=%d\n", self->ret));
					return;
				}

				ct_dd_relc_register_dump();
				ct_dd_relc_buffer_dump();
			}
		}
		else if ( strcmp( argv[ 2 ], "sync" ) == 0 ) {
			self->testNum = (kuchar)atoi( (const kchar *)argv[ 3 ] );
			/* Normal mode */
			if ( self->testNum == 1 ) {		

				memcpy( (kuchar *)0x58000000, S_GRELC_DESC_TABLE1, sizeof(S_GRELC_DESC_TABLE1) );
				memset( &(self->ctrlCom), 0, sizeof(T_DD_RELC_CTRL_CMN) );
				memset( &(self->ctrlDesc), 0, sizeof(T_DD_RELC_CTRL_DESC) );

				self->ctrlCom.write_hprot	= 11;
				self->ctrlCom.read_hprot = 11;

				/* After power on and the reset, this is executed only once.
				 * Initialize RELC macro.
				 */
				Dd_RELC_Init( self->ctrlCom.write_hprot, self->ctrlCom.read_hprot );
				Ddim_Print(("RELC init OK\n"));

				// Open RELC macro.
				self->ret = Dd_RELC_Open();

				if ( self->ret != D_DDIM_OK ) {
					Ddim_Print( ("Error RELC Open !!\n" ) );
					return;
				}

				self->ctrlCom.desc_mode = D_DD_RELC_RUN_MODE_DESC;
				self->ctrlCom.callback = (RELK_CALLBACK)ct_dd_relc_cmd_cb;
				self->ctrlCom.seq_num = 1;	
				// Normal mode	
				self->ctrlCom.cont_run_mode = D_DD_RELC_CONT_MODE_NORMAL;
				self->ctrlDesc.descriptor_addr = 0x58000000;

				// Set control common data.
				self->ret = Dd_RELC_Ctrl_Common(&(self->ctrlCom));

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution common control setting error. ret=%d\n", self->ret));
					return;
				}

				// Get control common data.
				memset( &(self->ctrlCom), 0, sizeof(T_DD_RELC_CTRL_CMN) );
				self->ret = Dd_RELC_Get_Ctrl_Common( &(self->ctrlCom) );

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution comon control getting error. ret=%d\n", self->ret));
					return;
				}

				Ddim_Print(("Common control information\n"));
				Ddim_Print(("# Descriptor Mode = %d\n", self->ctrlCom.desc_mode));
				Ddim_Print(("# Continuous Run Mode = %d\n", self->ctrlCom.cont_run_mode));
				Ddim_Print(("# Sequential Run Number of Times = %lu\n", self->ctrlCom.seq_num));

				// Set control descriptor data.
				self->ret = Dd_RELC_Ctrl_Descriptor( &(self->ctrlDesc) );

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution descriptor control setting error. ret=%d\n", self->ret));
					return;
				}

				// Get control descriptor data.
				self->ret = Dd_RELC_Get_Ctrl_Descriptor( &(self->ctrlDesc) );

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution descriptor control getting error. ret=0x%x\n", self->ret));
					return;
				}

				Ddim_Print(("Discriptor control information\n"));
				Ddim_Print(("# Descriptor address = 0x%lx\n", self->ctrlDesc.descriptor_addr));

				// Start RELC macro.(Synchronization of RELC macro start)
				self->ret = Dd_RELC_Start_Sync();

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Synchronous RELC start ERR. ret=0x%x\n", self->ret));
				}else {
					Ddim_Print(("Synchronous RELC start OK\n"));
				}

				// Get RELC macro status.
				self->ret = Dd_RELC_Get_Status();

				Ddim_Print(("RELC decode status\n"));
				Ddim_Print(("# RELC macro status = 0x%x\n", self->ret));

				// Get RELC process status.
				self->ret = Dd_RELC_Get_Process_Status(&(self->decInfo));

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution RELC processing status getting error. ret=0x%x\n", self->ret));
					return;
				}

				Ddim_Print(("RELC processing status\n"));
				Ddim_Print(("# Number of bytes read = %d\n", self->decInfo.read_byte));
				Ddim_Print(("# Number of bytes written = %d\n", self->decInfo.write_byte));
				Ddim_Print(("# Number of processing blocks = %d\n", self->decInfo.proc_block));
				Ddim_Print(("# Decode the total number of bytes to read = %lu\n", self->decInfo.dec_total_read_bytes));
				Ddim_Print(("# Decode the total number of bytes to write = %lu\n", self->decInfo.dec_total_write_bytes));
				Ddim_Print(("# Sequential run counter = %lu\n", self->decInfo.seq_cnt));

				// Get RELC error status.
				self->ret = Dd_RELC_Get_Error_Status();

				Ddim_Print(("RELC error status information\n"));
				Ddim_Print(("# RELC error = 0x%x\n", self->ret));

				// Get RELC error number. 
				self->ret = Dd_RELC_Get_Error();

				Ddim_Print(("RELC error information\n"));
				Ddim_Print(("# RELC error = 0x%x\n", self->ret));

				// Close RELC macro.
				Dd_RELC_Close();

				ct_dd_relc_register_dump();
				ct_dd_relc_buffer_dump();
			}
			else if ( self->testNum == 2 ) {		
				/* Continuous run mode */
				memcpy((kuchar *)0x58000000, S_GRELC_DESC_TABLE1, sizeof(S_GRELC_DESC_TABLE1));
				memset( &(self->ctrlCom), 0, sizeof(T_DD_RELC_CTRL_CMN) );
				memset( &(self->ctrlDesc), 0, sizeof(T_DD_RELC_CTRL_DESC) );

				self->ctrlCom.write_hprot = 11;
				self->ctrlCom.read_hprot = 11;

				/*
				 * After power on and the reset, this is executed only once.
				 *  Initialize RELC macro.
				 */
				Dd_RELC_Init( self->ctrlCom.write_hprot, self->ctrlCom.read_hprot );
				Ddim_Print(("RELC init OK\n"));

				// Open RELC macro.
				self->ret = Dd_RELC_Open();

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print( ("Error RELC Open !!\n" ) );
					return;
				}

				self->ctrlCom.desc_mode = D_DD_RELC_RUN_MODE_DESC;
				self->ctrlCom.callback = (RELK_CALLBACK)ct_dd_relc_cmd_cb;
				self->ctrlCom.seq_num = 3;
				// Continuous run mode 	
				self->ctrlCom.cont_run_mode = D_DD_RELC_CONT_MODE_CONT;
				self->ctrlDesc.descriptor_addr = 0x58000000;

				// Set control common data.
				self->ret = Dd_RELC_Ctrl_Common( &(self->ctrlCom) );

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution common control setting error. ret=%d\n", self->ret));
					return;
				}

				// Get control common data.
				memset(&(self->ctrlCom), 0, sizeof(T_DD_RELC_CTRL_CMN));
				self->ret = Dd_RELC_Get_Ctrl_Common(&(self->ctrlCom));

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution comon control getting error. ret=%d\n", self->ret));
					return;
				}

				Ddim_Print(("Common control information\n"));
				Ddim_Print(("# Descriptor Mode = %d\n", self->ctrlCom.desc_mode));
				Ddim_Print(("# Continuous Run Mode = %d\n", self->ctrlCom.cont_run_mode));
				Ddim_Print(("# Sequential Run Number of Times = %lu\n", self->ctrlCom.seq_num));

				// Set control descriptor data.
				self->ret = Dd_RELC_Ctrl_Descriptor(&(self->ctrlDesc));

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution descriptor control setting error. ret=%d\n", self->ret));
					return;
				}

				// Get control descriptor data.
				self->ret = Dd_RELC_Get_Ctrl_Descriptor(&(self->ctrlDesc));

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution descriptor control getting error. ret=0x%x\n", self->ret));
					return;
				}

				Ddim_Print(("Discriptor control information\n"));
				Ddim_Print(("# Descriptor address = 0x%lx\n", self->ctrlDesc.descriptor_addr));

				// Start RELC macro.(Synchronization of RELC macro start)
				self->ret = Dd_RELC_Start_Sync();

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Synchronous RELC start ERR. ret=0x%x\n", self->ret));
				}else {
					Ddim_Print(("Synchronous RELC start OK\n"));
				}

				// Get RELC macro status.
				self->ret = Dd_RELC_Get_Status();

				Ddim_Print(("RELC decode status\n"));
				Ddim_Print(("# RELC macro status = 0x%x\n", self->ret));

				// Get RELC process status.
				self->ret = Dd_RELC_Get_Process_Status( &(self->decInfo) );

				if ( self->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution RELC processing status getting error. ret=0x%x\n", self->ret));
					return;
				}

				Ddim_Print(("RELC processing status\n"));
				Ddim_Print(("# Number of bytes read = %d\n", self->decInfo.read_byte));
				Ddim_Print(("# Number of bytes written = %d\n", self->decInfo.write_byte));
				Ddim_Print(("# Number of processing blocks = %d\n", self->decInfo.proc_block));
				Ddim_Print(("# Decode the total number of bytes to read = %lu\n", self->decInfo.dec_total_read_bytes));
				Ddim_Print(("# Decode the total number of bytes to write = %lu\n", self->decInfo.dec_total_write_bytes));
				Ddim_Print(("# Sequential run counter = %lu\n", self->decInfo.seq_cnt));

				// Get RELC error status.
				self->ret = Dd_RELC_Get_Error_Status();

				Ddim_Print(("RELC error status information\n"));
				Ddim_Print(("# RELC error = 0x%x\n", self->ret));

				// Get RELC error number. 
				self->ret = Dd_RELC_Get_Error();

				Ddim_Print(("RELC error information\n"));
				Ddim_Print(("# RELC error = 0x%x\n", self->ret));

				// Close RELC macro.
				Dd_RELC_Close();

				ct_dd_relc_register_dump();
				ct_dd_relc_buffer_dump();
			}
		}
	}
	else if ( strcmp( argv[ 1 ], "inthdr" ) == 0 ) {
#ifdef PC_DEBUG
		self->testPat = strtoul( argv[ 2 ], &(self->endstr), 16 );
		switch ( self->testPat ) {
			case 1:
				IO_RELC.RELC_INT_EN.bit.SINT = 1;
				IO_RELC.RELC_INT_ST.bit.__SINS = 1;
				break;
			case 2:
				IO_RELC.RELC_INT_EN.bit.FINT = 1;
				IO_RELC.RELC_INT_ST.bit.__FINS = 1;
				break;
			case 3:
				IO_RELC.RELC_INT_EN.bit.EINT = 1;
				IO_RELC.RELC_INT_ST.bit.__EINS = 1;
				break;
			default:
				IO_RELC.RELC_INT_EN.bit.CINT = 1;
				IO_RELC.RELC_INT_ST.bit.__CINS = 1;
				break;
		}
#endif
		Dd_RELC_Int_Handler();
#ifdef PC_DEBUG
		ct_dd_relc_register_dump();
#endif
	}
	else if ( strcmp( argv[ 1 ], "err" ) == 0 ) {
		if ( strcmp( argv[ 2 ], "open" ) == 0 ) {
			self->ret = Dd_RELC_Open();
			self->ret = Dd_RELC_Open();

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Open error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "ctrlcomm" ) == 0 ) {
			self->ret = Dd_RELC_Ctrl_Common( NULL );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution comon control getting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "ctrlreg" ) == 0 ) {
			self->ret = Dd_RELC_Ctrl_Register( NULL );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution register control getting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "ctrldesc" ) == 0 ) {
			self->ret = Dd_RELC_Ctrl_Descriptor( NULL );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution descriptor control getting error. ret=0x%x\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "set_in_sta_addr" ) == 0 ) {
			self->ret = Dd_RELC_Set_In_Start_Addr( 0 );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution input start address setting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "set_in_end_addr" ) == 0 ) {
			self->ret = Dd_RELC_Set_In_End_Addr( 0 );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution input end address setting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "set_out_sta_addr" ) == 0 ) {
			self->ret = Dd_RELC_Set_Out_Start_Addr( 0 );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution output start address setting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "set_out_end_addr" ) == 0 ) {
			self->ret = Dd_RELC_Set_Out_End_Addr( 0 );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution output end address setting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "set_inbuf" ) == 0 ) {
			self->ret = Dd_RELC_Set_In_Buf_Data( 0, self->refBufSize );		
			/* pgr0039 */
			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution input buffer setting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "set_inbufm" ) == 0 ) {
			self->ret = Dd_RELC_Set_In_Buf_Data_Mirror( 0, 256 );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution input buffer(mirror) setting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "set_refbuf" ) == 0 ) {
			self->ret = Dd_RELC_Set_Ref_Buf_Data( 0, 256 );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution reference buffer setting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_ctrlcomm" ) == 0 ) {
			self->ret = Dd_RELC_Get_Ctrl_Common( NULL );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution comon control getting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_ctrlreg" ) == 0 ) {
			self->ret = Dd_RELC_Get_Ctrl_Register( NULL );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution register control getting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_ctrldesc" ) == 0 ) {
			self->ret = Dd_RELC_Get_Ctrl_Descriptor( NULL );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution descriptor control getting error. ret=0x%x\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_psta" ) == 0 ) {

#ifdef PC_DEBUG
			IO_RELC.RELC_READ_BYTE.bit.DRNM	= 1234;
			IO_RELC.RELC_WRITE_BYTE.bit.DWNM = 2345;
			IO_RELC.RELC_BLOCK.bit.BLKN = 3456;
			IO_RELC.RELC_INPUT_BYTE = 876;
			IO_RELC.RELC_OUTPUT_BYTE = 985;
			IO_RELC.RELC_SEQ_CNT = 65;
#endif

			self->ret = Dd_RELC_Get_Process_Status( NULL );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution RELC processing status getting error. ret=0x%x\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_bufsize1" ) == 0 ) {
			self->ret = Dd_RELC_Get_Buf_Size( NULL, &(self->refBufSize) );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution RELC buffer size getting error. ret=0x%x\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_bufsize2" ) == 0 ) {
			self->ret = Dd_RELC_Get_Buf_Size( &(self->inBufSize), NULL );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution RELC buffer size getting error. ret=0x%x\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_inbuf" ) == 0 ) {
			self->ret = Dd_RELC_Get_In_Buf_Data( 0, self->setSize );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution RELC input buffer data getting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_inbufm" ) == 0 ) {
			self->ret = Dd_RELC_Get_In_Buf_Data_Mirror( 0, self->setSize );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution RELC input data buffer getting error. ret=%d\n", self->ret));
				return;
			}
		}
		else if ( strcmp( argv[ 2 ], "get_refbuf" ) == 0 ) {
			self->ret = Dd_RELC_Get_Ref_Buf_Data( 0, self->setSize );

			if ( self->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution RELC reference data buffer getting error. ret=%d\n", self->ret));
				return;
			}
		}
	}else{
		ct_dd_relc_help();
	}
}

CtDdRelcJugde* ct_dd_relc_jugde_new(void) 
{
    CtDdRelcJugde *self = k_object_new_with_private(CT_TYPE_DD_RELC_JUGDE, sizeof(CtDdRelcJugdePrivate));

    return self;
}
