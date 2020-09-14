/*
 * imdisp0.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
#ifndef __IM_DISP0_H__
#define __IM_DISP0_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp.h"

#define IM_TYPE_DISP0				(im_disp0_get_type())
#define IM_DISP0(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp0))
#define IM_IS_DISP0(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP0))

typedef struct   _ImDisp0 			ImDisp0;
typedef struct   _ImDisp0Private		ImDisp0Private;

struct _ImDisp0 {
	KObject parent;
};


KConstType 		im_disp0_get_type(void);
ImDisp0*	im_disp0_get(void);

#define	D_IM_DISP_MATRIX_SIZE						(3)		/**< Size of matrix coefficient.			*/
#define	D_IM_DISP_COLOR_BAR_COUNT					(16)	/**< Maximum number of color bars.			*/
#define	D_IM_DISP_BLOCK_NUM							(2)		/**< Common block number.					*/
#define	D_IM_DISP_INPUT_PARAM_ERROR					(D_IM_DISP | D_DDIM_INPUT_PARAM_ERROR)	/**< Processing result code.<br> Input parameter error.	*/
#define	D_IM_DISP_FACE_FRAME_COUNT					(42)	/**< Maximum number of face frame.			*/

/**	INTE register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	LEE		:1;	/**< LEE: Main data input block forwarding error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG			:3;	/**< Reserve										*/
		ULONG	GR0EE	:1;	/**< GR0EE: OSD data 0 input block forwarding error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	GR1EE	:1;	/**< GR1EE: OSD data 1 input block forwarding error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	GA0EE	:1;	/**< GR0EE: OSD data 0 input block A component forwarding error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	GA1EE	:1;	/**< GR1EE: OSD data 1 input block A component forwarding error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	LREE	:1;	/**< LREE: Main data input block AXI error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG			:3;	/**< Reserve										*/
		ULONG	GR0REE	:1;	/**< GR0REE: OSD data 0 input block AXI error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	GR1REE	:1;	/**< GR1REE: OSD data 1 input block AXI error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	GA0REE	:1;	/**< GR0REE: OSD data 0 input block A component AXI error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	GA1REE	:1;	/**< GR1REE: OSD data 1 input block A component AXI error interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	VE		:1;	/**< VE: Vsync detection interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG			:3;	/**< Reserve										*/
		ULONG	VE2		:1;	/**< VE: Vsync detection interruption permission.
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG			:11;/**< Reserve										*/
	} bit;	/**< Bit field */
} U_IM_DISP_INTE;

/** Image color. */
typedef union {
	ULONG word;	/**< All bits */
	struct {
		ULONG	r	:8;		/**< R<br> Value range:0~255	*/
		ULONG	g	:8;		/**< G<br> Value range:0~255	*/
		ULONG	b	:8;		/**< R<br> Value range:0~255	*/
		ULONG		:8;		/**< Reserve					*/
	} rgb;	/**< bit field of rgb */
	struct {
		ULONG	y	:8;		/**< Y<br> Value range:0~255	*/
		ULONG	cb	:8;		/**< Cb<br> Value range:0~255	*/
		ULONG	cr	:8;		/**< Cr<br> Value range:0~255	*/
		ULONG		:8;		/**< Reserve					*/
	} ycc;	/**< bit field of ycc */
} U_IM_DISP_IMAGE_COLOR;

/** Image color(16 bit). */
typedef union {
	unsigned long	word[2];	/**< All bits */
	struct {
		ULONG	r	:16;	/**< R<br> Value range:0~65535	*/
		ULONG	g	:16;	/**< G<br> Value range:0~65535	*/
		ULONG	b	:16;	/**< R<br> Value range:0~65535	*/
		ULONG		:16;	/**< Reserve					*/
	} rgb;	/**< bit field of rgb */
	struct {
		ULONG	y	:16;	/**< Y<br> Value range:0~65535	*/
		ULONG	cb	:16;	/**< Cb<br> Value range:0~65535	*/
		ULONG	cr	:16;	/**< Cr<br> Value range:0~65535	*/
		ULONG		:16;	/**< Reserve					*/
	} ycc;	/**< bit field of ycc */
} U_IM_DISP_IMAGE_COLOR16;

/**	BLDCTL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	BLD1	:2;		/**< BLD1: Blend order 1 layer selection.<br>
									 <ul><li>@ref D_IM_DISP_BLD_GRID
										 <li>@ref D_IM_DISP_BLD_FACE
										 <li>@ref D_IM_DISP_BLD_OSD0
										 <li>@ref D_IM_DISP_BLD_OSD1</ul>		*/
		ULONG			:2;		/**< Reserve									*/
		ULONG	BLD2	:2;		/**< BLD2: Blend order 2 layer selection.<br>
									 <ul><li>@ref D_IM_DISP_BLD_GRID
										 <li>@ref D_IM_DISP_BLD_FACE
										 <li>@ref D_IM_DISP_BLD_OSD0
										 <li>@ref D_IM_DISP_BLD_OSD1</ul>		*/
		ULONG			:2;		/**< Reserve									*/
		ULONG	BLD3	:2;		/**< BLD3: Blend order 3 layer selection.<br>
									 <ul><li>@ref D_IM_DISP_BLD_GRID
										 <li>@ref D_IM_DISP_BLD_FACE
										 <li>@ref D_IM_DISP_BLD_OSD0
										 <li>@ref D_IM_DISP_BLD_OSD1</ul>		*/
		ULONG			:2;		/**< Reserve									*/
		ULONG	BLD4	:2;		/**< BLD4: Blend order 4 layer selection.<br>
									 <ul><li>@ref D_IM_DISP_BLD_GRID
										 <li>@ref D_IM_DISP_BLD_FACE
										 <li>@ref D_IM_DISP_BLD_OSD0
										 <li>@ref D_IM_DISP_BLD_OSD1</ul>		*/
		ULONG			:18;	/**< Reserve									*/
	} bit;	/**< Bit field */
} U_IM_DISP_BLDCTL;

/** Matrix coefficient (YCbCr <-> RGB). */
typedef union {
	LLONG		dword;	/**< All bits */
	struct {
		LLONG	COEFFICIENT0	:16;	/**< Matrix coefficient 0<br>
											 Value range:-128~127(-2.0~1.984)<br>
											 Regiser:<br>
											 LY2R0.YR00/LY2R1.YR10/LY2R2.YR20<br>
											 R2Y0.RY00/R2Y1.RY10/R2Y2.RY20<br>
											 Y2R0.YR00/Y2R1.YR10/Y2R2.YR20			*/
		LLONG	COEFFICIENT1	:16;	/**< Matrix coefficient 1<br>
											 Value range:-128~127(-2.0~1.984)<br>
											 Regiser:<br>
											 LY2R0.YR01/LY2R1.YR11/LY2R2.YR21<br>
											 R2Y0.RY01/R2Y1.RY11/R2Y2.RY21<br>
											 Y2R0.YR01/Y2R1.YR11/Y2R2.YR21			*/
		LLONG	COEFFICIENT2	:16;	/**< Matrix coefficient 2<br>
											 Value range:-128~127(-2.0~1.984)<br>
											 Regiser:<br>
											 LY2R0.YR02/LY2R1.YR12/LY2R2.YR22<br>
											 R2Y0.RY02/R2Y1.RY12/R2Y2.RY22<br>
											 Y2R0.YR02/Y2R1.YR12/Y2R2.YR22			*/
		LLONG					:16;	/**< Reserve								*/
	}bit;	/**< Bit field */
}U_IM_DISP_YR_MATRIX_COEFFICIENT;

/**	DOCTL0 register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	DTO1	:2;	/**< DTO1: Data output order selection 1.
								 <ul><li>@ref D_IM_DISP_DTO_R_Y0
									 <li>@ref D_IM_DISP_DTO_G_CB
									 <li>@ref D_IM_DISP_DTO_B_CR
									 <li>@ref D_IM_DISP_DTO_0_Y1</ul>	*/
		ULONG			:2;	/**< Reserve								*/
		ULONG	DTO2	:2;	/**< DTO2: Data output order selection 2.
								 <ul><li>@ref D_IM_DISP_DTO_R_Y0
									 <li>@ref D_IM_DISP_DTO_G_CB
									 <li>@ref D_IM_DISP_DTO_B_CR
									 <li>@ref D_IM_DISP_DTO_0_Y1</ul>	*/
		ULONG			:2;	/**< Reserve								*/
		ULONG	DTO3	:2;	/**< DTO3: Data output order selection 3.
								 <ul><li>@ref D_IM_DISP_DTO_R_Y0
									 <li>@ref D_IM_DISP_DTO_G_CB
									 <li>@ref D_IM_DISP_DTO_B_CR
									 <li>@ref D_IM_DISP_DTO_0_Y1</ul>	*/
		ULONG			:2;	/**< Reserve								*/
		ULONG	DTO4	:2;	/**< DTO4: Data output order selection 4.
								 <ul><li>@ref D_IM_DISP_DTO_R_Y0
									 <li>@ref D_IM_DISP_DTO_G_CB
									 <li>@ref D_IM_DISP_DTO_B_CR
									 <li>@ref D_IM_DISP_DTO_0_Y1</ul>	*/
		ULONG			:2;	/**< Reserve								*/
		ULONG	DTO5	:2;	/**< DTO5: Data output order selection 5.
								 <ul><li>@ref D_IM_DISP_DTO_R_Y0
									 <li>@ref D_IM_DISP_DTO_G_CB
									 <li>@ref D_IM_DISP_DTO_B_CR
									 <li>@ref D_IM_DISP_DTO_0_Y1</ul>	*/
		ULONG			:2;	/**< Reserve								*/
		ULONG	DTO6	:2;	/**< DTO6: Data output order selection 6.
								 <ul><li>@ref D_IM_DISP_DTO_R_Y0
									 <li>@ref D_IM_DISP_DTO_G_CB
									 <li>@ref D_IM_DISP_DTO_B_CR
									 <li>@ref D_IM_DISP_DTO_0_Y1</ul>	*/
		ULONG			:10;/**< Reserve								*/
	} bit;	/**< Bit field */
} U_IM_DISP_DOCTL0;

/**	DOCTL1 register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	SOO		:1;	/**< SOO: 0.5pix shift output (Odd line)<br>
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>				*/
		ULONG			:3;	/**< Reserve											*/
		ULONG	SOE		:1;	/**< SOE: 0.5pix shift output (Even line)<br>
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>				*/
		ULONG			:3;	/**< Reserve											*/
		ULONG	ODO0	:1;	/**< ODO0: Data output delay selection 0 (Odd line)<br>
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>				*/
		ULONG	ODO1	:1;	/**< ODO1: Data output delay selection 1 (Odd line)<br>
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>				*/
		ULONG	ODO2	:1;	/**< ODO2: Data output delay selection 2 (Odd line)<br>
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>				*/
		ULONG			:1;	/**< Reserve											*/
		ULONG	ODE0	:1;	/**< ODE0: Data output delay selection 0 (Even line)<br>
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>				*/
		ULONG	ODE1	:1;	/**< ODE1: Data output delay selection 1 (Even line)<br>
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>				*/
		ULONG	ODE2	:1;	/**< ODE2: Data output delay selection 2 (Even line)<br>
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>				*/
		ULONG			:17;/**< Reserve											*/
	} bit;	/**< Bit field */
} U_IM_DISP_DOCTL1;

/**	DOCTL2 register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	CLVS	:1;	/**< CLVS: CbCr data output level selection.<br>
								 <ul><li>@ref D_IM_DISP_CLVS_NORMAL
									 <li>@ref D_IM_DISP_CLVS_SIGNED</ul>	*/
		ULONG			:3;	/**< Reserve									*/
		ULONG	CTOH	:2;	/**< CTOH: Horizontal CbCr  off selection.<br>
								 <ul><li>@ref D_IM_DISP_CTOH_LEFT
									 <li>@ref D_IM_DISP_CTOH_RIGHT
									 <li>@ref D_IM_DISP_CTOH_AVERAGE
									 <li>@ref D_IM_DISP_CTOH_FILTER</ul>	*/
		ULONG			:2;	/**< Reserve									*/
		ULONG	CTOV	:1;	/**< CTOV: Vertical CbCr  off selection.<br>
								 <ul><li>@ref D_IM_DISP_CTOV_TOP
									 <li>@ref D_IM_DISP_CTOV_AVERAGE</ul>	*/
		ULONG			:7;	/**< Reserve									*/
		ULONG	TRSOS	:2;	/**< TRSOS: SAV/EAV code output selection.<br>
								 <ul><li>@ref D_IM_DISP_TRSOS_NONE
									 <li>@ref D_IM_DISP_TRSOS_15_8
									 <li>@ref D_IM_DISP_TRSOS_7_0
									 <li>@ref D_IM_DISP_TRSOS_BOTH</ul>		*/
		ULONG			:14;/**< Reserve									*/
	} bit;	/**< Bit field */
} U_IM_DISP_DOCTL2;

/**	TRSCODE0, TRSCODE1 register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	EAV0	:8;	/**< EAV0: EAV code 00 (or 10)<br>
								 Value range:0~255				*/
		ULONG	SAV0	:8;	/**< SAV0: SAV code 00 (or 10)<br>
								 Value range:0~255				*/
		ULONG	EAV1	:8;	/**< EAV1: EAV code 01 (or 11)<br>
								 Value range:0~255				*/
		ULONG	SAV1	:8;	/**< SAV1: SAV code 01 (or 11)<br>
								 Value range:0~255				*/
	} bit;	/**< Bit field */
} U_IM_DISP_TRSCODE;

/** Processing enable setting of Gamma correct or Anti-Gamma correct or gradation adjustment. */
typedef enum {
	E_IM_DISP_CORRECT_PROC_DISABLE = 0,		/**< Processing disable	*/
	E_IM_DISP_CORRECT_PROC_ENABLE			/**< Processing enable	*/
} E_IM_DISP_CORRECT_PROC;

/**	YCAL register structure. */
typedef struct {
	ULONG	ygain;		/**< YGAIN, CBGAIN, CRGAIN: Gain value.(Y)<br>
							 Value range:0,1~131071(0.000015~1.999985)<br>
							 Gain value is 2(=131072/65536) when a GAIN value is 0.	*/
	ULONG	yofs;		/**< YOFS: Offset value.(Y)<br>
							 In case of YOFS<br>
							 Value range:0~8191<br>									*/
} T_IM_DISP_YCAL;

/**	YCLIP, CBCLIP, CRCLIP register structure. */
typedef struct {
	USHORT	cph;		/**< YCPH, CBCPH, CRCPH: Clip upper bound value.<br>
							 Value range:0x0000~0xFFFF<br>
							 0xFFFF is set up when clip processing is not performed.	*/
	USHORT	cpl;		/**< YCPL, CBCPL, CRCPL: Clip lower bound value.<br>
							 Value range:0x0000~0xFFFF<br>
							 0x0000 is set up when clip processing is not performed.	*/
} T_IM_DISP_CLIP;

/**	CBCAL, CRCAL register structure. */
typedef struct {
	USHORT	cgain;		/**< CBGAIN, CRGAIN: Gain value.(Cb or Cr)<br>
							 Value range:0,1~65565(0.00003~1.99997)<br>
							 Gain value is 2(=65536/32768) when a GAIN value is 0. */
	SHORT	cofs;		/**< CBOFS, CROFS: Offset value.(Cb or Cr)<br>
							 In case of CBOFS, CROFS<br>
							 Value range:-8192~8191<br>							*/
} T_IM_DISP_CCAL;

/** Setting of gain, clip, offset. */
typedef struct {
	T_IM_DISP_YCAL	y_cal;		/**< Gain and offset setting of Y data		*/
	T_IM_DISP_CLIP	y_clip;		/**< Clip setting of Y data					*/
	T_IM_DISP_CCAL	cb_cal;		/**< Gain and offset setting of Cb data		*/
	T_IM_DISP_CLIP	cb_clip;	/**< Clip setting of Cb data				*/
	T_IM_DISP_CCAL	cr_cal;		/**< Gain and offset setting of Cr data		*/
	T_IM_DISP_CLIP	cr_clip;	/**< Clip setting of Cr data				*/
} T_IM_DISP_CLIP_CAL;

/** Setting of face frame parameter. */
typedef struct {
	U_IM_DISP_DSTA		ffdsta;		/**< Display beginning position.	*/
	U_IM_DISP_FFSIZE	ffsize;		/**< Face frame size.				*/
	U_IM_DISP_FFWIDTH	ffwidth;	/**< Face frame width.				*/
	U_IM_DISP_FFCLR		ffclr;		/**< Face frame color.				*/
} T_IM_DISP_FACE_FRAME_PARAM;

/** Setting of face frame. */
typedef struct {
	T_IM_DISP_FACE_FRAME_PARAM	param[D_IM_DISP_FACE_FRAME_COUNT];	/**< Face frame parameter.								*/
	unsigned long long			ffden;								/**< FFDISPEN.FFDEN: Face frame display enable.<br>
																		 bit d[0]:Face frame 0 ~ d[41]:Face frame 41<br>
																		 Value 0:disable, 1:enable<br>						*/
	BYTE						msff;								/**< FFDO.MSFF: Top face frame setting register.<br>
																		 Value range:0~41 (face frame 0 ~ face frame 41)	*/
} T_IM_DISP_FACE_FRAME;

/**
Control data of data output block.<br>
It is possible to rewrite it while data output block is operating.
*/
typedef struct {
	// Whole control register area.
	ULONG							intc;									/**< INTC: Interruption control register.<br>
																				 <ul><li>@ref D_IM_DISP_VFTMG_NONE
																				     <li>@ref D_IM_DISP_VFTMG_1ST
																					 <li>@ref D_IM_DISP_VFTMG_2ND
																					 <li>@ref D_IM_DISP_VFTMG_1ST_2ND</ul>								*/
	U_IM_DISP_INTE					inte;									/**< INTE: Interruption enable register.<br>								*/
	// Timing control register area.
	ULONG							hablk;									/**< HABLK: Horizontal blank adjustment setting register.<br>
																				 Value range:0~4095														*/
	// Output data control register area.
	ULONG							fdoen;									/**< FDOEN: Fource data output enable register.<br>
																				 <ul><li>@ref D_IM_DISP_ENABLE_OFF
																					 <li>@ref D_IM_DISP_ENABLE_ON</ul>									*/
	U_IM_DISP_IMAGE_COLOR			fodata;									/**< FODATA: Fource output data setting register.<br>						*/
	U_IM_DISP_IMAGE_COLOR16			blankdt;								/**< BLANKDT: Blank data setting register.<br>								*/
	ULONG							clbhsize;								/**< CLBHSIZE: Color bar horizontal size setting register.<br>
																				 Value range:0~65535<br>												*/
	U_IM_DISP_IMAGE_COLOR			clbdt[D_IM_DISP_COLOR_BAR_COUNT];		/**< CLBDT: Color bar display color setting register.<br>					*/
	U_IM_DISP_BLDCTL				bldctl;									/**< BLDCTL: Blend order 1~4 layer selection.<br>							*/
	U_IM_DISP_YR_MATRIX_COEFFICIENT	r2y[D_IM_DISP_MATRIX_SIZE];				/**< R2Y0/1/2: RGB->YCbCr matrix coefficient setting register.<br>			*/
	T_IM_DISP_CLIP_CAL				clip_cal;								/**< YCAL  : Y data operation setting.<br>
																				 YCLIP : Y data clip setting.<br>
																				 CBCAL : Cb data operation setting.<br>
																				 CBCLIP: Cb data clip setting.<br>
																				 CRCAL : Cr data operation setting.<br>
																				 CRCLIP: Cr data clip setting.<br>										*/
	U_IM_DISP_DOCTL0				doctl0;									/**< DOCTL0: Data output control 0 register.<br>							*/
	U_IM_DISP_DOCTL1				doctl1;									/**< DOCTL1: Data output control 1 register.<br>							*/
	U_IM_DISP_DOCTL2				doctl2;									/**< DOCTL2: Data output control 2 register.<br>							*/
	U_IM_DISP_TRSCODE				trscode[2];								/**< TRSCODE0: SAV/EAV code setting 0 register.<br>
																				 TRSCODE1: SAV/EAV code setting 1 register.<br>							*/
	U_IM_DISP_YR_MATRIX_COEFFICIENT	y2r[D_IM_DISP_MATRIX_SIZE];				/**< Y2R0/1/2: YCbCr->RGB matrix coefficient setting register.				*/
	E_IM_DISP_CORRECT_PROC			tblaset_gmen;							/**< TBLASET.gmen: Gamma correction enable.<br>
																				 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
																					 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>						*/
	BYTE							tblaset_gmtsl;							/**< TBLASET.gmtsl: Gamma correction table surface.<br>
																				 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
																					 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>							*/
	E_IM_DISP_CORRECT_PROC			tblaset_ysaten;							/**< TBLASET.YSATEN: Luminance and chroma correction enable.<br>
																				 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
																					 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>						*/
	BYTE							tblaset_ysatsl;							/**< TBLASET.YSATSL: Luminance and chroma correction table surface.<br>
																				 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
																					 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>							*/
	// Face frame
	T_IM_DISP_FACE_FRAME			face;									/**< Face frame data.<br>													*/
	// Interrupt callback functions.
	VP_CALLBACK						int_callback[ImDisp_E_IM_DISP_INT_CB_MAX];		/**< Interrupt callback functions.											*/
} T_IM_DISP_CTRL_OUTPUT;


void im_disp0_memcpy(ImDisp0 * self,ImDispEImDispSel block , T_IM_DISP_CTRL_OUTPUT const *const ctrl);
void im_disp0_memcpy1(ImDisp0 * self,ImDispEImDispSel block , T_IM_DISP_CTRL_OUTPUT *const ctrl);
void im_disp0_gim_Disp_Interrupt_Callback1(ImDisp0 * self);
 INT32 im_disp0_set_int_callback(ImDisp0 * self, ImDispEImDispSel block, UINT32 interruption_select, VP_CALLBACK vp_callback);

/**
Get interruption's call-back function pointer.<br>
@param[in]	block				Common block selection.<br>
								<ul><li>@ref ImDisp_E_IM_DISP_HDMI
									<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	interruption_select	Bit map to select set item. <br>
								It must be set to a value exclude @ref ImDisp_E_IM_DISP_CORRECT_SELECT_ALL.<br>
@param[out]	vp_callback			The call-back pointer.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp0_get_int_callback(ImDisp0 * self, ImDispEImDispSel block, ImDispEImDispInterruptionSelect interruption_select, VP_CALLBACK *vp_callback);

/**
Get AXI state.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	axi_state		AXI state.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
#endif /* __IM_DISP0_H__ */
/** @}*//* end of im_disp*/

/** @weakgroup im_disp
@{
<hr>
@section im_disp_Initialize Initialize DISP
This is a sample for Initialize DISP while system start up<br>
@code
// SAMPLE CODE //
VOID im_disp_sample_initialize(VOID)
{
	INT32									ret;
	INT32									i;
	T_IM_DISP_CTRL_MAIN_TBL					ctrl_tbl_main_lcd;
	T_IM_DISP_CTRL_OUTPUT_TBL				ctrl_tbl_out_lcd;

	T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT		ctrl_trg_limit_main_lcd;
	T_IM_DISP_CTRL_MAIN_LAYER				ctrl_main_lcd;

	T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT			ctrl_trg_limit_out_lcd;
	T_IM_DISP_CTRL_OUTPUT					ctrl_out_lcd;

	ImDispEImDispRpgtmg						grrpgctl;
	T_IM_DISP_CTRL_OSD_LAYER				ctrl_osd_lcd;

	UINT32 r_anti_tbl_a[32/2] = {	0x00040000, 0x000C0008, 0x00140010, 0x001C0018,
									0x00240020, 0x002C0028, 0x002C0028, 0x003C0038,
									0x00440040, 0x004C0048, 0x00540050, 0x005C0058,
									0x00640060, 0x006C0068, 0x00740070, 0x007C0078
	};
	UINT32 g_anti_tbl_a[32/2] = {	0x00080004, 0x0010000C, 0x00180014, 0x0020001C,
									0x00280024, 0x0030002C, 0x00380034, 0x0040003C,
									0x00480044, 0x0050004C, 0x00580054, 0x0060005C,
									0x00680064, 0x0070006C, 0x00780074, 0x0080007C
	};
	UINT32 b_anti_tbl_a[32/2] = {	0x00040000, 0x000C0008, 0x00140010, 0x001C0018,
									0x00240020, 0x002C0028, 0x00340030, 0x003C0038,
									0x00440040, 0x004C0048, 0x00540050, 0x005C0058,
									0x00640060, 0x006C0068, 0x00740070, 0x007C0078
	};
	UINT32 r_anti_tbl_b[32/2] = {	0x00040000, 0x000C0008, 0x00140010, 0x001C0018,
									0x00240020, 0x002C0028, 0x002C0028, 0x003C0038,
									0x00440040, 0x004C0048, 0x00540050, 0x005C0058,
									0x00640060, 0x006C0068, 0x00740070, 0x007C0078
	};
	UINT32 g_anti_tbl_b[32/2] = {	0x00080004, 0x0010000C, 0x00180014, 0x0020001C,
									0x00280024, 0x0030002C, 0x00380034, 0x0040003C,
									0x00480044, 0x0050004C, 0x00580054, 0x0060005C,
									0x00680064, 0x0070006C, 0x00780074, 0x0080007C
	};
	UINT32 b_anti_tbl_b[32/2] = {	0x00040000, 0x000C0008, 0x00140010, 0x001C0018,
									0x00240020, 0x002C0028, 0x00340030, 0x003C0038,
									0x00440040, 0x004C0048, 0x00540050, 0x005C0058,
									0x00640060, 0x006C0068, 0x00740070, 0x007C0078
	};
	UINT32 r_gamma_tbl_a_in[32/2] = {	0x00040000, 0x000C0008, 0x000C0008, 0x001C0018,
										0x00240020, 0x002C0028, 0x00340030, 0x003C0038,
										0x00440040, 0x004C0048, 0x00540050, 0x005C0058,
										0x00640060, 0x006C0068, 0x00740070, 0x007C0078
	};
	UINT32 g_gamma_tbl_a_in[32/2] = {	0x00080004, 0x0010000C, 0x00180014, 0x0020001C,
										0x00280024, 0x0030002C, 0x00380034, 0x0040003C,
										0x00480044, 0x0050004C, 0x00580054, 0x0060005C,
										0x00680064, 0x0070006C, 0x00780074, 0x0080007C
	};
	UINT32 b_gamma_tbl_a_in[32/2] = {	0x00040000, 0x000C0008, 0x00140010, 0x001C0018,
										0x00240020, 0x002C0028, 0x00340030, 0x003C0038,
										0x00440040, 0x004C0048, 0x00540050, 0x005C0058,
										0x00640060, 0x006C0068, 0x00740070, 0x007C0078
	};
	UINT32 r_gamma_tbl_b_in[32/2] = {	0x00040000, 0x000C0008, 0x000C0008, 0x001C0018,
										0x00240020, 0x002C0028, 0x00340030, 0x003C0038,
										0x00440040, 0x004C0048, 0x00540050, 0x005C0058,
										0x00640060, 0x006C0068, 0x00740070, 0x007C0078
	};
	UINT32 g_gamma_tbl_b_in[32/2] = {	0x00080004, 0x0010000C, 0x00180014, 0x0020001C,
										0x00280024, 0x0030002C, 0x00380034, 0x0040003C,
										0x00480044, 0x0050004C, 0x00580054, 0x0060005C,
										0x00680064, 0x0070006C, 0x00780074, 0x0080007C
	};
	UINT32 b_gamma_tbl_b_in[32/2] = {	0x00040000, 0x000C0008, 0x00140010, 0x001C0018,
										0x00240020, 0x002C0028, 0x00340030, 0x003C0038,
										0x00440040, 0x004C0048, 0x00540050, 0x005C0058,
										0x00640060, 0x006C0068, 0x00740070, 0x007C0078
	};
	USHORT r_gamma_tbl_a_out[33] = {	0x0000, 0x0004, 0x0008, 0x000C, 0x0010, 0x0014, 0x0018, 0x001C,
										0x0020, 0x0024, 0x0028, 0x002C, 0x0030, 0x0034, 0x0038, 0x003C,
										0x0040, 0x0044, 0x0048, 0x004C, 0x0050, 0x0054, 0x0058, 0x005C,
										0x0060, 0x0064, 0x0068, 0x006C, 0x0070, 0x0074, 0x0078, 0x007C, 0x0080
	};
	USHORT g_gamma_tbl_a_out[33] = {	0x0080, 0x0084, 0x0088, 0x008C, 0x0090, 0x0094, 0x0098, 0x009C,
										0x00A0, 0x00A4, 0x00A8, 0x00AC, 0x00B0, 0x00B4, 0x00B8, 0x00BC,
										0x00C0, 0x00C4, 0x00C8, 0x00CC, 0x00D0, 0x00D4, 0x00D8, 0x00DC,
										0x00E0, 0x00E4, 0x00E8, 0x00EC, 0x00F0, 0x00F4, 0x00F8, 0x00FC, 0x00FF
	};
	USHORT b_gamma_tbl_a_out[33] = {	0x0010, 0x0014, 0x0018, 0x001C, 0x0030, 0x0034, 0x0038, 0x003C,
										0x0050, 0x0054, 0x0058, 0x005C, 0x0070, 0x0074, 0x0078, 0x007C,
										0x0020, 0x0024, 0x0028, 0x002C, 0x0040, 0x0044, 0x0048, 0x004C,
										0x0060, 0x0064, 0x0068, 0x006C, 0x0080, 0x0084, 0x0088, 0x008C, 0x0090
	};
	USHORT r_gamma_tbl_b_out[33] = {	0x0000, 0x0004, 0x0008, 0x000C, 0x0010, 0x0014, 0x0018, 0x001C,
										0x0020, 0x0024, 0x0028, 0x002C, 0x0030, 0x0034, 0x0038, 0x003C,
										0x0040, 0x0044, 0x0048, 0x004C, 0x0050, 0x0054, 0x0058, 0x005C,
										0x0060, 0x0064, 0x0068, 0x006C, 0x0070, 0x0074, 0x0078, 0x007C, 0x0080
	};
	USHORT g_gamma_tbl_b_out[33] = {	0x0080, 0x0084, 0x0088, 0x008C, 0x0090, 0x0094, 0x0098, 0x009C,
										0x00A0, 0x00A4, 0x00A8, 0x00AC, 0x00B0, 0x00B4, 0x00B8, 0x00BC,
										0x00C0, 0x00C4, 0x00C8, 0x00CC, 0x00D0, 0x00D4, 0x00D8, 0x00DC,
										0x00E0, 0x00E4, 0x00E8, 0x00EC, 0x00F0, 0x00F4, 0x00F8, 0x00FC, 0x00FF
	};
	USHORT b_gamma_tbl_b_out[33] = {	0x0010, 0x0014, 0x0018, 0x001C, 0x0030, 0x0034, 0x0038, 0x003C,
										0x0050, 0x0054, 0x0058, 0x005C, 0x0070, 0x0074, 0x0078, 0x007C,
										0x0020, 0x0024, 0x0028, 0x002C, 0x0040, 0x0044, 0x0048, 0x004C,
										0x0060, 0x0064, 0x0068, 0x006C, 0x0080, 0x0084, 0x0088, 0x008C, 0x0090
	};
	USHORT luminance_a[33] = {	0x0000, 0x0004, 0x0008, 0x000C, 0x0010, 0x0014, 0x0018, 0x001C,
								0x0020, 0x0024, 0x0028, 0x002C, 0x0030, 0x0034, 0x0038, 0x003C,
								0x0040, 0x0044, 0x0048, 0x004C, 0x0050, 0x0054, 0x0058, 0x005C,
								0x0060, 0x0064, 0x0068, 0x006C, 0x0070, 0x0074, 0x0078, 0x007C, 0x0080
	};
	USHORT luminance_b[33] = {	0x0080, 0x0084, 0x0088, 0x008C, 0x0090, 0x0094, 0x0098, 0x009C,
								0x00A0, 0x00A4, 0x00A8, 0x00AC, 0x00B0, 0x00B4, 0x00B8, 0x00BC,
								0x00C0, 0x00C4, 0x00C8, 0x00CC, 0x00D0, 0x00D4, 0x00D8, 0x00DC,
								0x00E0, 0x00E4, 0x00E8, 0x00EC, 0x00F0, 0x00F4, 0x00F8, 0x00FC, 0x00FF
	};
	USHORT chroma_a[33] = {	0x0000, 0x0004, 0x0008, 0x000C, 0x0010, 0x0014, 0x0018, 0x001C,
							0x0020, 0x0024, 0x0028, 0x002C, 0x0030, 0x0034, 0x0038, 0x003C,
							0x0040, 0x0044, 0x0048, 0x004C, 0x0050, 0x0054, 0x0058, 0x005C,
							0x0060, 0x0064, 0x0068, 0x006C, 0x0070, 0x0074, 0x0078, 0x007C, 0x0080
	};
	USHORT chroma_b[33] = {	0x0080, 0x0084, 0x0088, 0x008C, 0x0090, 0x0094, 0x0098, 0x009C,
							0x00A0, 0x00A4, 0x00A8, 0x00AC, 0x00B0, 0x00B4, 0x00B8, 0x00BC,
							0x00C0, 0x00C4, 0x00C8, 0x00CC, 0x00D0, 0x00D4, 0x00D8, 0x00DC,
							0x00E0, 0x00E4, 0x00E8, 0x00EC, 0x00F0, 0x00F4, 0x00F8, 0x00FC, 0x00FF
	};

	// Set display I/F selection
	im_disp4_set_display_interface(im_disp4_new(),ImDisp_E_IM_DISP_LCD_MIPI, D_IM_DISP_IFS_LCD);

	// Clear software reset of DISP
	im_disp1_init(im_disp1_new());

	// DISP is initialize by default setting
	// Set main data input block table
	memset(&ctrl_tbl_main_lcd, 0, sizeof(ctrl_tbl_main_lcd));
	ctrl_tbl_main_lcd.anti_a.r_anti		= (USHORT*)r_anti_tbl_a;
	ctrl_tbl_main_lcd.anti_a.g_anti		= (USHORT*)g_anti_tbl_a;
	ctrl_tbl_main_lcd.anti_a.b_anti		= (USHORT*)b_anti_tbl_a;
	ctrl_tbl_main_lcd.anti_b.r_anti		= (USHORT*)r_anti_tbl_b;
	ctrl_tbl_main_lcd.anti_b.g_anti		= (USHORT*)g_anti_tbl_b;
	ctrl_tbl_main_lcd.anti_b.b_anti		= (USHORT*)b_anti_tbl_b;
	ctrl_tbl_main_lcd.gamma_a.r_data	= (USHORT*)r_gamma_tbl_a_in;
	ctrl_tbl_main_lcd.gamma_a.g_data	= (USHORT*)g_gamma_tbl_a_in;
	ctrl_tbl_main_lcd.gamma_a.b_data	= (USHORT*)b_gamma_tbl_a_in;
	ctrl_tbl_main_lcd.gamma_b.r_data	= (USHORT*)r_gamma_tbl_b_in;
	ctrl_tbl_main_lcd.gamma_b.g_data	= (USHORT*)g_gamma_tbl_b_in;
	ctrl_tbl_main_lcd.gamma_b.b_data	= (USHORT*)b_gamma_tbl_b_in;

	ret = im_disp2_ctrl_main_tbl(im_disp2_new(),ImDisp_E_IM_DISP_LCD_MIPI, &ctrl_tbl_main_lcd);
	if (ret != D_DDIM_OK){
		Ddim_Print(("I:im_disp2_ctrl_main_tbl error ret=%08X\n", ret));
	}

	// Set main data input block table
	memset(&ctrl_tbl_out_lcd, 0, sizeof(ctrl_tbl_out_lcd));
	ctrl_tbl_out_lcd.gamma_a.r_data	= (USHORT*)r_gamma_tbl_a_out;
	ctrl_tbl_out_lcd.gamma_a.g_data	= (USHORT*)g_gamma_tbl_a_out;
	ctrl_tbl_out_lcd.gamma_a.b_data	= (USHORT*)b_gamma_tbl_a_out;
	ctrl_tbl_out_lcd.gamma_b.r_data	= (USHORT*)r_gamma_tbl_b_out;
	ctrl_tbl_out_lcd.gamma_b.g_data	= (USHORT*)g_gamma_tbl_b_out;
	ctrl_tbl_out_lcd.gamma_b.b_data	= (USHORT*)b_gamma_tbl_b_out;
	ctrl_tbl_out_lcd.luminance_a	= (USHORT*)&luminance_a;
	ctrl_tbl_out_lcd.chroma_a		= (USHORT*)&chroma_a;
	ctrl_tbl_out_lcd.luminance_b	= (USHORT*)&luminance_b;
	ctrl_tbl_out_lcd.chroma_b		= (USHORT*)&chroma_b;

	ret = im_disp2_ctrl_output_tbl(im_disp2_new(),ImDisp_E_IM_DISP_LCD_MIPI, &ctrl_tbl_out_lcd);
	if (ret != D_DDIM_OK){
		Ddim_Print(("I:im_disp2_ctrl_output_tbl error ret=%08X\n", ret));
	}

	// Set main data input block
	memset(&ctrl_trg_limit_main_lcd, 0, sizeof(ctrl_trg_limit_main_lcd));
	ctrl_trg_limit_main_lcd.lrpgctl			= ImDisp_E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP;
	ctrl_trg_limit_main_lcd.ltblaset_igtaen	= ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE;
	ctrl_trg_limit_main_lcd.ltblaset_gtaen	= ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE;

	memset(&ctrl_main_lcd, 0, sizeof(ctrl_main_lcd));
	ctrl_main_lcd.lidt.bit.ifmt			= D_IM_DISP_LIDT_IFMT_YCC422_RP_8BIT;
	ctrl_main_lcd.lidt.bit.nbt			= D_IM_DISP_NBT_128BYTE;
	ctrl_main_lcd.lidt.bit.ifew			= D_IM_DISP_IFEW_16BIT;
	ctrl_main_lcd.lidt.bit.lvfm			= D_IM_DISP_FORMAT_NORMAL;
	ctrl_main_lcd.lidt.bit.pkgdv		= 0;
	ctrl_main_lcd.lidt.bit.cache		= 0;
	ctrl_main_lcd.lidt.bit.pROT			= 0;
	ctrl_main_lcd.lidt.bit.yslvsl		= D_IM_DISP_SLVSL_MASTER_INTERFACE_0;
	ctrl_main_lcd.lidt.bit.cslvsl		= D_IM_DISP_SLVSL_MASTER_INTERFACE_0;
	ctrl_main_lcd.lisize.size.width		= 640;
	ctrl_main_lcd.lisize.size.lines		= 480;
	ctrl_main_lcd.laddr[0].y_addr		= 0x50000000;
	ctrl_main_lcd.laddr[0].c_addr		= 0x50100000;
	ctrl_main_lcd.laddr[1].y_addr		= 0x50200000;
	ctrl_main_lcd.laddr[1].c_addr		= 0x50300000;
	ctrl_main_lcd.laddr[2].y_addr		= 0x50400000;
	ctrl_main_lcd.laddr[2].c_addr		= 0x50500000;
	ctrl_main_lcd.laddr[3].y_addr		= 0x50600000;
	ctrl_main_lcd.laddr[3].c_addr		= 0x50700000;
	ctrl_main_lcd.y_hga					= 640;
	ctrl_main_lcd.c_hga					= 480;
	ctrl_main_lcd.libctl_iben			= 0;
	ctrl_main_lcd.libctl_ibset			= E_IM_DISP_BANK_00;
	ctrl_main_lcd.lercv					= E_IM_DISP_ERCV_ON;
	ctrl_main_lcd.lrsz0					= ImDisp_E_IM_DISP_RSZSL_PADDING_THINNING;
	ctrl_main_lcd.lrsz1.bit.hrszm		= 1;
	ctrl_main_lcd.lrsz1.bit.hrszn		= 1;
	ctrl_main_lcd.lrsz1.bit.hrszof		= 0;
	ctrl_main_lcd.lrsz2.bit.vrszm		= 1;
	ctrl_main_lcd.lrsz2.bit.vrszn		= 1;
	ctrl_main_lcd.lrsz2.bit.vrszof		= 0;
	ctrl_main_lcd.lrsz3.bit.hcsta		= 0;
	ctrl_main_lcd.lrsz3.bit.vcsta		= 0;
	ctrl_main_lcd.yhlp.lyhlpcl.bit.yhlpen		= 0;
	ctrl_main_lcd.yhlp.lyhlpcl.bit.yhlpmd		= E_IM_DISP_YHLPMD_HORIZONTAL_SPACE_FILTER;
	ctrl_main_lcd.yhlp.lyhlpk.bit.yhlpk0		= 0;
	ctrl_main_lcd.yhlp.lyhlpk.bit.yhlpk1		= 0;
	ctrl_main_lcd.yhlp.lyhlpk.bit.yhlpk2		= 0;
	ctrl_main_lcd.yhlp.lyhlpk.bit.yhlpk3		= 0;
	ctrl_main_lcd.yhlp.lyhlpol.bit.yhlpcor		= 0;
	ctrl_main_lcd.yhlp.lyhlpol.bit.yhlpth		= 0;
	ctrl_main_lcd.yhlp.lyhlpclr.bit.yhlpy		= 0;
	ctrl_main_lcd.yhlp.lyhlpclr.bit.yhlpcb		= 0;
	ctrl_main_lcd.yhlp.lyhlpclr.bit.yhlpcr		= 0;
	ctrl_main_lcd.warning.lywctl.bit.ywen		= D_IM_DISP_ENABLE_OFF;
	ctrl_main_lcd.warning.lywctl.bit.ywsl		= E_IM_DISP_YWSL_BRIGHTNESS_SPECIFIED_COLOR;
	ctrl_main_lcd.warning.lyw0th.bit.ywthh		= 0;
	ctrl_main_lcd.warning.lyw0th.bit.ywthl		= 0;
	ctrl_main_lcd.warning.lyw1th.bit.ywthh		= 0;
	ctrl_main_lcd.warning.lyw1th.bit.ywthl		= 0;
	ctrl_main_lcd.warning.lyw0st				= ImDisp_E_IM_DISP_YWMD_BR_RGB;
	ctrl_main_lcd.warning.lyw0ca.bit.ywy		= 0;
	ctrl_main_lcd.warning.lyw0ca.bit.ywcb		= 0;
	ctrl_main_lcd.warning.lyw0ca.bit.ywcr		= 0;
	ctrl_main_lcd.warning.lyw0ca.bit.ywa		= 0;
	ctrl_main_lcd.warning.lyw0cb.bit.ywy		= 0;
	ctrl_main_lcd.warning.lyw0cb.bit.ywcb		= 0;
	ctrl_main_lcd.warning.lyw0cb.bit.ywcr		= 0;
	ctrl_main_lcd.warning.lyw0cb.bit.ywa		= 0;
	ctrl_main_lcd.warning.lyw1st				= ImDisp_E_IM_DISP_YWMD_BR_RGB;
	ctrl_main_lcd.warning.lyw1ca.bit.ywy		= 0;
	ctrl_main_lcd.warning.lyw1ca.bit.ywcb		= 0;
	ctrl_main_lcd.warning.lyw1ca.bit.ywcr		= 0;
	ctrl_main_lcd.warning.lyw1ca.bit.ywa		= 0;
	ctrl_main_lcd.warning.lyw1cb.bit.ywy		= 0;
	ctrl_main_lcd.warning.lyw1cb.bit.ywcb		= 0;
	ctrl_main_lcd.warning.lyw1cb.bit.ywcr		= 0;
	ctrl_main_lcd.warning.lyw1cb.bit.ywa		= 0;
	ctrl_main_lcd.warning.lbost					= D_IM_DISP_BOMD_MASTER;
	ctrl_main_lcd.lbltmr.bit.btimh		= 0;
	ctrl_main_lcd.lbltmr.bit.btiml		= 0;
	ctrl_main_lcd.lbltmr.bit.btimd		= D_IM_DISP_BTIMD_NORMAL;
	ctrl_main_lcd.zebra.lzbwid.bit.zbhh	= 2;
	ctrl_main_lcd.zebra.lzbwid.bit.zbhl	= 2;
	ctrl_main_lcd.zebra.lzbv.bit.zbvsta	= 0;
	ctrl_main_lcd.zebra.lzbv.bit.zbvcyc	= 0;
	ctrl_main_lcd.zebra.lzbpt.bit.zbdir	= 0;
	ctrl_main_lcd.ly2r[0].dword			= 0x0000001f00eb002a;
	ctrl_main_lcd.ly2r[1].dword			= 0x000000d300f70048;
	ctrl_main_lcd.ly2r[2].dword			= 0x000000fc00720046;
	ctrl_main_lcd.ltblaset_igen			= E_IM_DISP_CORRECT_PROC_ENABLE;
	ctrl_main_lcd.ltblaset_igtsl		= D_IM_DISP_TABLE_SURFACE_A;
	ctrl_main_lcd.ltblaset_gmen			= E_IM_DISP_CORRECT_PROC_ENABLE;
	ctrl_main_lcd.ltblaset_gmtsl		= D_IM_DISP_TABLE_SURFACE_A;
	ctrl_main_lcd.lcc[0].dword			= 0x000000f300f90040;
	ctrl_main_lcd.lcc[1].dword			= 0x0000000700410000;
	ctrl_main_lcd.lcc[2].dword			= 0x0000004100040000;
	ctrl_main_lcd.lgmmd.bit.GMMD		= D_IM_DISP_GMMD_EQUAL_INTERVAL_MODE;
	ctrl_main_lcd.lalp.bit.ALP			= 255;
	ctrl_main_lcd.ldsta.bit.DSH			= 0;
	ctrl_main_lcd.ldsta.bit.DSV			= 0;
	ctrl_main_lcd.lrevdisp.bit.HREV		= D_IM_DISP_REV_NORMAL;
	ctrl_main_lcd.lrevdisp.bit.VREV		= D_IM_DISP_REV_NORMAL;

	ret = im_disp1_ctrl_main_layer(im_disp1_new(),ImDisp_E_IM_DISP_LCD_MIPI, &ctrl_trg_limit_main_lcd, &ctrl_main_lcd);
	if (ret != D_DDIM_OK){
		Ddim_Print(("I:im_disp1_ctrl_main_layer error ret=%08X\n", ret));
	}

	// Set data output block
	memset(&ctrl_trg_limit_out_lcd, 0, sizeof(ctrl_trg_limit_out_lcd));
	ctrl_trg_limit_out_lcd.tgkmd			= ImDisp_E_IM_DISP_TGKMD_NORMAL;
	ctrl_trg_limit_out_lcd.tgkst			= 0;
	ctrl_trg_limit_out_lcd.toctl.bit.CON	= D_IM_DISP_CON_EXTERNAL;
	ctrl_trg_limit_out_lcd.toctl.bit.CKOEN	= D_IM_DISP_ENABLE_OFF;
	ctrl_trg_limit_out_lcd.toctl.bit.CKICEN	= D_IM_DISP_ENABLE_OFF;
	ctrl_trg_limit_out_lcd.polsel.bit.VDPS	= D_IM_DISP_POLARITY_POSITIVE;
	ctrl_trg_limit_out_lcd.polsel.bit.HDPS	= D_IM_DISP_POLARITY_POSITIVE;
	ctrl_trg_limit_out_lcd.polsel.bit.VEPS	= D_IM_DISP_POLARITY_POSITIVE;
	ctrl_trg_limit_out_lcd.polsel.bit.HEPS	= D_IM_DISP_POLARITY_POSITIVE;
	ctrl_trg_limit_out_lcd.polsel.bit.CKEG	= D_IM_DISP_CKEG_FALL;
	ctrl_trg_limit_out_lcd.rpgctl			= ImDisp_E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP;
	ctrl_trg_limit_out_lcd.tsl				= D_IM_DISP_TSL_PROGRESSIVE;
	ctrl_trg_limit_out_lcd.vcyc.bit.VCYC1	= 482;
	ctrl_trg_limit_out_lcd.vcyc.bit.VCYC2	= 482;
	ctrl_trg_limit_out_lcd.vcyc.bit.VDSFT	= D_IM_DISP_VDSFT_NORMAL;
	ctrl_trg_limit_out_lcd.hcyc				= 668;
	ctrl_trg_limit_out_lcd.ovpw.bit.OVPW	= 0x0010;
	ctrl_trg_limit_out_lcd.ovpw.bit.OVPWU	= D_IM_DISP_OVPWU_CLOCK_UNIT;
	ctrl_trg_limit_out_lcd.hpw				= 0x0010;
	ctrl_trg_limit_out_lcd.vblk.bit.VBLK1	= 1;
	ctrl_trg_limit_out_lcd.vblk.bit.VBLK2	= 1;
	ctrl_trg_limit_out_lcd.hblk				= 16;
	ctrl_trg_limit_out_lcd.vdly				= 0;
	ctrl_trg_limit_out_lcd.hdly				= 0;
	ctrl_trg_limit_out_lcd.ovsize			= 480;
	ctrl_trg_limit_out_lcd.ohsize			= 640;
	ctrl_trg_limit_out_lcd.vrfctl			= D_IM_DISP_VENS_H_ENABLE;
	ctrl_trg_limit_out_lcd.hrfctl			= D_IM_DISP_HENS_ASSERT_ON;
	ctrl_trg_limit_out_lcd.domd.bit.MODE	= D_IM_DISP_MODE_RGB888_24BIT;
	ctrl_trg_limit_out_lcd.domd.bit.OBPSL	= D_IM_DISP_OBPSL_LSB;
	ctrl_trg_limit_out_lcd.domd.bit.OBUSL	= D_IM_DISP_OBUSL_8BIT;
	ctrl_trg_limit_out_lcd.tblaset_gmtaen	= ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE;
	ctrl_trg_limit_out_lcd.tblaset_ysatta	= ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE;

	memset(&ctrl_out_lcd, 0, sizeof(ctrl_out_lcd));
	ctrl_out_lcd.intc						= D_IM_DISP_VFTMG_1ST;
	ctrl_out_lcd.inte.bit.LEE				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.GR0EE				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.GR1EE				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.GA0EE				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.GA1EE				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.LREE				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.GR0REE			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.GR1REE			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.GA0REE			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.GA1REE			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.VE				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.inte.bit.VE2				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.hablk						= 0;
	ctrl_out_lcd.fdoen						= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.fodata.rgb.r				= 0;
	ctrl_out_lcd.fodata.rgb.g				= 0;
	ctrl_out_lcd.fodata.rgb.b				= 0;
	ctrl_out_lcd.blankdt.ycc.y				= 0;
	ctrl_out_lcd.blankdt.ycc.cb				= 0;
	ctrl_out_lcd.blankdt.ycc.cr				= 0;
	ctrl_out_lcd.clbhsize					= 40;
	ctrl_out_lcd.clbdt[0].rgb.r				= 0;
	ctrl_out_lcd.clbdt[0].rgb.g				= 0;
	ctrl_out_lcd.clbdt[0].rgb.b				= 0;
	ctrl_out_lcd.clbdt[1].rgb.r				= 0;
	ctrl_out_lcd.clbdt[1].rgb.g				= 0;
	ctrl_out_lcd.clbdt[1].rgb.b				= 0;
	ctrl_out_lcd.clbdt[2].rgb.r				= 0;
	ctrl_out_lcd.clbdt[2].rgb.g				= 0;
	ctrl_out_lcd.clbdt[2].rgb.b				= 0;
	ctrl_out_lcd.bldctl.bit.BLD1			= D_IM_DISP_BLD_GRID;
	ctrl_out_lcd.bldctl.bit.BLD2			= D_IM_DISP_BLD_FACE;
	ctrl_out_lcd.bldctl.bit.BLD3			= D_IM_DISP_BLD_OSD0;
	ctrl_out_lcd.bldctl.bit.BLD4			= D_IM_DISP_BLD_OSD1;
	ctrl_out_lcd.r2y[0].bit.COEFFICIENT0	= 0;
	ctrl_out_lcd.r2y[0].bit.COEFFICIENT1	= 0;
	ctrl_out_lcd.r2y[0].bit.COEFFICIENT2	= 0;
	ctrl_out_lcd.r2y[1].bit.COEFFICIENT0	= 0;
	ctrl_out_lcd.r2y[1].bit.COEFFICIENT1	= 0;
	ctrl_out_lcd.r2y[1].bit.COEFFICIENT2	= 0;
	ctrl_out_lcd.r2y[2].bit.COEFFICIENT0	= 0;
	ctrl_out_lcd.r2y[2].bit.COEFFICIENT1	= 0;
	ctrl_out_lcd.r2y[2].bit.COEFFICIENT2	= 0;
	ctrl_out_lcd.clip_cal.y_cal.ygain		= 0;
	ctrl_out_lcd.clip_cal.y_cal.yofs		= 0;
	ctrl_out_lcd.clip_cal.y_clip.cph		= 0x0000;
	ctrl_out_lcd.clip_cal.y_clip.cpl		= 0x0000;
	ctrl_out_lcd.clip_cal.cb_cal.cgain		= 0;
	ctrl_out_lcd.clip_cal.cb_cal.cofs		= 0;
	ctrl_out_lcd.clip_cal.cb_clip.cph		= 0x0000;
	ctrl_out_lcd.clip_cal.cb_clip.cpl		= 0x0000;
	ctrl_out_lcd.clip_cal.cr_cal.cgain		= 0;
	ctrl_out_lcd.clip_cal.cr_cal.cofs		= 0;
	ctrl_out_lcd.clip_cal.cr_clip.cph		= 0x0000;
	ctrl_out_lcd.clip_cal.cr_clip.cpl		= 0x0000;
	ctrl_out_lcd.doctl0.bit.DTO1			= D_IM_DISP_DTO_R_Y0;
	ctrl_out_lcd.doctl0.bit.DTO2			= D_IM_DISP_DTO_R_Y0;
	ctrl_out_lcd.doctl0.bit.DTO3			= D_IM_DISP_DTO_R_Y0;
	ctrl_out_lcd.doctl0.bit.DTO4			= D_IM_DISP_DTO_G_CB;
	ctrl_out_lcd.doctl0.bit.DTO5			= D_IM_DISP_DTO_G_CB;
	ctrl_out_lcd.doctl0.bit.DTO6			= D_IM_DISP_DTO_G_CB;
	ctrl_out_lcd.doctl1.bit.SOO				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.doctl1.bit.SOE				= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.doctl1.bit.ODO0			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.doctl1.bit.ODO1			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.doctl1.bit.ODO2			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.doctl1.bit.ODE0			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.doctl1.bit.ODE1			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.doctl1.bit.ODE2			= D_IM_DISP_ENABLE_ON;
	ctrl_out_lcd.doctl2.bit.CLVS			= D_IM_DISP_CLVS_NORMAL;
	ctrl_out_lcd.doctl2.bit.CTOH			= D_IM_DISP_CTOH_LEFT;
	ctrl_out_lcd.doctl2.bit.CTOV			= D_IM_DISP_CTOV_TOP;
	ctrl_out_lcd.doctl2.bit.TRSOS			= D_IM_DISP_TRSOS_NONE;
	ctrl_out_lcd.trscode[0].bit.EAV0		= 0xB6;
	ctrl_out_lcd.trscode[0].bit.SAV0		= 0xAB;
	ctrl_out_lcd.trscode[0].bit.EAV1		= 0x9D;
	ctrl_out_lcd.trscode[0].bit.SAV1		= 0x80;
	ctrl_out_lcd.trscode[1].bit.EAV0		= 0xF1;
	ctrl_out_lcd.trscode[1].bit.SAV0		= 0xEC;
	ctrl_out_lcd.trscode[1].bit.EAV1		= 0xDA;
	ctrl_out_lcd.trscode[1].bit.SAV1		= 0xC7;
	ctrl_out_lcd.y2r[0].bit.COEFFICIENT0	= 0;
	ctrl_out_lcd.y2r[0].bit.COEFFICIENT1	= 0;
	ctrl_out_lcd.y2r[0].bit.COEFFICIENT2	= 0;
	ctrl_out_lcd.y2r[1].bit.COEFFICIENT0	= 0;
	ctrl_out_lcd.y2r[1].bit.COEFFICIENT1	= 0;
	ctrl_out_lcd.y2r[1].bit.COEFFICIENT2	= 0;
	ctrl_out_lcd.y2r[2].bit.COEFFICIENT0	= 0;
	ctrl_out_lcd.y2r[2].bit.COEFFICIENT1	= 0;
	ctrl_out_lcd.y2r[2].bit.COEFFICIENT2	= 0;
	ctrl_out_lcd.tblaset_gmen				= E_IM_DISP_CORRECT_PROC_ENABLE;
	ctrl_out_lcd.tblaset_gmtsl				= D_IM_DISP_TABLE_SURFACE_A;
	ctrl_out_lcd.tblaset_ysaten				= E_IM_DISP_CORRECT_PROC_ENABLE;
	ctrl_out_lcd.tblaset_ysatsl				= D_IM_DISP_TABLE_SURFACE_A;
	for(i = 0; i < D_IM_DISP_FACE_FRAME_COUNT; i++) {
		ctrl_out_lcd.face.param[i].ffdsta.bit.DSH		= 0;
		ctrl_out_lcd.face.param[i].ffdsta.bit.DSV		= 0;
		ctrl_out_lcd.face.param[i].ffsize.bit.FFHSZ		= 8;
		ctrl_out_lcd.face.param[i].ffsize.bit.FFVSZ		= 8;
		ctrl_out_lcd.face.param[i].ffwidth.bit.FFHWID	= 2;
		ctrl_out_lcd.face.param[i].ffwidth.bit.FFVWID	= 2;
		ctrl_out_lcd.face.param[i].ffclr.bit.FFCLRR		= 0;
		ctrl_out_lcd.face.param[i].ffclr.bit.FFCLRG		= 0;
		ctrl_out_lcd.face.param[i].ffclr.bit.FFCLRB		= 0;
	}
	ctrl_out_lcd.face.ffden					= 0x0000;
	ctrl_out_lcd.face.msff					= 0;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_VE]		= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_VE2]		= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_GR0EE]	= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_GR1EE]	= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_GA0EE]	= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_GA1EE]	= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_LEE]		= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_GR0REE]	= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_GR1REE]	= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_GA0REE]	= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_GA1REE]	= NULL;
	ctrl_out_lcd.int_callback[ImDisp_E_IM_DISP_INT_CB_LREE]	= NULL;

	ret = im_disp1_ctrl_output(ImDisp_E_IM_DISP_LCD_MIPI, &ctrl_trg_limit_out_lcd, &ctrl_out_lcd);
	if (ret != D_DDIM_OK){
		Ddim_Print(("I:im_disp1_ctrl_output error ret=%08X\n", ret));
	}

	// Set OSD data input block
	grrpgctl = ImDisp_E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP;

	memset(&ctrl_osd_lcd, 0, sizeof(ctrl_osd_lcd));
	ctrl_osd_lcd.gridt.bit.ifmt				= D_IM_DISP_GRIDT_IFMT_RGBA8888;
	ctrl_osd_lcd.gridt.bit.nbt				= D_IM_DISP_NBT_128BYTE;
	ctrl_osd_lcd.gridt.bit.cache			= 0;
	ctrl_osd_lcd.gridt.bit.pROT				= 0;
	ctrl_osd_lcd.gridt.bit.SLVSL			= D_IM_DISP_SLVSL_MASTER_INTERFACE_0;
	ctrl_osd_lcd.gridt.bit.ASLVSL			= D_IM_DISP_SLVSL_MASTER_INTERFACE_0;
	ctrl_osd_lcd.gridt.bit.IFBTMU			= D_IM_DISP_IFBTMU_UP_TO_BOTTOM;
	ctrl_osd_lcd.grtisize.size.width		= 640;
	ctrl_osd_lcd.grtisize.size.lines		= 480;
	ctrl_osd_lcd.grtdsta.bit.DSH			= 0;
	ctrl_osd_lcd.grtdsta.bit.DSV			= 0;
	ctrl_osd_lcd.gripo.bit.IPO1				= D_IM_DISP_IPO_RGBA8888_R;
	ctrl_osd_lcd.gripo.bit.IPO2				= D_IM_DISP_IPO_RGBA8888_G;
	ctrl_osd_lcd.gripo.bit.IPO3				= D_IM_DISP_IPO_RGBA8888_B;
	ctrl_osd_lcd.gripo.bit.IPO4				= D_IM_DISP_IPO_RGBA8888_A;
	ctrl_osd_lcd.grscctl_idset				= ImDisp_E_IM_DISP_INPUT_DATA_AREA_0;
	for(i = 0; i < ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT; i++) {
		ctrl_osd_lcd.grisize[i].size.width	= 8;
		ctrl_osd_lcd.grisize[i].size.lines	= 8;
		ctrl_osd_lcd.grhga[i]				= 8;
		ctrl_osd_lcd.grahga[i]				= 8;
		ctrl_osd_lcd.grdsta[i].bit.DSH		= 0;
		ctrl_osd_lcd.grdsta[i].bit.DSV		= 0;
	}
	ctrl_osd_lcd.grsa0[0]					= 0x51001000;
	ctrl_osd_lcd.grsa0[1]					= 0x51002000;
	ctrl_osd_lcd.grsa0[2]					= 0x51003000;
	ctrl_osd_lcd.grsa0[3]					= 0x51004000;
	ctrl_osd_lcd.grsa[0]					= 0x51005000;
	ctrl_osd_lcd.grsa[8]					= 0x5100D000;
	ctrl_osd_lcd.grasa[0]					= 0x51006000;
	ctrl_osd_lcd.grasa[9]					= 0x5100E000;
	ctrl_osd_lcd.graren						= 0;
	ctrl_osd_lcd.grbsl						= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_0		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_0		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_1		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_1		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_2		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_2		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_3		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_3		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_4		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_4		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_5		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_5		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_6		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_6		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_7		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_7		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_8		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_8		= 0;
	ctrl_osd_lcd.grblink.bit.BTIMH_9		= 0;
	ctrl_osd_lcd.grblink.bit.BTIML_9		= 0;
	ctrl_osd_lcd.grbinit					= 0;
	ctrl_osd_lcd.grbitrg					= D_IM_DISP_BITRG_NON;
	ctrl_osd_lcd.grrsz0						= ImDisp_E_IM_DISP_RSZSL_PADDING_THINNING;
	ctrl_osd_lcd.grrsz1.bit.hrszm			= 1;
	ctrl_osd_lcd.grrsz1.bit.hrszn			= 1;
	ctrl_osd_lcd.grrsz1.bit.hrszof			= 0;
	ctrl_osd_lcd.grrsz2.bit.vrszm			= 1;
	ctrl_osd_lcd.grrsz2.bit.vrszn			= 1;
	ctrl_osd_lcd.grrsz2.bit.vrszof			= 0;
	ctrl_osd_lcd.grrsz3.bit.hcsta			= 0;
	ctrl_osd_lcd.grrsz3.bit.vcsta			= 0;
	ctrl_osd_lcd.gry2r[0].bit.YR0			= 0;
	ctrl_osd_lcd.gry2r[0].bit.YR1			= 0;
	ctrl_osd_lcd.gry2r[0].bit.YR2			= 0;
	ctrl_osd_lcd.gry2r[1].bit.YR0			= 0;
	ctrl_osd_lcd.gry2r[1].bit.YR1			= 0;
	ctrl_osd_lcd.gry2r[1].bit.YR2			= 0;
	ctrl_osd_lcd.gry2r[2].bit.YR0			= 0;
	ctrl_osd_lcd.gry2r[2].bit.YR1			= 0;
	ctrl_osd_lcd.gry2r[2].bit.YR2			= 0;
	ctrl_osd_lcd.gralp						= 0;

	ret = im_disp1_ctrl_osd_layer(im_disp1_new(),ImDisp_E_IM_DISP_LCD_MIPI, E_IM_DISP_SEL_LAYER_OSD_0, &grrpgctl, &ctrl_osd_lcd);
	if (ret != D_DDIM_OK){
		Ddim_Print(("I:im_disp1_ctrl_osd_layer error ret=%08X\n", ret));
	}

	ret = im_disp1_ctrl_osd_layer(im_disp1_new(),ImDisp_E_IM_DISP_LCD_MIPI, E_IM_DISP_SEL_LAYER_OSD_1, &grrpgctl, &ctrl_osd_lcd);
	if (ret != D_DDIM_OK){
		Ddim_Print(("I:im_disp1_ctrl_osd_layer error ret=%08X\n", ret));
	}

	// Start.
	ret = im_disp2_start(im_disp2_new(),E_IM_DISP_SEL_LAYER_NONE, E_IM_DISP_SEL_LAYER_ALL, 0);
	if (ret != D_DDIM_OK){
		Ddim_Print(("I:im_disp2_start error ret=%08X\n", ret));
	}

	// Wait VSYNC
	ret = im_disp2_wait_vsync(im_disp2_new(),ImDisp_E_IM_DISP_LCD_MIPI, ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE, E_IM_DISP_WAIT_1_TIME);
	if (ret != D_DDIM_OK){
		Ddim_Print(("I:im_disp2_wait_vsync error ret=%08X\n", ret));
	}
}
@endcode
@}*//* end of im_disp*/

