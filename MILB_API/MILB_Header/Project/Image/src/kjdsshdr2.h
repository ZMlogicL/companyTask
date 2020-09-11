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

#define K_TYPE_JDSSHDR2	(k_jdsshdr2_get_type())
#define K_JDSSHDR2(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsshdr2))
#define K_IS_JDSSHDR2(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSSHDR2))

typedef struct _KJdsshdr2 KJdsshdr2;
typedef struct _KJdsshdr2Private KJdsshdr2Private;

typedef union _IoShdrShdractl0 IoShdrShdractl0;
typedef union _IoShdrShdractl1 IoShdrShdractl1;
typedef union _IoShdrShdractl2 IoShdrShdractl2;
typedef union _IoShdrShdrint0 IoShdrShdrint0;
typedef union _IoShdrShdrint1 IoShdrShdrint1;
typedef union _IoShdrAxmd IoShdrAxmd;
typedef union _IoShdrAxictlara IoShdrAxictlara;
typedef union _IoShdrAxictlarb IoShdrAxictlarb;
typedef union _IoShdrAxictlarc IoShdrAxictlarc;
typedef union _IoShdrAxictlard IoShdrAxictlard;
typedef union _IoShdrAxictlawa IoShdrAxictlawa;
typedef union _IoShdrAxictlawb IoShdrAxictlawb;
typedef union _IoShdrAxictlawc IoShdrAxictlawc;
typedef union _IoShdrAxictlra IoShdrAxictlra;
typedef union _IoShdrAxictlrb IoShdrAxictlrb;
typedef union _IoShdrAxictlrc IoShdrAxictlrc;
typedef union _IoShdrAxictlrd IoShdrAxictlrd;
typedef union _IoShdrAxictlwa IoShdrAxictlwa;
typedef union _IoShdrAxictlwb IoShdrAxictlwb;
typedef union _IoShdrAxictlwc IoShdrAxictlwc;
typedef union _IoShdrCoremon0 IoShdrCoremon0;
typedef union _IoShdrCoremon1 IoShdrCoremon1;
typedef union _IoShdrDgtRsel IoShdrDgtRsel;
typedef union _IoShdrSdrrAddrA IoShdrSdrrAddrA;
typedef union _IoShdrSdrrAddrB IoShdrSdrrAddrB;
typedef union _IoShdrSdrrAddrC IoShdrSdrrAddrC;
typedef union _IoShdrSdrrAddrD IoShdrSdrrAddrD;
typedef union _IoShdrSdrrAddrE IoShdrSdrrAddrE;
typedef union _IoShdrSdrrAddrF IoShdrSdrrAddrF;
typedef union _IoShdrSdrrGhsizeA IoShdrSdrrGhsizeA;
typedef union _IoShdrSdrrGhsizeB IoShdrSdrrGhsizeB;
typedef union _IoShdrSdrrGhsizeC IoShdrSdrrGhsizeC;
typedef union _IoShdrSdrrGhsizeD IoShdrSdrrGhsizeD;
typedef union _IoShdrSdrrGhsizeE IoShdrSdrrGhsizeE;
typedef union _IoShdrSdrrGhsizeF IoShdrSdrrGhsizeF;
typedef union _IoShdrSdrrVfm IoShdrSdrrVfm;
typedef union _IoShdrSdrwAddrB IoShdrSdrwAddrB;
typedef union _IoShdrSdrwAddrE IoShdrSdrwAddrE;
typedef union _IoShdrSdrwAddrF IoShdrSdrwAddrF;
typedef union _IoShdrSdrwAddrG IoShdrSdrwAddrG;
typedef union _IoShdrSdrwAddrH IoShdrSdrwAddrH;
typedef union _IoShdrSdrwAddrI IoShdrSdrwAddrI;
typedef union _IoShdrSdrwGhsizeB IoShdrSdrwGhsizeB;
typedef union _IoShdrSdrwGhsizeE IoShdrSdrwGhsizeE;
typedef union _IoShdrSdrwGhsizeF IoShdrSdrwGhsizeF;
typedef union _IoShdrSdrwGhsizeG IoShdrSdrwGhsizeG;
typedef union _IoShdrSdrwGhsizeH IoShdrSdrwGhsizeH;
typedef union _IoShdrSdrwGhsizeI IoShdrSdrwGhsizeI;
typedef union _IoShdrSdrwVfm IoShdrSdrwVfm;
typedef union _IoShdrSdrwBaA IoShdrSdrwBaA;
typedef union _IoShdrSdrwBaC IoShdrSdrwBaC;
typedef union _IoShdrSdrwBaD IoShdrSdrwBaD;
typedef union _IoShdrSdrwFwA IoShdrSdrwFwA;
typedef union _IoShdrSdrwFwC IoShdrSdrwFwC;
typedef union _IoShdrSdrwFwD IoShdrSdrwFwD;

struct _KJdsshdr2
{
    KObject parent;
};

/*  structure of shdractl0      */
union _IoShdrShdractl0
{
    unsigned long word;
    struct
    {
        unsigned long sr :1;
        unsigned long :31;
    } bit;
};

/*  structure of shdractl1      */
union _IoShdrShdractl1
{
    unsigned long word;
    struct
    {
        unsigned long trg :2;
        unsigned long :30;
    } bit;
};

/*  structure of shdractl2      */
union _IoShdrShdractl2
{
    unsigned long word;
    struct
    {
        unsigned long sramaen :1;
        unsigned long :31;
    } bit;
};

/*  structure of shdrint0       */
union _IoShdrShdrint0
{
    unsigned long word;
    struct
    {
        unsigned long shdren :1;
        unsigned long :3;
        unsigned long axreen :1;
        unsigned long axween :1;
        unsigned long :26;
    } bit;
};

/*  structure of shdrint1       */
union _IoShdrShdrint1
{
    unsigned long word;
    struct
    {
        unsigned long shdrflg :1;
        unsigned long :3;
        unsigned long axreflg :1;
        unsigned long axweflg :1;
        unsigned long :26;
    } bit;
};

/*  structure of axmd           */
union _IoShdrAxmd
{
    unsigned long word;
    struct
    {
        unsigned long burstr :2;
        unsigned long :2;
        unsigned long burstw :2;
        unsigned long :2;
        unsigned long wstbmsk :1;
        unsigned long :23;
    } bit;
};

/*  structure of axictlara      */
union _IoShdrAxictlara
{
    unsigned long word;
    struct
    {
        unsigned long arcachea0 :4;
        unsigned long arprota0 :3;
        unsigned long :1;
        unsigned long arcachea1 :4;
        unsigned long arprota1 :3;
        unsigned long :1;
        unsigned long :16;
    } bit;
};

/*  structure of axictlarb      */
union _IoShdrAxictlarb
{
    unsigned long word;
    struct
    {
        unsigned long arcacheb0 :4;
        unsigned long arprotb0 :3;
        unsigned long :1;
        unsigned long arcacheb1 :4;
        unsigned long arprotb1 :3;
        unsigned long :1;
        unsigned long :16;
    } bit;
};

/*  structure of axictlarc      */
union _IoShdrAxictlarc
{
    unsigned long word;
    struct
    {
        unsigned long arcachec0 :4;
        unsigned long arprotc0 :3;
        unsigned long :1;
        unsigned long arcachec1 :4;
        unsigned long arprotc1 :3;
        unsigned long :1;
        unsigned long arcachec2 :4;
        unsigned long arprotc2 :3;
        unsigned long :1;
        unsigned long arcachec3 :4;
        unsigned long arprotc3 :3;
        unsigned long :1;
    } bit;
};

/*  structure of axictlard      */
union _IoShdrAxictlard
{
    unsigned long word;
    struct
    {
        unsigned long arcached0 :4;
        unsigned long arprotd0 :3;
        unsigned long :1;
        unsigned long arcached1 :4;
        unsigned long arprotd1 :3;
        unsigned long :1;
        unsigned long :16;
    } bit;
};

/*  structure of AXICTLAW_A     */
union _IoShdrAxictlawa
{
    unsigned long word;
    struct
    {
        unsigned long awcache0 :4;
        unsigned long awprot0 :3;
        unsigned long :1;
        unsigned long awcache1 :4;
        unsigned long awprot1 :3;
        unsigned long :1;
        unsigned long awcache2 :4;
        unsigned long awprot2 :3;
        unsigned long :1;
        unsigned long awcache3 :4;
        unsigned long awprot3 :3;
        unsigned long :1;
    } bit;
};

/*  structure of AXICTLAW_B     */
union _IoShdrAxictlawb
{
    unsigned long word[2];
    struct
    {
        unsigned long awcache0 :4;
        unsigned long awprot0 :3;
        unsigned long :1;
        unsigned long awcache1 :4;
        unsigned long awprot1 :3;
        unsigned long :1;
        unsigned long awcache2 :4;
        unsigned long awprot2 :3;
        unsigned long :1;
        unsigned long awcache3 :4;
        unsigned long awprot3 :3;
        unsigned long :1;
        unsigned long awcache4 :4;
        unsigned long awprot4 :3;
        unsigned long :1;
        unsigned long awcache5 :4;
        unsigned long awprot5 :3;
        unsigned long :1;
        unsigned long :16;
    } bit;
};

/*  structure of AXICTLAW_C     */
union _IoShdrAxictlawc
{
    unsigned long word[2];
    struct
    {
        unsigned long awcache0 :4;
        unsigned long awprot0 :3;
        unsigned long :1;
        unsigned long awcache1 :4;
        unsigned long awprot1 :3;
        unsigned long :1;
        unsigned long awcache2 :4;
        unsigned long awprot2 :3;
        unsigned long :1;
        unsigned long awcache3 :4;
        unsigned long awprot3 :3;
        unsigned long :1;
        unsigned long awcache4 :4;
        unsigned long awprot4 :3;
        unsigned long :1;
        unsigned long awcache5 :4;
        unsigned long awprot5 :3;
        unsigned long :1;
        unsigned long awcache6 :4;
        unsigned long awprot6 :3;
        unsigned long :1;
        unsigned long :8;
    } bit;
};

/*  structure of axictlra       */
union _IoShdrAxictlra
{
    unsigned long word;
    struct
    {
        unsigned long rrespa0 :2;
        unsigned long :6;
        unsigned long rrespa1 :2;
        unsigned long :6;
        unsigned long :16;
    } bit;
};

/*  structure of axictlrb       */
union _IoShdrAxictlrb
{
    unsigned long word;
    struct
    {
        unsigned long rrespb0 :2;
        unsigned long :6;
        unsigned long rrespb1 :2;
        unsigned long :6;
        unsigned long :16;
    } bit;
};

/*  structure of axictlrc       */
union _IoShdrAxictlrc
{
    unsigned long word;
    struct
    {
        unsigned long rrespc0 :2;
        unsigned long :6;
        unsigned long rrespc1 :2;
        unsigned long :6;
        unsigned long rrespc2 :2;
        unsigned long :6;
        unsigned long rrespc3 :2;
        unsigned long :6;
    } bit;
};

/*  structure of axictlrd       */
union _IoShdrAxictlrd
{
    unsigned long word;
    struct
    {
        unsigned long rrespd0 :2;
        unsigned long :6;
        unsigned long rrespd1 :2;
        unsigned long :6;
        unsigned long :16;
    } bit;
};

/*  structure of axictlwa   */
union _IoShdrAxictlwa
{
    unsigned long word;
    struct
    {
        unsigned long brespa0 :2;
        unsigned long :6;
        unsigned long brespa1 :2;
        unsigned long :6;
        unsigned long brespa2 :2;
        unsigned long :6;
        unsigned long brespa3 :2;
        unsigned long :6;
    } bit;
};

/*  structure of axictlwb   */
union _IoShdrAxictlwb
{
    unsigned long word[2];
    struct
    {
        unsigned long brespb0 :2;
        unsigned long :6;
        unsigned long brespb1 :2;
        unsigned long :6;
        unsigned long brespb2 :2;
        unsigned long :6;
        unsigned long brespb3 :2;
        unsigned long :6;
        unsigned long brespb4 :2;
        unsigned long :6;
        unsigned long brespb5 :2;
        unsigned long :6;
        unsigned long :16;
    } bit;
};

/*  structure of axictlwc   */
union _IoShdrAxictlwc
{
    unsigned long word[2];
    struct
    {
        unsigned long brespc0 :2;
        unsigned long :6;
        unsigned long brespc1 :2;
        unsigned long :6;
        unsigned long brespc2 :2;
        unsigned long :6;
        unsigned long brespc3 :2;
        unsigned long :6;
        unsigned long brespc4 :2;
        unsigned long :6;
        unsigned long brespc5 :2;
        unsigned long :6;
        unsigned long brespc6 :2;
        unsigned long :6;
        unsigned long :8;
    } bit;
};

/*  structure of coremon0   */
union _IoShdrCoremon0
{
    unsigned long word;
    struct
    {
        unsigned long monIlinnum :11;
        unsigned long :1;
        unsigned long :4;
        unsigned long monIthnum :4;
        unsigned long :4;
        unsigned long monItvnum :5;
        unsigned long :3;
    } bit;
};

/*  structure of coremon1       */
union _IoShdrCoremon1
{
    unsigned long word;
    struct
    {
        unsigned long monOlinnum :11;
        unsigned long :1;
        unsigned long :4;
        unsigned long monOthnum :4;
        unsigned long :4;
        unsigned long monOtvnum :5;
        unsigned long :3;
    } bit;
};

/*  structure of dgtRsel       */
union _IoShdrDgtRsel
{
    unsigned long word;
    struct
    {
        unsigned long dgtRsel :3;
        unsigned long :29;
    } bit;
};

/*  structure of sdrrAddrA    */
union _IoShdrSdrrAddrA
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrAddrA0 :32;
        unsigned long sdrrAddrA1 :32;
    } bit;
};

/*  structure of sdrrAddrB    */
union _IoShdrSdrrAddrB
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrAddrB0 :32;
        unsigned long sdrrAddrB1 :32;
    } bit;
};

/*  structure of sdrrAddrC    */
union _IoShdrSdrrAddrC
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrAddrC0 :32;
        unsigned long sdrrAddrC1 :32;
    } bit;
};

/*  structure of sdrrAddrD    */
union _IoShdrSdrrAddrD
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrAddrD0 :32;
        unsigned long sdrrAddrD1 :32;
    } bit;
};

/*  structure of sdrrAddrE    */
union _IoShdrSdrrAddrE
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrAddrE0 :32;
        unsigned long sdrrAddrE1 :32;
    } bit;
};

/*  structure of sdrrAddrF    */
union _IoShdrSdrrAddrF
{
    unsigned long word;
    struct
    {
        unsigned long sdrrAddrF0 :32;
    } bit;
};

/*  structure of sdrrGhsizeA  */
union _IoShdrSdrrGhsizeA
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrGhsizeA0 :16;
        unsigned long :16;
        unsigned long sdrrGhsizeA1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrrGhsizeB  */
union _IoShdrSdrrGhsizeB
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrGhsizeB0 :16;
        unsigned long :16;
        unsigned long sdrrGhsizeB1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrrGhsizeC  */
union _IoShdrSdrrGhsizeC
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrGhsizeC0 :16;
        unsigned long :16;
        unsigned long sdrrGhsizeC1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrrGhsizeD  */
union _IoShdrSdrrGhsizeD
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrGhsizeD0 :16;
        unsigned long :16;
        unsigned long sdrrGhsizeD1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrrGhsizeE  */
union _IoShdrSdrrGhsizeE
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrrGhsizeE0 :16;
        unsigned long :16;
        unsigned long sdrrGhsizeE1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrrGhsizeF  */
union _IoShdrSdrrGhsizeF
{
    unsigned long word;
    struct
    {
        unsigned long sdrrGhsizeF0 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrrVfm       */
union _IoShdrSdrrVfm
{
    unsigned long word;
    struct
    {
        unsigned long sdrrVfmA :1;
        unsigned long :15;
        unsigned long :1;
        unsigned long :15;
    } bit;
};

/*  structure of sdrwAddrB    */
union _IoShdrSdrwAddrB
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwAddrB0 :32;
        unsigned long sdrwAddrB1 :32;
    } bit;
};

/*  structure of sdrwAddrE    */
union _IoShdrSdrwAddrE
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwAddrE0 :32;
        unsigned long sdrwAddrE1 :32;
    } bit;
};

/*  structure of sdrwAddrF    */
union _IoShdrSdrwAddrF
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwAddrF0 :32;
        unsigned long sdrwAddrF1 :32;
    } bit;
};

/*  structure of sdrwAddrG    */
union _IoShdrSdrwAddrG
{
    unsigned long word[3];
    struct
    {
        unsigned long sdrwAddrG0 :32;
        unsigned long sdrwAddrG1 :32;
        unsigned long sdrwAddrG2 :32;
    } bit;
};

/*  structure of sdrwAddrH    */
union _IoShdrSdrwAddrH
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwAddrH0 :32;
        unsigned long sdrwAddrH1 :32;
    } bit;
};

/*  structure of sdrwAddrI    */
union _IoShdrSdrwAddrI
{
    unsigned long word;
    struct
    {
        unsigned long sdrwAddrI0 :32;
    } bit;
};

/*  structure of sdrwGhsizeB  */
union _IoShdrSdrwGhsizeB
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwGhsizeB0 :16;
        unsigned long :16;
        unsigned long sdrwGhsizeB1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrwGhsizeE  */
union _IoShdrSdrwGhsizeE
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwGhsizeE0 :16;
        unsigned long :16;
        unsigned long sdrwGhsizeE1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrwGhsizeF  */
union _IoShdrSdrwGhsizeF
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwGhsizeF0 :16;
        unsigned long :16;
        unsigned long sdrwGhsizeF1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrwGhsizeG  */
union _IoShdrSdrwGhsizeG
{
    unsigned long word[3];
    struct
    {
        unsigned long sdrwGhsizeG0 :16;
        unsigned long :16;
        unsigned long sdrwGhsizeG1 :16;
        unsigned long :16;
        unsigned long sdrwGhsizeG2 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrwGhsizeH  */
union _IoShdrSdrwGhsizeH
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwGhsizeH0 :16;
        unsigned long :16;
        unsigned long sdrwGhsizeH1 :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrwGhsizeI  */
union _IoShdrSdrwGhsizeI
{
    unsigned long word;
    struct
    {
        unsigned long sdrwGhsizeI0 :15;
        unsigned long sdrwVfmA :1;
        unsigned long :16;
    } bit;
};

/*  structure of sdrwVfm       */
union _IoShdrSdrwVfm
{
    unsigned long word;
    struct
    {
        unsigned long :4;
        unsigned long sdrwVfmB :1;
        unsigned long :27;
    } bit;
};

/*  structure of sdrwBaA      */
union _IoShdrSdrwBaA
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwBaA0 :32;
        unsigned long sdrwBaA1 :32;
    } bit;
};

/*  structure of sdrwBaC      */
union _IoShdrSdrwBaC
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwBaC0 :32;
        unsigned long sdrwBaC1 :32;
    } bit;
};

/*  structure of sdrwBaD      */
union _IoShdrSdrwBaD
{
    unsigned long word[2];
    struct
    {
        unsigned long sdrwBaD0 :32;
        unsigned long sdrwBaD1 :32;
    } bit;
};

/*  structure of sdrwFwA      */
union _IoShdrSdrwFwA
{
    unsigned long word;
    struct
    {
        unsigned long sdrwFwA :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrwFwC      */
union _IoShdrSdrwFwC
{
    unsigned long word;
    struct
    {
        unsigned long sdrwFwC :16;
        unsigned long :16;
    } bit;
};

/*  structure of sdrwFwD      */
union _IoShdrSdrwFwD
{
    unsigned long word;
    struct
    {
        unsigned long sdrwFwD :16;
        unsigned long :16;
    } bit;
};

KConstType k_jdsshdr2_get_type(void);
KJdsshdr2* k_jdsshdr2_new(void);

#endif/*__K_JDSSHDR2_H__*/

