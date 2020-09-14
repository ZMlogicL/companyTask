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


#ifndef __JCTPMC_UART_H__
#define __JCTPMC_UART_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPmcUartScr IoPmcUartScr;
typedef union 				_IoPmcUartSmr IoPmcUartSmr;
typedef union 				_IoPmcUartSsr IoPmcUartSsr;
typedef union 				_IoPmcUartEscr IoPmcUartEscr;
typedef union 				_IoPmcUartDr IoPmcUartDr;
typedef union 				_IoPmcUartBgr IoPmcUartBgr;
typedef union 				_IoPmcUartFcr IoPmcUartFcr;
typedef union 				_IoPmcUartFbyte IoPmcUartFbyte;
typedef struct 				_IoPmcUart IoPmcUart;

/* UART */
union _IoPmcUartScr {
	guchar		byte;
	struct {
		guchar	txe 			:1;
		guchar	rxe 			:1;
		guchar	tbie			:1;
		guchar	tie 			:1;
		guchar	rie 			:1;
		guchar					:2;
		guchar	upcl			:1;
	} bit;
};

union _IoPmcUartSmr {
	guchar		byte;
	struct {
		guchar	soe 			:1;
		guchar					:1;
		guchar	bds 			:1;
		guchar	sbl 			:1;
		guchar					:1;
		guchar	md				:3;
	} bit;
};

union _IoPmcUartSsr {
	guchar		byte;
	struct {
		guchar	tbiTemp2 			:1;
		guchar	tdreTemp2			:1;
		guchar	rdrfTemp2			:1;
		guchar	oreTemp2 			:1;
		guchar	freTemp2 			:1;
		guchar	peTemp2			:1;
		guchar					:1;
		guchar	recTemp2 			:1;
	} bit;
};

union _IoPmcUartEscr {
	guchar		byte;
	struct {
		guchar	l				:3;
		guchar	p				:1;
		guchar	pen 			:1;
		guchar	inv 			:1;
		guchar					:2;
	} bit;
};

union _IoPmcUartDr {
	gushort		hword;
	guchar		byte[2];
	struct {
		gushort	 dataTemp2			:9;
		gushort					:7;
	} bit;
};

union _IoPmcUartBgr {
	gushort		hword;
	struct {
		gushort	bgr 			:15;
		gushort	ext 			:1;
	} bit;
};

union _IoPmcUartFcr {
	gushort		hword;
	struct {
		guchar	fe1 			:1;
		guchar	fe2 			:1;
		guchar	fcl1			:1;
		guchar	fcl2			:1;
		guchar	fset			:1;
		guchar	fld 			:1;
		guchar	flst			:1;
		guchar					:1;
		guchar	fsel			:1;
		guchar	ftie			:1;
		guchar	fdrq			:1;
		guchar	friie			:1;
		guchar	flste			:1;
		guchar					:1;
		guchar	ftst0			:1;
		guchar	ftst1			:1;
	} bit;
};

union _IoPmcUartFbyte {
	gushort		hword;
	guchar		byte[2];
	struct {
		gushort	 fifo1Temp2 		:8;
		gushort	 fifo2Temp2 		:8;
	} bit;
};

/* UART */
struct _IoPmcUart {
	/* 1DE0_0000h	*/
	IoPmcUartSmr 	smr;
	/* 1DE0_0001h	*/
	IoPmcUartScr 	scr;
	/* 1DE0_0002h	*/
	IoPmcUartEscr	escr;
	/* 1DE0_0003h	*/
	IoPmcUartSsr 	ssr;
	/* 1DE0_(0004 - 0005h)	*/
	IoPmcUartDr		dr;
	/* 1DE0_(0006 - 0007h)	*/
	IoPmcUartBgr 	bgr;
	/* 1DE0_(0008 - 000Bh)	*/
	guchar				dmyPmcUart00800b[0x00C - 0x008];
	/* 1DE0_(000C - 000Dh)	*/
	IoPmcUartFcr 	fcr;
	/* 1DE0_(000E - 000Fh)	*/
	IoPmcUartFbyte	fbyte;
	/* 1DE0_0010 - 1DEF_FFFFh	*/
	guchar				dmyPmcUart00010Fffff[0x100000 - 0x0010];
};


#endif /* __JCTPMC_UART_H__ */
