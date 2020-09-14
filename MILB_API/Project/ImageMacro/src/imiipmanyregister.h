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


#ifndef __IM_IIP_MANY_REGISTER_H__
#define __IM_IIP_MANY_REGISTER_H__


#include <stdio.h>
#include <glib-object.h>
#include "imiipfrectregister.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_MANY_REGISTER			(im_iip_many_register_struct_get_type ())
#define IM_IIP_MANY_REGISTER(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_IIP_MANY_REGISTER, ImIipManyRegister))
#define IM_IIP_MANY_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_IIP_MANY_REGISTER, ImIipManyRegisterClass))
#define IM_IS_IIP_MANY_REGISTER(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_IIP_MANY_REGISTER))
#define IM_IS_IIP_MANY_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_IIP_MANY_REGISTER))
#define IM_IIP_MANY_REGISTER_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_IIP_MANY_REGISTER, ImIipManyRegisterClass))


typedef union _Uim1dlLdTopcnf0				Uim1dlLdTopcnf0;
typedef union _Uim1dlLdTopcnf1				Uim1dlLdTopcnf1;
typedef union _Uim1dlPixiddef					Uim1dlPixiddef;
typedef union _Uim1dlLdCtl						Uim1dlLdCtl;
typedef union _Uim1dlLdPrefetch				Uim1dlLdPrefetch;
typedef union _Uim1dlLdHsize					Uim1dlLdHsize;
typedef union _Uim1dlLdVsize					Uim1dlLdVsize;
typedef union _Uim1dlLdPhsz						Uim1dlLdPhsz;
typedef union _Uim1dlLdPvsz						Uim1dlLdPvsz;
typedef union _Uim1dlUplkTarget				Uim1dlUplkTarget;
typedef union _Uim1dlDwlkTarget				Uim1dlDwlkTarget;
typedef union _Uim1dlLknum						Uim1dlLknum;
typedef union _Uim1dlRing							Uim1dlRing;
typedef struct _Tim1dlDump						Tim1dlDump;
typedef union _UimBlendBlendtopcnf0		UimBlendBlendtopcnf0;
typedef union _UimBlendBlendtopcnf1		UimBlendBlendtopcnf1;
typedef union _UimBlendBlendtopcnf2		UimBlendBlendtopcnf2;
typedef union _UimBlendBlendctl				UimBlendBlendctl;
typedef union _UimBlendAlphactl0			UimBlendAlphactl0;
typedef union _UimBlendAlphactl1			UimBlendAlphactl1;
typedef union _UimBlendAlphactl2			UimBlendAlphactl2;
typedef union _UimBlendWaddctl				UimBlendWaddctl;
typedef union _UimBlendDivctl0					UimBlendDivctl0;
typedef union _UimBlendMskctl0				UimBlendMskctl0;
typedef union _UimBlendMulctl					UimBlendMulctl;
typedef struct _TimBlendDump					TimBlendDump;
typedef union _UimCflowDiffCftopconf		UimCflowDiffCftopconf;
typedef union _UimCflowDiffPrewait			UimCflowDiffPrewait;
typedef union _UimCflowDiffPostwait		UimCflowDiffPostwait;
typedef union _UimCflowMagpow				UimCflowMagpow;
typedef union _UimCflowCfmode				UimCflowCfmode;
typedef struct _TimCflowDump					TimCflowDump;
typedef union _UimCscCsctopcnf				UimCscCsctopcnf;
typedef union _UimCscCsck							UimCscCsck;
typedef union _UimCscMdsel						UimCscMdsel;
typedef union _UimCscAlpsel						UimCscAlpsel;
typedef union _UimCscAlpval						UimCscAlpval;
typedef union _UimCscMaxmin					UimCscMaxmin;
typedef union _UimCscOutclip					UimCscOutclip;
typedef struct _TimCscDump						TimCscDump;

typedef struct _ImIipManyRegister				ImIipManyRegister;
typedef struct _ImIipManyRegisterClass		ImIipManyRegisterClass;
typedef struct _ImIipManyRegisterPrivate 		ImIipManyRegisterPrivate;



///////////////////////////////////////////////////////////////
// 1D UNIT Register
///////////////////////////////////////////////////////////////
/** structure of ldTopcnf0 (0004h) */
union _Uim1dlLdTopcnf0
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< waitconf<br>Refer to @ref EimPortid. */
		gulong waitconf :6;
		gulong :26;
	} bit;
} ;

/** structure of ldTopcnf1 (0008h) */
union _Uim1dlLdTopcnf1
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< linkUid<br>Refer to @ref EimPortid. */
		gulong linkUid :6;
		gulong :26;
	} bit;
} ;

/** structure of pixiddef	(0010h) */
union _Uim1dlPixiddef
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		gulong :2;
		gulong :2;
		/**< ipixid */
		gulong ipixid :4;
		gulong :24;
	} bit;
} ;

/** structure of ldCtl (0014h) */
union _Uim1dlLdCtl
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< ldMode<br>Refer to @ref EimLdMode. */
		gulong ldMode :2;
		gulong :2;
		/**< ldOut */
		gulong ldOut :2;
		gulong :2;
		/**< slow<br>Refer to @ref EimSlow. */
		gulong slow :1;
		gulong :3;
		/**< saverd */
		gulong saverd :2;
		gulong :2;
		/**< csel<br>Refer to @ref EimCsel */
		gulong csel :2;
		gulong :14;
	} bit;
} ;

/** structure of ldPrefetch	(0018h) */
union _Uim1dlLdPrefetch
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< pfoff<br>Refer to @ref EimPfoff. */
		gulong pfoff :1;
		/**< pfPdist<br>Refer to @ref EimPfPdist. */
		gulong pfPdist :2;
		/**< pf1st<br>Refer to @ref EimPf1st. */
		gulong pf1st :1;
		gulong :1;
		gulong :3;
		gulong :2;
		gulong :2;
		gulong :1;
		gulong :3;
		/**< pfbNum */
		gulong pfbNum :5;
		gulong :3;
		/**< pfAdd */
		gulong pfAdd :5;
		gulong :3;
	} bit;
} ;

/** structure of ldHsize	(0020h) */
union _Uim1dlLdHsize
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< hstart */
		gulong hstart :14;
		gulong :2;
		/**< hend */
		gulong hend :14;
		gulong :2;
	} bit;
} ;

/** structure of ldVsize	(0024h) */
union _Uim1dlLdVsize
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< vstart */
		gulong vstart :14;
		gulong :2;
		/**< vend */
		gulong vend :14;
		gulong :2;
	} bit;
} ;

/** structure of ldPhsz	(0028h) */
union _Uim1dlLdPhsz
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< phsz0 */
		gulong phsz0 :14;
		gulong :2;
		/**< phsz1 */
		gulong phsz1 :14;
		gulong :2;
	} bit;
} ;

/** structure of ldPvsz	(002Ch) */
union _Uim1dlLdPvsz
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< pvsz0 */
		gulong pvsz0 :14;
		gulong :2;
		/**< pvsz1 */
		gulong pvsz1 :14;
		gulong :2;
	} bit;
} ;

/** structure of uplkTarget	(0030h) */
union _Uim1dlUplkTarget
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< upsu0<br>Refer to @ref EimUpsu. */
		gulong upsu0 :4;
		gulong :4;
		/**< upsu1<br>Refer to @ref EimUpsu. */
		gulong upsu1 :4;
		gulong :4;
		/**< upsu2 */
		gulong upsu2 :4;
		gulong :12;
	} bit;
} ;

/** structure of dwlkTarget	(0034h) */
union _Uim1dlDwlkTarget
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< dwsu0<br>Refer to @ref EimDwsu. */
		gulong dwsu0 :4;
		gulong :4;
		/**< dwsu1<br>Refer to @ref EimDwsu. */
		gulong dwsu1 :4;
		gulong :4;
		/**< dwsu2 */
		gulong dwsu2 :4;
		gulong :12;
	} bit;
} ;

/** structure of lknum	(0038h) */
union _Uim1dlLknum
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< upnum<br>Refer to @ref EimUpnum. */
		gulong upnum :2;
		gulong :2;
		/**< dwnum<br>Refer to @ref EimDwnum. */
		gulong dwnum :2;
		gulong :26;
	} bit;
} ;

/** structure of ring	(003Ch) */
union _Uim1dlRing
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< uringsize */
		gulong uringsize :8;
		/**< umarginiysz */
		gulong umarginiysz :4;
		gulong :4;
		/**< dringsize */
		gulong dringsize :8;
		gulong :8;
	} bit;
} ;

/** Define i/o mapping */
struct _Tim1dlDump
{
	/**< (0000 - 0003h) */
	guchar dmy00000003[0x0004 - 0x0000];
	/**< (0004 - 0007h) */
	Uim1dlLdTopcnf0 ldTopcnf0;
	/**< (0008 - 000Bh) */
	Uim1dlLdTopcnf1 ldTopcnf1;
	/**< (000C - 000Fh) */
	guchar dmy000c000f[0x0010 - 0x000C];
	/**< (0010 - 0013h) */
	Uim1dlPixiddef pixiddef;
	/**< (0014 - 0017h) */
	Uim1dlLdCtl ldCtl;
	/**< (0018 - 001Bh) */
	Uim1dlLdPrefetch ldPrefetch;
	/**< (001C - 001Fh) */
	guchar dmy001c001f[0x0020 - 0x001C];
	/**< (0020 - 0023h) */
	Uim1dlLdHsize ldHsize;
	/**< (0024 - 0027h) */
	Uim1dlLdVsize ldVsize;
	/**< (0028 - 002Bh) */
	Uim1dlLdPhsz ldPhsz;
	/**< (002C - 002Fh) */
	Uim1dlLdPvsz ldPvsz;
	/**< (0030 - 0033h) */
	Uim1dlUplkTarget uplkTarget;
	/**< (0034 - 0037h) */
	Uim1dlDwlkTarget dwlkTarget;
	/**< (0038 - 003Bh) */
	Uim1dlLknum lknum;
	/**< (003C - 003Fh) */
	Uim1dlRing ring;
	/**< 0040 - FFFFh */
	guchar dmy000400ffff[0x10000 - 0x00040];
} ;

///////////////////////////////////////////////////////////////
// BLEND UNIT Register
///////////////////////////////////////////////////////////////
/** structure of blendtopcnf0	(0000h) */
union _UimBlendBlendtopcnf0
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< waitconf0<br>Refer to @ref EimPortid. */
		gulong waitconf0 :6;
		gulong :2;
		gulong :8;
		/**< dataconf0<br>Refer to @ref EimPortid. */
		gulong dataconf0 :6;
		gulong :10;
	} bit;
} ;

/** structure of blendtopcnf1	(0004h) */
union _UimBlendBlendtopcnf1
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< waitconf1<br>Refer to @ref EimPortid. */
		gulong waitconf1 :6;
		gulong :2;
		gulong :8;
		/**< dataconf1<br>Refer to @ref EimPortid. */
		gulong dataconf1 :6;
		gulong :10;
	} bit;
} ;

/** structure of blendtopcnf2	(0008h) */
union _UimBlendBlendtopcnf2
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		gulong :16;
		/**< dataconf2<br>Refer to @ref EimPortid. */
		gulong dataconf2 :6;
		gulong :10;
	} bit;
} ;

/** structure of blendctl	(0080h) */
union _UimBlendBlendctl
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< bldMd<br>Refer to @ref EimBldMd. */
		gulong bldMd :3;
		gulong :1;
		/**< clpMd<br>Refer to @ref EimClpMd. */
		gulong clpMd :2;
		gulong :2;
		/**< alphaOut<br>Refer to @ref EimAlphaOut. */
		gulong alphaOut :2;
		gulong :22;
	} bit;
} ;

/** structure of alphactl0	(0088h) */
union _UimBlendAlphactl0
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< alphaStep<br>Refer to @ref EimAlphaStep. */
		gulong alphaStep :2;
		gulong :2;
		/**< alphaSel<br>Refer to @ref EimAlphaSel. */
		gulong alphaSel :3;
		gulong :25;
	} bit;
} ;

/** structure of alphactl1	(008Ch) */
union _UimBlendAlphactl1
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< alphaVal0 */
		gulong alphaVal0 :8;
		gulong :8;
		/**< alphaVal1 */
		gulong alphaVal1 :8;
		gulong :8;
	} bit;
} ;

/** structure of alphactl2	(0090h) */
union _UimBlendAlphactl2
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< alphaVal2 */
		gulong alphaVal2 :8;
		gulong :8;
		/**< alphaVal3 */
		gulong alphaVal3 :8;
		gulong :8;
	} bit;
} ;

/** structure of WADDCTL0	(0098h)
	structure of WADDCTL1	(009Ch)
	structure of WADDCTL2	(00A0h)
	structure of WADDCTL3	(00A4h) */
union _UimBlendWaddctl
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< WADD_KA0<br>WADD_KA1<br>WADD_KA2<br>WADD_KA3 */
		gs64 waddKa :13;
		gulong :3;
		/**< WADD_KB0<br>WADD_KB1<br>WADD_KB2<br>WADD_KB3 */
		gs64 waddKb :13;
		gulong :3;
	} bit;
} ;

/** structure of divctl0	(00ACh) */
union _UimBlendDivctl0
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< rsft */
		gulong rsft :4;
		gulong :28;
	} bit;
} ;

/** structure of mskctl0	(00B4h) */
union _UimBlendMskctl0
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< msksel */
		gulong msksel :1;
		gulong :3;
		/**< dinsel */
		gulong dinsel :1;
		gulong :27;
	} bit;
} ;

/** structure of MULCTL0	(00BCh)
	structure of MULCTL1	(00C0h)
	structure of MULCTL2	(00C4h)
	structure of MULCTL3	(00C8h)
	structure of MULCTL4	(00CCh)
	structure of MULCTL5	(00D0h)
	structure of MULCTL6	(00D4h)
	structure of MULCTL7	(00D8h) */
union _UimBlendMulctl
{
	/**< All bits */
	gulong word[2];
	/**< bit field */
	struct {
		/**< ADDVAL_A0<br>ADDVAL_A1<br>ADDVAL_A2<br>ADDVAL_A3 */
		gs64 addvalA :15;
		gulong :1;
		/**< ADDVAL_B0<br>ADDVAL_B1<br>ADDVAL_B2<br>ADDVAL_B3 */
		gs64 addvalB :15;
		gulong :1;
		/**< ADDVAL_C0<br>ADDVAL_C1<br>ADDVAL_C2<br>ADDVAL_C3 */
		gs64 addvalC :15;
		gulong :1;
		/**< SFTSEL0<br>SFTSEL1<br>SFTSEL2<br>SFTSEL3<br>Refer to @ref EimSftsel */
		gulong sftsel :2;
		gulong :14;
	} bit;
} ;

/** Define i/o mapping */
struct _TimBlendDump
{
	/**< (0000 - 0003h) */
	UimBlendBlendtopcnf0 blendtopcnf0;
	/**< (0004 - 0007h) */
	UimBlendBlendtopcnf1 blendtopcnf1;
	/**< (0008 - 000Bh) */
	UimBlendBlendtopcnf2 blendtopcnf2;
	/**< (000C - 007Fh) */
	guchar dmy000c007f[0x0080 - 0x000C];
	/**< (0080 - 0083h) */
	UimBlendBlendctl blendctl;
	/**< (0084 - 0087h) */
	guchar dmy00840087[0x0088 - 0x0084];
	/**< (0088 - 008Bh) */
	UimBlendAlphactl0 alphactl0;
	/**< (008C - 008Fh) */
	UimBlendAlphactl1 alphactl1;
	/**< (0090 - 0093h) */
	UimBlendAlphactl2 alphactl2;
	/**< (0094 - 0097h) */
	guchar dmy00940097[0x0098 - 0x0094];
	/**< (0098 - 00A7h) */
	UimBlendWaddctl waddctl[4];
	/**< (00A8 - 00ABh) */
	guchar dmy00a800ab[0x00AC - 0x00A8];
	/**< (00AC - 00AFh) */
	UimBlendDivctl0 divctl0;
	/**< (00B0 - 00B3h) */
	guchar dmy00b000b3[0x00B4 - 0x00B0];
	/**< (00B4 - 00B7h) */
	UimBlendMskctl0 mskctl0;
	/**< (00B8 - 00BBh) */
	guchar dmy_00B8_00BB[0x00BC - 0x00B8];
	/**< (00BC - 00DBh) */
	UimBlendMulctl mulctl[4];
	/**< 00DC - FFFFh */
	guchar dmy200dc2ffff[0x30000 - 0x200DC];
} ;

///////////////////////////////////////////////////////////////
// CFC UNIT Register
///////////////////////////////////////////////////////////////
/** structure of cftopconf	(0000h) */
union _UimCflowDiffCftopconf
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< dataconf0<br>Refer to @ref EimPortid. */
		gulong dataconf0 :6;
		gulong :2;
		/**< dataconf1<br>Refer to @ref EimPortid. */
		gulong dataconf1 :6;
		gulong :18;
	} bit;
} ;

/** structure of diffPrewait	(0010h) */
union _UimCflowDiffPrewait
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< diffPrewait */
		gulong diffPrewait :19;
		gulong :13;
	} bit;
} ;

/** structure of diffPostwait	(0014h) */
union _UimCflowDiffPostwait
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< diffPostwait */
		gulong diffPostwait :19;
		gulong :13;
	} bit;
} ;

/** structure of magpow (0018h) */
union _UimCflowMagpow
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< premag */
		gulong premag :7;
		gulong :1;
		/**< postmag */
		gulong postmag :7;
		gulong :17;
	} bit;
} ;

/** structure of cfmode (001Ch) */
union _UimCflowCfmode
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< spcOn */
		gulong spcOn :1;
		gulong :31;
	} bit;
} ;

/** Define i/o mapping */
struct _TimCflowDump
{
	/**< (0000 - 0003h) */
	UimCflowDiffCftopconf cftopconf;
	/**< (0004 - 000Fh) */
	guchar dmy0004000f[0x0010 - 0x0004];
	/**< (0010 - 0013h) */
	UimCflowDiffPrewait diffPrewait;
	/**< (0014 - 0017h) */
	UimCflowDiffPostwait diffPostwait;
	/**< (0018 - 001Bh) */
	UimCflowMagpow magpow;
	/**< (001C - 001Fh) */
	UimCflowCfmode cfmode;
	/**< 0020 - FFFFh */
	guchar dmy300203ffff[0x40000 - 0x30020];
} ;

///////////////////////////////////////////////////////////////
// CSC UNIT Register
///////////////////////////////////////////////////////////////
/** structure of csctopcnf	(0000h) */
union _UimCscCsctopcnf
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< waitconf<br>Refer to @ref EimPortid. */
		gulong waitconf :6;
		gulong :2;
		gulong :8;
		/**< dataconf<br>Refer to @ref EimPortid. */
		gulong dataconf :6;
		gulong :10;
	} bit;
} ;

/** structure of csck  (0020h) */
union _UimCscCsck
{
	/**< All bits */
	gulong word[2];
	/**< bit field */
	struct {
		/**< csck[n][0] (0020h) */
		gs64 csck0 :15;
		gulong :1;
		/**< csck[n][1] (0022h) */
		gs64 csck1 :15;
		gulong :1;
		/**< csck[n][2] (0024h) */
		gs64 csck2 :15;
		gulong :1;
		/**< csck[n][3] (0026h) */
		gs64 csck3 :15;
		gulong :1;
	} bit;
} ;

/** structure of mdsel	(0040h) */
union _UimCscMdsel
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< mdsel */
		gulong mdsel :2;
		gulong :30;
	} bit;
} ;

/** structure of alpsel (0044h) */
union _UimCscAlpsel
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< alpsel<br>Refer to @ref EimAlpsel. */
		gulong alpsel :1;
		gulong :3;
		/**< alosel<br>Refer to @ref EimAlosel. */
		gulong alosel :1;
		gulong :27;
	} bit;
} ;

/** structure of alpval (0048h) */
union _UimCscAlpval
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< alpval */
		gs64 alpval :15;
		gulong :17;
	} bit;
} ;

/** structure of maxmin (004Ch) */
union _UimCscMaxmin
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< maxmin0<br>Refer to @ref EimMaxmin. */
		gulong maxmin0 :2;
		gulong :2;
		/**< maxmin1<br>Refer to @ref EimMaxmin. */
		gulong maxmin1 :2;
		gulong :2;
		/**< maxmin2<br>Refer to @ref EimMaxmin. */
		gulong maxmin2 :2;
		gulong :2;
		/**< maxmin3<br>Refer to @ref EimMaxmin. */
		gulong maxmin3 :2;
		gulong :18;
	} bit;
} ;

/** structure of outclip	(0050h) */
union _UimCscOutclip
{
	/**< All bits */
	gulong word[4];
	/**< bit field */
	struct {
		/**< clpmax0 */
		gs64 clpmax0 :15;
		gulong :1;
		/**< clpmin0 */
		gs64 clpmin0 :15;
		gulong :1;
		/**< clpmax1 */
		gs64 clpmax1 :15;
		gulong :1;
		/**< clpmin1 */
		gs64 clpmin1 :15;
		gulong :1;
		/**< clpmax2 */
		gs64 clpmax2 :15;
		gulong :1;
		/**< clpmin2 */
		gs64 clpmin2 :15;
		gulong :1;
		/**< clpmax3 */
		gs64 clpmax3 :9;
		gulong :7;
		/**< clpmin3 */
		gs64 clpmin3 :9;
		gulong :7;
	} bit;
} ;

/** Define i/o mapping */
struct _TimCscDump
{
	/**< (0000 - 0003h) */
	UimCscCsctopcnf csctopcnf;
	/**< (0004 - 001Fh) */
	guchar dmy0004001f[0x0020 - 0x0004];
	/**< (0020 - 003Fh) */
	UimCscCsck csck[4];
	/**< (0040 - 0043h) */
	UimCscMdsel mdsel;
	/**< (0044 - 0047h) */
	UimCscAlpsel alpsel;
	/**< (0048 - 004Bh) */
	UimCscAlpval alpval;
	/**< (004C - 004Fh) */
	UimCscMaxmin maxmin;
	/**< (0050 - 005Fh) */
	UimCscOutclip outclip;
	/**< 0060 - FFFFh */
	guchar dmy400604ffff[0x50000 - 0x40060];
} ;


struct _ImIipManyRegister
{
	GObject parent;
};

struct _ImIipManyRegisterClass
{
	GObjectClass parentClass;
};


GType								im_iip_many_register_struct_get_type(void)	G_GNUC_CONST;
ImIipManyRegister*		im_iip_many_register_struct_new(void);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_IIP_MANY_REGISTER_H__ */
