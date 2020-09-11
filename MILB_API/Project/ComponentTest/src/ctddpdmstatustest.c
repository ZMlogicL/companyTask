/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmStatustest类
*@rely                :klib
*@function
*1.0.0 2020年09月开始开发
*设计的主要功能:
*1、
*@version
*
*/

#include <string.h>
#include <stdlib.h>
#include "pdm.h"
#include "dd_pdm.h"
#include "ct_dd_pdm.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_gic.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "peripheral.h"
#include "ctddpdmothertest.h"
#include "ctddpdmstatustest.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmStatustest, ct_dd_pdm_statustest);
#define CT_DD_PDM_STATUSTEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmStatustestPrivate,CT_TYPE_DD_PDM_STATUSTEST))

struct _CtDdPdmStatustestPrivate
{
	kint a;
};

static void ct_dd_pdm_statustest_constructor(CtDdPdmStatustest *self) 
{
	self->test = NULL;
}

static void ct_dd_pdm_statustest_destructor(CtDdPdmStatustest *self) 
{
	self->test = NULL;
}

/*
 *PUBLIC
 */
void ct_dd_pdm_statustest_set_test(CtDdPdmStatustest *self,CtDdPdmOthertest *test)
{
	self->test = test;
}

void ct_dd_pdm_statustest_get(CtDdPdmStatustest *self)
{
	kint32 result;
	kuint8 status;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Get_Status(self->test->ch, E_DD_PDM_INT_TYPE_FFOVF, &status);
	
	Ddim_Print(("status=0x%x\n", status));
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_statustest_get2(CtDdPdmStatustest *self)
{
	kint32 result;
	kuint8 status;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Get_Status(self->test->ch, E_DD_PDM_INT_TYPE_DMA0, &status);
	
	Ddim_Print(("status=0x%x\n", status));
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_statustest_get3(CtDdPdmStatustest *self)
{
	kint32 result;
	kuint8 status;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Get_Status(self->test->ch, E_DD_PDM_INT_TYPE_DMA1, &status);
	
	Ddim_Print(("status=0x%x\n", status));
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_statustest_get_get_e1(CtDdPdmStatustest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Get_Status(self->test->ch, E_DD_PDM_INT_TYPE_FFOVF, NULL);
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_statustest_clear1(CtDdPdmStatustest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Clear_Status(self->test->ch, E_DD_PDM_INT_TYPE_FFOVF);
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_statustest_clear2( CtDdPdmStatustest *self )
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Clear_Status(self->test->ch, E_DD_PDM_INT_TYPE_DMA0);
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_statustest_clear3( CtDdPdmStatustest *self )
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Clear_Status(self->test->ch, E_DD_PDM_INT_TYPE_DMA1);
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

CtDdPdmStatustest* ct_dd_pdm_statustest_new(void) 
{
    CtDdPdmStatustest *self = k_object_new_with_private(CT_TYPE_DD_PDM_STATUSTEST, sizeof(CtDdPdmStatustestPrivate));
    return self;
}
