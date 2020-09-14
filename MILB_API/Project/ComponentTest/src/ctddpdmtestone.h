/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTestone类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_TESTONE_H__
#define __CT_DD_PDM_TESTONE_H__

#include <klib.h>

#define CT_TYPE_DD_PDM_TESTONE					(ct_dd_pdm_testone_get_type())
#define CT_DD_PDM_TESTONE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmTestone))
#define CT_IS_DD_PDM_TESTONE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_TESTONE))

#define CtDdPdmTestone_WORK_AREA				(0x7C000000)

typedef struct 														_CtDdPdmTestone CtDdPdmTestone;
typedef struct 														_CtDdPdmTestonePrivate CtDdPdmTestonePrivate;

struct _CtDdPdmTestone
{
	KObject parent;
	kuint32 cnt;
	DdPdmCoreCfg pdmCfg;
	DdPdmDmaCfg pdmDmaCfg;
	CtDdPdmTestonePrivate *priv;
};

KConstType 					ct_dd_pdm_testone_get_type(void);
CtDdPdmTestone* 		ct_dd_pdm_testone_new(void);

void 								ct_dd_pdm_testone_reg_rw(void);
#ifdef CO_ES1_HARDWARE
void 								ct_dd_pdm_testone_001(CtDdPdmTestone * self);
void 								ct_dd_pdm_testone_002(CtDdPdmTestone * self);
void 								ct_dd_pdm_testone_003(CtDdPdmTestone * self);
void 								ct_dd_pdm_testone_004(CtDdPdmTestone * self);
void 								ct_dd_pdm_testone_005(CtDdPdmTestone * self);
#endif /*CO_ES1_HARDWARE*/

#endif /* __CT_DD_PDM_TESTONE_H__ */
