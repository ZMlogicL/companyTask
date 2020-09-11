/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTesttwo类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_TESTTWO_H__
#define __CT_DD_PDM_TESTTWO_H__

#include <klib.h>

#define CT_TYPE_DD_PDM_TESTTWO					(ct_dd_pdm_testtwo_get_type())
#define CT_DD_PDM_TESTTWO(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmTesttwo))
#define CT_IS_DD_PDM_TESTTWO(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_TESTTWO))

typedef struct 														_CtDdPdmTesttwo CtDdPdmTesttwo;
typedef struct 														_CtDdPdmTesttwoPrivate CtDdPdmTesttwoPrivate;

struct _CtDdPdmTesttwo
{
	KObject parent;
	T_DD_PDM_CORE_CFG pdmCfg;
	T_DD_PDM_DMA_CFG pdmDmaCfg;
	CtDdPdmTesttwoPrivate *priv;
};

KConstType 					ct_dd_pdm_testtwo_get_type(void);
CtDdPdmTesttwo* 			ct_dd_pdm_testtwo_new(void);

void 								ct_dd_pdm_testtwo_set_addr(CtDdPdmTesttwo *self,CtDdPdmTestone *testone);
#ifdef CO_ES1_HARDWARE
void 								ct_dd_pdm_testtwo_006(CtDdPdmTesttwo *self);
#endif /*CO_ES1_HARDWARE*/
#ifdef CO_ES3_HARDWARE
void 								ct_dd_pdm_testtwo_007(CtDdPdmTesttwo *self);
void 								ct_dd_pdm_testtwo_008(CtDdPdmTesttwo *self);
void 								ct_dd_pdm_testtwo_009(CtDdPdmTesttwo *self);
void 								ct_dd_pdm_testtwo_010(CtDdPdmTesttwo *self);
void 								ct_dd_pdm_testtwo_011(CtDdPdmTesttwo *self);
#endif /*CO_ES3_HARDWARE*/

#endif /* __CT_DD_PDM_TESTTWO_H__ */
