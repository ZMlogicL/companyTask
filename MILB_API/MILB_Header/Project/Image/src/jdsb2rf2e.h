/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :陈倩
 *@brief             :jdsb2rf2e
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


#ifndef __JDSB2R_F2E_H__
#define __JDSB2R_F2E_H__


#include <klib.h>
#include "__fb2r6a.h"
#include "__jdsb2r_f2e_sram.h"


#define JDSB2R_TYPE_F2E				(jdsb2r_f2e_get_type())
#define JDSB2R_F2E(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), Jdsb2rF2e))
#define JDSB2R_IS_F2E(obj)				(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSB2R_TYPE_F2E))


typedef struct _Jdsb2rF2e 				Jdsb2rF2e;
typedef struct _Jdsb2rF2ePrivate 	Jdsb2rF2ePrivate;


struct _Jdsb2rF2e
{
	KObject parent;
};


/*	structure of ybraxctl	(2841_2200h)	*/
typedef union _IoB2rYbraxctl
{
	kulong word;
	struct
	{
		kulong ybrcache :4;
		kulong ybrprot :3;
		kulong :25;
	} bit;
} IoB2rYbraxctl;

/*	structure of ybwaxctl	(2841_2204h)	*/
typedef union _IoB2rYbwaxctl
{
	kulong word;
	struct
	{
		kulong ybwcache0 :4;
		kulong ybwprot0 :3;
		kulong :1;
		kulong ybwcache1 :4;
		kulong ybwprot1 :3;
		kulong :1;
		kulong ybwcache2 :4;
		kulong ybwprot2 :3;
		kulong :9;
	} bit;
} IoB2rYbwaxctl;

/*	structure of ybraxsts	(2841_2208h)	*/
typedef union _IoB2rYbraxsts
{
	kulong word;
	struct
	{
		kulong ybrresp :2;
		kulong :30;
	} bit;
} IoB2rYbraxsts;

/*	structure of ybwaxsts	(2841_220Ch)	*/
typedef union _IoB2rYbwaxsts
{
	kulong word;
	struct
	{
		kulong ybbresp0 :2;
		kulong :6;
		kulong ybbresp1 :2;
		kulong :6;
		kulong ybbresp2 :2;
		kulong :14;
	} bit;
} IoB2rYbwaxsts;

/*	structure of ybraxmd	(2841_2210h)	*/
typedef union _IoB2rYbraxmd
{
	kulong word;
	struct
	{
		kulong ybrbl :2;
		kulong :30;
	} bit;
} IoB2rYbraxmd;

/*	structure of ybwaxmd	(2841_2214h)	*/
typedef union _IoB2rYbwaxmd
{
	kulong word;
	struct
	{
		kulong ybwbl :2;
		kulong :6;
		kulong ybwdos :1;
		kulong :23;
	} bit;
} IoB2rYbwaxmd;

/*	structure of ybrreqmsk	(2841_2218h)	*/
typedef union _IoB2rYbrreqmsk
{
	kulong word;
	struct
	{
		kulong ybrreqmsk :12;
		kulong :20;
	} bit;
} IoB2rYbrreqmsk;

/*	structure of ybwreqmsk	(2841_2220h)	*/
typedef union _IoB2rYbwreqmsk
{
	kulong word[2];
	struct
	{
		kulong ybwreqmsk0 :12;
		kulong :4;
		kulong ybwreqmsk1 :12;
		kulong :4;
		kulong ybwreqmsk2 :12;
		kulong :20;
	} bit;
} IoB2rYbwreqmsk;

/*	structure of ybinte	(2841_2240h)	*/
typedef union _IoB2rYbinte
{
	kulong word;
	struct
	{
		kulong ybree :1;
		kulong ybwee :1;
		kulong :2;
		kulong fb2ree :1;
		kulong elnee :1;
		kulong :2;
		kulong ybrere :1;
		kulong ybwere :1;
		kulong :2;
		kulong axrere :1;
		kulong axwere :1;
		kulong :18;
	} bit;
} IoB2rYbinte;

/*	structure of ybintf	(2841_2244h)	*/
typedef union _IoB2rYbintf
{
	kulong word;
	struct
	{
		kulong __ybref :1;
		kulong __ybwef :1;
		kulong :2;
		kulong __fb2ref :1;
		kulong __elnef :1;
		kulong :2;
		kulong __ybrerf :1;
		kulong __ybwerf :1;
		kulong :2;
		kulong __axrerf :1;
		kulong __axwerf :1;
		kulong :18;
	} bit;
} IoB2rYbintf;

/*	structure of dinsel	(2841_2248h)	*/
typedef union _IoB2rDinsel
{
	kulong word;
	struct
	{
		kulong b2bdin :1;
		kulong :3;
		kulong extoen :1;
		kulong :27;
	} bit;
} IoB2rDinsel;

/*	structure of b2rmode	(2841_224Ch)	*/
typedef union _IoB2rB2rmode
{
	kulong word;
	struct
	{
		kulong ciabyp :1;
		kulong ciapdd :1;
		kulong :30;
	} bit;
} IoB2rB2rmode;

/*	structure of elnlv	(2841_2250h)	*/
typedef union _IoB2rElnlv
{
	kulong word;
	struct
	{
		kulong elnlv :14;
		kulong :18;
	} bit;
} IoB2rElnlv;

/*	structure of ramaen	(2841_2254h)	*/
typedef union _IoB2rRamaen
{
	kulong word;
	struct
	{
		kulong ramaenBayDeknee :1;
		kulong ramaenYbr :1;
		kulong ramaenRgbKnee :1;
		kulong ramaenYbw :1;
		kulong :28;
	} bit;
} IoB2rRamaen;

/*	structure of exalmsl	(2841_2258h)	*/
typedef union _IoB2rExalmsl
{
	kulong word;
	struct
	{
		kulong exalmsl :2;
		kulong :30;
	} bit;
} IoB2rExalmsl;

/*	structure of ybrtrg	(2841_2280h)	*/
typedef union _IoB2rYbrtrg
{
	kulong word;
	struct
	{
		kulong ybrtrg :2;
		kulong :30;
	} bit;
} IoB2rYbrtrg;

/*	structure of ybrctl	(2841_2284h)	*/
typedef union _IoB2rYbrctl
{
	kulong word;
	struct
	{
		kulong ybrdtyp :2;
		kulong :2;
		kulong pixel :2;
		kulong :2;
		kulong dknen :1;
		kulong :23;
	} bit;
} IoB2rYbrctl;

/*	structure of ybra	(2841_2288h)	*/
typedef union _IoB2rYbra
{
	kulong word;
	struct
	{
		kulong ybra :32;
	} bit;
} IoB2rYbra;

/*	structure of ybrofs	(2841_228Ch)	*/
typedef union IoB2rYbrofs
{
	kulong word;
	struct
	{
		kulong ybrofs :3;
		kulong :29;
	} bit;
} IoB2rYbrofs;

/*	structure of ybrdef	(2841_2290h)	*/
typedef union _IoB2rYbrdef
{
	kulong word;
	struct
	{
		kulong ybrdef :16;
		kulong :16;
	} bit;
} IoB2rYbrdef;

/*	structure of ybrhsiz	(2841_2294h)	*/
typedef union _IoB2rYbrhsiz
{
	kulong word;
	struct
	{
		kulong ybrhsiz :13;
		kulong :19;
	} bit;
} IoB2rYbrhsiz;

/*	structure of ybrvsiz	(2841_2298h)	*/
typedef union _IoB2rYbrvsiz
{
	kulong word;
	struct
	{
		kulong ybrvsiz :14;
		kulong :18;
	} bit;
} IoB2rYbrvsiz;

/*	structure of ybrhblnk	(2841_229Ch)	*/
typedef union _IoB2rYbrhblnk
{
	kulong word;
	struct
	{
		kulong ybrhblnk :10;
		kulong :22;
	} bit;
} IoB2rYbrhblnk;

/*	structure of dinctl	(2841_22A0h)	*/
typedef union _IoB2rDinctl
{
	kulong word;
	struct
	{
		kulong frmstp :1;
		kulong :31;
	} bit;
} IoB2rDinctl;

/*	structure of dinhsta	(2841_22A4h)	*/
typedef union _IoB2rDinhsta
{
	kulong word;
	struct
	{
		kulong dinhsta :13;
		kulong :19;
	} bit;
} IoB2rDinhsta;

/*	structure of dinvsta	(2841_22A8h)	*/
typedef union _IoB2rDinvsta
{
	kulong word;
	struct
	{
		kulong dinvsta :14;
		kulong :18;
	} bit;
} IoB2rDinvsta;

/*	structure of dinhsiz	(2841_22ACh)	*/
typedef union _IoB2rDinhsiz
{
	kulong word;
	struct
	{
		kulong dinhsiz :13;
		kulong :19;
	} bit;
} IoB2rDinhsiz;

/*	structure of dinvsiz	(2841_22B0h)	*/
typedef union _IoB2rDinvsiz
{
	kulong word;
	struct
	{
		kulong dinvsiz :14;
		kulong :18;
	} bit;
} IoB2rDinvsiz;

/*	structure of dinels	(2841_22B4h)	*/
typedef union _IoB2rDinels
{
	kulong word;
	struct
	{
		kulong dinels :13;
		kulong :19;
	} bit;
} IoB2rDinels;

/*	structure of dinerr	(2841_22BCh)	*/
typedef union _IoB2rDinerr
{
	kulong word;
	struct
	{
		kulong trmer :1;
		kulong hpdder :1;
		kulong waiter :1;
		kulong :29;
	} bit;
} IoB2rDinerr;

/*	structure of ybwtrg	(2841_2300h)	*/
typedef union _IoB2rYbwtrg
{
	kulong word;
	struct
	{
		kulong ybwtrg :2;
		kulong :30;
	} bit;
} IoB2rYbwtrg;

/*	structure of ybwctl	(2841_2304h)	*/
typedef union _IoB2rYbwctl
{
	kulong word;
	struct
	{
		kulong ybwdtyp :2;
		kulong :2;
		kulong ybwcse :1;
		kulong :3;
		kulong usebank :2;
		kulong :22;
	} bit;
} IoB2rYbwctl;

/*	structure of ybwmd	(2841_2308h)	*/
typedef union _IoB2rYbwmd
{
	kulong word;
	struct
	{
		kulong trmen :1;
		kulong :3;
		kulong kneen :1;
		kulong :27;
	} bit;
} IoB2rYbwmd;

/*	structure of YBWBANK	(2841_230Ch)	*/
typedef union _IoB2rYbwbank
{
	kulong word;
	struct
	{
		kulong bankst :1;
		kulong :3;
		kulong bankps :2;
		kulong :2;
		kulong banksts :2;
		kulong :22;
	} bit;
} IoB2rYbwbank;

/*	structure of ybwa	(2841_2340h)	*/
typedef union _IoB2rYbwa
{
	kulong word[3][4];
	struct
	{
		kulong ybwa00 :32;
		kulong ybwa01 :32;
		kulong ybwa02 :32;
		kulong ybwa03 :32;
		kulong ybwa10 :32;
		kulong ybwa11 :32;
		kulong ybwa12 :32;
		kulong ybwa13 :32;
		kulong ybwa20 :32;
		kulong ybwa21 :32;
		kulong ybwa22 :32;
		kulong ybwa23 :32;
	} bit;
} IoB2rYbwa;

/*	structure of ybwdef	(2841_2380h)	*/
typedef union _IoB2rYbwdef
{
	kulong word;
	struct
	{
		long ybwdef :17;
		kulong :15;
	} bit;
} IoB2rYbwdef;

/*	structure of ybwtrmh	(2841_2384h)	*/
typedef union _IoB2rYbwtrmh
{
	kulong word;
	struct
	{
		kulong trmhsta :13;
		kulong :3;
		kulong trmhsiz :13;
		kulong :3;
	} bit;
} IoB2rYbwtrmh;

/*	structure of ybwtrmv	(2841_2388h)	*/
typedef union _IoB2rYbwtrmv
{
	kulong word;
	struct
	{
		kulong trmvsta :14;
		kulong :2;
		kulong trmvsiz :14;
		kulong :2;
	} bit;
} IoB2rYbwtrmv;

/*	structure of ybch area	2841_(2200 - 223Fh) */
typedef struct _IoB2rYbch
{
	IoB2rYbraxctl ybraxctl; /* 2841_(2200 - 2203h) */
	IoB2rYbwaxctl ybwaxctl; /* 2841_(2204 - 2207h) */
	IoB2rYbraxsts ybraxsts; /* 2841_(2208 - 220Bh) */
	IoB2rYbwaxsts ybwaxsts; /* 2841_(220C - 220Fh) */
	IoB2rYbraxmd ybraxmd; /* 2841_(2210 - 2213h) */
	IoB2rYbwaxmd ybwaxmd; /* 2841_(2214 - 2217h) */
	IoB2rYbrreqmsk ybrreqmsk; /* 2841_(2218 - 221Bh) */

	kuchar dmy221c221f[0x2220 - 0x221C]; /* 2841_(221C - 221Fh) */

	IoB2rYbwreqmsk ybwreqmsk; /* 2841_(2220 - 2227h) */

	kuchar dmy2228223f[0x2240 - 0x2228]; /* 2841_(2228 - 223Fh) */
} IoB2rYbch;

/*	structure of B2R COMMON area	2841_(2240 - 227Fh) */
typedef struct _IoB2rCmn
{
	IoB2rYbinte ybinte; /* 2841_(2240 - 2243h) */
	IoB2rYbintf ybintf; /* 2841_(2244 - 2247h) */
	IoB2rDinsel dinsel; /* 2841_(2248 - 224Bh) */
	IoB2rB2rmode b2rmode; /* 2841_(224C - 224Fh) */
	IoB2rElnlv elnlv; /* 2841_(2250 - 2253h) */
	IoB2rRamaen ramaen; /* 2841_(2254 - 2257h) */
	IoB2rExalmsl exalmsl; /* 2841_(2258 - 225Bh) */

	kuchar dmy225c227f[0x2280 - 0x225C]; /* 2841_(225C - 227Fh) */
} IoB2rCmn;

/*	structure of ybr area	2841_(2280 - 22FFh) */
typedef struct _IoB2rYbr
{
	IoB2rYbrtrg ybrtrg; /* 2841_(2280 - 2283h) */
	IoB2rYbrctl ybrctl; /* 2841_(2284 - 2287h) */
	IoB2rYbra ybra; /* 2841_(2288 - 228Bh) */
	IoB2rYbrofs ybrofs; /* 2841_(228C - 228Fh) */
	IoB2rYbrdef ybrdef; /* 2841_(2290 - 2293h) */
	IoB2rYbrhsiz ybrhsiz; /* 2841_(2294 - 2297h) */
	IoB2rYbrvsiz ybrvsiz; /* 2841_(2298 - 229Bh) */
	IoB2rYbrhblnk ybrhblnk; /* 2841_(229C - 229Fh) */
	IoB2rDinctl dinctl; /* 2841_(22A0 - 22A3h) */
	IoB2rDinhsta dinhsta; /* 2841_(22A4 - 22A7h) */
	IoB2rDinvsta dinvsta; /* 2841_(22A8 - 22ABh) */
	IoB2rDinhsiz dinhsiz; /* 2841_(22AC - 22AFh) */
	IoB2rDinvsiz dinvsiz; /* 2841_(22B0 - 22B3h) */
	IoB2rDinels dinels; /* 2841_(22B4 - 22B7h) */
	kuchar dmy22b822bb[0x22BC - 0x22B8]; /* 2841_(22B8 - 22BBh) */
	IoB2rDinerr dinerr; /* 2841_(22BC - 22BFh) */

	kuchar dmy22c022ff[0x2300 - 0x22C0]; /* 2841_(22C0 - 22FFh) */
} IoB2rYbr;

/*	structure of ybw area	2841_(2300 - 23FFh) */
typedef struct _IoB2rYbw
{
	IoB2rYbwtrg ybwtrg; /* 2841_(2300 - 2303h) */
	IoB2rYbwctl ybwctl; /* 2841_(2304 - 2307h) */
	IoB2rYbwmd ybwmd; /* 2841_(2308 - 230Bh) */
	IoB2rYbwbank ybwbank; /* 2841_(230C - 230Fh) */

	kuchar dmy2310233f[0x2340 - 0x2310]; /* 2841_(2310 - 233Fh) */

	IoB2rYbwa ybwa; /* 2841_(2340 - 236Fh) */

	kuchar dmy2370237f[0x2380 - 0x2370]; /* 2841_(2370 - 237Fh) */

	IoB2rYbwdef ybwdef; /* 2841_(2380 - 2383h) */
	IoB2rYbwtrmh ybwtrmh; /* 2841_(2384 - 2387h) */
	IoB2rYbwtrmv ybwtrmv; /* 2841_(2388 - 238Bh) */

	kuchar dmy238c23ff[0x2400 - 0x238C]; /* 2841_(238C - 23FFh) */
} IoB2rYbw;

/* Define i/o mapping */
typedef struct _IoB2r
{
	/* JDSB2R */
	IoB2rFb2r fB2r; /* 2841_(2000 - 21FFh) */
	IoB2rYbch ybch; /* 2841_(2200 - 223Fh) */
	IoB2rCmn b2rCmn; /* 2841_(2240 - 227Fh) */
	IoB2rYbr ybr; /* 2841_(2280 - 22FFh) */
	IoB2rYbw ybw; /* 2841_(2300 - 23FFh) */

} IoB2r;


extern volatile IoB2r ioB2rP1;
extern volatile IoB2r ioB2rP2;
extern volatile IoB2r ioB2rP3;


KConstType jdsb2r_f2e_get_type(void);
Jdsb2rF2e* jdsb2r_f2e_new(void);


#endif/*__JDSB2R_F2E_H__*/

