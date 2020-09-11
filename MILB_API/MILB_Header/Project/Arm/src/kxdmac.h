/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition XDMAC Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_XDMAC_H__
#define __K_XDMAC_H__

#include <klib.h>

#define K_TYPE_XDMAC	(k_xdmac_get_type())
#define K_XDMAC(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KXdmac))
#define K_IS_XDMAC(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_XDMAC))

typedef struct _KXdmac KXdmac;
typedef struct _KXdmacPrivate KXdmacPrivate;

typedef struct _IoXdmacElement IoXdmacElement;
typedef struct _IoXdmac IoXdmac;

typedef union _IoXdmacXdacs IoXdmacXdacs;
typedef union _IoXdmacXdsac IoXdmacXdsac;
typedef union _IoXdmacXddac IoXdmacXddac;
typedef union _IoXdmacXddes IoXdmacXddes;
typedef union _IoXdmacXddpc IoXdmacXddpc;
typedef union _IoXdmacXddsd IoXdmacXddsd;

struct _KXdmac
{
    KObject parent;
};

/* structure of xdacs                   (Base = 1914_0000h, SNAP Base = 1C25_0000h) */
union _IoXdmacXdacs
{
    unsigned long word;
    struct
    {
        unsigned long :16;
        unsigned long xs :1;
        unsigned long :3;
        unsigned long lp :1;
        unsigned long :3;
        unsigned long cp :1;
        unsigned long :3;
        unsigned long xe :1;
        unsigned long :3;
    } bit;
};

/* structure of xdsac                   (Base + 0x1Ch,4Ch,7Ch,ACh,DCh,10Ch,13Ch,16Ch) */
union _IoXdmacXdsac
{
    unsigned long word;
    struct
    {
        unsigned long srl :1;
        unsigned long :1;
        unsigned long saf :1;
        unsigned long :5;
        unsigned long sbl :4;
        unsigned long :4;
        unsigned long sbs :2;
        unsigned long :14;
    } bit;
};

/* structure of xddac                   (Base + 0x20h,50h,80h,B0h,E0h,110h,140h,170h) */
union _IoXdmacXddac
{
    unsigned long word;
    struct
    {
        unsigned long drl :1;
        unsigned long :1;
        unsigned long daf :1;
        unsigned long :5;
        unsigned long dbl :4;
        unsigned long :4;
        unsigned long dbs :2;
        unsigned long :14;
    } bit;
};

/* structure of xddes                   (Base + 0x28h,58h,88h,B8h,E8h,118h,148h,178h) */
union _IoXdmacXddes
{
    unsigned long word;
    struct
    {
        unsigned long ti :1;
        unsigned long ei :1;
        unsigned long :2;
        unsigned long at :1;
        unsigned long :3;
        unsigned long br :1;
        unsigned long :3;
        unsigned long bt :1;
        unsigned long :2;
        unsigned long sa :1;
        unsigned long :4;
        unsigned long tf :4;
        unsigned long se :1;
        unsigned long :3;
        unsigned long ce :1;
        unsigned long :3;
    } bit;
};

/* structure of xddpc                   (Base + 0x2Ch,5Ch,8Ch,BCh,ECh,11Ch,14Ch,17Ch) */
union _IoXdmacXddpc
{
    unsigned long word;
    struct
    {
        unsigned long dp :3;
        unsigned long :1;
        unsigned long sp :3;
        unsigned long :25;
    } bit;
};

/* structure of xddsd                   (Base + 0x30h,60h,90h,C0h,F0h,120h,150h,180h) */
union _IoXdmacXddsd
{
    unsigned long word;
    struct
    {
        unsigned long is :4;
        unsigned long :12;
        unsigned long ts :1;
        unsigned long :15;
    } bit;
};

/* structure of element                 (Base + 0x10h,40h,70h,A0h,D0h,100h,130h,160h) */
struct _IoXdmacElement
{
    unsigned long xdtbc;                  // Base_(0010 - 0013) Transfer Byte Count Register
    unsigned long xdssa;                  // Base_(0014 - 0017) Source Start Address Register
    unsigned long xddsa;                  // Base_(0018 - 001B) Destination Start Address Register
    IoXdmacXdsac xdsac;                  // Base_(001C - 001F) Source Access Configuration Register
    IoXdmacXddac xddac;                  // Base_(0020 - 0023) Destination Access Configuration Register
    unsigned long xddcc;                  // Base_(0024 - 0027) Descriptor Chain Configuration Register
    IoXdmacXddes xddes;                  // Base_(0028 - 002B) DMA Enable Setting Register
    IoXdmacXddpc xddpc;                  // Base_(002C - 002F) DMA Protection Control Register
    IoXdmacXddsd xddsd;                  // Base_(0030 - 0033) DMA Status Display Register
    unsigned char dmy343f[0x40 - 0x34]; // Base_(0034 - 003F) Reserved
};

/* XDMAC register                           */
struct _IoXdmac
{
    IoXdmacXdacs xdacs;                  // Base_(0000 - 0003) All Channel Setting Register
    unsigned char dmy040f[0x10 - 0x04]; // Base_(0004 - 000F) Reserved
    IoXdmacElement ch[8];
};

extern volatile IoXdmac ioXdmac;
extern volatile IoXdmac ioXdmacs;

KConstType k_xdmac_get_type(void);
KXdmac* k_xdmac_new(void);

#endif/*__K_XDMAC_H__*/

