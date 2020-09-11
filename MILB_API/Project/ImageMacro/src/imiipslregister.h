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


#include <klib.h>
#include "imiipfltregister.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_SL_REGISTER					(im_iip_sl_register_get_type())
#define IM_IIP_SL_REGISTER(obj)						(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipSlRegister))
#define IM_IS_IIP_SL_REGISTER(obj)				(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_SL_REGISTER))


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

typedef struct _ImIipSlRegister 						ImIipSlRegister;
typedef struct _ImIipSlRegisterPrivate 			ImIipSlRegisterPrivate;


///////////////////////////////////////////////////////////////
// SL UNIT Register
///////////////////////////////////////////////////////////////
/** structure of slTopcnf0 (0000h) */
union _UimStsSlTopcnf0
{
		/**< All bits */
		kulong word;
		struct {
			/**< waitconf<br>Refer to @ref EimPortid. */
			kulong waitconf :6;
			kulong :2;
			kulong :8;
			/**< dataconf<br>Refer to @ref EimPortid. */
			kulong dataconf :6;
			kulong :10;
		} bit;
};

/** structure of pixiddef	(0004h) */
union _UimStsPixiddef
{
		/**< All bits */
		kulong word;
		struct {
			/**< opixid */
			kulong opixid :4;
			kulong :4;
			/**< csel<br>Refer to @ref EimCsel */
			kulong csel :2;
			kulong :2;
			kulong :1;
			kulong :3;
			/**< div1st<br>Refer to @ref EimDiv1st. */
			kulong div1st :1;
			kulong :3;
			/**< lkdiv */
			kulong lkdiv :2;
			kulong :10;
		} bit;
};

/** structure of pldunitSl (0008h) */
union _UimStsPldunitSl
{
		 /**< All bits */
		kulong word[2];
		struct {
			/**< pldunitSlLo<br>Lower 32bit of D_IM_IIP_PARAM_PLDUNIT_xxx */
			kulong pldunitSlLo :32
			/**< pldunitSlHi<br>Upper 32bit of D_IM_IIP_PARAM_PLDUNIT_xxx */;
			kulong pldunitSlHi :32;
		} bit;
};

/** structure of slCtl (0010h) */
union _UimStsSlCtl
{
		/**< All bits */
		kulong word;
		struct {
			/**< slMode */
			kulong slMode :3;
			kulong :1;
			/**< loadmd */
			kulong loadmd :1;
			kulong :3;
			/**< masken<br>Refer to @ref EimMasken. */
			kulong masken :2;
			kulong :22;
		} bit;
};

/** structure of outcol (0014h) */
union _UimStsOutcol
{
		/**< All bits */
		kulong word;
		struct {
			/**< outcol */
			kulong outcol :4;
			kulong :28;
		} bit;
};

/** structure of slHsize	(0020h) */
union _UimStsSlHsize
{
		 /**< All bits */
		kulong word;
		struct {
			/**< hstart */
			kulong hstart :14;
			kulong :2;
			/**< hend */
			kulong hend :14;
			kulong :2;
		} bit;
};

/** structure of slVsize	(0024h) */
union _UimStsSlVsize
{
		/**< All bits */
		kulong word;
		struct {
			/**< vstart */
			kulong vstart :14;
			kulong :2;
			/**< vend */
			kulong vend :14;
			kulong :2;
		} bit;
};

/** structure of slPhsz	(0028h) */
union _UimStsSlPhsz
{
		/**< All bits */
		kulong word;
		struct {
			/**< phsz0 */
			kulong phsz0 :14;
			kulong :2;
			/**< phsz1 */
			kulong phsz1 :14;
			kulong :2;
		} bit;
};

/** structure of slPvsz	(002Ch) */
union _UimStsSlPvsz
{
		 /**< All bits */
		kulong word;
		struct {
			/**< pvsz0 */
			kulong pvsz0 :14;
			kulong :2;
			/**< pvsz1 */
			kulong pvsz1 :14;
			kulong :2;
		} bit;
};

/** structure of selOpara	(0040h) */
union _UimStsSelOpara
{
		/**< All bits */
		kulong word;
		struct {
			/**< selOpara */
			kulong selOpara :4;
			kulong :28;
		} bit;
};

/** structure of ofset0	(0048h)	structure of ofset1	(0064h) */
union _UimStsOfset
{
		 /**< All bits */
		kulong word;
		struct {
			/**< ofset0<br>ofset1 */
			kint64 ofset :15;
			kulong :17;
		} bit;
};

/** structure of clpthU0	(004Ch)	structure of clpthU1	(0068h) */
union _UimStsClpthU
{
		/**< All bits */
		kulong word;
		struct {
			/**< clpthU0<br>clpthU1 */
			kint64 clpthU :15;
			kulong :17;
		} bit;
};

/** structure of clpthL0	(0050h)	structure of clpthL1	(006Ch) */
union _UimStsClpthL
{
		/**< All bits */
		kulong word;
		struct {
			/**< clpthL0<br>clpthL1 */
			kint64 clpthL :15;
			kulong :17;
		} bit;
};

/** structure of clpvalU0 (0054h)	structure of clpvalU1 (0070h) */
union _UimStsClpvalU
{
		/**< All bits */
		kulong word;
		struct {
			/**< clpvalU0<br>clpvalU1 */
			kint64 clpvalU :15;
			kulong :17;
		} bit;
};

/** structure of clpvalL0 (0058h)	structure of clpvalL1 (0074h) */
union _UimStsClpvalL
{
		/**< All bits */
		kulong word;
		struct {
			/**< clpvalL0<br>clpvalL1 */
			kint64 clpvalL :15;
			kulong :17;
		} bit;
};

/** structure of sft0	(005Ch)	structure of sft1	(0078h) */
union _UimStsSft
{
		/**< All bits */
		kulong word;
		struct {
			/**< SFTM_0<br>SFTM_1<br>Refer to @ref EimSftm. */
			kulong sftm :1;
			kulong :3;
			/**< SFTVAL_0<br>SFTVAL_1 */
			kulong sftval :4;
			kulong :24;
		} bit;
};

/** structure of w14md0	(0060h)	structure of w14md1	(007Ch) */
union _UimStsW14md
{
		/**< All bits */
		kulong word;
		struct {
			/**< W14LSFT0<br>W14LSFT1 */
			kulong w14lsft :2;
			kulong :2;
			kulong w14sat :2;
			kulong :26;
		} bit;
};

/** structure of fillEn	(0200h) */
union _UimStsFillEn
{
		/**< All bits */
		kulong word;
		struct {
			/**< fillEn0<br>Refer to @ref EimFillEn. */
			kulong fillEn0 :1;
			kulong fillEn1 :1;
			kulong fillEn2 :1;
			kulong fillEn3 :1;
			kulong fillEn4 :1;
			kulong fillEn5 :1;
			kulong fillEn6 :1;
			kulong fillEn7 :1;
			kulong fillEn8 :1;
			kulong fillEn9 :1;
			/**< fillEn10<br>Refer to @ref EimFillEn. */
			kulong fillEn10 :1;
			kulong fillEn11 :1;
			kulong fillEn12 :1;
			kulong fillEn13 :1;
			kulong fillEn14 :1;
			kulong fillEn15 :1;
			kulong fillEn16 :1;
			kulong fillEn17 :1;
			kulong fillEn18 :1;
			kulong fillEn19 :1;
			kulong :12;
		} bit;
};

/** structure of fillData	(0204h) */
union _UimStsFillData
{
		/**< All bits */
		kulong word;
		struct {
				/**< fillD0 */
			kulong fillD0 :8;
			kulong fillD1 :8;
			kulong fillD2 :8;
			kulong :8;
		} bit;
};

/** structure of fillsize	(0300h) */
union _UimStsFillSize
{
		/**< All bits */
		kulong word[2];
		struct {
			/**< FILL_HSTA_0~19 */
			kulong fillHsta :14;
			kulong :2;
			kulong fillHend :14;
			kulong :2;
			kulong fillVsta :14;
			kulong :2;
			kulong fillVend :14;
			kulong :2;
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
		kuchar dmy0018001f[0x0020 - 0x0018];
		/**< (0020 - 0023h) */
		UimStsSlHsize slHsize;
		UimStsSlVsize slVsize;
		UimStsSlPhsz slPhsz;
		UimStsSlPvsz slPvsz;
		/**< (0030 - 003Fh) */
		kuchar dmy0030003f[0x0040 - 0x0030];
		/**< (0040 - 0043h) */
		UimStsSelOpara selOpara;
		/**< (0044 - 0047h) */
		kuchar dmy00440047[0x0048 - 0x0044];
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
		kuchar dmy008001ff[0x0200 - 0x0080];
		/**< (0200 - 0203h) */
		UimStsFillEn fillEn;
		/**< (0204 - 0207h) */
		UimStsFillData fillData;
		/**< (0208 - 02FFh) */
		kuchar dmy020802ff[0x0300 - 0x0208];
		/**< (0300 - 039Fh) */
		UimStsFillSize fillsize[20];
		/**< 03A0 - FFFFh */
		kuchar dmyB03a0Bffff[0xC0000 - 0xB03A0];
};

struct _ImIipSlRegister
{
	KObject parent;
};


KConstType 		    			im_iip_sl_register_get_type(void);
ImIipSlRegister*		        im_iip_sl_register_new(void);


#ifdef __cplusplus
}
#endif


#endif /* __IM_IIP_SL_REGISTER_H__ */
