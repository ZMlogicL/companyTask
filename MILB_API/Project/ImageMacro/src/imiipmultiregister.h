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


#include <stdio.h>
#include <glib-object.h>
#include "imiipmanyregister.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_MULTI_REGISTER			(im_iip_multi_register_struct_get_type ())
#define IM_IIP_MULTI_REGISTER(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_IIP_MULTI_REGISTER, ImIipMultiRegister))
#define IM_IIP_MULTI_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_IIP_MULTI_REGISTER, ImIipMultiRegisterClass))
#define IM_IS_IIP_MULTI_REGISTER(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_IIP_MULTI_REGISTER))
#define IM_IS_IIP_MULTI_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_IIP_MULTI_REGISTER))
#define IM_IIP_MULTI_REGISTER_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_IIP_MULTI_REGISTER, ImIipMultiRegisterClass))


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

typedef struct _ImIipMultiRegister			ImIipMultiRegister;
typedef struct _ImIipMultiRegisterClass		ImIipMultiRegisterClass;
typedef struct _ImIipMultiRegisterPrivate 		ImIipMultiRegisterPrivate;


///////////////////////////////////////////////////////////////
// GPC UNIT Register
///////////////////////////////////////////////////////////////
/** structure of gpctopcnf	(0000h) */
union _UimgpcGpctopcnf
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< waitconf0<br>waitconf1<br>Refer to @ref EimPortid. */
			gulong waitconf :6;
			gulong :2;
			gulong :8;
			/**< dataconf0<br>dataconf1<br>Refer to @ref EimPortid. */
			gulong dataconf :6;
			gulong :10;
		} bit;
} ;

/** structure of gpccontrol (0010h) */
union _UimgpcGpccontrol
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< commonpapa<br>Refer to @ref EimCommonpara. */
			gulong commonpapa :2;
			gulong :2;
			/**< md2dlk */
			gulong md2dlk :1;
			gulong :3;
			/**< alpen0 */
			gulong alpen0 :1;
			gulong :3;
			/**< alpen1 */
			gulong alpen1 :1;
			gulong :3;
			/**< atrb0<br>Refer to @ref EimAtrb */
			gulong atrb0 :4;
			/**< atrb1<br>Refer to @ref EimAtrb */
			gulong atrb1 :4;
			gulong :8;
		} bit;
} ;

/** structure of gpccloadadr	(0014h) */
union _UimgpcGpccloadadr
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< cloadadr */
			gulong cloadadr :32;
		} bit;
} ;
/** structure of gpcmon (0018h) */
union _UimgpcGpcmon
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< gpcrun */
			gulong gpcrun :1;
			gulong :3;
			/**< seqerr */
			gulong seqerr :1;
			gulong :11;
			/**< monpad */
			gulong monpad :12;
			/**< monseq */
			gulong monseq :1;
			/**< monlpa */
			gulong monlpa :1;
			gulong :2;
		} bit;
} ;

/** Define i/o mapping */
struct _TimgpcDump
{
		/**< (0000 - 0007h) */
		UimgpcGpctopcnf gpctopcnf[2];
		/**< (0008 - 000Fh) */
		guchar dmy0008000f[0x0010 - 0x0008];
		 /**< (0010 - 0013h) */
		UimgpcGpccontrol gpccontrol;
		 /**< (0014 - 0017h) */
		UimgpcGpccloadadr gpccloadadr;
		 /**< (0018 - 001Bh) */
		UimgpcGpcmon gpcmon;
		 /**< 001C - FFFFh */
		guchar dmy7001c7ffff[0x80000 - 0x7001C];
} ;

///////////////////////////////////////////////////////////////
// LUT UNIT Register
///////////////////////////////////////////////////////////////
/** structure of luttopcnf	(0000h) */
union _UimLutLuttopcnf
{
		 /**< All bits */
		gulong word;
		 /**< bit field */
		struct {
			/**< waitconf0<br>waitconf1<br>WAITCONF_2<br>WAITCONF_3<br>Refer to @ref EimPortid. */
			gulong waitconf :6;
			gulong :2;
			gulong :8;
			/**< dataconf0<br>dataconf1<br>dataconf2<br>DATACONF_3<br>Refer to @ref EimPortid. */
			gulong dataconf :6;
			gulong :10;
		} bit;
} ;

/** structure of lutunitctl (0010h) */
union _UimLutLutunitctl
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< porten */
			gulong porten :4;
			/**< port3seli */
			gulong port3seli :2;
			gulong :2;
			/**< port3selo */
			gulong port3selo :2;
			gulong :2;
			/**< branch */
			gulong branch :2;
			gulong :2;
			/**< port2seli */
			gulong port2seli :2;
			gulong :2;
			/**< port2selo */
			gulong port2selo :2;
			gulong :2;
			/**< outmd0 */
			gulong outmd0 :1;
			/**< outmd1 */
			gulong outmd1 :1;
			/**< outmd2 */
			gulong outmd2 :1;
			/**< outmd3 */
			gulong outmd3 :1;
			gulong :4;
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
		gulong word;
		/**< bit field */
		struct {
			/**< lutbit */
			gulong lutbit :4;
			/**< LUTUSE<br>Refer to @ref EimLutuse. */
			gulong use :1;
			gulong :3;
			/**< LUTSGN<br>Refer to @ref EimLutsgn. */
			gulong sgn :1;
			gulong :3;
			/**< splbit */
			gulong splbit :4;
			gulong :16;
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
		gulong word[4];
		/**< bit field */
		struct {
			/**< LUTSHIFT */
			gulong shift :4;
			gulong :12;
			/**< LUTOFSEL */
			gs64 ofset :15;
			gulong :1;
			/**< LUTCLPMAX */
			gs64 clpmax :15;
			gulong :1;
			/**< LUTTHMAX */
			gs64 thmax :15;
			gulong :1;
			/**< LUTCLPMIN */
			gs64 clpmin :15;
			gulong :1;
			/**< LUTTHMIN */
			gs64 thmin :15;
			gulong :1;
			/**< LUTABS */
			gulong abs :1;
			gulong :15;
			/**< lutadrs */
			gulong lutadrs :15;
			gulong :1;
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
		guchar dmy0014001f[0x0020 - 0x0014];
		 /**< (0020 - 0023h) */
		UimLutLutctl lutctlA;
		/**< (0024 - 002Fh) */
		guchar dmy0024002f[0x0030 - 0x0024];
		/**< (0030 - 003Fh) */
		UimLutLutprecal lutprecalA;
		/**< (0040 - 0043h) */
		UimLutLutctl lutctlB;
		/**< (0044 - 004Fh) */
		guchar dmy0044004f[0x0050 - 0x0044];
		/**< (0050 - 005Fh) */
		UimLutLutprecal lutprecalB;
		 /**< (0060 - 0063h) */
		UimLutLutctl lutctlC;
		/**< (0064 - 006Fh) */
		guchar dmy0064006f[0x0070 - 0x0064];
		 /**< (0070 - 007Fh) */
		UimLutLutprecal lutprecalC;
		/**< (0080 - 0083h) */
		UimLutLutctl lutctlD;
		/**< (0084 - 008Fh) */
		guchar dmy0084008f[0x0090 - 0x0084];
		/**< (0090 - 009Fh) */
		UimLutLutprecal lutprecalD;
		/**< (00A0 - 00A3h) */
		UimLutLutctl lutctlE;
		/**< (00A4 - 00AFh) */
		guchar dmy_00A4_00AF[0x00B0 - 0x00A4];
		 /**< (00B0 - 00BFh) */
		UimLutLutprecal lutprecalE;
		/**< (00C0 - 00C3h) */
		UimLutLutctl lutctlF;
		/**< (00C4 - 00CFh) */
		guchar dmy00c400cf[0x00D0 - 0x00C4];
		/**< (00D0 - 00DFh) */
		UimLutLutprecal lutprecalF;
		/**< 00E0 - FFFFh */
		guchar dmy800e08ffff[0x90000 - 0x800E0];
} ;

///////////////////////////////////////////////////////////////
// MFT UNIT Register
///////////////////////////////////////////////////////////////
/** structure of MFTTOPCONF (0000h) */
union _UimMftMfttopconf
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

/** structure of mftmd	(0004h) */
union _UimMftMftmd
{
		 /**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< mftmd<br>Refer to @ref EimMftmd. */
			gulong mftmd :1;
			gulong :31;
		} bit;
} ;

/** structure of flttpsz	(0008h) */
union _UimMftFlttpsz
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< flttpsz */
			gulong flttpsz :11;
			gulong :21;
		} bit;
} ;

/** structure of fltouthsz	(000Ch) */
union _UimMftFltouthsz
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< fltouthsz */
			gulong fltouthsz :15;
			gulong :17;
		} bit;
} ;

/** structure of MFTCTLD0	(0010h)
	structure of MFTCTLD1	(0014h)
	structure of MFTCTLD2	(0018h)
	structure of MFTCTLD3	(001Ch) */
union _UimMftMftctl
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< D0FIX<br>D1FIX<br>D2FIX<br>Refer to @ref EimDnfix. */
			gulong fix :1;
			gulong :15;
			/**< D0VAL<br>D1VAL<br>D2VAL<br>D3VAL */
			gs64 val :15;
			gulong :1;
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
		guchar dmy900209ffff[0xA0000 - 0x90020];
} ;

///////////////////////////////////////////////////////////////
// MON UNIT Register
///////////////////////////////////////////////////////////////
/** structure of monctl (0000h) */
union _UimMonMonctl
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< histae */
			gulong histae :1;
			gulong :3;
			/**< histbe */
			gulong histbe :1;
			gulong :3;
			/**< histce */
			gulong histce :1;
			gulong :3;
			/**< histde */
			gulong histde :1;
			gulong :3;
			/**< maxe */
			gulong maxe :1;
			gulong :3;
			/**< mine */
			gulong mine :1;
			gulong :3;
			/**< adde */
			gulong adde :1;
			gulong :7;
		} bit;
} ;

/** structure of mondsel	(0004h) */
union _UimMonMondsel
{
		 /**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< dsel<br>Refer to @ref EimDsel. */
			gulong dsel :3;
			gulong :1;
			/**< sgnen0<br>Refer to @ref EimSgnen. */
			gulong sgnen0 :1;
			/**< sgnen1<br>Refer to @ref EimSgnen. */
			gulong sgnen1 :1;
			/**< sgnen2<br>Refer to @ref EimSgnen. */
			gulong sgnen2 :1;
			/**< sgnen3<br>Refer to @ref EimSgnen. */
			gulong sgnen3 :1;
			gulong :24;
		} bit;
} ;

/** structure of histctl	(0010h) */
union _UimMonHistctl
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< HISTSEL_0<br>HISTSEL_1<br>HISTSEL_2<br>HISTSEL_3 */
			gulong histsel :2;
			gulong :2;
			/**< BITSEL_0<br>BITSEL_1<br>BITSEL_2<br>BITSEL_3<br>Refer to @ref EimBitsel. */
			gulong bitsel :3;
			gulong :1;
			/**< HISTSKIP_H_0<br>HISTSKIP_H_1<br>HISTSKIP_H_2<br>HISTSKIP_H_3 */
			gulong histskipH :6;
			gulong :2;
			/**< HISTSKIP_V_0<br>HISTSKIP_V_1<br>HISTSKIP_V_2<br>HISTSKIP_V_3 */
			gulong histskipV :6;
			gulong :10;
		} bit;
} ;

/** structure of absmax (0020h) */
union _UimMonAbsmax
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< absmax */
			gulong absmax :1;
			gulong :31;
		} bit;
} ;

/** structure of absmin (0024h) */
union _UimMonAbsmin
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< absmin */
			gulong absmin :1;
			gulong :31;
		} bit;
} ;

/** structure of absadd (0040h) */
union _UimMonAbsadd
{
		/**< All bits */
		gulong word;
		 /**< bit field */
		struct {
			/**< absadd */
			gulong absadd :1;
			gulong :31;
		} bit;
} ;

/** structure of overvalue	(0050h) */
union _UimMonOvervalue
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
			/**< overvalue */
			gs64 overvalue :32;
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
		guchar dmy0008000f[0x0010 - 0x0008];
		/**< (0010 - 001Fh) */
		UimMonHistctl histctl[4];
		/**< (0020 - 0023h) */
		UimMonAbsmax absmax;
		/**< (0024 - 0027h) */
		UimMonAbsmin absmin;
		 /**< (0028 - 003Fh) */
		guchar dmy0028003f[0x0040 - 0x0028];
		/**< (0040 - 0043h) */
		UimMonAbsadd absadd;
		/**< (0044 - 004Fh) */
		guchar dmy0044004f[0x0050 - 0x0044];
		/**< (0050 - 005Fh) */
		UimMonOvervalue overvalue[4];
		/**< 0060 - FFFFh */
		guchar dmyA0060Affff[0xB0000 - 0xA0060];
} ;

struct _ImIipMultiRegister
{
	GObject parent;
};

struct _ImIipMultiRegisterClass
{
	GObjectClass parentClass;
};


GType									im_iip_multi_register_struct_get_type(void)	G_GNUC_CONST;
ImIipMultiRegister*			im_iip_multi_register_struct_new(void);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_IIP_MULTI_REGISTER_H__ */
