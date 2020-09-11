/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSSHDR Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_JDSSHDR_H__
#define __K_JDSSHDR_H__

#include <klib.h>
#include "jdsshdrtbl.h"
#include "kjdsshdr2.h"
#include "kjdsshdr4.h"
#include "kjdsshdr3.h"

#define K_TYPE_JDSSHDR	(k_jdsshdr_get_type())
#define K_JDSSHDR(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsshdr))
#define K_IS_JDSSHDR(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSSHDR))

typedef struct _KJdsshdr KJdsshdr;
typedef struct _KJdsshdrPrivate KJdsshdrPrivate;

typedef struct _IoJdsshdr IoJdsshdr;

typedef union _IoShdrCh1mode IoShdrCh1mode;
typedef union _IoShdrCh2mode IoShdrCh2mode;
typedef union _IoShdrCh3mode IoShdrCh3mode;
typedef union _IoShdrCh4mode IoShdrCh4mode;
typedef union _IoShdrCh5mode IoShdrCh5mode;
typedef union _IoShdrWoutsz IoShdrWoutsz;
typedef union _IoShdrRszhcnt IoShdrRszhcnt;
typedef union _IoShdrRszvcnt IoShdrRszvcnt;
typedef union _IoShdrTrmsta IoShdrTrmsta;
typedef union _IoShdrDrcofst IoShdrDrcofst;
typedef union _IoShdrDrcgain IoShdrDrcgain;
typedef union _IoShdrDrcclph IoShdrDrcclph;
typedef union _IoShdrDrcclpl IoShdrDrcclpl;
typedef union _IoShdrMcarmd IoShdrMcarmd;
typedef union _IoShdrMcmpmd IoShdrMcmpmd;
typedef union _IoShdrMmvval IoShdrMmvval;
typedef union _IoShdrMmvrcnt IoShdrMmvrcnt;
typedef union _IoShdrMdbcnt IoShdrMdbcnt;
typedef union _IoShdrMdbrocnt IoShdrMdbrocnt;
typedef union _IoShdrMolrcnt IoShdrMolrcnt;
typedef union _IoShdrMcpcnt IoShdrMcpcnt;
typedef union _IoShdrMmcrcnt IoShdrMmcrcnt;
typedef union _IoShdrMolecnt IoShdrMolecnt;
typedef union _IoShdrMmvecnt IoShdrMmvecnt;
typedef union _IoShdrMcpxecnt IoShdrMcpxecnt;
typedef union _IoShdrMvlcnt IoShdrMvlcnt;

struct _KJdsshdr
{
    KObject parent;
};

/*  structure of ch1mode    */
union _IoShdrCh1mode
{
    unsigned long word;
    struct
    {
        unsigned long wen1 :1;
        unsigned long :3;
        unsigned long :2;
        unsigned long :2;
        unsigned long :1;
        unsigned long :1;
        unsigned long rdcmd1 :2;
        unsigned long :1;
        unsigned long :3;
        unsigned long :1;
        unsigned long :3;
        unsigned long cssmd1 :2;
        unsigned long :10;
    } bit;
};

/*  structure of ch2mode    */
union _IoShdrCh2mode
{
    unsigned long word;
    struct
    {
        unsigned long wen2 :1;
        unsigned long :3;
        unsigned long rszmd2 :2;
        unsigned long :2;
        unsigned long rdcen2 :1;
        unsigned long :1;
        unsigned long rdcmd2 :2;
        unsigned long trmen2 :1;
        unsigned long :3;
        unsigned long drcen2 :1;
        unsigned long :3;
        unsigned long cssmd2 :2;
        unsigned long :10;
    } bit;
};

/*  structure of ch3mode    */
union _IoShdrCh3mode
{
    unsigned long word;
    struct
    {
        unsigned long wen3 :1;
        unsigned long :3;
        unsigned long rszmd3 :2;
        unsigned long :2;
        unsigned long rdcen3 :1;
        unsigned long :1;
        unsigned long rdcmd3 :2;
        unsigned long trmen3 :1;
        unsigned long :3;
        unsigned long drcen3 :1;
        unsigned long :3;
        unsigned long cssmd3 :2;
        unsigned long :10;
    } bit;
};

/*  structure of ch4mode    */
union _IoShdrCh4mode
{
    unsigned long word;
    struct
    {
        unsigned long wen4 :1;
        unsigned long :3;
        unsigned long rszmd4 :2;
        unsigned long :2;
        unsigned long rdcen4 :1;
        unsigned long :1;
        unsigned long rdcmd4 :2;
        unsigned long trmen4 :1;
        unsigned long :3;
        unsigned long :1;
        unsigned long :3;
        unsigned long cssmd4 :2;
        unsigned long :10;
    } bit;
};

/*  structure of ch5mode    */
union _IoShdrCh5mode
{
    unsigned long word;
    struct
    {
        unsigned long wen5 :1;
        unsigned long :3;
        unsigned long rszmd5 :2;
        unsigned long :2;
        unsigned long rdcen5 :1;
        unsigned long :1;
        unsigned long rdcmd5 :2;
        unsigned long trmen5 :1;
        unsigned long :3;
        unsigned long :1;
        unsigned long :3;
        unsigned long cssmd5 :2;
        unsigned long :10;
    } bit;
};

/*  structure of woutsz     */
union _IoShdrWoutsz
{
    unsigned long word[6];
    struct
    {
        unsigned long wouthsz0 :14;
        unsigned long :2;
        unsigned long woutvsz0 :14;
        unsigned long :2;
        unsigned long wouthsz1 :14;
        unsigned long :2;
        unsigned long woutvsz1 :14;
        unsigned long :2;
        unsigned long wouthsz2 :14;
        unsigned long :2;
        unsigned long woutvsz2 :14;
        unsigned long :2;
        unsigned long wouthsz3 :14;
        unsigned long :2;
        unsigned long woutvsz3 :14;
        unsigned long :2;
        unsigned long wouthsz4 :14;
        unsigned long :2;
        unsigned long woutvsz4 :14;
        unsigned long :2;
        unsigned long wouthsz5 :14;
        unsigned long :2;
        unsigned long woutvsz5 :14;
        unsigned long :2;
    } bit;
};

/*  structure of rszhcnt2/3/4/5    */
union _IoShdrRszhcnt
{
    unsigned long word;
    struct
    {
        unsigned long rszhsta :14;
        unsigned long :2;
        unsigned long rszhpit :15;
        unsigned long :1;
    } bit;
};

/*  structure of rszvcnt2/3/4/5    */
union _IoShdrRszvcnt
{
    unsigned long word;
    struct
    {
        unsigned long rszvsta :14;
        unsigned long :2;
        unsigned long rszvpit :15;
        unsigned long :1;
    } bit;
};

/*  structure of trmsta2/3/4/5     */
union _IoShdrTrmsta
{
    unsigned long word;
    struct
    {
        unsigned long trmhsta :14;
        unsigned long :2;
        unsigned long trmvsta :14;
        unsigned long :2;
    } bit;
};

/*  structure of drcofst0/2/3      */
union _IoShdrDrcofst
{
    unsigned long word;
    struct
    {
        unsigned long drcyofst :5;
        unsigned long :3;
        unsigned long :8;
        long drccbofst :5;
        unsigned long :3;
        long drccrofst :5;
        unsigned long :3;
    } bit;
};

/*  structure of drcgain0/2/3  */
union _IoShdrDrcgain
{
    unsigned long word;
    struct
    {
        unsigned long drcygain :9;
        unsigned long :7;
        unsigned long drccbgain :8;
        unsigned long drccrgain :8;
    } bit;
};

/*  structure of drcclph0/2/3  */
union _IoShdrDrcclph
{
    unsigned long word;
    struct
    {
        unsigned long drcyclph :8;
        unsigned long :8;
        long drccbclph :8;
        long drccrclph :8;
    } bit;
};

/*  structure of drcclpl0/2/3  */
union _IoShdrDrcclpl
{
    unsigned long word;
    struct
    {
        unsigned long drcyclpl :8;
        unsigned long :8;
        long drccbclpl :8;
        long drccrclpl :8;
    } bit;
};

/*  structure of mcarmd     */
union _IoShdrMcarmd
{
    unsigned long word;
    struct
    {
        unsigned long mcamd :2;
        unsigned long :2;
        unsigned long :4;
        unsigned long mcrmd :2;
        unsigned long :22;
    } bit;
};

/*  structure of mcmpmd     */
union _IoShdrMcmpmd
{
    unsigned long word;
    struct
    {
        unsigned long mcmpmd :1;
        unsigned long :3;
        unsigned long :4;
        unsigned long mvwen :1;
        unsigned long :23;
    } bit;
};

/*  structure of mmvval     */
union _IoShdrMmvval
{
    unsigned long word;
    struct
    {
        unsigned long mmvx :7;
        unsigned long :1;
        unsigned long :8;
        unsigned long mmvy :7;
        unsigned long :9;
    } bit;
};

/*  structure of mmvrcnt    */
union _IoShdrMmvrcnt
{
    unsigned long word;
    struct
    {
        unsigned long mmvrox :5;
        unsigned long :3;
        unsigned long mmvroy :5;
        unsigned long :3;
        unsigned long mmvrkx :3;
        unsigned long :1;
        unsigned long :4;
        unsigned long mmvrky :3;
        unsigned long :5;
    } bit;
};

/*  structure of mdbcnt     */
union _IoShdrMdbcnt
{
    unsigned long word;
    struct
    {
        unsigned long mdbx :3;
        unsigned long :5;
        unsigned long :8;
        unsigned long mdby :3;
        unsigned long :13;
    } bit;
};

/*  structure of mdbrocnt   */
union _IoShdrMdbrocnt
{
    unsigned long word;
    struct
    {
        unsigned long mdbrox :5;
        unsigned long :3;
        unsigned long mdbroy :5;
        unsigned long :3;
        unsigned long mdbrkx :3;
        unsigned long :1;
        unsigned long :4;
        unsigned long mdbrky :3;
        unsigned long :5;
    } bit;
};

/*  structure of molrcnt    */
union _IoShdrMolrcnt
{
    unsigned long word;
    struct
    {
        unsigned long molrsm :4;
        unsigned long :1;
        unsigned long :3;
        unsigned long molrss :4;
        unsigned long :1;
        unsigned long :3;
        unsigned long molro :5;
        unsigned long :3;
        unsigned long molrk :2;
        unsigned long :6;
    } bit;
};

/*  structure of mcpcnt     */
union _IoShdrMcpcnt
{
    unsigned long word;
    struct
    {
        unsigned long mcpxs :8;
        unsigned long mcpxo :5;
        unsigned long :3;
        unsigned long mcpxk :3;
        unsigned long :13;
    } bit;
};

/*  structure of mmcrcnt    */
union _IoShdrMmcrcnt
{
    unsigned long word;
    struct
    {
        unsigned long mmcrs :10;
        unsigned long :2;
        unsigned long mmcrk :3;
        unsigned long :17;
    } bit;
};

/*  structure of molecnt    */
union _IoShdrMolecnt
{
    unsigned long word;
    struct
    {
        unsigned long moles :10;
        unsigned long :6;
        unsigned long moleo :5;
        unsigned long :3;
        unsigned long molek :3;
        unsigned long :5;
    } bit;
};

/*  structure of mmvecnt    */
union _IoShdrMmvecnt
{
    unsigned long word;
    struct
    {
        unsigned long mmves :10;
        unsigned long :6;
        unsigned long mmveo :5;
        unsigned long :3;
        unsigned long mmvek :3;
        unsigned long :5;
    } bit;
};

/*  structure of mcpxecnt   */
union _IoShdrMcpxecnt
{
    unsigned long word;
    struct
    {
        unsigned long mcpxes :10;
        unsigned long :6;
        unsigned long mcpxeo :5;
        unsigned long :3;
        unsigned long mcpxek :3;
        unsigned long :5;
    } bit;
};

/*  structure of mvlcnt     */
union _IoShdrMvlcnt
{
    unsigned long word;
    struct
    {
        unsigned long mvlen :1;
        unsigned long :7;
        unsigned long mvlth :7;
        unsigned long :1;
        unsigned long mvlcth :7;
        unsigned long :9;
    } bit;
};

/* Define i/o mapping */
struct _IoJdsshdr
{
    /* JDSIMG */
    IoShdrShdractl0 shdractl0; /* (0000 - 0003h) */
    IoShdrShdractl1 shdractl1; /* (0004 - 0007h) */
    IoShdrShdractl2 shdractl2; /* (0008 - 000Bh) */

    unsigned char dmyA00cA01f[0xA020 - 0xA00C]; /* (000C - 001Fh) */

    IoShdrShdrint0 shdrint0; /* (0020 - 0023h) */
    IoShdrShdrint1 shdrint1; /* (0024 - 0027h) */

    unsigned char dmyA028A07f[0xA080 - 0xA028]; /* (0028 - 007Fh) */

    IoShdrAxmd axmd; /* (0080 - 0083h) */
    IoShdrAxictlara axictlara; /* (0084 - 0087h) */
    IoShdrAxictlarb axictlarb; /* (0088 - 008Bh) */
    IoShdrAxictlarc axictlarc; /* (008C - 008Fh) */
    IoShdrAxictlard axictlard; /* (0090 - 0093h) */
    IoShdrAxictlawa axictlawa; /* (0094 - 0097h) */
    IoShdrAxictlawb axictlawb; /* (0098 - 009Fh) */
    IoShdrAxictlawc axictlawc; /* (00A0 - 00A7h) */
    IoShdrAxictlra axictlra; /* (00A8 - 00ABh) */
    IoShdrAxictlrb axictlrb; /* (00AC - 00AFh) */
    IoShdrAxictlrc axictlrc; /* (00B0 - 00B3h) */
    IoShdrAxictlrd axictlrd; /* (00B4 - 00B7h) */
    IoShdrAxictlwa axictlwa; /* (00B8 - 00BBh) */

    unsigned char dmyA0bcA0bf[0xA0C0 - 0xA0BC]; /* (00BC - 00BFh) */

    IoShdrAxictlwb axictlwb; /* (00C0 - 00C7h) */
    IoShdrAxictlwc axictlwc; /* (00C8 - 00CFh) */
    IoShdrCoremon0 coremon0; /* (00D0 - 00D3h) */
    IoShdrCoremon1 coremon1; /* (00D4 - 00D7h) */
    IoShdrDgtRsel dgtRsel; /* (00D8 - 00DBh) */

    unsigned char dmyA0dcA0ff[0xA100 - 0xA0DC]; /* (00DC - 00FFh) */

    IoShdrSdrrAddrA sdrrAddrA; /* (0100 - 0107h) */
    IoShdrSdrrAddrB sdrrAddrB; /* (0108 - 010Fh) */
    IoShdrSdrrAddrC sdrrAddrC; /* (0110 - 0117h) */
    IoShdrSdrrAddrD sdrrAddrD; /* (0118 - 011Fh) */
    IoShdrSdrrAddrE sdrrAddrE; /* (0120 - 0127h) */
    IoShdrSdrrAddrF sdrrAddrF; /* (0128 - 012Bh) */

    unsigned char dmyA12cA12f[0xA130 - 0xA12C]; /* (012C - 012Fh) */

    IoShdrSdrrGhsizeA sdrrGhsizeA; /* (0130 - 0137h) */
    IoShdrSdrrGhsizeB sdrrGhsizeB; /* (0138 - 013Fh) */
    IoShdrSdrrGhsizeC sdrrGhsizeC; /* (0140 - 0147h) */
    IoShdrSdrrGhsizeD sdrrGhsizeD; /* (0148 - 014Fh) */
    IoShdrSdrrGhsizeE sdrrGhsizeE; /* (0150 - 0157h) */
    IoShdrSdrrGhsizeF sdrrGhsizeF; /* (0158 - 015Bh) */

    unsigned char dmyA15cA15f[0xA160 - 0xA15C]; /* (015C - 015Fh) */

    IoShdrSdrrVfm sdrrVfm; /* (0160 - 0163h) */

    unsigned char dmyA164A16f[0xA170 - 0xA164]; /* (0164 - 016Fh) */

    IoShdrSdrwAddrB sdrwAddrB; /* (0170 - 0177h) */
    IoShdrSdrwAddrE sdrwAddrE; /* (0178 - 017Fh) */
    IoShdrSdrwAddrF sdrwAddrF; /* (0180 - 0187h) */
    IoShdrSdrwAddrG sdrwAddrG; /* (0188 - 0193h) */
    IoShdrSdrwAddrH sdrwAddrH; /* (0194 - 019Bh) */
    IoShdrSdrwAddrI sdrwAddrI; /* (019C - 019Fh) */

    IoShdrSdrwGhsizeB sdrwGhsizeB; /* (01A0 - 01A7h) */
    IoShdrSdrwGhsizeE sdrwGhsizeE; /* (01A8 - 01AFh) */
    IoShdrSdrwGhsizeF sdrwGhsizeF; /* (01B0 - 01B7h) */
    IoShdrSdrwGhsizeG sdrwGhsizeG; /* (01B8 - 01C3h) */
    IoShdrSdrwGhsizeH sdrwGhsizeH; /* (01C4 - 01CBh) */
    IoShdrSdrwGhsizeI sdrwGhsizeI; /* (01CC - 01CFh) */

    IoShdrSdrwVfm sdrwVfm; /* (01D0 - 01D3h) */

    unsigned char dmyA1d4A1d7[0xA1D8 - 0xA1D4]; /* (01D4 - 01D7h) */

    IoShdrSdrwBaA sdrwBaA; /* (01D8 - 01DFh) */
    IoShdrSdrwBaC sdrwBaC; /* (01E0 - 01E7h) */
    IoShdrSdrwBaD sdrwBaD; /* (01E8 - 01EFh) */
    IoShdrSdrwFwA sdrwFwA; /* (01F0 - 01F3h) */
    IoShdrSdrwFwC sdrwFwC; /* (01F4 - 01F7h) */
    IoShdrSdrwFwD sdrwFwD; /* (01F8 - 01FBh) */

    unsigned char dmyA1fcA1ff[0xA200 - 0xA1FC]; /* (01FC - 01FFh) */

    IoShdrShdrifrm shdrifrm; /* (0200 - 0203h) */
    IoShdrShdrofrm shdrofrm; /* (0204 - 0207h) */

    unsigned char dmyA208A20f[0xA210 - 0xA208]; /* (0208 - 020Fh) */

    IoShdrSdrrHsizeA sdrrHsizeA; /* (0210 - 0213h) */
    IoShdrSdrrHsizeB sdrrHsizeB; /* (0214 - 0217h) */
    IoShdrSdrrHsizeC sdrrHsizeC; /* (0218 - 021Bh) */
    IoShdrSdrrHsizeD sdrrHsizeD; /* (021C - 021Fh) */
    IoShdrSdrrHsizeE sdrrHsizeE; /* (0220 - 0223h) */

    unsigned char dmyA224A22f[0xA230 - 0xA224]; /* (0224 - 022Fh) */

    IoShdrSdrrVsizeA sdrrVsizeA; /* (0230 - 0233h) */
    IoShdrSdrrVsizeB sdrrVsizeB; /* (0234 - 0237h) */
    IoShdrSdrrVsizeC sdrrVsizeC; /* (0238 - 023Bh) */
    IoShdrSdrrVsizeD sdrrVsizeD; /* (023C - 023Fh) */
    IoShdrSdrrVsizeE sdrrVsizeE; /* (0240 - 0243h) */

    unsigned char dmyA244A24f[0xA250 - 0xA244]; /* (0244 - 024Fh) */

    IoShdrExmag exmag; /* (0250 - 0253h) */
    IoShdrRemval remval; /* (0254 - 0257h) */

    unsigned char dmyA258A25f[0xA260 - 0xA258]; /* (0258 - 025Fh) */

    IoShdrShift shift; /* (0260 - 0263h) */
    IoShdrMrgn mrgn; /* (0264 - 0267h) */

    unsigned char dmyA268A26f[0xA270 - 0xA268]; /* (0268 - 026Fh) */

    IoShdrFlwcnt flwcnt; /* (0270 - 0273h) */
    IoShdrTmode tmode; /* (0274 - 0277h) */

    unsigned char dmyA278A2ff[0xA300 - 0xA278]; /* (0278 - 02FFh) */

    /* COMPIP   */
    IoShdrModesel modesel; /* (0300 - 0303h) */
    IoShdrMcmodesel mcModesel; /* (0304 - 0307h) */
    IoShdrCompincfmsel compIncfmsel; /* (0308 - 030Bh) */
    IoShdrBypasson bypasson; /* (030C - 030Fh) */
    IoShdrAxisize axisize; /* (0310 - 0313h) */
    IoShdrLint lint; /* (0314 - 031Fh) */
    IoShdrWrstartaddr wrstartaddr; /* (0320 - 0327h) */
    IoShdrRdstartaddr rdstartaddr; /* (0328 - 032Fh) */

    unsigned char dmyA330A3ff[0xA400 - 0xA330]; /* (0330 - 03FFh) */

    IoShdrPremd premd; /* (0400 - 0403h) */

    unsigned char dmyA404A41f[0xA420 - 0xA404]; /* (0404 - 041Fh) */

    IoShdrY2rcoef y2rcoef; /* (0420 - 0433h) */

    unsigned char dmyA434A43f[0xA440 - 0xA434]; /* (0434 - 043Fh) */

    IoShdrPrey2rclpul0 prey2rclpul0; /* (0440 - 0447h) */
    IoShdrPrey2rclpll0 prey2rclpll0; /* (0448 - 044Fh) */
    unsigned char dmyA450A45f[0xA460 - 0xA450]; /* (0450 - 0457h) */
    /* (0458 - 045Fh) */
    IoShdrPrey2rclpus prey2rclpus; /* (0460 - 0467h) */
    IoShdrPrey2rclpls prey2rclpls; /* (0468 - 046Fh) */

    unsigned char dmyA470A47f[0xA480 - 0xA470]; /* (0470 - 047Fh) */

    IoShdrR2ycoef r2ycoef; /* (0480 - 0493h) */

    unsigned char dmyA494A49f[0xA4A0 - 0xA494]; /* (0494 - 049Fh) */

    IoShdrPrer2yclpul prer2yclpul; /* (04A0 - 04ABh) */

    unsigned char dmyA4acA4af[0xA4B0 - 0xA4AC]; /* (04AC - 04AFh) */

    IoShdrPrer2yclpll prer2yclpll; /* (04B0 - 04BBh) */

    unsigned char dmyA4bcA4bf[0xA4C0 - 0xA4BC]; /* (04BC - 04BFh) */

    IoShdrPrer2yclpus prer2yclpus; /* (04C0 - 04C7h) */
    IoShdrPrer2yclpls prer2yclpls; /* (04C8 - 04CFh) */

    unsigned char dmyA4d0A4f3[0xA4F4 - 0xA4D0]; /* (04D0 - 04DFh) */

    /* (04E0 - 04F3h) */

    unsigned char dmyA4f4A513[0xA514 - 0xA4F4]; /* (04F4 - 04FFh) */

    /* (0500 - 0513h) */

    unsigned char dmyA514A51f[0xA520 - 0xA514]; /* (0514 - 051Fh) */

    IoShdrSknofs sknofs; /* (0520 - 052Bh) */

    unsigned char dmyA52cA52f[0xA530 - 0xA52C]; /* (052C - 052Fh) */

    IoShdrSknsl sknsl; /* (0530 - 053Bh) */

    unsigned char dmyA53cA543[0xA544 - 0xA53C]; /* (053C - 0543h) */

    IoShdrSknb sknb1; /* (0544 - 0547h) */
    IoShdrSknb sknb2; /* (0548 - 054Bh) */

    unsigned char dmyA54cA54f[0xA550 - 0xA54C]; /* (054C - 054Fh) */

    IoShdrLknofs lknofs; /* (0550 - 055Bh) */

    unsigned char dmyA55cA55f[0xA560 - 0xA55C]; /* (055C - 055Fh) */

    IoShdrLknsl lknsl; /* (0560 - 056Bh) */

    unsigned char dmyA56cA573[0xA574 - 0xA56C]; /* (056C - 0573h) */

    IoShdrLknb lknb1; /* (0574 - 0577h) */
    IoShdrLknb lknb2; /* (0578 - 057Bh) */

    unsigned char dmyA57cA5ff[0xA600 - 0xA57C]; /* (057C - 05FFh) */

    IoShdrEpbd epbd; /* (0600 - 0607h) */
    IoShdrEpof epof; /* (0608 - 060Fh) */
    IoShdrEpbld epbld; /* (0610 - 0613h) */
    IoShdrFdweight fdweight; /* (0614 - 0617h) */
    IoShdrMvcnt mvcnt; /* (0618 - 061Bh) */

    unsigned char dmyA61cA61f[0xA620 - 0xA61C]; /* (061C - 061Fh) */

    IoShdrBldrofs bldrofs; /* (0620 - 062Bh) */

    unsigned char dmyA62cA62f[0xA630 - 0xA62C]; /* (062C - 062Fh) */

    IoShdrBldrsl bldrsl; /* (0630 - 063Bh) */

    unsigned char dmyA63cA63f[0xA640 - 0xA63C]; /* (063C - 063Fh) */

    IoShdrBldrb bldrb; /* (0640 - 064Bh) */

    unsigned char dmyA64cA64f[0xA650 - 0xA64C]; /* (064C - 064Fh) */

    IoShdrWghtr2ycoef wghtr2ycoef; /* (0650 - 0657h) */
    IoShdrWghtr2yclp wghtr2yclp; /* (0658 - 065Bh) */

    unsigned char dmyA65cA65f[0xA660 - 0xA65C]; /* (065C - 065Fh) */

    IoShdrWghtbase wghtbase; /* (0660 - 0663h) */

    unsigned char dmyA664A66f[0xA670 - 0xA664]; /* (0664 - 066Fh) */

    IoShdrWghtrofs wghtrofs; /* (0670 - 067Bh) */

    unsigned char dmyA67cA67f[0xA680 - 0xA67C]; /* (067C - 067Fh) */

    IoShdrWghtgofs wghtgofs; /* (0680 - 068Bh) */

    unsigned char dmyA68cA68f[0xA690 - 0xA68C]; /* (068C - 068Fh) */

    IoShdrWghtbofs wghtbofs; /* (0690 - 069Bh) */

    unsigned char dmyA69cA69f[0xA6A0 - 0xA69C]; /* (069C - 069Fh) */

    IoShdrWghtrsl wghtrsl; /* (06A0 - 06ABh) */

    unsigned char dmyA6acA6af[0xA6B0 - 0xA6AC]; /* (06AC - 06AFh) */

    IoShdrWghtgsl wghtgsl; /* (06B0 - 06BBh) */

    unsigned char dmyA6bcA6bf[0xA6C0 - 0xA6BC]; /* (06BC - 06BFh) */

    IoShdrWghtbsl wghtbsl; /* (06C0 - 06CBh) */

    unsigned char dmyA6ccA6cf[0xA6D0 - 0xA6CC]; /* (06CC - 06CFh) */

    IoShdrWghtrb wghtrb; /* (06D0 - 06DBh) */

    unsigned char dmyA6dcA6df[0xA6E0 - 0xA6DC]; /* (06DC - 06DFh) */

    IoShdrWghtgb wghtgb; /* (06E0 - 06EBh) */

    unsigned char dmyA6ecA6ef[0xA6F0 - 0xA6EC]; /* (06EC - 06EFh) */

    IoShdrWghtbb wghtbb; /* (06F0 - 06FBh) */

    unsigned char dmyA6fcA6ff[0xA700 - 0xA6FC]; /* (06FC - 06FFh) */

    IoShdrIsoth isoth; /* (0700 - 0703h) */
    IoShdrIsocoef isocoef; /* (0704 - 0707h) */
    IoShdrSatth satth; /* (0708 - 070Bh) */

    unsigned char dmyA70cA713[0xA714 - 0xA70C]; /* (070C - 070Fh) */

    /* (0710 - 0713h) */

    unsigned char dmyA714A723[0xA724 - 0xA714]; /* (0714 - 0717h) */

    /* (0718 - 071Fh) */
    /* (0720 - 0723h) */
    IoShdrExp77md exp77md; /* (0724 - 0727h) */
    IoShdrFmdsel fmdsel; /* (0728 - 072Bh) */

    unsigned char dmyA72cA7ff[0xA800 - 0xA72C]; /* (072C - 07FFh) */

    IoShdrTlut TLUT; /* (0800 - 0813h) */

    unsigned char dmyA814A81f[0xA820 - 0xA814]; /* (0814 - 081Fh) */

    IoShdrPmskmd pmskmd; /* (0820 - 0823h) */

    unsigned char dmyA824A83f[0xA840 - 0xA824]; /* (0824 - 083Fh) */

    IoShdrSpnren spnren; /* (0840 - 0843h) */
    IoShdrSpebd spebd; /* (0844 - 084Bh) */

    unsigned char dmyA84cA84f[0xA850 - 0xA84C]; /* (084C - 084Fh) */

    IoShdrSpeof speof; /* (0850 - 0857h) */
    IoShdrSpebld spebld; /* (0858 - 085Bh) */

    unsigned char dmyA85cA8ff[0xA900 - 0xA85C]; /* (085C - 08FFh) */

    IoShdrMsky2rclpul msky2rclpul; /* (0900 - 0907h) */
    IoShdrMsky2rclpll msky2rclpll; /* (0908 - 090Fh) */
    IoShdrMsky2rclpus msky2rclpus; /* (0910 - 0917h) */
    IoShdrMsky2rclpls msky2rclpls; /* (0918 - 091Fh) */
    IoShdrAlpha alpha; /* (0920 - 0923h) */

    unsigned char dmyA924A93f[0xA940 - 0xA924]; /* (0924 - 093Fh) */

    IoShdrLpfc lpfc; /* (0940 - 0953h) */

    unsigned char dmyA954A963[0xA964 - 0xA954]; /* (0954 - 095Fh) */

    /* (0960 - 0963h) */

    unsigned char dmyA964A96f[0xA970 - 0xA964]; /* (0964 - 096Fh) */

    IoShdrBldofs bldofs; /* (0970 - 097Fh) */
    IoShdrBldsl bldsl; /* (0980 - 099Bh) */

    unsigned char dmyA99cA99f[0xA9A0 - 0xA99C]; /* (099C - 099Fh) */

    IoShdrBldb bldb; /* (09A0 - 09AFh) */
    IoShdrNormgain normgain; /* (09B0 - 09B7h) */
    IoShdrNormofs normofs; /* (09B8 - 09BFh) */
    IoShdrMskmd mskmd; /* (09C0 - 09C3h) */

    unsigned char dmyA9c4A9ff[0xAA00 - 0xA9C4]; /* (09C4 - 09FFh) */

    IoShdrBldsel bldsel; /* (0A00 - 0A03h) */

    unsigned char dmyAa04Aa0f[0xAA10 - 0xAA04]; /* (0A04 - 0A0Fh) */

    IoShdrAlphasel alphasel; /* (0A10 - 0A13h) */

    unsigned char dmyAa14Aa1f[0xAA20 - 0xAA14]; /* (0A14 - 0A1Fh) */

    IoShdrAlphaval alphaval; /* (0A20 - 0A27h) */

    unsigned char dmyAa28Aa33[0xAA34 - 0xAA28]; /* (0A28 - 0A2Fh) */

    /* (0A30 - 0A33h) */

    unsigned char dmyAa34Aaff[0xAB00 - 0xAA34]; /* (0A34 - 0AFFh) */

    IoShdrPostsft1rnd postsft1rnd; /* (0B00 - 0B03h) */

    unsigned char dmyAb04Ab1f[0xAB20 - 0xAB04]; /* (0B04 - 0B1Fh) */

    IoShdrPosty2rcoef posty2rcoef; /* (0B20 - 0B33h) */

    unsigned char dmyAb34Ab3f[0xAB40 - 0xAB34]; /* (0B34 - 0B3Fh) */

    IoShdrPosty2rclpthu posty2rclpthu; /* (0B40 - 0B47h) */
    IoShdrPosty2rclpthl posty2rclpthl; /* (0B48 - 0B4Fh) */
    IoShdrPostsel1 postsel1; /* (0B50 - 0B53h) */
    IoShdrPostmulqpos postmulqpos; /* (0B54 - 0B57h) */

    unsigned char dmyAb58Ab5f[0xAB60 - 0xAB58]; /* (0B58 - 0B5Fh) */

    IoShdrEvknb evknb; /* (0B60 - 0B73h) */

    unsigned char dmyAb74Ab7f[0xAB80 - 0xAB74]; /* (0B74 - 0B7Fh) */

    IoShdrEvknofs evknofs; /* (0B80 - 0B93h) */

    unsigned char dmyAb94Ab9f[0xABA0 - 0xAB94]; /* (0B94 - 0B9Fh) */

    IoShdrEvknsl evknsl; /* (0BA0 - 0BB3h) */

    unsigned char dmyAbb4Abbf[0xABC0 - 0xABB4]; /* (0BB4 - 0BBFh) */

    IoShdrPostsel0 postsel0; /* (0BC0 - 0BC3h) */
    IoShdrHdrcssmd hdrcssmd; /* (0BC4 - 0BC7h) */

    unsigned char dmyAbc8Abff[0xAC00 - 0xABC8]; /* (0BC8 - 0BFFh) */

    IoShdrCh0mode ch0mode; /* (0C00 - 0C03h) */
    IoShdrCh1mode ch1mode; /* (0C04 - 0C07h) */
    IoShdrCh2mode ch2mode; /* (0C08 - 0C0Bh) */
    IoShdrCh3mode ch3mode; /* (0C0C - 0C0Fh) */
    IoShdrCh4mode ch4mode; /* (0C10 - 0C13h) */
    IoShdrCh5mode ch5mode; /* (0C14 - 0C17h) */

    unsigned char dmyAc18Ac1f[0xAC20 - 0xAC18]; /* (0C18 - 0C1Fh) */

    IoShdrWoutsz woutsz; /* (0C20 - 0C37h) */

    unsigned char dmyAc38Ac47[0xAC48 - 0xAC38]; /* (0C38 - 0C47h) */

    IoShdrRszhcnt rszhcnt2; /* (0C48 - 0C4Bh) */
    IoShdrRszhcnt rszhcnt3; /* (0C4C - 0C4Fh) */
    IoShdrRszhcnt rszhcnt4; /* (0C50 - 0C53h) */
    IoShdrRszhcnt rszhcnt5; /* (0C54 - 0C57h) */

    unsigned char dmyAc58Ac67[0xAC68 - 0xAC58]; /* (0C58 - 0C67h) */

    IoShdrRszvcnt rszvcnt2; /* (0C68 - 0C6Bh) */
    IoShdrRszvcnt rszvcnt3; /* (0C6C - 0C6Fh) */
    IoShdrRszvcnt rszvcnt4; /* (0C70 - 0C73h) */
    IoShdrRszvcnt rszvcnt5; /* (0C74 - 0C77h) */

    unsigned char dmyAc78Ac87[0xAC88 - 0xAC78]; /* (0C78 - 0C87h) */

    IoShdrTrmsta trmsta2; /* (0C88 - 0C8Bh) */
    IoShdrTrmsta trmsta3; /* (0C8C - 0C8Fh) */
    IoShdrTrmsta trmsta4; /* (0C90 - 0C93h) */
    IoShdrTrmsta trmsta5; /* (0C94 - 0C97h) */

    unsigned char dmyAc98Ac9f[0xACA0 - 0xAC98]; /* (0C98 - 0C9Fh) */

    IoShdrDrcofst drcofst0; /* (0CA0 - 0CA3h) */

    unsigned char dmyAca4Aca7[0xACA8 - 0xACA4]; /* (0CA4 - 0CA7h) */

    IoShdrDrcofst drcofst2; /* (0CA8 - 0CABh) */
    IoShdrDrcofst drcofst3; /* (0CAC - 0CAFh) */
    IoShdrDrcgain drcgain0; /* (0CB0 - 0CB3h) */

    unsigned char dmyAcb4Acb7[0xACB8 - 0xACB4]; /* (0CB4 - 0CB7h) */

    IoShdrDrcgain drcgain2; /* (0CB8 - 0CBBh) */
    IoShdrDrcgain drcgain3; /* (0CBC - 0CBFh) */
    IoShdrDrcclph drcclph0; /* (0CC0 - 0CC3h) */

    unsigned char dmyAcc4Acc7[0xACC8 - 0xACC4]; /* (0CC4 - 0CC7h) */

    IoShdrDrcclph drcclph2; /* (0CC8 - 0CCBh) */
    IoShdrDrcclph drcclph3; /* (0CCC - 0CCFh) */
    IoShdrDrcclpl drcclpl0; /* (0CD0 - 0CD3h) */

    unsigned char dmy_ACD4_ACD7[0xACD8 - 0xACD4]; /* (0CD4 - 0CD7h) */

    IoShdrDrcclpl drcclpl2; /* (0CD8 - 0CDBh) */
    IoShdrDrcclpl drcclpl3; /* (0CDC - 0CDFh) */

    unsigned char dmyAce0Acff[0xAD00 - 0xACE0]; /* (0CE0 - 0CFFh) */

    IoShdrMcarmd mcarmd; /* (0D00 - 0D03h) */
    IoShdrMcmpmd mcmpmd; /* (0D04 - 0D07h) */

    unsigned char dmyAd08Ad0f[0xAD10 - 0xAD08]; /* (0D08 - 0D0Fh) */

    IoShdrMmvval mmvval; /* (0D10 - 0D13h) */
    IoShdrMmvrcnt mmvrcnt; /* (0D14 - 0D17h) */
    IoShdrMdbcnt mdbcnt; /* (0D18 - 0D1Bh) */
    IoShdrMdbrocnt mdbrocnt; /* (0D1C - 0D1Fh) */
    IoShdrMolrcnt molrcnt; /* (0D20 - 0D23h) */

    unsigned char dmyAd24Ad27[0xAD28 - 0xAD24]; /* (0D24 - 0D27h) */

    IoShdrMcpcnt mcpcnt; /* (0D28 - 0D2Bh) */

    unsigned char dmyAd2cAd2f[0xAD30 - 0xAD2C]; /* (0D2C - 0D2Fh) */

    IoShdrMmcrcnt mmcrcnt; /* (0D30 - 0D33h) */

    unsigned char dmyAd34Ad37[0xAD38 - 0xAD34]; /* (0D34 - 0D37h) */

    IoShdrMolecnt molecnt; /* (0D38 - 0D3Bh) */
    IoShdrMmvecnt mmvecnt; /* (0D3C - 0D3Fh) */
    IoShdrMcpxecnt mcpxecnt; /* (0D40 - 0D43h) */

    unsigned char dmyAd44Ad47[0xAD48 - 0xAD44]; /* (0D44 - 0D47h) */

    IoShdrMvlcnt mvlcnt; /* (0D48 - 0D4Bh) */

    unsigned char dmyAd4cAfff[0xB000 - 0xAD4C]; /* (0D4C - 0FFFh) */
};

extern volatile IoJdsshdr ioShdr;

KConstType k_jdsshdr_get_type(void);
KJdsshdr* k_jdsshdr_new(void);

#endif/*__K_JDSSHDR_H__*/

