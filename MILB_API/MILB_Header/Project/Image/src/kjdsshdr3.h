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

#define K_TYPE_JDSSHDR3	(k_jdsshdr3_get_type())
#define K_JDSSHDR3(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsshdr3))
#define K_IS_JDSSHDR3(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSSHDR3))

typedef struct _KJdsshdr3 KJdsshdr3;
typedef struct _KJdsshdr3Private KJdsshdr3Private;

typedef union _IoShdrWghtr2yclp IoShdrWghtr2yclp;
typedef union _IoShdrWghtbase IoShdrWghtbase;
typedef union _IoShdrWghtrofs IoShdrWghtrofs;
typedef union _IoShdrWghtgofs IoShdrWghtgofs;
typedef union _IoShdrWghtbofs IoShdrWghtbofs;
typedef union _IoShdrWghtrsl IoShdrWghtrsl;
typedef union _IoShdrWghtgsl IoShdrWghtgsl;
typedef union _IoShdrWghtbsl IoShdrWghtbsl;
typedef union _IoShdrWghtrb IoShdrWghtrb;
typedef union _IoShdrWghtgb IoShdrWghtgb;
typedef union _IoShdrWghtbb IoShdrWghtbb;
typedef union _IoShdrIsoth IoShdrIsoth;
typedef union _IoShdrIsocoef IoShdrIsocoef;
typedef union _IoShdrSatth IoShdrSatth;
typedef union _IoShdrExp77md IoShdrExp77md;
typedef union _IoShdrFmdsel IoShdrFmdsel;
typedef union _IoShdrTlut IoShdrTlut;
typedef union _IoShdrPmskmd IoShdrPmskmd;
typedef union _IoShdrSpnren IoShdrSpnren;
typedef union _IoShdrSpebd IoShdrSpebd;
typedef union _IoShdrSpeof IoShdrSpeof;
typedef union _IoShdrSpebld IoShdrSpebld;
typedef union _IoShdrMsky2rclpul IoShdrMsky2rclpul;
typedef union _IoShdrMsky2rclpll IoShdrMsky2rclpll;
typedef union _IoShdrMsky2rclpus IoShdrMsky2rclpus;
typedef union _IoShdrMsky2rclpls IoShdrMsky2rclpls;
typedef union _IoShdrAlpha IoShdrAlpha;
typedef union _IoShdrLpfc IoShdrLpfc;
typedef union _IoShdrBldofs IoShdrBldofs;
typedef union _IoShdrBldsl IoShdrBldsl;
typedef union _IoShdrBldb IoShdrBldb;
typedef union _IoShdrNormgain IoShdrNormgain;
typedef union _IoShdrNormofs IoShdrNormofs;
typedef union _IoShdrMskmd IoShdrMskmd;
typedef union _IoShdrBldsel IoShdrBldsel;
typedef union _IoShdrAlphasel IoShdrAlphasel;
typedef union _IoShdrAlphaval IoShdrAlphaval;
typedef union _IoShdrPostsft1rnd IoShdrPostsft1rnd;
typedef union _IoShdrPosty2rcoef IoShdrPosty2rcoef;
typedef union _IoShdrPosty2rclpthu IoShdrPosty2rclpthu;
typedef union _IoShdrPosty2rclpthl IoShdrPosty2rclpthl;
typedef union _IoShdrPostsel1 IoShdrPostsel1;
typedef union _IoShdrPostmulqpos IoShdrPostmulqpos;
typedef union _IoShdrEvknb IoShdrEvknb;
typedef union _IoShdrEvknofs IoShdrEvknofs;
typedef union _IoShdrEvknsl IoShdrEvknsl;
typedef union _IoShdrPostsel0 IoShdrPostsel0;
typedef union _IoShdrHdrcssmd IoShdrHdrcssmd;
typedef union _IoShdrCh0mode IoShdrCh0mode;


struct _KJdsshdr3
{
    KObject parent;
};

/*  structure of wghtr2yclp */
union _IoShdrWghtr2yclp
{
    unsigned long word;
    struct
    {
        unsigned long wghtr2yclpu :8;
        unsigned long :8;
        unsigned long wghtr2yclpl :8;
        unsigned long :8;
    } bit;
};

/*  structure of wghtbase   */
union _IoShdrWghtbase
{
    unsigned long word;
    struct
    {
        unsigned long wghtbase :1;
        unsigned long :31;
    } bit;
};

/*  structure of wghtrofs   */
union _IoShdrWghtrofs
{
    unsigned long word[3];
    struct
    {
        unsigned long wghtrofs0 :12;
        unsigned long :4;
        unsigned long wghtrofs1 :12;
        unsigned long :4;
        unsigned long wghtrofs2 :12;
        unsigned long :4;
        unsigned long wghtrofs3 :12;
        unsigned long :4;
        unsigned long wghtrofs4 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of wghtgofs   */
union _IoShdrWghtgofs
{
    unsigned long word[3];
    struct
    {
        unsigned long wghtgofs0 :12;
        unsigned long :4;
        unsigned long wghtgofs1 :12;
        unsigned long :4;
        unsigned long wghtgofs2 :12;
        unsigned long :4;
        unsigned long wghtgofs3 :12;
        unsigned long :4;
        unsigned long wghtgofs4 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of wghtbofs   */
union _IoShdrWghtbofs
{
    unsigned long word[3];
    struct
    {
        unsigned long wghtbofs0 :12;
        unsigned long :4;
        unsigned long wghtbofs1 :12;
        unsigned long :4;
        unsigned long wghtbofs2 :12;
        unsigned long :4;
        unsigned long wghtbofs3 :12;
        unsigned long :4;
        unsigned long wghtbofs4 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of wghtrsl    */
union _IoShdrWghtrsl
{
    unsigned long word[3];
    struct
    {
        unsigned long wghtrsl0 :12;
        unsigned long :4;
        unsigned long wghtrsl1 :12;
        unsigned long :4;
        unsigned long wghtrsl2 :12;
        unsigned long :4;
        unsigned long wghtrsl3 :12;
        unsigned long :4;
        unsigned long wghtrsl4 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of wghtgsl    */
union _IoShdrWghtgsl
{
    unsigned long word[3];
    struct
    {
        unsigned long wghtgsl0 :12;
        unsigned long :4;
        unsigned long wghtgsl1 :12;
        unsigned long :4;
        unsigned long wghtgsl2 :12;
        unsigned long :4;
        unsigned long wghtgsl3 :12;
        unsigned long :4;
        unsigned long wghtgsl4 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of wghtbsl    */
union _IoShdrWghtbsl
{
    unsigned long word[3];
    struct
    {
        unsigned long wghtbsl0 :12;
        unsigned long :4;
        unsigned long wghtbsl1 :12;
        unsigned long :4;
        unsigned long wghtbsl2 :12;
        unsigned long :4;
        unsigned long wghtbsl3 :12;
        unsigned long :4;
        unsigned long wghtbsl4 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of wghtrb     */
union _IoShdrWghtrb
{
    unsigned long word[3];
    struct
    {
        unsigned long :16;
        unsigned long wghtrb1 :8;
        unsigned long :8;
        unsigned long wghtrb2 :8;
        unsigned long :8;
        unsigned long wghtrb3 :8;
        unsigned long :8;
        unsigned long wghtrb4 :8;
        unsigned long :24;
    } bit;
};

/*  structure of wghtgb     */
union _IoShdrWghtgb
{
    unsigned long word[3];
    struct
    {
        unsigned long :16;
        unsigned long wghtgb1 :8;
        unsigned long :8;
        unsigned long wghtgb2 :8;
        unsigned long :8;
        unsigned long wghtgb3 :8;
        unsigned long :8;
        unsigned long wghtgb4 :8;
        unsigned long :24;
    } bit;
};

/*  structure of wghtbb */
union _IoShdrWghtbb
{
    unsigned long word[3];
    struct
    {
        unsigned long :16;
        unsigned long wghtbb1 :8;
        unsigned long :8;
        unsigned long wghtbb2 :8;
        unsigned long :8;
        unsigned long wghtbb3 :8;
        unsigned long :8;
        unsigned long wghtbb4 :8;
        unsigned long :24;
    } bit;
};

/*  structure of isoth      */
union _IoShdrIsoth
{
    unsigned long word;
    struct
    {
        unsigned long isoth2 :9;
        unsigned long :23;
    } bit;
};

/*  structure of isocoef    */
union _IoShdrIsocoef
{
    unsigned long word;
    struct
    {
        unsigned long iso2k0 :2;
        unsigned long iso2k1 :2;
        unsigned long iso2k2 :2;
        unsigned long :2;
        unsigned long iso2k3 :5;
        unsigned long :3;
        unsigned long iso2k4 :5;
        unsigned long :3;
        unsigned long iso2k5 :8;
    } bit;
};

/*  structure of satth      */
union _IoShdrSatth
{
    unsigned long word;
    struct
    {
        unsigned long satth :8;
        unsigned long :24;
    } bit;
};

/*  structure of exp77md    */
union _IoShdrExp77md
{
    unsigned long word;
    struct
    {
        unsigned long exp77md :1;
        unsigned long :31;
    } bit;
};

/*  structure of fmdsel     */
union _IoShdrFmdsel
{
    unsigned long word;
    struct
    {
        unsigned long fmdsel :1;
        unsigned long :31;
    } bit;
};

/*  structure of TLUT       */
union _IoShdrTlut
{
    unsigned long word[5];
    struct
    {
        unsigned long tlut0 :8;
        unsigned long tlut1 :8;
        unsigned long tlut2 :8;
        unsigned long tlut3 :8;
        unsigned long tlut4 :8;
        unsigned long tlut5 :8;
        unsigned long tlut6 :8;
        unsigned long tlut7 :8;
        unsigned long tlut8 :8;
        unsigned long tlut9 :8;
        unsigned long tlut10 :8;
        unsigned long tlut11 :8;
        unsigned long tlut12 :8;
        unsigned long tlut13 :8;
        unsigned long tlut14 :8;
        unsigned long tlut15 :8;
        unsigned long tlut16 :8;
        unsigned long :24;
    } bit;
};

/*  structure of pmskmd     */
union _IoShdrPmskmd
{
    unsigned long word;
    struct
    {
        unsigned long pmskmd :1;
        unsigned long :31;
    } bit;
};

/*  structure of spnren     */
union _IoShdrSpnren
{
    unsigned long word;
    struct
    {
        unsigned long spnren :1;
        unsigned long :31;
    } bit;
};

/*  structure of spebd      */
union _IoShdrSpebd
{
    unsigned long word[2];
    struct
    {
        unsigned long :16;
        unsigned long spebd1 :12;
        unsigned long :4;
        unsigned long spebd2 :12;
        unsigned long :4;
        unsigned long spebd3 :12;
        unsigned long :4;
    } bit;
};

/*  structure of speof      */
union _IoShdrSpeof
{
    unsigned long word[2];
    struct
    {
        unsigned long speof0 :12;
        unsigned long :4;
        unsigned long speof1 :12;
        unsigned long :4;
        unsigned long speof2 :12;
        unsigned long :4;
        unsigned long speof3 :12;
        unsigned long :4;
    } bit;
};

/*  structure of spebld     */
union _IoShdrSpebld
{
    unsigned long word;
    struct
    {
        unsigned long spebld :3;
        unsigned long :29;
    } bit;
};

/*  structure of msky2rclpul    */
union _IoShdrMsky2rclpul
{
    unsigned long word[2];
    struct
    {
        unsigned long msky2rclpul0 :12;
        unsigned long :4;
        unsigned long msky2rclpul1 :12;
        unsigned long :4;
        unsigned long msky2rclpul2 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of msky2rclpll    */
union _IoShdrMsky2rclpll
{
    unsigned long word[2];
    struct
    {
        unsigned long msky2rclpll0 :12;
        unsigned long :4;
        unsigned long msky2rclpll1 :12;
        unsigned long :4;
        unsigned long msky2rclpll2 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of msky2rclpus    */
union _IoShdrMsky2rclpus
{
    unsigned long word[2];
    struct
    {
        unsigned long msky2rclpus0 :12;
        unsigned long :4;
        unsigned long msky2rclpus1 :12;
        unsigned long :4;
        unsigned long msky2rclpus2 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of msky2rclpls    */
union _IoShdrMsky2rclpls
{
    unsigned long word[2];
    struct
    {
        unsigned long msky2rclpls0 :12;
        unsigned long :4;
        unsigned long msky2rclpls1 :12;
        unsigned long :4;
        unsigned long msky2rclpls2 :12;
        unsigned long :4;
        unsigned long :16;
    } bit;
};

/*  structure of alpha      */
union _IoShdrAlpha
{
    unsigned long word;
    struct
    {
        unsigned long alpha :6;
        unsigned long :26;
    } bit;
};

/*  structure of lpfc       */
union _IoShdrLpfc
{
    unsigned long word[5];
    struct
    {
        unsigned long lpfc00 :8;
        unsigned long :8;
        unsigned long lpfc01 :8;
        unsigned long :8;
        unsigned long lpfc02 :8;
        unsigned long :8;
        unsigned long lpfc10 :8;
        unsigned long :8;
        unsigned long lpfc11 :8;
        unsigned long :8;
        unsigned long lpfc12 :8;
        unsigned long :8;
        unsigned long lpfc20 :8;
        unsigned long :8;
        unsigned long lpfc21 :8;
        unsigned long :8;
        unsigned long lpfc22 :8;
        unsigned long :8;
        unsigned long :16;
    } bit;
};

/*  structure of bldofs     */
union _IoShdrBldofs
{
    unsigned long word[4];
    struct
    {
        unsigned long bldofs0 :8;
        unsigned long :8;
        unsigned long bldofs1 :8;
        unsigned long :8;
        unsigned long bldofs2 :8;
        unsigned long :8;
        unsigned long bldofs3 :8;
        unsigned long :8;
        unsigned long bldofs4 :8;
        unsigned long :8;
        unsigned long bldofs5 :8;
        unsigned long :8;
        unsigned long bldofs6 :8;
        unsigned long :8;
        unsigned long :16;
    } bit;
};

/*  structure of bldsl  */
union _IoShdrBldsl
{
    unsigned long word[7];
    struct
    {
        unsigned long bldsl0 :16;
        unsigned long :16;
        unsigned long bldsl1 :16;
        unsigned long :16;
        unsigned long bldsl2 :16;
        unsigned long :16;
        unsigned long bldsl3 :16;
        unsigned long :16;
        unsigned long bldsl4 :16;
        unsigned long :16;
        unsigned long bldsl5 :16;
        unsigned long :16;
        unsigned long bldsl6 :16;
        unsigned long :16;
    } bit;
};

/*  structure of bldb   */
union _IoShdrBldb
{
    unsigned long word[4];
    struct
    {
        unsigned long :12;
        unsigned long :4;
        unsigned long bldb1 :12;
        unsigned long :4;
        unsigned long bldb2 :12;
        unsigned long :4;
        unsigned long bldb3 :12;
        unsigned long :4;
        unsigned long bldb4 :12;
        unsigned long :4;
        unsigned long bldb5 :12;
        unsigned long :4;
        unsigned long bldb6 :12;
        unsigned long :20;
    } bit;
};

/*  structure of normgain   */
union _IoShdrNormgain
{
    unsigned long word[2];
    struct
    {
        unsigned long normgain0 :8;
        unsigned long :8;
        unsigned long normgain1 :8;
        unsigned long :8;
        unsigned long normgain2 :8;
        unsigned long :8;
        unsigned long :16;
    } bit;
};

/*  structure of normofs    */
union _IoShdrNormofs
{
    unsigned long word[2];
    struct
    {
        unsigned long normofs0 :8;
        unsigned long :8;
        unsigned long normofs1 :8;
        unsigned long :8;
        unsigned long normofs2 :8;
        unsigned long :8;
        unsigned long :16;
    } bit;
};

/*  structure of mskmd      */
union _IoShdrMskmd
{
    unsigned long word;
    struct
    {
        unsigned long mskmd :2;
        unsigned long :30;
    } bit;
};

/*  structure of bldsel     */
union _IoShdrBldsel
{
    unsigned long word;
    struct
    {
        unsigned long bldsel :1;
        unsigned long :31;
    } bit;
};

/*  structure of alphasel   */
union _IoShdrAlphasel
{
    unsigned long word;
    struct
    {
        unsigned long alphasel :2;
        unsigned long :30;
    } bit;
};

/*  structure of alphaval   */
union _IoShdrAlphaval
{
    unsigned long word[2];
    struct
    {
        unsigned long alphavaly :8;
        unsigned long :8;
        unsigned long alphavalu :8;
        unsigned long :8;
        unsigned long alphavalv :8;
        unsigned long :24;
    } bit;
};

/*  structure of postsft1rnd    */
union _IoShdrPostsft1rnd
{
    unsigned long word;
    struct
    {
        unsigned long postsft1rnden :1;
        unsigned long :3;
        unsigned long :1;
        unsigned long :3;
        unsigned long :2;
        unsigned long :22;
    } bit;
};

/*  structure of posty2rcoef    */
union _IoShdrPosty2rcoef
{
    unsigned long word[5];
    struct
    {
        long posty2rcoef0 :15;
        unsigned long :1;
        long posty2rcoef1 :15;
        unsigned long :1;
        long posty2rcoef2 :15;
        unsigned long :1;
        long posty2rcoef3 :15;
        unsigned long :1;
        long posty2rcoef4 :15;
        unsigned long :1;
        long posty2rcoef5 :15;
        unsigned long :1;
        long posty2rcoef6 :15;
        unsigned long :1;
        long posty2rcoef7 :15;
        unsigned long :1;
        long posty2rcoef8 :15;
        unsigned long :1;
        unsigned long :16;
    } bit;
};

/*  structure of posty2rclpthu  */
union _IoShdrPosty2rclpthu
{
    unsigned long word[2];
    struct
    {
        unsigned long posty2rclpthu0 :16;
        unsigned long posty2rclpthu1 :16;
        unsigned long posty2rclpthu2 :16;
        unsigned long :16;
    } bit;
};

/*  structure of posty2rclpthl  */
union _IoShdrPosty2rclpthl
{
    unsigned long word[2];
    struct
    {
        unsigned long posty2rclpthl0 :16;
        unsigned long posty2rclpthl1 :16;
        unsigned long posty2rclpthl2 :16;
        unsigned long :16;
    } bit;
};

/*  structure of postsel1   */
union _IoShdrPostsel1
{
    unsigned long word;
    struct
    {
        unsigned long postsel1 :1;
        unsigned long :31;
    } bit;
};

/*  structure of postmulqpos    */
union _IoShdrPostmulqpos
{
    unsigned long word;
    struct
    {
        unsigned long postmulqpos :2;
        unsigned long :30;
    } bit;
};

/*  structure of evknb      */
union _IoShdrEvknb
{
    unsigned long word[5];
    struct
    {
        unsigned long :12;
        unsigned long :4;
        unsigned long evknb1 :12;
        unsigned long :4;
        unsigned long evknb2 :12;
        unsigned long :4;
        unsigned long evknb3 :12;
        unsigned long :4;
        unsigned long evknb4 :12;
        unsigned long :4;
        unsigned long evknb5 :12;
        unsigned long :4;
        unsigned long evknb6 :12;
        unsigned long :4;
        unsigned long evknb7 :12;
        unsigned long :4;
        unsigned long evknb8 :12;
        unsigned long :4;
        unsigned long evknb9 :12;
        unsigned long :4;
    } bit;
};

/*  structure of evknofs    */
union _IoShdrEvknofs
{
    unsigned long word[5];
    struct
    {
        unsigned long evknofs0 :14;
        unsigned long :2;
        unsigned long evknofs1 :14;
        unsigned long :2;
        unsigned long evknofs2 :14;
        unsigned long :2;
        unsigned long evknofs3 :14;
        unsigned long :2;
        unsigned long evknofs4 :14;
        unsigned long :2;
        unsigned long evknofs5 :14;
        unsigned long :2;
        unsigned long evknofs6 :14;
        unsigned long :2;
        unsigned long evknofs7 :14;
        unsigned long :2;
        unsigned long evknofs8 :14;
        unsigned long :2;
        unsigned long evknofs9 :14;
        unsigned long :2;
    } bit;
};

/*  structure of evknsl     */
union _IoShdrEvknsl
{
    unsigned long word[5];
    struct
    {
        long evknsl0 :15;
        unsigned long :1;
        long evknsl1 :15;
        unsigned long :1;
        long evknsl2 :15;
        unsigned long :1;
        long evknsl3 :15;
        unsigned long :1;
        long evknsl4 :15;
        unsigned long :1;
        long evknsl5 :15;
        unsigned long :1;
        long evknsl6 :15;
        unsigned long :1;
        long evknsl7 :15;
        unsigned long :1;
        long evknsl8 :15;
        unsigned long :1;
        long evknsl9 :15;
        unsigned long :1;
    } bit;
};

/*  structure of postsel0   */
union _IoShdrPostsel0
{
    unsigned long word;
    struct
    {
        unsigned long postsel0 :1;
        unsigned long :31;
    } bit;
};

/*  structure of hdrcssmd   */
union _IoShdrHdrcssmd
{
    unsigned long word;
    struct
    {
        unsigned long hdrcssmd :1;
        unsigned long :31;
    } bit;
};

/*  structure of ch0mode    */
union _IoShdrCh0mode
{
    unsigned long word;
    struct
    {
        unsigned long wen0 :1;
        unsigned long :3;
        unsigned long :2;
        unsigned long :2;
        unsigned long :1;
        unsigned long :1;
        unsigned long :2;
        unsigned long :1;
        unsigned long :3;
        unsigned long drcen0 :1;
        unsigned long :3;
        unsigned long cssmd0 :2;
        unsigned long :10;
    } bit;
};

KConstType k_jdsshdr3_get_type(void);
KJdsshdr3* k_jdsshdr3_new(void);

#endif/*__K_JDSSHDR3_H__*/

