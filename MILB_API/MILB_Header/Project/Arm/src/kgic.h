/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :郑蛘钊
 *@brief             :kgic
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、Definition GIC (Generic Interrupt Controller) I/O register
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_GIC_H__
#define __K_GIC_H__


#include <klib.h>


#define K_TYPE_GIC	            (k_gic_get_type())
#define K_GIC(obj)	            (K_TYPE_CHECK_INSTANCE_CAST((obj), KGic))
#define K_IS_GIC(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_GIC))

typedef struct _KGic            KGic;
typedef struct _KGicPrivate     KGicPrivate;

typedef struct _IoGicDist       IoGicDist;
typedef struct _IoGicCpu        IoGicCpu;

typedef union _IoGicDistCtlr    IoGicDistCtlr;
typedef union _IoGicDistTyper   IoGicDistTyper;
typedef union _IoGicDistIidr    IoGicDistIidr;
typedef union _IoGicDistPpisr   IoGicDistPpisr;
typedef union _IoGicDistSgir    IoGicDistSgir;
typedef union _IoGicCpuCtlr     IoGicCpuCtlr;
typedef union _IoGicCpuPmr      IoGicCpuPmr;
typedef union _IoGicCpuBpr      IoGicCpuBpr;
typedef union _IoGicCpuIar      IoGicCpuIar;
typedef union _IoGicCpuEoir     IoGicCpuEoir;
typedef union _IoGicCpuRpr      IoGicCpuRpr;
typedef union _IoGicCpuHpir     IoGicCpuHpir;
typedef union _IoGicCpuAbpr     IoGicCpuAbpr;
typedef union _IoGicCpuAiar     IoGicCpuAiar;
typedef union _IoGicCpuAeoir    IoGicCpuAeoir;
typedef union _IoGicCpuAhppir   IoGicCpuAhppir;
typedef union _IoGicCpuIidr     IoGicCpuIidr;
typedef union _IoGicCpuDir      IoGicCpuDir;


extern volatile IoGicDist ioGicDist;
extern volatile IoGicCpu ioGicCpu;


struct _KGic
{
    KObject parent;
};


/* structure of gicdCtlr       (1D00_1000h) */
union _IoGicDistCtlr
{
    kulong word;
    struct
    {
        kulong ENABLEGR0 :1;
        kulong ENABLEGR1 :1;
        kulong :30;
    } bit;
};

/* structure of gicdTyper      (1D00_1004h) */
union _IoGicDistTyper
{
    kulong word;
    struct
    {
        kulong itlinesnumber :5;
        kulong cpunumber :3;
        kulong :2;
        kulong securityExtn :1;
        kulong lspi :5;
        kulong :16;
    } bit;
};

/* structure of gicdIidr       (1D00_1008h) */
union _IoGicDistIidr
{
    kulong word;
    struct
    {
        kulong implementer :12;
        kulong revision :4;
        kulong variant :4;
        kulong :4;
        kulong productid :8;
    } bit;
};

/* structure of gicdPpisr      (1D00_1D00h) */
union _IoGicDistPpisr
{
    kulong word;
    struct
    {
        kulong :9;
        kulong ppi6Status :1;
        kulong ppi5Status :1;
        kulong ppi4Status :1;
        kulong ppi0Status :1;
        kulong ppi1Status :1;
        kulong ppi2Status :1;
        kulong ppi3Status :1;
        kulong :16;
    } bit;
};

/* structure of gicdSgir       (1D00_1F00h) */
union _IoGicDistSgir
{
    kulong word;
    struct
    {
        kulong sgiintid :4;
        kulong :11;
        kulong nsatt :1;
        kulong cputargetlist :8;
        kulong targetlistfilter :2;
        kulong :6;
    } bit;
};

/* structure of giccCtlr       (1D00_2000h) */
union _IoGicCpuCtlr
{
    kulong word;
    struct
    {
        kulong enablegrp0 :1;
        kulong enablegrp1 :1;
        kulong ackctl :1;
        kulong fiqen :1;
        kulong cbpr :1;
        kulong fiqbypdisgrp0 :1;
        kulong irqbypdisgrp0 :1;
        kulong fiqbypdisgrp1 :1;
        kulong irqbypdisgrp1 :1;
        kulong eoimodes :1;
        kulong eoimodens :1;
        kulong :21;
    } bit;
};

/* structure of giccPmr        (1D00_2004h) */
union _IoGicCpuPmr
{
    kulong word;
    struct
    {
        kulong priority :8;
        kulong :24;
    } bit;
};

/* structure of giccBpr        (1D00_2008h) */
union _IoGicCpuBpr
{
    kulong word;
    struct
    {
        kulong binarypoint :3;
        kulong :29;
    } bit;
};

/* structure of giccIar        (1D00_200Ch) */
union _IoGicCpuIar
{
    kulong word;
    struct
    {
        kulong ackintid :10;
        kulong cpuid :3;
        kulong :19;
    } bit;
};

/* structure of giccEoir       (1D00_2010h) */
union _IoGicCpuEoir
{
    kulong word;
    struct
    {
        kulong eoiintid :10;
        kulong cpuid :3;
        kulong :19;
    } bit;
};

/* structure of giccRpr        (1D00_2014h) */
union _IoGicCpuRpr
{
    kulong word;
    struct
    {
        kulong priority :8;
        kulong :24;
    } bit;
};

/* structure of giccHppir      (1D00_2018h) */
union _IoGicCpuHpir
{
    kulong word;
    struct
    {
        kulong pendintid :10;
        kulong cpuid :3;
        kulong :19;
    } bit;
};

/* structure of giccAbpr       (1D00_201Ch) */
union _IoGicCpuAbpr
{
    kulong word;
    struct
    {
        kulong binarypoint :3;
        kulong :29;
    } bit;
};

/* structure of giccAiar       (1D00_2020h) */
union _IoGicCpuAiar
{
    kulong word;
    struct
    {
        kulong ackintid :10;
        kulong cpuid :3;
        kulong :19;
    } bit;
};

/* structure of giccAeoir      (1D00_2024h) */
union _IoGicCpuAeoir
{
    kulong word;
    struct
    {
        kulong eoiintid :10;
        kulong cpuid :3;
        kulong :19;
    } bit;
};

/* structure of giccAhppir     (1D00_2028h) */
union _IoGicCpuAhppir
{
    kulong word;
    struct
    {
        kulong pendintid :10;
        kulong cpuid :3;
        kulong :19;
    } bit;
};

/* structure of giccIidr       (1D00_20FCh) */
union _IoGicCpuIidr
{
    kulong word;
    struct
    {
        kulong implementer :12;
        kulong revision :4;
        kulong version :4;
        kulong productid :12;
    } bit;
};

/* structure of giccDir        (1D00_3000h) */
union _IoGicCpuDir
{
    kulong word;
    struct
    {
        kulong intid :10;
        kulong cpuid :3;
        kulong :19;
    } bit;
};


/*  GIC Distributor register                */
struct _IoGicDist
{
    IoGicDistCtlr gicdCtlr;                      // 1D00_(1000 - 1003h) RW Distributor Control Register
    IoGicDistTyper gicdTyper;                     // 1D00_(1004 - 1007h) RO Interrupt Controller Type Register
    IoGicDistIidr gicdIidr;                      // 1D00_(1008 - 100Bh) RO Distributor Implementer Identification Register
    kuchar dmy100c107f[0x1080 - 0x100C]; // 1D00_(100C - 107Fh) Reserved
    kulong gicdIgroupr[32];               // 1D00_(1080 - 10FFh) RW Interrupt Group Registers
    kulong gicdIsenabler[32];             // 1D00_(1100 - 117Fh) RW Interrupt Set-Enable Registers
    kulong gicdIcenabler[32];             // 1D00_(1180 - 11FFh) RW Interrupt Clear-Enable Registers
    kulong gicdIspendr[32];               // 1D00_(1200 - 127Fh) RW Interrupt Set-Pending Registers
    kulong gicdIcpendr[32];               // 1D00_(1280 - 12FFh) RW Interrupt Clear-Pending Registers
    kulong gicdIsactiver[32];             // 1D00_(1300 - 137Fh) RW Interrupt Set-Active Registers
    kulong gicdIcactiver[32];             // 1D00_(1380 - 13FFh) RW Interrupt Clear-Active Registers
    kuchar gicdIpriorityr[512];           // 1D00_(1400 - 15FFh) RW Interrupt Priority Registers
    kuchar dmy160017ff[0x1800 - 0x1600]; // 1D00_(1600 - 17FFh) Reserved
    kuchar gicdItargetsr[512];            // 1D00_(1800 - 19FFh) RW Interrupt Processor Targets Registers
    kuchar dmy1a001bff[0x1C00 - 0x1A00]; // 1D00_(1A00 - 1BFFh) Reserved
    kulong gicdIcfgr[32];                 // 1D00_(1C00 - 1C7Fh) RW Interrupt Clear-Active Registers
    kuchar dmy1c801cff[0x1D00 - 0x1C80]; // 1D00_(1C80 - 1CFFh) Reserved
    IoGicDistPpisr gicdPpisr;                     // 1D00_(1D00 - 1D03h) RO Private Peripheral Interrupt Status Register
    kulong gicdSpisr[15];                 // 1D00_(1D04 - 1D3Fh) RO Shared Peripheral Interrupt Status Registers
    kuchar dmy1d401dff[0x1F00 - 0x1D40]; // 1D00_(1D40 - 1DFFh) Reserved
    IoGicDistSgir gicdSgir;                      // 1D00_(1F00 - 1F03h) WO Software Generated Interrupt Register
    kuchar dmy1f041f0f[0x1F10 - 0x1F04]; // 1D00_(1F04 - 1F0Fh) Reserved
    kulong gicdCpendsgir[4];              // 1D00_(1F10 - 1F1Fh) RW SGI Clear-Pending Registers
    kulong gicdSpendsgir[4];              // 1D00_(1F20 - 1F2Fh) RW SGI Set-Pending Registers
    kuchar dmy1f301fff[0x2000 - 0x1F30]; // 1D00_(1F30 - 1FFFh) Reserved
};

/*  GIC CPU Interface register              */
struct _IoGicCpu
{
    IoGicCpuCtlr giccCtlr;                      // 1D00_(2000 - 2003h) RW CPU Interface Control Register
    IoGicCpuPmr giccPmr;                       // 1D00_(2004 - 2007h) RW Interrupt Priority Mask Register
    IoGicCpuBpr giccBpr;                       // 1D00_(2008 - 200Bh) RW Binary Point Register
    IoGicCpuIar giccIar;                       // 1D00_(200C - 200Fh) RO Interrupt Acknowledge Register
    IoGicCpuEoir giccEoir;                      // 1D00_(2010 - 2013h) WO End of Interrupt Register
    IoGicCpuRpr giccRpr;                       // 1D00_(2014 - 2017h) RO Running Priority Register
    IoGicCpuHpir giccHppir;                     // 1D00_(2018 - 201Bh) RO Highest Priority Pending Interrupt Register
    IoGicCpuAbpr giccAbpr;                      // 1D00_(201C - 201Fh) RW Active Priorities Registers
    IoGicCpuAiar giccAiar;                      // 1D00_(2020 - 2023h) RO Aliased Interrupt Acknowledge Register
    IoGicCpuAeoir giccAeoir;                     // 1D00_(2024 - 2027h) WO Aliased End of Interrupt Register
    IoGicCpuAhppir giccAhppir;                    // 1D00_(2028 - 202Bh) RO Aliased Highest Priority Pending Interrupt Register
    kuchar dmy202c20cf[0x20D0 - 0x202C]; // 1D00_(202C - 20CFh) Reserved
    kulong giccApr0;                      // 1D00_(20D0 - 20D3h) RW Active Priorities Registers
    kuchar dmy20d420df[0x20E0 - 0x20D4]; // 1D00_(20D4 - 20DFh) Reserved
    kulong giccNsapr0;                    // 1D00_(20E0 - 20E3h) RW Non-secure Active Priorities Registers
    kuchar dmy20e420fb[0x20FC - 0x20E4]; // 1D00_(20E4 - 20FBh) Reserved
    IoGicCpuIidr giccIidr;                      // 1D00_(20FC - 20FFh) RO CPU Interface Identification Register
    kuchar dmy21002fff[0x3000 - 0x2100]; // 1D00_(2100 - 2FFFh) Reserved
    IoGicCpuDir giccDir;                       // 1D00_(3000 - 3003h) WO Deactivate Interrupt Register
};


KConstType  k_gic_get_type(void);
KGic*       k_gic_new(void);


#endif/*__K_GIC_H__*/

