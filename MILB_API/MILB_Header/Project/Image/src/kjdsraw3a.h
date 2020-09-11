/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSRAW3A Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_JDSRAW3A_H__
#define __K_JDSRAW3A_H__

#include <klib.h>
#include "kjdsraw3a2.h"

#define K_TYPE_JDSRAW3A	(k_jdsraw3a_get_type())
#define K_JDSRAW3A(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsraw3a))
#define K_IS_JDSRAW3A(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSRAW3A))

typedef struct _KJdsraw3a KJdsraw3a;
typedef struct _KJdsraw3aPrivate KJdsraw3aPrivate;

typedef struct _IoRawCode IoRawCode;
typedef struct _IoRawLen IoRawLen;
typedef struct _IoRawLut IoRawLut;
typedef struct _IoJdsraw IoJdsraw;

typedef union _IoRawRctl0 IoRawRctl0;
typedef union _IoRawRctl1 IoRawRctl1;
typedef union _IoRawCond IoRawCond;
typedef union _IoRawRintf IoRawRintf;
typedef union _IoRawRinte IoRawRinte;
typedef union _IoRawHsize IoRawHsize;
typedef union _IoRawVsize IoRawVsize;
typedef union _IoRawDsize IoRawDsize;
typedef union _IoRawMsa IoRawMsa;
typedef union _IoRawMda IoRawMda;
typedef union _IoRawDefinit IoRawDefinit;
typedef union _IoRawClmt IoRawClmt;
typedef union _IoRawCcnt IoRawCcnt;
typedef union _IoRawTblaen IoRawTblaen;
typedef union _IoRawMraxctl IoRawMraxctl;
typedef union _IoRawMwaxctl IoRawMwaxctl;
typedef union _IoRawMraxsts IoRawMraxsts;
typedef union _IoRawMwaxsts IoRawMwaxsts;
typedef union _IoRawCode1 IoRawCode1;
typedef union _IoRawCode2 IoRawCode2;
typedef union _IoRawCode3 IoRawCode3;
typedef union _IoRawCode4 IoRawCode4;
typedef union _IoRawCode5 IoRawCode5;
typedef union _IoRawCode6 IoRawCode6;
typedef union _IoRawCode7 IoRawCode7;
typedef union _IoRawCode8 IoRawCode8;
typedef union _IoRawLen1 IoRawLen1;
typedef union _IoRawLen2 IoRawLen2;
typedef union _IoRawLen3 IoRawLen3;
typedef union _IoRawLen4 IoRawLen4;
typedef union _IoRawLen5 IoRawLen5;
typedef union _IoRawLen6 IoRawLen6;
typedef union _IoRawLen7 IoRawLen7;
typedef union _IoRawLen8 IoRawLen8;
typedef union _IoRawLut1 IoRawLut1;
typedef union _IoRawLut2 IoRawLut2;
typedef union _IoRawLut3 IoRawLut3;
typedef union _IoRawLut4 IoRawLut4;
typedef union _IoRawLut5 IoRawLut5;
typedef union _IoRawLut6 IoRawLut6;
typedef union _IoRawLut7 IoRawLut7;
typedef union _IoRawLut8 IoRawLut8;
typedef union _IoRawLut9 IoRawLut9;
typedef union _IoRawLut10 IoRawLut10;
typedef union _IoRawLut11 IoRawLut11;
typedef union _IoRawLut12 IoRawLut12;
typedef union _IoRawLut13 IoRawLut13;
typedef union _IoRawLut14 IoRawLut14;
typedef union _IoRawLut15 IoRawLut15;
typedef union _IoRawLut16 IoRawLut16;
typedef union _IoRawLut17 IoRawLut17;
typedef union _IoRawLut18 IoRawLut18;
typedef union _IoRawLut19 IoRawLut19;
typedef union _IoRawLut20 IoRawLut20;
typedef union _IoRawLut21 IoRawLut21;
typedef union _IoRawLut22 IoRawLut22;
typedef union _IoRawLut23 IoRawLut23;
typedef union _IoRawLut24 IoRawLut24;
typedef union _IoRawLut25 IoRawLut25;
typedef union _IoRawLut26 IoRawLut26;
typedef union _IoRawLut27 IoRawLut27;
typedef union _IoRawLut28 IoRawLut28;
typedef union _IoRawLut29 IoRawLut29;
typedef union _IoRawLut30 IoRawLut30;
typedef union _IoRawLut31 IoRawLut31;
typedef union _IoRawLut32 IoRawLut32;
typedef union _IoRawLut33 IoRawLut33;
typedef union _IoRawLut34 IoRawLut34;
typedef union _IoRawLut35 IoRawLut35;
typedef union _IoRawLut36 IoRawLut36;
typedef union _IoRawLut37 IoRawLut37;
typedef union _IoRawLut38 IoRawLut38;
typedef union _IoRawLut39 IoRawLut39;
typedef union _IoRawLut40 IoRawLut40;
typedef union _IoRawLut41 IoRawLut41;
typedef union _IoRawLut42 IoRawLut42;
typedef union _IoRawLut43 IoRawLut43;
typedef union _IoRawLut44 IoRawLut44;
typedef union _IoRawLut45 IoRawLut45;
typedef union _IoRawLut46 IoRawLut46;
typedef union _IoRawLut47 IoRawLut47;
typedef union _IoRawLut48 IoRawLut48;
typedef union _IoRawLut49 IoRawLut49;
typedef union _IoRawLut50 IoRawLut50;
typedef union _IoRawLut51 IoRawLut51;
typedef union _IoRawLut52 IoRawLut52;
typedef union _IoRawLut53 IoRawLut53;
typedef union _IoRawLut54 IoRawLut54;
typedef union _IoRawLut55 IoRawLut55;
typedef union _IoRawLut56 IoRawLut56;
typedef union _IoRawLut57 IoRawLut57;
typedef union _IoRawLut58 IoRawLut58;
typedef union _IoRawLut59 IoRawLut59;
typedef union _IoRawLut60 IoRawLut60;
typedef union _IoRawLut61 IoRawLut61;
typedef union _IoRawLut62 IoRawLut62;
typedef union _IoRawLut63 IoRawLut63;
typedef union _IoRawLut64 IoRawLut64;

struct _KJdsraw3a
{
    KObject parent;
};
union _IoRawLut26
{
    unsigned long word;
    struct
    {
        unsigned long lut100 :8;
        unsigned long lut101 :8;
        unsigned long lut102 :8;
        unsigned long lut103 :8;
    } bit;
};
union _IoRawLut27
{
    unsigned long word;
    struct
    {
        unsigned long lut104 :8;
        unsigned long lut105 :8;
        unsigned long lut106 :8;
        unsigned long lut107 :8;
    } bit;
};
union _IoRawLut28
{
    unsigned long word;
    struct
    {
        unsigned long lut108 :8;
        unsigned long lut109 :8;
        unsigned long lut110 :8;
        unsigned long lut111 :8;
    } bit;
};
union _IoRawLut29
{
    unsigned long word;
    struct
    {
        unsigned long lut112 :8;
        unsigned long lut113 :8;
        unsigned long lut114 :8;
        unsigned long lut115 :8;
    } bit;
};
union _IoRawLut30
{
    unsigned long word;
    struct
    {
        unsigned long lut116 :8;
        unsigned long lut117 :8;
        unsigned long lut118 :8;
        unsigned long lut119 :8;
    } bit;
};
union _IoRawLut31
{
    unsigned long word;
    struct
    {
        unsigned long lut120 :8;
        unsigned long lut121 :8;
        unsigned long lut122 :8;
        unsigned long lut123 :8;
    } bit;
};
union _IoRawLut32
{
    unsigned long word;
    struct
    {
        unsigned long lut124 :8;
        unsigned long lut125 :8;
        unsigned long lut126 :8;
        unsigned long lut127 :8;
    } bit;
};
union _IoRawLut33
{
    unsigned long word;
    struct
    {
        unsigned long lut128 :8;
        unsigned long lut129 :8;
        unsigned long lut130 :8;
        unsigned long lut131 :8;
    } bit;
};
union _IoRawLut34
{
    unsigned long word;
    struct
    {
        unsigned long lut132 :8;
        unsigned long lut133 :8;
        unsigned long lut134 :8;
        unsigned long lut135 :8;
    } bit;
};
union _IoRawLut35
{
    unsigned long word;
    struct
    {
        unsigned long lut136 :8;
        unsigned long lut137 :8;
        unsigned long lut138 :8;
        unsigned long lut139 :8;
    } bit;
};
union _IoRawLut36
{
    unsigned long word;
    struct
    {
        unsigned long lut140 :8;
        unsigned long lut141 :8;
        unsigned long lut142 :8;
        unsigned long lut143 :8;
    } bit;
};
union _IoRawLut37
{
    unsigned long word;
    struct
    {
        unsigned long lut144 :8;
        unsigned long lut145 :8;
        unsigned long lut146 :8;
        unsigned long lut147 :8;
    } bit;
};
union _IoRawLut38
{
    unsigned long word;
    struct
    {
        unsigned long lut148 :8;
        unsigned long lut149 :8;
        unsigned long lut150 :8;
        unsigned long lut151 :8;
    } bit;
};
union _IoRawLut39
{
    unsigned long word;
    struct
    {
        unsigned long lut152 :8;
        unsigned long lut153 :8;
        unsigned long lut154 :8;
        unsigned long lut155 :8;
    } bit;
};
union _IoRawLut40
{
    unsigned long word;
    struct
    {
        unsigned long lut156 :8;
        unsigned long lut157 :8;
        unsigned long lut158 :8;
        unsigned long lut159 :8;
    } bit;
};
union _IoRawLut41
{
    unsigned long word;
    struct
    {
        unsigned long lut160 :8;
        unsigned long lut161 :8;
        unsigned long lut162 :8;
        unsigned long lut163 :8;
    } bit;
};
union _IoRawLut42
{
    unsigned long word;
    struct
    {
        unsigned long lut164 :8;
        unsigned long lut165 :8;
        unsigned long lut166 :8;
        unsigned long lut167 :8;
    } bit;
};
union _IoRawLut43
{
    unsigned long word;
    struct
    {
        unsigned long lut168 :8;
        unsigned long lut169 :8;
        unsigned long lut170 :8;
        unsigned long lut171 :8;
    } bit;
};
union _IoRawLut44
{
    unsigned long word;
    struct
    {
        unsigned long lut172 :8;
        unsigned long lut173 :8;
        unsigned long lut174 :8;
        unsigned long lut175 :8;
    } bit;
};
union _IoRawLut45
{
    unsigned long word;
    struct
    {
        unsigned long lut176 :8;
        unsigned long lut177 :8;
        unsigned long lut178 :8;
        unsigned long lut179 :8;
    } bit;
};
union _IoRawLut46
{
    unsigned long word;
    struct
    {
        unsigned long lut180 :8;
        unsigned long lut181 :8;
        unsigned long lut182 :8;
        unsigned long lut183 :8;
    } bit;
};
union _IoRawLut47
{
    unsigned long word;
    struct
    {
        unsigned long lut184 :8;
        unsigned long lut185 :8;
        unsigned long lut186 :8;
        unsigned long lut187 :8;
    } bit;
};
union _IoRawLut48
{
    unsigned long word;
    struct
    {
        unsigned long lut188 :8;
        unsigned long lut189 :8;
        unsigned long lut190 :8;
        unsigned long lut191 :8;
    } bit;
};
union _IoRawLut49
{
    unsigned long word;
    struct
    {
        unsigned long lut192 :8;
        unsigned long lut193 :8;
        unsigned long lut194 :8;
        unsigned long lut195 :8;
    } bit;
};
union _IoRawLut50
{
    unsigned long word;
    struct
    {
        unsigned long lut196 :8;
        unsigned long lut197 :8;
        unsigned long lut198 :8;
        unsigned long lut199 :8;
    } bit;
};
union _IoRawLut51
{
    unsigned long word;
    struct
    {
        unsigned long lut200 :8;
        unsigned long lut201 :8;
        unsigned long lut202 :8;
        unsigned long lut203 :8;
    } bit;
};
union _IoRawLut52
{
    unsigned long word;
    struct
    {
        unsigned long lut204 :8;
        unsigned long lut205 :8;
        unsigned long lut206 :8;
        unsigned long lut207 :8;
    } bit;
};
union _IoRawLut53
{
    unsigned long word;
    struct
    {
        unsigned long lut208 :8;
        unsigned long lut209 :8;
        unsigned long lut210 :8;
        unsigned long lut211 :8;
    } bit;
};
union _IoRawLut54
{
    unsigned long word;
    struct
    {
        unsigned long lut212 :8;
        unsigned long lut213 :8;
        unsigned long lut214 :8;
        unsigned long lut215 :8;
    } bit;
};
union _IoRawLut55
{
    unsigned long word;
    struct
    {
        unsigned long lut216 :8;
        unsigned long lut217 :8;
        unsigned long lut218 :8;
        unsigned long lut219 :8;
    } bit;
};
union _IoRawLut56
{
    unsigned long word;
    struct
    {
        unsigned long lut220 :8;
        unsigned long lut221 :8;
        unsigned long lut222 :8;
        unsigned long lut223 :8;
    } bit;
};
union _IoRawLut57
{
    unsigned long word;
    struct
    {
        unsigned long lut224 :8;
        unsigned long lut225 :8;
        unsigned long lut226 :8;
        unsigned long lut227 :8;
    } bit;
};
union _IoRawLut58
{
    unsigned long word;
    struct
    {
        unsigned long lut228 :8;
        unsigned long lut229 :8;
        unsigned long lut230 :8;
        unsigned long lut231 :8;
    } bit;
};
union _IoRawLut59
{
    unsigned long word;
    struct
    {
        unsigned long lut232 :8;
        unsigned long lut233 :8;
        unsigned long lut234 :8;
        unsigned long lut235 :8;
    } bit;
};
union _IoRawLut60
{
    unsigned long word;
    struct
    {
        unsigned long lut236 :8;
        unsigned long lut237 :8;
        unsigned long lut238 :8;
        unsigned long lut239 :8;
    } bit;
};
union _IoRawLut61
{
    unsigned long word;
    struct
    {
        unsigned long lut240 :8;
        unsigned long lut241 :8;
        unsigned long lut242 :8;
        unsigned long lut243 :8;
    } bit;
};
union _IoRawLut62
{
    unsigned long word;
    struct
    {
        unsigned long lut244 :8;
        unsigned long lut245 :8;
        unsigned long lut246 :8;
        unsigned long lut247 :8;
    } bit;
};
union _IoRawLut63
{
    unsigned long word;
    struct
    {
        unsigned long lut248 :8;
        unsigned long lut249 :8;
        unsigned long lut250 :8;
        unsigned long lut251 :8;
    } bit;
};
union _IoRawLut64
{
    unsigned long word;
    struct
    {
        unsigned long lut252 :8;
        unsigned long lut253 :8;
        unsigned long lut254 :8;
        unsigned long lut255 :8;
    } bit;
};

struct _IoRawCode
{
    IoRawCode1 code1;
    IoRawCode2 code2;
    IoRawCode3 code3;
    IoRawCode4 code4;
    IoRawCode5 code5;
    IoRawCode6 code6;
    IoRawCode7 code7;
    IoRawCode8 code8;
};

struct _IoRawLen
{
    IoRawLen1 len1;
    IoRawLen2 len2;
    IoRawLen3 len3;
    IoRawLen4 len4;
    IoRawLen5 len5;
    IoRawLen6 len6;
    IoRawLen7 len7;
    IoRawLen8 len8;
};

struct _IoRawLut
{
    IoRawLut1 lut1;
    IoRawLut2 lut2;
    IoRawLut3 lut3;
    IoRawLut4 lut4;
    IoRawLut5 lut5;
    IoRawLut6 lut6;
    IoRawLut7 lut7;
    IoRawLut8 lut8;
    IoRawLut9 lut9;
    IoRawLut10 lut10;
    IoRawLut11 lut11;
    IoRawLut12 lut12;
    IoRawLut13 lut13;
    IoRawLut14 lut14;
    IoRawLut15 lut15;
    IoRawLut16 lut16;
    IoRawLut17 lut17;
    IoRawLut18 lut18;
    IoRawLut19 lut19;
    IoRawLut20 lut20;
    IoRawLut21 lut21;
    IoRawLut22 lut22;
    IoRawLut23 lut23;
    IoRawLut24 lut24;
    IoRawLut25 lut25;
    IoRawLut26 lut26;
    IoRawLut27 lut27;
    IoRawLut28 lut28;
    IoRawLut29 lut29;
    IoRawLut30 lut30;
    IoRawLut31 lut31;
    IoRawLut32 lut32;
    IoRawLut33 lut33;
    IoRawLut34 lut34;
    IoRawLut35 lut35;
    IoRawLut36 lut36;
    IoRawLut37 lut37;
    IoRawLut38 lut38;
    IoRawLut39 lut39;
    IoRawLut40 lut40;
    IoRawLut41 lut41;
    IoRawLut42 lut42;
    IoRawLut43 lut43;
    IoRawLut44 lut44;
    IoRawLut45 lut45;
    IoRawLut46 lut46;
    IoRawLut47 lut47;
    IoRawLut48 lut48;
    IoRawLut49 lut49;
    IoRawLut50 lut50;
    IoRawLut51 lut51;
    IoRawLut52 lut52;
    IoRawLut53 lut53;
    IoRawLut54 lut54;
    IoRawLut55 lut55;
    IoRawLut56 lut56;
    IoRawLut57 lut57;
    IoRawLut58 lut58;
    IoRawLut59 lut59;
    IoRawLut60 lut60;
    IoRawLut61 lut61;
    IoRawLut62 lut62;
    IoRawLut63 lut63;
    IoRawLut64 lut64;
};

/* Define i/o mapping */
struct _IoJdsraw
{
    /* JDSIMG */
    IoRawRctl0 rctl0; /* 288A_(0000 - 0003h) */
    IoRawRctl1 rctl1; /* 288A_(0004 - 0007h) */
    IoRawCond cond; /* 288A_(0008 - 000Bh) */
    IoRawRintf rintf; /* 288A_(000C - 000Fh) */

    unsigned char dmy0010003f[0x0040 - 0x0010]; /* 288A_(0010 - 003Fh) */

    IoRawRinte rinte; /* 288A_(0040 - 0043h) */
    IoRawHsize hsize; /* 288A_(0044 - 0047h) */
    IoRawVsize vsize; /* 288A_(0048 - 004Bh) */
    IoRawDsize dsize; /* 288A_(004C - 004Fh) */
    IoRawMsa msa; /* 288A_(0050 - 0053h) */
    IoRawMda mda; /* 288A_(0054 - 0057h) */
    IoRawDefinit definit; /* 288A_(0058 - 005Bh) */
    IoRawClmt clmt; /* 288A_(005C - 005Fh) */
    IoRawCcnt ccnt; /* 288A_(0060 - 0063h) */
    IoRawTblaen tblaen; /* 288A_(0064 - 0067h) */
    IoRawMraxctl mraxctl; /* 288A_(0068 - 006Bh) */
    IoRawMwaxctl mwaxctl; /* 288A_(006C - 006Fh) */
    IoRawMraxsts mraxsts; /* 288A_(0070 - 0073h) */
    IoRawMwaxsts mwaxsts; /* 288A_(0074 - 0077h) */

    unsigned char dmy0078007f[0x0080 - 0x0078]; /* 288A_(0078 - 007Fh) */

    IoRawCode code; /* 288A_(0080 - 009Fh) */
    IoRawLen len; /* 288A_(00A0 - 00BFh) */

    unsigned char dmy00c000ff[0x0100 - 0x00C0]; /* 288A_(00C0 - 00FFh) */

    IoRawLut lut; /* 288A_(0100 - 01FFh) */

    unsigned char dmy288a0200288affff[0x288B0000 - 0x288A0200]; /* 288A_0200 - 288A_FFFFh */

};

extern volatile IoJdsraw ioRaw;

KConstType k_jdsraw3a_get_type(void);
KJdsraw3a* k_jdsraw3a_new(void);

#endif/*__K_JDSRAW3A_H__*/

