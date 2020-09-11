/*
 * imdisp.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
/**
@weakgroup im_disp
@{

<hr>

@section im_disp_sequence Sequence Chart
- @ref Disp_Start_1
- @ref Disp_Start_2
- @ref Disp_Stop_1
- @ref Disp_Stop_2
- @ref Disp_Stop_3
- @ref Disp_Stop_4
- @ref Disp_Stop_5
- @ref Disp_Int
- @ref Disp_Face_Frame


@section Disp_Start_1					Initialize and start driver.
@image html im_disp_start.png

@section Disp_Start_2					The specified layer is started.
@image html im_disp_start_specified_layer.png

@section Disp_Stop_1					All layer stop (no wait).
@image html im_disp_stop_all_stop_no_wait.png

@section Disp_Stop_2					All layer stop (wait, progressive).
@image html im_disp_stop_all_stop_wait_prog.png

@section Disp_Stop_3					All layer stop (wait, interlace).
@image html im_disp_stop_all_stop_wait_int.png

@section Disp_Stop_4					The specified layer is stoped (no wait).
@image html im_disp_stop_specified_layer_no_wait.png

@section Disp_Stop_5					The specified layer is stoped (wait).
@image html im_disp_stop_specified_layer_wait.png

@section Disp_Int						Set interrupt.
@image html im_disp_set_int.png

@section Disp_Face_Frame				Data read and setting (ex. face frame).
@image html im_disp_face_frame.png

@}
*/
/**
@addtogroup im_disp
@{
*/

#ifndef _IM_DISP_H_
#define _IM_DISP_H_
#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"


#define IM_TYPE_DISP				(im_disp_get_type())
#define IM_DISP(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp))
#define IM_IS_DISP(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP))

typedef struct   _ImDisp 			ImDisp;
typedef struct   _ImDispPrivate		ImDispPrivate;

struct _ImDisp{
	KObject parent;
};

KConstType 		im_disp_get_type(void);
ImDisp*	im_disp_new(void);

typedef enum {
	E_IM_DISP_INT_CB_VE = 0,	/**< VE: Vsync detection interruption.											*/
	E_IM_DISP_INT_CB_VE2,		/**< VE2: Vsync detection interruption for 2nd field.							*/
	E_IM_DISP_INT_CB_GR0EE,		/**< GR0EE: OSD data 0 input block forwarding error interruption.				*/
	E_IM_DISP_INT_CB_GR1EE,		/**< GR1EE: OSD data 1 input block forwarding error interruption.				*/
	E_IM_DISP_INT_CB_GA0EE,		/**< GA0EE: OSD data 0 input block A component forwarding error interruption.	*/
	E_IM_DISP_INT_CB_GA1EE,		/**< GA1EE: OSD data 1 input block A component forwarding error interruption.	*/
	E_IM_DISP_INT_CB_LEE,		/**< LEE: Main data input block forwarding error interruption.					*/

	E_IM_DISP_INT_CB_GR0REE,	/**< GR0REE: OSD data 0 input block AXI error interruption.						*/
	E_IM_DISP_INT_CB_GR1REE,	/**< GR1REE: OSD data 1 input block AXI error interruption.						*/
	E_IM_DISP_INT_CB_GA0REE,	/**< GA0REE: OSD data 0 input block A component AXI error interruption.			*/
	E_IM_DISP_INT_CB_GA1REE,	/**< GA1REE: OSD data 1 input block A component AXI error interruption.			*/
	E_IM_DISP_INT_CB_LREE,		/**< LREE: Main data input block AXI error interruption.						*/
	E_IM_DISP_INT_CB_MAX		/**< Stopper */
} E_IM_DISP_INT_CB;

// for Gamma table set/get
typedef enum {
	E_IM_DISP_ACCESS_GAMMA_SET = 0,	// copy the local gamma table to the gamma region registers
	E_IM_DISP_ACCESS_GAMMA_GET,		// copy the gamma region registers to the local gamma table
} E_IM_DISP_ACCESS_GAMMA;

// Startup status of layer
typedef enum {
	E_IM_DISP_TRG_WRITE_NO_ACT = 0x00000000,	// Set TRG to off at once
	E_IM_DISP_TRG_WRITE_ACT,					// Set TRG to on
	E_IM_DISP_TRG_READ_NO_ACT,					// TRG is not on or set to off by frame stop
	E_IM_DISP_TRG_READ_ACT						// TRG is on
} E_IM_DISP_TRG;

#define	D_IM_DISP_OSD_DISPLAY_AREA_COUNT			(10)	/**< Maximum number of OSD display area.	*/
#define	D_IM_DISP_OSD_ADDR_0_BANK_SIZE				(4)		/**< Bank size of main image address 0.		*/
#define	D_IM_DISP_OSD_ADDR_BANK_SIZE				(9)		/**< Bank size of main image address.		*/

#ifdef CO_DDIM_UTILITY_USE
/**
@name Utility Definition
@{
*/
//---------------------- utility section -------------------------------
/** CC information */
//---------------------- colabo  section -------------------------------
/*		@}*/ /* end of im_disp_util */
#endif // CO_DDIM_UTILITY_USE
/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/** Control block selection. (Bit flag) */
typedef enum {
	E_IM_DISP_HDMI = 0,		/**< HDMI block     (Common block 0).	*/
	E_IM_DISP_LCD_MIPI		/**< LCD/MIPI block (Common block 1).	*/
} E_IM_DISP_SEL;

/** Gamma correct or Anti-Gamma correct or Luminance correct or Chroma correct. */
typedef enum {
	E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA			= 0x00000001,	/**< Anti-gamma correct						*/
	E_IM_DISP_CORRECT_SELECT_GAMMA_IN			= 0x00000002,	/**< Gamma correct (Main data input block)	*/
	E_IM_DISP_CORRECT_SELECT_GAMMA_OUT			= 0x00000004,	/**< Gamma correct (Data output block)		*/
	E_IM_DISP_CORRECT_SELECT_LUMINANCE			= 0x00000008,	/**< Luminance correct						*/
	E_IM_DISP_CORRECT_SELECT_CHROMA				= 0x00000010,	/**< Chroma correct							*/
} E_IM_DISP_CORRECT_SELECT;

/** Table access enable setting of Gamma correct or Anti-Gamma correct or gradation adjustment. */
typedef enum {
	E_IM_DISP_TABLE_ACCESS_DISABLE = 0,		/**< Table access disable	*/
	E_IM_DISP_TABLE_ACCESS_ENABLE			/**< Table access enable	*/
} E_IM_DISP_TABLE_ACCESS;

/** Select interruption demand permission. */
typedef enum {
	E_IM_DISP_INTERRUPTION_SELECT_VE2    = 0x00100000,	/**< Vertical syschronization signal interruption for 2nd field permission */
	E_IM_DISP_INTERRUPTION_SELECT_VE     = 0x00010000,	/**< Vertical syschronization signal interruption permission*/

	E_IM_DISP_INTERRUPTION_SELECT_GA1REE = 0x00008000,	/**< GR1 A component AXI error interruption permission */
	E_IM_DISP_INTERRUPTION_SELECT_GA0REE = 0x00004000,	/**< GR0 A component AXI error interruption permission */
	E_IM_DISP_INTERRUPTION_SELECT_GR1REE = 0x00002000,	/**< GR1 AXI error interruption permission */
	E_IM_DISP_INTERRUPTION_SELECT_GR0REE = 0x00001000,	/**< GR0 AXI error interruption permission */
	E_IM_DISP_INTERRUPTION_SELECT_LREE   = 0x00000100,	/**< Main AXI error interruption permission */

	E_IM_DISP_INTERRUPTION_SELECT_GA1EE  = 0x00000080,	/**< GR1 A component transmitte error interruption permission */
	E_IM_DISP_INTERRUPTION_SELECT_GA0EE  = 0x00000040,	/**< GR0 A component transmitte error interruption permission */
	E_IM_DISP_INTERRUPTION_SELECT_GR1EE  = 0x00000020,	/**< GR1 transmitte error interruption permission */
	E_IM_DISP_INTERRUPTION_SELECT_GR0EE  = 0x00000010,	/**< GR0 transmitte error interruption permission */
	E_IM_DISP_INTERRUPTION_SELECT_LEE    = 0x00000001,	/**< Main transmitte error interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL_VE		=	E_IM_DISP_INTERRUPTION_SELECT_VE |
											E_IM_DISP_INTERRUPTION_SELECT_VE2,/**< All Vertical syschronization signal interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL_GRREE	=	E_IM_DISP_INTERRUPTION_SELECT_GA1REE |
											E_IM_DISP_INTERRUPTION_SELECT_GA0REE |
											E_IM_DISP_INTERRUPTION_SELECT_GR1REE |
											E_IM_DISP_INTERRUPTION_SELECT_GR0REE,/**< All GR's AXI error interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL_GREE	=	E_IM_DISP_INTERRUPTION_SELECT_GA1EE |
											E_IM_DISP_INTERRUPTION_SELECT_GA0EE |
											E_IM_DISP_INTERRUPTION_SELECT_GR1EE |
											E_IM_DISP_INTERRUPTION_SELECT_GR0EE,/**< All GR's transmitte error interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL_REE	=	E_IM_DISP_CORRECT_SELECT_ALL_GREE | 
											E_IM_DISP_INTERRUPTION_SELECT_LREE,/**< Main and all GR's AXI error interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL_EE		=	E_IM_DISP_CORRECT_SELECT_ALL_GREE | 
											E_IM_DISP_INTERRUPTION_SELECT_LEE,/**< Main and all GR's transmitte error interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL_GR_ERROR =	E_IM_DISP_CORRECT_SELECT_ALL_GREE |
											E_IM_DISP_CORRECT_SELECT_ALL_GRREE,/**< All GR's transmitte error and AXI error interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL_MIAN_ERROR=E_IM_DISP_INTERRUPTION_SELECT_LREE | 
											E_IM_DISP_INTERRUPTION_SELECT_LEE,/**< Main's transmitte error interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL_ERROR	=	E_IM_DISP_CORRECT_SELECT_ALL_GR_ERROR | 
											E_IM_DISP_CORRECT_SELECT_ALL_MIAN_ERROR,/**< Main and all GRs all errors interruption permission */

	E_IM_DISP_CORRECT_SELECT_ALL		=	E_IM_DISP_CORRECT_SELECT_ALL_VE	|
											E_IM_DISP_CORRECT_SELECT_ALL_ERROR	/**< All interruption permission */
} E_IM_DISP_INTERRUPTION_SELECT;

/** LRPGCTL Register - RPGTMG (Register parameter internal taking timing selection)<br>
 RPGCTL Register - RPGTMG (Register parameter internal taking timing selection)<br>
 GRRPGCTL Register - RPGTMG (Register parameter internal taking timing selection)*/
typedef enum {
	E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP = 0,	/**< LRPGCTL.RPGTMG, RPGCTL.RPGTMG, GRRPGCTL.RPGTMG Register<br> 
												 When vertical synchronizing signal is generated at frame head.	*/
	E_IM_DISP_RPGTMG_VSYNC_VSYNC			/**< LRPGCTL.RPGTMG, RPGCTL.RPGTMG, GRRPGCTL.RPGTMG Register<br>
												 When vertical synchronizing signal is generated.				*/
}E_IM_DISP_RPGTMG;

/** LRSZ0 Register - RSZSL (Horizontal resize method selection)<br>
 GRRSZ0 Register - RSZSL (Horizontal resize method selection)*/
typedef enum {
	E_IM_DISP_RSZSL_PADDING_THINNING = 0,	/**< LRSZ0.RSZSL, GRRSZ0.RSZSL Register<br> Padding and thinning out processing.	*/
	E_IM_DISP_RSZSL_BILINEAR				/**< LRSZ0.RSZSL, GRRSZ0.RSZSL Register<br> Bilinear interpolation processing.		*/
}E_IM_DISP_RSZSL;

/** LYW0ST Register - YW0MD (Range 0 - warning processing mode select)<br>
 LYW1ST Register - YW1MD (Range 0 - warning processing mode select) */
typedef enum {
	E_IM_DISP_YWMD_BR_RGB = 0,	/**< LYW0ST.YW0MD, LYW1ST.YW1MD Register<br> Brightness reverse display or RGB pixel warning display.	*/
	E_IM_DISP_YWMD_BW_R,		/**< LYW0ST.YW0MD, LYW1ST.YW1MD Register<br> Brightness warning display or R pixel warning display.		*/
	E_IM_DISP_YWMD_G,			/**< LYW0ST.YW0MD, LYW1ST.YW1MD Register<br> Brightness G pixel warning display.						*/
	E_IM_DISP_YWMD_B			/**< LYW0ST.YW0MD, LYW1ST.YW1MD Register<br> Brightness B pixel warning display.						*/
}E_IM_DISP_YWMD;

/** GDISPEN Register - (Grid display enable)*/
typedef enum {
	E_IM_DISP_GDISPEN_NOT_DISPLAY = 0,	/**< GDISPEN Register<br> Not Display.	*/
	E_IM_DISP_GDISPEN_DISPLAY			/**< GDISPEN Register<br> Display.		*/
}E_IM_DISP_GDISPEN;

/** GRSCCTL Register - IDSET (Input data area setting), IDM (Input data area monitor)*/
typedef enum {
	E_IM_DISP_INPUT_DATA_AREA_0 = 0,	/**< GRSCCTL.IDSET, GRSCCTL.IDM Register<br> Input data area 0.	*/
	E_IM_DISP_INPUT_DATA_AREA_1,		/**< GRSCCTL.IDSET, GRSCCTL.IDM Register<br> Input data area 1.	*/
	E_IM_DISP_INPUT_DATA_AREA_2,		/**< GRSCCTL.IDSET, GRSCCTL.IDM Register<br> Input data area 2.	*/
	E_IM_DISP_INPUT_DATA_AREA_3			/**< GRSCCTL.IDSET, GRSCCTL.IDM Register<br> Input data area 3.	*/
} E_IM_DISP_INPUT_DATA_AREA;

/** TRG Register - TGKMD (External start-up mode) */
typedef enum {
	E_IM_DISP_TGKMD_NORMAL		= 0,	/**< TRG.TGKMD Register<br> Normal start-up		*/
	E_IM_DISP_TGKMD_EXTERNAL	= 1		/**< TRG.TGKMD Register<br> External start-up	*/
} E_IM_DISP_TGKMD;

/** P2MCTL Register - PLPF (LPF recording mode) */
typedef enum {
	E_IM_DISP_PLPF_INVALID	= 0,	/**< LPF invalid.	*/
	E_IM_DISP_PLPF_SHORT,			/**< LPF(Short).	*/
	E_IM_DISP_PLPF_MIDDLE,			/**< LPF(Middle).	*/
	E_IM_DISP_PLPF_LONG				/**< LPF(Long).		*/
} E_IM_DISP_PLPF;

/** P2MCTL Register - P2MTYP (P2M recording mode) */
typedef enum {
	E_IM_DISP_P2MTYP_8	= 0,	/**< 8 bit recording mode.			*/
	E_IM_DISP_P2MTYP_10_PACK,	/**< 10 bit pack recording mode.	*/
	E_IM_DISP_P2MTYP_12_PACK,	/**< 12 bit pack recording mode.	*/
	E_IM_DISP_P2MTYP_16			/**< 16 bit recording mode.			*/
} E_IM_DISP_P2MTYP;

/** P2M2PMD Register (P2M 1 pixel / 2 pixels input mode selection) */
typedef enum {
	E_IM_DISP_P2M2PMD_1	= 0,	/**< 1 pixel input mode.	*/
	E_IM_DISP_P2M2PMD_2			/**< 2 pixels input mode.	*/
} E_IM_DISP_P2M2PMD;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/** LIDT0/LIDT1 register structure. */
typedef union {
	ULONG		word[2];	/**< All bits */
	struct {
		/* LIDT0 */
		ULONG	IFMT	:5;		/**< Input format selection.<br>
									 <ul><li>@ref D_IM_DISP_LIDT_IFMT_YCC422_RP_8BIT
										 <li>@ref D_IM_DISP_LIDT_IFMT_YCC422_RP_12BIT_PACK
										 <li>@ref D_IM_DISP_LIDT_IFMT_YCC422_RP_16BIT
										 <li>@ref D_IM_DISP_LIDT_IFMT_YCC422_RP_10BIT_PACK
										 <li>@ref D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT
										 <li>@ref D_IM_DISP_LIDT_IFMT_YCC420_RP_10BIT_PACK
										 <li>@ref D_IM_DISP_LIDT_IFMT_GENERAL_8BIT
										 <li>@ref D_IM_DISP_LIDT_IFMT_GENERAL_16BIT
										 <li>@ref D_IM_DISP_LIDT_IFMT_GENERAL_10BIT
										 <li>@ref D_IM_DISP_LIDT_IFMT_GENERAL_10BITx2</ul>							*/
		ULONG			:3;		/**< Reserve																		*/
		ULONG	NBT		:2;		/**< Burst size selection.<br>
									 <ul><li>@ref D_IM_DISP_NBT_128BYTE
										 <li>@ref D_IM_DISP_NBT_256BYTE
										 <li>@ref D_IM_DISP_NBT_512BYTE</ul>										*/
		ULONG			:2;		/**< Reserve																		*/
		ULONG	IFEW	:2;		/**< Input format effective bit width selection.<br>
									 <ul><li>@ref D_IM_DISP_IFEW_16BIT
									     <li>@ref D_IM_DISP_IFEW_14BIT
										 <li>@ref D_IM_DISP_IFEW_12BIT
										 <li>@ref D_IM_DISP_IFEW_10BIT</ul>											*/
		ULONG			:2;		/**< Reserve																		*/
		ULONG	LVFM	:1;		/**< LVFM: Video format selection.<br>
									 <ul><li>@ref D_IM_DISP_FORMAT_NORMAL
										 <li>@ref D_IM_DISP_FORMAT_VIDEO</ul>											*/
		ULONG			:15;	/**< Reserve																		*/
		/* LIDT1 */
		ULONG	PKGDV	:4;		/**< PKGDV: Continuous forwarding demand control.<br>
									 Value : 0 (fix).																*/
		ULONG	CACHE	:4;		/**< CACHE: Cache type.<br>
									 d[0]:Bufferable bit. Value 0:Nonbufferable, 1:Bufferable.<br>
									 d[1]:Cacheable bit. Value 0:Noncacheable, 1:Cacheable.<br>
									 d[2]:Read allocate bit. Value 0:Read through, 1:Allocate on Reads.<br>
									 d[3]:Write allocate bit. Value 0:Write through, 1:Allocate on writes.<br>		*/
		ULONG	PROT	:3;		/**< PROT: Protect type.<br>
									 d[0]:Normal or privileged. Value 0:Normal access, 1:Privileged access.<br>
									 d[1]:Secure or non-secure. Value 0:Secure access, 1:Non-secure access.<br>
									 d[2]:Instruction or Data. Value 0:Data access, 1:Instrauction access.<br>		*/
		ULONG			:1;		/**< Reserve																		*/
		ULONG	YSLVSL	:1;		/**< YSLVSL: Master interface selection of Y.<br>
									 <ul><li>@ref D_IM_DISP_SLVSL_MASTER_INTERFACE_0
										 <li>@ref D_IM_DISP_SLVSL_MASTER_INTERFACE_1</ul>							*/
		ULONG	CSLVSL	:1;		/**< CSLVSL: Master interface selection of Cb/Cr.<br>
									 <ul><li>@ref D_IM_DISP_SLVSL_MASTER_INTERFACE_0
										 <li>@ref D_IM_DISP_SLVSL_MASTER_INTERFACE_1</ul>							*/
		ULONG			:18;	/**< Reserve																		*/
	} bit;	/**< Bit field */
} U_IM_DISP_LIDT;

/** LRSZ1, GRRSZ1 register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	HRSZM	:5;		/**< HRSZM: Horizontal resize magnification setting (M of M/N)<br>
									 Value range:1~31.<br>
									 Resize magnification range:M/N=1/2~8.																*/
		ULONG			:3;		/**< Reserve																							*/
		ULONG	HRSZN	:5;		/**< HRSZM: Horizontal resize magnification setting (N of M/N)<br>
									 Value range:1~31.<br>
									 Resize magnification range:M/N=1/2~8.																*/
		ULONG			:11;	/**< Reserve																							*/
		ULONG	HRSZOF	:5;		/**< HRSZOF: Horizontal resize offset.<br>
									 Value range:0~31.<br>
									 fulfill the following conditions.<br>
									 HRSZOF < (pixel count before resizing) * HRSZM - (pixel count before resizing - 1) * HRSZM.<br>
									 HRSZOF < HRSZM.<br>
									 0 is set up when resize magnification is 1 or LRSZ0.RSZSL=0.<br>									*/
		ULONG			:3;		/**< Reserve																							*/
	} bit;	/**< Bit field */
} U_IM_DISP_RSZ1;

/** LRSZ2, GRRSZ2 register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	VRSZM	:5;		/**< VRSZM: Vertical resize magnification setting (M of M/N)<br>
									 Value range:1~31.<br>
									 Resize magnification range:M/N=1/2~8.																*/
		ULONG			:3;		/**< Reserve																							*/

		ULONG	VRSZN	:5;		/**< VRSZN: Vertical resize magnification setting (N of M/N)<br>
									 Value range:1~31.<br>
									 Resize magnification range:M/N=1/2~8.																*/
		ULONG			:11;	/**< Reserve																							*/
		ULONG	VRSZOF	:5;		/**< VRSZOF: Vertical resize offset.<br>
									 Value range:0~31.<br>
									 fulfill the following conditions.<br>
									 VRSZOF < (pixel count before resizing) * VRSZM - (pixel count before resizing - 1) * VRSZM.<br>
									 VRSZOF < VRSZM.<br>
									 0 is set up when resize magnification is 1 or LRSZ0.RSZSL(GRRSZ0.RSZSL)=0.<br>						*/
		ULONG			:3;		/**< Reserve																							*/
	} bit;	/**< Bit field */
} U_IM_DISP_RSZ2;

/** LRSZ3, GRRSZ3 register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	HCSTA	:6;		/**< HCSTA: Horizontal chrominance start position adjustment.<br>
									 Value range:0~63.												*/
		ULONG			:2;		/**< Reserve														*/

		ULONG	VCSTA	:6;		/**< VCSTA: Vertical chrominance start position adjustment.<br>
									 Value range:0~63.												*/
		ULONG			:18;	/**< Reserve														*/
	} bit;	/**< Bit field */
} U_IM_DISP_RSZ3;

/** LYHLPCTL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	YHLPEN	:1;	/**< YHLPEN: YHLP enable<br>
								 Value 0:disable, 1:enable.<br>								*/
		ULONG			:7;	/**< Reserve													*/
		ULONG	YHLPMD	:2;	/**< YHLPMD: YHLP mode<br>
								 <ul><li>@ref E_IM_DISP_YHLPMD_HORIZONTAL_SPACE_FILTER
									 <li>@ref E_IM_DISP_YHLPMD_OUTLINE_ENHANCEMENT
									 <li>@ref E_IM_DISP_YHLPMD_OUTLINE_COLOR</ul>			*/
		ULONG			:22;/**< Reserve													*/
	} bit;	/**< Bit field */
} U_IM_DISP_LYHLPCTL;

/** LYHLPK0/1 register structure. */
typedef union {
	ULONG		word[2];	/**< All bits */
	struct {
		ULONG	YHLPK0	:9;	/**< YHLPK0: YHLP filter coefficient 0<br>
								 Value range:0~511.											*/
		ULONG			:7;	/**< Reserve													*/
		ULLONG	YHLPK1	:8;	/**< YHLPK1: YHLP filter coefficient 1<br>
								 Value range:0~255.											*/
		ULONG			:8;/**< Reserve														*/
		ULONG	YHLPK2	:8;	/**< YHLPK0: YHLP filter coefficient 2<br>
								 Value range:0~255.											*/
		ULONG			:8;	/**< Reserve													*/
		ULONG	YHLPK3	:8;	/**< YHLPK3: YHLP filter coefficient 3<br>
								 Value range:0~255.											*/
		ULONG			:8;/**< Reserve														*/
	} bit;	/**< Bit field */
} U_IM_DISP_LYHLPK;

/** LYHLPOL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	YHLPCOR	:16;	/**< YHLPCOR: Outline coring value <br>
									 Value range:0~65535.									*/
		ULONG	YHLPTH	:16;	/**< YHLPTH: Outline color threshold<br>
									 Value range:0~65535.									*/
	} bit;	/**< Bit field */
} U_IM_DISP_LYHLPOL;

/** LYHLPCLR register structure. */
typedef union {
	ULLONG		dword;	/**< All bits */
	struct {
		ULLONG	YHLPY	:16;	/**< YHLPY: Outline color pixel Y.<br>
									 Value range:0~65535.									*/
		ULLONG	YHLPCB	:16;	/**< YHLPCB: Outline color pixel Cb.<br>
									 Value range:0~65535.									*/
		ULLONG	YHLPCR	:16;	/**< YHLPCR: Outline color pixel Cr.<br>
									 Value range:0~65535.									*/
		ULLONG			:16;	/**< Reserve												*/
	} bit;	/**< Bit field */
} U_IM_DISP_LYHLPCLR;

/**	 LYWCTL	register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	YWEN	:1;		/**< YWEN: Warning enable.<br>
									 <ul><li>@ref D_IM_DISP_ENABLE_OFF
										 <li>@ref D_IM_DISP_ENABLE_ON</ul>					*/
		ULONG			:7;		/**< Reserve												*/
		ULONG	YWSL	:2;		/**< YWSL: Warning type select.<br>
									 <ul><li>@ref E_IM_DISP_YWSL_BRIGHTNESS_SPECIFIED_COLOR
										 <li>@ref E_IM_DISP_YWSL_BRIGHTNESS_ZEBRA
										 <li>@ref E_IM_DISP_YWSL_RGB_SPECIFIED_COLOR
										 <li>@ref E_IM_DISP_YWSL_RGB_ZEBRA</ul>				*/
		ULONG			:22;	/**< Reserve												*/
	}bit;	/**< Bit field */
} U_IM_DISP_LYWCTL;

/**	LYW0TH/LYW1TH register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	YWTHH	:16;	/**< YW0THH/YW1THH: Warning level upper limit.<br>
									 Value range:0~65535.									*/
		ULONG	YWTHL	:16;	/**< YW0THL/YW1THL: Warning level lower limit.<br>
									 Value range:0~65535.									*/
	}bit;	/**< Bit field */
} U_IM_DISP_LYWTH;

/** LYW0CA/LYW0CB/LYW1CA/LYW1CB register structure. */
typedef union {
	ULLONG		dword;	/**< All bits */
	struct {
		ULLONG	YWY		:16;	/**< YW0AY/YW0BY/YW1AY/YW1BY: Warning color Y(R).<br>
									 LYWCTL.YWSL=0or1 -> Y data.<br>
									 LYWCTL.YWSL=2or3 -> R data.<br>
									 Value range:0~65535.									*/
		ULLONG	YWCB	:16;	/**< YW0ACB/YW0BCB/YW1ACB/YW1BCB: Warning color Cb(G).<br>
									 LYWCTL.YWSL=0or1 -> Cb data.<br>
									 LYWCTL.YWSL=2or3 -> G data.<br>
									 Value range:0~65535.									*/
		ULLONG	YWCR	:16;	/**< YW0ACR/YW0BCR/YW1ACR/YW1BCR: Warning color Cr(B).<br>
									 LYWCTL.YWSL=0or1 -> Cr data.<br>
									 LYWCTL.YWSL=2or3 -> B data.<br>
									 Value range:0~65535.									*/
		ULLONG	YWA		:8;		/**< YW0AA/YW0BA/YW1AA/YW1BA: Warning color A.<br>
									 Value range:0~255.										*/
		ULLONG			:8;		/**< Reserve												*/
	} bit;	/**< Bit field */
} U_IM_DISP_LYWC;

/**	LBLTMR register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	BTIMH	:8;	/**< BTIMH: Setting of luminance warning display period.<br>
								 Value range:0~255.<br>
								 BTIMH = frame cout - 1.<br>									*/
		ULONG	BTIML	:8;	/**< BTIML: Setting of luminance warning non-display period.<br>
								 Value range:0~255.<br>
								 BTIML = frame cout - 1.<br>									*/
		ULONG	BTIMD	:1;	/**< BTIMD: Warning display period mode.<br>
									 <ul><li>@ref D_IM_DISP_BTIMD_NORMAL
										 <li>@ref D_IM_DISP_BTIMD_BLINK</ul>					*/
		ULONG			:15;/**< Reserve														*/
	} bit;	/**< Bit field */
} U_IM_DISP_LBLTMR;

/** LZBWID register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	ZBHH	:8;		/**< ZBHH: Zebra warning horizontal high brightness width.<br>
									 Value range : 2~255.<br>									*/
		ULONG	ZBHL	:8;		/**< ZBHL: Zebra warning horizontal low brightness width.<br>
									 Value range : 2~255.<br>									*/
		ULONG			:16;	/**< Reserve													*/
	} bit;	/**< Bit field */
} U_IM_DISP_LZBWID;

/** LZBV register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	ZBVSTA	:1;		/**< ZBVSTA: Zebra warning dispay vertical start position.<br>
									 Value :0 or 1.												*/
		ULONG			:7;		/**< Reserve													*/
		ULONG	ZBVCYC	:1;		/**< ZBVCYC: Zebra warning dispay vertical cycle.<br>
									 Value 0:a pixel cycle, 1:2 pixels cycle.<br>				*/
		ULONG			:23;	/**< Reserve													*/
	} bit;	/**< Bit field */
} U_IM_DISP_LZBV;

/** LZBPT register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	ZBDIR	:1;	/**< ZBDIR: Zebra warning dispay pattern direction.<br>
								 Value 0:right down, 1:left down.<br>							*/
		ULONG			:31;/**< Reserve														*/
	} bit;	/**< Bit field */
} U_IM_DISP_LZBPT;

/**	LTBLASET register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	IGTAEN	:1;		/**< IGTAEN : Inverse gamma table access enable.<br>
									 <ul><li>@ref E_IM_DISP_TABLE_ACCESS_DISABLE
										 <li>@ref E_IM_DISP_TABLE_ACCESS_ENABLE</ul>		*/
		ULONG	IGEN	:1;		/**< IGEN: Inverse gamma correction enable.<br>
									 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
										 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>		*/
		ULONG	IGTSL	:1;		/**< IGTSL: Inverse gamma correction table surface.<br>
									 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
										 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>			*/
		ULONG			:5;		/**< Reserve												*/
		ULONG	GTAEN	:1;		/**< GTAEN : Gamma table access enable.<br>
									 <ul><li>@ref E_IM_DISP_TABLE_ACCESS_DISABLE
										 <li>@ref E_IM_DISP_TABLE_ACCESS_ENABLE</ul>		*/
		ULONG	GMEN	:1;		/**< GMEN: Gamma correction enable.<br>
									 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
										 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>		*/
		ULONG	GMTSL	:1;		/**< GMTSL: Gamma correction table surface.<br>
									 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
										 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>			*/
		ULONG			:5;		/**< Reserve												*/
		ULONG	IGTMN	:1;		/**< IGTMN: Inverse gamma correction monitor.<br>
									 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
										 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>			*/
		ULONG			:7;		/**< Reserve												*/
		ULONG	GMTMN   :1;		/**< GMTMN: Gamma correction monitor.<br>
									 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
										 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>			*/
		ULONG			:7;		/**< Reserve												*/
	} bit;	/**< Bit field */
} U_IM_DISP_LTBLASET;

/** LGMMD register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	GMMD	:1;		/**< GMMD: Gamma correct mode.<br>
									 <ul><li>@ref D_IM_DISP_GMMD_EQUAL_INTERVAL_MODE
										 <li>@ref D_IM_DISP_GMMD_UNEQUAL_INTERVALS_MODE</ul>	*/
		ULONG			:31;	/**< Reserve													*/
	} bit;	/**< Bit field */
} U_IM_DISP_LGMMD;

/** LALP register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	ALP		:8;		/**< ALP: alpha value setting.<br>
									 Value range:0~255				*/
		ULONG			:24;	/**< Reserve						*/
	} bit;	/**< Bit field */
} U_IM_DISP_LALP;

/**	LDSTA, GRDSTA, GHDSTA, GRTDSTA, FFDSTA register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	DSH		:16;/**< DSH: Horizontal display beginning position.<br>
								 Value range:0~65534 (2-pixel unit)				*/
		ULONG	DSV		:14;/**< DSV: Vertical display beginning position.<br>
								 Value range:0~16382 (2-pixel unit)				*/
		ULONG			:2;	/**< Reserve										*/
	} bit;	/**< Bit field */
} U_IM_DISP_DSTA;

/**	LREVDISP register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	HREV	:1;	/**< HREV: Horizontal reversing display selection.
								 <ul><li>@ref D_IM_DISP_REV_NORMAL
									 <li>@ref D_IM_DISP_REV_REVERSE</ul>		*/
		ULONG			:7;	/**< Reserve										*/
		ULONG	VREV	:1;	/**< VREV: Vertical reversing display selection.
								 <ul><li>@ref D_IM_DISP_REV_NORMAL
									 <li>@ref D_IM_DISP_REV_REVERSE</ul>		*/
		ULONG			:23;/**< Reserve										*/
	} bit;	/**< Bit field */
} U_IM_DISP_LREVDISP;


/**	FODATA register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	FOD_0	:8;	/**< FOD_0: R (or Y)<br>
								 Value range:0~255	*/
		ULONG	FOD_1	:8;	/**< FOD_1: G (or Cb)<br>
								 Value range:0~255	*/
		ULONG	FOD_2	:8;	/**< FOD_2: B (or Cr)<br>
								 Value range:0~255	*/
		ULONG			:8;	/**< Reserve			*/
	} bit;	/**< Bit field */
} U_IM_DISP_FODATA;

/**	GLENGTH register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	GHLEN	:16;	/**< GHLEN: Horizontal grid line length.<br>
									 Value range:8~65534 (2-pixel unit)		*/
		ULONG	GVLEN	:14;	/**< GVLEN: Vertical grid line length.<br>
									 Value range:8~16382 (2-pixel unit)		*/
		ULONG			:2;		/**< Reserve								*/
	} bit;	/**< Bit field */
} U_IM_DISP_GLENGTH;

/**	GWIDTH register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	GHWID	:6;		/**< GHWID: Horizontal grid line width.<br>
									 Value range:2~62 (2-pixel unit)		*/
		ULONG			:10;	/**< Reserve								*/
		ULONG	GVWID	:6;		/**< GVWID: Vertical grid line width.<br>
									 Value range:2~62 (2-pixel unit)		*/
		ULONG			:10;	/**< Reserve								*/
	} bit;	/**< Bit field */
} U_IM_DISP_GWIDTH;

/**	GITVL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	GHITV	:14;	/**< GHITV: Horizontal grid line interval.<br>
									 Value range:4~16382 (2-pixel unit)<br>
									 GHITV >= GHWID + 2							*/
		ULONG			:2;		/**< Reserve									*/
		ULONG	GVITV	:16;	/**< GVITV: Vertical grid line interval.<br>
									 Value range:4~65534 (2-pixel unit)<br>
									 GVITV >= GVWID + 2							*/
	} bit;	/**< Bit field */
} U_IM_DISP_GITVL;

/**	GNUM register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	GHNUM	:3;		/**< GHNUM: Number of horizontal grid line.<br>
									 Value range:0~7<br>
									 Horizontal grid line num = GHNUM + 1		*/
		ULONG			:13;	/**< Reserve									*/
		ULONG	GVNUM	:3;		/**< GVNUM: Number of vertical grid line.<br>
									 Value range:0~7<br>
									 Vertical grid line num = GVNUM + 1			*/
		ULONG			:13;	/**< Reserve									*/
	} bit;	/**< Bit field */
} U_IM_DISP_GNUM;

/**	GDCTL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	GCLRR	:8;	/**< GCLRR: Grid line display color R.<br>
								 Value range:0~255								*/
		ULONG	GCLRG	:8;	/**< GCLRG: Grid line display color G.<br>
								 Value range:0~255								*/
		ULONG	GCLRB	:8;	/**< GCLRB: Grid line display color B.<br>
								 Value range:0~255								*/
		ULONG	GALP	:2;	/**< GALP: Grid line alpha value setting.<br>
								 GALP=00b:grid line=25%, low rank layer=75%<br>
								 GALP=01b:grid line=50%, low rank layer=50%<br>
								 GALP=10b:grid line=75%, low rank layer=25%<br>
								 GALP=11b:grid line=100%, low rank layer=0%		*/
		ULONG			:6;	/**< Reserve										*/
	}bit;	/**< Bit field */
} U_IM_DISP_GDCTL;

/**	FFSIZE register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	FFHSZ	:16;	/**< FFHSZ: Face frame horizontal size.<br>
									 Value range:8~65534 (2-pixel unit)		*/
		ULONG	FFVSZ	:14;	/**< FFVSZ: Face frame vertical size.<br>
									 Value range:8~16382 (2-pixel unit)		*/
		ULONG			:2;		/**< Reserve								*/
	}bit;	/**< Bit field */
} U_IM_DISP_FFSIZE;

/**	FFWIDTH register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	FFHWID	:6;		/**< FFHSZ: Horizontal face frame width.<br>
									 Value range:2~62 (2-pixel unit)		*/
		ULONG			:10;	/**< Reserve								*/
		ULONG	FFVWID	:6;		/**< FFHSZ: Vertical face frame width.<br>
									 Value range:2~62 (2-pixel unit)		*/
		ULONG			:10;	/**< Reserve								*/
	}bit;	/**< Bit field */
} U_IM_DISP_FFWIDTH;

/**	FFCLR register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	FFCLRR	:8;	/**< FFCLRR: Face frame display color R.<br>
								 Value range:0~255						*/
		ULONG	FFCLRG	:8;	/**< FFCLRG: Face frame display color G.<br>
								 Value range:0~255						*/
		ULONG	FFCLRB	:8;	/**< FFCLRB: Face frame display color B.<br>
								 Value range:0~255						*/
		ULONG			:8;	/**< Reserve								*/
	}bit;	/**< Bit field */
} U_IM_DISP_FFCLR;

/** Image address. */
typedef struct {
	ULONG	y_addr;			/**< Y address<br>
								 Value range:0x00000000~0xFFFFFFFF<br>
								 Bit depth=8bit -> 2-byte unit<br>
								 Bit depth=12bit -> 3-byte unit<br>
								 Bit depth=16bit -> 4-byte unit		 		*/
	ULONG	c_addr;			/**< CbCr address<br>
								 Value range:0x00000000~0xFFFFFFFF<br>
								 Bit depth=8bit -> 2-byte unit<br>
								 Bit depth=12bit -> 3-byte unit<br>
								 Bit depth=16bit -> 4-byte unit		 		*/
} T_IM_DISP_IMAGE_ADDR;

/** Setting of YHLP data. */
typedef struct {
	U_IM_DISP_LYHLPCTL	lyhlpcl;	/**< YHLP processing setting register.				*/
	U_IM_DISP_LYHLPK	lyhlpk;		/**< YHLP filter coefficient setting 0/1 register.	*/
	U_IM_DISP_LYHLPOL	lyhlpol;	/**< Outline setting register.						*/
	U_IM_DISP_LYHLPCLR	lyhlpclr;	/**< Outline color setting register.				*/
} T_IM_DISP_YHLP;

/** Setting of Warning processing data. */
typedef struct {
	U_IM_DISP_LYWCTL	lywctl;		/**< Warning processing setting register.				*/
	U_IM_DISP_LYWTH		lyw0th;		/**< Range 0 - warning level setting register.			*/
	U_IM_DISP_LYWTH		lyw1th;		/**< Range 1 - warning level setting register.			*/
	E_IM_DISP_YWMD		lyw0st;		/**< Range 0 - warning processing mode select.<br>
										 <ul><li>@ref E_IM_DISP_YWMD_BR_RGB
											 <li>@ref E_IM_DISP_YWMD_BW_R
											 <li>@ref E_IM_DISP_YWMD_G
											 <li>@ref E_IM_DISP_YWMD_B</ul>					*/
	U_IM_DISP_LYWC		lyw0ca;		/**< Range 0 - warning color A.							*/
	U_IM_DISP_LYWC		lyw0cb;		/**< Range 0 - warning color B.							*/
	E_IM_DISP_YWMD		lyw1st;		/**< Range 1 - warning processing mode select.<br>
										 <ul><li>@ref E_IM_DISP_YWMD_BR_RGB
											 <li>@ref E_IM_DISP_YWMD_BW_R
											 <li>@ref E_IM_DISP_YWMD_G
											 <li>@ref E_IM_DISP_YWMD_B</ul>					*/
	U_IM_DISP_LYWC		lyw1ca;		/**< Range 1 - warning color A.							*/
	U_IM_DISP_LYWC		lyw1cb;		/**< Range 1 - warning color B.							*/
	ULONG				lbost;		/**< Warning display operation setting.<br>
										 <ul><li>@ref D_IM_DISP_BOMD_MASTER
											 <li>@ref D_IM_DISP_BOMD_SLAVE</ul>				*/
} T_IM_DISP_WARNING;

/** Setting of zebra warning (width, vertical, pattern). */
typedef struct {
	U_IM_DISP_LZBWID	lzbwid;		/**< LZBWID: Zebra width setting register.	*/
	U_IM_DISP_LZBV		lzbv;		/**< LZBV: Zebra vertical setting register.	*/
	U_IM_DISP_LZBPT		lzbpt;		/**< LZBPT: Zebra pattern setting register.	*/
} T_IM_DISP_ZEBRA;

/** Setting of grid. */
typedef struct {
	U_IM_DISP_DSTA		ghdsta;		/**< Display beginning position of horizontal grid.	*/
	U_IM_DISP_DSTA		gvdsta;		/**< Display beginning position of vertical grid.	*/
	U_IM_DISP_GLENGTH	glength;	/**< Grid length									*/
	U_IM_DISP_GWIDTH	gwidth;		/**< Grid width										*/
	U_IM_DISP_GITVL		gitvl;		/**< Grid interval									*/
	U_IM_DISP_GNUM		gnum;		/**< The number of Grid line						*/
	U_IM_DISP_GDCTL		gdctl;		/**< Grid setting									*/
} T_IM_DISP_GRID;

/*----------------------------------------------------------------------*/
/* Macro  																*/
/*----------------------------------------------------------------------*/
#ifdef CO_ACT_PCLOCK
// PCLK On
#define	Im_DISP_APB_Clock_On()		(Dd_Top_Start_Clock((UCHAR*)&gimDispApbClockCounter, &Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAP_ON))

// PCLK Off
#define	Im_DISP_APB_Clock_Off()		(Dd_Top_Stop_Clock((UCHAR*)&gimDispApbClockCounter, &Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAP_OFF))
#endif	// CO_ACT_PCLOCK

#ifdef CO_ACT_HCLOCK
// HCLK On
#define	Im_DISP_AHB_Clock_On()		(Dd_Top_Start_Clock((UCHAR*)&gimDispAhbClockCounter, &Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAH_ON))

// HCLK Off
#define	Im_DISP_AHB_Clock_Off()		(Dd_Top_Stop_Clock((UCHAR*)&gimDispAhbClockCounter, &Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAH_OFF))
#endif	// CO_ACT_HCLOCK

/*----------------------------------------------------------------------*/
/* Function  															*/
/*----------------------------------------------------------------------*/
VOID im_disp_pclk_on(ImDisp *self);
VOID im_disp_pclk_off(ImDisp *self);
VOID im_disp_hclk_on(ImDisp *self);
VOID im_disp_hclk_off(ImDisp *self);
VOID im_disp_access_gamma_table(ImDisp *self, BYTE* table_top,
									 const BYTE* register_table_top,
									 const E_IM_DISP_CORRECT_SELECT correct,
									 const E_IM_DISP_ACCESS_GAMMA access);
INT32 im_disp_wait_trg_stop_start(ImDisp *self, E_IM_DISP_SEL block, UINT32 layer, UINT32 act);
INT32 im_disp_set_trg(ImDisp *self, E_IM_DISP_SEL block, UINT32 layer, BYTE write_channel, E_IM_DISP_TRG start_stop);
UINT32 im_disp_get_event_flag(ImDisp *self, E_IM_DISP_INTERRUPTION_SELECT interrupt_type);
INT32 im_disp_get_cb_index(ImDisp *self, E_IM_DISP_INTERRUPTION_SELECT interrupt_type);

#endif /* __IM_DISP1_H__ */
