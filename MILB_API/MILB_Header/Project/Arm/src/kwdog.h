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


#define K_TYPE_WDOG	           (k_wdog_get_type())
#define K_WDOG(obj)	           (K_TYPE_CHECK_INSTANCE_CAST((obj), KWdog))
#define K_IS_WDOG(obj)	       (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_WDOG))


typedef struct _KWdog           KWdog;
typedef struct _KWdogPrivate    KWdogPrivate;

typedef struct _IoWdog          IoWdog;

typedef union _IoWdogControl    IoWdogControl;
typedef union _IoWdogRis        IoWdogRis;
typedef union _IoWdogMis        IoWdogMis;
typedef union _IoWdogLock       IoWdogLock;
typedef union _IoWdogItcr       IoWdogItcr;
typedef union _IoWdogItop       IoWdogItop;
typedef union _IoWdogPeriphid0  IoWdogPeriphid0;
typedef union _IoWdogPeriphid1  IoWdogPeriphid1;
typedef union _IoWdogPeriphid2  IoWdogPeriphid2;
typedef union _IoWdogPeriphid3  IoWdogPeriphid3;
typedef union _IoWdogPcellid    IoWdogPcellid;


struct _KWdog
{
    KObject parent;
};


/* WdogControl */
union _IoWdogControl
{
    kulong word;
    struct
    {
        kulong inten :1;
        kulong resen :1;
        kulong :30;
    } bit;
};

/* WdogRIS */
union _IoWdogRis
{
    kulong word;
    struct
    {
        kulong status :1;
        kulong :31;
    } bit;
};

/* WdogMIS */
union _IoWdogMis
{
    kulong word;
    struct
    {
        kulong status :1;
        kulong :31;
    } bit;
};

/* WdogLOCK */
union _IoWdogLock
{
    kulong word;
    struct
    {
        kulong enStatus :1;
        kulong enRegister :31;
    } bit;
};

/* WdogITCR */
union _IoWdogItcr
{
    kulong word;
    struct
    {
        kulong iten :1;
        kulong :31;
    } bit;
};

/* WdogITOP */
union _IoWdogItop
{
    kulong word;
    struct
    {
        kulong wdogRes :1;
        kulong wdogInt :1;
        kulong :30;
    } bit;
};

/* WdogPeriphID0 */
union _IoWdogPeriphid0
{
    kulong word;
    struct
    {
        kulong partNumber0 :8;
        kulong :24;
    } bit;
};

/* WdogPeriphID1 */
union _IoWdogPeriphid1
{
    kulong word;
    struct
    {
        kulong partNumber1 :4;
        kulong designer0 :4;
        kulong :24;
    } bit;
};

/* WdogPeriphID2 */
union _IoWdogPeriphid2
{
    kulong word;
    struct
    {
        kulong designer1 :4;
        kulong revision :4;
        kulong :24;
    } bit;
};

/* WdogPeriphID3 */
union _IoWdogPeriphid3
{
    kulong word;
    struct
    {
        kulong configuration :8;
        kulong :24;
    } bit;
};

/* WdogPCellID0-3 */
union _IoWdogPcellid
{
    kulong word;
    struct
    {
        kulong wdogPCellId :8;
        kulong :24;
    } bit;
};


/* Watchdog Timer register                          */
struct _IoWdog
{
    kulong wdogLoad; /* 1C26_(C000 - C003h)  */
    kulong wdogValue; /* 1C26_(C004 - C007h)  */
    IoWdogControl wdogControl; /* 1C26_(C008 - C00Bh)  */
    kulong wdogIntclr; /* 1C26_(C00C - C00Fh)  */
    IoWdogRis wdogRis; /* 1C26_(C010 - C013h)  */
    IoWdogMis wdogMis; /* 1C26_(C014 - C017h)  */
    kuchar dmy018Bff[0xC00 - 0x018]; /* 1C26_(C018 - CBFFh)  */
    IoWdogLock wdogLock; /* 1C26_(CC00 - CC03h)  */
    kuchar dmyC04Eff[0xF00 - 0xC04]; /* 1C26_(CC04 - CEFFh)  */
    IoWdogItcr wdogItcr; /* 1C26_(CF00 - CF03h)  */
    IoWdogItop wdogItop; /* 1C26_(CF04 - CF07h)  */
    kuchar dmyF08Fdf[0xFE0 - 0xF08]; /* 1C26_(CF08 - CFDFh)  */
    IoWdogPeriphid0 wdogPeriPhId0; /* 1C26_(CFE0 - CFE3h)  */
    IoWdogPeriphid1 wdogPeriPhId1; /* 1C26_(CFE4 - CFE7h)  */
    IoWdogPeriphid2 wdogPeriPhId2; /* 1C26_(CFE8 - CFEBh)  */
    IoWdogPeriphid3 wdogPeriPhId3; /* 1C26_(CFEC - CFEFh)  */
    IoWdogPcellid wdogPCellId[4]; /* 1C26_(CFF0 - CFFFh)  */
};


extern volatile IoWdog ioWdog;


KConstType  k_wdog_get_type(void);
KWdog*      k_wdog_new(void);


#endif/*__K_WDOG_H__*/
