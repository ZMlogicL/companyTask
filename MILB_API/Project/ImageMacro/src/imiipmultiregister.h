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


#ifndef __IM_IIP_MULTI_REGISTER_H__
#define __IM_IIP_MULTI_REGISTER_H__


#include <klib.h>
#include "imiipmanyregister.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_MULTI_REGISTER							(im_iip_multi_register_get_type())
#define IM_IIP_MULTI_REGISTER(obj)								(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipMultiRegister))
#define IM_IS_IIP_MULTI_REGISTER(obj)						(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_MULTI_REGISTER))

typedef union _UimgpcGpctopcnf					UimgpcGpctopcnf;
typedef union _UimgpcGpccontrol					UimgpcGpccontrol;
typedef union _UimgpcGpccloadadr				UimgpcGpccloadadr;
typedef union _UimgpcGpcmon						UimgpcGpcmon;
typedef struct _TimgpcDump							TimgpcDump;

typedef union _UimLutLuttopcnf						UimLutLuttopcnf;
typedef union _UimLutLutunitctl						UimLutLutunitctl;
typedef union _UimLutLutctl							UimLutLutctl;
typedef union _UimLutLutprecal						UimLutLutprecal;
typedef struct _TimLutDump							TimLutDump;

typedef union _UimMftMfttopconf					UimMftMfttopconf;
typedef union _UimMftMftmd							UimMftMftmd;
typedef union _UimMftFlttpsz							UimMftFlttpsz;
typedef union _UimMftFltouthsz						UimMftFltouthsz;
typedef union _UimMftMftctl							UimMftMftctl;
typedef struct _TimMftDump							TimMftDump;

typedef union _UimMonMonctl						UimMonMonctl;
typedef union _UimMonMondsel					UimMonMondsel;
typedef union _UimMonHistctl						UimMonHistctl;
typedef union _UimMonAbsmax						UimMonAbsmax;
typedef union _UimMonAbsmin						UimMonAbsmin;
typedef union _UimMonAbsadd						UimMonAbsadd;
typedef union _UimMonOvervalue				UimMonOvervalue;
typedef struct _TimMonDump							TimMonDump;

typedef struct _ImIipMultiRegister 					ImIipMultiRegister;
typedef struct _ImIipMultiRegisterPrivate 	ImIipMultiRegisterPrivate;


///////////////////////////////////////////////////////////////
// GPC UNIT Register
///////////////////////////////////////////////////////////////
/** structure of gpctopcnf	(0000h) */
union _UimgpcGpctopcnf
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< waitconf0<br>waitconf1<br>Refer to @ref EimPortid. */
			kulong waitconf :6;
			kulong :2;
			kulong :8;
			/**< dataconf0<br>dataconf1<br>Refer to @ref EimPortid. */
			kulong dataconf :6;
			kulong :10;
		} bit;
} ;

/** structure of gpccontrol (0010h) */
union _UimgpcGpccontrol
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< commonpapa<br>Refer to @ref EimCommonpara. */
			kulong commonpapa :2;
			kulong :2;
			/**< md2dlk */
			kulong md2dlk :1;
			kulong :3;
			/**< alpen0 */
			kulong alpen0 :1;
			kulong :3;
			/**< alpen1 */
			kulong alpen1 :1;
			kulong :3;
			/**< atrb0<br>Refer to @ref EimAtrb */
			kulong atrb0 :4;
			/**< atrb1<br>Refer to @ref EimAtrb */
			kulong atrb1 :4;
			kulong :8;
		} bit;
} ;

/** structure of gpccloadadr	(0014h) */
union _UimgpcGpccloadadr
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< cloadadr */
			kulong cloadadr :32;
		} bit;
} ;
/** structure of gpcmon (0018h) */
union _UimgpcGpcmon
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< gpcrun */
			kulong gpcrun :1;
			kulong :3;
			/**< seqerr */
			kulong seqerr :1;
			kulong :11;
			/**< monpad */
			kulong monpad :12;
			/**< monseq */
			kulong monseq :1;
			/**< monlpa */
			kulong monlpa :1;
			kulong :2;
		} bit;
} ;

/** Define i/o mapping */
struct _TimgpcDump
{
		/**< (0000 - 0007h) */
		UimgpcGpctopcnf gpctopcnf[2];
		/**< (0008 - 000Fh) */
		kuchar dmy0008000f[0x0010 - 0x0008];
		 /**< (0010 - 0013h) */
		UimgpcGpccontrol gpccontrol;
		 /**< (0014 - 0017h) */
		UimgpcGpccloadadr gpccloadadr;
		 /**< (0018 - 001Bh) */
		UimgpcGpcmon gpcmon;
		 /**< 001C - FFFFh */
		kuchar dmy7001c7ffff[0x80000 - 0x7001C];
} ;

///////////////////////////////////////////////////////////////
// LUT UNIT Register
///////////////////////////////////////////////////////////////
/** structure of luttopcnf	(0000h) */
union _UimLutLuttopcnf
{
		 /**< All bits */
		kulong word;
		 /**< bit field */
		struct {
			/**< waitconf0<br>waitconf1<br>WAITCONF_2<br>WAITCONF_3<br>Refer to @ref EimPortid. */
			kulong waitconf :6;
			kulong :2;
			kulong :8;
			/**< dataconf0<br>dataconf1<br>dataconf2<br>DATACONF_3<br>Refer to @ref EimPortid. */
			kulong dataconf :6;
			kulong :10;
		} bit;
} ;

/** structure of lutunitctl (0010h) */
union _UimLutLutunitctl
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< porten */
			kulong porten :4;
			/**< port3seli */
			kulong port3seli :2;
			kulong :2;
			/**< port3selo */
			kulong port3selo :2;
			kulong :2;
			/**< branch */
			kulong branch :2;
			kulong :2;
			/**< port2seli */
			kulong port2seli :2;
			kulong :2;
			/**< port2selo */
			kulong port2selo :2;
			kulong :2;
			/**< outmd0 */
			kulong outmd0 :1;
			/**< outmd1 */
			kulong outmd1 :1;
			/**< outmd2 */
			kulong outmd2 :1;
			/**< outmd3 */
			kulong outmd3 :1;
			kulong :4;
		} bit;
} ;

/** structure of lutctlA	(0020h)
	structure of lutctlB	(0040h)
	structure of lutctlC	(0060h)
	structure of lutctlD	(0080h)
	structure of lutctlE	(00A0h)
	structure of lutctlF	(00C0h) */
union _UimLutLutctl
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< lutbit */
			kulong lutbit :4;
			/**< LUTUSE<br>Refer to @ref EimLutuse. */
			kulong use :1;
			kulong :3;
			/**< LUTSGN<br>Refer to @ref EimLutsgn. */
			kulong sgn :1;
			kulong :3;
			/**< splbit */
			kulong splbit :4;
			kulong :16;
		} bit;
} ;

/** structure of lutprecalA	(0030h)
	structure of lutprecalB	(0050h)
	structure of lutprecalC	(0070h)
	structure of lutprecalD	(0090h)
	structure of lutprecalE	(00B0h)
	structure of lutprecalF	(00D0h) */
union _UimLutLutprecal
{
		/**< All bits */
		kulong word[4];
		/**< bit field */
		struct {
			/**< LUTSHIFT */
			kulong shift :4;
			kulong :12;
			/**< LUTOFSEL */
			kint64 ofset :15;
			kulong :1;
			/**< LUTCLPMAX */
			kint64 clpmax :15;
			kulong :1;
			/**< LUTTHMAX */
			kint64 thmax :15;
			kulong :1;
			/**< LUTCLPMIN */
			kint64 clpmin :15;
			kulong :1;
			/**< LUTTHMIN */
			kint64 thmin :15;
			kulong :1;
			/**< LUTABS */
			kulong abs :1;
			kulong :15;
			/**< lutadrs */
			kulong lutadrs :15;
			kulong :1;
		} bit;
} ;

/** Define i/o mapping */
struct _TimLutDump
{
		 /**< (0000 - 000Fh) */
		UimLutLuttopcnf luttopcnf[4];
		/**< (0010 - 0013h) */
		UimLutLutunitctl lutunitctl;
		/**< (0014 - 001Fh) */
		kuchar dmy0014001f[0x0020 - 0x0014];
		 /**< (0020 - 0023h) */
		UimLutLutctl lutctlA;
		/**< (0024 - 002Fh) */
		kuchar dmy0024002f[0x0030 - 0x0024];
		/**< (0030 - 003Fh) */
		UimLutLutprecal lutprecalA;
		/**< (0040 - 0043h) */
		UimLutLutctl lutctlB;
		/**< (0044 - 004Fh) */
		kuchar dmy0044004f[0x0050 - 0x0044];
		/**< (0050 - 005Fh) */
		UimLutLutprecal lutprecalB;
		 /**< (0060 - 0063h) */
		UimLutLutctl lutctlC;
		/**< (0064 - 006Fh) */
		kuchar dmy0064006f[0x0070 - 0x0064];
		 /**< (0070 - 007Fh) */
		UimLutLutprecal lutprecalC;
		/**< (0080 - 0083h) */
		UimLutLutctl lutctlD;
		/**< (0084 - 008Fh) */
		kuchar dmy0084008f[0x0090 - 0x0084];
		/**< (0090 - 009Fh) */
		UimLutLutprecal lutprecalD;
		/**< (00A0 - 00A3h) */
		UimLutLutctl lutctlE;
		/**< (00A4 - 00AFh) */
		kuchar dmy_00A4_00AF[0x00B0 - 0x00A4];
		 /**< (00B0 - 00BFh) */
		UimLutLutprecal lutprecalE;
		/**< (00C0 - 00C3h) */
		UimLutLutctl lutctlF;
		/**< (00C4 - 00CFh) */
		kuchar dmy00c400cf[0x00D0 - 0x00C4];
		/**< (00D0 - 00DFh) */
		UimLutLutprecal lutprecalF;
		/**< 00E0 - FFFFh */
		kuchar dmy800e08ffff[0x90000 - 0x800E0];
} ;

///////////////////////////////////////////////////////////////
// MFT UNIT Register
///////////////////////////////////////////////////////////////
/** structure of MFTTOPCONF (0000h) */
union _UimMftMfttopconf
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< waitconf<br>Refer to @ref EimPortid. */
			kulong waitconf :6;
			kulong :2;
			kulong :8;
			/**< dataconf<br>Refer to @ref EimPortid. */
			kulong dataconf :6;
			kulong :10;
		} bit;
} ;

/** structure of mftmd	(0004h) */
union _UimMftMftmd
{
		 /**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< mftmd<br>Refer to @ref EimMftmd. */
			kulong mftmd :1;
			kulong :31;
		} bit;
} ;

/** structure of flttpsz	(0008h) */
union _UimMftFlttpsz
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< flttpsz */
			kulong flttpsz :11;
			kulong :21;
		} bit;
} ;

/** structure of fltouthsz	(000Ch) */
union _UimMftFltouthsz
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< fltouthsz */
			kulong fltouthsz :15;
			kulong :17;
		} bit;
} ;

/** structure of MFTCTLD0	(0010h)
	structure of MFTCTLD1	(0014h)
	structure of MFTCTLD2	(0018h)
	structure of MFTCTLD3	(001Ch) */
union _UimMftMftctl
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< D0FIX<br>D1FIX<br>D2FIX<br>Refer to @ref EimDnfix. */
			kulong fix :1;
			kulong :15;
			/**< D0VAL<br>D1VAL<br>D2VAL<br>D3VAL */
			kint64 val :15;
			kulong :1;
		} bit;
} ;

/** Define i/o mapping */
struct _TimMftDump
{
		 /**< (0000 - 0003h) */
		UimMftMfttopconf fttopconf;
		/**< (0004 - 0007h) */
		UimMftMftmd mftmd;
		/**< (0008 - 000Bh) */
		UimMftFlttpsz flttpsz;
		 /**< (000C - 000Fh) */
		UimMftFltouthsz fltouthsz;
		/**< (0010 - 001Fh) */
		UimMftMftctl mftctld[4];
		/**< 0020 - FFFFh */
		kuchar dmy900209ffff[0xA0000 - 0x90020];
} ;

///////////////////////////////////////////////////////////////
// MON UNIT Register
///////////////////////////////////////////////////////////////
/** structure of monctl (0000h) */
union _UimMonMonctl
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< histae */
			kulong histae :1;
			kulong :3;
			/**< histbe */
			kulong histbe :1;
			kulong :3;
			/**< histce */
			kulong histce :1;
			kulong :3;
			/**< histde */
			kulong histde :1;
			kulong :3;
			/**< maxe */
			kulong maxe :1;
			kulong :3;
			/**< mine */
			kulong mine :1;
			kulong :3;
			/**< adde */
			kulong adde :1;
			kulong :7;
		} bit;
} ;

/** structure of mondsel	(0004h) */
union _UimMonMondsel
{
		 /**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< dsel<br>Refer to @ref EimDsel. */
			kulong dsel :3;
			kulong :1;
			/**< sgnen0<br>Refer to @ref EimSgnen. */
			kulong sgnen0 :1;
			/**< sgnen1<br>Refer to @ref EimSgnen. */
			kulong sgnen1 :1;
			/**< sgnen2<br>Refer to @ref EimSgnen. */
			kulong sgnen2 :1;
			/**< sgnen3<br>Refer to @ref EimSgnen. */
			kulong sgnen3 :1;
			kulong :24;
		} bit;
} ;

/** structure of histctl	(0010h) */
union _UimMonHistctl
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< HISTSEL_0<br>HISTSEL_1<br>HISTSEL_2<br>HISTSEL_3 */
			kulong histsel :2;
			kulong :2;
			/**< BITSEL_0<br>BITSEL_1<br>BITSEL_2<br>BITSEL_3<br>Refer to @ref EimBitsel. */
			kulong bitsel :3;
			kulong :1;
			/**< HISTSKIP_H_0<br>HISTSKIP_H_1<br>HISTSKIP_H_2<br>HISTSKIP_H_3 */
			kulong histskipH :6;
			kulong :2;
			/**< HISTSKIP_V_0<br>HISTSKIP_V_1<br>HISTSKIP_V_2<br>HISTSKIP_V_3 */
			kulong histskipV :6;
			kulong :10;
		} bit;
} ;

/** structure of absmax (0020h) */
union _UimMonAbsmax
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< absmax */
			kulong absmax :1;
			kulong :31;
		} bit;
} ;

/** structure of absmin (0024h) */
union _UimMonAbsmin
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< absmin */
			kulong absmin :1;
			kulong :31;
		} bit;
} ;

/** structure of absadd (0040h) */
union _UimMonAbsadd
{
		/**< All bits */
		kulong word;
		 /**< bit field */
		struct {
			/**< absadd */
			kulong absadd :1;
			kulong :31;
		} bit;
} ;

/** structure of overvalue	(0050h) */
union _UimMonOvervalue
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
			/**< overvalue */
			kint64 overvalue :32;
		} bit;
} ;

/** Define i/o mapping */
struct _TimMonDump
{
		/**< (0000 - 0003h) */
		UimMonMonctl monctl;
		/**< (0004 - 0007h) */
		UimMonMondsel mondsel;
		/**< (0008 - 000Fh) */
		kuchar dmy0008000f[0x0010 - 0x0008];
		/**< (0010 - 001Fh) */
		UimMonHistctl histctl[4];
		/**< (0020 - 0023h) */
		UimMonAbsmax absmax;
		/**< (0024 - 0027h) */
		UimMonAbsmin absmin;
		 /**< (0028 - 003Fh) */
		kuchar dmy0028003f[0x0040 - 0x0028];
		/**< (0040 - 0043h) */
		UimMonAbsadd absadd;
		/**< (0044 - 004Fh) */
		kuchar dmy0044004f[0x0050 - 0x0044];
		/**< (0050 - 005Fh) */
		UimMonOvervalue overvalue[4];
		/**< 0060 - FFFFh */
		kuchar dmyA0060Affff[0xB0000 - 0xA0060];
} ;

struct _ImIipMultiRegister
{
	KObject parent;
};



KConstType 		    				im_iip_multi_register_get_type(void);
ImIipMultiRegister*		        im_iip_multi_register_new(void);


#ifdef __cplusplus
}
#endif


#endif /* __IM_IIP_MULTI_REGISTER_H__ */
