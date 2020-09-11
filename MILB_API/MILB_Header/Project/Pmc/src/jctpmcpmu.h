/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
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


#include <klib.h>


#define JCTPMC_TYPE_PMU			(jctpmc_pmu_get_type())
#define JCTPMC_PMU(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcPmu))
#define JCTPMC_IS_PMU(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_PMU))


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
typedef struct 				_JctpmcPmu JctpmcPmu;
typedef struct 				_JctpmcPmuPrivate JctpmcPmuPrivate;

/* PMU */

/* PMU_CTL */
union _IoPmcPmuCtl {
	kulong		word;
	struct {
		kulong	puset			:1;
		kulong	pdset			:1;
		kulong					:6;
		kulong	seten			:8;
		kulong					:15;
		kulong	ckge			:1;
	}bit;
};

/* PMU_MSR */
union _IoPmcPmuMsr {
	kulong		word;
	struct {
		kulong	rstsel			:1;
		kulong					:3;
		kulong	wtoffsel		:1;
		kulong					:27;
	}bit;
};

/* PMU_INT_EN */
union _IoPmcPmuIntEn {
	kulong		word;
	struct {
		kulong					:4;
		kulong	ponie			:1;
		kulong	pdnie			:1;
		kulong					:26;
	}bit;
};

/* PMU_INT_ST */
union _IoPmcPmuIntSt {
	kulong		word;
	struct {
		kulong					:4;
		kulong	poni			:1;
		kulong	pdni			:1;
		kulong					:26;
	}bit;
};

/* PMU_INT_CLR */
union _IoPmcPmuIntClr {
	kulong		word;
	struct {
		kulong					:4;
		kulong	ponic			:1;
		kulong	pdnic			:1;
		kulong					:26;
	}bit;
};

/* PMU_STR */
union _IoPmcPmuStr {
	kulong		word;
	struct {
		kulong	pmuSt			:1;
		kulong					:14;
		kulong	pwrSw			:1;
		kulong					:16;
	}bit;
};

/* PWR_ON_CYCx (x=0-1) */
union _IoPmcPmuPwrOnCyc {
	kulong		word;
	struct {
		kulong	pcyc0			:8;
		kulong	pcyc1			:8;
		kulong	pcyc2			:8;
		kulong	pcyc3			:8;
	}bit;
};

/* PWR_DLY_CTLx (x=0-1) */
union _IoPmcPmuPwrDlyCtl {
	kulong		word;
	struct {
		kulong	pon0			:5;
		kulong					:3;
		kulong	pon1			:5;
		kulong					:3;
		kulong	pon2			:5;
		kulong					:3;
		kulong	pon3			:5;
		kulong					:3;
	}bit;
};

/* PWR_TM_CTL0/PWR_TM_S1_CTL0/PWR_TM_S2_CTL0 */
union _IoPmcPmuPwrTmCtl {
	kulong		word;
	struct {
		kulong	ptc0			:3;
		kulong					:1;
		kulong	ptc1			:3;
		kulong					:1;
		kulong	ptc2			:3;
		kulong					:1;
		kulong	ptc3			:3;
		kulong					:1;
		kulong	ptc4			:3;
		kulong					:1;
		kulong	ptc5			:3;
		kulong					:1;
		kulong	ptc6			:3;
		kulong					:1;
		kulong	ptc7			:3;
		kulong					:1;
	}bit;
};

/* PMU_CFG */
union _IoPmcPmuCfg {
	kulong		word;
	struct {
		kulong	cfg				:8;
		kulong					:24;
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
	kulong					pwrStr;
	/* 1DFF_(F01C - F01Fh)	*/
	kuchar					dmyPmcPmu01c01f[0x020 - 0x01C];
	/* 1DFF_(F020 - F023h)	*/
	kulong					pwrOnEn0;
	/* 1DFF_(F024 - F03Fh)	*/
	kuchar					dmyPmcPmu02403f[0x040 - 0x024];
	/* 1DFF_(F040 - F043h)	*/
	kulong					pwrDnEn;
	/* 1DFF_(F044 - F04Fh)	*/
	kuchar					dmyPmcPmu04404f[0x050 - 0x044];
	/* 1DFF_(F050 - F057h)	*/
	IoPmcPmuPwrOnCyc 	pwrOnCyc[2];
	/* 1DFF_(F058 - F06Fh)	*/
	kuchar					dmyPmcPmu05806f[0x070 - 0x058];
	/* 1DFF_(F070 - F073h)	*/
	kulong					pwrCycSel;
	/* 1DFF_(F074 - F07Fh)	*/
	kuchar					dmyPmcPmu07407f[0x080 - 0x074];
	/* 1DFF_(F080 - F087h)	*/
	IoPmcPmuPwrDlyCtl 	 pwrDlyCtl[2];
	/* 1DFF_(F088 - F09Fh)	*/
	kuchar					dmyPmcPmu08809f[0x0A0 - 0x088];
	/* 1DFF_(F0A0 - F0A3h)	*/
	IoPmcPmuPwrTmCtl	pwrTmCtl0;
	/* 1DFF_(F0A4 - F0AFh)	*/
	kuchar					dmyPmcPmu0a40af[0x0B0 - 0x0A4];
	/* 1DFF_(F0B0 - F0B3h)	*/
	IoPmcPmuPwrTmCtl	pwrTmS1Ctl0;
	/* 1DFF_(F0B4 - F0BFh)	*/
	kuchar					dmyPmcPmu0b40bf[0x0C0 - 0x0B4];
	/* 1DFF_(F0C0 - F0C3h)	*/
	IoPmcPmuPwrTmCtl	pwrTmS2Ctl0;
	/* 1DFF_(F0C4 - F0F7h)	*/
	kuchar					dmyPmcPmu0c40f7[0x0F8 - 0x0C4];
	/* 1DFF_(F0F8 - F0FBh)	*/
	kulong					mltstpPd;
	/* 1DFF_(F0FC - F0FFh)	*/
	IoPmcPmuCfg			pmuCfg;
	/* 1DFF_(F100 - FFFFh)	*/
	kuchar					dmyPmcPmu100Fff[0x1000 - 0x100];
};

struct _JctpmcPmu {
	KObject parent;
};


KConstType 				jctpmc_pmu_get_type(void);
JctpmcPmu*		        jctpmc_pmu_new(void);


#endif /* __JCTPMC_PMU_H__ */
