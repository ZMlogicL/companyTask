/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :董如利
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#include "ctddcoes3help.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdCoes3Help, ct_dd_coes3_help);
#define CT_DD_COES3_HELP_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdCoes3HelpPrivate,CT_TYPE_DD_COES3_HELP))

struct _CtDdCoes3HelpPrivate
{
	kint a;
};
/****************
* DECLS
*/
static void 			ct_dd_coes3_help_constructor(CtDdCoes3Help *self);
static void 			ct_dd_coes3_help_destructor(CtDdCoes3Help *self);
/****************
* IMPL
*/
static void ct_dd_coes3_help_constructor(CtDdCoes3Help *self) 
{
//	CtDdCoes3HelpPrivate *priv = CT_DD_COES3_HELP_GET_PRIVATE(self);
}

static void ct_dd_coes3_help_destructor(CtDdCoes3Help *self) 
{
//	CtDdCoes3HelpPrivate *priv = CT_DD_COES3_HELP_GET_PRIVATE(self);
}

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**
 * @brief  Command main function for TOP test.
 * @param  kint argc	:The number of parameters
 *		   kchar** argv	:The value of parameters
 * @return void
 *
 *	The meaning of parameters
 *
 * P1  P2        P3     P4   P5
 * lsi get_ctrl persel1								// Get persel1 register
 * lsi get_ctrl persel3								// Get persel3 register
 * lsi get_ctrl msel								// Get msel register
 * lsi get_ctrl dbcnt1								// Get dbcnt1 register
 * lsi get_ctrl dbcnt2								// Get dbcnt2 register
 * lsi get_ctrl dbcnt3								// Get dbcnt3 register
 * lsi get_ctrl dbcnt4								// Get dbcnt4 register
 * lsi get_ctrl dbcnt5								// Get dbcnt5 register
 * lsi set_ctrl persel1 I2C0CNT value				// Set persel1 I2C0CNT register
 * lsi set_ctrl persel1 SDANC0 value				// Set persel1 SDANC0 register
 * lsi set_ctrl persel1 SCLNC0 value				// Set persel1 SCLNC0 register
 * lsi set_ctrl persel1 I2C1CNT value				// Set persel1 I2C1CNT register
 * lsi set_ctrl persel1 SDANC1 value				// Set persel1 SDANC1 register
 * lsi set_ctrl persel1 SCLNC1 value				// Set persel1 SCLNC1 register
 * lsi set_ctrl persel1 I2C2CNT value				// Set persel1 I2C2CNT register
 * lsi set_ctrl persel1 SDANC2 value				// Set persel1 SDANC2 register
 * lsi set_ctrl persel1 SCLNC2 value				// Set persel1 SCLNC2 register
 * lsi set_ctrl persel1 DVWT2 value					// Set persel1 DVWT2 register
 * lsi set_ctrl persel1 DHWT3 value					// Set persel1 DHWT3 register
 * lsi set_ctrl persel1 AU0DO0C value				// Set persel1 AU0DO0C register
 * lsi set_ctrl persel1 AU0DO1C value				// Set persel1 AU0DO1C register
 * lsi set_ctrl persel1 AU1DOC value				// Set persel1 AU1DOC register
 * lsi set_ctrl persel1 AU0MCC value				// Set persel1 AU0MCC register
 * lsi set_ctrl persel1 AU1MCC value				// Set persel1 AU1MCC register
 * lsi set_ctrl persel1 RLSEL3 value				// Set persel1 RLSEL3 register
 * lsi set_ctrl persel1 RLSEL4 value				// Set persel1 RLSEL4 register
 * lsi set_ctrl persel1 RLSEL5 value				// Set persel1 RLSEL5 register
 * lsi set_ctrl persel3 AU1WPPS value				// Set persel3 AU1WPPS register
 * lsi set_ctrl mselc MSEL value					// Set mselc MSEL register
 * lsi set_ctrl dbcnt1 T00DC value					// Set dbcnt1 T00DC register
 * lsi set_ctrl dbcnt1 T01DC value					// Set dbcnt1 T01DC register
 * lsi set_ctrl dbcnt1 T02DC value					// Set dbcnt1 T02DC register
 * lsi set_ctrl dbcnt1 T03DC value					// Set dbcnt1 T03DC register
 * lsi set_ctrl dbcnt1 T04DC value					// Set dbcnt1 T04DC register
 * lsi set_ctrl dbcnt1 T05DC value					// Set dbcnt1 T05DC register
 * lsi set_ctrl dbcnt1 T06DC value					// Set dbcnt1 T06DC register
 * lsi set_ctrl dbcnt1 T07DC value					// Set dbcnt1 T07DC register
 * lsi set_ctrl dbcnt1 T08DC value					// Set dbcnt1 T08DC register
 * lsi set_ctrl dbcnt1 T09DC value					// Set dbcnt1 T09DC register
 * lsi set_ctrl dbcnt1 T10DC value					// Set dbcnt1 T10DC register
 * lsi set_ctrl dbcnt1 T11DC value					// Set dbcnt1 T11DC register
 * lsi set_ctrl dbcnt1 T12DC value					// Set dbcnt1 T12DC register
 * lsi set_ctrl dbcnt1 T13DC value					// Set dbcnt1 T13DC register
 * lsi set_ctrl dbcnt1 T14DC value					// Set dbcnt1 T14DC register
 * lsi set_ctrl dbcnt1 T15DC value					// Set dbcnt1 T15DC register
 * lsi set_ctrl dbcnt2 T16DC value					// Set dbcnt2 T16DC register
 * lsi set_ctrl dbcnt2 T17DC value					// Set dbcnt2 T17DC register
 * lsi set_ctrl dbcnt2 T18DC value					// Set dbcnt2 T18DC register
 * lsi set_ctrl dbcnt2 T19DC value					// Set dbcnt2 T19DC register
 * lsi set_ctrl dbcnt2 T20DC value					// Set dbcnt2 T20DC register
 * lsi set_ctrl dbcnt2 T21DC value					// Set dbcnt2 T21DC register
 * lsi set_ctrl dbcnt2 T22DC value					// Set dbcnt2 T22DC register
 * lsi set_ctrl dbcnt2 T23DC value					// Set dbcnt2 T23DC register
 * lsi set_ctrl dbcnt2 T24DC value					// Set dbcnt2 T24DC register
 * lsi set_ctrl dbcnt2 T25DC value					// Set dbcnt2 T25DC register
 * lsi set_ctrl dbcnt2 T26DC value					// Set dbcnt2 T26DC register
 * lsi set_ctrl dbcnt2 T27DC value					// Set dbcnt2 T27DC register
 * lsi set_ctrl dbcnt2 T28DC value					// Set dbcnt2 T28DC register
 * lsi set_ctrl dbcnt2 T29DC value					// Set dbcnt2 T29DC register
 * lsi set_ctrl dbcnt2 T30DC value					// Set dbcnt2 T30DC register
 * lsi set_ctrl dbcnt2 T31DC value					// Set dbcnt2 T31DC register
 * lsi set_ctrl dbcnt3 T32DC value					// Set dbcnt3 T32DC register
 * lsi set_ctrl dbcnt3 T33DC value					// Set dbcnt3 T33DC register
 * lsi set_ctrl dbcnt3 T34DC value					// Set dbcnt3 T34DC register
 * lsi set_ctrl dbcnt3 T35DC value					// Set dbcnt3 T35DC register
 * lsi set_ctrl dbcnt3 T36DC value					// Set dbcnt3 T36DC register
 * lsi set_ctrl dbcnt3 T37DC value					// Set dbcnt3 T37DC register
 * lsi set_ctrl dbcnt3 T38DC value					// Set dbcnt3 T38DC register
 * lsi set_ctrl dbcnt3 T39DC value					// Set dbcnt3 T39DC register
 * lsi set_ctrl dbcnt3 T40DC value					// Set dbcnt3 T40DC register
 * lsi set_ctrl dbcnt3 T41DC value					// Set dbcnt3 T41DC register
 * lsi set_ctrl dbcnt3 T42DC value					// Set dbcnt3 T42DC register
 * lsi set_ctrl dbcnt3 T43DC value					// Set dbcnt3 T43DC register
 * lsi set_ctrl dbcnt3 T44DC value					// Set dbcnt3 T44DC register
 * lsi set_ctrl dbcnt3 T45DC value					// Set dbcnt3 T45DC register
 * lsi set_ctrl dbcnt3 T46DC value					// Set dbcnt3 T46DC register
 * lsi set_ctrl dbcnt3 T47DC value					// Set dbcnt3 T47DC register
 * lsi set_ctrl dbcnt4 T48DC value					// Set dbcnt4 T48DC register
 * lsi set_ctrl dbcnt4 T49DC value					// Set dbcnt4 T49DC register
 * lsi set_ctrl dbcnt4 T50DC value					// Set dbcnt4 T50DC register
 * lsi set_ctrl dbcnt4 T51DC value					// Set dbcnt4 T51DC register
 * lsi set_ctrl dbcnt4 T52DC value					// Set dbcnt4 T52DC register
 * lsi set_ctrl dbcnt4 T53DC value					// Set dbcnt4 T53DC register
 * lsi set_ctrl dbcnt4 T54DC value					// Set dbcnt4 T54DC register
 * lsi set_ctrl dbcnt4 T55DC value					// Set dbcnt4 T55DC register
 * lsi set_ctrl dbcnt4 T56DC value					// Set dbcnt4 T56DC register
 * lsi set_ctrl dbcnt4 T57DC value					// Set dbcnt4 T57DC register
 * lsi set_ctrl dbcnt4 T58DC value					// Set dbcnt4 T58DC register
 * lsi set_ctrl dbcnt4 T59DC value					// Set dbcnt4 T59DC register
 * lsi set_ctrl dbcnt4 T60DC value					// Set dbcnt4 T60DC register
 * lsi set_ctrl dbcnt4 T61DC value					// Set dbcnt4 T61DC register
 * lsi set_ctrl dbcnt4 T62DC value					// Set dbcnt4 T62DC register
 * lsi set_ctrl dbcnt4 T63DC value					// Set dbcnt4 T63DC register
 * lsi set_ctrl dbcnt5 T64DC value					// Set dbcnt5 T64DC register
 * lsi set_ctrl dbcnt5 T65DC value					// Set dbcnt5 T65DC register
 * lsi set_ctrl dbcnt5 T66DC value					// Set dbcnt5 T66DC register
 * 
 * P1  P2        P3     P4   P5
 * clock set_reg clksel1 RCLK value					// Set clksel1 RCLK register
 * clock set_reg clksel1 UHS1CLK0 value				// Set clksel1 UHS1CLK0 register
 * clock set_reg clksel1 UHS1CLK1 value				// Set clksel1 UHS1CLK1 register
 * clock set_reg clksel1 UHS1CLK2 value				// Set clksel1 UHS1CLK2 register
 * clock set_reg clksel1 UHS2CLK value				// Set clksel1 UHS2CLK register
 * clock set_reg clksel1 NFCLK value				// Set clksel1 NFCLK register
 * clock set_reg clksel1 EMMCCLK value				// Set clksel1 EMMCCLK register
 * clock set_reg clksel2 ELACLK value				// Set clksel2 ELACLK register
 * clock set_reg clksel2 JPGCLK value				// Set clksel2 JPGCLK register
 * clock set_reg clksel2 GPUCLK value				// Set clksel2 GPUCLK register
 * clock set_reg clksel2 IPUTMECLK value			// Set clksel2 IPUTMECLK register
 * clock set_reg clksel2 IPUCLK value				// Set clksel2 IPUCLK register
 * clock set_reg clksel2 MIFCLK value				// Set clksel2 MIFCLK register
 * clock set_reg clksel2 HIFCLK value				// Set clksel2 HIFCLK register
 * clock set_reg clksel2 RAWCLK value				// Set clksel2 RAWCLK register
 * clock set_reg clksel3 RIBCLK value				// Set clksel3 RIBCLK register
 * clock set_reg clksel3 VDFCLK value				// Set clksel3 VDFCLK register
 * clock set_reg clksel3 HEVENCCLK value			// Set clksel3 HEVENCCLK register
 * clock set_reg clksel3 IPPCLK value				// Set clksel3 IPPCLK register
 * clock set_reg clksel3 PASCLK value				// Set clksel3 PASCLK register
 * clock set_reg clksel3 IIPCLK value				// Set clksel3 IIPCLK register
 * clock set_reg clksel3 SENMSKCLK value			// Set clksel3 SENMSKCLK register
 * clock set_reg clksel3 SENCLK value				// Set clksel3 SENCLK register
 * clock set_reg clksel3 HEVENCSEL value			// Set clksel3 HEVENCSEL register
 * clock set_reg clksel4 CNR1CLK value				// Set clksel4 CNR1CLK register
 * clock set_reg clksel4 B2R1CLK value				// Set clksel4 B2R1CLK register
 * clock set_reg clksel4 LTM1CLK value				// Set clksel4 LTM1CLK register
 * clock set_reg clksel4 R2Y1CLK value				// Set clksel4 R2Y1CLK register
 * clock set_reg clksel4 SRO1CLK_2 value			// Set clksel4 SRO1CLK_2 register
 * clock set_reg clksel5 LTMRBK1CLK value			// Set clksel5 LTMRBK1CLK register
 * clock set_reg clksel5 B2B1CLK value				// Set clksel5 B2B1CLK register
 * clock set_reg clksel5 SRO1CLK value				// Set clksel5 SRO1CLK register
 * clock set_reg clksel6 CNR2CLK value				// Set clksel6 CNR2CLK register
 * clock set_reg clksel6 B2R2CLK value				// Set clksel6 B2R2CLK register
 * clock set_reg clksel6 LTM2CLK value				// Set clksel6 LTM2CLK register
 * clock set_reg clksel6 R2Y2CLK value				// Set clksel6 R2Y2CLK register
 * clock set_reg clksel6 SRO2CLK_2 value			// Set clksel6 SRO2CLK_2 register
 * clock set_reg clksel7 LTMRBK2CLK value			// Set clksel7 LTMRBK2CLK register
 * clock set_reg clksel7 B2B2CLK value				// Set clksel7 B2B2CLK register
 * clock set_reg clksel7 SRO2CLK value				// Set clksel7 SRO2CLK register
 * clock set_reg clksel7 MIPISEL value				// Set clksel7 MIPISEL register
 * clock set_reg clksel7 PDM0SEL value				// Set clksel7 PDM0SEL register
 * clock set_reg clksel7 PDM1SEL value				// Set clksel7 PDM1SEL register
 * clock set_reg clksel8 DSPCLK value				// Set clksel8 DSPCLK register
 * clock set_reg clksel8 SPICLK value				// Set clksel8 SPICLK register
 * clock set_reg clksel8 AUCLK value				// Set clksel8 AUCLK register
 * clock set_reg clksel8 AU0SEL value				// Set clksel8 AU0SEL register
 * clock set_reg clksel8 AU2SEL value				// Set clksel8 AU2SEL register
 * clock set_reg clksel8 AU3SEL value				// Set clksel8 AU3SEL register
 * clock set_reg clksel8 NETAUSEL value				// Set clksel8 NETAUSEL register
 * clock set_reg clksel8 APCLK value				// Set clksel8 APCLK register
 * clock set_reg clksel8 AP0SEL value				// Set clksel8 AP0SEL register
 * clock set_reg clksel8 AP1SEL value				// Set clksel8 AP1SEL register
 * clock set_reg clksel8 AP2SEL value				// Set clksel8 AP2SEL register
 * clock set_reg clksel8 AP3SEL value				// Set clksel8 AP3SEL register
 * clock set_reg clksel9 PCLK value					// Set clksel9 PCLK register
 * clock set_reg clksel9 HCLK value					// Set clksel9 HCLK register
 * clock set_reg clksel9 HCLKBMH value				// Set clksel9 HCLKBMH register
 * clock set_reg clksel9 ACLKEXS value				// Set clksel9 ACLKEXS register
 * clock set_reg clksel9 ACLK value					// Set clksel9 ACLK register
 * clock set_reg clksel10 ACLK400 value				// Set clksel10 ACLK400 register
 * clock set_reg clksel10 MCLK200 value				// Set clksel10 MCLK200 register
 * clock set_reg clksel10 MCLK400 value				// Set clksel10 MCLK400 register
 * clock set_reg clksel11 DCHREQ value				// Set clksel11 DCHREQ register
 * clock set_reg clksel12 ACLK300 value				// Set clksel12 ACLK300 register
 * clock set_reg clksel12 GYROCLK value				// Set clksel12 GYROCLK register
 * clock set_reg clksel12 FPT0CLK value				// Set clksel12 FPT0CLK register
 * clock set_reg clksel12 FPT1CLK value				// Set clksel12 FPT1CLK register
 * clock set_reg clksel12 MECLK value				// Set clksel12 MECLK register
 * clock set_reg clksel12 NFBCHCLK value			// Set clksel12 NFBCHCLK register
 * clock set_reg clksel12 RIBCLK value				// Set clksel12 RIBCLK register
 * clock set_reg clksel12 SHDRCLK value				// Set clksel12 SHDRCLK register
 * clock set_reg pllcnt1 PL00ST value				// Set pllcnt1 PL00ST register
 * clock set_reg pllcnt1 PL01ST value				// Set pllcnt1 PL01ST register
 * clock set_reg pllcnt1 PL02ST value				// Set pllcnt1 PL02ST register
 * clock set_reg pllcnt1 PL03ST value				// Set pllcnt1 PL03ST register
 * clock set_reg pllcnt1 PL04ST value				// Set pllcnt1 PL04ST register
 * clock set_reg pllcnt1 PL05ST value				// Set pllcnt1 PL05ST register
 * clock set_reg pllcnt1 PL05AST value				// Set pllcnt1 PL05AST register
 * clock set_reg pllcnt1 PL06ST value				// Set pllcnt1 PL06ST register
 * clock set_reg pllcnt1 PL07ST value				// Set pllcnt1 PL07ST register
 * clock set_reg pllcnt1 PL08ST value				// Set pllcnt1 PL08ST register
 * clock set_reg pllcnt1 PL10ST value				// Set pllcnt1 PL10ST register
 * clock set_reg pllcnt1 PL10AST value				// Set pllcnt1 PL10AST register
 * clock set_reg pllcnt1 PL11ST value				// Set pllcnt1 PL11ST register
 * clock set_reg pllcnt1 DPL00ST value				// Set pllcnt1 DPL00ST register
 * clock set_reg pllcnt1 DPL01ST value				// Set pllcnt1 DPL01ST register
 * clock set_reg pllcnt1 DPL02ST value				// Set pllcnt1 DPL02ST register
 * clock set_reg pllcnt1 DPL10ST value				// Set pllcnt1 DPL10ST register
 * clock set_reg pllcnt1 DPL11ST value				// Set pllcnt1 DPL11ST register
 * clock set_reg pllcnt1 DPL12ST value				// Set pllcnt1 DPL12ST register
 * clock set_reg pllcnt2 PL00SEL value				// Set pllcnt2 PL00SEL register
 * clock set_reg pllcnt2 PL01SEL value				// Set pllcnt2 PL01SEL register
 * clock set_reg pllcnt2 PL02SEL value				// Set pllcnt2 PL02SEL register
 * clock set_reg pllcnt2 PL03SEL value				// Set pllcnt2 PL03SEL register
 * clock set_reg pllcnt2 PL04SEL value				// Set pllcnt2 PL04SEL register
 * clock set_reg pllcnt2 PL05SEL value				// Set pllcnt2 PL05SEL register
 * clock set_reg pllcnt2 PL05ASEL value				// Set pllcnt2 PL05ASEL register
 * clock set_reg pllcnt2 PL06SEL value				// Set pllcnt2 PL06SEL register
 * clock set_reg pllcnt2 PL07SEL value				// Set pllcnt2 PL07SEL register
 * clock set_reg pllcnt2 PL08SEL value				// Set pllcnt2 PL08SEL register
 * clock set_reg pllcnt2 PL10SEL value				// Set pllcnt2 PL10SEL register
 * clock set_reg pllcnt2 PL10ASEL value				// Set pllcnt2 PL10ASEL register
 * clock set_reg pllcnt2 PL11SEL value				// Set pllcnt2 PL11SEL register
 * clock set_reg pllcnt2 PL01SSEN value				// Set pllcnt2 PL01SSEN register
 * clock set_reg pllcnt2 PL02SSEN value				// Set pllcnt2 PL02SSEN register
 * clock set_reg pllcnt3 P00POSTDIV value			// Set pllcnt3 P00POSTDIV register
 * clock set_reg pllcnt3 P00PREDIV value			// Set pllcnt3 P00PREDIV register
 * clock set_reg pllcnt3 P00PLLDIV value			// Set pllcnt3 P00PLLDIV register
 * clock set_reg pllcnt4 P00FNUM value				// Set pllcnt4 P00FNUM register
 * clock set_reg pllcnt5 P00FDEN value				// Set pllcnt5 P00FDEN register
 * clock set_reg pllcnt7 P03POSTDIV0 value			// Set pllcnt7 P03POSTDIV0 register
 * clock set_reg pllcnt7 P03POSTDIV1 value			// Set pllcnt7 P03POSTDIV1 register
 * clock set_reg pllcnt7 P03PREDIV value			// Set pllcnt7 P03PREDIV register
 * clock set_reg pllcnt7 P03PLLDIV value			// Set pllcnt7 P03PLLDIV register
 * clock set_reg pllcnt7 P03OC0 value				// Set pllcnt7 P03OC0 register
 * clock set_reg pllcnt7 P03OC1 value				// Set pllcnt7 P03OC1 register
 * clock set_reg pllcnt7 D0XOC value				// Set pllcnt7 D0XOC register
 * clock set_reg pllcnt7 D1XOC value				// Set pllcnt7 D1XOC register
 * clock set_reg pllcnt7 DSEL value					// Set pllcnt7 DSEL register
 * clock set_reg pllcnt8 P04POSTDIV value			// Set pllcnt8 P04POSTDIV register
 * clock set_reg pllcnt8 P04PREDIV value			// Set pllcnt8 P04PREDIV register
 * clock set_reg pllcnt8 P04PLLDIV value			// Set pllcnt8 P04PLLDIV register
 * clock set_reg pllcnt9 P10APLLDIV value			// Set pllcnt9 P10APLLDIV register
 * clock set_reg pllcnt9 P08PLLDIV value			// Set pllcnt9 P08PLLDIV register
 * clock set_reg clkstop1 DSPCK value				// Set clkstop1 DSPCK register
 * clock set_reg clkstop1 DSPAX value				// Set clkstop1 DSPAX register
 * clock set_reg clkstop1 SENCK value				// Set clkstop1 SENCK register
 * clock set_reg clkstop1 SENAX value				// Set clkstop1 SENAX register
 * clock set_reg clkstop1 SENAH value				// Set clkstop1 SENAH register
 * clock set_reg clkstop1 SENAP value				// Set clkstop1 SENAP register
 * clock set_reg clkstop1 GPIOAP value				// Set clkstop1 GPIOAP register
 * clock set_reg clkstop1 AU0CK value				// Set clkstop1 AU0CK register
 * clock set_reg clkstop1 AU2CK value				// Set clkstop1 AU2CK register
 * clock set_reg clkstop1 AU3CK value				// Set clkstop1 AU3CK register
 * clock set_reg clkstop1 AU4CK value				// Set clkstop1 AU4CK register
 * clock set_reg clkstop1 AU5CK value				// Set clkstop1 AU5CK register
 * clock set_reg clkstop1 NETAUCK value				// Set clkstop1 NETAUCK register
 * clock set_reg clkstop1 TEMPCK value				// Set clkstop1 TEMPCK register
 * clock set_reg clkstop2 RCK value					// Set clkstop2 RCK register
 * clock set_reg clkstop2 UHS1CK0 value				// Set clkstop2 UHS1CK0 register
 * clock set_reg clkstop2 UHS1CK1 value				// Set clkstop2 UHS1CK1 register
 * clock set_reg clkstop2 UHS1CK2 value				// Set clkstop2 UHS1CK2 register
 * clock set_reg clkstop2 UHS2CK value				// Set clkstop2 UHS2CK register
 * clock set_reg clkstop2 NFCK value				// Set clkstop2 NFCK register
 * clock set_reg clkstop2 EMMCCK value				// Set clkstop2 EMMCCK register
 * clock set_reg clkstop2 NETSECCK value			// Set clkstop2 NETSECCK register
 * clock set_reg clkstop2 NETRCK value				// Set clkstop2 NETRCK register
 * clock set_reg clkstop2 EXSAX value				// Set clkstop2 EXSAX register
 * clock set_reg clkstop2 SPICK value				// Set clkstop2 SPICK register
 * clock set_reg clkstop2 SLIMB00CK value			// Set clkstop2 SLIMB00CK register
 * clock set_reg clkstop2 SLIMB01CK value			// Set clkstop2 SLIMB01CK register
 * clock set_reg clkstop2 SLIMB10CK value			// Set clkstop2 SLIMB10CK register
 * clock set_reg clkstop2 SLIMB11CK value			// Set clkstop2 SLIMB11CK register
 * clock set_reg clkstop2 PCISUPPCK value			// Set clkstop2 PCISUPPCK register
 * clock set_reg clkstop3 IIPCK value				// Set clkstop3 IIPCK register
 * clock set_reg clkstop3 IIPAP value				// Set clkstop3 IIPAP register
 * clock set_reg clkstop3 IIPAH value				// Set clkstop3 IIPAH register
 * clock set_reg clkstop3 IIPAX value				// Set clkstop3 IIPAX register
 * clock set_reg clkstop3 LCDCK value				// Set clkstop3 LCDCK register
 * clock set_reg clkstop3 HIFCK value				// Set clkstop3 HIFCK register
 * clock set_reg clkstop3 MIFCK value				// Set clkstop3 MIFCK register
 * clock set_reg clkstop3 DISPAP value				// Set clkstop3 DISPAP register
 * clock set_reg clkstop3 DISPAH value				// Set clkstop3 DISPAH register
 * clock set_reg clkstop3 DISPAX value				// Set clkstop3 DISPAX register
 * clock set_reg clkstop3 JPGCK value				// Set clkstop3 JPGCK register
 * clock set_reg clkstop3 JPGAP value				// Set clkstop3 JPGAP register
 * clock set_reg clkstop3 JPGAH value				// Set clkstop3 JPGAH register
 * clock set_reg clkstop3 JPGAX value				// Set clkstop3 JPGAX register
 * clock set_reg clkstop4 GPUCK value				// Set clkstop4 GPUCK register
 * clock set_reg clkstop4 GPUAP value				// Set clkstop4 GPUAP register
 * clock set_reg clkstop4 GPUAH value				// Set clkstop4 GPUAH register
 * clock set_reg clkstop4 GPUAX value				// Set clkstop4 GPUAX register
 * clock set_reg clkstop4 FPT0CK value				// Set clkstop4 FPT0CK register
 * clock set_reg clkstop4 FPT0AP value				// Set clkstop4 FPT0AP register
 * clock set_reg clkstop4 FPT0AH value				// Set clkstop4 FPT0AH register
 * clock set_reg clkstop4 FPT0AX value				// Set clkstop4 FPT0AX register
 * clock set_reg clkstop4 FPT1CK value				// Set clkstop4 FPT1CK register
 * clock set_reg clkstop4 FPT1AP value				// Set clkstop4 FPT1AP register
 * clock set_reg clkstop4 FPT1AH value				// Set clkstop4 FPT1AH register
 * clock set_reg clkstop4 FPT1AX value				// Set clkstop4 FPT1AX register
 * clock set_reg clkstop4 APCK0 value				// Set clkstop4 APCK0 register
 * clock set_reg clkstop4 APCK1 value				// Set clkstop4 APCK1 register
 * clock set_reg clkstop4 APCK2 value				// Set clkstop4 APCK2 register
 * clock set_reg clkstop4 APCK3 value				// Set clkstop4 APCK3 register
 * clock set_reg clkstop5 MICAX0 value				// Set clkstop5 MICAX0 register
 * clock set_reg clkstop5 MICAX1 value				// Set clkstop5 MICAX1 register
 * clock set_reg clkstop5 MICAX2 value				// Set clkstop5 MICAX2 register
 * clock set_reg clkstop5 MICAX3 value				// Set clkstop5 MICAX3 register
 * clock set_reg clkstop5 MICAX4 value				// Set clkstop5 MICAX4 register
 * clock set_reg clkstop5 MICAX5 value				// Set clkstop5 MICAX5 register
 * clock set_reg clkstop5 MICAX6 value				// Set clkstop5 MICAX6 register
 * clock set_reg clkstop5 MICAP0 value				// Set clkstop5 MICAP0 register
 * clock set_reg clkstop5 MICAP1 value				// Set clkstop5 MICAP1 register
 * clock set_reg clkstop5 MICAP2 value				// Set clkstop5 MICAP2 register
 * clock set_reg clkstop5 MICAP3 value				// Set clkstop5 MICAP3 register
 * clock set_reg clkstop5 MICAP4 value				// Set clkstop5 MICAP4 register
 * clock set_reg clkstop5 MICAP5 value				// Set clkstop5 MICAP5 register
 * clock set_reg clkstop5 MICAP6 value				// Set clkstop5 MICAP6 register
 * clock set_reg clkstop6 MICAH1 value				// Set clkstop6 MICAH1 register
 * clock set_reg clkstop6 MICAH2 value				// Set clkstop6 MICAH2 register
 * clock set_reg clkstop6 MICAH3 value				// Set clkstop6 MICAH3 register
 * clock set_reg clkstop6 IMGAX value				// Set clkstop6 IMGAX register
 * clock set_reg clkstop6 IMGAH0 value				// Set clkstop6 IMGAH0 register
 * clock set_reg clkstop6 IMGAH1 value				// Set clkstop6 IMGAH1 register
 * clock set_reg clkstop6 IMGAH3 value				// Set clkstop6 IMGAH3 register
 * clock set_reg clkstop6 IMGAP3 value				// Set clkstop6 IMGAP3 register
 * clock set_reg clkstop6 REGAP value				// Set clkstop6 REGAP register
 * clock set_reg clkstop6 XCHAX value				// Set clkstop6 XCHAX register
 * clock set_reg clkstop6 XCHAP value				// Set clkstop6 XCHAP register
 * clock set_reg clkstop6 ELACK value				// Set clkstop6 ELACK register
 * clock set_reg clkstop6 ELAAX value				// Set clkstop6 ELAAX register
 * clock set_reg clkstop6 ELAAP value				// Set clkstop6 ELAAP register
 * clock set_reg clkstop7 IPUFDCK value				// Set clkstop7 IPUFDCK register
 * clock set_reg clkstop7 IPUVISCK value			// Set clkstop7 IPUVISCK register
 * clock set_reg clkstop7 IPUAX value				// Set clkstop7 IPUAX register
 * clock set_reg clkstop7 IPUAH value				// Set clkstop7 IPUAH register
 * clock set_reg clkstop7 RAWCK value				// Set clkstop7 RAWCK register
 * clock set_reg clkstop7 RAWAX value				// Set clkstop7 RAWAX register
 * clock set_reg clkstop7 RAWAP value				// Set clkstop7 RAWAP register
 * clock set_reg clkstop7 SHDRCK value				// Set clkstop7 SHDRCK register
 * clock set_reg clkstop7 SHDRAX value				// Set clkstop7 SHDRAX register
 * clock set_reg clkstop7 SHDRAH value				// Set clkstop7 SHDRAH register
 * clock set_reg clkstop7 SHDRAP value				// Set clkstop7 SHDRAP register
 * clock set_reg clkstop7 M0CK value				// Set clkstop7 M0CK register
 * clock set_reg clkstop8 RIBCK value				// Set clkstop8 RIBCK register
 * clock set_reg clkstop8 RIBAH value				// Set clkstop8 RIBAH register
 * clock set_reg clkstop8 HEVDFCK value				// Set clkstop8 HEVDFCK register
 * clock set_reg clkstop8 HEVENCCK value			// Set clkstop8 HEVENCCK register
 * clock set_reg clkstop8 HEIPPCK value				// Set clkstop8 HEIPPCK register
 * clock set_reg clkstop8 UMC0HEVCMX2 value			// Set clkstop8 UMC0HEVCMX2 register
 * clock set_reg clkstop8 UMC0HEVCMX4 value			// Set clkstop8 UMC0HEVCMX4 register
 * clock set_reg clkstop8 UMC0RBRMX4 value			// Set clkstop8 UMC0RBRMX4 register
 * clock set_reg clkstop8 UMC1HEVCMX2 value			// Set clkstop8 UMC1HEVCMX2 register
 * clock set_reg clkstop8 UMC1HEVCMX4 value			// Set clkstop8 UMC1HEVCMX4 register
 * clock set_reg clkstop8 UMC1RBRMX4 value			// Set clkstop8 UMC1RBRMX4 register
 * clock set_reg clkstop8 UMC0CMNAX value			// Set clkstop8 UMC0CMNAX register
 * clock set_reg clkstop8 UMC0MX1AX value			// Set clkstop8 UMC0MX1AX register
 * clock set_reg clkstop8 UMC0MX2AX value			// Set clkstop8 UMC0MX2AX register
 * clock set_reg clkstop8 UMC0MX3AX value			// Set clkstop8 UMC0MX3AX register
 * clock set_reg clkstop8 UMC0MX4AX value			// Set clkstop8 UMC0MX4AX register
 * clock set_reg clkstop9 UMC0MX5AX value			// Set clkstop9 UMC0MX5AX register
 * clock set_reg clkstop9 UMC1CMNAX value			// Set clkstop9 UMC1CMNAX register
 * clock set_reg clkstop9 UMC1MX1AX value			// Set clkstop9 UMC1MX1AX register
 * clock set_reg clkstop9 UMC1MX2AX value			// Set clkstop9 UMC1MX2AX register
 * clock set_reg clkstop9 UMC1MX3AX value			// Set clkstop9 UMC1MX3AX register
 * clock set_reg clkstop9 UMC1MX4AX value			// Set clkstop9 UMC1MX4AX register
 * clock set_reg clkstop9 UMC1MX5AX value			// Set clkstop9 UMC1MX5AX register
 * clock set_reg clkstop9 UMC0MX0AX3 value			// Set clkstop9 UMC0MX0AX3 register
 * clock set_reg clkstop9 UMC0MX6AX4 value			// Set clkstop9 UMC0MX6AX4 register
 * clock set_reg clkstop9 UMC0HEVCAX4 value			// Set clkstop9 UMC0HEVCAX4 register
 * clock set_reg clkstop9 UMC1MX0AX3 value			// Set clkstop9 UMC1MX0AX3 register
 * clock set_reg clkstop9 UMC1MX6AX4 value			// Set clkstop9 UMC1MX6AX4 register
 * clock set_reg clkstop9 UMC1HEVCAX4 value			// Set clkstop9 UMC1HEVCAX4 register
 * clock set_reg clkstop9 UMC0AP value				// Set clkstop9 UMC0AP register
 * clock set_reg clkstop9 UMC1AP value				// Set clkstop9 UMC1AP register
 * clock set_reg clkstop10 SRO1CK value				// Set clkstop10 SRO1CK register
 * clock set_reg clkstop10 SRO1CK_2 value			// Set clkstop10 SRO1CK_2 register
 * clock set_reg clkstop10 SRO1AX value				// Set clkstop10 SRO1AX register
 * clock set_reg clkstop10 SRO1AH value				// Set clkstop10 SRO1AH register
 * clock set_reg clkstop10 SRO1AP value				// Set clkstop10 SRO1AP register
 * clock set_reg clkstop10 B2B1CK value				// Set clkstop10 B2B1CK register
 * clock set_reg clkstop10 B2B1AX value				// Set clkstop10 B2B1AX register
 * clock set_reg clkstop10 B2B1AH value				// Set clkstop10 B2B1AH register
 * clock set_reg clkstop10 B2B1AP value				// Set clkstop10 B2B1AP register
 * clock set_reg clkstop10 LTMRBK1CK value			// Set clkstop10 LTMRBK1CK register
 * clock set_reg clkstop10 B2R1CK value				// Set clkstop10 B2R1CK register
 * clock set_reg clkstop10 B2R1AX value				// Set clkstop10 B2R1AX register
 * clock set_reg clkstop10 B2R1AH value				// Set clkstop10 B2R1AH register
 * clock set_reg clkstop10 B2R1AP value				// Set clkstop10 B2R1AP register
 * clock set_reg clkstop11 LTM1CK value				// Set clkstop11 LTM1CK register
 * clock set_reg clkstop11 LTM1AX value				// Set clkstop11 LTM1AX register
 * clock set_reg clkstop11 LTM1AH value				// Set clkstop11 LTM1AH register
 * clock set_reg clkstop11 LTM1AP value				// Set clkstop11 LTM1AP register
 * clock set_reg clkstop11 R2Y1CK value				// Set clkstop11 R2Y1CK register
 * clock set_reg clkstop11 R2Y1AX value				// Set clkstop11 R2Y1AX register
 * clock set_reg clkstop11 R2Y1AH value				// Set clkstop11 R2Y1AH register
 * clock set_reg clkstop11 R2Y1AP value				// Set clkstop11 R2Y1AP register
 * clock set_reg clkstop11 CNR1CK value				// Set clkstop11 CNR1CK register
 * clock set_reg clkstop11 CNR1AX value				// Set clkstop11 CNR1AX register
 * clock set_reg clkstop11 CNR1AP value				// Set clkstop11 CNR1AP register
 * clock set_reg clkstop12 SRO2CK value				// Set clkstop12 SRO2CK register
 * clock set_reg clkstop12 SRO2CK_2 value			// Set clkstop12 SRO2CK_2 register
 * clock set_reg clkstop12 SRO2AX value				// Set clkstop12 SRO2AX register
 * clock set_reg clkstop12 SRO2AH value				// Set clkstop12 SRO2AH register
 * clock set_reg clkstop12 SRO2AP value				// Set clkstop12 SRO2AP register
 * clock set_reg clkstop12 B2B2CK value				// Set clkstop12 B2B2CK register
 * clock set_reg clkstop12 B2B2AX value				// Set clkstop12 B2B2AX register
 * clock set_reg clkstop12 B2B2AH value				// Set clkstop12 B2B2AH register
 * clock set_reg clkstop12 B2B2AP value				// Set clkstop12 B2B2AP register
 * clock set_reg clkstop12 LTMRBK2CK value			// Set clkstop12 LTMRBK2CK register
 * clock set_reg clkstop12 B2R2CK value				// Set clkstop12 B2R2CK register
 * clock set_reg clkstop12 B2R2AX value				// Set clkstop12 B2R2AX register
 * clock set_reg clkstop12 B2R2AH value				// Set clkstop12 B2R2AH register
 * clock set_reg clkstop12 B2R2AP value				// Set clkstop12 B2R2AP register
 * clock set_reg clkstop13 LTM2CK value				// Set clkstop13 LTM2CK register
 * clock set_reg clkstop13 LTM2AX value				// Set clkstop13 LTM2AX register
 * clock set_reg clkstop13 LTM2AH value				// Set clkstop13 LTM2AH register
 * clock set_reg clkstop13 LTM2AP value				// Set clkstop13 LTM2AP register
 * clock set_reg clkstop13 R2Y2CK value				// Set clkstop13 R2Y2CK register
 * clock set_reg clkstop13 R2Y2AX value				// Set clkstop13 R2Y2AX register
 * clock set_reg clkstop13 R2Y2AH value				// Set clkstop13 R2Y2AH register
 * clock set_reg clkstop13 R2Y2AP value				// Set clkstop13 R2Y2AP register
 * clock set_reg clkstop13 CNR2CK value				// Set clkstop13 CNR2CK register
 * clock set_reg clkstop13 CNR2AX value				// Set clkstop13 CNR2AX register
 * clock set_reg clkstop13 CNR2AP value				// Set clkstop13 CNR2AP register
 * clock set_reg clkstop14 STATAX value				// Set clkstop14 STATAX register
 * clock set_reg clkstop14 STATAH value				// Set clkstop14 STATAH register
 * clock set_reg clkstop14 STATAP value				// Set clkstop14 STATAP register
 * clock set_reg clkstop14 PERIAH value				// Set clkstop14 PERIAH register
 * clock set_reg clkstop14 PERIAP value				// Set clkstop14 PERIAP register
 * clock set_reg clkstop14 SENMSKCK value			// Set clkstop14 SENMSKCK register
 * clock set_reg clkstop14 PDMCK value				// Set clkstop14 PDMCK register
 * clock set_reg clkstop14 GYROCK value				// Set clkstop14 GYROCK register
 * clock get_reg clksel1							// Get clksel1 register
 * clock get_reg clksel2							// Get clksel2 register
 * clock get_reg clksel3							// Get clksel3 register
 * clock get_reg clksel4							// Get clksel4 register
 * clock get_reg clksel5							// Get clksel5 register
 * clock get_reg clksel6							// Get clksel6 register
 * clock get_reg clksel7							// Get clksel7 register
 * clock get_reg clksel8							// Get clksel8 register
 * clock get_reg clksel9							// Get clksel9 register
 * clock get_reg clksel10							// Get clksel10 register
 * clock get_reg clksel11							// Get clksel11 register
 * clock get_reg clksel12							// Get clksel12 register
 * clock get_reg pllcnt1							// Get pllcnt1 register
 * clock get_reg pllcnt2							// Get pllcnt2 register
 * clock get_reg pllcnt3							// Get pllcnt3 register
 * clock get_reg pllcnt4							// Get pllcnt4 register
 * clock get_reg pllcnt5							// Get pllcnt5 register
 * clock get_reg pllcnt7							// Get pllcnt7 register
 * clock get_reg pllcnt8							// Get pllcnt8 register
 * clock get_reg pllcnt9							// Get pllcnt9 register
 * clock get_reg clkstop1							// Get clkstop1 register
 * clock get_reg clkstop2							// Get clkstop2 register
 * clock get_reg clkstop3							// Get clkstop3 register
 * clock get_reg clkstop4							// Get clkstop4 register
 * clock get_reg clkstop5							// Get clkstop5 register
 * clock get_reg clkstop6							// Get clkstop6 register
 * clock get_reg clkstop7							// Get clkstop7 register
 * clock get_reg clkstop8							// Get clkstop8 register
 * clock get_reg clkstop9							// Get clkstop9 register
 * clock get_reg clkstop10							// Get clkstop10 register
 * clock get_reg clkstop11							// Get clkstop11 register
 * clock get_reg clkstop12							// Get clkstop12 register
 * clock get_reg clkstop13							// Get clkstop13 register
 * clock get_reg clkstop14							// Get clkstop14 register
 * clock get_clock EMMCCLK value					// Get EMMCCLK register
 * clock get_clock NFCLK value						// Get NFCLK register
 * clock get_clock UHS2CLK value					// Get UHS2CLK register
 * clock get_clock UHS1CLK2 value					// Get UHS1CLK2 register
 * clock get_clock UHS1CLK1 value					// Get UHS1CLK1 register
 * clock get_clock UHS1CLK0 value					// Get UHS1CLK0 register
 * clock get_clock RCLK value						// Get RCLK register
 * clock get_clock RAWCLK value						// Get RAWCLK register
 * clock get_clock HIFCLK value						// Get HIFCLK register
 * clock get_clock MIFCLK value						// Get MIFCLK register
 * clock get_clock IPUCLK value						// Get IPUCLK register
 * clock get_clock IPUTMECLK value					// Get IPUTMECLK register
 * clock get_clock GPUCLK value						// Get GPUCLK register
 * clock get_clock JPGCLK value						// Get JPGCLK register
 * clock get_clock ELACLK value						// Get ELACLK register
 * clock get_clock SENCLK value						// Get SENCLK register
 * clock get_clock SENMSKCLK value					// Get SENMSKCLK register
 * clock get_clock IIPCLK value						// Get IIPCLK register
 * clock get_clock PASCLK value						// Get PASCLK register
 * clock get_clock IPPCLK value						// Get IPPCLK register
 * clock get_clock HEVENCCLK value					// Get HEVENCCLK register
 * clock get_clock VDFCLK value						// Get VDFCLK register
 * clock get_clock RIBCLK value						// Get RIBCLK register
 * clock get_clock SRO1CLK_2 value					// Get SRO1CLK_2 register
 * clock get_clock R2Y1CLK value					// Get R2Y1CLK register
 * clock get_clock SRO1CLK value					// Get SRO1CLK register
 * clock get_clock LTM1CLK value					// Get LTM1CLK register
 * clock get_clock B2R1CLK value					// Get B2R1CLK register
 * clock get_clock CNR1CLK value					// Get CNR1CLK register
 * clock get_clock B2B1CLK value					// Get B2B1CLK register
 * clock get_clock LTMRBK1CLK value					// Get LTMRBK1CLK register
 * clock get_clock SRO2CLK_2 value					// Get SRO2CLK_2 register
 * clock get_clock R2Y2CLK value					// Get R2Y2CLK register
 * clock get_clock LTM2CLK value					// Get LTM2CLK register
 * clock get_clock B2R2CLK value					// Get B2R2CLK register
 * clock get_clock CNR2CLK value					// Get CNR2CLK register
 * clock get_clock SRO2CLK value					// Get SRO2CLK register
 * clock get_clock B2B2CLK value					// Get B2B2CLK register
 * clock get_clock LTMRBK2CLK value					// Get LTMRBK2CLK register
 * clock get_clock APCLK value						// Get APCLK register
 * clock get_clock AUCLK value						// Get AUCLK register
 * clock get_clock SPICLK value						// Get SPICLK register
 * clock get_clock DSPCLK value						// Get DSPCLK register
 * clock get_clock ACLK value						// Get ACLK register
 * clock get_clock ACLKEXS value					// Get ACLKEXS register
 * clock get_clock HCLKBMH value					// Get HCLKBMH register
 * clock get_clock HCLK value						// Get HCLK register
 * clock get_clock PCLK value						// Get PCLK register
 * clock get_clock MCLK400 value					// Get MCLK400 register
 * clock get_clock MCLK200 value					// Get MCLK200 register
 * clock get_clock ACLK400 value					// Get ACLK400 register
 * clock get_clock ACLK300 value					// Get ACLK300 register
 * clock get_clock GYROCLK value					// Get GYROCLK register
 * clock get_clock SHDRCLK value					// Get SHDRCLK register
 * clock get_clock FPT0CLK value					// Get FPT0CLK register
 * clock get_clock FPT1CLK value					// Get FPT1CLK register
 * clock start clkstop1 count value					// Start clkstop1 register
 * clock start clkstop2 count value					// Start clkstop2 register
 * clock start clkstop3 count value					// Start clkstop3 register
 * clock start clkstop4 count value					// Start clkstop4 register
 * clock start clkstop5 count value					// Start clkstop5 register
 * clock start clkstop6 count value					// Start clkstop6 register
 * clock start clkstop7 count value					// Start clkstop7 register
 * clock start clkstop8 count value					// Start clkstop8 register
 * clock start clkstop9 count value					// Start clkstop9 register
 * clock start clkstop10 count value				// Start clkstop10 register
 * clock start clkstop11 count value				// Start clkstop11 register
 * clock start clkstop12 count value				// Start clkstop12 register
 * clock start clkstop13 count value				// Start clkstop13 register
 * clock start clkstop14 count value				// Start clkstop14 register
 * clock stop clkstop1 count value					// Stop clkstop1 register
 * clock stop clkstop2 count value					// Stop clkstop2 register
 * clock stop clkstop3 count value					// Stop clkstop3 register
 * clock stop clkstop4 count value					// Stop clkstop4 register
 * clock stop clkstop5 count value					// Stop clkstop5 register
 * clock stop clkstop6 count value					// Stop clkstop6 register
 * clock stop clkstop7 count value					// Stop clkstop7 register
 * clock stop clkstop8 count value					// Stop clkstop8 register
 * clock stop clkstop9 count value					// Stop clkstop9 register
 * clock stop clkstop10 count value					// Stop clkstop10 register
 * clock stop clkstop11 count value					// Stop clkstop11 register
 * clock stop clkstop12 count value					// Stop clkstop12 register
 * clock stop clkstop13 count value					// Stop clkstop13 register
 * clock stop clkstop14 count value					// Stop clkstop14 register
 * 
 * P1  P2    P3
 * pll pll00 start								// Start pll00 PLL clock
 * pll pll00 stop								// Stop	 pll00 PLL clock
 * pll pll01 start								// Start pll01 PLL clock
 * pll pll01 stop								// Stop	 pll01 PLL clock
 * pll pll02 start								// Start pll02 PLL clock
 * pll pll02 stop								// Stop	 pll02 PLL clock
 * pll pll03 start								// Start pll03 PLL clock
 * pll pll03 stop								// Stop	 pll03 PLL clock
 * pll pll04 start								// Start pll04 PLL clock
 * pll pll04 stop								// Stop	 pll04 PLL clock
 * pll pll05 start								// Start pll05 PLL clock
 * pll pll05 stop								// Stop	 pll05 PLL clock
 * pll pll05a start								// Start pll05a PLL clock
 * pll pll05a stop								// Stop	 pll05a PLL clock
 * pll pll06 start								// Start pll06 PLL clock
 * pll pll06 stop								// Stop	 pll06 PLL clock
 * pll pll07 start								// Start pll07 PLL clock
 * pll pll07 stop								// Stop	 pll07 PLL clock
 * pll pll08 start								// Start pll08 PLL clock
 * pll pll08 stop								// Stop	 pll08 PLL clock
 * pll pll10 start								// Start pll10 PLL clock
 * pll pll10 stop								// Stop	 pll10 PLL clock
 * pll pll10a start								// Start pll10a PLL clock
 * pll pll10a stop								// Stop	 pll10a PLL clock
 * pll pll11 start								// Start pll11 PLL clock
 * pll pll11 stop								// Stop	 pll11 PLL clock
 * pll ddr00 start								// Start ddr00 PLL clock
 * pll ddr00 stop								// Stop	 ddr00 PLL clock
 * pll ddr01 start								// Start ddr01 PLL clock
 * pll ddr01 stop								// Stop	 ddr01 PLL clock
 * pll ddr02 start								// Start ddr02 PLL clock
 * pll ddr02 stop								// Stop	 ddr02 PLL clock
 * pll ddr10 start								// Start ddr10 PLL clock
 * pll ddr10 stop								// Stop	 ddr10 PLL clock
 * pll ddr11 start								// Start ddr11 PLL clock
 * pll ddr11 stop								// Stop	 ddr11 PLL clock
 * pll ddr12 start								// Start ddr12 PLL clock
 * pll ddr12 stop								// Stop	 ddr12 PLL clock
 * pll pl00sel pll_select								// Set pl00sel pll select register
 * pll pl01sel pll_select								// Set pl01sel pll select register
 * pll pl02sel pll_select								// Set pl02sel pll select register
 * pll pl03sel pll_select								// Set pl03sel pll select register
 * pll pl04sel pll_select								// Set pl04sel pll select register
 * pll pl05sel pll_select								// Set pl05sel pll select register
 * pll pl05asel pll_select								// Set pl05asel pll select register
 * pll pl06sel pll_select								// Set pl06sel pll select register
 * pll pl07sel pll_select								// Set pl07sel pll select register
 * pll pl08sel pll_select								// Set pl08sel pll select register
 * pll pl10sel pll_select								// Set pl10sel pll select register
 * pll pl10asel pll_select								// Set pl10asel pll select register
 * pll pl11sel pll_select								// Set pl11sel pll select register
 * pll pl01ssen pll_select								// Set pl01ssen pll select register
 * pll pl02ssen pll_select								// Set pl02ssen pll select register
 * pll p00postdiv pll_select								// Set p00postdiv pll select register
 * pll p00prediv pll_select								// Set p00prediv pll select register
 * pll p00plldiv pll_select								// Set p00plldiv pll select register
 * pll p00fnum pll_select								// Set p00fnum pll select register
 * pll p00fden pll_select								// Set p00fden pll select register
 * pll p03postdiv0 pll_select								// Set p03postdiv0 pll select register
 * pll p03postdiv1 pll_select								// Set p03postdiv1 pll select register
 * pll p03prediv pll_select								// Set p03prediv pll select register
 * pll p03plldiv pll_select								// Set p03plldiv pll select register
 * pll p03oc0 pll_select								// Set p03oc0 pll select register
 * pll p03oc1 pll_select								// Set p03oc1 pll select register
 * pll d0xoc pll_select								// Set d0xoc pll select register
 * pll d1xoc pll_select								// Set d1xoc pll select register
 * pll dodvsel pll_select								// Set dodvsel pll select register
 * pll p04postdiv pll_select								// Set p04postdiv pll select register
 * pll p04prediv pll_select								// Set p04prediv pll select register
 * pll p04plldiv pll_select								// Set p04plldiv pll select register
 * pll p10aplldiv pll_select								// Set p10aplldiv pll select register
 * pll p08plldiv pll_select								// Set p08plldiv pll select register
 * pll err										// API parameter error check

 *
 * P1    P2  P3
 * reset get									// Get CRRSM/CRRRS register
 * reset set CRRSM_WDRST						// Set Watchdog Reset Clear in CRRSM register
 * reset set CRRSM_SWRST						// Set SRREQ Reset Clear in CRRSM register
 * reset set CRRSM_SRST							// Set TSRSTX Terminal Reset Clear in CRRSM register
 * reset set CRRSM_PORST						// Set RSTX Terminal Reset Clear in CRRSM register
 * reset set CRRSM_CPU0_SWRST							// Set CPU0_SR Bit Reset Clear in CRRSM register
 * reset set CRRSM_CPU1_SWRST							// Set CPU1_SR Bit Reset Clear in CRRSM register
 * reset set CRRSM_CPU2_SWRST							// Set CPU2_SR Bit Reset Clear in CRRSM register
 * reset set CRRSM_CPU3_SWRST							// Set CPU3_SR Bit Reset Clear in CRRSM register
 *
 * P1   P2  P3   P4   P5
 * gpio set regi port value						// Set EPCR/PDR/DDR/PUDER/PUDCR register
 * gpio get regi port							// Get EPCR/PDR/DDR/PUDER/PUDCR register
 * gpio test								// Init EPCR/PDR/DDR/PUDER/PUDCR register (0 crear)
 * gpio err										// API parameter error check
 *
 *	 regi:
 *		"EPCR"  :External Port Control Register
 *		"DDR"   :Port Direction Register
 *		"PDR"   :Port Data Register
 *		"PUDER" :Pull-Up/Down Enable Register
 *		"PUDCR" :Pull-Up/Down Control Register
 *
 *	 port:
 *		"Pxx"   ex)"P37"
 */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
/****************
* PUBLIC
*/
CtDdCoes3Help* ct_dd_coes3_help_new(void) 
{
    CtDdCoes3Help *self = k_object_new_with_private(CT_TYPE_DD_COES3_HELP, sizeof(CtDdCoes3HelpPrivate));
    return self;
}
