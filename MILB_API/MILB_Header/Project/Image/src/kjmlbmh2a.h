/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JMLBMH2A Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_JMLBMH2A_H__
#define __K_JMLBMH2A_H__


#include <klib.h>


#define K_TYPE_JMLBMH2A	            (k_jmlbmh2a_get_type())
#define K_JMLBMH2A(obj)	            (K_TYPE_CHECK_INSTANCE_CAST((obj), KJmlbmh2a))
#define K_IS_JMLBMH2A(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JMLBMH2A))

typedef struct _KJmlbmh2a           KJmlbmh2a;
typedef struct _KJmlbmh2aPrivate    KJmlbmh2aPrivate;

typedef struct _IoBmh IoBmh;

typedef union _IoBmhBmhsr           IoBmhBmhsr;
typedef union _IoBmhBmhtrg          IoBmhBmhtrg;
typedef union _IoBmhBmhre           IoBmhBmhre;
typedef union _IoBmhBmhcont         IoBmhBmhcont;
typedef union _IoBmhBmhintfs        IoBmhBmhintfs;
typedef union _IoBmhBmhinte         IoBmhBmhinte;
typedef union _IoBmhBmhmd           IoBmhBmhmd;
typedef union _IoBmhBmhprm          IoBmhBmhprm;
typedef union _IoBmhBmhhcnt         IoBmhBmhhcnt;
typedef union _IoBmhBmhsadWr        IoBmhBmhsadWr;
typedef union _IoBmhBmhdma          IoBmhBmhdma;
typedef union _IoBmhBmhghsize       IoBmhBmhghsize;
typedef union _IoBmhBmhhsize        IoBmhBmhhsize;
typedef union _IoBmhBmhvsize        IoBmhBmhvsize;
typedef union _IoBmhBmhcurad        IoBmhBmhcurad;
typedef union _IoBmhBmhrefad        IoBmhBmhrefad;
typedef union _IoBmhBmhsadad        IoBmhBmhsadad;
typedef union _IoBmhBmhsadgh        IoBmhBmhsadgh;
typedef union _IoBmhBmhaxictrl      IoBmhBmhaxictrl;
typedef union _IoBmhBmhaxierr       IoBmhBmhaxierr;
typedef union _IoBmhSadr            IoBmhSadr;
typedef union _IoBmhCur             IoBmhCur;
typedef union _IoBmhRef             IoBmhRef;
typedef union _IoBmhLut             IoBmhLut;


struct _KJmlbmh2a
{
    KObject parent;
};


/*  structure of bmhsr  (1D40_0000h/1D48_0000h) */
union _IoBmhBmhsr
{
    kulong word;
    struct
    {
        kulong :31;
        kulong sr :1;
    } bit;
};

/*  structure of bmhtrg (1D40_0004h/1D48_0004h) */
union _IoBmhBmhtrg
{
    kulong word;
    struct
    {
        kulong :30;
        kulong bmhtrg :2;
    } bit;
};

/*  structure of bmhre  (1D40_0008h/1D48_0008h) */
union _IoBmhBmhre
{
    kulong word;
    struct
    {
        kulong bmhre :1;
        kulong :31;
    } bit;
};

/*  structure of bmhcont    (1D40_000Ch/1D48_000Ch) */
union _IoBmhBmhcont
{
    kulong word;
    struct
    {
        kulong :31;
        kulong cont :1;
    } bit;
};

/*  structure of bmhintfs   (1D40_0010h/1D48_0010h) */
union _IoBmhBmhintfs
{
    kulong word;
    struct
    {
        kulong :15;
        kulong rsst :1;
        kulong :7;
        kulong axif :1;
        kulong :7;
        kulong bmhf :1;
    } bit;
};

/*  structure of bmhinte    (1D40_0014h/1D48_0014h) */
union _IoBmhBmhinte
{
    kulong word;
    struct
    {
        kulong :23;
        kulong axie :1;
        kulong :7;
        kulong bmhe :1;
    } bit;
};

/*  structure of bmhmd  (1D40_0018h/1D48_0018h) */
union _IoBmhBmhmd
{
    kulong word;
    struct
    {
        kulong mode :4;
        kulong :4;
        kulong offmd :1;
        kulong :3;
        kulong lutmd :1;
        kulong :3;
        kulong outmd :3;
        kulong :1;
        kulong pshift :3;
        kulong :1;
        kulong rbs :3;
        kulong :1;
        kulong lselcnt :4;
    } bit;
};

/*  structure of bmhprm (1D40_001Ch/1D48_001Ch) */
union _IoBmhBmhprm
{
    kulong word;
    struct
    {
        kulong sadlv :16;
        kulong poffset :8;
        kulong :8;
    } bit;
};

/*  structure of bmhhcnt    (1D40_0020h/1D48_0020h) */
union _IoBmhBmhhcnt
{
    kulong word;
    struct
    {
        kulong rcnt :4;
        kulong :12;
        kulong hcnt :8;
        kulong :8;
    } bit;
};

/*  structure of bmhsadWr  (1D40_0024h/1D48_0024h) */
union _IoBmhBmhsadWr
{
    kulong word;
    struct
    {
        kulong sadWr :5;
        kulong :27;
    } bit;
};

/*  structure of bmhdma (1D40_0030h/1D48_0030h) */
union _IoBmhBmhdma
{
    kulong word;
    struct
    {
        kulong dmamd :1;
        kulong :31;
    } bit;
};

/*  structure of bmhghsize  (1D40_0034h/1D48_0034h) */
union _IoBmhBmhghsize
{
    kulong word;
    struct
    {
        kulong ghsizeRef :16;
        kulong ghsizeCur :16;
    } bit;
};

/*  structure of bmhhsize   (1D40_0038h/1D48_0038h) */
union _IoBmhBmhhsize
{
    kulong word;
    struct
    {
        kulong hsizeRef :16;
        kulong :16;
    } bit;
};

/*  structure of bmhvsize   (1D40_003Ch/1D48_003Ch) */
union _IoBmhBmhvsize
{
    kulong word;
    struct
    {
        kulong vsizeRef :16;
        kulong :16;
    } bit;
};

/*  structure of bmhcurad   (1D40_0040h/1D48_0040h) */
union _IoBmhBmhcurad
{
    kulong word;
    struct
    {
        kulong curstad :32;
    } bit;
};

/*  structure of bmhrefad   (1D40_0044h/1D48_0044h) */
union _IoBmhBmhrefad
{
    kulong word;
    struct
    {
        kulong refstad :32;
    } bit;
};

/*  structure of bmhsadad   (1D40_0048h/1D48_0048h) */
union _IoBmhBmhsadad
{
    kulong word;
    struct
    {
        kulong sadstad :32;
    } bit;
};

/*  structure of bmhsadgh   (1D40_004Ch/1D48_004Ch) */
union _IoBmhBmhsadgh
{
    kulong word;
    struct
    {
        kulong sadghsize :16;
        kulong :16;
    } bit;
};

/*  structure of bmhaxictrl (1D40_0050h/1D48_0050h) */
union _IoBmhBmhaxictrl
{
    kulong word;
    struct
    {
        kulong arcache :4;
        kulong arprot :3;
        kulong :1;
        kulong awcache :4;
        kulong awprot :3;
        kulong :17;
    } bit;
};

/*  structure of bmhaxierr  (1D40_0054h/1D48_0054h) */
union _IoBmhBmhaxierr
{
    kulong word;
    struct
    {
        kulong rresp :2;
        kulong :6;
        kulong wresp :2;
        kulong :22;
    } bit;
};

/*  structure of sadr   (1D40_0800h/1D48_0800h) */
union _IoBmhSadr
{
    kulong word[2][128];
    /* bmhmd.outmd=000b */
    struct
    {
        kulong pos0 :7;
        kulong sadCmp0 :1;
        kulong pos1 :7;
        kulong sadCmp1 :1;
        kulong pos2 :7;
        kulong sadCmp2 :1;
        kulong pos3 :7;
        kulong sadCmp3 :1;
    } bit000[2][57];

    /* bmhmd.outmd=001b */
    kulong word001[225];
    struct
    {
        kulong sadMin :16;
        kulong pos :7;
        kulong sadCmp :1;
        kulong :8;
    } bit001[225];

    /* bmhmd.outmd=010b */
    kulong word010[2][113];
    struct
    {
        kulong posFraction0 :6;
        kulong posInteger0 :7;
        kulong sadCmp0 :1;
        kulong :2;
        kulong posFraction1 :6;
        kulong posInteger1 :7;
        kulong sadCmp1 :1;
        kulong :2;
    } bit010[2][113];

    /* bmhmd.outmd=011b */
    kulong word011[225];
    struct
    {
        kulong sadMin :16;
        kulong posFraction :6;
        kulong posInteger :7;
        kulong sadCmp :1;
        kulong :2;
    } bit011[225];

    /* bmhmd.outmd=100b */
    kulong word100[2][112];
    struct
    {
        kulong sadMin :16;
        kulong posFraction :6;
        kulong posInteger :7;
        kulong sadCmp :1;
        kulong :2;
    } bit100[2][112];

    /* bmhmd.outmd=101b */
    kulong word101[2][56][2];
    struct
    {
        unsigned long long sadMin :16;
        unsigned long long posFraction :6;
        unsigned long long posInteger :7;
        unsigned long long sadCmp :1;
        unsigned long long :2;
        unsigned long long curMin :8;
        unsigned long long curMax :8;
        unsigned long long deviation :8;
        unsigned long long weight :7;
        unsigned long long :1;
    } bit101[2][56];

    /* bmhmd.outmd=110b */
    kulong word110[2][28][4];
    struct
    {
        unsigned long long sadMin :16;
        unsigned long long pos :7;
        unsigned long long sadCmp :1;
        unsigned long long :8;
        unsigned long long sadMin1after :16;
        unsigned long long sadMin1before :16;
        unsigned long long sadMin2after :16;
        unsigned long long sadMin2before :16;
        unsigned long long curMin :8;
        unsigned long long curMax :8;
        unsigned long long deviation :8;
        unsigned long long weight :7;
        unsigned long long :1;
    } bit110[2][28];
};

/*  structure of cur    (1D40_1000h/1D48_1000h) */
union _IoBmhCur
{
    kulong word[9][64];
    struct
    {
        kulong cur0 :8;
        kulong cur1 :8;
        kulong cur2 :8;
        kulong cur3 :8;
    } bit[9][64];
};

/*  structure of ref    (1D40_2000h/1D48_2000h) */
union _IoBmhRef
{
    kulong word[9][64];
    struct
    {
        kulong ref0 :8;
        kulong ref1 :8;
        kulong ref2 :8;
        kulong ref3 :8;
    } bit[9][64];
};

/*  structure of lut    (1D40_3000h/1D48_3000h) */
union _IoBmhLut
{
    kulong word[1024];
    struct
    {
        kulong lut0 :12;
        kulong :4;
        kulong lut1 :12;
        kulong :4;
    } bit[1024];
};

/* Define i/o mapping */
struct _IoBmh
{
    /* JMLBMH2A */
    IoBmhBmhsr bmhsr; /* 1D40/1D48_(0000 - 0003h) */
    IoBmhBmhtrg bmhtrg; /* 1D40/1D48_(0004 - 0007h) */
    IoBmhBmhre bmhre; /* 1D40/1D48_(0008 - 000Bh) */
    IoBmhBmhcont bmhcont; /* 1D40/1D48_(000C - 000Fh) */
    IoBmhBmhintfs bmhintfs; /* 1D40/1D48_(0010 - 0013h) */
    IoBmhBmhinte bmhinte; /* 1D40/1D48_(0014 - 0017h) */
    IoBmhBmhmd bmhmd; /* 1D40/1D48_(0018 - 001Bh) */
    IoBmhBmhprm bmhprm; /* 1D40/1D48_(001C - 001Fh) */
    IoBmhBmhhcnt bmhhcnt; /* 1D40/1D48_(0020 - 0023h) */
    IoBmhBmhsadWr bmhsadWr; /* 1D40/1D48_(0024 - 0027h) */

    kuchar dmy0028002f[0x0030 - 0x0028]; /* 1D40/1D48_(0028 - 002Fh) */

    IoBmhBmhdma bmhdma; /* 1D40/1D48_(0030 - 0033h) */
    IoBmhBmhghsize bmhghsize; /* 1D40/1D48_(0034 - 0037h) */
    IoBmhBmhhsize bmhhsize; /* 1D40/1D48_(0038 - 003Bh) */
    IoBmhBmhvsize bmhvsize; /* 1D40/1D48_(003C - 003Fh) */
    IoBmhBmhcurad bmhcurad; /* 1D40/1D48_(0040 - 0043h) */
    IoBmhBmhrefad bmhrefad; /* 1D40/1D48_(0044 - 0047h) */
    IoBmhBmhsadad bmhsadad; /* 1D40/1D48_(0048 - 004Bh) */
    IoBmhBmhsadgh bmhsadgh; /* 1D40/1D48_(004C - 004Fh) */
    IoBmhBmhaxictrl bmhaxictrl; /* 1D40/1D48_(0050 - 0053h) */
    IoBmhBmhaxierr bmhaxierr; /* 1D40/1D48_(0054 - 0057h) */

    kuchar dmy005807ff[0x0800 - 0x0058]; /* 1D40/1D48_(0058 - 07FFh) */

    IoBmhSadr sadr; /* 1D40/1D48_(0800 - 0BFFh) */

    kuchar dmy0c000fff[0x1000 - 0x0C00]; /* 1D40/1D48_(0C00 - 0FFFh) */

    IoBmhCur cur; /* 1D40/1D48_(1000 - 18FFh) */

    kuchar dmy19001fff[0x2000 - 0x1900]; /* 1D40/1D48_(1900 - 1FFFh) */

    IoBmhRef ref; /* 1D40/1D48_(2000 - 28FFh) */

    kuchar dmy29002fff[0x3000 - 0x2900]; /* 1D40/1D48_(2900 - 2FFFh) */

    IoBmhLut lut; /* 1D40/1D48_(3000 - 3FFFh) */

    kuchar dmy1d4040001d47ffff[0x1D480000 - 0x1D404000]; /* 1D40/1D48_4000 - 1D47_FFFFh */

};


extern volatile IoBmh ioBmh[2];


KConstType k_jmlbmh2a_get_type(void);
KJmlbmh2a* k_jmlbmh2a_new(void);


#endif/*__K_JMLBMH2A_H__*/
