/*
 * imr2yctrl.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
*@author              :gonghaotian
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __IM_R2Y_CTRL_H__
#define __IM_R2Y_CTRL_H__

#include <klib.h>
#include "ddimtypedef.h"

#define IM_TYPE_R2Y_CTRL			(im_r2y_ctrl_get_type())
#define IM_R2Y_CTRL(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yCtrl))
#define IM_IS_R2Y_CTRL(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CTRL))

/** Function Enable
*/
#define	ImR2yCtrl_ENABLE_OFF						(0)						/**< Disable						*/
#define	ImR2yCtrl_ENABLE_ON						(1)						/**< Enable							*/

/** Wait Enable
*/
#define	ImR2yCtrl_WAIT_OFF						(0)						/**< Wait disable.					*/
#define	ImR2yCtrl_WAIT_ON						(1)						/**< Wait enable.					*/

/** Interrupt status(bit field)
*/
#define	ImR2yCtrl_INT_STATE_YYR_END1				(0x00000001)			/**< YYR: Normal end				*/
#define	ImR2yCtrl_INT_STATE_YYWALL_END1			(0x00000002)			/**< YYW0,0a,1 and 2: Normal end	*/
#define	ImR2yCtrl_INT_STATE_YYW0_END1			(0x00000004)			/**< YYW0: Normal end				*/
#define	ImR2yCtrl_INT_STATE_YYW0A_END1			(0x00000008)			/**< YYW0a: Normal end				*/
#define	ImR2yCtrl_INT_STATE_YYW1_END1			(0x00000010)			/**< YYW1: Normal end				*/
#define	ImR2yCtrl_INT_STATE_YYW2_END1			(0x00000020)			/**< YYW2: Normal end				*/
#define	ImR2yCtrl_INT_STATE_LINE0_END1			(0x00000040)			/**< YYW Line transferd 0			*/
#define	ImR2yCtrl_INT_STATE_LINE1_END1			(0x00000080)			/**< YYW Line transferd 1			*/
#define	ImR2yCtrl_INT_STATE_LINE2_END1			(0x00000100)			/**< YYW Line transferd 2			*/
#define	ImR2yCtrl_INT_STATE_YYR_ERR1				(0x00000200)			/**< YYR: Transfer error			*/
#define	ImR2yCtrl_INT_STATE_YYW_ERR1				(0x00000400)			/**< YYW0,0a,1 or 2: Transfer error	*/
#define	ImR2yCtrl_INT_STATE_AXR_ERR1				(0x00000800)			/**< AXI Read channel error			*/
#define	ImR2yCtrl_INT_STATE_AXW_ERR1				(0x00001000)			/**< AXI Write channel error		*/
#define	ImR2yCtrl_INT_STATE_YCFERR_ERR1			(0x00002000)			/**< F_R2Y YCFERR					*/
#define	ImR2yCtrl_INT_STATE_TCT_END1				(0x00004000)			/**< F_R2Y TCT Normal end			*/
#define	ImR2yCtrl_INT_STATE_TCHS_END1			(0x00008000)			/**< F_R2Y TCHS Normal end			*/
#define	ImR2yCtrl_INT_STATE_YYR_END2				(0x00010000)			/**< YYR: Normal end				*/
#define	ImR2yCtrl_INT_STATE_YYWALL_END2			(0x00020000)			/**< YYW0,0a,1 and 2: Normal end	*/
#define	ImR2yCtrl_INT_STATE_YYW0_END2			(0x00040000)			/**< YYW0: Normal end				*/
#define	ImR2yCtrl_INT_STATE_YYW0A_END2			(0x00080000)			/**< YYW0a: Normal end				*/
#define	ImR2yCtrl_INT_STATE_YYW1_END2			(0x00100000)			/**< YYW1: Normal end				*/
#define	ImR2yCtrl_INT_STATE_YYW2_END2			(0x00200000)			/**< YYW2: Normal end				*/
#define	ImR2yCtrl_INT_STATE_LINE0_END2			(0x00400000)			/**< YYW Line transferd 0			*/
#define	ImR2yCtrl_INT_STATE_LINE1_END2			(0x00800000)			/**< YYW Line transferd 1			*/
#define	ImR2yCtrl_INT_STATE_LINE2_END2			(0x01000000)			/**< YYW Line transferd 2			*/
#define	ImR2yCtrl_INT_STATE_YYR_ERR2				(0x02000000)			/**< YYR: Transfer error			*/
#define	ImR2yCtrl_INT_STATE_YYW_ERR2				(0x04000000)			/**< YYW0,0a,1 or 2: Transfer error	*/
#define	ImR2yCtrl_INT_STATE_AXR_ERR2				(0x08000000)			/**< AXI Read channel error			*/
#define	ImR2yCtrl_INT_STATE_AXW_ERR2				(0x10000000)			/**< AXI Write channel error		*/
#define	ImR2yCtrl_INT_STATE_YCFERR_ERR2			(0x20000000)			/**< F_R2Y YCFERR					*/
#define	ImR2yCtrl_INT_STATE_TCT_END2				(0x40000000)			/**< F_R2Y TCT Normal end			*/
#define	ImR2yCtrl_INT_STATE_TCHS_END2			(0x80000000)			/**< F_R2Y TCHS Normal end			*/

/** Interrupt flag for im_r2y_proc_waitend(im_r2y_proc_new(), ) (bit field)
*/
#define	ImR2yCtrl_INT_FLG_YYR_END1				(0x00000001)			/**< YYR: Normal end				*/
#define	ImR2yCtrl_INT_FLG_YYWALL_END1			(0x00000002)			/**< YYW0,0a,1 and 2: Normal end	*/
#define	ImR2yCtrl_INT_FLG_YYW0_END1				(0x00000004)			/**< YYW0: Normal end				*/
#define	ImR2yCtrl_INT_FLG_YYW0A_END1				(0x00000008)			/**< YYW0a: Normal end				*/
#define	ImR2yCtrl_INT_FLG_YYW1_END1				(0x00000010)			/**< YYW1: Normal end				*/
#define	ImR2yCtrl_INT_FLG_YYW2_END1				(0x00000020)			/**< YYW2: Normal end				*/
#define	ImR2yCtrl_INT_FLG_LINE0_END1				(0x00000040)			/**< YYW Line transferd 0			*/
#define	ImR2yCtrl_INT_FLG_LINE1_END1				(0x00000080)			/**< YYW Line transferd 1			*/
#define	ImR2yCtrl_INT_FLG_LINE2_END1				(0x00000100)			/**< YYW Line transferd 2			*/
#define	ImR2yCtrl_INT_FLG_YYR_ERR1				(0x00000200)			/**< YYR: Transfer error			*/
#define	ImR2yCtrl_INT_FLG_YYW_ERR1				(0x00000400)			/**< YYW0,0a,1 or 2: Transfer error	*/
#define	ImR2yCtrl_INT_FLG_AXR_ERR1				(0x00000800)			/**< AXI Read channel error			*/
#define	ImR2yCtrl_INT_FLG_AXW_ERR1				(0x00001000)			/**< AXI Write channel error		*/
#define	ImR2yCtrl_INT_FLG_YCFERR_ERR1			(0x00002000)			/**< F_R2Y YCFERR					*/
#define	D_IM_R2Y1_INT_FLG_TCT_END				(0x00004000)			/**< F_R2Y TCT Normal end			*/
#define	D_IM_R2Y1_INT_FLG_TCHS_END				(0x00008000)			/**< F_R2Y TCHS Normal end			*/
#define	D_IM_R2Y1_INT_FLG_ALL					(0x0000FFFF)			/**< All flags(PIPE1)				*/
#define	D_IM_R2Y2_INT_FLG_YYR_END				(0x00010000)			/**< YYR: Normal end				*/
#define	D_IM_R2Y2_INT_FLG_YYWALL_END			(0x00020000)			/**< YYW0,0a,1 and 2: Normal end	*/
#define	D_IM_R2Y2_INT_FLG_YYW0_END				(0x00040000)			/**< YYW0: Normal end				*/
#define	D_IM_R2Y2_INT_FLG_YYW0A_END				(0x00080000)			/**< YYW0a: Normal end				*/
#define	D_IM_R2Y2_INT_FLG_YYW1_END				(0x00100000)			/**< YYW1: Normal end				*/
#define	D_IM_R2Y2_INT_FLG_YYW2_END				(0x00200000)			/**< YYW2: Normal end				*/
#define	D_IM_R2Y2_INT_FLG_LINE0_END				(0x00400000)			/**< YYW Line transferd 0			*/
#define	D_IM_R2Y2_INT_FLG_LINE1_END				(0x00800000)			/**< YYW Line transferd 1			*/
#define	D_IM_R2Y2_INT_FLG_LINE2_END				(0x01000000)			/**< YYW Line transferd 2			*/
#define	D_IM_R2Y2_INT_FLG_YYR_ERR				(0x02000000)			/**< YYR: Transfer error			*/
#define	D_IM_R2Y2_INT_FLG_YYW_ERR				(0x04000000)			/**< YYW0,0a,1 or 2: Transfer error	*/
#define	D_IM_R2Y2_INT_FLG_AXR_ERR				(0x08000000)			/**< AXI Read channel error			*/
#define	D_IM_R2Y2_INT_FLG_AXW_ERR				(0x10000000)			/**< AXI Write channel error		*/
#define	D_IM_R2Y2_INT_FLG_YCFERR_ERR			(0x20000000)			/**< F_R2Y YCFERR					*/
#define	D_IM_R2Y2_INT_FLG_TCT_END				(0x40000000)			/**< F_R2Y TCT Normal end			*/
#define	D_IM_R2Y2_INT_FLG_TCHS_END				(0x80000000)			/**< F_R2Y TCHS Normal end			*/
#define	D_IM_R2Y2_INT_FLG_ALL					(0xFFFF0000)			/**< All flags(PIPE2)				*/
#define	D_IM_R2Y_INT_FLG_ALL					(0xFFFFFFFF)			/**< All flags						*/

/** Reading data type
*/
#define	ImR2yCtrl_READ_DTYP_PACK8				(0)						/**< 8bit							*/
#define	ImR2yCtrl_READ_DTYP_PACK12				(2)						/**< 12bit PACK						*/
#define	ImR2yCtrl_READ_DTYP_PACK16				(3)						/**< 16bit							*/
																		/* @YYRCTL.YYRDTYP	*/

/** Writing data type
*/
#define	ImR2yCtrl_WRITE_DTYP_PACK8				(0)						/**< 8bit							*/
#define	ImR2yCtrl_WRITE_DTYP_PACK10				(1)						/**< 10bit PACK						*/
#define	ImR2yCtrl_WRITE_DTYP_PACK12				(2)						/**< 12bit PACK						*/
#define	ImR2yCtrl_WRITE_DTYP_PACK16				(3)						/**< 16bit							*/
																		/* @YYW1MD.DTY1SL	*/

/** RGB data left shift
*/
#define	ImR2yCtrl_STL_RGB_LEFT_SHIFT_NONE		(0x0)					/**< Non shift.						*/
#define	ImR2yCtrl_STL_RGB_LEFT_SHIFT_1BIT		(0x1)					/**< Left shift 1bit.				*/
#define	ImR2yCtrl_STL_RGB_LEFT_SHIFT_2BIT		(0x2)					/**< Left shift 2bits.				*/
#define	ImR2yCtrl_STL_RGB_LEFT_SHIFT_4BIT		(0x3)					/**< Left shift 4bits.				*/
																		/* @YYRCTL.RGBLSFT	*/
/** Resize mode
*/
#define	ImR2yCtrl_RSZ_BILINEAR					(0)						/**< Bilinear interpolation method	*/
#define	ImR2yCtrl_RSZ_BICUBIC					(1)						/**< Bi-cubic interpolation method	*/
																		/* @YYW0MD.RSZ0MD, YYW1MD.RSZ1MD	*/
/** Burst length
*/
#define	ImR2yCtrl_BRST_512						(0)						/**< 512bytes burst					*/
#define	ImR2yCtrl_BRST_256						(1)						/**< 256bytes burst					*/
#define	ImR2yCtrl_BRST_128						(2)						/**< 128bytes burst					*/
																		/* @YYRAXMD.YYRBL, YYW0AXMD.YYW0BL, YYWAAXMD.YYWABL, YYW1AXMD.YYW1BL, YYW2AXMD.YYW2BL	*/

/** YCC CbCr sampling select
*/
#define	ImR2yCtrl_THIN_OUT_YCC444				(0x0)					/**< YCC444 output mode					*/
#define	ImR2yCtrl_THIN_OUT_YCC422_ODD			(0x8)					/**< YCC422 odd sampling output mode	*/
#define	ImR2yCtrl_THIN_OUT_YCC422_CENTER			(0xB)					/**< YCC422 center sampling output mode	*/
#define	ImR2yCtrl_THIN_OUT_YCC420_ODD			(0xC)					/**< YCC420 odd sampling output mode	*/
#define	ImR2yCtrl_THIN_OUT_YCC420_CENTER_LEFT	(0xD)					/**< YCC420 left columned center sampling output mode	*/
#define	ImR2yCtrl_THIN_OUT_YCC420_CENTER			(0xF)					/**< YCC420 center sampling output mode	*/
																		/* @YYW0MD.CSS0SL, YYW1MD.CSS1SL		*/

/** Planar/Dotter output format select
 */
#define	ImR2yCtrl_PORT_PLANAR					(0)						/**< Planar format						*/
#define	ImR2yCtrl_PORT_INTERLEAVED				(1)						/**< Color Interleaved format			*/
																		/* @YYW0MD.SPL0EN, YYW1MD.SPL1EN	*/

/** Output format(Video)
*/
#define	ImR2yCtrl_VFM_NORMAL						(0)						/**< Outout in normal format	*/
#define	ImR2yCtrl_VFM_VIDEO						(1)						/**< Outout in video format	*/
																		/* @YYW0MD.CH0VFM, YYW0MD.CHAVFM	*/

/** Output mode(ch0a)
*/
#define	ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP			(0)						/**< YYW/ch0a stops	*/
#define	ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_4_Y		(1)						/**< After 1/4 reduction, only Y data is output	*/
#define	ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_8_Y		(2)						/**< After 1/8 reduction, only Y data is output	*/
#define	ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_32_SP	(3)						/**< After 1/32 reduction, YCbCr data is output by semi-planar	*/
																		/* @YYW0MD.CH0AMD	*/

/** Output format(ch1)
*/
#define	ImR2yCtrl_DATA_FORMAT_8					(0)						/**< 8bit data format	*/
#define	ImR2yCtrl_DATA_FORMAT_10					(1)						/**< 10bit data format	*/
																		/* @YYW1MD.DFM1SL	*/

/** MCC select
*/
#define	ImR2yCtrl_MCC_AFTER_CC0					(0)						/**< MCC is performed after CC0	*/
#define	ImR2yCtrl_MCC_AFTER_GAMMA				(1)						/**< MCC is performed after gamma	*/
																		/* @R2YMODE.MCCSL	*/


/** YYW channel number
*/
#define ImR2yCtrl_YYW_CH_0						(0)						/**< YYW channel index number 0 */
#define ImR2yCtrl_YYW_CH_1						(1)						/**< YYW channel index number 1 */
#define ImR2yCtrl_YYW_CH_2						(2)						/**< YYW channel index number 2 */
#define ImR2yCtrl_YYW_CH_0A						(3)						/**< YYW channel index number 3 */
#define ImR2yCtrl_YYW_CH_MAX						(4)						/**< Maximum channel index number of YYW */

/** YCbCr/RGB component to be processed
*/
#define ImR2yCtrl_PORT_0							(0)						/**< Port0						*/
#define ImR2yCtrl_PORT_1							(1)						/**< Port1						*/
#define ImR2yCtrl_PORT_2							(2)						/**< Port2						*/
#define ImR2yCtrl_PORT_MAX						(3)						/**< The maximum values of YCbCr/RGB component to be processed */

/** Pipe No
*/
#define	ImR2yCtrl_PIPE1							(0)						/**< Pipe1.							*/
#define	ImR2yCtrl_PIPE2							(1)						/**< Pipe2.							*/
#define	ImR2yCtrl_PIPE12							(2)						/**< Pipe1&2						*/
#define	ImR2yCtrl_PIPE_MAX						(3)						/**< Max value						*/

/** YYW Master I/F select
*/
#define	ImR2yCtrl_MASTER_IF0_PORT0				(0x00)					/**< YYW Ch0(Port0) Master I/F 0 select			*/
#define	ImR2yCtrl_MASTER_IF0_PORT1				(0x00)					/**< YYW Ch1(Port1) Master I/F 0 select			*/
#define	ImR2yCtrl_MASTER_IF0_PORT2				(0x00)					/**< YYW Ch2(Port2) Master I/F 0 select			*/
#define	ImR2yCtrl_MASTER_IF1_PORT0				(0x01)					/**< YYW Ch0(Port0) Master I/F 1 select			*/
#define	ImR2yCtrl_MASTER_IF1_PORT1				(0x04)					/**< YYW Ch1(Port1) Master I/F 1 select			*/
#define	ImR2yCtrl_MASTER_IF1_PORT2				(0x10)					/**< YYW Ch2(Port2) Master I/F 1 select			*/
#define	ImR2yCtrl_MASTER_IF2_PORT0				(0x02)					/**< YYW Ch0(Port0) Master I/F 2 select			*/
#define	ImR2yCtrl_MASTER_IF2_PORT1				(0x08)					/**< YYW Ch1(Port1) Master I/F 2 select			*/
#define	ImR2yCtrl_MASTER_IF2_PORT2				(0x20)					/**< YYW Ch2(Port2) Master I/F 2 select			*/
#define	ImR2yCtrl_MASTER_IF3_PORT0				(0x03)					/**< YYW Ch0(Port0) Master I/F 3 select			*/
#define	ImR2yCtrl_MASTER_IF3_PORT1				(0x0C)					/**< YYW Ch1(Port1) Master I/F 3 select			*/
#define	ImR2yCtrl_MASTER_IF3_PORT2				(0x30)					/**< YYW Ch2(Port2) Master I/F 3 select			*/
																		/* @YYW0MSL, YYWAMSL(PORT0&1), YYW1MSL, YYW2MSL(PORT0 only) */

/** Maximum of Table size
*/
// F_R2Y
#define ImR2yCtrl_TABLE_MAX_TONE					(1024)					/**< Tone Control table array number					*/
#define ImR2yCtrl_TABLE_MAX_TCT					(1200)					/**< Luminance evaluation value table array number		*/
#define ImR2yCtrl_TABLE_MAX_BTC_HISTOGRAM_Y		(4096)					/**< Histogram data(Y) table array number(before TC)	*/
#define ImR2yCtrl_TABLE_MAX_BTC_HISTOGRAM_RGB	(256)					/**< Histogram data(RGB) table array number(before TC)	*/
#define ImR2yCtrl_TABLE_MAX_GAMMA				(256)					/**< Gamma table array number 							*/
#define ImR2yCtrl_TABLE_MAX_EDGE_SCALE_HI		(512)					/**< High frequency Edge Scale table array number		*/
#define ImR2yCtrl_TABLE_MAX_EDGE_TC_HI			(256)					/**< High frequency Edge Tc table array number			*/
#define ImR2yCtrl_TABLE_MAX_EDGE_SCALE_MEDIUM	(512)					/**< Medium frequency Edge Scale table array number		*/
#define ImR2yCtrl_TABLE_MAX_EDGE_TC_MEDIUM		(256)					/**< Medium frequency Edge Tc table array number		*/
#define ImR2yCtrl_TABLE_MAX_EDGE_SCALE_LO		(512)					/**< Low frequency edge Scale table array number		*/
#define ImR2yCtrl_TABLE_MAX_EDGE_TC_LO			(256)					/**< Low frequency edge Tc table array number			*/
#define ImR2yCtrl_TABLE_MAX_MAPSCL				(221)					/**< Map Scale table array number (13 x 17)				*/

// JDSR2Y
#define ImR2yCtrl_TABLE_MAX_HISTOGRAM			(128)					/**< Histogram data table array number				*/
#define ImR2yCtrl_TABLE_MAX_RGB_DEKNEE			(256)					/**< JDSR2Y RGB Deknee table array number			*/


// YCbCr(planar)
#define	ImR2yCtrl_PORT_Y							(ImR2yCtrl_PORT_0)		/**< Y data						*/
#define	ImR2yCtrl_PORT_CB						(ImR2yCtrl_PORT_1)		/**< Cb data (planar)			*/
#define	ImR2yCtrl_PORT_CR						(ImR2yCtrl_PORT_2)		/**< Cr data (planar)			*/
// YCbCr(semi-planar)
#define	ImR2yCtrl_PORT_CBCR						(ImR2yCtrl_PORT_1)		/**< CbCr data (semi-planar)	*/
// RGB
#define	ImR2yCtrl_PORT_R							(ImR2yCtrl_PORT_0)		/**< R data						*/
#define	ImR2yCtrl_PORT_G							(ImR2yCtrl_PORT_1)		/**< G data						*/
#define	ImR2yCtrl_PORT_B							(ImR2yCtrl_PORT_2)		/**< B data						*/
#define	ImR2yCtrl_PORT_GRAY						(ImR2yCtrl_PORT_0)		/**< Gray data					*/


/** Line interrupt channel number
 */
#define ImR2yCtrl_LINE_INT_0						(0)						/**< Line interrupt index number 0 */
#define ImR2yCtrl_LINE_INT_1						(1)						/**< Line interrupt index number 1 */
#define ImR2yCtrl_LINE_INT_2						(2)						/**< Line interrupt index number 2 */
#define ImR2yCtrl_LINE_INT_MAX					(3)						/**< Maximum channel index number of Line interrupt */

/** YYW output bank number
*/
#define ImR2yCtrl_YYW_BANK_0						(0)						/**< YYW output bank index number 0 */
#define ImR2yCtrl_YYW_BANK_1						(1)						/**< YYW output bank index number 1 */
#define ImR2yCtrl_YYW_BANK_2						(2)						/**< YYW output bank index number 2 */
#define ImR2yCtrl_YYW_BANK_3						(3)						/**< YYW output bank index number 3 */
#define ImR2yCtrl_YYW_BANK_MAX					(4)						/**< Maximum output bank index number of YYW */

/** Histogram sampling pitch
 */
#define	ImR2yCtrl_HIST_PIT_2X2					(0)						/**< 1pixel in 2x2 area			*/
#define	ImR2yCtrl_HIST_PIT_4X4					(1)						/**< 1pixel in 4x4 area			*/
#define	ImR2yCtrl_HIST_PIT_8X8					(2)						/**< 1pixel in 8x8 area			*/
#define	ImR2yCtrl_HIST_PIT_16X16					(3)						/**< 1pixel in 16x16 area		*/
																		/* @HSTMD.PIT_M */

/** Transferred subject to the interrupt line number
*/
#define	ImR2yCtrl_LINT_YYW_CH0					(0)						/**< Monitoring of the number of lines transferred the YYW/ch0	*/
#define	ImR2yCtrl_LINT_YYW_CH1					(1)						/**< Monitoring of the number of lines transferred the YYW/ch1	*/
																		/* @LINTSEL.LINTS */

/** Transferred subject to the interrupt line number
*/
#define	ImR2yCtrl_RDC_MODE_DIV_2					(0)						/**< Reduction 1/2 -> H:2 x V:2 = Find the average of the 4 pixels	*/
#define	ImR2yCtrl_RDC_MODE_DIV_4					(1)						/**< Reduction 1/4 -> H:4 x V:4 = Find the average of the 16 pixels	*/
#define	ImR2yCtrl_RDC_MODE_DIV_8					(2)						/**< Reduction 1/8 -> H:8 x V:8 = Find the average of the 64 pixels	*/
																		/* @YYW0MD.RDC0MD, YYW1MD.RDC1MD, YYW2MD.RDC2MD */
#define	ImR2yCtrl_RDC_MODE_DIV_DIS				(3)						/**< Reduction disable	*/

/** Gamma correction mode
*/
#define	ImR2yCtrl_GAMMA_MODE_12					(0)						/**< 12bit input difference type gamma correction mode	*/
#define	ImR2yCtrl_GAMMA_MODE_10					(1)						/**< 10bit input gamma correction mode	*/
																		/* @GMCTL.GMMD */

#define ImR2yCtrl_TABLE_MAX_VAL					(32767)					/**< Maximum value of Histogram data */

// Output Address array maximum number
#define ImR2yCtrl_ADDR_INDEX_MAX					(ImR2yCtrl_YYW_BANK_MAX)	/**< Maximum number of R2Y output address information(bank0 ~ 3)	*/

// RSZ0HSTA, RSZ0HPIT, RSZ0VSTA, RSZ0VPIT, RSZ1HSTA, RSZ1HPIT, RSZ1VSTA, RSZ1VPIT, RSZ2HSTA, RSZ2HPIT, RSZ2VSTA, RSZ2VPIT register value mean "1.0"
#define ImR2yCtrl_STA_PIT_1_0					(0x4000)				/**< RSZxxSTA, RSZxxPIT register value mean "1.0" */

/** Histogram horizontal sampling interval
 */
#define	ImR2yCtrl_HIST_HCYC_4					(0)						/**< 4pixel				*/
#define	ImR2yCtrl_HIST_HCYC_8					(1)						/**< 8pixel				*/
#define	ImR2yCtrl_HIST_HCYC_16					(2)						/**< 16pixel			*/
																		/* @TCHSCTL.TCHSHCYC */

/** Histogram vertical sampling interval
 */
#define	ImR2yCtrl_HIST_VCYC_1					(0)						/**< 1lines				*/
#define	ImR2yCtrl_HIST_VCYC_2					(1)						/**< 2lines				*/
#define	ImR2yCtrl_HIST_VCYC_4					(2)						/**< 4lines				*/
#define	ImR2yCtrl_HIST_VCYC_8					(3)						/**< 8lines				*/
#define	ImR2yCtrl_HIST_VCYC_16					(4)						/**< 16lines			*/
																		/* @TCHSCTL.TCHSVCYC */

/** RGB Histogram mode
 */
#define	ImR2yCtrl_HIST_BIT_WIDTH_7_0				(0)						/**< Detection bit range[7:0]	Detection maximum value:0xFF		*/
#define	ImR2yCtrl_HIST_BIT_WIDTH_8_1				(1)						/**< Detection bit range[8:1]	Detection maximum value:0x1FF		*/
#define	ImR2yCtrl_HIST_BIT_WIDTH_9_2				(2)						/**< Detection bit range[9:2]	Detection maximum value:0x3FF		*/
#define	ImR2yCtrl_HIST_BIT_WIDTH_10_3			(3)						/**< Detection bit range[10:3]	Detection maximum value:0x7FF		*/
#define	ImR2yCtrl_HIST_BIT_WIDTH_11_4			(4)						/**< Detection bit range[11:4]	Detection maximum value:0xFFF		*/
																		/* @TCHSCTL.TCHSRGBMD */

/** TC table reference resolution
 */
#define	ImR2yCtrl_TC_RESOLUTION_1024				(0)						/**< 1024 gradations				*/
#define	ImR2yCtrl_TC_RESOLUTION_512				(1)						/**<  512 gradations				*/
#define	ImR2yCtrl_TC_RESOLUTION_256				(2)						/**<  256 gradations				*/
																		/* @TCCTL.TCRES */

/** Edge enhancement edge noise reduction mode
 */
#define	ImR2yCtrl_EGSMT_VERSION1					(0)						/**< Edge noise reduction ver.1		*/
#define	ImR2yCtrl_EGSMT_VERSION2					(1)						/**< Edge noise reduction ver.2		*/
																		/* @EGSMCTL.EGSMT */

#define ImR2yCtrl_YYRTRG_IDLE			(2)

#define ImR2yCtrl_YYR_IS_ACTIVATED(a)					(gImIoR2yRegPtr[a]->YYR.YYRTRG.bit.YYRTRG != ImR2yCtrl_YYRTRG_IDLE)




typedef struct 				_ImR2yCtrl ImR2yCtrl;
typedef struct 				_ImR2yCtrlPrivate ImR2yCtrlPrivate;




struct _ImR2yCtrl {
	KObject parent;
};

/** Post-resize edge enhancement0 control information
*/
typedef struct {
	kuint16					edgeEnable;							/**< EE0CTL.EE0EN : Post-resize edge enhancement 0 enable (1bit)					*/
	kuint16					gradation_enable;						/**< EE0CTL.EE0TC : Gradation adjustment enable (1bit)								*/
	kint16					hpfK[6];								/**< EE0HPFK : High pass filter coefficient K0-K5.<br>
																					 EE0HPFK0(10bits unsigned), EE0HPFK1-EE0HPFK5(8bits signed).		*/
	kuint16					strength;								/**< EE0NRLV : Noise reduction strength (4bits 0~8)									*/
	kuint16					coring_p_offset[4];						/**< EE0CORPOF 0-3 : Coring positive direction offset (8bits)						*/
	INT8					coring_p_gain[4];						/**< EE0CORPGA 0-3 : Coring positive direction gain (8bits signed)					*/
	kuint16					coring_p_border[3];						/**< EE0CORPBD 1-3 : Coring positive direction area boundary (8bits)				*/
	kuint16					coring_m_offset[4];						/**< EE0CORMOF 0-3 : Coring negative direction offset (8bits)						*/
	INT8					coring_m_gain[4];						/**< EE0CORMGA 0-3 : Coring negative direction gain (8bits signed)					*/
	kuint16					coring_m_border[3];						/**< EE0CORMBD 1-3 : Coring negative direction area boundary (8bits)				*/
	kuint16					scale_reduct_coef;						/**< EE0SCLSUP : Scale reduction coefficient (6bits)								*/
	kuint16					scale_p_offset[10];						/**< EE0SCLPOF 0-9 : Scale positive direction offset (8bits)						*/
	kint16					scale_p_gain[10];						/**< EE0SCLPGA 0-9 : Scale positive direction gain (13bits signed)					*/
	kuint16					scale_p_border[9];						/**< EE0SCLPBD 1-9 : Scale positive direction area boundary (8bits)					*/
	kuint16					scale_m_offset[10];						/**< EE0SCLMOF 0-9 : Scale negative direction offset (8bits)						*/
	kint16					scale_m_gain[10];						/**< EE0SCLMGA 0-9 : Scale negative direction gain (13bits signed)					*/
	kuint16					scale_m_border[9];						/**< EE0SCLMBD 1-9 : Scale negative direction area boundary (8bits)					*/
	kuint16					gradation_p_offset[5];					/**< EE0TONPOF 0-4 : Gradation adjustment positive direction offset (7bits)			*/
	kint16					gradation_p_gain[5];					/**< EE0TONPGA 0-4 : Gradation adjustment positive direction gain (9bits signed)	*/
	kuint16					gradation_p_border[4];					/**< EE0TONPBD 1-4 : Gradation adjustment positive direction area boundary (7bits)	*/
	kuint16					gradation_m_offset[5];					/**< EE0TONMOF 0-4 : Gradation adjustment negative direction offset (7bits)			*/
	kint16					gradation_m_gain[5];					/**< EE0TONMGA 0-4 : Gradation adjustment negative direction gain (9bits signed)	*/
	kuint16					gradation_m_border[4];					/**< EE0TONMBD 1-4 : Gradation adjustment negative direction area boundary (7bits)	*/
	kuint16					levelClipPOffset[3];					/**< EE0CLPPOF 0-2 : Level clip positive direction offset (7bits)					*/
	INT8					levelClipPGain[3];					/**< EE0CLPPGA 0-2 : Level clip positive direction gain (8bits signed)				*/
	kuint16					levelClipPBorder[2];					/**< EE0CLPPBD 1-2 : Level clip positive direction area boundary (8bits)			*/
	kuint16					levelClipMOffset[3];					/**< EE0CLPMOF 0-2 : Level clip negative direction offset (7bits)					*/
	INT8					levelClipMGain[3];					/**< EE0CLPMGA 0-2 : Level clip negative direction gain (8bits signed)				*/
	kuint16					levelClipMBorder[2];					/**< EE0CLPMBD 1-2 : Level clip negative direction area boundary (8bits)			*/
} R2yPostResize0Param;

/** Post-resize edge enhancement1 control information
*/
typedef struct {
	kuint16					edgeEnable;							/**< EE1CTL.EE1EN : Post-resize edge enhancement 1 enable (1bit)					*/
	kuint16					gradation_enable;						/**< EE1CTL.EE1TC : Gradation adjustment enable (1bit)								*/
	kint16					hpfK[6];								/**< EE1HPFK : High pass filter coefficient K0-K5.<br>
																					 EE0HPFK0(10bits unsigned), EE0HPFK1-EE0HPFK5(8bits signed).		*/
	kuint16					strength;								/**< EE1NRLV : Noise reduction strength (4bits 0~8)									*/
	kuint16					coring_p_offset[4];						/**< EE1CORPOF 0-3 : Coring positive direction offset (10bits)						*/
	INT8					coring_p_gain[4];						/**< EE1CORPGA 0-3 : Coring positive direction gain (8bits signed)					*/
	kuint16					coring_p_border[3];						/**< EE1CORPBD 1-3 : Coring positive direction area boundary (10bits)				*/
	kuint16					coring_m_offset[4];						/**< EE1CORMOF 0-3 : Coring negative direction offset (10bits)						*/
	INT8					coring_m_gain[4];						/**< EE1CORMGA 0-3 : Coring negative direction gain (8bits signed)					*/
	kuint16					coring_m_border[3];						/**< EE1CORMBD 1-3 : Coring negative direction area boundary (10bits)				*/
	kuint16					scale_reduct_coef;						/**< EE1SCLSUP : Scale reduction coefficient (6bits)								*/
	kuint16					scale_p_offset[10];						/**< EE1SCLPOF 0-9 : Scale positive direction offset (8bits)						*/
	kint16					scale_p_gain[10];						/**< EE1SCLPGA 0-9 : Scale positive direction gain (13bits signed)					*/
	kuint16					scale_p_border[9];						/**< EE1SCLPBD 1-9 : Scale positive direction area boundary (10bits)				*/
	kuint16					scale_m_offset[10];						/**< EE1SCLMOF 0-9 : Scale negative direction offset (8bits)						*/
	kint16					scale_m_gain[10];						/**< EE1SCLMGA 0-9 : Scale negative direction gain (13bits signed)					*/
	kuint16					scale_m_border[9];						/**< EE1SCLMBD 1-9 : Scale negative direction area boundary (10bits)				*/
	kuint16					gradation_p_offset[5];					/**< EE1TONPOF 0-4 : Gradation adjustment positive direction offset (9bits)			*/
	kint16					gradation_p_gain[5];					/**< EE1TONPGA 0-4 : Gradation adjustment positive direction gain (9bits signed)	*/
	kuint16					gradation_p_border[4];					/**< EE1TONPOF 1-4 : Gradation adjustment positive direction area boundary (9bits)	*/
	kuint16					gradation_m_offset[5];					/**< EE1TONMOF 0-4 : Gradation adjustment negative direction offset (9bits)			*/
	kint16					gradation_m_gain[5];					/**< EE1TONMGA 0-4 : Gradation adjustment negative direction gain (9bits signed)	*/
	kuint16					gradation_m_border[4];					/**< EE1TONMOF 1-4 : Gradation adjustment negative direction area boundary (9bits)	*/
	kuint16					levelClipPOffset[3];					/**< EE1CLPPOF 0-2 : Level clip positive direction offset (9bits)					*/
	INT8					levelClipPGain[3];					/**< EE1CLPPGA 0-2 : Level clip positive direction gain (8bits signed)				*/
	kuint16					levelClipPBorder[2];					/**< EE1CLPPBD 1-2 : Level clip positive direction area boundary (10bits)			*/
	kuint16					levelClipMOffset[3];					/**< EE1CLPMOF 0-2 : Level clip negative direction offset (9bits)					*/
	INT8					levelClipMGain[3];					/**< EE1CLPMGA 0-2 : Level clip negative direction gain (8bits signed)				*/
	kuint16					levelClipMBorder[2];					/**< EE1CLPMBD 1-2 : Level clip negative direction area boundary (10bits)			*/
} R2yPostResize1Param;

/** Tone control
*/
typedef struct {
	kuint16			tone_enable;				/**< TCCTL.TCEN : TC RGB enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform TC to RGB.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs TC to RGB.</ul>					*/
	kuint16			tone_yb_enable;				/**< TCCTL.TCYBEN : TC luminance Yb enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform TC to luminance Yb.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs TC to luminance Yb.</ul>			*/
	kuint16			table_blend_enable;			/**< TCCTL.TCBLEN : TC table blend enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform blend.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs blend.</ul>						*/
	kuint16			table_resol;				/**< TCCTL.TCRES : TC table reference resolution (2bits 0 ~ 2)
												<ul><li>@ref ImR2yCtrl_TC_RESOLUTION_1024
													<li>@ref ImR2yCtrl_TC_RESOLUTION_512
													<li>@ref ImR2yCtrl_TC_RESOLUTION_256</ul>								*/
	kuint16			table_select;				/**< TCCTL.TCTBL : Tone control table select (2bits 0 ~ 3)					*/
	kuint16			ytc_out;					/**< TCCTL.TCYOUT : TC YTc output selection (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : YTc = Y(coefficient "TCYC").
													<li>@ref ImR2yCtrl_ENABLE_ON : YTc = Yb(coefficient "CCYC").</ul>		*/
	kuint16			int_bit;					/**< TCCTL.TCINTBIT : TC data integral part selection(used to set the format of TC and TCEP). (2bits)	*/
	kuint16			table_blend_ratio;			/**< TCTBLCTL.TCBLND : TC table blend ratio (6bits 0 ~ 31)					*/
	kuint16			yc_matrix[3];				/**< TCYC : Tone control YC matrix (8bits)									*/
	kuint16			table_endp[4];				/**< TCEP : Tone control end point table (15bits)							*/
	kuint16			clipPR;					/**< TCCLPR.TCCLPRP : R component after TC positive direction clip(12bit)	*/
	kuint16			clipMR;					/**< TCCLPR.TCCLPRM : R component after TC negative direction clip(12bit)	*/
	kuint16			clipPG;					/**< TCCLPG.TCCLPGP : G component after TC positive direction clip(12bit)	*/
	kuint16			clipMG;					/**< TCCLPG.TCCLPGM : G component after TC negative direction clip(12bit)	*/
	kuint16			clipPB;					/**< TCCLPB.TCCLPBP : B component after TC positive direction clip(12bit)	*/
	kuint16			clipMB;					/**< TCCLPB.TCCLPBM : B component after TC negative direction clip(12bit)	*/
} ImR2yCtrlTone;

/** Offset control of RGB data
*/
typedef struct {
	kint16			R;							/**< OFSTR : Control of R pixel (10bits signed)	*/
	kint16			G;							/**< OFSTG : Control of G pixel (10bits signed)	*/
	kint16			B;							/**< OFSTB : Control of B pixel (10bits signed)	*/
} ImR2yCtrlOfs;									/* Offset control data	*/

KConstType 		   	 	im_r2y_ctrl_get_type(void);
ImR2yCtrl*		        im_r2y_ctrl_new(void);

/**
Post-resize edge enhancement0 control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_post_resize	: pointer of Post resize edge enhancement control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl_post_resize_edge0(ImR2yCtrl *self, kuint16 pipeNo, const R2yPostResize0Param* const r2y_ctrl_post_resize );

/**
Post-resize edge enhancement1 control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_post_resize	: pointer of Post resize edge enhancement control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl_post_resize_edge1(ImR2yCtrl *self, kuint16 pipeNo, const R2yPostResize1Param* const r2y_ctrl_post_resize );

/**
Offset Control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		ofs						: pointer of offset parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_set_offset(ImR2yCtrl *self, kuint16 pipeNo, const ImR2yCtrlOfs* const ofs );

/**
Tone Control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_tone			: pointer of Tone control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl_tone(ImR2yCtrl *self, kuint16 pipeNo, const ImR2yCtrlTone* const r2y_ctrl_tone );

/**
Set Tone control table access enable
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tc_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: ImR2yCtrl_WAIT_OFF : Turn off wait. / ImR2yCtrl_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_MACRO_BUSY		: Macro busy error.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_set_tone_control_tbl_access_enable(ImR2yCtrl *self, kuint16 pipeNo, kuint16 tc_enable, kuint16 wait_enable );

/**
Is Tone Control active
@param[in]		pipeNo	: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		active_status			: Tone control status(active/inactive).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_is_act_tone(ImR2yCtrl *self, kuint16 pipeNo, kuint16* const active_status );

#endif /* __IM_R2Y_CTRL_H__ */
