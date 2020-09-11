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


#ifndef __JCTPMC_CALENDAR_H__
#define __JCTPMC_CALENDAR_H__


#include <klib.h>


#define JCTPMC_TYPE_CALENDAR		(jctpmc_calendar_get_type())
#define JCTPMC_CALENDAR(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcCalendar))
#define JCTPMC_IS_CALENDAR(obj)	(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_CALENDAR))


typedef union 				_IoPmcCalendarCac IoPmcCalendarCac;
typedef union 				_IoPmcCalendarCa1 IoPmcCalendarCa1;
typedef union 				_IoPmcCalendarCa2 IoPmcCalendarCa2;
typedef union 				_IoPmcCalendarCa3 IoPmcCalendarCa3;
typedef union 				_IoPmcCalendarCa4 IoPmcCalendarCa4;
typedef union 				_IoPmcCalendarCa5 IoPmcCalendarCa5;
typedef union 				_IoPmcCalendarCa6 IoPmcCalendarCa6;
typedef union 				_IoPmcCalendarCa7 IoPmcCalendarCa7;
typedef union 				_IoPmcCalendarAl1 IoPmcCalendarAl1;
typedef union 				_IoPmcCalendarAl2 IoPmcCalendarAl2;
typedef union 				_IoPmcCalendarAl3 IoPmcCalendarAl3;
typedef union 				_IoPmcCalendarAl4 IoPmcCalendarAl4;
typedef union 				_IoPmcCalendarTst IoPmcCalendarTst;
typedef struct 				_IoPmcCalendar IoPmcCalendar;
typedef struct 				_JctpmcCalendar JctpmcCalendar;
typedef struct 				_JctpmcCalendarPrivate JctpmcCalendarPrivate;

/* Calendar */

/* CAC */
union _IoPmcCalendarCac {
	kulong		word;
	struct {
		kulong	mode			:2;
		kulong	alen			:1;
		kulong	out1hzen		:1;
		kulong	alrst			:1;
		kulong	scpurst			:1;
		kulong					:1;
		kulong	irst			:1;
		kulong					:24;
	}bit;
};

/* CA1 */
union _IoPmcCalendarCa1 {
	kulong		word;
	struct {
		kulong	sec				:6;
		kulong					:26;
	}bit;
};

/* CA2 */
union _IoPmcCalendarCa2 {
	kulong		word;
	struct {
		kulong	min				:6;
		kulong					:26;
	}bit;
};

/* CA3 */
union _IoPmcCalendarCa3 {
	kulong		word;
	struct {
		kulong	hour			:5;
		kulong					:27;
	}bit;
};

/* CA4 */
union _IoPmcCalendarCa4 {
	kulong		word;
	struct {
		kulong	day				:5;
		kulong					:27;
	}bit;
};

/* CA5 */
union _IoPmcCalendarCa5 {
	kulong		word;
	struct {
		kulong	week			:3;
		kulong					:29;
	}bit;
};

/* CA6 */
union _IoPmcCalendarCa6 {
	kulong		word;
	struct {
		kulong	month			:4;
		kulong					:28;
	}bit;
};

/* CA7 */
union _IoPmcCalendarCa7 {
	kulong		word;
	struct {
		kulong	year			:7;
		kulong					:25;
	}bit;
};

/* AL1 */
union _IoPmcCalendarAl1 {
	kulong		word;
	struct {
		kulong	amin			:6;
		kulong					:26;
	}bit;
};

/* AL2 */
union _IoPmcCalendarAl2 {
	kulong		word;
	struct {
		kulong	ahour			:5;
		kulong					:27;
	}bit;
};

/* AL3 */
union _IoPmcCalendarAl3 {
	kulong		word;
	struct {
		kulong	aday			:5;
		kulong					:27;
	}bit;
};

/* AL4 */
union _IoPmcCalendarAl4 {
	kulong		word;
	struct {
		kulong	aweek			:3;
		kulong					:29;
	}bit;
};

/* TST */
union _IoPmcCalendarTst {
	kulong		word;
	struct {
		kulong	test			:4;
		kulong					:28;
	}bit;
};

/* Calendar */
struct _IoPmcCalendar {
	/* 1DFF_(C000 - C003h)	*/
	IoPmcCalendarCac		cac;
	/* 1DFF_(C004 - C007h)	*/
	IoPmcCalendarCa1		ca1;
	/* 1DFF_(C008 - C00Bh)	*/
	IoPmcCalendarCa2		ca2;
	/* 1DFF_(C00C - C00Fh)	*/
	IoPmcCalendarCa3		ca3;
	/* 1DFF_(C010 - C013h)	*/
	IoPmcCalendarCa4		ca4;
	/* 1DFF_(C014 - C017h)	*/
	IoPmcCalendarCa5		ca5;
	/* 1DFF_(C018 - C01Bh)	*/
	IoPmcCalendarCa6		ca6;
	/* 1DFF_(C01C - C01Fh)	*/
	IoPmcCalendarCa7		ca7;
	/* 1DFF_(C020 - C023h)	*/
	IoPmcCalendarAl1		al1;
	/* 1DFF_(C024 - C027h)	*/
	IoPmcCalendarAl2		al2;
	/* 1DFF_(C028 - C02Bh)	*/
	IoPmcCalendarAl3		al3;
	/* 1DFF_(C02C - C02Fh)	*/
	IoPmcCalendarAl4		al4;
	/* 1DFF_(C030 - C033h)	*/
	IoPmcCalendarTst		tst;
	/* 1DFF_(C034 - CFFFh)	*/
	kuchar					dmyPmcCalendar034Fff[0x1000 - 0x034];
};

struct _JctpmcCalendar {
	KObject parent;
};


KConstType 						jctpmc_calendar_get_type(void);
JctpmcCalendar*		        jctpmc_calendar_new(void);


#endif /* __JCTPMC_CALENDAR_H__ */
