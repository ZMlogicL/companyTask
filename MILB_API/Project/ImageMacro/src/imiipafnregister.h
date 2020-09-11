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


#include <klib.h>
#include "imiipparamenum.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_AFN_REGISTER							(im_iip_afn_register_get_type())
#define IM_IIP_AFN_REGISTER	(obj)							(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipAfnRegister))
#define IM_IS_IIP_AFN_REGISTER	(obj)					(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_AFN_REGISTER	))


typedef union _UimAfnAfntopcnf				UimAfnAfntopcnf;
typedef union _UimAfnAfnldcnf					UimAfnAfnldcnf;
typedef union _UimAfnAfnctl						UimAfnAfnctl;
typedef union _UimAfnPfctl							UimAfnPfctl;
typedef union _UimAfnPixidef					UimAfnPixidef;
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
typedef union _UimAfnCliplvlr					UimAfnCliplvlr;
typedef union _UimAfnCliplvla					UimAfnCliplvla;
typedef union _UimAfnAfnpcnt					UimAfnAfnpcnt;
typedef union _UimAfnAfnpa						UimAfnAfnpa;
typedef union _UimAfnOutsize					UimAfnOutsize;
typedef union _UimAfnOutstartpos			UimAfnOutstartpos;
typedef union _UimAfnUplkTarget				UimAfnUplkTarget;
typedef union _UimAfnDwlkTarget				UimAfnDwlkTarget;
typedef union _UimAfnLknum					UimAfnLknum;
typedef union _UimAfnRing							UimAfnRing;

typedef struct _TimAfnDump						TimAfnDump;
typedef struct _ImIipAfnRegister 								ImIipAfnRegister;
typedef struct _ImIipAfnRegisterPrivate 					ImIipAfnRegisterPrivate;



///////////////////////////////////////////////////////////////
// AFN UNIT Register
///////////////////////////////////////////////////////////////
/** structure of afntopcnf	(0000h) */
union _UimAfnAfntopcnf
{
		/**< All bits 			*/
		kulong word;
		/**< bit field 			*/
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

/** structure of afnldcnf	(0004h) */
union _UimAfnAfnldcnf
{
		/**< All bits 		*/
		kulong word;
		/**< bit field 		*/
		struct {
				kulong :3;
				kulong :1;
				kulong :3;
				kulong :1;
				/**< dthd<br>Refer to @ref EimDthd. 	*/
				kulong dthd :1;
				kulong :3;
				/**< cbc<br>Refer to @ref EimCbc. 			*/
				kulong cbc :1;
				kulong :19;
		} bit;
} ;

/** structure of afnctl (0008h) */
union _UimAfnAfnctl
{
		/**< All bits 			*/
		kulong word;
		/**< bit field 			*/
		struct {
				/**< ghsz<br>Refer to @ref EimGhsz. 	*/
				kulong ghsz :1;
				kulong :3;
				/**< gvsz<br>Refer to @ref EimGvsz. 		*/
				kulong gvsz :4;
				/**< lplvl<br>Refer to @ref EimLplvl. 	*/
				kulong lplvl :1;
				kulong :3;
				kulong :4;
				/**< hdbl<br>Refer to @ref EimHdbl 	*/
				kulong hdbl :1;
				/**< vdbl<br>Refer to @ref EimVdbl 		*/
				kulong vdbl :1;
				/**< hsmd<br>Refer to @ref EimHsmd 	*/
				kulong hsmd :1;
				kulong :13;
		} bit;
} ;

/** structure of pfctl	(000Ch) */
union _UimAfnPfctl
{
		/**< All bits 		*/
		kulong word;
		/**< bit field 		*/
		struct {
				/**< pfextmc */
				kulong pfextmc :3;
				kulong :5;
				/**< pfextadc*/
				kulong pfextadc :8;
				/**< pfsp1<br>Refer to @ref EimPfsp 		*/
				kulong pfsp1 :3;
				kulong :1;
				/**< pfsp2<br>Refer to @ref EimPfsp 		*/
				kulong pfsp2 :3;
				kulong :1;
				/**< pfvsp<br>Refer to @ref EimPfvsp. 	*/
				kulong pfvsp :2;
				kulong :2;
				/**< pfoff<br>Refer to @ref EimPfoff. 	*/
				kulong pfoff :1;
				kulong :3;
		} bit;
} ;

/** structure of pixidef	(0010h) */
union _UimAfnPixidef
{
		/**< All bits 			*/
		kulong word;
		/**< bit field 			*/
		struct {
				kulong :2;
				kulong :2;
				/**< ipixid	*/
				kulong ipixid :4;
				/**< exa<br>Refer to @ref EimExa. 		*/
				kulong exa :1;
				kulong :3;
				/**< csel<br>Refer to @ref EimCsel	 */
				kulong csel :2;
				kulong :18;
		} bit;
} ;

/** structure of calmethod	(0014h) */
union _UimAfnCalmethod
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
				/**< opcol */
				kulong opcol :1;
				kulong :3;
				/**< itmd<br>Refer to @ref EimItmd. 		*/
				kulong itmd :2;
				/**< ara<br>Refer to @ref EimAra. 				*/
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
				/**< scub<br>Refer to @ref EimScub. 		*/
				kulong scub :1;
				kulong :16;
		} bit;
} ;

/** structure of filval0	(0018h) */
union _UimAfnFilval0
{
		/**< All bits */
		kulong word;
		/**< bit field */
		struct {
				/**< filvalyg */
				kulong filvalyg :16;
				/**< filvalb 	*/
				kulong filvalb :16;
		} bit;
} ;

/** structure of filval1	(001Ch) */
union _UimAfnFilval1
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
union _UimAfnOpmd
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
union _UimAfnOpy
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
union _UimAfnOpb
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
union _UimAfnOpr
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
union _UimAfnOpa
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
union _UimAfnCliplvly
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
union _UimAfnCliplvlb
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
union _UimAfnCliplvlr
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
union _UimAfnCliplvla
{
		/**< All bits 	*/
		kulong word;
		/**< bit field 	*/
		struct {
				/**< cliplvlah */
				kulong cliplvlah :16;
				/**< cliplvlal */
				kulong cliplvlal :16;
		} bit;
} ;

/** structure of afnpcnt	(0050h) */
union _UimAfnAfnpcnt
{
		/**< All bits 	*/
		kulong word;
		/**< bit field 	*/
		struct {
				/**< afnphcnt */
				kulong afnphcnt :9;
				kulong :7;
				/**< afnpvcnt */
				kulong afnpvcnt :8;
				kulong :8;
		} bit;
} ;

/** structure of afnpa	(0054h) */
union _UimAfnAfnpa
{
		/**< All bits 	*/
		kulong word;
		/**< bit field 	*/
		struct {
				/**< afnpa */
				kulong afnpa :32;
		} bit;
} ;

/** structure of outsize	(0058h) */
union _UimAfnOutsize
{
		/**< All bits 	*/
		kulong word;
		/**< bit field 	*/
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
union _UimAfnOutstartpos
{
		/**< All bits 	*/
		kulong word;
		/**< bit field 	*/
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
union _UimAfnUplkTarget
{
		/**< All bits 	*/
		kulong word;
		/**< bit field 	*/
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
union _UimAfnDwlkTarget
{
		/**< All bits		*/
		kulong word;
		/**< bit field 	*/
		struct {
				/**< dwsu0<br>Refer to @ref EimDwsu. */
				kulong dwsu0 :4;
				kulong :4;
				kulong dwsu1 :4;
				/**< dwsu1<br>Refer to @ref EimDwsu. */
				kulong :4;
				/**< dwsu2 */
				kulong dwsu2 :4;
				kulong :4;
				kulong :8;
		} bit;
} ;

/** structure of lknum	(0068h) */
union _UimAfnLknum
{
		/**< All bits 	*/
		kulong word;
		/**< bit field 	*/
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
union _UimAfnRing
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
		kuchar dmy0024002f[0x0030 - 0x0024];
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
		kuchar dmy100701ffff[0x20000 - 0x10070];
} ;


struct _ImIipAfnRegister
{
	KObject parent;
};


KConstType 		    			im_iip_afn_register_get_type(void);
ImIipAfnRegister*		        im_iip_afn_register_new(void);


#ifdef __cplusplus
}
#endif


#endif /* __IM_IIP_AFN_REGISTER_H__ */
