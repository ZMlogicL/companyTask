/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-9-7 (发布日期)
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


#ifndef  __DD_TOPONE_H__
#define __DD_TOPONE_H__


#include "ddim_typedef.h"
#include "driver_common.h"
#include "chiptop.h"
#include "dd_arm.h"
#include <glib-object.h>


G_BEGIN_DECLS


#define DD_TYPE_TOPONE								(dd_topone_get_type ())
#define DD_TOPONE(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), DD_TYPE_TOPONE, DdTopone))
#define DD_TOPONE_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST((klass), DD_TYPE_TOPONE, DdToponeClass))
#define DD_IS_TOPONE(obj)							(G_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_TOPONE))
#define DD_IS_TOPONE_CLASS(klass)		 		(G_TYPE_CHECK_CLASS_TYPE ((klass), DD_TYPE_TOPONE))
#define DD_TOPONE_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), DD_TYPE_TOPONE, DdToponeClass))

/**
// Error Code
*/
#define	DdTopone_INPUT_PARAM_ERROR		(D_DD_TOP | D_DDIM_INPUT_PARAM_ERROR)	/**< Input parameter error. */
#define	DdTopone_STATUS_ABNORMAL		(D_DD_TOP | D_DDIM_STATUS_ABNORMAL) 	/**< Abnormal status error. */

// Base Clock
#define DdTopone_UCLK40I			(40000000)	/**< Frequency of External Clock UCLK40I port */

// PLL out
#define DdTopone_2200_PLL_OUT		(DdTopone_UCLK40I * 55)					/**< 2200MHz : Frequency of PLL2200 */
#define DdTopone_1600_PLL_OUT		(DdTopone_UCLK40I * 40)					/**< 1600MHz : Frequency of PLL1600 */
#define DdTopone_1500_PLL_OUT		(DdTopone_UCLK40I / 2 * 75)				/**< 1500MHz : Frequency of PLL1500 */
#define DdTopone_1400_PLL_OUT		(DdTopone_UCLK40I * 35)					/**< 1400MHz : Frequency of PLL1400 */
#define DdTopone_1200_PLL_OUT		(DdTopone_UCLK40I * 30)					/**< 1200MHz : Frequency of PLL1200 */
//#define DdTopone_1188_PLL_OUT		(DdTopone_2200_PLL_OUT / 50 * (54 / 2))	/**< 1188MHz : Frequency of PLL1188 */
#define DdTopone_1188_PLL_OUT		(DdTopone_UCLK40I * 11 / 10 * 27)		/**< 1188MHz : Frequency of PLL1188 */
#define DdTopone_864_PLL_OUT		(DdTopone_UCLK40I / 5 * 108)			/**< 864MHz : Frequency of PLL864 */
#define DdTopone_Audio_96_PLL_OUT	(DdTopone_864_PLL_OUT / 125 * 96)	/**< 663.552MHz : Frequency of Audio PLL */
#define DdTopone_Audio_98_PLL_OUT	(DdTopone_864_PLL_OUT / 125 * 98)	/**< 677.376MHz : Frequency of Audio PLL */
#define DdTopone_Audio_128_PLL_OUT	(DdTopone_864_PLL_OUT / 125 * 128)	/**< 884.736MHz : Frequency of Audio PLL */


// CLKSTOP-1
#define	DdTopone_DSPCK_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_DSPAX_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_SENCK_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_SENAX_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_SENAH_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_SENAP_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_GPIOAP_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_AU0CK_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_AU2CK_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_AU3CK_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_AU4CK_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_AU5CK_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_NETAUCK_BIT		(1<<24)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopone_TEMPCK_BIT		(1<<28)		/**< Bit Location of * on CLKSTOP-1 */

// CLKSTOP-2
#define	DdTopone_RCK_BIT					(1<<0)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_UHS1CK0_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_UHS1CK1_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_UHS1CK2_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_UHS2CK_BIT				(1<<8)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_NFCK_BIT					(1<<10)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_EMMCCK_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_NETSECCK_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_NETRCK_BIT				(1<<16)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_EXSAX_BIT				(1<<18)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_SPICK_BIT				(1<<20)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_SLIMB00CK_BIT		(1<<22)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_SLIMB01CK_BIT		(1<<24)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_SLIMB10CK_BIT		(1<<26)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_SLIMB11CK_BIT		(1<<28)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopone_PCISUPPCK_BIT		(1<<30)		/**< Bit Location of * on CLKSTOP-2 */

// CLKSTOP-3
#define	DdTopone_IIPCK_BIT				(1<<0)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_IIPAP_BIT				(1<<2)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_IIPAH_BIT				(1<<4)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_IIPAX_BIT				(1<<6)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_LCDCK_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_HIFCK_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_MIFCK_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_DISPAP_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_DISPAH_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_DISPAX_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_JPGCK_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_JPGAX_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_JPGAH_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_JPGAP_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_PDM0CK_BIT			(1<<28)		/**< Bit Location of * on CLKSTOP-3 */
#define	DdTopone_PDM1CK_BIT			(1<<30)		/**< Bit Location of * on CLKSTOP-3 */

// CLKSTOP-4
#define	DdTopone_GPUCK_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_GPUAP_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_GPUAH_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_GPUAX_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_FPT0CK_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_FPT0AX_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_FPT0AH_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_FPT0AP_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_FPT1CK_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_FPT1AP_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_FPT1AH_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_FPT1AX_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_APCK0_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_APCK1_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_APCK2_BIT			(1<<28)		/**< Bit Location of * on CLKSTOP-4 */
#define	DdTopone_APCK3_BIT			(1<<30)		/**< Bit Location of * on CLKSTOP-4 */

// CLKSTOP-5
#define	DdTopone_MICAX0_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAX1_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAX2_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAX3_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAX4_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAX5_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAX6_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAP0_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAP1_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAP2_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAP3_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAP4_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAP5_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopone_MICAP6_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-5 */

// CLKSTOP-6
#define	DdTopone_MICAH1_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_MICAH2_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_MICAH3_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_IMGAX_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_IMGAH0_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_IMGAH1_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_IMGAH3_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_IMGAP3_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_REGAP_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_XCHAX_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_XCHAP_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_ELACK_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_ELAAX_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopone_ELAAP_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-6 */

// CLKSTOP-7
#define	DdTopone_IPUFDCK_BIT		(1<<0)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_IPUVISCK_BIT		(1<<2)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_IPUAX_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_IPUAH_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_RAWCK_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_RAWAX_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_RAWAP_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_SHDRCK_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_SHDRAX_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_SHDRAH_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_SHDRAP_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_M0CK_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_MECK_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_MEAX_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopone_MEAP_BIT			(1<<28)		/**< Bit Location of * on CLKSTOP-7 */

// CLKSTOP-8
#define	DdTopone_RIBCK_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_RIBAH_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_HEVDFCK_BIT		(1<<4)		/**< Bit Location of * on CLKSTOP-8 */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define	DdTopone_HEPXFCK_BIT		(1<<6)		/**< Bit Location of * on CLKSTOP-8 */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdTopone_HEVENCCK_BIT		(1<<6)		/**< Bit Location of * on CLKSTOP-8 */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define	DdTopone_HEIPPCK_BIT		(1<<8)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC0HEVCMX2_BIT	(1<<10)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC0HEVCMX4_BIT	(1<<12)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC0RBRMX4_BIT		(1<<14)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC1HEVCMX2_BIT	(1<<16)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC1HEVCMX4_BIT	(1<<18)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC1RBRMX4_BIT		(1<<20)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC0CMNAX_BIT		(1<<22)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC0MX1AX_BIT		(1<<24)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC0MX2AX_BIT		(1<<26)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC0MX3AX_BIT		(1<<28)		/**< Bit Location of * on CLKSTOP-8 */
#define	DdTopone_UMC0MX4AX_BIT		(1<<30)		/**< Bit Location of * on CLKSTOP-8 */

// CLKSTOP-9
#define	DdTopone_UMC0MX5AX_BIT		(1<<0)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1CMNAX_BIT		(1<<2)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1MX1AX_BIT		(1<<4)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1MX2AX_BIT		(1<<6)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1MX3AX_BIT		(1<<8)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1MX4AX_BIT		(1<<10)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1MX5AX_BIT		(1<<12)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC0MX0AX3_BIT		(1<<14)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC0MX6AX4_BIT		(1<<16)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC0HEVCAX4_BIT	(1<<18)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1MX0AX3_BIT		(1<<20)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1MX6AX4_BIT		(1<<22)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1HEVCAX4_BIT	(1<<24)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC0AP_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-9 */
#define	DdTopone_UMC1AP_BIT			(1<<28)		/**< Bit Location of * on CLKSTOP-9 */

// CLKSTOP-10
#define	DdTopone_SRO1CK_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_SRO1CK_2_BIT		(1<<2)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_SRO1AX_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_SRO1AH_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_SRO1AP_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_B2B1CK_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_B2B1AX_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_B2B1AH_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_B2B1AP_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_LTMRBK1CK_BIT		(1<<18)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_B2R1CK_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_B2R1AX_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_B2R1AH_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-10 */
#define	DdTopone_B2R1AP_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-10 */

// CLKSTOP-11
#define	DdTopone_LTM1CK_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_LTM1AX_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_LTM1AH_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_LTM1AP_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_R2Y1CK_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_R2Y1AX_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_R2Y1AH_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_R2Y1AP_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_CNR1CK_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_CNR1AX_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_CNR1AP_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_APAH_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_DBGAP_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-11 */
#define	DdTopone_NFBCHCK_BIT		(1<<26)		/**< Bit Location of * on CLKSTOP-11 */

// CLKSTOP-12
#define	DdTopone_SRO2CK_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_SRO2CK_2_BIT		(1<<2)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_SRO2AX_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_SRO2AH_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_SRO2AP_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_B2B2CK_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_B2B2AX_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_B2B2AH_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_B2B2AP_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_LTMRBK2CK_BIT		(1<<18)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_B2R2CK_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_B2R2AX_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_B2R2AH_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-12 */
#define	DdTopone_B2R2AP_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-12 */

// CLKSTOP-13
#define	DdTopone_LTM2CK_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_LTM2AX_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_LTM2AH_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_LTM2AP_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_R2Y2CK_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_R2Y2AX_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_R2Y2AH_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_R2Y2AP_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_CNR2CK_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_CNR2AX_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_CNR2AP_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_UMCVDFMX4_BIT		(1<<22)		/**< Bit Location of * on CLKSTOP-13 */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define	DdTopone_UMCPXFMX4_BIT		(1<<24)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_UMCVDFMX2_BIT		(1<<26)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_UMCPXFMX2_BIT		(1<<28)		/**< Bit Location of * on CLKSTOP-13 */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdTopone_UMCHEVENCAX4_BIT	(1<<24)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_UMCVDFMX2_BIT		(1<<26)		/**< Bit Location of * on CLKSTOP-13 */
#define	DdTopone_HEVENCAP_BIT		(1<<28)		/**< Bit Location of * on CLKSTOP-13 */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define	DdTopone_BMH1CK_BIT			(1<<30)		/**< Bit Location of * on CLKSTOP-13 */

// CLKSTOP-14
#define	DdTopone_STATAX_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_STATAH_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_STATAP_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_PERIAH_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_PERIAP_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_SENMSKCK_BIT		(1<<10)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_GYROCK_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_EXSAH_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_EXSAP_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_PASCK_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_BMH0CK_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_BMH0AX_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_RDMAAX_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_RDMAAP_BIT			(1<<28)		/**< Bit Location of * on CLKSTOP-14 */
#define	DdTopone_BMH1AX_BIT			(1<<30)		/**< Bit Location of * on CLKSTOP-14 */

// CLKSEL
#define	DdTopone_GET_CLKSEL1()					(IO_CHIPTOP.CLKSEL1.word)												/**< Get Clock Select  */
#define	DdTopone_GET_CLKSEL2()				(IO_CHIPTOP.CLKSEL2.word)													/**< Get Clock Select 2 */
#define	DdTopone_GET_CLKSEL3()				(IO_CHIPTOP.CLKSEL3.word)													/**< Get Clock Select 3 */
#define	DdTopone_GET_CLKSEL4()				(IO_CHIPTOP.CLKSEL4.word)													/**< Get Clock Select 4 */
#define	DdTopone_GET_CLKSEL5()				(IO_CHIPTOP.CLKSEL5.word)													/**< Get Clock Select 5 */
#define	DdTopone_GET_CLKSEL6()				(IO_CHIPTOP.CLKSEL6.word)													/**< Get Clock Select 6 */
#define	DdTopone_GET_CLKSEL7()				(IO_CHIPTOP.CLKSEL7.word)													/**< Get Clock Select 7 */
#define	DdTopone_GET_CLKSEL8()				(IO_CHIPTOP.CLKSEL8.word)													/**< Get Clock Select 8 */
#define	DdTopone_GET_CLKSEL9()				(IO_CHIPTOP.CLKSEL9.word)													/**< Get Clock Select 9 */
#define	DdTopone_GET_CLKSEL10()				(IO_CHIPTOP.CLKSEL10.word)													/**< Get Clock Select 10 */
#define	DdTopone_GET_CLKSEL11()				(IO_CHIPTOP.CLKSEL11.word)													/**< Get Clock Select 11 */
#define	DdTopone_GET_CLKSEL12()				(IO_CHIPTOP.CLKSEL12.word)													/**< Get Clock Select 12 */


// CLKSEL1
#define	DdTopone_GET_CLKSEL1_RCLK()			(IO_CHIPTOP.CLKSEL1.bit.RCLK&0x03)											/**< Get Peripheral Clock Select */
#define	DdTopone_SET_CLKSEL1_RCLK(val)		(IO_CHIPTOP.CLKSEL1.bit.RCLK=(0x04|val))									/**< Set Peripheral Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL1_UHS1CLK0()		(IO_CHIPTOP.CLKSEL1.bit.UHS1CLK0&0x0F)										/**< Get UHS1 ch0 Clock Select */
#define	DdTopone_SET_CLKSEL1_UHS1CLK0(val)	(IO_CHIPTOP.CLKSEL1.bit.UHS1CLK0=(0x10|val))								/**< Set UHS1 ch0 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL1_UHS1CLK1()		(IO_CHIPTOP.CLKSEL1.bit.UHS1CLK1&0x0F)										/**< Get UHS1 ch1 Clock Select */
#define	DdTopone_SET_CLKSEL1_UHS1CLK1(val)	(IO_CHIPTOP.CLKSEL1.bit.UHS1CLK1=(0x10|val))								/**< Set UHS1 ch1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL1_UHS1CLK2()		(IO_CHIPTOP.CLKSEL1.bit.UHS1CLK2&0x0F)										/**< Get UHS1 ch2 Clock Select */
#define	DdTopone_SET_CLKSEL1_UHS1CLK2(val)	(IO_CHIPTOP.CLKSEL1.bit.UHS1CLK2=(0x10|val))								/**< Set UHS1 ch2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL1_UHS2CLK()		(IO_CHIPTOP.CLKSEL1.bit.UHS2CLK&0x07)										/**< Get UHS2 Clock Select */
#define	DdTopone_SET_CLKSEL1_UHS2CLK(val)		(IO_CHIPTOP.CLKSEL1.bit.UHS2CLK=(0x08|val))									/**< Set UHS2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL1_NFCLK()			(IO_CHIPTOP.CLKSEL1.bit.NFCLK&0x1F)											/**< Get Nand Flash I/F Clock Select */
#define	DdTopone_SET_CLKSEL1_NFCLK(val)		(IO_CHIPTOP.CLKSEL1.bit.NFCLK=(0x20|val))									/**< Set Nand Flash I/F Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL1_EMMCCLK()		(IO_CHIPTOP.CLKSEL1.bit.EMMCCLK&0x03)										/**< Get eMMC I/F Clock Select */
#define	DdTopone_SET_CLKSEL1_EMMCCLK(val)		(IO_CHIPTOP.CLKSEL1.bit.EMMCCLK=(0x04|val))									/**< Set eMMC I/F Clock Select (Set write bit internally) */
// CLKSEL2
#define	DdTopone_GET_CLKSEL2_ELACLK()			(IO_CHIPTOP.CLKSEL2.bit.ELACLK&0x07)										/**< Get ELA Clock Select */
#define	DdTopone_SET_CLKSEL2_ELACLK(val)		(IO_CHIPTOP.CLKSEL2.bit.ELACLK=(0x08|val))									/**< Set ELA Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL2_JPGCLK()			(IO_CHIPTOP.CLKSEL2.bit.JPGCLK&0x07)										/**< Get JPEG Clock Select */
#define	DdTopone_SET_CLKSEL2_JPGCLK(val)		(IO_CHIPTOP.CLKSEL2.bit.JPGCLK=(0x08|val))									/**< Set JPEG Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL2_GPUCLK()			(IO_CHIPTOP.CLKSEL2.bit.GPUCLK&0x07)										/**< Get GPU Clock Select */
#define	DdTopone_SET_CLKSEL2_GPUCLK(val)		(IO_CHIPTOP.CLKSEL2.bit.GPUCLK=(0x08|val))									/**< Set GPU Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL2_IPUTMECLK()		(IO_CHIPTOP.CLKSEL2.bit.IPUTMECLK&0x07)										/**< Get IPU TME Clock Select */
#define	DdTopone_SET_CLKSEL2_IPUTMECLK(val)	(IO_CHIPTOP.CLKSEL2.bit.IPUTMECLK=(0x08|val))								/**< Set IPU TME Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL2_IPUCLK()			(IO_CHIPTOP.CLKSEL2.bit.IPUCLK&0x07)										/**< Get IPU System Clock Select */
#define	DdTopone_SET_CLKSEL2_IPUCLK(val)		(IO_CHIPTOP.CLKSEL2.bit.IPUCLK=(0x08|val))									/**< Set IPU System Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL2_MIFCLK()			(IO_CHIPTOP.CLKSEL2.bit.MIFCLK&0x07)										/**< Get DISP macro MIF Clock Select */
#define	DdTopone_SET_CLKSEL2_MIFCLK(val)		(IO_CHIPTOP.CLKSEL2.bit.MIFCLK=(0x08|val))									/**< Set DISP macro MIF Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL2_HIFCLK()			(IO_CHIPTOP.CLKSEL2.bit.HIFCLK&0x07)										/**< Get DISP macro HIF Clock Select */
#define	DdTopone_SET_CLKSEL2_HIFCLK(val)		(IO_CHIPTOP.CLKSEL2.bit.HIFCLK=(0x08|val))									/**< Set DISP macro HIF Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL2_RAWCLK()			(IO_CHIPTOP.CLKSEL2.bit.RAWCLK&0x03)										/**< Get RAW macro Clock Select */
#define	DdTopone_SET_CLKSEL2_RAWCLK(val)		(IO_CHIPTOP.CLKSEL2.bit.RAWCLK=(0x04|val))									/**< Set RAW macro Clock Select (Set write bit internally) */
// CLKSEL3
#define	DdTopone_GET_CLKSEL3_VDFCLK()			(IO_CHIPTOP.CLKSEL3.bit.VDFCLK&0x07)										/**< Get HEVC macro VXF Clock Select */
#define	DdTopone_SET_CLKSEL3_VDFCLK(val)		(IO_CHIPTOP.CLKSEL3.bit.VDFCLK=(0x08|val))									/**< Set HEVC macro VXF Clock Select (Set write bit internally) */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define	DdTopone_GET_CLKSEL3_PXFCLK()			(IO_CHIPTOP.CLKSEL3.bit.PXFCLK&0x07)										/**< Get HEVC macro PXF Clock Select */
#define	DdTopone_SET_CLKSEL3_PXFCLK(val)		(IO_CHIPTOP.CLKSEL3.bit.PXFCLK=(0x08|val))									/**< Set HEVC macro PXF Clock Select (Set write bit internally) */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdTopone_GET_CLKSEL3_HEVENCCLK()		(IO_CHIPTOP.CLKSEL3.bit.HEVENCCLK&0x07)										/**< Get HEVC macro ENC Clock Select */
#define	DdTopone_SET_CLKSEL3_HEVENCCLK(val)	(IO_CHIPTOP.CLKSEL3.bit.HEVENCCLK=(0x08|val))								/**< Set HEVC macro ENC Clock Select (Set write bit internally) */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define	DdTopone_GET_CLKSEL3_IPPCLK()			(IO_CHIPTOP.CLKSEL3.bit.IPPCLK&0x0F)										/**< Get HEVC macro IPP Clock Select */
#define	DdTopone_SET_CLKSEL3_IPPCLK(val)		(IO_CHIPTOP.CLKSEL3.bit.IPPCLK=(0x10|val))									/**< Set HEVC macro IPP Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL3_PASCLK()			(IO_CHIPTOP.CLKSEL3.bit.PASCLK&0x07)										/**< Get STAT macro Clock Select */
#define	DdTopone_SET_CLKSEL3_PASCLK(val)		(IO_CHIPTOP.CLKSEL3.bit.PASCLK=(0x08|val))									/**< Set STAT macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL3_IIPCLK()			(IO_CHIPTOP.CLKSEL3.bit.IIPCLK&0x07)										/**< Get IIP macro Clock Select */
#define	DdTopone_SET_CLKSEL3_IIPCLK(val)		(IO_CHIPTOP.CLKSEL3.bit.IIPCLK=(0x08|val))									/**< Set IIP macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL3_SENMSKCLK()		(IO_CHIPTOP.CLKSEL3.bit.SENMSKCLK&0x01)										/**< Get SENSOR macro Clock Select */
#define	DdTopone_SET_CLKSEL3_SENMSKCLK(val)	(IO_CHIPTOP.CLKSEL3.bit.SENMSKCLK=(0x02|val))								/**< Set SENSOR macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL3_SENCLK()			(IO_CHIPTOP.CLKSEL3.bit.SENCLK&0x07)										/**< Get SENSOR macro Clock Select */
#define	DdTopone_SET_CLKSEL3_SENCLK(val)		(IO_CHIPTOP.CLKSEL3.bit.SENCLK=(0x08|val))									/**< Set SENSOR macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL3_PIPESEL()		(IO_CHIPTOP.CLKSEL3.bit.PIPESEL&0x01)										/**< Get Source clock of image pipe macro Select */
#define	DdTopone_SET_CLKSEL3_PIPESEL(val)		(IO_CHIPTOP.CLKSEL3.bit.PIPESEL=(0x02|val))									/**< Set Source clock of image pipe macro Select (Set write bit internally) */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdTopone_GET_CLKSEL3_HEVENCSEL()		(IO_CHIPTOP.CLKSEL3.bit.HEVENCSEL&0x01)										/**< Get HEVENC macro Select */
#define	DdTopone_SET_CLKSEL3_HEVENCSEL(val)	(IO_CHIPTOP.CLKSEL3.bit.HEVENCSEL=(0x02|val))								/**< Set HEVENC macro Select (Set write bit internally) */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// CLKSEL4
#define	DdTopone_GET_CLKSEL4_CNR1CLK()		(IO_CHIPTOP.CLKSEL4.bit.CNR1CLK&0x3F)										/**< Get CNR macro pipe1 Clock Select */
#define	DdTopone_SET_CLKSEL4_CNR1CLK(val)		(IO_CHIPTOP.CLKSEL4.bit.CNR1CLK=(0x40|val))									/**< Set CNR macro pipe1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL4_B2R1CLK()		(IO_CHIPTOP.CLKSEL4.bit.B2R1CLK&0x3F)										/**< Get B2R macro pipe1 Clock Select */
#define	DdTopone_SET_CLKSEL4_B2R1CLK(val)		(IO_CHIPTOP.CLKSEL4.bit.B2R1CLK=(0x40|val))									/**< Set B2R macro pipe1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL4_LTM1CLK()		(IO_CHIPTOP.CLKSEL4.bit.LTM1CLK&0x3F)										/**< Get LTM macro pipe1 Clock Select */
#define	DdTopone_SET_CLKSEL4_LTM1CLK(val)		(IO_CHIPTOP.CLKSEL4.bit.LTM1CLK=(0x40|val))									/**< Set LTM macro pipe1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL4_R2Y1CLK()		(IO_CHIPTOP.CLKSEL4.bit.R2Y1CLK&0x3F)										/**< Get R2Y macro pipe1 Clock Select */
#define	DdTopone_SET_CLKSEL4_R2Y1CLK(val)		(IO_CHIPTOP.CLKSEL4.bit.R2Y1CLK=(0x40|val))									/**< Set R2Y macro pipe1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL4_SRO1CLK_2()		(IO_CHIPTOP.CLKSEL4.bit.SRO1CLK_2&0x07)										/**< Get SRO macro pipe1 input2 Clock Select */
#define	DdTopone_SET_CLKSEL4_SRO1CLK_2(val)	(IO_CHIPTOP.CLKSEL4.bit.SRO1CLK_2=(0x08|val))								/**< Set SRO macro pipe1 input2 Clock Select (Set write bit internally) */
// CLKSEL5
#define	DdTopone_GET_CLKSEL5_LTMRBK1CLK()		(IO_CHIPTOP.CLKSEL5.bit.LTMRBK1CLK&0x1F)									/**< Get LTMRBK macro pipe1 Clock Select */
#define	DdTopone_SET_CLKSEL5_LTMRBK1CLK(val)	(IO_CHIPTOP.CLKSEL5.bit.LTMRBK1CLK=(0x20|val))								/**< Set LTMRBK macro pipe1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL5_B2B1CLK()		(IO_CHIPTOP.CLKSEL5.bit.B2B1CLK&0x1F)										/**< Get B2B macro pipe1 Clock Select */
#define	DdTopone_SET_CLKSEL5_B2B1CLK(val)		(IO_CHIPTOP.CLKSEL5.bit.B2B1CLK=(0x20|val))									/**< Set B2B macro pipe1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL5_SRO1CLK()		(IO_CHIPTOP.CLKSEL5.bit.SRO1CLK&0x0F)										/**< Get SRO macro pipe1 Clock Select */
#define	DdTopone_SET_CLKSEL5_SRO1CLK(val)		(IO_CHIPTOP.CLKSEL5.bit.SRO1CLK=(0x10|val))									/**< Set SRO macro pipe1 Clock Select (Set write bit internally) */
// CLKSEL6
#define	DdTopone_GET_CLKSEL6_CNR2CLK()		(IO_CHIPTOP.CLKSEL6.bit.CNR2CLK&0x3F)										/**< Get CNR macro pipe2 Clock Select */
#define	DdTopone_SET_CLKSEL6_CNR2CLK(val)		(IO_CHIPTOP.CLKSEL6.bit.CNR2CLK=(0x40|val))									/**< Set CNR macro pipe2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL6_B2R2CLK()		(IO_CHIPTOP.CLKSEL6.bit.B2R2CLK&0x3F)										/**< Get B2R macro pipe2 Clock Select */
#define	DdTopone_SET_CLKSEL6_B2R2CLK(val)		(IO_CHIPTOP.CLKSEL6.bit.B2R2CLK=(0x40|val))									/**< Set B2R macro pipe2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL6_LTM2CLK()		(IO_CHIPTOP.CLKSEL6.bit.LTM2CLK&0x3F)										/**< Get LTM macro pipe2 Clock Select */
#define	DdTopone_SET_CLKSEL6_LTM2CLK(val)		(IO_CHIPTOP.CLKSEL6.bit.LTM2CLK=(0x40|val))									/**< Set LTM macro pipe2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL6_R2Y2CLK()		(IO_CHIPTOP.CLKSEL6.bit.R2Y2CLK&0x3F)										/**< Get R2Y macro pipe2 Clock Select */
#define	DdTopone_SET_CLKSEL6_R2Y2CLK(val)		(IO_CHIPTOP.CLKSEL6.bit.R2Y2CLK=(0x40|val))									/**< Set R2Y macro pipe2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL6_SRO2CLK_2()		(IO_CHIPTOP.CLKSEL6.bit.SRO2CLK_2&0x07)										/**< Get SRO macro pipe2 input2 Clock Select */
#define	DdTopone_SET_CLKSEL6_SRO2CLK_2(val)	(IO_CHIPTOP.CLKSEL6.bit.SRO2CLK_2=(0x08|val))								/**< Set SRO macro pipe2 input2 Clock Select (Set write bit internally) */
// CLKSEL7
#define	DdTopone_GET_CLKSEL7_LTMRBK2CLK()		(IO_CHIPTOP.CLKSEL7.bit.LTMRBK2CLK&0x1F)									/**< Get LTMRBK macro pipe2 Clock Select */
#define	DdTopone_SET_CLKSEL7_LTMRBK2CLK(val)	(IO_CHIPTOP.CLKSEL7.bit.LTMRBK2CLK=(0x20|val))								/**< Set LTMRBK macro pipe2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL7_B2B2CLK()		(IO_CHIPTOP.CLKSEL7.bit.B2B2CLK&0x1F)										/**< Get B2B macro pipe2 Clock Select */
#define	DdTopone_SET_CLKSEL7_B2B2CLK(val)		(IO_CHIPTOP.CLKSEL7.bit.B2B2CLK=(0x20|val))									/**< Set B2B macro pipe2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL7_SRO2CLK()		(IO_CHIPTOP.CLKSEL7.bit.SRO2CLK&0x0F)										/**< Get SRO macro pipe2 Clock Select */
#define	DdTopone_SET_CLKSEL7_SRO2CLK(val)		(IO_CHIPTOP.CLKSEL7.bit.SRO2CLK=(0x10|val))									/**< Set SRO macro pipe2 Clock Select (Set write bit internally) */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdTopone_GET_CLKSEL7_MIPISEL()		(IO_CHIPTOP.CLKSEL7.bit.MIPISEL&0x01)										/**< Get MIPI Clock Select */
#define	DdTopone_SET_CLKSEL7_MIPISEL(val)		(IO_CHIPTOP.CLKSEL7.bit.MIPISEL=(0x02|val))									/**< Set MIPI Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL7_PDM0SEL()		(IO_CHIPTOP.CLKSEL7.bit.PDM0SEL&0x03)										/**< Get PDM0 Clock Select */
#define	DdTopone_SET_CLKSEL7_PDM0SEL(val)		(IO_CHIPTOP.CLKSEL7.bit.PDM0SEL=(0x04|val))									/**< Set PDM0 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL7_PDM1SEL()		(IO_CHIPTOP.CLKSEL7.bit.PDM1SEL&0x03)										/**< Get PDM1 Clock Select */
#define	DdTopone_SET_CLKSEL7_PDM1SEL(val)		(IO_CHIPTOP.CLKSEL7.bit.PDM1SEL=(0x04|val))									/**< Set PDM1 Clock Select (Set write bit internally) */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// CLKSEL8
#define	DdTopone_GET_CLKSEL8_DSPCLK()			(IO_CHIPTOP.CLKSEL8.bit.DSPCLK&0x03)										/**< Get DSP macro Clock Select */
#define	DdTopone_SET_CLKSEL8_DSPCLK(val)		(IO_CHIPTOP.CLKSEL8.bit.DSPCLK=(0x04|val))									/**< Set DSP macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_SPICLK()			(IO_CHIPTOP.CLKSEL8.bit.SPICLK&0x03)										/**< Get SPI macro Clock Select */
#define	DdTopone_SET_CLKSEL8_SPICLK(val)		(IO_CHIPTOP.CLKSEL8.bit.SPICLK=(0x04|val))									/**< Set SPI macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_AUCLK()			(IO_CHIPTOP.CLKSEL8.bit.AUCLK&0x03)											/**< Get audio Clock Select */
#define	DdTopone_SET_CLKSEL8_AUCLK(val)		(IO_CHIPTOP.CLKSEL8.bit.AUCLK=(0x04|val))									/**< Set audio Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_AU0SEL()			(IO_CHIPTOP.CLKSEL8.bit.AU0SEL&0x01)										/**< Get audio macro 0ch Clock Select */
#define	DdTopone_SET_CLKSEL8_AU0SEL(val)		(IO_CHIPTOP.CLKSEL8.bit.AU0SEL=(0x02|val))									/**< Set audio macro 0ch Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_AU2SEL()			(IO_CHIPTOP.CLKSEL8.bit.AU2SEL&0x01)										/**< Get audio macro 2ch Clock Select */
#define	DdTopone_SET_CLKSEL8_AU2SEL(val)		(IO_CHIPTOP.CLKSEL8.bit.AU2SEL=(0x02|val))									/**< Set audio macro 2ch Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_AU3SEL()			(IO_CHIPTOP.CLKSEL8.bit.AU3SEL&0x01)										/**< Get audio macro 3ch Clock Select */
#define	DdTopone_SET_CLKSEL8_AU3SEL(val)		(IO_CHIPTOP.CLKSEL8.bit.AU3SEL=(0x02|val))									/**< Set audio macro 3ch Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_NETAUSEL()		(IO_CHIPTOP.CLKSEL8.bit.NETAUSEL&0x01)										/**< Get NETSEC macro Clock Select */
#define	DdTopone_SET_CLKSEL8_NETAUSEL(val)	(IO_CHIPTOP.CLKSEL8.bit.NETAUSEL=(0x02|val))								/**< Set NETSEC macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_APCLK()			(IO_CHIPTOP.CLKSEL8.bit.APCLK&0x1F)											/**< Get APCLK Clock Select */
#define	DdTopone_SET_CLKSEL8_APCLK(val)		(IO_CHIPTOP.CLKSEL8.bit.APCLK=(0x20|val))									/**< Set APCLK Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_AP0SEL()			(IO_CHIPTOP.CLKSEL8.bit.AP0SEL&0x01)										/**< Get SNAPCLKO0 Clock Select */
#define	DdTopone_SET_CLKSEL8_AP0SEL(val)		(IO_CHIPTOP.CLKSEL8.bit.AP0SEL=(0x02|val))									/**< Set SNAPCLKO0 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_AP1SEL()			(IO_CHIPTOP.CLKSEL8.bit.AP1SEL&0x01)										/**< Get SNAPCLKO1 Clock Select */
#define	DdTopone_SET_CLKSEL8_AP1SEL(val)		(IO_CHIPTOP.CLKSEL8.bit.AP1SEL=(0x02|val))									/**< Set SNAPCLKO1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_AP2SEL()			(IO_CHIPTOP.CLKSEL8.bit.AP2SEL&0x01)										/**< Get SNAPCLKO2 Clock Select */
#define	DdTopone_SET_CLKSEL8_AP2SEL(val)		(IO_CHIPTOP.CLKSEL8.bit.AP2SEL=(0x02|val))									/**< Set SNAPCLKO2 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL8_AP3SEL()			(IO_CHIPTOP.CLKSEL8.bit.AP3SEL&0x01)										/**< Get SNAPCLKO3 Clock Select */
#define	DdTopone_SET_CLKSEL8_AP3SEL(val)		(IO_CHIPTOP.CLKSEL8.bit.AP3SEL=(0x02|val))									/**< Set SNAPCLKO3 Clock Select (Set write bit internally) */
// CLKSEL9
#define	DdTopone_GET_CLKSEL9_PCLK()			(IO_CHIPTOP.CLKSEL9.bit.PCLK&0x3F)											/**< Get APB bus Clock Select */
#define	DdTopone_SET_CLKSEL9_PCLK(val)		(IO_CHIPTOP.CLKSEL9.bit.PCLK=(0x40|val))									/**< Set APB bus Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL9_HCLK()			(IO_CHIPTOP.CLKSEL9.bit.HCLK&0x0F)											/**< Get AHB bus Clock Select */
#define	DdTopone_SET_CLKSEL9_HCLK(val)		(IO_CHIPTOP.CLKSEL9.bit.HCLK=(0x10|val))									/**< Set AHB bus Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL9_HCLKBMH()		(IO_CHIPTOP.CLKSEL9.bit.HCLKBMH&0x07)										/**< Get AHB bus BMH block Clock Select */
#define	DdTopone_SET_CLKSEL9_HCLKBMH(val)		(IO_CHIPTOP.CLKSEL9.bit.HCLKBMH=(0x08|val))									/**< Set AHB bus BMH block Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL9_ACLKEXS()		(IO_CHIPTOP.CLKSEL9.bit.ACLKEXS&0x07)										/**< Get AXI bus EXS block Clock Select */
#define	DdTopone_SET_CLKSEL9_ACLKEXS(val)		(IO_CHIPTOP.CLKSEL9.bit.ACLKEXS=(0x08|val))									/**< Set AXI bus EXS block Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL9_ACLK()			(IO_CHIPTOP.CLKSEL9.bit.ACLK&0x07)											/**< Get AXI bus Clock Select */
#define	DdTopone_SET_CLKSEL9_ACLK(val)		(IO_CHIPTOP.CLKSEL9.bit.ACLK=(0x08|val))									/**< Set AXI bus Clock Select (Set write bit internally) */
// CLKSEL10
#define	DdTopone_GET_CLKSEL10_ACLK400()		(IO_CHIPTOP.CLKSEL10.bit.ACLK400&0x03)										/**< Get AXI bus Clock Select */
#define	DdTopone_SET_CLKSEL10_ACLK400(val)	(IO_CHIPTOP.CLKSEL10.bit.ACLK400=(0x04|val))								/**< Set AXI bus Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL10_MCLK200()		(IO_CHIPTOP.CLKSEL10.bit.MCLK200&0x07)										/**< Get MXI bus Clock Select */
#define	DdTopone_SET_CLKSEL10_MCLK200(val)	(IO_CHIPTOP.CLKSEL10.bit.MCLK200=(0x08|val))								/**< Set MXI bus Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL10_MCLK400()		(IO_CHIPTOP.CLKSEL10.bit.MCLK400&0x03)										/**< Get MXI bus Clock Select */
#define	DdTopone_SET_CLKSEL10_MCLK400(val)	(IO_CHIPTOP.CLKSEL10.bit.MCLK400=(0x04|val))								/**< Set MXI bus Clock Select (Set write bit internally) */
// CLKSEL11
#define	DdTopone_GET_CLKSEL11_DCHREQ()		(IO_CHIPTOP.CLKSEL11.bit.DCHREQ)											/**< Get CLKSEL9 and CLKSEL10 division ratio Select */
#define	DdTopone_SET_CLKSEL11_DCHREQ(val)		(IO_CHIPTOP.CLKSEL11.bit.DCHREQ=(0x01|val))									/**< Set CLKSEL9 and CLKSEL10 division ratio Select (Set write bit internally) */
// CLKSEL12
#define	DdTopone_GET_CLKSEL12_ACLK300()		(IO_CHIPTOP.CLKSEL12.bit.ACLK300&0x01)										/**< Get AXI bus Clock Select */
#define	DdTopone_SET_CLKSEL12_ACLK300(val)	(IO_CHIPTOP.CLKSEL12.bit.ACLK300=(0x02|val))								/**< Set AXI bus Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL12_GYROCLK()		(IO_CHIPTOP.CLKSEL12.bit.GYROCLK&0x03)										/**< Get Gyro macro Clock Select */
#define	DdTopone_SET_CLKSEL12_GYROCLK(val)	(IO_CHIPTOP.CLKSEL12.bit.GYROCLK=(0x04|val))								/**< Set Gyro macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL12_FPT0CLK()		(IO_CHIPTOP.CLKSEL12.bit.FPT0CLK&0x07)										/**< Get FPT0 Clock Select */
#define	DdTopone_SET_CLKSEL12_FPT0CLK(val)	(IO_CHIPTOP.CLKSEL12.bit.FPT0CLK=(0x08|val))								/**< Set FPT0 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL12_FPT1CLK()		(IO_CHIPTOP.CLKSEL12.bit.FPT1CLK&0x07)										/**< Get FPT1 Clock Select */
#define	DdTopone_SET_CLKSEL12_FPT1CLK(val)	(IO_CHIPTOP.CLKSEL12.bit.FPT1CLK=(0x08|val))								/**< Set FPT1 Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL12_MECLK()			(IO_CHIPTOP.CLKSEL12.bit.MECLK&0x03)										/**< Get ME macro Clock Select */
#define	DdTopone_SET_CLKSEL12_MECLK(val)		(IO_CHIPTOP.CLKSEL12.bit.MECLK=(0x04|val))									/**< Set ME macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL12_NFBCHCLK()		(IO_CHIPTOP.CLKSEL12.bit.NFBCHCLK&0x01)										/**< Get Nand Flash Bch macro Clock Select */
#define	DdTopone_SET_CLKSEL12_NFBCHCLK(val)	(IO_CHIPTOP.CLKSEL12.bit.NFBCHCLK=(0x02|val))								/**< Set Nand Flash Bch macro Clock Select (Set write bit internally) */
#define	DdTopone_GET_CLKSEL12_RIBCLK()		(IO_CHIPTOP.CLKSEL12.bit.RIBCLK&0x0F)										/**< Get RIBERY macro Clock Select */
#define	DdTopone_SET_CLKSEL12_RIBCLK(val)		(IO_CHIPTOP.CLKSEL12.bit.RIBCLK=(0x10|val))									/**< Set RIBERY macro Clock Select (Set write bit internally) */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define	DdTopone_GET_CLKSEL12_SHDRCLK()		(IO_CHIPTOP.CLKSEL12.bit.SHDRCLK&0x07)										/**< Get 3DNR macro Clock Select */
#define	DdTopone_SET_CLKSEL12_SHDRCLK(val)	(IO_CHIPTOP.CLKSEL12.bit.SHDRCLK=(0x08|val))								/**< Set 3DNR macro Clock Select (Set write bit internally) */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdTopone_GET_CLKSEL12_SHDRCLK()		(IO_CHIPTOP.CLKSEL12.bit.SHDRCLK&0x0F)										/**< Get 3DNR macro Clock Select */
#define	DdTopone_SET_CLKSEL12_SHDRCLK(val)	(IO_CHIPTOP.CLKSEL12.bit.SHDRCLK=(0x10|val))								/**< Set 3DNR macro Clock Select (Set write bit internally) */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---


// PLLCNT1
#define	DdTopone_GET_PLLCNT1_PL00ST()			(IO_CHIPTOP.PLLCNT1.bit.PL00ST)												/**< Get DDR PLL 00 Stop */
#define	DdTopone_SET_PLLCNT1_PL00ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL00ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 00 Stop */
#define	DdTopone_GET_PLLCNT1_PL01ST()			(IO_CHIPTOP.PLLCNT1.bit.PL01ST)												/**< Get DDR PLL 01 Stop */
#define	DdTopone_SET_PLLCNT1_PL01ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL01ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 01 Stop */
#define	DdTopone_GET_PLLCNT1_PL02ST()			(IO_CHIPTOP.PLLCNT1.bit.PL02ST)												/**< Get DDR PLL 02 Stop */
#define	DdTopone_SET_PLLCNT1_PL02ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL02ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 02 Stop */
#define	DdTopone_GET_PLLCNT1_PL03ST()			(IO_CHIPTOP.PLLCNT1.bit.PL03ST)												/**< Get DDR PLL 03 Stop */
#define	DdTopone_SET_PLLCNT1_PL03ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL03ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 03 Stop */
#define	DdTopone_GET_PLLCNT1_PL04ST()			(IO_CHIPTOP.PLLCNT1.bit.PL04ST)												/**< Get DDR PLL 04 Stop */
#define	DdTopone_SET_PLLCNT1_PL04ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL04ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 04 Stop */
#define	DdTopone_GET_PLLCNT1_PL05ST()			(IO_CHIPTOP.PLLCNT1.bit.PL05ST)												/**< Get DDR PLL 05 Stop */
#define	DdTopone_SET_PLLCNT1_PL05ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL05ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 05 Stop */
#define	DdTopone_GET_PLLCNT1_PL05AST()		(IO_CHIPTOP.PLLCNT1.bit.PL05AST)											/**< Get DDR PLL 05A Stop */
#define	DdTopone_SET_PLLCNT1_PL05AST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL05AST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 05A Stop */
#define	DdTopone_GET_PLLCNT1_PL06ST()			(IO_CHIPTOP.PLLCNT1.bit.PL06ST)												/**< Get DDR PLL 06 Stop */
#define	DdTopone_SET_PLLCNT1_PL06ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL06ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 06 Stop */
#define	DdTopone_GET_PLLCNT1_PL07ST()			(IO_CHIPTOP.PLLCNT1.bit.PL07ST)												/**< Get DDR PLL 07 Stop */
#define	DdTopone_SET_PLLCNT1_PL07ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL07ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 07 Stop */
#define	DdTopone_GET_PLLCNT1_PL08ST()			(IO_CHIPTOP.PLLCNT1.bit.PL08ST)												/**< Get DDR PLL 08 Stop */
#define	DdTopone_SET_PLLCNT1_PL08ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL08ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 08 Stop */
#define	DdTopone_GET_PLLCNT1_PL10ST()			(IO_CHIPTOP.PLLCNT1.bit.PL10ST)												/**< Get DDR PLL 10 Stop */
#define	DdTopone_SET_PLLCNT1_PL10ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL10ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 10 Stop */
#define	DdTopone_GET_PLLCNT1_PL10AST()		(IO_CHIPTOP.PLLCNT1.bit.PL10AST)											/**< Get DDR PLL 10A Stop */
#define	DdTopone_SET_PLLCNT1_PL10AST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL10AST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 10A Stop */
#define	DdTopone_GET_PLLCNT1_PL11ST()			(IO_CHIPTOP.PLLCNT1.bit.PL11ST)												/**< Get DDR PLL 11 Stop */
#define	DdTopone_SET_PLLCNT1_PL11ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.PL11ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 11 Stop */
#define	DdTopone_GET_PLLCNT1_DPL00ST()		(IO_CHIPTOP.PLLCNT1.bit.DPL00ST)											/**< Get DPL 00 Stop */
#define	DdTopone_SET_PLLCNT1_DPL00ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.DPL00ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DPL 00 Stop */
#define	DdTopone_GET_PLLCNT1_DPL01ST()		(IO_CHIPTOP.PLLCNT1.bit.DPL01ST)											/**< Get DPL 01 Stop */
#define	DdTopone_SET_PLLCNT1_DPL01ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.DPL01ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DPL 01 Stop */
#define	DdTopone_GET_PLLCNT1_DPL02ST()		(IO_CHIPTOP.PLLCNT1.bit.DPL02ST)											/**< Get DPL 02 Stop */
#define	DdTopone_SET_PLLCNT1_DPL02ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.DPL02ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DPL 02 Stop */
#define	DdTopone_GET_PLLCNT1_DPL10ST()		(IO_CHIPTOP.PLLCNT1.bit.DPL10ST)											/**< Get DPL 10 Stop */
#define	DdTopone_SET_PLLCNT1_DPL10ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.DPL10ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DPL 10 Stop */
#define	DdTopone_GET_PLLCNT1_DPL11ST()		(IO_CHIPTOP.PLLCNT1.bit.DPL11ST)											/**< Get DPL 11 Stop */
#define	DdTopone_SET_PLLCNT1_DPL11ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.DPL11ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DPL 11 Stop */
#define	DdTopone_GET_PLLCNT1_DPL12ST()		(IO_CHIPTOP.PLLCNT1.bit.DPL12ST)											/**< Get DPL 12 Stop */
#define	DdTopone_SET_PLLCNT1_DPL12ST(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT1.bit.DPL12ST=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DPL 12 Stop */
// PLLCNT2
#define	DdTopone_GET_PLLCNT2_PL00SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL00SEL)											/**< Get DDR PLL 00 Output Select */
#define	DdTopone_SET_PLLCNT2_PL00SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL00SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 00 Output Select */
#define	DdTopone_GET_PLLCNT2_PL01SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL01SEL)											/**< Get DDR PLL 01 Output Select */
#define	DdTopone_SET_PLLCNT2_PL01SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL01SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 01 Output Select */
#define	DdTopone_GET_PLLCNT2_PL02SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL02SEL)											/**< Get DDR PLL 02 Output Select */
#define	DdTopone_SET_PLLCNT2_PL02SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL02SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 02 Output Select */
#define	DdTopone_GET_PLLCNT2_PL03SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL03SEL)											/**< Get DDR PLL 03 Output Select */
#define	DdTopone_SET_PLLCNT2_PL03SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL03SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 03 Output Select */
#define	DdTopone_GET_PLLCNT2_PL04SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL04SEL)											/**< Get DDR PLL 04 Output Select */
#define	DdTopone_SET_PLLCNT2_PL04SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL04SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 04 Output Select */
#define	DdTopone_GET_PLLCNT2_PL05SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL05SEL)											/**< Get DDR PLL 05 Output Select */
#define	DdTopone_SET_PLLCNT2_PL05SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL05SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 05 Output Select */
#define	DdTopone_GET_PLLCNT2_PL05ASEL()		(IO_CHIPTOP.PLLCNT2.bit.PL05ASEL)											/**< Get DDR PLL 05A Output Select */
#define	DdTopone_SET_PLLCNT2_PL05ASEL(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL05ASEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 05A Output Select */
#define	DdTopone_GET_PLLCNT2_PL06SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL06SEL)											/**< Get DDR PLL 06 Output Select */
#define	DdTopone_SET_PLLCNT2_PL06SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL06SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 06 Output Select */
#define	DdTopone_GET_PLLCNT2_PL07SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL07SEL)											/**< Get DDR PLL 07 Output Select */
#define	DdTopone_SET_PLLCNT2_PL07SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL07SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 07 Output Select */
#define	DdTopone_GET_PLLCNT2_PL08SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL08SEL)											/**< Get DDR PLL 08 Output Select */
#define	DdTopone_SET_PLLCNT2_PL08SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL08SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 08 Output Select */
#define	DdTopone_GET_PLLCNT2_PL10SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL10SEL)											/**< Get DDR PLL 10 Output Select */
#define	DdTopone_SET_PLLCNT2_PL10SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL10SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 10 Output Select */
#define	DdTopone_GET_PLLCNT2_PL10ASEL()		(IO_CHIPTOP.PLLCNT2.bit.PL10ASEL)											/**< Get DDR PLL 10A Output Select */
#define	DdTopone_SET_PLLCNT2_PL10ASEL(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL10ASEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 10A Output Select */
#define	DdTopone_GET_PLLCNT2_PL11SEL()		(IO_CHIPTOP.PLLCNT2.bit.PL11SEL)											/**< Get DDR PLL 11 Output Select */
#define	DdTopone_SET_PLLCNT2_PL11SEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL11SEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 11 Output Select */
#define	DdTopone_GET_PLLCNT2_PL01SSEN()		(IO_CHIPTOP.PLLCNT2.bit.PL01SSEN)											/**< Get DDR PLL 01 Spread spectrumt */
#define	DdTopone_SET_PLLCNT2_PL01SSEN(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL01SSEN=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 01 Spread spectrumt */
#define	DdTopone_GET_PLLCNT2_PL02SSEN()		(IO_CHIPTOP.PLLCNT2.bit.PL02SSEN)											/**< Get DDR PLL 02 Spread spectrumt */
#define	DdTopone_SET_PLLCNT2_PL02SSEN(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT2.bit.PL02SSEN=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DDR PLL 02 Spread spectrumt */
// PLLCNT3
#define	DdTopone_GET_PLLCNT3_P00POSTDIV()		(IO_CHIPTOP.PLLCNT3.bit.P00POSTDIV)											/**< Get PLL 00 back Clock Divider */
#define	DdTopone_SET_PLLCNT3_P00POSTDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT3.bit.P00POSTDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 00 back Clock Divider */
#define	DdTopone_GET_PLLCNT3_P00PREDIV()		(IO_CHIPTOP.PLLCNT3.bit.P00PREDIV)											/**< Get PLL 00 front Clock Divider */
#define	DdTopone_SET_PLLCNT3_P00PREDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT3.bit.P00PREDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 00 front Clock Divider */
#define	DdTopone_GET_PLLCNT3_P00PLLDIV()		(IO_CHIPTOP.PLLCNT3.bit.P00PLLDIV)											/**< Get PLL 00 Clock Divider */
#define	DdTopone_SET_PLLCNT3_P00PLLDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT3.bit.P00PLLDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 00 Clock Divider */
// PLLCNT4
#define	DdTopone_GET_PLLCNT4_P00FNUM()		(IO_CHIPTOP.PLLCNT4.bit.P00FNUM)											/**< Get PLL 00 divider fractional numerator ratio */
#define	DdTopone_SET_PLLCNT4_P00FNUM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT4.bit.P00FNUM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 00 divider fractional numerator ratio */
// PLLCNT5
#define	DdTopone_GET_PLLCNT5_P00FDEN()		(IO_CHIPTOP.PLLCNT5.bit.P00FDEN)											/**< Get PLL 00 divider fractional denominator ratio */
#define	DdTopone_SET_PLLCNT5_P00FDEN(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT5.bit.P00FDEN=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 00 divider fractional denominator ratio */
// PLLCNT6
#define	DdTopone_GET_PLLCNT6_P01RATE()		(IO_CHIPTOP.PLLCNT6.bit.P01RATE)											/**< Get PLL 01 SSC  */
#define	DdTopone_SET_PLLCNT6_P01RATE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT6.bit.P01RATE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 01 SSC modulation rate */
#define	DdTopone_GET_PLLCNT6_P01FREQ()		(IO_CHIPTOP.PLLCNT6.bit.P01FREQ)											/**< Get PLL 01 SSC modulation frequency */
#define	DdTopone_SET_PLLCNT6_P01FREQ(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT6.bit.P01FREQ=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 01 SSC modulation frequency */
#define	DdTopone_GET_PLLCNT6_P01MODE()		(IO_CHIPTOP.PLLCNT6.bit.P01MODE)											/**< Get PLL 01 SSC modulation mode */
#define	DdTopone_SET_PLLCNT6_P01MODE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT6.bit.P01MODE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 01 SSC modulation mode */
#define	DdTopone_GET_PLLCNT6_P02RATE()		(IO_CHIPTOP.PLLCNT6.bit.P02RATE)											/**< Get PLL 02 SSC modulation rate */
#define	DdTopone_SET_PLLCNT6_P02RATE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT6.bit.P02RATE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 02 SSC modulation rate */
#define	DdTopone_GET_PLLCNT6_P02FREQ()		(IO_CHIPTOP.PLLCNT6.bit.P02FREQ)											/**< Get PLL 02 SSC modulation frequency */
#define	DdTopone_SET_PLLCNT6_P02FREQ(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT6.bit.P02FREQ=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 02 SSC modulation frequency */
#define	DdTopone_GET_PLLCNT6_P02MODE()		(IO_CHIPTOP.PLLCNT6.bit.P02MODE)											/**< Get PLL 02 SSC modulation mode */
#define	DdTopone_SET_PLLCNT6_P02MODE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT6.bit.P02MODE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 02 SSC modulation mode */
// PLLCNT7
#define	DdTopone_GET_PLLCNT7_P03POSTDIV0()	(IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV0)										/**< Get PLL 03 back Clock Divider */
#define	DdTopone_SET_PLLCNT7_P03POSTDIV0(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV0=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 03 back Clock Divider */
#define	DdTopone_GET_PLLCNT7_P03POSTDIV1()	(IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV1)										/**< Get PLL 03 back Clock Divider */
#define	DdTopone_SET_PLLCNT7_P03POSTDIV1(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.P03POSTDIV1=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 03 back Clock Divider */
#define	DdTopone_GET_PLLCNT7_P03PREDIV()		(IO_CHIPTOP.PLLCNT7.bit.P03PREDIV)											/**< Get PLL 03 front Clock Divider */
#define	DdTopone_SET_PLLCNT7_P03PREDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.P03PREDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 03 front Clock Divider */
#define	DdTopone_GET_PLLCNT7_P03PLLDIV()		(IO_CHIPTOP.PLLCNT7.bit.P03PLLDIV)											/**< Get PLL 03 Clock Divider */
#define	DdTopone_SET_PLLCNT7_P03PLLDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.P03PLLDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 03 Clock Divider */
#define	DdTopone_GET_PLLCNT7_P03OC0()			(IO_CHIPTOP.PLLCNT7.bit.P03OC0)												/**< Get PLL 03 Clock Disable */
#define	DdTopone_SET_PLLCNT7_P03OC0(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.P03OC0=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 03 Clock Disable */
#define	DdTopone_GET_PLLCNT7_P03OC1()			(IO_CHIPTOP.PLLCNT7.bit.P03OC1)												/**< Get PLL 03 Clock Disable */
#define	DdTopone_SET_PLLCNT7_P03OC1(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.P03OC1=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 03 Clock Disable */
#define	DdTopone_GET_PLLCNT7_D0XOC()			(IO_CHIPTOP.PLLCNT7.bit.D0XOC)												/**< Get DPL0 Clock Disable */
#define	DdTopone_SET_PLLCNT7_D0XOC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.D0XOC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DPL0 Clock Disable */
#define	DdTopone_GET_PLLCNT7_D1XOC()			(IO_CHIPTOP.PLLCNT7.bit.D1XOC)												/**< Get DPL1 Clock Disable */
#define	DdTopone_SET_PLLCNT7_D1XOC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.D1XOC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set DPL1 Clock Disable */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define	DdTopone_GET_PLLCNT7_DPLX8()			(IO_CHIPTOP.PLLCNT7.bit.DPLX8)												/**< Get multiplication rate of DDR subsequent stage PLL */
#define	DdTopone_SET_PLLCNT7_DPLX8(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.DPLX8=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set multiplication rate of DDR subsequent stage PLL */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define	DdTopone_GET_PLLCNT7_DSEL()			(IO_CHIPTOP.PLLCNT7.bit.DSEL)												/**< Get CLK path of the PLL */
#define	DdTopone_SET_PLLCNT7_DSEL(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT7.bit.DSEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set CLK path of the PLL */
// PLLCNT8
#define	DdTopone_GET_PLLCNT8_P04POSTDIV()		(IO_CHIPTOP.PLLCNT8.bit.P04POSTDIV)											/**< Get PLL 04 back Clock Divider */
#define	DdTopone_SET_PLLCNT8_P04POSTDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT8.bit.P04POSTDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 04 back Clock Divider */
#define	DdTopone_GET_PLLCNT8_P04PREDIV()		(IO_CHIPTOP.PLLCNT8.bit.P04PREDIV)											/**< Get PLL 04 front Clock Divider */
#define	DdTopone_SET_PLLCNT8_P04PREDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT8.bit.P04PREDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 04 front Clock Divider */
#define	DdTopone_GET_PLLCNT8_P04PLLDIV()		(IO_CHIPTOP.PLLCNT8.bit.P04PLLDIV)											/**< Get PLL 04 Clock Divider */
#define	DdTopone_SET_PLLCNT8_P04PLLDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT8.bit.P04PLLDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 04 Clock Divider */
// PLLCNT9
#define	DdTopone_GET_PLLCNT9_P10APLLDIV()		(IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV)											/**< Get PLL 10 Clock Divider */
#define	DdTopone_SET_PLLCNT9_P10APLLDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 10 Clock Divider */
#define	DdTopone_GET_PLLCNT9_P08PLLDIV()		(IO_CHIPTOP.PLLCNT9.bit.P08PLLDIV)											/**< Get PLL 08 Clock Divider */
#define	DdTopone_SET_PLLCNT9_P08PLLDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLCNT9.bit.P08PLLDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 08 Clock Divider */
#define	DdTopone_GET_PLLCNT9_P05CHG()			(IO_CHIPTOP.PLLCNT9.bit.P05CHG)												/**< Get PLL 05 frefrequency generated */
#define	DdTopone_SET_PLLCNT9_P05CHG(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
                                                IO_CHIPTOP.PLLCNT9.bit.P05CHG=(val); \
                                                Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PLL 05 frequency generated */

// CRSWR(Software reset request register 0)
#define	DdTopone_SET_CRSWR_SRREQ()				{IO_CHIPTOP.CRSWR.bit.SRREQ=1;}												/**< Set ARESETn Generation */

// PLLFREQ1
#define	DdTopone_GET_PLLFREQ1_PLLIDIV()		(IO_CHIPTOP.PLLFREQ1.bit.PLLIDIV)												/**< Get PLLFREQ1 Divider */
#define	DdTopone_SET_PLLFREQ1_PLLIDIV(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PLLFREQ1.bit.PLLIDIV=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}							/**< Set PLLFREQ1 Divider */

// ODIVCH0
#define	DdTopone_GET_ODIVCH0_ODIVCH0NUM()		(IO_CHIPTOP.ODIVCH0.bit.ODIVCH0NUM)												/**< Get ODIVCH0 Divider */
#define	DdTopone_SET_ODIVCH0_ODIVCH0NUM(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.ODIVCH0.bit.ODIVCH0NUM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}							/**< Set ODIVCH0 Divider */

// CMDEN
#define	DdTopone_GET_CMDEN_CMDEN()			(IO_CHIPTOP.CMDEN.bit.CMDEN)													/**< Get CMDEN Divider */
#define	DdTopone_SET_CMDEN_CMDEN(val)			{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.CMDEN.bit.CMDEN=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}							/**< Set CMDEN Divider */


typedef struct 	_DdTopone 					DdTopone;
typedef struct 	_DdToponeClass 			DdToponeClass;
typedef struct 	_DdToponePrivate 			DdToponePrivate;

struct _DdTopone{
	GObject parent;
};

struct _DdToponeClass{
	GObjectClass parentclass;
};

GType 								dd_topone_get_type(void) G_GNUC_CONST;
DdTopone* 					dd_topone_new(void);


/*@}*/
G_END_DECLS


#endif /* __DD_TOPTHREE_H__ */
