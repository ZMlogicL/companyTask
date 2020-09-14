/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTestsix类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_TESTCASE6_H__
#define __CT_DD_PDM_TESTCASE6_H__

#include <klib.h>

#define CT_TYPE_DD_PDM_TESTCASE6					(ct_dd_pdm_testsix_get_type())
#define CT_DD_PDM_TESTCASE6(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmTestsix))
#define CT_IS_DD_PDM_TESTCASE6(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_TESTCASE6))

typedef struct 															_CtDdPdmTestsix CtDdPdmTestsix;
typedef struct 															_CtDdPdmTestsixPrivate CtDdPdmTestsixPrivate;

struct _CtDdPdmTestsix
{
	KObject parent;
	DdPdmCoreCfg pdmCfg;
	DdPdmDmaCfg pdmDmaCfg;
	DdPdmDmaLen pdmLen;
};

KConstType 					ct_dd_pdm_testsix_get_type(void);
CtDdPdmTestsix* 			ct_dd_pdm_testsix_new(void);

void 								ct_dd_pdm_testsix_set_addr(CtDdPdmTestsix *self,CtDdPdmTestone *testone);
#ifdef CO_ES3_HARDWARE
void 								ct_dd_pdm_testsix_037(CtDdPdmTestsix *self);
void 								ct_dd_pdm_testsix_038(CtDdPdmTestsix *self);
void 								ct_dd_pdm_testsix_039(CtDdPdmTestsix *self);
void 								ct_dd_pdm_testsix_040(CtDdPdmTestsix *self);
void 								ct_dd_pdm_testsix_041(CtDdPdmTestsix *self);
void 								ct_dd_pdm_testsix_042(CtDdPdmTestsix *self);
void 								ct_dd_pdm_testsix_043(CtDdPdmTestsix *self);
void 								ct_dd_pdm_testsix_044(CtDdPdmTestsix *self);
#endif /*CO_ES3_HARDWARE*/

#endif /* __CT_DD_PDM_TESTCASE6_H__ */
