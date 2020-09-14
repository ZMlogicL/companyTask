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


#define K_TYPE_JDSRAW3A	            (k_jdsraw3a_get_type())
#define K_JDSRAW3A(obj)	            (K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsraw3a))
#define K_IS_JDSRAW3A(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSRAW3A))


typedef struct _KJdsraw3a           KJdsraw3a;
typedef struct _KJdsraw3aPrivate    KJdsraw3aPrivate;

typedef struct _IoRawCode           IoRawCode;
typedef struct _IoRawLen            IoRawLen;
typedef struct _IoRawLut            IoRawLut;
typedef struct _IoJdsraw            IoJdsraw;

typedef union _IoRawRctl0           IoRawRctl0;
typedef union _IoRawRctl1           IoRawRctl1;
typedef union _IoRawCond            IoRawCond;
typedef union _IoRawRintf           IoRawRintf;
typedef union _IoRawRinte           IoRawRinte;
typedef union _IoRawHsize           IoRawHsize;
typedef union _IoRawVsize           IoRawVsize;
typedef union _IoRawDsize           IoRawDsize;
typedef union _IoRawMsa             IoRawMsa;
typedef union _IoRawMda             IoRawMda;
typedef union _IoRawDefinit         IoRawDefinit;
typedef union _IoRawClmt            IoRawClmt;
typedef union _IoRawCcnt            IoRawCcnt;
typedef union _IoRawTblaen          IoRawTblaen;
typedef union _IoRawMraxctl         IoRawMraxctl;
typedef union _IoRawMwaxctl         IoRawMwaxctl;
typedef union _IoRawMraxsts         IoRawMraxsts;
typedef union _IoRawMwaxsts         IoRawMwaxsts;
typedef union _IoRawCode1           IoRawCode1;
typedef union _IoRawCode2           IoRawCode2;
typedef union _IoRawCode3           IoRawCode3;
typedef union _IoRawCode4           IoRawCode4;
typedef union _IoRawCode5           IoRawCode5;
typedef union _IoRawCode6           IoRawCode6;
typedef union _IoRawCode7           IoRawCode7;
typedef union _IoRawCode8           IoRawCode8;
typedef union _IoRawLen1            IoRawLen1;
typedef union _IoRawLen2            IoRawLen2;
typedef union _IoRawLen3            IoRawLen3;
typedef union _IoRawLen4            IoRawLen4;
typedef union _IoRawLen5            IoRawLen5;
typedef union _IoRawLen6            IoRawLen6;
typedef union _IoRawLen7            IoRawLen7;
typedef union _IoRawLen8            IoRawLen8;
typedef union _IoRawLut1            IoRawLut1;
typedef union _IoRawLut2            IoRawLut2;
typedef union _IoRawLut3            IoRawLut3;
typedef union _IoRawLut4            IoRawLut4;
typedef union _IoRawLut5            IoRawLut5;
typedef union _IoRawLut6            IoRawLut6;
typedef union _IoRawLut7            IoRawLut7;
typedef union _IoRawLut8            IoRawLut8;
typedef union _IoRawLut9            IoRawLut9;
typedef union _IoRawLut10           IoRawLut10;
typedef union _IoRawLut11           IoRawLut11;
typedef union _IoRawLut12           IoRawLut12;
typedef union _IoRawLut13           IoRawLut13;
typedef union _IoRawLut14           IoRawLut14;
typedef union _IoRawLut15           IoRawLut15;
typedef union _IoRawLut16           IoRawLut16;
typedef union _IoRawLut17           IoRawLut17;
typedef union _IoRawLut18           IoRawLut18;
typedef union _IoRawLut19           IoRawLut19;
typedef union _IoRawLut20           IoRawLut20;
typedef union _IoRawLut21           IoRawLut21;
typedef union _IoRawLut22           IoRawLut22;
typedef union _IoRawLut23           IoRawLut23;
typedef union _IoRawLut24           IoRawLut24;
typedef union _IoRawLut25           IoRawLut25;
typedef union _IoRawLut26           IoRawLut26;
typedef union _IoRawLut27           IoRawLut27;
typedef union _IoRawLut28           IoRawLut28;
typedef union _IoRawLut29           IoRawLut29;
typedef union _IoRawLut30           IoRawLut30;
typedef union _IoRawLut31           IoRawLut31;
typedef union _IoRawLut32           IoRawLut32;
typedef union _IoRawLut33           IoRawLut33;
typedef union _IoRawLut34           IoRawLut34;
typedef union _IoRawLut35           IoRawLut35;
typedef union _IoRawLut36           IoRawLut36;
typedef union _IoRawLut37           IoRawLut37;
typedef union _IoRawLut38           IoRawLut38;
typedef union _IoRawLut39           IoRawLut39;
typedef union _IoRawLut40           IoRawLut40;
typedef union _IoRawLut41           IoRawLut41;
typedef union _IoRawLut42           IoRawLut42;
typedef union _IoRawLut43           IoRawLut43;
typedef union _IoRawLut44           IoRawLut44;
typedef union _IoRawLut45           IoRawLut45;
typedef union _IoRawLut46           IoRawLut46;
typedef union _IoRawLut47           IoRawLut47;
typedef union _IoRawLut48           IoRawLut48;
typedef union _IoRawLut49           IoRawLut49;
typedef union _IoRawLut50           IoRawLut50;
typedef union _IoRawLut51           IoRawLut51;
typedef union _IoRawLut52           IoRawLut52;
typedef union _IoRawLut53           IoRawLut53;
typedef union _IoRawLut54           IoRawLut54;
typedef union _IoRawLut55           IoRawLut55;
typedef union _IoRawLut56           IoRawLut56;
typedef union _IoRawLut57           IoRawLut57;
typedef union _IoRawLut58           IoRawLut58;
typedef union _IoRawLut59           IoRawLut59;
typedef union _IoRawLut60           IoRawLut60;
typedef union _IoRawLut61           IoRawLut61;
typedef union _IoRawLut62           IoRawLut62;
typedef union _IoRawLut63           IoRawLut63;
typedef union _IoRawLut64           IoRawLut64;


struct _KJdsraw3a
{
    KObject parent;
};


union _IoRawLut26
{
    kulong word;
    struct
    {
        kulong lut100 :8;
        kulong lut101 :8;
        kulong lut102 :8;
        kulong lut103 :8;
    } bit;
};

union _IoRawLut27
{
    kulong word;
    struct
    {
        kulong lut104 :8;
        kulong lut105 :8;
        kulong lut106 :8;
        kulong lut107 :8;
    } bit;
};

union _IoRawLut28
{
    kulong word;
    struct
    {
        kulong lut108 :8;
        kulong lut109 :8;
        kulong lut110 :8;
        kulong lut111 :8;
    } bit;
};

union _IoRawLut29
{
    kulong word;
    struct
    {
        kulong lut112 :8;
        kulong lut113 :8;
        kulong lut114 :8;
        kulong lut115 :8;
    } bit;
};

union _IoRawLut30
{
    kulong word;
    struct
    {
        kulong lut116 :8;
        kulong lut117 :8;
        kulong lut118 :8;
        kulong lut119 :8;
    } bit;
};

union _IoRawLut31
{
    kulong word;
    struct
    {
        kulong lut120 :8;
        kulong lut121 :8;
        kulong lut122 :8;
        kulong lut123 :8;
    } bit;
};

union _IoRawLut32
{
    kulong word;
    struct
    {
        kulong lut124 :8;
        kulong lut125 :8;
        kulong lut126 :8;
        kulong lut127 :8;
    } bit;
};

union _IoRawLut33
{
    kulong word;
    struct
    {
        kulong lut128 :8;
        kulong lut129 :8;
        kulong lut130 :8;
        kulong lut131 :8;
    } bit;
};

union _IoRawLut34
{
    kulong word;
    struct
    {
        kulong lut132 :8;
        kulong lut133 :8;
        kulong lut134 :8;
        kulong lut135 :8;
    } bit;
};

union _IoRawLut35
{
    kulong word;
    struct
    {
        kulong lut136 :8;
        kulong lut137 :8;
        kulong lut138 :8;
        kulong lut139 :8;
    } bit;
};

union _IoRawLut36
{
    kulong word;
    struct
    {
        kulong lut140 :8;
        kulong lut141 :8;
        kulong lut142 :8;
        kulong lut143 :8;
    } bit;
};

union _IoRawLut37
{
    kulong word;
    struct
    {
        kulong lut144 :8;
        kulong lut145 :8;
        kulong lut146 :8;
        kulong lut147 :8;
    } bit;
};

union _IoRawLut38
{
    kulong word;
    struct
    {
        kulong lut148 :8;
        kulong lut149 :8;
        kulong lut150 :8;
        kulong lut151 :8;
    } bit;
};

union _IoRawLut39
{
    kulong word;
    struct
    {
        kulong lut152 :8;
        kulong lut153 :8;
        kulong lut154 :8;
        kulong lut155 :8;
    } bit;
};

union _IoRawLut40
{
    kulong word;
    struct
    {
        kulong lut156 :8;
        kulong lut157 :8;
        kulong lut158 :8;
        kulong lut159 :8;
    } bit;
};

union _IoRawLut41
{
    kulong word;
    struct
    {
        kulong lut160 :8;
        kulong lut161 :8;
        kulong lut162 :8;
        kulong lut163 :8;
    } bit;
};

union _IoRawLut42
{
    kulong word;
    struct
    {
        kulong lut164 :8;
        kulong lut165 :8;
        kulong lut166 :8;
        kulong lut167 :8;
    } bit;
};

union _IoRawLut43
{
    kulong word;
    struct
    {
        kulong lut168 :8;
        kulong lut169 :8;
        kulong lut170 :8;
        kulong lut171 :8;
    } bit;
};

union _IoRawLut44
{
    kulong word;
    struct
    {
        kulong lut172 :8;
        kulong lut173 :8;
        kulong lut174 :8;
        kulong lut175 :8;
    } bit;
};

union _IoRawLut45
{
    kulong word;
    struct
    {
        kulong lut176 :8;
        kulong lut177 :8;
        kulong lut178 :8;
        kulong lut179 :8;
    } bit;
};

union _IoRawLut46
{
    kulong word;
    struct
    {
        kulong lut180 :8;
        kulong lut181 :8;
        kulong lut182 :8;
        kulong lut183 :8;
    } bit;
};

union _IoRawLut47
{
    kulong word;
    struct
    {
        kulong lut184 :8;
        kulong lut185 :8;
        kulong lut186 :8;
        kulong lut187 :8;
    } bit;
};

union _IoRawLut48
{
    kulong word;
    struct
    {
        kulong lut188 :8;
        kulong lut189 :8;
        kulong lut190 :8;
        kulong lut191 :8;
    } bit;
};

union _IoRawLut49
{
    kulong word;
    struct
    {
        kulong lut192 :8;
        kulong lut193 :8;
        kulong lut194 :8;
        kulong lut195 :8;
    } bit;
};

union _IoRawLut50
{
    kulong word;
    struct
    {
        kulong lut196 :8;
        kulong lut197 :8;
        kulong lut198 :8;
        kulong lut199 :8;
    } bit;
};

union _IoRawLut51
{
    kulong word;
    struct
    {
        kulong lut200 :8;
        kulong lut201 :8;
        kulong lut202 :8;
        kulong lut203 :8;
    } bit;
};

union _IoRawLut52
{
    kulong word;
    struct
    {
        kulong lut204 :8;
        kulong lut205 :8;
        kulong lut206 :8;
        kulong lut207 :8;
    } bit;
};

union _IoRawLut53
{
    kulong word;
    struct
    {
        kulong lut208 :8;
        kulong lut209 :8;
        kulong lut210 :8;
        kulong lut211 :8;
    } bit;
};

union _IoRawLut54
{
    kulong word;
    struct
    {
        kulong lut212 :8;
        kulong lut213 :8;
        kulong lut214 :8;
        kulong lut215 :8;
    } bit;
};

union _IoRawLut55
{
    kulong word;
    struct
    {
        kulong lut216 :8;
        kulong lut217 :8;
        kulong lut218 :8;
        kulong lut219 :8;
    } bit;
};

union _IoRawLut56
{
    kulong word;
    struct
    {
        kulong lut220 :8;
        kulong lut221 :8;
        kulong lut222 :8;
        kulong lut223 :8;
    } bit;
};

union _IoRawLut57
{
    kulong word;
    struct
    {
        kulong lut224 :8;
        kulong lut225 :8;
        kulong lut226 :8;
        kulong lut227 :8;
    } bit;
};

union _IoRawLut58
{
    kulong word;
    struct
    {
        kulong lut228 :8;
        kulong lut229 :8;
        kulong lut230 :8;
        kulong lut231 :8;
    } bit;
};

union _IoRawLut59
{
    kulong word;
    struct
    {
        kulong lut232 :8;
        kulong lut233 :8;
        kulong lut234 :8;
        kulong lut235 :8;
    } bit;
};

union _IoRawLut60
{
    kulong word;
    struct
    {
        kulong lut236 :8;
        kulong lut237 :8;
        kulong lut238 :8;
        kulong lut239 :8;
    } bit;
};

union _IoRawLut61
{
    kulong word;
    struct
    {
        kulong lut240 :8;
        kulong lut241 :8;
        kulong lut242 :8;
        kulong lut243 :8;
    } bit;
};

union _IoRawLut62
{
    kulong word;
    struct
    {
        kulong lut244 :8;
        kulong lut245 :8;
        kulong lut246 :8;
        kulong lut247 :8;
    } bit;
};

union _IoRawLut63
{
    kulong word;
    struct
    {
        kulong lut248 :8;
        kulong lut249 :8;
        kulong lut250 :8;
        kulong lut251 :8;
    } bit;
};

union _IoRawLut64
{
    kulong word;
    struct
    {
        kulong lut252 :8;
        kulong lut253 :8;
        kulong lut254 :8;
        kulong lut255 :8;
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

    kuchar dmy0010003f[0x0040 - 0x0010]; /* 288A_(0010 - 003Fh) */

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

    kuchar dmy0078007f[0x0080 - 0x0078]; /* 288A_(0078 - 007Fh) */

    IoRawCode code; /* 288A_(0080 - 009Fh) */
    IoRawLen len; /* 288A_(00A0 - 00BFh) */

    kuchar dmy00c000ff[0x0100 - 0x00C0]; /* 288A_(00C0 - 00FFh) */

    IoRawLut lut; /* 288A_(0100 - 01FFh) */

    kuchar dmy288a0200288affff[0x288B0000 - 0x288A0200]; /* 288A_0200 - 288A_FFFFh */

};


extern volatile IoJdsraw ioRaw;


KConstType k_jdsraw3a_get_type(void);
KJdsraw3a* k_jdsraw3a_new(void);


#endif/*__K_JDSRAW3A_H__*/
