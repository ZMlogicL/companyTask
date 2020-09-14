/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 王顺
*@brief : DdPcieRcCommon
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __DD_PCIE_RC_COMMON_H__
#define __DD_PCIE_RC_COMMON_H__


#include <klib.h>
#include <string.h>
#include "ddimusercustom.h"
#include "chiptop.h"
#include "ddexs.h"
#include "ddpciercint.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#define DD_TYPE_PCIE_RC_COMMON                  (dd_pcie_rc_common_get_type())
#define DD_PCIE_RC_COMMON(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdPcieRcCommon))
#define DD_IS_PCIE_RC_COMMON(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_PCIE_RC_COMMON))

#ifndef D_DEBUG_PRINT_INFO_ON
#define DdPcieRcCommon_DEBUG_PRINT(arg)
#else
#define DdPcieRcCommon_DEBUG_PRINT(arg)		{DDIM_User_Printf arg;}
#endif	// D_DEBUG_PRINT_INFO_ON


typedef struct _DdPcieRcCommon DdPcieRcCommon;
typedef struct _DdPcieRcCommonPrivate DdPcieRcCommonPrivate;

struct _DdPcieRcCommon
{
	KObject parent;
};


//extern volatile DdPcieBifurcation	gddPcieRcBifurcation;
extern volatile DdPcieRcIntTrsIcsMsiCb gddPcieRcIntTrsIcsMsiCb[C_PCIE_RC_MAX_CH];
extern volatile DdPcieRcIntSysErrCb gddPcieRcIntSysErrCb[C_PCIE_RC_MAX_CH];
extern volatile DdPcieRcIntEpCb gddPcieRcIntEpCb[C_PCIE_RC_MAX_CH];
extern volatile DdPciRcIntOwnCb gddPcieRcIntOwnCb[C_PCIE_RC_MAX_CH];
extern volatile VpCallbackPcieFunc gddPcieRcHpDetectCard[C_PCIE_RC_MAX_CH];
extern volatile kuint16 gddPcieRcConfigAdr[C_PCIE_RC_MAX_CH];
extern volatile kuchar	gddPcieRcReType;
extern volatile DdPcieIntDmaCb gddPcieRcIntDmaCb[C_PCIE_RC_MAX_CH];
extern volatile VpCallbackPcieFunc gddPcieRcIntMsiCb[C_PCIE_RC_MAX_CH];;


KConstType					dd_pcie_rc_common_get_type(void);
DdPcieRcCommon*	dd_pcie_rc_common_get(void);
void							dd_pcie_rc_common_init(DdPcieRcCommon *self, volatile IoPcie* ioPcie,
										volatile IoPcieCore* ioPcieCore, DdPcieBifurcation bifurcation);
kint32							dd_pcie_rc_common_chk_config_rw_par(DdPcieRcCommon *self,
										DdPcieCh ch, kuint16 offset);
kint32							dd_pcie_rc_common_chk_exs_reg_par(DdPcieRcCommon *self,
										DdPcieCh ch, kuint16 offset);
kint32							dd_pcie_rc_common_chk_dbi_reg_par(DdPcieRcCommon *self,
										DdPcieCh ch, kuint16 offset);
DdPcieBifurcation	dd_pcie_rc_common_get_gdd_pcie_rc_bifurcation(DdPcieRcCommon * self);
void							dd_pcie_rc_common_set_gdd_pcie_rc_bifurcation(DdPcieRcCommon * self,
										DdPcieBifurcation	gddPcieRcBifurcation);

#ifdef __cplusplus
}
#endif

#endif /* DD_PCIE_RC2_H_ */
