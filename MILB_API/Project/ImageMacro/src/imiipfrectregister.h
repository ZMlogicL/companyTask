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


#ifndef __IM_IIP_FRECT_REGISTER_H__
#define __IM_IIP_FRECT_REGISTER_H__


#include <stdio.h>
#include <glib-object.h>
#include "imiipafnregister.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_FRECT_REGISTER			(im_iip_frect_register_struct_get_type ())
#define IM_IIP_FRECT_REGISTER(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_IIP_FRECT_REGISTER, ImIipFrectRegister))
#define IM_IIP_FRECT_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_IIP_FRECT_REGISTER, ImIipFrectRegisterClass))
#define IM_IS_IIP_FRECT_REGISTER(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_IIP_FRECT_REGISTER))
#define IM_IS_IIP_FRECT_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_IIP_FRECT_REGISTER))
#define IM_IIP_FRECT_REGISTER_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_IIP_FRECT_REGISTER, ImIipFrectRegisterClass))


typedef union _UimFrectFrtopcnf				UimFrectFrtopcnf;
typedef union _UimFrectFrldcnf					UimFrectFrldcnf;
typedef union _UimFrectFrctl						UimFrectFrctl;
typedef union _UimFrectPfctl						UimFrectPfctl;
typedef union _UimFrectPixidef					UimFrectPixidef;
typedef union _UimFrectCalmethod			UimFrectCalmethod;
typedef union _UimFrectFilval0					UimFrectFilval0;
typedef union _UimFrectFilval1					UimFrectFilval1;
typedef union _UimFrectOpmd					UimFrectOpmd;
typedef union _UimFrectOpy						UimFrectOpy;
typedef union _UimFrectOpb						UimFrectOpb;
typedef union _UimFrectOpr						UimFrectOpr;
typedef union _UimFrectOpa						UimFrectOpa;
typedef union _UimFrectCliplvly					UimFrectCliplvly;
typedef union _UimFrectCliplvlb					UimFrectCliplvlb;
typedef union _UimFrectCliplvlr					UimFrectCliplvlr;
typedef union _UimFrectCliplvla					UimFrectCliplvla;
typedef union _UimFrectFrpcnt					UimFrectFrpcnt;
typedef union _UimFrectPadrs					UimFrectPadrs;
typedef union _UimFrectOutsize					UimFrectOutsize;
typedef union _UimFrectOutstartpos			UimFrectOutstartpos;
typedef union _UimFrectUplkTarget			UimFrectUplkTarget;
typedef union _UimFrectDwlkTarget			UimFrectDwlkTarget;
typedef union _UimFrectLknum					UimFrectLknum;
typedef union _UimFrectRing						UimFrectRing;

typedef struct _TimFrectDump					TimFrectDump;
typedef struct _ImIipFrectRegister				ImIipFrectRegister;
typedef struct _ImIipFrectRegisterClass		ImIipFrectRegisterClass;
typedef struct _ImIipFrectRegisterPrivate 		ImIipFrectRegisterPrivate;


///////////////////////////////////////////////////////////////
// FRECT UNIT Register
///////////////////////////////////////////////////////////////
/** structure of frtopcnf	(0000h) */
union _UimFrectFrtopcnf
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

/** structure of frldcnf	(0004h) */
union _UimFrectFrldcnf
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		gulong :3;
		gulong :1;
		gulong :3;
		gulong :1;
		/**< dthd<br>Refer to @ref EimDthd. */
		gulong dthd :1;
		gulong :23;
	} bit;
} ;

/** structure of frctl	(0008h) */
union _UimFrectFrctl
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< ghsz<br>Refer to @ref EimGhsz. */
		gulong ghsz :1;
		gulong :3;
		/**< gvsz<br>Refer to @ref EimGvsz. */
		gulong gvsz :4;
		/**< lplvl<br>Refer to @ref EimLplvl. */
		gulong lplvl :1;
		gulong :3;
		gulong :4;
		/**< hdbl<br>Refer to @ref EimHdbl */
		gulong hdbl :1;
		/**< vdbl<br>Refer to @ref EimVdbl */
		gulong vdbl :1;
		/**< hsmd<br>Refer to @ref EimHsmd */
		gulong hsmd :1;
		gulong :13;
	} bit;
} ;

/** structure of pfctl	(000Ch) */
union _UimFrectPfctl
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< pfextmc */
		gulong pfextmc :3;
		gulong :5;
		/**< pfextadc */
		gulong pfextadc :8;
		/**< pfsp1<br>Refer to @ref EimPfsp */
		gulong pfsp1 :3;
		gulong :1;
		/**< pfsp2<br>Refer to @ref EimPfsp */
		gulong pfsp2 :3;
		gulong :1;
		/**< pfvsp<br>Refer to @ref EimPfvsp. */
		gulong pfvsp :2;
		gulong :2;
		/**< pfoff<br>Refer to @ref EimPfoff. */
		gulong pfoff :1;
		gulong :3;
	} bit;
} ;

/** structure of pixidef	(0010h) */
union _UimFrectPixidef
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		gulong :2;
		gulong :2;
		/**< ipixid */
		gulong ipixid :4;
		/**< exa<br>Refer to @ref EimExa. */
		gulong exa :1;
		gulong :3;
		/**< csel<br>Refer to @ref EimCsel */
		gulong csel :2;
		gulong :18;
	} bit;
} ;

/** structure of calmethod	(0014h) */
union _UimFrectCalmethod
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< opcol */
		gulong opcol :1;
		gulong :3;
		/**< itmd<br>Refer to @ref EimItmd. */
		gulong itmd :2;
		/**< ara<br>Refer to @ref EimAra. */
		gulong ara :2;
		/**< filmd */
		gulong filmd :1;
		/**< danti */
		gulong danti :1;
		/**< aanti */
		gulong aanti :1;
		gulong :1;
		/**< cubsel<br>Refer to @ref EimCubsel. */
		gulong cubsel :3;
		/**< scub<br>Refer to @ref EimScub. */
		gulong scub :1;
		gulong :16;
	} bit;
} ;

/** structure of filval0	(0018h) */
union _UimFrectFilval0
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< filvalyg */
		gulong filvalyg :16;
		/**< filvalb */
		gulong filvalb :16;
	} bit;
} ;

/** structure of filval1	(001Ch) */
union _UimFrectFilval1
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< filvalr */
		gulong filvalr :16;
		/**< filvala */
		gulong filvala :16;
	} bit;
} ;

/** structure of opmd	(0020h) */
union _UimFrectOpmd
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< opmd0<br>Refer to @ref EimOpmd. */
		gulong opmd0 :3;
		gulong :1;
		gulong :1;
		gulong :27;
	} bit;
} ;

/** structure of opy	(0030h) */
union _UimFrectOpy
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< opby */
		gulong opby :16;
		/**< opay */
		gulong opay :8;
		gulong :8;
	} bit;
} ;

/** structure of opb	(0034h) */
union _UimFrectOpb
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< opbb */
		gulong opbb :16;
		/**< opab */
		gulong opab :8;
		gulong :8;
	} bit;
} ;

/** structure of opr	(0038h) */
union _UimFrectOpr
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< opbr */
		gulong opbr :16;
		/**< opar */
		gulong opar :8;
		gulong :8;
	} bit;
} ;

/** structure of opa	(003Ch) */
union _UimFrectOpa
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< opba */
		gulong opba :16;
		/**< opaa */
		gulong opaa :8;
		gulong :8;
	} bit;
} ;

/** structure of cliplvly	(0040h) */
union _UimFrectCliplvly
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< cliplvlyh */
		gulong cliplvlyh :16;
		/**< cliplvlyl */
		gulong cliplvlyl :16;
	} bit;
} ;

/** structure of cliplvlb	(0044h) */
union _UimFrectCliplvlb
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< cliplvlbh */
		gulong cliplvlbh :16;
		/**< cliplvlbl */
		gulong cliplvlbl :16;
	} bit;
} ;

/** structure of cliplvlr	(0048h) */
union _UimFrectCliplvlr
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< cliplvlrh */
		gulong cliplvlrh :16;
		/**< cliplvlrl */
		gulong cliplvlrl :16;
	} bit;
} ;

/** structure of cliplvla	(004Ch) */
union _UimFrectCliplvla
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< cliplvlah */
		gulong cliplvlah :16;
		/**< cliplvlal */
		gulong cliplvlal :16;
	} bit;
} ;

/** structure of frpcnt (0050h) */
union _UimFrectFrpcnt
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< frphcnt */
		gulong frphcnt :9;
		gulong :7;
		/**< frpvcnt */
		gulong frpvcnt :8;
		gulong :8;
	} bit;
} ;

/** structure of padrs	(0054h) */
union _UimFrectPadrs
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< padrs */
		gulong padrs :32;
	} bit;
} ;

/** structure of outsize	(0058h) */
union _UimFrectOutsize
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< outhsz */
		gulong outhsz :14;
		gulong :2;
		/**< outvsz */
		gulong outvsz :14;
		gulong :2;
	} bit;
} ;

/** structure of outstartpos	(005Ch) */
union _UimFrectOutstartpos
{
	/**< All bits */
	gulong word;
	/**< bit field */
	struct {
		/**< startx */
		gulong startx :14;
		gulong :2;
		/**< starty */
		gulong starty :14;
		gulong :2;
	} bit;
} ;

/** structure of uplkTarget	(0060h) */
union _UimFrectUplkTarget
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
		gulong :4;
		gulong :8;
	} bit;
} ;

/** structure of dwlkTarget	(0064h) */
union _UimFrectDwlkTarget
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
		gulong :4;
		gulong :8;
	} bit;
} ;

/** structure of lknum	(0068h) */
union _UimFrectLknum
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

/** structure of ring	(006Ch) */
union _UimFrectRing
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
struct _TimFrectDump
{
	/**< (0000 - 0003h) */
	UimFrectFrtopcnf frtopcnf;
	/**< (0004 - 0007h) */
	UimFrectFrldcnf frldcnf;
	/**< (0008 - 000Bh) */
	UimFrectFrctl frctl;
	/**< (000C - 000Fh) */
	UimFrectPfctl pfctl;
	/**< (0010 - 0013h) */
	UimFrectPixidef pixidef;
	/**< (0014 - 0017h) */
	UimFrectCalmethod calmethod;
	/**< (0018 - 001Bh) */
	UimFrectFilval0 filval0;
	/**< (001C - 001Fh) */
	UimFrectFilval1 filval1;
	/**< (0020 - 0023h) */
	UimFrectOpmd opmd;
	/**< (0024 - 002Fh) */
	guchar dmy0024002f[0x0030 - 0x0024];
	/**< (0030 - 0033h) */
	UimFrectOpy opy;
	/**< (0034 - 0037h) */
	UimFrectOpb opb;
	/**< (0038 - 003Bh) */
	UimFrectOpr opr;
	/**< (003C - 003Fh) */
	UimFrectOpa opa;
	/**< (0040 - 0043h) */
	UimFrectCliplvly cliplvly;
	/**< (0044 - 0047h) */
	UimFrectCliplvlb cliplvlb;
	/**< (0048 - 004Bh) */
	UimFrectCliplvlr cliplvlr;
	/**< (004C - 004Fh) */
	UimFrectCliplvla cliplvla;
	/**< (0050 - 0053h) */
	UimFrectFrpcnt frpcnt;
	/**< (0054 - 0057h) */
	UimFrectPadrs padrs;
	/**< (0058 - 005Bh) */
	UimFrectOutsize outsize;
	/**< (005C - 005Fh) */
	UimFrectOutstartpos outstartpos;
	/**< (0060 - 0063h) */
	UimFrectUplkTarget uplkTarget;
	/**< (0064 - 0067h) */
	UimFrectDwlkTarget dwlkTarget;
	/**< (0068 - 006Bh) */
	UimFrectLknum lknum;
	/**< (006C - 006Fh) */
	UimFrectRing ring;
	/**< 0070 - FFFFh */
	guchar dmy600706ffff[0x70000 - 0x60070];
} ;

struct _ImIipFrectRegister
{
	GObject parent;
};

struct _ImIipFrectRegisterClass
{
	GObjectClass parentClass;
};


GType						im_iip_frect_register_struct_get_type(void)	G_GNUC_CONST;
ImIipFrectRegister*					im_iip_frect_register_struct_new(void);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_IIP_FRECT_REGISTER_H__ */
