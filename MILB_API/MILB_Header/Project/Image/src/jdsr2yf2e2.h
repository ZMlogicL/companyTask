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

#define JDSR2Y_TYPE_F2E2	(jdsr2y_f2e2_get_type())
#define JDSR2Y_F2E2(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), Jdsr2yF2e2))
#define JDSR2Y_IS_F2E2(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSR2Y_TYPE_F2E2))

typedef struct _Jdsr2yF2e2 Jdsr2yF2e2;
typedef struct _Jdsr2yF2e2Private Jdsr2yF2e2Private;

typedef union _IoR2yYyraxctl IoR2yYyraxctl;
typedef union _IoR2yYyw0axctl IoR2yYyw0axctl;
typedef union _IoR2yYywaaxctl IoR2yYywaaxctl;
typedef union _IoR2yYyw1axctl IoR2yYyw1axctl;
typedef union _IoR2yYyw2axctl IoR2yYyw2axctl;
typedef union _IoR2yYyraxsts IoR2yYyraxsts;
typedef union _IoR2yYyw0axsts IoR2yYyw0axsts;
typedef union _IoR2yYywaaxsts IoR2yYywaaxsts;
typedef union _IoR2yYyw1axsts IoR2yYyw1axsts;
typedef union _IoR2yYyw2axsts IoR2yYyw2axsts;
typedef union _IoR2yYyraxmd IoR2yYyraxmd;
typedef union _IoR2yYyw0axmd IoR2yYyw0axmd;
typedef union _IoR2yYywaaxmd IoR2yYywaaxmd;
typedef union _IoR2yYyw1axmd IoR2yYyw1axmd;
typedef union _IoR2yYyw2axmd IoR2yYyw2axmd;
typedef union _IoR2yYyrreqmsk IoR2yYyrreqmsk;
typedef union _IoR2yYyw0reqmsk IoR2yYyw0reqmsk;
typedef union _IoR2yYywareqmsk IoR2yYywareqmsk;
typedef union _IoR2yYyw1reqmsk IoR2yYyw1reqmsk;
typedef union _IoR2yYyw2reqmsk IoR2yYyw2reqmsk;
typedef union _IoR2yYyinte IoR2yYyinte;
typedef union _IoR2yYyintf IoR2yYyintf;
typedef union _IoR2yLintlv IoR2yLintlv;
typedef union _IoR2yLintsel IoR2yLintsel;
typedef union _IoR2yR2ymode IoR2yR2ymode;
typedef union _IoR2yRamaen IoR2yRamaen;
typedef union _IoR2yYyrtrg IoR2yYyrtrg;
typedef union _IoR2yYyrctl IoR2yYyrctl;
typedef union _IoR2yDinctl IoR2yDinctl;
typedef union _IoR2yYyra IoR2yYyra;
typedef union _IoR2yYyrofs IoR2yYyrofs;
typedef union _IoR2yYyrdef IoR2yYyrdef;
typedef union _IoR2yYyrhsiz IoR2yYyrhsiz;
typedef union _IoR2yYyrvsiz IoR2yYyrvsiz;
typedef union _IoR2yYywtrg IoR2yYywtrg;
typedef union _IoR2yYywctl IoR2yYywctl;
typedef union _IoR2yYywbank IoR2yYywbank;
typedef union _IoR2yYywkpp IoR2yYywkpp;
typedef union _IoR2yYyw0md IoR2yYyw0md;
typedef union _IoR2yYyw1md IoR2yYyw1md;
typedef union _IoR2yYyw2md IoR2yYyw2md;
typedef union _IoR2yHstmd IoR2yHstmd;
typedef union _IoR2yHsth IoR2yHsth;
typedef union _IoR2yHstv IoR2yHstv;
typedef union _IoR2yYyw0a IoR2yYyw0a;
typedef union _IoR2yYyw0def IoR2yYyw0def;
typedef union _IoR2yYyw0ofsx IoR2yYyw0ofsx;
typedef union _IoR2yRsz0hsta IoR2yRsz0hsta;
typedef union _IoR2yRsz0hpit IoR2yRsz0hpit;
typedef union _IoR2yRsz0vsta IoR2yRsz0vsta;
typedef union _IoR2yRsz0vpit IoR2yRsz0vpit;
typedef union _IoR2yPcemd IoR2yPcemd;
typedef union _IoR2yPcexy IoR2yPcexy;
typedef union _IoR2yPcec IoR2yPcec;
typedef union _IoR2yPceh IoR2yPceh;

struct _Jdsr2yF2e2
{
    KObject parent;
};

/*  structure of yyraxctl   (2841_C000h)    */
union _IoR2yYyraxctl
{
    unsigned long word;
    struct
    {
        unsigned long yyrcache0 :4;
        unsigned long yyrprot0 :3;
        unsigned long :1;
        unsigned long yyrcache1 :4;
        unsigned long yyrprot1 :3;
        unsigned long :1;
        unsigned long yyrcache2 :4;
        unsigned long yyrprot2 :3;
        unsigned long :9;
    } bit;
};

/*  structure of yyw0axctl  (2841_C004h)    */
union _IoR2yYyw0axctl
{
    unsigned long word;
    struct
    {
        unsigned long yyw0cache0 :4;
        unsigned long yyw0prot0 :3;
        unsigned long :1;
        unsigned long yyw0cache1 :4;
        unsigned long yyw0prot1 :3;
        unsigned long :1;
        unsigned long yyw0cache2 :4;
        unsigned long yyw0prot2 :3;
        unsigned long :9;
    } bit;
};

/*  structure of yywaaxctl  (2841_C008h)    */
union _IoR2yYywaaxctl
{
    unsigned long word;
    struct
    {
        unsigned long yywacache0 :4;
        unsigned long yywaprot0 :3;
        unsigned long :1;
        unsigned long yywacache1 :4;
        unsigned long yywaprot1 :3;
        unsigned long :17;
    } bit;
};

/*  structure of yyw1axctl  (2841_C00Ch)    */
union _IoR2yYyw1axctl
{
    unsigned long word;
    struct
    {
        unsigned long yyw1cache0 :4;
        unsigned long yyw1prot0 :3;
        unsigned long :1;
        unsigned long yyw1cache1 :4;
        unsigned long yyw1prot1 :3;
        unsigned long :1;
        unsigned long yyw1cache2 :4;
        unsigned long yyw1prot2 :3;
        unsigned long :9;
    } bit;
};

/*  structure of yyw2axctl  (2841_C010h)    */
union _IoR2yYyw2axctl
{
    unsigned long word;
    struct
    {
        unsigned long yyw2cache :4;
        unsigned long yyw2prot :3;
        unsigned long :25;
    } bit;
};

/*  structure of yyraxsts   (2841_C014h)    */
union _IoR2yYyraxsts
{
    unsigned long word;
    struct
    {
        unsigned long yyrresp0 :2;
        unsigned long :6;
        unsigned long yyrresp1 :2;
        unsigned long :6;
        unsigned long yyrresp2 :2;
        unsigned long :14;
    } bit;
};

/*  structure of yyw0axsts  (2841_C018h)    */
union _IoR2yYyw0axsts
{
    unsigned long word;
    struct
    {
        unsigned long yy0bresp0 :2;
        unsigned long :6;
        unsigned long yy0bresp1 :2;
        unsigned long :6;
        unsigned long yy0bresp2 :2;
        unsigned long :14;
    } bit;
};

/*  structure of yywaaxsts  (2841_C01Ch)    */
union _IoR2yYywaaxsts
{
    unsigned long word;
    struct
    {
        unsigned long yyabresp0 :2;
        unsigned long :6;
        unsigned long yyabresp1 :2;
        unsigned long :22;
    } bit;
};

/*  structure of yyw1axsts  (2841_C020h)    */
union _IoR2yYyw1axsts
{
    unsigned long word;
    struct
    {
        unsigned long yy1bresp0 :2;
        unsigned long :6;
        unsigned long yy1bresp1 :2;
        unsigned long :6;
        unsigned long yy1bresp2 :2;
        unsigned long :14;
    } bit;
};

/*  structure of yyw2axsts  (2841_C024h)    */
union _IoR2yYyw2axsts
{
    unsigned long word;
    struct
    {
        unsigned long yy2bresp :2;
        unsigned long :30;
    } bit;
};

/*  structure of yyraxmd    (2841_C028h)    */
union _IoR2yYyraxmd
{
    unsigned long word;
    struct
    {
        unsigned long yyrbl :2;
        unsigned long :30;
    } bit;
};

/*  structure of yyw0axmd   (2841_C02Ch)    */
union _IoR2yYyw0axmd
{
    unsigned long word;
    struct
    {
        unsigned long yyw0msl :6;
        unsigned long :2;
        unsigned long yyw0bl :2;
        unsigned long :6;
        unsigned long yyw0doe :3;
        unsigned long :13;
    } bit;
};

/*  structure of yywaaxmd   (2841_C030h)    */
union _IoR2yYywaaxmd
{
    unsigned long word;
    struct
    {
        unsigned long yywamsl :4;
        unsigned long :4;
        unsigned long yywabl :2;
        unsigned long :6;
        unsigned long yywadoe :2;
        unsigned long :14;
    } bit;
};

/*  structure of yyw1axmd   (2841_C034h)    */
union _IoR2yYyw1axmd
{
    unsigned long word;
    struct
    {
        unsigned long yyw1msl :6;
        unsigned long :2;
        unsigned long yyw1bl :2;
        unsigned long :6;
        unsigned long yyw1doe :3;
        unsigned long :13;
    } bit;
};

/*  structure of yyw2axmd   (2841_C038h)    */
union _IoR2yYyw2axmd
{
    unsigned long word;
    struct
    {
        unsigned long yyw2msl :2;
        unsigned long :6;
        unsigned long yyw2bl :2;
        unsigned long :22;
    } bit;
};

/*  structure of yyrreqmsk  (2841_C040h)    */
union _IoR2yYyrreqmsk
{
    unsigned long word[2];
    struct
    {
        unsigned long yyrreqmsk0 :12;
        unsigned long :4;
        unsigned long yyrreqmsk1 :12;
        unsigned long :4;
        unsigned long yyrreqmsk2 :12;
        unsigned long :20;
    } bit;
};

/*  structure of yyw0reqmsk (2841_C048h)    */
union _IoR2yYyw0reqmsk
{
    unsigned long word[2];
    struct
    {
        unsigned long yyw0reqmsk0 :12;
        unsigned long :4;
        unsigned long yyw0reqmsk1 :12;
        unsigned long :4;
        unsigned long yyw0reqmsk2 :12;
        unsigned long :20;
    } bit;
};

/*  structure of yywareqmsk (2841_C050h)    */
union _IoR2yYywareqmsk
{
    unsigned long word;
    struct
    {
        unsigned long yywareqmsk0 :12;
        unsigned long :4;
        unsigned long yywareqmsk1 :12;
        unsigned long :4;
    } bit;
};

/*  structure of yyw1reqmsk (2841_C058h)    */
union _IoR2yYyw1reqmsk
{
    unsigned long word[2];
    struct
    {
        unsigned long yyw1reqmsk0 :12;
        unsigned long :4;
        unsigned long yyw1reqmsk1 :12;
        unsigned long :4;
        unsigned long yyw1reqmsk2 :12;
        unsigned long :20;
    } bit;
};

/*  structure of yyw2reqmsk (2841_C060h)    */
union _IoR2yYyw2reqmsk
{
    unsigned long word;
    struct
    {
        unsigned long yyw2reqmsk :12;
        unsigned long :20;
    } bit;
};

/*  structure of yyinte (2841_C080h)    */
union _IoR2yYyinte
{
    unsigned long word;
    struct
    {
        unsigned long yyree :1;
        unsigned long :3;
        unsigned long yyw0ee :1;
        unsigned long yywaee :1;
        unsigned long yyw1ee :1;
        unsigned long yyw2ee :1;
        unsigned long yywee :1;
        unsigned long :3;
        unsigned long lint0e :1;
        unsigned long lint1e :1;
        unsigned long lint2e :1;
        unsigned long :1;
        unsigned long yyrere :1;
        unsigned long yywere :1;
        unsigned long :2;
        unsigned long axrere :1;
        unsigned long axwere :1;
        unsigned long :10;
    } bit;
};

/*  structure of yyintf (2841_C084h)    */
union _IoR2yYyintf
{
    unsigned long word;
    struct
    {
        unsigned long yyref :1;
        unsigned long :3;
        unsigned long yyw0ef :1;
        unsigned long yywaef :1;
        unsigned long yyw1ef :1;
        unsigned long yyw2ef :1;
        unsigned long yywef :1;
        unsigned long :3;
        unsigned long lint0f :1;
        unsigned long lint1f :1;
        unsigned long lint2f :1;
        unsigned long :1;
        unsigned long yyrerf :1;
        unsigned long yywerf :1;
        unsigned long :2;
        unsigned long axrerf :1;
        unsigned long axwerf :1;
        unsigned long :10;
    } bit;
};

/*  structure of lintlv (2841_C088h)    */
union _IoR2yLintlv
{
    unsigned long word[2];
    struct
    {
        unsigned long lintlv0 :14;
        unsigned long :2;
        unsigned long lintlv1 :14;
        unsigned long :2;
        unsigned long lintlv2 :14;
        unsigned long :18;
    } bit;
};

/*  structure of lintsel    (2841_C090h)    */
union _IoR2yLintsel
{
    unsigned long word;
    struct
    {
        unsigned long lints0 :1;
        unsigned long :7;
        unsigned long lints1 :1;
        unsigned long :7;
        unsigned long lints2 :1;
        unsigned long :15;
    } bit;
};

/*  structure of r2ymode    (2841_C094h)    */
union _IoR2yR2ymode
{
    unsigned long word;
    struct
    {
        unsigned long ycfbyp :1;
        unsigned long ycfpdd :1;
        unsigned long :2;
        unsigned long mccsl :1;
        unsigned long mcc1bm :1;
        unsigned long :26;
    } bit;
};

/*  structure of ramaen (2841_C098h)    */
union _IoR2yRamaen
{
    unsigned long word;
    struct
    {
        unsigned long yyraenRgbDeknee :1;
        unsigned long yyraenYyr :1;
        unsigned long :2;
        unsigned long yw0aenYyw0 :1;
        unsigned long yw0aenYyw0Bicubic :1;
        unsigned long yw0aenYyw0Edge :1;
        unsigned long yw0aenYyw0a :1;
        unsigned long yw1aenYyw1 :1;
        unsigned long yw1aenYyw1Bicubic :1;
        unsigned long yw1aenYyw1Edge :1;
        unsigned long yw2aen :1;
        unsigned long hstaen :1;
        unsigned long :19;
    } bit;
};

/*  structure of yyrtrg (2841_C0C0h)    */
union _IoR2yYyrtrg
{
    unsigned long word;
    struct
    {
        unsigned long yyrtrg :2;
        unsigned long :30;
    } bit;
};

/*  structure of yyrctl (2841_C0C4h)    */
union _IoR2yYyrctl
{
    unsigned long word;
    struct
    {
        unsigned long yyrdtyp :2;
        unsigned long :2;
        unsigned long monoen :1;
        unsigned long :3;
        unsigned long dknen :1;
        unsigned long :3;
        unsigned long rgblsft :2;
        unsigned long rgblsm :1;
        unsigned long :17;
    } bit;
};

/*  structure of dinctl (2841_C0C8h)    */
union _IoR2yDinctl
{
    unsigned long word;
    struct
    {
        unsigned long b2rdin :1;
        unsigned long :7;
        unsigned long frmstp :1;
        unsigned long :23;
    } bit;
};

/*  structure of yyra   (2841_C0D0h)    */
union _IoR2yYyra
{
    unsigned long word[3];
    struct
    {
        unsigned long yyra0 :32;
        unsigned long yyra1 :32;
        unsigned long yyra2 :32;
    } bit;
};

/*  structure of yyrofs (2841_C0E0h)    */
union _IoR2yYyrofs
{
    unsigned long word;
    struct
    {
        unsigned long yyrofs0 :3;
        unsigned long :5;
        unsigned long yyrofs1 :3;
        unsigned long :5;
        unsigned long yyrofs2 :3;
        unsigned long :13;
    } bit;
};

/*  structure of yyrdef (2841_C0E4h)    */
union _IoR2yYyrdef
{
    unsigned long word;
    struct
    {
        unsigned long yyrdef :16;
        unsigned long :16;
    } bit;
};

/*  structure of yyrhsiz    (2841_C0E8h)    */
union _IoR2yYyrhsiz
{
    unsigned long word;
    struct
    {
        unsigned long yyrhsiz :13;
        unsigned long :19;
    } bit;
};

/*  structure of yyrvsiz    (2841_C0ECh)    */
union _IoR2yYyrvsiz
{
    unsigned long word;
    struct
    {
        unsigned long yyrvsiz :14;
        unsigned long :18;
    } bit;
};

/*  structure of yywtrg (2841_C100h)    */
union _IoR2yYywtrg
{
    unsigned long word;
    struct
    {
        unsigned long yywtrg :2;
        unsigned long :30;
    } bit;
};

/*  structure of yywctl (2841_C104h)    */
union _IoR2yYywctl
{
    unsigned long word;
    struct
    {
        unsigned long yywmode :3;
        unsigned long :1;
        unsigned long yywcse :1;
        unsigned long yywhrv :1;
        unsigned long :2;
        unsigned long usebank0 :2;
        unsigned long usebanka :2;
        unsigned long usebank1 :2;
        unsigned long usebank2 :2;
        unsigned long :16;
    } bit;
};

/*  structure of yywbank    (2841_C108h)    */
union _IoR2yYywbank
{
    unsigned long word;
    struct
    {
        unsigned long bankst :1;
        unsigned long :3;
        unsigned long bank0ps :2;
        unsigned long bankaps :2;
        unsigned long bank1ps :2;
        unsigned long bank2ps :2;
        unsigned long :4;
        unsigned long bank0sts :2;
        unsigned long bankasts :2;
        unsigned long bank1sts :2;
        unsigned long bank2sts :2;
        unsigned long :8;
    } bit;
};

/*  structure of yywkpp (2841_C10Ch)    */
union _IoR2yYywkpp
{
    unsigned long word;
    struct
    {
        unsigned long yywkpp :1;
        unsigned long :31;
    } bit;
};

/*  structure of yyw0md (2841_C110h)    */
union _IoR2yYyw0md
{
    unsigned long word;
    struct
    {
        unsigned long rsz0md :1;
        unsigned long :3;
        unsigned long rdc0md :2;
        unsigned long rdc0en :1;
        unsigned long :1;
        unsigned long css0sl :4;
        unsigned long trm0en :1;
        unsigned long :3;
        unsigned long spl0en :1;
        unsigned long ch0vfm :1;
        unsigned long :2;
        unsigned long extben :1;
        unsigned long trmben :1;
        unsigned long :2;
        unsigned long extcen :1;
        unsigned long trmcen :1;
        unsigned long :2;
        unsigned long ch0amd :2;
        unsigned long chavfm :1;
        unsigned long :1;
    } bit;
};

/*  structure of yyw1md (2841_C114h)    */
union _IoR2yYyw1md
{
    unsigned long word;
    struct
    {
        unsigned long rsz1md :1;
        unsigned long :3;
        unsigned long rdc1md :2;
        unsigned long rdc1en :1;
        unsigned long :1;
        unsigned long css1sl :4;
        unsigned long trm1en :1;
        unsigned long dfm1sl :1;
        unsigned long :2;
        unsigned long spl1en :1;
        unsigned long :1;
        unsigned long dty1sl :2;
        unsigned long :12;
    } bit;
};

/*  structure of yyw2md (2841_C118h)    */
union _IoR2yYyw2md
{
    unsigned long word;
    struct
    {
        unsigned long :4;
        unsigned long rdc2md :2;
        unsigned long rdc2en :1;
        unsigned long :5;
        unsigned long trm2en :1;
        unsigned long :19;
    } bit;
};

/*  structure of hstmd  (2841_C120h)    */
union _IoR2yHstmd
{
    unsigned long word;
    struct
    {
        unsigned long hsten :1;
        unsigned long :1;
        unsigned long hstsel :1;
        unsigned long :1;
        unsigned long pitM :2;
        unsigned long :2;
        unsigned long yhsovf :1;
        unsigned long :3;
        unsigned long hststs :1;
        unsigned long :19;
    } bit;
};

/*  structure of hsth   (2841_C124h)    */
union _IoR2yHsth
{
    unsigned long word;
    struct
    {
        unsigned long hsthsta :13;
        unsigned long :3;
        unsigned long hsthsiz :13;
        unsigned long :3;
    } bit;
};

/*  structure of hstv   (2841_C128h)    */
union _IoR2yHstv
{
    unsigned long word;
    struct
    {
        unsigned long hstvsta :14;
        unsigned long :2;
        unsigned long hstvsiz :14;
        unsigned long :2;
    } bit;
};

/*  structure of yyw0a  (2841_C200h)    */
union _IoR2yYyw0a
{
    unsigned long word[3][4];
    struct
    {
        unsigned long yyw0a00 :32;
        unsigned long yyw0a01 :32;
        unsigned long yyw0a02 :32;
        unsigned long yyw0a03 :32;
        unsigned long yyw0a10 :32;
        unsigned long yyw0a11 :32;
        unsigned long yyw0a12 :32;
        unsigned long yyw0a13 :32;
        unsigned long yyw0a20 :32;
        unsigned long yyw0a21 :32;
        unsigned long yyw0a22 :32;
        unsigned long yyw0a23 :32;
    } bit;
};

/*  structure of yyw0def    (2841_C240h)    */
union _IoR2yYyw0def
{
    unsigned long word[2];
    struct
    {
        long yyw0def0 :17;
        unsigned long :15;
        long yyw0def1 :17;
        unsigned long :15;
    } bit;
};

/*  structure of yyw0ofsx   (2841_C248h)    */
union _IoR2yYyw0ofsx
{
    unsigned long word[2];
    struct
    {
        unsigned long yyw0ofsx0 :12;
        unsigned long :4;
        unsigned long yyw0ofsx1 :12;
        unsigned long :4;
        unsigned long yyw0ofsx2 :12;
        unsigned long :4;
        unsigned long yyw0ofsx3 :12;
        unsigned long :4;
    } bit;
};

/*  structure of rsz0hsta   (2841_C258h)    */
union _IoR2yRsz0hsta
{
    unsigned long word;
    struct
    {
        unsigned long rsz0hsta :20;
        unsigned long :12;
    } bit;
};

/*  structure of rsz0hpit   (2841_C25Ch)    */
union _IoR2yRsz0hpit
{
    unsigned long word;
    struct
    {
        unsigned long rsz0hpit :16;
        unsigned long :16;
    } bit;
};

/*  structure of rsz0vsta   (2841_C260h)    */
union _IoR2yRsz0vsta
{
    unsigned long word;
    struct
    {
        unsigned long rsz0vsta :20;
        unsigned long :12;
    } bit;
};

/*  structure of rsz0vpit   (2841_C264h)    */
union _IoR2yRsz0vpit
{
    unsigned long word;
    struct
    {
        unsigned long rsz0vpit :16;
        unsigned long :16;
    } bit;
};

/*  structure of pcemd  (2841_C268h)    */
union _IoR2yPcemd
{
    unsigned long word;
    struct
    {
        unsigned long pceen :1;
        unsigned long :31;
    } bit;
};

/*  structure of pcexy  (2841_C26Ch)    */
union _IoR2yPcexy
{
    unsigned long word;
    struct
    {
        long pcex :9;
        unsigned long :7;
        long pcey :9;
        unsigned long :7;
    } bit;
};

/*  structure of pcec   (2841_C270h)    */
union _IoR2yPcec
{
    unsigned long word;
    struct
    {
        unsigned long pcecof :8;
        unsigned long :8;
        unsigned long pcecga :10;
        unsigned long :6;
    } bit;
};

/*  structure of pceh   (2841_C274h)    */
union _IoR2yPceh
{
    unsigned long word;
    struct
    {
        unsigned long pcehof :8;
        unsigned long :8;
        unsigned long pcehga :10;
        unsigned long :6;
    } bit;
};

KConstType jdsr2y_f2e2_get_type(void);
Jdsr2yF2e2* jdsr2y_f2e2_new(void);

#endif/*__JDSR2Y_F2E2_H__*/

