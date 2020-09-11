/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :杨升柄
*@brief               :CtDdGpvMain类
*@rely                :klib
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
#include "dd_gpv.h"
#include "ctddgpv.h"
#include "ctddgpvmain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdGpvMain, ct_dd_gpv_main);
#define CT_DD_GPV_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdGpvMainPrivate,CT_TYPE_DD_GPV_MAIN))

struct _CtDdGpvMainPrivate
{
	CtDdGpv* cdGpv;
};

static kint S_DAT1 = 0;
static kint S_DAT2 = 0;
static kint S_DAT3 = 0;
static kint S_DAT4 = 0;
//static kint dat5 = 0;

static T_DD_GPV_CTRL_M	S_DAT_M_GET;
static T_DD_GPV_CTRL_M	S_DAT_M_SET;

static T_DD_GPV_CTRL_S	S_DAT_S_GET;
static T_DD_GPV_CTRL_S	S_DAT_S_SET;

static T_DD_GPV_CTRL_IB	S_DAT_IB_GET;
static T_DD_GPV_CTRL_IB	S_DAT_IB_SET;

static void ct_dd_gpv_main_constructor(CtDdGpvMain *self) 
{
	CtDdGpvMainPrivate *priv = CT_DD_GPV_MAIN_GET_PRIVATE(self);
	priv->cdGpv = ct_dd_gpv_new();
	self->priv = priv;
}

static void ct_dd_gpv_main_destructor(CtDdGpvMain *self) 
{
	CtDdGpvMainPrivate *priv = CT_DD_GPV_MAIN_GET_PRIVATE(self);
	if(priv->cdGpv)
	{
		k_object_unref(priv->cdGpv);
	}
	priv->cdGpv = NULL;
}

/*
 * PUBLIC
 *
 * Local Method Definition
 *
 * Nothing Special
 *
 * Function
 *
 * @brief  Command main function for GPV test.
 * @param  kint argc	:The number of parameters
 *		   kchar** argv	:The value of parameters
 * @return void
 *
 * The meaning of parameters
 * +=======+=====+==================+=======+=======+=======================================================+
 * | P0    | P1  | P2               | P3    | P4    | Meaning                                               |
 * +=======+=====+==================+=======+=======+=======================================================+
 * | ddgpv | get | m_usb3_r_ib      |       |       | Get and display the registers of M_Usb3_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_emmc_r_ib      |       |       | Get and display the registers of M_Emmc_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_uhs2_r_ib      |       |       | Get and display the registers of M_Uhs2_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_mxic1_m_ib     |       |       | Get and display the registers of M_Mxic1_m_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_mxic2_m_ib     |       |       | Get and display the registers of M_Mxic2_m_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_xdmac_r_ib     |       |       | Get and display the registers of M_Xdmac_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_nf_r_ib        |       |       | Get and display the registers of M_Nf_r_ib.           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_pcie0_r_ib     |       |       | Get and display the registers of M_Pcie0_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_pcie1_r_ib     |       |       | Get and display the registers of M_Pcie1_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_nicperiahb_m   |       |       | Get and display the registers of M_NicPeriAHB_m_ib.   |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_nicbmahb1_r    |       |       | Get and display the registers of M_NicBmAHB1_r_ib.    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | nsecx2p_ib       |       |       | Get and display the registers of NsecX2P_ib.          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | toprx2p_ib       |       |       | Get and display the registers of ToprX2P_ib.          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | m_nicbmahb2_r_ib |       |       | Get and display the registers of M_NicBmAHB2_r_ib.    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_main_rm_ib     |       |       | Get and display the registers of S_Main_rm_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_xdmac_m_ib     |       |       | Get and display the registers of S_Xdmac_m_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_netsec_m       |       |       | Get and display the registers of S_Netsec_m.          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_wifiahb_m_ib   |       |       | Get and display the registers of S_WifiAHB_m_ib.      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_uhs2ahb_m      |       |       | Get and display the registers of S_Uhs2AHB_m.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_relcrahb_m     |       |       | Get and display the registers of S_RelcrAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_uhs1ahb_m      |       |       | Get and display the registers of S_Uhs1AHB_m.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_relcwahb_m     |       |       | Get and display the registers of S_RelcwAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_bmnicahb_m     |       |       | Get and display the registers of S_BmNicAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_usb2ahb_ehci   |       |       | Get and display the registers of S_Usb2AHB_ehci.      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_usb2ahb_ohci   |       |       | Get and display the registers of S_Usb2AHB_ohci.      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | s_netsec2_m      |       |       | Get and display the registers of S_Netsec2_m.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | ib8              |       |       | Get and display the registers of ib8.                 |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | ib13             |       |       | Get and display the registers of ib13.                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | ib12             |       |       | Get and display the registers of ib12.                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | get | ib9              |       |       | Get and display the registers of ib9.                 |
 * +=======+=====+==================+=======+=======+=======================================================+
 * | ddgpv | set | m_usb3_r_ib      | fmib  | [val] | It set M_Usb3_r_ib fn_mod_iss_bm.                     |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_usb3_r_ib      | fm2   | [val] | It set M_Usb3_r_ib fn_mod2.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_usb3_r_ib      | fml   | [val] | It set M_Usb3_r_ib fn_mod_lb.                         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_usb3_r_ib      | fm    | [val] | It set M_Usb3_r_ib fn_mod.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_emmc_r_ib      | fmib  | [val] | It set M_Emmc_r_ib fn_mod_iss_bm.                     |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_emmc_r_ib      | fm2   | [val] | It set M_Emmc_r_ib fn_mod2.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_emmc_r_ib      | fml   | [val] | It set M_Emmc_r_ib fn_mod_lb.                         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_emmc_r_ib      | fm    | [val] | It set M_Emmc_r_ib fn_mod.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_uhs2_r_ib      | fmib  | [val] | It set M_Uhs2_r_ib fn_mod_iss_bm.                     |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_uhs2_r_ib      | fm2   | [val] | It set M_Uhs2_r_ib fn_mod2.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_uhs2_r_ib      | fml   | [val] | It set M_Uhs2_r_ib fn_mod_lb.                         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_uhs2_r_ib      | fm    | [val] | It set M_Uhs2_r_ib fn_mod.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_mxic1_m_ib     | fmib  | [val] | It set M_Mxic1_m_ib fn_mod_iss_bm.                    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_mxic1_m_ib     | wt    | [val] | It set M_Mxic1_m_ib wr_tidemark.                      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_mxic1_m_ib     | fm    | [val] | It set M_Mxic1_m_ib fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_mxic2_m_ib     | fmib  | [val] | It set M_Mxic2_m_ib fn_mod_iss_bm.                    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_mxic2_m_ib     | wt    | [val] | It set M_Mxic2_m_ib wr_tidemark.                      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_mxic2_m_ib     | fm    | [val] | It set M_Mxic2_m_ib fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_xdmac_r_ib     | fmib  | [val] | It set M_Xdmac_r_ib fn_mod_iss_bm.                    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_xdmac_r_ib     | fm2   | [val] | It set M_Xdmac_r_ib fn_mod2.                          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_xdmac_r_ib     | fm    | [val] | It set M_Xdmac_r_ib fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nf_r_ib        | fmib  | [val] | It set M_Nf_r_ib fn_mod_iss_bm.                       |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nf_r_ib        | fm2   | [val] | It set M_Nf_r_ib fn_mod2.                             |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nf_r_ib        | fml   | [val] | It set M_Nf_r_ib fn_mod_lb.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nf_r_ib        | fm    | [val] | It set M_Nf_r_ib fn_mod.                              |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_pcie0_r_ib     | fmib  | [val] | It set M_Pcie0_r_ib fn_mod_iss_bm.                    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_pcie0_r_ib     | fm2   | [val] | It set M_Pcie0_r_ib fn_mod2.                          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_pcie0_r_ib     | fml   | [val] | It set M_Pcie0_r_ib fn_mod_lb.                        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_pcie0_r_ib     | fm    | [val] | It set M_Pcie0_r_ib fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_pcie1_r_ib     | fmib  | [val] | It set M_Pcie1_r_ib fn_mod_iss_bm.                    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_pcie1_r_ib     | fm2   | [val] | It set M_Pcie1_r_ib fn_mod2.                          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_pcie1_r_ib     | fml   | [val] | It set M_Pcie1_r_ib fn_mod_lb.                        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_pcie1_r_ib     | fm    | [val] | It set M_Pcie1_r_ib fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nicperiahb_m   | fmib  | [val] | It set M_NicPeriAHB_m_ib fn_mod_iss_bm.               |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nicperiahb_m   | fm2   | [val] | It set M_NicPeriAHB_m_ib fn_mod2.                     |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nicperiahb_m   | ac    | [val] | It set M_NicPeriAHB_m ahb_cntl.                       |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nicbmahb1_r    | fmib  | [val] | It set M_NicBmAHB1_r_ib fn_mod_iss_bm.                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nicbmahb1_r    | ac    | [val] | It set M_NicBmAHB1_r ahb_cntl.                        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | nsecx2p_ib       | fmib  | [val] | It set NsecX2P_ib fn_mod_iss_bm.                      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | nsecx2p_ib       | fm2   | [val] | It set NsecX2P_ib fn_mod2.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | toprx2p_ib       | fmib  | [val] | It set ToprX2P_ib fn_mod_iss_bm.                      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | toprx2p_ib       | fm2   | [val] | It set ToprX2P_ib fn_mod2.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nicbmahb2_r_ib | fmib  | [val] | It set M_NicBmAHB2_r_ib fn_mod_iss_bm.                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nicbmahb2_r_ib | fm2   | [val] | It set M_NicBmAHB2_r_ib fn_mod2.                      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | m_nicbmahb2_r_ib | ac    | [val] | It set M_NicBmAHB2_r ahb_cntl.                        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_main_rm_ib     | fm    | [val] | It set S_Main_rm_ib fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_xdmac_m_ib     | fm    | [val] | It set S_Xdmac_m_ib fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_netsec_m       | fm    | [val] | It set S_Netsec_m fn_mod.                             |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_wifiahb_m_ib   | fma   | [val] | It set S_WifiAHB_m_ib fn_mod_ahb.                     |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_wifiahb_m_ib   | fm    | [val] | It set S_WifiAHB_m_ib fn_mod.                         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_uhs2ahb_m      | fma   | [val] | It set S_Uhs2AHB_m fn_mod_ahb.                        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_uhs2ahb_m      | fm    | [val] | It set S_Uhs2AHB_m fn_mod.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_relcrahb_m     | fma   | [val] | It set S_RelcrAHB_m fn_mod_ahb.                       |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_relcrahb_m     | fm    | [val] | It set S_RelcrAHB_m fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_uhs1ahb_m      | fma   | [val] | It set S_Uhs1AHB_m fn_mod_ahb.                        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_uhs1ahb_m      | fm    | [val] | It set S_Uhs1AHB_m fn_mod.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_relcwahb_m     | fma   | [val] | It set S_RelcwAHB_m fn_mod_ahb.                       |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_relcwahb_m     | fm    | [val] | It set S_RelcwAHB_m fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_bmnicahb_m     | fma   | [val] | It set S_BmNicAHB_m fn_mod_ahb.                       |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_bmnicahb_m     | fm    | [val] | It set S_BmNicAHB_m fn_mod.                           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_usb2ahb_ehci   | fma   | [val] | It set S_Usb2AHB_ehci fn_mod_ahb.                     |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_usb2ahb_ehci   | fm    | [val] | It set S_Usb2AHB_ehci fn_mod.                         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_usb2ahb_ohci   | fma   | [val] | It set S_Usb2AHB_ohci fn_mod_ahb.                     |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_usb2ahb_ohci   | fm    | [val] | It set S_Usb2AHB_ohci fn_mod.                         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | s_netsec2_m      | fm    | [val] | It set S_Netsec2_m fn_mod.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib8              | fmib  | [val] | It set ib8 fn_mod_iss_bm.                             |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib8              | fm2   | [val] | It set ib8 fn_mod2.                                   |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib8              | wt    | [val] | It set ib8 wr_tidemark.                               |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib8              | fm    | [val] | It set ib8 fn_mod.                                    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib13             | fmib  | [val] | It set ib13 fn_mod_iss_bm.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib13             | fm2   | [val] | It set ib13 fn_mod2.                                  |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib13             | fml   | [val] | It set ib13 fn_mod_lb.                                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib13             | fm    | [val] | It set ib13 fn_mod.                                   |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib12             | fmib  | [val] | It set ib12 fn_mod_iss_bm.                            |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib12             | fm2   | [val] | It set ib12 fn_mod2.                                  |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib12             | fm    | [val] | It set ib12 fn_mod.                                   |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib9              | fmib  | [val] | It set ib9 fn_mod_iss_bm.                             |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib9              | fm2   | [val] | It set ib9 fn_mod2.                                   |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib9              | wt    | [val] | It set ib9 wr_tidemark.                               |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | ib9              | fm    | [val] | It set ib9 fn_mod.                                    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | set | remap            |       |       | It set remap.                                         |
 * +=======+=====+==================+=======+=======+=======================================================+
 * | ddgpv | all | m_usb3_r_ib      | get   |       | Get and display the registers of M_Usb3_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_emmc_r_ib      | get   |       | Get and display the registers of M_Emmc_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_uhs2_r_ib      | get   |       | Get and display the registers of M_Uhs2_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_mxic1_m_ib     | get   |       | Get and display the registers of M_Mxic1_m_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_mxic2_m_ib     | get   |       | Get and display the registers of M_Mxic2_m_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_xdmac_r_ib     | get   |       | Get and display the registers of M_Xdmac_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_nf_r_ib        | get   |       | Get and display the registers of M_Nf_r_ib.           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_pcie0_r_ib     | get   |       | Get and display the registers of M_Pcie0_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_pcie1_r_ib     | get   |       | Get and display the registers of M_Pcie1_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_nicperiahb_m   | get   |       | Get and display the registers of M_NicPeriAHB_m_ib.   |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_nicbmahb1_r    | get   |       | Get and display the registers of M_NicBmAHB1_r_ib.    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | nsecx2p_ib       | get   |       | Get and display the registers of NsecX2P_ib.          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | toprx2p_ib       | get   |       | Get and display the registers of ToprX2P_ib.          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_nicbmahb2_r_ib | get   |       | Get and display the registers of M_NicBmAHB2_r_ib.    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_main_rm_ib     | get   |       | Get and display the registers of S_Main_rm_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_uhs2ahb_m      | get   |       | Get and display the registers of S_Uhs2AHB_m.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_relcrahb_m     | get   |       | Get and display the registers of S_RelcrAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_uhs1ahb_m      | get   |       | Get and display the registers of S_Uhs1AHB_m.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_relcwahb_m     | get   |       | Get and display the registers of S_RelcwAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_bmnicahb_m     | get   |       | Get and display the registers of S_BmNicAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_usb2ahb_ehci   | get   |       | Get and display the registers of S_Usb2AHB_ehci.      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_usb2ahb_ohci   | get   |       | Get and display the registers of S_Usb2AHB_ohci.      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | ib8              | get   |       | Get and display the registers of ib8.                 |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | ib13             | get   |       | Get and display the registers of ib13.                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | ib12             | get   |       | Get and display the registers of ib12.                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | ib9              | get   |       | Get and display the registers of ib9.                 |
 * +=======+=====+==================+=======+=======+=======================================================+
 * | ddgpv | all | m_usb3_r_ib      | set   | [val] | Get and display the registers of M_Usb3_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_emmc_r_ib      | set   | [val] | Get and display the registers of M_Emmc_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_uhs2_r_ib      | set   | [val] | Get and display the registers of M_Uhs2_r_ib.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_mxic1_m_ib     | set   | [val] | Get and display the registers of M_Mxic1_m_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_mxic2_m_ib     | set   | [val] | Get and display the registers of M_Mxic2_m_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_xdmac_r_ib     | set   | [val] | Get and display the registers of M_Xdmac_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_nf_r_ib        | set   | [val] | Get and display the registers of M_Nf_r_ib.           |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_pcie0_r_ib     | set   | [val] | Get and display the registers of M_Pcie0_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_pcie1_r_ib     | set   | [val] | Get and display the registers of M_Pcie1_r_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_nicperiahb_m   | set   | [val] | Get and display the registers of M_NicPeriAHB_m_ib.   |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_nicbmahb1_r    | set   | [val] | Get and display the registers of M_NicBmAHB1_r_ib.    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | nsecx2p_ib       | set   | [val] | Get and display the registers of NsecX2P_ib.          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | toprx2p_ib       | set   | [val] | Get and display the registers of ToprX2P_ib.          |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | m_nicbmahb2_r_ib | set   | [val] | Get and display the registers of M_NicBmAHB2_r_ib.    |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_main_rm_ib     | set   | [val] | Get and display the registers of S_Main_rm_ib.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_uhs2ahb_m      | set   | [val] | Get and display the registers of S_Uhs2AHB_m.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_relcrahb_m     | set   | [val] | Get and display the registers of S_RelcrAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_uhs1ahb_m      | set   | [val] | Get and display the registers of S_Uhs1AHB_m.         |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_relcwahb_m     | set   | [val] | Get and display the registers of S_RelcwAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_bmnicahb_m     | set   | [val] | Get and display the registers of S_BmNicAHB_m.        |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_usb2ahb_ehci   | set   | [val] | Get and display the registers of S_Usb2AHB_ehci.      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | s_usb2ahb_ohci   | set   | [val] | Get and display the registers of S_Usb2AHB_ohci.      |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | ib8              | set   | [val] | Get and display the registers of ib8.                 |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | ib13             | set   | [val] | Get and display the registers of ib13.                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | ib12             | set   | [val] | Get and display the registers of ib12.                |
 * +-------+-----+------------------+-------+-------+-------------------------------------------------------+
 * | ddgpv | all | ib9              | set   | [val] | Get and display the registers of ib9.                 |
 * +=======+=====+==================+=======+=======+=======================================================+
*/


void ct_dd_gpv_main_test(CtDdGpvMain* self, kint argc, kchar** argv)
{
/*
 * サンプル
 * 1. 現在の状態を取得。
 * ddgpv get m_usb3_r_ib
 * 2. 設定
 * ddgpv set m_usb3_r_ib fmib [val]
 * 3. 変更後の状態を確認
 * ddgpv get m_usb3_r_ib
 */

	 CtDdGpvMainPrivate* priv = self->priv;

	 ct_dd_gpv_from_main(priv->cdGpv, argc, argv);

	if( 0 == strcmp( argv[1], "get" ) ) {
		if( 0 == strcmp( argv[2], "m_usb3_r_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Usb3_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Usb3_r_ib_FM2();
			S_DAT4 = Dd_GPV_Get_M_Usb3_r_ib_FM();
			Ddim_Print(("M_Usb3_r_ib(FMIB) = 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Usb3_r_ib(FM2)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Usb3_r_ib(FM)   = 0x%08x\n", S_DAT4));
		}else if( 0 == strcmp( argv[2], "m_emmc_r_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Emmc_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Emmc_r_ib_FM2();
			S_DAT3 = Dd_GPV_Get_M_Emmc_r_ib_FML();
			S_DAT4 = Dd_GPV_Get_M_Emmc_r_ib_FM();
			Ddim_Print(("M_Emmc_r_ib(FMIB) = 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Emmc_r_ib(FM2)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Emmc_r_ib(FML)  = 0x%08x\n", S_DAT3));
			Ddim_Print(("M_Emmc_r_ib(FM)   = 0x%08x\n", S_DAT4));
		}else if( 0 == strcmp( argv[2], "m_uhs2_r_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Uhs2_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Uhs2_r_ib_FM2();
			S_DAT3 = Dd_GPV_Get_M_Uhs2_r_ib_FML();
			S_DAT4 = Dd_GPV_Get_M_Uhs2_r_ib_FM();
			Ddim_Print(("M_Uhs2_r_ib(FMIB) = 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Uhs2_r_ib(FM2)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Uhs2_r_ib(FML)  = 0x%08x\n", S_DAT3));
			Ddim_Print(("M_Uhs2_r_ib(FM)   = 0x%08x\n", S_DAT4));
		}else if( 0 == strcmp( argv[2], "m_mxic1_m_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Mxic1_m_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Mxic1_m_ib_WT();
			S_DAT3 = Dd_GPV_Get_M_Mxic1_m_ib_FM();
			Ddim_Print(("M_Mxic1_m_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Mxic1_m_ib(WT)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Mxic1_m_ib(FM)  = 0x%08x\n", S_DAT3));
		}else if( 0 == strcmp( argv[2], "m_mxic2_m_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Mxic2_m_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Mxic2_m_ib_WT();
			S_DAT3 = Dd_GPV_Get_M_Mxic2_m_ib_FM();
			Ddim_Print(("M_Mxic2_m_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Mxic2_m_ib(WT)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Mxic2_m_ib(FM)  = 0x%08x\n", S_DAT3));
		}else if( 0 == strcmp( argv[2], "m_xdmac_r_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Xdmac_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Xdmac_r_ib_FM2();
			S_DAT3 = Dd_GPV_Get_M_Xdmac_r_ib_FM();
			Ddim_Print(("M_Xdmac_r_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Xdmac_r_ib(FM2) = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Xdmac_r_ib(FM)  = 0x%08x\n", S_DAT3));
		}else if( 0 == strcmp( argv[2], "m_nf_r_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Nf_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Nf_r_ib_FM2();
			S_DAT3 = Dd_GPV_Get_M_Nf_r_ib_FML();
			S_DAT4 = Dd_GPV_Get_M_Nf_r_ib_FM();
			Ddim_Print(("M_Nf_r_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Nf_r_ib(FM2) = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Nf_r_ib(FML) = 0x%08x\n", S_DAT3));
			Ddim_Print(("M_Nf_r_ib(FM)  = 0x%08x\n", S_DAT4));
		}else if( 0 == strcmp( argv[2], "m_pcie0_r_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Pcie0_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Pcie0_r_ib_FM2();
			S_DAT3 = Dd_GPV_Get_M_Pcie0_r_ib_FML();
			S_DAT4 = Dd_GPV_Get_M_Pcie0_r_ib_FM();
			Ddim_Print(("M_Pcie0_r_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Pcie0_r_ib(FM2) = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Pcie0_r_ib(FML) = 0x%08x\n", S_DAT3));
			Ddim_Print(("M_Pcie0_r_ib(FM)  = 0x%08x\n", S_DAT4));
		}else if( 0 == strcmp( argv[2], "m_pcie1_r_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_Pcie1_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_Pcie1_r_ib_FM2();
			S_DAT3 = Dd_GPV_Get_M_Pcie1_r_ib_FML();
			S_DAT4 = Dd_GPV_Get_M_Pcie1_r_ib_FM();
			Ddim_Print(("M_Pcie1_r_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_Pcie1_r_ib(FM2) = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_Pcie1_r_ib(FML) = 0x%08x\n", S_DAT3));
			Ddim_Print(("M_Pcie1_r_ib(FM)  = 0x%08x\n", S_DAT4));
		}else if( 0 == strcmp( argv[2], "m_nicperiahb_m" ) ) {
			S_DAT1 = Dd_GPV_Get_M_NicPeriAHB_m_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_NicPeriAHB_m_ib_FM2();
			S_DAT3 = Dd_GPV_Get_M_NicPeriAHB_m_AC();
			Ddim_Print(("M_NicPeriAHB_m_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_NicPeriAHB_m_ib(FM2) = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_NicPeriAHB_m_ib(AC)  = 0x%08x\n", S_DAT3));
		}else if( 0 == strcmp( argv[2], "m_nicbmahb1_r" ) ) {
			S_DAT1 = Dd_GPV_Get_M_NicBmAHB1_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_NicBmAHB1_r_AC();
			Ddim_Print(("M_NicBmAHB1_r_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_NicBmAHB1_r_ib(AC)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "nsecx2p_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_NsecX2P_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_NsecX2P_ib_FM2();
			Ddim_Print(("NsecX2P_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("NsecX2P_ib(FM2) = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "toprx2p_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_ToprX2P_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_ToprX2P_ib_FM2();
			Ddim_Print(("ToprX2P_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("ToprX2P_ib(FM2) = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "m_nicbmahb2_r_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_M_NicBmAHB2_r_ib_FMIB();
			S_DAT2 = Dd_GPV_Get_M_NicBmAHB2_r_ib_FM2();
			S_DAT3 = Dd_GPV_Get_M_NicBmAHB2_r_AC();
			Ddim_Print(("M_NicBmAHB2_r_ib(FMIB)= 0x%08x\n", S_DAT1));
			Ddim_Print(("M_NicBmAHB2_r_ib(FM2) = 0x%08x\n", S_DAT2));
			Ddim_Print(("M_NicBmAHB2_r_ib(AC)  = 0x%08x\n", S_DAT3));
		}else if( 0 == strcmp( argv[2], "s_main_rm_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_S_Main_rm_ib_FM();
			Ddim_Print(("S_Main_rm_ib(FM) = 0x%08x\n", S_DAT1));
		}else if( 0 == strcmp( argv[2], "s_xdmac_m_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_S_Xdmac_m_ib_FM();
			Ddim_Print(("S_Xdmac_m_ib(FM) = 0x%08x\n", S_DAT1));
		}else if( 0 == strcmp( argv[2], "s_netsec_m" ) ) {
			S_DAT1 = Dd_GPV_Get_S_Netsec_m_FM();
			Ddim_Print(("S_Netsec_m(FM)= 0x%08x\n", S_DAT1));
		}else if( 0 == strcmp( argv[2], "s_wifiahb_m_ib" ) ) {
			S_DAT1 = Dd_GPV_Get_S_WifiAHB_m_FMA();
			S_DAT2 = Dd_GPV_Get_S_WifiAHB_m_ib_FM();
			Ddim_Print(("S_WifiAHB_m_ib(FMA) = 0x%08x\n", S_DAT1));
			Ddim_Print(("S_WifiAHB_m_ib(FM)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "s_uhs2ahb_m" ) ) {
			S_DAT1 = Dd_GPV_Get_S_Uhs2AHB_m_FMA();
			S_DAT2 = Dd_GPV_Get_S_Uhs2AHB_m_FM();
			Ddim_Print(("S_Uhs2AHB_m(FMA) = 0x%08x\n", S_DAT1));
			Ddim_Print(("S_Uhs2AHB_m(FM)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "s_relcrahb_m" ) ) {
			S_DAT1 = Dd_GPV_Get_S_RelcrAHB_m_FMA();
			S_DAT2 = Dd_GPV_Get_S_RelcrAHB_m_FM();
			Ddim_Print(("S_RelcrAHB_m(FMA) = 0x%08x\n", S_DAT1));
			Ddim_Print(("S_RelcrAHB_m(FM)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "s_uhs1ahb_m" ) ) {
			S_DAT1 = Dd_GPV_Get_S_Uhs1AHB_m_FMA();
			S_DAT2 = Dd_GPV_Get_S_Uhs1AHB_m_FM();
			Ddim_Print(("S_Uhs1AHB_m(FMA) = 0x%08x\n", S_DAT1));
			Ddim_Print(("S_Uhs1AHB_m(FM)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "s_relcwahb_m" ) ) {
			S_DAT1 = Dd_GPV_Get_S_RelcwAHB_m_FMA();
			S_DAT2 = Dd_GPV_Get_S_RelcwAHB_m_FM();
			Ddim_Print(("S_RelcwAHB_m(FMA) = 0x%08x\n", S_DAT1));
			Ddim_Print(("S_RelcwAHB_m(FM)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "s_bmnicahb_m" ) ) {
			S_DAT1 = Dd_GPV_Get_S_BmNicAHB_m_FMA();
			S_DAT2 = Dd_GPV_Get_S_BmNicAHB_m_FM();
			Ddim_Print(("S_BmNicAHB_m(FMA) = 0x%08x\n", S_DAT1));
			Ddim_Print(("S_BmNicAHB_m(FM)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "s_usb2ahb_ehci" ) ) {
			S_DAT1 = Dd_GPV_Get_S_Usb2AHB_ehci_FMA();
			S_DAT2 = Dd_GPV_Get_S_Usb2AHB_ehci_FM();
			Ddim_Print(("S_Usb2AHB_ehci(FMA) = 0x%08x\n", S_DAT1));
			Ddim_Print(("S_Usb2AHB_ehci(FM)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "s_usb2ahb_ohci" ) ) {
			S_DAT1 = Dd_GPV_Get_S_Usb2AHB_ohci_FMA();
			S_DAT2 = Dd_GPV_Get_S_Usb2AHB_ohci_FM();
			Ddim_Print(("S_Usb2AHB_ohci(FMA) = 0x%08x\n", S_DAT1));
			Ddim_Print(("S_Usb2AHB_ohci(FM)  = 0x%08x\n", S_DAT2));
		}else if( 0 == strcmp( argv[2], "s_netsec2_m" ) ) {
			S_DAT1 = Dd_GPV_Get_S_Netsec2_m_FM();
			Ddim_Print(("S_Netsec2_m(FM)  = 0x%08x\n", S_DAT1));
		}else if( 0 == strcmp( argv[2], "ib8" ) ) {
			S_DAT1 = Dd_GPV_Get_IB8_FMIB();
			S_DAT2 = Dd_GPV_Get_IB8_FM2();
			S_DAT3 = Dd_GPV_Get_IB8_WT();
			S_DAT4 = Dd_GPV_Get_IB8_FM();
			Ddim_Print(("IB8(FMIB) = 0x%08x\n", S_DAT1));
			Ddim_Print(("IB8(FM2)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("IB8(WT)   = 0x%08x\n", S_DAT3));
			Ddim_Print(("IB8(FM)   = 0x%08x\n", S_DAT4));
		}else if( 0 == strcmp( argv[2], "ib13" ) ) {
			S_DAT1 = Dd_GPV_Get_IB13_FMIB();
			S_DAT2 = Dd_GPV_Get_IB13_FM2();
			S_DAT3 = Dd_GPV_Get_IB13_FML();
			S_DAT4 = Dd_GPV_Get_IB13_FM();
			Ddim_Print(("IB13(FMIB) = 0x%08x\n", S_DAT1));
			Ddim_Print(("IB13(FM2)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("IB13(FML)  = 0x%08x\n", S_DAT3));
			Ddim_Print(("IB13(FM)   = 0x%08x\n", S_DAT4));
		}else if( 0 == strcmp( argv[2], "ib12" ) ) {
			S_DAT1 = Dd_GPV_Get_IB12_FMIB();
			S_DAT2 = Dd_GPV_Get_IB12_FM2();
			S_DAT3 = Dd_GPV_Get_IB12_FM();
			Ddim_Print(("IB12(FMIB) = 0x%08x\n", S_DAT1));
			Ddim_Print(("IB12(FM2)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("IB12(FM)   = 0x%08x\n", S_DAT3));
		}else if( 0 == strcmp( argv[2], "ib9" ) ) {
			S_DAT1 = Dd_GPV_Get_IB9_FMIB();
			S_DAT2 = Dd_GPV_Get_IB9_FM2();
			S_DAT3 = Dd_GPV_Get_IB9_WT();
			S_DAT4 = Dd_GPV_Get_IB9_FM();
			Ddim_Print(("IB9(FMIB) = 0x%08x\n", S_DAT1));
			Ddim_Print(("IB9(FM2)  = 0x%08x\n", S_DAT2));
			Ddim_Print(("IB9(WT)   = 0x%08x\n", S_DAT3));
			Ddim_Print(("IB9(FM)   = 0x%08x\n", S_DAT4));
		}else{
			// Input parameter NG
			Ddim_Print(("please check 2nd parameter!!\n"));
		}
	}else if( 0 == strcmp( argv[1], "all" ) ) {
		priv->cdGpv->input = atoi(argv[4]);
		//-------------------------------------------------------//
		if( 0 == strcmp( argv[3], "get" ) ) {
			if( 0 == strcmp( argv[2], "m_usb3_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Usb3_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Usb3_r_ib(FMIB) = 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Usb3_r_ib(FM2)  = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_Usb3_r_ib(FM)   = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_emmc_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Emmc_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Emmc_r_ib(FMIB) = 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Emmc_r_ib(FM2)  = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_Emmc_r_ib(FML)  = 0x%08lx\n", S_DAT_M_GET.FML));
				Ddim_Print(("M_Emmc_r_ib(FM)   = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_uhs2_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Uhs2_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Uhs2_r_ib(FMIB) = 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Uhs2_r_ib(FM2)  = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_Uhs2_r_ib(FML)  = 0x%08lx\n", S_DAT_M_GET.FML));
				Ddim_Print(("M_Uhs2_r_ib(FM)   = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_mxic1_m_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Mxic1_m_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Mxic1_m_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Mxic1_m_ib(WT)  = 0x%08lx\n", S_DAT_M_GET.WT));
				Ddim_Print(("M_Mxic1_m_ib(FM)  = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_mxic2_m_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Mxic2_m_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Mxic2_m_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Mxic2_m_ib(WT)  = 0x%08lx\n", S_DAT_M_GET.WT));
				Ddim_Print(("M_Mxic2_m_ib(FM)  = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_xdmac_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Xdmac_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Xdmac_r_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Xdmac_r_ib(FM2) = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_Xdmac_r_ib(FM)  = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_nf_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Nf_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Nf_r_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Nf_r_ib(FM2) = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_Nf_r_ib(FML) = 0x%08lx\n", S_DAT_M_GET.FML));
				Ddim_Print(("M_Nf_r_ib(FM)  = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_pcie0_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Pcie0_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Pcie0_r_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Pcie0_r_ib(FM2) = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_Pcie0_r_ib(FML) = 0x%08lx\n", S_DAT_M_GET.FML));
				Ddim_Print(("M_Pcie0_r_ib(FM)  = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_pcie1_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_Pcie1_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_Pcie1_r_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_Pcie1_r_ib(FM2) = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_Pcie1_r_ib(FML) = 0x%08lx\n", S_DAT_M_GET.FML));
				Ddim_Print(("M_Pcie1_r_ib(FM)  = 0x%08lx\n", S_DAT_M_GET.FM));
			}else if( 0 == strcmp( argv[2], "m_nicperiahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_NicPeriAHB_m_ib(&S_DAT_M_GET);
				Ddim_Print(("M_NicPeriAHB_m_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_NicPeriAHB_m_ib(FM2) = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_NicPeriAHB_m_ib(AC)  = 0x%08lx\n", S_DAT_M_GET.AC));
			}else if( 0 == strcmp( argv[2], "m_nicbmahb1_r" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_NicBmAHB1_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_NicBmAHB1_r_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_NicBmAHB1_r_ib(AC)  = 0x%08lx\n", S_DAT_M_GET.AC));
			}else if( 0 == strcmp( argv[2], "nsecx2p_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_NsecX2P_ib(&S_DAT_M_GET);
				Ddim_Print(("NsecX2P_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("NsecX2P_ib(FM2) = 0x%08lx\n", S_DAT_M_GET.FM2));
			}else if( 0 == strcmp( argv[2], "toprx2p_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_ToprX2P_ib(&S_DAT_M_GET);
				Ddim_Print(("ToprX2P_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("ToprX2P_ib(FM2) = 0x%08lx\n", S_DAT_M_GET.FM2));
			}else if( 0 == strcmp( argv[2], "m_nicbmahb2_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_M_NicBmAHB2_r_ib(&S_DAT_M_GET);
				Ddim_Print(("M_NicBmAHB2_r_ib(FMIB)= 0x%08lx\n", S_DAT_M_GET.FMIB));
				Ddim_Print(("M_NicBmAHB2_r_ib(FM2) = 0x%08lx\n", S_DAT_M_GET.FM2));
				Ddim_Print(("M_NicBmAHB2_r_ib(AC)  = 0x%08lx\n", S_DAT_M_GET.AC));
			}else if( 0 == strcmp( argv[2], "s_wifiahb_m_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_S_WifiAHB_m_ib(&S_DAT_S_GET);
				Ddim_Print(("S_WifiAHB_m_ib(FMA) = 0x%08lx\n", S_DAT_S_GET.FMA));
				Ddim_Print(("S_WifiAHB_m_ib(FM)  = 0x%08lx\n", S_DAT_S_GET.FM));
			}else if( 0 == strcmp( argv[2], "s_uhs2ahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_S_Uhs2AHB_m(&S_DAT_S_GET);
				Ddim_Print(("S_Uhs2AHB_m(FMA) = 0x%08lx\n", S_DAT_S_GET.FMA));
				Ddim_Print(("S_Uhs2AHB_m(FM)  = 0x%08lx\n", S_DAT_S_GET.FM));
			}else if( 0 == strcmp( argv[2], "s_relcrahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_S_RelcrAHB_m(&S_DAT_S_GET);
				Ddim_Print(("S_RelcrAHB_m(FMA) = 0x%08lx\n", S_DAT_S_GET.FMA));
				Ddim_Print(("S_RelcrAHB_m(FM)  = 0x%08lx\n", S_DAT_S_GET.FM));
			}else if( 0 == strcmp( argv[2], "s_uhs1ahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_S_Uhs1AHB_m(&S_DAT_S_GET);
				Ddim_Print(("S_Uhs1AHB_m(FMA) = 0x%08lx\n", S_DAT_S_GET.FMA));
				Ddim_Print(("S_Uhs1AHB_m(FM)  = 0x%08lx\n", S_DAT_S_GET.FM));
			}else if( 0 == strcmp( argv[2], "s_relcwahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_S_RelcwAHB_m(&S_DAT_S_GET);
				Ddim_Print(("S_RelcwAHB_m(FMA) = 0x%08lx\n", S_DAT_S_GET.FMA));
				Ddim_Print(("S_RelcwAHB_m(FM)  = 0x%08lx\n", S_DAT_S_GET.FM));
			}else if( 0 == strcmp( argv[2], "s_bmnicahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_S_BmNicAHB_m(&S_DAT_S_GET);
				Ddim_Print(("S_BmNicAHB_m(FMA) = 0x%08lx\n", S_DAT_S_GET.FMA));
				Ddim_Print(("S_BmNicAHB_m(FM)  = 0x%08lx\n", S_DAT_S_GET.FM));
			}else if( 0 == strcmp( argv[2], "s_usb2ahb_ehci" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_S_Usb2AHB_ehci(&S_DAT_S_GET);
				Ddim_Print(("S_Usb2AHB_ehci(FMA) = 0x%08lx\n", S_DAT_S_GET.FMA));
				Ddim_Print(("S_Usb2AHB_ehci(FM)  = 0x%08lx\n", S_DAT_S_GET.FM));
			}else if( 0 == strcmp( argv[2], "s_usb2ahb_ohci" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_S_Usb2AHB_ohci(&S_DAT_S_GET);
				Ddim_Print(("S_Usb2AHB_ohci(FMA) = 0x%08lx\n", S_DAT_S_GET.FMA));
				Ddim_Print(("S_Usb2AHB_ohci(FM)  = 0x%08lx\n", S_DAT_S_GET.FM));
			}else if( 0 == strcmp( argv[2], "ib8" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_IB8(&S_DAT_IB_GET);
				Ddim_Print(("IB8(FMIB) = 0x%08lx\n", S_DAT_IB_GET.FMIB));
				Ddim_Print(("IB8(FM2)  = 0x%08lx\n", S_DAT_IB_GET.FM2));
				Ddim_Print(("IB8(WT)   = 0x%08lx\n", S_DAT_IB_GET.WT));
				Ddim_Print(("IB8(FM)   = 0x%08lx\n", S_DAT_IB_GET.FM));
			}else if( 0 == strcmp( argv[2], "ib13" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_IB13(&S_DAT_IB_GET);
				Ddim_Print(("IB13(FMIB) = 0x%08lx\n", S_DAT_IB_GET.FMIB));
				Ddim_Print(("IB13(FM2)  = 0x%08lx\n", S_DAT_IB_GET.FM2));
				Ddim_Print(("IB13(FML)  = 0x%08lx\n", S_DAT_IB_GET.FML));
				Ddim_Print(("IB13(FM)   = 0x%08lx\n", S_DAT_IB_GET.FM));
			}else if( 0 == strcmp( argv[2], "ib12" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_IB12(&S_DAT_IB_GET);
				Ddim_Print(("IB12(FMIB) = 0x%08lx\n", S_DAT_IB_GET.FMIB));
				Ddim_Print(("IB12(FM2)  = 0x%08lx\n", S_DAT_IB_GET.FM2));
				Ddim_Print(("IB12(FM)   = 0x%08lx\n", S_DAT_IB_GET.FM));
			}else if( 0 == strcmp( argv[2], "ib9" ) ) {
				priv->cdGpv->ret = Dd_GPV_Get_IB9(&S_DAT_IB_GET);
				Ddim_Print(("IB9(FMIB) = 0x%08lx\n", S_DAT_IB_GET.FMIB));
				Ddim_Print(("IB9(FM2)  = 0x%08lx\n", S_DAT_IB_GET.FM2));
				Ddim_Print(("IB9(WT)   = 0x%08lx\n", S_DAT_IB_GET.WT));
				Ddim_Print(("IB9(FM)   = 0x%08lx\n", S_DAT_IB_GET.FM));
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 2nd parameter!!\n"));
			}
		}else if( 0 == strcmp( argv[3], "set" ) ) {
			priv->cdGpv->input = atoi(argv[4]);

			switch (priv->cdGpv->input) {
				case 0:
					S_DAT_M_SET.FMIB	= 0;
					S_DAT_M_SET.FM2	= 0;
					S_DAT_M_SET.FML	= 0;
					S_DAT_M_SET.WT	= 0;
					S_DAT_M_SET.AC	= 0;
					S_DAT_M_SET.FM	= 0;

					S_DAT_S_SET.FMA	= 0;
					S_DAT_S_SET.FM	= 0;

					S_DAT_IB_SET.FMIB	= 0;
					S_DAT_IB_SET.FM2	= 0;
					S_DAT_IB_SET.FML	= 0;
					S_DAT_IB_SET.WT	= 0;
					S_DAT_IB_SET.FM	= 0;
					break;
				case 1:
					S_DAT_M_SET.FMIB	= 3;
					S_DAT_M_SET.FM2	= 1;
					S_DAT_M_SET.FML	= 3;
					S_DAT_M_SET.WT	= 8;
					S_DAT_M_SET.AC	= 3;
					S_DAT_M_SET.FM	= 3;

					S_DAT_S_SET.FMA	= 3;
					S_DAT_S_SET.FM	= 3;

					S_DAT_IB_SET.FMIB	= 3;
					S_DAT_IB_SET.FM2	= 1;
					S_DAT_IB_SET.FML	= 3;
					S_DAT_IB_SET.WT	= 8;
					S_DAT_IB_SET.FM	= 3;
					break;
				default:
					break;
			}

			if( 0 == strcmp( argv[2], "m_usb3_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Usb3_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_emmc_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Emmc_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_uhs2_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Uhs2_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_mxic1_m_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Mxic1_m_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_mxic2_m_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Mxic2_m_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_xdmac_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Xdmac_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_nf_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Nf_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_pcie0_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Pcie0_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_pcie1_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_Pcie1_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_nicperiahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_NicPeriAHB_m_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_nicbmahb1_r" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_NicBmAHB1_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "nsecx2p_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_NsecX2P_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "toprx2p_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_ToprX2P_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "m_nicbmahb2_r_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_M_NicBmAHB2_r_ib(&S_DAT_M_SET);
			}else if( 0 == strcmp( argv[2], "s_wifiahb_m_ib" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_S_WifiAHB_m_ib(&S_DAT_S_SET);
			}else if( 0 == strcmp( argv[2], "s_uhs2ahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_S_Uhs2AHB_m(&S_DAT_S_SET);
			}else if( 0 == strcmp( argv[2], "s_relcrahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_S_RelcrAHB_m(&S_DAT_S_SET);
			}else if( 0 == strcmp( argv[2], "s_uhs1ahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_S_Uhs1AHB_m(&S_DAT_S_SET);
			}else if( 0 == strcmp( argv[2], "s_relcwahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_S_RelcwAHB_m(&S_DAT_S_SET);
			}else if( 0 == strcmp( argv[2], "s_bmnicahb_m" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_S_BmNicAHB_m(&S_DAT_S_SET);
			}else if( 0 == strcmp( argv[2], "s_usb2ahb_ehci" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_S_Usb2AHB_ehci(&S_DAT_S_SET);
			}else if( 0 == strcmp( argv[2], "s_usb2ahb_ohci" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_S_Usb2AHB_ohci(&S_DAT_S_SET);
			}else if( 0 == strcmp( argv[2], "ib8" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_IB8(&S_DAT_IB_SET);
			}else if( 0 == strcmp( argv[2], "ib13" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_IB13(&S_DAT_IB_SET);
			}else if( 0 == strcmp( argv[2], "ib12" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_IB12(&S_DAT_IB_SET);
			}else if( 0 == strcmp( argv[2], "ib9" ) ) {
				priv->cdGpv->ret = Dd_GPV_Set_IB9(&S_DAT_IB_SET);
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 2nd parameter!!\n"));
			}
		}
	}else
	{
		// Input parameter NG
		Ddim_Print(("please check 1st parameter!\n"));
	}
}

CtDdGpvMain* ct_dd_gpv_main_new(void) 
{
    CtDdGpvMain *self = k_object_new_with_private(CT_TYPE_DD_GPV_MAIN, sizeof(CtDdGpvMainPrivate));
    return self;
}
