/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __JCTPMC_PMU_H__
#define __JCTPMC_PMU_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcPmuCtl IoPmcPmuCtl;
typedef union 				_IoPmcPmuMsr IoPmcPmuMsr;
typedef union 				_IoPmcPmuIntEn IoPmcPmuIntEn;
typedef union 				_IoPmcPmuIntSt IoPmcPmuIntSt;
typedef union 				_IoPmcPmuIntClr IoPmcPmuIntClr;
typedef union 				_IoPmcPmuStr IoPmcPmuStr;
typedef union 				_IoPmcPmuPwrOnCyc IoPmcPmuPwrOnCyc;
typedef union 				_IoPmcPmuPwrDlyCtl IoPmcPmuPwrDlyCtl;
typedef union 				_IoPmcPmuPwrTmCtl IoPmcPmuPwrTmCtl;
typedef union 				_IoPmcPmuCfg IoPmcPmuCfg;
typedef struct 				_IoPmcPmu IoPmcPmu;

/* PMU */

/* PMU_CTL */
union _IoPmcPmuCtl {
	gulong		word;
	struct {
		gulong	puset			:1;
		gulong	pdset			:1;
		gulong					:6;
		gulong	seten			:8;
		gulong					:15;
		gulong	ckge			:1;
	}bit;
};

/* PMU_MSR */
union _IoPmcPmuMsr {
	gulong		word;
	struct {
		gulong	rstsel			:1;
		gulong					:3;
		gulong	wtoffsel		:1;
		gulong					:27;
	}bit;
};

/* PMU_INT_EN */
union _IoPmcPmuIntEn {
	gulong		word;
	struct {
		gulong					:4;
		gulong	ponie			:1;
		gulong	pdnie			:1;
		gulong					:26;
	}bit;
};

/* PMU_INT_ST */
union _IoPmcPmuIntSt {
	gulong		word;
	struct {
		gulong					:4;
		gulong	poni			:1;
		gulong	pdni			:1;
		gulong					:26;
	}bit;
};

/* PMU_INT_CLR */
union _IoPmcPmuIntClr {
	gulong		word;
	struct {
		gulong					:4;
		gulong	ponic			:1;
		gulong	pdnic			:1;
		gulong					:26;
	}bit;
};

/* PMU_STR */
union _IoPmcPmuStr {
	gulong		word;
	struct {
		gulong	pmuSt			:1;
		gulong					:14;
		gulong	pwrSw			:1;
		gulong					:16;
	}bit;
};

/* PWR_ON_CYCx (x=0-1) */
union _IoPmcPmuPwrOnCyc {
	gulong		word;
	struct {
		gulong	pcyc0			:8;
		gulong	pcyc1			:8;
		gulong	pcyc2			:8;
		gulong	pcyc3			:8;
	}bit;
};

/* PWR_DLY_CTLx (x=0-1) */
union _IoPmcPmuPwrDlyCtl {
	gulong		word;
	struct {
		gulong	pon0			:5;
		gulong					:3;
		gulong	pon1			:5;
		gulong					:3;
		gulong	pon2			:5;
		gulong					:3;
		gulong	pon3			:5;
		gulong					:3;
	}bit;
};

/* PWR_TM_CTL0/PWR_TM_S1_CTL0/PWR_TM_S2_CTL0 */
union _IoPmcPmuPwrTmCtl {
	gulong		word;
	struct {
		gulong	ptc0			:3;
		gulong					:1;
		gulong	ptc1			:3;
		gulong					:1;
		gulong	ptc2			:3;
		gulong					:1;
		gulong	ptc3			:3;
		gulong					:1;
		gulong	ptc4			:3;
		gulong					:1;
		gulong	ptc5			:3;
		gulong					:1;
		gulong	ptc6			:3;
		gulong					:1;
		gulong	ptc7			:3;
		gulong					:1;
	}bit;
};

/* PMU_CFG */
union _IoPmcPmuCfg {
	gulong		word;
	struct {
		gulong	cfg				:8;
		gulong					:24;
	}bit;
};

/* PMU */
struct _IoPmcPmu {
	/* 1DFF_(F000 - F003h)	*/
	IoPmcPmuCtl			pmuCtl;
	/* 1DFF_(F004 - F007h)	*/
	IoPmcPmuMsr			pmuMsr;
	/* 1DFF_(F008 - F00Bh)	*/
	IoPmcPmuIntEn		pmuIntEn;
	/* 1DFF_(F00C - F00Fh)	*/
	IoPmcPmuIntSt		pmuIntSt;
	/* 1DFF_(F010 - F013h)	*/
	IoPmcPmuIntClr		pmuIntClr;
	/* 1DFF_(F014 - F017h)	*/
	IoPmcPmuStr			pmuStr;
	/* 1DFF_(F018 - F01Bh)	*/
	gulong					pwrStr;
	/* 1DFF_(F01C - F01Fh)	*/
	guchar					dmyPmcPmu01c01f[0x020 - 0x01C];
	/* 1DFF_(F020 - F023h)	*/
	gulong					pwrOnEn0;
	/* 1DFF_(F024 - F03Fh)	*/
	guchar					dmyPmcPmu02403f[0x040 - 0x024];
	/* 1DFF_(F040 - F043h)	*/
	gulong					pwrDnEn;
	/* 1DFF_(F044 - F04Fh)	*/
	guchar					dmyPmcPmu04404f[0x050 - 0x044];
	/* 1DFF_(F050 - F057h)	*/
	IoPmcPmuPwrOnCyc 	pwrOnCyc[2];
	/* 1DFF_(F058 - F06Fh)	*/
	guchar					dmyPmcPmu05806f[0x070 - 0x058];
	/* 1DFF_(F070 - F073h)	*/
	gulong					pwrCycSel;
	/* 1DFF_(F074 - F07Fh)	*/
	guchar					dmyPmcPmu07407f[0x080 - 0x074];
	/* 1DFF_(F080 - F087h)	*/
	IoPmcPmuPwrDlyCtl 	 pwrDlyCtl[2];
	/* 1DFF_(F088 - F09Fh)	*/
	guchar					dmyPmcPmu08809f[0x0A0 - 0x088];
	/* 1DFF_(F0A0 - F0A3h)	*/
	IoPmcPmuPwrTmCtl	pwrTmCtl0;
	/* 1DFF_(F0A4 - F0AFh)	*/
	guchar					dmyPmcPmu0a40af[0x0B0 - 0x0A4];
	/* 1DFF_(F0B0 - F0B3h)	*/
	IoPmcPmuPwrTmCtl	pwrTmS1Ctl0;
	/* 1DFF_(F0B4 - F0BFh)	*/
	guchar					dmyPmcPmu0b40bf[0x0C0 - 0x0B4];
	/* 1DFF_(F0C0 - F0C3h)	*/
	IoPmcPmuPwrTmCtl	pwrTmS2Ctl0;
	/* 1DFF_(F0C4 - F0F7h)	*/
	guchar					dmyPmcPmu0c40f7[0x0F8 - 0x0C4];
	/* 1DFF_(F0F8 - F0FBh)	*/
	gulong					mltstpPd;
	/* 1DFF_(F0FC - F0FFh)	*/
	IoPmcPmuCfg			pmuCfg;
	/* 1DFF_(F100 - FFFFh)	*/
	guchar					dmyPmcPmu100Fff[0x1000 - 0x100];
};


#endif /* __JCTPMC_PMU_H__ */
