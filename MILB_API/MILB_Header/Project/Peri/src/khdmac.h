/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :陈倩
 *@brief             :khdmac
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

#ifndef __K_HDMAC_H__
#define __K_HDMAC_H__


#include <klib.h>


#define K_TYPE_HDMAC				(k_hdmac_get_type())
#define K_HDMAC(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KHdmac))
#define K_IS_HDMAC(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_HDMAC))


typedef struct _KHdmac KHdmac;
typedef struct _KHdmacPrivate KHdmacPrivate;

struct _KHdmac
{
	KObject parent;
};

typedef union _IoHdmacDmacr
{
	unsigned long word;
	struct
	{
		unsigned long :24;
		unsigned long dh :4;
		unsigned long pr :1;
		unsigned long :1;
		unsigned long ds :1;
		unsigned long de :1;
	} bit;
} IoHdmacDmacr;

typedef union _IoHdmacDmaca
{
	unsigned long word;
	struct
	{
		unsigned long tc :16;
		unsigned long bc :4;
		unsigned long bt :4;
		unsigned long is :5;
		unsigned long st :1;
		unsigned long pb :1;
		unsigned long eb :1;
	} bit;
} IoHdmacDmaca;

typedef union _IoHdmacDmacb
{
	unsigned long word;
	struct
	{
		unsigned long :8;
		unsigned long dp :4;
		unsigned long sp :4;
		unsigned long ss :3;
		unsigned long ci :1;
		unsigned long ei :1;
		unsigned long rd :1;
		unsigned long rs :1;
		unsigned long rc :1;
		unsigned long fd :1;
		unsigned long fs :1;
		unsigned long tw :2;
		unsigned long ms :2;
		unsigned long tt :2;
	} bit;
} IoHdmacDmacb;

typedef struct _IoHdmacElement
{
	/* 0-7ch 10,20,30,40,50,60,70,80 */
	IoHdmacDmaca dmaca;
	/* 0-7ch 14,24,34,44,54,64,74,84 */
	IoHdmacDmacb dmacb;
	/* 0-7ch 18,28,38,48,58,68,78,88 */
	unsigned long dmacsa;
	/* 0-7ch 1C,2C,3C,4C,5C,6C,7C,8C */
	unsigned long dmacda;
} IoHdmacElement;

typedef struct _IoHdmac
{
	/* 1E10_(0000 - 0003h) */
	IoHdmacDmacr dmacr;
	/* 1E10_(0004 - 000Fh) */
	unsigned char dmy040f[0x10 - 0x04];
	/* 1E10_(0010 - 008Fh) */
	IoHdmacElement dmac[8];
} IoHdmac;


/* 1B04_0000 */
extern volatile IoHdmac ioHdmac;
/* 1E10_0000 */
extern volatile IoHdmac ioHdmac0;
/* 1E11_0000 */
extern volatile IoHdmac ioHdmac1;


KConstType k_hdmac_get_type(void);
KHdmac* k_hdmac_new(void);

#endif/*__K_HDMAC_H__*/

