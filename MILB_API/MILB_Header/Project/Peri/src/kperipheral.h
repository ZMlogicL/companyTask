/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :陈倩
 *@brief             :kperipheral
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *3、
 *4、
 *5、
 *@version
 *
 */


#ifndef __K_PERIPHERAL_H__
#define __K_PERIPHERAL_H__


#include <klib.h>


#define K_TYPE_PERIPHERAL			(k_peripheral_get_type())
#define K_PERIPHERAL(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KPeripheral))
#define K_IS_PERIPHERAL(obj)		(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_PERIPHERAL))


typedef struct _KPeripheral 			KPeripheral;
typedef struct _KPeripheralPrivate KPeripheralPrivate;


struct _KPeripheral
{
	KObject parent;
};

/* 32bit reload timer register */

/* structure of TMCSR0		(1E00_0000h)	*/
/* structure of TMCSR1		(1E00_0010h)	*/
/* structure of TMCSR2		(1E00_0020h)	*/
/* structure of TMCSR3		(1E00_0030h)	*/
/* structure of TMCSR4		(1E00_0040h)	*/
/* structure of TMCSR5		(1E00_0050h)	*/
/* structure of TMCSR6		(1E00_0060h)	*/
/* structure of TMCSR7		(1E00_0070h)	*/
/* structure of TMCSR8		(1E00_0080h)	*/
/* structure of TMCSR9		(1E00_0090h)	*/
/* structure of TMCSR10		(1E00_00A0h)	*/
/* structure of TMCSR11		(1E00_00B0h)	*/
/* structure of TMCSR12		(1E00_00C0h)	*/
/* structure of TMCSR13		(1E00_00D0h)	*/
typedef union _IoTmrTmcsr
{
	kulong word;
	struct
	{
		kulong __trg :1;
		kulong __cnte :1;
		kulong __uf :1;
		kulong __inte :1;
		kulong __reld :1;
		kulong __outl :1;
		kulong :1;
		kulong __mod :3;
		kulong __csl :2;
		kulong __rels :1;
		kulong :3;
		kulong :16;
	} bit;
} IoTmrTmcsr;

/* 64bit free run timer register */

/* structure of tmcsr641	(1E00_0100h)	*/
typedef union _IoTmr64Tmcsr1
{
	kulong word;
	struct
	{
		kulong trg :1;
		kulong cnte :1;
		kulong :8;
		kulong csl :2;
		kulong :4;
		kulong :16;
	} bit;
} IoTmr64Tmcsr1;

/* structure of tmcsr642	(1E00_0110h)	*/
typedef union _IoTmr64Tmcsr2
{
	kulong word;
	struct
	{
		kulong __cvt :1;
		kulong :15;
		kulong __tsen :1;
		kulong :15;
	} bit;
} IoTmr64Tmcsr2;

/* pwm timer register */

/* structure of gcn1		(1E00_1000h)	*/
typedef union _IoPwmGcn1
{
	kulong word;
	struct
	{
		kulong tsel0 :4;
		kulong tsel1 :4;
		kulong tsel2 :4;
		kulong tsel3 :4;

		kulong :16;
	} bit;
} IoPwmGcn1;

/* structure of gcn2		(1E00_1004h)	*/
typedef union _IoPwmGcn2
{
	kulong word;
	struct
	{
		kulong en0 :1;
		kulong en1 :1;
		kulong en2 :1;
		kulong en3 :1;
		kulong chas :1;
		kulong :2;
		kulong tmeen :1;

		kulong msk0 :1;
		kulong msk1 :1;
		kulong msk2 :1;
		kulong msk3 :1;
		kulong stp0 :1;
		kulong stp1 :1;
		kulong stp2 :1;
		kulong stp3 :1;

		kulong :16;
	} bit;
} IoPwmGcn2;

/* structure of ptmra		(1E00_1010h)	*/
/* structure of ptmrb		(1E00_1020h)	*/
/* structure of ptmrc		(1E00_1030h)	*/
/* structure of ptmrd		(1E00_1040h)	*/
/* structure of ptmre		(1E00_1050h)	*/

/* structure of pcsra		(1E00_1014h)	*/
/* structure of pcsrb		(1E00_1024h)	*/
/* structure of pcsrc		(1E00_1034h)	*/
/* structure of pcsrd		(1E00_1044h)	*/

/* structure of pduta		(1E00_1018h)	*/
/* structure of pdutb		(1E00_1028h)	*/
/* structure of pdutc		(1E00_1038h)	*/
/* structure of pdutd		(1E00_1048h)	*/

/* structure of pcna		(1E00_101Ch)	*/
/* structure of pcnb		(1E00_102Ch)	*/
/* structure of pcnc		(1E00_103Ch)	*/
/* structure of pcnd		(1E00_104Ch)	*/
/* structure of pcne		(1E00_1054h)	*/
typedef union _IoPwmPcn
{
	kulong word;
	struct
	{
		kulong __osel :1;
		kulong :1;
		kulong __irs :2;
		kulong __irqf :1;
		kulong __iren :1;
		kulong __egs :2;

		kulong :1;
		kulong __pgms :1;
		kulong __cks :2;
		kulong __rtrg :1;
		kulong __mdse :1;
		kulong __stgr :1;
		kulong __cnte :1;

		kulong :16;
	} bit;
} IoPwmPcn;

/* structure of tsel		(1E00_1058h)	*/
typedef union _IoPwmTsel
{
	kulong word;
	struct
	{
		kulong sel0 :2;
		kulong sel1 :2;
		kulong sel2 :2;
		kulong sel3 :2;

		kulong :24;
	} bit;
} IoPwmTsel;

/* structure of prev		(1E00_105Ch)	*/
typedef union _IoPwmPrev
{
	kulong word;
	struct
	{
		kulong :8;

		kulong preve0 :1;
		kulong preve1 :1;
		kulong preve2 :1;
		kulong preve3 :1;
		kulong :4;

		kulong :16;
	} bit;
} IoPwmPrev;

/* structure of pcsrqa		(1E00_1080h)	*/
/* structure of pcsrqb		(1E00_1088h)	*/
/* structure of pcsrqc		(1E00_1090h)	*/
/* structure of pcsrqd		(1E00_1098h)	*/

/* structure of pdutqa		(1E00_1084h)	*/
/* structure of pdutqb		(1E00_108Ch)	*/
/* structure of pdutqc		(1E00_1094h)	*/
/* structure of pdutqd		(1E00_109Ch)	*/

/* structure of pcsrra		(1E00_10A0h)	*/
/* structure of pcsrrb		(1E00_10A8h)	*/
/* structure of pcsrrc		(1E00_10B0h)	*/
/* structure of pcsrrd		(1E00_10B8h)	*/

/* structure of pdutra		(1E00_10A4h)	*/
/* structure of pdutrb		(1E00_10ACh)	*/
/* structure of pdutrc		(1E00_10B4h)	*/
/* structure of pdutrd		(1E00_10BCh)	*/

/* structure of pchset0 	(1E00_10C0h)	*/
typedef union _IoPwmPchset0
{
	kulong word;
	struct
	{
		kulong frcen0 :1;
		kulong frcen1 :1;
		kulong frcen2 :1;
		kulong frcen3 :1;
		kulong osta0 :1;
		kulong osta1 :1;
		kulong osta2 :1;
		kulong osta3 :1;

		kulong frcval0 :1;
		kulong frcval1 :1;
		kulong frcval2 :1;
		kulong frcval3 :1;
		kulong hld0 :1;
		kulong hld1 :1;
		kulong hld2 :1;
		kulong hld3 :1;

		kulong :16;
	} bit;
} IoPwmPchset0;

/* structure of pchset1 	(1E00_10C4h)	*/
typedef union _IoPwmPchset1
{
	kulong word;
	struct
	{
		kulong uden :1;
		kulong :7;

		kulong rqtim :2;
		kulong :6;

		kulong :16;
	} bit;
} IoPwmPchset1;

/* structure of pintct0 	(1E00_10C8h)	*/
typedef union _IoPwmPintct0
{
	kulong word;
	struct
	{
		kulong __aie :1;
		kulong __fie :1;
		kulong :2;
		kulong __uie :1;
		kulong :3;

		kulong __ais :1;
		kulong __fis :1;
		kulong :2;
		kulong __uis :1;
		kulong :3;

		kulong :16;
	} bit;
} IoPwmPintct0;

/* structure of pintct1 	(1E00_10CCh)	*/
typedef union _IoPwmPintct1
{
	kulong word;
	struct
	{
		kulong :7;
		kulong drqe :1;

		kulong :7;
		kulong drqs :1;

		kulong :16;
	} bit;
} IoPwmPintct1;

/* structure of stmrh		(1E00_10D0h)	*/
/* structure of stmrl		(1E00_10D4h)	*/

/* structure of pcsre0		(1E00_1100h)	*/
/* structure of pcsre1		(1E00_1110h)	*/
/* structure of pcsre2		(1E00_1120h)	*/
/* structure of pcsre3		(1E00_1130h)	*/
/* structure of pcsre4		(1E00_1140h)	*/
/* structure of pcsre5		(1E00_1150h)	*/
/* structure of pcsre6		(1E00_1160h)	*/
/* structure of pcsre7		(1E00_1170h)	*/

/* structure of pdute0		(1E00_1104h)	*/
/* structure of pdute1		(1E00_1114h)	*/
/* structure of pdute2		(1E00_1124h)	*/
/* structure of pdute3		(1E00_1134h)	*/
/* structure of pdute4		(1E00_1144h)	*/
/* structure of pdute5		(1E00_1154h)	*/
/* structure of pdute6		(1E00_1164h)	*/
/* structure of pdute7		(1E00_1174h)	*/

/* structure of ppale0		(1E00_1108h)	*/
/* structure of ppale1		(1E00_1118h)	*/
/* structure of ppale2		(1E00_1128h)	*/
/* structure of ppale3		(1E00_1138h)	*/
/* structure of ppale4		(1E00_1148h)	*/
/* structure of ppale5		(1E00_1158h)	*/
/* structure of ppale6		(1E00_1168h)	*/
/* structure of ppale7		(1E00_1178h)	*/
typedef union _IoPwmPpale
{
	kulong word;
	struct
	{
		kulong ppale :10;
		kulong :5;
		kulong link :1;

		kulong :16;
	} bit;
} IoPwmPpale;

/* structure of pcsru0		(1E00_1180h)	*/
/* structure of pcsru1		(1E00_1190h)	*/
/* structure of pcsru2		(1E00_11A0h)	*/
/* structure of pcsru3		(1E00_11B0h)	*/

/* structure of pdutu0		(1E00_1184h)	*/
/* structure of pdutu1		(1E00_1194h)	*/
/* structure of pdutu2		(1E00_11A4h)	*/
/* structure of pdutu3		(1E00_11B4h)	*/

/* structure of ppalu0		(1E00_1188h)	*/
/* structure of ppalu1		(1E00_1198h)	*/
/* structure of ppalu2		(1E00_11A8h)	*/
/* structure of ppalu3		(1E00_11B8h)	*/
typedef union _IoPwmPpalu
{
	kulong word;
	struct
	{
		kulong ppalu :10;
		kulong :5;
		kulong link :1;

		kulong :16;
	} bit;
} IoPwmPpalu;

/* i2c */
/* structure of SDAT0		(1E00_3000h)	*/
/* structure of SDAT1		(1E00_3400h)	*/
/* structure of SDAT2		(1E00_3800h)	*/
typedef union _IoI2cSdat
{
	kulong word;
	struct
	{
		kulong data :8;

		kulong :24;
	} bit;
} IoI2cSdat;

/* structure of ST0			(1E00_3004h)	*/
/* structure of ST1			(1E00_3404h)	*/
/* structure of ST2			(1E00_3804h)	*/
typedef union _IoI2cSt
{
	kulong word;
	struct
	{
		kulong mode :5;
		kulong :2;
		kulong ksint :1;

		kulong :24;
	} bit;
} IoI2cSt;

/* structure of CST0		(1E00_3008h)	*/
/* structure of CST1		(1E00_3408h)	*/
/* structure of CST2		(1E00_3808h)	*/
typedef union _IoI2cCst
{
	kulong word;
	struct
	{
		kulong bb :1;
		kulong tocdiv :2;
		kulong terr :1;
		kulong tsda :1;
		kulong tgscl :1;
		kulong pecnext :1;
		kulong pecfault :1;

		kulong :24;
	} bit;
} IoI2cCst;

/* structure of CTL1_0		(1E00_300Ch)	*/
/* structure of CTL1_1		(1E00_340Ch)	*/
/* structure of CTL1_2		(1E00_380Ch)	*/
typedef union _IoI2cCtl1
{
	kulong word;
	struct
	{
		kulong start :1;
		kulong stop :1;
		kulong inten :1;
		kulong :1;
		kulong ack :1;
		kulong gcmen :1;
		kulong smbare :1;
		kulong clrst :1;

		kulong :24;
	} bit;
} IoI2cCtl1;

/* structure of ADDR0		(1E00_3010h)	*/
/* structure of ADDR1		(1E00_3410h)	*/
/* structure of ADDR2		(1E00_3810h)	*/
typedef union _IoI2cAddr
{
	kulong word;
	struct
	{
		kulong addr :7;
		kulong saen :1;

		kulong :24;
	} bit;
} IoI2cAddr;

/* structure of CTL2_0		(1E00_3014h)	*/
/* structure of CTL2_1		(1E00_3414h)	*/
/* structure of CTL2_2		(1E00_3814h)	*/
typedef union _IoI2cCtl2
{
	kulong word;
	struct
	{
		kulong enable :1;
		kulong sclfrq :7;

		kulong :24;
	} bit;
} IoI2cCtl2;

/* structure of TOPR0		(1E00_3018h)	*/
/* structure of TOPR1		(1E00_3418h)	*/
/* structure of TOPR2		(1E00_3818h)	*/
typedef union _IoI2cTopr
{
	kulong word;
	struct
	{
		kulong topr :8;

		kulong :24;
	} bit;
} IoI2cTopr;

/* structure of CTL3_0		(1E00_301Ch)	*/
/* structure of CTL3_1		(1E00_341Ch)	*/
/* structure of CTL3_2		(1E00_381Ch)	*/
typedef union _IoI2cCtl3
{
	kulong word;
	struct
	{
		kulong s10adr :3;
		kulong s10en :1;
		kulong hscdiv :4;

		kulong :24;
	} bit;
} IoI2cCtl3;

/* udc */
/* structure of UDCR0		(1E00_2000h)	*/
/* structure of UDCR1		(1E00_2020h)	*/
/* structure of UDCR2		(1E00_2040h)	*/
/* structure of UDCR3		(1E00_2060h)	*/
/* structure of UDCR4		(1E00_2080h)	*/
/* structure of UDCR5		(1E00_20A0h)	*/
typedef union _IoUdcUdcr
{
	kulong word;
	struct
	{
		kulong d :16;

		kulong :16;
	} bit;
} IoUdcUdcr;

/* structure of RCR0		(1E00_2004h)	*/
/* structure of RCR1		(1E00_2024h)	*/
/* structure of RCR2		(1E00_2044h)	*/
/* structure of RCR3		(1E00_2064h)	*/
/* structure of RCR4		(1E00_2084h)	*/
/* structure of RCR5		(1E00_20A4h)	*/
typedef union _IoUdcRcr
{
	kulong word;
	struct
	{
		kulong d :16;

		kulong :16;
	} bit;
} IoUdcRcr;

/* structure of CSR0		(1E00_200Ch)	*/
/* structure of CSR1		(1E00_202Ch)	*/
/* structure of CSR2		(1E00_204Ch)	*/
/* structure of CSR3		(1E00_206Ch)	*/
/* structure of CSR4		(1E00_208Ch)	*/
/* structure of CSR5		(1E00_20ACh)	*/
typedef union _IoUdcCsr
{
	kulong word;
	struct
	{
		kulong __udf :2;
		kulong __udff :1;
		kulong __ovff :1;
		kulong __cmpf :1;
		kulong __udie :1;
		kulong __cite :1;
		kulong __cstr :1;

		kulong :24;
	} bit;
} IoUdcCsr;

/* structure of CCR0		(1E00_2014h)	*/
/* structure of CCR1		(1E00_2034h)	*/
/* structure of CCR2		(1E00_2054h)	*/
/* structure of CCR3		(1E00_2074h)	*/
/* structure of CCR4		(1E00_2094h)	*/
/* structure of CCR5		(1E00_20B4h)	*/
typedef union _IoUdcCcr
{
	kulong word;
	struct
	{
		kulong __cge :2;
		kulong __cgsc :1;
		kulong __udcc :1;
		kulong __rlde :1;
		kulong __ucre :1;
		kulong __ctut :1;
		kulong :1;

		kulong __ces :2;
		kulong __cms :2;
		kulong __clks :1;
		kulong __cfie :1;
		kulong __cdcf :1;
		// Reserve bit. However, it is necessary to be "1".
		kulong __m16e :1;

		kulong :16;
	} bit;
} IoUdcCcr;

typedef struct _IoTmr
{
	/* 1E00_(0000 - 0003h) */
	IoTmrTmcsr tmcsr;
	/* 1E00_(0004 - 0007h) */
	kulong tmr;
	/* 1E00_(0008 - 000Bh) */
	kulong tmrlr0;
	/* 1E00_(000C - 000Fh) */
	kulong tmrlr1;
} IoTmr;

typedef struct _IoTmr64
{
	/* 1E00_(0100 - 0103h) */
	IoTmr64Tmcsr1 tmcsr641;
	/* 1E00_(0104 - 010Fh) */
	kuchar dmyPeri0104010f[0x0110 - 0x0104];
	/* 1E00_(0110 - 0113h) */
	IoTmr64Tmcsr2 tmcsr642;
	/* 1E00_(0114 - 011Fh) */
	kuchar dmyPeri0114011f[0x0120 - 0x0114];
	/* 1E00_(0120 - 0123h) */
	kulong gstmp;
	/* 1E00_(0124 - 01FFh) */
	kuchar dmyPeri012401ff[0x0200 - 0x0124];
	/* 1E00_(0200 - 0203h) */
	kulong fsstmp00l;
	/* 1E00_(0204 - 0207h) */
	kulong fsstmp00h;
	/* 1E00_(0208 - 020Bh) */
	kulong fsstmp01l;
	/* 1E00_(020C - 020Fh) */
	kulong fsstmp01h;
	/* 1E00_(0210 - 0213h) */
	kulong fsstmp02l;
	/* 1E00_(0214 - 0217h) */
	kulong fsstmp02h;
	/* 1E00_(0218 - 021Fh) */
	kuchar dmyPeri0218021f[0x0220 - 0x0218];
	/* 1E00_(0220 - 0223h) */
	kulong fsstmp10l;
	/* 1E00_(0224 - 0227h) */
	kulong fsstmp10h;
	/* 1E00_(0228 - 022Bh) */
	kulong fsstmp11l;
	/* 1E00_(022C - 022Fh) */
	kulong fsstmp11h;
	/* 1E00_(0230 - 0233h) */
	kulong fsstmp12l;
	/* 1E00_(0234 - 0237h) */
	kulong fsstmp12h;
	/* 1E00_(0238 - 023Fh) */
	kuchar dmyPeri0238023f[0x0240 - 0x0238];
	/* 1E00_(0240 - 0243h) */
	kulong fsstmp20l;
	/* 1E00_(0240 - 0247h) */
	kulong fsstmp20h;
	/* 1E00_(0248 - 024Bh) */
	kulong fsstmp21l;
	/* 1E00_(024C - 024Fh) */
	kulong fsstmp21h;
	/* 1E00_(0250 - 0253h) */
	kulong fsstmp22l;
	/* 1E00_(0253 - 0257h) */
	kulong fsstmp22h;
	/* 1E00_(0258 - 025Fh) */
	kuchar dmyPeri0258025f[0x0260 - 0x0258];
	/* 1E00_(0260 - 0263h) */
	kulong fsstmp30l;
	/* 1E00_(0264 - 0267h) */
	kulong fsstmp30h;
	/* 1E00_(0268 - 026Bh) */
	kulong fsstmp31l;
	/* 1E00_(026C - 026Fh) */
	kulong fsstmp31h;
	/* 1E00_(0270 - 0273h) */
	kulong fsstmp32l;
	/* 1E00_(0274 - 0277h) */
	kulong fsstmp32h;
	/* 1E00_(0278 - 027Fh) */
	kuchar dmyperi027802ff[0x0300 - 0x0278];
	/* 1E00_(0300 - 0303h) */
	kulong festmp00l;
	/* 1E00_(0304 - 0307h) */
	kulong festmp00h;
	/* 1E00_(0308 - 030Bh) */
	kulong festmp01l;
	/* 1E00_(030C - 030Fh) */
	kulong festmp01h;
	/* 1E00_(0310 - 0313h) */
	kulong festmp02l;
	/* 1E00_(0314 - 0317h) */
	kulong festmp02h;
	/* 1E00_(0318 - 031Fh) */
	kuchar dmyperi0318031f[0x0320 - 0x0318];
	/* 1E00_(0320 - 0323h) */
	kulong festmp10l;
	/* 1E00_(0324 - 0327h) */
	kulong festmp10h;
	/* 1E00_(0328 - 032Bh) */
	kulong festmp11l;
	/* 1E00_(032C - 032Fh) */
	kulong festmp11h;
	/* 1E00_(0330 - 0333h) */
	kulong festmp12l;
	/* 1E00_(0334 - 0337h) */
	kulong festmp12h;
	/* 1E00_(0338 - 033Fh) */
	kuchar dmyperi0338033f[0x0340 - 0x0338];
	/* 1E00_(0340 - 0343h) */
	kulong festmp20l;
	/* 1E00_(0340 - 0347h) */
	kulong festmp20h;
	/* 1E00_(0348 - 034Bh) */
	kulong festmp21l;
	/* 1E00_(034C - 034Fh) */
	kulong festmp21h;
	/* 1E00_(0350 - 0353h) */
	kulong festmp22l;
	/* 1E00_(0353 - 0357h) */
	kulong festmp22h;
	/* 1E00_(0358 - 035Fh) */
	kuchar dmyperi0358035f[0x0360 - 0x0358];
	/* 1E00_(0360 - 0363h) */
	kulong festmp30l;
	/* 1E00_(0364 - 0367h) */
	kulong festmp30h;
	/* 1E00_(0368 - 036Bh) */
	kulong festmp31l;
	/* 1E00_(036C - 036Fh) */
	kulong festmp31h;
	/* 1E00_(0370 - 0373h) */
	kulong festmp32l;
	/* 1E00_(0374 - 0377h) */
	kulong festmp32h;
	/* 1E00_(0378 - 037Fh) */
	kuchar dmyperi037803ff[0x0400 - 0x0378];
	/* 1E00_(0400 - 0403h) */
	kulong tmr64L;
	/* 1E00_(0404 - 0407h) */
	kulong tmr64H;
} IoTmr64;

typedef struct _IoPwm
{
	/* 1E00_(1000 - 1003h) */
	IoPwmGcn1 gcn1;
	/* 1E00_(1004 - 1007h) */
	IoPwmGcn2 gcn2;
	/* 1E00_(1008 - 100Fh) */
	kuchar dmyperi1008100f[0x1010 - 0x1008];
	/* 1E00_(1010 - 1013h) */
	kulong ptmra;
	/* 1E00_(1014 - 1017h) */
	kulong pcsra;
	/* 1E00_(1018 - 101Bh) */
	kulong pduta;
	/* 1E00_(101C - 101Fh) */
	IoPwmPcn pcna;
	/* 1E00_(1020 - 1023h) */
	kulong ptmrb;
	/* 1E00_(1024 - 1027h) */
	kulong pcsrb;
	/* 1E00_(1028 - 102Bh) */
	kulong pdutb;
	/* 1E00_(102C - 102Fh) */
	IoPwmPcn pcnb;
	/* 1E00_(1030 - 1033h) */
	kulong ptmrc;
	/* 1E00_(1034 - 1037h) */
	kulong pcsrc;
	/* 1E00_(1038 - 103Bh) */
	kulong pdutc;
	/* 1E00_(103C - 103Fh) */
	IoPwmPcn pcnc;
	/* 1E00_(1040 - 1043h) */
	kulong ptmrd;
	/* 1E00_(1044 - 1047h) */
	kulong pcsrd;
	/* 1E00_(1048 - 104Bh) */
	kulong pdutd;
	/* 1E00_(104C - 104Fh) */
	IoPwmPcn pcnd;
	/* 1E00_(1050 - 1053h) */
	kulong ptmre;
	/* 1E00_(1054 - 1057h) */
	IoPwmPcn pcne;
	/* 1E00_(1058 - 105Bh) */
	IoPwmTsel tsel;
	/* 1E00_(105C - 105Fh) */
	IoPwmPrev prev;
	/* 1E00_(1060 - 107Fh) */
	kuchar dmyperi1060107f[0x1080 - 0x1060];
	/* 1E00_(1080 - 1083h) */
	kulong pcsrqa;
	/* 1E00_(1084 - 1087h) */
	kulong pdutqa;
	/* 1E00_(1088 - 108Bh) */
	kulong pcsrqb;
	/* 1E00_(108C - 108Fh) */
	kulong pdutqb;
	/* 1E00_(1090 - 1093h) */
	kulong pcsrqc;
	/* 1E00_(1094 - 1097h) */
	kulong pdutqc;
	/* 1E00_(1098 - 109Bh) */
	kulong pcsrqd;
	/* 1E00_(109C - 109Fh) */
	kulong pdutqd;
	/* 1E00_(10A0 - 10A3h) */
	kulong pcsrra;
	/* 1E00_(10A4 - 10A7h) */
	kulong pdutra;
	/* 1E00_(10A8 - 10ABh) */
	kulong pcsrrb;
	/* 1E00_(10AC - 10AFh) */
	kulong pdutrb;
	/* 1E00_(10B0 - 10B3h) */
	kulong pcsrrc;
	/* 1E00_(10B4 - 10B7h) */
	kulong pdutrc;
	/* 1E00_(10B8 - 10BBh) */
	kulong pcsrrd;
	/* 1E00_(10BC - 10BFh) */
	kulong pdutrd;
	/* 1E00_(10C0 - 10C3h) */
	IoPwmPchset0 pchset0;
	/* 1E00_(10C4 - 10C7h) */
	IoPwmPchset1 pchset1;
	/* 1E00_(10C8 - 10CBh) */
	IoPwmPintct0 pintct0;
	/* 1E00_(10CC - 10CFh) */
	IoPwmPintct1 pintct1;
	/* 1E00_(10D0 - 10D3h) */
	kulong stmrh;
	/* 1E00_(10D4 - 10D7h) */
	kulong stmrl;
	/* 1E00_(10D8 - 10FFh) */
	kuchar dmyperi10d810ff[0x1100 - 0x10D8];
	/* 1E00_(1100 - 1103h) */
	kulong pcsre0;
	/* 1E00_(1104 - 1107h) */
	kulong pdute0;
	/* 1E00_(1108 - 110Bh) */
	IoPwmPpale ppale0;
	/* 1E00_(110C - 110Fh) */
	kuchar dmyperi110c110f[0x1110 - 0x110C];
	/* 1E00_(1110 - 1113h) */
	kulong pcsre1;
	/* 1E00_(1114 - 1117h) */
	kulong pdute1;
	/* 1E00_(1118 - 111Bh) */
	IoPwmPpale ppale1;
	/* 1E00_(111C - 111Fh) */
	kuchar dmyperi111c111f[0x1120 - 0x111C];
	/* 1E00_(1120 - 1123h) */
	kulong pcsre2;
	/* 1E00_(1124 - 1127h) */
	kulong pdute2;
	/* 1E00_(1128 - 112Bh) */
	IoPwmPpale ppale2;
	/* 1E00_(112C - 112Fh) */
	kuchar dmyperi112c112f[0x1130 - 0x112C];
	/* 1E00_(1130 - 1133h) */
	kulong pcsre3;
	/* 1E00_(1134 - 1137h) */
	kulong pdute3;
	/* 1E00_(1138 - 113Bh) */
	IoPwmPpale ppale3;
	/* 1E00_(113C - 113Fh) */
	kuchar dmy_peri_113C_113F[0x1140 - 0x113C];
	/* 1E00_(1140 - 1143h) */
	kulong pcsre4;
	/* 1E00_(1144 - 1147h) */
	kulong pdute4;
	/* 1E00_(1148 - 114Bh) */
	IoPwmPpale ppale4;
	/* 1E00_(114C - 114Fh) */
	kuchar dmyperi114c114f[0x1150 - 0x114C];
	/* 1E00_(1150 - 1153h) */
	kulong pcsre5;
	/* 1E00_(1154 - 1157h) */
	kulong pdute5;
	/* 1E00_(1158 - 115Bh) */
	IoPwmPpale ppale5;
	/* 1E00_(115C - 115Fh) */
	kuchar dmyperi115c115f[0x1160 - 0x115C];
	/* 1E00_(1160 - 1163h) */
	kulong pcsre6;
	/* 1E00_(1164 - 1167h) */
	kulong pdute6;
	/* 1E00_(1168 - 116Bh) */
	IoPwmPpale ppale6;
	/* 1E00_(116C - 116Fh) */
	kuchar dmyperi116c116f[0x1170 - 0x116C];
	/* 1E00_(1170 - 1173h) */
	kulong pcsre7;
	/* 1E00_(1174 - 1177h) */
	kulong pdute7;
	/* 1E00_(1178 - 117Bh) */
	IoPwmPpale ppale7;
	/* 1E00_(117C - 117Fh) */
	kuchar dmyperi117c117f[0x1180 - 0x117C];
	/* 1E00_(1180 - 1183h) */
	kulong pcsru0;
	/* 1E00_(1184 - 1187h) */
	kulong pdutu0;
	/* 1E00_(1188 - 118Bh) */
	IoPwmPpalu ppalu0;
	/* 1E00_(118C - 118Fh) */
	kuchar dmyperi118c118f[0x1190 - 0x118C];
	/* 1E00_(1190 - 1193h) */
	kulong pcsru1;
	/* 1E00_(1194 - 1197h) */
	kulong pdutu1;
	/* 1E00_(1198 - 119Bh) */
	IoPwmPpalu ppalu1;
	/* 1E00_(119C - 119Fh) */
	kuchar dmyperi119c119f[0x11A0 - 0x119C];
	/* 1E00_(11A0 - 11A3h) */
	kulong pcsru2;
	/* 1E00_(11A4 - 11A7h) */
	kulong pdutu2;
	/* 1E00_(11A8 - 11ABh) */
	IoPwmPpalu ppalu2;
	/* 1E00_(11AC - 11AFh) */
	kuchar dmyperi11ac11af[0x11B0 - 0x11AC];
	/* 1E00_(11B0 - 11B3h) */
	kulong pcsru3;
	/* 1E00_(11B4 - 11B7h) */
	kulong pdutu3;
	/* 1E00_(11B8 - 11BBh) */
	IoPwmPpalu ppalu3;
	/* 1E00_(11BC - 13FFh) */
	kuchar dmyperi11bc13ff[0x1400 - 0x11BC];
} IoPwm;

typedef struct _IoUdc
{
	/* 1E00_(2000 - 2003h) */
	IoUdcUdcr udcr;
	/* 1E00_(2004 - 2007h) */
	IoUdcRcr rcr;
	/* 1E00_(2008 - 200Bh) */
	kuchar dmyperi2008200b[0x200C - 0x2008];
	/* 1E00_(200C - 200Fh) */
	IoUdcCsr csr;
	/* 1E00_(2010 - 2013h) */
	kuchar dmyperi20102013[0x2014 - 0x2010];
	/* 1E00_(2014 - 2017h) */
	IoUdcCcr ccr;
	/* 1E00_(2018 - 201Fh) */
	kuchar dmyperi2018201f[0x2020 - 0x2018];
} IoUdc;

typedef struct _IoI2c
{
	/* 1E00_(3000 - 3003h) */
	IoI2cSdat sdat;
	/* 1E00_(3004 - 3007h) */
	IoI2cSt st;
	/* 1E00_(3008 - 300Bh) */
	IoI2cCst cst;
	/* 1E00_(300C - 300Fh) */
	IoI2cCtl1 ctl1;
	/* 1E00_(3010 - 3013h) */
	IoI2cAddr addr;
	/* 1E00_(3014 - 3017h) */
	IoI2cCtl2 ctl2;
	/* 1E00_(3018 - 301Bh) */
	IoI2cTopr topr;
	/* 1E00_(301C - 301Fh) */
	IoI2cCtl3 ctl3;
	/* 1E00_(3020 - 33FFh) */
	kuchar dmyperi302033ff[0x3400 - 0x3020];
} IoI2c;

/* Define I/O mapping		*/
typedef struct _IoPeri
{
	/* 32bit reload timer registers */
	/* 1E00_(0000 - 00DFh)	*/
	IoTmr tmr[14];
	/* 1E00_(00E0 - 00FFh)	*/
	kuchar dmyperi00e000ff[0x0100 - 0x00E0];
	/* 64bit free run timer registers */
	/* 1E00_(0100 - 0407h)	*/
	IoTmr64 tmr64;
	/* 1E00_(0408 - 0FFFh)	*/
	kuchar dmyperi04080fff[0x1000 - 0x0408];
	/* pwm timer registers */
	/* 1E00_(1000 - 1FFFh)	*/
	IoPwm pwm[4];
	/* udc interface registers */
	/* 1E00_(2000 - 20BFh)	*/
	IoUdc udc[6];
	/* 1E00_(20C0 - 2FFFh)	*/
	kuchar dmyperi20c02fff[0x3000 - 0x20C0];
	/* i2c interface registers */
	/* 1E00_(3000 - 3BFFh)	*/
	IoI2c i2c[3];
	/* 1E00_(3C00 - 3FFFh)	*/
	kuchar dmyperi3c003fff[0x4000 - 0x3C00];
} IoPeri;

typedef struct _IoPwmdma
{
	/* pwm buffer data window registers */
	/* 1E12_(0000 - 03FFh)	*/
	kushort bfdtpt[512];
	/* 1E12_(0400 - FFFFh) */
	kuchar dmyperi0400ffff[0x30000 - 0x20400];
} IoPwmdma;


extern volatile IoPeri ioPeri;
extern volatile IoPwmdma ioPwmdma[4];


KConstType k_peripheral_get_type(void);
KPeripheral* k_peripheral_new(void);


#endif/*__K_PERIPHERAL_H__*/

