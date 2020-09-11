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


#ifndef  __DD_TOPTWO_H__
#define __DD_TOPTWO_H__


#include "ddim_typedef.h"
#include "driver_common.h"
#include "chiptop.h"
#include "dd_arm.h"
#include <glib-object.h>


G_BEGIN_DECLS


#define DD_TYPE_TOPTWO								(dd_toptwo_get_type ())
#define DD_TOPTWO(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), DD_TYPE_TOPTWO, DdToptwo))
#define DD_TOPTWO_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST((klass), DD_TYPE_TOPTWO, DdToptwoClass))
#define DD_IS_TOPTWO(obj)							(G_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_TOPTWO))
#define DD_IS_TOPTWO_CLASS(klass)		 	(G_TYPE_CHECK_CLASS_TYPE ((klass), DD_TYPE_TOPTWO))
#define DD_TOPTWO_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), DD_TYPE_TOPTWO, DdToptwoClass))

// CLKSTOP
#define	DdToptwo_GET_CLKSTOP1()				(IO_CHIPTOP.CLKSTOP1.word)														/**< Get Clock Stop 1 */
#define	DdToptwo_GET_CLKSTOP2()				(IO_CHIPTOP.CLKSTOP2.word)														/**< Get Clock Stop 2 */
#define	DdToptwo_GET_CLKSTOP3()				(IO_CHIPTOP.CLKSTOP3.word)														/**< Get Clock Stop 3 */
#define	DdToptwo_GET_CLKSTOP4()				(IO_CHIPTOP.CLKSTOP4.word)														/**< Get Clock Stop 4 */
#define	DdToptwo_GET_CLKSTOP5()				(IO_CHIPTOP.CLKSTOP5.word)														/**< Get Clock Stop 5 */
#define	DdToptwo_GET_CLKSTOP6()				(IO_CHIPTOP.CLKSTOP6.word)														/**< Get Clock Stop 6 */
#define	DdToptwo_GET_CLKSTOP7()				(IO_CHIPTOP.CLKSTOP7.word)														/**< Get Clock Stop 7 */
#define	DdToptwo_GET_CLKSTOP8()				(IO_CHIPTOP.CLKSTOP8.word)														/**< Get Clock Stop 8 */
#define	DdToptwo_GET_CLKSTOP9()				(IO_CHIPTOP.CLKSTOP9.word)														/**< Get Clock Stop 9 */
#define	DdToptwo_GET_CLKSTOP10()			(IO_CHIPTOP.CLKSTOP10.word)														/**< Get Clock Stop 10 */
#define	DdToptwo_GET_CLKSTOP11()			(IO_CHIPTOP.CLKSTOP11.word)														/**< Get Clock Stop 11 */
#define	DdToptwo_GET_CLKSTOP12()			(IO_CHIPTOP.CLKSTOP12.word)														/**< Get Clock Stop 12 */
#define	DdToptwo_GET_CLKSTOP13()			(IO_CHIPTOP.CLKSTOP13.word)														/**< Get Clock Stop 13 */
#define	DdToptwo_GET_CLKSTOP14()			(IO_CHIPTOP.CLKSTOP14.word)														/**< Get Clock Stop 14 */

// CLKSTOP1
#define	DdToptwo_GET_CLKSTOP1_DSPCK()				(IO_CHIPTOP.CLKSTOP1.bit.DSPCK)												/**< Get DSP Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_DSPCK(val)			(IO_CHIPTOP.CLKSTOP1.bit.DSPCK=(0x02|val))									/**< Set DSP Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_DSPAX()				(IO_CHIPTOP.CLKSTOP1.bit.DSPAX)												/**< Get EXS AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_DSPAX(val)			(IO_CHIPTOP.CLKSTOP1.bit.DSPAX=(0x02|val))									/**< Set EXS AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_SENCK()				(IO_CHIPTOP.CLKSTOP1.bit.SENCK)												/**< Get SENSOR Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_SENCK(val)			(IO_CHIPTOP.CLKSTOP1.bit.SENCK=(0x02|val))									/**< Set SENSOR Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_SENAX()				(IO_CHIPTOP.CLKSTOP1.bit.SENAX)												/**< Get SENSOR AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_SENAX(val)			(IO_CHIPTOP.CLKSTOP1.bit.SENAX=(0x02|val))									/**< Set SENSOR AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_SENAH()				(IO_CHIPTOP.CLKSTOP1.bit.SENAH)												/**< Get SENSOR AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_SENAH(val)			(IO_CHIPTOP.CLKSTOP1.bit.SENAH=(0x02|val))									/**< Set SENSOR AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_SENAP()				(IO_CHIPTOP.CLKSTOP1.bit.SENAP)												/**< Get SENSOR APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_SENAP(val)			(IO_CHIPTOP.CLKSTOP1.bit.SENAP=(0x02|val))									/**< Set SENSOR APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_GPIOAP()			(IO_CHIPTOP.CLKSTOP1.bit.GPIOAP)											/**< Get GPIO APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_GPIOAP(val)			(IO_CHIPTOP.CLKSTOP1.bit.GPIOAP=(0x02|val))									/**< Set GPIO APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_AU0CK()				(IO_CHIPTOP.CLKSTOP1.bit.AU0CK)												/**< Get Audio 0ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_AU0CK(val)			(IO_CHIPTOP.CLKSTOP1.bit.AU0CK=(0x02|val))									/**< Set Audio 0ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_AU2CK()				(IO_CHIPTOP.CLKSTOP1.bit.AU2CK)												/**< Get Audio 2ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_AU2CK(val)			(IO_CHIPTOP.CLKSTOP1.bit.AU2CK=(0x02|val))									/**< Set Audio 2ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_AU3CK()				(IO_CHIPTOP.CLKSTOP1.bit.AU3CK)												/**< Get Audio 3ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_AU3CK(val)			(IO_CHIPTOP.CLKSTOP1.bit.AU3CK=(0x02|val))									/**< Set Audio 3ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_AU4CK()				(IO_CHIPTOP.CLKSTOP1.bit.AU4CK)												/**< Get Audio 4ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_AU4CK(val)			(IO_CHIPTOP.CLKSTOP1.bit.AU4CK=(0x02|val))									/**< Set Audio 4ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_AU5CK()				(IO_CHIPTOP.CLKSTOP1.bit.AU5CK)												/**< Get Audio 5ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_AU5CK(val)			(IO_CHIPTOP.CLKSTOP1.bit.AU5CK=(0x02|val))									/**< Set Audio 5ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_NETAUCK()			(IO_CHIPTOP.CLKSTOP1.bit.NETAUCK)											/**< Get NETSEC Audio Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_NETAUCK(val)		(IO_CHIPTOP.CLKSTOP1.bit.NETAUCK=(0x02|val))								/**< Set NETSEC Audio Clock Stop */
#define	DdToptwo_GET_CLKSTOP1_TEMPCK()			(IO_CHIPTOP.CLKSTOP1.bit.TEMPCK)											/**< Get Temperature Sensor Clock Stop */
#define	DdToptwo_SET_CLKSTOP1_TEMPCK(val)			(IO_CHIPTOP.CLKSTOP1.bit.TEMPCK=(0x02|val))									/**< Set Temperature Sensor Clock Stop */

// CLKSTOP2
#define	DdToptwo_GET_CLKSTOP2_RCK()				(IO_CHIPTOP.CLKSTOP2.bit.RCK)												/**< Get PERI RCK Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_RCK(val)			(IO_CHIPTOP.CLKSTOP2.bit.RCK=(0x02|val))									/**< Set PERI RCK Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_UHS1CK0()			(IO_CHIPTOP.CLKSTOP2.bit.UHS1CK0)											/**< Get UHS1 ch0 Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_UHS1CK0(val)		(IO_CHIPTOP.CLKSTOP2.bit.UHS1CK0=(0x02|val))								/**< Set UHS1 ch0 Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_UHS1CK1()			(IO_CHIPTOP.CLKSTOP2.bit.UHS1CK1)											/**< Get UHS1 ch1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_UHS1CK1(val)		(IO_CHIPTOP.CLKSTOP2.bit.UHS1CK1=(0x02|val))								/**< Set UHS1 ch1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_UHS1CK2()			(IO_CHIPTOP.CLKSTOP2.bit.UHS1CK2)											/**< Get UHS1 ch2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_UHS1CK2(val)		(IO_CHIPTOP.CLKSTOP2.bit.UHS1CK2=(0x02|val))								/**< Set UHS1 ch2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_UHS2CK()			(IO_CHIPTOP.CLKSTOP2.bit.UHS2CK)											/**< Get UHS2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_UHS2CK(val)			(IO_CHIPTOP.CLKSTOP2.bit.UHS2CK=(0x02|val))									/**< Set UHS2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_NFCK()				(IO_CHIPTOP.CLKSTOP2.bit.NFCK)												/**< Get Nand Flash Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_NFCK(val)			(IO_CHIPTOP.CLKSTOP2.bit.NFCK=(0x02|val))									/**< Set Nand Flash Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_EMMCCK()			(IO_CHIPTOP.CLKSTOP2.bit.EMMCCK)											/**< Get eMMC Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_EMMCCK(val)			(IO_CHIPTOP.CLKSTOP2.bit.EMMCCK=(0x02|val))									/**< Set eMMC Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_NETSECCK()			(IO_CHIPTOP.CLKSTOP2.bit.NETSECCK)											/**< Get NETSEC Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_NETSECCK(val)		(IO_CHIPTOP.CLKSTOP2.bit.NETSECCK=(0x02|val))								/**< Set NETSEC Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_NETRCK()			(IO_CHIPTOP.CLKSTOP2.bit.NETRCK)											/**< Get NETSEC RCK Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_NETRCK(val)			(IO_CHIPTOP.CLKSTOP2.bit.NETRCK=(0x02|val))									/**< Set NETSEC RCK Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_EXSAX()				(IO_CHIPTOP.CLKSTOP2.bit.EXSAX)												/**< Get EXS AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_EXSAX(val)			(IO_CHIPTOP.CLKSTOP2.bit.EXSAX=(0x02|val))									/**< Set EXS AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_SPICK()				(IO_CHIPTOP.CLKSTOP2.bit.SPICK)												/**< Get SPI Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_SPICK(val)			(IO_CHIPTOP.CLKSTOP2.bit.SPICK=(0x02|val))									/**< Set SPI Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_SLIMB00CK()			(IO_CHIPTOP.CLKSTOP2.bit.SLIMB00CK)											/**< Get SLIMbus 00ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_SLIMB00CK(val)		(IO_CHIPTOP.CLKSTOP2.bit.SLIMB00CK=(0x02|val))								/**< Set SLIMbus 00ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_SLIMB01CK()			(IO_CHIPTOP.CLKSTOP2.bit.SLIMB01CK)											/**< Get SLIMbus 01ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_SLIMB01CK(val)		(IO_CHIPTOP.CLKSTOP2.bit.SLIMB01CK=(0x02|val))								/**< Set SLIMbus 01ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_SLIMB10CK()			(IO_CHIPTOP.CLKSTOP2.bit.SLIMB10CK)											/**< Get SLIMbus 10ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_SLIMB10CK(val)		(IO_CHIPTOP.CLKSTOP2.bit.SLIMB10CK=(0x02|val))								/**< Set SLIMbus 10ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_SLIMB11CK()			(IO_CHIPTOP.CLKSTOP2.bit.SLIMB11CK)											/**< Get SLIMbus 11ch Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_SLIMB11CK(val)		(IO_CHIPTOP.CLKSTOP2.bit.SLIMB11CK=(0x02|val))								/**< Set SLIMbus 11ch Clock Stop */
#define	DdToptwo_GET_CLKSTOP2_PCISUPPCK()			(IO_CHIPTOP.CLKSTOP2.bit.PCISUPPCK)											/**< Get PCI sub Clock Stop */
#define	DdToptwo_SET_CLKSTOP2_PCISUPPCK(val)		(IO_CHIPTOP.CLKSTOP2.bit.PCISUPPCK=(0x02|val))								/**< Set PCI sub Clock Stop */

// CLKSTOP3
#define	DdToptwo_GET_CLKSTOP3_IIPCK()				(IO_CHIPTOP.CLKSTOP3.bit.IIPCK)												/**< Get IIP Macro Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_IIPCK(val)			(IO_CHIPTOP.CLKSTOP3.bit.IIPCK=(0x02|val))									/**< Set IIP Macro Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_IIPAP()				(IO_CHIPTOP.CLKSTOP3.bit.IIPAP)												/**< Get IIP Macro APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_IIPAP(val)			(IO_CHIPTOP.CLKSTOP3.bit.IIPAP=(0x02|val))									/**< Set IIP Macro APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_IIPAH()				(IO_CHIPTOP.CLKSTOP3.bit.IIPAH)												/**< Get IIP Macro AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_IIPAH(val)			(IO_CHIPTOP.CLKSTOP3.bit.IIPAH=(0x02|val))									/**< Set IIP Macro AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_IIPAX()				(IO_CHIPTOP.CLKSTOP3.bit.IIPAX)												/**< Get IIP Macro AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_IIPAX(val)			(IO_CHIPTOP.CLKSTOP3.bit.IIPAX=(0x02|val))									/**< Set IIP Macro AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_LCDCK()				(IO_CHIPTOP.CLKSTOP3.bit.LCDCK)												/**< Get DISP LCD Macro Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_LCDCK(val)			(IO_CHIPTOP.CLKSTOP3.bit.LCDCK=(0x02|val))									/**< Set DISP LCD Macro Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_HIFCK()				(IO_CHIPTOP.CLKSTOP3.bit.HIFCK)												/**< Get DISP HIF Macro Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_HIFCK(val)			(IO_CHIPTOP.CLKSTOP3.bit.HIFCK=(0x02|val))									/**< Set DISP HIF Macro Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_MIFCK()				(IO_CHIPTOP.CLKSTOP3.bit.MIFCK)												/**< Get DISP MIF Macro Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_MIFCK(val)			(IO_CHIPTOP.CLKSTOP3.bit.MIFCK=(0x02|val))									/**< Set DISP MIF Macro Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_DISPAP()			(IO_CHIPTOP.CLKSTOP3.bit.DISPAP)											/**< Get DISP Macro APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_DISPAP(val)			(IO_CHIPTOP.CLKSTOP3.bit.DISPAP=(0x02|val))									/**< Set DISP Macro APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_DISPAH()			(IO_CHIPTOP.CLKSTOP3.bit.DISPAH)											/**< Get DISP Macro AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_DISPAH(val)			(IO_CHIPTOP.CLKSTOP3.bit.DISPAH=(0x02|val))									/**< Set DISP Macro AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_DISPAX()			(IO_CHIPTOP.CLKSTOP3.bit.DISPAX)											/**< Get DISP Macro AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_DISPAX(val)			(IO_CHIPTOP.CLKSTOP3.bit.DISPAX=(0x02|val))									/**< Set DISP Macro AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_JPGCK()				(IO_CHIPTOP.CLKSTOP3.bit.JPGCK)												/**< Get JPEG Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_JPGCK(val)			(IO_CHIPTOP.CLKSTOP3.bit.JPGCK=(0x02|val))									/**< Set JPEG Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_JPGAX()				(IO_CHIPTOP.CLKSTOP3.bit.JPGAX)												/**< Get JPEG AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_JPGAX(val)			(IO_CHIPTOP.CLKSTOP3.bit.JPGAX=(0x02|val))									/**< Set JPEG AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_JPGAH()				(IO_CHIPTOP.CLKSTOP3.bit.JPGAH)												/**< Get JPEG AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_JPGAH(val)			(IO_CHIPTOP.CLKSTOP3.bit.JPGAH=(0x02|val))									/**< Set JPEG AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_JPGAP()				(IO_CHIPTOP.CLKSTOP3.bit.JPGAP)												/**< Get JPEG APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_JPGAP(val)			(IO_CHIPTOP.CLKSTOP3.bit.JPGAP=(0x02|val))									/**< Set JPEG APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_PDM0CK()			(IO_CHIPTOP.CLKSTOP3.bit.PDM0CK)											/**< Get PDM0 Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_PDM0CK(val)			(IO_CHIPTOP.CLKSTOP3.bit.PDM0CK=(0x02|val))									/**< Set PDM0 Clock Stop */
#define	DdToptwo_GET_CLKSTOP3_PDM1CK()			(IO_CHIPTOP.CLKSTOP3.bit.PDM1CK)											/**< Get PDM1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP3_PDM1CK(val)			(IO_CHIPTOP.CLKSTOP3.bit.PDM1CK=(0x02|val))									/**< Set PDM1 Clock Stop */

// CLKSTOP4
#define	DdToptwo_GET_CLKSTOP4_GPUCK()				(IO_CHIPTOP.CLKSTOP4.bit.GPUCK)												/**< Get MXIC Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_GPUCK(val)			(IO_CHIPTOP.CLKSTOP4.bit.GPUCK=(0x02|val))									/**< Set MXIC Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_GPUAP()				(IO_CHIPTOP.CLKSTOP4.bit.GPUAP)												/**< Get MXIC APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_GPUAP(val)			(IO_CHIPTOP.CLKSTOP4.bit.GPUAP=(0x02|val))									/**< Set MXIC APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_GPUAH()				(IO_CHIPTOP.CLKSTOP4.bit.GPUAH)												/**< Get MXIC AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_GPUAH(val)			(IO_CHIPTOP.CLKSTOP4.bit.GPUAH=(0x02|val))									/**< Set MXIC AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_GPUAX()				(IO_CHIPTOP.CLKSTOP4.bit.GPUAX)												/**< Get MXIC AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_GPUAX(val)			(IO_CHIPTOP.CLKSTOP4.bit.GPUAX=(0x02|val))									/**< Set MXIC AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_FPT0CK()			(IO_CHIPTOP.CLKSTOP4.bit.FPT0CK)											/**< Get FPT0 Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_FPT0CK(val)			(IO_CHIPTOP.CLKSTOP4.bit.FPT0CK=(0x02|val))									/**< Set FPT0 Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_FPT0AX()			(IO_CHIPTOP.CLKSTOP4.bit.FPT0AX)											/**< Get FPT0 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_FPT0AX(val)			(IO_CHIPTOP.CLKSTOP4.bit.FPT0AX=(0x02|val))									/**< Set FPT0 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_FPT0AH()			(IO_CHIPTOP.CLKSTOP4.bit.FPT0AH)											/**< Get FPT0 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_FPT0AH(val)			(IO_CHIPTOP.CLKSTOP4.bit.FPT0AH=(0x02|val))									/**< Set FPT0 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_FPT0AP()			(IO_CHIPTOP.CLKSTOP4.bit.FPT0AP)											/**< Get FPT0 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_FPT0AP(val)			(IO_CHIPTOP.CLKSTOP4.bit.FPT0AP=(0x02|val))									/**< Set FPT0 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_FPT1CK()			(IO_CHIPTOP.CLKSTOP4.bit.FPT1CK)											/**< Get FPT1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_FPT1CK(val)			(IO_CHIPTOP.CLKSTOP4.bit.FPT1CK=(0x02|val))									/**< Set FPT1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_FPT1AP()			(IO_CHIPTOP.CLKSTOP4.bit.FPT1AP)											/**< Get FPT1 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_FPT1AP(val)			(IO_CHIPTOP.CLKSTOP4.bit.FPT1AP=(0x02|val))									/**< Set FPT1 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_FPT1AH()			(IO_CHIPTOP.CLKSTOP4.bit.FPT1AH)											/**< Get FPT1 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_FPT1AH(val)			(IO_CHIPTOP.CLKSTOP4.bit.FPT1AH=(0x02|val))									/**< Set FPT1 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_FPT1AX()			(IO_CHIPTOP.CLKSTOP4.bit.FPT1AX)											/**< Get FPT1 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_FPT1AX(val)			(IO_CHIPTOP.CLKSTOP4.bit.FPT1AX=(0x02|val))									/**< Set FPT1 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_APCK0()				(IO_CHIPTOP.CLKSTOP4.bit.APCK0)												/**< Get SNAPCLKO0 Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_APCK0(val)			(IO_CHIPTOP.CLKSTOP4.bit.APCK0=(0x02|val))									/**< Set SNAPCLKO0 Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_APCK1()				(IO_CHIPTOP.CLKSTOP4.bit.APCK1)												/**< Get SNAPCLKO1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_APCK1(val)			(IO_CHIPTOP.CLKSTOP4.bit.APCK1=(0x02|val))									/**< Set SNAPCLKO1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_APCK2()				(IO_CHIPTOP.CLKSTOP4.bit.APCK2)												/**< Get SNAPCLKO2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_APCK2(val)			(IO_CHIPTOP.CLKSTOP4.bit.APCK2=(0x02|val))									/**< Set SNAPCLKO2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP4_APCK3()				(IO_CHIPTOP.CLKSTOP4.bit.APCK3)												/**< Get SNAPCLKO3 Clock Stop */
#define	DdToptwo_SET_CLKSTOP4_APCK3(val)			(IO_CHIPTOP.CLKSTOP4.bit.APCK3=(0x02|val))									/**< Set SNAPCLKO3 Clock Stop */

// CLKSTOP5
#define	DdToptwo_GET_CLKSTOP5_MICAX0()			(IO_CHIPTOP.CLKSTOP5.bit.MICAX0)											/**< Get MXIC AXI Bus Clock0 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAX0(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAX0=(0x02|val))									/**< Set MXIC AXI Bus Clock0 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAX1()			(IO_CHIPTOP.CLKSTOP5.bit.MICAX1)											/**< Get MXIC AXI Bus Clock1 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAX1(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAX1=(0x02|val))									/**< Set MXIC AXI Bus Clock1 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAX2()			(IO_CHIPTOP.CLKSTOP5.bit.MICAX2)											/**< Get MXIC AXI Bus Clock2 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAX2(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAX2=(0x02|val))									/**< Set MXIC AXI Bus Clock2 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAX3()			(IO_CHIPTOP.CLKSTOP5.bit.MICAX3)											/**< Get MXIC AXI Bus Clock3 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAX3(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAX3=(0x02|val))									/**< Set MXIC AXI Bus Clock3 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAX4()			(IO_CHIPTOP.CLKSTOP5.bit.MICAX4)											/**< Get MXIC AXI Bus Clock4 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAX4(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAX4=(0x02|val))									/**< Set MXIC AXI Bus Clock4 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAX5()			(IO_CHIPTOP.CLKSTOP5.bit.MICAX5)											/**< Get MXIC AXI Bus Clock5 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAX5(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAX5=(0x02|val))									/**< Set MXIC AXI Bus Clock5 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAX6()			(IO_CHIPTOP.CLKSTOP5.bit.MICAX6)											/**< Get MXIC AXI Bus Clock6 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAX6(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAX6=(0x02|val))									/**< Set MXIC AXI Bus Clock6 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAP0()			(IO_CHIPTOP.CLKSTOP5.bit.MICAP0)											/**< Get MXIC APB Bus Clock0 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAP0(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAP0=(0x02|val))									/**< Set MXIC APB Bus Clock0 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAP1()			(IO_CHIPTOP.CLKSTOP5.bit.MICAP1)											/**< Get MXIC APB Bus Clock1 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAP1(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAP1=(0x02|val))									/**< Set MXIC APB Bus Clock1 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAP2()			(IO_CHIPTOP.CLKSTOP5.bit.MICAP2)											/**< Get MXIC APB Bus Clock2 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAP2(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAP2=(0x02|val))									/**< Set MXIC APB Bus Clock2 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAP3()			(IO_CHIPTOP.CLKSTOP5.bit.MICAP3)											/**< Get MXIC APB Bus Clock3 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAP3(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAP3=(0x02|val))									/**< Set MXIC APB Bus Clock3 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAP4()			(IO_CHIPTOP.CLKSTOP5.bit.MICAP4)											/**< Get MXIC APB Bus Clock4 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAP4(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAP4=(0x02|val))									/**< Set MXIC APB Bus Clock4 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAP5()			(IO_CHIPTOP.CLKSTOP5.bit.MICAP5)											/**< Get MXIC APB Bus Clock5 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAP5(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAP5=(0x02|val))									/**< Set MXIC APB Bus Clock5 Stop */
#define	DdToptwo_GET_CLKSTOP5_MICAP6()			(IO_CHIPTOP.CLKSTOP5.bit.MICAP6)											/**< Get MXIC APB Bus Clock6 Stop */
#define	DdToptwo_SET_CLKSTOP5_MICAP6(val)			(IO_CHIPTOP.CLKSTOP5.bit.MICAP6=(0x02|val))									/**< Set MXIC APB Bus Clock6 Stop */

// CLKSTOP6
#define	DdToptwo_GET_CLKSTOP6_MICAH1()			(IO_CHIPTOP.CLKSTOP6.bit.MICAH1)											/**< Get MXIC AHB Bus Clock1 Stop */
#define	DdToptwo_SET_CLKSTOP6_MICAH1(val)			(IO_CHIPTOP.CLKSTOP6.bit.MICAH1=(0x02|val))									/**< Set MXIC AHB Bus Clock1 Stop */
#define	DdToptwo_GET_CLKSTOP6_MICAH2()			(IO_CHIPTOP.CLKSTOP6.bit.MICAH2)											/**< Get MXIC AHB Bus Clock2 Stop */
#define	DdToptwo_SET_CLKSTOP6_MICAH2(val)			(IO_CHIPTOP.CLKSTOP6.bit.MICAH2=(0x02|val))									/**< Set MXIC AHB Bus Clock2 Stop */
#define	DdToptwo_GET_CLKSTOP6_MICAH3()			(IO_CHIPTOP.CLKSTOP6.bit.MICAH3)											/**< Get MXIC AHB Bus Clock3 Stop */
#define	DdToptwo_SET_CLKSTOP6_MICAH3(val)			(IO_CHIPTOP.CLKSTOP6.bit.MICAH3=(0x02|val))									/**< Set MXIC AHB Bus Clock2 Stop */
#define	DdToptwo_GET_CLKSTOP6_IMGAX()				(IO_CHIPTOP.CLKSTOP6.bit.IMGAX)												/**< Get Image macro AXI Bus Clock0 Stop */
#define	DdToptwo_SET_CLKSTOP6_IMGAX(val)			(IO_CHIPTOP.CLKSTOP6.bit.IMGAX=(0x02|val))									/**< Set Image macro AXI Bus Clock0 Stop */
#define	DdToptwo_GET_CLKSTOP6_IMGAH0()			(IO_CHIPTOP.CLKSTOP6.bit.IMGAH0)											/**< Get Image macro AHB Bus Clock0 Stop */
#define	DdToptwo_SET_CLKSTOP6_IMGAH0(val)			(IO_CHIPTOP.CLKSTOP6.bit.IMGAH0=(0x02|val))									/**< Set Image macro AHB Bus Clock0 Stop */
#define	DdToptwo_GET_CLKSTOP6_IMGAH1()			(IO_CHIPTOP.CLKSTOP6.bit.IMGAH1)											/**< Get Image macro AHB Bus Clock1 Stop */
#define	DdToptwo_SET_CLKSTOP6_IMGAH1(val)			(IO_CHIPTOP.CLKSTOP6.bit.IMGAH1=(0x02|val))									/**< Set Image macro AHB Bus Clock1 Stop */
#define	DdToptwo_GET_CLKSTOP6_IMGAH3()			(IO_CHIPTOP.CLKSTOP6.bit.IMGAH3)											/**< Get Image macro AHB Bus Clock3 Stop */
#define	DdToptwo_SET_CLKSTOP6_IMGAH3(val)			(IO_CHIPTOP.CLKSTOP6.bit.IMGAH3=(0x02|val))									/**< Set Image macro AHB Bus Clock3 Stop */
#define	DdToptwo_GET_CLKSTOP6_IMGAP3()			(IO_CHIPTOP.CLKSTOP6.bit.IMGAP3)											/**< Get Image macro APB Bus Clock3 Stop */
#define	DdToptwo_SET_CLKSTOP6_IMGAP3(val)			(IO_CHIPTOP.CLKSTOP6.bit.IMGAP3=(0x02|val))									/**< Set Image macro APB Bus Clock3 Stop */
#define	DdToptwo_GET_CLKSTOP6_REGAP()				(IO_CHIPTOP.CLKSTOP6.bit.REGAP)												/**< Get Chip top Register APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP6_REGAP(val)			(IO_CHIPTOP.CLKSTOP6.bit.REGAP=(0x02|val))									/**< Set Chip top Register APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP6_XCHAX()				(IO_CHIPTOP.CLKSTOP6.bit.XCHAX)												/**< Get XCH AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP6_XCHAX(val)			(IO_CHIPTOP.CLKSTOP6.bit.XCHAX=(0x02|val))									/**< Set XCH AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP6_XCHAP()				(IO_CHIPTOP.CLKSTOP6.bit.XCHAP)												/**< Get XCH APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP6_XCHAP(val)			(IO_CHIPTOP.CLKSTOP6.bit.XCHAP=(0x02|val))									/**< Set XCH APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP6_ELACK()				(IO_CHIPTOP.CLKSTOP6.bit.ELACK)												/**< Get ELA Clock Stop */
#define	DdToptwo_SET_CLKSTOP6_ELACK(val)			(IO_CHIPTOP.CLKSTOP6.bit.ELACK=(0x02|val))									/**< Set ELA Clock Stop */
#define	DdToptwo_GET_CLKSTOP6_ELAAX()				(IO_CHIPTOP.CLKSTOP6.bit.ELAAX)												/**< Get ELA AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP6_ELAAX(val)			(IO_CHIPTOP.CLKSTOP6.bit.ELAAX=(0x02|val))									/**< Set ELA AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP6_ELAAP()				(IO_CHIPTOP.CLKSTOP6.bit.ELAAP)												/**< Get ELA APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP6_ELAAP(val)			(IO_CHIPTOP.CLKSTOP6.bit.ELAAP=(0x02|val))									/**< Set ELA APB Bus Clock Stop */

// CLKSTOP7
#define	DdToptwo_GET_CLKSTOP7_IPUFDCK()			(IO_CHIPTOP.CLKSTOP7.bit.IPUFDCK)											/**< Get IPUFD AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_IPUFDCK(val)		(IO_CHIPTOP.CLKSTOP7.bit.IPUFDCK=(0x02|val))								/**< Set IPUFD AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_IPUVISCK()			(IO_CHIPTOP.CLKSTOP7.bit.IPUVISCK)											/**< Get IPUVIS AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_IPUVISCK(val)		(IO_CHIPTOP.CLKSTOP7.bit.IPUVISCK=(0x02|val))								/**< Set IPUVIS AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_IPUAX()				(IO_CHIPTOP.CLKSTOP7.bit.IPUAX)												/**< Get IPU AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_IPUAX(val)			(IO_CHIPTOP.CLKSTOP7.bit.IPUAX=(0x02|val))									/**< Set IPU AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_IPUAH()				(IO_CHIPTOP.CLKSTOP7.bit.IPUAH)												/**< Get IPU AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_IPUAH(val)			(IO_CHIPTOP.CLKSTOP7.bit.IPUAH=(0x02|val))									/**< Set IPU AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_RAWCK()				(IO_CHIPTOP.CLKSTOP7.bit.RAWCK)												/**< Get RAW Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_RAWCK(val)			(IO_CHIPTOP.CLKSTOP7.bit.RAWCK=(0x02|val))									/**< Set RAW Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_RAWAX()				(IO_CHIPTOP.CLKSTOP7.bit.RAWAX)												/**< Get RAW AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_RAWAX(val)			(IO_CHIPTOP.CLKSTOP7.bit.RAWAX=(0x02|val))									/**< Set RAW AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_RAWAP()				(IO_CHIPTOP.CLKSTOP7.bit.RAWAP)												/**< Get RAW APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_RAWAP(val)			(IO_CHIPTOP.CLKSTOP7.bit.RAWAP=(0x02|val))									/**< Set RAW APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_SHDRCK()			(IO_CHIPTOP.CLKSTOP7.bit.SHDRCK)											/**< Get 3DNR Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_SHDRCK(val)			(IO_CHIPTOP.CLKSTOP7.bit.SHDRCK=(0x02|val))									/**< Set 3DNR Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_SHDRAX()			(IO_CHIPTOP.CLKSTOP7.bit.SHDRAX)											/**< Get 3DNR AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_SHDRAX(val)			(IO_CHIPTOP.CLKSTOP7.bit.SHDRAX=(0x02|val))									/**< Set 3DNR AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_SHDRAH()			(IO_CHIPTOP.CLKSTOP7.bit.SHDRAH)											/**< Get 3DNR AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_SHDRAH(val)			(IO_CHIPTOP.CLKSTOP7.bit.SHDRAH=(0x02|val))									/**< Set 3DNR AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_SHDRAP()			(IO_CHIPTOP.CLKSTOP7.bit.SHDRAP)											/**< Get 3DNR APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_SHDRAP(val)			(IO_CHIPTOP.CLKSTOP7.bit.SHDRAP=(0x02|val))									/**< Set 3DNR APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_M0CK()				(IO_CHIPTOP.CLKSTOP7.bit.M0CK)												/**< Get M0 Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_M0CK(val)			(IO_CHIPTOP.CLKSTOP7.bit.M0CK=(0x02|val))									/**< Set M0 Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_MECK()				(IO_CHIPTOP.CLKSTOP7.bit.MECK)												/**< Get ME Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_MECK(val)			(IO_CHIPTOP.CLKSTOP7.bit.MECK=(0x02|val))									/**< Set ME Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_MEAX()				(IO_CHIPTOP.CLKSTOP7.bit.MEAX)												/**< Get ME AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_MEAX(val)			(IO_CHIPTOP.CLKSTOP7.bit.MEAX=(0x02|val))									/**< Set ME AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP7_MEAP()				(IO_CHIPTOP.CLKSTOP7.bit.MEAP)												/**< Get ME APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP7_MEAP(val)			(IO_CHIPTOP.CLKSTOP7.bit.MEAP=(0x02|val))									/**< Set ME APB Bus Clock Stop */

// CLKSTOP8
#define	DdToptwo_GET_CLKSTOP8_RIBCK()				(IO_CHIPTOP.CLKSTOP8.bit.RIBCK)												/**< Get RIBERY(H.264 Codec) Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_RIBCK(val)			(IO_CHIPTOP.CLKSTOP8.bit.RIBCK=(0x02|val))									/**< Set RIBERY(H.264 Codec) Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_RIBAH()				(IO_CHIPTOP.CLKSTOP8.bit.RIBAH)												/**< Get RIBERY(H.264 Codec) AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_RIBAH(val)			(IO_CHIPTOP.CLKSTOP8.bit.RIBAH=(0x02|val))									/**< Set RIBERY(H.264 Codec) AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_HEVDFCK()			(IO_CHIPTOP.CLKSTOP8.bit.HEVDFCK)											/**< Get HEVC VDF AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_HEVDFCK(val)		(IO_CHIPTOP.CLKSTOP8.bit.HEVDFCK=(0x02|val))								/**< Set HEVC VDF AHB Bus Clock Stop */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define	DdToptwo_GET_CLKSTOP8_HEPXFCK()			(IO_CHIPTOP.CLKSTOP8.bit.HEPXFCK)											/**< Get HEVC PXF AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_HEPXFCK(val)		(IO_CHIPTOP.CLKSTOP8.bit.HEPXFCK=(0x02|val))								/**< Set HEVC PXF AHB Bus Clock Stop */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdToptwo_GET_CLKSTOP8_HEVENCCK()			(IO_CHIPTOP.CLKSTOP8.bit.HEVENCCK)											/**< Get HEVC ENC AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_HEVENCCK(val)		(IO_CHIPTOP.CLKSTOP8.bit.HEVENCCK=(0x02|val))								/**< Set HEVC ENC AHB Bus Clock Stop */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define	DdToptwo_GET_CLKSTOP8_HEIPPCK()			(IO_CHIPTOP.CLKSTOP8.bit.HEIPPCK)											/**< Get HEVC IPP AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_HEIPPCK(val)		(IO_CHIPTOP.CLKSTOP8.bit.HEIPPCK=(0x02|val))								/**< Set HEVC IPP AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC0HEVCMX2()		(IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX2)										/**< Get UMC0 HEVC MXI Bus 200MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC0HEVCMX2(val)	(IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX2=(0x02|val))							/**< Set UMC0 HEVC MXI Bus 200MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC0HEVCMX4()		(IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX4)										/**< Get UMC0 HEVC MXI Bus 400MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC0HEVCMX4(val)	(IO_CHIPTOP.CLKSTOP8.bit.UMC0HEVCMX4=(0x02|val))							/**< Set UMC0 HEVC MXI Bus 400MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC0RBRMX4()		(IO_CHIPTOP.CLKSTOP8.bit.UMC0RBRMX4)										/**< Get UMC0 RIBERY MXI Bus 400MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC0RBRMX4(val)		(IO_CHIPTOP.CLKSTOP8.bit.UMC0RBRMX4=(0x02|val))								/**< Set UMC0 RIBERY MXI Bus 400MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC1HEVCMX2()		(IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX2)										/**< Get UMC1 HEVC MXI Bus 200MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC1HEVCMX2(val)	(IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX2=(0x02|val))							/**< Set UMC1 HEVC MXI Bus 200MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC1HEVCMX4()		(IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX4)										/**< Get UMC1 HEVC MXI Bus 400MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC1HEVCMX4(val)	(IO_CHIPTOP.CLKSTOP8.bit.UMC1HEVCMX4=(0x02|val))							/**< Set UMC1 HEVC MXI Bus 400MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC1RBRMX4()		(IO_CHIPTOP.CLKSTOP8.bit.UMC1RBRMX4)										/**< Get UMC1 RIBERY MXI Bus 400MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC1RBRMX4(val)		(IO_CHIPTOP.CLKSTOP8.bit.UMC1RBRMX4=(0x02|val))								/**< Set UMC1 RIBERY MXI Bus 400MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC0CMNAX()			(IO_CHIPTOP.CLKSTOP8.bit.UMC0CMNAX)											/**< Get UMC0 CMN AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC0CMNAX(val)		(IO_CHIPTOP.CLKSTOP8.bit.UMC0CMNAX=(0x02|val))								/**< Set UMC0 CMN AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC0MX1AX()			(IO_CHIPTOP.CLKSTOP8.bit.UMC0MX1AX)											/**< Get UMC0 MXIC1 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC0MX1AX(val)		(IO_CHIPTOP.CLKSTOP8.bit.UMC0MX1AX=(0x02|val))								/**< Set UMC0 MXIC1 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC0MX2AX()			(IO_CHIPTOP.CLKSTOP8.bit.UMC0MX2AX)											/**< Get UMC0 MXIC2 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC0MX2AX(val)		(IO_CHIPTOP.CLKSTOP8.bit.UMC0MX2AX=(0x02|val))								/**< Set UMC0 MXIC2 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC0MX3AX()			(IO_CHIPTOP.CLKSTOP8.bit.UMC0MX3AX)											/**< Get UMC0 MXIC3 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC0MX3AX(val)		(IO_CHIPTOP.CLKSTOP8.bit.UMC0MX3AX=(0x02|val))								/**< Set UMC0 MXIC3 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP8_UMC0MX4AX()			(IO_CHIPTOP.CLKSTOP8.bit.UMC0MX4AX)											/**< Get UMC0 MXIC4 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP8_UMC0MX4AX(val)		(IO_CHIPTOP.CLKSTOP8.bit.UMC0MX4AX=(0x02|val))								/**< Set UMC0 MXIC4 MXI Bus Clock Stop */

// CLKSTOP9
#define	DdToptwo_GET_CLKSTOP9_UMC0MX5AX()			(IO_CHIPTOP.CLKSTOP9.bit.UMC0MX5AX)											/**< Get UMC0 MXIC5 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC0MX5AX(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC0MX5AX=(0x02|val))								/**< Set UMC0 MXIC5 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1CMNAX()			(IO_CHIPTOP.CLKSTOP9.bit.UMC1CMNAX)											/**< Get UMC1 CMN AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1CMNAX(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC1CMNAX=(0x02|val))								/**< Set UMC1 CMN AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1MX1AX()			(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX1AX)											/**< Get UMC1 MXIC1 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1MX1AX(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX1AX=(0x02|val))								/**< Set UMC1 MXIC1 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1MX2AX()			(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX2AX)											/**< Get UMC1 MXIC2 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1MX2AX(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX2AX=(0x02|val))								/**< Set UMC1 MXIC2 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1MX3AX()			(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX3AX)											/**< Get UMC1 MXIC3 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1MX3AX(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX3AX=(0x02|val))								/**< Set UMC1 MXIC3 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1MX4AX()			(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX4AX)											/**< Get UMC1 MXIC4 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1MX4AX(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX4AX=(0x02|val))								/**< Set UMC1 MXIC4 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1MX5AX()			(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX5AX)											/**< Get UMC1 MXIC5 MXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1MX5AX(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX5AX=(0x02|val))								/**< Set UMC1 MXIC5 MXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC0MX0AX3()		(IO_CHIPTOP.CLKSTOP9.bit.UMC0MX0AX3)										/**< Get UMC0 MXIC0 MXI Bus 300MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC0MX0AX3(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC0MX0AX3=(0x02|val))								/**< Set UMC0 MXIC0 MXI Bus 300MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC0MX6AX4()		(IO_CHIPTOP.CLKSTOP9.bit.UMC0MX6AX4)										/**< Get UMC0 MXIC6 MXI Bus 400MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC0MX6AX4(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC0MX6AX4=(0x02|val))								/**< Set UMC0 MXIC6 MXI Bus 400MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC0HEVCAX4()		(IO_CHIPTOP.CLKSTOP9.bit.UMC0HEVCAX4)										/**< Get UMC0 HEVC AXI Bus 400MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC0HEVCAX4(val)	(IO_CHIPTOP.CLKSTOP9.bit.UMC0HEVCAX4=(0x02|val))							/**< Set UMC0 HEVC AXI Bus 400MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1MX0AX3()		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX0AX3)										/**< Get UMC1 MXIC0 MXI Bus 300MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1MX0AX3(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX0AX3=(0x02|val))								/**< Set UMC1 MXIC0 MXI Bus 300MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1MX6AX4()		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX6AX4)										/**< Get UMC1 MXIC6 MXI Bus 400MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1MX6AX4(val)		(IO_CHIPTOP.CLKSTOP9.bit.UMC1MX6AX4=(0x02|val))								/**< Set UMC1 MXIC6 MXI Bus 400MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1HEVCAX4()		(IO_CHIPTOP.CLKSTOP9.bit.UMC1HEVCAX4)										/**< Get UMC1 HEVC AXI Bus 400MHz Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1HEVCAX4(val)	(IO_CHIPTOP.CLKSTOP9.bit.UMC1HEVCAX4=(0x02|val))							/**< Set UMC1 HEVC AXI Bus 400MHz Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC0AP()			(IO_CHIPTOP.CLKSTOP9.bit.UMC0AP)											/**< Get UMC0 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC0AP(val)			(IO_CHIPTOP.CLKSTOP9.bit.UMC0AP=(0x02|val))									/**< Set UMC0 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP9_UMC1AP()			(IO_CHIPTOP.CLKSTOP9.bit.UMC1AP)											/**< Get UMC1 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP9_UMC1AP(val)			(IO_CHIPTOP.CLKSTOP9.bit.UMC1AP=(0x02|val))									/**< Set UMC1 APB Bus Clock Stop */

// CLKSTOP10
#define	DdToptwo_GET_CLKSTOP10_SRO1CK()			(IO_CHIPTOP.CLKSTOP10.bit.SRO1CK)											/**< Get SRO pipe1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_SRO1CK(val)		(IO_CHIPTOP.CLKSTOP10.bit.SRO1CK=(0x02|val))								/**< Set SRO pipe1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_SRO1CK_2()			(IO_CHIPTOP.CLKSTOP10.bit.SRO1CK_2)											/**< Get SRO pipe1 Clock2 Stop */
#define	DdToptwo_SET_CLKSTOP10_SRO1CK_2(val)		(IO_CHIPTOP.CLKSTOP10.bit.SRO1CK_2=(0x02|val))								/**< Set SRO pipe1 Clock2 Stop */
#define	DdToptwo_GET_CLKSTOP10_SRO1AX()			(IO_CHIPTOP.CLKSTOP10.bit.SRO1AX)											/**< Get SRO pipe1 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_SRO1AX(val)		(IO_CHIPTOP.CLKSTOP10.bit.SRO1AX=(0x02|val))								/**< Set SRO pipe1 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_SRO1AH()			(IO_CHIPTOP.CLKSTOP10.bit.SRO1AH)											/**< Get SRO pipe1 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_SRO1AH(val)		(IO_CHIPTOP.CLKSTOP10.bit.SRO1AH=(0x02|val))								/**< Set SRO pipe1 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_SRO1AP()			(IO_CHIPTOP.CLKSTOP10.bit.SRO1AP)											/**< Get SRO pipe1 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_SRO1AP(val)		(IO_CHIPTOP.CLKSTOP10.bit.SRO1AP=(0x02|val))								/**< Set SRO pipe1 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_B2B1CK()			(IO_CHIPTOP.CLKSTOP10.bit.B2B1CK)											/**< Get B2B pipe1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_B2B1CK(val)		(IO_CHIPTOP.CLKSTOP10.bit.B2B1CK=(0x02|val))								/**< Set B2B pipe1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_B2B1AX()			(IO_CHIPTOP.CLKSTOP10.bit.B2B1AX)											/**< Get B2B pipe1 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_B2B1AX(val)		(IO_CHIPTOP.CLKSTOP10.bit.B2B1AX=(0x02|val))								/**< Set B2B pipe1 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_B2B1AH()			(IO_CHIPTOP.CLKSTOP10.bit.B2B1AH)											/**< Get B2B pipe1 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_B2B1AH(val)		(IO_CHIPTOP.CLKSTOP10.bit.B2B1AH=(0x02|val))								/**< Set B2B pipe1 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_B2B1AP()			(IO_CHIPTOP.CLKSTOP10.bit.B2B1AP)											/**< Get B2B pipe1 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_B2B1AP(val)		(IO_CHIPTOP.CLKSTOP10.bit.B2B1AP=(0x02|val))								/**< Set B2B pipe1 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_LTMRBK1CK()		(IO_CHIPTOP.CLKSTOP10.bit.LTMRBK1CK)										/**< Get LTMRBK1 pipe1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_LTMRBK1CK(val)		(IO_CHIPTOP.CLKSTOP10.bit.LTMRBK1CK=(0x02|val))								/**< Set LTMRBK1 pipe1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_B2R1CK()			(IO_CHIPTOP.CLKSTOP10.bit.B2R1CK)											/**< Get B2R pipe1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_B2R1CK(val)		(IO_CHIPTOP.CLKSTOP10.bit.B2R1CK=(0x02|val))								/**< Set B2R pipe1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_B2R1AX()			(IO_CHIPTOP.CLKSTOP10.bit.B2R1AX)											/**< Get B2R pipe1 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_B2R1AX(val)		(IO_CHIPTOP.CLKSTOP10.bit.B2R1AX=(0x02|val))								/**< Set B2R pipe1 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_B2R1AH()			(IO_CHIPTOP.CLKSTOP10.bit.B2R1AH)											/**< Get B2R pipe1 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_B2R1AH(val)		(IO_CHIPTOP.CLKSTOP10.bit.B2R1AH=(0x02|val))								/**< Set B2R pipe1 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP10_B2R1AP()			(IO_CHIPTOP.CLKSTOP10.bit.B2R1AP)											/**< Get B2R pipe1 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP10_B2R1AP(val)		(IO_CHIPTOP.CLKSTOP10.bit.B2R1AP=(0x02|val))								/**< Set B2R pipe1 APB Bus Clock Stop */

// CLKSTOP11
#define	DdToptwo_GET_CLKSTOP11_LTM1CK()			(IO_CHIPTOP.CLKSTOP11.bit.LTM1CK)											/**< Get LTM pipe1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_LTM1CK(val)		(IO_CHIPTOP.CLKSTOP11.bit.LTM1CK=(0x02|val))								/**< Set LTM pipe1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_LTM1AX()			(IO_CHIPTOP.CLKSTOP11.bit.LTM1AX)											/**< Get LTM pipe1 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_LTM1AX(val)		(IO_CHIPTOP.CLKSTOP11.bit.LTM1AX=(0x02|val))								/**< Set LTM pipe1 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_LTM1AH()			(IO_CHIPTOP.CLKSTOP11.bit.LTM1AH)											/**< Get LTM pipe1 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_LTM1AH(val)		(IO_CHIPTOP.CLKSTOP11.bit.LTM1AH=(0x02|val))								/**< Set LTM pipe1 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_LTM1AP()			(IO_CHIPTOP.CLKSTOP11.bit.LTM1AP)											/**< Get LTM pipe1 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_LTM1AP(val)		(IO_CHIPTOP.CLKSTOP11.bit.LTM1AP=(0x02|val))								/**< Set LTM pipe1 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_R2Y1CK()			(IO_CHIPTOP.CLKSTOP11.bit.R2Y1CK)											/**< Get R2Y pipe1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_R2Y1CK(val)		(IO_CHIPTOP.CLKSTOP11.bit.R2Y1CK=(0x02|val))								/**< Set R2Y pipe1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_R2Y1AX()			(IO_CHIPTOP.CLKSTOP11.bit.R2Y1AX)											/**< Get R2Y pipe1 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_R2Y1AX(val)		(IO_CHIPTOP.CLKSTOP11.bit.R2Y1AX=(0x02|val))								/**< Set R2Y pipe1 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_R2Y1AH()			(IO_CHIPTOP.CLKSTOP11.bit.R2Y1AH)											/**< Get R2Y pipe1 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_R2Y1AH(val)		(IO_CHIPTOP.CLKSTOP11.bit.R2Y1AH=(0x02|val))								/**< Set R2Y pipe1 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_R2Y1AP()			(IO_CHIPTOP.CLKSTOP11.bit.R2Y1AP)											/**< Get R2Y pipe1 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_R2Y1AP(val)		(IO_CHIPTOP.CLKSTOP11.bit.R2Y1AP=(0x02|val))								/**< Set R2Y pipe1 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_CNR1CK()			(IO_CHIPTOP.CLKSTOP11.bit.CNR1CK)											/**< Get CNR pipe1 Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_CNR1CK(val)		(IO_CHIPTOP.CLKSTOP11.bit.CNR1CK=(0x02|val))								/**< Set CNR pipe1 Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_CNR1AX()			(IO_CHIPTOP.CLKSTOP11.bit.CNR1AX)											/**< Get CNR pipe1 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_CNR1AX(val)		(IO_CHIPTOP.CLKSTOP11.bit.CNR1AX=(0x02|val))								/**< Set CNR pipe1 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_CNR1AP()			(IO_CHIPTOP.CLKSTOP11.bit.CNR1AP)											/**< Get CNR pipe1 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_CNR1AP(val)		(IO_CHIPTOP.CLKSTOP11.bit.CNR1AP=(0x02|val))								/**< Set CNR pipe1 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_APAH()				(IO_CHIPTOP.CLKSTOP11.bit.APAH)												/**< Get CPU HCLKAP AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_APAH(val)			(IO_CHIPTOP.CLKSTOP11.bit.APAH=(0x02|val))									/**< Set CPU HCLKAP AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_DBGAP()			(IO_CHIPTOP.CLKSTOP11.bit.DBGAP)											/**< Get CPU PCLKDBG AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_DBGAP(val)			(IO_CHIPTOP.CLKSTOP11.bit.DBGAP=(0x02|val))									/**< Set CPU PCLKDBG AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP11_NFBCHCK()			(IO_CHIPTOP.CLKSTOP11.bit.NFBCHCK)											/**< Get CPU NFBCHCK AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP11_NFBCHCK(val)		(IO_CHIPTOP.CLKSTOP11.bit.NFBCHCK=(0x02|val))								/**< Set CPU NFBCHCK AHB Bus Clock Stop */

// CLKSTOP12
#define	DdToptwo_GET_CLKSTOP12_SRO2CK()			(IO_CHIPTOP.CLKSTOP12.bit.SRO2CK)											/**< Get SRO pipe2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_SRO2CK(val)		(IO_CHIPTOP.CLKSTOP12.bit.SRO2CK=(0x02|val))								/**< Set SRO pipe2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_SRO2CK_2()			(IO_CHIPTOP.CLKSTOP12.bit.SRO2CK_2)											/**< Get SRO pipe2 Clock2 Stop */
#define	DdToptwo_SET_CLKSTOP12_SRO2CK_2(val)		(IO_CHIPTOP.CLKSTOP12.bit.SRO2CK_2=(0x02|val))								/**< Set SRO pipe2 Clock2 Stop */
#define	DdToptwo_GET_CLKSTOP12_SRO2AX()			(IO_CHIPTOP.CLKSTOP12.bit.SRO2AX)											/**< Get SRO pipe2 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_SRO2AX(val)		(IO_CHIPTOP.CLKSTOP12.bit.SRO2AX=(0x02|val))								/**< Set SRO pipe2 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_SRO2AH()			(IO_CHIPTOP.CLKSTOP12.bit.SRO2AH)											/**< Get SRO pipe2 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_SRO2AH(val)		(IO_CHIPTOP.CLKSTOP12.bit.SRO2AH=(0x02|val))								/**< Set SRO pipe2 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_SRO2AP()			(IO_CHIPTOP.CLKSTOP12.bit.SRO2AP)											/**< Get SRO pipe2 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_SRO2AP(val)		(IO_CHIPTOP.CLKSTOP12.bit.SRO2AP=(0x02|val))								/**< Set SRO pipe2 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_B2B2CK()			(IO_CHIPTOP.CLKSTOP12.bit.B2B2CK)											/**< Get B2B pipe2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_B2B2CK(val)		(IO_CHIPTOP.CLKSTOP12.bit.B2B2CK=(0x02|val))								/**< Set B2B pipe2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_B2B2AX()			(IO_CHIPTOP.CLKSTOP12.bit.B2B2AX)											/**< Get B2B pipe2 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_B2B2AX(val)		(IO_CHIPTOP.CLKSTOP12.bit.B2B2AX=(0x02|val))								/**< Set B2B pipe2 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_B2B2AH()			(IO_CHIPTOP.CLKSTOP12.bit.B2B2AH)											/**< Get B2B pipe2 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_B2B2AH(val)		(IO_CHIPTOP.CLKSTOP12.bit.B2B2AH=(0x02|val))								/**< Set B2B pipe2 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_B2B2AP()			(IO_CHIPTOP.CLKSTOP12.bit.B2B2AP)											/**< Get B2B pipe2 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_B2B2AP(val)		(IO_CHIPTOP.CLKSTOP12.bit.B2B2AP=(0x02|val))								/**< Set B2B pipe2 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_LTMRBK2CK()		(IO_CHIPTOP.CLKSTOP12.bit.LTMRBK2CK)										/**< Get LTMRBK1 pipe2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_LTMRBK2CK(val)		(IO_CHIPTOP.CLKSTOP12.bit.LTMRBK2CK=(0x02|val))								/**< Set LTMRBK1 pipe2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_B2R2CK()			(IO_CHIPTOP.CLKSTOP12.bit.B2R2CK)											/**< Get B2R pipe2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_B2R2CK(val)		(IO_CHIPTOP.CLKSTOP12.bit.B2R2CK=(0x02|val))								/**< Set B2R pipe2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_B2R2AX()			(IO_CHIPTOP.CLKSTOP12.bit.B2R2AX)											/**< Get B2R pipe2 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_B2R2AX(val)		(IO_CHIPTOP.CLKSTOP12.bit.B2R2AX=(0x02|val))								/**< Set B2R pipe2 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_B2R2AH()			(IO_CHIPTOP.CLKSTOP12.bit.B2R2AH)											/**< Get B2R pipe2 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_B2R2AH(val)		(IO_CHIPTOP.CLKSTOP12.bit.B2R2AH=(0x02|val))								/**< Set B2R pipe2 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP12_B2R2AP()			(IO_CHIPTOP.CLKSTOP12.bit.B2R2AP)											/**< Get B2R pipe2 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP12_B2R2AP(val)		(IO_CHIPTOP.CLKSTOP12.bit.B2R2AP=(0x02|val))								/**< Set B2R pipe2 APB Bus Clock Stop */

// CLKSTOP13
#define	DdToptwo_GET_CLKSTOP13_LTM2CK()			(IO_CHIPTOP.CLKSTOP13.bit.LTM2CK)											/**< Get LTM pipe2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_LTM2CK(val)		(IO_CHIPTOP.CLKSTOP13.bit.LTM2CK=(0x02|val))								/**< Set LTM pipe2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_LTM2AX()			(IO_CHIPTOP.CLKSTOP13.bit.LTM2AX)											/**< Get LTM pipe2 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_LTM2AX(val)		(IO_CHIPTOP.CLKSTOP13.bit.LTM2AX=(0x02|val))								/**< Set LTM pipe2 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_LTM2AH()			(IO_CHIPTOP.CLKSTOP13.bit.LTM2AH)											/**< Get LTM pipe2 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_LTM2AH(val)		(IO_CHIPTOP.CLKSTOP13.bit.LTM2AH=(0x02|val))								/**< Set LTM pipe2 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_LTM2AP()			(IO_CHIPTOP.CLKSTOP13.bit.LTM2AP)											/**< Get LTM pipe2 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_LTM2AP(val)		(IO_CHIPTOP.CLKSTOP13.bit.LTM2AP=(0x02|val))								/**< Set LTM pipe2 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_R2Y2CK()			(IO_CHIPTOP.CLKSTOP13.bit.R2Y2CK)											/**< Get R2Y pipe2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_R2Y2CK(val)		(IO_CHIPTOP.CLKSTOP13.bit.R2Y2CK=(0x02|val))								/**< Set R2Y pipe2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_R2Y2AX()			(IO_CHIPTOP.CLKSTOP13.bit.R2Y2AX)											/**< Get R2Y pipe2 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_R2Y2AX(val)		(IO_CHIPTOP.CLKSTOP13.bit.R2Y2AX=(0x02|val))								/**< Set R2Y pipe2 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_R2Y2AH()			(IO_CHIPTOP.CLKSTOP13.bit.R2Y2AH)											/**< Get R2Y pipe2 AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_R2Y2AH(val)		(IO_CHIPTOP.CLKSTOP13.bit.R2Y2AH=(0x02|val))								/**< Set R2Y pipe2 AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_R2Y2AP()			(IO_CHIPTOP.CLKSTOP13.bit.R2Y2AP)											/**< Get R2Y pipe2 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_R2Y2AP(val)		(IO_CHIPTOP.CLKSTOP13.bit.R2Y2AP=(0x02|val))								/**< Set R2Y pipe2 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_CNR2CK()			(IO_CHIPTOP.CLKSTOP13.bit.CNR2CK)											/**< Get CNR pipe2 Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_CNR2CK(val)		(IO_CHIPTOP.CLKSTOP13.bit.CNR2CK=(0x02|val))								/**< Set CNR pipe2 Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_CNR2AX()			(IO_CHIPTOP.CLKSTOP13.bit.CNR2AX)											/**< Get CNR pipe2 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_CNR2AX(val)		(IO_CHIPTOP.CLKSTOP13.bit.CNR2AX=(0x02|val))								/**< Set CNR pipe2 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_CNR2AP()			(IO_CHIPTOP.CLKSTOP13.bit.CNR2AP)											/**< Get CNR pipe2 APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP13_CNR2AP(val)		(IO_CHIPTOP.CLKSTOP13.bit.CNR2AP=(0x02|val))								/**< Set CNR pipe2 APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP13_UMCVDFMX4()		(IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX4)										/**< Get UMC VDF 400MHz MXI Bus Clock Stataus */
#define	DdToptwo_SET_CLKSTOP13_UMCVDFMX4(val)		(IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX4=(0x02|val))								/**< Set UMC VDF 400MHz MXI Bus Clock Stataus */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define	DdToptwo_GET_CLKSTOP13_UMCPXFMX4()		(IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX4)										/**< Get UMC PXF 400MHz MXI Bus Clock Stataus */
#define	DdToptwo_SET_CLKSTOP13_UMCPXFMX4(val)		(IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX4=(0x02|val))								/**< Set UMC PXF 400MHz MXI Bus Clock Stataus */
#define	DdToptwo_GET_CLKSTOP13_UMCVDFMX2()		(IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX2)										/**< Get UMC VDF 200MHz MXI Bus Clock Stataus */
#define	DdToptwo_SET_CLKSTOP13_UMCVDFMX2(val)		(IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX2=(0x02|val))								/**< Set UMC VDF 200MHz MXI Bus Clock Stataus */
#define	DdToptwo_GET_CLKSTOP13_UMCPXFMX2()		(IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX2)										/**< Get UMC PXF 200MHz MXI Bus Clock Stataus */
#define	DdToptwo_SET_CLKSTOP13_UMCPXFMX2(val)		(IO_CHIPTOP.CLKSTOP13.bit.UMCPXFMX2=(0x02|val))								/**< Set UMC PXF 200MHz MXI Bus Clock Stataus */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdToptwo_GET_CLKSTOP13_UMCHEVENCAX4()		(IO_CHIPTOP.CLKSTOP13.bit.UMCHEVENCAX4)										/**< Get HEVENC 400MHz AXI Bus Clock Stataus */
#define	DdToptwo_SET_CLKSTOP13_UMCHEVENCAX4(val)	(IO_CHIPTOP.CLKSTOP13.bit.UMCHEVENCAX4=(0x02|val))							/**< Set HEVENC 400MHz AXI Bus Clock Stataus */
#define	DdToptwo_GET_CLKSTOP13_UMCVDFMX2()		(IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX2)										/**< Get UMC VDF 200MHz MXI Bus Clock Stataus */
#define	DdToptwo_SET_CLKSTOP13_UMCVDFMX2(val)		(IO_CHIPTOP.CLKSTOP13.bit.UMCVDFMX2=(0x02|val))								/**< Set UMC VDF 200MHz MXI Bus Clock Stataus */
#define	DdToptwo_GET_CLKSTOP13_HEVENCAP()			(IO_CHIPTOP.CLKSTOP13.bit.HEVENCAP)											/**< Get HEVENC APB Bus Clock of Stataus */
#define	DdToptwo_SET_CLKSTOP13_HEVENCAP(val)		(IO_CHIPTOP.CLKSTOP13.bit.HEVENCAP=(0x02|val))								/**< Set HEVENC APB Bus Clock of Stataus */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define	DdToptwo_GET_CLKSTOP13_BMH1CK()			(IO_CHIPTOP.CLKSTOP13.bit.BMH1CK)											/**< Get UMC BMH1 Bus Clock Stataus */
#define	DdToptwo_SET_CLKSTOP13_BMH1CK(val)		(IO_CHIPTOP.CLKSTOP13.bit.BMH1CK=(0x02|val))								/**< Set UMC BMH1 Bus Clock Stataus */
// CLKSTOP14
#define	DdToptwo_GET_CLKSTOP14_STATAX()			(IO_CHIPTOP.CLKSTOP14.bit.STATAX)											/**< Get STAT AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_STATAX(val)		(IO_CHIPTOP.CLKSTOP14.bit.STATAX=(0x02|val))								/**< Set STAT AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_STATAH()			(IO_CHIPTOP.CLKSTOP14.bit.STATAH)											/**< Get STAT AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_STATAH(val)		(IO_CHIPTOP.CLKSTOP14.bit.STATAH=(0x02|val))								/**< Set STAT AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_STATAP()			(IO_CHIPTOP.CLKSTOP14.bit.STATAP)											/**< Get STAT APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_STATAP(val)		(IO_CHIPTOP.CLKSTOP14.bit.STATAP=(0x02|val))								/**< Set STAT APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_PERIAH()			(IO_CHIPTOP.CLKSTOP14.bit.PERIAH)											/**< Get Peripheral AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_PERIAH(val)		(IO_CHIPTOP.CLKSTOP14.bit.PERIAH=(0x02|val))								/**< Set Peripheral AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_PERIAP()			(IO_CHIPTOP.CLKSTOP14.bit.PERIAP)											/**< Get Peripheral APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_PERIAP(val)		(IO_CHIPTOP.CLKSTOP14.bit.PERIAP=(0x02|val))								/**< Set Peripheral APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_SENMSKCK()			(IO_CHIPTOP.CLKSTOP14.bit.SENMSKCK)											/**< Get mask clock of SENSOR Stop */
#define	DdToptwo_SET_CLKSTOP14_SENMSKCK(val)		(IO_CHIPTOP.CLKSTOP14.bit.SENMSKCK=(0x02|val))								/**< Set mask clock of SENSOR Stop */
#define	DdToptwo_GET_CLKSTOP14_GYROCK()			(IO_CHIPTOP.CLKSTOP14.bit.GYROCK)											/**< Get GYRO Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_GYROCK(val)		(IO_CHIPTOP.CLKSTOP14.bit.GYROCK=(0x02|val))								/**< Set GYRO Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_EXSAH()			(IO_CHIPTOP.CLKSTOP14.bit.EXSAH)											/**< Get EXS AHB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_EXSAH(val)			(IO_CHIPTOP.CLKSTOP14.bit.EXSAH=(0x02|val))									/**< Set EXS AHB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_EXSAP()			(IO_CHIPTOP.CLKSTOP14.bit.EXSAP)											/**< Get EXS APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_EXSAP(val)			(IO_CHIPTOP.CLKSTOP14.bit.EXSAP=(0x02|val))									/**< Set EXS APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_PASCK()			(IO_CHIPTOP.CLKSTOP14.bit.PASCK)											/**< Get PAS Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_PASCK(val)			(IO_CHIPTOP.CLKSTOP14.bit.PASCK=(0x02|val))									/**< Set PAS Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_BMH0CK()			(IO_CHIPTOP.CLKSTOP14.bit.BMH0CK)											/**< Get BMH0 Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_BMH0CK(val)		(IO_CHIPTOP.CLKSTOP14.bit.BMH0CK=(0x02|val))								/**< Set BMH0 Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_BMH0AX()			(IO_CHIPTOP.CLKSTOP14.bit.BMH0AX)											/**< Get BMH0 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_BMH0AX(val)		(IO_CHIPTOP.CLKSTOP14.bit.BMH0AX=(0x02|val))								/**< Set BMH0 AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_RDMAAX()			(IO_CHIPTOP.CLKSTOP14.bit.RDMAAX)											/**< Get RDMA AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_RDMAAX(val)		(IO_CHIPTOP.CLKSTOP14.bit.RDMAAX=(0x02|val))								/**< Set RDMA AXI Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_RDMAAP()			(IO_CHIPTOP.CLKSTOP14.bit.RDMAAP)											/**< Get RDMA APB Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_RDMAAP(val)		(IO_CHIPTOP.CLKSTOP14.bit.RDMAAP=(0x02|val))								/**< Set RDMA APB Bus Clock Stop */
#define	DdToptwo_GET_CLKSTOP14_BMH1AX()			(IO_CHIPTOP.CLKSTOP14.bit.BMH1AX)											/**< Get BMH1 AXI Bus Clock Stop */
#define	DdToptwo_SET_CLKSTOP14_BMH1AX(val)		(IO_CHIPTOP.CLKSTOP14.bit.BMH1AX=(0x02|val))								/**< Set BMH1 AXI Bus Clock Stop */

// CRRSM(Reset and monitor register)
#define	DdToptwo_GET_CRRSM_WDRST()				(IO_CHIPTOP.CRRSM.bit.__WDRST)												/**< Get Watchdog Reset Monitor */
#define	DdToptwo_CLEAR_CRRSM_WDRST()				{IO_CHIPTOP.CRRSM.word = ~(1 << 0);}										/**< Set Watchdog Reset Clear */
#define	DdToptwo_GET_CRRSM_SWRST()				(IO_CHIPTOP.CRRSM.bit.__SWRST)												/**< Get SRREQ Bit Reset Monitor */
#define	DdToptwo_CLEAR_CRRSM_SWRST()				{IO_CHIPTOP.CRRSM.word = ~(1 << 1);}										/**< Set SRREQ Bit Reset Clear */
#define	DdToptwo_GET_CRRSM_SRST()					(IO_CHIPTOP.CRRSM.bit.__SRST)												/**< Get TSRSTX Terminal Reset Monitor */
#define	DdToptwo_CLEAR_CRRSM_SRST()				{IO_CHIPTOP.CRRSM.word = ~(1 << 2);}										/**< Set TSRSTX Terminal Reset Clear */
#define	DdToptwo_GET_CRRSM_PORST()				(IO_CHIPTOP.CRRSM.bit.__PORST)												/**< Get RSTX Terminal Reset Monitor */
#define	DdToptwo_CLEAR_CRRSM_PORST()				{IO_CHIPTOP.CRRSM.word = ~(1 << 3);}										/**< Set RSTX Terminal Reset Clear */

// CRRRS(Register controlled request register)
#define	DdToptwo_GET_CRRRS_RIBSR()				(IO_CHIPTOP.CRRRS.bit.RIBSR)												/**< Get RIBERY(H.264 Codec) Macro Reset */
#define	DdToptwo_RESET_CRRRS_RIBSR()				{IO_CHIPTOP.CRRRS.bit.RIBSR=1;}												/**< Set RIBERY(H.264 Codec) Macro Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_RIBSR()				{IO_CHIPTOP.CRRRS.bit.RIBSR=0;}												/**< Set RIBERY(H.264 Codec) Macro Reset Clear */
#define	DdToptwo_GET_CRRRS_HEIPPASYNCSR()			(IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR)											/**< Get HEIPP async Reset */
#define	DdToptwo_RESET_CRRRS_HEIPPASYNCSR()		{IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR=1;}										/**< Set HEIPP async Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_HEIPPASYNCSR()		{IO_CHIPTOP.CRRRS.bit.HEIPPASYNCSR=0;}										/**< Set HEIPP async Reset Clear */
#define	DdToptwo_GET_CRRRS_HEIPPSYNCSR()			(IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR)											/**< Get HEIPP sync Reset */
#define	DdToptwo_RESET_CRRRS_HEIPPSYNCSR()		{IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR=1;}										/**< Set HEIPP sync Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_HEIPPSYNCSR()		{IO_CHIPTOP.CRRRS.bit.HEIPPSYNCSR=0;}										/**< Set HEIPP sync Reset Clear */
#define	DdToptwo_GET_CRRRS_HEVDFSR()				(IO_CHIPTOP.CRRRS.bit.HEVDFSR)												/**< Get HEVDF async Reset */
#define	DdToptwo_RESET_CRRRS_HEVDFSR()			{IO_CHIPTOP.CRRRS.bit.HEVDFSR=1;}											/**< Set HEVDF async Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_HEVDFSR()			{IO_CHIPTOP.CRRRS.bit.HEVDFSR=0;}											/**< Set HEVDF async Reset Clear */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define	DdToptwo_GET_CRRRS_HEPXFSR()				(IO_CHIPTOP.CRRRS.bit.HEPXFSR)												/**< Get HEPXF sync Reset */
#define	DdToptwo_RESET_CRRRS_HEPXFSR()			{IO_CHIPTOP.CRRRS.bit.HEPXFSR=1;}											/**< Set HEPXF sync Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_HEPXFSR()			{IO_CHIPTOP.CRRRS.bit.HEPXFSR=0;}											/**< Set HEPXF sync Reset Clear */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define	DdToptwo_GET_CRRRS_HEVENCSR()				(IO_CHIPTOP.CRRRS.bit.HEVENCSR)												/**< Get HEVENC sync Reset */
#define	DdToptwo_RESET_CRRRS_HEVENCSR()			{IO_CHIPTOP.CRRRS.bit.HEVENCSR=1;}											/**< Set HEVENC sync Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_HEVENCSR()			{IO_CHIPTOP.CRRRS.bit.HEVENCSR=0;}											/**< Set HEVENC sync Reset Clear */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define	DdToptwo_GET_CRRRS_DSPSR()				(IO_CHIPTOP.CRRRS.bit.DSPSR)												/**< Get DSP Reset */
#define	DdToptwo_RESET_CRRRS_DSPSR()				{IO_CHIPTOP.CRRRS.bit.DSPSR=1;}												/**< Set DSP Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_DSPSR()				{IO_CHIPTOP.CRRRS.bit.DSPSR=0;}												/**< Set DSP Reset Clear */
#define	DdToptwo_GET_CRRRS_CPU0_SR()				(IO_CHIPTOP.CRRRS.bit.CPU0_SR)												/**< Get Cortex-A7 MPCore CPU0 Reset */
#define	DdToptwo_RESET_CRRRS_CPU0_SR()			{IO_CHIPTOP.CRRRS.bit.CPU0_SR=0;}											/**< Set Cortex-A7 MPCore CPU0 Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_CPU0_SR()			{IO_CHIPTOP.CRRRS.bit.CPU0_SR=1;}											/**< Set Cortex-A7 MPCore CPU0 Reset Clear */
#define	DdToptwo_GET_CRRRS_CPU1_SR()				(IO_CHIPTOP.CRRRS.bit.CPU1_SR)												/**< Get Cortex-A7 MPCore CPU1 Reset */
#define	DdToptwo_RESET_CRRRS_CPU1_SR()			{IO_CHIPTOP.CRRRS.bit.CPU1_SR=0;}											/**< Set Cortex-A7 MPCore CPU1 Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_CPU1_SR()			{IO_CHIPTOP.CRRRS.bit.CPU1_SR=1;}											/**< Set Cortex-A7 MPCore CPU1 Reset Clear */
#define	DdToptwo_GET_CRRRS_CPU2_SR()				(IO_CHIPTOP.CRRRS.bit.CPU2_SR)												/**< Get Cortex-A7 MPCore CPU2 Reset */
#define	DdToptwo_RESET_CRRRS_CPU2_SR()			{IO_CHIPTOP.CRRRS.bit.CPU2_SR=0;}											/**< Set Cortex-A7 MPCore CPU2 Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_CPU2_SR()			{IO_CHIPTOP.CRRRS.bit.CPU2_SR=1;}											/**< Set Cortex-A7 MPCore CPU2 Reset Clear */
#define	DdToptwo_GET_CRRRS_CPU3_SR()				(IO_CHIPTOP.CRRRS.bit.CPU3_SR)												/**< Get Cortex-A7 MPCore CPU3 Reset */
#define	DdToptwo_RESET_CRRRS_CPU3_SR()			{IO_CHIPTOP.CRRRS.bit.CPU3_SR=0;}											/**< Set Cortex-A7 MPCore CPU3 Reset Generation */
#define	DdToptwo_CLEAR_CRRRS_CPU3_SR()			{IO_CHIPTOP.CRRRS.bit.CPU3_SR=1;}

// GPIO
// GPIO functional type (EPCR)
#define DdToptwo_GPIO_FUNC_GPIO		(0)		/**< GPIO mode */
#define DdToptwo_GPIO_FUNC_HWMODE	(1)		/**< Hardware mode (Resource output signal) */

// GPIO direction (DDR)
#define DdToptwo_GPIO_DIR_IN		(0)		/**< Input port */
#define DdToptwo_GPIO_DIR_OUT		(1)		/**< Output port */

// GPIO status (PDR)
#define DdToptwo_GPIO_STATUS_LOW	(0)		/**< Low status */
#define DdToptwo_GPIO_STATUS_HIGH	(1)		/**< High status */

// GPIO pull-up/down register enable (PUDER)
#define DdToptwo_GPIO_PUD_OFF		(0)		/**< Pull-up/down disable */
#define DdToptwo_GPIO_PUD_ON		(1)		/**< Pull-up/down enable */

// GPIO pull-up/down register control (PUDCR)
#define DdToptwo_GPIO_PUD_DOWN		(0)		/**< Pull-down */
#define DdToptwo_GPIO_PUD_UP		(1)		/**< Pull-Up */

#define DdToptwo_PDR_WR_EN_B16	( 1 << 16 )
#define DdToptwo_PDR_WR_EN_B17	(( 1 << 1 ) << 16 )
#define DdToptwo_PDR_WR_EN_B18	(( 1 << 2 ) << 16 )
#define DdToptwo_PDR_WR_EN_B19	(( 1 << 3 ) << 16 )
#define DdToptwo_PDR_WR_EN_B20	(( 1 << 4 ) << 16 )
#define DdToptwo_PDR_WR_EN_B21	(( 1 << 5 ) << 16 )
#define DdToptwo_PDR_WR_EN_B22	(( 1 << 6 ) << 16 )
#define DdToptwo_PDR_WR_EN_B23	(( 1 << 7 ) << 16 )
#define DdToptwo_PDR_WR_EN_B24	(( 1 << 8 ) << 16 )
#define DdToptwo_PDR_WR_EN_B25	(( 1 << 9 ) << 16 )
#define DdToptwo_PDR_WR_EN_B26	(( 1 << 10 ) << 16 )
#define DdToptwo_PDR_WR_EN_B27	(( 1 << 11 ) << 16 )
#define DdToptwo_PDR_WR_EN_B28	(( 1 << 12 ) << 16 )
#define DdToptwo_PDR_WR_EN_B29	(( 1 << 13 ) << 16 )
#define DdToptwo_PDR_WR_EN_B30	(( 1 << 14 ) << 16 )
#define DdToptwo_PDR_WR_EN_B31	(( 1 << 15 ) << 16 )

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#ifdef CO_ACT_PCLOCK
#define DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
#endif //CO_ACT_PCLOCK

#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
#define DdToptwo_START_GPIO_CLK_WITH_CS()	{Dd_ARM_Critical_Section_Start(gDD_Top_Spin_Lock)DdToptwo_SET_CLKSTOP_GPIOAP(0);(void)IO_CHIPTOP.PDR.bit.P30;Dd_ARM_Dsb_Pou();}
#define DdToptwo_STOP_GPIO_CLK_WITH_CS()	{DdToptwo_SET_CLKSTOP_GPIOAP(1);Dd_ARM_Critical_Section_End(gDD_Top_Spin_Lock);}
#else
#define DdToptwo_START_GPIO_CLK_WITH_CS()
#define DdToptwo_STOP_GPIO_CLK_WITH_CS()
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL


typedef struct 	_DdToptwo 						DdToptwo;
typedef struct 	_DdToptwoClass 			DdToptwoClass;
typedef struct 	_DdToptwoPrivate 			DdToptwoPrivate;

struct _DdToptwo{
	GObject parent;
};

struct _DdToptwoClass{
	GObjectClass parentclass;
};


GType 								dd_toptwo_get_type(void) G_GNUC_CONST;
DdToptwo* 					dd_toptwo_new(void);


/*@}*/
G_END_DECLS


#endif /* __DD_TOPTWO_H__ */
