/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition Timestamp Generator I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_TIMESTAMP_H__
#define __K_TIMESTAMP_H__


#include <klib.h>


#define K_TYPE_TIMESTAMP	        (k_timestamp_get_type())
#define K_TIMESTAMP(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KTimestamp))
#define K_IS_TIMESTAMP(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_TIMESTAMP))

typedef struct _KTimestamp          KTimestamp;
typedef struct _KTimestampPrivate   KTimestampPrivate;

typedef struct _IoTimestamp         IoTimestamp;

typedef union _IoTimestampCntcr     IoTimestampCntcr;
typedef union _IoTimestampCntsr     IoTimestampCntsr;
typedef union _IoTimestampPidr4     IoTimestampPidr4;
typedef union _IoTimestampPidr0     IoTimestampPidr0;
typedef union _IoTimestampPidr1     IoTimestampPidr1;
typedef union _IoTimestampPidr2     IoTimestampPidr2;
typedef union _IoTimestampPidr3     IoTimestampPidr3;
typedef union _IoTimestampCidr0     IoTimestampCidr0;
typedef union _IoTimestampCidr1     IoTimestampCidr1;
typedef union _IoTimestampCidr2     IoTimestampCidr2;
typedef union _IoTimestampCidr3     IoTimestampCidr3;


struct _KTimestamp
{
    KObject parent;
};


/* structure of cntcr                   (1D01_0000h) */
union _IoTimestampCntcr
{
    kulong word;
    struct
    {
        kulong en :1;
        kulong hdbg :1;
        kulong :30;
    } bit;
};

/* structure of cntsr                   (1D01_0004h) */
union _IoTimestampCntsr
{
    kulong word;
    struct
    {
        kulong :1;
        kulong dbgh :1;
        kulong :30;
    } bit;
};

/* structure of pidr4                   (1D01_0FD0h) */
union _IoTimestampPidr4
{
    kulong word;
    struct
    {
        kulong des2 :4;
        kulong size :4;
        kulong :24;
    } bit;
};

/* structure of pidr0                   (1D01_0FE0h) */
union _IoTimestampPidr0
{
    kulong word;
    struct
    {
        kulong part0 :8;
        kulong :24;
    } bit;
};

/* structure of pidr1                   (1D01_0FE4h) */
union _IoTimestampPidr1
{
    kulong word;
    struct
    {
        kulong part1 :4;
        kulong des0 :4;
        kulong :24;
    } bit;
};

/* structure of pidr2                   (1D01_0FE8h) */
union _IoTimestampPidr2
{
    kulong word;
    struct
    {
        kulong des1 :3;
        kulong jedec :1;
        kulong revision :4;
        kulong :24;
    } bit;
};

/* structure of pidr3                   (1D01_0FECh) */
union _IoTimestampPidr3
{
    kulong word;
    struct
    {
        kulong cmod :4;
        kulong revand :4;
        kulong :24;
    } bit;
};

/* structure of cidr0                   (1D01_0FF0h) */
union _IoTimestampCidr0
{
    kulong word;
    struct
    {
        kulong prmbl0 :8;
        kulong :24;
    } bit;
};

/* structure of cidr1                   (1D01_0FF4h) */
union _IoTimestampCidr1
{
    kulong word;
    struct
    {
        kulong prmbl1 :4;
        kulong class :4;
        kulong :24;
    } bit;
};

/* structure of cidr2                   (1D01_0FF8h) */
union _IoTimestampCidr2
{
    kulong word;
    struct
    {
        kulong prmbl2 :8;
        kulong :24;
    } bit;
};

/* structure of cidr3                   (1D01_0FFCh) */
union _IoTimestampCidr3
{
    kulong word;
    struct
    {
        kulong prmbl3 :8;
        kulong :24;
    } bit;
};


/* Timestamp generator register                     */
struct _IoTimestamp
{
    IoTimestampCntcr cntcr;                          // 1D01_(0000 - 0003) Counter Control Register
    IoTimestampCntsr cntsr;                          // 1D01_(0004 - 0007) Counter Status Register
    kulong cntcvl;                         // 1D01_(0008 - 000B) Current Counter Value Lower register
    kulong cntcvu;                         // 1D01_(000C - 000F) Current Counter Value Upper register
    kuchar dmy0010001f[0x0020 - 0x0010]; // 1D01_(0010 - 001F) Reserved
    kulong cntfid0;                        // 1D01_(0020 - 0023) Base Frequency ID register
    kuchar dmy00240fcf[0x0FD0 - 0x0024]; // 1D01_(0024 - 0FCF) Reserved
    IoTimestampPidr4 pidr4;                          // 1D01_(0FD0 - 0FD3) Peripheral ID4 Register
    kuchar dmy0fd40fdf[0x0FE0 - 0x0FD4]; // 1D01_(0FD4 - 0FDF) Reserved
    IoTimestampPidr0 pidr0;                          // 1D01_(0FE0 - 0FE3) Peripheral ID0 Register
    IoTimestampPidr1 pidr1;                          // 1D01_(0FE4 - 0FE7) Peripheral ID1 Register
    IoTimestampPidr2 pidr2;                          // 1D01_(0FE8 - 0FEB) Peripheral ID2 Register
    IoTimestampPidr3 pidr3;                          // 1D01_(0FEC - 0FEF) Peripheral ID3 Register
    IoTimestampCidr0 cidr0;                          // 1D01_(0FF0 - 0FF3) Component ID0 Register
    IoTimestampCidr1 cidr1;                          // 1D01_(0FF4 - 0FF7) Component ID1 Register
    IoTimestampCidr2 cidr2;                          // 1D01_(0FF8 - 0FFB) Component ID2 Register
    IoTimestampCidr3 cidr3;                          // 1D01_(0FFC - 0FFF) Component ID3 Register
};


extern volatile IoTimestamp ioTimestamp;


KConstType  k_timestamp_get_type(void);
KTimestamp* k_timestamp_new(void);


#endif/*__K_TIMESTAMP_H__*/
