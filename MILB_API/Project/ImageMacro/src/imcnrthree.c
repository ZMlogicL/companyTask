/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#include "imcnr.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdscnr.h"
// for memset
#include <string.h>
#include "imcnrone.h"
#include "imcnrthree.h"


G_DEFINE_TYPE(ImCnrthree, im_cnrthree, G_TYPE_OBJECT);
#define IM_CNRTHREE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_CNRTHREE, ImCnrthreePrivate));


struct _ImCnrthreePrivate{

};


/*DECLS*/
static void 					dispose_od(GObject *object);
static void 					finalize_od(GObject *object);


/*IMPL*/
static void im_cnrthree_class_init(ImCnrthreeClass *klass)
{
	g_type_class_add_private(klass, sizeof(ImCnrthreePrivate));
}

static void im_cnrthree_init(ImCnrthree *self)
{
	ImCnrthreePrivate *priv = IM_CNRTHREE_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImCnrthreePrivate *self = IM_CNRTHREE_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImCnrthreePrivate *self = IM_CNRTHREE_GET_PRIVATE(object);
}

#ifdef CO_DDIM_UTILITY_USE

// SPR setting for CbCr address (OFL)
const static ImCnrRdmaAddrCtrlC S_IM_CNRTHREE_OFL_CTRL_C[ImCnr_CH_NUM_MAX] = {
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
const static ImCnrRdmaAddrCtrlC S_IM_CNRTHREE_OTF_CTRL_C[ImCnr_CH_NUM_MAX] = {
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
const static ImCnrRdmaAddrOflCtrlY S_IM_CNRTHREE_OFL_CTRL_Y[ImCnr_CH_NUM_MAX] = {
	// YSPREN			YSPRMODE		YSPRFXEY		YSPRFXEC		YSPRALPBD
	{0x28424000,		0x28424004,		0x28424020,		0x28424024,		0x28424028},	// Pipeline-1
	{0x28524000,		0x28524004,		0x28524020,		0x28524024,		0x28524028},	// Pipeline-2
	{0x28624000,		0x28624004,		0x28624020,		0x28624024,		0x28624028},	// Pipeline-3
};

// YSPR Table address (OFL) ---
const static ImCnrRdmaAddrOflYsprTbl S_IM_CNRTHREE_OFL_YSPR_TBL[ImCnr_CH_NUM_MAX] = {
	// YSPRDYEYOF_1		YSPRDYEYOF_2	YSPRDYEYGA_1	YSPRDYEYGA_2	YSPRDYEYBD_1	YSPRDYEYBD_2
	{0x28424030,		0x28424034,		0x28424038,		0x2842403C,		0x28424040,		0x28424044},	// Pipeline-1
	{0x28524030,		0x28524034,		0x28524038,		0x2852403C,		0x28524040,		0x28524044},	// Pipeline-2
	{0x28624030,		0x28624034,		0x28624038,		0x2862403C,		0x28624040,		0x28624044},	// Pipeline-3
};

// CSPR Mid-Y Table address (OFL) ---
const static ImCnrRdmaAddrCsprMidYTbl S_IM_CNRTHREE_OFL_CSPR_MID_Y_TBL[ImCnr_CH_NUM_MAX] = {
	// MCYSCLOF_1		MCYSCLOF_2		MCYSCLGA_1		MCYSCLGA_2		MCYSCLBD_1,		MCYSCLBD_2
	{0x28423048,		0x2842304C,		0x28423050,		0x28423054,		0x28423058,		0x2842305C},	// Pipeline-1
	{0x28523048,		0x2852304C,		0x28523050,		0x28523054,		0x28523058,		0x2852305C},	// Pipeline-2
	{0x28623048,		0x2862304C,		0x28623050,		0x28623054,		0x28623058,		0x2862305C},	// Pipeline-3
};

// CSPR Mid-Y Table address (OTF) ---
const static ImCnrRdmaAddrCsprMidYTbl S_IM_CNRTHREE_OTF_CSPR_MID_Y_TBL[ImCnr_CH_NUM_MAX] = {
	// MCYSCLOF_1		MCYSCLOF_2		MCYSCLGA_1		MCYSCLGA_2		MCYSCLBD_1,		MCYSCLBD_2
	{0x28421048,		0x2842104C,		0x28421050,		0x28421054,		0x28421058,		0x2842105C},	// Pipeline-1
	{0x28521048,		0x2852104C,		0x28521050,		0x28521054,		0x28521058,		0x2852105C},	// Pipeline-2
	{0x28621048,		0x2862104C,		0x28621050,		0x28621054,		0x28621058,		0x2862105C},	// Pipeline-3
};

// CSPR Mid-CC-Y Table address (OFL) ---
const static ImCnrRdmaAddrCsprMidCcYTbl S_IM_CNRTHREE_OFL_CSPR_MID_CC_Y_TBL[ImCnr_CH_NUM_MAX] = {
	// MCCSCLOF_1		MCCSCLOF_2		MCCSCLGA_1		MCCSCLGA_2		MCCSCLBD_1,		MCCSCLBD_2
	{0x28423068,		0x2842306C,		0x28423070,		0x28423074,		0x28423078,		0x2842307C},	// Pipeline-1
	{0x28523068,		0x2852306C,		0x28523070,		0x28523074,		0x28523078,		0x2852307C},	// Pipeline-2
	{0x28623068,		0x2862306C,		0x28623070,		0x28623074,		0x28623078,		0x2862307C},	// Pipeline-3
};

// CSPR Mid-CC-Y Table address (OTF) ---
const static ImCnrRdmaAddrCsprMidCcYTbl S_IM_CNRTHREE_OTF_CSPR_MID_CC_Y_TBL[ImCnr_CH_NUM_MAX] = {
	{0x28421068,		0x2842106C,		0x28421070,		0x28421074,		0x28421078,		0x2842107C},	// Pipeline-1
	{0x28521068,		0x2852106C,		0x28521070,		0x28521074,		0x28521078,		0x2852107C},	// Pipeline-2
	{0x28621068,		0x2862106C,		0x28621070,		0x28621074,		0x28621078,		0x2862107C},	// Pipeline-3
};

// CSPR Mid-CC-C Table address (OFL) ---
const static ImCnrRdmaAddrCsprMidCcCTbl S_IM_CNRTHREE_OFL_CSPR_MID_CC_C_TBL[ImCnr_CH_NUM_MAX] = {
	// MCSSCLOF_1		MCSSCLOF_2		MCSSCLGA_1		MCSSCLGA_2		MCSSCLBD_1,		MCSSCLBD_1
	{0x28423088,		0x2842308C,		0x28423090,		0x28423094,		0x28423098,		0x2842309C},	// Pipeline-1
	{0x28523088,		0x2852308C,		0x28523090,		0x28523094,		0x28523098,		0x2852309C},	// Pipeline-2
	{0x28623088,		0x2862308C,		0x28623090,		0x28623094,		0x28623098,		0x2862309C},	// Pipeline-3
};

// CSPR Mid-CC-C Table address (OTF) ---
const static ImCnrRdmaAddrCsprMidCcCTbl S_IM_CNRTHREE_OTF_CSPR_MID_CC_C_TBL[ImCnr_CH_NUM_MAX] = {
	// MCSSCLOF_1		MCSSCLOF_2		MCSSCLGA_1		MCSSCLGA_2		MCSSCLBD_1,		MCSSCLBD_1
	{0x28421088,		0x2842108C,		0x28421090,		0x28421094,		0x28421098,		0x2842109C},	// Pipeline-1
	{0x28521088,		0x2852108C,		0x28521090,		0x28521094,		0x28521098,		0x2852109C},	// Pipeline-2
	{0x28621088,		0x2862108C,		0x28621090,		0x28621094,		0x28621098,		0x2862109C},	// Pipeline-3
};

// CSPR Low-Y Table address (OFL) ---
const static ImCnrRdmaAddrCsprLowYTbl S_IM_CNRTHREE_OFL_CSPR_LOW_Y_TBL[ImCnr_CH_NUM_MAX] = {
	// LCYSCLOF_1		LCYSCLOF_2		LCYSCLGA_1		LCYSCLGA_2		LCYSCLBD_1,		LCYSCLBD_2
	{0x284230E8,		0x284230EC,		0x284230F0,		0x284230F4,		0x284230F8,		0x284230FC},	// Pipeline-1
	{0x285230E8,		0x285230EC,		0x285230F0,		0x285230F4,		0x285230F8,		0x285230FC},	// Pipeline-2
	{0x286230E8,		0x286230EC,		0x286230F0,		0x286230F4,		0x286230F8,		0x286230FC},	// Pipeline-3
};

// CSPR Low-Y Table address (OTF) ---
const static ImCnrRdmaAddrCsprLowYTbl S_IM_CNRTHREE_OTF_CSPR_LOW_Y_TBL[ImCnr_CH_NUM_MAX] = {
	// LCYSCLOF_1		LCYSCLOF_2		LCYSCLGA_1		LCYSCLGA_2		LCYSCLBD_1,		LCYSCLBD_2
	{0x284210E8,		0x284210EC,		0x284210F0,		0x284210F4,		0x284210F8,		0x284210FC},	// Pipeline-1
	{0x285210E8,		0x285210EC,		0x285210F0,		0x285210F4,		0x285210F8,		0x285210FC},	// Pipeline-2
	{0x286210E8,		0x286210EC,		0x286210F0,		0x286210F4,		0x286210F8,		0x286210FC},	// Pipeline-3
};

// CSPR Low-CC-Y Table address (OFL) ---
const static ImCnrRdmaAddrCsprLowCcYTbl S_IM_CNRTHREE_OFL_CSPR_LOW_CC_Y_TBL[ImCnr_CH_NUM_MAX] = {
	// LCCSCLOF_1		LCCSCLOF_2		LCCSCLGA_1		LCCSCLGA_2		LCCSCLBD_1,		LCCSCLBD_2
	{0x28423108,		0x2842310C,		0x28423110,		0x28423114,		0x28423118,		0x2842311C},	// Pipeline-1
	{0x28523108,		0x2852310C,		0x28523110,		0x28523114,		0x28523118,		0x2852311C},	// Pipeline-2
	{0x28623108,		0x2862310C,		0x28623110,		0x28623114,		0x28623118,		0x2862311C},	// Pipeline-3
};

// CSPR Low-CC-Y Table address (OTF) ---
const static ImCnrRdmaAddrCsprLowCcYTbl S_IM_CNRTHREE_OTF_CSPR_LOW_CC_Y_TBL[ImCnr_CH_NUM_MAX] = {
	// LCCSCLOF_1		LCCSCLOF_2		LCCSCLGA_1		LCCSCLGA_2		LCCSCLBD_1,		LCCSCLBD_2
	{0x28421108,		0x2842110C,		0x28421110,		0x28421114,		0x28421118,		0x2842111C},	// Pipeline-1
	{0x28521108,		0x2852110C,		0x28521110,		0x28521114,		0x28521118,		0x2852111C},	// Pipeline-2
	{0x28621108,		0x2862110C,		0x28621110,		0x28621114,		0x28621118,		0x2862111C},	// Pipeline-3
};

// CSPR Low-CC-C Table address (OFL) ---
const static ImCnroneRdmaAddrCsprLowCcCTbl S_IM_CNRTHREE_OFL_CSPR_LOW_CC_C_TBL[ImCnr_CH_NUM_MAX] = {
	// LCSSCLOF_1		LCSSCLOF_2		LCSSCLGA_1		LCSSCLGA_2		LCSSCLBD_1,		LCSSCLBD_2
	{0x28423128,		0x2842312C,		0x28423130,		0x28423134,		0x28423138,		0x2842313C},	// Pipeline-1
	{0x28523128,		0x2852312C,		0x28523130,		0x28523134,		0x28523138,		0x2852313C},	// Pipeline-2
	{0x28623128,		0x2862312C,		0x28623130,		0x28623134,		0x28623138,		0x2862313C},	// Pipeline-3
};

// CSPR Low-CC-C Table address (OTF) ---
const static ImCnroneRdmaAddrCsprLowCcCTbl S_IM_CNRTHREE_OTF_CSPR_LOW_CC_C_TBL[ImCnr_CH_NUM_MAX] = {
	// LCSSCLOF_1		LCSSCLOF_2		LCSSCLGA_1		LCSSCLGA_2		LCSSCLBD_1,		LCSSCLBD_2
	{0x28421128,		0x2842112C,		0x28421130,		0x28421134,		0x28421138,		0x2842113C},	// Pipeline-1
	{0x28521128,		0x2852112C,		0x28521130,		0x28521134,		0x28521138,		0x2852113C},	// Pipeline-2
	{0x28621128,		0x2862112C,		0x28621130,		0x28621134,		0x28621138,		0x2862113C},	// Pipeline-3
};

// CSPR EDGE Table address (OFL) ---
const static ImCnroneRdmaAddrCsprEdgeTbl S_IM_CNRTHREE_OFL_CSPR_EDGE_TBL[ImCnr_CH_NUM_MAX] = {
	// CESCLOF_1		CESCLOF_2		CESCLGA_1		CESCLGA_2		CESCLBD_1,		CESCLBD_2
	{0x28423168,		0x2842316C,		0x28423170,		0x28423174,		0x28423178,		0x2842317C},	// Pipeline-1
	{0x28523168,		0x2852316C,		0x28523170,		0x28523174,		0x28523178,		0x2852317C},	// Pipeline-2
	{0x28623168,		0x2862316C,		0x28623170,		0x28623174,		0x28623178,		0x2862317C},	// Pipeline-3
};

// CSPR EDGE Table address (OTF) ---
const static ImCnroneRdmaAddrCsprEdgeTbl S_IM_CNRTHREE_OTF_CSPR_EDGE_TBL[ImCnr_CH_NUM_MAX] = {
	// CESCLOF_1		CESCLOF_2		CESCLGA_1		CESCLGA_2		CESCLBD_1,		CESCLBD_2
	{0x28421168,		0x2842116C,		0x28421170,		0x28421174,		0x28421178,		0x2842117C},	// Pipeline-1
	{0x28521168,		0x2852116C,		0x28521170,		0x28521174,		0x28521178,		0x2852117C},	// Pipeline-2
	{0x28621168,		0x2862116C,		0x28621170,		0x28621174,		0x28621178,		0x2862117C},	// Pipeline-3
};

// CSPR Hue Specified Table address (OFL) ---
const static ImCnroneRdmaAddrCsprHueTbl S_IM_CNRTHREE_OFL_CSPR_HUE_TBL[ImCnr_CH_NUM_MAX] = {
	// CPHPT		CPHPTK		CDSCLOF_1	CDSCLOF_2	CDSCLOF_3,	CDSCLGA_1	CDSCLGA_2	CDSCLGA_3	CDSCLBD_1	CDSCLBD_2	CDSCLBD_3
	{0x28423190,	0x28423194,	0x284231A0,	0x284231A4,	0x284231A8,	0x284231B0,	0x284231B4,	0x284231B8,	0x284231C0,	0x284231C4,	0x284231C8},	// Pipeline-1
	{0x28523190,	0x28523194,	0x285231A0,	0x285231A4,	0x285231A8,	0x285231B0,	0x285231B4,	0x285231B8,	0x285231C0,	0x285231C4,	0x285231C8},	// Pipeline-2
	{0x28623190,	0x28623194,	0x286231A0,	0x286231A4,	0x286231A8,	0x286231B0,	0x286231B4,	0x286231B8,	0x286231C0,	0x286231C4,	0x286231C8},	// Pipeline-3
};

#endif

#ifdef CO_CNR_DEBUG
VOID im_cnrthree_print_clockstatus( ImCnrthree *self )
{
#ifdef CO_ACT_CNR_PCLK
	Ddim_Print(( "CLKSTOP: AP1=%u\n", Dd_Top_Get_CLKSTOP11_CNR1AP() ));
	Ddim_Print(( "CLKSTOP: AP2=%u\n", Dd_Top_Get_CLKSTOP13_CNR2AP() ));
#endif
#ifdef CO_ACT_CNR_ICLK
	Ddim_Print(( "CLKSTOP: AX1=%u\n", Dd_Top_Get_CLKSTOP11_CNR1AX() ));
	Ddim_Print(( "CLKSTOP: AX2=%u\n", Dd_Top_Get_CLKSTOP13_CNR2AX() ));
#endif
#ifdef CO_ACT_CNRCLK
	Ddim_Print(( "CLKSTOP: CK1=%u\n", Dd_Top_Get_CLKSTOP11_CNR1CK() ));
	Ddim_Print(( "CLKSTOP: CK2=%u\n", Dd_Top_Get_CLKSTOP13_CNR2CK() ));
#endif
#ifdef CO_ACT_CNR_PCLK
	Ddim_Print(( "CLKCNT: AP1=%u\n", S_IM_CNR_PCLK_CTRL_CNT1 ));
	Ddim_Print(( "CLKCNT: AP2=%u\n", S_IM_CNR_PCLK_CTRL_CNT2 ));
#endif
#ifdef CO_ACT_CNR_ICLK
	Ddim_Print(( "CLKCNT: AX1=%u\n", S_IM_CNR_ICLK_CTRL_CNT1 ));
	Ddim_Print(( "CLKCNT: AX2=%u\n", S_IM_CNR_ICLK_CTRL_CNT2 ));
#endif
#ifdef CO_ACT_CO_ACT_CNR_CLK
	Ddim_Print(( "CLKCNT: CK1=%u\n", S_IM_CNR_CLK_CTRL_CNT1 ));
	Ddim_Print(( "CLKCNT: CK2=%u\n", S_IM_CNR_CLK_CTRL_CNT2 ));
#endif
}
#endif


/*PUBLIC*/
/* Get Latest Address information
 */
INT32 im_cnrthree_otf_get_latest_outaddr(ImCnrthree *self, UCHAR ch, ULONG* const latestAddr )
{
#ifdef CO_PARAM_CHECK
	if( latestAddr == NULL ) {
		Ddim_Assertion(("im_cnrthree_otf_get_latest_outaddr() error. latestAddr = NULL\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( ch >= ImCnr_CH_READ_NUM_MAX ){
		Ddim_Assertion(( "im_cnrthree_otf_get_latest_outaddr() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*latestAddr     = S_IM_CNR_LATEST_MNG[ch].addr;

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
/*
CNR(OFL) Get SPR CTRL-C setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_ctrl_c(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCtrlC** const cnrCtrlC, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_ctrl_c() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( cnrCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_ctrl_c() Parameter(cnrCtrlC) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_ctrl_c() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cnrCtrlC		= &S_IM_CNRTHREE_OFL_CTRL_C[ch];
	*size			= sizeof( ImCnrRdmaAddrCtrlC );

	return D_DDIM_OK;
}

// --- Ctrl_C (OTF) ---
/*
CNR(OTF) Get SPR CTRL-C setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_otf_ctrl_c(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCtrlC** const cnrCtrlC, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_otf_ctrl_c() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( cnrCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_ctrl_c() Parameter(cnrCtrlC) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_ctrl_c() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cnrCtrlC		= &S_IM_CNRTHREE_OTF_CTRL_C[ch];
	*size			= sizeof( ImCnrRdmaAddrCtrlC );

	return D_DDIM_OK;
}

// --- Ctrl_Y (OFL) ---
/*
CNR(OFL) Get SPR CTRL-Y setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_ctrl_y(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrOflCtrlY** const cnrCtrlY, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_ctrl_y() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( cnrCtrlY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_ctrl_y() Parameter(cnrCtrlY) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_ctrl_y() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cnrCtrlY		= &S_IM_CNRTHREE_OFL_CTRL_Y[ch];
	*size			= sizeof( ImCnrRdmaAddrOflCtrlY );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set SPR CTRL-Y setting parameter information
*/
INT32 im_cnrthree_set_rdmavalue_ofl_ctrl_y(ImCnrthree *self, const ImCnrOflCtrlY* const sprCtrlY,
		ImCnrRdmaDataOflCtrlY* const rdmaCtrlY )
{
#ifdef CO_PARAM_CHECK
	if( sprCtrlY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_set_rdmavalue_ofl_ctrl_y() Parameter(sprCtrlY) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCtrlY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_set_rdmavalue_ofl_ctrl_y() Parameter(rdmaCtrlY) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCtrlY, 0, sizeof(ImCnrRdmaDataOflCtrlY) );

	rdmaCtrlY->YSPREN.bit.YSPREN			= sprCtrlY->enable;
	rdmaCtrlY->YSPRMODE.bit.YSPRMD		= sprCtrlY->thresholdType;
	rdmaCtrlY->YSPRMODE.bit.YSPRFE		= sprCtrlY->level;

	rdmaCtrlY->YSPRFXEY.bit.YSPRFXEYV		= sprCtrlY->vYThreshold;
	rdmaCtrlY->YSPRFXEY.bit.YSPRFXEYH		= sprCtrlY->hYThreshold;
	rdmaCtrlY->YSPRFXEC.bit.YSPRFXECV		= sprCtrlY->vCThreshold;
	rdmaCtrlY->YSPRFXEC.bit.YSPRFXECH		= sprCtrlY->hCThreshold;
	rdmaCtrlY->YSPRALPBD.bit.YSPRALPBD	= sprCtrlY->alphaBlendRatio;

	return D_DDIM_OK;
}

// --- YSPR Table (OFL) ---
/*
CNR(OFL) Get YSPR Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_yspr_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrOflYsprTbl** const cnrYsprTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_yspr_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( cnrYsprTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_yspr_table() Parameter(cnrYsprTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_yspr_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*cnrYsprTbl	= &S_IM_CNRTHREE_OFL_YSPR_TBL[ch];
	*size			= sizeof( ImCnrRdmaAddrOflYsprTbl );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set YSPR Table setting parameter information
*/
INT32 im_cnrthree_set_rdmavalue_ofl_yspr_table(ImCnrthree *self, const ImCnrTable* const ysprTable,
		ImCnrRdmaDataOflYsprTbl* const rdmaYsprTable )
{
#ifdef CO_PARAM_CHECK
	if( ysprTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_set_rdmavalue_ofl_yspr_table() Parameter(ysprTable) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaYsprTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_set_rdmavalue_ofl_yspr_table() Parameter(rdmaYsprTable) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaYsprTable, 0, sizeof(ImCnrRdmaDataOflYsprTbl) );
	rdmaYsprTable->YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_1	= ysprTable->bd1;
	rdmaYsprTable->YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_2	= ysprTable->bd2;
	rdmaYsprTable->YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_3	= ysprTable->bd3;
	rdmaYsprTable->YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_4	= ysprTable->bd4;
	rdmaYsprTable->YSPRDYEYBD.YSPRDYEYBD2.bit.YSPRDYEYBD_5	= ysprTable->bd5;
	rdmaYsprTable->YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_0	= ysprTable->of0;
	rdmaYsprTable->YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_1	= ysprTable->of1;
	rdmaYsprTable->YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_2	= ysprTable->of2;
	rdmaYsprTable->YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_3	= ysprTable->of3;
	rdmaYsprTable->YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_4	= ysprTable->of4;
	rdmaYsprTable->YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_5	= ysprTable->of5;
	// write signed data
	ImCnr_SET_REG_SIGNED( rdmaYsprTable->YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_0, ysprTable->gain0 );
	ImCnr_SET_REG_SIGNED( rdmaYsprTable->YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_1, ysprTable->gain1 );
	ImCnr_SET_REG_SIGNED( rdmaYsprTable->YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_2, ysprTable->gain2 );
	ImCnr_SET_REG_SIGNED( rdmaYsprTable->YSPRDYEYGA.YSPRDYEYGA1, union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_3, ysprTable->gain3 );
	ImCnr_SET_REG_SIGNED( rdmaYsprTable->YSPRDYEYGA.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_4, ysprTable->gain4 );
	ImCnr_SET_REG_SIGNED( rdmaYsprTable->YSPRDYEYGA.YSPRDYEYGA2, union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_5, ysprTable->gain5 );

	return D_DDIM_OK;
}

// --- CSPR Mid-Y Table (OFL) ---
/*
CNR(OFL) Get CSPR Mid_Y Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_mid_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidYTbl** const csprMidYTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprMidYTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_mid_y_table() Parameter(csprMidYTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_mid_y_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprMidYTbl	= &S_IM_CNRTHREE_OFL_CSPR_MID_Y_TBL[ch];
	*size			= sizeof( ImCnrRdmaAddrCsprMidYTbl );

	return D_DDIM_OK;
}

// --- CSPR Mid-Y Table (OTF) ---
/*
CNR(OTF) Get CSPR Mid_Y Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_otf_cspr_mid_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidYTbl** const csprMidYTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_otf_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprMidYTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_mid_y_table() Parameter(csprMidYTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_mid_y_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprMidYTbl	= &S_IM_CNRTHREE_OTF_CSPR_MID_Y_TBL[ch];
	*size			= sizeof( ImCnrRdmaAddrCsprMidYTbl );

	return D_DDIM_OK;
}

// --- CSPR Mid-CC-Y Table (OFL) ---
/*
CNR(OFL) Get CSPR Mid_CC_Y Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidCcYTbl** const csprMidCcYTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprMidCcYTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_y_table() Parameter(csprMidCcYTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_y_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprMidCcYTbl	= &S_IM_CNRTHREE_OFL_CSPR_MID_CC_Y_TBL[ch];
	*size				= sizeof( ImCnrRdmaAddrCsprMidCcYTbl );

	return D_DDIM_OK;
}

// --- CSPR Mid-CC-Y Table (OTF) ---
/*
CNR(OTF) Get CSPR Mid_CC_Y Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidCcYTbl** const csprMidCcYTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprMidCcYTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_y_table() Parameter(csprMidCcYTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_y_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprMidCcYTbl	= &S_IM_CNRTHREE_OTF_CSPR_MID_CC_Y_TBL[ch];
	*size				= sizeof( ImCnrRdmaAddrCsprMidCcYTbl );

	return D_DDIM_OK;
}

// --- CSPR Mid-CC-C Table (OFL) ---
/*
CNR(OFL) Get CSPR Mid_CC_C Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_c_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidCcCTbl** const csprMidCcCTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprMidCcCTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_c_table() Parameter(csprMidCcCTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_c_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprMidCcCTbl	= &S_IM_CNRTHREE_OFL_CSPR_MID_CC_C_TBL[ch];
	*size				= sizeof( ImCnrRdmaAddrCsprMidCcCTbl );

	return D_DDIM_OK;
}

// --- CSPR Mid-CC-C Table (OTF) ---
/*
CNR(OTF) Get CSPR Mid_CC_C Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_c_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidCcCTbl** const csprMidCcCTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprMidCcCTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_c_table() Parameter(csprMidCcCTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_c_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprMidCcCTbl	= &S_IM_CNRTHREE_OTF_CSPR_MID_CC_C_TBL[ch];
	*size				= sizeof( ImCnrRdmaAddrCsprMidCcCTbl );

	return D_DDIM_OK;
}

// --- CSPR Low-Y Table (OFL) ---
/*
CNR(OFL) Get CSPR Low_Y Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_low_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprLowYTbl** const csprLowYTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_cspr_low_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprLowYTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_low_y_table() Parameter(csprLowYTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_low_y_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprLowYTbl	= &S_IM_CNRTHREE_OFL_CSPR_LOW_Y_TBL[ch];
	*size			= sizeof( ImCnrRdmaAddrCsprLowYTbl );

	return D_DDIM_OK;
}

// --- CSPR Low-Y Table (OTF) ---
/*
CNR(OTF) Get CSPR Low_Y Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_otf_cspr_low_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprLowYTbl** const csprLowYTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_otf_cspr_low_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprLowYTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_low_y_table() Parameter(csprLowYTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_low_y_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprLowYTbl	= &S_IM_CNRTHREE_OTF_CSPR_LOW_Y_TBL[ch];
	*size			= sizeof( ImCnrRdmaAddrCsprLowYTbl );

	return D_DDIM_OK;
}

// --- CSPR Low-CC-Y Table (OFL) ---
/*
CNR(OFL) Get CSPR Low_CC_Y Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprLowCcYTbl** const csprLowCcYTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprLowCcYTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_y_table() Parameter(csprLowYTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_y_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprLowCcYTbl	= &S_IM_CNRTHREE_OFL_CSPR_LOW_CC_Y_TBL[ch];
	*size				= sizeof( ImCnrRdmaAddrCsprLowCcYTbl );

	return D_DDIM_OK;
}

// --- CSPR Low-CC-Y Table (OTF) ---
/*
CNR(OTF) Get CSPR Low_CC_Y Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprLowCcYTbl** const csprLowCcYTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprLowCcYTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_y_table() Parameter(csprLowCcYTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_y_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprLowCcYTbl	= &S_IM_CNRTHREE_OTF_CSPR_LOW_CC_Y_TBL[ch];
	*size				= sizeof( ImCnrRdmaAddrCsprLowCcYTbl );

	return D_DDIM_OK;
}

// --- CSPR Low-CC-C Table (OFL) ---
/*
CNR(OFL) Get CSPR Low_CC_C Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_c_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprLowCcCTbl** const csprLowCcCTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprLowCcCTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_c_table() Parameter(csprLowCcCTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_c_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprLowCcCTbl	= &S_IM_CNRTHREE_OFL_CSPR_LOW_CC_C_TBL[ch];
	*size				= sizeof( ImCnroneRdmaAddrCsprLowCcCTbl );

	return D_DDIM_OK;
}

// --- CSPR Low-CC-C Table (OTF) ---
/*
CNR(OTF) Get CSPR Low_CC_C Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_c_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprLowCcCTbl** const csprLowCcCTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_c_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprLowCcCTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_c_table() Parameter(csprLowCcCTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_c_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprLowCcCTbl	= &S_IM_CNRTHREE_OTF_CSPR_LOW_CC_C_TBL[ch];
	*size				= sizeof( ImCnroneRdmaAddrCsprLowCcCTbl );

	return D_DDIM_OK;
}

// --- CSPR EDGE Table (OFL) ---
/*
CNR(OFL) Get CSPR Edge Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_edge_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprEdgeTbl** const csprEdgeTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_cspr_edge_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprEdgeTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_edge_table() Parameter(csprEdgeTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_edge_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprEdgeTbl	= &S_IM_CNRTHREE_OFL_CSPR_EDGE_TBL[ch];
	*size			= sizeof( ImCnroneRdmaAddrCsprEdgeTbl );

	return D_DDIM_OK;
}

// --- CSPR EDGE Table (OTF) ---
/*
CNR(OTF) Get CSPR Edge Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_otf_cspr_edge_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprEdgeTbl** const csprEdgeTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_otf_cspr_edge_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprEdgeTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_edge_table() Parameter(csprEdgeTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_otf_cspr_edge_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprEdgeTbl	= &S_IM_CNRTHREE_OTF_CSPR_EDGE_TBL[ch];
	*size			= sizeof( ImCnroneRdmaAddrCsprEdgeTbl );

	return D_DDIM_OK;
}

// --- CSPR Hue Specified Table (OFL) ---
/*
CNR(OFL) Get CSPR Hue Specified Table setting address information
*/
INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_hue_spec_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprHueTbl** const csprHueTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrthree_get_rdmaaddr_ofl_cspr_hue_spec_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprHueTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_hue_spec_table() Parameter(csprHueTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrthree_get_rdmaaddr_ofl_cspr_hue_spec_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprHueTbl	= &S_IM_CNRTHREE_OFL_CSPR_HUE_TBL[ch];
	*size			= sizeof( ImCnroneRdmaAddrCsprHueTbl );

	return D_DDIM_OK;
}


#endif

ImCnrthree* im_cnrthree_new(void)
{
	ImCnrthree *self = g_object_new(IM_TYPE_CNRTHREE, NULL);
	return self;
}
















