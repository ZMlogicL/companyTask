/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :陈倩
 *@brief             :kjmiluart
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *3、
 *4、
 *5、
 *@version
 *
 */

#ifndef __K_JMILUART_H__
#define __K_JMILUART_H__


#include <klib.h>


#define K_TYPE_JMILUART			(k_jmiluart_get_type())
#define K_JMILUART(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJmiluart))
#define K_IS_JMILUART(obj)		(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JMILUART))


typedef struct _KJmiluart 			KJmiluart;
typedef struct _KJmiluartPrivate KJmiluartPrivate;


struct _KJmiluart
{
	KObject parent;
};

/* uart */
typedef union _IoUartScr
{
	kuchar byte;
	struct
	{
		kuchar txe :1;
		kuchar rxe :1;
		kuchar tbie :1;
		kuchar tie :1;
		kuchar rie :1;
		kuchar :2;
		kuchar upcl :1;
	} bit;
} IoUartScr;

typedef union _IoUartSmr
{
	kuchar byte;
	struct
	{
		kuchar soe :1;
		kuchar :1;
		kuchar bds :1;
		kuchar sbl :1;
		kuchar :1;
		kuchar md :3;
	} bit;
} IoUartSmr;

typedef union _IoUartSsr
{
	kuchar byte;
	struct
	{
		kuchar __tbi :1;
		kuchar __tdre :1;
		kuchar __rdrf :1;
		kuchar __ore :1;
		kuchar __fre :1;
		kuchar __pe :1;
		kuchar :1;
		kuchar __rec :1;
	} bit;
} IoUartSsr;

typedef union _IoUartEscr
{
	kuchar byte;
	struct
	{
		kuchar l :3;
		kuchar p :1;
		kuchar pen :1;
		kuchar inv :1;
		kuchar :1;
		kuchar flwen :1;
	} bit;
} IoUartEscr;

typedef union _IoUartDr
{
	kushort hword;
	kuchar byte[2];
	struct
	{
		kushort __data :9;
		kushort :7;
	} bit;
} IoUartDr;

typedef union _IoUartBgr
{
	kushort hword;
	struct
	{
		kushort bgr :15;
		kushort ext :1;
	} bit;
} IoUartBgr;

/* csio */
typedef union _IoSsioScr
{
	kuchar byte;
	struct
	{
		kuchar txe :1;
		kuchar rxe :1;
		kuchar tbie :1;
		kuchar tie :1;
		kuchar rie :1;
		kuchar spi :1;
		kuchar ms :1;
		kuchar upcl :1;
	} bit;
} IoSsioScr;

typedef union _IoCsioSmr
{
	kuchar byte;
	struct
	{
		kuchar soe :1;
		kuchar scke :1;
		kuchar bds :1;
		kuchar scinv :1;
		kuchar :1;
		kuchar md :3;
	} bit;
} IoCsioSmr;

typedef union _IoCsioSsr
{
	kuchar byte;
	struct
	{
		kuchar __tbi :1;
		kuchar __tdre :1;
		kuchar __rdrf :1;
		kuchar __ore :1;
		kuchar :3;
		kuchar __rec :1;
	} bit;
} IoCsioSsr;

typedef union _IoCsioEscr
{
	kuchar byte;
	struct
	{
		kuchar l :3;
		kuchar :2;
		kuchar :2;
		kuchar sop :1;
	} bit;
} IoCsioEscr;

typedef union IoCsioDr
{
	kushort hword;
	kuchar byte[2];
	struct
	{
		kushort __data :9;
		kushort :7;
	} bit;
} IoCsioDr;

typedef union _IoCsioBgr
{
	kushort hword;
	struct
	{
		kushort bgr :15;
		kushort :1;
	} bit;
} IoCsioBgr;

/* uart/csio common */
typedef union _IoUsioFcr
{
	kushort hword;
	struct
	{
		kuchar fe1 :1;
		kuchar fe2 :1;
		kuchar fcl1 :1;
		kuchar fcl2 :1;
		kuchar fset :1;
		kuchar fld :1;
		kuchar flst :1;
		kuchar :1;

		kuchar fsel :1;
		kuchar ftie :1;
		kuchar fdrq :1;
		kuchar friie :1;
		kuchar flste :1;
		kuchar :1;
		kuchar ftst0 :1;
		kuchar ftst1 :1;
	} bit;
} IoUsioFcr;

typedef union _IoUsioFbyte
{
	kushort hword;
	kuchar byte[2];
	struct
	{
		kushort __fifo1 :8;
		kushort __fifo2 :8;
	} bit;
} IoUsioFbyte;

/* uart */
typedef struct _IoUart
{
	/* 1E70_0000h	*/
	IoUartSmr smr;
	/* 1E70_0001h	*/
	IoUartScr scr;
	/* 1E70_0002h	*/
	IoUartEscr escr;
	/* 1E70_0003h	*/
	IoUartSsr ssr;
	/* 1E70_(0004 - 0005h)	*/
	IoUartDr dr;
	/* 1E70_(0006 - 0007h)	*/
	IoUartBgr bgr;
	/* 1E70_(0008 - 000Bh)	*/
	kuchar dmyuart0008000b[0x000C - 0x0008];
	/* 1E70_(000C - 000Dh)	*/
	IoUsioFcr fcr;
	/* 1E70_(000E - 000Fh)	*/
	IoUsioFbyte fbyte;
} IoUart;

/* csio */
typedef struct _IoCsio
{
	/* 1E70_0000h	*/
	IoCsioSmr smr;
	/* 1E70_0001h	*/
	IoSsioScr scr;
	/* 1E70_0002h	*/
	IoCsioEscr escr;
	/* 1E70_0003h	*/
	IoCsioSsr ssr;
	/* 1E70_(0004 - 0005h)	*/
	IoCsioDr dr;
	/* 1E70_(0006 - 0007h)	*/
	IoCsioBgr bgr;
	/* 1E70_(0008 - 000Bh)	*/
	kuchar dmycsio0008000b[0x000C - 0x0008];
	/* 1E70_(000C - 000Dh)	*/
	IoUsioFcr fcr;
	/* 1E70_(000E - 000Fh)	*/
	IoUsioFbyte fbyte;
} IoCsio;

/* Define I/O mapping		*/
typedef union _IoUsio
{
	/* 1E70_(0000 - 007Fh)	*/
	IoUart uart[8];
	/* 1E70_(0000 - 007Fh)	*/
	IoCsio csio[8];
} IoUsio;


/* addr 1E70_0000h- */
extern volatile IoUsio ioUsio;


KConstType k_jmiluart_get_type(void);
KJmiluart* k_jmiluart_new(void);


#endif/*__K_JMILUART_H__*/

