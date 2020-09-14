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


#ifndef __IM_IIP_AFN_REGISTER_H__
#define __IM_IIP_AFN_REGISTER_H__


#include <stdio.h>
#include <glib-object.h>
#include "imiipparamenum.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_AFN_REGISTER			(im_iip_afn_register_struct_get_type ())
#define IM_IIP_AFN_REGISTER(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_IIP_AFN_REGISTER, ImIipAfnRegister))
#define IM_IIP_AFN_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_IIP_AFN_REGISTER, ImIipAfnRegisterClass))
#define IM_IS_IIP_AFN_REGISTER(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_IIP_AFN_REGISTER))
#define IM_IS_IIP_AFN_REGISTER_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_IIP_AFN_REGISTER))
#define IM_IIP_AFN_REGISTER_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_IIP_AFN_REGISTER, ImIipAfnRegisterClass))


typedef union _UimAfnAfntopcnf				UimAfnAfntopcnf;
typedef union _UimAfnAfnldcnf					UimAfnAfnldcnf;
typedef union _UimAfnAfnctl						UimAfnAfnctl;
typedef union _UimAfnPfctl							UimAfnPfctl;
typedef union _UimAfnPixidef						UimAfnPixidef;
typedef union _UimAfnCalmethod				UimAfnCalmethod;
typedef union _UimAfnFilval0						UimAfnFilval0;
typedef union _UimAfnFilval1						UimAfnFilval1;
typedef union _UimAfnOpmd						UimAfnOpmd;
typedef union _UimAfnOpy							UimAfnOpy;
typedef union _UimAfnOpb							UimAfnOpb;
typedef union _UimAfnOpr							UimAfnOpr;
typedef union _UimAfnOpa							UimAfnOpa;
typedef union _UimAfnCliplvly					UimAfnCliplvly;
typedef union _UimAfnCliplvlb					UimAfnCliplvlb;
typedef union _UimAfnCliplvlr						UimAfnCliplvlr;
typedef union _UimAfnCliplvla					UimAfnCliplvla;
typedef union _UimAfnAfnpcnt					UimAfnAfnpcnt;
typedef union _UimAfnAfnpa						UimAfnAfnpa;
typedef union _UimAfnOutsize					UimAfnOutsize;
typedef union _UimAfnOutstartpos			UimAfnOutstartpos;
typedef union _UimAfnUplkTarget				UimAfnUplkTarget;
typedef union _UimAfnDwlkTarget				UimAfnDwlkTarget;
typedef union _UimAfnLknum						UimAfnLknum;
typedef union _UimAfnRing							UimAfnRing;

typedef struct _TimAfnDump						TimAfnDump;
typedef struct _ImIipAfnRegister					ImIipAfnRegister;
typedef struct _ImIipAfnRegisterClass		ImIipAfnRegisterClass;
typedef struct _ImIipAfnRegisterPrivate 	ImIipAfnRegisterPrivate;



///////////////////////////////////////////////////////////////
// AFN UNIT Register
///////////////////////////////////////////////////////////////
/** structure of afntopcnf	(0000h) */
union _UimAfnAfntopcnf
{
		/**< All bits 			*/
		gulong word;
		/**< bit field 			*/
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

/** structure of afnldcnf	(0004h) */
union _UimAfnAfnldcnf
{
		/**< All bits 		*/
		gulong word;
		/**< bit field 		*/
		struct {
				gulong :3;
				gulong :1;
				gulong :3;
				gulong :1;
				/**< dthd<br>Refer to @ref EimDthd. 	*/
				gulong dthd :1;
				gulong :3;
				/**< cbc<br>Refer to @ref EimCbc. 			*/
				gulong cbc :1;
				gulong :19;
		} bit;
} ;

/** structure of afnctl (0008h) */
union _UimAfnAfnctl
{
		/**< All bits 			*/
		gulong word;
		/**< bit field 			*/
		struct {
				/**< ghsz<br>Refer to @ref EimGhsz. 	*/
				gulong ghsz :1;
				gulong :3;
				/**< gvsz<br>Refer to @ref EimGvsz. 		*/
				gulong gvsz :4;
				/**< lplvl<br>Refer to @ref EimLplvl. 	*/
				gulong lplvl :1;
				gulong :3;
				gulong :4;
				/**< hdbl<br>Refer to @ref EimHdbl 	*/
				gulong hdbl :1;
				/**< vdbl<br>Refer to @ref EimVdbl 		*/
				gulong vdbl :1;
				/**< hsmd<br>Refer to @ref EimHsmd 	*/
				gulong hsmd :1;
				gulong :13;
		} bit;
} ;

/** structure of pfctl	(000Ch) */
union _UimAfnPfctl
{
		/**< All bits 		*/
		gulong word;
		/**< bit field 		*/
		struct {
				/**< pfextmc */
				gulong pfextmc :3;
				gulong :5;
				/**< pfextadc*/
				gulong pfextadc :8;
				/**< pfsp1<br>Refer to @ref EimPfsp 		*/
				gulong pfsp1 :3;
				gulong :1;
				/**< pfsp2<br>Refer to @ref EimPfsp 		*/
				gulong pfsp2 :3;
				gulong :1;
				/**< pfvsp<br>Refer to @ref EimPfvsp. 	*/
				gulong pfvsp :2;
				gulong :2;
				/**< pfoff<br>Refer to @ref EimPfoff. 	*/
				gulong pfoff :1;
				gulong :3;
		} bit;
} ;

/** structure of pixidef	(0010h) */
union _UimAfnPixidef
{
		/**< All bits 			*/
		gulong word;
		/**< bit field 			*/
		struct {
				gulong :2;
				gulong :2;
				/**< ipixid	*/
				gulong ipixid :4;
				/**< exa<br>Refer to @ref EimExa. 		*/
				gulong exa :1;
				gulong :3;
				/**< csel<br>Refer to @ref EimCsel	 */
				gulong csel :2;
				gulong :18;
		} bit;
} ;

/** structure of calmethod	(0014h) */
union _UimAfnCalmethod
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
				/**< opcol */
				gulong opcol :1;
				gulong :3;
				/**< itmd<br>Refer to @ref EimItmd. 		*/
				gulong itmd :2;
				/**< ara<br>Refer to @ref EimAra. 				*/
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
				/**< scub<br>Refer to @ref EimScub. 		*/
				gulong scub :1;
				gulong :16;
		} bit;
} ;

/** structure of filval0	(0018h) */
union _UimAfnFilval0
{
		/**< All bits */
		gulong word;
		/**< bit field */
		struct {
				/**< filvalyg */
				gulong filvalyg :16;
				/**< filvalb 	*/
				gulong filvalb :16;
		} bit;
} ;

/** structure of filval1	(001Ch) */
union _UimAfnFilval1
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
union _UimAfnOpmd
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
union _UimAfnOpy
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
union _UimAfnOpb
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
union _UimAfnOpr
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
union _UimAfnOpa
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
union _UimAfnCliplvly
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
union _UimAfnCliplvlb
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
union _UimAfnCliplvlr
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
union _UimAfnCliplvla
{
		/**< All bits 	*/
		gulong word;
		/**< bit field 	*/
		struct {
				/**< cliplvlah */
				gulong cliplvlah :16;
				/**< cliplvlal */
				gulong cliplvlal :16;
		} bit;
} ;

/** structure of afnpcnt	(0050h) */
union _UimAfnAfnpcnt
{
		/**< All bits 	*/
		gulong word;
		/**< bit field 	*/
		struct {
				/**< afnphcnt */
				gulong afnphcnt :9;
				gulong :7;
				/**< afnpvcnt */
				gulong afnpvcnt :8;
				gulong :8;
		} bit;
} ;

/** structure of afnpa	(0054h) */
union _UimAfnAfnpa
{
		/**< All bits 	*/
		gulong word;
		/**< bit field 	*/
		struct {
				/**< afnpa */
				gulong afnpa :32;
		} bit;
} ;

/** structure of outsize	(0058h) */
union _UimAfnOutsize
{
		/**< All bits 	*/
		gulong word;
		/**< bit field 	*/
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
union _UimAfnOutstartpos
{
		/**< All bits 	*/
		gulong word;
		/**< bit field 	*/
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
union _UimAfnUplkTarget
{
		/**< All bits 	*/
		gulong word;
		/**< bit field 	*/
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
union _UimAfnDwlkTarget
{
		/**< All bits		*/
		gulong word;
		/**< bit field 	*/
		struct {
				/**< dwsu0<br>Refer to @ref EimDwsu. */
				gulong dwsu0 :4;
				gulong :4;
				gulong dwsu1 :4;
				/**< dwsu1<br>Refer to @ref EimDwsu. */
				gulong :4;
				/**< dwsu2 */
				gulong dwsu2 :4;
				gulong :4;
				gulong :8;
		} bit;
} ;

/** structure of lknum	(0068h) */
union _UimAfnLknum
{
		/**< All bits 	*/
		gulong word;
		/**< bit field 	*/
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
union _UimAfnRing
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
struct _TimAfnDump
{
		/**< (0000 - 0003h) */
		UimAfnAfntopcnf afntopcnf;
		/**< (0004 - 0007h) */
		UimAfnAfnldcnf afnldcnf;
		/**< (0008 - 000Bh) */
		UimAfnAfnctl afnctl;
		/**< (000C - 000Fh) */
		UimAfnPfctl pfctl;
		/**< (0010 - 0013h) */
		UimAfnPixidef pixidef;
		/**< (0014 - 0017h) */
		UimAfnCalmethod calmethod;
		/**< (0018 - 001Bh) */
		UimAfnFilval0 filval0;
		/**< (001C - 001Fh) */
		UimAfnFilval1 filval1;
		/**< (0020 - 0023h) */
		UimAfnOpmd opmd;
		/**< (0024 - 002Fh) */
		guchar dmy0024002f[0x0030 - 0x0024];
		/**< (0030 - 0033h) */
		UimAfnOpy opy;
		/**< (0034 - 0037h) */
		UimAfnOpb opb;
		/**< (0038 - 003Bh) */
		UimAfnOpr opr;
		/**< (003C - 003Fh) */
		UimAfnOpa opa;
		/**< (0040 - 0043h) */
		UimAfnCliplvly cliplvly;
		/**< (0044 - 0047h) */
		UimAfnCliplvlb cliplvlb;
		/**< (0048 - 004Bh) */
		UimAfnCliplvlr cliplvlr;
		/**< (004C - 004Fh) */
		UimAfnCliplvla cliplvla;
		/**< (0050 - 0053h) */
		UimAfnAfnpcnt afnpcnt;
		/**< (0054 - 0057h) */
		UimAfnAfnpa afnpa;
		/**< (0058 - 005Bh) */
		UimAfnOutsize outsize;
		/**< (005C - 005Fh) */
		UimAfnOutstartpos outstartpos;
		/**< (0060 - 0063h) */
		UimAfnUplkTarget uplkTarget;
		/**< (0064 - 0067h) */
		UimAfnDwlkTarget dwlkTarget;
		/**< (0068 - 006Bh) */
		UimAfnLknum lknum;
		/**< (006C - 006Fh) */
		UimAfnRing ring;
		/**< 0070 - FFFFh */
		guchar dmy100701ffff[0x20000 - 0x10070];
} ;


struct _ImIipAfnRegister
{
	GObject parent;
};

struct _ImIipAfnRegisterClass
{
	GObjectClass parentClass;
};


GType						im_iip_afn_register_struct_get_type(void)	G_GNUC_CONST;
ImIipAfnRegister*					im_iip_afn_register_struct_new(void);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_IIP_AFN_REGISTER_H__ */
