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


#include <stdio.h>
#include "dd_arm.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if 1    // special key control
#include "pmc.h"
#include <string.h>
#endif
#include "ddtopone.h"


G_DEFINE_TYPE(DdTopone, dd_topone, G_TYPE_OBJECT);
#define DD_TOPONE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), DD_TYPE_TOPONE, DdToponePrivate));


struct _DdToponePrivate{

};


/*DECLS*/
static void 					dispose_od(GObject  *object);
static void 					finalize_od(GObject  *object);


/*IMPL*/
static void dd_topone_class_init(DdToponeClass *klass)
{
	g_type_class_add_private(klass, sizeof(DdToponePrivate));
}

static void dd_topone_init(DdTopone *self)
{
	DdToponePrivate *priv = DD_TOPONE_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	DdToponePrivate *self = DD_TOPONE_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	DdToponePrivate *self = DD_TOPONE_GET_PRIVATE(object);
}

/**
Get Frequency of eMMC clock
@retval	Hz
*/
ULONG dd_topone_get_emmcclk(DdTopone *self)
{
	// 0:187.5MHz(=1500MHz/8)
	// 1:166.666MHz(=1500MHz/9)
	// 2:150MHz(=1500MHz/10)
	// 3:100MHz(=1500MHz/15)
	static const UCHAR S_DIVID[] = {8, 9, 10, 15};

	return (DdTopone_1500_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL1_EMMCCLK()]);
}

/**
Get Frequency of NAND Flash clock
@retval	Hz
*/
ULONG dd_topone_get_nfclk(DdTopone *self)
{
	// 0:100MHz 	(=1600MHz/16)
	// 1:80MHz 		(=1600MHz/20)
	// 2:61.538MHz 	(=1600MHz/26)
	// 3:50MHz 		(=1600MHz/32)
	// 4:20MHz 		(=1600MHz/80)
	// 8:32MHz 		(=1600MHz/50)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 8, 255};
	static const UCHAR S_DIVID[] = {16, 20, 26, 32, 80, 50};
	int i;

	ULONG clock = 0;
	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL1_NFCLK() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}
	return clock;
}

/**
Get Frequency of UHS2 clock
@retval	Hz
*/
ULONG dd_topone_get_uhs2clk(DdTopone *self)
{
	// 0: 51.851MHz(=1400MHz/27)
	// 1: 46.666MHz(=1400MHz/30)
	// 2: 42.424MHz(=1400MHz/33)
	// 3: 38.888MHz(=1400MHz/36)
	// 4: 35.897MHz(=1400MHz/39)
	// 5: 33.333MHz(=1400MHz/42)
	// 6: 29.166MHz(=1400MHz/48)
	// 7: 25.925MHz(=1400MHz/54)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 5, 6, 7, 255};
	static const UCHAR S_DIVID[] = {27, 30, 33, 36, 39, 42, 48, 54};
	int i;

	ULONG clock = 0;
	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL1_UHS2CLK() == S_ID[i]) {
			clock = (DdTopone_1400_PLL_OUT / S_DIVID[i]);
			break;
		}
	}
	return clock;
}

/**
Get Frequency of UHS1 ch2 clock
@retval	Hz
*/
ULONG dd_topone_get_uhs1clk2(DdTopone *self)
{
	// 2: 400MHz(=1600MHz/4)
	// 3: 200MHz(=1600MHz/8)
	// 4: 100MHz(=1600MHz/16)
	// 8: 700MHz(=1400MHz/2)
	static const UCHAR S_ID[] = {2, 3, 4, 8, 255};
	static const UCHAR S_DIVID[] = {4, 8, 16, 2};
	static const ULONG S_PLLID[] = {DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT,
									DdTopone_1600_PLL_OUT, DdTopone_1400_PLL_OUT};
	int i;

	ULONG clock = 0;
	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL1_UHS1CLK2() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}
	return clock;
}

/**
Get Frequency of UHS1 ch1 clock
@retval	Hz
*/
ULONG dd_topone_get_uhs1clk1(DdTopone *self)
{
	// 3: 200MHz(=1600MHz/8)
	// 4: 100MHz(=1600MHz/16)
	// 8: 700MHz(=1400MHz/2)
	static const UCHAR S_ID[] = {3, 4, 8, 255};
	static const UCHAR S_DIVID[] = {8, 16, 2};
	static const ULONG S_PLLID[] = {DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT,
									DdTopone_1400_PLL_OUT};
	int i;

	ULONG clock = 0;
	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL1_UHS1CLK1() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}
	return clock;
}

/**
Get Frequency of UHS1 ch0 clock
@retval	Hz
*/
ULONG dd_topone_get_uhs1clk0(DdTopone *self)
{
	// 0: 800MHz(=1600MHz/2)
	// 1: 533.333MHz (=1600MHz/3)
	// 2: 400MHz(=1600MHz/4)
	// 3: 200MHz(=1600MHz/8)
	// 4: 100MHz(=1600MHz/16)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 255};
	static const UCHAR S_DIVID[] = {2, 3, 4, 8, 16};
	static const ULONG S_PLLID[] = {DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT,
									DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT,
									DdTopone_1600_PLL_OUT};
	int i;

	ULONG clock = 0;
	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL1_UHS1CLK0() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}
	return clock;
}

/**
Get Frequency of Cortex-A7 MPCore Peri clock
@retval	Hz
*/
ULONG dd_topone_get_rclk(DdTopone *self)
{
	// 0:54MHz(=864MHz/16)
	// 1:27MHz(=864MHz/32)
	// 2:18MHz(=864MHz/48)
	// 3:13.5MHz(=864MHz/64)
	static const UCHAR S_DIVID[] = {16, 32, 48, 64};

	return (DdTopone_864_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL1_RCLK()]);
}

/**
Get Frequency of RAW clock
@retval	Hz
*/
ULONG dd_topone_get_rawclk(DdTopone *self)
{
	// 0: 200MHz(=1600MHz/8)
	// 1: 160MHz(=1600MHz/10)
	// 2: 100MHz(=1600MHz/16)
	// 3: 50MHz(=1600MHz/32)
	static const UCHAR S_DIVID[] = {8, 10, 16, 32};

	return (DdTopone_1600_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL2_RAWCLK()]);
}

/**
Get Frequency of DISP HIF clock
@retval	Hz
*/
ULONG dd_topone_get_hifclk(DdTopone *self)
{
	// 0:594MHz(=1188MHz/2)
	// 1:297MHz(=1188MHz/4)
	// 2:148.5MHz(=1188MHz/8)
	// 3:74.25MHz(=1188MHz/16)
	// 4:27MHz(=1188MHz/44)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 255};
	static const UCHAR S_DIVID[] = {2, 4, 8, 16, 44};
	int i;

	ULONG clock = 0;
	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL2_HIFCLK() == S_ID[i]) {
			clock = (DdTopone_1188_PLL_OUT / S_DIVID[i]);
			break;
		}
	}
	return clock;
}

/**
Get Frequency of DISP MIF clock
@retval	Hz
*/
ULONG dd_topone_get_mifclk(DdTopone *self)
{
	// 0: 169.714MHz (=1188MHz/7)
	// 1: 148.5MHz (=1188MHz/8)
	// 2: 108MHz (=1188MHz/11)
	// 3: 74.25MHz (=1188MHz/16)
	// 4: 66MHz (=1188MHz/18)
	// 5: 54MHz (=1188MHz/22)
	// 6: 49.5MHz (=1188MHz/24)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {7, 8, 11, 16, 18, 22, 24};
	int i;

	ULONG clock = 0;
	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL2_MIFCLK() == S_ID[i]) {
			clock = (DdTopone_1188_PLL_OUT / S_DIVID[i]);
			break;
		}
	}
	return clock;
}

/**
Get Frequency of IPU system clock
@retval	Hz
*/
ULONG dd_topone_get_ipuclk(DdTopone *self)
{
	// 0: 400MHz (=1600MHz/4/(8/8))
	// 1: 50MHz  (=1600MHz/4/(1/8))
	// 2: 100MHz (=1600MHz/4/(2/8))
	// 3: 150MHz (=1600MHz/4/(3/8))
	// 4: 200MHz (=1600MHz/4/(4/8))
	// 5: 250MHz (=1600MHz/4/(5/8))
	// 6: 300MHz (=1600MHz/4/(6/8))
	// 7: 350MHz (=1600MHz/4/(7/8))
	static const UCHAR S_DIVID[] = {8, 1, 2, 3, 4, 5, 6, 7};

	return (DdTopone_1600_PLL_OUT / 32  * S_DIVID[DdTopone_Get_CLKSEL2_IPUCLK()]);
}

/**
Get Frequency of IPU TME clock
@retval	Hz
*/
ULONG dd_topone_get_iputmeclk(DdTopone *self)
{
	// 0:500MHz   (=1500MHz/3/(8/8))
	// 1:62.5MHz  (=1500MHz/3/(1/8))
	// 2:125MHz   (=1500MHz/3/(2/8))
	// 3:187.5MHz (=1500MHz/3/(3/8))
	// 4:250MHz   (=1500MHz/3/(4/8))
	// 5:312.5MHz (=1500MHz/3/(5/8))
	// 6:375MHz   (=1500MHz/3/(6/8))
	// 7:437.5MHz (=1500MHz/3/(7/8))
	static const UCHAR S_DIVID[] = {8, 1, 2, 3, 4, 5, 6, 7};

	return (DdTopone_1500_PLL_OUT / 24  * S_DIVID[DdTopone_Get_CLKSEL2_IPUTMECLK()]);
}
/**
Get Frequency of GPU clock
@retval	Hz
*/
ULONG dd_topone_get_gpuclk(DdTopone *self)
{
	// 0:466.666MHz(=1400MHz/3/(8/8))
	// 1:58.333MHz(=1400MHz/3/(1/8))
	// 2:116.666MHz(=1400MHz/3/(2/8))
	// 3:175MHz(=1400MHz/3/(3/8))
	// 4:233.333MHz(=1400MHz/3/(4/8))
	// 5:291.666MHz(=1400MHz/3/(5/8))
	// 6:350MHz(=1400MHz/3/(6/8))
	// 7:408.333MHz(=1400MHz/3/(7/8))
	static const UCHAR S_DIVID[] = {8, 1, 2, 3, 4, 5, 6, 7};

	return (DdTopone_1400_PLL_OUT / 24  * S_DIVID[DdTopone_Get_CLKSEL2_GPUCLK()]);
}

/**
Get Frequency of JPEG clock
@retval	Hz
*/
ULONG dd_topone_get_jpegclk(DdTopone *self)
{
	// 0:200MHz(=1600MHz/8/(8/8))
	// 1:25MHz(=1600MHz/8/(1/8))
	// 2:50MHz(=1600MHz/8/(2/8))
	// 3:75MHz(=1600MHz/8/(3/8))
	// 4:100MHz(=1600MHz/8/(4/8))
	// 5:125MHz(=1600MHz/8/(5/8))
	// 6:150MHz(=1600MHz/8/(6/8))
	// 7:175MHz(=1600MHz/8/(7/8))
	static const UCHAR S_DIVID[] = {8, 1, 2, 3, 4, 5, 6, 7};

	return (DdTopone_1600_PLL_OUT / 64  * S_DIVID[DdTopone_Get_CLKSEL2_JPGCLK()]);
}

/**
Get Frequency of ELA clock
@retval	Hz
*/
ULONG dd_topone_get_elaclk(DdTopone *self)
{
	// 0:300MHz(=1200MHz/4)
	// 1:200MHz(=1200MHz/6)
	// 2:150MHz(=1200MHz/8)
	// 3:100MHz(=1200MHz/12)
	// 4:75MHz(=1200MHz/16)
	// 5:60MHz(=1200MHz/20)
	// 6:50MHz(=1200MHz/24)
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};

	return (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL2_ELACLK()]);
}

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**
Get type of image pipe macro Select
@retval	Select value
*/
ULONG dd_topone_get_hevencsel(VOID)
{
	// 0:500MHz(=1500MHz/3)
	// 1:HEVENCCLK

	return DdTopone_Get_CLKSEL3_HEVENCSEL();
}

// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
/**
Get type of image pipe macro Select
@retval	Select value
*/
ULONG dd_topone_get_pipesel(DdTopone *self)
{
	// 10:Use PLL02 (300MHz�`50MHz)
	// 11:Use PLL01 (266.666MHz�`66.666MHz)

	return DdTopone_Get_CLKSEL3_PIPESEL();
}

/**
Get Frequency of SENSOR clock
@retval	Hz
*/
ULONG dd_topone_get_senclk(DdTopone *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL3_SENCLK() == S_ID[i]) {
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of SENSOR clock
@retval	Hz
*/
ULONG dd_topone_get_senmskclk(DdTopone *self)
{
	// 0:100MHz(=1600MHz/16)
	// 1:80MHz(=1600MHz/20)
	static const UCHAR S_DIVID[] = {16, 20};

	return (DdTopone_1600_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL3_SENMSKCLK()]);
}

/**
Get Frequency of IIP clock
@retval	Hz
*/
ULONG dd_topone_get_iipclk(DdTopone *self)
{
	// 0:300MHz(=1200MHz/4)
	// 1:200MHz(=1200MHz/6)
	// 2:150MHz(=1200MHz/8)
	// 3:100MHz(=1200MHz/12)
	// 4:75MHz(=1200MHz/16)
	// 5:60MHz(=1200MHz/20)
	// 6:50MHz(=1200MHz/24)
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};

	return (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL3_IIPCLK()]);
}

/**
Get Frequency of STAT clock
@retval	Hz
*/
ULONG dd_topone_get_pasclk(DdTopone *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)v
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL3_PASCLK() == S_ID[i]) {
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of HEVC IPP clock
@retval	Hz
*/
ULONG dd_topone_get_ippclk(DdTopone *self)
{
	// 0:800MHz    (=1600MHz/2)
	// 1:533.333MHz(=1600MHz/3)
	// 2:400MHz    (=1600MHz/4)
	// 3:200MHz    (=1600MHz/8)
	// 4:700MHz    (=1400MHz/2)
	// 8:600MHz    (=1200MHz/2)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 8, 255};
	static const UCHAR S_DIVID[] = {2, 3, 4, 8, 2, 2};
	static const ULONG S_PLLID[] = {DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT,
									DdTopone_1600_PLL_OUT, DdTopone_1400_PLL_OUT, DdTopone_1200_PLL_OUT};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL3_IPPCLK() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**
Get Frequency of HEVC PXF clock
@retval	Hz
*/
ULONG dd_topone_get_pxfclk(DdTopone *self)
{
	// 0: 700MHz(=1400MHz/2)
	// 1: 280MHz(=1400MHz/5)
	// 2: 155.555MHz(=1400MHz/9)
	// 4: 533.333MHz(=1600MHz/3)
	// 5: 400MHz(=1600MHz/4)
	// 6: 100MHz(=1600MHz/16)
	static const UCHAR S_ID[] = {0, 1, 2, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {2, 5, 9, 3, 4, 16};
	static const ULONG S_PLLID[] = {DdTopone_1400_PLL_OUT, DdTopone_1400_PLL_OUT, DdTopone_1400_PLL_OUT,
									DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL3_PXFCLK() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}

	return clock;
}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**
Get Frequency of HEVC ENC clock
@retval	Hz
*/
ULONG dd_topone_get_hevencclk(DdTopone *self)
{
	// 0:466.666MHz(=1400MHz/3)
	// 1:350MHz(=1400MHz/4)
	// 2:280MHz(=1400MHz/5)
	// 4:200MHz(=1400MHz/7)
	// 5:100MHz(=1400MHz/14)
	static const UCHAR S_ID[] = {0, 1, 2, 4, 5, 255};
	static const UCHAR S_DIVID[] = {3, 4, 5, 7, 14};
	static const ULONG S_PLLID[] = {DdTopone_1400_PLL_OUT, DdTopone_1400_PLL_OUT, DdTopone_1400_PLL_OUT,
									DdTopone_1400_PLL_OUT, DdTopone_1400_PLL_OUT};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL3_HEVENCCLK() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}

	return clock;
}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

/**
Get Frequency of HEVC VDF clock
@retval	Hz
*/
ULONG dd_topone_get_vdfclk(DdTopone *self)
{
	// 0: 700MHz(=1400MHz/2)
	// 1: 280MHz(=1400MHz/5)
	// 2: 155.555MHz(=1400MHz/9)
	// 4: 533.333MHz(=1600MHz/3)
	// 5: 400MHz(=1600MHz/4)
	// 6: 100MHz(=1600MHz/16)
	static const UCHAR S_ID[] = {0, 1, 2, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {2, 5, 9, 3, 4, 16};
	static const ULONG S_PLLID[] = {DdTopone_1400_PLL_OUT, DdTopone_1400_PLL_OUT, DdTopone_1400_PLL_OUT,
									DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT, DdTopone_1600_PLL_OUT};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL3_VDFCLK() == S_ID[i]) {
			clock = (S_PLLID[i] / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of SRO pipe1 input2 clock
@retval	Hz
*/
ULONG dd_topone_get_sro1clk_2(DdTopone *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};

	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL4_SRO1CLK_2() == S_ID[i]) {
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of R2Y pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_r2y1clk(DdTopone *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};

	return (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL4_R2Y1CLK()]);
}

/**
Get Frequency of LTM pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_ltm1clk(DdTopone *self)
{
	// 0:  300MHz(=1200MHz/4)
	// 1:  200MHz(=1200MHz/6)
	// 2:  150MHz(=1200MHz/8)
	// 3:  100MHz(=1200MHz/12)
	// 4:  75MHz(=1200MHz/16)
	// 5:  60MHz(=1200MHz/20)
	// 6:  50MHz(=1200MHz/24)
	// 8:  SRO1CLK
	// 16: SRO1CLK_2
	// 24: B2B1CLK
	// 32: B2R1CLK
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL4_LTM1CLK()) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL4_LTM1CLK()]);
			break;
		case 8:
			clock = dd_topone_get_sro1clk();
			break;
		case 16:
			clock = dd_topone_get_sro1clk_2();
			break;
		case 24:
			clock = dd_topone_get_b2b1clk();
			break;
		case 32:
			clock = dd_topone_get_b2r1clk();
			break;
	}

	return clock;
}

/**
Get Frequency of B2R pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_b2r1clk(DdTopone *self)
{
	// 0:  300MHz(=1200MHz/4)
	// 1:  200MHz(=1200MHz/6)
	// 2:  150MHz(=1200MHz/8)
	// 3:  100MHz(=1200MHz/12)
	// 4:  75MHz(=1200MHz/16)
	// 5:  60MHz(=1200MHz/20)
	// 6:  50MHz(=1200MHz/24)
	// 8:  SRO1CLK
	// 16: SRO1CLK_2
	// 24: B2B1CLK
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL4_B2R1CLK()) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL4_B2R1CLK()]);
			break;
		case 8:
			clock = dd_topone_get_sro1clk();
			break;
		case 16:
			clock = dd_topone_get_sro1clk_2();
			break;
		case 24:
			clock = dd_topone_get_sro1clk_2();
			break;
		case 32:
			clock = dd_topone_get_b2b1clk();
			break;
	}

	return clock;
}

/**
Get Frequency of CNR pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_cnr1clk(DdTopone *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	// 8: R2Y1CLK
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL4_CNR1CLK()) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL4_CNR1CLK()]);
			break;
		case 8:
			clock = dd_topone_get_r2y1clk();
			break;
	}

	return clock;
}

/**
Get Frequency of SRO pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_sro1clk(DdTopone *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};

	return (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL5_SRO1CLK()]);
}

/**
Get Frequency of B2B pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_b2b1clk(DdTopone *self)
{
	// 0:  300MHz(=1200MHz/4)
	// 1:  200MHz(=1200MHz/6)
	// 2:  150MHz(=1200MHz/8)
	// 3:  100MHz(=1200MHz/12)
	// 4:  75MHz(=1200MHz/16)
	// 5:  60MHz(=1200MHz/20)
	// 6:  50MHz(=1200MHz/24)
	// 8:  SRO1CLK
	// 16: SRO1CLK_2
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	ULONG clock = 0;

	switch (DdTopone_Get_CLKSEL5_B2B1CLK()) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL5_B2B1CLK()]);
			break;
		case 8:
			clock = dd_topone_get_sro1clk();
			break;
		case 16:
			clock = dd_topone_get_sro1clk_2();
			break;
	}

	return clock;
}

/**
Get Frequency of LTMRBK pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_ltmrbk1clk(DdTopone *self)
{
	// 0:  300MHz(=1200MHz/4)
	// 1:  200MHz(=1200MHz/6)
	// 2:  150MHz(=1200MHz/8)
	// 3:  100MHz(=1200MHz/12)
	// 4:  75MHz(=1200MHz/16)
	// 5:  60MHz(=1200MHz/20)
	// 6:  50MHz(=1200MHz/24)
	// 8:  SRO1CLK
	// 16: SRO1CLK_2
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	ULONG clock = 0;

	switch (DdTopone_GET_CLKSEL5_LTMRBK1CLK()) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_GET_CLKSEL5_LTMRBK1CLK()]);
			break;
		case 8:
			clock = dd_topone_get_sro1clk();
			break;
		case 16:
			clock = dd_topone_get_sro1clk_2();
			break;
	}

	return clock;
}

/**
Get Frequency of SRO pipe2 input2 clock
@retval	Hz
*/
ULONG dd_topone_get_sro2clk_2(DdTopone *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL6_SRO2CLK_2() == S_ID[i]) {
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of R2Y pipe2 clock
@retval	Hz
*/
ULONG dd_topone_get_r2y2clk(DdTopone *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};

	return (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL6_R2Y2CLK()]);
}


DdTopone* dd_topone_new(void)
{
	DdTopone *self = g_object_new(DD_TYPE_TOPONE, NULL);
	return self;
}

