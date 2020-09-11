/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmMain类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PDM_MAIN_H__
#define __CT_DD_PDM_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_PDM_MAIN					(ct_dd_pdm_main_get_type())
#define CT_DD_PDM_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPdmMain))
#define CT_IS_DD_PDM_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PDM_MAIN)) 

typedef struct 													_CtDdPdmMain CtDdPdmMain;
typedef struct 													_CtDdPdmMainPrivate CtDdPdmMainPrivate;

struct _CtDdPdmMain
{
	KObject parent;
};

KConstType 			ct_dd_pdm_main_get_type(void);
CtDdPdmMain* 		ct_dd_pdm_main_new(void);

void 						ct_dd_pdm_main(CtDdPdmMain *self,kint argc, kchar** argv);
void 						ct_dd_pdm_main_init_test(CtDdPdmMain *self);
void 						ct_dd_pdm_main_reg_init( void );

#endif /* __CT_DD_PDM_MAIN_H__ */
