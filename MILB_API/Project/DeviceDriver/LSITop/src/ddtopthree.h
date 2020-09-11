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


#ifndef  __DD_TOPTHREE_H__
#define __DD_TOPTHREE_H__


#include "ddim_typedef.h"
#include "driver_common.h"
#include "chiptop.h"
#include "dd_arm.h"
#include <glib-object.h>


G_BEGIN_DECLS


#define DD_TYPE_TOPTHREE							(dd_topthree_get_type ())
#define DD_TOPTHREE(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), DD_TYPE_TOPTHREE, DdTopthree))
#define DD_TOPTHREE_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), DD_TYPE_TOPTHREE, DdTopthreeClass))
#define DD_IS_TOPTHREE(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_TOPTHREE))
#define DD_IS_TOPTHREE_CLASS(klass)		 	(G_TYPE_CHECK_CLASS_TYPE ((klass), DD_TYPE_TOPTHREE))
#define DD_TOPTHREE_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), DD_TYPE_TOPTHREE, DdTopthreeClass))

#define	DdTopthree_GET_PERSEL1_I2C0CNT()		(IO_CHIPTOP.PERSEL1.bit.I2C0CNT)											/**< Get step number of filter for ISCL and ISDA ports */
#define	DdTopthree_SET_PERSEL1_I2C0CNT(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.I2C0CNT=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set step number of filter for ISCL and ISDA ports */

#define	DdTopthree_GET_PERSEL1_SDANC0()			(IO_CHIPTOP.PERSEL1.bit.SDANC0)												/**< Get filter enable for ISDA port */
#define	DdTopthree_SET_PERSEL1_SDANC0(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.SDANC0=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set filter enable for ISDA port */

#define	DdTopthree_GET_PERSEL1_SCLNC0()			(IO_CHIPTOP.PERSEL1.bit.SCLNC0)												/**< Get filter enable for ISCL port */
#define	DdTopthree_SET_PERSEL1_SCLNC0(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.SCLNC0=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set filter enable for ISCL port */

#define	DdTopthree_GET_PERSEL1_I2C1CNT()		(IO_CHIPTOP.PERSEL1.bit.I2C1CNT)											/**< Get step number of filter for IS1CL and IS1DA ports */
#define	DdTopthree_SET_PERSEL1_I2C1CNT(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.I2C1CNT=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set step number of filter for IS1CL and IS1DA ports */

#define	DdTopthree_GET_PERSEL1_SDANC1()			(IO_CHIPTOP.PERSEL1.bit.SDANC1)												/**< Get filter enable for IS1DA port */
#define	DdTopthree_SET_PERSEL1_SDANC1(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.SDANC1=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set filter enable for IS1DA port */

#define	DdTopthree_GET_PERSEL1_SCLNC1()			(IO_CHIPTOP.PERSEL1.bit.SCLNC1)												/**< Get filter enable for IS1CL port */
#define	DdTopthree_SET_PERSEL1_SCLNC1(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.SCLNC1=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set filter enable for IS1CL port */

#define	DdTopthree_GET_PERSEL1_I2C2CNT()		(IO_CHIPTOP.PERSEL1.bit.I2C2CNT)											/**< Get step number of filter for IS2CL and IS2DA ports */
#define	DdTopthree_SET_PERSEL1_I2C2CNT(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.I2C2CNT=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set step number of filter for IS2CL and IS2DA ports */

#define	DdTopthree_GET_PERSEL1_SDANC2()			(IO_CHIPTOP.PERSEL1.bit.SDANC2)												/**< Get filter enable for IS2DA port */
#define	DdTopthree_SET_PERSEL1_SDANC2(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.SDANC2=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set filter enable for IS2DA port */

#define	DdTopthree_GET_PERSEL1_SCLNC2()			(IO_CHIPTOP.PERSEL1.bit.SCLNC2)												/**< Get filter enable for IS2CL port */
#define	DdTopthree_SET_PERSEL1_SCLNC2(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.SCLNC2=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set filter enable for IS2CL port */

#define	DdTopthree_GET_PERSEL1_DVWT2()			(IO_CHIPTOP.PERSEL1.bit.DVWT2)												/**< Get HD to WTrg2 Select */
#define	DdTopthree_SET_PERSEL1_DVWT2(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.DVWT2=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set HD to WTrg2 Select */

#define	DdTopthree_GET_PERSEL1_DHWT3()			(IO_CHIPTOP.PERSEL1.bit.DHWT3)												/**< Get HD to WTrg3 Select */
#define	DdTopthree_SET_PERSEL1_DHWT3(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.DHWT3=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set HD to WTrg3 Select */

#define	DdTopthree_GET_PERSEL1_AU0DO0C()		(IO_CHIPTOP.PERSEL1.bit.AU0DO0C)											/**< Get AU0DO Signal0 IO Control */
#define	DdTopthree_SET_PERSEL1_AU0DO0C(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.AU0DO0C=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set AU0DO Signal0 IO Control */

#define	DdTopthree_GET_PERSEL1_AU0DO1C()		(IO_CHIPTOP.PERSEL1.bit.AU0DO1C)											/**< Get AU0DO Signal1 IO Control */
#define	DdTopthree_SET_PERSEL1_AU0DO1C(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.AU0DO1C=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set AU0DO Signal1 IO Control */

#define	DdTopthree_GET_PERSEL1_AU1DOC()			(IO_CHIPTOP.PERSEL1.bit.AU1DOC)												/**< Get AU1DO Signal IO Control */
#define	DdTopthree_SET_PERSEL1_AU1DOC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.AU1DOC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set AU1DO Signal IO Control */

#define	DdTopthree_GET_PERSEL1_AU0MCC()			(IO_CHIPTOP.PERSEL1.bit.AU0MCC)												/**< Get AU0MCLKO Signal IO Control */
#define	DdTopthree_SET_PERSEL1_AU0MCC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.AU0MCC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set AU0MCLKO Signal IO Control */

#define	DdTopthree_GET_PERSEL1_AU1MCC()			(IO_CHIPTOP.PERSEL1.bit.AU1MCC)												/**< Get AU1MCLK Signal IO Control */
#define	DdTopthree_SET_PERSEL1_AU1MCC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.AU1MCC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set AU1MCLK Signal IO Control */

#define	DdTopothree_GET_PERSEL1_RLSEL3()			(IO_CHIPTOP.PERSEL1.bit.RLSEL3)												/**< Get Peripheral Timer Trigger ch3 Select */
#define	DdTopothree_SET_PERSEL1_RLSEL3(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.RLSEL3=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Peripheral Timer Trigger ch3 Select */

#define	DdTopothree_GET_PERSEL1_RLSEL4()			(IO_CHIPTOP.PERSEL1.bit.RLSEL4)												/**< Get Peripheral Timer Trigger ch4 Select */
#define	DdTopothree_SET_PERSEL1_RLSEL4(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.RLSEL4=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Peripheral Timer Trigger ch4 Select */

#define	DdTopothree_GET_PERSEL1_RLSEL5()			(IO_CHIPTOP.PERSEL1.bit.RLSEL5)												/**< Get Peripheral Timer Trigger ch5 Select */
#define	DdTopothree_SET_PERSEL1_RLSEL5(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.RLSEL5=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Peripheral Timer Trigger ch5 Select */

#define	DdTopothree_GET_PERSEL1_INTVDSEL()		(IO_CHIPTOP.PERSEL1.bit.INTVDSEL)											/**< Get Interrupt VD Select */
#define	DdTopothree_SET_PERSEL1_INTVDSEL(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL1.bit.INTVDSEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Interrupt VD Select */

#define	DdTopothree_GET_PERSEL2_UDCTRG()			(IO_CHIPTOP.PERSEL2.bit.UDCTRG)												/**< Get UDC function Select */
#define	DdTopothree_SET_PERSEL2_UDCTRG(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDCTRG=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC function Select */

#define	DdTopothree_GET_PERSEL2_UDC0AM()			(IO_CHIPTOP.PERSEL2.bit.UDC0AM)												/**< Get UDC A-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC0AM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC0AM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC A-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC0BM()			(IO_CHIPTOP.PERSEL2.bit.UDC0BM)												/**< Get UDC B-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC0BM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC0BM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC B-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC1AM()			(IO_CHIPTOP.PERSEL2.bit.UDC1AM)												/**< Get UDC A-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC1AM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC1AM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC A-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC1BM()			(IO_CHIPTOP.PERSEL2.bit.UDC1BM)												/**< Get UDC B-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC1BM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC1BM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC B-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC2AM()			(IO_CHIPTOP.PERSEL2.bit.UDC2AM)												/**< Get UDC A-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC2AM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC2AM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC A-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC2BM()			(IO_CHIPTOP.PERSEL2.bit.UDC2BM)												/**< Get UDC B-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC2BM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC2BM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC B-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC3AM()			(IO_CHIPTOP.PERSEL2.bit.UDC3AM)												/**< Get UDC A-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC3AM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC3AM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC A-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC3BM()			(IO_CHIPTOP.PERSEL2.bit.UDC3BM)												/**< Get UDC B-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC3BM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC3BM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC B-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC4AM()			(IO_CHIPTOP.PERSEL2.bit.UDC4AM)												/**< Get UDC A-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC4AM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC4AM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC A-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC4BM()			(IO_CHIPTOP.PERSEL2.bit.UDC4BM)												/**< Get UDC B-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC4BM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC4BM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC B-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC5AM()			(IO_CHIPTOP.PERSEL2.bit.UDC5AM)												/**< Get UDC A-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC5AM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC5AM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC A-pin trigger input signal Mask */

#define	DdTopothree_GET_PERSEL2_UDC5BM()			(IO_CHIPTOP.PERSEL2.bit.UDC5BM)												/**< Get UDC B-pin trigger input signal Mask */
#define	DdTopothree_SET_PERSEL2_UDC5BM(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.UDC5BM=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set UDC B-pin trigger input signal Mask */

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdTopothree_GET_PERSEL2_SPIMSEN0()			(IO_CHIPTOP.PERSEL2.bit.SPIMSEN0)										/**< Get SPI I/O ch0 direction input/output */
#define	DdTopothree_SET_PERSEL2_SPIMSEN0(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.SPIMSEN0=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SPI I/O ch0 direction input/output */

#define	DdTopothree_GET_PERSEL2_SPIMSEN1()			(IO_CHIPTOP.PERSEL2.bit.SPIMSEN1)										/**< Get SPI I/O ch1 direction input/output */
#define	DdTopothree_SET_PERSEL2_SPIMSEN1(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.SPIMSEN1=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SPI I/O ch1 direction input/output */

#define	DdTopothree_GET_PERSEL2_SPIMSEN2()			(IO_CHIPTOP.PERSEL2.bit.SPIMSEN2)										/**< Get SPI I/O ch2 direction input/output */
#define	DdTopothree_SET_PERSEL2_SPIMSEN2(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL2.bit.SPIMSEN2=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SPI I/O ch2 direction input/output */

// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define	DdTopothree_GET_PERSEL3_AU1WPPS()		(IO_CHIPTOP.PERSEL3.bit.AU1WPPS)											/**< Get AU0DO1 SPI3 IO Control */
#define	DdTopothree_SET_PERSEL3_AU1WPPS(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.AU1WPPS=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set AU0DO1 SPI3 IO Control */

#define	DdTopothree_GET_PERSEL3_AU0WP11()		(IO_CHIPTOP.PERSEL3.bit.AU0WP11)											/**< Get PA5/AU0DO1/WPPG11 IO Control */
#define	DdTopothree_SET_PERSEL3_AU0WP11(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.AU0WP11=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PA5/AU0DO1/WPPG11 IO Control */

#define	DdTopothree_GET_PERSEL3_SNH2WP04()		(IO_CHIPTOP.PERSEL3.bit.SNH2WP04)											/**< Get PG6/SNHD2/WPPG4 IO Control */
#define	DdTopothree_SET_PERSEL3_SNH2WP04(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.SNH2WP04=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PG6/SNHD2/WPPG4 IO Control */

#define	DdTopothree_GET_PERSEL3_SNV2WP05()		(IO_CHIPTOP.PERSEL3.bit.SNV2WP05)											/**< Get PG7/SNVD2/WPPG5 IO Control */
#define	DdTopothree_SET_PERSEL3_SNV2WP05(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.SNV2WP05=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PG7/SNVD2/WPPG5 IO Control */

#define	DdTopothree_GET_PERSEL3_SNA2WP06()		(IO_CHIPTOP.PERSEL3.bit.SNA2WP06)											/**< Get PH0/SNAPCLKO2/WPPG6 IO Control */
#define	DdTopothree_SET_PERSEL3_SNA2WP06(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.SNA2WP06=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PH0/SNAPCLKO2/WPPG6 IO Control */

#define	DdTopothree_GET_PERSEL3_SNH3WP07()		(IO_CHIPTOP.PERSEL3.bit.SNH3WP07)											/**< Get PH1/SNHD3/WPPG7 IO Control */
#define	DdTopothree_SET_PERSEL3_SNH3WP07(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.SNH3WP07=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PH1/SNHD3/WPPG7 IO Control */

#define	DdTopothree_GET_PERSEL3_SNV3WP08()		(IO_CHIPTOP.PERSEL3.bit.SNV3WP08)											/**< Get PH2/SNVD3/WPPG8 IO Control */
#define	DdTopothree_SET_PERSEL3_SNV3WP08(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.SNV3WP08=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PH2/SNVD3/WPPG8 IO Control */

#define	DdTopothree_GET_PERSEL3_SNA3WP09()		(IO_CHIPTOP.PERSEL3.bit.SNA3WP09)											/**< Get PH3/SNAPCLKO3/WPPG9 IO Control */
#define	DdTopothree_SET_PERSEL3_SNA3WP09(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.SNA3WP09=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PH3/SNAPCLKO3/WPPG9 IO Control */

#define	DdTopothree_GET_PERSEL3_U1VBSOU5()		(IO_CHIPTOP.PERSEL3.bit.U1VBSOU5)											/**< Get U1VBUSE/PM1/FPSOUT6 IO Control */
#define	DdTopothree_SET_PERSEL3_U1VBSOU5(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.U1VBSOU5=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set U1VBUSE/PM1/FPSOUT6 IO Control */

#define	DdTopothree_GET_PERSEL3_U2VBSOU6()		(IO_CHIPTOP.PERSEL3.bit.U2VBSOU6)											/**< Get U2VBUSE/PN1/FPSOUT7 IO Control */
#define	DdTopothree_SET_PERSEL3_U2VBSOU6(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.U2VBSOU6=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set U2VBUSE/PN1/FPSOUT7 IO Control */

#define	DdTopothree_GET_PERSEL3_U2IDWP14()		(IO_CHIPTOP.PERSEL3.bit.U2IDWP14)											/**< Get U2IDPU/PN4/WPPG14_1 IO Control */
#define	DdTopothree_SET_PERSEL3_U2IDWP14(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.U2IDWP14=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set U2IDPU/PN4/WPPG14_1 IO Control */

#define	DdTopothree_GET_PERSEL3_PRT1SOU3()		(IO_CHIPTOP.PERSEL3.bit.PRT1SOU3)											/**< Get PY1/PXRSTX1/FPSOUT4 IO Control */
#define	DdTopothree_SET_PERSEL3_PRT1SOU3(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.PRT1SOU3=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PY1/PXRSTX1/FPSOUT4 IO Control */

#define	DdTopothree_GET_PERSEL3_PXW0WP12()		(IO_CHIPTOP.PERSEL3.bit.PXW0WP12)											/**< Get PY4/PXWAKE0/WPPG12_1 IO Control */
#define	DdTopothree_SET_PERSEL3_PXW0WP12(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.PXW0WP12=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PY4/PXWAKE0/WPPG12_1 IO Control */

#define	DdTopothree_GET_PERSEL3_PXW1SOU7()		(IO_CHIPTOP.PERSEL3.bit.PXW1SOU7)											/**< Get PY5/PXWAKE1/FPSOUT8 IO Control */
#define	DdTopothree_SET_PERSEL3_PXW1SOU7(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.PXW1SOU7=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PY5/PXWAKE1/FPSOUT8 IO Control */

#define	DdTopothree_GET_PERSEL3_PXC0SCK7()		(IO_CHIPTOP.PERSEL3.bit.PXC0SCK7)											/**< Get PY6/PXCLKREQ0/FPSCK8 IO Control */
#define	DdTopothree_SET_PERSEL3_PXC0SCK7(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.PXC0SCK7=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PY6/PXCLKREQ0/FPSCK8 IO Control */

#define	DdTopone_Get_PERSEL3_PXC1WP15()		(IO_CHIPTOP.PERSEL3.bit.PXC1WP15)											/**< Get PY7/PXCLKREQ1/WPPG15_1 IO Control */
#define	DdTopone_Set_PERSEL3_PXC1WP15(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.PXC1WP15=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PY7/PXCLKREQ1/WPPG15_1 IO Control */

#define	DdTopothree_GET_PERSEL3_SCK4WP13()		(IO_CHIPTOP.PERSEL3.bit.SCK4WP13)											/**< Get SD3WP/PP1/FPSCK5/WPPG13_2 IO Control */
#define	DdTopothree_SET_PERSEL3_SCK4WP13(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.SCK4WP13=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SD3WP/PP1/FPSCK5/WPPG13_2 IO Control */

#define	DdTopothree_GET_PERSEL3_S3LSOU5WP14()	(IO_CHIPTOP.PERSEL3.bit.S3LSOU5WP14)										/**< Get SD3LEDX/PP2/FPSOUT5/WPPG14_2 IO Control */
#define	DdTopothree_SET_PERSEL3_S3LSOU5WP14(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.S3LSOU5WP14=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SD3LEDX/PP2/FPSOUT5/WPPG14_2 IO Control */

#define	DdTopothree_GET_PERSEL3_S3SWP15()		(IO_CHIPTOP.PERSEL3.bit.S3SWP15)											/**< Get SD3SW/PP3/UDTRG5B/WPPG15_2 IO Control */
#define	DdTopothree_SET_PERSEL3_S3SWP15(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.S3SWP15=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SD3SW/PP3/UDTRG5B/WPPG15_2 IO Control */

#define	DdTopothree_GET_PERSEL3_RTS1SCK2()		(IO_CHIPTOP.PERSEL3.bit.RTS1SCK2)											/**< Get P85/FPSRTS2/WTRG1/FPSCK3 IO Control */
#define	DdTopthree_SET_PERSEL3_RTS1SCK2(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.RTS1SCK2=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set P85/FPSRTS2/WTRG1/FPSCK3 IO Control */

#define	DdTopthree_GET_PERSEL3_U1IDWP13()		(IO_CHIPTOP.PERSEL3.bit.U1IDWP13)											/**< Get U1IDPU/PM4/WPPG13_1 IO Control */
#define	DdTopthree_SET_PERSEL3_U1IDWP13(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.U1IDWP13=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set U1IDPU/PM4/WPPG13_1 IO Control */

#define	DdTopthree_GET_PERSEL3_PRT0SCK3()		(IO_CHIPTOP.PERSEL3.bit.PRT0SCK3)											/**< Get PY0/PXRSTX0/FPSCK4 IO Control */
#define	DdTopthree_SET_PERSEL3_PRT0SCK3(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL3.bit.PRT0SCK3=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set PY0/PXRSTX0/FPSCK4 IO Control */


#define	DdTopthree_GET_PERSEL4_EI22UD0A()		(IO_CHIPTOP.PERSEL4.bit.EI22UD0A)											/**< Get external interrupt request 22 */
#define	DdTopthree_SET_PERSEL4_EI22UD0A(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI22UD0A=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 22 */
#define	DdTopthree_GET_PERSEL4_EI23UD0B()		(IO_CHIPTOP.PERSEL4.bit.EI23UD0B)											/**< Get external interrupt request 23 */
#define	DdTopthree_SET_PERSEL4_EI23UD0B(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI23UD0B=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 23 */
#define	DdTopthree_GET_PERSEL4_EI24UD1A()		(IO_CHIPTOP.PERSEL4.bit.EI24UD1A)											/**< Get external interrupt request 24 */
#define	DdTopthree_SET_PERSEL4_EI24UD1A(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI24UD1A=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 24 */
#define	DdTopthree_GET_PERSEL4_EI25UD1B()		(IO_CHIPTOP.PERSEL4.bit.EI25UD1B)											/**< Get external interrupt request 25 */
#define	DdTopthree_SET_PERSEL4_EI25UD1B(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI25UD1B=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 25 */
#define	DdTopthree_GET_PERSEL4_EI26UD2A()		(IO_CHIPTOP.PERSEL4.bit.EI26UD2A)											/**< Get external interrupt request 26 */
#define	DdTopthree_SET_PERSEL4_EI26UD2A(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI26UD2A=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 26 */
#define	DdTopthree_GET_PERSEL4_EI27UD2B()		(IO_CHIPTOP.PERSEL4.bit.EI27UD2B)											/**< Get external interrupt request 27 */
#define	DdTopthree_SET_PERSEL4_EI27UD2B(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI27UD2B=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 27 */
#define	DdTopthree_GET_PERSEL4_EI28UD3A()		(IO_CHIPTOP.PERSEL4.bit.EI28UD3A)											/**< Get external interrupt request 28 */
#define	DdTopthree_SET_PERSEL4_EI28UD3A(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI28UD3A=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 28 */
#define	DdTopthree_GET_PERSEL4_EI29UD3B()		(IO_CHIPTOP.PERSEL4.bit.EI29UD3B)											/**< Get external interrupt request 29 */
#define	DdTopthree_SET_PERSEL4_EI29UD3B(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI29UD3B=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 29 */
#define	DdTopthree_GET_PERSEL4_EI30UD4A()		(IO_CHIPTOP.PERSEL4.bit.EI30UD4A)											/**< Get external interrupt request 30 */
#define	DdTopthree_SET_PERSEL4_EI30UD4A(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI30UD4A=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 30 */
#define	DdTopthree_GET_PERSEL4_EI31UD4B()		(IO_CHIPTOP.PERSEL4.bit.EI31UD4B)											/**< Get external interrupt request 31 */
#define	DdTopthree_SET_PERSEL4_EI31UD4B(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.EI31UD4B=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set external interrupt request 31 */
#define	DdTopthree_GET_PERSEL4_SD3CDXS()		(IO_CHIPTOP.PERSEL4.bit.SD3CDXS)											/**< Get SD card ch3 connection check */
#define	DdTopthree_SET_PERSEL4_SD3CDXS(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.SD3CDXS=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SD card ch3 connection check */
#define	DdTopthree_GET_PERSEL4_SD3WPS()			(IO_CHIPTOP.PERSEL4.bit.SD3WPS)												/**< Get SD card ch3 write protection */
#define	DdTopthree_SET_PERSEL4_SD3WPS(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.SD3WPS=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SD card ch3 write protection */
#define	DdTopthree_GET_PERSEL4_U1OCDXS()		(IO_CHIPTOP.PERSEL4.bit.U1OCDXS	)											/**< Get USB2.0 macro overcurrent detection */
#define	DdTopthree_SET_PERSEL4_U1OCDXS(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.U1OCDXS=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set USB2.0 macro overcurrent detection */
#define	DdTopthree_GET_PERSEL4_U1IDDIGS()		(IO_CHIPTOP.PERSEL4.bit.U1IDDIGS)											/**< Get USB2.0 macro ID detection */
#define	DdTopthree_SET_PERSEL4_U1IDDIGS(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.U1IDDIGS=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set USB2.0 macro ID detection */
#define	DdTopthree_GET_PERSEL4_U2OCDXS()		(IO_CHIPTOP.PERSEL4.bit.U2OCDXS)											/**< Get USB3.0&USB2.0 macro overcurrent detection */
#define	DdTopthree_SET_PERSEL4_U2OCDXS(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.U2OCDXS=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set USB3.0&USB2.0 macro overcurrent detection */
#define	DdTopthree_GET_PERSEL4_U2IDDIGS()		(IO_CHIPTOP.PERSEL4.bit.U2IDDIGS)											/**< Get USB3.0&USB2.0 macro ID detection */
#define	DdTopthree_SET_PERSEL4_U2IDDIGS(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PERSEL4.bit.U2IDDIGS=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set USB3.0&USB2.0 macro ID detection */


#define	DdTopthree_GET_MSELC_MSEL()				(IO_CHIPTOP.MSELC.bit.MSEL)													/**< Get power-supply voltage Control */
#define	DdTopthree_SET_MSELC_MSEL(val)			{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.MSELC.bit.MSEL=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set power-supply voltage Control */


#define	DdTopthree_GET_DBCNT1_T07DC()			(IO_CHIPTOP.DBCNT1.bit.T07DC)												/**< Get Driving Force Control 07 */
#define	DdTopthree_SET_DBCNT1_T07DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T07DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 07 */
#define	DdTopthree_GET_DBCNT1_T08DC()			(IO_CHIPTOP.DBCNT1.bit.T08DC)												/**< Get Driving Force Control 08 */
#define	DdTopthree_SET_DBCNT1_T08DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T08DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 08 */
#define	DdTopthree_GET_DBCNT1_T09DC()			(IO_CHIPTOP.DBCNT1.bit.T09DC)												/**< Get Driving Force Control 09 */
#define	DdTopthree_SET_DBCNT1_T09DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T09DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 09 */
#define	DdTopthree_GET_DBCNT1_T10DC()			(IO_CHIPTOP.DBCNT1.bit.T10DC)												/**< Get Driving Force Control 10 */
#define	DdTopthree_SET_DBCNT1_T10DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T10DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 10 */
#define	DdTopthree_GET_DBCNT1_T11DC()			(IO_CHIPTOP.DBCNT1.bit.T11DC)												/**< Get Driving Force Control 11 */
#define	DdTopthree_SET_DBCNT1_T11DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T11DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 11 */
#define	DdTopthree_GET_DBCNT1_T12DC()			(IO_CHIPTOP.DBCNT1.bit.T12DC)												/**< Get Driving Force Control 12 */
#define	DdTopthree_SET_DBCNT1_T12DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T12DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 12 */
#define	DdTopthree_GET_DBCNT1_T13DC()			(IO_CHIPTOP.DBCNT1.bit.T13DC)												/**< Get Driving Force Control 13 */
#define	DdTopthree_SET_DBCNT1_T13DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T13DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 13 */
#define	DdTopthree_GET_DBCNT1_T14DC()			(IO_CHIPTOP.DBCNT1.bit.T14DC)												/**< Get Driving Force Control 14 */
#define	DdTopthree_SET_DBCNT1_T14DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T14DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 14 */
#define	DdTopthree_GET_DBCNT1_T15DC()			(IO_CHIPTOP.DBCNT1.bit.T15DC)												/**< Get Driving Force Control 15 */
#define	DdTopthree_SET_DBCNT1_T15DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT1.bit.T15DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 15 */
#define	DdTopthree_GET_DBCNT2_T16DC()			(IO_CHIPTOP.DBCNT2.bit.T16DC)												/**< Get Driving Force Control 16 */
#define	DdTopthree_SET_DBCNT2_T16DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T16DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 16 */
#define	DdTopthree_GET_DBCNT2_T17DC()			(IO_CHIPTOP.DBCNT2.bit.T17DC)												/**< Get Driving Force Control 17 */
#define	DdTopthree_SET_DBCNT2_T17DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T17DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 17 */
#define	DdTopthree_GET_DBCNT2_T18DC()			(IO_CHIPTOP.DBCNT2.bit.T18DC)												/**< Get Driving Force Control 18 */
#define	DdTopthree_SET_DBCNT2_T18DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T18DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 18 */
#define	DdTopthree_GET_DBCNT2_T19DC()			(IO_CHIPTOP.DBCNT2.bit.T19DC)												/**< Get Driving Force Control 19 */
#define	DdTopthree_SET_DBCNT2_T19DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T19DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 19 */
#define	DdTopthree_GET_DBCNT2_T20DC()			(IO_CHIPTOP.DBCNT2.bit.T20DC)												/**< Get Driving Force Control 20 */
#define	DdTopthree_SET_DBCNT2_T20DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T20DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 20 */
#define	DdTopthree_GET_DBCNT2_T21DC()			(IO_CHIPTOP.DBCNT2.bit.T21DC)												/**< Get Driving Force Control 21 */
#define	DdTopthree_SET_DBCNT2_T21DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T21DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 21 */
#define	DdTopthree_GET_DBCNT2_T22DC()			(IO_CHIPTOP.DBCNT2.bit.T22DC)												/**< Get Driving Force Control 22 */
#define	DdTopthree_SET_DBCNT2_T22DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T22DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 22 */
#define	DdTopthree_GET_DBCNT2_T23DC()			(IO_CHIPTOP.DBCNT2.bit.T23DC)												/**< Get Driving Force Control 23 */
#define	DdTopthree_SET_DBCNT2_T23DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T23DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 23 */
#define	DdTopthree_GET_DBCNT2_T24DC()			(IO_CHIPTOP.DBCNT2.bit.T24DC)												/**< Get Driving Force Control 24 */
#define	DdTopthree_SET_DBCNT2_T24DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T24DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 24 */
#define	DdTopthree_GET_DBCNT2_T25DC()			(IO_CHIPTOP.DBCNT2.bit.T25DC)												/**< Get Driving Force Control 25 */
#define	DdTopthree_SET_DBCNT2_T25DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T25DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 25 */
#define	DdTopthree_GET_DBCNT2_T26DC()			(IO_CHIPTOP.DBCNT2.bit.T26DC)												/**< Get Driving Force Control 26 */
#define	DdTopthree_SET_DBCNT2_T26DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T26DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 26 */
#define	DdTopthree_GET_DBCNT2_T27DC()			(IO_CHIPTOP.DBCNT2.bit.T27DC)												/**< Get Driving Force Control 27 */
#define	DdTopthree_SET_DBCNT2_T27DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T27DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 27 */
#define	DdTopthree_GET_DBCNT2_T28DC()			(IO_CHIPTOP.DBCNT2.bit.T28DC)												/**< Get Driving Force Control 28 */
#define	DdTopthree_SET_DBCNT2_T28DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T28DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 28 */
#define	DdTopthree_GET_DBCNT2_T29DC()			(IO_CHIPTOP.DBCNT2.bit.T29DC)												/**< Get Driving Force Control 29 */
#define	DdTopthree_SET_DBCNT2_T29DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T29DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 29 */
#define	DdTopthree_GET_DBCNT2_T30DC()			(IO_CHIPTOP.DBCNT2.bit.T30DC)												/**< Get Driving Force Control 30 */
#define	DdTopthree_SET_DBCNT2_T30DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T30DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 30 */
#define	DdTopthree_GET_DBCNT2_T31DC()			(IO_CHIPTOP.DBCNT2.bit.T31DC)												/**< Get Driving Force Control 31 */
#define	DdTopthree_SET_DBCNT2_T31DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT2.bit.T31DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 31 */
#define	DdTopthree_GET_DBCNT3_T32DC()			(IO_CHIPTOP.DBCNT3.bit.T32DC)												/**< Get Driving Force Control 32 */
#define	DdTopthree_SET_DBCNT3_T32DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T32DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 32 */
#define	DdTopthree_GET_DBCNT3_T33DC()			(IO_CHIPTOP.DBCNT3.bit.T33DC)												/**< Get Driving Force Control 33 */
#define	DdTopthree_SET_DBCNT3_T33DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T33DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 33 */
#define	DdTopthree_GET_DBCNT3_T34DC()			(IO_CHIPTOP.DBCNT3.bit.T34DC)												/**< Get Driving Force Control 34 */
#define	DdTopthree_SET_DBCNT3_T34DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T34DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 34 */
#define	DdTopthree_GET_DBCNT3_T35DC()			(IO_CHIPTOP.DBCNT3.bit.T35DC)												/**< Get Driving Force Control 35 */
#define	DdTopthree_SET_DBCNT3_T35DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T35DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 35 */
#define	DdTopthree_GET_DBCNT3_T36DC()			(IO_CHIPTOP.DBCNT3.bit.T36DC)												/**< Get Driving Force Control 36 */
#define	DdTopthree_SET_DBCNT3_T36DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T36DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 36 */
#define	DdTopthree_GET_DBCNT3_T37DC()			(IO_CHIPTOP.DBCNT3.bit.T37DC)												/**< Get Driving Force Control 37 */
#define	DdTopthree_SET_DBCNT3_T37DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T37DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 37 */
#define	DdTopthree_GET_DBCNT3_T38DC()			(IO_CHIPTOP.DBCNT3.bit.T38DC)												/**< Get Driving Force Control 38 */
#define	DdTopthree_SET_DBCNT3_T38DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T38DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 38 */
#define	DdTopthree_GET_DBCNT3_T39DC()			(IO_CHIPTOP.DBCNT3.bit.T39DC)												/**< Get Driving Force Control 39 */
#define	DdTopthree_SET_DBCNT3_T39DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T39DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 39 */
#define	DdTopthree_GET_DBCNT3_T40DC()			(IO_CHIPTOP.DBCNT3.bit.T40DC)												/**< Get Driving Force Control 40 */
#define	DdTopthree_SET_DBCNT3_T40DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T40DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 40 */
#define	DdTopthree_GET_DBCNT3_T41DC()			(IO_CHIPTOP.DBCNT3.bit.T41DC)												/**< Get Driving Force Control 41 */
#define	DdTopthree_SET_DBCNT3_T41DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T41DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 41 */
#define	DdTopthree_GET_DBCNT3_T42DC()			(IO_CHIPTOP.DBCNT3.bit.T42DC)												/**< Get Driving Force Control 42 */
#define	DdTopthree_SET_DBCNT3_T42DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T42DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 42 */
#define	DdTopthree_GET_DBCNT3_T43DC()			(IO_CHIPTOP.DBCNT3.bit.T43DC)												/**< Get Driving Force Control 43 */
#define	DdTopthree_SET_DBCNT3_T43DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T43DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 43 */
#define	DdTopthree_GET_DBCNT3_T44DC()			(IO_CHIPTOP.DBCNT3.bit.T44DC)												/**< Get Driving Force Control 44 */
#define	DdTopthree_SET_DBCNT3_T44DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T44DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 44 */
#define	DdTopthree_GET_DBCNT3_T45DC()			(IO_CHIPTOP.DBCNT3.bit.T45DC)												/**< Get Driving Force Control 45 */
#define	DdTopthree_SET_DBCNT3_T45DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T45DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 45 */
#define	DdTopthree_GET_DBCNT3_T46DC()			(IO_CHIPTOP.DBCNT3.bit.T46DC)												/**< Get Driving Force Control 46 */
#define	DdTopthree_SET_DBCNT3_T46DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T46DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 46 */
#define	DdTopthree_GET_DBCNT3_T47DC()			(IO_CHIPTOP.DBCNT3.bit.T47DC)												/**< Get Driving Force Control 47 */
#define	DdTopthree_SET_DBCNT3_T47DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT3.bit.T47DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 47 */
#define	DdTopthree_GET_DBCNT4_T48DC()			(IO_CHIPTOP.DBCNT4.bit.T48DC)												/**< Get Driving Force Control 48 */
#define	DdTopthree_SET_DBCNT4_T48DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T48DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 48 */
#define	DdTopthree_GET_DBCNT4_T49DC()			(IO_CHIPTOP.DBCNT4.bit.T49DC)												/**< Get Driving Force Control 49 */
#define	DdTopthree_SET_DBCNT4_T49DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T49DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 49 */
#define	DdTopthree_GET_DBCNT4_T50DC()			(IO_CHIPTOP.DBCNT4.bit.T50DC)												/**< Get Driving Force Control 50 */
#define	DdTopthree_SET_DBCNT4_T50DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T50DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 50 */
#define	DdTopthree_GET_DBCNT4_T51DC()			(IO_CHIPTOP.DBCNT4.bit.T51DC)												/**< Get Driving Force Control 51 */
#define	DdTopthree_SET_DBCNT4_T51DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock) \
												;IO_CHIPTOP.DBCNT4.bit.T51DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 51 */
#define	DdTopthree_GET_DBCNT4_T52DC()			(IO_CHIPTOP.DBCNT4.bit.T52DC)												/**< Get Driving Force Control 52 */
#define	DdTopthree_SET_DBCNT4_T52DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T52DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 52 */
#define	DdTopthree_GET_DBCNT4_T53DC()			(IO_CHIPTOP.DBCNT4.bit.T53DC)												/**< Get Driving Force Control 53 */
#define	DdTopthree_SET_DBCNT4_T53DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T53DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 53 */
#define	DdTopthree_GET_DBCNT4_T54DC()			(IO_CHIPTOP.DBCNT4.bit.T54DC)												/**< Get Driving Force Control 54 */
#define	DdTopthree_SET_DBCNT4_T54DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T54DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 54 */
#define	DdTopthree_GET_DBCNT4_T55DC()			(IO_CHIPTOP.DBCNT4.bit.T55DC)												/**< Get Driving Force Control 55 */
#define	DdTopthree_SET_DBCNT4_T55DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T55DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 55 */
#define	DdTopthree_GET_DBCNT4_T56DC()			(IO_CHIPTOP.DBCNT4.bit.T56DC)												/**< Get Driving Force Control 56 */
#define	DdTopthree_SET_DBCNT4_T56DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T56DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 56 */
#define	DdTopthree_GET_DBCNT4_T57DC()			(IO_CHIPTOP.DBCNT4.bit.T57DC)												/**< Get Driving Force Control 57 */
#define	DdTopthree_SET_DBCNT4_T57DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T57DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 57 */
#define	DdTopthree_GET_DBCNT4_T58DC()			(IO_CHIPTOP.DBCNT4.bit.T58DC)												/**< Get Driving Force Control 58 */
#define	DdTopthree_SET_DBCNT4_T58DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T58DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 58 */
#define	DdTopthree_GET_DBCNT4_T59DC()			(IO_CHIPTOP.DBCNT4.bit.T59DC)												/**< Get Driving Force Control 59 */
#define	DdTopthree_SET_DBCNT4_T59DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T59DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 59 */
#define	DdTopthree_GET_DBCNT4_T60DC()			(IO_CHIPTOP.DBCNT4.bit.T60DC)												/**< Get Driving Force Control 60 */
#define	DdTopthree_SET_DBCNT4_T60DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T60DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 60 */
#define	DdTopthree_GET_DBCNT4_T61DC()			(IO_CHIPTOP.DBCNT4.bit.T61DC)												/**< Get Driving Force Control 61 */
#define	DdTopthree_SET_DBCNT4_T61DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T61DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 61 */
#define	DdTopthree_GET_DBCNT4_T62DC()			(IO_CHIPTOP.DBCNT4.bit.T62DC)												/**< Get Driving Force Control 62 */
#define	DdTopthree_SET_DBCNT4_T62DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T62DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 62 */
#define	DdTopthree_GET_DBCNT4_T63DC()			(IO_CHIPTOP.DBCNT4.bit.T63DC)												/**< Get Driving Force Control 63 */
#define	DdTopthree_SET_DBCNT4_T63DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT4.bit.T63DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 63 */
#define	DdTopthree_GET_DBCNT5_T64DC()			(IO_CHIPTOP.DBCNT5.bit.T64DC)												/**< Get Driving Force Control 64 */
#define	DdTopthree_SET_DBCNT5_T64DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT5.bit.T64DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 64 */
#define	DdTopthree_GET_DBCNT5_T65DC()			(IO_CHIPTOP.DBCNT5.bit.T65DC)												/**< Get Driving Force Control 65 */
#define	DdTopthree_SET_DBCNT5_T65DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT5.bit.T65DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 65 */
#define	DdTopthree_GET_DBCNT5_T66DC()			(IO_CHIPTOP.DBCNT5.bit.T66DC)												/**< Get Driving Force Control 66 */
#define	DdTopthree_SET_DBCNT5_T66DC(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.DBCNT5.bit.T66DC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set Driving Force Control 66 */

#define	DdTopthree_GET_PUDCNT_EMMCNICS()		(IO_CHIPTOP.PUDCNT.bit.EMMCNICS)											/**< Get resource signal Select */
#define	DdTopthree_SET_PUDCNT_EMMCNICS(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.EMMCNICS=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set resource signal Select */
#define	DdTopthree_GET_PUDCNT_EMDATPUE()		(IO_CHIPTOP.PUDCNT.bit.EMDATPUE)											/**< Get EMDATA Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_EMDATPUE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.EMDATPUE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set EMDATA Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_EMCMDPUE()		(IO_CHIPTOP.PUDCNT.bit.EMCMDPUE)											/**< Get EMCMD Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_EMCMDPUE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.EMCMDPUE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set EMCMD Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_EMDSPDE()			(IO_CHIPTOP.PUDCNT.bit.EMDSPDE)												/**< Get EMDS Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_EMDSPDE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.EMDSPDE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set EMDS Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_NFDATPUE()		(IO_CHIPTOP.PUDCNT.bit.NFDATPUE)											/**< Get NFD Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_NFDATPUE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.NFDATPUE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set NFD Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_NFRBXPUE()		(IO_CHIPTOP.PUDCNT.bit.NFRBXPUE)											/**< Get NFRBX Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_NFRBXPUE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.NFRBXPUE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set NFRBX Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_NFDQSPUE()		(IO_CHIPTOP.PUDCNT.bit.NFDQSPUE)											/**< Get NFDQS Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_NFDQSPUE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.NFDQSPUE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set NFDQS Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_SP1MISOPE()		(IO_CHIPTOP.PUDCNT.bit.SP1MISOPE)											/**< Get SP2MISO Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_SP1MISOPE(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.SP1MISOPE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SP2MISO Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_SP1MOSIPE()		(IO_CHIPTOP.PUDCNT.bit.SP1MOSIPE)											/**< Get SP2MOSI Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_SP1MOSIPE(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.SP1MOSIPE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SP2MOSI Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_SP1SCKPE()		(IO_CHIPTOP.PUDCNT.bit.SP1SCKPE)											/**< Get SP2SCK Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_SP1SCKPE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.SP1SCKPE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SP2SCK Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_SP1CS0PE()		(IO_CHIPTOP.PUDCNT.bit.SP1CS0PE)											/**< Get SP2CS0X Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_SP1CS0PE(val)		{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.SP1CS0PE=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SP2CS0X Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_SP1MISOUDC()		(IO_CHIPTOP.PUDCNT.bit.SP1MISOUDC)											/**< Get SP2MISO Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_SP1MISOUDC(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.SP1MISOUDC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SP2MISO Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_SP1MOSIUDC()		(IO_CHIPTOP.PUDCNT.bit.SP1MOSIUDC)											/**< Get SP2MOSI Pull up/down Registance */
#define	DdTopthree_SET_PUDCNT_SP1MOSIUDC(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.SP1MOSIUDC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SP2MOSI Pull up/down Registance */
#define	DdTopthree_GET_PUDCNT_SP1SCKUDC()		(IO_CHIPTOP.PUDCNT.bit.SP1SCKUDC)											/**< Get SP2SCK Pull up/down Select */
#define	DdTopthree_SET_PUDCNT_SP1SCKUDC(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.SP1SCKUDC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SP2SCK Pull up/down Select */
#define	DdTopthree_GET_PUDCNT_SP1CS0UDC()		(IO_CHIPTOP.PUDCNT.bit.SP1CS0UDC)											/**< Get SP2CS0X Pull up/down Select */
#define	DdTopthree_SET_PUDCNT_SP1CS0UDC(val)	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock); \
												IO_CHIPTOP.PUDCNT.bit.SP1CS0UDC=(val); \
												Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}						/**< Set SP2CS0X Pull up/down Select */


typedef struct 	_DdTopthree 					DdTopthree;
typedef struct 	_DdTopthreeClass 			DdTopthreeClass;
typedef struct 	_DdTopthreePrivate 		DdTopthreePrivate;

struct _DdTopthree{
	GObject parent;
};

struct _DdTopthreeClass{
	GObjectClass parentclass;
};


GType 								dd_topthree_get_type(void) G_GNUC_CONST;
DdTopthree* 					dd_topthree_new(void);


/*@}*/
G_END_DECLS


#endif /* __DD_TOPTHREE_H__ */

