/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/

/**
@addtogroup image
@{
	@addtogroup im_cnr
	@{
	- @ref im_cnr_sample
*/
/**	@}
@}*/

#ifndef  __IM_CNR_H__
#define __IM_CNR_H__


#include <glib-object.h>
#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"


G_BEGIN_DECLS

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/**
@weakgroup im_cnr
@{
*/
//---------------------------- driver section ----------------------------
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
// #define CO_CNR_DEBUG
// #define CO_CNR_REG_TYPE_CHECK

// Low power consumption option
#define IM_TYPE_CNR							(im_cnr_get_type ())
#define IM_CNR(obj)							(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_CNR, ImCnr))
#define IM_CNR_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_CNR, ImCnrClass))
#define IM_IS_CNR(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_CNR))
#define IM_IS_CNR_CLASS(klass)		    (G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_CNR))
#define IM_CNR_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_CNR, ImCnrClass))

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_IMAGE_CLOCK)
#	define CO_ACT_CNRCLOCK
#endif
#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#	define CO_ACT_CNR_ICLK
#endif
#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#	define CO_ACT_CNR_PCLK
#endif

#define D_IM_CNR_OFF_LINE				(0)				// Off Line Mode
#define D_IM_CNR_ON_THE_FLY				(1)				// On The Fly mode

#define D_IM_CNR_SYNC					(0)				// Sync Processing
#define D_IM_CNR_ASYNC					(1)				// Async Processing
#define D_IM_CNR_SRAM_WAIT_USEC			(1)

#define D_IM_CNR_OFL_0_WAIT_FLGPTN		(D_IM_CNR_FLG_0_OFL_SPR_END | D_IM_CNR_FLG_0_OFL_SPR_AXI_ERR)
#define D_IM_CNR_OFL_1_WAIT_FLGPTN		(D_IM_CNR_FLG_1_OFL_SPR_END | D_IM_CNR_FLG_1_OFL_SPR_AXI_ERR)
#define D_IM_CNR_OTF_0_WAIT_FLGPTN		(D_IM_CNR_FLG_0_OTF_SPR_END | D_IM_CNR_FLG_0_OTF_SPR_AXI_ERR | D_IM_CNR_FLG_0_OTF_SPR_DRT_ERR)
#define D_IM_CNR_OTF_1_WAIT_FLGPTN		(D_IM_CNR_FLG_1_OTF_SPR_END | D_IM_CNR_FLG_1_OTF_SPR_AXI_ERR | D_IM_CNR_FLG_1_OTF_SPR_DRT_ERR)


#define Im_CNR_Dsb()	Dd_ARM_Dsb_Pou()

#define	IO_CNR(ch)		((D_IM_CNR_CH_0 == ((ch))) ? &IO_CNR1 : (D_IM_CNR_CH_1 == ((ch))) ? &IO_CNR2 : &IO_CNR3)

#define	Im_CNR_OFL_Enable(ch)			IO_CNR(ch)->OFL_REG_RW.SPRTRG.bit.SPRTRG = 1;
#define	Im_CNR_OFL_Disable(ch)			IO_CNR(ch)->OFL_REG_RW.SPRTRG.bit.SPRTRG = 0;
#define	Im_CNR_OFL_Softreset(ch)		IO_CNR(ch)->OFL_REG_RW.SPRSR.bit.SR = 1;
#define	Im_CNR_OTF_Enable(ch)			IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.SPRTRG = 1;
#define	Im_CNR_OTF_Disable(ch)			IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.SPRTRG = 0;
#define	Im_CNR_OTF_Softreset(ch)		IO_CNR(ch)->OTF_REG_RW.SPRSR.bit.SR = 1;

#define im_cnr_wait_usec( usec )		Dd_ARM_Wait_ns( (usec * 1000) )

#ifdef CO_CNR_REG_TYPE_CHECK
#define im_cnr_check_reg_type( dst, src )	(dst) = (src);
#else
#define im_cnr_check_reg_type( dst, src )
#endif

#define im_cnr_set_reg_signed( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_cnr_check_reg_type( work, (reg) ); \
		}

#define	D_IM_CNR_SEM_TIMEOUT_ERR		(D_IM_CNR | D_DDIM_SEM_TIMEOUT)			/**< Time Out                 (0x14000011) */
#define	D_IM_CNR_NG						(D_IM_CNR | D_DDIM_SYSTEM_ERROR)		/**< Processing NG            (0x14000099) */
#define D_IM_CNR_SEM_NG					(D_IM_CNR | D_DDIM_SEM_NG)				/**< Semaphore acquisition NG (0x14000010) */
#define D_IM_CNR_INPUT_PARAM_ERROR		(D_IM_CNR | D_DDIM_INPUT_PARAM_ERROR)	/**< parameter error.         (0x14000001) */
#define	D_IM_CNR_AXI_ERR				(D_IM_CNR | 0x100)						/**< AXI bus error.           (0x14000100) */
#define	D_IM_CNR_DRT_ERR				(D_IM_CNR | 0x200)						/**< DRT error.               (0x14000200) */

#define D_IM_CNR_FLG_0_OFL_SPR_END		(0x00000001)	/**< Suppre end flag ch 0 Off Line			*/
#define D_IM_CNR_FLG_1_OFL_SPR_END		(0x00000002)	/**< Suppre end flag ch 1 Off Line			*/
#define D_IM_CNR_FLG_0_OTF_SPR_END		(0x00000004)	/**< Suppre end flag ch 0 On The Fly		*/
#define D_IM_CNR_FLG_1_OTF_SPR_END		(0x00000008)	/**< Suppre end flag ch 1 On The Fly		*/
#define D_IM_CNR_FLG_0_OFL_SPR_AXI_ERR	(0x00000010)	/**< Suppre AXI error flag ch 0 Off Line	*/
#define D_IM_CNR_FLG_1_OFL_SPR_AXI_ERR	(0x00000020)	/**< Suppre AXI error flag ch 1 Off Line	*/
#define D_IM_CNR_FLG_0_OTF_SPR_AXI_ERR	(0x00000040)	/**< Suppre AXI error flag ch 0 On The Fly	*/
#define D_IM_CNR_FLG_1_OTF_SPR_AXI_ERR	(0x00000080)	/**< Suppre AXI error flag ch 1 On The Fly	*/
#define D_IM_CNR_FLG_0_OTF_SPR_DRT_ERR	(0x00000400)	/**< Suppre DRT error flag ch 0 On The Fly	*/
#define D_IM_CNR_FLG_1_OTF_SPR_DRT_ERR	(0x00000800)	/**< Suppre DRT error flag ch 1 On The Fly	*/


#define D_IM_CNR_CH_0					(0)				/**< CNR Channel 0						*/
#define D_IM_CNR_CH_1					(1)				/**< CNR Channel 1						*/
#define D_IM_CNR_CH_2					(2)				/**< CNR Channel 0/1 Simultaneous write	*/
#define D_IM_CNR_CH_READ_NUM_MAX		(2)				/**< Read Channel Max Number			*/
#define D_IM_CNR_CH_NUM_MAX				(3)				/**< Channel Max Number					*/

#define D_IM_CNR_MODE_OFL				(0)				/**< CNR Off Line mode		*/
#define D_IM_CNR_MODE_OTF				(1)				/**< CNR On The Fly mode	*/

#define D_IM_CNR_ADDR_BANK_MAX			(4)				/**< Maximum output bank index number of WCTA */
#define ADDR_BNK_LIMIT(pos, total) ((pos < total) ? pos : 0)

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------


/** SPR YUV mode(OFL)
*/
typedef enum {
	ImCnr_OFL_YCC_MODE_YCC444_PLANE = 0,		/**< YCC444 planar									*/
	ImCnr_OFL_YCC_MODE_YCC422_SIMPLE,		/**< YCC422 Y packed CbCr simple D_SPR_MODE_C only	*/
	ImCnr_OFL_YCC_MODE_YCC422,				/**< YCC422 Y packed CbCr							*/
	ImCnr_OFL_YCC_MODE_YCC420_SIMPLE,		/**< YCC420 Y packed CbCr simple D_SPR_MODE_C only	*/
	ImCnr_OFL_YCC_MODE_YCC420				/**< YCC420 Y packed CbCr							*/
} ImCnrOflYccMode;

/** SPR YUV mode(OTF)
*/
typedef enum {
	ImCnr_OTF_YCC_MODE_YCC422_SIMPLE = 1,	/**< YCC422 Y packed CbCr simple D_SPR_MODE_C only	*/
	ImCnr_OTF_YCC_MODE_YCC420_SIMPLE = 3,	/**< YCC420 Y packed CbCr simple D_SPR_MODE_C only	*/
} ImCnrOtfYccMode;

/** SPR vertical process type(normal / devide)
*/
typedef enum {
	ImCnr_VPROCESS_NORM = 0,		/**< Normal	*/
	ImCnr_VPROCESS_DIV			/**< devide	*/
} ImCnrVprocess;

/** SPR horizontal process type(normal / devide)
*/
typedef enum {
	ImCnr_HPROCESS_NORM = 0,		/**< Normal	*/
	ImCnr_HPROCESS_DIV			/**< devide	*/
} ImCnrHprocess;

/** SPR level
*/
typedef enum {
	ImCnr_LEVEL_HIGH = 0,		/**< SPR level high (default)	*/
	ImCnr_LEVEL_MID,				/**< SPR level middle			*/
	ImCnr_LEVEL_LOW				/**< SPR level low				*/
} ImCnrLevel;

/** SPR threshold type
*/
typedef enum {
	ImCnr_THRES_REGISTER = 0,	/**< SPR threshold type register	*/
	ImCnr_THRES_DYNAMIC			/**< SPR threshold type dynamic		*/
} ImCnrThreshold;

/** SPR Whitening base
*/
typedef enum {
	ImCnr_WHITEN_BASE_LOW = 0,		/**< SPR low	*/
	ImCnr_WHITEN_BASE_MIDDLE,		/**< SPR middle	*/
	ImCnr_WHITEN_BASE_HIGH			/**< SPR high	*/
} ImCnrWhitenBase;

/** SPR C Blend mode
*/
typedef enum {
	ImCnr_C_BLEND_MD_FIX = 0,		/**< Fixed value blend				*/
	ImCnr_C_BLEND_MD_COL_DIFF_EDGE,	/**< Color difference edge blend	*/
	ImCnr_C_BLEND_MD_HUE_SPEC,		/**< Hue specified blend			*/
} ImCnrBlendMd;

/** SPR C range mode
*/
typedef enum {
	ImCnr_C_RANGE_MODE_0_1 = 0,		/**< SPR 0-1	*/
	ImCnr_C_RANGE_MODE_0_2,			/**< SPR 0-2	*/
	ImCnr_C_RANGE_MODE_0_4,			/**< SPR 0-4	*/
	ImCnr_C_RANGE_MODE_0_8,			/**< SPR 0-8	*/
	ImCnr_C_RANGE_MODE_0_16,			/**< SPR 0-16	*/
	ImCnr_C_RANGE_MODE_0_32,			/**< SPR 0-32	*/
	ImCnr_C_RANGE_MODE_0_64,			/**< SPR 0-64	*/
} ImCnrCRangeMode;

/** SPR enable / disable
*/
typedef enum {
	ImCnr_ONOFF_DISABLE = 0,		/**< SPR disable	*/
	ImCnr_ONOFF_ENABLE			/**< SPR enable		*/
} ImCnrOnoff;

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------

typedef VOID (*T_IM_CNR_CALLBACK)( UCHAR ch, ULONG interrupt_flag_mask, UINT32 user_param );	/**< Callback function pointer	*/

static volatile T_IM_CNR_CALLBACK	gIM_CNR_OFL_CallBack_Func[D_IM_CNR_CH_READ_NUM_MAX] = {NULL, NULL};
static volatile T_IM_CNR_CALLBACK	gIM_CNR_OTF_CallBack_Func[D_IM_CNR_CH_READ_NUM_MAX] = {NULL, NULL};
static volatile UINT32 gIM_CNR_OFL_UserParam[D_IM_CNR_CH_READ_NUM_MAX] = {0, 0};
static volatile UINT32 gIM_CNR_OTF_UserParam[D_IM_CNR_CH_READ_NUM_MAX] = {0, 0};
static UCHAR gim_cnr_mode[2] = { D_IM_CNR_MODE_OFL, D_IM_CNR_MODE_OFL };


/** SPR Control info for common
*/
/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
// Output address management information
typedef struct {
	UCHAR	use_bank_num;							// Output bank number
	UCHAR	bank_area;								// Target bank number
	ULONG	output_addr[D_IM_CNR_ADDR_BANK_MAX];	// Output bank address information.
} T_IM_CNR_OUTPUT_MNG;

// Output latest management information
typedef struct {
	UCHAR	bank_area;								// Latest bank number
	ULONG	addr;									// Latest Output address.
} T_IM_CNR_LATEST_MNG;

// Output address parameter
static volatile T_IM_CNR_OUTPUT_MNG gIM_CNR_Output_Mng[D_IM_CNR_CH_READ_NUM_MAX];
// Output address parameter
static volatile T_IM_CNR_LATEST_MNG gIM_CNR_Latest_Mng[D_IM_CNR_CH_READ_NUM_MAX];


typedef struct _ImCnr 							ImCnr;
typedef struct _ImCnrClass 				ImCnrClass;
typedef struct _ImCnrPrivate 				ImCnrPrivate;

struct _ImCnr{
	GObject parent;
};

struct _ImCnrClass{
	GObjectClass parentclass;
};

typedef struct _ImCnroneOflCtrl{
	ImCnrOflYccMode	mode;		/**< SPR YCC mode	@@YUV_MODE	<br>
														 <ul><li>@ref ImCnr_OFL_YCC_MODE_YCC444_PLANE
															 <li>@ref ImCnr_OFL_YCC_MODE_YCC422_SIMPLE
															 <li>@ref ImCnr_OFL_YCC_MODE_YCC422
															 <li>@ref ImCnr_OFL_YCC_MODE_YCC420_SIMPLE
															 <li>@ref ImCnr_OFL_YCC_MODE_YCC420</ul>		*/

	USHORT				width;		/**< SPR valid data width [64 ~ 16384(aligned on 16pixel)]		@@HSIZE	*/
	USHORT				lines;		/**< SPR valid data lines [64 ~ 16384(aligned on 16pixel)]		@@VSIZE	*/

	ULONG				r_y_width;	/**< Y width for read (aligned on 16byte)			@@RYDEF	*/
	ULONG				r_y_addr;	/**< Y address for read (aligned on 16byte)			@@RYTA	*/

	ULONG				r_c_width;	/**< CbCr width for read (aligned on 16byte)		@@RCDEF	*/
	ULONG				r_cb_addr;	/**< Cb address for read (aligned on 16byte)		@@RCBTA	*/
	ULONG				r_cr_addr;	/**< Cr address for read (aligned on 16byte)		@@RCRTA	*/

	ULONG				w_y_width;	/**< Y width for write (aligned on 16byte)			@@WYDEF	*/
	ULONG				w_y_addr;	/**< Y address for write (aligned on 16byte)		@@WYTA	*/

	ULONG				w_c_width;	/**< CbCr width for write (aligned on 16byte)		@@WCDEF	*/
	ULONG				w_cb_addr;	/**< Cb address for write (aligned on 16byte)		@@WCBTA	*/
	ULONG				w_cr_addr;	/**< Cr address for write (aligned on 16byte)		@@WCRTA	*/

	ULONG				work_addr;	/**< Address fir work area[288 * VSIZE]		@@TMPTA	*/

	ImCnrVprocess	divide_top;	/**< Virtucal process devide	@@VDIVT	<br>
														 <ul><li>@ref ImCnr_VPROCESS_NORM
															 <li>@ref ImCnr_VPROCESS_DIV</ul>	*/
	ImCnrVprocess	divide_bot;	/**< Virtucal process devide	@@VDIVB	<br>
														 <ul><li>@ref ImCnr_VPROCESS_NORM
															 <li>@ref ImCnr_VPROCESS_DIV</ul>	*/

	T_IM_CNR_CALLBACK	pCallBack;	/**< callback function	*/
	UINT32				user_param;		/**< This set value will return to callback argument value when interrupt occurs.	*/
} ImCnrOflCtrl;

/** SPR Control info for common
*/
typedef struct _ImCnrOtfCtrl{
	ImCnrOtfYccMode	mode;		/**< SPR YCC mode	@@YUV_MODE	<br>
														 <ul><li>@ref ImCnr_OTF_YCC_MODE_YCC422_SIMPLE
															 <li>@ref ImCnr_OTF_YCC_MODE_YCC420_SIMPLE</ul>		*/

	UCHAR				extra_mode;		/**< extra_mode @@EXMODE */
	UCHAR				video_format;	/**< video_format @@CNRVFM */
	USHORT				width;			/**< SPR valid data width [64 ~ 16384(aligned on 16pixel)]		@@HSIZE	*/
	USHORT				lines;			/**< SPR valid data lines [64 ~ 16384(aligned on 16pixel)]		@@VSIZE	*/

	ULONG				w_c_width;		/**< CbCr width for write (aligned on 16byte)		@@WCDEF	*/

	ULONG				w_offset_x;		/**< write offset work X direction (aligned on 2byte)		@@CNRWOFSX	*/

	ImCnrHprocess	divide_left;	/**< Virtucal process devide	@@HDIVL	<br>
														 <ul><li>@ref ImCnr_HPROCESS_NORM
															 <li>@ref ImCnr_HPROCESS_DIV</ul>	*/
	ImCnrHprocess	divide_right;	/**< Virtucal process devide	@@HDIVR	<br>
														 <ul><li>@ref ImCnr_HPROCESS_NORM
															 <li>@ref ImCnr_HPROCESS_DIV</ul>	*/
	ImCnrOnoff		continuous;		/**< Continuous processing enable @@CNRCSE <br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	T_IM_CNR_CALLBACK	pCallBack;		/**< callback function	*/
	UINT32				user_param;		/**< This set value will return to callback argument value when interrupt occurs.	*/
} ImCnrOtfCtrl;

/** im_cnrone_otf_set_outaddr_info() parameter structure */
typedef struct _ImCnrOtfOutaddrInfo{
	UCHAR				use_bank_num;						/**< CbCr address bank number @@WCTA
																	Use only one bank in the setting of 1 (d),
																	and use of the four banks in the setting of 4 (d).	*/
	ULONG				w_c_addr[D_IM_CNR_ADDR_BANK_MAX];	/**< CbCr address for write (aligned on 2bytes)		@@WCTA	*/
} ImCnrOtfOutaddrInfo;

/** im_cnrone_ofl_ctrl_Axi() parameter structure */
typedef struct _ImCnrOflAxi{
	UINT32	read_cache_type;			/**< Read Cache type. */
	UINT32	read_protection_type;		/**< Read Protection type. */
	UINT32	write_cache_type;			/**< Write Cache type. */
	UINT32	write_protection_type;		/**< Write Protection type. */
} ImCnrOflAxi;

/** im_cnrone_ofl_get_axi_status() parameter structure */
typedef struct _ImCnrOflAxiStatus{
	UCHAR	read_channel_response;	/**< RRESP register */
	UCHAR	write_channel_response;	/**< WRESP register */
} ImCnrOflAxiStatus;

/** im_cnrone_otf_ctrl_axi() parameter structure */
typedef struct _ImCnrOtfAxi{
	UINT32	write_cache_type;			/**< Write Cache type. */
	UINT32	write_protection_type;		/**< Write Protection type. */
} ImCnrOtfAxi;

/** im_cnrone_otf_get_axi_status() parameter structure */
typedef struct _ImCnrOtfAxiStatus{
	UCHAR	write_channel_response;	/**< WRESP register */
} ImCnrOtfAxiStatus;

/** SPR Control info for Low/Middle frequency CbCr
*/
typedef struct _ImCnrCtrlCMcLc{
	ImCnrOnoff			enable;				/**< Low/Middle CbCr SPR enable @@MCEN, @@LCEN	<br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	UCHAR					h_y_threshold[4];	/**< Low/Middle SPR Y threshold for horizontal		@@MCYTHH, @@LCYTHH	*/
	UCHAR					v_y_threshold[4];	/**< Low/Middle SPR Y threshold for vertical		@@MCYTHV, @@LCYTHV	*/
	UCHAR					h_c_threshold[4];	/**< Low/Middle SPR CbCr threshold for horizontal	@@MCCTHH, @@LCCTHH	*/
	UCHAR					v_c_threshold[4];	/**< Low/Middle SPR CbCr threshold for vertical	@@MCCTHV, @@LCCTHV	*/
	UCHAR					y_threshold_cor;	/**< Low/Middle SPR Y threshold coring	@@MCYDYMYCR, @@LCYDYMYCR	*/
	USHORT					y_threshold_gain;	/**< Low/Middle SPR Y threshold gain (9bit)	@@MCYDYMYG, @@LCYDYMYG	<br>
													value range: [0 - 511(=0/256 - 511/256)]	*/
	ImCnrOnoff			y_threshold_dym_en;	/**< Low/Middle Y threshold dynamic setting enable @@MCYDYM, @@LCYDYM <br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	ImCnrOnoff			y_threshold_scl_en;	/**< Low/Middle Y threshold scale enable @@MCYSCL, @@LCYSCL <br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	ImCnrOnoff			c_y_threshold_scl_en;	/**< Low/Middle CbCr threshold Y scale enable @@MCSSCL, @@LCSSCL <br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	ImCnrOnoff			c_threshold_scl_en;	/**< Low/Middle CbCr threshold scale enable @@MCCSCL, @@LCCSCL <br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
} ImCnrCtrlCMcLc;

/** SPR Control info for CbCr
*/
typedef struct _ImCnrCtrlC{
	ImCnrOnoff			enable;				/**< CbCr SPR enable @@CSPREN	<br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	ImCnrOnoff			gradation_keep_en;	/**< gradation keep enable @@CGDKEN <br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	ImCnrCtrlCMcLc	mid_freq_nr;		/**< Middle range frequency Color NR parmeters */
	ImCnrCtrlCMcLc	low_freq_nr;		/**< Low range frequency Color NR parmeters */
	ImCnrOnoff			whitening_enable;	/**< Whitening enable @@WHTEN <br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	USHORT					whitening_value;	/**< Whitening value[0~31]			@@WHTVAL	*/
	ImCnrWhitenBase	whitening_base;		/**< Whitening base @@WHTBASE <br>
														 <ul><li>@ref ImCnr_WHITEN_BASE_LOW
															 <li>@ref ImCnr_WHITEN_BASE_MIDDLE
															 <li>@ref ImCnr_WHITEN_BASE_HIGH</ul>	*/
	ImCnrBlendMd		c_blend_md;			/**< Blend mode @@BLENDMD <br>
														 <ul><li>@ref ImCnr_C_BLEND_MD_FIX
															 <li>@ref ImCnr_C_BLEND_MD_COL_DIFF_EDGE
															 <li>@ref ImCnr_C_BLEND_MD_HUE_SPEC</ul>	*/
	USHORT					c_alpha_blend;		/**< Alpha blend value[0~31] @@CSPRALPBD */
	ImCnrOnoff			c_range;			/**< C range enable @@CSRGEN <br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	ImCnrCRangeMode	c_range_mode;		/**< C range mode @@CSRGMD <br>
														 <ul><li>@ref ImCnr_C_RANGE_MODE_0_1
															 <li>@ref ImCnr_C_RANGE_MODE_0_2
															 <li>@ref ImCnr_C_RANGE_MODE_0_4
															 <li>@ref ImCnr_C_RANGE_MODE_0_8
															 <li>@ref ImCnr_C_RANGE_MODE_0_16
															 <li>@ref ImCnr_C_RANGE_MODE_0_32
															 <li>@ref ImCnr_C_RANGE_MODE_0_64</ul>	*/
} ImCnrCtrlC;

/** SPR Control info for Y
*/
typedef struct _ImCnrOflCtrlY{
	ImCnrOnoff		enable;				/**< Y SPR enable @@YSPREN	<br>
														 <ul><li>@ref ImCnr_ONOFF_DISABLE
															 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	ImCnrThreshold	threshold_type;		/**< threshold type			@@YSPRMODE YSPRMD	<br>
														 <ul><li>@ref ImCnr_THRES_REGISTER
															 <li>@ref ImCnr_THRES_DYNAMIC</ul>	*/
	ImCnrLevel		level;				/**< SPR filter level		@@YSPRMODE YSPRFE	<br>
														 <ul><li>@ref ImCnr_LEVEL_HIGH
															 <li>@ref ImCnr_LEVEL_MID
															 <li>@ref ImCnr_LEVEL_LOW</ul>	*/
	UCHAR				h_y_threshold;		/**< SPR Y threshold for horizontal		@@YSPRFXEYH	*/
	UCHAR				v_y_threshold;		/**< SPR Y threshold for vertical		@@YSPRFXEYV	*/
	UCHAR				h_c_threshold;		/**< SPR CbCr threshold for horizontal	@@YSPRFXECH	*/
	UCHAR				v_c_threshold;		/**< SPR CbCr threshold for vertical	@@YSPRFXECV	*/
	UCHAR				alpha_blend_ratio;	/**< Alpha blend ratio[0~31]			@@YSPRALPBD	*/
} ImCnrOflCtrlY;

/** SPR YSPRDYEY/MCYSCL/MCCSCL/MCSSCL/LCYSCL/LCCSCL/LCSSCL/CESCL table
*/
typedef struct _ImCnrTable{
	UCHAR	bd1;	/**< Boundary1	@@YSPRDYEYBD_1, @@MCYSCLBD_1, @@MCCSCLBD_1, @@MCSSCLBD_1, @@LCYSCLBD_1, @@LCCSCLBD_1, @@LCSSCLBD_1, @@CESCLBD_1 */
	UCHAR	bd2;	/**< Boundary2	@@YSPRDYEYBD_2, @@MCYSCLBD_2, @@MCCSCLBD_2, @@MCSSCLBD_2, @@LCYSCLBD_2, @@LCCSCLBD_2, @@LCSSCLBD_2, @@CESCLBD_2 */
	UCHAR	bd3;	/**< Boundary3	@@YSPRDYEYBD_3, @@MCYSCLBD_3, @@MCCSCLBD_3, @@MCSSCLBD_3, @@LCYSCLBD_3, @@LCCSCLBD_3, @@LCSSCLBD_3, @@CESCLBD_3 */
	UCHAR	bd4;	/**< Boundary4	@@YSPRDYEYBD_4, @@MCYSCLBD_4, @@MCCSCLBD_4, @@MCSSCLBD_4, @@LCYSCLBD_4, @@LCCSCLBD_4, @@LCSSCLBD_4, @@CESCLBD_4 */
	UCHAR	bd5;	/**< Boundary5	@@YSPRDYEYBD_5, @@MCYSCLBD_5, @@MCCSCLBD_5, @@MCSSCLBD_5, @@LCYSCLBD_5, @@LCCSCLBD_5, @@LCSSCLBD_5, @@CESCLBD_5 */
	UCHAR	of0;	/**< Offset0	@@YSPRDYEYOF_0, @@MCYSCLOF_0, @@MCCSCLOF_0, @@MCSSCLOF_0, @@LCYSCLOF_0, @@LCCSCLOF_0, @@LCSSCLOF_0, @@CESCLOF_0 */
	UCHAR	of1;	/**< Offset1	@@YSPRDYEYOF_1, @@MCYSCLOF_1, @@MCCSCLOF_1, @@MCSSCLOF_1, @@LCYSCLOF_1, @@LCCSCLOF_1, @@LCSSCLOF_1, @@CESCLOF_1 */
	UCHAR	of2;	/**< Offset2	@@YSPRDYEYOF_2, @@MCYSCLOF_2, @@MCCSCLOF_2, @@MCSSCLOF_2, @@LCYSCLOF_2, @@LCCSCLOF_2, @@LCSSCLOF_2, @@CESCLOF_2 */
	UCHAR	of3;	/**< Offset3	@@YSPRDYEYOF_3, @@MCYSCLOF_3, @@MCCSCLOF_3, @@MCSSCLOF_3, @@LCYSCLOF_3, @@LCCSCLOF_3, @@LCSSCLOF_3, @@CESCLOF_3 */
	UCHAR	of4;	/**< Offset4	@@YSPRDYEYOF_4, @@MCYSCLOF_4, @@MCCSCLOF_4, @@MCSSCLOF_4, @@LCYSCLOF_4, @@LCCSCLOF_4, @@LCSSCLOF_4, @@CESCLOF_4 */
	UCHAR	of5;	/**< Offset5	@@YSPRDYEYOF_5, @@MCYSCLOF_5, @@MCCSCLOF_5, @@MCSSCLOF_5, @@LCYSCLOF_5, @@LCCSCLOF_5, @@LCSSCLOF_5, @@CESCLOF_5 */
	INT8	gain0;	/**< Gain0 (8bits signed)	@@YSPRDYEYGA_0, @@MCYSCLGA_0, @@MCCSCLGA_0, @@MCSSCLGA_0, @@LCYSCLGA_0, @@LCCSCLGA_0, @@LCSSCLGA_0, @@CESCLGA_0 <br>
						value range: [-128 - 127(=-128/16 - 127/16)]	*/
	INT8	gain1;	/**< Gain1 (8bits signed)	@@YSPRDYEYGA_1, @@MCYSCLGA_1, @@MCCSCLGA_1, @@MCSSCLGA_1, @@LCYSCLGA_1, @@LCCSCLGA_1, @@LCSSCLGA_1, @@CESCLGA_1 <br>
						value range: [-128 - 127(=-128/16 - 127/16)]	*/
	INT8	gain2;	/**< Gain2 (8bits signed)	@@YSPRDYEYGA_2, @@MCYSCLGA_2, @@MCCSCLGA_2, @@MCSSCLGA_2, @@LCYSCLGA_2, @@LCCSCLGA_2, @@LCSSCLGA_2, @@CESCLGA_2 <br>
						value range: [-128 - 127(=-128/16 - 127/16)]	*/
	INT8	gain3;	/**< Gain3 (8bits signed)	@@YSPRDYEYGA_3, @@MCYSCLGA_3, @@MCCSCLGA_3, @@MCSSCLGA_3, @@LCYSCLGA_3, @@LCCSCLGA_3, @@LCSSCLGA_3, @@CESCLGA_3 <br>
						value range: [-128 - 127(=-128/16 - 127/16)]	*/
	INT8	gain4;	/**< Gain4 (8bits signed)	@@YSPRDYEYGA_4, @@MCYSCLGA_4, @@MCCSCLGA_4, @@MCSSCLGA_4, @@LCYSCLGA_4, @@LCCSCLGA_4, @@LCSSCLGA_4, @@CESCLGA_4 <br>
						value range: [-128 - 127(=-128/16 - 127/16)]	*/
	INT8	gain5;	/**< Gain5 (8bits signed)	@@YSPRDYEYGA_5, @@MCYSCLGA_5, @@MCCSCLGA_5, @@MCSSCLGA_5, @@LCYSCLGA_5, @@LCCSCLGA_5, @@LCSSCLGA_5, @@CESCLGA_5 <br>
						value range: [-128 - 127(=-128/16 - 127/16)]	*/
} ImCnrTable;

/** SPR SPRSCB/SPRSCR/SPRDCR/SPRDCR table
*/
typedef struct _ImCnrCcTableSrcDst{
	INT8	bd1;	/**< Boundary1	@@SPRSCBBD_1, @@SPRSCRBD_1, @@SPRDCBBD_1, @@SPRDCRBD_1 */
	INT8	bd2;	/**< Boundary2	@@SPRSCBBD_2, @@SPRSCRBD_2, @@SPRDCBBD_2, @@SPRDCRBD_2 */
	INT8	bd3;	/**< Boundary3	@@SPRSCBBD_3, @@SPRSCRBD_3, @@SPRDCBBD_3, @@SPRDCRBD_3 */
	INT8	bd4;	/**< Boundary4	@@SPRSCBBD_4, @@SPRSCRBD_4, @@SPRDCBBD_4, @@SPRDCRBD_4 */
	INT8	bd5;	/**< Boundary5	@@SPRSCBBD_5, @@SPRSCRBD_5, @@SPRDCBBD_5, @@SPRDCRBD_5 */
	INT8	of0;	/**< Offset0	@@SPRSCBOF_0, @@SPRSCROF_0, @@SPRDCBOF_0, @@SPRDCROF_0 */
	INT8	of1;	/**< Offset1	@@SPRSCBOF_1, @@SPRSCROF_1, @@SPRDCBOF_1, @@SPRDCROF_1 */
	INT8	of2;	/**< Offset2	@@SPRSCBOF_2, @@SPRSCROF_2, @@SPRDCBOF_2, @@SPRDCROF_2 */
	INT8	of3;	/**< Offset3	@@SPRSCBOF_3, @@SPRSCROF_3, @@SPRDCBOF_3, @@SPRDCROF_3 */
	INT8	of4;	/**< Offset4	@@SPRSCBOF_4, @@SPRSCROF_4, @@SPRDCBOF_4, @@SPRDCROF_4 */
	INT8	of5;	/**< Offset5	@@SPRSCBOF_5, @@SPRSCROF_5, @@SPRDCBOF_5, @@SPRDCROF_5 */
	SHORT	gain0;	/**< Gain0 (12bits signed)	@@SPRSCBGA_0, @@SPRSCRGA_0, @@SPRDCBGA_0, @@SPRDCRGA_0<br>
						value range: [-2048 - 2047(=-2048/256 - 2047/256)]	*/
	SHORT	gain1;	/**< Gain1 (12bits signed)	@@SPRSCBGA_1, @@SPRSCRGA_1, @@SPRDCBGA_1, @@SPRDCRGA_1<br>
						value range: [-2048 - 2047(=-2048/256 - 2047/256)]	*/
	SHORT	gain2;	/**< Gain2 (12bits signed)	@@SPRSCBGA_2, @@SPRSCRGA_2, @@SPRDCBGA_2, @@SPRDCRGA_2<br>
						value range: [-2048 - 2047(=-2048/256 - 2047/256)]	*/
	SHORT	gain3;	/**< Gain3 (12bits signed)	@@SPRSCBGA_3, @@SPRSCRGA_3, @@SPRDCBGA_3, @@SPRDCRGA_3<br>
						value range: [-2048 - 2047(=-2048/256 - 2047/256)]	*/
	SHORT	gain4;	/**< Gain4 (12bits signed)	@@SPRSCBGA_4, @@SPRSCRGA_4, @@SPRDCBGA_4, @@SPRDCRGA_4<br>
						value range: [-2048 - 2047(=-2048/256 - 2047/256)]	*/
	SHORT	gain5;	/**< Gain5 (12bits signed)	@@SPRSCBGA_5, @@SPRSCRGA_5, @@SPRDCBGA_5, @@SPRDCRGA_5<br>
						value range: [-2048 - 2047(=-2048/256 - 2047/256)]	*/
} ImCnrCcTableSrcDst;

/** SPR CPHPT/CPHPTK/CDSCLOF/CDSCLGA/CDSCLBD table
*/
typedef struct _ImCnrHueSpecTable{
	INT8	cd_cb;	/**< Origin coordinate for Cb	@@CDCB */
	INT8	cd_cr;	/**< Origin coordinate for Cr	@@CDCR */
	USHORT	k_cb;	/**< Origin coordinate coefficient	@@KCB */
	USHORT	k_cr;	/**< Origin coordinate coefficient	@@KCR */
	USHORT	bd1;	/**< Boundary1	@@CDSCLBD_1 */
	USHORT	bd2;	/**< Boundary2	@@CDSCLBD_2 */
	USHORT	bd3;	/**< Boundary3	@@CDSCLBD_3 */
	USHORT	bd4;	/**< Boundary4	@@CDSCLBD_4 */
	USHORT	bd5;	/**< Boundary5	@@CDSCLBD_5 */
	USHORT	of0;	/**< Offset0	@@CDSCLOF_0 */
	USHORT	of1;	/**< Offset1	@@CDSCLOF_1 */
	USHORT	of2;	/**< Offset2	@@CDSCLOF_2 */
	USHORT	of3;	/**< Offset3	@@CDSCLOF_3 */
	USHORT	of4;	/**< Offset4	@@CDSCLOF_4 */
	USHORT	of5;	/**< Offset5	@@CDSCLOF_5 */
	SHORT	gain0;	/**< Gain0 (10bits signed)	@@CDSCLGA_0<br>
						value range: [-64 - 63(=-1024/16 - 1023/16)]	*/
	SHORT	gain1;	/**< Gain1 (10bits signed)	@@CDSCLGA_1<br>
						value range: [-64 - 63(=-1024/16 - 1023/16)]	*/
	SHORT	gain2;	/**< Gain2 (10bits signed)	@@CDSCLGA_2<br>
						value range: [-64 - 63(=-1024/16 - 1023/16)]	*/
	SHORT	gain3;	/**< Gain3 (10bits signed)	@@CDSCLGA_3<br>
						value range: [-64 - 63(=-1024/16 - 1023/16)]	*/
	SHORT	gain4;	/**< Gain4 (10bits signed)	@@CDSCLGA_4<br>
						value range: [-64 - 63(=-1024/16 - 1023/16)]	*/
	SHORT	gain5;	/**< Gain5 (10bits signed)	@@CDSCLGA_5<br>
						value range: [-64 - 63(=-1024/16 - 1023/16)]	*/
} ImCnrHueSpecTable;

/** SPR Control info for adjustment of Source/Destination CbCr
*/
typedef struct _ImCnrCtrlCcSrcDst{
	ImCnrOnoff					enable;		/**< Source/Destination CbCr adjustment enable @@SPRS, @@SPRD	<br>
													 <ul><li>@ref ImCnr_ONOFF_DISABLE
														 <li>@ref ImCnr_ONOFF_ENABLE</ul>	*/
	ImCnrCcTableSrcDst		cb_table;	/**< Source/Destination Cb adjustment table	*/
	ImCnrCcTableSrcDst		cr_table;	/**< Source/Destination Cr adjustment table	*/
} ImCnrCtrlCcSrcDst;

/* @} */	// im_cnr

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
/** Ctrl_C Table (OTF/OFL)
address
*/
typedef struct _ImCnrRdmaAddrCtrlC{
	//						OTF							OFL
	ULONG	CSPREN;			/**< 2842_(1000 - 1003h),	2842_(3000 - 3003h) */
	ULONG	CGDKEN;			/**< 2842_(1008 - 100Bh),	2842_(3008 - 300Bh) */
	ULONG	MCEN;			/**< 2842_(1020 - 1023h),	2842_(3020 - 3023h) */
	ULONG	MCYTHH;			/**< 2842_(1024 - 1027h),	2842_(3024 - 3027h) */
	ULONG	MCYTHV;			/**< 2842_(1028 - 102Bh),	2842_(3028 - 302Bh) */
	ULONG	MCCTHH;			/**< 2842_(102C - 102Fh),	2842_(302C - 302Fh) */
	ULONG	MCCTHV;			/**< 2842_(1030 - 1033h),	2842_(3030 - 3033h) */
	ULONG	MCYDYM;			/**< 2842_(1034 - 1037h),	2842_(3034 - 3037h) */
	ULONG	MCYDYMDT;		/**< 2842_(1038 - 103Bh),	2842_(3038 - 303Bh) */
	ULONG	MCYSCL;			/**< 2842_(1040 - 1043h),	2842_(3040 - 3043h) */
	ULONG	MCCSCL;			/**< 2842_(1060 - 1063h),	2842_(3060 - 3063h) */
	ULONG	MCSSCL;			/**< 2842_(1080 - 1083h),	2842_(3080 - 3083h) */
	ULONG	LCEN;			/**< 2842_(10C0 - 10C3h),	2842_(30C0 - 30C3h) */
	ULONG	LCYTHH;			/**< 2842_(10C4 - 10C7h),	2842_(30C4 - 30C7h) */
	ULONG	LCYTHV;			/**< 2842_(10C8 - 10CBh),	2842_(30C8 - 30CBh) */
	ULONG	LCCTHH;			/**< 2842_(10CC - 10CFh),	2842_(30CC - 30CFh) */
	ULONG	LCCTHV;			/**< 2842_(10D0 - 10D3h),	2842_(30D0 - 30D3h) */
	ULONG	LCYDYM;			/**< 2842_(10D4 - 10D7h),	2842_(30D4 - 30D7h) */
	ULONG	LCYDYMDT;		/**< 2842_(10D8 - 10DBh),	2842_(30D8 - 30DBh) */
	ULONG	LCYSCL;			/**< 2842_(10E0 - 10E3h),	2842_(30E0 - 30E3h) */
	ULONG	LCCSCL;			/**< 2842_(1100 - 1103h),	2842_(3100 - 3103h) */
	ULONG	LCSSCL;			/**< 2842_(1120 - 1123h),	2842_(3120 - 3123h) */
	ULONG	BLEND;			/**< 2842_(1160 - 1163h),	2842_(3160 - 3163h) */
	ULONG	WHTMD;			/**< 2842_(11D0 - 11D3h),	2842_(31D0 - 31D3h) */
} ImCnrRdmaAddrCtrlC;
/** Ctrl_C Table (OTF/OFL)
data
*/
typedef struct _ImCnrRdmaDataCtrlC{
	//												OTF							OFL
	union	io_cnr_cspr_reg_cspren		CSPREN;		/**< 2842_(1000 - 1003h),	2842_(3000 - 3003h) */
	union	io_cnr_cspr_reg_cgdken		CGDKEN;		/**< 2842_(1008 - 100Bh),	2842_(3008 - 300Bh) */
	union	io_cnr_cspr_reg_mcen		MCEN;		/**< 2842_(1020 - 1023h),	2842_(3020 - 3023h) */
	union	io_cnr_cspr_reg_mcythh		MCYTHH;		/**< 2842_(1024 - 1027h),	2842_(3024 - 3027h) */
	union	io_cnr_cspr_reg_mcythv		MCYTHV;		/**< 2842_(1028 - 102Bh),	2842_(3028 - 302Bh) */
	union	io_cnr_cspr_reg_mccthh		MCCTHH;		/**< 2842_(102C - 102Fh),	2842_(302C - 302Fh) */
	union	io_cnr_cspr_reg_mccthv		MCCTHV;		/**< 2842_(1030 - 1033h),	2842_(3030 - 3033h) */
	union	io_cnr_cspr_reg_mcydym		MCYDYM;		/**< 2842_(1034 - 1037h),	2842_(3034 - 3037h) */
	union	io_cnr_cspr_reg_mcydymdt	MCYDYMDT;	/**< 2842_(1038 - 103Bh),	2842_(3038 - 303Bh) */
	union	io_cnr_cspr_reg_mcyscl		MCYSCL;		/**< 2842_(1040 - 1043h),	2842_(3040 - 3043h) */
	union	io_cnr_cspr_reg_mccscl		MCCSCL;		/**< 2842_(1060 - 1063h),	2842_(3060 - 3063h) */
	union	io_cnr_cspr_reg_mcsscl		MCSSCL;		/**< 2842_(1080 - 1083h),	2842_(3080 - 3083h) */
	union	io_cnr_cspr_reg_lcen		LCEN;		/**< 2842_(10C0 - 10C3h),	2842_(30C0 - 30C3h) */
	union	io_cnr_cspr_reg_lcythh		LCYTHH;		/**< 2842_(10C4 - 10C7h),	2842_(30C4 - 30C7h) */
	union	io_cnr_cspr_reg_lcythv		LCYTHV;		/**< 2842_(10C8 - 10CBh),	2842_(30C8 - 30CBh) */
	union	io_cnr_cspr_reg_lccthh		LCCTHH;		/**< 2842_(10CC - 10CFh),	2842_(30CC - 30CFh) */
	union	io_cnr_cspr_reg_lccthv		LCCTHV;		/**< 2842_(10D0 - 10D3h),	2842_(30D0 - 30D3h) */
	union	io_cnr_cspr_reg_lcydym		LCYDYM;		/**< 2842_(10D4 - 10D7h),	2842_(30D4 - 30D7h) */
	union	io_cnr_cspr_reg_lcydymdt	LCYDYMDT;	/**< 2842_(10D8 - 10DBh),	2842_(30D8 - 30DBh) */
	union	io_cnr_cspr_reg_lcyscl		LCYSCL;		/**< 2842_(10E0 - 10E3h),	2842_(30E0 - 30E3h) */
	union	io_cnr_cspr_reg_lccscl		LCCSCL;		/**< 2842_(1100 - 1103h),	2842_(3100 - 3103h) */
	union	io_cnr_cspr_reg_lcsscl		LCSSCL;		/**< 2842_(1120 - 1123h),	2842_(3120 - 3123h) */
	union	io_cnr_cspr_reg_blend 		BLEND;		/**< 2842_(1160 - 1163h),	2842_(3160 - 3163h) */
	union	io_cnr_cspr_reg_whtmd		WHTMD;		/**< 2842_(11D0 - 11D3h),	2842_(31D0 - 31D3h) */
} ImCnrRdmaDataCtrlC;


/** OFL CTRL Y (OFL)
address
*/
typedef struct _ImCnrRdmaAddrOflCtrlY{
	ULONG	YSPREN;			/**< 2842_(4000 - 4003h) */
	ULONG	YSPRMODE;		/**< 2842_(4004 - 4007h) */
	ULONG	YSPRFXEY;		/**< 2842_(4020 - 4023h) */
	ULONG	YSPRFXEC;		/**< 2842_(4024 - 4027h) */
	ULONG	YSPRALPBD;		/**< 2842_(4028 - 402Bh) */
} ImCnrRdmaAddrOflCtrlY;
/** OFL CTRL Y (OFL)
data
*/
typedef struct _ImCnrRdmaDataOflCtrlY{
	union	io_cnr_ofl_reg_yspr_yspren		YSPREN;		/**< 2842_(4000 - 4003h) */
	union	io_cnr_ofl_reg_yspr_ysprmode	YSPRMODE;	/**< 2842_(4004 - 4007h) */
	union	io_cnr_ofl_reg_yspr_ysprfxey	YSPRFXEY;	/**< 2842_(4020 - 4023h) */
	union	io_cnr_ofl_reg_yspr_ysprfxec	YSPRFXEC;	/**< 2842_(4024 - 4027h) */
	union	io_cnr_ofl_reg_yspr_yspralpbd	YSPRALPBD;	/**< 2842_(4028 - 402Bh) */
} ImCnrRdmaDataOflCtrlY;


/** OFL Y YSPR Table (OFL)
address
*/
typedef struct _ImCnrRdmaAddrOflYsprTbl{
	ULONG	YSPRDYEYOF_1;	/**< 2842_(4030 - 4033h) */
	ULONG	YSPRDYEYOF_2;	/**< 2842_(4034 - 4037h) */
	ULONG	YSPRDYEYGA_1;	/**< 2842_(4038 - 403Bh) */
	ULONG	YSPRDYEYGA_2;	/**< 2842_(403C - 403Fh) */
	ULONG	YSPRDYEYBD_1;	/**< 2842_(4040 - 4043h) */
	ULONG	YSPRDYEYBD_2;	/**< 2842_(4044 - 4047h) */
} ImCnrRdmaAddrOflYsprTbl;
/** OFL Y YSPR Table (OFL)
data
*/
typedef struct _ImCnrRdmaDataOflYsprTbl{
	struct	io_cnr_ofl_reg_yspr_ysprdyeyof	YSPRDYEYOF;	/**< 2842_(4030 - 4037h) */
	struct	io_cnr_ofl_reg_yspr_ysprdyeyga	YSPRDYEYGA;	/**< 2842_(4038 - 403Fh) */
	struct	io_cnr_ofl_reg_yspr_ysprdyeybd	YSPRDYEYBD;	/**< 2842_(4040 - 4047h) */
} ImCnrRdmaDataOflYsprTbl;


/** CSPR Middle Y Table (OTF/OFL)
address
*/
typedef struct _ImCnrRdmaAddrCsprMidYTbl{
	//						OTF							OFL
	ULONG	MCYSCLOF_1;		/**< 2842_(1048 - 104Bh),	2842_(3048 - 304Bh) */
	ULONG	MCYSCLOF_2;		/**< 2842_(104C - 104Fh),	2842_(304C - 304Fh) */
	ULONG	MCYSCLGA_1;		/**< 2842_(1050 - 1053h),	2842_(3050 - 3053h) */
	ULONG	MCYSCLGA_2;		/**< 2842_(1054 - 1057h),	2842_(3054 - 3057h) */
	ULONG	MCYSCLBD_1;		/**< 2842_(1058 - 105Bh),	2842_(3058 - 305Bh) */
	ULONG	MCYSCLBD_2;		/**< 2842_(105C - 105Fh),	2842_(305C - 305Fh) */
} ImCnrRdmaAddrCsprMidYTbl;
/** CSPR Middle Y Table (OTF/OFL)
data
*/
typedef struct _ImCnrRdmaDataCsprMidYTbl{
	//											OTF							OFL
	struct io_cnr_cspr_reg_mcysclof	MCYSCLOF;	/**< 2842_(1048 - 104Fh),	2842_(3048 - 304Fh) */
	struct io_cnr_cspr_reg_mcysclga	MCYSCLGA;	/**< 2842_(1050 - 1057h),	2842_(3050 - 3057h) */
	struct io_cnr_cspr_reg_mcysclbd	MCYSCLBD;	/**< 2842_(1058 - 105Fh),	2842_(3058 - 305Fh) */
} ImCnrRdmaDataCsprMidYTbl;


/** CSPR Middle CC Y Table (OTF/OFL)
address
*/
typedef struct _ImCnrRdmaAddrCsprMidCcYTbl{
	//						OTF							OFL
	ULONG	MCCSCLOF_1;		/**< 2842_(1068 - 106Bh),	2842_(3068 - 306Bh) */
	ULONG	MCCSCLOF_2;		/**< 2842_(106C - 106Fh),	2842_(306C - 306Fh) */
	ULONG	MCCSCLGA_1;		/**< 2842_(1070 - 1073h),	2842_(3070 - 3073h) */
	ULONG	MCCSCLGA_2;		/**< 2842_(1074 - 1077h),	2842_(3074 - 3077h) */
	ULONG	MCCSCLBD_1;		/**< 2842_(1078 - 107Bh),	2842_(3078 - 307Bh) */
	ULONG	MCCSCLBD_2;		/**< 2842_(107C - 107Fh),	2842_(307C - 307Fh) */
} ImCnrRdmaAddrCsprMidCcYTbl;
/** CSPR Middle CC Y Table (OTF/OFL)
data
*/
typedef struct _ImCnrRdmaDataCsprMidCcYTbl{
	//											OTF							OFL
	struct io_cnr_cspr_reg_mccsclof	MCCSCLOF;	/**< 2842_(1068 - 106Fh),	2842_(3068 - 306Fh) */
	struct io_cnr_cspr_reg_mccsclga	MCCSCLGA;	/**< 2842_(1070 - 1077h),	2842_(3070 - 3077h) */
	struct io_cnr_cspr_reg_mccsclbd	MCCSCLBD;	/**< 2842_(1078 - 107Fh),	2842_(3078 - 307Fh) */
} ImCnrRdmaDataCsprMidCcYTbl;


/** CSPR Middle CC C Table (OTF/OFL)
address
*/
typedef struct _ImCnrRdmaAddrCsprMidCcCTbl{
	//						OTF							OFL
	ULONG	MCSSCLOF_1;		/**< 2842_(1088 - 108Bh),	2842_(3088 - 308Bh) */
	ULONG	MCSSCLOF_2;		/**< 2842_(108C - 108Fh),	2842_(308C - 308Fh) */
	ULONG	MCSSCLGA_1;		/**< 2842_(1090 - 1093h),	2842_(3090 - 3093h) */
	ULONG	MCSSCLGA_2;		/**< 2842_(1094 - 1097h),	2842_(3094 - 3097h) */
	ULONG	MCSSCLBD_1;		/**< 2842_(1098 - 109Bh),	2842_(3098 - 309Bh) */
	ULONG	MCSSCLBD_2;		/**< 2842_(109C - 109Fh),	2842_(309C - 309Fh) */
} ImCnrRdmaAddrCsprMidCcCTbl;
/** CSPR Middle CC C Table (OTF/OFL)
data
*/
typedef struct _ImCnrRdmaDataCsprMidCcCTbl{
	//											OTF							OFL
	struct io_cnr_cspr_reg_mcssclof	MCSSCLOF;	/**< 2842_(1088 - 108Fh),	2842_(3088 - 308Fh) */
	struct io_cnr_cspr_reg_mcssclga	MCSSCLGA;	/**< 2842_(1090 - 1097h),	2842_(3090 - 3097h) */
	struct io_cnr_cspr_reg_mcssclbd	MCSSCLBD;	/**< 2842_(1098 - 109Fh),	2842_(3098 - 309Fh) */
} ImCnrRdmaDataCsprMidCcCTbl;


/** CSPR Low Y Table (OTF/OFL)
address
*/
typedef struct _ImCnrRdmaAddrCsprLowYTbl{
	//						OTF							OFL
	ULONG	LCYSCLOF_1;		/**< 2842_(10E8 - 10EBh),	2842_(30E8 - 30EBh) */
	ULONG	LCYSCLOF_2;		/**< 2842_(10EC - 10EFh),	2842_(30EC - 30EFh) */
	ULONG	LCYSCLGA_1;		/**< 2842_(10F0 - 10F3h),	2842_(30F0 - 30F3h) */
	ULONG	LCYSCLGA_2;		/**< 2842_(10F4 - 10F7h),	2842_(30F4 - 30F7h) */
	ULONG	LCYSCLBD_1;		/**< 2842_(10F8 - 10F8h),	2842_(30F8 - 30F8h) */
	ULONG	LCYSCLBD_2;		/**< 2842_(10FC - 10FFh),	2842_(30FC - 30FFh) */
} ImCnrRdmaAddrCsprLowYTbl;

/** CSPR Low Y Table (OTF/OFL)
data
*/
typedef struct _ImCnrRdmaDataCsprLowYTbl{
	//											OTF							OFL
	struct io_cnr_cspr_reg_lcysclof	LCYSCLOF;	/**< 2842_(10E8 - 10EFh),	2842_(30E8 - 30EFh) */
	struct io_cnr_cspr_reg_lcysclga	LCYSCLGA;	/**< 2842_(10F0 - 10F7h),	2842_(30F0 - 30F7h) */
	struct io_cnr_cspr_reg_lcysclbd	LCYSCLBD;	/**< 2842_(10F8 - 10FFh),	2842_(30F8 - 30FFh) */
} ImCnrRdmaDataCsprLowYTbl;


/** CSPR Low CC Y Table (OTF/OFL)
address
*/
typedef struct _ImCnrRdmaAddrCsprLowCcYTbl{
	//						OTF							OFL
	ULONG	LCCSCLOF_1;		/**< 2842_(1108 - 110Bh),	2842_(3108 - 310Bh) */
	ULONG	LCCSCLOF_2;		/**< 2842_(110C - 110Fh),	2842_(310C - 310Fh) */
	ULONG	LCCSCLGA_1;		/**< 2842_(1110 - 1113h),	2842_(3110 - 3113h) */
	ULONG	LCCSCLGA_2;		/**< 2842_(1114 - 1117h),	2842_(3114 - 3117h) */
	ULONG	LCCSCLBD_1;		/**< 2842_(1118 - 1118h),	2842_(3118 - 3118h) */
	ULONG	LCCSCLBD_2;		/**< 2842_(111C - 111Fh),	2842_(311C - 311Fh) */
} ImCnrRdmaAddrCsprLowCcYTbl;

#endif

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------- driver section ----------------------------

GType 						im_cnr_get_type(void) G_GNUC_CONST;
ImCnr* 					im_cnr_new(void);
/**
Set software reset and operating mode for Off Line
@param [in]	ch				channel[0 - 2]
@retval		D_DDIM_OK						Success
*/
extern	INT32 im_cnr_ofl_init(ImCnr *self, UCHAR ch );

/**
SPR Stop for Off Line
@param [in]	ch				channel[0 - 2]
@retval		D_DDIM_OK						Success.
@remarks	SPR function is stopped(disable).
*/
extern	INT32 im_cnr_ofl_stop(ImCnr *self, UCHAR ch );

/**
The semaphore of SPR is returned for Off Line
@param [in]	ch				channel[0 - 1]
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_SEM_NG					Fail - Processing NG (system error)
@remarks	This API uses DDIM_User_Sig_Sem().
*/
extern	INT32 im_cnr_ofl_close(ImCnr *self, UCHAR ch );

/**
SPR Reset for Off Line
@param [in]	ch				channel[0 - 2]
@retval		D_DDIM_OK						Success
@remarks	SPR function soft reset
*/
extern	INT32 im_cnr_ofl_reset(ImCnr *self, UCHAR ch );

/**
SPR Macro Interrupt handler for ch0
@remarks This API uses DDIM_User_Set_Flg().
*/
extern	VOID im_cnr_0_int_handler( VOID );

/**
SPR Macro Interrupt handler for ch1
@remarks This API uses DDIM_User_Set_Flg().
*/
extern	VOID im_cnr_1_int_handler( VOID );

/**
Set software reset and operating mode for On The Fly
@param [in]	ch				channel[0 - 2]
@retval		D_DDIM_OK						Success
*/
extern	INT32 im_cnr_otf_init(ImCnr *self, UCHAR ch );

/**
SPR Stop for On The Fly
@param [in]	ch				channel[0 - 2]
@retval		D_DDIM_OK						Success.
@remarks	SPR function is stopped(disable).
*/
extern	INT32 im_cnr_otf_stop(ImCnr *self, UCHAR ch );

/**
The semaphore of SPR is returned for On The Fly
@param [in]	ch				channel[0 - 1]
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_SEM_NG					Fail - Processing NG (system error)
@remarks	This API uses DDIM_User_Sig_Sem().
*/
extern	INT32 im_cnr_otf_close(ImCnr *self, UCHAR ch );

/**
SPR Reset for On The Fly
@param [in]	ch				channel[0 - 2]
@retval		D_DDIM_OK						Success
@remarks	SPR function soft reset
*/
extern	INT32 im_cnr_otf_reset(ImCnr *self, UCHAR ch );



#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
//------------ for RDMA ----------------


#endif


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_CNR_H__ */

