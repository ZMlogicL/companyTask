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


#ifndef __JCTPMC_WATCHDOG_H__
#define __JCTPMC_WATCHDOG_H__


#include <stdio.h>
#include <glib-object.h>


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

/* Watchdog */

/* WdogControl */
union _IoPmcWdogControl {
	gulong		word;
	struct {
		gulong	inten			:1;
		gulong	resen			:1;
		gulong					:30;
	}bit;
};

/* WdogRIS */
union _IoPmcWdogRis {
	gulong		word;
	struct {
		gulong	wdogris			:1;
		gulong					:31;
	}bit;
};

/* WdogMIS */
union _IoPmcWdogMis {
	gulong		word;
	struct {
		gulong	wdogmis			:1;
		gulong					:31;
	}bit;
};

/* WdogITCR */
union _IoPmcWdogItcr {
	gulong		word;
	struct {
		gulong	iten			:1;
		gulong					:31;
	}bit;
};

/* WdogITOP */
union _IoPmcWdogItop {
	gulong		word;
	struct {
		gulong	wdogres			:1;
		gulong	wdogint			:1;
		gulong					:30;
	}bit;
};

/* WdogPeriphID0 */
union _IoPmcWdogPeriphid0 {
	gulong		word;
	struct {
		gulong	partnumber0		:8;
		gulong					:24;
	}bit;
};

/* WdogPeriphID1 */
union _IoPmcWdogPeriphid1 {
	gulong		word;
	struct {
		gulong	partnumber1		:4;
		gulong	designer0		:4;
		gulong					:24;
	}bit;
};

/* WdogPeriphID2 */
union _IoPmcWdogPeriphid2 {
	gulong		word;
	struct {
		gulong	designer1		:4;
		gulong	revision		:4;
		gulong					:24;
	}bit;
};

/* WdogPeriphID3 */
union _IoPmcWdogPeriphid3 {
	gulong		word;
	struct {
		gulong	configuration	:8;
		gulong					:24;
	}bit;
};

/* WdogPCellID0-3 */
union _IoPmcWdogPcellid {
	gulong		word;
	struct {
		gulong	wdogpcellid		:8;
		gulong					:24;
	}bit;
};

/* Watchdog */
struct _IoPmcWatchdog {
	/* 1DFF_(D000 - D003h)	*/
	gulong					wdogload;
	/* 1DFF_(D004 - D007h)	*/
	gulong					wdogvalue;
	/* 1DFF_(D008 - D00Bh)	*/
	IoPmcWdogControl		wdogcontrol;
	/* 1DFF_(D00C - D00Fh)	*/
	gulong					wdogintclr;
	/* 1DFF_(D010 - D013h)	*/
	IoPmcWdogRis			wdogris;
	/* 1DFF_(D014 - D017h)	*/
	IoPmcWdogMis			wdogmis;
	/* 1DFF_(D018 - DBFFh)	*/
	guchar					dmyPmcWdog018Bff[0xC00 - 0x018];
	/* 1DFF_(DC00 - DC03h)	*/
	gulong					wdoglock;
	/* 1DFF_(DC04 - DEFFh)	*/
	guchar					dmyPmcWdogC04Eff[0xF00 - 0xC04];
	/* 1DFF_(DF00 - DF03h)	*/
	IoPmcWdogItcr		wdogitcr;
	/* 1DFF_(DF04 - DF07h)	*/
	IoPmcWdogItop		wdogitop;
	/* 1DFF_(DF08 - DFDFh)	*/
	guchar					dmyPmcWdogF08Fdf[0xFE0 - 0xF08];
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


#endif /* __JCTPMC_WATCHDOG_H__ */
