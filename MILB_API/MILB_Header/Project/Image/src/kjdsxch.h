/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSXH2D Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_JDSXCH_H__
#define __K_JDSXCH_H__

#include <klib.h>

#define K_TYPE_JDSXCH	(k_jdsxch_get_type())
#define K_JDSXCH(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsxch))
#define K_IS_JDSXCH(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSXCH))

typedef struct _KJdsxch KJdsxch;
typedef struct _KJdsxchPrivate KJdsxchPrivate;

typedef struct _IoXchXctl IoXchXctl;
typedef struct _IoJdsxch IoJdsxch;

typedef union _IoXchSr IoXchSr;
typedef union _IoXchXchice IoXchXchice;
typedef union _IoXchXchicf IoXchXchicf;
typedef union _IoXchXtrg IoXchXtrg;
typedef union _IoXchXdtype IoXchXdtype;
typedef union _IoXchXmd IoXchXmd;
typedef union _IoXchXfdt IoXchXfdt;
typedef union _IoXchXcyc IoXchXcyc;
typedef union _IoXchXven IoXchXven;
typedef union _IoXchXhen IoXchXhen;
typedef union _IoXchXshw IoXchXshw;
typedef union _IoXchXghw IoXchXghw;
typedef union _IoXchXdvw IoXchXdvw;
typedef union _IoXchXdhw IoXchXdhw;
typedef union _IoXchXsa IoXchXsa;
typedef union _IoXchXda IoXchXda;
typedef union _IoXchXhistg0 IoXchXhistg0;
typedef union _IoXchXhbf IoXchXhbf;

struct _KJdsxch
{
    KObject parent;
};

/*  structure of sr (288C_0000h)    */
union _IoXchSr
{
    unsigned long word;
    struct
    {
        unsigned long sr :1;
        unsigned long :31;
    } bit;
};

/*  structure of xchice (288C_0004h)    */
union _IoXchXchice
{
    unsigned long word;
    struct
    {
        unsigned long xe0 :1;
        unsigned long :3;
        unsigned long xe1 :1;
        unsigned long :27;
    } bit;
};

/*  structure of xchicf (288C_0008h)    */
union _IoXchXchicf
{
    unsigned long word;
    struct
    {
        unsigned long xf0 :1;
        unsigned long :3;
        unsigned long xf1 :1;
        unsigned long :27;
    } bit;
};

/*  structure of XTRG0  (288C_000Ch)    */
/*  structure of XTRG1  (288C_0050h)    */
union _IoXchXtrg
{
    unsigned long word;
    struct
    {
        unsigned long xtrg :2;
        unsigned long :30;
    } bit;
};

/*  structure of XDTYPE0    (288C_0014h)    */
/*  structure of XDTYPE1    (288C_0058h)    */
union _IoXchXdtype
{
    unsigned long word;
    struct
    {
        unsigned long xsdtype :2;
        unsigned long :2;
        unsigned long xddtype :2;
        unsigned long :26;
    } bit;
};

/*  structure of XMD0   (288C_0018h)    */
/*  structure of XMD1   (288C_005Ch)    */
union _IoXchXmd
{
    unsigned long word;
    struct
    {
        unsigned long xmd :3;
        unsigned long :29;
    } bit;
};

/*  structure of XFDT0  (288C_001Ch)    */
/*  structure of XFDT1  (288C_0060h)    */
union _IoXchXfdt
{
    unsigned long word;
    struct
    {
        unsigned long xfdt :8;
        unsigned long :24;
    } bit;
};

/*  structure of XCYC0  (288C_0020h)    */
/*  structure of XCYC1  (288C_0064h)    */
union _IoXchXcyc
{
    unsigned long word;
    struct
    {
        unsigned long xvcyc :5;
        unsigned long :3;
        unsigned long xhcyc :5;
        unsigned long :19;
    } bit;
};

/*  structure of XVEN0  (288C_0024h)    */
/*  structure of XVEN1  (288C_0068h)    */
union _IoXchXven
{
    unsigned long word;
    struct
    {
        unsigned long xven :32;
    } bit;
};

/*  structure of XHEN0  (288C_0028h)    */
/*  structure of XHEN1  (288C_006Ch)    */
union _IoXchXhen
{
    unsigned long word;
    struct
    {
        unsigned long xhen :32;
    } bit;
};

/*  structure of XSHW0  (288C_002Ch)    */
/*  structure of XSHW1  (288C_0070h)    */
union _IoXchXshw
{
    unsigned long word;
    struct
    {
        unsigned long xshw :16;
        unsigned long :16;
    } bit;
};

/*  structure of XGHW0  (288C_0030h)    */
/*  structure of XGHW1  (288C_0074h)    */
union _IoXchXghw
{
    unsigned long word;
    struct
    {
        unsigned long xghw :16;
        unsigned long :16;
    } bit;
};

/*  structure of XDVW0  (288C_0034h)    */
/*  structure of XDVW1  (288C_0078h)    */
union _IoXchXdvw
{
    unsigned long word;
    struct
    {
        unsigned long xdvw :14;
        unsigned long :18;
    } bit;
};

/*  structure of XDHW0  (288C_0038h)    */
/*  structure of XDHW1  (288C_007Ch)    */
union _IoXchXdhw
{
    unsigned long word;
    struct
    {
        unsigned long xdhw :15;
        unsigned long :17;
    } bit;
};

/*  structure of XSA0   (288C_003Ch)    */
/*  structure of XSA1   (288C_0080h)    */
union _IoXchXsa
{
    unsigned long word;
    struct
    {
        unsigned long xsa :32;
    } bit;
};

/*  structure of XDA0   (288C_0040h)    */
/*  structure of XDA1   (288C_0084h)    */
union _IoXchXda
{
    unsigned long word;
    struct
    {
        unsigned long xda :32;
    } bit;
};

/*  structure of xhistg0    (288C_0044h)    */
union _IoXchXhistg0
{
    unsigned long word;
    struct
    {
        unsigned long xhmax0 :8;
        unsigned long xhren0 :1;
        unsigned long :3;
        unsigned long xhcnt0 :1;
        unsigned long :19;
    } bit;
};

/*  structure of xhbf   (288C_0400h)    */
union _IoXchXhbf
{
    unsigned long word;
    struct
    {
        unsigned long xhbf :24;
        unsigned long :8;
    } bit;
};

/* Xch control of each channel common */
struct _IoXchXctl
{
    IoXchXtrg xtrg; /* 288C_(000C - 000Fh) *//* 288C_(0050 - 0053h) */

    unsigned char dmy00100013[0x0014 - 0x0010]; /* 288C_(0010 - 0013h) *//* 288C_(0054 - 0057h) */

    IoXchXdtype xdtype; /* 288C_(0014 - 0017h) *//* 288C_(0058 - 005Bh) */
    IoXchXmd xmd; /* 288C_(0018 - 001Bh) *//* 288C_(005C - 005Fh) */
    IoXchXfdt xfdt; /* 288C_(001C - 001Fh) *//* 288C_(0060 - 0063h) */
    IoXchXcyc xcyc; /* 288C_(0020 - 0023h) *//* 288C_(0064 - 0067h) */
    IoXchXven xven; /* 288C_(0024 - 0027h) *//* 288C_(0068 - 006Bh) */
    IoXchXhen xhen; /* 288C_(0028 - 002Bh) *//* 288C_(006C - 006Fh) */
    IoXchXshw xshw; /* 288C_(002C - 002Fh) *//* 288C_(0070 - 0073h) */
    IoXchXghw xghw; /* 288C_(0030 - 0033h) *//* 288C_(0074 - 0077h) */
    IoXchXdvw xdvw; /* 288C_(0034 - 0037h) *//* 288C_(0078 - 007Bh) */
    IoXchXdhw xdhw; /* 288C_(0038 - 003Bh) *//* 288C_(007C - 007Fh) */
    IoXchXsa xsa; /* 288C_(003C - 003Fh) *//* 288C_(0080 - 0083h) */
    IoXchXda xda; /* 288C_(0040 - 0043h) *//* 288C_(0084 - 0087h) */
};

/* Define i/o mapping */
struct _IoJdsxch
{
    /* JDSIMG */
    IoXchSr sr; /* 288C_(0000 - 0003h) */
    IoXchXchice xchice; /* 288C_(0004 - 0007h) */
    IoXchXchicf xchicf; /* 288C_(0008 - 000Bh) */
    IoXchXctl xchctl0; /* 288C_(000C - 0043h) */

    IoXchXhistg0 xhistg0; /* 288C_(0044 - 0047h) */

    unsigned char dmy0048004f[0x0050 - 0x0048]; /* 288C_(0048 - 004Fh) */

    IoXchXctl xchctl1; /* 288C_(0050 - 0087h) */

    unsigned char dmy008803ff[0x0400 - 0x0088]; /* 288C_(0088 - 03FFh) */

    IoXchXhbf xhbf[256]; /* 288C_(0400 - 07FFh) */

    unsigned char dmy288c0800288cffff[0x288E0000 - 0x288C0800]; /* 288C_0800 - 288C_FFFFh */

};

extern volatile IoJdsxch ioXch;

KConstType k_jdsxch_get_type(void);
KJdsxch* k_jdsxch_new(void);

#endif/*__K_JDSXCH_H__*/

