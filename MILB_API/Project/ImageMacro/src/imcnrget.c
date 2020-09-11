/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :李昕
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

#include "imcnrget.h"
#include "imcnr.h"
#include "imcnrset.h"
#include "imcnrinit.h"
#include "imcnrcspr.h"
#include "imcnraxi.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdscnr.h"
// for memset
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImCnrGet, im_cnr_get);
#define IM_CNR_GET_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImCnrGetPrivate, IM_TYPE_CNR_GET))

struct _ImCnrGetPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// SPR setting for CbCr address (OFL)
const static T_IM_CNR_RDMA_ADDR_CTRL_C S_G_IM_CNR_OFL_CTRL_C[D_IM_CNR_CH_NUM_MAX] = {
	// CSPREN		CGDKEN		MCEN		MCYTHH		MCYTHV
	// MCCTHH		MCCTHV		MCYDYM		MCYDYMDT	MCYSCL
	// MCCSCL		MCSSCL		LCEN		LCYTHH		LCYTHV
	// LCCTHH		LCCTHV		LCYDYM		LCYDYMDT	LCYSCL
	// LCCSCL		LCSSCL		BLEND		WHTMD

	// Pipeline-1
	{0x28423000,	0x28423008,	0x28423020,	0x28423024,	0x28423028,
	 0x2842302C,	0x28423030,	0x28423034,	0x28423038,	0x28423040,
	 0x28423060,	0x28423080,	0x284230C0,	0x284230C4,	0x284230C8,
	 0x284230CC,	0x284230D0,	0x284230D4,	0x284230D8,	0x284230E0,
	 0x28423100,	0x28423120,	0x28423160,	0x284231D0},
	// Pipeline-2
	{0x28523000,	0x28523008,	0x28523020,	0x28523024,	0x28523028,
	 0x2852302C,	0x28523030,	0x28523034,	0x28523038,	0x28523040,
	 0x28523060,	0x28523080,	0x285230C0,	0x285230C4,	0x285230C8,
	 0x285230CC,	0x285230D0,	0x285230D4,	0x285230D8,	0x285230E0,
	 0x28523100,	0x28523120,	0x28523160,	0x285231D0},
	// Pipeline-3
	{0x28623000,	0x28623008,	0x28623020,	0x28623024,	0x28623028,
	 0x2862302C,	0x28623030,	0x28623034,	0x28623038,	0x28623040,
	 0x28623060,	0x28623080,	0x286230C0,	0x286230C4,	0x286230C8,
	 0x286230CC,	0x286230D0,	0x286230D4,	0x286230D8,	0x286230E0,
	 0x28623100,	0x28623120,	0x28623160,	0x286231D0},
};

// SPR setting for CbCr address (OTF)
const static T_IM_CNR_RDMA_ADDR_CTRL_C S_G_IM_CNR_OTF_CTRL_C[D_IM_CNR_CH_NUM_MAX] = {
	// CSPREN		CGDKEN		MCEN		MCYTHH		MCYTHV
	// MCCTHH		MCCTHV		MCYDYM		MCYDYMDT	MCYSCL
	// MCCSCL		MCSSCL		LCEN		LCYTHH		LCYTHV
	// LCCTHH		LCCTHV		LCYDYM		LCYDYMDT	LCYSCL
	// LCCSCL		LCSSCL		BLEND		WHTMD

	// Pipeline-1
	{0x28421000,	0x28421008,	0x28421020,	0x28421024,	0x28421028,
	 0x2842102C,	0x28421030,	0x28421034,	0x28421038,	0x28421040,
	 0x28421060,	0x28421080,	0x284210C0,	0x284210C4,	0x284210C8,
	 0x284210CC,	0x284210D0,	0x284210D4,	0x284210D8,	0x284210E0,
	 0x28421100,	0x28421120,	0x28421160,	0x284211D0},
	// Pipeline-2
	{0x28521000,	0x28521008,	0x28521020,	0x28521024,	0x28521028,
	 0x2852102C,	0x28521030,	0x28521034,	0x28521038,	0x28521040,
	 0x28521060,	0x28521080,	0x285210C0,	0x285210C4,	0x285210C8,
	 0x285210CC,	0x285210D0,	0x285210D4,	0x285210D8,	0x285210E0,
	 0x28521100,	0x28521120,	0x28521160,	0x285211D0},
	// Pipeline-3
	{0x28621000,	0x28621008,	0x28621020,	0x28621024,	0x28621028,
	 0x2862102C,	0x28621030,	0x28621034,	0x28621038,	0x28621040,
	 0x28621060,	0x28621080,	0x286210C0,	0x286210C4,	0x286210C8,
	 0x286210CC,	0x286210D0,	0x286210D4,	0x286210D8,	0x286210E0,
	 0x28621100,	0x28621120,	0x28621160,	0x286211D0},
};

// SPR setting for Y address (OFL)
const static T_IM_CNR_RDMA_ADDR_OFL_CTRL_Y S_G_IM_CNR_OFL_CTRL_Y[D_IM_CNR_CH_NUM_MAX] = {
	// YSPREN			YSPRMODE		YSPRFXEY		YSPRFXEC		YSPRALPBD
	{0x28424000,		0x28424004,		0x28424020,		0x28424024,		0x28424028},	// Pipeline-1
	{0x28524000,		0x28524004,		0x28524020,		0x28524024,		0x28524028},	// Pipeline-2
	{0x28624000,		0x28624004,		0x28624020,		0x28624024,		0x28624028},	// Pipeline-3
};

// YSPR Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_OFL_YSPR_TBL S_G_IM_CNR_OFL_YSPR_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// YSPRDYEYOF_1		YSPRDYEYOF_2	YSPRDYEYGA_1	YSPRDYEYGA_2	YSPRDYEYBD_1	YSPRDYEYBD_2
	{0x28424030,		0x28424034,		0x28424038,		0x2842403C,		0x28424040,		0x28424044},	// Pipeline-1
	{0x28524030,		0x28524034,		0x28524038,		0x2852403C,		0x28524040,		0x28524044},	// Pipeline-2
	{0x28624030,		0x28624034,		0x28624038,		0x2862403C,		0x28624040,		0x28624044},	// Pipeline-3
};

// CSPR Mid-Y Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL S_G_IM_CNR_OFL_CSPR_MID_Y_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// MCYSCLOF_1		MCYSCLOF_2		MCYSCLGA_1		MCYSCLGA_2		MCYSCLBD_1,		MCYSCLBD_2
	{0x28423048,		0x2842304C,		0x28423050,		0x28423054,		0x28423058,		0x2842305C},	// Pipeline-1
	{0x28523048,		0x2852304C,		0x28523050,		0x28523054,		0x28523058,		0x2852305C},	// Pipeline-2
	{0x28623048,		0x2862304C,		0x28623050,		0x28623054,		0x28623058,		0x2862305C},	// Pipeline-3
};

// CSPR Mid-Y Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL S_G_IM_CNR_OTF_CSPR_MID_Y_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// MCYSCLOF_1		MCYSCLOF_2		MCYSCLGA_1		MCYSCLGA_2		MCYSCLBD_1,		MCYSCLBD_2
	{0x28421048,		0x2842104C,		0x28421050,		0x28421054,		0x28421058,		0x2842105C},	// Pipeline-1
	{0x28521048,		0x2852104C,		0x28521050,		0x28521054,		0x28521058,		0x2852105C},	// Pipeline-2
	{0x28621048,		0x2862104C,		0x28621050,		0x28621054,		0x28621058,		0x2862105C},	// Pipeline-3
};

// CSPR Mid-CC-Y Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL S_G_IM_CNR_OFL_CSPR_MID_CC_Y_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// MCCSCLOF_1		MCCSCLOF_2		MCCSCLGA_1		MCCSCLGA_2		MCCSCLBD_1,		MCCSCLBD_2
	{0x28423068,		0x2842306C,		0x28423070,		0x28423074,		0x28423078,		0x2842307C},	// Pipeline-1
	{0x28523068,		0x2852306C,		0x28523070,		0x28523074,		0x28523078,		0x2852307C},	// Pipeline-2
	{0x28623068,		0x2862306C,		0x28623070,		0x28623074,		0x28623078,		0x2862307C},	// Pipeline-3
};

// CSPR Mid-CC-Y Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL S_G_IM_CNR_OTF_CSPR_MID_CC_Y_TBL[D_IM_CNR_CH_NUM_MAX] = {
	{0x28421068,		0x2842106C,		0x28421070,		0x28421074,		0x28421078,		0x2842107C},	// Pipeline-1
	{0x28521068,		0x2852106C,		0x28521070,		0x28521074,		0x28521078,		0x2852107C},	// Pipeline-2
	{0x28621068,		0x2862106C,		0x28621070,		0x28621074,		0x28621078,		0x2862107C},	// Pipeline-3
};

// CSPR Mid-CC-C Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL S_G_IM_CNR_OFL_CSPR_MID_CC_C_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// MCSSCLOF_1		MCSSCLOF_2		MCSSCLGA_1		MCSSCLGA_2		MCSSCLBD_1,		MCSSCLBD_1
	{0x28423088,		0x2842308C,		0x28423090,		0x28423094,		0x28423098,		0x2842309C},	// Pipeline-1
	{0x28523088,		0x2852308C,		0x28523090,		0x28523094,		0x28523098,		0x2852309C},	// Pipeline-2
	{0x28623088,		0x2862308C,		0x28623090,		0x28623094,		0x28623098,		0x2862309C},	// Pipeline-3
};

// CSPR Mid-CC-C Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL S_G_IM_CNR_OTF_CSPR_MID_CC_C_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// MCSSCLOF_1		MCSSCLOF_2		MCSSCLGA_1		MCSSCLGA_2		MCSSCLBD_1,		MCSSCLBD_1
	{0x28421088,		0x2842108C,		0x28421090,		0x28421094,		0x28421098,		0x2842109C},	// Pipeline-1
	{0x28521088,		0x2852108C,		0x28521090,		0x28521094,		0x28521098,		0x2852109C},	// Pipeline-2
	{0x28621088,		0x2862108C,		0x28621090,		0x28621094,		0x28621098,		0x2862109C},	// Pipeline-3
};

// CSPR Low-Y Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL S_G_IM_CNR_OFL_CSPR_LOW_Y_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// LCYSCLOF_1		LCYSCLOF_2		LCYSCLGA_1		LCYSCLGA_2		LCYSCLBD_1,		LCYSCLBD_2
	{0x284230E8,		0x284230EC,		0x284230F0,		0x284230F4,		0x284230F8,		0x284230FC},	// Pipeline-1
	{0x285230E8,		0x285230EC,		0x285230F0,		0x285230F4,		0x285230F8,		0x285230FC},	// Pipeline-2
	{0x286230E8,		0x286230EC,		0x286230F0,		0x286230F4,		0x286230F8,		0x286230FC},	// Pipeline-3
};

// CSPR Low-Y Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL S_G_IM_CNR_OTF_CSPR_LOW_Y_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// LCYSCLOF_1		LCYSCLOF_2		LCYSCLGA_1		LCYSCLGA_2		LCYSCLBD_1,		LCYSCLBD_2
	{0x284210E8,		0x284210EC,		0x284210F0,		0x284210F4,		0x284210F8,		0x284210FC},	// Pipeline-1
	{0x285210E8,		0x285210EC,		0x285210F0,		0x285210F4,		0x285210F8,		0x285210FC},	// Pipeline-2
	{0x286210E8,		0x286210EC,		0x286210F0,		0x286210F4,		0x286210F8,		0x286210FC},	// Pipeline-3
};

// CSPR Low-CC-Y Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL S_G_IM_CNR_OFL_CSPR_LOW_CC_Y_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// LCCSCLOF_1		LCCSCLOF_2		LCCSCLGA_1		LCCSCLGA_2		LCCSCLBD_1,		LCCSCLBD_2
	{0x28423108,		0x2842310C,		0x28423110,		0x28423114,		0x28423118,		0x2842311C},	// Pipeline-1
	{0x28523108,		0x2852310C,		0x28523110,		0x28523114,		0x28523118,		0x2852311C},	// Pipeline-2
	{0x28623108,		0x2862310C,		0x28623110,		0x28623114,		0x28623118,		0x2862311C},	// Pipeline-3
};

// CSPR Low-CC-Y Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL S_G_IM_CNR_OTF_CSPR_LOW_CC_Y_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// LCCSCLOF_1		LCCSCLOF_2		LCCSCLGA_1		LCCSCLGA_2		LCCSCLBD_1,		LCCSCLBD_2
	{0x28421108,		0x2842110C,		0x28421110,		0x28421114,		0x28421118,		0x2842111C},	// Pipeline-1
	{0x28521108,		0x2852110C,		0x28521110,		0x28521114,		0x28521118,		0x2852111C},	// Pipeline-2
	{0x28621108,		0x2862110C,		0x28621110,		0x28621114,		0x28621118,		0x2862111C},	// Pipeline-3
};

// CSPR Low-CC-C Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL S_G_IM_CNR_OFL_CSPR_LOW_CC_C_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// LCSSCLOF_1		LCSSCLOF_2		LCSSCLGA_1		LCSSCLGA_2		LCSSCLBD_1,		LCSSCLBD_2
	{0x28423128,		0x2842312C,		0x28423130,		0x28423134,		0x28423138,		0x2842313C},	// Pipeline-1
	{0x28523128,		0x2852312C,		0x28523130,		0x28523134,		0x28523138,		0x2852313C},	// Pipeline-2
	{0x28623128,		0x2862312C,		0x28623130,		0x28623134,		0x28623138,		0x2862313C},	// Pipeline-3
};

// CSPR Low-CC-C Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL S_G_IM_CNR_OTF_CSPR_LOW_CC_C_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// LCSSCLOF_1		LCSSCLOF_2		LCSSCLGA_1		LCSSCLGA_2		LCSSCLBD_1,		LCSSCLBD_2
	{0x28421128,		0x2842112C,		0x28421130,		0x28421134,		0x28421138,		0x2842113C},	// Pipeline-1
	{0x28521128,		0x2852112C,		0x28521130,		0x28521134,		0x28521138,		0x2852113C},	// Pipeline-2
	{0x28621128,		0x2862112C,		0x28621130,		0x28621134,		0x28621138,		0x2862113C},	// Pipeline-3
};

// CSPR EDGE Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL S_G_IM_CNR_OFL_CSPR_EDGE_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// CESCLOF_1		CESCLOF_2		CESCLGA_1		CESCLGA_2		CESCLBD_1,		CESCLBD_2
	{0x28423168,		0x2842316C,		0x28423170,		0x28423174,		0x28423178,		0x2842317C},	// Pipeline-1
	{0x28523168,		0x2852316C,		0x28523170,		0x28523174,		0x28523178,		0x2852317C},	// Pipeline-2
	{0x28623168,		0x2862316C,		0x28623170,		0x28623174,		0x28623178,		0x2862317C},	// Pipeline-3
};

// CSPR EDGE Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL S_G_IM_CNR_OTF_CSPR_EDGE_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// CESCLOF_1		CESCLOF_2		CESCLGA_1		CESCLGA_2		CESCLBD_1,		CESCLBD_2
	{0x28421168,		0x2842116C,		0x28421170,		0x28421174,		0x28421178,		0x2842117C},	// Pipeline-1
	{0x28521168,		0x2852116C,		0x28521170,		0x28521174,		0x28521178,		0x2852117C},	// Pipeline-2
	{0x28621168,		0x2862116C,		0x28621170,		0x28621174,		0x28621178,		0x2862117C},	// Pipeline-3
};

// CSPR Hue Specified Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL S_G_IM_CNR_OFL_CSPR_HUE_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// CPHPT		CPHPTK		CDSCLOF_1	CDSCLOF_2	CDSCLOF_3,	CDSCLGA_1	CDSCLGA_2	CDSCLGA_3	CDSCLBD_1	CDSCLBD_2	CDSCLBD_3
	{0x28423190,	0x28423194,	0x284231A0,	0x284231A4,	0x284231A8,	0x284231B0,	0x284231B4,	0x284231B8,	0x284231C0,	0x284231C4,	0x284231C8},	// Pipeline-1
	{0x28523190,	0x28523194,	0x285231A0,	0x285231A4,	0x285231A8,	0x285231B0,	0x285231B4,	0x285231B8,	0x285231C0,	0x285231C4,	0x285231C8},	// Pipeline-2
	{0x28623190,	0x28623194,	0x286231A0,	0x286231A4,	0x286231A8,	0x286231B0,	0x286231B4,	0x286231B8,	0x286231C0,	0x286231C4,	0x286231C8},	// Pipeline-3
};

// CSPR Hue Specified Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL S_G_IM_CNR_OTF_CSPR_HUE_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// CPHPT		CPHPTK		CDSCLOF_1	CDSCLOF_2	CDSCLOF_3,	CDSCLGA_1	CDSCLGA_2	CDSCLGA_3	CDSCLBD_1	CDSCLBD_2	CDSCLBD_3
	{0x28421190,	0x28421194,	0x284211A0,	0x284211A4,	0x284211A8,	0x284211B0,	0x284211B4,	0x284211B8,	0x284211C0,	0x284211C4,	0x284211C8},	// Pipeline-1
	{0x28521190,	0x28521194,	0x285211A0,	0x285211A4,	0x285211A8,	0x285211B0,	0x285211B4,	0x285211B8,	0x285211C0,	0x285211C4,	0x285211C8},	// Pipeline-2
	{0x28621190,	0x28621194,	0x286211A0,	0x286211A4,	0x286211A8,	0x286211B0,	0x286211B4,	0x286211B8,	0x286211C0,	0x286211C4,	0x286211C8},	// Pipeline-3
};

// CSPR SPRS_CC Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL S_G_IM_CNR_OFL_SPRS_CC_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// SPRS,			SPRSCBOF_1		SPRSCBOF_2		SPRSCBGA_1		SPRSCBGA_2		SPRSCBGA_3,		SPRSCBBD_1		SPRSCBBD_2
	// SPRSCROF_1		SPRSCROF_2		SPRSCRGA_1		SPRSCRGA_2		SPRSCRGA_3,		SPRSCRBD_1		SPRSCRBD_2
	// Pipeline-1
	{0x28423200,		0x28423208,		0x2842320C,		0x28423210,		0x28423214,		0x28423218,		0x28423220,		0x28423224,
	 0x28423228,		0x2842322C,		0x28423230,		0x28423234,		0x28423238,		0x28423240,		0x28423244},
	// Pipeline-2
	{0x28523200,		0x28523208,		0x2852320C,		0x28523210,		0x28523214,		0x28523218,		0x28523220,		0x28523224,
	 0x28523228,		0x2852322C,		0x28523230,		0x28523234,		0x28523238,		0x28523240,		0x28523244},
	// Pipeline-3
	{0x28623200,		0x28623208,		0x2862320C,		0x28623210,		0x28623214,		0x28623218,		0x28623220,		0x28623224,
	 0x28623228,		0x2862322C,		0x28623230,		0x28623234,		0x28623238,		0x28623240,		0x28623244},
};

// CSPR SPRS_CC Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL S_G_IM_CNR_OTF_SPRS_CC_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// SPRS,			SPRSCBOF_1		SPRSCBOF_2		SPRSCBGA_1		SPRSCBGA_2		SPRSCBGA_3,		SPRSCBBD_1		SPRSCBBD_2
	// SPRSCROF_1		SPRSCROF_2		SPRSCRGA_1		SPRSCRGA_2		SPRSCRGA_3,		SPRSCRBD_1		SPRSCRBD_2
	// Pipeline-1
	{0x28421200,		0x28421208,		0x2842120C,		0x28421210,		0x28421214,		0x28421218,		0x28421220,		0x28421224,
	 0x28421228,		0x2842122C,		0x28421230,		0x28421234,		0x28421238,		0x28421240,		0x28421244},
	// Pipeline-2
	{0x28521200,		0x28521208,		0x2852120C,		0x28521210,		0x28521214,		0x28521218,		0x28521220,		0x28521224,
	 0x28521228,		0x2852122C,		0x28521230,		0x28521234,		0x28521238,		0x28521240,		0x28521244},
	// Pipeline-3
	{0x28621200,		0x28621208,		0x2862120C,		0x28621210,		0x28621214,		0x28621218,		0x28621220,		0x28621224,
	 0x28621228,		0x2862122C,		0x28621230,		0x28621234,		0x28621238,		0x28621240,		0x28621244},
};

// CSPR SPRD_CC Table address (OFL) ---
const static T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL S_G_IM_CNR_OFL_SPRD_CC_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// SPRD,			SPRDCBOF_1		SPRDCBOF_2		SPRDCBGA_1		SPRDCBGA_2		SPRDCBGA_3,		SPRDCBBD_1		SPRDCBBD_2
	// SPRDCROF_1		SPRDCROF_2		SPRDCRGA_1		SPRDCRGA_2		SPRDCRGA_3,		SPRDCRBD_1		SPRDCRBD_2
	// Pipeline-1
	{0x28423280,		0x28423288,		0x2842328C,		0x28423290,		0x28423294,		0x28423298,		0x284232A0,		0x284232A4,
	 0x284232A8,		0x284232AC,		0x284232B0,		0x284232B4,		0x284232B8,		0x284232C0,		0x284232C4},
	// Pipeline-2
	{0x28523280,		0x28523288,		0x2852328C,		0x28523290,		0x28523294,		0x28523298,		0x285232A0,		0x285232A4,
	 0x285232A8,		0x285232AC,		0x285232B0,		0x285232B4,		0x285232B8,		0x285232C0,		0x285232C4},
	// Pipeline-3
	{0x28623280,		0x28623288,		0x2862328C,		0x28623290,		0x28623294,		0x28623298,		0x286232A0,		0x286232A4,
	 0x286232A8,		0x286232AC,		0x286232B0,		0x286232B4,		0x286232B8,		0x286232C0,		0x286232C4},
};

// CSPR SPRD_CC Table address (OTF) ---
const static T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL S_G_IM_CNR_OTF_SPRD_CC_TBL[D_IM_CNR_CH_NUM_MAX] = {
	// SPRD,			SPRDCBOF_1		SPRDCBOF_2		SPRDCBGA_1		SPRDCBGA_2		SPRDCBGA_3,		SPRDCBBD_1		SPRDCBBD_2
	// SPRDCROF_1		SPRDCROF_2		SPRDCRGA_1		SPRDCRGA_2		SPRDCRGA_3,		SPRDCRBD_1		SPRDCRBD_2
	// Pipeline-1
	{0x28421280,		0x28421288,		0x2842128C,		0x28421290,		0x28421294,		0x28421298,		0x284212A0,		0x284212A4,
	 0x284212A8,		0x284212AC,		0x284212B0,		0x284212B4,		0x284212B8,		0x284212C0,		0x284212C4},
	// Pipeline-2
	{0x28521280,		0x28521288,		0x2852128C,		0x28521290,		0x28521294,		0x28521298,		0x285212A0,		0x285212A4,
	 0x285212A8,		0x285212AC,		0x285212B0,		0x285212B4,		0x285212B8,		0x285212C0,		0x285212C4},
	// Pipeline-3
	{0x28621280,		0x28621288,		0x2862128C,		0x28621290,		0x28621294,		0x28621298,		0x286212A0,		0x286212A4,
	 0x286212A8,		0x286212AC,		0x286212B0,		0x286212B4,		0x286212B8,		0x286212C0,		0x286212C4},
};
#endif

static void im_cnr_get_constructor(ImCnrGet *self)
{
}

static void im_cnr_get_destructor(ImCnrGet *self)
{
}

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// --- Ctrl_C (OFL) ---
/*
CNR(OFL) Get SPR CTRL-C setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_ctrl_c(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CTRL_C** const cnr_ctrl_c, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_ctrl_c() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cnr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_ctrl_c() Parameter(cnr_ctrl_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_ctrl_c() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	*cnr_ctrl_c		= &S_G_IM_CNR_OFL_CTRL_C[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CTRL_C );
	return D_DDIM_OK;
}

// --- Ctrl_C (OTF) ---
/*
CNR(OTF) Get SPR CTRL-C setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_ctrl_c(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CTRL_C** const cnr_ctrl_c, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_ctrl_c() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cnr_ctrl_c == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_ctrl_c() Parameter(cnr_ctrl_c) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_ctrl_c() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	*cnr_ctrl_c		= &S_G_IM_CNR_OTF_CTRL_C[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CTRL_C );
	return D_DDIM_OK;
}

// --- Ctrl_Y (OFL) ---
/*
CNR(OFL) Get SPR CTRL-Y setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_ctrl_y(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_OFL_CTRL_Y** const cnr_ctrl_y, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_ctrl_y() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cnr_ctrl_y == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_ctrl_y() Parameter(cnr_ctrl_y) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_ctrl_y() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cnr_ctrl_y		= &S_G_IM_CNR_OFL_CTRL_Y[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_OFL_CTRL_Y );
	return D_DDIM_OK;
}

// --- YSPR Table (OFL) ---
/*
CNR(OFL) Get YSPR Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_yspr_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_OFL_YSPR_TBL** const cnr_yspr_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_yspr_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cnr_yspr_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_yspr_table() Parameter(cnr_yspr_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_yspr_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cnr_yspr_tbl	= &S_G_IM_CNR_OFL_YSPR_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_OFL_YSPR_TBL );
	return D_DDIM_OK;
}

// --- CSPR Mid-Y Table (OFL) ---
/*
CNR(OFL) Get CSPR Mid_Y Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL** const cspr_mid_y_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_mid_y_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_mid_y_table() Parameter(cspr_mid_y_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_mid_y_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_mid_y_tbl	= &S_G_IM_CNR_OFL_CSPR_MID_Y_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL );
	return D_DDIM_OK;
}

// --- CSPR Mid-Y Table (OTF) ---
/*
CNR(OTF) Get CSPR Mid_Y Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL** const cspr_mid_y_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_mid_y_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_mid_y_table() Parameter(cspr_mid_y_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_mid_y_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_mid_y_tbl	= &S_G_IM_CNR_OTF_CSPR_MID_Y_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL );
	return D_DDIM_OK;
}

// --- CSPR Mid-CC-Y Table (OFL) ---
/*
CNR(OFL) Get CSPR Mid_CC_Y Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_cc_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL** const cspr_mid_cc_y_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_mid_cc_y_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_mid_cc_y_table() Parameter(cspr_mid_cc_y_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_mid_cc_y_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_mid_cc_y_tbl	= &S_G_IM_CNR_OFL_CSPR_MID_CC_Y_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL );
	return D_DDIM_OK;
}

// --- CSPR Mid-CC-Y Table (OTF) ---
/*
CNR(OTF) Get CSPR Mid_CC_Y Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_cc_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL** const cspr_mid_cc_y_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_mid_cc_y_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_mid_cc_y_table() Parameter(cspr_mid_cc_y_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_mid_cc_y_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_mid_cc_y_tbl	= &S_G_IM_CNR_OTF_CSPR_MID_CC_Y_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL );
	return D_DDIM_OK;
}

// --- CSPR Mid-CC-C Table (OFL) ---
/*
CNR(OFL) Get CSPR Mid_CC_C Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_cc_c_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL** const cspr_mid_cc_c_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_mid_cc_c_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table() Parameter(cspr_mid_cc_c_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_mid_cc_c_tbl	= &S_G_IM_CNR_OFL_CSPR_MID_CC_C_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL );
	return D_DDIM_OK;
}

// --- CSPR Mid-CC-C Table (OTF) ---
/*
CNR(OTF) Get CSPR Mid_CC_C Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_cc_c_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL** const cspr_mid_cc_c_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_mid_cc_c_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_mid_cc_c_table() Parameter(cspr_mid_cc_c_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_mid_cc_c_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_mid_cc_c_tbl	= &S_G_IM_CNR_OTF_CSPR_MID_CC_C_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL );
	return D_DDIM_OK;
}

// --- CSPR Low-Y Table (OFL) ---
/*
CNR(OFL) Get CSPR Low_Y Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL** const cspr_low_y_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_low_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_low_y_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_low_y_table() Parameter(cspr_low_y_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_low_y_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_low_y_tbl	= &S_G_IM_CNR_OFL_CSPR_LOW_Y_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL );
	return D_DDIM_OK;
}

// --- CSPR Low-Y Table (OTF) ---
/*
CNR(OTF) Get CSPR Low_Y Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL** const cspr_low_y_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_low_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_low_y_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_low_y_table() Parameter(cspr_low_y_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_low_y_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_low_y_tbl	= &S_G_IM_CNR_OTF_CSPR_LOW_Y_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL );
	return D_DDIM_OK;
}

// --- CSPR Low-CC-Y Table (OFL) ---
/*
CNR(OFL) Get CSPR Low_CC_Y Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_cc_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL** const cspr_low_cc_y_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_low_cc_y_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_low_cc_y_table() Parameter(cspr_low_y_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_low_cc_y_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_low_cc_y_tbl	= &S_G_IM_CNR_OFL_CSPR_LOW_CC_Y_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL );
	return D_DDIM_OK;
}

// --- CSPR Low-CC-Y Table (OTF) ---
/*
CNR(OTF) Get CSPR Low_CC_Y Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_cc_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL** const cspr_low_cc_y_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_low_cc_y_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_low_cc_y_table() Parameter(cspr_low_cc_y_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_low_cc_y_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_low_cc_y_tbl	= &S_G_IM_CNR_OTF_CSPR_LOW_CC_Y_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL );
	return D_DDIM_OK;
}

// --- CSPR Low-CC-C Table (OFL) ---
/*
CNR(OFL) Get CSPR Low_CC_C Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_cc_c_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL** const cspr_low_cc_c_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_low_cc_c_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_low_cc_c_table() Parameter(cspr_low_cc_c_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_low_cc_c_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_low_cc_c_tbl	= &S_G_IM_CNR_OFL_CSPR_LOW_CC_C_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL );
	return D_DDIM_OK;
}

// --- CSPR Low-CC-C Table (OTF) ---
/*
CNR(OTF) Get CSPR Low_CC_C Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_cc_c_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL** const cspr_low_cc_c_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_low_cc_c_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_low_cc_c_table() Parameter(cspr_low_cc_c_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_low_cc_c_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_low_cc_c_tbl	= &S_G_IM_CNR_OTF_CSPR_LOW_CC_C_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL );
	return D_DDIM_OK;
}

// --- CSPR EDGE Table (OFL) ---
/*
CNR(OFL) Get CSPR Edge Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_edge_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL** const cspr_edge_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_edge_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_edge_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_edge_table() Parameter(cspr_edge_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_edge_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_edge_tbl	= &S_G_IM_CNR_OFL_CSPR_EDGE_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL );
	return D_DDIM_OK;
}

// --- CSPR EDGE Table (OTF) ---
/*
CNR(OTF) Get CSPR Edge Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_edge_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL** const cspr_edge_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_edge_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_edge_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_edge_table() Parameter(cspr_edge_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_edge_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_edge_tbl	= &S_G_IM_CNR_OTF_CSPR_EDGE_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL );
	return D_DDIM_OK;
}

// --- CSPR Hue Specified Table (OFL) ---
/*
CNR(OFL) Get CSPR Hue Specified Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_hue_spec_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL** const cspr_hue_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_hue_spec_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_hue_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_hue_spec_table() Parameter(cspr_hue_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_hue_spec_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_hue_tbl	= &S_G_IM_CNR_OFL_CSPR_HUE_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL );
	return D_DDIM_OK;
}

// --- CSPR Hue Specified Table (OTF) ---
/*
CNR(OTF) Get CSPR Hue Specified Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_hue_spec_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL** const cspr_hue_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_hue_spec_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_hue_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_hue_spec_table() Parameter(cspr_hue_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_hue_spec_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_hue_tbl	= &S_G_IM_CNR_OTF_CSPR_HUE_TBL[ch];
	*size			= sizeof( T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL );
	return D_DDIM_OK;
}

// --- CSPR SPRS_CC Table (OFL) ---
/*
CNR(OFL) Get CSPR SPRS_CC Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_sprs_cc_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL** const cspr_sprs_cc_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_sprs_cc_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_sprs_cc_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_sprs_cc_table() Parameter(cspr_sprs_cc_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_sprs_cc_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_sprs_cc_tbl	= &S_G_IM_CNR_OFL_SPRS_CC_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL );
	return D_DDIM_OK;
}

// --- CSPR SPRS_CC Table (OTF) ---
/*
CNR(OTF) Get CSPR SPRS_CC Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_sprs_cc_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL** const cspr_sprs_cc_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_sprs_cc_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_sprs_cc_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_sprs_cc_table() Parameter(cspr_sprs_cc_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_sprs_cc_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_sprs_cc_tbl	= &S_G_IM_CNR_OTF_SPRS_CC_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL );
	return D_DDIM_OK;
}

// --- CSPR SPRD_CC Table (OFL) ---
/*
CNR(OFL) Get CSPR SPRD_CC Table setting address information
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_sprd_cc_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL** const cspr_sprd_cc_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_ofl_cspr_sprd_cc_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_sprd_cc_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_sprd_cc_table() Parameter(cspr_sprd_cc_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_ofl_cspr_sprd_cc_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_sprd_cc_tbl	= &S_G_IM_CNR_OFL_SPRD_CC_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL );
	return D_DDIM_OK;
}

// --- CSPR SPRD_CC Table (OTF) ---
/*
CNR(OTF) Get CSPR SPRD_CC Table setting address information
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_sprd_cc_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL** const cspr_sprd_cc_tbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnr_get_rdma_addr_otf_cspr_sprd_cc_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( cspr_sprd_cc_tbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_sprd_cc_table() Parameter(cspr_sprd_cc_tbl) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnr_get_rdma_addr_otf_cspr_sprd_cc_table() Parameter(size) is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cspr_sprd_cc_tbl	= &S_G_IM_CNR_OTF_SPRD_CC_TBL[ch];
	*size				= sizeof( T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL );
	return D_DDIM_OK;
}

#endif

ImCnrGet *im_cnr_get_new(void)
{
	ImCnrGet* self = k_object_new_with_private(IM_TYPE_CNR_GET,sizeof(ImCnrGetPrivate));
	return self;
}
