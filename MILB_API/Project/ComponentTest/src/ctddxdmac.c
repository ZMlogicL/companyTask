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
#include "dd_xdmac.h"
#include "dd_top.h"

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
static T_DD_XDMAC_COMMON			S_GXDMAC_COMMON;

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
	T_DD_XDMAC_CTRL dma_ctrl_trans;
	T_DD_XDMAC_TRNS_SIZE dma_trns_size;
	USHORT status;
	VP_CALLBACK intHandler = 0;
	
	printf("<Dd_XDMAC>\n");
	printf("\n");
	
	printf("[Dd_XDMAC_Open]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Open(D_DD_XDMAC_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_FEVR);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("tmout < D_DDIM_USER_SEM_WAIT_FEVR:\n");
	ret = Dd_XDMAC_Open(0, D_DDIM_USER_SEM_WAIT_FEVR - 1);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("tmout = D_DDIM_USER_SEM_WAIT_POL, pol_sem = D_DDIM_USER_E_TMOUT:\n");
	ret = Dd_XDMAC_Open(0, D_DDIM_USER_SEM_WAIT_POL);
	ret = Dd_XDMAC_Open(0, D_DDIM_USER_SEM_WAIT_POL);
	ctXdmacResultOut(D_DD_XDMAC_SEM_TIMEOUT, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Close]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Close(D_DD_XDMAC_CH_NUM_MAX);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Ctrl_Common]\n");
	printf("dma_common is NULL:\n");
	ret = Dd_XDMAC_Ctrl_Common(NULL);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Ctrl_Trns]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Ctrl_Trns(D_DD_XDMAC_CH_NUM_MAX, NULL);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("dma_ctrl_trans is NULL:\n");
	ret = Dd_XDMAC_Ctrl_Trns(0, NULL);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("dma_ctrl_trans->trns_size = 0:\n");
	dma_ctrl_trans.trns_size = 0;
	ret = Dd_XDMAC_Ctrl_Trns(0, &dma_ctrl_trans);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Set_Trns_Size]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Set_Trns_Size(D_DD_XDMAC_CH_NUM_MAX, NULL);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("dma_trns_size is NULL:\n");
	ret = Dd_XDMAC_Set_Trns_Size(0, NULL);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("dma_trns_size->trns_size = 0:\n");
	dma_trns_size.trns_size = 0;
	ret = Dd_XDMAC_Set_Trns_Size(0, &dma_trns_size);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Start_Sync]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Start_Sync(D_DD_XDMAC_CH_NUM_MAX, NULL, D_DD_XDMAC_WAITMODE_CPU);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("[Dd_XDMAC_Start_Sync]\n");
	printf("status is NULL:\n");
	ret = Dd_XDMAC_Start_Sync(0, NULL, D_DD_XDMAC_WAITMODE_CPU);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (D_DD_XDMAC_WAITMODE_CPU, D_DD_XDMAC_WAITMODE_EVENT):\n");
	ret = Dd_XDMAC_Start_Sync(0, &status, D_DD_XDMAC_WAITMODE_EVENT + 1);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("wait_mode = D_DD_XDMAC_WAITMODE_EVENT, twai_flg <> D_DDIM_USER_E_TMOUT:\n");
	ret = Dd_XDMAC_Start_Sync(0, &status, D_DD_XDMAC_WAITMODE_EVENT);
	ctXdmacResultOut(D_DD_XDMAC_SYSTEM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Start_Async]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Start_Async(D_DD_XDMAC_CH_NUM_MAX);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Stop]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Stop(D_DD_XDMAC_CH_NUM_MAX);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Set_Wait_Time]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Set_Wait_Time(D_DD_XDMAC_CH_NUM_MAX, D_DDIM_WAIT_END_FOREVER);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("waitTime < D_DDIM_WAIT_END_FOREVER:\n");
	ret = Dd_XDMAC_Set_Wait_Time(0, D_DDIM_WAIT_END_FOREVER - 1);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Wait_End]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Wait_End(D_DD_XDMAC_CH_NUM_MAX, &status, D_DD_XDMAC_WAITMODE_CPU);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("status is NULL:\n");
	ret = Dd_XDMAC_Wait_End(0, NULL, D_DD_XDMAC_WAITMODE_CPU);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (D_DD_XDMAC_WAITMODE_CPU, D_DD_XDMAC_WAITMODE_EVENT):\n");
	ret = Dd_XDMAC_Wait_End(0, &status, D_DD_XDMAC_WAITMODE_EVENT + 1);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Clear_Status]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Clear_Status(D_DD_XDMAC_CH_NUM_MAX);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Get_Status]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Get_Status(D_DD_XDMAC_CH_NUM_MAX, &status, &status, &status);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("XDMAC_status is NULL:\n");
	ret = Dd_XDMAC_Get_Status(0, NULL, &status, &status);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("transfer_status is NULL:\n");
	ret = Dd_XDMAC_Get_Status(0, &status, NULL, &status);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("interrupt_status is NULL:\n");
	ret = Dd_XDMAC_Get_Status(0, &status, &status, NULL);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Get_Trns_Size]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Get_Trns_Size(D_DD_XDMAC_CH_NUM_MAX);
	ctXdmacResultOut(0, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Get_Src_Addr]\n");
	printf("ch >= D_DD_XDAMC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Get_Src_Addr(D_DD_XDMAC_CH_NUM_MAX);
	ctXdmacResultOut(0, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Get_Dst_Addr]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Get_Dst_Addr(D_DD_XDMAC_CH_NUM_MAX);
	ctXdmacResultOut(0, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Set_LowPower]\n");
	printf("lowpower > D_DD_XDMAC_XDACS_LP_ENABLE:\n");
	ret = Dd_XDMAC_Set_LowPower(D_DD_XDMAC_XDACS_LP_ENABLE + 1);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Set_Source_Protect]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Set_Source_Protect(D_DD_XDMAC_CH_NUM_MAX, D_DD_XDMAC_XDDPC_SP_PRIVILEGED_SECURE);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("protect_code > D_DD_xdmac_XDDPC_SP_PRIVILEGED_SECURE:\n");
	ret = Dd_XDMAC_Set_Source_Protect(0, D_DD_XDMAC_XDDPC_SP_PRIVILEGED_SECURE + 1);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Set_Destination_Protect]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Set_Destination_Protect(D_DD_XDMAC_CH_NUM_MAX, D_DD_XDMAC_XDDPC_DP_PRIVILEGED_SECURE);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("protect_code > D_DD_XDMAC_XDDPC_SP_PRIVILEGED_SECURE:\n");
	ret = Dd_XDMAC_Set_Destination_Protect(0, D_DD_XDMAC_XDDPC_DP_PRIVILEGED_SECURE + 1);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Set_Int_Handler]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	Dd_XDMAC_Set_Int_Handler(D_DD_XDMAC_CH_NUM_MAX, NULL);
	printf("\n");
	
	printf("[Dd_XDMAC_Int_Handler]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	Dd_XDMAC_Int_Handler(D_DD_XDMAC_CH_NUM_MAX);
	printf("\n");
	
	printf("[Dd_XDMAC_Copy_SDRAM_Sync]\n");
	printf("ch >= D_DD_xdmac_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Copy_SDRAM_Sync(D_DD_XDMAC_CH_NUM_MAX, 1, 1, 1, D_DD_XDMAC_WAITMODE_EVENT);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("src_addr = 0:\n");
	ret = Dd_XDMAC_Copy_SDRAM_Sync(0, 0, 1, 1, D_DD_XDMAC_WAITMODE_EVENT);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("dst_addr = 0:\n");
	ret = Dd_XDMAC_Copy_SDRAM_Sync(1, 1, 0, 1, D_DD_XDMAC_WAITMODE_EVENT);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("size = 0:\n");
	ret = Dd_XDMAC_Copy_SDRAM_Sync(2, 1, 1, 0, D_DD_XDMAC_WAITMODE_EVENT);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("wait_mode not in (D_DD_XDMAC_WAITMODE_CPU, D_DD_XDMAC_WAITMODE_EVENT):\n");
	ret = Dd_XDMAC_Copy_SDRAM_Sync(3, 1, 1, 1, D_DD_XDMAC_WAITMODE_EVENT + 1);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("\n");
	
	printf("[Dd_XDMAC_Copy_SDRAM_Async]\n");
	printf("ch >= D_DD_XDMAC_CH_NUM_MAX:\n");
	ret = Dd_XDMAC_Copy_SDRAM_Async(D_DD_XDMAC_CH_NUM_MAX, 1, 1, 1, intHandler);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("src_addr = 0:\n");
	ret = Dd_XDMAC_Copy_SDRAM_Async(0, 0, 1, 1, intHandler);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("dst_addr = 0:\n");
	ret = Dd_XDMAC_Copy_SDRAM_Async(1, 1, 0, 1, intHandler);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
	printf("size = 0:\n");
	ret = Dd_XDMAC_Copy_SDRAM_Async(2, 1, 1, 0, intHandler);
	ctXdmacResultOut(D_DD_XDMAC_INPUT_PARAM_ERR, ret);
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
 *	| "open"          | ch       | waitTime  |          |            |            |          |    |    |     |     | Dd_XDMAC_Open()                   |
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
void ct_dd_xdmac_main(int argc, char** argv)
{
	// kint32				ret;
	// kuchar				ch;
	// kuchar				num;
	// kint32				waitTime;
	
	CtDdXdmac* self = ct_dd_xdmac_new();
	CtDdXdmacPrivate *priv = CT_DD_XDMAC_GET_PRIVATE(self);
	// check number of parameter
	if (argc > 12) {
		Ddim_Print(("The number of input parameters is exceeded!\n"));
		return;
	}
	
	Dd_Top_Set_CLKSTOP2_EXSAX(0);
	
	if (strcmp(argv[1], "open") == 0) {
		/* ch number */
		priv->ch = atoi(argv[2]);
		priv->waitTime = atoi(argv[3]);
		
		priv->ret = Dd_XDMAC_Open(priv->ch, priv->waitTime);
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
		
		priv->ret = Dd_XDMAC_Close(priv->ch);
		if (priv->ret == 0) {
			Ddim_Print(("XDMAC Close OK\n"));
		}
		else {
			Ddim_Print(("XDMAC Close ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "ctrl_cmm") == 0) {
		Dd_XDMAC_Open(0, D_DDIM_USER_SEM_WAIT_POL);
		
		// Set XE
		if (strcmp(argv[2], "0") == 0) {
			S_GXDMAC_COMMON.common_config.bit.XE = D_DD_XDMAC_XDACS_XE_DISABLE;
		}
		else if (strcmp(argv[2], "1") == 0) {
			S_GXDMAC_COMMON.common_config.bit.XE = D_DD_XDMAC_XDACS_XE_ENABLE;
		}
		else {
			Ddim_Print(("Parameter ERR. P3 \n"));
			Dd_XDMAC_Close(0);
			return;
		}
		
		// Set CP
		if (strcmp(argv[3], "0") == 0) {
			S_GXDMAC_COMMON.common_config.bit.CP = D_DD_XDMAC_XDACS_CP_FIXED;
		}
		else if (strcmp(argv[3], "1") == 0) {
			S_GXDMAC_COMMON.common_config.bit.CP = D_DD_XDMAC_XDACS_CP_ROTATED;
		}
		else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			Dd_XDMAC_Close(0);
			return;
		}
		
		priv->ret = Dd_XDMAC_Ctrl_Common(&S_GXDMAC_COMMON);
		if (priv->ret == 0) {
			Ddim_Print(("XDMAC Ctrl_Common OK\n"));
		}
		else {
			Ddim_Print(("XDMAC Ctrl_Common ERR. priv->ret=0x%x\n", priv->ret));
		}
		Dd_XDMAC_Close(0);
	}
	else if (strcmp(argv[1], "int_set") == 0){
		/* ch number */
		priv->ch = atoi(argv[2]);
		
		Dd_XDMAC_Set_Int_Handler(priv->ch, ct_dd_xdmac_callback_cb);
	}
	else if (strcmp(argv[1], "auto") == 0) {
		/* ch number */
		priv->num = atoi(argv[2]);
		CtDdXdmac1* ctddxdmac1 = ct_dd_xdmac1_new();
		ct_dd_xdmac1_set_ctddxdmac(ctddxdmac1,self);
		priv->ret = ct_dd_xdmac1_process(ctddxdmac1);
		k_object_unref(ctddxdmac1);
		if (priv->ret == 0) {
			Ddim_Print(("ct_dd_xdmac1_process OK\n"));
		}
		else {
			Ddim_Print(("ct_dd_xdmac1_process ERR. priv->ret=0x%x\n", priv->ret));
		}
	}
	else if (strcmp(argv[1], "prm_chk") == 0) {
		T_DD_XDMAC_CTRL    dma_ctrl_trns;
		T_DD_XDMAC_TRNS_SIZE dma_trns_size;
		
		if(strcmp(argv[2], "0") == 0){
			dma_ctrl_trns.trns_size       = 0;
			dma_ctrl_trns.src_addr        = 0;
			dma_ctrl_trns.dst_addr        = 0;
			dma_ctrl_trns.int_handler     = NULL;
			
			priv->ret = Dd_XDMAC_Ctrl_Trns(0, &dma_ctrl_trns);
			if(priv->ret != D_DDIM_OK){
				Ddim_Print(("Dd_XDMAC_Ctrl_Trns ERR : priv->ret=0x%x\n", priv->ret));
			}
		}
		else if(strcmp(argv[2], "1") == 0){
			dma_trns_size.trns_size       = 0;
			dma_trns_size.src_addr        = 0;
			dma_trns_size.dst_addr        = 0;
			
			priv->ret = Dd_XDMAC_Set_Trns_Size(0,&dma_trns_size);
			if(priv->ret != D_DDIM_OK){
				Ddim_Print(("Dd_XDMAC_Set_Trns_Size ERR : priv->ret=0x%x\n", priv->ret));
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
	k_object_unref(self);
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