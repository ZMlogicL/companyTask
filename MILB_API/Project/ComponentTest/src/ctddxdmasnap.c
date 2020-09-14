/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liudong
*@brief               :CtDdXdmasnap类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/
#include <stdlib.h>
#include <string.h>
#include "ctddxdmasnap.h"
#include "driver_common.h"
// #include "dd_xdmasnap.h"
#include "../../DeviceDriver/ARM/src/ddxdmasnap.h"

#include "ctddxdmasnap.h"
#include "ctddxdmasnap1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdXdmasnap, ct_dd_xdmasnap);
#define CT_DD_XDMASNAP_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdXdmasnapPrivate,CT_TYPE_DD_XDMASNAP))

struct _CtDdXdmasnapPrivate
{
	kint32				ret;
	kuchar				ch;
	kuchar				num;
	kint32				waitTime;
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static TDdXdmasnapCommon			S_GXDMASNAP_COMMON;

/*
DECLS
*/

static void ctXdmacSnapResultOut(kint32 expect, kint32 ret);
static void ctXdmaSnapTest( void );

static void ct_dd_xdmasnap_constructor(CtDdXdmasnap *self) 
{
//	CtDdXdmasnapPrivate *priv = CT_DD_XDMASNAP_GET_PRIVATE(self);
}

static void ct_dd_xdmasnap_destructor(CtDdXdmasnap *self) 
{
//	CtDdXdmasnapPrivate *priv = CT_DD_XDMASNAP_GET_PRIVATE(self);
}

/*
IMPL//todo
*/

static void ctXdmacSnapResultOut(kint32 expect, kint32 ret)
{
	printf("\tExpect = 0x%x\n", expect);
	printf("\tReturn = 0x%x\n", ret);
	
	if(expect == ret){
		printf("\t--- OK\n");
	}else{
		printf("\t--- NG\n");
	}
}

static void ctXdmaSnapTest( void )
{	
	kint32 ret;
	TDdXdmasnapCtrl dma_ctrl_trans;
	DdXdmasnapTrnsSize dma_trns_size;
	USHORT status;
	VP_CALLBACK intHandler = 0;
	
	printf("<Dd_XDMASNAP>\n");
	printf("\n");
	
	printf("[dd_xdmasnap_open]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_open(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_FEVR);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("tmout < D_DDIM_USER_SEM_WAIT_FEVR:\n");
	ret = dd_xdmasnap_open(0, D_DDIM_USER_SEM_WAIT_FEVR - 1);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("tmout = D_DDIM_USER_SEM_WAIT_POL, pol_sem = D_DDIM_USER_E_TMOUT:\n");
	ret = dd_xdmasnap_open(0, D_DDIM_USER_SEM_WAIT_POL);
	ret = dd_xdmasnap_open(0, D_DDIM_USER_SEM_WAIT_POL);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_SEM_TIMEOUT, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_close]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_close(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_ctrl_common]\n");
	printf("dma_common is NULL:\n");
	ret = dd_xdmasnap_ctrl_common(NULL);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_ctrl_trns]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_ctrl_trns(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, NULL);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dma_ctrl_trans is NULL:\n");
	ret = dd_xdmasnap_ctrl_trns(0, NULL);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dma_ctrl_trans->trns_size = 0:\n");
	dma_ctrl_trans.trns_size = 0;
	ret = dd_xdmasnap_ctrl_trns(0, &dma_ctrl_trans);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_set_trns_size]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_set_trns_size(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, NULL);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dma_trns_size is NULL:\n");
	ret = dd_xdmasnap_set_trns_size(0, NULL);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dma_trns_size->trns_size = 0:\n");
	dma_trns_size.trns_size = 0;
	ret = dd_xdmasnap_set_trns_size(0, &dma_trns_size);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_start_sync]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_start_sync(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, NULL, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("[dd_xdmasnap_start_sync]\n");
	printf("status is NULL:\n");
	ret = dd_xdmasnap_start_sync(0, NULL, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT):\n");
	ret = dd_xdmasnap_start_sync(0, &status, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT + 1);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("wait_mode = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT, twai_flg <> D_DDIM_USER_E_TMOUT:\n");
	ret = dd_xdmasnap_start_sync(0, &status, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_start_async]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_start_async(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_stop]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_stop(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_set_wait_time]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_set_wait_time(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, D_DDIM_WAIT_END_FOREVER);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("waitTime < D_DDIM_WAIT_END_FOREVER:\n");
	ret = dd_xdmasnap_set_wait_time(0, D_DDIM_WAIT_END_FOREVER - 1);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_wait_end]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_wait_end(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, &status, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("status is NULL:\n");
	ret = dd_xdmasnap_wait_end(0, NULL, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT):\n");
	ret = dd_xdmasnap_wait_end(0, &status, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT + 1);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_clear_status]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_clear_status(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_get_status]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_get_status(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, &status, &status, &status);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("xdmac_status is NULL:\n");
	ret = dd_xdmasnap_get_status(0, NULL, &status, &status);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("transfer_status is NULL:\n");
	ret = dd_xdmasnap_get_status(0, &status, NULL, &status);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("interrupt_status is NULL:\n");
	ret = dd_xdmasnap_get_status(0, &status, &status, NULL);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_get_trns_size]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_get_trns_size(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(0, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_get_src_addr]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_get_src_addr(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(0, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_get_dst_addr]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_get_dst_addr(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(0, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_set_low_power]\n");
	printf("lowpower > DdXdmasnap_D_DD_XDMASNAP_XDACS_LP_ENABLE:\n");
	ret = dd_xdmasnap_set_low_power(DdXdmasnap_D_DD_XDMASNAP_XDACS_LP_ENABLE + 1);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_set_source_protect]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_set_source_protect(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("protect_code > DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE:\n");
	ret = dd_xdmasnap_set_source_protect(0, DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE + 1);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_set_destination_protect]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_set_destination_protect(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, DdXdmasnap_D_DD_XDMASNAP_XDDPC_DP_PRIVILEGED_SECURE);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("protect_code > DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE:\n");
	ret = dd_xdmasnap_set_destination_protect(0, DdXdmasnap_D_DD_XDMASNAP_XDDPC_DP_PRIVILEGED_SECURE + 1);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_set_int_handler]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	dd_xdmasnap_set_int_handler(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, NULL);
	printf("\n");
	
	printf("[dd_xdmasnap_int_handler]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	dd_xdmasnap_int_handler(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX);
	printf("\n");
	
	printf("[dd_xdmasnap_copy_sdram_sync]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_copy_sdram_sync(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, 1, 1, 1, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("src_addr = 0:\n");
	ret = dd_xdmasnap_copy_sdram_sync(0, 0, 1, 1, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dst_addr = 0:\n");
	ret = dd_xdmasnap_copy_sdram_sync(1, 1, 0, 1, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("size = 0:\n");
	ret = dd_xdmasnap_copy_sdram_sync(2, 1, 1, 0, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT):\n");
	ret = dd_xdmasnap_copy_sdram_sync(3, 1, 1, 1, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT + 1);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmasnap_copy_sdram_async]\n");
	printf("ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = dd_xdmasnap_copy_sdram_async(DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX, 1, 1, 1, intHandler);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("src_addr = 0:\n");
	ret = dd_xdmasnap_copy_sdram_async(0, 0, 1, 1, intHandler);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dst_addr = 0:\n");
	ret = dd_xdmasnap_copy_sdram_async(1, 1, 0, 1, intHandler);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("size = 0:\n");
	ret = dd_xdmasnap_copy_sdram_async(2, 1, 1, 0, intHandler);
	ctXdmacSnapResultOut(DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
}	

/*
PUBLIC//todo
*/

void ct_dd_xdmasnap_callback_cb(void)
{
	Ddim_Print(("XDMASNAP Callback\n"));
}

/**
 * @brief  Command main function for XDMASNAP test.
 * @param  kint32 argc	:The number of parameters
 *		   CHAR** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| P1              | P2       | P3         | P4       | P5         | P6         | P7       | P8 | P9 | P10 | P11 | Meaning                           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "open"          | ch       | waitTime  |          |            |            |          |    |    |     |     | Dd_XDMASNAP_Open()               |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "close"         | ch       |            |          |            |            |          |    |    |     |     | Dd_XDMASNAP_Close()              |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "ctrl_cmm"      | ch       |  "0"       |  "0"     |  "0"       |            |          |    |    |     |     | Dd_XDMASNAP_Ctrl_Common()        |
 *	|                 |          |  "1"       |  "1"     |  "1"       |            |          |    |    |     |     |                                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "int_set"       | ch       |            |          |            |            |          |    |    |     |     | Dd_XDMASNAP_Set_Int_Handler()    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "auto"          | num      |            |          |            |            |          |    |    |     |     | Continuous execution              |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "prm_chk"       | 0 or 1   |            |          |            |            |          |    |    |     |     | Check parameter error(XDTBC = 0)  |
 *  |                 |          |            |          |            |            |          |    |    |     |     | 0:Dd_XDMASNAP_Ctrl_Trns           |
 *  |                 |          |            |          |            |            |          |    |    |     |     | 1:Dd_XDMASNAP_Set_Trns_Size       |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *
 *			ch			:	0          - 3
 *			rc			:	ena / dis
 *			rs			:	ena / dis
 *			rd			:	ena / dis
 *			sp			:	0          - 15
 *			dp			:	0          - 15
 *			size		:	0          - 0xFFFFFFFF
 *			src_addr	:	0          - 0xFFFFFFFF
 *			dst_addr	:	0          - 0xFFFFFFFF
 *			IntHandler  :	Callback Function Pointer
 *			num			:	Test ID
 *
 * @return void
 */
void ct_dd_xdmasnap_main(CtDdXdmasnap* self,int argc, char** argv)
{
	// kint32				ret;
	// kuchar				ch;
	// kuchar				num;
	// kint32				waitTime;
	
	CtDdXdmasnap* ctDdXdmasnap = ct_dd_xdmasnap_new();
	CtDdXdmasnapPrivate *priv = CT_DD_XDMASNAP_GET_PRIVATE(ctDdXdmasnap);

	// check number of parameter
	if (argc > 12) {
		Ddim_Print(("The number of input parameters is exceeded!\n"));
		return;
	}
	
	if (strcmp(argv[1], "open") == 0) {
		/* ch number */
		priv->ch = atoi(argv[2]);
		priv->waitTime = atoi(argv[3]);
		
		priv->ret = dd_xdmasnap_open(priv->ch, priv->waitTime);
		if (priv->ret == 0) {
			Ddim_Print(("XDMASNAP Open OK\n"));
		}
		else {
			Ddim_Print(("XDMASNAP Open ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "close") == 0) {
		/* ch number */
		priv->ch = atoi(argv[2]);
		
		priv->ret = dd_xdmasnap_close(priv->ch);
		if (priv->ret == 0) {
			Ddim_Print(("XDMASNAP Close OK\n"));
		}
		else {
			Ddim_Print(("XDMASNAP Close ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "ctrl_cmm") == 0) {
		// Set XE
		if (strcmp(argv[2], "0") == 0) {
			S_GXDMASNAP_COMMON.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_DISABLE;
		}
		else if (strcmp(argv[2], "1") == 0) {
			S_GXDMASNAP_COMMON.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
		}
		else {
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}
		
		// Set CP
		if (strcmp(argv[3], "0") == 0) {
			S_GXDMASNAP_COMMON.common_config.bit.CP = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED;
		}
		else if (strcmp(argv[3], "1") == 0) {
			S_GXDMASNAP_COMMON.common_config.bit.CP = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_ROTATED;
		}
		else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}
		
		priv->ret = dd_xdmasnap_ctrl_common(&S_GXDMASNAP_COMMON);
		if (priv->ret == 0) {
			Ddim_Print(("XDMASNAP Ctrl_Common OK\n"));
		}
		else {
			Ddim_Print(("XDMASNAP Ctrl_Common ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "int_set") == 0){
		/* ch number */
		priv->ch = atoi(argv[2]);
		
		dd_xdmasnap_set_int_handler(priv->ch, ct_dd_xdmasnap_callback_cb);
	}
	else if (strcmp(argv[1], "auto") == 0) {
		/* ch number */
		priv->num = atoi(argv[2]);
		
		CtDdXdmasnap1* ctDdXdmasnap1 = ct_dd_xdmasnap1_new();
		ct_dd_xdmasnap1_set_ctddxdmasnap(ctDdXdmasnap1,ctDdXdmasnap);

		priv->ret = ct_dd_xdmasnap1_process(ctDdXdmasnap1);
		k_object_unref(ctDdXdmasnap1);
		if (priv->ret == 0) {
			Ddim_Print(("ct_dd_xdmasnap1_process OK\n"));
		}
		else {
			Ddim_Print(("ct_dd_xdmasnap1_process ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "prm_chk") == 0) {
		TDdXdmasnapCtrl    dma_ctrl_trns;
		DdXdmasnapTrnsSize dma_trns_size;
		
		if(strcmp(argv[2], "0") == 0){
			dma_ctrl_trns.trns_size       = 0;
			dma_ctrl_trns.src_addr        = 0;
			dma_ctrl_trns.dst_addr        = 0;
			dma_ctrl_trns.int_handler     = NULL;
			
			priv->ret = dd_xdmasnap_ctrl_trns(0, &dma_ctrl_trns);
			if(priv->ret != D_DDIM_OK){
				Ddim_Print(("dd_xdmasnap_ctrl_trns ERR : priv->ret=0x%x\n", priv->ret));
			}
		}
		else if(strcmp(argv[2], "1") == 0){
			dma_trns_size.trns_size       = 0;
			dma_trns_size.src_addr        = 0;
			dma_trns_size.dst_addr        = 0;
			
			priv->ret = dd_xdmasnap_set_trns_size(0,&dma_trns_size);
			if(priv->ret != D_DDIM_OK){
				Ddim_Print(("dd_xdmasnap_set_trns_size ERR : priv->ret=0x%x\n", priv->ret));
			}
		}
		else{
			Ddim_Print(("Parameter ERR. P3 \n"));
		}
	}
	else if (strcmp(argv[1], "xdmac_test") == 0) {
		ctXdmaSnapTest();
	}
	else {
		Ddim_Print(("please check 1st parameter!!\n"));
	}
	k_object_unref(ctDdXdmasnap);
	return;
}

kuchar ct_dd_xdmasnap_get_num(CtDdXdmasnap *self)
{
	CtDdXdmasnapPrivate *priv = CT_DD_XDMASNAP_GET_PRIVATE(self);
	return priv->num;
}

CtDdXdmasnap* ct_dd_xdmasnap_new(void) 
{
    CtDdXdmasnap *self = k_object_new_with_private(CT_TYPE_DD_XDMASNAP, sizeof(CtDdXdmasnapPrivate));
    return self;
}
