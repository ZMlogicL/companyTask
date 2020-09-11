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

#define K_TYPE_JDSSHDR4	(k_jdsshdr4_get_type())
#define K_JDSSHDR4(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsshdr4))
#define K_IS_JDSSHDR4(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSSHDR4))

typedef struct _KJdsshdr4 KJdsshdr4;
typedef struct _KJdsshdr4Private KJdsshdr4Private;

typedef union _IoShdrShdrifrm IoShdrShdrifrm;
typedef union _IoShdrShdrofrm IoShdrShdrofrm;
typedef union _IoShdrSdrrHsizeA IoShdrSdrrHsizeA;
typedef union _IoShdrSdrrHsizeB IoShdrSdrrHsizeB;
typedef union _IoShdrSdrrHsizeC IoShdrSdrrHsizeC;
typedef union _IoShdrSdrrHsizeD IoShdrSdrrHsizeD;
typedef union _IoShdrSdrrHsizeE IoShdrSdrrHsizeE;
typedef union _IoShdrSdrrVsizeA IoShdrSdrrVsizeA;
typedef union _IoShdrSdrrVsizeB IoShdrSdrrVsizeB;
typedef union _IoShdrSdrrVsizeC IoShdrSdrrVsizeC;
typedef union _IoShdrSdrrVsizeD IoShdrSdrrVsizeD;
typedef union _IoShdrSdrrVsizeE IoShdrSdrrVsizeE;
typedef union _IoShdrExmag IoShdrExmag;
typedef union _IoShdrRemval IoShdrRemval;
typedef union _IoShdrShift IoShdrShift;
typedef union _IoShdrMrgn IoShdrMrgn;
typedef union _IoShdrFlwcnt IoShdrFlwcnt;
typedef union _IoShdrTmode IoShdrTmode;
typedef union _IoShdrModesel IoShdrModesel;
typedef union _IoShdrMcmodesel IoShdrMcmodesel;
typedef union _IoShdrCompincfmsel IoShdrCompincfmsel;
typedef union _IoShdrBypasson IoShdrBypasson;
typedef union _IoShdrAxisize IoShdrAxisize;
typedef union _IoShdrLint IoShdrLint;
typedef union _IoShdrWrstartaddr IoShdrWrstartaddr;
typedef union _IoShdrRdstartaddr IoShdrRdstartaddr;
typedef union _IoShdrPremd IoShdrPremd;
typedef union _IoShdrY2rcoef IoShdrY2rcoef;
typedef union _IoShdrPrey2rclpul0 IoShdrPrey2rclpul0;
typedef union _IoShdrPrey2rclpll0 IoShdrPrey2rclpll0;
typedef union _IoShdrPrey2rclpus IoShdrPrey2rclpus;
typedef union _IoShdrPrey2rclpls IoShdrPrey2rclpls;
typedef union _IoShdrR2ycoef IoShdrR2ycoef;
typedef union _IoShdrPrer2yclpul IoShdrPrer2yclpul;
typedef union _IoShdrPrer2yclpll IoShdrPrer2yclpll;
typedef union _IoShdrPrer2yclpus IoShdrPrer2yclpus;
typedef union _IoShdrPrer2yclpls IoShdrPrer2yclpls;
typedef union _IoShdrSknofs IoShdrSknofs;
typedef union _IoShdrSknsl IoShdrSknsl;
typedef union _IoShdrSknb IoShdrSknb;
typedef union _IoShdrLknofs IoShdrLknofs;
typedef union _IoShdrLknsl IoShdrLknsl;
typedef union _IoShdrLknb IoShdrLknb;
typedef union _IoShdrEpbd IoShdrEpbd;
typedef union _IoShdrEpof IoShdrEpof;
typedef union _IoShdrEpbld IoShdrEpbld;
typedef union _IoShdrFdweight IoShdrFdweight;
typedef union _IoShdrMvcnt IoShdrMvcnt;
typedef union _IoShdrBldrofs IoShdrBldrofs;
typedef union _IoShdrBldrsl IoShdrBldrsl;
typedef union _IoShdrBldrb IoShdrBldrb;
typedef union _IoShdrWghtr2ycoef IoShdrWghtr2ycoef;


struct _KJdsshdr4
{
    KObject parent;
};

/*  structure of shdrifrm       */
union _IoShdrShdrifrm
{
    unsigned long word;
    struct
    {
        unsigned long ibits0 :1;
        unsigned long :3;
        unsigned long :4;
        unsigned long incfmt :1;
        unsigned long :3;
        unsigned long :4;
        unsigned long edgecpy :1;
        unsigned long :3;
        unsigned long :4;
        unsigned long edgecut :1;
        unsigned long :7;
    } bit;
};

/*  structure of shdrofrm       */
union _IoShdrShdrofrm
{
    unsigned long word;
    struct
    {
        unsigned long outctrl :1;
        unsigned long :3;
        unsigned long :4;
        unsigned long outsel :1;
        unsigned long :3;
        unsigned long outselen :1;
        unsigned long :19;
    } bit;
};

/*  structure of sdrrHsizeA   */
union _IoShdrSdrrHsizeA
{
    unsigned long word;
    struct
    {
        unsigned long sdrrHsizeA :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrHsizeB   */
union _IoShdrSdrrHsizeB
{
    unsigned long word;
    struct
    {
        unsigned long sdrrHsizeB :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrHsizeC   */
union _IoShdrSdrrHsizeC
{
    unsigned long word;
    struct
    {
        unsigned long sdrrHsizeC :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrHsizeD   */
union _IoShdrSdrrHsizeD
{
    unsigned long word;
    struct
    {
        unsigned long sdrrHsizeD :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrHsizeE   */
union _IoShdrSdrrHsizeE
{
    unsigned long word;
    struct
    {
        unsigned long sdrrHsizeE :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrVsizeA   */
union _IoShdrSdrrVsizeA
{
    unsigned long word;
    struct
    {
        unsigned long sdrrVsizeA :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrVsizeB   */
union _IoShdrSdrrVsizeB
{
    unsigned long word;
    struct
    {
        unsigned long sdrrVsizeB :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrVsizeC   */
union _IoShdrSdrrVsizeC
{
    unsigned long word;
    struct
    {
        unsigned long sdrrVsizeC :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrVsizeD   */
union _IoShdrSdrrVsizeD
{
    unsigned long word;
    struct
    {
        unsigned long sdrrVsizeD :14;
        unsigned long :18;
    } bit;
};

/*  structure of sdrrVsizeE   */
union _IoShdrSdrrVsizeE
{
    unsigned long word;
    struct
    {
        unsigned long sdrrVsizeE :14;
        unsigned long :18;
    } bit;
};

/*  structure of exmag      */
union _IoShdrExmag
{
    unsigned long word;
    struct
    {
        unsigned long exmag :14;
        unsigned long :18;
    } bit;
};

/*  structure of remval     */
union _IoShdrRemval
{
    unsigned long word;
    struct
    {
        unsigned long rexmag :17;
        unsigned long :3;
        unsigned long :4;
        long remsft :4;
        unsigned long :4;
    } bit;
};

/*  structure of shift      */
union _IoShdrShift
{
    unsigned long word;
    struct
    {
        long shiftx :13;
        unsigned long :3;
        long shifty :13;
        unsigned long :3;
    } bit;
};

/*  structure of mrgn       */
union _IoShdrMrgn
{
    unsigned long word;
    struct
    {
        unsigned long mrgn :7;
        unsigned long :25;
    } bit;
};

/*  structure of flwcnt     */
union _IoShdrFlwcnt
{
    unsigned long word;
    struct
    {
        unsigned long fmden :1;
        unsigned long :3;
        unsigned long :4;
        unsigned long bpen :1;
        unsigned long :3;
        unsigned long :4;
        unsigned long smcin :2;
        unsigned long :2;
        unsigned long :4;
        unsigned long brsel :2;
        unsigned long :6;
    } bit;
};

/*  structure of tmode      */
union _IoShdrTmode
{
    unsigned long word;
    struct
    {
        unsigned long tmode :1;
        unsigned long :31;
    } bit;
};

/*  structure of modesel    */
union _IoShdrModesel
{
    unsigned long word;
    struct
    {
        unsigned long mode :1;
        unsigned long :31;
    } bit;
};

/*  structure of mcModesel */
union _IoShdrMcmodesel
{
    unsigned long word;
    struct
    {
        unsigned long mode :1;
        unsigned long :31;
    } bit;
};

/*  structure of COMP_INCFMSELSEL   */
union _IoShdrCompincfmsel
{
    unsigned long word;
    struct
    {
        unsigned long mode :1;
        unsigned long :31;
    } bit;
};

/*  structure of bypasson   */
union _IoShdrBypasson
{
    unsigned long word;
    struct
    {
        unsigned long rmd :1;
        unsigned long :3;
        unsigned long wmd :1;
        unsigned long :27;
    } bit;
};

/*  structure of axisize    */
union _IoShdrAxisize
{
    unsigned long word;
    struct
    {
        unsigned long ryc :1;
        unsigned long :3;
        unsigned long rci :1;
        unsigned long :3;
        unsigned long wr :1;
        unsigned long :23;
    } bit;
};

/*  structure of lint   */
union _IoShdrLint
{
    unsigned long word[3];
    struct
    {
        unsigned long no :5;
        unsigned long :27;
        unsigned long msk :1;
        unsigned long :31;
        unsigned long st :1;
        unsigned long :31;
    } bit;
};

/*  structure of wrstartaddr    */
union _IoShdrWrstartaddr
{
    unsigned long word[2];
    struct
    {
        unsigned long addrY :32;
        unsigned long addrC :32;
    } bit;
};

/*  structure of rdstartaddr    */
union _IoShdrRdstartaddr
{
    unsigned long word[2];
    struct
    {
        unsigned long addrY :32;
        unsigned long addrC :32;
    } bit;
};

/*  structure of premd      */
union _IoShdrPremd
{
    unsigned long word;
    struct
    {
        unsigned long cusmd :3;
        unsigned long :1;
        unsigned long :4;
        unsigned long dgmd :1;
        unsigned long :23;
    } bit;
};

/*  structure of y2rcoef    */
union _IoShdrY2rcoef
{
    unsigned long word[5];
    struct
    {
        long y2rcoef0 :15;
        unsigned long :1;
        long y2rcoef1 :15;
        unsigned long :1;
        long y2rcoef2 :15;
        unsigned long :1;
        long y2rcoef3 :15;
        unsigned long :1;
        long y2rcoef4 :15;
        unsigned long :1;
        long y2rcoef5 :15;
        unsigned long :1;
        long y2rcoef6 :15;
        unsigned long :1;
        long y2rcoef7 :15;
        unsigned long :1;
        long y2rcoef8 :15;
        unsigned long :1;
        unsigned long :16;
    } bit;
};

/*  structure of prey2rclpul0   */
union _IoShdrPrey2rclpul0
{
    unsigned long word[2];
    struct
    {
        unsigned long prey2rclpul00 :16;
        unsigned long prey2rclpul01 :16;
        unsigned long prey2rclpul02 :16;
        unsigned long :16;
    } bit;
};

/*  structure of prey2rclpll0   */
union _IoShdrPrey2rclpll0
{
    unsigned long word[2];
    struct
    {
        unsigned long prey2rclpll00 :16;
        unsigned long prey2rclpll01 :16;
        unsigned long prey2rclpll02 :16;
        unsigned long :16;
    } bit;
};

/*  structure of prey2rclpus    */
union _IoShdrPrey2rclpus
{
    unsigned long word[2];
    struct
    {
        unsigned long prey2rclpus0 :8;
        unsigned long :8;
        unsigned long prey2rclpus1 :8;
        unsigned long :8;
        unsigned long prey2rclpus2 :8;
        unsigned long :8;
        unsigned long :16;
    } bit;
};

/*  structure of prey2rclpls    */
union _IoShdrPrey2rclpls
{
    unsigned long word[2];
    struct
    {
        unsigned long prey2rclpls0 :8;
        unsigned long :8;
        unsigned long prey2rclpls1 :8;
        unsigned long :8;
        unsigned long prey2rclpls2 :8;
        unsigned long :8;
        unsigned long :16;
    } bit;
};

/*  structure of r2ycoef    */
union _IoShdrR2ycoef
{
    unsigned long word[5];
    struct
    {
        long r2ycoef0 :15;
        unsigned long :1;
        long r2ycoef1 :15;
        unsigned long :1;
        long r2ycoef2 :15;
        unsigned long :1;
        long r2ycoef3 :15;
        unsigned long :1;
        long r2ycoef4 :15;
        unsigned long :1;
        long r2ycoef5 :15;
        unsigned long :1;
        long r2ycoef6 :15;
        unsigned long :1;
        long r2ycoef7 :15;
        unsigned long :1;
        long r2ycoef8 :15;
        unsigned long :1;
        unsigned long :16;
    } bit;
};

/*  structure of prer2yclpul    */
union _IoShdrPrer2yclpul
{
    unsigned long word[3];
    struct
    {
        unsigned long prer2yclpul0 :16;
        unsigned long :16;
        long prer2yclpul1 :16;
        unsigned long :16;
        long prer2yclpul2 :16;
        unsigned long :16;
    } bit;
};

/*  structure of prer2yclpll    */
union _IoShdrPrer2yclpll
{
    unsigned long word[3];
    struct
    {
        unsigned long prer2yclpll0 :16;
        unsigned long :16;
        long prer2yclpll1 :16;
        unsigned long :16;
        long prer2yclpll2 :16;
        unsigned long :16;
    } bit;
};

/*  structure of prer2yclpus    */
union _IoShdrPrer2yclpus
{
    unsigned long word[2];
    struct
    {
        unsigned long prer2yclpus0 :12;
        unsigned long :4;
        long prer2yclpus1 :12;
        unsigned long :4;
        long prer2yclpus2 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of prer2yclpls    */
union _IoShdrPrer2yclpls
{
    unsigned long word[2];
    struct
    {
        unsigned long prer2yclpls0 :12;
        unsigned long :4;
        long prer2yclpls1 :12;
        unsigned long :4;
        long prer2yclpls2 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of sknofs     */
union _IoShdrSknofs
{
    unsigned long word[3];
    struct
    {
        unsigned long sknofs0 :8;
        unsigned long :24;
        unsigned long sknofs1 :8;
        unsigned long :24;
        unsigned long sknofs2 :8;
        unsigned long :24;
    } bit;
};

/*  structure of sknsl      */
union _IoShdrSknsl
{
    unsigned long word[3];
    struct
    {
        unsigned long sknsl0 :8;
        unsigned long :24;
        unsigned long sknsl1 :8;
        unsigned long :24;
        unsigned long sknsl2 :8;
        unsigned long :24;
    } bit;
};

/*  structure of sknb       */
union _IoShdrSknb
{
    unsigned long word;
    struct
    {
        unsigned long sknb :10;
        unsigned long :22;
    } bit;
};

/*  structure of lknofs     */
union _IoShdrLknofs
{
    unsigned long word[3];
    struct
    {
        unsigned long lknofs0 :8;
        unsigned long :24;
        unsigned long lknofs1 :8;
        unsigned long :24;
        unsigned long lknofs2 :8;
        unsigned long :24;
    } bit;
};

/*  structure of lknsl      */
union _IoShdrLknsl
{
    unsigned long word[3];
    struct
    {
        unsigned long lknsl0 :8;
        unsigned long :24;
        unsigned long lknsl1 :8;
        unsigned long :24;
        unsigned long lknsl2 :8;
        unsigned long :24;
    } bit;
};

/*  structure of lknb       */
union _IoShdrLknb
{
    unsigned long word;
    struct
    {
        unsigned long lknb :10;
        unsigned long :22;
    } bit;
};

/*  structure of epbd       */
union _IoShdrEpbd
{
    unsigned long word[2];
    struct
    {
        unsigned long :16;
        unsigned long epbd1 :8;
        unsigned long :8;
        unsigned long epbd2 :8;
        unsigned long :8;
        unsigned long epbd3 :8;
        unsigned long :8;
    } bit;
};

/*  structure of epof   */
union _IoShdrEpof
{
    unsigned long word[2];
    struct
    {
        unsigned long epof0 :8;
        unsigned long :8;
        unsigned long epof1 :8;
        unsigned long :8;
        unsigned long epof2 :8;
        unsigned long :8;
        unsigned long epof3 :8;
        unsigned long :8;
    } bit;
};

/*  structure of epbld      */
union _IoShdrEpbld
{
    unsigned long word;
    struct
    {
        unsigned long epbld :3;
        unsigned long :29;
    } bit;
};

/*  structure of fdweight   */
union _IoShdrFdweight
{
    unsigned long word;
    struct
    {
        unsigned long fdweight :5;
        unsigned long :27;
    } bit;
};

/*  structure of mvcnt      */
union _IoShdrMvcnt
{
    unsigned long word;
    struct
    {
        unsigned long mvbd :8;
        unsigned long mvth :8;
        long mvgr :13;
        unsigned long :3;
    } bit;
};

/*  structure of bldrofs    */
union _IoShdrBldrofs
{
    unsigned long word[3];
    struct
    {
        unsigned long bldrofs0 :8;
        unsigned long :8;
        unsigned long bldrofs1 :8;
        unsigned long :8;
        unsigned long bldrofs2 :8;
        unsigned long :8;
        unsigned long bldrofs3 :8;
        unsigned long :8;
        unsigned long bldrofs4 :8;
        unsigned long :8;
        unsigned long :16;
    } bit;
};

/*  structure of bldrsl */
union _IoShdrBldrsl
{
    unsigned long word[3];
    struct
    {
        unsigned long bldrsl0 :12;
        unsigned long :4;
        unsigned long bldrsl1 :12;
        unsigned long :4;
        unsigned long bldrsl2 :12;
        unsigned long :4;
        unsigned long bldrsl3 :12;
        unsigned long :4;
        unsigned long bldrsl4 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of bldrb  */
union _IoShdrBldrb
{
    unsigned long word[3];
    struct
    {
        unsigned long :16;
        unsigned long bldrb1 :8;
        unsigned long :8;
        unsigned long bldrb2 :8;
        unsigned long :8;
        unsigned long bldrb3 :8;
        unsigned long :8;
        unsigned long bldrb4 :8;
        unsigned long :24;
    } bit;
};

/*  structure of WGHTR2YCOE */
union _IoShdrWghtr2ycoef
{
    unsigned long word[2];
    struct
    {
        long wghtr2ycoef0 :15;
        unsigned long :1;
        long wghtr2ycoef1 :15;
        unsigned long :1;
        long wghtr2ycoef2 :15;
        unsigned long :1;
        unsigned long :16;
    } bit;
};

KConstType k_jdsshdr4_get_type(void);
KJdsshdr4* k_jdsshdr4_new(void);

#endif/*__K_JDSSHDR4_H__*/

