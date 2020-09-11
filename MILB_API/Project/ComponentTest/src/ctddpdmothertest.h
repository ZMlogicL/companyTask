/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmOthertest类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_OTHERTEST_H__
#define __CT_DD_PDM_OTHERTEST_H__

#include <klib.h>

#define CT_TYPE_DD_PDM_OTHERTEST					(ct_dd_pdm_othertest_get_type())
#define CT_DD_PDM_OTHERTEST(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmOthertest)) 
#define CT_IS_DD_PDM_OTHERTEST(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_OTHERTEST))

typedef struct 															_CtDdPdmOthertest CtDdPdmOthertest;
typedef struct 															_CtDdPdmOthertestPrivate CtDdPdmOthertestPrivate;

struct _CtDdPdmOthertest
{
	KObject parent;
	kuint8 ch;
};

KConstType 					ct_dd_pdm_othertest_get_type(void);
CtDdPdmOthertest* 		ct_dd_pdm_othertest_new(void);

void 								ct_dd_pdm_othertest_opentest1(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_opentest2(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_opentest3(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_opentest_e1(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_opentest_e2(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_closetest(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_dma0_int_handler_test(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_dma1_int_handler_test(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_overflow_int_handler_test(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_start_streaming_test(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_stop_streaming_test(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_set_enable_overflow_intr_test1(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_set_enable_overflow_intr_test2(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_set_enable_overflow_intr_test_e1(CtDdPdmOthertest* self);
void 								ct_dd_pdm_othertest_set_callback_overflow_intr_test(CtDdPdmOthertest* self);

static inline void ct_dd_pdm_othertest_set_ch(CtDdPdmOthertest* self,  kuint8 newch)
{
	self->ch = newch;
}

#endif /* __CT_DD_PDM_OTHERTEST_H__ */
