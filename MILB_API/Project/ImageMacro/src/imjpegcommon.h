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


#ifndef __IM_JPEG_COMMON_H__
#define __IM_JPEG_COMMON_H__


#include <stdio.h>
#include <glib-object.h>
#include "driver_common.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_JPEG_COMMON							(im_jpeg_common_struct_get_type ())
#define IM_JPEG_COMMON(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_JPEG_COMMON, ImJpegCommon))
#define IM_JPEG_COMMON_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_JPEG_COMMON, ImJpegCommonClass))
#define IM_IS_JPEG_COMMON(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_JPEG_COMMON))
#define IM_IS_JPEG_COMMON_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_JPEG_COMMON))
#define IM_JPEG_COMMON_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_JPEG_COMMON, ImJpegCommonClass))
/*----------------------------------------------------------------------	*/
/* im_jpeg.h Definition													*/
/*----------------------------------------------------------------------	*/
/* Return value of processing result*/
#define ImJpegCommon_D_IM_JPEG_OK								(D_DDIM_OK)
#define ImJpegCommon_D_IM_JPEG_PARAM_ERROR			(D_IM_JPEG | D_DDIM_INPUT_PARAM_ERROR)
#define ImJpegCommon_D_IM_JPEG_SEM_NG						(D_IM_JPEG | D_DDIM_SEM_NG)
#define ImJpegCommon_D_IM_JPEG_SEM_TIMEOUT			(D_IM_JPEG | D_DDIM_SEM_TIMEOUT)
#define ImJpegCommon_D_IM_JPEG_TIMEOUT					(D_IM_JPEG | D_DDIM_TIMEOUT)
#define ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR		(D_IM_JPEG | D_DDIM_SYSTEM_ERROR)
#define ImJpegCommon_D_IM_JPEG_RUNNING_NG			(D_IM_JPEG | D_DDIM_MACRO_BUSY_NG)
#define ImJpegCommon_D_IM_JPEG_ENCODE_ERR				(D_IM_JPEG | 0x00002001)
#define ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE			(D_IM_JPEG | 0x00002002)
#define ImJpegCommon_D_IM_JPEG_DECODE_ERR				(D_IM_JPEG | 0x00004001)
#define ImJpegCommon_D_IM_JPEG_DECODE_PAUSE			(D_IM_JPEG | 0x00004002)
#define ImJpegCommon_D_IM_JPEG_AXI_ERR						(D_IM_JPEG | 0x00008001)

/* Process result*/
/**< jpeg core end */
#define ImJpegCommon_D_IM_JPEG_NML_END					(1<<0)
/**< Pause end */
#define ImJpegCommon_D_IM_JPEG_PAUSE							(1<<1)
/**< The correction process end */
#define ImJpegCommon_D_IM_JPEG_CORRECT_END			(1<<2)
#define ImJpegCommon_D_IM_JPEG_CORSIZINFO				(1<<3)
#define ImJpegCommon_D_IM_JPEG_CORDRIINFO				(1<<4)
/**< Unsupported format erorr */
#define ImJpegCommon_D_IM_JPEG_JCLRFMER					(1<<5)
/**< AXI error(JBUF)  */
#define ImJpegCommon_D_IM_JPEG_JJBINT							(1<<6)
/**< AXI error(PBUF)  */
#define ImJpegCommon_D_IM_JPEG_JPBINT							(1<<7)
/**< AXI error(JBUF)  */
#define ImJpegCommon_D_IM_JPEG_PLINEINT					(1<<8)
/**< AXI error(PBUF)  */
#define ImJpegCommon_D_IM_JPEG_PSECTINT					(1<<9)
/**< Encode data error */
#define ImJpegCommon_D_IM_JPEG_ERR								(1<<10)
/**< The total number of data anomalies */
#define ImJpegCommon_D_IM_JPEG_SIZERR							(1<<11)
/**< RST marker interval abnormalities */
#define ImJpegCommon_D_IM_JPEG_RSTERR						(1<<12)
/**< Target sampling type not matching */
#define ImJpegCommon_D_IM_JPEG_SMPL_TYPE_NG			(1<<13)
/**< Format can not cutout */
#define ImJpegCommon_D_IM_JPEG_CUTOUT_ERR				(1<<14)
/**< Size read enable */
#define ImJpegCommon_D_IM_JPEG_REGRDINT					(1<<15)
/**< Unknown marker detection */
#define ImJpegCommon_D_IM_JPEG_UMKSINFO					(1<<16)
/**< Com marker detection */
#define ImJpegCommon_D_IM_JPEG_COMMKINFO				(1<<17)
/**< App marker detection */
#define ImJpegCommon_D_IM_JPEG_APPMKINFO				(1<<18)
/**< JIF interrupt */
#define ImJpegCommon_D_IM_JPEG_JIF									(1<<19)
/**< JCF interrupt */
#define ImJpegCommon_D_IM_JPEG_JCF								(1<<20)
/**< Update quantization table */
#define ImJpegCommon_D_IM_JPEG_QTWINT						(1<<21)

/** Process normal end result pattern*/
#define ImJpegCommon_D_IM_JPEG_PROC_END	(ImJpegCommon_D_IM_JPEG_NML_END | ImJpegCommon_D_IM_JPEG_JIF | ImJpegCommon_D_IM_JPEG_JCF)

/* Interrupt flag*/
/**< Interrupt flag of process end */
#define ImJpegCommon_D_IM_JPEG_FLG_WAIT_END			(0x00001000)

/* Function Enable*/
#define	ImJpegCommon_D_IM_JPEG_ENABLE_OFF				(0)
#define	ImJpegCommon_D_IM_JPEG_ENABLE_ON				(1)

/* Jpeg down sampling type*/
/**< Not used the down sampling. */
#define	ImJpegCommon_D_IM_JPEG_DOWNSP_NONE			(0)
#define	ImJpegCommon_D_IM_JPEG_DOWNSP_1_2					(1)
#define	ImJpegCommon_D_IM_JPEG_DOWNSP_1_4					(2)
#define	ImJpegCommon_D_IM_JPEG_DOWNSP_1_8					(3)

/* AXI Error state*/
/**< AXI success */
#define	ImJpegCommon_D_IM_JPEG_AXI_OKAY						(0)
/**< AXI slave error  */
#define	ImJpegCommon_D_IM_JPEG_AXI_SLVERR						(2)
/**< AXI decode error */
#define	ImJpegCommon_D_IM_JPEG_AXI_DECERR					(3)

/* AXI chache type */
/**< Cache Support: Non Cacheable & Non Bufferable */
#define ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF							(0)
/**< Cache Support: Bufferable */
#define ImJpegCommon_D_IM_JPEG_ON_BUF														(1)
/**< Cache Support: Cacheable & No Allocate */
#define ImJpegCommon_D_IM_JPEG_ON_CACHE_NO_ALLOCATE						(2)
/**< Cache Support: Cacheable & Bufferable & No Allocate */
#define ImJpegCommon_D_IM_JPEG_ON_CACHE_ON_BUF_NO_ALLOCATE	(3)
/**< Cache Support: Cacheable & Write Through(Allocate Read only) */
#define ImJpegCommon_D_IM_JPEG_ON_CACHE_R_WRITE_THROUGH			(6)
/**< Cache Support: Cacheable & Write Back(Allocate Read only) */
#define ImJpegCommon_D_IM_JPEG_ON_CACHE_R_WRITE_BACK						(7)
/**< Cache Support: Cacheable & Write Through(Allocate Write only) */
#define ImJpegCommon_D_IM_JPEG_ON_CACHE_W_WRITE_THROUGH			(10)
/**< Cache Support: Cacheable & Write Back(Allocate Write only) */
#define ImJpegCommon_D_IM_JPEG_ON_CACHE_W_WRITE_BACK					(11)
/**< Cache Support: Cacheable & Write Through(Allocate Read & Write) */
#define ImJpegCommon_D_IM_JPEG_ON_CACHE_RW_WRITE_THROUGH			(14)
/**< Cache Support: Cacheable & Write Back(Allocate Read & Write) */
#define ImJpegCommon_D_IM_JPEG_ON_CACHE_RW_WRITE_BACK					(15)

/* AXI chache protect type*/
/**< Cache Protect: Data       /Secure    /Normal     Access */
#define ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS				(0)
#define ImJpegCommon_D_IM_JPEG_D_SEC_PRIVILEGED_ACCESS		(1)
#define ImJpegCommon_D_IM_JPEG_D_NSEC_NORMAL_ACCESS			(2)
#define ImJpegCommon_D_IM_JPEG_D_NSEC_PRIVILEGED_ACCESS		(3)
#define ImJpegCommon_D_IM_JPEG_I_SEC_NORMAL_ACCESS				(4)
#define ImJpegCommon_D_IM_JPEG_I_SEC_PRIVILEGED_ACCESS			(5)
#define ImJpegCommon_D_IM_JPEG_I_NSEC_NORMAL_ACCESS			(6)
#define ImJpegCommon_D_IM_JPEG_I_NSEC_PRIVILEGED_ACCESS		(7)


/*----------------------------------------------------------------------	*/
/* im_jpeg.c  Definition													*/
/*----------------------------------------------------------------------	*/
// for debug
//#define CO_IM_JPEG_DEBUG

#ifdef CO_ACT_CLOCK
#define ImJpegCommon_CO_ACT_JPEG_CLOCK
#endif //CO_ACT_CLOCK
#ifdef CO_ACT_HCLOCK
#define ImJpegCommon_CO_ACT_JPEG_HCLOCK
#endif //CO_ACT_HCLOCK
#ifdef CO_ACT_ICLOCK
#define ImJpegCommon_CO_ACT_JPEG_ICLOCK
#endif //CO_ACT_ICLOCK

#if 1	// Clock control force ON.
#ifndef CO_ACT_CLOCK
#define ImJpegCommon_CO_ACT_JPEG_CLOCK
#endif //CO_ACT_CLOCK
#ifndef CO_ACT_HCLOCK
#define ImJpegCommon_CO_ACT_JPEG_HCLOCK
#endif //CO_ACT_HCLOCK
#ifndef CO_ACT_ICLOCK
#define ImJpegCommon_CO_ACT_JPEG_ICLOCK
#endif //CO_ACT_ICLOCK
#endif

#define ImJpegCommon_D_IM_JPEG_CLK_REG_ADDR			(&Dd_Top_Get_CLKSTOP3())
#define ImJpegCommon_D_IM_JPEG_HCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP3())
#define ImJpegCommon_D_IM_JPEG_ICLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP3())
#define ImJpegCommon_D_IM_JPEG_CLK_BIT						DdTopone_JPGCK_BIT
#define ImJpegCommon_D_IM_JPEG_HCLK_BIT					DdTopone_JPGAH_BIT
#define ImJpegCommon_D_IM_JPEG_ICLK_BIT						DdTopone_JPGAX_BIT
#define ImJpegCommon_D_IM_JPEG_SECT_CNT					512

// difinition macro
#define ImJpegCommon_IM_JPEG_LIMIT_MIN(A, B)			(((A) > (B)) ? (A) : (B))
#define ImJpegCommon_IM_JPEG_LIMIT_MAX(A, B)			(((A) < (B)) ? (A) : (B))
#define ImJpegCommon_IM_JPEG_LIMIT(A, B, C)					(ImJpegCommon_IM_JPEG_LIMIT_MAX(ImJpegCommon_IM_JPEG_LIMIT_MIN((A), (B)), (C)))
#define ImJpegCommon_IM_JPEG_DSB()								DD_ARM_DSB_POU()


typedef enum _EimgSmplType						EimgSmplType;
typedef enum _EimgMemForm						EimgMemForm;
typedef enum _EimgAxiSt									EimgAxiSt;
typedef enum _EimgResizeExt							EimgResizeExt;
typedef enum _EimgIssueTran							EimgIssueTran;
typedef enum _EimgEndian								EimgEndian;
typedef enum _EimgBurstIncr							EimgBurstIncr;
typedef enum _EimgBurstAl								EimgBurstAl;
typedef enum _EimgBitDepth							EimgBitDepth;
typedef enum _EimgIipPortMode					EimgIipPortMode;
typedef enum _EimgIipBlock							EimgIipBlock;

typedef struct _TimgAddrYcc							TimgAddrYcc;
typedef struct _TimgComponentTbl				TimgComponentTbl;
typedef struct _TimgQuatTbl							TimgQuatTbl;
typedef struct _TimgQuatTblPack					TimgQuatTblPack;
typedef struct _TimgColorBand						TimgColorBand;
typedef struct _TimgAxiCtrl								TimgAxiCtrl;
typedef struct _TimgEncMng							TimgEncMng;
typedef struct _TimgEncFrameMng				TimgEncFrameMng;
typedef struct _TimgDecMng							TimgDecMng;
typedef struct _TimgDecFrameMng				TimgDecFrameMng;
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
typedef struct _TimgDecInput							TimgDecInput;
typedef struct _TimgDecOutput						TimgDecOutput;
//---------------------- colabo  section ----------------------------
#endif	// CO_DDIM_UTILITY_USE

typedef struct _ImJpegCommon						ImJpegCommon;
typedef struct _ImJpegCommonClass			ImJpegCommonClass;
typedef struct _ImJpegCommonPrivate 		ImJpegCommonPrivate;


/*----------------------------------------------------------------------*/
/* Enumeration																*/
/*----------------------------------------------------------------------*/
/** Jpeg sampling ratio type*/
enum _EimgSmplType
{
	ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444 = 0,
	ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422 = 1,
	ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420 = 2,
	ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400 = 3
} ;

/**Jpeg memory format type
 *  Planar format
 *	 Planar format of Y and Dot sequential format of CbCr
 */
enum _EimgMemForm
{
	ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE = 0,
	ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT = 1
} ;

/**Jpeg AXI(PBUF/JBUF) status
 *  PBUF and JBUF is not running
 *  PBUF and JBUF is running
 *  PBUF is running
 *  JBUF is running
 */
enum _EimgAxiSt
{
	ImJpegCommon_E_IM_JPEG_AXI_ST_INACTIVE_BOTH = 0,
	ImJpegCommon_E_IM_JPEG_AXI_ST_ACTIVE_BOTH = 1,
	ImJpegCommon_E_IM_JPEG_AXI_ST_ACTIVE_PBUF = 2,
	ImJpegCommon_E_IM_JPEG_AXI_ST_ACTIVE_JBUF = 3
} ;

/**Setting the Jpeg dummy area in decoding.
 *  Directly outputs the pixel containing the dummy area.
 *  Outputs the color band to pixel containing the dummy area.
 */
enum _EimgResizeExt
{
	ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT = 0,
	ImJpegCommon_E_IM_JPEG_RESIZE_EXT_BAND = 1
} ;

/**Number of transactions that can be issued by a continuous
 *  Issued eight times a transaction
 *  Issued four times a transaction
 *  Issued twice a transaction
 */
enum _EimgIssueTran
{
	ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8 = 0,
	ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_4 = 1,
	ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_2 = 2
} ;

/**AXI(JBUF/PBUF) endian setting
 *  AXI(JBUF/PBUF) little endian
 *  AXI(JBUF/PBUF) big endian
 */
enum _EimgEndian
{
	ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE = 0,
	ImJpegCommon_E_IM_JPEG_ENDIAN_BIG = 1
} ;

/**JBUF/PBUF(AXI) burst rength
 *  64 byte transfer
 *  128 byte transfer
 */
enum _EimgBurstIncr
{
	ImJpegCommon_E_IM_JPEG_BURST_INCR_8 = 0,
	ImJpegCommon_E_IM_JPEG_BURST_INCR_16 = 1
} ;

/**Burst alignment control on/off setting of the code data.
 *  Burst alignment control ON
 *  Burst alignment control OFF
 */
enum _EimgBurstAl
{
	ImJpegCommon_E_IM_JPEG_BURST_AL_ON = 0,
	ImJpegCommon_E_IM_JPEG_BURST_AL_OFF = 1
} ;

/** Bit depth.*/
enum _EimgBitDepth
{
	ImJpegCommon_E_IM_JPEG_BIT_DEPTH_8BIT = 0,
	ImJpegCommon_E_IM_JPEG_BIT_DEPTH_12BIT = 1
} ;

/**IIP cooperation mode.
 *  IIP cooperation mode OFF
 *  IIP 1 port (P0)
 */
enum _EimgIipPortMode
{
	ImJpegCommon_E_IM_JPEG_IIP_PORT_MODE_OFF = 0,
	ImJpegCommon_E_IM_JPEG_IIP_PORT_MODE_1 = 4,
	ImJpegCommon_E_IM_JPEG_IIP_PORT_MODE_2 = 5,
	ImJpegCommon_E_IM_JPEG_IIP_PORT_MODE_3 = 6,
	ImJpegCommon_E_IM_JPEG_IIP_PORT_MODE_4 = 7
} ;

/**IIP cooperation mode.
 *  1 block is 64 * 8 (format:420 8->16)
 *  1 block is Horizontal size * 8 (format:420 8->16)
 */
enum _EimgIipBlock
{
	ImJpegCommon_E_IM_JPEG_IIP_BLOCK_64x8 = 0,
	ImJpegCommon_E_IM_JPEG_IIP_BLOCK_128x8 = 1,
	ImJpegCommon_E_IM_JPEG_IIP_BLOCK_256x8 = 2,
	ImJpegCommon_E_IM_JPEG_IIP_BLOCK_HSIZEx8 = 3
} ;


/*----------------------------------------------------------------------*/
/* Structure																		*/
/*----------------------------------------------------------------------*/
/** YCC image address
 *  Y address
 *  C address
 */
struct _TimgAddrYcc
{
	gulong y;
	gulong c;
} ;

/** Jpeg Component table*/
struct _TimgComponentTbl
{
	/**< Quantization table number.<br>:value range[0 - 3] */
	guchar quantTblNo;
	/**< DC huffman table number.<br>:value range[0 - 1] */
	guchar hufDcTblNo;
	/**< AC huffman table number.<br>:value range[0 - 1] */
	guchar hufAcTblNo;
} ;

/** Jpeg Quatization table*/
struct _TimgQuatTbl
{
	guchar quantValue[64];
} ;

/** Jpeg Quatization table pack
 *  Quantization table 0
 */
struct _TimgQuatTblPack
{
	TimgQuatTbl* quantizationTbl0;
	TimgQuatTbl* quantizationTbl1;
	TimgQuatTbl* quantizationTbl2;
	TimgQuatTbl* quantizationTbl3;
} ;

/**Jpeg Color band
 *  Color band of the Y component
 *  Color band of the Cb component
 *  Color band of the Cr component
 */
struct _TimgColorBand
{
	guchar yBand;
	guchar cbBand;
	guchar crBand;
} ;

/** JBUF/PBUF(AXI) Contoroll table*/
struct _TimgAxiCtrl
{
	/**< Endian setting. */
	EimgEndian endian;
	/**< Continuous issuing number of the transaction. */
	EimgIssueTran issueTranNum;
	guchar cacheType;
	guchar protType;
	guchar errState;
} ;

/** Jpeg encode base management structure*/
struct _TimgEncMng
{
	/**< Sampling type. */
	EimgSmplType yccSmpl;
	/**< Memory format type. */
	EimgMemForm memFormat;
	/**< Horizontal size.<br> :value range[64 - 65520] */
	gushort width;
	/**< Vertical size.<br>:value range[64 - 65280] */
	gushort lines;
	/**< Use number of the component table. */
	TimgComponentTbl component[3];
	guchar skipMkFlg;
	/**< MCU number to insert the DRI marker. */
	gushort driMkNum;
	guchar exifFmtFlg;
	/**< Periodic line interrupt function.<br> Generate an interrupt after setting lines processed. */
	gushort pintLine;
	/**< Periodic sector interrupt function.<br> Generate an interrupt after setting sector processed. */
	gulong pintSect;
	TimgAxiCtrl pbufCtrl;
	TimgAxiCtrl jbufCtrl;
	EimgBurstIncr pburstLength;
	EimgBurstIncr jburstLength;
	EimgBitDepth bitDepth;
	EimgBurstAl burstAlignment;
	EimgIipPortMode portMode;
	guchar ringOn;
	EimgIipBlock blockSize;
	guchar ringSize;
	gulong codeSize;
	gint32 result;
	VpCallbackFunc pcallback;
} ;

/** Jpeg encode frame management structure*/
struct _TimgEncFrameMng
{
	gulong globalYWidth;
	gulong globalCWidth;
	TimgAddrYcc yccAddr;
	gulong codeAddr;
	guchar codeCountFlg;
	guchar codeOverCountFlg;
	kulonglong limitSize;
} ;

/** Jpeg decode base management structure*/
struct _TimgDecMng
{
	EimgMemForm memFormat;
	EimgResizeExt extMode;
	guchar corrMode;
	guchar skipMkFlg;
	gushort pintLine;
	gulong pintSect;
	TimgColorBand colorBand;
	TimgAxiCtrl pbufCtrl;
	TimgAxiCtrl jbufCtrl;
	EimgBurstIncr pburstLength;
	EimgBurstIncr jburstLength;
	EimgBurstAl burstAlignment;
	EimgIipPortMode portMode;
	guchar ringOn;
	EimgIipBlock blockSize;
	guchar ringSize;
	EimgSmplType smplType;
	gushort orgWidth;
	gushort orgLines;
	gint32 result;
	guchar errCode;
	VpCallbackFunc pcallback;
} ;

/** Jpeg decode frame management structure*/
struct _TimgDecFrameMng
{
	/**< Global Y width.<br> Should be aligned on 8:value range[64 - 1048512]  */
	gulong globalYWidth;
	/**< Global C width.<br> Should be aligned on 8:value range[64 - 1048512]  */
	gulong globalCWidth;
	/**< Flag to use the cutout function of image. */
	guchar cutoutFlg;
	/**< Horizontal of cutout.<br> Should be aligned on 16:value range[64 - 65280]<br>
	 But, Please set to 0 if you do not use the cutout function. */
	gushort cutoutWidth;
	/**< Vertical of cutout.<br> Should be aligned on 16.<br> :value range[64 - 65520]<br>
	 But, Please set to 0 if you do not use the cutout function. */
	gushort cutoutLines;
	/**< Horizontal offset of cutout.<br> Should be aligned on 16:value range[0 - 65216] */
	gushort cutoutOffsetH;
	/**< Vertical offset of cutout.<br> Should be aligned on 16:value range[0 - 65456] */
	gushort cutoutOffsetV;
	/**< Header address of YCC.Should be aligned on 8.*/
	TimgAddrYcc yccAddr;
	/**< Header address of compressed data.Should be aligned on 8. */
	gulong codeAddr;
	kulonglong codeSize;
} ;

/*  Explanation of parameters
 [Sample image of Jpeg decode]

         [ Jpeg ]                   [ YUV ]

       |           |           |      *1       |
       |           |           |<------------->|
       |           |           |               |
       |           |           |               |
 ------@a----------+           +---------------+--------
       |***********|           | @b----------+ |----
       |***********|  Decode   | |***********| |
       |***********| --------> | |***********| |
       |***********|           | |**** Y ****| |
       |***********|           | |***********| |
       |***********|           | |***********| |
 ------+-----------+           | |***********| |
                               | +-----------+ |----
                               +---------------+--------

       Fig.1 Sample of normal decode setting
       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

         [ Jpeg ]                     [ YUV ]

       |               |
       |               |           |     *1    |
       | *4|  *2 |     |           |<--------->|
       |<->|<--->|     |           |           |
 ------@a--------------+           +-----------+
     *5|               |           |           |
    ---|   +-----+     |  Decode   |           |
     *3|   |*****| --------+       @b----+     |---
       |   |*****|     |   |       |*****|     | *3
    ---|   +-----+     |   +-----> |*****|     |
       |               |           +-----+-----+---
 ------+---------------+           |  *2 |
                                   |<--->|

       Fig.2 Sample of decode cut-off setting
       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 [Meaning of parameters]
   *1 :globalYWidth   -> JIMGYGH (frame area width of the Y data)
   *2 :cutoutWidth     -> JIMGSH
   *3 :cutoutLines     -> JIMGSV
   *4 :cutoutOffsetH  -> HOFFSET
   *5 :cutoutOffsetV  -> VOFFSET
   @a :codeAddr        -> JCODA
   @b :yccAddr         -> JIMGAY

 [Usage]
   1. When Jpeg decode cut-off is not used(it means normal decode). (See Fig.1)
       - the value of cut_h_offset and cut_v_offset has to be 0.
       - width and lines is used download value.
   2. When Jpeg decode cut-off is used. (See Fig.2)

*/
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/** Jpeg decode input table
 * @remarks This is for utility
*/
struct _TimgDecInput
{
	/**< Global Y width (must 8 byte aligned value) :value range[64 - 1048512] */
	gulong globalYWidth;
	/**< Global CbCr width (must 8 byte aligned value) :value range[64 - 1048512] */
	gulong globalCWidth;
	/**< Memory format type */
	EimgMemForm memFormat;
	/**< Sampling type */
	EimgSmplType smplType;
	/**< Size of Jpeg compressed data :value range[0 - 0x1FFFFFFFC00] */
	kulonglong codeSize;
	/**< Header address of compressed data (must 8 byte aligned value) */
	gulong codeAddr;
	/**< Header address of YCC data (must 8 byte aligned value) */
	TimgAddrYcc dstYccAddr;
} ;

/** Jpeg decode output table
 * @remarks This is for utility
*/
struct _TimgDecOutput
{
	/**< Sampling type */
	EimgSmplType smplType;
	/**< Horizontal of the original image data */
	gushort orgWidth;
	/**< Vertical of the original image data */
	gushort orgLines;
	/**< Decompression error code */
	guchar errCode;
} ;
//---------------------- colabo  section -------------------------------
#endif	// CO_DDIM_UTILITY_USE


struct _ImJpegCommon
{
	GObject parent;
	DdimUserCustom *ddimUserCustom;
};

struct _ImJpegCommonClass
{
	GObjectClass parentClass;
};


GType										im_jpeg_common_get_type(void)	G_GNUC_CONST;
ImJpegCommon*					im_jpeg_common_new(void);

/**
This function cancels the Sleep state of Jpeg macro
*/
extern	void	im_jpeg_init( ImJpegCommon*self );
/**
 This function open (acquire semaphore) of Jpeg macro.
 @param [in]	tmout																: Time of timeout<br>
 <ul>
 <li>Positive Value(Time of timeout)
 <li>@ref D_DDIM_USER_SEM_WAIT_POL
 <li>@ref D_DDIM_USER_SEM_WAIT_FEVR
 </ul>
 @retval		ImJpegCommon_D_IM_JPEG_OK						: Success.
 @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
 @retval		ImJpegCommon_D_IM_JPEG_SEM_NG				: Semaphoore acquisition error.
 @retval		ImJpegCommon_D_IM_JPEG_SEM_TIMEOUT	: Semaphoore acquisition TimeOut.
 @remarks		This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
 */
extern	gint32	im_jpeg_open(ImJpegCommon*self, gint32 tmout );

/**
 This function close (release semaphore) of Jpeg macro.
 @retval		ImJpegCommon_D_IM_JPEG_OK				: Success.
 @retval		ImJpegCommon_D_IM_JPEG_SEM_NG		: Semaphoore acquisition error.
 @remarks		This API uses DDIM_User_Sig_Sem().
 */
extern	gint32	im_jpeg_close( ImJpegCommon*self );
/**
 This function set quantization table.
 @param [in]	pQuantTbl				: Pointer of quantization table pack.<br>
 @param [in]	nextFrmFlg				: Flag to determine whether a quantization table for the next frame.<br>
 0: Current frame / 1: Next frame
 @remarks		"pQuantTbl" is NULL, use the default table.<br>
 */
extern	void	im_jpeg_set_qtbl(ImJpegCommon*self, TimgQuatTblPack* pQuantTbl, guchar nextFrmFlg );

/**
 This function set Jpeg quality values depend on quantization table.
 @param [in]	quaValue												: Quality value (format: S7.10)
 @param [in]	nextFrmFlg											: Flag to determine whether a quantization table for the next frame.<br>
 0: Current frame / 1: Next frame
 @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
 @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
 */
extern	gint32	im_jpeg_set_quality(ImJpegCommon*self, gint32 quaValue, guchar nextFrmFlg );
/**
  This function is setting of the block downsampling.
  @param [in]	downspType		: downsampling type
									<ul>
										<li>@ref ImJpegCommon_D_IM_JPEG_DOWNSP_NONE
										<li>@ref ImJpegCommon_D_IM_JPEG_DOWNSP_1_2
										<li>@ref ImJpegCommon_D_IM_JPEG_DOWNSP_1_4
										<li>@ref ImJpegCommon_D_IM_JPEG_DOWNSP_1_8
									</ul>
  @retval		gushort					: Proportion of remainder after adjusting for size when decimated.( format: 8.8 )
  @remarks		Please call this function after you have made the setting in im_jpeg_ctrl_enc()
*/
extern	gushort	im_jpeg_set_down_sampling_rate(ImJpegCommon*self, guchar downspType );
/**
  This function set Jpeg encode base management table data before encode process start.
  @param [in]	pJpgEncMng													: Pointer to Jpeg encode base management table
  @retval		ImJpegCommon_D_IM_JPEG_OK						: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
  @retval		D_IM_JPEG_BUSY_NG		: Macro busy.
*/
extern	gint32	im_jpeg_ctrl_enc(ImJpegCommon*self, TimgEncMng* pJpgEncMng );
/**
  This function get the frame settings for Jpeg decode.
  @param [out]	pJpgDecFrmMng											: pointer to Jpeg decode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK						: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
  @remarks		Please call this function after you have made the setting in im_jpeg_ctrl_dec()<br>
				It can set during the decoding process, If the same base configuration to decode<br>
				If you want to set in during Jpeg decoding process, please set after PBUF and JBUF is running.<br>
*/
extern	gint32	im_jpeg_get_ctrl_dec_frame(ImJpegCommon*self, TimgDecFrameMng* pJpgDecFrmMng );
/**
  This function starts as asynchronous processing Jpeg decoded.
  @retval		ImJpegCommon_D_IM_JPEG_OK												: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_RUNNING_NG							: Macro is running error.
  @retval		ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR						: System call error.
  @remarks		If you want to synchronize, please call im_jpeg_wait_end_dec().<br>
  				This API uses DDIM_User_Clr_Flg().
  @remarks		This API uses DDIM_User_Twai_Flg().
*/
extern	gint32 im_jpeg_start_dec( ImJpegCommon*self );


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_JPEG_COMMON_H__ */
