/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/


#ifndef __SNS_JMLEXS_H__
#define __SNS_JMLEXS_H__


#include <klib.h>


#define SNS_TYPE_JMLEXS                  (sns_jmlexs_get_type())
#define SNS_JMLEXS(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, SnsJmlexs))
#define SNS_IS_JMLEXS(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, SNS_TYPE_JMLEXS))


typedef union _IoAddressRegionCtrlRemap 		IoAddressRegionCtrlRemap;
typedef struct _IoGpvMUsb3RIb 						IoGpvMUsb3RIb;
typedef struct _IoGpvMEmmcRIb 						IoGpvMEmmcRIb;
typedef struct _IoGpvMUhs2RIb 						IoGpvMUhs2RIb;
typedef struct _IoGpvMMxic1MIb 						IoGpvMMxic1MIb;
typedef struct _IoGpvMMxic2MIb 						IoGpvMMxic2MIb;
typedef struct _IoGpvMXdmacRIb 						IoGpvMXdmacRIb;
typedef struct _IoGpvMNfRIb 							IoGpvMNfRIb;
typedef struct _IoGpvMPcie0RIb 						IoGpvMPcie0RIb;
typedef struct _IoGpvMPcie1RIb 						IoGpvMPcie1RIb;
typedef struct _IoGpvMNicPeriAHBMIb  			IoGpvMNicPeriAHBMIb;
typedef struct _IoGpvMNicBmAHB1RIb  			IoGpvMNicBmAHB1RIb;
typedef struct _IoGpvNsecX2PIb  						IoGpvNsecX2PIb;
typedef struct _IoGpvToprX2PIb  						IoGpvToprX2PIb;
typedef struct _IoGpvMNicBmAHB2RIb  			IoGpvMNicBmAHB2RIb;
typedef struct _IoGpvSMainRmIb  						IoGpvSMainRmIb;
typedef struct _IoGpvSXdmacMIb  					IoGpvSXdmacMIb;
typedef struct _IoGpvSNetsecM  						IoGpvSNetsecM;
typedef struct _IoGpvSWifiAHBMIb  					IoGpvSWifiAHBMIb;
typedef struct _IoGpvSUhs2AHBM  					IoGpvSUhs2AHBM;
typedef struct _IoGpvSRelcrAHBM  					IoGpvSRelcrAHBM;
typedef struct _IoGpvSUhs1AHBM  					IoGpvSUhs1AHBM;
typedef struct _IoGpvSRelcwAHBM  					IoGpvSRelcwAHBM;
typedef struct _IoGpvSBmNicAHBM  				IoGpvSBmNicAHBM;
typedef struct _IoGpvSUsb2AHBEhci  				IoGpvSUsb2AHBEhci;
typedef struct _IoGpvSUsb2AHBOhci  				IoGpvSUsb2AHBOhci;
typedef struct _IoGpvSNetsec2M  						IoGpvSNetsec2M;
typedef struct _IoGpvIb8  									IoGpvIb8;
typedef struct _IoGpvIb13  									IoGpvIb13;
typedef struct _IoGpvIb12  									IoGpvIb12;
typedef struct _IoGpvIb9  									IoGpvIb9;
typedef struct _IoGpv  										IoGpv;
typedef union _IoExstopXdmaclowpowctrl		IoExstopXdmaclowpowctrl;
typedef union _IoExstopSoftreset						IoExstopSoftreset;
typedef union _IoExstopSoftreset2						IoExstopSoftreset2;
typedef union _IoExstopIntmsk							IoExstopIntmsk;
typedef union _IoExstopSigmon							IoExstopSigmon;
typedef union _IoExstopDeben							IoExstopDeben;
typedef union _IoExstopCdimodctrl					IoExstopCdimodctrl;
typedef union _IoExstopRelchptctrl					IoExstopRelchptctrl;
typedef union _IoExstopRampdctrl					IoExstopRampdctrl;
typedef union _IoExstopBusckstpctrl					IoExstopBusckstpctrl;
typedef union _IoExstopNetsecptpclkstopctrl	IoExstopNetsecptpclkstopctrl;
typedef union _IoExstopEmmcckstp					IoExstopEmmcckstp;
typedef union  _IoExstopEmdrvstr						IoExstopEmdrvstr;
typedef union _IoExstopEmpvdtimec					IoExstopEmpvdtimec;
typedef union _IoExstopEmpvampbl					IoExstopEmpvampbl;
typedef union _IoExstopEmcrslottype				IoExstopEmcrslottype;
typedef union _IoExstopEmcrbclkfreq				IoExstopEmcrbclkfreq;
typedef union _IoExstopEmcddet						IoExstopEmcddet;
typedef union _IoExstopUsb2ckctl						IoExstopUsb2ckctl;
typedef union _IoExstopUsb2rctl						IoExstopUsb2rctl;
typedef union _IoExstopUsb2anpd						IoExstopUsb2anpd;
typedef union _IoExstopUsb2hfsel						IoExstopUsb2hfsel;
typedef union _IoExstopUsb2fsel						IoExstopUsb2fsel;
typedef union _IoExstopUsb2ehcisb					IoExstopUsb2ehcisb;
typedef union _IoExstopUsb2ehcistrap				IoExstopUsb2ehcistrap;
typedef union _IoExstopUsb2ohciif					IoExstopUsb2ohciif;
typedef union _IoExstopUsb2ahbslvif				IoExstopUsb2ahbslvif;
typedef union _IoExstopUsb2lmodset				IoExstopUsb2lmodset;
typedef union _IoExstopUsb2pmodset				IoExstopUsb2pmodset;
typedef union _IoExstopUsb2hptctl					IoExstopUsb2hptctl;
typedef union _IoExstopUsb2idvbusctl				IoExstopUsb2idvbusctl;
typedef union _IoExstopUsb2hdmac1				IoExstopUsb2hdmac1;
typedef union _IoExstopUsb2hdmac2				IoExstopUsb2hdmac2;
typedef union _IoExstopUsb2dmafsm1				IoExstopUsb2dmafsm1;
typedef union _IoExstopUsb2dmafsm2				IoExstopUsb2dmafsm2;
typedef union _IoExstopUsb3ckctl						IoExstopUsb3ckctl;
typedef union _IoExstopUsb3rctl						IoExstopUsb3rctl;
typedef union _IoExstopUsb3rcvsns					IoExstopUsb3rcvsns;
typedef union _IoExstopUsb3fsel						IoExstopUsb3fsel;
typedef union _IoExstopUsb3rfcctl						IoExstopUsb3rfcctl;
typedef union _IoExstopUsb3hoif						IoExstopUsb3hoif;
typedef union _IoExstopUsb3jtadj						IoExstopUsb3jtadj;
typedef union _IoExstopUsb3idvbusctl				IoExstopUsb3idvbusctl;
typedef union _IoExstopNfipctl							IoExstopNfipctl;
typedef union _IoExstopNfbtsqstate					IoExstopNfbtsqstate;
typedef union _IoExstopNfbvalidtm					IoExstopNfbvalidtm;
typedef union _IoExstopNfphyctrlreg					IoExstopNfphyctrlreg;
typedef union _IoExstopNfphydqtim					IoExstopNfphydqtim;
typedef union _IoExstopNfphydqstim				IoExstopNfphydqstim;
typedef union _IoExstopNfphygtlpbk					IoExstopNfphygtlpbk;
typedef union _IoExstopNfphydllmctl				IoExstopNfphydllmctl;
typedef union _IoExstopNfphydllsctl					IoExstopNfphydllsctl;
typedef union _IoExstopNfbooteccctl				IoExstopNfbooteccctl;
typedef union _IoExstopNfwpxcnt						IoExstopNfwpxcnt;
typedef union _IoExstopIntstat							IoExstopIntstat;
typedef struct _IoExstop										IoExstop;
typedef struct _SnsJmlexs 									SnsJmlexs;
typedef struct _SnsJmlexsPrivate 						SnsJmlexsPrivate;


/* Structure of Address region control remap		(1900_0000h) */
union _IoAddressRegionCtrlRemap{
	kulong		word;
	struct {
		kulong	rm			:8;
		kulong					:24;
	}bit;
};

/* Structure of M_Usb3_r_ib */
struct _IoGpvMUsb3RIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Usb3_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_Usb3_r_ib fn_mod2 Register
	kuchar						dmy0028002b[0x002C - 0x0028];			// Base_(0028h - 002Bh) Reserved
	kulong						fml;									// Base_(002Ch - 002Fh) M_Usb3_r_ib fn_mod_lb Register
	kuchar						dmy00300107[0x0108 - 0x0030];			// Base_(0030h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Usb3_r_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_Emmc_r_ib */
struct _IoGpvMEmmcRIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Emmc_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_Emmc_r_ib fn_mod2 Register
	kuchar						dmy0028002b[0x002C - 0x0028];			// Base_(0028h - 002Bh) Reserved
	kulong						fml;									// Base_(002Ch - 002Fh) M_Emmc_r_ib fn_mod_lb Register
	kuchar						dmy00300107[0x0108 - 0x0030];			// Base_(0030h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Emmc_r_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_Uhs2_r_ib */
struct _IoGpvMUhs2RIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Uhs2_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_Uhs2_r_ib fn_mod2 Register
	kuchar						dmy0028002b[0x002C - 0x0028];			// Base_(0028h - 002Bh) Reserved
	kulong						fml;									// Base_(002Ch - 002Fh) M_Uhs2_r_ib fn_mod_lb Register
	kuchar						dmy00300107[0x0108 - 0x0030];			// Base_(0030h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Uhs2_r_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_Mxic1_m_ib */
struct _IoGpvMMxic1MIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Mxic1_m_ib fn_mod_iss_bm Register
	kuchar						dmy000c003f[0x0040 - 0x000C];			// Base_(000Ch - 003Fh) Reserved
	kulong						wt;										// Base_(0040h - 0043h) M_Mxic1_m_ib wr_tidemark Register
	kuchar						dmy00440107[0x0108 - 0x0044];			// Base_(0044h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Mxic1_m_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_Mxic2_m_ib */
struct _IoGpvMMxic2MIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Mxic2_m_ib fn_mod_iss_bm Register
	kuchar						dmy000c003f[0x0040 - 0x000C];			// Base_(000Ch - 003Fh) Reserved
	kulong						wt;										// Base_(0040h - 0043h) M_Mxic2_m_ib wr_tidemark Register
	kuchar						dmy00440107[0x0108 - 0x0044];			// Base_(0044h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Mxic2_m_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_Xdmac_r_ib */
struct _IoGpvMXdmacRIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Xdmac_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_Xdmac_r_ib fn_mod2 Register
	kuchar						dmy00280107[0x0108 - 0x0028];			// Base_(0028h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Xdmac_r_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_Nf_r_ib */
struct _IoGpvMNfRIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Nf_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_Nf_r_ib fn_mod2 Register
	kuchar						dmy0028002b[0x002C - 0x0028];			// Base_(0028h - 002Bh) Reserved
	kulong						fml;									// Base_(002Ch - 002Fh) M_Nf_r_ib fn_mod_lb Register
	kuchar						dmy00300107[0x0108 - 0x0030];			// Base_(0030h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Nf_r_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_Pcie0_r_ib */
struct _IoGpvMPcie0RIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Pcie0_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_Pcie0_r_ib fn_mod2 Register
	kuchar						dmy0028002b[0x002C - 0x0028];			// Base_(0028h - 002Bh) Reserved
	kulong						fml;									// Base_(002Ch - 002Fh) M_Pcie0_r_ib fn_mod_lb Register
	kuchar						dmy00300107[0x0108 - 0x0030];			// Base_(0030h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Pcie0_r_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_Pcie1_r_ib */
struct _IoGpvMPcie1RIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_Pcie1_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_Pcie1_r_ib fn_mod2 Register
	kuchar						dmy0028002b[0x002C - 0x0028];			// Base_(0028h - 002Bh) Reserved
	kulong						fml;									// Base_(002Ch - 002Fh) M_Pcie1_r_ib fn_mod_lb Register
	kuchar						dmy00300107[0x0108 - 0x0030];			// Base_(0030h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) M_Pcie1_r_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of M_NicPeriAHB_m_ib */
struct _IoGpvMNicPeriAHBMIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_NicPeriAHB_m_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_NicPeriAHB_m_ib fn_mod2 Register
	kuchar						dmy00280043[0x0044 - 0x0028];			// Base_(0028h - 0043h) Reserved
	kulong						ac;										// Base_(0044h - 0047h) M_NicPeriAHB_m_ib ahb_cntl Register
	kuchar						dmy00480fff[0x1000 - 0x0048];			// Base_(0048h - 0FFFh) Reserved
};

/* Structure of M_NicBmAHB1_r_ib */
struct _IoGpvMNicBmAHB1RIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_NicBmAHB1_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0043[0x0044 - 0x000C];			// Base_(000Ch - 0043h) Reserved
	kulong						ac;										// Base_(0044h - 0047h) M_NicBmAHB1_r_ib ahb_cntl Register
	kuchar						dmy00480fff[0x1000 - 0x0048];			// Base_(0048h - 0FFFh) Reserved
};

/* Structure of NsecX2P_ib */
struct _IoGpvNsecX2PIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) NsecX2P_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) NsecX2P_ib fn_mod2 Register
	kuchar						dmy00280fff[0x1000 - 0x0028];			// Base_(0028h - 0FFFh) Reserved
};

/* Structure of ToprX2P_ib */
struct _IoGpvToprX2PIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) ToprX2P_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) ToprX2P_ib fn_mod2 Register
	kuchar						dmy00280fff[0x1000 - 0x0028];			// Base_(0028h - 0FFFh) Reserved
};

/* Structure of M_NicBmAHB2_r_ib */
struct _IoGpvMNicBmAHB2RIb {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) M_NicBmAHB2_r_ib fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) M_NicBmAHB2_r_ib fn_mod2 Register
	kuchar						dmy00280043[0x0044 - 0x0028];			// Base_(0028h - 0043h) Reserved
	kulong						ac;										// Base_(0044h - 0047h) M_NicBmAHB2_r_ib ahb_cntl Register
	kuchar						dmy00480fff[0x1000 - 0x0048];			// Base_(0048h - 0FFFh) Reserved
};

/* Structure of S_Main_rm_ib */
struct _IoGpvSMainRmIb {
	kuchar						dmy00000007[0x0108 - 0x0000];			// Base_(0000h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_Main_rm_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_Xdmac_m_ib */
struct _IoGpvSXdmacMIb {
	kuchar						dmy00000007[0x0108 - 0x0000];			// Base_(0000h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_Xdmac_m_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_Netsec_m */
struct _IoGpvSNetsecM {
	kuchar						dmy00000007[0x0108 - 0x0000];			// Base_(0000h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_Netsec_m fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_WifiAHB_m_ib */
struct _IoGpvSWifiAHBMIb {
	kuchar						dmy00000007[0x0028 - 0x0000];			// Base_(0000h - 0027h) Reserved
	kulong						fma;									// Base_(0028h - 002Bh) S_WifiAHB_m_ib fn_mod_ahb Register
	kuchar						dmy00300107[0x0108 - 0x002C];			// Base_(002Ch - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_WifiAHB_m_ib fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_Uhs2AHB_m */
struct _IoGpvSUhs2AHBM {
	kuchar						dmy00000007[0x0028 - 0x0000];			// Base_(0000h - 0027h) Reserved
	kulong						fma;									// Base_(0028h - 002Bh) S_Uhs2AHB_m fn_mod_ahb Register
	kuchar						dmy00300107[0x0108 - 0x002C];			// Base_(002Ch - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_Uhs2AHB_m fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_RelcrAHB_m */
struct _IoGpvSRelcrAHBM {
	kuchar						dmy00000007[0x0028 - 0x0000];			// Base_(0000h - 0027h) Reserved
	kulong						fma;									// Base_(0028h - 002Bh) S_RelcrAHB_m fn_mod_ahb Register
	kuchar						dmy00300107[0x0108 - 0x002C];			// Base_(002Ch - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_RelcrAHB_m fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_Uhs1AHB_m */
struct _IoGpvSUhs1AHBM {
	kuchar						dmy00000007[0x0028 - 0x0000];			// Base_(0000h - 0027h) Reserved
	kulong						fma;									// Base_(0028h - 002Bh) S_Uhs1AHB_m fn_mod_ahb Register
	kuchar						dmy00300107[0x0108 - 0x002C];			// Base_(002Ch - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_Uhs1AHB_m fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_RelcwAHB_m */
struct _IoGpvSRelcwAHBM {
	kuchar						dmy00000007[0x0028 - 0x0000];			// Base_(0000h - 0027h) Reserved
	kulong						fma;									// Base_(0028h - 002Bh) S_RelcwAHB_m fn_mod_ahb Register
	kuchar						dmy00300107[0x0108 - 0x002C];			// Base_(002Ch - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_RelcwAHB_m fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_BmNicAHB_m */
struct _IoGpvSBmNicAHBM {
	kuchar						dmy00000007[0x0028 - 0x0000];			// Base_(0000h - 0027h) Reserved
	kulong						fma;									// Base_(0028h - 002Bh) S_BmNicAHB_m fn_mod_ahb Register
	kuchar						dmy00300107[0x0108 - 0x002C];			// Base_(002Ch - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_BmNicAHB_m fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_Usb2AHB_ehci */
struct _IoGpvSUsb2AHBEhci {
	kuchar						dmy00000007[0x0028 - 0x0000];			// Base_(0000h - 0027h) Reserved
	kulong						fma;									// Base_(0028h - 002Bh) S_Usb2AHB_ehci fn_mod_ahb Register
	kuchar						dmy00300107[0x0108 - 0x002C];			// Base_(002Ch - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_Usb2AHB_ehci fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_Usb2AHB_ohci */
struct _IoGpvSUsb2AHBOhci {
	kuchar						dmy00000007[0x0028 - 0x0000];			// Base_(0000h - 0027h) Reserved
	kulong						fma;									// Base_(0028h - 002Bh) S_Usb2AHB_ohci fn_mod_ahb Register
	kuchar						dmy00300107[0x0108 - 0x002C];			// Base_(002Ch - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_Usb2AHB_ohci fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of S_Netsec2_m */
struct _IoGpvSNetsec2M {
	kuchar						dmy00000107[0x0108 - 0x0000];			// Base_(0000h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) S_Netsec2_m fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of ib8 */
struct _IoGpvIb8 {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) ib8 fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) ib8 fn_mod2 Register
	kuchar						dmy0028003f[0x0040 - 0x0028];			// Base_(0028h - 003Fh) Reserved
	kulong						wt;										// Base_(0040h - 0043h) ib8 wr_tidemark Register
	kuchar						dmy00440107[0x0108 - 0x0044];			// Base_(0044h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) ib8 fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of ib13 */
struct _IoGpvIb13 {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) ib13 fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) ib13 fn_mod2 Register
	kuchar						dmy0028002b[0x002C - 0x0028];			// Base_(0028h - 002Bh) Reserved
	kulong						fml;									// Base_(002Ch - 002Fh) ib13 fn_mod_lb Register
	kuchar						dmy00300107[0x0108 - 0x0030];			// Base_(0030h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) ib13 fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of ib12 */
struct _IoGpvIb12 {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) ib12 fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) ib12 fn_mod2 Register
	kuchar						dmy00280107[0x0108 - 0x0028];			// Base_(0028h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) ib12 fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

/* Structure of ib9 */
struct _IoGpvIb9 {
	kuchar						dmy00000007[0x0008 - 0x0000];			// Base_(0000h - 0007h) Reserved
	kulong						fmib;									// Base_(0008h - 000Bh) ib9 fn_mod_iss_bm Register
	kuchar						dmy000c0023[0x0024 - 0x000C];			// Base_(000Ch - 0023h) Reserved
	kulong						fm2;									// Base_(0024h - 0027h) ib9 fn_mod2 Register
	kuchar						dmy0028003f[0x0040 - 0x0028];			// Base_(0028h - 003Fh) Reserved
	kulong						wt;										// Base_(0040h - 0043h) ib9 wr_tidemark Register
	kuchar						dmy00440107[0x0108 - 0x0044];			// Base_(0044h - 0107h) Reserved
	kulong						fm;										// Base_(0108h - 010Bh) ib9 fn_mod Register
	kuchar						dmy010c0fff[0x1000 - 0x010C];			// Base_(010Ch - 0FFFh) Reserved
};

struct _IoGpv {
	IoAddressRegionCtrlRemap	remap;		// 1900_(0000h - 0003h) Address region control registers
	kuchar										dmy00042fff[0x3000 - 0x0004];			// 1900_(0004h - 2FFFh) Reserved
	IoGpvMUsb3RIb						mUsb3RIb;								// 1900_(3000h - 3FFFh) M_Usb3_r_ib Registers
	IoGpvMEmmcRIb					mEmmcRIb;								// 1900_(4000h - 4FFFh) M_Emmc_r_ib Registers
	IoGpvMUhs2RIb						mUhs2RIb;								// 1900_(5000h - 5FFFh) M_Uhs2_r_ib Registers
	IoGpvMMxic1MIb					mMxic1MIb;								// 1900_(6000h - 6FFFh) M_Mxic1_m_ib Registers
	IoGpvMMxic2MIb					mMxic2MIb;								// 1900_(7000h - 7FFFh) M_Mxic2_m_ib Registers
	kuchar										dmy8000afff[0xB000 - 0x8000];			// 1900_(8000h - AFFFh) Reserved
	IoGpvMXdmacRIb					mXdmacRIb;								// 1900_(B000h - BFFFh) M_Xdmac_r_ib Registers
	IoGpvMNfRIb							mNfRIb;									// 1900_(C000h - CFFFh) M_Nf_r_ib Registers
	IoGpvMPcie0RIb						mPcie0RIb;								// 1900_(D000h - DFFFh) M_Pcie0_r_ib Registers
	IoGpvMPcie1RIb						mPcie1RIb;								// 1900_(E000h - EFFFh) M_Pcie1_r_ib Registers
	IoGpvMNicPeriAHBMIb			mNicPeriAhbMIb;							// 1900_(F000h - FFFFh) M_NicPeriAHB_m_ib Registers
	IoGpvMNicBmAHB1RIb			mNicBmAhb1RIb;							// 190_(10000h - 10FFFh) M_NicBmAHB1_r_ib Registers
	IoGpvNsecX2PIb						nsecX2pIb;								// 190_(11000h - 11FFFh) NsecX2P_ib Registers
	IoGpvToprX2PIb						toprX2pIb;								// 190_(12000h - 12FFFh) ToprX2P_ib Registers
	IoGpvMNicBmAHB2RIb			mNicBmAhb2RIb;							// 190_(13000h - 13FFFh) M_NicBmAHB2_r_ib Registers
	kuchar										dmy1400041fff[0x42000 - 0x14000];		// 190_(14000h - 41FFFh) Reserved
	IoGpvSMainRmIb					sMainRmIb;								// 190_(42000h - 42FFFh) S_Main_rm_ib Registers
	IoGpvSXdmacMIb					sXdmacMIb;								// 190_(43000h - 43FFFh) S_Xdmac_m_ib Registers
	kuchar										dmy4400044fff[0x45000 - 0x44000];		// 190_(44000h - 44FFFh) Reserved
	IoGpvSNetsecM						sNetsecM;								// 190_(45000h - 45FFFh) S_Netsec_m Registers
	kuchar										dmy460004afff[0x4B000 - 0x46000];		// 190_(46000h - 4AFFFh) Reserved
	IoGpvSWifiAHBMIb				sWifiAhbMIb;							// 190_(4B000h - 4BFFFh) S_WifiAHB_m_ib Registers
	IoGpvSUhs2AHBM					sUhs2AhbM;								// 190_(4C000h - 4CFFFh) S_Uhs2AHB_m Registers
	IoGpvSRelcrAHBM					sRelcrAhbM;								// 190_(4D000h - 4DFFFh) S_RelcrAHB_m Registers
	IoGpvSUhs1AHBM					sUhs1AhbM;								// 190_(4E000h - 4EFFFh) S_Uhs1AHB_m Registers
	IoGpvSRelcwAHBM				sRelcwAhbM;								// 190_(4F000h - 4FFFFh) S_RelcwAHB_m Registers
	IoGpvSBmNicAHBM				sBmNicAhbM;								// 190_(50000h - 50FFFh) S_BmNicAHB_m Registers
	IoGpvSUsb2AHBEhci				sUsb2AhbEhci;							// 190_(51000h - 51FFFh) S_Usb2AHB_ehci Registers
	IoGpvSUsb2AHBOhci				sUsb2AhbOhci;							// 190_(52000h - 52FFFh) S_Usb2AHB_ohci Registers
	IoGpvSNetsec2M					sNetsec2M;								// 190_(53000h - 53FFFh) S_Netsec2_m Registers
	kuchar										dmy54000C2fff[0xC3000 - 0x54000];		// 190_(54000h - C2FFFh) Reserved
	IoGpvIb8									ib8;										// 190_(C3000h - C3FFFh) IB8 Registers
	kuchar										dmyC4000C4fff[0xC5000 - 0xC4000];		// 190_(C4000h - C4FFFh) Reserved
	IoGpvIb13								ib13;									// 190_(C5000h - C5FFFh) IB13 Registers
	kuchar										dmyC6000C7fff[0xC8000 - 0xC6000];		// 190_(C6000h - C7FFFh) Reserved
	IoGpvIb12								ib12;									// 190_(C8000h - C8FFFh) IB12 Registers
	IoGpvIb9									ib9;									// 190_(C9000h - C9FFFh) IB9 Registers
	kuchar										dmyCa000Fffff[0x100000 - 0xCA000];	// 190_(CA000h - FFFFFh) Reserved
};

/*	Structure of XDMAC LowPower Control	(1B11_0000h)	*/
union _IoExstopXdmaclowpowctrl{
	kulong		word;
	struct {
		kulong	csysReq				:1;		// CSYS Request
		kulong								:7;		// reserved
		kulong	csysAck				:1;		// CSYS Acknowlege
		kulong								:7;		// reserved
		kulong	cActive					:1;		// C Active
		kulong								:15;	// reserved
    } bit;
};

/*	Structure of SoftReset	(1B11_000Ch)	*/
union _IoExstopSoftreset {
	kulong		word;
	struct {
		kulong	nfRstn					:1;		// NF Reset
		kulong	nfRstnBch			:1;		// NF Reset Bch
		kulong	nfRstnReg			:1;		// NF Reset Reg
		kulong								:5;		// reserved
		kulong	netsecRst				:1;		// NETSEC Reset
		kulong								:7;		// reserved
		kulong	emcRst				:1;		// eMMC Reset x
		kulong								:7;		// reserved
		kulong	relcRst					:1;		// RELC Reset
		kulong								:7;		// reserved
    } bit;
};

/*	Structure of SoftReset 2	(1B11_0010h)	*/
union _IoExstopSoftreset2 {
	kulong		word;
	struct {
		kulong	debrstxReserve		:1;		// reserved
		kulong	debrstxSd3				:1;		// SD3( UHS2 )
		kulong	debrstxSd4				:1;		// SD4( UHS1 Card )
		kulong	debrstxPcie0			:1;		// PCIe0
		kulong	debrstxPcie1			:1;		// PCIe1
		kulong	debrstxUsb2Vbus	:1;		// USB2 VBUS
		kulong	debrstxUsb2Id		:1;		// USB2 ID
		kulong	debrstxUsb3Vbus	:1;		// USB3 VBUS
		kulong	debrstxUsb3Id		:1;		// USB3 ID
		kulong									:23;		// reserved
    } bit;
};

/*	Structure of INTMSK register	(1B11_0014h)	*/
union _IoExstopIntmsk {
	kulong		word;
	struct {
		kulong	intMsk00			:1;		// reserved
		kulong	intMsk01			:1;		// reserved
		kulong	intMsk02			:1;		// SD3 (UHS2) INT Mask(Rising Edge)
		kulong	intMsk03			:1;		// SD3 (UHS2) INT Mask(Falling Edge)
		kulong	intMsk04			:1;		// SD4 (UHS1 Card) INT Mask(Rising Edge)
		kulong	intMsk05			:1;		// SD4 (UHS1 Card) INT Mask(Falling Edge)
		kulong	intMsk06			:1;		// PCIe0 INT Mask(Rising Edge)
		kulong	intMsk07			:1;		// PCIe0 INT Mask(Falling Edge)
		kulong	intMsk08			:1;		// PCIe1 INT Mask(Rising Edge)
		kulong	intMsk09			:1;		// PCIe1 INT Mask(Falling Edge)
		kulong	intMsk10			:1;		// USB2 VBUS INT Mask(Rising Edge)
		kulong	intMsk11			:1;		// USB2 VBUS INT Mask(Falling Edge)
		kulong	intMsk12			:1;		// USB2 ID INT Mask(Rising Edge)
		kulong	intMsk13			:1;		// USB2 ID INT Mask(Falling Edge)
		kulong	intMsk14			:1;		// USB3 VBUS INT Mask(Rising Edge)
		kulong	intMsk15			:1;		// USB3 VBUS INT Mask(Falling Edge)
		kulong	intMsk16			:1;		// USB3 ID INT Mask(Rising Edge)
		kulong	intMsk17			:1;		// USB3 ID INT Mask(Falling Edge)
		kulong							:14;		// reserved
    } bit;
};

/*	Structure of SIGMON register	(1B11_0018h)	*/
union _IoExstopSigmon {
	kulong		word;
	struct {
		kulong	sigmonReserve		:1;		// SIGMON reserved
		kulong	sigmonSd3				:1;		// SIGMON SD3( UHS2 )
		kulong	sigmonSd4				:1;		// SIGMON SD4( UHS1 Card )
		kulong	sigmonPcie0			:1;		// SIGMON PCIe0
		kulong	sigmonPcie1			:1;		// SIGMON PCIe1
		kulong	sigmonUsb2Vbus	:1;		// SIGMON USB2 VBUS
		kulong	sigmonUsb2Id		:1;		// SIGMON USB2 ID
		kulong	sigmonUsb3Vbus	:1;		// SIGMON USB3 VBUS
		kulong	sigmonUsb3Id		:1;		// SIGMON USB3 ID
		kulong									:7;		// reserved
		kulong	sigmon2Reserve		:1;		// SIGMON2 reserved
		kulong	sigmon2Sd3			:1;		// SIGMON2 SD3( UHS2 )
		kulong	sigmon2Sd4			:1;		// SIGMON2 SD4( UHS1 Card )
		kulong	sigmon2Pcie0			:1;		// SIGMON2 PCIe0
		kulong	sigmon2Pcie1			:1;		// SIGMON2 PCIe1
		kulong	sigmon2Usb2Vbus	:1;		// SIGMON2 USB2 VBUS
		kulong	sigmon2Usb2Id		:1;		// SIGMON2 USB2 ID
		kulong	sigmon2Usb3Vbus	:1;		// SIGMON2 USB3 VBUS
		kulong	sigmon2Usb3Id		:1;		// SIGMON2 USB3 ID
		kulong									:7;		// reserved
    } bit;
};

/*	Structure of DEBEN register	(1B11_001Ch)	*/
union _IoExstopDeben {
	kulong		word;
	struct {
		kulong	debenReserve			:1;		// DEBEN reserved
		kulong	debenSd3				:1;		// DEBEN SD3( UHS2 )
		kulong	debenSd4				:1;		// DEBEN SD4( UHS1 Card )
		kulong	debenPcie0				:1;		// DEBEN PCIe0
		kulong	debenPcie1				:1;		// DEBEN PCIe1
		kulong	debenUsb2Vbus		:1;		// DEBEN USB2 VBUS
		kulong	debenUsb2Id			:1;		// DEBEN USB2 ID
		kulong	debenUsb3Vbus		:1;		// DEBEN USB3 VBUS
		kulong	debenUsb3Id			:1;		// DEBEN USB3 ID
		kulong									:1;		// reserved
		kulong	sd2Detim				:2;		// reserved
		kulong	sd3Detim				:2;		// SD3( UHS2 )
		kulong	sd4Detim				:2;		// SD4( UHS1 Card )
		kulong	pcie0Detim				:2;		// PCIe0
		kulong	pcie1Detim				:2;		// PCIe1
		kulong	usb2VbusDetim		:2;		// USB2 VBUS
		kulong	usb2IdDetim			:2;		// USB2 ID
		kulong	usb3VbusDetim		:2;		// USB3 VBUS
		kulong	usb3IdDetim			:2;		// USB3 ID
		kulong									:4;		// reserved
    } bit;
};

/*	Structure of CDINS MOD Control	(1B11_0020h)	*/
union _IoExstopCdimodctrl {
	kulong		word;
	struct {
		kulong	cdimodReserve		:1;		// CDIMOD reserved
		kulong	cdimodSd3				:1;		// CDIMOD SD3( UHS2 )
		kulong	cdimodSd4				:1;		// CDIMOD SD4( UHS1 Card )
		kulong	cdimodPcie0			:1;		// CDIMOD PCIe0
		kulong	cdimodPcie1			:1;		// CDIMOD PCIe1
		kulong	cdimodUsb2Vbus	:1;		// CDIMOD USB2 VBUS
		kulong	cdimodUsb2Id		:1;		// CDIMOD USB2 ID
		kulong	cdimodUsb3Vbus	:1;		// CDIMOD USB3 VBUS
		kulong	cdimodUsb3Id		:1;		// CDIMOD USB3 ID
		kulong									:23;		// reserved
    } bit;
};

/*	Structure of RELC HPROT Control	(1B11_0030h)	*/
union _IoExstopRelchptctrl {
	kulong		word;
	struct {
		kulong	reRHpt			:4;		// RELC R HPROT
		kulong						:4;		// reserved
		kulong	reWHpt		:4;		// RELC W HPROT
		kulong						:20;		// reserved
    } bit;
};

/*	Structure of RAM PD Control	(1B11_0040h)	*/
union _IoExstopRampdctrl {
	kulong		word;
	struct {
		kulong	rampdSd2			:1;		// SD2( UHS1 Wifi )
		kulong	rampdSd3			:1;		// SD3( UHS2 )
		kulong	rampdSd4			:1;		// SD4( UHS1 Card )
		kulong	rampdNf				:1;		// Nand Flash
		kulong	rampdRelc			:1;		// RELC
		kulong	rampdNetsec		:1;		// NETSEC
		kulong	rampdUsb2			:1;		// USB2
		kulong	rampdUsb3			:1;		// USB3
		kulong	rampdPcie0		:1;		// PCIe0
		kulong	rampdPcie1		:1;		// PCIe1
		kulong	rampdEmmc		:1;		// eMMC
		kulong								:21;		// reserved
    } bit;
};

/*	Structure of BUS CLOCK Stop Control	(1B11_0060h)	*/
union _IoExstopBusckstpctrl {
	kulong		word;
	struct {
		kulong	nfCkStp			:1;		// Nand Flash
		kulong	pcie0CkStp		:1;		// PCIe0
		kulong	pcie1CkStp		:1;		// PCIe1
		kulong	xdmacCkStp	:1;		// XDMAC
		kulong	hdmacCkStp	:1;		// HDMAC
		kulong	emmcCkStp	:1;		// eMMC
		kulong	sd2CkStp			:1;		// SD2( Wifi )
		kulong	sd3CkStp			:1;		// SD3( UHS2 )
		kulong	sd4CkStp			:1;		// SD4( UHS1 Card )
		kulong	netsecCkStp	:1;		// NETSEC
		kulong	relcCkStp			:1;		// RELC
		kulong							:21;		// reserved
    } bit;
};

/*	Structure of NETSEC PTPCLK Stop Control	(1B11_0070h)	*/
union _IoExstopNetsecptpclkstopctrl {
	kulong		word;
	struct {
		kulong	netsecPtpStp		:1;		// NETSEC PTP_CLK Stop Control
		kulong								:31;		// reserved
    } bit;
};

/*	Structure of EMMC_CKSTP register	(1B11_0074h)	*/
union _IoExstopEmmcckstp {
	kulong		word;
	struct {
		kulong	emClkStp			:1;		// MMC_BCLK_I Control
		kulong							:31;		// reserved
    } bit;
};

/*	Structure of EM_DRVSTR register	(1B11_0090h)	*/
union  _IoExstopEmdrvstr {
	kulong		word;
	struct {
		kulong	emDsel				:2;		// EM_DSEL
		kulong								:30;		// reserved
    } bit;
};

/*	Structure of EM_PV_DTIMEC register	(1B11_00B4h)	*/
union _IoExstopEmpvdtimec {
	kulong		word;
	struct {
		kulong	pvDtimec	:24;		// PV_DTIMEC
		kulong						:8;		// reserved
    } bit;
};

/*	Structure of EM_PV_AMPBL register	(1B11_00B8h)	*/
union _IoExstopEmpvampbl{
	kulong		word;
	struct {
		kulong	pvAmpbl			:4;		// PV_AMPBL
		kulong							:28;		// reserved
    } bit;
};

/*	Structure of EM_CR_SLOTTYPE register	(1B11_00BCh)	*/
union _IoExstopEmcrslottype {
	kulong		word;
	struct {
		kulong	crSlottype			:1;		// CR_SLOTTYPE
		kulong								:31;		// reserved
    } bit;
};

/*	Structure of EM_CR_BCLKFREQ register	(1B11_00C0h)	*/
union _IoExstopEmcrbclkfreq {
	kulong		word;
	struct {
		kulong	crBclkfreq			:8;		// CR_BCLKFREQ
		kulong								:24;		// reserved
    } bit;
};

/*	Structure of EM_CDDET register	(1B11_00C4h)	*/
union _IoExstopEmcddet {
	kulong		word;
	struct {
		kulong	emcd			:1;		// EMCD
		kulong						:7;		// reserved
		kulong	emphylk		:1;		// EMPHYLK
		kulong						:23;		// reserved
    } bit;
};

/*	Structure of USB2_CKCTL register	(1B11_0200h)	*/
union _IoExstopUsb2ckctl {
	kulong		word;
	struct {
		kulong	hdcHclken		:1;		// HDC_HCLKEN
		kulong							:7;			// reserved
		kulong	hoHclken			:1;		// HO_HCLKEN
		kulong							:23;		// reserved
    } bit;
};

/*	Structure of USB2_RCTL register	(1B11_0204h)	*/
union _IoExstopUsb2rctl {
	kulong		word;
	struct {
		kulong	hdcSrst			:1;		// HDC_SRST
		kulong							:7;		// reserved
		kulong	hoSrst				:1;		// HO_SRST
		kulong							:23;		// reserved
    } bit;
};

/*	Structure of USB2_ANPD register	(1B11_0208h)	*/
union _IoExstopUsb2anpd {
	kulong		word;
	struct {
		kulong	anpd				:1;		// ANPD
		kulong							:31;		// reserved
    } bit;
};

/*	Structure of USB2_HFSEL register	(1B11_020Ch)	*/
union _IoExstopUsb2hfsel {
	kulong		word;
	struct {
		kulong	hfSel				:1;		// HF_SEL
		kulong							:31;		// reserved
    } bit;
};

/*	Structure of USB2_FSEL register	(1B11_0210h)	*/
union _IoExstopUsb2fsel {
	kulong		word;
	struct {
		kulong	fsel					:3;		// FSEL
		kulong	pllbtune			:1;		// PLLBTUNE
		kulong							:28;		// reserved
    } bit;
};

/*	Structure of USB2_EHCI_SB register	(1B11_0214h)	*/
union _IoExstopUsb2ehcisb {
	kulong		word;
	struct {
		kulong	ehciXferCntO		:11;		// EHCI_XFER_CNT_O
		kulong	ehciXferPrdcO	:1;		// EHCI_XFER_PRDC_O
		kulong	ehciBufaccO		:1;		// EHCI_BUFACC_O
		kulong	mcuIncFrdxO		:1;		// MCU_INC_FRDX_O
		kulong	eorRunstopO		:1;		// EOR_RUNSTOP_O
		kulong								:1;		// reserved
		kulong	ehciUsbstsO		:6;		// EHCI_USBSTS_O
		kulong								:10;		// reserved
    } bit;
};

/*	Structure of USB2_EHCI_STRAP register	(1B11_0218h)	*/
union _IoExstopUsb2ehcistrap {
	kulong		word;
	struct {
		kulong	ssFadjHostI		:6;		// SS_FADJ_HOST_I
		kulong							:2;		// reserved
		kulong	ssFladjValI		:6;		// SS_FLADJ_VAL_I
		kulong							:18;		// reserved
    } bit;
};

/*	Structure of USB2_OHCI_IF register	(1B11_021Ch)	*/
union _IoExstopUsb2ohciif {
	kulong		word;
	struct {
		kulong	ohciClkselI				:1;		// OHCI_CLKSEL_I
		kulong									:7;		// reserved
		kulong	utmiSuspendON		:1;		// UTMI_SUSPEND_O_N
		kulong	ohciGsuspendO		:1;		// OHCI_GSUSPEND_O
		kulong	ohciRweO				:1;		// OHCI_RWE_O
		kulong	ohciRmtwkpO			:1;		// OHCI_RMTWKP_O
		kulong	ohciDrweO				:1;		// OHCI_DRWE_O
		kulong	ohciCcsO					:1;		// OHCI_CCS_O
		kulong	ohciSofON				:1;		// OHCI_SOF_O_N
		kulong	ohciBufaccO			:1;		// OHCI_BUFACC_O
		kulong									:16;		// reserved
    } bit;
};

/*	Structure of USB2_AHB_SLVIF register	(1B11_0220h)	*/
union _IoExstopUsb2ahbslvif {
	kulong		word;
	struct {
		kulong	regRdyO			:1;		// REG_RDY_O
		kulong							:31;		// reserved
    } bit;
};

/*	Structure of USB2_LMODSET register	(1B11_0224h)	*/
union _IoExstopUsb2lmodset {
	kulong		word;
	struct {
		kulong	ssEnaIncr4I			:1;		// SS_ENA_INCR4_I
		kulong	ssEnaIncr8I			:1;		// SS_ENA_INCR8_I
		kulong	ssEnaIncr16I		:1;		// SS_ENA_INCR16_I
		kulong	ssEnaIncAlI			:1;		// SS_ENA_INC_AL_I
		kulong	ssEhci64bEnI		:1;		// SS_EHCI64B_EN_I
		kulong								:26;		// reserved
    } bit;
};

/*	Structure of USB2_PMODSET register	(1B11_0228h)	*/
union _IoExstopUsb2pmodset {
	kulong		word;
	struct {
		kulong	rpdpenI			:1;		// RPDPEN_I
		kulong							:7;		// reserved
		kulong	rpdmenI			:1;		// RPDMEN_I
		kulong							:23;		// reserved
    } bit;
};

/*	Structure of USB2_HPT_CTL register	(1B11_022Ch)	*/
union _IoExstopUsb2hptctl {
	kulong		word;
	struct {
		kulong	usb2Ehpt			:4;		// RPDPEN_I
		kulong							:4;		// reserved
		kulong	usb2Ohpt		:4;		// RPDMEN_I
		kulong							:20;		// reserved
    } bit;
};

/*	Structure of USB2_IDVBUSCTL register	(1B11_0230h)	*/
union _IoExstopUsb2idvbusctl {
	kulong		word;
	struct {
		kulong	usb2IdpuVal		:1;		// USB2_IDPU_VAL
		kulong								:3;		// reserved
		kulong	usb2IdpuSel		:1;		// USB2_IDPU_SEL
		kulong								:3;		// reserved
		kulong	usb2IdSel			:1;		// USB2_ID_SEL
		kulong								:3;		// reserved
		kulong	usb2IdVal			:1;		// USB2_ID_VAL
		kulong								:3;		// reserved
		kulong	usb2VbSel			:1;		// USB2_VB_SEL
		kulong								:3;		// reserved
		kulong	usb2VbVal			:1;		// USB2_VB_VAL
		kulong								:3;		// reserved
		kulong	usb2VbdetSel		:2;		// USB2_VBDET_SEL
		kulong								:2;		// reserved
		kulong	usb2VbdetVal		:1;		// USB2_VBDET_VAL
		kulong								:3;		// reserved
    } bit;
};

/*	Structure of USB2_HDMAC1 register	(1B11_0238h)	*/
union _IoExstopUsb2hdmac1 {
	kulong		word;
	struct {
		kulong	hdmacBc1			:4;		// HDMAC_BC1
		kulong								:4;		// reserved
		kulong	hdmacBt1			:2;		// HDMAC_BT1
		kulong								:6;		// reserved
		kulong	hdmacMs1			:1;		// HDMAC_MS1
		kulong								:15;		// reserved
    } bit;
};

/*	Structure of USB2_HDMAC2 register	(1B11_023Ch)	*/
union _IoExstopUsb2hdmac2 {
	kulong		word;
	struct {
		kulong	hdmacBc2			:4;		// HDMAC_BC2
		kulong								:4;		// reserved
		kulong	hdmacBt2			:2;		// HDMAC_BT2
		kulong								:6;		// reserved
		kulong	hdmacMs2			:1;		// HDMAC_MS2
		kulong								:15;		// reserved
    } bit;
};

/*	Structure of USB2_DMAFSM1 register	(1B11_0240h)	*/
union _IoExstopUsb2dmafsm1 {
	kulong		word;
	struct {
		kulong	fsmrst1				:1;		// FSMRST1
		kulong	dmaTransState1	:1;		// DMA_TRANS_STATE1
		kulong								:30;	// reserved
    } bit;
};

/*	Structure of USB2_DMAFSM2 register	(1B11_0244h)	*/
union _IoExstopUsb2dmafsm2 {
	kulong		word;
	struct {
		kulong	fsmrst2				:1;		// FSMRST2
		kulong	dmaTransState2	:1;		// DMA_TRANS_STATE2
		kulong								:30;	// reserved
    } bit;
};

/*	Structure of USB3_CKCTL register	(1B11_0280h)	*/
union _IoExstopUsb3ckctl {
	kulong		word;
	struct {
		kulong	aclken				:1;		// ACLKEN
		kulong							:30;	// reserved
    } bit;
};

/*	Structure of USB3_RCTL register	(1B11_0284h)	*/
union _IoExstopUsb3rctl {
	kulong		word;
	struct {
		kulong	sftrst					:1;		// SFTRST
		kulong								:7;		// reserved
		kulong	phyResetN			:1;		// PHY_RESET_N
		kulong								:23;	// reserved
    } bit;
};

/*	Structure of USB3_RCV_SNS register	(1B11_0288h)	*/
union _IoExstopUsb3rcvsns {
	kulong		word;
	struct {
		kulong	acjtLevel			:5;		// ACJT_LEVEL
		kulong							:27;		// reserved
    } bit;
};

/*	Structure of USB3_FSEL register	(1B11_028Ch)	*/
union _IoExstopUsb3fsel {
	kulong		word;
	struct {
		kulong	fsel3						:6;		// FSEL3
		kulong								:2;		// reserved
		kulong	mpllMultiplier		:7;		// MPLL_MULTIPLIER
		kulong								:1;		// reserved
		kulong	sscRefClkSel		:9;		// SSC_REF_CLK_SEL
		kulong								:3;		// reserved
		kulong	refClkdiv2			:1;		// REF_CLKDIV2
		kulong								:3;		// reserved
    } bit;
};

/*	Structure of USB3_RFC_CTL register	(1B11_0290h)	*/
union _IoExstopUsb3rfcctl {
	kulong		word;
	struct {
		kulong	refSspEn			:1;		// REF_SSP_EN
		kulong							:7;		// reserved
		kulong	refUsePad		:1;		// REF_USE_PAD
		kulong							:23;		// reserved
    } bit;
};

/*	Structure of USB3_HO_IF register	(1B11_0294h)	*/
union _IoExstopUsb3hoif {
	kulong		word;
	struct {
		kulong	pciImplement			:1;		// PCI_IMPLEMENT
		kulong									:7;		// reserved
		kulong	hostMsiEnable		:1;		// HOST_MSI_ENABLE
		kulong									:7;		// reserved
		kulong	xhcBme					:1;		// XHC_BME
		kulong	xhcAc64					:1;		// XHC_AC64
		kulong									:6;		// reserved
		kulong	hostSystemErr		:1;		// HOST_SYSTEM_ERR
		kulong									:7;		// reserved
    } bit;
};

/*	Structure of USB3_JT_ADJ register	(1B11_0298h)	*/
union _IoExstopUsb3jtadj {
	kulong		word;
	struct {
		kulong	fladj30mhzReg		:6;		// FLADJ_30MHZ_REG
		kulong									:10;	// reserved
		kulong	usb3OvrcurEn			:1;		// USB3_OVRCUR_EN
		kulong									:15;	// reserved
    } bit;
};

/*	Structure of USB3_IDVBUSCTL register	(1B11_02A0h)	*/
union _IoExstopUsb3idvbusctl {
	kulong		word;
	struct {
		kulong	usb3IdpuVal		:1;		// USB3_IDPU_VAL
		kulong								:7;		// reserved
		kulong	usb3IdSel			:1;		// USB3_ID_SEL
		kulong								:3;		// reserved
		kulong	usb3IdVal			:1;		// USB3_ID_VAL
		kulong								:3;		// reserved
		kulong	usb3VbSel			:1;		// USB3_VB_SEL
		kulong								:3;		// reserved
		kulong	usb3VbVal			:1;		// USB3_VB_VAL
		kulong								:3;		// reserved
		kulong	usb3VbdetSel		:2;		// USB3_VBDET_SEL
		kulong								:2;		// reserved
		kulong	usb3VbdetVal		:1;		// USB3_VBDET_VAL
		kulong								:3;		// reserved
    } bit;
};

/*	Structure of NF_IP_CTL register	(1B11_0300h)	*/
union _IoExstopNfipctl {
	kulong		word;
	struct {
		kulong	dscvInhibit		:1;		// Nand Flash IP ( cdns_hpnfc ) discovery_inhibit Control
		kulong	dscvIgnrCrc		:1;		// Nand Flash IP ( cdns_hpnfc ) discovery_ignore_crc Control
		kulong							:2;		// reserved
		kulong	bootEn			:1;		// Nand Flash IP ( cdns_hpnfc ) boot_en Control
		kulong							:3;		// reserved
		kulong	iddqEn				:1;		// Nand Flash IP ( cdns_flash_dll_phy ) iddq_en Control
		kulong							:23;	// reserved
    } bit;
};

/*	Structure of NF_BTSQ_STATE register	(1B11_0304h)	*/
union _IoExstopNfbtsqstate {
	kulong		word;
	struct {
		kulong	initFail			:1;		// Nand Flash IP ( cdns_hpnfc ) init_fail monitor
		kulong						:3;		// reserved
		kulong	bootComp	:1;		// Nand Flash IP ( cdns_hpnfc ) boot_comp monitor
		kulong						:3;		// reserved
		kulong	bootError	:1;		// Nand Flash IP ( cdns_hpnfc ) boot_error monitor
		kulong						:3;		// reserved
		kulong	ctrlBusy		:1;		// Nand Flash IP ( cdns_hpnfc ) ctrl_busy monitor
		kulong						:19;	// reserved
    } bit;
};

/*	Structure of NF_RB_VALID_TM register	(1B11_0308h)	*/
union _IoExstopNfbvalidtm {
	kulong		word;
	struct {
		kulong	rbValidTime		:16;	// Nand Flash IP ( cdns_hpnfc ) rb_valid_time[15:0] Control
		kulong								:16;	// reserved
    } bit;
};

/*	Structure of NF_PHY_CTRL_REG register	(1B11_030Ch)	*/
union _IoExstopNfphyctrlreg {
	kulong		word;
	struct {
		kulong	phyCtrl			:32;	// Nand Flash IP ( cdns_hpnfc )  phy_ctrl_reg[31:0] Control
    } bit;
};

/*	Structure of NF_PHY_DQ_TIM register	(1B11_0310h)	*/
union _IoExstopNfphydqtim {
	kulong		word;
	struct {
		kulong	phyDqTiming		:32;	// Nand Flash IP ( cdns_hpnfc )  phy_dq_timing[31:0] Control
    } bit;
};

/*	Structure of NF_PHY_DQS_TIM register	(1B11_0314h)	*/
union _IoExstopNfphydqstim {
	kulong		word;
	struct {
		kulong	phyDqsTiming	:32;	// Nand Flash IP ( cdns_hpnfc )  phy_dqs_timing[31:0] Control
    } bit;
};

/*	Structure of NF_PHY_GT_LPBK register	(1B11_0318h)	*/
union _IoExstopNfphygtlpbk {
	kulong		word;
	struct {
		kulong	phyGtLpbkCtl		:32;	// Nand Flash IP ( cdns_hpnfc )  phy_gate_lpbk_ctrl_reg[31:0] Control
    } bit;
};

/*	Structure of NF_PHY_DLL_MCTL register	(1B11_031Ch)	*/
union _IoExstopNfphydllmctl {
	kulong		word;
	struct {
		kulong	phyDllMstCtl		:32;	// Nand Flash IP ( cdns_hpnfc )  phy_dll_master_ctrl_reg[31:0] Control
    } bit;
};

/*	Structure of NF_PHY_DLL_SCTL register	(1B11_0320h)	*/
union _IoExstopNfphydllsctl {
	kulong		word;
	struct {
		kulong	phyDllSlvCtl		:32;	// Nand Flash IP ( cdns_hpnfc )  phy_dll_slave_ctrl_reg[31:0] Control
    } bit;
};

/*	Structure of NF_BOOT_ECC_CTL register	(1B11_0324h)	*/
union _IoExstopNfbooteccctl {
	kulong		word;
	struct {
		kulong	bootEccSecSiz		:16;	// Nand Flash IP ( cdns_hpnfc )  boot_ecc_sec_size[15:0] Control
		kulong	btEccCorrStr		:3;		// Nand Flash IP ( cdns_hpnfc )  boot_ecc_corr_str[2:0] Control
		kulong								:5;		// reserved
		kulong	bootEccEn			:1;		// Nand Flash IP ( cdns_hpnfc )  boot_ecc_enable Control
		kulong								:7;		// reserved
    } bit;
};

/*	Structure of NF_NFWPX_CNT register	(1B11_0328h)	*/
union _IoExstopNfwpxcnt {
	kulong		word;
	struct {
		kulong	nfwpxCnt			:1;		// Nand Flash IP ( cdns_hpnfc )  NFWPX mask Control
		kulong							:31;	// reserved
    } bit;
};

/*	Structure of INTSTAT register	(1B11_0F00h)	*/
union _IoExstopIntstat {
	kulong		word;
	struct {
		kulong	__intstat00			:1;		// SD2 (UHS1 Wifi) rising edge detection
		kulong	__intstat01			:1;		// SD2 (UHS1 Wifi) falling edge detection
		kulong	__intstat02			:1;		// SD3 (UHS2) rising edge detection
		kulong	__intstat03			:1;		// SD3 (UHS2) falling edge detection
		kulong	__intstat04			:1;		// SD4 (UHS1 Card) rising edge detection
		kulong	__intstat05			:1;		// SD4 (UHS1 Card) falling edge detection
		kulong	__intstat06			:1;		// PCIe0 rising edge detection
		kulong	__intstat07			:1;		// PCIe0 falling edge detection
		kulong	__intstat08			:1;		// PCIe1 rising edge detection
		kulong	__intstat09			:1;		// PCIe1 falling edge detection
		kulong	__intstat10			:1;		// USB2 VBUS rising edge detection
		kulong	__intstat11			:1;		// USB2 VBUS falling edge detection
		kulong	__intstat12			:1;		// USB2 ID rising edge detection
		kulong	__intstat13			:1;		// USB2 ID falling edge detection
		kulong	__intstat14			:1;		// USB3 VBUS rising edge detection
		kulong	__intstat15			:1;		// USB3 VBUS falling edge detection
		kulong	__intstat16			:1;		// USB3 ID rising edge detection
		kulong	__intstat17			:1;		// USB3 ID falling edge detection
		kulong								:14;	// reserved
    } bit;
};

struct _IoExstop {
	IoExstopXdmaclowpowctrl		xdmacLpctrl;							/*	1B11_(0000 - 0003h)	*/
	kuchar											dmyExstop0004000b[0x000C-0x0004];	/*	1B11_(0004 - 000Bh)	*/
	IoExstopSoftreset						softreset;								/*	1B11_(000C - 000Fh)	*/
	IoExstopSoftreset2						softreset2;								/*	1B11_(0010 - 0013h)	*/
	IoExstopIntmsk							intMsk;									/*	1B11_(0014 - 0017h)	*/
	IoExstopSigmon							sigmon;									/*	1B11_(0018 - 001Bh)	*/
	IoExstopDeben							deben;									/*	1B11_(001C - 001Fh)	*/
	IoExstopCdimodctrl					cdinsmdctl;								/*	1B11_(0020 - 0023h)	*/
	kuchar											dmyExstop0024002f[0x0030-0x0024];	/*	1B11_(0024 - 002Fh)	*/
	IoExstopRelchptctrl					rlcHptCtl;							/*	1B11_(0030 - 0033h)	*/
	kuchar											dmyExstop0034003f[0x0040-0x0034];	/*	1B11_(0034 - 003Fh)	*/
	IoExstopRampdctrl						ramPd;									/*	1B11_(0040 - 0043h)	*/
	kuchar											dmyExstop0044005f[0x0060-0x0044];	/*	1B11_(0044 - 005Fh)	*/
	IoExstopBusckstpctrl					busckstp;								/*	1B11_(0060 - 0063h)	*/
	kuchar											dmyExstop0064006f[0x0070-0x0064];	/*	1B11_(0064 - 006Fh)	*/
	IoExstopNetsecptpclkstopctrl	nsecCkstp;								/*	1B11_(0070 - 0073h)	*/
	IoExstopEmmcckstp					emmcCkStp;								/*	1B11_(0074 - 0077h)	*/
	kuchar											dmyExstop0078008f[0x0090-0x0078];	/*	1B11_(0078 - 008Fh)	*/
	IoExstopEmdrvstr						emDrvstr;								/*	1B11_(0090 - 0093h)	*/
	kuchar											dmyExstop009400b3[0x00B4-0x0094];	/*	1B11_(0094 - 00B3h)	*/
	IoExstopEmpvdtimec					emPvDtimec;							/*	1B11_(00B4 - 00B7h)	*/
	IoExstopEmpvampbl					emPvAmpbl;							/*	1B11_(00B8 - 00BBh)	*/
	IoExstopEmcrslottype				emCrSlottype;							/*	1B11_(00BC - 00BFh)	*/
	IoExstopEmcrbclkfreq				emCrBclkfreq;							/*	1B11_(00C0 - 00C3h)	*/
	IoExstopEmcddet						emCddet;								/*	1B11_(00C4 - 00C7h)	*/
	kuchar											dmyExstop00c801ff[0x0200-0x00C8];	/*	1B11_(00C8 - 01FFh)	*/
	IoExstopUsb2ckctl						usb2Ckctl;								/*  1B11_(0200 - 0203h)	*/
	IoExstopUsb2rctl						usb2Rctl;								/*  1B11_(0204 - 0207h)	*/
	IoExstopUsb2anpd						usb2Anpd;								/*  1B11_(0208 - 020Bh)	*/
	IoExstopUsb2hfsel						usb2Hfsel;								/*  1B11_(020C - 020Fh)	*/
	IoExstopUsb2fsel						usb2Fsel;								/*  1B11_(0210 - 0213h)	*/
	IoExstopUsb2ehcisb					usb2EhciSb;							/*  1B11_(0214 - 0217h)	*/
	IoExstopUsb2ehcistrap				usb2EhciStrap;						/*  1B11_(0218 - 021Bh)	*/
	IoExstopUsb2ohciif					usb2OhciIf;							/*  1B11_(021C - 021Fh)	*/
	IoExstopUsb2ahbslvif					usb2AhbSlvif;							/*  1B11_(0220 - 0223h)	*/
	IoExstopUsb2lmodset				usb2Lmodset;							/*  1B11_(0224 - 0227h)	*/
	IoExstopUsb2pmodset				usb2Pmodset;							/*  1B11_(0228 - 022Bh)	*/
	IoExstopUsb2hptctl					usb2HptCtl;							/*  1B11_(022C - 022Fh)	*/
	IoExstopUsb2idvbusctl				usb2Idvbusctl;							/*  1B11_(0230 - 0233h)	*/
	kuchar											dmyExstop02340237[0x0238-0x0234];	/*	1B11_(0234 - 0237h)	*/
	IoExstopUsb2hdmac1				usb2Hdmac1;							/*  1B11_(0238 - 023Bh)	*/
	IoExstopUsb2hdmac2				usb2Hdmac2;							/*  1B11_(023C - 023Fh)	*/
	IoExstopUsb2dmafsm1				usb2Dmafsm1;							/*  1B11_(0240 - 0243h)	*/
	IoExstopUsb2dmafsm2				usb2Dmafsm2;							/*  1B11_(0244 - 0247h)	*/
	kuchar											dmyExstop0248027f[0x0280-0x0248];	/*	1B11_(0248 - 027Fh)	*/
	IoExstopUsb3ckctl						usb3Ckctl;								/*  1B11_(0280 - 0283h)	*/
	IoExstopUsb3rctl						usb3Rctl;								/*  1B11_(0284 - 0287h)	*/
	IoExstopUsb3rcvsns					usb3RcvSns;							/*  1B11_(0288 - 028Bh)	*/
	IoExstopUsb3fsel						usb3Fsel;								/*  1B11_(028C - 028Fh)	*/
	IoExstopUsb3rfcctl						usb3RfcCtl;							/*  1B11_(0290 - 0293h)	*/
	IoExstopUsb3hoif						usb3HoIf;								/*  1B11_(0294 - 0298h)	*/
	IoExstopUsb3jtadj						usb3JtAdj;							/*  1B11_(0298 - 029Bh)	*/
	kuchar											dmyExstop029c029f[0x02A0-0x029C];	/*	1B11_(029C - 029Fh)	*/
	IoExstopUsb3idvbusctl				usb3Idvbusctl;							/*  1B11_(02A0 - 02A3h)	*/
	kuchar											dmyExstop02a402ff[0x0300-0x02A4];	/*	1B11_(02A4 - 02FFh)	*/
	IoExstopNfipctl							nfIpCtl;								/*	1B11_(0300 - 0303h)	*/
	IoExstopNfbtsqstate					nfBtsqState;							/*	1B11_(0304 - 0307h)	*/
	IoExstopNfbvalidtm					nfRbValidTm;							/*	1B11_(0308 - 030Bh)	*/
	IoExstopNfphyctrlreg					nfPhyCtrlReg;						/*	1B11_(030C - 030Fh)	*/
	IoExstopNfphydqtim					nfPhyDqTim;							/*	1B11_(0310 - 0313h)	*/
	IoExstopNfphydqstim				nfPhyDqsTim;							/*	1B11_(0314 - 0317h)	*/
	IoExstopNfphygtlpbk					nfPhyGtLpbk;							/*	1B11_(0318 - 031Bh)	*/
	IoExstopNfphydllmctl				nfPhyDllMctl;						/*	1B11_(031C - 031Fh)	*/
	IoExstopNfphydllsctl					nfPhyDllSctl;						/*	1B11_(0320 - 0323h)	*/
	IoExstopNfbooteccctl					nfBootEccCtl;						/*	1B11_(0324 - 0327h)	*/
	IoExstopNfwpxcnt						nfNfwpxCnt;							/*	1B11_(0328 - 032Bh)	*/
	kuchar											dmyExstop032c0eff[0x0F00-0x032C];	/*	1B11_(032C - 0EFFh)	*/
	IoExstopIntstat							intstat;								/*	1B11_(0F00 - 0F03h)	*/
	kuchar											dmyExstop0f04ffff[0x10000-0x0F04];	/*	1B11_(0F04 - FFFFh)	*/
};

struct _SnsJmlexs
{
	KObject parent;
};


extern volatile IoGpv   		ioGpv;							// addr 19000000h-
extern volatile IoExstop 		ioExstop;						// addr 1B110000h-


KConstType 	sns_jmlexs_get_type(void);
SnsJmlexs*		sns_jmlexs_new(void);
SnsJmlexs* 		sns_jmlexs_get(void);


#endif /* __SNS_JMLEXS_H__ */
