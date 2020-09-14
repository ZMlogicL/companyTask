/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :郑蛘钊
 *@brief             :jdsr2yf2e2
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __JDSR2Y_F2E2_H__
#define __JDSR2Y_F2E2_H__


#include <klib.h>


#define JDSR2Y_TYPE_F2E2	        (jdsr2y_f2e2_get_type())
#define JDSR2Y_F2E2(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), Jdsr2yF2e2))
#define JDSR2Y_IS_F2E2(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSR2Y_TYPE_F2E2))


typedef struct _Jdsr2yF2e2          Jdsr2yF2e2;
typedef struct _Jdsr2yF2e2Private   Jdsr2yF2e2Private;

typedef union _IoR2yYyraxctl        IoR2yYyraxctl;
typedef union _IoR2yYyw0axctl       IoR2yYyw0axctl;
typedef union _IoR2yYywaaxctl       IoR2yYywaaxctl;
typedef union _IoR2yYyw1axctl       IoR2yYyw1axctl;
typedef union _IoR2yYyw2axctl       IoR2yYyw2axctl;
typedef union _IoR2yYyraxsts        IoR2yYyraxsts;
typedef union _IoR2yYyw0axsts       IoR2yYyw0axsts;
typedef union _IoR2yYywaaxsts       IoR2yYywaaxsts;
typedef union _IoR2yYyw1axsts       IoR2yYyw1axsts;
typedef union _IoR2yYyw2axsts       IoR2yYyw2axsts;
typedef union _IoR2yYyraxmd         IoR2yYyraxmd;
typedef union _IoR2yYyw0axmd        IoR2yYyw0axmd;
typedef union _IoR2yYywaaxmd        IoR2yYywaaxmd;
typedef union _IoR2yYyw1axmd        IoR2yYyw1axmd;
typedef union _IoR2yYyw2axmd        IoR2yYyw2axmd;
typedef union _IoR2yYyrreqmsk       IoR2yYyrreqmsk;
typedef union _IoR2yYyw0reqmsk      IoR2yYyw0reqmsk;
typedef union _IoR2yYywareqmsk      IoR2yYywareqmsk;
typedef union _IoR2yYyw1reqmsk      IoR2yYyw1reqmsk;
typedef union _IoR2yYyw2reqmsk      IoR2yYyw2reqmsk;
typedef union _IoR2yYyinte          IoR2yYyinte;
typedef union _IoR2yYyintf          IoR2yYyintf;
typedef union _IoR2yLintlv          IoR2yLintlv;
typedef union _IoR2yLintsel         IoR2yLintsel;
typedef union _IoR2yR2ymode         IoR2yR2ymode;
typedef union _IoR2yRamaen          IoR2yRamaen;
typedef union _IoR2yYyrtrg          IoR2yYyrtrg;
typedef union _IoR2yYyrctl          IoR2yYyrctl;
typedef union _IoR2yDinctl          IoR2yDinctl;
typedef union _IoR2yYyra            IoR2yYyra;
typedef union _IoR2yYyrofs          IoR2yYyrofs;
typedef union _IoR2yYyrdef          IoR2yYyrdef;
typedef union _IoR2yYyrhsiz         IoR2yYyrhsiz;
typedef union _IoR2yYyrvsiz         IoR2yYyrvsiz;
typedef union _IoR2yYywtrg          IoR2yYywtrg;
typedef union _IoR2yYywctl          IoR2yYywctl;
typedef union _IoR2yYywbank         IoR2yYywbank;
typedef union _IoR2yYywkpp          IoR2yYywkpp;
typedef union _IoR2yYyw0md          IoR2yYyw0md;
typedef union _IoR2yYyw1md          IoR2yYyw1md;
typedef union _IoR2yYyw2md          IoR2yYyw2md;
typedef union _IoR2yHstmd           IoR2yHstmd;
typedef union _IoR2yHsth            IoR2yHsth;
typedef union _IoR2yHstv            IoR2yHstv;
typedef union _IoR2yYyw0a           IoR2yYyw0a;
typedef union _IoR2yYyw0def         IoR2yYyw0def;
typedef union _IoR2yYyw0ofsx        IoR2yYyw0ofsx;
typedef union _IoR2yRsz0hsta        IoR2yRsz0hsta;
typedef union _IoR2yRsz0hpit        IoR2yRsz0hpit;
typedef union _IoR2yRsz0vsta        IoR2yRsz0vsta;
typedef union _IoR2yRsz0vpit        IoR2yRsz0vpit;
typedef union _IoR2yPcemd           IoR2yPcemd;
typedef union _IoR2yPcexy           IoR2yPcexy;
typedef union _IoR2yPcec            IoR2yPcec;
typedef union _IoR2yPceh            IoR2yPceh;


struct _Jdsr2yF2e2
{
    KObject parent;
};


/*  structure of yyraxctl   (2841_C000h)    */
union _IoR2yYyraxctl
{
    kulong word;
    struct
    {
        kulong yyrcache0 :4;
        kulong yyrprot0 :3;
        kulong :1;
        kulong yyrcache1 :4;
        kulong yyrprot1 :3;
        kulong :1;
        kulong yyrcache2 :4;
        kulong yyrprot2 :3;
        kulong :9;
    } bit;
};

/*  structure of yyw0axctl  (2841_C004h)    */
union _IoR2yYyw0axctl
{
    kulong word;
    struct
    {
        kulong yyw0cache0 :4;
        kulong yyw0prot0 :3;
        kulong :1;
        kulong yyw0cache1 :4;
        kulong yyw0prot1 :3;
        kulong :1;
        kulong yyw0cache2 :4;
        kulong yyw0prot2 :3;
        kulong :9;
    } bit;
};

/*  structure of yywaaxctl  (2841_C008h)    */
union _IoR2yYywaaxctl
{
    kulong word;
    struct
    {
        kulong yywacache0 :4;
        kulong yywaprot0 :3;
        kulong :1;
        kulong yywacache1 :4;
        kulong yywaprot1 :3;
        kulong :17;
    } bit;
};

/*  structure of yyw1axctl  (2841_C00Ch)    */
union _IoR2yYyw1axctl
{
    kulong word;
    struct
    {
        kulong yyw1cache0 :4;
        kulong yyw1prot0 :3;
        kulong :1;
        kulong yyw1cache1 :4;
        kulong yyw1prot1 :3;
        kulong :1;
        kulong yyw1cache2 :4;
        kulong yyw1prot2 :3;
        kulong :9;
    } bit;
};

/*  structure of yyw2axctl  (2841_C010h)    */
union _IoR2yYyw2axctl
{
    kulong word;
    struct
    {
        kulong yyw2cache :4;
        kulong yyw2prot :3;
        kulong :25;
    } bit;
};

/*  structure of yyraxsts   (2841_C014h)    */
union _IoR2yYyraxsts
{
    kulong word;
    struct
    {
        kulong yyrresp0 :2;
        kulong :6;
        kulong yyrresp1 :2;
        kulong :6;
        kulong yyrresp2 :2;
        kulong :14;
    } bit;
};

/*  structure of yyw0axsts  (2841_C018h)    */
union _IoR2yYyw0axsts
{
    kulong word;
    struct
    {
        kulong yy0bresp0 :2;
        kulong :6;
        kulong yy0bresp1 :2;
        kulong :6;
        kulong yy0bresp2 :2;
        kulong :14;
    } bit;
};

/*  structure of yywaaxsts  (2841_C01Ch)    */
union _IoR2yYywaaxsts
{
    kulong word;
    struct
    {
        kulong yyabresp0 :2;
        kulong :6;
        kulong yyabresp1 :2;
        kulong :22;
    } bit;
};

/*  structure of yyw1axsts  (2841_C020h)    */
union _IoR2yYyw1axsts
{
    kulong word;
    struct
    {
        kulong yy1bresp0 :2;
        kulong :6;
        kulong yy1bresp1 :2;
        kulong :6;
        kulong yy1bresp2 :2;
        kulong :14;
    } bit;
};

/*  structure of yyw2axsts  (2841_C024h)    */
union _IoR2yYyw2axsts
{
    kulong word;
    struct
    {
        kulong yy2bresp :2;
        kulong :30;
    } bit;
};

/*  structure of yyraxmd    (2841_C028h)    */
union _IoR2yYyraxmd
{
    kulong word;
    struct
    {
        kulong yyrbl :2;
        kulong :30;
    } bit;
};

/*  structure of yyw0axmd   (2841_C02Ch)    */
union _IoR2yYyw0axmd
{
    kulong word;
    struct
    {
        kulong yyw0msl :6;
        kulong :2;
        kulong yyw0bl :2;
        kulong :6;
        kulong yyw0doe :3;
        kulong :13;
    } bit;
};

/*  structure of yywaaxmd   (2841_C030h)    */
union _IoR2yYywaaxmd
{
    kulong word;
    struct
    {
        kulong yywamsl :4;
        kulong :4;
        kulong yywabl :2;
        kulong :6;
        kulong yywadoe :2;
        kulong :14;
    } bit;
};

/*  structure of yyw1axmd   (2841_C034h)    */
union _IoR2yYyw1axmd
{
    kulong word;
    struct
    {
        kulong yyw1msl :6;
        kulong :2;
        kulong yyw1bl :2;
        kulong :6;
        kulong yyw1doe :3;
        kulong :13;
    } bit;
};

/*  structure of yyw2axmd   (2841_C038h)    */
union _IoR2yYyw2axmd
{
    kulong word;
    struct
    {
        kulong yyw2msl :2;
        kulong :6;
        kulong yyw2bl :2;
        kulong :22;
    } bit;
};

/*  structure of yyrreqmsk  (2841_C040h)    */
union _IoR2yYyrreqmsk
{
    kulong word[2];
    struct
    {
        kulong yyrreqmsk0 :12;
        kulong :4;
        kulong yyrreqmsk1 :12;
        kulong :4;
        kulong yyrreqmsk2 :12;
        kulong :20;
    } bit;
};

/*  structure of yyw0reqmsk (2841_C048h)    */
union _IoR2yYyw0reqmsk
{
    kulong word[2];
    struct
    {
        kulong yyw0reqmsk0 :12;
        kulong :4;
        kulong yyw0reqmsk1 :12;
        kulong :4;
        kulong yyw0reqmsk2 :12;
        kulong :20;
    } bit;
};

/*  structure of yywareqmsk (2841_C050h)    */
union _IoR2yYywareqmsk
{
    kulong word;
    struct
    {
        kulong yywareqmsk0 :12;
        kulong :4;
        kulong yywareqmsk1 :12;
        kulong :4;
    } bit;
};

/*  structure of yyw1reqmsk (2841_C058h)    */
union _IoR2yYyw1reqmsk
{
    kulong word[2];
    struct
    {
        kulong yyw1reqmsk0 :12;
        kulong :4;
        kulong yyw1reqmsk1 :12;
        kulong :4;
        kulong yyw1reqmsk2 :12;
        kulong :20;
    } bit;
};

/*  structure of yyw2reqmsk (2841_C060h)    */
union _IoR2yYyw2reqmsk
{
    kulong word;
    struct
    {
        kulong yyw2reqmsk :12;
        kulong :20;
    } bit;
};

/*  structure of yyinte (2841_C080h)    */
union _IoR2yYyinte
{
    kulong word;
    struct
    {
        kulong yyree :1;
        kulong :3;
        kulong yyw0ee :1;
        kulong yywaee :1;
        kulong yyw1ee :1;
        kulong yyw2ee :1;
        kulong yywee :1;
        kulong :3;
        kulong lint0e :1;
        kulong lint1e :1;
        kulong lint2e :1;
        kulong :1;
        kulong yyrere :1;
        kulong yywere :1;
        kulong :2;
        kulong axrere :1;
        kulong axwere :1;
        kulong :10;
    } bit;
};

/*  structure of yyintf (2841_C084h)    */
union _IoR2yYyintf
{
    kulong word;
    struct
    {
        kulong yyref :1;
        kulong :3;
        kulong yyw0ef :1;
        kulong yywaef :1;
        kulong yyw1ef :1;
        kulong yyw2ef :1;
        kulong yywef :1;
        kulong :3;
        kulong lint0f :1;
        kulong lint1f :1;
        kulong lint2f :1;
        kulong :1;
        kulong yyrerf :1;
        kulong yywerf :1;
        kulong :2;
        kulong axrerf :1;
        kulong axwerf :1;
        kulong :10;
    } bit;
};

/*  structure of lintlv (2841_C088h)    */
union _IoR2yLintlv
{
    kulong word[2];
    struct
    {
        kulong lintlv0 :14;
        kulong :2;
        kulong lintlv1 :14;
        kulong :2;
        kulong lintlv2 :14;
        kulong :18;
    } bit;
};

/*  structure of lintsel    (2841_C090h)    */
union _IoR2yLintsel
{
    kulong word;
    struct
    {
        kulong lints0 :1;
        kulong :7;
        kulong lints1 :1;
        kulong :7;
        kulong lints2 :1;
        kulong :15;
    } bit;
};

/*  structure of r2ymode    (2841_C094h)    */
union _IoR2yR2ymode
{
    kulong word;
    struct
    {
        kulong ycfbyp :1;
        kulong ycfpdd :1;
        kulong :2;
        kulong mccsl :1;
        kulong mcc1bm :1;
        kulong :26;
    } bit;
};

/*  structure of ramaen (2841_C098h)    */
union _IoR2yRamaen
{
    kulong word;
    struct
    {
        kulong yyraenRgbDeknee :1;
        kulong yyraenYyr :1;
        kulong :2;
        kulong yw0aenYyw0 :1;
        kulong yw0aenYyw0Bicubic :1;
        kulong yw0aenYyw0Edge :1;
        kulong yw0aenYyw0a :1;
        kulong yw1aenYyw1 :1;
        kulong yw1aenYyw1Bicubic :1;
        kulong yw1aenYyw1Edge :1;
        kulong yw2aen :1;
        kulong hstaen :1;
        kulong :19;
    } bit;
};

/*  structure of yyrtrg (2841_C0C0h)    */
union _IoR2yYyrtrg
{
    kulong word;
    struct
    {
        kulong yyrtrg :2;
        kulong :30;
    } bit;
};

/*  structure of yyrctl (2841_C0C4h)    */
union _IoR2yYyrctl
{
    kulong word;
    struct
    {
        kulong yyrdtyp :2;
        kulong :2;
        kulong monoen :1;
        kulong :3;
        kulong dknen :1;
        kulong :3;
        kulong rgblsft :2;
        kulong rgblsm :1;
        kulong :17;
    } bit;
};

/*  structure of dinctl (2841_C0C8h)    */
union _IoR2yDinctl
{
    kulong word;
    struct
    {
        kulong b2rdin :1;
        kulong :7;
        kulong frmstp :1;
        kulong :23;
    } bit;
};

/*  structure of yyra   (2841_C0D0h)    */
union _IoR2yYyra
{
    kulong word[3];
    struct
    {
        kulong yyra0 :32;
        kulong yyra1 :32;
        kulong yyra2 :32;
    } bit;
};

/*  structure of yyrofs (2841_C0E0h)    */
union _IoR2yYyrofs
{
    kulong word;
    struct
    {
        kulong yyrofs0 :3;
        kulong :5;
        kulong yyrofs1 :3;
        kulong :5;
        kulong yyrofs2 :3;
        kulong :13;
    } bit;
};

/*  structure of yyrdef (2841_C0E4h)    */
union _IoR2yYyrdef
{
    kulong word;
    struct
    {
        kulong yyrdef :16;
        kulong :16;
    } bit;
};

/*  structure of yyrhsiz    (2841_C0E8h)    */
union _IoR2yYyrhsiz
{
    kulong word;
    struct
    {
        kulong yyrhsiz :13;
        kulong :19;
    } bit;
};

/*  structure of yyrvsiz    (2841_C0ECh)    */
union _IoR2yYyrvsiz
{
    kulong word;
    struct
    {
        kulong yyrvsiz :14;
        kulong :18;
    } bit;
};

/*  structure of yywtrg (2841_C100h)    */
union _IoR2yYywtrg
{
    kulong word;
    struct
    {
        kulong yywtrg :2;
        kulong :30;
    } bit;
};

/*  structure of yywctl (2841_C104h)    */
union _IoR2yYywctl
{
    kulong word;
    struct
    {
        kulong yywmode :3;
        kulong :1;
        kulong yywcse :1;
        kulong yywhrv :1;
        kulong :2;
        kulong usebank0 :2;
        kulong usebanka :2;
        kulong usebank1 :2;
        kulong usebank2 :2;
        kulong :16;
    } bit;
};

/*  structure of yywbank    (2841_C108h)    */
union _IoR2yYywbank
{
    kulong word;
    struct
    {
        kulong bankst :1;
        kulong :3;
        kulong bank0ps :2;
        kulong bankaps :2;
        kulong bank1ps :2;
        kulong bank2ps :2;
        kulong :4;
        kulong bank0sts :2;
        kulong bankasts :2;
        kulong bank1sts :2;
        kulong bank2sts :2;
        kulong :8;
    } bit;
};

/*  structure of yywkpp (2841_C10Ch)    */
union _IoR2yYywkpp
{
    kulong word;
    struct
    {
        kulong yywkpp :1;
        kulong :31;
    } bit;
};

/*  structure of yyw0md (2841_C110h)    */
union _IoR2yYyw0md
{
    kulong word;
    struct
    {
        kulong rsz0md :1;
        kulong :3;
        kulong rdc0md :2;
        kulong rdc0en :1;
        kulong :1;
        kulong css0sl :4;
        kulong trm0en :1;
        kulong :3;
        kulong spl0en :1;
        kulong ch0vfm :1;
        kulong :2;
        kulong extben :1;
        kulong trmben :1;
        kulong :2;
        kulong extcen :1;
        kulong trmcen :1;
        kulong :2;
        kulong ch0amd :2;
        kulong chavfm :1;
        kulong :1;
    } bit;
};

/*  structure of yyw1md (2841_C114h)    */
union _IoR2yYyw1md
{
    kulong word;
    struct
    {
        kulong rsz1md :1;
        kulong :3;
        kulong rdc1md :2;
        kulong rdc1en :1;
        kulong :1;
        kulong css1sl :4;
        kulong trm1en :1;
        kulong dfm1sl :1;
        kulong :2;
        kulong spl1en :1;
        kulong :1;
        kulong dty1sl :2;
        kulong :12;
    } bit;
};

/*  structure of yyw2md (2841_C118h)    */
union _IoR2yYyw2md
{
    kulong word;
    struct
    {
        kulong :4;
        kulong rdc2md :2;
        kulong rdc2en :1;
        kulong :5;
        kulong trm2en :1;
        kulong :19;
    } bit;
};

/*  structure of hstmd  (2841_C120h)    */
union _IoR2yHstmd
{
    kulong word;
    struct
    {
        kulong hsten :1;
        kulong :1;
        kulong hstsel :1;
        kulong :1;
        kulong pitM :2;
        kulong :2;
        kulong yhsovf :1;
        kulong :3;
        kulong hststs :1;
        kulong :19;
    } bit;
};

/*  structure of hsth   (2841_C124h)    */
union _IoR2yHsth
{
    kulong word;
    struct
    {
        kulong hsthsta :13;
        kulong :3;
        kulong hsthsiz :13;
        kulong :3;
    } bit;
};

/*  structure of hstv   (2841_C128h)    */
union _IoR2yHstv
{
    kulong word;
    struct
    {
        kulong hstvsta :14;
        kulong :2;
        kulong hstvsiz :14;
        kulong :2;
    } bit;
};

/*  structure of yyw0a  (2841_C200h)    */
union _IoR2yYyw0a
{
    kulong word[3][4];
    struct
    {
        kulong yyw0a00 :32;
        kulong yyw0a01 :32;
        kulong yyw0a02 :32;
        kulong yyw0a03 :32;
        kulong yyw0a10 :32;
        kulong yyw0a11 :32;
        kulong yyw0a12 :32;
        kulong yyw0a13 :32;
        kulong yyw0a20 :32;
        kulong yyw0a21 :32;
        kulong yyw0a22 :32;
        kulong yyw0a23 :32;
    } bit;
};

/*  structure of yyw0def    (2841_C240h)    */
union _IoR2yYyw0def
{
    kulong word[2];
    struct
    {
        klong yyw0def0 :17;
        kulong :15;
        klong yyw0def1 :17;
        kulong :15;
    } bit;
};

/*  structure of yyw0ofsx   (2841_C248h)    */
union _IoR2yYyw0ofsx
{
    kulong word[2];
    struct
    {
        kulong yyw0ofsx0 :12;
        kulong :4;
        kulong yyw0ofsx1 :12;
        kulong :4;
        kulong yyw0ofsx2 :12;
        kulong :4;
        kulong yyw0ofsx3 :12;
        kulong :4;
    } bit;
};

/*  structure of rsz0hsta   (2841_C258h)    */
union _IoR2yRsz0hsta
{
    kulong word;
    struct
    {
        kulong rsz0hsta :20;
        kulong :12;
    } bit;
};

/*  structure of rsz0hpit   (2841_C25Ch)    */
union _IoR2yRsz0hpit
{
    kulong word;
    struct
    {
        kulong rsz0hpit :16;
        kulong :16;
    } bit;
};

/*  structure of rsz0vsta   (2841_C260h)    */
union _IoR2yRsz0vsta
{
    kulong word;
    struct
    {
        kulong rsz0vsta :20;
        kulong :12;
    } bit;
};

/*  structure of rsz0vpit   (2841_C264h)    */
union _IoR2yRsz0vpit
{
    kulong word;
    struct
    {
        kulong rsz0vpit :16;
        kulong :16;
    } bit;
};

/*  structure of pcemd  (2841_C268h)    */
union _IoR2yPcemd
{
    kulong word;
    struct
    {
        kulong pceen :1;
        kulong :31;
    } bit;
};

/*  structure of pcexy  (2841_C26Ch)    */
union _IoR2yPcexy
{
    kulong word;
    struct
    {
        klong pcex :9;
        kulong :7;
        klong pcey :9;
        kulong :7;
    } bit;
};

/*  structure of pcec   (2841_C270h)    */
union _IoR2yPcec
{
    kulong word;
    struct
    {
        kulong pcecof :8;
        kulong :8;
        kulong pcecga :10;
        kulong :6;
    } bit;
};

/*  structure of pceh   (2841_C274h)    */
union _IoR2yPceh
{
    kulong word;
    struct
    {
        kulong pcehof :8;
        kulong :8;
        kulong pcehga :10;
        kulong :6;
    } bit;
};


KConstType  jdsr2y_f2e2_get_type(void);
Jdsr2yF2e2* jdsr2y_f2e2_new(void);


#endif/*__JDSR2Y_F2E2_H__*/
