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

#define K_TYPE_TIMESTAMP	(k_timestamp_get_type())
#define K_TIMESTAMP(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KTimestamp))
#define K_IS_TIMESTAMP(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_TIMESTAMP))

typedef struct _KTimestamp KTimestamp;
typedef struct _KTimestampPrivate KTimestampPrivate;

typedef struct _IoTimestamp IoTimestamp;

typedef union _IoTimestampCntcr IoTimestampCntcr;
typedef union _IoTimestampCntsr IoTimestampCntsr;
typedef union _IoTimestampPidr4 IoTimestampPidr4;
typedef union _IoTimestampPidr0 IoTimestampPidr0;
typedef union _IoTimestampPidr1 IoTimestampPidr1;
typedef union _IoTimestampPidr2 IoTimestampPidr2;
typedef union _IoTimestampPidr3 IoTimestampPidr3;
typedef union _IoTimestampCidr0 IoTimestampCidr0;
typedef union _IoTimestampCidr1 IoTimestampCidr1;
typedef union _IoTimestampCidr2 IoTimestampCidr2;
typedef union _IoTimestampCidr3 IoTimestampCidr3;

struct _KTimestamp
{
    KObject parent;
};

/* structure of cntcr                   (1D01_0000h) */
union _IoTimestampCntcr
{
    unsigned long word;
    struct
    {
        unsigned long en :1;
        unsigned long hdbg :1;
        unsigned long :30;
    } bit;
};

/* structure of cntsr                   (1D01_0004h) */
union _IoTimestampCntsr
{
    unsigned long word;
    struct
    {
        unsigned long :1;
        unsigned long dbgh :1;
        unsigned long :30;
    } bit;
};

/* structure of pidr4                   (1D01_0FD0h) */
union _IoTimestampPidr4
{
    unsigned long word;
    struct
    {
        unsigned long des2 :4;
        unsigned long size :4;
        unsigned long :24;
    } bit;
};

/* structure of pidr0                   (1D01_0FE0h) */
union _IoTimestampPidr0
{
    unsigned long word;
    struct
    {
        unsigned long part0 :8;
        unsigned long :24;
    } bit;
};

/* structure of pidr1                   (1D01_0FE4h) */
union _IoTimestampPidr1
{
    unsigned long word;
    struct
    {
        unsigned long part1 :4;
        unsigned long des0 :4;
        unsigned long :24;
    } bit;
};

/* structure of pidr2                   (1D01_0FE8h) */
union _IoTimestampPidr2
{
    unsigned long word;
    struct
    {
        unsigned long des1 :3;
        unsigned long jedec :1;
        unsigned long revision :4;
        unsigned long :24;
    } bit;
};

/* structure of pidr3                   (1D01_0FECh) */
union _IoTimestampPidr3
{
    unsigned long word;
    struct
    {
        unsigned long cmod :4;
        unsigned long revand :4;
        unsigned long :24;
    } bit;
};

/* structure of cidr0                   (1D01_0FF0h) */
union _IoTimestampCidr0
{
    unsigned long word;
    struct
    {
        unsigned long prmbl0 :8;
        unsigned long :24;
    } bit;
};

/* structure of cidr1                   (1D01_0FF4h) */
union _IoTimestampCidr1
{
    unsigned long word;
    struct
    {
        unsigned long prmbl1 :4;
        unsigned long class :4;
        unsigned long :24;
    } bit;
};

/* structure of cidr2                   (1D01_0FF8h) */
union _IoTimestampCidr2
{
    unsigned long word;
    struct
    {
        unsigned long prmbl2 :8;
        unsigned long :24;
    } bit;
};

/* structure of cidr3                   (1D01_0FFCh) */
union _IoTimestampCidr3
{
    unsigned long word;
    struct
    {
        unsigned long prmbl3 :8;
        unsigned long :24;
    } bit;
};

/* Timestamp generator register                     */
struct _IoTimestamp
{
    IoTimestampCntcr cntcr;                          // 1D01_(0000 - 0003) Counter Control Register
    IoTimestampCntsr cntsr;                          // 1D01_(0004 - 0007) Counter Status Register
    unsigned long cntcvl;                         // 1D01_(0008 - 000B) Current Counter Value Lower register
    unsigned long cntcvu;                         // 1D01_(000C - 000F) Current Counter Value Upper register
    unsigned char dmy0010001f[0x0020 - 0x0010]; // 1D01_(0010 - 001F) Reserved
    unsigned long cntfid0;                        // 1D01_(0020 - 0023) Base Frequency ID register
    unsigned char dmy00240fcf[0x0FD0 - 0x0024]; // 1D01_(0024 - 0FCF) Reserved
    IoTimestampPidr4 pidr4;                          // 1D01_(0FD0 - 0FD3) Peripheral ID4 Register
    unsigned char dmy0fd40fdf[0x0FE0 - 0x0FD4]; // 1D01_(0FD4 - 0FDF) Reserved
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

KConstType k_timestamp_get_type(void);
KTimestamp* k_timestamp_new(void);

#endif/*__K_TIMESTAMP_H__*/

