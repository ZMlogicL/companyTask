/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTestfour类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_TESTFOUR_H__
#define __CT_DD_PDM_TESTFOUR_H__

#include <klib.h>

#define CT_TYPE_DD_PDM_TESTFOUR					(ct_dd_pdm_testfour_get_type())
#define CT_DD_PDM_TESTFOUR(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmTestfour))
#define CT_IS_DD_PDM_TESTFOUR(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_TESTFOUR))

typedef struct 															_CtDdPdmTestfour CtDdPdmTestfour;
typedef struct 															_CtDdPdmTestfourPrivate CtDdPdmTestfourPrivate;

struct _CtDdPdmTestfour
{
	KObject parent;
	DdPdmCoreCfg pdmCfg;
	DdPdmDmaCfg pdmDmaCfg;
};

KConstType 					ct_dd_pdm_testfour_get_type(void);
CtDdPdmTestfour* 		ct_dd_pdm_testfour_new(void);

void 								ct_dd_pdm_testfour_set_addr(CtDdPdmTestfour *self,CtDdPdmTestone *testone);
#ifdef CO_ES3_HARDWARE
void 								ct_dd_pdm_testfour_019(CtDdPdmTestfour *self);
void 								ct_dd_pdm_testfour_020(CtDdPdmTestfour *self);
void 								ct_dd_pdm_testfour_021(CtDdPdmTestfour *self);
void 								ct_dd_pdm_testfour_022(CtDdPdmTestfour *self);
void 								ct_dd_pdm_testfour_023(CtDdPdmTestfour *self);
void 								ct_dd_pdm_testfour_024(CtDdPdmTestfour *self);
void 								ct_dd_pdm_testfour_025(CtDdPdmTestfour *self);
#endif /*CO_ES3_HARDWARE*/

#endif /* __CT_DD_PDM_TESTFOUR_H__ */
