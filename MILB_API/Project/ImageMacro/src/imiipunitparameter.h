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


#ifndef __IM_IIP_UNIT_PARAMETER_H__
#define __IM_IIP_UNIT_PARAMETER_H__


#include <klib.h>
#include "imiipslregister.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_UNIT_PARAMETER							(im_iip_unit_parameter_get_type())
#define IM_IIP_UNIT_PARAMETER(obj)							(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipUnitParameter))
#define IM_IS_IIP_UNIT_PARAMETER(obj)						(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_UNIT_PARAMETER))


typedef union _UimPacketHeader					UimPacketHeader;

typedef struct _Tim1dl										Tim1dl;
typedef struct _TimFlt										TimFlt;
typedef struct _TimAfn										TimAfn;
typedef struct _TimFrect									TimFrect;
typedef struct _TimStsBase								TimStsBase;
typedef struct _TimStsOpara1							TimStsOpara1;
typedef struct _TimStsAll									TimStsAll;
typedef struct _TimStsFill									TimStsFill;
typedef struct _TimSts										TimSts;
typedef struct _TimCsc										TimCsc;
typedef struct _TimLut										TimLut;
typedef struct _Timgpc									Timgpc;
typedef struct _TimBlend									TimBlend;
typedef struct _TimMon									TimMon;
typedef struct _TimCflow									TimCflow;
typedef struct _TimMft										TimMft;

typedef union _UimUnitdebug						UimUnitdebug;

typedef struct _ImIipUnitParameter 								ImIipUnitParameter;
typedef struct _ImIipUnitParameterPrivate 					ImIipUnitParameterPrivate;


///////////////////////////////////////////////////////////////
// UNIT Parameter
///////////////////////////////////////////////////////////////
/** Packet header of Unit Parameters */
union _UimPacketHeader
{
		/**< All bits */
		kuint32 word;
		struct {
			/**< Beginning address of the register */
			kuint32 BeginningAddress :16;
			/**< Word Length (including Packed header) */
			kuint32 WordLength :8;
			/**< Control code<br>Refer to @ref EimCtlCode. */
			kuint32 CtrlCode :8;
		} bit;
};

/** 1DL Unit Parameter */
struct _Tim1dl
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=16, BeginningAddress=0x0004) */
		UimPacketHeader header0;
		/**< ldTopcnf0		(+0004h) */
		Uim1dlLdTopcnf0 ldTopcnf0;
		/**< ldTopcnf1		(+0008h) */
		Uim1dlLdTopcnf1 ldTopcnf1;
		/**< Unused variable */
		kuchar dmy000c000f[0x0010 - 0x000C];
		/**< pixiddef			(+0010h) */
		Uim1dlPixiddef pixiddef;
		/**< ldCtl				(+0014h) */
		Uim1dlLdCtl ldCtl;
		/**< ldPrefetch		(+0018h) */
		Uim1dlLdPrefetch ldPrefetch;
		/**< Unused variable */
		kuchar dmy001c001f[0x0020 - 0x001C];
		/**< ldHsize			(+0020h) */
		Uim1dlLdHsize ldHsize;
		/**< ldVsize			(+0024h) */
		Uim1dlLdVsize ldVsize;
		/**< ldPhsz			(+0028h) */
		Uim1dlLdPhsz ldPhsz;
		/**< ldPvsz			(+002Ch) */
		Uim1dlLdPvsz ldPvsz;
		/**< uplkTarget		(+0030h) */
		Uim1dlUplkTarget uplkTarget;
		/**< dwlkTarget	(+0034h) */
		Uim1dlDwlkTarget dwlkTarget;
		/**< lknum			(+0038h) */
		Uim1dlLknum lknum;
		/**< ring				(+003Ch) */
		Uim1dlRing ring;
};

/** FLT Unit Parameter */
struct _TimFlt
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=145, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< tdltopcnf		(+0000h) */
		UimfltTdltopcnf tdltopcnf;
		/**< pixiddef			(+0004h) */
		UimfltPixiddef pixiddef;
		/**< tdlCtl				(+0008h) */
		UimfltTdlCtl tdlCtl;
		/**< calcMd			(+000Ch) */
		UimfltCalcMd calcMd;
		/**< tdlHsize			(+0010h) */
		UimfltTdlHsize tdlHsize;
		/**< tdlVsize			(+0014h) */
		UimfltTdlVsize tdlVsize;
		/**< tdlPhsz			(+0018h) */
		UimfltTdlPhsz tdlPhsz;
		/**< tdlPvsz			(+001Ch) */
		UimfltTdlPvsz tdlPvsz;
		/**< tdlPf				(+0020h) */
		UimfltTdlPf tdlPf;
		/**< unitOut			(+0024h) */
		UimfltUnitOut unitOut;
		/**< finClpAD0		(+0028h) */
		UimfltFinClpAd0 finClpAD0;
		/**< finClpAD1		(+002Ch) */
		UimfltFinClpAd1 finClpAD1;
		/**< finClpAD2		(+0030h) */
		UimfltFinClpAd2 finClpAD2;
		/**< finClpBD0		(+0034h) */
		UimfltFinClpBd0 finClpBD0;
		/**< finClpBD1		(+0038h) */
		UimfltFinClpBd1 finClpBD1;
		/**< finClpBD2		(+003Ch) */
		UimfltFinClpBd2 finClpBD2;
		/**< isoMd			(+0040h) */
		UimfltIsoMd isoMd;
		/**< ISO_TH_D0~3	(+0044h) */
		UimfltIsoThD isoThD[4];
		/**< ISO_GAIN_D0~3	(+0054h) */
		UimfltIsoGainD isoGainD[4];
		/**< spfMd			(+0064h) */
		UimfltSpfSpfMd spfMd;
		/**< Unused variable */
		kuchar dmy0068007f[0x0080 - 0x0068];
		/**< spfFltwD0		(+0080h) */
		UimfltSpfSpfFltw spfFltwD0;
		/**< Unused variable */
		kuchar dmy00a400bf[0x00C0 - 0x00A4];
		/**< spfFltwD1		(+00C0h) */
		UimfltSpfSpfFltw spfFltwD1;
		/**< Unused variable */
		kuchar dmy00e400ff[0x0100 - 0x00E4];
		/**< spfFltwD2		(+0100h) */
		UimfltSpfSpfFltw spfFltwD2;
		/**< Unused variable */
		kuchar dmy0124013f[0x0140 - 0x0124];
		/**< spfFltwD3		(+0140h) */
		UimfltSpfSpfFltw spfFltwD3;
		/**< Unused variable */
		kuchar dmy0164017f[0x0180 - 0x0164];
		/**< spfVthD0		(+0180h) */
		UimfltSpfVthD0 spfVthD0;
		/**< spfVthD1		(+0184h) */
		UimfltSpfVthD1 spfVthD1;
		/**< spfVthD2		(+0188h) */
		UimfltSpfVthD2 spfVthD2;
		/**< spfCoreD0	(+018Ch) */
		UimfltSpfCoreD0 spfCoreD0;
		/**< spfCoreD1	(+0190h) */
		UimfltSpfCoreD1 spfCoreD1;
		/**< spfCoreD2	(+0194h) */
		UimfltSpfCoreD2 spfCoreD2;
		/**< spfClpD0		(+0198h) */
		UimfltSpfClpD0 spfClpD0;
		/**< spfClpD1		(+019Ch) */
		UimfltSpfClpD1 spfClpD1;
		/**< spfClpD2		(+01A0h) */
		UimfltSpfClpD2 spfClpD2;
		/**< spfEoaddD0	(+01A4h) */
		UimfltSpfEoaddD0 spfEoaddD0;
		/**< spfEoaddD1	(+01A8h) */
		UimfltSpfEoaddD1 spfEoaddD1;
		/**< spfEoaddD2	(+01ACh) */
		UimfltSpfEoaddD2 spfEoaddD2;
		/**< epMd				(+01B0h) */
		UimfltEpMd epMd;
		/**< Unused variable */
		kuchar dmy01b401b7[0x01B8 - 0x01B4];
		/**< EP_GA_D0~3	(+01B8h,+01C0h,+01C8h,+01D0h) */
		UimfltEpGa epGaD[4];
		/**< EP_OFS_D0~3(+01D8h,+01E0h,+01E8h,+01F0h) */
		UimfltEpOfs epOfsD[4];
		/**< EP_BD_D0~3	(+01F8h,+0200h,+0208h,+0210h) */
		UimfltEdBd epBdD[4];
		/**< edFm				(+0218h) */
		UimfltEdFm edFm;
		/**< edOut			(+021Ch) */
		UimfltEdOut edOut;
		/**< adaptK			(+0220h) */
		UimfltAdaptK adaptK;
		/**< adaptTh			(+0224h) */
		UimfltAdaptTh adaptTh;
		/**< adaptDiv		(+0228h) */
		UimfltAdaptDiv adaptDiv;
		/**< uplkTarget		(+022Ch) */
		UimfltUplkTarget uplkTarget;
		/**< dwlkTarget	(+0230h) */
		UimfltDwlkTarget dwlkTarget;
		/**< lknum			(+0234h) */
		UimfltLknum lknum;
		/**< ring				(+0238h) */
		UimfltRing ring;
		/**< bfMd				(+023Ch) */
		UimfltBfMd bfMd;
};

/** AFN Unit Parameter */
struct _TimAfn
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=29, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< afntopcnf		(+0000h) */
		UimAfnAfntopcnf afntopcnf;
		/**< afnldcnf			(+0004h) */
		UimAfnAfnldcnf afnldcnf;
		/**< afnctl				(+0008h) */
		UimAfnAfnctl afnctl;
		/**< pfctl				(+000Ch) */
		UimAfnPfctl pfctl;
		/**< pixidef			(+0010h) */
		UimAfnPixidef pixidef;
		/**< calmethod	(+0014h) */
		UimAfnCalmethod calmethod;
		/**< filval0			(+0018h) */
		UimAfnFilval0 filval0;
		/**< filval1			(+001Ch) */
		UimAfnFilval1 filval1;
		/**< opmd				(+0020h) */
		UimAfnOpmd opmd;
		/**< Unused variable */
		kuchar dmy0024002f[0x0030 - 0x0024];
		/**< opy					(+0030h) */
		UimAfnOpy opy;
		/**< opb				(+0034h) */
		UimAfnOpb opb;
		/**< opr					(+0038h) */
		UimAfnOpr opr;
		/**< opa				(+003Ch) */
		UimAfnOpa opa;
		/**< cliplvly			(+0040h) */
		UimAfnCliplvly cliplvly;
		/**< cliplvlb			(+0044h) */
		UimAfnCliplvlb cliplvlb;
		/**< cliplvlr			(+0048h) */
		UimAfnCliplvlr cliplvlr;
		/**< cliplvla			(+004Ch) */
		UimAfnCliplvla cliplvla;
		/**< afnpcnt			(+0050h) */
		UimAfnAfnpcnt afnpcnt;
		/**< afnpa				(+0054h) */
		UimAfnAfnpa afnpa;
		/**< outsize			(+0058h) */
		UimAfnOutsize outsize;
		/**< outstartpos	(+005Ch) */
		UimAfnOutstartpos outstartpos;
		/**< uplkTarget		(+0060h) */
		UimAfnUplkTarget uplkTarget;
		/**< dwlkTarget	(+0064h) */
		UimAfnDwlkTarget dwlkTarget;
		/**< lknum			(+0068h) */
		UimAfnLknum lknum;
		/**< ring				(+006Ch) */
		UimAfnRing ring;
};

/** FRECT Unit Parameter */
struct _TimFrect
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=29, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< frtopcnf			(+0000h) */
		UimFrectFrtopcnf frtopcnf;
		/**< frldcnf			(+0004h) */
		UimFrectFrldcnf frldcnf;
		/**< frctl				(+0008h) */
		UimFrectFrctl frctl;
		/**< pfctl				(+000Ch) */
		UimFrectPfctl pfctl;
		/**< pixidef			(+0010h) */
		UimFrectPixidef pixidef;
		/**< calmethod	(+0014h) */
		UimFrectCalmethod calmethod;
		/**< filval0			(+0018h) */
		UimFrectFilval0 filval0;
		/**< filval1			(+001Ch) */
		UimFrectFilval1 filval1;
		/**< opmd				(+0020h) */
		UimFrectOpmd opmd;
		/**< Unused variable */
		kuchar dmy0024002f[0x0030 - 0x0024];
		/**< opy					(+0030h) */
		UimFrectOpy opy;
		/**< opb				(+0034h) */
		UimFrectOpb opb;
		/**< opr					(+0038h) */
		UimFrectOpr opr;
		/**< opa				(+003Ch) */
		UimFrectOpa opa;
		/**< cliplvly			(+0040h) */
		UimFrectCliplvly cliplvly;
		/**< cliplvlb			(+0044h) */
		UimFrectCliplvlb cliplvlb;
		/**< cliplvlr			(+0048h) */
		UimFrectCliplvlr cliplvlr;
		/**< cliplvla			(+004Ch) */
		UimFrectCliplvla cliplvla;
		/**< frpcnt				(+0050h) */
		UimFrectFrpcnt frpcnt;
		/**< padrs				(+0054h) */
		UimFrectPadrs padrs;
		/**< outsize			(+0058h) */
		UimFrectOutsize outsize;
		/**<outstartpos	(+005Ch) */
		UimFrectOutstartpos outstartpos;
		/**<uplkTarget		(+0060h) */
		UimFrectUplkTarget uplkTarget;
		/**<dwlkTarget		(+0064h) */
		UimFrectDwlkTarget dwlkTarget;
		/**< lknum			(+0068h) */
		UimFrectLknum lknum;
		/**< ring				(+006Ch) */
		UimFrectRing ring;
};

/** STS Unit Parameter (Basic) */
struct _TimStsBase
{
		/**< slTopcnf0		(+0000h) */
		UimStsSlTopcnf0 slTopcnf0;
		/**< pixiddef			(+0004h) */
		UimStsPixiddef pixiddef;
		/**< pldunitSl		(+0008h) */
		UimStsPldunitSl pldunitSl;
		/**< slCtl				(+000Ch) */
		UimStsSlCtl slCtl;
		/**< outcol			(+0010h) */
		UimStsOutcol outcol;
		/**< Unused variable */
		kuchar dmy0018001f[0x0020 - 0x0018];
		/**< slHsize			(+0020h) */
		UimStsSlHsize slHsize;
		/**< slVsize			(+0024h) */
		UimStsSlVsize slVsize;
		/**< slPhsz			(+0028h) */
		UimStsSlPhsz slPhsz;
		/**< slPvsz				(+002Ch) */
		UimStsSlPvsz slPvsz;
		/**< Unused variable */
		kuchar dmy0030003f[0x0040 - 0x0030];
		/**< selOpara		(+0040h) */
		UimStsSelOpara selOpara;
		/**< Unused variable */
		kuchar dmy00440047[0x0048 - 0x0044];
		/**< ofset0			(+0048h) */
		UimStsOfset ofset0;
		/**< clpthU0			(+004Ch) */
		UimStsClpthU clpthU0
		/**< clpthL0			(+0050h) */;
		UimStsClpthL clpthL0;
		/**< clpvalU0		(+0054h) */
		UimStsClpvalU clpvalU0;
		/**< clpvalL0			(+0058h) */
		UimStsClpvalL clpvalL0;
		/**< sft0					(+005Ch) */
		UimStsSft sft0;
		/**< w14md0		(+0060h) */
		UimStsW14md w14md0;
};

/** STS Unit Parameter (Out parmeter 1) */
struct _TimStsOpara1
{
		/**< ofset1			(+0064h) */
		UimStsOfset ofset1;
		/**< clpthU1			(+0068h) */
		UimStsClpthU clpthU1;
		/**< clpthL1			(+006Ch) */
		UimStsClpthL clpthL1;
		/**< clpvalU1		(+0070h) */
		UimStsClpvalU clpvalU1;
		/**< clpvalL1			(+0074h) */
		UimStsClpvalL clpvalL1;
		/**< sft1					(+0078h) */
		UimStsSft sft1;
		/**< w14md1		(+007Ch) */
		UimStsW14md w14md1;
};

/** STS Unit Parameter (Set all registers) */
struct _TimStsAll
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY, WordLength=33, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< basic parameter */
		TimStsBase base;
		/**< Output parameter 1 */
		TimStsOpara1 opara1;
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY, WordLength=3, BeginningAddress=0x0200) */
		UimPacketHeader header1;
		/**< fillEn				(+0200h) */
		UimStsFillEn fillEn;
		/**< fillData			(+0204h) */
		UimStsFillData fillData;
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=41, BeginningAddress=0x0300) */
		UimPacketHeader header2;
		/**< fillsize[20]		(+0300h) */
		UimStsFillSize fillsize[20];
};

/** STS Unit Parameter (Use out parameter 0, Fill enable) */
struct _TimStsFill
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY, WordLength=26, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< basic parameter */
		TimStsBase base;
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY, WordLength=3, BeginningAddress=0x0200) */
		UimPacketHeader header1;
		/**< fillEn				(+0200h) */
		UimStsFillEn fillEn;
		/**< fillData			(+0204h) */
		UimStsFillData fillData;
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=41, BeginningAddress=0x0300) */
		UimPacketHeader header2;
		/**< fillsize[20]		(+0300h) */
		UimStsFillSize fillsize[20];
};

/** STS Unit Parameter (Use out parameter 0, Fill disable) */
struct _TimSts
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY, WordLength=26, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< basic parameter */
		TimStsBase base;
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=2, BeginningAddress=0x0200) */
		UimPacketHeader header1;
		/**< fillEn				(+0200h) */
		UimStsFillEn fillEn;
};

/** CSC Unit Parameter */
struct _TimCsc
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=25, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< csctopcnf		(+0000h) */
		UimCscCsctopcnf csctopcnf;
		/**< Unused variable */
		kuchar dmy0004001f[0x0020 - 0x0004];
		/**< csck				(+0020h) */
		UimCscCsck csck[4];
		/**< mdsel			(+0040h) */
		UimCscMdsel mdsel;
		/**< alpsel				(+0044h) */
		UimCscAlpsel alpsel;
		UimCscAlpval alpval;
		UimCscMaxmin maxmin;
		UimCscOutclip outclip;
};

/** LUT Unit Parameter */
struct _TimLut
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=57, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< luttopcnf		(+0000h) */
		UimLutLuttopcnf luttopcnf[4];
		/**< lutunitctl		(+0010h) */
		UimLutLutunitctl lutunitctl;
		/**< Unused variable */
		kuchar dmy0014001f[0x0020 - 0x0014];
		/**< lutctlA			(+0020h) */
		UimLutLutctl lutctlA;
		/**< Unused variable */
		kuchar dmy0024002f[0x0030 - 0x0024];
		/**< lutprecalA		(+0030h) */
		UimLutLutprecal lutprecalA;
		/**< lutctlB			(+0040h) */
		UimLutLutctl lutctlB;
		/**< Unused variable */
		kuchar dmy0044004f[0x0050 - 0x0044];
		/**< lutprecalB		(+0050h) */
		UimLutLutprecal lutprecalB;
		/**< lutctlC			(+0060h) */
		UimLutLutctl lutctlC;
		/**< Unused variable */
		kuchar dmy0064006f[0x0070 - 0x0064];
		/**< lutprecalC		(+0070h) */
		UimLutLutprecal lutprecalC;
		/**< lutctlD			(+0080h) */
		UimLutLutctl lutctlD;
		/**< Unused variable */
		kuchar dmy0084008f[0x0090 - 0x0084];
		/**< lutprecalD		(+0090h) */
		UimLutLutprecal lutprecalD;
		/**< lutctlE				(+00A0h) */
		UimLutLutctl lutctlE;
		/**< Unused variable */
		kuchar dmy_00A4_00AF[0x00B0 - 0x00A4];
		/**< lutprecalE		(+00B0h) */
		UimLutLutprecal lutprecalE;
		UimLutLutctl lutctlF;
		/**< Unused variable */
		kuchar dmy00c400cf[0x00D0 - 0x00C4];
		/**< lutprecalF		(+00D0h) */
		UimLutLutprecal lutprecalF;
};

/** GPC Unit Parameter */
struct _Timgpc
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=7, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< gpctopcnf		(+0000h) */
		UimgpcGpctopcnf gpctopcnf[2];
		/**< Unused variable */
		kuchar dmy0008000f[0x0010 - 0x0008];
		/**< gpccontrol		(+0010h) */
		UimgpcGpccontrol gpccontrol;
		/**< gpccloadadr	(+0014h) */
		UimgpcGpccloadadr gpccloadadr;
};

/** Blend Unit Parameter */
struct _TimBlend
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY, WordLength=4, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< blendtopcnf0(+0000h) */
		UimBlendBlendtopcnf0 blendtopcnf0;
		/**< blendtopcnf1(+0004h) */
		UimBlendBlendtopcnf1 blendtopcnf1;
		/**< blendtopcnf2(+0008h) */
		UimBlendBlendtopcnf2 blendtopcnf2;
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=24, BeginningAddress=0x0080) */
		UimPacketHeader header1;
		/**< blendctl			(+0080h) */
		UimBlendBlendctl blendctl;
		/**< Unused variable */
		kuchar dmy00840087[0x0088 - 0x0084];
		/**< alphactl0		(+0088h) */
		UimBlendAlphactl0 alphactl0;
		/**< alphactl1		(+008Ch) */
		UimBlendAlphactl1 alphactl1;
		/**< alphactl2		(+0090h) */
		UimBlendAlphactl2 alphactl2;
		/**< Unused variable */
		kuchar dmy00940097[0x0098 - 0x0094];
		/**< WADDCTL0~3	(+0098h) */
		UimBlendWaddctl waddctl[4];
		/**< Unused variable */
		kuchar dmy00a800ab[0x00AC - 0x00A8];
		/**< divctl0			(+00ACh) */
		UimBlendDivctl0 divctl0;
		/**< Unused variable */
		kuchar dmy00b000b3[0x00B4 - 0x00B0];
		/**< mskctl0			(+00B4h) */
		UimBlendMskctl0 mskctl0;
		/**< Unused variable */
		kuchar dmy_00B8_00BB[0x00BC - 0x00B8];
		/**< mulctl[4]		(+00BCh) */
		UimBlendMulctl mulctl[4];
};

/** MON Unit Parameter */
struct _TimMon
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=25, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		/**< monctl			(+0000h) */
		UimMonMonctl monctl;
		/**< mondsel		(+0004h) */
		UimMonMondsel mondsel;
		/**< Unused variable */
		kuchar dmy0008000f[0x0010 - 0x0008];
		/**< histctl				(+0010h) */
		UimMonHistctl histctl[4];
		/**< absmax			(+0020h) */
		UimMonAbsmax absmax;
		/**< absmin			(+0024h) */
		UimMonAbsmin absmin;
		/**< Unused variable */
		kuchar dmy0028003f[0x0040 - 0x0028];
		/**< absadd			(+0040h) */
		UimMonAbsadd absadd;
		/**< Unused variable */
		kuchar dmy0044004f[0x0050 - 0x0044];
		/**< overvalue		(+0050h) */
		UimMonOvervalue overvalue[4];
};

/** CFLOW Unit Parameter */
struct _TimCflow
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=9, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		UimCflowDiffCftopconf cftopconf;
		/**< Unused variable */
		kuchar dmy0004000f[0x0010 - 0x0004];
		/**< diffPrewait	(+0010h) */
		UimCflowDiffPrewait diffPrewait;
		UimCflowDiffPostwait diffPostwait;
		UimCflowMagpow magpow;
		/**< cfmode			(+001Ch) */
		UimCflowCfmode cfmode;
};

/** MFT Unit Parameter */
struct _TimMft
{
		/**< Packet header (CtrlCode=ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, WordLength=9, BeginningAddress=0x0000) */
		UimPacketHeader header0;
		UimMftMfttopconf fttopconf;
		UimMftMftmd mftmd;
		UimMftFlttpsz flttpsz;
		UimMftFltouthsz fltouthsz;
		UimMftMftctl mftctld[4];
} ;

/** Unit Registers of UNITDEBUG register space. */
union _UimUnitdebug
{
		/**< AFN unit registers. */
		TimAfnDump afn;
		TimFrectDump frect;
		Tim1dlDump ld;
		TimBlendDump blend;
		TimCflowDump cfl;
		TimCscDump csc;
		TimgpcDump gpc;
		TimLutDump lut;
		TimMftDump mft;
		TimMonDump mon;
		TimFltDump flt;
		TimStsDump sts;
};

struct _ImIipUnitParameter
{
	KObject parent;
};


KConstType 		    					im_iip_unit_parameter_get_type(void);
ImIipUnitParameter*		        im_iip_unit_parameter_new(void);


#ifdef __cplusplus
}
#endif


#endif /* __IM_IIP_UNIT_PARAMETER_H__ */
