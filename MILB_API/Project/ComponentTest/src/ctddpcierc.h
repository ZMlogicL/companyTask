/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdPcieRc类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PCIE_RC_H__
#define __CT_DD_PCIE_RC_H__

#include <klib.h>

#define CT_TYPE_DD_PCIE_RC						(ct_dd_pcie_rc_get_type())
#define CT_DD_PCIE_RC(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPcieRc))
#define CT_IS_DD_PCIE_RC(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PCIE_RC)) 

typedef struct 			_CtDdPcieRc CtDdPcieRc;
typedef struct 			_CtDdPcieRcPrivate CtDdPcieRcPrivate;

struct _CtDdPcieRc
{
	KObject 								parent;
	kint32									ret;
	E_DD_PCIE_CH					ch;
	T_DD_PCIE_RC_CTRL_CFG	pcieCtrlCfg;
	T_DD_PCIE_CTRL_DMA		ctrlDma;
	T_DD_PCIE_CTRL_MEM		ctrlMem;
	T_DD_PCIE_RC_CTRL_MSI	pcieCtrlMsi;

};

KConstType 		ct_dd_pcie_rc_get_type(void);
CtDdPcieRc* 		ct_dd_pcie_rc_new(void);

void 					ct_dd_pcie_rc_from_main(CtDdPcieRc* self, kint argc, kchar** argv);

#endif /* __CT_DD_PCIE_RC_H__ */
