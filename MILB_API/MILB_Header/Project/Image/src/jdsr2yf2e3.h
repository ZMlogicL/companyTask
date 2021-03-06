/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-11
 *@author            :郑蛘钊
 *@brief             :jdsr2yf2e3
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __JDSR2Y_F2E3_H__
#define __JDSR2Y_F2E3_H__


#include <klib.h>


#define JDSR2Y_TYPE_F2E3	        (jdsr2y_f2e3_get_type())
#define JDSR2Y_F2E3(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), Jdsr2yF2e3))
#define JDSR2Y_IS_F2E3(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSR2Y_TYPE_F2E3))


typedef struct _Jdsr2yF2e3          Jdsr2yF2e3;
typedef struct _Jdsr2yF2e3Private   Jdsr2yF2e3Private;

typedef union _IoR2yTrm0h           IoR2yTrm0h;
typedef union _IoR2yTrm0v           IoR2yTrm0v;
typedef union _IoR2yTrmbh           IoR2yTrmbh;
typedef union _IoR2yTrmbv           IoR2yTrmbv;
typedef union _IoR2yTrmch           IoR2yTrmch;
typedef union _IoR2yTrmcv           IoR2yTrmcv;
typedef union _IoR2yYyw0ltt         IoR2yYyw0ltt;
typedef union _IoR2yYywaa           IoR2yYywaa;
typedef union _IoR2yYywadef         IoR2yYywadef;
typedef union _IoR2yYywaofsx        IoR2yYywaofsx;
typedef union _IoR2yYyw1a           IoR2yYyw1a;
typedef union _IoR2yYyw1def         IoR2yYyw1def;
typedef union _IoR2yRsz1hsta        IoR2yRsz1hsta;
typedef union _IoR2yRsz1hpit        IoR2yRsz1hpit;
typedef union _IoR2yRsz1vsta        IoR2yRsz1vsta;
typedef union _IoR2yRsz1vpit        IoR2yRsz1vpit;
typedef union _IoR2yTrm1h           IoR2yTrm1h;
typedef union _IoR2yTrm1v           IoR2yTrm1v;
typedef union _IoR2yYyw2a           IoR2yYyw2a;
typedef union _IoR2yYyw2def         IoR2yYyw2def;
typedef union _IoR2yRsz2hsta        IoR2yRsz2hsta;
typedef union _IoR2yRsz2hpit        IoR2yRsz2hpit;
typedef union _IoR2yRsz2vsta        IoR2yRsz2vsta;
typedef union _IoR2yRsz2vpit        IoR2yRsz2vpit;
typedef union _IoR2yTrm2h           IoR2yTrm2h;
typedef union _IoR2yTrm2v           IoR2yTrm2v;
typedef union _IoR2yEe0ctl          IoR2yEe0ctl;
typedef union _IoR2yEe0hpfk         IoR2yEe0hpfk;
typedef union _IoR2yEe0nrlv         IoR2yEe0nrlv;
typedef union _IoR2yEe0corpof       IoR2yEe0corpof;
typedef union _IoR2yEe0corpga       IoR2yEe0corpga;
typedef union _IoR2yEe0corpbd       IoR2yEe0corpbd;
typedef union _IoR2yEe0cormof       IoR2yEe0cormof;
typedef union _IoR2yEe0cormga       IoR2yEe0cormga;
typedef union _IoR2yEe0cormbd       IoR2yEe0cormbd;
typedef union _IoR2yEe0sclsup       IoR2yEe0sclsup;
typedef union _IoR2yEe0sclpof       IoR2yEe0sclpof;
typedef union _IoR2yEe0sclpga       IoR2yEe0sclpga;
typedef union _IoR2yEe0sclpbd       IoR2yEe0sclpbd;
typedef union _IoR2yEe0sclmof       IoR2yEe0sclmof;
typedef union _IoR2yEe0sclmga       IoR2yEe0sclmga;
typedef union _IoR2yEe0sclmbd       IoR2yEe0sclmbd;
typedef union _IoR2yEe0tonpof       IoR2yEe0tonpof;
typedef union _IoR2yEe0tonpga       IoR2yEe0tonpga;
typedef union _IoR2yEe0tonpbd       IoR2yEe0tonpbd;
typedef union _IoR2yEe0tonmof       IoR2yEe0tonmof;
typedef union _IoR2yEe0tonmga       IoR2yEe0tonmga;
typedef union _IoR2yEe0tonmbd       IoR2yEe0tonmbd;
typedef union _IoR2yEe0clppof       IoR2yEe0clppof;
typedef union _IoR2yEe0clppga       IoR2yEe0clppga;
typedef union _IoR2yEe0clppbd       IoR2yEe0clppbd;


struct _Jdsr2yF2e3
{
    KObject parent;
};


/*  structure of trm0h  (2841_C278h)    */
union _IoR2yTrm0h
{
    kulong word;
    struct
    {
        kulong trm0hsta :13;
        kulong :3;
        kulong trm0hsiz :13;
        kulong :3;
    } bit;
};

/*  structure of trm0v  (2841_C27Ch)    */
union _IoR2yTrm0v
{
    kulong word;
    struct
    {
        kulong trm0vsta :14;
        kulong :2;
        kulong trm0vsiz :14;
        kulong :2;
    } bit;
};

/*  structure of trmbh  (2841_C280h)    */
union _IoR2yTrmbh
{
    kulong word;
    struct
    {
        kulong trmbhsta :13;
        kulong :3;
        kulong trmbhsiz :13;
        kulong :3;
    } bit;
};

/*  structure of trmbv  (2841_C284h)    */
union _IoR2yTrmbv
{
    kulong word;
    struct
    {
        kulong trmbvsta :14;
        kulong :2;
        kulong trmbvsiz :14;
        kulong :2;
    } bit;
};

/*  structure of trmch  (2841_C288h)    */
union _IoR2yTrmch
{
    kulong word;
    struct
    {
        kulong trmchsta :13;
        kulong :3;
        kulong trmchsiz :13;
        kulong :3;
    } bit;
};

/*  structure of trmcv  (2841_C28Ch)    */
union _IoR2yTrmcv
{
    kulong word;
    struct
    {
        kulong trmcvsta :14;
        kulong :2;
        kulong trmcvsiz :14;
        kulong :2;
    } bit;
};

/*  structure of yyw0ltt    (2841_C290h)    */
union _IoR2yYyw0ltt
{
    kulong word;
    struct
    {
        kulong yyw0ltt :14;
        kulong :18;
    } bit;
};

/*  structure of yywaa  (2841_C2A0h)    */
union _IoR2yYywaa
{
    kulong word[2][4];
    struct
    {
        kulong yywaa00 :32;
        kulong yywaa01 :32;
        kulong yywaa02 :32;
        kulong yywaa03 :32;
        kulong yywaa10 :32;
        kulong yywaa11 :32;
        kulong yywaa12 :32;
        kulong yywaa13 :32;
    } bit;
};

/*  structure of yywadef    (2841_C2C0h)    */
union _IoR2yYywadef
{
    kulong word;
    struct
    {
        klong yywadef :17;
        kulong :15;
    } bit;
};

/*  structure of yywaofsx   (2841_C2C8h)    */
union _IoR2yYywaofsx
{
    kulong word[2];
    struct
    {
        kulong yywaofsx0 :12;
        kulong :4;
        kulong yywaofsx1 :12;
        kulong :4;
        kulong yywaofsx2 :12;
        kulong :4;
        kulong yywaofsx3 :12;
        kulong :4;
    } bit;
};

/*  structure of yyw1a  (2841_C300h)    */
union _IoR2yYyw1a
{
    kulong word[3][4];
    struct
    {
        kulong yyw1a00 :32;
        kulong yyw1a01 :32;
        kulong yyw1a02 :32;
        kulong yyw1a03 :32;
        kulong yyw1a10 :32;
        kulong yyw1a11 :32;
        kulong yyw1a12 :32;
        kulong yyw1a13 :32;
        kulong yyw1a20 :32;
        kulong yyw1a21 :32;
        kulong yyw1a22 :32;
        kulong yyw1a23 :32;
    } bit;
};

/*  structure of yyw1def    (2841_C340h)    */
union _IoR2yYyw1def
{
    kulong word[2];
    struct
    {
        klong yyw1def0 :17;
        kulong :15;
        klong yyw1def1 :17;
        kulong :15;
    } bit;
};

/*  structure of rsz1hsta   (2841_C348h)    */
union _IoR2yRsz1hsta
{
    kulong word;
    struct
    {
        kulong rsz1hsta :20;
        kulong :12;
    } bit;
};

/*  structure of rsz1hpit   (2841_C34Ch)    */
union _IoR2yRsz1hpit
{
    kulong word;
    struct
    {
        kulong rsz1hpit :16;
        kulong :16;
    } bit;
};

/*  structure of rsz1vsta   (2841_C350h)    */
union _IoR2yRsz1vsta
{
    kulong word;
    struct
    {
        kulong rsz1vsta :20;
        kulong :12;
    } bit;
};

/*  structure of rsz1vpit   (2841_C354h)    */
union _IoR2yRsz1vpit
{
    kulong word;
    struct
    {
        kulong rsz1vpit :16;
        kulong :16;
    } bit;
};

/*  structure of trm1h  (2841_C358h)    */
union _IoR2yTrm1h
{
    kulong word;
    struct
    {
        kulong trm1hsta :13;
        kulong :3;
        kulong trm1hsiz :13;
        kulong :3;
    } bit;
};

/*  structure of trm1v  (2841_C35Ch)    */
union _IoR2yTrm1v
{
    kulong word;
    struct
    {
        kulong trm1vsta :14;
        kulong :2;
        kulong trm1vsiz :14;
        kulong :2;
    } bit;
};

/*  structure of yyw2a  (2841_C380h)    */
union _IoR2yYyw2a
{
    kulong word[4];
    struct
    {
        kulong yyw2a0 :32;
        kulong yyw2a1 :32;
        kulong yyw2a2 :32;
        kulong yyw2a3 :32;
    } bit;
};

/*  structure of yyw2def    (2841_C390h)    */
union _IoR2yYyw2def
{
    kulong word;
    struct
    {
        klong yyw2def :17;
        kulong :15;
    } bit;
};

/*  structure of rsz2hsta   (2841_C394h)    */
union _IoR2yRsz2hsta
{
    kulong word;
    struct
    {
        kulong rsz2hsta :20;
        kulong :12;
    } bit;
};

/*  structure of rsz2hpit   (2841_C398h)    */
union _IoR2yRsz2hpit
{
    kulong word;
    struct
    {
        kulong rsz2hpit :16;
        kulong :16;
    } bit;
};

/*  structure of rsz2vsta   (2841_C39Ch)    */
union _IoR2yRsz2vsta
{
    kulong word;
    struct
    {
        kulong rsz2vsta :20;
        kulong :12;
    } bit;
};

/*  structure of rsz2vpit   (2841_C3A0h)    */
union _IoR2yRsz2vpit
{
    kulong word;
    struct
    {
        kulong rsz2vpit :16;
        kulong :16;
    } bit;
};

/*  structure of trm2h  (2841_C3A4h)    */
union _IoR2yTrm2h
{
    kulong word;
    struct
    {
        kulong trm2hsta :13;
        kulong :3;
        kulong trm2hsiz :13;
        kulong :3;
    } bit;
};

/*  structure of trm2v  (2841_C3A8h)    */
union _IoR2yTrm2v
{
    kulong word;
    struct
    {
        kulong trm2vsta :14;
        kulong :2;
        kulong trm2vsiz :14;
        kulong :2;
    } bit;
};

/*  structure of ee0ctl (2841_C400h)    */
union _IoR2yEe0ctl
{
    kulong word;
    struct
    {
        kulong ee0en :1;
        kulong :3;
        kulong ee0tc :1;
        kulong :27;
    } bit;
};

/*  structure of ee0hpfk    (2841_C408h)    */
union _IoR2yEe0hpfk
{
    kulong word[2];
    struct
    {
        kulong ee0hpfk0 :10;
        kulong :6;
        klong ee0hpfk1 :8;
        klong ee0hpfk2 :8;
        klong ee0hpfk3 :8;
        klong ee0hpfk4 :8;
        klong ee0hpfk5 :8;
        kulong :8;
    } bit;
};

/*  structure of ee0nrlv    (2841_C410h)    */
union _IoR2yEe0nrlv
{
    kulong word;
    struct
    {
        kulong ee0nrlv :4;
        kulong :28;
    } bit;
};

/*  structure of ee0corpof  (2841_C414h)    */
union _IoR2yEe0corpof
{
    kulong word;
    struct
    {
        kulong ee0corpof0 :8;
        kulong ee0corpof1 :8;
        kulong ee0corpof2 :8;
        kulong ee0corpof3 :8;
    } bit;
};

/*  structure of ee0corpga  (2841_C418h)    */
union _IoR2yEe0corpga
{
    kulong word;
    struct
    {
        klong ee0corpga0 :8;
        klong ee0corpga1 :8;
        klong ee0corpga2 :8;
        klong ee0corpga3 :8;
    } bit;
};

/*  structure of ee0corpbd  (2841_C41Ch)    */
union _IoR2yEe0corpbd
{
    kulong word;
    struct
    {
        kulong ee0corpbd1 :8;
        kulong ee0corpbd2 :8;
        kulong ee0corpbd3 :8;
        kulong :8;
    } bit;
};

/*  structure of ee0cormof  (2841_C420h)    */
union _IoR2yEe0cormof
{
    kulong word;
    struct
    {
        kulong ee0cormof0 :8;
        kulong ee0cormof1 :8;
        kulong ee0cormof2 :8;
        kulong ee0cormof3 :8;
    } bit;
};

/*  structure of ee0cormga  (2841_C424h)    */
union _IoR2yEe0cormga
{
    kulong word;
    struct
    {
        klong ee0cormga0 :8;
        klong ee0cormga1 :8;
        klong ee0cormga2 :8;
        klong ee0cormga3 :8;
    } bit;
};

/*  structure of ee0cormbd  (2841_C428h)    */
union _IoR2yEe0cormbd
{
    kulong word;
    struct
    {
        kulong ee0cormbd1 :8;
        kulong ee0cormbd2 :8;
        kulong ee0cormbd3 :8;
        kulong :8;
    } bit;
};

/*  structure of ee0sclsup  (2841_C42Ch)    */
union _IoR2yEe0sclsup
{
    kulong word;
    struct
    {
        kulong ee0sclsup :6;
        kulong :26;
    } bit;
};

/*  structure of ee0sclpof  (2841_C430h)    */
union _IoR2yEe0sclpof
{
    kulong word[3];
    struct
    {
        kulong ee0sclpof0 :8;
        kulong ee0sclpof1 :8;
        kulong ee0sclpof2 :8;
        kulong ee0sclpof3 :8;
        kulong ee0sclpof4 :8;
        kulong ee0sclpof5 :8;
        kulong ee0sclpof6 :8;
        kulong ee0sclpof7 :8;
        kulong ee0sclpof8 :8;
        kulong ee0sclpof9 :8;
        kulong :16;
    } bit;
};

/*  structure of ee0sclpga  (2841_C440h)    */
union _IoR2yEe0sclpga
{
    kulong word[5];
    struct
    {
        klong ee0sclpga0 :13;
        kulong :3;
        klong ee0sclpga1 :13;
        kulong :3;
        klong ee0sclpga2 :13;
        kulong :3;
        klong ee0sclpga3 :13;
        kulong :3;
        klong ee0sclpga4 :13;
        kulong :3;
        klong ee0sclpga5 :13;
        kulong :3;
        klong ee0sclpga6 :13;
        kulong :3;
        klong ee0sclpga7 :13;
        kulong :3;
        klong ee0sclpga8 :13;
        kulong :3;
        klong ee0sclpga9 :13;
        kulong :3;
    } bit;
};

/*  structure of ee0sclpbd  (2841_C460h)    */
union _IoR2yEe0sclpbd
{
    kulong word[3];
    struct
    {
        kulong ee0sclpbd1 :8;
        kulong ee0sclpbd2 :8;
        kulong ee0sclpbd3 :8;
        kulong ee0sclpbd4 :8;
        kulong ee0sclpbd5 :8;
        kulong ee0sclpbd6 :8;
        kulong ee0sclpbd7 :8;
        kulong ee0sclpbd8 :8;
        kulong ee0sclpbd9 :8;
        kulong :24;
    } bit;
};

/*  structure of ee0sclmof  (2841_C470h)    */
union _IoR2yEe0sclmof
{
    kulong word[3];
    struct
    {
        kulong ee0sclmof0 :8;
        kulong ee0sclmof1 :8;
        kulong ee0sclmof2 :8;
        kulong ee0sclmof3 :8;
        kulong ee0sclmof4 :8;
        kulong ee0sclmof5 :8;
        kulong ee0sclmof6 :8;
        kulong ee0sclmof7 :8;
        kulong ee0sclmof8 :8;
        kulong ee0sclmof9 :8;
        kulong :16;
    } bit;
};

/*  structure of ee0sclmga  (2841_C480h)    */
union _IoR2yEe0sclmga
{
    kulong word[5];
    struct
    {
        klong ee0sclmga0 :13;
        kulong :3;
        klong ee0sclmga1 :13;
        kulong :3;
        klong ee0sclmga2 :13;
        kulong :3;
        klong ee0sclmga3 :13;
        kulong :3;
        klong ee0sclmga4 :13;
        kulong :3;
        klong ee0sclmga5 :13;
        kulong :3;
        klong ee0sclmga6 :13;
        kulong :3;
        klong ee0sclmga7 :13;
        kulong :3;
        klong ee0sclmga8 :13;
        kulong :3;
        klong ee0sclmga9 :13;
        kulong :3;
    } bit;
};

/*  structure of ee0sclmbd  (2841_C4A0h)    */
union _IoR2yEe0sclmbd
{
    kulong word[3];
    struct
    {
        kulong ee0sclmbd1 :8;
        kulong ee0sclmbd2 :8;
        kulong ee0sclmbd3 :8;
        kulong ee0sclmbd4 :8;
        kulong ee0sclmbd5 :8;
        kulong ee0sclmbd6 :8;
        kulong ee0sclmbd7 :8;
        kulong ee0sclmbd8 :8;
        kulong ee0sclmbd9 :8;
        kulong :24;
    } bit;
};

/*  structure of ee0tonpof  (2841_C4B0h)    */
union _IoR2yEe0tonpof
{
    kulong word[2];
    struct
    {
        kulong ee0tonpof0 :7;
        kulong :1;
        kulong ee0tonpof1 :7;
        kulong :1;
        kulong ee0tonpof2 :7;
        kulong :1;
        kulong ee0tonpof3 :7;
        kulong :1;
        kulong ee0tonpof4 :7;
        kulong :25;
    } bit;
};

/*  structure of ee0tonpga  (2841_C4C0h)    */
union _IoR2yEe0tonpga
{
    kulong word[3];
    struct
    {
        klong ee0tonpga0 :9;
        kulong :7;
        klong ee0tonpga1 :9;
        kulong :7;
        klong ee0tonpga2 :9;
        kulong :7;
        klong ee0tonpga3 :9;
        kulong :7;
        klong ee0tonpga4 :9;
        kulong :23;
    } bit;
};

/*  structure of ee0tonpbd  (2841_C4D0h)    */
union _IoR2yEe0tonpbd
{
    kulong word;
    struct
    {
        kulong ee0tonpbd1 :7;
        kulong :1;
        kulong ee0tonpbd2 :7;
        kulong :1;
        kulong ee0tonpbd3 :7;
        kulong :1;
        kulong ee0tonpbd4 :7;
        kulong :1;
    } bit;
};

/*  structure of ee0tonmof  (2841_C4D8h)    */
union _IoR2yEe0tonmof
{
    kulong word[2];
    struct
    {
        kulong ee0tonmof0 :7;
        kulong :1;
        kulong ee0tonmof1 :7;
        kulong :1;
        kulong ee0tonmof2 :7;
        kulong :1;
        kulong ee0tonmof3 :7;
        kulong :1;
        kulong ee0tonmof4 :7;
        kulong :25;
    } bit;
};

/*  structure of ee0tonmga  (2841_C4E0h)    */
union _IoR2yEe0tonmga
{
    kulong word[3];
    struct
    {
        klong ee0tonmga0 :9;
        kulong :7;
        klong ee0tonmga1 :9;
        kulong :7;
        klong ee0tonmga2 :9;
        kulong :7;
        klong ee0tonmga3 :9;
        kulong :7;
        klong ee0tonmga4 :9;
        kulong :23;
    } bit;
};

/*  structure of ee0tonmbd  (2841_C4F0h)    */
union _IoR2yEe0tonmbd
{
    kulong word;
    struct
    {
        kulong ee0tonmbd1 :7;
        kulong :1;
        kulong ee0tonmbd2 :7;
        kulong :1;
        kulong ee0tonmbd3 :7;
        kulong :1;
        kulong ee0tonmbd4 :7;
        kulong :1;
    } bit;
};

/*  structure of ee0clppof  (2841_C4F4h)    */
union _IoR2yEe0clppof
{
    kulong word;
    struct
    {
        kulong ee0clppof0 :7;
        kulong :1;
        kulong ee0clppof1 :7;
        kulong :1;
        kulong ee0clppof2 :7;
        kulong :9;
    } bit;
};

/*  structure of ee0clppga  (2841_C4F8h)    */
union _IoR2yEe0clppga
{
    kulong word;
    struct
    {
        klong ee0clppga0 :8;
        klong ee0clppga1 :8;
        klong ee0clppga2 :8;
        kulong :8;
    } bit;
};

/*  structure of ee0clppbd  (2841_C4FCh)    */
union _IoR2yEe0clppbd
{
    kulong word;
    struct
    {
        kulong ee0clppbd1 :8;
        kulong ee0clppbd2 :8;
        kulong :16;
    } bit;
};


KConstType  jdsr2y_f2e3_get_type(void);
Jdsr2yF2e3* jdsr2y_f2e3_new(void);


#endif/*__JDSR2Y_F2E3_H__*/
