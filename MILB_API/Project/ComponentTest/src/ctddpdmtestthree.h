/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTestthree类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_TESTTHREE_H__
#define __CT_DD_PDM_TESTTHREE_H__

#include <klib.h>

#define CT_TYPE_DD_PDM_TESTTHREE					(ct_dd_pdm_testthree_get_type())
#define CT_DD_PDM_TESTTHREE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmTestthree))
#define CT_IS_DD_PDM_TESTTHREE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_TESTTHREE))

typedef struct 															_CtDdPdmTestthree CtDdPdmTestthree;
typedef struct 															_CtDdPdmTestthreePrivate CtDdPdmTestthreePrivate;

struct _CtDdPdmTestthree
{
	KObject parent;
	DdPdmCoreCfg pdmCfg;
	DdPdmDmaCfg pdmDmaCfg;
};

KConstType 					ct_dd_pdm_testthree_get_type(void);
CtDdPdmTestthree* 		ct_dd_pdm_testthree_new(void);
void 								ct_dd_pdm_testthree_set_addr(CtDdPdmTestthree *self,CtDdPdmTestone *testone);
#ifdef CO_ES3_HARDWARE
void 								ct_dd_pdm_testthree_012(CtDdPdmTestthree *self);
void 								ct_dd_pdm_testthree_013(CtDdPdmTestthree *self);
void 								ct_dd_pdm_testthree_014(CtDdPdmTestthree *self);
void 								ct_dd_pdm_testthree_015(CtDdPdmTestthree *self);
void 								ct_dd_pdm_testthree_016(CtDdPdmTestthree *self);
void 								ct_dd_pdm_testthree_017(CtDdPdmTestthree *self);
void 								ct_dd_pdm_testthree_018(CtDdPdmTestthree *self);
#endif /*CO_ES3_HARDWARE*/

#endif /* __CT_DD_PDM_TESTTHREE_H__ */
