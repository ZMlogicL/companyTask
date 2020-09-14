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


#define K_TYPE_SDRAMC2	        (k_sdramc2_get_type())
#define K_SDRAMC2(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KSdramc2))
#define K_IS_SDRAMC2(obj)	    (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_SDRAMC2))


typedef struct _KSdramc2        KSdramc2;
typedef struct _KSdramc2Private KSdramc2Private;


struct _KSdramc2
{
    KObject parent;
};


/*  structure of embnum     */
union _IoSdramcEmbnum
{
    kulong word;
    struct
    {
        kulong rnum :4;
        kulong :4;
        kulong wnum :4;
        kulong :4;
        kulong rsize :3;
        kulong :5;
        kulong wsize :3;
        kulong :5;
    } bit;
};

/*  structure of remapaddr      */
union _IoSdramcRemapaddr
{
    kulong word;
    struct
    {
        kulong :26;
        long remapaddr :6;
    } bit;
};

/*  structure of chsel          */
union _IoSdramcChsel
{
    kulong word;
    struct
    {
        kulong :25;
        kulong ch :1;
        kulong :6;
    } bit;
};

/*  structure of ratecont       */
union _IoSdramcRatecount
{
    kulong word;
    struct
    {
        kulong cycnum :12;
        kulong :4;
        kulong latnum :12;
        kulong :4;
    } bit;
};

/*  structure of masteroption       */
union _IoSdramcMasterop
{
    kulong word;
    struct
    {
        kulong enableCatR :1;
        kulong :3;
        kulong enableCatB :1;
        kulong :27;
    } bit;
};

/*  structure of prioritCat        */
union _IoSdramcPriorit
{
    kulong word;
    struct
    {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
        kulong prioritCatB :5;
        kulong :27;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
        kulong prioritCatB :6;
        kulong :26;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif  // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
    } bit;
};

/*  structure of rateChange        */
union _IoSdramcRatechg
{
    kulong word;
    struct
    {
        kulong rateChg :1;
        kulong :31;
    } bit;
};

/*  structure of umccmdctla     */
union _IoSdramcUmccmda
{
    kulong word;
    struct
    {
        kulong tras :7;
        kulong :1;
        kulong trp :7;
        kulong :1;
        kulong trcd :7;
        kulong :1;
        kulong trrd :7;
        kulong :1;
    } bit;
};

/*  structure of umccmdctlb     */
union _IoSdramcUmccmdb
{
    kulong word;
    struct
    {
        kulong tr2p :7;
        kulong :1;
        kulong tw2p :7;
        kulong :1;
        kulong tfaw :7;
        kulong :1;
        kulong trc :7;
        kulong :1;
    } bit;
};

/*  structure of umccmdctlc     */
union _IoSdramcUmccmdc
{
    kulong word;
    struct
    {
        kulong tccd :7;
        kulong :1;
        kulong tr2w :7;
        kulong :1;
        kulong tw2r :7;
        kulong :1;
        kulong :7;
        kulong :1;
    } bit;
};

/*  structure of umccmdctld     */
union _IoSdramcUmccmdd
{
    kulong word;
    struct
    {
        kulong tdrwr :7;
        kulong :1;
        kulong tdrrw :7;
        kulong :1;
        kulong tdrww :7;
        kulong :1;
        kulong tdrrr :7;
        kulong :1;
    } bit;
};

/*  structure of umcinitctla        */
union _IoSdramcUmcinita
{
    kulong word;
    struct
    {
        kulong ti2cke :12;
        kulong tcke2rst :20;
    } bit;
};

/*  structure of umcinitctlb        */
union _IoSdramcUmcinitb
{
    kulong word;
    struct
    {
        kulong trst2zqc :12;
        kulong :4;
        kulong trst2dai :16;
    } bit;
};

/*  structure of umcinitctlc        */
union _IoSdramcUmcinitc
{
    kulong word;
    struct
    {
        kulong tzqinit :12;
        kulong :20;
    } bit;
};

/*  structure of umcdrmmra      */
union _IoSdramcUmcdrm
{
    kulong word;
    struct
    {
        kulong mr1 :8;
        kulong mr2 :8;
        kulong mr3 :8;
        kulong mr10 :8;
    } bit;
};

/*  structure of umcinitset     */
union _IoSdramcUmcinitset
{
    kulong word;
    struct
    {
        kulong siniten :1;
        kulong sinitmd :1;
        kulong :6;
        kulong miniten :1;
        kulong :23;
    } bit;
};

/*  structure of umcinitstat        */
union _IoSdramcUmcinitsta
{
    kulong word;
    struct
    {
        kulong sinitst :1;
        kulong :7;
        kulong minitst :1;
        kulong :7;
        kulong :16;
    } bit;
};

/*  structure of umccmdctle     */
union _IoSdramcUmccmde
{
    kulong word;
    struct
    {
        kulong trefi :16;
        kulong trfc :12;
        kulong :4;
    } bit;
};

/*  structure of umccmdctlf     */
union _IoSdramcUmccmdf
{
    kulong word;
    struct
    {
        kulong :8;
        kulong txsr :12;
        kulong :4;
        kulong tckesr :8;
    } bit;
};

/*  structure of umccmdctlg     */
union _IoSdramcUmccmdg
{
    kulong word;
    struct
    {
        kulong tcpdxd :4;
        kulong :4;
        kulong tcpded :4;
        kulong :4;
        kulong txp :4;
        kulong :4;
        kulong tcke :4;
        kulong :4;
    } bit;
};

/*  structure of umccmdctlh     */
union _IoSdramcUmccmdh
{
    kulong word;
    struct
    {
        kulong tzqint :32;
    } bit;
};

/*  structure of umccmdctli     */
union _IoSdramcUmccmdi
{
    kulong word;
    struct
    {
        kulong tzqcs :8;
        kulong :8;
        kulong tzqcl :12;
        kulong :4;
    } bit;
};

/*  structure of umccmdctlj     */
union _IoSdramcUmccmdj
{
    kulong word;
    struct
    {
        kulong tmrr :4;
        kulong tmrw :4;
        kulong tmr2pd :8;
        kulong tpd2mr :8;
        kulong :8;
    } bit;
};

/*  structure of umcspcseta     */
union _IoSdramcUmcspca
{
    kulong word;
    struct
    {
        kulong arefen :1;
        kulong :7;
        kulong srinen :1;
        kulong srouten :1;
        kulong :14;
        kulong zqcen :1;
        kulong :7;
    } bit;
};

/*  structure of umcspcsetb     */
union _IoSdramcUmcspcb
{
    kulong word;
    struct
    {
        kulong arefmd :2;
        kulong :22;
        kulong zqcmd :2;
        kulong :6;
    } bit;
};

/*  structure of umcspcstat     */
union _IoSdramcUmcspcsta
{
    kulong word;
    struct
    {
        kulong slfrst :1;
        kulong :7;
        kulong pwdnst :1;
        kulong :7;
        kulong :16;
    } bit;
};

/*  structure of umcmemconf0a/umcmemconf1a  */
union _IoSdramcUmcmema
{
    kulong word;
    struct
    {
        kulong valid :1;
        kulong :7;
        kulong size :4;
        kulong :14;
        kulong baseaddr :6;
    } bit;
};

/*  structure of umcmemconf0b/umcmemconf1b  */
union _IoSdramcUmcmemb
{
    kulong word;
    struct
    {
        kulong col :2;
        kulong :2;
        kulong row :3;
        kulong :1;
        kulong bank :2;
        kulong :2;
        kulong dev :2;
        kulong :2;
        kulong :16;
    } bit;
};

/*  structure of umcmemconfch   */
union _IoSdramcUmcmemch
{
    kulong word;
    struct
    {
        kulong type :4;
        kulong :4;
        kulong size :4;
        kulong bl :3;
        kulong :1;
        kulong width :3;
        kulong :7;
        kulong baseaddr :6;
    } bit;
};

/*  structure of umcmemmapset   */
union _IoSdramcUmcmemset
{
    kulong word;
    struct
    {
        kulong bnkTyp :4;
        kulong :28;
    } bit;
};

/*  structure of umcaccchka/umcaccchkb/umcoodchk    */
union _IoSdramcUmcacchk
{
    kulong word;
    struct
    {
        kulong chken :1;
        kulong prct :1;
        kulong buserr :1;
        kulong ksint :1;
        kulong :28;
    } bit;
};

/*  structure of umcaccarsaa/umcaccarsab    */
union _IoSdramcUmcaccrsa
{
    kulong word;
    struct
    {
        kulong staddr :20;
        kulong :12;
    } bit;
};

/*  structure of umcaccareaa/umcaccareab    */
union _IoSdramcUmcaccrea
{
    kulong word;
    struct
    {
        kulong enaddr :20;
        kulong :12;
    } bit;
};

/*  structure of umcwaccmsta/umcwaccmstb    */
union _IoSdramcUmcwaccst
{
    kulong word;
    struct
    {
        kulong wmst :32;
    } bit;
};

/*  structure of umcraccmsta/umcraccmstb    */
union _IoSdramcUmcraccst
{
    kulong word;
    struct
    {
        kulong rmst :32;
    } bit;
};

/*  structure of umcmracs       */
union _IoSdramcUmcmracs
{
    kulong word;
    struct
    {
        kulong mrma :8;
        kulong reserved0 :16;
        kulong mrmode :4;
        kulong mrrank :2;
        kulong reserved1 :2;
    } bit;
};

/*  structure of umcmracsst     */
union _IoSdramcUmcmracsst
{
    kulong word;
    struct
    {
        kulong mrst :1;
        kulong :31;
    } bit;
};

/*  structure of umcmrwdt       */
union _IoSdramcUmcmrwdt
{
    kulong word;
    struct
    {
        kulong wdata :32;
    } bit;
};

/*  structure of umcmrrdt       */
union _IoSdramcUmcmrrdt
{
    kulong word;
    struct
    {
        kulong rdata :32;
    } bit;
};

/*  structure of umcrdatactlD0     */
union _IoSdramcUmcrdata0
{
    kulong word;
    struct
    {
        kulong rdyltyD0 :6;
        kulong :2;
        kulong renltyD0 :5;
        kulong :19;
    } bit;
};

/*  structure of umcrdatactlD1     */
union _IoSdramcUmcrdata1
{
    kulong word;
    struct
    {
        kulong rdyltyD1 :6;
        kulong :2;
        kulong renltyD1 :5;
        kulong :19;
    } bit;
};

/*  structure of umcwdatactlD0     */
union _IoSdramcUmcwdata0
{
    kulong word;
    struct
    {
        kulong tenltyD0 :5;
        kulong :3;
        kulong tdtltyD0 :4;
        kulong :20;
    } bit;
};

/*  structure of umcwdatactlD1     */
union _IoSdramcUmcwdata1
{
    kulong word;
    struct
    {
        kulong tenltyD1 :5;
        kulong :3;
        kulong tdtltyD1 :4;
        kulong :20;
    } bit;
};

/*  structure of umcdataset     */
union _IoSdramcUmcdataset
{
    kulong word;
    struct
    {
        kulong cenlty :4;
        kulong :28;
    } bit;
};

/*  structure of umcwdataswp        */
union _IoSdramcUmcwdatswp
{
    kulong word;
    struct
    {
        kulong wdataswp :1;
        kulong :31;
    } bit;
};

/*  structure of umcintcausem0      */
union _IoSdramcUmcintc
{
    kulong word;
    struct
    {
        kulong intcause :30;
        kulong reserved :2;
    } bit;
};

/*  structure of umcintmaskm0       */
union _IoSdramcUmcintmsk
{
    kulong word;
    struct
    {
        kulong intmask :30;
        kulong reserved :2;
    } bit;
};

/*  structure of accchkflg      */
union _IoSdramcAccchkflg
{
    kulong word;
    struct
    {
        kulong :8;
        kulong accchkflga :1;
        kulong accchkflgb :1;
        kulong :22;
    } bit;
};


KConstType  k_sdramc2_get_type(void);
KSdramc2*   k_sdramc2_new(void);


#endif/*__K_SDRAMC2_H__*/
