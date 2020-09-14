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


#ifndef __IM_IIP_GPC_PARAMETER_H__
#define __IM_IIP_GPC_PARAMETER_H__


#include <stdio.h>
#include <glib-object.h>
#include "imiipunitparameter.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_GPC_PARAMETER			(im_iip_gpc_parameter_struct_get_type ())
#define IM_IIP_GPC_PARAMETER(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_IIP_GPC_PARAMETER, ImIipGpcParameter))
#define IM_IIP_GPC_PARAMETER_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_IIP_GPC_PARAMETER, ImIipGpcParameterClass))
#define IM_IS_IIP_GPC_PARAMETER(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_IIP_GPC_PARAMETER))
#define IM_IS_IIP_GPC_PARAMETER_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_IIP_GPC_PARAMETER))
#define IM_IIP_GPC_PARAMETER_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_IIP_GPC_PARAMETER, ImIipGpcParameterClass))


typedef union _UimgpcParacnt						UimgpcParacnt;
typedef union _UimgpcSeqctl							UimgpcSeqctl;
typedef union _UimgpcPrecal							UimgpcPrecal;
typedef union _UimgpcGpc0para0					UimgpcGpc0para0;
typedef union _UimgpcGpc0para1					UimgpcGpc0para1;
typedef union _UimgpcGpc1para0					UimgpcGpc1para0;
typedef union _UimgpcGpc1para1					UimgpcGpc1para1;
typedef union _UimgpcSerpass						UimgpcSerpass;
typedef union _UimgpcCompsel						UimgpcCompsel;
typedef union _UimgpcConfcnf						UimgpcConfcnf;
typedef union _UimgpcGpcalp							UimgpcGpcalp;
typedef union _UimgpcP1outmd						UimgpcP1outmd;
typedef union _UimgpcP0outmdD3				UimgpcP0outmdD3;
typedef union _UimgpcElecal							UimgpcElecal;
typedef struct _TimgpcSeqCtrl							TimgpcSeqCtrl;
typedef struct _TimgpcPrecal							TimgpcPrecal;
typedef struct _TimgpcCalc								TimgpcCalc;
typedef struct _TimgpcAlpha							TimgpcAlpha;
typedef struct _TimgpcInterCompCalc			TimgpcInterCompCalc;

typedef struct _ImIipGpcParameter				ImIipGpcParameter;
typedef struct _ImIipGpcParameterClass		ImIipGpcParameterClass;
typedef struct _ImIipGpcParameterPrivate 	ImIipGpcParameterPrivate;



///////////////////////////////////////////////////////////////
// GPC Struct Parameter
///////////////////////////////////////////////////////////////
/**
   paracnt <br>
   (+0000h/+0100h/+0140h/+0180h/+01C0h/+0200h/+0240h/+0280h/+02C0h/+0300h/
	+0340h/+0380h/+03C0h/+0400h/+0440h/+0480h/+04C0h/+0500h/+0540h) <br>
	64 bytes of GPC struct parameters has header part.
	The structure of header part is described in UimgpcParacnt.
*/
union _UimgpcParacnt
{
		/**< All bits */
	guint32	word;
	struct{
			/**< paraad<br>Refer to @ref EimParaad. */
		guint32	paraad		:12;
		/**< seqen */
		guint32	seqen		:1;
		guint32				:3;
		guint32	lpara		:1;
		guint32				:15;
	}bit;
};

// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_SEQ_CTRL
/** seqloop (+0004h) */
/** seqctl (+0010h) */
union _UimgpcSeqctl
{
		/**< All bits */
		guint32 word[4];
		struct {
			/**< cntend0 */
			guint32 cntend0 :20;
			guint32 seqconf0 :2;
			guint32 :2;
			guint32 cnfout0 :1;
			guint32 :3;
			guint32 stepnum :4;
			/**< cntend1 */
			guint32 cntend1 :20;
			guint32 seqconf1 :2;
			guint32 :2;
			guint32 cnfout1 :1;
			guint32 :7;
			/**< cntend2 */
			guint32 cntend2 :20;
			guint32 seqconf2 :2;
			guint32 :2;
			guint32 cnfout2 :1;
			guint32 :7;
			/**< cntend3 */
			guint32 cntend3 :20;
			guint32 seqconf3 :2;
			guint32 :2;
			guint32 cnfout3 :1;
			guint32 :7;
		} bit;
};

// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D0_1
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D2_3
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P1_D0_1
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P1_D2_3
/**
   precal (+0104h/+0144h/+0184h/+01C4h) <br>
   Beginning 4bytes of precal(+0100h/+0140h/+0180h/+01C0h) is same structure as UimgpcParacnt.
 */
union _UimgpcPrecal
{
		/**< All bits */
		guint32 word[5];
		struct {
			/**< PREOFSET0<br>PREOFSET1 */
			gint32 preofset :15;
			guint32 :17;
			/**< PRECLIPMAX0<br>PRECLIPMAX1 */
			gint32 preclipmax :15;
			guint32 :17;
			/**< PRECTHMAX0<br>PRECTHMAX1 */
			gint32 precthmax :15;
			guint32 :17;
			/**< PRECLIPMIN0<br>PRECLIPMIN1 */
			gint32 preclipmin :15;
			guint32 :17;
			/**< PRECTHMIN0<br>PRECTHMIN1 */
			gint32 precthmin :15;
			guint32 :5;
			guint32 preae :1;
			guint32 :11;
		} bit;
};

// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG0
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG1
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG2
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG3
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D1_CFG0
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D1_CFG1
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D1_CFG2
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D1_CFG3
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D2_CFG0
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D2_CFG1
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D2_CFG2
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D2_CFG3
/** gpc0para0 (+0204h/+0244h/+0284h/+02C4h/+0304h/+0344h/+0384h/+03C4h/+0404h/+0444h/+0484h/+04C4h) */
union _UimgpcGpc0para0
{
		/**< All bits */
		guint32 word;
		struct {
			/**< gpc0sel0<br>Refer to @ref EimGpcsel. */
			guint32 gpc0sel0 :5;
			guint32 gpc0sel1 :5;
			guint32 gpc0sel2 :5;
			guint32 :1;
			guint32 gpc0sel3 :5;
			guint32 :3;
			guint32 g0md0 :1;
			guint32 g0md1 :1;
			guint32 :2;
			guint32 g0md2 :3;
			guint32 :1;
		} bit;
};

/** gpc0para1 (+0208h/+0248h/+0288h/+02C8h/+0308h/+0348h/+0388h/+03C8h/+0408h/+0448h/+0488h/+04C8h) */
union _UimgpcGpc0para1
{
		/**< All bits */
		guint32 word[2];
		struct {
			/**< g0rnd0<br>Refer to @ref EimRnd. */
			guint32 g0rnd0 :1;
			guint32 :3;
			guint32 g0sft0 :4;
			guint32 g0rnd1 :1;
			guint32 :3;
			guint32 g0sft1 :4;
			guint32 g0rnd2 :1;
			guint32 :3;
			guint32 g0sft2 :4;
			guint32 g0rnd3 :1;
			guint32 :3;
			guint32 g0sft3 :4;
			guint32 g0rnd4 :1;
			guint32 :3;
			guint32 g0sft4 :4;
			guint32 g0rnd5 :1;
			guint32 :3;
			guint32 g0sft5 :4;
			guint32 g0rnd6 :1;
			guint32 :3;
			/**< g0sft6 */
			guint32 g0sft6 :4;
			guint32 :8;
		} bit;
};

/** gpc1para0 (+0210h/+0250h/+0290h/+02D0h/+0310h/+0350h/+0390h/+03D0h/+0410h/+0450h/+0490h/+04D0h) */
union _UimgpcGpc1para0
{
		/**< All bits */
		guint32 word;
		struct {
			/**< gpc1sel0<br>Refer to @ref EimGpcsel. */
			guint32 gpc1sel0 :5;
			guint32 :3;
			guint32 gpc1sel1 :5;
			guint32 :3;
			guint32 gpc1sel2 :5;
			guint32 :3;
			guint32 g1md0 :2;
			guint32 :2;
			guint32 g1md1 :3;
			guint32 :1;
		} bit;
};

/** gpc1para1 (+0218h/+0258h/+0298h/+02D8h/+0318h/+0358h/+0398h/+03D8h/+0418h/+0458h/+0498h/+04D8h) */
union _UimgpcGpc1para1
{
		/**< All bits */
		guint32 word[2];
		struct {
			/**< g1rnd0<br>Refer to @ref EimRnd. */
			guint32 g1rnd0 :1;
			guint32 :3;
			/**< g1sft0 */
			guint32 g1sft0 :4;
			guint32 g1rnd1 :1;
			guint32 :3;
			guint32 g1sft1 :4;
			guint32 g1rnd2 :1;
			guint32 :3;
			guint32 g1sft2 :4;
			guint32 g1rnd3 :1;
			guint32 :3;
			guint32 g1sft3 :4;
			guint32 g1rnd4 :1;
			guint32 :3;
			guint32 g1sft4 :4;
			guint32 :8;
			guint32 :8;
			guint32 :8;
		} bit;
};

/** serpass (+0220h/+0260h/+02A0h/+02E0h/+0320h/+0360h/+03A0h/+03E0h/+0420h/+0460h/+04A0h/+04E0h) */
union _UimgpcSerpass
{
		/**< All bits */
		guint32 word;
		struct {
			/**< sedly0 */
			guint32 sedly0 :1;
			guint32 :3;
			/**< sesel0<br>Refer to @ref EimSesel0. */
			guint32 sesel0 :1;
			guint32 :3;
			guint32 sedly1 :2;
			guint32 :2;
			guint32 sesel1 :2;
			guint32 :2;
			guint32 sedly2 :2;
			guint32 :2;
			guint32 sedly3 :2;
			guint32 :2;
			guint32 sedly4 :2;
			guint32 sedly5 :2;
			guint32 sedly6 :2;
			guint32 sedly7 :2;
		} bit;
};

/** compsel (+0224h/+0264h/+02A4h/+02E4h/+0324h/+0364h/+03A4h/+03E4h/+0424h/+0464h/+04A4h/+04E4h) */
union _UimgpcCompsel
{
		/**< All bits */
		guint32 word;
		struct {
			/**< compsel<br>Refer to @ref EimCompsel. */
			guint32 compsel :5;
			guint32 :3;
			guint32 cmprnd :1;
			guint32 :3;
			guint32 cmpsft :4;
			guint32 corpen :1;
			guint32 :3;
			guint32 cormen :1;
			guint32 :3;
			guint32 clppen :1;
			guint32 :3;
			guint32 clpmen :1;
			guint32 :3;
		} bit;
};

/** confcnt (+0228h/+0268h/+02A8h/+02E8h/+0328h/+0368h/+03A8h/+03E8h/+0428h/+0468h/+04A8h/+04E8h) */
union _UimgpcConfcnf
{
		/**< All bits */
		guint32 word[2];
		struct {
			/**< confwen0 */
			guint32 confwen0 :1;
			guint32 confwen1 :1;
			guint32 confwen2 :1;
			guint32 confwen3 :1;
			guint32 :12;
			/**< confregsel0<br>Refer to @ref EimConfregsel. */
			guint32 confregsel0 :4;
			guint32 confregsel1 :4;
			guint32 confregsel2 :4;
			guint32 confregsel3 :4;
			guint32 confregsel4 :4;
			guint32 confregsel5 :4;
			guint32 confregsel6 :4;
			guint32 confregsel7 :4;
			guint32 confregsel8 :4;
			guint32 confregsel9 :4;
			guint32 :8;
		} bit;
};

/** confreg (+0230h) */
// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_ALPHA
/** gpcalp (+0510h) */
union _UimgpcGpcalp
{
		/**< All bits */
		guint32 word;
		struct {
			/**< GPCALPFIX_0<br>GPCALPFIX_1<br>GPCALPFIX_2<br>GPCALPFIX_3 */
			gint32 gpcalpfix :9;
			guint32 :11;
			/**< GPCALPSEL0_0<br>GPCALPSEL0_1<br>GPCALPSEL0_2<br>GPCALPSEL0_3<br>Refer to @ref EimGpcalpsel. */
			guint32 gpcalpsel0 :2;
			guint32 gpcalpsel1 :2;
			/**< GPCALPMODE_0<br>GPCALPMODE_1<br>GPCALPMODE_2<br>GPCALPMODE_3<br>Refer to @ref EimGpcalpmode. */
			guint32 gpcalpmode :3;
			guint32 :5;
		} bit;
};

// ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_INTER_COMP_CALC
/** p1outmd (+0550h) */
union _UimgpcP1outmd
{
		/**< All bits */
		guint32 word;
		struct {
			/**< p1rndo0<br>Refer to @ref EimRnd. */
			guint32 p1rndo0 :1;
			/**< p1sfto0 */
			guint32 p1sfto0 :4;
			/**< p1selo0<br>Refer to @ref EimP1selo */
			guint32 p1selo0 :2;
			guint32 :1;
			guint32 p1rndo1 :1;
			guint32 p1sfto1 :4;
			guint32 p1selo1 :2;
			guint32 :1;
			guint32 p1rndo2 :1;
			guint32 p1sfto2 :4;
			guint32 p1selo2 :2;
			guint32 :1;
			guint32 p1rndo3 :1;
			guint32 p1sfto3 :4;
			guint32 p1selo3 :2;
			guint32 :1;
		} bit;
};

/** p0outmdD3 (+0554h) */
union _UimgpcP0outmdD3
{
		/**< All bits */
		guint32 word;
		/**< Bit field */
		struct {
			/**< p0rndoD3<br>Refer to @ref EimRnd. */
			guint32 p0rndoD3 :1;
			/**< p0sftoD3 */
			guint32 p0sftoD3 :4;
			/**< p0seloD3<br>Refer to @ref EimP0selo */
			guint32 p0seloD3 :2;
			guint32 :1;
			guint32 :24;
		} bit;
};

/** elecal (+0560h) */
union _UimgpcElecal
{
		/**< All bits */
		guint32 word[2];
		struct {
			/**< ELESEL0_0<br>ELESEL0_1<br>ELESEL0_2<br>ELESEL0_3<br>Refer to @ref EimElesel. */
			guint32 elesel0 :2;
			/**< ELERD0_0<br>ELERD0_1<br>ELERD0_2<br>ELERD0_3<br>Refer to @ref EimRnd. */
			guint32 elerd0 :1;
			/**< ELESHIFT0_0<br>ELESHIFT0_1<br>ELESHIFT0_2<br>ELESHIFT0_3<br>Refer to @ref EimEleshift. */
			guint32 eleshift0 :5;
			/**< ELESEL1_0<br>ELESEL1_1<br>ELESEL1_2<br>ELESEL1_3<br>Refer to @ref EimElesel. */
			guint32 elesel1 :2;
			/**< ELERD1_0<br>ELERD1_1<br>ELERD1_2<br>ELERD1_3<br>Refer to @ref EimRnd. */
			guint32 elerd1 :1;
			/**< ELESHIFT1_0<br>ELESHIFT1_1<br>ELESHIFT1_2<br>ELESHIFT1_3<br>Refer to @ref EimEleshift. */
			guint32 eleshift1 :5;
			/**< ELESEL2_0<br>ELESEL2_1<br>ELESEL2_2<br>ELESEL2_3<br>Refer to @ref EimElesel. */
			guint32 elesel2 :2;
			/**< ELERD2_0<br>ELERD2_1<br>ELERD2_2<br>ELERD2_3<br>Refer to @ref EimRnd. */
			guint32 elerd2 :1;
			/**< ELESHIFT2_0<br>ELESHIFT2_1<br>ELESHIFT2_2<br>ELESHIFT2_3<br>Refer to @ref EimEleshift. */
			guint32 eleshift2 :5;
			/**< ELESEL3_0<br>ELESEL3_1<br>ELESEL3_2<br>ELESEL3_3<br>Refer to @ref EimElesel. */
			guint32 elesel3 :2;
			/**< ELERD3_0<br>ELERD3_1<br>ELERD3_2<br>ELERD3_3<br>Refer to @ref EimRnd. */
			guint32 elerd3 :1;
			/**< ELESHIFT3_0<br>ELESHIFT3_1<br>ELESHIFT3_2<br>ELESHIFT3_3<br>Refer to @ref EimEleshift. */
			guint32 eleshift3 :5;
			/**< ELEMODE0_0<br>ELEMODE0_1<br>ELEMODE0_2<br>ELEMODE0_3<br>Refer to @ref EimElemode. */
			guint32 elemode0 :3;
			guint32 :1;
			/**< ELEMODE1_0<br>ELEMODE1_1<br>ELEMODE1_2<br>ELEMODE1_3<br>Refer to @ref EimElemode. */
			guint32 elemode1 :3;
			guint32 :1;
			/**< ELEMODE2_0<br>ELEMODE2_1<br>ELEMODE2_2<br>ELEMODE2_3<br>Refer to @ref EimElemode. */
			guint32 elemode2 :3;
			guint32 :1;
			/**< ELERDO_0<br>ELERDO_1<br>ELERDO_2<br>ELERDO_3<br>Refer to @ref EimRnd. */
			guint32 elerdo :1;
			/**< ELESHIFTO_0<br>ELESHIFTO_1<br>ELESHIFTO_2<br>ELESHIFTO_3 */
			guint32 eleshifto :4;
			guint32 :15;
		} bit;
};

/**
 GPC struct paramters which be associated with
 <ul>
	 <li>Sequence control
 </ul>
 */
struct _TimgpcSeqCtrl
{
		/**< paracnt (+0000h) */
		UimgpcParacnt paracnt;
		/**< seqloop (+0004h) */
		guint32 seqloop;
		/**< Unused variable */
		guchar dmy0008000f[0x0010 - 0x0008];
		/**< seqctl (+0010h) */
		UimgpcSeqctl seqctl;
		/**< Unused variable */
		guchar dmy0020003f[0x0040 - 0x0020];
};

/**
 GPC struct paramters which be associated with
 <ul>
	 <li>Pre-calculation (PORT0 D0, D1)
	 <li>Pre-calculation (PORT0 D2, D3)
	 <li>Pre-calculation (PORT1 D0, D1)
	 <li>Pre-calculation (PORT1 D2, D3)
 </ul>
 */
struct _TimgpcPrecal
{
		/**< precal (+0100h/+0140h/+180h/+1C0h) */
		UimgpcParacnt paracnt;
		/**< precal (+0104h/+0144h/+184h/+1C04) */
		UimgpcPrecal precal[2];
		/**< Unused variable */
		guchar dmy002c003f[0x0040 - 0x002C];
};

/**
 GPC struct paramters which be associated with
 <ul>
	 <li>Configuration[0] of General calculation for D0 compoment
	 <li>Configuration[1] of General calculation for D0 compoment
	 <li>Configuration[2] of General calculation for D0 compoment
	 <li>Configuration[3] of General calculation for D0 compoment
	 <li>Configuration[0] of General calculation for D1 compoment
	 <li>Configuration[1] of General calculation for D1 compoment
	 <li>Configuration[2] of General calculation for D1 compoment
	 <li>Configuration[3] of General calculation for D1 compoment
	 <li>Configuration[0] of General calculation for D2 compoment
	 <li>Configuration[1] of General calculation for D2 compoment
	 <li>Configuration[2] of General calculation for D2 compoment
	 <li>Configuration[3] of General calculation for D2 compoment
 </ul>
 */
struct _TimgpcCalc
{
		/**< paracnt   (+0200h/+0240h/+0280h/+02C0h/+0300h/+0340h/+0380h/+03C0h/+0400h/+0440h/+0480h/+04C0h) */
		UimgpcParacnt paracnt;
		/**< gpc0para0 (+0204h/+0244h/+0284h/+02C4h/+0304h/+0344h/+0384h/+03C4h/+0404h/+0444h/+0484h/+04C4h) */
		UimgpcGpc0para0 gpc0para0;
		/**< gpc0para1 (+0208h/+0248h/+0288h/+02C8h/+0308h/+0348h/+0388h/+03C8h/+0408h/+0448h/+0488h/+04C8h) */
		UimgpcGpc0para1 gpc0para1;
		/**< gpc1para0 (+0210h/+0250h/+0290h/+02D0h/+0310h/+0350h/+0390h/+03D0h/+0410h/+0450h/+0490h/+04D0h) */
		UimgpcGpc1para0 gpc1para0;
		/**< Unused variable */
		guchar dmy00140017[0x0018 - 0x0014];
		/**< gpc1para1 (+0218h/+0258h/+0298h/+02D8h/+0318h/+0358h/+0398h/+03D8h/+0418h/+0458h/+0498h/+04D8h) */
		UimgpcGpc1para1 gpc1para1;
		/**< serpass   (+0220h/+0260h/+02A0h/+02E0h/+0320h/+0360h/+03A0h/+03E0h/+0420h/+0460h/+04A0h/+04E0h) */
		UimgpcSerpass serpass;
		/**< compsel   (+0224h/+0264h/+02A4h/+02E4h/+0324h/+0364h/+03A4h/+03E4h/+0424h/+0464h/+04A4h/+04E4h) */
		UimgpcCompsel compsel;
		/**< confcnt   (+0228h/+0268h/+02A8h/+02E8h/+0328h/+0368h/+03A8h/+03E8h/+0428h/+0468h/+04A8h/+04E8h) */
		UimgpcConfcnf confcnt;
		/**< confreg   (+0230h/+0270h/+02B0h/+02F0h/+0330h/+0370h/+03B0h/+03F0h/+0430h/+0470h/+04B0h/+04F0h) */
		guint32 confreg[4];
};

/**
 GPC struct paramters which be associated with
 <ul>
	 <li>Configuration[0][1][2][3] of Alpha
 </ul>
 */
struct _TimgpcAlpha
{
		/**< paracnt (+0500h) */
		UimgpcParacnt paracnt;
		/**< Unused variable */
		guchar dmy0004000f[0x0010 - 0x0004];
		/**< gpcalp (+0510h) */
		UimgpcGpcalp gpcalp[4];
		/**< Unused variable */
		guchar dmy0020003f[0x0040 - 0x0020];
};

/**
 GPC struct paramters which be associated with
 <ul>
	 <li>Inter color calculation
 </ul>
 */
struct _TimgpcInterCompCalc
{
		/**< paracnt (+0540h) */
		UimgpcParacnt paracnt;
		/**< Unused variable */
		guchar dmy0004000f[0x0010 - 0x0004];
		/**< p1outmd (+0550h) */
		UimgpcP1outmd p1outmd;
		/**< p0outmdD3 (+0554h) */
		UimgpcP0outmdD3 p0outmdD3;
		/**< Unused variable */
		guchar dmy0018001f[0x0020 - 0x0018];
		/**< elecal (+0560h) */
		UimgpcElecal elecal[3];
		/**< Unused variable */
		guchar dmy0038003f[0x0040 - 0x0038];
};

struct _ImIipGpcParameter
{
	GObject parent;
};

struct _ImIipGpcParameterClass
{
	GObjectClass parentClass;
};


GType						im_iip_gpc_parameter_struct_get_type(void)	G_GNUC_CONST;
ImIipGpcParameter*					im_iip_gpc_parameter_struct_new(void);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_IIP_GPC_PARAMETER_H__ */
