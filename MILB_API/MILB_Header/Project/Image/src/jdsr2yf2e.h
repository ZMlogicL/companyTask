/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSR2Y_F2E Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __JDSR2Y_F2E_H__
#define __JDSR2Y_F2E_H__


#include <klib.h>
#include "__fr2y6a.h"
#include "__jdsr2y_f2e_sram.h"
#include "jdsr2yf2e3.h"
#include "jdsr2yf2e2.h"


#define JDSR2Y_TYPE_F2E	(jdsr2y_f2e_get_type())
#define JDSR2Y_F2E(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), Jdsr2yF2e))
#define JDSR2Y_IS_F2E(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSR2Y_TYPE_F2E))


typedef struct _Jdsr2yF2e           Jdsr2yF2e;
typedef struct _Jdsr2yF2ePrivate    Jdsr2yF2ePrivate;

typedef struct _IoR2yYych           IoR2yYych;
typedef struct _IoR2yCmn            IoR2yCmn;
typedef struct _IoR2yYyr            IoR2yYyr;
typedef struct _IoR2yYyw            IoR2yYyw;
typedef struct _IoR2y               IoR2y;

typedef union _IoR2yEe0clpmof       IoR2yEe0clpmof;
typedef union _IoR2yEe0clpmga       IoR2yEe0clpmga;
typedef union _IoR2yEe0clpmbd       IoR2yEe0clpmbd;
typedef union _IoR2yEe1ctl          IoR2yEe1ctl;
typedef union _IoR2yEe1hpfk         IoR2yEe1hpfk;
typedef union _IoR2yEe1nrlv         IoR2yEe1nrlv;
typedef union _IoR2yEe1corpof       IoR2yEe1corpof;
typedef union _IoR2yEe1corpga       IoR2yEe1corpga;
typedef union _IoR2yEe1corpbd       IoR2yEe1corpbd;
typedef union _IoR2yEe1cormof       IoR2yEe1cormof;
typedef union _IoR2yEe1cormga       IoR2yEe1cormga;
typedef union _IoR2yEe1cormbd       IoR2yEe1cormbd;
typedef union _IoR2yEe1sclsup       IoR2yEe1sclsup;
typedef union _IoR2yEe1sclpof       IoR2yEe1sclpof;
typedef union _IoR2yEe1sclpga       IoR2yEe1sclpga;
typedef union _IoR2yEe1sclpbd       IoR2yEe1sclpbd;
typedef union _IoR2yEe1sclmof       IoR2yEe1sclmof;
typedef union _IoR2yEe1sclmga       IoR2yEe1sclmga;
typedef union _IoR2yEe1sclmbd       IoR2yEe1sclmbd;
typedef union _IoR2yEe1tonpof       IoR2yEe1tonpof;
typedef union _IoR2yEe1tonpga       IoR2yEe1tonpga;
typedef union _IoR2yEe1tonpbd       IoR2yEe1tonpbd;
typedef union _IoR2yEe1tonmof       IoR2yEe1tonmof;
typedef union _IoR2yEe1tonmga       IoR2yEe1tonmga;
typedef union _IoR2yEe1tonmbd       IoR2yEe1tonmbd;
typedef union _IoR2yEe1clppof       IoR2yEe1clppof;
typedef union _IoR2yEe1clppga       IoR2yEe1clppga;
typedef union _IoR2yEe1clppbd       IoR2yEe1clppbd;
typedef union _IoR2yEe1clpmof       IoR2yEe1clpmof;
typedef union _IoR2yEe1clpmga       IoR2yEe1clpmga;
typedef union _IoR2yEe1clpmbd       IoR2yEe1clpmbd;


struct _Jdsr2yF2e
{
    KObject parent;
};


/*  structure of ee0clpmof  (2841_C500h)    */
union _IoR2yEe0clpmof
{
    kulong word;
    struct
    {
        kulong ee0clpmof0 :7;
        kulong :1;
        kulong ee0clpmof1 :7;
        kulong :1;
        kulong ee0clpmof2 :7;
        kulong :9;
    } bit;
};

/*  structure of ee0clpmga  (2841_C504h)    */
union _IoR2yEe0clpmga
{
    kulong word;
    struct
    {
        klong ee0clpmga0 :8;
        klong ee0clpmga1 :8;
        klong ee0clpmga2 :8;
        kulong :8;
    } bit;
};

/*  structure of ee0clpmbd  (2841_C508h)    */
union _IoR2yEe0clpmbd
{
    kulong word;
    struct
    {
        kulong ee0clpmbd1 :8;
        kulong ee0clpmbd2 :8;
        kulong :16;
    } bit;
};

/*  structure of ee1ctl (2841_C600h)    */
union _IoR2yEe1ctl
{
    kulong word;
    struct
    {
        kulong ee1en :1;
        kulong :3;
        kulong ee1tc :1;
        kulong :27;
    } bit;
};

/*  structure of ee1hpfk    (2841_C608h)    */
union _IoR2yEe1hpfk
{
    kulong word[2];
    struct
    {
        kulong ee1hpfk0 :10;
        kulong :6;
        klong ee1hpfk1 :8;
        klong ee1hpfk2 :8;
        klong ee1hpfk3 :8;
        klong ee1hpfk4 :8;
        klong ee1hpfk5 :8;
        kulong :8;
    } bit;
};

/*  structure of ee1nrlv    (2841_C610h)    */
union _IoR2yEe1nrlv
{
    kulong word;
    struct
    {
        kulong ee1nrlv :4;
        kulong :28;
    } bit;
};

/*  structure of ee1corpof  (2841_C618h)    */
union _IoR2yEe1corpof
{
    kulong word[2];
    struct
    {
        kulong ee1corpof0 :10;
        kulong :6;
        kulong ee1corpof1 :10;
        kulong :6;
        kulong ee1corpof2 :10;
        kulong :6;
        kulong ee1corpof3 :10;
        kulong :6;
    } bit;
};

/*  structure of ee1corpga  (2841_C620h)    */
union _IoR2yEe1corpga
{
    kulong word;
    struct
    {
        klong ee1corpga0 :8;
        klong ee1corpga1 :8;
        klong ee1corpga2 :8;
        klong ee1corpga3 :8;
    } bit;
};

/*  structure of ee1corpbd  (2841_C628h)    */
union _IoR2yEe1corpbd
{
    kulong word[2];
    struct
    {
        kulong ee1corpbd1 :10;
        kulong :6;
        kulong ee1corpbd2 :10;
        kulong :6;
        kulong ee1corpbd3 :10;
        kulong :22;
    } bit;
};

/*  structure of ee1cormof  (2841_C630h)    */
union _IoR2yEe1cormof
{
    kulong word[2];
    struct
    {
        kulong ee1cormof0 :10;
        kulong :6;
        kulong ee1cormof1 :10;
        kulong :6;
        kulong ee1cormof2 :10;
        kulong :6;
        kulong ee1cormof3 :10;
        kulong :6;
    } bit;
};

/*  structure of ee1cormga  (2841_C638h)    */
union _IoR2yEe1cormga
{
    kulong word;
    struct
    {
        klong ee1cormga0 :8;
        klong ee1cormga1 :8;
        klong ee1cormga2 :8;
        klong ee1cormga3 :8;
    } bit;
};

/*  structure of ee1cormbd  (2841_C640h)    */
union _IoR2yEe1cormbd
{
    kulong word[2];
    struct
    {
        kulong ee1cormbd1 :10;
        kulong :6;
        kulong ee1cormbd2 :10;
        kulong :6;
        kulong ee1cormbd3 :10;
        kulong :22;
    } bit;
};

/*  structure of ee1sclsup  (2841_C648h)    */
union _IoR2yEe1sclsup
{
    kulong word;
    struct
    {
        kulong ee1sclsup :6;
        kulong :26;
    } bit;
};

/*  structure of ee1sclpof  (2841_C650h)    */
union _IoR2yEe1sclpof
{
    kulong word[3];
    struct
    {
        kulong ee1sclpof0 :8;
        kulong ee1sclpof1 :8;
        kulong ee1sclpof2 :8;
        kulong ee1sclpof3 :8;
        kulong ee1sclpof4 :8;
        kulong ee1sclpof5 :8;
        kulong ee1sclpof6 :8;
        kulong ee1sclpof7 :8;
        kulong ee1sclpof8 :8;
        kulong ee1sclpof9 :8;
        kulong :16;
    } bit;
};

/*  structure of ee1sclpga  (2841_C660h)    */
union _IoR2yEe1sclpga
{
    kulong word[5];
    struct
    {
        klong ee1sclpga0 :13;
        kulong :3;
        klong ee1sclpga1 :13;
        kulong :3;
        klong ee1sclpga2 :13;
        kulong :3;
        klong ee1sclpga3 :13;
        kulong :3;
        klong ee1sclpga4 :13;
        kulong :3;
        klong ee1sclpga5 :13;
        kulong :3;
        klong ee1sclpga6 :13;
        kulong :3;
        klong ee1sclpga7 :13;
        kulong :3;
        klong ee1sclpga8 :13;
        kulong :3;
        klong ee1sclpga9 :13;
        kulong :3;
    } bit;
};

/*  structure of ee1sclpbd  (2841_C680h)    */
union _IoR2yEe1sclpbd
{
    kulong word[5];
    struct
    {
        kulong ee1sclpbd1 :10;
        kulong :6;
        kulong ee1sclpbd2 :10;
        kulong :6;
        kulong ee1sclpbd3 :10;
        kulong :6;
        kulong ee1sclpbd4 :10;
        kulong :6;
        kulong ee1sclpbd5 :10;
        kulong :6;
        kulong ee1sclpbd6 :10;
        kulong :6;
        kulong ee1sclpbd7 :10;
        kulong :6;
        kulong ee1sclpbd8 :10;
        kulong :6;
        kulong ee1sclpbd9 :10;
        kulong :22;
    } bit;
};

/*  structure of ee1sclmof  (2841_C6A0h)    */
union _IoR2yEe1sclmof
{
    kulong word[3];
    struct
    {
        kulong ee1sclmof0 :8;
        kulong ee1sclmof1 :8;
        kulong ee1sclmof2 :8;
        kulong ee1sclmof3 :8;
        kulong ee1sclmof4 :8;
        kulong ee1sclmof5 :8;
        kulong ee1sclmof6 :8;
        kulong ee1sclmof7 :8;
        kulong ee1sclmof8 :8;
        kulong ee1sclmof9 :8;
        kulong :16;
    } bit;
};

/*  structure of ee1sclmga  (2841_C6C0h)    */
union _IoR2yEe1sclmga
{
    kulong word[5];
    struct
    {
        klong ee1sclmga0 :13;
        kulong :3;
        klong ee1sclmga1 :13;
        kulong :3;
        klong ee1sclmga2 :13;
        kulong :3;
        klong ee1sclmga3 :13;
        kulong :3;
        klong ee1sclmga4 :13;
        kulong :3;
        klong ee1sclmga5 :13;
        kulong :3;
        klong ee1sclmga6 :13;
        kulong :3;
        klong ee1sclmga7 :13;
        kulong :3;
        klong ee1sclmga8 :13;
        kulong :3;
        klong ee1sclmga9 :13;
        kulong :3;
    } bit;
};

/*  structure of ee1sclmbd  (2841_C6E0h)    */
union _IoR2yEe1sclmbd
{
    kulong word[5];
    struct
    {
        kulong ee1sclmbd1 :10;
        kulong :6;
        kulong ee1sclmbd2 :10;
        kulong :6;
        kulong ee1sclmbd3 :10;
        kulong :6;
        kulong ee1sclmbd4 :10;
        kulong :6;
        kulong ee1sclmbd5 :10;
        kulong :6;
        kulong ee1sclmbd6 :10;
        kulong :6;
        kulong ee1sclmbd7 :10;
        kulong :6;
        kulong ee1sclmbd8 :10;
        kulong :6;
        kulong ee1sclmbd9 :10;
        kulong :22;
    } bit;
};

/*  structure of ee1tonpof  (2841_C700h)    */
union _IoR2yEe1tonpof
{
    kulong word[3];
    struct
    {
        kulong ee1tonpof0 :9;
        kulong :7;
        kulong ee1tonpof1 :9;
        kulong :7;
        kulong ee1tonpof2 :9;
        kulong :7;
        kulong ee1tonpof3 :9;
        kulong :7;
        kulong ee1tonpof4 :9;
        kulong :23;
    } bit;
};

/*  structure of ee1tonpga  (2841_C710h)    */
union _IoR2yEe1tonpga
{
    kulong word[3];
    struct
    {
        klong ee1tonpga0 :9;
        kulong :7;
        klong ee1tonpga1 :9;
        kulong :7;
        klong ee1tonpga2 :9;
        kulong :7;
        klong ee1tonpga3 :9;
        kulong :7;
        klong ee1tonpga4 :9;
        kulong :23;
    } bit;
};

/*  structure of ee1tonpbd  (2841_C720h)    */
union _IoR2yEe1tonpbd
{
    kulong word[2];
    struct
    {
        kulong ee1tonpbd1 :9;
        kulong :7;
        kulong ee1tonpbd2 :9;
        kulong :7;
        kulong ee1tonpbd3 :9;
        kulong :7;
        kulong ee1tonpbd4 :9;
        kulong :7;
    } bit;
};

/*  structure of ee1tonmof  (2841_C730h)    */
union _IoR2yEe1tonmof
{
    kulong word[3];
    struct
    {
        kulong ee1tonmof0 :9;
        kulong :7;
        kulong ee1tonmof1 :9;
        kulong :7;
        kulong ee1tonmof2 :9;
        kulong :7;
        kulong ee1tonmof3 :9;
        kulong :7;
        kulong ee1tonmof4 :9;
        kulong :23;
    } bit;
};

/*  structure of ee1tonmga  (2841_C740h)    */
union _IoR2yEe1tonmga
{
    kulong word[3];
    struct
    {
        klong ee1tonmga0 :9;
        kulong :7;
        klong ee1tonmga1 :9;
        kulong :7;
        klong ee1tonmga2 :9;
        kulong :7;
        klong ee1tonmga3 :9;
        kulong :7;
        klong ee1tonmga4 :9;
        kulong :23;
    } bit;
};

/*  structure of ee1tonmbd  (2841_C750h)    */
union _IoR2yEe1tonmbd
{
    kulong word[2];
    struct
    {
        kulong ee1tonmbd1 :9;
        kulong :7;
        kulong ee1tonmbd2 :9;
        kulong :7;
        kulong ee1tonmbd3 :9;
        kulong :7;
        kulong ee1tonmbd4 :9;
        kulong :7;
    } bit;
};

/*  structure of ee1clppof  (2841_C758h)    */
union _IoR2yEe1clppof
{
    kulong word[2];
    struct
    {
        kulong ee1clppof0 :9;
        kulong :7;
        kulong ee1clppof1 :9;
        kulong :7;
        kulong ee1clppof2 :9;
        kulong :23;
    } bit;
};

/*  structure of ee1clppga  (2841_C760h)    */
union _IoR2yEe1clppga
{
    kulong word;
    struct
    {
        klong ee1clppga0 :8;
        klong ee1clppga1 :8;
        klong ee1clppga2 :8;
        kulong :8;
    } bit;
};

/*  structure of ee1clppbd  (2841_C764h)    */
union _IoR2yEe1clppbd
{
    kulong word;
    struct
    {
        kulong ee1clppbd1 :10;
        kulong :6;
        kulong ee1clppbd2 :10;
        kulong :6;
    } bit;
};

/*  structure of ee1clpmof  (2841_C768h)    */
union _IoR2yEe1clpmof
{
    kulong word[2];
    struct
    {
        kulong ee1clpmof0 :9;
        kulong :7;
        kulong ee1clpmof1 :9;
        kulong :7;
        kulong ee1clpmof2 :9;
        kulong :23;
    } bit;
};

/*  structure of ee1clpmga  (2841_C770h)    */
union _IoR2yEe1clpmga
{
    kulong word;
    struct
    {
        klong ee1clpmga0 :8;
        klong ee1clpmga1 :8;
        klong ee1clpmga2 :8;
        kulong :8;
    } bit;
};

/*  structure of ee1clpmbd  (2841_C774h)    */
union _IoR2yEe1clpmbd
{
    kulong word;
    struct
    {
        kulong ee1clpmbd1 :10;
        kulong :6;
        kulong ee1clpmbd2 :10;
        kulong :6;
    } bit;
};


/*  structure of yych area  2841_(C000 - C07Fh) */
struct _IoR2yYych
{
    IoR2yYyraxctl yyraxctl; /* 2841_(C000 - C003h) */
    IoR2yYyw0axctl yyw0axctl; /* 2841_(C004 - C007h) */
    IoR2yYywaaxctl yywaaxctl; /* 2841_(C008 - C00Bh) */
    IoR2yYyw1axctl yyw1axctl; /* 2841_(C00C - C00Fh) */
    IoR2yYyw2axctl yyw2axctl; /* 2841_(C010 - C013h) */
    IoR2yYyraxsts yyraxsts; /* 2841_(C014 - C017h) */
    IoR2yYyw0axsts yyw0axsts; /* 2841_(C018 - C01Bh) */
    IoR2yYywaaxsts yywaaxsts; /* 2841_(C01C - C01Fh) */
    IoR2yYyw1axsts yyw1axsts; /* 2841_(C020 - C023h) */
    IoR2yYyw2axsts yyw2axsts; /* 2841_(C024 - C027h) */
    IoR2yYyraxmd yyraxmd; /* 2841_(C028 - C02Bh) */
    IoR2yYyw0axmd yyw0axmd; /* 2841_(C02C - C02Fh) */
    IoR2yYywaaxmd yywaaxmd; /* 2841_(C030 - C033h) */
    IoR2yYyw1axmd yyw1axmd; /* 2841_(C034 - C037h) */
    IoR2yYyw2axmd yyw2axmd; /* 2841_(C038 - C03Bh) */

    kuchar dmyC03cC03f[0xC040 - 0xC03C]; /* 2841_(C03C - C03Fh) */

    IoR2yYyrreqmsk yyrreqmsk; /* 2841_(C040 - C047h) */
    IoR2yYyw0reqmsk yyw0reqmsk; /* 2841_(C048 - C04Fh) */
    IoR2yYywareqmsk yywareqmsk; /* 2841_(C050 - C053h) */

    kuchar dmyC054C057[0xC058 - 0xC054]; /* 2841_(C054 - C057h) */

    IoR2yYyw1reqmsk yyw1reqmsk; /* 2841_(C058 - C05Fh) */
    IoR2yYyw2reqmsk yyw2reqmsk; /* 2841_(C060 - C063h) */

    kuchar dmyC064C07f[0xC080 - 0xC064]; /* 2841_(C064 - C07Fh) */
};

/*  structure of R2Y COMMON area    2841_(C080 - C0BFh) */
struct _IoR2yCmn
{
    IoR2yYyinte yyinte; /* 2841_(C080 - C083h) */
    IoR2yYyintf yyintf; /* 2841_(C084 - C087h) */
    IoR2yLintlv lintlv; /* 2841_(C088 - C08Fh) */
    IoR2yLintsel lintsel; /* 2841_(C090 - C093h) */
    IoR2yR2ymode r2ymode; /* 2841_(C094 - C097h) */
    IoR2yRamaen ramaen; /* 2841_(C098 - C09Bh) */

    kuchar dmyC09cC0bf[0xC0C0 - 0xC09C]; /* 2841_(C09C - C0BFh) */
};

/*  structure of yyr area   2841_(C0C0 - C0FFh) */
struct _IoR2yYyr
{
    IoR2yYyrtrg yyrtrg; /* 2841_(C0C0 - C0C3h) */
    IoR2yYyrctl yyrctl; /* 2841_(C0C4 - C0C7h) */
    IoR2yDinctl dinctl; /* 2841_(C0C8 - C0CBh) */

    kuchar dmyC0ccC0cf[0xC0D0 - 0xC0CC]; /* 2841_(C0CC - C0CFh) */

    IoR2yYyra yyra; /* 2841_(C0D0 - C0DBh) */

    kuchar dmyC0dcC0df[0xC0E0 - 0xC0DC]; /* 2841_(C0DC - C0DFh) */

    IoR2yYyrofs yyrofs; /* 2841_(C0E0 - C0E3h) */
    IoR2yYyrdef yyrdef; /* 2841_(C0E4 - C0E7h) */
    IoR2yYyrhsiz yyrhsiz; /* 2841_(C0E8 - C0EBh) */
    IoR2yYyrvsiz yyrvsiz; /* 2841_(C0EC - C0EFh) */

    kuchar dmyC0f0C0ff[0xC100 - 0xC0F0]; /* 2841_(C0F0 - C0FFh) */
};

/*  structure of yyw area   2841_(C100 - FFFFh) */
struct _IoR2yYyw
{
    IoR2yYywtrg yywtrg; /* 2841_(C100 - C103h) */
    IoR2yYywctl yywctl; /* 2841_(C104 - C107h) */
    IoR2yYywbank yywbank; /* 2841_(C108 - C10Bh) */
    IoR2yYywkpp yywkpp; /* 2841_(C10C - C10Fh) */
    IoR2yYyw0md yyw0md; /* 2841_(C110 - C113h) */
    IoR2yYyw1md yyw1md; /* 2841_(C114 - C117h) */
    IoR2yYyw2md yyw2md; /* 2841_(C118 - C11Bh) */

    kuchar dmyC11cC11f[0xC120 - 0xC11C]; /* 2841_(C11C - C11Fh) */

    IoR2yHstmd hstmd; /* 2841_(C120 - C123h) */
    IoR2yHsth hsth; /* 2841_(C124 - C127h) */
    IoR2yHstv hstv; /* 2841_(C128 - C12Bh) */

    kuchar dmyC12cC1ff[0xC200 - 0xC12C]; /* 2841_(C12C - C1FFh) */

    IoR2yYyw0a yyw0a; /* 2841_(C200 - C22Fh) */

    kuchar dmyC230C23f[0xC240 - 0xC230]; /* 2841_(C230 - C23Fh) */

    IoR2yYyw0def yyw0def; /* 2841_(C240 - C247h) */
    IoR2yYyw0ofsx yyw0ofsx; /* 2841_(C248 - C24Fh) */

    kuchar dmyC250C257[0xC258 - 0xC250]; /* 2841_(C250 - C257h) */

    IoR2yRsz0hsta rsz0hsta; /* 2841_(C258 - C25Bh) */
    IoR2yRsz0hpit rsz0hpit; /* 2841_(C25C - C25Fh) */
    IoR2yRsz0vsta rsz0vsta; /* 2841_(C260 - C263h) */
    IoR2yRsz0vpit rsz0vpit; /* 2841_(C264 - C267h) */
    IoR2yPcemd pcemd; /* 2841_(C268 - C26Bh) */
    IoR2yPcexy pcexy; /* 2841_(C26C - C26Fh) */
    IoR2yPcec pcec; /* 2841_(C270 - C273h) */
    IoR2yPceh pceh; /* 2841_(C274 - C277h) */
    IoR2yTrm0h trm0h; /* 2841_(C278 - C27Bh) */
    IoR2yTrm0v trm0v; /* 2841_(C27C - C27Fh) */
    IoR2yTrmbh trmbh; /* 2841_(C280 - C283h) */
    IoR2yTrmbv trmbv; /* 2841_(C284 - C287h) */
    IoR2yTrmch trmch; /* 2841_(C288 - C28Bh) */
    IoR2yTrmcv trmcv; /* 2841_(C28C - C28Fh) */
    IoR2yYyw0ltt yyw0ltt; /* 2841_(C290 - C293h) */

    kuchar dmyC294C29f[0xC2A0 - 0xC294]; /* 2841_(C294 - C29Fh) */

    IoR2yYywaa yywaa; /* 2841_(C2A0 - C2BFh) */
    IoR2yYywadef yywadef; /* 2841_(C2C0 - C2C3h) */

    kuchar dmyC2c4C2c7[0xC2C8 - 0xC2C4]; /* 2841_(C2C4 - C2C7h) */

    IoR2yYywaofsx yywaofsx; /* 2841_(C2C8 - C2CFh) */

    kuchar dmyC2d0C2ff[0xC300 - 0xC2D0]; /* 2841_(C2D0 - C2FFh) */

    IoR2yYyw1a yyw1a; /* 2841_(C300 - C32Fh) */

    kuchar dmyC330C33f[0xC340 - 0xC330]; /* 2841_(C330 - C33Fh) */

    IoR2yYyw1def yyw1def; /* 2841_(C340 - C347h) */
    IoR2yRsz1hsta rsz1hsta; /* 2841_(C348 - C34Bh) */
    IoR2yRsz1hpit rsz1hpit; /* 2841_(C34C - C34Fh) */
    IoR2yRsz1vsta rsz1vsta; /* 2841_(C350 - C353h) */
    IoR2yRsz1vpit rsz1vpit; /* 2841_(C354 - C357h) */
    IoR2yTrm1h trm1h; /* 2841_(C358 - C35Bh) */
    IoR2yTrm1v trm1v; /* 2841_(C35C - C35Fh) */

    kuchar dmyC360C37f[0xC380 - 0xC360]; /* 2841_(C360 - C37Fh) */

    IoR2yYyw2a yyw2a; /* 2841_(C380 - C38Fh) */
    IoR2yYyw2def yyw2def; /* 2841_(C390 - C393h) */
    IoR2yRsz2hsta rsz2hsta; /* 2841_(C394 - C397h) */
    IoR2yRsz2hpit rsz2hpit; /* 2841_(C398 - C39Bh) */
    IoR2yRsz2vsta rsz2vsta; /* 2841_(C39C - C39Fh) */
    IoR2yRsz2vpit rsz2vpit; /* 2841_(C3A0 - C3A3h) */
    IoR2yTrm2h trm2h; /* 2841_(C3A4 - C3A7h) */
    IoR2yTrm2v trm2v; /* 2841_(C3A8 - C3ABh) */

    kuchar dmyC3acC3ff[0xC400 - 0xC3AC]; /* 2841_(C3AC - C3FFh) */

    IoR2yEe0ctl ee0ctl; /* 2841_(C400 - C403h) */

    kuchar dmyC404C407[0xC408 - 0xC404]; /* 2841_(C404 - C407h) */

    IoR2yEe0hpfk ee0hpfk; /* 2841_(C408 - C40Fh) */
    IoR2yEe0nrlv ee0nrlv; /* 2841_(C410 - C413h) */
    IoR2yEe0corpof ee0corpof; /* 2841_(C414 - C417h) */
    IoR2yEe0corpga ee0corpga; /* 2841_(C418 - C41Bh) */
    IoR2yEe0corpbd ee0corpbd; /* 2841_(C41C - C41Fh) */
    IoR2yEe0cormof ee0cormof; /* 2841_(C420 - C423h) */
    IoR2yEe0cormga ee0cormga; /* 2841_(C424 - C427h) */
    IoR2yEe0cormbd ee0cormbd; /* 2841_(C428 - C42Bh) */
    IoR2yEe0sclsup ee0sclsup; /* 2841_(C42C - C42Fh) */
    IoR2yEe0sclpof ee0sclpof; /* 2841_(C430 - C43Bh) */

    kuchar dmyC43cC43f[0xC440 - 0xC43C]; /* 2841_(C43C - C43Fh) */

    IoR2yEe0sclpga ee0sclpga; /* 2841_(C440 - C453h) */

    kuchar dmyC454C45f[0xC460 - 0xC454]; /* 2841_(C454 - C45Fh) */

    IoR2yEe0sclpbd ee0sclpbd; /* 2841_(C460 - C46Bh) */

    kuchar dmyC46cC46f[0xC470 - 0xC46C]; /* 2841_(C46C - C46Fh) */

    IoR2yEe0sclmof ee0sclmof; /* 2841_(C470 - C47Bh) */

    kuchar dmyC47cC47f[0xC480 - 0xC47C]; /* 2841_(C47C - C47Fh) */

    IoR2yEe0sclmga ee0sclmga; /* 2841_(C480 - C493h) */

    kuchar dmyC494C49f[0xC4A0 - 0xC494]; /* 2841_(C494 - C49Fh) */

    IoR2yEe0sclmbd ee0sclmbd; /* 2841_(C4A0 - C4ABh) */

    kuchar dmyC4acC4af[0xC4B0 - 0xC4AC]; /* 2841_(C4AC - C4AFh) */

    IoR2yEe0tonpof ee0tonpof; /* 2841_(C4B0 - C4B7h) */

    kuchar dmyC4b8C4bf[0xC4C0 - 0xC4B8]; /* 2841_(C4B8 - C4BFh) */

    IoR2yEe0tonpga ee0tonpga; /* 2841_(C4C0 - C4CBh) */

    kuchar dmyC4ccC4cf[0xC4D0 - 0xC4CC]; /* 2841_(C4CC - C4CFh) */

    IoR2yEe0tonpbd ee0tonpbd; /* 2841_(C4D0 - C4D3h) */

    kuchar dmyC4d4C4d7[0xC4D8 - 0xC4D4]; /* 2841_(C4D4 - C4D7h) */

    IoR2yEe0tonmof ee0tonmof; /* 2841_(C4D8 - C4DFh) */
    IoR2yEe0tonmga ee0tonmga; /* 2841_(C4E0 - C4EBh) */

    kuchar dmyC4ecC4ef[0xC4F0 - 0xC4EC]; /* 2841_(C4EC - C4EFh) */

    IoR2yEe0tonmbd ee0tonmbd; /* 2841_(C4F0 - C4F3h) */
    IoR2yEe0clppof ee0clppof; /* 2841_(C4F4 - C4F7h) */
    IoR2yEe0clppga ee0clppga; /* 2841_(C4F8 - C4FBh) */
    IoR2yEe0clppbd ee0clppbd; /* 2841_(C4FC - C4FFh) */
    IoR2yEe0clpmof ee0clpmof; /* 2841_(C500 - C503h) */
    IoR2yEe0clpmga ee0clpmga; /* 2841_(C504 - C507h) */
    IoR2yEe0clpmbd ee0clpmbd; /* 2841_(C508 - C50Bh) */

    kuchar dmyC50cC5ff[0xC600 - 0xC50C]; /* 2841_(C50C - C5FFh) */

    IoR2yEe1ctl ee1ctl; /* 2841_(C600 - C603h) */

    kuchar dmyC604C607[0xC608 - 0xC604]; /* 2841_(C604 - C607h) */

    IoR2yEe1hpfk ee1hpfk; /* 2841_(C608 - C60Fh) */
    IoR2yEe1nrlv ee1nrlv; /* 2841_(C610 - C613h) */

    kuchar dmyC614C617[0xC618 - 0xC614]; /* 2841_(C614 - C617h) */

    IoR2yEe1corpof ee1corpof; /* 2841_(C618 - C61Fh) */
    IoR2yEe1corpga ee1corpga; /* 2841_(C620 - C623h) */

    kuchar dmyC624C627[0xC628 - 0xC624]; /* 2841_(C624 - C627h) */

    IoR2yEe1corpbd ee1corpbd; /* 2841_(C628 - C62Fh) */
    IoR2yEe1cormof ee1cormof; /* 2841_(C630 - C637h) */
    IoR2yEe1cormga ee1cormga; /* 2841_(C638 - C63Bh) */

    kuchar dmyC63cC63f[0xC640 - 0xC63C]; /* 2841_(C63C - C63Fh) */

    IoR2yEe1cormbd ee1cormbd; /* 2841_(C640 - C647h) */
    IoR2yEe1sclsup ee1sclsup; /* 2841_(C648 - C64Bh) */

    kuchar dmyC64cC64f[0xC650 - 0xC64C]; /* 2841_(C64C - C64Fh) */

    IoR2yEe1sclpof ee1sclpof; /* 2841_(C650 - C65Bh) */

    kuchar dmyC65cC65f[0xC660 - 0xC65C]; /* 2841_(C65C - C65Fh) */

    IoR2yEe1sclpga ee1sclpga; /* 2841_(C660 - C673h) */

    kuchar dmyC674C67f[0xC680 - 0xC674]; /* 2841_(C674 - C67Fh) */

    IoR2yEe1sclpbd ee1sclpbd; /* 2841_(C680 - C693h) */

    kuchar dmyC694C69f[0xC6A0 - 0xC694]; /* 2841_(C694 - C69Fh) */

    IoR2yEe1sclmof ee1sclmof; /* 2841_(C6A0 - C6ABh) */

    kuchar dmyC6acC6bf[0xC6C0 - 0xC6AC]; /* 2841_(C6AC - C6BFh) */

    IoR2yEe1sclmga ee1sclmga; /* 2841_(C6C0 - C6D3h) */

    kuchar dmyC6d4C6df[0xC6E0 - 0xC6D4]; /* 2841_(C6D4 - C6DFh) */

    IoR2yEe1sclmbd ee1sclmbd; /* 2841_(C6E0 - C6F3h) */

    kuchar dmyC6f4C6ff[0xC700 - 0xC6F4]; /* 2841_(C6F4 - C6FFh) */

    IoR2yEe1tonpof ee1tonpof; /* 2841_(C700 - C70Bh) */

    kuchar dmyC70cC70f[0xC710 - 0xC70C]; /* 2841_(C70C - C70Fh) */

    IoR2yEe1tonpga ee1tonpga; /* 2841_(C710 - C71Bh) */

    kuchar dmyC71cC71f[0xC720 - 0xC71C]; /* 2841_(C71C - C71Fh) */

    IoR2yEe1tonpbd ee1tonpbd; /* 2841_(C720 - C727h) */

    kuchar dmyC728C72f[0xC730 - 0xC728]; /* 2841_(C728 - C72Fh) */

    IoR2yEe1tonmof ee1tonmof; /* 2841_(C730 - C73Bh) */

    kuchar dmyC73cC73f[0xC740 - 0xC73C]; /* 2841_(C73C - C73Fh) */

    IoR2yEe1tonmga ee1tonmga; /* 2841_(C740 - C74Bh) */

    kuchar dmyC74cC74f[0xC750 - 0xC74C]; /* 2841_(C74C - C74Fh) */

    IoR2yEe1tonmbd ee1tonmbd; /* 2841_(C750 - C757h) */
    IoR2yEe1clppof ee1clppof; /* 2841_(C758 - C75Fh) */
    IoR2yEe1clppga ee1clppga; /* 2841_(C760 - C763h) */
    IoR2yEe1clppbd ee1clppbd; /* 2841_(C764 - C767h) */
    IoR2yEe1clpmof ee1clpmof; /* 2841_(C768 - C76Fh) */
    IoR2yEe1clpmga ee1clpmga; /* 2841_(C770 - C773h) */
    IoR2yEe1clpmbd ee1clpmbd; /* 2841_(C774 - C777h) */

    kuchar dmyC778Ffff[0x10000 - 0xC778]; /* 2841_(C778 - FFFFh) */
};

/* Define i/o mapping */
struct _IoR2y
{
    /* JDSR2Y */
    IoR2yFr2y fR2y; /* 2841_(8000 - BFFFh) */
    IoR2yYych yych; /* 2841_(C000 - C07Fh) */
    IoR2yCmn r2yCmn; /* 2841_(C080 - C0BFh) */
    IoR2yYyr yyr; /* 2841_(C0C0 - C0FFh) */
    IoR2yYyw yyw; /* 2841_(C100 - FFFFh) */
};


extern volatile IoR2y ioR2yP1;
extern volatile IoR2y ioR2yP2;
extern volatile IoR2y ioR2yP3;


KConstType jdsr2y_f2e_get_type(void);
Jdsr2yF2e* jdsr2y_f2e_new(void);


#endif/*__JDSR2Y_F2E_H__*/
