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


#ifndef __JCTPMC_WATCHDOG_H__
#define __JCTPMC_WATCHDOG_H__


#include <klib.h>


#define JCTPMC_TYPE_WATCHDOG			(jctpmc_watchdog_get_type())
#define JCTPMC_WATCHDOG(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcWatchdog))
#define JCTPMC_IS_WATCHDOG(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_WATCHDOG))


typedef union 				_IoPmcWdogControl IoPmcWdogControl;
typedef union 				_IoPmcWdogRis IoPmcWdogRis;
typedef union 				_IoPmcWdogMis IoPmcWdogMis;
typedef union 				_IoPmcWdogItcr IoPmcWdogItcr;
typedef union 				_IoPmcWdogItop IoPmcWdogItop;
typedef union 				_IoPmcWdogPeriphid0 IoPmcWdogPeriphid0;
typedef union 				_IoPmcWdogPeriphid1 IoPmcWdogPeriphid1;
typedef union 				_IoPmcWdogPeriphid2 IoPmcWdogPeriphid2;
typedef union 				_IoPmcWdogPeriphid3 IoPmcWdogPeriphid3;
typedef union 				_IoPmcWdogPcellid IoPmcWdogPcellid;
typedef struct 				_IoPmcWatchdog IoPmcWatchdog;
typedef struct 				_JctpmcWatchdog JctpmcWatchdog;
typedef struct 				_JctpmcWatchdogPrivate JctpmcWatchdogPrivate;

/* Watchdog */

/* WdogControl */
union _IoPmcWdogControl {
	kulong		word;
	struct {
		kulong	inten			:1;
		kulong	resen			:1;
		kulong					:30;
	}bit;
};

/* WdogRIS */
union _IoPmcWdogRis {
	kulong		word;
	struct {
		kulong	wdogris			:1;
		kulong					:31;
	}bit;
};

/* WdogMIS */
union _IoPmcWdogMis {
	kulong		word;
	struct {
		kulong	wdogmis			:1;
		kulong					:31;
	}bit;
};

/* WdogITCR */
union _IoPmcWdogItcr {
	kulong		word;
	struct {
		kulong	iten			:1;
		kulong					:31;
	}bit;
};

/* WdogITOP */
union _IoPmcWdogItop {
	kulong		word;
	struct {
		kulong	wdogres			:1;
		kulong	wdogint			:1;
		kulong					:30;
	}bit;
};

/* WdogPeriphID0 */
union _IoPmcWdogPeriphid0 {
	kulong		word;
	struct {
		kulong	partnumber0		:8;
		kulong					:24;
	}bit;
};

/* WdogPeriphID1 */
union _IoPmcWdogPeriphid1 {
	kulong		word;
	struct {
		kulong	partnumber1		:4;
		kulong	designer0		:4;
		kulong					:24;
	}bit;
};

/* WdogPeriphID2 */
union _IoPmcWdogPeriphid2 {
	kulong		word;
	struct {
		kulong	designer1		:4;
		kulong	revision		:4;
		kulong					:24;
	}bit;
};

/* WdogPeriphID3 */
union _IoPmcWdogPeriphid3 {
	kulong		word;
	struct {
		kulong	configuration	:8;
		kulong					:24;
	}bit;
};

/* WdogPCellID0-3 */
union _IoPmcWdogPcellid {
	kulong		word;
	struct {
		kulong	wdogpcellid		:8;
		kulong					:24;
	}bit;
};

/* Watchdog */
struct _IoPmcWatchdog {
	/* 1DFF_(D000 - D003h)	*/
	kulong					wdogload;
	/* 1DFF_(D004 - D007h)	*/
	kulong					wdogvalue;
	/* 1DFF_(D008 - D00Bh)	*/
	IoPmcWdogControl		wdogcontrol;
	/* 1DFF_(D00C - D00Fh)	*/
	kulong					wdogintclr;
	/* 1DFF_(D010 - D013h)	*/
	IoPmcWdogRis			wdogris;
	/* 1DFF_(D014 - D017h)	*/
	IoPmcWdogMis			wdogmis;
	/* 1DFF_(D018 - DBFFh)	*/
	kuchar					dmyPmcWdog018Bff[0xC00 - 0x018];
	/* 1DFF_(DC00 - DC03h)	*/
	kulong					wdoglock;
	/* 1DFF_(DC04 - DEFFh)	*/
	kuchar					dmyPmcWdogC04Eff[0xF00 - 0xC04];
	/* 1DFF_(DF00 - DF03h)	*/
	IoPmcWdogItcr		wdogitcr;
	/* 1DFF_(DF04 - DF07h)	*/
	IoPmcWdogItop		wdogitop;
	/* 1DFF_(DF08 - DFDFh)	*/
	kuchar					dmyPmcWdogF08Fdf[0xFE0 - 0xF08];
	/* 1DFF_(DFE0 - DFE3h)	*/
	IoPmcWdogPeriphid0	wdogperiphid0;
	/* 1DFF_(DFE4 - DFE7h)	*/
	IoPmcWdogPeriphid1	wdogperiphid1;
	/* 1DFF_(DFE8 - DFEBh)	*/
	IoPmcWdogPeriphid2	wdogperiphid2;
	/* 1DFF_(DFEC - DFEFh)	*/
	IoPmcWdogPeriphid3	wdogperiphid3;
	/* 1DFF_(DFF0 - DFFFh)	*/
	IoPmcWdogPcellid		wdogpcellid[4];
};

struct _JctpmcWatchdog {
	KObject parent;
};


KConstType 						jctpmc_watchdog_get_type(void);
JctpmcWatchdog*		        jctpmc_watchdog_new(void);


#endif /* __JCTPMC_WATCHDOG_H__ */
