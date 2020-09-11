/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-11
 *@author            :郑蛘钊
 *@brief             :ksdramc2
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_SDRAMC2_H__
#define __K_SDRAMC2_H__

#include <klib.h>

#define K_TYPE_SDRAMC2	(k_sdramc2_get_type())
#define K_SDRAMC2(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KSdramc2))
#define K_IS_SDRAMC2(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_SDRAMC2))

typedef struct _KSdramc2 KSdramc2;
typedef struct _KSdramc2Private KSdramc2Private;

struct _KSdramc2
{
    KObject parent;
};

/*  structure of embnum     */
union _IoSdramcEmbnum
{
    unsigned long word;
    struct
    {
        unsigned long rnum :4;
        unsigned long :4;
        unsigned long wnum :4;
        unsigned long :4;
        unsigned long rsize :3;
        unsigned long :5;
        unsigned long wsize :3;
        unsigned long :5;
    } bit;
};

/*  structure of remapaddr      */
union _IoSdramcRemapaddr
{
    unsigned long word;
    struct
    {
        unsigned long :26;
        long remapaddr :6;
    } bit;
};

/*  structure of chsel          */
union _IoSdramcChsel
{
    unsigned long word;
    struct
    {
        unsigned long :25;
        unsigned long ch :1;
        unsigned long :6;
    } bit;
};

/*  structure of ratecont       */
union _IoSdramcRatecount
{
    unsigned long word;
    struct
    {
        unsigned long cycnum :12;
        unsigned long :4;
        unsigned long latnum :12;
        unsigned long :4;
    } bit;
};

/*  structure of masteroption       */
union _IoSdramcMasterop
{
    unsigned long word;
    struct
    {
        unsigned long enableCatR :1;
        unsigned long :3;
        unsigned long enableCatB :1;
        unsigned long :27;
    } bit;
};

/*  structure of prioritCat        */
union _IoSdramcPriorit
{
    unsigned long word;
    struct
    {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
        unsigned long prioritCatB :5;
        unsigned long :27;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
        unsigned long prioritCatB :6;
        unsigned long :26;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif  // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
    } bit;
};

/*  structure of rateChange        */
union _IoSdramcRatechg
{
    unsigned long word;
    struct
    {
        unsigned long rateChg :1;
        unsigned long :31;
    } bit;
};

/*  structure of umccmdctla     */
union _IoSdramcUmccmda
{
    unsigned long word;
    struct
    {
        unsigned long tras :7;
        unsigned long :1;
        unsigned long trp :7;
        unsigned long :1;
        unsigned long trcd :7;
        unsigned long :1;
        unsigned long trrd :7;
        unsigned long :1;
    } bit;
};

/*  structure of umccmdctlb     */
union _IoSdramcUmccmdb
{
    unsigned long word;
    struct
    {
        unsigned long tr2p :7;
        unsigned long :1;
        unsigned long tw2p :7;
        unsigned long :1;
        unsigned long tfaw :7;
        unsigned long :1;
        unsigned long trc :7;
        unsigned long :1;
    } bit;
};

/*  structure of umccmdctlc     */
union _IoSdramcUmccmdc
{
    unsigned long word;
    struct
    {
        unsigned long tccd :7;
        unsigned long :1;
        unsigned long tr2w :7;
        unsigned long :1;
        unsigned long tw2r :7;
        unsigned long :1;
        unsigned long :7;
        unsigned long :1;
    } bit;
};

/*  structure of umccmdctld     */
union _IoSdramcUmccmdd
{
    unsigned long word;
    struct
    {
        unsigned long tdrwr :7;
        unsigned long :1;
        unsigned long tdrrw :7;
        unsigned long :1;
        unsigned long tdrww :7;
        unsigned long :1;
        unsigned long tdrrr :7;
        unsigned long :1;
    } bit;
};

/*  structure of umcinitctla        */
union _IoSdramcUmcinita
{
    unsigned long word;
    struct
    {
        unsigned long ti2cke :12;
        unsigned long tcke2rst :20;
    } bit;
};

/*  structure of umcinitctlb        */
union _IoSdramcUmcinitb
{
    unsigned long word;
    struct
    {
        unsigned long trst2zqc :12;
        unsigned long :4;
        unsigned long trst2dai :16;
    } bit;
};

/*  structure of umcinitctlc        */
union _IoSdramcUmcinitc
{
    unsigned long word;
    struct
    {
        unsigned long tzqinit :12;
        unsigned long :20;
    } bit;
};

/*  structure of umcdrmmra      */
union _IoSdramcUmcdrm
{
    unsigned long word;
    struct
    {
        unsigned long mr1 :8;
        unsigned long mr2 :8;
        unsigned long mr3 :8;
        unsigned long mr10 :8;
    } bit;
};

/*  structure of umcinitset     */
union _IoSdramcUmcinitset
{
    unsigned long word;
    struct
    {
        unsigned long siniten :1;
        unsigned long sinitmd :1;
        unsigned long :6;
        unsigned long miniten :1;
        unsigned long :23;
    } bit;
};

/*  structure of umcinitstat        */
union _IoSdramcUmcinitsta
{
    unsigned long word;
    struct
    {
        unsigned long sinitst :1;
        unsigned long :7;
        unsigned long minitst :1;
        unsigned long :7;
        unsigned long :16;
    } bit;
};

/*  structure of umccmdctle     */
union _IoSdramcUmccmde
{
    unsigned long word;
    struct
    {
        unsigned long trefi :16;
        unsigned long trfc :12;
        unsigned long :4;
    } bit;
};

/*  structure of umccmdctlf     */
union _IoSdramcUmccmdf
{
    unsigned long word;
    struct
    {
        unsigned long :8;
        unsigned long txsr :12;
        unsigned long :4;
        unsigned long tckesr :8;
    } bit;
};

/*  structure of umccmdctlg     */
union _IoSdramcUmccmdg
{
    unsigned long word;
    struct
    {
        unsigned long tcpdxd :4;
        unsigned long :4;
        unsigned long tcpded :4;
        unsigned long :4;
        unsigned long txp :4;
        unsigned long :4;
        unsigned long tcke :4;
        unsigned long :4;
    } bit;
};

/*  structure of umccmdctlh     */
union _IoSdramcUmccmdh
{
    unsigned long word;
    struct
    {
        unsigned long tzqint :32;
    } bit;
};

/*  structure of umccmdctli     */
union _IoSdramcUmccmdi
{
    unsigned long word;
    struct
    {
        unsigned long tzqcs :8;
        unsigned long :8;
        unsigned long tzqcl :12;
        unsigned long :4;
    } bit;
};

/*  structure of umccmdctlj     */
union _IoSdramcUmccmdj
{
    unsigned long word;
    struct
    {
        unsigned long tmrr :4;
        unsigned long tmrw :4;
        unsigned long tmr2pd :8;
        unsigned long tpd2mr :8;
        unsigned long :8;
    } bit;
};

/*  structure of umcspcseta     */
union _IoSdramcUmcspca
{
    unsigned long word;
    struct
    {
        unsigned long arefen :1;
        unsigned long :7;
        unsigned long srinen :1;
        unsigned long srouten :1;
        unsigned long :14;
        unsigned long zqcen :1;
        unsigned long :7;
    } bit;
};

/*  structure of umcspcsetb     */
union _IoSdramcUmcspcb
{
    unsigned long word;
    struct
    {
        unsigned long arefmd :2;
        unsigned long :22;
        unsigned long zqcmd :2;
        unsigned long :6;
    } bit;
};

/*  structure of umcspcstat     */
union _IoSdramcUmcspcsta
{
    unsigned long word;
    struct
    {
        unsigned long slfrst :1;
        unsigned long :7;
        unsigned long pwdnst :1;
        unsigned long :7;
        unsigned long :16;
    } bit;
};

/*  structure of umcmemconf0a/umcmemconf1a  */
union _IoSdramcUmcmema
{
    unsigned long word;
    struct
    {
        unsigned long valid :1;
        unsigned long :7;
        unsigned long size :4;
        unsigned long :14;
        unsigned long baseaddr :6;
    } bit;
};

/*  structure of umcmemconf0b/umcmemconf1b  */
union _IoSdramcUmcmemb
{
    unsigned long word;
    struct
    {
        unsigned long col :2;
        unsigned long :2;
        unsigned long row :3;
        unsigned long :1;
        unsigned long bank :2;
        unsigned long :2;
        unsigned long dev :2;
        unsigned long :2;
        unsigned long :16;
    } bit;
};

/*  structure of umcmemconfch   */
union _IoSdramcUmcmemch
{
    unsigned long word;
    struct
    {
        unsigned long type :4;
        unsigned long :4;
        unsigned long size :4;
        unsigned long bl :3;
        unsigned long :1;
        unsigned long width :3;
        unsigned long :7;
        unsigned long baseaddr :6;
    } bit;
};

/*  structure of umcmemmapset   */
union _IoSdramcUmcmemset
{
    unsigned long word;
    struct
    {
        unsigned long bnkTyp :4;
        unsigned long :28;
    } bit;
};

/*  structure of umcaccchka/umcaccchkb/umcoodchk    */
union _IoSdramcUmcacchk
{
    unsigned long word;
    struct
    {
        unsigned long chken :1;
        unsigned long prct :1;
        unsigned long buserr :1;
        unsigned long ksint :1;
        unsigned long :28;
    } bit;
};

/*  structure of umcaccarsaa/umcaccarsab    */
union _IoSdramcUmcaccrsa
{
    unsigned long word;
    struct
    {
        unsigned long staddr :20;
        unsigned long :12;
    } bit;
};

/*  structure of umcaccareaa/umcaccareab    */
union _IoSdramcUmcaccrea
{
    unsigned long word;
    struct
    {
        unsigned long enaddr :20;
        unsigned long :12;
    } bit;
};

/*  structure of umcwaccmsta/umcwaccmstb    */
union _IoSdramcUmcwaccst
{
    unsigned long word;
    struct
    {
        unsigned long wmst :32;
    } bit;
};

/*  structure of umcraccmsta/umcraccmstb    */
union _IoSdramcUmcraccst
{
    unsigned long word;
    struct
    {
        unsigned long rmst :32;
    } bit;
};

/*  structure of umcmracs       */
union _IoSdramcUmcmracs
{
    unsigned long word;
    struct
    {
        unsigned long mrma :8;
        unsigned long reserved0 :16;
        unsigned long mrmode :4;
        unsigned long mrrank :2;
        unsigned long reserved1 :2;
    } bit;
};

/*  structure of umcmracsst     */
union _IoSdramcUmcmracsst
{
    unsigned long word;
    struct
    {
        unsigned long mrst :1;
        unsigned long :31;
    } bit;
};

/*  structure of umcmrwdt       */
union _IoSdramcUmcmrwdt
{
    unsigned long word;
    struct
    {
        unsigned long wdata :32;
    } bit;
};

/*  structure of umcmrrdt       */
union _IoSdramcUmcmrrdt
{
    unsigned long word;
    struct
    {
        unsigned long rdata :32;
    } bit;
};

/*  structure of umcrdatactlD0     */
union _IoSdramcUmcrdata0
{
    unsigned long word;
    struct
    {
        unsigned long rdyltyD0 :6;
        unsigned long :2;
        unsigned long renltyD0 :5;
        unsigned long :19;
    } bit;
};

/*  structure of umcrdatactlD1     */
union _IoSdramcUmcrdata1
{
    unsigned long word;
    struct
    {
        unsigned long rdyltyD1 :6;
        unsigned long :2;
        unsigned long renltyD1 :5;
        unsigned long :19;
    } bit;
};

/*  structure of umcwdatactlD0     */
union _IoSdramcUmcwdata0
{
    unsigned long word;
    struct
    {
        unsigned long tenltyD0 :5;
        unsigned long :3;
        unsigned long tdtltyD0 :4;
        unsigned long :20;
    } bit;
};

/*  structure of umcwdatactlD1     */
union _IoSdramcUmcwdata1
{
    unsigned long word;
    struct
    {
        unsigned long tenltyD1 :5;
        unsigned long :3;
        unsigned long tdtltyD1 :4;
        unsigned long :20;
    } bit;
};

/*  structure of umcdataset     */
union _IoSdramcUmcdataset
{
    unsigned long word;
    struct
    {
        unsigned long cenlty :4;
        unsigned long :28;
    } bit;
};

/*  structure of umcwdataswp        */
union _IoSdramcUmcwdatswp
{
    unsigned long word;
    struct
    {
        unsigned long wdataswp :1;
        unsigned long :31;
    } bit;
};

/*  structure of umcintcausem0      */
union _IoSdramcUmcintc
{
    unsigned long word;
    struct
    {
        unsigned long intcause :30;
        unsigned long reserved :2;
    } bit;
};

/*  structure of umcintmaskm0       */
union _IoSdramcUmcintmsk
{
    unsigned long word;
    struct
    {
        unsigned long intmask :30;
        unsigned long reserved :2;
    } bit;
};

/*  structure of accchkflg      */
union _IoSdramcAccchkflg
{
    unsigned long word;
    struct
    {
        unsigned long :8;
        unsigned long accchkflga :1;
        unsigned long accchkflgb :1;
        unsigned long :22;
    } bit;
};

KConstType k_sdramc2_get_type(void);
KSdramc2* k_sdramc2_new(void);

#endif/*__K_SDRAMC2_H__*/

