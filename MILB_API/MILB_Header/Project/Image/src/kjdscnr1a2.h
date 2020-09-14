/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-14
*@author            :陈倩
*@brief             :kjdscnr1a2
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/


#ifndef __K_JDSCNR1A2_H__
#define __K_JDSCNR1A2_H__


#include <klib.h>


#define K_TYPE_JDSCNR1A2			(k_jdscnr1a2_get_type())
#define K_JDSCNR1A2(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdscnr1a2))
#define K_IS_JDSCNR1A2(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSCNR1A2))


typedef struct _KJdscnr1a2				KJdscnr1a2;
typedef struct _KJdscnr1a2Private	KJdscnr1a2Private;

struct  _KJdscnr1a2
{
	KObject parent;
};


/*	structure of lcysclbd	(2842_10F8h)	*/
typedef union _IoCnrCsprRegLcysclbd1
{
	kulong word;
	struct
	{
		kulong lcysclbd1 :8;
		kulong lcysclbd2 :8;
		kulong lcysclbd3 :8;
		kulong lcysclbd4 :8;
	} bit;
} IoCnrCsprRegLcysclbd1;

typedef union _IoCnrCsprRegLcysclbd2
{
	kulong word;
	struct
	{
		kulong lcysclbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegLcysclbd2;

typedef struct _IoCnrCsprRegLcysclbd
{
	IoCnrCsprRegLcysclbd1 lcysclbd1;
	IoCnrCsprRegLcysclbd2 lcysclbd2;
} IoCnrCsprRegLcysclbd;

/*	structure of lccscl (2842_1100h)	*/
typedef union _IoCnrCsprRegLccscl
{
	kulong word;
	struct
	{
		kulong lccscl :1;
		kulong :31;
	} bit;
} IoCnrCsprRegLccscl;

/*	structure of lccsclof	(2842_1108h)	*/
typedef union _IoCnrCsprRegLccsclof1
{
	kulong word;
	struct
	{
		kulong lccsclof0 :8;
		kulong lccsclof1 :8;
		kulong lccsclof2 :8;
		kulong lccsclof3 :8;
	} bit;
} IoCnrCsprRegLccsclof1;

typedef union _IoCnrCsprRegLccsclof2
{
	kulong word;
	struct
	{
		kulong lccsclof4 :8;
		kulong lccsclof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegLccsclof2;

typedef struct _IoCnrCsprRegLccsclof
{
	IoCnrCsprRegLccsclof1 lccsclof1;
	IoCnrCsprRegLccsclof2 lccsclof2;
} IoCnrCsprRegLccsclof;

/*	structure of lccsclga	(2842_1110h)	*/
typedef union _IoCnrCsprRegLccsclga1
{
	kulong word;
	struct
	{
		klong lccsclga0 :8;
		klong lccsclga1 :8;
		klong lccsclga2 :8;
		klong lccsclga3 :8;
	} bit;
} IoCnrCsprRegLccsclga1;

typedef union _IoCnrCsprRegLccsclga2
{
	kulong word;
	struct
	{
		klong lccsclga4 :8;
		klong lccsclga5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegLccsclga2;

typedef struct _IoCnrCsprRegLccsclga
{
	IoCnrCsprRegLccsclga1 lccsclga1;
	IoCnrCsprRegLccsclga2 lccsclga2;
} IoCnrCsprRegLccsclga;

/*	structure of lccsclbd	(2842_1118h)	*/
typedef union _IoCnrCsprRegLccsclbd1
{
	kulong word;
	struct
	{
		kulong lccsclbd1 :8;
		kulong lccsclbd2 :8;
		kulong lccsclbd3 :8;
		kulong lccsclbd4 :8;
	} bit;
} IoCnrCsprRegLccsclbd1;

typedef union _IoCnrCsprRegLccsclbd2
{
	kulong word;
	struct
	{
		kulong lccsclbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegLccsclbd2;

typedef struct _IoCnrCsprRegLccsclbd
{
	IoCnrCsprRegLccsclbd1 lccsclbd1;
	IoCnrCsprRegLccsclbd2 lccsclbd2;
} IoCnrCsprRegLccsclbd;

/*	structure of lcsscl (2842_1120h)	*/
typedef union _IoCnrCsprRegLcsscl
{
	kulong word;
	struct
	{
		kulong lcsscl :1;
		kulong :31;
	} bit;
} IoCnrCsprRegLcsscl;

/*	structure of lcssclof	(2842_1128h)	*/
typedef union _IoCnrCsprRegLcssclof1
{
	kulong word;
	struct
	{
		kulong lcssclof0 :8;
		kulong lcssclof1 :8;
		kulong lcssclof2 :8;
		kulong lcssclof3 :8;
	} bit;
} IoCnrCsprRegLcssclof1;

typedef union _IoCnrCsprRegLcssclof2
{
	kulong word;
	struct
	{
		kulong lcssclof4 :8;
		kulong lcssclof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegLcssclof2;

typedef struct _IoCnrCsprRegLcssclof
{
	IoCnrCsprRegLcssclof1 lcssclof1;
	IoCnrCsprRegLcssclof2 lcssclof2;
} IoCnrCsprRegLcssclof;

/*	structure of lcssclga	(2842_1130h)	*/
typedef union _IoCnrCsprRegLcssclga1
{
	kulong word;
	struct
	{
		klong lcssclga0 :8;
		klong lcssclga1 :8;
		klong lcssclga2 :8;
		klong lcssclga3 :8;
	} bit;
} IoCnrCsprRegLcssclga1;

typedef union _IoCnrCsprRegLcssclga2
{
	kulong word;
	struct
	{
		klong lcssclga4 :8;
		klong lcssclga5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegLcssclga2;

typedef struct _IoCnrCsprRegLcssclga
{
	IoCnrCsprRegLcssclga1 lcssclga1;
	IoCnrCsprRegLcssclga2 lcssclga2;
} IoCnrCsprRegLcssclga;

/*	structure of lcssclbd	(2842_1138h)	*/
typedef union _IoCnrCsprRegLcssclbd1
{
	kulong word;
	struct
	{
		kulong lcssclbd1 :8;
		kulong lcssclbd2 :8;
		kulong lcssclbd3 :8;
		kulong lcssclbd4 :8;
	} bit;
} IoCnrCsprRegLcssclbd1;

typedef union _IoCnrCsprRegLcssclbd2
{
	kulong word;
	struct
	{
		kulong lcssclbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegLcssclbd2;

typedef struct _IoCnrCsprRegLcssclbd
{
	IoCnrCsprRegLcssclbd1 lcssclbd1;
	IoCnrCsprRegLcssclbd2 lcssclbd2;
} IoCnrCsprRegLcssclbd;

/*	structure of blend	(2842_1160h)	*/
typedef union _IoCnrCsprRegBlend
{
	kulong word;
	struct
	{
		kulong blendmd :2;
		kulong :6;
		kulong cspralpbd :5;
		kulong :3;
		kulong csrgen :1;
		kulong :3;
		kulong csrgmd :3;
		kulong :9;
	} bit;
} IoCnrCsprRegBlend;

/*	structure of cesclof	(2842_1168h)	*/
typedef union _IoCnrCsprRegCesclof1
{
	kulong word;
	struct
	{
		kulong cesclof0 :6;
		kulong :2;
		kulong cesclof1 :6;
		kulong :2;
		kulong cesclof2 :6;
		kulong :2;
		kulong cesclof3 :6;
		kulong :2;
	} bit;
} IoCnrCsprRegCesclof1;

typedef union _IoCnrCsprRegCesclof2
{
	kulong word;
	struct
	{
		kulong cesclof4 :6;
		kulong :2;
		kulong cesclof5 :6;
		kulong :2;
		kulong :16;
	} bit;
} IoCnrCsprRegCesclof2;

typedef struct _IoCnrCsprRegCesclof
{
	IoCnrCsprRegCesclof1 cesclof1;
	IoCnrCsprRegCesclof2 cesclof2;
} IoCnrCsprRegCesclof;

/*	structure of cesclga	(2842_1170h)	*/
typedef union _IoCnrCsprRegCesclga1
{
	kulong word;
	struct
	{
		klong cesclga0 :8;
		klong cesclga1 :8;
		klong cesclga2 :8;
		klong cesclga3 :8;
	} bit;
} IoCnrCsprRegCesclga1;

typedef union _IoCnrCsprRegCesclga2
{
	kulong word;
	struct
	{
		klong cesclga4 :8;
		klong cesclga5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegCesclga2;

typedef struct _IoCnrCsprRegCesclga
{
	IoCnrCsprRegCesclga1 cesclga1;
	IoCnrCsprRegCesclga2 cesclga2;
} IoCnrCsprRegCesclga;

/*	structure of cesclbd	(2842_1178h)	*/
typedef union _IoCnrCsprRegCesclbd1
{
	kulong word;
	struct
	{
		kulong cesclbd1 :8;
		kulong cesclbd2 :8;
		kulong cesclbd3 :8;
		kulong cesclbd4 :8;
	} bit;
} IoCnrCsprRegCesclbd1;

typedef union _IoCnrCsprRegCesclbd2
{
	kulong word;
	struct
	{
		kulong cesclbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegCesclbd2;

typedef struct _IoCnrCsprRegCesclbd
{
	IoCnrCsprRegCesclbd1 cesclbd1;
	IoCnrCsprRegCesclbd2 cesclbd2;
} IoCnrCsprRegCesclbd;

/*	structure of cphpt	(2842_1190h)	*/
typedef union _IoCnrCsprRegCphpt
{
	kulong word;
	struct
	{
		klong cdcb :8;
		klong cdcr :8;
		kulong :16;
	} bit;
} IoCnrCsprRegCphpt;

/*	structure of cphptk	(2842_1194h)	*/
typedef union _IoCnrCsprRegCphptk
{
	kulong word;
	struct
	{
		kulong kcb :10;
		kulong :6;
		kulong kcr :10;
		kulong :6;
	} bit;
} IoCnrCsprRegCphptk;

/*	structure of cdsclof	(2842_11A0h)	*/
typedef union _IoCnrCsprRegCdsclof1
{
	kulong word;
	struct
	{
		kulong cdsclof0 :9;
		kulong :7;
		kulong cdsclof1 :9;
		kulong :7;
	} bit;
} IoCnrCsprRegCdsclof1;

typedef union _IoCnrCsprRegCdsclof2
{
	kulong word;
	struct
	{
		kulong cdsclof2 :9;
		kulong :7;
		kulong cdsclof3 :9;
		kulong :7;
	} bit;
} IoCnrCsprRegCdsclof2;

typedef union _IoCnrCsprRegCdsclof3
{
	kulong word;
	struct
	{
		kulong CDSCLOF_4 :9;
		kulong :7;
		kulong CDSCLOF_5 :9;
		kulong :7;
	} bit;
} IoCnrCsprRegCdsclof3;

typedef struct _IoCnrCsprRegCdsclof
{
	IoCnrCsprRegCdsclof1 cdsclof1;
	IoCnrCsprRegCdsclof2 cdsclof2;
	IoCnrCsprRegCdsclof3 cdsclof3;
} IoCnrCsprRegCdsclof;

/*	structure of cdsclga	(2842_11B0h)	*/
typedef union _IoCnrCsprRegCdsclga1
{
	kulong word;
	struct
	{
		klong cdsclga0 :11;
		kulong :5;
		klong cdsclga1 :11;
		kulong :5;
	} bit;
} IoCnrCsprRegCdsclga1;

typedef union _IoCnrCsprRegCdsclga2
{
	kulong word;
	struct
	{
		klong cdsclga2 :11;
		kulong :5;
		klong cdsclga3 :11;
		kulong :5;
	} bit;
} IoCnrCsprRegCdsclga2;

typedef union _IoCnrCsprRegCdsclga3
{
	kulong word;
	struct
	{
		klong cdsclga4 :11;
		kulong :5;
		klong cdsclga5 :11;
		kulong :5;
	} bit;
} IoCnrCsprRegCdsclga3;

typedef struct _IoCnrCsprRegCdsclga
{
	IoCnrCsprRegCdsclga1 cdsclga1;
	IoCnrCsprRegCdsclga2 cdsclga2;
	IoCnrCsprRegCdsclga3 cdsclga3;
} IoCnrCsprRegCdsclga;

/*	structure of cdsclbd	(2842_11C0h)	*/
typedef union _IoCnrCsprRegCdsclbd1
{
	kulong word;
	struct
	{
		kulong cdsclbd1 :11;
		kulong :5;
		kulong cdsclbd2 :11;
		kulong :5;
	} bit;
} IoCnrCsprRegCdsclbd1;

typedef union _IoCnrCsprRegCdsclbd2
{
	kulong word;
	struct
	{
		kulong cdsclbd3 :11;
		kulong :5;
		kulong cdsclbd4 :11;
		kulong :5;
	} bit;
} IoCnrCsprRegCdsclbd2;

typedef union _IoCnrCsprRegCdsclbd3
{
	kulong word;
	struct
	{
		kulong cdsclbd5 :11;
		kulong :21;
	} bit;
} IoCnrCsprRegCdsclbd3;

typedef struct _IoCnrCsprRegCdsclbd
{
	IoCnrCsprRegCdsclbd1 cdsclbd1;
	IoCnrCsprRegCdsclbd2 cdsclbd2;
	IoCnrCsprRegCdsclbd3 cdsclbd3;
} IoCnrCsprRegCdsclbd;

/*	structure of whtmd	(2842_11D0h)	*/
typedef union _IoCnrCsprRegWhtmd
{
	kulong word;
	struct
	{
		kulong whten :1;
		kulong :7;
		kulong whtval :5;
		kulong :3;
		kulong whtbase :2;
		kulong :14;
	} bit;
} IoCnrCsprRegWhtmd;

/*	structure of sprs	(2842_1200h)	*/
typedef union _IoCnrCsprRegSprs
{
	kulong word;
	struct
	{
		kulong sprs :1;
		kulong :31;
	} bit;
} IoCnrCsprRegSprs;

/*	structure of sprscbof	(2842_1208h)	*/
typedef union _IoCnrCsprRegSprscbof1
{
	kulong word;
	struct
	{
		klong sprscbof0 :8;
		klong sprscbof1 :8;
		klong sprscbof2 :8;
		klong sprscbof3 :8;
	} bit;
} IoCnrCsprRegSprscbof1;

typedef union _IoCnrCsprRegSprscbof2
{
	kulong word;
	struct
	{
		klong sprscbof4 :8;
		klong sprscbof5 :8;
		kulong :16;
	} bit;
} IoCnrCsprRegSprscbof2;

typedef struct _IoCnrCsprRegSprscbof
{
	IoCnrCsprRegSprscbof1 sprscbof1;
	IoCnrCsprRegSprscbof2 sprscbof2;
} IoCnrCsprRegSprscbof;

/*	structure of sprscbga	(2842_1210h)	*/
typedef union _IoCnrCsprRegSprscbga1
{
	kulong word;
	struct
	{
		klong sprscbga0 :12;
		kulong :4;
		klong sprscbga1 :12;
		kulong :4;
	} bit;
} IoCnrCsprRegSprscbga1;

typedef union _IoCnrCsprRegSprscbga2
{
	kulong word;
	struct
	{
		klong sprscbga2 :12;
		kulong :4;
		klong sprscbga3 :12;
		kulong :4;
	} bit;
} IoCnrCsprRegSprscbga2;

typedef union _IoCnrCsprRegSprscbga3
{
	kulong word;
	struct
	{
		klong sprscbga4 :12;
		kulong :4;
		klong sprscbga5 :12;
		kulong :4;
	} bit;
} IoCnrCsprRegSprscbga3;

typedef struct _IoCnrCsprRegSprscbga
{
	IoCnrCsprRegSprscbga1 sprscbga1;
	IoCnrCsprRegSprscbga2 sprscbga2;
	IoCnrCsprRegSprscbga3 sprscbga3;
} IoCnrCsprRegSprscbga;

/*	structure of sprscbbd	(2842_1220h)	*/
typedef union _IoCnrCsprRegSprscbbd1
{
	kulong word;
	struct
	{
		klong sprscbbd1 :8;
		klong sprscbbd2 :8;
		klong sprscbbd3 :8;
		klong sprscbbd4 :8;
	} bit;
} IoCnrCsprRegSprscbbd1;

typedef union _IoCnrCsprRegSprscbbd2
{
	kulong word;
	struct
	{
		klong sprscbbd5 :8;
		kulong :24;
	} bit;
} IoCnrCsprRegSprscbbd2;

typedef struct _IoCnrCsprRegSprscbbd
{
	IoCnrCsprRegSprscbbd1 sprscbbd1;
	IoCnrCsprRegSprscbbd2 sprscbbd2;
} IoCnrCsprRegSprscbbd;

/*	structure of sprscrof	(2842_1228h)	*/
typedef union _IoCnrCsprRegSprscrof1
{
	kulong word;
	struct
	{
		klong sprscrof0 :8;
		klong sprscrof1 :8;
		klong sprscrof2 :8;
		klong sprscrof3 :8;
	} bit;
} IoCnrCsprRegSprscrof1;


KConstType	k_jdscnr1a2_get_type(void);
KJdscnr1a2*	k_jdscnr1a2_new(void);


#endif/*__K_JDSCNR1A2_H__*/

