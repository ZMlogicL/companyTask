/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition Watchdog Timer I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_WDOG_H__
#define __K_WDOG_H__

#include <klib.h>

#define K_TYPE_WDOG	(k_wdog_get_type())
#define K_WDOG(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KWdog))
#define K_IS_WDOG(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_WDOG))

typedef struct _KWdog KWdog;
typedef struct _KWdogPrivate KWdogPrivate;

typedef struct _IoWdog IoWdog;

typedef union _IoWdogControl IoWdogControl;
typedef union _IoWdogRis IoWdogRis;
typedef union _IoWdogMis IoWdogMis;
typedef union _IoWdogLock IoWdogLock;
typedef union _IoWdogItcr IoWdogItcr;
typedef union _IoWdogItop IoWdogItop;
typedef union _IoWdogPeriphid0 IoWdogPeriphid0;
typedef union _IoWdogPeriphid1 IoWdogPeriphid1;
typedef union _IoWdogPeriphid2 IoWdogPeriphid2;
typedef union _IoWdogPeriphid3 IoWdogPeriphid3;
typedef union _IoWdogPcellid IoWdogPcellid;

struct _KWdog
{
    KObject parent;
};

/* WdogControl */
union _IoWdogControl
{
    unsigned long word;
    struct
    {
        unsigned long inten :1;
        unsigned long resen :1;
        unsigned long :30;
    } bit;
};

/* WdogRIS */
union _IoWdogRis
{
    unsigned long word;
    struct
    {
        unsigned long status :1;
        unsigned long :31;
    } bit;
};

/* WdogMIS */
union _IoWdogMis
{
    unsigned long word;
    struct
    {
        unsigned long status :1;
        unsigned long :31;
    } bit;
};

/* WdogLOCK */
union _IoWdogLock
{
    unsigned long word;
    struct
    {
        unsigned long enStatus :1;
        unsigned long enRegister :31;
    } bit;
};

/* WdogITCR */
union _IoWdogItcr
{
    unsigned long word;
    struct
    {
        unsigned long iten :1;
        unsigned long :31;
    } bit;
};

/* WdogITOP */
union _IoWdogItop
{
    unsigned long word;
    struct
    {
        unsigned long wdogres :1;
        unsigned long wdogint :1;
        unsigned long :30;
    } bit;
};

/* WdogPeriphID0 */
union _IoWdogPeriphid0
{
    unsigned long word;
    struct
    {
        unsigned long partnumber0 :8;
        unsigned long :24;
    } bit;
};

/* WdogPeriphID1 */
union _IoWdogPeriphid1
{
    unsigned long word;
    struct
    {
        unsigned long partnumber1 :4;
        unsigned long designer0 :4;
        unsigned long :24;
    } bit;
};

/* WdogPeriphID2 */
union _IoWdogPeriphid2
{
    unsigned long word;
    struct
    {
        unsigned long designer1 :4;
        unsigned long revision :4;
        unsigned long :24;
    } bit;
};

/* WdogPeriphID3 */
union _IoWdogPeriphid3
{
    unsigned long word;
    struct
    {
        unsigned long configuration :8;
        unsigned long :24;
    } bit;
};

/* WdogPCellID0-3 */
union _IoWdogPcellid
{
    unsigned long word;
    struct
    {
        unsigned long wdogpcellid :8;
        unsigned long :24;
    } bit;
};

/* Watchdog Timer register                          */
struct _IoWdog
{
    unsigned long wdogload; /* 1C26_(C000 - C003h)  */
    unsigned long wdogvalue; /* 1C26_(C004 - C007h)  */
    IoWdogControl wdogcontrol; /* 1C26_(C008 - C00Bh)  */
    unsigned long wdogintclr; /* 1C26_(C00C - C00Fh)  */
    IoWdogRis wdogris; /* 1C26_(C010 - C013h)  */
    IoWdogMis wdogmis; /* 1C26_(C014 - C017h)  */
    unsigned char dmy018Bff[0xC00 - 0x018]; /* 1C26_(C018 - CBFFh)  */
    IoWdogLock wdoglock; /* 1C26_(CC00 - CC03h)  */
    unsigned char dmyC04Eff[0xF00 - 0xC04]; /* 1C26_(CC04 - CEFFh)  */
    IoWdogItcr wdogitcr; /* 1C26_(CF00 - CF03h)  */
    IoWdogItop wdogitop; /* 1C26_(CF04 - CF07h)  */
    unsigned char dmyF08Fdf[0xFE0 - 0xF08]; /* 1C26_(CF08 - CFDFh)  */
    IoWdogPeriphid0 wdogperiphid0; /* 1C26_(CFE0 - CFE3h)  */
    IoWdogPeriphid1 wdogperiphid1; /* 1C26_(CFE4 - CFE7h)  */
    IoWdogPeriphid2 wdogperiphid2; /* 1C26_(CFE8 - CFEBh)  */
    IoWdogPeriphid3 wdogperiphid3; /* 1C26_(CFEC - CFEFh)  */
    IoWdogPcellid wdogpcellid[4]; /* 1C26_(CFF0 - CFFFh)  */
};

extern volatile IoWdog ioWdog;

KConstType k_wdog_get_type(void);
KWdog* k_wdog_new(void);

#endif/*__K_WDOG_H__*/

