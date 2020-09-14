/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-10
 *@author            :郑蛘钊
 *@brief             :kjdsshdr4
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_JDSSHDR4_H__
#define __K_JDSSHDR4_H__


#include <klib.h>


#define K_TYPE_JDSSHDR4	            (k_jdsshdr4_get_type())
#define K_JDSSHDR4(obj)	            (K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsshdr4))
#define K_IS_JDSSHDR4(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSSHDR4))


typedef struct _KJdsshdr4           KJdsshdr4;
typedef struct _KJdsshdr4Private    KJdsshdr4Private;

typedef union _IoShdrShdrifrm       IoShdrShdrifrm;
typedef union _IoShdrShdrofrm       IoShdrShdrofrm;
typedef union _IoShdrSdrrHsizeA     IoShdrSdrrHsizeA;
typedef union _IoShdrSdrrHsizeB     IoShdrSdrrHsizeB;
typedef union _IoShdrSdrrHsizeC     IoShdrSdrrHsizeC;
typedef union _IoShdrSdrrHsizeD     IoShdrSdrrHsizeD;
typedef union _IoShdrSdrrHsizeE     IoShdrSdrrHsizeE;
typedef union _IoShdrSdrrVsizeA     IoShdrSdrrVsizeA;
typedef union _IoShdrSdrrVsizeB     IoShdrSdrrVsizeB;
typedef union _IoShdrSdrrVsizeC     IoShdrSdrrVsizeC;
typedef union _IoShdrSdrrVsizeD     IoShdrSdrrVsizeD;
typedef union _IoShdrSdrrVsizeE     IoShdrSdrrVsizeE;
typedef union _IoShdrExmag          IoShdrExmag;
typedef union _IoShdrRemval         IoShdrRemval;
typedef union _IoShdrShift          IoShdrShift;
typedef union _IoShdrMrgn           IoShdrMrgn;
typedef union _IoShdrFlwcnt         IoShdrFlwcnt;
typedef union _IoShdrTmode          IoShdrTmode;
typedef union _IoShdrModesel        IoShdrModesel;
typedef union _IoShdrMcmodesel      IoShdrMcmodesel;
typedef union _IoShdrCompincfmsel   IoShdrCompincfmsel;
typedef union _IoShdrBypasson       IoShdrBypasson;
typedef union _IoShdrAxisize        IoShdrAxisize;
typedef union _IoShdrLint           IoShdrLint;
typedef union _IoShdrWrstartaddr    IoShdrWrstartaddr;
typedef union _IoShdrRdstartaddr    IoShdrRdstartaddr;
typedef union _IoShdrPremd          IoShdrPremd;
typedef union _IoShdrY2rcoef        IoShdrY2rcoef;
typedef union _IoShdrPrey2rclpul0   IoShdrPrey2rclpul0;
typedef union _IoShdrPrey2rclpll0   IoShdrPrey2rclpll0;
typedef union _IoShdrPrey2rclpus    IoShdrPrey2rclpus;
typedef union _IoShdrPrey2rclpls    IoShdrPrey2rclpls;
typedef union _IoShdrR2ycoef        IoShdrR2ycoef;
typedef union _IoShdrPrer2yclpul    IoShdrPrer2yclpul;
typedef union _IoShdrPrer2yclpll    IoShdrPrer2yclpll;
typedef union _IoShdrPrer2yclpus    IoShdrPrer2yclpus;
typedef union _IoShdrPrer2yclpls    IoShdrPrer2yclpls;
typedef union _IoShdrSknofs         IoShdrSknofs;
typedef union _IoShdrSknsl          IoShdrSknsl;
typedef union _IoShdrSknb           IoShdrSknb;
typedef union _IoShdrLknofs         IoShdrLknofs;
typedef union _IoShdrLknsl          IoShdrLknsl;
typedef union _IoShdrLknb           IoShdrLknb;
typedef union _IoShdrEpbd           IoShdrEpbd;
typedef union _IoShdrEpof           IoShdrEpof;
typedef union _IoShdrEpbld          IoShdrEpbld;
typedef union _IoShdrFdweight       IoShdrFdweight;
typedef union _IoShdrMvcnt          IoShdrMvcnt;
typedef union _IoShdrBldrofs        IoShdrBldrofs;
typedef union _IoShdrBldrsl         IoShdrBldrsl;
typedef union _IoShdrBldrb          IoShdrBldrb;
typedef union _IoShdrWghtr2ycoef    IoShdrWghtr2ycoef;


struct _KJdsshdr4
{
    KObject parent;
};


/*  structure of shdrifrm       */
union _IoShdrShdrifrm
{
    kulong word;
    struct
    {
        kulong ibits0 :1;
        kulong :3;
        kulong :4;
        kulong incfmt :1;
        kulong :3;
        kulong :4;
        kulong edgecpy :1;
        kulong :3;
        kulong :4;
        kulong edgecut :1;
        kulong :7;
    } bit;
};

/*  structure of shdrofrm       */
union _IoShdrShdrofrm
{
    kulong word;
    struct
    {
        kulong outctrl :1;
        kulong :3;
        kulong :4;
        kulong outsel :1;
        kulong :3;
        kulong outselen :1;
        kulong :19;
    } bit;
};

/*  structure of sdrrHsizeA   */
union _IoShdrSdrrHsizeA
{
    kulong word;
    struct
    {
        kulong sdrrHsizeA :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrHsizeB   */
union _IoShdrSdrrHsizeB
{
    kulong word;
    struct
    {
        kulong sdrrHsizeB :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrHsizeC   */
union _IoShdrSdrrHsizeC
{
    kulong word;
    struct
    {
        kulong sdrrHsizeC :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrHsizeD   */
union _IoShdrSdrrHsizeD
{
    kulong word;
    struct
    {
        kulong sdrrHsizeD :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrHsizeE   */
union _IoShdrSdrrHsizeE
{
    kulong word;
    struct
    {
        kulong sdrrHsizeE :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrVsizeA   */
union _IoShdrSdrrVsizeA
{
    kulong word;
    struct
    {
        kulong sdrrVsizeA :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrVsizeB   */
union _IoShdrSdrrVsizeB
{
    kulong word;
    struct
    {
        kulong sdrrVsizeB :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrVsizeC   */
union _IoShdrSdrrVsizeC
{
    kulong word;
    struct
    {
        kulong sdrrVsizeC :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrVsizeD   */
union _IoShdrSdrrVsizeD
{
    kulong word;
    struct
    {
        kulong sdrrVsizeD :14;
        kulong :18;
    } bit;
};

/*  structure of sdrrVsizeE   */
union _IoShdrSdrrVsizeE
{
    kulong word;
    struct
    {
        kulong sdrrVsizeE :14;
        kulong :18;
    } bit;
};

/*  structure of exmag      */
union _IoShdrExmag
{
    kulong word;
    struct
    {
        kulong exmag :14;
        kulong :18;
    } bit;
};

/*  structure of remval     */
union _IoShdrRemval
{
    kulong word;
    struct
    {
        kulong rexmag :17;
        kulong :3;
        kulong :4;
        klong remsft :4;
        kulong :4;
    } bit;
};

/*  structure of shift      */
union _IoShdrShift
{
    kulong word;
    struct
    {
        klong shiftx :13;
        kulong :3;
        klong shifty :13;
        kulong :3;
    } bit;
};

/*  structure of mrgn       */
union _IoShdrMrgn
{
    kulong word;
    struct
    {
        kulong mrgn :7;
        kulong :25;
    } bit;
};

/*  structure of flwcnt     */
union _IoShdrFlwcnt
{
    kulong word;
    struct
    {
        kulong fmden :1;
        kulong :3;
        kulong :4;
        kulong bpen :1;
        kulong :3;
        kulong :4;
        kulong smcin :2;
        kulong :2;
        kulong :4;
        kulong brsel :2;
        kulong :6;
    } bit;
};

/*  structure of tmode      */
union _IoShdrTmode
{
    kulong word;
    struct
    {
        kulong tmode :1;
        kulong :31;
    } bit;
};

/*  structure of modesel    */
union _IoShdrModesel
{
    kulong word;
    struct
    {
        kulong mode :1;
        kulong :31;
    } bit;
};

/*  structure of mcModesel */
union _IoShdrMcmodesel
{
    kulong word;
    struct
    {
        kulong mode :1;
        kulong :31;
    } bit;
};

/*  structure of COMP_INCFMSELSEL   */
union _IoShdrCompincfmsel
{
    kulong word;
    struct
    {
        kulong mode :1;
        kulong :31;
    } bit;
};

/*  structure of bypasson   */
union _IoShdrBypasson
{
    kulong word;
    struct
    {
        kulong rmd :1;
        kulong :3;
        kulong wmd :1;
        kulong :27;
    } bit;
};

/*  structure of axisize    */
union _IoShdrAxisize
{
    kulong word;
    struct
    {
        kulong ryc :1;
        kulong :3;
        kulong rci :1;
        kulong :3;
        kulong wr :1;
        kulong :23;
    } bit;
};

/*  structure of lint   */
union _IoShdrLint
{
    kulong word[3];
    struct
    {
        kulong no :5;
        kulong :27;
        kulong msk :1;
        kulong :31;
        kulong st :1;
        kulong :31;
    } bit;
};

/*  structure of wrstartaddr    */
union _IoShdrWrstartaddr
{
    kulong word[2];
    struct
    {
        kulong addrY :32;
        kulong addrC :32;
    } bit;
};

/*  structure of rdstartaddr    */
union _IoShdrRdstartaddr
{
    kulong word[2];
    struct
    {
        kulong addrY :32;
        kulong addrC :32;
    } bit;
};

/*  structure of premd      */
union _IoShdrPremd
{
    kulong word;
    struct
    {
        kulong cusmd :3;
        kulong :1;
        kulong :4;
        kulong dgmd :1;
        kulong :23;
    } bit;
};

/*  structure of y2rcoef    */
union _IoShdrY2rcoef
{
    kulong word[5];
    struct
    {
        klong y2rcoef0 :15;
        kulong :1;
        klong y2rcoef1 :15;
        kulong :1;
        klong y2rcoef2 :15;
        kulong :1;
        klong y2rcoef3 :15;
        kulong :1;
        klong y2rcoef4 :15;
        kulong :1;
        klong y2rcoef5 :15;
        kulong :1;
        klong y2rcoef6 :15;
        kulong :1;
        klong y2rcoef7 :15;
        kulong :1;
        klong y2rcoef8 :15;
        kulong :1;
        kulong :16;
    } bit;
};

/*  structure of prey2rclpul0   */
union _IoShdrPrey2rclpul0
{
    kulong word[2];
    struct
    {
        kulong prey2rclpul00 :16;
        kulong prey2rclpul01 :16;
        kulong prey2rclpul02 :16;
        kulong :16;
    } bit;
};

/*  structure of prey2rclpll0   */
union _IoShdrPrey2rclpll0
{
    kulong word[2];
    struct
    {
        kulong prey2rclpll00 :16;
        kulong prey2rclpll01 :16;
        kulong prey2rclpll02 :16;
        kulong :16;
    } bit;
};

/*  structure of prey2rclpus    */
union _IoShdrPrey2rclpus
{
    kulong word[2];
    struct
    {
        kulong prey2rclpus0 :8;
        kulong :8;
        kulong prey2rclpus1 :8;
        kulong :8;
        kulong prey2rclpus2 :8;
        kulong :8;
        kulong :16;
    } bit;
};

/*  structure of prey2rclpls    */
union _IoShdrPrey2rclpls
{
    kulong word[2];
    struct
    {
        kulong prey2rclpls0 :8;
        kulong :8;
        kulong prey2rclpls1 :8;
        kulong :8;
        kulong prey2rclpls2 :8;
        kulong :8;
        kulong :16;
    } bit;
};

/*  structure of r2ycoef    */
union _IoShdrR2ycoef
{
    kulong word[5];
    struct
    {
        klong r2ycoef0 :15;
        kulong :1;
        klong r2ycoef1 :15;
        kulong :1;
        klong r2ycoef2 :15;
        kulong :1;
        klong r2ycoef3 :15;
        kulong :1;
        klong r2ycoef4 :15;
        kulong :1;
        klong r2ycoef5 :15;
        kulong :1;
        klong r2ycoef6 :15;
        kulong :1;
        klong r2ycoef7 :15;
        kulong :1;
        klong r2ycoef8 :15;
        kulong :1;
        kulong :16;
    } bit;
};

/*  structure of prer2yclpul    */
union _IoShdrPrer2yclpul
{
    kulong word[3];
    struct
    {
        kulong prer2yclpul0 :16;
        kulong :16;
        klong prer2yclpul1 :16;
        kulong :16;
        klong prer2yclpul2 :16;
        kulong :16;
    } bit;
};

/*  structure of prer2yclpll    */
union _IoShdrPrer2yclpll
{
    kulong word[3];
    struct
    {
        kulong prer2yclpll0 :16;
        kulong :16;
        klong prer2yclpll1 :16;
        kulong :16;
        klong prer2yclpll2 :16;
        kulong :16;
    } bit;
};

/*  structure of prer2yclpus    */
union _IoShdrPrer2yclpus
{
    kulong word[2];
    struct
    {
        kulong prer2yclpus0 :12;
        kulong :4;
        klong prer2yclpus1 :12;
        kulong :4;
        klong prer2yclpus2 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of prer2yclpls    */
union _IoShdrPrer2yclpls
{
    kulong word[2];
    struct
    {
        kulong prer2yclpls0 :12;
        kulong :4;
        klong prer2yclpls1 :12;
        kulong :4;
        klong prer2yclpls2 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of sknofs     */
union _IoShdrSknofs
{
    kulong word[3];
    struct
    {
        kulong sknofs0 :8;
        kulong :24;
        kulong sknofs1 :8;
        kulong :24;
        kulong sknofs2 :8;
        kulong :24;
    } bit;
};

/*  structure of sknsl      */
union _IoShdrSknsl
{
    kulong word[3];
    struct
    {
        kulong sknsl0 :8;
        kulong :24;
        kulong sknsl1 :8;
        kulong :24;
        kulong sknsl2 :8;
        kulong :24;
    } bit;
};

/*  structure of sknb       */
union _IoShdrSknb
{
    kulong word;
    struct
    {
        kulong sknb :10;
        kulong :22;
    } bit;
};

/*  structure of lknofs     */
union _IoShdrLknofs
{
    kulong word[3];
    struct
    {
        kulong lknofs0 :8;
        kulong :24;
        kulong lknofs1 :8;
        kulong :24;
        kulong lknofs2 :8;
        kulong :24;
    } bit;
};

/*  structure of lknsl      */
union _IoShdrLknsl
{
    kulong word[3];
    struct
    {
        kulong lknsl0 :8;
        kulong :24;
        kulong lknsl1 :8;
        kulong :24;
        kulong lknsl2 :8;
        kulong :24;
    } bit;
};

/*  structure of lknb       */
union _IoShdrLknb
{
    kulong word;
    struct
    {
        kulong lknb :10;
        kulong :22;
    } bit;
};

/*  structure of epbd       */
union _IoShdrEpbd
{
    kulong word[2];
    struct
    {
        kulong :16;
        kulong epbd1 :8;
        kulong :8;
        kulong epbd2 :8;
        kulong :8;
        kulong epbd3 :8;
        kulong :8;
    } bit;
};

/*  structure of epof   */
union _IoShdrEpof
{
    kulong word[2];
    struct
    {
        kulong epof0 :8;
        kulong :8;
        kulong epof1 :8;
        kulong :8;
        kulong epof2 :8;
        kulong :8;
        kulong epof3 :8;
        kulong :8;
    } bit;
};

/*  structure of epbld      */
union _IoShdrEpbld
{
    kulong word;
    struct
    {
        kulong epbld :3;
        kulong :29;
    } bit;
};

/*  structure of fdweight   */
union _IoShdrFdweight
{
    kulong word;
    struct
    {
        kulong fdweight :5;
        kulong :27;
    } bit;
};

/*  structure of mvcnt      */
union _IoShdrMvcnt
{
    kulong word;
    struct
    {
        kulong mvbd :8;
        kulong mvth :8;
        klong mvgr :13;
        kulong :3;
    } bit;
};

/*  structure of bldrofs    */
union _IoShdrBldrofs
{
    kulong word[3];
    struct
    {
        kulong bldrofs0 :8;
        kulong :8;
        kulong bldrofs1 :8;
        kulong :8;
        kulong bldrofs2 :8;
        kulong :8;
        kulong bldrofs3 :8;
        kulong :8;
        kulong bldrofs4 :8;
        kulong :8;
        kulong :16;
    } bit;
};

/*  structure of bldrsl */
union _IoShdrBldrsl
{
    kulong word[3];
    struct
    {
        kulong bldrsl0 :12;
        kulong :4;
        kulong bldrsl1 :12;
        kulong :4;
        kulong bldrsl2 :12;
        kulong :4;
        kulong bldrsl3 :12;
        kulong :4;
        kulong bldrsl4 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of bldrb  */
union _IoShdrBldrb
{
    kulong word[3];
    struct
    {
        kulong :16;
        kulong bldrb1 :8;
        kulong :8;
        kulong bldrb2 :8;
        kulong :8;
        kulong bldrb3 :8;
        kulong :8;
        kulong bldrb4 :8;
        kulong :24;
    } bit;
};

/*  structure of WGHTR2YCOE */
union _IoShdrWghtr2ycoef
{
    kulong word[2];
    struct
    {
        klong wghtr2ycoef0 :15;
        kulong :1;
        klong wghtr2ycoef1 :15;
        kulong :1;
        klong wghtr2ycoef2 :15;
        kulong :1;
        kulong :16;
    } bit;
};


KConstType k_jdsshdr4_get_type(void);
KJdsshdr4* k_jdsshdr4_new(void);


#endif/*__K_JDSSHDR4_H__*/
