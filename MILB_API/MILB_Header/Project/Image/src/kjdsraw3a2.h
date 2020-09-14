/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-11
 *@author            :郑蛘钊
 *@brief             :kjdsraw3a2
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_JDSRAW3A2_H__
#define __K_JDSRAW3A2_H__


#include <klib.h>


#define K_TYPE_JDSRAW3A2	        (k_jdsraw3a2_get_type())
#define K_JDSRAW3A2(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsraw3a2))
#define K_IS_JDSRAW3A2(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSRAW3A2))


typedef struct _KJdsraw3a2          KJdsraw3a2;
typedef struct _KJdsraw3a2Private   KJdsraw3a2Private;


struct _KJdsraw3a2
{
    KObject parent;
};


/*  structure of rctl0  (288A_0000h)    */
union _IoRawRctl0
{
    kulong word;
    struct
    {
        kulong sr :1;
        kulong :31;
    } bit;
};

/*  structure of rctl1  (288A_0004h)    */
union _IoRawRctl1
{
    kulong word;
    struct
    {
        kulong rtrg :2;
        kulong :2;
        kulong luten :1;
        kulong defop :1;
        kulong deffc :1;
        kulong byts :1;
        kulong rfmt :2;
        kulong opmd :1;
        kulong :1;
        kulong bitsel :1;
        kulong :19;
    } bit;
};

/*  structure of cond   (288A_0008h)    */
union _IoRawCond
{
    kulong word;
    struct
    {
        kulong cond :3;
        kulong :29;
    } bit;
};

/*  structure of rintf  (288A_000Ch)    */
union _IoRawRintf
{
    kulong word;
    struct
    {
        kulong rf :1;
        kulong :3;
        kulong raxerf :1;
        kulong waxerf :1;
        kulong :26;
    } bit;
};

/*  structure of rinte  (288A_0040h)    */
union _IoRawRinte
{
    kulong word;
    struct
    {
        kulong re :1;
        kulong :3;
        kulong raxere :1;
        kulong waxere :1;
        kulong :26;
    } bit;
};

/*  structure of hsize  (288A_0044h)    */
union _IoRawHsize
{
    kulong word;
    struct
    {
        kulong hsize :14;
        kulong :18;
    } bit;
};

/*  structure of vsize  (288A_0048h)    */
union _IoRawVsize
{
    kulong word;
    struct
    {
        kulong vsize :14;
        kulong :18;
    } bit;
};

/*  structure of dsize  (288A_004Ch)    */
union _IoRawDsize
{
    kulong word;
    struct
    {
        kulong dsize :24;
        kulong :8;
    } bit;
};

/*  structure of msa    (288A_0050h)    */
union _IoRawMsa
{
    kulong word;
    struct
    {
        kulong msa :32;
    } bit;
};

/*  structure of mda    (288A_0054h)    */
union _IoRawMda
{
    kulong word;
    struct
    {
        kulong mda :32;
    } bit;
};

/*  structure of definit    (288A_0058h)    */
union _IoRawDefinit
{
    kulong word;
    struct
    {
        kulong definit :14;
        kulong :18;
    } bit;
};

/*  structure of clmt   (288A_005Ch)    */
union _IoRawClmt
{
    kulong word;
    struct
    {
        kulong clmt :29;
        kulong :3;
    } bit;
};

/*  structure of ccnt   (288A_0060h)    */
union _IoRawCcnt
{
    kulong word;
    struct
    {
        kulong ccnt :29;
        kulong :3;
    } bit;
};

/*  structure of tblaen (288A_0064h)    */
union _IoRawTblaen
{
    kulong word;
    struct
    {
        kulong tblaen :1;
        kulong :31;
    } bit;
};

/*  structure of mraxctl    (288A_0068h)    */
union _IoRawMraxctl
{
    kulong word;
    struct
    {
        kulong mrcache :4;
        kulong mrprot :3;
        kulong :25;
    } bit;
};

/*  structure of mwaxctl    (288A_006Ch)    */
union _IoRawMwaxctl
{
    kulong word;
    struct
    {
        kulong mwcache :4;
        kulong mwprot :3;
        kulong :25;
    } bit;
};

/*  structure of mraxsts    (288A_0070h)    */
union _IoRawMraxsts
{
    kulong word;
    struct
    {
        kulong rresp :2;
        kulong :30;
    } bit;
};

/*  structure of mwaxsts    (288A_0074h)    */
union _IoRawMwaxsts
{
    kulong word;
    struct
    {
        kulong bresp :2;
        kulong :30;
    } bit;
};

/*  structure of code   (288A_0080h)    */
union _IoRawCode1
{
    kulong word;
    struct
    {
        kulong code0 :16;
        kulong code1 :16;
    } bit;
};

union _IoRawCode2
{
    kulong word;
    struct
    {
        kulong code2 :16;
        kulong code3 :16;
    } bit;
};

union _IoRawCode3
{
    kulong word;
    struct
    {
        kulong code4 :16;
        kulong code5 :16;
    } bit;
};

union _IoRawCode4
{
    kulong word;
    struct
    {
        kulong code6 :16;
        kulong code7 :16;
    } bit;
};

union _IoRawCode5
{
    kulong word;
    struct
    {
        kulong code8 :16;
        kulong code9 :16;
    } bit;
};

union _IoRawCode6
{
    kulong word;
    struct
    {
        kulong codea :16;
        kulong codeb :16;
    } bit;
};

union _IoRawCode7
{
    kulong word;
    struct
    {
        kulong codec :16;
        kulong coded :16;
    } bit;
};

union _IoRawCode8
{
    kulong word;
    struct
    {
        kulong codee :16;
        kulong :16;
    } bit;
};

/*  structure of len    (288A_00A0h)    */
union _IoRawLen1
{
    kulong word;
    struct
    {
        kulong len0 :16;
        kulong len1 :16;
    } bit;
};

union _IoRawLen2
{
    kulong word;
    struct
    {
        kulong len2 :16;
        kulong len3 :16;
    } bit;
};

union _IoRawLen3
{
    kulong word;
    struct
    {
        kulong len4 :16;
        kulong len5 :16;
    } bit;
};

union _IoRawLen4
{
    kulong word;
    struct
    {
        kulong len6 :16;
        kulong len7 :16;
    } bit;
};

union _IoRawLen5
{
    kulong word;
    struct
    {
        kulong len8 :16;
        kulong len9 :16;
    } bit;
};

union _IoRawLen6
{
    kulong word;
    struct
    {
        kulong lena :16;
        kulong lenb :16;
    } bit;
};

union _IoRawLen7
{
    kulong word;
    struct
    {
        kulong lenc :16;
        kulong lend :16;
    } bit;
};

union _IoRawLen8
{
    kulong word;
    struct
    {
        kulong lene :16;
        kulong :16;
    } bit;
};

/*  structure of lut    (288A_0100h)    */
union _IoRawLut1
{
    kulong word;
    struct
    {
        kulong lut0 :8;
        kulong lut1 :8;
        kulong lut2 :8;
        kulong lut3 :8;
    } bit;
};

union _IoRawLut2
{
    kulong word;
    struct
    {
        kulong lut4 :8;
        kulong lut5 :8;
        kulong lut6 :8;
        kulong lut7 :8;
    } bit;
};

union _IoRawLut3
{
    kulong word;
    struct
    {
        kulong lut8 :8;
        kulong lut9 :8;
        kulong lut10 :8;
        kulong lut11 :8;
    } bit;
};

union _IoRawLut4
{
    kulong word;
    struct
    {
        kulong lut12 :8;
        kulong lut13 :8;
        kulong lut14 :8;
        kulong lut15 :8;
    } bit;
};

union _IoRawLut5
{
    kulong word;
    struct
    {
        kulong lut16 :8;
        kulong lut17 :8;
        kulong lut18 :8;
        kulong lut19 :8;
    } bit;
};

union _IoRawLut6
{
    kulong word;
    struct
    {
        kulong lut20 :8;
        kulong lut21 :8;
        kulong lut22 :8;
        kulong lut23 :8;
    } bit;
};

union _IoRawLut7
{
    kulong word;
    struct
    {
        kulong lut24 :8;
        kulong lut25 :8;
        kulong lut26 :8;
        kulong lut27 :8;
    } bit;
};

union _IoRawLut8
{
    kulong word;
    struct
    {
        kulong lut28 :8;
        kulong lut29 :8;
        kulong lut30 :8;
        kulong lut31 :8;
    } bit;
};

union _IoRawLut9
{
    kulong word;
    struct
    {
        kulong lut32 :8;
        kulong lut33 :8;
        kulong lut34 :8;
        kulong lut35 :8;
    } bit;
};

union _IoRawLut10
{
    kulong word;
    struct
    {
        kulong lut36 :8;
        kulong lut37 :8;
        kulong lut38 :8;
        kulong lut39 :8;
    } bit;
};

union _IoRawLut11
{
    kulong word;
    struct
    {
        kulong lut40 :8;
        kulong lut41 :8;
        kulong lut42 :8;
        kulong lut43 :8;
    } bit;
};

union _IoRawLut12
{
    kulong word;
    struct
    {
        kulong lut44 :8;
        kulong lut45 :8;
        kulong lut46 :8;
        kulong lut47 :8;
    } bit;
};

union _IoRawLut13
{
    kulong word;
    struct
    {
        kulong lut48 :8;
        kulong lut49 :8;
        kulong lut50 :8;
        kulong lut51 :8;
    } bit;
};

union _IoRawLut14
{
    kulong word;
    struct
    {
        kulong lut52 :8;
        kulong lut53 :8;
        kulong lut54 :8;
        kulong lut55 :8;
    } bit;
};

union _IoRawLut15
{
    kulong word;
    struct
    {
        kulong lut56 :8;
        kulong lut57 :8;
        kulong lut58 :8;
        kulong lut59 :8;
    } bit;
};

union _IoRawLut16
{
    kulong word;
    struct
    {
        kulong lut60 :8;
        kulong lut61 :8;
        kulong lut62 :8;
        kulong lut63 :8;
    } bit;
};

union _IoRawLut17
{
    kulong word;
    struct
    {
        kulong lut64 :8;
        kulong lut65 :8;
        kulong lut66 :8;
        kulong lut67 :8;
    } bit;
};

union _IoRawLut18
{
    kulong word;
    struct
    {
        kulong lut68 :8;
        kulong lut69 :8;
        kulong lut70 :8;
        kulong lut71 :8;
    } bit;
};

union _IoRawLut19
{
    kulong word;
    struct
    {
        kulong lut72 :8;
        kulong lut73 :8;
        kulong lut74 :8;
        kulong lut75 :8;
    } bit;
};

union _IoRawLut20
{
    kulong word;
    struct
    {
        kulong lut76 :8;
        kulong lut77 :8;
        kulong lut78 :8;
        kulong lut79 :8;
    } bit;
};

union _IoRawLut21
{
    kulong word;
    struct
    {
        kulong lut80 :8;
        kulong lut81 :8;
        kulong lut82 :8;
        kulong lut83 :8;
    } bit;
};

union _IoRawLut22
{
    kulong word;
    struct
    {
        kulong lut84 :8;
        kulong lut85 :8;
        kulong lut86 :8;
        kulong lut87 :8;
    } bit;
};

union _IoRawLut23
{
    kulong word;
    struct
    {
        kulong lut88 :8;
        kulong lut89 :8;
        kulong lut90 :8;
        kulong lut91 :8;
    } bit;
};

union _IoRawLut24
{
    kulong word;
    struct
    {
        kulong lut92 :8;
        kulong lut93 :8;
        kulong lut94 :8;
        kulong lut95 :8;
    } bit;
};

union _IoRawLut25
{
    kulong word;
    struct
    {
        kulong lut96 :8;
        kulong lut97 :8;
        kulong lut98 :8;
        kulong lut99 :8;
    } bit;
};


KConstType k_jdsraw3a2_get_type(void);
KJdsraw3a2* k_jdsraw3a2_new(void);


#endif/*__K_JDSRAW3A2_H__*/
