/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :杨升柄
*@brief               :CtDdGpv类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtDdGpv, ct_dd_gpv);
#define CT_DD_GPV_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdGpvPrivate,CT_TYPE_DD_GPV))

struct _CtDdGpvPrivate
{
};

static void ct_dd_gpv_constructor(CtDdGpv *self) 
{
	self->input = 0;
	self->ret = 0;
}

static void ct_dd_gpv_destructor(CtDdGpv *self) 
{
}

/*
 * PUBLIC
 */
void ct_dd_gpv_from_main(CtDdGpv* self, kint argc, kchar** argv)
{
	if( 0 == strcmp( argv[1], "set" ) ) {
		self->input = atoi(argv[4]);
		//-------------------------------------------------------//
		if( 0 == strcmp( argv[2], "m_usb3_r_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Usb3_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Usb3_r_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_Usb3_r_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Usb3_r_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Usb3_r_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Usb3_r_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_emmc_r_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Emmc_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Emmc_r_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_Emmc_r_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Emmc_r_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fml" ) ) {
				self->ret = Dd_GPV_Set_M_Emmc_r_ib_FML(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Emmc_r_ib FML OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Emmc_r_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Emmc_r_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_uhs2_r_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Uhs2_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Uhs2_r_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_Uhs2_r_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Uhs2_r_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fml" ) ) {
				self->ret = Dd_GPV_Set_M_Uhs2_r_ib_FML(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Uhs2_r_ib FML OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Uhs2_r_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set M_Uhs2_r_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_mxic1_m_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Mxic1_m_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_mxic1_m_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "wt" ) ) {
				self->ret = Dd_GPV_Set_M_Mxic1_m_ib_WT(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_mxic1_m_ib WT OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Mxic1_m_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_mxic1_m_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_mxic2_m_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Mxic2_m_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_mxic2_m_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "wt" ) ) {
				self->ret = Dd_GPV_Set_M_Mxic2_m_ib_WT(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_mxic2_m_ib WT OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Mxic2_m_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_mxic2_m_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_xdmac_r_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Xdmac_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_xdmac_r_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_Xdmac_r_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_xdmac_r_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Xdmac_r_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_xdmac_r_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_nf_r_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Nf_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nf_r_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_Nf_r_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nf_r_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fml" ) ) {
				self->ret = Dd_GPV_Set_M_Nf_r_ib_FML(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nf_r_ib FML OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Nf_r_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nf_r_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_pcie0_r_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Pcie0_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_pcie0_r_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_Pcie0_r_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_pcie0_r_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fml" ) ) {
				self->ret = Dd_GPV_Set_M_Pcie0_r_ib_FML(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_pcie0_r_ib FML OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Pcie0_r_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_pcie0_r_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_pcie1_r_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_Pcie1_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_pcie1_r_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_Pcie1_r_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_pcie1_r_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fml" ) ) {
				self->ret = Dd_GPV_Set_M_Pcie1_r_ib_FML(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_pcie1_r_ib FML OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_M_Pcie1_r_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_pcie1_r_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_nicperiahb_m" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_NicPeriAHB_m_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nicperiahb_m FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_NicPeriAHB_m_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nicperiahb_m FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "ac" ) ) {
				self->ret = Dd_GPV_Set_M_NicPeriAHB_m_AC(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nicperiahb_m AC OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_nicbmahb1_r" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_NicBmAHB1_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nicbmahb1_r FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "ac" ) ) {
				self->ret = Dd_GPV_Set_M_NicBmAHB1_r_AC(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nicbmahb1_r AC OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "nsecx2p_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_NsecX2P_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set nsecx2p_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_NsecX2P_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set nsecx2p_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "toprx2p_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_ToprX2P_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set toprx2p_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_ToprX2P_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set toprx2p_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "m_nicbmahb2_r_ib" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_M_NicBmAHB2_r_ib_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nicbmahb2_r_ib FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_M_NicBmAHB2_r_ib_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nicbmahb2_r_ib FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "ac" ) ) {
				self->ret = Dd_GPV_Set_M_NicBmAHB2_r_AC(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set m_nicbmahb2_r_ib AC OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_main_rm_ib" ) ) {
			if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_Main_rm_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_main_rm_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_xdmac_m_ib" ) ) {
			if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_Xdmac_m_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_xdmac_m_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}
		}else if( 0 == strcmp( argv[2], "s_netsec_m" ) ) {
			if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_Netsec_m_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_netsec_m FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_wifiahb_m_ib" ) ) {
			if( 0 == strcmp( argv[3], "fma" ) ) {
				self->ret = Dd_GPV_Set_S_WifiAHB_m_FMA(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_wifiahb_m_ib FMA OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_WifiAHB_m_ib_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_wifiahb_m_ib FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_uhs2ahb_m" ) ) {
			if( 0 == strcmp( argv[3], "fma" ) ) {
				self->ret = Dd_GPV_Set_S_Uhs2AHB_m_FMA(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_uhs2ahb_m FMA OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_Uhs2AHB_m_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_uhs2ahb_m FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_relcrahb_m" ) ) {
			if( 0 == strcmp( argv[3], "fma" ) ) {
				self->ret = Dd_GPV_Set_S_RelcrAHB_m_FMA(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_relcrahb_m FMA OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_RelcrAHB_m_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_relcrahb_m FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_uhs1ahb_m" ) ) {
			if( 0 == strcmp( argv[3], "fma" ) ) {
				self->ret = Dd_GPV_Set_S_Uhs1AHB_m_FMA(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_uhs1ahb_m FMA OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_Uhs1AHB_m_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_uhs1ahb_m FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_relcwahb_m" ) ) {
			if( 0 == strcmp( argv[3], "fma" ) ) {
				self->ret = Dd_GPV_Set_S_RelcwAHB_m_FMA(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_relcwahb_m FMA OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_RelcwAHB_m_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_relcwahb_m FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_bmnicahb_m" ) ) {
			if( 0 == strcmp( argv[3], "fma" ) ) {
				self->ret = Dd_GPV_Set_S_BmNicAHB_m_FMA(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_bmnicahb_m FMA OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_BmNicAHB_m_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_bmnicahb_m FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_usb2ahb_ehci" ) ) {
			if( 0 == strcmp( argv[3], "fma" ) ) {
				self->ret = Dd_GPV_Set_S_Usb2AHB_ehci_FMA(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_usb2ahb_ehci FMA OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_Usb2AHB_ehci_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_usb2ahb_ehci FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_usb2ahb_ohci" ) ) {
			if( 0 == strcmp( argv[3], "fma" ) ) {
				self->ret = Dd_GPV_Set_S_Usb2AHB_ohci_FMA(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_usb2ahb_ohci FMA OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_Usb2AHB_ohci_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_usb2ahb_ohci FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "s_netsec2_m" ) ) {
			if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_S_Netsec2_m_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set s_netsec2_m FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "ib8" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_IB8_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib8 FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_IB8_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib8 FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "wt" ) ) {
				self->ret = Dd_GPV_Set_IB8_WT(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib8 WT OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_IB8_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib8 FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "ib13" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_IB13_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib13 FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_IB13_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib13 FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fml" ) ) {
				self->ret = Dd_GPV_Set_IB13_FML(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib13 FML OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_IB13_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib13 FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "ib12" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_IB12_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib12 FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_IB12_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib12 FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_IB12_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib12 FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "ib9" ) ) {
			if( 0 == strcmp( argv[3], "fmib" ) ) {
				self->ret = Dd_GPV_Set_IB9_FMIB(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib9 FMBI OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm2" ) ) {
				self->ret = Dd_GPV_Set_IB9_FM2(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib9 FM2 OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "wt" ) ) {
				self->ret = Dd_GPV_Set_IB9_WT(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib9 WT OK(self->input = 0x%08x).\n", self->input));
				}
			}else if( 0 == strcmp( argv[3], "fm" ) ) {
				self->ret = Dd_GPV_Set_IB9_FM(self->input);
				if ( self->ret == 0 ){
					Ddim_Print(("It set ib9 FM OK(self->input = 0x%08x).\n", self->input));
				}
			}else
			{
				// Input parameter NG
				Ddim_Print(("please check 3rd parameter!!\n"));
				return;
			}
		}else if( 0 == strcmp( argv[2], "remap" ) ) {
			// get remap
			self->ret = Dd_GPV_Get_ARC_Remap();
			Ddim_Print(("It get REMAP.0x%08x\n", self->ret));
			// set remapp. (val = 0xDF / set = 0).
			Dd_GPV_Set_ARC_Remap(0xDF, 0);
			Ddim_Print(("It clr REMAP.0xDF\n"));
			// get remap
			self->ret = Dd_GPV_Get_ARC_Remap();
			Ddim_Print(("It get REMAP.0x%08x\n", self->ret));
			// set remapp. (val = 0x7F / set = 1).
			Dd_GPV_Set_ARC_Remap(0x7F, 1);
			Ddim_Print(("It set REMAP.0x7F\n"));
			// get remap
			self->ret = Dd_GPV_Get_ARC_Remap();
			Ddim_Print(("It get REMAP.0x%08x\n", self->ret));
		}else
		{
			// Input parameter NG
			Ddim_Print(("please check 2nd parameter!!\n"));
			return;
		}

		if ( self->ret != 0 ) {
				// set NG
				Ddim_Print(("It set NG(return = %d).\n", self->ret));
		}
	}
}

CtDdGpv* ct_dd_gpv_new(void) 
{
    CtDdGpv *self = k_object_new_with_private(CT_TYPE_DD_GPV, sizeof(CtDdGpvPrivate));
    return self;
}
