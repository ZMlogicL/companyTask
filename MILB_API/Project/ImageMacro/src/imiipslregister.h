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


#ifndef __IM_IIP_SL_REGISTER_H__
#define __IM_IIP_SL_REGISTER_H__


#include <stdio.h>
#include <glib-object.h>
#include "imiipfltregister.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_SL_REGISTER							(im_iip_sl_register_struct_get_type ())
#define IM_IIP_SL_REGISTER(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_IIP_SL_REGISTER, ImIipSlRegister))
#define IM_IIP_SL_REGISTER_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_IIP_SL_REGISTER, ImIipSlRegisterClass))
#define IM_IS_IIP_SL_REGISTER(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_IIP_SL_REGISTER))
#define IM_IS_IIP_SL_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_IIP_SL_REGISTER))
#define IM_IIP_SL_REGISTER_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_IIP_SL_REGISTER, ImIipSlRegisterClass))


typedef union _UimStsSlTopcnf0		UimStsSlTopcnf0;
typedef union _UimStsPixiddef		UimStsPixiddef;
typedef union _UimStsPldunitSl		UimStsPldunitSl;
typedef union _UimStsSlCtl				UimStsSlCtl;
typedef union _UimStsOutcol			UimStsOutcol;
typedef union _UimStsSlHsize			UimStsSlHsize;
typedef union _UimStsSlVsize			UimStsSlVsize;
typedef union _UimStsSlPhsz			UimStsSlPhsz;
typedef union _UimStsSlPvsz			UimStsSlPvsz;
typedef union _UimStsSelOpara		UimStsSelOpara;
typedef union _UimStsOfset			UimStsOfset;
typedef union _UimStsClpthU			UimStsClpthU;
typedef union _UimStsClpthL			UimStsClpthL;
typedef union _UimStsClpvalU		UimStsClpvalU;
typedef union _UimStsClpvalL			UimStsClpvalL;
typedef union _UimStsSft					UimStsSft;
typedef union _UimStsW14md		UimStsW14md;
typedef union _UimStsFillEn				UimStsFillEn;
typedef union _UimStsFillData		UimStsFillData;
typedef union _UimStsFillSize			UimStsFillSize;
typedef struct _TimStsDump			TimStsDump;

typedef struct _ImIipSlRegister			ImIipSlRegister;
typedef struct _ImIipSlRegisterClass		ImIipSlRegisterClass;
typedef struct _ImIipSlRegisterPrivate 		ImIipSlRegisterPrivate;


///////////////////////////////////////////////////////////////
// SL UNIT Register
///////////////////////////////////////////////////////////////
/** structure of slTopcnf0 (0000h) */
union _UimStsSlTopcnf0
{
		/**< All bits */
		gulong word;
		struct {
			/**< waitconf<br>Refer to @ref EimPortid. */
			gulong waitconf :6;
			gulong :2;
			gulong :8;
			/**< dataconf<br>Refer to @ref EimPortid. */
			gulong dataconf :6;
			gulong :10;
		} bit;
};

/** structure of pixiddef	(0004h) */
union _UimStsPixiddef
{
		/**< All bits */
		gulong word;
		struct {
			/**< opixid */
			gulong opixid :4;
			gulong :4;
			/**< csel<br>Refer to @ref EimCsel */
			gulong csel :2;
			gulong :2;
			gulong :1;
			gulong :3;
			/**< div1st<br>Refer to @ref EimDiv1st. */
			gulong div1st :1;
			gulong :3;
			/**< lkdiv */
			gulong lkdiv :2;
			gulong :10;
		} bit;
};

/** structure of pldunitSl (0008h) */
union _UimStsPldunitSl
{
		 /**< All bits */
		gulong word[2];
		struct {
			/**< pldunitSlLo<br>Lower 32bit of D_IM_IIP_PARAM_PLDUNIT_xxx */
			gulong pldunitSlLo :32
			/**< pldunitSlHi<br>Upper 32bit of D_IM_IIP_PARAM_PLDUNIT_xxx */;
			gulong pldunitSlHi :32;
		} bit;
};

/** structure of slCtl (0010h) */
union _UimStsSlCtl
{
		/**< All bits */
		gulong word;
		struct {
			/**< slMode */
			gulong slMode :3;
			gulong :1;
			/**< loadmd */
			gulong loadmd :1;
			gulong :3;
			/**< masken<br>Refer to @ref EimMasken. */
			gulong masken :2;
			gulong :22;
		} bit;
};

/** structure of outcol (0014h) */
union _UimStsOutcol
{
		/**< All bits */
		gulong word;
		struct {
			/**< outcol */
			gulong outcol :4;
			gulong :28;
		} bit;
};

/** structure of slHsize	(0020h) */
union _UimStsSlHsize
{
		 /**< All bits */
		gulong word;
		struct {
			/**< hstart */
			gulong hstart :14;
			gulong :2;
			/**< hend */
			gulong hend :14;
			gulong :2;
		} bit;
};

/** structure of slVsize	(0024h) */
union _UimStsSlVsize
{
		/**< All bits */
		gulong word;
		struct {
			/**< vstart */
			gulong vstart :14;
			gulong :2;
			/**< vend */
			gulong vend :14;
			gulong :2;
		} bit;
};

/** structure of slPhsz	(0028h) */
union _UimStsSlPhsz
{
		/**< All bits */
		gulong word;
		struct {
			/**< phsz0 */
			gulong phsz0 :14;
			gulong :2;
			/**< phsz1 */
			gulong phsz1 :14;
			gulong :2;
		} bit;
};

/** structure of slPvsz	(002Ch) */
union _UimStsSlPvsz
{
		 /**< All bits */
		gulong word;
		struct {
			/**< pvsz0 */
			gulong pvsz0 :14;
			gulong :2;
			/**< pvsz1 */
			gulong pvsz1 :14;
			gulong :2;
		} bit;
};

/** structure of selOpara	(0040h) */
union _UimStsSelOpara
{
		/**< All bits */
		gulong word;
		struct {
			/**< selOpara */
			gulong selOpara :4;
			gulong :28;
		} bit;
};

/** structure of ofset0	(0048h)	structure of ofset1	(0064h) */
union _UimStsOfset
{
		 /**< All bits */
		gulong word;
		struct {
			/**< ofset0<br>ofset1 */
			gs64 ofset :15;
			gulong :17;
		} bit;
};

/** structure of clpthU0	(004Ch)	structure of clpthU1	(0068h) */
union _UimStsClpthU
{
		/**< All bits */
		gulong word;
		struct {
			/**< clpthU0<br>clpthU1 */
			gs64 clpthU :15;
			gulong :17;
		} bit;
};

/** structure of clpthL0	(0050h)	structure of clpthL1	(006Ch) */
union _UimStsClpthL
{
		/**< All bits */
		gulong word;
		struct {
			/**< clpthL0<br>clpthL1 */
			gs64 clpthL :15;
			gulong :17;
		} bit;
};

/** structure of clpvalU0 (0054h)	structure of clpvalU1 (0070h) */
union _UimStsClpvalU
{
		/**< All bits */
		gulong word;
		struct {
			/**< clpvalU0<br>clpvalU1 */
			gs64 clpvalU :15;
			gulong :17;
		} bit;
};

/** structure of clpvalL0 (0058h)	structure of clpvalL1 (0074h) */
union _UimStsClpvalL
{
		/**< All bits */
		gulong word;
		struct {
			/**< clpvalL0<br>clpvalL1 */
			gs64 clpvalL :15;
			gulong :17;
		} bit;
};

/** structure of sft0	(005Ch)	structure of sft1	(0078h) */
union _UimStsSft
{
		/**< All bits */
		gulong word;
		struct {
			/**< SFTM_0<br>SFTM_1<br>Refer to @ref EimSftm. */
			gulong sftm :1;
			gulong :3;
			/**< SFTVAL_0<br>SFTVAL_1 */
			gulong sftval :4;
			gulong :24;
		} bit;
};

/** structure of w14md0	(0060h)	structure of w14md1	(007Ch) */
union _UimStsW14md
{
		/**< All bits */
		gulong word;
		struct {
			/**< W14LSFT0<br>W14LSFT1 */
			gulong w14lsft :2;
			gulong :2;
			gulong w14sat :2;
			gulong :26;
		} bit;
};

/** structure of fillEn	(0200h) */
union _UimStsFillEn
{
		/**< All bits */
		gulong word;
		struct {
			/**< fillEn0<br>Refer to @ref EimFillEn. */
			gulong fillEn0 :1;
			gulong fillEn1 :1;
			gulong fillEn2 :1;
			gulong fillEn3 :1;
			gulong fillEn4 :1;
			gulong fillEn5 :1;
			gulong fillEn6 :1;
			gulong fillEn7 :1;
			gulong fillEn8 :1;
			gulong fillEn9 :1;
			/**< fillEn10<br>Refer to @ref EimFillEn. */
			gulong fillEn10 :1;
			gulong fillEn11 :1;
			gulong fillEn12 :1;
			gulong fillEn13 :1;
			gulong fillEn14 :1;
			gulong fillEn15 :1;
			gulong fillEn16 :1;
			gulong fillEn17 :1;
			gulong fillEn18 :1;
			gulong fillEn19 :1;
			gulong :12;
		} bit;
};

/** structure of fillData	(0204h) */
union _UimStsFillData
{
		/**< All bits */
		gulong word;
		struct {
				/**< fillD0 */
			gulong fillD0 :8;
			gulong fillD1 :8;
			gulong fillD2 :8;
			gulong :8;
		} bit;
};

/** structure of fillsize	(0300h) */
union _UimStsFillSize
{
		/**< All bits */
		gulong word[2];
		struct {
			/**< FILL_HSTA_0~19 */
			gulong fillHsta :14;
			gulong :2;
			gulong fillHend :14;
			gulong :2;
			gulong fillVsta :14;
			gulong :2;
			gulong fillVend :14;
			gulong :2;
		} bit;
};

/** Define i/o mapping */
struct _TimStsDump
{
		/**< (0000 - 0003h) */
		UimStsSlTopcnf0 slTopcnf0;
		UimStsPixiddef pixiddef;
		UimStsPldunitSl pldunitSl;
		UimStsSlCtl slCtl;
		UimStsOutcol outcol;
		/**< (0018 - 001Fh) */
		guchar dmy0018001f[0x0020 - 0x0018];
		/**< (0020 - 0023h) */
		UimStsSlHsize slHsize;
		UimStsSlVsize slVsize;
		UimStsSlPhsz slPhsz;
		UimStsSlPvsz slPvsz;
		/**< (0030 - 003Fh) */
		guchar dmy0030003f[0x0040 - 0x0030];
		/**< (0040 - 0043h) */
		UimStsSelOpara selOpara;
		/**< (0044 - 0047h) */
		guchar dmy00440047[0x0048 - 0x0044];
		/**< (0048 - 004Bh) */
		UimStsOfset ofset0;
		UimStsClpthU clpthU0;
		UimStsClpthL clpthL0;
		UimStsClpvalU clpvalU0;
		UimStsClpvalL clpvalL0;
		UimStsSft sft0;
		UimStsW14md w14md0;
		UimStsOfset ofset1;
		UimStsClpthU clpthU1;
		UimStsClpthL clpthL1;
		UimStsClpvalU clpvalU1;
		UimStsClpvalL clpvalL1;
		UimStsSft sft1;
		UimStsW14md w14md1;
		/**< (0080 - 01FFh) */
		guchar dmy008001ff[0x0200 - 0x0080];
		/**< (0200 - 0203h) */
		UimStsFillEn fillEn;
		/**< (0204 - 0207h) */
		UimStsFillData fillData;
		/**< (0208 - 02FFh) */
		guchar dmy020802ff[0x0300 - 0x0208];
		/**< (0300 - 039Fh) */
		UimStsFillSize fillsize[20];
		/**< 03A0 - FFFFh */
		guchar dmyB03a0Bffff[0xC0000 - 0xB03A0];
};

struct _ImIipSlRegister
{
	GObject parent;
};

struct _ImIipSlRegisterClass
{
	GObjectClass parentClass;
};


GType										im_iip_sl_register_struct_get_type(void)	G_GNUC_CONST;
ImIipSlRegister*					im_iip_sl_register_struct_new(void);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_IIP_SL_REGISTER_H__ */
