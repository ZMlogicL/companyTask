/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-09
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#ifndef __IM_IIP_FLT_REGISTER_H__
#define __IM_IIP_FLT_REGISTER_H__


#include <klib.h>
#include "imiipmultiregister.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_FLT_REGISTER							(im_iip_flt_register_get_type())
#define IM_IIP_FLT_REGISTER(obj)							(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipFltRegister))
#define IM_IS_IIP_FLT_REGISTER(obj)						(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_FLT_REGISTER))

typedef union _UimfltTdltopcnf				UimfltTdltopcnf;
typedef union _UimfltPixiddef					UimfltPixiddef;
typedef union _UimfltTdlCtl						UimfltTdlCtl;
typedef union _UimfltCalcMd					UimfltCalcMd;
typedef union _UimfltTdlHsize					UimfltTdlHsize;
typedef union _UimfltTdlVsize					UimfltTdlVsize;
typedef union _UimfltTdlPhsz					UimfltTdlPhsz;
typedef union _UimfltTdlPvsz					UimfltTdlPvsz;
typedef union _UimfltTdlPf						UimfltTdlPf;
typedef union _UimfltUnitOut					UimfltUnitOut;
typedef union _UimfltFinClpAd0				UimfltFinClpAd0;
typedef union _UimfltFinClpAd1				UimfltFinClpAd1;
typedef union _UimfltFinClpAd2				UimfltFinClpAd2;
typedef union _UimfltFinClpBd0				UimfltFinClpBd0;
typedef union _UimfltFinClpBd1				UimfltFinClpBd1;
typedef union _UimfltFinClpBd2				UimfltFinClpBd2;
typedef union _UimfltIsoMd					UimfltIsoMd;
typedef union _UimfltIsoThD					UimfltIsoThD;
typedef union _UimfltIsoGainD				UimfltIsoGainD;
typedef union _UimfltSpfSpfMd				UimfltSpfSpfMd;
typedef union _UimfltSpfSpfFltw				UimfltSpfSpfFltw;
typedef union _UimfltSpfVthD0				UimfltSpfVthD0;
typedef union _UimfltSpfVthD1				UimfltSpfVthD1;
typedef union _UimfltSpfVthD2				UimfltSpfVthD2;
typedef union _UimfltSpfCoreD0			UimfltSpfCoreD0;
typedef union _UimfltSpfCoreD1			UimfltSpfCoreD1;
typedef union _UimfltSpfCoreD2			UimfltSpfCoreD2;
typedef union _UimfltSpfClpD0				UimfltSpfClpD0;
typedef union _UimfltSpfClpD1				UimfltSpfClpD1;
typedef union _UimfltSpfClpD2				UimfltSpfClpD2;
typedef union _UimfltSpfEoaddD0			UimfltSpfEoaddD0;
typedef union _UimfltSpfEoaddD1			UimfltSpfEoaddD1;
typedef union _UimfltSpfEoaddD2			UimfltSpfEoaddD2;
typedef union _UimfltEpMd						UimfltEpMd;
typedef union _UimfltEpGa						UimfltEpGa;
typedef union _UimfltEpOfs						UimfltEpOfs;
typedef union _UimfltEdBd						UimfltEdBd;
typedef union _UimfltEdFm						UimfltEdFm;
typedef union _UimfltEdOut						UimfltEdOut;
typedef union _UimfltAdaptK					UimfltAdaptK;
typedef union _UimfltAdaptTh					UimfltAdaptTh;
typedef union _UimfltAdaptDiv				UimfltAdaptDiv;
typedef union _UimfltUplkTarget			UimfltUplkTarget;
typedef union _UimfltDwlkTarget			UimfltDwlkTarget;
typedef union _UimfltLknum					UimfltLknum;
typedef union _UimfltRing						UimfltRing;
typedef union _UimfltBfMd						UimfltBfMd;
typedef struct _TimFltDump						TimFltDump;

typedef struct _ImIipFltRegister 								ImIipFltRegister;
typedef struct _ImIipFltRegisterPrivate 					ImIipFltRegisterPrivate;


///////////////////////////////////////////////////////////////
// FLT UNIT Register
///////////////////////////////////////////////////////////////
/** structure of tdltopcnf	(0000h) */
union _UimfltTdltopcnf
{
		/**< All bits */
		kulong word;
		struct {
			/**< waitconf0<br>Refer to @ref EimPortid. */
			kulong waitconf0 :6;
			kulong :2;
			kulong waitconf1 :6;
			kulong :2;
			kulong dataconf :6;
			kulong :10;
		} bit;
};

/** structure of pixiddef	(0004h) */
union _UimfltPixiddef
{
		/**< All bits */
		kulong word;
		struct {
			/**< ipixid0 */
			kulong ipixid0 :4;
			kulong :12;
			kulong ipixid1 :4;
			kulong :12;
		} bit;
};

/** structure of tdlCtl	(0008h) */
union _UimfltTdlCtl
{
		/**< All bits */
		kulong word;
		struct {
			/**< fm<br>Refer to @ref EimFm. */
			kulong fm :2;
			kulong :2;
			kulong lnum :1;
			kulong :3;
			kulong saverd :2;
			kulong :2;
			kulong inputMode :2;
			kulong :2;
			kulong csel :2;
			kulong :14;
		} bit;
};

/** structure of calcMd	(000Ch) */
union _UimfltCalcMd
{
		/**< All bits */
		kulong word;
		struct {
			/**< calcMd<br>Refer to @ref EimCalcMd */
			kulong calcMd :2;
			kulong :30;
		} bit;
};

/** structure of tdlHsize	(0010h) */
union _UimfltTdlHsize
{
		/**< All bits */
		kulong word;
		struct {
			/**< hstart */
			kulong hstart :14;
			kulong :2;
			kulong hend :14;
			kulong :2;
		} bit;
};

/** structure of tdlVsize	(0014h) */
union _UimfltTdlVsize
{
		 /**< All bits */
		kulong word;
		struct {
			/**< vstart */
			kulong vstart :14;
			kulong :2;
			kulong vend :14;
			kulong :2;
		} bit;
};

/** structure of tdlPhsz	(0018h) */
union _UimfltTdlPhsz
{
		/**< All bits */
		kulong word;
		struct {
			/**< phsz0 */
			kulong phsz0 :14;
			kulong :2;
			kulong phsz1 :14;
			kulong :2;
		} bit;
};

/** structure of tdlPvsz	(001Ch) */
union _UimfltTdlPvsz
{
		/**< All bits */
		kulong word;
		struct {
			/**< pvsz0 */
			kulong pvsz0 :14;
			kulong :2;
			kulong pvsz1 :14;
			kulong :2;
		} bit;
};

/** structure of tdlPf (0020h) */
union _UimfltTdlPf
{
		kulong word; /**< All bits */
		struct {
			/**< pfOn<br>Refer to @ref EimPfOn. */
			kulong pfOn :1;
			kulong :1;
			kulong pfMd :1;
			kulong :1;
			kulong pfNum :6;
			kulong :2;
			kulong pfAdjNum :4;
			kulong pfAdjVal :16;
		} bit;
};

/** structure of unitOut	(0024h) */
union _UimfltUnitOut
{
		/**< All bits */
		kulong word;
		struct {
			/**< unitOutAD0<br>Refer to @ref EimUnitOut. */
			kulong unitOutAD0 :3;
			kulong :1;
			kulong unitOutAD1 :3;
			kulong :1;
			kulong unitOutAD2 :3;
			kulong :5;
			kulong unitOutBD0 :3;
			kulong :1;
			kulong unitOutBD1 :3;
			kulong :1;
			kulong unitOutBD2 :3;
			kulong :5;
		} bit;
};

/** structure of finClpAD0	(0028h) */
union _UimfltFinClpAd0
{
		/**< All bits */
		kulong word;
		struct {
			/**< finClvlpAD0 */
			kint64 finClvlpAD0 :15;
			kulong :1;
			kint64 finClvlmAD0 :15;
			kulong :1;
		} bit;
};

/** structure of finClpAD1	(002Ch) */
union _UimfltFinClpAd1
{
		/**< All bits */
		kulong word;
		struct {
			/**< finClvlpAD1 */
			kint64 finClvlpAD1 :9;
			kulong :7;
			kint64 finClvlmAD1 :9;
			kulong :7;
		} bit;
};

/** structure of finClpAD2	(0030h) */
union _UimfltFinClpAd2
{
		/**< All bits */
		kulong word;
		struct {
			/**< finClvlpAD2 */
			kint64 finClvlpAD2 :9;
			kulong :7;
			kint64 finClvlmAD2 :9;
			kulong :7;
		} bit;
};

/** structure of finClpBD0	(0034h) */
union _UimfltFinClpBd0
{
		/**< All bits */
		kulong word;
		struct {
			/**< finClvlpBD0 */
			kint64 finClvlpBD0 :15;
			kulong :1;
			kint64 finClvlmBD0 :15;
			kulong :1;
		} bit;
};

/** structure of finClpBD1	(0038h) */
union _UimfltFinClpBd1
{
		 /**< All bits */
		kulong word;
		struct {
			/**< finClvlpBD1 */
			kint64 finClvlpBD1 :9;
			kulong :7;
			kint64 finClvlmBD1 :9;
			kulong :7;
		} bit;
};

/** structure of finClpBD2	(003Ch) */
union _UimfltFinClpBd2
{
		/**< All bits */
		kulong word;
		struct {
			/**< finClvlpBD2 */
			kint64 finClvlpBD2 :9;
			kulong :7;
			kint64 finClvlmBD2 :9;
			kulong :7;
		} bit;
};

/** structure of isoMd (0040h) */
union _UimfltIsoMd
{
		/**< All bits */
		kulong word;
		struct {
			/**< IsoJm */
			kulong IsoJm :1;
			kulong :15;
			kulong IsoCm :1;
			kulong :15;
		} bit;
};

/** structure of ISO_TH_D0	(0044h)	structure of ISO_TH_D1	(0048h)
	structure of ISO_TH_D2	(004Ch)	structure of ISO_TH_D3	(0050h) */
union _UimfltIsoThD
{
		 /**< All bits */
		kulong word;
		struct {
			/**< IsoUthD */
			kulong IsoUthD :15;
			kulong :1;
			kulong IsoLthD :15;
			kulong :1;
		} bit;
};

/** structure of ISO_GAIN_D0	(0054h)	structure of ISO_GAIN_D1	(0058h)
	structure of ISO_GAIN_D2	(005Ch)	structure of ISO_GAIN_D3	(0060h) */
union _UimfltIsoGainD
{
		/**< All bits */
		kulong word;
		struct {
			/**< IsoGaD */
			kulong IsoGaD :12;
			kulong :4;
			kulong IsoGbD :12;
			kulong :4;
		} bit;
};

/** structure of spfMd (0064h) */
union _UimfltSpfSpfMd
{
		 /**< All bits */
		kulong word;
		struct {
			/**< spfMd<br>Refer to @ref EimSpfMd. */
			kulong spfMd :2;
			kulong :30;
		} bit;
};

/** structure of spfFltwD0	(0080h)	structure of spfFltwD1	(00C0h)
	structure of spfFltwD2	(0100h)	structure of spfFltwD3	(0140h) */
union _UimfltSpfSpfFltw
{
		/**< All bits */
		kulong word[9];
		struct {
			/**< spfFltw0 (+00h) */
			kint64 spfFltw0 :13;
			kulong :3;
			kint64 spfFltw1 :13;
			kulong :3;
			kint64 spfFltw2 :13;
			kulong :3;
			kint64 spfFltw3 :13;
			kulong :3;
			kint64 spfFltw4 :13;
			kulong :3;
			kint64 spfFltw5 :13;
			kulong :3;
			kint64 spfFltw6 :13;
			kulong :3;
			kint64 spfFltw7 :13;
			kulong :3;
			kint64 spfFltw8 :13;
			kulong :3;
			kint64 spfFltw9 :13;
			kulong :3;
			kint64 spfFltw10 :13;
			kulong :3;
			kint64 spfFltw11 :13;
			kulong :3;
			kint64 spfFltw12 :13;
			kulong :3;
			kint64 spfFltw13 :13;
			kulong :3;
			kint64 spfFltw14 :13;
			kulong :3;
			kint64 spfFltw15 :13;
			kulong :3;
			kint64 spfFltw16 :13;
			kulong :3;
			kulong :16;
		} bit;
};

/** structure of spfVthD0 (0180h) */
union _UimfltSpfVthD0
{
		 /**< All bits */
		kulong word;
		struct {
			/**< spfUthD0 */
			kulong spfUthD0 :15;
			kulong :1;
			kulong spfLthD0 :15;
			kulong :1;
		} bit;
};

/** structure of spfVthD1 (0184h) */
union _UimfltSpfVthD1
{
		 /**< All bits */
		kulong word;
		struct {
			/**< spfUthD1 */
			kulong spfUthD1 :9;
			kulong :7;
			kulong spfLthD1 :9;
			kulong :7;
		} bit;
};

/** structure of spfVthD2 (0188h) */
union _UimfltSpfVthD2
{
		/**< All bits */
		kulong word;
		struct {
			/**< spfUthD2 */
			kulong spfUthD2 :9;
			kulong :7;
			kulong spfLthD2 :9;
			kulong :7;
		} bit;
};

/** structure of spfCoreD0	(018Ch) */
union _UimfltSpfCoreD0
{
		 /**< All bits */
		kulong word;
		struct {
			/**< spfCthpD0 */
			kulong spfCthpD0 :14;
			kulong :2;
			kulong spfCthmD0 :14;
			kulong :2;
		} bit;
};

/** structure of spfCoreD1	(0190h) */
union _UimfltSpfCoreD1
{
		/**< All bits */
		kulong word;
		struct {
			/**< spfCthpD1 */
			kulong spfCthpD1 :8;
			kulong :8;
			kulong spfCthmD1 :8;
			kulong :8;
		} bit;
};

/** structure of spfCoreD2	(0194h) */
union _UimfltSpfCoreD2
{
		/**< All bits */
		kulong word;
		struct {
			/**< spfCthpD2 */
			kulong spfCthpD2 :8;
			kulong :8;
			kulong spfCthmD2 :8;
			kulong :8;
		} bit;
};

/** structure of spfClpD0 (0198h) */
union _UimfltSpfClpD0
{
		/**< All bits */
		kulong word;
		struct {
			/**< spfClvlpD0 */
			kint64 spfClvlpD0 :15;
			kulong :1;
			kint64 spfClvlmD0 :15;
			kulong :1;
		} bit;
};

/** structure of spfClpD1 (019Ch) */
union _UimfltSpfClpD1
{
		 /**< All bits */
		kulong word;
		struct {
			/**< spfClvlpD1 */
			kint64 spfClvlpD1 :9;
			kulong :7;
			kint64 spfClvlmD1 :9;
			kulong :7;
		} bit;
};

/** structure of spfClpD2 (01A0h) */
union _UimfltSpfClpD2
{
		/**< All bits */
		kulong word;
		struct {
			/**< spfClvlpD2 */
			kint64 spfClvlpD2 :9;
			kulong :7;
			kint64 spfClvlmD2 :9;
			kulong :7;
		} bit;
};

/** structure of spfEoaddD0	(01A4h) */
union _UimfltSpfEoaddD0
{
		/**< All bits */
		kulong word;
		struct {
			/**< spfEoaddD0 */
			kulong spfEoaddD0 :14;
			kulong :18;
		} bit;
};

/** structure of spfEoaddD1	(01A8h) */
union _UimfltSpfEoaddD1
{
		/**< All bits */
		kulong word;
		struct {
			/**< spfEoaddD1 */
			kulong spfEoaddD1 :8;
			kulong :24;
		} bit;
};

/** structure of spfEoaddD2	(01ACh) */
union _UimfltSpfEoaddD2
{
		/**< All bits */
		kulong word;
		struct {
			/**< spfEoaddD2 */
			kulong spfEoaddD2 :8;
			kulong :24;
		} bit;
};

/** structure of epMd	(01B0h) */
union _UimfltEpMd
{
		/**< All bits */
		kulong word;
		struct {
			/**< epMd<br>Refer to @ref EimEpMd. */
			kulong epMd :2;
			kulong :30;
		} bit;
};

/** structure of EP_GA_D0	(01B8h)	structure of EP_GA_D1	(01C0h)
	structure of EP_GA_D2	(01C8h)	structure of EP_GA_D3	(01D0h) */
union _UimfltEpGa
{
		/**< All bits */
		kulong word[2];
		struct {
			/**< EP_GA[0] (+00h) */
			kint64 epGa0 :11;
			kulong :5;
			kint64 epGa1 :11;
			kulong :5;
			kint64 epGa2 :11;
			kulong :5;
			kulong :16;
		} bit;
};

/** structure of EP_OFS_D0	(01D8h)	structure of EP_OFS_D1	(01E0h)
	structure of EP_OFS_D2	(01E8h)	structure of EP_OFS_D3	(01F0h) */
union _UimfltEpOfs
{
		/**< All bits */
		kulong word[2];
		struct {
			/**< epOfs[0] (+00h) */
			kint64 epOfs0 :15;
			kulong :1;
			kint64 epOfs1 :15;
			kulong :1;
			kint64 epOfs2 :15;
			kulong :1;
			kulong :16;
		} bit;
};

/** structure of EP_BD_D0	(01F8h)	structure of EP_BD_D1	(0200h)
	structure of EP_BD_D2	(0208h)	structure of EP_BD_D3	(0210h) */
union _UimfltEdBd
{
		 /**< All bits */
		kulong word[2];
		struct {
			/**< epBd[0] (+00h) */
			kint64 epBd0 :15;
			kulong :1;
			kint64 epBd1 :15;
			kulong :1;
			kint64 epBd2 :15;
			kulong :1;
			kulong :16;
		} bit;
};

/** structure of edFm	(0218h) */
union _UimfltEdFm
{
		/**< All bits */
		kulong word;
		struct {
			/**< edFm0<br>Refer to @ref EimEdFm. */
			kulong edFm0 :1;
			kulong :7;
			kulong edFm1 :1;
			kulong :7;
			kulong edFm2 :1;
			kulong :7;
			kulong edFm3 :1;
			kulong :7;
		} bit;
};

/** structure of edOut (021Ch) */
union _UimfltEdOut
{
		/**< All bits */
		kulong word;
		struct {
			/**< edOut0<br>Refer to @ref EimEdOut. */
			kulong edOut0 :1;
			kulong :7;
			kulong edOut1 :1;
			kulong :7;
			kulong edOut2 :1;
			kulong :7;
			kulong edOut3 :1;
			kulong :7;
		} bit;
};

/** structure of adaptK	(0220h) */
union _UimfltAdaptK
{
		/**< All bits */
		kulong word;
		struct {
			/**< adaptK0 */
			kint64 adaptK0 :6;
			kulong :2;
			kint64 adaptK1 :6;
			kulong :2;
			kint64 adaptK2 :6;
			kulong :10;
		} bit;
};

/** structure of adaptTh	(0224h) */
union _UimfltAdaptTh
{
		/**< All bits */
		kulong word;
		struct {
			kulong adaptTh :10;
			kulong :22;
		} bit;
};

/** structure of adaptDiv	(0228h) */
union _UimfltAdaptDiv
{
		/**< All bits */
		kulong word;
		struct {
			kulong adaptDiv :3;
			kulong :29;
		} bit;
};

/** structure of uplkTarget	(022Ch) */
union _UimfltUplkTarget
{
		 /**< All bits */
		kulong word;
		struct {
			kulong upsu0 :4;
			kulong :4;
			kulong upsu1 :4;
			kulong :4;
			kulong upsu2 :4;
			kulong :12;
		} bit;
};

/** structure of dwlkTarget	(0230h) */
union _UimfltDwlkTarget
{
		kulong word;
		struct {
			kulong dwsu0 :4;
			kulong :4;
			kulong dwsu1 :4;
			kulong :4;
			kulong dwsu2 :4;
			kulong :12;
		} bit;
};

/** structure of lknum	(0234h) */
union _UimfltLknum
{
		kulong word;
		struct {
			kulong upnum :2;
			kulong :2;
			kulong dwnum :2;
			kulong :26;
		} bit;
};

/** structure of ring	(0238h) */
union _UimfltRing
{
		kulong word;
		struct {
			kulong uringsize :8;
			kulong umarginiysz :4;
			kulong :4;
			kulong dringsize :8;
			kulong :8;
		} bit;
};

/** structure of bfMd	(023Ch) */
union _UimfltBfMd
{
		kulong word;
		struct {
			kulong bfFmt :1;
			kulong :3;
			kulong bfPrt :1;
			kulong :27;
		} bit;
};

/** Define i/o mapping */
struct _TimFltDump
{
		/**< (0000 - 0003h) */
		UimfltTdltopcnf tdltopcnf;
		UimfltPixiddef pixiddef;
		UimfltTdlCtl tdlCtl;
		UimfltCalcMd calcMd;
		UimfltTdlHsize tdlHsize;
		UimfltTdlVsize tdlVsize;
		UimfltTdlPhsz tdlPhsz;
		UimfltTdlPvsz tdlPvsz;
		UimfltTdlPf tdlPf;
		UimfltUnitOut unitOut;
		UimfltFinClpAd0 finClpAD0;
		UimfltFinClpAd1 finClpAD1;
		UimfltFinClpAd2 finClpAD2;
		UimfltFinClpBd0 finClpBD0;
		UimfltFinClpBd1 finClpBD1;
		UimfltFinClpBd2 finClpBD2;
		UimfltIsoMd isoMd;
		UimfltIsoThD isoThD[4];
		UimfltIsoGainD isoGainD[4];
		UimfltSpfSpfMd spfMd;
		/**< (0068 - 007Fh) */
		kuchar dmy0068007f[0x0080 - 0x0068];
		/**< (0080 - 00A3h) */
		UimfltSpfSpfFltw spfFltwD0;
		/**< (00A4 - 00BFh) */
		kuchar dmy00a400bf[0x00C0 - 0x00A4];
		/**< (00C0 - 00E3h) */
		UimfltSpfSpfFltw spfFltwD1;
		/**< (00E4 - 00FFh) */
		kuchar dmy00e400ff[0x0100 - 0x00E4];
		/**< (0100 - 0123h) */
		UimfltSpfSpfFltw spfFltwD2;
		/**< (0124 - 013Fh) */
		kuchar dmy0124013f[0x0140 - 0x0124];
		/**< (0140 - 0163h) */
		UimfltSpfSpfFltw spfFltwD3;
		/**< (0164 - 017Fh) */
		kuchar dmy0164017f[0x0180 - 0x0164];
		/**< (0180 - 0183h) */
		UimfltSpfVthD0 spfVthD0;
		UimfltSpfVthD1 spfVthD1;
		UimfltSpfVthD2 spfVthD2;
		UimfltSpfCoreD0 spfCoreD0;
		UimfltSpfCoreD1 spfCoreD1;
		UimfltSpfCoreD2 spfCoreD2;
		UimfltSpfClpD0 spfClpD0;
		UimfltSpfClpD1 spfClpD1;
		UimfltSpfClpD2 spfClpD2;
		UimfltSpfEoaddD0 spfEoaddD0;
		UimfltSpfEoaddD1 spfEoaddD1;
		UimfltSpfEoaddD2 spfEoaddD2;
		UimfltEpMd epMd;
		/**< (01B4 - 01B7h) */
		kuchar dmy01b401b7[0x01B8 - 0x01B4];
		/**< (01B8 - 01BFh) */
		UimfltEpGa epGaD[4];
		UimfltEpOfs epOfs[4];
		UimfltEdBd epBd[4];
		UimfltEdFm edFm;
		UimfltEdOut edOut;
		UimfltAdaptK adaptK;
		UimfltAdaptTh adaptTh;
		UimfltAdaptDiv adaptDiv;
		UimfltUplkTarget uplkTarget;
		UimfltDwlkTarget dwlkTarget;
		UimfltLknum lknum;
		UimfltRing ring;
		UimfltBfMd bfMd;
		/**< 0240 - FFFFh */
		kuchar dmy502405ffff[0x60000 - 0x50240];
};

struct _ImIipFltRegister
{
	KObject parent;
};


KConstType 		    			im_iip_flt_register_get_type(void);
ImIipFltRegister*		        im_iip_flt_register_new(void);


#ifdef __cplusplus
}
#endif


#endif /* __IM_IIP_FLT_REGISTER_H__ */
