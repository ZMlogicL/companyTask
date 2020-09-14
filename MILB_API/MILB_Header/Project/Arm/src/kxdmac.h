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


#define K_TYPE_XDMAC	        (k_xdmac_get_type())
#define K_XDMAC(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KXdmac))
#define K_IS_XDMAC(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_XDMAC))


typedef struct _KXdmac          KXdmac;
typedef struct _KXdmacPrivate   KXdmacPrivate;

typedef struct _IoXdmacElement  IoXdmacElement;
typedef struct _IoXdmac         IoXdmac;

typedef union _IoXdmacXdacs     IoXdmacXdacs;
typedef union _IoXdmacXdsac     IoXdmacXdsac;
typedef union _IoXdmacXddac     IoXdmacXddac;
typedef union _IoXdmacXddes     IoXdmacXddes;
typedef union _IoXdmacXddpc     IoXdmacXddpc;
typedef union _IoXdmacXddsd     IoXdmacXddsd;


struct _KXdmac
{
    KObject parent;
};


/* structure of xdacs                   (Base = 1914_0000h, SNAP Base = 1C25_0000h) */
union _IoXdmacXdacs
{
    kulong word;
    struct
    {
        kulong :16;
        kulong xs :1;
        kulong :3;
        kulong lp :1;
        kulong :3;
        kulong cp :1;
        kulong :3;
        kulong xe :1;
        kulong :3;
    } bit;
};

/* structure of xdsac                   (Base + 0x1Ch,4Ch,7Ch,ACh,DCh,10Ch,13Ch,16Ch) */
union _IoXdmacXdsac
{
    kulong word;
    struct
    {
        kulong srl :1;
        kulong :1;
        kulong saf :1;
        kulong :5;
        kulong sbl :4;
        kulong :4;
        kulong sbs :2;
        kulong :14;
    } bit;
};

/* structure of xddac                   (Base + 0x20h,50h,80h,B0h,E0h,110h,140h,170h) */
union _IoXdmacXddac
{
    kulong word;
    struct
    {
        kulong drl :1;
        kulong :1;
        kulong daf :1;
        kulong :5;
        kulong dbl :4;
        kulong :4;
        kulong dbs :2;
        kulong :14;
    } bit;
};

/* structure of xddes                   (Base + 0x28h,58h,88h,B8h,E8h,118h,148h,178h) */
union _IoXdmacXddes
{
    kulong word;
    struct
    {
        kulong ti :1;
        kulong ei :1;
        kulong :2;
        kulong at :1;
        kulong :3;
        kulong br :1;
        kulong :3;
        kulong bt :1;
        kulong :2;
        kulong sa :1;
        kulong :4;
        kulong tf :4;
        kulong se :1;
        kulong :3;
        kulong ce :1;
        kulong :3;
    } bit;
};

/* structure of xddpc                   (Base + 0x2Ch,5Ch,8Ch,BCh,ECh,11Ch,14Ch,17Ch) */
union _IoXdmacXddpc
{
    kulong word;
    struct
    {
        kulong dp :3;
        kulong :1;
        kulong sp :3;
        kulong :25;
    } bit;
};

/* structure of xddsd                   (Base + 0x30h,60h,90h,C0h,F0h,120h,150h,180h) */
union _IoXdmacXddsd
{
    kulong word;
    struct
    {
        kulong is :4;
        kulong :12;
        kulong ts :1;
        kulong :15;
    } bit;
};


/* structure of element           (Base + 0x10h,40h,70h,A0h,D0h,100h,130h,160h) */
struct _IoXdmacElement
{
    kulong xdtbc;                  // Base_(0010 - 0013) Transfer Byte Count Register
    kulong xdssa;                  // Base_(0014 - 0017) Source Start Address Register
    kulong xddsa;                  // Base_(0018 - 001B) Destination Start Address Register
    IoXdmacXdsac xdsac;            // Base_(001C - 001F) Source Access Configuration Register
    IoXdmacXddac xddac;            // Base_(0020 - 0023) Destination Access Configuration Register
    kulong xddcc;                  // Base_(0024 - 0027) Descriptor Chain Configuration Register
    IoXdmacXddes xddes;            // Base_(0028 - 002B) DMA Enable Setting Register
    IoXdmacXddpc xddpc;            // Base_(002C - 002F) DMA Protection Control Register
    IoXdmacXddsd xddsd;            // Base_(0030 - 0033) DMA Status Display Register
    kuchar dmy343f[0x40 - 0x34];   // Base_(0034 - 003F) Reserved
};

/* XDMAC register                           */
struct _IoXdmac
{
    IoXdmacXdacs xdacs;          // Base_(0000 - 0003) All Channel Setting Register
    kuchar dmy040f[0x10 - 0x04]; // Base_(0004 - 000F) Reserved
    IoXdmacElement ch[8];
};


extern volatile IoXdmac ioXdmac;
extern volatile IoXdmac ioXdmacs;


KConstType  k_xdmac_get_type(void);
KXdmac*     k_xdmac_new(void);


#endif/*__K_XDMAC_H__*/
