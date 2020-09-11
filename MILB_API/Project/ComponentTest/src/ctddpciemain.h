/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdPcieMain类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PCIE_MAIN_H__
#define __CT_DD_PCIE_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_PCIE_MAIN					(ct_dd_pcie_main_get_type())
#define CT_DD_PCIE_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPcieMain))
#define CT_IS_DD_PCIE_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PCIE_MAIN)) 

typedef struct 			_CtDdPcieMain CtDdPcieMain;
typedef struct 			_CtDdPcieMainPrivate CtDdPcieMainPrivate;

struct _CtDdPcieMain
{
	KObject parent;
	CtDdPcieMainPrivate *priv;

};

KConstType 		ct_dd_pcie_main_get_type(void);
CtDdPcieMain* 	ct_dd_pcie_main_new(void);

void 					ct_dd_pcie_main_test(CtDdPcieMain* self, kint argc, kchar** argv);

#endif /* __CT_DD_PCIE_MAIN_H__ */
