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
#include "dd_xdmasnap.h"

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
static T_DD_XDMASNAP_COMMON			S_GXDMASNAP_COMMON;

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
	T_DD_XDMASNAP_CTRL dma_ctrl_trans;
	T_DD_XDMASNAP_TRNS_SIZE dma_trns_size;
	USHORT status;
	VP_CALLBACK intHandler = 0;
	
	printf("<Dd_XDMASNAP>\n");
	printf("\n");
	
	printf("[Dd_XDMASNAP_Open]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Open(D_DD_XDMASNAP_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_FEVR);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("tmout < D_DDIM_USER_SEM_WAIT_FEVR:\n");
	ret = Dd_XDMASNAP_Open(0, D_DDIM_USER_SEM_WAIT_FEVR - 1);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("tmout = D_DDIM_USER_SEM_WAIT_POL, pol_sem = D_DDIM_USER_E_TMOUT:\n");
	ret = Dd_XDMASNAP_Open(0, D_DDIM_USER_SEM_WAIT_POL);
	ret = Dd_XDMASNAP_Open(0, D_DDIM_USER_SEM_WAIT_POL);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_SEM_TIMEOUT, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Close]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Close(D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Ctrl_Common]\n");
	printf("dma_common is NULL:\n");
	ret = Dd_XDMASNAP_Ctrl_Common(NULL);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Ctrl_Trns]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Ctrl_Trns(D_DD_XDMASNAP_CH_NUM_MAX, NULL);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dma_ctrl_trans is NULL:\n");
	ret = Dd_XDMASNAP_Ctrl_Trns(0, NULL);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dma_ctrl_trans->trns_size = 0:\n");
	dma_ctrl_trans.trns_size = 0;
	ret = Dd_XDMASNAP_Ctrl_Trns(0, &dma_ctrl_trans);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Set_Trns_Size]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Set_Trns_Size(D_DD_XDMASNAP_CH_NUM_MAX, NULL);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dma_trns_size is NULL:\n");
	ret = Dd_XDMASNAP_Set_Trns_Size(0, NULL);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dma_trns_size->trns_size = 0:\n");
	dma_trns_size.trns_size = 0;
	ret = Dd_XDMASNAP_Set_Trns_Size(0, &dma_trns_size);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Start_Sync]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Start_Sync(D_DD_XDMASNAP_CH_NUM_MAX, NULL, D_DD_XDMASNAP_WAITMODE_CPU);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("[Dd_XDMASNAP_Start_Sync]\n");
	printf("status is NULL:\n");
	ret = Dd_XDMASNAP_Start_Sync(0, NULL, D_DD_XDMASNAP_WAITMODE_CPU);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (D_DD_XDMASNAP_WAITMODE_CPU, D_DD_XDMASNAP_WAITMODE_EVENT):\n");
	ret = Dd_XDMASNAP_Start_Sync(0, &status, D_DD_XDMASNAP_WAITMODE_EVENT + 1);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("wait_mode = D_DD_XDMASNAP_WAITMODE_EVENT, twai_flg <> D_DDIM_USER_E_TMOUT:\n");
	ret = Dd_XDMASNAP_Start_Sync(0, &status, D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_SYSTEM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Start_Async]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Start_Async(D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Stop]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Stop(D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Set_Wait_Time]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Set_Wait_Time(D_DD_XDMASNAP_CH_NUM_MAX, D_DDIM_WAIT_END_FOREVER);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("waitTime < D_DDIM_WAIT_END_FOREVER:\n");
	ret = Dd_XDMASNAP_Set_Wait_Time(0, D_DDIM_WAIT_END_FOREVER - 1);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Wait_End]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Wait_End(D_DD_XDMASNAP_CH_NUM_MAX, &status, D_DD_XDMASNAP_WAITMODE_CPU);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("status is NULL:\n");
	ret = Dd_XDMASNAP_Wait_End(0, NULL, D_DD_XDMASNAP_WAITMODE_CPU);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (D_DD_XDMASNAP_WAITMODE_CPU, D_DD_XDMASNAP_WAITMODE_EVENT):\n");
	ret = Dd_XDMASNAP_Wait_End(0, &status, D_DD_XDMASNAP_WAITMODE_EVENT + 1);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Clear_Status]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Clear_Status(D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Get_Status]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Get_Status(D_DD_XDMASNAP_CH_NUM_MAX, &status, &status, &status);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("xdmac_status is NULL:\n");
	ret = Dd_XDMASNAP_Get_Status(0, NULL, &status, &status);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("transfer_status is NULL:\n");
	ret = Dd_XDMASNAP_Get_Status(0, &status, NULL, &status);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("interrupt_status is NULL:\n");
	ret = Dd_XDMASNAP_Get_Status(0, &status, &status, NULL);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Get_Trns_Size]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Get_Trns_Size(D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(0, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Get_Src_Addr]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Get_Src_Addr(D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(0, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Get_Dst_Addr]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Get_Dst_Addr(D_DD_XDMASNAP_CH_NUM_MAX);
	ctXdmacSnapResultOut(0, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Set_LowPower]\n");
	printf("lowpower > D_DD_XDMASNAP_XDACS_LP_ENABLE:\n");
	ret = Dd_XDMASNAP_Set_LowPower(D_DD_XDMASNAP_XDACS_LP_ENABLE + 1);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Set_Source_Protect]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Set_Source_Protect(D_DD_XDMASNAP_CH_NUM_MAX, D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("protect_code > D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE:\n");
	ret = Dd_XDMASNAP_Set_Source_Protect(0, D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE + 1);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Set_Destination_Protect]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Set_Destination_Protect(D_DD_XDMASNAP_CH_NUM_MAX, D_DD_XDMASNAP_XDDPC_DP_PRIVILEGED_SECURE);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("protect_code > D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE:\n");
	ret = Dd_XDMASNAP_Set_Destination_Protect(0, D_DD_XDMASNAP_XDDPC_DP_PRIVILEGED_SECURE + 1);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Set_Int_Handler]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	Dd_XDMASNAP_Set_Int_Handler(D_DD_XDMASNAP_CH_NUM_MAX, NULL);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Int_Handler]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	Dd_XDMASNAP_Int_Handler(D_DD_XDMASNAP_CH_NUM_MAX);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Copy_SDRAM_Sync]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Sync(D_DD_XDMASNAP_CH_NUM_MAX, 1, 1, 1, D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("src_addr = 0:\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Sync(0, 0, 1, 1, D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dst_addr = 0:\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Sync(1, 1, 0, 1, D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("size = 0:\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Sync(2, 1, 1, 0, D_DD_XDMASNAP_WAITMODE_EVENT);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (D_DD_XDMASNAP_WAITMODE_CPU, D_DD_XDMASNAP_WAITMODE_EVENT):\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Sync(3, 1, 1, 1, D_DD_XDMASNAP_WAITMODE_EVENT + 1);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMASNAP_Copy_SDRAM_Async]\n");
	printf("ch >= D_DD_XDMASNAP_CH_NUM_MAX:\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Async(D_DD_XDMASNAP_CH_NUM_MAX, 1, 1, 1, intHandler);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("src_addr = 0:\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Async(0, 0, 1, 1, intHandler);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("dst_addr = 0:\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Async(1, 1, 0, 1, intHandler);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
	printf("size = 0:\n");
	ret = Dd_XDMASNAP_Copy_SDRAM_Async(2, 1, 1, 0, intHandler);
	ctXdmacSnapResultOut(D_DD_XDMASNAP_INPUT_PARAM_ERR, ret);
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
void ct_dd_xdmasnap_main(int argc, char** argv)
{
	// kint32				ret;
	// kuchar				ch;
	// kuchar				num;
	// kint32				waitTime;
	
	CtDdXdmasnap* self = ct_dd_xdmasnap_new();
	CtDdXdmasnapPrivate *priv = CT_DD_XDMASNAP_GET_PRIVATE(self);

	// check number of parameter
	if (argc > 12) {
		Ddim_Print(("The number of input parameters is exceeded!\n"));
		return;
	}
	
	if (strcmp(argv[1], "open") == 0) {
		/* ch number */
		priv->ch = atoi(argv[2]);
		priv->waitTime = atoi(argv[3]);
		
		priv->ret = Dd_XDMASNAP_Open(priv->ch, priv->waitTime);
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
		
		priv->ret = Dd_XDMASNAP_Close(priv->ch);
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
			S_GXDMASNAP_COMMON.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_DISABLE;
		}
		else if (strcmp(argv[2], "1") == 0) {
			S_GXDMASNAP_COMMON.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
		}
		else {
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}
		
		// Set CP
		if (strcmp(argv[3], "0") == 0) {
			S_GXDMASNAP_COMMON.common_config.bit.CP = D_DD_XDMASNAP_XDACS_CP_FIXED;
		}
		else if (strcmp(argv[3], "1") == 0) {
			S_GXDMASNAP_COMMON.common_config.bit.CP = D_DD_XDMASNAP_XDACS_CP_ROTATED;
		}
		else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}
		
		priv->ret = Dd_XDMASNAP_Ctrl_Common(&S_GXDMASNAP_COMMON);
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
		
		Dd_XDMASNAP_Set_Int_Handler(priv->ch, ct_dd_xdmasnap_callback_cb);
	}
	else if (strcmp(argv[1], "auto") == 0) {
		/* ch number */
		priv->num = atoi(argv[2]);
		
		CtDdXdmasnap1* ctddxdmasnap1 = ct_dd_xdmasnap1_new();
		ct_dd_xdmasnap1_set_ctddxdmasnap(ctddxdmasnap1,self);

		priv->ret = ct_dd_xdmasnap1_process(ctddxdmasnap1);
		k_object_unref(ctddxdmasnap1);
		if (priv->ret == 0) {
			Ddim_Print(("ct_dd_xdmasnap1_process OK\n"));
		}
		else {
			Ddim_Print(("ct_dd_xdmasnap1_process ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "prm_chk") == 0) {
		T_DD_XDMASNAP_CTRL    dma_ctrl_trns;
		T_DD_XDMASNAP_TRNS_SIZE dma_trns_size;
		
		if(strcmp(argv[2], "0") == 0){
			dma_ctrl_trns.trns_size       = 0;
			dma_ctrl_trns.src_addr        = 0;
			dma_ctrl_trns.dst_addr        = 0;
			dma_ctrl_trns.int_handler     = NULL;
			
			priv->ret = Dd_XDMASNAP_Ctrl_Trns(0, &dma_ctrl_trns);
			if(priv->ret != D_DDIM_OK){
				Ddim_Print(("Dd_XDMASNAP_Ctrl_Trns ERR : priv->ret=0x%x\n", priv->ret));
			}
		}
		else if(strcmp(argv[2], "1") == 0){
			dma_trns_size.trns_size       = 0;
			dma_trns_size.src_addr        = 0;
			dma_trns_size.dst_addr        = 0;
			
			priv->ret = Dd_XDMASNAP_Set_Trns_Size(0,&dma_trns_size);
			if(priv->ret != D_DDIM_OK){
				Ddim_Print(("Dd_XDMASNAP_Set_Trns_Size ERR : priv->ret=0x%x\n", priv->ret));
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
	k_object_unref(self);
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
