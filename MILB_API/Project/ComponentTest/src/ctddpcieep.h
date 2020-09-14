/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdPcieEp类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __CT_DD_PCIE_EP_H__
#define __CT_DD_PCIE_EP_H__

#include <klib.h>
#include "ddimtypedef.h"
#include "ddpcieep.h"
#include "ddtimestamp.h"
#include "ddpciecomm.h"
#include "ddimusercustom.h"

#define CT_TYPE_DD_PCIE_EP                  (ct_dd_pcie_ep_get_type())
#define CT_DD_PCIE_EP(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPcieEp)) 
#define CT_IS_DD_PCIE_EP(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PCIE_EP)) 

typedef struct                              _CtDdPcieEp CtDdPcieEp;
typedef struct                              _CtDdPcieEpPrivate CtDdPcieEpPrivate;

struct _CtDdPcieEp {
    KObject             parent;
    DdPcieDmaCh			dmach;
	DdPcieDmaDir		dir;
	kushort				offset;
	kuint32				data;
	EDdPcieEpMsiNum		msiNum;
	DdTimestamp			timestampCtrl;
	DdPcieCtrlDma		ctrlDma;
	DdPcieCtrlMem		ctrlMem;
	DdPcieLinkSpeed		currentLinkSpeed;
	DdPcieAspmControl	aspmStatus;
	DdPcieMps 			mps;
};

KConstType      ct_dd_pcie_ep_get_type(void);

void            ct_dd_pcie_ep_main(CtDdPcieEp *self, kint argc, KType* argv);

CtDdPcieEp*     ct_dd_pcie_ep_new(void);

#endif /* __CT_DD_PCIE_EP_H__ */
