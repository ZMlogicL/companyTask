/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmStatustest类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_STATUSTEST_H__
#define __CT_DD_PDM_STATUSTEST_H__

#include <klib.h>
#include "ctddpdmothertest.h"

#define CT_TYPE_DD_PDM_STATUSTEST					(ct_dd_pdm_statustest_get_type())
#define CT_DD_PDM_STATUSTEST(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmStatustest)) 
#define CT_IS_DD_PDM_STATUSTEST(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_STATUSTEST))

typedef struct 															_CtDdPdmStatustest CtDdPdmStatustest;
typedef struct 															_CtDdPdmStatustestPrivate CtDdPdmStatustestPrivate;

struct _CtDdPdmStatustest
{
	KObject parent;
	CtDdPdmOthertest *test;
};

KConstType 					ct_dd_pdm_statustest_get_type(void);
CtDdPdmStatustest* 		ct_dd_pdm_statustest_new(void);
void 								ct_dd_pdm_statustest_set_test(CtDdPdmStatustest *self,CtDdPdmOthertest *test);
void 								ct_dd_pdm_statustest_get( CtDdPdmStatustest *self );
void 								ct_dd_pdm_statustest_get2( CtDdPdmStatustest *self );
void 								ct_dd_pdm_statustest_get3( CtDdPdmStatustest *self );
void 								ct_dd_pdm_statustest_get_get_e1( CtDdPdmStatustest *self );
void 								ct_dd_pdm_statustest_clear1( CtDdPdmStatustest *self );
void 								ct_dd_pdm_statustest_clear2( CtDdPdmStatustest *self );
void 								ct_dd_pdm_statustest_clear3( CtDdPdmStatustest *self );

#endif /* __CT_DD_PDM_STATUSTEST_H__ */
