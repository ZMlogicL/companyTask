/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdRelc类
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
#include "ctddrelcmain.h"
#include "ctddrelc.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdRelc, ct_dd_relc);
#define CT_DD_RELC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdRelcPrivate,CT_TYPE_DD_RELC))

struct _CtDdRelcPrivate
{
	CtDdRelcMain *main;
};

static void ct_dd_relc_constructor(CtDdRelc *self) 
{
	CtDdRelcPrivate *priv = CT_DD_RELC_GET_PRIVATE(self);

    priv->main = ct_dd_relc_main_new();
}

static void ct_dd_relc_destructor(CtDdRelc *self) 
{
	CtDdRelcPrivate *priv = CT_DD_RELC_GET_PRIVATE(self);

	k_object_unref(priv->main);
    priv->main = NULL;
}

/*
 *PUBLIC
 */
void ct_dd_relc_register_dump( void )
{
#ifdef PC_DEBUG
	Ddim_Print(("RELC REGISTER INFO.\n"));
	Ddim_Print(("IO_RELC.RELC_RESET.bit.SRST        = %d\n",	IO_RELC.RELC_RESET.bit.SRST));
	Ddim_Print(("IO_RELC.RELC_MODE1.bit.PRUN        = %d\n",	IO_RELC.RELC_MODE1.bit.PRUN));
	Ddim_Print(("IO_RELC.RELC_MODE1.bit.CRMD        = %d\n",	IO_RELC.RELC_MODE1.bit.CRMD));
	Ddim_Print(("IO_RELC.RELC_MODE1.bit.DSMD        = %d\n",	IO_RELC.RELC_MODE1.bit.DSMD));
	Ddim_Print(("IO_RELC.RELC_MODE2.bit.IMAX        = %d\n",	IO_RELC.RELC_MODE2.bit.IMAX));
	Ddim_Print(("IO_RELC.RELC_MODE2.bit.OMAX        = %d\n",	IO_RELC.RELC_MODE2.bit.OMAX));
	Ddim_Print(("IO_RELC.RELC_MODE2.bit.IAAI        = %d\n",	IO_RELC.RELC_MODE2.bit.IAAI));
	Ddim_Print(("IO_RELC.RELC_MODE2.bit.OAAI        = %d\n",	IO_RELC.RELC_MODE2.bit.OAAI));
	Ddim_Print(("IO_RELC.RELC_INT_EN.bit.SINT       = %d\n",	IO_RELC.RELC_INT_EN.bit.SINT));
	Ddim_Print(("IO_RELC.RELC_INT_EN.bit.FINT       = %d\n",	IO_RELC.RELC_INT_EN.bit.FINT));
	Ddim_Print(("IO_RELC.RELC_INT_EN.bit.EINT       = %d\n",	IO_RELC.RELC_INT_EN.bit.EINT));
	Ddim_Print(("IO_RELC.RELC_INT_EN.bit.CINT       = %d\n",	IO_RELC.RELC_INT_EN.bit.CINT));
	Ddim_Print(("IO_RELC.RELC_INT_ST.bit.__SINS     = %d\n",	IO_RELC.RELC_INT_ST.bit.__SINS));
	Ddim_Print(("IO_RELC.RELC_INT_ST.bit.__FINS     = %d\n",	IO_RELC.RELC_INT_ST.bit.__FINS));
	Ddim_Print(("IO_RELC.RELC_INT_ST.bit.__EINS     = %d\n",	IO_RELC.RELC_INT_ST.bit.__EINS));
	Ddim_Print(("IO_RELC.RELC_INT_ST.bit.__CINS     = %d\n",	IO_RELC.RELC_INT_ST.bit.__CINS));
	Ddim_Print(("IO_RELC.RELC_STATUS.bit.RUNS       = %d\n",	IO_RELC.RELC_STATUS.bit.RUNS));
	Ddim_Print(("IO_RELC.RELC_STATUS.bit.SLPS       = %d\n",	IO_RELC.RELC_STATUS.bit.SLPS));
	Ddim_Print(("IO_RELC.RELC_STATUS.bit.FINS       = %d\n",	IO_RELC.RELC_STATUS.bit.FINS));
	Ddim_Print(("IO_RELC.RELC_STATUS.bit.SRES       = %d\n",	IO_RELC.RELC_STATUS.bit.SRES));
	Ddim_Print(("IO_RELC.RELC_STATUS.bit.EFLG       = %d\n",	IO_RELC.RELC_STATUS.bit.EFLG));
	Ddim_Print(("IO_RELC.RELC_IN_START_ADDR         = %08LX\n",	IO_RELC.RELC_IN_START_ADDR));
	Ddim_Print(("IO_RELC.RELC_IN_END_ADDR           = %08LX\n",	IO_RELC.RELC_IN_END_ADDR));
	Ddim_Print(("IO_RELC.RELC_OUT_START_ADDR        = %08LX\n",	IO_RELC.RELC_OUT_START_ADDR));
	Ddim_Print(("IO_RELC.RELC_OUT_END_ADDR          = %08LX\n",	IO_RELC.RELC_OUT_END_ADDR));
	Ddim_Print(("IO_RELC.RELC_DESCRIPTOR_ADDR       = %08LX\n",	IO_RELC.RELC_DESCRIPTOR_ADDR));
	Ddim_Print(("IO_RELC.RELC_SEQ_NUM               = %d\n",	IO_RELC.RELC_SEQ_NUM));
	Ddim_Print(("IO_RELC.RELC_SEQ_CNT               = %d\n",	IO_RELC.RELC_SEQ_CNT));
	Ddim_Print(("IO_RELC.RELC_BUF_SIZE.bit.IBFS     = %d\n",	IO_RELC.RELC_BUF_SIZE.bit.IBFS));
	Ddim_Print(("IO_RELC.RELC_BUF_SIZE.bit.RBFS     = %d\n",	IO_RELC.RELC_BUF_SIZE.bit.RBFS));
	Ddim_Print(("IO_RELC.RELC_ERROR_NUM.bit.ENUM    = %d\n",	IO_RELC.RELC_ERROR_NUM.bit.ENUM));
	Ddim_Print(("IO_RELC.RELC_READ_BYTE.bit.DRNM    = %d\n",	IO_RELC.RELC_READ_BYTE.bit.DRNM));
	Ddim_Print(("IO_RELC.RELC_WRITE_BYTE.bit.DWNM   = %d\n",	IO_RELC.RELC_WRITE_BYTE.bit.DWNM));
	Ddim_Print(("IO_RELC.RELC_BLOCK.bit.BLKN        = %d\n",	IO_RELC.RELC_BLOCK.bit.BLKN));
	Ddim_Print(("IO_RELC.RELC_INPUT_BYTE            = %08LX\n",	IO_RELC.RELC_INPUT_BYTE));
	Ddim_Print(("IO_RELC.RELC_OUTPUT_BYTE           = %08LX\n",	IO_RELC.RELC_OUTPUT_BYTE));
	Ddim_Print(("IO_RELC.RELC_INPUT_BUF_DATA_MIRROR = %08LX\n",	IO_RELC.RELC_INPUT_BUF_DATA_MIRROR));
	Ddim_Print(("IO_RELC.RELC_INPUT_BUF_DATA        = %08LX\n",	IO_RELC.RELC_INPUT_BUF_DATA));
	Ddim_Print(("IO_RELC.RELC_REF_BUF_DATA          = %08LX\n",	IO_RELC.RELC_REF_BUF_DATA));
#endif
}

void ct_dd_relc_cmd_cb(kuint32 int_factor)
{
	switch ( int_factor ) {
		case D_DD_RELC_ERR:
			//Error interrupt
			Ddim_Print(("[RELC INT] Error interrupt \n"));
			break;

		case D_DD_RELC_SLEEP:
			// Sleep interrupt
			Ddim_Print(("[RELC INT] Sleep interrupt \n"));
			break;

		case D_DD_RELC_FINISH:
			// Finish interrupt
			Ddim_Print(("[RELC INT] Finish interrupt \n"));
			break;

		case D_DD_RELC_CR_FINISH:
			// Continuous run finish interrupt
			Ddim_Print(("[RELC INT] Continuous run finish interrupt \n"));
			break;

		default:
			// Unknown factor
			Ddim_Print(("[RELC INT] Unknown factor. factor=%d \n", int_factor));
			break;
	}
}

void ct_dd_relc_ps_sim(CtDdRelc *self)
{
	CtDdRelcPrivate *priv = CT_DD_RELC_GET_PRIVATE(self);
	kint32	argc;
	kchar*	argv[ 32 ];

	argv[ 0 ] = (kchar*)( "relc" );

	Ddim_Print(("[CT]01-01-1 : Dd_RELC_Init()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "init" );
	argv[ 2 ] = (kchar*)( "F" );
	argv[ 3 ] = (kchar*)( "F" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-2 : Dd_RELC_Open()\n"));
	argc = 2;
	argv[ 1 ] = (kchar*)( "open" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-3 : Dd_RELC_Close()\n"));
	argc = 2;
	argv[ 1 ] = (kchar*)( "close" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-4 : Dd_RELC_Start_Sync()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "start" );
	argv[ 2 ] = (kchar*)( "sync" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-5 : Dd_RELC_Start_Async()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "start" );
	argv[ 2 ] = (kchar*)( "async" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-6 : Dd_RELC_Stop()\n"));
	argc = 2;
	argv[ 1 ] = (kchar*)( "stop" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-7 : Dd_RELC_Ctrl_Common()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "ctrlcomm" );
	argv[ 2 ] = (kchar*)( "reg" );
	argv[ 3 ] = (kchar*)( "nmod" );
	argv[ 4 ] = (kchar*)( "8" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-8 : Dd_RELC_Ctrl_Common()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "ctrlcomm" );
	argv[ 2 ] = (kchar*)( "desc" );
	argv[ 3 ] = (kchar*)( "cmod" );
	argv[ 4 ] = (kchar*)( "256" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-9 : Dd_RELC_Ctrl_Register()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "ctrlcomm" );
	argv[ 2 ] = (kchar*)( "reg" );
	argv[ 3 ] = (kchar*)( "nmod" );
	argv[ 4 ] = (kchar*)( "8" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));
	argc = 8;
	argv[ 1 ] = (kchar*)( "ctrlreg" );
	argv[ 2 ] = (kchar*)( "imaxd" );
	argv[ 3 ] = (kchar*)( "omaxd" );
	argv[ 4 ] = (kchar*)( "0x40105000" );
	argv[ 5 ] = (kchar*)( "0x40107000" );
	argv[ 6 ] = (kchar*)( "0x40207000" );
	argv[ 7 ] = (kchar*)( "0x4020B000" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-10 : Dd_RELC_Ctrl_Register()\n"));
	argc = 8;
	argv[ 1 ] = (kchar*)( "ctrlreg" );
	argv[ 2 ] = (kchar*)( "imaxe" );
	argv[ 3 ] = (kchar*)( "omaxe" );
	argv[ 4 ] = (kchar*)( "0x40105000" );
	argv[ 5 ] = (kchar*)( "0x40106000" );
	argv[ 6 ] = (kchar*)( "0x40207000" );
	argv[ 7 ] = (kchar*)( "0x40209000" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-11 : Dd_RELC_Ctrl_Descriptor()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "ctrldesc" );
	argv[ 2 ] = (kchar*)( "0x40408000" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-12 : Dd_RELC_Set_In_Start_Addr()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "set" );
	argv[ 2 ] = (kchar*)( "in_sta_addr" );
	argv[ 3 ] = (kchar*)( "0x40302000" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-13 : Dd_RELC_Set_In_End_Addr()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "set" );
	argv[ 2 ] = (kchar*)( "in_end_addr" );
	argv[ 3 ] = (kchar*)( "0x40103000" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-14 : Dd_RELC_Set_Out_Start_Addr()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "set" );
	argv[ 2 ] = (kchar*)( "out_sta_addr" );
	argv[ 3 ] = (kchar*)( "0x40802000" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-15 : Dd_RELC_Set_Out_End_Addr()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "set" );
	argv[ 2 ] = (kchar*)( "out_end_addr" );
	argv[ 3 ] = (kchar*)( "0x40907012" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-16 : Dd_RELC_Get_Ctrl_Common()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "ctrlcomm" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-17 : Dd_RELC_Get_Ctrl_Register()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "ctrlreg" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-18 : Dd_RELC_Get_Ctrl_Descriptor()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "ctrldesc" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-19 : Dd_RELC_Get_Status()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "msta" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-20 : Dd_RELC_Get_Sleep_Reason()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "sleep" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-21 : Dd_RELC_Get_Error_Status()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "errsta" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-22 : Dd_RELC_Get_Error()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "err" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-23 : Dd_RELC_Get_Process_Status()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "psta" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-24 : Dd_RELC_Get_Buf_Size()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "bufsize" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));
/*
	Ddim_Print(("[CT]01-01-25 : Dd_RELC_Set_In_Buf_Data()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "set" );
	argv[ 2 ] = (kchar*)( "inbuf" );
	argv[ 3 ] = (kchar*)( "0x3A001800" );
	argv[ 4 ] = (kchar*)( "8192" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-26 : Dd_RELC_Set_In_Buf_Data_Mirror()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "set" );
	argv[ 2 ] = (kchar*)( "inbufm" );
	argv[ 3 ] = (kchar*)( "0x44900000" );
	argv[ 4 ] = (kchar*)( "512" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-27 : Dd_RELC_Set_Ref_Buf_Data()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "set" );
	argv[ 2 ] = (kchar*)( "relbuf" );
	argv[ 3 ] = (kchar*)( "0x44800000" );
	argv[ 4 ] = (kchar*)( "256" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-28 : Dd_RELC_Get_In_Buf_Data()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "inbuf" );
	argv[ 3 ] = (kchar*)( "0x44900000" );
	argv[ 4 ] = (kchar*)( "512" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-29 : Dd_RELC_Get_In_Buf_Data_Mirror()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "inbufm" );
	argv[ 3 ] = (kchar*)( "0x44A00000" );
	argv[ 4 ] = (kchar*)( "1024" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-30 : Dd_RELC_Get_Ref_Buf_Data()\n"));
	argc = 5;
	argv[ 1 ] = (kchar*)( "get" );
	argv[ 2 ] = (kchar*)( "relbuf" );
	argv[ 3 ] = (kchar*)( "0x44B00000" );
	argv[ 4 ] = (kchar*)( "256" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-31 : Dd_RELC_Utility_Register()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "norm" );
	argv[ 2 ] = (kchar*)( "async" );
	argv[ 3 ] = (kchar*)( "1" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-32 : Dd_RELC_Utility_Register()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "norm" );
	argv[ 2 ] = (kchar*)( "async" );
	argv[ 3 ] = (kchar*)( "2" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-33 : Dd_RELC_Utility_Descriptor()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "desc" );
	argv[ 2 ] = (kchar*)( "async" );
	argv[ 3 ] = (kchar*)( "1" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-34 : Dd_RELC_Utility_Descriptor()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "desc" );
	argv[ 2 ] = (kchar*)( "async" );
	argv[ 3 ] = (kchar*)( "2" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-35 : Dd_RELC_Utility_Register()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "norm" );
	argv[ 2 ] = (kchar*)( "sync" );
	argv[ 3 ] = (kchar*)( "1" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-36 : Dd_RELC_Utility_Register()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "norm" );
	argv[ 2 ] = (kchar*)( "sync" );
	argv[ 3 ] = (kchar*)( "2" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-37 : Dd_RELC_Utility_Descriptor()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "desc" );
	argv[ 2 ] = (kchar*)( "sync" );
	argv[ 3 ] = (kchar*)( "1" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-01-38 : Dd_RELC_Utility_Descriptor()\n"));
	argc = 4;
	argv[ 1 ] = (kchar*)( "desc" );
	argv[ 2 ] = (kchar*)( "sync" );
	argv[ 3 ] = (kchar*)( "2" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));
*/
	Ddim_Print(("[CT]01-01-39 : Dd_RELC_Int_Handler()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "inthdr" );
	argv[ 2 ] = (kchar*)( "1" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));
	argv[ 2 ] = (kchar*)( "2" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));
	argv[ 2 ] = (kchar*)( "3" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));
	argv[ 2 ] = (kchar*)( "4" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-1 : Dd_RELC_Open()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "open" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-2 : Dd_RELC_Ctrl_Common()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "ctrlcomm" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-3 : Dd_RELC_Ctrl_Register()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "ctrlreg" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-4 : Dd_RELC_Ctrl_Descriptor()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "ctrldesc" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-5 : Dd_RELC_Set_In_Start_Addr()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "set_in_sta_addr" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-6 : Dd_RELC_Set_In_End_Addr()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "set_in_end_addr" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-7 : Dd_RELC_Set_Out_Start_Addr()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "set_out_sta_addr" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-8 : Dd_RELC_Set_Out_End_Addr()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "set_out_end_addr" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-9 : Dd_RELC_Set_In_Buf_Data()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "set_inbuf" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-10 : Dd_RELC_Set_In_Buf_Data_Mirror()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "set_inbufm" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-11 : Dd_RELC_Set_Ref_Buf_Data()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "set_refbuf" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-12 : Dd_RELC_Get_Ctrl_Common()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_ctrlcomm" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-13 : Dd_RELC_Get_Ctrl_Register()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_ctrlreg" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-14 : Dd_RELC_Get_Ctrl_Descriptor()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_ctrldesc" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-15 : Dd_RELC_Get_Status()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_psta" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-16 : Dd_RELC_Get_Buf_Size()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_bufsize1" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-17 : Dd_RELC_Get_Buf_Size()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_bufsize2" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-18 : Dd_RELC_Get_In_Buf_Data()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_inbuf" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-19 : Dd_RELC_Get_In_Buf_Data_Mirror()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_inbufm" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));

	Ddim_Print(("[CT]01-02-20 : Dd_RELC_Get_Ref_Buf_Data()\n"));
	argc = 3;
	argv[ 1 ] = (kchar*)( "err" );
	argv[ 2 ] = (kchar*)( "get_refbuf" );
	ct_dd_relc_main(priv->main, argc, argv);
	Ddim_Print(("\n"));
}

CtDdRelc* ct_dd_relc_new(void) 
{
    CtDdRelc *self = k_object_new_with_private(CT_TYPE_DD_RELC, sizeof(CtDdRelcPrivate));

    return self;
}
