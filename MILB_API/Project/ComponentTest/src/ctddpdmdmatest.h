/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmDmatest类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_DMATEST_H__
#define __CT_DD_PDM_DMATEST_H__

#include <klib.h>
#include "ctddpdmothertest.h"

#define CT_TYPE_DD_PDM_DMATEST						(ct_dd_pdm_dmatest_get_type())
#define CT_DD_PDM_DMATEST(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmDmatest))
#define CT_IS_DD_PDM_DMATEST(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_DMATEST)) 

typedef struct 															_CtDdPdmDmatest CtDdPdmDmatest;
typedef struct 															_CtDdPdmDmatestPrivate CtDdPdmDmatestPrivate;

struct _CtDdPdmDmatest
{
	KObject parent;
	CtDdPdmOthertest *test;
};

KConstType 				ct_dd_pdm_dmatest_get_type(void);
CtDdPdmDmatest* 	ct_dd_pdm_dmatest_new(void);

void 							ct_dd_pdm_dmatest_set_test(CtDdPdmDmatest *self,CtDdPdmOthertest *test);
void 							ct_dd_pdm_dmatest_ctrl(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_ctrl_e1(CtDdPdmDmatest *self);
void	 						ct_dd_pdm_dmatest_ctrl_e2(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_ctrl_e3(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_ctrl_e4(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_ctrl_e5(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_ctrl_e6(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_get_ctrl(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_get_ctrl_e1(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_callback_dma0_intr_test(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_callback_dma1_intr_test(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_enable_dma0_intr_test1(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_enable_dma0_intr_test2(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_enable_dma0_intr_test_e1(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_enable_dma1_intr_test1(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_enable_dma1_intr_test2(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_enable_dma1_intr_test_e1(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_dma0_dst_addr_test(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_dma1_dst_addr_test(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_dma_trans_length_test(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_dma_trans_length_test_e1(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_dma_trans_length_test_e2(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_dma_trans_length_test_e3(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_set_dma_trans_length_test_e4(CtDdPdmDmatest *self);
void 							ct_dd_pdm_dmatest_flush_dma_fifo_test(CtDdPdmDmatest *self);

#endif /* __CT_DD_PDM_DMATEST_H__ */
