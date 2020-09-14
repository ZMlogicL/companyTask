/**
 * @file		ct_dd_xdmac.c
 * @brief		dd_xdmac Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include <stdlib.h>
#include <string.h>
// #include "ctddxdmac.h"
#include "driver_common.h"
// #include "dd_xdmac.h"
#include "../../DeviceDriver/Exs/src/ddxdmac.h"

// #include "dd_top.h"
#include "../../Project/DeviceDriver/LSITop/src/ddtop.h"

#include "ctddxdmac.h"
#include "ctddxdmac1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdXdmac, ct_dd_xdmac);
#define CT_DD_XDMAC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdXdmacPrivate,CT_TYPE_DD_XDMAC))

struct _CtDdXdmacPrivate
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
static TDdXdmacCommon			S_GXDMAC_COMMON;

/*
DECLS
*/

static void ctXdmacResultOut(kint32 expect, kint32 ret);
static void ctXdmacTest( void );

static void ct_dd_xdmac_constructor(CtDdXdmac *self) 
{
//	CtDdXdmacPrivate *priv = CT_DD_XDMAC_GET_PRIVATE(self);

}

static void ct_dd_xdmac_destructor(CtDdXdmac *self) 
{
//	CtDdXdmacPrivate *priv = CT_DD_XDMAC_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

static void ctXdmacResultOut(kint32 expect, kint32 ret)
{
	printf("\tExpect = 0x%x\n", expect);
	printf("\tReturn = 0x%x\n", ret);
	
	if(expect == ret){
		printf("\t--- OK\n");
	}else{
		printf("\t--- NG\n");
	}
}

static void ctXdmacTest( void )
{	
	kint32 ret;
	TDdXdmacCtrl dma_ctrl_trans;
	TDdXdmacTrnsSize dma_trns_size;
	USHORT status;
	VP_CALLBACK intHandler = 0;
	
	printf("<Dd_XDMAC>\n");
	printf("\n");
	
	printf("[dd_xdmac_open]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_open(DdXdmac_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_FEVR);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("tmout < D_DDIM_USER_SEM_WAIT_FEVR:\n");
	ret = dd_xdmac_open(0, D_DDIM_USER_SEM_WAIT_FEVR - 1);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("tmout = D_DDIM_USER_SEM_WAIT_POL, pol_sem = D_DDIM_USER_E_TMOUT:\n");
	ret = dd_xdmac_open(0, D_DDIM_USER_SEM_WAIT_POL);
	ret = dd_xdmac_open(0, D_DDIM_USER_SEM_WAIT_POL);
	ctXdmacResultOut(DdXdmac_SEM_TIMEOUT, ret);
	printf("\n");
	
	printf("[dd_xdmac_close]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_close(DdXdmac_CH_NUM_MAX);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_ctrl_common]\n");
	printf("dma_common is NULL:\n");
	ret = dd_xdmac_ctrl_common(NULL);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_ctrl_trns]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_ctrl_trns(DdXdmac_CH_NUM_MAX, NULL);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("dma_ctrl_trans is NULL:\n");
	ret = dd_xdmac_ctrl_trns(0, NULL);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("dma_ctrl_trans->trns_size = 0:\n");
	dma_ctrl_trans.trnsSize = 0;
	ret = dd_xdmac_ctrl_trns(0, &dma_ctrl_trans);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_set_trns_size]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_set_trns_size(DdXdmac_CH_NUM_MAX, NULL);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("dma_trns_size is NULL:\n");
	ret = dd_xdmac_set_trns_size(0, NULL);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("dma_trns_size->trns_size = 0:\n");
	dma_trns_size.trnsSize = 0;
	ret = dd_xdmac_set_trns_size(0, &dma_trns_size);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_start_sync]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_start_sync(DdXdmac_CH_NUM_MAX, NULL, DdXdmac_WAITMODE_CPU);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("[dd_xdmac_start_sync]\n");
	printf("status is NULL:\n");
	ret = dd_xdmac_start_sync(0, NULL, DdXdmac_WAITMODE_CPU);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (DdXdmac_WAITMODE_CPU, DdXdmac_WAITMODE_EVENT):\n");
	ret = dd_xdmac_start_sync(0, &status, DdXdmac_WAITMODE_EVENT + 1);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("wait_mode = DdXdmac_WAITMODE_EVENT, twai_flg <> D_DDIM_USER_E_TMOUT:\n");
	ret = dd_xdmac_start_sync(0, &status, DdXdmac_WAITMODE_EVENT);
	ctXdmacResultOut(DdXdmac_CH_SYSTEM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_start_async]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_start_async(DdXdmac_CH_NUM_MAX);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_stop]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_stop(DdXdmac_CH_NUM_MAX);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_set_wait_time]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_set_wait_time(DdXdmac_CH_NUM_MAX, D_DDIM_WAIT_END_FOREVER);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("waitTime < D_DDIM_WAIT_END_FOREVER:\n");
	ret = dd_xdmac_set_wait_time(0, D_DDIM_WAIT_END_FOREVER - 1);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_wait_end]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_wait_end(DdXdmac_CH_NUM_MAX, &status, DdXdmac_WAITMODE_CPU);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("status is NULL:\n");
	ret = dd_xdmac_wait_end(0, NULL, DdXdmac_WAITMODE_CPU);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (DdXdmac_WAITMODE_CPU, DdXdmac_WAITMODE_EVENT):\n");
	ret = dd_xdmac_wait_end(0, &status, DdXdmac_WAITMODE_EVENT + 1);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_clear_status]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_clear_status(DdXdmac_CH_NUM_MAX);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_get_status]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_get_status(DdXdmac_CH_NUM_MAX, &status, &status, &status);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("XDMAC_status is NULL:\n");
	ret = dd_xdmac_get_status(0, NULL, &status, &status);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("transfer_status is NULL:\n");
	ret = dd_xdmac_get_status(0, &status, NULL, &status);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("interrupt_status is NULL:\n");
	ret = dd_xdmac_get_status(0, &status, &status, NULL);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_get_trns_size]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_get_trns_size(DdXdmac_CH_NUM_MAX);
	ctXdmacResultOut(0, ret);
	printf("\n");
	
	printf("[dd_xdmac_get_src_addr]\n");
	printf("ch >= D_DD_XDAMC_CH_NUM_MAX:\n");
	ret = dd_xdmac_get_src_addr(DdXdmac_CH_NUM_MAX);
	ctXdmacResultOut(0, ret);
	printf("\n");
	
	printf("[dd_xdmac_get_dst_addr]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_get_dst_addr(DdXdmac_CH_NUM_MAX);
	ctXdmacResultOut(0, ret);
	printf("\n");
	
	printf("[dd_xdmac_set_low_power]\n");
	printf("lowpower > DdXdmacXDACS_LP_ENABLE:\n");
	ret = dd_xdmac_set_low_power(DdXdmacXDACS_LP_ENABLE + 1);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Set_Source_Protect]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Set_Source_Protect(DdXdmac_CH_NUM_MAX, DdXdmacXDDPC_SP_PRIVILEGED_SECURE);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("protect_code > D_DD_xdmac_XDDPC_SP_PRIVILEGED_SECURE:\n");
	ret = Dd_XDMAC_Set_Source_Protect(0, DdXdmacXDDPC_SP_PRIVILEGED_SECURE + 1);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_set_destination_protect]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_set_destination_protect(DdXdmac_CH_NUM_MAX, DdXdmacXDDPC_DP_PRIVILEGED_SECURE);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("protect_code > DdXdmacXDDPC_SP_PRIVILEGED_SECURE:\n");
	ret = dd_xdmac_set_destination_protect(0, DdXdmacXDDPC_DP_PRIVILEGED_SECURE + 1);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_set_int_handler]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	dd_xdmac_set_int_handler(DdXdmac_CH_NUM_MAX, NULL);
	printf("\n");
	
	printf("[dd_xdmac_int_handler]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	dd_xdmac_int_handler(DdXdmac_CH_NUM_MAX);
	printf("\n");
	
	printf("[dd_xdmac_copy_sdram_sync]\n");
	printf("ch >= D_DD_xdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_copy_sdram_sync(DdXdmac_CH_NUM_MAX, 1, 1, 1, DdXdmac_WAITMODE_EVENT);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("src_addr = 0:\n");
	ret = dd_xdmac_copy_sdram_sync(0, 0, 1, 1, DdXdmac_WAITMODE_EVENT);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("dst_addr = 0:\n");
	ret = dd_xdmac_copy_sdram_sync(1, 1, 0, 1, DdXdmac_WAITMODE_EVENT);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("size = 0:\n");
	ret = dd_xdmac_copy_sdram_sync(2, 1, 1, 0, DdXdmac_WAITMODE_EVENT);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (DdXdmac_WAITMODE_CPU, DdXdmac_WAITMODE_EVENT):\n");
	ret = dd_xdmac_copy_sdram_sync(3, 1, 1, 1, DdXdmac_WAITMODE_EVENT + 1);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[dd_xdmac_copy_sdram_async]\n");
	printf("ch >= DdXdmac_CH_NUM_MAX:\n");
	ret = dd_xdmac_copy_sdram_async(DdXdmac_CH_NUM_MAX, 1, 1, 1, intHandler);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("src_addr = 0:\n");
	ret = dd_xdmac_copy_sdram_async(0, 0, 1, 1, intHandler);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("dst_addr = 0:\n");
	ret = dd_xdmac_copy_sdram_async(1, 1, 0, 1, intHandler);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("size = 0:\n");
	ret = dd_xdmac_copy_sdram_async(2, 1, 1, 0, intHandler);
	ctXdmacResultOut(DdXdmac_INPUT_PARAM_ERR, ret);
	printf("\n");
}

/*
PUBLIC//todo
*/

void ct_dd_xdmac_callback_cb(void)
{
	Ddim_Print(("XDMAC Callback\n"));
}

/**
 * @brief  Command main function for XDMAC test.
 * @param  kint32 argc	:The number of parameters
 *		   CHAR** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| P1              | P2       | P3         | P4       | P5         | P6         | P7       | P8 | P9 | P10 | P11 | Meaning                           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "open"          | ch       | waitTime  |          |            |            |          |    |    |     |     | dd_xdmac_open()                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "close"         | ch       |            |          |            |            |          |    |    |     |     | Dd_XDMAC_Close()                  |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "ctrl_cmm"      | ch       |  "0"       |  "0"     |  "0"       |            |          |    |    |     |     | Dd_XDMAC_Ctrl_Common()            |
 *	|                 |          |  "1"       |  "1"     |  "1"       |            |          |    |    |     |     |                                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "int_set"       | ch       |            |          |            |            |          |    |    |     |     | Dd_XDMAC_Set_Int_Handler()        |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "auto"          | num      |            |          |            |            |          |    |    |     |     | Continuous execution              |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+-----------------------------------+
 *	| "prm_chk"       | 0 or 1   |            |          |            |            |          |    |    |     |     | Check parameter error(XDTBC = 0)  |
 *  |                 |          |            |          |            |            |          |    |    |     |     | 0:Dd_XDMAC_Ctrl_Trns              |
 *  |                 |          |            |          |            |            |          |    |    |     |     | 1:Dd_XDMAC_Set_Trns_Size          |
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
void ct_dd_xdmac_main(CtDdXdmac* self,int argc, char** argv)
{
	// kint32				ret;
	// kuchar				ch;
	// kuchar				num;
	// kint32				waitTime;
	
	CtDdXdmac* ctDdXdmac = ct_dd_xdmac_new();
	CtDdXdmacPrivate *priv = CT_DD_XDMAC_GET_PRIVATE(ctDdXdmac);
	// check number of parameter
	if (argc > 12) {
		Ddim_Print(("The number of input parameters is exceeded!\n"));
		return;
	}
	
	DdToptwo_SET_CLKSTOP2_EXSAX(0);
	
	if (strcmp(argv[1], "open") == 0) {
		/* ch number */
		priv->ch = atoi(argv[2]);
		priv->waitTime = atoi(argv[3]);
		
		priv->ret = dd_xdmac_open(priv->ch, priv->waitTime);
		if (priv->ret == 0) {
			Ddim_Print(("XDMAC Open OK\n"));
		}
		else {
			Ddim_Print(("XDMAC Open ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "close") == 0) {
		/* ch number */
		priv->ch = atoi(argv[2]);
		
		priv->ret = dd_xdmac_close(priv->ch);
		if (priv->ret == 0) {
			Ddim_Print(("XDMAC Close OK\n"));
		}
		else {
			Ddim_Print(("XDMAC Close ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "ctrl_cmm") == 0) {
		dd_xdmac_open(0, D_DDIM_USER_SEM_WAIT_POL);
		
		// Set XE
		if (strcmp(argv[2], "0") == 0) {
			S_GXDMAC_COMMON.commonConfig.bit.XE = DdXdmacXDACS_XE_DISABLE;
		}
		else if (strcmp(argv[2], "1") == 0) {
			S_GXDMAC_COMMON.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
		}
		else {
			Ddim_Print(("Parameter ERR. P3 \n"));
			dd_xdmac_close(0);
			return;
		}
		
		// Set CP
		if (strcmp(argv[3], "0") == 0) {
			S_GXDMAC_COMMON.commonConfig.bit.CP = DdXdmacXDACS_CP_FIXED;
		}
		else if (strcmp(argv[3], "1") == 0) {
			S_GXDMAC_COMMON.commonConfig.bit.CP = DdXdmacXDACS_CP_ROTATED;
		}
		else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			dd_xdmac_close(0);
			return;
		}
		
		priv->ret = dd_xdmac_ctrl_common(&S_GXDMAC_COMMON);
		if (priv->ret == 0) {
			Ddim_Print(("XDMAC Ctrl_Common OK\n"));
		}
		else {
			Ddim_Print(("XDMAC Ctrl_Common ERR. priv->ret=0x%x\n", priv->ret));
		}
		dd_xdmac_close(0);
	}
	else if (strcmp(argv[1], "int_set") == 0){
		/* ch number */
		priv->ch = atoi(argv[2]);
		
		dd_xdmac_set_int_handler(priv->ch, ct_dd_xdmac_callback_cb);
	}
	else if (strcmp(argv[1], "auto") == 0) {
		/* ch number */
		priv->num = atoi(argv[2]);
		CtDdXdmac1* ctDdXdmac1 = ct_dd_xdmac1_new();
		ct_dd_xdmac1_set_ctddxdmac(ctDdXdmac1,ctDdXdmac);
		priv->ret = ct_dd_xdmac1_process(ctDdXdmac1);
		k_object_unref(ctDdXdmac1);
		if (priv->ret == 0) {
			Ddim_Print(("ct_dd_xdmac1_process OK\n"));
		}
		else {
			Ddim_Print(("ct_dd_xdmac1_process ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "prm_chk") == 0) {
		TDdXdmacCtrl    dma_ctrl_trns;
		TDdXdmacTrnsSize dma_trns_size;
		
		if(strcmp(argv[2], "0") == 0){
			dma_ctrl_trns.trnsSize       = 0;
			dma_ctrl_trns.srcAddr        = 0;
			dma_ctrl_trns.dstAddr        = 0;
			dma_ctrl_trns.intHandler     = NULL;
			
			priv->ret = dd_xdmac_ctrl_trns(0, &dma_ctrl_trns);
			if(priv->ret != D_DDIM_OK){
				Ddim_Print(("dd_xdmac_ctrl_trns ERR : priv->ret=0x%x\n", priv->ret));
			}
		}
		else if(strcmp(argv[2], "1") == 0){
			dma_trns_size.trnsSize       = 0;
			dma_trns_size.srcAddr        = 0;
			dma_trns_size.dstAddr        = 0;
			
			priv->ret = dd_xdmac_set_trns_size(0,&dma_trns_size);
			if(priv->ret != D_DDIM_OK){
				Ddim_Print(("dd_xdmac_set_trns_size ERR : priv->ret=0x%x\n", priv->ret));
			}
		}
		else{
			Ddim_Print(("Parameter ERR. P3 \n"));
		}
	}
	else if (strcmp(argv[1], "xdmac_test") == 0) {
		ctXdmacTest();
	}
	else {
		Ddim_Print(("please check 1st parameter!!\n"));
	}
	k_object_unref(ctDdXdmac);
	return;
}

kuchar ct_dd_xdmac_get_num(CtDdXdmac *self)
{
	CtDdXdmacPrivate *priv = CT_DD_XDMAC_GET_PRIVATE(self);
	return priv->num;
}

CtDdXdmac* ct_dd_xdmac_new(void) 
{
    CtDdXdmac *self = k_object_new_with_private(CT_TYPE_DD_XDMAC, sizeof(CtDdXdmacPrivate));
    return self;
}