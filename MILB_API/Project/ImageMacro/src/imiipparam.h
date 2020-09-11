/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-08
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#ifndef __IM_IIP_PARAM_H__
#define __IM_IIP_PARAM_H__


#include <klib.h>
#include "imiipparamenum.h"
#include "imiipafnregister.h"
#include "imiipfrectregister.h"
#include "imiipmanyregister.h"
#include "imiipmultiregister.h"
#include "imiipfltregister.h"
#include "imiipslregister.h"
#include "imiipunitparameter.h"
#include "imiipgpcparameter.h"
#include "ddimtypedef.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_IIP_PARAM			(im_iip_param_get_type())
#define IM_IIP_PARAM	(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipParam))
#define IM_IS_IIP_PARAM	(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_PARAM	))

/*----------------------------------------------------------------------*/
/* Definition																		*/
/*----------------------------------------------------------------------*/
/**< "1.0" value of UimAfnStaxy and UimAfnDOutIn */
#define ImIipParam_D_IM_IIP_PARAM_AFN_VAL_1_0					(0x10000L)
/**< "1.0" value of UimFrectXy */
#define ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0				(0x100L)
/**< Convert float type pixel position to UimAfnStaxy and UimAfnDOutIn register value. */
#define ImIipParam_M_IM_IIP_AFNTBL_CALC_POS(pos)			((kulong)((pos) * ImIipParam_D_IM_IIP_PARAM_AFN_VAL_1_0))
/**< Convert float type pixel position to UimFrectXy register value. */
#define ImIipParam_M_IM_IIP_FRECTTBL_CALC_POS(pos)			((kulong)((pos) * ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0))


/*----------------------------------------------------------------------	*/
/* Structure		&&	Union												*/
/*----------------------------------------------------------------------	*/
typedef union _UimAfnStaxy		UimAfnStaxy;
typedef union _UimAfnDOutIn	UimAfnDOutIn;
typedef union _UimAfnSz				UimAfnSz;

typedef struct _TimAfnOpcol0		TimAfnOpcol0;
typedef struct _TimAfnOpcol1		TimAfnOpcol1;

typedef union _UimFrectXy			UimFrectXy;
typedef union _UimFrectSz			UimFrectSz;

typedef struct _TimFrectOpcol0	TimFrectOpcol0;
typedef struct _TimFrectOpcol1	TimFrectOpcol1;
typedef struct _ImIipParam 						ImIipParam;
typedef struct _ImIipParamPrivate 			ImIipParamPrivate;



///////////////////////////////////////////////////////////////
// AFN Struct Parameter
///////////////////////////////////////////////////////////////

/**
   AFN Struct Parameter stax/stay
   <br>
   [+0000~0007]
   <br>
   [+0020~0027]
   <br>
   [+0040~0047]
   <br>
   [+0060~0067]
   <br>
 */
union _UimAfnStaxy
{
		/**< All bits */
		kuint32 word[2];
		/**< Bit field */
		struct {
			/**< STAX0 [calmethod.opcol=0]<br>STAX0/STAX1/STAX2/STAX3 [calmethod.opcol=1] */
			kint32 stax :31;
			kuint32 :1;
			/**< STAY0 [calmethod.opcol=0]<br>STAY0/STAY1/STAY2/STAY3 [calmethod.opcol=1] */
			kint32 stay :31;
			kuint32 :1;
		} bit;
};

/**
   AFN Struct Parameter dxx/dxy/dyx/dyy
   <br>
   [+0008~0017]
   <br>
   [+0028~0037]
   <br>
   [+0048~0057]
   <br>
   [+0068~0077]
   <br>
 */
union _UimAfnDOutIn
{
		/**< All bits */
		kuint32 word[4];
		/**< Bit field */
		struct {
			/**< DXX0 [calmethod.opcol=0]<br>DXX0/DXX1/DXX2/DXX3 [calmethod.opcol=1] */
			kint32 dxx :24;
			kuint32 :8;
			/**< DXY0 [calmethod.opcol=0]<br>DXY0/DXY1/DXY2/DXY3 [calmethod.opcol=1] */
			kint32 dxy :24;
			kuint32 :8;
			/**< DYX0 [calmethod.opcol=0]<br>DYX0/DYX1/DYX2/DYX3 [calmethod.opcol=1] */
			kint32 dyx :24;
			kuint32 :8;
			/**< DYY0 [calmethod.opcol=0]<br>DYY0/DYY1/DYY2/DYY3 [calmethod.opcol=1] */
			kint32 dyy :24;
			kuint32 :8;
		} bit;
};

/**
   AFN Struct Parameter afndvsz/afndhsz
   <br>
   [+0018~001B]
 */
union _UimAfnSz
{
		/**< All bits */
		kuint32 word;
		/**< Bit field */
		struct {
			/**< afndhsz */
			kuint32 afndhsz :14;
			kuint32 :2;
			/**< afndvsz */
			kuint32 afndvsz :14;
			kuint32 :2;
		} bit;
};

/** AFN Struct Paramter [calmethod.opcol=0] */
struct _TimAfnOpcol0
{
		/**< [+0000~0007] */
		UimAfnStaxy staxy0;
		/**< [+0008~0017] */
		UimAfnDOutIn dOutIn0;
		/**< [+0018~001B] */
		UimAfnSz sz;
		/**< Unused variable */
		kuchar dmy001c001f[0x0020 - 0x001C];
} ;

/** AFN Struct Paramter [calmethod.opcol=1] */
struct _TimAfnOpcol1
{
		/**< [+0000~0007] */
		UimAfnStaxy staxy0;
		/**< [+0008~0017] */
		UimAfnDOutIn dOutIn0;
		/**< [+0018~001B] */
		UimAfnSz sz;
		/**< Unused variable */
		kuchar dmy001c001f[0x0020 - 0x001C];
		/**< [+0020~0027] */
		UimAfnStaxy staxy1;
		/**< [+0028~0037] */
		UimAfnDOutIn dOutIn1;
		/**< Unused variable */
		kuchar dmy0038003f[0x0040 - 0x0038];
		/**< [+0040~0047] */
		UimAfnStaxy staxy2;
		/**< [+0048~0057] */
		UimAfnDOutIn dOutIn2;
		/**< Unused variable */
		kuchar dmy0058005f[0x0060 - 0x0058];
		/**< [+0060~0067] */
		UimAfnStaxy staxy3;
		/**< [+0068~0077] */
		UimAfnDOutIn dOutIn3;
} ;

///////////////////////////////////////////////////////////////
// FRECT Struct Parameter
///////////////////////////////////////////////////////////////

/**
   FRECT Struct Parameter ax/ay/bx/by/cx/cy/dx/dy
   <br>
	[+0000~001F]
   <br>
	[+0030~004F]
   <br>
	[+0050~006F]
   <br>
	[+0070~008F]
   <br>
 */
union _UimFrectXy
{
		/**< Bit field */
		struct {
			/**< AX0 [calmethod.opcol=0]<br>AX0/AX1/AX2/AX3 [calmethod.opcol=1] */
			kint32 ax :23;
			kuint32 :9;
			/**< AY0 [calmethod.opcol=0]<br>AY0/AY1/AY2/AY3 [calmethod.opcol=1] */
			kint32 ay :23;
			kuint32 :9;
			/**< BX0 [calmethod.opcol=0]<br>BX0/BX1/BX2/BX3 [calmethod.opcol=1] */
			kint32 bx :23;
			kuint32 :9;
			/**< BY0 [calmethod.opcol=0]<br>BY0/BY1/BY2/BY3 [calmethod.opcol=1] */
			kint32 by :23;
			kuint32 :9;
			/**< CX0 [calmethod.opcol=0]<br>CX0/CX1/CX2/CX3 [calmethod.opcol=1] */
			kint32 cx :23;
			kuint32 :9;
			/**< CY0 [calmethod.opcol=0]<br>CY0/CY1/CY2/CY3 [calmethod.opcol=1] */
			kint32 cy :23;
			kuint32 :9;
			/**< DX0 [calmethod.opcol=0]<br>DX0/DX1/DX2/DX3 [calmethod.opcol=1] */
			kint32 dx :23;
			kuint32 :9;
			/**< DY0 [calmethod.opcol=0]<br>DY0/DY1/DY2/DY3 [calmethod.opcol=1] */
			kint32 dy :23;
			kuint32 :9;
		} bit;
		/**< All bits */
		kuint32 word[8];
} ;

/**
   FRECT Struct Parameter szpowh/szpowv
   <br>
   [+0020~0023]
   */
union _UimFrectSz
{
		/**< Bit field */
		struct {
			/**< szpowh<br>Refer to @ref EimSzpowh */
			kuint32 szpowh :3;
			kuint32 :5;
			/**< szpowv<br>Refer to @ref EimSzpowv */
			kuint32 szpowv :3;
			kuint32 :5;
			kuint32 :16;
		} bit;
		/**< All bits */
		kuint32 word;
};

/** FRECT Struct Paramter [calmethod.opcol=0] */
struct _TimFrectOpcol0
{
		/**< [+0000~001F] */
		UimFrectXy xy0;
		/**< [+0020~0023] */
		UimFrectSz sz;
		/**< Unused variable */
		kuchar dmy00240027[0x0028 - 0x0024];
} ;

/** FRECT Struct Paramter [calmethod.opcol=1] */
struct _TimFrectOpcol1
{
		/**< [+0000~001F] */
		UimFrectXy xy0;
		/**< [+0020~0023] */
		UimFrectSz sz;
		/**< Unused variable */
		kuchar dmy0024002f[0x0030 - 0x0024];
		/**< [+0030~004F] */
		UimFrectXy xy1;
		/**< [+0050~006F] */
		UimFrectXy xy2;
		/**< [+0070~008F] */
		UimFrectXy xy3;
} ;

struct _ImIipParam
{
	KObject parent;
};


KConstType 		    		im_iip_param_get_type(void);
ImIipParam*		       		im_iip_param_new(void);


#ifdef __cplusplus
}
#endif


#endif /* __IM_IIP_PARAM_H__ */
