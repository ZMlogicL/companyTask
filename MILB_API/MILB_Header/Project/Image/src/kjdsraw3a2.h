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

#define K_TYPE_JDSRAW3A2	(k_jdsraw3a2_get_type())
#define K_JDSRAW3A2(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsraw3a2))
#define K_IS_JDSRAW3A2(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSRAW3A2))

typedef struct _KJdsraw3a2 KJdsraw3a2;
typedef struct _KJdsraw3a2Private KJdsraw3a2Private;

struct _KJdsraw3a2
{
    KObject parent;
};

/*  structure of rctl0  (288A_0000h)    */
union _IoRawRctl0
{
    unsigned long word;
    struct
    {
        unsigned long sr :1;
        unsigned long :31;
    } bit;
};

/*  structure of rctl1  (288A_0004h)    */
union _IoRawRctl1
{
    unsigned long word;
    struct
    {
        unsigned long rtrg :2;
        unsigned long :2;
        unsigned long luten :1;
        unsigned long defop :1;
        unsigned long deffc :1;
        unsigned long byts :1;
        unsigned long rfmt :2;
        unsigned long opmd :1;
        unsigned long :1;
        unsigned long bitsel :1;
        unsigned long :19;
    } bit;
};

/*  structure of cond   (288A_0008h)    */
union _IoRawCond
{
    unsigned long word;
    struct
    {
        unsigned long cond :3;
        unsigned long :29;
    } bit;
};

/*  structure of rintf  (288A_000Ch)    */
union _IoRawRintf
{
    unsigned long word;
    struct
    {
        unsigned long rf :1;
        unsigned long :3;
        unsigned long raxerf :1;
        unsigned long waxerf :1;
        unsigned long :26;
    } bit;
};

/*  structure of rinte  (288A_0040h)    */
union _IoRawRinte
{
    unsigned long word;
    struct
    {
        unsigned long re :1;
        unsigned long :3;
        unsigned long raxere :1;
        unsigned long waxere :1;
        unsigned long :26;
    } bit;
};

/*  structure of hsize  (288A_0044h)    */
union _IoRawHsize
{
    unsigned long word;
    struct
    {
        unsigned long hsize :14;
        unsigned long :18;
    } bit;
};

/*  structure of vsize  (288A_0048h)    */
union _IoRawVsize
{
    unsigned long word;
    struct
    {
        unsigned long vsize :14;
        unsigned long :18;
    } bit;
};

/*  structure of dsize  (288A_004Ch)    */
union _IoRawDsize
{
    unsigned long word;
    struct
    {
        unsigned long dsize :24;
        unsigned long :8;
    } bit;
};

/*  structure of msa    (288A_0050h)    */
union _IoRawMsa
{
    unsigned long word;
    struct
    {
        unsigned long msa :32;
    } bit;
};

/*  structure of mda    (288A_0054h)    */
union _IoRawMda
{
    unsigned long word;
    struct
    {
        unsigned long mda :32;
    } bit;
};

/*  structure of definit    (288A_0058h)    */
union _IoRawDefinit
{
    unsigned long word;
    struct
    {
        unsigned long definit :14;
        unsigned long :18;
    } bit;
};

/*  structure of clmt   (288A_005Ch)    */
union _IoRawClmt
{
    unsigned long word;
    struct
    {
        unsigned long clmt :29;
        unsigned long :3;
    } bit;
};

/*  structure of ccnt   (288A_0060h)    */
union _IoRawCcnt
{
    unsigned long word;
    struct
    {
        unsigned long ccnt :29;
        unsigned long :3;
    } bit;
};

/*  structure of tblaen (288A_0064h)    */
union _IoRawTblaen
{
    unsigned long word;
    struct
    {
        unsigned long tblaen :1;
        unsigned long :31;
    } bit;
};

/*  structure of mraxctl    (288A_0068h)    */
union _IoRawMraxctl
{
    unsigned long word;
    struct
    {
        unsigned long mrcache :4;
        unsigned long mrprot :3;
        unsigned long :25;
    } bit;
};

/*  structure of mwaxctl    (288A_006Ch)    */
union _IoRawMwaxctl
{
    unsigned long word;
    struct
    {
        unsigned long mwcache :4;
        unsigned long mwprot :3;
        unsigned long :25;
    } bit;
};

/*  structure of mraxsts    (288A_0070h)    */
union _IoRawMraxsts
{
    unsigned long word;
    struct
    {
        unsigned long rresp :2;
        unsigned long :30;
    } bit;
};

/*  structure of mwaxsts    (288A_0074h)    */
union _IoRawMwaxsts
{
    unsigned long word;
    struct
    {
        unsigned long bresp :2;
        unsigned long :30;
    } bit;
};

/*  structure of code   (288A_0080h)    */
union _IoRawCode1
{
    unsigned long word;
    struct
    {
        unsigned long code0 :16;
        unsigned long code1 :16;
    } bit;
};
union _IoRawCode2
{
    unsigned long word;
    struct
    {
        unsigned long code2 :16;
        unsigned long code3 :16;
    } bit;
};
union _IoRawCode3
{
    unsigned long word;
    struct
    {
        unsigned long code4 :16;
        unsigned long code5 :16;
    } bit;
};
union _IoRawCode4
{
    unsigned long word;
    struct
    {
        unsigned long code6 :16;
        unsigned long code7 :16;
    } bit;
};
union _IoRawCode5
{
    unsigned long word;
    struct
    {
        unsigned long code8 :16;
        unsigned long code9 :16;
    } bit;
};
union _IoRawCode6
{
    unsigned long word;
    struct
    {
        unsigned long codea :16;
        unsigned long codeb :16;
    } bit;
};
union _IoRawCode7
{
    unsigned long word;
    struct
    {
        unsigned long codec :16;
        unsigned long coded :16;
    } bit;
};
union _IoRawCode8
{
    unsigned long word;
    struct
    {
        unsigned long codee :16;
        unsigned long :16;
    } bit;
};

/*  structure of len    (288A_00A0h)    */
union _IoRawLen1
{
    unsigned long word;
    struct
    {
        unsigned long len0 :16;
        unsigned long len1 :16;
    } bit;
};
union _IoRawLen2
{
    unsigned long word;
    struct
    {
        unsigned long len2 :16;
        unsigned long len3 :16;
    } bit;
};
union _IoRawLen3
{
    unsigned long word;
    struct
    {
        unsigned long len4 :16;
        unsigned long len5 :16;
    } bit;
};
union _IoRawLen4
{
    unsigned long word;
    struct
    {
        unsigned long len6 :16;
        unsigned long len7 :16;
    } bit;
};
union _IoRawLen5
{
    unsigned long word;
    struct
    {
        unsigned long len8 :16;
        unsigned long len9 :16;
    } bit;
};
union _IoRawLen6
{
    unsigned long word;
    struct
    {
        unsigned long lena :16;
        unsigned long lenb :16;
    } bit;
};
union _IoRawLen7
{
    unsigned long word;
    struct
    {
        unsigned long lenc :16;
        unsigned long lend :16;
    } bit;
};
union _IoRawLen8
{
    unsigned long word;
    struct
    {
        unsigned long lene :16;
        unsigned long :16;
    } bit;
};

/*  structure of lut    (288A_0100h)    */
union _IoRawLut1
{
    unsigned long word;
    struct
    {
        unsigned long lut0 :8;
        unsigned long lut1 :8;
        unsigned long lut2 :8;
        unsigned long lut3 :8;
    } bit;
};
union _IoRawLut2
{
    unsigned long word;
    struct
    {
        unsigned long lut4 :8;
        unsigned long lut5 :8;
        unsigned long lut6 :8;
        unsigned long lut7 :8;
    } bit;
};
union _IoRawLut3
{
    unsigned long word;
    struct
    {
        unsigned long lut8 :8;
        unsigned long lut9 :8;
        unsigned long lut10 :8;
        unsigned long lut11 :8;
    } bit;
};
union _IoRawLut4
{
    unsigned long word;
    struct
    {
        unsigned long lut12 :8;
        unsigned long lut13 :8;
        unsigned long lut14 :8;
        unsigned long lut15 :8;
    } bit;
};
union _IoRawLut5
{
    unsigned long word;
    struct
    {
        unsigned long lut16 :8;
        unsigned long lut17 :8;
        unsigned long lut18 :8;
        unsigned long lut19 :8;
    } bit;
};
union _IoRawLut6
{
    unsigned long word;
    struct
    {
        unsigned long lut20 :8;
        unsigned long lut21 :8;
        unsigned long lut22 :8;
        unsigned long lut23 :8;
    } bit;
};
union _IoRawLut7
{
    unsigned long word;
    struct
    {
        unsigned long lut24 :8;
        unsigned long lut25 :8;
        unsigned long lut26 :8;
        unsigned long lut27 :8;
    } bit;
};
union _IoRawLut8
{
    unsigned long word;
    struct
    {
        unsigned long lut28 :8;
        unsigned long lut29 :8;
        unsigned long lut30 :8;
        unsigned long lut31 :8;
    } bit;
};
union _IoRawLut9
{
    unsigned long word;
    struct
    {
        unsigned long lut32 :8;
        unsigned long lut33 :8;
        unsigned long lut34 :8;
        unsigned long lut35 :8;
    } bit;
};
union _IoRawLut10
{
    unsigned long word;
    struct
    {
        unsigned long lut36 :8;
        unsigned long lut37 :8;
        unsigned long lut38 :8;
        unsigned long lut39 :8;
    } bit;
};
union _IoRawLut11
{
    unsigned long word;
    struct
    {
        unsigned long lut40 :8;
        unsigned long lut41 :8;
        unsigned long lut42 :8;
        unsigned long lut43 :8;
    } bit;
};
union _IoRawLut12
{
    unsigned long word;
    struct
    {
        unsigned long lut44 :8;
        unsigned long lut45 :8;
        unsigned long lut46 :8;
        unsigned long lut47 :8;
    } bit;
};
union _IoRawLut13
{
    unsigned long word;
    struct
    {
        unsigned long lut48 :8;
        unsigned long lut49 :8;
        unsigned long lut50 :8;
        unsigned long lut51 :8;
    } bit;
};
union _IoRawLut14
{
    unsigned long word;
    struct
    {
        unsigned long lut52 :8;
        unsigned long lut53 :8;
        unsigned long lut54 :8;
        unsigned long lut55 :8;
    } bit;
};
union _IoRawLut15
{
    unsigned long word;
    struct
    {
        unsigned long lut56 :8;
        unsigned long lut57 :8;
        unsigned long lut58 :8;
        unsigned long lut59 :8;
    } bit;
};
union _IoRawLut16
{
    unsigned long word;
    struct
    {
        unsigned long lut60 :8;
        unsigned long lut61 :8;
        unsigned long lut62 :8;
        unsigned long lut63 :8;
    } bit;
};
union _IoRawLut17
{
    unsigned long word;
    struct
    {
        unsigned long lut64 :8;
        unsigned long lut65 :8;
        unsigned long lut66 :8;
        unsigned long lut67 :8;
    } bit;
};
union _IoRawLut18
{
    unsigned long word;
    struct
    {
        unsigned long lut68 :8;
        unsigned long lut69 :8;
        unsigned long lut70 :8;
        unsigned long lut71 :8;
    } bit;
};
union _IoRawLut19
{
    unsigned long word;
    struct
    {
        unsigned long lut72 :8;
        unsigned long lut73 :8;
        unsigned long lut74 :8;
        unsigned long lut75 :8;
    } bit;
};

union _IoRawLut20
{
    unsigned long word;
    struct
    {
        unsigned long lut76 :8;
        unsigned long lut77 :8;
        unsigned long lut78 :8;
        unsigned long lut79 :8;
    } bit;
};
union _IoRawLut21
{
    unsigned long word;
    struct
    {
        unsigned long lut80 :8;
        unsigned long lut81 :8;
        unsigned long lut82 :8;
        unsigned long lut83 :8;
    } bit;
};
union _IoRawLut22
{
    unsigned long word;
    struct
    {
        unsigned long lut84 :8;
        unsigned long lut85 :8;
        unsigned long lut86 :8;
        unsigned long lut87 :8;
    } bit;
};
union _IoRawLut23
{
    unsigned long word;
    struct
    {
        unsigned long lut88 :8;
        unsigned long lut89 :8;
        unsigned long lut90 :8;
        unsigned long lut91 :8;
    } bit;
};
union _IoRawLut24
{
    unsigned long word;
    struct
    {
        unsigned long lut92 :8;
        unsigned long lut93 :8;
        unsigned long lut94 :8;
        unsigned long lut95 :8;
    } bit;
};
union _IoRawLut25
{
    unsigned long word;
    struct
    {
        unsigned long lut96 :8;
        unsigned long lut97 :8;
        unsigned long lut98 :8;
        unsigned long lut99 :8;
    } bit;
};

KConstType k_jdsraw3a2_get_type(void);
KJdsraw3a2* k_jdsraw3a2_new(void);

#endif/*__K_JDSRAW3A2_H__*/

