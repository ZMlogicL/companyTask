/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdRelcMain类
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
#include "ctddrelcjugde.h"
#include "ctddrelcmain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdRelcMain, ct_dd_relc_main);
#define CT_DD_RELC_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdRelcMainPrivate,CT_TYPE_DD_RELC_MAIN))

struct _CtDdRelcMainPrivate
{
	CtDdRelcJugde *judge;
};

// Continuous mode judge data
static volatile kuchar S_GRELC_CONT_MODE;

/*
 *DECLS
 */
static void 	ctExsRegisterDump( void );

static void ct_dd_relc_main_constructor(CtDdRelcMain *self) 
{
    CtDdRelcMainPrivate *priv = CT_DD_RELC_MAIN_GET_PRIVATE(self);

    priv->judge = ct_dd_relc_jugde_new();
}

static void ct_dd_relc_main_destructor(CtDdRelcMain *self) 
{
	CtDdRelcMainPrivate *priv = CT_DD_RELC_MAIN_GET_PRIVATE(self);

    k_object_unref(priv->judge);
    priv->judge = NULL;
}

/*
 *IMPL
 */
static void ctExsRegisterDump( void )
{
#ifdef PC_DEBUG
	Ddim_Print(("EXS REGISTER INFO.\n"));
	Ddim_Print(("IO_EXSTOP.RLC_HPT_CTL.bit.RERHPT = %d\n", IO_EXSTOP.RLC_HPT_CTL.bit.RERHPT));
	Ddim_Print(("IO_EXSTOP.RLC_HPT_CTL.bit.REWHPT = %d\n", IO_EXSTOP.RLC_HPT_CTL.bit.REWHPT));
#endif
}

/*
 *PUBLIC
 */

/*
 * @brief  Command main function for RELC test.
 * @param  kint32 argc	:The number of parameters
 *	CGAR** argv	:The value of parameters
 *	The meaning of parameters see ctddrelcjugde.c
 */
void ct_dd_relc_main(CtDdRelcMain *self,kint argc, kchar** argv )
{
    CtDdRelcMainPrivate *priv = CT_DD_RELC_MAIN_GET_PRIVATE(self);
	priv->judge->ret = D_DD_RELC_OK;
	priv->judge->setSize = 0;
	priv ->judge->refBufSize = 0;
	
	if ( strcmp( argv[ 1 ], "init" ) == 0 ) {
		/* Initialize RELC */
		priv->judge->writeHprot	= strtoul(argv[ 2 ], &(priv->judge->hprot), 16);
		priv->judge->readHprot	= strtoul(argv[ 3 ], &(priv->judge->hprot), 16);

		Dd_RELC_Init((kuchar)priv->judge->writeHprot, (kuchar)priv->judge->readHprot);
		/* pgr0539 */		
		Ddim_Print(("RELC init OK\n"));

		ct_dd_relc_register_dump();
		ctExsRegisterDump();
	}
	else if (strcmp(argv[ 1 ], "open" ) == 0) {
		/* Open RELC */
		priv->judge->ret = Dd_RELC_Open();

		if (priv->judge->ret != D_DD_RELC_OK) {
			Ddim_Print(("RELC open ERR. ret=0x%x\n", priv->judge->ret));
		}else {
			Ddim_Print(("RELC open OK\n"));
		}
	}
	else if (strcmp( argv[ 1 ], "close") == 0 ) {
		/* Close RELC */
		Dd_RELC_Close();
		Ddim_Print(("RELC close OK\n"));
	}
	else if (strcmp( argv[ 1 ], "start" ) == 0) {
		/* Synchronous start of RELC */
		if (strcmp( argv[ 2 ], "sync" ) == 0) {
			priv->judge->ret = Dd_RELC_Start_Sync();

			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Synchronous RELC start ERR. ret=0x%x\n", priv->judge->ret));
			}else {
				Ddim_Print(("Synchronous RELC start OK\n"));
			}
		}
		/* Asynchronous start of RELC */
		else if (strcmp( argv[ 2 ], "async" ) == 0) {
			Dd_RELC_Start_Async();
		}else {
		}

		ct_dd_relc_register_dump();
	}
	else if(strcmp( argv[ 1 ], "stop" ) == 0) {
		/* Stop RELC */
#ifdef PC_DEBUG
		IO_RELC.RELC_MODE1.bit.PRUN = 1;
#endif
		Dd_RELC_Stop();
		Ddim_Print(("RELC stop OK\n"));

		ct_dd_relc_register_dump();
	}
	else if (strcmp( argv[ 1 ], "ctrlcomm" ) == 0) {
		/* Control common of RELC */
		if (strcmp( argv[ 2 ], "reg" ) == 0) {
			// Normal mode(register)			
			priv->judge->ctrlCom.desc_mode = D_DD_RELC_RUN_MODE_NORMAL;
		}
		else if (strcmp( argv[ 2 ], "desc" ) == 0) {
			// Descriptor mode		
			priv->judge->ctrlCom.desc_mode = D_DD_RELC_RUN_MODE_DESC;
		}else {
			priv->judge->ctrlCom.desc_mode = D_DD_RELC_RUN_MODE_NORMAL;
		}

		if (strcmp( argv[ 3 ], "nmod") == 0) {
			// Normal mode(once)			
			priv->judge->ctrlCom.cont_run_mode = D_DD_RELC_CONT_MODE_NORMAL;
			S_GRELC_CONT_MODE = 0;
		}
		else if (strcmp( argv[ 3 ], "cmod") == 0 ) {
			// Continuous Mode		
			priv->judge->ctrlCom.cont_run_mode = D_DD_RELC_CONT_MODE_CONT;
			S_GRELC_CONT_MODE = 1;
		}else {
			priv->judge->ctrlCom.cont_run_mode = D_DD_RELC_CONT_MODE_NORMAL;
			S_GRELC_CONT_MODE = 0;
		}

		priv->judge->ctrlCom.seq_num	= (kulong)atoi(argv[ 4 ]);
		priv->judge->ctrlCom.callback 	= (RELK_CALLBACK)ct_dd_relc_cmd_cb;

		priv->judge->ret = Dd_RELC_Ctrl_Common(&(priv->judge->ctrlCom));
		if (priv->judge->ret != D_DD_RELC_OK) {
			Ddim_Print(("Execution common control setting error. ret=%d\n", priv->judge->ret));
			return;
		}

		ct_dd_relc_register_dump();
	}
	else if (strcmp( argv[ 1 ], "ctrlreg") == 0) {
		/* Control register of RELC */
		if (strcmp( argv[ 2 ], "imaxd") == 0) {
			// Input end address disable 
			priv->judge->ctrlReg.in_end_addr_en = D_DD_RELC_ADDR_DISABLE;
		}
		else if (strcmp( argv[ 2 ], "imaxe" ) == 0) {
			// Input end address enable	
			priv->judge->ctrlReg.in_end_addr_en = D_DD_RELC_ADDR_ENABLE;
		}else {
			priv->judge->ctrlReg.in_end_addr_en = D_DD_RELC_ADDR_DISABLE;
		}

		if (strcmp( argv[ 3 ], "omaxd" ) == 0) {
			// Output end address disable		
			priv->judge->ctrlReg.out_end_addr_en = D_DD_RELC_ADDR_DISABLE;
		}
		else if (strcmp( argv[ 3 ], "omaxe" ) == 0) {
			// Output end address disable	
			priv->judge->ctrlReg.out_end_addr_en = D_DD_RELC_ADDR_ENABLE;
		}else {
			priv->judge->ctrlReg.out_end_addr_en = D_DD_RELC_ADDR_DISABLE;
		}

		if (S_GRELC_CONT_MODE != 0) {
			/* Address auto increment on */				
			priv->judge->ctrlReg.in_addr_auto_inc = D_DD_RELC_ADDR_INCRE_ON;
			priv->judge->ctrlReg.out_addr_auto_inc = D_DD_RELC_ADDR_INCRE_ON;
		}else {
			/* Address auto increment off */										
			priv->judge->ctrlReg.in_addr_auto_inc = D_DD_RELC_ADDR_INCRE_OFF;
			priv->judge->ctrlReg.out_addr_auto_inc = D_DD_RELC_ADDR_INCRE_OFF;
		}

		priv->judge->ctrlReg.in_start_addr = strtoul(argv[ 4 ], &(priv->judge->endstr), 16);
		priv->judge->ctrlReg.in_end_addr = strtoul(argv[ 5 ], &(priv->judge->endstr), 16);
		priv->judge->ctrlReg.out_start_addr = strtoul(argv[ 6 ], &(priv->judge->endstr), 16);
		priv->judge->ctrlReg.out_end_addr = strtoul(argv[ 7 ], &(priv->judge->endstr), 16);

#ifdef PC_DEBUG
		if (priv->judge->ctrlReg.in_end_addr_en == D_DD_RELC_ADDR_DISABLE) {
			IO_RELC.RELC_MODE2.bit.IMAX = 1;
			IO_RELC.RELC_MODE2.bit.OMAX = 1;
			IO_RELC.RELC_MODE2.bit.IAAI = 1;
			IO_RELC.RELC_MODE2.bit.OAAI = 1;
		}else {
			IO_RELC.RELC_MODE2.bit.IMAX = 0;
			IO_RELC.RELC_MODE2.bit.OMAX = 0;
			IO_RELC.RELC_MODE2.bit.IAAI = 1;
			IO_RELC.RELC_MODE2.bit.OAAI = 1;
		}
#endif

		priv->judge->ret = Dd_RELC_Ctrl_Register(&(priv->judge->ctrlReg));

		if ( priv->judge->ret != D_DD_RELC_OK ) {
			Ddim_Print(("Execution register control setting error. ret=%d\n", priv->judge->ret));
			return;
		}

		ct_dd_relc_register_dump();
	}
	else if ( strcmp(argv[ 1 ], "ctrldesc" ) == 0 ) {
		/* Control descriptor of RELC */
		priv->judge->ctrlDesc.descriptor_addr = strtoul(argv[ 2 ], &(priv->judge->endstr), 16);

		priv->judge->ret = Dd_RELC_Ctrl_Descriptor(&(priv->judge->ctrlDesc));

		if (priv->judge->ret != D_DD_RELC_OK) {
			Ddim_Print(("Execution descriptor control setting error. ret=%d\n", priv->judge->ret));
			return;
		}

		ct_dd_relc_register_dump();
	}
	else if (strcmp( argv[ 1 ], "set" ) == 0) {
		if (strcmp( argv[ 2 ], "in_sta_addr" ) == 0) {

			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 16);
			priv->judge->ret = Dd_RELC_Set_In_Start_Addr(priv->judge->setAddr);

			/* pgr0539 */
			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution input start address setting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
		}
		else if ( strcmp( argv[ 2 ], "in_end_addr" ) == 0 ) {
			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 16);
			priv->judge->ret = Dd_RELC_Set_In_End_Addr(priv->judge->setAddr);

			/* pgr0539 */
			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution input end address setting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
		}
		else if (strcmp( argv[ 2 ], "out_sta_addr" ) == 0) {
			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 16);
			priv->judge->ret = Dd_RELC_Set_Out_Start_Addr(priv->judge->setAddr);

			/* pgr0539 */
			if ( priv->judge->ret != D_DD_RELC_OK ) {
				Ddim_Print(("Execution output start address setting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
		}
		else if (strcmp( argv[ 2 ], "out_end_addr" ) == 0) {
			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 16 );
			priv->judge->ret = Dd_RELC_Set_Out_End_Addr(priv->judge->setAddr );

			/* pgr0539 */
			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution output end address setting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
		}
		else if (strcmp( argv[ 2 ], "inbuf" ) == 0) {
			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 16);
			priv->judge->setSize = (kuint32)atoi( (const kchar *)argv[ 4 ] );
			priv->judge->ret = Dd_RELC_Set_In_Buf_Data(priv->judge->setAddr, priv->judge->setSize);

			/* pgr0539 */
			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution input buffer setting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
		}
		else if (strcmp( argv[ 2 ], "inbufm") == 0 ) {
			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 16);
			priv->judge->setSize = (kuint32)atoi((const kchar *)argv[ 4 ]);
			priv->judge->ret = Dd_RELC_Set_In_Buf_Data_Mirror(priv->judge->setAddr, priv->judge->setSize);

			/* pgr0539 */
			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution input buffer(mirror) setting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
		}
		else if (strcmp( argv[ 2 ], "refbuf" ) == 0) {
			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 16);
			priv->judge->setSize = (kuint32)atoi( (const kchar *)argv[ 4 ] );
			priv->judge->ret = Dd_RELC_Set_Ref_Buf_Data(priv->judge->setAddr, priv->judge->setSize);

			/* pgr0539 */
			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution reference buffer setting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
		}
	}
	else if (strcmp( argv[ 1 ], "get") == 0 ) {
		if (strcmp( argv[ 2 ], "ctrlcomm") == 0 ) {
#ifdef PC_DEBUG
			IO_RELC.RELC_MODE1.bit.DSMD = 1;
			IO_RELC.RELC_MODE1.bit.CRMD = 1;
			IO_RELC.RELC_SEQ_NUM = 726;
#endif
			priv->judge->ret = Dd_RELC_Get_Ctrl_Common(&(priv->judge->ctrlCom));

			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution comon control getting error. ret=%d\n", priv->judge->ret));
				return;
			}

			Ddim_Print(("Common control information\n"));
			Ddim_Print(("# Descriptor Mode = %d\n", priv->judge->ctrlCom.desc_mode));
			Ddim_Print(("# Continuous Run Mode = %d\n", priv->judge->ctrlCom.cont_run_mode));
			Ddim_Print(("# Sequential Run Number of Times = %lu\n", priv->judge->ctrlCom.seq_num));

			ct_dd_relc_register_dump();
		}
		else if (strcmp( argv[ 2 ], "ctrlreg") == 0 ) {
#ifdef PC_DEBUG
			IO_RELC.RELC_MODE2.bit.IMAX = 1;
			IO_RELC.RELC_MODE2.bit.OMAX = 1;
			IO_RELC.RELC_MODE2.bit.IAAI	= 1;
			IO_RELC.RELC_MODE2.bit.OAAI	= 1;
			IO_RELC.RELC_IN_START_ADDR = 0x41012560;
			IO_RELC.RELC_IN_END_ADDR = 0x41024568;
			IO_RELC.RELC_OUT_START_ADDR = 0x42302530;
			IO_RELC.RELC_OUT_END_ADDR = 0x44332020;
#endif
			priv->judge->ret = Dd_RELC_Get_Ctrl_Register(&(priv->judge->ctrlReg));

			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution register control getting error. ret=%d\n", priv->judge->ret));
				return;
			}

			Ddim_Print(("Register control information\n"));
			Ddim_Print(("# Input End Address Enable = %d\n", priv->judge->ctrlReg.in_end_addr_en));
			Ddim_Print(("# Output End Address Enable = %d\n", priv->judge->ctrlReg.out_end_addr_en));
			Ddim_Print(("# Input Address Auto Increment = %d\n", priv->judge->ctrlReg.in_addr_auto_inc));
			Ddim_Print(("# Output Address Auto Increment = %d\n", priv->judge->ctrlReg.out_addr_auto_inc));
			Ddim_Print(("# Input start address = 0x%lx\n", priv->judge->ctrlReg.in_start_addr));
			Ddim_Print(("# Input end address = 0x%lx\n", priv->judge->ctrlReg.in_end_addr));
			Ddim_Print(("# Output start address = 0x%lx\n", priv->judge->ctrlReg.out_start_addr));
			Ddim_Print(("# Output end address = 0x%lx\n", priv->judge->ctrlReg.out_end_addr));

			ct_dd_relc_register_dump();
		}
		else if (strcmp(argv[ 2 ], "ctrldesc" ) == 0) {
#ifdef PC_DEBUG
			IO_RELC.RELC_DESCRIPTOR_ADDR = 0x44802210;
#endif
			priv->judge->ret = Dd_RELC_Get_Ctrl_Descriptor(&(priv->judge->ctrlDesc));

			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution descriptor control getting error. ret=0x%x\n", priv->judge->ret));
				return;
			}

			Ddim_Print(("Discriptor control information\n"));
			Ddim_Print(("# Descriptor address = 0x%lx\n", priv->judge->ctrlDesc.descriptor_addr));

			ct_dd_relc_register_dump();
		}
		else if ( strcmp( argv[ 2 ], "msta" ) == 0 ) {
#ifdef PC_DEBUG
			IO_RELC.RELC_STATUS.word = 4;
#endif
			priv->judge->ret = Dd_RELC_Get_Status();
			Ddim_Print(("RELC decode status\n"));
			Ddim_Print(("# RELC macro status = 0x%x\n", priv->judge->ret));

			ct_dd_relc_register_dump();
		}
		else if (strcmp(argv[ 2 ], "sleep" ) == 0) {
#ifdef PC_DEBUG
			IO_RELC.RELC_STATUS.bit.SRES = 2;
#endif
			priv->judge->ret = Dd_RELC_Get_Sleep_Reason();
			Ddim_Print(("RELC sleep reason\n"));
			Ddim_Print(("# RELC sleep reason = 0x%x\n", priv->judge->ret));

			ct_dd_relc_register_dump();
		}
		else if (strcmp(argv[ 2 ], "errsta") == 0) {
#ifdef PC_DEBUG
			IO_RELC.RELC_STATUS.bit.EFLG = 1;
#endif
			priv->judge->ret = Dd_RELC_Get_Error_Status();

			Ddim_Print(("RELC error status information\n"));
			Ddim_Print(("# RELC error = 0x%x\n", priv->judge->ret));

			ct_dd_relc_register_dump();
		}
		else if (strcmp(argv[ 2 ], "err") == 0) {
#ifdef PC_DEBUG
			IO_RELC.RELC_ERROR_NUM.word = 0x00008234;
#endif
			priv->judge->ret = Dd_RELC_Get_Error();

			Ddim_Print(("RELC error information\n"));
			Ddim_Print(("# RELC error = 0x%x\n", priv->judge->ret));

			ct_dd_relc_register_dump();
		}
		else if (strcmp( argv[ 2 ], "psta" ) == 0) {
#ifdef PC_DEBUG
			IO_RELC.RELC_READ_BYTE.bit.DRNM = 1234;
			IO_RELC.RELC_WRITE_BYTE.bit.DWNM = 2345;
			IO_RELC.RELC_BLOCK.bit.BLKN	= 3456;
			IO_RELC.RELC_INPUT_BYTE = 876;
			IO_RELC.RELC_OUTPUT_BYTE = 985;
			IO_RELC.RELC_SEQ_CNT = 65;
#endif
			priv->judge->ret = Dd_RELC_Get_Process_Status(&(priv->judge->decInfo));
			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution RELC processing status getting error. ret=0x%x\n", priv->judge->ret));
				return;
			}

			Ddim_Print(("RELC processing status\n"));
			Ddim_Print(("# Number of bytes read = %d\n", priv->judge->decInfo.read_byte));
			Ddim_Print(("# Number of bytes written = %d\n", priv->judge->decInfo.write_byte));
			Ddim_Print(("# Number of processing blocks = %d\n", priv->judge->decInfo.proc_block));
			Ddim_Print(("# Decode the total number of bytes to read = %lu\n", priv->judge->decInfo.dec_total_read_bytes));
			Ddim_Print(("# Decode the total number of bytes to write = %lu\n", priv->judge->decInfo.dec_total_write_bytes));
			Ddim_Print(("# Sequential run counter = %lu\n", priv->judge->decInfo.seq_cnt));

			ct_dd_relc_register_dump();
		}
		else if (strcmp( argv[ 2 ], "bufsize" ) == 0) {
#ifdef PC_DEBUG
			IO_RELC.RELC_BUF_SIZE.bit.IBFS = 7;
			IO_RELC.RELC_BUF_SIZE.bit.RBFS = 1;
#endif
			priv->judge->ret = Dd_RELC_Get_Buf_Size(&(priv->judge->inBufSize), &(priv->judge->refBufSize));

			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution RELC buffer size getting error. ret=0x%x\n", priv->judge->ret));
				return;
			}

			Ddim_Print(("RELC buffer size information\n"));
			Ddim_Print(("# RELC input buffer size = %d\n", priv->judge->inBufSize));
			Ddim_Print(("# RELC reference buffer size = %d\n", priv->judge->refBufSize));

			ct_dd_relc_register_dump();
		}
		else if ( strcmp( argv[ 2 ], "inbuf" ) == 0 ) {

			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 16);
			priv->judge->setSize = (kuint32)atoi((const kchar *)argv[ 4 ]);
			priv->judge->ret = Dd_RELC_Get_In_Buf_Data(priv->judge->setAddr, priv->judge->setSize);

			/* pgr0539 */
			if (priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution RELC input buffer data getting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
			ct_dd_relc_buffer_dump();
		}
		else if (strcmp( argv[ 2 ], "inbufm" ) == 0) {
			priv->judge->setAddr = strtoul(argv[ 3 ], &(priv->judge->endstr), 1 );
			priv->judge->setSize = (kuint32)atoi((const kchar *)argv[ 4 ]);
			priv->judge->ret = Dd_RELC_Get_In_Buf_Data_Mirror(priv->judge->setAddr, priv->judge->setSize);
			
			/* pgr0539 */
			if(priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution RELC input data buffer getting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
			ct_dd_relc_buffer_dump();
		}
		else if (strcmp( argv[ 2 ], "refbuf" ) == 0) {
			priv->judge->setAddr = strtoul( argv[ 3 ], &(priv->judge->endstr), 16 );
			priv->judge->setSize = (kuint32)atoi( (const kchar *)argv[ 4 ] );
			priv->judge->ret = Dd_RELC_Get_Ref_Buf_Data( priv->judge->setAddr, priv->judge->setSize );

			/* pgr0539 */
			if(priv->judge->ret != D_DD_RELC_OK) {
				Ddim_Print(("Execution RELC reference data buffer getting error. ret=%d\n", priv->judge->ret));
				return;
			}

			ct_dd_relc_register_dump();
			ct_dd_relc_buffer_dump();
		}
	}
	else if (strcmp( argv[ 1 ], "norm" ) == 0) {
		if (strcmp( argv[ 2 ], "async" ) == 0) {

			priv->judge->testNum = (kuchar)atoi((const kchar *)argv[ 3 ]);
			memset(&(priv->judge->setModNorm), 0, sizeof(T_DD_RELC_SET_MOD_NORMAL));

			if ( priv->judge->testNum == 1) {
				/* Normal mode */		
				priv->judge->setModNorm.write_hprot	= 11;
				priv->judge->setModNorm.read_hprot = 11;
				priv->judge->setModNorm.in_start_addr = 0x58100000;
				priv->judge->setModNorm.out_start_addr = 0x58200000;
				priv->judge->setModNorm.seq_num = 1;
				priv->judge->setModNorm.callback = (RELK_CALLBACK)ct_dd_relc_cmd_cb;

				priv->judge->ret = Dd_RELC_Utility_Register( &(priv->judge->setModNorm) );

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Set and Start RELC normal mode error. ret=%d\n", priv->judge->ret));
					return;
				}

				ct_dd_relc_register_dump();
				ct_dd_relc_buffer_dump();
			}
			else if (priv->judge->testNum == 2) {
				/* Continuous run mode */		
				priv->judge->setModNorm.write_hprot	= 11;
				priv->judge->setModNorm.read_hprot = 11;
				priv->judge->setModNorm.in_start_addr = 0x58100000;
				priv->judge->setModNorm.out_start_addr = 0x58200000;
				priv->judge->setModNorm.seq_num = 3;
				priv->judge->setModNorm.callback = (RELK_CALLBACK)ct_dd_relc_cmd_cb;

				priv->judge->ret = Dd_RELC_Utility_Register(&(priv->judge->setModNorm));

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Set and Start RELC normal mode error. ret=%d\n", priv->judge->ret));
					return;
				}

				ct_dd_relc_register_dump();
				ct_dd_relc_buffer_dump();
			}
		}
		else if (strcmp( argv[ 2 ], "sync" ) == 0) {
			priv->judge->testNum = (kuchar)atoi((const kchar *)argv[ 3 ]);

			if ( priv->judge->testNum == 1) {
				/* Normal mode */		
				memset(&(priv->judge->ctrlCom), 0, sizeof(T_DD_RELC_CTRL_CMN));
				memset(&(priv->judge->ctrlReg), 0, sizeof(T_DD_RELC_CTRL_REG));

				priv->judge->ctrlCom.write_hprot	 = 11;
				priv->judge->ctrlCom.read_hprot	= 11;

				/* After power on and the reset, this is executed only once
				*Initialize RELC macro
				*/	
				Dd_RELC_Init(priv->judge->ctrlCom.write_hprot, priv->judge->ctrlCom.read_hprot);
				Ddim_Print(("RELC init OK\n"));

				// Open RELC macro.
				priv->judge->ret = Dd_RELC_Open();

				if (priv->judge->ret != D_DDIM_OK) {
					Ddim_Print(("Error RELC Open !!\n" ));
					return;
				}

				priv->judge->ctrlCom.desc_mode = D_DD_RELC_RUN_MODE_NORMAL;
				priv->judge->ctrlCom.callback = (RELK_CALLBACK)ct_dd_relc_cmd_cb;
				priv->judge->ctrlCom.seq_num = 1;
				// Normal mode		
				priv->judge->ctrlCom.cont_run_mode = D_DD_RELC_CONT_MODE_NORMAL;
				priv->judge->ctrlReg.in_end_addr_en = D_DD_RELC_ADDR_ENABLE;
				priv->judge->ctrlReg.out_end_addr_en = D_DD_RELC_ADDR_ENABLE;
				priv->judge->ctrlReg.in_addr_auto_inc = D_DD_RELC_ADDR_INCRE_OFF;
				priv->judge->ctrlReg.out_addr_auto_inc = D_DD_RELC_ADDR_INCRE_OFF;
				priv->judge->ctrlReg.in_start_addr = 0x58100000;
				priv->judge->ctrlReg.in_end_addr = 0x581166B5;
				priv->judge->ctrlReg.out_start_addr = 0x58200000;
				priv->judge->ctrlReg.out_end_addr = 0x58218A5C;

				// Set control common data.
				priv->judge->ret = Dd_RELC_Ctrl_Common(&(priv->judge->ctrlCom));

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Execution common control setting error. ret=%d\n", priv->judge->ret));
					return;
				}

				// Get control common data.
				memset(&(priv->judge->ctrlCom), 0, sizeof(T_DD_RELC_CTRL_CMN));
				priv->judge->ret = Dd_RELC_Get_Ctrl_Common(&(priv->judge->ctrlCom));

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Execution comon control getting error. ret=%d\n", priv->judge->ret));
					return;
				}

				Ddim_Print(("Common control information\n"));
				Ddim_Print(("# Descriptor Mode = %d\n", priv->judge->ctrlCom.desc_mode));
				Ddim_Print(("# Continuous Run Mode = %d\n", priv->judge->ctrlCom.cont_run_mode));
				Ddim_Print(("# Sequential Run Number of Times = %lu\n", priv->judge->ctrlCom.seq_num));

				// Set control register data.
				priv->judge->ret = Dd_RELC_Ctrl_Register( &(priv->judge->ctrlReg) );

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Execution register control setting error. ret=%d\n", priv->judge->ret));
					return;
				}

				// Get control register data.
				memset(&(priv->judge->ctrlReg), 0, sizeof(T_DD_RELC_CTRL_REG));
				priv->judge->ret = Dd_RELC_Get_Ctrl_Register(&(priv->judge->ctrlReg));

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Execution register control getting error. ret=%d\n", priv->judge->ret));
					return;
				}

				Ddim_Print(("Register control information\n"));
				Ddim_Print(("# Input End Address Enable = %d\n", priv->judge->ctrlReg.in_end_addr_en));
				Ddim_Print(("# Output End Address Enable = %d\n", priv->judge->ctrlReg.out_end_addr_en));
				Ddim_Print(("# Input Address Auto Increment = %d\n", priv->judge->ctrlReg.in_addr_auto_inc));
				Ddim_Print(("# Output Address Auto Increment = %d\n", priv->judge->ctrlReg.out_addr_auto_inc));
				Ddim_Print(("# Input start address = 0x%lx\n", priv->judge->ctrlReg.in_start_addr));
				Ddim_Print(("# Input end address = 0x%lx\n", priv->judge->ctrlReg.in_end_addr));
				Ddim_Print(("# Output start address = 0x%lx\n", priv->judge->ctrlReg.out_start_addr));
				Ddim_Print(("# Output end address = 0x%lx\n", priv->judge->ctrlReg.out_end_addr));

				// Start RELC macro.(Synchronization of RELC macro start)
				priv->judge->ret = Dd_RELC_Start_Sync();

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Synchronous RELC start ERR. ret=0x%x\n", priv->judge->ret));
				}else {
					Ddim_Print(("Synchronous RELC start OK\n"));
				}

				// Get RELC macro status.
				priv->judge->ret = Dd_RELC_Get_Status();

				Ddim_Print(("RELC decode status\n"));
				Ddim_Print(("# RELC macro status = 0x%x\n", priv->judge->ret));

				// Get RELC process status.
				priv->judge->ret = Dd_RELC_Get_Process_Status(&(priv->judge->decInfo));

				if ( priv->judge->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution RELC processing status getting error. ret=0x%x\n", priv->judge->ret));
					return;
				}

				Ddim_Print(("RELC processing status\n"));
				Ddim_Print(("# Number of bytes read = %d\n", priv->judge->decInfo.read_byte));
				Ddim_Print(("# Number of bytes written = %d\n", priv->judge->decInfo.write_byte));
				Ddim_Print(("# Number of processing blocks = %d\n", priv->judge->decInfo.proc_block));
				Ddim_Print(("# Decode the total number of bytes to read = %lu\n", priv->judge->decInfo.dec_total_read_bytes));
				Ddim_Print(("# Decode the total number of bytes to write = %lu\n", priv->judge->decInfo.dec_total_write_bytes));
				Ddim_Print(("# Sequential run counter = %lu\n", priv->judge->decInfo.seq_cnt));

				// Get RELC error status.
				priv->judge->ret = Dd_RELC_Get_Error_Status();

				Ddim_Print(("RELC error status information\n"));
				Ddim_Print(("# RELC error = 0x%x\n", priv->judge->ret));

				// Get RELC error number. 
				priv->judge->ret = Dd_RELC_Get_Error();

				Ddim_Print(("RELC error information\n"));
				Ddim_Print(("# RELC error = 0x%x\n", priv->judge->ret));

				// Close RELC macro.
				Dd_RELC_Close();

				ct_dd_relc_register_dump();
				ct_dd_relc_buffer_dump();
			}
			else if (priv->judge->testNum == 2) {
				/* Continuous run mode */
				memset(&(priv->judge->ctrlCom), 0, sizeof(T_DD_RELC_CTRL_CMN));
				memset(&(priv->judge->ctrlReg), 0, sizeof(T_DD_RELC_CTRL_REG));

				priv->judge->ctrlCom.write_hprot = 11;
				priv->judge->ctrlCom.read_hprot = 11;

				/* After power on and the reset, this is executed only once. */
				Dd_RELC_Init(priv->judge->ctrlCom.write_hprot, priv->judge->ctrlCom.read_hprot);
				Ddim_Print(("RELC init OK\n"));

				// Open RELC macro
				priv->judge->ret = Dd_RELC_Open();

				if ( priv->judge->ret != D_DDIM_OK ) {
					Ddim_Print(("Error RELC Open !!\n" ));
					return;
				}

				priv->judge->ctrlCom.desc_mode = D_DD_RELC_RUN_MODE_NORMAL;
				priv->judge->ctrlCom.callback = (RELK_CALLBACK)ct_dd_relc_cmd_cb;
				priv->judge->ctrlCom.seq_num = 3;
				/* Continuous run mode */	
				priv->judge->ctrlCom.cont_run_mode = D_DD_RELC_CONT_MODE_CONT;
				priv->judge->ctrlReg.in_end_addr_en = D_DD_RELC_ADDR_DISABLE;
				priv->judge->ctrlReg.out_end_addr_en = D_DD_RELC_ADDR_DISABLE;
				priv->judge->ctrlReg.in_addr_auto_inc = D_DD_RELC_ADDR_INCRE_ON;
				priv->judge->ctrlReg.out_addr_auto_inc = D_DD_RELC_ADDR_INCRE_ON;
				priv->judge->ctrlReg.in_start_addr = 0x58100000;
				priv->judge->ctrlReg.in_end_addr = 0;
				priv->judge->ctrlReg.out_start_addr = 0x58200000;
				priv->judge->ctrlReg.out_end_addr = 0;

				// Set control common data.
				priv->judge->ret = Dd_RELC_Ctrl_Common(&(priv->judge->ctrlCom));

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Execution common control setting error. ret=%d\n", priv->judge->ret));
					return;
				}

				// Get control common data.
				memset(&(priv->judge->ctrlCom), 0, sizeof(T_DD_RELC_CTRL_CMN));
				priv->judge->ret = Dd_RELC_Get_Ctrl_Common(&(priv->judge->ctrlCom));

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Execution comon control getting error. ret=%d\n", priv->judge->ret));
					return;
				}

				Ddim_Print(("Common control information\n"));
				Ddim_Print(("# Descriptor Mode = %d\n", priv->judge->ctrlCom.desc_mode));
				Ddim_Print(("# Continuous Run Mode = %d\n", priv->judge->ctrlCom.cont_run_mode));
				Ddim_Print(("# Sequential Run Number of Times = %lu\n", priv->judge->ctrlCom.seq_num));

				// Set control register data.
				priv->judge->ret = Dd_RELC_Ctrl_Register(&(priv->judge->ctrlReg));

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Execution register control setting error. ret=%d\n", priv->judge->ret));
					return;
				}

				memset(&(priv->judge->ctrlReg), 0, sizeof(T_DD_RELC_CTRL_REG));
				// Get control register data.
				priv->judge->ret = Dd_RELC_Get_Ctrl_Register(&(priv->judge->ctrlReg));

				if ( priv->judge->ret != D_DD_RELC_OK ) {
					Ddim_Print(("Execution register control getting error. ret=%d\n", priv->judge->ret));
					return;
				}

				Ddim_Print(("Register control information\n"));
				Ddim_Print(("# Input End Address Enable = %d\n", priv->judge->ctrlReg.in_end_addr_en));
				Ddim_Print(("# Output End Address Enable = %d\n", priv->judge->ctrlReg.out_end_addr_en));
				Ddim_Print(("# Input Address Auto Increment = %d\n", priv->judge->ctrlReg.in_addr_auto_inc));
				Ddim_Print(("# Output Address Auto Increment = %d\n", priv->judge->ctrlReg.out_addr_auto_inc));
				Ddim_Print(("# Input start address = 0x%lx\n", priv->judge->ctrlReg.in_start_addr));
				Ddim_Print(("# Input end address = 0x%lx\n", priv->judge->ctrlReg.in_end_addr));
				Ddim_Print(("# Output start address = 0x%lx\n", priv->judge->ctrlReg.out_start_addr));
				Ddim_Print(("# Output end address = 0x%lx\n", priv->judge->ctrlReg.out_end_addr));

				// Start RELC macro.(Synchronization of RELC macro start)
				priv->judge->ret = Dd_RELC_Start_Sync();

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Synchronous RELC start ERR. ret=0x%x\n", priv->judge->ret));
				}else {
					Ddim_Print(("Synchronous RELC start OK\n"));
				}

				// Get RELC macro status.
				priv->judge->ret = Dd_RELC_Get_Status();

				Ddim_Print(("RELC decode status\n"));
				Ddim_Print(("# RELC macro status = 0x%x\n", priv->judge->ret));

				// Get RELC process status.
				priv->judge->ret = Dd_RELC_Get_Process_Status( &(priv->judge->decInfo) );

				if (priv->judge->ret != D_DD_RELC_OK) {
					Ddim_Print(("Execution RELC processing status getting error. ret=0x%x\n", priv->judge->ret));
					return;
				}

				Ddim_Print(("RELC processing status\n"));
				Ddim_Print(("# Number of bytes read = %d\n", priv->judge->decInfo.read_byte));
				Ddim_Print(("# Number of bytes written = %d\n", priv->judge->decInfo.write_byte));
				Ddim_Print(("# Number of processing blocks = %d\n", priv->judge->decInfo.proc_block));
				Ddim_Print(("# Decode the total number of bytes to read = %lu\n", priv->judge->decInfo.dec_total_read_bytes));
				Ddim_Print(("# Decode the total number of bytes to write = %lu\n", priv->judge->decInfo.dec_total_write_bytes));
				Ddim_Print(("# Sequential run counter = %lu\n", priv->judge->decInfo.seq_cnt));

				// Get RELC error status.
				priv->judge->ret = Dd_RELC_Get_Error_Status();

				Ddim_Print(("RELC error status information\n"));
				Ddim_Print(("# RELC error = 0x%x\n", priv->judge->ret));

				// Get RELC error number. 
				priv->judge->ret = Dd_RELC_Get_Error(); 

				Ddim_Print(("RELC error information\n"));
				Ddim_Print(("# RELC error = 0x%x\n", priv->judge->ret));

				// Close RELC macro.
				Dd_RELC_Close();

				ct_dd_relc_register_dump();
				ct_dd_relc_buffer_dump();
			}
		}
	}
    ct_dd_relc_judge(priv->judge,argc, argv );
}

CtDdRelcMain* ct_dd_relc_main_new(void) 
{
    CtDdRelcMain *self = k_object_new_with_private(CT_TYPE_DD_RELC_MAIN, sizeof(CtDdRelcMainPrivate));
	
    return self;
}
