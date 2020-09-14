/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdNic类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_nic.c
 * @brief		dd_nic Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "ddnic.h"
#include "ctddnic.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdNic, ct_dd_nic);
#define CT_DD_NIC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdNicPrivate,CT_TYPE_DD_NIC))

struct _CtDdNicPrivate {
    kint a;
};

/*
 *DECLS
 */
static void ctDdNicRun(kint32 ctParam1st, kulong ctParam2st, kulong ctParam3st);

static void ct_dd_nic_constructor(CtDdNic *self) 
{
	// CtDdNicPrivate *priv = CT_DD_NIC_GET_PRIVATE(self);
}

static void ct_dd_nic_destructor(CtDdNic *self)
{
// CtDdNicPrivate *priv = CT_DD_NIC_GET_PRIVATE(self);
}
/*
 *IMPL
 */
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
static void ctDdNicRun(kint32 ctParam1st, kulong ctParam2st, kulong ctParam3st)
{
	kint32 dat;
	kint32 num;
	DdNic *ddNic = dd_nic_new();

	switch (ctParam1st) {
		case 1:
			for(num=0; num <= C_NIC_NODE_NUM_MAX; num++) {
				dat = DdNic_GET_ASIB_WR_TIDEMARK(num);
				Ddim_Print(("ASIB[%d] (Tidemark) = %d\n", num, dat));
				
				dat = DdNic_GET_ASIB_READ_QOS(num);
				Ddim_Print(("ASIB[%d] (Read channel QoS) = %d\n", num, dat));
				
				dat = DdNic_GET_ASIB_WRITE_QOS(num);
				Ddim_Print(("ASIB[%d] (Write channel QoS) = %d\n", num, dat));
				
				dat = DdNic_GET_ASIB_FUNC_MOD(num);
				Ddim_Print(("ASIB[%d] (Functionality Modification) = %d\n", num, dat));
			}
			break;
		case 2:
			dd_nic_set_addrctrl_security1(ddNic, ctParam2st);
			Ddim_Print(("It set ADDRCTRL Security1.\n"));
			break;
		case 3:
			dd_nic_set_asib_wr_tidemark(ddNic, (kuint32)ctParam2st, ctParam3st);
			Ddim_Print(("It set ASIB Tidemark.\n"));
			break;
		case 4:
			dd_nic_set_asib_read_qos(ddNic, (kuint32)ctParam2st, ctParam3st);
			Ddim_Print(("It set ASIB Read Channel QoS.\n"));
			break;
		case 5:
			dd_nic_set_asib_write_qos(ddNic, (kuint32)ctParam2st, ctParam3st);
			Ddim_Print(("It set ASIB Write Channel QoS.\n"));
			break;
		case 6:
			dd_nic_set_asib_func_mod(ddNic, (kuint32)ctParam2st, ctParam3st);
			Ddim_Print(("It set ASIB Functionality Modification.\n"));
			break;
		default:
			Ddim_Print(("please check parameter!!\n"));
			break;
	}
	return;
	k_object_unref(ddNic);
	ddNic = NULL; 
}
/*
 *PUBLIC
 */
/**
 * @brief  Command main function for NIC test.
 * @param  int argc	:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 *
 *		The meaning of parameters
 *		+---------------------+-----+-----+-----------------------------------------------------+
 *		| P1                  | P2  | P3  |Meaning                                              |
 *		+---------------------+-----+-----+-----------------------------------------------------+
 *		| 1:display           | -   | -   |Display all registers in Network Inter Connect.      |
 *		+---------------------+-----+-----+-----------------------------------------------------+
 *		| 2:set Security1     | dat | -   |It set ADDRCTRL Security1.                           |
 *		+---------------------+-----+-----+-----------------------------------------------------+
 *		| 3:set asib_tidemark | num | dat |It set ASIB Tidemark.                                |
 *		+---------------------+-----+-----+-----------------------------------------------------+
 *		| 4:set asib_rqos     | num | dat |It set ASIB Read Channel QoS.                        |
 *		+---------------------+-----+-----+-----------------------------------------------------+
 *		| 5:set asib_wqos     | num | dat |It set ASIB Write Channel QoS.                       |
 *		+---------------------+-----+-----+-----------------------------------------------------+
 *		| 6:set asib_fmod     | num | dat |It set ASIB Functionality Modification.              |
 *		+---------------------+-----+-----+-----------------------------------------------------+
 */
void ct_dd_nic_main(CtDdNic *self, kint argc, KType* argv)
{
	self->param2 = 0;
	self->param3 = 0;
	if (argc > 4) {
		Ddim_Print(("input parameter error\n"));
		return;
	}
	
	self->param1 = atoi((KConstType)argv[1]);
	
	if (argc >= 2) {
		self->param2 = atol((KConstType)argv[2]);
	}
	
	if (argc >= 3) {
		self->param3 = atol((KConstType)argv[3]);
	}
	
	ctDdNicRun(self->param1, self->param2, self->param3);
	
	return;
}

CtDdNic *ct_dd_nic_new(void)
{
    CtDdNic *self = k_object_new_with_private(CT_TYPE_DD_NIC, sizeof(CtDdNicPrivate));
    return self;
}
