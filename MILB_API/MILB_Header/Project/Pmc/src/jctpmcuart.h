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


#ifndef __JCTPMC_UART_H__
#define __JCTPMC_UART_H__


#include <klib.h>


#define JCTPMC_TYPE_UART		(jctpmc_uart_get_type())
#define JCTPMC_UART(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, JctpmcUart))
#define JCTPMC_IS_UART(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, JCTPMC_TYPE_UART))


typedef union 				_IoPmcUartScr IoPmcUartScr;
typedef union 				_IoPmcUartSmr IoPmcUartSmr;
typedef union 				_IoPmcUartSsr IoPmcUartSsr;
typedef union 				_IoPmcUartEscr IoPmcUartEscr;
typedef union 				_IoPmcUartDr IoPmcUartDr;
typedef union 				_IoPmcUartBgr IoPmcUartBgr;
typedef union 				_IoPmcUartFcr IoPmcUartFcr;
typedef union 				_IoPmcUartFbyte IoPmcUartFbyte;
typedef struct 				_IoPmcUart IoPmcUart;
typedef struct 				_JctpmcUart JctpmcUart;
typedef struct 				_JctpmcUartPrivate JctpmcUartPrivate;

/* UART */
union _IoPmcUartScr {
	kuchar		byte;
	struct {
		kuchar	txe 			:1;
		kuchar	rxe 			:1;
		kuchar	tbie			:1;
		kuchar	tie 			:1;
		kuchar	rie 			:1;
		kuchar					:2;
		kuchar	upcl			:1;
	} bit;
};

union _IoPmcUartSmr {
	kuchar		byte;
	struct {
		kuchar	soe 			:1;
		kuchar					:1;
		kuchar	bds 			:1;
		kuchar	sbl 			:1;
		kuchar					:1;
		kuchar	md				:3;
	} bit;
};

union _IoPmcUartSsr {
	kuchar		byte;
	struct {
		kuchar	tbiTemp2 			:1;
		kuchar	tdreTemp2			:1;
		kuchar	rdrfTemp2			:1;
		kuchar	oreTemp2 			:1;
		kuchar	freTemp2 			:1;
		kuchar	peTemp2			:1;
		kuchar					:1;
		kuchar	recTemp2 			:1;
	} bit;
};

union _IoPmcUartEscr {
	kuchar		byte;
	struct {
		kuchar	l				:3;
		kuchar	p				:1;
		kuchar	pen 			:1;
		kuchar	inv 			:1;
		kuchar					:2;
	} bit;
};

union _IoPmcUartDr {
	kushort		hword;
	kuchar		byte[2];
	struct {
		kushort	 dataTemp2			:9;
		kushort					:7;
	} bit;
};

union _IoPmcUartBgr {
	kushort		hword;
	struct {
		kushort	bgr 			:15;
		kushort	ext 			:1;
	} bit;
};

union _IoPmcUartFcr {
	kushort		hword;
	struct {
		kuchar	fe1 			:1;
		kuchar	fe2 			:1;
		kuchar	fcl1			:1;
		kuchar	fcl2			:1;
		kuchar	fset			:1;
		kuchar	fld 			:1;
		kuchar	flst			:1;
		kuchar					:1;
		kuchar	fsel			:1;
		kuchar	ftie			:1;
		kuchar	fdrq			:1;
		kuchar	friie			:1;
		kuchar	flste			:1;
		kuchar					:1;
		kuchar	ftst0			:1;
		kuchar	ftst1			:1;
	} bit;
};

union _IoPmcUartFbyte {
	kushort		hword;
	kuchar		byte[2];
	struct {
		kushort	 fifo1Temp2 		:8;
		kushort	 fifo2Temp2 		:8;
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
	kuchar				dmyPmcUart00800b[0x00C - 0x008];
	/* 1DE0_(000C - 000Dh)	*/
	IoPmcUartFcr 	fcr;
	/* 1DE0_(000E - 000Fh)	*/
	IoPmcUartFbyte	fbyte;
	/* 1DE0_0010 - 1DEF_FFFFh	*/
	kuchar				dmyPmcUart00010Fffff[0x100000 - 0x0010];
};

struct _JctpmcUart {
	KObject parent;
};


KConstType 				jctpmc_uart_get_type(void);
JctpmcUart*		        jctpmc_uart_new(void);


#endif /* __JCTPMC_UART_H__ */
