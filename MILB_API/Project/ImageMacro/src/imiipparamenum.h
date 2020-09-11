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


#ifndef __IM_IIP_PARAM_ENUM_H__
#define __IM_IIP_PARAM_ENUM_H__


#include <klib.h>
#include "ddimtypedef.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_PARAM_ENUM					(im_iip_param_enum_get_type())
#define IM_IIP_PARAM_ENUM	(obj)					(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipParamEnum))
#define IM_IS_IIP_PARAM_ENUM	(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_PARAM_ENUM	))

typedef enum _EimCtlCode					EimCtlCode;
typedef enum _EimPortid						EimPortid;
typedef enum _EimUpsu						EimUpsu;
typedef enum _EimUpnum					EimUpnum;
typedef enum _EimDwsu						EimDwsu;
typedef enum _EimDwnum					EimDwnum;
typedef enum _EimDthd						EimDthd;
typedef enum _EimCbc							EimCbc;
typedef enum _EimGhsz						EimGhsz;
typedef enum _EimGvsz						EimGvsz;
typedef enum _EimLplvl						EimLplvl;
typedef enum _EimHdbl						EimHdbl;
typedef enum _EimVdbl						EimVdbl;
typedef enum _EimHsmd						EimHsmd;
typedef enum _EimPfsp						EimPfsp;
typedef enum _EimPfvsp						EimPfvsp;
typedef enum _EimPfoff						EimPfoff;
typedef enum _EimExa							EimExa;
typedef enum _EimItmd						EimItmd;
typedef enum _EimAra							EimAra;
typedef enum _EimCubsel					EimCubsel;
typedef enum _EimScub						EimScub;
typedef enum _EimOpmd						EimOpmd;
typedef enum _EimCsel						EimCsel;
typedef enum _EimLdMode					EimLdMode;
typedef enum _EimSlow						EimSlow;
typedef enum _EimPfPdist					EimPfPdist;
typedef enum _EimPf1st						EimPf1st;
typedef enum _EimBldMd					EimBldMd;
typedef enum _EimClpMd					EimClpMd;
typedef enum _EimAlphaOut				EimAlphaOut;
typedef enum _EimAlphaStep				EimAlphaStep;
typedef enum _EimAlphaSel				EimAlphaSel;
typedef enum _EimSftsel						EimSftsel;
typedef enum _EimAlpsel						EimAlpsel;
typedef enum _EimAlosel						EimAlosel;
typedef enum _EimMaxmin					EimMaxmin;
typedef enum _EimCommonpara		EimCommonpara;
typedef enum _EimAtrb						EimAtrb;
typedef enum _EimLutuse					EimLutuse;
typedef enum _EimLutsgn					EimLutsgn;
typedef enum _EimDsel						EimDsel;
typedef enum _EimSgnen						EimSgnen;
typedef enum _EimBitsel						EimBitsel;
typedef enum _EimFm							EimFm;
typedef enum _EimLnum						EimLnum;
typedef enum _EimInputMode			EimInputMode;
typedef enum _EimPfOn						EimPfOn;
typedef enum _EimPfMd						EimPfMd;
typedef enum _EimUnitOut					EimUnitOut;
typedef enum _EimSpfMd					EimSpfMd;
typedef enum _EimEpMd						EimEpMd;
typedef enum _EimEdFm						EimEdFm;
typedef enum _EimEdOut						EimEdOut;
typedef enum _EimAdaptDiv				EimAdaptDiv;
typedef enum _EimCalcMd					EimCalcMd;
typedef enum _EimBfFmt						EimBfFmt;
typedef enum _EimBfPrt						EimBfPrt;
typedef enum _EimDiv1st						EimDiv1st;
typedef enum _EimMasken					EimMasken;
typedef enum _EimSftm						EimSftm;
typedef enum _EimFillEn						EimFillEn;
typedef enum _EimMftmd					EimMftmd;
typedef enum _EimDnfix						EimDnfix;
typedef enum _EimParaad					EimParaad;
typedef enum _EimCompsel				EimCompsel;
typedef enum _EimRnd							EimRnd;
typedef enum _EimConfregsel				EimConfregsel;
typedef enum _EimElesel						EimElesel;
typedef enum _EimEleshift					EimEleshift;
typedef enum _EimElemode				EimElemode;
typedef enum _EimGpcsel					EimGpcsel;
typedef enum _EimGmdMul				EimGmdMul;
typedef enum _EimGmdBin					EimGmdBin;
typedef enum _EimGpcalpsel				EimGpcalpsel;
typedef enum _EimGpcalpmode			EimGpcalpmode;
typedef enum _EimSedly						EimSedly;
typedef enum _EimSesel0					EimSesel0;
typedef enum _EimSesel1					EimSesel1;
typedef enum _EimP1selo					EimP1selo;
typedef enum _EimP0selo					EimP0selo;
typedef enum _EimSzpowh					EimSzpowh;
typedef enum _EimSzpowv					EimSzpowv;

typedef struct _ImIipParamEnum 						ImIipParamEnum;
typedef struct _ImIipParamEnumPrivate 			ImIipParamEnumPrivate;



/*----------------------------------------------------------------------*/
/* Enumeration																*/
/*----------------------------------------------------------------------*/
/** Control code of packet header */
enum _EimCtlCode{
	ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY = 0x11,
	ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET = 0x01,
	ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE = 0x02,
	ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_NEXT_CHAIN = 0x03,
} ;
/** PORT ID */
enum _EimPortid{
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD2 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD3 = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FLT_P0 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FLT_P1 = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_AFN0 = 6,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_AFN1 = 7,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_AFN2 = 8,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FRECT0 = 9,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL0 = 10,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL1 = 12,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2 = 14,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL3 = 16,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL4 = 18,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL5 = 20,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL6 = 22,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FRECT1 = 24,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL7 = 26,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL8 = 28,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_CSC0 = 32,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_CSC1 = 33,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LUT_P0 = 34,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LUT_P1 = 35,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LUT_P2 = 36,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LUT_P3 = 37,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_GPC_P0 = 38,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_GPC_P1 = 39,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_BLEND0_P0 = 40,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_BLEND0_P1 = 41,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_BLEND0_P2 = 42,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_CFL0_P0 = 44,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_CFL0_P1 = 45,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_CSC2 = 52,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_CSC3 = 53,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD4 = 54,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD5 = 55,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD6 = 56,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD7 = 57,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_AFN3 = 58,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_BLEND1_P0 = 59,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_BLEND1_P1 = 60,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_BLEND1_P2 = 61,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_MFT = 62,
	ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE = 0x3F
} ;
/** Unit of upper stream */
enum _EimUpsu{
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_NONE = 0x0,
	/**< B2Y macro [FRECT and AFN unit only] */
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_B2Y = 0x1,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_AFN0 = 0x2,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_AFN1 = 0x3,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_AFN2 = 0x4,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_AFN3 = 0x5,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_FRECT0 = 0x6,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_FRECT1 = 0x7,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_FLT = 0x8,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_LD0 = 0x9,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_LD1 = 0xA,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_LD2 = 0xB,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_LD3 = 0xC,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_LD4 = 0xD,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_LD5 = 0xE,
	ImIipParamEnum_E_IM_IIP_PARAM_UPSU_LD6 = 0xF,
} ;
/** Unit number of upper stream */
enum _EimUpnum{
	ImIipParamEnum_E_IM_IIP_PARAM_UPNUM_NONE = 0x0,
	/**< Unit number is 1 */
	ImIipParamEnum_E_IM_IIP_PARAM_UPNUM_1 = 0x1,
	ImIipParamEnum_E_IM_IIP_PARAM_UPNUM_2 = 0x2,
} ;
/** Unit of lower stream */
enum _EimDwsu{
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_NONE = 0x0,
	/**< AFN0-UNIT [AFN, FRECT, FLT and LD unit only] */
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_AFN0 = 0x2,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_AFN1 = 0x3,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_AFN2 = 0x4,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_AFN3 = 0x5,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_FLT = 0x8,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_LD0 = 0x9,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_LD1 = 0xA,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_LD2 = 0xB,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_LD3 = 0xC,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_LD4 = 0xD,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_LD5 = 0xE,
	ImIipParamEnum_E_IM_IIP_PARAM_DWSU_LD6 = 0xF,
} ;
/** Unit number of lower stream */
enum _EimDwnum{
	ImIipParamEnum_E_IM_IIP_PARAM_DWNUM_NONE = 0x0,
	/**< Unit number is 1 */
	ImIipParamEnum_E_IM_IIP_PARAM_DWNUM_1 = 0x1,
	ImIipParamEnum_E_IM_IIP_PARAM_DWNUM_2 = 0x2,
} ;
/** Dirty bit preserved cache read */
enum _EimDthd{
	ImIipParamEnum_E_IM_IIP_PARAM_DTHD_NORMAL = 0x0,
} ;
/** Corner Blur Correction mode */
enum _EimCbc{
	ImIipParamEnum_E_IM_IIP_PARAM_CBC_DISABLE = 0x0,
	ImIipParamEnum_E_IM_IIP_PARAM_CBC_ENABLE = 0x1,
} ;
/** ghsz of afnctl ghsz of frctl*/
enum _EimGhsz{
	ImIipParamEnum_E_IM_IIP_PARAM_GHSZ_64PIX = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_GHSZ_32PIX = 1,
} ;
/** gvsz of afnctl gvsz of frctl*/
enum _EimGvsz{
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_SAME_AS_VERTICAL_PIX = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_2PIX = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_4PIX = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_8PIX = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_16PIX = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_32PIX = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_64PIX = 6,
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_128PIX = 7,
	ImIipParamEnum_E_IM_IIP_PARAM_GVSZ_256PIX = 8,
} ;
/** lplvl of afnctl lplvl of frctl */
enum _EimLplvl{
	/**< Output High level when the last pixel is transfered. */
	ImIipParamEnum_E_IM_IIP_PARAM_LPLVL_H_LEVEL = 1,
} ;
/**hdbl of afnctl hdbl of frctl*/
enum _EimHdbl{
	ImIipParamEnum_E_IM_IIP_PARAM_HDBL_SAME_AS_PICHSZ = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_HDBL_DOUBLE_PICHSZ = 1,
} ;
/** vdbl of afnctl vdbl of frctl*/
enum _EimVdbl{
	ImIipParamEnum_E_IM_IIP_PARAM_VDBL_SAME_AS_PICVSZ = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_VDBL_DOUBLE_PICVSZ = 1,
} ;
/** hsmd of afnctl  hsmd of frctl */
enum _EimHsmd{
	ImIipParamEnum_E_IM_IIP_PARAM_HSMD_NORMAL = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_HSMD_HIGH = 1,
} ;
/** PFSP of pfctl*/
enum _EimPfsp{
	/**< Prefetch interval 1	*/
	ImIipParamEnum_E_IM_IIP_PARAM_PFSP_1 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_PFSP_2 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_PFSP_4 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_PFSP_8 = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_PFSP_16 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_PFSP_32 = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_PFSP_64 = 6,
	ImIipParamEnum_E_IM_IIP_PARAM_PFSP_128 = 7,
} ;
/** pfvsp of pfctl*/
enum _EimPfvsp{
	ImIipParamEnum_E_IM_IIP_PARAM_PFVSP_VERTICAL_0 = 0,
} ;
/** pfoff of ldPrefetch pfoff of pfctl*/
enum _EimPfoff{
	ImIipParamEnum_E_IM_IIP_PARAM_PFOFF_RUN = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_PFOFF_STOP = 1,
} ;
/**  exa of pixidef*/
enum _EimExa{
	ImIipParamEnum_E_IM_IIP_PARAM_EXA_NO_ALPHA_TO_NEXT_UNIT = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_EXA_ALPHA_TO_NEXT_UNIT = 1,
} ;
/** itmd of calmethod*/
enum _EimItmd{
	ImIipParamEnum_E_IM_IIP_PARAM_ITMD_BI_LINEAR = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ITMD_NEAREST = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_ITMD_BI_CUBIC = 2,
} ;
/** ara of calmethod*/
enum _EimAra{
	ImIipParamEnum_E_IM_IIP_PARAM_ARA_ITMD = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ARA_REDUCE_1_4 = 1,
} ;
/** cubsel of calmethod*/
enum _EimCubsel{
	ImIipParamEnum_E_IM_IIP_PARAM_CUBSEL_AFN0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_CUBSEL_AFN1 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_CUBSEL_AFN2 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_CUBSEL_AFN3 = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_CUBSEL_FRECT0 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_CUBSEL_FRECT1 = 5,
} ;
/**  scub of calmethod*/
enum _EimScub{
	ImIipParamEnum_E_IM_IIP_PARAM_SCUB_0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SCUB_1 = 1,
} ;
/**  opmd*/
enum _EimOpmd{
	ImIipParamEnum_E_IM_IIP_PARAM_OPMD_NON = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_OPMD_ADD = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_OPMD_SUB = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_OPMD_EOR = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_OPMD_OR	= 4,
	ImIipParamEnum_E_IM_IIP_PARAM_OPMD_AND = 5,
} ;
/** csel of ldCtl	csel of tdlCtl	csel of pixiddef	csel of pixidef*/
enum _EimCsel{
	ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0 = 0x0,
	ImIipParamEnum_E_IM_IIP_PARAM_CSEL_1 = 0x1,
	/**< Cache controller 2. */
	ImIipParamEnum_E_IM_IIP_PARAM_CSEL_2 = 0x2,
} ;
/** ldMode of ldCtl */
enum _EimLdMode{
	ImIipParamEnum_E_IM_IIP_PARAM_LD_MODE_NORMAL_LOAD = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_LD_MODE_LINK = 3,
} ;
/** slow of ldCtl */
enum _EimSlow{
	ImIipParamEnum_E_IM_IIP_PARAM_SLOW_2PIX_CYC = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SLOW_1PIX_CYC = 1,
} ;
/**  pfPdist of ldPrefetch */
enum _EimPfPdist{
	ImIipParamEnum_E_IM_IIP_PARAM_PF_PDIST_8PIX  = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_PF_PDIST_16PIX = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_PF_PDIST_32PIX = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_PF_PDIST_64PIX = 3,
} ;
/**   pf1st of ldPrefetch */
enum _EimPf1st{
	ImIipParamEnum_E_IM_IIP_PARAM_PF_1ST_ACCESS_BEFORE_PF = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_PF_1ST_ACCESS_AFTER_PF = 1,
} ;
/**   bldMd of blendctl */
enum _EimBldMd{
	ImIipParamEnum_E_IM_IIP_PARAM_BLD_MD_ALPHA_BLEND = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_BLD_MD_W_ADD = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_BLD_MD_SUB = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_BLD_MD_MASK_TBL = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_BLD_MD_MUL = 4,
} ;
/**  clpMd of blendctl */
enum _EimClpMd{
	ImIipParamEnum_E_IM_IIP_PARAM_CLP_MD_NO_CLIP = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_CLP_MD_CLIP_UNSIGNED_8 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_CLP_MD_CLIP_SIGNED_8 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_CLP_MD_CLIP_HYBRID_8 = 3,
} ;
/**  alphaOut of blendctl */
enum _EimAlphaOut{
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA = 0,
	/**< Alpha of Port 1 */
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P1_ALPHA = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_NONE = 3,
} ;
/** alphaStep of alphactl0 */
enum _EimAlphaStep{
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_STEP_8BITS = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_STEP_4BITS = 3,
} ;
/** alphaSel of ALHACTL*/
enum _EimAlphaSel{
	/**< Alpha of Port 0 */
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P1_ALPHA = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P2_D0_D1_D2_ALPHA = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P2_D0_ALPHA = 4,
} ;
/**  sftsel of mulctl */
enum _EimSftsel{
	/**< 14bit Right shift */
	ImIipParamEnum_E_IM_IIP_PARAM_SFTSEL_14BIT = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SFTSEL_12BIT = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_SFTSEL_8BIT = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_SFTSEL_NONE = 2,
} ;
/** CSC  alpsel */
enum _EimAlpsel{
	/**< Direct */
	ImIipParamEnum_E_IM_IIP_PARAM_ALPSEL_DIRECT = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ALPSEL_ALPVAL_REG = 1,
} ;
/** alosel */
enum _EimAlosel{
	/**< Calculated value */
	ImIipParamEnum_E_IM_IIP_PARAM_ALOSEL_CALCULATED = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ALOSEL_THROUGH = 1,
} ;
/**  maxmin */
enum _EimMaxmin{
	/**< Through */
	ImIipParamEnum_E_IM_IIP_PARAM_MAXMIN_THROUGH = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_MAXMIN_MAX = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_MAXMIN_MIN = 3,
} ;
// GPC
/**  commonpapa of gpccontrol */
enum _EimCommonpara{
	/**< D0:D0 parameter | D1:D1 parameter | D2:D2 parameter */
	ImIipParamEnum_E_IM_IIP_PARAM_COMMONPARA_D0_D1_D2 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_COMMONPARA_D0_D1_D1 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_COMMONPARA_D0_D0_D0 = 2,
} ;
/**  atrb0/atrb1 */
enum _EimAtrb{
	/**< Through input port 0 image type */
	ImIipParamEnum_E_IM_IIP_PARAM_ATRB_PORT0 = 0x0,
	ImIipParamEnum_E_IM_IIP_PARAM_ATRB_YUV_RGB = 0x8,
	ImIipParamEnum_E_IM_IIP_PARAM_ATRB_CBCR = 0x9,
	ImIipParamEnum_E_IM_IIP_PARAM_ATRB_PALNE = 0xB,
} ;
// LUT
/**  use of LUTCTL */
enum _EimLutuse{
	/**< Output of Precal (No LUT) */
	ImIipParamEnum_E_IM_IIP_PARAM_LUTUSE_PRECALC = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_LUTUSE_LUT_OUT = 1,
} ;
/** sgn of LUTCTL */
enum _EimLutsgn{
	ImIipParamEnum_E_IM_IIP_PARAM_LUTSGN_UNSIGN = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_LUTSGN_SIGN = 1,
} ;
// MON
/**   dsel of mondsel */
enum _EimDsel{
	/**< SL 0 */
	ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL1 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL2 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL3 = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL4 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL5 = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL6 = 6,
	ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL7 = 7,
} ;
/** sgnen0 of mondsel sgnen1 of mondsel sgnen2 of mondsel  sgnen3 of mondsel */
enum _EimSgnen{
	/**< Unsigned */
	ImIipParamEnum_E_IM_IIP_PARAM_SGNEN_UNSIGN = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SGNEN_SIGN = 1,
};
/** BITSEL_0 of histctl  BITSEL_1 of histctl  BITSEL_2 of histctl */
enum _EimBitsel{
	/**< [7:0] */
	ImIipParamEnum_E_IM_IIP_PARAM_BITSEL_7_0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_BITSEL_9_2 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_BITSEL_11_4 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_BITSEL_13_6 = 3,
} ;
// FLT
/**  fm of tdlCtl */
enum _EimFm{
	/**< 3x3 */
	ImIipParamEnum_E_IM_IIP_PARAM_FM_3x3 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_FM_4x4 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_FM_5x5 = 2,
} ;
/**  lnum of tdlCtl */
enum _EimLnum{
	/**< Slow */
	ImIipParamEnum_E_IM_IIP_PARAM_LNUM_SLOW = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_LNUM_FAST = 1,
} ;
/**  inputMode of tdlCtl */
enum _EimInputMode{
	/**< Normal */
	ImIipParamEnum_E_IM_IIP_PARAM_INPUT_MODE_NORMAL = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_INPUT_MODE_SLINK = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_INPUT_MODE_DLINK = 3,
} ;
/**   pfOn of tdlPf */
enum _EimPfOn{
	/**< Invalid prefetch */
	ImIipParamEnum_E_IM_IIP_PARAM_PF_ON_INVALID = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_PF_ON_ACTIVE = 1,
} ;
/**   pfMd of tdlPf */
enum _EimPfMd{
	ImIipParamEnum_E_IM_IIP_PARAM_PF_MD_ACCESS = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_PF_MD_PREFETCH = 1,
} ;
/**
   unitOutAD0 of unitOut<br>
   unitOutAD1 of unitOut<br>
   unitOutAD2 of unitOut<br>
   unitOutBD0 of unitOut<br>
   unitOutBD1 of unitOut<br>
   unitOutBD2 of unitOut
 */
enum _EimUnitOut{
	ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_THROUGH = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_ISO = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_EDGE = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_EP = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_SPF = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_BADC = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_DISABLE = 7,
} ;
/**   spfMd */
enum _EimSpfMd{
	/**< SPF  */
	ImIipParamEnum_E_IM_IIP_PARAM_SPF_MD_SPF = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SPF_MD_EDGE_ENHANCE = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_SPF_MD_EDGE_DETECT = 2,
} ;
/**   epMd */
enum _EimEpMd{
	ImIipParamEnum_E_IM_IIP_PARAM_EP_MD_NR_LOW = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_EP_MD_NR_MID = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_EP_MD_NR_HIGH = 2,
} ;
/**   edFm */
enum _EimEdFm{
	/**< Near 4 pxiels */
	ImIipParamEnum_E_IM_IIP_PARAM_ED_FM_NEAR4 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ED_FM_NEAR8 = 1,
} ;
/**   edOut */
enum _EimEdOut{
	/**< min(|P0 - Px|) */
	ImIipParamEnum_E_IM_IIP_PARAM_ED_OUT_DIFF_ABS_MIN = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ED_OUT_DIFF_ABS_MAX = 1,
} ;
/**   adaptDiv */
enum _EimAdaptDiv{
	/**< 1/1 */
	ImIipParamEnum_E_IM_IIP_PARAM_ADAPT_DIV_1_DIVBY_1 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ADAPT_DIV_1_DIVBY_2 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_ADAPT_DIV_1_DIVBY_3 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_ADAPT_DIV_1_DIVBY_4 = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_ADAPT_DIV_1_DIVBY_8 = 4,
};
/**   calcMd */
enum _EimCalcMd{
	ImIipParamEnum_E_IM_IIP_PARAM_CALC_MD_NORMAL = 0,
	/**< Corner Blur Correction mode. */
	ImIipParamEnum_E_IM_IIP_PARAM_CALC_MD_CBC = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_CALC_MD_WSF = 2,
} ;
/**   bfFmt */
enum _EimBfFmt{
	/**< D0, D1 and D2 is valid. */
	ImIipParamEnum_E_IM_IIP_PARAM_BF_FMT_VALID_D0_D1_D2 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_BF_FMT_VALID_D0 = 1,
};
/**   BFPRT */
enum _EimBfPrt{
	ImIipParamEnum_E_IM_IIP_PARAM_BF_PRT_PORT0 = 0,
	/**< Output port is 0 and 1. */
	ImIipParamEnum_E_IM_IIP_PARAM_BF_PRT_PORT0_AND_1 = 1,
};
// SL
/**   div1st of pixiddef */
enum _EimDiv1st{
	/**< None 1st block */
	ImIipParamEnum_E_IM_IIP_PARAM_DIV1ST_NON_1ST = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_DIV1ST_1ST = 1,
};
/**  masken of slCtl */
enum _EimMasken{
	ImIipParamEnum_E_IM_IIP_PARAM_MASKEN_NO_MASK = 0,
	/**< Mask depends on alpha */
	ImIipParamEnum_E_IM_IIP_PARAM_MASKEN_DEPEND_ON_ALPHA = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_MASKEN_FRAME_MASK = 2,
};
/**   SFTM_0 of sft0<br>   SFTM_1 of sft1 */
enum _EimSftm{
	ImIipParamEnum_E_IM_IIP_PARAM_SFTM_ROUNDDOWN = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SFTM_ROUNDOFF = 1,
} ;
/** * fillEn */
enum _EimFillEn{
	/**< Rectangle fill is disable. */
	ImIipParamEnum_E_IM_IIP_PARAM_FILL_EN_DISABLE = 0x0,
	ImIipParamEnum_E_IM_IIP_PARAM_FILL_EN_ENABLE = 0x1,
} ;
// MFT
/**   mftmd */
enum _EimMftmd{
	/**< Min mode */
	ImIipParamEnum_E_IM_IIP_PARAM_MFTMD_MIN = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_MFTMD_MAX = 1,
} ;
/**   D0FIX/D1FIX/D2FIX */
enum _EimDnfix{
	ImIipParamEnum_E_IM_IIP_PARAM_DNFIX_FILTER = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_DNFIX_FIXVAL = 1,
};

///////////////////////////////////////////////////////////////
// GPC Struct Parameter
///////////////////////////////////////////////////////////////
/** Valid value of paraad (associated with GPC unit) */
enum _EimParaad{
	/**< Sequence control */
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_SEQ_CTRL		= 0x000,
	/**< Pre-calculation (PORT0 D0, D1) */
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D0_1  = 0x100,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D2_3  = 0x140,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P1_D0_1  = 0x180,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P1_D2_3  = 0x1C0,
	/**< Configuration[0] of General calculation for D0 compoment */
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG0	= 0x200,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG1	= 0x240,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG2	= 0x280,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG3	= 0x2C0,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D1_CFG0	= 0x300,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D1_CFG1	= 0x340,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D1_CFG2	= 0x380,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D1_CFG3	= 0x3C0,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D2_CFG0	= 0x400,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D2_CFG1	= 0x440,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D2_CFG2	= 0x480,
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D2_CFG3	= 0x4C0,
	/**< Configuration[0][1][2][3] of Alpha */
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_ALPHA			= 0x500,
	/**< Inter color calculation */
	ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_INTER_COMP_CALC = 0x540
};
/**   compsel register<br>   compsel */
enum _EimCompsel {
	/**< D0 of Port 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_P0D0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_P1D0 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_P0D3 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_P1D3 = 3,
	/**< Config register 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG0 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG1 = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG2 = 6,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG3 = 7,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG4 = 8,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG5 = 9,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG6 = 10,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG7 = 11,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG8 = 12,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG9 = 13,
	/**< D1 of Port 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_P0D1 = 14,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_P1D1 = 15,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_P0D2 = 16,
	ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_P1D2 = 17,
} ;
/**gpc0para1 register<br>
 ELERD0_0 / ELERD0_1 / ELERD0_2 / ELERD0_3 /
 ELERD1_0 / ELERD1_1 / ELERD1_2 / ELERD1_3 /
 ELERD2_0 / ELERD2_1 / ELERD2_2 / ELERD2_3 /
 ELERD3_0 / ELERD3_1 / ELERD3_2 / ELERD3_3 /
 ELERDO_0 / ELERDO_1 / ELERDO_2 / ELERDO_3
 */
enum _EimRnd{
	/**< Round-down */
	ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDOFF = 1,
} ;
/** confcnt register<br>
 confregsel0 / confregsel1 / confregsel2 / confregsel3 / confregsel4 /
 confregsel5 / confregsel6 / confregsel7 / confregsel8 / confregsel9
 */
enum _EimConfregsel{
	/**< D0 of Port 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P0D0	= 0,
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P1D0	= 1,
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P0D3	= 2,
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P1D3	= 3,
	/**< Calculation 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CALC0 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CALC1 = 5,
	/**< Comparator		*/
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_COMP	= 6,
	/**< Config register n-1 */
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n_1 = 7,
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n = 8,
	/**< D0 of Port 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P0D1	= 9,
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P1D1	= 10,
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P0D2	= 11,
	ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P1D2	= 12,
};
/**   elecal register
 ELESEL0_0 / ELESEL0_1 / ELESEL0_2 / ELESEL0_3 /
 ELESEL1_0 / ELESEL1_1 / ELESEL1_2 / ELESEL1_3 /
 ELESEL2_0 / ELESEL2_1 / ELESEL2_2 / ELESEL2_3 /
 ELESEL3_0 / ELESEL3_1 / ELESEL3_2 / ELESEL3_3
 */
enum _EimElesel{
	/**< Config register 9 of D0 */
	ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D0_CFG9 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D1_CFG9 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D2_CFG9 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D3_ALPHA = 3,
} ;
/**elecal register<br>
 *   ELESHIFT0_0 / ELESHIFT0_1 / ELESHIFT0_2 / ELESHIFT0_3 /
 *   ELESHIFT1_0 / ELESHIFT1_1 / ELESHIFT1_2 / ELESHIFT1_3 /
 *   ELESHIFT2_0 / ELESHIFT2_1 / ELESHIFT2_2 / ELESHIFT2_3 /
 *   ELESHIFT3_0 / ELESHIFT3_1 / ELESHIFT3_2 / ELESHIFT3_3 /
 *   ELESHIFTO_0 / ELESHIFTO_1 / ELESHIFTO_2 / ELESHIFTO_3
 */
enum _EimEleshift{
	ImIipParamEnum_E_IM_IIP_PARAM_ELESHIFT_RIGHT = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ELESHIFT_LEFT = 1,
};
/**elecal register<br>
 * ELEMODE0_0 / ELEMODE0_1 / ELEMODE0_2 / ELEMODE0_3 /
 * ELEMODE1_0 / ELEMODE1_1 / ELEMODE1_2 / ELEMODE1_3 /
 * ELEMODE2_0 / ELEMODE2_1 / ELEMODE2_2 / ELEMODE2_3
 */
enum _EimElemode{
	ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_AND = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_OR = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_EOR = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_ADD = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_SUB = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_ABS = 6,
};
/**gpc0para0 register gpc0sel0 / gpc0sel1 / gpc0sel2 / gpc0sel3
 *	 gpc1para0 register gpc1sel0 / gpc1sel1 / gpc1sel2*/
enum _EimGpcsel{
	/**< D0 of Port 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P0D0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P1D0 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P0D3 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P1D3 = 3,
	/**< Config register 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG0 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG1 = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG2 = 6,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG3 = 7,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG4 = 8,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG5 = 9,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG6 = 10,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG7 = 11,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG8 = 12,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG9 = 13,
	/**< D1 of Port 0	*/
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P0D1 = 14,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P1D1 = 15,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P0D2 = 16,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P1D2 = 17,
} ;
/** gpc0para0 register g0md0 / g0md1  gpc1para0 register g1md0 */
enum _EimGmdMul{
	/**< Through */
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_THROUGH = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_MUL = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_MAX = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_MIN = 3,
} ;
/** gpc0para0 register g0md2  gpc1para0 register g1md1 */
enum _EimGmdBin{
	/**< Through */
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_THROUGH = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_AND = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_OR = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_EOR = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_ADD = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_SUB = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_ABS = 6,
} ;
/**gpcalp register<br>
 GPCALPSEL0_0 / GPCALPSEL0_1 / GPCALPSEL0_2 / GPCALPSEL0_3 /
 GPCALPSEL1_0 / GPCALPSEL1_1 / GPCALPSEL1_2 / GPCALPSEL1_3
 */
enum _EimGpcalpsel{
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P0D3 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P1D3 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_GPCALPFIX = 2,
} ;
/**gpcalp register<br> GPCALPMODE_0 / GPCALPMODE_1 / GPCALPMODE_2 / GPCALPMODE_3*/
enum _EimGpcalpmode{
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_THROUGH = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_AND = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_OR = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_EOR = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_ADD = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_SUB = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_ABS = 6,
} ;
/** serpass register<br> sedly1 / sedly2 / sedly3 */
enum _EimSedly{
	ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_4_STEP = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_8_STEP = 2,
} ;
/**serpass register<br> sesel0 */
enum _EimSesel0 {
	ImIipParamEnum_E_IM_IIP_PARAM_SESEL0_INPUT_SELECTOR = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SESEL0_CALC0_OUT = 1,
} ;
/**serpass register<br>sesel1*/
enum _EimSesel1{
	ImIipParamEnum_E_IM_IIP_PARAM_SESEL1_INPUT_SELECTOR = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SESEL1_COMP_OUT = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_SESEL1_CALC0_OUT = 2,
} ;
/**p1selo0/p1selo1/p1selo2/p1selo3 register*/
enum _EimP1selo{
	ImIipParamEnum_E_IM_IIP_PARAM_P1SELO_CONF6_D0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_P1SELO_CONF6_D1 = 1,
	/**< Select D2 value of Config register 6 */
	ImIipParamEnum_E_IM_IIP_PARAM_P1SELO_CONF6_D2 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_P1SELO_ALPHA = 3,
} ;
/**   p0seloD3 register   */
enum _EimP0selo {
	/**< Select D0 value of Config register 9 */
	ImIipParamEnum_E_IM_IIP_PARAM_P0SELO_CONF9_D0 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_P0SELO_CONF9_D1 = 1,
	ImIipParamEnum_E_IM_IIP_PARAM_P0SELO_CONF9_D2 = 2,
	ImIipParamEnum_E_IM_IIP_PARAM_P0SELO_ALPHA = 3,
} ;
/** szpowh */
enum _EimSzpowh {
	/**< 256 pixels */
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWH_256 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWH_8 = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWH_16 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWH_32 = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWH_64 = 6,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWH_128 = 7
} ;
/** szpowv */
enum _EimSzpowv{
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWV_256 = 0,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWV_8 = 3,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWV_16 = 4,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWV_32 = 5,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWV_64 = 6,
	ImIipParamEnum_E_IM_IIP_PARAM_SZPOWV_128 = 7
} ;


struct _ImIipParamEnum
{
	KObject parent;
};


KConstType 		    				im_iip_param_enum_get_type(void);
ImIipParamEnum*		        im_iip_param_enum_new(void);


#ifdef __cplusplus
}
#endif


#endif /* __IM_IIP_PARAM_ENUM_H__ */
