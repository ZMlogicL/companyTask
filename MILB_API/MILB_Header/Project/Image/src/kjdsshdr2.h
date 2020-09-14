/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :郑蛘钊
 *@brief             :kjdsshdr2
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_JDSSHDR2_H__
#define __K_JDSSHDR2_H__


#include <klib.h>


#define K_TYPE_JDSSHDR2	                (k_jdsshdr2_get_type())
#define K_JDSSHDR2(obj)	                (K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsshdr2))
#define K_IS_JDSSHDR2(obj)	            (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSSHDR2))


typedef struct _KJdsshdr2               KJdsshdr2;
typedef struct _KJdsshdr2Private        KJdsshdr2Private;

typedef union _IoShdrShdractl0          IoShdrShdractl0;
typedef union _IoShdrShdractl1          IoShdrShdractl1;
typedef union _IoShdrShdractl2          IoShdrShdractl2;
typedef union _IoShdrShdrint0           IoShdrShdrint0;
typedef union _IoShdrShdrint1           IoShdrShdrint1;
typedef union _IoShdrAxmd               IoShdrAxmd;
typedef union _IoShdrAxictlara          IoShdrAxictlara;
typedef union _IoShdrAxictlarb          IoShdrAxictlarb;
typedef union _IoShdrAxictlarc          IoShdrAxictlarc;
typedef union _IoShdrAxictlard          IoShdrAxictlard;
typedef union _IoShdrAxictlawa          IoShdrAxictlawa;
typedef union _IoShdrAxictlawb          IoShdrAxictlawb;
typedef union _IoShdrAxictlawc          IoShdrAxictlawc;
typedef union _IoShdrAxictlra           IoShdrAxictlra;
typedef union _IoShdrAxictlrb           IoShdrAxictlrb;
typedef union _IoShdrAxictlrc           IoShdrAxictlrc;
typedef union _IoShdrAxictlrd           IoShdrAxictlrd;
typedef union _IoShdrAxictlwa           IoShdrAxictlwa;
typedef union _IoShdrAxictlwb           IoShdrAxictlwb;
typedef union _IoShdrAxictlwc           IoShdrAxictlwc;
typedef union _IoShdrCoremon0           IoShdrCoremon0;
typedef union _IoShdrCoremon1           IoShdrCoremon1;
typedef union _IoShdrDgtRsel            IoShdrDgtRsel;
typedef union _IoShdrSdrrAddrA          IoShdrSdrrAddrA;
typedef union _IoShdrSdrrAddrB          IoShdrSdrrAddrB;
typedef union _IoShdrSdrrAddrC          IoShdrSdrrAddrC;
typedef union _IoShdrSdrrAddrD          IoShdrSdrrAddrD;
typedef union _IoShdrSdrrAddrE          IoShdrSdrrAddrE;
typedef union _IoShdrSdrrAddrF          IoShdrSdrrAddrF;
typedef union _IoShdrSdrrGhsizeA        IoShdrSdrrGhsizeA;
typedef union _IoShdrSdrrGhsizeB        IoShdrSdrrGhsizeB;
typedef union _IoShdrSdrrGhsizeC        IoShdrSdrrGhsizeC;
typedef union _IoShdrSdrrGhsizeD        IoShdrSdrrGhsizeD;
typedef union _IoShdrSdrrGhsizeE        IoShdrSdrrGhsizeE;
typedef union _IoShdrSdrrGhsizeF        IoShdrSdrrGhsizeF;
typedef union _IoShdrSdrrVfm            IoShdrSdrrVfm;
typedef union _IoShdrSdrwAddrB          IoShdrSdrwAddrB;
typedef union _IoShdrSdrwAddrE          IoShdrSdrwAddrE;
typedef union _IoShdrSdrwAddrF          IoShdrSdrwAddrF;
typedef union _IoShdrSdrwAddrG          IoShdrSdrwAddrG;
typedef union _IoShdrSdrwAddrH          IoShdrSdrwAddrH;
typedef union _IoShdrSdrwAddrI          IoShdrSdrwAddrI;
typedef union _IoShdrSdrwGhsizeB        IoShdrSdrwGhsizeB;
typedef union _IoShdrSdrwGhsizeE        IoShdrSdrwGhsizeE;
typedef union _IoShdrSdrwGhsizeF        IoShdrSdrwGhsizeF;
typedef union _IoShdrSdrwGhsizeG        IoShdrSdrwGhsizeG;
typedef union _IoShdrSdrwGhsizeH        IoShdrSdrwGhsizeH;
typedef union _IoShdrSdrwGhsizeI        IoShdrSdrwGhsizeI;
typedef union _IoShdrSdrwVfm            IoShdrSdrwVfm;
typedef union _IoShdrSdrwBaA            IoShdrSdrwBaA;
typedef union _IoShdrSdrwBaC            IoShdrSdrwBaC;
typedef union _IoShdrSdrwBaD            IoShdrSdrwBaD;
typedef union _IoShdrSdrwFwA            IoShdrSdrwFwA;
typedef union _IoShdrSdrwFwC            IoShdrSdrwFwC;
typedef union _IoShdrSdrwFwD            IoShdrSdrwFwD;


struct _KJdsshdr2
{
    KObject parent;
};


/*  structure of shdractl0      */
union _IoShdrShdractl0
{
    kulong word;
    struct
    {
        kulong sr :1;
        kulong :31;
    } bit;
};

/*  structure of shdractl1      */
union _IoShdrShdractl1
{
    kulong word;
    struct
    {
        kulong trg :2;
        kulong :30;
    } bit;
};

/*  structure of shdractl2      */
union _IoShdrShdractl2
{
    kulong word;
    struct
    {
        kulong sramaen :1;
        kulong :31;
    } bit;
};

/*  structure of shdrint0       */
union _IoShdrShdrint0
{
    kulong word;
    struct
    {
        kulong shdren :1;
        kulong :3;
        kulong axreen :1;
        kulong axween :1;
        kulong :26;
    } bit;
};

/*  structure of shdrint1       */
union _IoShdrShdrint1
{
    kulong word;
    struct
    {
        kulong shdrflg :1;
        kulong :3;
        kulong axreflg :1;
        kulong axweflg :1;
        kulong :26;
    } bit;
};

/*  structure of axmd           */
union _IoShdrAxmd
{
    kulong word;
    struct
    {
        kulong burstr :2;
        kulong :2;
        kulong burstw :2;
        kulong :2;
        kulong wstbmsk :1;
        kulong :23;
    } bit;
};

/*  structure of axictlara      */
union _IoShdrAxictlara
{
    kulong word;
    struct
    {
        kulong arcachea0 :4;
        kulong arprota0 :3;
        kulong :1;
        kulong arcachea1 :4;
        kulong arprota1 :3;
        kulong :1;
        kulong :16;
    } bit;
};

/*  structure of axictlarb      */
union _IoShdrAxictlarb
{
    kulong word;
    struct
    {
        kulong arcacheb0 :4;
        kulong arprotb0 :3;
        kulong :1;
        kulong arcacheb1 :4;
        kulong arprotb1 :3;
        kulong :1;
        kulong :16;
    } bit;
};

/*  structure of axictlarc      */
union _IoShdrAxictlarc
{
    kulong word;
    struct
    {
        kulong arcachec0 :4;
        kulong arprotc0 :3;
        kulong :1;
        kulong arcachec1 :4;
        kulong arprotc1 :3;
        kulong :1;
        kulong arcachec2 :4;
        kulong arprotc2 :3;
        kulong :1;
        kulong arcachec3 :4;
        kulong arprotc3 :3;
        kulong :1;
    } bit;
};

/*  structure of axictlard      */
union _IoShdrAxictlard
{
    kulong word;
    struct
    {
        kulong arcached0 :4;
        kulong arprotd0 :3;
        kulong :1;
        kulong arcached1 :4;
        kulong arprotd1 :3;
        kulong :1;
        kulong :16;
    } bit;
};

/*  structure of AXICTLAW_A     */
union _IoShdrAxictlawa
{
    kulong word;
    struct
    {
        kulong awcache0 :4;
        kulong awprot0 :3;
        kulong :1;
        kulong awcache1 :4;
        kulong awprot1 :3;
        kulong :1;
        kulong awcache2 :4;
        kulong awprot2 :3;
        kulong :1;
        kulong awcache3 :4;
        kulong awprot3 :3;
        kulong :1;
    } bit;
};

/*  structure of AXICTLAW_B     */
union _IoShdrAxictlawb
{
    kulong word[2];
    struct
    {
        kulong awcache0 :4;
        kulong awprot0 :3;
        kulong :1;
        kulong awcache1 :4;
        kulong awprot1 :3;
        kulong :1;
        kulong awcache2 :4;
        kulong awprot2 :3;
        kulong :1;
        kulong awcache3 :4;
        kulong awprot3 :3;
        kulong :1;
        kulong awcache4 :4;
        kulong awprot4 :3;
        kulong :1;
        kulong awcache5 :4;
        kulong awprot5 :3;
        kulong :1;
        kulong :16;
    } bit;
};

/*  structure of AXICTLAW_C     */
union _IoShdrAxictlawc
{
    kulong word[2];
    struct
    {
        kulong awcache0 :4;
        kulong awprot0 :3;
        kulong :1;
        kulong awcache1 :4;
        kulong awprot1 :3;
        kulong :1;
        kulong awcache2 :4;
        kulong awprot2 :3;
        kulong :1;
        kulong awcache3 :4;
        kulong awprot3 :3;
        kulong :1;
        kulong awcache4 :4;
        kulong awprot4 :3;
        kulong :1;
        kulong awcache5 :4;
        kulong awprot5 :3;
        kulong :1;
        kulong awcache6 :4;
        kulong awprot6 :3;
        kulong :1;
        kulong :8;
    } bit;
};

/*  structure of axictlra       */
union _IoShdrAxictlra
{
    kulong word;
    struct
    {
        kulong rrespa0 :2;
        kulong :6;
        kulong rrespa1 :2;
        kulong :6;
        kulong :16;
    } bit;
};

/*  structure of axictlrb       */
union _IoShdrAxictlrb
{
    kulong word;
    struct
    {
        kulong rrespb0 :2;
        kulong :6;
        kulong rrespb1 :2;
        kulong :6;
        kulong :16;
    } bit;
};

/*  structure of axictlrc       */
union _IoShdrAxictlrc
{
    kulong word;
    struct
    {
        kulong rrespc0 :2;
        kulong :6;
        kulong rrespc1 :2;
        kulong :6;
        kulong rrespc2 :2;
        kulong :6;
        kulong rrespc3 :2;
        kulong :6;
    } bit;
};

/*  structure of axictlrd       */
union _IoShdrAxictlrd
{
    kulong word;
    struct
    {
        kulong rrespd0 :2;
        kulong :6;
        kulong rrespd1 :2;
        kulong :6;
        kulong :16;
    } bit;
};

/*  structure of axictlwa   */
union _IoShdrAxictlwa
{
    kulong word;
    struct
    {
        kulong brespa0 :2;
        kulong :6;
        kulong brespa1 :2;
        kulong :6;
        kulong brespa2 :2;
        kulong :6;
        kulong brespa3 :2;
        kulong :6;
    } bit;
};

/*  structure of axictlwb   */
union _IoShdrAxictlwb
{
    kulong word[2];
    struct
    {
        kulong brespb0 :2;
        kulong :6;
        kulong brespb1 :2;
        kulong :6;
        kulong brespb2 :2;
        kulong :6;
        kulong brespb3 :2;
        kulong :6;
        kulong brespb4 :2;
        kulong :6;
        kulong brespb5 :2;
        kulong :6;
        kulong :16;
    } bit;
};

/*  structure of axictlwc   */
union _IoShdrAxictlwc
{
    kulong word[2];
    struct
    {
        kulong brespc0 :2;
        kulong :6;
        kulong brespc1 :2;
        kulong :6;
        kulong brespc2 :2;
        kulong :6;
        kulong brespc3 :2;
        kulong :6;
        kulong brespc4 :2;
        kulong :6;
        kulong brespc5 :2;
        kulong :6;
        kulong brespc6 :2;
        kulong :6;
        kulong :8;
    } bit;
};

/*  structure of coremon0   */
union _IoShdrCoremon0
{
    kulong word;
    struct
    {
        kulong monIlinnum :11;
        kulong :1;
        kulong :4;
        kulong monIthnum :4;
        kulong :4;
        kulong monItvnum :5;
        kulong :3;
    } bit;
};

/*  structure of coremon1       */
union _IoShdrCoremon1
{
    kulong word;
    struct
    {
        kulong monOlinnum :11;
        kulong :1;
        kulong :4;
        kulong monOthnum :4;
        kulong :4;
        kulong monOtvnum :5;
        kulong :3;
    } bit;
};

/*  structure of dgtRsel       */
union _IoShdrDgtRsel
{
    kulong word;
    struct
    {
        kulong dgtRsel :3;
        kulong :29;
    } bit;
};

/*  structure of sdrrAddrA    */
union _IoShdrSdrrAddrA
{
    kulong word[2];
    struct
    {
        kulong sdrrAddrA0 :32;
        kulong sdrrAddrA1 :32;
    } bit;
};

/*  structure of sdrrAddrB    */
union _IoShdrSdrrAddrB
{
    kulong word[2];
    struct
    {
        kulong sdrrAddrB0 :32;
        kulong sdrrAddrB1 :32;
    } bit;
};

/*  structure of sdrrAddrC    */
union _IoShdrSdrrAddrC
{
    kulong word[2];
    struct
    {
        kulong sdrrAddrC0 :32;
        kulong sdrrAddrC1 :32;
    } bit;
};

/*  structure of sdrrAddrD    */
union _IoShdrSdrrAddrD
{
    kulong word[2];
    struct
    {
        kulong sdrrAddrD0 :32;
        kulong sdrrAddrD1 :32;
    } bit;
};

/*  structure of sdrrAddrE    */
union _IoShdrSdrrAddrE
{
    kulong word[2];
    struct
    {
        kulong sdrrAddrE0 :32;
        kulong sdrrAddrE1 :32;
    } bit;
};

/*  structure of sdrrAddrF    */
union _IoShdrSdrrAddrF
{
    kulong word;
    struct
    {
        kulong sdrrAddrF0 :32;
    } bit;
};

/*  structure of sdrrGhsizeA  */
union _IoShdrSdrrGhsizeA
{
    kulong word[2];
    struct
    {
        kulong sdrrGhsizeA0 :16;
        kulong :16;
        kulong sdrrGhsizeA1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrrGhsizeB  */
union _IoShdrSdrrGhsizeB
{
    kulong word[2];
    struct
    {
        kulong sdrrGhsizeB0 :16;
        kulong :16;
        kulong sdrrGhsizeB1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrrGhsizeC  */
union _IoShdrSdrrGhsizeC
{
    kulong word[2];
    struct
    {
        kulong sdrrGhsizeC0 :16;
        kulong :16;
        kulong sdrrGhsizeC1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrrGhsizeD  */
union _IoShdrSdrrGhsizeD
{
    kulong word[2];
    struct
    {
        kulong sdrrGhsizeD0 :16;
        kulong :16;
        kulong sdrrGhsizeD1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrrGhsizeE  */
union _IoShdrSdrrGhsizeE
{
    kulong word[2];
    struct
    {
        kulong sdrrGhsizeE0 :16;
        kulong :16;
        kulong sdrrGhsizeE1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrrGhsizeF  */
union _IoShdrSdrrGhsizeF
{
    kulong word;
    struct
    {
        kulong sdrrGhsizeF0 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrrVfm       */
union _IoShdrSdrrVfm
{
    kulong word;
    struct
    {
        kulong sdrrVfmA :1;
        kulong :15;
        kulong :1;
        kulong :15;
    } bit;
};

/*  structure of sdrwAddrB    */
union _IoShdrSdrwAddrB
{
    kulong word[2];
    struct
    {
        kulong sdrwAddrB0 :32;
        kulong sdrwAddrB1 :32;
    } bit;
};

/*  structure of sdrwAddrE    */
union _IoShdrSdrwAddrE
{
    kulong word[2];
    struct
    {
        kulong sdrwAddrE0 :32;
        kulong sdrwAddrE1 :32;
    } bit;
};

/*  structure of sdrwAddrF    */
union _IoShdrSdrwAddrF
{
    kulong word[2];
    struct
    {
        kulong sdrwAddrF0 :32;
        kulong sdrwAddrF1 :32;
    } bit;
};

/*  structure of sdrwAddrG    */
union _IoShdrSdrwAddrG
{
    kulong word[3];
    struct
    {
        kulong sdrwAddrG0 :32;
        kulong sdrwAddrG1 :32;
        kulong sdrwAddrG2 :32;
    } bit;
};

/*  structure of sdrwAddrH    */
union _IoShdrSdrwAddrH
{
    kulong word[2];
    struct
    {
        kulong sdrwAddrH0 :32;
        kulong sdrwAddrH1 :32;
    } bit;
};

/*  structure of sdrwAddrI    */
union _IoShdrSdrwAddrI
{
    kulong word;
    struct
    {
        kulong sdrwAddrI0 :32;
    } bit;
};

/*  structure of sdrwGhsizeB  */
union _IoShdrSdrwGhsizeB
{
    kulong word[2];
    struct
    {
        kulong sdrwGhsizeB0 :16;
        kulong :16;
        kulong sdrwGhsizeB1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrwGhsizeE  */
union _IoShdrSdrwGhsizeE
{
    kulong word[2];
    struct
    {
        kulong sdrwGhsizeE0 :16;
        kulong :16;
        kulong sdrwGhsizeE1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrwGhsizeF  */
union _IoShdrSdrwGhsizeF
{
    kulong word[2];
    struct
    {
        kulong sdrwGhsizeF0 :16;
        kulong :16;
        kulong sdrwGhsizeF1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrwGhsizeG  */
union _IoShdrSdrwGhsizeG
{
    kulong word[3];
    struct
    {
        kulong sdrwGhsizeG0 :16;
        kulong :16;
        kulong sdrwGhsizeG1 :16;
        kulong :16;
        kulong sdrwGhsizeG2 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrwGhsizeH  */
union _IoShdrSdrwGhsizeH
{
    kulong word[2];
    struct
    {
        kulong sdrwGhsizeH0 :16;
        kulong :16;
        kulong sdrwGhsizeH1 :16;
        kulong :16;
    } bit;
};

/*  structure of sdrwGhsizeI  */
union _IoShdrSdrwGhsizeI
{
    kulong word;
    struct
    {
        kulong sdrwGhsizeI0 :15;
        kulong sdrwVfmA :1;
        kulong :16;
    } bit;
};

/*  structure of sdrwVfm       */
union _IoShdrSdrwVfm
{
    kulong word;
    struct
    {
        kulong :4;
        kulong sdrwVfmB :1;
        kulong :27;
    } bit;
};

/*  structure of sdrwBaA      */
union _IoShdrSdrwBaA
{
    kulong word[2];
    struct
    {
        kulong sdrwBaA0 :32;
        kulong sdrwBaA1 :32;
    } bit;
};

/*  structure of sdrwBaC      */
union _IoShdrSdrwBaC
{
    kulong word[2];
    struct
    {
        kulong sdrwBaC0 :32;
        kulong sdrwBaC1 :32;
    } bit;
};

/*  structure of sdrwBaD      */
union _IoShdrSdrwBaD
{
    kulong word[2];
    struct
    {
        kulong sdrwBaD0 :32;
        kulong sdrwBaD1 :32;
    } bit;
};

/*  structure of sdrwFwA      */
union _IoShdrSdrwFwA
{
    kulong word;
    struct
    {
        kulong sdrwFwA :16;
        kulong :16;
    } bit;
};

/*  structure of sdrwFwC      */
union _IoShdrSdrwFwC
{
    kulong word;
    struct
    {
        kulong sdrwFwC :16;
        kulong :16;
    } bit;
};

/*  structure of sdrwFwD      */
union _IoShdrSdrwFwD
{
    kulong word;
    struct
    {
        kulong sdrwFwD :16;
        kulong :16;
    } bit;
};


KConstType k_jdsshdr2_get_type(void);
KJdsshdr2* k_jdsshdr2_new(void);


#endif/*__K_JDSSHDR2_H__*/
