/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmOthertest类
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
#include "ctddpdmmain.h"
#include "ctddpdmothertest.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmOthertest, ct_dd_pdm_othertest);
#define CT_DD_PDM_OTHERTEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmOthertestPrivate,CT_TYPE_DD_PDM_OTHERTEST))

struct _CtDdPdmOthertestPrivate
{
	kint a;
};

static void ct_dd_pdm_othertest_constructor(CtDdPdmOthertest *self) 
{
	
}

static void ct_dd_pdm_othertest_destructor(CtDdPdmOthertest *self) 
{

}

/*
 *PUBLIC
 */
void ct_dd_pdm_othertest_opentest1(CtDdPdmOthertest* self)
{
	kint32 result;
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	result = Dd_Pdm_Open(self->ch, D_DDIM_USER_SEM_WAIT_POL);
	Dd_Pdm_Close(self->ch);

	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_opentest2(CtDdPdmOthertest* self)
{
	kint32 result;
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	result = Dd_Pdm_Open(self->ch, 3000);
	Dd_Pdm_Close(self->ch);

	Ddim_Print(("<%s> End. result=0x%x, self->chch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_opentest3(CtDdPdmOthertest* self)
{
	kint32 result;
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	result = Dd_Pdm_Open(self->ch, D_DDIM_USER_SEM_WAIT_FEVR);
	Dd_Pdm_Close(self->ch);

	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_opentest_e1(CtDdPdmOthertest* self)
{
	kint32 result;
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Open(self->ch, -2);
	
	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_opentest_e2(CtDdPdmOthertest* self)
{
	kint32 result;
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Open(self->ch, D_DDIM_USER_SEM_WAIT_POL);
	result = Dd_Pdm_Open(self->ch, D_DDIM_USER_SEM_WAIT_POL);
	
	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_closetest(CtDdPdmOthertest* self)
{
	kint32 result;
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	Dd_Pdm_Open(self->ch, D_DDIM_USER_SEM_WAIT_POL);
	result = Dd_Pdm_Close(self->ch);

	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_dma0_int_handler_test(CtDdPdmOthertest* self)
{
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	Dd_Pdm_Dma0_Int_Handler(self->ch);

	Ddim_Print(("<%s> End. self->ch=%d\n", __FUNCTION__, self->ch));
}

void ct_dd_pdm_othertest_dma1_int_handler_test(CtDdPdmOthertest* self)
{
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	Dd_Pdm_Dma1_Int_Handler(self->ch);

	Ddim_Print(("<%s> End. self->ch=%d\n", __FUNCTION__, self->ch));
}

void ct_dd_pdm_othertest_overflow_int_handler_test(CtDdPdmOthertest* self)
{
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));

	Dd_Pdm_OverFlow_Int_Handler(self->ch);

	Ddim_Print(("<%s> End. self->ch=%d\n", __FUNCTION__, self->ch));
}

void ct_dd_pdm_othertest_start_streaming_test(CtDdPdmOthertest* self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Start_Streaming(self->ch);
	
	if (self->ch <= 1){
		Ddim_Print(("PDMCORE_EN=0x%x\n", IO_PDM[self->ch].CORE_CFG.bit.PDMCORE_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_stop_streaming_test(CtDdPdmOthertest* self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Stop_Streaming(self->ch);
	
	if (self->ch <= 1){
		Ddim_Print(("PDMCORE_EN=0x%x\n", IO_PDM[self->ch].CORE_CFG.bit.PDMCORE_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_set_enable_overflow_intr_test1(CtDdPdmOthertest* self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableOverFlowIntr(self->ch, D_DD_PDM_ENABLE);
	
	if (self->ch <= 1){
		Ddim_Print(("CLR_IRQ_FFOVF=%d\n", IO_PDM[self->ch].DMA_CFG.bit.CLR_IRQ_FFOVF));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_set_enable_overflow_intr_test2(CtDdPdmOthertest* self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableOverFlowIntr(self->ch, D_DD_PDM_DISABLE);
	
	if (self->ch <= 1){
		Ddim_Print(("CLR_IRQ_FFOVF=%d\n", IO_PDM[self->ch].DMA_CFG.bit.CLR_IRQ_FFOVF));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_set_enable_overflow_intr_test_e1(CtDdPdmOthertest* self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableOverFlowIntr(self->ch, 2);
	
	if (self->ch <= 1){
		Ddim_Print(("CLR_IRQ_FFOVF=%d\n", IO_PDM[self->ch].DMA_CFG.bit.CLR_IRQ_FFOVF));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

void ct_dd_pdm_othertest_set_callback_overflow_intr_test(CtDdPdmOthertest* self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_CallbackOverFlowIntr(self->ch, NULL);
	
	Ddim_Print(("<%s> End. result=0x%x, self->ch=%d\n", __FUNCTION__, result, self->ch));
}

CtDdPdmOthertest* ct_dd_pdm_othertest_new(void) 
{
    CtDdPdmOthertest *self = k_object_new_with_private(CT_TYPE_DD_PDM_OTHERTEST, sizeof(CtDdPdmOthertestPrivate));
    return self;
}
