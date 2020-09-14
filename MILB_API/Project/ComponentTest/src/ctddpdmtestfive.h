/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTestfive类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_TESTFIVE_H__
#define __CT_DD_PDM_TESTFIVE_H__

#include <klib.h>

#define CT_TYPE_DD_PDM_TESTFIVE					(ct_dd_pdm_testfive_get_type())
#define CT_DD_PDM_TESTFIVE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmTestfive))
#define CT_IS_DD_PDM_TESTFIVE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_TESTFIVE))

typedef struct 														_CtDdPdmTestfive CtDdPdmTestfive;
typedef struct 														_CtDdPdmTestfivePrivate CtDdPdmTestfivePrivate;

struct _CtDdPdmTestfive
{
	KObject parent;
	DdPdmCoreCfg pdmCfg;
	DdPdmDmaCfg pdmDmaCfg;
	DdPdmDmaLen pdmLen;
};

KConstType 					ct_dd_pdm_testfive_get_type(void);
CtDdPdmTestfive* 			ct_dd_pdm_testfive_new(void);

void 								ct_dd_pdm_testfive_set_addr(CtDdPdmTestfive *self,CtDdPdmTestone *testone);
#ifdef CO_ES3_HARDWARE
void 								ct_dd_pdm_testfive_dma_int_handler026_0_cb( void );
void 								ct_dd_pdm_testfive_dma_int_handler026_1_cb( void );
void 								ct_dd_pdm_testfive_026(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_027(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_028(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_029(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_030(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_031(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_032(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_033(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_034(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_035(CtDdPdmTestfive *self);
void 								ct_dd_pdm_testfive_036(CtDdPdmTestfive *self);
#endif /*CO_ES3_HARDWARE*/

#endif /* __CT_DD_PDM_TESTFIVE_H__ */
