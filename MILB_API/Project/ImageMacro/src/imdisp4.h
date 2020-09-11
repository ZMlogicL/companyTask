/*
 * imdisp4.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
#ifndef __IM_DISP4_H__
#define __IM_DISP4_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp1.h"
#include "imdisp8.h"
#define IM_TYPE_DISP4				(im_disp4_get_type())
#define IM_DISP4(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp4))
#define IM_IS_DISP4(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP4))

typedef struct   _ImDisp4 			ImDisp4;
typedef struct   _ImDisp4Private		ImDisp4Private;

struct _ImDisp4 {
	KObject parent;
};


KConstType 		im_disp4_get_type(void);
ImDisp4*	im_disp4_new(void);


/** Matrix kind. */
typedef enum {
	E_IM_DISP_MATRIX_KIND_Y2R = 0,		/**< YCbCr -> RGB's matrix		*/
	E_IM_DISP_MATRIX_KIND_R2Y,			/**< RGB -> YCbCr's matrix		*/
	E_IM_DISP_MATRIX_KIND_CC,			/**< Color space convert matrix	*/
} E_IM_DISP_MATRIX_KIND;

/** Vertical sync signal detection interrupt flag generation timing. */
typedef enum {
	E_IM_DISP_VSYNC_FLAG_NONE = 0,	/**< No any flag						*/
	E_IM_DISP_VSYNC_FLAG_FIRST,		/**< Generate a flag at No. 1 field		*/
	E_IM_DISP_VSYNC_FLAG_SECOND,	/**< Generate a flag at No. 2 field		*/
	E_IM_DISP_VSYNC_FLAG_BOTH,		/**< Generate a flag at No. 1 and No. 2	*/
} E_IM_DISP_VSYNC_FLAG;

/** Interruption demand permission state. */
typedef enum {
	E_IM_DISP_INTERRUPTION_STATE_NONE = 0x00000000,						/**< Set no  permission*/
	E_IM_DISP_INTERRUPTION_STATE_SET  = E_IM_DISP_CORRECT_SELECT_ALL,	/**< Set permission*/
} E_IM_DISP_INTERRUPTION_STATE;

/** FDOEN Register - (Enable force data output or not)*/
typedef enum {
	E_IM_DISP_FDOEN_ORDINARY_OUT = 0,	/**< FDOEN Register<br> Ordinary output.	*/
	E_IM_DISP_FDOEN_FORCE_DATA_OUT		/**< FDOEN Register<br> Force data output.	*/
}E_IM_DISP_FDOEN;


/**	AXISTS	*/
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	LRESP		:2;		/**< Main response<br>
										 Value:<br>
										 00b:Normal access success or Exclusive failure.<br>
										 01b:Exclusive access.<br>
										 10b:Slave error.<br>
										 11b:Decode error										*/
		ULONG				:14;	/**< Reserve												*/
		ULONG	GR0RESP		:2;		/**< GR0's response<br>
										 The value that can be selected is the same as LRESP.	*/
		ULONG				:2;		/**< Reserve												*/
		ULONG	GR1RESP		:2;		/**< GR1's response<br>
										 The value that can be selected is the same as LRESP.	*/
		ULONG				:2;		/**< Reserve												*/
		ULONG	GRA0RESP	:2;		/**< GR0's A component response<br>
										 The value that can be selected is the same as LRESP.	*/
		ULONG				:2;		/**< Reserve												*/
		ULONG	GRA1RESP	:2;		/**< GR1's A component response<br>
										 The value that can be selected is the same as LRESP.	*/
		ULONG				:2;		/**< Reserve												*/
	}AXI_Rep;	/**< Bit field */
}U_IM_DISP_AXISTS;


extern INT32 Im_DISP_Set_Display_Interface(E_IM_DISP_SEL block, BYTE ifs);

/**
Get display interface selection.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	ifs				Display I/F Selection .<br>
							<ul><li>@ref D_IM_DISP_IFS_NONE
								<li>@ref D_IM_DISP_IFS_LCD
								<li>@ref D_IM_DISP_IFS_HDMI
								<li>@ref D_IM_DISP_IFS_MIPI</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Display_Interface(E_IM_DISP_SEL block, BYTE *ifs);


/**
Set external start-up mode.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	tgkmd			External start-up mode.<br>
							<ul><li>@ref E_IM_DISP_TGKMD_NORMAL
								<li>@ref E_IM_DISP_TGKMD_EXTERNAL</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_STATUS_ABNORMAL		Can not set because TRG.TRG is not stoped.
@remarks	The data output unit needs to be in a reset state.
*/
extern INT32 Im_DISP_Set_External_Startup_Mode(E_IM_DISP_SEL block, E_IM_DISP_TGKMD tgkmd);

/**
Get external start-up mode.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	tgkmd			External start-up mode.<br>
							<ul><li>@ref E_IM_DISP_TGKMD_NORMAL
								<li>@ref E_IM_DISP_TGKMD_EXTERNAL</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_External_Startup_Mode(E_IM_DISP_SEL block, E_IM_DISP_TGKMD* tgkmd);

/**
Set external start-up operation start timing.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	tgkst			Operation start setting.<br>
							Value range:0~4095.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_STATUS_ABNORMAL		Can not set because TRG.TRG is not stoped.
*/
extern INT32 Im_DISP_Set_External_Startup_Timing(E_IM_DISP_SEL block, ULONG tgkst);

/**
Get external start-up operation start timing.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	tgkst			Operation start setting.<br>
							Value range:0~4095.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_External_Startup_Timing(E_IM_DISP_SEL block, ULONG* tgkst);

/**
Set a flag generation timing of vertical synchronization signal.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	timing			Generation timing.<br>
							<ul><li>@ref E_IM_DISP_VSYNC_FLAG_NONE
								<li>@ref E_IM_DISP_VSYNC_FLAG_FIRST
								<li>@ref E_IM_DISP_VSYNC_FLAG_SECOND
								<li>@ref E_IM_DISP_VSYNC_FLAG_BOTH</ul>
*/
extern VOID Im_DISP_Set_Vsync_Int_Timing(E_IM_DISP_SEL block, E_IM_DISP_VSYNC_FLAG timing);

/**
Get a flag generation timing of vertical synchronization signal.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	timing			Generation timing.<br>
							<ul><li>@ref E_IM_DISP_VSYNC_FLAG_NONE
								<li>@ref E_IM_DISP_VSYNC_FLAG_FIRST
								<li>@ref E_IM_DISP_VSYNC_FLAG_SECOND
								<li>@ref E_IM_DISP_VSYNC_FLAG_BOTH</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Vsync_Int_Timing(E_IM_DISP_SEL block, E_IM_DISP_VSYNC_FLAG *timing);

/**
Set interruption demand permission setting.<br>
@param[in]	block					Common block selection.<br>
									<ul><li>@ref E_IM_DISP_HDMI
										<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	interruption_select		Bit map to select set item. <br>
									It must be set to a member of @ref E_IM_DISP_INTERRUPTION_SELECT or their OR value.<br>
@param[in]	interruption_state		The interruption demand permission setting.<br>
									<ul><li>@ref E_IM_DISP_INTERRUPTION_STATE_NONE
										<li>@ref E_IM_DISP_INTERRUPTION_STATE_SET</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Set_Int(E_IM_DISP_SEL block, UINT32 interruption_select, E_IM_DISP_INTERRUPTION_STATE interruption_state);

/**
Get interruption demand permission setting.<br>
@param[in]	block					Common block selection.<br>
									<ul><li>@ref E_IM_DISP_HDMI
										<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	interruption_state		The interruption demand permission setting.<br>
									It should be AND with E_IM_DISP_INTERRUPTION_SELECT's member to get<br>
									the result.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Int(E_IM_DISP_SEL block, UINT32* interruption_state);

/**
Set interruption's call-back function pointer.<br>
@param[in]	block				Common block selection.<br>
								<ul><li>@ref E_IM_DISP_HDMI
									<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	interruption_select	Bit map to select set item. <br>
								It must be set to a member of @ref E_IM_DISP_INTERRUPTION_SELECT or their OR value.<br>
@param[in]	vp_callback			The call-back pointer to set. <br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/

extern INT32 Im_DISP_Get_AXI_Status(E_IM_DISP_SEL block, U_IM_DISP_AXISTS *axi_state);

/**
Set parameter reflect timing.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	timing			Register parameter reflect timing.<br>
							<ul><li>@ref E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
								<li>@ref E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy.
*/
extern INT32 Im_DISP_Set_Output_Parameter_Reflect_Timing(E_IM_DISP_SEL block, E_IM_DISP_RPGTMG timing);

/**
Get parameter reflect timing.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	timing			Register parameter reflect timing.<br>
							<ul><li>@ref E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
								<li>@ref E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Output_Parameter_Reflect_Timing(E_IM_DISP_SEL block, E_IM_DISP_RPGTMG *timing);

/**
Set parameter reflect enable.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	enable			Register parameter reflect enable.<br>
							<ul><li>@ref D_IM_DISP_ENABLE_OFF
								<li>@ref D_IM_DISP_ENABLE_ON</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Set_Output_Parameter_Reflect_Enable(E_IM_DISP_SEL block, UINT32 enable);

/**
Get parameter reflect enable.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	enable			Register parameter reflect enable.<br>
							<ul><li>@ref D_IM_DISP_ENABLE_OFF
								<li>@ref D_IM_DISP_ENABLE_ON</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Output_Parameter_Reflect_Enable(E_IM_DISP_SEL block, UINT32 *enable);

/**
Set transmission mode.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	tsl				Register parameter transmission mode.<br>
							<ul><li>@ref D_IM_DISP_TSL_PROGRESSIVE
								<li>@ref D_IM_DISP_TSL_INTERLACE</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy.
*/
extern INT32 Im_DISP_Set_TSL(E_IM_DISP_SEL block, BYTE tsl);

/**
Get transmission mode.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	tsl				Register parameter transmission mode.<br>
							<ul><li>@ref D_IM_DISP_TSL_PROGRESSIVE
								<li>@ref D_IM_DISP_TSL_INTERLACE</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_TSL(E_IM_DISP_SEL block, BYTE *tsl);

/**
Get output size.<br>
@param[in]	block		Common block selection.<br>
						<ul><li>@ref E_IM_DISP_HDMI
							<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	ovsize		Vertical output size
@param[out]	ohsize		Horizonal output size
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Output_Size(E_IM_DISP_SEL block, ULONG *ovsize, ULONG *ohsize);

/**
Switch force data out.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	is_enable		0 mean disable and 1 mean enable.<br>
							<ul><li>@ref E_IM_DISP_FDOEN_ORDINARY_OUT
								<li>@ref E_IM_DISP_FDOEN_FORCE_DATA_OUT</ul>
*/
extern VOID Im_DISP_Set_Force_Out_Data_Enable(E_IM_DISP_SEL block, E_IM_DISP_FDOEN is_enable);

/**
Get force data out state.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	is_enable		0 mean disable and 1 mean enable.<br>
							<ul><li>@ref E_IM_DISP_FDOEN_ORDINARY_OUT
								<li>@ref E_IM_DISP_FDOEN_FORCE_DATA_OUT</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32  Im_DISP_Get_Force_Out_Data_Enable(E_IM_DISP_SEL block, E_IM_DISP_FDOEN *is_enable);

/**
Set force output data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	color_data		Force output color data.
*/
extern VOID Im_DISP_Set_Force_Out_Data(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR color_data);

/**
Get force output data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	color_data		Force output color data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Force_Out_Data(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR *color_data);

/**
Set color bar's width.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	clbhsize		Color bar's width.<br>
							Value range:0~65535<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>CLBHSIZE * 16 >= OHSIZE
			</ul>
*/
extern INT32 Im_DISP_Set_Color_Bar_Size(E_IM_DISP_SEL block, ULONG clbhsize);

/**
Get color bar's width.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	clbhsize		Color bar's width.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Color_Bar_Size(E_IM_DISP_SEL block, ULONG *clbhsize);

/**
Set color bar's color.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	clbdt			Color bar display color.<br>
@param[in]	clbdt_size		clbdt's size that must not be over 16.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Set_Color_Bar(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR const *const clbdt, UINT32 clbdt_size);

/**
Get color bar's color.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	clbdt			The array of color bar
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Color_Bar(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR clbdt[D_IM_DISP_COLOR_BAR_COUNT]);

/**
Set blend order.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	blend			Blend order data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Set_Blend(E_IM_DISP_SEL block, U_IM_DISP_BLDCTL blend);

/**
Get blend order.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	blend			Blend order data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Blend(E_IM_DISP_SEL block, U_IM_DISP_BLDCTL *blend);

/**
Set YCbCr <-> RGB matrix data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	kind			Matrix kind.<br>
							<ul><li>@ref E_IM_DISP_MATRIX_KIND_Y2R
								<li>@ref E_IM_DISP_MATRIX_KIND_R2Y</ul>
@param[in]	matrix			Matrix data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>Value range of COEFFICIENT0 is -128~127.<br>
					The matrix coefficient value is COEFFICIENT0/64.<br>
				<li>Value range of COEFFICIENT1 is -128~127.<br>
					The matrix coefficient value is COEFFICIENT1/64.<br>
				<li>Value range of COEFFICIENT2 is -128~127.<br>
					The matrix coefficient value is COEFFICIENT2/64.<br>
			</ul>
*/
extern INT32 Im_DISP_Set_Output_Matrix(E_IM_DISP_SEL block, E_IM_DISP_MATRIX_KIND kind, const U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE]);

/**
Get YCbCr <-> RGB matrix data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	kind			Matrix kind.<br>
							<ul><li>@ref E_IM_DISP_MATRIX_KIND_Y2R
								<li>@ref E_IM_DISP_MATRIX_KIND_R2Y</ul>
@param[out]	matrix			Matrix data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Output_Matrix(E_IM_DISP_SEL block, E_IM_DISP_MATRIX_KIND kind, U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE]);

/**
Set clip/gain/offset.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	clip_cal		clip/gain/offset data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>Value range of y_cal.gain is 0~255.<br>
					The gain value is y_cal.gain/256.<br>
					The gain value is 1(=256/256) when y_cal.gain is 0.<br>
				<li>Value range of cb_cal.gain is 0~255.<br>
					The gain value is cb_cal.gain/128.<br>
					The gain value is 2(=256/128) when cb_cal.gain is 0.<br>
				<li>Value range of cr_cal.gain is 0~255.<br>
					The gain value is cr_cal.gain/128.<br>
					The gain value is 2(=256/128) when cr_cal.gain is 0.<br>
				<li>Value range of y_cal.ofs is 0~8191.<br>
				<li>Value range of cb_cal.ofs is -4096~4095.<br>
				<li>Value range of cr_cal.ofs is -4096~4095.<br>
			</ul>
*/
extern INT32 Im_DISP_Set_Clip(E_IM_DISP_SEL block, T_IM_DISP_CLIP_CAL const *const clip_cal);

/**
Get clip/gain/offset.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	clip_cal		clip/gain/offset data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Clip(E_IM_DISP_SEL block, T_IM_DISP_CLIP_CAL *const clip_cal);

/**
Set RGB/YCbCr's output order.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	doctl0			RGB/YCbCr's output order.
*/

extern VOID Im_DISP_Set_Output_Order(E_IM_DISP_SEL block, U_IM_DISP_DOCTL0 doctl0);

/**
Get RGB/YCbCr's output order.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	doctl0			RGB/YCbCr's output order.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Output_Order(E_IM_DISP_SEL block, U_IM_DISP_DOCTL0 *doctl0);

/**
Set grid data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	grid			Grid data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GHDSTA.DSH is a multiple of 2
				<li>GHDSTA.DSV is a multiple of 2
				<li>GVDSTA.DSH is a multiple of 2
				<li>GVDSTA.DSV is a multiple of 2
				<li>GLENGTH.GHLEN is a multiple of 2
				<li>GLENGTH.GHLEN >= 8
				<li>GLENGTH.GVLEN is a multiple of 2
				<li>GLENGTH.GVLEN >= 8
				<li>GWIDTH.GHWID is a multiple of 2
				<li>GWIDTH.GHWID >= 2
				<li>GWIDTH.GVWID is a multiple of 2
				<li>GWIDTH.GVWID >= 2
				<li>GITVL.GHITV is a multiple of 2
				<li>GITVL.GHITV >= GWIDTH.GHWID + 2
				<li>GITVL.GVITV is a multiple of 2
				<li>GITVL.GVITV >= GWIDTH.GVWID + 2
			</ul>
*/
extern INT32 Im_DISP_Set_Grid(E_IM_DISP_SEL block, T_IM_DISP_GRID const *const grid);

/**
Get grid data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	grid			Grid data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Grid(E_IM_DISP_SEL block, T_IM_DISP_GRID *const grid);

/**
Set grid line display enable.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	gdispen			Grid display enable.<br>
							<ul><li>@ref E_IM_DISP_GDISPEN_NOT_DISPLAY
								<li>@ref E_IM_DISP_GDISPEN_DISPLAY</ul>
*/
extern VOID Im_DISP_Set_Grid_Enable(E_IM_DISP_SEL block, E_IM_DISP_GDISPEN gdispen);

/**
Get grid line display enable.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	gdispen			Grid display enable.<br>
							<ul><li>@ref E_IM_DISP_GDISPEN_NOT_DISPLAY
								<li>@ref E_IM_DISP_GDISPEN_DISPLAY</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Grid_Enable(E_IM_DISP_SEL block, E_IM_DISP_GDISPEN *gdispen);

/**
Set face frame data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	frame_count		Face frame data count.<br>
							Value range:1-42<br>
@param[in]	face			Face frame data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>FFDSTA.FFDSH is a multiple of 2
				<li>FFDSTA.FFDSV is a multiple of 2
				<li>FFSIZE.FFHSZ is a multiple of 2
				<li>FFSIZE.FFHSZ >= 8
				<li>FFSIZE.FFVSZ is a multiple of 2
				<li>FFSIZE.FFVSZ >= 8
				<li>FFWIDTH.FFHWID is a multiple of 2
				<li>FFWIDTH.FFHWID >= 2
				<li>FFWIDTH.FFVWID is a multiple of 2
				<li>FFWIDTH.FFVWID >= 2
			</ul>
*/

#endif /* __IM_DISP4_H__ */
