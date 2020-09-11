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


typedef struct _KJmiluart KJmiluart;
typedef struct _KJmiluartPrivate KJmiluartPrivate;


struct _KJmiluart
{
	KObject parent;
};

/* uart */
typedef union _IoUartScr
{
	unsigned char byte;
	struct
	{
		unsigned char txe :1;
		unsigned char rxe :1;
		unsigned char tbie :1;
		unsigned char tie :1;
		unsigned char rie :1;
		unsigned char :2;
		unsigned char upcl :1;
	} bit;
} IoUartScr;

typedef union _IoUartSmr
{
	unsigned char byte;
	struct
	{
		unsigned char soe :1;
		unsigned char :1;
		unsigned char bds :1;
		unsigned char sbl :1;
		unsigned char :1;
		unsigned char md :3;
	} bit;
} IoUartSmr;

typedef union _IoUartSsr
{
	unsigned char byte;
	struct
	{
		unsigned char __tbi :1;
		unsigned char __tdre :1;
		unsigned char __rdrf :1;
		unsigned char __ore :1;
		unsigned char __fre :1;
		unsigned char __pe :1;
		unsigned char :1;
		unsigned char __rec :1;
	} bit;
} IoUartSsr;

typedef union _IoUartEscr
{
	unsigned char byte;
	struct
	{
		unsigned char l :3;
		unsigned char p :1;
		unsigned char pen :1;
		unsigned char inv :1;
		unsigned char :1;
		unsigned char flwen :1;
	} bit;
} IoUartEscr;

typedef union _IoUartDr
{
	unsigned short hword;
	unsigned char byte[2];
	struct
	{
		unsigned short __data :9;
		unsigned short :7;
	} bit;
} IoUartDr;

typedef union _IoUartBgr
{
	unsigned short hword;
	struct
	{
		unsigned short bgr :15;
		unsigned short ext :1;
	} bit;
} IoUartBgr;

/* csio */
typedef union _IoSsioScr
{
	unsigned char byte;
	struct
	{
		unsigned char txe :1;
		unsigned char rxe :1;
		unsigned char tbie :1;
		unsigned char tie :1;
		unsigned char rie :1;
		unsigned char spi :1;
		unsigned char ms :1;
		unsigned char upcl :1;
	} bit;
} IoSsioScr;

typedef union _IoCsioSmr
{
	unsigned char byte;
	struct
	{
		unsigned char soe :1;
		unsigned char scke :1;
		unsigned char bds :1;
		unsigned char scinv :1;
		unsigned char :1;
		unsigned char md :3;
	} bit;
} IoCsioSmr;

typedef union _IoCsioSsr
{
	unsigned char byte;
	struct
	{
		unsigned char __tbi :1;
		unsigned char __tdre :1;
		unsigned char __rdrf :1;
		unsigned char __ore :1;
		unsigned char :3;
		unsigned char __rec :1;
	} bit;
} IoCsioSsr;

typedef union _IoCsioEscr
{
	unsigned char byte;
	struct
	{
		unsigned char l :3;
		unsigned char :2;
		unsigned char :2;
		unsigned char sop :1;
	} bit;
} IoCsioEscr;

typedef union IoCsioDr
{
	unsigned short hword;
	unsigned char byte[2];
	struct
	{
		unsigned short __data :9;
		unsigned short :7;
	} bit;
} IoCsioDr;

typedef union _IoCsioBgr
{
	unsigned short hword;
	struct
	{
		unsigned short bgr :15;
		unsigned short :1;
	} bit;
} IoCsioBgr;

/* uart/csio common */
typedef union _IoUsioFcr
{
	unsigned short hword;
	struct
	{
		unsigned char fe1 :1;
		unsigned char fe2 :1;
		unsigned char fcl1 :1;
		unsigned char fcl2 :1;
		unsigned char fset :1;
		unsigned char fld :1;
		unsigned char flst :1;
		unsigned char :1;

		unsigned char fsel :1;
		unsigned char ftie :1;
		unsigned char fdrq :1;
		unsigned char friie :1;
		unsigned char flste :1;
		unsigned char :1;
		unsigned char ftst0 :1;
		unsigned char ftst1 :1;
	} bit;
} IoUsioFcr;

typedef union _IoUsioFbyte
{
	unsigned short hword;
	unsigned char byte[2];
	struct
	{
		unsigned short __fifo1 :8;
		unsigned short __fifo2 :8;
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
	unsigned char dmyuart0008000b[0x000C - 0x0008];
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
	unsigned char dmycsio0008000b[0x000C - 0x0008];
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

