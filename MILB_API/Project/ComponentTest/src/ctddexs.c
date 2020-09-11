/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-02
*@author              	:杨升柄
*@brief               	:CtDdExs类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "arm.h"
#include "exstop.h"
//#include "chiptop.h"
#include "dd_gpv.h"
#include "dd_exs.h"
//#include "dd_xdmafasp.h"
//#include "ddim_user_custom.h"
#include "ctddexs.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdExs, ct_dd_exs);
#define CT_DD_EXS_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdExsPrivate,CT_TYPE_DD_EXS))

struct _CtDdExsPrivate
{
	kint dat1;
};

//暂时没有地方用,自己屏蔽的
//kint32 get_val = 0;

static void ct_dd_exs_constructor(CtDdExs *self) 
{
	CtDdExsPrivate *priv = CT_DD_EXS_GET_PRIVATE(self);

	priv->dat1 = 0;
	self->priv = priv;
}

static void ct_dd_exs_destructor(CtDdExs *self) 
{
}

/*
 * PUBLIC
 *
 * Local Method Definition
 *
 * Nothing Special
 *
 * Function
 */
void ct_dd_exs_from_main(CtDdExs* self, kint argc, kchar** argv)
{
	CtDdExsPrivate* priv = self->priv;

	if( 0 == strcmp( argv[1], "get" ) ) {
		if( 0 == strcmp( argv[2], "xd_lpc" ) ) {
			if( 0 == strcmp( argv[3], "csysreq" ) ) {
				priv->dat1 = Dd_Exs_Get_XDMAC_LowPower_Ctl_CSYSREQ();
				Ddim_Print(("Dd_Exs_Get_XDMAC_LowPower_Ctl_CSYSREQ = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "csysack" ) ) {
				priv->dat1 = Dd_Exs_Get_XDMAC_LowPower_Ctl_CSYSACK();
				Ddim_Print(("Dd_Exs_Get_XDMAC_LowPower_Ctl_CSYSACK = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "cactrive" ) ) {
				priv->dat1 = Dd_Exs_Get_XDMAC_LowPower_Ctl_CSYSACK();
				Ddim_Print(("Dd_Exs_Get_XDMAC_LowPower_Ctl_CACTIVE = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "softreset" ) ) {
			if( 0 == strcmp( argv[3], "nfrstn" ) ) {
				priv->dat1 = Dd_Exs_Get_nf_rst_n_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_nf_rst_n_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "nfrstnbch" ) ) {
				priv->dat1 = Dd_Exs_Get_bch_rst_n_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_bch_rst_n_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "nfrstnreg" ) ) {
				priv->dat1 = Dd_Exs_Get_reg_rst_n_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_reg_rst_n_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "netsecrst" ) ) {
				priv->dat1 = Dd_Exs_Get_NETSEC_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_NETSEC_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "emcrst" ) ) {
				priv->dat1 = Dd_Exs_Get_eMMC_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_eMMC_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "relcrst" ) ) {
				priv->dat1 = Dd_Exs_Get_RELC_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_RELC_Soft_Reset = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "softreset2" ) ) {
			if( 0 == strcmp( argv[3], "debretx_sd3" ) ) {
				priv->dat1 = Dd_Exs_Get_SD3_CD_Debounce_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_SD3_CD_Debounce_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "debretx_sd4" ) ) {
				priv->dat1 = Dd_Exs_Get_SD4_CD_Debounce_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_SD4_CD_Debounce_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "debretx_pcie0" ) ) {
				priv->dat1 = Dd_Exs_Get_PCIE0_CD_Debounce_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_PCIE0_CD_Debounce_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "debretx_pcie1" ) ) {
				priv->dat1 = Dd_Exs_Get_PCIE1_CD_Debounce_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_PCIE1_CD_Debounce_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "debretx_usb2vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_USB2VBUS_CD_Debounce_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_USB2VBUS_CD_Debounce_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "debretx_usb2id" ) ) {
				priv->dat1 = Dd_Exs_Get_USB2ID_CD_Debounce_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_USB2ID_CD_Debounce_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "debretx_usb3vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_USB3VBUS_CD_Debounce_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_USB3VBUS_CD_Debounce_Soft_Reset = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "debretx_usb3id" ) ) {
				priv->dat1 = Dd_Exs_Get_USB3ID_CD_Debounce_Soft_Reset();
				Ddim_Print(("Dd_Exs_Get_USB3ID_CD_Debounce_Soft_Reset = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "intmask" ) ) {
			if( 0 == strcmp( argv[3], "intmsk02" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_SD3_RIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_SD3_RIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk03" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_SD3_FIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_SD3_FIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk04" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_SD4_RIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_SD4_RIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk05" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_SD4_FIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_SD4_FIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk06" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_PCIe0_RIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_PCIe0_RIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk07" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_PCIe0_FIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_PCIe0_FIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk08" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_PCIe1_RIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_PCIe1_RIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk09" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_PCIe1_FIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_PCIe1_FIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk10" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_USB2VBUS_RIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_USB2VBUS_RIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk11" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_USB2VBUS_FIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_USB2VBUS_FIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk12" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_USB2ID_RIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_USB2ID_RIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk13" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_USB2ID_FIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_USB2ID_FIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk14" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_USB3VBUS_RIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_USB3VBUS_RIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk15" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_USB3VBUS_FIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_USB3VBUS_FIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk16" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_USB3ID_RIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_USB3ID_RIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "intmsk17" ) ) {
				priv->dat1 = Dd_Exs_Get_INTMSK_USB3ID_FIM();
				Ddim_Print(("Dd_Exs_Get_INTMSK_USB3ID_FIM = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "sigmon" ) ) {
			if( 0 == strcmp( argv[3], "sigmon_sd3" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON_SD3_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON_SD3_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon_sd4" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON_SD4_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON_SD4_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon_pcie0" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON_PCIE0_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON_PCIE0_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon_pcie1" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON_PCIE1_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON_PCIE1_CD = 0x%08x\n", priv->dat1));
			}
			if( 0 == strcmp( argv[3], "sigmon_usb2vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON_USB2VBUS_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON_USB2VBUS_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon_usb2id" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON_USB2ID_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON_USB2ID_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon_usb3vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON_USB3VBUS_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON_USB3VBUS_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon_usb3id" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON_USB3ID_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON_USB3ID_CD = 0x%08x\n", priv->dat1));
			}
			if( 0 == strcmp( argv[3], "sigmon2_sd3" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON2_SD3_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON2_SD3_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon2_sd4" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON2_SD4_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON2_SD4_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon2_pcie0" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON2_PCIE0_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON2_PCIE0_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon2_pcie1" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON2_PCIE1_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON2_PCIE1_CD = 0x%08x\n", priv->dat1));
			}
			if( 0 == strcmp( argv[3], "sigmon2_usb2vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON2_USB2VBUS_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON2_USB2VBUS_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon2_usb2id" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON2_USB2ID_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON2_USB2ID_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon2_usb3vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON2_USB3VBUS_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON2_USB3VBUS_CD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sigmon2_usb3id" ) ) {
				priv->dat1 = Dd_Exs_Get_SIGMON2_USB3ID_CD();
				Ddim_Print(("Dd_Exs_Get_SIGMON2_USB3ID_CD = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "deben" ) ) {
			if( 0 == strcmp( argv[3], "deben_sd3" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_SD3_EN();
				Ddim_Print(("Dd_Exs_Get_DEBEN_SD3_EN = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "deben_sd4" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_SD4_EN();
				Ddim_Print(("Dd_Exs_Get_DEBEN_SD4_EN = 0x%08x\n", priv->dat1));
			}
			if( 0 == strcmp( argv[3], "deben_pcie0" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_PCIE0_EN();
				Ddim_Print(("Dd_Exs_Get_DEBEN_PCIE0_EN = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "deben_pcie1" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_PCIE1_EN();
				Ddim_Print(("Dd_Exs_Get_DEBEN_PCIE1_EN = 0x%08x\n", priv->dat1));
			}
			if( 0 == strcmp( argv[3], "deben_usb2vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_USB2VBUS_EN();
				Ddim_Print(("Dd_Exs_Get_DEBEN_USB2VBUS_EN = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "deben_usb2id" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_USB2ID_EN();
				Ddim_Print(("Dd_Exs_Get_DEBEN_USB2ID_EN = 0x%08x\n", priv->dat1));
			}
			if( 0 == strcmp( argv[3], "deben_usb3vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_USB3VBUS_EN();
				Ddim_Print(("Dd_Exs_Get_DEBEN_USB3VBUS_EN = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "deben_usb3id" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_USB3ID_EN();
				Ddim_Print(("Dd_Exs_Get_DEBEN_USB3ID_EN = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd3detim" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_SD3DETIM();
				Ddim_Print(("Dd_Exs_Get_DEBEN_SD3DETIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd4detim" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_SD4DETIM();
				Ddim_Print(("Dd_Exs_Get_DEBEN_SD4DETIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "pcie0detim" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_PCIE0DETIM();
				Ddim_Print(("Dd_Exs_Get_DEBEN_PCIE0DETIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "pcie1detim" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_PCIE1DETIM();
				Ddim_Print(("Dd_Exs_Get_DEBEN_PCIE1DETIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb2vbdetim" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_USB2VBUSDETIM();
				Ddim_Print(("Dd_Exs_Get_DEBEN_USB2VBUSDETIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb2iddetim" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_USB2IDDETIM();
				Ddim_Print(("Dd_Exs_Get_DEBEN_USB2IDDETIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb3vbdetim" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_USB3VBUSDETIM();
				Ddim_Print(("Dd_Exs_Get_DEBEN_USB3VBUSDETIM = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb3iddetim" ) ) {
				priv->dat1 = Dd_Exs_Get_DEBEN_USB3IDDETIM();
				Ddim_Print(("Dd_Exs_Get_DEBEN_USB3IDDETIM = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "cdinsmdctl" ) ) {
			if( 0 == strcmp( argv[3], "cdmod_sd3" ) ) {
				priv->dat1 = Dd_Exs_Get_CDINS_SD3_MOD();
				Ddim_Print(("Dd_Exs_Get_CDINS_SD3_MOD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "cdmod_sd4" ) ) {
				priv->dat1 = Dd_Exs_Get_CDINS_SD4_MOD();
				Ddim_Print(("Dd_Exs_Get_CDINS_SD4_MOD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "cdmod_pcie0" ) ) {
				priv->dat1 = Dd_Exs_Get_CDINS_PCIE0_MOD();
				Ddim_Print(("Dd_Exs_Get_CDINS_PCIE0_MOD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "cdmod_pcie1" ) ) {
				priv->dat1 = Dd_Exs_Get_CDINS_PCIE1_MOD();
				Ddim_Print(("Dd_Exs_Get_CDINS_PCIE1_MOD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "cdmod_usb2vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_CDINS_USB2VBUS_MOD();
				Ddim_Print(("Dd_Exs_Get_CDINS_USB2VBUS_MOD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "cdmod_usb2id" ) ) {
				priv->dat1 = Dd_Exs_Get_CDINS_USB2ID_MOD();
				Ddim_Print(("Dd_Exs_Get_CDINS_USB2ID_MOD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "cdmod_usb3vbus" ) ) {
				priv->dat1 = Dd_Exs_Get_CDINS_USB3VBUS_MOD();
				Ddim_Print(("Dd_Exs_Get_CDINS_USB3VBUS_MOD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "cdmod_usb3id" ) ) {
				priv->dat1 = Dd_Exs_Get_CDINS_USB3ID_MOD();
				Ddim_Print(("Dd_Exs_Get_CDINS_USB3ID_MOD = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "rlc_hpt_ctl" ) ) {
			if( 0 == strcmp( argv[3], "rerhpt" ) ) {
				priv->dat1 = Dd_Exs_Get_RELC_HPROT_Read();
				Ddim_Print(("Dd_Exs_Get_RELC_HPROT_Read = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rewhpt" ) ) {
				priv->dat1 = Dd_Exs_Get_RELC_HPROT_Write();
				Ddim_Print(("Dd_Exs_Get_RELC_HPROT_Write = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "ram_pd" ) ) {
			if( 0 == strcmp( argv[3], "rampd_sd2" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_SD2();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_SD2 = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_sd3" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_SD3();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_SD3 = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_sd4" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_SD4();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_SD4 = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_nf" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_NF();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_NF = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_relc" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_RELC();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_RELC = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_netsec" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_NETSEC();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_NETSEC = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_usb2" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_USB2();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_USB2 = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_usb3" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_USB3();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_USB3 = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_pcie0" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_PCIE0();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_PCIE0 = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_pcie1" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_PCIE1();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_PCIE1 = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "rampd_emmc" ) ) {
				priv->dat1 = Dd_Exs_Get_RAM_PD_Ctrl_EMMC();
				Ddim_Print(("Dd_Exs_Get_RAM_PD_Ctrl_EMMC = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "busckstp" ) ) {
			if( 0 == strcmp( argv[3], "nf_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_NF_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "pcie0_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_PCIE0_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_PCIE0_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "pcie1_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_PCIE1_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_PCIE1_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "xdmac_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_XDMAC_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_XDMAC_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "hdmac_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_HDMAC_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_HDMAC_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "emmc_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_EMMC_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_EMMC_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd2_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_SD2_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_SD2_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd3_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_SD3_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_SD3_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd4_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_SD4_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_SD4_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "netsec_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_NETSEC_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_NETSEC_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "relc_ckstp" ) ) {
				priv->dat1 = Dd_Exs_Get_RELC_BUS_CLOCK_Stop_Ctrl();
				Ddim_Print(("Dd_Exs_Get_RELC_BUS_CLOCK_Stop_Ctrl = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nsec_ckstp" ) ) {
			if( 0 == strcmp( argv[3], "netsec_ptpstp" ) ) {
				priv->dat1 = Dd_Exs_Get_NETSEC_PTPCLK_Stop_Ctrl_NETSEC_PTPSTP();
				Ddim_Print(("Dd_Exs_Get_NETSEC_PTPCLK_Stop_Ctrl_NETSEC_PTPSTP = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "emmc_ckstp" ) ) {
			if( 0 == strcmp( argv[3], "emclkstp" ) ) {
				priv->dat1 = Dd_Exs_Get_EMMC_CKSTP_EMCLKSTP();
				Ddim_Print(("Dd_Exs_Get_EMMC_CKSTP_EMCLKSTP = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "em_drvstr" ) ) {
			if( 0 == strcmp( argv[3], "em_dsel" ) ) {
				priv->dat1 = Dd_Exs_Get_EM_DRVSTR();
				Ddim_Print(("Dd_Exs_Get_EM_DRVSTR = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "em_pv_dtimec" ) ) {
			if( 0 == strcmp( argv[3], "pv_dtimec" ) ) {
				priv->dat1 = Dd_Exs_Get_EM_PV_DTIMEC();
				Ddim_Print(("Dd_Exs_Get_EM_PV_DTIMEC = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "em_pv_ampbl" ) ) {
			if( 0 == strcmp( argv[3], "pv_ampbl" ) ) {
				priv->dat1 = Dd_Exs_Get_EM_PV_AMPBL();
				Ddim_Print(("Dd_Exs_Get_EM_PV_AMPBL = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "em_cr_slottype" ) ) {
			if( 0 == strcmp( argv[3], "cr_slottype" ) ) {
				priv->dat1 = Dd_Exs_Get_EM_CR_SLOTTYPE();
				Ddim_Print(("Dd_Exs_Get_EM_CR_SLOTTYPE = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "em_cr_bclkfreq" ) ) {
			if( 0 == strcmp( argv[3], "cr_bclkfreq" ) ) {
				priv->dat1 = Dd_Exs_Get_EM_CR_BCLKFREQ();
				Ddim_Print(("Dd_Exs_Get_EM_CR_BCLKFREQ = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "em_cddet" ) ) {
			if( 0 == strcmp( argv[3], "emcd" ) ) {
				priv->dat1 = Dd_Exs_Get_EM_CDDET_EMCD();
				Ddim_Print(("Dd_Exs_Get_EM_CDDET_EMCD = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "emphylk" ) ) {
				priv->dat1 = Dd_Exs_Get_EM_CDDET_EMPHYLK();
				Ddim_Print(("Dd_Exs_Get_EM_CDDET_EMPHYLK = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_ip_ctl" ) ) {
			if( 0 == strcmp( argv[3], "dscv_inhibit" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_IP_CTL_DSCV_INHIBIT();
				Ddim_Print(("Dd_Exs_Get_NF_IP_CTL_DSCV_INHIBIT = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "dscv_ignr_crc" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_IP_CTL_DSCV_IGNR_CRC();
				Ddim_Print(("Dd_Exs_Get_NF_IP_CTL_DSCV_IGNR_CRC = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "boot_en" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_IP_CTL_BOOT_EN();
				Ddim_Print(("Dd_Exs_Get_NF_IP_CTL_BOOT_EN = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "iddq_en" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_IP_CTL_IDDQ_EN();
				Ddim_Print(("Dd_Exs_Get_NF_IP_CTL_IDDQ_EN = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_btsq_state" ) ) {
			if( 0 == strcmp( argv[3], "init_fail" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_BTSQ_STATE_INIT_FAIL();
				Ddim_Print(("Dd_Exs_Get_NF_BTSQ_STATE_INIT_FAIL = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "boot_comp" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_BTSQ_STATE_BOOT_COMP();
				Ddim_Print(("Dd_Exs_Get_NF_BTSQ_STATE_BOOT_COMP = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "boot_error" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_BTSQ_STATE_CTRL_BUSY();
				Ddim_Print(("Dd_Exs_Get_NF_BTSQ_STATE_CTRL_BUSY = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "boot_busy" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_BTSQ_STATE_CTRL_BUSY();
				Ddim_Print(("Dd_Exs_Get_NF_BTSQ_STATE_CTRL_BUSY = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_rb_valid_tm" ) ) {
			if( 0 == strcmp( argv[3], "rb_valid_time" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_RB_VALID_TM();
				Ddim_Print(("Dd_Exs_Get_NF_RB_VALID_TM = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_phy_ctrl_reg" ) ) {
			if( 0 == strcmp( argv[3], "phy_ctrl" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_PHY_CTRL_REG();
				Ddim_Print(("Dd_Exs_Get_NF_PHY_CTRL_REG = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_phy_dq_tim" ) ) {
			if( 0 == strcmp( argv[3], "phy_dq_timing" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_PHY_DQ_TIMING();
				Ddim_Print(("Dd_Exs_Get_NF_PHY_DQ_TIMING = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_phy_dqs_tim" ) ) {
			if( 0 == strcmp( argv[3], "phy_dqs_timing" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_PHY_DQS_TIMING();
				Ddim_Print(("Dd_Exs_Get_NF_PHY_DQS_TIMING = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_phy_gt_lpbk" ) ) {
			if( 0 == strcmp( argv[3], "phy_gt_lpbk_ctl" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_PHY_GT_LPBK_CTL();
				Ddim_Print(("Dd_Exs_Get_NF_PHY_GT_LPBK_CTL = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_phy_dll_mctl" ) ) {
			if( 0 == strcmp( argv[3], "phy_dll_mst_ctl" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_PHY_DLL_MCTL();
				Ddim_Print(("Dd_Exs_Get_NF_PHY_DLL_MCTL = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_phy_dll_sctl" ) ) {
			if( 0 == strcmp( argv[3], "phy_dll_slv_ctl" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_PHY_DLL_SCTL();
				Ddim_Print(("Dd_Exs_Get_NF_PHY_DLL_SCTL = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_boot_ecc_ctl" ) ) {
			if( 0 == strcmp( argv[3], "boot_ecc_sec_siz" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_BOOT_ECC_CTL_SEC_SIZ();
				Ddim_Print(("Dd_Exs_Get_NF_BOOT_ECC_CTL_SEC_SIZ = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "bt_ecc_corr_str" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_BOOT_ECC_CTL_CORR_STR();
				Ddim_Print(("Dd_Exs_Get_NF_BOOT_ECC_CTL_CORR_STR = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "boot_ecc_en" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_BOOT_ECC_CTL_EN();
				Ddim_Print(("Dd_Exs_Get_NF_BOOT_ECC_CTL_EN = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nf_wpx_cnt" ) ) {
			if( 0 == strcmp( argv[3], "wpx_cnt" ) ) {
				priv->dat1 = Dd_Exs_Get_NF_NFWPX_CNT();
				Ddim_Print(("Dd_Exs_Get_NF_NFWPX_CNT = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "intstat" ) ) {
			if( 0 == strcmp( argv[3], "sd2_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_SD2_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_SD2_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd2_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_SD2_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_SD2_FIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd3_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_SD3_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_SD3_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd3_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_SD3_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_SD3_FIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd4_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_SD4_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_SD4_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "sd4_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_SD4_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_SD4_FIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "pcie0_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_PCIe0_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_PCIe0_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "pcie0_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_PCIe0_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_PCIe0_FIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "pcie1_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_PCIe1_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_PCIe1_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "pcie1_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_PCIe1_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_PCIe1_FIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb2vbus_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_USB2VBUS_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_USB2VBUS_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb2vbus_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_USB2VBUS_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_USB2VBUS_FIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb2id_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_USB2ID_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_USB2ID_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb2id_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_USB2ID_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_USB2ID_FIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb3vbus_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_USB3VBUS_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_USB3VBUS_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb3vbus_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_USB3VBUS_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_USB3VBUS_FIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb3id_ris" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_USB3ID_RIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_USB3ID_RIS = 0x%08x\n", priv->dat1));
			}else if( 0 == strcmp( argv[3], "usb3id_fis" ) ) {
				priv->dat1 = Dd_Exs_Get_INTSTAT_USB3ID_FIS();
				Ddim_Print(("Dd_Exs_Get_INTSTAT_USB3ID_FIS = 0x%08x\n", priv->dat1));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else
		{
			// Input parameter NG
			Ddim_Print(("please check 2nd parameter!!\n"));
		}
	}
}

CtDdExs* ct_dd_exs_new(void) 
{
    CtDdExs *self = k_object_new_with_private(CT_TYPE_DD_EXS, sizeof(CtDdExsPrivate));
    return self;
}
