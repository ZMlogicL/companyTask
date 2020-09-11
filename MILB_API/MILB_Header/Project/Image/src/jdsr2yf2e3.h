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

#define JDSR2Y_TYPE_F2E3	(jdsr2y_f2e3_get_type())
#define JDSR2Y_F2E3(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), Jdsr2yF2e3))
#define JDSR2Y_IS_F2E3(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSR2Y_TYPE_F2E3))

typedef struct _Jdsr2yF2e3 Jdsr2yF2e3;
typedef struct _Jdsr2yF2e3Private Jdsr2yF2e3Private;

typedef union _IoR2yTrm0h IoR2yTrm0h;
typedef union _IoR2yTrm0v IoR2yTrm0v;
typedef union _IoR2yTrmbh IoR2yTrmbh;
typedef union _IoR2yTrmbv IoR2yTrmbv;
typedef union _IoR2yTrmch IoR2yTrmch;
typedef union _IoR2yTrmcv IoR2yTrmcv;
typedef union _IoR2yYyw0ltt IoR2yYyw0ltt;
typedef union _IoR2yYywaa IoR2yYywaa;
typedef union _IoR2yYywadef IoR2yYywadef;
typedef union _IoR2yYywaofsx IoR2yYywaofsx;
typedef union _IoR2yYyw1a IoR2yYyw1a;
typedef union _IoR2yYyw1def IoR2yYyw1def;
typedef union _IoR2yRsz1hsta IoR2yRsz1hsta;
typedef union _IoR2yRsz1hpit IoR2yRsz1hpit;
typedef union _IoR2yRsz1vsta IoR2yRsz1vsta;
typedef union _IoR2yRsz1vpit IoR2yRsz1vpit;
typedef union _IoR2yTrm1h IoR2yTrm1h;
typedef union _IoR2yTrm1v IoR2yTrm1v;
typedef union _IoR2yYyw2a IoR2yYyw2a;
typedef union _IoR2yYyw2def IoR2yYyw2def;
typedef union _IoR2yRsz2hsta IoR2yRsz2hsta;
typedef union _IoR2yRsz2hpit IoR2yRsz2hpit;
typedef union _IoR2yRsz2vsta IoR2yRsz2vsta;
typedef union _IoR2yRsz2vpit IoR2yRsz2vpit;
typedef union _IoR2yTrm2h IoR2yTrm2h;
typedef union _IoR2yTrm2v IoR2yTrm2v;
typedef union _IoR2yEe0ctl IoR2yEe0ctl;
typedef union _IoR2yEe0hpfk IoR2yEe0hpfk;
typedef union _IoR2yEe0nrlv IoR2yEe0nrlv;
typedef union _IoR2yEe0corpof IoR2yEe0corpof;
typedef union _IoR2yEe0corpga IoR2yEe0corpga;
typedef union _IoR2yEe0corpbd IoR2yEe0corpbd;
typedef union _IoR2yEe0cormof IoR2yEe0cormof;
typedef union _IoR2yEe0cormga IoR2yEe0cormga;
typedef union _IoR2yEe0cormbd IoR2yEe0cormbd;
typedef union _IoR2yEe0sclsup IoR2yEe0sclsup;
typedef union _IoR2yEe0sclpof IoR2yEe0sclpof;
typedef union _IoR2yEe0sclpga IoR2yEe0sclpga;
typedef union _IoR2yEe0sclpbd IoR2yEe0sclpbd;
typedef union _IoR2yEe0sclmof IoR2yEe0sclmof;
typedef union _IoR2yEe0sclmga IoR2yEe0sclmga;
typedef union _IoR2yEe0sclmbd IoR2yEe0sclmbd;
typedef union _IoR2yEe0tonpof IoR2yEe0tonpof;
typedef union _IoR2yEe0tonpga IoR2yEe0tonpga;
typedef union _IoR2yEe0tonpbd IoR2yEe0tonpbd;
typedef union _IoR2yEe0tonmof IoR2yEe0tonmof;
typedef union _IoR2yEe0tonmga IoR2yEe0tonmga;
typedef union _IoR2yEe0tonmbd IoR2yEe0tonmbd;
typedef union _IoR2yEe0clppof IoR2yEe0clppof;
typedef union _IoR2yEe0clppga IoR2yEe0clppga;
typedef union _IoR2yEe0clppbd IoR2yEe0clppbd;

struct _Jdsr2yF2e3
{
    KObject parent;
};

/*  structure of trm0h  (2841_C278h)    */
union _IoR2yTrm0h
{
    unsigned long word;
    struct
    {
        unsigned long trm0hsta :13;
        unsigned long :3;
        unsigned long trm0hsiz :13;
        unsigned long :3;
    } bit;
};

/*  structure of trm0v  (2841_C27Ch)    */
union _IoR2yTrm0v
{
    unsigned long word;
    struct
    {
        unsigned long trm0vsta :14;
        unsigned long :2;
        unsigned long trm0vsiz :14;
        unsigned long :2;
    } bit;
};

/*  structure of trmbh  (2841_C280h)    */
union _IoR2yTrmbh
{
    unsigned long word;
    struct
    {
        unsigned long trmbhsta :13;
        unsigned long :3;
        unsigned long trmbhsiz :13;
        unsigned long :3;
    } bit;
};

/*  structure of trmbv  (2841_C284h)    */
union _IoR2yTrmbv
{
    unsigned long word;
    struct
    {
        unsigned long trmbvsta :14;
        unsigned long :2;
        unsigned long trmbvsiz :14;
        unsigned long :2;
    } bit;
};

/*  structure of trmch  (2841_C288h)    */
union _IoR2yTrmch
{
    unsigned long word;
    struct
    {
        unsigned long trmchsta :13;
        unsigned long :3;
        unsigned long trmchsiz :13;
        unsigned long :3;
    } bit;
};

/*  structure of trmcv  (2841_C28Ch)    */
union _IoR2yTrmcv
{
    unsigned long word;
    struct
    {
        unsigned long trmcvsta :14;
        unsigned long :2;
        unsigned long trmcvsiz :14;
        unsigned long :2;
    } bit;
};

/*  structure of yyw0ltt    (2841_C290h)    */
union _IoR2yYyw0ltt
{
    unsigned long word;
    struct
    {
        unsigned long yyw0ltt :14;
        unsigned long :18;
    } bit;
};

/*  structure of yywaa  (2841_C2A0h)    */
union _IoR2yYywaa
{
    unsigned long word[2][4];
    struct
    {
        unsigned long yywaa00 :32;
        unsigned long yywaa01 :32;
        unsigned long yywaa02 :32;
        unsigned long yywaa03 :32;
        unsigned long yywaa10 :32;
        unsigned long yywaa11 :32;
        unsigned long yywaa12 :32;
        unsigned long yywaa13 :32;
    } bit;
};

/*  structure of yywadef    (2841_C2C0h)    */
union _IoR2yYywadef
{
    unsigned long word;
    struct
    {
        long yywadef :17;
        unsigned long :15;
    } bit;
};

/*  structure of yywaofsx   (2841_C2C8h)    */
union _IoR2yYywaofsx
{
    unsigned long word[2];
    struct
    {
        unsigned long yywaofsx0 :12;
        unsigned long :4;
        unsigned long yywaofsx1 :12;
        unsigned long :4;
        unsigned long yywaofsx2 :12;
        unsigned long :4;
        unsigned long yywaofsx3 :12;
        unsigned long :4;
    } bit;
};

/*  structure of yyw1a  (2841_C300h)    */
union _IoR2yYyw1a
{
    unsigned long word[3][4];
    struct
    {
        unsigned long yyw1a00 :32;
        unsigned long yyw1a01 :32;
        unsigned long yyw1a02 :32;
        unsigned long yyw1a03 :32;
        unsigned long yyw1a10 :32;
        unsigned long yyw1a11 :32;
        unsigned long yyw1a12 :32;
        unsigned long yyw1a13 :32;
        unsigned long yyw1a20 :32;
        unsigned long yyw1a21 :32;
        unsigned long yyw1a22 :32;
        unsigned long yyw1a23 :32;
    } bit;
};

/*  structure of yyw1def    (2841_C340h)    */
union _IoR2yYyw1def
{
    unsigned long word[2];
    struct
    {
        long yyw1def0 :17;
        unsigned long :15;
        long yyw1def1 :17;
        unsigned long :15;
    } bit;
};

/*  structure of rsz1hsta   (2841_C348h)    */
union _IoR2yRsz1hsta
{
    unsigned long word;
    struct
    {
        unsigned long rsz1hsta :20;
        unsigned long :12;
    } bit;
};

/*  structure of rsz1hpit   (2841_C34Ch)    */
union _IoR2yRsz1hpit
{
    unsigned long word;
    struct
    {
        unsigned long rsz1hpit :16;
        unsigned long :16;
    } bit;
};

/*  structure of rsz1vsta   (2841_C350h)    */
union _IoR2yRsz1vsta
{
    unsigned long word;
    struct
    {
        unsigned long rsz1vsta :20;
        unsigned long :12;
    } bit;
};

/*  structure of rsz1vpit   (2841_C354h)    */
union _IoR2yRsz1vpit
{
    unsigned long word;
    struct
    {
        unsigned long rsz1vpit :16;
        unsigned long :16;
    } bit;
};

/*  structure of trm1h  (2841_C358h)    */
union _IoR2yTrm1h
{
    unsigned long word;
    struct
    {
        unsigned long trm1hsta :13;
        unsigned long :3;
        unsigned long trm1hsiz :13;
        unsigned long :3;
    } bit;
};

/*  structure of trm1v  (2841_C35Ch)    */
union _IoR2yTrm1v
{
    unsigned long word;
    struct
    {
        unsigned long trm1vsta :14;
        unsigned long :2;
        unsigned long trm1vsiz :14;
        unsigned long :2;
    } bit;
};

/*  structure of yyw2a  (2841_C380h)    */
union _IoR2yYyw2a
{
    unsigned long word[4];
    struct
    {
        unsigned long yyw2a0 :32;
        unsigned long yyw2a1 :32;
        unsigned long yyw2a2 :32;
        unsigned long yyw2a3 :32;
    } bit;
};

/*  structure of yyw2def    (2841_C390h)    */
union _IoR2yYyw2def
{
    unsigned long word;
    struct
    {
        long yyw2def :17;
        unsigned long :15;
    } bit;
};

/*  structure of rsz2hsta   (2841_C394h)    */
union _IoR2yRsz2hsta
{
    unsigned long word;
    struct
    {
        unsigned long rsz2hsta :20;
        unsigned long :12;
    } bit;
};

/*  structure of rsz2hpit   (2841_C398h)    */
union _IoR2yRsz2hpit
{
    unsigned long word;
    struct
    {
        unsigned long rsz2hpit :16;
        unsigned long :16;
    } bit;
};

/*  structure of rsz2vsta   (2841_C39Ch)    */
union _IoR2yRsz2vsta
{
    unsigned long word;
    struct
    {
        unsigned long rsz2vsta :20;
        unsigned long :12;
    } bit;
};

/*  structure of rsz2vpit   (2841_C3A0h)    */
union _IoR2yRsz2vpit
{
    unsigned long word;
    struct
    {
        unsigned long rsz2vpit :16;
        unsigned long :16;
    } bit;
};

/*  structure of trm2h  (2841_C3A4h)    */
union _IoR2yTrm2h
{
    unsigned long word;
    struct
    {
        unsigned long trm2hsta :13;
        unsigned long :3;
        unsigned long trm2hsiz :13;
        unsigned long :3;
    } bit;
};

/*  structure of trm2v  (2841_C3A8h)    */
union _IoR2yTrm2v
{
    unsigned long word;
    struct
    {
        unsigned long trm2vsta :14;
        unsigned long :2;
        unsigned long trm2vsiz :14;
        unsigned long :2;
    } bit;
};

/*  structure of ee0ctl (2841_C400h)    */
union _IoR2yEe0ctl
{
    unsigned long word;
    struct
    {
        unsigned long ee0en :1;
        unsigned long :3;
        unsigned long ee0tc :1;
        unsigned long :27;
    } bit;
};

/*  structure of ee0hpfk    (2841_C408h)    */
union _IoR2yEe0hpfk
{
    unsigned long word[2];
    struct
    {
        unsigned long ee0hpfk0 :10;
        unsigned long :6;
        long ee0hpfk1 :8;
        long ee0hpfk2 :8;
        long ee0hpfk3 :8;
        long ee0hpfk4 :8;
        long ee0hpfk5 :8;
        unsigned long :8;
    } bit;
};

/*  structure of ee0nrlv    (2841_C410h)    */
union _IoR2yEe0nrlv
{
    unsigned long word;
    struct
    {
        unsigned long ee0nrlv :4;
        unsigned long :28;
    } bit;
};

/*  structure of ee0corpof  (2841_C414h)    */
union _IoR2yEe0corpof
{
    unsigned long word;
    struct
    {
        unsigned long ee0corpof0 :8;
        unsigned long ee0corpof1 :8;
        unsigned long ee0corpof2 :8;
        unsigned long ee0corpof3 :8;
    } bit;
};

/*  structure of ee0corpga  (2841_C418h)    */
union _IoR2yEe0corpga
{
    unsigned long word;
    struct
    {
        long ee0corpga0 :8;
        long ee0corpga1 :8;
        long ee0corpga2 :8;
        long ee0corpga3 :8;
    } bit;
};

/*  structure of ee0corpbd  (2841_C41Ch)    */
union _IoR2yEe0corpbd
{
    unsigned long word;
    struct
    {
        unsigned long ee0corpbd1 :8;
        unsigned long ee0corpbd2 :8;
        unsigned long ee0corpbd3 :8;
        unsigned long :8;
    } bit;
};

/*  structure of ee0cormof  (2841_C420h)    */
union _IoR2yEe0cormof
{
    unsigned long word;
    struct
    {
        unsigned long ee0cormof0 :8;
        unsigned long ee0cormof1 :8;
        unsigned long ee0cormof2 :8;
        unsigned long ee0cormof3 :8;
    } bit;
};

/*  structure of ee0cormga  (2841_C424h)    */
union _IoR2yEe0cormga
{
    unsigned long word;
    struct
    {
        long ee0cormga0 :8;
        long ee0cormga1 :8;
        long ee0cormga2 :8;
        long ee0cormga3 :8;
    } bit;
};

/*  structure of ee0cormbd  (2841_C428h)    */
union _IoR2yEe0cormbd
{
    unsigned long word;
    struct
    {
        unsigned long ee0cormbd1 :8;
        unsigned long ee0cormbd2 :8;
        unsigned long ee0cormbd3 :8;
        unsigned long :8;
    } bit;
};

/*  structure of ee0sclsup  (2841_C42Ch)    */
union _IoR2yEe0sclsup
{
    unsigned long word;
    struct
    {
        unsigned long ee0sclsup :6;
        unsigned long :26;
    } bit;
};

/*  structure of ee0sclpof  (2841_C430h)    */
union _IoR2yEe0sclpof
{
    unsigned long word[3];
    struct
    {
        unsigned long ee0sclpof0 :8;
        unsigned long ee0sclpof1 :8;
        unsigned long ee0sclpof2 :8;
        unsigned long ee0sclpof3 :8;
        unsigned long ee0sclpof4 :8;
        unsigned long ee0sclpof5 :8;
        unsigned long ee0sclpof6 :8;
        unsigned long ee0sclpof7 :8;
        unsigned long ee0sclpof8 :8;
        unsigned long ee0sclpof9 :8;
        unsigned long :16;
    } bit;
};

/*  structure of ee0sclpga  (2841_C440h)    */
union _IoR2yEe0sclpga
{
    unsigned long word[5];
    struct
    {
        long ee0sclpga0 :13;
        unsigned long :3;
        long ee0sclpga1 :13;
        unsigned long :3;
        long ee0sclpga2 :13;
        unsigned long :3;
        long ee0sclpga3 :13;
        unsigned long :3;
        long ee0sclpga4 :13;
        unsigned long :3;
        long ee0sclpga5 :13;
        unsigned long :3;
        long ee0sclpga6 :13;
        unsigned long :3;
        long ee0sclpga7 :13;
        unsigned long :3;
        long ee0sclpga8 :13;
        unsigned long :3;
        long ee0sclpga9 :13;
        unsigned long :3;
    } bit;
};

/*  structure of ee0sclpbd  (2841_C460h)    */
union _IoR2yEe0sclpbd
{
    unsigned long word[3];
    struct
    {
        unsigned long ee0sclpbd1 :8;
        unsigned long ee0sclpbd2 :8;
        unsigned long ee0sclpbd3 :8;
        unsigned long ee0sclpbd4 :8;
        unsigned long ee0sclpbd5 :8;
        unsigned long ee0sclpbd6 :8;
        unsigned long ee0sclpbd7 :8;
        unsigned long ee0sclpbd8 :8;
        unsigned long ee0sclpbd9 :8;
        unsigned long :24;
    } bit;
};

/*  structure of ee0sclmof  (2841_C470h)    */
union _IoR2yEe0sclmof
{
    unsigned long word[3];
    struct
    {
        unsigned long ee0sclmof0 :8;
        unsigned long ee0sclmof1 :8;
        unsigned long ee0sclmof2 :8;
        unsigned long ee0sclmof3 :8;
        unsigned long ee0sclmof4 :8;
        unsigned long ee0sclmof5 :8;
        unsigned long ee0sclmof6 :8;
        unsigned long ee0sclmof7 :8;
        unsigned long ee0sclmof8 :8;
        unsigned long ee0sclmof9 :8;
        unsigned long :16;
    } bit;
};

/*  structure of ee0sclmga  (2841_C480h)    */
union _IoR2yEe0sclmga
{
    unsigned long word[5];
    struct
    {
        long ee0sclmga0 :13;
        unsigned long :3;
        long ee0sclmga1 :13;
        unsigned long :3;
        long ee0sclmga2 :13;
        unsigned long :3;
        long ee0sclmga3 :13;
        unsigned long :3;
        long ee0sclmga4 :13;
        unsigned long :3;
        long ee0sclmga5 :13;
        unsigned long :3;
        long ee0sclmga6 :13;
        unsigned long :3;
        long ee0sclmga7 :13;
        unsigned long :3;
        long ee0sclmga8 :13;
        unsigned long :3;
        long ee0sclmga9 :13;
        unsigned long :3;
    } bit;
};

/*  structure of ee0sclmbd  (2841_C4A0h)    */
union _IoR2yEe0sclmbd
{
    unsigned long word[3];
    struct
    {
        unsigned long ee0sclmbd1 :8;
        unsigned long ee0sclmbd2 :8;
        unsigned long ee0sclmbd3 :8;
        unsigned long ee0sclmbd4 :8;
        unsigned long ee0sclmbd5 :8;
        unsigned long ee0sclmbd6 :8;
        unsigned long ee0sclmbd7 :8;
        unsigned long ee0sclmbd8 :8;
        unsigned long ee0sclmbd9 :8;
        unsigned long :24;
    } bit;
};

/*  structure of ee0tonpof  (2841_C4B0h)    */
union _IoR2yEe0tonpof
{
    unsigned long word[2];
    struct
    {
        unsigned long ee0tonpof0 :7;
        unsigned long :1;
        unsigned long ee0tonpof1 :7;
        unsigned long :1;
        unsigned long ee0tonpof2 :7;
        unsigned long :1;
        unsigned long ee0tonpof3 :7;
        unsigned long :1;
        unsigned long ee0tonpof4 :7;
        unsigned long :25;
    } bit;
};

/*  structure of ee0tonpga  (2841_C4C0h)    */
union _IoR2yEe0tonpga
{
    unsigned long word[3];
    struct
    {
        long ee0tonpga0 :9;
        unsigned long :7;
        long ee0tonpga1 :9;
        unsigned long :7;
        long ee0tonpga2 :9;
        unsigned long :7;
        long ee0tonpga3 :9;
        unsigned long :7;
        long ee0tonpga4 :9;
        unsigned long :23;
    } bit;
};

/*  structure of ee0tonpbd  (2841_C4D0h)    */
union _IoR2yEe0tonpbd
{
    unsigned long word;
    struct
    {
        unsigned long ee0tonpbd1 :7;
        unsigned long :1;
        unsigned long ee0tonpbd2 :7;
        unsigned long :1;
        unsigned long ee0tonpbd3 :7;
        unsigned long :1;
        unsigned long ee0tonpbd4 :7;
        unsigned long :1;
    } bit;
};

/*  structure of ee0tonmof  (2841_C4D8h)    */
union _IoR2yEe0tonmof
{
    unsigned long word[2];
    struct
    {
        unsigned long ee0tonmof0 :7;
        unsigned long :1;
        unsigned long ee0tonmof1 :7;
        unsigned long :1;
        unsigned long ee0tonmof2 :7;
        unsigned long :1;
        unsigned long ee0tonmof3 :7;
        unsigned long :1;
        unsigned long ee0tonmof4 :7;
        unsigned long :25;
    } bit;
};

/*  structure of ee0tonmga  (2841_C4E0h)    */
union _IoR2yEe0tonmga
{
    unsigned long word[3];
    struct
    {
        long ee0tonmga0 :9;
        unsigned long :7;
        long ee0tonmga1 :9;
        unsigned long :7;
        long ee0tonmga2 :9;
        unsigned long :7;
        long ee0tonmga3 :9;
        unsigned long :7;
        long ee0tonmga4 :9;
        unsigned long :23;
    } bit;
};

/*  structure of ee0tonmbd  (2841_C4F0h)    */
union _IoR2yEe0tonmbd
{
    unsigned long word;
    struct
    {
        unsigned long ee0tonmbd1 :7;
        unsigned long :1;
        unsigned long ee0tonmbd2 :7;
        unsigned long :1;
        unsigned long ee0tonmbd3 :7;
        unsigned long :1;
        unsigned long ee0tonmbd4 :7;
        unsigned long :1;
    } bit;
};

/*  structure of ee0clppof  (2841_C4F4h)    */
union _IoR2yEe0clppof
{
    unsigned long word;
    struct
    {
        unsigned long ee0clppof0 :7;
        unsigned long :1;
        unsigned long ee0clppof1 :7;
        unsigned long :1;
        unsigned long ee0clppof2 :7;
        unsigned long :9;
    } bit;
};

/*  structure of ee0clppga  (2841_C4F8h)    */
union _IoR2yEe0clppga
{
    unsigned long word;
    struct
    {
        long ee0clppga0 :8;
        long ee0clppga1 :8;
        long ee0clppga2 :8;
        unsigned long :8;
    } bit;
};

/*  structure of ee0clppbd  (2841_C4FCh)    */
union _IoR2yEe0clppbd
{
    unsigned long word;
    struct
    {
        unsigned long ee0clppbd1 :8;
        unsigned long ee0clppbd2 :8;
        unsigned long :16;
    } bit;
};

KConstType jdsr2y_f2e3_get_type(void);
Jdsr2yF2e3* jdsr2y_f2e3_new(void);

#endif/*__JDSR2Y_F2E3_H__*/

