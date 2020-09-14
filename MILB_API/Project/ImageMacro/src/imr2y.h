/*
 * imr2y.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
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

#ifndef __IM_R2Y_H__
#define __IM_R2Y_H__

#include <klib.h>
#include "driver_common.h"
#include "ddimtypedef.h"
#include "ddimusercustom.h"
#include "jdsr2y.h"
#include "imr2yctrl.h"
#include "imr2yctrl2.h"

#define IM_TYPE_R2Y		(im_r2y_get_type())
#define IM_R2Y(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2y))
#define IM_IS_R2Y(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y))

//外部调用
#if 1
#ifdef CO_DEBUG_PRINT_XX_YYY
#ifndef IM_R2Y_STATUS_PRINT
#define CO_DEBUG_PRINT_IM_R2Y	/**< DEBUG */
#endif
#endif
#endif
#ifdef CO_DEBUG_PRINT_IM_R2Y
#ifndef IM_R2Y_STATUS_PRINT
#define IM_R2Y_STATUS_PRINT		/**< DEBUG */
#endif
#endif





/** RGB table type(for Deknee).
 */
typedef enum {
	ImR2y_DKN_RGBTBL_R = 0,			/**< R color table. */
	ImR2y_DKN_RGBTBL_G,				/**< G color table. */
	ImR2y_DKN_RGBTBL_B,				/**< B color table. */
	ImR2y_DKN_RGBTBL_MAX,			/**< Maximum value. */
} ER2yDknRgbtbl;

/** RGB table type(for Histogram before TC).
 */
typedef enum {
	ImR2y_BTC_HIST_RGBTBL_R = 0,	/**< R component data table. */
	ImR2y_BTC_HIST_RGBTBL_G,		/**< G component data table. */
	ImR2y_BTC_HIST_RGBTBL_B,		/**< B component data table. */
	ImR2y_BTC_HIST_RGBTBL_Y,		/**< Y component data table. */
	ImR2y_BTC_HIST_RGBTBL_MAX,		/**< Maximum value. */
} R2yBtcHistRgbtbl;

typedef struct 				_ImR2y ImR2y;
typedef struct 				_ImR2yPrivate ImR2yPrivate;

struct _ImR2y {
	KObject parent;
};


/** AXI bus I/F control
*/
typedef struct {
	kuint16					cacheType;								/**< cache type (4bits)				*/
	kuint16					protectType;							/**< protect type (3bits)			*/
} CtrlAxiType;

/** AXI bus I/F control
*/
typedef struct {
	CtrlAxiType	yyr[ImR2yCtrl_PORT_MAX];							/**< YYRAXCTL.YYRCACHE_x, YYRAXCTL.YYRPROT_x YYR Read channel types.	*/
	CtrlAxiType	yyw[ImR2yCtrl_YYW_CH_MAX][ImR2yCtrl_PORT_MAX];	/**< YYW0AXCTL.YYW0CACHE[3], YYW0AXCTL.YYW0PROT[3],<br>
																				 YYW1AXCTL.YYW1CACHE[3], YYW1AXCTL.YYW1PROT[3],<br>
																				 YYW2AXCTL.YYW2CACHE, YYW2AXCTL.YYW2PROT,<br>
																				 YYWAAXCTL.YYWACACHE[2], YYWAAXCTL.YYWAPROT[2]<br>
																				 YYW Write channel types.											*/
} TImR2yCtrlAxi;

/** AXI bus read channel status
*/
typedef struct {
	kuint16					yyrAxiStat[ImR2yCtrl_PORT_MAX];		/**< YYRAXSTS.YYRRESP_x : Read channel status (2bits)	*/
} AxiYyrStat;

/** AXI bus write channel status
*/
typedef struct {
	kuint16					yyw0AxiStat[ImR2yCtrl_PORT_MAX];		/**< YYW0AXSTS.YY0BRESP[3] : Write channel status (2bits)	*/
	kuint16					yyw0aAxiStat[ImR2yCtrl_PORT_MAX-1];	/**< YYWAAXSTS.YYABRESP[2] : Write channel status (2bits)	*/
	kuint16					yyw1AxiStat[ImR2yCtrl_PORT_MAX];		/**< YYW1AXSTS.YY1BRESP[3] : Write channel status (2bits)	*/
	kuint16					yyw2AxiStat;							/**< YYW2AXSTS.YY2BRESP : Write channel status (2bits)		*/
} AxiYywStat;

/** AXI bus write channel status
*/
typedef struct {
	kuint16					masterIfSelect;						/**< Master I/F select.<br>
																		YYW0AXMD.YYW0MSL, YYW1AXMD.YYW1MSL : (6bits)<br>
																		Set bit-OR parameter between YYW0/YYW1 Ch0-Ch2.<br>
																		YYWAAXMD.YYWAMSL : (4bits)<br>
																		Set bit-OR parameter between YYW0a Ch0-Ch1.<br>
																		YYW2AXMD.YYW2MSL : (2bits)<br>
																		Set bit-OR parameter between YYW2 Ch0.<br>
																		YYW0/YYW0a/YYW1/YYW2 Ch0(Port0):<br>
																	<ul><li>@ref ImR2yCtrl_MASTER_IF0_PORT0
																		<li>@ref ImR2yCtrl_MASTER_IF1_PORT0
																		<li>@ref ImR2yCtrl_MASTER_IF2_PORT0
																		<li>@ref ImR2yCtrl_MASTER_IF3_PORT0</ul>
																	YYW0/YYW0a/YYW1 Ch1(Port1):<br>
																	<ul><li>@ref ImR2yCtrl_MASTER_IF0_PORT1
																		<li>@ref ImR2yCtrl_MASTER_IF1_PORT1
																		<li>@ref ImR2yCtrl_MASTER_IF2_PORT1
																		<li>@ref ImR2yCtrl_MASTER_IF3_PORT1</ul>
																	YYW0/YYW1 Ch2(Port2):<br>
																	<ul><li>@ref ImR2yCtrl_MASTER_IF0_PORT2
																		<li>@ref ImR2yCtrl_MASTER_IF1_PORT2
																		<li>@ref ImR2yCtrl_MASTER_IF2_PORT2
																		<li>@ref ImR2yCtrl_MASTER_IF3_PORT2</ul>										*/
	kuint16					burstLength;							/**< YYW0AXMD.YYW0BL, YYWAAXMD.YYWABL,<br>
																		 YYW1AXMD.YYW1BL, YYW2AXMD.YYW2BL : Transfer burst length (2bits)
																	<ul><li>@ref ImR2yCtrl_BRST_512
																		<li>@ref ImR2yCtrl_BRST_256
																		<li>@ref ImR2yCtrl_BRST_128</ul>												*/
	kuint16					outEnable[ImR2yCtrl_PORT_MAX];			/**< Set of componentsto be output to the external memory.<br>
																		 YYW0AXMD.YYW0DOE, YYW1AXMD.YYW1DOE : Y/Cb/Cr(planar) or Y/CbCr(semi-planar) (3bits)
																		 YYWAAXMD.YYWADOE					: Y/CbCr(semi-planar) (2bits)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not transfer component data to master I/F
																		<li>@ref ImR2yCtrl_ENABLE_ON : Transfers component data to master I/F</ul>	*/
} AxiYywMode;

/** R2Y Window size
*/
typedef struct {
	kuint16					yywWidth;								/**< image width(YYW0/1/2)																		*/
	kuint16					yywLines;								/**< image lines(YYW0/1/2)																		*/
	INT32					outputGlobalW[ImR2yCtrl_PORT_MAX];		/**< YYW0DEF[2], YYWADEF, YYW1DEF[2], YYW2DEF : Output Horizontal global bytes (17 bits signed)	*/
} R2yWindowsSize;


/** R2Y Pitch
*/
typedef struct {
	UINT32					outputXStartPos;						/**< resize horizontal start pos<br>
																		 RSZ0HSTA, RSZ1HSTA : Bilinear (0 ~ 63 + 16383/16384)<br>
																							  Bi-cubic (1 ~ 63 + 16383/16384)<br>
																		 RSZ2HSTA : 		  (0 ~ 63 + 16383/16384)												*/
	UINT32					outputXPitch;							/**< RSZ0HPIT, RSZ1HPIT, RSZ2HPIT : resize horizontal pitch (2048/16384 ~ 32768/16384)			*/
	UINT32					outputYStartPos;						/**< resize vertical start pos
																		 RSZ0VSTA, RSZ1VSTA : Bilinear (0 ~ 63 + 16383/16384)<br>
																							  Bi-cubic (1 ~ 63 + 16383/16384)<br>
																		 RSZ2VSTA : 		  (0 ~ 63 + 16383/16384)												*/
	UINT32					outputYPitch;							/**< RSZ0VPIT, RSZ1VPIT, RSZ2VPIT : resize vertical pitch (2048/16384 ~ 32768/16384)			*/
	INT32					outputGlobalW[ImR2yCtrl_PORT_MAX];		/**< YYW0DEF[2], YYW1DEF[2], YYW2DEF, YYWADEF : Output Horizontal global bytes (17 bits signed)	*/
} TImR2yPitch;

/** YYW control
*/
typedef struct {
	AxiYywMode			axiWriteMode;							/**< AXI bus write channel control parameters										*/
	kuint16					writeRequestMask[ImR2yCtrl_PORT_MAX];	/**< YYW0REQMSK.YYW0REQMSK[3], YYWAREQMSK.YYWAREQMSK[2],<br>
																		 YYW1REQMSK.YYW1REQMSK[3], YYW2REQMSK.YYW2REQMSK :
																		 YYW transfer request mask (12bits)<br>
																		<p>Please set number of cycles, the time until the next access request.<br>
																		   If you set the "000h" you is disabled.										*/
	kuint16					resizeMode;							/**< YYW0MD.RSZ0MD, YYW1MD.RSZ1MD : Resize mode selection (1bit)
																	<ul><li>@ref ImR2yCtrl_RSZ_BILINEAR
																		<li>@ref ImR2yCtrl_RSZ_BICUBIC</ul>												*/
	kuint16					pixelAvgReductionMode;				/**< YYW0MD.RDC0MD, YYW1MD.RDC1MD, YYW2MD.RDC2MD : Pixel average reduction mode (2bits)
																	<ul><li>@ref ImR2yCtrl_RDC_MODE_DIV_2
																		<li>@ref ImR2yCtrl_RDC_MODE_DIV_4
																		<li>@ref ImR2yCtrl_RDC_MODE_DIV_8</ul>	*/
	kuint16					pixelAvgReductionEnable;				/**< YYW0MD.RDC0EN, YYW1MD.RDC1EN, YYW2MD.RDC2EN : Pixel average reduction enable
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Pixel average reduction function is not used
																		<li>@ref ImR2yCtrl_ENABLE_ON : Pixel average reduction function is used</ul>		*/
	kuint16					yccCcThinSelect;						/**< YYW0MD.CSS0SL, YYW1MD.CSS1SL : YCCC444, YCC422 and YCC420 format (4bits)
																	<ul><li>@ref ImR2yCtrl_THIN_OUT_YCC444
																		<li>@ref ImR2yCtrl_THIN_OUT_YCC422_ODD
																		<li>@ref ImR2yCtrl_THIN_OUT_YCC422_CENTER
																		<li>@ref ImR2yCtrl_THIN_OUT_YCC420_ODD
																		<li>@ref ImR2yCtrl_THIN_OUT_YCC420_CENTER_LEFT
																		<li>@ref ImR2yCtrl_THIN_OUT_YCC420_CENTER</ul>									*/
	kuint16					trimOutEnable;						/**< YYW0MD.TRM0EN, YYW1MD.TRM1EN, YYW2MD.TRM2EN : Trimming output enable
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Do not do the trimming.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Trimming.</ul>									*/
	kuint16					planarInterleavedMode;				/**< YYW0MD.SPL0EN, YYW1MD.SPL1EN : Planar or Color Interleaved store mode
																	<ul><li>@ref ImR2yCtrl_PORT_PLANAR
																		<li>@ref ImR2yCtrl_PORT_INTERLEAVED</ul>											*/
} R2yYywCtrl;

/** YYW Line interrupt control
*/
typedef struct {
	kuint16					level;									/**< LINTLV[3] : YYW Line interrupt level. (14bits)
																		<p>We generate the interrupt request flag when the set value of this register,
																		   the number of lines of ch transferred was selected by line_intr_select arrives.
																		   Setting of this interrupt can be three places,
																		   also can be set in each interrupt request.
																		<p>This interrupt request is required that you have chosen is ch operation is enabled,
																		   also is effective SDRAM power of that ch, and the operation is enabled.
																		<p>This interrupt request, can be disabled by setting the "0000" h.							*/
	kuint16					yywSelect;								/**< LINTSEL.LINTS[3] : Line interrupt select.
																	<ul><li>@ref ImR2yCtrl_YYW_CH_0 : Monitoring of the number of lines of YYW/ch0 transferred.
																		<li>@ref ImR2yCtrl_YYW_CH_1 : Monitoring of the number of lines of YYW/ch1 transferred.</ul>	*/
} CtrlLineIntr;

/** R2Y control
*/
typedef struct {
	// YYW write channel control
	R2yYywCtrl		yyw[ImR2yCtrl_YYW_CH_MAX];				/**< YYW0/YYW1/YYW2/YYW0a control parameters										*/
	CtrlLineIntr	lineIntr[ImR2yCtrl_LINE_INT_MAX];		/**< YYW Line interrupt control parameters											*/
	kuint16					yywEnable[ImR2yCtrl_YYW_CH_MAX - 1];	/**< YYWCTL.YYWMODE[0] : YYW enable(ch0(+ch0a)) (1bit)<br>
																		 YYWCTL.YYWMODE[1] : YYW enable(ch1) (1bit)<br>
																		 YYWCTL.YYWMODE[2] : YYW enable(ch2) (1bit)<br>
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Stop
																		<li>@ref ImR2yCtrl_ENABLE_ON : Transfer is enabled</ul>							*/
	kuint16					lineTransferCycle;					/**< YYW0LTT : 1 Line transfer clock cycle (14bits)
																		<p>We adjust the amount of time between the beginning of the current line
																		   from the output data, and outputs the data to the beginning of the next line.
																		<p>Set minimum number of cycles per 2-cycles are required YYW to output data for one line.<br>
																		   If the number of cycles for the number of cycles that have been set in this register,
																		   took to the transfer of one line is below, we will interrupt the output line of the
																		   following to stop the transfer operation of YYW only time of the difference.<br>
																		   YYW transfer operation does not stop if the number of cycles needed to transfer one line,
																		   this setting is exceeded, we make the following output line.<br>
																		   If you set the 0d, this function is disabled.								*/
	kuint16					yywContinueStartEnable;				/**< YYWCTL.YYWCSE : YYW continue start enable (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Frame processing one-shot.
																			(YYWTRG will need to restart each process one frame.)
																		<li>@ref ImR2yCtrl_ENABLE_ON : Continuous frame processing.
																			(I continue to frame processing writing "00" to YYWTRG.)</ul>				*/
	kuint16					yywHorizontalFlip;					/**< YYWCTL.YYWHRV : YYW horizonta flip (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Horizontal flip disable.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Horizontal flip enable.</ul>						*/
	kuint16					videoFormatOutSelect0;				/**< YYW0MD.CH0VFM : Video format output selection(ch0).
																	<ul><li>@ref ImR2yCtrl_VFM_NORMAL
																		<li>@ref ImR2yCtrl_VFM_VIDEO</ul>												*/
	kuint16					ipuMacroOutputEnable;				/**< YYW0MD.EXTBEN : External I/F output B enable(IPU macro).
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not output.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Output is enabled.</ul>							*/
	kuint16					ipuMacroTrimmingEnable;				/**< YYW0MD.TRMBEN : External I/F trimming B enable(IPU macro).
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Trimming is disabled.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Trimming is enabled.</ul>							*/
	kuint16					cnrMacroOutputEnable;				/**< YYW0MD.EXTCEN : External I/F output C enable(CNR macro).
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not output.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Output is enabled.</ul>							*/
	kuint16					cnrMacroTrimmingEnable;				/**< YYW0MD.TRMCEN : External I/F trimming C enable(CNR macro).
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Trimming is disabled.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Trimming is enabled.</ul>							*/
	kuint16					outputMode0a;							/**< YYW0MD.CH0AMD : Output channel 0a mode.
																	<ul><li>@ref ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP
																		<li>@ref ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_4_Y
																		<li>@ref ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_8_Y
																		<li>@ref ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_32_SP</ul>								*/
	kuint16					videoFormatOutSelect0a;				/**< YYW0MD.CHAVFM : Video format output selection(ch0a).
																	<ul><li>@ref ImR2yCtrl_VFM_NORMAL
																		<li>@ref ImR2yCtrl_VFM_VIDEO	 </ul>												*/
	kuint16					outputFormatSel1;						/**< YYW1MD.DFM1SL : YCbCr data format selection(ch1)
																	<ul><li>@ref ImR2yCtrl_DATA_FORMAT_8
																		<li>@ref ImR2yCtrl_DATA_FORMAT_10</ul>											*/
	kuint16					outputTypeSel1;						/**< YYW1MD.DTY1SL : Transfer data type selection(ch1)
																	<ul><li>@ref ImR2yCtrl_WRITE_DTYP_PACK8
																		<li>@ref ImR2yCtrl_WRITE_DTYP_PACK10
																		<li>@ref ImR2yCtrl_WRITE_DTYP_PACK12
																		<li>@ref ImR2yCtrl_WRITE_DTYP_PACK16</ul>										*/

	/* R2Y control */
	kuint16					ycfBypass;								/**< R2YMODE.YCFBYP : YCF bypass mode of the F_R2Y (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : YCF block of F_R2Y is set to normal mode.
																		<li>@ref ImR2yCtrl_ENABLE_ON : YCF block of F_R2Y is set to bypass mode.</ul>	*/
	kuint16					ycfPadding;							/**< R2YMODE.YCFPDD : YCF padding mode of the F_R2Y (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform ring pixel padding.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Perform ring pixel padding.</ul>					*/
	kuint16					mccSelect;								/**< R2YMODE.MCCSL : Multi-axis color correction processing selection (1bit)
																	<ul><li>@ref ImR2yCtrl_MCC_AFTER_CC0
																		<li>@ref ImR2yCtrl_MCC_AFTER_GAMMA</ul>											*/
	kuint16					mccBitShift;							/**< R2YMODE.MCC1BM : MCCSL=1 selection bit shift mode (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Saturation compensation is disabled.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Saturation compensation is enabled.</ul>			*/

	void					(*r2yUserHandler)(UINT32* intStatus, UINT32 userParam);			/**< Interrupt Handler																*/
	UINT32					userParam;								/**< This set value will return to callback argument value when interrupt occurs.	*/
} TImR2yCtrl;								/* R2Y control	*/

/** R2Y SDRAM input mode control
*/
typedef struct {
	kuint16					burstLength;							/**< YYRAXMD.YYRBL : Transfer burst length of the read channel. (2bits)
																	<ul><li>@ref ImR2yCtrl_BRST_512
																		<li>@ref ImR2yCtrl_BRST_256
																		<li>@ref ImR2yCtrl_BRST_128</ul>													*/
	kuint16					readRequestMask[ImR2yCtrl_PORT_MAX];	/**< YYRREQMSK.YYRREQMSK[3] : Mask transfer request(12bits)<br>
																	<p>Mask setting of the transfer request from the read to do YYR.<br>
																	   Please set number of cycles, the time until the next access request.<br>
																	   If you set the 000h you is disabled.												*/
	kuint16					inputDtype;							/**< YYRCTL.YYRDTYP : Input data type (2bits)
																	<ul><li>@ref ImR2yCtrl_READ_DTYP_PACK8
																		<li>@ref ImR2yCtrl_READ_DTYP_PACK12
																		<li>@ref ImR2yCtrl_READ_DTYP_PACK16</ul>											*/

	//TODO 怀疑单词拼错了
	kuint16					monoEbable;							/**< YYRCTL.MONOEN : Single component processing enable (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Input the RGB data.
																		<li>@ref ImR2yCtrl_ENABLE_ON : Input only single component data.</ul>			*/
	kuint16					rgbDekneeEnable;						/**< YYRCTL.DKNEN : Deknee enable for RGB data. (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Do not process Deknee
																		<li>@ref ImR2yCtrl_ENABLE_ON : Processing Deknee</ul>							*/
	kuint16					rgbLeftShift;							/**< YYRCTL.RGBLSFT : Left shift for RGB data. (2bits)
																	<ul><li>@ref ImR2yCtrl_STL_RGB_LEFT_SHIFT_NONE
																		<li>@ref ImR2yCtrl_STL_RGB_LEFT_SHIFT_1BIT
																		<li>@ref ImR2yCtrl_STL_RGB_LEFT_SHIFT_2BIT
																		<li>@ref ImR2yCtrl_STL_RGB_LEFT_SHIFT_4BIT</ul>									*/
	kuint16					rgbSaturationMode;					/**< YYRCTL.RGBLSM : Saturation mode when left shift. (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Do not process Saturation
																		<li>@ref ImR2yCtrl_ENABLE_ON : Processing Saturation</ul>						*/
	kuint16					topOffset[ImR2yCtrl_PORT_MAX];			/**< YYROFS[3] : Setting top bit input data area (3bits)<br>
																		<p>Set the first bit of the data area is read YYR.
																		This setting can be made for each individual component data.
																		Set the position of the LSB bit in bit position at the time of each data format.<br>
																		However, when you select 8-bit / 16-bit in inputDtype(YYRDTYP) is always 000b.
																		Only when you select a 12-bit pack, please select the setting of 000b or 100b.
																		Only when you select a 10-bit pack, please select the setting of 000b or 010b or 100b or 110b.
																		<p>This setting is valid only when the input mode SDRAM.
																		<p>exp)<br>
																		I would like the following figure, data and each are stored in 12-bit pack.<br>
																		Assuming that the first pixel data3 at this time,
																		since the position of the LSB and bit 4 data3 address, I set 100b.
																		@image html im_r2y_yyrofs_exp.png												*/
	kuint16					inputGlobal;							/**< YYRDEF : Input horizontal Gobal area size (16bits, multiple of 16)				*/
} CtrlSdramInput;						/* R2Y SDRAM input mode control	*/

/** R2Y B2R/LTM direct connection mode control
*/
typedef struct {
	kuint16					frameStop;								/**< DINCTL.FRMSTP : R2Y stop when next frame<br>
																	<p>If you want to stop at the frame boundaries of YYR transfer process is set to "1".	*/
} R2CtrlDirect;								/* R2Y B2R/LTM direct connection mode control	*/



/** Resize Rectangle control
*/
typedef struct {
	TImR2yRect			inputSize;								/**< SDRAM input mode : input image size(and trimming)<br>
																							Please set the start position and size<br>
																		 Direct input mode : input image size<br>
																							 Please set output size of connection origin.<br>
																							 (Please set (0,0) to start position)				*/
	R2yWindowsSize		outputSize[ImR2yCtrl_YYW_CH_MAX];		/**< output image size(YYW0/1/2/0a)											*/
} R2yResizeRect;

/** Resize Pitch control
*/
typedef struct {
	TImR2yRect			inputSize;								/**< input image size(and trimming)	*/
	TImR2yPitch			outputPitch[ImR2yCtrl_YYW_CH_MAX];		/**< output image pitch(YYW0/1/2/0a)*/
} R2yResizePitch;

/** Resize control information
*/
typedef struct {
	UINT32					resizeSelect;							/**< 0:invalidate(initial value or parameter changing)<br>
																		1:validate r2yResizeRect<br>
																		2:validate r2yResizePitch */
	R2yResizeRect		r2yResizeRect;						/**< rectangle information. (refer im_r2y2_set_resize_rect(im_r2y2_new(), )) */
	R2yResizePitch		r2yResizePitch;						/**< pitch information. (refer im_r2y2_set_resize_pitch()) */
} R2yResizeParam;

/** YCC address information
*/
typedef struct {
	void*					addrY;									/**< Y address		*/
	void*					addrCb;								/**< Cb address		*/
	void*					addrCr;								/**< Cr address		*/
} AddrYccInfo;

/** RGB address information
*/
typedef struct {
	void*					addrR;									/**< R address		*/
	void*					addrG;									/**< G address		*/
	void*					addrB;									/**< B address		*/
} AddrRgbInfo;

/** YYR input address information
*/
typedef union {
	AddrRgbInfo	rgb;									/**< RGB address information	*/
} R2yInaddrInfo;

/** YYW output address information
*/
typedef union {
	AddrYccInfo	ycc;									/**< YCC address information	*/
} R2yOutaddrInfo;

/** YYW output bank control
*/
typedef struct {
	kuint16					bankInitialPosition;					/**< YYWBANK.BANK0PS, YYWBANK.BANKAPS, YYWBANK.BANK1PS, YYWBANK.BANK2PS : Bank initial position
																	<ul><li>@ref ImR2yCtrl_YYW_BANK_0
																		<li>@ref ImR2yCtrl_YYW_BANK_1
																		<li>@ref ImR2yCtrl_YYW_BANK_2
																		<li>@ref ImR2yCtrl_YYW_BANK_3</ul>				*/
	kuint16					useBankNum;							/**< YYWCTL.USEBANK0, YYWCTL.USEBANKA, YYWCTL.USEBANK1, YYWCTL.USEBANK2 : Use bank number<br>
																	Use only one bank in the setting of 0 (d),
																	and use of the four banks in the setting of 3 (d).	*/
	R2yOutaddrInfo	outputAddr[ImR2yCtrl_YYW_BANK_MAX];		/**< Output bank address information				*/
} R2yOutbankInfo;

/** YYW output right side offset(for video format)
*/
typedef struct {
	UINT32					offsetByte[ImR2yCtrl_YYW_BANK_MAX];		/**< YYW0OFSX(multiple of 8), YYWAOFSX(multiple of 2) : Offset byte(12bits)	*/
} R2yRightsideOffset;


/** Histogram control
*/
typedef struct {
	kuint16					enable;									/**< HSTMD.HSTEN : Histogram enable (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Do not get the histogram
																		<li>@ref ImR2yCtrl_ENABLE_ON : Get the histogram</ul>						*/
	kuint16					yywNo;									/**< HSTMD.HSTSEL : Select a ch of YYW that you want to get the histogram. (1bit)
																	<ul><li>@ref ImR2yCtrl_YYW_CH_0
																		<li>@ref ImR2yCtrl_YYW_CH_1</ul>												*/
	kuint16					samplingPitch;							/**< HSTMD.PIT_M : Sampling pixel pitch (2bits)
																	<ul><li>@ref ImR2yCtrl_HIST_PIT_2X2
																		<li>@ref ImR2yCtrl_HIST_PIT_4X4
																		<li>@ref ImR2yCtrl_HIST_PIT_8X8
																		<li>@ref ImR2yCtrl_HIST_PIT_16X16</ul>										*/
	TImR2yRect			histogramArea;							/**< HSTH (13bits, multiple of 2), HSTV(14bits, multiple of 2) : Histogram area	*/
} R2yCtrlHistogram;

/** Histogram address
*/
typedef struct {
	kuint16*					yBuf;									/**< Y Histogram data copy destination address (kuint16 x ImR2yCtrl_TABLE_MAX_HISTOGRAM) */
} R2yHistogramAddr;

/** Histogram status
*/
typedef struct {
	kuint16					yOverflow;								/**< HSTMD.YHSOVF : Y data overflow stauts (1bit)<br>
																	<p>When the acquisition time of the histogram for the Y data,
																	   the number of gray scale appearance of the same exceeds 32767d displays "1".
																	   Gradation appearance is greater than the number 32767d, you clip in 32767d.	*/
	kuint16					runningStatus;							/**< HSTMD.HSTSTS : Histogram running status (1bit)<br>
																	<p>While trying to get the histogram to display "1".<br>
																	   When this bit is "1", the result of the histogram can not be read.			*/
} R2yHistogramStat;

/** Partial color extraction information
*/
typedef struct {
	kuint16					extractEnable;							/**< PCEMD.PCEEN : Partial color extraction enable (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF
																		<li>@ref ImR2yCtrl_ENABLE_ON</ul>										*/
	kint16					refAxisX;								/**< PCEXY.PCEX : Axis of the color you want to extract (X) (9bits signed)	*/
	kint16					refAxisY;								/**< PCEXY.PCEY : Axis of the color you want to extract (Y) (9bits signed)	*/
} R2yColorExtract;

/** Chroma scale value
*/
typedef struct {
	kuint16					chromaOffset;							/**< PCEC.PCECOF : Offset chroma scale value (8bits 0 ~ 128)	*/
	kuint16					chromaGain;							/**< PCEC.PCECGA : Gain chroma scale value (10bits)				*/
} R2yChRomaScale;

/** Hue scale value
*/
typedef struct {
	kuint16					hueOffset;								/**< PCEH.PCEHOF : Offset hue scale value (8bits 0 ~ 128)	*/
	kuint16					hueGain;								/**< PCEH.PCEHGA : Gain hue scale value (10bits)			*/
} R2yHueScale;


/* @} */	// im_r2y group

/** @weakgroup im_r2y_iq
@{
*/

/* RGB array control data	*/

/** Multi Axis control
*/
typedef struct {
	kint16			cycCoeff[9];				/**< MCYC : Coefficient of YC convert (9bits signed)				*/
	kuint16			boundary[16];				/**< MCB1A~MCB4D : Boundary of color correction (12bits)			*/
	kuint16			areaIndex[4][5];			/**< MCID1A~MCID4E : Index value of correction area (4bits 0 ~ 11)	*/
	kint16			areaAK[5][3][3];			/**< MCKA_0_00~MCKA_4_22 : Convert data of area-A (12bits signed)	*/
	kint16			areaBK[5][3][3];			/**< MCKB_0_00~MCKB_4_22 : Convert data of area-B (12bits signed)	*/
	kint16			areaCK[5][3][3];			/**< MCKC_0_00~MCKC_4_22 : Convert data of area-C (12bits signed)	*/
	kint16			areaDK[5][3][3];			/**< MCKD_0_00~MCKD_4_22 : Convert data of area-D (12bits signed)	*/
	kint16			areaEK[5][3][3];			/**< MCKE_0_00~MCKE_4_22 : Convert data of area-E (12bits signed)	*/
	kint16			areaFK[5][3][3];			/**< MCKF_0_00~MCKF_4_22 : Convert data of area-F (12bits signed)	*/
	kint16			areaGK[5][3][3];			/**< MCKG_0_00~MCKG_4_22 : Convert data of area-G (12bits signed)	*/
	kint16			areaHK[5][3][3];			/**< MCKH_0_00~MCKH_4_22 : Convert data of area-H (12bits signed)	*/
	kint16			areaIK[5][3][3];			/**< MCKI_0_00~MCKI_4_22 : Convert data of area-I (12bits signed)	*/
	kint16			areaJK[5][3][3];			/**< MCKJ_0_00~MCKJ_4_22 : Convert data of area-J (12bits signed)	*/
	kint16			areaKK[5][3][3];			/**< MCKK_0_00~MCKK_4_22 : Convert data of area-K (12bits signed)	*/
	kint16			areaLK[5][3][3];			/**< MCKL_0_00~MCKL_4_22 : Convert data of area-L (12bits signed)	*/
	kint16			areaAL[5][3][2];			/**< MCLA_0_00~MCLA_4_21 : Convert data of area-A (10bits signed)	*/
	kint16			areaBL[5][3][2];			/**< MCLB_0_00~MCLB_4_21 : Convert data of area-B (10bits signed)	*/
	kint16			areaCL[5][3][2];			/**< MCLC_0_00~MCLC_4_21 : Convert data of area-C (10bits signed)	*/
	kint16			areaDL[5][3][2];			/**< MCLD_0_00~MCLD_4_21 : Convert data of area-D (10bits signed)	*/
	kint16			areaEL[5][3][2];			/**< MCLE_0_00~MCLE_4_21 : Convert data of area-E (10bits signed)	*/
	kint16			areaFL[5][3][2];			/**< MCLF_0_00~MCLF_4_21 : Convert data of area-F (10bits signed)	*/
	kint16			areaGL[5][3][2];			/**< MCLG_0_00~MCLG_4_21 : Convert data of area-G (10bits signed)	*/
	kint16			areaHL[5][3][2];			/**< MCLH_0_00~MCLH_4_21 : Convert data of area-H (10bits signed)	*/
	kint16			areaIL[5][3][2];			/**< MCLI_0_00~MCLI_4_21 : Convert data of area-I (10bits signed)	*/
	kint16			areaJL[5][3][2];			/**< MCLJ_0_00~MCLJ_4_21 : Convert data of area-J (10bits signed)	*/
	kint16			areaKL[5][3][2];			/**< MCLK_0_00~MCLK_4_21 : Convert data of area-K (10bits signed)	*/
	kint16			areaLL[5][3][2];			/**< MCLL_0_00~MCLL_4_21 : Convert data of area-L (10bits signed)	*/
	kuint16			cycAlphaBlend;			/**< MCYCBALP.MCYCBALP : CYC Alpha blend value (6bits)				*/
	kuint16			cycBlendGain[4];			/**< MCYCBGA : CYC blend gain (12bits)								*/
	kuint16			cycBlendBorder[4];		/**< MCYCBBD : CYC blend border (12bits)							*/
	kuint16			cbaAlphaBlend;			/**< MCBABALP.MCBABALP : Alpha blend value (6bits)					*/
	kuint16			cbaBlendOffset[4];		/**< MCBABOF : CBA blend offset (11bits)							*/
	kint16			cbaBlendGain[4];			/**< MCBABGA : CBA blend gain (9bits signed)						*/
	kuint16			cbaBlendBorder[3];		/**< MCBABBD : CBA blend border (12bits)							*/
} CtrlMultiAxis;						/* Multi Axis control	*/


/** Histogram overflow flag before TC data
*/
typedef struct {
	kuint16			Y;							/**< TCHYOV : Histogram overflow flag Y component	*/
	kuint16			R;							/**< TCHROV : Histogram overflow flag R component	*/
	kuint16			G;							/**< TCHGOV : Histogram overflow flag G component	*/
	kuint16			B;							/**< TCHBOV : Histogram overflow flag B component	*/
} R2yTchsFlg;							/* Offset before TC data	*/


/** High/Medium frequency edge enhancement common control
*/
typedef struct {
	kuint16			reductionMode;				/**< EGSMCTL.EGSMT : Edge enhancement edge noise reduction mode (1bit)
												<ul><li>@ref ImR2yCtrl_EGSMT_VERSION1
													<li>@ref ImR2yCtrl_EGSMT_VERSION2</ul>										*/
	kuint16			threshold;					/**< EGSMTT.EGSMTTH : Edge noise reduction applying threshold value (10bits)	*/
	kuint16			textureGain;				/**< EGSMTT.EGSMTTXGA : Edge noise reduction texture gain (7bits 0~64)			*/
} CtrlEdgeCmn;						/* High/Medium frequency edge enhancement common control	*/

/** High frequency edge enhancement control
*/
typedef struct {
	kuint16			edgeEnable;				/**< EGHWCTL.EGHWEN : Edge enhancement enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform high-frequency edge enhancement.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs high-frequency edge enhancement</ul>				*/
	kuint16			scaleEnable;				/**< EGHWCTL.EGHWMP : Coordinate dependent scale enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform coordinate dependent scale adjustment.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs coordinate dependent scale adjustment.</ul>		*/
	kuint16			tableClipSelect;			/**< EGHWCTL.EGHWTC : Gradation adjustment table enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not refer to gradation table.
													<li>@ref ImR2yCtrl_ENABLE_ON : Refers to gradation table.</ul>							*/
	kuint16			scaleTableResol;			/**< EGHWCTL.EGHWSCLRES : Scale table reference resolution (2bits 0 ~ 2)					*/
	kuint16			scaleTableSelect;			/**< EGHWCTL.EGHWSCLTBL : Scale table selection (2bits)										*/
	kuint16			gradationTableResol;		/**< EGHWCTL.EGHWTCRES : Gradation adjustment table reference resolution (2bits 0 ~ 2)		*/
	kuint16			gradationTableSelect;		/**< EGHWCTL.EGHWTCTBL : Gradation adjustment table selection (2bits)						*/
	kuint16			nrLevel;					/**< EGHWCTL.EGHWNRLV : Noise reduction strength (4bits 0 ~ 8)								*/

	kint16				hpfK[6];					/**< EGHWHPFK : High pass filter coefficient K0-K5.<br>
													 EGHWHPFK0(10bits unsigned), EGHWHPFK1-EGHWHPFK5(8bits signed).							*/
	kuint16			corpOffset[4];				/**< EGHWCORPOF : Coring positive direction offset 0-3 (10bits)								*/
	INT8				corpGain[4];				/**< EGHWCORPGA : Coring positive direction gain 0-3 (8bits signed)							*/
	kuint16			corpBorder[3];				/**< EGHWCORPBD : Coring positive direction area boundary 1-3 (10bits)						*/
	kuint16			cormOffset[4];				/**< EGHWCORMOF : Coring negative direction offset 0-3 (10bits)								*/
	INT8				cormGain[4];				/**< EGHWCORMGA : Coring negative direction gain 0-3 (8bits signed)							*/
	kuint16			cormBorder[3];				/**< EGHWCORMBD : Coring negative direction area boundary 1-3 (10bits)						*/
	kuint16			supScl;					/**< EGHWSCLSUP : Scale reduction coefficient (6bits)										*/
	kuint16			levelClipPOffset[3];		/**< EGHWCLPPOF : Level clip positive direction offset (9bits)								*/
	INT8				levelClipPGain[3];		/**< EGHWCLPPGA : Level clip positive direction gain (8bits signed)							*/
	kuint16			levelClipPBorder[2];		/**< EGHWCLPPBD : Level clip positive direction area boundary (10bits)						*/
	kuint16			levelClipMOffset[3];		/**< EGHWCLPMOF : Level clip negative direction offset (9bits)								*/
	INT8				levelClipMGain[3];		/**< EGHWCLPMGA : Level clip negative direction gain (8bits signed)							*/
	kuint16			levelClipMBorder[2];		/**< EGHWCLPMBD : Level clip negative direction area boundary (10bits)						*/
} R2yCtrlHedge;							/* High frequency edge enhancement control	*/

/** Medium frequency edge enhancement control
*/
typedef struct {
	kuint16			edgeEnable;				/**< EGMWCTL.EGMWEN : Edge enhancement enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform medium-frequency edge enhancement.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs medium-frequency edge enhancement</ul>			*/
	kuint16			scaleEnable;				/**< EGMWCTL.EGMWMP : Coordinate dependent scale enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform coordinate dependent scale adjustment.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs coordinate dependent scale adjustment.</ul>		*/
	kuint16			tableClipSelect;			/**< EGMWCTL.EGMWTC : Gradation adjustment table enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not refer to gradation table.
													<li>@ref ImR2yCtrl_ENABLE_ON : Refers to gradation table.</ul>							*/
	kuint16			scaleTableResol;			/**< EGMWCTL.EGMWSCLRES : Scale table reference resolution (2bits 0 ~ 2)					*/
	kuint16			scaleTableSelect;			/**< EGMWCTL.EGMWSCLTBL : Scale table selection (2bits)										*/
	kuint16			gradationTableResol;		/**< EGMWCTL.EGMWTCRES : Gradation adjustment table reference resolution (2bits 0 ~ 2)		*/
	kuint16			gradationTableSelect;		/**< EGMWCTL.EGMWTCTBL : Gradation adjustment table selection (2bits)						*/
	kuint16			nrLevel;					/**< EGMWCTL.EGMWNRLV : Noise reduction strength (4bits 0 ~ 8)								*/

	kint16			hpfK[6];					/**< EGMWHPFK : High pass filter coefficient K0-K5.<br>
													 EGMWHPFK0(10bits unsigned), EGMWHPFK1-EGMWHPFK5(8bits signed).							*/
	kuint16			corpOffset[4];				/**< EGMWCORPOF : Coring positive direction offset 0-3 (10bits)								*/
	INT8			corpGain[4];				/**< EGMWCORPGA : Coring positive direction gain 0-3 (8bits signed)							*/
	kuint16			corpBorder[3];				/**< EGMWCORPBD : Coring positive direction area boundary 1-3 (10bits)						*/
	kuint16			cormOffset[4];				/**< EGMWCORMOF : Coring negative direction offset 0-3 (10bits)								*/
	INT8			cormGain[4];				/**< EGMWCORMGA : Coring negative direction gain 0-3 (8bits signed)							*/
	kuint16			cormBorder[3];				/**< EGMWCORMBD : Coring negative direction area boundary 1-3 (10bits)						*/
	kuint16			supScl;					/**< EGMWSCLSUP : Scale reduction coefficient (6bits)										*/
	kuint16			levelClipPOffset[3];		/**< EGMWCLPPOF : Level clip positive direction offset (9bits)								*/
	INT8			levelClipPGain[3];		/**< EGMWCLPPGA : Level clip positive direction gain (8bits signed)							*/
	kuint16			levelClipPBorder[2];		/**< EGMWCLPPBD : Level clip positive direction area boundary (10bits)						*/
	kuint16			levelClipMOffset[3];		/**< EGMWCLPMOF : Level clip negative direction offset (9bits)								*/
	INT8			levelClipMGain[3];		/**< EGMWCLPMGA : Level clip negative direction gain (8bits signed)							*/
	kuint16			levelClipMBorder[2];		/**< EGMWCLPMBD : Level clip negative direction area boundary (10bits)						*/
} R2yCtrlMedge;							/* Medium frequency edge enhancement control	*/

/** Low frequency edge enhancement control
*/
typedef struct {
	kuint16			edgeEnable;				/**< EGLWCTL.EGLWEN : Edge enhancement enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform low-frequency edge enhancement
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs low-frequency edge enhancement</ul>				*/
	kuint16			scaleEnable;				/**< EGLWCTL.EGLWMP : Coordinate dependent scale enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform coordinate dependent scale adjustment.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs coordinate dependent scale adjustment.</ul>		*/
	kuint16			tableClipSelect;			/**< EGLWCTL.EGLWTC : Gradation adjustment table enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not refer to gradation table.
													<li>@ref ImR2yCtrl_ENABLE_ON : Refers to gradation table.</ul>							*/
	kuint16			scaleTableResol;			/**< EGLWCTL.EGLWSCLRES : Scale table reference resolution (2bits 0 ~ 2)	*/
	kuint16			scaleTableSelect;			/**< EGLWCTL.EGLWSCLTBL : Scale table selection (2bits)					*/
	kuint16			gradationTableResol;		/**< EGLWCTL.EGLWTCRES : Gradation adjustment table reference resolution (2bits 0 ~ 2)		*/
	kuint16			gradationTableSelect;		/**< EGLWCTL.EGLWTCTBL : Gradation adjustment table selection (2bits)						*/

	kint16				hpfK[10];					/**< EGLWHPFK : High pass filter coefficient K0-K9.<br>
													 EGLWHPFK0(10bits unsigned), EGLWHPFK1-EGLWHPFK9(8bits signed).							*/
	kuint16			corpOffset[4];				/**< EGLWCORPOF : Coring positive direction offset 0-3 (10bits)								*/
	INT8				corpGain[4];				/**< EGLWCORPGA : Coring positive direction gain 0-3 (8bits signed)							*/
	kuint16			corpBorder[3];				/**< EGLWCORPBD : Coring positive direction boundary 1-3 (10bits)							*/
	kuint16			cormOffset[4];				/**< EGLWCORMOF : Coring negative direction offset 0-3 (10bits)								*/
	INT8				cormGain[4];				/**< EGLWCORMGA : Coring negative direction gain 0-3 (8bits signed)							*/
	kuint16			cormBorder[3];				/**< EGLWCORMBD : Coring negative direction boundary 1-3 (10bits)							*/
	kuint16			supScl;					/**< EGLWSCLSUP : Scale reduction coefficient (6bits)										*/
	kuint16			levelClipPOffset[3];		/**< EGLWCLPPOF : Level clip positive direction offset (9bits)								*/
	INT8				levelClipPGain[3];		/**< EGLWCLPPGA : Level clip positive direction gain (8bits signed)							*/
	kuint16			levelClipPBorder[2];		/**< EGLWCLPPBD : Level clip positive direction border (10bits)								*/
	kuint16			levelClipMOffset[3];		/**< EGLWCLPMOF : Level clip negative direction offset (9bits)								*/
	INT8				levelClipMGain[3];		/**< EGLWCLPMGA : Level clip negative direction gain (8bits signed)							*/
	kuint16			levelClipMBorder[2];		/**< EGLWCLPMBD : Level clip negative direction border (10bits)								*/
} R2yCtrlLedge;							/* Low frequency edge enhancement control	*/

/** Edge dot noise correction control
*/
typedef struct {
	kuint16			hfEnable;					/**< EGDTCTL.EGDTHW : High frequency edge dot noise correction enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform high-frequency edge dot noise correction.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs high-frequency edge dot noise correction.</ul>		*/
	kuint16			mfEnable;					/**< EGDTCTL.EGDTMW : Medium frequency edge dot noise correction enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform medium-frequency edge dot noise correction.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs medium-frequency edge dot noise correction.</ul>		*/
	kuint16			hfPThreshold;				/**< EGDTHWTH.EGDTHWTHP : Threshold for high-frequency edge dot noise detection(+) (10bits)		*/
	kuint16			hfMThreshold;				/**< EGDTHWTH.EGDTHWTHM : Threshold for high-frequency edge dot noise detection(-) (10bits)		*/
	kuint16			hfPCoef;					/**< EGDTHWK.EGDTHWKP : High-frequency edge dot noise correction coefficient(+) (4bits 0~8)		*/
	kuint16			hfMCoef;					/**< EGDTHWK.EGDTHWKM : High-frequency edge dot noise correction coefficient(-) (4bits 0~8)		*/
	kuint16			mfPThreshold;				/**< EGDTMWTH.EGDTMWTHP : Threshold for Medium-frequency edge dot noise detection(+) (10bits)	*/
	kuint16			mfMThreshold;				/**< EGDTMWTH.EGDTMWTHM : Threshold for Medium-frequency edge dot noise detection(-) (10bits)	*/
	kuint16			mfPCoef;					/**< EGDTMWK.EGDTMWKP : Medium-frequency edge dot noise correction coefficient(+) (4bits 0~8)	*/
	kuint16			mfMCoef;					/**< EGDTMWK.EGDTMWKM : Medium-frequency edge dot noise correction coefficient(-) (4bits 0~8)	*/
} CtrlEdgeDotNoise;					/* Edge dot noise correction control	*/

/** Map scale control
*/
typedef struct {
	kuint16			blockSizeH;				/**< EGMPSIZ.EGMPSIZH : Horizontal block size (10bits 16 ~ 1022)									*/
	kuint16			blockSizeV;				/**< EGMPSIZ.EGMPSIZV : Vertical block size (10bits 16 ~ 1023)										*/
	kuint16			recipMultipliH;			/**< EGMPSIZHINV.EGMPINVH : Horizontal reciprocal multiplication value (14bits)						*/
	kuint16			recipMultipliShiftH;		/**< EGMPSIZHINV.EGMPINVSFTH : Amount multiplied by the reciprocal horizontal shift (3bits 0 ~ 6)	*/
	kuint16			recipMultipliV;			/**< EGMPSIZVINV.EGMPINVV : Vertical reciprocal multiplication value (14bits)						*/
	kuint16			recipMultipliShiftV;		/**< EGMPSIZVINV.EGMPINVSFTV : Amount multiplied by the reciprocal vertical shift (3bits 0 ~ 6)		*/
	kuint16			blockStartH;				/**< EGMPSTAPH.EGMPSTABH : Block horizontal start (4bits 0 ~ 15)									*/
	kuint16			blockStartCoordH;		/**< EGMPSTAPH.EGMPSTACH : Horizontal start coordinate in the block (10bits 0 ~ 1022)				*/
	kuint16			blockStartV;				/**< EGMPSTAPV.EGMPSTAPV : Block horizontal start (4bits 0 ~ 11)									*/
	kuint16			blockStartCoordV;		/**< EGMPSTAPV.EGMPSTACV : Horizontal start coordinate in the block (10bits 0 ~ 1023)				*/
} R2yCtrlMapScl;							/* Map scale control	*/

/** Edge blend control
*/
typedef struct {
	kuint16			blendType;					/**< EGCMPCTL.EGCMPS : Edge blend type select (1bits)								*/
	kuint16			border[3];					/**< EGCMPBD : Edge synthesis blend coefficient area boundary 1-3 (10bits)			*/
	kuint16			alphaOffset[4];			/**< EGCMPALPOF : Edge synthesis blend coefficient alpha offset 0-3 (8bits 0 ~ 128)	*/
	kint16				alphaGain[4];				/**< EGCMPALPGA : Edge synthesis blend coefficient alpha gain 0-3 (10bits signed)	*/
	kuint16			betaOffset[4];				/**< EGCMPBTAOF : Edge synthesis blend coefficient beta offset 0-3 (8bits 0 ~ 128)	*/
	kint16				betaGain[4];				/**< EGCMPBTAGA : Edge synthesis blend coefficient beta gain 0-3 (10bits signed)	*/
	kuint16			levelClipP;				/**< EGCMPCLP.EGCMPCLPP : Edge synthesis positive direction level clip (9bits)		*/
	kuint16			levelClipM;				/**< EGCMPCLP.EGCMPCLPM : Edge synthesis negative direction level clip (9bits)		*/
} CtrlEdgeBlend;						/* Edge blend control	*/

/** Chroma referenced edge and texture adjustment control common
 */
typedef struct {
	INT8			cbAFocus1Pos;			/**< CRVAF.CRVAFX1 : Ellipse focus 1 Cb coordinate of color difference reference correction area A (8bits signed) */
	INT8			crAFocus1Pos;			/**< CRVAF.CRVAFY1 : Ellipse focus 1 Cr coordinate of color difference reference correction area A (8bits signed) */
	INT8			cbAFocus2Pos;			/**< CRVAF.CRVAFX2 : Ellipse focus 2 Cb coordinate of color difference reference correction area A (8bits signed) */
	INT8			crAFocus2Pos;			/**< CRVAF.CRVAFY2 : Ellipse focus 2 Cr coordinate of color difference reference correction area A (8bits signed) */
	INT8			cbBFocus1Pos;			/**< CRVBF.CRVBFX1 : Ellipse focus 1 Cb coordinate of color difference reference correction area B (8bits signed) */
	INT8			crBFocus1Pos;			/**< CRVBF.CRVBFY1 : Ellipse focus 1 Cr coordinate of color difference reference correction area B (8bits signed) */
	INT8			cbBFocus2Pos;			/**< CRVBF.CRVBFX2 : Ellipse focus 2 Cb coordinate of color difference reference correction area B (8bits signed) */
	INT8			crBFocus2Pos;			/**< CRVBF.CRVBFY2 : Ellipse focus 2 Cr coordinate of color difference reference correction area B (8bits signed) */
} CtrlCrefEdgeTexture;

/** Chroma referenced edge adjustment control
 */
typedef struct {
	kuint16			areaAEnable;				/**< EGCRVCTL.EGCRAE : Set whether color difference reference edge correction is
													 performed or not by using correction area A. (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF :
														Does not perform color difference regerence edge correction by using correction area A.
													<li>@ref ImR2yCtrl_ENABLE_ON :
														Performs color difference regerence edge correction by using correction area A.</ul>		*/
	kuint16			areaBEnable;				/**< EGCRVCTL.EGCRBE : Set whether color difference reference edge correction is
													 performed or not by using correction area A. (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF :
														Does not perform color difference regerence edge correction by using correction area B.
													<li>@ref ImR2yCtrl_ENABLE_ON :
														Performs color difference regerence edge correction by using correction area B.</ul>		*/
	kuint16			mergeMethod;				/**< EGCRVCTL.EGCRVMRG : Color difference reference edge correction area AB merge method (2bits 0~2)*/
	kuint16			areaAScaleOffset;		/**< EGCRVASCLOF : Area A scale offset (8bits)														*/
	kint16				areaAScaleGain[2];		/**< EGCRVASCLGA : Area A scale gain (11bits signed)												*/
	kuint16			areaAScaleBorder;		/**< EGCRVASCLBD : Area A scale border (7bits)														*/
	kuint16			areaAScaleClipLo;		/**< EGCRVASCLCP.EGCRVASCLCPL : Area A scale lower clip (8bits)										*/
	kuint16			areaAScaleClipHi;		/**< EGCRVASCLCP.EGCRVASCLCPH : Area A scale upper clip (8bits)										*/
	kuint16			areaAYScaleGainP;		/**< EGYASCLGA.EGYASCLGA0 : Area A luminance scale plus gain0 (8bits)								*/
	kuint16			areaAYScaleGainM;		/**< EGYASCLGA.EGYASCLGA1 : Area A luminance scale minus gain1 (8bits)								*/
	kuint16			areaAYScaleBorder[2];	/**< EGYASCLBD : Area A luminance scale border (8bits)												*/
	kuint16			areaAYScaleClipLo;		/**< EGYASCLCLP.EGYASCLCLPL : Area A luminance scale lower clip (9bits)								*/
	kuint16			areaAYScaleClipHi;		/**< EGYASCLCLP.EGYASCLCLPH : Area A luminance scale upper clip (9bits)								*/
	kuint16			areaBScaleOffset;		/**< EGCRVBSCLOF : Area B scale offset (8bits)														*/
	kint16				areaBScaleGain[2];		/**< EGCRVBSCLGA : Area B scale gain (11bits signed)												*/
	kuint16			areaBScaleBoarder;		/**< EGCRVBSCLBD : Area B scale border (7bits)														*/
	kuint16			areaBScaleClipLo;		/**< EGCRVBSCLCP.EGCRVBSCLCPL : Area B scale lower clip (8bits)										*/
	kuint16			areaBScaleClipHi;		/**< EGCRVBSCLCP.EGCRVBSCLCPH : Area B scale upper clip (8bits)										*/
	kuint16			areaBYScaleGainP;		/**< EGYBSCLGA.EGYBSCLGA0 : Area B luminance scale plus gain0 (8bits)								*/
	kuint16			areaBYScaleGainM;		/**< EGYBSCLGA.EGYBSCLGA1 : Area B luminance scale minus gain1 (8bits)								*/
	kuint16			areaBYScaleBorder[2];	/**< EGYBSCLBD : Area B luminance scale border (8bits)												*/
	kuint16			areaBYScaleClipLo;		/**< EGYBSCLCLP.EGYBSCLCLPL : Area B luminance scale lower clip (9bits)								*/
	kuint16			areaBYScaleClipHi;		/**< EGYBSCLCLP.EGYBSCLCLPH : Area B luminance scale upper clip (9bits)								*/
	kuint16			levelClipP;				/**< EGCRVCLP.EGCRVCLPP : Level clip plus (9bits)													*/
	kuint16			levelClipM;				/**< EGCRVCLP.EGCRVCLPM : Level clip minus (9bits)													*/
} CtrlCrefEdgeAdj;

/** Chroma referenced luminance blend control common
 */
typedef struct {
	kuint16			areaAEnable;				/**< YBCRVCTL.YBCRAE : Set whether color difference regerence luminance blend is
													 performed or not by using correction area A. (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF :
														Does not perform color difference regerence luminance blend by using correction area A.
													<li>@ref ImR2yCtrl_ENABLE_ON :
														Performs color difference regerence luminance blend by using correction area A.</ul>	*/
	kuint16			areaBEnable;				/**< YBCRVCTL.YBCRBE : Set whether color difference regerence luminance blend is
													 performed or not by using correction area B. (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF :
														Does not perform color difference regerence luminance blend by using correction area B.
													<li>@ref ImR2yCtrl_ENABLE_ON :
														Performs color difference regerence luminance blend by using correction area B.</ul>	*/
	kuint16			areaAOffset;				/**< YBCRVAALPOF : offset value alpha in area A (8bits)											*/
	kint16				areaAGain[2];				/**< YBCRVAALPGA : gain value alpha in area A (11bits signed)									*/
	kuint16			areaABoarder;				/**< YBCRVAALPBD : border value alpha in area A (7bits)											*/
	kuint16			areaAScaleClipLo;		/**< YBCRVAALPCP.YBCRVAALPCPL : lower clip in area A (8bits)									*/
	kuint16			areaAScaleClipHi;		/**< YBCRVAALPCP.YBCRVAALPCPH : upper clip in area A (8bits)									*/
	kuint16			areaACorrectGainP;		/**< YBYAALPGA.YBYAALPGA0 : Area A alpha value correction plus gain (8bits)						*/
	kuint16			areaACorrectGainM;		/**< YBYAALPGA.YBYAALPGA1 : Area A alpha value correction minus gain (8bits)					*/
	kuint16			areaACorrectBorder[2];	/**< YBYAALPBD : Area A alpha value correction boudary (8bits)									*/
	kuint16			areaACorrectClipLo;		/**< YBYAALPCLP.YBYAALPCLPL : Area A alpha value correction lower clip (8bits)					*/
	kuint16			areaACorrectClipHi;		/**< YBYAALPCLP.YBYAALPCLPH : Area A alpha value correction upper clip (8bits)					*/
	kuint16			areaBOffset;				/**< YBCRVBALPOF : offset value alpha in area B (8bits)											*/
	kint16				areaBGain[2];				/**< YBCRVBALPGA : gain value alpha in area B (11bits signed)									*/
	kuint16			areaBBoarder;				/**< YBCRVBALPBD : border value alpha in area B (7bits)											*/
	kuint16			areaBScaleClipLo;		/**< YBCRVBALPCP.YBCRVAALPCPL : lower clip in area B (8bits)									*/
	kuint16			areaBScaleClipHi;		/**< YBCRVBALPCP.YBCRVAALPCPH : upper clip in area B (8bits)									*/
	kuint16			areaBCorrectGainP;		/**< YBYBALPGA.YBYBALPGA0 : Area B alpha value correction plus gain (8bits)						*/
	kuint16			areaBCorrectGainM;		/**< YBYBALPGA.YBYBALPGA1 : Area B alpha value correction minus gain (8bits)					*/
	kuint16			areaBCorrectBoarder[2];	/**< YBYBALPBD : Area B alpha value correction boudary (8bits)									*/
	kuint16			areaBCorrectClipLo;		/**< YBYBALPCLP.YBYBALPCLPL : Area B alpha value correction lower clip (8bits)					*/
	kuint16			areaBCorrectClipHi;		/**< YBYBALPCLP.YBYBALPCLPH : Area B alpha value correction upper clip (8bits)					*/
} CtrlCrefYbBlend;

/** C(Chroma) Noise Reduction control
*/
typedef struct {
	kuint16			clpfEnable;				/**< CLPFCTL.CLPFEN : Color Noise Reduction enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform color noise reduction.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs color noise reduction.</ul>							*/
	kuint16			interlockBlendEnable;		/**< CLPFCTL.CLPFYA : Color difference component LPF luminance cooperating blend enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF :
														Does not perform color difference component LPF luminance cooperating blend.
													<li>@ref ImR2yCtrl_ENABLE_ON :
														Performs color difference component LPF luminance cooperating blend.</ul>				*/
	kint16				lpfK[9];					/**< CLPFK: LPF kernel parameter (9bits signed)													*/
	kuint16			lpfIbOffset[4];			/**< CLPFOF: LPF kernel Interlock blend offset (8bits 0 ~ 128)									*/
	kint16				lpfIbGain[4];				/**< CLPFGA: LPF kernel Interlock blend gain (10bits signed)									*/
	kuint16			lpfIbBorder[3];			/**< CLPFBD: LPF kernel Interlock blend border (10bits)											*/
} R2yCtrlClpf;

/** Chroma Suppress control
*/
typedef struct {
	kuint16			csyEnable;					/**< CSYCTL.CSYEN : Set whether reduction function by luminance/chroma
													 reference color difference reduction table is used or not. (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF :
														Does not peform color difference reduction by luminance/chroma reference.
													<li>@ref ImR2yCtrl_ENABLE_ON :
														Peforms color difference reduction by luminance/chroma reference.</ul>		*/
	kuint16			csy_mix_ratio;				/**< CSYCTL.CSYKY : Mixing ratio of Luminannce & Chroma (4bits 0 ~ 8)				*/
	kuint16			csy_select_table;			/**< CSYCTL.CSYTBL : Selection of Chroma suppress table (1bit)						*/
	kuint16			csy_offset[4];				/**< CSYOF : offset (10bits)														*/
	kint16			csy_gain[4];				/**< CSYGA : gain (11bits signed)													*/
	kuint16			csy_border[3];				/**< CSYBD : border (10bits)														*/
	kuint16			y_rev_enable;				/**< YCRVFX.YRV : Enable of Y data reverse (1bit) <br>
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : No operation.
													<li>@ref ImR2yCtrl_ENABLE_ON : Sets luminance to 1023d-Y.</ul>					*/
	kuint16			c_rev_enable;				/**< YCRVFX.CRV : Enable of Chroma data reverse (1bit) <br>
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : No operation.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs bit inversion to color difference.</ul>	*/
	kuint16			c_fixed_enable;				/**< YCRVFX.CFIXEN : Enable of Chroma fixed control (1bit) <br>
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : No operation.
													<li>@ref ImR2yCtrl_ENABLE_ON : Sets color difference fixing enable.</ul>			*/
	kint16			cb_fixed;					/**< CFIX.CFIXB : When enabled, c_fixed_enable is the value
																  that you set the component Cb. (10bits signed)					*/
	kint16			cr_fixed;					/**< CFIX.CFIXR : When enabled, c_fixed_enable is the value
																  that you set the component Cr. (10bits signed)					*/
	kint16			y_offset;					/**< YCOF.YOF : YOF is added to Y component processed
																by color difference reduction. (11bits signed)						*/
	kint16			cb_offset;					/**< YCOF.COFB : (512d + COFB setting value) is added to Cb component processed
																 by color difference reduction. (11bits signed)						*/
	kint16			cr_offset;					/**< YCOF.COFR : (512d + COFR setting value) is added to Cr component processed
																 by color difference reduction. (11bits signed)						*/
} R2yCtrlCs;								/* Chroma Suppress control	*/

/* @} */	// im_r2y_iq group

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
//------------ for RDMA ----------------
/** Post-resize edge enhancement0 control register address info (for RDMA)
*/
typedef struct {
	kulong	EE0CTL;					/**< 2841_(C400 - C403h) */
	kulong	EE0HPFK1;				/**< 2841_(C408 - C40Bh) */
	kulong	EE0HPFK2;				/**< 2841_(C40C - C40Fh) */
	kulong	EE0NRLV;				/**< 2841_(C410 - C413h) */
	kulong	EE0CORPOF;				/**< 2841_(C414 - C417h) */
	kulong	EE0CORPGA;				/**< 2841_(C418 - C41Bh) */
	kulong	EE0CORPBD;				/**< 2841_(C41C - C41Fh) */
	kulong	EE0CORMOF;				/**< 2841_(C420 - C423h) */
	kulong	EE0CORMGA;				/**< 2841_(C424 - C427h) */
	kulong	EE0CORMBD;				/**< 2841_(C428 - C42Bh) */
	kulong	EE0SCLSUP;				/**< 2841_(C42C - C42Fh) */
	kulong	EE0SCLPOF1;				/**< 2841_(C430 - C433h) */
	kulong	EE0SCLPOF2;				/**< 2841_(C434 - C437h) */
	kulong	EE0SCLPOF3;				/**< 2841_(C438 - C43Bh) */
	kulong	EE0SCLPGA1;				/**< 2841_(C440 - C443h) */
	kulong	EE0SCLPGA2;				/**< 2841_(C444 - C447h) */
	kulong	EE0SCLPGA3;				/**< 2841_(C448 - C44Bh) */
	kulong	EE0SCLPGA4;				/**< 2841_(C44C - C44Fh) */
	kulong	EE0SCLPGA5;				/**< 2841_(C450 - C453h) */
	kulong	EE0SCLPBD1;				/**< 2841_(C460 - C463h) */
	kulong	EE0SCLPBD2;				/**< 2841_(C464 - C467h) */
	kulong	EE0SCLPBD3;				/**< 2841_(C468 - C46Bh) */
	kulong	EE0SCLMOF1;				/**< 2841_(C470 - C473h) */
	kulong	EE0SCLMOF2;				/**< 2841_(C474 - C477h) */
	kulong	EE0SCLMOF3;				/**< 2841_(C478 - C47Bh) */
	kulong	EE0SCLMGA1;				/**< 2841_(C480 - C483h) */
	kulong	EE0SCLMGA2;				/**< 2841_(C484 - C487h) */
	kulong	EE0SCLMGA3;				/**< 2841_(C488 - C48Bh) */
	kulong	EE0SCLMGA4;				/**< 2841_(C48C - C48Fh) */
	kulong	EE0SCLMGA5;				/**< 2841_(C490 - C493h) */
	kulong	EE0SCLMBD1;				/**< 2841_(C4A0 - C4A3h) */
	kulong	EE0SCLMBD2;				/**< 2841_(C4A4 - C4A7h) */
	kulong	EE0SCLMBD3;				/**< 2841_(C4A8 - C4ABh) */
	kulong	EE0TONPOF1;				/**< 2841_(C4B0 - C4B3h) */
	kulong	EE0TONPOF2;				/**< 2841_(C4B4 - C4B7h) */
	kulong	EE0TONPGA1;				/**< 2841_(C4C0 - C4C3h) */
	kulong	EE0TONPGA2;				/**< 2841_(C4C4 - C4C7h) */
	kulong	EE0TONPGA3;				/**< 2841_(C4C8 - C4CBh) */
	kulong	EE0TONPBD;				/**< 2841_(C4D0 - C4D3h) */
	kulong	EE0TONMOF1;				/**< 2841_(C4D8 - C4DBh) */
	kulong	EE0TONMOF2;				/**< 2841_(C4DC - C4DFh) */
	kulong	EE0TONMGA1;				/**< 2841_(C4E0 - C4E3h) */
	kulong	EE0TONMGA2;				/**< 2841_(C4E4 - C4E7h) */
	kulong	EE0TONMGA3;				/**< 2841_(C4E8 - C4EBh) */
	kulong	EE0TONMBD;				/**< 2841_(C4F0 - C4F3h) */
	kulong	EE0CLPPOF;				/**< 2841_(C4F4 - C4F7h) */
	kulong	EE0CLPPGA;				/**< 2841_(C4F8 - C4FBh) */
	kulong	EE0CLPPBD;				/**< 2841_(C4FC - C4FFh) */
	kulong	EE0CLPMOF;				/**< 2841_(C500 - C503h) */
	kulong	EE0CLPMGA;				/**< 2841_(C504 - C507h) */
	kulong	EE0CLPMBD;				/**< 2841_(C508 - C50Bh) */
} CtrlRdmaEe0Addr;

/** Post-resize edge enhancement1 control register address info (for RDMA)
*/
typedef struct {
	kulong	EE1CTL;					/**< 2841_(C600 - C603h) */
	kulong	EE1HPFK1;				/**< 2841_(C608 - C60Bh) */
	kulong	EE1HPFK2;				/**< 2841_(C60C - C60Fh) */
	kulong	EE1NRLV;				/**< 2841_(C610 - C613h) */
	kulong	EE1CORPOF1;				/**< 2841_(C618 - C61Bh) */
	kulong	EE1CORPOF2;				/**< 2841_(C61C - C61Fh) */
	kulong	EE1CORPGA;				/**< 2841_(C620 - C623h) */
	kulong	EE1CORPBD1;				/**< 2841_(C628 - C62Bh) */
	kulong	EE1CORPBD2;				/**< 2841_(C62C - C62Fh) */
	kulong	EE1CORMOF1;				/**< 2841_(C630 - C633h) */
	kulong	EE1CORMOF2;				/**< 2841_(C634 - C637h) */
	kulong	EE1CORMGA;				/**< 2841_(C638 - C63Bh) */
	kulong	EE1CORMBD1;				/**< 2841_(C640 - C643h) */
	kulong	EE1CORMBD2;				/**< 2841_(C644 - C647h) */
	kulong	EE1SCLSUP;				/**< 2841_(C648 - C64Bh) */
	kulong	EE1SCLPOF1;				/**< 2841_(C650 - C653h) */
	kulong	EE1SCLPOF2;				/**< 2841_(C654 - C657h) */
	kulong	EE1SCLPOF3;				/**< 2841_(C658 - C65Bh) */
	kulong	EE1SCLPGA1;				/**< 2841_(C660 - C663h) */
	kulong	EE1SCLPGA2;				/**< 2841_(C664 - C667h) */
	kulong	EE1SCLPGA3;				/**< 2841_(C668 - C66Bh) */
	kulong	EE1SCLPGA4;				/**< 2841_(C66C - C66Fh) */
	kulong	EE1SCLPGA5;				/**< 2841_(C670 - C673h) */
	kulong	EE1SCLPBD1;				/**< 2841_(C680 - C683h) */
	kulong	EE1SCLPBD2;				/**< 2841_(C684 - C687h) */
	kulong	EE1SCLPBD3;				/**< 2841_(C688 - C68Bh) */
	kulong	EE1SCLPBD4;				/**< 2841_(C68C - C68Fh) */
	kulong	EE1SCLPBD5;				/**< 2841_(C690 - C693h) */
	kulong	EE1SCLMOF1;				/**< 2841_(C6A0 - C6A3h) */
	kulong	EE1SCLMOF2;				/**< 2841_(C6A4 - C6A7h) */
	kulong	EE1SCLMOF3;				/**< 2841_(C6A8 - C6ABh) */
	kulong	EE1SCLMGA1;				/**< 2841_(C6C0 - C6C3h) */
	kulong	EE1SCLMGA2;				/**< 2841_(C6C4 - C6C7h) */
	kulong	EE1SCLMGA3;				/**< 2841_(C6C8 - C6CBh) */
	kulong	EE1SCLMGA4;				/**< 2841_(C6CC - C6CFh) */
	kulong	EE1SCLMGA5;				/**< 2841_(C6D0 - C6D3h) */
	kulong	EE1SCLMBD1;				/**< 2841_(C6E0 - C6E3h) */
	kulong	EE1SCLMBD2;				/**< 2841_(C6E4 - C6E7h) */
	kulong	EE1SCLMBD3;				/**< 2841_(C6E8 - C6EBh) */
	kulong	EE1SCLMBD4;				/**< 2841_(C6EC - C6EFh) */
	kulong	EE1SCLMBD5;				/**< 2841_(C6F0 - C6F3h) */
	kulong	EE1TONPOF1;				/**< 2841_(C700 - C703h) */
	kulong	EE1TONPOF2;				/**< 2841_(C704 - C707h) */
	kulong	EE1TONPOF3;				/**< 2841_(C708 - C70Bh) */
	kulong	EE1TONPGA1;				/**< 2841_(C710 - C713h) */
	kulong	EE1TONPGA2;				/**< 2841_(C714 - C717h) */
	kulong	EE1TONPGA3;				/**< 2841_(C718 - C71Bh) */
	kulong	EE1TONPBD1;				/**< 2841_(C720 - C723h) */
	kulong	EE1TONPBD2;				/**< 2841_(C724 - C727h) */
	kulong	EE1TONMOF1;				/**< 2841_(C730 - C733h) */
	kulong	EE1TONMOF2;				/**< 2841_(C734 - C737h) */
	kulong	EE1TONMOF3;				/**< 2841_(C738 - C73Bh) */
	kulong	EE1TONMGA1;				/**< 2841_(C740 - C743h) */
	kulong	EE1TONMGA2;				/**< 2841_(C744 - C747h) */
	kulong	EE1TONMGA3;				/**< 2841_(C748 - C74Bh) */
	kulong	EE1TONMBD1;				/**< 2841_(C750 - C753h) */
	kulong	EE1TONMBD2;				/**< 2841_(C754 - C757h) */
	kulong	EE1CLPPOF1;				/**< 2841_(C758 - C75Bh) */
	kulong	EE1CLPPOF2;				/**< 2841_(C75C - C75Fh) */
	kulong	EE1CLPPGA;				/**< 2841_(C760 - C763h) */
	kulong	EE1CLPPBD;				/**< 2841_(C764 - C767h) */
	kulong	EE1CLPMOF1;				/**< 2841_(C768 - C76Bh) */
	kulong	EE1CLPMOF2;				/**< 2841_(C76C - C76Fh) */
	kulong	EE1CLPMGA;				/**< 2841_(C770 - C773h) */
	kulong	EE1CLPMBD;				/**< 2841_(C774 - C777h) */
} CtrlRdmaEe1Addr;

/** Deknee Table(R/G/B) register address info (for RDMA)
*/
typedef struct {
	kulong	DKNTBL[128];			/**< 294A_(E000 - E1FFh) */
									/**< 294A_(E200 - E3FFh) */
									/**< 294A_(E400 - E5FFh) */
} RdmaDekneeTblAddr;

/** Offset control register address info (for RDMA)
*/
typedef struct {
	kulong	OFST1;					/**< 2841_(8020 - 8023h) */
	kulong	OFST2;					/**< 2841_(8024 - 8027h) */
} T_IM_R2Y_CTRL_RDMA_OFST_ADDR;

/** WB clip control register address info (for RDMA)
*/
typedef struct {
	kulong	WBLV1;					/**< 2841_(8030 - 8033h) */
	kulong	WBLV2;					/**< 2841_(8034 - 8037h) */
} RdmaWbClipAddr;

/** CC0 matrix control register address info (for RDMA)
*/
typedef struct {
	kulong	CC0CTL;					/**< 2841_(8080 - 8083h) */
	kulong	CC0K1;					/**< 2841_(80A0 - 80A3h) */
	kulong	CC0K2;					/**< 2841_(80A4 - 80A7h) */
	kulong	CC0K3;					/**< 2841_(80A8 - 80ABh) */
	kulong	CC0K4;					/**< 2841_(80AC - 80AFh) */
	kulong	CC0K5;					/**< 2841_(80B0 - 80B3h) */
	kulong	CC0YBOF1;				/**< 2841_(80C0 - 80C3h) */
	kulong	CC0YBOF2;				/**< 2841_(80C4 - 80C7h) */
	kulong	CC0YBGA1;				/**< 2841_(80C8 - 80CBh) */
	kulong	CC0YBGA2;				/**< 2841_(80CC - 80CFh) */
	kulong	CC0YBBD;				/**< 2841_(80D0 - 80D3h) */
	kulong	CCYC;					/**< 2841_(80D4 - 80D7h) */
} CtrlRdmaCc0Addr;

/** CC0 matrix coefficient control register address info (for RDMA)
*/
typedef struct {
	kulong	CC0K1;					/**< 2841_(80A0 - 80A3h) */
	kulong	CC0K2;					/**< 2841_(80A4 - 80A7h) */
	kulong	CC0K3;					/**< 2841_(80A8 - 80ABh) */
	kulong	CC0K4;					/**< 2841_(80AC - 80AFh) */
	kulong	CC0K5;					/**< 2841_(80B0 - 80B3h) */
} RdmaCc0CoefAddr;

/** Multi Axis control register address info (for RDMA)
*/
typedef struct {
	kulong	MCYC1;					/**< 2841_(9000 - 9003h) */
	kulong	MCYC2;					/**< 2841_(9004 - 9007h) */
	kulong	MCYC3;					/**< 2841_(9008 - 900Bh) */
	kulong	MCYC4;					/**< 2841_(900C - 900Fh) */
	kulong	MCYC5;					/**< 2841_(9000 - 9013h) */
	kulong	MCB1AB;					/**< 2841_(9020 - 9023h) */
	kulong	MCB1CD;					/**< 2841_(9024 - 9027h) */
	kulong	MCB2AB;					/**< 2841_(9028 - 902Bh) */
	kulong	MCB2CD;					/**< 2841_(902C - 902Fh) */
	kulong	MCB3AB;					/**< 2841_(9030 - 9033h) */
	kulong	MCB3CD;					/**< 2841_(9034 - 9037h) */
	kulong	MCB4AB;					/**< 2841_(9038 - 903Bh) */
	kulong	MCB4CD;					/**< 2841_(903C - 903Fh) */
	kulong	MCID1;					/**< 2841_(9040 - 9043h) */
	kulong	MCID2;					/**< 2841_(9044 - 9047h) */
	kulong	MCID3;					/**< 2841_(9048 - 904Bh) */
	kulong	MCID4;					/**< 2841_(904C - 904Fh) */
	kulong	MCKA1;					/**< 2841_(9080 - 9083h) */
	kulong	MCKA2;					/**< 2841_(9084 - 9087h) */
	kulong	MCKA3;					/**< 2841_(9088 - 908Bh) */
	kulong	MCKA4;					/**< 2841_(908C - 908Fh) */
	kulong	MCKA5;					/**< 2841_(9090 - 9093h) */
	kulong	MCKA6;					/**< 2841_(9094 - 9097h) */
	kulong	MCKA7;					/**< 2841_(9098 - 909Bh) */
	kulong	MCKA8;					/**< 2841_(909C - 909Fh) */
	kulong	MCKA9;					/**< 2841_(90A0 - 90A3h) */
	kulong	MCKA10;					/**< 2841_(90A4 - 90A7h) */
	kulong	MCKA11;					/**< 2841_(90A8 - 90ABh) */
	kulong	MCKA12;					/**< 2841_(90AC - 90AFh) */
	kulong	MCKA13;					/**< 2841_(90B0 - 90B3h) */
	kulong	MCKA14;					/**< 2841_(90B4 - 90B7h) */
	kulong	MCKA15;					/**< 2841_(90B8 - 90BBh) */
	kulong	MCKA16;					/**< 2841_(90BC - 90BFh) */
	kulong	MCKA17;					/**< 2841_(90C0 - 90C3h) */
	kulong	MCKA18;					/**< 2841_(90C4 - 90C7h) */
	kulong	MCKA19;					/**< 2841_(90C8 - 90CBh) */
	kulong	MCKA20;					/**< 2841_(90CC - 90CFh) */
	kulong	MCKA21;					/**< 2841_(90D0 - 90D3h) */
	kulong	MCKA22;					/**< 2841_(90D4 - 90D7h) */
	kulong	MCKA23;					/**< 2841_(90D8 - 90DBh) */
	kulong	MCKA24;					/**< 2841_(90DC - 90DFh) */
	kulong	MCKA25;					/**< 2841_(90E0 - 90E3h) */
	kulong	MCKB1;					/**< 2841_(9100 - 9103h) */
	kulong	MCKB2;					/**< 2841_(9104 - 9107h) */
	kulong	MCKB3;					/**< 2841_(9108 - 910Bh) */
	kulong	MCKB4;					/**< 2841_(910C - 910Fh) */
	kulong	MCKB5;					/**< 2841_(9110 - 9113h) */
	kulong	MCKB6;					/**< 2841_(9114 - 9117h) */
	kulong	MCKB7;					/**< 2841_(9118 - 911Bh) */
	kulong	MCKB8;					/**< 2841_(911C - 911Fh) */
	kulong	MCKB9;					/**< 2841_(9120 - 9123h) */
	kulong	MCKB10;					/**< 2841_(9124 - 9127h) */
	kulong	MCKB11;					/**< 2841_(9128 - 912Bh) */
	kulong	MCKB12;					/**< 2841_(912C - 912Fh) */
	kulong	MCKB13;					/**< 2841_(9130 - 9133h) */
	kulong	MCKB14;					/**< 2841_(9134 - 9137h) */
	kulong	MCKB15;					/**< 2841_(9138 - 913Bh) */
	kulong	MCKB16;					/**< 2841_(913C - 913Fh) */
	kulong	MCKB17;					/**< 2841_(9140 - 9143h) */
	kulong	MCKB18;					/**< 2841_(9144 - 9147h) */
	kulong	MCKB19;					/**< 2841_(9148 - 914Bh) */
	kulong	MCKB20;					/**< 2841_(914C - 914Fh) */
	kulong	MCKB21;					/**< 2841_(9150 - 9153h) */
	kulong	MCKB22;					/**< 2841_(9154 - 9157h) */
	kulong	MCKB23;					/**< 2841_(9158 - 915Bh) */
	kulong	MCKB24;					/**< 2841_(915C - 915Fh) */
	kulong	MCKB25;					/**< 2841_(9160 - 9163h) */
	kulong	MCKC1;					/**< 2841_(9180 - 9183h) */
	kulong	MCKC2;					/**< 2841_(9184 - 9187h) */
	kulong	MCKC3;					/**< 2841_(9188 - 918Bh) */
	kulong	MCKC4;					/**< 2841_(918C - 918Fh) */
	kulong	MCKC5;					/**< 2841_(9190 - 9193h) */
	kulong	MCKC6;					/**< 2841_(9194 - 9197h) */
	kulong	MCKC7;					/**< 2841_(9198 - 919Bh) */
	kulong	MCKC8;					/**< 2841_(919C - 919Fh) */
	kulong	MCKC9;					/**< 2841_(91A0 - 91A3h) */
	kulong	MCKC10;					/**< 2841_(91A4 - 91A7h) */
	kulong	MCKC11;					/**< 2841_(91A8 - 91ABh) */
	kulong	MCKC12;					/**< 2841_(91AC - 91AFh) */
	kulong	MCKC13;					/**< 2841_(91B0 - 91B3h) */
	kulong	MCKC14;					/**< 2841_(91B4 - 91B7h) */
	kulong	MCKC15;					/**< 2841_(91B8 - 91BBh) */
	kulong	MCKC16;					/**< 2841_(91BC - 91BFh) */
	kulong	MCKC17;					/**< 2841_(91C0 - 91C3h) */
	kulong	MCKC18;					/**< 2841_(91C4 - 91C7h) */
	kulong	MCKC19;					/**< 2841_(91C8 - 91CBh) */
	kulong	MCKC20;					/**< 2841_(91CC - 91CFh) */
	kulong	MCKC21;					/**< 2841_(91D0 - 91D3h) */
	kulong	MCKC22;					/**< 2841_(91D4 - 91D7h) */
	kulong	MCKC23;					/**< 2841_(91D8 - 91DBh) */
	kulong	MCKC24;					/**< 2841_(91DC - 91DFh) */
	kulong	MCKC25;					/**< 2841_(91E0 - 91E3h) */
	kulong	MCKD1;					/**< 2841_(9200 - 9203h) */
	kulong	MCKD2;					/**< 2841_(9204 - 9207h) */
	kulong	MCKD3;					/**< 2841_(9208 - 920Bh) */
	kulong	MCKD4;					/**< 2841_(920C - 920Fh) */
	kulong	MCKD5;					/**< 2841_(9210 - 9213h) */
	kulong	MCKD6;					/**< 2841_(9214 - 9217h) */
	kulong	MCKD7;					/**< 2841_(9218 - 921Bh) */
	kulong	MCKD8;					/**< 2841_(921C - 921Fh) */
	kulong	MCKD9;					/**< 2841_(9220 - 9223h) */
	kulong	MCKD10;					/**< 2841_(9224 - 9227h) */
	kulong	MCKD11;					/**< 2841_(9228 - 922Bh) */
	kulong	MCKD12;					/**< 2841_(922C - 922Fh) */
	kulong	MCKD13;					/**< 2841_(9230 - 9233h) */
	kulong	MCKD14;					/**< 2841_(9234 - 9237h) */
	kulong	MCKD15;					/**< 2841_(9238 - 923Bh) */
	kulong	MCKD16;					/**< 2841_(923C - 923Fh) */
	kulong	MCKD17;					/**< 2841_(9240 - 9243h) */
	kulong	MCKD18;					/**< 2841_(9244 - 9247h) */
	kulong	MCKD19;					/**< 2841_(9248 - 924Bh) */
	kulong	MCKD20;					/**< 2841_(924C - 924Fh) */
	kulong	MCKD21;					/**< 2841_(9250 - 9253h) */
	kulong	MCKD22;					/**< 2841_(9254 - 9257h) */
	kulong	MCKD23;					/**< 2841_(9258 - 925Bh) */
	kulong	MCKD24;					/**< 2841_(925C - 925Fh) */
	kulong	MCKD25;					/**< 2841_(9260 - 9263h) */
	kulong	MCKE1;					/**< 2841_(9280 - 9283h) */
	kulong	MCKE2;					/**< 2841_(9284 - 9287h) */
	kulong	MCKE3;					/**< 2841_(9288 - 928Bh) */
	kulong	MCKE4;					/**< 2841_(928C - 928Fh) */
	kulong	MCKE5;					/**< 2841_(9290 - 9293h) */
	kulong	MCKE6;					/**< 2841_(9294 - 9297h) */
	kulong	MCKE7;					/**< 2841_(9298 - 929Bh) */
	kulong	MCKE8;					/**< 2841_(929C - 929Fh) */
	kulong	MCKE9;					/**< 2841_(92A0 - 92A3h) */
	kulong	MCKE10;					/**< 2841_(92A4 - 92A7h) */
	kulong	MCKE11;					/**< 2841_(92A8 - 92ABh) */
	kulong	MCKE12;					/**< 2841_(92AC - 92AFh) */
	kulong	MCKE13;					/**< 2841_(92B0 - 92B3h) */
	kulong	MCKE14;					/**< 2841_(92B4 - 92B7h) */
	kulong	MCKE15;					/**< 2841_(92B8 - 92BBh) */
	kulong	MCKE16;					/**< 2841_(92BC - 92BFh) */
	kulong	MCKE17;					/**< 2841_(92C0 - 92C3h) */
	kulong	MCKE18;					/**< 2841_(92C4 - 92C7h) */
	kulong	MCKE19;					/**< 2841_(92C8 - 92CBh) */
	kulong	MCKE20;					/**< 2841_(92CC - 92CFh) */
	kulong	MCKE21;					/**< 2841_(92D0 - 92D3h) */
	kulong	MCKE22;					/**< 2841_(92D4 - 92D7h) */
	kulong	MCKE23;					/**< 2841_(92D8 - 92DBh) */
	kulong	MCKE24;					/**< 2841_(92DC - 92DFh) */
	kulong	MCKE25;					/**< 2841_(92E0 - 92E3h) */
	kulong	MCKF1;					/**< 2841_(9300 - 9303h) */
	kulong	MCKF2;					/**< 2841_(9304 - 9307h) */
	kulong	MCKF3;					/**< 2841_(9308 - 930Bh) */
	kulong	MCKF4;					/**< 2841_(930C - 930Fh) */
	kulong	MCKF5;					/**< 2841_(9310 - 9313h) */
	kulong	MCKF6;					/**< 2841_(9314 - 9317h) */
	kulong	MCKF7;					/**< 2841_(9318 - 931Bh) */
	kulong	MCKF8;					/**< 2841_(931C - 931Fh) */
	kulong	MCKF9;					/**< 2841_(9320 - 9323h) */
	kulong	MCKF10;					/**< 2841_(9324 - 9327h) */
	kulong	MCKF11;					/**< 2841_(9328 - 932Bh) */
	kulong	MCKF12;					/**< 2841_(932C - 932Fh) */
	kulong	MCKF13;					/**< 2841_(9330 - 9333h) */
	kulong	MCKF14;					/**< 2841_(9334 - 9337h) */
	kulong	MCKF15;					/**< 2841_(9338 - 933Bh) */
	kulong	MCKF16;					/**< 2841_(933C - 933Fh) */
	kulong	MCKF17;					/**< 2841_(9340 - 9343h) */
	kulong	MCKF18;					/**< 2841_(9344 - 9347h) */
	kulong	MCKF19;					/**< 2841_(9348 - 934Bh) */
	kulong	MCKF20;					/**< 2841_(934C - 934Fh) */
	kulong	MCKF21;					/**< 2841_(9350 - 9353h) */
	kulong	MCKF22;					/**< 2841_(9354 - 9357h) */
	kulong	MCKF23;					/**< 2841_(9358 - 935Bh) */
	kulong	MCKF24;					/**< 2841_(935C - 935Fh) */
	kulong	MCKF25;					/**< 2841_(9360 - 9363h) */
	kulong	MCKG1;					/**< 2841_(9380 - 9383h) */
	kulong	MCKG2;					/**< 2841_(9384 - 9387h) */
	kulong	MCKG3;					/**< 2841_(9388 - 938Bh) */
	kulong	MCKG4;					/**< 2841_(938C - 938Fh) */
	kulong	MCKG5;					/**< 2841_(9390 - 9393h) */
	kulong	MCKG6;					/**< 2841_(9394 - 9397h) */
	kulong	MCKG7;					/**< 2841_(9398 - 939Bh) */
	kulong	MCKG8;					/**< 2841_(939C - 939Fh) */
	kulong	MCKG9;					/**< 2841_(93A0 - 93A3h) */
	kulong	MCKG10;					/**< 2841_(93A4 - 93A7h) */
	kulong	MCKG11;					/**< 2841_(93A8 - 93ABh) */
	kulong	MCKG12;					/**< 2841_(93AC - 93AFh) */
	kulong	MCKG13;					/**< 2841_(93B0 - 93B3h) */
	kulong	MCKG14;					/**< 2841_(93B4 - 93B7h) */
	kulong	MCKG15;					/**< 2841_(93B8 - 93BBh) */
	kulong	MCKG16;					/**< 2841_(93BC - 93BFh) */
	kulong	MCKG17;					/**< 2841_(93C0 - 93C3h) */
	kulong	MCKG18;					/**< 2841_(93C4 - 93C7h) */
	kulong	MCKG19;					/**< 2841_(93C8 - 93CBh) */
	kulong	MCKG20;					/**< 2841_(93CC - 93CFh) */
	kulong	MCKG21;					/**< 2841_(93D0 - 93D3h) */
	kulong	MCKG22;					/**< 2841_(93D4 - 93D7h) */
	kulong	MCKG23;					/**< 2841_(93D8 - 93DBh) */
	kulong	MCKG24;					/**< 2841_(93DC - 93DFh) */
	kulong	MCKG25;					/**< 2841_(93E0 - 93E3h) */
	kulong	MCKH1;					/**< 2841_(9400 - 9403h) */
	kulong	MCKH2;					/**< 2841_(9404 - 9407h) */
	kulong	MCKH3;					/**< 2841_(9408 - 940Bh) */
	kulong	MCKH4;					/**< 2841_(940C - 940Fh) */
	kulong	MCKH5;					/**< 2841_(9410 - 9413h) */
	kulong	MCKH6;					/**< 2841_(9414 - 9417h) */
	kulong	MCKH7;					/**< 2841_(9418 - 941Bh) */
	kulong	MCKH8;					/**< 2841_(941C - 941Fh) */
	kulong	MCKH9;					/**< 2841_(9420 - 9423h) */
	kulong	MCKH10;					/**< 2841_(9424 - 9427h) */
	kulong	MCKH11;					/**< 2841_(9428 - 942Bh) */
	kulong	MCKH12;					/**< 2841_(942C - 942Fh) */
	kulong	MCKH13;					/**< 2841_(9430 - 9433h) */
	kulong	MCKH14;					/**< 2841_(9434 - 9437h) */
	kulong	MCKH15;					/**< 2841_(9438 - 943Bh) */
	kulong	MCKH16;					/**< 2841_(943C - 943Fh) */
	kulong	MCKH17;					/**< 2841_(9440 - 9443h) */
	kulong	MCKH18;					/**< 2841_(9444 - 9447h) */
	kulong	MCKH19;					/**< 2841_(9448 - 944Bh) */
	kulong	MCKH20;					/**< 2841_(944C - 944Fh) */
	kulong	MCKH21;					/**< 2841_(9450 - 9453h) */
	kulong	MCKH22;					/**< 2841_(9454 - 9457h) */
	kulong	MCKH23;					/**< 2841_(9458 - 945Bh) */
	kulong	MCKH24;					/**< 2841_(945C - 945Fh) */
	kulong	MCKH25;					/**< 2841_(9460 - 9463h) */
	kulong	MCKI1;					/**< 2841_(9480 - 9483h) */
	kulong	MCKI2;					/**< 2841_(9484 - 9487h) */
	kulong	MCKI3;					/**< 2841_(9488 - 948Bh) */
	kulong	MCKI4;					/**< 2841_(948C - 948Fh) */
	kulong	MCKI5;					/**< 2841_(9490 - 9493h) */
	kulong	MCKI6;					/**< 2841_(9494 - 9497h) */
	kulong	MCKI7;					/**< 2841_(9498 - 949Bh) */
	kulong	MCKI8;					/**< 2841_(949C - 949Fh) */
	kulong	MCKI9;					/**< 2841_(94A0 - 94A3h) */
	kulong	MCKI10;					/**< 2841_(94A4 - 94A7h) */
	kulong	MCKI11;					/**< 2841_(94A8 - 94ABh) */
	kulong	MCKI12;					/**< 2841_(94AC - 94AFh) */
	kulong	MCKI13;					/**< 2841_(94B0 - 94B3h) */
	kulong	MCKI14;					/**< 2841_(94B4 - 94B7h) */
	kulong	MCKI15;					/**< 2841_(94B8 - 94BBh) */
	kulong	MCKI16;					/**< 2841_(94BC - 94BFh) */
	kulong	MCKI17;					/**< 2841_(94C0 - 94C3h) */
	kulong	MCKI18;					/**< 2841_(94C4 - 94C7h) */
	kulong	MCKI19;					/**< 2841_(94C8 - 94CBh) */
	kulong	MCKI20;					/**< 2841_(94CC - 94CFh) */
	kulong	MCKI21;					/**< 2841_(94D0 - 94D3h) */
	kulong	MCKI22;					/**< 2841_(94D4 - 94D7h) */
	kulong	MCKI23;					/**< 2841_(94D8 - 94DBh) */
	kulong	MCKI24;					/**< 2841_(94DC - 94DFh) */
	kulong	MCKI25;					/**< 2841_(94E0 - 94E3h) */
	kulong	MCKJ1;					/**< 2841_(9500 - 9503h) */
	kulong	MCKJ2;					/**< 2841_(9504 - 9507h) */
	kulong	MCKJ3;					/**< 2841_(9508 - 950Bh) */
	kulong	MCKJ4;					/**< 2841_(950C - 950Fh) */
	kulong	MCKJ5;					/**< 2841_(9510 - 9513h) */
	kulong	MCKJ6;					/**< 2841_(9514 - 9517h) */
	kulong	MCKJ7;					/**< 2841_(9518 - 951Bh) */
	kulong	MCKJ8;					/**< 2841_(951C - 951Fh) */
	kulong	MCKJ9;					/**< 2841_(9520 - 9523h) */
	kulong	MCKJ10;					/**< 2841_(9524 - 9527h) */
	kulong	MCKJ11;					/**< 2841_(9528 - 952Bh) */
	kulong	MCKJ12;					/**< 2841_(952C - 952Fh) */
	kulong	MCKJ13;					/**< 2841_(9530 - 9533h) */
	kulong	MCKJ14;					/**< 2841_(9534 - 9537h) */
	kulong	MCKJ15;					/**< 2841_(9538 - 953Bh) */
	kulong	MCKJ16;					/**< 2841_(953C - 953Fh) */
	kulong	MCKJ17;					/**< 2841_(9540 - 9543h) */
	kulong	MCKJ18;					/**< 2841_(9544 - 9547h) */
	kulong	MCKJ19;					/**< 2841_(9548 - 954Bh) */
	kulong	MCKJ20;					/**< 2841_(954C - 954Fh) */
	kulong	MCKJ21;					/**< 2841_(9550 - 9553h) */
	kulong	MCKJ22;					/**< 2841_(9554 - 9557h) */
	kulong	MCKJ23;					/**< 2841_(9558 - 955Bh) */
	kulong	MCKJ24;					/**< 2841_(955C - 955Fh) */
	kulong	MCKJ25;					/**< 2841_(9560 - 9563h) */
	kulong	MCKK1;					/**< 2841_(9580 - 9583h) */
	kulong	MCKK2;					/**< 2841_(9584 - 9587h) */
	kulong	MCKK3;					/**< 2841_(9588 - 958Bh) */
	kulong	MCKK4;					/**< 2841_(958C - 958Fh) */
	kulong	MCKK5;					/**< 2841_(9590 - 9593h) */
	kulong	MCKK6;					/**< 2841_(9594 - 9597h) */
	kulong	MCKK7;					/**< 2841_(9598 - 959Bh) */
	kulong	MCKK8;					/**< 2841_(959C - 959Fh) */
	kulong	MCKK9;					/**< 2841_(95A0 - 95A3h) */
	kulong	MCKK10;					/**< 2841_(95A4 - 95A7h) */
	kulong	MCKK11;					/**< 2841_(95A8 - 95ABh) */
	kulong	MCKK12;					/**< 2841_(95AC - 95AFh) */
	kulong	MCKK13;					/**< 2841_(95B0 - 95B3h) */
	kulong	MCKK14;					/**< 2841_(95B4 - 95B7h) */
	kulong	MCKK15;					/**< 2841_(95B8 - 95BBh) */
	kulong	MCKK16;					/**< 2841_(95BC - 95BFh) */
	kulong	MCKK17;					/**< 2841_(95C0 - 95C3h) */
	kulong	MCKK18;					/**< 2841_(95C4 - 95C7h) */
	kulong	MCKK19;					/**< 2841_(95C8 - 95CBh) */
	kulong	MCKK20;					/**< 2841_(95CC - 95CFh) */
	kulong	MCKK21;					/**< 2841_(95D0 - 95D3h) */
	kulong	MCKK22;					/**< 2841_(95D4 - 95D7h) */
	kulong	MCKK23;					/**< 2841_(95D8 - 95DBh) */
	kulong	MCKK24;					/**< 2841_(95DC - 95DFh) */
	kulong	MCKK25;					/**< 2841_(95E0 - 95E3h) */
	kulong	MCKL1;					/**< 2841_(9600 - 9603h) */
	kulong	MCKL2;					/**< 2841_(9604 - 9607h) */
	kulong	MCKL3;					/**< 2841_(9608 - 960Bh) */
	kulong	MCKL4;					/**< 2841_(960C - 960Fh) */
	kulong	MCKL5;					/**< 2841_(9610 - 9613h) */
	kulong	MCKL6;					/**< 2841_(9614 - 9617h) */
	kulong	MCKL7;					/**< 2841_(9618 - 961Bh) */
	kulong	MCKL8;					/**< 2841_(961C - 961Fh) */
	kulong	MCKL9;					/**< 2841_(9620 - 9623h) */
	kulong	MCKL10;					/**< 2841_(9624 - 9627h) */
	kulong	MCKL11;					/**< 2841_(9628 - 962Bh) */
	kulong	MCKL12;					/**< 2841_(962C - 962Fh) */
	kulong	MCKL13;					/**< 2841_(9630 - 9633h) */
	kulong	MCKL14;					/**< 2841_(9634 - 9637h) */
	kulong	MCKL15;					/**< 2841_(9638 - 963Bh) */
	kulong	MCKL16;					/**< 2841_(963C - 963Fh) */
	kulong	MCKL17;					/**< 2841_(9640 - 9643h) */
	kulong	MCKL18;					/**< 2841_(9644 - 9647h) */
	kulong	MCKL19;					/**< 2841_(9648 - 964Bh) */
	kulong	MCKL20;					/**< 2841_(964C - 964Fh) */
	kulong	MCKL21;					/**< 2841_(9650 - 9653h) */
	kulong	MCKL22;					/**< 2841_(9654 - 9657h) */
	kulong	MCKL23;					/**< 2841_(9658 - 965Bh) */
	kulong	MCKL24;					/**< 2841_(965C - 965Fh) */
	kulong	MCKL25;					/**< 2841_(9660 - 9663h) */
	kulong	MCLA1;					/**< 2841_(9680 - 9683h) */
	kulong	MCLA2;					/**< 2841_(9684 - 9687h) */
	kulong	MCLA3;					/**< 2841_(9688 - 968Bh) */
	kulong	MCLA4;					/**< 2841_(968C - 96BFh) */
	kulong	MCLA5;					/**< 2841_(9690 - 9693h) */
	kulong	MCLA6;					/**< 2841_(9694 - 9697h) */
	kulong	MCLA7;					/**< 2841_(9698 - 969Bh) */
	kulong	MCLA8;					/**< 2841_(969C - 969Fh) */
	kulong	MCLA9;					/**< 2841_(96A0 - 96A3h) */
	kulong	MCLA10;					/**< 2841_(96A4 - 96A7h) */
	kulong	MCLA11;					/**< 2841_(96A8 - 96ABh) */
	kulong	MCLA12;					/**< 2841_(96AC - 96AFh) */
	kulong	MCLA13;					/**< 2841_(96B0 - 96B3h) */
	kulong	MCLA14;					/**< 2841_(96B4 - 96B7h) */
	kulong	MCLA15;					/**< 2841_(96B8 - 96BBh) */
	kulong	MCLB1;					/**< 2841_(96C0 - 96C3h) */
	kulong	MCLB2;					/**< 2841_(96C4 - 96C7h) */
	kulong	MCLB3;					/**< 2841_(96C8 - 96CBh) */
	kulong	MCLB4;					/**< 2841_(96CC - 96CFh) */
	kulong	MCLB5;					/**< 2841_(96D0 - 96D3h) */
	kulong	MCLB6;					/**< 2841_(96D4 - 96D7h) */
	kulong	MCLB7;					/**< 2841_(96D8 - 96DBh) */
	kulong	MCLB8;					/**< 2841_(96DC - 96DFh) */
	kulong	MCLB9;					/**< 2841_(96E0 - 96E3h) */
	kulong	MCLB10;					/**< 2841_(96E4 - 96E7h) */
	kulong	MCLB11;					/**< 2841_(96E8 - 96EBh) */
	kulong	MCLB12;					/**< 2841_(96EC - 96EFh) */
	kulong	MCLB13;					/**< 2841_(96F0 - 96F3h) */
	kulong	MCLB14;					/**< 2841_(96F4 - 96F7h) */
	kulong	MCLB15;					/**< 2841_(96F8 - 96FBh) */
	kulong	MCLC1;					/**< 2841_(9700 - 9703h) */
	kulong	MCLC2;					/**< 2841_(9704 - 9707h) */
	kulong	MCLC3;					/**< 2841_(9708 - 970Bh) */
	kulong	MCLC4;					/**< 2841_(970C - 970Fh) */
	kulong	MCLC5;					/**< 2841_(9710 - 9713h) */
	kulong	MCLC6;					/**< 2841_(9714 - 9717h) */
	kulong	MCLC7;					/**< 2841_(9718 - 971Bh) */
	kulong	MCLC8;					/**< 2841_(971C - 971Fh) */
	kulong	MCLC9;					/**< 2841_(9720 - 9723h) */
	kulong	MCLC10;					/**< 2841_(9724 - 9727h) */
	kulong	MCLC11;					/**< 2841_(9728 - 972Bh) */
	kulong	MCLC12;					/**< 2841_(972C - 972Fh) */
	kulong	MCLC13;					/**< 2841_(9730 - 9733h) */
	kulong	MCLC14;					/**< 2841_(9734 - 9737h) */
	kulong	MCLC15;					/**< 2841_(9738 - 973Bh) */
	kulong	MCLD1;					/**< 2841_(9740 - 9743h) */
	kulong	MCLD2;					/**< 2841_(9744 - 9747h) */
	kulong	MCLD3;					/**< 2841_(9748 - 974Bh) */
	kulong	MCLD4;					/**< 2841_(974C - 974Fh) */
	kulong	MCLD5;					/**< 2841_(9750 - 9753h) */
	kulong	MCLD6;					/**< 2841_(9754 - 9757h) */
	kulong	MCLD7;					/**< 2841_(9758 - 975Bh) */
	kulong	MCLD8;					/**< 2841_(975C - 975Fh) */
	kulong	MCLD9;					/**< 2841_(9760 - 9763h) */
	kulong	MCLD10;					/**< 2841_(9764 - 9767h) */
	kulong	MCLD11;					/**< 2841_(9768 - 976Bh) */
	kulong	MCLD12;					/**< 2841_(976C - 976Fh) */
	kulong	MCLD13;					/**< 2841_(9770 - 9773h) */
	kulong	MCLD14;					/**< 2841_(9774 - 9777h) */
	kulong	MCLD15;					/**< 2841_(9778 - 977Bh) */
	kulong	MCLE1;					/**< 2841_(9780 - 9783h) */
	kulong	MCLE2;					/**< 2841_(9784 - 9787h) */
	kulong	MCLE3;					/**< 2841_(9788 - 978Bh) */
	kulong	MCLE4;					/**< 2841_(978C - 97BFh) */
	kulong	MCLE5;					/**< 2841_(9790 - 9793h) */
	kulong	MCLE6;					/**< 2841_(9794 - 9797h) */
	kulong	MCLE7;					/**< 2841_(9798 - 979Bh) */
	kulong	MCLE8;					/**< 2841_(979C - 979Fh) */
	kulong	MCLE9;					/**< 2841_(97A0 - 97A3h) */
	kulong	MCLE10;					/**< 2841_(97A4 - 97A7h) */
	kulong	MCLE11;					/**< 2841_(97A8 - 97ABh) */
	kulong	MCLE12;					/**< 2841_(97AC - 97AFh) */
	kulong	MCLE13;					/**< 2841_(97B0 - 97B3h) */
	kulong	MCLE14;					/**< 2841_(97B4 - 97B7h) */
	kulong	MCLE15;					/**< 2841_(97B8 - 97BBh) */
	kulong	MCLF1;					/**< 2841_(97C0 - 97C3h) */
	kulong	MCLF2;					/**< 2841_(97C4 - 97C7h) */
	kulong	MCLF3;					/**< 2841_(97C8 - 97CBh) */
	kulong	MCLF4;					/**< 2841_(97CC - 97CFh) */
	kulong	MCLF5;					/**< 2841_(97D0 - 97D3h) */
	kulong	MCLF6;					/**< 2841_(97D4 - 97D7h) */
	kulong	MCLF7;					/**< 2841_(97D8 - 97DBh) */
	kulong	MCLF8;					/**< 2841_(97DC - 97DFh) */
	kulong	MCLF9;					/**< 2841_(97E0 - 97E3h) */
	kulong	MCLF10;					/**< 2841_(97E4 - 97E7h) */
	kulong	MCLF11;					/**< 2841_(97E8 - 97EBh) */
	kulong	MCLF12;					/**< 2841_(97EC - 97EFh) */
	kulong	MCLF13;					/**< 2841_(97F0 - 97F3h) */
	kulong	MCLF14;					/**< 2841_(97F4 - 97F7h) */
	kulong	MCLF15;					/**< 2841_(97F8 - 97FBh) */
	kulong	MCLG1;					/**< 2841_(9800 - 9803h) */
	kulong	MCLG2;					/**< 2841_(9804 - 9807h) */
	kulong	MCLG3;					/**< 2841_(9808 - 980Bh) */
	kulong	MCLG4;					/**< 2841_(980C - 980Fh) */
	kulong	MCLG5;					/**< 2841_(9810 - 9813h) */
	kulong	MCLG6;					/**< 2841_(9814 - 9817h) */
	kulong	MCLG7;					/**< 2841_(9818 - 981Bh) */
	kulong	MCLG8;					/**< 2841_(981C - 981Fh) */
	kulong	MCLG9;					/**< 2841_(9820 - 9823h) */
	kulong	MCLG10;					/**< 2841_(9824 - 9827h) */
	kulong	MCLG11;					/**< 2841_(9828 - 982Bh) */
	kulong	MCLG12;					/**< 2841_(982C - 982Fh) */
	kulong	MCLG13;					/**< 2841_(9830 - 9833h) */
	kulong	MCLG14;					/**< 2841_(9834 - 9837h) */
	kulong	MCLG15;					/**< 2841_(9838 - 983Bh) */
	kulong	MCLH1;					/**< 2841_(9840 - 9843h) */
	kulong	MCLH2;					/**< 2841_(9844 - 9847h) */
	kulong	MCLH3;					/**< 2841_(9848 - 984Bh) */
	kulong	MCLH4;					/**< 2841_(984C - 984Fh) */
	kulong	MCLH5;					/**< 2841_(9850 - 9853h) */
	kulong	MCLH6;					/**< 2841_(9854 - 9857h) */
	kulong	MCLH7;					/**< 2841_(9858 - 985Bh) */
	kulong	MCLH8;					/**< 2841_(985C - 985Fh) */
	kulong	MCLH9;					/**< 2841_(9860 - 9863h) */
	kulong	MCLH10;					/**< 2841_(9864 - 9867h) */
	kulong	MCLH11;					/**< 2841_(9868 - 986Bh) */
	kulong	MCLH12;					/**< 2841_(986C - 986Fh) */
	kulong	MCLH13;					/**< 2841_(9870 - 9873h) */
	kulong	MCLH14;					/**< 2841_(9874 - 9877h) */
	kulong	MCLH15;					/**< 2841_(9878 - 987Bh) */
	kulong	MCLI1;					/**< 2841_(9880 - 9883h) */
	kulong	MCLI2;					/**< 2841_(9884 - 9887h) */
	kulong	MCLI3;					/**< 2841_(9888 - 988Bh) */
	kulong	MCLI4;					/**< 2841_(988C - 98BFh) */
	kulong	MCLI5;					/**< 2841_(9890 - 9893h) */
	kulong	MCLI6;					/**< 2841_(9894 - 9897h) */
	kulong	MCLI7;					/**< 2841_(9898 - 989Bh) */
	kulong	MCLI8;					/**< 2841_(989C - 989Fh) */
	kulong	MCLI9;					/**< 2841_(98A0 - 98A3h) */
	kulong	MCLI10;					/**< 2841_(98A4 - 98A7h) */
	kulong	MCLI11;					/**< 2841_(98A8 - 98ABh) */
	kulong	MCLI12;					/**< 2841_(98AC - 98AFh) */
	kulong	MCLI13;					/**< 2841_(98B0 - 98B3h) */
	kulong	MCLI14;					/**< 2841_(98B4 - 98B7h) */
	kulong	MCLI15;					/**< 2841_(98B8 - 98BBh) */
	kulong	MCLJ1;					/**< 2841_(98C0 - 98C3h) */
	kulong	MCLJ2;					/**< 2841_(98C4 - 98C7h) */
	kulong	MCLJ3;					/**< 2841_(98C8 - 98CBh) */
	kulong	MCLJ4;					/**< 2841_(98CC - 98CFh) */
	kulong	MCLJ5;					/**< 2841_(98D0 - 98D3h) */
	kulong	MCLJ6;					/**< 2841_(98D4 - 98D7h) */
	kulong	MCLJ7;					/**< 2841_(98D8 - 98DBh) */
	kulong	MCLJ8;					/**< 2841_(98DC - 98DFh) */
	kulong	MCLJ9;					/**< 2841_(98E0 - 98E3h) */
	kulong	MCLJ10;					/**< 2841_(98E4 - 98E7h) */
	kulong	MCLJ11;					/**< 2841_(98E8 - 98EBh) */
	kulong	MCLJ12;					/**< 2841_(98EC - 98EFh) */
	kulong	MCLJ13;					/**< 2841_(98F0 - 98F3h) */
	kulong	MCLJ14;					/**< 2841_(98F4 - 98F7h) */
	kulong	MCLJ15;					/**< 2841_(98F8 - 98FBh) */
	kulong	MCLK1;					/**< 2841_(9900 - 9903h) */
	kulong	MCLK2;					/**< 2841_(9904 - 9907h) */
	kulong	MCLK3;					/**< 2841_(9908 - 990Bh) */
	kulong	MCLK4;					/**< 2841_(990C - 990Fh) */
	kulong	MCLK5;					/**< 2841_(9910 - 9913h) */
	kulong	MCLK6;					/**< 2841_(9914 - 9917h) */
	kulong	MCLK7;					/**< 2841_(9918 - 991Bh) */
	kulong	MCLK8;					/**< 2841_(991C - 991Fh) */
	kulong	MCLK9;					/**< 2841_(9920 - 9923h) */
	kulong	MCLK10;					/**< 2841_(9924 - 9927h) */
	kulong	MCLK11;					/**< 2841_(9928 - 992Bh) */
	kulong	MCLK12;					/**< 2841_(992C - 992Fh) */
	kulong	MCLK13;					/**< 2841_(9930 - 9933h) */
	kulong	MCLK14;					/**< 2841_(9934 - 9937h) */
	kulong	MCLK15;					/**< 2841_(9938 - 993Bh) */
	kulong	MCLL1;					/**< 2841_(9940 - 9943h) */
	kulong	MCLL2;					/**< 2841_(9944 - 9947h) */
	kulong	MCLL3;					/**< 2841_(9948 - 994Bh) */
	kulong	MCLL4;					/**< 2841_(994C - 994Fh) */
	kulong	MCLL5;					/**< 2841_(9950 - 9953h) */
	kulong	MCLL6;					/**< 2841_(9954 - 9957h) */
	kulong	MCLL7;					/**< 2841_(9958 - 995Bh) */
	kulong	MCLL8;					/**< 2841_(995C - 995Fh) */
	kulong	MCLL9;					/**< 2841_(9960 - 9963h) */
	kulong	MCLL10;					/**< 2841_(9964 - 9967h) */
	kulong	MCLL11;					/**< 2841_(9968 - 996Bh) */
	kulong	MCLL12;					/**< 2841_(996C - 996Fh) */
	kulong	MCLL13;					/**< 2841_(9970 - 9973h) */
	kulong	MCLL14;					/**< 2841_(9974 - 9977h) */
	kulong	MCLL15;					/**< 2841_(9978 - 997Bh) */
	kulong	MCYCBALP;				/**< 2841_(9980 - 9983h) */
	kulong	MCYCBGA1;				/**< 2841_(9988 - 998Bh) */
	kulong	MCYCBGA2;				/**< 2841_(998C - 998Fh) */
	kulong	MCYCBBD1;				/**< 2841_(9990 - 9993h) */
	kulong	MCYCBBD2;				/**< 2841_(9994 - 9997h) */
	kulong	MCBABALP;				/**< 2841_(9998 - 999Bh) */
	kulong	MCBABOF1;				/**< 2841_(99A0 - 99A3h) */
	kulong	MCBABOF2;				/**< 2841_(99A4 - 99A7h) */
	kulong	MCBABGA1;				/**< 2841_(99A8 - 99ABh) */
	kulong	MCBABGA2;				/**< 2841_(99AC - 99AFh) */
	kulong	MCBABBD1;				/**< 2841_(99B0 - 99B3h) */
	kulong	MCBABBD2;				/**< 2841_(99B4 - 99B7h) */
} CtrlRdmaMcycAddr;

/** RGB Offset before TC control register address info (for RDMA)
*/
typedef struct {
	kulong	TCOF1;					/**< 2841_(A000 - A003h) */
	kulong	TCOF2;					/**< 2841_(A004 - A007h) */
} RdmaBtcTcofAddr;

/** Luminance Evaluation TC control register address info (for RDMA)
*/
typedef struct {
	kulong	TCTCTL;					/**< 2841_(A008 - A00Bh) */
	kulong	TCTSTA;					/**< 2841_(A00C - A00Fh) */
	kulong	TCTB;					/**< 2841_(A010 - A013h) */
} RdmaBtcTctAddr;

/** Histogram before TC control register address info (for RDMA)
*/
typedef struct {
	kulong	TCHSCTL;				/**< 2841_(A014 - A017h) */
	kulong	TCHSSTA;				/**< 2841_(A018 - A01Bh) */
	kulong	TCHSSIZ;				/**< 2841_(A01C - A01Fh) */
} RdmaBtcTchsAddr;

/** Tone control register address info (for RDMA)
*/
typedef struct {
	kulong	TCCTL;					/**< 2841_(A040 - A043h) */
	kulong	TCYC;					/**< 2841_(A044 - A047h) */
	kulong	TCEP1;					/**< 2841_(A048 - A04Bh) */
	kulong	TCEP2;					/**< 2841_(A04C - A04Fh) */
	kulong	TCCLPR;					/**< 2841_(A050 - A053h) */
	kulong	TCCLPG;					/**< 2841_(A054 - A057h) */
	kulong	TCCLPB;					/**< 2841_(A058 - A05Bh) */
} CtrlRdmaToneAddr;

/** Gamma control register address info (for RDMA)
*/
typedef struct {
	kulong	GMCTL;					/**< 2841_(A060 - A063h) */
} CtrlRdmaGammaAddr;

/** CC1 matrix control register address info (for RDMA)
*/
typedef struct {
	kulong	CC1CTL;					/**< 2841_(A080 - A083h) */
	kulong	CC1K1;					/**< 2841_(A0A0 - A0A3h) */
	kulong	CC1K2;					/**< 2841_(A0A4 - A0A7h) */
	kulong	CC1K3;					/**< 2841_(A0A8 - A0ABh) */
	kulong	CC1K4;					/**< 2841_(A0AC - A0AFh) */
	kulong	CC1K5;					/**< 2841_(A0B0 - A0B3h) */
	kulong	CC1CLPR;				/**< 2841_(A0C0 - A0C3h) */
	kulong	CC1CLPG;				/**< 2841_(A0C4 - A0C7h) */
	kulong	CC1CLPB;				/**< 2841_(A0C8 - A0CBh) */
} CtrlRdmaCc1Addr;

/** CC1 matrix coefficient control register address info (for RDMA)
*/
typedef struct {
	kulong	CC1K1;					/**< 2841_(A0A0 - A0A3h) */
	kulong	CC1K2;					/**< 2841_(A0A4 - A0A7h) */
	kulong	CC1K3;					/**< 2841_(A0A8 - A0ABh) */
	kulong	CC1K4;					/**< 2841_(A0AC - A0AFh) */
	kulong	CC1K5;					/**< 2841_(A0B0 - A0B3h) */
} RdmaCc1CoefAddr;

/** Yc convert control register address info (for RDMA)
*/
typedef struct {
	kulong	YC1;					/**< 2841_(A100 - A103h) */
	kulong	YC2;					/**< 2841_(A104 - A107h) */
	kulong	YC3;					/**< 2841_(A108 - A10Bh) */
	kulong	YC4;					/**< 2841_(A10C - A110h) */
	kulong	YC5;					/**< 2841_(A110 - A113h) */
	kulong	YBLEND;					/**< 2841_(A120 - A123h) */
} CtrlRdmaYccAddr;

/** YNR control register address info (for RDMA)
*/
typedef struct {
	kulong	NRCTL;					/**< 2841_(A140 - A143h) */
	kulong	NROF1;					/**< 2841_(A148 - A14Bh) */
	kulong	NROF2;					/**< 2841_(A14C - A14Fh) */
	kulong	NRGA1;					/**< 2841_(A150 - A153h) */
	kulong	NRGA2;					/**< 2841_(A154 - A157h) */
	kulong	NRBD1;					/**< 2841_(A158 - A15Bh) */
	kulong	NRBD2;					/**< 2841_(A15C - A15Fh) */
} CtrlRdmaYnrAddr;

/** Edge enhancement noise reduction control register address info (for RDMA)
*/
typedef struct {
	kulong	EGSMCTL;				/**< 2841_(A180 - A183h) */
	kulong	EGSMTT;					/**< 2841_(A184 - A187h) */
} CtrlRdmaEenrAddr;

/** High frequency edge enhancement control register address info (for RDMA)
*/
typedef struct {
	kulong	EGHWCTL;				/**< 2841_(A200 - A203h) */
	kulong	EGHWHPFK1;				/**< 2841_(A208 - A20Bh) */
	kulong	EGHWHPFK2;				/**< 2841_(A20C - A20Fh) */
	kulong	EGHWCORPOF1;			/**< 2841_(A210 - A213h) */
	kulong	EGHWCORPOF2;			/**< 2841_(A214 - A217h) */
	kulong	EGHWCORPGA;				/**< 2841_(A218 - A21Bh) */
	kulong	EGHWCORPBD1;			/**< 2841_(A220 - A223h) */
	kulong	EGHWCORPBD2;			/**< 2841_(A224 - A227h) */
	kulong	EGHWCORMOF1;			/**< 2841_(A228 - A22Bh) */
	kulong	EGHWCORMOF2;			/**< 2841_(A22C - A22Fh) */
	kulong	EGHWCORMGA;				/**< 2841_(A230 - A233h) */
	kulong	EGHWCORMBD1;			/**< 2841_(A238 - A23Bh) */
	kulong	EGHWCORMBD2;			/**< 2841_(A23C - A23Fh) */
	kulong	EGHWSCLSUP;				/**< 2841_(A240 - A243h) */
	kulong	EGHWCLPPOF1;			/**< 2841_(A248 - A24Bh) */
	kulong	EGHWCLPPOF2;			/**< 2841_(A24C - A24Fh) */
	kulong	EGHWCLPPGA;				/**< 2841_(A250 - A253h) */
	kulong	EGHWCLPPBD;				/**< 2841_(A254 - A257h) */
	kulong	EGHWCLPMOF1;			/**< 2841_(A258 - A25Bh) */
	kulong	EGHWCLPMOF2;			/**< 2841_(A25C - A25Fh) */
	kulong	EGHWCLPMGA;				/**< 2841_(A260 - A263h) */
	kulong	EGHWCLPMBD;				/**< 2841_(A264 - A267h) */
} CtrlRdmaEghwAddr;

/** Medium frequency edge enhancement control register address info (for RDMA)
*/
typedef struct {
	kulong	EGMWCTL;				/**< 2841_(A280 - A283h) */
	kulong	EGMWHPFK1;				/**< 2841_(A288 - A28Bh) */
	kulong	EGMWHPFK2;				/**< 2841_(A28C - A28Fh) */
	kulong	EGMWCORPOF1;			/**< 2841_(A290 - A293h) */
	kulong	EGMWCORPOF2;			/**< 2841_(A294 - A297h) */
	kulong	EGMWCORPGA;				/**< 2841_(A298 - A29Bh) */
	kulong	EGMWCORPBD1;			/**< 2841_(A2A0 - A2A3h) */
	kulong	EGMWCORPBD2;			/**< 2841_(A2A4 - A2A7h) */
	kulong	EGMWCORMOF1;			/**< 2841_(A2A8 - A2ABh) */
	kulong	EGMWCORMOF2;			/**< 2841_(A2AC - A2AFh) */
	kulong	EGMWCORMGA;				/**< 2841_(A2B0 - A2B3h) */
	kulong	EGMWCORMBD1;			/**< 2841_(A2B8 - A2BBh) */
	kulong	EGMWCORMBD2;			/**< 2841_(A2BC - A2BFh) */
	kulong	EGMWSCLSUP;				/**< 2841_(A2C0 - A2C3h) */
	kulong	EGMWCLPPOF1;			/**< 2841_(A2C8 - A2CBh) */
	kulong	EGMWCLPPOF2;			/**< 2841_(A2CC - A2CFh) */
	kulong	EGMWCLPPGA;				/**< 2841_(A2D0 - A2D3h) */
	kulong	EGMWCLPPBD;				/**< 2841_(A2D4 - A2D7h) */
	kulong	EGMWCLPMOF1;			/**< 2841_(A2D8 - A2DBh) */
	kulong	EGMWCLPMOF2;			/**< 2841_(A2DC - A2DFh) */
	kulong	EGMWCLPMGA;				/**< 2841_(A2E0 - A2E3h) */
	kulong	EGMWCLPMBD;				/**< 2841_(A2E4 - A2E7h) */
} CtrlRdmaEgmwAddr;

/** Low frequency edge enhancement control register address info (for RDMA)
*/
typedef struct {
	kulong	EGLWCTL;				/**< 2841_(A300 - A303h) */
	kulong	EGLWHPFK1;				/**< 2841_(A310 - A313h) */
	kulong	EGLWHPFK2;				/**< 2841_(A314 - A317h) */
	kulong	EGLWHPFK3;				/**< 2841_(A318 - A31Bh) */
	kulong	EGLWCORPOF1;			/**< 2841_(A320 - A323h) */
	kulong	EGLWCORPOF2;			/**< 2841_(A324 - A327h) */
	kulong	EGLWCORPGA;				/**< 2841_(A328 - A32Bh) */
	kulong	EGLWCORPBD1;			/**< 2841_(A330 - A333h) */
	kulong	EGLWCORPBD2;			/**< 2841_(A334 - A337h) */
	kulong	EGLWCORMOF1;			/**< 2841_(A338 - A33Bh) */
	kulong	EGLWCORMOF2;			/**< 2841_(A33C - A33Fh) */
	kulong	EGLWCORMGA;				/**< 2841_(A340 - A343h) */
	kulong	EGLWCORMBD1;			/**< 2841_(A348 - A34Bh) */
	kulong	EGLWCORMBD2;			/**< 2841_(A34C - A34Fh) */
	kulong	EGLWSCLSUP;				/**< 2841_(A350 - A353h) */
	kulong	EGLWCLPPOF1;			/**< 2841_(A358 - A35Bh) */
	kulong	EGLWCLPPOF2;			/**< 2841_(A35C - A35Fh) */
	kulong	EGLWCLPPGA;				/**< 2841_(A360 - A363h) */
	kulong	EGLWCLPPBD;				/**< 2841_(A364 - A367h) */
	kulong	EGLWCLPMOF1;			/**< 2841_(A368 - A36Bh) */
	kulong	EGLWCLPMOF2;			/**< 2841_(A36C - A36Fh) */
	kulong	EGLWCLPMGA;				/**< 2841_(A370 - A373h) */
	kulong	EGLWCLPMBD;				/**< 2841_(A374 - A377h) */
} CtrlRdmaEglwAddr;

/** Edge dot noise correction control register address info (for RDMA)
*/
typedef struct {
	kulong	EGDTCTL;				/**< 2841_(A380 - A383h) */
	kulong	EGDTHWTH;				/**< 2841_(A384 - A387h) */
	kulong	EGDTHWK;				/**< 2841_(A388 - A38Bh) */
	kulong	EGDTMWTH;				/**< 2841_(A38C - A38Fh) */
	kulong	EGDTMWK;				/**< 2841_(A390 - A393h) */
} CtrlRdmaEgdtAddr;

/** Edge emphasis blend control register address info (for RDMA)
*/
typedef struct {
	kulong	EGCMPCTL;				/**< 2841_(A3C0 - A3C3h) */
	kulong	EGCMPBD1;				/**< 2841_(A3C8 - A3CBh) */
	kulong	EGCMPBD2;				/**< 2841_(A3CC - A3CFh) */
	kulong	EGCMPALPOF;				/**< 2841_(A3D0 - A3D3h) */
	kulong	EGCMPALPGA1;			/**< 2841_(A3D8 - A3DBh) */
	kulong	EGCMPALPGA2;			/**< 2841_(A3DC - A3DFh) */
	kulong	EGCMPBTAOF;				/**< 2841_(A3E0 - A3E3h) */
	kulong	EGCMPBTAGA1;			/**< 2841_(A3E8 - A3EBh) */
	kulong	EGCMPBTAGA2;			/**< 2841_(A3EC - A3EFh) */
	kulong	EGCMPCLP;				/**< 2841_(A3F0 - A3F3h) */
} CtrlRdmaEgcmpAddr;

/** Chroma referenced edge and texture adjustment control register address info (for RDMA)
*/
typedef struct {
	kulong	CRVAF;					/**< 2841_(A400 - A403h) */
	kulong	CRVBF;					/**< 2841_(A404 - A407h) */
} CtrlRdmaCrvAddr;

/** Chroma referenced edge adjustment control register address info (for RDMA)
*/
typedef struct {
	kulong	EGCRVCTL;				/**< 2841_(A440 - A443h) */
	kulong	EGCRVASCLOF;			/**< 2841_(A444 - A447h) */
	kulong	EGCRVASCLGA;			/**< 2841_(A448 - A44Bh) */
	kulong	EGCRVASCLBD;			/**< 2841_(A44C - A44Fh) */
	kulong	EGCRVASCLCP;			/**< 2841_(A450 - A453h) */
	kulong	EGYASCLGA;				/**< 2841_(A454 - A457h) */
	kulong	EGYASCLBD;				/**< 2841_(A458 - A45Bh) */
	kulong	EGYASCLCLP;				/**< 2841_(A45C - A45Fh) */
	kulong	EGCRVBSCLOF;			/**< 2841_(A460 - A463h) */
	kulong	EGCRVBSCLGA;			/**< 2841_(A464 - A467h) */
	kulong	EGCRVBSCLBD;			/**< 2841_(A468 - A46Bh) */
	kulong	EGCRVBSCLCP;			/**< 2841_(A46C - A46Fh) */
	kulong	EGYBSCLGA;				/**< 2841_(A470 - A473h) */
	kulong	EGYBSCLBD;				/**< 2841_(A474 - A477h) */
	kulong	EGYBSCLCLP;				/**< 2841_(A478 - A47Bh) */
	kulong	EGCRVCLP;				/**< 2841_(A47C - A47Fh) */
} CtrlRdmaEgcrvAddr;

/** Chroma referenced luminance blend control register address info (for RDMA)
*/
typedef struct {
	kulong	YBCRVCTL;				/**< 2841_(A480 - A483h) */
	kulong	YBCRVAALPOF;			/**< 2841_(A484 - A487h) */
	kulong	YBCRVAALPGA;			/**< 2841_(A488 - A48Bh) */
	kulong	YBCRVAALPBD;			/**< 2841_(A48C - A48Fh) */
	kulong	YBCRVAALPCP;			/**< 2841_(A490 - A493h) */
	kulong	YBYAALPGA;				/**< 2841_(A494 - A497h) */
	kulong	YBYAALPBD;				/**< 2841_(A498 - A49Bh) */
	kulong	YBYAALPCLP;				/**< 2841_(A49C - A49Fh) */
	kulong	YBCRVBALPOF;			/**< 2841_(A4A0 - A4A3h) */
	kulong	YBCRVBALPGA;			/**< 2841_(A4A4 - A4A7h) */
	kulong	YBCRVBALPBD;			/**< 2841_(A4A8 - A4ABh) */
	kulong	YBCRVBALPCP;			/**< 2841_(A4AC - A4AFh) */
	kulong	YBYBALPGA;				/**< 2841_(A4B0 - A4B3h) */
	kulong	YBYBALPBD;				/**< 2841_(A4B4 - A4B7h) */
	kulong	YBYBALPCLP;				/**< 2841_(A4B8 - A4BBh) */
} CtrlRdmaYbcrvAddr;

/** Color Noise Reduction(LPF) control register address info (for RDMA)
*/
typedef struct {
	kulong	CLPFCTL;				/**< 2841_(A500 - A503h) */
	kulong	CLPFK1;					/**< 2841_(A520 - A523h) */
	kulong	CLPFK2;					/**< 2841_(A524 - A527h) */
	kulong	CLPFK3;					/**< 2841_(A528 - A52Bh) */
	kulong	CLPFK4;					/**< 2841_(A52C - A52Fh) */
	kulong	CLPFK5;					/**< 2841_(A530 - A533h) */
	kulong	CLPFOF;					/**< 2841_(A540 - A543h) */
	kulong	CLPFGA1;				/**< 2841_(A548 - A54Bh) */
	kulong	CLPFGA2;				/**< 2841_(A54C - A54Fh) */
	kulong	CLPFBD1;				/**< 2841_(A550 - A553h) */
	kulong	CLPFBD2;				/**< 2841_(A554 - A557h) */
} CtrlRdmaClpfAddr;

/** Chroma suppress control register address info (for RDMA)
*/
typedef struct {
	kulong	CSYCTL;					/**< 2841_(A580 - A583h) */
	kulong	CSYOF1;					/**< 2841_(A588 - A58Bh) */
	kulong	CSYOF2;					/**< 2841_(A58C - A58Fh) */
	kulong	CSYGA1;					/**< 2841_(A590 - A593h) */
	kulong	CSYGA2;					/**< 2841_(A594 - A597h) */
	kulong	CSYBD1;					/**< 2841_(A598 - A59Bh) */
	kulong	CSYBD2;					/**< 2841_(A59C - A59Fh) */
	kulong	YCRVFX;					/**< 2841_(A5A0 - A5A3h) */
	kulong	CFIX;					/**< 2841_(A5A4 - A5A7h) */
	kulong	YCOF1;					/**< 2841_(A5A8 - A5ABh) */
	kulong	YCOF2;					/**< 2841_(A5AC - A5AFh) */
} CtrlRdmaCspAddr;

/** Tone control Table register address info (for RDMA)
*/
typedef struct {
	kulong	TC[512];				/**< 294A_(0000 - 07FFh) */
} RdmaToneTblAddr;

/** Gamma Table(Diff) register address info (for RDMA)
*/
typedef struct {
	kulong	GMDF[512];				/**< 294A_(8000 - 87FFh) */
									/**< 294A_(8800 - 8FFFh) */
									/**< 294A_(9000 - 97FFh) */
									/**< 294A_(9800 - 9FFFh) */
									/**< 294A_(A000 - A7FFh) */
} RdmaGmdfTblAddr;

/** Gamma Table(Full) register address info (for RDMA)
*/
typedef struct {
	kulong	GMFL[128];				/**< 294A_(A800 - A9FFh) */
									/**< 294A_(AA00 - ABFFh) */
									/**< 294A_(AC00 - ADFFh) */
									/**< 294A_(AE00 - AFFFh) */
									/**< 294A_(B000 - B1FFh) */
} RdmaGmflTblAddr;

/** (High/Medium/Low) Edge emphasis scaling Table register address info (for RDMA)
*/
typedef struct {
	kulong	EGWSCL[128];			/**< 294A_(C000 - C1FFh) */
									/**< 294A_(C400 - C5FFh) */
									/**< 294A_(C800 - C9FFh) */
} RdmaEgwsclTblAddr;

/** (High/Medium/Low) Edge emphasis stepping Table register address info (for RDMA)
*/
typedef struct {
	kulong	EGWTON[128];			/**< 294A_(C200 - C3FFh) */
									/**< 294A_(C600 - C7FFh) */
									/**< 294A_(CA00 - CBFFh) */
} RdmaEgwtonTblAddr;

/** Map Scale Table register address info (for RDMA)
*/
typedef struct {
	kulong	EGMPSCL[111];			/**< 294A_(CC00 - CDBBh) */
} RdmaEgmpsclTblAddr;

/** Post-resize edge enhancement0 control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_ee0ctl		EE0CTL;			/**< 2841_(C400 - C403h) */
	union	io_r2y_ee0hpfk		EE0HPFK;		/**< 2841_(C408 - C40Fh) */
	union	io_r2y_ee0nrlv		EE0NRLV;		/**< 2841_(C410 - C413h) */
	union	io_r2y_ee0corpof	EE0CORPOF;		/**< 2841_(C414 - C417h) */
	union	io_r2y_ee0corpga	EE0CORPGA;		/**< 2841_(C418 - C41Bh) */
	union	io_r2y_ee0corpbd	EE0CORPBD;		/**< 2841_(C41C - C41Fh) */
	union	io_r2y_ee0cormof	EE0CORMOF;		/**< 2841_(C420 - C423h) */
	union	io_r2y_ee0cormga	EE0CORMGA;		/**< 2841_(C424 - C427h) */
	union	io_r2y_ee0cormbd	EE0CORMBD;		/**< 2841_(C428 - C42Bh) */
	union	io_r2y_ee0sclsup	EE0SCLSUP;		/**< 2841_(C42C - C42Fh) */
	union	io_r2y_ee0sclpof	EE0SCLPOF;		/**< 2841_(C430 - C43Bh) */
	union	io_r2y_ee0sclpga	EE0SCLPGA;		/**< 2841_(C440 - C453h) */
	union	io_r2y_ee0sclpbd	EE0SCLPBD;		/**< 2841_(C460 - C46Bh) */
	union	io_r2y_ee0sclmof	EE0SCLMOF;		/**< 2841_(C470 - C47Bh) */
	union	io_r2y_ee0sclmga	EE0SCLMGA;		/**< 2841_(C480 - C493h) */
	union	io_r2y_ee0sclmbd	EE0SCLMBD;		/**< 2841_(C4A0 - C4ABh) */
	union	io_r2y_ee0tonpof	EE0TONPOF;		/**< 2841_(C4B0 - C4B7h) */
	union	io_r2y_ee0tonpga	EE0TONPGA;		/**< 2841_(C4C0 - C4CBh) */
	union	io_r2y_ee0tonpbd	EE0TONPBD;		/**< 2841_(C4D0 - C4D3h) */
	union	io_r2y_ee0tonmof	EE0TONMOF;		/**< 2841_(C4D8 - C4DFh) */
	union	io_r2y_ee0tonmga	EE0TONMGA;		/**< 2841_(C4E0 - C4EBh) */
	union	io_r2y_ee0tonmbd	EE0TONMBD;		/**< 2841_(C4F0 - C4F3h) */
	union	io_r2y_ee0clppof	EE0CLPPOF;		/**< 2841_(C4F4 - C4F7h) */
	union	io_r2y_ee0clppga	EE0CLPPGA;		/**< 2841_(C4F8 - C4FBh) */
	union	io_r2y_ee0clppbd	EE0CLPPBD;		/**< 2841_(C4FC - C4FFh) */
	union	io_r2y_ee0clpmof	EE0CLPMOF;		/**< 2841_(C500 - C503h) */
	union	io_r2y_ee0clpmga	EE0CLPMGA;		/**< 2841_(C504 - C507h) */
	union	io_r2y_ee0clpmbd	EE0CLPMBD;		/**< 2841_(C508 - C50Bh) */
} CtrlRdmaEe0Val;

/** Post-resize edge enhancement1 control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_ee1ctl		EE1CTL;			/**< 2841_(C600 - C603h) */
	union	io_r2y_ee1hpfk		EE1HPFK;		/**< 2841_(C608 - C60Fh) */
	union	io_r2y_ee1nrlv		EE1NRLV;		/**< 2841_(C610 - C613h) */
	union	io_r2y_ee1corpof	EE1CORPOF;		/**< 2841_(C618 - C61Fh) */
	union	io_r2y_ee1corpga	EE1CORPGA;		/**< 2841_(C620 - C623h) */
	union	io_r2y_ee1corpbd	EE1CORPBD;		/**< 2841_(C628 - C62Fh) */
	union	io_r2y_ee1cormof	EE1CORMOF;		/**< 2841_(C630 - C637h) */
	union	io_r2y_ee1cormga	EE1CORMGA;		/**< 2841_(C638 - C63Bh) */
	union	io_r2y_ee1cormbd	EE1CORMBD;		/**< 2841_(C640 - C647h) */
	union	io_r2y_ee1sclsup	EE1SCLSUP;		/**< 2841_(C648 - C64Bh) */
	union	io_r2y_ee1sclpof	EE1SCLPOF;		/**< 2841_(C650 - C65Bh) */
	union	io_r2y_ee1sclpga	EE1SCLPGA;		/**< 2841_(C660 - C673h) */
	union	io_r2y_ee1sclpbd	EE1SCLPBD;		/**< 2841_(C680 - C693h) */
	union	io_r2y_ee1sclmof	EE1SCLMOF;		/**< 2841_(C6A0 - C6ABh) */
	union	io_r2y_ee1sclmga	EE1SCLMGA;		/**< 2841_(C6C0 - C6D3h) */
	union	io_r2y_ee1sclmbd	EE1SCLMBD;		/**< 2841_(C6E0 - C6F3h) */
	union	io_r2y_ee1tonpof	EE1TONPOF;		/**< 2841_(C700 - C70Bh) */
	union	io_r2y_ee1tonpga	EE1TONPGA;		/**< 2841_(C710 - C71Bh) */
	union	io_r2y_ee1tonpbd	EE1TONPBD;		/**< 2841_(C720 - C727h) */
	union	io_r2y_ee1tonmof	EE1TONMOF;		/**< 2841_(C730 - C73Bh) */
	union	io_r2y_ee1tonmga	EE1TONMGA;		/**< 2841_(C740 - C74Bh) */
	union	io_r2y_ee1tonmbd	EE1TONMBD;		/**< 2841_(C750 - C757h) */
	union	io_r2y_ee1clppof	EE1CLPPOF;		/**< 2841_(C758 - C75Fh) */
	union	io_r2y_ee1clppga	EE1CLPPGA;		/**< 2841_(C760 - C763h) */
	union	io_r2y_ee1clppbd	EE1CLPPBD;		/**< 2841_(C764 - C767h) */
	union	io_r2y_ee1clpmof	EE1CLPMOF;		/**< 2841_(C768 - C76Fh) */
	union	io_r2y_ee1clpmga	EE1CLPMGA;		/**< 2841_(C770 - C773h) */
	union	io_r2y_ee1clpmbd	EE1CLPMBD;		/**< 2841_(C774 - C777h) */
} CtrlRdmaEe1Val;

/** Deknee Table(R/G/B) register value info (for RDMA)
*/
typedef union {
	union	io_r2y_sram_dkntbl	DKNTBLR;	/**< 294A_(E000 - E1FFh) */
	union	io_r2y_sram_dkntbl	DKNTBLG;	/**< 294A_(E200 - E3FFh) */
	union	io_r2y_sram_dkntbl	DKNTBLB;	/**< 294A_(E400 - E5FFh) */
} RdmaDekneeTblVal;

/** Offset control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_ofst			OFST;			/**< 2841_(8020 - 8027h) */
} CtrlRdmaOfstVal;

/** WB clip control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_wblv			WBLV;			/**< 2841_(8030 - 8037h) */
} RdmaWbClipVal;

/** CC0 matrix control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_cc0ctl		CC0CTL;			/**< 2841_(8080 - 8083h) */
	union	io_r2y_cc0k			CC0K;			/**< 2841_(80A0 - 80B3h) */
	union	io_r2y_cc0ybof		CC0YBOF;		/**< 2841_(80C0 - 80C7h) */
	union	io_r2y_cc0ybga		CC0YBGA;		/**< 2841_(80C8 - 80CFh) */
	union	io_r2y_cc0ybbd		CC0YBBD;		/**< 2841_(80D0 - 80D3h) */
	union	io_r2y_ccyc			CCYC;			/**< 2841_(80D4 - 80D7h) */
} CtrlRdmaCc0Val;

/** CC0 matrix coefficient control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_cc0k			CC0K;			/**< 2841_(80A0 - 80B3h) */
} RdmaCc0CoefVal;

/** Multi Axis control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_mcyc			MCYC;			/**< 2841_(9000 - 9013h) */
	union	io_r2y_mcb1ab		MCB1AB;			/**< 2841_(9020 - 9023h) */
	union	io_r2y_mcb1cd		MCB1CD;			/**< 2841_(9024 - 9027h) */
	union	io_r2y_mcb2ab		MCB2AB;			/**< 2841_(9028 - 902Bh) */
	union	io_r2y_mcb2cd		MCB2CD;			/**< 2841_(902C - 902Fh) */
	union	io_r2y_mcb3ab		MCB3AB;			/**< 2841_(9030 - 9033h) */
	union	io_r2y_mcb3cd		MCB3CD;			/**< 2841_(9034 - 9037h) */
	union	io_r2y_mcb4ab		MCB4AB;			/**< 2841_(9038 - 903Bh) */
	union	io_r2y_mcb4cd		MCB4CD;			/**< 2841_(903C - 903Fh) */
	union	io_r2y_mcid1		MCID1;			/**< 2841_(9040 - 9043h) */
	union	io_r2y_mcid2		MCID2;			/**< 2841_(9044 - 9047h) */
	union	io_r2y_mcid3		MCID3;			/**< 2841_(9048 - 904Bh) */
	union	io_r2y_mcid4		MCID4;			/**< 2841_(904C - 904Fh) */
	struct io_r2y_mck			MCKA;			/**< 2841_(9080 - 90E3h) */
	struct io_r2y_mck			MCKB;			/**< 2841_(9100 - 9163h) */
	struct io_r2y_mck			MCKC;			/**< 2841_(9180 - 91E3h) */
	struct io_r2y_mck			MCKD;			/**< 2841_(9200 - 9263h) */
	struct io_r2y_mck			MCKE;			/**< 2841_(9280 - 92E3h) */
	struct io_r2y_mck			MCKF;			/**< 2841_(9300 - 9363h) */
	struct io_r2y_mck			MCKG;			/**< 2841_(9380 - 93E3h) */
	struct io_r2y_mck			MCKH;			/**< 2841_(9400 - 9463h) */
	struct io_r2y_mck			MCKI;			/**< 2841_(9480 - 94E3h) */
	struct io_r2y_mck			MCKJ;			/**< 2841_(9500 - 9563h) */
	struct io_r2y_mck			MCKK;			/**< 2841_(9580 - 95E3h) */
	struct io_r2y_mck			MCKL;			/**< 2841_(9600 - 9663h) */
	struct io_r2y_mcl			MCLA;			/**< 2841_(9680 - 96BBh) */
	struct io_r2y_mcl			MCLB;			/**< 2841_(96C0 - 96FBh) */
	struct io_r2y_mcl			MCLC;			/**< 2841_(9700 - 973Bh) */
	struct io_r2y_mcl			MCLD;			/**< 2841_(9740 - 977Bh) */
	struct io_r2y_mcl			MCLE;			/**< 2841_(9780 - 97BBh) */
	struct io_r2y_mcl			MCLF;			/**< 2841_(97C0 - 97FBh) */
	struct io_r2y_mcl			MCLG;			/**< 2841_(9800 - 983Bh) */
	struct io_r2y_mcl			MCLH;			/**< 2841_(9840 - 987Bh) */
	struct io_r2y_mcl			MCLI;			/**< 2841_(9880 - 98BBh) */
	struct io_r2y_mcl			MCLJ;			/**< 2841_(98C0 - 98FBh) */
	struct io_r2y_mcl			MCLK;			/**< 2841_(9900 - 993Bh) */
	struct io_r2y_mcl			MCLL;			/**< 2841_(9940 - 997Bh) */
	union	io_r2y_mcycbalp		MCYCBALP;		/**< 2841_(9980 - 9983h) */
	union	io_r2y_mcycbga		MCYCBGA;		/**< 2841_(9988 - 998Fh) */
	union	io_r2y_mcycbbd		MCYCBBD;		/**< 2841_(9990 - 9997h) */
	union	io_r2y_mcbabalp		MCBABALP;		/**< 2841_(9998 - 999Bh) */
	union	io_r2y_mcbabof		MCBABOF;		/**< 2841_(99A0 - 99A7h) */
	union	io_r2y_mcbabga		MCBABGA;		/**< 2841_(99A8 - 99AFh) */
	union	io_r2y_mcbabbd		MCBABBD;		/**< 2841_(99B0 - 99B7h) */
} CtrlRdmaMcycVal;

/** RGB Offset before TC control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_tcof			TCOF;			/**< 2841_(A000 - A007h) */
} RdmaBtcTcofVal;

/** Luminance Evaluation before TC control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_tctctl		TCTCTL;			/**< 2841_(A008 - A00Bh) */
	union	io_r2y_tctsta		TCTSTA;			/**< 2841_(A00C - A00Fh) */
	union	io_r2y_tctb			TCTB;			/**< 2841_(A010 - A013h) */
} RdmaBtcTctVal;

/** Histogram before TC control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_tchsctl		TCHSCTL;		/**< 2841_(A014 - A017h) */
	union	io_r2y_tchssta		TCHSSTA;		/**< 2841_(A018 - A01Bh) */
	union	io_r2y_tchssiz		TCHSSIZ;		/**< 2841_(A01C - A01Fh) */
	union	io_r2y_tchov		TCHOV;			/**< 2841_(A020 - A023h) */
} RdmaBtcTchsVal;

/** Tone control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_tcctl		TCCTL;			/**< 2841_(A040 - A043h) */
	union	io_r2y_tcyc			TCYC;			/**< 2841_(A044 - A047h) */
	union	io_r2y_tcep			TCEP;			/**< 2841_(A048 - A04Fh) */
	union	io_r2y_tcclpr		TCCLPR;			/**< 2841_(A050 - A053h) */
	union	io_r2y_tcclpg		TCCLPG;			/**< 2841_(A054 - A057h) */
	union	io_r2y_tcclpb		TCCLPB;			/**< 2841_(A058 - A05Bh) */
} CtrlRdmaToneVal;

/** Gamma control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_gmctl		GMCTL;			/**< 2841_(A060 - A063h) */
} CtrlRdmaGammaVal;

/** CC1 matrix control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_cc1ctl		CC1CTL;			/**< 2841_(A080 - A083h) */
	union	io_r2y_cc1k			CC1K;			/**< 2841_(A0A0 - A0B3h) */
	union	io_r2y_cc1clpr		CC1CLPR;		/**< 2841_(A0C0 - A0C3h) */
	union	io_r2y_cc1clpg		CC1CLPG;		/**< 2841_(A0C4 - A0C7h) */
	union	io_r2y_cc1clpb		CC1CLPB;		/**< 2841_(A0C8 - A0CBh) */
} CtrlRdmaCc1Val;

/** CC1 matrix coefficient control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_cc1k			CC1K;			/**< 2841_(A0A0 - A0B3h) */
} RdmaCc1CoefVal;

/** Yc convert control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_yc			YC;				/**< 2841_(A100 - A113h) */
	union	io_r2y_yblend		YBLEND;			/**< 2841_(A120 - A123h) */
} CtrlRdmaYccVal;

/** YNR control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_nrctl		NRCTL;			/**< 2841_(A140 - A143h) */
	union	io_r2y_nrof			NROF;			/**< 2841_(A148 - A14Fh) */
	union	io_r2y_nrga			NRGA;			/**< 2841_(A150 - A157h) */
	union	io_r2y_nrbd			NRBD;			/**< 2841_(A158 - A15Fh) */
} CtrlRdmaYnrVal;

/** Edge enhancement noise reduction control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_egsmctl		EGSMCTL;		/**< 2841_(A180 - A183h) */
	union	io_r2y_egsmtt		EGSMTT;			/**< 2841_(A184 - A187h) */
} CtrlRdmaEenrVal;

/** High frequency edge enhancement control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_eghwctl		EGHWCTL;		/**< 2841_(A200 - A203h) */
	union	io_r2y_eghwhpfk		EGHWHPFK;		/**< 2841_(A208 - A20Fh) */
	union	io_r2y_eghwcorpof	EGHWCORPOF;		/**< 2841_(A210 - A217h) */
	union	io_r2y_eghwcorpga	EGHWCORPGA;		/**< 2841_(A218 - A21Bh) */
	union	io_r2y_eghwcorpbd	EGHWCORPBD;		/**< 2841_(A220 - A227h) */
	union	io_r2y_eghwcormof	EGHWCORMOF;		/**< 2841_(A228 - A22Fh) */
	union	io_r2y_eghwcormga	EGHWCORMGA;		/**< 2841_(A230 - A233h) */
	union	io_r2y_eghwcormbd	EGHWCORMBD;		/**< 2841_(A238 - A23Fh) */
	union	io_r2y_eghwsclsup	EGHWSCLSUP;		/**< 2841_(A240 - A243h) */
	union	io_r2y_eghwclppof	EGHWCLPPOF;		/**< 2841_(A248 - A24Fh) */
	union	io_r2y_eghwclppga	EGHWCLPPGA;		/**< 2841_(A250 - A253h) */
	union	io_r2y_eghwclppbd	EGHWCLPPBD;		/**< 2841_(A254 - A257h) */
	union	io_r2y_eghwclpmof	EGHWCLPMOF;		/**< 2841_(A258 - A25Fh) */
	union	io_r2y_eghwclpmga	EGHWCLPMGA;		/**< 2841_(A260 - A263h) */
	union	io_r2y_eghwclpmbd	EGHWCLPMBD;		/**< 2841_(A264 - A267h) */
} CtrlRdmaEghwVal;

/** Medium frequency edge enhancement control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_egmwctl		EGMWCTL;		/**< 2841_(A280 - A283h) */
	union	io_r2y_egmwhpfk		EGMWHPFK;		/**< 2841_(A288 - A28Fh) */
	union	io_r2y_egmwcorpof	EGMWCORPOF;		/**< 2841_(A290 - A297h) */
	union	io_r2y_egmwcorpga	EGMWCORPGA;		/**< 2841_(A298 - A29Bh) */
	union	io_r2y_egmwcorpbd	EGMWCORPBD;		/**< 2841_(A2A0 - A2A7h) */
	union	io_r2y_egmwcormof	EGMWCORMOF;		/**< 2841_(A2A8 - A2AFh) */
	union	io_r2y_egmwcormga	EGMWCORMGA;		/**< 2841_(A2B0 - A2B3h) */
	union	io_r2y_egmwcormbd	EGMWCORMBD;		/**< 2841_(A2B8 - A2BFh) */
	union	io_r2y_egmwsclsup	EGMWSCLSUP;		/**< 2841_(A2C0 - A2C3h) */
	union	io_r2y_egmwclppof	EGMWCLPPOF;		/**< 2841_(A2C8 - A2CFh) */
	union	io_r2y_egmwclppga	EGMWCLPPGA;		/**< 2841_(A2D0 - A2D3h) */
	union	io_r2y_egmwclppbd	EGMWCLPPBD;		/**< 2841_(A2D4 - A2D7h) */
	union	io_r2y_egmwclpmof	EGMWCLPMOF;		/**< 2841_(A2D8 - A2DFh) */
	union	io_r2y_egmwclpmga	EGMWCLPMGA;		/**< 2841_(A2E0 - A2E3h) */
	union	io_r2y_egmwclpmbd	EGMWCLPMBD;		/**< 2841_(A2E4 - A2E7h) */
} CtrlRdmaEgmwVal;

/** Low frequency edge enhancement control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_eglwctl		EGLWCTL;		/**< 2841_(A300 - A303h) */
	union	io_r2y_eglwhpfk		EGLWHPFK;		/**< 2841_(A310 - A31Bh) */
	union	io_r2y_eglwcorpof	EGLWCORPOF;		/**< 2841_(A320 - A327h) */
	union	io_r2y_eglwcorpga	EGLWCORPGA;		/**< 2841_(A328 - A32Bh) */
	union	io_r2y_eglwcorpbd	EGLWCORPBD;		/**< 2841_(A330 - A337h) */
	union	io_r2y_eglwcormof	EGLWCORMOF;		/**< 2841_(A338 - A33Fh) */
	union	io_r2y_eglwcormga	EGLWCORMGA;		/**< 2841_(A340 - A343h) */
	union	io_r2y_eglwcormbd	EGLWCORMBD;		/**< 2841_(A348 - A34Fh) */
	union	io_r2y_eglwsclsup	EGLWSCLSUP;		/**< 2841_(A350 - A353h) */
	union	io_r2y_eglwclppof	EGLWCLPPOF;		/**< 2841_(A358 - A35Fh) */
	union	io_r2y_eglwclppga	EGLWCLPPGA;		/**< 2841_(A360 - A363h) */
	union	io_r2y_eglwclppbd	EGLWCLPPBD;		/**< 2841_(A364 - A367h) */
	union	io_r2y_eglwclpmof	EGLWCLPMOF;		/**< 2841_(A368 - A36Fh) */
	union	io_r2y_eglwclpmga	EGLWCLPMGA;		/**< 2841_(A370 - A373h) */
	union	io_r2y_eglwclpmbd	EGLWCLPMBD;		/**< 2841_(A374 - A377h) */
} CtrlRdmaEglwVal;

/** Edge dot noise correction control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_egdtctl		EGDTCTL;		/**< 2841_(A380 - A383h) */
	union	io_r2y_egdthwth		EGDTHWTH;		/**< 2841_(A384 - A387h) */
	union	io_r2y_egdthwk		EGDTHWK;		/**< 2841_(A388 - A38Bh) */
	union	io_r2y_egdtmwth		EGDTMWTH;		/**< 2841_(A38C - A38Fh) */
	union	io_r2y_egdtmwk		EGDTMWK;		/**< 2841_(A390 - A393h) */
} CtrlRdmaEgdtVal;

/** Edge emphasis blend control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_egcmpctl		EGCMPCTL;		/**< 2841_(A3C0 - A3C3h) */
	union	io_r2y_egcmpbd		EGCMPBD;		/**< 2841_(A3C8 - A3CFh) */
	union	io_r2y_egcmpalpof	EGCMPALPOF;		/**< 2841_(A3D0 - A3D3h) */
	union	io_r2y_egcmpalpga	EGCMPALPGA;		/**< 2841_(A3D8 - A3DFh) */
	union	io_r2y_egcmpbtaof	EGCMPBTAOF;		/**< 2841_(A3E0 - A3E3h) */
	union	io_r2y_egcmpbtaga	EGCMPBTAGA;		/**< 2841_(A3E8 - A3EFh) */
	union	io_r2y_egcmpclp		EGCMPCLP;		/**< 2841_(A3F0 - A3F3h) */
} CtrlRdmaEgcmpVal;

/** Chroma referenced edge and texture adjustment control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_crvaf		CRVAF;			/**< 2841_(A400 - A403h) */
	union	io_r2y_crvbf		CRVBF;			/**< 2841_(A404 - A407h) */
} CtrlRdmaCrvVal;

/** Chroma referenced edge adjustment control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_egcrvctl		EGCRVCTL;		/**< 2841_(A440 - A443h) */
	union	io_r2y_egcrvasclof	EGCRVASCLOF;	/**< 2841_(A444 - A447h) */
	union	io_r2y_egcrvasclga	EGCRVASCLGA;	/**< 2841_(A448 - A44Bh) */
	union	io_r2y_egcrvasclbd	EGCRVASCLBD;	/**< 2841_(A44C - A44Fh) */
	union	io_r2y_egcrvasclcp	EGCRVASCLCP;	/**< 2841_(A450 - A453h) */
	union	io_r2y_egyasclga	EGYASCLGA;		/**< 2841_(A454 - A457h) */
	union	io_r2y_egyasclbd	EGYASCLBD;		/**< 2841_(A458 - A45Bh) */
	union	io_r2y_egyasclclp	EGYASCLCLP;		/**< 2841_(A45C - A45Fh) */
	union	io_r2y_egcrvbsclof	EGCRVBSCLOF;	/**< 2841_(A460 - A463h) */
	union	io_r2y_egcrvbsclga	EGCRVBSCLGA;	/**< 2841_(A464 - A467h) */
	union	io_r2y_egcrvbsclbd	EGCRVBSCLBD;	/**< 2841_(A468 - A46Bh) */
	union	io_r2y_egcrvbsclcp	EGCRVBSCLCP;	/**< 2841_(A46C - A46Fh) */
	union	io_r2y_egybsclga	EGYBSCLGA;		/**< 2841_(A470 - A473h) */
	union	io_r2y_egybsclbd	EGYBSCLBD;		/**< 2841_(A474 - A477h) */
	union	io_r2y_egybsclclp	EGYBSCLCLP;		/**< 2841_(A478 - A47Bh) */
	union	io_r2y_egcrvclp		EGCRVCLP;		/**< 2841_(A47C - A47Fh) */
} CtrlRdmaEgcrvVal;

/** Chroma referenced luminance blend control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_ybcrvctl		YBCRVCTL;		/**< 2841_(A480 - A483h) */
	union	io_r2y_ybcrvaalpof	YBCRVAALPOF;	/**< 2841_(A484 - A487h) */
	union	io_r2y_ybcrvaalpga	YBCRVAALPGA;	/**< 2841_(A488 - A48Bh) */
	union	io_r2y_ybcrvaalpbd	YBCRVAALPBD;	/**< 2841_(A48C - A48Fh) */
	union	io_r2y_ybcrvaalpcp	YBCRVAALPCP;	/**< 2841_(A490 - A493h) */
	union	io_r2y_ybyaalpga	YBYAALPGA;		/**< 2841_(A494 - A497h) */
	union	io_r2y_ybyaalpbd	YBYAALPBD;		/**< 2841_(A498 - A49Bh) */
	union	io_r2y_ybyaalpclp	YBYAALPCLP;		/**< 2841_(A49C - A49Fh) */
	union	io_r2y_ybcrvbalpof	YBCRVBALPOF;	/**< 2841_(A4A0 - A4A3h) */
	union	io_r2y_ybcrvbalpga	YBCRVBALPGA;	/**< 2841_(A4A4 - A4A7h) */
	union	io_r2y_ybcrvbalpbd	YBCRVBALPBD;	/**< 2841_(A4A8 - A4ABh) */
	union	io_r2y_ybcrvbalpcp	YBCRVBALPCP;	/**< 2841_(A4AC - A4AFh) */
	union	io_r2y_ybybalpga	YBYBALPGA;		/**< 2841_(A4B0 - A4B3h) */
	union	io_r2y_ybybalpbd	YBYBALPBD;		/**< 2841_(A4B4 - A4B7h) */
	union	io_r2y_ybybalpclp	YBYBALPCLP;		/**< 2841_(A4B8 - A4BBh) */
} CtrlRdmaYbcrvVal;

/** Color Noise Reduction(LPF) control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_clpfctl		CLPFCTL;		/**< 2841_(A500 - A503h) */
	union	io_r2y_clpfk		CLPFK;			/**< 2841_(A520 - A533h) */
	union	io_r2y_clpfof		CLPFOF;			/**< 2841_(A540 - A543h) */
	union	io_r2y_clpfga		CLPFGA;			/**< 2841_(A548 - A54Fh) */
	union	io_r2y_clpfbd		CLPFBD;			/**< 2841_(A550 - A557h) */
} CtrlRdmaClpfVal;

/** Chroma suppress control register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_csyctl		CSYCTL;			/**< 2841_(A580 - A583h) */
	union	io_r2y_csyof		CSYOF;			/**< 2841_(A588 - A58Fh) */
	union	io_r2y_csyga		CSYGA;			/**< 2841_(A590 - A597h) */
	union	io_r2y_csybd		CSYBD;			/**< 2841_(A598 - A59Fh) */
	union	io_r2y_ycrvfx		YCRVFX;			/**< 2841_(A5A0 - A5A3h) */
	union	io_r2y_cfix			CFIX;			/**< 2841_(A5A4 - A5A7h) */
	union	io_r2y_ycof			YCOF;			/**< 2841_(A5A8 - A5AFh) */
} CtrlRdmaCspVal;

/** Tone control Table register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_sram_tc		TC;				/**< 294A_(0000 - 07FFh) */
} RdmaToneTblVal;

/** Map Scale Table register value info (for RDMA)
*/
typedef struct {
	union	io_r2y_sram_egmpscl	EGMPSCL;		/**< 294A_(CC00 - CDBBh) */
} RdmaEgmpsclTblVal;
#endif	// CO_DDIM_UTILITY_USE

/** Trimming control
*/
typedef struct {
	kuint16					trimming_enable;						/**< YYW0MD.TRM0EN, YYW1MD.TRM1EN, YYW2MD.TRM2EN : Trimming enable (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Do not do the trimming
																		<li>@ref ImR2yCtrl_ENABLE_ON : Trimming	</ul> 							*/
	TImR2yRect			trim_window;							/**< TRM0H, TRM1H, TRM2H : start X position (13bits, multiple of 2)<br>
																		 TRM0V, TRM1V, TRM2V : start Y position (14bits, multiple of 2)			*/
} R2yCtrlTrimming;

/** Trimming control
*/
typedef struct {
	kuint16					trimming_enable_b;						/**< YYW0MD.TRMBEN : Trimming enable (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Do not do the trimming
																		<li>@ref ImR2yCtrl_ENABLE_ON : Trimming	</ul> 							*/
	kuint16					trimming_enable_c;						/**< YYW0MD.TRMCEN : Trimming enable (1bit)
																	<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Do not do the trimming
																		<li>@ref ImR2yCtrl_ENABLE_ON : Trimming	</ul> 							*/
	TImR2yRect			trim_window_b;							/**< TRMBH : start X position (13bits, multiple of 2)<br>
																		 TRMBV : start Y position (14bits, multiple of 2)						*/
	TImR2yRect			trim_window_c;							/**< TRMCH : start X position (13bits, multiple of 2)<br>
																		 TRMCV : start Y position (14bits, multiple of 2)						*/
} CtrlTrimmingExt;

/** Gamma Table(Diff) Table register value info (for RDMA)
*/
typedef union {
	union	io_r2y_sram_gmrgbdf	GMRGBDF;		/**< 294A_(8000 - 87FFh) */
	union	io_r2y_sram_gmrdf	GMRDF;			/**< 294A_(8800 - 8FFFh) */
	union	io_r2y_sram_gmgdf	GMGDF;			/**< 294A_(9000 - 97FFh) */
	union	io_r2y_sram_gmbdf	GMBDF;			/**< 294A_(9800 - 9FFFh) */
	union	io_r2y_sram_gmybdf	GMYBDF;			/**< 294A_(A000 - A7FFh) */
} CtrlRdmaGmdfTblval;

/** Gamma Table(Full) Table register value info (for RDMA)
*/
typedef union {
	union	io_r2y_sram_gmrgbfl	GMRGBFL;		/**< 294A_(A800 - A9FFh) */
	union	io_r2y_sram_gmrfl	GMRFL;			/**< 294A_(AA00 - ABFFh) */
	union	io_r2y_sram_gmgfl	GMGFL;			/**< 294A_(AC00 - ADFFh) */
	union	io_r2y_sram_gmbfl	GMBFL;			/**< 294A_(AE00 - AFFFh) */
	union	io_r2y_sram_gmybfl	GMYBFL;			/**< 294A_(B000 - B1FFh) */
} CtrlRdmaGmflTblval;

/** (High/Medium/Low) Edge emphasis scaling Table register value info (for RDMA)
*/
typedef union {
	union	io_r2y_sram_eghwscl	EGHWSCL;		/**< 294A_(C000 - C1FFh) */
	union	io_r2y_sram_egmwscl	EGMWSCL;		/**< 294A_(C400 - C5FFh) */
	union	io_r2y_sram_eglwscl	EGLWSCL;		/**< 294A_(C800 - C9FFh) */
} CtrlRdmaEgwsclTblval;

/** (High/Medium/Low) Edge emphasis stepping Table register value info (for RDMA)
*/
typedef union {
	union	io_r2y_sram_eghwton	EGHWTON;		/**< 294A_(C200 - C3FFh) */
	union	io_r2y_sram_egmwton	EGMWTON;		/**< 294A_(C600 - C7FFh) */
	union	io_r2y_sram_eglwton	EGLWTON;		/**< 294A_(CA00 - CBFFh) */
} CtrlRdmaEgwtonTblval;


KConstType 		    im_r2y_get_type(void);
ImR2y*		        	im_r2y_new(void);

void im_r2y_update_latest_address(ImR2y *self,kuint16 pipeNo, const UINT32 yywNo);
void im_r2y_get_next_r2y_addr(ImR2y *self,kuint16 pipeNo, const UINT32 yywNo, R2yOutaddrInfo* const r2yAddr);
void im_r2y_get_latest_addr(ImR2y *self, kuint16 pipeNo, UINT32 yywNo, kuint16* const latestBankIdx,
		R2yOutaddrInfo* const latestAddr);
void im_r2y_ddim_print(ImR2y *self, UINT32 loopcnt, UINT32 loopcnt2, UINT32 loopcnt3);


/**
R2Y Initialize
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 Im_r2y_init(ImR2y *self, kuint16 pipeNo );

/**
set AXI bus I/F Control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2yCtrlAxi			: Control information for AXI bus.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl_axi(ImR2y *self, kuint16 pipeNo, const TImR2yCtrlAxi* const r2yCtrlAxi );

/**
get AXI bus read channel status
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2).
@param[out]		r2yAxiReadStat		: Status of AXI bus read channel.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_get_axi_read_stat(ImR2y *self, kuint16 pipeNo, AxiYyrStat* const r2yAxiReadStat );

/**
get AXI bus write channel status
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2).
@param[out]		r2yAxiWriteStat		: Status of AXI bus write channel.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_get_axi_write_stat(ImR2y *self, kuint16 pipeNo, AxiYywStat* const r2yAxiWriteStat );

/**
get AXI bus write channel Transfer mode
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2).
@param[in]		yywNo					: YYW number
@param[out]		r2yAxiWriteMode		: Transfer mode of AXI bus write channel.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_get_axi_write_mode(ImR2y *self, kuint16 pipeNo, kuint16 yywNo, AxiYywMode* const r2yAxiWriteMode );

/**
get AXI bus write channel Transfer mode
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		yywNo					: YYW number
@param[in]		r2yAxiWriteMode		: Transfer mode of AXI bus write channel.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_set_axi_write_mode(ImR2y *self, kuint16 pipeNo, kuint16 yywNo, const AxiYywMode* const r2yAxiWriteMode );

/**
R2Y Control (each mode common control)
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2yCtrl				: Control information for Common.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl(ImR2y *self, kuint16 pipeNo, const TImR2yCtrl* const r2yCtrl );

/**
R2Y Control (photo mode control)
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2yCtrlSdramInput	: Control information.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@retval			ImR2yUtils_MACRO_BUSY		: Macro busy error.
*/
INT32 im_r2y_ctrl_mode_sdram_input(ImR2y *self, kuint16 pipeNo, const CtrlSdramInput* const r2yCtrlSdramInput );

/**
Set Managed Input Address information
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		inAddr					: Input address information.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_set_inaddr_info(ImR2y *self, kuint16 pipeNo, const R2yInaddrInfo* const inAddr );

/**
Set Managed bank information
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2).
@param[in]		yywNo					: YYW number.
@param[in]		r2yBank				: Output bank information.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		Selecting normal format	: Set address in units of 8 bytes.<br>
				Selecting video format	: Set address in units of 16384 bytes.
*/
INT32 im_r2y_set_out_bank_info(ImR2y *self, kuint16 pipeNo, kuint16 yywNo, const R2yOutbankInfo* const r2yBank );

/**
Get bank index value
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2).
@param[in]		yywNo					: YYW number
@param[out]		bankIndex				: Current bank index
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_get_out_bank_index(ImR2y *self, kuint16 pipeNo, kuint16 yywNo, kuint16* const bankIndex );

#endif /* __IM_R2Y_H__ */
