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


#include <klib.h>
#include "imiipafnregister.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_FRECT_REGISTER						(im_iip_frect_register_get_type())
#define IM_IIP_FRECT_REGISTER(obj)							(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipFrectRegister))
#define IM_IS_IIP_FRECT_REGISTER(obj)						(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_FRECT_REGISTER))


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
typedef struct _ImIipFrectRegister 								ImIipFrectRegister;
typedef struct _ImIipFrectRegisterPrivate 				ImIipFrectRegisterPrivate;


///////////////////////////////////////////////////////////////
// FRECT UNIT Register
///////////////////////////////////////////////////////////////
/** structure of frtopcnf	(0000h) */
union _UimFrectFrtopcnf
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

/** structure of frldcnf	(0004h) */
union _UimFrectFrldcnf
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		kulong :3;
		kulong :1;
		kulong :3;
		kulong :1;
		/**< dthd<br>Refer to @ref EimDthd. */
		kulong dthd :1;
		kulong :23;
	} bit;
} ;

/** structure of frctl	(0008h) */
union _UimFrectFrctl
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< ghsz<br>Refer to @ref EimGhsz. */
		kulong ghsz :1;
		kulong :3;
		/**< gvsz<br>Refer to @ref EimGvsz. */
		kulong gvsz :4;
		/**< lplvl<br>Refer to @ref EimLplvl. */
		kulong lplvl :1;
		kulong :3;
		kulong :4;
		/**< hdbl<br>Refer to @ref EimHdbl */
		kulong hdbl :1;
		/**< vdbl<br>Refer to @ref EimVdbl */
		kulong vdbl :1;
		/**< hsmd<br>Refer to @ref EimHsmd */
		kulong hsmd :1;
		kulong :13;
	} bit;
} ;

/** structure of pfctl	(000Ch) */
union _UimFrectPfctl
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< pfextmc */
		kulong pfextmc :3;
		kulong :5;
		/**< pfextadc */
		kulong pfextadc :8;
		/**< pfsp1<br>Refer to @ref EimPfsp */
		kulong pfsp1 :3;
		kulong :1;
		/**< pfsp2<br>Refer to @ref EimPfsp */
		kulong pfsp2 :3;
		kulong :1;
		/**< pfvsp<br>Refer to @ref EimPfvsp. */
		kulong pfvsp :2;
		kulong :2;
		/**< pfoff<br>Refer to @ref EimPfoff. */
		kulong pfoff :1;
		kulong :3;
	} bit;
} ;

/** structure of pixidef	(0010h) */
union _UimFrectPixidef
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		kulong :2;
		kulong :2;
		/**< ipixid */
		kulong ipixid :4;
		/**< exa<br>Refer to @ref EimExa. */
		kulong exa :1;
		kulong :3;
		/**< csel<br>Refer to @ref EimCsel */
		kulong csel :2;
		kulong :18;
	} bit;
} ;

/** structure of calmethod	(0014h) */
union _UimFrectCalmethod
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< opcol */
		kulong opcol :1;
		kulong :3;
		/**< itmd<br>Refer to @ref EimItmd. */
		kulong itmd :2;
		/**< ara<br>Refer to @ref EimAra. */
		kulong ara :2;
		/**< filmd */
		kulong filmd :1;
		/**< danti */
		kulong danti :1;
		/**< aanti */
		kulong aanti :1;
		kulong :1;
		/**< cubsel<br>Refer to @ref EimCubsel. */
		kulong cubsel :3;
		/**< scub<br>Refer to @ref EimScub. */
		kulong scub :1;
		kulong :16;
	} bit;
} ;

/** structure of filval0	(0018h) */
union _UimFrectFilval0
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< filvalyg */
		kulong filvalyg :16;
		/**< filvalb */
		kulong filvalb :16;
	} bit;
} ;

/** structure of filval1	(001Ch) */
union _UimFrectFilval1
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< filvalr */
		kulong filvalr :16;
		/**< filvala */
		kulong filvala :16;
	} bit;
} ;

/** structure of opmd	(0020h) */
union _UimFrectOpmd
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< opmd0<br>Refer to @ref EimOpmd. */
		kulong opmd0 :3;
		kulong :1;
		kulong :1;
		kulong :27;
	} bit;
} ;

/** structure of opy	(0030h) */
union _UimFrectOpy
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< opby */
		kulong opby :16;
		/**< opay */
		kulong opay :8;
		kulong :8;
	} bit;
} ;

/** structure of opb	(0034h) */
union _UimFrectOpb
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< opbb */
		kulong opbb :16;
		/**< opab */
		kulong opab :8;
		kulong :8;
	} bit;
} ;

/** structure of opr	(0038h) */
union _UimFrectOpr
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< opbr */
		kulong opbr :16;
		/**< opar */
		kulong opar :8;
		kulong :8;
	} bit;
} ;

/** structure of opa	(003Ch) */
union _UimFrectOpa
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< opba */
		kulong opba :16;
		/**< opaa */
		kulong opaa :8;
		kulong :8;
	} bit;
} ;

/** structure of cliplvly	(0040h) */
union _UimFrectCliplvly
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< cliplvlyh */
		kulong cliplvlyh :16;
		/**< cliplvlyl */
		kulong cliplvlyl :16;
	} bit;
} ;

/** structure of cliplvlb	(0044h) */
union _UimFrectCliplvlb
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< cliplvlbh */
		kulong cliplvlbh :16;
		/**< cliplvlbl */
		kulong cliplvlbl :16;
	} bit;
} ;

/** structure of cliplvlr	(0048h) */
union _UimFrectCliplvlr
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< cliplvlrh */
		kulong cliplvlrh :16;
		/**< cliplvlrl */
		kulong cliplvlrl :16;
	} bit;
} ;

/** structure of cliplvla	(004Ch) */
union _UimFrectCliplvla
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< cliplvlah */
		kulong cliplvlah :16;
		/**< cliplvlal */
		kulong cliplvlal :16;
	} bit;
} ;

/** structure of frpcnt (0050h) */
union _UimFrectFrpcnt
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< frphcnt */
		kulong frphcnt :9;
		kulong :7;
		/**< frpvcnt */
		kulong frpvcnt :8;
		kulong :8;
	} bit;
} ;

/** structure of padrs	(0054h) */
union _UimFrectPadrs
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< padrs */
		kulong padrs :32;
	} bit;
} ;

/** structure of outsize	(0058h) */
union _UimFrectOutsize
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< outhsz */
		kulong outhsz :14;
		kulong :2;
		/**< outvsz */
		kulong outvsz :14;
		kulong :2;
	} bit;
} ;

/** structure of outstartpos	(005Ch) */
union _UimFrectOutstartpos
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< startx */
		kulong startx :14;
		kulong :2;
		/**< starty */
		kulong starty :14;
		kulong :2;
	} bit;
} ;

/** structure of uplkTarget	(0060h) */
union _UimFrectUplkTarget
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< upsu0<br>Refer to @ref EimUpsu. */
		kulong upsu0 :4;
		kulong :4;
		/**< upsu1<br>Refer to @ref EimUpsu. */
		kulong upsu1 :4;
		kulong :4;
		/**< upsu2 */
		kulong upsu2 :4;
		kulong :4;
		kulong :8;
	} bit;
} ;

/** structure of dwlkTarget	(0064h) */
union _UimFrectDwlkTarget
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< dwsu0<br>Refer to @ref EimDwsu. */
		kulong dwsu0 :4;
		kulong :4;
		/**< dwsu1<br>Refer to @ref EimDwsu. */
		kulong dwsu1 :4;
		kulong :4;
		/**< dwsu2 */
		kulong dwsu2 :4;
		kulong :4;
		kulong :8;
	} bit;
} ;

/** structure of lknum	(0068h) */
union _UimFrectLknum
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< upnum<br>Refer to @ref EimUpnum. */
		kulong upnum :2;
		kulong :2;
		/**< dwnum<br>Refer to @ref EimDwnum. */
		kulong dwnum :2;
		kulong :26;
	} bit;
} ;

/** structure of ring	(006Ch) */
union _UimFrectRing
{
	/**< All bits */
	kulong word;
	/**< bit field */
	struct {
		/**< uringsize */
		kulong uringsize :8;
		/**< umarginiysz */
		kulong umarginiysz :4;
		kulong :4;
		/**< dringsize */
		kulong dringsize :8;
		kulong :8;
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
	kuchar dmy0024002f[0x0030 - 0x0024];
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
	kuchar dmy600706ffff[0x70000 - 0x60070];
} ;

struct _ImIipFrectRegister
{
	KObject parent;
};


KConstType 		    				im_iip_frect_register_get_type(void);
ImIipFrectRegister*		        im_iip_frect_register_new(void);


#ifdef __cplusplus
}
#endif


#endif /* __IM_IIP_FRECT_REGISTER_H__ */
