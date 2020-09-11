/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmCoretest类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_CORETEST_H__
#define __CT_DD_PDM_CORETEST_H__

#include <klib.h>
#include "ctddpdmothertest.h"

#define CT_TYPE_DD_PDM_CORETEST					(ct_dd_pdm_coretest_get_type())
#define CT_DD_PDM_CORETEST(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmCoretest))
#define CT_IS_DD_PDM_CORETEST(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_CORETEST)) 

typedef struct 															_CtDdPdmCoretest CtDdPdmCoretest;
typedef struct 															_CtDdPdmCoretestPrivate CtDdPdmCoretestPrivate;

struct _CtDdPdmCoretest
{
	KObject parent;
	CtDdPdmOthertest *test;
};

KConstType 						ct_dd_pdm_coretest_get_type(void);
CtDdPdmCoretest* 			ct_dd_pdm_coretest_new(void);

void 									ct_dd_pdm_coretest_set_test(CtDdPdmCoretest *self,CtDdPdmOthertest *test);
void 									ct_dd_pdm_coretest_ctrl(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e1(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e2(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e3(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e4(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e5(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e6(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e7(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e8(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_ctrl_e9(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_get_ctrl(CtDdPdmCoretest *self);
void 									ct_dd_pdm_coretest_get_ctrl_e1(CtDdPdmCoretest *self);

#endif /* __CT_DD_PDM_CORETEST_H__ */
