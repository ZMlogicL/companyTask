/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :郑蛘钊
 *@brief             :Definition IPCU (Inter-Processor Communications Unit) I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_IPCU_H__
#define __K_IPCU_H__

#include <klib.h>

#define K_TYPE_IPCU	(k_ipcu_get_type())
#define K_IPCU(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KIpcu))
#define K_IS_IPCU(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_IPCU))

typedef struct _KIpcu KIpcu;
typedef struct _KIpcuPrivate KIpcuPrivate;

typedef struct _IoIpcuMailbox IoIpcuMailbox;
typedef struct _IoIpcu IoIpcu;

typedef union _IoIpcuIsr IoIpcuIsr;
typedef union _IoIpcuMbAdr IoIpcuMbAdr;
typedef union _IoIpcuSrc IoIpcuSrc;
typedef union _IoIpcuMode IoIpcuMode;
typedef union _IoIpcuSend IoIpcuSend;
typedef union _IoIpcuDstSet IoIpcuDstSet;
typedef union _IoIpcuDstClr IoIpcuDstClr;
typedef union _IoIpcuDstStat IoIpcuDstStat;
typedef union _IoIpcuMaskSet IoIpcuMaskSet;
typedef union _IoIpcuMaskClr IoIpcuMaskClr;
typedef union _IoIpcuMaskStat IoIpcuMaskStat;
typedef union _IoIpcuAckSet IoIpcuAckSet;
typedef union _IoIpcuAckClr IoIpcuAckClr;
typedef union _IoIpcuAckStat IoIpcuAckStat;
typedef union _IoIpcuAckSrc IoIpcuAckSrc;
typedef union _IoIpcuMbStat IoIpcuMbStat;

extern volatile IoIpcu ioIpcu0; /* Base(IPCU0) : 0x1C25_1000 */
extern volatile IoIpcu ioIpcu1; /* Base(IPCU1) : 0x1C25_2000 */

struct _KIpcu
{
    KObject parent;
};

/* structure of isr             (Base_0000h) */
union _IoIpcuIsr
{
    unsigned long word;
    struct
    {
        unsigned long mb0 :1;
        unsigned long mb1 :1;
        unsigned long mb2 :1;
        unsigned long mb3 :1;
        unsigned long mb4 :1;
        unsigned long mb5 :1;
        unsigned long mb6 :1;
        unsigned long mb7 :1;
        unsigned long :8;
        unsigned long :8;
        unsigned long :8;
    } bit;
};

/* structure of mbadr           (Base_0080h) */
union _IoIpcuMbAdr
{
    unsigned long word;
    struct
    {
        unsigned long mba :12;
        unsigned long req :1;
        unsigned long ack :1;
        unsigned long :2;
        unsigned long :16;
    } bit;
};

/* structure of src             (Base_0100h) */
union _IoIpcuSrc
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of mode            (Base_0104h) */
union _IoIpcuMode
{
    unsigned long word;
    struct
    {
        unsigned long mode :3;
        unsigned long :5;
        unsigned long :24;
    } bit;
};

/* structure of send            (Base_0108h) */
union _IoIpcuSend
{
    unsigned long word;
    struct
    {
        unsigned long send :1;
        unsigned long :7;
        unsigned long :24;
    } bit;
};

/* structure of dstset          (Base_0110h) */
union _IoIpcuDstSet
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of dstclr          (Base_0114h) */
union _IoIpcuDstClr
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of dststat         (Base_0118h) */
union _IoIpcuDstStat
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of maskset         (Base_0120h) */
union _IoIpcuMaskSet
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of maskclr         (Base_0124h) */
union _IoIpcuMaskClr
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of maskstat        (Base_0128h) */
union _IoIpcuMaskStat
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of ackset          (Base_0130h) */
union _IoIpcuAckSet
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of ackclr          (Base_0134h) */
union _IoIpcuAckClr
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of ackstat         (Base_0138h) */
union _IoIpcuAckStat
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of acksrc          (Base_013Ch) */
union _IoIpcuAckSrc
{
    unsigned long word;
    struct
    {
        unsigned long unit00 :1;
        unsigned long unit01 :1;
        unsigned long unit02 :1;
        unsigned long unit03 :1;
        unsigned long unit04 :1;
        unsigned long unit05 :1;
        unsigned long unit06 :1;
        unsigned long unit07 :1;
        unsigned long unit08 :1;
        unsigned long unit09 :1;
        unsigned long unit10 :1;
        unsigned long unit11 :1;
        unsigned long unit12 :1;
        unsigned long unit13 :1;
        unsigned long unit14 :1;
        unsigned long unit15 :1;
        unsigned long :16;
    } bit;
};

/* structure of mbstat          (Base_0900h) */
union _IoIpcuMbStat
{
    unsigned long word;
    struct
    {
        unsigned long mb0 :1;
        unsigned long mb1 :1;
        unsigned long mb2 :1;
        unsigned long mb3 :1;
        unsigned long mb4 :1;
        unsigned long mb5 :1;
        unsigned long mb6 :1;
        unsigned long mb7 :1;
        unsigned long :24;
    } bit;
};

struct _IoIpcuMailbox
{
    IoIpcuSrc src; /* Base_(0100 - 0103h) RW Source Register               */
    IoIpcuMode mode; /* Base_(0104 - 0107h) RW Mode Register                 */
    IoIpcuSend send; /* Base_(0108 - 010Bh) RW Send Register                 */
    unsigned char dmy010c010f[0x0110 - 0x010C]; /* Base_(010C - 010Fh) Reserved                         */
    IoIpcuDstSet dstset; /* Base_(0110 - 0113h) WO Destination Set Register      */
    IoIpcuDstClr dstclr; /* Base_(0114 - 0117h) WO Destination Clear Register    */
    IoIpcuDstStat dststat; /* Base_(0118 - 011Bh) RO Destination Status Register   */
    unsigned char dmy011c011f[0x0120 - 0x011C]; /* Base_(011C - 011Fh) Reserved                         */
    IoIpcuMaskSet maskset; /* Base_(0120 - 0123h) WO Mask Set Register             */
    IoIpcuMaskClr maskclr; /* Base_(0124 - 0127h) WO Mask Clear Register           */
    IoIpcuMaskStat maskstat; /* Base_(0128 - 012Bh) RO Mask Status Register          */
    unsigned char dmy012c0130[0x0130 - 0x012C]; /* Base_(012C - 012Fh) Reserved                         */
    IoIpcuAckSet ackset; /* Base_(0130 - 0133h) WO Acknowledge Set Register      */
    IoIpcuAckClr ackclr; /* Base_(0134 - 0137h) WO Acknowledge Clear Register    */
    IoIpcuAckStat ackstat; /* Base_(0138 - 013Bh) RO Acknowledge Status Register   */
    IoIpcuAckSrc acksrc; /* Base_(013C - 013Fh) RO Acknowledge Source Register   */
    unsigned long data[9]; /* Base_(0140 - 0163h) RW Data Register                 */
    unsigned char dmy0164017f[0x0180 - 0x0164];
};

/*  IPCU register                           */
struct _IoIpcu
{
    IoIpcuIsr isr[16]; /* Base_(0000 - 003Fh) RO Interrupt Status Register     */
    unsigned char dmy0040007f[0x0080 - 0x0040]; /* Base_(0040 - 007Fh) Reserved                         */
    IoIpcuMbAdr mbadr[16]; /* Base_(0080 - 00BFh) RO Mailbox Address Register      */
    unsigned char dmy00c000ff[0x0100 - 0x00C0]; /* Base_(00C0 - 00FFh) Reserved                         */
    IoIpcuMailbox mailbox[8]; /* Base_(0100 - 04FFh) Mailbox Register                 */
    unsigned char dmy050008ff[0x0900 - 0x0500]; /* Base_(0500 - 08FFh) Reserved                         */
    IoIpcuMbStat mbstat; /* Base_(0900 - 0903h) RO Mailbox Status Register       */
};

KConstType k_ipcu_get_type(void);
KIpcu* k_ipcu_new(void);

#endif/*__K_IPCU_H__*/

