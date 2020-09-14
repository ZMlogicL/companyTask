/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition Network InterConnect I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_NIC_H__
#define __K_NIC_H__


#include <klib.h>


#define K_TYPE_NIC	        (k_nic_get_type())
#define K_NIC(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KNic))
#define K_IS_NIC(obj)	    (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_NIC))

typedef struct _KNic        KNic;
typedef struct _KNicPrivate KNicPrivate;

typedef struct _IoAddrctrl  IoAddrctrl;
typedef struct _IoAsib      IoAsib;

typedef union _NicSecurity1 NicSecurity1;
typedef union _NicTidemark  NicTidemark;
typedef union _NicRq        NicRq;
typedef union _NicWq        NicWq;
typedef union _NicFm        NicFm;


struct _KNic
{
    KObject parent;
};


/* structure of security1               (1D10_000Ch) */
union _NicSecurity1
{
    kulong word;
    struct
    {
        kulong security1 :16;
        kulong :16;
    } bit;
};

/* structure of wr_tidemark             (1D14_2040h, 3040h, 4040h, 5040h, 6040h, 7040h, 8040h) */
union _NicTidemark
{
    kulong word;
    struct
    {
        kulong wt :4;
        kulong :28;
    } bit;
};

/* structure of read_qos                (1D14_2100h, 3100h, 4100h, 5100h, 6100h, 7100h, 8100h) */
union _NicRq
{
    kulong word;
    struct
    {
        kulong rq :4;
        kulong :28;
    } bit;
};

/* structure of write_qos               (1D14_2104h, 3104h, 4104h, 5104h, 6104h, 7104h, 8104h) */
union _NicWq
{
    kulong word;
    struct
    {
        kulong wq :4;
        kulong :28;
    } bit;
};

/* structure of fn_mod                  (1D14_2108h, 3108h, 4108h, 5108h, 6108h, 7108h, 8108h) */
union _NicFm
{
    kulong word;
    struct
    {
        kulong fm :2;
        kulong :30;
    } bit;
};


/* Address region control register                  */
struct _IoAddrctrl
{
    kuchar dmy0000000b[0x000C - 0x0000]; // 1D10_(0000 - 000B) Reserved
    NicSecurity1 security1;                      // 1D10_(000C - 000F) Slave 1 security setting Register
    kuchar dmy00100fff[0x1000 - 0x0010]; // 1D10_(0010 - 0FFF) Reserved
};

/* Slave Interface register                         */
struct _IoAsib
{
    kuchar dmy2000203f[0x2040 - 0x2000]; // 1D14_(2000 - 203F) Reserved
    NicTidemark wrTidemark;                    // 1D14_(2040 - 2043) Tidemark Register
    kuchar dmy204420ff[0x2100 - 0x2044]; // 1D14_(2044 - 20FF) Reserved
    NicRq readQos;                       // 1D14_(2100 - 2103) Read channel QoS Register
    NicWq writeQos;                      // 1D14_(2104 - 2107) Write channel QoS Register
    NicFm fnMod;                         // 1D14_(2108 - 210B) Functionality Modification Register
    kuchar dmy210c2fff[0x3000 - 0x210C]; // 1D14_(210C - 2FFF) Reserved
};


extern volatile IoAddrctrl ioNicAddrctrl;
extern volatile IoAsib ioNicAsib[7];


KConstType  k_nic_get_type(void);
KNic*       k_nic_new(void);


#endif/*__K_NIC_H__*/
