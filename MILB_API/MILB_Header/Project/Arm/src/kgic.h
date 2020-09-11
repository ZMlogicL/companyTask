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

#define K_TYPE_GIC	(k_gic_get_type())
#define K_GIC(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KGic))
#define K_IS_GIC(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_GIC))

typedef struct _KGic KGic;
typedef struct _KGicPrivate KGicPrivate;

typedef struct _IoGicDist IoGicDist;
typedef struct _IoGicCpu IoGicCpu;

typedef union _IoGicDistCtlr IoGicDistCtlr;
typedef union _IoGicDistTyper IoGicDistTyper;
typedef union _IoGicDistIidr IoGicDistIidr;
typedef union _IoGicDistPpisr IoGicDistPpisr;
typedef union _IoGicDistSgir IoGicDistSgir;
typedef union _IoGicCpuCtlr IoGicCpuCtlr;
typedef union _IoGicCpuPmr IoGicCpuPmr;
typedef union _IoGicCpuBpr IoGicCpuBpr;
typedef union _IoGicCpuIar IoGicCpuIar;
typedef union _IoGicCpuEoir IoGicCpuEoir;
typedef union _IoGicCpuRpr IoGicCpuRpr;
typedef union _IoGicCpuHpir IoGicCpuHpir;
typedef union _IoGicCpuAbpr IoGicCpuAbpr;
typedef union _IoGicCpuAiar IoGicCpuAiar;
typedef union _IoGicCpuAeoir IoGicCpuAeoir;
typedef union _IoGicCpuAhppir IoGicCpuAhppir;
typedef union _IoGicCpuIidr IoGicCpuIidr;
typedef union _IoGicCpuDir IoGicCpuDir;

extern volatile IoGicDist ioGicDist;
extern volatile IoGicCpu ioGicCpu;

struct _KGic
{
    KObject parent;
};

/* structure of gicdCtlr       (1D00_1000h) */
union _IoGicDistCtlr
{
    unsigned long word;
    struct
    {
        unsigned long ENABLEGR0 :1;
        unsigned long ENABLEGR1 :1;
        unsigned long :30;
    } bit;
};

/* structure of gicdTyper      (1D00_1004h) */
union _IoGicDistTyper
{
    unsigned long word;
    struct
    {
        unsigned long itlinesnumber :5;
        unsigned long cpunumber :3;
        unsigned long :2;
        unsigned long securityExtn :1;
        unsigned long lspi :5;
        unsigned long :16;
    } bit;
};

/* structure of gicdIidr       (1D00_1008h) */
union _IoGicDistIidr
{
    unsigned long word;
    struct
    {
        unsigned long implementer :12;
        unsigned long revision :4;
        unsigned long variant :4;
        unsigned long :4;
        unsigned long productid :8;
    } bit;
};

/* structure of gicdPpisr      (1D00_1D00h) */
union _IoGicDistPpisr
{
    unsigned long word;
    struct
    {
        unsigned long :9;
        unsigned long ppi6Status :1;
        unsigned long ppi5Status :1;
        unsigned long ppi4Status :1;
        unsigned long ppi0Status :1;
        unsigned long ppi1Status :1;
        unsigned long ppi2Status :1;
        unsigned long ppi3Status :1;
        unsigned long :16;
    } bit;
};

/* structure of gicdSgir       (1D00_1F00h) */
union _IoGicDistSgir
{
    unsigned long word;
    struct
    {
        unsigned long sgiintid :4;
        unsigned long :11;
        unsigned long nsatt :1;
        unsigned long cputargetlist :8;
        unsigned long targetlistfilter :2;
        unsigned long :6;
    } bit;
};

/* structure of giccCtlr       (1D00_2000h) */
union _IoGicCpuCtlr
{
    unsigned long word;
    struct
    {
        unsigned long enablegrp0 :1;
        unsigned long enablegrp1 :1;
        unsigned long ackctl :1;
        unsigned long fiqen :1;
        unsigned long cbpr :1;
        unsigned long fiqbypdisgrp0 :1;
        unsigned long irqbypdisgrp0 :1;
        unsigned long fiqbypdisgrp1 :1;
        unsigned long irqbypdisgrp1 :1;
        unsigned long eoimodes :1;
        unsigned long eoimodens :1;
        unsigned long :21;
    } bit;
};

/* structure of giccPmr        (1D00_2004h) */
union _IoGicCpuPmr
{
    unsigned long word;
    struct
    {
        unsigned long priority :8;
        unsigned long :24;
    } bit;
};

/* structure of giccBpr        (1D00_2008h) */
union _IoGicCpuBpr
{
    unsigned long word;
    struct
    {
        unsigned long binarypoint :3;
        unsigned long :29;
    } bit;
};

/* structure of giccIar        (1D00_200Ch) */
union _IoGicCpuIar
{
    unsigned long word;
    struct
    {
        unsigned long ackintid :10;
        unsigned long cpuid :3;
        unsigned long :19;
    } bit;
};

/* structure of giccEoir       (1D00_2010h) */
union _IoGicCpuEoir
{
    unsigned long word;
    struct
    {
        unsigned long eoiintid :10;
        unsigned long cpuid :3;
        unsigned long :19;
    } bit;
};

/* structure of giccRpr        (1D00_2014h) */
union _IoGicCpuRpr
{
    unsigned long word;
    struct
    {
        unsigned long priority :8;
        unsigned long :24;
    } bit;
};

/* structure of giccHppir      (1D00_2018h) */
union _IoGicCpuHpir
{
    unsigned long word;
    struct
    {
        unsigned long pendintid :10;
        unsigned long cpuid :3;
        unsigned long :19;
    } bit;
};

/* structure of giccAbpr       (1D00_201Ch) */
union _IoGicCpuAbpr
{
    unsigned long word;
    struct
    {
        unsigned long binarypoint :3;
        unsigned long :29;
    } bit;
};

/* structure of giccAiar       (1D00_2020h) */
union _IoGicCpuAiar
{
    unsigned long word;
    struct
    {
        unsigned long ackintid :10;
        unsigned long cpuid :3;
        unsigned long :19;
    } bit;
};

/* structure of giccAeoir      (1D00_2024h) */
union _IoGicCpuAeoir
{
    unsigned long word;
    struct
    {
        unsigned long eoiintid :10;
        unsigned long cpuid :3;
        unsigned long :19;
    } bit;
};

/* structure of giccAhppir     (1D00_2028h) */
union _IoGicCpuAhppir
{
    unsigned long word;
    struct
    {
        unsigned long pendintid :10;
        unsigned long cpuid :3;
        unsigned long :19;
    } bit;
};

/* structure of giccIidr       (1D00_20FCh) */
union _IoGicCpuIidr
{
    unsigned long word;
    struct
    {
        unsigned long implementer :12;
        unsigned long revision :4;
        unsigned long version :4;
        unsigned long productid :12;
    } bit;
};

/* structure of giccDir        (1D00_3000h) */
union _IoGicCpuDir
{
    unsigned long word;
    struct
    {
        unsigned long intid :10;
        unsigned long cpuid :3;
        unsigned long :19;
    } bit;
};

/*  GIC Distributor register                */
struct _IoGicDist
{
    IoGicDistCtlr gicdCtlr;                      // 1D00_(1000 - 1003h) RW Distributor Control Register
    IoGicDistTyper gicdTyper;                     // 1D00_(1004 - 1007h) RO Interrupt Controller Type Register
    IoGicDistIidr gicdIidr;                      // 1D00_(1008 - 100Bh) RO Distributor Implementer Identification Register
    unsigned char dmy100c107f[0x1080 - 0x100C]; // 1D00_(100C - 107Fh) Reserved
    unsigned long gicdIgroupr[32];               // 1D00_(1080 - 10FFh) RW Interrupt Group Registers
    unsigned long gicdIsenabler[32];             // 1D00_(1100 - 117Fh) RW Interrupt Set-Enable Registers
    unsigned long gicdIcenabler[32];             // 1D00_(1180 - 11FFh) RW Interrupt Clear-Enable Registers
    unsigned long gicdIspendr[32];               // 1D00_(1200 - 127Fh) RW Interrupt Set-Pending Registers
    unsigned long gicdIcpendr[32];               // 1D00_(1280 - 12FFh) RW Interrupt Clear-Pending Registers
    unsigned long gicdIsactiver[32];             // 1D00_(1300 - 137Fh) RW Interrupt Set-Active Registers
    unsigned long gicdIcactiver[32];             // 1D00_(1380 - 13FFh) RW Interrupt Clear-Active Registers
    unsigned char gicdIpriorityr[512];           // 1D00_(1400 - 15FFh) RW Interrupt Priority Registers
    unsigned char dmy160017ff[0x1800 - 0x1600]; // 1D00_(1600 - 17FFh) Reserved
    unsigned char gicdItargetsr[512];            // 1D00_(1800 - 19FFh) RW Interrupt Processor Targets Registers
    unsigned char dmy1a001bff[0x1C00 - 0x1A00]; // 1D00_(1A00 - 1BFFh) Reserved
    unsigned long gicdIcfgr[32];                 // 1D00_(1C00 - 1C7Fh) RW Interrupt Clear-Active Registers
    unsigned char dmy1c801cff[0x1D00 - 0x1C80]; // 1D00_(1C80 - 1CFFh) Reserved
    IoGicDistPpisr gicdPpisr;                     // 1D00_(1D00 - 1D03h) RO Private Peripheral Interrupt Status Register
    unsigned long gicdSpisr[15];                 // 1D00_(1D04 - 1D3Fh) RO Shared Peripheral Interrupt Status Registers
    unsigned char dmy1d401dff[0x1F00 - 0x1D40]; // 1D00_(1D40 - 1DFFh) Reserved
    IoGicDistSgir gicdSgir;                      // 1D00_(1F00 - 1F03h) WO Software Generated Interrupt Register
    unsigned char dmy1f041f0f[0x1F10 - 0x1F04]; // 1D00_(1F04 - 1F0Fh) Reserved
    unsigned long gicdCpendsgir[4];              // 1D00_(1F10 - 1F1Fh) RW SGI Clear-Pending Registers
    unsigned long gicdSpendsgir[4];              // 1D00_(1F20 - 1F2Fh) RW SGI Set-Pending Registers
    unsigned char dmy1f301fff[0x2000 - 0x1F30]; // 1D00_(1F30 - 1FFFh) Reserved
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
    unsigned char dmy202c20cf[0x20D0 - 0x202C]; // 1D00_(202C - 20CFh) Reserved
    unsigned long giccApr0;                      // 1D00_(20D0 - 20D3h) RW Active Priorities Registers
    unsigned char dmy20d420df[0x20E0 - 0x20D4]; // 1D00_(20D4 - 20DFh) Reserved
    unsigned long giccNsapr0;                    // 1D00_(20E0 - 20E3h) RW Non-secure Active Priorities Registers
    unsigned char dmy20e420fb[0x20FC - 0x20E4]; // 1D00_(20E4 - 20FBh) Reserved
    IoGicCpuIidr giccIidr;                      // 1D00_(20FC - 20FFh) RO CPU Interface Identification Register
    unsigned char dmy21002fff[0x3000 - 0x2100]; // 1D00_(2100 - 2FFFh) Reserved
    IoGicCpuDir giccDir;                       // 1D00_(3000 - 3003h) WO Deactivate Interrupt Register
};

KConstType k_gic_get_type(void);
KGic* k_gic_new(void);

#endif/*__K_GIC_H__*/

