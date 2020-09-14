/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :郑蛘钊
 *@brief             :kjdsshdr3
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_JDSSHDR3_H__
#define __K_JDSSHDR3_H__

#include <klib.h>

#define K_TYPE_JDSSHDR3	            (k_jdsshdr3_get_type())
#define K_JDSSHDR3(obj)	            (K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsshdr3))
#define K_IS_JDSSHDR3(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSSHDR3))

typedef struct _KJdsshdr3           KJdsshdr3;
typedef struct _KJdsshdr3Private    KJdsshdr3Private;

typedef union _IoShdrWghtr2yclp     IoShdrWghtr2yclp;
typedef union _IoShdrWghtbase       IoShdrWghtbase;
typedef union _IoShdrWghtrofs       IoShdrWghtrofs;
typedef union _IoShdrWghtgofs       IoShdrWghtgofs;
typedef union _IoShdrWghtbofs       IoShdrWghtbofs;
typedef union _IoShdrWghtrsl        IoShdrWghtrsl;
typedef union _IoShdrWghtgsl        IoShdrWghtgsl;
typedef union _IoShdrWghtbsl        IoShdrWghtbsl;
typedef union _IoShdrWghtrb         IoShdrWghtrb;
typedef union _IoShdrWghtgb         IoShdrWghtgb;
typedef union _IoShdrWghtbb         IoShdrWghtbb;
typedef union _IoShdrIsoth          IoShdrIsoth;
typedef union _IoShdrIsocoef        IoShdrIsocoef;
typedef union _IoShdrSatth          IoShdrSatth;
typedef union _IoShdrExp77md        IoShdrExp77md;
typedef union _IoShdrFmdsel         IoShdrFmdsel;
typedef union _IoShdrTlut           IoShdrTlut;
typedef union _IoShdrPmskmd         IoShdrPmskmd;
typedef union _IoShdrSpnren         IoShdrSpnren;
typedef union _IoShdrSpebd          IoShdrSpebd;
typedef union _IoShdrSpeof          IoShdrSpeof;
typedef union _IoShdrSpebld         IoShdrSpebld;
typedef union _IoShdrMsky2rclpul    IoShdrMsky2rclpul;
typedef union _IoShdrMsky2rclpll    IoShdrMsky2rclpll;
typedef union _IoShdrMsky2rclpus    IoShdrMsky2rclpus;
typedef union _IoShdrMsky2rclpls    IoShdrMsky2rclpls;
typedef union _IoShdrAlpha          IoShdrAlpha;
typedef union _IoShdrLpfc           IoShdrLpfc;
typedef union _IoShdrBldofs         IoShdrBldofs;
typedef union _IoShdrBldsl          IoShdrBldsl;
typedef union _IoShdrBldb           IoShdrBldb;
typedef union _IoShdrNormgain       IoShdrNormgain;
typedef union _IoShdrNormofs        IoShdrNormofs;
typedef union _IoShdrMskmd          IoShdrMskmd;
typedef union _IoShdrBldsel         IoShdrBldsel;
typedef union _IoShdrAlphasel       IoShdrAlphasel;
typedef union _IoShdrAlphaval       IoShdrAlphaval;
typedef union _IoShdrPostsft1rnd    IoShdrPostsft1rnd;
typedef union _IoShdrPosty2rcoef    IoShdrPosty2rcoef;
typedef union _IoShdrPosty2rclpthu  IoShdrPosty2rclpthu;
typedef union _IoShdrPosty2rclpthl  IoShdrPosty2rclpthl;
typedef union _IoShdrPostsel1       IoShdrPostsel1;
typedef union _IoShdrPostmulqpos    IoShdrPostmulqpos;
typedef union _IoShdrEvknb          IoShdrEvknb;
typedef union _IoShdrEvknofs        IoShdrEvknofs;
typedef union _IoShdrEvknsl         IoShdrEvknsl;
typedef union _IoShdrPostsel0       IoShdrPostsel0;
typedef union _IoShdrHdrcssmd       IoShdrHdrcssmd;
typedef union _IoShdrCh0mode        IoShdrCh0mode;


struct _KJdsshdr3
{
    KObject parent;
};


/*  structure of wghtr2yclp */
union _IoShdrWghtr2yclp
{
    kulong word;
    struct
    {
        kulong wghtr2yclpu :8;
        kulong :8;
        kulong wghtr2yclpl :8;
        kulong :8;
    } bit;
};

/*  structure of wghtbase   */
union _IoShdrWghtbase
{
    kulong word;
    struct
    {
        kulong wghtbase :1;
        kulong :31;
    } bit;
};

/*  structure of wghtrofs   */
union _IoShdrWghtrofs
{
    kulong word[3];
    struct
    {
        kulong wghtrofs0 :12;
        kulong :4;
        kulong wghtrofs1 :12;
        kulong :4;
        kulong wghtrofs2 :12;
        kulong :4;
        kulong wghtrofs3 :12;
        kulong :4;
        kulong wghtrofs4 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of wghtgofs   */
union _IoShdrWghtgofs
{
    kulong word[3];
    struct
    {
        kulong wghtgofs0 :12;
        kulong :4;
        kulong wghtgofs1 :12;
        kulong :4;
        kulong wghtgofs2 :12;
        kulong :4;
        kulong wghtgofs3 :12;
        kulong :4;
        kulong wghtgofs4 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of wghtbofs   */
union _IoShdrWghtbofs
{
    kulong word[3];
    struct
    {
        kulong wghtbofs0 :12;
        kulong :4;
        kulong wghtbofs1 :12;
        kulong :4;
        kulong wghtbofs2 :12;
        kulong :4;
        kulong wghtbofs3 :12;
        kulong :4;
        kulong wghtbofs4 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of wghtrsl    */
union _IoShdrWghtrsl
{
    kulong word[3];
    struct
    {
        kulong wghtrsl0 :12;
        kulong :4;
        kulong wghtrsl1 :12;
        kulong :4;
        kulong wghtrsl2 :12;
        kulong :4;
        kulong wghtrsl3 :12;
        kulong :4;
        kulong wghtrsl4 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of wghtgsl    */
union _IoShdrWghtgsl
{
    kulong word[3];
    struct
    {
        kulong wghtgsl0 :12;
        kulong :4;
        kulong wghtgsl1 :12;
        kulong :4;
        kulong wghtgsl2 :12;
        kulong :4;
        kulong wghtgsl3 :12;
        kulong :4;
        kulong wghtgsl4 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of wghtbsl    */
union _IoShdrWghtbsl
{
    kulong word[3];
    struct
    {
        kulong wghtbsl0 :12;
        kulong :4;
        kulong wghtbsl1 :12;
        kulong :4;
        kulong wghtbsl2 :12;
        kulong :4;
        kulong wghtbsl3 :12;
        kulong :4;
        kulong wghtbsl4 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of wghtrb     */
union _IoShdrWghtrb
{
    kulong word[3];
    struct
    {
        kulong :16;
        kulong wghtrb1 :8;
        kulong :8;
        kulong wghtrb2 :8;
        kulong :8;
        kulong wghtrb3 :8;
        kulong :8;
        kulong wghtrb4 :8;
        kulong :24;
    } bit;
};

/*  structure of wghtgb     */
union _IoShdrWghtgb
{
    kulong word[3];
    struct
    {
        kulong :16;
        kulong wghtgb1 :8;
        kulong :8;
        kulong wghtgb2 :8;
        kulong :8;
        kulong wghtgb3 :8;
        kulong :8;
        kulong wghtgb4 :8;
        kulong :24;
    } bit;
};

/*  structure of wghtbb */
union _IoShdrWghtbb
{
    kulong word[3];
    struct
    {
        kulong :16;
        kulong wghtbb1 :8;
        kulong :8;
        kulong wghtbb2 :8;
        kulong :8;
        kulong wghtbb3 :8;
        kulong :8;
        kulong wghtbb4 :8;
        kulong :24;
    } bit;
};

/*  structure of isoth      */
union _IoShdrIsoth
{
    kulong word;
    struct
    {
        kulong isoth2 :9;
        kulong :23;
    } bit;
};

/*  structure of isocoef    */
union _IoShdrIsocoef
{
    kulong word;
    struct
    {
        kulong iso2k0 :2;
        kulong iso2k1 :2;
        kulong iso2k2 :2;
        kulong :2;
        kulong iso2k3 :5;
        kulong :3;
        kulong iso2k4 :5;
        kulong :3;
        kulong iso2k5 :8;
    } bit;
};

/*  structure of satth      */
union _IoShdrSatth
{
    kulong word;
    struct
    {
        kulong satth :8;
        kulong :24;
    } bit;
};

/*  structure of exp77md    */
union _IoShdrExp77md
{
    kulong word;
    struct
    {
        kulong exp77md :1;
        kulong :31;
    } bit;
};

/*  structure of fmdsel     */
union _IoShdrFmdsel
{
    kulong word;
    struct
    {
        kulong fmdsel :1;
        kulong :31;
    } bit;
};

/*  structure of TLUT       */
union _IoShdrTlut
{
    kulong word[5];
    struct
    {
        kulong tlut0 :8;
        kulong tlut1 :8;
        kulong tlut2 :8;
        kulong tlut3 :8;
        kulong tlut4 :8;
        kulong tlut5 :8;
        kulong tlut6 :8;
        kulong tlut7 :8;
        kulong tlut8 :8;
        kulong tlut9 :8;
        kulong tlut10 :8;
        kulong tlut11 :8;
        kulong tlut12 :8;
        kulong tlut13 :8;
        kulong tlut14 :8;
        kulong tlut15 :8;
        kulong tlut16 :8;
        kulong :24;
    } bit;
};

/*  structure of pmskmd     */
union _IoShdrPmskmd
{
    kulong word;
    struct
    {
        kulong pmskmd :1;
        kulong :31;
    } bit;
};

/*  structure of spnren     */
union _IoShdrSpnren
{
    kulong word;
    struct
    {
        kulong spnren :1;
        kulong :31;
    } bit;
};

/*  structure of spebd      */
union _IoShdrSpebd
{
    kulong word[2];
    struct
    {
        kulong :16;
        kulong spebd1 :12;
        kulong :4;
        kulong spebd2 :12;
        kulong :4;
        kulong spebd3 :12;
        kulong :4;
    } bit;
};

/*  structure of speof      */
union _IoShdrSpeof
{
    kulong word[2];
    struct
    {
        kulong speof0 :12;
        kulong :4;
        kulong speof1 :12;
        kulong :4;
        kulong speof2 :12;
        kulong :4;
        kulong speof3 :12;
        kulong :4;
    } bit;
};

/*  structure of spebld     */
union _IoShdrSpebld
{
    kulong word;
    struct
    {
        kulong spebld :3;
        kulong :29;
    } bit;
};

/*  structure of msky2rclpul    */
union _IoShdrMsky2rclpul
{
    kulong word[2];
    struct
    {
        kulong msky2rclpul0 :12;
        kulong :4;
        kulong msky2rclpul1 :12;
        kulong :4;
        kulong msky2rclpul2 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of msky2rclpll    */
union _IoShdrMsky2rclpll
{
    kulong word[2];
    struct
    {
        kulong msky2rclpll0 :12;
        kulong :4;
        kulong msky2rclpll1 :12;
        kulong :4;
        kulong msky2rclpll2 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of msky2rclpus    */
union _IoShdrMsky2rclpus
{
    kulong word[2];
    struct
    {
        kulong msky2rclpus0 :12;
        kulong :4;
        kulong msky2rclpus1 :12;
        kulong :4;
        kulong msky2rclpus2 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of msky2rclpls    */
union _IoShdrMsky2rclpls
{
    kulong word[2];
    struct
    {
        kulong msky2rclpls0 :12;
        kulong :4;
        kulong msky2rclpls1 :12;
        kulong :4;
        kulong msky2rclpls2 :12;
        kulong :4;
        kulong :16;
    } bit;
};

/*  structure of alpha      */
union _IoShdrAlpha
{
    kulong word;
    struct
    {
        kulong alpha :6;
        kulong :26;
    } bit;
};

/*  structure of lpfc       */
union _IoShdrLpfc
{
    kulong word[5];
    struct
    {
        kulong lpfc00 :8;
        kulong :8;
        kulong lpfc01 :8;
        kulong :8;
        kulong lpfc02 :8;
        kulong :8;
        kulong lpfc10 :8;
        kulong :8;
        kulong lpfc11 :8;
        kulong :8;
        kulong lpfc12 :8;
        kulong :8;
        kulong lpfc20 :8;
        kulong :8;
        kulong lpfc21 :8;
        kulong :8;
        kulong lpfc22 :8;
        kulong :8;
        kulong :16;
    } bit;
};

/*  structure of bldofs     */
union _IoShdrBldofs
{
    kulong word[4];
    struct
    {
        kulong bldofs0 :8;
        kulong :8;
        kulong bldofs1 :8;
        kulong :8;
        kulong bldofs2 :8;
        kulong :8;
        kulong bldofs3 :8;
        kulong :8;
        kulong bldofs4 :8;
        kulong :8;
        kulong bldofs5 :8;
        kulong :8;
        kulong bldofs6 :8;
        kulong :8;
        kulong :16;
    } bit;
};

/*  structure of bldsl  */
union _IoShdrBldsl
{
    kulong word[7];
    struct
    {
        kulong bldsl0 :16;
        kulong :16;
        kulong bldsl1 :16;
        kulong :16;
        kulong bldsl2 :16;
        kulong :16;
        kulong bldsl3 :16;
        kulong :16;
        kulong bldsl4 :16;
        kulong :16;
        kulong bldsl5 :16;
        kulong :16;
        kulong bldsl6 :16;
        kulong :16;
    } bit;
};

/*  structure of bldb   */
union _IoShdrBldb
{
    kulong word[4];
    struct
    {
        kulong :12;
        kulong :4;
        kulong bldb1 :12;
        kulong :4;
        kulong bldb2 :12;
        kulong :4;
        kulong bldb3 :12;
        kulong :4;
        kulong bldb4 :12;
        kulong :4;
        kulong bldb5 :12;
        kulong :4;
        kulong bldb6 :12;
        kulong :20;
    } bit;
};

/*  structure of normgain   */
union _IoShdrNormgain
{
    kulong word[2];
    struct
    {
        kulong normgain0 :8;
        kulong :8;
        kulong normgain1 :8;
        kulong :8;
        kulong normgain2 :8;
        kulong :8;
        kulong :16;
    } bit;
};

/*  structure of normofs    */
union _IoShdrNormofs
{
    kulong word[2];
    struct
    {
        kulong normofs0 :8;
        kulong :8;
        kulong normofs1 :8;
        kulong :8;
        kulong normofs2 :8;
        kulong :8;
        kulong :16;
    } bit;
};

/*  structure of mskmd      */
union _IoShdrMskmd
{
    kulong word;
    struct
    {
        kulong mskmd :2;
        kulong :30;
    } bit;
};

/*  structure of bldsel     */
union _IoShdrBldsel
{
    kulong word;
    struct
    {
        kulong bldsel :1;
        kulong :31;
    } bit;
};

/*  structure of alphasel   */
union _IoShdrAlphasel
{
    kulong word;
    struct
    {
        kulong alphasel :2;
        kulong :30;
    } bit;
};

/*  structure of alphaval   */
union _IoShdrAlphaval
{
    kulong word[2];
    struct
    {
        kulong alphavaly :8;
        kulong :8;
        kulong alphavalu :8;
        kulong :8;
        kulong alphavalv :8;
        kulong :24;
    } bit;
};

/*  structure of postsft1rnd    */
union _IoShdrPostsft1rnd
{
    kulong word;
    struct
    {
        kulong postsft1rnden :1;
        kulong :3;
        kulong :1;
        kulong :3;
        kulong :2;
        kulong :22;
    } bit;
};

/*  structure of posty2rcoef    */
union _IoShdrPosty2rcoef
{
    kulong word[5];
    struct
    {
        klong posty2rcoef0 :15;
        kulong :1;
        klong posty2rcoef1 :15;
        kulong :1;
        klong posty2rcoef2 :15;
        kulong :1;
        klong posty2rcoef3 :15;
        kulong :1;
        klong posty2rcoef4 :15;
        kulong :1;
        klong posty2rcoef5 :15;
        kulong :1;
        klong posty2rcoef6 :15;
        kulong :1;
        klong posty2rcoef7 :15;
        kulong :1;
        klong posty2rcoef8 :15;
        kulong :1;
        kulong :16;
    } bit;
};

/*  structure of posty2rclpthu  */
union _IoShdrPosty2rclpthu
{
    kulong word[2];
    struct
    {
        kulong posty2rclpthu0 :16;
        kulong posty2rclpthu1 :16;
        kulong posty2rclpthu2 :16;
        kulong :16;
    } bit;
};

/*  structure of posty2rclpthl  */
union _IoShdrPosty2rclpthl
{
    kulong word[2];
    struct
    {
        kulong posty2rclpthl0 :16;
        kulong posty2rclpthl1 :16;
        kulong posty2rclpthl2 :16;
        kulong :16;
    } bit;
};

/*  structure of postsel1   */
union _IoShdrPostsel1
{
    kulong word;
    struct
    {
        kulong postsel1 :1;
        kulong :31;
    } bit;
};

/*  structure of postmulqpos    */
union _IoShdrPostmulqpos
{
    kulong word;
    struct
    {
        kulong postmulqpos :2;
        kulong :30;
    } bit;
};

/*  structure of evknb      */
union _IoShdrEvknb
{
    kulong word[5];
    struct
    {
        kulong :12;
        kulong :4;
        kulong evknb1 :12;
        kulong :4;
        kulong evknb2 :12;
        kulong :4;
        kulong evknb3 :12;
        kulong :4;
        kulong evknb4 :12;
        kulong :4;
        kulong evknb5 :12;
        kulong :4;
        kulong evknb6 :12;
        kulong :4;
        kulong evknb7 :12;
        kulong :4;
        kulong evknb8 :12;
        kulong :4;
        kulong evknb9 :12;
        kulong :4;
    } bit;
};

/*  structure of evknofs    */
union _IoShdrEvknofs
{
    kulong word[5];
    struct
    {
        kulong evknofs0 :14;
        kulong :2;
        kulong evknofs1 :14;
        kulong :2;
        kulong evknofs2 :14;
        kulong :2;
        kulong evknofs3 :14;
        kulong :2;
        kulong evknofs4 :14;
        kulong :2;
        kulong evknofs5 :14;
        kulong :2;
        kulong evknofs6 :14;
        kulong :2;
        kulong evknofs7 :14;
        kulong :2;
        kulong evknofs8 :14;
        kulong :2;
        kulong evknofs9 :14;
        kulong :2;
    } bit;
};

/*  structure of evknsl     */
union _IoShdrEvknsl
{
    kulong word[5];
    struct
    {
        klong evknsl0 :15;
        kulong :1;
        klong evknsl1 :15;
        kulong :1;
        klong evknsl2 :15;
        kulong :1;
        klong evknsl3 :15;
        kulong :1;
        klong evknsl4 :15;
        kulong :1;
        klong evknsl5 :15;
        kulong :1;
        klong evknsl6 :15;
        kulong :1;
        klong evknsl7 :15;
        kulong :1;
        klong evknsl8 :15;
        kulong :1;
        klong evknsl9 :15;
        kulong :1;
    } bit;
};

/*  structure of postsel0   */
union _IoShdrPostsel0
{
    kulong word;
    struct
    {
        kulong postsel0 :1;
        kulong :31;
    } bit;
};

/*  structure of hdrcssmd   */
union _IoShdrHdrcssmd
{
    kulong word;
    struct
    {
        kulong hdrcssmd :1;
        kulong :31;
    } bit;
};

/*  structure of ch0mode    */
union _IoShdrCh0mode
{
    kulong word;
    struct
    {
        kulong wen0 :1;
        kulong :3;
        kulong :2;
        kulong :2;
        kulong :1;
        kulong :1;
        kulong :2;
        kulong :1;
        kulong :3;
        kulong drcen0 :1;
        kulong :3;
        kulong cssmd0 :2;
        kulong :10;
    } bit;
};


KConstType k_jdsshdr3_get_type(void);
KJdsshdr3* k_jdsshdr3_new(void);


#endif/*__K_JDSSHDR3_H__*/
