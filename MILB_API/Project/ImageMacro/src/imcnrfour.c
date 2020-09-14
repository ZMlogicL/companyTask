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
#include "imcnrfive.h"
#include "imcnrfour.h"


G_DEFINE_TYPE(ImCnrfour, im_cnrfour, G_TYPE_OBJECT);
#define IM_CNRFOUR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_CNRFOUR, ImCnrfourPrivate));


struct _ImCnrfourPrivate{

};


#ifdef CO_DDIM_UTILITY_USE
// CSPR Hue Specified Table address (OTF) ---
const static ImCnroneRdmaAddrCsprHueTbl S_IM_CNRTHREE_OTF_CSPR_HUE_TBL[ImCnr_CH_NUM_MAX] = {
	// CPHPT		CPHPTK		CDSCLOF_1	CDSCLOF_2	CDSCLOF_3,	CDSCLGA_1	CDSCLGA_2	CDSCLGA_3	CDSCLBD_1	CDSCLBD_2	CDSCLBD_3
	{0x28421190,	0x28421194,	0x284211A0,	0x284211A4,	0x284211A8,	0x284211B0,	0x284211B4,	0x284211B8,	0x284211C0,	0x284211C4,	0x284211C8},	// Pipeline-1
	{0x28521190,	0x28521194,	0x285211A0,	0x285211A4,	0x285211A8,	0x285211B0,	0x285211B4,	0x285211B8,	0x285211C0,	0x285211C4,	0x285211C8},	// Pipeline-2
	{0x28621190,	0x28621194,	0x286211A0,	0x286211A4,	0x286211A8,	0x286211B0,	0x286211B4,	0x286211B8,	0x286211C0,	0x286211C4,	0x286211C8},	// Pipeline-3
};

// CSPR SPRD_CC Table address (OTF) ---
const static ImCnroneRdmaAddrSprdCcTbl S_IM_CNRTHREE_OTF_SPRD_CC_TBL[ImCnr_CH_NUM_MAX] = {
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

// CSPR SPRS_CC Table address (OFL) ---
const static ImCnroneRdmaAddrSprsCcTbl S_IM_CNRTHREE_OFL_SPRS_CC_TBL[ImCnr_CH_NUM_MAX] = {
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
const static ImCnroneRdmaAddrSprsCcTbl S_IM_CNRTHREE_OTF_SPRS_CC_TBL[ImCnr_CH_NUM_MAX] = {
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
const static ImCnroneRdmaAddrSprdCcTbl S_IM_CNRTHREE_OFL_SPRD_CC_TBL[ImCnr_CH_NUM_MAX] = {
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

#endif


/*DECLS*/
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
#ifdef CO_DDIM_UTILITY_USE
static INT32 	imCnrOtfStartCore( const UCHAR ch, const UCHAR sync, const INT32 waitTime );
static INT32 	imCnrOflStartCore( const UCHAR ch, const UCHAR sync, const INT32 waitTime );
static VOID 	imCnrConvertRdmaValueCtrlC(const ImCnrCtrlC* sprCtrlC,
		ImCnrRdmaDataCtrlC* rdmaCtrlC);
static VOID		imCnrConvertRdmaCsprMidYTable(const ImCnrTable* sprCsprMidY,
		ImCnrRdmaDataCsprMidYTbl* rdmaCsprMidYTable);
static VOID 	imCnrConvertRdmaCsprMidCcYTable(const ImCnrTable* csprMidCcY,
		ImCnrRdmaDataCsprMidCcYTbl* rdmaMidCcYTable);
static VOID 	imCnrConvertRdmaCsprMidCcCTable(const ImCnrTable* csprMidCcC,
		ImCnrRdmaDataCsprMidCcCTbl* rdmaMidCcCTable);
#endif


/*IMPL*/
static void im_cnrfour_class_init(ImCnrfourClass *klass)
{
	g_type_class_add_private(klass, sizeof(ImCnrfourPrivate));
}

static void im_cnrfour_init(ImCnrfour *self)
{
	ImCnrfourPrivate *priv = IM_CNRFOUR_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImCnrfourPrivate *self = IM_CNRFOUR_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImCnrfourPrivate *self = IM_CNRFOUR_GET_PRIVATE(object);
}

// CNR(OTF) Start CORE
static INT32 imCnrOtfStartCore( const UCHAR ch, const UCHAR sync, const INT32 waitTime )
{
	INT32 ercd;
	UINT32 flgPtn;

	// SUPPRE End Flag disable
	if (ch == ImCnr_CH_0) {
		S_IM_CNR_MODE[ImCnr_CH_0] = ImCnr_MODE_OTF;
		DDIM_User_Clr_Flg( FID_IM_CNR, ~ImCnr_OTF_0_WAIT_FLGPTN );
	}
	else if (ch == ImCnr_CH_1) {
		S_IM_CNR_MODE[ImCnr_CH_1] = ImCnr_MODE_OTF;
		DDIM_User_Clr_Flg( FID_IM_CNR, ~ImCnr_OTF_1_WAIT_FLGPTN );
	}
	else {
		S_IM_CNR_MODE[ImCnr_CH_0] = ImCnr_MODE_OTF;
		S_IM_CNR_MODE[ImCnr_CH_1] = ImCnr_MODE_OTF;
		DDIM_User_Clr_Flg( FID_IM_CNR, ~(ImCnr_OTF_0_WAIT_FLGPTN|ImCnr_OTF_1_WAIT_FLGPTN) );
	}

	imCnrOnSprClk(ch);
	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	// Set Acess Enable
	IO_CNR(ch)->OTF_REG_RW.ACESEN.bit.SPRACS = 1;

	// wait 1us
	ImCnr_WAIT_USEC(ImCnr_SRAM_WAIT_USEC);

	ImCnr_OTF_ENABLE(ch);

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

#ifdef CO_DEBUG_ON_PC
	if( ch == ImCnr_CH_0 ){
		IO_CNR(ImCnr_CH_0)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
	}
	else if( ch == ImCnr_CH_1 ){
		IO_CNR(ImCnr_CH_1)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
	}
	else{
		IO_CNR(ImCnr_CH_0)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
		IO_CNR(ImCnr_CH_1)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
	}
#endif //CO_DEBUG_ON_PC

	if( ImCnr_ASYNC == sync ) {
		return D_DDIM_OK;
	}

#ifdef CO_DEBUG_ON_PC
	if( ch == ImCnr_CH_2 ){
		if( (IO_CNR(ImCnr_CH_0)->OTF_REG_RW.SPRICF.bit.__SPDF != 0)
		 || (IO_CNR(ImCnr_CH_0)->OTF_REG_RW.SPRICF.bit.__AXIF != 0)
		 || (IO_CNR(ImCnr_CH_0)->OTF_REG_RW.SPRICF.bit.__DRTF != 0)
		 || (IO_CNR(ImCnr_CH_1)->OTF_REG_RW.SPRICF.bit.__SPDF != 0)
		 || (IO_CNR(ImCnr_CH_1)->OTF_REG_RW.SPRICF.bit.__AXIF != 0)
		 || (IO_CNR(ImCnr_CH_1)->OTF_REG_RW.SPRICF.bit.__DRTF != 0) ) {
			im_cnr_0_int_handler();
			im_cnr_1_int_handler();
		}
	}
	else{
		if( (IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__SPDF != 0)
		 || (IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__AXIF != 0)
		 || (IO_CNR(ch)->OTF_REG_RW.SPRICF.bit.__DRTF != 0) ) {
			if (ch == ImCnr_CH_0) {
				im_cnr_0_int_handler();
			}
			else{
				im_cnr_1_int_handler();
			}
		}
	}
#endif //CO_DEBUG_ON_PC

	// Wait for Process end with Sync
	ercd = im_cnrfive_otf_wait_end( ch, &flgPtn, waitTime );
	if( ercd != D_DDIM_OK ) {
		return ercd;
	}
	if (ch == ImCnr_CH_0) {
		if( (flgPtn & ImCnr_FLG_0_OTF_SPR_AXI_ERR) != 0 ) {
			return ImCnr_AXI_ERR;
		}
		if( (flgPtn & ImCnr_FLG_0_OTF_SPR_DRT_ERR) != 0 ) {
			return ImCnr_DRT_ERR;
		}
	}
	else if (ch == ImCnr_CH_1) {
		if( (flgPtn & ImCnr_FLG_1_OTF_SPR_AXI_ERR) != 0 ) {
			return ImCnr_AXI_ERR;
		}
		if( (flgPtn & ImCnr_FLG_1_OTF_SPR_DRT_ERR) != 0 ) {
			return ImCnr_DRT_ERR;
		}
	}
	else {
		if( (flgPtn & ImCnr_FLG_0_OTF_SPR_AXI_ERR) != 0 ) {
			return ImCnr_AXI_ERR;
		}
		if( (flgPtn & ImCnr_FLG_1_OTF_SPR_AXI_ERR) != 0 ) {
			return ImCnr_AXI_ERR;
		}
		if( (flgPtn & ImCnr_FLG_0_OTF_SPR_DRT_ERR) != 0 ) {
			return ImCnr_DRT_ERR;
		}
		if( (flgPtn & ImCnr_FLG_1_OTF_SPR_DRT_ERR) != 0 ) {
			return ImCnr_DRT_ERR;
		}
	}

	return D_DDIM_OK;
}

// CNR(OFT) Start CORE
static INT32 imCnrOflStartCore( const UCHAR ch, const UCHAR sync, const INT32 waitTime )
{
	INT32 ercd;
	UINT32 flgPtn;

	// SUPPRE End Flag disable
	if (ch == ImCnr_CH_0) {
		S_IM_CNR_MODE[ImCnr_CH_0] = ImCnr_MODE_OFL;
		DDIM_User_Clr_Flg( FID_IM_CNR, ~ImCnr_OFL_0_WAIT_FLGPTN );
	}
	else if (ch == ImCnr_CH_1) {
		S_IM_CNR_MODE[ImCnr_CH_1] = ImCnr_MODE_OFL;
		DDIM_User_Clr_Flg( FID_IM_CNR, ~ImCnr_OFL_1_WAIT_FLGPTN );
	}
	else {
		S_IM_CNR_MODE[ImCnr_CH_0] = ImCnr_MODE_OFL;
		S_IM_CNR_MODE[ImCnr_CH_1] = ImCnr_MODE_OFL;
		DDIM_User_Clr_Flg( FID_IM_CNR, ~(ImCnr_OFL_0_WAIT_FLGPTN|ImCnr_OFL_1_WAIT_FLGPTN) );
	}

	imCnrOnSprClk(ch);
	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	// Set Acess Enable
	IO_CNR(ch)->OFL_REG_RW.ACESEN.bit.SPRACS = 1;

	// wait 1us
	ImCnr_WAIT_USEC(ImCnr_SRAM_WAIT_USEC);

	ImCnr_OFL_ENABLE(ch);

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

#ifdef CO_DEBUG_ON_PC
	if( ch == ImCnr_CH_0 ){
		IO_CNR(ImCnr_CH_0)->OFL_REG_RW.SPRICF.bit.__SPDF = 1;
	}
	else if( ch == ImCnr_CH_1 ){
		IO_CNR(ImCnr_CH_1)->OFL_REG_RW.SPRICF.bit.__SPDF = 1;
	}
	else{
		IO_CNR(ImCnr_CH_0)->OFL_REG_RW.SPRICF.bit.__SPDF = 1;
		IO_CNR(ImCnr_CH_1)->OFL_REG_RW.SPRICF.bit.__SPDF = 1;
	}
#endif //CO_DEBUG_ON_PC

	if( ImCnr_ASYNC == sync ) {
		return D_DDIM_OK;
	}

#ifdef CO_DEBUG_ON_PC
	if( ch == ImCnr_CH_2 ){
		if( (IO_CNR(ImCnr_CH_0)->OFL_REG_RW.SPRICF.bit.__SPDF != 0)
		 || (IO_CNR(ImCnr_CH_0)->OFL_REG_RW.SPRICF.bit.__AXIF != 0)
		 || (IO_CNR(ImCnr_CH_1)->OFL_REG_RW.SPRICF.bit.__SPDF != 0)
		 || (IO_CNR(ImCnr_CH_1)->OFL_REG_RW.SPRICF.bit.__AXIF != 0) ) {
			im_cnr_0_int_handler();
			im_cnr_1_int_handler();
		}
	}
	else{
		if( (IO_CNR(ch)->OFL_REG_RW.SPRICF.bit.__SPDF != 0)
		 || (IO_CNR(ch)->OFL_REG_RW.SPRICF.bit.__AXIF != 0) ) {
			if (ch == ImCnr_CH_0) {
				im_cnr_0_int_handler();
			}
			else {
				im_cnr_1_int_handler();
			}
		}
	}
#endif //CO_DEBUG_ON_PC

	// Wait for Process end with Sync
	ercd = im_cnrfive_ofl_wait_end( ch, &flgPtn, waitTime );
	if( ercd != D_DDIM_OK ) {
		return ercd;
	}
	if (ch == ImCnr_CH_0) {
		if( (flgPtn & ImCnr_FLG_0_OFL_SPR_AXI_ERR) != 0 ) {
			return ImCnr_AXI_ERR;
		}
	}
	else if (ch == ImCnr_CH_1) {
		if( (flgPtn & ImCnr_FLG_1_OFL_SPR_AXI_ERR) != 0 ) {
			return ImCnr_AXI_ERR;
		}
	}
	else {
		if( (flgPtn & ImCnr_FLG_0_OFL_SPR_AXI_ERR) != 0 ) {
			return ImCnr_AXI_ERR;
		}
		if( (flgPtn & ImCnr_FLG_1_OFL_SPR_AXI_ERR) != 0 ) {
			return ImCnr_AXI_ERR;
		}
	}

	return D_DDIM_OK;
}

/*
Convert ImCnrCtrlC to ImCnrRdmaDataCtrlC
*/
static VOID imCnrConvertRdmaValueCtrlC( const ImCnrCtrlC* sprCtrlC, ImCnrRdmaDataCtrlC* rdmaCtrlC )
{
	rdmaCtrlC->CSPREN.bit.CSPREN	= sprCtrlC->enable;
	rdmaCtrlC->CGDKEN.bit.CGDKEN	= sprCtrlC->gradationKeepEn;
	rdmaCtrlC->MCEN.bit.MCEN		= sprCtrlC->midFreqNr.enable;

	rdmaCtrlC->MCYTHH.bit.MCYTHH_0	= sprCtrlC->midFreqNr.hYThreshold[0];
	rdmaCtrlC->MCYTHH.bit.MCYTHH_1	= sprCtrlC->midFreqNr.hYThreshold[1];
	rdmaCtrlC->MCYTHH.bit.MCYTHH_2	= sprCtrlC->midFreqNr.hYThreshold[2];
	rdmaCtrlC->MCYTHH.bit.MCYTHH_3	= sprCtrlC->midFreqNr.hYThreshold[3];
	rdmaCtrlC->MCYTHV.bit.MCYTHV_0	= sprCtrlC->midFreqNr.vYThreshold[0];
	rdmaCtrlC->MCYTHV.bit.MCYTHV_1	= sprCtrlC->midFreqNr.vYThreshold[1];
	rdmaCtrlC->MCYTHV.bit.MCYTHV_2	= sprCtrlC->midFreqNr.vYThreshold[2];
	rdmaCtrlC->MCYTHV.bit.MCYTHV_3	= sprCtrlC->midFreqNr.vYThreshold[3];
	rdmaCtrlC->MCCTHH.bit.MCCTHH_0	= sprCtrlC->midFreqNr.hCThreshold[0];
	rdmaCtrlC->MCCTHH.bit.MCCTHH_1	= sprCtrlC->midFreqNr.hCThreshold[1];
	rdmaCtrlC->MCCTHH.bit.MCCTHH_2	= sprCtrlC->midFreqNr.hCThreshold[2];
	rdmaCtrlC->MCCTHH.bit.MCCTHH_3	= sprCtrlC->midFreqNr.hCThreshold[3];
	rdmaCtrlC->MCCTHV.bit.MCCTHV_0	= sprCtrlC->midFreqNr.vCThreshold[0];
	rdmaCtrlC->MCCTHV.bit.MCCTHV_1	= sprCtrlC->midFreqNr.vCThreshold[1];
	rdmaCtrlC->MCCTHV.bit.MCCTHV_2	= sprCtrlC->midFreqNr.vCThreshold[2];
	rdmaCtrlC->MCCTHV.bit.MCCTHV_3	= sprCtrlC->midFreqNr.vCThreshold[3];

	rdmaCtrlC->MCYDYMDT.bit.MCYDYMYCR	= sprCtrlC->midFreqNr.yThresholdCor;
	rdmaCtrlC->MCYDYMDT.bit.MCYDYMYG	= sprCtrlC->midFreqNr.yThresholdGain;
	rdmaCtrlC->MCYDYM.bit.MCYDYM		= sprCtrlC->midFreqNr.yThresholdDymEn;
	rdmaCtrlC->MCYSCL.bit.MCYSCL		= sprCtrlC->midFreqNr.yThresholdSclEn;
	rdmaCtrlC->MCSSCL.bit.MCSSCL		= sprCtrlC->midFreqNr.cYThresholdSclEn;
	rdmaCtrlC->MCCSCL.bit.MCCSCL		= sprCtrlC->midFreqNr.cThresholdSclEn;
	rdmaCtrlC->LCEN.bit.LCEN			= sprCtrlC->lowFreqNr.enable;
	rdmaCtrlC->LCYTHH.bit.LCYTHH_0	= sprCtrlC->lowFreqNr.hYThreshold[0];
	rdmaCtrlC->LCYTHH.bit.LCYTHH_1	= sprCtrlC->lowFreqNr.hYThreshold[1];
	rdmaCtrlC->LCYTHH.bit.LCYTHH_2	= sprCtrlC->lowFreqNr.hYThreshold[2];
	rdmaCtrlC->LCYTHH.bit.LCYTHH_3	= sprCtrlC->lowFreqNr.hYThreshold[3];
	rdmaCtrlC->LCYTHV.bit.LCYTHV_0	= sprCtrlC->lowFreqNr.vYThreshold[0];
	rdmaCtrlC->LCYTHV.bit.LCYTHV_1	= sprCtrlC->lowFreqNr.vYThreshold[1];
	rdmaCtrlC->LCYTHV.bit.LCYTHV_2	= sprCtrlC->lowFreqNr.vYThreshold[2];
	rdmaCtrlC->LCYTHV.bit.LCYTHV_3	= sprCtrlC->lowFreqNr.vYThreshold[3];
	rdmaCtrlC->LCCTHH.bit.LCCTHH_0	= sprCtrlC->lowFreqNr.hCThreshold[0];
	rdmaCtrlC->LCCTHH.bit.LCCTHH_1	= sprCtrlC->lowFreqNr.hCThreshold[1];
	rdmaCtrlC->LCCTHH.bit.LCCTHH_2	= sprCtrlC->lowFreqNr.hCThreshold[2];
	rdmaCtrlC->LCCTHH.bit.LCCTHH_3	= sprCtrlC->lowFreqNr.hCThreshold[3];
	rdmaCtrlC->LCCTHV.bit.LCCTHV_0	= sprCtrlC->lowFreqNr.vCThreshold[0];
	rdmaCtrlC->LCCTHV.bit.LCCTHV_1	= sprCtrlC->lowFreqNr.vCThreshold[1];
	rdmaCtrlC->LCCTHV.bit.LCCTHV_2	= sprCtrlC->lowFreqNr.vCThreshold[2];
	rdmaCtrlC->LCCTHV.bit.LCCTHV_3	= sprCtrlC->lowFreqNr.vCThreshold[3];
	rdmaCtrlC->LCYDYMDT.bit.LCYDYMYCR	= sprCtrlC->lowFreqNr.yThresholdCor;
	rdmaCtrlC->LCYDYMDT.bit.LCYDYMYG	= sprCtrlC->lowFreqNr.yThresholdGain;
	rdmaCtrlC->LCYDYM.bit.LCYDYM	= sprCtrlC->lowFreqNr.yThresholdDymEn;
	rdmaCtrlC->LCYSCL.bit.LCYSCL	= sprCtrlC->lowFreqNr.yThresholdSclEn;
	rdmaCtrlC->LCSSCL.bit.LCSSCL	= sprCtrlC->lowFreqNr.cYThresholdSclEn;
	rdmaCtrlC->LCCSCL.bit.LCCSCL	= sprCtrlC->lowFreqNr.cThresholdSclEn;

	rdmaCtrlC->WHTMD.bit.WHTEN	= sprCtrlC->whiteningEnable;
	rdmaCtrlC->WHTMD.bit.WHTVAL	= sprCtrlC->whiteningValue;
	rdmaCtrlC->WHTMD.bit.WHTBASE	= sprCtrlC->whiteningBase;

	rdmaCtrlC->BLEND.bit.BLENDMD		= sprCtrlC->cBlendMd;
	rdmaCtrlC->BLEND.bit.CSPRALPBD	= sprCtrlC->cAlphaBlend;
	rdmaCtrlC->BLEND.bit.CSRGEN		= sprCtrlC->cRange;
	rdmaCtrlC->BLEND.bit.CSRGMD		= sprCtrlC->cRangeMode;
}

/*
Convert ImCnrTable to ImCnrRdmaDataCsprMidYTbl
*/
static VOID imCnrConvertRdmaCsprMidYTable( const ImCnrTable* sprCsprMidY,
		ImCnrRdmaDataCsprMidYTbl* rdmaCsprMidYTable )
{
	rdmaCsprMidYTable->MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_1	= sprCsprMidY->bd1;
	rdmaCsprMidYTable->MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_2	= sprCsprMidY->bd2;
	rdmaCsprMidYTable->MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_3	= sprCsprMidY->bd3;
	rdmaCsprMidYTable->MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_4	= sprCsprMidY->bd4;
	rdmaCsprMidYTable->MCYSCLBD.MCYSCLBD2.bit.MCYSCLBD_5	= sprCsprMidY->bd5;
	rdmaCsprMidYTable->MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_0	= sprCsprMidY->of0;
	rdmaCsprMidYTable->MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_1	= sprCsprMidY->of1;
	rdmaCsprMidYTable->MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_2	= sprCsprMidY->of2;
	rdmaCsprMidYTable->MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_3	= sprCsprMidY->of3;
	rdmaCsprMidYTable->MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_4	= sprCsprMidY->of4;
	rdmaCsprMidYTable->MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_5	= sprCsprMidY->of5;
	// write signed data
	ImCnr_SET_REG_SIGNED( rdmaCsprMidYTable->MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, sprCsprMidY->gain0 );
	ImCnr_SET_REG_SIGNED( rdmaCsprMidYTable->MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_1, sprCsprMidY->gain1 );
	ImCnr_SET_REG_SIGNED( rdmaCsprMidYTable->MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_2, sprCsprMidY->gain2 );
	ImCnr_SET_REG_SIGNED( rdmaCsprMidYTable->MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, sprCsprMidY->gain3 );
	ImCnr_SET_REG_SIGNED( rdmaCsprMidYTable->MCYSCLGA.MCYSCLGA2,
			union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, sprCsprMidY->gain4 );
	ImCnr_SET_REG_SIGNED( rdmaCsprMidYTable->MCYSCLGA.MCYSCLGA2,
			union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, sprCsprMidY->gain5 );
}

/*
Convert ImCnrTable to ImCnrRdmaAddrCsprMidCcYTbl
*/
static VOID imCnrConvertRdmaCsprMidCcYTable( const ImCnrTable* csprMidCcY,
		ImCnrRdmaDataCsprMidCcYTbl* rdmaMidCcYTable )
{
	rdmaMidCcYTable->MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_1	= csprMidCcY->bd1;
	rdmaMidCcYTable->MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_2	= csprMidCcY->bd2;
	rdmaMidCcYTable->MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_3	= csprMidCcY->bd3;
	rdmaMidCcYTable->MCCSCLBD.MCCSCLBD1.bit.MCCSCLBD_4	= csprMidCcY->bd4;
	rdmaMidCcYTable->MCCSCLBD.MCCSCLBD2.bit.MCCSCLBD_5	= csprMidCcY->bd5;
	rdmaMidCcYTable->MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_0	= csprMidCcY->of0;
	rdmaMidCcYTable->MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_1	= csprMidCcY->of1;
	rdmaMidCcYTable->MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_2	= csprMidCcY->of2;
	rdmaMidCcYTable->MCCSCLOF.MCCSCLOF1.bit.MCCSCLOF_3	= csprMidCcY->of3;
	rdmaMidCcYTable->MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_4	= csprMidCcY->of4;
	rdmaMidCcYTable->MCCSCLOF.MCCSCLOF2.bit.MCCSCLOF_5	= csprMidCcY->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( rdmaMidCcYTable->MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_0, csprMidCcY->gain0 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcYTable->MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_1, csprMidCcY->gain1 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcYTable->MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_2, csprMidCcY->gain2 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcYTable->MCCSCLGA.MCCSCLGA1,
			union io_cnr_cspr_reg_mccsclga_1, MCCSCLGA_3, csprMidCcY->gain3 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcYTable->MCCSCLGA.MCCSCLGA2,
			union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_4, csprMidCcY->gain4 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcYTable->MCCSCLGA.MCCSCLGA2,
			union io_cnr_cspr_reg_mccsclga_2, MCCSCLGA_5, csprMidCcY->gain5 );
}

/*
Convert ImCnrTable to ImCnrRdmaAddrCsprMidCcCTbl
*/
static VOID imCnrConvertRdmaCsprMidCcCTable( const ImCnrTable* csprMidCcC,
		ImCnrRdmaDataCsprMidCcCTbl* rdmaMidCcCTable )
{
	rdmaMidCcCTable->MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_1	= csprMidCcC->bd1;
	rdmaMidCcCTable->MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_2	= csprMidCcC->bd2;
	rdmaMidCcCTable->MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_3	= csprMidCcC->bd3;
	rdmaMidCcCTable->MCSSCLBD.MCSSCLBD1.bit.MCSSCLBD_4	= csprMidCcC->bd4;
	rdmaMidCcCTable->MCSSCLBD.MCSSCLBD2.bit.MCSSCLBD_5	= csprMidCcC->bd5;
	rdmaMidCcCTable->MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_0	= csprMidCcC->of0;
	rdmaMidCcCTable->MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_1	= csprMidCcC->of1;
	rdmaMidCcCTable->MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_2	= csprMidCcC->of2;
	rdmaMidCcCTable->MCSSCLOF.MCSSCLOF1.bit.MCSSCLOF_3	= csprMidCcC->of3;
	rdmaMidCcCTable->MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_4	= csprMidCcC->of4;
	rdmaMidCcCTable->MCSSCLOF.MCSSCLOF2.bit.MCSSCLOF_5	= csprMidCcC->of5;
	// write signed data
	ImCnr_SET_REG_SIGNED( rdmaMidCcCTable->MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_0, csprMidCcC->gain0 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcCTable->MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_1, csprMidCcC->gain1 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcCTable->MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_2, csprMidCcC->gain2 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcCTable->MCSSCLGA.MCSSCLGA1,
			union io_cnr_cspr_reg_mcssclga_1, MCSSCLGA_3, csprMidCcC->gain3 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcCTable->MCSSCLGA.MCSSCLGA2,
			union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_4, csprMidCcC->gain4 );
	ImCnr_SET_REG_SIGNED( rdmaMidCcCTable->MCSSCLGA.MCSSCLGA2,
			union io_cnr_cspr_reg_mcssclga_2, MCSSCLGA_5, csprMidCcC->gain5 );
}


/*PUBLIC*/
/*
CNR(OTF) Start Sync
*/
INT32 im_cnrfour_otf_start_sync(ImCnrfour *self, UCHAR ch, const INT32 waitTime )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfour_otf_start_sync() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif
	return imCnrOtfStartCore( ch, ImCnr_SYNC, waitTime );
}

/*
CNR(OTF) Start Async
*/
INT32 im_cnrfour_otf_start_async(ImCnrfour *self, UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfour_otf_start_async() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif
	return imCnrOtfStartCore( ch, ImCnr_ASYNC, 0 );	// waitTime is dummy.
}

/*
CNR(OFL) Start Sync
*/
INT32 im_cnrfour_ofl_start_sync(ImCnrfour *self, UCHAR ch, const INT32 waitTime )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfour_ofl_start_sync() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif
	return imCnrOflStartCore( ch, ImCnr_SYNC, waitTime );
}

/*
CNR(OFL) Start Async
*/
INT32 im_cnrfour_ofl_start_async(ImCnrfour *self, UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfour_ofl_start_async() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif
	return imCnrOflStartCore( ch, ImCnr_ASYNC, 0 );	// waitTime is dummy.
}

#ifdef CO_DDIM_UTILITY_USE
// --- CSPR Hue Specified Table (OTF) ---
/*
CNR(OTF) Get CSPR Hue Specified Table setting address information
*/
INT32 im_cnrfour_get_rdmaaddr_otf_cspr_hue_spec_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprHueTbl** const csprHueTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion
		(("im_cnrfour_get_rdmaaddr_otf_cspr_hue_spec_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprHueTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_get_rdmaaddr_otf_cspr_hue_spec_table() Parameter(csprHueTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_otf_cspr_hue_spec_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprHueTbl	= &S_IM_CNRTHREE_OTF_CSPR_HUE_TBL[ch];
	*size			= sizeof( ImCnroneRdmaAddrCsprHueTbl );

	return D_DDIM_OK;
}

// --- CSPR SPRS_CC Table (OFL) ---
/*
CNR(OFL) Get CSPR SPRS_CC Table setting address information
*/
INT32 im_cnrfour_get_rdmaaddr_ofl_cspr_sprs_cc_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrSprsCcTbl** const csprSprsCcTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfour_get_rdmaaddr_ofl_cspr_sprs_cc_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprSprsCcTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_ofl_cspr_sprs_cc_table() Parameter(csprSprsCcTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_ofl_cspr_sprs_cc_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprSprsCcTbl	= &S_IM_CNRTHREE_OFL_SPRS_CC_TBL[ch];
	*size				= sizeof( ImCnroneRdmaAddrSprsCcTbl );

	return D_DDIM_OK;
}

// --- CSPR SPRS_CC Table (OTF) ---
/*
CNR(OTF) Get CSPR SPRS_CC Table setting address information
*/
INT32 im_cnrfour_get_rdmaaddr_otf_cspr_sprs_cc_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrSprsCcTbl** const csprSprsCcTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfour_get_rdmaaddr_otf_cspr_sprs_cc_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprSprsCcTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_otf_cspr_sprs_cc_table() Parameter(csprSprsCcTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_otf_cspr_sprs_cc_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprSprsCcTbl	= &S_IM_CNRTHREE_OTF_SPRS_CC_TBL[ch];
	*size				= sizeof( ImCnroneRdmaAddrSprsCcTbl );

	return D_DDIM_OK;
}

// --- CSPR SPRD_CC Table (OFL) ---
/*
CNR(OFL) Get CSPR SPRD_CC Table setting address information
*/
INT32 im_cnrfour_get_rdmaaddr_ofl_cspr_sprd_cc_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrSprdCcTbl** const csprSprdCcTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfour_get_rdmaaddr_ofl_cspr_sprd_cc_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprSprdCcTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_ofl_cspr_sprd_cc_table() Parameter(csprSprdCcTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_ofl_cspr_sprd_cc_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprSprdCcTbl	= &S_IM_CNRTHREE_OFL_SPRD_CC_TBL[ch];
	*size				= sizeof( ImCnroneRdmaAddrSprdCcTbl );

	return D_DDIM_OK;
}

// --- CSPR SPRD_CC Table (OTF) ---
/*
CNR(OTF) Get CSPR SPRD_CC Table setting address information
*/
INT32 im_cnrfour_get_rdmaaddr_otf_cspr_sprd_cc_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrSprdCcTbl** const csprSprdCcTbl, ULONG* const size )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfour_get_rdmaaddr_otf_cspr_sprd_cc_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( csprSprdCcTbl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_otf_cspr_sprd_cc_table() Parameter(csprSprdCcTbl) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( size == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_get_rdmaaddr_otf_cspr_sprd_cc_table() Parameter(size) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*csprSprdCcTbl	= &S_IM_CNRTHREE_OTF_SPRD_CC_TBL[ch];
	*size				= sizeof( ImCnroneRdmaAddrSprdCcTbl );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set SPR CTRL-C setting parameter information
*/
INT32 im_cnrfour_set_rdmavalue_ofl_ctrl_c(ImCnrfour *self, const ImCnrCtrlC* const sprCtrlC,
		ImCnrRdmaDataCtrlC* const rdmaCtrlC )
{
#ifdef CO_PARAM_CHECK
	if( sprCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_set_rdmavalue_ofl_ctrl_c() Parameter(sprCtrlC) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_set_rdmavalue_ofl_ctrl_c() Parameter(rdmaCtrlC) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCtrlC, 0, sizeof(ImCnrRdmaDataCtrlC) );
	imCnrConvertRdmaValueCtrlC( sprCtrlC, rdmaCtrlC );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set SPR CTRL-C setting parameter information
*/
INT32 im_cnrfour_set_rdmavalue_otf_ctrl_c(ImCnrfour *self, const ImCnrCtrlC* const sprCtrlC,
		ImCnrRdmaDataCtrlC* const rdmaCtrlC )
{
#ifdef CO_PARAM_CHECK
	if( sprCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_set_rdmavalue_otf_ctrl_c() Parameter(sprCtrlC) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_set_rdmavalue_otf_ctrl_c() Parameter(rdmaCtrlC) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCtrlC, 0, sizeof(ImCnrRdmaDataCtrlC) );
	imCnrConvertRdmaValueCtrlC( sprCtrlC, rdmaCtrlC );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_Y Table setting parameter information
*/
INT32 im_cnrfour_set_rdmavalue_ofl_cspr_mid_y_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidY,
		ImCnrRdmaDataCsprMidYTbl* const rdmaCsprMidYTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprMidY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_set_rdmavalue_ofl_cspr_mid_y_table() Parameter(sprCsprMidY) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprMidYTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_ofl_cspr_mid_y_table() Parameter(rdmaCsprMidYTable) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprMidYTable, 0, sizeof(ImCnrRdmaDataCsprMidYTbl) );
	imCnrConvertRdmaCsprMidYTable( sprCsprMidY, rdmaCsprMidYTable );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_Y Table setting parameter information
*/
INT32 im_cnrfour_set_rdmavalue_otf_cspr_mid_y_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidY,
		ImCnrRdmaDataCsprMidYTbl* const rdmaCsprMidYTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprMidY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfour_set_rdmavalue_otf_cspr_mid_y_table() Parameter(sprCsprMidY) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprMidYTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_otf_cspr_mid_y_table() Parameter(rdmaCsprMidYTable) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprMidYTable, 0, sizeof(ImCnrRdmaDataCsprMidYTbl) );
	imCnrConvertRdmaCsprMidYTable( sprCsprMidY, rdmaCsprMidYTable );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_CC_Y Table setting parameter information
*/
INT32 im_cnrfour_set_rdmavalue_ofl_cspr_mid_cc_y_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidCcY,
		ImCnrRdmaDataCsprMidCcYTbl* const rdmaCsprMidCcYTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprMidCcY == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_ofl_cspr_mid_cc_y_table() Parameter(sprCsprMidCcY) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprMidCcYTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_ofl_cspr_mid_cc_y_table() Parameter(rdmaCsprMidCcYTable) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprMidCcYTable, 0, sizeof(ImCnrRdmaDataCsprMidCcYTbl) );
	imCnrConvertRdmaCsprMidCcYTable( sprCsprMidCcY, rdmaCsprMidCcYTable );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_CC_Y Table setting parameter information
*/
INT32 im_cnrfour_set_rdmavalue_otf_cspr_mid_cc_y_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidCcY,
		ImCnrRdmaDataCsprMidCcYTbl* const rdmaCsprMidCcYTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprMidCcY == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_otf_cspr_mid_cc_y_table() Parameter(sprCsprMidCcY) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprMidCcYTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_otf_cspr_mid_cc_y_table() Parameter(rdmaCsprMidCcYTable) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprMidCcYTable, 0, sizeof(ImCnrRdmaDataCsprMidCcYTbl) );
	imCnrConvertRdmaCsprMidCcYTable( sprCsprMidCcY, rdmaCsprMidCcYTable );

	return D_DDIM_OK;
}

/*
CNR(OFL) Set CSPR Mid_CC_C Table setting parameter information
*/
INT32 im_cnrfour_set_rdmavalue_ofl_cspr_mid_cc_c_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidCcC,
		ImCnrRdmaDataCsprMidCcCTbl* const rdmaCsprMidCcCTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprMidCcC == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_ofl_cspr_mid_cc_c_table() Parameter(sprCsprMidCcC) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprMidCcCTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_ofl_cspr_mid_cc_c_table() Parameter(rdmaCsprMidCcCTable) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprMidCcCTable, 0, sizeof(ImCnrRdmaDataCsprMidCcCTbl) );
	imCnrConvertRdmaCsprMidCcCTable( sprCsprMidCcC, rdmaCsprMidCcCTable );

	return D_DDIM_OK;
}

/*
CNR(OTF) Set CSPR Mid_CC_C Table setting parameter information
*/
INT32 im_cnrfour_set_rdmavalue_otf_cspr_mid_cc_c_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidCcC,
		ImCnrRdmaDataCsprMidCcCTbl* const rdmaCsprMidCcCTable )
{
#ifdef CO_PARAM_CHECK
	if( sprCsprMidCcC == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_otf_cspr_mid_cc_c_table() Parameter(sprCsprMidCcC) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( rdmaCsprMidCcCTable == NULL ) {
		// Parameter setting error
		Ddim_Assertion
		(("I:im_cnrfour_set_rdmavalue_otf_cspr_mid_cc_c_table() Parameter(rdmaCsprMidCcCTable) is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	memset( rdmaCsprMidCcCTable, 0, sizeof(ImCnrRdmaDataCsprMidCcCTbl) );
	imCnrConvertRdmaCsprMidCcCTable( sprCsprMidCcC, rdmaCsprMidCcCTable );

	return D_DDIM_OK;
}

#endif

ImCnrfour* im_cnrfour_new(void)
{
	ImCnrfour *self = g_object_new(IM_TYPE_CNRFOUR, NULL);
	return self;
}






