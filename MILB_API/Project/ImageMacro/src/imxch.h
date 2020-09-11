/*
 * imxch.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、interrupt setting process api
*2、
*@version:        1.0.0
*/

#ifndef __IM_XCH_H__
#define __IM_XCH_H__

#include <klib.h>
#include "driver_common.h"


#define IM_TYPE_XCH      (im_xch_get_type())
#define IM_XCH(obj)        (K_TYPE_CHECK_INSTANCE_CAST(obj, ImXch))
#define IM_IS_XCH(obj)  (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_XCH))


// for debug
#define CO_IM_XCH_DEBUG

#ifdef CO_ACT_PCLOCK
#define CO_ACT_XCH_PCLOCK
#endif //CO_ACT_PCLOCK
#ifdef CO_ACT_ICLOCK
#define CO_ACT_XCH_ICLOCK
#endif //CO_ACT_ICLOCK

#define D_IM_XCH_APCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP6())
#define D_IM_XCH_AXCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP6())

#define D_IM_XCH_PCLK_REG_BIT		D_DD_TOP_XCHAP_BIT	// bit1
#define D_IM_XCH_ICLK_REG_BIT		D_DD_TOP_XCHAX_BIT	// bit3

#define D_IM_XCH_ICF_XF0_OFF		(0x0001)			// XCHICF XF0 OFF
#define D_IM_XCH_ICF_XF1_OFF		(0x0010)			// XCHICF XF1 OFF

// XCHCTL0.XTRG.bit.TRG
// XCHCTL1.XTRG.bit.TRG
#define	D_IM_XCH_STOP				(0)
#define	D_IM_XCH_START				(1)
#define	D_IM_XCH_STOPPED			(2)
#define	D_IM_XCH_RUNNING			(3)

// macro
#define Im_XCH_Dsb()				Dd_ARM_Dsb_Pou()


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// #define D_IM_XCH_PRINT_ST	// for debug

/* Return value of processing result
*/
#define D_IM_XCH_OK						(D_DDIM_OK)								/**< Normal end						*/
#define D_IM_XCH_NG						(D_IM_XCH | D_DDIM_SYSTEM_ERROR)		/**< Processing NG					*/
#define D_IM_XCH_INPUT_PARAM_ERR		(D_IM_XCH | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error			*/
#define D_IM_XCH_SEM_TIMEOUT			(D_IM_XCH | D_DDIM_SEM_TIMEOUT)			/**< Semaphore acquisition Time Out */
#define D_IM_XCH_SEM_NG					(D_IM_XCH | D_DDIM_SEM_NG)				/**< Semaphore acquisition NG		*/
#define D_IM_XCH_MACRO_BUSY_NG			(D_IM_XCH | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy Error				*/


/* Interrupt flag
*/
#define D_IM_XCH_FLG_0_WAIT_END			(0x00000001)							/**< Xch-0 flag to wait for async processing end */
#define D_IM_XCH_FLG_1_WAIT_END			(0x00000002)							/**< Xch-1 flag to wait for async processing end */

/* XMD (Mode select)
*/
#define D_IM_XCH_MD_DOWN_HI_SPEED		(0)										/**< Downsampling process mode (high-speed) */
#define D_IM_XCH_MD_DOWN				(1)										/**< Downsampling process mode */
#define D_IM_XCH_MD_HISTGRAM_DOWN		(2)										/**< Get histogram data mode (downsampling output transfer available) */
#define D_IM_XCH_MD_HISTGRAM			(3)										/**< Get histogram data mode (no downsampling output transfer) */
#define D_IM_XCH_MD_HORI_1_2_EVEN		(4)										/**< Horizontal 1/2 downsampling mode (even pixel output) */
#define D_IM_XCH_MD_HORI_1_2_ODD		(5)										/**< Horizontal 1/2 downsampling mode (odd pixel output) */
#define D_IM_XCH_MD_COPY				(6)										/**< Copy transfer mode */
#define D_IM_XCH_MD_FILL				(7)										/**< Fill mode */

/* XDTYPE (Type select)
*/
#define D_IM_XCH_XDTYPE_8				(0)										/**< Input data width of 8bit */
#define D_IM_XCH_XDTYPE_16				(1)										/**< Input data width of 16bit */

/* HCNT0 (Histgram initizlize setting)
*/
#define D_IM_XCH_INITIALIZE				(0)										/**< Initialize the histgram data */
#define D_IM_XCH_INHERITING				(1)										/**< Inheriting the histgram data */

#ifdef CO_DDIM_UTILITY_USE
/**
@name Utility Definition
@{*/

//---------------------- utility section -------------------------------

/* Down sampling rate select */
#define D_IM_XCH_THIN_SEL_1_1			(0)										/**< 1/1 (not downsampling) */
#define D_IM_XCH_THIN_SEL_1_2			(1)										/**< 1/2 downsampling out */
#define D_IM_XCH_THIN_SEL_1_4			(2)										/**< 1/4 downsampling out */
#define D_IM_XCH_THIN_SEL_3_4			(3)										/**< 3/4 downsampling out */

//---------------------- colabo  section -------------------------------

/*@}*/
#endif	// CO_DDIM_UTILITY_USE

// Synchronous mode when Xch is executed
typedef enum {
	E_IM_XCH_SYNC_TYPE_SYNC = 0,	// Sync Processing
	E_IM_XCH_SYNC_TYPE_ASYNC		// Async Processing
} E_IM_XCH_SYNC_TYPE;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/** Xch0 or Xch1 select
*/
typedef enum {
	E_IM_XCH_CH_SEL_0		= 0,		/**< Select X0ch */
	E_IM_XCH_CH_SEL_1					/**< Select X1ch */
} E_IM_XCH_CH_SEL;

/** Xch0 or Xch1 transfer status
*/
typedef enum {
	E_IM_XCH_ST_STOPPED	= 0,			/**< Xch stopped */
	E_IM_XCH_ST_RUNNING					/**< Xch running */
} E_IM_XCH_ST;

#ifdef CO_DDIM_UTILITY_USE
/**
@name Utility Enumeration
@{*/

//---------------------- utility section -------------------------------

/** Copy mode select
*/
typedef enum {
	E_IM_XCH_COPY_SEL_HI		= 0,	/**< Select hi-speed copy */
	E_IM_XCH_COPY_SEL_NORMAL			/**< Select normal copy */
} E_IM_XCH_COPY_SEL;

//---------------------- colabo  section -------------------------------

/*@}*/
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/** Xch driver common control structure
*/
typedef struct {
	UCHAR	mode;								/**< Operation mode. @@XMD
													<ul>
														<li>@ref D_IM_XCH_MD_DOWN_HI_SPEED
														<li>@ref D_IM_XCH_MD_DOWN
														<li>@ref D_IM_XCH_MD_HISTGRAM_DOWN
														<li>@ref D_IM_XCH_MD_HISTGRAM
														<li>@ref D_IM_XCH_MD_HORI_1_2_EVEN
														<li>@ref D_IM_XCH_MD_HORI_1_2_ODD
														<li>@ref D_IM_XCH_MD_COPY
														<li>@ref D_IM_XCH_MD_FILL
													</ul>
												 */
	USHORT	gHsize;							/**< Global horizontal size of the output area. @@XGHW <br>
													 Set at 16 byte units.
												 */
	USHORT	dHsize;							/**< Horizontal size of the output area. @@XDHW <br>
													 Set at 16 byte units if you use the following mode.<br>
													<ul>
														<li>@ref D_IM_XCH_MD_HORI_1_2_EVEN
														<li>@ref D_IM_XCH_MD_HORI_1_2_ODD
														<li>@ref D_IM_XCH_MD_COPY
													</ul>
												 */
	USHORT	dVsize;							/**< Vertical size of the output area. @@XDVW
												 */
	UINT32	dstAddr;							/**< Start address of the output area. @@XDA <br>
													 Set at 16 byte units if you use the following mode.<br>
													<ul>
														<li>@ref D_IM_XCH_MD_HORI_1_2_EVEN
														<li>@ref D_IM_XCH_MD_HORI_1_2_ODD
														<li>@ref D_IM_XCH_MD_COPY
													</ul><br>
													 But, When accessing the SRAM, Set at 32 byte units.
												 */
	VP_CALLBACK	pCallBack;						/**< Callback function pointer.
												 */
} ImXchCtrlCmn;

/** Xch driver downsampling control structure
*/
typedef struct {
	UCHAR	xdtype;								/**< Input data width. @@XDDTYPE @@XSDTYPE <br>
													<ul>
														<li>@ref D_IM_XCH_XDTYPE_8
														<li>@ref D_IM_XCH_XDTYPE_16
													</ul>
												 */
	UCHAR	hcyc;								/**< Down sampling cycle of the horizontal. @@XHCYC <br>
													 Value Range :[0x00-0x1F] <br>
													  0x00 : 32 byte cycle<br>
													  0x01 : 1 byte cycle<br>
													  :<br>
													  0x1F : 31 byte cycle<br>
												 */
	UCHAR	vcyc;								/**< Down sampling cycle of the vertical.  @@XVCYC <br>
													 Value Range :[0x00-0x1F] <br>
													  0x00 : 32 line cycle<br>
													  0x01 : 1 line cycle<br>
													  :<br>
													  0x1F : 31 line cycle<br>
												 */
	UINT32	hen;								/**< Data acquisition in the horizontal direction. @@XHEN <br>
													 (Set in the MSB-justified)
													 Please set so that there is valid data to within range of "hcyc".
												 */
	UINT32	ven;								/**< Line acquisition in the vertical direction. @@XVEN <br>
													 (Set in the MSB-justified)
													 Please set so that there is valid data to within range of "vcyc".
												 */
	USHORT	sHsize;							/**< The horizontal size of the original data. @@XSHW <br>
													 Set at 16 byte units.
												 */
	UINT32	srcAddr;							/**< Start address of the source area. @@XSA <br>
													 When accessing the SRAM, Set at 64 byte units.
												 */
} ImXchCtrlThin;

/** Xch driver histogram control structure
*/
typedef struct {
	UCHAR	xdtype;								/**< Input data width. @@XDDTYPE @@XSDTYPE <br>
													<ul>
														<li>@ref D_IM_XCH_XDTYPE_8
														<li>@ref D_IM_XCH_XDTYPE_16
													</ul>
												 */
	UCHAR	hcyc;								/**< Down sampling cycle of the horizontal. @@XHCYC <br>
													 Value Range :[0x00-0x1F] <br>
													  0x00 : 32 byte cycle<br>
													  0x01 : 1 byte cycle<br>
													  :<br>
													  0x1F : 31 byte cycle<br>
												*/
	UCHAR	vcyc;								/**< Down sampling cycle of the vertical.  @@XVCYC <br>
													 Value Range :[0x00-0x1F] <br>
													  0x00 : 32 line cycle<br>
													  0x01 : 1 line cycle<br>
													  :<br>
													  0x1F : 31 line cycle<br>
												 */
	UINT32	hen;								/**< Data acquisition in the horizontal direction. @@XHEN <br>
													 (Set in the MSB-justified)<br>
													 Please set so that there is valid data to within range of "hcyc".
												 */
	UINT32	ven;								/**< Line acquisition in the vertical direction. @@XVEN <br>
													 (Set in the MSB-justified)<br>
													 Please set so that there is valid data to within range of "vcyc".
												 */
	USHORT	sHsize;							/**< The horizontal size of the original data. @@XSHW <br>
													 Set at 16 byte units.
												 */
	UINT32	srcAddr;							/**< Start address of the source area. @@XSA <br>
													 When accessing the SRAM, Set at 64 byte units.
												 */
	UCHAR	hcnt;								/**< The initialize or inheriting of the histogram data. @@XHCNT0 <br>
													<ul>
														<li>@ref D_IM_XCH_INITIALIZE
														<li>@ref D_IM_XCH_INHERITING
													</ul>
												 */
} ImXchCtrlHist;

/** Xch driver half downsampling control structure
*/
typedef struct {
	UCHAR	vcyc;								/**< Down sampling cycle of the vertical.  @@XVCYC <br>
													 Value Range :[0x00-0x1F] <br>
													  0x00 : 32 line cycle<br>
													  0x01 : 1 line cycle<br>
													  :<br>
													  0x1F : 31 line cycle<br>
												 */
	UINT32	ven;								/**< Line acquisition in the vertical direction. @@XVEN <br>
													 (Packed to the left)
												 */
	USHORT	sHsize;							/**< The horizontal size of the original data. @@XSHW <br>
													 Set at 16 byte units.
												 */
	UINT32	srcAddr;							/**< Start address of the source area. @@XSA <br>
													 Set at 16 byte units.<br>
													 But, When accessing the SRAM, Set at 64 byte units.
												 */
} ImXchCtrlHalfThin;

/** Xch driver copy control structure
*/
typedef struct {
	UCHAR	vcyc;								/**< Down sampling cycle of the vertical.  @@XVCYC <br>
													 Value Range :[0x00-0x1F] <br>
													  0x00 : 32 line cycle<br>
													  0x01 : 1 line cycle<br>
													  :<br>
													  0x1F : 31 line cycle<br>
												 */
	UINT32	ven;								/**< Line acquisition in the vertical direction. @@XVEN <br>
													 (Packed to the left)
												 */
	USHORT	sHsize;							/**< The horizontal size of the original data. @@XSHW <br>
													 Set at 16 byte units.
												 */
	UINT32	srcAddr;							/**< Start address of the source area. @@XSA <br>
													 Set at 16 byte units.<br>
													 But, When accessing the SRAM, Set at 64 byte units.
												 */
} ImXchCtrlCopy;

#ifdef CO_DDIM_UTILITY_USE

//---------------------- utility section -------------------------------

/**
@name Utility Data Structures
@{*/

/** Xch driver copy structure
*/
typedef struct {
	E_IM_XCH_CH_SEL		xch;					/**< Channel select.<br>
													<ul>
														<li>@ref E_IM_XCH_CH_SEL_0
														<li>@ref E_IM_XCH_CH_SEL_1
													</ul>
												 */
	E_IM_XCH_COPY_SEL	copyType;				/**< Copy type select. <br>
													<ul>
														<li>@ref E_IM_XCH_COPY_SEL_HI
														<li>@ref E_IM_XCH_COPY_SEL_NORMAL
													</ul>
												 */
	struct {
		USHORT			width;					/**< Copy image width. @@XDHW <br><br>
													 Restrictions by the use type.<br>
													 <ul>
														<li>@ref E_IM_XCH_COPY_SEL_HI &nbsp;: Set at 16 byte units.
													 </ul>
												 */
		USHORT			lines;					/**< Copy image lines. @@XDVW
												 */
		USHORT			srcGlWidth;			/**< Source image width. @@XSHW<br>
													 Set at 16 byte units.
												 */
		USHORT			dstGlWidth;			/**< Destination image global width. @@XGHW<br>
													 Set at 16 byte units.
												 */
	} size;										/**< Src and Dst image size. */
	struct {
		ULONG			src;					/**< Source data address. @@XSA <br><br>
													 Restrictions by the use type.<br>
													 <ul>
														<li>@ref E_IM_XCH_COPY_SEL_HI &nbsp;: Set at 16 byte units.
													 </ul>
													 But, When accessing the SRAM, Set at 64 byte units.
												 */
		ULONG			dst;					/**< Destination data address. @@XDA <br><br>
													 Restrictions by the use type.<br>
													 <ul>
														<li>@ref E_IM_XCH_COPY_SEL_HI &nbsp;: Set at 16 byte units.
													 </ul>
													 But, When accessing the SRAM, Set at 32 byte units.
												 */
	} addr;										/**< Src and Dst image address. */
} ImXchCopyEx;


/** Xch driver fill structure
*/
typedef struct {
	E_IM_XCH_CH_SEL		xch;					/**< Channel select.<br>
													<ul>
														<li>@ref E_IM_XCH_CH_SEL_0
														<li>@ref E_IM_XCH_CH_SEL_1
													</ul>
												 */
	UCHAR				fillDate;				/**< Data to fill. @@XFDT
												 */
	ULONG				fillAddr;				/**< Start address to fill. @@XDA <br>
													 When accessing the SRAM, Set at 32 byte units.
												 */
	struct {
		USHORT			width;					/**< Image width. @@XDHW
												 */
		USHORT			lines;					/**< Image lines. @@XDVW
												 */
		USHORT			glWidth;				/**< Image global width. @@XGHW<br>
													 Set at 16 byte units.
												 */
	} size;										/**< fill size */
} ImXchFillEx;

/** Xch driver histogram structure
*/
typedef struct {
	ULONG				histAddr;				/**< Histogram image address. @@XDA @@XSA <br>
													 When accessing the SRAM, Set at 64 byte units.
												 */
	struct {
		USHORT			width;					/**< Image width. @@XGHW @@XSHW @@XDHW<br>
													 Set at 16 byte units.
												 */
		USHORT			lines;					/**< Image lines. @@XDVW
												 */
	} size;										/**< histogram image size */
} ImXchExamineHist;

/** Xch driver downsampling structure
*/
typedef struct {
	E_IM_XCH_CH_SEL		xch;					/**< Channel select.<br>
													<ul>
														<li>@ref E_IM_XCH_CH_SEL_0
														<li>@ref E_IM_XCH_CH_SEL_1
													</ul>
												 */
	UINT32				thinWidth;				/**< Thinning out rate select of width.<br>
													<ul>
														<li>@ref D_IM_XCH_THIN_SEL_1_1
														<li>@ref D_IM_XCH_THIN_SEL_1_2
														<li>@ref D_IM_XCH_THIN_SEL_1_4
														<li>@ref D_IM_XCH_THIN_SEL_3_4
													</ul>
												 */
	UINT32				thinLines;				/**< Thinning out rate select of lines.<br>
													<ul>
														<li>@ref D_IM_XCH_THIN_SEL_1_1
														<li>@ref D_IM_XCH_THIN_SEL_1_2
														<li>@ref D_IM_XCH_THIN_SEL_1_4
														<li>@ref D_IM_XCH_THIN_SEL_3_4
													</ul>
												 */
	struct {
		USHORT			width;					/**< Source image width.
												 */
		USHORT			lines;					/**< Source image lines.
												 */
		USHORT			srcGlWidth;			/**< Source image width. @@XSHW <br>
													 Set at 16 byte units.
												 */
		USHORT			dstGlWidth;			/**< Destination image global width. @@XGHW <br>
													 Set at 16 byte units.
												 */
	} size;										/**< Src and Dst image size. */
	struct {
		ULONG			src;					/**< Source data address. @@XSA <br>
													 When accessing the SRAM, Set at 64 byte units.<br>
												 */
		ULONG			dst;					/**< Destination data address. @@XDA <br>
													 When accessing the SRAM, Set at 32 byte units.<br>
												 */
	} addr;										/**< Src and Dst image address. */
} ImXchConvThin;

/*@}*/

//---------------------- colabo  section -------------------------------



#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
//---------------------- colabo  section -------------------------------
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// Nothing Special

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
//---------------------- colabo  section -------------------------------
#endif	// CO_DDIM_UTILITY_USE


typedef struct {
	E_IM_XCH_SYNC_TYPE	syncType;	// Synchronous mode
	UCHAR				xdtype;		// @XDTYPE	: Input data width
	UCHAR				xmd;		// @XMD		: Operation mode
	UCHAR				xfdt;		// @XFDT	: Fill data
	UCHAR				xhcyc;		// @XHCYC	: Horizontal downsampling cycle
	UCHAR				xvcyc;		// @XVCYC	: Vertical downsampling cycle
	ULONG				xhen;		// @XHEN	: Horizontal import data
	ULONG				xven;		// @XVEN	: Vertical import data
	USHORT				xshw;		// @XSHW	: Source image horizontal size
	USHORT				xghw;		// @XGHW	: Global image horizontal size
	USHORT				xdhw;		// @XDHW	: Destination image horizontal size
	USHORT				xdvw;		// @XDVW	: Destination image vertical size
	ULONG				xsa;		// @XSA		: Source image area address
	ULONG				xda;		// @XDA		: Destination image area address
	UCHAR				xhcnt;		// @XHCNT	: Continuance of histogram data acquisition
	VP_CALLBACK			pCallBack;	// Call Back function pointer
} ImXchMngSave;

typedef struct _ImXch  ImXch;
typedef struct _ImXchPrivate ImXchPrivate;

struct _ImXch {
KObject parent;
ImXchMngSave	      gImXchMngSave[2];
};


KConstType  im_xch_get_type(void);
ImXch* im_xch_get(void);

VOID im_xch_off_pclk( ImXch*self );
VOID im_xch_on_pclk( ImXch*self );
INT32 im_xch_softreset( ImXch*self );
INT32 im_xch_open( ImXch*self,E_IM_XCH_CH_SEL xch, INT32 tmout );
VOID im_xch_init( ImXch*self );
INT32 im_xch_start_sync( ImXch*self,E_IM_XCH_CH_SEL xch );
INT32 im_xch_start_async( ImXch*self,E_IM_XCH_CH_SEL xch );
INT32 im_xch_get_histogram( ImXch*self,ULONG* histogram_buf );
INT32 im_xch_wait_end( ImXch*self,E_IM_XCH_CH_SEL xch );
INT32 im_xch_close( ImXch*self,E_IM_XCH_CH_SEL xch );
INT32 im_xch_stop( ImXch*self );
VOID im_xch_int_handler( VOID );
INT32 im_xch_fill( ImXch*self,E_IM_XCH_CH_SEL xch, UCHAR fill_data, USHORT gl_width, UINT32 dst_addr, USHORT width, USHORT lines );
INT32 im_xch_fill_ex_sync( ImXch*self,ImXchFillEx* fill_param );
INT32 im_xch_fill_ex_async( ImXch*self,ImXchFillEx* fill_param, VP_CALLBACK pCallBack );



#define im_xch_get_gIM_Xch_Mng_Save(self,i)         (self->gImXchMngSave[i])


#endif /* __IM_XCH_H__ */
