/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition SDRAMC Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_SDRAMC_H__
#define __K_SDRAMC_H__


#include <klib.h>
#include "ksdramc2.h"


#define K_TYPE_SDRAMC	            (k_sdramc_get_type())
#define K_SDRAMC(obj)	            (K_TYPE_CHECK_INSTANCE_CAST((obj), KSdramc))
#define K_IS_SDRAMC(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_SDRAMC))


typedef struct _KSdramc             KSdramc;
typedef struct _KSdramcPrivate      KSdramcPrivate;

typedef struct _IoSdramc            IoSdramc;

typedef union _IoSdramcEmbnum       IoSdramcEmbnum;
typedef union _IoSdramcRemapaddr    IoSdramcRemapaddr;
typedef union _IoSdramcChsel        IoSdramcChsel;
typedef union _IoSdramcRatecount    IoSdramcRatecount;
typedef union _IoSdramcMasterop     IoSdramcMasterop;
typedef union _IoSdramcPriorit      IoSdramcPriorit;
typedef union _IoSdramcRatechg      IoSdramcRatechg;
typedef union _IoSdramcUmccmda      IoSdramcUmccmda;
typedef union _IoSdramcUmccmdb      IoSdramcUmccmdb;
typedef union _IoSdramcUmccmdc      IoSdramcUmccmdc;
typedef union _IoSdramcUmccmdd      IoSdramcUmccmdd;
typedef union _IoSdramcUmcinita     IoSdramcUmcinita;
typedef union _IoSdramcUmcinitb     IoSdramcUmcinitb;
typedef union _IoSdramcUmcinitc     IoSdramcUmcinitc;
typedef union _IoSdramcUmcdrm       IoSdramcUmcdrm;
typedef union _IoSdramcUmcinitset   IoSdramcUmcinitset;
typedef union _IoSdramcUmcinitsta   IoSdramcUmcinitsta;
typedef union _IoSdramcUmccmde      IoSdramcUmccmde;
typedef union _IoSdramcUmccmdf      IoSdramcUmccmdf;
typedef union _IoSdramcUmccmdg      IoSdramcUmccmdg;
typedef union _IoSdramcUmccmdh      IoSdramcUmccmdh;
typedef union _IoSdramcUmccmdi      IoSdramcUmccmdi;
typedef union _IoSdramcUmccmdj      IoSdramcUmccmdj;
typedef union _IoSdramcUmcspca      IoSdramcUmcspca;
typedef union _IoSdramcUmcspcb      IoSdramcUmcspcb;
typedef union _IoSdramcUmcspcsta    IoSdramcUmcspcsta;
typedef union _IoSdramcUmcmema      IoSdramcUmcmema;
typedef union _IoSdramcUmcmemb      IoSdramcUmcmemb;
typedef union _IoSdramcUmcmemch     IoSdramcUmcmemch;
typedef union _IoSdramcUmcmemset    IoSdramcUmcmemset;
typedef union _IoSdramcUmcacchk     IoSdramcUmcacchk;
typedef union _IoSdramcUmcaccrsa    IoSdramcUmcaccrsa;
typedef union _IoSdramcUmcaccrea    IoSdramcUmcaccrea;
typedef union _IoSdramcUmcwaccst    IoSdramcUmcwaccst;
typedef union _IoSdramcUmcraccst    IoSdramcUmcraccst;
typedef union _IoSdramcUmcmracs     IoSdramcUmcmracs;
typedef union _IoSdramcUmcmracsst   IoSdramcUmcmracsst;
typedef union _IoSdramcUmcmrwdt     IoSdramcUmcmrwdt;
typedef union _IoSdramcUmcmrrdt     IoSdramcUmcmrrdt;
typedef union _IoSdramcUmcrdata0    IoSdramcUmcrdata0;
typedef union _IoSdramcUmcrdata1    IoSdramcUmcrdata1;
typedef union _IoSdramcUmcwdata0    IoSdramcUmcwdata0;
typedef union _IoSdramcUmcwdata1    IoSdramcUmcwdata1;
typedef union _IoSdramcUmcdataset   IoSdramcUmcdataset;
typedef union _IoSdramcUmcwdatswp   IoSdramcUmcwdatswp;
typedef union _IoSdramcUmcintc      IoSdramcUmcintc;
typedef union _IoSdramcUmcintmsk    IoSdramcUmcintmsk;
typedef union _IoSdramcAccchkflg    IoSdramcAccchkflg;
typedef union _IoSdramcAccchkflgclr IoSdramcAccchkflgclr;
typedef union _IoSdramcAccchkloga   IoSdramcAccchkloga;
typedef union _IoSdramcAccchklogb   IoSdramcAccchklogb;
typedef union _IoSdramcUmcphya      IoSdramcUmcphya;
typedef union _IoSdramcUmcphyb      IoSdramcUmcphyb;
typedef union _IoSdramcUmcphyc      IoSdramcUmcphyc;
typedef union _IoSdramcUmcdfictla   IoSdramcUmcdfictla;
typedef union _IoSdramcUmcdfictlb   IoSdramcUmcdfictlb;
typedef union _IoSdramcUmcpfmctl    IoSdramcUmcpfmctl;
typedef union _IoSdramcUmcpfmst     IoSdramcUmcpfmst;
typedef union _IoSdramcClkena       IoSdramcClkena;
typedef union _IoSdramcClkenb       IoSdramcClkenb;
typedef union _IoSdramcClkenc       IoSdramcClkenc;
typedef union _IoSdramcClkenda      IoSdramcClkenda;
typedef union _IoSdramcClkenmon     IoSdramcClkenmon;
typedef union _IoSdramcIrqen        IoSdramcIrqen;
typedef union _IoSdramcIrqclr       IoSdramcIrqclr;


struct _KSdramc
{
    KObject parent;
};


/*  structure of accchkflgclr   */
union _IoSdramcAccchkflgclr
{
    kulong word;
    struct
    {
        kulong :8;
        kulong accchkflgclra :1;
        kulong accchkflgclrb :1;
        kulong :22;
    } bit;
};

/*  structure of accchkloga     */
union _IoSdramcAccchkloga
{
    kulong word;
    struct
    {
        kulong portid :6;
        kulong :26;
    } bit;
};

/*  structure of accchklogb     */
union _IoSdramcAccchklogb
{
    kulong word;
    struct
    {
        kulong drmadr :29;
        kulong :3;
    } bit;
};

/*  structure of umcphyctla     */
union _IoSdramcUmcphya
{
    kulong word;
    struct
    {
        kulong rstx :1;
        kulong :3;
        kulong pzqrstx :1;
        kulong :3;
        kulong rstxCack :1;
        kulong rstxPzq :1;
        kulong :2;
        kulong rstxDqdqs :4;
        kulong softrstxCack :1;
        kulong :3;
        kulong softrstxDqdqs :4;
        kulong dllrstxCack :1;
        kulong :3;
        kulong dllrstxDqdqs :4;
    } bit;
};

/*  structure of umcphyctlb     */
union _IoSdramcUmcphyb
{
    kulong word;
    struct
    {
        kulong dllInitUpdCack :1;
        kulong :3;
        kulong dllInitUpdDqdqs :4;
        kulong pzqInitUpd :1;
        kulong :7;
        kulong pzqUpdWidth :8;
        kulong :8;
    } bit;
};

/*  structure of umcphyctlc     */
union _IoSdramcUmcphyc
{
    kulong word;
    struct
    {
        kulong itrReq :1;
        kulong :3;
        kulong itrMode :4;
        kulong otrResp :1;
        kulong :23;
    } bit;
};

/*  structure of umcdfictla     */
union _IoSdramcUmcdfictla
{
    kulong word;
    struct
    {
        kulong lpreqCack :1;
        kulong lpreqDqdqs :1;
        kulong :29;
        kulong lpctlmd :1;
    } bit;
};

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN --
/*  structure of umcdfictlb     */
union _IoSdramcUmcdfictlb
{
    kulong word;
    struct
    {
        kulong dramClkDisable :1;
        kulong :30;
        kulong dramclkmd :1;
    }bit;
};

// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif  // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
/*  structure of umcpfmctl/umcmidpfmctl     */
union _IoSdramcUmcpfmctl
{
    kulong word;
    struct
    {
        kulong pfmOn :1;
        kulong pfmRst :1;
        kulong pfmRstAfterRead :1;
        kulong pfmMonROff :1;
        kulong pfmMonWOff :1;
        kulong :3;
        kulong pfmMonCmd :1;
        kulong :23;
    } bit;
};

/*  structure of umcpfmst/umcmidpfmst       */
union _IoSdramcUmcpfmst
{
    kulong word;
    struct
    {
        kulong vlddata :32;
    } bit;
};

/*  structure of clkenbifa      */
union _IoSdramcClkena
{
    kulong word;
    struct
    {
        kulong clkwmx10 :1;
        kulong clkwmx11 :1;
        kulong clkwmx12 :1;
        kulong clkwmx13 :1;
        kulong clkwmx20 :1;
        kulong clkwmx21 :1;
        kulong clkwmx22 :1;
        kulong clkwmx23 :1;
        kulong clkwmx30 :1;
        kulong clkwmx31 :1;
        kulong clkwmx32 :1;
        kulong clkwmx33 :1;
        kulong clkwmx40 :1;
        kulong clkwmx50 :1;
        kulong clkwmx51 :1;
        kulong clkwmx00 :1;
        kulong clkwmx01 :1;
        kulong clkwmx60 :1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
        kulong :14;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
        kulong :6;
        kulong clkwvcorew :1;
        kulong clkwvcorer0 :1;
        kulong clkwvcorer1 :1;
        kulong :3;
        kulong clkwvcpu :1;
        kulong :1;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif  // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
    } bit;
};

/*  structure of clkenbifb      */
union _IoSdramcClkenb
{
    kulong word;
    struct
    {
        kulong clkrmx10 :1;
        kulong clkrmx11 :1;
        kulong clkrmx12 :1;
        kulong clkrmx13 :1;
        kulong clkrmx20 :1;
        kulong clkrmx21 :1;
        kulong clkrmx22 :1;
        kulong clkrmx23 :1;
        kulong clkrmx30 :1;
        kulong clkrmx31 :1;
        kulong clkrmx32 :1;
        kulong clkrmx33 :1;
        kulong clkrmx40 :1;
        kulong clkrmx50 :1;
        kulong clkrmx51 :1;
        kulong clkrmx00 :1;
        kulong clkrmx01 :1;
        kulong clkrmx60 :1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
        kulong :14;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
        kulong :6;
        kulong clkrvcorew :1;
        kulong clkrvcorer0 :1;
        kulong clkrvcorer1 :1;
        kulong :3;
        kulong clkrvcpu :1;
        kulong :1;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif  // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
    } bit;
};

/*  structure of clkenbifc      */
union _IoSdramcClkenc
{
    kulong word;
    struct
    {
        kulong clkdsp :1;
        kulong :7;
        kulong clkbif :1;
        kulong :9;
        kulong clkrb0 :1;
        kulong clkrb1 :1;
        kulong clkrb2 :1;
        kulong clkds0 :1;
        kulong clkds1 :1;
        kulong clksdm :1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
        kulong clkve0 :1;
        kulong clkve1 :1;
        kulong clkve2 :1;
        kulong clkvd0 :1;
        kulong clkvd1 :1;
        kulong clkvd2 :1;
        kulong reserved :2;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
        kulong reserved0 :3;
        kulong clkvd0 :1;
        kulong clkvd1 :1;
        kulong clkvd2 :1;
        kulong reserved1 :1;
        kulong clkvorem :1;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif  // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
    } bit;
};

/*  structure of clkenda        */
union _IoSdramcClkenda
{
    kulong word;
    struct
    {
        kulong clkb0da :1;
        kulong clkb1da :1;
        kulong clkb2da :1;
        kulong clkb3da :1;
        kulong clkb4da :1;
        kulong clkb5da :1;
        kulong clkb6da :1;
        kulong clkb7da :1;
        kulong clkb8da :1;
        kulong clkb9da :1;
        kulong clkbada :1;
        kulong clkbbda :1;
        kulong clkbcda :1;
        kulong clkbdda :1;
        kulong clkbeda :1;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
        kulong clkbfda :1;
        kulong clkb10da :1;
        kulong :14;
        kulong clkdrbda :1;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
        kulong reserved0 :1;
        kulong clkb10da :1;
        kulong reserved1 :1;
        kulong clkb12da :1;
        kulong clkb13da :1;
        kulong clkb14da :1;
        kulong clkb15da :1;
        kulong reserved2 :9;
        kulong clkdrbda :1;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif  // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
    } bit;
};

/*  structure of clkenmon       */
union _IoSdramcClkenmon
{
    kulong word;
    struct
    {
        kulong clkmon :1;
        kulong :31;

    } bit;
};

/*  structure of irqen          */
union _IoSdramcIrqen
{
    kulong word;
    struct
    {
        kulong irqen :1;
        kulong :31;

    } bit;
};

/*  structure of irqclr         */
union _IoSdramcIrqclr
{
    kulong word;
    struct
    {
        kulong irqclr :1;
        kulong :31;

    } bit;
};

/* Define i/o mapping */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
struct _IoSdramc
{
    // Bus IF.
    IoSdramcEmbnum embnum[30]; /* (0000 - 0077h) */
    kuchar dmy007802ff[0x0300-0x0078]; /* (0078 - 02FFh) */
    IoSdramcRemapaddr remapaddr[30]; /* (0300 - 0377h) */

    kuchar dmy037804ff[0x0500-0x0378]; /* (0378 - 04FFh) */
    kuchar dmy05000fff[0x1000-0x0500]; /* (0500 - 0FFFh) */
    kuchar dmy100025ff[0x2600-0x1000]; /* (1000 - 25FFh) */

    IoSdramcChsel chsel[30]; /* (2600 - 2677h) */
    kuchar dmy26784fff[0x5000-0x2678]; /* (2678 - 4FFFh) */

    // Command arbitration.
    IoSdramcRatecount ratecont[30]; /* (5000 - 5077h) */
    kuchar dmy507851ff[0x5200-0x5078]; /* (5078 - 51FFh) */

    IoSdramcMasterop masteroption[30]; /* (5200 - 5277h) */
    kuchar dmy527853ff[0x5400-0x5278]; /* (5278 - 53FFh) */

    IoSdramcPriorit prioritCat[30]; /* (5400 - 5477h) */
    kuchar dmy547854ff[0x5500-0x5478]; /* (5478 - 54FFh) */

    kuchar dmy550059ff[0x5A00-0x5500]; /* (5500 - 59FFh) */

    IoSdramcRatechg rateChange; /* (5A00 - 5A03h) */
    kuchar dmy5a045aff[0x5B00-0x5A04]; /* (5A04 - 5AFFh) */

    kuchar dmy5b007fff[0x8000-0x5B00]; /* (5B00 - 7FFFh) */

    // DRAM control.
    IoSdramcUmccmda umccmdctla; /* (8000 - 8003h) */
    IoSdramcUmccmdb umccmdctlb; /* (8004 - 8007h) */
    IoSdramcUmccmdc umccmdctlc; /* (8008 - 800Bh) */
    IoSdramcUmccmdd umccmdctld; /* (800C - 800Fh) */
    kuchar dmy8010801f[0x8020-0x8010]; /* (8010 - 801Fh) */
    IoSdramcUmcinita umcinitctla; /* (8020 - 8023h) */
    IoSdramcUmcinitb umcinitctlb; /* (8024 - 8027h) */
    IoSdramcUmcinitc umcinitctlc; /* (8028 - 802Bh) */
    kuchar dmy802c802f[0x8030-0x802C]; /* (802C - 802Fh) */
    IoSdramcUmcdrm umcdrmmra; /* (8030 - 8033h) */
    kuchar dmy8034803f[0x8040-0x8034]; /* (8034 - 803Fh) */
    IoSdramcUmcinitset umcinitset; /* (8040 - 8043h) */
    IoSdramcUmcinitsta umcinitstat; /* (8044 - 8047h) */
    kuchar dmy8048804f[0x8050-0x8048]; /* (8048 - 804Fh) */
    IoSdramcUmccmde umccmdctle; /* (8050 - 8053h) */
    IoSdramcUmccmdf umccmdctlf; /* (8054 - 8057h) */
    IoSdramcUmccmdg umccmdctlg; /* (8058 - 805Bh) */
    IoSdramcUmccmdh umccmdctlh; /* (805C - 805Fh) */
    IoSdramcUmccmdi umccmdctli; /* (8060 - 8063h) */
    IoSdramcUmccmdj umccmdctlj; /* (8064 - 8067h) */
    kuchar dmy8068807f[0x8080-0x8068]; /* (8068 - 807Fh) */
    IoSdramcUmcspca umcspcseta; /* (8080 - 8083h) */
    IoSdramcUmcspcb umcspcsetb; /* (8084 - 8087h) */
    kuchar dmy8088808f[0x8090-0x8088]; /* (8088 - 808Fh) */
    IoSdramcUmcspcsta umcspcstat; /* (8090 - 8093h) */
    kuchar dmy8094809f[0x80A0-0x8094]; /* (8094 - 809Fh) */

    kuchar dmy80a081ff[0x8200-0x80A0]; /* (80A0 - 81FFh) */

    IoSdramcUmcmema umcmemconf0a; /* (8200 - 8203h) */
    IoSdramcUmcmemb umcmemconf0b; /* (8204 - 8207h) */
    kuchar dmy8208820f[0x8210-0x8208]; /* (8208 - 820Fh) */
    IoSdramcUmcmema umcmemconf1a; /* (8210 - 8213h) */
    IoSdramcUmcmemb umcmemconf1b; /* (8214 - 8217h) */
    kuchar dmy8218823f[0x8240-0x8218]; /* (8218 - 823Fh) */
    IoSdramcUmcmemch umcmemconfch; /* (8240 - 8243h) */
    kuchar dmy8244824f[0x8250-0x8244]; /* (8244 - 824Fh) */
    IoSdramcUmcmemset umcmemmapset; /* (8250 - 8253h) */
    kuchar dmy8254827f[0x8280-0x8254]; /* (8254 - 827Fh) */

    kuchar dmy828082ff[0x8300-0x8280]; /* (8280 - 82FFh) */

    IoSdramcUmcacchk umcaccchka; /* (8300 - 8303h) */
    IoSdramcUmcaccrsa umcaccarsaa; /* (8304 - 8307h) */
    IoSdramcUmcaccrea umcaccareaa; /* (8308 - 830Bh) */
    IoSdramcUmcwaccst umcwaccmsta; /* (830C - 830Fh) */
    IoSdramcUmcraccst umcraccmsta; /* (8310 - 8313h) */
    kuchar dmy8314831f[0x8320-0x8314]; /* (8314 - 831Fh) */
    IoSdramcUmcacchk umcaccchkb; /* (8320 - 8323h) */
    IoSdramcUmcaccrsa umcaccarsab; /* (8324 - 8327h) */
    IoSdramcUmcaccrea umcaccareab; /* (8328 - 832Bh) */
    IoSdramcUmcwaccst umcwaccmstb; /* (832C - 832Fh) */
    IoSdramcUmcraccst umcraccmstb; /* (8330 - 8333h) */
    kuchar dmy8334833f[0x8340-0x8334]; /* (8334 - 833Fh) */
    IoSdramcUmcacchk umcoodchk; /* (8340 - 8343h) */
    kuchar dmy8344835f[0x8360-0x8344]; /* (8344 - 835Fh) */
    IoSdramcUmcmracs umcmracs; /* (8360 - 8363h) */
    IoSdramcUmcmracsst umcmracsst; /* (8364 - 8367h) */
    kuchar dmy8368836f[0x8370-0x8368]; /* (8368 - 836Fh) */
    IoSdramcUmcmrwdt umcmrwdt; /* (8370 - 8373h) */
    kuchar dmy8374838f[0x8390-0x8374]; /* (8374 - 838Fh) */
    IoSdramcUmcmrrdt umcmrrdt; /* (8390 - 8393h) */
    kuchar dmy839483ff[0x8400-0x8394]; /* (8394 - 83FFh) */

    kuchar dmy840085ff[0x8600-0x8400]; /* (8400 - 85FFh) */

    IoSdramcUmcrdata0 umcrdatactlD0; /* (8600 - 8603h) */
    IoSdramcUmcwdata0 umcwdatactlD0; /* (8604 - 8607h) */
    IoSdramcUmcrdata1 umcrdatactlD1; /* (8608 - 860Bh) */
    IoSdramcUmcwdata1 umcwdatactlD1; /* (860C - 860Fh) */
    IoSdramcUmcdataset umcdataset; /* (8610 - 8613h) */
    kuchar dmy8614861f[0x8620-0x8614]; /* (8614 - 861Fh) */
    IoSdramcUmcwdatswp umcwdataswp; /* (8620 - 8623h) */
    kuchar dmy8624867f[0x8680-0x8624]; /* (8624 - 867Fh) */

    kuchar dmy868088ff[0x8900-0x8680]; /* (8680 - 88FFh) */

    kuchar dmy8900894f[0x8950-0x8900]; /* (8900 - 894Fh) */
    IoSdramcUmcintc umcintcausem0; /* (8950 - 8953h) */
    kuchar dmy89548957[0x8958-0x8954]; /* (8954 - 8957h) */
    IoSdramcUmcintmsk umcintmaskm0; /* (8958 - 895Bh) */
    kuchar dmy895c8967[0x8968-0x895C]; /* (895C - 8967h) */
    IoSdramcAccchkflg accchkflg; /* (8968 - 896Bh) */
    IoSdramcAccchkflgclr accchkflgclr; /* (896C - 896Fh) */
    IoSdramcAccchkloga accchkloga; /* (8970 - 8973h) */
    IoSdramcAccchklogb accchklogb; /* (8974 - 8977h) */
    kuchar dmy897889ff[0x8A00-0x8978]; /* (8978 - 89FFh) */

    kuchar dmy8a008bff[0x8C00-0x8A00]; /* (8A00 - 8BFFh) */

    IoSdramcUmcphya umcphyctla; /* (8C00 - 8C03h) */
    IoSdramcUmcphyb umcphyctlb; /* (8C04 - 8C07h) */
    IoSdramcUmcphyc umcphyctlc; /* (8C08 - 8C0Bh) */
    kuchar dmy8c0c8c3f[0x8C40-0x8C0C]; /* (8C0C - 8C3Fh) */
    IoSdramcUmcdfictla umcdfictla; /* (8C40 - 8C43h) */
    kuchar dmy8c448cff[0x8D00-0x8C44]; /* (8C44 - 8CFFh) */
    IoSdramcUmcpfmctl umcpfmctl; /* (8D00 - 8D03h) */
    kuchar dmy8d048d1f[0x8D20-0x8D04]; /* (8D04 - 8D1Fh) */
    IoSdramcUmcpfmst umcpfmst[30]; /* (8D20 - 8D97h) */
    kuchar dmy8d988e3f[0x8E40-0x8D98]; /* (8D98 - 8E3Fh) */
    IoSdramcUmcpfmctl umcmidpfmctl; /* (8E40 - 8E43h) */
    kuchar dmy8e448e5f[0x8E60-0x8E44]; /* (8E44 - 8E5Fh) */
    IoSdramcUmcpfmst umcmidpfmst[62]; /* (8E60 - 8F57h) */
    kuchar dmy8f588fff[0x9000-0x8F58]; /* (8F58 - 8FFFh) */

    kuchar dmy9000Efff[0xF000-0x9000]; /* (9000 - EFFFh) */

    // Overall control.
    IoSdramcClkena clkenbifa; /* (F000 - F003h) */
    IoSdramcClkenb clkenbifb; /* (F004 - F007h) */
    IoSdramcClkenc clkenbifc; /* (F008 - F00Bh) */
    kuchar dmyF00cF00f[0xF010-0xF00C]; /* (F00C - F00Fh) */
    IoSdramcClkenda clkenda; /* (F010 - F013h) */
    kuchar dmyF014F01f[0xF020-0xF014]; /* (F014 - F01Fh) */
    IoSdramcClkenmon clkenmon; /* (F020 - F023h) */
    kuchar dmyF024F0ff[0xF100-0xF024]; /* (F024 - F0FFh) */

    kuchar dmyF100F2ff[0xF300-0xF100]; /* (F100 - F2FFh) */

    IoSdramcIrqen irqen; /* (F300 - F303h) */
    kuchar dmyF304F307[0xF308-0xF304]; /* (F304 - F307h) */
    IoSdramcIrqclr irqclr; /* (F308 - F30Bh) */
    kuchar dmyF30cF3ff[0xF400-0xF30C]; /* (F30C - F3FFh) */

    kuchar dmyF4001ffff[0x20000-0xF400]; /* (F400 - 1FFFFh) */
};
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN --
struct _IoSdramc {
    // Bus IF.
    IoSdramcEmbnum embnum[34]; /* (0000 - 0087h) */
    kuchar dmy008802ff[0x0300-0x0088]; /* (0088 - 02FFh) */
    IoSdramcRemapaddr remapaddr[34]; /* (0300 - 0387h) */

    kuchar dmy038804ff[0x0500-0x0388]; /* (0388 - 04FFh) */
    kuchar dmy05000fff[0x1000-0x0500]; /* (0500 - 0FFFh) */
    kuchar dmy100025ff[0x2600-0x1000]; /* (1000 - 25FFh) */

    IoSdramcChsel chsel[34]; /* (2600 - 2687h) */
    kuchar dmy26884fff[0x5000-0x2688]; /* (2688 - 4FFFh) */

    // Command arbitration.
    IoSdramcRatecount ratecont[34]; /* (5000 - 5087h) */
    kuchar dmy508851ff[0x5200-0x5088]; /* (5088 - 51FFh) */

    IoSdramcMasterop masteroption[34]; /* (5200 - 5287h) */
    kuchar dmy527853ff[0x5400-0x5288]; /* (5288 - 53FFh) */

    IoSdramcPriorit prioritCat[34]; /* (5400 - 5487h) */
    kuchar dmy548854ff[0x5500-0x5488]; /* (5488 - 54FFh) */

    kuchar dmy550059ff[0x5A00-0x5500]; /* (5500 - 59FFh) */

    IoSdramcRatechg rateChange; /* (5A00 - 5A03h) */
    kuchar dmy5a045aff[0x5B00-0x5A04]; /* (5A04 - 5AFFh) */

    kuchar dmy5b007fff[0x8000-0x5B00]; /* (5B00 - 7FFFh) */

    // DRAM control.
    IoSdramcUmccmda umccmdctla; /* (8000 - 8003h) */
    IoSdramcUmccmdb umccmdctlb; /* (8004 - 8007h) */
    IoSdramcUmccmdc umccmdctlc; /* (8008 - 800Bh) */
    IoSdramcUmccmdd umccmdctld; /* (800C - 800Fh) */
    kuchar dmy8010801f[0x8020-0x8010]; /* (8010 - 801Fh) */
    IoSdramcUmcinita umcinitctla; /* (8020 - 8023h) */
    IoSdramcUmcinitb umcinitctlb; /* (8024 - 8027h) */
    IoSdramcUmcinitc umcinitctlc; /* (8028 - 802Bh) */
    kuchar dmy802c802f[0x8030-0x802C]; /* (802C - 802Fh) */
    IoSdramcUmcdrm umcdrmmra; /* (8030 - 8033h) */
    kuchar dmy8034803f[0x8040-0x8034]; /* (8034 - 803Fh) */
    IoSdramcUmcinitset umcinitset; /* (8040 - 8043h) */
    IoSdramcUmcinitsta umcinitstat; /* (8044 - 8047h) */
    kuchar dmy8048804f[0x8050-0x8048]; /* (8048 - 804Fh) */
    IoSdramcUmccmde umccmdctle; /* (8050 - 8053h) */
    IoSdramcUmccmdf umccmdctlf; /* (8054 - 8057h) */
    IoSdramcUmccmdg umccmdctlg; /* (8058 - 805Bh) */
    IoSdramcUmccmdh umccmdctlh; /* (805C - 805Fh) */
    IoSdramcUmccmdi umccmdctli; /* (8060 - 8063h) */
    IoSdramcUmccmdj umccmdctlj; /* (8064 - 8067h) */
    kuchar dmy8068807f[0x8080-0x8068]; /* (8068 - 807Fh) */
    IoSdramcUmcspca umcspcseta; /* (8080 - 8083h) */
    IoSdramcUmcspcb umcspcsetb; /* (8084 - 8087h) */
    kuchar dmy8088808f[0x8090-0x8088]; /* (8088 - 808Fh) */
    IoSdramcUmcspcsta umcspcstat; /* (8090 - 8093h) */
    kuchar dmy8094809f[0x80A0-0x8094]; /* (8094 - 809Fh) */

    kuchar dmy80a081ff[0x8200-0x80A0]; /* (80A0 - 81FFh) */

    IoSdramcUmcmema umcmemconf0a; /* (8200 - 8203h) */
    IoSdramcUmcmemb umcmemconf0b; /* (8204 - 8207h) */
    kuchar dmy8208820f[0x8210-0x8208]; /* (8208 - 820Fh) */
    IoSdramcUmcmema umcmemconf1a; /* (8210 - 8213h) */
    IoSdramcUmcmemb umcmemconf1b; /* (8214 - 8217h) */
    kuchar dmy8218823f[0x8240-0x8218]; /* (8218 - 823Fh) */
    IoSdramcUmcmemch umcmemconfch; /* (8240 - 8243h) */
    kuchar dmy8244824f[0x8250-0x8244]; /* (8244 - 824Fh) */
    IoSdramcUmcmemset umcmemmapset; /* (8250 - 8253h) */
    kuchar dmy8254827f[0x8280-0x8254]; /* (8254 - 827Fh) */

    kuchar dmy828082ff[0x8300-0x8280]; /* (8280 - 82FFh) */

    IoSdramcUmcacchk umcaccchka; /* (8300 - 8303h) */
    IoSdramcUmcaccrsa umcaccarsaa; /* (8304 - 8307h) */
    IoSdramcUmcaccrea umcaccareaa; /* (8308 - 830Bh) */
    IoSdramcUmcwaccst umcwaccmstal; /* (830C - 830Fh) */
    IoSdramcUmcraccst umcraccmstal; /* (8310 - 8313h) */
    IoSdramcUmcwaccst umcwaccmstau; /* (8314 - 8317h) */
    IoSdramcUmcraccst umcraccmstau; /* (8318 - 831Bh) */
    kuchar dmy831c831f[0x8320-0x831C]; /* (831C - 831Fh) */
    IoSdramcUmcacchk umcaccchkb; /* (8320 - 8323h) */
    IoSdramcUmcaccrsa umcaccarsab; /* (8324 - 8327h) */
    IoSdramcUmcaccrea umcaccareab; /* (8328 - 832Bh) */
    IoSdramcUmcwaccst umcwaccmstbl; /* (832C - 832Fh) */
    IoSdramcUmcraccst umcraccmstbl; /* (8330 - 8333h) */
    IoSdramcUmcwaccst umcwaccmstbu; /* (8334 - 8337h) */
    IoSdramcUmcraccst umcraccmstbu; /* (8338 - 833Bh) */
    kuchar dmy833c833f[0x8340-0x833C]; /* (833C - 833Fh) */
    IoSdramcUmcacchk umcoodchk; /* (8340 - 8343h) */
    kuchar dmy8344835f[0x8360-0x8344]; /* (8344 - 835Fh) */
    IoSdramcUmcmracs umcmracs; /* (8360 - 8363h) */
    IoSdramcUmcmracsst umcmracsst; /* (8364 - 8367h) */
    kuchar dmy8368836f[0x8370-0x8368]; /* (8368 - 836Fh) */
    IoSdramcUmcmrwdt umcmrwdt; /* (8370 - 8373h) */
    kuchar dmy8374838f[0x8390-0x8374]; /* (8374 - 838Fh) */
    IoSdramcUmcmrrdt umcmrrdt; /* (8390 - 8393h) */
    kuchar dmy839483ff[0x8400-0x8394]; /* (8394 - 83FFh) */

    kuchar dmy840085ff[0x8600-0x8400]; /* (8400 - 85FFh) */

    IoSdramcUmcrdata0 umcrdatactlD0; /* (8600 - 8603h) */
    IoSdramcUmcwdata0 umcwdatactlD0; /* (8604 - 8607h) */
    IoSdramcUmcrdata1 umcrdatactlD1; /* (8608 - 860Bh) */
    IoSdramcUmcwdata1 umcwdatactlD1; /* (860C - 860Fh) */
    IoSdramcUmcdataset umcdataset; /* (8610 - 8613h) */
    kuchar dmy8614861f[0x8620-0x8614]; /* (8614 - 861Fh) */
    IoSdramcUmcwdatswp umcwdataswp; /* (8620 - 8623h) */
    kuchar dmy8624867f[0x8680-0x8624]; /* (8624 - 867Fh) */

    kuchar dmy868088ff[0x8900-0x8680]; /* (8680 - 88FFh) */

    kuchar dmy8900894f[0x8950-0x8900]; /* (8900 - 894Fh) */
    IoSdramcUmcintc umcintcausem0; /* (8950 - 8953h) */
    IoSdramcUmcintc umcintcausem1; /* (8954 - 8957h) */
    IoSdramcUmcintmsk umcintmaskm0; /* (8958 - 895Bh) */
    IoSdramcUmcintmsk umcintmaskm1; /* (895C - 895Fh) */
    kuchar dmy89608967[0x8968-0x8960]; /* (8960 - 8967h) */
    IoSdramcAccchkflg accchkflg; /* (8968 - 896Bh) */
    IoSdramcAccchkflgclr accchkflgclr; /* (896C - 896Fh) */
    IoSdramcAccchkloga accchkloga; /* (8970 - 8973h) */
    IoSdramcAccchklogb accchklogb; /* (8974 - 8977h) */
    kuchar dmy897889ff[0x8A00-0x8978]; /* (8978 - 89FFh) */

    kuchar dmy8a008bff[0x8C00-0x8A00]; /* (8A00 - 8BFFh) */

    IoSdramcUmcphya umcphyctla; /* (8C00 - 8C03h) */
    IoSdramcUmcphyb umcphyctlb; /* (8C04 - 8C07h) */
    IoSdramcUmcphyc umcphyctlc; /* (8C08 - 8C0Bh) */
    kuchar dmy8c0c8c13[0x8C14-0x8C0C]; /* (8C0C - 8C13h) */
    IoSdramcUmcdfictlb umcdfictlb; /* (8C14 - 8C17h) */
    kuchar dmy8c188c3f[0x8C40-0x8C18]; /* (8C18 - 8C3Fh) */
    IoSdramcUmcdfictla umcdfictla; /* (8C40 - 8C43h) */
    kuchar dmy8c448cff[0x8D00-0x8C44]; /* (8C44 - 8CFFh) */
    IoSdramcUmcpfmctl umcpfmctl; /* (8D00 - 8D03h) */
    kuchar dmy8d048d1f[0x8D20-0x8D04]; /* (8D04 - 8D1Fh) */
    IoSdramcUmcpfmst umcpfmst[34]; /* (8D20 - 8DA7h) */
    kuchar dmy8da88e3f[0x8E40-0x8DA8]; /* (8DA8 - 8E3Fh) */
    IoSdramcUmcpfmctl umcmidpfmctl; /* (8E40 - 8E43h) */
    kuchar dmy8e448e5f[0x8E60-0x8E44]; /* (8E44 - 8E5Fh) */
    IoSdramcUmcpfmst umcmidpfmst[62]; /* (8E60 - 8F57h) */
    kuchar dmy8f588fff[0x9000-0x8F58]; /* (8F58 - 8FFFh) */

    kuchar dmy9000Efff[0xF000-0x9000]; /* (9000 - EFFFh) */

    // Overall control.
    IoSdramcClkena clkenbifa; /* (F000 - F003h) */
    IoSdramcClkenb clkenbifb; /* (F004 - F007h) */
    IoSdramcClkenc clkenbifc; /* (F008 - F00Bh) */
    kuchar dmyF00cF00f[0xF010-0xF00C]; /* (F00C - F00Fh) */
    IoSdramcClkenda clkenda; /* (F010 - F013h) */
    kuchar dmyF014F01f[0xF020-0xF014]; /* (F014 - F01Fh) */
    IoSdramcClkenmon clkenmon; /* (F020 - F023h) */
    kuchar dmyF024F0ff[0xF100-0xF024]; /* (F024 - F0FFh) */

    kuchar dmyF100F2ff[0xF300-0xF100]; /* (F100 - F2FFh) */

    IoSdramcIrqen irqen; /* (F300 - F303h) */
    kuchar dmyF304F307[0xF308-0xF304]; /* (F304 - F307h) */
    IoSdramcIrqclr irqclr; /* (F308 - F30Bh) */
    kuchar dmyF30cF3ff[0xF400-0xF30C]; /* (F30C - F3FFh) */

    kuchar dmyF4001ffff[0x20000-0xF400]; /* (F400 - 1FFFFh) */
};
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif  // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---


extern volatile IoSdramc ioSdramc[2];


KConstType  k_sdramc_get_type(void);
KSdramc*    k_sdramc_new(void);


#endif/*__K_SDRAMC_H__*/
